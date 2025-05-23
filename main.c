#include "gui.h"
#include "usb.h"

int main(int argc, char *argv[]) {
	// Initialize GTK
	GtkApplication *app = initialize_gtk();
	
	// Initialize LibUSB
	libusb_device_handle *handle = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
	if(handle == NULL) {
		perror("Error Opening Device\n");
	}
	initialize_libusb(handle);

	// Run the color picker
	g_application_run(G_APPLICATION(app), argc, argv);
	
	// Deinitialize GTK
	g_object_unref(app);
	// Deinitialize LibUSB
	deinitialize_libusb(handle);

	return 0;
}







