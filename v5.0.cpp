/*
  - author：叶汕、莫小荷、刘津睿
  - url：https://github.com/ds-group-innovation/Simulation-of-genealogy-management-system
  - copyright：2019 yeshan <yeshan1329441308@gmail.com>
  - license：MIT, see LICENSE for more details.
  - version：v3.0 
  - contact me：1329441308@qq.com
  - remember：代码辣鸡非我意，谈笑风声活长命  
*/

//c++11标准编译：-std=c++11（Dev-C++5.11）
 
#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>
//#include<windows.h>会与select冲突 
using namespace std;


/*
 - 家谱树结构体 
 - 由容器vector实现多叉链表结构 
*/ 
class Person{
	public:
		string name;                          // 姓名 
		//char sex;
		int flag;                             //用来标志有没有被找过,0没找过 
	public:
		Person *father;                       // 双亲 
        vector<Person*> brother;		      // 兄弟 
        vector<Person*> child;                // 孩子 
};


/*
  - 全局变量
    - root: 族谱 
    - select: 用于菜单选择 
*/ 
Person *root;
int select;


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

 
void mainMenu()
{
	system("cls"); 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         输入1 创建族谱                            "<<endl;
	cout<<"                         输入2 获取族员信息                        "<<endl;
	cout<<"                         输入3 存档退出                            "<<endl;
	cout<<"                         输入4 显示族谱                            "<<endl;
	cout<<"                         输入5 添加成员                            "<<endl;
	cout<<"                         输入0 退出程序                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	
	cin>>select;
	
	switch(select)
	{
		case 1:subMenuCreate();break;
		case 2:subMenuGetMessage();break;
		case 3:
		    if(root==NULL)
			    cout<<"家谱树还未建立，请先建树！";
			else
			{
				saveToFile();
			    cout<<"存档成功!"<<endl;
			}
			system("pause");
			exit(0);//cout<<"此处功能未完善!";system("pause");mainMenu();break; 
		    break;
		case 4:
		    if(root==NULL)
			    cout<<"家谱树还未建立，请先建树！";
			else
			    showTheFamilyTree();
			system("pause");
			break;
		case 5:
		    if(root==NULL)
			    cout<<"家谱树还未建立，请先建树！";
		    else
			    subMenuAddMember();
			system("pause");
			break; 
		case 0:exit(0);break;
		//default: mainMenu();
	}
	mainMenu();
}


void subMenu()
{
	system("cls");
    cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         输入1 返回主菜单                          "<<endl;
	cout<<"                         输入2 添加成员                            "<<endl;
	cout<<"                         输入3 获取已有族员信息                    "<<endl;
	cout<<"                         输入4 显示族谱                            "<<endl;
	cout<<"                         输入0 退出程序                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	
	cin>>select;
	
	switch(select)
	{
		case 1:mainMenu();break;
		case 2:subMenuAddMember();break;
		case 3:subMenuGetMessage();break;
		case 4:showTheFamilyTree();system("pause");break; 
	    case 0:exit(0);break;
	    default: subMenu();
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
		case 2:root=loadFromFile();if(root)cout<<"创建成功";system("pause");break; 
	    case 0:exit(0);
	}
	//mainMenu();
	subMenu();
}


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
	cout<<"                         输入1     显示他的双亲的姓名              "<<endl;
	cout<<"                         输入2     显示他的后代的姓名              "<<endl;
	cout<<"                         输入3     显示他的所有兄弟的姓名          "<<endl;
	cout<<"                         输入4     显示他的始祖的姓名              "<<endl;
	cout<<"                         输入5     显示他的所有信息                "<<endl;
	cout<<"                         输入其它  返回上一层菜单                  "<<endl; 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	
	cin>>select;
	switch(select)
	{
	    case 1:hisFather(p);break;
		case 2:hisChild(p);break;
		case 3:hisBrother(p);break;
		case 4:hisAncestor(p);break;
		case 5:hisAllMessage(p);break;
		default: subMenu(); 
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
			cout<<"请输入要给这个人添加的后代的数量（整数1-999）：";
			//while(cin.fail()) 
		    cin>>num;
			 
            //int s=cin.rdstate();//判断流输入状态 
            /*
			while(num<0||num>999)
            {
            	//cin.clear(); 
            	cout<<"您输入的不是整数，请输入一个整数："; 
            	cin>>num;
            	//s = cin.rdstate();
			}
			*/
            
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

//祖先 
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

//双亲 
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

//兄弟，包括表兄弟 
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

//后代 
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

//个人所有相关信息 
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
	
	system("pause");
}

