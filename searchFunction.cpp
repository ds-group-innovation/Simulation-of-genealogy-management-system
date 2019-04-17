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

// --------------------------------------------------------------

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

bool nochild(Person *s)
{
    for(auto t=s->child.begin(); t!= s->child.end(); t++)
	{
		//��һ�����Ӳ�Ϊ�գ�����˴��ں�� 
		if( (*t) != NULL)
		    return 1;	
		else
		    return 0; 
	}	
} 

bool allchildhassearch(Person *s)
{
    for(auto t=s->child.begin(); t!= s->child.end(); t++)
	{
		//����û����� 
		if( (*t)->flag==0 )
		    return 0;
	}
	return 1;	
}

Person* searchPerson(string na)
{
	Person *s=root,*temp;
	
	if(s->name == na)
	    return s;//���Ȳ��� 
	else
	{
		while(!allchildhassearch(s) && s->name !=na)//û�ҵ��ˣ�����s�ĺ��Ӳ�δ������� 
		{
		    temp = s;//ÿ�ζ������ȿ�ʼ 
		    temp = hasChildhasoneNoSearch(temp);//����temp�ĺ��ӣ����ࣩܺܶ���������û����� 
		    while(temp)//temp��Ϊ�� 
		    {
		    	if(temp->name == na)
		    	    return temp;
		    	else
		    	{
		    		//û�к��ӻ������к��Ӷ����ҹ� 
		    		if( nochild(temp) || allchildhassearch(temp) )//all���������ж��������к����Ƿ񶼱����� 
					    temp->flag = 1;//��ǲ�� 
					else
					    temp->flag = 0; 
				    temp = hasChildhasoneNoSearch(temp);
					//cout<<"1"<<endl; 
		    	}
				//cout<<"1"<<endl; 
			}
			//cout<<"1"<<endl;
	    }
	    //cout<<"1"<<endl;	 
	}
	
}


int main()
{
	root = CreateFamilyTree(); 
	Person *q = searchPerson("wocao");
	
	cout<<endl<<"��ӳ�Ա"<<endl; 
	addMember(q);
	
	
	Person *test;
	if(test = searchPerson("shan"))
	{
		cout<<endl<<"��ӳ�Ա"<<endl;
	    addMember(test);
	}
	else
	{
		cout<<"û�������"<<endl;
	}
	/*
	cout<<endl;
	cout<<(q->child)[0]->name<<endl;
	cout<<(q->child)[1]->name<<endl;
	
	cout<<(((q->child)[1])->child)[0]->name<<endl;
	*/
	
	cout<<(((root->child)[1])->child)[0]->name<<endl;
	
	return 0;	
} 
