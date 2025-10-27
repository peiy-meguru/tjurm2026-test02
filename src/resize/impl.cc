#include "impls.h"


cv::Mat my_resize(const cv::Mat& input, float scale) {
    /**
     * 要求：
     *      实现resize算法，只能使用基础的语法，比如说for循环，Mat的基本操作。不能
     * 用cv::resize。resize算法的内容自行查找学习，不是很难。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件：
     * 运行测试点，你的结果跟答案长的差不多就行。
     */
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
    // IMPLEMENT YOUR CODE HERE
    // 创建一个用于存储调整大小后图像的Mat对象
    cv::Mat output = cv::Mat::zeros(new_rows, new_cols, input.type());
    // 遍历新图像的每个像素
    for (int i = 0; i < new_rows; ++i) {
        for (int j = 0; j < new_cols; ++j) {
            // 计算当前新图像像素在原始图像中对应的坐标（最近邻插值）
            int src_i = static_cast<int>(i / scale);
            int src_j = static_cast<int>(j / scale);
            // 将原始图像的像素值复制到新图像的对应位置
            output.at<cv::Vec3b>(i, j) = input.at<cv::Vec3b>(src_i, src_j);
        }
    }
    return output;
    // return cv::Mat::zeros(new_rows, new_cols, input.type());
}