#include <Windows.h>

/// How to update (assumes IDA Pro is being used):
/// 1. Firstly find Contraption. This can be done by going to the Names view and searching "Contraption::`vftable'".
/// 2. Then xref to the first instance of it being used. This will be the constructor, xref one more time and you are at the global variable.
/// 3. Put this address in the baseAddr + 0x..... line.
/// 4. Go to the strings view and search for "Resize content from (".
/// 5. Xref to the first instance of it being used. This is the function that actually resizes the content. We do not call it directly, instead we set a flag to 1 which makes the game call it.
/// 6. The first parameter to this function is the contraption instance, this will be important later. Xref one back from this "resizeContent" function.
/// 7. On the line above you should see a value being set to something plus 0x299, you will notice this "something" is the same thing that a1 is to resizeContent, this way we know it's the contraption + 0x299 for a resize flag.
/// 8. Put this address in the contraption + 0x..... line if it is no longer 0x299, if not, you Xwere already done when you updated the contraption address.

int main(HMODULE moduleHandle) {
    DWORD64 baseAddr = reinterpret_cast<DWORD64>(GetModuleHandle(nullptr));
    DWORD64 contraption = *reinterpret_cast<DWORD64*>(baseAddr + 0x1267538);

    while (true) {
        // Limit to ~60 iterations per second so that
        // it doesn't use all of the CPU's processing power
        Sleep(16);

        if (contraption == 0)
            contraption = *reinterpret_cast<DWORD64*>(baseAddr + 0x1267538);

        if (contraption && GetAsyncKeyState(VK_F5) & 0x8000) {
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

