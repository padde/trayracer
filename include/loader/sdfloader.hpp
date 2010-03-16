#ifndef BUW_SDFLOADER
#define BUW_SDFLOADER


// project header
#include <scene.hpp>

using namespace std;

//! @author Frank Urbainsky
//! @date January 2010
//! @brief ... sdf file loader and parser
//
class sdfloader
{
	public:
	//! @brief constructor
	sdfloader();
	
	///////////////////////////////////////////////////////////
	//! @brief	interface for sdfloader access
	//////////////////////////////////////////////////////////
	
	//! @brief for access to ./sdf/
	bool	load	();
	//! @brief for access to specific sdf file
	//! @param filename filename of the sdf file to load
	bool	load	(string& filename);
	
	private: //member function
	
	///////////////////////////////////////////////////////////	
	//! @brief directory listing for choosing of sdf-file
	int	getdir	(string dir ,vector<string>& files);
	
	///////////////////////////////////////////////////////////	
	//! @brief converts file on drive in 2d input vector
	vector< vector<string> > fileload (const char* path);
	
	///////////////////////////////////////////////////////////	
	//! @brief parses the input vector
	void			parse ( vector < vector<string> >& input);
	
	///////////////////////////////////////////////////////////
	//! @brief helper functions for specific things to parse
	void			load_phong( vector<string>& word );
	void			load_reflective ( vector<string>& word );
	void			load_transparent ( vector<string>& word );
	void			load_box ( vector<string>& word );
	void			load_sphere ( vector<string>& word );
	void			load_triangle ( vector<string>& word );
	void			load_composite ( vector<string>& word );
	void			load_alight ( vector<string>& word );
	void			load_dlight ( vector<string>& word );
	void			load_camera (vector<string>& word);
	void			apply_transformation( vector<string>& word );
	void			set_bgcolor ( vector<string>& word);
	void			do_render(vector<string>& word) const;
	
	bool			phong( vector < string>& input) const;
	bool			reflective( vector < string>& input) const;
	bool			transparent( vector < string>& input) const;
	bool			box( vector<string>& input) const;
	bool			sphere( vector<string>& input) const;
	bool			triangle( vector<string>& input) const;
	bool			composite( vector<string>& input) const;
	bool			alight( vector<string>& input) const;
	bool			dlight( vector<string>& input) const;
	bool			camera( vector<string>& input) const;
	bool			render( vector<string>& input) const;
	bool			transform( vector<string>& input) const;
	bool			background( vector<string>& input) const;
	
	///////////////////////////////////////////////////////////
	public: //member variables
	Scene*	world;
	
};


#endif //BUW_SDFLOADER
