#include "sampler.hpp"

Sampler ( const int num, const float px )
{
	n = (int) std::sqrt(static_cast<float>(num));
	num_samples = n*n;
	pixel_size = px;
}

~Sampler()
{}

void generate_samples ( const Ray& ray )
{
	for ( int y=0; y<n; ++y )
	{
		for ( int x=0; x<n; ++x )
		{
			Ray tmpray(ray)
			
			rays.push_back(tmpray);
		}
	}
}
