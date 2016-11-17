#ifndef GEOMETRIC_QUATERNION
#define GEOMETRIC_QUATERNION

#include "triple.h"

class Quaternion {
	public:
		float w, x, y, z;
		Quaternion(float, float, float, float);
		~Quaternion();
		Quaternion(const Quaternion&);
		void multiply(Quaternion&);
		void rotate(Triple&);
};

void inverse(float&, float&, float&, float&);
void inverse(Quaternion&);
Quaternion fromRotation(float, float, float, float);

#endif //GEOMETRIC_QUATERNION