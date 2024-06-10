#include "SoundManager.h"
#include "Game.h"
#include <cassert>

namespace
{
	constexpr char sound_file_signature[] = "SND_";
	constexpr char sound_config_file_path[] = "./sound.conf";
	constexpr float sound_config_version = 1.0f;
}

void SoundManager::LoadSoundConfig()
{
	SoundConfigInfo conf = {};
	FILE* fp = nullptr;
	fopen_s(&fp, sound_config_file_path, "rb");
	if (fp)
	{
		fread(&conf, sizeof(conf), 1, fp);
		fclose(fp);
		m_volumeBGM = conf.volumeBGM;
		m_volumeSE = conf.volumeSE;
	}
}

void SoundManager::SaveSoundConfig()
{
	SoundConfigInfo conf = {};
	memcpy_s(conf.signature, sizeof(conf.signature), sound_file_signature, sizeof(sound_file_signature));

	conf.version = sound_config_version;
	conf.volumeSE = m_volumeSE;
	conf.volumeBGM = m_volumeBGM;

	FILE* fp = nullptr;
	fopen_s(&fp, sound_config_file_path, "wb");
	if (fp)
	{
		fwrite(&conf, sizeof(conf), 1, fp);
		fclose(fp);
	}
}

SoundManager::~SoundManager()
{
	SaveSoundConfig();

	// 効果音データ
	for (auto& soundData : m_soundData)
	{
		DeleteSoundMem(soundData.soundHandle);
	}
	m_soundData.clear();

	// 曲データ
	DeleteSoundMem(m_hMusic);
}

void SoundManager::PlaySE(SoundType sound)
{
	int volumePal = (255 / 100) * m_volumeSE;
	ChangeVolumeSoundMem(m_volumeSE, GetCurrentSoundHandle(sound));
	PlaySoundMem(GetCurrentSoundHandle(sound), DX_PLAYTYPE_BACK);
}

void SoundManager::PlayMusic()
{
	int volumePal = (255 / 100) * m_volumeBGM;
	ChangeVolumeSoundMem(volumePal, m_hMusic);
	PlaySoundMem(m_hMusic, DX_PLAYTYPE_BACK);
}

void SoundManager::RestartCurrentBGM()
{
	PlaySoundMem(m_hMusic, DX_PLAYTYPE_BACK, false);
}

int SoundManager::IsPlayingMusic()
{
	return CheckSoundMem(m_hMusic);
}

void SoundManager::SetSEVolume(int volume)
{
	m_volumeSE = volume;
}

int SoundManager::GetSEVolume() const
{
	return m_volumeSE;
}

void SoundManager::SetBGMVolume(int volume)
{
	m_volumeBGM = volume;
	int volumePal = (255 / 100) * m_volumeBGM;
	ChangeVolumeSoundMem(volumePal, m_hMusic);
}

int SoundManager::GetBGMVolume() const
{
	return m_volumeBGM;
}

void SoundManager::SetBGMRate(float rate)
{
	assert(0.0f <= rate && rate <= 1.0f);
	ChangeVolumeSoundMem(static_cast<int>(static_cast<float>(m_volumeBGM) * rate), m_hMusic);
}

void SoundManager::StopBGM()
{
	StopSoundMem(m_hMusic);
}

SoundManager::SoundManager() :
	m_soundData(),
	m_hMusic(-1)
{
	LoadSoundConfig();
	LoadData();
}

int SoundManager::GetCurrentSoundHandle(SoundType sound)
{
	int currentSound = -1;

	for (auto& soundData : m_soundData)
	{
		if (soundData.soundType == sound)
		{
			currentSound = soundData.soundHandle;
			break;
		}
	}

	return currentSound;
}

void SoundManager::LoadData()
{
	// サウンド
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/Select.wav"), SoundType::select));
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/nukiuti.wav"), SoundType::idle));
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/correctSE.mp3"), SoundType::correct));
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/incorrectSE.mp3"), SoundType::incorrect));
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/chinogood.wav"), SoundType::good));
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/chinodesu.wav"), SoundType::chino));
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/myudesu.wav"), SoundType::myu));
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/neffydesu.wav"), SoundType::neffy));
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/ninadesu.wav"), SoundType::nina));
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/raradesu.wav"), SoundType::rara));
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/vittedesu.wav"), SoundType::vitte));
	m_soundData.push_back(SoundData(LoadSoundMem("Data/SoundData/humu.wav"), SoundType::humu));

	// ミュージック
	m_hMusic = LoadSoundMem("Data/MusicData/I.C.E.mp3");
}
