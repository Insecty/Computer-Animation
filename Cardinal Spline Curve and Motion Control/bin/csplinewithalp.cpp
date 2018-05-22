#include "csplinewithalp.h"
#include <math.h>

CSplineWithALP::CSplineWithALP(double x[100], double y[100], int n, int grain, float tension)
{
    CPt jd[100];  // 控制点数组
    CPt *knots;   // 控制点头指针
    n0 = n;
    this->grain = grain;
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

    a[0] = new float[n-1];
    b[0] = new float[n-1];
    c[0] = new float[n-1];
    d[0] = new float[n-1];

    a[1] = new float[n-1];
    b[1] = new float[n-1];
    c[1] = new float[n-1];
    d[1] = new float[n-1];

    CubicSpine(np, knots, grain, tension); // 生成插值点
}

void CSplineWithALP::CubicSpine(int n, CPt *knots, int grain, float tension){
    CPt *s, *k0, *kml, *k1, *k2, *ss;
    float alpha[60]; // 参数u

    GetCardinalMatrix(tension); // 根据t计算出矩阵M

    for(int i = 0; i < grain; i++){
        alpha[i] = ((float)i)/grain;
    }
    s = Spline;  // 插值点头指针
    ss = SplineWithALP; // 参数化后插值点头指针
    kml = knots; // 控制点
    k0 = kml+1;
    k1 = k0+1;
    k2 = k1+1;
    for(int i = 0; i < n-3; i++){ // n-1段中间曲线
        init(0,i,kml->x,k0->x,k1->x,k2->x);
        init(1,i,kml->y,k0->y,k1->y,k2->y);
        for(int j = 0; j < grain; j++){ // 算出原始插值点
            s->x = Matrix(0, i, alpha[j]);
            s->y = Matrix(1, i, alpha[j]);
            s++;
        }
        initLength();
        float length = getLen(i,1.0f);
        for(int j = 0; j < grain; j++){ // 重新插值
            float ssnow = length/grain*j;
            float unow = getU(i, ssnow, 0.0f, 1.0f);
            ss->x = Matrix(0, i, unow);
            ss->y = Matrix(1, i, unow);
            ss++;
        }
        k0++; kml++; k1++; k2++;
    }
}

float CSplineWithALP::f(int i,float x){
    return sqrt(((((A[i]*x+B[i])*x)+C[i])*x+D[i])*x+E[i]);
}

float CSplineWithALP::getLen(int i,float u){
    return simpson(i,0,u);
}

float CSplineWithALP::simpson(int j,float x,float y)
{   // 从x到y 第j段曲线的simpson积分计算
    const int n = 10; // 10阶
    const float h = (y - x)/n;
    float ans = 0.0f;
    for(int i=1;i<=n-1;i++){
        if(i%2){
            ans += 4*f(j,x+1.0f*i/n*(y-x));
        }
        else ans += 2*f(j,x+1.0f*i/n*(y-x));
    }
    ans += f(j,x) + f(j,y); // 第一项和最后一项
    ans *= h/3;

    return ans;
}

void CSplineWithALP::GetCardinalMatrix(float t){
    m[0]=-t;  m[1]=2-t;  m[2]=-2+t;  m[3]=t;
    m[4]=2*t; m[5]=-3+t; m[6]=3-2*t; m[7]=-t;
    m[8]=-t;  m[9]=0;    m[10]=t;    m[11]=0;
    m[12]=0;  m[13]=1;   m[14]=0;    m[15]=0;
}

void CSplineWithALP::initLength(){
    int n = n0;
    A = new float[n-1];
    B = new float[n-1];
    C = new float[n-1];
    D = new float[n-1];
    E = new float[n-1];
    for(int i=0;i<n-1;i++){
       A[i] = 9*(a[0][i]*a[0][i]+a[1][i]*a[1][i]);
       B[i] = 12*(a[0][i]*b[0][i]+a[1][i]*b[1][i]);
       C[i] = 6*(a[0][i]*c[0][i]+a[1][i]*c[1][i]) + 4*(b[0][i]*b[0][i]+b[1][i]*b[1][i]);
       D[i] = 4*(b[0][i]*c[0][i]+b[1][i]*c[1][i]);
       E[i] = c[0][i]*c[0][i]+c[1][i]*c[1][i];
    }
}

float CSplineWithALP::getU(int i,float s,float u1,float u2){
    // 二分法计算在u1和u2之间满足弧长为s的u值
    // 关于第i段曲线
    float ms = getLen(i,(u1+u2)/2);
    if(ms-s>-1.0f && ms-s<1.0f){
        return (u1+u2)/2;
    }
    else if(ms > s)return getU(i,s,u1,(u1+u2)/2); // 递归继续寻找
    else if(ms < s)return getU(i,s,(u1+u2)/2,u2);
}

void CSplineWithALP::init(int i,int j,float a0, float b0, float c0, float d0)
{
    a[i][j] = m[0] * a0 + m[1] * b0 + m[2] * c0 + m[3] * d0;
    b[i][j] = m[4] * a0 + m[5] * b0 + m[6] * c0 + m[7] * d0;
    c[i][j] = m[8] * a0 + m[9] * b0 + m[10] * c0 + m[11] * d0;
    d[i][j] = m[12] * a0 + m[13] * b0 + m[14] * c0 + m[15] * d0;
}

float CSplineWithALP::Matrix(int i, int j,float u)
{
    return(d[i][j] + u*(c[i][j] + u*(b[i][j] + u*a[i][j])));
}
