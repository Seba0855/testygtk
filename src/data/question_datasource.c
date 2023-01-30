//
// Created by Sebastian on 10.12.2022.
//

#include "question_datasource.h"

int countLines(FILE *file) {
    char buf[65536];
    int counter = 0;

    printf("Counting lines in file\n");

    for (;;) {
        printf("Counting lines: inf loop start\n");
        size_t res = fread(buf, 1, 65536, file);
        if (ferror(file))
            return -1;

        int i;
        for (i = 0; i < res; i++) {
            if (buf[i] == '\n') {
                // printf("Counting lines: Found %dth newline\n", counter+1); // overkill
                counter++;
            }
        }

        if (feof(file))
            break;
    }
    fseek(file, 0, SEEK_SET);
    printf("Counting lines: END! Found %d lines \n", counter);
    return counter;
}

Question *checkLine(char *str, size_t next_id) {
    char question[300 + 1];
    char answer1[100 + 1];
    char answer2[100 + 1];
    char answer3[100 + 1];
    char answer4[100 + 1];
    int correctAnswer;

    if (sscanf(str, "%300[^;];%100[^;];%100[^;];%100[^;];%100[^;];%d", question, answer1, answer2, answer3, answer4,
               &correctAnswer) != 6) {
        printf("sscanf reading failed\n\n");
        return NULL;
    }
    printf("Checking line: Read nazwa: \"%s\", Odpowiedź 1: \"%s\" dobre=%d\n", question, answer1, correctAnswer);
    if (question[0] != '\0') {
        Question *newLine = malloc(sizeof(Question));
        newLine->question = malloc(strlen(question) + 1);
        newLine->answer1 = malloc(strlen(answer1) + 1);
        newLine->answer2 = malloc(strlen(answer2) + 1);
        newLine->answer3 = malloc(strlen(answer3) + 1);
        newLine->answer4 = malloc(strlen(answer4) + 1);
        if (newLine->question == NULL) {
            printf("Memory allocation failed\n\n");
            return NULL;
        }
        strcpy(newLine->question, question);
        strcpy(newLine->answer1, answer1);
        strcpy(newLine->answer2, answer2);
        strcpy(newLine->answer3, answer3);
        strcpy(newLine->answer4, answer4);
        newLine->correctAnswer = correctAnswer;
        // printf("Checking line: Created newLine struct - nazwa: \"%s\", ilosc=%d, wartosc=%f\n",
        //         newLine->nazwa, newLine->ilosc, newLine->wartosc);
        return newLine;
    }
    return NULL;
}

Question *createStructsFromFile(FILE *filestream, size_t fileLength, size_t *rowsRead) {
    printf("Create struct from file: start\n");
    Question *js = malloc(fileLength * sizeof(Question));
    Question *currentItem = malloc(sizeof(Question));
    size_t failed = 0;
    size_t j = 0;
    unsigned int buffer_size = 1000;

    for (size_t i = 0; i < fileLength; i++) {
        char buffer[buffer_size];
        // printf("start pętli %zd\n", i);
        fgets(buffer, buffer_size, filestream);
        if ((currentItem = checkLine(buffer, j)) != NULL) {
            currentItem->id = j;

            printf("createStructsFromFile: before assignment currentItem[%zd] (%s) to js[%zd]\n",
                   i, currentItem->question, j);

            js[j] = *currentItem;

            printf("createStructsFromFile: inserted %zdth struct\n\n", j);
            currentItem = (Question *) malloc(sizeof(Question));
            j++;
        } else
            failed++;  // TODO
    }
    printf("Create struct from file: END\n");
    *rowsRead = j;
    printf("rowsRead = %zd", *rowsRead);
    printf("Create struct from file: Finished creating, failed reading %zd / %zd lines\n", failed, fileLength);
    return js;
}

Question *get_question_structures_array(size_t *rowsRead) {
    FILE *filestream = fopen("question_database.csv", "r");
    int fileLength = countLines(filestream);
    if (fileLength <= 0)
        return NULL;

    Question *structuresArray;
    structuresArray = createStructsFromFile(filestream, fileLength, rowsRead);

    fclose(filestream);
    return structuresArray;
}

