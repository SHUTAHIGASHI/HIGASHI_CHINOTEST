#pragma once
#include "Scene.h"
#include <memory>
#include "GameDataManager.h"
#include "Subject.h"

class StageDirecting;
class Player;
class SubjectManager;

enum class SubjectType;

class SceneMain :
    public Scene
{
public:
    // コンストラクタ
    SceneMain(SceneManager& manager);
    // デストラクタ
    virtual ~SceneMain();

    // 更新処理
    void Update(const InputState& input);
    // 描画処理
    void Draw();

    // 問題正解の処理
    void OnCorrect();
    // 問題不正解の処理
    void OnIncorrect();

    // 回答中かどうか取得
    bool IsAnswering() { return m_isAnswering; }

private:
    // 常時実行する更新処理
    void AlwaysUpdate(const InputState& input);
    // ゲームモードに応じた初期化
    void InitGameMode();
    // 解答が操桃のとき
    void OnAnswerIsSought();
    // 回答後の処理
    void OnResponse();
    // 回答中の処理へ移行
    void OnChangeAnswering();
    // ゲーム終了時の処理
    void OnGameEnd();
    // ゲーム終了判定
    void CheckGameEnd();
    // 種類に対応したサウンドを再生
    void PlayerSoundSubType(SubjectType subType);

    // メンバ関数ポインタ(更新)
    using m_tUpdateFunc = void (SceneMain::*) (const InputState& input);
    m_tUpdateFunc m_updateFunc = nullptr;
    void SceneStartUpdate(const InputState& input); // シーン開始時の処理
    void IdlingUpdate(const InputState& input);     // 待機中の更新処理
    void AnsweringUpdate(const InputState& input);  // 回答中の更新処理
    void AnsweredUpdate(const InputState& input);   // 回答後の更新処理
    void SceneEndUpdate(const InputState& input);   // シーン終了時の処理

    // メンバ関数ポインタ(描画)
    using m_tDrawFunc = void (SceneMain::*) ();
    m_tDrawFunc m_drawFunc = nullptr;
    void SceneStartDraw();
    void IdlingDraw();
    void NormalDraw();
    void SceneEndDraw();

    // メンバ関数ポインタ(ゲーム情報描画)
    using m_tDrawInfoFunc = void (SceneMain::*) ();
    m_tDrawInfoFunc m_drawInfoFunc = nullptr;
    void QuestionLimitDraw();
    void TimeLimitDraw();
    void AllChallengeDraw();

private:
    // ゲームモード
    GameMode m_gameMode;
    // ゲームポイント
    int m_correct;
    int m_incorrect;
    // 問題開始前のカウントダウン
    int m_IdlingTime;
    // 問題終了時のカウントダウン
    int m_endTime;
    // 制限時間
    int m_gameTime;
    int m_attackTime;
    // 合計問題数
    int m_questionNum;
    // 問題数
    int m_answerNum;
    // 回答済みの問題数
    int m_answeredNum;
    // 回答後の遅延時間
    int m_answeredDelay;
    // モード選択
    bool m_isModeSelected;
    // 回答中かどうか
    bool m_isAnswering;
    // 操桃を描画するかどうか
    bool m_isDrawSought;
    // 終了処理済みかどうか
    bool m_isEnd;
    // 待機中の正答文字
    std::string m_correctText;

private:
    std::shared_ptr<StageDirecting> m_pStage;
    std::shared_ptr<SubjectManager> m_pSubjectManager;
    std::shared_ptr<Player> m_pPlayer;
};

