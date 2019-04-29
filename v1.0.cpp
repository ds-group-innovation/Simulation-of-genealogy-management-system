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
        vector<Person*> child;                 // 孩子 
};

//全局变量 
Person *root;
int select;


Person* CreateFamilyTree()//单边模拟 
{
	Person *p;
	string n;
	
	cin>>n;
	
	//if( !n.compare("end") )p=NULL; 
	//else{
		//cout<<"test"<<endl;
		p = new Person;
		p->name = n;
		p->flag = 0; 
		p->father = NULL;
	    /*
		for(auto v:p->brother)
	        v=NULL;
	    */
	    
	    //p->child.push_back(CreateFamilyTree()); 
	//}
	
	return p;    
	//for(auto v=p->brother.begin(); v != p->brother.end(); v++)
	//    *v = NULL;
	     
	//root->brother.push_back()
} 

bool nochild(Person*);
//添加成员，传入双亲指针，添加一个孩子（或者一系带） 
Person* searchPerson(string na);
void resetTreeFlag(Person *t);
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
		
		//指好表兄弟关系
		/*
		if( t->father!=NULL  && t->father->child.size() > 0 )
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
		}
		*/ 
	}

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

bool nochild(Person *s)
{
    if(s->child.empty())
	    return 1;
	else
	    return 0;	
} 

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

//重置flag
void resetTreeFlag(	Person *t)
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

