#include<iostream>
#include<vector>
#include<malloc.h>
using namespace std;

//c++11标准编译：-std=c++11

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

Person* CreateFamilyTree()
{
	//设置后代
	//p = (Person*)malloc(sizeof(Person*));
	Person *p;
	p = new Person;
	
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

void Children(Person *r)//后代模拟 
{
	Person *p;
	//p = (Person*)malloc(sizeof(Person *));//用不了卧槽 
	p = new Person;
	p->father = r;
	p->name = "ye";
	
	for(auto v:p->brother)
	    v=NULL;
	
	for(auto v:p->child)
	    v=NULL;
    
    r->child.push_back(p);
    
    //delete p;//不用
	 
    //cout<<p->father->name;
    
    //cout<<p->name;
    
}

int main()
{
	Person *root; 
	
	root = CreateFamilyTree(); 
	
	cout<<root->name;
	Children(root);
	
	//输出始祖第一个孩子的姓名
	cout<<endl; 
	cout<<(root->child)[0]->name; 
	
	/*
	//输出所有孩子的姓名  
	for(auto v:root->child)
	    cout<<v->name<<endl;
	*/ 
	return 0;	
} 
