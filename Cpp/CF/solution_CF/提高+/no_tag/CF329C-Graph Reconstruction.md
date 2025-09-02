# Graph Reconstruction

## 题目描述

I have an undirected graph consisting of $ n $ nodes, numbered 1 through $ n $ . Each node has at most two incident edges. For each pair of nodes, there is at most an edge connecting them. No edge connects a node to itself.

I would like to create a new graph in such a way that:

- The new graph consists of the same number of nodes and edges as the old graph.
- The properties in the first paragraph still hold.
- For each two nodes $ u $ and $ v $ , if there is an edge connecting them in the old graph, there is no edge connecting them in the new graph.

Help me construct the new graph, or tell me if it is impossible.

## 说明/提示

The old graph of the first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329C/b1129560868ff844afcd23de4bd0225b3c2eaffb.png)

A possible new graph for the first example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329C/a236c3432a9690ef14f3805128dc6f4078063345.png)

In the second example, we cannot create any new graph.

The old graph of the third example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329C/0c623aea06e6e65528063142d300db01a6c49816.png)

A possible new graph for the third example:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF329C/a607e4e3b511cfdb5ff11751224f590048568b98.png)

## 样例 #1

### 输入

```
8 7
1 2
2 3
4 5
5 6
6 8
8 7
7 4
```

### 输出

```
1 4
4 6
1 6
2 7
7 5
8 5
2 8
```

## 样例 #2

### 输入

```
3 2
1 2
2 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5 4
1 2
2 3
3 4
4 1
```

### 输出

```
1 3
3 5
5 2
2 4
```

# 题解

## 作者：ZolaWatle (赞：2)

#### 题目大意

给出一张 $n$ 个顶点 $m$ 条边的无向图 $G$，保证每个点的度数不超过 $2$。你需要构造出一张同样每个点的度数不超过 $2$ 的 $n$ 个顶点 $m$ 条边的无向图 $G'$。设 $G=\{ V, E \}, G' = \{ V', E' \}$，你构造出的 $G'$ 应当满足 $V = V', E\bigcap E' = \emptyset$。

#### 解题思路

首先我们考虑什么样的无向图满足每个点的度数小于等于 $2$。很容易地想到，**链**和**环**满足这样的要求。由于本题有 $\text{spj}$，我们只需要给出一种合法方案，那就只需要构造出一条链或者一个环即可。

我们先对于环进行考虑。一张 $n$ 个顶点的无向图要是一个环，它将有且仅有 $n$ 条边。因此，对于 $n=m$ 的情况，我们考虑构造一个环。当 $m < n$ 时，我们则考虑构造一条链。由于题中保证了 $m\leq n$，因此不会出现其他的情况。

我们考虑随机生成一个排列 $a_i$，表示构造出的链的形式。这条链的形式如下：$a_1\rightarrow a_2, a_2\rightarrow a_3,\dots, a_{n-1}\rightarrow a_n$。然后分别判断这之中的每一条边在原图 $G$ 中是否出现过，如果没有，则满足了要求，输出前 $m$ 条边即可。对于 $n=m$（成环）的情况，还需要手动连上一条 $a_n\rightarrow a_1$，判断是否出现过。如果不满足要求，就多随机几次，如果随机的次数足够多，我们就认为是无解的。通过这样一种简单的方式，就可以满足题目的要求。

关于随机生成排列的方法，我们先初始化 $a_i$，使得 $\forall i\in[1, n], a_i=i$。然后不断地使用 $ \text{random}\_ \text{shuffle} $ 函数就行了。

#### 完整代码

```cpp
#include <bits/stdc++.h>
#define ll long long
#define re register int
#define rl register ll
#define rep(i,a,b) for(re i=(a),i##end=(b);i<=i##end;++i)
#define pre(i,a,b) for(re i=(a),i##end=(b);i>=i##end;--i)
#define mem(x,val) memset(x,val,sizeof(x))
using namespace std;

const int N=1e5+10;
int n,m,a[N],T=1e3;
map <int,int> hav[N];

inline int rint()
{
    re x=0,f=1; char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
    while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48); ch=getchar();}
    return x*f;
}

int main()
{
	n=rint(),m=rint();
	rep(i,1,m)
	{
		re x=rint(),y=rint();
		hav[x][y]=hav[y][x]=1;
	}
	
	rep(i,1,n) a[i]=i;
	while(T--)
	{
		random_shuffle(a+1,a+n+1);
		re flg=0;
		rep(i,2,n)
			if(hav[a[i-1]][a[i]])
			{
				flg=1;
				break;
			}
		if(n==m&&hav[a[n]][a[1]]) flg=1;
		if(!flg)
		{
			rep(i,2,min(m+1,n))
				printf("%d %d\n",a[i-1],a[i]);
			if(n==m) printf("%d %d",a[n],a[1]);
			return 0;
		}
	}
    
    printf("-1");
    return 0;
}
```

