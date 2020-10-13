#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "at24cx.h"

#define AT24C_ADDR  (0x50)

int8_t usr_i2c_write(const uint8_t busAddr, const uint8_t *data, const uint32_t len) {
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    // Transmit the data to the specified device from the provided
    // data buffer.

    return ret;
}

int8_t usr_i2c_read(const uint8_t busAddr, uint8_t *data, const uint32_t len) {
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    // Received the specified amount of data from the device and store it
    // in the data buffer

    return ret;
}

void usr_delay_us(uint32_t period) {
    // Delay for the requested period
}

int main(void) {
    at24cx_return_code_t ret = AT24Cx_RET_OK;
    uint8_t ex_buff[AT24CX_MAX_PAGE_SIZE] = {0};

    // Create an instance of our at24cx device
    at24cx_dev_t dev;

    // Store the Device ID in our new device instance
    dev.id = AT24Cx_DEV_512;

    // Provide the hardware abstraction functions for
    // I2c Read/Write and a micro-second delay function
    dev.intf.i2c_addr = AT24C_ADDR;
    dev.intf.write = usr_i2c_write;
    dev.intf.read = usr_i2c_read;
    dev.intf.delay_us = usr_delay_us;

    // Print out the size info of our part
    printf("Device Capacity: %d bytes\n", at24cx_dev_size[dev.id].capacity);
    printf("Number of pages: %d pages\n", at24cx_dev_size[dev.id].num_pages);
    printf("Page size: %d bytes\n", at24cx_dev_size[dev.id].page_size);

    // Erase the EEPROM
    for(uint8_t i = 0; i < at24cx_dev_size[dev.id].num_pages; i++) {
        at24cx_erase(&dev, at24cx_dev_size[dev.id].page_size * i, at24cx_dev_size[dev.id].page_size);
    }

    // Write all zeros to the EEPROM
    memset(ex_buff, 0x00, at24cx_dev_size[dev.id].page_size);
    for(uint8_t i = 0; i < at24cx_dev_size[dev.id].num_pages; i++) {
        at24cx_write(&dev, at24cx_dev_size[dev.id].page_size * i, ex_buff, at24cx_dev_size[dev.id].page_size);
    }

    // Read all of the data back
    for(uint8_t i = 0; i < at24cx_dev_size[dev.id].num_pages; i++) {
        at24cx_read(&dev, at24cx_dev_size[dev.id].page_size * i, ex_buff, at24cx_dev_size[dev.id].page_size);
    }

    return 0;
}