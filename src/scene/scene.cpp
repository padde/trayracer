#include "scene.hpp"

// system header
#include <iostream>

// project header
#include <rgb.hpp>
#include <camera.hpp>
#include <tracer.hpp>
#include <raycast.hpp>
#include <barebone.hpp>
#include <light.hpp>
#include <ambientlight.hpp>




Scene::Scene () :
	tracer_ptr (NULL),
	ambient_ptr (NULL),
	bgcolor    (0.0,0.0,0.0)
{
	tracer_ptr = new  RayCast(this);
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
	camera_ptr->scene_ptr = this;
}

void Scene::set ( rgb col )
{
	bgcolor = col;
}

void Scene::set ( Tracer* ptr )
{
	tracer_ptr = ptr;
}

void Scene::set ( AmbientLight* ptr )
{
	ambient_ptr = ptr;
}
