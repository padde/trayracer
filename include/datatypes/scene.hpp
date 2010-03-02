#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP

// project header
#include <point.hpp>
#include <vector.hpp>
#include <matrix.hpp>
#include <shape.hpp>
#include <compositeshape.hpp>
//#include <light.hpp>
//#include <material.hpp>
#include <rgb.hpp>
#include <camera.hpp>
#include <tracer.hpp>
//#include <sampler.hpp>

// system header
#include <vector>

class Light;
class Material;
class Sampler;

class Scene
{
public: // enums, typedefs
	typedef std::vector< Light*    > light_container;
	typedef std::vector< Material* > material_container;

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
	void set ( Sampler* sampler_ptr );
	
	Shape* shapes  ();
	rgb    bgcolor ();
	
	void render ( std::string filename );
	
private:
	Tracer*            tracer_ptr_;
	Sampler*           sampler_ptr_;
	Camera*            camera_ptr_;
	CompositeShape     shapes_;
	light_container    lights_;
	material_container materials_;
	rgb                bgcolor_;
};

#endif //BUW_SCENE_HPP