#include "app.h"

struct _TestifyApp {
    GtkApplication parent;
};

G_DEFINE_TYPE(TestifyApp, testify, GTK_TYPE_APPLICATION);

static void testify_app_init(TestifyApp *app) {
}

static void preferences_activated(GSimpleAction *action,
                                  GVariant *parameter,
                                  gpointer app) {
    TestifyAppPrefs *prefs;
    GtkWindow *win;

    win = gtk_application_get_active_window(GTK_APPLICATION (app));
    prefs = testify_app_prefs_new(TESTIFY_APP_WINDOW(win));
    gtk_window_present(GTK_WINDOW (prefs));
}

static void quit_activated(GSimpleAction *action,
                           GVariant *parameter,
                           gpointer app) {
    g_application_quit(G_APPLICATION (app));
}

static GActionEntry app_entries[] =
        {
                {"preferences", preferences_activated, NULL, NULL, NULL},
                {"quit",        quit_activated,        NULL, NULL, NULL}
        };

static void
testify_app_startup(GApplication *app) {
    const char *quit_accels[2] = {"<Ctrl>Q", NULL};

    G_APPLICATION_CLASS (testify_app_parent_class)->startup(app);

    g_action_map_add_action_entries(G_ACTION_MAP (app),
                                    app_entries, G_N_ELEMENTS (app_entries),
                                    app);
    gtk_application_set_accels_for_action(GTK_APPLICATION (app),
                                          "app.quit",
                                          quit_accels);
}

static void testify_app_activate(GApplication *app) {
    TestifyAppWindow *win;

    win = testify_app_window_new(TESTIFY_APP(app));
    gtk_window_present(GTK_WINDOW (win));
}

static void testify_app_open(GApplication *app,
                             GFile **files,
                             int n_files,
                             const char *hint) {
    GList *windows;
    TestifyAppWindow *win;
    int i;

    windows = gtk_application_get_windows(GTK_APPLICATION (app));
    if (windows)
        win = TESTIFY_APP_WINDOW(windows->data);
    else
        win = testify_app_window_new(TESTIFY_APP(app));

    for (i = 0; i < n_files; i++)
        testify_app_window_open(win, files[i]);

    gtk_window_present(GTK_WINDOW (win));
}

static void testify_app_class_init(TestifyAppClass *class) {
    G_APPLICATION_CLASS (class)->startup = testify_app_startup;
    G_APPLICATION_CLASS (class)->activate = testify_app_activate;
    G_APPLICATION_CLASS (class)->open = testify_app_open;
}

TestifyApp *testify_app_new(void) {
    return g_object_new(TESTIFY_APP_TYPE,
                        "application-id", PACKAGE_NAME,
                        "flags", G_APPLICATION_HANDLES_OPEN,
                        NULL);
}
