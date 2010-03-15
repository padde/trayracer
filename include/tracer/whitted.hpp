#ifndef BUW_WHITTED_HPP
#define BUW_WHITTED_HPP

// project header
#include <ray.hpp>
#include <rgb.hpp>
#include <tracer.hpp>
#include <scene.hpp>


//! @author Patrick Oscity
//! @date January 2010
//! @brief ... whitted tracer for recursive shadings (reflective/transparent)
//


class Whitted : public Tracer
{
public: // c'tors, d'tor
	Whitted ( Scene* scene_ptr );
	~Whitted ();

public: // public methods
	rgb trace ( const Ray& ray, int depth ) const;
};

#endif //BUW_WHITTED_HPP
