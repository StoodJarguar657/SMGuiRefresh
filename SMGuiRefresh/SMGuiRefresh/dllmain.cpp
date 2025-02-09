#include <Windows.h>
#include <functional>

int main(HMODULE moduleHandle) {

    DWORD64 baseAddr = reinterpret_cast<DWORD64>(GetModuleHandle(nullptr));
    DWORD64 contraption = *reinterpret_cast<DWORD64*>(baseAddr + 0x1267538);

    while (true) {

        // Limit to ~60 iterations per second
        // Dont use all the cpu
        Sleep(1);

        if (GetAsyncKeyState(VK_F5) & 0x8000) {
            // Function @ 0x2DA080 -> resizeContent(Contraption, HWND)
            // 
            // Cut down disassembly:
            // if (*(_BYTE*)(Contraption + 0x299)) {
            //    resizeContent(Contraption, 0);
            // }
            *reinterpret_cast<char*>(contraption + 0x299) = 1;
        }

        // Unload the dll
        if (GetAsyncKeyState(VK_END) & 0x8000)
            break;
    }

    FreeLibraryAndExitThread(moduleHandle, 0);
}

BOOL APIENTRY DllMain(HMODULE moduleHandle, DWORD callReason, LPVOID reserved) {

    if (callReason == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(main), moduleHandle, 0, 0);

    return TRUE;
}

