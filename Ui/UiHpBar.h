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
    // îwåiâÊëú
    int m_hBarImg;
    // ï`âÊç¿ïW
    int m_drawX, m_drawY;
    int m_drawW, m_drawH;

private:
    // åªç›ÇÃHPó 
    float m_currentHpRate;
};

