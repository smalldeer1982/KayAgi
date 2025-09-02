# Orientation of Edges

## 题目描述

Vasya 拥有一张由有向边和无向边组成的图。这张图中，两个顶点之间可能存在多条边。

Vasya 从中选定了一个顶点 $s$。现在，他希望制定两个不同的方案：

1. 将每条无向边指定一个方向，以最大化从顶点 $s$ 可以到达的其他顶点数量；
2. 将每条无向边指定一个方向，以最小化从顶点 $s$ 可以到达的其他顶点数量。

在每个方案中，所有无向边都必须变为有向边。同一条无向边可以在两个方案中选择不同的方向。

你的任务是帮助 Vasya 找出这两个方案。

## 样例 #1

### 输入

```
2 2 1
1 1 2
2 2 1
```

### 输出

```
2
-
2
+
```

## 样例 #2

### 输入

```
6 6 3
2 2 6
1 4 5
2 3 4
1 4 1
1 3 1
2 2 3
```

### 输出

```
6
++-
2
+-+
```

# 题解

## 作者：DPair (赞：3)

题解连更计划第6篇

## 【思路】
这道题还是比较水的，没什么思想难度（就码量大一点）。

首先，我们很容易想到先用所有有向边推出**一定能到达的点**，那么剩下的点肯定都是**只能通过无向边到达的点**。

于是很简单，要最大化能到达的点数，以所有**一定能到达的点**，为起点，经过所有**能扩展到其他点**的无向边，达到最大化的效果。

反过来说，要最小化这个点数，就把上面的所有无向边改成不经过，也就是建反边（当然并不是直接全部取反），是为了使得**一定能到达的点**一定不能到达**只能通过无向边到达的点**。

然后就好了。

说的形象一点，就是要最大化能到达的点数，就是“开门”，让**一定能到达的点**有出路，而最小化就是“关门”，把出路封死。

于是，跑两边$bfs$，每一次特判一下，这道题就做完了。

## 【代码】
码量比较大，但鉴于两次$bfs$本质基本相同，于是可以直接$ctrl+C+ctrl+V$，然后稍事改动。

```cpp
#include <bits/stdc++.h>
using namespace std;

template <typename T>
inline void read(T &x)
{
    char c;
    x = 0;
    int fu = 1;
    c = getchar();
    while(c > 57 || c < 48)
    {
        if(c == 45)
        {
            fu = -1;
        }
        c = getchar();
    }
    while(c <= 57 && c >= 48)
    {
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x)
{
    if(x < 0)
    {
        putchar(45);
        x = -x;
    }
    if(x > 9)
    {
        fprint(x / 10);
    }
    putchar(x % 10 + 48);
}

int n, m, s, tot;
int ans[300010], cnt, vis[300010];

struct EDGE{
	int e, num, val;
	EDGE (int tmp1, int tmp2, int tmp3) : e(tmp1), num(tmp2), val(tmp3) {}
}; 
vector <EDGE> ude[300010];
vector <int> de[300010];
queue <int> q;

void work1()
{
	cnt = 1;
	memset(ans, 0, sizeof(ans));
	memset(vis, 0, sizeof(vis));
	q.push(s);
	while(!q.empty())
	{
		int tp = q.front();
		q.pop();
		vis[tp] = true;
//		printf("WORK %d\n", tp);
		for (register int i = 0;i < de[tp].size();i ++)
		{
			int _e = de[tp][i];
			if(!vis[_e])
			{
				cnt ++;
				vis[_e] = true;
				q.push(_e);
//				printf("PUSH D %d\n", _e);
			}
		}
		for (register int i = 0;i < ude[tp].size();i ++)
		{
			int _e = ude[tp][i].e, _num = ude[tp][i].num, _val = ude[tp][i].val;
			if(!vis[_e] && ans[_num] != -_val)
			{
				ans[_num] = _val;
				cnt ++;
				vis[_e] = true;
//				printf("PUSH UD %d\n", _e);
				q.push(_e);
			}
		}
	}
	fprint(cnt);
	putchar('\n');
	for (register int i = 1;i <= tot;i ++)
	{
		putchar(ans[i] == 1? '+':'-');
	}
	putchar('\n');
}

void work2()
{
	cnt = 1;
	memset(ans, 0, sizeof(ans));
	memset(vis, 0, sizeof(vis));
	q.push(s);
	while(!q.empty())
	{
		int tp = q.front();
		q.pop();
		vis[tp] = true;
//		printf("WORK %d\n", tp);
		for (register int i = 0;i < de[tp].size();i ++)
		{
			int _e = de[tp][i];
			if(!vis[_e])
			{
				cnt ++;
				vis[_e] = true;
				q.push(_e);
//				printf("PUSH D %d\n", _e);
			}
		}
		for (register int i = 0;i < ude[tp].size();i ++)
		{
			int _e = ude[tp][i].e, _num = ude[tp][i].num, _val = ude[tp][i].val;
			if(ans[_num] != _val)
			{
				ans[_num] = -_val;
			}
		}
	}
	fprint(cnt);
	putchar('\n');
	for (register int i = 1;i <= tot;i ++)
	{
		putchar(ans[i] == 1? '+':'-');
	}
	putchar('\n');
}

int main()
{
	read(n);
	read(m);
	read(s);
	while(m --)
	{
		int opt, u, v;
		read(opt);read(u);read(v);
		if(opt == 1)
		{
			de[u].push_back(v);
		}
		else
		{
			ude[u].push_back(EDGE(v, ++ tot, 1));
			ude[v].push_back(EDGE(u, tot, -1));
		}
	}
	work1();
	work2(); 
} 
```

---

