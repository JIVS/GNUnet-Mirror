/*
     This file is part of GNUnet.
     (C) 2001, 2002, 2003, 2004, 2006 Christian Grothoff (and other contributing authors)

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
 * @file applications/fs/fsui/search.c
 * @brief Helper functions for searching.  FSUI search performs the
 *   filtering of duplicate results as well as adding boolean search
 *   (ANDing).
 * @author Christian Grothoff
 */

#include "platform.h"
#include "gnunet_directories.h"
#include "gnunet_protocols.h"
#include "gnunet_fsui_lib.h"
#include "gnunet_uritrack_lib.h"
#include "gnunet_namespace_lib.h"
#include "fsui.h"

#define DEBUG_SEARCH NO

/* must match namespace_info.c */
#define NS_ROOTS "data" DIR_SEPARATOR_STR "namespace-root" DIR_SEPARATOR_STR

/**
 * Pass the result to the client and note it as shown.
 */
static void processResult(const ECRS_FileInfo * fi,
			  FSUI_SearchList * pos) {
  FSUI_Event event;

  GROW(pos->resultsReceived,
       pos->sizeResultsReceived,
       pos->sizeResultsReceived+1);
  pos->resultsReceived[pos->sizeResultsReceived-1].uri
    = ECRS_dupUri(fi->uri);
  pos->resultsReceived[pos->sizeResultsReceived-1].meta
    = ECRS_dupMetaData(fi->meta);

  event.type = FSUI_search_result;
  event.data.SearchResult.sc.pos = pos;
  event.data.SearchResult.sc.cctx = pos->cctx;
  event.data.SearchResult.fi = *fi;
  event.data.SearchResult.searchURI = pos->uri;
  pos->ctx->ecb(pos->ctx->ecbClosure,
		&event);
}

static void setNamespaceRoot(struct GE_Context * ectx,
			     struct GC_Configuration * cfg,
			     const ECRS_FileInfo * fi) {
  char * fn;
  char * fnBase;
  HashCode512 ns;
  char * name;

  if (OK != ECRS_getNamespaceId(fi->uri,
				&ns)) {
    GE_BREAK(ectx, 0);
    return;
  }
  name = ECRS_getNamespaceName(&ns);
  GC_get_configuration_value_string(cfg,
				    "GNUNET",
				    "GNUNET_HOME",
				    GNUNET_HOME_DIRECTORY,
				    &fnBase);
  fn = MALLOC(strlen(fnBase) +
	      strlen(NS_ROOTS) +
	      strlen(name) +
	      6);
  strcpy(fn, fnBase);
  strcat(fn, DIR_SEPARATOR_STR);
  strcat(fn, NS_ROOTS);
  disk_directory_create(ectx, fn);
  strcat(fn, DIR_SEPARATOR_STR);
  strcat(fn, name);
  FREE(name);
  FREE(fnBase);
  if (OK == ECRS_getSKSContentHash(fi->uri,
				   &ns)) {
    disk_file_write(ectx,
		    fn,
		    &ns,
		    sizeof(HashCode512),
		    "644");
  }
  FREE(fn);
}

/**
 * Process results found by ECRS.
 */
