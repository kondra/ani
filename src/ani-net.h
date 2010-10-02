#ifndef __ANI_NET_INCLUDE__

#define __ANI_NET_INCLUDE__

#include <glib.h>
#include <libsoup/soup.h>

enum
{
    ALL = 0,
    ANIME,
    MUSIC,
    MANGA,
    HENTAI,
    OTHER,
    NONE,
    RAWS,
    CATEGORIES
};

gchar const *category_names[] = {"All", "Anime", "Music", "Manga", "Hentai", "Other", "", "Raws", "Drama", "Music Video"};

SoupMessage *request (const gchar *terms, guint type, gint min_size, gint max_size);

#endif
