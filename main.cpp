#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"

#include "detector.h"
#include <chrono>
#include "filter.h"

using namespace std;

int main()
{
    /**
        auto start = std::chrono::high_resolution_clock::now();
        std::ostringstream oss;
        //oss << "/home/lars/Documents/downloads/signs/false_0" << i << ".jpg";
        //oss << "/home/lars/Documents/downloads/stopSign/" << i << ".jpg";
        //oss << "/home/lars/Documents/downloads/giveWaySign/" << i << ".jpg";
        oss << "/home/lars/Documents/downloads/prioritySign/" << 1 << ".jpg";
        //oss << "/home/lars/Documents/downloads/prioritySign/" << i << ".jpg";
        std::string var = oss.str();
        cv::Mat image = cv::imread(var);
        Detector *detector = new Detector(image);
        detector->detectSigns();
        detector->markDetectedSigns();

        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;

        std::cout << "==> Elapsed time: " << elapsed.count() << " s\n";

        cv::namedWindow("", CV_WINDOW_AUTOSIZE);
        cv::imshow("", Filter::scale(Sign::m_originalImage,600));
        cv::waitKey(0);

    **/


    // /**
    for(int i=0; i<=5; i++){
        auto start = std::chrono::high_resolution_clock::now();
        std::ostringstream oss;
        oss << "/home/lars/Documents/downloads/presentation/" << i << ".jpg";
        std::string var = oss.str();
        cv::Mat image = cv::imread(var);
        Detector *detector = new Detector(image);
        detector->detectSigns();
        detector->markDetectedSigns();

        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;

        std::cout << "==> Elapsed time: " << elapsed.count() << " s\n";

        cv::namedWindow("", CV_WINDOW_AUTOSIZE);
        cv::imshow("", Filter::scale(Sign::m_originalImage,600));
        cv::waitKey(0);
    }
    // **/

    /**
    for(int i=6; i<=11; i++){
        auto start = std::chrono::high_resolution_clock::now();
        std::ostringstream oss;
        oss << "/home/lars/Documents/downloads/presentation/" << i << ".jpg";
        std::string var = oss.str();
        cv::Mat image = cv::imread(var);
        Detector *detector = new Detector(image);
        detector->detectSigns();
        detector->markDetectedSigns();

        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;

        std::cout << "==> Elapsed time: " << elapsed.count() << " s\n";

        cv::namedWindow("", CV_WINDOW_AUTOSIZE);
        cv::imshow("", Filter::scale(Sign::m_originalImage,600));
        cv::waitKey(0);
    }
    **/

    /**
    for(int i=12; i<=17; i++){
        auto start = std::chrono::high_resolution_clock::now();
        std::ostringstream oss;
        oss << "/home/lars/Documents/downloads/presentation/" << i << ".jpg";
        std::string var = oss.str();
        cv::Mat image = cv::imread(var);
        Detector *detector = new Detector(image);
        detector->detectSigns();
        detector->markDetectedSigns();

        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;

        std::cout << "==> Elapsed time: " << elapsed.count() << " s\n";

        cv::namedWindow("", CV_WINDOW_AUTOSIZE);
        cv::imshow("", Filter::scale(Sign::m_originalImage,600));
        cv::waitKey(0);
    }
    **/

    /**
    for(int i=18; i<=23; i++){
        auto start = std::chrono::high_resolution_clock::now();
        std::ostringstream oss;
        oss << "/home/lars/Documents/downloads/presentation/" << i << ".jpg";
        std::string var = oss.str();
        cv::Mat image = cv::imread(var);
        Detector *detector = new Detector(image);
        detector->detectSigns();
        detector->markDetectedSigns();

        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;

        std::cout << "==> Elapsed time: " << elapsed.count() << " s\n";

        cv::namedWindow("", CV_WINDOW_AUTOSIZE);
        cv::imshow("", Filter::scale(Sign::m_originalImage,600));
        cv::waitKey(0);
    }

    **/

    /**
    for(int i=24; i<=25; i++){
        auto start = std::chrono::high_resolution_clock::now();
        std::ostringstream oss;
        oss << "/home/lars/Documents/downloads/presentation/" << i << ".jpg";
        std::string var = oss.str();
        cv::Mat image = cv::imread(var);
        Detector *detector = new Detector(image);
        detector->detectSigns();
        detector->markDetectedSigns();

        auto finish = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = finish - start;

        std::cout << "==> Elapsed time: " << elapsed.count() << " s\n";

        cv::namedWindow("", CV_WINDOW_AUTOSIZE);
        cv::imshow("", Filter::scale(Sign::m_originalImage,600));
        cv::waitKey(0);
    }
    **/


    return 0;
}
