#pragma once

#include <string>

static class Utilitys
{
public:
  static void Log(const std::string& message);
  static void Log(const std::wstring& message);
};