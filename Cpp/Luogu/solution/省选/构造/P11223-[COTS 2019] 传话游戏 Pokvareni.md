# [COTS 2019] 传话游戏 Pokvareni

## 题目背景


译自 [Izborne Pripreme 2019 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2019/) D1T3。$\texttt{1s,0.5G}$。

## 题目描述

**提示**：搬题人在题面的最后提供了简要题意。

老师带着 $N$ 个小朋友玩传话游戏。他们都知道同样的 $M$ 个单词，我们不妨编号为 $1\sim M$。

游戏进行方式是这样的：

- 小朋友们被排成一列；
- 老师对第一个小朋友耳语单词 $1$；
- 对于 $1\le i\lt N$，第 $i$ 个小朋友对第 $(i+1)$ 个小朋友耳语听到的词；
- 第 $N$ 个小朋友大声说出他听到的词。

由于当时旁边有 OIer 在大力敲打键盘，游戏受到了干扰，小朋友常常听错词。但是，神奇的是，对于第 $i$ 个小朋友，无论谁对他耳语，以及他在队列中的哪个位置，对他耳语相同的词 $A$，他都会听到相同的词 $B$（$A=B$ 是可能的）。

老师重复进行了 $N!$ 局游戏，每种排列都试了一次。她注意到，有一个词恰好被大声说出 $K$ 次。老师很好奇，于是找来了你，来复现这样的情况。

具体地说，给定整数 $N,K$。构造正整数 $M,X$，以及一种小朋友误听单词的方式，使得在 $N!$ 局游戏中，$X$ 恰好被大声说出 $K$ 次。

找到的 $M$ 越小，得分越高，详见【计分方式】。

**简单地说**：给定 $N,K$。构造 $N$ 个 $[1,M]\to [1,M]$ 的函数 $f_1(x),f_2(x),\ldots,f_{N}(x)$（$M$ 是你选定的正整数），使得：

- 令 $p_1,p_2,\ldots,p_N$ 取遍 $N!$ 个 $1\sim N$ 的排列；
	- 将 $N!$ 种排列 $p$ 中，$f_{p_N}(f_{p_{N-1}}\cdots(f_{p_2}(f_{p_1}(1)))\cdots)$ 取到的值放入**多重集** $S$。则存在 $X\in S$，使得 $X$ **恰好**在 $S$ 中出现 $K$ 次。

这里，$[1,M]$ 指的是 $[1,M]\cap \mathbb{Z}$。

目标是使 $M$ 尽量小。


## 说明/提示


对于 $100\%$ 的数据，保证：

- $\mathrm{id}\in \{1,2\}$；
- $1\le N\le 12$；
- $0\le K\le N!$；
- $1\le T\le 10$。

【计分方式】

本题分为两个子任务计分。

- Subtask $1$（$30$ pts）：保证 $1\le N\le 7$。

    只要构造方案合法，就能获得满分。否则得 $0$ 分。
- Subtask $2$（$70$ pts）：保证 $1\le N\le 12$。
    
    如果输出不合法，得 $0$ 分。

    否则单组测试数据得分为 $70\cdot k$，$k$ 按照下式计算：

    $$k=
    \begin{cases}
    \displaystyle 1, & M\le N+1 \\
    \displaystyle 0.7 + \frac{0.15}{M-N-1}\, \in [0.7,0.85], & N+1\lt M\le N+5 \\
    \displaystyle 0.5 + 0.05 \left(5-\frac{M}{N}\right) \, \in[0.5,0.7], & N+5\lt M\le 5\cdot N \\
    \displaystyle \frac{0.5}{\log_{10}(M/5N)+1}\, \in [0,0.5]& 5\cdot N\lt M\le 10^4 \\

    \end{cases}
    $$
    
    单个测试点得分是所有测试数据中得分的最小值。例如，样例 $2$ 的两组数据的 $k$ 分别为 $0.77,1$。该输出得 $0.7\cdot  70$ 分。

## 样例 #1

### 输入

```
1
2
3 2
2 1```

### 输出

```
3 3
2 1 3
3 2 2
1 3 2
2 1
1 1
2 2```

## 样例 #2

### 输入

```
2
2
3 3
4 0```

### 输出

```
6 2
1 2 3 4 5 6
6 5 4 3 2 1
2 4 1 4 3 2
2 2
1 1
1 1
1 1
1 1```

# 题解

## 作者：zyh_helen (赞：1)

不算太难但很有意思的一道题，这里提供一下我的构造方法。

---
---

