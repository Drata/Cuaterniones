#include "camera.h"


// devuelve los valores de distancia de los planos a partir del fov horizontal
FRUSTUM makeFrustum(double fovX, double aspectRatio, double nearValue, double farValue)
{
	const double DEG2RAD = 3.14159265 / 180;

	double tangent = tan(fovX/2 * DEG2RAD); // tangent of half fovX
	double width = nearValue * tangent; // half width of near plane
	double height = width * 1/aspectRatio; // half height of near plane

	FRUSTUM ret;
	
	ret.nearValue = nearValue;
	ret.farValue = farValue;
	ret.bottom = -height;
	ret.left = -width;
	ret.right = width;
	ret.top = height;
	
	return ret;
}

MATRIX4 lookAt(VECTOR3D eyePosition, VECTOR3D forward, VECTOR3D upVector) 
{
	MATRIX3 m;
	
	VECTOR3D left = CrossProduct(upVector, forward);
	VECTOR3D up = CrossProduct(forward, left);
	
	m.column0 = Normalize(left);
	m.column1 = Normalize(up);
	m.column2 = Normalize(forward);

	return InverseOrthogonalMatrix(m, eyePosition);
}

void updateEulerOrientation(EULER& euler) 
{
	QUATERNION qYaw, qPitch, qRoll, qAux;

	qYaw = QuaternionFromAngleAxis(euler.yaw, {0, 1, 0});
	qPitch = QuaternionFromAngleAxis(euler.pitch, {1, 0, 0});
	qRoll = QuaternionFromAngleAxis(euler.roll, {0, 0, 1});

	qAux = Multiply(qYaw, qPitch);
	euler.orientation = Multiply(qAux, qRoll);
}

VECTOR3D getForward(EULER euler) 
{
	return RotateWithQuaternion({ 0, 0, -1 }, euler.orientation);
}
