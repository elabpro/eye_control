//-- Подключение библиотек
#include "data/objdetect.hpp"
#include "data/highgui.hpp"
#include "data/imgproc.hpp"
#include <iostream>
#include <fstream> 

using namespace std;
using namespace cv;

void EyeDetected();
void LoadSettings();
void GUI();
void RectangleGUI();
void InputKey();
void InputMouse();

//================== Глобальные переменные =====================
int glaz0; // Счётчик, когда глаза не обнаружены
int glaz1; // Счётчик для одного глаза
int glaz2; // Счётчик для двух глаз
int leftglaz; // Условие, если это левый глаз
int rightglaz; // Условие, если это правый глаз
int keynumberleft; // Номер позиции клавиши, когда закрыт левый глаз
int keynumberright; // Номер позиции клавиши, когда закрыт правый глаз
string commanda; // Команда для терминала Linux
int regime; // Режим работы. 1 - клавиатура, 2 - мышь
IplImage* image; // картинка как изображение
Mat mat_image; // картинка как матрица
CvCapture* capture; // структура, для чтение кадров из камеры
int glaztimekeyboard; // счётчик времени переключения раскладки клавиатуры
int glaztime; // счётчик времени для срабатывания событий
int mousespeed; // счётчик скорости передвижения мыши
int language; // 1 - английский, 2 - русский
//-- Алфавиты
String alfavit_eng = "abcdefghijklmnopqrstuvwxyz";
String alfavit_rus = "абвгдеёжзийклмнопрстуфхцчшщъыьэюя";
//-- Каскады
String face_cascade_name = "data/lbpcascade_frontalface.xml";
String eyes_cascade_name = "data/haarcascade_eye_tree_eyeglasses.xml";
CascadeClassifier face_cascade;
CascadeClassifier eyes_cascade;
String window_name = "PC control eyes";

/** ################################################################# */
/** ++++++++++++++++++++++++ ГОЛОВНАЯ ФУНКЦИЯ +++++++++++++++++++++++ */
//-- @function main

int main(void) {
    //-- Загрузка настроек
    LoadSettings();
    //-- Создаём окно с параметрами
    namedWindow(window_name, WINDOW_AUTOSIZE);
    //-- Считываем видео с камеры
    capture = cvCaptureFromCAM(0);
    image = 0;
    //-- Вывод ошибки при компиляции, если невозможна загрузка каскадов
    if (!face_cascade.load(face_cascade_name)) {
        printf("--(!)Error loading face cascade\n");
        return -1;
    };
    if (!eyes_cascade.load(eyes_cascade_name)) {
        printf("--(!)Error loading eyes cascade\n");
        return -1;
    };
    //-- Устанавливаем начальные значения
    glaz0 = 0;
    glaz1 = 0;
    glaz2 = 0;
    leftglaz = 0;
    rightglaz = 0;
    keynumberleft = 0;
    keynumberright = 0;
    regime = 1; //-- По-умолчанию - режим клавиатуры
    int i;
    language = 1; //-- Язык по умолчанию - английский

    // ============= Заход в бесконечный цикл =============
    //-- В нём будет происходить считывание и обработка входящего видеопотока
    while (1 > 0) {
        // Считываем изображение с камеры
        image = cvQueryFrame(capture);
        // Отрисовка графического интерфейса
        GUI();
        // Нахождение глаз на видеопотоке
        EyeDetected();
        // Если режим клавиатуры
        if (regime == 1) {
            InputKey();
        }// Если режим мыши
        else {
            InputMouse();
        }
        // Выход из программы при нажатии клавиши ESC
        int c = waitKey(1);
        if ((char) c == 27) {
            break;
        }
    }
    return 0;
}

/** 
 *	Функция обработки входящего видеопотока
 */
