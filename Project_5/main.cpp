#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;


class System{

private:
	int count;				//关键词出现次数

	string src;				//文章

	string keyword;			//关键词

	string f_name;			//文件名

public:
	System(){

	}

	~System(){

	}

	void initial();			//初始化对象方法

	void start();			//控制流程方法

	void work();			//核心操作方法

	void show();			//输出摆放方法
};

void System::initial(){

	count = 0;
	src = "";

	cout << "关键字检索系统" << endl;

	cout << "请输入文件名：";

	cin >> f_name;

	cin.get();
}


void System::start(){

	initial();

	cout << endl << "请输入一段英文(以 ^ 符号为结尾)：" << endl;

	string str;

	//以 ^ 符号为结尾读入文章	
	do {
		getline(cin, str);

		src = src + str + "\n";

	} while (str[str.length()-1]!='^');

	//文件写入
	ofstream f(f_name);

	f << src;

	f.close();

	cout << "本段文本已保存在文本文件\"" << f_name << "\"中。" << endl << endl;

	work();

	show();
}

void System::work(){

	cout << "请输入要检索的关键字：";
	cin >> keyword;

	int now = 0;
	string str = "";

	//检索
	do{

		if (isalpha(src[now])){

			str += src[now];
		}
		else{

			if (str == keyword){

				count++;
			}

			str = "";
		}

		now++;

	} while (now < src.length());
}

void System::show(){

	cout << "显示源文件\"" << f_name << "\"：" << endl << endl << src << endl << endl;

	cout << "在源文件中共检索到：" << count << "个关键字\"" << keyword << "\"" << endl;
}

int main(){

	System *my_system = new System();

	my_system->start();

	system("pause");

	return 0;
}
