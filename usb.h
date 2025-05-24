#include <libusb-1.0/libusb.h>
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

// Get using lsusb
#define VENDOR_ID 0x046d
#define PRODUCT_ID 0xc335

int send_usb_packet(u_int8_t bmRequestType, u_int8_t bRequest, u_int16_t wValue, u_int8_t wIndex, unsigned char *data, u_int16_t wLength);
void send_misc_packet(unsigned char *prefix, unsigned char *data, u_int8_t start, u_int8_t end, u_int8_t red, u_int8_t green, u_int8_t blue); 
void send_color_packets(u_int8_t red, u_int8_t green,  u_int8_t blue);
int initialize_libusb();
int deinitialize_libusb();