考虑限制给到了 $m\le n+1$，我们直接取满。

我们确定两个状态使其一部分情况最终到这个值，另一部分状态最终到另一个值，这两个值封闭；为了最小化影响，我们直接使这两个值分别为 $n$ 和 $m$（即第 $n$ 行都是 $n$，第 $m$ 行都是 $m$）。

---

我们手模一下小数据找找灵感，$k=0$ 的时候我们显然直接让 $n$ 这个值无法到达就行了；但 $k=1$ 就不那么好办了，我们要构造出来一条路径经过所有值一次，相当于确定出一个排列，大概就是这样（拿 $n=8$ 举个例子）：

```
2 9 9 9 9 9 9 8 9
9 3 9 9 9 9 9 8 9
9 9 4 9 9 9 9 8 9
9 9 9 5 9 9 9 8 9
9 9 9 9 6 9 9 8 9
9 9 9 9 9 7 9 8 9
9 9 9 9 9 9 8 8 9
9 9 9 9 9 9 9 8 9
```

显然只能沿着不是 $m$ 的数一路走到 $n$。

---

我们沿着 $k=1$ 继续想，如果第 $i$ 列的某个值给到了 $n$，那么相当于走到该值后的 $n-i$ 个操作随意排列，即给答案增加了 $(n-i)!$，同时注意到第 $i$ 列还剩下 $n-i+1$ 个值都可以自由改动（其他的值在此之前都被调用过了），也就是在第 $i$ 行 $k\in[0,(n-i+1)!]$ 都可以被处理（如果用 $(n-i)!$ 处理完还有剩余就像 $k=1$ 一样引导其走到下一列再处理）。

易证 $\forall k \in [0,n!]$ 可以处理。

---
---

代码实现不难，注意特判 $n=1,k=0$ 的情况。

```cpp
#include<bits/stdc++.h>
//#include<Windows.h>
#define int long long
//#define ll long long
#define double long double
#define fi first
#define se second
//#define ls t[p].l
//#define rs t[p].r
#define y1 yyyyyyyyyyyyyyyy1
using namespace std;
const int N = 3e5 + 10, inf = 1e12, M = 101;
const double eps = 1e-14, pi = 3.1415926, kou = 0.577215669902;
const int mod = 1e9 + 7;
//const int AQX = 9;
mt19937 rnd(time(0) ^ clock());
int random(int l, int r){
	return rnd() % (r - l + 1) + l;
}
/*
		    	           _      _        _          
			       ____  _| |_   | |_  ___| |___ _ _  
			      |_ / || | ' \  | ' \/ -_) / -_) ' \ 
			      /__|\_, |_||_|_|_||_\___|_\___|_||_|
			          |__/    |___|                              
				       
*/
//struct Graph{
//	int head[N], tot = 1;
//	struct edge{
//		int t;
//		int d, fa, f;
//		int next;
//	}e[N << 1];
//	void edge_add(int u, int v, int w = 0){
//		e[++tot].next = head[u];
//		e[tot].t = v;
//		e[tot].d = w;
//		e[tot].f = u;
//		head[u] = tot;
//	}
//	void clear(int n){
//		for(int i = 1;i <= tot;i++)e[i].t = e[i].f = e[i].d = e[i].next = 0;
//		for(int i = 1;i <= n;i++)head[i] = 0;
//		tot = 0;
//	}
//}g;
//int qmr(int x, int a){
//	int ret = 1, p = x;
//	while(a){
//		if(a & 1)ret = ret * p % mod;
//		p = p * p % mod;
//		a >>= 1;
//	}
//	return ret;
//}


int n, k, jc[N], ans[20][20];
signed main(){
	int T, lsj;
	cin >> lsj >> T;
	jc[0] = 1;
	for(int i = 1;i <= 12;i++)jc[i] = jc[i - 1] * i % mod;
	while(T--){
		cin >> n >> k;
		if(n == 1 && k == 0){
			cout << 2 << " " << 2 << endl;
			printf("1 1\n");
			continue;
		}
		cout << n + 1 << " " << n << endl;
		for(int i = 1;i < n;i++){
			int p = jc[n - i], j = n;
			for(;k >= p;k -= p, j--)ans[i][j] = n;
			for(;j;j--)ans[i][j] = n + 1;
			if(k)ans[i][i] = i + 1;
		}
		for(int i = 1;i <= n;i++){
			for(int j = 1;j < n;j++)printf("%lld ", ans[j][i]);
			printf("%lld %lld\n", n, n + 1);
		}
	}
	return 0;
}

---

