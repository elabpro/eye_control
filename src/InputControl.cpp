/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   InputControl.cpp
 * Author: eugine
 *
 * Created on August 11, 2018, 6:14 PM
 */

#include "InputControl.h"

InputControl::InputControl() {
}

InputControl::InputControl(const InputControl& orig) {
}

void InputControl::init(Settings& newS) {
    s = &newS;
}

InputControl::~InputControl() {
}

/**
 * Process eyes changes
 *
 * @param regime 1 - keyboard, 2 - mouse
 * @return
 */
int InputControl::process(int regime) {
    int result = 0;
    if (regime == 1) {
        result = InputKey();
    } else {
        result = InputMouse();
    }
    return result;
}

/**
 * Manipulate with keyboard
 * 
 * @return 0 - unknown, 1 - change language
 */
int InputControl::InputKey() {
    int result = 0;
    String command;

    //-- Условия для смены раскладки клавиатуры
    // Condition to change language
    if ((s->getEye(0) >= s->glaztimekeyboard)
            and (s->getEye(1) <= ceil(s->glaztimekeyboard * 0.85))
            and (s->getEye(2) <= ceil(s->glaztimekeyboard * 0.85))) {
        s->changeLanguage();
        s->setEye(0, 0);
        s->setEye(1, 0);
        s->setEye(2, 0);
        s->keynumberleft = 0;
        s->keynumberright = 0;
        s->setEye(3, 0);
        s->setEye(4, 0);
        result = 1;
    }

    //-- Условие проверки, когда левый глаз закрыт
    if ((s->getEye(1) >= s->glaztime)
            and (s->getEye(1) > s->getEye(2))
            and (s->getEye(3) >= s->glaztime)
            and (s->getEye(3) > s->getEye(4))) {
        // Если не буква 'a', то удаляем предыдущий символ
        if (s->keynumberleft != 0) {
            makeMove("xdotool key BackSpace");
        }
        // Запись буквы из алфавита
        command = "xdotool type " + s->getAlfavit().substr(s->keynumberleft, 1);
        // Выполняем команду в терминале
        makeMove(command);
        s->keynumberleft = s->keynumberleft + 1;
        if (s->getLanguage() == 1) {
            //-- Если язык ввода английский, то...
            if (s->keynumberleft == 26) {
                s->keynumberleft = 0;
            }
        } else {
            //-- Если язык ввода русский, то...
            if (s->keynumberleft == 33) {
                s->keynumberleft = 0;
            }
        }
        //-- Для удобства, ускоряем ввод последующих букв
        s->setEye(0, 0);
        s->setEye(1, ceil(s->glaztime * 0.3)); // -70%
        s->setEye(2, ceil(s->glaztime * 0.3));
        s->setEye(3, ceil(s->glaztime * 0.3));
        s->setEye(4, 0);
    }

    //-- Условие проверки, когда правый глаз закрыт
    if ((s->getEye(1) >= s->glaztime)
            and (s->getEye(1) > s->getEye(2))
            and (s->getEye(4) >= s->glaztime)
            and (s->getEye(4) > s->getEye(3))) {
        switch (s->keynumberright) {
            case 0:
                makeMove("xdotool key space");
                s->keynumberright = s->keynumberright + 1;
                break;
            case 1:
                makeMove("xdotool key BackSpace");
                makeMove("xdotool key KP_Enter");
                s->keynumberright = s->keynumberright + 1;
                break;
            case 2:
                makeMove("xdotool key BackSpace");
                makeMove("xdotool key BackSpace");
                s->keynumberright = s->keynumberright + 1;
                break;
            case 3:
                s->keynumberright = 0;
                s->regime = 2;
        }
        //-- Для удобства, ускоряем ввод последующих букв
        s->setEye(0, 0);
        s->setEye(1, ceil(s->glaztime * 0.3));
        s->setEye(2, ceil(s->glaztime * 0.3));
        s->setEye(3, 0);
        s->setEye(4, ceil(s->glaztime * 0.3));
    }
    return result;
}

