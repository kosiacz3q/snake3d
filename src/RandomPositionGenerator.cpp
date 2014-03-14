
/*
 * RandomPositionGenerator.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: lucas
 */

#include "RandomPositionGenerator.h"
#include <boost/random.hpp>
#include <math.h>

bool RandomPositionGenerator::reservedMap[6][30][30];

RandomPositionGenerator::RandomPositionGenerator() {}

/**
 *@param wallDim dimensions of brick
 *@param wall if provided number is -1, then wall will be choosen randomly ,otherwise provided number will be used
 *@param zp beginning of the interval of z axis
 *@param zk end of the interval of z axis
 *@param someSeedChange if this method is used in proximity same time then you have to provide some seed
 */
Vector4f RandomPositionGenerator::generate( int** wallDim, const int wall,  int zp ,  int zk , int someSeedChange) {
	boost::mt19937 generator(  time(0) + time_t( someSeedChange));
	boost::uniform_real<float> u01;
	Vector4f resultPosition;

	do{
	if ((wall < 1) || (wall > 6)) {
		resultPosition.w = ((int)(u01(generator)* 100 )% 6) + 1;
	} else {
		resultPosition.w = wall;
	}

	resultPosition.z = ((int)(u01(generator) * 100 ) % (zk -zp) ) + zp;

	switch((int)resultPosition.w){
	case 3:
	case 1:
		resultPosition.x = ((int)(u01(generator)* 100 ) % (wallDim[(int)resultPosition.w - 1][0] - 2))  + 1;
		resultPosition.y = ((int)(u01(generator) * 100) % (wallDim[(int)resultPosition.w - 1][1] - 2))  + 1;
		break;
	case 5:
	case 6:
		resultPosition.x = ((int)(u01(generator)* 100 ) % (wallDim[(int)resultPosition.w - 1][0]  )) ;
		resultPosition.y = ((int)(u01(generator) * 100) % (wallDim[(int)resultPosition.w - 1][1]  )) ;
		break;
	case 4:
	case 2:
		resultPosition.x = ((int)(u01(generator)* 100 ) % (wallDim[(int)resultPosition.w - 1][0] ));
		resultPosition.y = ((int)(u01(generator) * 100) % (wallDim[(int)resultPosition.w - 1][1] - 3 )) + 1 ;
		break;
	}

	}while(!checkPosition(resultPosition));

	return resultPosition;
}

void RandomPositionGenerator::clearReservedPosition(){
	for(int i = 0; i < 6; ++i)
		for(int j = 0; j < 30; ++j)
			for(int k = 0; k < 30; ++k)
				reservedMap[i][j][k] = false;
}

void RandomPositionGenerator::addReservedPosition(const Vector4f& vec){
	reservedMap[(int)vec.w][(int)vec.x][(int)vec.y] = true;
}

void RandomPositionGenerator::removeReservedPosition(const Vector4f& vec){
	reservedMap[(int)vec.w][(int)vec.x][(int)vec.y] = false;
}

bool RandomPositionGenerator::checkPosition(const Vector4f& pos){
	return !reservedMap[(int)pos.w][(int)pos.x][(int)pos.y];
}

int RandomPositionGenerator::getRandomNumber(int start , int end){
	boost::mt19937 generator(  time(0) + time_t( 3));
	boost::uniform_real<float> u01;
	return ((int)(u01(generator)* 100 ) % (end - start + 1) ) + start;
}
