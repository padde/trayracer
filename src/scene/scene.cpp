#include "scene.hpp"

// project header
#include <whitted.hpp>
#include <shape.hpp>
#include <iostream>



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
Scene::set_ambient ( AmbientLight* ptr )
{
	ambient_ptr = ptr;
}

Shape* 
Scene::get_shape ( const std::string name ) const
{
	Scene::shape_container_t::const_iterator it = shapes.find(name);
	Shape* result = it->second;
	if ( it == shapes.end() ) {
		std::cerr << "shape \"" << name << "\" not found" << std::endl;
		exit(1);
	}
	return result;
}

Material*
Scene::get_material ( const std::string name ) const
{
	Scene::material_container_t::const_iterator it = materials.find(name);
	Material* result = it->second;
	if ( it == materials.end() ) {
		std::cerr << "material \"" << name << "\" not found" << std::endl;
		exit(1);
	}
	return result;
}

Camera*
Scene::get_camera ( const std::string name ) const
{
	Scene::camera_container_t::const_iterator it = cameras.find(name);
	Camera* result = it->second;
	if ( it == cameras.end() ) {
		std::cerr << "camera \"" << name << "\" not found" << std::endl;
		exit(1);
	}
	return result;
}

Shape*
Scene::get_and_remove_shape ( const std::string name )
{
	Scene::shape_container_t::iterator it = shapes.find(name);
	Shape* result = it->second;
	
	if ( it == shapes.end() ) {
		std::cerr << "shape \"" << name << "\" not found" << std::endl;
		exit(1);
	}
	
	shapes.erase(it);
	return result;
	
}
