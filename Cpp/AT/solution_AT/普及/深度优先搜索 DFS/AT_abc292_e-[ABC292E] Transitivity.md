# [ABC292E] Transitivity

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc292/tasks/abc292_e

頂点に $ 1 $ から $ N $ の番号が、辺に $ 1 $ から $ M $ の番号がついた $ N $ 頂点 $ M $ 辺の単純有向グラフが与えられます。辺 $ i $ は頂点 $ u_i $ から頂点 $ v_i $ への有向辺です。

また、あなたは次の操作を $ 0 $ 回以上何度でも行えます。

- 相異なる頂点 $ x,y $ であって頂点 $ x $ から頂点 $ y $ への有向辺が存在しないようなものを選ぶ。そして、頂点 $ x $ から頂点 $ y $ への有向辺を追加する。

このグラフが次の条件を満たす状態にするために最小で何回操作を行う必要があるかを求めてください。

- 相異なる頂点 $ a,b,c $ すべてについて、頂点 $ a $ から頂点 $ b $ への有向辺と頂点 $ b $ から頂点 $ c $ への有向辺がともに存在するならば頂点 $ a $ から頂点 $ c $ への有向辺も存在する。

## 说明/提示

### 制約

- $ 3\ \leq\ N\ \leq\ 2000 $
- $ 0\ \leq\ M\ \leq\ 2000 $
- $ 1\ \leq\ u_i\ ,v_i\ \leq\ N $
- $ u_i\ \neq\ v_i $
- $ i\ \neq\ j $ ならば $ (u_i,v_i)\ \neq\ (u_j,v_j) $
- 入力はすべて整数

### Sample Explanation 1

初め、一例として頂点 $ 2,4,3 $ について、頂点 $ 2 $ から頂点 $ 4 $ への有向辺と頂点 $ 4 $ から頂点 $ 3 $ への有向辺がともに存在するにもかかわらず、頂点 $ 2 $ から頂点 $ 3 $ への有向辺は存在せず、条件を満たさない状態です。 そこで、以下の $ 3 $ 本の有向辺を追加すると条件を満たす状態になります。 - 頂点 $ 2 $ から頂点 $ 3 $ への有向辺 - 頂点 $ 2 $ から頂点 $ 1 $ への有向辺 - 頂点 $ 4 $ から頂点 $ 1 $ への有向辺 一方、$ 3 $ 本未満の追加で条件を満たす状態には出来ないため、答えは $ 3 $ です。

## 样例 #1

### 输入

```
4 3
2 4
3 1
4 3```

### 输出

```
3```

## 样例 #2

### 输入

```
292 0```

### 输出

```
0```

## 样例 #3

### 输入

```
5 8
1 2
2 1
1 3
3 1
1 4
4 1
1 5
5 1```

### 输出

```
12```

# 题解

## 作者：zhlzt (赞：6)

### 题目
- 有 $n$ 个顶点。
- 有 $m$ 条有向边。
- 第 $i$ 条有向边是 $(u_i,v_i)$。
- 若存在有向边 $(a,b)$ 和 $(b,c)$，则必须存在有向边 $(a,c)$。
- 求至少添加几条边使有向图满足条件。
- $3\le n\le 2000$，$0\le m\le2000$，$1\le u_i,v_i\le n$。
- $u_i\ne v_i$，若 $i\ne j$ 则 $(u_i,v_i)\ne(u_j,v_j)$。

