#pragma once

struct VertexData;
class DirectXDevice;
class GameObject
{
public:
	GameObject(DirectXDevice* device);
	~GameObject();

private:
	VertexData* vertexes;
	DirectXDevice* device;
};
