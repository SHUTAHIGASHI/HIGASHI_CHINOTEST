#pragma once
#include "Scene.h"
#include "Game.h"
#include <memory>
#include <string>

class SceneDebug :
    public Scene
{
public:
    SceneDebug(SceneManager& manager);
    virtual ~SceneDebug();

    void Update(const InputState& input);
    void Draw();

private:
    void UpdateText();

private:
    // ‘I‘ğ’†‚Ì€–Ú
    int m_selectedPos;
    // ‘I‘ğ’†‚Ì€–Ú–¼
    std::string m_selectedItemName;
};

