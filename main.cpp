#include <stdio.h>
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <assert.h>
using namespace std;

#include "BST.h"

int main(int argc , char * argv[])
{
	BST myTree;
	//USED VARIABLES
	bool check;
	string inputfile;
	string outputfile;
	//ARGC CHECK
	if(argc != 3)
	{
		cout<<"Incorrect number of arguments"<<'\n';
		return 0;
	}
	else
	{
	 inputfile = argv[1] ;
	 outputfile = argv[2];
	}

	check = myTree.ParseDocument(inputfile,outputfile);
	if(check == false)
		return 0;
    return 0;
}
