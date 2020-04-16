#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

vector<int> parseLine(string line);
void printGraph(vector<vector<int>> &graph);

int main(int argc, char **argv)
{
	string line; //used for reading each line of the file
	ifstream inFile;//used to open the file
	int row =0;
	if(argc != 2)//if there are not 2 command line arguments
	{
		cout << "usage: <a.out> <file>" << endl;
	}
	vector<vector<int>> graph;//graph used for this problem
	inFile.open(argv[1]);//opening the second command line argument, which should be the file

	if(!inFile)//if the file is not valid
	{
		cout <<"ERROR: " << argv[1] << " is not a valid file" << endl;
		return -1;
	}

	vector<int> temp;
	while(getline(inFile, line))
	{
		graph.push_back(parseLine(line));
	}

	return 0;
}

vector<int> parseLine(string line)
{
	vector<int> temp;
	for(int i =0; i < line.length(); i++)
	{
		if(line[i] != ',')
		{
			temp.push_back(line[i] - '0'); //converting the character to integer
		}
	}
	return temp;

}

void printGraph(vector<vector<int>> &graph)
{

}
