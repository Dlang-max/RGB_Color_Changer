#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>


#define VENDOR_ID 0x046d
#define PRODUCT_ID 0xc335

int main(int argc, char *argv[]) {
	// Initialize connection to usb device
	// Send USB HID packet containing color HEX
	if(libusb_init_context(NULL, NULL, 0) != 0) {
		perror("Error Initializing libusb");
	}


	// List of all USB devices
	libusb_device **devices;
	libusb_get_device_list(NULL, &devices);

	libusb_device *device;
	struct libusb_device_descriptor description;
	for(int i = 0; devices[i] != NULL; i++) {
		 device = devices[i];
		if(libusb_get_device_descriptor(device, &description) != 0) {
			perror("Error getting device description");
		}

		if(description.idVendor == VENDOR_ID &&
		   description.idProduct == PRODUCT_ID) {
			break;
		}
	}


	libusb_device_handle *handle;
	if(libusb_open(device, &handle) != 0) {
		perror("Error opening device");
	}

	


	libusb_close(handle);
	libusb_free_device_list(devices, 1);
	libusb_exit(NULL);

	return 0;
}
