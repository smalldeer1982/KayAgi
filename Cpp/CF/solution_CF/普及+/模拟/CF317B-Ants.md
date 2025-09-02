# Ants

## 题目描述

It has been noted that if some ants are put in the junctions of the graphene integer lattice then they will act in the following fashion: every minute at each junction ( $ x $ , $ y $ ) containing at least four ants a group of four ants will be formed, and these four ants will scatter to the neighbouring junctions ( $ x+1 $ , $ y $ ), ( $ x-1 $ , $ y $ ), ( $ x $ , $ y+1 $ ), ( $ x $ , $ y-1 $ ) — one ant in each direction. No other ant movements will happen. Ants never interfere with each other.

Scientists have put a colony of $ n $ ants into the junction (0, 0) and now they wish to know how many ants will there be at some given junctions, when the movement of the ants stops.

## 说明/提示

In the first sample the colony consists of the one ant, so nothing happens at all.

In the second sample the colony consists of 6 ants. At the first minute 4 ants scatter from (0, 0) to the neighbouring junctions. After that the process stops.

## 样例 #1

### 输入

```
1 3
0 1
0 0
0 -1
```

### 输出

```
0
1
0
```

## 样例 #2

### 输入

```
6 5
0 -2
0 -1
0 0
0 1
0 2
```

### 输出

```
0
1
2
1
0
```

# 题解

## 作者：封禁用户 (赞：2)

## 题解：CF317B Ants

又水了一道绿题。

### 解题思路

一只一只的放，复杂度 $O(n^2+t)$，明显超时，所以可以尝试将所有蚂蚁同时放入格子中，再进行更新，这时，此题就变成了**爆搜**模板，连剪枝都不用。最终复杂度：$O(\log{(n^2)}+t)$。

剩下的思路就很简单了，直接模拟蚂蚁爬行即可。此时已经可以 $AC$ 了，但是为了极致的效率，我额外加入了一个小优化，如果想要学习和另一篇题解不同的思路，请继续阅读。

### 优化思路

首先来看一组数据：

当 $n = 23$ 时，蚂蚁的最终数量如下：

```txt
0 0 0 0 0 0 0
0 0 0 1 0 0 0
0 0 2 2 2 0 0
0 1 2 3 2 1 0
0 0 2 2 2 0 0
0 0 0 1 0 0 0
0 0 0 0 0 0 0
```

我们可以发现，这个数据中有很多部分是重复的，如果我们将其想象为平面直角坐标系，那么只要知道坐标轴上的数和一个象限的数，就可以推出整个平面直角坐标系中所有位置蚂蚁的数量。

进行一个小优化后，上面的矩阵就会变为：

```txt
0 0 0 0
1 0 0 0
2 2 0 0
3 2 1 0
```

计算量明显小多了。成功拿下最优解第一名，比目前第二名的 $\frac{1}{2}$ 时间还少。

如果还没明白，可以对照代码看一下搜索中边界条件的处理方法。

最后想吐槽一下第一篇的题解，复杂度算错了，这道题没有常数级别的预处理算法。

**注意事项**：要特判 $x_i , y_i$ 的范围比数组大的情况，这时肯定蚂蚁数为 $0$，直接输出即可。
### 参考代码：

```cpp
#include<bits/stdc++.h>
#pragma GCC optimize(2)
using namespace std;
int n , t , a[105][105] , p , q;
void dfs(int x , int y)
{
	if(a[x][y] < 4)
	{
		return;
	}
	int tmp = a[x][y];
	a[x][y] %= 4;
	if(x == 1)
	{
		a[x - 1][y] += tmp / 4 * 2;
		dfs(x - 1 , y);
	}
	else if(x != 0)
	{
		a[x - 1][y] += tmp / 4;
		dfs(x - 1 , y);
	}
	if(y == 1)
	{
		a[x][y - 1] += tmp / 4 * 2;
		dfs(x , y - 1);
	}
	else if(y != 0)
	{
		a[x][y - 1] += tmp / 4;
		dfs(x , y - 1);
	}
	a[x + 1][y] += tmp / 4;
	dfs(x + 1 , y);
	a[x][y + 1] += tmp / 4;
	dfs(x , y + 1);
	return;
}
int main()
{
	ios::sync_with_stdio(0);
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> t;
	a[0][0] = n;
	dfs(0 , 0);
	while(t--)
	{
		cin >> p >> q;
		p = abs(p);
		q = abs(q);
		if(p >= 100 || q >= 100)
		{
			cout << "0\n";
			continue;
		}
		cout << a[p][q] << '\n';
	}
	return 0;
}
```

