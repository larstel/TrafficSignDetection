#ifndef PRIORITYSIGN_H
#define PRIORITYSIGN_H
#include "sign.h"
#include "filter.h"

class PrioritySign : public Sign
{
public:
    PrioritySign(int x, int y, int radius);
    bool isSign(int minimumGreyValue);
    ~PrioritySign();
};

#endif // PRIORITYSIGN_H
