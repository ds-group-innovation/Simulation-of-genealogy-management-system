#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>

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
        vector<Person*> child;                 // ���� 
};

//ȫ�ֱ��� 
Person *root;
int select;


Person* CreateFamilyTree()//����ģ�� 
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

void mainMenu();
bool nochild(Person *s);
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

bool nochild(Person*);
//��ӳ�Ա������˫��ָ�룬���һ�����ӣ�����һϵ���� 
Person* searchPerson(string na);
void resetTreeFlag(Person *t);
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
		    //����û����� 
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

//����flag
void resetTreeFlag(	Person *t)
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

//�������ĺ��� 
int searchTheMostNum()
{
	Person *s = root;
	Person *temp;
	int max_num = s->child.size();//
	
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

void subMenuCreate();
void subMenuGetMessage();
void mainMenu()
{
	system("cls"); 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         ����1 ��������                            "<<endl;
	cout<<"                         ����2 ��ȡ��Ա��Ϣ                        "<<endl;
	cout<<"                         ����3 �浵                                "<<endl;
	cout<<"                         ����0 �˳�����                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
	
	cin>>select;
	
	switch(select)
	{
		case 1:subMenuCreate();break;
		case 2:subMenuGetMessage();break;
		case 3:cout<<"�˴�����δ����!";system("pause");mainMenu();break; 
		case 0:exit(0); 
	}
}


void subMenuAddMember();
void subMenuGetMessage();
void subMenu()
{
	system("cls");
    cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         ����1 �������˵�                          "<<endl;
	cout<<"                         ����2 ��ӳ�Ա                            "<<endl;
	cout<<"                         ����3 ��ȡ������Ա��Ϣ                    "<<endl;
	cout<<"                         ����0 �˳�����                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
	
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


void hisFather(Person *p);
void hisBrother(Person *p);
void hisChild(Person *p);
void hisAllMessage(Person *p);
void hisAncestor(Person *p);
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
	cout<<"                         ����1 ��ʾ����˫�׵�����                  "<<endl;
	cout<<"                         ����2 ��ʾ���ĺ��������                  "<<endl;
	cout<<"                         ����3 ��ʾ���������ֵܵ�����              "<<endl;
	cout<<"                         ����4 ��ʾ����ʼ�������                  "<<endl;
	cout<<"                         ����5 ��ʾ����������Ϣ                    "<<endl; 
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
			cout<<"������Ҫ���������ӵĺ����������";
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
			cout<<"����˲����ڣ����������룺";
		}
		resetTreeFlag(root);
    }
     
	//mainMenu(); 	
    subMenu();
}

//-----------------------------------------
//������Ϣչʾ 
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

int main()
{
	//root = CreateFamilyTree();
	
	mainMenu(); 
	
	cout<<root->name;
	return 0;
}
