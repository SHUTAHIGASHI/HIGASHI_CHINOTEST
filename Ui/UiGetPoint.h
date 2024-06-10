#pragma once
#include "UiPointBase.h"

class UiGetPoint :
    public UiPointBase
{
public:
    UiGetPoint(int point);
    virtual ~UiGetPoint();

    void Update();

private:
};

