#include "impls.h"


std::pair<cv::Rect, cv::RotatedRect> get_rect_by_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用findCountours函数找出输入图像（彩色图像）中的矩形轮廓，并且返回它的外接矩形，以及
     * 最小面积外接矩形。所需要的函数自行查找。->?
     * 
     * 通过条件：
     * 运行测试点，你找到的矩形跟答案一样就行。
    */
    std::pair<cv::Rect, cv::RotatedRect> res;
    // IMPLEMENT YOUR CODE HERE
    // 都懂不解释
    cv::Mat gray;
    cv::cvtColor(input, gray, cv::COLOR_BGR2GRAY);
    cv::Mat dst;
    cv::threshold(gray, dst, 100, 255, cv::THRESH_BINARY_INV);
    
    // 查找轮廓
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(dst, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    // 找到面积最大的轮廓
    double max_area = 0;
    int max_area_idx = -1;
    double area;
    for (int i = 0; i < contours.size(); i++) {//小area找麻麻
        area = cv::contourArea(contours[i]);
        if (area > max_area) {
            max_area = area;
            max_area_idx = i;
        }
    }

    if (max_area_idx > -1) {
        // 计算外接矩形
        res.first = cv::boundingRect(contours[max_area_idx]);
        // 计算最小面积外接矩形
        res.second = cv::minAreaRect(contours[max_area_idx]);
    }
    
    return res;
}