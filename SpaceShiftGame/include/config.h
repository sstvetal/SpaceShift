#pragma once
#include<string>

std::string GetResourceDir()
{
#ifdef NDBUG //release build
	return "assets/";
#else
	return "D:/work Unreal/SpaceShift/SpaceShiftGame/assets/";
#endif
}