void EyeDetected() {
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor(mat_image, frame_gray, COLOR_BGR2GRAY);
    equalizeHist(frame_gray, frame_gray);

    //-- Поиск лица
    face_cascade.detectMultiScale(frame_gray, faces, 1.1, 2, 0, Size(180, 180));

    for (size_t i = 0; i < faces.size(); i++) {
        Mat faceROI = frame_gray(faces[i]);
        std::vector<Rect> eyes;

        //-- Поиск глаз на лице
        eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 1, 0 | CASCADE_SCALE_IMAGE, 
            Size(35, 35));

        /** ПРИ НАХОЖДЕНИИ В КАДРЕ ОДНОГО ГЛАЗА */
        if (eyes.size() == 1) {
            //-- Увеличиваем счётчик количества одного глаза на 1
            glaz1 = glaz1 + 1;
            //-- Отрисовка лица кругом синего цвета
            Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
            ellipse(mat_image, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360,
                    Scalar(255, 0, 0), 6, 8, 0);

            for (size_t j = 0; j < eyes.size(); j++) {
                //-- Отрисовка глаз
                Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y +
                        eyes[j].y + eyes[j].height / 2);
                int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
                //-- Который находится влевой части изображения,
                //-- ввиду зеркального изображения
                if (center.x < eye_center.x) {
                    circle(mat_image, eye_center, radius, Scalar(0, 0, 0), 3, 8, 0);
                    //-- Увеличиваем счётчик на 1 
                    rightglaz = rightglaz + 1;
                }
                //-- Который находится вправой части изображения,
                //-- ввиду зеркального изображения
                if (center.x > eye_center.x) {
                    circle(mat_image, eye_center, radius, Scalar(0, 0, 0), 3, 8, 0);
                    //-- Увеличиваем счётчик на 1
                    leftglaz = leftglaz + 1;
                }
            }
        }
        /** ПРИ НАХОЖДЕНИИ В КАДРЕ ДВУХ ГЛАЗ */
        if (eyes.size() == 2) {
            //-- Увеличиваем счётчик количества двух глаз на 1
            glaz2 = glaz2 + 1;
            //-- Отрисовка лица кругом синего цвета
            Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
            ellipse(mat_image, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 360,
                    Scalar(255, 0, 0), 6, 8, 0);

            for (size_t j = 0; j < eyes.size(); j++) {
                //-- Отрисовка глаз
                Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y +
                        eyes[j].y + eyes[j].height / 2);
                int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
                //-- Который находится влевой части изображения
                if (center.x < eye_center.x) {
                    circle(mat_image, eye_center, radius, Scalar(0, 0, 0), 3, 8, 0);
                }
                //-- Который находится вправой части изображения
                if (center.x > eye_center.x) {
                    circle(mat_image, eye_center, radius, Scalar(0, 0, 0), 3, 8, 0);
                }
            }
        }


        /** ПРИ НАХОЖДЕНИИ В КАДРЕ БОЛЕЕ ДВУХ ГЛАЗ */
        if (eyes.size() > 2) {
            glaz0 = 1;
            glaz1 = 1;
            glaz2 = 1;
            leftglaz = 1;
            rightglaz = 1;
        }

        /** ПРИ НЕНАХОЖДЕНИИ В КАДРЕ ГЛАЗ */
        if (eyes.size() == 0) {
            //-- Увеличиваем счётчик ненахождения глаз на 1
            glaz0 = glaz0 + 1;
            //-- Отрисовка лица кругом синего цвета			
            Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
            ellipse(mat_image, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0, 
                360, Scalar(255, 0, 0), 6, 8, 0);
        }
    }
    //-- Вывод изображения на экран
    imshow(window_name, mat_image);
}

/**
 *	Функция производит считывание настроек с файла settings.dat
 **/
void LoadSettings() {
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
}

/**
 *	Функция производит наложение на изображение, получаемое с web-камеры,
 *	виртуальной клавиатуры, и панели управления мышью
 **/
void GUI() {
    // Если текущая раскладка -- английская
    if (language == 1) {
        cv::Mat image2 = imread("data/alfavit_eng.png");
        cv::Mat image3 = imread("data/mousepanel.png");
        // Отрисовка выбранной буквы, или пиктограммы 
        RectangleGUI();
        mat_image = image + image2 + image3;
    }
    // Если текущая раскладка -- русская
    if (language == 2) {
        Mat image1 = image;
        cv::Mat image2 = imread("data/alfavit_rus.png");
        cv::Mat image3 = imread("data/mousepanel.png");
        // Отрисовка выбранной буквы, или пиктограммы 
        RectangleGUI();
        mat_image = image + image2 + image3;
    }
}

/**
 *	Функция налаживает на изображение виртуальной клавиатуры, прямоугольник,
 *	который обозначает, какая в данный момент буква выбрана; либо налаживает
 *	прямоугольник на боковую панель управления мышью
 **/