//判断这个数组成员是否都为零成员，辅助存档函数循环的实现 
bool allIsZero(vector<Person*> s)
{
	if(s.empty())return 1;
	for(auto z=s.begin();z!=s.end();z++)
	{
		if( (*z)->name != "0")
		    return 0;
	}
	return 1;
}


/*
  - 家谱树存档
  - 辅助函数：allIsZero() 
*/ 
void saveToFile()
{
	Person *r = root;
    int num = searchTheMostNum();
    ofstream out("family.txt", ios::out);
    vector<Person*> a,b;
    
    out<<r->name;
    out<<" ";
    out<<num;
    out<<endl;
    
    //祖先没孩子，结束 
    if(r->child.empty())
    {
    	out.close(); 
    	return ;
	} 
    //第二层 
	int count=0;
	for(auto v:r->child)
    {
        out<<v->name<<" ";
		a.push_back(v);
		count++;	
	}
	while(count != num)
	{
		Person *temp=new Person;
		temp->name = "0";
		temp->flag = 0;
		temp->father = NULL;
		out<<temp->name<<" ";
		a.push_back(temp);
		count++;
	}
	out<<endl;
    
    //如果a的孩子都不是0
	while(!allIsZero(a))
	{
		for(auto q:a)
		{
	    	if( q->name == "0")
			{
				for(int i=0;i<num;i++)
				{	
					Person *temp=new Person;
		        	temp->name = "0";
		        	temp->flag = 0;
		        	temp->father = NULL;
		        	out<<temp->name<<" ";
		        	b.push_back(temp);
				}
			}
			else if(nochild(q))
			{
			    int co=q->child.size();
				while( co!=num)
				{
		    		Person *temp=new Person;
		    		temp->name = "0";
		    		temp->flag = 0;
		    		temp->father = NULL;
		    		out<<temp->name<<" ";
		    		b.push_back(temp);	
		    		co++;
				}	
			} 
		    else
			{
				for(auto x:q->child)
			    {
					out<<x->name<<" ";
					b.push_back(x);
				}
				int co=q->child.size();
				while( co!=num)
				{
		    		Person *temp=new Person;
		    		temp->name = "0";
		    		temp->flag = 0;
		    		temp->father = NULL;
		    		out<<temp->name<<" ";
		    		b.push_back(temp);	
		    		co++;
				}
			} 
				
		}
		//放完一层了 
		out<<endl;
		a.clear();
		a.assign(b.begin(),b.end()); 
		b.clear(); 
	}
	
    out.close();
    //exit(0); 
}


/*
  - 显示家谱树
  - 辅助函数：allIsZero() 
*/
void showTheFamilyTree()
{
	Person *r = root;
    int num = searchTheMostNum();
    vector<Person*> a,b;
    
    cout<<"( "<<r->name<<" )";
    //cout<<" ";
    //cout<<num;
    cout<<endl;
    
    //祖先没孩子，结束 
    if(r->child.empty())
    { 
    	return ;
	} 
    //第二层 
	int count=0;
	cout<<"( ";
	for(auto v:r->child)
    {
        cout<<v->name<<" ";
		a.push_back(v);
		count++;	
	}
	while(count != num)
	{
		Person *temp=new Person;
		temp->name = "0";
		temp->flag = 0;
		temp->father = NULL;
		cout<<temp->name<<" ";
		a.push_back(temp);
		count++;
	}
	cout<<")";
	cout<<endl;
    
    //如果a的孩子都不是0
	while(!allIsZero(a))
	{
		for(auto q:a)
		{
	    	if( q->name == "0")
			{
				cout<<"( ";
				for(int i=0;i<num;i++)
				{	
					Person *temp=new Person;
		        	temp->name = "0";
		        	temp->flag = 0;
		        	temp->father = NULL;
		        	
		        	b.push_back(temp);
				}
				//只打印一个0，方便看 
				cout<<"0 ";
				cout<<") "; 
			}
			else if(nochild(q))//没有孩子 
			{
				cout<<"( 0 ) ";
			}
		    else
			{
				cout<<"( ";
				for(auto x:q->child)
			    {
					cout<<x->name<<" ";
					b.push_back(x);
				}
				int co=q->child.size();
				while( co!=num)
				{
		    		Person *temp=new Person;
		    		temp->name = "0";
		    		temp->flag = 0;
		    		temp->father = NULL;
		    		//cout<<temp->name<<" ";
		    		b.push_back(temp);	
		    		co++;
				}
				cout<<") ";
			} 
				
		}
		//显示完一层了 
		cout<<endl;
		a.clear();
		a.assign(b.begin(),b.end()); 
		b.clear(); 
	}
}


int main()
{
	mainMenu(); 
	//cout<<"我佛了！"; 
	return 0;
}
