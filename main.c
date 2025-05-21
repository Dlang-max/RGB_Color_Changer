#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>


void print_devices(libusb_device **devices) {
	
	
	int i = 0;
	while(devices[i] != NULL) {
		libusb_device_handle *device_handle = NULL;
		struct libusb_device_descriptor description;
		libusb_device *device = devices[i];
		uint8_t ports[8];

		if(libusb_get_device_descriptor(device, &description) != 0) {
			printf("Error\n");
			return;
		}

		libusb_open(device, &device_handle);
		if(device_handle == NULL) {
			i++;
			continue;
		}

		unsigned char data[256];
		memset(data, '\0', sizeof(unsigned char) * 256);

		int length = libusb_get_string_descriptor_ascii(device_handle, description.iProduct, data, sizeof(unsigned char) * 256);
		printf("VendorId/ProductId %04x:%04x Bus: %d Device: %d Description: %s\n", description.idVendor, description.idProduct, 
	 		libusb_get_bus_number(device), libusb_get_device_address(device), data);
		libusb_close(device_handle);
		
		i++;
	}
}



int main(int argc, char *argv[]) {
	
	libusb_device **devices;
	
	if(libusb_init_context(NULL, NULL, 0) != 0) { 
		printf("Error initializing libusb\n");
		return 1;
	}

	int num_devices = libusb_get_device_list(NULL, &devices);	
	printf("Devices: %d\n", num_devices);

	print_devices(devices);

	libusb_free_device_list(devices, 1);
	libusb_exit(NULL);
		
	return 0;
}
