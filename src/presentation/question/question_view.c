//
// Created by Sebastian on 10.12.2022.
//

#include "question_view.h"

static void set_label(QuestionView *questionView) {
    GtkWidget *label = gtk_label_new(questionView->questionArray[questionView->currentQuestion].question);
    gtk_label_set_wrap(GTK_LABEL(label), TRUE);
    gtk_label_set_justify(GTK_LABEL(label), GTK_JUSTIFY_CENTER);
    questionView->questionLabel = label;
}

static void configure_radio_buttons(QuestionView *questionView) {
    RadioButtons *radioButtons = malloc(sizeof(RadioButtons));
    int currentQuestion = questionView->currentQuestion;

    radioButtons->answerGroup = gtk_check_button_new();
    radioButtons->answer1 = set_radio_button(questionView->questionArray[currentQuestion].answer1,
                                             radioButtons->answerGroup);
    radioButtons->answer2 = set_radio_button(questionView->questionArray[currentQuestion].answer2,
                                             radioButtons->answerGroup);
    radioButtons->answer3 = set_radio_button(questionView->questionArray[currentQuestion].answer3,
                                             radioButtons->answerGroup);
    radioButtons->answer4 = set_radio_button(questionView->questionArray[currentQuestion].answer4,
                                             radioButtons->answerGroup);
    questionView->radioButtons = radioButtons;
}

static void update_window_title(GtkWidget *win, QuestionView *questionView) {
    char *title = malloc(sizeof(char) * 100);
    sprintf(title, "Quizy Informatyczne - Pytanie %d/15", questionView->currentQuestion + 1);
    gtk_window_set_title(GTK_WINDOW(win), title);
    free(title);
}

static void update_radio_buttons(QuestionView *questionView) {
    int currentQuestion = questionView->currentQuestion;
    gtk_check_button_set_label(GTK_CHECK_BUTTON(questionView->radioButtons->answer1),
                               questionView->questionArray[currentQuestion].answer1);
    gtk_check_button_set_label(GTK_CHECK_BUTTON(questionView->radioButtons->answer2),
                               questionView->questionArray[currentQuestion].answer2);
    gtk_check_button_set_label(GTK_CHECK_BUTTON(questionView->radioButtons->answer3),
                               questionView->questionArray[currentQuestion].answer3);
    gtk_check_button_set_label(GTK_CHECK_BUTTON(questionView->radioButtons->answer4),
                               questionView->questionArray[currentQuestion].answer4);
}

static void next_question(GtkButton *btn, QuestionView *questionView) {
    if (questionView->currentQuestion <= 14) {
        if (questionView->currentQuestion == 14) {
            gtk_button_set_label(GTK_BUTTON(questionView->nextButton), "Zakończ test");
        }

        questionView->currentQuestion++;
        update_window_title((GtkWidget *) gtk_widget_get_root(GTK_WIDGET(btn)), questionView);
        gtk_label_set_text(GTK_LABEL(questionView->questionLabel),
                           questionView->questionArray[questionView->currentQuestion].question);
        update_radio_buttons(questionView);
    } else {
        gtk_widget_show(score_view_create(questionView->app, questionView->correctAnswers));
        gtk_window_destroy(GTK_WINDOW(gtk_widget_get_root(GTK_WIDGET(btn))));
    }
}

static void clear_button_selection(RadioButtons *radioButtons) {
    gtk_check_button_set_active(GTK_CHECK_BUTTON(radioButtons->answer1), FALSE);
    gtk_check_button_set_active(GTK_CHECK_BUTTON(radioButtons->answer2), FALSE);
    gtk_check_button_set_active(GTK_CHECK_BUTTON(radioButtons->answer3), FALSE);
    gtk_check_button_set_active(GTK_CHECK_BUTTON(radioButtons->answer4), FALSE);
}

static void check_correct_answer(QuestionView *questionView) {
    RadioButtons *radioButtons = questionView->radioButtons;
    if (gtk_check_button_get_active(GTK_CHECK_BUTTON(radioButtons->answer1))) {
        if (questionView->questionArray[questionView->currentQuestion].correctAnswer == 1) {
            questionView->correctAnswers++;
        }
    } else if (gtk_check_button_get_active(GTK_CHECK_BUTTON(radioButtons->answer2))) {
        if (questionView->questionArray[questionView->currentQuestion].correctAnswer == 2) {
            questionView->correctAnswers++;
        }
    } else if (gtk_check_button_get_active(GTK_CHECK_BUTTON(radioButtons->answer3))) {
        if (questionView->questionArray[questionView->currentQuestion].correctAnswer == 3) {
            questionView->correctAnswers++;
        }
    } else if (gtk_check_button_get_active(GTK_CHECK_BUTTON(radioButtons->answer4))) {
        if (questionView->questionArray[questionView->currentQuestion].correctAnswer == 4) {
            questionView->correctAnswers++;
        }
    }
    clear_button_selection(radioButtons);
}

static void on_next_button_clicked(GtkButton *btn, QuestionView *questionView) {
    check_correct_answer(questionView);
    next_question(btn, questionView);
}

static void *configure_next_button(QuestionView *questionView) {
    GtkWidget *nextButton = gtk_button_new_with_label("Następne pytanie");
    gtk_widget_set_halign(nextButton, GTK_ALIGN_END);
    g_signal_connect (nextButton, "clicked", G_CALLBACK(on_next_button_clicked), questionView);
    questionView->nextButton = nextButton;
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
    GtkWidget *win, *mainContainerBox;

    questionView->app = app;
    questionView->questionArray = get_question_array_execute(rowsRead);
    questionView->currentQuestion = 0;
    questionView->correctAnswers = 0;

    win = setupApplicationWindow(GTK_APPLICATION(app), "Quizy Informatyczne - Pytanie 1/15");

    mainContainerBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 40);

    gtk_window_set_child(GTK_WINDOW (win), mainContainerBox);
    gtk_widget_set_valign(mainContainerBox, GTK_ALIGN_CENTER);

    gtk_widget_set_margin_start(mainContainerBox, 20);
    gtk_widget_set_margin_end(mainContainerBox, 20);
    gtk_widget_set_margin_top(mainContainerBox, 20);
    gtk_widget_set_margin_bottom(mainContainerBox, 20);

    set_label(questionView);
    configure_next_button(questionView);
    gtk_box_append(GTK_BOX (mainContainerBox), questionView->questionLabel);
    gtk_box_append(GTK_BOX(mainContainerBox), attach_buttons_on_view(win, questionView));
    gtk_box_append(GTK_BOX(mainContainerBox), questionView->nextButton);

    return win;
}
