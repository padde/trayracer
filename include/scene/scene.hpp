#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP

// project header
#include <point.hpp>
#include <vector.hpp>
#include <matrix.hpp>
#include <shape.hpp>
#include <compositeshape.hpp>
#include <light.hpp>
#include <ambientlight.hpp>
#include <material.hpp>
#include <rgb.hpp>
#include <camera.hpp>
#include <tracer.hpp>
//#include <sampler.hpp>

// system header
#include <vector>
#include <map>



class Scene
{
public: // enums, typedefs
	typedef std::vector< Light*    > light_container_t;
	typedef std::map< std::string, Material* > material_container_t;
	typedef std::map< std::string, Shape*    > shape_container_t;
	typedef std::map< std::string, Camera*   > camera_container_t;

public: // c'tors, d'tor
	Scene ();
	~Scene ();
	
public: // methods
	void push_shape    ( Shape*    shape_ptr    );
	void push_light    ( Light*    light_ptr    );
	void push_material ( Material* material_ptr );
	void push_camera   ( Camera*  camera_ptr  );

	void set_bgcolor ( rgb      bgcolor     );
	void set_tracer  ( Tracer*  tracer_ptr  );
	void set_ambient ( AmbientLight* ambient_ptr );
	
	Shape*    get_shape    ( const std::string name ) const;
	Material* get_material ( const std::string name ) const;
	Camera*   get_camera   ( const std::string name ) const;
	
	Shape* get_and_remove_shape ( const std::string name );
	
	bool hit ( const Ray& ray, Shape::interval_t tmin, Shape::interval_t tmax, HitRecord& hitrec );
	bool hit ( const Ray& ray, Shape::interval_t tmin, Shape::interval_t tmax );
	
public:
	Tracer*              tracer_ptr;
	//camera_container_t   cameras;
	AmbientLight*        ambient_ptr;
	//CompositeShape       shapes;
	light_container_t    lights;
	//material_container_t materials;
	rgb                  bgcolor;
	
	material_container_t  materials;
	shape_container_t     shapes;
	camera_container_t    cameras;
};

#endif //BUW_SCENE_HPP