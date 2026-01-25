#include "EntryPoint.h"
#include "framework/Application.h"

int main(){
    saga::Application* app = saga::GetApplication();
    app->Run();
    delete app;
    return 0;
}