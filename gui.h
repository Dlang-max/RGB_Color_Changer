#include "gdk/gdk.h"
#include "gio/gio.h"
#include "glib-object.h"
#include <gtk/gtk.h>
#include <stdint.h>

static void print_color(GtkWidget *widget, gpointer data);
static void activate(GtkApplication *app, gpointer user_data);
int main(int argc, char *argv[]);
