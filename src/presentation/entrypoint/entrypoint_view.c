//
// Created by Sebastian on 10.12.2022.
//

#include "entrypoint_view.h"

static void on_close_button_clicked(GtkButton *btn, GtkWindow *win) {
    gtk_window_destroy(win);
}

static void on_begin_button_clicked(GtkButton *btn, GApplication *app) {
    gtk_widget_show(question_view_create(app));
    gtk_window_destroy(GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(btn))));
}

static GtkWidget *set_label() {
    GtkWidget *label = gtk_label_new(entrypoint_label);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    return label;
}

static GtkWidget *configure_buttons_box(GtkWidget *win, GApplication *app) {
    GtkWidget *bottomBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    GtkWidget *btn, *closeButton;

    gtk_widget_set_halign(bottomBox, GTK_ALIGN_CENTER);

    btn = gtk_button_new_with_label("Rozpocznij test");
    g_signal_connect (btn, "clicked", G_CALLBACK(on_begin_button_clicked), app);

    closeButton = gtk_button_new_with_label("Zamknij");
    g_signal_connect (closeButton, "clicked", G_CALLBACK(on_close_button_clicked), win);

    gtk_box_append(GTK_BOX (bottomBox), closeButton);
    gtk_box_append(GTK_BOX (bottomBox), btn);

    return bottomBox;
}

GtkWidget *entrypoint_create(GApplication *app) {
    GtkWidget *win, *mainContainerBox;
    win = setupApplicationWindow(GTK_APPLICATION(app), "Quizy Informatyczne");

    mainContainerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_window_set_child(GTK_WINDOW (win), mainContainerBox);
    gtk_widget_set_valign(mainContainerBox, GTK_ALIGN_CENTER);

    gtk_box_append(GTK_BOX (mainContainerBox), set_label());
    gtk_box_append(GTK_BOX (mainContainerBox), configure_buttons_box(win, app));
    return win;
}