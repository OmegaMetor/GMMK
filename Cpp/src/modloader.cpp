#include "modloader.h"
#include <Windows.h>
#include <iostream>


using namespace System;
using namespace testingFunny;


void LoadMods(){
    cli::array<unsigned char,1>^ thing = funnylol::doFunny();
    Console::WriteLine(thing[2]);
}