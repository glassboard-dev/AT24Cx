#include "unity.h"
#include "at24cx.h"

int8_t usr_i2c_write(const uint8_t busAddr, const uint8_t *data, const uint32_t len);
int8_t usr_i2c_read(const uint8_t busAddr, uint8_t *data, const uint32_t len);
void usr_delay_us(uint32_t period);

at24cx_dev_t at24cx_device;

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

void setUp(void)
{
    // Store the Device ID in our new device instance
    at24cx_device.id = AT24Cx_DEV_512;

    // Provide the hardware abstraction functions for
    // I2c Read/Write and a micro-second delay function
    at24cx_device.intf.i2c_addr = 0x50;
    at24cx_device.intf.write = usr_i2c_write;
    at24cx_device.intf.read = usr_i2c_read;
    at24cx_device.intf.delay_us = usr_delay_us;
}

void tearDown(void)
{
}

/**************** ERASE *************************************/
void test_at24cx_erase_AllValid(void)
{
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    ret = at24cx_erase(&at24cx_device, 0x00, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_OK, ret);
}

void test_at24cx_erase_NullDevice(void)
{
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    ret = at24cx_erase(NULL, 0x00, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_NULL_PTR, ret);
}

void test_at24cx_erase_InvalidDeviceId(void)
{
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    at24cx_device.id = AT24Cx_DEV__MAX__;

    ret = at24cx_erase(&at24cx_device, 0x00, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_INV_PARAM, ret);
}

void test_at24cx_erase_EraseLengthTooLarge(void)
{
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    // Set the erase size 1 byte larger than our devices page size and attempt an erase
    ret = at24cx_erase(&at24cx_device, 0x00, at24cx_dev_size[at24cx_device.id].page_size+1);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_INV_PARAM, ret);
}

void test_at24cx_erase_EraseLengthIsZero(void)
{
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    // Set the erase size to zero
    ret = at24cx_erase(&at24cx_device, 0x00, 0x00);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_INV_PARAM, ret);
}

void test_at24cx_erase_NullWriteIntf(void)
{
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    at24cx_device.intf.write = NULL;

    ret = at24cx_erase(&at24cx_device, 0x00, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_NULL_PTR, ret);
}

/**************** WRITE *************************************/
void test_at24cx_write_AllValid(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    ret = at24cx_write(&at24cx_device, 0x00, buff, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_OK, ret);
}

void test_at24cx_write_NullDevice(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    ret = at24cx_write(NULL, 0x00, buff, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_NULL_PTR, ret);
}

void test_at24cx_write_NullDataBuffer(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    ret = at24cx_write(&at24cx_device, 0x00, NULL, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_NULL_PTR, ret);
}

void test_at24cx_write_NullWriteIntf(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    at24cx_device.intf.write = NULL;

    ret = at24cx_write(&at24cx_device, 0x00, buff, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_NULL_PTR, ret);
}

void test_at24cx_write_InvalidDeviceId(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    at24cx_device.id = AT24Cx_DEV__MAX__;

    ret = at24cx_write(&at24cx_device, 0x00, buff, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_INV_PARAM, ret);
}

void test_at24cx_write_WriteLengthTooLarge(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    // Set the write size 1 byte larger than our devices page size and attempt a write
    ret = at24cx_write(&at24cx_device, 0x00, buff, at24cx_dev_size[at24cx_device.id].page_size+1);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_INV_PARAM, ret);
}

void test_at24cx_write_WriteLengthIsZero(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    // Set the write size to zero
    ret = at24cx_write(&at24cx_device, 0x00, buff, 0x00);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_INV_PARAM, ret);
}

/**************** READ *************************************/
void test_at24cx_read_AllValid(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    ret = at24cx_read(&at24cx_device, 0x00, buff, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_OK, ret);
}

void test_at24cx_read_NullDevice(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    ret = at24cx_read(NULL, 0x00, buff, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_NULL_PTR, ret);
}

void test_at24cx_read_NullDataBuffer(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    ret = at24cx_read(&at24cx_device, 0x00, NULL, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_NULL_PTR, ret);
}

void test_at24cx_read_NullWriteIntf(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    at24cx_device.intf.write = NULL;

    ret = at24cx_read(&at24cx_device, 0x00, buff, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_NULL_PTR, ret);
}

void test_at24cx_read_NullReadIntf(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    at24cx_device.intf.read = NULL;

    ret = at24cx_read(&at24cx_device, 0x00, buff, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_NULL_PTR, ret);
}

void test_at24cx_read_InvalidDeviceId(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    at24cx_device.id = AT24Cx_DEV__MAX__;

    ret = at24cx_read(&at24cx_device, 0x00, buff, at24cx_dev_size[at24cx_device.id].page_size);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_INV_PARAM, ret);
}

void test_at24cx_read_ReadSizeTooLarge(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    // Set the read size 1 byte larger than our devices page size and attempt a write
    ret = at24cx_read(&at24cx_device, 0x00, buff, at24cx_dev_size[at24cx_device.id].page_size+1);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_INV_PARAM, ret);
}

void test_at24cx_read_ReadSizeIsZero(void)
{
    uint8_t buff[at24cx_dev_size[at24cx_device.id].page_size];
    at24cx_return_code_t ret = AT24Cx_RET_OK;

    // Set the read size to zero
    ret = at24cx_read(&at24cx_device, 0x00, buff, 0x00);

    TEST_ASSERT_EQUAL_INT(AT24Cx_RET_INV_PARAM, ret);
}