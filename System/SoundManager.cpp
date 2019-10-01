#include "stdafx.h"
#include "SoundManager.h"

SoundManager::SoundManager()
	:system(NULL), channel(NULL), sound(NULL), buffer(15), volume(1.0f)
{
	//시스템 생성
	System_Create(&system);	
	system->init(buffer, FMOD_INIT_NORMAL, NULL);

	//채널 생성
	sound = new Sound*[buffer]; 
	channel = new Channel*[buffer];

	//사운드, 채널 배열 NULL 초기화
	memset(sound, NULL, sizeof(Sound*) * buffer);
	memset(channel, NULL, sizeof(Channel*) * buffer);
	//ZeroMemory(sound, sizeof(Sound*) * buffer);

}

SoundManager::~SoundManager()
{
	//채널 혹은 사운드가 사용 중인 상태라면
	if (channel != NULL || sound != NULL)
	{
		for (UINT i = 0; i < buffer; i++)
		{
			if (channel != NULL)
			{
				if (channel[i]) channel[i]->stop();
			}

			if (sound != NULL)
			{
				if (sound[i]) sound[i]->release();
			}

		}
	}

	SAFE_DELETE(channel);
	SAFE_DELETE(sound);

	//시스템 닫기
	if (system != NULL)
	{
		system->release();
		system->close();
	}

	sounds.clear();
}

void SoundManager::AddSound(string name, string soundFile, bool loop)
{
	if (loop == true)
	{
		system->createStream
		(
			soundFile.c_str(),
			FMOD_LOOP_NORMAL, //루프
			NULL,
			&sound[sounds.size()]
		);
	}
	else
	{
		system->createStream
		(
			soundFile.c_str(),
			FMOD_DEFAULT,
			NULL,
			&sound[sounds.size()]
		);
	}

	//name + sound resource를 맵에 저장(pair)
	sounds.insert(make_pair(name, &sound[sounds.size()]));

}

void SoundManager::Play(string name, float volume)
{
	int count = 0;
	iter = sounds.begin();

	for (iter; iter != sounds.end(); ++iter, count++)
	{
		if (name == iter->first)
		{
			//해당 사운드 플레이
			system->playSound(FMOD_CHANNEL_FREE, *iter->second, false, &channel[count]);

			//볼륨
			channel[count]->setVolume(volume);
		}
	}

}

void SoundManager::Stop(string name)
{
	int count = 0;
	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++)
	{
		if (name == iter->first)
		{
			//해당 채널 스톱
			channel[count]->stop();
			break;
		}
	}
}

void SoundManager::Pause(string name)
{
	int count = 0;
	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++)
	{
		if (name == iter->first)
		{
			//해당 채널 pause
			channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::Resume(string name)
{
	int count = 0;
	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++)
	{
		if (name == iter->first)
		{
			//해당 채널 pause
			channel[count]->setPaused(false);
			break;
		}
	}
}

bool SoundManager::Playing(string key)
{
	bool bPlay = false;
	int count = 0;
	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++)
	{
		//모든 채널 검사, 하나라도 플레이 중인게 있는지
		if (key == iter->first)
		{
			channel[count]->isPlaying(&bPlay);
			break;
		}
	}

	return bPlay;
}

bool SoundManager::Paused(string key)
{
	bool bPause = false;
	int count = 0;
	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++)
	{
		//모든 채널 검사, 하나라도 플레이 중인게 있는지
		if (key == iter->first)
		{
			channel[count]->getPaused(&bPause);
			break;
		}
	}

	return bPause;
}

void SoundManager::Update()
{
	system->update();
}

void SoundManager::Volume(string name, float volume)
{
	int count = 0;
	iter = sounds.begin();
	for (iter; iter != sounds.end(); ++iter, count++)
	{
		if (name == iter->first)
		{
			channel[count]->setVolume(volume);
		}
	}
}
