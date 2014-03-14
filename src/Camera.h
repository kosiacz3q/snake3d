#ifndef CAMERA_H
#define CAMERA_H

#include <GL/freeglut.h>


#include "Vectorf.h"

class Camera
{
    public:

		static void updatePosition(Vector3f snakeHead);
		static void setVision();
		static void setStaticVision();
		static void reset();
		static void setPosition(Vector3f pos);
		static Vector3f lastSnakeHead;
        static float distanceFromCenter;
        static Vector3f lastPosition;
        static Vector3f position;
        static Vector3f lookPoint;
        static Vector3f verticalTurn;
        static Vector3f verticalTurnToReach;
        static Vector3f rotate;
        static Vector3f positionToReach;

    protected:
    private:
        static bool firstUpdate;

        Camera();
};

#endif // CAMERA_H