/**
 * Manipulate with mouse
 */
int InputControl::InputMouse() {
    int result = 0;
    String command;
    //-- Условия для перехода в режим клавиатуры
    if ((s->getEye(0) >= s->glaztimekeyboard)
            and (s->getEye(1) <= ceil(s->glaztimekeyboard * 0.85))
            and (s->getEye(2) <= ceil(s->glaztimekeyboard * 0.85))) {
        s->regime = 1;
        s->setEye(0, 0);
        s->setEye(1, 0);
        s->setEye(2, 0);
        s->keynumberleft = 0;
        s->keynumberright = 0;
        s->setEye(3, 0);
        s->setEye(4, 0);
    }

    //-- Условие проверки, когда левый глаз закрыт
    if ((s->getEye(1) >= s->glaztime)
            and (s->getEye(1) > s->getEye(2))
            and (s->getEye(3) >= s->glaztime)
            and (s->getEye(3) > s->getEye(4))) {
        // Предварительная очистка
        command = "";
        // Нажатие левой кнопки мыши
        if (s->keynumberright == 0) {
            command = "xdotool click 1";
        }
        // Нажатие правой кнопки мыши
        if (s->keynumberright == 1) {
            command = "xdotool click 3";
        }
        // Двойное нажатие левой кнопки мыши
        if (s->keynumberright == 2) {
            command = "xdotool click 1 click 1";
        }
        // Переместить курсор вверх
        if (s->keynumberright == 3) {
            command = "xdotool mousemove_relative 0 -" + s->mousespeed;
        }
        // Переместить курсор вниз
        if (s->keynumberright == 4) {
            command = "xdotool mousemove_relative 0 " + s->mousespeed;
        }
        // Переместить курсор влево
        if (s->keynumberright == 5) {
            command = "xdotool mousemove_relative -" + s->mousespeed;
            command = command + " 0";
        }
        // Переместить курсор вправо
        if (s->keynumberright == 6) {
            command = "xdotool mousemove_relative " + s->mousespeed;
            command = command + " 0";
        }

        makeMove(command);
        //-- Для удобства, ускоряем ввод последующих букв
        s->setEye(0, 0);
        s->setEye(1, ceil(s->glaztime * 0.2)); // -80%
        s->setEye(2, ceil(s->glaztime * 0.2));
        s->setEye(3, ceil(s->glaztime * 0.2));
        s->setEye(4, 0);
    }

    //-- Условие проверки, когда правый глаз закрыт
    if ((s->getEye(1) >= s->glaztime)
            and (s->getEye(1) > s->getEye(2))
            and (s->getEye(4) >= s->glaztime)
            and (s->getEye(4) > s->getEye(3))) {
        switch (s->keynumberright) {
            case 0:
                s->keynumberright = s->keynumberright + 1;
                break;
            case 1:
                s->keynumberright = s->keynumberright + 1;
                break;
            case 2:
                s->keynumberright = s->keynumberright + 1;
                break;
            case 3:
                s->keynumberright = s->keynumberright + 1;
                break;
            case 4:
                s->keynumberright = s->keynumberright + 1;
                break;
            case 5:
                s->keynumberright = s->keynumberright + 1;
                break;
            case 6:
                s->keynumberright = 0;
                break;

        }
        //-- Для удобства, ускоряем ввод
        s->setEye(0, 0);
        s->setEye(1, ceil(s->glaztime * 0.2));
        s->setEye(2, ceil(s->glaztime * 0.2));
        s->setEye(3, 0);
        s->setEye(4, ceil(s->glaztime * 0.2));
    }
    return result;
}

/**
 * Use xdotool to make a move
 * 
 * @param command
 * @return 
 */
int InputControl::makeMove(String command) {
    // Выполняем команду в терминале
    return system(command.c_str());
}
