#include "filter.h"

cv::Mat Filter::sobelXY(cv::Mat image){
    if(Filter::isGreyImage(image) == 0){
        image = Filter::toGreyscaleByLuminosity(image);
    }
    int gauss_mask_x[9] = {1, 2, 1, 0, 0, 0, -1, -2, -1};
    int gauss_mask_y[9] = {1, 0, -1, 2, 0, -2, 1, 0, -1};
    int tmpX = 0;
    int tmpY = 0;
    int counter = 0;
    uchar sobelValue;
    cv::Mat sobelImage = cv::Mat::ones(image.rows-2,image.cols-2,CV_8UC3);
    for(int i = 1; i<image.rows-1; i++){
        for(int j = 1; j<image.cols-1; j++){

            for(int k = i-1; k<i+2; k++){
                for(int l = j-1; l<j+2; l++){
                    tmpX += gauss_mask_x[counter] * static_cast<int>(image.at<cv::Vec3b>(k,l)[0]);
                    tmpY += gauss_mask_y[counter] * static_cast<int>(image.at<cv::Vec3b>(k,l)[0]);
                    counter++;
                }
            }
            sobelValue = static_cast<uchar>(255.0/1449.0*sqrt(tmpX*tmpX+tmpY*tmpY));
            sobelImage.at<cv::Vec3b>(i-1,j-1) = cv::Vec3b(sobelValue, sobelValue, sobelValue);
            tmpX = 0;
            tmpY = 0;
            counter = 0;
        }
    }
    return sobelImage;
}

cv::Mat Filter::toGreyscaleByLuminosity(cv::Mat image){
    cv::Mat greyscaleImage = cv::Mat::ones(image.rows, image.cols, CV_8UC3);
    uchar greyValue;
    for(int i = 0; i < image.cols; i++){
        for(int j = 0; j < image.rows; j++){
            greyValue = static_cast<uchar>(0.07*image.at<cv::Vec3b>(j,i)[0]+0.72*image.at<cv::Vec3b>(j,i)[1]+0.21*image.at<cv::Vec3b>(j,i)[2]);
            greyscaleImage.at<cv::Vec3b>(j,i) = cv::Vec3b(greyValue, greyValue, greyValue);
        }
    }
    return greyscaleImage;
}

bool Filter::isGreyImage(cv::Mat image){
    for(int i=0; i<image.rows; i++){
        for (int j=0; j<image.cols; j++){
            if((static_cast<int>(image.at<cv::Vec3b>(i,j)[0]) != static_cast<int>(image.at<cv::Vec3b>(i,j)[1]) || static_cast<int>(image.at<cv::Vec3b>(i,j)[1]) != static_cast<int>(image.at<cv::Vec3b>(i,j)[2]))){
                return false;
            }
        }
    }
    return true;
}

cv::Mat Filter::scale(cv::Mat image, int widestSide){
    std::cout << "  - original image height: " << image.rows << " width: " << image.cols << std::endl;
    float factor;

    if(image.cols > image.rows){
        factor = static_cast<float>(widestSide) / image.cols;
    } else {
        factor = static_cast<float>(widestSide) / image.rows;
    }
    float newCols = image.cols * factor;
    float newRows = static_cast<int>(round(image.rows * factor));
    std::cout << "  - scaled image height: " << newRows << " width: " << newCols << std::endl;

    float xRatio = image.cols / newCols;
    float yRatio = image.rows / newRows;

    cv::Mat resizedImage = cv::Mat::ones(static_cast<int>(newRows), static_cast<int>(newCols), CV_8UC3);

    int px, py;
    for (int i = 0; i < newCols; i++) {
        for (int j = 0; j < newRows; j++) {
            px = static_cast<int>(floor(i * xRatio));
            py = static_cast<int>(floor(j * yRatio));

            resizedImage.at<cv::Vec3b>(cv::Point(static_cast<int>(i), static_cast<int>(j))) = image.at<cv::Vec3b>(cv::Point(static_cast<int>(px),static_cast<int>(py)));
        }
    }
    return resizedImage;
}
