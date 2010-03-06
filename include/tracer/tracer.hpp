#ifndef BUW_TRACER_HPP
#define BUW_TRACER_HPP

// project header
#include <ray.hpp>
#include <rgb.hpp>

// fwd declarations
class Scene;



class Tracer
{
public: // c'tors, d'tor
	Tracer ( Scene* scene_ptr );
	virtual ~Tracer ();

public: // virtual methods
	virtual rgb trace ( const Ray& ray, int depth ) const = 0;

protected:
	Scene* scene_ptr_;
};

#endif //BUW_TRACER_HPP