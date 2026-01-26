#pragma once
#include <string>

std::string GetResourceDirectory(){
#ifdef NDEBUG
    return "assets/";
#else
    return "/Users/fatakhillahkhaqo/Documents/Learnings/CPP/SagaGame/SagaGame/assets/";
#endif
}
