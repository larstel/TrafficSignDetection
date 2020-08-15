#include "sign.h"

cv::Mat Sign::m_originalImage = cv::Mat::ones(1,1,CV_8UC3);
cv::Mat Sign::m_modifiedImage = cv::Mat::ones(1,1,CV_8UC3);

Sign::Sign()
{

}

Sign::~Sign()
{

}

std::vector<cv::Point> *Sign::getLineCoordinates(std::vector<cv::Point> *signPoints)
{
    std::vector<cv::Point> *vector = new std::vector<cv::Point>;
    for(uint j = 0; j<signPoints->size() - 1; j++) {
        int x1 = signPoints->at(j).x;
        int y1 = signPoints->at(j).y;

        int x2 = signPoints->at(j+1).x;
        int y2 = signPoints->at(j+1).y;

        int signX = 1;
        int signY = 1;

        int deltaX = abs(x2-x1);
        int deltaY = abs(y2-y1);

        float m = abs(static_cast<float>(deltaY))/abs(static_cast<float>(deltaX));

        if(x1 > x2){
            signX = -1;
        }

        if(y1 > y2){
            signY = -1;
        }

        if(m <= 1){
            for(int i=0; i <= deltaX; i++){
                vector->push_back(cv::Point(static_cast<int>(ceil(x1 + i * signX)), static_cast<int>(ceil(y1 + i * m * signY))));
            }
        } else {
            for(int i=0; i<= deltaY; i++){
                vector->push_back(cv::Point(static_cast<int>(ceil(x1 + i / m * signX)), static_cast<int>(ceil(y1 + i * signY))));
            }
        }
    }
    return vector;
}
