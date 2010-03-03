#ifndef BUW_HITRECORD_HPP
#define BUW_HITRECORD_HPP

// project header
#include <rgb.hpp>
#include <ray.hpp>
#include <vector.hpp>
#include <point.hpp>
#include <material.hpp>

// fwd declarations
class Scene;



// struct for recording hits
class HitRecord
{
public: // c'tors, d'tor
	HitRecord ( Scene* ptr );
	~HitRecord ();

public: // methods
	HitRecord& operator= ( HitRecord const& rhs );

public: // member
	bool      hit;          // is it a hit?
	float     t;            // distance from ray origin
	rgb       color;        // color (for early development stage)
	Vector    normal;       // normal vector on surface
	Material* material_ptr; // material at hit point
	Point     hitpoint;     // hit point
	Scene*    scene_ptr;
	Ray       ray;
};


#endif //BUW_HITRECORD_HPP 