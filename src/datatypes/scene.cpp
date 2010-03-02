#include "scene.hpp"

// system header
#include <GL/glut.h>

// project header
#include <glutwindow.hpp>
#include <pixel.hpp>
#include <rgb.hpp>
#include <camera.hpp>
#include <raycast.hpp>




Scene::Scene ()
{
	cameras_.push_back(new Camera(500,500,0.0));
	tracer_ptr_ = new RayCast(this);
	bgcolor_    = rgb(0,0,0);
}

Scene::~Scene ()
{
	// delete camera_ptr_;
	// delete tracer_ptr_;
}

void Scene::push ( Shape* shape )
{
	shapes_.push(shape);
}

void Scene::push ( Light* light )
{
	lights_.push_back(light);
}

void Scene::push ( Material* material )
{
	materials_.push_back(material);
}

void Scene::push ( Camera* camera_ptr )
{
	cameras_.push_back(camera_ptr);
}

void Scene::set ( rgb bgcolor )
{
	bgcolor_ = bgcolor;
}

void Scene::set ( Tracer* tracer_ptr )
{
	// delete tracer_ptr_;
	tracer_ptr_ = tracer_ptr;
}

void Scene::set ( Sampler* sampler_ptr )
{
	// delete sampler_ptr_;
	sampler_ptr_ = sampler_ptr;
}

	
Shape*
Scene::shapes ()
{
	return &shapes_;
}

rgb
Scene::bgcolor ()
{
	return bgcolor_;
}

void Scene::render ( /*std::string cam_name,*/ std::string filename )
{
	glutwindow& gw = glutwindow::instance();
	
	Camera* camera = cameras_[0];
	
	// loop through all pixels of the viewplane
	for (std::size_t y = 0; y < gw.height(); ++y)
	{
		for (std::size_t x = 0; x < gw.width(); ++x)
		{
			// create pixel and ray
			pixel p   ( x,y );
			Ray   ray ( camera->make_ray(x,y) );
			
			// trace the ray and write pixel to window
			p.color = tracer_ptr_->trace(ray);
			gw.write(p);
		}	
	}
}
