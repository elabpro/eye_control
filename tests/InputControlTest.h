/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   InputControlTest.h
 * Author: eugine
 *
 * Created on Aug 11, 2018, 11:48:03 PM
 */

#ifndef INPUTCONTROLTEST_H
#define INPUTCONTROLTEST_H

#include <cppunit/extensions/HelperMacros.h>

class InputControlTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(InputControlTest);

    CPPUNIT_TEST(testProcess);

    CPPUNIT_TEST_SUITE_END();

public:
    InputControlTest();
    virtual ~InputControlTest();
    void setUp();
    void tearDown();

private:
    void testProcess();

};

#endif /* INPUTCONTROLTEST_H */

