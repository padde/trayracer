#ifndef BUW_VECTOR_HPP
#define BUW_VECTOR_HPP

// forward declarations
class Point;

class Vector
{
public: // enums, typedefs
	typedef float value_t;
	
public: // c'tors, d'tor
	Vector ();
	Vector (const Vector& v);
	Vector (const Point& p);
	Vector (const Point& p1, const Point& p2);
	Vector (const value_t& x, const value_t& y, const value_t& z);
	~Vector ();
	
public: // methods	
	value_t&       operator[] (unsigned int index);
	const value_t& operator[] (unsigned int index) const;
	
	value_t length () const;
	void    unify  ();
	
	Vector& operator=  (const Vector& v);
	void    operator+= (const Vector& v);
	void    operator-= (const Vector& v);
	void    operator*= (const value_t& scalar);
	void    operator/= (const value_t& scalar);
	
	Vector& operator=  (const Point& p);
	
	void swap     (Vector& v);
	void print_on (std::ostream& os) const;
	
public: // friends
	friend Vector operator+ (const Vector& lhs, const Vector& rhs);
	friend Vector operator- (const Vector& lhs, const Vector& rhs);
	friend Vector operator* (const value_t& scalar, const Vector& rhs);
	friend Vector operator* (const Vector& lhs, const value_t& scalar);
	friend Vector operator/ (const Vector& lhs, const value_t& scalar);
	
	friend bool operator== (const Vector& lhs, const Vector& rhs);
	friend bool operator!= (const Vector& lhs, const Vector& rhs);
	
	friend value_t dot   (const Vector& lhs, const Vector& rhs);
	friend Vector  cross (const Vector& lhs, const Vector& rhs); 
	
	friend std::ostream& operator<< (std::ostream& os, Vector const& v);
	
private: // members
	value_t data_[3]; // x,y,z
	
};


#endif //BUW_VECTOR_HPP 