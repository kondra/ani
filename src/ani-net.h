#ifndef __ANI_NET_INCLUDE__

#define __ANI_NET_INCLUDE__

#include <glib.h>
#include <libsoup/soup.h>

enum
{
    ALL = 0,
    ANIME = 1,
    RAWS = 7,
};

SoupMessage *request (gchar *terms, gint type, gint min_size, gint max_size);

#endif
