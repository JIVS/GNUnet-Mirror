/*
     This file is part of GNUnet.
     (C) 2005, 2006 Christian Grothoff (and other contributing authors)

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
 * @file util/string/string.c
 * @brief string functions
 * @author Nils Durner
 * @author Christian Grothoff
 */

#include "platform.h"
#if HAVE_ICONV_H
#include <iconv.h>
#endif
#include "gnunet_util_string.h"


int
GNUNET_snprintf (char *buf, size_t size, const char *format, ...)
{
  int ret;
  va_list args;

  va_start (args, format);
  ret = VSNPRINTF (buf, size, format, args);
  va_end (args);
  GNUNET_GE_ASSERT (NULL, ret <= size);
  return ret;
}

/**
 * Give relative time in human-readable fancy format.
 * @param delta time in milli seconds
 */
char *
GNUNET_get_time_interval_as_fancy_string (unsigned long long delta)
{
  const char *unit = _( /* time unit */ "ms");
  char *ret;

  if (delta > 5 * 1000)
    {
      delta = delta / 1000;
      unit = _( /* time unit */ "s");
      if (delta > 5 * 60)
        {
          delta = delta / 60;
          unit = _( /* time unit */ "m");
          if (delta > 5 * 60)
            {
              delta = delta / 60;
              unit = _( /* time unit */ "h");
              if (delta > 5 * 24)
                {
                  delta = delta / 24;
                  unit = _( /* time unit */ " days");
                }
            }
        }
    }
  ret = GNUNET_malloc (32);
  GNUNET_snprintf (ret, 32, "%llu%s", delta, unit);
  return ret;
}

/**
 * Convert a given filesize into a fancy human-readable format.
 */
char *
GNUNET_get_byte_size_as_fancy_string (unsigned long long size)
{
  const char *unit = _( /* size unit */ "b");
  char *ret;

  if (size > 5 * 1024)
    {
      size = size / 1024;
      unit = _( /* size unit */ "KiB");
      if (size > 5 * 1024)
        {
          size = size / 1024;
          unit = _( /* size unit */ "MiB");
          if (size > 5 * 1024)
            {
              size = size / 1024;
              unit = _( /* size unit */ "GiB");
              if (size > 5 * 1024)
                {
                  size = size / 1024;
                  unit = _( /* size unit */ "TiB");
                }
            }
        }
    }
  ret = GNUNET_malloc (32);
  GNUNET_snprintf (ret, 32, "%llu%s", size, unit);
  return ret;
}




/**
 * Convert the len characters long character sequence
 * given in input that is in the given charset
 * to UTF-8.
 * @return the converted string (0-terminated),
 *  if conversion fails, a copy of the orignal
 *  string is returned.
 */
char *
GNUNET_convert_string_to_utf8 (struct GNUNET_GE_Context *ectx,
                               const char *input, size_t len,
                               const char *charset)
{
  char *ret;
#if ENABLE_NLS && HAVE_ICONV
  size_t tmpSize;
  size_t finSize;
  char *tmp;
  char *itmp;
  iconv_t cd;

  cd = iconv_open ("UTF-8", charset);
  if (cd == (iconv_t) - 1)
    {
      GNUNET_GE_LOG_STRERROR (ectx,
                              GNUNET_GE_USER | GNUNET_GE_ADMIN |
                              GNUNET_GE_WARNING | GNUNET_GE_BULK,
                              "iconv_open");
      ret = GNUNET_malloc (len + 1);
      memcpy (ret, input, len);
      ret[len] = '\0';
      return ret;
    }
  tmpSize = 3 * len + 4;
  tmp = GNUNET_malloc (tmpSize);
  itmp = tmp;
  finSize = tmpSize;
  if (iconv (cd, (char **) &input, &len, &itmp, &finSize) == (size_t) - 1)
    {
      GNUNET_GE_LOG_STRERROR (ectx,
                              GNUNET_GE_USER | GNUNET_GE_WARNING |
                              GNUNET_GE_BULK, "iconv");
      iconv_close (cd);
      GNUNET_free (tmp);
      ret = GNUNET_malloc (len + 1);
      memcpy (ret, input, len);
      ret[len] = '\0';
      return ret;
    }
  ret = GNUNET_malloc (tmpSize - finSize + 1);
  memcpy (ret, tmp, tmpSize - finSize);
  ret[tmpSize - finSize] = '\0';
  GNUNET_free (tmp);
  if (0 != iconv_close (cd))
    GNUNET_GE_LOG_STRERROR (ectx,
                            GNUNET_GE_ADMIN | GNUNET_GE_WARNING |
                            GNUNET_GE_REQUEST, "iconv_close");
  return ret;
#else
  ret = GNUNET_malloc (len + 1);
  memcpy (ret, input, len);
  ret[len] = '\0';
  return ret;
#endif
}




