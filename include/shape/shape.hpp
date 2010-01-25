#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

// system header
#include <string>

// forward declarations
class Ray;
class Material;
class HitRecord;

class Shape
{
public: // enums, typedefs
	typedef float interval_t;

public: // c'tors, d'tor
	Shape ();
	Shape ( std::string name, Material* material );
	virtual ~Shape ();

public: // methods
	const std::string& name () const;

public: // virtual methods
	virtual bool hit        ( const Ray& ray, HitRecord& hitrec, interval_t tmin, interval_t tmax ) const = 0;
	virtual bool shadow_hit ( const Ray& ray, HitRecord& hitrec ) const = 0;

private:
	std::string name_;
	Material*   material_;
};

#endif //BUW_SHAPE_HPP 