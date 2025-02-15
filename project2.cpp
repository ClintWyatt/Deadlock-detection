#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

vector<int> parseLine(string line, vector<int> *avail);
void printGraph(vector<vector<int>> *graph, vector<int> *avail);//method for printing the graph
void allocateResources(vector<vector<int>> *graph, vector<int> *avail);//method for allocating all the resources to the processes
bool graphReduction(vector<vector<int>> *graph, vector<int> *avail, vector<int> *safe);//method to see if the graph is reducible
bool processes = false;
bool resources = false;
bool availableVector = false;
int numProcesses =0, numResources =0;
//vector<int> available;

int main(int argc, char **argv)
{
	vector<int> available;
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
	vector<int> temp;//used for each line in the 2d adjacency matrix
	while(getline(inFile, line))
	{
		if(line[0] != '%' && line.length() >0)//if the beginning of the line contains useful information about the graph
		{
			
			temp = parseLine(line, &available); //use the parseLine function to get information about the graph
			if(processes == true && resources == true && available.size() > 0)//if we are on the matrix section of the graph
			{
				if(temp.size() != 0)//if the temp vector has nothing in it
				{
					graph.push_back(temp);//add the vector of information to the graph (2d vector)
				}
			}
		}
	}
	//printGraph(&graph); //uncomment this to see what the origional available resources are
	allocateResources(&graph, &available);//allocate all resources to the processes
	printGraph(&graph, &available);//print graph method
	vector<int> safeExecution; //vector that will contain the safe execution of processes if the system does not deadlock
	inFile.close();//closing the file
	if(graphReduction(&graph, &available, &safeExecution) == false)
	{
		cout << "Graph reduction failed. Deadlock detected!" << endl;
		return 0;
	}
	cout << "Graph reduction sucessful. System is safe from deadlock!" << endl;
	cout << "Safe process execution: ";
	for(int i =0; i < safeExecution.size(); i++)
	{
		cout << safeExecution[i] +1 << " -> ";
	}
	cout << endl;
	return 0;
}

vector<int> parseLine(string line, vector<int> *avail)
{
	vector<int> temp;//temporary array to represent the row in the adjacency matrix

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
				avail->push_back(line[i] - '0');//putting the number into the vector
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
	
return temp;
}

void printGraph(vector<vector<int>> *graph, vector<int> *avail)
{
	cout << "Available resources after allocation: " << endl;
	for(int i =0; i < avail->size(); i++)
	{
		cout << avail->at(i) << " ";
	}
	cout << endl;
	cout << "Graph:" << endl;
	for(int i = 0; i < graph->size(); i++)
	{
		for(int j = 0; j < graph->at(i).size(); j++)
		{
			cout << graph->at(i)[j] << " ";
		}
		cout << endl;
	}
}

void allocateResources(vector<vector<int>> *graph, vector<int> *avail)
{
	//starting in the bottom left corner of the matrix
	for(int i = numProcesses; i < numProcesses + numResources; i++)
	{
		for(int j =0; j < numProcesses; j++)
		{
			avail->at(i - numProcesses) -= graph->at(i)[j];
		}
	}


}

bool graphReduction(vector<vector<int>> *graph, vector<int> *avail, vector<int> *safe)
{

	int rightQuadrant = numProcesses; //used to check the requests of each process in the right quadrant of the adjency matrix
	int processesLeft = numProcesses; //used to specify the number of processes left in the system
	int success =0;//Success is used for a process that can request resources and leave the system
	bool reduceGraph = false;	
	while(processesLeft >0) //while there are processes in the system
	{
		for(int j =0; j < numProcesses; j++)//starting from process 0 and going to process n
		{

			if(graph->at(j)[j] ==1)//if the process is in the system
			{
				for(int a = rightQuadrant; a < rightQuadrant + numResources; a++)//testing to see if the process at index j in the graph can request all resources
				{
					if(graph->at(j)[a] > avail->at(a - numProcesses))//if the request cannot be done (not enough resources)
					{
						success = -1;//setting success to -1.  
						break;//exit the loop. request cannot be granted. not enough resources are available
					}
				}
				if(success ==0)//if the process was able to request resources
				{
					processesLeft--;//process can now leave the system
					graph->at(j)[j] = 0;//process is now out of the system
					safe->push_back(j);//adding the process to the safe execution vector
					
					for(int b = numProcesses, c = 0; b < numProcesses + numResources; b++, c++)//adding process j's allocation back to the system
					{
							avail->at(c) += graph->at(b)[j];
					}
					reduceGraph = true; //process is leaving the system
				}
			}
			success = 0; //resetting the succcess varaible 
		}

		if(reduceGraph == false)//if ethe graph cannot be reduced 
		{
			return false;
		}
		reduceGraph = false;//resetting teh reduceGraph variable to false to test for the next reduction sequence
	}
	return true;
}
