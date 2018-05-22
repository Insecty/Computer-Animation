/*******************
 *    主程序入口    *
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

GLuint texture_bgid; // 背景纹理标识符
GLuint texture_snow; // 贴图纹理标识符
GLuint height, width;
// 观察位置
GLfloat center[3] = { 0.0, 0.0, 0.0 };
// 视线中心
GLfloat eye[3] = { 0.0, 0.0, 120.0 };

/* 发射器 */
Controler *c_snow; // 雪花/落叶
Controler *c_fire1, *c_fire2, *c_fire3, *c_fire4; // 烟花
Controler *c_water; // 喷泉
Controler *c_burn; // 火焰

/*   烟花部分粒子初始化函数    */
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

/*   落叶/雪花部分粒子初始化函数   */
Particle* initParticles() {
	//GLfloat r = rand() % 100 * 0.02f; // snow
	GLfloat r = (rand() % 50 + 50) * 0.08f; // leaf
	GLuint color[3] = { 1.0f,0.0f,0.0f }; // 指定颜色

	Particle* p = new Particle();
	p->initParticle(r, rand() % 800, GLfloat(rand()%10) / 80, GLfloat(rand() % 10-8) / 40,
		1.0 / 10000, -8.9 / 40000, rand() % 360, false, true, texture_snow, color[0], color[1], color[2]);
	return p;
}

/*   喷泉部分粒子初始化函数   */
Particle* initWater() {
	GLfloat r = (rand() % 50) *0.02f;
	Particle *p = new Particle();
	p->initParticle(r, rand() % 60, GLfloat(rand() % 10 - 4) / 38, GLfloat(rand() % 100) / 200 + 0.5,
		0, -4.9 / 1000, rand() % 80, false, true, texture_snow, 0, 0, 0);
	return p;
}

/*   燃烧部分粒子初始化函数   */
Particle* initBurn() {
	GLfloat r = (rand() % 50) *0.02f;
	Particle *p = new Particle();
	p->initParticle(r, rand() % 50, GLfloat(rand() % 10 - 4) / 80, GLfloat(rand() % 10-2) / 40 ,
		0, -4.9 / 80000, rand() % 80, false, true, texture_snow, 0, 0, 0);
	return p;
}


// 各类模式初始化
void init(void) 
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);   // 开启深度测试
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);  // 图像混合模式
	glEnable(GL_BLEND);

	// 绑定纹理
	BuildTexture("snowbg.jpg", texture_bgid);
	BuildTexture("snowflower.jpg", texture_snow);

    // 雪花发射器类
	c_snow = new Controler(-140, 120, -10, 180, 50);
	c_snow->emit(initParticles);
	
	// 烟花发射器类
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

	// 喷泉发射器类 
	//c_water = new Controler(0, -60, 0, -60, 5000);
	//c_water->emit(initWater);

	// 火焰发射器类
	//c_burn = new Controler(-12, -10, 18, -10, 5000);
	//c_burn->emit(initBurn);
}

// 改变屏幕分辨率时调用
void reshape(GLint w, GLint h) {
	if (h == 0)
		h = 1;
	height = h;
	width = w;
	
	// 更新视角
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLfloat wradio = (GLfloat)w / (GLfloat)h;
	gluPerspective(60.0, wradio, 1.0, 501.0); // 透视投影
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eye[0], eye[1], eye[2], center[0], center[1], center[2], 0.0, 1.0, 0.0); //观察方向

}

// 空闲时调用
void idle(void) {
	glutPostRedisplay();
}

// 控制绘制/显示主函数
void display(void) {
	// 绘制背景
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

	// 刷新粒子
	c_snow->updateAll(initParticles);
	//c_fire1->updateAll(initFire1);
	//c_fire2->updateAll(initFire2);
	//c_fire3->updateAll(initFire3);
	//c_fire4->updateAll(initFire4);
	//c_water->updateAll(initWater);
	//c_burn->updateAll(initBurn);

	// 刷新屏幕
	glutSwapBuffers();
}


int main(int argc, char** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);   // 显示模式初始化
	glutInitWindowSize(500, 500);      // 窗口大小
	glutInitWindowPosition(100, 100);  // 窗口位置
	glutCreateWindow("Particle System");

	glutReshapeFunc(reshape);
	glutDisplayFunc(display);   // 显示
	glutIdleFunc(idle);         // 空闲时更新屏幕

	init(); // 初始化
	glutMainLoop();

	return 0;
}

