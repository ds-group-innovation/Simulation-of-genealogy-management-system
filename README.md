# 简易家谱管理系统模拟

基于 Win 控制台的简易家谱管理系统，支持基本的增删改查，「查」不支持模糊搜索。使用 CPP vector 扩展树结构。家谱可从文件中读取，也可建立后存放到文件中。

```c++
/*
  - author：叶汕、莫小荷、刘津睿
  - url：https://github.com/ds-group-innovation/Simulation-of-genealogy-management-system
  - copyright：2019 yeshan <yeshan1329441308@gmail.com>
  - license：MIT, see LICENSE for more details.
  - version：v3.0
  - contact me：1329441308@qq.com
  - remember：代码辣鸡非我意，谈笑风声活长命
*/

//c++11标准编译：-std=c++11（Dev-C++5.11）

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
```
