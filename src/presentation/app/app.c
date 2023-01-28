#include "app.h"

void app_activate(GApplication *app, gpointer user_data) {
    GtkWidget *entryPoint = entrypoint_create(app);
    gtk_window_present(GTK_WINDOW(entryPoint));
}