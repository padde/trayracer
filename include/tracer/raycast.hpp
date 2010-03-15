#ifndef BUW_RAYCAST_HPP
#define BUW_RAYCAST_HPP

// project header
#include <ray.hpp>
#include <rgb.hpp>
#include <tracer.hpp>
#include <scene.hpp>


//! @author Patrick Oscity
//! @date January 2010
//! @brief ... raycast tracer for basic materials (phong/matte)
//

class RayCast : public Tracer
{
public: // c'tors, d'tor
	RayCast ( Scene* scene_ptr );
	~RayCast ();

public: // public methods
	rgb trace ( const Ray& ray, int depth ) const;
};

#endif //BUW_RAYCAST_HPP
