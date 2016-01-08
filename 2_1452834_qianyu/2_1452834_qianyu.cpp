#include <iostream>
#include <algorithm>

using namespace std;


//Person类	
class Person{
	
friend class System;

private:
	int id;
	bool isAlive;

	Person *next;			//next指针
	Person *newNext;		//用于约瑟夫环从操作的next指针

public:
	//构造函数
	Person(){

		id = 0;
		isAlive = true;

		next = NULL;
		newNext = NULL;
	}

	~Person(){

	}

	//静态的Create方法
	static Person* Create(){

		Person *person = new Person();

		return person;
	}
};

//System类
class System{

private:
	int length;			//总人数
	int position;		//起始位置
	int step;			//间隔
	int left;			//剩余生者人数

	Person *child;		//用于链表存储

public:
	//构造函数
	System(){

	}
	
	//开始方法
	void start();

	//初始化方法
	void initial();

	//数据的Set方法
	void set();

	//主过程方法
	void work();

	//释放空间方法
	void finish();
};

void System::start(){

	initial();

	set();
}

void System::initial(){

	cout << "现有N个人围成一圈，从第S个人开始依次报数，报M的人出局，再由下一人开始报数，如此循环，直到剩下N人为止" << endl << endl;

	length = position = step = left = 0;
}

void System::set(){

	child = Person::Create();

	bool flag = true;

	do{
		flag = true;

		cout << "请输入生死游戏的总人数N：    ";
		cin >> length;

		if (length<1){

			cout << "总人数应大于1，请重新输入！" << endl;

			flag = false;
		}
	} while (!flag);

	do{
		flag = true;

		cout << "请输入游戏开始的位置：       ";
		cin >> position;

		if (position<1 || position>length){

			cout << "开始位置应大于0并且小于等于" << length << ",请重新输入！" << endl;

			flag = false;
		}
	} while (!flag);

	do{
		flag = true;

		cout << "请输入死亡数字M：            ";
		cin >> step;

		if (step <= 0){

			cout << "死亡数字应为正整数，请重新输入！" << endl;

			flag = false;
		}
	} while (!flag);
	
	do{
		flag = true;
		cout << "请输出剩余的生者人数K：      ";
		cin >> left;

		if (left<0 || left>length){

			cout << "剩余生者人数应大于等于0，并小于等于" << length << ",请重新输入！" << endl;
		}
	} while (!flag);
	
	Person *now = child;
	now->id = 1;

	Person *person;

	for (int i = 2; i <= length; i++){

		person = Person::Create();

		now->newNext = now->next = person;

		now = now->next;

		now->id = i;
	}

	person->next = person->newNext = child;

	work();
}

void System::work(){

	cout << endl;

	Person *now = child;

	int num = length;

	for (; num > left; num--){

		for (int i = 2; i < step; i++){

			now = now->newNext;
		}

		cout << "第" << length - num + 1 << "个死者的位置是\t" << now->newNext->id << endl;

		now->newNext->isAlive = false;

		now->newNext = now->newNext->newNext;

		now = now->newNext;
	}

	cout << endl << "最后剩下：        " << left << "人" << endl;
	cout << "剩余生者的位置为：";
	
	now = child;
	
	while (!now->isAlive){

		now = now->next;
	}

	for (int i = 0; i < left; i++){

		cout << "\t" << now->id;

		now = now->newNext;
	}

	cout << endl;

	finish();
}

void System::finish(){

	Person *now = child;

	for (int i = 1; i < length; i++){

		Person *tmp = now;

		now = now->next;

		delete(tmp);
	}

	delete(now);
}

int main(){

	System *system = new System();

	system->start();

	return 0;
}