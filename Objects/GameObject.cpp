#include "GameObject.h"

#include<Core/Type/VertexData.h>

GameObject::GameObject()
{
	Vector2 center = {0,0};
	float size = 0.5f;
  vertexes = new VertexData[6];
  float w = size;
  float h = size;
  float l = -size/2;
  float b = -size/2;
  float r = l + w;
  float t = b + h;

  vertexes[0] = { { l, b, 0.0f, 1.0f },{ 0.0f, 1.0f } };
  vertexes[1] = { { l, t, 0.0f, 1.0f },{ 0.0f, 0.0f } };
  vertexes[2] = { { r, b, 0.0f, 1.0f },{ 1.0f, 1.0f } };

  vertexes[3] = { { l, t, 0.0f, 1.0f },{ 0.0f, 0.0f } };
  vertexes[4] = { { r, t, 0.0f, 1.0f },{ 1.0f, 0.0f } };
  vertexes[5] = { { r, b, 0.0f, 1.0f },{ 1.0f, 1.0f } };
}

GameObject::~GameObject()
{
}
