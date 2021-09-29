
#ifndef LIST_H_
#define LIST_H_
#ifdef	__cplusplus
extern "C" {
#endif


class BST{
public:

BST();

void insert(std::string const & title, const int & day, const int & time);
void retrieve( std::string const & title,const int & day,const int & time );
void in_ord_traversal();
void program(std::string words[], int numofwords);
bool ParseDocument(std::string file_name,std::string file_name2);
bool checkStoi(std::string x);
void deleteNode(const int & day, const int & hour);

private:
	
	struct Node;
	typedef Node * Tree;
	void in_ord_traversal_private(Tree nptr);
	
	struct Node {
		bool nullTree;
		int Day ;
		int Time;
		std::string Title;
		Tree Left;
		Tree Right;
	};

   
	
	Tree Root;
	Tree temp;
	Tree temp2;
}; 



#ifdef	__cplusplus
}
#endif
#endif 