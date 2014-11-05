#ifndef RANDOMPOSITIONGENERATOR_H_
#define RANDOMPOSITIONGENERATOR_H_

#include "Vectorf.h"
#include "MapObject.h"
#include <set>
#include <utility>

class RandomPositionGenerator
{
	public:
		/**
		 *@param wall -1 if any wall ,otherwise specified wall will be used
		 */
		static Vector4f generate(int** wallDim, const int wall, int zp, int zk, int someSeedChange);

		static void clearReservedPosition();
		static void addReservedPosition(const Vector4f&);
		static void removeReservedPosition(const Vector4f&);
		//returns true if there is no object on specified position ,otherwise returns false
		static bool checkPosition(const Vector4f&);
		static int getRandomNumber(int start, int end);

	private:

		static bool reservedMap[6][30][30];
		RandomPositionGenerator();
};

#endif /* RANDOMPOSITIONGENERATOR_H_ */
