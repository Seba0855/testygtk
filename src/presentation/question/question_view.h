//
// Created by Sebastian on 10.12.2022.
//

#include <gtk/gtk.h>
#include "../common/ui_common.h"

#ifndef PROJEKTTESTY_QUESTION_VIEW_H
#define PROJEKTTESTY_QUESTION_VIEW_H

#include "../../domain/usecase/get_question_usecase.h"

typedef struct Answer {
    char *answer;
    int isCorrect;
} Answer;

typedef struct RadioButtons {
    GtkWidget *answerGroup;
    GtkWidget *answer1;
    GtkWidget *answer2;
    GtkWidget *answer3;
    GtkWidget *answer4;
} RadioButtons;

typedef struct QuestionView {
    GtkWidget *questionLabel;
    Answer *answers;
    RadioButtons *radioButtons;
    GtkWidget *nextButton;
} QuestionView;

GtkWidget *question_view_create(GApplication *);

#endif //PROJEKTTESTY_QUESTION_VIEW_H
