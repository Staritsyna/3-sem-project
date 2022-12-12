
#ifndef INPUT_H
#define INPUT_H 1

#include <string>
#include <vector>

float B_x_P(float x, float y, float z, std::string B);
float B_y_P(float x, float y, float z, std::string B);
float B_z_P(float x, float y, float z, std::string B);

void full(std::vector<float> co,std::vector<float> vo, std::vector<std::string> B_o ,float m,float q);
void input();

#endif
