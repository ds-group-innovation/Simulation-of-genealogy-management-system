Person* searchPerson(string na)
{
	Person *s=root,temp;
	
	if(s->name == na)return s;//���Ȳ��� 
	else{
		while(s->name != na)
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
				    temp = temp = hasChildhesoneNoSearch(temp); 
		    	} 
			}
	    }	 
	}
	// return s;
}

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
