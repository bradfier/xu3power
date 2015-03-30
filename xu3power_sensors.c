#include <stdio.h>
#include <fcntl.h>

#include "xu3power_sensors.h"


int open_sensor(const char *node, struct sensor *sensor)
{
    if((sensor->fd = open(node, O_RDWR)) < 0) {
        fprintf(stderr, "Failed to open sensor device.");
    }
    return sensor->fd;
}

void set_sensor_enabled(struct sensor *sensor, unsigned char enable)
{
    if (sensor->fd > 0) {
        sensor->data.enable = enable ? 1 : 0;
        if (ioctl(sensor->fd, INA231_IOCSSTATUS, &sensor->data) < 0) {
            fprintf(stderr, "Failed to enable sensor.");
        }
    }
}

void read_sensor(struct sensor *sensor)
{
    if (sensor->fd > 0) {
        if (ioctl(sensor->fd, INA231_IOCGREG, &sensor->data) < 0) {
            fprintf(stderr, "Failed to read sensor.");
        }
    }
}

void close_sensor(struct sensor *sensor)
{
    if (sensor->fd > 0) {
        close(sensor->fd);
    }
}

/*
int main(int argc, char* argv[])
{
    struct sensor sensor;
    open_sensor(DEV_SENSOR_A15, &sensor);
    set_sensor_enabled(&sensor, 1);
    read_sensor(&sensor);
    close_sensor(&sensor);

    printf("%duA\n", sensor.data.cur_uA);
}
*/
