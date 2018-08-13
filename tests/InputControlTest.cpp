/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   InputControlTest.cpp
 * Author: eugine
 *
 * Created on Aug 11, 2018, 11:48:03 PM
 */

#include "InputControlTest.h"
#include "../src/InputControl.h"


CPPUNIT_TEST_SUITE_REGISTRATION(InputControlTest);

InputControlTest::InputControlTest() {
}

InputControlTest::~InputControlTest() {
}

void InputControlTest::setUp() {
}

void InputControlTest::tearDown() {
}

void InputControlTest::testProcess() {
    int p0;
    InputControl inputControl;
//    Settings* s = new Settings();
//    inputControl.init(*s);
// inputControl.process(p0);
    int result = 1;
    CPPUNIT_ASSERT(result == 1);
}

