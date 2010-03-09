//system headers
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//project headers
#include "sdfloader.hpp"
#include "scene.hpp"
#include "shape.hpp"
#include "compositeshape.hpp"
#include "sphere.hpp"
#include "triangle.hpp"
#include "box.hpp"
#include "material.hpp"
#include "phong.hpp"
#include "reflective.hpp"
//#include "transparent.hpp"
#include "light.hpp"
#include "ambientlight.hpp"
#include "pointlight.hpp"

////////////////////////////////////////////////////////////////////////////////
//  path to the sdf files...
////////////////////////////////////////////////////////////////////////////////
#define SDFPATH "./sdf/"

using namespace std;

////////////////////////////////////////////////////////////////////////////////
//  c'tor
////////////////////////////////////////////////////////////////////////////////
sdfloader::sdfloader()
	: world(new Scene)
{}





////////////////////////////////////////////////////////////////////////////////
//	getdir: directory listing for choosing of sdf-file
////////////////////////////////////////////////////////////////////////////////
int
sdfloader::getdir (string dir , vector<string>& files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        cout << "Error(" << errno << ") opening " << dir << endl;
        return errno;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
//	load: converts file on drive in 2d input vector
////////////////////////////////////////////////////////////////////////////////
bool
sdfloader::load ()
{
	vector<string> files = vector<string>();
	vector<string> sdf_files = vector<string>();
	
	
	// get files in the sdf folder
	getdir(SDFPATH,files);
	
	// weed out non sdf files
	for (unsigned int i = 0;i < files.size();i++) {
	  	if (string::npos != files[i].find ( ".sdf", 0 ) )
	  	{
			sdf_files.push_back( files[i] );
	    	}
	}
	
	// if several sdf files are present, start the file chooser
	if (sdf_files.size() > 1 )
	{
		cout << endl << "Please choose the sdf file to load:" << endl;
		for (unsigned int i = 0;i < sdf_files.size();++i){
			cout << '['<<i<<"] " << sdf_files[i] << endl;
		}
		
		cout << endl << "Enter the number of the correct file: ";
		
		unsigned number;
		cin >> number;
		
		load (sdf_files[number]);
		
	}
	else if ( sdf_files.size() == 1)
	{
		load( sdf_files[0] );
	}
	else 
		cerr << endl << "No sdf files found to load!" << endl << "Please check the "<< SDFPATH << " Folder";
	return 0;
}



vector < vector<string> >
sdfloader::fileload (const char* path )
{
	ifstream ifs ( path, ifstream::in );
	unsigned int zeilenzahl = 0;
	vector < vector<string> > input;
	
  	while( ifs.good() )
  	{
  		// cleanup input till first argument statement
  		unsigned int dirty = 1;
  		while ( dirty )
  		{
  			char firstchar = ifs.peek();
  						
  			if ( firstchar == '#' )
  			{
				ifs.ignore( 512, '\n');
 			}  				
  			else if ( firstchar == '\n' )
  			{
  				ifs.ignore(512, '\n');
  			}
  			else if ( firstchar == '\t' )
  			{
  				ifs.ignore(1, '\t');
  			}
  			else if ( firstchar == ' ' )
  			{
  				ifs.ignore(1, ' ');
 			}
  			else
  			{
  				dirty = 0;
  			}
  		}
  		
  		// resize input vector to accomodate enough lines
  		++zeilenzahl;
  		input.resize(zeilenzahl);
  		
  		// import a single line from the input filestream
		char cline[512];
		ifs.getline(cline,512);
		
		// convert it into a stringstream for formatted extraction of words
		stringstream line (stringstream::in | stringstream::out);
		// fill stringstream from char array
		line << cline;
		string word;
		while ( line.good() )
		{
			
			line >> word;
			input[zeilenzahl - 1].push_back( word );
		}	 		
  	}
  	ifs.close();
  	
  	return input;
}

bool
sdfloader::load (string& filename)
{
	cout << endl << "loading " << SDFPATH << filename << " ..." << endl;

	const string temppath = SDFPATH + filename;
  	const char* path = temppath.c_str();
  	
  	// load pure input from file
  	vector< vector <string> > input = fileload( path );
  	
  	
  	
	// parse input
	parse( input );

	
	return true;
}


void
sdfloader::parse ( vector< vector<string> >& input)
{
	for (unsigned int i = 0; i < input.size()-1; ++i)
	{
	
		if( phong(input[i]) )
		{
			cout << "Adding material \"" << input[i][3] << "\" of type phong ...\n";
			
			// check for input sanity
			if (input[i].size() != 14)
			{
				cerr << "\tInvalid number of arguments!\t" ;
				break;
			}		
				
			// conversion of strings to floats :
			float kaR = atof ( input[i][4].c_str() );
			float kaG = atof ( input[i][5].c_str() );
			float kaB = atof ( input[i][6].c_str() );
			
			float kdR = atof ( input[i][7].c_str() );
			float kdG = atof ( input[i][8].c_str() );
			float kdB = atof ( input[i][9].c_str() );
			
			float ksR = atof ( input[i][10].c_str() );
			float ksG = atof ( input[i][11].c_str() );
			float ksB = atof ( input[i][12].c_str() );
			
			float m = atof ( input[i][13].c_str() );
			
			cout << "\tka: (" << kaR <<','<< kaG <<','<< kaB << ") kd: (" << kdR <<','<<kdG <<','<< kdB << ") ks: (" << ksR <<','<< ksG <<','<< ksB << ") m: " << m << endl;
			
			
			// integrate into world
			world->push_material( new Phong(input[i][3], rgb( kaR, kaG, kaB ), rgb( kdR, kdG, kdB ), rgb( ksR, ksG, ksB ), m) );
		}
		else if( reflective(input[i]) )
		{
			cout << "Adding material \"" << input[i][3] << "\" of type reflective ...\n";
			
			// check for input sanity
			if (input[i].size() != 17)
			{
				cerr << "\tInvalid number of arguments!\t" ;
				break;
			}
				
			// conversion of strings to floats :
			float kaR = atof ( input[i][4].c_str() );
			float kaG = atof ( input[i][5].c_str() );
			float kaB = atof ( input[i][6].c_str() );
			
			float kdR = atof ( input[i][7].c_str() );
			float kdG = atof ( input[i][8].c_str() );
			float kdB = atof ( input[i][9].c_str() );
			
			float ksR = atof ( input[i][10].c_str() );
			float ksG = atof ( input[i][11].c_str() );
			float ksB = atof ( input[i][12].c_str() );
			
			float krR = atof ( input[i][14].c_str() );
			float krG = atof ( input[i][15].c_str() );
			float krB = atof ( input[i][16].c_str() );
			
			float m = atof ( input[i][13].c_str() );
			
			// integrate into world
			world->push_material( new Reflective(input[i][3], rgb( kaR, kaG, kaB ), rgb( kdR, kdG, kdB ), rgb( ksR, ksG, ksB ), m, rgb( krR, krG, krB )) );
		}		
		else if( transparent(input[i]) ) // NEED TO EDIT, STILL COPY OF THONG
		{
			cout << "Adding material \"" << input[i][2] << "\" of type transparent ...\n";
			
			// check for input sanity
			if (input[i].size() != 13)
			{
				cerr << "\tInvalid number of arguments!\t" ;
				break;
			}		
				
			// conversion of strings to floats :
			float kaR = atof ( input[i][3].c_str() );
			float kaG = atof ( input[i][4].c_str() );
			float kaB = atof ( input[i][5].c_str() );
			
			float kdR = atof ( input[i][6].c_str() );
			float kdG = atof ( input[i][7].c_str() );
			float kdB = atof ( input[i][8].c_str() );
			
			float ksR = atof ( input[i][9].c_str() );
			float ksG = atof ( input[i][10].c_str() );
			float ksB = atof ( input[i][11].c_str() );
			
			float m = atof ( input[i][12].c_str() );
			
			// integrate into world
			world->push_material( new Phong(input[i][2], rgb( kaR, kaG, kaB ), rgb( kdR, kdG, kdB ), rgb( ksR, ksG, ksB ), m) );
		}				
		else if( box(input[i]) )
		{
			cout << "Adding box \"" << input[i][3] << "\" ...\n";
			
			// check for input sanity
			if (input[i].size() != 11)
			{
				cerr << "\tInvalid number of arguments!\t" ;
				break;
			}
			
			// conversion of strings to correct types:
			float lX = atof ( input[i][4].c_str() );
			float lY = atof ( input[i][5].c_str() );
			float lZ = atof ( input[i][6].c_str() );
			
			float hX = atof ( input[i][7].c_str() );
			float hY = atof ( input[i][8].c_str() );
			float hZ = atof ( input[i][9].c_str() );
		
			
			Material* m = world->get_material( input[i][10] );

	cout << input[i][10] << " ist material : " << world->get_material (  input[i][10] )->name() << endl;
			// integrate into world
			world->push_shape( new Box( input[i][3], Point( lX, lY, lZ), Point( hX, hY, hZ ), m ) ); 
			
		}
		else if( sphere(input[i]) )
		{
			cout << "Adding sphere \"" << input[i][3] << "\" ...\n";
			
			// check for input sanity
			if (input[i].size() != 9)
			{
				cerr << "\tInvalid number of arguments!\t" ;
				break;
			}
			
			// conversion of strings to correct type :
			float cX = atof ( input[i][4].c_str() );
			float cY = atof ( input[i][5].c_str() );
			float cZ = atof ( input[i][6].c_str() );
			
			float r = atof ( input[i][7].c_str() );
			
			
			Material* mat = world->get_material( input[i][8] );

			
			// integrate into world
			world->push_shape( new Sphere( input[i][3], Point( cX, cY, cZ), r, mat ) ); 
		}
		else if( composite(input[i]) )
		{
			cout << "Adding composite \"" << input[i][3] << "\" ...\n";
			
			// create composite shape to fill
			CompositeShape* temp = new CompositeShape( input[i][3] );
			
			// fill it with the remaining arguments
			for (unsigned int j = 4; j < input[i].size(); ++j)
			{
				temp->push(world->get_and_remove_shape( input[i][j] ));
			}
			
			// and add it to the world
			world->push_shape( temp );
		}
		else if( alight(input[i]) )
		{
			cout << "Adding ambient light \"" << input[i][3] << "\" ...\n";
			
			// check for input sanity
			if (input[i].size() != 7)
			{
				cerr << "\tInvalid number of arguments!\t" ;
				break;
			}
			
			// conversion of strings to correct type :
			float r = atof ( input[i][4].c_str() );
			float g = atof ( input[i][5].c_str() );
			float b = atof ( input[i][6].c_str() );
			
			// integrate into world
			world->set_ambient ( new AmbientLight ( input[i][3], rgb ( r, g, b)));
		}
		else if( dlight(input[i]) )
		{
			cout << "Adding diffuse light \"" << input[i][3] << "\" ...\n";
			
			// check for input sanity
			if (input[i].size() != 10)
			{
				cerr << "\tInvalid number of arguments!\t" ;
				break;
			}
			
			// conversion of strings to correct type :
			
			float x = atof ( input[i][4].c_str() );
			float y = atof ( input[i][5].c_str() );	
			float z = atof ( input[i][6].c_str() );	
					
			float r = atof ( input[i][7].c_str() );
			float g = atof ( input[i][8].c_str() );
			float b = atof ( input[i][9].c_str() );
			
			// integrate into world
			world->push_light ( new PointLight ( input[i][3], Point( x, y, z), rgb ( r, g, b) ));
		}
		else if( camera(input[i]) )
		{
			cout << "Adding camera \"" << input[i][2] << "\" ...\n";
			
			// check for input sanity
			if (input[i].size() != 6)
			{
				cerr << "\tInvalid number of arguments!\t" ;
				break;
			}
			
			// conversion of strings to correct type :
			
			float angle = atof ( input[i][3].c_str() );
			float x_res = atof ( input[i][4].c_str() );	
			float y_res = atof ( input[i][5].c_str() );	
					
			// integrate into world
			world->push_camera ( new Camera ( input[i][2], x_res, y_res, angle ));
		}
		else if( transform(input[i]) )
		{
			cout << "Applying transformation \"" << input[i][2] << "\" to shape \"" << input[i][1] << "\" ...\n";
			
			/*	
			MISSING FEATURE!
			WAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAGH!!!
			SYNTAX ERROR!
			*/
			
		}
		else if( render(input[i]) )
		{
			cout << "\n Now rendering scene as seen through \"" << input[i][1] << "\" and outputting to file \"" << input[i][2] << "\" !\n\n";
			
			if (input[i].size() != 3)			
			{
				cerr << "\tInvalid number of arguments!\t" ;
				break;
			}
			
			Camera* cam = world->get_camera( input[i][1] );
			cam->render( input[i][2] );
			
		}
		else
		{
			cerr << "Error: Cannot parse input: \n\t";
			for (unsigned int j = 0; j < input[i].size(); ++j)
			{
				cerr << input[i][j] << " ";
			}
			cerr << endl;
		}
	}	
}




bool
sdfloader::phong( vector < string>& word)
{
	if ( word[0] == "define" && word[1] == "material" && word[2] == "phong")
		return true;
	else
		return false;
}


bool
sdfloader::reflective( vector < string>& word)
{
	if ( word[0] == "define" && word[1] == "material" && word[2] == "reflective")
		return true;
	else
		return false;
}


bool
sdfloader::transparent( vector < string>& word)
{
	if ( word[0] == "define" && word[1] == "material" && word[2] == "transparent")
		return true;
	else
		return false;
}


bool
sdfloader::box( vector < string>& word)
{
	if ( word[0] == "define" && word[1] == "shape" && word[2] == "box" )
		return true;
	else
		return false;
}

bool
sdfloader::sphere( vector < string>& word)
{
	if ( word[0] == "define" && word[1] == "shape" && word[2] == "sphere" )
		return true;
	else
		return false;
}

bool
sdfloader::composite( vector < string>& word)
{
	if ( word[0] == "define" && word[1] == "shape" && word[2] == "composite" )
		return true;
	else
		return false;
}

bool
sdfloader::alight( vector < string>& word)
{
	if ( word[0] == "define" && word[1] == "light" && word[2] == "ambient" )
		return true;
	else
		return false;
}

bool
sdfloader::dlight( vector < string>& word)
{
	if ( word[0] == "define" && word[1] == "light" && word[2] == "diffuse" )
		return true;
	else
		return false;
}

bool
sdfloader::camera( vector < string>& word)
{
	if ( word[0] == "define" && word[1] == "camera" )
		return true;
	else
		return false;
}

bool
sdfloader::render( vector < string>& word)
{
	if ( word[0] == "render" )
		return true;
	else
		return false;
}

bool
sdfloader::transform( vector < string>& word)
{
	if ( word[0] == "transform" )
		return true;
	else
		return false;
}
