/*
 * SnakeAbilities.cpp
 *
 *  Created on: Jan 3, 2014
 *      Author: lucas
 */

#include "SnakeAbilities.h"
#include "Colors.h"
#include "ShapeGenerator.h"

Texture SnakeAbilities::jumpTexture;
Texture SnakeAbilities::speedTexture;

SnakeAbilities::SnakeAbilities(const Vector3f& vec) {
	position = vec;
	rotation = Vector3f();
	activeBoost = Message::BOOST_USED;
}

SnakeAbilities::~SnakeAbilities() {

}

void SnakeAbilities::draw(){

	glPushMatrix();

	glTranslatef( this->position.x , this->position.y, this->position.z );

	glRotatef(this->rotation.x  , 0. , 1. , 0.);
	glRotatef(this->rotation.y , 1. , 0. , 0.);
	glRotatef(this->rotation.z , 0. , 0. , 1.);

	glScalef(0.5 , 0.5 , 0.5);

	glEnable(GL_TEXTURE_2D);


	if(activeBoost == Message::BOOST_OBTAINED_JUMP){
		glColor4fv(Colors::Orange);
		glBindTexture(GL_TEXTURE_2D , jumpTexture.mTextureID);
	}else if(activeBoost == Message::BOOST_OBTAINED_SPEED){
		glBindTexture(GL_TEXTURE_2D , speedTexture.mTextureID);
		glColor4fv(Colors::Red);
	}else{
		glBindTexture(GL_TEXTURE_2D , 0);
		glColor4fv(Colors::Gray);
	}

	glBegin(GL_QUADS);
		glTexCoord2f (0.0, 0.0);
		glVertex3f (-1 , 1 , 0); //upper left
		glTexCoord2f (1.0, 0.0);
		glVertex3f (1 , 1 , 0); //upper right
		glTexCoord2f (1.0, 1.0);
		glVertex3f (1 , -1 , 0); //bottom right
		glTexCoord2f (0.0, 1.0);
		glVertex3f (-1 , -1 , 0); //bottom left
	glEnd();

	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void SnakeAbilities::setRotation(const Vector3f vec){
	this->rotation.x = vec.x;
	this->rotation.y = vec.y;
	this->rotation.z = vec.z;
}

void SnakeAbilities::init(){
	jumpTexture.loadTextureFromFile("/home/lucas/Workspace/Snake3d/tex/tex_jump.png");
	speedTexture.loadTextureFromFile("/home/lucas/Workspace/Snake3d/tex/tex_speed.png");
}

void SnakeAbilities::free(){
	jumpTexture.freeTexture();
	speedTexture.freeTexture();
}

void SnakeAbilities::setActiveAbility(Message::Notification e){
	this->activeBoost = e;
}
