#pragma once

class DirectXDevice;

class DirectXInfoQueue
{
public:
	DirectXInfoQueue(DirectXDevice* device);
	~DirectXInfoQueue();

private:
	DirectXDevice* device;
};