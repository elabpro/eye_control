/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   EyesControlTest.h
 * Author: eugine
 *
 * Created on Aug 11, 2018, 11:55:51 PM
 */

#ifndef EYESCONTROLTEST_H
#define EYESCONTROLTEST_H

#include "../src/EyesControl.h"
#include <cppunit/extensions/HelperMacros.h>

class EyesControlTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(EyesControlTest);

    CPPUNIT_TEST(testDetectAndShow);
    CPPUNIT_TEST(testDetect);
    CPPUNIT_TEST(testRectangleGUI);
    CPPUNIT_TEST(testGetAction);

    CPPUNIT_TEST_SUITE_END();

public:
    EyesControlTest();
    virtual ~EyesControlTest();
    void setUp();
    void tearDown();

private:
    EyesControl eyesControl;
    void testDetectAndShow();
    void testDetect();
    void testRectangleGUI();
    void testGetAction();

};

#endif /* EYESCONTROLTEST_H */

