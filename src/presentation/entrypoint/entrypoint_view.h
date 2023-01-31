#include <gtk/gtk.h>
#include "../common/ui_common.h"
#include "../question/question_view.h"

#ifndef PROJEKTTESTY_MENU_VIEW_H
#define PROJEKTTESTY_MENU_VIEW_H

static gchar *entrypoint_label = "Witamy w Quizie z wiedzy o informatyce.\n"
                                 "\n"
                                 "Program wyświetla 15 pytań jednokrotnego wyboru z dziedziny informatyki.\n"
                                 "Po ukończeniu testu program podliczy ilość poprawnych odpowiedzi.\n"
                                 "\n"
                                 "Kliknij poniższy przycisk by rozpocząć quiz.";

GtkWidget *entrypoint_create(GApplication *);

#endif //PROJEKTTESTY_MENU_VIEW_H
