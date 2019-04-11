#include<iostream>
#include<vector>
#include<malloc.h>
using namespace std;

//c++11��׼���룺-std=c++11

class Person{
	public:
		string name;                          // ���� 
		//char sex;
		int flag;                             //������־��û�б��ҹ�,0û�ҹ� 
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
		p->flag = 0; 
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

bool haveThePerson(Person* s,string na);
//�����ֲ��ҽ�㣬�Ա������Ӻ�� 
Person* searchPerson(string na)
{
	Person *s=root;
	
	if(s->name == na)return s;
	else{
		//���ڵ�û�У������ĺ�������
		//if ��û�У����� 
		//û��,��ô 
		
		/*for(auto t=s->child.begin(); t!= s->child.end(); t++)
		{
		    if( (*t)->name == na )break;
				
	    }*/
	    
	    for(auto t=s->child.begin(); t!= s->child.end(); t++)
	    {
	    	if((*t)!=NULL)break;
	    	else{
	    		if( haveThePerson(*t,na) )
	    		{
	    			//��; 
				}
				else{
					continue;
				} 
			}
		}
	    //���������û��
	    //if( isHasChild( (s->child)[0] ) )	 
	}
	return s;
}

//���˫�׵ĵ�һ��������������
bool haveThePerson(Person* s,string na)
{
	for(auto t=s->child.begin(); t!= s->child.end(); t++)
	{
		if( (*t)->name == na )return true;		
	}
	return false; 
} 

//��û�к��ӣ��� 
bool isHasChild(Person* s)
{
    for(auto t=s->child.begin(); t!= s->child.end(); t++)
	{
		if((*t)!=NULL)return true;		
	    else return false;
	}
} 

//���ص�һ������ 
Person* firstChild(Person* s)
{
	//�к��� 
	for(auto t=s->child.begin(); t!= s->child.end(); t++)
	{
		if( (*t) != NULL )return *t;		
	}
	return NULL; 
}


//��������˵ĺ���(����еĻ�)�����Һ���û����ѯ��
Person* hasChildhasoneNoSearch(Person* s)
{
    for(auto t=s->child.begin(); t!= s->child.end(); t++)
	{
		if( (*t) != NULL && (*t)->flag==0 )
		{
			//(*t)->flag =1; 
		    return *t;	
		}
	}
	return NULL;	
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
