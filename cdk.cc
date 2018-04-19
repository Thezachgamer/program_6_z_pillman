/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <string>
#include <cstdint>
#include <sstream>
#include <locale>
#include <stdio.h>
#include <ctype.h>



#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;


template <class T>
string to_string(T t, ios_base & (*f)(ios_base&))
{
  ostringstream oss;
  oss << f << t;
  return oss.str();
}

//why can't c++ just be not bac
string toUpperCase(string s){
  locale loc;
  string rtn;
  for(int i = 0; i < s.length(); i++){
    rtn += toupper(s[i], loc);

  }
  return rtn;
}


int main()
{

  ifstream inFile;
  inFile.open("cs3377.bin", ios::binary | ios::in);

  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
  uint8_t strLength;
  char stringBuffer[25];

  //read in header
  if(inFile.is_open()){
    //cout << "we did it boss" << endl;
    inFile.read(reinterpret_cast<char *>(&magicNumber), sizeof(magicNumber));
    //cout << std::hex  << magicNumber << endl;
    inFile.read(reinterpret_cast<char *>(&versionNumber), sizeof(versionNumber));
    //cout << versionNumber << endl;
    inFile.read(reinterpret_cast<char *>(&numRecords), sizeof(numRecords));
    //cout << std::hex << numRecords << endl;
  }
  
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"C0", "a", "b", "c"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  
  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */

  stringstream ss;
  
  long totalRecords = static_cast<long>(numRecords);

  //build string for the magicnumber box
  string temp = "Magic: 0x";
  string temp2 = to_string<long>(magicNumber, hex);
  temp2 = toUpperCase(temp2);
  temp += temp2;
  setCDKMatrixCell(myMatrix, 1, 1, temp.c_str() );

  //build the string for version
  temp = "Version: ";
  temp2 = to_string(versionNumber); 
  temp += temp2;
  setCDKMatrixCell(myMatrix, 1, 2, temp.c_str() );
  
  //build string for numRecords
  temp = "numRecords: ";
  temp2 = to_string(numRecords);
  temp += temp2;
  setCDKMatrixCell(myMatrix, 1, 3, temp.c_str() );

  temp = "strlen: ";
  temp2 = "";
  //for each element in the the file, read and print the information from it 
  for(int i = 0; i < totalRecords && i < 4; i++){

    if(inFile.is_open() && !inFile.eof()){

    inFile.read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
    inFile.read(stringBuffer, sizeof(stringBuffer));
    
    temp2 = temp + to_string(strLength);
    
    setCDKMatrixCell(myMatrix, (i + 2), 1, temp2.c_str() );
    setCDKMatrixCell(myMatrix, (i + 2), 2, stringBuffer );
    }

  }


  /*
  //print out first string in file
  temp = "strlen: ";
  temp2 = to_string(strLength);
  temp += temp2;
  
  
  
  //read in second string
  if(inFile.is_open()){
    inFile.read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
    inFile.read(stringBuffer, sizeof(stringBuffer));
  }

  //print out second string in file
  temp = "strlen: ";
  temp2 = to_string(strLength);
  temp += temp2;
  setCDKMatrixCell(myMatrix, 3, 1, temp.c_str() );
  setCDKMatrixCell(myMatrix, 3, 2, stringBuffer );
  
  //read in third string
  if(inFile.is_open()){
    inFile.read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
    inFile.read(stringBuffer, sizeof(stringBuffer));
  }

  //print out third string in file
  temp = "strlen: ";
  temp2 = to_string(strLength);
  temp += temp2;
  setCDKMatrixCell(myMatrix, 4, 1, temp.c_str() );
  setCDKMatrixCell(myMatrix, 4, 2, stringBuffer );

  //read in fourth string in file
  if(inFile.is_open()){
    inFile.read(reinterpret_cast<char *>(&strLength), sizeof(strLength));
    inFile.read(stringBuffer, sizeof(stringBuffer));
  }

  //print out fourth string
  temp = "strlen: ";
  temp2 = to_string(strLength);
  temp += temp2;
  setCDKMatrixCell(myMatrix, 5, 1, temp.c_str() );
  setCDKMatrixCell(myMatrix, 5, 2, stringBuffer );
  */

  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (100);

  


  // Cleanup screen
  endCDK();
}
