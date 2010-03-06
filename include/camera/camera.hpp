#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP

// project header
#include <ray.hpp>
#include <pixel.hpp>

// system header
#include <string>

// fwd declarations
class Scene;


class Camera
{
public: // ctor's, d'tor
	Camera ( std::string name, std::size_t hres, std::size_t vres, float fov_x );
	~Camera ();

public: // methods
	void render ( std::string filename ) const;

public:
	Scene* scene_ptr;

private:
	std::string name_;
	std::size_t hres_, vres_;
	float angle_;
	float vpd_;
};

#endif // BUW_CAMERA_HPP
