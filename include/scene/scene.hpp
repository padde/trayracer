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



class Scene
{
public: // enums, typedefs
	typedef std::vector< Light*    > light_container_t;
	typedef std::vector< Material* > material_container_t;

public: // c'tors, d'tor
	Scene ();
	~Scene ();
	
public: // methods
	void push ( Shape*    shape_ptr    );
	void push ( Light*    light_ptr    );
	void push ( Material* material_ptr );
	
	void set ( Camera*  camera_ptr  );
	void set ( rgb      bgcolor     );
	void set ( Tracer*  tracer_ptr  );
	void set ( AmbientLight* ambient_ptr );
	
	bool hit ( const Ray& ray, Shape::interval_t tmin, Shape::interval_t tmax, HitRecord& hitrec );
	bool hit ( const Ray& ray, Shape::interval_t tmin, Shape::interval_t tmax );
	
public:
	Tracer*              tracer_ptr;
	Camera*              camera_ptr;
	AmbientLight*        ambient_ptr;
	CompositeShape       shapes;
	light_container_t    lights;
	material_container_t materials;
	rgb                  bgcolor;
};

#endif //BUW_SCENE_HPP