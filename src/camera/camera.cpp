#include "camera.hpp"

// project header
#include <ray.hpp>
#include <point.hpp>
#include <vector.hpp>



Camera::Camera ( std::size_t width, std::size_t height, float fov_x ) :
	width_  ( width  ),
	height_ ( height ),
	fov_x_  ( fov_x  )
{
	vpd_ = 0; // FIXME: compute actual view plane distance
}

Camera::~Camera ()
{}

Ray
Camera::make_ray ( std::size_t x, std::size_t y ) const
{
	// FIXME: make eye camera
	return Ray( Point(x,y,0), Vector(0,0,-1) );
}