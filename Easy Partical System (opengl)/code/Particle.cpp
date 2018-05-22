#include "Particle.h"

Particle::Particle(){}

Particle::~Particle(){}

void Particle::initParticle(GLfloat _r, GLfloat _ttl, GLfloat _vx, GLfloat _vy, GLfloat _ax,
	GLfloat _ay, GLfloat _angle, bool _isForever, bool _isTex, 
	GLuint _textureid, GLuint colorr, GLuint colorg, GLuint colorb)
{
	r = _r;
	ttl = _ttl;
	vx = _vx;
	vy = _vy;
	ax = _ax;
	ay = _ay;
	angle = _angle;
	isForever = _isForever;
	isTex = _isTex;
	if (isTex)
		textureid = _textureid;
	else {
		color[0] = colorr;
		color[1] = colorg;
		color[2] = colorb;
	}
}

void Particle::drawColor()
{
	glBegin(GL_QUADS);  // ������������Ƭ
		glVertex2f(-r, -r);
		glVertex2f(r, -r);
		glVertex2f(r, r);
		glVertex2f(-r, r);
	glEnd();
}

void Particle::drawTex(GLuint textureid)
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureid);
	glBegin(GL_QUADS);  // ʹ�����������������Ƭ
		glTexCoord2f(0, 0); glVertex2f(-r, -r);
		glTexCoord2f(1, 0); glVertex2f(r, -r);
		glTexCoord2f(1, 1); glVertex2f(r, r);
		glTexCoord2f(0, 1); glVertex2f(-r, r);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void Particle::show() // ��������
{
	if (ttl > 0.0f || isForever) { // ���ӻ����򲻻���ʧ
		if (isTex) { // ������ʹ��������ͼ
			glDepthMask(GL_FALSE);
			glPushMatrix();
				glTranslated(pos_x, pos_y, 0); // ƽ��
				glRotated(angle+(rand()%10-5), 0, 0, 1); // ��ת
				//glRotated(angle, 0, 0, 1);
				drawTex(textureid);            // ��������
			glPopMatrix();
			// �����ٶ� λ��
			pos_x += vx;
			pos_y += vy;
			vx += ax;
			vy += ay;
			if (!isForever)
				ttl -= 0.2f;
			glDepthMask(GL_TRUE);
		}
		else { // ������ʹ����ɫ
			glPushMatrix();
			glColor3f((GLfloat)color[0], (GLfloat)color[1], (GLfloat)color[2]);
				glTranslated(pos_x, pos_y, 0);
				glRotated(angle, 0, 0, 1); 
				drawColor();
			glPopMatrix();
			
			// �����ٶ� λ��
			pos_x += vx;
			pos_y += vy;
			vx += ax;
			vy += ay;
			if (!isForever)
				ttl -= 0.2f;
			glColor3f(1, 1, 1); // ������ɫ ȱ����һ���򱳾�������ʾ����
		}
	}
}

void Particle::setPos(GLfloat x, GLfloat y) {
	pos_x = x;
	pos_y = y;
}