#include "ani-search.h"
#include "ani-parser.h"
#include "ani-net.h"

#include <gtk/gtk.h>

void progress (SoupMessage *msg, SoupBuffer *chunk, GtkProgressBar *bar)
{
    static gint count = 0;
    count ++;
    if (count > 10) count = 0;
    else return;

    gtk_progress_bar_pulse (bar);
}

GPtrArray *anime_search (const gchar *terms, guint type, gint min_size, gint max_size)
{
    SoupMessage *msg;

    GPtrArray *arr;
    GtkWidget *dialog;
    GtkWidget *bar, *content_area;

    bar = gtk_progress_bar_new ();
    gtk_progress_bar_set_pulse_step (GTK_PROGRESS_BAR (bar), 0.1);

    dialog = gtk_dialog_new ();
    gtk_dialog_set_has_separator (GTK_DIALOG (dialog), FALSE);
    gtk_window_set_position (GTK_WINDOW (dialog), GTK_WIN_POS_CENTER);
    gtk_widget_set_size_request (dialog, 400, 50);

    content_area = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
    g_signal_connect_swapped (G_OBJECT (dialog), "response", G_CALLBACK (gtk_widget_destroy), (gpointer) dialog);

    gtk_box_pack_start (GTK_BOX (content_area), bar, TRUE, TRUE, 5);
    gtk_widget_show_all (GTK_WIDGET (dialog));

    msg = request (terms, type, min_size, max_size, G_CALLBACK (progress), bar);
    arr = result_parser (msg->response_body->data, msg->response_body->length);

    gtk_widget_destroy (dialog);

    return arr;
}
