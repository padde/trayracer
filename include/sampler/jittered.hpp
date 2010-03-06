#ifndef BUW_JITTERED_HPP
#define BUW_JITTERED_HPP

// system header
#include <vector>

// project header
#include <sampler.hpp>
#include <ray.hpp>



class Jittered : public Sampler
{
public: // c'tors, d'tor
	Sampler ( const int num_samples, const float px );
	~Sampler();
	
public: // methods
	virtual void generate_samples () = 0;
	
	void  setup_shuffled_indices ();
	void  shuffle_samples        (); // shuffle samples in each pattern
	Point sample_unit_square     (); // get next sample
	
public: // members
	int                num_samples;
	int                num_sets;
	std::vector<Point> samples;
	std::vector<int>   shuffled_indices;
	unsigned int       count;
	int                jump;
	
};

#endif //BUW_JITTERED_HPP