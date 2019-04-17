#include "Vision.h"

/**
 * PostProcessor class, all vision data is processed here
 * Written By: Brach Knutson
 */

using namespace cv;

PostProcessor::PostProcessor() {
    this->udp = UDP("127.0.0.1", 3695);
    this->stream = cv::VideoCapture(0);
    this->stream.set(cv::CAP_PROP_FRAME_WIDTH, Settings::CAMERA_RESOLUTION_X);
    this->stream.set(cv::CAP_PROP_FRAME_HEIGHT, Settings::CAMERA_RESULUTION_Y);
}


void PostProcessor::Loop() {

    while(this->stream.isOpened()) {
        Target bestTarget;
        bool targetFound = false;
        int x = -1,
            y = -1,
            d = 100;

        double a = 180;

        cv::Mat frame = GetImage();
        cv::Mat binary;
        cv::Mat out;

        frame.copyTo(out);

        cv::cvtColor(frame, frame, cv::COLOR_BGR2GRAY);
        cv::inRange(frame, cv::Scalar(254,254,254), cv::Scalar(255,255,255), binary);

        std::vector< std::vector<Point> > contours;
        cv::findContours(binary, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
        cv::drawContours(out, contours, -1, cv::Scalar(0,255,0), 3);

        for(int i=0; i<contours.size(); i++) {
            bool ar       = false; //aspect ratio test result
            bool solidity = false; //solidity test result
            bool area     = false; // area test result

            std::vector<Point> contour = contours[i];
            Target targ = Target(contour);
            cv::rectangle(out, targ.boundingRect(), (255,0,0), 3);
            double contourAR = targ.AspectRatio();
            int contourArea = targ.Area();

            int trueContourArea = cv::contourArea(contour);
            double contourSolidity = trueContourArea / (double)contourArea;

            ar = (contourAR > Settings::ASPECT_RATIO - Settings::AR_ERROR &&
                  contourAR < Settings::ASPECT_RATIO + Settings::AR_ERROR);

            solidity = (contourSolidity > Settings::SOLIDITY - Settings::SOLIDITY_ERROR &&
                        contourSolidity < Settings::SOLIDITY + Settings::SOLIDITY_ERROR);
            
            area = (contourArea > Settings::MIN_AREA);

            // std::cout << "ar pass: " << ar << std::endl;
            // std::cout << "solidity pass: " << solidity << std::endl;
            // std::cout << "area pass: " << area << std::endl;
            // std::cout << "ar value: " << contourAR << std::endl;
            // std::cout << "solidity value: " << contourSolidity << std::endl;
            // std::cout << "area value: " << contourArea << std::endl;

            if(ar && solidity && area) {
                //it a target fellas
                targetFound = true;

                bestTarget = targ;
                x = targ.Center().x;
                y = targ.Center().y;

                cv::circle(out, targ.Center(), 5, cv::Scalar(255,255,0), 5);
                cv::rectangle(out, targ.boundingRect(), cv::Scalar(255,0,0), 3);
            }
        }

        if(targetFound) {
            //find the angle for robot turning (we gonna do it the sketchy way becuase it doesn't have to be crazy accurate)
            int centerFrame = Settings::CAMERA_RESOLUTION_X / 2;
            double pixelsToDegrees = Settings::CAMERA_FOV / (double) Settings::CAMERA_RESOLUTION_X;

            int pixelsToCenter = bestTarget.Center().x - centerFrame;
            a = pixelsToCenter * pixelsToDegrees;
            cv::circle(out, cv::Point(centerFrame, Settings::CAMERA_RESULUTION_Y / 2), 5, cv::Scalar(255, 0, 255), 5);
            cv::circle(out, bestTarget.Center(), 3, cv::Scalar(0,255,255), 3);
        }

        std::string rioString = ":" + 
                            std::to_string(x) + "," + 
                            std::to_string(y) + "," + 
                            std::to_string(d) + "," + 
                            std::to_string((int) a) + ";";

        cv::putText(out, rioString, cv::Point(5,35), cv::FONT_HERSHEY_PLAIN, 1.0, cv::Scalar(0,0,255), 2);

        udp.Send(rioString);

        // //loop through all contours and figure out which are which
        cv::imshow("image", out);
        cv::waitKey(5);
    }
}


cv::Mat PostProcessor::GetImage() {
    cv::Mat img;
    if(Settings::USE_CAMERA) {
        this->stream.read(img);
    } else {
        img = cv::imread("fightingFoxes_target_2.png");
    }

    return img;
}