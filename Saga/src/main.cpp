#include <iostream>
#include <memory>
#include <SFML/Graphics.hpp>

#include "framework/Application.h"

int main()
{
    std::unique_ptr<saga::Application> app = std::make_unique<saga::Application>();
    app->Run();
    
    return 0;
}