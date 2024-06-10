#include "Load.h"
#include <DxLib.h>

Load::~Load()
{
}

void Load::AllLoadData()
{
	// データをロードする
	// チノ
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoUtamita1.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoUtamita2.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoSolo.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoHat.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoSleeve.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoText.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoText2.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoTextV.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoMoe1.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoMoe2.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoMoe3.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoHat1.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoHat2.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoHat3.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoMask.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoDoukesi.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoGekijou.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoGuzou.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoKaimaku.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoKakumei.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoMayonaka.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoMousou.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoNibiiro.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoSaikousei.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoSakusou.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoSouhan.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoTsaitsen.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoTyoujougensyou.png")));
	m_subjects.push_back(SubjectData(SubjectType::CHINO, LoadGraph("Data/ImageData/Subject/chinoZankyou.png")));
	// ミュー
	m_subjects.push_back(SubjectData(SubjectType::MYU, LoadGraph("Data/ImageData/Subject/myuUtamita1.png")));
	m_subjects.push_back(SubjectData(SubjectType::MYU, LoadGraph("Data/ImageData/Subject/myuUtamita2.png")));
	m_subjects.push_back(SubjectData(SubjectType::MYU, LoadGraph("Data/ImageData/Subject/myuSolo.png")));
	m_subjects.push_back(SubjectData(SubjectType::MYU, LoadGraph("Data/ImageData/Subject/myuTextV.png")));
	m_subjects.push_back(SubjectData(SubjectType::MYU, LoadGraph("Data/ImageData/Subject/myuAccessory.png")));
	m_subjects.push_back(SubjectData(SubjectType::MYU, LoadGraph("Data/ImageData/Subject/myuDot.png")));
	m_subjects.push_back(SubjectData(SubjectType::MYU, LoadGraph("Data/ImageData/Subject/myuGuzou.png")));
	m_subjects.push_back(SubjectData(SubjectType::MYU, LoadGraph("Data/ImageData/Subject/myuMayonaka.png")));
	m_subjects.push_back(SubjectData(SubjectType::MYU, LoadGraph("Data/ImageData/Subject/myuTsaitsen.png")));
	// ネフィ
	m_subjects.push_back(SubjectData(SubjectType::NEFFY, LoadGraph("Data/ImageData/Subject/neffyUtamita1.png")));
	m_subjects.push_back(SubjectData(SubjectType::NEFFY, LoadGraph("Data/ImageData/Subject/neffyUtamita2.png")));
	m_subjects.push_back(SubjectData(SubjectType::NEFFY, LoadGraph("Data/ImageData/Subject/neffySolo.png")));
	m_subjects.push_back(SubjectData(SubjectType::NEFFY, LoadGraph("Data/ImageData/Subject/neffyTextV.png")));
	m_subjects.push_back(SubjectData(SubjectType::NEFFY, LoadGraph("Data/ImageData/Subject/neffyAccessory.png")));
	m_subjects.push_back(SubjectData(SubjectType::NEFFY, LoadGraph("Data/ImageData/Subject/neffyDot.png")));
	m_subjects.push_back(SubjectData(SubjectType::NEFFY, LoadGraph("Data/ImageData/Subject/neffyGekijou.png")));
	m_subjects.push_back(SubjectData(SubjectType::NEFFY, LoadGraph("Data/ImageData/Subject/neffySouhan.png")));
	m_subjects.push_back(SubjectData(SubjectType::NEFFY, LoadGraph("Data/ImageData/Subject/neffyTyoujougensyou.png")));
	// ニナ
	m_subjects.push_back(SubjectData(SubjectType::NINA, LoadGraph("Data/ImageData/Subject/ninaUtamita1.png")));
	m_subjects.push_back(SubjectData(SubjectType::NINA, LoadGraph("Data/ImageData/Subject/ninaUtamita2.png")));
	m_subjects.push_back(SubjectData(SubjectType::NINA, LoadGraph("Data/ImageData/Subject/ninaSolo.png")));
	m_subjects.push_back(SubjectData(SubjectType::NINA, LoadGraph("Data/ImageData/Subject/ninaTextV.png")));
	m_subjects.push_back(SubjectData(SubjectType::NINA, LoadGraph("Data/ImageData/Subject/ninaAccessory.png")));
	m_subjects.push_back(SubjectData(SubjectType::NINA, LoadGraph("Data/ImageData/Subject/ninaDot.png")));
	m_subjects.push_back(SubjectData(SubjectType::NINA, LoadGraph("Data/ImageData/Subject/ninaDoukesi.png")));
	m_subjects.push_back(SubjectData(SubjectType::NINA, LoadGraph("Data/ImageData/Subject/ninaMousou.png")));
	m_subjects.push_back(SubjectData(SubjectType::NINA, LoadGraph("Data/ImageData/Subject/ninaNibiiro.png")));
	m_subjects.push_back(SubjectData(SubjectType::NINA, LoadGraph("Data/ImageData/Subject/ninaText.png")));
	m_subjects.push_back(SubjectData(SubjectType::NINA, LoadGraph("Data/ImageData/Subject/ninaTyoujougensyou.png")));
	// ララ
	m_subjects.push_back(SubjectData(SubjectType::RARA, LoadGraph("Data/ImageData/Subject/raraUtamita1.png")));
	m_subjects.push_back(SubjectData(SubjectType::RARA, LoadGraph("Data/ImageData/Subject/raraUtamita2.png")));
	m_subjects.push_back(SubjectData(SubjectType::RARA, LoadGraph("Data/ImageData/Subject/raraSolo.png")));
	m_subjects.push_back(SubjectData(SubjectType::RARA, LoadGraph("Data/ImageData/Subject/raraTextV.png")));
	m_subjects.push_back(SubjectData(SubjectType::RARA, LoadGraph("Data/ImageData/Subject/raraAccessory.png")));
	m_subjects.push_back(SubjectData(SubjectType::RARA, LoadGraph("Data/ImageData/Subject/raraDot.png")));
	m_subjects.push_back(SubjectData(SubjectType::RARA, LoadGraph("Data/ImageData/Subject/raraKakumei.png")));
	m_subjects.push_back(SubjectData(SubjectType::RARA, LoadGraph("Data/ImageData/Subject/raraSaikousei.png")));
	m_subjects.push_back(SubjectData(SubjectType::RARA, LoadGraph("Data/ImageData/Subject/raraSakusou.png")));
	m_subjects.push_back(SubjectData(SubjectType::RARA, LoadGraph("Data/ImageData/Subject/raraZankyou.png")));
	// ヴィッテ
	m_subjects.push_back(SubjectData(SubjectType::VITTE, LoadGraph("Data/ImageData/Subject/vitteUtamita1.png")));
	m_subjects.push_back(SubjectData(SubjectType::VITTE, LoadGraph("Data/ImageData/Subject/vitteUtamita2.png")));
	m_subjects.push_back(SubjectData(SubjectType::VITTE, LoadGraph("Data/ImageData/Subject/vitteSolo.png")));
	m_subjects.push_back(SubjectData(SubjectType::VITTE, LoadGraph("Data/ImageData/Subject/vitteTextV.png")));
	m_subjects.push_back(SubjectData(SubjectType::VITTE, LoadGraph("Data/ImageData/Subject/vitteAccessory.png")));
	m_subjects.push_back(SubjectData(SubjectType::VITTE, LoadGraph("Data/ImageData/Subject/vitteDot.png")));
	m_subjects.push_back(SubjectData(SubjectType::VITTE, LoadGraph("Data/ImageData/Subject/vitteKaimaku.png")));
	m_subjects.push_back(SubjectData(SubjectType::VITTE, LoadGraph("Data/ImageData/Subject/vitteTyoujougensyou.png")));
	// 操桃
	m_subjects.push_back(SubjectData(SubjectType::SOUGHT, LoadGraph("Data/ImageData/Subject/soughtAccessory.png")));
	m_subjects.push_back(SubjectData(SubjectType::SOUGHT, LoadGraph("Data/ImageData/Subject/soughtAccessory2.png")));
}

void Load::AllDeleteData()
{
	// データを削除する
	for (auto& data : m_subjects)
	{
		DeleteGraph(data.subHandle);
	}
	m_subjects.clear();
}
