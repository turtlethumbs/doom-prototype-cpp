#include "Application.hpp"

int main(int argc, char** argv)
{
    Application app;
    if (app.initialize()) {
        app.run();
    }
    return 0;
}
