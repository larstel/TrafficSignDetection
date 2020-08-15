#ifndef DETECTOR_H
#define DETECTOR_H
#include <opencv2/opencv.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/core.hpp"
#include "filter.h"
#include "sign.h"
#include "prioritywaysign.h"
#include "stopsign.h"
#include "givewaysign.h"
#include "prioritysign.h"

class Detector
{
public:
    Detector(cv::Mat image);
    void detectSigns();
    void markDetectedSigns();

    void setNumberOfIgnoredBounds(int number);
    int getNumberOfIgnoredBounds();

    void setCheckrate(int rate);
    int getCheckrate();

    void setRadiusSteps(int steps);
    int getRadiusSteps();

    void setMinimumGreyvalue(int value);
    int getMinimumGreyValue();

    std::vector<Sign*> getSingle(std::vector<Sign*> *sign);
    ~Detector();

private:
    PriorityWaySign *m_priorityWaySign;
    StopSign *m_stopSign;
    GiveWaySign *m_giveWaySign;
    PrioritySign *m_prioritySign;

    int m_numberOfIgnoredBounds = 0; //ignore X border pixel around the image // default 10
    int m_checkRate = 1; // check sign every X pixel
    int m_radiusSteps = 1; // radius every X steps
    int m_minimumGreyvalue = 80; // greyvalue; every pixel over X is counted // default 100
    int m_startRadius = 6;//3 //12
    
    std::vector<Sign*> *detectedSigns;
};

#endif // DETECTOR_H
