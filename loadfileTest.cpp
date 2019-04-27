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

Person* loadFromFile()
{
	ifstream infile("family.txt",ios::in);
	int num;
	string name;
	vector<Person*> a,b;
	
	infile>>name;
	infile>>num;
    
    //���Ƚ�� 
    Person *p = new Person;	
	p->name = name;
	p->flag = 0;
	p->father = NULL;
	for(auto v:p->brother)
	    v=NULL;
	//������ֵΪ�� 
	
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
		//����Ϊ�� 
		a.push_back(q);
		count++; 
	}
	
	/*
	for(auto i=a.begin(); i!=a.end(); i++)
	{
		cout<<(*i)->name<<endl;
	}
	*/
	
	//�������ڶ��� 
	for(auto i=a.begin(); i!=a.end(); i++)
	{
		p->child.push_back(*i);
	}
	
	i = i+1;
	
	//������ 
	int co=0;
	while( !infile.eof() && co != pow(num,i-1) )
	{
		infile>>name;
		Person *q = new Person;	
	    q->name = name;
		//��������
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
	
	//���漸�� 
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
		    //��������
		    
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
