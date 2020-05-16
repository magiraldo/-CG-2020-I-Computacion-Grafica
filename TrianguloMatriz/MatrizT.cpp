#include "MatrizT.h"

void MatrizT::identidadM(float* a, float* b, float* c, int m, int n)
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


