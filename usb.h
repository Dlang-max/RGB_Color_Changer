#include <libusb-1.0/libusb.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

// Get using lsusb
#define VENDOR_ID 0x046d
#define PRODUCT_ID 0xc335

int send_usb_packet(libusb_device_handle *handle, u_int8_t bmRequestType, u_int8_t bRequest, u_int16_t wValue, u_int8_t wIndex, unsigned char *data, u_int16_t wLength);
int initialize_libusb(libusb_device_handle *handle);
int deinitialize_libusb(libusb_device_handle *handle);


