#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include <assert.h>
#include "BST.h"

using namespace std;

ofstream myfile;
ifstream myfile2;


bool modify = false;
BST::BST()
{
	Root = NULL;
	temp = Root;
}

void BST::insert(std::string const & title, const int & day, const int & time )
{
	if(Root == NULL)
	{
	
		Tree node = new Node;
		assert(node != NULL);
		Root = node;
		temp = Root;
		node->Day = day;
		node->Time = time;
		node->Title = title;
		node->Left = NULL;
		node->Right = NULL;
		
	}
	
	else if(temp->Day > day )
	{ 
		if(temp->Left == NULL)
		{
			Tree node = new Node;
			assert(node != NULL);
			temp->Left = node;
			node->Day = day;
			node->Time = time;
			node->Title = title;
			node->Left = NULL;
			node->Right = NULL;
			temp = Root;
		}
		else
		{
			temp = temp->Left;
			insert(title,day,time);
		}
			
	}
	else if(temp->Day < day )
	{ 
		if(temp->Right == NULL)
		{
			Tree node = new Node;
			assert(node != NULL);
			node->Day = day;
			node->Time = time;
			node->Title = title;
			node->Left = NULL;
			node->Right = NULL;
			temp->Right = node;
			temp = Root;
		}
		else
		{
		temp = temp->Right;
		insert(title,day,time);
		}
			
	}	
	else if(temp->Day == day)
	{
		if(temp->Time > time )
		{ 
			if(temp->Left == NULL)
			{
				Tree node = new Node;
				assert(node != NULL);
				temp->Left = node;
				node->Day = day;
				node->Time = time;
				node->Title = title;
				node->Left = NULL;
				node->Right = NULL;
				temp = Root;
			}
			else
			{
				temp = temp->Left;
				insert(title,day,time);
			}
				
		}
		else if(temp->Time < time )
		{ 
			if(temp->Right == NULL)
			{
				Tree node = new Node;
				assert(node != NULL);
				node->Day = day;
				node->Time = time;
				node->Title = title;
				node->Left = NULL;
				node->Right = NULL;
				temp->Right = node;
				temp = Root;
			}
			else
			{
			temp = temp->Right;
			insert(title,day,time);
			}
				
		}
		else if(temp->Time == time)
		{	
			cout<<"Conflict "<<temp->Day<<" "<<temp->Time<<'\n';
			myfile<<"Conflict "<<temp->Day<<" "<<temp->Time<<'\n';
			temp = Root;
		}
		else{}
	}
	else{}
		
}
	
void BST::retrieve(std::string const & title, const int & day,const int & time )
{

	
	if(Root == NULL)
	{
		cout<<"Empty "<<day<<" "<<time<<'\n';
		myfile<<"Empty "<<day<<" "<<time<<'\n';
	}
	else
	{
		static Tree temp2 = Root;
		if(temp2->Day == day && temp2->Time == time )
		{	

			if(modify)
			{
				temp2->Title = title;
				modify = false;
				temp2 = Root;
			}
			else
			{
				cout<<temp2->Title<<'\n';
				myfile<<temp2->Title<<'\n';
				temp2 = Root;
			}
				
		}
		else if(temp2->Day > day)
		{
			if(temp2->Left == NULL)
			{
				cout<<"Empty "<<day<<" "<<time<<'\n';
				myfile<<"Empty "<<day<<" "<<time<<'\n';
				temp2 = Root;
			}
			else
			{
			temp2 = temp2->Left;
			retrieve(title,day,time);
			}
		}
		else if(temp2->Day < day)
		{
			if(temp2->Right == NULL)
			{
				cout<<"Empty "<<day<<" "<<time<<'\n';
				myfile<<"Empty "<<day<<" "<<time<<'\n';
				temp2 = Root;
			}
			else
			{
			temp2 = temp2->Right;
			retrieve(title,day,time);
			}
		}
		else if(temp2->Day == day)
		{
			if(temp2->Day == day && temp2->Time == time )
			{	

				if(modify)
				{
					temp2->Title = title;
					modify = false;
					temp2 = Root;
				}
				else
				{
					cout<<temp2->Title<<'\n';
					myfile<<temp2->Title<<'\n';
					temp2 = Root;
				}
			}
			else if(temp2->Time > time)
			{
				if(temp2->Left == NULL)
				{
				cout<<"Empty "<<day<<" "<<time<<'\n';
				myfile<<"Empty "<<day<<" "<<time<<'\n';
				temp2 = Root;
				}
				else
				{
				temp2 = temp2->Left;
				retrieve(title,day,time);
				}
			}
			else if(temp2->Time < time)
			{
				if(temp2->Right == NULL)
				{
				cout<<"Empty "<<day<<" "<<time<<'\n';
				myfile<<"Empty "<<day<<" "<<time<<'\n';
				temp2 = Root;
				}
				else
				{
				temp2 = temp2->Right;
				retrieve(title,day,time);
				}
			}
				
			

		}
	
	}

}
void BST::in_ord_traversal()
{
	if(Root != NULL)
	in_ord_traversal_private(Root);
	else
	{
		cout<<"Empty Planner"<<'\n';
		myfile<<"Empty Planner"<<'\n';
	}
}

