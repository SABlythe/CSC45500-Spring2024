#include <fstream>
#include <iostream>
#include <string>

#include "Token.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  ifstream ifile(argv[1]);
  
  Token t;
  ifile >> t;

  while (ifile)
    {
      cout << t << ": " << t.stype() << "(" << t.type() << ")" << endl;
      ifile >> t;
    }

  return 0;
}
