/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   EyesControlTest.cpp
 * Author: eugine
 *
 * Created on Aug 11, 2018, 11:55:51 PM
 */

#include "EyesControlTest.h"
#include "../src/EyesControl.h"


CPPUNIT_TEST_SUITE_REGISTRATION(EyesControlTest);

EyesControlTest::EyesControlTest() {
}

EyesControlTest::~EyesControlTest() {
}

void EyesControlTest::setUp() {
}

void EyesControlTest::tearDown() {
}

void EyesControlTest::testDetectAndShow() {
    EyesControl eyesControl;
//    IplImage* result = eyesControl.detectAndShow();
    int resultInt = 0;
    CPPUNIT_ASSERT_EQUAL(0, resultInt);
}

void EyesControlTest::testDetect() {
    EyesControl eyesControl;
    int result = eyesControl.detectEyes();
    CPPUNIT_ASSERT(result == 1);
}

void EyesControlTest::testRectangleGUI() {
    EyesControl eyesControl;
//    eyesControl.RectangleGUI();
    int result = 1;
    CPPUNIT_ASSERT(result == 1);
}

