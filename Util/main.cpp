#include "Game.h"
#include "SceneManager.h"
#include "SceneTitleMenu.h"
#include "SceneDebug.h"
#include "Load.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ウィンドウモード設定
	ChangeWindowMode(Game::kWindowMode);
	// ウィンドウモードのサイズ変更
	SetWindowSizeChangeEnableFlag(true);
	// ウィンドウ名設定
	SetMainWindowText(Game::kTitleText);
	// 画面サイズの設定
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// ダブルバッファモード
	SetDrawScreen(DX_SCREEN_BACK);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// リソースの読み込み
	LPCSTR font = Game::kFontFileName;	// 読み込むフォントファイルのパス
	if (AddFontResourceEx(font, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読み込みエラー処理
		MessageBox(NULL, "フォント読み込み失敗", "", MB_OK);
	}
	// 標準フォント設定
	ChangeFont("チョークS");
	SetFontSize(Game::kFontSize);

	// カーソル画像読み込み
	int hCursorImg = LoadGraph("Data/ImageData/Chalk.png");
	// ゲーム中のマウスポインタ描画設定
	SetMouseDispFlag(false);
	// マウスカーソル位置設定
	SetMousePoint(Game::kScreenWidthHalf, Game::kScreenHeightHalf);

	// サウンドマネージャー宣言
	auto& soundManager = SoundManager::GetInstance();
	// ゲームマネージャー宣言
	auto& gameManager = GameDataManager::GetInstance();
	// キー入力状態クラス宣言
	InputState input;
	// シーンマネージャー宣言
	SceneManager scene;

	//ロード
	Load::GetInstance().AllLoadData();

#ifdef _DEBUG
	scene.ChangeScene(new SceneDebug(scene));
#else
	scene.ChangeScene(new SceneTitleMenu(scene));
#endif

	while (ProcessMessage() == 0)
	{
		LONGLONG time = GetNowHiPerformanceCount();
		// 音楽再生開始
		if (SoundManager::GetInstance().IsPlayingMusic() != 1)
		{
			SoundManager::GetInstance().PlayMusic();
		}

		// 画面のクリア
		ClearDrawScreen();

		// 入力状態更新
		input.Update();

		// 現在のシーンの更新
		scene.Update(input);

		// 現在のシーンの描画
		scene.Draw();

		// マウスカーソル描画
		DrawRotaGraph(input.GetMousePos().x + 12, input.GetMousePos().y + 12, 0.2, 0.0, hCursorImg, true, false, true);

		// 裏画面を表画面と入れ替える
		ScreenFlip();

#ifdef _DEBUG
		// escキーを押したら終了する
		if (CheckHitKey(KEY_INPUT_L)) scene.ChangeScene(new SceneDebug(scene));
#endif

		if (scene.IsGameEnd()) break;

		while (GetNowHiPerformanceCount() - time < 16667)
		{

		}
	}
	// カーソル画像削除
	DeleteGraph(hCursorImg);
	// マウスカーソル描画
	SetMouseDispFlag(true);

	//データ削除
	Load::GetInstance().AllDeleteData();

	DxLib_End();				// ＤＸライブラリ使用の終了処理

	return 0;				// ソフトの終了 
}