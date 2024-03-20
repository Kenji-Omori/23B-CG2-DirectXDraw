#include "TimeKeeper.h"

TimeKeeper::TimeKeeper(float targetFps)
{
  SetTargetFps(targetFps);
}

TimeKeeper::~TimeKeeper()
{
}

void TimeKeeper::SetTargetFps(float targetFps)
{
  this->targetFps = targetFps;
  lastUpdate = std::chrono::steady_clock::now();
  ResetCurrentFpses();
}

void TimeKeeper::Update()
{
  // 経過時間計測
  auto now = std::chrono::steady_clock::now();
  deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(now - lastUpdate).count() / 1000000.0f;
  countTime += deltaTime;
  lastUpdate = now;

  float frameTime = 1.0f / targetFps;
  bool isNext = countTime > frameTime;
  if (!isNext) { isNextFrame = false; }
  countTime -= frameTime;
  isNextFrame = true;
}


bool TimeKeeper::IsNextFrame()
{
  return isNextFrame;
}

float TimeKeeper::GetDeltaTime()
{
  return deltaTime;
}

float TimeKeeper::GetAverageFps()
{
  float sumFps = 0;
  int countNum = 0;
  for (int i = 0; i < RECORD_FPS_NUM; i++)
  {
    float curFps = currentFps[i];
    if (curFps < 0) { continue; }
    sumFps += currentFps[i];
    countNum++;
  }
  if (countNum == 0) { return 0; }
  return sumFps / countNum;
}

void TimeKeeper::ResetCurrentFpses()
{
  for (int i = 0; i < RECORD_FPS_NUM; i++)
  {
    currentFps[i] = -1;
  }
}

void TimeKeeper::PrintFpsToConsole()
{
  char str[50];
  sprintf_s(str, "fps=%03.0f ", GetAverageFps());
}

