# Group Division

## 题目描述

In the $ 31 $ st lyceum, there were two groups of olympiad participants: computer science and mathematics. The number of computer scientists was $ n_1 $ , and the number of mathematicians was $ n_2 $ . It is not known for certain who belonged to which group, but it is known that there were friendly connections between some pairs of people (these connections could exist between a pair of people from the same group or from different groups).

The connections were so strong that even if one person is removed along with all their friendly connections, any pair of people still remains acquainted either directly or through mutual friends.

 $ ^{\dagger} $ More formally, two people $ (x, y) $ are acquainted in the following case: there are people $ a_1, a_2, \ldots,a_n $ ( $ 1 \le a_i \le n_1 + n_2 $ ) such that the following conditions are simultaneously met:

 $ \bullet $ Person $ x $ is directly acquainted with $ a_1 $ .

 $ \bullet $ Person $ a_n $ is directly acquainted with $ y $ .

 $ \bullet $ Person $ a_i $ is directly acquainted with $ a_{i + 1} $ for any ( $ 1 \le i \le n - 1 $ ).

The teachers were dissatisfied with the fact that computer scientists were friends with mathematicians and vice versa, so they decided to divide the students into two groups in such a way that the following two conditions are met:

 $ \bullet $ There were $ n_1 $ people in the computer science group, and $ n_2 $ people in the mathematics group.

 $ \bullet $ Any pair of computer scientists should be acquainted (acquaintance involving mutual friends, who must be from the same group as the people in the pair, is allowed), the same should be true for mathematicians.

Help them solve this problem and find out who belongs to which group.

## 说明/提示

Consider the third test case. The division into groups looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1916F/61a6b120f4c32c6f1c36976b3b60c3a388509a79.png)  The students selected as computer scientists are colored in green, and those selected as mathematicians are colored in blue.Consider all pairs of computer scientists and how they are acquainted:

Pairs $ (4, 5), (4, 6) $ are directly acquainted.

Pair $ (5, 6) $ is acquainted through the computer scientist with number $ 4 $ .

Consider all pairs of mathematicians and how they are acquainted:

Pairs $ (1, 2), (2, 3) $ are directly acquainted.

Pair $ (1, 3) $ is acquainted through the mathematician with number $ 2 $ .

We conclude that any pair of people belonging to the same group is acquainted with each other, thus the division into two groups is correct.

## 样例 #1

### 输入

```
3
1 2 3
2 3
1 3
1 2
1 4 7
2 5
3 4
2 4
1 2
3 5
4 5
1 5
3 3 7
1 2
1 6
2 3
2 5
3 4
4 5
4 6```

### 输出

```
3 
1 2 
5 
1 2 3 4 
4 5 6 
1 2 3```

# 题解

## 作者：蒟蒻君HJT (赞：16)

考虑归纳地构造第一个集合 $S$。初始时令 $S=\{1\}$（任意点），称去除 $S$ 之后的图为 $T$，每次找到 $T$ 中的割点，向 $S$ 中加入一个不在 $S$ 中的，与 $S$ 连通的，且不是 $T$ 的割点的结点 $x$。

$\text{Claim 1:}$ 存在这样的 $x$。

$\text{Claim 2:}$ 如果存在一个割点 $y$，去掉它后 $T$ 分裂为互相不连通的 $T_1,T_2,\cdots T_k(k\geq 2)$，则 $\forall i\in [k],T_i$ 与 $S$ 间存在边。

$\text{Proof 2:}$ 若不然，则在原图中去除 $x$ 后，$T_i$ 无法与 $S$ 连通，即 $x$ 为原图的割点，不符合题设。

$\text{Proof 1:}$ 根据 $\text{dfs}$ 树的形态，一定可以取出一个割点 $z$ 使得它存在一个没有割点的子树 $s$。在 $s$ 中任意取一个与 $S$ 连通的结点，即为所求的 $x$。 

时间复杂度 $\Theta(n_1(m+n_1+n_2))$。

