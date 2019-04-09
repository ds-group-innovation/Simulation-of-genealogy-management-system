#include<iostream>
#include<vector>
#include<malloc.h>
using namespace std;

class Person{
	public:
		string name;                          // ÐÕÃû 
		//char sex;
	public:
		Person *father;                       // ¸¸Ç× 
        Person *brother;		      // ÐÖµÜ 
        Person *child;                // º¢×Ó 
};

//Person *root;
Person* create()
{
	string name;
	Person *p;
	cin>>name;
	if(name=="wocao") p=NULL;
	else
	{
		p = new Person;
		p->name = name;
		//p->brother = create();
		p->child = create(); 
	}
	return p;
}
