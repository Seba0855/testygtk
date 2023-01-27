#include "window.h"

GtkWidget* setupWindow(GtkApplication *app, char* title) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    return window;
}