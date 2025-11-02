#include "impls.h"


std::vector<std::vector<cv::Point>> find_contours(const cv::Mat& input) {
    /**
     * 要求：
     * 使用cv::findContours函数，从输入图像（3个通道）中找出所有的最内层轮廓。
     * 将它们保存起来作为函数返回值就行。contours的中文意思就是轮廓。
     * 
     * 提示：
     * 1. 使用cv::imshow来查看输入图像。
     * 2. 使用cv::drawContours来在一张图上绘制轮廓。
     * 3. 直接使用原图一般而言不利于轮廓的寻找，可以做一些简单的处理。
     * 4. findContours函数可以返回轮廓的层次结构，理解层次结构的保存方式并使用它（重点）。
     * 
     * 通过条件：
     * 运行测试点，你找到的轮廓与答案的轮廓一样就行。
     */
    
    // 请参考 https://zhuanlan.zhihu.com/p/396282346
    std::vector<std::vector<cv::Point>> res;
    // IMPLEMENT YOUR CODE HERE
    cv::imshow("输入图像 - INPUTTED IMAGE", input);

    // 显然应当二值化简化问题
    cv::Mat gray_image;
    cv::cvtColor(input, gray_image, cv::COLOR_BGR2GRAY);

    cv::Mat dst_image;
    // 使用cv::threshold，将灰度值小于128的像素设为0（黑），大于等于128的设为255（白）
    cv::threshold(gray_image, dst_image, 128, 255, cv::THRESH_BINARY);

    std::vector<std::vector<cv::Point>> all_contours; // 用于存储所有找到的轮廓
    std::vector<cv::Vec4i> hierarchy; // 用于存储轮廓的层级结构
    // RETR_TREE会构建完整的轮廓层级树
    // CHAIN_APPROX_SIMPLE只保留端点
    cv::findContours(dst_image, all_contours, hierarchy, cv::RETR_TREE, cv::CHAIN_APPROX_SIMPLE);

    // 筛选最内层轮廓
    for (size_t i = 0; i < all_contours.size(); ++i) {
        /* hierarchy[i] 是一个包含4个整数的向量：[Next, Previous, First_Child, Parent]
           Next表示同一层次的下一个轮廓，Previous表示同一层次上的先前轮廓，First_Child表示它的第一个子轮廓，Parent表示其父轮廓的索引
           First_Child 是轮廓i的第一个子轮廓的索引。
           如果 First_Child == -1，说明这个轮廓没有任何子轮廓，因此它是最内层的轮廓。 */
        if (hierarchy[i][2] == -1) {
            res.push_back(all_contours[i]);
        }
    }
    
    return res;
}