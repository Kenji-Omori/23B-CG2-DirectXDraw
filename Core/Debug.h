#pragma once

#include <Windows.h>
#include <string>

namespace Core{
  class Debug
  {
  public:
    static void Log(const std::string& message);
    static void Log(const std::wstring& message);
  };
}