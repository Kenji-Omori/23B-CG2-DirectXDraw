#include "Color.h"

Color::Color()
{
  r = 0;
  g = 0;
  b = 0;
  a = 0;
}

Color::Color(float r, float g, float b, float a)
{
  this->r = r;
  this->g = g;
  this->b = b;
  this->a = a;
}

float Color::GetR() const
{
  return r;
}

float Color::GetG() const
{
  return g;
}

float Color::GetB() const
{
  return b;
}

float Color::GetA() const
{
  return a;
}
