#include<iostream>
#include<vector>
#include<malloc.h>
using namespace std;

//c++11��׼���룺-std=c++11

class Person{
	public:
		string name;                          // ���� 
		//char sex;
	public:
		Person *father;                       // ���� 
        vector<Person*> brother;		      // �ֵ� 
        vector<Person*> child;                // ���� 
};

Person* CreateFamilyTree()
{
	//���ú��
	//p = (Person*)malloc(sizeof(Person));
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

void Children(Person *r, string n)//��һ��ģ�� 
{
	Person *p;
	//p = (Person*)malloc(sizeof(Person));//�ò����Բ� 
	p = new Person;
	p->father = r;
	p->name = n;
	
	for(auto v:p->brother)
	    v=NULL;
	
	for(auto v:p->child)
	    v=NULL;
    
    r->child.push_back(p);
    
    //delete p;//����
	 
    //cout<<p->father->name;
    
    //cout<<p->name;
    
}


/*
//���ݸ���������Ӻ�� 
void Generation(string n)
{
	Person *p,*father;
	string na;
	
	father = Search(n);
	
	cin>>na;
	p = new Person;
	p->name = na;
	 
	
}
//���ҽ��,���������������� 
Person* Search(string name)
{
	Person *p = root;
	while(p->name != name)
    {
    	while(p)
    	    p = p->child[0];
	}
	return p;	
}
*/

int main()
{
	Person *root; 
	
	root = CreateFamilyTree(); 
	
	cout<<root->name;
	Children(root,"ye");
	Children(root,"mo");
	//���ʼ���һ�����ӵ�����
	cout<<endl; 
	cout<<(root->child)[0]->name<<endl; 
	cout<<(root->child)[1]->name<<endl;
	/*
	//������к��ӵ�����  
	for(auto v:root->child)
	    cout<<v->name<<endl;                 
	*/ 
	return 0;	
} 
