#ifndef BUW_COMPOSITESHAPE_HPP
#define BUW_COMPOSITESHAPE_HPP

#include <vector>

#include "shape.hpp"

class CompositeShape : public Shape
{
public: // c'tors, d'tor
	CompositeShape ();
	virtual ~CompositeShape ();

public: // methods
	bool hit ( const Ray& ray, interval_t tmin, interval_t tmax, HitRecord& hitrec ) const;
	bool hit ( const Ray& ray, interval_t tmin, interval_t tmax ) const;
	
	void push ( Shape* shape ); // push shape to shapes_
	
	const Shape* operator[] ( unsigned ) const; // shape getter
	Shape* operator[] ( unsigned );             // shape setter

private:
	std::vector<Shape*> shapes_;
};

#endif //BUW_COMPOSITESHAPE_HPP 