void RectangleGUI() {
    // Если режим клавиатуры
    if (regime == 1) {
        // Если раскладка -- английская...
        if (language == 1) {
            cvRectangle(image,
                    cvPoint(25 * (keynumberleft - 1), 420),
                    cvPoint(25 * keynumberleft, 450),
                    CV_RGB(255, 0, 0), 6, 0, 0);
        }
        // Если раскладка -- русская...
        if (language == 2) {
            cvRectangle(image,
                    cvPoint(17 * (keynumberleft - 1), 444),
                    cvPoint(17 * keynumberleft, 468),
                    CV_RGB(255, 0, 0), 6, 0, 0);
        }
    }// Если режим мыши
    else {
        cvRectangle(image,
                cvPoint(580, 60 * keynumberright),
                cvPoint(635, 60 * (keynumberright + 1)),
                CV_RGB(255, 0, 0), 6, 0, 0);
    }
}

void InputKey() {
    //-- Условие для сброса счётчиков (когда два глаза открыты)
    if ((glaz2 >= ceil(glaztime * 0.75))
            and (glaz1 < glaz2)) // -25%
    {
        glaz0 = 0;
        glaz1 = 0;
        glaz2 = 0;
        keynumberleft = 0;
        keynumberright = 0;
        leftglaz = 0;
        rightglaz = 0;
    }

    //-- Если разница слишком небольшая - идём на ещё один круг по проверке вход.изобр.
    if (((glaz1 >= glaztime)
            and (glaz1 > glaz2)
            and (glaz2 >= ceil(glaztime * 0.8)))) // -20%
    {
        glaz0 = 0;
        glaz1 = ceil(glaztime * 0.35); // -65%
        glaz2 = ceil(glaztime * 0.35);
        leftglaz = ceil(glaztime * 0.35);
        rightglaz = ceil(glaztime * 0.35);
    }


    //-- Условия для смены раскладки клавиатуры
    if ((glaz0 >= glaztimekeyboard)
            and (glaz1 <= ceil(glaztimekeyboard * 0.85))
            and (glaz2 <= ceil(glaztimekeyboard * 0.85))) {
        if (language == 1) {
            language = 2;
        } else {
            language = 1;
        }
        glaz0 = 0;
        glaz1 = 0;
        glaz2 = 0;
        keynumberleft = 0;
        keynumberright = 0;
        leftglaz = 0;
        rightglaz = 0;
    }

    //-- Условие проверки, когда левый глаз закрыт
    if ((glaz1 >= glaztime)
            and (glaz1 > glaz2)
            and (leftglaz >= glaztime)
            and (leftglaz > rightglaz)) {
        //-- Если язык ввода английский, то...
        if (language == 1) {
            // Если не буква 'a', то удаляем предыдущий символ
            if (keynumberleft != 0) {
                system("xdotool key BackSpace");
            }
            // Предварительная очистка
            commanda = "";
            // Запись буквы из алфавита
            commanda = "xdotool type " + alfavit_eng.substr(keynumberleft, 1);
            // Выполняем команду в терминале
            system(commanda.c_str());
            keynumberleft = keynumberleft + 1;
            if (keynumberleft == 26) {
                keynumberleft = 0;
            }
        }
        //-- Если язык ввода русский, то...
        if (language == 2) {
            // Если не буква 'a', то удаляем предыдущий символ
            if (keynumberleft != 0) {
                system("xdotool key BackSpace");
            }
            // Предварительная очистка
            commanda = "";
            // Запись буквы из алфавита
            commanda = "xdotool type " + alfavit_rus.substr(keynumberleft, 1);
            // Выполняем команду в терминале
            system(commanda.c_str());
            keynumberleft = keynumberleft + 1;
            if (keynumberleft == 33) {
                keynumberleft = 0;
            }
        }
        //-- Для удобства, ускоряем ввод последующих букв
        glaz0 = 0;
        glaz1 = ceil(glaztime * 0.3); // -70%
        glaz2 = ceil(glaztime * 0.3);
        leftglaz = ceil(glaztime * 0.3);
        rightglaz = 0;
    }

    //-- Условие проверки, когда правый глаз закрыт
    if ((glaz1 >= glaztime)
            and (glaz1 > glaz2)
            and (rightglaz >= glaztime)
            and (rightglaz > leftglaz)) {
        switch (keynumberright) {
            case 0:
                system("xdotool key space");
                keynumberright = keynumberright + 1;
                break;
            case 1:
                system("xdotool key BackSpace");
                system("xdotool key KP_Enter");
                keynumberright = keynumberright + 1;
                break;
            case 2:
                system("xdotool key BackSpace");
                system("xdotool key BackSpace");
                keynumberright = keynumberright + 1;
                break;
            case 3:
                keynumberright = 0;
                regime = 2;
        }
        //-- Для удобства, ускоряем ввод последующих букв
        glaz0 = 0;
        glaz1 = ceil(glaztime * 0.3);
        glaz2 = ceil(glaztime * 0.3);
        leftglaz = 0;
        rightglaz = ceil(glaztime * 0.3);
    }
}

