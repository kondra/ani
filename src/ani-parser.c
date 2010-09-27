#include "ani-parser.h"

GPtrArray *parse (const gchar *text, goffset length)
{
    GPtrArray *parr = g_ptr_array_new ();

    gchar *cur = g_strstr_len (text, length, "<table class=\"listing\">");

    GRegex *regex, *regex_top, *regex_bot;
    GMatchInfo *match_info;

    GError *err = NULL;

    Anime *ani;

    regex = g_regex_new ("<tr\\ class=\"", 0, 0, &err);
    if (err) {
        g_critical ("%s\n", err->message);
        return NULL;
    }

    regex_top = g_regex_new ("<td\\ class=\"desc-top\">.*\"(.*)\">(.*)<\\/a><\\/td><td.*details\\.php\\?id=(\\d*)", 0, 0, &err);
    if (err) {
        g_critical ("%s\n", err->message);
        return NULL;
    }

    regex_bot = g_regex_new ("<td\\ class=\"desc-bot\">Submitter: (.*) \\| Size: (.*) \\| Date: (.*) \\| Comment: (.*)<\\/td><td", 0, 0, &err);
    if (err) {
        g_critical ("%s\n", err->message);
        return NULL;
    }

    gchar **res = g_regex_split (regex, cur, 0);
    while (*res != NULL) {
        ani = (Anime*) g_malloc0 (sizeof (Anime));

        g_regex_match (regex_top, *res, 0, &match_info);
        if (g_match_info_matches (match_info)) {
            ani->uri = g_match_info_fetch (match_info, 1);
            ani->name = g_match_info_fetch (match_info, 2);
            gchar *buf = g_match_info_fetch (match_info, 3);
            ani->id = g_ascii_strtoull (buf, NULL, 10);
            g_free (buf);

            //            g_debug ("%s", ani->uri);
            //            g_debug ("%s", ani->name);
            //            g_debug ("%d", ani->id);

            g_match_info_free (match_info);
            res++;
        } else
            g_match_info_free (match_info);

        if (res == NULL)
            break;

        g_regex_match (regex_bot, *res, 0, &match_info);
        if (g_match_info_matches (match_info)) {
            ani->submitter = g_match_info_fetch (match_info, 1);
            ani->size = g_match_info_fetch (match_info, 2);
            ani->date = g_match_info_fetch (match_info, 3);
            ani->comment = g_match_info_fetch (match_info, 4);

            //            g_debug ("%s", ani->submitter);
            //            g_debug ("%s", ani->size);
            //            g_debug ("%s", ani->date);
            //            g_debug ("%s\n", ani->comment);

            g_match_info_free (match_info);
            res++;
        } else {
            g_match_info_free (match_info);
            res++;
        }

        g_ptr_array_add (parr, (gpointer) ani);
    }

    g_regex_unref (regex);
    g_regex_unref (regex_top);
    g_regex_unref (regex_bot);

    return parr;
}
