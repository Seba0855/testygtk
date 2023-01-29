#include "window.h"

GtkWidget *setupApplicationWindow(GtkApplication *app, char *title) {
    GtkWidget *window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    return window;
}

GtkWidget *setupNewWindow(char *title) {
    GtkWidget *window = gtk_window_new();
    gtk_window_set_title(GTK_WINDOW(window), title);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    return window;
}