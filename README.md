# abc-adm
Estimation for accumulated damage models via approximate Bayesian computation

# Installation 

## Download and compile the code:
```
git clone https://github.com/wongswk/abc-adm.git
cd abc-adm/src
make all
```

# Usage

## DOLmod_MCMC

DOLmod_MCMC **number_of_samples** **burning** **thining** **delta** **data**

- The data file name should be "something_**tau_c**_**t_c(in years)**.csv", e.g., constLoad_4500_1Y.csv.
- Output files: theta.csv containing _m_ theta vectors and accept.csv containing the acceptance rate.

## generate

generate **file_of_parameters** **output_filename** **number_of_samples** **tau_c** **t_c(in hours)**

- Output file: A csv file contain generated samples from the parameters; each column contains samples form one parameter

## CanADM

CanADM **theta_file_name** **phi** 

- This program will give the estimated probability of failure after 30 years based on a large
	number of replications with given load profile. It will read, from user, the parameter vectors
	thetas. The thetas will then be used to solve the Canadian ADM for time-to-failure T_f and
	probability of failure P_f. Tf and Pf per theta will be written into files with suffix “csv”.
	The output file names depend on phi. Set value of phi and number of thetas will be printed
	along with the simulation steps.
- Output file: probability of failure with and without DOL


# Examples
```
cd ../example
# simulate data using parameters in true_theta.csv 
# with constant load 4500 psi and test of duration 1Y (8760 hours)
../generate true_theta.csv simuConstLoad_4500_1Y.csv 300 4500 8760
# run the abc-mcmc algorithm to obtain 500 posterior samples
../DOLmod_MCMC 100 100 10 0.3 simuConstLoad_4500_1Y.csv
# simulate the time-to-failures given theta under the residential loads
../CanADM theta_0.3_csv 1  

```


## Details

There are some additional parameters in CanADM (solveCanODE.cpp) that can be modified:
- mu:        constant with units ‘time’ to ensure dimensional consistency.
- k:         standard ramp-loading rate.
- T0:        with Tc = 4500psi, T0 = Tc/k
- n_per_theta:    number of replications for each draw of theta. (could be modified for better approximation)
- t_start:    0 as start of time.
- t_end:        hours in 30 years.(should be modified based on return period)
- dt:        step of time. (could be modified for better approximation) 

The current load profile in CanADM is the residential load profile. Other load profiles can be added by creating a new class.
