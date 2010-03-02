#ifndef BUW_BAREBONE_HPP
#define BUW_BAREBONE_HPP

// project header
#include <ray.hpp>
#include <rgb.hpp>
#include <tracer.hpp>
#include <scene.hpp>



class BareBone : public Tracer
{
public: // c'tors, d'tor
	BareBone ( Scene* scene_ptr );
	~BareBone ();

public: // virtual methods
	rgb trace ( const Ray& ray ) const;
};

#endif //BUW_BAREBONE_HPP