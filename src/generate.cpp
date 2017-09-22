#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <ctime>
#include <random>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <vector>
#include "model.hpp"
#include "utils.hpp"


using namespace std;


// global variables
const int n_par = 10; // number of parameters
const int n_s = 11; // number of summary statistics; 5 quantiles for each part (in log scale) and number of censored data
const vector<double> probs = {0.1, 0.25, 0.5, 0.75, 0.9}; // quantiles
const int n_q = probs.size();
const double delta = 17;

// set up random number generators
mt19937 generator(time(0));

int main ( int argc, char* argv[] )

{  
	// read parameters from file and simulated using the parameters
	// output format: simulation using one parameter is store in one column

	if(argc != 6){
		cout << "Invalid input filename, output filename, number of samples, w0, and censored period" << endl;
		return 0;
	}

	const int N = atoi(argv[3]); //number of samples
	const double w0 = atof(argv[4]);
	const double k = 388440;
	const double T0 = w0/k;
	const double censored = atof(argv[5]);

	
	cout << "Read parameters from " << argv[1] << "!" << endl;
	ifstream fin(argv[1]);
	if(fin.is_open()){
		vector< vector<double> > paras = readCSV_to_vec(fin);
		int n = paras.size();
		cout << "Finish reading " << n << " parameters!"<< endl;
		cout << "Start generating data from the parameters!" << endl;
		vector< vector<double> > t(n, vector<double>(N));
		vector<double> tmp(N);
		for(int i = 0; i < n; ++i){
			tmp = CANL(paras[i], N, w0, k, 0.5);
			t[i] = tmp;
		}	

		cout << "Write out simulation result to " << argv[2] << endl;

		ofstream fout(argv[2]);
  
		if(fout.is_open()){
			for(int i = 0; i < N; ++i){
				for(int j = 0; j < n-1; ++j){
					fout << t[j][i] << ",";
				}
				fout << t[n-1][i] << endl;
			}
		}
		else{
			cout << "File is not open!" << endl;
		}
	
	}
	else{
		cout << "File does not exist!" << endl;
	}
	

	return 0;
}

