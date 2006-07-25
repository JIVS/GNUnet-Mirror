/*
     This file is part of GNUnet.
     (C) 2001, 2002, 2004, 2005, 2006 Christian Grothoff (and other contributing authors)

     GNUnet is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published
     by the Free Software Foundation; either version 2, or (at your
     option) any later version.

     GNUnet is distributed in the hope that it will be useful, but
     WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
     General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with GNUnet; see the file COPYING.  If not, write to the
     Free Software Foundation, Inc., 59 Temple Place - Suite 330,
     Boston, MA 02111-1307, USA.
*/

/**
 * @file transports/ip6.c
 * @brief code to determine the IP(v6) of the local machine
 *
 * Todo:
 * * scanning of network devices for IPv6 (first: find good
 *   API to do it, doesn't seem to exist!)
 *
 * @author Christian Grothoff
 * @author Tzvetan Horozov
 */

#include <stdlib.h>
#include "platform.h"
#include "gnunet_util.h"
#include "ip6.h"

/* maximum length of hostname */
#define MAX_HOSTNAME 1024

/**
 * Obtain the identity information for the current node
 * (connection information), conInfo.
 * @return SYSERR on failure, OK on success
 */
static int getAddress6FromHostname(struct GE_Context * ectx,
				   IP6addr * identity) {
  char hostname[MAX_HOSTNAME];
  struct hostent * ip;
  
  if (0 != gethostname(hostname, MAX_HOSTNAME)) {
    GE_LOG_STRERROR(ectx,
		    GE_ERROR | GE_ADMIN | GE_USER | GE_BULK,
		    "gethostname");
    return SYSERR;
  }
  /* LOG(LOG_DEBUG,
      " looking up $HOSTNAME (%s) to obtain local IP\n",
      hostname); */

  ip = gethostbyname2(hostname, AF_INET6);
  if (ip == NULL) {
    GE_LOG(ectx,
	   GE_ERROR | GE_ADMIN | GE_USER | GE_BULK,
	   _("Could not find IP of host `%s': %s\n"),
	   hostname, 
	   hstrerror(h_errno));
    return SYSERR;
  }
  if (ip->h_addrtype != AF_INET6) {
    GE_BREAK(ectx,
	     0);
    return SYSERR;
  }
  GE_ASSERT(ectx,
	    sizeof(struct in6_addr) == sizeof(identity->addr));
  memcpy(&identity->addr[0],
	 ip->h_addr_list[0],
	 sizeof(struct in6_addr));
  return OK;
}

/**
 * Get the IP address for the local machine.
 * @return SYSERR on error, OK on success
 */
static int getAddress6(struct GC_Configuration * cfg,
		       struct GE_Context * ectx,
		       IP6addr  * address){
  char * ipString;
  int retval;
  struct hostent * ip; /* for the lookup of the IP in gnunet.conf */

  retval = SYSERR;
  if (0 != GC_get_configuration_value_string(cfg,
					     "NETWORK",
					     "IP",
					     NULL,
					     &ipString)) {
    retval = getAddress6FromHostname(ectx,
				     address);
  } else {
    ip = gethostbyname2(ipString,
			AF_INET6);
    if (ip == NULL) {
      GE_LOG(ectx,
	     GE_ERROR | GE_USER | GE_BULK,
	     _("Could not resolve `%s': %s\n"),
	     ipString, 
	     hstrerror(h_errno));
      retval = SYSERR;
    } else {
      if (ip->h_addrtype != AF_INET6) {
	GE_ASSERT(ectx,
		  0);
	retval = SYSERR;
      } else {
	GE_ASSERT(ectx,
		  sizeof(struct in6_addr) == sizeof(address->addr));
	memcpy(&address->addr[0],
	       ip->h_addr_list[0],
	       sizeof(struct in6_addr));
	retval = OK;
      }
    }
    FREE(ipString);
  }
  return retval;
}

/**
 * Get the IPv6 address for the local machine.
 * @return SYSERR on error, OK on success
 */
int getPublicIP6Address(struct GC_Configuration * cfg,
			struct GE_Context * ectx,
			IP6addr * address) {
  static IP6addr myAddress;
  static cron_t last;
  static cron_t lastError;
  cron_t now;

  now = get_time();
  if (last + cronMINUTES < now) {
    if (lastError + 30 * cronSECONDS > now)
      return SYSERR;
    if (SYSERR == getAddress6(cfg,
			      ectx,
			      &myAddress)) {
      lastError = now;
      GE_LOG(ectx,
	     GE_WARNING | GE_USER | GE_BULK,
	     _("Failed to obtain my (external) %s address!\n"),
	     "IPv6");
      return SYSERR;
    }
    last = now;
  }
  memcpy(address,
	 &myAddress,
	 sizeof(IP6addr));
  return OK;
}

/* end of ip6.c */
