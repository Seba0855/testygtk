//
// Created by Sebastian on 10.12.2022.
//

#ifndef PROJEKTTESTY_MENU_VIEW_H
#define PROJEKTTESTY_MENU_VIEW_H

#include "../app/app.h"

struct _MenuView
{
    GtkApplicationWindow parent;
};

G_DEFINE_TYPE(MenuView, menu_view, GTK_TYPE_APPLICATION_WINDOW)

GtkWindow *display_menu_view(GtkApplication *app);
static void menu_view_init(MenuView*);
static void menu_view_class_init(MenuViewClass*);

#endif //PROJEKTTESTY_MENU_VIEW_H
