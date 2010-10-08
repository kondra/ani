#include <gtk/gtk.h>
#include <glib.h>

#include "main-window.h"

int main (int argc, char *argv[])
{
    g_type_init ();
    gtk_init (&argc, &argv);

    create_window ();

    return 0;
}
