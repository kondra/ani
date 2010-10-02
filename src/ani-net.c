#include "ani-net.h"

const gchar *category_names[] = {"All", "Anime", "Music", "Manga", "Hentai", "Other", "", "Raws", "Drama", "Music Video"};

SoupMessage *request (const gchar *terms, guint type, gint min_size, gint max_size)
{
    SoupSession *session;
    SoupMessage *msg;

    guint status;

    session = soup_session_async_new ();

    if (max_size > 0 && min_size >= 0) {
        msg = soup_form_request_new ("GET", "http://tokyotosho.info/search.php",
                "terms", terms,
                "type", g_strdup_printf ("%d", type),
                "size_min", g_strdup_printf ("%d", min_size),
                "size_max", g_strdup_printf ("%d", max_size), 
                NULL);
    } else {
        msg = soup_form_request_new ("GET", "http://tokyotosho.info/search.php",
                "terms", terms,
                "type", g_strdup_printf ("%d", type),
                NULL);
    }

    status = soup_session_send_message (session, msg);

    return msg;
}
