#include "camera.hpp"

// project header
#include <ray.hpp>
#include <pixel.hpp>
#include <point.hpp>
#include <vector.hpp>

// system header
#include <string>



Camera::Camera ( std::string name, std::size_t width, std::size_t height, float fov_x ) :
	name_   ( name   ),
	width_  ( width  ),
	height_ ( height ),
	fov_x_  ( fov_x  )
{
	vpd_ = 0; // FIXME: compute actual view plane distance
}

Camera::~Camera ()
{}

Ray
Camera::ray_for_pixel ( const pixel p ) const
{
	// FIXME: make eye camera
	return Ray( Point(p.x,p.y,0), Vector(0,0,-1) );
}