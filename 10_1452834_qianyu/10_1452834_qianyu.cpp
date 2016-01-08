#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

const int BUBBLER_SORT = 1;
const int SELECT_SORT = 2;
const int INSERT_SORT = 3;
const int SHELL_SORT = 4;
const int QUICK_SORT = 5;
const int HEAP_SORT = 6;
const int MERGE_SORT = 7;
const int RADIX_SORT = 8;

class System{

private:

	int _length;				//随机数个数
	int *_originalArr;			//随机数
	int *_arr;					//用于排序
	int *_temp;					//归并排序临时数组
	int _count;					//比较计数

	void _adjust(int i, int length){	//归并排序维护堆

		int right = i * 2 + 1, left = i * 2, largest = i;

		if (left <= length && _arr[left] < _arr[largest]) largest = left;

		if (right <= length && _arr[right] < _arr[largest]) largest = right;

		if (largest != i){

			swap(_arr[i], _arr[largest]);

			_adjust(largest, length);

			_count++;
		}
	}

	int _getMaxBase(){					//返回所有随机数中最大位数

		int ans = 0;

		for (int i = 0; i < _length; i++){

			ans = max(ans, int(log10(_arr[i])));
		}

		return ans + 1;
	}

public:
	System(){

		_length = 0;
		_originalArr = NULL;
		_arr = NULL;
		_count = 0;
	}

	~System(){


	}

	void initial();								//初始化对象方法

	void start();								//控制流程方法

	void work();								//核心操作方法

	void _bubblerSort();						//冒泡排序

	void _selectSort();							//选择排序

	void _straightInsertSort();					//直接插入排序

	void _shellSort();							//希尔排序

	void _quickSort(int left, int right);		//快速排序

	void _heapSort();							//堆排序

	void _mergeSort(int left, int right);		//归并排序

	void _radixSort();							//基数排序
};

void System::initial(){

	_length = 0;

	cout
		<< "**                    排序算法比较                    **" << endl
		<< "========================================================" << endl
		<< "**                   1 --- 冒泡排序                   **" << endl
		<< "**                   2 --- 选择排序                   **" << endl
		<< "**                   3 --- 直接插入排序               **" << endl
		<< "**                   4 --- 希尔排序                   **" << endl
		<< "**                   5 --- 快速排序                   **" << endl
		<< "**                   6 --- 堆排序                     **" << endl
		<< "**                   7 --- 归并排序                   **" << endl
		<< "**                   8 --- 基数排序                   **" << endl
		<< "**                   9 --- 退出程序                   **" << endl
		<< "========================================================" << endl;

	cout << endl << "请输入要产生的随机数的个数：";

	cin >> _length;

	_originalArr = new int[_length];

	_arr = new int[_length];

	_temp = new int[_length];

	srand((unsigned)time(NULL));

	for (int i = 0; i < _length; i++){

		_originalArr[i] = rand();
	}
}

void System::start(){

	initial();

	int option = 0;
	double begin = 0, end = 0;
	string sortName;

	cout << endl;

	while (true) {

		cout << "请选择排序算法：\t";

		cin >> option;

		if (option < 1 || option>9){

			cout << "输入有误，请重新输入！" << endl;

			continue;
		}

		begin = (double)clock();

		_count = 0;

		memcpy(_arr, _originalArr, sizeof(int) * _length);

		switch (option){

		case BUBBLER_SORT:_bubblerSort(); sortName = "冒泡排序"; break;

		case SELECT_SORT:_selectSort(); sortName = "选择排序"; break;

		case INSERT_SORT:_straightInsertSort(); sortName = "直接插入排序"; break;

		case SHELL_SORT:_shellSort(); sortName = "希尔排序"; break;

		case QUICK_SORT:_quickSort(0, _length - 1);; sortName = "快速排序"; break;

		case HEAP_SORT:_heapSort();; sortName = "堆排序"; break;

		case MERGE_SORT:_mergeSort(0, _length);; sortName = "归并排序"; break;

		case RADIX_SORT:_radixSort();; sortName = "基数排序"; break;

		default:return;
		}

		end = (double)clock();

		cout << sortName << "所用时间：\t" << (end - begin) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
		cout << sortName << "比较次数：\t" << _count << endl << endl;
	};
}

