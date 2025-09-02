# The Artful Expedient

## 题目描述

首先定义一个整形变量n,Koyomi和Karen都会分别选择n个不同的正整数,分别表示为X1,X2,...Xn和Y1,Y2,...Yn。它们不断重复显示它们的序列,并一直重复直到所有2n个整数变得不同,此时,这是唯一被保留和考虑的最终状态。
他们需要计算满足有序数对(i,j)[1<=i,j<=n]中(Xi ^ Yi)的值等于2n个整数之中任意一个整数的值的有序数对的数量。这里'^'意味着对两个整数的按位异或操作,并且在大多数编程语言中用'^','/'或'xor'表示

如果这样的配对数量是偶数时,Karen就可以取得胜利,否则Koyomi胜利。你需要帮助他们决出最近一场比赛的获胜者。

## 样例 #1

### 输入

```
3
1 2 3
4 5 6
```

### 输出

```
Karen
```

## 样例 #2

### 输入

```
5
2 4 6 8 10
9 7 5 3 1
```

### 输出

```
Karen
```

# 题解

## 作者：Wen_kr (赞：9)

假设 $x_i$ ^ $y_j$ = $x_k$
那么 $x_k$ ^ $y_j$ = $x_i$

同理当$x_i$ ^ $y_j$ = $y_k$
时，$y_k$ ^ $x_i$ = $y_j$

因此对数永远是偶数。

题解就是显然的：
```
#include <cstdio>

int main()
{
    printf("Karen\n");
}
```


---

## 作者：PC_DOS (赞：2)

一道模拟题，只需要一个个枚举两个数组之中的数，计算它们的异或值，然后判定一下在不在两个数组之中即可。不过不能枚举一次搜索一次(会TLE)，这里开了一个长度为2000001，默认均为false的布尔型数组，输入数据时，每输入一个数就把这个数对应的位置标为true，枚举的时候只需要确定对应的位置是不是true即可。

所以就有代码了:
```
#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std; //头文件和命名空间
bool arrChecker[20000001] = { 0 }; //布尔型数组，默认值均为false，输入数据时，每输入一个数就把这个数对应的位置标为true
int main(){
	ios::sync_with_stdio(false); //一定意义上的输入输出加速
	vector<int> arrNumsKoyomi, arrNumsKaren; //存放两人所给数字的数组
	int iTemp, nCount, i, j,nAns=0; //iTemp-暂存数据，nCount-数的个数，i、j-循环计数器，nAns-有多少个符合题意的数对
	cin >> nCount; //输入数的个数
	for (i = 1; i <= nCount; ++i){ //输入Koyomi所给数字
		cin >> iTemp; //读入
		arrNumsKoyomi.push_back(iTemp); //压入数组
		arrChecker[iTemp] = true; //把这个数对应的位置标为true
	}
	for (i = 1; i <= nCount; ++i){ //输入Karen所给数字
		cin >> iTemp; //读入
		arrNumsKaren.push_back(iTemp); //压入数组
		arrChecker[iTemp] = true; //把这个数对应的位置标为true
	}
	for (i = 0; i <= nCount - 1; ++i){ //枚举Koyomi的数
		for (j = 0; j <= nCount - 1; ++j){ //枚举Karen的数
			iTemp = arrNumsKoyomi[i] ^ arrNumsKaren[j]; //记录两数异或
			if (arrChecker[iTemp]) //如果对应位置为true，即这两个数的异或在两人所给数中
				++nAns; //计数器加一
		}
	}
	if (nAns % 2 == 0) //如果有偶数对
		cout << "Karen"; //Karen胜利
	else //否则
		cout << "Koyomi"; //Koyomi胜利
	return 0; //结束
}
```

---

## 作者：CZQ_King (赞：0)

在说做法之前，说句废话：
#### 最短代码，除了$PY($~~屁眼~~$)$，其实发py的那个是我师父(C++党发py题解
## 做法：在这道题中，对数=偶数。所以输出Karen即可。
```cpp
#include<iostream>
int mian(){std:cout<<"Karen";}
```
###### 欢迎抄题解。。

---

## 作者：RioBlu (赞：0)

蒟蒻见大佬都没发Python2题解
就水一发
对数永远是偶数
## 而偶数就输出
# Karen
~~所以题解就N长~~
```
print "Karen"
```

---

