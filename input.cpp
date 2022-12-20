#include "TFile.h" 
#include "TTree.h" 
 
#include <iostream>   
#include <cstring> 
#include <vector> 
 
#include "read_exp.h" 
#include "input.h" 

double const m_e = 9.1;
double const q_e = 1.6;
double const k = 0.09;
double const b_o = 1e-26;
double const a_o = 1e5;

//the value of external magnetic field in the point (x,y,z) is calculated
double B_P(double x, double y, double z, std::string B){ 
	Expression B_s(B); 
	return B_s.Calc( x, y, z) ; 
} 

//the value of particales's magnetic field in the point (x,y,z) is calculated 
void partB(std::vector<double>& B,std::vector<double> const  c1,std::vector<double> const c2,std::vector<double> const v,double const q){ 
	std::vector<double> r(3,0); 
	r[0] = c1[0]-c2[0]; 
	r[1] = c1[1]-c2[1]; 
	r[2] = c1[2]-c2[2]; 
	double dist = sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]); 
	if ( dist == 0) throw std::string ("division by zero"); 

	B[0] += b_o*q_e*q*(v[1]*r[2]-v[2]*r[1])/(pow(dist,3)); 
	B[1] += b_o*q_e*q*(v[2]*r[0]-v[0]*r[2])/(pow(dist,3)); 
	B[2] += b_o*q_e*q*(v[0]*r[1]-v[1]*r[0])/(pow(dist,3));
} 

//the value of acceleration of 1 partical created by 2
void El(std::vector<double>& a,std::vector<double> c1,std::vector<double> c2,double q1,double q2,double m){ 
	std::vector<double> r(3,0); 
	r[0] = c1[0]-c2[0]; 
	r[1] = c1[1]-c2[1]; 
	r[2] = c1[2]-c2[2]; 
	double dist = sqrt(r[0]*r[0]+r[1]*r[1]+r[2]*r[2]); 
	if ( dist == 0) throw std::string ("division by zero"); 

	a[0] += k*q_e*q_e*q1*q2*r[0]/(m_e*m*pow(dist,3)); 
	a[1] += k*q_e*q_e*q1*q2*r[1]/(m_e*m*pow(dist,3)); 
	a[2] += k*q_e*q_e*q1*q2*r[2]/(m_e*m*pow(dist,3)); 
} 
//recreates fileTrace.root and fills it with data (velocity and coordinate of each partical)
void full(int n,  std::vector<std::vector<double>> co, std::vector<std::vector<double>> vo, 
std::vector<std::string> B_o ,std::vector<double> m,std::vector<double> q){ 

        const int nPoints = 10000; 
        const double t=0.001; 
 
	std::vector<double> B{0,0,0}; 
	std::vector<std::vector<double>> c = co; 
	std::vector<std::vector<double>> c_prev = co; 
	std::vector<std::vector<double>> V = vo; 
	std::vector<std::vector<double>> V_prev = vo; 
  	std::vector<std::vector<double>> a(n,{0,0,0}); 
  	
	std::unique_ptr<TFile> myFile( TFile::Open("/home/anna/project/fileTrace.root", "RECREATE") );  
	auto tree = std::make_unique<TTree>("tree", "tree");  
 
 	for (int i = 0; i < n; i++){ 
         char brnch[120]; 
  	 sprintf(brnch,"coordx%d",i); 
         tree->Branch(brnch, &c[i][0]); 
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
   	for (int k = 0; k < nPoints; k++){ 
   		
        	for (int i = 0; i < n; i++){ 
		    	B[0]=B_P(c_prev[i][0], c_prev[i][1], c_prev[i][2], B_o[0]); 
			B[1]=B_P(c_prev[i][0], c_prev[i][1], c_prev[i][2],B_o[1]); 
			B[2]=B_P(c_prev[i][0], c_prev[i][1], c_prev[i][2],B_o[2]); 
  	     	for (int m0 = 0; m0 < n; m0++){ 
             	   	if (m0 != i){ 
     				partB(B, c_prev[i],c_prev[m0], V_prev[m0], q[i]); 
     				El(a[i],c_prev[i],c_prev[m0], q[i],q[m0], m[i]); 
    		   } 
   	        } 
	  	a[i][0] += q_e*q[i]*(V[i][1]*B[2]-V[i][2]*B[1])/(m_e*m[i]); 
	  	a[i][1] += q_e*q[i]*(V[i][2]*B[0]-V[i][0]*B[2])/(m_e*m[i]); 
	 	a[i][2] += q_e*q[i]*(V[i][0]*B[1]-V[i][1]*B[0])/(m_e*m[i]); 
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
		a[i][0] = 0; 
	  	a[i][1] = 0; 
	 	a[i][2] = 0; 
		}  

	tree->Fill();  
 	} 
	tree->Write(); 
} 

//read initial data and fills file by full()
void input(int np){ 
	std::vector<std::vector<double>> coord; 
	std::vector<std::vector<double>> vel; 
	std::vector<std::string> B{"","",""}; 

	std::cout << "Enter a dependency B_x (x, y, z)" << std::endl; 
	std::cin >> B[0];
	std::cout << "Enter a dependency B_y (x, y, z)" << std::endl; 
	std::cin >> B[1]; 

	std::cout << "Enter a dependency B_z (x, y, z)" << std::endl; 
	std::cin >> B[2]; 

	std::vector<double> m (np,0); 
	std::vector<double> q (np,0); 
	for (int i=0; i < np; i++){ 
		std::vector<double> coor1; 
		std::vector<double> vel1; 
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
		if ( m[i] <= 0) throw std::string ("m <= 0"); 
		
		std::cout << "Enter the charge of  the particle (in e charge)" << std::endl; 
		std::cin >> q[i] ; 

		std::cout << "Enter the initial coordinates of  the particle (x, y, z)" << std::endl; 
		std::cin >> coord[i][0] >> coord[i][1] >> coord[i][2] ; 

		std::cout << "Enter the initial velocity of  the particle (Vx, Vy, Vz)" << std::endl; 
		std::cin >> vel[i][0] >> vel[i][1] >> vel[i][2] ; 
	}   
	full( np,coord, vel, B, m, q); 
}




