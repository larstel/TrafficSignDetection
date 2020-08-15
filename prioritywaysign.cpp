#include "prioritywaysign.h"

PriorityWaySign::PriorityWaySign(int x, int y, int radius)
{
    this->m_x = x;
    this->m_y = y;
    this->m_radius = radius;
    this->m_signType = 2;
}

bool PriorityWaySign::isSign(int minimumGreyValue)
{
    cv::Point a,b,c,d;
    int rPart,gPart,bPart;

    a = cv::Point(m_y + m_radius, m_x);
    b = cv::Point(m_y, m_x + m_radius);

    c = cv::Point(m_y - m_radius,m_x);
    d = cv::Point(m_y, m_x - m_radius);

    std::vector<cv::Point> *pointVector = new std::vector<cv::Point>;
    pointVector->push_back(a);
    pointVector->push_back(b);
    pointVector->push_back(c);
    pointVector->push_back(d);
    pointVector->push_back(a);
    std::vector<cv::Point> *allPoints = new std::vector<cv::Point>;
    allPoints = getLineCoordinates(pointVector);

    for(uint i = 0; i<allPoints->size(); i++){
        if(this->m_modifiedImage.at<cv::Vec3b>(allPoints->at(i).x, allPoints->at(i).y)[0] >= minimumGreyValue){
            m_truePixelCount++;
        } else {
            m_falsePixelCount++;
        }
    }

    if(m_truePixelCount != 0 && static_cast<float>(m_falsePixelCount)/static_cast<float>(m_truePixelCount) < 7.0f){ //5
        for(int b = m_x - m_radius; b < m_x + m_radius; b++)
        {
            for(int a = m_y - m_radius; a < m_y + m_radius; a++)
            {
                rPart = m_originalImage.at<cv::Vec3b>(a,b)[2];
                gPart = m_originalImage.at<cv::Vec3b>(a,b)[1];
                bPart = m_originalImage.at<cv::Vec3b>(a,b)[0];

                if(rPart > 75 && gPart > 75 && bPart < 60 && abs(rPart-gPart) < 70)
                {
                    m_trueColorCount++;
                } else {
                    m_falseColorCount++;
                }
            }
        }
        if(m_trueColorCount != 0 && static_cast<float>(m_falseColorCount)/static_cast<float>(m_trueColorCount) < 5.0f){ //3
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

PriorityWaySign::~PriorityWaySign()
{

}