void BST::in_ord_traversal_private(Tree ptr)
{
	
	if(ptr != NULL)
	{
		
		in_ord_traversal_private(ptr->Left);
		cout<<ptr->Title<<" ";
		cout<<ptr->Day<<" ";
		cout<<ptr->Time<<'\n';
		myfile<<ptr->Title<<" ";
		myfile<<ptr->Day<<" ";
		myfile<<ptr->Time<<'\n';
		in_ord_traversal_private(ptr->Right);
	}

}


int NoOfLines = 0;
int LineNoOfChars = 0;
int TotalNoOfChars = 0;
int initialWordChar = -1;
int NumOfWords = 0;
string checkEmpty;

bool BST::ParseDocument(std::string file_name,std::string file_name2)
{
	//output file
	myfile.open (file_name2);
	//input file
	string line;
	string cmd;
	int lastChar;
	string title;
	myfile2.open (file_name);
	int qpos = 0;
	int nspace = 0;
	if (myfile2.is_open())
	{
		string words[50];
		
		while ( getline (myfile2,line) ) 
		{ 
			//cout<<"1"<<'\n';
			NoOfLines ++ ;
			initialWordChar = 0;			
			LineNoOfChars = line.length();
			TotalNoOfChars += LineNoOfChars ; 
			NumOfWords = 0;
			if(line[LineNoOfChars-1] == '\r')
			{
				//cout<<"entered linux check"<<'\n';
				line[LineNoOfChars-1] = '\0';
				LineNoOfChars--;
			}
			//cout<<"line length in windows is:"<<LineNoOfChars<<'\n';
			for(int currentChar = 0; currentChar < LineNoOfChars ; currentChar++)
			{ 
				//cout<<"char is: "<<line[currentChar]<<'\n';
				if( line[currentChar] == ' ' || line[currentChar+1] == '\0'||line[currentChar] == '\t' )
				{
					if(line[initialWordChar] == '\"')
					{
						for(int qcheck = 2 ; qcheck < LineNoOfChars - initialWordChar ; qcheck++)
						{	
							if(line[initialWordChar + qcheck] == '\"' && (line[initialWordChar + qcheck +1] == ' '||line[initialWordChar + qcheck +1] == '\t'))
							{
								qpos = qcheck;
								currentChar =initialWordChar + qpos + 1;
							}
						}
						
							
					}
					if(line[currentChar+1] == '\0')
					{
						if(line[currentChar] == ' '||line[currentChar] == '\t')
						words[NumOfWords] = line.substr(initialWordChar ,currentChar-initialWordChar);
						else
						words[NumOfWords] = line.substr(initialWordChar ,currentChar-initialWordChar+1);
					}
					else
					{
					checkEmpty = line.substr(initialWordChar ,currentChar-initialWordChar);
					if( checkEmpty.length() != 0 )
					{
						words[NumOfWords] = checkEmpty;
					}
					else
					{
					NumOfWords--;
					}
					
					}
					
					while(line[currentChar+1] == ' ' ||line[currentChar+1] == '\t'  )
					{
						currentChar++;
					}
					initialWordChar = currentChar + 1;
					NumOfWords++;
				}

				
			}
			if(LineNoOfChars != 0)
			program(words,NumOfWords);
		}
			
	}
	else 
	{
		cout << "File not found"; 
		myfile<< "File not found"; 
		return false;
	}	
}	

