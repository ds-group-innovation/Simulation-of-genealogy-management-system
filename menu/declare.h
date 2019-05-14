
#include"family.h"
//#include<windows.h>会与select冲突 
using namespace std;

//菜单 
void subMenu();
void mainMenu();
void subMenuCreate();
void subMenuAddMember();
void subMenuGetMessage();

//功能函数，详情看注释 
void saveToFile();
void showTheFamilyTree();
void hisChild(Person* p);
void addMember(Person *t);
void hisFather(Person* p);
void hisBrother(Person* p);
void hisAncestor(Person* p);
void resetTreeFlag(Person *t);
void hisAllMessage(Person *p);

int searchTheMostNum();

bool nochild(Person *s);
bool allchildhassearch(Person *s);
bool allIsZero(vector<Person*> s);

Person* loadFromFile();
Person* CreateFamilyTree();
Person* searchPerson(string na);
Person* hasChildhasoneNoSearch(Person* s);

#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>
#include"family.h"
#include"declare.h"
//#include<windows.h>会与select冲突 
using namespace std;

//成员初始化 
Person* CreateFamilyTree()//单边模拟 
{
	Person *p;
	string n;
	
	cin>>n;
	p = new Person;
	p->name = n;
	p->flag = 0; 
	p->father = NULL;
	/*
	    for(auto v:p->brother)
	        v=NULL;
	*/
	return p;    
} 


