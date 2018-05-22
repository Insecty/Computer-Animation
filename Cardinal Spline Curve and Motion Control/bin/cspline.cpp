#include "CSpline.h"

CSpline::CSpline(){

}

/* Initialization function.
 * @param x[] y[] : control point
 * @param n : number of CPt
 * @param grain : number of interpolation point
 * @param tension : t
 */
CSpline::CSpline(double x[100], double y[100], int n, int grain, float tension){
    CPt jd[100]; // 控制点数组
    CPt *knots;  // 控制点头指针
    this->grain = grain;
    n0 = n;
    int np = n0; // 控制点个数
    for(int i = 1; i <= np; i++){
        jd[i].x = x[i-1];
        jd[i].y = y[i-1];
    }
    // 首部虚拟点赋值
    jd[0].x = x[0];
    jd[0].y = y[0];
    // 尾部虚拟点赋值
    jd[np+1].x = x[n-1];
    jd[np+1].y = y[n-1];
    knots = jd;
    knots0 = knots;
    np += 2; // 算上虚拟点的控制点个数
    CubicSpine(np, knots, grain, tension); // 生成插值点
}

/* This method is used to calculate the cardinal line.
 * @param n : number of control point(including virtual point)
 * @param knots : pointer to CPt array
 * @param grain : number of interpolation point
 * @param tension : t
 */
void CSpline::CubicSpine(int n, CPt *knots, int grain, float tension){
    CPt *s, *k0, *kml, *k1, *k2;
    double alpha[60]; // 参数u

    GetCardinalMatrix(tension); // 根据t计算出矩阵M

    for(int i = 0; i < grain; i++){
        alpha[i] = ((double)i+1.0)/(grain+1);
       //alpha[i] = (double)i/grain;
    }
    s = Spline;  // 插值点头指针
    kml = knots; // 控制点
    k0 = kml+1;
    k1 = k0+1;
    k2 = k1+1;
    for(int i = 1; i < n-2; i++){ // n-1段中间曲线
        for(int j = 0; j < grain; j++){
            s->x = Matrix(kml->x, k0->x, k1->x, k2->x, alpha[j]);
            s->y = Matrix(kml->y, k0->y, k1->y, k2->y, alpha[j]);
            s++;
        }
        k0++; kml++; k1++; k2++;
    }
}

void CSpline::GetCardinalMatrix(float t){
    m[0]=-t;  m[1]=2-t;  m[2]=-2+t;  m[3]=t;
    m[4]=2*t; m[5]=-3+t; m[6]=3-2*t; m[7]=-t;
    m[8]=-t;  m[9]=0;    m[10]=t;    m[11]=0;
    m[12]=0;  m[13]=1;   m[14]=0;    m[15]=0;
}

double CSpline::Matrix(double a, double b, double c, double d, double alpha){
     double p0, p1, p2, p3;
     p0=m[0]*a+m[1]*b+m[2]*c+m[3]*d;
     p1=m[4]*a+m[5]*b+m[6]*c+m[7]*d;
     p2=m[8]*a+m[9]*b+m[10]*c+m[11]*d;
     p3=m[12]*a+m[13]*b+m[14]*c+m[15]*d;
     return(p3+alpha*(p2+alpha*(p1+alpha*p0)));
}


