#include "Camera.h"
#include <math.h>

Vector3f Camera::position = Vector3f( 0. , 0. , 0.);
Vector3f Camera::positionToReach = Vector3f( 0. , 0. , 0.);
Vector3f Camera::verticalTurnToReach = Vector3f(0. , 1. , 0.);
Vector3f Camera::lookPoint = Vector3f( 0. , 0. , 0.);
Vector3f Camera::verticalTurn = Vector3f( 0. ,  1. , 0.);
Vector3f Camera::rotate = Vector3f(0. , 0. , 0.);
Vector3f Camera::lastPosition = Vector3f(0. , 0. , 0.);
Vector3f Camera::lastSnakeHead = Vector3f( -0.0 , -0.0 , -0.0);
float Camera::distanceFromCenter = 3;
bool Camera::firstUpdate = true;

void Camera::reset(){
	Camera::position.reset();
	Camera::positionToReach.reset();
	Camera::verticalTurnToReach.reset();
	Camera::verticalTurnToReach.y = 1.;
	Camera::lookPoint.reset();
	Camera::verticalTurn.reset();
	Camera::verticalTurn.y = 1.;
	Camera::rotate.reset();
	Camera::lastPosition.reset();
	Camera::lastSnakeHead.reset();
}

void Camera::updatePosition(Vector3f snakeHead){
	if(!(position == positionToReach))
		position -= Vector3f::getPartOfDiffrence(position , positionToReach , 0.1 );

	Vector3f::moveCloseToVector(verticalTurnToReach, verticalTurn , 0.1);

	if(firstUpdate){
		firstUpdate = false;
		lastSnakeHead = snakeHead;
	}

	float c = pow(snakeHead.x , 2.) + pow(snakeHead.y , 2.) + pow(snakeHead.z , 2.);
	float t ;

	if(c != 0){
		lastPosition = position;

		t = sqrt( pow(distanceFromCenter , 2) / c );
		positionToReach.x = t * snakeHead.x;
		positionToReach.y = t * snakeHead.y;
		positionToReach.z = t * snakeHead.z;

		positionToReach.smooth( lastPosition , 0.001 );

		if( ! (snakeHead == lastSnakeHead)){
			verticalTurnToReach = (snakeHead - lastSnakeHead) * 10;
			/*
			std::cout<<"x "<<verticalTurnToReach.x <<"  y "<<verticalTurnToReach.y<<" z "<<verticalTurnToReach.z<<" | "
					 <<"x "<<verticalTurn.x <<"  y "<<verticalTurn.y<<" z "<<verticalTurn.z<<"\n";
			 */
			lastSnakeHead = snakeHead;
		}
	}else{
		//theoretically impossible
	}
}

void Camera::setVision(){
    gluLookAt( position.x , position.y, position.z ,
               lookPoint.x , lookPoint.y , lookPoint.z,
               verticalTurn.x , verticalTurn.y , verticalTurn.z);

   glRotatef(Camera::rotate.x , 0. , 1. , 0.);
   glRotatef(Camera::rotate.y , 1. , 0. , 0.);
   glRotatef(Camera::rotate.z , 0. , 0. , 1.);
}

void Camera::setStaticVision(){
	gluLookAt(0 ,0, 3,
		   0 , 0 , 0,
		   0 , 1. , 0);
}

void Camera::setPosition(Vector3f pos){
	position = pos;
	positionToReach = pos;
}

Camera::Camera()
{

}
