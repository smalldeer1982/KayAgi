# [SEERC 2020] 3-colorings

## 题目描述

**这是一道仅有输出的题。**

定义一个图的有效“三色”染色为：

- 每个点的颜色只能属于 $\{1,2,3\}$。

- 对于每个有边相连的顶点 $(u,v)$，$u$ 的颜色需要与 $v$ 不同。

可以证明，一个图最多的“三色”染色总数为 $3^n$ 种。

现在你需构造一个图，一开始它存在 $n \ (1 \leq n \leq 19)$ 个顶点 $m \ (1 \leq m \leq \frac{n(n-1)}{2})$ 条无向边，然后对于每个 $1 \leq k \leq 500$ 的 $k$，你可以添加至多 $17$ 条无向边使得此图的“三色”染色总数为 $6k$ 种。

## 说明/提示

样例仅给出 $k=1$ 和 $k=2$ 的示例。

## 样例 #1

### 输入

```
```

### 输出

```
3 2
1 2
2 3
1
1 3
0```

# 题解

## 作者：oMin0 (赞：3)

## 分析

小清新神秘构造题。

数据范围给得相当精准，感觉就是要大胆猜出做法。

首先观察一些基本结构，一个三元环方案数是 $6$，一条链染色方案数是 $3\times 2^{len-1}$，这时你已经能发现最终图里只有一个连通块，否则方案数是 $3^2$ 的倍数。

然后不妨想到先给 $1,2,3$ 连一个三元环并钦定它们的颜色分别就是 $1,2,3$，这样只需让其它点的方案数恰好是 $k$ 即可。然后根据数据范围必然想到二进制拆分，这时关键问题是我们需要让方案数加起来而不是乘起来，再进行一些尝试后能得到下面这种结构：

- 对一条链进行改造，我们额外对链上的第 $i$ 个点与 $(i-1)\bmod 3+1$ 连边，这样一来方案数变成了 $len+1$，因为每种方案都是对一个前缀（可以为空）染成 $(i\bmod 3)+1$，对其余点染成 $(i+1)\bmod 3+1$。

这种结构的好处是把总方案数变成了若干部分的和，回到题目要求中来，我们把 $4\sim 11$ 造成这种结构，然后把 $12\sim 19$ 挂到上面即可完成二进制拆分，因为可以控制使得后缀方案数总是 $1$，前缀方案数是 $2$ 的若干次幂。

还有一些细节：比如我们有时要给空前缀挂点，这可以通过直接与 $1$ 连边实现；比如我们其实希望总方案数是 $\text{popcount}(k)$ 个部分的和，因此有时需要对 $4\sim 11$ 额外连一条边，以强制一段后缀染成 $(i+1)\bmod 3+1$。

具体实现见代码。

## 代码

```cpp
/*
  author: honglan0301
  Sexy_goodier _ xiaoqing
 */
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cctype>
#include <queue>
#include <map>
#include <unordered_map>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <cmath>
#include <random>
#include <set>
#include <bitset>
#include <assert.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define endl "\n"

int n=19;
vector <pair<int,int>> cs;
#define lowbit(x) (x&(-x))

signed main()
{
	cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);
	cs.pb(mp(0,1)); cs.pb(mp(1,2)); cs.pb(mp(2,0));
	for(int i=3;i<=10;i++) cs.pb(mp(i%3,i));
	for(int i=3;i<10;i++) cs.pb(mp(i,i+1));
	cout<<n<<" "<<cs.size()<<endl;
	for(auto i:cs) cout<<i.fi+1<<" "<<i.se+1<<endl;
	for(int i=1;i<=500;i++)
	{
		vector <pair<int,int>> nb;
		int ni=i,nx=3,ny=11; 
		if(1)
		{
			int dd=__lg(lowbit(ni));
			for(int j=1;j<=dd;j++) nb.pb(mp(0,ny)),ny++; ni>>=(dd+1);
		}
		while(ni)
		{
			int dd=__lg(lowbit(ni)); 
			for(int j=1;j<=dd+1;j++) nb.pb(mp(nx,ny)),nb.pb(mp((nx+1)%3,ny)),ny++; ni>>=(dd+1); nx++;
		}
		if(nx<=10) nb.pb(mp((nx+1)%3,nx));
		for(int j=ny;j<=18;j++) nb.pb(mp(0,j)),nb.pb(mp(1,j));
		cout<<nb.size()<<endl;
		for(auto i:nb) cout<<i.fi+1<<" "<<i.se+1<<endl;
	}
}
```

---

## 作者：Imakf (赞：1)

这个题比较神秘，或者说我的做法比较神秘。

首先我们发现 $k \le 500$，这暗示我们可以打表。但打表也不可以凭空，所以我们先研究一些特殊图。

首先树的三染色方案就是 $3\cdot 2^{n-1}$，因为确定一个点之后剩下的可以一一确定。所以说树不太行，它生成的答案不够**随机**。同时若干个不同的连通块之间，答案是乘起来的，看起来也造不出质数。

但是一个环的方案可以用 dp 或者容斥求出。容斥引入了加法减法，也许能凑出质数。这启发我们尝试在环的基础上生成出 $1\sim 500$ 的所有答案：

- 一开始的图是 $n$ 个点的环；
- 然后我们随机一个边数 $m$，往环上添加这么多条边；
- 计算出染色方案数，如果落在 $[1,500]$ 则把答案记下。

$n$ 较大时计算速度会较慢，$n$ 较小时有可能随机不出一些刁钻的答案，于是我们选择 $n=14$。

新加边数 $m$ 也会影响随机出的答案分布，边数较小时答案可能很大，所以我们选择 $m$ 在 $6\sim 17$ 中随机，同时加大随机到 $17$ 的权重（我们期望越复杂的图会生成尽可能多的答案）。

计算染色方案数可以直接子集 dp，复杂度 $O(3\cdot 3^n+m)$。

可以考虑使用多线程加速打表。但注意线程数不要超过 cpu 核心数。本机多线程运行了 5 分钟即求出了所有结果；单线程时间也不会超过 30 分钟。

对于打出来的表，如何进行压缩？考虑一条边 $(u,v)$ 可以压缩成一个长度为 $2$ 的字母串（$|\Sigma|= 26 > 14$），对于一个 $k$ 的答案就可以压缩成长 $2m$ 的字符串。加上引号和逗号需要 $2m+3$ 个字符。也就是最坏情况下表的大小为 18.50KB，可以提交！最后实际运行出来表大小为 9.35KB。

```cpp
#include <bits/stdc++.h>
using namespace std;

vector<string> ans = {/*表，略去*/};
int main() {
	int n = 14;
	vector < pair <int, int> > e;
	for (int i = 0; i < n; ++i) {
		e.push_back({i + 1, (i + 1) % n + 1});
	}
	cout << n << ' ' << e.size() << '\n';
	for (auto [x, y] : e) {
		cout << x <<  ' ' << y << '\n';
	}
	for (auto i : ans) {
		set < pair <int, int> > S;
		for (int i = 0; i < n; ++i) {
		S.insert({i + 1, (i + 1) % n + 1});
	}
	vector < pair <int, int>> output;
		for (int j = 0; j < i.size(); j += 2) {
			int x, y;
			x =  i[j] - 'a', y = i[j + 1] - 'a';
			if (!S.count({x, y}) && !S.count({y, x})) output.push_back({x, y});
		}
		cout << output.size() << endl;
		for (auto [x, y] : output) cout << x << ' ' << y << '\n';
	}
}
```

---

