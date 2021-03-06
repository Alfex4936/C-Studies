<div align="center">
<p>
    <img width="200" src="https://cdn.iconscout.com/icon/free/png-512/c-programming-569564.png">
</p>
<h1>C언어 + Python API 공부</h1>
    <h5>-lpython3.7</h5>

[Python C언어 공식 문서](https://python.readthedocs.io/en/latest/extending/extending.html)

</div>

## Python 함수 부르기

모듈 location 추가 -> load my python `file.py` -> 함수 Call -> `Py_X/DECREF`

```c
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

// Clean up...
```

## C언어 Kore 웹프레임워크 JSON 만들기

Simple Example of using JSON in Kore web framework.

```c
struct kore_json_item *build_simple_text(char *msg)
{
    struct kore_json_item *json;
    struct kore_json_item *template;
    struct kore_json_item *outputs;
    struct kore_json_item *simpleTextOuter;
    struct kore_json_item *simpleText;
    struct kore_json_item *text;

    json = kore_json_create_object(NULL, NULL);

    template = kore_json_create_object(json, "template");
    outputs = kore_json_create_array(template, "outputs");
    simpleTextOuter = kore_json_create_object(outputs, NULL);
    simpleText = kore_json_create_object(simpleTextOuter, "simpleText");
    text = kore_json_create_object(simpleText, NULL);
    kore_json_create_string(text, "text", msg); // 마지막으로 text 만들기

    kore_json_create_string(json, "version", "2.0");

    return json;
}

... main()
struct kore_json_item *json;
json = build_simple_text("First SimpleText!");
kore_json_item_tobuf(json, &buf);
char *answer = kore_buf_stringify(&buf, NULL);

// 항상 JSON response
http_response_header(req, "Content-Type", "application/json; charset=utf-8");

// answer = JSON 데이터
http_response(req, 200, answer, strlen(answer));

kore_buf_cleanup(&buf);
kore_json_item_free(json);
```