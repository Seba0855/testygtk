#include "menu_view.h"

static void menu_view_init(MenuView *menu_view) {
}

static void menu_view_class_init(MenuViewClass *class) {
}

GtkWindow *display_menu_view(GtkApplication *app) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Menu");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    return GTK_WINDOW(window);
}
