/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SettingsTest.cpp
 * Author: eugine
 *
 * Created on August 11, 2018, 10:21 PM
 */

#include <stdlib.h>
#include <iostream>
#include "src/Settings.h"

/*
 * Simple C++ Test Suite
 */

void testLoad() {
    Settings settings;
    int result = settings.load();
    if (result != 1) {
        std::cout << "%TEST_FAILED% time=0 testname=testLoad (SettingsTest) message=error message sample" << std::endl;
    }
}

int main(int argc, char** argv) {
    std::cout << "%SUITE_STARTING% SettingsTest" << std::endl;
    std::cout << "%SUITE_STARTED%" << std::endl;

    std::cout << "%TEST_STARTED% testLoad (SettingsTest)" << std::endl;
    testLoad();
    std::cout << "%TEST_FINISHED% time=0 testLoad (SettingsTest)" << std::endl;

    std::cout << "%SUITE_FINISHED% time=0" << std::endl;

    return (EXIT_SUCCESS);
}

