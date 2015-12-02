#include <iostream>
#include <string>
#include <algorithm>

#define CREATE_HEAD 1

//操作码
#define OPERATE_INSERT 1
#define OPERATE_DELETE 2
#define OPERATE_SEARCH 3
#define OPERATE_CHANGE 4
#define OPERATE_COUNT 5
#define OPERATE_EXIT 0

//修改操作码
#define CHANGE_ID 1
#define CHANGE_NAME 2
#define CHANGE_SEX 3
#define CHANGE_AGE 4
#define CHANGE_JOB 5
#define CHANGE_FINISH 0

using namespace std;

//Student信息的存储类
class Student{

friend class StudentList;

private:
	//链表指针
	Student *next;

	//存储数据
	string id;            //考号
	string name;		  //姓名
	string sex;			  //性别
	string age;			  //年龄
	string job;			  //报考类别

public:
	//构造函数
	Student(){

		next = NULL;

		cin >> id >> name >> sex >> age >> job;
	}

	Student(int TMP){

		next = NULL;
	}

	//析构函数
	~Student(){
	}

	//静态的Create方法
	static Student* create();
	
	static Student* createHead();

	//输出学生数据到屏幕
	void show();
};

Student* Student::create(){

	Student* stu = new Student();

	return stu;
}

Student* Student::createHead(){

	Student* stu = new Student(CREATE_HEAD);

	return stu;
}

void Student::show(){
	
	cout << id << "         " << name << "       " << sex << "          " << age << "          " << job << endl;
}

//Student链表操作与维护类
class StudentList
{
private :
	Student *child;
	int length;

public :
	//构造函数
	StudentList(){
	}

	//析构函数
	~StudentList(){
	}

	//初始化数据读入与存储方法
	void start();

	//读取操作码方法
	void work();

	//插入考生信息方法
	void _insert();

	//删除考生信息方法
	void _delete();
	
	//查询考生信息方法
	void _search();
	
	//修改考生信息方法
	void _change();
	
	//统计考生信息方法
	void _count();

	//输出考生信息到屏幕方法
	void show();
};

void StudentList::start(){

	//Cout
	cout << "首先请建立考生信息系统！"
		<< endl
		<< "请输入考生人数：";

	//判断读入信息是否合理
	do{
		cin >> length;

		if (length < 0)
		{
			cout << "输入考生人数有误，请输入一个非负整数！";
		}
	} while (length < 0);

	if (length > 0){

		Student *now;

		cout << "请依次输入考生的考号，姓名，性别，年龄以及报考类别！" << endl;

		child = now = Student::createHead();

		for (int i = 0; i < length; i++){

			now->next = Student::create(); //调用静态的Create方法生成Student对象

			now = now->next;
		}
	}

	show();

	return work();
}

void StudentList::work(){

	int operation = 0;

	cout << "请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）" << endl << endl;
	cout << "请选择您要进行的操作：";
	
	//读取并判断操作码
	cin >> operation;

	switch (operation){

		case OPERATE_INSERT:return _insert();

		case OPERATE_DELETE:return _delete();

		case OPERATE_SEARCH:return _search();

		case OPERATE_CHANGE:return _change();

		case OPERATE_COUNT:return _count();

		case OPERATE_EXIT:return show();

		default:{

			cout << "输入的操作码有误！" << endl;

			return work();
		}
	}
}

void StudentList::_insert(){

	Student* now = child;

	int position = 0;

	length++;
	
	//判断插入位置是否合理
	do{

		cout << "请输入您要插入的考生的位置：";

		cin >> position;

		if (position < 1){
			cout << "插入的位置必须大于0！" << endl;
		}

		if (position > length){
			cout << "插入的位置必须小于" << length + 1 << "!" << endl;
		}

	} while (position < 1 || position > length);

	for (int i = 1; i < position; i++){

		now = now->next;
	}

	cout << "请依次输入要插入的考生的考号，姓名，性别，年龄以及报考类别！" << endl;

	Student* stu = Student::create();

	stu->next = now->next;

	now->next = stu;

	show();

	return work();
}

