#include "detector.h"
#include <typeinfo>

Detector::Detector(cv::Mat image)
{
    std::cout << "PRE PROCESSING" << std::endl;
    std::cout << "- scaling image" << std::endl;
    Sign::m_originalImage = Filter::scale(image, 150);

    std::cout << "- apply sobel" << std::endl;
    Sign::m_modifiedImage = Filter::sobelXY(Sign::m_originalImage);

    cv::namedWindow("", CV_WINDOW_AUTOSIZE);
    cv::imshow("", Sign::m_modifiedImage);
    cv::waitKey(0);

    detectedSigns = new std::vector<Sign*>;
}

void Detector::detectSigns()
{
    std::cout << "PROCESSING" << std::endl;
    std::cout << "- detecting signs" << std::endl;
    int maxRadius = 0;
    int leftEdge, rightEdge, topEdge, bottomEdge;

    for(int numberOfRows = m_numberOfIgnoredBounds; numberOfRows <= Sign::m_modifiedImage.rows - m_numberOfIgnoredBounds*2; numberOfRows += m_checkRate) // anzahl reihen
    {
        for(int numberOfCols = m_numberOfIgnoredBounds; numberOfCols < Sign::m_modifiedImage.cols - m_numberOfIgnoredBounds*2; numberOfCols += m_checkRate) // anzahl spalten
        {
            leftEdge = numberOfCols;
            rightEdge = Sign::m_modifiedImage.cols - numberOfCols;
            topEdge = numberOfRows;
            bottomEdge = Sign::m_modifiedImage.rows - numberOfRows;

            maxRadius = std::min(leftEdge, std::min(rightEdge, std::min(topEdge, bottomEdge)));

            for(int i = m_startRadius; i <= maxRadius; i += m_radiusSteps)
            {
                m_stopSign = new StopSign(numberOfCols, numberOfRows, i);
                if(m_stopSign->isSign(m_minimumGreyvalue))
                {
                    detectedSigns->push_back(m_stopSign);
                }

                m_priorityWaySign = new PriorityWaySign(numberOfCols, numberOfRows, i);
                if(m_priorityWaySign->isSign(m_minimumGreyvalue))
                {
                    detectedSigns->push_back(m_priorityWaySign);
                }

                m_giveWaySign = new GiveWaySign(numberOfCols, numberOfRows, i);
                if(m_giveWaySign->isSign(m_minimumGreyvalue))
                {
                    detectedSigns->push_back(m_giveWaySign);
                }

                m_prioritySign = new PrioritySign(numberOfCols, numberOfRows, i);
                if(m_prioritySign->isSign(m_minimumGreyvalue))
                {
                    detectedSigns->push_back(m_prioritySign);
                }
            }
        }
    }
    std::cout << "  - signs found: " << detectedSigns->size() << std::endl;
}

void Detector::setNumberOfIgnoredBounds(int number)
{
    this->m_numberOfIgnoredBounds = number;
}

int Detector::getNumberOfIgnoredBounds()
{
    return this->m_numberOfIgnoredBounds;
}

void Detector::setCheckrate(int rate)
{
    this->m_checkRate = rate;
}

int Detector::getCheckrate()
{
    return this->m_checkRate;
}

void Detector::setRadiusSteps(int steps)
{
    this->m_radiusSteps = steps;
}

int Detector::getRadiusSteps()
{
    return this->m_radiusSteps;
}

void Detector::setMinimumGreyvalue(int value)
{
    this->m_minimumGreyvalue = value;
}

int Detector::getMinimumGreyValue()
{
    return this->m_minimumGreyvalue;
}

std::vector<Sign*> Detector::getSingle(std::vector<Sign*> *sign)
{
    std::vector<Sign*> *trueSigns = new std::vector<Sign*>;
    ulong stop = 0;
    int lastRadius = 0;
    double distance = 0;

    for(ulong i = 0; i<sign->size(); i++){
        if(lastRadius < sign->at(i)->m_radius){
            stop = i;
            lastRadius = sign->at(i)->m_radius;
        }
    }

    trueSigns->push_back(sign->at(stop));
    sign->erase(detectedSigns->begin()+static_cast<long>(stop));
    for(ulong a = 0; a < sign->size(); a++){
        distance = sqrt(static_cast<int>(pow(abs(trueSigns->front()->m_x - sign->at(a)->m_x),2)) + static_cast<int>(pow(abs(trueSigns->front()->m_y - sign->at(a)->m_y),2)));
        if(distance - sign->at(a)->m_radius > trueSigns->front()->m_radius){
            trueSigns->push_back(sign->at(a));
       }
    }
    return *trueSigns;
}

Detector::~Detector()
{
    delete m_priorityWaySign;
    delete m_stopSign;
    delete m_giveWaySign;
    delete detectedSigns;
}

void Detector::markDetectedSigns()
{

    std::cout << "POST PROCESSING" << std::endl;
    std::cout << "  - filter signs" << std::endl;
    bool end = false;
    std::vector<Sign*> *testSigns = new std::vector<Sign*>;
    std::vector<Sign*> *trueSigns = new std::vector<Sign*>;
    testSigns = detectedSigns;
    while(end == false){
        if(testSigns->size() != 0){
            *testSigns = Detector::getSingle(testSigns);
            trueSigns->push_back(testSigns->front());
            testSigns->erase(testSigns->begin());
        }
        if(testSigns->size() <= 1){
            end = true;
        }
    }

    std::cout << "  - signs left: " << trueSigns->size() << std::endl;
    for(Sign *elem: *trueSigns){
        if(elem->m_signType == 0){
            cv::circle(Sign::m_originalImage, cv::Point(elem->m_x, elem->m_y),elem->m_radius,cv::Scalar(255,0,0),2);
            std::cout << "  - stopSign found - blue" << std::endl;
        } else if(elem->m_signType == 1)
        {
            cv::circle(Sign::m_originalImage, cv::Point(elem->m_x, elem->m_y),elem->m_radius,cv::Scalar(0,255,0),2);
            std::cout << "  - giveWaySign found - green" << std::endl;
        } else if(elem->m_signType == 2)
        {
            cv::circle(Sign::m_originalImage, cv::Point(elem->m_x, elem->m_y),elem->m_radius,cv::Scalar(0,0,255),2);
            std::cout << "  - priorityWaySign found - red" << std::endl;
        } else if(elem->m_signType == 3)
        {
            cv::circle(Sign::m_originalImage, cv::Point(elem->m_x, elem->m_y),elem->m_radius,cv::Scalar(0,255,255),2);
            std::cout << "  - prioritySign found - yellow" << std::endl;
        }
    }
}
