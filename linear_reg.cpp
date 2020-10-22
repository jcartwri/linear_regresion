#include "pch.h"
#include <iostream>

void ft_out_put(int flag_x, int flag_file, string path, double x)
{
	vector<double> km;
	string		line;
	double		elem;
	double		theta0;
	double		theta1;
	double		std;
	double		mean;

	ifstream file_model;
	file_model.open("model.txt");
	file_model >> theta0;
	file_model.ignore(1);
	file_model >> theta1;
	file_model.ignore(1);
	file_model >> mean;
	file_model.ignore(1);
	file_model >> std;

	ofstream out_file;
	out_file.open("out_put.csv");

	Perceptron	per(0.15, 20);
	per.set_theta(theta0, theta1);

	if (!file_model)
		throw runtime_error("cann't find file: model.txt");

	if (flag_file)
	{
		ifstream file;
		file.open(path);
		if (!file)
			throw runtime_error("cann't open file!");
		getline(file, line, '\n');
		while (file)
		{
			file >> elem;
			file.ignore(1);
			km.push_back(elem);
		}

		out_file << "mileage;mileage_norm;price_predict" << endl;

		for (int i = 0; i < static_cast<int>(km.size()); i++)
		{
			out_file << km[i] << ";" << (km[i] - mean) / std << ";" << per.predict((km.at(i) - mean) / std) << endl;
		}
	}
	else if (flag_x)
	{
		out_file << "mileage;mileage_norm;price_predict" << endl;
		out_file << x << ";" << (x - mean) / std << ";" << per.predict((x - mean) / std) << endl;
	}
}

int main(int argc, char **argv)
{
	double	x;
	string	file;
	int		flag_path;
	int		flag_x;

	x = 0.0;
	file = "";
	flag_x = 0;
	flag_path = 0;
	if (argc == 1)
	{
		cout << "Error: No argument" << endl;
		return (-1);
	}
	try
	{
		for (int i = 1; i < argc; i++)
		{
			if (strcmp(argv[i], "--file") == 0)
			{
				if (i + 2 > argc)
					throw runtime_error("Error: bed parametr");
				flag_path = 1;
				file = argv[i + 1];
				i++;
			}
			else if (strcmp("--x", argv[i]) == 0)
			{
				if (i + 2 > argc)
					throw runtime_error("Error: bed parametr");
				flag_x = 1;
				x = stod(argv[i + 1]);
				i++;
			}
		}
		cout << flag_x << " -- " << flag_path << " -- " << file << " -- " << x << endl;
		if (!flag_x && !flag_path)
			throw runtime_error("cann't argument");
		ft_out_put(flag_x, flag_path, file, x);
	}
	catch (runtime_error& ex)
	{
		cout << "Error happens: " << ex.what() << endl;
	}
	return (0);
}