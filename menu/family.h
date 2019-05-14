#ifndef FAMILY
#define FAMILY

#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>
//#include<windows.h>会与select冲突 
using namespace std;


/*
 - 家谱树结构体 
 - 由容器vector实现多叉链表结构 
*/ 
class Person{
	public:
		string name;                          // 姓名 
		//char sex;
		int flag;                             //用来标志有没有被找过,0没找过 
	public:
		Person *father;                       // 双亲 
        vector<Person*> brother;		      // 兄弟 
        vector<Person*> child;                // 孩子 
};


/*
  - 全局变量
    - root: 族谱 
    - select: 用于菜单选择 
*/ 
Person *root;
int select;

#endif