void StudentList::_delete(){

	Student* now = child;

	Student* stu = NULL;

	int position = 0;

	//判断删除位置是否合理
	do{

		cout << "请输入您要删除的考生的位置：";

		cin >> position;

		if (position < 1){
			cout << "插入的位置必须大于0！" << endl;
		}

		if (position > length){
			cout << "插入的位置必须小于" << length + 1 << "!" << endl;
		}

	} while (position < 1 || position > length);

	length--;

	for (int i = 1; i < position; i++){

		now = now->next;
	}

	stu = now->next;

	now->next = stu->next;

	delete(stu);

	show();

	return work();
}

void StudentList::_search(){

	Student* now = child;

	string id;

	bool find = false;   //记录是否找到对应考号的考生

	cout << "请输入要查找的考生的考号：";

	cin >> id;

	do{

		if (now->id == id){

			find = true;
		}
		else{

			now = now->next;
		}

	} while (!find && now->next != NULL);
	
	if (find){

		cout << "考号      " << "姓名      " << "性别      " << "年龄      " << "报考类别" << endl;
		
		now->show();
	}
	else{

		cout << "没有找到对应学号的学生记录！" << endl;
	}

	show();

	return work();
}

void StudentList::_change(){

	Student* now = child;

	string id;

	string str;

	int operation = 0;

	bool find = false;

	cout << "请输入要修改的考生的考号：";
	cin >> id;

	do{

		if (now->id == id){

			find = true;
		}
		else{

			now = now->next;
		}

	} while (!find && now->next != NULL);

	if (find){
	
		cout << endl << "考号      " << "姓名         " << "性别        " << "年龄        " << "报考类别" << endl;

		now->show();

		//读取并判断修改操作码
		do{

			cout << "请输入要修改的考生信息（1为考号，2为姓名，3为性别，4为年龄，5为报考类别,0为结束操作）" << endl;
			cout << "请输入要修改的考生信息：";

			cin >> operation;

			switch (operation)
			{
			case CHANGE_ID:{

				cout << "您要将“" << now->id << "”" << "修改为：";

				cin >> str;

				now->id = str;

				now->show();

				break;
			}
			case CHANGE_NAME:{

				cout << "您要将“" << now->name << "”" << "修改为：";

				cin >> str;

				now->name = str;

				now->show();

				break;
			}
			case CHANGE_SEX:{

				cout << "您要将“" << now->sex << "”" << "修改为：";

				cin >> str;

				now->sex = str;

				now->show();

				break;
			}
			case CHANGE_AGE:{

				cout << "您要将“" << now->age << "”" << "修改为：";

				cin >> str;

				now->age = str;

				now->show();

				break;
			}
			case CHANGE_JOB:{

				cout << "您要将“" << now->job << "”" << "修改为：";

				cin >> str;

				now->job = str;

				now->show();

				break;
			}
			case CHANGE_FINISH:{

				cout << "修改后的结果是：" << endl;

				cout << "考号      " << "姓名      " << "性别      " << "年龄      " << "报考类别" << endl;

				now->show();

				break;
			}
			default:cout << "输入的操作码有误！" << endl; break;
			}

			cout << endl;

		} while (operation != CHANGE_FINISH);
	}
	else{

		cout << "没有找到对应学号的学生记录！" << endl;
	}

	show();

	return work();
}

void StudentList::_count(){

	cout << "一共有" << length << "名考生档案！" << endl;

	show();

	return work();
}

void StudentList::show(){

	Student* now = child->next;

	cout << endl << "考号      " << "姓名         " << "性别        " << "年龄        " << "报考类别" << endl;

	while (now != NULL){

		now->show();

		now = now->next;
	}

	cout << endl;
}

int main(){

	StudentList* studentList = new StudentList();

	studentList->start();

	return 0;
}