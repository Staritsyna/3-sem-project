#include "TFile.h"
#include "TTree.h"

#include <iostream>  
#include <cstring>
#include <vector>

#include "read_exp.h"
#include "input.h"

float B_x_P(float x, float y, float z, std::string B){
	Expression Bx(B);
	return Bx.Calc( x, y, z) ;
}
float B_y_P(float x, float y, float z, std::string B){
	Expression By(B);
	return By.Calc( x, y, z) ;
}
float B_z_P(float x, float y, float z, std::string B){
	Expression Bz(B);
	return Bz.Calc( x, y, z) ;
}

void partB(std::vector<float>& B,std::vector<float> c1,std::vector<float> c2,std::vector<float> v,float q){
	std::vector<float> r(3,0);
	r[0] = c1[0]-c2[0];
	r[1] = c1[1]-c2[1];
	r[2] = c1[2]-c2[2];
	float dist = sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
	if ( dist == 0) throw std::string ("division by zero");
		
	B[0] += pow(10,-26)*1.6*q*(v[1]*r[2]-v[2]*r[1])/(pow(dist,3));
	B[1] += pow(10,-26)*1.6*q*(v[2]*r[0]-v[0]*r[2])/(pow(dist,3));
	B[2] += pow(10,-26)*1.6*q*(v[0]*r[1]-v[1]*r[0])/(pow(dist,3));

}

void El(int i,std::vector<float>& a,std::vector<float> c1,std::vector<float> c2,float q1,float q2,float m){
	std::vector<float> r(3,0);
	r[0] = c1[0]-c2[0];
	r[1] = c1[1]-c2[1];
	r[2] = c1[2]-c2[2];
	float dist = sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]);
	if ( dist == 0) throw std::string ("division by zero");
		
	a[0] += 1.6*1.6*9*100*q1*q2*r[0]/(9.1*m*pow(dist,3));
	a[1] += 1.6*1.6*9*100*q1*q2*r[1]/(9.1*m*pow(dist,3));
	a[2] += 1.6*1.6*9*100*q1*q2*r[2]/(9.1*m*pow(dist,3));

}
void full(int n,  std::vector<std::vector<float>> co, std::vector<std::vector<float>> vo, std::vector<std::string> B_o ,std::vector<float> m,std::vector<float> q){
        const int nEvents = 2000;
        const float t=0.001;

  	std::vector<float> B{0,0,0};
  	std::vector<std::vector<float>> c = co;
  	std::vector<std::vector<float>> c_prev = co;
  	std::vector<std::vector<float>> V = vo;
  	std::vector<std::vector<float>> V_prev = vo;
  	
  	std::vector<std::vector<float>> a(n,{0,0,0});
  	
 	
	std::unique_ptr<TFile> myFile( TFile::Open("/home/anna/project/fileTrace.root", "RECREATE") ); 
	auto tree = std::make_unique<TTree>("tree", "tree"); 

	for (int i = 0; i < n; i++){
        	char brnch[120];
		sprintf(brnch,"coordx%d",i);
        	tree->Branch(brnch, &c[i][1]);
        	sprintf(brnch,"coordy%d",i);
        	tree->Branch(brnch, &c[i][1]);
        	sprintf(brnch,"coordz%d",i); 
        	tree->Branch(brnch, &c[i][2]); 
        	sprintf(brnch,"Vx%d",i);
        	tree->Branch(brnch, &V[i][0]); 
        	sprintf(brnch,"Vy%d",i);
        	tree->Branch(brnch, &V[i][1]); 
        	sprintf(brnch,"Vz%d",i);
        	tree->Branch(brnch, &V[i][2]);
	}
  	for (int k = 0; k < nEvents; k++){
  	     for (int i = 0; i < n; i++){
		
   		B[0]=B_x_P(c_prev[i][0], c_prev[i][1], c_prev[i][2], B_o[0]);
   		B[1]=B_y_P(c_prev[i][0], c_prev[i][1], c_prev[i][2],B_o[1]);
		B[2]=B_z_P(c_prev[i][0], c_prev[i][1], c_prev[i][2],B_o[2]);
		for (int m0 = 0; m0 < n; m0++){
			if (m0 != i){
				partB(B, c_prev[i],c_prev[m0], V_prev[m0], q[i]);
				El(i,a[i],c_prev[i],c_prev[m0], q[i],q[m0], m[i]);
				}
			}
		a[i][0] += 1.6*pow(10,12)*q[i]*(V[i][1]*B[2]-V[i][2]*B[1])/(9.1*m[i]);
		a[i][1] += 1.6*pow(10,12)*q[i]*(V[i][2]*B[0]-V[i][0]*B[2])/(9.1*m[i]);
		a[i][2] += 1.6*pow(10,12)*q[i]*(V[i][0]*B[1]-V[i][1]*B[0])/(9.1*m[i]);
		V[i][0] = V_prev[i][0]+t*a[i][0];
		V[i][1] = V_prev[i][1]+t*a[i][1];
		V[i][2] = V_prev[i][2]+t*a[i][2];
		V_prev[i][0] = V[i][0];
		V_prev[i][1] = V[i][1];
		V_prev[i][2] = V[i][2];
		c[i][0] = c_prev[i][0]+(V[i][0]*t+0.5*t*t*a[i][0]);
		c[i][1] = c_prev[i][1]+(V[i][1]*t+0.5*t*t*a[i][1]);
		c[i][2] = c_prev[i][2]+(V[i][2]*t+0.5*t*t*a[i][2]);
		c_prev[i][0] = c[i][0];
		c_prev[i][1] = c[i][1];
		c_prev[i][2] = c[i][2];
		} 
		
		tree->Fill(); 
	}
tree->Write();
}

void input(int np){


  std::vector<std::vector<float>> coord;
  std::vector<std::vector<float>> vel;
  std::vector<std::string> B{"","",""};
  
  std::cout << "Enter a dependency B_x (x, y, z)" << std::endl;
  std::cin >> B[0];
  
  std::cout << "Enter a dependency B_y (x, y, z)" << std::endl;
  std::cin >> B[1];
  
  std::cout << "Enter a dependency B_z (x, y, z)" << std::endl;
  std::cin >> B[2];
 
  std::vector<float> m (np,0);
  std::vector<float> q (np,0);
  for (int i=0; i < np; i++){
  	std::vector<float> coor1;
  	std::vector<float> vel1;
  	for (int i=0; i < 3; i++){
  		coor1.push_back(0);
  		vel1.push_back(0);
  	}
  	coord.push_back(coor1);
  	vel.push_back(vel1);
  }
  for (int i = 0; i < np; i++){
  std::cout <<  "Enter the mass of  the "<< i+1<< " particle (in e mass)" << std::endl;
  std::cin >> m[i] ;
  
  std::cout << "Enter the charge of  the particle (in e charge)" << std::endl;
  std::cin >> q[i] ;
  
  std::cout << "Enter the initial coordinates of  the particle (x, y, z)" << std::endl;
  std::cin >> coord[i][0] >> coord[i][1] >> coord[i][2] ;
  
  std::cout << "Enter the initial velocity of  the particle (Vx, Vy, Vz)" << std::endl;
  std::cin >> vel[i][0] >> vel[i][1] >> vel[i][2] ;
  
  }  
   full( np,coord, vel, B, m, q);
}





