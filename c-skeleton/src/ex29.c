#include <stdio.h>
#include "dbg.h"
#include <dlfcn.h>

// (*function_name) = pointer to function
// lib_function f = int (*lib_function)(const char *data)
// f is therefore a function that returns an int and takes
// a const string data as a parameter.

typedef int (*lib_function) (const char *data);

int main(int argc, char *argv[])
{
	int rc = 0;
	check(argc == 4, "Usage: ex29 libex29.so function data");

	char *lib_file = argv[1];
	char *func_to_run = argv[2];
	char *data = argv[3];

	void *lib = dlopen(lib_file, RTLD_NOW);
	check(lib != NULL, "Failed to open the library %s: %s", lib_file, 
			dlerror());

	lib_function func = dlsym(lib, func_to_run);
	check(func != NULL,
			"Did not find %s function in the library %s: %s", func_to_run,
			lib_file, dlerror());

	rc = func(data);
	check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc,
			data);


	return 0;

error:
	return 1;

}
