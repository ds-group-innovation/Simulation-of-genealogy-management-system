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
