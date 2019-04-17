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
	//其他赋值为空 
	
	int count = 0;
	
	while( !infile.eof() && count != num )
	{
	    infile>>name;
		Person *p = new Person;	
	    p->name = name;
		//其他赋空
		a.push_back(p);
		count++; 
	}
	
	//封装为nimei 
	int co;
	while( !infile.eof() && co != pow(num,i-1) )
	{
		infile>>name;
		Person *p = new Person;	
	    p->name = name;
		//其他赋空
		b.push_back(p);
		co++;
	}
	
	//开始互怼,这里可以封装为一个函数,shepi 
	for(auto v=a.begin(); v!=a.end(); v++)
	{
		int count = 0;
		for(auto s=b.begin(); v!=b.end(); v++)
		{
			if count!=num
			     count++;
				 (*v)->child.push_back(*s);
			else
			     b = s;//不知道行不行 
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
