//
// Created by Sebastian on 10.12.2022.
//

#include "question_view.h"

static void set_label(QuestionView *questionView) {
    GtkWidget *label = gtk_label_new(questionView->questionArray[questionView->currentQuestion - 1].question);
    gtk_label_set_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    questionView->questionLabel = label;
}

static void on_answer_selected(GtkButton *btn, Answer *answer) {
//    gtk_window_set_title(win, "Quizy Informatyczne - Pytanie 2");
//    gtk_check_button_get_label(GTK_CHECK_BUTTON(btn));
    g_print("%d\n", gtk_check_button_get_inconsistent(GTK_CHECK_BUTTON(btn)));
    g_print("%s\n", gtk_check_button_get_label(GTK_CHECK_BUTTON(btn)));
}

static void configure_radio_buttons(QuestionView *questionView) {
    RadioButtons *radioButtons = malloc(sizeof(RadioButtons));
    int currentQuestion = questionView->currentQuestion - 1;

    radioButtons->answerGroup = gtk_check_button_new();
    radioButtons->answer1 = set_radio_button(questionView->questionArray[currentQuestion].answer1,
                                             radioButtons->answerGroup, G_CALLBACK(on_answer_selected));
    radioButtons->answer2 = set_radio_button(questionView->questionArray[currentQuestion].answer2,
                                             radioButtons->answerGroup, G_CALLBACK(on_answer_selected));
    radioButtons->answer3 = set_radio_button(questionView->questionArray[currentQuestion].answer3,
                                             radioButtons->answerGroup, G_CALLBACK(on_answer_selected));
    radioButtons->answer4 = set_radio_button(questionView->questionArray[currentQuestion].answer4,
                                             radioButtons->answerGroup, G_CALLBACK(on_answer_selected));
    questionView->radioButtons = radioButtons;
}

static void update_window_title(GtkWidget *win, QuestionView *questionView) {
    char *title = malloc(sizeof(char) * 100);
    sprintf(title, "Quizy Informatyczne - Pytanie %d/15", questionView->currentQuestion);
    gtk_window_set_title(GTK_WINDOW(win), title);
    free(title);
}

static void update_radio_buttons(QuestionView *questionView) {
    int currentQuestion = questionView->currentQuestion - 1;
    gtk_check_button_set_label(GTK_CHECK_BUTTON(questionView->radioButtons->answer1),
                               questionView->questionArray[currentQuestion].answer1);
    gtk_check_button_set_label(GTK_CHECK_BUTTON(questionView->radioButtons->answer2),
                               questionView->questionArray[currentQuestion].answer2);
    gtk_check_button_set_label(GTK_CHECK_BUTTON(questionView->radioButtons->answer3),
                               questionView->questionArray[currentQuestion].answer3);
    gtk_check_button_set_label(GTK_CHECK_BUTTON(questionView->radioButtons->answer4),
                               questionView->questionArray[currentQuestion].answer4);
}

static void on_next_button_clicked(GtkButton *btn, QuestionView *questionView) {
    if (questionView->currentQuestion < 15) {
        questionView->currentQuestion++;
        update_window_title((GtkWidget *) gtk_widget_get_root(GTK_WIDGET(btn)), questionView);
        gtk_label_set_text(GTK_LABEL(questionView->questionLabel), questionView->questionArray[questionView->currentQuestion - 1].question);
        update_radio_buttons(questionView);
    }
}

static void *configure_next_button(GtkWidget *nextButton, QuestionView *questionView) {
    nextButton = gtk_button_new_with_label("Następne pytanie");
    gtk_widget_set_halign(nextButton, GTK_ALIGN_END);
    g_signal_connect (nextButton, "clicked", G_CALLBACK(on_next_button_clicked), questionView);
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

GtkWidget *question_view_create(GApplication *app) {
    QuestionView *questionView = malloc(sizeof(QuestionView));
    size_t *rowsRead = malloc(sizeof(size_t));
    GtkWidget *win, *mainContainerBox, *nextButton;

    questionView->questionArray = get_question_array_execute(rowsRead);
    questionView->currentQuestion = 1;

    win = setupApplicationWindow(GTK_APPLICATION(app), "Quizy Informatyczne - Pytanie 1/15");

    mainContainerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 40);

    gtk_window_set_child(GTK_WINDOW (win), mainContainerBox);
    gtk_widget_set_valign(mainContainerBox, GTK_ALIGN_CENTER);

    gtk_widget_set_margin_start(mainContainerBox, 20);
    gtk_widget_set_margin_end(mainContainerBox, 20);
    gtk_widget_set_margin_top(mainContainerBox, 20);
    gtk_widget_set_margin_bottom(mainContainerBox, 20);

    set_label(questionView);
    gtk_box_append(GTK_BOX (mainContainerBox), questionView->questionLabel);
    gtk_box_append(GTK_BOX(mainContainerBox), attach_buttons_on_view(win, questionView));
    gtk_box_append(GTK_BOX(mainContainerBox), configure_next_button(nextButton, questionView));

    return win;
}
