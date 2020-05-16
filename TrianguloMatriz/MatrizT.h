#pragma once
#include <iostream>
#include <glm.hpp>
#include <math.h>

using namespace std;

class MatrizT
{
	public:
		

		void identidadM(float * a, float * b, float * c, int m, int n);
		void escalaM(float* a, float* b, float* c, int m, int n);
		void traslacionM(float* a, float* b, float* c, int m, int n);

		void rotacionM(float* a, float* b, float* c, int m, int n);
		//MatrizT multiplicacionM(MatrizT m, MatrizT n);

		float* x;
		float* y;
		float* z;
};

