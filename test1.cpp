#include<iostream>
#include<vector>
#include<malloc.h>
using namespace std;

class Person{
	public:
		string name;                          // ���� 
		//char sex;
	public:
		Person *father;                       // ���� 
        Person *brother;		      // �ֵ� 
        Person *child;                // ���� 
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
