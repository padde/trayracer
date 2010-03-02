#ifndef BUW_RAYCAST_HPP
#define BUW_RAYCAST_HPP

// system header

// project header
#include <ray.hpp>
#include <rgb.hpp>
#include <tracer.hpp>
#include <scene.hpp>


class RayCast : public Tracer
{
public: // c'tors, d'tor
	RayCast ( Scene* scene_ptr );
	~RayCast ();

public: // virtual methods
	rgb trace ( const Ray& ray ) const;
};

#endif //BUW_RAYCAST_HPP