#include "tusb.h"
#include <string.h>
#include "disk_data.h"
#define BLOCK_COUNT 128u
#define BLOCK_SIZE 512u
void tud_msc_inquiry_cb(uint8_t lun, uint8_t vendor[8], uint8_t product[16], uint8_t rev[4]) {
    (void)lun; memcpy(vendor,"PICO    ",8); memcpy(product,"USB Storage     ",16); memcpy(rev,"1.0 ",4);
}
bool tud_msc_test_unit_ready_cb(uint8_t lun) { (void)lun; return true; }
void tud_msc_capacity_cb(uint8_t lun,uint32_t* count,uint16_t* size) { (void)lun; *count=BLOCK_COUNT; *size=BLOCK_SIZE; }
bool tud_msc_is_writable_cb(uint8_t lun) { (void)lun; return false; }
int32_t tud_msc_read10_cb(uint8_t lun,uint32_t lba,uint32_t offset,void* buffer,uint32_t size) {
    if(lba>=BLOCK_COUNT || offset>=BLOCK_SIZE || size>(BLOCK_COUNT-lba)*BLOCK_SIZE-offset) { tud_msc_set_sense(lun, SCSI_SENSE_ILLEGAL_REQUEST,0x21,0); return -1; }
    uint8_t* out=buffer; uint32_t remaining=size;
    while(remaining) {
        const uint8_t* sector = lba==0?boot:lba==1?fat:lba==2?root:lba==3?file_data:NULL;
        uint32_t n=BLOCK_SIZE-offset; if(n>remaining)n=remaining;
        if(sector)memcpy(out,sector+offset,n); else memset(out,0,n);
        out+=n; remaining-=n; lba++; offset=0;
    }
    return (int32_t)size;
}
int32_t tud_msc_write10_cb(uint8_t lun,uint32_t lba,uint32_t offset,uint8_t* buffer,uint32_t size) {
    (void)lba;(void)offset;(void)buffer;(void)size; tud_msc_set_sense(lun,SCSI_SENSE_DATA_PROTECT,0x27,0); return -1;
}
bool tud_msc_start_stop_cb(uint8_t lun,uint8_t power_condition,bool start,bool load_eject) { (void)lun;(void)power_condition;(void)start;(void)load_eject; return true; }
int32_t tud_msc_scsi_cb(uint8_t lun,uint8_t const cmd[16],void* buffer,uint16_t size) {
    (void)cmd;(void)buffer;(void)size; tud_msc_set_sense(lun,SCSI_SENSE_ILLEGAL_REQUEST,0x20,0); return -1;
}
