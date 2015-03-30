#ifndef _XU3POWER_SENSORS_H
#define _XU3POWER_SENSORS_H

#include <sys/ioctl.h>

#define DEV_SENSOR_A15 "/dev/sensor_arm"
#define DEV_SENSOR_A7  "/dev/sensor_kfc"
#define DEV_SENSOR_MEM "/dev/sensor_mem"
#define DEV_SENSOR_GPU "/dev/sensor_g3d"

struct ina231_iocreg {
    char name[20];
    unsigned int enable;
    unsigned int cur_uV;
    unsigned int cur_uA;
    unsigned int cur_uW;
};

struct sensor {
    int fd;
    struct ina231_iocreg data;
};

#define INA231_IOCGREG      _IOR('i', 1, struct ina231_iocreg *)
#define INA231_IOCSSTATUS   _IOW('i', 2, struct ina231_iocreg *)
#define INA231_IOCGSTATUS   _IOR('i', 3, struct ina231_iocreg *)

/* Open the file handle for the sensor device */
int open_sensor(const char *node, struct sensor *sensor);

/* Set the sensor enable status bit */
void set_sensor_enabled(struct sensor *sensor, unsigned char enable);

/* Read data from a sensor */
void read_sensor(struct sensor *sensor);

/* Close the sensor file descriptor */
void close_sensor(struct sensor *sensor);

#endif //_XU3POWER_SENSORS_H
