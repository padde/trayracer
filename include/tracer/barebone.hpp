#ifndef BUW_BAREBONE_HPP
#define BUW_BAREBONE_HPP

// system header

// project header
#include <ray.hpp>
#include <rgb.hpp>
#include <tracer.hpp>
// #include <scene.hpp>
class Scene; // TODO: switch fwd declaration with include


class Barebone : public Tracer
{
public: // c'tors, d'tor
	Barebone ( Scene* scene_ptr );
	~Barebone ();

public: // virtual methods
	rgb trace ( const Ray& ray );
};

#endif //BUW_BAREBONE_HPP