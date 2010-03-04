#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

// project header
#include <ray.hpp>
#include <pixel.hpp>

// system header
#include <string>



class Camera
{
public: // ctor's, d'tor
	Camera ( std::string name, std::size_t width, std::size_t height, float fov_x );
	~Camera ();

public: // methods
	Ray ray_for_pixel ( const pixel p ) const;

private:
	std::string name_;
	std::size_t width_, height_;
	float angle_;
	float vpd_;
};

#endif // BUW_CAMERA_HPP
