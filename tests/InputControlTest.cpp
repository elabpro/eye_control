/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   InputControlTest.cpp
 * Author: eugine
 *
 * Created on August 11, 2018, 10:34 PM
 */

#include <stdlib.h>
#include <iostream>
#include "src/InputControl.h"

/*
 * Simple C++ Test Suite
 */

void testProcess() {
    int p0 = 0;
    InputControl inputControl;
    int result = inputControl.process(p0);
    if (result == 1) {
        std::cout << "%TEST_FAILED% time=0 testname=testProcess (InputControlTest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% InputControlTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testProcess (InputControlTest)" << std::endl;
    testProcess();
    std::cout << "%TEST_FINISHED% time=0 testProcess (InputControlTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

