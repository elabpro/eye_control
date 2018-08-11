/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FaceControl.cpp
 * Author: eugine
 *
 * Created on August 11, 2018, 6:15 PM
 */

#include "EyesControl.h"

EyesControl::EyesControl() {

}

EyesControl::EyesControl(const EyesControl& orig) {
}

int EyesControl::init(Settings& newS) {
    int result = 0;
    s = &newS;
    // Load image from webcam
    try {
        capture = cvCaptureFromCAM(0);
        //-- Вывод ошибки при компиляции, если невозможна загрузка каскадов
        if (!face_cascade.load(s->face_cascade_name)) {
            printf("--(!)Error loading face cascade\n");
            result = -1;
        };
        if (!eyes_cascade.load(s->eyes_cascade_name)) {
            printf("--(!)Error loading eyes cascade\n");
            result = -1;
        };
    } catch (int e) {
        std::cout << "Exception:" << e;
    }
    //-- Создаём окно с параметрами
    namedWindow(s->window_name, WINDOW_AUTOSIZE);
    return result;
}

EyesControl::~EyesControl() {
}

IplImage* EyesControl::detectAndShow() {
    // Get image from Webcam
    image = cvQueryFrame(capture);
    show(*image);
    detect();
}

/**
 * Function to detect eyes on a face with OpenCV2
 */
int EyesControl::detect() {
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
            s->glaz1 = s->glaz1 + 1;
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
                    s->rightglaz = s->rightglaz + 1;
                }
                //-- Который находится вправой части изображения,
                //-- ввиду зеркального изображения
                if (center.x > eye_center.x) {
                    circle(mat_image, eye_center, radius, Scalar(0, 0, 0), 3, 8, 0);
                    //-- Увеличиваем счётчик на 1
                    s->leftglaz = s->leftglaz + 1;
                }
            }
        }
        /** ПРИ НАХОЖДЕНИИ В КАДРЕ ДВУХ ГЛАЗ */
        if (eyes.size() == 2) {
            //-- Увеличиваем счётчик количества двух глаз на 1
            s->glaz2 = s->glaz2 + 1;
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
            s->glaz0 = 1;
            s->glaz1 = 1;
            s->glaz2 = 1;
            s->leftglaz = 1;
            s->rightglaz = 1;
        }

        /** ПРИ НЕНАХОЖДЕНИИ В КАДРЕ ГЛАЗ */
        if (eyes.size() == 0) {
            //-- Увеличиваем счётчик ненахождения глаз на 1
            s->glaz0 = s->glaz0 + 1;
            //-- Отрисовка лица кругом синего цвета
            Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
            ellipse(mat_image, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0,
                    360, Scalar(255, 0, 0), 6, 8, 0);
        }
    }
    //-- Вывод изображения на экран
    imshow(s->window_name, mat_image);
    return 0;
}

/**
 * Show webcam image with detected eyes and keyboard(?)
 */
void EyesControl::show(IplImage& img) {
    // Если текущая раскладка -- английская
    if (s->language == 1) {
        cv::Mat image2 = imread("../data/alfavit_eng.png");
        cv::Mat image3 = imread("../data/mousepanel.png");
        // Отрисовка выбранной буквы, или пиктограммы
        RectangleGUI();
        mat_image = cv::cvarrToMat(image) + image2 + image3;
    }
    // Если текущая раскладка -- русская
    if (s->language == 2) {
        cv::Mat image2 = imread("../data/alfavit_rus.png");
        cv::Mat image3 = imread("../data/mousepanel.png");
        // Отрисовка выбранной буквы, или пиктограммы
        RectangleGUI();
        mat_image = cv::cvarrToMat(image) + image2 + image3;
    }
}

/**
 * Функция налаживает на изображение виртуальной клавиатуры, прямоугольник,
 * который обозначает, какая в данный момент буква выбрана; либо налаживает
 * прямоугольник на боковую панель управления мышью
 * Function puts rectangle over virtual keyboard
 */
void EyesControl::RectangleGUI() {
    if (s->regime == 1) {
        // Keyboard mode
        if (s->language == 1) {
            // English
            cvRectangle(image,
                    cvPoint(25 * (s->keynumberleft - 1), 420),
                    cvPoint(25 * s->keynumberleft, 450),
                    CV_RGB(255, 0, 0), 6, 0, 0);
        } else {
            // Russian
            cvRectangle(image,
                    cvPoint(17 * (s->keynumberleft - 1), 444),
                    cvPoint(17 * s->keynumberleft, 468),
                    CV_RGB(255, 0, 0), 6, 0, 0);
        }
    } else {
        // Mouse mode
        cvRectangle(image,
                cvPoint(580, 60 * s->keynumberright),
                cvPoint(635, 60 * (s->keynumberright + 1)),
                CV_RGB(255, 0, 0), 6, 0, 0);
    }
}