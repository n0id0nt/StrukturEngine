#pragma once
namespace Struktur
{
	namespace Util
	{
		namespace Noise
		{
			double Grad(int hash, double value);
			double Smoothstep(double edge0, double edge1, double x);
			double PerlinNoise1(unsigned int seed, double value);
		};
	};
};
