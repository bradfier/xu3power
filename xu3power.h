#ifndef _XU3POWER_H
#define _XU3POWER_H

#include <Python.h>

#include "xu3power_sensors.h"

static PyObject * getPower(PyObject *self, PyObject *args);

static PyObject * enableSensor(PyObject *self, PyObject *args);

static PyMethodDef xu3power_methods[];

static struct PyModuleDef xu3power_module;

PyMODINIT_FUNC PyInit_xu3power(void);

static void readSensor(const char *device, struct sensor *sensor);

#endif /* _XU3POWER_H */ 
