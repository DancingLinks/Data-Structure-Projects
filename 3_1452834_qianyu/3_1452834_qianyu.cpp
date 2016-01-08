#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;


//迷宫类
class Maze{

private:

	int xx[4];				//dfs顺序
	int yy[4];

	int sizeI;				//地图行数
	int sizeJ;				//地图列数
	char map[100][100];		//地图

	int dx[50000];			//路径
	int dy[50000];
	int length;				//路径长度

	bool find;				//是否找到通路
	bool findMap;			//是否找到地图文件

	int sx;					//起点
	int sy;
	int ex;					//终点
	int ey;

	void _dfs(int x, int y);//dfs

public:
	Maze(){

	}

	~Maze(){

	}

	void initial();			//初始化对象方法

	bool input();			//读入方法

	void start();			//控制流程方法

	void showMap();			//输出地图方法

	void showWay();			//输出路径方法

	void work();			//核心操作方法
};

void Maze::initial(){

	sizeI = sizeJ = 7;		//初始化默认地图信息

	sx = sy = 1;
	ex = ey = 5;

	length = 0;

	find = false;

	xx[0] = xx[2] = yy[1] = yy[3] = 0;
	xx[1] = yy[0] = 1;
	xx[3] = yy[2] = -1;

	memset(map, '#', sizeof(map));

	map[1][1] = map[2][1] = map[3][1] = map[4][1] = map[5][1] 
		= map[3][2] = map[1][3] = map[2][3] = map[3][3] = map[4][3] 
		= map[5][3] = map[1][4] = map[4][4] = map[1][5] = map[3][5]
		= map[4][5] = map[5][5] = '0';
}

bool Maze::input(){

	ifstream fin("Input.txt");//寻找地图文件

	if (!fin) return false;
	
	fin >> sizeI >> sizeJ;

	fin >> sx >> sy >> ex >> ey;

	for (int i = 0; i < sizeI; i++)
		for (int j = 0; j < sizeJ; j++)
			fin >> map[i][j];

	return true;
}

void Maze::start(){

	initial();

	findMap = input();

	if (!findMap){

		cout << "没有找到地图文件,将采用默认地图！" << endl << endl;
	}
	else if (map[sx][sy] != '0' || map[ex][ey] != '0'){

		cout << "起点终点不能为'#'，已自动修改地图！" << endl << endl;

		map[sx][sy] = map[ex][ey] = '0';
	}

	work();						//执行寻路操作

	showMap();

	if (find){

		cout << "迷宫有通路！" << endl;
	}
	else{

		cout << "迷宫没有通路！" << endl;
	}

	showWay();
}

void Maze::work(){

	_dfs(sx, sy);
}

void Maze::_dfs(int x, int y){

	if (!find){

		map[x][y] = '*';
		dx[length] = x;
		dy[length++] = y;

		if (ex == x && ey == y){

			find = true;

			return;
		}

		for (int i = 0; i < 4; i++){			//递归寻路

			if (map[x + xx[i]][y + yy[i]] == '0')
			{
				_dfs(x + xx[i], y + yy[i]);
				
				if (!find){
				
					dx[length] = x;
					dy[length++] = y;
				}
			}
		}
	}
}

void Maze::showMap(){

	map[sx][sy] = 'S';
	map[ex][ey] = 'E';

	cout << "迷宫地图：" << endl << endl;

	for (int j = 0; j < sizeJ; j++){

		cout << "\t" << j << "列";
	}
	cout << endl;

	for (int i = 0; i < sizeI; i++)
	{

		cout << i << "行";

		for (int j = 0; j < sizeJ; j++)
			cout << "\t" <<  map[i][j];

		cout << endl << endl;
	}
}

void Maze::showWay(){

	cout << endl << "(" << sx << "," << sy << ")";

	for (int i = 1; i < length; i++){

		cout << " ---> (" << dx[i] << "," << dy[i] << ")";
	}

	cout << endl;
}

int main(){

	Maze *maze = new Maze();

	maze->start();

	system("pause");

	return 0;
}
