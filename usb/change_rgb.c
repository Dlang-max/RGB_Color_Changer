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
			perror("Error getting device description\n");
		}

		if(description.idVendor == VENDOR_ID &&
		   description.idProduct == PRODUCT_ID) {
			printf("Found Keyboard\n");
			break;
		}
	}

	libusb_device_handle *handle;
	if(libusb_open(device, &handle) != 0) {
		perror("Error opening device\n");
	}
	
	libusb_set_auto_detach_kernel_driver(handle, 1);
	
	int claim = libusb_claim_interface(handle, 1);
	if(claim != 0) {
		switch(claim) {
			case LIBUSB_ERROR_NOT_FOUND:
			printf("No Interface\n");
			break;

			case LIBUSB_ERROR_BUSY:
			printf("Busy\n");
			break;

			case LIBUSB_ERROR_NO_DEVICE:
			printf("No Device\n");
			break;

			default:
			break;
		}
	}


	unsigned char bytes[] = {0x12, 0xff, 0xf, 0x3f, 0x0, 0x1, 0x0, 0xe, 0x4, 0xff, 0xff, 0xff, 0x5, 0xff, 0xff, 0xff, 0x6, 0xff, 0xff, 0xff, 0x7, 0xff, 0x00, 0x00, 0x8, 0xff, 0xff, 0xff, 0x9, 0xff, 0xff, 0xff, 0xa, 0xff, 0xff, 0xff, 0xb, 0xff, 0xff, 0xff, 0xc, 0xff, 0xff, 0xff, 0xd, 0xff, 0xff, 0xff, 0xe, 0xff, 0xff, 0xff, 0xf, 0xff, 0x00, 0x00, 0x10, 0xff, 0xff, 0xff, 0x1e, 0x80, 0x00, 0x80};
	int transfered = libusb_control_transfer(handle, 0x21, 0x09, 0x0212, 0x01, bytes, 0x0040, 100);
	printf("%s\n", libusb_error_name(transfered));
	printf("Transfered: %d\n", transfered);

	unsigned char final[] = {0x11, 0xff, 0xf, 0x5f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	transfered = libusb_control_transfer(handle, 0x21, 0x09, 0x0211, 0x01, final, 0x0014, 100);
	printf("%s\n", libusb_error_name(transfered));
	printf("Transfered: %d\n", transfered);

	
	libusb_release_interface(handle, 1);
	libusb_close(handle);
	libusb_free_device_list(devices, 1);
	libusb_exit(NULL);

	return 0;
}
