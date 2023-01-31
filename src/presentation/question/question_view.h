//
// Created by Sebastian on 10.12.2022.
//

#ifndef PROJEKTTESTY_QUESTION_VIEW_H
#define PROJEKTTESTY_QUESTION_VIEW_H

#include <gtk/gtk.h>
#include "../common/ui_common.h"
#include "../../domain/usecase/get_question_usecase.h"
#include "../score/score_view.h"

typedef struct RadioButtons {
    GtkWidget *answerGroup;
    GtkWidget *answer1;
    GtkWidget *answer2;
    GtkWidget *answer3;
    GtkWidget *answer4;
} RadioButtons;

typedef struct QuestionView {
    GApplication *app;
    GtkWidget *questionLabel;
    Question *questionArray;
    RadioButtons *radioButtons;
    GtkWidget *nextButton;
    int correctAnswers;
    int currentQuestion;
} QuestionView;

GtkWidget *question_view_create(GApplication *);

#endif //PROJEKTTESTY_QUESTION_VIEW_H
