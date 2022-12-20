
#ifndef INPUT_H
#define INPUT_H 1

#include <string>
#include <vector>

double B_P(double x, double y, double z, std::string B);

void partB(std::vector<double>& B,std::vector<double> c1,std::vector<double> c2,std::vector<double> v,double q);
void El(std::vector<double>& a,std::vector<double> c1,std::vector<double> c2,double q1,double q2,double m);

void full(int n,  std::vector<std::vector<double>> co, std::vector<std::vector<double>> vo,
 std::vector<std::string> B_o ,std::vector<double> m,std::vector<double> q);
void input(int np);

#endif
