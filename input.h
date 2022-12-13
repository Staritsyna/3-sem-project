
#ifndef INPUT_H
#define INPUT_H 1

#include <string>
#include <vector>

float B_x_P(float x, float y, float z, std::string B);
float B_y_P(float x, float y, float z, std::string B);
float B_z_P(float x, float y, float z, std::string B);

void partB(std::vector<float>& B,std::vector<float> c1,std::vector<float> c2,std::vector<float> v,float q);
void full(int n,  std::vector<std::vector<float>> co, std::vector<std::vector<float>> vo,
 std::vector<std::string> B_o ,std::vector<float> m,std::vector<float> q);
void input(int np);

#endif