### BFS 做法
![](https://cdn.luogu.com.cn/upload/image_hosting/6sdvdxg1.png)

最初，有三条有向边 $(a,b),(b,c),(c,d)$。

因为存在有向边 $(a,b),(b,c)$，所以添加有向边 $(a,c)$。

因为存在有向边 $(a,c),(c,d)$，所以添加有向边 $(a,d)$。

如上是需要添加的从 $a$ 出发的有向边。

由此可得出结论：对于一个点 $x$，它必须和从自己出发能够到达的所有点（除去自己本身和能直接到达的点）连有向边。

### 代码实现
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,x,y,ans,vis[2010];
vector<int>edge[2010];
int bfs(int s){
	memset(vis,0,sizeof(vis));
	queue<int>q;
	int fa,sn,ans=0;
	q.push(s),vis[s]=1;
	while(!q.empty()){
		fa=q.front(),q.pop();
		ans++;
		for(int i=0;i<edge[fa].size();i++){
			sn=edge[fa][i];
			if(vis[sn]==0) q.push(sn),vis[sn]=1;
		}
	}
	return ans;
} 
int main(){
	scanf("%d%d",&n,&m);
	while(m--){
		scanf("%d%d",&x,&y);
		edge[x].push_back(y);
	}
	for(int i=1;i<=n;i++) ans+=bfs(i)-1-edge[i].size();
	printf("%d",ans);
	return 0;
}
```

---

## 作者：FFTotoro (赞：3)

本题需要使用简单的 BFS 算法。

注意到题目中的条件“若 $a$ 到 $b$ 有路径且 $b$ 到 $c$ 有路径，那么 $a$ 和 $c$ 必须有一条有向边连接”，其实可以转化一下——即“若 $a$ 到 $c$ 有路径，那么 $a$ 和 $c$ 必须有一条有向边连接”。

这样只用对于每个点 $a$，跑一遍 BFS，统计一下 $a$ 能到达的点的数量，减去 $a$ 连接的点数（因为题目中给出的图无重边，这个值即为 $a$ 的出度）即为这个点的答案。最终答案即为所有点的答案之和。

放代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
main(){
  ios::sync_with_stdio(false);
  int n,m,c=0; cin>>n>>m;
  vector<vector<int> > g(n);
  vector<int> d(n);
  for(int i=1;i<=m;i++){
    int u,v; cin>>u>>v;
    g[--u].emplace_back(--v);
  }
  for(int i=0;i<n;i++){
    vector<bool> b(n); // 打标记的数组，表示每个点是否被遍历过
    queue<int> q; q.emplace(i),b[i]=true;
    while(!q.empty()){
      int t=q.front(); q.pop();
      for(int j:g[t])if(!b[j])
        b[j]=true,q.emplace(j),d[i]++;
    } // 经典广搜
    c+=d[i]-g[i].size(); // d[i] 即为能到达的点的个数
  }
  cout<<c<<endl;
  return 0;
}
```

---

## 作者：Unnamed114514 (赞：2)

我们首先来考虑点对 $(a,b,c)$，容易发现 $a\rightarrow b\rightarrow c$ 的时候 $(a,c)$ 的距离是 $2$，这启发我们用最短路进行求解：

对于所有点 $i$，求出所有点 $j$ 的 $i$ 到 $j$ 的最短路 $dis_j$，那么当 $dis_j\ge2$ 时，$i,j$ 之间就会加边。

正确性证明：

首先当 $dis_j\ge2$ 时，那么首先我们可以找到一个点 $k$ 使 $dis_k=2$ 且 $k$ 可以到 $j$，那么 $i$ 到 $k$ 是会加边的，那么此时 $dis=3$ 的节点 $p$ 就 可以通过 $i\rightarrow k\rightarrow p$ 的方式加边。以此类推，$(i,j)$ 之间是会加边的。

当 $dis_j<2$ 时：因为 $dis_j$ 一定是非负数，所以 $dis_j=0\text{或}1$。当 $dis_j=0$ 时，只有 $i$ 这一个节点，由于 $a\ne b\ne c$（题目没说，但是可以通过最后一个样例得到），所以是不加边的；当 $dis_j=1$ 时，$(i,j)$ 已经有边了，所以是不加边的。

综上，原命题是正确的。

因为边权只能是 $1$，所以可以直接用 `BFS` $O(n+m)$ 求出最短路，时间复杂度 $O(n(n+m))$。

```cpp
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f
using namespace std;
const int maxn=2005;
int n,m,ans,dis[maxn];
bool vis[maxn];
vector<int> G[maxn];
struct node{
    int u,len;
};
queue<node> q;
void BFS(int s){
	memset(vis,0,sizeof(vis));
	memset(dis,inf,sizeof(dis));
	q.push(node({s,0}));
	while(q.size()){
		int u=q.front().u,len=q.front().len;
		q.pop();
		if(vis[u])
			continue;
		vis[u]=1,dis[u]=len;
		for(auto v:G[u])
			q.push(node({v,len+1}));
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1,u,v;i<=m;++i){
		scanf("%d%d",&u,&v);
		G[u].push_back(v);
	}
	for(int i=1;i<=n;++i){
		BFS(i);
		for(int j=1;j<=n;++j)
			if(dis[j]>=2&&dis[j]!=inf)
				++ans;
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：快乐的大童 (赞：2)

### 题目大意
给定一个 $n$ 点 $m$ 边的简单有向图，你需要添加 $k$ 条有向边，使得对于任意三个不同的整数 $a,b,c$，若 $a\rightarrow b$，$b\rightarrow c$，则 $a\rightarrow c$。你需要求出 $k$ 的最小值。

$n,m\le 2000$
### 思路
为了表述方便，下文称的“自环”均为“自己连向自己的边”。

我们看到“若 $a\rightarrow b$，$b\rightarrow c$，则 $a\rightarrow c$”，我们想到了什么？

传递闭包！

我们对原图做一次传递闭包，在这个闭包中有的边且原图没有的边，就是我们必须要添加的边。

由于原图无自环无重边，所以我们只需要输出闭包中边的数量减去 $m$ 的值。

注意统计闭包中存在的边时要跳过自环。
### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e3+5;
int n,m;
bitset<maxn>f[maxn];
int main(){
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y;
		f[x][y]=1;
	}
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(f[j][i])f[j]|=f[i];
	int ans=0;
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(f[i][j]&&i!=j)ans++;
	cout<<ans-m<<endl;
}
```


---

## 作者：ダ月 (赞：1)

### 题意概要：

给定一张有向图。添加一些边，要求添加后的图满足任意结点 $x,y,z$，若 $x$ 到 $y$ 有一条边，$y$ 到 $z$ 有一条边，那么 $x$ 到 $z$ 一定有一条边。

### 题目分析：

直接暴力是过不去的，但是听说有人用 ```bitset``` 卡过去了。

结论 $1$：从一个结点出发，通过原图它能到的点，必然之间要连上一条边。这个结论显然，若 $x$ 到 $y$ 有一条边，$y$ 到 $z$ 有一条边，$z$ 到 $p$ 有一条边，那么 $x$ 到 $z$ 有一条边，$x$ 到 $p$ 有一条边。

我们利用这个性质，只需要对每个结点搜索，得出答案，再减去原有的边数就行。

### 代码如下：

```
#include<bits/stdc++.h>
using namespace std;
int n,m;
const int N=2e3+10;
vector<int> a[N];
bool c[N];
int ans=0;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;scanf("%d%d",&x,&y);
		a[x].push_back(y);
	}for(int i=1;i<=n;i++){
		memset(c,false,sizeof(c));
		queue<int> q;q.push(i);c[i]=true;
		while(!q.empty()){
			int x=q.front();q.pop();
			for(auto k:a[x]){
				if(c[k]) continue;
				c[k]=true;q.push(k);
				ans++;
			}
		}
	}printf("%d\n",ans-m);
	return 0;
}
```
时间复杂度：$O(mn)$。

---

## 作者：incra (赞：0)

## 题意
求每一个点到这个点能到达的点连一条边，若已经有边，则不连，求要连几条边。
## 题解
为了方便判断哪些点之间有连边，我们给每一个点连一条自环边，在统计答案时记得减去 $n$，并且不考虑原有的 $m$ 条边，所以就是连完自环边后求出每一个点到能到达的点数量减 $n$ 减 $m$。
这里用的是邻接矩阵存储所以可以用 bitset 优化。
## 代码
```cpp
#include <iostream>
#include <bitset>
using namespace std;
const int N = 2010,M = 2010;
int n,m;
bitset <N> g[N];
int main () {
	cin >> n >> m;
	for (int i = 1;i <= n;i++) g[i][i] = 1;
	int ans = -m - n;
	while (m--) {
		int a,b;
		cin >> a >> b;
		g[a][b] = 1;
	}
	for (int j = 1;j <= n;j++) {
		for (int i = 1;i <= n;i++) {
			if (g[i][j]) g[i] |= g[j];
		}
	}
	for (int i = 1;i <= n;i++) ans += g[i].count ();
	cout << ans << endl;
    return 0;
}
```

---

## 作者：zajasi (赞：0)

## 题意
给你一个有向图。对于三个结点 $a,b,c$，如果 $a,b$ 之间有边，$b,c$ 之间有边，那么 $a,c$ 之间也必须有边。你每一次可以任意加一条边，问至少加多少条边可以满足要求？
## 解题思路
这不是裸的 [传递闭包](https://www.luogu.com.cn/problem/B3611) 吗？这道题中的第一篇题解，详细给我们介绍了如何 $O(n^2)$ 解决。我们在理解的基础上稍微更改一下——对于每两个能到达但是没有直接边的结点，就加边。具体看代码吧。
## AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int n,m;
int x,y,z;
vector<int> g[2020];
bitset<2020> a[2020];
bitset<2020> b[2020];
main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        cin>>x>>y;
        a[x][y]=1;
    }
    for(int i=1;i<=n;i++){
        a[i][i]=1;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            b[i][j]=a[i][j];
        }
    }//b 邻接矩阵
    for(int j=1;j<=n;j++){
        for(int i=1;i<=n;i++){
            if(a[i][j]){
                a[i]=a[i]|a[j];
            }
        }
    }//a 传递闭包
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(a[i][j]==1&&b[i][j]==0){//能到达但没有直接边
                z++;
                b[i][j]=1;
            }
        }
    }
    cout<<z;
    return 0;
}
```

---