static int spcb(const ECRS_FileInfo * fi,
		const HashCode512 * key,
		int isRoot,
		void * cls) {
  FSUI_SearchList * pos = cls;
  unsigned int i;
  unsigned int j;
  ResultPending * rp;
  struct GE_Context * ectx;

  ectx = pos->ctx->ectx;

  URITRACK_trackURI(ectx,
		    pos->ctx->cfg,
		    fi);
  if (isRoot) {
    setNamespaceRoot(ectx,
		     pos->ctx->cfg,
		     fi);
    NS_addNamespaceInfo(ectx,
			pos->ctx->cfg,
			fi->uri,
			fi->meta);
    return OK;
  }
  for (i=0;i<pos->sizeResultsReceived;i++)
    if (ECRS_equalsUri(fi->uri,
		       pos->resultsReceived[i].uri)) {
#if DEBUG_SEARCH
      GE_LOG(ectx, GE_DEBUG | GE_REQUEST | GE_USER,
	  "Received search result that I have seen before.\n");
#endif
      return OK; /* seen before */
    }
  if (pos->numberOfURIKeys > 1) {
    if (key == NULL) {
      GE_BREAK(ectx, 0);
#if DEBUG_SEARCH
      GE_LOG(ectx, GE_DEBUG | GE_REQUEST | GE_USER,
	  "Received search result without key to decrypt.\n");
#endif
      return SYSERR;
    }
    for (i=0;i<pos->sizeUnmatchedResultsReceived;i++) {
      rp = &pos->unmatchedResultsReceived[i];
      if (ECRS_equalsUri(fi->uri,
			 rp->fi.uri)) {
	for (j=0;j<rp->matchingKeyCount;j++)
	  if (0 == memcmp(key,
			  &rp->matchingKeys[j],
			  sizeof(HashCode512))) {
#if DEBUG_SEARCH
	    GE_LOG(ectx, GE_DEBUG | GE_REQUEST | GE_USER,
		"Received search result that I have seen before (missing keyword to show client).\n");
#endif
	    return OK;
	  }
	if (rp->matchingKeyCount + 1 == pos->numberOfURIKeys) {
#if DEBUG_SEARCH
	  GE_LOG(ectx, GE_DEBUG | GE_REQUEST | GE_USER,
	      "Received search result (showing client)!\n");
#endif
	  GROW(rp->matchingKeys,
	       rp->matchingKeyCount,
	       0);
	  processResult(&rp->fi,
			pos);
	  ECRS_freeUri(rp->fi.uri);
	  ECRS_freeMetaData(rp->fi.meta);
	  pos->unmatchedResultsReceived[i]
	    = pos->unmatchedResultsReceived[pos->sizeUnmatchedResultsReceived-1];
	  GROW(pos->unmatchedResultsReceived,
	       pos->sizeUnmatchedResultsReceived,
	       pos->sizeUnmatchedResultsReceived-1);
	  return OK;
	} else {
	  GROW(rp->matchingKeys,
	       rp->matchingKeyCount,
	       rp->matchingKeyCount+1);
	  rp->matchingKeys[rp->matchingKeyCount-1] = *key;
#if DEBUG_SEARCH
	  GE_LOG(ectx, GE_DEBUG | GE_REQUEST | GE_USER,
	      "Received search result (waiting for more %u keys before showing client).\n",
	      pos->numberOfURIKeys - rp->matchingKeyCount);
#endif
	  return OK;
	}	
      }
    }
    GROW(pos->unmatchedResultsReceived,
	 pos->sizeUnmatchedResultsReceived,
	 pos->sizeUnmatchedResultsReceived+1);
    rp = &pos->unmatchedResultsReceived[pos->sizeUnmatchedResultsReceived-1];
    rp->fi.meta = ECRS_dupMetaData(fi->meta);
    rp->fi.uri = ECRS_dupUri(fi->uri);
    rp->matchingKeys = NULL;
    rp->matchingKeyCount = 0;
    GROW(rp->matchingKeys,
	 rp->matchingKeyCount,
	 1);
    rp->matchingKeys[0] = *key;
#if DEBUG_SEARCH
    GE_LOG(ectx, GE_DEBUG | GE_REQUEST | GE_USER,
	"Received search result (waiting for %u more keys before showing client).\n",
	pos->numberOfURIKeys  - rp->matchingKeyCount);
#endif
    return OK;
  } else {
#if DEBUG_SEARCH
    GE_LOG(ectx, GE_DEBUG | GE_REQUEST | GE_USER,
	"Received search result (showing client)!\n");
#endif
    processResult(fi,
		  pos);
  }
  return OK;
}

static int testTerminate(void * cls) {
  FSUI_SearchList * pos = cls;
  if ( (pos->state == FSUI_ACTIVE) &&
       (pos->maxResults > pos->sizeResultsReceived) )
    return OK;
  return SYSERR;
}

/**
 * Thread that searches for data.
 */
void * FSUI_searchThread(void * cls) {
  FSUI_SearchList * pos = cls;
  FSUI_Event event;
  int ret;

  ret = ECRS_search(pos->ctx->ectx,
		    pos->ctx->cfg,
		    pos->uri,
		    pos->anonymityLevel,
		    pos->timeout,
		    &spcb,
		    pos,
		    &testTerminate,
		    pos);
  if (ret != OK) {
    pos->state = FSUI_ERROR;
    event.type = FSUI_search_error;
    event.data.SearchError.sc.pos = pos;
    event.data.SearchError.sc.cctx = pos->cctx;
    event.data.SearchError.message = _("Error running search (consult logs).");
    pos->ctx->ecb(pos->ctx->ecbClosure,
		  &event);
  } else if (pos->state == FSUI_ABORTED) {
    event.type = FSUI_search_aborted;
    event.data.SearchAborted.sc.pos = pos;
    event.data.SearchAborted.sc.cctx = pos->cctx;
    pos->ctx->ecb(pos->ctx->ecbClosure,
		  &event);
  } else if (pos->state == FSUI_ACTIVE) {
    pos->state = FSUI_COMPLETED;
    event.type = FSUI_search_completed;
    event.data.SearchCompleted.sc.pos = pos;
    event.data.SearchCompleted.sc.cctx = pos->cctx;
    pos->ctx->ecb(pos->ctx->ecbClosure,
		  &event);
  } else {
    GE_ASSERT(NULL, pos->state == FSUI_PENDING);
    /* must be suspending */
  }

  return NULL;
}

/**
 * Thread that searches for data (and signals startup).
 */
