#pragma once

class UiHpBar
{
public:
    UiHpBar();
    virtual ~UiHpBar();
    
    void Init();
    void Update();
    void UpdateUIData(int hp);
    void Draw();

private:
    // wić
    int m_hBarImg;
    // `ćŔW
    int m_drawX, m_drawY;
    int m_drawW, m_drawH;

private:
    // ťÝĚHPĘ
    float m_currentHpRate;
};

