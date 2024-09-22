#include "modloader.h"
#include <Windows.h>
#include <iostream>


//using namespace System;
using namespace GMMK;

void LoadMods(){
    System::Console::WriteLine("Mod Loader Called");
    cli::array<unsigned char,1>^ thing = ModLoader::loadMods();
    std::cout << thing[2] << std::endl;
}