#include "TFile.h"
#include "TTree.h"

#include <iostream>  
#include <cstring>
#include <vector>



//const float e=1.602*pow(10,-19);
//const float m_e=9.1*pow(10,-31);

float B_x_P(float x, float y, float z){

	return 5;
}
float B_y_P(float x, float y, float z){

	return 0;
}
float B_z_P(float x, float y, float z){

	return 0;
}
void full(std::vector<float> co,std::vector<float> vo, std::vector<std::string> B_o ,float m,float q){
        const int N_events = 2000;
        const float t=0.001;

  	std::vector<float> B{0,0,0};
  	std::vector<float> c = co;
  	std::vector<float> c_prev = co;
  	std::vector<float> V = vo;
  	std::vector<float> V_prev = vo;
  	std::vector<float> a{0,0,0};
  	

        std::unique_ptr<TFile> myFile( TFile::Open("file.root", "RECREATE") ); 
        auto tree = std::make_unique<TTree>("trace_tree", "The Tree Title"); 

        tree->Branch("coordx", &c[0]); 
        tree->Branch("coordy", &c[1]); 
        tree->Branch("coordz", &c[2]); 
        tree->Branch("Vx", &V[0]); 
        tree->Branch("Vy", &V[1]); 
        tree->Branch("Vz", &V[2]); 
  
 for (int iEntry = 0; iEntry < N_events ; ++iEntry) { 
   B[0]=B_x_P(c_prev[0], c_prev[1], c_prev[2]);
   B[1]=B_y_P(c_prev[0], c_prev[1], c_prev[2]);
   B[2]=B_z_P(c_prev[0], c_prev[1], c_prev[2]);
   a[0] = q*(V[1]*B[2]-V[2]*B[1])/m;
   a[1] = q*(V[2]*B[0]-V[0]*B[2])/m;
   a[2] = q*(V[0]*B[1]-V[1]*B[0])/m;
   V[0] = V_prev[0]+t*a[0];
   V[1] = V_prev[1]+t*a[1];
   V[2] = V_prev[2]+t*a[2];
   V_prev[0] = V[0];
   V_prev[1] = V[1];
   V_prev[2] = V[2];
   c[0] = c_prev[0]+(V[0]*t+0.5*t*t*a[0]);
   c[1] = c_prev[1]+(V[1]*t+0.5*t*t*a[1]);
   c[2] = c_prev[2]+(V[2]*t+0.5*t*t*a[2]);
   c_prev[0] = c[0];
   c_prev[1] = c[1];
   c_prev[2] = c[2];
   // Fill the current value of var into branch0 
   tree->Fill(); 
  
} 
 
// Now write the header 
tree->Write();

}

void input(){
  float m;
  float q;

  std::vector<float> coor{0,0,0};
  std::vector<float> vel{0,0,0};
  std::vector<std::string> B{"","",""};

  std::cout << "Enter the mass of  the particle (in e mass)" << std::endl;
  std::cin >> m ;
  
  std::cout << "Enter the charge of  the particle (in e charge)" << std::endl;
  std::cin >> q ;
  
  std::cout << "Enter the initial coordinates of  the particle (x, y, z)" << std::endl;
  std::cin >> coor[0] >> coor[1] >> coor[2] ;
  
  std::cout << "Enter the initial velocity of  the particle (Vx, Vy, Vz)" << std::endl;
  std::cin >> vel[0] >> vel[1] >> vel[2] ;
  
  std::cout << "Enter a dependency B_x (x, y, z)" << std::endl;
  std::cin >> B[0];
  
  std::cout << "Enter a dependency B_y (x, y, z)" << std::endl;
  std::cin >> B[1];
  
  std::cout << "Enter a dependency B_z (x, y, z)" << std::endl;
  std::cin >> B[2];
full( coor, vel, B, m, q);
}


