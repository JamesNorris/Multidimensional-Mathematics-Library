#include "quat.h"
#include <math.h>

void inverse(float& w, float& x, float& y, float& z) {
	float scale = 1.0 / (x * x + y * y + z * z + w * w);
	w *= scale;
	x *= -scale;
	y *= -scale;
	z *= -scale;
}

void inverse(Quaternion& quat) {
	inverse(quat.w, quat.x, quat.y, quat.z);
}

Quaternion fromRotation(float rot, float x, float y, float z) {
	float len = sqrt(x * x + y * y + z * z);
	float s = sin(rot / 2.0);
	float c = cos(rot / 2.0);
	float tmp = s / len;
	return Quaternion(c, x * tmp, y * tmp, z * tmp);
}

Quaternion::Quaternion(float w, float x, float y, float z) {
	this->w = w;
	this->x = x;
	this->y = y;
	this->z = z;
}

Quaternion::~Quaternion() {}

Quaternion::Quaternion(const Quaternion& other) : w(other.w), x(other.x), y(other.y), z(other.z) {}

void Quaternion::multiply(Quaternion& other) {
	float qx = other.x, qy = other.y, qz = other.z, qw = other.w;
	other.w = w * qw - x * qx - y * qy - z * qz;
	other.x = w * qx + x * qw + y * qz - z * qy;
	other.y = w * qy + y * qw + z * qx - x * qz;
	other.z = w * qz + z * qw + x * qy - y * qx;
}

void Quaternion::rotate(Triple& pt) {
	float iw = w, ix = x, iy = y, iz = z;//temps
	inverse(iw, ix, iy, iz);
	float tx = pt.x, ty = pt.y, tz = pt.z;
	float aw = -x * tx - y * ty - z * tz;
	float ax = w * tx + y * tz - z * ty;
	float ay = w * ty + z * tx - x * tz;
	float az = w * tz + x * ty - y * tx;
	pt.x = aw * ix + ax * iw + ay * iz - az * iy;
	pt.y = aw * iy + ay * iw + az * ix - ax * iz;
	pt.z = aw * iz + az * iw + ax * iy - ay * ix;
}