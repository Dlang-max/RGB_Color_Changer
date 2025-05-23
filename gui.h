#include "gdk/gdk.h"
#include "gio/gio.h"
#include "glib-object.h"
#include <gtk/gtk.h>
#include <stdint.h>


void print_color(GtkWidget *widget, gpointer data);
void activate(GtkApplication *app, gpointer user_data);

GtkApplication *initialize_gtk();
