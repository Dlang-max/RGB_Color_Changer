#include "gui.h"
#include "usb.h"

int main(int argc, char *argv[]) {
	// Initialize GTK
	GtkApplication *app = initialize_gtk();
	
	// Initialize LibUSB
	initialize_libusb();

	// Run the color picker
	g_application_run(G_APPLICATION(app), argc, argv);
	
	// Deinitialize GTK
	g_object_unref(app);
	// Deinitialize LibUSB
	deinitialize_libusb();

	return 0;
}







