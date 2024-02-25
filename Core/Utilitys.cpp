#include "Utilitys.h"
#include <dxgidebug.h>
#include <Core/Type/String.h>

void Utilitys::Log(const std::string& message)
{
  OutputDebugStringA(message.c_str());
}

void Utilitys::Log(const std::wstring& message)
{
  Log(WStrToStr(message));
}
