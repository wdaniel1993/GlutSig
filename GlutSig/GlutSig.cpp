// GlutSig.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "ex01_blueRect.h"
#include "ex02_geoPrimitives.h"


int main(int argc, char* argv[])
{
	std::cout << "GLUTSig launched!" << std::endl;
	ex02_geoPrimitves_run(argc, argv);
    return 0;
}

