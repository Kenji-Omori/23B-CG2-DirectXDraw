#pragma once

#include <Windows.h>
#include <string>
namespace Utility {
  class String {
  public:
    static std::wstring StrToWStr(const std::string& str);
    static std::string WStrToStr(const std::wstring& str);
  };
}