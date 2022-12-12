#ifndef READ_EXP_H
#define READ_EXP_H 1

#include <string>

class Expression 
{ 
public:
	std::string infixExpr ;
	std::string postfixExpr;
	Expression(std::string expr);
	double Execute(char op, double first, double second);
	double Calc(float x, float y, float z);
	
private:
	int operationPriority(char c);
	std::string GetStringNumber(std::string expr,  int& pos);
	std::string ToPostfix(std::string infixExpr);
};

#endif

