#include "math3d.h"

VECTOR3D Add(VECTOR3D a, VECTOR3D b)
{
	VECTOR3D ret;

	ret.x = a.x + b.x;
	ret.y = a.y + b.y;
	ret.z = a.z + b.z;

	return ret;
}

VECTOR3D Substract(VECTOR3D a, VECTOR3D b) 
{
	VECTOR3D ret;

	ret.x = a.x - b.x;
	ret.y = a.y - b.y;
	ret.z = a.z - b.z;

	return ret;
}

VECTOR3D Multiply(VECTOR3D a, VECTOR3D b)
{
	VECTOR3D ret;

	ret.x = a.x * b.y;
	ret.y = a.y * b.y;
	ret.z = a.z * b.z;

	return ret;
}

VECTOR3D MultiplyWithScalar(float scalar, VECTOR3D a)
{
	VECTOR3D ret;

	ret.x = a.x * scalar;
	ret.y = a.y * scalar;
	ret.z = a.z * scalar;

	return ret;
}

double Magnitude(VECTOR3D a)
{
	return sqrt((a.x*a.x) + (a.y*a.y) + (a.z*a.z));
}

VECTOR3D Normalize(VECTOR3D a)
{
	VECTOR3D ret;
	double magnitude = Magnitude(a);

	ret.x = a.x / magnitude;
	ret.y = a.y / magnitude;
	ret.z = a.z / magnitude;

	return ret;
}

VECTOR3D CrossProduct(VECTOR3D a, VECTOR3D b) 
{
	VECTOR3D ret;

	ret.x = a.y*b.z - a.z*b.y;
	ret.y = a.z*b.x - a.x*b.z;
	ret.z = a.x*b.y - a.y*b.x;

	return ret;
}

double DotProduct(VECTOR3D a, VECTOR3D b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}


MATRIX3 Transpose(MATRIX3 m) 
{
	MATRIX3 ret;

	ret.column0.x = m.column0.x;
	ret.column1.x = m.column0.y;
	ret.column2.x = m.column0.z;

	ret.column0.y = m.column1.x;
	ret.column1.y = m.column1.y;
	ret.column2.y = m.column1.z;

	ret.column0.z = m.column2.x;
	ret.column1.z = m.column2.y;
	ret.column2.z = m.column2.z;

	return ret;
}


VECTOR3D Transform(MATRIX3 m, VECTOR3D a)
{
	VECTOR3D ret;

	ret.x = DotProduct(m.column0, a);
	ret.y = DotProduct(m.column1, a);
	ret.z = DotProduct(m.column2, a);
	
	return ret;
}

MATRIX4 InverseOrthogonalMatrix(MATRIX3 A, VECTOR3D t)
{
	MATRIX4 ret;
	MATRIX3 At = Transpose(A);
	
	ret.m[0] = At.column0.x;
	ret.m[1] = At.column0.y;
	ret.m[2] = At.column0.z;
	ret.m[3] = 0;

	ret.m[4] = At.column1.x;
	ret.m[5] = At.column1.y;
	ret.m[6] = At.column1.z;
	ret.m[7] = 0;

	ret.m[8] = At.column2.x;
	ret.m[9] = At.column2.y;
	ret.m[10] = At.column2.z;
	ret.m[11] = 0;

	ret.m[12] = -DotProduct(t, A.column0);
	ret.m[13] = -DotProduct(t, A.column1);
	ret.m[14] = -DotProduct(t, A.column2);
	ret.m[15] = 1;

	return ret;
}