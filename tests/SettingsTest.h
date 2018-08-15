/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SettingsTest.h
 * Author: eugine
 *
 * Created on Aug 11, 2018, 11:34:51 PM
 */

#ifndef SETTINGSTEST_H
#define SETTINGSTEST_H

#include <cppunit/extensions/HelperMacros.h>

class SettingsTest : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(SettingsTest);

    CPPUNIT_TEST(testLoad);
    CPPUNIT_TEST(testSetEye);
    CPPUNIT_TEST(testLanguage);

    CPPUNIT_TEST_SUITE_END();

public:
    SettingsTest();
    virtual ~SettingsTest();
    void setUp();
    void tearDown();

private:
    void testLoad();
    void testSetEye();
    void testLanguage();

};

#endif /* SETTINGSTEST_H */

