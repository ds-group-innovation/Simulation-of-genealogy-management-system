
#include"family.h"
//#include<windows.h>����select��ͻ 
using namespace std;

//�˵� 
void subMenu();
void mainMenu();
void subMenuCreate();
void subMenuAddMember();
void subMenuGetMessage();

//���ܺ��������鿴ע�� 
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
//#include<windows.h>����select��ͻ 
using namespace std;

//��Ա��ʼ�� 
Person* CreateFamilyTree()//����ģ�� 
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
  - ��ȡfamily.txt���������� 
  - ����������ͬʱ��ָ���³�Ա��ɳ�Ա���ֵܹ�ϵ��˫�׹�ϵ 
*/ 
Person* loadFromFile()
{
	ifstream infile("family.txt",ios::in);
	
	if(!infile)
	{
		cout<<"û�м����ļ������ļ��Ѷ�ʧ"<<endl;
		system("pause");
		mainMenu();
	}
	
	int num;
	string name;
	vector<Person*> a,b;
	
	infile>>name;
	infile>>num;
    
    //�������Ƚ�� 
    Person *p = new Person;	
	p->name = name;
	p->flag = 0;
	p->father = NULL;

	//count���ڼ��㺢���Ƿ��Ѿ���ӹ��� 
	int count = 0,i=2;
	
	if(infile.eof())
	    return p; 
	
	//�ڶ��� 
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
	
	//����,�汲�ĵĺ��� 
	for(auto i=a.begin(); i!=a.end(); i++)
	{
		(*i)->flag = 0;
		if((*i)->name == "0")continue;
		if( !nochild(p) )
		{
			//���ֵܹ�ϵ 
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
	 
	//���漸�� 
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
	    
	    //ָ���ֵܹ�ϵ���������ֵ� 
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
				    
					//���ֵܹ�ϵ,������Ҫ��ô���� 
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
  - ���ڸ���������ӳ�Ա
  - ����������Ҫ��ӳ�Ա������
  - �������ӵĳ�Ա�ͼ������е�ĳ����Աͬ���������¸�����ӳ�Ա���� 
  - ����������CreateFamilyTree()��resetTreeFlag()��nochild()  
*/ 
void addMember(Person *t)
{
	//fflush(stdin);
	//Person *temp = new Person;
	cout<<"������Ҫ��ӵĳ�Ա��������"; 
	Person *temp = CreateFamilyTree();
	
	//ͬ��ͬ�տ���
	while( searchPerson(temp->name) )
	{
		resetTreeFlag(root); 
	    cout<<"������Ѿ����ڣ�����������Ҫ��ӵĳ�Ա��������";
		temp = CreateFamilyTree();
	}
	resetTreeFlag(root);  
	
	temp->father = t;
	//˫���к���,�����ֵܹ�ϵ 
	if( !nochild(t))
	{
		//ָ�����ֵܹ�ϵ 
		for(auto v:t->child)
		{
			v->brother.push_back(temp);
			temp->brother.push_back(v);
		}
	}
	
	//ָ�ñ��ֵܹ�ϵ	
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
		
	
	//ʵ��2�������� 
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


//��������˵ĺ���(����еĻ�)�����Һ���û����ѯ��
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


//�����ж�ĳ�����Ƿ��к�� 
bool nochild(Person *s)
{
    if(s->child.empty())
	    return 1;
	else
	    return 0;	
} 


/* 
 - �����ж�����˵����к����Ƿ񶼱���� 
 - ����û������ľͷ��ؼ٣������������û�к��Ӿͷ�����  
*/ 
bool allchildhassearch(Person *s)
{
	if(s->child.empty())
	    return 1;
    else
    {
    	for(auto t=s->child.begin(); t!= s->child.end(); t++)
	    {    
		    //����û����� 
		    if( (*t)->flag==0 )
		        return 0;
	    }
	}
	return 1;	
}


/*
  - �������������ݴ�����������������������������Ա�ͷ��������Ա��Ӧ��Person*���͵Ľ��
  - ����������hasChildhasoneNoSearch()��nochild()��allchildhassearch() 
*/
Person* searchPerson(string na)
{
	Person *s=root,*temp;
	
	if(s->name == na)
	    return s;//���Ȳ��� 
	else
	{
		while(!allchildhassearch(s))//û�ҵ��ˣ�����s�ĺ��Ӳ�δ������� 
		{
		    //temp = s;//ÿ�ζ������ȿ�ʼ 
		    temp = hasChildhasoneNoSearch(s);//��������temp�ĺ��ӣ����ࣩܺܶ���������û����� 
		    while(temp)//temp��Ϊ�� 
		    {
		    	if(temp->name == na)
		    	    return temp;
		    	else
		    	{
		    		//û�к��ӻ������к��Ӷ����ҹ� 
		    		if( nochild(temp) || allchildhassearch(temp) )//all���������ж��������к����Ƿ񶼱����� 
					    temp->flag = 1;//��ǲ��
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
  - ���ü���������ʵ�ּ�����searchPerson��������flag��Ա 
  - ������ÿ������һ�ξ���Ҫ��������������������� 
*/ 
void resetTreeFlag(Person *t)
{
    if(nochild(t))
	{
	    t->flag = 0;
		return ;	
	}
	else//�к��� 
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
 - ���ڼ�������������ȡ��������Ǹ��˵ĺ�����Ŀ����������浵��ʵ��(saveToFile����)
 - ����������resetTreeFlag()��hasChildhasoneNoSearch()��allchildhassearch()��nochild() 
*/ 
int searchTheMostNum()
{
	Person *s = root;
	Person *temp;
	int max_num = s->child.size();//Ĭ��Ϊ���ȵĺ����� 
	
	do
	{
		//cout<<"\n1 ";
		//temp = s;//ÿ�δ����ȿ�ʼ 
	    temp = hasChildhasoneNoSearch(root);
	    while(temp)//temp��Ϊ�� 
		{
		    //cout<<"\n1 ";
		    if(temp->child.size() > max_num)
		        max_num = temp->child.size();
			if( nochild(temp) || allchildhassearch(temp) )//all���������ж��������к����Ƿ񶼱����� 
				temp->flag = 1;//��ǲ�� 
			else
				temp->flag = 0;
			temp = hasChildhasoneNoSearch(temp);
		}
	}while( !allchildhassearch(root));
	return max_num;	
}

