#include <gtk/gtk.h>

#include "ani-parser.h"
#include "ani-net.h"

typedef struct
{
    GPtrArray *result;

    GtkWidget *search_view;
    GtkListStore *store;
} CSearch;

typedef struct
{
    GtkWidget *window;
    GtkWidget *scrolled;

    GtkWidget *search_entry;

    GtkWidget *search_button;
    GtkWidget *reset_button;

    GtkWidget *spin_min;
    GtkWidget *spin_max;

    GtkWidget *category_box;

    GtkWidget *vbox;
    GtkWidget *hbox1;
    GtkWidget *hbox2;

    GtkWidget *search_label;
    GtkWidget *category_label;
    GtkWidget *size_min_label;
    GtkWidget *size_max_label;

    CSearch *csh;
} CWindow;

enum
{
    SIZE = 0,
    RELEASE_GROUP,
    EPISODE,
    QUALITY,
    CODEC,
    COLUMNS
};

static const gchar *column_names[] = {"Size", "Release Group", "Episode", "Quality", "Codec"};

static void destroy (GtkWidget *window, gpointer data);
static void search_init (CSearch *csh);
//static void search_update (CSearch *sch);

void create_window(void)
{
    CWindow *win;
    CSearch *csh;

    win = (CWindow*) g_malloc0 (sizeof (CWindow));
    csh = win->csh = (CSearch*) g_malloc0 (sizeof (CSearch));

    win->window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (win->window), "Ani");
    gtk_container_set_border_width (GTK_CONTAINER (win->window), 10);
    gtk_widget_set_size_request (win->window, 600, 400);

    g_signal_connect (G_OBJECT (win->window), "destroy", G_CALLBACK (destroy), NULL);

    csh->search_view = gtk_tree_view_new ();
    search_init (csh);
    csh->store = gtk_list_store_new (COLUMNS, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING, G_TYPE_STRING);

    gtk_tree_view_set_model (GTK_TREE_VIEW (csh->search_view), GTK_TREE_MODEL (csh->store));
    gtk_tree_view_set_enable_search (GTK_TREE_VIEW (csh->search_view), FALSE);
    g_object_unref (csh->store);

    win->search_label = gtk_label_new ("Anime Title:");
    win->size_min_label = gtk_label_new ("Torrent size (Min Mb):");
    win->size_max_label = gtk_label_new ("(Max Mb):");
    win->category_label = gtk_label_new ("Category:");

    win->search_entry = gtk_entry_new ();

    win->reset_button = gtk_button_new_from_stock (GTK_STOCK_CLEAR);
    win->search_button = gtk_button_new_from_stock (GTK_STOCK_FIND);

//    g_signal_connect (G_OBJECT (win->search_button), "clicked", G_CALLBACK (search_wrapper), (gpointer) csh);
//    g_signal_connect (G_OBJECT (win->reset_button), "clicked", G_CALLBACK (search_reset), (gpointer) csh);

    win->spin_max = gtk_spin_button_new_with_range (0, G_MAXUINT32, 1);
    win->spin_min = gtk_spin_button_new_with_range (0, G_MAXUINT32, 1);

    win->category_box = gtk_combo_box_new_text ();
    //Should be fixed!!
    gtk_combo_box_append_text (GTK_COMBO_BOX (win->category_box), "Anime");
    gtk_combo_box_append_text (GTK_COMBO_BOX (win->category_box), "Raws");

    win->hbox1 = gtk_hbox_new (FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->hbox1), win->search_label, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->hbox1), win->search_entry, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->hbox1), win->search_button, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->hbox1), win->category_label, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->hbox1), win->category_box, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->hbox1), win->reset_button, FALSE, FALSE, 5);

    win->hbox2 = gtk_hbox_new (FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->hbox2), win->size_min_label, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->hbox2), win->spin_min, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->hbox2), win->size_max_label, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->hbox2), win->spin_max, FALSE, FALSE, 5);

    win->scrolled = gtk_scrolled_window_new (NULL, NULL);
    gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (win->scrolled), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    
    gtk_container_add (GTK_CONTAINER (win->scrolled), win->csh->search_view);

    win->vbox = gtk_vbox_new (FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->vbox), win->hbox1, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->vbox), win->hbox2, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (win->vbox), win->scrolled, FALSE, FALSE, 5);

    gtk_container_add (GTK_CONTAINER (win->window), win->vbox);
    gtk_widget_show_all (win->window);

    gtk_main ();
}

static void destroy (GtkWidget *window, gpointer data)
{
    gtk_main_quit ();
}

//static void search_update (CSearch *sch)
//{
//    GtkTreeIter iter;
//    guint i;
//
//    GPtrArray *p_arr = sch->result;
//    GtkListStore *store = sch->store;
//
//    Anime *ani;
//
//    for (i = 0; i < p_arr->len; i++) {
//        ani = (Anime *)g_ptr_array_index (p_arr, i);
//        gtk_list_store_append (store, &iter);
//        gtk_list_store_set (store, &iter,
//                            SIZE, ani->size,
//                            RELEASE_GROUP, ani->release_group,
//                            EPISODE, ani->episode,
//                            QUALITY, ani->quality,
//                            CODEC, ani->codec, -1);
//    }
//}

static void search_init (CSearch *csh)
{
    GtkCellRenderer *renderer;
    GtkTreeViewColumn *column;

    guint i = SIZE;
    while (i != COLUMNS)
    {
        renderer = gtk_cell_renderer_text_new ();

        column = gtk_tree_view_column_new_with_attributes (column_names[i], renderer, "text", i, NULL);
        gtk_tree_view_column_set_resizable (column, TRUE);
        gtk_tree_view_column_set_reorderable (column, TRUE);
        gtk_tree_view_column_set_sort_indicator (column, TRUE);
        gtk_tree_view_column_set_sort_column_id (column, i);
        gtk_tree_view_append_column (GTK_TREE_VIEW (csh->search_view), column);

        i++;
    }
}

