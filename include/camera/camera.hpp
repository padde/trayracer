#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

// project header
#include <ray.hpp>
#include <pixel.hpp>
#include <point.hpp>

// system header
#include <string>

// fwd declarations
class Scene;

//! @author Patrick Oscity
//! @date February 2010
//! @brief ... Camera model for viewpoint and angle
//
class Camera
{
public: // ctor's, d'tor
	//! @brief camera constructor
	//! @param name name of the camera for cross reference
	//! @param hres horizontal screen resolution
	//! @param vres vertical screen resolution
	//! @param fov_x opening angle of the camera lense
	//! @image latex Figure08.15.EPS
	//! @image html Figure08.15.png
	Camera ( std::string name, std::size_t hres, std::size_t vres, float fov_x );
	~Camera ();

public: // methods
	//! @brief renders the scene
	//! @param filename directory and filename to save the picture to
	void render ( std::string filename ) const;
	//! @brief returns the name of the camera
	std::string name () const;

public:
	Scene* scene_ptr;

private:
	std::string name_;
	std::size_t hres_, vres_;
	float angle_;
	float vpd_;
	Point origin_;
};

#endif // BUW_CAMERA_HPP
