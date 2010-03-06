#ifndef BUW_WHITTED_HPP
#define BUW_WHITTED_HPP

// project header
#include <ray.hpp>
#include <rgb.hpp>
#include <tracer.hpp>
#include <scene.hpp>



class Whitted : public Tracer
{
public: // c'tors, d'tor
	Whitted ( Scene* scene_ptr );
	~Whitted ();

public: // virtual methods
	rgb trace ( const Ray& ray, int depth ) const;
};

#endif //BUW_WHITTED_HPP