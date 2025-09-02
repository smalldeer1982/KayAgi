# 传说中的车 Fabled Rooks

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=23&page=show_problem&problem=2075

[PDF](https://uva.onlinejudge.org/external/111/p11134.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA11134/bd6c0f2fb7433acc9184472bbe18e9f1a53f823f.png)

## 样例 #1

### 输入

```
8
1 1 2 2
5 7 8 8
2 2 5 5
2 2 5 5
6 3 8 6
6 3 8 5
6 3 8 8
3 6 7 8
8
1 1 2 2
5 7 8 8
2 2 5 5
2 2 5 5
6 3 8 6
6 3 8 5
6 3 8 8
3 6 7 8
0```

### 输出

```
1 1
5 8
2 4
4 2
7 3
8 5
6 6
3 7
1 1
5 8
2 4
4 2
7 3
8 5
6 6
3 7```

# 题解

## 作者：pufanyi (赞：9)

一道神奇的贪心题……

这道题乍一看感觉难以下手，机房大佬一看这题竟说出了二分图匹配（当时我震惊了）。

首先，我们发现其实x轴与y轴是互不相关的，可以独立求解。于是我们把x轴与y轴分开求解。

于是问题就变成了：在$[1,n]$的区间中，有一些区间，在每一个区间中选一个点，使最终恰好覆盖$[1,n]$中的这$n$个点。

开始时，我想的是以$l$作为第一关键字，$r$作为第二关键字进行排序。然后从左往右扫。然而这样显然是不成立的，`[1,3],[1,3],[2,2]`这组数据就会被卡掉。

在用贪心法解决问题时，我们可以考虑：如果要选择几种状态，一种决策的“后路”覆盖了所有其他决策的“后路”，那我们**不应当**选择这种决策。（可能我语文不怎么好，那就用这道题解释一下吧。）

试想一下，如果我们要求从前往后做出抉择，且有两段区间都可以选择，那我们应该选择哪一段？显然是$r$值小的哪一段。应为对于后面的点，$r$值小的可以覆盖的点$r$值大的也可以覆盖，而$r$值大的可覆盖的点$r$值小的可能无法覆盖。这样，我们可以认为$r$值大的”后路“覆盖了$r$值小的的所有后路，于是我们应该选$r$值小的。

于是我们就不难想到方法：以$r$（后路）作为关键字排序（$r$相同的可以随意排），然后对于每一个序列，从$l$到$r$扫描。如果是该点没有被选择过，那就选择该点。

具体实现可以看一下代码。

## 代码

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 5005;

struct qujian
{
	int xl, xr, yl, yr;
	int x, y;
	int num;

	inline bool operator < (const qujian& oth) const//重载小于号，方便打乱之后排回来
	{
		return num < oth.num;
	}
} qj[maxn];

inline bool cmp_x(qujian a, qujian b)//以r为关键字进行排序
{
	return a.xr < b.xr;
}

inline bool cmp_y(qujian a, qujian b)
{
	return a.yr < b.yr;
}

bool have[maxn];

inline void solve(int n)
{
	for(int i = 1; i <= n; ++i)
	{
		scanf("%d%d%d%d", &qj[i].xl, &qj[i].yl, &qj[i].xr, &qj[i].yr);
		qj[i].num = i;//在读入时记录标号，方便打乱之后排回来
	}

	memset(have, 0, sizeof(have));//多组数据，注意初始化
	sort(qj+1, qj+n+1, cmp_x);
	for(int i = 1; i <= n; ++i)
	{
		int x = qj[i].xl;
		while(have[x] && x <= qj[i].xr)//找到第一个没有被选过的点
			x++;
		if(x > qj[i].xr)
		{
			puts("IMPOSSIBLE ");//udebeg上有空格，但不加似乎也能过
			return;
		}
		else
		{
			qj[i].x = x;
			have[x] = true;
		}
	}

	memset(have, 0, sizeof(have));
	sort(qj+1, qj+n+1, cmp_y);
	for(int i = 1; i <= n; ++i)
	{
		int y = qj[i].yl;
		while(have[y] && y <= qj[i].yr)
			y++;
		if(y > qj[i].yr)
		{
			puts("IMPOSSIBLE ");
			return;
		}
		qj[i].y = y;
		have[y] = true;
	}

	sort(qj+1, qj+n+1);//排回来
	for(int i = 1; i <= n; ++i)
		printf("%d %d\n", qj[i].x, qj[i].y);
}

int main()
{
	int n;
	while(scanf("%d", &n) == 1 && n)
		solve(n);
}
```

[在我的博客上查看](http://www.cnblogs.com/pfypfy/p/9062584.html)

---

## 作者：伟大的王夫子 (赞：4)

其实，这道题根本用不着什么模拟，只是最一般的贪心而已。

我们可以将这道题车的横坐标与纵坐标拆开来计算，那么问题就变成了：

给出 $n$ 个区间 $[a_i, b_i]$， 在每个区间内分别选一个点，试问能否选出这么 $n$ 个点，使得每个点不重合。

在这里，我要先说一下，不能按左端点排序，然后每次选可以选的最小的点。否则会被这样一组数据卡掉。

```
1 3
1 3
2 2
```
正确的做法应是按右端点从小到大排序（如果相同则按左端点从小到大），找到每次能选的最小的点进行选择。为什么这样是正确的？因为每次我们选出这个最小的点时，数组已经按照右端点从小到大排了序，所以说越小对于后继结点的影响越小。读者可以根据左端点大小关系进行分类讨论，这里留做一个思考题。

以下代码仅供参考。

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, ansx[5010], ansy[5010];
bool v[5010];
struct P {
	int x, y, id;
	bool operator < (const P &a) const {
		return y < a.y || (y == a.y && x < a.x);
	}
} a[5010], b[5010];
bool calc(P *a, int n, int *ans) {
	for (register int i = 1; i <= n; ++i) {
		int y = a[i].x;
		while (v[y] && y <= a[i].y) ++y;
		if (y == a[i].y + 1) return 0;
		ans[a[i].id] = y;
		v[y] = 1;
	}
	return 1;
}
int main() {
	while (~scanf("%d", &n) && n) {
		for (register int i = 1; i <= n; ++i) scanf("%d%d%d%d", &a[i].x, &b[i].x, &a[i].y, &b[i].y), a[i].id = b[i].id = i;
		memset(v, 0, sizeof v);
		sort(a + 1, a + n + 1);
		bool flag = calc(a, n, ansx);
		memset(v, 0, sizeof v);
		sort(b + 1, b + n + 1);
		flag &= calc(b, n, ansy);
		if (!flag) puts("IMPOSSIBLE");
		else {
			for (register int i = 1; i <= n; ++i) printf("%d %d\n", ansx[i], ansy[i]);
		}
	}
}
```

---

## 作者：小闸蟹 (赞：4)

```cpp
#include <iostream>
#include <array>
#include <algorithm>

constexpr int MaxN = 5000 + 5;
int n;

// 找到一个数组c[]，使得a[i] <= c[i] <= b[i] (0 <= i < n)
// 我懒得写出参数类型了所以弄了个template来偷懒
template <typename T>
bool Solve(const T &a, const T &b, T &c, int n) // 因为要修改c[]，所以这里是引用类型
{
    std::fill(c.begin(), c.begin() + n, -1);    // 将c[]初始化为全-1
    for (int Col = 1; Col <= n; ++Col)  // 遍历棋盘的第[1, n]列
    {
        // Rook是车的编号，MinB是能选的区间中最右边的点的最小值
        int Rook = -1, MinB = n + 1;
        for (int i = 0; i < n; ++i)
        {
            // 遍历每辆车的每个小区间：
            // 如果c[i]还没被安排点，因为任何两辆车不能在同一行或者同一列
            // 并且b[i]能在最右边的点的最小值的左边
            // 并且Col在左边的点的右边
            // 那就可以安排这第i辆车
            if (c[i] < 0 && b[i] < MinB && Col >= a[i])
            {
                Rook = i;       // 能安排第i辆车了
                MinB = b[i];    // 更新区间的最右边的点的最小值
            }
        }

        // 如果这一轮下来，Rook还是-1，即没被安排到车
        // 或者最左边的点跑得比最右边的点还要右
        // 那就说明并没有解
        if (Rook < 0 || Col > MinB)
        {
            return false;
        }

        // 给编号为Rook的车安排位置，安排在第Col列（行）
        c[Rook] = Col;
    }

    // 成功地安排好了位置
    return true;
}

int main()
{
    std::array<int, MaxN> x1{ 0 }, y1{ 0 }, x2{ 0 }, y2{ 0 }, x{ 0 }, y{ 0 };

    while (std::cin >> n && n)
    {
        for (int i = 0; i < n; ++i)
        {
            std::cin >> x1[i] >> y1[i] >> x2[i] >> y2[i];
        }

        // 这是一个贪心题：
        // 注意和n皇后不同，因为没有对角线的限制
        // 所以可以将一个二维的问题分解成了两个一维的问题
        // 然后贪心地选取对后面的车影响最小的坐标
        if (Solve(x1, x2, x, n) && Solve(y1, y2, y, n))
        {
            for (int i = 0; i < n; ++i)
            {
                std::cout << x[i] << ' ' << y[i] << std::endl;
            }
        }
        else
        {
            std::puts("IMPOSSIBLE");
        }
    }

    return 0;
}
```

---

## 作者：Chouquet (赞：2)

按照常规思路，一定是分解成两个一维问题：使 $1 \sim n$ 中每个数都在唯一的区间 $[l,r]$ 中（每个区间只能包含一个数）。如果一个车的横坐标能像上面一样做，纵坐标也能像上面那样做，那么这个车一定是符合题目要求的。

之后的贪心策略不好想。也许你会想要按照 $r$ 从大到小排序，再用一个 $O(n)$ 的倒序扫描完成问题：

```cpp
bool cmp (Seg a, Seg b) {
    if (a.r == b.r)
        return a.l < b.l;
    return a.r > b.r;
}
std::sort(a + 1, a + 1 + n, cmp);
int i = n, j = 1;
while (i >= 1 && j <= n) {
    if (a[j].l <= i && i <= a[j].r)
         rook[a[j].id] = i--;
     ++j;
}
if (i >= 1)
     return false;
else
    return true;
```

但对下面两个数据，无论 $l$ 怎么排都会输出错误结果，因为这不能保证一遍扫描时就能确定每个坐标：

```
#1:
[1,3],[1,3],[2,2]
#2:
[1,1],[3,4],[1,3],[2,3]
```

既然这样不行，那可以再尝试按照 $r$ 从小到大排序， $r$ 相同时 $l$ 从小到大排序，坐标从小到大扫描。这样对于每个坐标都可以选取占据空间尽量小的位置，让后面尽量都能选。这个也会遇到和上面同样的问题，所以需要用 $O(n^2)$ 算法，对于每个坐标都找所有的区间，第一个找到的区间就能包含它。用上面的方法，当横纵坐标都能找到时就说明有一组解。

```cpp
struct Seg {
    int l, r, id;//id表示这个区间是第几个输入的
};
bool cmp(Seg a, Seg b) {
    if (a.r == b.r)
        return a.l < b.l;
    return a.r < b.r;
}
int n;
bool vis[5003];
bool work(Seg a[], int rook[]) {//rook[id]表示区间id包含的坐标
    std::sort(a + 1, a + 1 + n, cmp);
    memset(vis, 0, sizeof vis);//用vis[id]表示区间id是否已用过
    int i = 1;
    while (i <= n) {
        bool found = 0;//found表示是否找到
        for (int j = 1; j <= n; j++)
            if (a[j].l <= i && i <= a[j].r && !vis[a[j].id]) {
                found = 1;
                rook[a[j].id] = i++, vis[a[j].id] = 1;
                break;
            }
        if (!found)
            return 0;
    }
    return 1;
}
```

完整代码不贴了。

---

