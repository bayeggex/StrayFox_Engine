#pragma once
class Owindow;
class engineRoot
{
public:
	engineRoot();
	~engineRoot();
	void Instantiate();
	void Destroy();

protected:
	bool isInstantiate = true;
	Owindow* display = nullptr;
};