[for reference only.](https://codeforces.com/contest/1916/submission/239819732)

---

## 作者：zhuoheng (赞：11)

首先看到这题的题意里的**点双连通分量**就能大致知道跟 Tarjan 算法有关了。  
考虑接近倍增的思想，设立两个集合 $S_1,S_2$。   
一开始 $S_1$ 中只有一个点（可以选任意一点），$S_2$ 里有剩下的$\ \ n_1+n_2-1\ \ $个点。   
然后大致做法就是从 $S_2$ 中选出与 $S_1$ 中的任意点有连边的点，直到 $S_1$ 的点数等于 $ n_1$。   
但是题目里还说了：**且 $S_1,S_2$ 的导出子图均连通。**  
所以还有一个要求那就是选出的点不能为 $S_2$ 中的割点，不然就会破坏 $S_2$ 的连通性。   
能够证明这样的点一定存在：

考虑 $S_2$ 中的割点，找到 $S_2$ 中只与一个割点 $x$ 相邻的一块，如果这个块与 $S_1$ 没有边相连，则 $x$ 是原图的的一个割点，这与题设是**矛盾**的。  
综上所述，我们可以先确定一个点作为 $S_1$ 的起始点，接着使用 Tarjan 找到 $S_2$ 里的割点，然后把其他点一个个丢进 $S_1$ 里就可以了。

---

## 作者：phigy (赞：8)

## 前言

本题解采用双极定向问题的标准方式解决此问题。

也就是加强为线性求一个以 $S$ 为开头 $T$ 为结尾的点排列使得任意前后缀均连通。

以下为介绍耳分解和双极定向问题。

## 耳分解

定义图 $G=(V,E)$ 的子图 $G'=(V',E')$ **的** **一个** 耳，是一个相邻有边的顶点序列 $x_0,x_1…x_t$ 其中 $x_1…x_{t-1}$ 在 $V'$ 外边且互不相同，$x_0,x_t$ 在 $V'$ 里边可以相同，但是如果不相同就是一个开耳。

耳分解指对一张图 $G$ 给一个后面包含前面的子图序列 $(G_0,G_1,…,G_t)$ ，其中 $G_0$ 是一个环，$G_t=G$，并且 $G_{i+1}$ 和 $G_{i}$ 的差的点是掐头去尾的耳。特别的如果所有耳都是开耳，那就是开耳分解。

有结论：

- 无向图边双连通 $\Leftrightarrow$ 该无向图存在耳分解
- 无向图点双连通 $\Leftrightarrow$ 该无向图存在开耳分解

简单的考虑 $G_p$ 是一个包含根节点的连通块，此时一定有 $x$ 在外 $fa_x$ 在内，那么找一条覆盖这条边的返祖边，$(u,v)$ 其中 $u$ 在 $fa_x$ 上，$v$ 在 $x$ 下，然后 $fa_x\rightarrow x\rightarrow v\rightarrow u$ 就是耳朵了，特别的点双 $u$ 肯定可以不是 $fa_x$。

## 双极定向问题

给一张无向图的边定向，使其成为 DAG。

同时 $S$ 是唯一无入度点，$T$ 是唯一无出度点。

可以当且仅当加入 $S\rightarrow T$ 后是点双连通的。

充分性就是考虑开耳分解等价于点双连通，我们以 $S\rightsquigarrow T$ 和 $S\rightarrow T$ 为初始的环做开耳分解，然后去掉 $S\rightarrow T$ 根据每个开耳的头尾的偏序关系确定方向即可。必要性就是说，连了 $S\rightsquigarrow T$ 后 $S,T$ 在一个点双里面，也就是如果有割点，一定可以分成一个有 $S,T$ 的块一个没 $S,T$ 的块，这显然无法同时满足双极和 DAG。

## 线性解决方法

考虑构造，实质上双极定向后的拓扑序是满足任意前后缀均连通的，这个也可以反推双极定向，也就是构造一个序列。
考虑 $S\rightsquigarrow T$ 这个链就是主干，就按这个顺序。

然后考虑对于一个点 $x$ 我们只用保留他返祖后最浅的子树返祖边，也就是 $low_x$ 和 $fa_x$，即是说 $x$ 在 $low_x$ 和 $fa_x$ 之间。注意到由于加上 $S\rightarrow T$ 是点双，因此 $low_x\neq fa_x$。

考虑一个简单的实现，以 $S$ 为根，我们把 $x$ 丢到 $fa_x$ 和 $low_x$ 的一个后继 vector 里面，然后我们从 $S$ 开始遍历它的后继 vector，每遍历到一个点丢进答案队列然后遍历他的 vector。

注意到这样做 $T$ 不一定是最后一个，考虑我们不把 DFS 树上 $S\rightsquigarrow T$ 上的点扔进后继 vector 里面而是以这个顺序遍历即可。

可以注意到 $T$ 的后继 vector 一定在遍历它之前都遍历过了。

这样做就是 $O(m)$ 的了。


```cpp
int n,m,S,T;
vector<int>E[MAXN];
void add(int x,int y) {E[x].push_back(y);}
int dfn[MAXN],low[MAXN],id[MAXN],fa[MAXN],dfx;
vector<int>ans,now,dmt;
int book[MAXN];
vector<int>vec[MAXN];
void Tarjan(int x)
{
    id[dfn[x]=low[x]=++dfx]=x;
    now.push_back(x);
    if(x==T) {dmt=now;}
    for(int v:E[x])
    {
        if(v==fa[x]) {continue;}
        if(!dfn[v]) {fa[v]=x;Tarjan(v);low[x]=min(low[x],low[v]);vec[x].push_back(v);vec[id[low[v]]].push_back(v);}
        else                          {low[x]=min(low[x],dfn[v]);}
    }
    now.pop_back();
}
int vis[MAXN];
void dfs(int x)
{
    vis[x]=1;ans.push_back(x);
    for(int v:vec[x]) {if(!vis[v]&&!book[v]) {dfs(v);}}
}
void Bipolar_Orientation()
{
    Tarjan(S);
    for(int x:dmt) {book[x]=1;}
    for(int x:dmt) {if(!vis[x]) {dfs(x);}}
}
```

## 后话

本题解主要提供双极定向问题的一个简短模板

---

## 作者：Leasier (赞：4)

Update on 2024.1.18：感谢 [yhk1001](https://www.luogu.com.cn/user/191754)。

~~本题原数据很水，通过其并不能在很大程度上保证你所实现的算法的正确性。~~

------------

考虑构造一个长为 $n = n_1 + n_2$ 的序列 $a$，使得 $\forall 1 \leq i < n$，前 $i$ 个点的导出子图与后 $n - i$ 个点的导出子图联通。

考虑先任选一个根 $R$ 跑无向图 Tarjan 得出 一个 dfs 生成树 $T$ 和 $\operatorname{dfn}_u, \operatorname{low}_u, \operatorname{rk}_x$。

考虑操作 $\mathcal{P}(u)$ 表示 $T$ 中以 $u$ 为根：

- 将 $u$ 放到 $a$ 的末端。
- 将 $T$ 的 $u$ 子树中 $u$ 之外的点分为三层：$\mathcal{A}: \operatorname{low}_v < \operatorname{dfn}_u$，$\mathcal{B}: \operatorname{low}_v = \operatorname{dfn}_u$，$\mathcal{C}: \operatorname{low}_v > \operatorname{dfn}_u$。
- 首先考虑从深到浅处理 $\mathcal{B}$ 类点：对这些 $v$ 进行操作 $\mathcal{P}(v)$。
- 然后 dfs 遍历 $\mathcal{A}$ 类点和在上一步中未处理到的 $\mathcal{C}$ 类点，按 dfs 的顺序将其放到 $a$ 的末端。
- 删去 dfs 遍历到的点和与其相连的边。

操作 $\mathcal{P}(R)$ 即可得到一个满足条件的 $a$。正确性不难证明。

接下来考虑如何实现这个过程。考虑 $\forall u \neq R$，按在 $T$ 上 dfs 返回的顺序把 $T$ 中 $u$ 的父亲（一）和 $\operatorname{rk}_{\operatorname{low_u}}$（二）向 $u$ 连边，则可以发现若我们在这张新图上从 $R$ 开始 dfs，则处理 $\mathcal{A}$ 类点时我们一定会走第一类边，处理 $\mathcal{B}$ 类点时我们一定会走第二类边。

于是我们在新图上 dfs 一遍，依次访问到的点组成的序列即为一个合法的 $a$。时间复杂度为 $O(\sum(n_1 + n_2 + m))$。

代码：
```cpp
#include <iostream>
#include <vector>

using namespace std;

typedef struct {
	int nxt;
	int end;
} Edge;

int cnt;
int head[4007], dfn[4007], low[4007], rnk[4007], ans[4007];
bool vis[4007];
Edge edge[10007];
vector<int> v[4007];

inline void init(int n){
	cnt = 0;
	for (int i = 1; i <= n; i++){
		head[i] = 0;
		v[i].clear();
	}
}

inline void add_edge(int start, int end){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
}

void dfs1(int u, int father, int &id){
	vis[u] = true;
	id++;
	dfn[u] = low[u] = id;
	rnk[id] = u;
	for (int i = head[u]; i != 0; i = edge[i].nxt){
		int x = edge[i].end;
		if (!vis[x]){
			dfs1(x, u, id);
			low[u] = min(low[u], low[x]);
			v[u].push_back(x);
			v[rnk[low[x]]].push_back(x);
		} else if (x != father){
			low[u] = min(low[u], dfn[x]);
		}
	}
}

void dfs2(int u, int &pos){
	vis[u] = false;
	ans[++pos] = u;
	for (int i : v[u]){
		if (vis[i]) dfs2(i, pos);
	}
}

int main(){
	int t;
	cin >> t;
	for (int i = 1; i <= t; i++){
		int n1, n2, m, n, id = 0, pos = 0;
		cin >> n1 >> n2 >> m;
		n = n1 + n2;
		init(n);
		for (int j = 1; j <= m; j++){
			int a, b;
			cin >> a >> b;
			add_edge(a, b);
			add_edge(b, a);
		}
		dfs1(1, 0, id);
		dfs2(1, pos);
		for (int j = 1; j <= n1; j++){
			cout << ans[j] << " ";
		}
		cout << endl;
		for (int j = n1 + 1; j <= n; j++){
			cout << ans[j] << " ";
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：shicj (赞：1)

# CF1916F Group Division 题解


upd 2024.11.20 “（否则选出这个点后 $S_2$ 就不连通了）” $S_2$ 改为 $S_1$

upd 2024.10.10 “且选出的点不是剩余点集 $S_2$ 的割点” $S_2$ 改为 $S_1$

1. 题意

   给定一个无向图 $G$，点数为 $n_1+n_2$，边数为 $m$,保证 $G$ 是一个点双连通分量且无重边。

   请将 $G$ 划分为两个无交集的点集 $S_1$，$S_2$ 满足 $|S_1|=n_1$，$|S_2|=n_2$，且 $S_1$，$S_2$ 的导出子图均连通。

   保证有解。

2. 思路

   - 因为 $ 1 \le n_1 , n_2 \le 2000 $，$ 1 \le m \le 5000 $ 所以可以考虑一个点一个点地选取和划分，每一次选取花费时间 $O\left(\log\right.m)$ 或更少。
   - 因此可以定义 $S_2$ 为空集，所有点都在 $S_1$ 中，之后，每次从 $S_1$ 取出 $1$ 个点放入 $S_2$，执行 $n_2$ 次。
   - 然后考虑怎样的点可以被选取，易得，只要保证新选出的点与 $S_2$ 连通（题目要求保证两个子图均连通）且选出的点不是剩余点集 $S_1$ 的割点（否则选出这个点后 $S_1$ 就不连通了）。
   - 于是，就可以用 Tarjan 求割点解决了。

3. 注意

   - 每次求割点之前一定要清空相关数组。
   - 注意多测要清空存图的 ```vector```。
   - 注意取出的点要在 $S_1$ 删除。
   - 开始时先取任意一点放入 $S_2$ 并注意要在 $S_1$ 中删点。

4. 代码

   ```cpp
   //#include<bits/stdc++.h>
   #include<iostream>
   #include<vector>
   #include<algorithm>
   #include<cstring>
   #include<set>
   using namespace std;
   const int maxn=20000;
   vector<int>G[maxn+100];
   vector<int>GG[maxn+100];
   int dfn[maxn+100]，low[maxn+100]，tot;
   int n，m;
   int cut[maxn+100];
   void del_point(int p){
   	for(auto po:G[p]){
   		for(int i=0;i<G[po].size();i++){
   			if(G[po][i]==p){
   				G[po].erase(G[po].begin()+i);
   			}
   		}
   	}
   	G[p].clear();
   }
   void Tarjan(int u，int root){
   	low[u]=dfn[u]=++tot;
   	int cnt=0;
   	for(auto v:G[u]){
   		if(!dfn[v]){
   			Tarjan(v，root);
   			low[u]=min(low[u]，low[v]);
   			if(low[v]>=dfn[u])cnt++;
   		}
   		else{
   			low[u]=min(low[u]，dfn[v]);
   		}
   	}
   	if(u==root){
   		if(cnt>1)cut[u]=1;
   	}
   	else 
   		if(cnt>0)cut[u]=1;
   }
   void find_cut(){
   	for(int i=1;i<=n;i++){
   		if(dfn[i])continue;
   		Tarjan(i，i);
   	}
   }
   bool ans[maxn+100];
   void init(bool x){
   	memset(dfn，0，sizeof(dfn));
   	memset(low，0，sizeof(low));
   	memset(cut，0，sizeof(cut));
   	tot=0;
   	if(x){
   		memset(ans，0，sizeof(ans));
   		memset(G，0，sizeof(G));
   		memset(GG，0，sizeof(GG));
   	}
   }
   int CASEmain(){
   	init(true);
   	int n1，n2;
   	cin>>n1>>n2>>m;
   	n=n1+n2;
   	for(int i=1;i<=m;i++){
   		int u，v;
   		cin>>u>>v;
   		G[u].push_back(v);
   		G[v].push_back(u);
   		GG[u].push_back(v);
   		GG[v].push_back(u);
   	}
   	cout<<1<<" ";
   	ans[1]=1;
   	del_point(1);
   	for(int i=1;i<n1;i++){
   		init(false);
   		find_cut();
   		set<int>ps;
   		for(int j=1;j<=n;j++){
   			if(ans[j]){
   				for(auto k:GG[j]){
   					ps.insert(k);
   				}
   			}
   		}
   		for(auto j:ps){
   			if(!cut[j]&&G[j].size()!=0){
   				cout<<j<<" ";
   				ans[j]=1;
   				del_point(j);
   				break;
   			}
   		}
   	}
   	cout<<endl;
   	for(int i=1;i<=n;i++){
   		if(!ans[i])
   			cout<<i<<" ";
   	}
   	cout<<endl;
   	return 0;
   }
   int main(){
   	int t;
   	cin>>t;
   	for(int i=1;i<=t;i++){
   		CASEmain();
   	}
   	return 0;
   }
   ```

---

## 作者：Z1qqurat (赞：0)

官方题解做法。考虑动态构造 $S,|S|=n_1$。设 $T=N-S$（$N$ 表示原图点集），每次从 $T$ 中选出一个并非 $T$ 的导出子图割点且与 $S$ 连通（与 $S$ 内的点有连边）的 $x$，将 $x$ 从 $T$ 中删除，并到 $S$ 中去，该过程进行 $n_1$ 次即可。

如果每次都可以找出这样一个 $x$ 的话正确性就显然了，试着证明为什么每次都能找出这样的 $x$。首先，$T$ 的导出子图内的每个割点都会和 $S$ 内点有连边，否则会导致 $N$ 非点双联通，与题意矛盾。考虑反证法，我们取出一个割点 $y$，满足将 $y$ 去掉之后 $T$ 中至少有一个新连通块 $T'$ 内无割点（一定能找到这样的一个联通块，考虑选择 dfs 树上深度最大的那个割点，那么它的子树除去它就会是一个没有割点的联通块）。那么由于 $T'$ 内没有割点，$T$ 中也不存在一个非割点又与 $S$ 有连边的点，也就是说 $T'$ 在去掉 $y$ 后和 $S$ 不连通了，所以 $y$ 是原图的一个割点，与原图点双联通矛盾，故每次操作都必然存在这样的一个 $y$（当然这是建立在题目保证有解的情况下）。

每次重新 tarjan 求出 $T$ 的所有割点并打上标记，任取一个非割点也不属于 $S$ 的与 $S$ 有连边的点 $x$ 加入 $x$，便可以在 $\mathcal{O}(n_1(n_1+n_2+m))$ 的时间内完成构造。注意 tarjan 的一些细节即可。

[Submission.](https://codeforces.com/contest/1916/submission/246358716)

---

