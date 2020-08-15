#include "stopsign.h"

StopSign::StopSign(int x, int y, int radius)
{
    this->m_x = x;
    this->m_y = y;
    this->m_radius = radius;
    this->m_signType = 0;
}

bool StopSign::isSign(int minimumGreyValue)
{
    cv::Point a,b,c,d,e,f,g,h;
    int G = static_cast<int>(round(tan(22.5*(M_PI/180))*m_radius));

    e = cv::Point(m_y+m_radius,m_x+G);
    f = cv::Point(m_y+m_radius,m_x-G);

    b = cv::Point(m_y-m_radius,m_x+G);
    a = cv::Point(m_y-m_radius,m_x-G);

    d = cv::Point(m_y+G,m_x+m_radius);
    c = cv::Point(m_y-G,m_x+m_radius);

    g = cv::Point(m_y+G,m_x-m_radius);
    h = cv::Point(m_y-G,m_x-m_radius);

    std::vector<cv::Point> *pointVector = new std::vector<cv::Point>;
    pointVector->push_back(a);
    pointVector->push_back(b);
    pointVector->push_back(c);
    pointVector->push_back(d);
    pointVector->push_back(e);
    pointVector->push_back(f);
    pointVector->push_back(g);
    pointVector->push_back(h);
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

    if(m_truePixelCount != 0 && static_cast<float>(m_falsePixelCount)/static_cast<float>(m_truePixelCount) < 1.5f){//6
        for(int b = m_x - m_radius; b < m_x + m_radius; b++)
        {
            for(int a = m_y - m_radius; a < m_y + m_radius; a++)
            {
                if((static_cast<float>(m_originalImage.at<cv::Vec3b>(a,b)[2])/(static_cast<float>(m_originalImage.at<cv::Vec3b>(a,b)[2]) + static_cast<float>(m_originalImage.at<cv::Vec3b>(a,b)[1]) + static_cast<float>(m_originalImage.at<cv::Vec3b>(a,b)[0]))) > 0.6f)
                {
                    m_trueColorCount++;
                } else {
                    m_falseColorCount++;
                }
            }
        }
        if(m_trueColorCount != 0 && static_cast<float>(m_falseColorCount)/static_cast<float>(m_trueColorCount) < 1.5f){
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

StopSign::~StopSign()
{

}
