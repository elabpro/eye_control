/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   Settings.cpp
 * Author: eugine
 *
 * Created on August 11, 2018, 6:14 PM
 */

#include "Settings.h"

Settings::Settings() {
}

Settings::Settings(const Settings& orig) {
}

Settings::~Settings() {
}

int Settings::load() {
    int result = 0;
    //-- Каскады
    face_cascade_name = "data/lbpcascade_frontalface.xml";
    eyes_cascade_name = "data/haarcascade_eye_tree_eyeglasses.xml";
    //-- Алфавиты
    alfavit_eng = "abcdefghijklmnopqrstuvwxyz";
    alfavit_rus = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
    window_name = "PC control eyes";
    //-- Устанавливаем начальные значения
    glaz0 = 0;
    glaz1 = 0;
    glaz2 = 0;
    leftglaz = 0;
    rightglaz = 0;
    keynumberleft = 0;
    keynumberright = 0;
    regime = 1; //-- По-умолчанию - режим клавиатуры
    language = 1; //-- Язык по умолчанию - английский

    try {
        // Создаём поток
        ifstream FILE;
        // Открываем файл
        FILE.open("data/settings.dat", ios::in);
        char value[3];
        // Считываем данные
        FILE>>value;
        // Преобразуем в int
        glaztimekeyboard = atoi(value);
        FILE>>value;
        glaztime = atoi(value);
        FILE>>value;
        mousespeed = atoi(value);
        // Закрываем файл
        FILE.close();
        result = 1;
    } catch (int e) {
        cout << "Exception " << e << "\n";
    }
    return result;
}