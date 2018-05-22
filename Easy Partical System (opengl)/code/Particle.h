/********************
 *      ������      *
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
	GLfloat pos_x, pos_y; // xy����
	GLfloat r; // �뾶
	GLfloat ttl; // time to live
	GLfloat vx, vy; // �ٶ�
	GLfloat ax, ay; // ���ٶ�
	GLfloat angle;  // �Ƕ�
	bool isForever; // ������ʧ
	bool isTex; // ������ͼ/��ɫ
	GLuint textureid; // �����ʶ��
	GLuint color[3];
	
public:
	Particle();
	~Particle();
	// ������λ����Ĳ�����ʼ��(λ�ø��ݷ�����controler����)
	void initParticle(GLfloat _r, GLfloat _ttl, GLfloat _vx, GLfloat _vy, GLfloat _ax,
		GLfloat _ay, GLfloat _angle, bool _isForever, bool _isTex,
		GLuint _textureid, GLuint colorr, GLuint colorg, GLuint colorb);
	// ���Ƹ����� ʹ�õ�һ��ɫ��QUADS
	void drawColor();
	// ���Ƹ�����
	void drawTex(GLuint textureid);
	// �������Ӳ����û��ƺ���
	void show();
	// ���������� ��������λ��
	void setPos(GLfloat x, GLfloat y);
	// ������������ ��ȡ��������״̬
	GLfloat getTTL() { return ttl; };
};

