#include "Token.hpp"

using namespace std;



istream&
Token::read(istream &is)
{
  // add code here to read in next token ...
}

const string 
Token::stype() const
{
  switch(_type)
  {
    case INTEGER:
      return "INTEGER";
    case LPAREN:
      return "LPAREN";
    case RPAREN:
      return "RPAREN";
    case PLUS:
      return "PLUS";
    case MINUS:
      return "MINUS";
    case MULTIPLY:
      return "MULTIPLY"; 
    case DIVIDE:
      return "DIVIDE"; 
    default: 
      return "ERROR";
  }
}
ostream& Token::print(std::ostream &os) const
{
  os<< _value; 
  return os;
}

ostream& operator<<(ostream &os, const Token &t)
{
  return t.print(os);
}

istream& operator>>(istream &is, Token &t)
{
  return t.read(is);
}
