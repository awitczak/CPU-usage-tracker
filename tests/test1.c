#include <assert.h>
#include <string.h>
#include "fileread.h"

void test1_filepath();
void test2_filepath();

int main() {

    test1_filepath();
    //test2_filepath();


    return 0;
}

void test1_filepath() {
    const char* filepath = "/home/awitczak/Desktop/CPU_Usage_Tracker/tests/test.txt";

    char **data = (char **) get_CPU_data(filepath);

    assert(strcmp(data[0], "cpu  1 1 1 1 1 1 1 1 1 1") == 0);
    assert(strcmp(data[1], "cpu0 32066 43 6450 873879 581 0 1722 0 0 0") == 0);
    assert(strcmp(data[2], "cpu1 32852 285 6558 872478 454 0 807 0 0 0") == 0);

    // assert(strcmp(data[0], "cpu 1123 1 1 1 1 1 1 1 1 0") == 0);
}

void test2_filepath() {
    const char* filepath = "/home/awitczak/Desktop/CPU_Usage_Tracker/tests/test.txt";

    char **data = (char **) get_CPU_data(filepath);

    // assert(strcmp(data[0], "cpu  1 1 1 1 1 1 1 1 1 1") == 0);
    // assert(strcmp(data[1], "cpu0 32066 43 6450 873879 581 0 1722 0 0 0") == 0);
    // assert(strcmp(data[2], "cpu1 32852 285 6558 872478 454 0 807 0 0 0") == 0);

    assert(strcmp(data[0], "cpu 1123 1 1 1 1 1 1 1 1 0") == 0);
}