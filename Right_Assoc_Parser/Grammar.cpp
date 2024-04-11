#include "Grammar.hpp"
#include "Token.hpp"

using namespace std;

int expr(std::ifstream &is)
{
  int lhs = term(is); // all three grammar rule options start with term

  int pos = is.tellg();
  
  Token pm;
  is >> pm;

  if (pm.type() == PLUS)
    {
      return lhs + expr(is);
    }
  else if  (pm.type() == MINUS)
    {
      return lhs - expr(is);
    }
  else // we shouldn't have read the token !!!
    {
      // unget the token !!!
      is.seekg(pos);

      return lhs;
    }
}

int term(std::ifstream &is)
{
  int lhs = factor(is); // all three grammar rule options start with term

  int pos = is.tellg();
  
  Token pm;
  is >> pm;

  if (pm.type() == MULTIPLY)
    {
      return lhs * term(is);
    }
  else if  (pm.type() == DIVIDE)
    {
      return lhs / term(is);
    }
  else // we shouldn't have read the token !!!
    {
      // unget the token !!!
      is.seekg(pos);

      return lhs;
    }

}

int factor(std::ifstream &is)
{
  Token tok;
  is >> tok;

  if (tok.type()== INTEGER)
    {
      return atoi(tok.value().c_str());
    }
  else if (tok.type() == LPAREN)
    {
      int pval = expr(is);

      is >> tok;
      if (tok.type()!=RPAREN)
	cerr << "Expected ')', got:" << tok << endl;

      return pval;
    }
  else // invalid token to start a factor
    {
      cerr << "Unexpected token: " << tok << endl;
      return 0;
    }
}