bool bad = false;
void BST::program(std::string words[], int numofwords)
{
	bad = false;
	if(words[0] == "ADD")
	{
		
		if(numofwords == 4)
		{
		
			if(words[1][0] != '\"' || words[1][words[1].length()-1] != '\"' )
			{
				cout<<"Invalid title"<<'\n';
				myfile<<"Invalid title"<<'\n';
				
				bad = true;
			}
			if(checkStoi(words[2]))
			{
				if(stoi(words[2]) < 1 || stoi(words[2])> 365  )
				{
					cout<<"Invalid day"<<'\n';
					myfile<<"Invalid day"<<'\n';
					bad = true;
				}

			}		
			else
			{
				cout<<"Invalid day"<<'\n';
				myfile<<"Invalid day"<<'\n';
				bad = true;
			}		
			if(checkStoi(words[3]))
			{
				if(stoi(words[3]) < 0 || stoi(words[3])> 23  )
				{
					cout<<"Invalid hour"<<'\n';
					myfile<<"Invalid hour"<<'\n';
					bad = true;	
				}

			}
			else
			{
				cout<<"Invalid hour"<<'\n';
				myfile<<"Invalid hour"<<'\n';
				bad = true;
			}			
			
			if(!bad)
			{
				//insert
				temp = Root;
				insert(words[1],stoi(words[2]),stoi(words[3]));
			}
			
		}
		else
		{
			cout<<"Invalid arguments"<<'\n';
			myfile<<"Invalid arguments"<<'\n';
		}
		
	}
	
	else if(words[0] == "Find")
	{
		
		if(numofwords == 3)
		{
			if(checkStoi(words[1]))
			{
				if(stoi(words[1]) < 1 || stoi(words[1])> 365  )
				{
					cout<<"Invalid day"<<'\n';
					myfile<<"Invalid day"<<'\n';
					bad = true;
				}

			}		
			else
			{
				cout<<"Invalid day"<<'\n';
				myfile<<"Invalid day"<<'\n';
				bad = true;
			}		
			if(checkStoi(words[2]))
			{
				if(stoi(words[2]) < 0 || stoi(words[2])> 23  )
				{
					cout<<"Invalid hour"<<'\n';
					myfile<<"Invalid hour"<<'\n';
					bad = true;	
				}

			}
			else
			{
				cout<<"Invalid hour"<<'\n';
				myfile<<"Invalid hour"<<'\n';
				bad = true;
			}	
			if(!bad)
			{
				modify = false;
				retrieve(words[0],stoi(words[1]),stoi(words[2]));
			}
		}
		else
		{
			cout<<"Invalid arguments"<<'\n';
			myfile<<"Invalid arguments"<<'\n';
		}		
	}
	
	else if(words[0] == "MOD")
	{
		
			if(numofwords == 4)
			{
				if(words[1][0] != '\"' || words[1][words[1].length()-1] != '\"' )
				{
					cout<<"Invalid title"<<'\n';	
					myfile<<"Invalid title"<<'\n';	
					bad = true;
				}
				if(checkStoi(words[2]))
				{
					if(stoi(words[2]) < 1 || stoi(words[2])> 365  )
					{
						cout<<"Invalid day"<<'\n';
						myfile<<"Invalid day"<<'\n';
						bad = true;
					}

				}		
				else
				{
					cout<<"Invalid day"<<'\n';
					myfile<<"Invalid day"<<'\n';
					bad = true;
				}		
				if(checkStoi(words[3]))
				{
					if(stoi(words[3]) < 0 || stoi(words[3])> 23  )
					{
						cout<<"Invalid hour"<<'\n';
						myfile<<"Invalid hour"<<'\n';
						bad = true;	
					}

				}
				else
				{
					cout<<"Invalid hour"<<'\n';
					myfile<<"Invalid hour"<<'\n';
					bad = true;
				}			
				
				if(!bad)
				{
					//insert
				
					modify = true;
					retrieve(words[1],stoi(words[2]),stoi(words[3]));
				}
			}
		
		else
		{
			cout<<"Invalid arguments"<<'\n';
			myfile<<"Invalid arguments"<<'\n';
		}
		
		
	}
	
	else if(words[0] == "Print")
	{
		if(numofwords == 1)
		{
			in_ord_traversal();
		}
		else
		{
			cout<<"Invalid arguments"<<'\n';
			myfile<<"Invalid arguments"<<'\n';
		}
		
	}
	else if(words[0] == "DEL")
	{
		if(numofwords == 3)
		{
				if(checkStoi(words[1]))
				{
					if(stoi(words[1]) < 1 || stoi(words[1])> 365  )
					{
						cout<<"Invalid day"<<'\n';
						myfile<<"Invalid day"<<'\n';
						bad = true;
					}

				}		
				else
				{
					cout<<"Invalid day"<<'\n';
					myfile<<"Invalid day"<<'\n';
					bad = true;
				}		
				if(checkStoi(words[2]))
				{
					if(stoi(words[2]) < 0 || stoi(words[2])> 23  )
					{
						cout<<"Invalid hour"<<'\n';
						myfile<<"Invalid hour"<<'\n';
						bad = true;	
					}

				}
				else
				{
					cout<<"Invalid hour"<<'\n';
					myfile<<"Invalid hour"<<'\n';
					bad = true;
				}			
				
				if(!bad)
				{
					modify = true;
					deleteNode(stoi(words[1]), stoi(words[2]));
				}
	
		}
		else
		{
			cout<<"Invalid arguments"<<'\n';
			myfile<<"Invalid arguments"<<'\n';
		}
		
	}
	else
	{
		cout<<"Invalid command"<<'\n';
		myfile<<"Invalid command"<<'\n';
	}

}

