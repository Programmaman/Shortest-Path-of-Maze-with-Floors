#include <cstdio>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <list>
#include <utility>
#include <queue>
#include <deque>

using namespace std;

//Tile Structure
typedef struct  {
	int TileID;
	bool visited;
	vector <int> NeighborsID;
}Tile;

//Output Overload for testing
ostream& operator << (ostream &os, const Tile& t)
{
	os << t.TileID << ' ' << boolalpha << t.visited << "Edge IDs:";
	for ( int l = 0; l < t.NeighborsID.size(); l++)
	{
		os << t.NeighborsID.at(l) << ' ';
	}
	os << endl;
		return os;
}

//Write Path function
void writePath(vector<Tile> patharray, const int rootid, const int goalid, const int numofcolumns, const int numofrows, ofstream &outputfile)
{
	vector <char> output;
	for (int i = patharray.size()-1; i >= 0;)
	{
		
		bool neighborfound = false;
		Tile tempnode = patharray.at(i);
		int gotoidx = i;
		for (int j = 0; j < tempnode.NeighborsID.size(); j++)
		{
			for (int k = i; k >= 0; k--)
			{
				if (tempnode.NeighborsID[j] == patharray[k].TileID)
				{
					gotoidx = k;
					neighborfound = true;

					// Print direction of next node
					if (patharray[k].TileID == tempnode.TileID + 1)
					{
						//outputfile << "W ";
						output.push_back('W');
					}
					else if (patharray[k].TileID == tempnode.TileID - 1)
					{
						//outputfile << "E ";
						output.push_back('E');
					}
					else if (patharray[k].TileID == tempnode.TileID - numofcolumns)
					{
						//outputfile << "S ";
						output.push_back('S');
					}
					else if (patharray[k].TileID == tempnode.TileID + numofrows)
					{
						//outputfile << "N ";
						output.push_back('N');
					}
					else if (patharray[k].TileID == tempnode.TileID + numofrows * numofcolumns)
					{
						//outputfile << "D ";
						output.push_back('D');
					}
					else if (patharray[k].TileID == tempnode.TileID - numofrows * numofcolumns)
					{
						//outputfile << "U ";
						output.push_back('U');
					}
				}

			}
		}
		if (neighborfound == true)
		{
			i = gotoidx;
		}
		else
		{
			i--;
		}

	}
	for (int iterate = output.size()-1; iterate >=0; iterate --)
	{
		outputfile << output[iterate];
		outputfile << ' ';
		if (iterate == 0)
		{
			break;
		}
	}

	outputfile << endl << endl;
}

//BFS 
void BFS(vector<Tile> tiles, vector<Tile> &patharray, const int rootid, const int goalid)
{
	Tile tempnode;
	tiles[rootid].visited = true;
	queue <Tile> queueoftiles;
	queueoftiles.push(tiles[rootid]);

	while (queueoftiles.size() != 0)
	{
		tempnode = queueoftiles.front();
		queueoftiles.pop();
		bool flag = false;

		for ( int second_iterator = 0; second_iterator < tempnode.NeighborsID.size(); second_iterator++)
		{
			if (tiles[tempnode.NeighborsID[second_iterator]].visited != true)
			{
				patharray.push_back(tiles[tempnode.TileID]);
				break;
			}
			
		}
		


		for ( int iterator = 0; iterator < tempnode.NeighborsID.size(); iterator++)
		{
			if (tiles[tempnode.NeighborsID[iterator]].visited == true)
			{
				;
			}
			else
			{

				tiles[tempnode.NeighborsID[iterator]].visited = true;
				queueoftiles.push(tiles[tempnode.NeighborsID[iterator]]);
			}

		}
		
	}
	patharray.push_back(tiles[goalid]);
}

//Main
int main()
{
	int floornum;
	int rownum;
	int columnnum;
	int numMazes;

	cout << "Running Algorithm" << endl;
	
	//Read File
	ifstream infile("input.txt");
	ofstream outfile("output.txt");
	if (!infile.is_open())
	{
		cout << "Error opening input file." << endl;
		return 0;
	}
	else if (!outfile.is_open())
	{
		cout << "Error opening output file." << endl;
		return 0;
	}
	infile >> numMazes;
	for (int i = 1; i <= numMazes; i++)
	{

		int numTiles;
		int numoffloors, numofrows, numofcolumns;
		int rootID;
		int goalID;

		infile >> numoffloors;
		infile >> numofrows;
		infile >> numofcolumns;
		numTiles = numoffloors * numofrows * numofcolumns;
		vector <Tile> arrayoftiles(numTiles);
		vector <Tile> arrayofpaths;
		infile >> floornum;
		infile >> rownum;
		infile >> columnnum;

		rootID = (floornum* numofrows * numofcolumns) + (rownum * numofcolumns) + columnnum;

		infile >> floornum;
		infile >> rownum;
		infile >> columnnum;



		goalID = (floornum* numofrows * numofcolumns) + (rownum * numofcolumns) + columnnum;
		
		// Assign neighbors to Tiles
		for (int j = 0; j < numTiles; j++)
		{
			string availablepaths;


			arrayoftiles[j].TileID = j;
			arrayoftiles[j].visited = false;

			infile >> availablepaths;

			if (availablepaths[0] == '0')
			{
				;
			}
			else if (availablepaths[0] == '1')
			{
				arrayoftiles[j].NeighborsID.push_back(j - numofcolumns);
			}
			if (availablepaths[1] == '0')
			{
				;
			}
			else if (availablepaths[1] == '1')
			{
				arrayoftiles[j].NeighborsID.push_back(j + 1);
			}
			if (availablepaths[2] == '0')
			{
				;
			}
			else if (availablepaths[2] == '1')
			{
				arrayoftiles[j].NeighborsID.push_back(j + numofcolumns);
			}
			if (availablepaths[3] == '0')
			{
				;
			}
			else if (availablepaths[3] == '1')
			{
				arrayoftiles[j].NeighborsID.push_back(j - 1);
			}
			if (availablepaths[4] == '0')
			{
				;
			}
			else if (availablepaths[4] == '1')
			{
				arrayoftiles[j].NeighborsID.push_back(j + numofrows*numofcolumns);
			}
			if (availablepaths[5] == '0')
			{
				;
			}
			else if (availablepaths[5] == '1')
			{
				arrayoftiles[j].NeighborsID.push_back(j - numofrows*numofcolumns);
			}
			
		}
		BFS(arrayoftiles, arrayofpaths, rootID, goalID);
		writePath(arrayofpaths, rootID, goalID, numofcolumns, numofrows, outfile);
		


	}
	cout << "'output.txt' file created." << endl;
	cout << "Please exit this window. And open the Outputfile.";
	cin.get();
	return 0;
	}
	
