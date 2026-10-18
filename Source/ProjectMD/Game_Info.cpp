
#include "Game_Info.h"

bool Check(UObject* Object, FString Text)
{
    if (!IsValid(Object))
    {
        Test("Warning!! : %s", *Text);
        return false;
    }

    return true;
}
