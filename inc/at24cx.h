/*! @file at24cx.h
 * @brief Public header file for the AT24Cx 2-Wire Serial EEPROM ICs
 */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _AT24CX_H_
#define _AT24CX_H_

#include <stdint.h>

#define AT24CX_MAX_PAGE_SIZE    (256) /*! @brief Max EEPROM page size in bytes */

/*!
 * @brief This function pointer API reads I2C data from the specified
 * device on the bus.
 *
 * @param[in] busAddr: Address of the device to be read from
 * @param[out] *data: Pointer to the where we should store the read data
 * @param[in] len: Length of data to be read
 *
 * @return The result of reading I2C data
 */
typedef int8_t(*at24cx_read_fptr_t)(const uint8_t busAddr, uint8_t *data, const uint32_t len);

/*!
 * @brief This function pointer API writes I2C data to the specified
 * device on the bus.
 *
 * @param[in] busAddr: Address of the device to be written to
 * @param[in] *data: Pointer to the data to be written
 * @param[in] len: Length of data to be written
 *
 * @return The result of writing I2C data
 */
typedef int8_t(*at24cx_write_fptr_t)(const uint8_t busAddr, const uint8_t *data, const uint32_t len);

/*!
 * @brief This function pointer API delays for the specified time in microseconds.
 *
 * @param[in] period: Duration to be delayed in micro-seconds
 */
typedef void(*at24cx_delay_us_fptr_t)(uint32_t period);

/*!
 * @brief AT24Cx Return codes for the driver API
 */
typedef enum {
    AT24Cx_RET_OK          = 0,    /* OK */
    AT24Cx_RET_ERROR       = -1,   /* Error */
    AT24Cx_RET_BUSY        = -2,   /* Interface Busy */
    AT24Cx_RET_TIMEOUT     = -3,   /* Timeout */
    AT24Cx_RET_INV_PARAM   = -4,   /* Invalid Parameter */
    AT24Cx_RET_NULL_PTR    = -5,   /* NULL Pointer */
} at24cx_return_code_t;

/*!
 * @brief AT24Cx Supported Memory ICs
 */
typedef enum {
    AT24Cx_DEV_32 = 0x00,           /* AT24C32 */
    AT24Cx_DEV_64,                  /* AT24C64 */
    AT24Cx_DEV_128,                 /* AT24C128 */
    AT24Cx_DEV_256,                 /* AT24C256 */
    AT24Cx_DEV_512,                 /* AT24C512 */
    AT24Cx_DEV__MAX__
} at24cx_device_t;

/*!
 * @brief AT24Cx max page size
 */
typedef struct {
    uint32_t capacity;              /* Device capacity in bytes */
    uint16_t num_pages;             /* Number of pages in the memory */
    uint16_t page_size;             /* Device page size in bytes */
} at24cx_device_size_t;

/*!
 * @brief AT24Cx HW Interface
 */
typedef struct {
    uint8_t i2c_addr;                  /* Device I2C Address */
    at24cx_read_fptr_t read;           /* User I2C Read Function Pointer */
    at24cx_write_fptr_t write;         /* User I2C Write Function Pointer */
    at24cx_delay_us_fptr_t delay_us;   /* User Micro-Second Delay Function Pointer */
} at24cx_dev_intf_t;

/*!
 * @brief AT24Cx Device Instance
 */
typedef struct
{
    at24cx_dev_intf_t intf;         /* Device Hardware Interface */
    at24cx_device_t id;             /* PN/Type of EEPROM */
} at24cx_dev_t;

/*!
 * @brief This API erases the requested number of bytes from the provided
 * memory address
 *
 * @param[in] *dev: Pointer to the device instance containing the i2c
 * interface to erase from
 * @param[in] addr: Memory address to begin erasing from
 * @param[in] len: Number of bytes to erase
 *
 * @return The result of erasing the EEPROM
 */
at24cx_return_code_t at24cx_erase(at24cx_dev_t *dev, const uint16_t addr, const uint16_t len);

/*!
 * @brief This API writes data to the requested address
 *
 * @param[in] *dev: Pointer to the device instance containing the i2c
 * interface to write to
 * @param[in] addr: Memory address to write to
 * @param[in] *data: Pointer to the data to be written
 * @param[in] len: Number of bytes to write
 *
 * @return The result of writing data to the EEPROM
 */
at24cx_return_code_t at24cx_write(at24cx_dev_t *dev, const uint16_t addr, const uint8_t *data, const uint16_t len);

/*!
 * @brief This API reads data from the requested address
 *
 * @param[in] *dev: Pointer to the device instance containing the i2c
 * interface to read from
 * @param[in] addr: Memory address to read from
 * @param[in] *data: Pointer to where to store the read data
 * @param[in] len: Number of bytes to read
 *
 * @return The result of reading data from the EEPROM
 */
at24cx_return_code_t at24cx_read(at24cx_dev_t *dev, const uint16_t addr, uint8_t *data, const uint16_t len) ;

/*!
 * @brief AT24Cx Device Page Sizes
 */
extern const at24cx_device_size_t at24cx_dev_size[AT24Cx_DEV__MAX__];

#endif // _AT24CX_H_

#ifdef __cplusplus
}
#endif