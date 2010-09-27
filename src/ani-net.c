#include "ani-net.h"

SoupMessage *request (gchar *terms, gint type, gint min_size, gint max_size)
{
    const int debug_level = 2;

    SoupSession *session;
    SoupMessage *msg;

    guint status;

    session = soup_session_async_new ();

    if (debug_level) {
        SoupLogger *logger;

        logger = soup_logger_new (debug_level, -1);
        soup_session_add_feature (session, SOUP_SESSION_FEATURE (logger));
        g_object_unref (logger);
    }

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
