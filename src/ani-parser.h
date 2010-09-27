#ifndef __ANI_PARSER_INCLUDE__

#define __ANI_PARSER_INCLUDE__

#include <glib.h>

typedef struct
{
    guint id;
    gchar *uri;
    gchar *name;

    gchar *submitter;
    gchar *size;
    gchar *date;
    gchar *comment;
} Anime;

GPtrArray *parse (const gchar *text, goffset length);

#endif
