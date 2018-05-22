#ifndef CSPLINEWITHALP_H
#define CSPLINEWITHALP_H

#include "cpt.h"

// Cardinal Spline with arc-length parameterization
class CSplineWithALP
{
public:
    float *a[2], *b[2], *c[2], *d[2]; // 参数
    float *A, *B, *C, *D, *E;         // 计算弧长的参数
    double m[16]; // M矩阵
    CPt *knots0;  // 控制点首指针
    CPt Spline[1024];  // 插值点数组
    CPt SplineWithALP[1024];
    int n0;       // 控制点个数
    int grain;    // 插值点个数
public:
    CSplineWithALP(double x[100], double y[100], int n, int grain, float tension);
    void CubicSpine(int n, CPt *knots, int grain, float tension);
    void GetCardinalMatrix(float t); // 计算M矩阵
    void initLength(); // 初始化ABCDE弧长参数
    float getLen(int i,float u); // 第i段的曲线路径长
    float f(int i,float x); // 第i段的积分函数
    float simpson(int j, float x, float y); // simpson近似函数
    float Matrix(int i, int j,float u);
    float getU(int i,float s,float u1,float u2); // 二分法得到给定s对应u值
    void init(int i,int j,float a0, float b0, float c0, float d0); // 初始化abcd参数

};

#endif // CSPLINEWITHALP_H
