#ifndef GIVEWAYSIGN_H
#define GIVEWAYSIGN_H
#include "sign.h"
#include "filter.h"

class GiveWaySign : public Sign
{
public:
    GiveWaySign(int x, int y, int radius);
    bool isSign(int minimumGreyValue);
    ~GiveWaySign();
};

#endif // GIVEWAYSIGN_H
