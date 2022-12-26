#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include "../question/question_view.h"

#ifndef PROJEKTTESTY_APP_H
#define PROJEKTTESTY_APP_H

#define PACKAGE_NAME "pl.smcebi.testify"
#define TESTIFY_APP_TYPE (tests_app_get_type ())

G_DECLARE_FINAL_TYPE (TestifyApp, testify_app, TESTIFY, APP, GtkApplication)

TestifyApp *testify_app_new(void);

#endif //PROJEKTTESTY_APP_H
