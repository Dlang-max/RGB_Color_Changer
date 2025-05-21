#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>


void print_devices(libusb_device **devices) {
	
	libusb_device *device;
	uint8_t ports[8];
	
	int i = 0;
	while(devices[i] != NULL) {
		device = devices[i];
		struct libusb_device_descriptor description;
		if(libusb_get_device_descriptor(device, &description) != 0) {
			printf("Error\n");
			return;
		}

		printf("%04x:%04x bus: %d device: %d\n", description.idVendor, description.idProduct, libusb_get_bus_number(device), libusb_get_device_address(device));
	
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
