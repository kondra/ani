#include <gtk/gtk.h>
#include <glib/gprintf.h>
#include <glib.h>

#include "ani-net.h"
#include "ani-parser.h"
#include "main-window.h"

int main (int argc, char *argv[])
{
    g_type_init ();

    SoupMessage *msg;
    GPtrArray *parr;

//    gint i;

//    Anime *ani;

    msg = request ("bakemonogatari", RAWS, 0, 0);

    parr = result_parser (msg->response_body->data, msg->response_body->length);

    gtk_init (&argc, &argv);

    create_window ();

//    for (i = 0; i < parr->len; i++) {
//        ani = (Anime *)g_ptr_array_index (parr, i);
//        name_parser (ani);
//        g_printf ("filename: %s\n", ani->name);
//        g_printf ("release group: %s\n", ani->release_group);
//        g_printf ("quality: %s\n", ani->quality);
//        g_printf ("codec: %s\n", ani->codec);
//        g_printf ("format: %s\n", ani->format);
//        g_printf ("episode: %d\n", ani->episode);
//        g_printf ("\n");
//    }

    return 0;
}
