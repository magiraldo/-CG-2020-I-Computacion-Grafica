#include "MatrizT.h"


void MatrizT::escalaM(float* a, float* b, float* c, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		c[i] = float(0);
		for (int j = 0; j < n; j++)
		{
			c[i] += a[i * n + j] * b[j];
		}
	}
}

void MatrizT::traslacionM(float* a, float* b, float* c, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		c[i] = float(0);
		for (int j = 0; j < n; j++)
		{
			c[i] += a[i * n + j] * b[j];
		}
	}
}

void MatrizT::rotacionM(float* a, float* b, float* c, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		c[i] = float(0);
		for (int j = 0; j < n; j++)
		{
			c[i] += a[i * n + j] * b[j];
		}
	}
}

void MatrizT::multiplicacionMV(float* a, float* b, float* c, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		c[i] = float(0);
		for (int j = 0; j < n; j++)
		{
			c[i] += a[i * n + j] * b[j];
		}
	}
}

void MatrizT::multiplicacionMM(float* a, float* b, float* c, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		c[i] = float(0);
		for (int j = 0; j < n; j++)
		{
			c[i] += a[i * n + j] * b[i * n + j];
		}
	}
}

void MatrizT::inversa(float* a, float* b, float* c, int m, int n)
{
	for (int i = 0; i < m; i++)
	{
		c[i] = float(0);
		for (int j = 0; j < n; j++)
		{

		}
	}
}

void MatrizT::determinante(float* a, int m, int n)
{
	float x, y, z, p, q, r, res;
	x = a[0] * a[m+1] * a[(m * n) - 1]; //a
	y = a[1] * a[m+2] * a[m + 3];		//b
	z = a[2] * a[m] * a[(m * n) - 2];	//c
	p = a[0] * a[m + 2] * a[(m * n) - 2];	//-a
	q = a[1] * a[m] * a[(m + n) - 1];		//-b
	r = a[2] * a[m + 1] * a[m + 3];			//-c

	res = x + y + z - r - q - p;
}
