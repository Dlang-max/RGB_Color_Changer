#include "gui.h"

static void print_color(GtkWidget *widget, gpointer data) {
	GdkRGBA *color;
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(widget), color);
	uint8_t red = (uint8_t)(0xFF * color->red);
	uint8_t green = (uint8_t)(0xFF * color->green);
	uint8_t blue = (uint8_t)(0xFF * color->blue);

	g_print("R: 0x%02x G: 0x%02x B: 0x%02x\n", red, green, blue);
	g_print("R: %d G: %d B: %d\n", red, green, blue);
}

static void activate(GtkApplication *app, gpointer user_data) {
	GtkWidget *window;
	window = gtk_application_window_new (app);
  	gtk_window_set_title(GTK_WINDOW (window), "Color Chooser");
  	gtk_window_set_default_size(GTK_WINDOW (window), 500, 500);


	GtkWidget *chooser = gtk_color_chooser_widget_new();
	g_signal_connect(chooser, "notify::rgba", G_CALLBACK(print_color), chooser);

	gtk_window_set_child(GTK_WINDOW (window), chooser);
	gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[]) {
	GtkApplication *app;
	app = gtk_application_new("gtk.color.chooser", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);
	int status = g_application_run(G_APPLICATION (app), argc, argv);
	g_object_unref(app);

	return status;
}
