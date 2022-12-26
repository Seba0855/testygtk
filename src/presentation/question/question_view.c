#include "question_view.h"

GtkWindow *display_question_view(GtkApplication *app,
                                 const char *question,
                                 const char *answer1,
                                 const char *answer2,
                                 const char *answer3,
                                 const char *answer4) {
    GtkWidget *window;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *grid;

    /* Create a new window */
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), question);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);

    /* Create a grid to arrange the widgets */
    grid = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_append(GTK_BOX(grid), gtk_label_new(question));

    /* Create the widgets */
    button1 = gtk_button_new_with_label(answer1);
    button2 = gtk_button_new_with_label(answer2);
    button3 = gtk_button_new_with_label(answer3);
    button4 = gtk_button_new_with_label(answer4);

    /* Arrange the widgets in the grid */
    gtk_box_append(GTK_BOX(grid), button1);
    gtk_box_append(GTK_BOX(grid), button2);
    gtk_box_append(GTK_BOX(grid), button3);
    gtk_box_append(GTK_BOX(grid), button4);

    /* Show the window and its components */
    gtk_window_set_child(GTK_WINDOW(window), grid);
    gtk_window_present(GTK_WINDOW(window));
}