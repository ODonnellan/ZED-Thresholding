#include <sl/Camera.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "ZedWrapper.h"

using namespace sl;

int low = 0;

int main(int argc, char **argv) {

    ZedWrapper zedCam;
    zedCam.init("C:/Users/Feathers/Downloads/OfficeWalk.svo");
    
    cv::namedWindow("Win");
    cv::createTrackbar("low", "Win", &low, 128);

    cv::Mat prev = zedCam.retrieveOpenCLDepth();
    cv::cvtColor(prev, prev, cv::COLOR_BGR2GRAY);

    while (true) {
        zedCam.progressFrame();

        cv::Mat thresh = prev.clone();
        cv::Mat test = zedCam.retrieveOpenCLDepth();
        cv::cvtColor(test, test, cv::COLOR_BGR2GRAY);
        cv::absdiff(test, prev, thresh);

        cv::Mat mask = thresh < low / 4.0;

        imshow("Win", mask);
        char c = (char)cv::waitKey(25);
    }
}

