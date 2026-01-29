#include "framework/Object.h"
#include "framework/Core.h"
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
        // LOG("Destroying object");
    }
}
