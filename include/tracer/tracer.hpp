#ifndef BUW_TRACER_HPP
#define BUW_TRACER_HPP

// system header

// project header
#include <ray.hpp>
#include <rgb.hpp>
// #include <scene.hpp>
class Scene; // TODO: switch fwd declaration with include


class Tracer
{
public: // c'tors, d'tor
	Tracer ( Scene* scene_ptr );
	virtual ~Tracer ();

public: // virtual methods
	virtual rgb trace ( const Ray& ray ) const = 0;

protected:
	Scene* scene_ptr_;
};

#endif //BUW_TRACER_HPP