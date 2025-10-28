#include "impls.h"


float compute_area_ratio(const std::vector<cv::Point>& contour) {
    /**
     * 要求：
     *      计算输入的轮廓的面积与它的最小外接矩形面积的比例。自行查找
     * 获得轮廓面积的函数。这个量可以用来判断一个轮廓到底有多靠近一个矩形。
     * 
     * 提示：
     * 无。
     * 
     * 通过条件:
     * 运行测试点，通过即可。
     */
    // IMPLEMENT YOUR ???? HERE

    float contour_area = cv::contourArea(contour);//显然是轮廓面积
    cv::RotatedRect min_area_rect = cv::minAreaRect(contour);//最小外接矩形
    float rotated_rect_area = min_area_rect.size.width * min_area_rect.size.height;//最小外接矩形面积
    if (rotated_rect_area)
    {
        return contour_area / rotated_rect_area;//懒得转换类型了，你就将就一下
    }

    return 0.f;
}