#include <iostream>
#include <opencv2/opencv.hpp>

int main(){

    std::cout << CV_VERSION << std::endl;
    cv::Mat image = cv::Mat::zeros(400, 600, CV_8UC3);

    cv::rectangle(image, cv::Point(50, 50), cv::Point(550, 350), cv::Scalar(0, 255, 0), -1);

    cv::imshow("Image", image);
    cv::waitKey(0);
    return 0;
}

