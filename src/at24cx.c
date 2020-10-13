/*! @file at24cx.c
 * @brief Driver source for the AT24Cx 2-Wire Serial EEPROM ICs
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "at24cx.h"

/*!
 * @brief AT24Cx Device Page Sizes
 */
const at24cx_device_size_t at24cx_dev_size[AT24Cx_DEV__MAX__] = {
    { .capacity = 4096, .num_pages = 128, .page_size = 32 },    // AT24C32
    { .capacity = 8192, .num_pages = 256, .page_size = 32 },    // AT24C64
    { .capacity = 16384, .num_pages = 256, .page_size = 64 },   // AT24C128
    { .capacity = 32768, .num_pages = 512, .page_size = 64 },   // AT24C256
    { .capacity = 65536, .num_pages = 512, .page_size = 128 },  // AT24C512
};

/*!
 * @brief This API erases the requested number of bytes from the provided
 * memory address
 */
at24cx_return_code_t at24cx_erase(at24cx_dev_t *dev, const uint16_t addr, const uint16_t len) {
    at24cx_return_code_t ret = AT24Cx_RET_OK;
    uint8_t buff[AT24CX_MAX_PAGE_SIZE] = {0xFF};
    uint16_t address = 0x0000;

    // Verify all of the parameters are OK
    if( NULL == dev) {
        ret = AT24Cx_RET_NULL_PTR;
    }
    else if((dev->id >= AT24Cx_DEV__MAX__) ||
            (len > at24cx_dev_size[dev->id].page_size) ||
            (0x00 == len) )
    {
        ret = AT24Cx_RET_INV_PARAM;
    }

    // Zero out the length instructed
    if( AT24Cx_RET_OK == ret ) {
        address = ((addr >> 8) & 0x00FF) | ((addr << 8) & 0xFF00);
        memcpy(&buff[0], &address, 2);
        memset(&buff[2], 0xFF, len);

        // Write the data
        ret = dev->intf.write((dev->intf.i2c_addr << 1), buff, len + 2);
    }

    return ret;
}

/*!
 * @brief This API writes data to the requested address
 */
at24cx_return_code_t at24cx_write(at24cx_dev_t *dev, const uint16_t addr, const uint8_t *data, const uint16_t len) {
    at24cx_return_code_t ret = AT24Cx_RET_OK;
    uint8_t buff[AT24CX_MAX_PAGE_SIZE] = {0xFF};
    uint16_t address = 0x0000;

    // Verify all of the parameters are OK
    if( (NULL == dev) || (NULL == data) ) {
        ret = AT24Cx_RET_NULL_PTR;
    }
    else if((dev->id >= AT24Cx_DEV__MAX__) ||
            (len > at24cx_dev_size[dev->id].page_size) ||
            (0x00 == len) )
    {
        ret = AT24Cx_RET_INV_PARAM;
    }

    // Write the data provided
    if( AT24Cx_RET_OK == ret ) {
        address = ((addr >> 8) & 0x00FF) | ((addr << 8) & 0xFF00);
        memcpy(&buff[0], &address, 2);
        memcpy(&buff[2], data, len);

        // Write the data
        ret = dev->intf.write((dev->intf.i2c_addr << 1), buff, len + 2);
    }

    return ret;
}

/*!
 * @brief This API reads data from the requested address
 */
at24cx_return_code_t at24cx_read(at24cx_dev_t *dev, const uint16_t addr, uint8_t *data, const uint16_t len) {
    at24cx_return_code_t ret = AT24Cx_RET_OK;
    uint8_t buff[AT24CX_MAX_PAGE_SIZE] = {0xFF};
    uint16_t address = 0x0000;

    // Verify all of the parameters are OK
    if( (NULL == dev) || (NULL == data) ) {
        ret = AT24Cx_RET_NULL_PTR;
    }
    else if((dev->id >= AT24Cx_DEV__MAX__) ||
            (len > at24cx_dev_size[dev->id].page_size) ||
            (0x00 == len) )
    {
        ret = AT24Cx_RET_INV_PARAM;
    }

    // Read the data from the requested address
    if( AT24Cx_RET_OK == ret ) {
        address = ((addr >> 8) & 0x00FF) | ((addr << 8) & 0xFF00);
        memcpy(&buff[0], &address, 2);

        // Transmit the address we would like to read from
        ret = dev->intf.write((dev->intf.i2c_addr << 1), buff, 0x02);
    }

    if( AT24Cx_RET_OK == ret ) {
        // Receive the data requested
        ret = dev->intf.read((dev->intf.i2c_addr << 1) | 0x01, data, len);
    }

    return ret;
}

