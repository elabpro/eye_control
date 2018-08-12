//-- Подключение библиотек
#include "InputControl.h"
#include "EyesControl.h"
#include "Settings.h"
#include <iostream>

using namespace std;

/** ################################################################# */
/** ++++++++++++++++++++++++ ГОЛОВНАЯ ФУНКЦИЯ +++++++++++++++++++++++ */
//-- @function main

int main(void) {
    Settings* s = new Settings();
    s->load();
    InputControl* ic = new InputControl();
    ic->init(*s);
    EyesControl* ec = new EyesControl();
    ec->init(*s);
    // ============= Заход в бесконечный цикл =============
    //-- В нём будет происходить считывание и обработка входящего видеопотока
    while (1 > 0) {
        // Нахождение глаз на видеопотоке
        ec->detectAndShow();
        ic->process(s->regime);

        // Выход из программы при нажатии клавиши ESC
        int c = waitKey(1);
        if ((char) c == 27) {
            break;
        }
    }
    return 0;
}

