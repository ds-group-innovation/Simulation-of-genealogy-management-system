#include"family.h"
#include"declare.h" 
//#include"function.cpp"
using namespace std;


void mainMenu()
{
	system("cls"); 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         输入1 创建族谱                            "<<endl;
	cout<<"                         输入2 获取族员信息                        "<<endl;
	cout<<"                         输入3 存档退出                            "<<endl;
	cout<<"                         输入4 显示族谱                            "<<endl;
	cout<<"                         输入5 添加成员                            "<<endl;
	cout<<"                         输入0 退出程序                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	
	cin>>select;
	
	switch(select)
	{
		case 1:subMenuCreate();break;
		case 2:subMenuGetMessage();break;
		case 3:
		    if(root==NULL)
			    cout<<"家谱树还未建立，请先建树！";
			else
			{
				saveToFile();
			    cout<<"存档成功!"<<endl;
			}
			system("pause");
			exit(0);//cout<<"此处功能未完善!";system("pause");mainMenu();break; 
		    break;
		case 4:
		    if(root==NULL)
			    cout<<"家谱树还未建立，请先建树！";
			else
			    showTheFamilyTree();
			system("pause");
			break;
		case 5:
		    if(root==NULL)
			    cout<<"家谱树还未建立，请先建树！";
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
	cout<<"                         输入1 返回主菜单                          "<<endl;
	cout<<"                         输入2 添加成员                            "<<endl;
	cout<<"                         输入3 获取已有族员信息                    "<<endl;
	cout<<"                         输入4 显示族谱                            "<<endl;
	cout<<"                         输入0 退出程序                            "<<endl;
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	
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
	cout<<"                         输入1 创建新族谱                          "<<endl;
	cout<<"                         输入2 从文件中获取已有族谱                "<<endl;
	cout<<"                         输入0 退出程序                            "<<endl; 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	
	cin>>select;
	
	switch(select)
	{
		case 1:cout<<"请输入始祖姓名:\n";root=CreateFamilyTree();break;
		case 2:root=loadFromFile();if(root)cout<<"创建成功";system("pause");break; 
	    case 0:exit(0);
	}
	//mainMenu();
	subMenu();
}


void subMenuGetMessage()
{
	if(root==NULL)
    {
    	cout<<"请先创建族谱！";
    	system("pause");
    	mainMenu(); 
	}
	string name;
	Person *p; 
	cout<<"请输入你想要了解的某个人的姓名：";
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
			cout<<"这个人不再族谱中，请重新输入你想要了解的那个人的姓名：";
		}
	}
	
    system("cls");
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"                         输入1     显示他的双亲的姓名              "<<endl;
	cout<<"                         输入2     显示他的后代的姓名              "<<endl;
	cout<<"                         输入3     显示他的所有兄弟的姓名          "<<endl;
	cout<<"                         输入4     显示他的始祖的姓名              "<<endl;
	cout<<"                         输入5     显示他的所有信息                "<<endl;
	cout<<"                         输入其它  返回上一层菜单                  "<<endl; 
	cout<<"-------------------------------------------------------------------"<<endl;
	cout<<"请选择您想要进行的操作：";
	
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
    cout<<"请输入你想要添加后代的那个族员的姓名：";
	Person *temp;
	while(true)
	{
		cin>>name;
    	if( temp=searchPerson(name) )
    	{
    		resetTreeFlag(root);
    		int num;
			cout<<"请输入要给这个人添加的后代的数量（整数1-999）：";
			//while(cin.fail()) 
		    cin>>num;
			 
            //int s=cin.rdstate();//判断流输入状态 
            /*
			while(num<0||num>999)
            {
            	//cin.clear(); 
            	cout<<"您输入的不是整数，请输入一个整数："; 
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
			cout<<"这个人不存在，请重新输入：";
		}
		resetTreeFlag(root);
    }
     
	//mainMenu(); 	
    subMenu();
}

int main()
{
	mainMenu(); 
	//cout<<"我佛了！"; 
	return 0;
}

