#pragma once

typedef struct Matrix4x4 {
  float m[4][4];
  static Matrix4x4 Identity();
}Matrix4x4;