void System::_bubblerSort(){

	for (int i = 0; i < _length; i++){

		for (int j = _length - 1; j > i; j--){

			if (_arr[j - 1] > _arr[j]){

				swap(_arr[j - 1], _arr[j]);

				_count++;
			}
		}
	}
}

void System::_selectSort(){

	int temp = 0;

	for (int i = 0; i < _length; i++){

		temp = i;

		for (int j = i; j < _length; j++){

			if (_arr[j] < _arr[temp]){

				temp = j;
			}
		}

		swap(_arr[i], _arr[temp]);

		_count++;
	}
}

void System::_straightInsertSort(){

	int temp = 0, j = 0;

	for (int i = 1; i < _length; i++){

		temp = _arr[i];

		for (j = i - 1; j >= 0 && temp < _arr[j]; j--){

			_arr[j + 1] = _arr[j];

			_count++;
		}

		_arr[j + 1] = temp;

		_count++;
	}

}

void System::_shellSort(){

	int k = 0, temp = 0, gap = _length / 3 + 1;

	while (gap >= 1){

		for (int i = 0; i < gap; i++){

			for (int j = i + gap; j < _length; j += gap){

				temp = _arr[j];

				for (k = j - gap; k >= 0 && temp < _arr[k]; k -= gap){

					_arr[k + gap] = _arr[k];

					_count++;
				}

				_arr[k + gap] = temp;

				_count++;
			}
		}

		gap = (gap + 1) / 3;
	}
}

void System::_quickSort(int left, int right){

	int i = left, j = right, mid = _arr[(i + j) / 2];

	while (i <= j){

		while (mid > _arr[i]) i++;

		while (mid < _arr[j]) j--;

		if (i <= j){

			swap(_arr[i], _arr[j]);

			i++, j--;

			_count++;
		}
	}

	if (i < right) _quickSort(i, right);

	if (j > left) _quickSort(left, j);
}

void System::_heapSort(){

	for (int i = _length / 2; i >= 1; i--) _adjust(i, _length);

	int length = _length;

	for (int i = _length; i >= 2; i--){

		swap(_arr[i], _arr[1]);

		length--;

		_adjust(1, length);
	}
}

void System::_mergeSort(int left, int right){

	if (right - left <= 1) return;

	int mid = left + (right - left) / 2;

	_mergeSort(left, mid);

	_mergeSort(mid, right);

	int l = left, r = mid, i = left;

	while (l < mid || r < right){

		if (r >= right || (l < mid && _arr[l] <= _arr[r])){

			_temp[i++] = _arr[l++];

			_count++;
		}
		else {

			_temp[i++] = _arr[r++];

			_count++;
		}
	}

	for (int i = left; i < right; i++){

		_arr[i] = _temp[i];
	}
}

void System::_radixSort(){

	int maxBit = _getMaxBase();
	int *temp = new int[_length];
	int container[10];
	int radix = 1, k = 0;

	for (int i = 0; i < maxBit; i++){

		memset(container, 0, sizeof(int) * 10);

		for (int j = 0; j < _length; j++){

			k = _arr[j] / radix % 10;

			container[k]++;
		}

		for (int j = 1; j < 10; j++){

			container[j] += container[j - 1];
		}

		for (int j = _length - 1; j >= 0; j--){

			k = _arr[j] / radix % 10;

			temp[container[k] - 1] = _arr[j];

			container[k]--;
		}

		for (int j = 0; j < _length; j++){

			_arr[j] = temp[j];
		}

		radix *= 10;
	}

	delete[] temp;
}

int main(){

	System *my_system = new System();

	my_system->start();

	system("pause");

	return 0;
}
