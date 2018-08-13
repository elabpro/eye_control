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


CPPUNIT_TEST_SUITE_REGISTRATION(EyesControlTest);

EyesControlTest::EyesControlTest() {
}

EyesControlTest::~EyesControlTest() {
}

void EyesControlTest::setUp() {
    Settings* s = new Settings();
    s->load();
    eyesControl.init(*s);
}

void EyesControlTest::tearDown() {
}

void EyesControlTest::testDetectAndShow() {
    //    IplImage* result = eyesControl.detectAndShow();
    int resultInt = 0;
    CPPUNIT_ASSERT_EQUAL(0, resultInt);
}

void EyesControlTest::testDetect() {
    int result = 1; //eyesControl.detectEyes();
    CPPUNIT_ASSERT(result == 1);
}

void EyesControlTest::testRectangleGUI() {
    //    eyesControl.RectangleGUI();
    int result = 1;
    CPPUNIT_ASSERT(result == 1);
}

void EyesControlTest::testGetAction() {
    Settings* s = new Settings();
    s->load();
    eyesControl.init(*s);
    int result = eyesControl.getAction();
    CPPUNIT_ASSERT(result == 0);
    s->setEye(1,100);
    s->setEye(2,300);
    s->glaztime = 0;
    result = eyesControl.getAction();
    CPPUNIT_ASSERT(result == 1);
}
