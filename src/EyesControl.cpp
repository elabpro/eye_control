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

/**
 * Detect eye, show image and make action
 * 
 * @return image
 */
IplImage* EyesControl::detectAndShow() {
    // Get image from Webcam
    image = cvQueryFrame(capture);
    show(*image);
    detectEyes(matImage);
    getAction();
    return image;
}

/**
 * Function to detect eyes on a face with OpenCV2
 */
int EyesControl::detectEyes(Mat mat_image) {
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
        if (eyes.size() == 1 || eyes.size() == 2) {
            //-- Увеличиваем счётчик количества одного глаза на 1
            s->setEye(eyes.size());
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
        } else {
            if (eyes.size() > 2) {
                /** ПРИ НАХОЖДЕНИИ В КАДРЕ БОЛЕЕ ДВУХ ГЛАЗ */
                s->setEye(0, 1);
                s->setEye(1, 1);
                s->setEye(2, 1);
                s->leftglaz = 1;
                s->rightglaz = 1;
            }
        }

        /** ПРИ НЕНАХОЖДЕНИИ В КАДРЕ ГЛАЗ */
        if (eyes.size() == 0) {
            //-- Увеличиваем счётчик ненахождения глаз на 1
            s->setEye(0);
            //-- Отрисовка лица кругом синего цвета
            Point center(faces[i].x + faces[i].width / 2, faces[i].y + faces[i].height / 2);
            ellipse(mat_image, center, Size(faces[i].width / 2, faces[i].height / 2), 0, 0,
                    360, Scalar(255, 0, 0), 6, 8, 0);
        }
    }
    //-- Вывод изображения на экран
    imshow(s->window_name, mat_image);
    matImage = mat_image;
    return 0;
}

/**
 * Show webcam image with detected eyes and keyboard(?)
 */
void EyesControl::show(IplImage& img) {
    String fileName;
    // Если текущая раскладка -- английская
    if (s->language == 1) {
        fileName = s->alfavit_eng_png;
    } else {
        // Отрисовка выбранной буквы, или пиктограммы
        fileName = s->alfavit_rus_png;
    }
    cv::Mat image2 = imread(fileName);
    cv::Mat image3 = imread(s->mouse_panel_png);
    RectangleGUI();
    matImage = cv::cvarrToMat(image) + image2 + image3;
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

/**
 * Find out what to do
 * 
 * @return 0 - nothing, 1 - two eyes are open
 */
int EyesControl::getAction() {
    int result = 0;
    // Two eyes are open
    if ((s->glaz2 >= ceil(s->glaztime * 0.75))
            && (s->glaz1 < s->glaz2)) {
        s->setEye(0, 0);
        s->setEye(1, 0);
        s->setEye(2, 0);
        s->keynumberleft = 0;
        s->keynumberright = 0;
        s->leftglaz = 0;
        s->rightglaz = 0;
        result = 1;
    }

    //-- Если разница слишком небольшая - идём на ещё один круг по проверке вход.изобр.
    if (((s->glaz1 >= s->glaztime)
            && (s->glaz1 > s->glaz2)
            && (s->glaz2 >= ceil(s->glaztime * 0.8)))) {
        s->setEye(0, 0);
        s->setEye(1, ceil(s->glaztime * 0.35)); // -65%
        s->setEye(2, ceil(s->glaztime * 0.35));
        s->leftglaz = ceil(s->glaztime * 0.35);
        s->rightglaz = ceil(s->glaztime * 0.35);
        result = 2;
    }
    return result;
}
