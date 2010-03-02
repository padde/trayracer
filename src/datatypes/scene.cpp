#include "scene.hpp"

Tracer*            tracer_ptr_;
Camera*            camera_ptr_;
CompositeShape     shapes_;
light_container    lights_;
material_container materials_;
rgb                bgcolor_;



Scene::Scene ()
{
	camera_ptr_ = new Pinhole();
	tracer_ptr_ = new Raycast();
	bgcolor_    = rgb(0.1,0.1,0.1);
}

Scene::~Scene ()
{
	delete camera_ptr_;
	delete tracer_ptr_;
}

void Scene::push ( Shape* shape )
{
	shapes_.push(shape);
}

void Scene::push ( Light* light )
{
	lights_.push(light);
}

void Scene::push ( Material* material )
{
	materials_.push(material);
}

void Scene::set ( rgb bgcolor )
{
	bgcolor_ = bgcolor;
}

void Scene::set ( Camera* camera_ptr )
{
	delete camera_ptr_;
	camera_ptr_ = camera_ptr
}

void Scene::set ( Tracer* tracer_ptr )
{
	delete tracer_ptr_;
	tracer_ptr_ = tracer_ptr;
}

void Scene::set ( Sampler* sampler_ptr )
{
	delete sampler_ptr_;
	sampler_ptr_ = sampler_ptr;
}

void Scene::render ()
{
	return; // FIXME: actual rendering goes here
}
