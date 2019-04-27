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
        vector<Person*> child;                 // ���� 
};

//Person *root;
Person *root;

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

bool nochild(Person*);
//��ӳ�Ա������˫��ָ�룬���һ�����ӣ�����һϵ���� 
void addMember(Person *t)
{
	//fflush(stdin);
	//Person *temp = new Person;
	Person *temp = CreateFamilyTree();
	temp->father = t;
	//˫���к���,�����ֵܹ�ϵ 
	if( !nochild(t))
	{
		for(auto v:t->brother)
		{
			v->brother.push_back(temp);
			temp->brother.push_back(v);
		}
	}

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
void resetTreeFlag(Person *t=root)
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


int main()
{
	return 0;
}
