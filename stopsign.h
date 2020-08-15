#ifndef STOPSIGN_H
#define STOPSIGN_H
#include "sign.h"


class StopSign : public Sign
{
public:
    StopSign(int x, int y, int radius);
    bool isSign(int minimumGreyValue);
    ~StopSign();
};

#endif // STOPSIGN_H
