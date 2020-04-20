#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

vector<int> parseLine(string line);
<<<<<<< HEAD
void printGraph(vector<vector<int>> *graph);

=======
void printGraph(vector<vector<int>> &graph);
bool processes = false;
bool resources = false;
bool availableVector = false;
int numProcesses =0, numResources =0;
vector<int> available;
>>>>>>> other
int main(int argc, char **argv)
{
	string line; //used for reading each line of the file
	ifstream inFile;//used to open the file
	int row =0;
	if(argc != 2)//if there are not 2 command line arguments
	{
		cout << "usage: <a.out> <file>" << endl;
		return 0; //end program
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
		if(line[0] != '%' && line.length() >0)//if the beginning of the line contains useful information about the graph
		{
			
			temp = parseLine(line); //use the parseLine function to get information about the graph
			if(processes == true && resources == true && available.size() > 0)//if we are on the matrix section of the graph
			{
				if(temp.size() != 0)//if the temp vector has nothing in it
				{
					graph.push_back(temp);//add the vector of information to the graph (2d vector)
				}
			}
		}
	}
<<<<<<< HEAD

	printGraph(&graph);

=======
	printGraph(graph);
	inFile.close();//closing the file
>>>>>>> other
	return 0;
}

vector<int> parseLine(string line)
{
	vector<int> temp;

	if(processes == false)//if we are on the number of processes section of the text file
	{
		processes = true;
		numProcesses = line[line.length() -1] - '0';//getting the number of processes in the system
	}
	else if(resources == false)//if we are on the number of resources section of the text file
	{
		resources = true;
		numResources = line[line.length() -1] - '0';//getting the number of resources in the system
	}
	else if(availableVector == false)//if we are on the vector of available resources section of the text file
	{
		availableVector = true;
		for(int i =0; i < line.length(); i++)
		{
			if(line[i] != ',')
			{
				available.push_back(line[i] - '0');//putting the number into the vector
			}
		}
	}
	else//case we are in the adjacancy matrix section of the text file
	{
		for(int i =0; i < line.length(); i++)
		{
			if(line[i] != ',')
			{
				temp.push_back(line[i] - '0'); //converting the character to integer
			}
		}
	}
	/*
	for(int i =0; i < temp.size(); i++)
	{
		cout << temp[i] << " ";
	}
	cout << endl;
	*/
return temp;
}

void printGraph(vector<vector<int>> *graph)
{
<<<<<<< HEAD
	cout << "Graph:" << endl;
	for(int i = 0; i < graph->size(); i++)
	{
		for(int j = 0; j < graph->at(i).size(); j++)
		{
			cout << graph->at(i)[j] << " ";
=======
	cout << "resulting graph " << endl;
	for(int i =0; i < graph.size(); i++)
	{
		for(int j =0; j < graph[i].size(); j++)
		{
			cout <<graph[i][j] << " ";
>>>>>>> other
		}
		cout << endl;
	}
}
