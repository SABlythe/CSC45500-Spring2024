#include "Grammar.hpp"
#include "Token.hpp"

using namespace std;

int expr(std::ifstream &is)
{
  int termVal = term(is);

  int expr2Val = expr2(is, termVal);

  return expr2Val;
}

int expr2(std::ifstream &is, int incomingValue)
{
  int pos = is.tellg();
  Token pm;
  is >> pm;

  int result = incomingValue;

  if (pm.type()==PLUS)
    {
      int termVal = term(is);
      result += termVal;
    }
  else if (pm.type()==MINUS)
    {
      int termVal = term(is);
      result -= termVal;
    }
  else // epsilon case
    {
      is.seekg(pos);
      return incomingValue;
    }
  
  return expr2(is, result);
}

int term(std::ifstream &is)
{
  int factorVal = factor(is);

  int term2Val = term2(is, factorVal);

  return term2Val;
}

int term2(std::ifstream &is, int incomingValue)
{
  int pos = is.tellg();
  Token md;
  is >> md;

  int result = incomingValue;

  if (md.type()==MULTIPLY)
    {
      int factorVal = factor(is);
      result *= factorVal;
    }
  else if (md.type()==DIVIDE)
    {
      int factorVal = factor(is);
      result /= factorVal;
    }
  else // epsilon case
    {
      is.seekg(pos);
      return incomingValue;
    }
  
  return term2(is, result);
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
