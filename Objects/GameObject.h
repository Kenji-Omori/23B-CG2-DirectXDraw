#pragma once

struct VertexData;
class GameObject
{
public:
	GameObject();
	~GameObject();

private:
	VertexData* vertexes;
};
