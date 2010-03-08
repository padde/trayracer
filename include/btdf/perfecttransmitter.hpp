#ifndef BUW_PERFECTTRANSMITTER_HPP
#define BUW_PERFECTTRANSMITTER_HPP

// project header
#include <btdf.hpp>
#include <rgb.hpp>
#include <hitrecord.hpp>



class PerfectTransmitter : public BTDF
{
public: // c'tors, d'tor
	PerfectTransmitter( const float kt, const float ior );
	~PerfectTransmitter();

public: // methods
	virtual rgb  sample_f ( const HitRecord& hitrec, const Vector& wo, Vector& wt ) const;
	virtual bool tir      ( const HitRecord& hitrec                               ) const;
	
	void kt  ( const float& kt  );
	void ior ( const float& ior );
	
	float kt  () const;
	float ior () const;
	
private:
	float kt_;
	float ior_;
};

#endif
