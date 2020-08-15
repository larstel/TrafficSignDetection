#include "prioritysign.h"

PrioritySign::PrioritySign(int x, int y, int radius)
{
    this->m_x = x;
    this->m_y = y;
    this->m_radius = radius;
    this->m_signType = 3;
}

bool PrioritySign::isSign(int minimumGreyValue)
{
    float rgbAverage;
    float rgbAddition;
    cv::Point a,b,c;
    int h = static_cast<int>(round((m_radius/2)*sqrt(3)));

    a = cv::Point(m_y-h/2,m_x);
    b = cv::Point(m_y+h/2,m_x+m_radius/2);
    c = cv::Point(m_y+h/2,m_x-m_radius/2);

    std::vector<cv::Point> *pointVector = new std::vector<cv::Point>;
    pointVector->push_back(a);
    pointVector->push_back(b);
    pointVector->push_back(c);
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

    if(m_truePixelCount != 0 && static_cast<float>(m_falsePixelCount)/static_cast<float>(m_truePixelCount) < 1.5f){
        for(int b = m_x - m_radius; b < m_x + m_radius; b++)
        {
            for(int a = m_y - m_radius; a < m_y + m_radius; a++)
            {
                rgbAddition = static_cast<float>(m_originalImage.at<cv::Vec3b>(a,b)[2]) + static_cast<float>(m_originalImage.at<cv::Vec3b>(a,b)[1]) + static_cast<float>(m_originalImage.at<cv::Vec3b>(a,b)[0]);
                rgbAverage = rgbAddition/3;
                if(rgbAverage > 200)
                {
                    m_trueColorCount++;
                } else {
                    m_falseColorCount++;
                }

                if((static_cast<float>(m_originalImage.at<cv::Vec3b>(a,b)[2])/(static_cast<float>(m_originalImage.at<cv::Vec3b>(a,b)[2]) + static_cast<float>(m_originalImage.at<cv::Vec3b>(a,b)[1]) + static_cast<float>(m_originalImage.at<cv::Vec3b>(a,b)[0]))) > 0.6f)
                {
                    m_trueAccentColor++;
                } else {
                    m_falseAccentColor++;
                }
            }
        }
        if(m_trueColorCount != 0 && static_cast<float>(m_falseColorCount)/static_cast<float>(m_trueColorCount) < 1.0f && m_trueAccentColor !=0 && static_cast<float>(m_falseAccentColor)/static_cast<float>(m_trueAccentColor) < 9.0f){
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}


PrioritySign::~PrioritySign()
{

}
