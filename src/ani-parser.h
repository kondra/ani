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

    gchar *release_group;
    gchar *quality;
    gchar *codec;

    guint episode;
    guint season;

    gchar *format;
} Anime;

GPtrArray *result_parser (const gchar *text, goffset length);
gint name_parser (Anime *ani);

#endif
