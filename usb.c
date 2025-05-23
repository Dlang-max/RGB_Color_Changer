#include "usb.h"
#include <libusb-1.0/libusb.h>
#include <unistd.h>

libusb_device_handle *handle = NULL;

int send_usb_packet(u_int8_t bmRequestType, u_int8_t bRequest, u_int16_t wValue, u_int8_t wIndex, unsigned char *data, u_int16_t wLength) {
	int transfered = libusb_control_transfer(handle, bmRequestType, bRequest, wValue, wIndex, data, wLength, 500);
	printf("Bytes Transfered: %d\n", transfered);
	if(transfered < 0) {
		printf("%s\n", libusb_error_name(transfered));
	}

	return transfered;
}


void send_color_packets(u_int8_t red, u_int8_t green, u_int8_t blue) {
	libusb_claim_interface(handle, 1);

	u_int8_t elementsPerPacket = ((64 - 8) / 4);
	unsigned char data[64] = {0x12, 0xff, 0xf, 0x3f, 0x0, 0x1, 0x0, 0xe};
	for(u_int8_t i = 0x01; i <= 0xE7; i++)  {
			
		int index = 8 + 4 * ((i - 1) % elementsPerPacket);
		data[index] = i;
		data[index + 1] = red;
		data[index + 2] = green;
		data[index + 3] = blue;

		// Time to send a packet
		if(i % elementsPerPacket == 0) {
			send_usb_packet(0x21, 0x09, 0x0212, 0x01, data, 0x0040);
			usleep(1000);
		}

	}
	send_usb_packet(0x21, 0x09, 0x0212, 0x01, data, 0x0040);	

	// Send the final USBHID packet
	unsigned char final[20] = {0x11, 0xff, 0xf, 0x5f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
	send_usb_packet(0x21, 0x09, 0x0211, 0x01, final, 0x0014);
	libusb_release_interface(handle, 1);

}

int initialize_libusb() {
	libusb_init_context(NULL, NULL, 0);

	handle = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
	if(handle == NULL) {
		perror("Error Opening Device\n");
		return 1;
	}

	// Detach Kernel Driver so we can actually write to USB device
	if(libusb_set_auto_detach_kernel_driver(handle, 1) != LIBUSB_SUCCESS) {
		perror("Issue auto detaching kernel driver\n");
		return 1;
	}
	
	// Claim USB device
	//int claim = libusb_claim_interface(handle, 1);
	//if(claim != 0) {
	//	switch(claim) {
	//		case LIBUSB_ERROR_NOT_FOUND:
	//		perror("No Interface\n");
	//		break;

	//		case LIBUSB_ERROR_BUSY:
	//		perror("Busy\n");
	//		break;

	//		case LIBUSB_ERROR_NO_DEVICE:
	//		perror("No Device\n");
	//		break;

	//		default:
	//		break;
	//	}

	//	return 1;
	//}

	return 0;
}

int deinitialize_libusb() {
	// libusb_release_interface(handle, 1);
	libusb_close(handle);
	libusb_exit(NULL);

	return 0;
}
