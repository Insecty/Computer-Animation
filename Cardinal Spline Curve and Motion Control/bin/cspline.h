#ifndef SPLINE_H
#define SPLINE_H

#include "cpt.h"

// Cardinal Line
class CSpline
{
public:
    CPt Spline[1024];    // 插值点数组
    CSpline();           // 默认构造函数
    CSpline(double x[100], double y[100], int n, int grain, float tension); // 生成曲线
    void CubicSpine(int n, CPt *knots, int grain, float tension);   // 生成插值点
    virtual ~CSpline(){}
public:
    CPt *knots0;  // 控制点首指针
    int n0;       // 控制点个数
    double m[16]; // M矩阵
    int grain;    // 插值点个数

    double Matrix(double a, double b, double c, double d, double alpha); // 计算插值点坐标
    void GetCardinalMatrix(float t); // 计算M矩阵
};

#endif // SPLINE_H