bool BST::checkStoi(std::string x)
{
	for(int h = 0 ; h < x.length()  ; h++)
	{		
		if(x[h] < 48 || x[h] >57)
			return false;
	}

		return true;
}

void BST::deleteNode(const int & day, const int & hour)
{
	Tree ptr = Root;
	Tree ptr_prev = ptr;
	Tree ptr_bu = Root;
	Tree parent = Root;
	if(ptr != NULL)
	{
	while(  !((ptr->Day == day)  && (ptr->Time == hour)) )
	{
		if(ptr->Day > day)
		{
		ptr_prev = ptr;
		ptr = ptr -> Left;	
		}
		else if(ptr->Day < day)
		{
		
		ptr_prev = ptr;
		ptr = ptr -> Right;	
		
			
		}
		else if(ptr->Day == day)
		{
			if(ptr->Time > hour)
			{
			ptr_prev = ptr;
			ptr = ptr -> Left;	
			}
			else if(ptr->Time < hour)
			{
			ptr_prev = ptr;
			ptr = ptr -> Right;		
			}
		}
		if( ptr == NULL )
			break;
	
	}	
	bool left ;
	
	if(ptr_prev->Left == ptr)
		left = true;
	else 
		left = false;

	if(ptr == NULL)
	{
		cout<<"Empty "<<day<<" "<<hour<<'\n';
		myfile<<"Empty "<<day<<" "<<hour<<'\n';
	}
	else if(ptr->Left ==  NULL)
	{
		if(ptr->Right == NULL)
		{
			if(ptr == Root)
			{
				Root = NULL;
			}
			else
			{				
				if(left)
				ptr_prev->Left = NULL;
				else
				ptr_prev->Right = NULL;
			}
			
		}
		else
		{
			if(ptr == Root)
			{
			 Root = ptr->Right;
			}
			else
			{
				if(left)
				ptr_prev->Left = ptr->Right;
				else
				ptr_prev->Right = ptr->Right;
			}
		}
		
	}
	else if(ptr->Right == NULL)
	{
		if(ptr == Root)
		{
			 Root = ptr->Left;
		}
		else
		{	
			if(left)
				ptr_prev->Left = ptr->Left;
			else
				ptr_prev->Right = ptr->Left;
		}
	}
	else if(ptr->Right != NULL && ptr->Left != NULL)
	{
		parent = ptr->Right;
		ptr_bu = parent;
		if(left)
			ptr_prev->Left =  parent;
		else
			ptr_prev->Right = parent;
			
		while(parent != NULL)
		{
			
			ptr_bu = parent;
			parent = parent->Left;
		}
		ptr_bu->Left = ptr->Left;

		if(ptr == Root)
		Root = ptr->Right;	
	}
	delete(ptr);
	if(ptr_prev == ptr)
	delete(ptr_prev);
	}
	else
	{
		cout<<"Empty "<<day<<" "<<hour<<'\n';
		myfile<<"Empty "<<day<<" "<<hour<<'\n';
	}
 
}




