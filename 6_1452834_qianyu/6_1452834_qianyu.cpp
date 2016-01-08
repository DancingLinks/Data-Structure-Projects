#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;


//��ͥ��Ա��
class Person{

private:

	string _name;				//��ͥ��Ա����

	vector<Person*> _children;	//��ͥ��Ա����

public:

	Person(){

	}

	Person(string name){

		_name = name;
	}

	string getName(){			//��ȡ��ͥ��Ա��������

		return _name;
	}

	void changeName(string name){	//�ı��ͥ��Ա��������

		_name = name;
	}

	void addChild(Person* child){	//��ͥ��Ա��Ӻ��ӷ���

		_children.push_back(child);
	}

	void show(){					//��ӡ��ͥ��Ա���ӷ���

		cout << _name << "�ĵ�һ�������ǣ�";

		for (int i = 0; i < _children.size(); i++){

			cout << _children.at(i)->getName() << "    ";
		}

		cout << endl;
	}

	void clearChildren(){			//�����ͥ��Ա���ӷ���

		_children.clear();
	}
};

class System{

private:

	string root;			//�洢���ڵ�

	Person *null;			//�洢�ռ�ͥ��Ա

	vector<Person*> people;	//�洢���м�ͥ��Ա

public:
	System(){

	}

	~System(){

	}

	void initial();			//��ʼ�����󷽷�

	void showBg();			//��ӡ���

	void start();			//�������̷���

	void work();			//���Ĳ�������

	void _addFamily();		//��Ӽ��׷���

	void _addChild();		//��Ӽ�ͥ��Ա����

	void _dismissFamily();	//��ɢ�ֲ���ͥ����

	void _changeName();		//���ļ�ͥ��Ա��������

	Person* _findPerson(string name){	//Ѱ�Ҳ����ؼ�ͥ��Ա����

		for (int i = 0; i < people.size(); i++){

			if (people.at(i)->getName() == name){

				return people.at(i);
			}
		}

		return null;
	}

	Person* _findName(){		//�½�������һ���µļ�ͥ��Ա����

		bool flag = true;

		string name;

		Person *person;

		while (flag)
		{
			cout << "������Ҫ�������˵�������";

			cin >> name;

			if (name != ""){

				person = _findPerson(name);

				if (person->getName() == ""){

					cout << "δ�ҵ����ˣ����������룡" << endl;
				}
				else{

					flag = false;

					break;
				}
			}
			else {

				cout << "��������Ϊ��,���������룡" << endl;
			}
		}

		return person;
	}

	string _checkName(){		//�½�������һ����ͥ��Ա���ַ���

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

					cout << name << "�Ѵ��ڣ����������룡" << endl;
				}
			}
			else {

				cout << "��������Ϊ�գ����������룡" << endl;
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

	cout << "���Ƚ���һ�����ף�" << endl
		<< "���������ȵ�������";

	cin >> name;

	Person *root = new Person(name);

	people.push_back(root);

	cout << "�˼��׵������ǣ�" << name << endl;
}

void System::showBg(){

	cout << endl
		<< "**                 ���׹���ϵͳ                 **" << endl
		<< "====================================================" << endl
		<< "**           ��ѡ��Ҫִ�еĲ��� ��                **" << endl
		<< "**              A --- ���Ƽ���                    **" << endl
		<< "**              B --- ��Ӽ�ͥ��Ա                **" << endl
		<< "**              C --- ��ɢ�ֲ���ͥ                **" << endl
		<< "**              D --- ���ļ�ͥ��Ա����            **" << endl
		<< "**              E --- �˳�����                    **" << endl
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

		cout << endl << "��ѡ��Ҫִ�еĲ�����";

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

	cout << "������" << name << "�Ķ�Ů������";

	cin >> num;

	cout << "����������" << name << "�Ķ�Ů��������";

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

					cout << name << "�Ѵ��ڣ����������룡" << endl;
				}
			}
			else {

				cout << "��������Ϊ�գ����������룡" << endl;
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

	cout << "������" << name << "����ӵĵĶ��ӣ�Ů������������";

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

	cout << "Ҫ��ɢ��ͥ�����ǣ�" << person->getName() << endl;

	person->show();

	person->clearChildren();
}

void System::_changeName(){

	Person *tmp;

	Person *person = _findName();

	bool flag = true;

	string newname;

	cout << "��������ĺ��������";

	cin >> newname;

	cout << person->getName() << "�Ѹ���Ϊ" << newname << endl;

	person->changeName(newname);
}

int main(){

	System *my_system = new System();

	my_system->start();

	system("pause");

	return 0;
}
