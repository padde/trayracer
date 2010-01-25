// system header
#include <UnitTest++.h>
#include <sstream>

// project header
#include <orthonormalbasis.hpp>
#include <vector.hpp>

TEST ( orthonormalbasis__standard_constructor )
{
	OrthonormalBasis onb;
	
	CHECK_EQUAL( Vector(0,0,0), onb.u() );
	CHECK_EQUAL( Vector(0,0,0), onb.v() );
	CHECK_EQUAL( Vector(0,0,0), onb.w() );
}

TEST ( orthonormalbasis__verbose_constructor )
{
	Vector a(1,2,3), b(4,5,6), c(7,8,9);
	OrthonormalBasis onb(a,b,c);
	
	CHECK_EQUAL( Vector(1,2,3), onb.u() );
	CHECK_EQUAL( Vector(4,5,6), onb.v() );
	CHECK_EQUAL( Vector(7,8,9), onb.w() );
}

TEST ( orthonormalbasis__should_get_members )
{
	Vector a(1,2,3), b(4,5,6), c(7,8,9);
	OrthonormalBasis onb(a,b,c);
	
	CHECK_EQUAL( Vector(1,2,3), onb.u() );
	CHECK_EQUAL( Vector(4,5,6), onb.v() );
	CHECK_EQUAL( Vector(7,8,9), onb.w() );
}

// TEST ( orthonormalbasis__should_init_from_u )
// {
// 	
// }
// 
// TEST ( orthonormalbasis__should_init_from_v )
// {
// 	
// }
// 
// TEST ( orthonormalbasis__should_init_from_w )
// {
// 	
// }
// 
// TEST ( orthonormalbasis__should_init_from_uv )
// {
// 	
// }
// 
// TEST ( orthonormalbasis__should_init_from_vu )
// {
// 	
// }
// 
// TEST ( orthonormalbasis__should_init_from_uw )
// {
// 	
// }
// 
// TEST ( orthonormalbasis__should_init_from_wu )
// {
// 	
// }
// 
// TEST ( orthonormalbasis__should_init_from_vw )
// {
// 	
// }
// 
// TEST ( orthonormalbasis__should_init_from_wv )
// {
// 	
// }

TEST ( orthonormalbasis__should__print_on_ostream )
{
	Vector u(1,0,0), v(0,1,0), w(0,0,1);
	OrthonormalBasis euklid(u,v,w);
	std::stringstream ss(std::stringstream::out);
	euklid.print_on(ss);
	CHECK_EQUAL("OnB ( Vector (1,0,0), Vector (0,1,0), Vector (0,0,1) )", ss.str());
}