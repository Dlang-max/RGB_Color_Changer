#include "gui.h"

void print_color(GtkWidget *widget, gpointer data) {
	GdkRGBA *color;
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(widget), color);
	
	u_int8_t red = (u_int8_t)(0xFF * color->red);
	u_int8_t green = (u_int8_t)(0xFF * color->green);
	u_int8_t blue = (u_int8_t)(0xFF * color->blue);

	send_color_packets(red, green, blue);
	printf("R: 0x%02x G: 0x%02x B: 0x%02x\n", red, green, blue);
}

void activate(GtkApplication *app, gpointer user_data) {
	GtkWidget *window;
	window = gtk_application_window_new (app);
  	gtk_window_set_title(GTK_WINDOW (window), "Color Chooser");
  	gtk_window_set_default_size(GTK_WINDOW (window), 500, 500);


	GtkWidget *chooser = gtk_color_chooser_widget_new();
	g_signal_connect(chooser, "notify::rgba", G_CALLBACK(print_color), chooser);

	gtk_window_set_child(GTK_WINDOW (window), chooser);
	gtk_window_present(GTK_WINDOW(window));
}

GtkApplication *initialize_gtk() {
	GtkApplication *app = gtk_application_new("gtk.color.chooser", G_APPLICATION_DEFAULT_FLAGS);
	g_signal_connect(app, "activate", G_CALLBACK (activate), NULL);

	return app;
}
