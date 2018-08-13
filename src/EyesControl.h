/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   FaceControl.h
 * Author: eugine
 *
 * Created on August 11, 2018, 6:15 PM
 */

#ifndef FACECONTROL_H
#define FACECONTROL_H

#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/core/core.hpp>
#include "Settings.h"
#include <iostream>

using namespace std;
using namespace cv;

class EyesControl {
public:
    EyesControl();
    EyesControl(const EyesControl& orig);
    int init(Settings& newS);
    virtual ~EyesControl();
    IplImage* detectAndShow();
    int detectEyes();
    void RectangleGUI();
    CascadeClassifier face_cascade;
    CascadeClassifier eyes_cascade;
    int getAction();
private:
    void show(IplImage&);
    Settings* s;
    CvCapture* capture; // структура, для чтение кадров из камеры
    IplImage* image; // картинка как изображение
    Mat mat_image; // картинка как матрица

};

#endif /* FACECONTROL_H */

