

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
	//������ֵΪ�� 
	while( !infile.eof() && count!=num)//�����ȼӺ��� 
	{
		Person *p = new Person;
		//������Ϊ�� 
		infile>>name;
		p->name = name;
		root->child.push_back(p);
		count++;
	}
	
	//�˴������ڶ�����ֵܹ�ϵ
	
	Person *temp = root->child[0];
	int count = 0;
	while(!infile.eof() && count !=num)//�����ӼӺ��� 
	{
	   	Person *p = new Person;
		infile>>name;
		p->name = name;
		temp->child.push_back(p);
		count++;
	} 
	
	
	if( !infile.eof() )
	    Person *q = temp;//�������¸�ѭ��ʹ�� 
	    while( !infile.eof() && haveBrother(temp) && count != num  )
	    { 
		    temp = temp->brother;//ȥ��vector���� 
		    Person *p = new Person;
		    infile>>name;
		    p->name = name;
		    temp->child.push_back(p);
		    count++;
	    }
	
	//û��brother�����ļ�û��ĩβ
	//�����������ֵܹ�ϵ
	if
	    temp_1 = q;
	    while
	    {
	    	temp_1 = temp_1->brother;
		}
	
	 
	
}
