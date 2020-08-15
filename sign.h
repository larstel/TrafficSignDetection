#ifndef SIGN_H
#define SIGN_H
#include <opencv2/opencv.hpp>
#include <string>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"

class Sign
{
public:
    static cv::Mat m_originalImage;
    static cv::Mat m_modifiedImage;
    int m_numberOfPixelThreshold = 30; // min number of pixels which have to be count
    int m_x;
    int m_y;
    int m_radius;
    int m_truePixelCount = 0;
    int m_falsePixelCount = 0;
    int m_trueColorCount = 0;
    int m_falseColorCount = 0;
    int m_trueAccentColor = 0;
    int m_falseAccentColor = 0;
    int m_signType;

    Sign();
    virtual bool isSign(int minimumGreyValue) = 0;
    virtual ~Sign();
protected:
    std::vector<cv::Point>* getLineCoordinates(std::vector<cv::Point> *signPoints); // privat machen?
};

#endif // SIGN_H
