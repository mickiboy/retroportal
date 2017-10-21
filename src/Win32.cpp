#ifdef _WIN32

#include <cstdlib>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

extern int main(int argc, char* argv[]);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPWSTR lpCmdLine, int nCmdShow)
{
    return main(__argc, __argv);
}

#endif
