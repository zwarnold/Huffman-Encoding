//Zach Arnold
//4/9/2012
//Lab 7 hencode.cc


#include "pri_queue.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "hnode.h"



using namespace std;

string codes[256]; //global array

void usage2()
{
  cout << "Usage: hencode filename " << endl;
  exit(1);
}

size_t power(size_t base, size_t exp)
{
  return exp == 0?1: base * power(base, exp - 1); //recursive power fn
}

void writeTree(Hnode * tree, ostream & ostr)
{
  if (!tree->left) //base case of null pointer
    ostr << "L" << tree->ch;
  //else write for internal leaf and then right the left and right trees
  else {
    ostr << "I";
    writeTree(tree->left, ostr);
    writeTree(tree->right, ostr);
  }  
}

unsigned char toUnsignedChar(string s)
{
  unsigned char c;
  //loop through the bit string
  for(size_t i = 0; i < 8; i++)
    if (s[i] == '1') {
      c += (128 / power(2, i));
    }
 
  return c;   
}

void prependAll(char bit, Hnode * tree)
{
  if (!tree->left)
    codes[tree->ch] = bit + codes[tree->ch]; //prepend the bit
  else{
    //recurse
    prependAll(bit, tree->left);
    prependAll(bit, tree->right);
  }
}

int Hnodecmp(void * a, void * b)
{
  //generic comparison b/w a and b
  Hnode * ap = (Hnode *) a;
  Hnode *ab = (Hnode *) b;
  return ap->count - ab->count;  
}
      


int main(int argc, char **argv)
{
  size_t counts[256];
  
  for (size_t i = 0 ; i < 256 ; i++)
    counts[i] = 0; //initializing an array

  if (argc != 2)
    usage2();
  
  string filename = argv[1];
  //List list;
  unsigned char ch;
  string orig;

  ifstream in(filename.c_str()); //set up inBuf
  string outFileNm = string(filename) + string(".huf");
  const char * outFileName = outFileNm.c_str();
  ofstream out(outFileName);// establish outBuff
  
  while(1){ //read in the inFile and add it to a list
    ch = in.get();
    if (in.fail())
      break;
    counts[ch]++; //increment the counts according to ch
    orig += ch; //store the file in a string
  }
  
  if (orig.length() == 0)//handle an empty file
    return 1;
  
  PriQueue pq = PriQueue(Hnodecmp); //create heap
  
  for (size_t i=0; i<256; i++)
    if (counts[i])
      pq.add(new Hnode(i, counts[i]));

  void * tree1;
  void * tree2;
  while (pq.get_size() > 1) {
    tree1 = pq.remove();
    tree2 = pq.remove();
    prependAll('0', (Hnode*)tree1);
    prependAll('1', (Hnode*)tree2);
    pq.add(new Hnode((Hnode*)  tree1, (Hnode*)  tree2)); //create huffman tree
  }
 
  string encodedBits;
  
  size_t len = orig.length();

  for (size_t i=0; i<len; i++){
    encodedBits += codes[(unsigned char)orig[i]];//put codes into a string
  }
  out << encodedBits.length();//out put origional number of bits
  size_t remainder = -(encodedBits.size() % 8) + 8;
  for (size_t r = remainder; r > 0; r--) //add the according number of zeros
    encodedBits += '0';
  
  string encodedChars;
  string subs;
  for(size_t i = 0; i < encodedBits.length(); i += 8){
    for (size_t j = 0; j < 8; j++){   
      subs[j] = encodedBits[i + j]; //get the bytes
    }
    
    ch = toUnsignedChar(subs); //convert each byte to one char
    encodedChars += ch; //add it to the string of chars
  }
  
  writeTree((Hnode*)pq.remove(), out); //output tree to the file
  for (size_t i = 0; i < encodedChars.length(); i++){
    out.put(encodedChars[i]);//output the encoded chars
  
  }  
  remove(filename.c_str()); //delete the file
}


