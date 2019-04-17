

Person* readFromFile()
{
	Person *root=new Person;
	string name;
	int num;
	
	ifstream infile("family.txt",ios::in);
	
	infile>>name;
	infile>>num;
	
	root->name = name;
	int count = 0;
	//其他赋值为空 
	while( !infile.eof() && count!=num)//给祖先加孩子 
	{
		Person *p = new Person;
		//其他赋为空 
		infile>>name;
		p->name = name;
		root->child.push_back(p);
		count++;
	}
	
	//此处建立第二层的兄弟关系
	
	Person *temp = root->child[0];
	int count = 0;
	while(!infile.eof() && count !=num)//给长子加孩子 
	{
	   	Person *p = new Person;
		infile>>name;
		p->name = name;
		temp->child.push_back(p);
		count++;
	} 
	
	
	if( !infile.eof() )
	    Person *q = temp;//方便下下个循环使用 
	    while( !infile.eof() && haveBrother(temp) && count != num  )
	    { 
		    temp = temp->brother;//去除vector属性 
		    Person *p = new Person;
		    infile>>name;
		    p->name = name;
		    temp->child.push_back(p);
		    count++;
	    }
	
	//没有brother，且文件没到末尾
	//建立第三层兄弟关系
	if
	    temp_1 = q;
	    while
	    {
	    	temp_1 = temp_1->brother;
		}
	
	 
	
}
