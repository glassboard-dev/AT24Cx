# AT24Cx I2C (2-Wire) Serial EEPROM

C Driver for the AT24Cx series of 2-Wire Serial EEPROM ICs. This driver can be included directly into a developers source or a static library can be created and then linked against. Development is done on the **develop** branch, and official releases can be found on the **master** branch.

## Retrieving the Source
The source is located on Github and can be either downloaded and included directly into a developers source OR the developer can add this repo as a submodule into their project directory (The latter is the preferred method).

To include the driver as a git submodule
```bash
$ cd ./${DIR_WHERE_YOU_WANT_TO_ADD_THE_MODULE}
$ git submodule add https://github.com/glassboard-dev/AT24Cx
```

## Integration
#### Creating & Linking against a static library
To create a static library to link against, you must first source your build environment and ensure the **CC** environment variable is set to your desired toolchain.

Once your cross-compiler is properly setup. Execute the following commands:
```bash
$ mkdir build && cd build
$ cmake ..
$ make
```
The output library (libat24cx.a) can be found in the **lib/** folder. Link against this file, and include the at24cx.h header file into your source include directories.
```c
#include "at24cx.h"
```

#### Adding to your own source/project
The other option for integrating the source into your project, is to include everything directly into your project
* Set your include directories to include the driver inc/ folder.
* Add the at24cx.c to your source list to be compiled.
* Include the API header file wherever you intended to implement the driver source.
```c
#include "at24cx.h"
```

## Implementing the driver
After following the integration steps above, you are ready to implement the driver and start retrieving ADC data. An example [***main.c***](./template/main.c) can be found in the templates folder that shows how to implement the settings, and data retrieval API. Note that you will need to fill out your own ***usr_*** functions for reading, writing, and a uS delay. You can build the example ***main.c*** by first compiling the static lib following the steps in the ***"Creating & Linking against a static library"*** and then executing the following commands.
```bash
$ cd template
$ mkdir build && cd build
$ cmake ..
$ make
```
Example application and main can be found below:
```C
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
```