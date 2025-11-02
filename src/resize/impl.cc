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
    /*
    int new_rows = input.rows * scale, new_cols = input.cols * scale;
     // IMPLEMENT YOUR CODE HERE
     
     return cv::Mat::zeros(new_rows, new_cols, input.type());
     */
    int new_rows = input.rows * scale;
    int new_cols = input.cols * scale;
    int int_rows = static_cast<int>(new_rows + 0.5f);
    int int_cols = static_cast<int>(new_cols + 0.5f);
    
    cv::Mat output(int_rows, int_cols, input.type());
    int src_w = input.cols;
    int src_h = input.rows;
    
    // 计算内部区域（即可以使用双线性插值区域）的最大 i 和 j，确保 x1 = x0 + 1 和 y1 = y0 + 1 始终有效
    int max_i_inner = static_cast<int>(scale * (src_w - 1)) - 1;
    int max_j_inner = static_cast<int>(scale * (src_h - 1)) - 1;
    
    // 区域1: 内部区域 (i从0到max_i_inner, j从0到max_j_inner)
    for (int j = 0; j <= max_j_inner; ++j) {
        for (int i = 0; i <= max_i_inner; ++i) {
            // 显然(u,v)更好表示点坐标
            float u = static_cast<float>(i) / scale;
            float v = static_cast<float>(j) / scale;
            int x0 = static_cast<int>(u);
            int y0 = static_cast<int>(v);
            float dx = u - x0;
            float dy = v - y0;
            int x1 = x0 + 1;
            int y1 = y0 + 1;
            for (int c = 0; c < 3; ++c) {
                uchar p00 = input.data[y0 * src_w * 3 + x0 * 3 + c];
                uchar p10 = input.data[y0 * src_w * 3 + x1 * 3 + c];
                uchar p01 = input.data[y1 * src_w * 3 + x0 * 3 + c];
                uchar p11 = input.data[y1 * src_w * 3 + x1 * 3 + c];
                float interpolated = (1.0f - dx) * (1.0f - dy) * p00 +
                                     dx * (1.0f - dy) * p10 +
                                     (1.0f - dx) * dy * p01 +
                                     dx * dy * p11;
                uchar value = interpolated < 0 ? 0 : (interpolated > 255 ? 255 : static_cast<uchar>(interpolated));
                output.data[j * int_cols * 3 + i * 3 + c] = value;
            }
        }
    }
    // 区域2: 右边界 (i从max_i_inner+1到int_cols-1, j从0到max_j_inner)
    for (int j = 0; j <= max_j_inner; ++j) {
        for (int i = max_i_inner + 1; i < int_cols; ++i) {
            float u = static_cast<float>(i) / scale;
            float v = static_cast<float>(j) / scale;
            int x0 = static_cast<int>(u);
            int y0 = static_cast<int>(v);
            float dx = u - x0;
            float dy = v - y0;
            int x1 = src_w - 1;
            int y1 = y0 + 1;
            for (int c = 0; c < 3; ++c) {
                uchar p00 = input.data[y0 * src_w * 3 + x0 * 3 + c];
                uchar p10 = input.data[y0 * src_w * 3 + x1 * 3 + c];
                uchar p01 = input.data[y1 * src_w * 3 + x0 * 3 + c];
                uchar p11 = input.data[y1 * src_w * 3 + x1 * 3 + c];
                float interpolated = (1.0f - dx) * (1.0f - dy) * p00 +
                                     dx * (1.0f - dy) * p10 +
                                     (1.0f - dx) * dy * p01 +
                                     dx * dy * p11;
                uchar value = interpolated < 0 ? 0 : (interpolated > 255 ? 255 : static_cast<uchar>(interpolated));
                output.data[j * int_cols * 3 + i * 3 + c] = value;
            }
        }
    }
    // 区域3: 底边界 (i从0到max_i_inner, j从max_j_inner+1到int_rows-1)
    for (int j = max_j_inner + 1; j < int_rows; ++j) {
        for (int i = 0; i <= max_i_inner; ++i) {
            float u = static_cast<float>(i) / scale;
            float v = static_cast<float>(j) / scale;
            int x0 = static_cast<int>(u);
            int y0 = static_cast<int>(v);
            float dx = u - x0;
            float dy = v - y0;
            int x1 = x0 + 1;
            int y1 = src_h - 1;
            for (int c = 0; c < 3; ++c) {
                uchar p00 = input.data[y0 * src_w * 3 + x0 * 3 + c];
                uchar p10 = input.data[y0 * src_w * 3 + x1 * 3 + c];
                uchar p01 = input.data[y1 * src_w * 3 + x0 * 3 + c];
                uchar p11 = input.data[y1 * src_w * 3 + x1 * 3 + c];
                float interpolated = (1.0f - dx) * (1.0f - dy) * p00 +
                                     dx * (1.0f - dy) * p10 +
                                     (1.0f - dx) * dy * p01 +
                                     dx * dy * p11;
                uchar value = interpolated < 0 ? 0 : (interpolated > 255 ? 255 : static_cast<uchar>(interpolated));
                output.data[j * int_cols * 3 + i * 3 + c] = value;
            }
        }
    }
    // 区域4: 角落 (i从max_i_inner+1到int_cols-1, j从max_j_inner+1到int_rows-1)
    for (int j = max_j_inner + 1; j < int_rows; ++j) {
        for (int i = max_i_inner + 1; i < int_cols; ++i) {
            float u = static_cast<float>(i) / scale;
            float v = static_cast<float>(j) / scale;
            int x0 = static_cast<int>(u);
            int y0 = static_cast<int>(v);
            float dx = u - x0;
            float dy = v - y0;
            int x1 = src_w - 1;
            int y1 = src_h - 1;
            for (int c = 0; c < 3; ++c) {
                uchar p00 = input.data[y0 * src_w * 3 + x0 * 3 + c];
                uchar p10 = input.data[y0 * src_w * 3 + x1 * 3 + c];
                uchar p01 = input.data[y1 * src_w * 3 + x0 * 3 + c];
                uchar p11 = input.data[y1 * src_w * 3 + x1 * 3 + c];
                float interpolated = (1.0f - dx) * (1.0f - dy) * p00 +
                                     dx * (1.0f - dy) * p10 +
                                     (1.0f - dx) * dy * p01 +
                                     dx * dy * p11;
                uchar value = interpolated < 0 ? 0 : (interpolated > 255 ? 255 : static_cast<uchar>(interpolated));
                output.data[j * int_cols * 3 + i * 3 + c] = value;
            }
        }
    }
    return output;
}