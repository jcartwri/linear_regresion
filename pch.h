// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H
#include <fstream>
#include <string>
#include <vector>
#include <utility>
#include <stdexcept>
//#include <stralign.h>
#include <cstring>
#include <cstdlib>

using namespace std;

class Perceptron
{
public:
	Perceptron(double lr, int col_iter)
	{
		learn_rate = lr;
		theta0 = 0.0;
		theta1 = 0.0;
		n_iter = col_iter;
	}

	void fit(vector<double>& x, vector<int>& y)
	{
		double tmp0;
		double tmp1;

		for (int i = 0; i < n_iter; i++)
		{
			tmp0 = 0.0;
			tmp1 = 0.0;
			for (int j = 0; j < static_cast<int>(x.size()); j++)
			{
				tmp0 += predict(x.at(j)) - y.at(j);
				tmp1 += (predict(x.at(j)) - y.at(j)) * x.at(j);
			}
			theta0 -= learn_rate * tmp0 / (static_cast<int>(y.size()));
			theta1 -= learn_rate * tmp1 / (static_cast<int>(y.size()));
		}
	}

	void set_theta(int theta_0 = 0, int theta_1 = 0)
	{
		theta0 = theta_0;
		theta1 = theta_1;
	}

	pair<double, double> ft_get_theta(void)
	{
		return make_pair(theta0, theta1);
	}

	void	ft_save_model(string file_name, double mean, double std)
	{
		ofstream	file;

		file.open(file_name);
		if (!file)
			throw runtime_error("Cann't open the file");
		file << theta0 << endl << theta1 << endl << mean << endl << std << endl;
	}

	double	predict(double x)
	{
		return (theta0 + theta1 * x);
	}

private:
	double	learn_rate;
	double	theta0;
	double	theta1;
	int		n_iter;
};

#endif //PCH_H
