#ifndef _GRAMMAR_HPP_
#define _GRAMMAR_HPP_

#include <fstream>
#include <iostream>

int expr(std::ifstream &);
int expr2(std::ifstream &, int lhs);
int term(std::ifstream &);
int term2(std::ifstream &, int lhs);
int factor(std::ifstream &);


#endif
