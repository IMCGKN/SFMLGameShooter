#include "App.hpp"

int main()
{
    ImcApp *app = new ImcApp();
    app->MainLoop();
    delete app;

    return 0;
}
