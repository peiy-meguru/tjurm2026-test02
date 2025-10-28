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
    // RETR_EXTERNAL表示只检测外轮廓
    cv::findContours(dst, contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    // 补充一下，第三个参数可以填的有：
    // 1.cv::RETR_EXTERNAL：表示只检测外轮廓
    // 2.cv::RETR_LIST：表示检测所有轮廓，并将它们保存到同一层级中，不建立任何层级关系
    // 3.cv::RETR_TREE：表示检测所有轮廓，并重建成嵌套轮廓层级树
    // 4.cv::RETR_CCOMP：表示检测所有轮廓，并将它们组织成两级层级结构，如果洞里面还有轮廓，则这些轮廓仍然在顶层（视为新的外轮廓）

    // 找到面积最大的轮廓
    double max_area = cv::contourArea(contours[0]);
    int max_area_idx = 0;
    double area;
    for (int i = 1; i < contours.size(); i++) {//小area找麻麻
        area = cv::contourArea(contours[i]);
        if (area > max_area) {
            max_area = area;
            max_area_idx = i;
        }
    }

    // 计算外接矩形
    res.first = cv::boundingRect(contours[max_area_idx]);
    // 计算最小面积外接矩形
    res.second = cv::minAreaRect(contours[max_area_idx]);
    
    return res;
}