#include "Vision.h"

/**
 * Source file for the Target class.
 * Written By: Brach Knutson
 */

using namespace cv;

Target::Target(std::vector<Point> contour) {
    cv::Rect bounds = cv::boundingRect(contour);

    this->width = bounds.width;
    this->height = bounds.height;

    this->coordX = bounds.x;
    this->coordY = bounds.y;

    // this->contourArea = cv::contourArea(contour);
}


double Target::AspectRatio() {
    return this->width / (double)this->height;
}


double Target::Solidity() {
    return this->Area() / (this->width * this->height);
}


int Target::Area() {
    return (this->width * this->height);
}


cv::Point Target::Center() {
    int x = this->coordX + (this->width / 2);
    int y = this->coordY + (this->height / 2);
    return cv::Point(x, y);
}