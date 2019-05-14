#undef NDEBUG
#ifndef _minunit_h
#define _minunit_h

#include <stdio.h>
#include "../src/lcthw/dbg.h"
#include <stdlib.h>

#define mu_suite_start() char *message = NULL

#define mu_assert(test, message) if (!(test)) { log_err(message); return message; }
#define mu_run_test(test);  debug("-----%s", " " #test);\
    message = test(); tests_run++; if (message) return message;

#define RUN_TESTS(name) int main(int argc, char *argv[]) {\
    argc = 1; \
    debug("\n-----\nRUNNING: ./%s", argv[0]);\
    char *result = name();\
    if (result != 0) {\
        debug("FAILED: %s", result);\
    }\
    else {\
        debug("ALL TESTS PASSED");\
    }\
    debug("Tests run: %d", tests_run);\
    debug("./%s PASS", argv[0]);\
    exit(result != 0);\
}

int tests_run;

#endif
