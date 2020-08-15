#ifndef PRIORITYWAYSIGN_H
#define PRIORITYWAYSIGN_H
#include "sign.h"

class PriorityWaySign : public Sign
{
public:
    PriorityWaySign(int x, int y, int radius);
    bool isSign(int minimumGreyValue);
    ~PriorityWaySign();
};

#endif // PRIORITYWAYSIGN_H
