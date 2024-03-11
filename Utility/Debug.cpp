#include "Debug.h"
#include <debugapi.h>
#include <Core/Utility/String.h>

void Utility::Debug::Log(const std::string& message)
{
  OutputDebugStringA(message.c_str());
}
void Utility::Debug::Log(const std::wstring& message)
{
  OutputDebugStringA(String::WStrToStr(message).c_str());
}