感谢阅读！

---

## 作者：Super_Cube (赞：1)

# Solution

由于 $m\le n$，那么原图的补图上的边会十分稠密，逼近完全图。

每个点度数不超过 $2$，那么必定为环或链构成答案。

如何生成链（$1\le m<n$）？考虑随机生成排列，将相邻位置对应元素连边，就只需要在过程中判断连边方式是否合法（即看原图中是否存在此边）。

环（$m=n$）的话就把刚刚链的做法拿过来，然后将排列的末尾元素向开头元素连边就可以了。

随机 $100$ 次基本是稳过的。

正确性？补图的边数为 $\dfrac{n(n-1)}{2}-m$，实在太多，很难随机不到正确答案。

# Code

```cpp
#include<bits/stdc++.h>
std::mt19937 rnd(time(0));
std::unordered_set<int>v[100005];
int a[100005];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;++i)
		scanf("%d%d",&x,&y),
		v[x].insert(y),v[y].insert(x);
	std::iota(a+1,a+n+1,1);
	for(int T=100,ok;T;--T){
		std::shuffle(a+1,a+n+1,rnd);
		ok=1;
		for(int i=1;i<n;++i)
			if(v[a[i]].count(a[i+1]))ok=0,i=n;
		if(n==m&&v[a[n]].count(a[1]))ok=0;
		if(ok){
			for(int i=1;i<n&&i<=m;++i)
				printf("%d %d\n",a[i],a[i+1]);
			if(n==m)
				printf("%d %d\n",a[n],a[1]);
			return 0;
		}
	}
	puts("-1");
	return 0;
}
```

---

## 作者：xyf007 (赞：1)

每个点的度数不超过 2，因此是一些链/环。注意到 $m \leq n$，因此反图极其稠密，可以随机一个排列，直接看相邻的是否可以连边。假如可以连的边大于等于 $m$ 就合法。如果随机很多次都不合法输出 `-1`。

标算有严谨的构造方法，但是相当复杂，而且 $n \leq 7$ 的时候还要暴力特判。这里不讲述，具体可以参考[官方题解](http://codeforces.com/blog/entry/8417)。
```cpp
#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <numeric>
#include <random>
#include <set>
#include <vector>
char Gc() {
  static char now[1 << 20], *S, *T;
  if (T == S) {
    T = (S = now) + std::fread(now, 1, 1 << 20, stdin);
    if (T == S) return EOF;
  }
  return *S++;
}
template <typename T>
void Read(T &x) {
  x = 0;
  int f = 1;
  char c;
  while ((c = Gc()) < '0' || c > '9')
    if (c == '-') f = -1;
  x = c - '0';
  while ((c = Gc()) >= '0' && c <= '9') x = x * 10 + (c - '0');
  x *= f;
}
template <typename T, typename... Args>
void Read(T &x, Args &... args) {
  Read(x);
  Read(args...);
}
template <typename T>
void checkmax(T &x, T y) {
  if (x < y) x = y;
}
template <typename T>
void checkmin(T &x, T y) {
  if (x > y) x = y;
}
std::size_t n, m, a[100001];
std::set<std::pair<std::size_t, std::size_t>> s;
std::vector<std::pair<std::size_t, std::size_t>> ans;
std::mt19937 mt_rand(
    std::chrono::_V2::steady_clock::now().time_since_epoch().count());
int main(int argc, char const *argv[]) {
  Read(n, m);
  for (std::size_t i = 1; i <= m; i++) {
    std::size_t u, v;
    Read(u, v);
    s.emplace(std::min(u, v), std::max(u, v));
  }
  std::size_t t = 3000000 / m;
  std::iota(a + 1, a + n + 1, 1);
  while (t--) {
    std::vector<std::pair<std::size_t, std::size_t>>().swap(ans);
    std::shuffle(a + 1, a + n + 1, mt_rand);
    a[0] = a[n];
    for (std::size_t i = 0; i < n; i++)
      if (!s.count({std::min(a[i], a[i + 1]), std::max(a[i], a[i + 1])}))
        ans.emplace_back(a[i], a[i + 1]);
    if (ans.size() < m) continue;
    for (std::size_t i = 0; i < m; i++)
      std::printf("%u %u\n", ans[i].first, ans[i].second);
    return 0;
  }
  std::printf("-1");
  return 0;
}
```

---

