Person* loadFromFile()
{
	ifstream infile("family.txt",ios::in);
	int num;
	string name;
	vector<Person*> a,b;
	
	infile>>name;
	infile>>num;

    Person *root = new Person;	
	root->name = name;
	root->flag = 0;
	//������ֵΪ�� 
	
	int count = 0;
	
	while( !infile.eof() && count != num )
	{
	    infile>>name;
		Person *p = new Person;	
	    p->name = name;
		//��������
		a.push_back(p);
		count++; 
	}
	
	//��װΪnimei 
	int co;
	while( !infile.eof() && co != pow(num,i-1) )
	{
		infile>>name;
		Person *p = new Person;	
	    p->name = name;
		//��������
		b.push_back(p);
		co++;
	}
	
	//��ʼ���,������Է�װΪһ������,shepi 
	for(auto v=a.begin(); v!=a.end(); v++)
	{
		int count = 0;
		for(auto s=b.begin(); v!=b.end(); v++)
		{
			if count!=num
			     count++;
				 (*v)->child.push_back(*s);
			else
			     b = s;//��֪���в��� 
			     break;
		}
	}
	clear b;
	a = b;
	//
	
	
	while(!infile.eof())
	{
	    nimei();
		shepi(a,b);	
	}

	
   
} 
