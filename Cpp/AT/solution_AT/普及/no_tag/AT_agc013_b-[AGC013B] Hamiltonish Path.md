# [AGC013B] Hamiltonish Path

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc013/tasks/agc013_b

$ N $ 頂点 $ M $ 辺の、連結な単純無向グラフが与えられます。 頂点には $ 1 $ から $ N $ までの番号がついており、辺には $ 1 $ から $ M $ までの番号がついています。 辺 $ i $ は、頂点 $ A_i $ と頂点 $ B_i $ を結んでいます。 次の条件を満たすパスを $ 1 $ つ見つけて、出力してください。

- $ 2 $ 個以上の頂点を通る
- 同じ頂点を $ 2 $ 度以上通らない
- パスの少なくとも一方の端点と直接辺で結ばれている頂点は、必ずパスに含まれる

ただし、この問題の制約の下で、このようなパスが必ず存在することが証明できます。 また、あり得る答えのうちどれを出力しても構いません。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^5 $
- $ 1\ \leq\ A_i\ <\ B_i\ \leq\ N $
- 与えられるグラフは連結かつ単純（どの $ 2 $ 頂点を直接結ぶ辺も高々 $ 1 $ つ）である

### Sample Explanation 1

頂点 $ 2 $ と直接辺で結ばれている頂点は、頂点 $ 3 $ と $ 4 $ です。 頂点 $ 4 $ と直接辺で結ばれている頂点は、頂点 $ 1 $ と $ 2 $ です。 なので、$ 2 $ → $ 3 $ → $ 1 $ → $ 4 $ というパスは条件を満たします。

## 样例 #1

### 输入

```
5 6
1 3
1 4
2 3
1 5
3 5
2 4```

### 输出

```
4
2 3 1 4```

## 样例 #2

### 输入

```
7 8
1 2
2 3
3 4
4 5
5 6
6 7
3 5
2 6```

### 输出

```
7
1 2 3 4 5 6 7```

## 样例 #3

### 输入

```
12 18
3 5
4 12
9 11
1 10
2 5
6 10
8 11
1 3
4 10
2 4
3 7
2 10
3 12
3 9
1 7
2 3
2 11
10 11```

### 输出

```
8
12 4 2 5 3 9 11 8```

# 题解

## 作者：小粉兔 (赞：11)

在博客园食用更佳：[https://www.cnblogs.com/PinkRabbit/p/AGC013.html](https://www.cnblogs.com/PinkRabbit/p/AGC013.html)。

考虑我们有一条经过 $k$ 个点的路径 $\{ u, a_2, a_3, \ldots , a_{k - 1}, v \}$，且其中 $a_1 = u$ 以及 $a_k = v$；

若此时 $v$ 还未满足相邻的点都在路径中的限制，任取一个相邻的不在路径中的点 $w$，将 $w$ 变为 $v$ 的下一个点，即 $a_{k + 1} = w$。

注意这样的过程一定会在有限步内结束，因为每次会多取一个点，而当取满所有 $N$ 个点时，限制一定会被满足。

此时 $v$ 已经满足其限制，对于 $u$ 来说同理，只不过是将新点变为 $u$ 的前一个点。用双端队列容易在 $\mathcal O (N + M)$ 的复杂度内维护。

```cpp
#include <cstdio>
#include <algorithm>
#include <vector>

const int MN = 100005;

int N, M;
std::vector<int> G[MN];
int vis[MN], A[MN], B[MN], C, D;

int main() {
	scanf("%d%d", &N, &M);
	for (int i = 1, x, y; i <= M; ++i) {
		scanf("%d%d", &x, &y);
		G[x].push_back(y);
		G[y].push_back(x);
	}
	A[C = 1] = 1;
	B[D = 1] = 1;
	vis[1] = 1;
	while (1) {
		int u = A[C], w = 0;
		for (int v : G[u]) if (!vis[v]) w = v;
		if (!w) break;
		vis[w] = 1, A[++C] = w;
	}
	while (1) {
		int u = B[D], w = 0;
		for (int v : G[u]) if (!vis[v]) w = v;
		if (!w) break;
		vis[w] = 1, B[++D] = w;
	}
	printf("%d\n", C + D - 1);
	for (int i = C; i >= 2; --i) printf("%d ", A[i]);
	for (int i = 1; i <= D; ++i) printf("%d%c", B[i], " \n"[i == D]);
	return 0;
}
```

---

## 作者：feecle6418 (赞：1)

# 这是一个假做法，但是能过（数据水了）

结论 $1$：一定存在一条合法路径的起点是图中度数最小的点。

结论 $2$：从这个度数最小的点开始以任意顺序 dfs 一遍整个图，一定能找到一种合法解。

我也不会证明这两个结论，但他就是过了……希望有神仙找到反例/给个证明 /kk

---

已经找到反例。

我的代码在如下数据会出错（结论 $2$ 有误）：

```
8 17
1 2
1 3
3 4
2 5
5 6
6 7
5 8
7 8
1 7
2 4
2 8
3 8
1 4
4 5
4 7
1 8
1 6
```


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans[300005],is[300005],v[300005],p;
vector<int> g[300005];
void dfs(int x){
	int flag=1;
	v[x]=is[x]=1,ans[++ans[0]]=x;
	for(int y:g[x])flag&=is[y];
	for(int y:g[p])flag&=is[y];
	if(flag){
		cout<<ans[0]<<endl;
		for(int i=1;i<=ans[0];i++)cout<<ans[i]<<' ';
		exit(0);
	}
	for(int y:g[x])if(!v[y])dfs(y);
	--ans[0],is[x]=0;
}
int main(){
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++)cin>>x>>y,g[x].push_back(y),g[y].push_back(x);
	int mn=1e9;
	for(int i=1;i<=n;i++)if(g[i].size()<mn)mn=g[i].size(),p=i;
	dfs(p);
}
```

---

