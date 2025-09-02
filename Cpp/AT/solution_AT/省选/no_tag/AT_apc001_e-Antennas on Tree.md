# Antennas on Tree

## 题目描述

[problemUrl]: https://atcoder.jp/contests/apc001/tasks/apc001_e

$ N $ 頂点の木があります。 頂点には $ 0 $ から $ N\ -\ 1 $ まで番号が振られています。 また、$ i $ ($ 0\ <\ =\ i\ <\ N\ -\ 1 $) 番目の辺は頂点 $ a_i $ と $ b_i $ を結んでいます。 各頂点対 $ u $, $ v $ ($ 0\ <\ =\ u,\ v\ <\ N $) に対して、距離 $ d(u,\ v) $ を「パス $ u $-$ v $ に含まれる辺の本数」と定義します。

近い将来、いずれか $ 1 $ 個の頂点に宇宙人が襲来することが予想されています。 すぬけ君は、宇宙人が襲来したときにその頂点をすぐに特定したいと考えています。 そのために、あらかじめいくつかの頂点にアンテナを設置しておくことにしました。

まず、アンテナの個数 $ K $ ($ 1\ <\ =\ K\ <\ =\ N $) を自由に決めます。 そして、すべて相異なる $ K $ 個の頂点 $ x_0 $, $ x_1 $, ..., $ x_{K\ -\ 1} $ を自由に選び、各頂点にアンテナ $ 0 $, $ 1 $, ..., $ K\ -\ 1 $ を設置します。 頂点 $ v $ に宇宙人が襲来すると、アンテナ $ k $ ($ 0\ <\ =\ k\ <\ K $) は距離 $ d(x_k,\ v) $ を出力します。 すぬけ君は、これら $ K $ 個の出力結果をもとに、宇宙人が襲来した頂点を特定します。 よって、どの頂点に宇宙人が襲来してもその頂点を一意に特定するためには、次の条件が成り立つ必要があります。

- 各頂点 $ u $ ($ 0\ <\ =\ u\ <\ N $) に対してベクトル $ (d(x_0,\ u),\ ...,\ d(x_{K\ -\ 1},\ u)) $ を考えたとき、これら $ N $ 通りのベクトルはすべて相異なる。

条件を満たすようにアンテナを設置するとき、アンテナの個数 $ K $ の最小値を求めてください。

## 说明/提示

### 制約

- $ 2\ <\ =\ N\ <\ =\ 10^5 $
- $ 0\ <\ =\ a_i,\ b_i\ <\ N $
- 与えられるグラフは木である。

### Sample Explanation 1

例えば、頂点 $ 1 $, $ 3 $ にアンテナを設置すればよいです。 このとき、次の $ 5 $ 通りのベクトルはすべて相異なります。 - $ (d(1,\ 0),\ d(3,\ 0))\ =\ (1,\ 1) $ - $ (d(1,\ 1),\ d(3,\ 1))\ =\ (0,\ 2) $ - $ (d(1,\ 2),\ d(3,\ 2))\ =\ (2,\ 2) $ - $ (d(1,\ 3),\ d(3,\ 3))\ =\ (2,\ 0) $ - $ (d(1,\ 4),\ d(3,\ 4))\ =\ (3,\ 1) $

### Sample Explanation 2

例えば、頂点 $ 0 $ にアンテナを設置すればよいです。

### Sample Explanation 3

例えば、頂点 $ 0 $, $ 4 $, $ 9 $ にアンテナを設置すればよいです。

## 样例 #1

### 输入

```
5
0 1
0 2
0 3
3 4```

### 输出

```
2```

## 样例 #2

### 输入

```
2
0 1```

### 输出

```
1```

## 样例 #3

### 输入

```
10
2 8
6 0
4 1
7 6
2 3
8 6
6 9
2 4
5 8```

### 输出

```
3```

# 题解

## 作者：是个汉子 (赞：4)

