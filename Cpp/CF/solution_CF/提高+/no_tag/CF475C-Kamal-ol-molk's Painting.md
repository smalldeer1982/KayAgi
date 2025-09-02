# Kamal-ol-molk's Painting

## 题目描述

传闻称卡马尔-奥尔-莫尔克的一幅画被改动过。一个矩形刷子在画上向右或向下移动。

假设这幅画是一个由 $n \times m$ 大小的矩形网格组成的画布。最初，一个 $x \times y$ 的矩形刷子放在某个位置，其边缘与画布的边框平行（即 $1 \leq x \leq n, 1 \leq y \leq m$）。接着，刷子被多次移动，每次移动时会向右或向下移动一个单位。在绘画的全过程中，刷子始终保持在画布的内部。刷子经过的每一个单元格都会被改动。

你发现了一幅卡马尔-奥尔-莫尔克的老画。你想知道这幅画是否有可能通过上述方式被改动过。如果可能，你还希望知道刷子的最小面积。

## 样例 #1

### 输入

```
4 4
XX..
XX..
XXXX
XXXX
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4 4
....
.XXX
.XXX
....
```

### 输出

```
2
```

## 样例 #3

### 输入

```
4 5
XXXX.
XXXX.
.XX..
.XX..
```

### 输出

```
-1
```

# 题解

## 作者：chufuzhe (赞：0)

### 题意：
给出一个 $n$ $*$ $m$ 的图，问你能不能找出一个面积最小的刷子给所有可以被涂色的点刷上颜色，刷子每次只能往下或右移动一格。

### 思路：
首先用 $f_{i_j}$ 表示从 $i$ 到 $n$ ，从 $j$ 到 $m$ 的可以被涂色的点的格子个数。

然后枚举刷子的面积，进行判断。对于每个刷子的面积，从图的最左上的点开始刷。然后判断能不能刷满，如果能够，就判断刷子下一步是往下还是往右移动。

### 代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
char c[1005][1005];
int f[1005][1005];
int n, m;
int getf(int x1, int y1, int x2, int y2) { //统计可以被涂色的点的格子个数
	return (f[x1][y1] + f[x2 + 1][y2 + 1]) - (f[x2 + 1][y1] + f[x1][y2 + 1]);
}
int check(int x, int y, int a, int b) { //判断
	if(x + a - 1 > n || y + b - 1 > m) return 0;
	if(getf(x, y, x + a - 1, y + b - 1) != a * b) return 0;
	if(getf(x + a, y, n, y) > 0 && getf(x, y + b, x, m) > 0) return 0;
	if(getf(x + a, y, n, m) == 0 && getf(x, y + b, n, m) == 0) return 1;
	if(getf(x + a, y, n, y) > 0) return check(x + 1, y, a, b);
	return check(x, y + 1, a, b);
}
int main()
{
	ios::sync_with_stdio(false);
	cin >> n >> m; //输入
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= m; j++) {
			cin >> c[i][j];
		}
	}
	int mx = n, my = m;
	for(int i = n; i >= 1; i--) {
		for(int j = m; j >= 1; j--) {
			if(c[i][j] == '.') f[i][j] = f[i + 1][j] + f[i][j + 1] - f[i + 1][j + 1];
			else {
				f[i][j] = f[i + 1][j] + f[i][j + 1] - f[i + 1][j + 1] + 1; //计算从i到n，从j到m的可以被涂色的点的格子个数
				mx = min(mx, i), my = min(my, j); //最左上的点
			}
		}
	}
	int ans = -1;
	for(int i = 1; i <= n; i++) { //枚举刷子面积
		for(int j = 1; j <= m; j++) {
			if((i * j < ans || ans == -1) && check(mx, my, i, j)) { //满足要求
				ans = i * j; //更新答案
			}
		}
	}
	cout << ans << endl; /输出
	return 0;
}

```


---

