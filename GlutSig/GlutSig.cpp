// GlutSig.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
//#include "ex01_blueRect.h"
//#include "ex02_geoPrimitives.h"
//#include "ex04_olympicRings.h"
#include "ex08_renderPreDefinedObjects.h";
//#include "FirstCubeExample.h"


int main(int argc, char* argv[])
{
	std::cout << "GLUTSig launched!" << std::endl;
	ex08_RenderPreDefinedObjects_run(argc, argv);
    return 0;
}

