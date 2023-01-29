//
// Created by Sebastian on 10.12.2022.
//

#include "question_view.h"

static void on_next_button_clicked(GtkButton *btn) {
    g_print("Next button clicked");
}

static void on_answer_selected(GtkButton *btn, Answer *answer) {
//    gtk_window_set_title(win, "Quizy Informatyczne - Pytanie 2");
//    gtk_check_button_get_label(GTK_CHECK_BUTTON(btn));
    g_print("%d\n", gtk_check_button_get_inconsistent(GTK_CHECK_BUTTON(btn)));
    g_print("%s\n", gtk_check_button_get_label(GTK_CHECK_BUTTON(btn)));
}

static void *configure_radio_buttons(QuestionView *questionView) {
    RadioButtons *radioButtons = malloc(sizeof(RadioButtons));
    radioButtons->answerGroup = gtk_check_button_new();
    radioButtons->answer1 = set_radio_button("questionView->answers[0].answer", radioButtons->answerGroup, G_CALLBACK(on_answer_selected));
    radioButtons->answer2 = set_radio_button("questionView->answers[1].answer", radioButtons->answerGroup, G_CALLBACK(on_answer_selected));
    radioButtons->answer3 = set_radio_button("questionView->answers[2].answer", radioButtons->answerGroup, G_CALLBACK(on_answer_selected));
    radioButtons->answer4 = set_radio_button("questionView->answers[3].answer", radioButtons->answerGroup, G_CALLBACK(on_answer_selected));
    questionView->radioButtons = radioButtons;
}

static void *configure_next_button(GtkWidget *nextButton) {
    nextButton = gtk_button_new_with_label("Następne pytanie");
    gtk_widget_set_halign(nextButton, GTK_ALIGN_END);
    g_signal_connect (nextButton, "clicked", G_CALLBACK(on_next_button_clicked), NULL);
    return nextButton;
}

static GtkWidget *attach_buttons_on_view(GtkWidget *win, QuestionView *questionView) {
    GtkWidget *radioBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_widget_set_halign(radioBox, GTK_ALIGN_START);
    configure_radio_buttons(questionView);

    gtk_box_append(GTK_BOX (radioBox), questionView->radioButtons->answer1);
    gtk_box_append(GTK_BOX (radioBox), questionView->radioButtons->answer2);
    gtk_box_append(GTK_BOX (radioBox), questionView->radioButtons->answer3);
    gtk_box_append(GTK_BOX (radioBox), questionView->radioButtons->answer4);

    return radioBox;
}

static GtkWidget *set_label() {
    char *placeholderQuestionLong = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nulla finibus, justo in ornare tincidunt, orci nisl tincidunt lacus, euismod aliquet purus nulla at nisl. Nullam et sapien velit. Duis ligula metus, feugiat nec dui ac, pretium iaculis ex. Pellentesque tincidunt, ligula ac suscipit elementum, ligula nunc rutrum justo, a blandit ante ante id orci. Vestibulum id nunc tincidunt, egestas leo sit amet, blandit augue. Nam et metus enim. Vivamus ultricies ultricies eleifend. Integer scelerisque nisi risus, vitae sollicitudin nisi molestie in. Nulla ac eros porttitor, ullamcorper enim eu, congue neque. Aenean imperdiet urna ac leo consectetur, vitae faucibus dolor mollis. Etiam et faucibus elit. Ut at magna a risus facilisis tincidunt quis in enim. Nulla magna arcu, congue id tincidunt vitae, aliquet id leo.";
    GtkWidget *label = gtk_label_new(placeholderQuestionLong);
    gtk_label_set_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    return label;
}

GtkWidget *question_view_create(GApplication *app) {
    QuestionView *questionView = malloc(sizeof(QuestionView));
    questionView->answers = malloc(sizeof(Answer) * 4);
    GtkWidget *win, *mainContainerBox, *nextButton;

    win = setupApplicationWindow(GTK_APPLICATION(app), "Quizy Informatyczne - Pytanie 1/15");

    mainContainerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 40);

    gtk_window_set_child(GTK_WINDOW (win), mainContainerBox);
    gtk_widget_set_valign(mainContainerBox, GTK_ALIGN_CENTER);

    gtk_widget_set_margin_start(mainContainerBox, 20);
    gtk_widget_set_margin_end(mainContainerBox, 20);
    gtk_widget_set_margin_top(mainContainerBox, 20);
    gtk_widget_set_margin_bottom(mainContainerBox, 20);

    gtk_box_append(GTK_BOX (mainContainerBox), set_label());
    gtk_box_append(GTK_BOX(mainContainerBox), attach_buttons_on_view(win, questionView));
    gtk_box_append(GTK_BOX(mainContainerBox), configure_next_button(nextButton));

    return win;
}
