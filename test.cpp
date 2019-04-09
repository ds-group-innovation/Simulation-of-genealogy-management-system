#include<iostream>
#include<vector>
#include<malloc.h>
using namespace std;

class Person{
	public:
		string name;                          // 姓名 
		//char sex;
	public:
		Person *father;                       // 父亲 
        vector<Person*> brother;		      // 兄弟 
        vector<Person*> child;                // 孩子 
};

//Person *root;

Person* CreateFamilyTree(Person *p)
{
	//设置后代
	//p = (Person*)malloc(sizeof(Person*));
	p->name = "shan";
	
	p->father = NULL;
	for(auto v:p->brother)
	    v=NULL;
	
	for(auto v:p->child)
	    v=NULL;
	
	return p;    
	//for(auto v=p->brother.begin(); v != p->brother.end(); v++)
	//    *v = NULL;
	     
	//root->brother.push_back()
} 


int main()
{
	Person root;
	CreateFamilyTree(&root);
	cout<<root.name;
    return 0;	
} 
