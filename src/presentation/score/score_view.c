//
// Created by Sebastian on 10.12.2022.
//

#include "score_view.h"

static void on_close_button_clicked(GtkButton *btn, GtkWindow *win) {
    gtk_window_destroy(win);
}

static GtkWidget *set_label(char *message) {
    GtkWidget *label = gtk_label_new(message);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    return label;
}

static GtkWidget *configure_buttons_box(GtkWidget *win, GApplication *app) {
    GtkWidget *bottomBox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    GtkWidget *closeButton;

    gtk_widget_set_halign(bottomBox, GTK_ALIGN_CENTER);

    closeButton = gtk_button_new_with_label("Zakończ");
    g_signal_connect (closeButton, "clicked", G_CALLBACK(on_close_button_clicked), win);

    gtk_box_append(GTK_BOX (bottomBox), closeButton);

    return bottomBox;
}

GtkWidget *score_view_create(GApplication *app, int correctAnswers) {
    GtkWidget *win, *mainContainerBox;
    win = setupApplicationWindow(GTK_APPLICATION(app), "Quizy Informatyczne - wynik");

    mainContainerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_window_set_child(GTK_WINDOW (win), mainContainerBox);
    gtk_widget_set_valign(mainContainerBox, GTK_ALIGN_CENTER);

    char *scoreMessage = malloc(100);
    sprintf(scoreMessage, "Twój wynik to: %d/15", correctAnswers);

    gtk_box_append(GTK_BOX (mainContainerBox), set_label("Gratulacje, ukończyłeś test!"));
    gtk_box_append(GTK_BOX (mainContainerBox), set_label(scoreMessage));
    gtk_box_append(GTK_BOX (mainContainerBox), configure_buttons_box(win, app));
    return win;
}