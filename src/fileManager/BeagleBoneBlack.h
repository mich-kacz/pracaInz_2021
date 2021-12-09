/**
 ******************************************************************************
 * @file    BeagleBoneBlack.h
 * @author  Michał Kaczmarczyk
 * @date    2021-08-22
 * @brief   <Provide some short description here>
 ******************************************************************************
 */

#ifndef BEAGLEBONEBLACK_H
#define BEAGLEBONEBLACK_H


/* Paths --------------------------------------------------------------- */

#define BBB_adc0_enable   "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage0_en"
#define BBB_adc0_raw      "/sys/bus/iio/devices/iio:device0/in_voltage0_raw"
#define BBB_adc1_enable   "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage1_en"
#define BBB_adc1_raw      "/sys/bus/iio/devices/iio:device0/in_voltage1_raw"
#define BBB_adc2_enable   "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage2_en"
#define BBB_adc2_raw      "/sys/bus/iio/devices/iio:device0/in_voltage2_raw"
#define BBB_adc3_enable   "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage3_en"
#define BBB_adc3_raw      "/sys/bus/iio/devices/iio:device0/in_voltage3_raw"
#define BBB_adc4_enable   "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage4_en"
#define BBB_adc4_raw      "/sys/bus/iio/devices/iio:device0/in_voltage4_raw"
#define BBB_adc5_enable   "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage5_en"
#define BBB_adc5_raw      "/sys/bus/iio/devices/iio:device0/in_voltage5_raw"
#define BBB_adc6_enable   "/sys/bus/iio/devices/iio:device0/scan_elements/in_voltage6_en"
#define BBB_adc6_raw      "/sys/bus/iio/devices/iio:device0/in_voltage6_raw"
#define BBB_buffer_length "/sys/bus/iio/devices/iio:device0/buffer/length"
#define BBB_buffer_enable "/sys/bus/iio/devices/iio:device0/buffer/enable"
#define BBB_buffer_available "/sys/bus/iio/devices/iio:device0/buffer/data_available"
#define BBB_buffer_data   "/dev/iio:device0"
#define BBB_gpio45        "/sys/class/gpio/gpio45"
#define BBB_gpio66        "/sys/class/gpio/gpio66"
#define BBB_gpio69        "/sys/class/gpio/gpio69"

#endif