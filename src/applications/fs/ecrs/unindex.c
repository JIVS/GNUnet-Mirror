/*
     This file is part of GNUnet.
     (C) 2003, 2004 Christian Grothoff (and other contributing authors)

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
 * @file applications/fs/ecrs/unindex.c
 * @author Krista Bennett
 * @author Christian Grothoff
 *
 * Unindex file.
 *
 * TODO:
 * - code cleanup (share more with
 *   upload.c, move detect index/unindex to FS_lib)
 */

#include "platform.h"
#include "gnunet_protocols.h"
#include "gnunet_ecrs_lib.h"
#include "gnunet_fs_lib.h"
#include "gnunet_getoption_lib.h"
#include "ecrs_core.h"
#include "ecrs.h"
#include "fs.h"
#include "tree.h"

/**
 * Append the given key and query to the iblock[level].
 * If iblock[level] is already full, compute its chk
 * and push it to level+1.  iblocks is guaranteed to
 * be big enough.
 *
 * This function matches exactly upload.c::pushBlock,
 * except in the call to 'FS_delete'.  TODO: refactor
 * to avoid code duplication (move to block.c, pass
 * FS_delete as argument!).
 */
static int pushBlock(GNUNET_TCP_SOCKET * sock,
		     const CHK * chk,	
		     unsigned int level,
		     Datastore_Value ** iblocks) {
  unsigned int size;
  unsigned int present;
  Datastore_Value * value;
  DBlock * db;
  CHK ichk;

  size = ntohl(iblocks[level]->size) - sizeof(Datastore_Value); 
  present = (size - sizeof(DBlock)) / sizeof(CHK);
  db = (DBlock*) &iblocks[level][1];
  if (present == CHK_PER_INODE) {
    fileBlockGetKey(db,
		    size,
		    &ichk.key);
    fileBlockGetQuery(db,
		      size,
		      &ichk.query);
    if (OK != pushBlock(sock, 
			&ichk,
			level+1, 
			iblocks))
      return SYSERR;
    fileBlockEncode(db,
		    size,
		    &ichk.query,
		    &value);
    if (OK != FS_delete(sock,
			value)) {
      FREE(value);
      return SYSERR;
    }
    FREE(value);
    size = sizeof(DBlock);
  }
  /* append CHK */
  memcpy(&((char*)db)[size],
	 chk,
	 sizeof(CHK));
  iblocks[level]->size = htonl(size + 
			       sizeof(CHK) + 
			       sizeof(Datastore_Value));
  return OK;
}



/**
 * Undo sym-linking operation (if allowed by config): 
 * a) check if we have a symlink
 * b) delete symbolic link
 * c) copy file, if fails restore symlink
 */
static int undoSymlinking(const char * fn,
			  const HashCode160 * fileId,
			  GNUNET_TCP_SOCKET * sock) {
  EncName enc;
  char * serverDir;
  char * serverFN;
  char * tmpName;
  HashCode160 serverFileId;
  struct stat buf;
  int ret;

#ifndef S_ISLNK
  return OK; /* symlinks do not exist? */
#endif
  if (0 != lstat(fn,
		 &buf)) {
    LOG_FILE_STRERROR(LOG_ERROR, "stat", fn);
    return SYSERR;
  }
#ifdef S_ISLNK
  if (! S_ISLNK(buf.st_mode))
    return OK;
#endif
  serverDir 
    = getConfigurationOptionValue(sock,
				  "FS",
				  "INDEX-DIRECTORY");
  if (serverDir == NULL)
    return OK;
  serverFN = MALLOC(strlen(serverDir) + 2 + sizeof(EncName));
  strcpy(serverFN,
	 serverDir);
  FREE(serverDir);
  if (serverFN[strlen(serverFN)-1] != DIR_SEPARATOR)
    strcat(serverFN,
	   DIR_SEPARATOR_STR);
  hash2enc(fileId,
	   &enc);
  strcat(serverFN,
	 (char*)&enc);  
  tmpName = MALLOC(strlen(serverFN) + 5);
  ret = readlink(fn,
		 tmpName,
		 strlen(serverFN) + 4);
  if (ret == -1) {
    LOG_FILE_STRERROR(LOG_ERROR, "readlink", fn);
    FREE(tmpName);
    FREE(serverFN);
    return SYSERR;
  }
  if ( (ret == strlen(serverFN) + 4) ||
       (0 != strcmp(tmpName,
		    serverFN)) ) {
    FREE(tmpName);
    FREE(serverFN);
    return OK; /* symlink elsewhere... */
  }
  FREE(tmpName);
  if (OK != getFileHash(serverFN,
			&serverFileId)) {
    FREE(serverFN);
    return SYSERR;
  }
  if (! equalsHashCode160(&serverFileId,
			  fileId)) {
    FREE(serverFN);
    BREAK(); /* rather odd... */
    return SYSERR;
  }
  tmpName = MALLOC(strlen(fn) + 4);
  strcpy(tmpName, fn);
  strcat(tmpName, "_");
#ifdef HAVE_LINK
  if (0 != link(serverFN, tmpName)) 
#endif
    if (OK != copyFile(serverFN, tmpName)) {
      FREE(serverFN);
      FREE(tmpName);
      return SYSERR;
    }

  if (0 != UNLINK(fn)) {
    FREE(serverFN);
    FREE(tmpName);
    LOG_FILE_STRERROR(LOG_ERROR, "unlink", tmpName);
    return SYSERR;
  }
  
  if (0 != RENAME(tmpName,
		  fn)) {
    LOG_FILE_STRERROR(LOG_ERROR, "rename", tmpName);
    FREE(tmpName);
    FREE(serverFN);
    return SYSERR;
  }
  FREE(tmpName);
  FREE(serverFN);
  return OK;
}



