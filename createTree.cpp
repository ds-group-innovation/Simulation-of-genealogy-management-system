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

//Person *root;
Person *root;

Person* CreateFamilyTree()//����ģ�� 
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

//��ӳ�Ա������˫��ָ�룬���һ�����ӣ�����һϵ���� 
void addMember(Person *t)
{
	t->child.push_back(CreateFamilyTree()); 
} 

//�����ֲ��ҽ�㣬�Ա������Ӻ�� 
Person* searchPerson(string na)
{
	Person *s=root;
	
	while(s->name != na)
	{
		
		s = s->child;
	}
	
	return s;
}

//�Ӱ��
void TestTree()
{
    root->child.push_back(CreateFamilyTree());	
} 

int main()
{
	 
	
	root = CreateFamilyTree(); 
	
	//cout<<root->name<<endl;
	
	//���ʼ���һ�����ӵ�����
	//cout<<endl; 
	//cout<<(root->child)[0]->name; 
	TestTree();
	
	//������к��ӵ�����  
	cout<<"��һ��"<<endl;
	for(auto v=root->child.begin(); v != root->child.end(); v++)
	{
		cout<<(*v)->name;
	    cout<<endl;
	}
	
	cout<<"�ڶ���"<<endl;
	for(auto v=(root->child)[0]->child.begin(); v != (root->child)[0]->child.end(); v++)
	{
		cout<<(*v)->name;
	    cout<<endl;
	}
	
	cout<<"������,�϶���wocao,����nimei"<<endl;
	cout<<((root->child)[1]->child)[0]->name<<endl;
	
	cout<<"������,�϶���nimei,����wocao"<<endl;
	cout<<((root->child)[0]->child)[0]->name<<endl; 
	//cout<<(((root->child)[0])->child)[0]->name;
	
	 
	return 0;	
} 
