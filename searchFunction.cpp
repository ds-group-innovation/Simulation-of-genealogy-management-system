#include<iostream>
#include<vector>
#include<malloc.h>
using namespace std;

//c++11标准编译：-std=c++11

class Person{
	public:
		string name;                          // 姓名 
		//char sex;
		int flag;                             //用来标志有没有被找过,0没找过 
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

//添加成员，传入双亲指针，添加一个孩子（或者一系带） 
void addMember(Person *t)
{
	t->child.push_back(CreateFamilyTree()); 
} 

// --------------------------------------------------------------

//返回这个人的孩子(如果有的话)，而且孩子没被查询过
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
		//第一个孩子不为空，这个人存在后代 
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
		//存在没查过的 
		if( (*t)->flag==0 )
		    return 0;
	}
	return 1;	
}

Person* searchPerson(string na)
{
	Person *s=root,*temp;
	
	if(s->name == na)
	    return s;//祖先不是 
	else
	{
		while(!allchildhassearch(s) && s->name !=na)//没找到人，而且s的孩子并未都被查过 
		{
		    temp = s;//每次都从祖先开始 
		    temp = hasChildhasoneNoSearch(temp);//返回temp的孩子（可能很多），这个孩子没被查过 
		    while(temp)//temp不为空 
		    {
		    	if(temp->name == na)
		    	    return temp;
		    	else
		    	{
		    		//没有孩子或者所有孩子都被找过 
		    		if( nochild(temp) || allchildhassearch(temp) )//all函数用来判断他的所有孩子是否都被查了 
					    temp->flag = 1;//标记查过 
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
	
	cout<<endl<<"添加成员"<<endl; 
	addMember(q);
	
	
	Person *test;
	if(test = searchPerson("shan"))
	{
		cout<<endl<<"添加成员"<<endl;
	    addMember(test);
	}
	else
	{
		cout<<"没有这个人"<<endl;
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
