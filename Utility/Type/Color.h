#pragma once

class Color
{
public:
	Color();
	Color(float r, float g, float b, float a = 1);
	~Color() {}

	float GetR() const;
	float GetG() const;
	float GetB() const;
	float GetA() const;

private:
	float r;
	float g;
	float b;
	float a;
};

