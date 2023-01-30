//
// Created by Sebastian on 10.12.2022.
//

#ifndef PROJEKTTESTY_QUESTION_H
#define PROJEKTTESTY_QUESTION_H

#include <stdlib.h>

typedef struct Question {
    size_t id;
    char *question;
    char *answer1;
    char *answer2;
    char *answer3;
    char *answer4;
    int correctAnswer;
} Question;

#endif //PROJEKTTESTY_QUESTION_H
