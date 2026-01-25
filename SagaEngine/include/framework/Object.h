#pragma once

#include "framework/Core.h"

namespace saga{
    class Object{
    public:
        Object();
        virtual ~Object();

        void Destroy();
        bool IsPendingDestroy() const {return mIsPendingDestroy;}
    
    private:
        bool mIsPendingDestroy;
    };
}