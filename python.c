#include "Python.h"
#include "src/jade.h"

static PyObject*
compileFn(PyObject* self, PyObject* arg) {
	if (!PyString_CheckExact(arg)) return NULL;
	unsigned char *src = (unsigned char*) PyString_AS_STRING(arg);
	unsigned len;
	unsigned char *dst = jade_compile(src, &len);

	return PyString_FromStringAndSize((char *) dst, len);
}

static PyMethodDef exports[] = {
	{"compile", (PyCFunction) compileFn, METH_O, "jade compile"},
	{NULL, NULL}
};

PyMODINIT_FUNC
initjade(void) {
	Py_InitModule("jade", exports);
}
