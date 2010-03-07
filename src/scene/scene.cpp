#include "scene.hpp"

// system header
#include <iostream>
#include <map>

// project header
#include <rgb.hpp>
#include <camera.hpp>
#include <tracer.hpp>
#include <raycast.hpp>
#include <whitted.hpp>
#include <barebone.hpp>
#include <light.hpp>
#include <ambientlight.hpp>




Scene::Scene () :
	tracer_ptr (NULL),
	ambient_ptr (NULL),
	bgcolor    (0.0,0.0,0.0)
{
	tracer_ptr = new Whitted(this);
}

Scene::~Scene ()
{
	delete tracer_ptr;
}

void
Scene::push_shape ( Shape* shape )
{
	shapes.insert( std::pair< std::string, Shape* >( shape->name(), shape ) );
}

void
Scene::push_light ( Light* light )
{
	lights.push_back(light);
}

void
Scene::push_material ( Material* material )
{
	materials.insert( std::pair< std::string, Material* >( material->name(), material ) );
}

void
Scene::push_camera ( Camera* ptr )
{
	ptr->scene_ptr = this;
	cameras.insert( std::pair< std::string, Camera* >( ptr->name(), ptr ) );
}

void
Scene::set_bgcolor ( rgb col )
{
	bgcolor = col;
}

void
Scene::set_tracer ( Tracer* ptr )
{
	tracer_ptr = ptr;
}

void
Scene::set_ambient ( AmbientLight* ptr )
{
	ambient_ptr = ptr;
}

Shape* 
Scene::get_shape ( const std::string name ) const
{
	return shapes.find(name)->second;
}

Material*
Scene::get_material ( const std::string name ) const
{
	return materials.find(name)->second;
}

Camera*
Scene::get_camera ( const std::string name ) const
{
	return cameras.find(name)->second;
}

Shape*
Scene::get_and_remove_shape ( const std::string name )
{
	Scene::shape_container_t::iterator it = shapes.find(name);
	Shape* result = it->second;
	shapes.erase(it);
	return result;
	
}
