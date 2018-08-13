/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   SettingsTest.cpp
 * Author: eugine
 *
 * Created on Aug 11, 2018, 11:34:51 PM
 */

#include "SettingsTest.h"
#include "../src/Settings.h"


CPPUNIT_TEST_SUITE_REGISTRATION(SettingsTest);

SettingsTest::SettingsTest() {
}

SettingsTest::~SettingsTest() {
}

void SettingsTest::setUp() {
}

void SettingsTest::tearDown() {
}

void SettingsTest::testLoad() {
    Settings settings;
    int result = settings.load();
    CPPUNIT_ASSERT(result == 1);
}

void SettingsTest::testSetEye() {
    Settings* settings;
    settings = new Settings();
    int result = settings->setEye(1,1);
    CPPUNIT_ASSERT(result == 1);
    result = settings->setEye(1,0);
    CPPUNIT_ASSERT(result == 2);
}
