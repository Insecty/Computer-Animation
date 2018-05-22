#include "Controler.h"

Controler::Controler(){}


Controler::~Controler()
{
	for (int i = 0; i < max_num; i++) {
		delete p[i];
	}
}

Controler::Controler(GLfloat _x1, GLfloat _y1, GLfloat _x2, GLfloat _y2, GLuint _num) {
	x1 = _x1;
	y1 = _y1;
	x2 = _x2;
	y2 = _y2;
	max_num = _num;
	p = new Particle*[max_num];   // 分配空间
}

void Controler::updateAll(Particle* (init)()) {
	for (int i = 0; i < max_num; i++) {
		p[i]->show();
		if (p[i]->getTTL() < 0) {  // 重生“死亡”的粒子
			delete p[i];
			int place = rand() % max_num;
			p[i] = init(); // 重新发射一个粒子
			GLfloat x = 1.0f * place / max_num*(x2 - x1) + x1; // x在x1-x2范围内
			GLfloat y = 1.0f * place / max_num*(y2 - y1) + y1; // y在y1-y2范围内
			p[i]->setPos(x, y);
		}
	}
}

void Controler::emit(Particle* (init)()) {
	for (int i = 0; i < max_num; i++) {
		p[i] = init(); // 初始化所有粒子 分配空间并设置参数
		int place = rand() % max_num;
		GLfloat x = 1.0f * place / max_num*(x2 - x1) + x1; // x在x1-x2范围内
		GLfloat y = 1.0f * place / max_num*(y2 - y1) + y1; // y在y1-y2范围内
		p[i]->setPos(x, y);
	}
}

