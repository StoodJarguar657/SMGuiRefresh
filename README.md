# SMGuiRefresh

A lightweight DLL that binds F5 to refresh the in-game GUI.

## Usage

You have multiple ways to use SMGuiRefresh:

**Option 1 — Launcher (recommended)**

Use a launcher like [Carbon Launcher](https://github.com/ScrappySM/)

Automatically downloads the latest version
Handles injection for you
Keeps the DLL up to date

**Option 2 — Manual injection**

Download the prebuilt DLL from the [SMGuiRefresh Releases](https://github.com/StoodJarguar657/SMGuiRefresh/releases/)
Inject it into the game using your preferred method

**Option 3 — Build it yourself**
If you prefer full control or don’t trust prebuilt binaries (I dont blame you):

- Install [xmake](https://github.com/xmake-io/xmake)
- lone the repository ```git clone https://github.com/StoodJarguar657/SMGuiRefresh```
- Build the project locally by going into the directory where the xmake.lua is and running the command ```xmake```

## How does this work?

**Scrap Mechanic** uses an internal engine structure called **Contraption**, which acts as a core singleton managing various runtime systems.

Inside this structure, certain graphics-related changes (such as adjusting resolution) toggle a specific flag. At offset ```0x299```, a boolean is set to ```true```, which appears to trigger a texture/UI resize.

This DLL simply:
- Listens for the F5 key
- Sets that boolean flag to true

As a result, the game performs the same refresh routine as if the resolution had been changed, effectively reloading the UI without requiring user interaction through the settings menu.
