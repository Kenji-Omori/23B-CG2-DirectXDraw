#include "DirectXResourceBarrier.h"

#include <Core/DirectX12/DirectXCommand.h>
#include <Core/DirectX12/DirectXSwapChain.h>

Core::DirectXResourceBarrier::DirectXResourceBarrier(DirectXCommand* command, DirectXSwapChain* swapChain)
{
  this->command = command;
  this->swapChain = swapChain;
}

void Core::DirectXResourceBarrier::InitializeDescs()
{
  writeModeDesc.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  writeModeDesc.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  //writeModeDesc.Transition.pResource = m_color
}

void Core::DirectXResourceBarrier::SwitchWriteMode()
{
}