[洛谷传送门](https://www.luogu.com.cn/problem/AT3912)	[AT传送门](https://www.luogu.com.cn/remoteJudgeRedirect/atcoder/3912)

### description

有一棵 $n$ 个节点的树，无边权。

选择 $k$ 个点。树上每个点到这 $k$ 个点的距离构成一个 $k$ 维坐标。

求得最小的 $k$ 使得每个坐标都不相同。

### Solution

考虑什么情况下两个坐标会相同？

对于某一个点为根时，有两个不同的子树中没有选择点，则这个两个子树的根的坐标相同。

也可以表示为：任何一个点为根时，都**最多**只有一颗子树中没有选择点。

假设我们已经选出了这 $k$ 个点，那么如果将这 $k$ 个点和它们之间的路径单独拎出来，可以发现这也是一棵树。而且这棵树的叶子结点是选出的 $k$ 个点。

那么这个题的解法就出来了(≧∇≦)ﾉ

我们从原树中的所有度为 $1$ 的点往上走，碰到度 $>2$ 的停下来并打上标记。

因为有一颗子树可以没有选择点，所有将叶子数减去有标记的点就是答案了。

（配合代码观看可能更佳\^o^/）

注意：当原树是一条链的时候注意特判，此时没有标记点，但是起码要选择一个点。

### Code

```c++
#include<vector>
#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>

using namespace std;
const int N=100010;
int n,ans;
vector<int> vec[N];
bool vis[N];

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while(!isdigit(ch)){if(ch=='-') f=-1;ch=getchar();}
    while(isdigit(ch)){x=x*10+(ch^48);ch=getchar();}
    return x*f;
}

int dfs(int u,int fa){
    if(vec[u].size()>2) return u;
    for(int v:vec[u]) if(v!=fa) return dfs(v,u);
    return u;
}//向上走的过程

int main(){
    n=read();
    for(int i=1,u,v;i<n;i++)
        u=read()+1,v=read()+1,vec[u].push_back(v),vec[v].push_back(u);
    for(int i=1;i<=n;i++)
        if(vec[i].size()==1) vis[dfs(i,0)]=true,ans++;
    for(int i=1;i<=n;i++)
        if(vis[i]) ans--;//有标记就减去
    if(!ans) puts("1");//特判
    else printf("%d\n",ans);
    return 0;
}
```



---

## 作者：LinkyChristian (赞：3)

> 有一棵 $n$ 个节点的树，无边权。
选择 $k$ 个点。树上每个点到这 $k$ 个点的距离构成一个 $k$ 维坐标。
求得最小的 $k$ 使得每个坐标都不相同。

考虑随便设定一个节点为根。两个节点的坐标不相同当且仅当一个有两个及以上儿子的节点，其子树内没有被选定的点，因此其他点到他的两个儿子的距离都是相同的。

考虑选定两个节点之后，这两个节点之间的链都可以表示出来。因此选定两个节点后，如果两个节点可以向两端拓展，那么拓展之后表达的范围一定不会更小，因此选定的节点一定是原树中度数为 1 的叶节点。

考虑先选定所有的叶节点。同上，如果一个节点的度数大于 2 ，即其儿子大于 1，那么一定需要至少一个选定的节点。但是其有一个儿子可以不选，通过其他儿子中的点用排除法表示出来。因此每个度数大于 2 的节点可以提供一个不选的机会，dfs 搜索从每个叶子节点出来遇到的第一个度数大于 2 的节点，将其打上标记，之后用总的叶节点数减去打上标记的节点数量即可。

---

## 作者：封禁用户 (赞：1)

### 思路

可以发现，如果两个点的距离为奇数，那么显然是可以区分开的。

如果为偶数，那么设这两个点为 $a$，$b$ 中点为 $c$， 显然必须要存在一个 $x_i$，满足当以 $c$ 为根的时候，$x_i$ 和 $a$ 或 $b$ 在同一棵子树里。

换句话说，以任何一个点作为根的时候，都至多有一棵子树内部没有 $x_i$。

我们一遍 DFS 就可以完成这个操作，但要注意的是，我们要考虑父节点方向是否有 $x_i$，这就很麻烦了。

于是我们从一个度数 $\ge 3$ 的节点开始 DFS，也就保证了父节点方向一定有 $x_i$。

### CODE


```cpp
#include<bits/stdc++.h>
#define R register
#define IN inline
#define W while
#define gc getchar()
#define MX 100500
template <class T>
IN void in(T &x)
{
	x = 0; R char c = gc;
	for (; !isdigit(c); c = gc);
	for (;  isdigit(c); c = gc)
	x = (x << 1) + (x << 3) + c - 48;
}
int n;
std::vector <int> nex[MX];
IN void add(R int from, R int to) {nex[to].push_back(from);}
int dp[MX];
void DFS(R int now, R int fa)
{
	bool fir = false;
	for (auto i : nex[now])
	{
		if (i == fa) continue;
		DFS(i, now);
		dp[now] += dp[i];
		if (!dp[i]) fir ? dp[now]++ : fir = true;
	}
}
int main(void){
	in(n);
  	int foo, bar, rt = -1;
	for (R int i = 1; i < n; ++i){
		in(foo), in(bar), add(foo, bar), add(bar, foo);
	}
	
	for (R int i = 0; i < n; ++i){
		if (nex[i].size() > 2){
			rt = i;
			break;
		}
	}
	if (~rt){
		DFS(rt, -1), printf("%d", dp[rt]);
	}
	else puts("1"); 
}
```

---

