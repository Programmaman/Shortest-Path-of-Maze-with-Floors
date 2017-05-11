#include <iostream>
#include <cmath>
#include <climits>
#include <string>
#include <fstream>
using namespace std;



int GetValue(int ** values, int * arr, int a, int b)
{
	if (values[a][b] != 0)
		return values[a][b];

	int value = 0;
	for (int i = a; i <= b; i++)
	{
		value = value + arr[i];
	}

	values[a][b] = value;
	return value;
}

int GetInequality(int ** values, int * arr, int t, int a, int b)
{
	return (int)pow((t - GetValue(values, arr, a, b)), 2);
}

void Reconstruct(int * splits, int n, int a, string &stg, int & splitcount)
{
	splitcount++;
	stg += to_string(splits[a] - a + 1) + " ";
	if (splits[a] == n - 1)
		return;
	Reconstruct(splits, n, splits[a] + 1,stg,splitcount);
}

int Algorithm(int * arr, const int n, const int t, ofstream &outputfile)
{
	int *inequalities, *splits, **values;
	inequalities = new int[n]();
	splits = new int[n]();
	
	values = new int*[n];
	for (int i = 0; i < n; i++)
		values[i] = new int[n]();

	for (int i = n-1; i >= 0; i--)
	{
		if (i == n-1)
		{
			inequalities[i] = GetInequality(values, arr, t, i, i);
			splits[i] = n-1;
		}
		else
		{
			int min = INT_MAX;
			int split = n-1;

			//when j = n-1 this means dont split at all actually
			for (int j = i; j <= n-1; j++)
			{
				if (GetValue(values, arr, i, j) > t)
					break;
				int inequality = GetInequality(values, arr, t, i, j) + (j < n-1 ? inequalities[j + 1] : 0); //0 = no split
				if (inequality < min)
				{
					min = inequality;
					split = j;
				}
			}
			inequalities[i] = min;
			splits[i] = split;
		}
	}
	


	string stg;
	int splitcount = 0;




	Reconstruct(splits, n, 0, stg,splitcount);
	outputfile << splitcount << " " << stg << endl;
	

	return 0;
}







int main()
{
	cout << "Running algorithm" << endl;
	int p;
	int n;
	int limit;

	ifstream infilename;
	ofstream outfilename;
	infilename.open("input.txt");
	outfilename.open("output.txt");
	if (!infilename.is_open())
	{
		cout << "File not found.";
		return 0;
	}
	infilename >> p;
	for (int i = 1; i <= p; i++)
	{
		infilename >> n;
		infilename >> limit;
		int *arr;
		arr = new int[n];
		for (int j = 0; j < n; j++)
		{
			infilename >> arr[j];
		}
		Algorithm(arr, n, limit,outfilename);
	}
	cout << "'output.txt' file created." << endl;
	cin.get();
}