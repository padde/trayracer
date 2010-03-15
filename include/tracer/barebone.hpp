#ifndef BUW_BAREBONE_HPP
#define BUW_BAREBONE_HPP

// project header
#include <ray.hpp>
#include <rgb.hpp>
#include <tracer.hpp>
#include <scene.hpp>


//! @author Patrick Oscity
//! @date January 2010
//! @brief ... barebone tracer for simple tests
//
class BareBone : public Tracer
{
public: // c'tors, d'tor
	BareBone ( Scene* scene_ptr );
	~BareBone ();

public: // public methods
	rgb trace ( const Ray& ray, int depth ) const;
};

#endif //BUW_BAREBONE_HPP
