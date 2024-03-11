#pragma once

#include <DirectXMath.h>

class Vector3
{
public:
	Vector3():x(0),y(0),z(0){};
	Vector3(float x, float y, float z):x(x),y(y),z(z){};
	~Vector3(){};
	float x;
	float y;
	float z;
	
	DirectX::XMFLOAT3 ToXMFLOAT3(){ return DirectX::XMFLOAT3(x,y,z); }

private:

};
