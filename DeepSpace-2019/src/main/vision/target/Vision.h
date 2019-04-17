#ifndef VISION_H
#define VISION_H

#include "Settings.h"
#include <iostream>
#include "opencv2/opencv.hpp"

#include "netdb.h"
#include "string.h"
#include "unistd.h"
#include "sys/socket.h"
#include "sys/types.h"
#include "netinet/in.h"
#include "arpa/inet.h"

/**
 * Main header for the FoxFest vision.
 * Written By: Brach Knutson
 */

using namespace cv;

/**
 * A UDP sender utility that sends and recieves information to and from the RIO.
 */
class UDP {
    public:
    UDP(){};
    UDP(std::string dest_ip, int port);
    void Send(std::string msg);
    std::string Recieve();
    void Close();

    private:
    int sock; //sock fd returned by socket() call
    sockaddr_in server_address; //address of the server
};


class Target {
    public:
    Target() {};
    Target(std::vector<Point> contour);
    int Area();
    double AspectRatio();
    double Solidity();
    cv::Point Center();
    cv::Size targSize() { return cv::Size(this->width, this->height); };
    cv::Rect boundingRect() { return cv::boundingRect(this->contour); };
    std::vector<Point> Contour() { return this->contour; };

    private:
    int coordX,
        coordY,
        width,
        height,
        contourArea;

    std::vector<Point> contour;
};


class PostProcessor {
    public:
    PostProcessor();
    void Loop();

    private:
    cv::Mat GetImage();
    cv::VideoCapture stream;
    UDP udp;
};

#endif