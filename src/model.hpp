#include <vector>

using namespace std;

double Teqn(double Ts, double params[]); 
vector<double> CANL(vector<double> params, int N, double w0, double k, double eps);
vector<double> const_Tc(double Ts, double T0, double params[]);
vector<double> summary_stat(vector<double> data, double censored, vector<double> probs);

