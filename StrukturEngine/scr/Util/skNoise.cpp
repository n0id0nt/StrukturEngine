#include "skNoise.h"
#include <stdlib.h>
#include <raymath.h>
#include <cmath>

double Struktur::Util::Noise::Grad(int hash, double value)
{
	int h = hash & 15;
	double grad = 1 + (h & 7); // Gradient value 1-8
	if (h & 8)
		grad = -grad;   // Randomly invert half of them
	return (grad * value);
}

double Struktur::Util::Noise::Smoothstep(double edge0, double edge1, double x)
{
	// Scale, bias and saturate x to 0..1 range
	x = Clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
	// Evaluate polynomial
	return x * x * (3 - 2 * x);
}

double Struktur::Util::Noise::PerlinNoise1(unsigned int seed, double value)
{
	int p[512];
	srand(seed);
	for (int i = 0; i < 256; ++i) {
		p[i] = p[256 + i] = rand() % 256;
	}

	int X = static_cast<int>(std::floor(value)) & 255;
	value -= std::floor(value);

	double u = Smoothstep(0.0, 1.0, value);

	int a = p[X];
	int b = p[X + 1];

	return Lerp(u, Grad(a, value), Grad(b, value - 1));
}