void * FSUI_searchThreadSignal(void * cls) {
  FSUI_SearchList * pos = cls;
  FSUI_Event event;

  event.type = FSUI_search_started;
  event.data.SearchStarted.sc.pos = pos;
  event.data.SearchStarted.sc.cctx = NULL;
  event.data.SearchStarted.searchURI = pos->uri;
  event.data.SearchStarted.anonymityLevel = pos->anonymityLevel;
  pos->cctx = pos->ctx->ecb(pos->ctx->ecbClosure,
			    &event);
  return FSUI_searchThread(pos);
}

/**
 * Start a search.
 */
struct FSUI_SearchList *
FSUI_startSearch(struct FSUI_Context * ctx,
		 unsigned int anonymityLevel,
		 unsigned int maxResults,
		 cron_t timeout,
		 const struct ECRS_URI * uri) {
  FSUI_SearchList * pos;
  struct GE_Context * ectx;

  ectx = ctx->ectx;
  MUTEX_LOCK(ctx->lock);
  pos = MALLOC(sizeof(FSUI_SearchList));
  pos->maxResults = maxResults;
  pos->state = FSUI_ACTIVE;
  pos->uri = ECRS_dupUri(uri);
  pos->numberOfURIKeys = ECRS_countKeywordsOfUri(uri);
  pos->sizeResultsReceived = 0;
  pos->resultsReceived = NULL;
  pos->sizeUnmatchedResultsReceived = 0;
  pos->unmatchedResultsReceived = 0;
  pos->anonymityLevel = anonymityLevel;
  pos->ctx = ctx;
  pos->start_time = get_time();
  pos->timeout = timeout;
  pos->handle = PTHREAD_CREATE(&FSUI_searchThreadSignal,
			       pos,
			       32 * 1024);
  if (pos->handle == NULL) {
    GE_LOG_STRERROR(ectx,
		    GE_ERROR | GE_IMMEDIATE | GE_USER | GE_ADMIN,
		    "PTHREAD_CREATE");
    ECRS_freeUri(pos->uri);
    FREE(pos);
    MUTEX_UNLOCK(ctx->lock);
    return NULL;
  }
  pos->next = ctx->activeSearches;
  ctx->activeSearches = pos;
  MUTEX_UNLOCK(ctx->lock);
  return pos;
}

/**
 * Abort a search.
 */
int FSUI_abortSearch(struct FSUI_Context * ctx,
		     struct FSUI_SearchList * sl) {
  if (sl->state == FSUI_PENDING) {
    sl->state = FSUI_ABORTED_JOINED;
    return OK;
  }
  if (sl->state != FSUI_ACTIVE) 
    return SYSERR;
  sl->state = FSUI_ABORTED;
  PTHREAD_STOP_SLEEP(sl->handle);  
  return OK;
}

/**
 * Stop a search.
 */
int FSUI_stopSearch(struct FSUI_Context * ctx,
		    struct FSUI_SearchList * sl) {
  FSUI_Event event;
  FSUI_SearchList * pos;
  FSUI_SearchList * prev;
  void * unused;
  int i;

  MUTEX_LOCK(ctx->lock);
  prev = NULL;
  pos = ctx->activeSearches;
  while ( (pos != sl) &&
	  (pos != NULL) ) {
    prev = pos;
    pos = pos->next;
  }
  if (pos == NULL) {
    MUTEX_UNLOCK(ctx->lock);
    return SYSERR;
  }
  if (prev == NULL)
    ctx->activeSearches = pos->next;
  else
    prev->next = pos->next;
  MUTEX_UNLOCK(ctx->lock);
  pos->next = NULL;
  if ( (pos->state == FSUI_COMPLETED) ||
       (pos->state == FSUI_ABORTED) ||
       (pos->state == FSUI_ERROR) ) {
    PTHREAD_JOIN(pos->handle,
		 &unused);
    pos->state++; /* add _JOINED */
  }
  event.type = FSUI_search_stopped;
  event.data.SearchStopped.sc.pos = pos;
  event.data.SearchStopped.sc.cctx = pos->cctx;
  pos->ctx->ecb(pos->ctx->ecbClosure,
		&event);


  ECRS_freeUri(pos->uri);
  for (i=0;i<pos->sizeResultsReceived;i++) {
    ECRS_freeUri(pos->resultsReceived[i].uri);
    ECRS_freeMetaData(pos->resultsReceived[i].meta);
  }
  GROW(pos->resultsReceived,
       pos->sizeResultsReceived,
       0);
  for (i=0;i<pos->sizeUnmatchedResultsReceived;i++) {
    ECRS_freeUri(pos->unmatchedResultsReceived[i].fi.uri);
    ECRS_freeMetaData(pos->unmatchedResultsReceived[i].fi.meta);
    GROW(pos->unmatchedResultsReceived[i].matchingKeys,
	 pos->unmatchedResultsReceived[i].matchingKeyCount,
	 0);
  }
  GROW(pos->unmatchedResultsReceived,
       pos->sizeUnmatchedResultsReceived,
       0);
  FREE(pos);
  return OK;
}

/* end of search.c */
