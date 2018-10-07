#include <stdio.h>
#include "cs1300bmp.h"
#include <iostream>
#include <fstream>
#include "Filter.h"

using namespace std;

#include "rtdsc.h"

//
// Forward declare the functions
//
Filter * readFilter(string filename);
double applyFilter(Filter *filter, cs1300bmp *input, cs1300bmp *output);

int
main(int argc, char **argv)
{

  if ( argc < 2) {
    fprintf(stderr,"Usage: %s filter inputfile1 inputfile2 .... \n", argv[0]);
  }

  //
  // Convert to C++ strings to simplify manipulation
  //
  string filtername = argv[1];

  //
  // remove any ".filter" in the filtername
  //
  string filterOutputName = filtername;
  string::size_type loc = filterOutputName.find(".filter");
  if (loc != string::npos) {
    //
    // Remove the ".filter" name, which should occur on all the provided filters
    //
    filterOutputName = filtername.substr(0, loc);
  }

  Filter *filter = readFilter(filtername);

  double sum = 0.0;
  int samples = 0;

  for (int inNum = 2; inNum < argc; inNum++) {
    string inputFilename = argv[inNum];
    string outputFilename = "filtered-" + filterOutputName + "-" + inputFilename;
    struct cs1300bmp *input = new struct cs1300bmp;
    struct cs1300bmp *output = new struct cs1300bmp;
    int ok = cs1300bmp_readfile( (char *) inputFilename.c_str(), input);

    if ( ok ) {
      double sample = applyFilter(filter, input, output);
      sum += sample;
      samples++;
      cs1300bmp_writefile((char *) outputFilename.c_str(), output);
    }
    delete input;
    delete output;
  }
  fprintf(stdout, "Average cycles per sample is %f\n", sum / samples);

}

struct Filter *
readFilter(string filename)
{
  ifstream input(filename.c_str());

  if ( ! input.bad() ) {
    int size = 0;
    input >> size;
    Filter *filter = new Filter(size);
    int div;
    input >> div;
    filter -> setDivisor(div);
    for (int i=0; i < size; i++) {
      for (int j=0; j < size; j++) {
	int value;
	input >> value;
	filter -> set(i,j,value);
      }
    }
    return filter;
  }
}


double
applyFilter(struct Filter *filter, cs1300bmp *input, cs1300bmp *output)
{

  long long cycStart, cycStop;

  cycStart = rdtscll();

  short int width = output -> width = input -> width;
  short int height = output -> height = input -> height;
  short int inwidth = width- 1;
  short int inheight = height - 1;
  
  // origin code:
  // for(int col = 1; col < (input -> width) - 1; col = col + 1) {
  // for(int row = 1; row < (input -> height) - 1 ; row = row + 1) {
  // for(int plane = 0; plane < 3; plane++) 
  
  // 
  // int a = (input -> width) - 1;
  // int b = (input -> height) - 1;
  // for(int plane = 0; plane < 3; plane++){
  // for(int row = 1; row < b; row = row + 1){
  // for(int col = 1; col < a; col = col + 1){
      
	/**in loop, the second always valued as a boolean expression. col-- will evaluate then subtract
	we switch the order of for loop because of memory alianment**/
	short int data0 = filter->data[0];
	short int data1 = filter->data[1];
	short int data2 = filter->data[2];
	short int data3 = filter->data[3];
	short int data4 = filter->data[4];
	short int data5 = filter->data[5];
	short int data6 = filter->data[6];
	short int data7 = filter->data[7];
	short int data8 = filter->data[8];

	short int d = filter -> getDivisor();
	for(int plane =3; plane--;){
		for(short int row = inheight-1; row--;){
			for(short int col = inwidth -1; col--;){
	

	// output -> color[plane][row][col] = 0; ** t = output -> color[plane][row][col] = 0;
	//for (int j = 0; j < filter->getSize(); j++) {
	//for (int i = 0; i < filter->getSize(); i++) {	
	    //output -> color[plane][row][col] = output -> color[plane][row][col] + (input -> color[plane][row + i - 1][col + j - 1] * filter -> get(i, j) );
		 //}
	//}
	/**filter->getSize() will give us a constant 3.
	 * since we only run these code 9 times, so we better to right them seperately to avoid loop overhead**/
	/**we need to avoid to call filter ->get many times, so we directly use this function in Filter.cpp
	 * and before that we need to let data be public**/
	short int x = row -1;
	short int y = row;
	short int z = row +1;
	short int a = col -1;
	short int b = col;
	short int c = col +1;
	//t = t + (input -> color[plane][row + 0 - 1][col + 0- 1] * filter->data[0] );
	/**since the row+0-1 .col+0-1... appear 3 times, so we can calculate first to aviod excessive operands**/
	short int t = (input -> color[plane][x][a] * data0 )+ 
		(input -> color[plane][x][b] * data1)+
		(input -> color[plane][x][c] *data2)+
		(input -> color[plane][y][a] *data3)+
		(input -> color[plane][y][b] *data4)+
		(input -> color[plane][y][c] *data5)+
		(input -> color[plane][z][a] *data6)+
		(input -> color[plane][z][b] *data7)+
		(input -> color[plane][z][c] *data8);
	
	if(d>0){
		t = t / d;
	}

	if ( t < 0 ) {
	  t = 0;
	}

	if ( t > 255 ) { 
	  t = 255;
	// origin code:
	//   t = t / filter-> getDivisor();
	//   if ( output -> color[plane][row][col]  < 0 ) {
	//   output -> color[plane][row][col] = 0;
	//   }
	//   if ( output -> color[plane][row][col]  > 255 ) { 
	//   output -> color[plane][row][col] = 255;
	//   }
	}
	output->color[plane][row][col] = t;
      }
    }
  }

  cycStop = rdtscll();
  double diff = cycStop - cycStart;
  double diffPerPixel = diff / (width * height);
  fprintf(stderr, "Took %f cycles to process, or %f cycles per pixel\n",
	  diff, diffPerPixel);
  return diffPerPixel;
}
