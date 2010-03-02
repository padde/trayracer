#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

// project header
#include <ray.hpp>

// system header
#include <string>



class Camera
{
public: // ctor's, d'tor
	Camera ( std::string name, std::size_t width, std::size_t height, float fov_x );
	~Camera ();

public: // methods
	Ray make_ray ( std::size_t x, std::size_t y ) const;

private:
	std::string name_;
	std::size_t width_, height_;
	float fov_x_;
	float vpd_;
};

#endif // BUW_CAMERA_HPP
