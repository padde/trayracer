#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP

// project header
#include <point.hpp>
#include <vector.hpp>
#include <matrix.hpp>
#include <shape.hpp>
#include <light.hpp>
#include <material.hpp>
#include <rgb.hpp>
#include <camera.hpp>
#include <tracer.hpp>
#include <sampler.hpp>



class Scene
{
public: // enums, typedefs
	typedef std::vector< Light*    > light_container;
	typedef std::vector< Material* > material_container;

public: // c'tors, d'tor
	Scene ();
	~Scene ();
	
public: // methods
	void push ( Shape*    shape    );
	void push ( Light*    light    );
	void push ( Material* material );
	
	void set ( rgb      bgcolor     );
	void set ( Camera*  camera_ptr  );
	void set ( Tracer*  tracer_ptr  );
	void set ( Sampler* sampler_ptr );
	
	void render ();
	
private:
	Tracer*            tracer_ptr_;
	Camera*            camera_ptr_;
	Sampler*           sampler_ptr_;
	CompositeShape     shapes_;
	light_container    lights_;
	material_container materials_;
	rgb                bgcolor_;
};

#endif //BUW_SCENE_HPP