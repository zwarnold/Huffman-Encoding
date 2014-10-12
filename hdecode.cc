//Zach Arnold
//4/29/2012
//Lab7 hdecode.cc

#include "pri_queue.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "hnode.h"
#include <string>

using namespace std;

size_t power(size_t base, size_t exp)
{
  return exp == 0? 1: base * power(base, exp - 1);
}

string toBitString(unsigned char c)
{
  string s = "00000000"; //string for bit
  //loop through the bit string
  for (size_t i = 0; i < 8; i++){
    if (c >= 128/power(2, i)){
      s[i] = '1';
      c -= 128/power(2, i);
    }
  }
  return s;
}

void usage()
{
  cout << "Usage: hdecode filename " << endl;
  exit(1);
} 

Hnode * readTree(istream & istr)
{
  //if a leaf then return a new HNode containing it else an HNode
  //containing the left and right trees
  return istr.get() == 'L'?new Hnode(istr.get(), 0):
  new Hnode(readTree(istr), readTree(istr));
}

void decodeBit(string & s, Hnode * tree, Hnode * root, ostream & ostr)
{
  //if the encoded string is gone out put the last char
  if (s.length() == 0){
    ostr << tree->ch;
    return;
  }
  
  string bit = s.substr(0, 1); //get the bit
  if (!tree->left){
    ostr << tree->ch; //if a leaf, output the char
    decodeBit(s, root, root, ostr); //start over
  }
  
  else{
    if (bit == "0"){
      s = s.substr(1, s.length()); //shorten the string of bits
      decodeBit(s, tree->left, root, ostr); //recurse
    }
    else {
      s = s.substr(1, s.length()); //shorten the string of bits
      decodeBit(s, tree->right, root, ostr); //recurse
    }
  }	   
}


int main(int argc, char **argv)
{
  if (argc != 2)
    usage();
  
  string outfile = argv[1];
  unsigned char ch;
  string encodedData; 
  size_t numOfBits;
  
  size_t sze = outfile.size();
  string outFileNm = outfile.substr(0, sze-4);
  const char * outFileName = outFileNm.c_str();
  ifstream in(outfile.c_str()); //set up inBuf
  ofstream out(outFileName); //set up outBuf

  string encodedTree;
  in >> numOfBits; //read in the number of bits
  Hnode * huffTree = readTree(in);
  string encodedBits;
  while(1){ //read in the inFile and add it to a list
    ch = in.get();
    if (in.fail())
      break;
    encodedBits += toBitString(ch); //change byte to bits
  }
  
  size_t len = encodedBits.length();
  // take off the extra bits
  encodedBits = encodedBits.substr(0, (len - (len - numOfBits)));
  decodeBit(encodedBits, huffTree, huffTree, out); //decode the bit string
  remove(outfile.c_str()); //delete the input file
  
}
