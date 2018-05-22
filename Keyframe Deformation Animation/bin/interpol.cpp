#include "interpol.h"
#include "math.h"

Interpol::Interpol(int __polnum, int __n, double beginx[], double beginy[], double endx[], double endy[])
{
    polnum = __polnum;
    n = __n;
    for(int i = 0; i < n; i++){
        begin[i].x = beginx[i];
        begin[i].y = beginy[i];
        end[i].x = endx[i];
        end[i].y = endy[i];
    }
}

void Interpol::linear(){// 线性插值
    for(int i = 0; i < polnum; i++){
        float t = (float)i/(float)polnum;
        for(int j = 0; j < n; j++){  // n个点
            inter[i][j].x = (1-t)*begin[j].x + t*end[j].x;
            inter[i][j].y = (1-t)*begin[j].y + t*end[j].y;
        }

    }
}

void Interpol::RectToPolar(){// 起始和终止图形的极坐标系转换
    for(int i = 0; i < n-1; i++){
        double a2 = pow(begin[i+1].x-begin[i].x,2)+(float)pow(begin[i+1].y-begin[i].y,2);
        double a = sqrt(a2);
        beginvec[i].a = a;
        double theta = atan2(begin[i+1].y-begin[i].y,begin[i+1].x-begin[i].x);
        beginvec[i].theta = theta;
    }

    for(int i = 0; i < n-1; i++){
        double a2 = pow(end[i+1].x-end[i].x,2)+(float)pow(end[i+1].y-end[i].y,2);
        double a = sqrt(a2);
        endvec[i].a = a;
        double theta = atan2(end[i+1].y-end[i].y,end[i+1].x-end[i].x);
        endvec[i].theta = theta;
    }
}

void Interpol::veclinear(){// 矢量线性插值
    RectToPolar();

    for(int i = 0; i < polnum; i++){
        float t = (float)i/(float)polnum;
        // 每个图形第一个控制点坐标由线性插值得到
        inter[i][0].x = (1-t)*begin[0].x + t*end[0].x;
        inter[i][0].y = (1-t)*begin[0].y + t*end[0].y;

        for(int j = 0; j < n-1; j++){  // n-1个矢量
            intervec[i][j].a = (1-t)*beginvec[j].a + t*endvec[j].a;
            // 保证旋转角度始终小于180
            if(endvec[j].theta - beginvec[j].theta < -Pi){
                intervec[i][j].theta = (1-t)*beginvec[j].theta + t*(endvec[j].theta+2*Pi);
            }else if(endvec[j].theta - beginvec[j].theta > Pi){
                intervec[i][j].theta = (1-t)*(beginvec[j].theta+2*Pi) + t*endvec[j].theta;
            }else{
                intervec[i][j].theta = (1-t)*beginvec[j].theta + t*endvec[j].theta;
            }
        }
    }

    PolarToRect();
}

void Interpol::vecclocklinear(){ // 顺时针旋转
    RectToPolar();

    for(int i = 0; i < polnum; i++){
        float t = (float)i/(float)polnum;
        // 每个图形第一个控制点坐标由线性插值得到
        inter[i][0].x = (1-t)*begin[0].x + t*end[0].x;
        inter[i][0].y = (1-t)*begin[0].y + t*end[0].y;

        for(int j = 0; j < n-1; j++){  // n-1个矢量
            intervec[i][j].a = (1-t)*beginvec[j].a + t*endvec[j].a;
            // 保证末角度始终大于初角度
            if(endvec[j].theta < beginvec[j].theta){
                intervec[i][j].theta = (1-t)*beginvec[j].theta + t*(endvec[j].theta+2*Pi);
            }else{
                intervec[i][j].theta = (1-t)*beginvec[j].theta + t*endvec[j].theta;
            }
        }
    }

    PolarToRect();
}

void Interpol::veccounterclocklinear(){ // 逆时针旋转
    RectToPolar();

    for(int i = 0; i < polnum; i++){
        float t = (float)i/(float)polnum;
        // 每个图形第一个控制点坐标由线性插值得到
        inter[i][0].x = (1-t)*begin[0].x + t*end[0].x;
        inter[i][0].y = (1-t)*begin[0].y + t*end[0].y;

        for(int j = 0; j < n-1; j++){  // n-1个矢量
            intervec[i][j].a = (1-t)*beginvec[j].a + t*endvec[j].a;
            // 保证末角度始终小于初角度
            if(endvec[j].theta > beginvec[j].theta){
                intervec[i][j].theta = (1-t)*(beginvec[j].theta+2*Pi)+t*endvec[j].theta;
            }else{
                intervec[i][j].theta = (1-t)*beginvec[j].theta + t*endvec[j].theta;
            }
        }
    }

    PolarToRect();
}

void Interpol::PolarToRect(){

    for(int i = 0; i < polnum; i++){
        for(int j = 1; j < n; j++){  // 从第1个控制点开始算到第n个
            inter[i][j].x = inter[i][j-1].x + intervec[i][j-1].a*cos(intervec[i][j-1].theta);
            inter[i][j].y = inter[i][j-1].y + intervec[i][j-1].a*sin(intervec[i][j-1].theta);
        }
    }
}