/**
 * Unindex a file.
 *
 * @return SYSERR if the unindexing failed (i.e. not indexed)
 */
int ECRS_unindexFile(const char * filename,
		     ECRS_UploadProgressCallback upcb,
		     void * upcbClosure,
		     ECRS_TestTerminate tt,
		     void * ttClosure) {
  unsigned long long filesize;
  unsigned long long pos;
  unsigned int treedepth;
  int fd;
  int i;
  unsigned int size;
  Datastore_Value ** iblocks;
  Datastore_Value * dblock;
  DBlock * db;
  Datastore_Value * value;
  GNUNET_TCP_SOCKET * sock;
  HashCode160 fileId;
  CHK chk;
  cron_t eta;
  cron_t start;
  cron_t now;
  int wasIndexed;
  RequestTestindex rti;

  cronTime(&start);
  if (isDirectory(filename)) {
    BREAK();
    return SYSERR;
  }
  if (0 == assertIsFile(filename)) {
    BREAK();
    return SYSERR;
  }
  sock = getClientSocket();
  if (sock == NULL) 
    return SYSERR;  
  filesize = getFileSize(filename);
  eta = 0;
  if (upcb != NULL)
    upcb(filesize, 0, eta, upcbClosure);
  if (SYSERR == getFileHash(filename,
			    &fileId)) {
    releaseClientSocket(sock);
    return SYSERR;
  }
  cronTime(&now);
  eta = now + 2 * (now - start); 
  /* very rough estimate: hash reads once through the file,
     we'll do that once more and write it.  But of course
     the second read may be cached, and we have the encryption,
     so a factor of two is really, really just a rough estimate */
  start = now;
  /* reset the counter since the formula later does not
     take the time for getFileHash into account */  
  treedepth = computeDepth(filesize);

  /* Test if file is indexed! */
  rti.header.size
    = htons(sizeof(RequestTestindex));
  rti.header.type 
    = htons(AFS_CS_PROTO_TESTINDEX);
  rti.fileId = fileId;
  if (OK != writeToSocket(sock,
			  &rti.header)) {
    releaseClientSocket(sock);
    return SYSERR;
  }
  if (OK != readTCPResult(sock,
			  &wasIndexed)) {
    releaseClientSocket(sock);
    return SYSERR;
  }

#ifdef O_LARGEFILE
  fd = OPEN(filename, O_RDONLY | O_LARGEFILE);
#else
  fd = OPEN(filename, O_RDONLY);
#endif
  if (fd == -1) {
    LOG_FILE_STRERROR(LOG_WARNING, "OPEN", filename);
    return SYSERR;
  }
  dblock = MALLOC(sizeof(Datastore_Value) + DBLOCK_SIZE + sizeof(DBlock));
  dblock->size = htonl(sizeof(Datastore_Value) + DBLOCK_SIZE + sizeof(DBlock));
  dblock->anonymityLevel = htonl(0);
  dblock->prio = htonl(0);
  dblock->type = htonl(D_BLOCK);
  dblock->expirationTime = htonll(0);
  db = (DBlock*) &dblock[1];
  db->type = htonl(D_BLOCK);
  iblocks = MALLOC(sizeof(Datastore_Value*) * (treedepth+1));
  for (i=0;i<=treedepth;i++) {
    iblocks[i] = MALLOC(sizeof(Datastore_Value) + IBLOCK_SIZE + sizeof(DBlock));
    iblocks[i]->size = htonl(sizeof(Datastore_Value) + sizeof(DBlock));
    iblocks[i]->anonymityLevel = htonl(0);
    iblocks[i]->prio = htonl(0);
    iblocks[i]->type = htonl(D_BLOCK);
    iblocks[i]->expirationTime = htonll(0);
    ((DBlock*) &iblocks[i][1])->type = htonl(D_BLOCK);
  }

  pos = 0;
  while (pos < filesize) {
    if (upcb != NULL)
      upcb(filesize, pos, eta, upcbClosure);
    if (tt != NULL)
      if (OK != tt(ttClosure))
	goto FAILURE;
    size = DBLOCK_SIZE;
    if (size > filesize - pos) {
      size = filesize - pos;
      memset(&db[1],
	     0, 
	     DBLOCK_SIZE);
    }
    if (size != READ(fd, 
		     &db[1], 
		     size)) {
      LOG_FILE_STRERROR(LOG_WARNING,
			"READ", 
			filename);
      goto FAILURE;
    }   
    if (tt != NULL)
      if (OK != tt(ttClosure))
	goto FAILURE;
    fileBlockGetKey(db,
		    size + sizeof(DBlock),
		    &chk.key);
    fileBlockGetQuery(db,
		      size + sizeof(DBlock),
		      &chk.query);
    if (OK != pushBlock(sock,
			&chk,
			0, /* dblocks are on level 0 */
			iblocks))
      goto FAILURE;
    if (! wasIndexed) {
      fileBlockEncode(db,
		      size,
		      &chk.query,
		      &value);
      *value = *dblock; /* copy options! */
      if (OK != FS_delete(sock,
			  value)) {
	FREE(value);
	goto FAILURE;
      }
      FREE(value);
    }
    pos += size;
    cronTime(&now);
    eta = (cron_t) (start +
		    (((double)(now - start)/(double)pos)) 
		    * (double)filesize);
  }
  if (tt != NULL)
    if (OK != tt(ttClosure))
      goto FAILURE;  
  for (i=0;i<treedepth;i++) {
    size = ntohl(iblocks[i]->size) - sizeof(Datastore_Value);
    db = (DBlock*) &iblocks[i];
    fileBlockGetKey(db,
		    size + sizeof(DBlock),
		    &chk.key);
    fileBlockGetQuery(db,
		      size + sizeof(DBlock),
		      &chk.query);   
    if (OK != pushBlock(sock, 
			&chk,
			i+1, 
			iblocks))
      goto FAILURE;
    fileBlockEncode(db,
		    size,
		    &chk.query,
		    &value);
    if (OK != FS_delete(sock,
			value)) {
      FREE(value);
      goto FAILURE;
    }
    FREE(value);
    FREE(iblocks[i]);
    iblocks[i] = NULL;
  }
  
  if (wasIndexed) {
    if (OK == undoSymlinking(filename,
			     &fileId,
			     sock)) {
      if (OK != FS_unindex(sock,
			   DBLOCK_SIZE,
			   &fileId))
	goto FAILURE;
    } else
      goto FAILURE;
  }

  /* free resources */
  FREE(iblocks);
  FREE(dblock);
  CLOSE(fd);
  releaseClientSocket(sock);
  return OK;
 FAILURE:
  for (i=0;i<treedepth;i++)
    FREENONNULL(iblocks[i]);
  FREE(iblocks);
  FREE(dblock);
  CLOSE(fd);
  releaseClientSocket(sock);
  return SYSERR;
}

/* end of unindex.c */
