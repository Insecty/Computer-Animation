#ifndef INTERPOL_H
#define INTERPOL_H

#include "cpt.h"
#include "vec.h"

class Interpol
{
public:
    CPt begin[50]; // 起始图形控制点坐标
    CPt end[50];   // 终止图形控制点坐标
    CPt inter[101][50]; // 最多100个插值图形 每个图形最多50个控制点
    int n; // 每个图形控制点个数
    int polnum; // 插值图形个数

    Vec beginvec[50];   // 起始图形矢量表达
    Vec endvec[50];     // 终止图形矢量表达
    Vec intervec[101][50];  // 最多100个插值图形 每个图形最多50个矢量

    Interpol(int __polnum, int __n, double beginx[], double beginy[], double endx[], double endy[]);
    void linear();
    void RectToPolar();   // 起始和终止图形的极坐标系转换
    void veclinear();
    void vecclocklinear();
    void veccounterclocklinear();
    void PolarToRect();   // 中间图形的直角坐标系转换
};

#endif // INTERPOL_H
