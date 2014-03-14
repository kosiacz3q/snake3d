/*
 * Menu.h
 *
 *  Created on: Sep 27, 2013
 *      Author: lucas
 */

#ifndef MENU_H_
#define MENU_H_

class Menu {
public:

	static void init();
	static void close();
	static void update();
	static void performKeyboardInput( unsigned char key, int x, int y );
	static void performSpecialKeyboardInput(  int key, int x, int y  );
	static void performMouseDragg( int x, int y );
	static void performMouseAction(int button, int state, int x, int y);
	static void reshape( int width, int height );
	static void performMouseMove(int x , int y);
	static void drawAll();
private:
	static void drawString(const char* , int length,const  float x,const  float y,const  float z);
	Menu();

};

#endif /* MENU_H_ */
