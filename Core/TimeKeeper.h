#pragma once
#include <chrono>

class TimeKeeper
{
public:
  TimeKeeper(float targetFps = 60);
  ~TimeKeeper();
  void SetTargetFps(float targetFps);
  void Update();
  bool IsNextFrame();
  float GetDeltaTime();
  float GetAverageFps();
  void ResetCurrentFpses();
  void PrintFpsToConsole();

private:
  static const int RECORD_FPS_NUM = 5;
  float targetFps;
  float currentFps[RECORD_FPS_NUM];
  float deltaTime;
  float countTime;
  bool isNextFrame;
  std::chrono::steady_clock::time_point lastUpdate;

};

