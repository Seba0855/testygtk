//
// Created by Sebastian on 29.01.2023.
//

#include "buttons.h"

GtkWidget *set_radio_button(char *label, GtkWidget *group, GCallback callback) {
    GtkWidget *button = gtk_check_button_new_with_label(label);
    gtk_check_button_set_group(GTK_CHECK_BUTTON(button), GTK_CHECK_BUTTON(group));
    g_signal_connect (button, "toggled", G_CALLBACK(callback), NULL);
    return button;
}