/*
  - 读取family.txt建立家谱树 
  - 建家谱树的同时会指好新成员与旧成员的兄弟关系和双亲关系 
*/ 
Person* loadFromFile()
{
	ifstream infile("family.txt",ios::in);
	
	if(!infile)
	{
		cout<<"没有家谱文件或者文件已丢失"<<endl;
		system("pause");
		mainMenu();
	}
	
	int num;
	string name;
	vector<Person*> a,b;
	
	infile>>name;
	infile>>num;
    
    //建立祖先结点 
    Person *p = new Person;	
	p->name = name;
	p->flag = 0;
	p->father = NULL;

	//count用于计算孩子是否已经添加够了 
	int count = 0,i=2;
	
	if(infile.eof())
	    return p; 
	
	//第二层 
	while( !infile.eof() && count != num )
	{
	    infile>>name;
	    //cout<<name<<" ";		
	    Person *q = new Person;
		q->name = name;
		q->father = p;
		q->flag = 0;
		a.push_back(q);
		count++; 
	}
	
	//初代,祖辈的的孩子 
	for(auto i=a.begin(); i!=a.end(); i++)
	{
		(*i)->flag = 0;
		if((*i)->name == "0")continue;
		if( !nochild(p) )
		{
			//亲兄弟关系 
			for(auto v:p->child)
			{
				v->brother.push_back(*i);
			    (*i)->brother.push_back(v);
			}
		}
		
		p->child.push_back(*i);
	}
	
	if(infile.eof())
	    return p;
	 
	//后面几层 
	while( !infile.eof())
	{
	    i = i+1;
	    int l= 0;
	    while(l != pow(num,i-1))
	    {
	    	infile>>name;
		    Person *q = new Person;	
	        q->name = name;
		    q->flag = 0;
			b.push_back(q);
		    l++;
		}
	    
	    //指好兄弟关系，包括表兄弟 
	    for(auto g=b.begin(); g!=b.end(); g++)
	    {
	    	if((*g)->name=="0")continue;
	    	for(auto z=b.begin(); z!=b.end(); z++)
	    	{
	    		if(z==g )continue;
	    		if((*z)->name == "0")continue;
	    		(*g)->brother.push_back(*z);
			}
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
				    if( (*s)->name == "0" )continue;
				    
					//亲兄弟关系,并不需要这么操作 
					/* 
					if( !nochild(*v) )
				    {
				        for(auto t:(*v)->child)
						{
						    (*s)->brother.push_back(t);
							t->brother.push_back(*s);	
						} 
					}
					*/ 
					
					(*s)->father = (*v); 
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
		
		//cout<<endl;
		a.assign(b.begin(),b.end());
	    b.clear();		
	}
	
	return p;
}


/*
  - 用于给家谱树添加成员
  - 可自主定义要添加成员的数量
  - 如果新添加的成员和家谱树中的某个成员同名，需重新给新添加成员命名 
  - 辅助函数：CreateFamilyTree()、resetTreeFlag()、nochild()  
*/ 
void addMember(Person *t)
{
	//fflush(stdin);
	//Person *temp = new Person;
	cout<<"请输入要添加的成员的姓名："; 
	Person *temp = CreateFamilyTree();
	
	//同名同姓考虑
	while( searchPerson(temp->name) )
	{
		resetTreeFlag(root); 
	    cout<<"这个人已经存在，请重新输入要添加的成员的姓名：";
		temp = CreateFamilyTree();
	}
	resetTreeFlag(root);  
	
	temp->father = t;
	//双亲有孩子,建立兄弟关系 
	if( !nochild(t))
	{
		//指好亲兄弟关系 
		for(auto v:t->child)
		{
			v->brother.push_back(temp);
			temp->brother.push_back(v);
		}
	}
	
	//指好表兄弟关系	
	if( t->brother.size()>0)
	{
		for(auto z:t->brother)
		{
			if( nochild(z) )continue;
			for(auto g:z->child)
			{
				//if(g->name == temp->name)continue;
				g->brother.push_back(temp);
				temp->brother.push_back(g);
			}
		}
	} 
		
	
	//实现2，不完整 
	/*if( t->father!=NULL  && t->father->child.size() > 0 )
	{
		for(auto i=t->father->child.begin(); i!=t->father->child.end(); i++)
		{
			if( (*i)!=t && !nochild(*i) )
			{
				for(auto q:(*i)->child)
				{
				    q->brother.push_back(temp);
				    temp->brother.push_back(q);
				}
			}	
		}
	}*/
			
	
	t->child.push_back(temp);
	//delete temp; 
} 


// --------------------------------------------------------------


//返回这个人的孩子(如果有的话)，而且孩子没被查询过
Person* hasChildhasoneNoSearch(Person* s)
{
	if( s->child.empty())
	    return NULL; 
    else
    {
    	for(auto t=s->child.begin(); t!= s->child.end(); t++)
	    {
		    if( (*t)->flag==0 )
		    {
			    //(*t)->flag =1; 
		        return *t;	
		    }
	    }
	}
	return NULL;	
}  


//用于判断某个人是否有后代 
bool nochild(Person *s)
{
    if(s->child.empty())
	    return 1;
	else
	    return 0;	
} 


/* 
 - 用于判断这个人的所有孩子是否都被查过 
 - 存在没被查过的就返回假，都被查过或者没有孩子就返回真  
*/ 
bool allchildhassearch(Person *s)
{
	if(s->child.empty())
	    return 1;
    else
    {
    	for(auto t=s->child.begin(); t!= s->child.end(); t++)
	    {    
		    //存在没查过的 
		    if( (*t)->flag==0 )
		        return 0;
	    }
	}
	return 1;	
}


/*
  - 检索函数，根据传入的姓名检索家谱树，存在这个成员就返回这个成员对应的Person*类型的结点
  - 辅助函数：hasChildhasoneNoSearch()、nochild()、allchildhassearch() 
*/
Person* searchPerson(string na)
{
	Person *s=root,*temp;
	
	if(s->name == na)
	    return s;//祖先不是 
	else
	{
		while(!allchildhassearch(s))//没找到人，而且s的孩子并未都被查过 
		{
		    //temp = s;//每次都从祖先开始 
		    temp = hasChildhasoneNoSearch(s);//函数返回temp的孩子（可能很多），这个孩子没被查过 
		    while(temp)//temp不为空 
		    {
		    	if(temp->name == na)
		    	    return temp;
		    	else
		    	{
		    		//没有孩子或者所有孩子都被找过 
		    		if( nochild(temp) || allchildhassearch(temp) )//all函数用来判断他的所有孩子是否都被查了 
					    temp->flag = 1;//标记查过
				    temp = hasChildhasoneNoSearch(temp);
					//cout<<"1"<<endl; 
		    	}
				//cout<<"1"<<endl; 
			}
			//cout<<"1"<<endl;
	    }
	    //cout<<"1"<<endl;
		return NULL;	 
	}
	
}


/* 
  - 重置家谱树用于实现检索（searchPerson函数）的flag成员 
  - 家谱树每被检索一次就需要调用它，避免检索出问题 
*/ 
void resetTreeFlag(Person *t)
{
    if(nochild(t))
	{
	    t->flag = 0;
		return ;	
	}
	else//有孩子 
	{
		t->flag = 0;
		for(auto i=t->child.begin(); i!=t->child.end(); i++)
		{
			//(*i)->flag = 0;
		    resetTreeFlag(*i);	
		}   
	}
}


/*
 - 用于检索家谱树，获取后代最多的那个人的孩子数目，方便后续存档的实现(saveToFile函数)
 - 辅助函数：resetTreeFlag()、hasChildhasoneNoSearch()、allchildhassearch()、nochild() 
*/ 
int searchTheMostNum()
{
	Person *s = root;
	Person *temp;
	int max_num = s->child.size();//默认为祖先的孩子数 
	
	do
	{
		//cout<<"\n1 ";
		//temp = s;//每次从祖先开始 
	    temp = hasChildhasoneNoSearch(root);
	    while(temp)//temp不为空 
		{
		    //cout<<"\n1 ";
		    if(temp->child.size() > max_num)
		        max_num = temp->child.size();
			if( nochild(temp) || allchildhassearch(temp) )//all函数用来判断他的所有孩子是否都被查了 
				temp->flag = 1;//标记查过 
			else
				temp->flag = 0;
			temp = hasChildhasoneNoSearch(temp);
		}
	}while( !allchildhassearch(root));
	return max_num;	
}