感谢浏览。

---

## 作者：Luo_gu_ykc (赞：0)

建议评绿（有点思维难度）。
## 题目大意

在 $(0, 0)$ 上有 $n$ 只蚂蚁，如果 $(x, y)$ 位置上的蚂蚁至少有 $4$ 个，那么这些蚂蚁会分别跳到 $(x - 1, y)(x + 1, y)(x, y - 1)(x, y + 1)$ 这些位置上，直到 $(x, y)$ 上的蚂蚁数量少于 $4$。

给出 $m$ 个询问，每次询问给定一个坐标 $(x, y)$ 请输出这个坐标上的蚂蚁数。

## 思路；

我们首先想到 dfs，因为 $n$ 的范围只有 $0 \leqslant n \leqslant 30000$，再因为每次蚂蚁跳的时候会往四个方向跳，所以跳的次数最多为 $\log_4 30000$，这个数不会超过 $8$，也就是时间复杂度为 $O(4 ^ 8)$，明显可以 $1s$ 跑过，即使有常数。

那么我们可以直接 dfs 模拟蚂蚁跳的过程，但是有个细节，因为坐标可能为负数，我们需要加一个值，使得坐标都为正数，明显，可以加上 $100$，因为合法坐标的绝对值不可能会超过 $75$，当然，你不放心也可以加上更大的数。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 105; 

int n, m;
int cnt[N * 2][N * 2]; // cnt 表示每个坐标上的蚂蚁数

void dfs(int x, int y){ // dfs 模拟蚂蚁跳的过程
	if(cnt[x][y] <= 3){
		return ;
	}
	int num = cnt[x][y] / 4;
	cnt[x - 1][y] += num;
	dfs(x - 1, y);
	cnt[x + 1][y] += num;
	dfs(x + 1, y);
	cnt[x][y - 1] += num;
	dfs(x, y - 1);
	cnt[x][y + 1] += num;
	dfs(x, y + 1);
	cnt[x][y] %= 4;
	return ;
}

signed main(){
	cin >> n >> m;
	cnt[N][N] = n; // 每个坐标都加上了 N，所以接下来的坐标都要加上 N
	dfs(N, N); 
	while(m--){
		int _x, _y;
		cin >> _x >> _y;
		if(0 <= (_x + N) && (_x + N) < 2 * N && 0 <= (_y + N) && (_y + N) < 2 * N){ // 看坐标是否可能跳到
			cout << cnt[_x + N][_y + N] << "\n";
		} else {
			cout << 0 << "\n";
		}
	}
	return 0;
}
```

但是交上去，我们会 **UKE**，再到 CF 上看，发现 RE，很明显，dfs 的通病，函数栈空间爆了。

解释一下，一个函数调用过多，会导致了函数栈空间内存不足，也会出现 RE 的情况。

那么我们只能尝试使用模拟解决，我们从上面可以知道，这个坐标的绝对值不会超过 $75$，也就是说突破点在坐标上，我们可以用一个数组存储每个坐标上蚂蚁的数量，然后每次枚举所有可能合法的坐标，再检查有没有坐标的蚂蚁要跳往四周，如果没有要跳的蚂蚁了，就可以退出循环。

那么这样的话，我们的时间复杂度为 $O(\log_4 30000 \times N ^ 2)$，$N$ 为最大的合法坐标，算下来，只有 $320000$ 左右，算上常数也是远远快于 $1s$ 的，那么问题就解决了。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 105; 

int n, m, x = N, y = N, cnt[2 * N][2 * N];
bool vis = 1;

signed main(){
	cin >> n >> m;
	cnt[N][N] = n;
	while(vis){
		vis = 0; // vis 代表是否有坐标上的蚂蚁会跳
		for(int i = 0; i < N * 2; i++){
			for(int j = 0; j < N * 2; j++){
				if(cnt[i][j] >= 4){
					vis = 1; 
					int num = cnt[i][j] / 4;
					cnt[i - 1][j] += num;
					cnt[i + 1][j] += num;
					cnt[i][j - 1] += num;
					cnt[i][j + 1] += num;
					cnt[i][j] -= (num * 4);
				}
			}
		}
	}
	while(m--){
		int _x, _y;
		cin >> _x >> _y;
		if(0 <= (_x + x) && (_x + x) < 2 * N && 0 <= (_y + y) && (_y + y) < 2 * N){ // 检查合法坐标
			cout << cnt[_x + x][_y + y] << "\n";
		} else {
			cout << 0 << "\n";
		}
	}
	return 0;
}
```

---

