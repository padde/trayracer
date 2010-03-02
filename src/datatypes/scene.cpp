#include "scene.hpp"

// system header
#include <GL/glut.h>
#include <png++/image.hpp>
#include <png++/rgb_pixel.hpp>

// project header
#include <glutwindow.hpp>
#include <pixel.hpp>
#include <rgb.hpp>
#include <camera.hpp>
#include <tracer.hpp>
#include <raycast.hpp>
#include <barebone.hpp>




Scene::Scene ()
{
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

void Scene::set ( Camera* camera_ptr )
{
	camera_ptr_ = camera_ptr;
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

void Scene::render ( std::string filename )
{
	glutwindow& gw = glutwindow::instance();
	std::size_t width  = gw.width();
	std::size_t height = gw.height();
	
	png::image< png::rgb_pixel > png(width,height);
	
	// loop through all pixels of the viewplane
	for (std::size_t y = 0; y < height; ++y)
	{
		for (std::size_t x = 0; x < width; ++x)
		{
			// create pixel and trace ray
			pixel p (x,y);
			Ray ray = camera_ptr_->make_ray(x,y);
			p.color = tracer_ptr_->trace(ray);
			
			// write pixel to window
			gw.write(p);
			
			// write pixel to png file
			int r = p.color[rgb::r] * 255;
			int g = p.color[rgb::g] * 255;
			int b = p.color[rgb::b] * 255;
			png[height-y-1][x] = png::rgb_pixel(r,g,b);
		}	
	}
	
	// save png image
	png.write(filename);
	std::cout << "image saved as " << filename << std::endl;
}
