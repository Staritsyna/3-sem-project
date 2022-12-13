#include <iostream> 
#include <vector> 
#include <string>
#include "math.h"

#include "read_exp.h"

int Expression::operationPriority(char c){
   	if (c == '('){
		return 0;
		}
	if (c == ')'){
		return 0;
		}
	if ((c == '-')||(c == '+')){
		return 1;
		}
	if ((c == '*')||(c == '/')){
		return 2;
		}
	if (c == '^'){
		return 3;
		}
		
	if (c == '~'){
		return 4;
		}
	return -1;
}
std::string Expression::GetStringNumber(std::string expr,  int& pos) 
{ 
  std::string strNumber = ""; 
 
  for (; pos < expr.length(); pos++) 
  { 

    char num = expr[pos]; 
  
   
    if ((operationPriority(num) == -1) and (num != ' '))

    {
      strNumber += num; }
    else 
    { 
      pos--; 
      break; 
    }
   
  } 

  return strNumber; 
}	 

std::string Expression::ToPostfix(std::string infixExpr) 
{ 
     
     postfixExpr = ""; 
   
    std::vector<char> operation; 
 
   int i = 0;
   while (i < infixExpr.length())
    { 
      char c = infixExpr[i]; 
       
      if (operationPriority(c) == -1) 
      { 
        if (c == 'x'){
        	postfixExpr += "x ";
        }
          else if (c == 'y'){
        	postfixExpr += "y ";
        }
          else if (c == 'z'){
        	postfixExpr += "z ";
        }
        else{
        std::string gs=GetStringNumber(infixExpr,  i); 
        postfixExpr += gs;
        postfixExpr +=" "; 
         }
      } 
       
      else if (c == '(') 
      { 
         operation.push_back(c); 
      } 
      
      else if (c == ')') 
      { 
          while (operation.size() > 0 && operation[operation.size()-1] != '(') {
              postfixExpr += operation[operation.size()-1];
              operation.pop_back(); 
          }
          operation.pop_back(); 
      } 
   
      else if (operationPriority(c)>0) 
      { 
        char op = c; 

        if (op == '-' && (i == 0 || (i > 1 && operationPriority( infixExpr[i-1] )>=0))) {
          
          op = '~'; }
        
        while (operation.size() > 0 && ( operationPriority(operation[operation.size()-1])>= operationPriority(op))) {
       
          postfixExpr += *(operation.end()-1); 
          operation.pop_back(); 
           }
        operation.push_back(op); 
      }
      i++; 
    } 
    for (int i=operation.size()-1; i>-1; i--) {
       postfixExpr += operation[i]; 
 }
    return postfixExpr; 
}

Expression::Expression(std::string expr) 
    { 
        infixExpr = expr; 
        postfixExpr = ToPostfix(infixExpr ); 
    } 
    
double Expression::Execute(char op, double first, double second) { 
 	if (op == '+'){ 
 		return first+second;
 		}
 	if (op == '-'){ 
 		return first-second;
 		}
 	if (op == '*'){ 
 		return first*second;
 		}
 	if (op == '/'){ 
 		if ( second == 0) throw std::string ("division by zero");
 		return first/second;
 		}
 	if (op == '^'){ 
 		return pow(first, second);
 		}
 	return 0;   
}
	
double Expression::Calc(float x, float y, float z) 
{ 
    std::vector<double> locals ;
    int cnt = 0; 

    for (int i = 0; i < postfixExpr.length(); i++) 
    { 
        char c = postfixExpr[i]; 
     
        if ((operationPriority(c)<0) & ( c != ' '))
        { 
          if (c == 'x'){
        	locals.push_back(x);
        }
          else if (c == 'y'){
        	locals.push_back(y);
        }
          else if (c == 'z'){
        	locals.push_back(z);
        }
          else {
            std::string number = GetStringNumber(postfixExpr,  i);
            double q=stof(number);
            locals.push_back(q); 
         }
        } 
        
        if (operationPriority(c) > 0) 
        { 
            cnt += 1; 
            if (c == '~') 
            { 
                double last =  0; 
                if (locals.size() > 0 ){
                	last = *(locals.end()-1); 
                	locals.pop_back();
                }
                locals.push_back(Execute('-', 0, last)); 
               
                continue; 
            } 
       
           double second =  0; 
                if (locals.size() > 0 ){
                	second = *(locals.end()-1); 
                	locals.pop_back();
                }
            double first =  0; 
                if (locals.size() > 0 ){
                	first = *(locals.end()-1);  
                	locals.pop_back();
                }
  
            locals.push_back(Execute(c, first, second)); 
        } 
    } 
   
    return *(locals.end()-1);
}