/**
 * Complete filename (a la shell) from abbrevition.
 * @param fil the name of the file, may contain ~/ or
 *        be relative to the current directory
 * @returns the full file name,
 *          NULL is returned on error
 */
char *
GNUNET_expand_file_name (struct GNUNET_GE_Context *ectx, const char *fil)
{
  char *buffer;
#ifndef MINGW
  size_t len;
  size_t n;
  char *fm;
  const char *fil_ptr;
#else
  char *fn;
  long lRet;
#endif

  if (fil == NULL)
    return NULL;

#ifndef MINGW
  if (fil[0] == DIR_SEPARATOR)
    /* absolute path, just copy */
    return GNUNET_strdup (fil);
  if (fil[0] == '~')
    {
      fm = getenv ("HOME");
      if (fm == NULL)
        {
          GNUNET_GE_LOG (ectx,
                         GNUNET_GE_USER | GNUNET_GE_ADMIN | GNUNET_GE_WARNING
                         | GNUNET_GE_IMMEDIATE,
                         _
                         ("Failed to expand `$HOME': environment variable `HOME' not set"));
          return NULL;
        }
      fm = GNUNET_strdup (fm);
      /* do not copy '~' */
      fil_ptr = fil + 1;

      /* skip over dir seperator to be consistent */
      if (fil_ptr[0] == DIR_SEPARATOR)
        fil_ptr++;
    }
  else
    {
      /* relative path */
      fil_ptr = fil;
      len = 512;
      fm = NULL;
      while (1)
        {
          buffer = GNUNET_malloc (len);
          if (getcwd (buffer, len) != NULL)
            {
              fm = buffer;
              break;
            }
          if ((errno == ERANGE) && (len < 1024 * 1024 * 4))
            {
              len *= 2;
              GNUNET_free (buffer);
              continue;
            }
          GNUNET_free (buffer);
          break;
        }
      if (fm == NULL)
        {
          GNUNET_GE_LOG_STRERROR (ectx,
                                  GNUNET_GE_USER | GNUNET_GE_WARNING |
                                  GNUNET_GE_IMMEDIATE, "getcwd");
          buffer = getenv ("PWD");      /* alternative */
          if (buffer != NULL)
            fm = GNUNET_strdup (buffer);
        }
      if (fm == NULL)
        fm = GNUNET_strdup ("./");      /* give up */
    }
  n = strlen (fm) + 1 + strlen (fil_ptr) + 1;
  buffer = GNUNET_malloc (n);
  GNUNET_snprintf (buffer, n, "%s/%s", fm, fil_ptr);
  GNUNET_free (fm);
  return buffer;
#else
  fn = GNUNET_malloc (MAX_PATH + 1);

  if ((lRet = plibc_conv_to_win_path (fil, fn)) != ERROR_SUCCESS)
    {
      SetErrnoFromWinError (lRet);
      GNUNET_GE_LOG_STRERROR (ectx,
                              GNUNET_GE_USER | GNUNET_GE_WARNING |
                              GNUNET_GE_IMMEDIATE, "plibc_conv_to_win_path");
      return NULL;
    }
  /* is the path relative? */
  if ((strncmp (fn + 1, ":\\", 2) != 0) && (strncmp (fn, "\\\\", 2) != 0))
    {
      char szCurDir[MAX_PATH + 1];
      lRet = GetCurrentDirectory (MAX_PATH + 1, szCurDir);
      if (lRet + strlen (fn) + 1 > (MAX_PATH + 1))
        {
          SetErrnoFromWinError (ERROR_BUFFER_OVERFLOW);
          GNUNET_GE_LOG_STRERROR (ectx,
                                  GNUNET_GE_USER | GNUNET_GE_WARNING |
                                  GNUNET_GE_IMMEDIATE, "GetCurrentDirectory");
          return NULL;
        }
      buffer = GNUNET_malloc (MAX_PATH + 1);
      GNUNET_snprintf (buffer, MAX_PATH + 1, "%s\\%s", szCurDir, fn);
      GNUNET_free (fn);
      fn = buffer;
    }

  return fn;
#endif
}



/* end of string.c */
