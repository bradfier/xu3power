#include <Python.h>
#include <string.h>

#include "xu3power.h"
#include "xu3power_sensors.h"

static void readSensor(const char *device, struct sensor *sensor)
{
    open_sensor(device, sensor);
    read_sensor(sensor);
    close_sensor(sensor);
}

static PyObject * getPower(PyObject *self, PyObject *args)
{
    char *device;

    struct sensor sensor;
    int mV, mA, mW;

    if (!PyArg_ParseTuple(args, "s", &device))
        return NULL;

    if (strcmp(device,"A15") == 0) {
        readSensor(DEV_SENSOR_A15, &sensor);

    } else if (strcmp(device,"A7") == 0) {
        readSensor(DEV_SENSOR_A7, &sensor);

    } else if (strcmp(device,"MEM") == 0) {
        readSensor(DEV_SENSOR_MEM, &sensor);

    } else if (strcmp(device,"GPU") == 0) {
        readSensor(DEV_SENSOR_GPU, &sensor);

    } else {
        PyErr_SetFromErrno(PyExc_ValueError);
        return NULL;
    }
    
    mV = sensor.data.cur_uV / 1000;
    mA = sensor.data.cur_uA / 1000;
    mW = sensor.data.cur_uW / 1000;
    return Py_BuildValue("iii", mV, mA, mW);
}

static PyObject * enableSensor(PyObject *self, PyObject *args)
{
    char *device;
    struct sensor sensor;

    if (!PyArg_ParseTuple(args, "s", &device))
        return NULL;

    if (strcmp(device,"A15") == 0) {
        open_sensor(DEV_SENSOR_A15, &sensor);
        set_sensor_enabled(&sensor, 1);
        close_sensor(&sensor);
    
    } else if (strcmp(device,"A7") == 0) {
        open_sensor(DEV_SENSOR_A7, &sensor);
        set_sensor_enabled(&sensor, 1);
        close_sensor(&sensor);

    } else if (strcmp(device,"MEM") == 0) {
        open_sensor(DEV_SENSOR_MEM, &sensor);
        set_sensor_enabled(&sensor, 1);
        close_sensor(&sensor);

    } else if (strcmp(device,"GPU") == 0) {
        open_sensor(DEV_SENSOR_GPU, &sensor);
        set_sensor_enabled(&sensor, 1);
        close_sensor(&sensor);
        
    } else {
        PyErr_SetFromErrno(PyExc_ValueError);
        return NULL;
    }
    return Py_BuildValue("i", 0);
}

static PyMethodDef xu3power_methods[] = {
    {"getPower", getPower, METH_VARARGS,
        "Return the power consumption tuple from the sensor."},

    {"enableSensor", enableSensor, METH_VARARGS,
        "Enable a sensor."},

    {NULL, NULL, 0, NULL} /* Sentinel */
};

static struct PyModuleDef xu3power_module = {
    PyModuleDef_HEAD_INIT,
    "xu3power",
    "ODROID-XU3 INA231 Sensor Module",           /* Module documentation */
    -1,
    xu3power_methods,
    NULL,
    NULL,
    NULL,
    NULL,
};

PyMODINIT_FUNC PyInit_xu3power(void)
{
    return PyModule_Create(&xu3power_module);
}
