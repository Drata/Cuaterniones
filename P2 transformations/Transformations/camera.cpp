#include "camera.h"

// TODO
// devuelve los valores de distancia de los planos a partir del fov horizontal
FRUSTUM makeFrustum(double fovX, double aspectRatio, double nearValue, double farValue)
{
	const double DEG2RAD = 3.14159265 / 180;

	double tangent = tan(fovX/2 * DEG2RAD); // tangent of half fovX
	double width = nearValue * tangent; // half width of near plane
	double height = width * 1/aspectRatio; // half height of near plane

	FRUSTUM ret;
	// TODO : rellenar valores de ret
	ret.nearValue = nearValue;
	ret.farValue = farValue;
	ret.bottom = -height;
	ret.left = -width;
	ret.right = width;
	ret.top = height;
	
	return ret;
}

MATRIX4 lookAt(VECTOR3D eyePosition, VECTOR3D target, VECTOR3D upVector) 
{
	MATRIX3 m;
	
	VECTOR3D forward = Substract(target, eyePosition);
	VECTOR3D left = CrossProduct(forward, upVector);
	VECTOR3D up = CrossProduct(left, forward);
	
	m.column0 = Normalize(left);
	m.column1 = Normalize(up);
	m.column2 = Normalize(MultiplyWithScalar(-1,forward));

	return InverseOrthogonalMatrix(m, eyePosition);
}