#include "Debug.h"
#include <debugapi.h>

#include <Core/Type/String.h>

void Core::Debug::Log(const std::string& message)
{
  OutputDebugStringA(message.c_str());
}
void Core::Debug::Log(const std::wstring& message)
{
  OutputDebugStringA(WStrToStr(message).c_str());
}

