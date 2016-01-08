#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;


class Queen{

private:

	int num;				//皇后个数&棋盘大小

	int arr[100];			//皇后摆放方法

	int checkRank;			//判断行是否重合
	int checkLLine;			//判断“\”列是否重合
	int checkRLine;			//判断“/”列是否重合

	int times;				//记录摆放总数

	void _dfs(int now);		//dfs

public:
	Queen(){

	}

	~Queen(){

	}

	void initial();			//初始化对象方法

	void input();			//读入方法

	void start();			//控制流程方法

	void work();			//核心操作方法

	void show();			//输出摆放方法
};

void Queen::initial(){
	
	num = checkRank = checkLLine = checkRLine = 0;

	memset(arr, 0, sizeof(arr));

	times = 0;

	cout << "现有N×N的棋盘，放入N个皇后，要求所有皇后不在同一行、列和同一斜线上！" << endl << endl;
}

void Queen::input(){

	cout << "请输入皇后的个数：";

	cin >> num;
}

void Queen::start(){

	initial();

	input();

	while (num < 1){

		cout << "请输入一个大于0的数！";

		input();
	}
	
	cout << endl << "皇后摆法:" << endl << endl;

	_dfs(0);

	cout << "共有" << times << "种解法！" << endl;
}

void Queen::_dfs(int now){		//now为当前行数

	if (now == num){

		times++;

		return show();
	}

	for (int i = 0; i < num; i++){

		if (!(checkRank & (1 << i)) && !(checkLLine & (1 << (num - i + now - 1))) && !(checkRLine & (1 << (i + now)))){		//判断是否能摆放

			//递归
			checkRank |= (1 << i);
			checkLLine |= (1 << (num - i + now - 1));
			checkRLine |= (1 << (i + now));
			arr[now] = i;
			_dfs(now + 1);
			checkRank ^= (1 << i);
			checkLLine ^= (1 << (num - i + now - 1));
			checkRLine ^= (1 << (i + now));
		}
	}
}

void Queen::show(){

	for (int i = 0; i < num; i++){

		for (int j = 0; j < num; j++){

			if (j == arr[i]){

				cout << "X ";
			}
			else{

				cout << "0 ";
			}
		}

		cout << endl;
	}
	cout << endl;
}

int main(){

	Queen *queen = new Queen();

	queen->start();

	system("pause");

	return 0;
}
