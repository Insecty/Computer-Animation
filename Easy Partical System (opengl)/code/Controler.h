/********************
 *    ������������   *
 *     Controler    *
 ********************/
#pragma once

#include "Particle.h"
#include <iostream>
using namespace std;

class Controler
{
private:
	Particle **p;    // ����
	GLuint max_num; // ������
	GLfloat x1, y1; // ���������
	GLfloat x2, y2; // �������յ�
public:
	Controler();
	// ���ι��캯��
	Controler(GLfloat _x1, GLfloat _y1, GLfloat _x2, GLfloat _y2, GLuint _num);
	~Controler();
	// ������������״̬
	void updateAll(Particle* (init)());
	// ��ʼ������
	void emit(Particle* (init)());
};

