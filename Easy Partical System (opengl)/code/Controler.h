/********************
 *    发射器控制类   *
 *     Controler    *
 ********************/
#pragma once

#include "Particle.h"
#include <iostream>
using namespace std;

class Controler
{
private:
	Particle **p;    // 粒子
	GLuint max_num; // 粒子数
	GLfloat x1, y1; // 发射器起点
	GLfloat x2, y2; // 发射器终点
public:
	Controler();
	// 含参构造函数
	Controler(GLfloat _x1, GLfloat _y1, GLfloat _x2, GLfloat _y2, GLuint _num);
	~Controler();
	// 更新所有粒子状态
	void updateAll(Particle* (init)());
	// 初始化粒子
	void emit(Particle* (init)());
};

