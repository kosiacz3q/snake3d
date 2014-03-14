/*
 * MouseHandler.cpp
 *
 *  Created on: Jul 29, 2013
 *      Author: lucas
 */

#include <GL/glut.h>

#include "MouseHandler.h"


MouseHandler::MouseHandler() {
	this->leftButtonState = GLUT_UP;
	this->rightButtonState = GLUT_UP;
	this->actualPosition = Vector2f();
	this->lastPosition = this->actualPosition;
}

MouseHandler::~MouseHandler() {

}

void MouseHandler::setMousePosition(const int& x ,const int& y){
	this->lastPosition = this->actualPosition;
	this->actualPosition.x = x;
	this->actualPosition.y = y;
}
