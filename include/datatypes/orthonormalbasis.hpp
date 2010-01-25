#ifndef BUW_ORTHONORMALBASIS_HPP
#define BUW_ORTHONORMALBASIS_HPP

// project header
#include <vector.hpp>

class OrthonormalBasis
{
public: // c'tors, d'tor
	OrthonormalBasis ();
	OrthonormalBasis ( const OrthonormalBasis& onb );
	OrthonormalBasis ( const Vector& u, const Vector& v, const Vector& w );
	~OrthonormalBasis ();

public: // methods
	Vector u () const;
	Vector v () const;
	Vector w () const;
	
	void init_from_u ( const Vector& u );
	void init_from_v ( const Vector& v );
	void init_from_w ( const Vector& w );
	
	void init_from_uv ( const Vector& u, const Vector& v );
	void init_from_vu ( const Vector& v, const Vector& u );
	void init_from_uw ( const Vector& u, const Vector& w );
	void init_from_wu ( const Vector& w, const Vector& u );
	void init_from_vw ( const Vector& v, const Vector& w );
	void init_from_wv ( const Vector& w, const Vector& v );
	
	void print_on ( std::ostream& os ) const;

public: // friends
	friend std::ostream& operator<< ( std::ostream& os, OrthonormalBasis const& onb );

private: // member
	Vector u_, v_, w_;
};

#endif //BUW_ORTHONORMALBASIS_HPP 