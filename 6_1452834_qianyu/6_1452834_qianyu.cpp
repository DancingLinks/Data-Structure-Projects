#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;


//家庭成员类
class Person{

private:

	string _name;				//家庭成员姓名

	vector<Person*> _children;	//家庭成员孩子

public:

	Person(){

	}

	Person(string name){

		_name = name;
	}

	string getName(){			//获取家庭成员姓名方法

		return _name;
	}

	void changeName(string name){	//改变家庭成员姓名方法

		_name = name;
	}

	void addChild(Person* child){	//家庭成员添加孩子方法

		_children.push_back(child);
	}

	void show(){					//打印家庭成员孩子方法

		cout << _name << "的第一代子孙是：";

		for (int i = 0; i < _children.size(); i++){

			cout << _children.at(i)->getName() << "    ";
		}

		cout << endl;
	}

	void clearChildren(){			//清除家庭成员孩子方法

		_children.clear();
	}
};

class System{

private:

	string root;			//存储根节点

	Person *null;			//存储空家庭成员

	vector<Person*> people;	//存储所有家庭成员

public:
	System(){

	}

	~System(){

	}

	void initial();			//初始化对象方法

	void showBg();			//打印面板

	void start();			//控制流程方法

	void work();			//核心操作方法

	void _addFamily();		//添加家谱方法

	void _addChild();		//添加家庭成员方法

	void _dismissFamily();	//解散局部家庭方法

	void _changeName();		//更改家庭成员姓名方法

	Person* _findPerson(string name){	//寻找并返回家庭成员方法

		for (int i = 0; i < people.size(); i++){

			if (people.at(i)->getName() == name){

				return people.at(i);
			}
		}

		return null;
	}

	Person* _findName(){		//新建并返回一个新的家庭成员方法

		bool flag = true;

		string name;

		Person *person;

		while (flag)
		{
			cout << "请输入要操作的人的姓名：";

			cin >> name;

			if (name != ""){

				person = _findPerson(name);

				if (person->getName() == ""){

					cout << "未找到此人，请重新输入！" << endl;
				}
				else{

					flag = false;

					break;
				}
			}
			else {

				cout << "姓名不能为空,请重新输入！" << endl;
			}
		}

		return person;
	}

	string _checkName(){		//新建并返回一个家庭成员名字方法

		bool flag = true;

		Person *tmp;

		string name;

		while (flag){

			cin >> name;

			if (name != ""){

				tmp = _findPerson(name);

				if (tmp->getName() == ""){

					flag = false;
				}
				else{

					cout << name << "已存在，请重新输入！" << endl;
				}
			}
			else {

				cout << "姓名不能为空，请重新输入！" << endl;
			}

		}

		delete(tmp);

		return name;
	}
};

void System::initial(){

	null = new Person("");

	string name;

	showBg();

	cout << "首先建立一个家谱！" << endl
		<< "请输入祖先的姓名：";

	cin >> name;

	Person *root = new Person(name);

	people.push_back(root);

	cout << "此家谱的祖先是：" << name << endl;
}

void System::showBg(){

	cout << endl
		<< "**                 家谱管理系统                 **" << endl
		<< "====================================================" << endl
		<< "**           请选择要执行的操作 ：                **" << endl
		<< "**              A --- 完善家谱                    **" << endl
		<< "**              B --- 添加家庭成员                **" << endl
		<< "**              C --- 解散局部家庭                **" << endl
		<< "**              D --- 更改家庭成员姓名            **" << endl
		<< "**              E --- 退出程序                    **" << endl
		<< "====================================================" << endl;
}

void System::start(){

	initial();

	work();
}

void System::work(){

	string option;

	bool flag = true;

	while (flag){

		cout << endl << "请选择要执行的操作：";

		cin >> option;

		switch (option[0]){

		case 'A': _addFamily(); break;
		case 'B': _addChild(); break;
		case 'C': _dismissFamily(); break;
		case 'D': _changeName(); break;
		case 'E': flag = false; break;
		default: break;
		}
	}
}

void System::_addFamily(){

	string name;

	int num;

	bool flag = true;

	Person *tmp;

	Person *person = _findName();

	cout << "请输入" << name << "的儿女人数：";

	cin >> num;

	cout << "请依次输入" << name << "的儿女的姓名：";

	for (int i = 0; i < num; i++){

		flag = true;

		while (flag){

			cin >> name;

			if (name != ""){

				tmp = _findPerson(name);

				if (tmp->getName() == ""){

					flag = false;
				}
				else{

					cout << name << "已存在，请重新输入！" << endl;
				}
			}
			else {

				cout << "姓名不能为空，请重新输入！" << endl;
			}

		}

		Person *child = new Person(name);

		people.push_back(child);

		person->addChild(child);
	}

	person->show();
}

void System::_addChild(){

	string name;

	bool flag = true;

	Person *person = _findName();

	cout << "请输入" << name << "新添加的的儿子（女儿）的姓名：";

	flag = true;

	name = _checkName();

	Person *child = new Person(name);

	people.push_back(child);

	person->addChild(child);

	person->show();
}


void System::_dismissFamily(){

	string name;

	bool flag = true;

	Person *person = _findName();

	cout << "要解散家庭的人是：" << person->getName() << endl;

	person->show();

	person->clearChildren();
}

void System::_changeName(){

	Person *tmp;

	Person *person = _findName();

	bool flag = true;

	string newname;

	cout << "请输入更改后的姓名：";

	cin >> newname;

	cout << person->getName() << "已更名为" << newname << endl;

	person->changeName(newname);
}

int main(){

	System *my_system = new System();

	my_system->start();

	system("pause");

	return 0;
}
