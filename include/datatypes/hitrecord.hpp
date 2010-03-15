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


//! @author Patrick Oscity
//! @date February 2010
//! @brief ... struct for recording hits
//
class HitRecord
{
public: 
	/// c'tor
	HitRecord ( Scene* ptr );
	~HitRecord ();

public: // methods
	HitRecord& operator= ( HitRecord const& rhs );

public: // member
	//! @brief  is it a hit?
	bool      hit;          
	//! @brief  distance from ray origin
	float     t;            
	//! @brief  color (for early development stage)
	rgb       color;        
	//! @brief  normal vector on surface
	Vector    normal;       
	//! @brief  material at hit point
	Material* material_ptr; 
	//! @brief  hit point
	Point     hitpoint;
	//! @brief  linkback scene pointer     
	Scene*    scene_ptr;
	//! @brief  recursion depth
	int       depth;
	Ray       ray;
};


#endif //BUW_HITRECORD_HPP 
