/*
 This file is part of GNUnet.
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
 * @author Nathan Evans
 * @file include/dv.h
 * @brief Structs necessary for the dv service providing
 * fisheye distance vector type routing.
 */
#ifndef DV_H
#define DV_H

#include "gnunet_core.h"

/**
 * Message that gets sent between nodes updating dv infos
 */
typedef struct
{
  GNUNET_MessageHeader header;

  /**
   * Cost from received from node to neighbor node, takes distance into account
   */
  unsigned int cost GNUNET_PACKED;

  /**
   * Identity of neighbor we learned information about
   */
  GNUNET_PeerIdentity neighbor;

  /**
   * Neighbor ID to use when sending to this peer
   */
  unsigned int neighbor_id GNUNET_PACKED;

} p2p_dv_MESSAGE_NeighborInfo;

/**
 * Message that gets sent between nodes carrying information
 */
typedef struct
{
  GNUNET_MessageHeader header;


  /**
   * Identity of peer that ultimately sent the message.
   * Should be looked up in the set of 'neighbor_id's of
   * the referring peer.
   */
  unsigned int sender GNUNET_PACKED;

  /**
   * Identity of neighbor this message is going to.  Should
   * be looked up in the set of our own identifiers for
   * neighbors!
   */
  unsigned int recipient GNUNET_PACKED;

} p2p_dv_MESSAGE_Data;


#endif

/* end of dv.h */
