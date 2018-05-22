/********************
 *      粒子类      *
 *     Particle     *
 ********************/
#define GLUT_DISABLE_ATEXIT_HACK  
#include <gl/glew.h>
#include <Windows.h>
#include <gl/glaux.h>
#include <gl/glut.h>
using namespace std;

#pragma once
class Particle
{
private:
	GLfloat pos_x, pos_y; // xy坐标
	GLfloat r; // 半径
	GLfloat ttl; // time to live
	GLfloat vx, vy; // 速度
	GLfloat ax, ay; // 加速度
	GLfloat angle;  // 角度
	bool isForever; // 不会消失
	bool isTex; // 纹理贴图/颜色
	GLuint textureid; // 纹理标识符
	GLuint color[3];
	
public:
	Particle();
	~Particle();
	// 除粒子位置外的参数初始化(位置根据发射器controler控制)
	void initParticle(GLfloat _r, GLfloat _ttl, GLfloat _vx, GLfloat _vy, GLfloat _ax,
		GLfloat _ay, GLfloat _angle, bool _isForever, bool _isTex,
		GLuint _textureid, GLuint colorr, GLuint colorg, GLuint colorb);
	// 绘制该粒子 使用单一颜色的QUADS
	void drawColor();
	// 绘制该粒子
	void drawTex(GLuint textureid);
	// 更新粒子并调用绘制函数
	void show();
	// 发射器调用 设置粒子位置
	void setPos(GLfloat x, GLfloat y);
	// 发射器更新用 获取粒子生存状态
	GLfloat getTTL() { return ttl; };
};

