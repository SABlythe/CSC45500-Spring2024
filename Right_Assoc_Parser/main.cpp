#include <fstream>
#include <iostream>
#include <string>

#include "Grammar.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  ifstream ifile(argv[1]);

  cout << expr(ifile) << endl;

  return 0;
}
