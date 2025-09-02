# Yet Another Task with Queens

## 题目描述

皇后是最强的棋子。在现代国际象棋中，皇后可以在任何水平、垂直或对角线方向上移动任意数量的方格（考虑到在其途中没有其他棋子）。女王结合了车和主教的技能。

$n\times n$方格棋盘上有 $m$ 个皇后 ，你知道每个女王的位置是 $(r_i,c_i)$ ，$r_i$ 是行，$c_i$ 是列。没有两个皇后处于同一位置。

对于每一个女王，我们可以计算 $w$ ——该女王威胁（攻击）的其他女王的数量。对于固定的攻击方向，如果有许多皇后处于攻击射线上，则只有该方向上的第一个皇后受到攻击。显然，对于任何女王来说，$0<=w<=8$ 。 

打印序列 $t_0,t_1,...，t_8$，其中$t_i$是威胁其他皇后的皇后数量，即他们的 $w$ 等于 $i$ 的皇后数量。

## 样例 #1

### 输入

```
8 4
4 3
4 8
6 5
1 6
```

### 输出

```
0 3 0 1 0 0 0 0 0 ```

## 样例 #2

### 输入

```
10 3
1 1
1 2
1 3
```

### 输出

```
0 2 1 0 0 0 0 0 0 ```

# 题解

## 作者：__cheems__ (赞：2)

## 解题思路

考虑排序，首先对于每个皇后按照 $r$ 的大小进行排序。此时对于第 $i$ 个皇后，若第 $i+1$ 个皇后与第 $i$ 个皇后的 $r$ 值相等，则第 $i$ 个皇后可以攻击的皇后数量 $w_i++$ 即可。同理，若第 $i-1$ 个皇后与第 $i$ 个皇后的 $r$ 值相等，则第 $i$ 个皇后可以攻击的皇后数量 $w_i++$ 。

按照上述方法，对于每个皇后的 $r$ ， $c$ ， $r+c$ ， $r-c$ 进行 $4$ 次排序。然后统计出每个皇后的攻击其他皇后的数量即可。

时间复杂度为 $O(\max(m,n))$ 。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m;
struct node
{
	int x, y, id;
};
node a[1000010];
int cnt[1000010], ans[1000010];
bool cmp1(node x, node y) // x 相同情况下的排序 
{
	if (x.x != y.x) return x.x < y.x;
	return x.y < y.y;
}
bool cmp2(node x, node y) // y 相同情况下的排序 
{
	if (x.y != y.y) return x.y < y.y;
	return x.x < y.x;
}
bool cmp3(node x, node y) // 斜行 x + y 相等情况下的排序 
{
	if (x.x + x.y != y.x + y.y) return x.x + x.y < y.x + y.y;
	return x.x < y.x;
}
bool cmp4(node x, node y) // 斜行 x - y 相等情况下的排序 
{
	if (x.x - x.y != y.x - y.y) return x.x - x.y < y.x - y.y;
	return x.x < y.x;
}
bool cmp5(node x, node y) // 回到开初 
{
	return x.id < y.id;
}
int main()
{
	cin >> n >> m;
	a[0] = ((node){2 * n + 1, 4 * n + 1, 0});
	a[m + 1] = ((node){4 * n + 1, 8 * n + 1, m + 1});
	for (int i = 1; i <= m; i++)
	{
		cin >> a[i].x >> a[i].y;
		a[i].id = i;
	}
	sort(a + 1, a + m + 1, cmp1);
	for (int i = 1; i <= m; i++)
	{
		ans[a[i].id] += 2; 
		if (a[i].x != a[i - 1].x) ans[a[i].id]--;
		if (a[i].x != a[i + 1].x) ans[a[i].id]--;
	}
	sort(a + 1, a + m + 1, cmp2);
	for (int i = 1; i <= m; i++)
	{
		ans[a[i].id] += 2; 
		if (a[i].y != a[i - 1].y) ans[a[i].id]--;
		if (a[i].y != a[i + 1].y) ans[a[i].id]--;
	} 
	sort(a + 1, a + m + 1, cmp3);
	for (int i = 1; i <= m; i++)
	{
		ans[a[i].id] += 2; 
		if (a[i].y + a[i].x != a[i - 1].y + a[i - 1].x) ans[a[i].id]--;
		if (a[i].y + a[i].x != a[i + 1].y + a[i + 1].x)	ans[a[i].id]--;
	}
	sort(a + 1, a + m + 1, cmp4);
	for (int i = 1; i <= m; i++)
	{
		ans[a[i].id] += 2; 
		if (a[i].x - a[i].y != a[i - 1].x - a[i - 1].y) ans[a[i].id]--;
		if (a[i].x - a[i].y != a[i + 1].x - a[i + 1].y) ans[a[i].id]--;
	}
	sort(a + 1, a + m + 1, cmp5);
	for (int i = 1; i <= m; i++) cnt[ans[i]]++;
	for (int i = 0; i <= 8; i++) cout << cnt[i] << " ";
    return 0;
}
```

---

