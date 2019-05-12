//存档实现
//判断这个数组成员是否都为零成员 
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
    
    //祖先没孩子，结束 
    if(r->child.empty())
    {
    	out.close(); 
    	return ;
	} 
    //第二层 
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
    
    //如果a的孩子都不是0
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
		//放完一层了 
		out<<endl;
		a.clear();
		a.assign(b.begin(),b.end()); 
		b.clear(); 
	}
	
    out.close();
} 
