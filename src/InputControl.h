/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   InputControl.h
 * Author: eugine
 *
 * Created on August 11, 2018, 6:14 PM
 */

#ifndef INPUTCONTROL_H
#define INPUTCONTROL_H
#include "Settings.h"
#include <iostream>

using namespace std;

class InputControl {
public:
    InputControl();
    InputControl(const InputControl& orig);
    void init(Settings&);
    virtual ~InputControl();
    int process(int);
private:
    Settings* s;
    int InputKey();
    int InputMouse();
};

#endif /* INPUTCONTROL_H */

