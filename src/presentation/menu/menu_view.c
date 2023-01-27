//
// Created by Sebastian on 10.12.2022.
//

#include "menu_view.h"

static void click_cb(GtkButton *btn, GtkWindow *win) {
    g_print("Clicked!\n");
    gtk_window_destroy(win);
}

GtkWidget* menu_view_create(GApplication *app) {
    GtkWidget *win;
    GtkWidget *lab;
    GtkWidget *btn;

    win = setupWindow(GTK_APPLICATION(app), "Quizy Informatyczne");

    lab = gtk_label_new("Hello.");
    gtk_window_set_child(GTK_WINDOW(win), lab);

    btn = gtk_button_new_with_label("Click me!");
    gtk_window_set_child(GTK_WINDOW(win), btn);
    g_signal_connect(btn, "clicked", G_CALLBACK(click_cb), NULL);

    gtk_window_present(GTK_WINDOW(win));
    return win;
}