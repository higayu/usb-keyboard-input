#include "tusb.h"
#include <string.h>
static const tusb_desc_device_t device = {
 .bLength=sizeof(tusb_desc_device_t), .bDescriptorType=TUSB_DESC_DEVICE,
 .bcdUSB=0x0200, .bMaxPacketSize0=CFG_TUD_ENDPOINT0_SIZE,
 .idVendor=0xCAFE, .idProduct=0x4002, .bcdDevice=0x0100,
 .iManufacturer=1, .iProduct=2, .bNumConfigurations=1
};
uint8_t const* tud_descriptor_device_cb(void) { return (uint8_t const*)&device; }
static const uint8_t config[] = {
 TUD_CONFIG_DESCRIPTOR(1, 1, 0, TUD_CONFIG_DESC_LEN+TUD_MSC_DESC_LEN, 0, 100),
 TUD_MSC_DESCRIPTOR(0, 0, 0x01, 0x81, 64)
};
uint8_t const* tud_descriptor_configuration_cb(uint8_t index) { (void)index; return config; }
uint16_t const* tud_descriptor_string_cb(uint8_t index, uint16_t langid) {
 (void)langid; static uint16_t buf[32];
 static const char* strings[]={"", "Pico Lab", "Pico USB Storage"};
 if(index==0) { buf[0]=0x0304; buf[1]=0x0409; return buf; }
 if(index>=3) return NULL;
 size_t n=strlen(strings[index]); if(n>31) n=31;
 for(size_t i=0;i<n;i++) buf[i+1]=(uint8_t)strings[index][i];
 buf[0]=(uint16_t)(0x0300 | (2*n+2)); return buf;
}
