#include"family.h"
#include"declare.h" 
//#include"function.cpp"
using namespace std;


void mainMenu()
{
	system("cls"); 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         ����1 ��������                            "<<endl;
	cout<<"                         ����2 ��ȡ��Ա��Ϣ                        "<<endl;
	cout<<"                         ����3 �浵�˳�                            "<<endl;
	cout<<"                         ����4 ��ʾ����                            "<<endl;
	cout<<"                         ����5 ��ӳ�Ա                            "<<endl;
	cout<<"                         ����0 �˳�����                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
	
	cin>>select;
	
	switch(select)
	{
		case 1:subMenuCreate();break;
		case 2:subMenuGetMessage();break;
		case 3:
		    if(root==NULL)
			    cout<<"��������δ���������Ƚ�����";
			else
			{
				saveToFile();
			    cout<<"�浵�ɹ�!"<<endl;
			}
			system("pause");
			exit(0);//cout<<"�˴�����δ����!";system("pause");mainMenu();break; 
		    break;
		case 4:
		    if(root==NULL)
			    cout<<"��������δ���������Ƚ�����";
			else
			    showTheFamilyTree();
			system("pause");
			break;
		case 5:
		    if(root==NULL)
			    cout<<"��������δ���������Ƚ�����";
		    else
			    subMenuAddMember();
			system("pause");
			break; 
		case 0:exit(0);break;
		//default: mainMenu();
	}
	mainMenu();
}


void subMenu()
{
	system("cls");
    cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         ����1 �������˵�                          "<<endl;
	cout<<"                         ����2 ��ӳ�Ա                            "<<endl;
	cout<<"                         ����3 ��ȡ������Ա��Ϣ                    "<<endl;
	cout<<"                         ����4 ��ʾ����                            "<<endl;
	cout<<"                         ����0 �˳�����                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
	
	cin>>select;
	
	switch(select)
	{
		case 1:mainMenu();break;
		case 2:subMenuAddMember();break;
		case 3:subMenuGetMessage();break;
		case 4:showTheFamilyTree();system("pause");break; 
	    case 0:exit(0);break;
	    default: subMenu();
	}	
}


void subMenuCreate()
{
	system("cls");
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         ����1 ����������                          "<<endl;
	cout<<"                         ����2 ���ļ��л�ȡ��������                "<<endl;
	cout<<"                         ����0 �˳�����                            "<<endl; 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
	
	cin>>select;
	
	switch(select)
	{
		case 1:cout<<"������ʼ������:\n";root=CreateFamilyTree();break;
		case 2:root=loadFromFile();if(root)cout<<"�����ɹ�";system("pause");break; 
	    case 0:exit(0);
	}
	//mainMenu();
	subMenu();
}


void subMenuGetMessage()
{
	if(root==NULL)
    {
    	cout<<"���ȴ������ף�";
    	system("pause");
    	mainMenu(); 
	}
	string name;
	Person *p; 
	cout<<"����������Ҫ�˽��ĳ���˵�������";
	while(true)
	{
		cin>>name;
		if(p=searchPerson(name))
		{
			resetTreeFlag(root);
		    break;	
		}
		else
		{
			resetTreeFlag(root);
			cout<<"����˲��������У���������������Ҫ�˽���Ǹ��˵�������";
		}
	}
	
    system("cls");
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         ����1     ��ʾ����˫�׵�����              "<<endl;
	cout<<"                         ����2     ��ʾ���ĺ��������              "<<endl;
	cout<<"                         ����3     ��ʾ���������ֵܵ�����          "<<endl;
	cout<<"                         ����4     ��ʾ����ʼ�������              "<<endl;
	cout<<"                         ����5     ��ʾ����������Ϣ                "<<endl;
	cout<<"                         ��������  ������һ��˵�                  "<<endl; 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"��ѡ������Ҫ���еĲ�����";
	
	cin>>select;
	switch(select)
	{
	    case 1:hisFather(p);break;
		case 2:hisChild(p);break;
		case 3:hisBrother(p);break;
		case 4:hisAncestor(p);break;
		case 5:hisAllMessage(p);break;
		default: subMenu(); 
	}
	subMenu();   	
}


void subMenuAddMember()
{
	string name;
    cout<<"����������Ҫ��Ӻ�����Ǹ���Ա��������";
	Person *temp;
	while(true)
	{
		cin>>name;
    	if( temp=searchPerson(name) )
    	{
    		resetTreeFlag(root);
    		int num;
			cout<<"������Ҫ���������ӵĺ��������������1-999����";
			//while(cin.fail()) 
		    cin>>num;
			 
            //int s=cin.rdstate();//�ж�������״̬ 
            /*
			while(num<0||num>999)
            {
            	//cin.clear(); 
            	cout<<"������Ĳ���������������һ��������"; 
            	cin>>num;
            	//s = cin.rdstate();
			}
			*/
            
			for(int i=0;i<num;i++)
			{
				addMember(temp);
				cout<<endl;
			}		
		    break;
		}
		else
		{ 
			cout<<"����˲����ڣ����������룺";
		}
		resetTreeFlag(root);
    }
     
	//mainMenu(); 	
    subMenu();
}

int main()
{
	mainMenu(); 
	//cout<<"�ҷ��ˣ�"; 
	return 0;
}

