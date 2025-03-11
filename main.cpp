#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
#include "pixel.h"

using namespace std;

//function to parse a line and retunr a Pixel object
Pixel make_pixel(string line)
{
	Pixel pixel;
	int pos;

	//extract x
	pos=line.find(',');
	pixel.x=stoi(line.substr(0, pos));
	line =line.substr(pos+1);

	//extract y
	pos=line.find(',');
	pixel.y=stoi(line.substr(0, pos));
	line=line.substr(pos+1);

	//extract r
	pos=line.find(',');
	pixel.r=stof(line.substr(0, pos));
	line=line.substr(pos+1);

	//extract g
	pos=line.find(',');
	pixel.g=stof(line.substr(0, pos));
	line=line.substr(pos+1);

	//extract b(last value)
	pixel.b=stof(line);
	return pixel;
}

//function to calculate average colors
void average_colors(vector<Pixel> &pixel_list)
{
	float total_r=0, total_g=0, total_b=0;
	int size=pixel_list.size();

	for(const auto &p: pixel_list)
	{
		total_r+=p.r;
		total_g+=p.g;
		total_b+=p.b;
	}

	cout <<"Average R: " <<total_r/size <<endl;
	cout <<"Average G: "<<total_g/size <<endl;
	cout <<"Average B: "<<total_b/size <<endl;
}

//function to flip thge pixels vertically
void flip_vertically(vector<Pixel> &pixel_list)
{
	int max_y=255; //since y ranges from 0 to 255

	for(auto &p: pixel_list)
	{
		p.y=max_y -p.y;
	}
}

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		cerr <<"Usage: "<<argv[0] <<"<filename>" <<endl;
		return 1;
	}
}
	
	string filename=argv[1];
	ifstream infile(filename);

	if(!infile)
	{
		cerr<<"Error opening file." <<endl;
		return 1;
	}

	vector <Pixel> pixel_list;
	string line;

	//Read and parse pixels from the file
	while(getline(infile, line))
	{
		pixel_list.push_back(make_pixel(line));
	}
	infile.close();

	//calculate average colors
	average_colors(pixel_list);

	//flip_pixels vertically
	flip_vertically(pixel_list);

	//write the flipped data to flipped.dat
	ofstream outfile("flipped.dat");
	if(!outfile)
	{
		cerr<<"Error creating output file." <<endl;
		return 1;
	}

	for(const auto &p: pixel_list)
	{
		outfile <<p.x<< "," <<p.y <<"," <<p.r << "," <<p.g <<"," <<p.b <<endl;
	}
	outfile.close();
	cout <<"Flipped image saved to flipped.dat" <<endl;
		
	return 0;
}
