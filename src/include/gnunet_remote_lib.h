/*
      This file is part of GNUnet
      (C) 2008 Christian Grothoff (and other contributing authors)

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
 * @file include/gnunet_remote_lib.h
 * @brief remote testing library for running gnunetd on multiple machines
 * @author Nathan Evans
 */

#ifndef GNUNET_REMOTE_LIB_H
#define GNUNET_REMOTE_LIB_H

#include "gnunet_util.h"

#ifdef __cplusplus
extern "C"
{
#if 0                           /* keep Emacsens' auto-indent happy */
}
#endif
#endif


/**
 * Linked list of information about daemon processes.
 */
struct GNUNET_REMOTE_DaemonContext
{
  struct GNUNET_TESTING_DaemonContext *next;
  GNUNET_PeerIdentity peer;
  pid_t pid;
  unsigned short port;
  char *configFile;
};


int GNUNET_REMOTE_read_config(const char *config_file,struct GNUNET_GC_Configuration **newcfg);

/**
 * Starts a single gnunet daemon on a remote machine
 *
 * @param gnunetd_home directory where gnunetd is on remote machine
 * @param localConfigPath local configuration path for config file
 * @param remote_config_path remote path to copy local config to
 * @param configFileName  file to copy and use on remote machine
 * @param ip_address ip address of remote machine
 * @param username username to use for ssh (assumed to be used with ssh-agent)
 */
int
GNUNET_REMOTE_start_daemon (char *gnunetd_home,
                             char *localConfigPath,char *configFileName,char *remote_config_path,char *ip_address,
                             char *username);
                             
int GNUNET_REMOTE_start_daemons(struct GNUNET_GC_Configuration **newcfg);


#if 0                           /* keep Emacsens' auto-indent happy */
{
#endif
#ifdef __cplusplus
}
#endif

#endif