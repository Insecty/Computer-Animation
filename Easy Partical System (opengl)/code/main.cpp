/*******************
 *    ���������    *
 *     main.cpp    *
 *******************/

#include <GL/glew.h>
#include <Windows.h>
#include <GL/GLAUX.H>
#include <GL/glut.h>
#include <iostream>
#include "texture.h"
#include "Controler.h"

using namespace std;

GLuint texture_bgid; // ���������ʶ��
GLuint texture_snow; // ��ͼ�����ʶ��
GLuint height, width;
// �۲�λ��
GLfloat center[3] = { 0.0, 0.0, 0.0 };
// ��������
GLfloat eye[3] = { 0.0, 0.0, 120.0 };

/* ������ */
Controler *c_snow; // ѩ��/��Ҷ
Controler *c_fire1, *c_fire2, *c_fire3, *c_fire4; // �̻�
Controler *c_water; // ��Ȫ
Controler *c_burn; // ����

/*   �̻��������ӳ�ʼ������    */
Particle* initFire1() {
	GLfloat r = rand() % 20 * 0.02f;
	GLuint color[3] = { 1.0f,0.0f,0.0f };
	Particle* p = new Particle();
	p->initParticle(r, rand() % 100, GLfloat(rand() % 10 - 5) / 80, GLfloat(rand() % 10 - 5) / 80,
		0, -4.9/40000, rand() % 80, false, false, -1, color[0], color[1], color[2]);
	return p;
}

Particle* initFire2() {
	GLfloat r = rand() % 20 * 0.02f;
	GLuint color[3] = { 1.0f,0.0f,1.0f };
	Particle* p = new Particle();
	p->initParticle(r, rand() % 80, GLfloat(rand() % 10 - 5) / 80, GLfloat(rand() % 10 - 5) / 80,
		0, -4.9 / 40000, rand() % 80, false, false, -1, color[0], color[1], color[2]);
	return p;
}

Particle* initFire3() {
	GLfloat r = rand() % 20 * 0.02f;
	GLuint color[3] = { 1.0f,1.0f,0.0f };
	Particle* p = new Particle();
	p->initParticle(r, rand() % 100, GLfloat(rand() % 10 - 5) / 80, GLfloat(rand() % 10 - 5) / 80,
		0, -4.9 / 40000, rand() % 80, false, false, -1, color[0], color[1], color[2]);
	return p;
}

Particle* initFire4() {
	GLfloat r = rand() % 20 * 0.02f;
	GLuint color[3] = { 0.0f,1.0f,1.0f };
	Particle* p = new Particle();
	p->initParticle(r, rand() % 100, GLfloat(rand() % 10 - 5) / 80, GLfloat(rand() % 10 - 5) / 80,
		0, -4.9 / 40000, rand() % 80, false, false, -1, color[0], color[1], color[2]);
	return p;
}

/*   ��Ҷ/ѩ���������ӳ�ʼ������   */
Particle* initParticles() {
	//GLfloat r = rand() % 100 * 0.02f; // snow
	GLfloat r = (rand() % 50 + 50) * 0.08f; // leaf
	GLuint color[3] = { 1.0f,0.0f,0.0f }; // ָ����ɫ

	Particle* p = new Particle();
	p->initParticle(r, rand() % 800, GLfloat(rand()%10) / 80, GLfloat(rand() % 10-8) / 40,
		1.0 / 10000, -8.9 / 40000, rand() % 360, false, true, texture_snow, color[0], color[1], color[2]);
	return p;
}

/*   ��Ȫ�������ӳ�ʼ������   */
Particle* initWater() {
	GLfloat r = (rand() % 50) *0.02f;
	Particle *p = new Particle();
	p->initParticle(r, rand() % 60, GLfloat(rand() % 10 - 4) / 38, GLfloat(rand() % 100) / 200 + 0.5,
		0, -4.9 / 1000, rand() % 80, false, true, texture_snow, 0, 0, 0);
	return p;
}

/*   ȼ�ղ������ӳ�ʼ������   */
Particle* initBurn() {
	GLfloat r = (rand() % 50) *0.02f;
	Particle *p = new Particle();
	p->initParticle(r, rand() % 50, GLfloat(rand() % 10 - 4) / 80, GLfloat(rand() % 10-2) / 40 ,
		0, -4.9 / 80000, rand() % 80, false, true, texture_snow, 0, 0, 0);
	return p;
}


// ����ģʽ��ʼ��
void init(void) 
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);   // ������Ȳ���
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);  // ͼ����ģʽ
	glEnable(GL_BLEND);

	// ������
	BuildTexture("snowbg.jpg", texture_bgid);
	BuildTexture("snowflower.jpg", texture_snow);

    // ѩ����������
	c_snow = new Controler(-140, 120, -10, 180, 50);
	c_snow->emit(initParticles);
	
	// �̻���������
	//c_fire1 = new Controler(0, 20, 0, 20, 100);
	//c_fire2 = new Controler(0, 20, 0, 20, 100);
	//c_fire3 = new Controler(0, 20, 0, 20, 100);
	//c_fire4 = new Controler(0, 20, 0, 20, 100);
	// c_fire1 = new Controler(12, 5, 12, 5, 500);
	// c_fire1->emit(initFire1);
	// c_fire2 = new Controler(30, 50, 30, 50, 400);
	// c_fire2->emit(initFire2);
	// c_fire3 = new Controler(-50, 42, -50, 42, 400);
	// c_fire3->emit(initFire3);
	// c_fire4 = new Controler(-18, -18, -18, -18, 500);
	// c_fire4->emit(initFire4);

	// ��Ȫ�������� 
	//c_water = new Controler(0, -60, 0, -60, 5000);
	//c_water->emit(initWater);

	// ���淢������
	//c_burn = new Controler(-12, -10, 18, -10, 5000);
	//c_burn->emit(initBurn);
}

// �ı���Ļ�ֱ���ʱ����
void reshape(GLint w, GLint h) {
	if (h == 0)
		h = 1;
	height = h;
	width = w;
	
	// �����ӽ�
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat wradio = (GLfloat)w / (GLfloat)h;
	gluPerspective(60.0, wradio, 1.0, 501.0); // ͸��ͶӰ
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0.0, 1.0, 0.0); //�۲췽��

}

// ����ʱ����
void idle(void) {
	glutPostRedisplay();
}

// ���ƻ���/��ʾ������
void display(void) {
	// ���Ʊ���
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture_bgid);
	glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex3f(-130.0, -120.0, -1.0);
		glTexCoord2f(1, 0); glVertex3f(130.0, -120.0, -1.0);
		glTexCoord2f(1, 1); glVertex3f(130.0, 120.0, -1.0);
		glTexCoord2f(0, 1); glVertex3f(-130.0, 120.0, -1.0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// ˢ������
	c_snow->updateAll(initParticles);
	//c_fire1->updateAll(initFire1);
	//c_fire2->updateAll(initFire2);
	//c_fire3->updateAll(initFire3);
	//c_fire4->updateAll(initFire4);
	//c_water->updateAll(initWater);
	//c_burn->updateAll(initBurn);

	// ˢ����Ļ
	glutSwapBuffers();
}


int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);   // ��ʾģʽ��ʼ��
	glutInitWindowSize(500, 500);      // ���ڴ�С
	glutInitWindowPosition(100, 100);  // ����λ��
	glutCreateWindow("Particle System");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);   // ��ʾ
	glutIdleFunc(idle);         // ����ʱ������Ļ

	init(); // ��ʼ��
	glutMainLoop();

	return 0;
}

