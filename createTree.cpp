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
Person *root;

Person* CreateFamilyTree()//单边模拟 
{
	Person *p;
	string n;
	
	cin>>n;
	
	if( !n.compare("end") )p=NULL; 
	else{
		//cout<<"test"<<endl;
		p = new Person;
		p->name = n;
		p->father = NULL;
	    for(auto v:p->brother)
	        v=NULL;
	    
	    p->child.push_back(CreateFamilyTree()); 
	}
	
	return p;    
	//for(auto v=p->brother.begin(); v != p->brother.end(); v++)
	//    *v = NULL;
	     
	//root->brother.push_back()
} 

//添加成员，传入双亲指针，添加一个孩子（或者一系带） 
void addMember(Person *t)
{
	t->child.push_back(CreateFamilyTree()); 
} 

//按名字查找结点，以便给他添加后代 
Person* searchPerson(string na)
{
	Person *s=root;
	
	while(s->name != na)
	{
		
		s = s->child;
	}
	
	return s;
}

//子半边
void TestTree()
{
    root->child.push_back(CreateFamilyTree());	
} 

int main()
{
	 
	
	root = CreateFamilyTree(); 
	
	//cout<<root->name<<endl;
	
	//输出始祖第一个孩子的姓名
	//cout<<endl; 
	//cout<<(root->child)[0]->name; 
	TestTree();
	
	//输出所有孩子的姓名  
	cout<<"第一代"<<endl;
	for(auto v=root->child.begin(); v != root->child.end(); v++)
	{
		cout<<(*v)->name;
	    cout<<endl;
	}
	
	cout<<"第二代"<<endl;
	for(auto v=(root->child)[0]->child.begin(); v != (root->child)[0]->child.end(); v++)
	{
		cout<<(*v)->name;
	    cout<<endl;
	}
	
	cout<<"第三代,老豆是wocao,不是nimei"<<endl;
	cout<<((root->child)[1]->child)[0]->name<<endl;
	
	cout<<"第三代,老豆是nimei,不是wocao"<<endl;
	cout<<((root->child)[0]->child)[0]->name<<endl; 
	//cout<<(((root->child)[0])->child)[0]->name;
	
	 
	return 0;	
} 
