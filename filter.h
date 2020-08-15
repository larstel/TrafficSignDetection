#ifndef FILTER_H
#define FILTER_H
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"

class Filter
{
public:
    static cv::Mat sobelXY(cv::Mat image);
    static std::list<cv::Point>* getLineCoordinates(cv::Point start, cv::Point end);
    static cv::Mat scale(cv::Mat image, int widestSide);
private:
    static cv::Mat toGreyscaleByLuminosity(cv::Mat image);
    static bool isGreyImage(cv::Mat image);
};

#endif // FILTER_H
