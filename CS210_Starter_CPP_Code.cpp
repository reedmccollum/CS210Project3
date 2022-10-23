#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>


using namespace std;
/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code (1)");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code (1)");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code (1)");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


/*
	PrintMenu
		Param: none
		Return: none
	PrintMenu is the loop that allows for user interaction into the program using a while loop and switch/case
	statements. There are three Python functions called: ListItems, ChooseItems, and MakeHistogram.
*/


void PrintMenu() {
	int swCase = 0;
	int passInt;
	string itemChoice;
	int chosenItemFreq;
	while (true) {
		cout << "1 : List all items and purchase frequency" << endl
			<< "2 : Pick a Product" << endl
			<< "3 : Frequency Histogram" << endl
			<< "4 : Exit" << endl;

		try {
			cin >> swCase;
			if (cin.fail()) {
				throw 505;

			}
		}
		catch (...) {
			cout << "Error in input, please try again." << endl;
			break;
		}

		switch (swCase) {
		case 1:
			cout << endl << endl;
			CallProcedure("ListItems");
			cout << endl;
			break;
		case 2:
			cout << endl << "Please choose product:" << endl;
			cin >> itemChoice;
			chosenItemFreq = callIntFunc("ChooseItem", itemChoice);
			if (chosenItemFreq == 0) {
				cout << endl << "Item not listed please try again." << endl;
			}
			else {
				cout << itemChoice << " has been purchased " << callIntFunc("ChooseItem", itemChoice) << " times."
					<< endl << endl;
			}
			break;
		case 3:
			cout << endl;
			CallProcedure("MakeHistogram");
			cout << endl;
			break;
		case 4:
			return;
		default:
			cout << "Invalid entry, please try again" << endl << endl;

		}
	}
}






void main()
{
	PrintMenu();
}