//查找最多的孩子 
int searchTheMostNum()
{
	Person *s = root;
	Person *temp;
	int max_num = s->child.size();//
	
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

void subMenuCreate();
void subMenuGetMessage();
void mainMenu()
{
	system("cls"); 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         输入1 创建族谱                            "<<endl;
	cout<<"                         输入2 获取族员信息                        "<<endl;
	cout<<"                         输入3 存档                                "<<endl;
	cout<<"                         输入0 退出程序                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	
	cin>>select;
	
	switch(select)
	{
		case 1:subMenuCreate();break;
		case 2:subMenuGetMessage();break;
		case 3:cout<<"此处功能未完善!";system("pause");mainMenu();break; 
		case 0:exit(0); 
	}
}


void subMenuAddMember();
void subMenuGetMessage();
void subMenu()
{
	system("cls");
    cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         输入1 返回主菜单                          "<<endl;
	cout<<"                         输入2 添加成员                            "<<endl;
	cout<<"                         输入3 获取已有族员信息                    "<<endl;
	cout<<"                         输入0 退出程序                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	
	cin>>select;
	
	switch(select)
	{
		case 1:mainMenu();break;
		case 2:subMenuAddMember();break;
		case 3:subMenuGetMessage();break; 
	    case 0:exit(0);
	}	
}

void subMenuCreate()
{
	system("cls");
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         输入1 创建新族谱                          "<<endl;
	cout<<"                         输入2 从文件中获取已有族谱                "<<endl;
	cout<<"                         输入0 退出程序                            "<<endl; 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	
	cin>>select;
	
	switch(select)
	{
		case 1:cout<<"请输入始祖姓名:\n";root=CreateFamilyTree();break;
		case 2:cout<<"此功能未完善";system("pause");break; 
	    case 0:exit(0);
	}
	//mainMenu();
	subMenu();
}


void hisFather(Person *p);
void hisBrother(Person *p);
void hisChild(Person *p);
void subMenuGetMessage()
{
	if(root==NULL)
    {
    	cout<<"请先创建族谱！";
    	system("pause");
    	mainMenu(); 
	}
	string name;
	Person *p; 
	cout<<"请输入你想要了解的某个人的姓名：";
	while(true)
	{
		cin>>name;
		if(p=searchPerson(name))
		{
			resetTreeFlag(root);
		    break;	
		}
		else
		{
			resetTreeFlag(root);
			cout<<"这个人不再族谱中，请重新输入你想要了解的那个人的姓名：";
		}
	}
	
    system("cls");
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         输入1 显示他的双亲的姓名                  "<<endl;
	cout<<"                         输入2 显示他的后代的姓名                  "<<endl;
	cout<<"                         输入3 显示他的所有兄弟的姓名              "<<endl;
	cout<<"                         输入4 显示他的始祖的姓名                  "<<endl;
	cout<<"                         输入5 显示他的所有信息                    "<<endl; 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	
	cin>>select;
	switch(select)
	{
	    case 1:hisFather(p);break;
		case 2:hisChild(p);break;
		case 3:hisBrother(p);break;
		case 4:mainMenu();break;
	}
	subMenu();   	
}

void subMenuAddMember()
{
	string name;
    cout<<"请输入你想要添加后代的那个族员的姓名：";
	Person *temp;
	while(true)
	{
		cin>>name;
    	if( temp=searchPerson(name) )
    	{
    		resetTreeFlag(root);
    		int num;
			cout<<"请输入要给这个人添加的后代的数量：";
			cin>>num; 
            
			for(int i=0;i<num;i++)
			{
				addMember(temp);
				cout<<endl;
			}		
		    break;
		}
		else
		{ 
			cout<<"这个人不存在，请重新输入：";
		}
		resetTreeFlag(root);
    }
     
	//mainMenu(); 	
    subMenu();
}

//-----------------------------------------
//个人信息展示 
void hisAncestor(Person* p)
{
    if(p->name == root->name)
    {
    	cout<<"这个人就是始祖<<endl";
    	system("pause");
	}
	else
	{
		cout<<"这个人的始祖姓名是："; 
		cout<<root->name<<endl;
	}
} 

void hisFather(Person *p)
{
	if(!p->father)
	{
		cout<<"这个人没有双亲"<<endl;
		system("pause");
	}
	else
	{
		cout<<"这个人的双亲的姓名是：";
		cout<<p->father->name<<endl;
		system("pause");
	}
    subMenu();
}

void hisBrother(Person *p)
{
	int n;
	n = p->brother.size();
	if(n)
	{
	    cout<<"这个人有 "<<n<<" 个兄弟,分别是：\n";
		for(auto v:p->brother)
		    cout<<v->name<<" ";
		cout<<endl;
		system("pause");	
	}
	else
	{
		cout<<"这个人没有兄弟"<<endl;
		system("pause");
	}
	subMenu();
}

void hisChild(Person *p)
{
	int n;
	n = p->child.size();
	if(n)
	{
	    cout<<"这个人有 "<<n<<" 个孩子,分别是：\n";
		for(auto v:p->child)
		    cout<<v->name<<" ";
		cout<<endl;
		system("pause");	
	}
	else
	{
		cout<<"这个人没有后代"<<endl;
		system("pause");
	}
	subMenu();
}

void hisAllMessage(Person *p)
{
	cout<<endl;
	if(p->name == root->name)
	{
		cout<<"这个人是这个家族的始祖"<<endl; 
	}
	else
	{
		cout<<"这个人的始祖是："<<root->name<<endl;
	}
	
	
	cout<<endl;
	if(p->father)
	{
		cout<<"这个人的双亲是："<<p->father->name<<endl;
	}
	else
	{
		cout<<"这个人没有双亲"<<endl; 
	}
	
	
	cout<<endl;
	if(p->child.size())
	{
		cout<<"这个人有"<<p->child.size()<<"个孩子,分别是："<<endl;
		for(auto v:p->child)
		    cout<<v->name<<" ";
		cout<<endl; 
	}
	else
	{
		cout<<"这个人没有后代!"<<endl;
	}
	
	
	cout<<endl;
	if(p->brother.size())
	{
		cout<<"这个人有"<<p->brother.size()<<"个兄弟,分别是："<<endl;
		for(auto v:p->brother)
		    cout<<v->name<<" ";
		cout<<endl; 
	}
	else
	{
		cout<<"这个人没有兄弟!"<<endl;
	}
}

int main()
{
	//root = CreateFamilyTree();
	
	mainMenu(); 
	
	cout<<root->name;
	return 0;
}
