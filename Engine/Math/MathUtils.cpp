#include "MathUtils.h"

namespace math
{
	

	inline float DegToRad(float degrees)
	{
		return degrees * (Pi / 180);
	}

	inline float RedToDeg(float radians)
	{
		return radians * (180 / Pi);
	}

	int sqr(int v){ return v * v;}
}
