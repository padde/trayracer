#ifndef BUW_RAYCAST_HPP
#define BUW_RAYCAST_HPP

// system header

// project header
#include <ray.hpp>
#include <rgb.hpp>
#include <tracer.hpp>
// #include <scene.hpp>
class Scene; // TODO: switch fwd declaration with include


class Raycast : public Tracer
{
public: // c'tors, d'tor
	Raycast ( Scene* scene_ptr );
	~Raycast ();

public: // virtual methods
	rgb trace ( const Ray& ray );
};

#endif //BUW_RAYCAST_HPP