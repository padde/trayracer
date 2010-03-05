#include "scene.hpp"

// system header
#include <GL/glut.h>
#include <png++/image.hpp>
#include <png++/rgb_pixel.hpp>
#include <iostream>

// project header
#include <glutwindow.hpp>
#include <pixel.hpp>
#include <rgb.hpp>
#include <camera.hpp>
#include <tracer.hpp>
#include <raycast.hpp>
#include <barebone.hpp>
#include <light.hpp>
#include <ambientlight.hpp>




Scene::Scene () :
	tracer_ptr (NULL),
	sampler_ptr (NULL),
	ambient_ptr (NULL),
	bgcolor    (0.0,0.0,0.0)
{
	tracer_ptr = new RayCast(this);
}

Scene::~Scene ()
{
	delete tracer_ptr;
}

void Scene::push ( Shape* shape )
{
	shapes.push(shape);
}

void Scene::push ( Light* light )
{
	lights.push_back(light);
}

void Scene::push ( Material* material )
{
	materials.push_back(material);
}

void Scene::set ( Camera* ptr )
{
	camera_ptr = ptr;
}

void Scene::set ( rgb col )
{
	bgcolor = col;
}

void Scene::set ( Tracer* ptr )
{
	tracer_ptr = ptr;
}

void Scene::set ( Sampler* ptr )
{
	sampler_ptr = ptr;
}

void Scene::set ( AmbientLight* ptr )
{
	ambient_ptr = ptr;
}

void Scene::render ( std::string filename )
{
	glutwindow& gw = glutwindow::instance();
	std::size_t width  = gw.width();
	std::size_t height = gw.height();
	float gamma = 2;
	
	png::image< png::rgb_pixel > png(width,height);
	
	// loop through all pixels of the viewplane
	for (std::size_t y = 0; y < height; ++y)
	{
		for (std::size_t x = 0; x < width; ++x)
		{
			// create pixel and trace ray
			pixel p (x,y);
			Ray ray = camera_ptr->ray_for_pixel(p);
			p.color = tracer_ptr->trace(ray) * gamma;
			p.color.max_to_one();
			
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
