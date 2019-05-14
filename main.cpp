/*
  - author��Ҷ�ǡ�ĪС�ɡ������
  - url��https://github.com/ds-group-innovation/Simulation-of-genealogy-management-system
  - copyright��2019 yeshan <yeshan1329441308@gmail.com>
  - license��MIT, see LICENSE for more details.
  - version��v3.0 
  - contact me��1329441308@qq.com
  - remember���������������⣬̸Ц�������  
*/

//c++11��׼���룺-std=c++11��Dev-C++5.11��
 
#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>
//#include<windows.h>����select��ͻ 
using namespace std;


/*
 - �������ṹ�� 
 - ������vectorʵ�ֶ������ṹ 
*/ 
class Person{
	public:
		string name;                          // ���� 
		//char sex;
		int flag;                             //������־��û�б��ҹ�,0û�ҹ� 
	public:
		Person *father;                       // ˫�� 
        vector<Person*> brother;		      // �ֵ� 
        vector<Person*> child;                // ���� 
};


/*
  - ȫ�ֱ���
    - root: ���� 
    - select: ���ڲ˵�ѡ�� 
*/ 
Person *root;
int select;


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

 
void mainMenu()
{
	system("cls"); 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         ����1 ��������                            "<<endl;
	cout<<"                         ����2 ��ȡ��Ա��Ϣ                        "<<endl;
	cout<<"                         ����3 �浵�˳�                            "<<endl;
	cout<<"                         ����4 ��ʾ����                            "<<endl;
	cout<<"                         ����5 ��ӳ�Ա                            "<<endl;
	cout<<"                         ����0 �˳�����                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
	
	cin>>select;
	
	switch(select)
	{
		case 1:subMenuCreate();break;
		case 2:subMenuGetMessage();break;
		case 3:
		    if(root==NULL)
			    cout<<"��������δ���������Ƚ�����";
			else
			{
				saveToFile();
			    cout<<"�浵�ɹ�!"<<endl;
			}
			system("pause");
			exit(0);//cout<<"�˴�����δ����!";system("pause");mainMenu();break; 
		    break;
		case 4:
		    if(root==NULL)
			    cout<<"��������δ���������Ƚ�����";
			else
			    showTheFamilyTree();
			system("pause");
			break;
		case 5:
		    if(root==NULL)
			    cout<<"��������δ���������Ƚ�����";
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
	cout<<"                         ����1 �������˵�                          "<<endl;
	cout<<"                         ����2 ��ӳ�Ա                            "<<endl;
	cout<<"                         ����3 ��ȡ������Ա��Ϣ                    "<<endl;
	cout<<"                         ����4 ��ʾ����                            "<<endl;
	cout<<"                         ����0 �˳�����                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
	
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
	cout<<"                         ����1 ����������                          "<<endl;
	cout<<"                         ����2 ���ļ��л�ȡ��������                "<<endl;
	cout<<"                         ����0 �˳�����                            "<<endl; 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
	
	cin>>select;
	
	switch(select)
	{
		case 1:cout<<"������ʼ������:\n";root=CreateFamilyTree();break;
		case 2:root=loadFromFile();if(root)cout<<"�����ɹ�";system("pause");break; 
	    case 0:exit(0);
	}
	//mainMenu();
	subMenu();
}


void subMenuGetMessage()
{
	if(root==NULL)
    {
    	cout<<"���ȴ������ף�";
    	system("pause");
    	mainMenu(); 
	}
	string name;
	Person *p; 
	cout<<"����������Ҫ�˽��ĳ���˵�������";
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
			cout<<"����˲��������У���������������Ҫ�˽���Ǹ��˵�������";
		}
	}
	
    system("cls");
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         ����1     ��ʾ����˫�׵�����              "<<endl;
	cout<<"                         ����2     ��ʾ���ĺ��������              "<<endl;
	cout<<"                         ����3     ��ʾ���������ֵܵ�����          "<<endl;
	cout<<"                         ����4     ��ʾ����ʼ�������              "<<endl;
	cout<<"                         ����5     ��ʾ����������Ϣ                "<<endl;
	cout<<"                         ��������  ������һ��˵�                  "<<endl; 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
	
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
    cout<<"����������Ҫ��Ӻ�����Ǹ���Ա��������";
	Person *temp;
	while(true)
	{
		cin>>name;
    	if( temp=searchPerson(name) )
    	{
    		resetTreeFlag(root);
    		int num;
			cout<<"������Ҫ���������ӵĺ��������������1-999����";
			//while(cin.fail()) 
		    cin>>num;
			 
            //int s=cin.rdstate();//�ж�������״̬ 
            /*
			while(num<0||num>999)
            {
            	//cin.clear(); 
            	cout<<"������Ĳ���������������һ��������"; 
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
			cout<<"����˲����ڣ����������룺";
		}
		resetTreeFlag(root);
    }
     
	//mainMenu(); 	
    subMenu();
}

//-----------------------------------------
//������Ϣչʾ 

//���� 
void hisAncestor(Person* p)
{
    if(p->name == root->name)
    {
    	cout<<"����˾���ʼ��<<endl";
    	system("pause");
	}
	else
	{
		cout<<"����˵�ʼ�������ǣ�"; 
		cout<<root->name<<endl;
	}
} 

//˫�� 
void hisFather(Person *p)
{
	if(!p->father)
	{
		cout<<"�����û��˫��"<<endl;
		system("pause");
	}
	else
	{
		cout<<"����˵�˫�׵������ǣ�";
		cout<<p->father->name<<endl;
		system("pause");
	}
    subMenu();
}

//�ֵܣ��������ֵ� 
void hisBrother(Person *p)
{
	int n;
	n = p->brother.size();
	if(n)
	{
	    cout<<"������� "<<n<<" ���ֵ�,�ֱ��ǣ�\n";
		for(auto v:p->brother)
		    cout<<v->name<<" ";
		cout<<endl;
		system("pause");	
	}
	else
	{
		cout<<"�����û���ֵ�"<<endl;
		system("pause");
	}
	subMenu();
}

//��� 
void hisChild(Person *p)
{
	int n;
	n = p->child.size();
	if(n)
	{
	    cout<<"������� "<<n<<" ������,�ֱ��ǣ�\n";
		for(auto v:p->child)
		    cout<<v->name<<" ";
		cout<<endl;
		system("pause");	
	}
	else
	{
		cout<<"�����û�к��"<<endl;
		system("pause");
	}
	subMenu();
}

//�������������Ϣ 
void hisAllMessage(Person *p)
{
	cout<<endl;
	if(p->name == root->name)
	{
		cout<<"���������������ʼ��"<<endl; 
	}
	else
	{
		cout<<"����˵�ʼ���ǣ�"<<root->name<<endl;
	}
	
	
	cout<<endl;
	if(p->father)
	{
		cout<<"����˵�˫���ǣ�"<<p->father->name<<endl;
	}
	else
	{
		cout<<"�����û��˫��"<<endl; 
	}
	
	
	cout<<endl;
	if(p->child.size())
	{
		cout<<"�������"<<p->child.size()<<"������,�ֱ��ǣ�"<<endl;
		for(auto v:p->child)
		    cout<<v->name<<" ";
		cout<<endl; 
	}
	else
	{
		cout<<"�����û�к��!"<<endl;
	}
	
	
	cout<<endl;
	if(p->brother.size())
	{
		cout<<"�������"<<p->brother.size()<<"���ֵ�,�ֱ��ǣ�"<<endl;
		for(auto v:p->brother)
		    cout<<v->name<<" ";
		cout<<endl; 
	}
	else
	{
		cout<<"�����û���ֵ�!"<<endl;
	}
	
	system("pause");
}

//�ж���������Ա�Ƿ�Ϊ���Ա�������浵����ѭ����ʵ�� 
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
  - �������浵
  - ����������allIsZero() 
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
    
    //����û���ӣ����� 
    if(r->child.empty())
    {
    	out.close(); 
    	return ;
	} 
    //�ڶ��� 
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
    
    //���a�ĺ��Ӷ�����0
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
		//����һ���� 
		out<<endl;
		a.clear();
		a.assign(b.begin(),b.end()); 
		b.clear(); 
	}
	
    out.close();
    //exit(0); 
}


/*
  - ��ʾ������
  - ����������allIsZero() 
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
    
    //����û���ӣ����� 
    if(r->child.empty())
    { 
    	return ;
	} 
    //�ڶ��� 
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
    
    //���a�ĺ��Ӷ�����0
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
				//ֻ��ӡһ��0�����㿴 
				cout<<"0 ";
				cout<<") "; 
			}
			else if(nochild(q))//û�к��� 
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
		//��ʾ��һ���� 
		cout<<endl;
		a.clear();
		a.assign(b.begin(),b.end()); 
		b.clear(); 
	}
}


int main()
{
	mainMenu(); 
	//cout<<"�ҷ��ˣ�"; 
	return 0;
}
