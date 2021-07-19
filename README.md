# libpsutil
#### A single-header PS3 sprx static library for useful additions to the SDK

## Prerequisites
- Visual Studio 2013+
- Sony PS3 4.75+ SDK w/ Visual Studio Integration

## Installation
1. Download the latest release from [Releases](https://github.com/skiff/libpsutil/releases)
2. Navigate to your SDK installation folder (default: `C:\usr\local\cell\target\ppu`)
3. Drop the *include* and *lib* folders in and overwrite any existing files
4. Add `#include <libpsutil.h>` into your project
5. Add `libpsutil.a` to your project "Additional Dependencies"

![Dependencies](https://i.imgur.com/uLZnsNe.png)

6. Make sure your c++ language version is set to C++11

## Features
- **Fixed std::string** 
- **Fixed std::vector**
- **Added std::initializer_list**
- System printf, sprintf and vsprintf imports
- Read/Write Memory (Includes HEN support!)
- String manipulation (to lower, to upper, split, etc)
- RC4 encryption
- Filesystem API
- Detour/Hooking API (Includes HEN support!)
- TCP/UDP sockets
- HTTP Get requests
- Math library (vec2, vec3, vec4)

## Cryptography
In order to use the cryptography namespace, you will need to add additional dependencies for the appropriate functions
- Add `$(SCE_PS3_ROOT)\target\ppu\lib\hash\libsha1.a` for `libpsutil::cryptography::sha1`
- Add `$(SCE_PS3_ROOT)\target\ppu\lib\hash\libsha256.a` for `libpsutil::cryptography::sha256`
- Add `$(SCE_PS3_ROOT)\target\ppu\lib\hash\libsha512.a` for `libpsutil::cryptography::sha512`
- Add `$(SCE_PS3_ROOT)\target\ppu\lib\hash\libmd5.a` for `libpsutil::cryptography::md5`

## Dynamic SPRX Loading
If you use my [PS3 Toolbox](https://github.com/skiff/PS3-Toolbox) to load your SPRX without an EBOOT, you will need to grab an update version of this tool. The original release uses the game's header to execute code, but that header is now needed to read the game TOC so adjustments were made to the tool.

## HEN Detours
While this library DOES support HEN for detouring, there is an extra function inside the detour class you MUST call to use detours

`libpsutil::memory::detour::force_stub_address(uint32_t address)`

This function needs to be given *empty, EXECUTABLE* memory that already exists in the game. Almost all games have one segment that matches this description and it can be found by looking at the program segmentation in IDA
