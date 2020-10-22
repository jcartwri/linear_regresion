
#include "pch.h"
#include <iostream>
#include <stdexcept>
#include <numeric>

vector<vector<int>> read_file(void)
{
	string line;
	int mile;
	int pr;
	vector<int> mileage;
	vector<int> price;
	vector<vector<int>> res;

	ifstream file("data.csv");
	if (!file)
		throw runtime_error("...");
	getline(file, line, '\n');
	while (file)
	{
		file >> mile;
		mileage.push_back(mile);
		file.ignore(1);
		file >> pr;
		price.push_back(pr);
		file.ignore(1);
	}	
	res.push_back(mileage);
	res.push_back(price);
	return (res);
}

int ft_work_horse(int flag_v, double lr, int n_iter)
{
	double	std;
	double	mean;
	vector<vector<int>> mas;
	vector<double> X;

	std = 0.0;
	mas = read_file();
	vector<int> &mileage = mas.at(0);
	mean = accumulate(mileage.begin(), mileage.end(), 0) / static_cast<int>(mileage.size());
	for (auto & d : mileage)
		std += 1.0 * (d - mean) * (d - mean);
	std = sqrt(std / (mileage.size() - 1));

	for (int i = 0; i < static_cast<int>(mileage.size()); i++)
		X.push_back(static_cast<double>(((mileage[i]) - mean) / std));

	cout << mean << " ----- " << std << endl << endl;
	for (int i = 0; i < static_cast<int>(mileage.size()); i++)
	{
		cout << X[i] << endl;
	}
	Perceptron per(lr, n_iter);
	per.fit(X, mas[1]);
	cout << flag_v << " ** ** " << lr << " ** ** " << n_iter << endl;
	pair<double, double> p = per.ft_get_theta();
	per.ft_save_model("model.txt", mean, std);
	return (1);
}

int	main(int argc, char **argv)
{
	int		flag_v;
	double	lr;
	int		n_iter;
	
	flag_v = 0;
	lr = 0.15;
	n_iter = 20;
	try
	{
		if (argc != 1)
		{
			for (int i = 1; i < argc; i++)
			{
				if (strcmp(argv[i], "--v") == 0)
					flag_v = 1;
				else if (strcmp(argv[i], "--lr") == 0)
				{
					if (i + 2 > argc)
						throw runtime_error("Error: bed parametr");
					lr = stod(argv[i + 1]);
					i++;
				}
				else if (strcmp(argv[i], "--iter") == 0)
				{
					if (i + 2 > argc)
						throw runtime_error("Error: bed parametr");
					n_iter = stoi(argv[i + 1]);
					if (n_iter <= 0)
						throw runtime_error("Error: bed parametr");
					i++;
				}
			}
		}
		ft_work_horse(flag_v, lr, n_iter);
	}
	catch (runtime_error& ex)
	{
		cout << "Exception happens: " << ex.what() << endl;
	}
	return (0);
}
