
class Person{
	public:
	    string name;        //姓名 
	    char sex;           //性别 
		int generation;     //当前第几代
	public:       
		Person *parent;     //老豆 
		Person *brother;    //弟弟 
		Person *child;      //孩子 
};

Person *root; //祖先 


