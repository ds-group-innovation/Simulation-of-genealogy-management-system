Person* searchPerson(string na)
{
	Person *s=root,temp;
	
	if(s->name == na)return s;//祖先不是 
	else{
		while(s->name != na)
		{
		    temp = s;//每次都从祖先开始 
		    temp = hasChildhasoneNoSearch(temp);//返回temp的孩子（可能很多），这个孩子没被查过 
		    while(temp)//temp不为空 
		    {
		    	if(temp->name == na)
		    	    return temp;
		    	else
		    	{
		    		//没有孩子或者所有孩子都被找过 
		    		if( nochild(temp) || allchildhassearch(temp) )//all函数用来判断他的所有孩子是否都被查了 
					    temp->flag = 1;//标记查过 
					else
					    temp->flag = 0; 
				    temp = temp = hasChildhesoneNoSearch(temp); 
		    	} 
			}
	    }	 
	}
	// return s;
}

//返回这个人的孩子(如果有的话)，而且孩子没被查询过
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
