#include "framework/Object.h"
// #include "Object.h"

namespace saga{
    Object::Object()
    : mIsPendingDestroy {false}
    {

    }

    Object::~Object()
    {
        LOG("Object destructor");
    }

    void Object::Destroy()
    {
        mIsPendingDestroy = true;
    }
}
