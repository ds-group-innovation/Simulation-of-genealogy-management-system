Person* loadFromFile()
{
	ifstream infile("family.txt",ios::in);
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
		q->father = NULL;
		q->flag = 0;
	    for(auto v:q->brother)
	        v=NULL;
		//����Ϊ�� 
		a.push_back(q);
		count++; 
	}
	
	//����,�汲�ĵĺ��� 
	for(auto i=a.begin(); i!=a.end(); i++)
	{
		//p->flag = 0;
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
		    //��������
		    q->flag = 0;
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
				    (*v)->child.push_back(*s);
			
			    }
			    else
			    {
				    vector<Person*>::iterator it;
                    it = temp->begin()+count;
                    //p->flag = 0;
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
