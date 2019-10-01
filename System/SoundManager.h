#pragma once

using namespace FMOD;

class SoundManager
{
private:
	System* system;	//Device
	Sound** sound;	//Resource
	Channel** channel;	//재생 채널

	UINT buffer; //버퍼 개수(Default + Extra)

	map<string, Sound**> sounds; //음원 개수
	map<string, Sound**>::iterator iter;

	float volume;

public:
	SoundManager();
	~SoundManager();
	
	void AddSound(string name, string soundFile, bool loop = false);
	void Play(string name, float volume = 1.0f);
	void Stop(string name);
	void Pause(string name);
	void Resume(string name);

	bool Playing(string key);
	bool Paused(string key);

	void Update();
	
	void Volume(string name, float volume);
	float Volume() { return volume; }

};
