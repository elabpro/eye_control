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
    IplImage* result = eyesControl.detectAndShow();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void EyesControlTest::testDetect() {
    EyesControl eyesControl;
    int result = eyesControl.detect();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void EyesControlTest::testRectangleGUI() {
    EyesControl eyesControl;
    eyesControl.RectangleGUI();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

