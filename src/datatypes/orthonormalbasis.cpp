// i/f header
#include "orthonormalbasis.hpp"

// system header
#include <ostream>

// project header
#include <vector.hpp>

// constants
#define ONB_EPSILON 0.01f


OrthonormalBasis::OrthonormalBasis () :
	u_(0,0,0), v_(0,0,0), w_(0,0,0)
{}

OrthonormalBasis::OrthonormalBasis ( const OrthonormalBasis& onb ) :
	u_(onb.u_), v_(onb.v_), w_(onb.w_)
{}

OrthonormalBasis::OrthonormalBasis ( const Vector& u, const Vector& v, const Vector& w ):
	u_(u), v_(v), w_(w)
{}

OrthonormalBasis::~OrthonormalBasis ()
{}

Vector
OrthonormalBasis::u () const
{
	return u_;
}

Vector
OrthonormalBasis::v () const
{
	return v_;
}

Vector
OrthonormalBasis::w () const
{
	return w_;
}

void
OrthonormalBasis::init_from_u ( const Vector& u )
{
	Vector n(1,0,0);
	Vector m(0,1,0);
	u_ = unify(u);
	v_ = cross(u_,n);
	if ( v_.length() < ONB_EPSILON )
		v_ = cross(u_,m);
	w_ = cross(u_,v_);
}

void
OrthonormalBasis::init_from_v ( const Vector& v )
{
	Vector n(1,0,0);
	Vector m(0,1,0);
	v_ = unify(v);
	w_ = cross(v_,n);
	if ( u_.squared_length() < ONB_EPSILON )
		u_ = cross(v_,m);
	w_ = cross(u_,v_);
}

void
OrthonormalBasis::init_from_w ( const Vector& w )
{
	Vector n(1,0,0);
	Vector m(0,1,0);
	w_ = unify(w);
	u_ = cross(w_,n);
	if ( u_.length() < ONB_EPSILON )
		u_ = cross(w_,m);
	v_ = cross(w_,u_);
}

void
OrthonormalBasis::init_from_uv ( const Vector& u, const Vector& v )
{
	u_ = unify(u);
	w_ = unify(cross(u,v));
	v_ = cross(w_,u_);
}

void
OrthonormalBasis::init_from_vu ( const Vector& v, const Vector& u )
{
	v_ = unify(v);
	w_ = unify(cross(u,v));
	u_ = cross(v_,w_);
}

void
OrthonormalBasis::init_from_uw ( const Vector& u, const Vector& w )
{
	u_ = unify(u);
	v_ = unify(cross(w,u));
	w_ = cross(u_,v_);
}

void
OrthonormalBasis::init_from_wu ( const Vector& w, const Vector& u )
{
	w_ = unify(w);
	v_ = unify(cross(w,u));
	u_ = cross(v_,w_);
}

void
OrthonormalBasis::init_from_vw ( const Vector& v, const Vector& w )
{
	v_ = unify(v);
	u_ = unify(cross(v,w));
	w_ = cross(u_,v_);
}

void
OrthonormalBasis::init_from_wv ( const Vector& w, const Vector& v )
{
	w_ = unify(w);
	u_ = unify(cross(v,w));
	v_ = cross(w_,u_);
}

void
OrthonormalBasis::print_on (std::ostream& os) const
{
	os << "OnB ( " << u_ << ", " << v_ << ", " << w_ << " )";
}

/* friend */ std::ostream&
operator<< (std::ostream& os, OrthonormalBasis const& onb)
{
	std::ostream::sentry const cerberus(os);
	if (cerberus)
		onb.print_on(os);
	return os;
}


