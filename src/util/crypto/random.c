/*
     This file is part of GNUnet.
     (C) 2001, 2002, 2003, 2004, 2005, 2006 Christian Grothoff (and other contributing authors)

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
 * @file util/crypto/random.c
 * @brief functions to gather random numbers
 * @author Christian Grothoff
 */
#include "platform.h"
#include "gnunet_util.h"
#include "gnunet_util_crypto.h"
#include "locking_gcrypt.h"
#include <gcrypt.h>

/**
 * @return a random value in the interval [0,i[.
 */
unsigned int
GNUNET_random_u32 (int mode, unsigned int i)
{
#ifdef gcry_fast_random_poll
  static unsigned int invokeCount;
#endif
  unsigned int ret;

  GNUNET_GE_ASSERT (NULL, i > 0);

  if (mode == GNUNET_RANDOM_QUALITY_STRONG)
    {
      GNUNET_lock_gcrypt_ ();
      /* see http://lists.gnupg.org/pipermail/gcrypt-devel/2004-May/000613.html */
#ifdef gcry_fast_random_poll
      if ((invokeCount++ % 256) == 0)
        gcry_fast_random_poll ();
#endif
      ret = rand ();            /* in case gcry_randomize fails,
                                   we at least get a pseudo-
                                   random number this way */
      gcry_randomize ((unsigned char *) &ret,
                      sizeof (unsigned int), GCRY_STRONG_RANDOM);
      GNUNET_unlock_gcrypt_ ();
      return ret % i;
    }
  else
    {
      ret = i * ((double) RANDOM () / RAND_MAX);
      if (ret >= i)
        ret = i - 1;
      return ret;
    }
}


/**
 * Get an array with a random permutation of the
 * numbers 0...n-1.
 * @param mode GNUNET_RANDOM_QUALITY_STRONG if the strong (but expensive)
 *        PRNG should be used, GNUNET_RANDOM_QUALITY_WEAK otherwise
 * @param n the size of the array
 * @return the permutation array (allocated from heap)
 */
unsigned int *
GNUNET_permute (int mode, unsigned int n)
{
  unsigned int *ret;
  unsigned int i;
  unsigned int tmp;
  unsigned int x;

  GNUNET_GE_ASSERT (NULL, n > 0);
  ret = GNUNET_malloc (n * sizeof (int));
  for (i = 0; i < n; i++)
    ret[i] = i;
  for (i = 0; i < n; i++)
    {
      x = GNUNET_random_u32 (mode, n);
      tmp = ret[x];
      ret[x] = ret[i];
      ret[i] = tmp;
    }
  return ret;
}

/**
 * Random on unsigned 64-bit values.
 */
unsigned long long
GNUNET_random_u64 (int mode, unsigned long long u)
{
  unsigned long long ret;

  GNUNET_GE_ASSERT (NULL, u > 0);
  if (mode == GNUNET_RANDOM_QUALITY_STRONG)
    {
      GNUNET_lock_gcrypt_ ();
      gcry_randomize ((unsigned char *) &ret,
                      sizeof (unsigned long long), GCRY_STRONG_RANDOM);
      GNUNET_unlock_gcrypt_ ();
      return ret % u;
    }
  else
    {
      ret = u * ((double) RANDOM () / RAND_MAX);
      if (ret >= u)
        ret = u - 1;
      return ret;
    }
}

/* end of random.c */
