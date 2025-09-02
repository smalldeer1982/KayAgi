# Conveyor Belts

## 题目描述

Conveyor matrix $ m_n $ is matrix of size $ n \times n $ , where $ n $ is an even number. The matrix consists of concentric ribbons moving clockwise.

In other words, the conveyor matrix for $ n = 2 $ is simply a matrix $ 2 \times 2 $ , whose cells form a cycle of length $ 4 $ clockwise. For any natural $ k \ge 2 $ , the matrix $ m_{2k} $ is obtained by adding to the matrix $ m_{2k - 2} $ an outer layer forming a clockwise cycle.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1811B/9983d2b36278ac1465bae7e881cd16110c58e71c.png) The conveyor matrix $ 8 \times 8 $ . You are standing in a cell with coordinates $ x_1, y_1 $ and you want to get into a cell with coordinates $ x_2, y_2 $ . A cell has coordinates $ x, y $ if it is located at the intersection of the $ x $ th row and the $ y $ th column.

Standing on some cell, every second you will move to the cell next in the direction of movement of the tape on which you are. You can also move to a neighboring cell by spending one unit of energy. Movements happen instantly and you can make an unlimited number of them at any time.

Your task is to find the minimum amount of energy that will have to be spent to get from the cell with coordinates $ x_1, y_1 $ to the cell with coordinates $ x_2, y_2 $ .

For example, $ n=8 $ initially you are in a cell with coordinates $ 1,3 $ and you want to get into a cell with coordinates $ 6, 4 $ . You can immediately make $ 2 $ movements, once you are in a cell with coordinates $ 3, 3 $ , and then after $ 8 $ seconds you will be in the right cell.

## 样例 #1

### 输入

```
5
2 1 1 2 2
4 1 4 3 3
8 1 3 4 6
100 10 20 50 100
1000000000 123456789 987654321 998244353 500000004```

### 输出

```
0
1
2
9
10590032```

# 题解

## 作者：abensyl (赞：1)

原题传送门：[CF1811B Conveyor Belts](https://www.luogu.com.cn/problem/CF1811B)。

## 思路

本人觉得本题很简单，重点主要在于理解题意。

理解题意我们就会发现，任意相邻两层之间，都可以指通过一次移动相互到达。

所以，实际题目让你求出的是两个点所在层的间距，即两个点所在的层数的差的绝对值。

因此，我们只要算出两点分别属于那一层即可。

在这里，我们规定最外面的一层为第 $1$ 层，则 $(1,1)$ 在第 $1$ 层。

判定一个点处于哪一层，我们可以考虑他到四边的距离，其中距离最小的即为到四边距离的最小值，即 $\min(n-x+1,n-y+1,x,y)$。

这样的话，我们就可以知道一个点处在那一层了，然后这道题目就迎刃而解了。

最后，两个点的层数相减取绝对值即为答案，输出答案即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int TT;
  cin >> TT;
  while (TT--) {
    int n, a, c, b, d;
    cin >> n >> a >> c >> b >> d;
    n /= 2;
    if (a > n) a = n * 2 - a + 1;
    if (b > n) b = n * 2 - b + 1;
    if (c > n) c = n * 2 - c + 1;
    if (d > n) d = n * 2 - d + 1;
    int ca = min(a, c), cb = min(b, d);
    cout << abs(ca - cb) << '\n';
  }
  return 0;
}
```

我的 [AC 记录](https://codeforces.com/contest/1811/submission/200708311)。

---

## 作者：sto_5k_orz (赞：0)

显然答案为两个坐标点的层数之差。

对于某一个坐标，它的层数是它到周围四条边线的最小距离。

所以 $(x,y)$ 的层数 $=\min(x,y,n-x+1,n-y+1)$。

那么两个点的层数求好，做差即可，注意需要绝对值。

下面给一个 dis 函数求出 $(x,y)$ 的层数。

```cpp
int dis(int n, int x, int y) {
	return min(min(x, y), min(n - x + 1, n - y + 1));
}
```

---

## 作者：aimcf (赞：0)

## 题解

设传送带左上角的 $x$ 坐标的值为这个传送带的编号。

那么容易发现答案就是 $(x_1,y_1)$ 和 $(x_2,y_2)$ 所在的传送带的编号的差的绝对值。

为了得到编号，可以发现编号就是这个点到四边的距离的最小值。

直接计算即可。

## 代码

[Submission #200847678 - Codeforces](https://codeforces.com/contest/1811/submission/200847678)

不知道为什么跑的很慢。

---