void InputMouse() {
    //-- Условие для сброса счётчиков (когда два глаза открыты)
    if ((glaz2 >= ceil(glaztime * 0.85))
            and (glaz1 < glaz2)) // -15%
    {
        glaz0 = 0;
        glaz1 = 0;
        glaz2 = 0;
        keynumberleft = 0;
        keynumberright = 0;
        leftglaz = 0;
        rightglaz = 0;
    }

    //-- Если разница слишком небольшая - идём на ещё один круг по проверке вход.изобр.
    if (((glaz1 >= glaztime)
            and (glaz1 > glaz2)
            and (glaz2 >= ceil(glaztime * 0.8)))) // -20%
    {
        glaz0 = 0;
        glaz1 = ceil(glaztime * 0.35); // -65%
        glaz2 = ceil(glaztime * 0.35);
        leftglaz = ceil(glaztime * 0.35);
        rightglaz = ceil(glaztime * 0.35);
    }

    //-- Условия для перехода в режим клавиатуры
    if ((glaz0 >= glaztimekeyboard)
            and (glaz1 <= ceil(glaztimekeyboard * 0.85))
            and (glaz2 <= ceil(glaztimekeyboard * 0.85))) {
        regime = 1;
        glaz0 = 0;
        glaz1 = 0;
        glaz2 = 0;
        keynumberleft = 0;
        keynumberright = 0;
        leftglaz = 0;
        rightglaz = 0;
    }

    //-- Условие проверки, когда левый глаз закрыт
    if ((glaz1 >= glaztime)
            and (glaz1 > glaz2)
            and (leftglaz >= glaztime)
            and (leftglaz > rightglaz)) {
        // Предварительная очистка
        commanda = "";
        // Нажатие левой кнопки мыши
        if (keynumberright == 0) {
            commanda = "xdotool click 1";
        }
        // Нажатие правой кнопки мыши
        if (keynumberright == 1) {
            commanda = "xdotool click 3";
        }
        // Двойное нажатие левой кнопки мыши
        if (keynumberright == 2) {
            commanda = "xdotool click 1 click 1";
        }
        // Переместить курсор вверх
        if (keynumberright == 3) {
            commanda = "xdotool mousemove_relative 0 -" + mousespeed;
        }
        // Переместить курсор вниз
        if (keynumberright == 4) {
            commanda = "xdotool mousemove_relative 0 " + mousespeed;
        }
        // Переместить курсор влево
        if (keynumberright == 5) {
            commanda = "xdotool mousemove_relative -" + mousespeed;
            commanda = commanda + " 0";
        }
        // Переместить курсор вправо
        if (keynumberright == 6) {
            commanda = "xdotool mousemove_relative " + mousespeed;
            commanda = commanda + " 0";
        }

        // Выполняем команду в терминале
        system(commanda.c_str());
        //-- Для удобства, ускоряем ввод последующих букв
        glaz0 = 0;
        glaz1 = ceil(glaztime * 0.2); // -80%
        glaz2 = ceil(glaztime * 0.2);
        leftglaz = ceil(glaztime * 0.2);
        rightglaz = 0;
    }

    //-- Условие проверки, когда правый глаз закрыт
    if ((glaz1 >= glaztime)
            and (glaz1 > glaz2)
            and (rightglaz >= glaztime)
            and (rightglaz > leftglaz)) {
        switch (keynumberright) {
            case 0:
                keynumberright = keynumberright + 1;
                break;
            case 1:
                keynumberright = keynumberright + 1;
                break;
            case 2:
                keynumberright = keynumberright + 1;
                break;
            case 3:
                keynumberright = keynumberright + 1;
                break;
            case 4:
                keynumberright = keynumberright + 1;
                break;
            case 5:
                keynumberright = keynumberright + 1;
                break;
            case 6:
                keynumberright = 0;
                break;

        }
        //-- Для удобства, ускоряем ввод
        glaz0 = 0;
        glaz1 = ceil(glaztime * 0.2);
        glaz2 = ceil(glaztime * 0.2);
        leftglaz = 0;
        rightglaz = ceil(glaztime * 0.2);
    }

}