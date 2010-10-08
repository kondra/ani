#ifndef __ANI_SEARCH_INCLUDE__

#define __ANI_SEARCH_INCLUDE__

#include <glib.h>

#include "ani-net.h"
#include "ani-parser.h"

GPtrArray *anime_search (const gchar *terms, guint type, gint min_size, gint max_size);

#endif

