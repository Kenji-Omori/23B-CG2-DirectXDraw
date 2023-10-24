#include "Matrix4x4.h"

Matrix4x4 Matrix4x4::Identity()
{
  Matrix4x4 result = {
    {
      {1,0,0,0},
      {0,1,0,0},
      {0,0,1,0},
      {0,0,0,1}
    }
  };
  return result;
}
