#include<iostream>
#include<vector>
#include<fstream>
#include<cmath> 

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

Person* loadFromFile()
{
	ifstream infile("family.txt",ios::in);
	int num;
	string name;
	vector<Person*> a,b;
	
	infile>>name;
	infile>>num;
    
    //祖先结点 
    Person *p = new Person;	
	p->name = name;
	p->flag = 0;
	p->father = NULL;
	for(auto v:p->brother)
	    v=NULL;
	//其他赋值为空 
	
	int count = 0,i=2;
	
	while( !infile.eof() && count != num )
	{
	    infile>>name;
	    //cout<<name<<" ";		
	    Person *q = new Person;
		q->name = name;
		q->father = NULL;
	    for(auto v:q->brother)
	        v=NULL;
		//其他为空 
		a.push_back(q);
		count++; 
	}
	
	/*
	for(auto i=a.begin(); i!=a.end(); i++)
	{
		cout<<(*i)->name<<endl;
	}
	*/
	
	//初代，第二层 
	for(auto i=a.begin(); i!=a.end(); i++)
	{
		p->child.push_back(*i);
	}
	
	i = i+1;
	
	//第三层 
	int co=0;
	while( !infile.eof() && co != pow(num,i-1) )
	{
		infile>>name;
		Person *q = new Person;	
	    q->name = name;
		//其他赋空
		q->father = NULL;
	    for(auto v:q->brother)
	        v=NULL;
		b.push_back(q);
		co++;
	}
	//cout<<endl<<b[0]->name<<endl;
	
	vector<Person*> *temp=&b;
	vector<Person*> bs;
	for(auto v=a.begin(); v!=a.end(); v++)
	{
		int count = 0;
		for(auto s=temp->begin(); s!=temp->end(); s++)
		{
			
			if(count != num)
			{
				count++;
				//cout<<(*s)->name<<endl;
				(*v)->child.push_back(*s);
			
			}
			else
			{
				vector<Person*>::iterator it;
                it = temp->begin()+count;
                
				bs.assign(it,temp->end());
			    temp = &bs;
		        break; 
			}
		}
	}
	
	a.assign(b.begin(),b.end());
	b.clear();
	
	//后面几层 
	cout<<"\n----------"<<endl; 
	while( !infile.eof())
	{
	    i = i+1;
	    int l= 0;
	    while(l != pow(num,i-1))
	    {
	    	infile>>name;
		    Person *q = new Person;	
	        q->name = name;
		    //其他赋空
		    
			b.push_back(q);
		    l++;
		}
	    
		vector<Person*> *temp=&b;
	    vector<Person*> bs;
	    for(auto v=a.begin(); v!=a.end(); v++)
	    {
		    int count = 0;
		    for(auto s=temp->begin(); s!=temp->end(); s++)
		    {
			
			    if(count != num)
			    {
				    count++;
				    //cout<<(*s)->name<<" ";
				    (*v)->child.push_back(*s);
			
			    }
			    else
			    {
				    vector<Person*>::iterator it;
                    it = temp->begin()+count;
                
				    bs.assign(it,temp->end());
			        temp = &bs;
		            break; 
			    }
		    }
	    }
		
		cout<<endl;
		a.assign(b.begin(),b.end());
	    b.clear();		
	}
	
	return p;
} 

int main()
{
	/*
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
	cout<<endl;
	cout<<(q->child)[0]->name<<endl;
	cout<<(q->child)[1]->name<<endl;
	
	cout<<(((q->child)[1])->child)[0]->name<<endl;
	
	cout<<(((root->child)[1])->child)[0]->name<<endl;
	*/
	
    root = loadFromFile();
    cout<<endl<<"----------"<<endl;
	//cout<<root->name<<endl;
    
    cout<<(((root->child)[0]->child)[0]->child)[0]->name<<endl;
    
	
	
	return 0;	
} 
