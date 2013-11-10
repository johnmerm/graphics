//============================================================================
// Name        : hw3.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <FreeImage.h>
#include <FreeImagePlus.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <deque>
#include <stack>

using namespace std;
#include "object.h"
#include "scene.h"
#include "Transform.h"
#include "RayTracer.h"

void SaveScreenshot(string fname, BYTE* image, int width, int height) {

	FIBITMAP* img = FreeImage_ConvertFromRawBits(image, width, height,
        width * 3, 24, 0xFF0000, 0x00FF00, 0x0000FF, false);

	std::cout << "Saving screenshot: " << fname << "\n";

	FreeImage_Save(FIF_PNG, img, fname.c_str(), 0);
}

BYTE* RayTrace (Camera camera, const Scene& scene)  {
	RayTracer ray_tracer;
	int width = scene.width;
	int height = scene.height;
	int pix = width * height;
	BYTE* image = new BYTE[3*pix];
	for (int i = 0 ; i < height ; i++)
		for (int j = 0 ; j < width ; j++) {
			Ray ray = ray_tracer.GenerateRay(camera, i, j, height, width);
			Color color = ray_tracer.Trace(ray, scene, 0, i, j);
			int base = 3 * ((height-i-1) * width + j);
			image[base + 0] = color.Bbyte();
			image[base + 1] = color.Gbyte();
			image[base + 2] = color.Rbyte();
			if (i % 40 == 0 && j == 0)
                printf("%d %d\n",i, j);
		}
	return image;
}


int main(int argc, char* argv[]) {
	if (argc < 2) {
		cerr << "Usage: transforms scenefile [grader input (optional)]\n";
		exit(-1);
	}
  	FreeImage_Initialise();

	Scene scene;
	string testfile = string(argv[1]);

	string outputfile = testfile.substr(0,testfile.length()-5)+".png";
	scene.outputFile = outputfile;
    scene.readfile(argv[1]);

    BYTE* image = RayTrace(scene.camera, scene);
    SaveScreenshot(scene.outputFile, image, scene.width, scene.height);
    delete image;

	FreeImage_DeInitialise();


	return EXIT_SUCCESS;
}
