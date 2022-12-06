#include <iostream> 
#include <vector> 
#include <cstring>
#include "math.h"
 class Expression 
{ 
int operationPriority(char c){
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
public: std::string infixExpr ;
	 std::string postfixExpr;	

 private: std::string GetStringNumber(std::string expr,  int& pos) 
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
	  std::string ToPostfix(std::string infixExpr) 
{ 
     
     postfixExpr = ""; 
   
    std::vector<char> operation; 
 
   int i = 0;
   while (i < infixExpr.length())
    { 
      char c = infixExpr[i]; 
       
      if (operationPriority(c) == -1) 
      { 
        std::string gs=GetStringNumber(infixExpr,  i); 
        postfixExpr += gs;
        postfixExpr +=" "; 
   
         
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
public: Expression(std::string expr) 
    { 
        infixExpr = expr; 
        postfixExpr = ToPostfix(infixExpr ); 
    } 
    
   double Execute(char op, double first, double second) { 
 	if (op == '+'){ return first+second;}
 	if (op == '-'){ return first-second;}
 	if (op == '*'){ return first*second;}
 	if (op == '/'){ return first/second;}
 	if (op == '^'){ return pow(first, second);}
 	return 0;   
}
	
	double Calc(float x, float y, float z) 
{ 
    std::vector<double> locals ;
    int cnt = 0; 

    for (int i = 0; i < postfixExpr.length(); i++) 
    { 
        char c = postfixExpr[i]; 
     
        if ((operationPriority(c)<0) & ( c != ' '))
        { 
            std::string number = GetStringNumber(postfixExpr,  i);
            double q=stof(number);
            locals.push_back(q); 
         
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
                	//std::cout<<locals.size()<<"GGG"; 
                	locals.pop_back();
                }
            double first =  0; 
                if (locals.size() > 0 ){
                	first = *(locals.end()-1); 
                	//std::cout<<"KKK"<<std::endl; 
                	locals.pop_back();
                }
  
            locals.push_back(Execute(c, first, second)); 
        } 
    } 
   
    return *(locals.end()-1);
}
};
int main(){
	std::string expr = "(3+5)*2/5";
	Expression  easy(expr);
	std::cout<<"Input "<< expr<<std::endl;
	std::cout << easy.postfixExpr<<std::endl;
	std::cout << easy.Calc(0,0,0)<<std::endl;

}
