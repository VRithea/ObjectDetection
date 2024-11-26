#include <opencv2/opencv.hpp>
#include <iostream>

cv::Mat preprocessImage(const cv::Mat &image)
{
    cv::Mat gray;
    cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

    cv::Mat blurred;
    cv::GaussianBlur(gray, blurred, cv::Size(5, 5), 0);

    // cv::Mat binary;
    // cv::threshold(blurred, binary, 100, 255, cv::THRESH_BINARY);

    cv::Mat edges;
    cv::Canny(blurred, edges, 50, 150);

    return edges;
}

cv::Mat detectColor(const cv::Mat &input, const cv::Scalar lower, const cv::Scalar upper)
{
    cv::Mat hsv, mask;
    cv::cvtColor(input, hsv, cv::COLOR_BGR2HSV);
    cv::inRange(hsv, lower, upper, mask);
    return mask;
}

void detectShapes(const cv::Mat &edges, cv::Mat &output)
{
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(edges, contours, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    for (const auto &contour : contours)
    {
        double area = cv::contourArea(contour);
        if (area > 100)
        {
            std::vector<cv::Point> approx;
            cv::approxPolyDP(contour, approx, 0.02 * cv::arcLength(contour, true), true);

            double perimeter = cv::arcLength(contour, true);
            double circularity = 4 * M_PI * area / (perimeter * perimeter);

            std::string shape;
            if (approx.size() == 3)
                shape = "Triangle";
            else if (approx.size() == 4)
            {

                cv::Rect boundingBox = cv::boundingRect(contour);
                double aspectRatio = (double)boundingBox.width / boundingBox.height;
                if (aspectRatio > 0.95 && aspectRatio < 1.05)
                    shape = "Square";
                else
                    shape = "Rectangle";
            }
            else if (circularity > 0.9)
                shape = "Circle";
            else if (approx.size() == 5)
                shape = "Pentagon";
            else if (approx.size() == 6)
                shape = "Hexagon";
            else if (approx.size() > 6)
                shape = "Polygon (" + std::to_string(approx.size()) + " sides)";
            else
                shape = "Unknown";

            cv::drawContours(output, std::vector<std::vector<cv::Point>>{approx}, -1, cv::Scalar(0, 255, 0), 2);
            cv::putText(output, shape, approx[0], cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(255, 0, 0), 2);
        }
    }
}

void detectShapesInColor(const cv::Mat &input, const cv::Scalar &lower, const cv::Scalar &upper, cv::Mat &output)
{
    cv::Mat mask = detectColor(input, lower, upper);
    cv::Mat edges;
    cv::bitwise_and(preprocessImage(input), mask, edges);
    detectShapes(edges, output);
}

int main()
{

    std::string imagePath = "../res.png";
    cv::Mat image = cv::imread(imagePath);

    // cv::Mat annotated = image.clone();
    //  detectShapesInColor(image, cv::Scalar(35, 50, 50), cv::Scalar(85, 255, 255), annotated); // Green region
    // cv::imshow("Shapes in Green", annotated);

    cv::Mat edges = preprocessImage(image);
    cv::Mat annotated = image.clone();
    detectShapes(edges, annotated);
    cv::imshow("Shapes", annotated);

    // For later
    // cv::Mat greenMask = detectColor(image, cv::Scalar(35, 50, 50), cv::Scalar(85, 255, 255));
    // cv::imshow("Green Mask", greenMask);
    // cv::imshow("Green Mask", edges);
    // cv::imshow("Shapes", annotated);
    cv::waitKey(0);
    return 0;
}
