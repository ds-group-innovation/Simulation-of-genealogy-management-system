#ifndef FAMILY
#define FAMILY

#include<iostream>
#include<vector>
#include<fstream>
#include<cmath>
//#include<windows.h>����select��ͻ 
using namespace std;


/*
 - �������ṹ�� 
 - ������vectorʵ�ֶ������ṹ 
*/ 
class Person{
	public:
		string name;                          // ���� 
		//char sex;
		int flag;                             //������־��û�б��ҹ�,0û�ҹ� 
	public:
		Person *father;                       // ˫�� 
        vector<Person*> brother;		      // �ֵ� 
        vector<Person*> child;                // ���� 
};


/*
  - ȫ�ֱ���
    - root: ���� 
    - select: ���ڲ˵�ѡ�� 
*/ 
Person *root;
int select;

#endif
