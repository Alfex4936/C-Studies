#include <stdio.h>
#include <stdlib.h>
#include <Python.h>

int main(int argc, char *argv[]) // 나중에 argument로 파일, function 이름 넘길 수 있도록
{
    // Borrowed objects
    PyObject *pName, *pModule, *pDict, *pClass, *pFunc, *pValue, *object;

    Py_Initialize();

    // 파이썬 모듈 위치를 알려주고, 내 파이썬 site-packages 경로를 추가해준다.
    PyObject *sys = PyImport_ImportModule("sys");
    PyObject *path = PyObject_GetAttrString(sys, "path");

    PyList_Append(path, PyUnicode_FromString("."));
    PyList_Append(path, PyUnicode_FromString(getenv("THRID_PACKAGES")));

    // Import the module
    pName = PyUnicode_FromString((char *)"helper");
    if (!pName)
    {
        PyErr_Print();
        printf("Error finding helper.py file in sys.path\n");
    }

    // 모듈 import
    pModule = PyImport_Import(pName);
    if (!pModule)
    {
        PyErr_Print();
        printf("Error importing python script.\n");
    }

    pDict = PyModule_GetDict(pModule);

    // pClass는 helper.py -> Ajou란 클래스
    pClass = PyDict_GetItemString(pDict, (char *)"Ajou");

    if (pClass && PyCallable_Check(pClass))
    {
        object = PyObject_CallObject(pClass, NULL);
    }
    else
    {
        printf("Error calling Ajou class\n");
        PyErr_Print();
    }

    // pValue = Ajou.parse란 함수의 결과로 Tuple이며, integer (보고 싶은 공지 갯수)
    pValue = PyObject_CallMethod(object, "parse", "(i)", 5);
    if (!pValue)
        PyErr_Print();

    // Clean up
    // Py_DECREF, Py_XDECREF는 borrowed object면 해줘야한다.
    // Py_XDECREF는 NULL일 수도 있을 때 사용되며, NULL이 아니라면 Py_DECREF 부르는 것이 빠르다.
    Py_DECREF(sys);
    Py_DECREF(path);

    Py_DECREF(pValue);
    Py_DECREF(pName);
    Py_DECREF(pModule);

    Py_DECREF(pClass);
    Py_DECREF(pDict);

    // 종료 Py3+
    Py_FinalizeEx();

    return 0;
}