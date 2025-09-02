# Kostyanych's Theorem

## 题目描述

This is an interactive problem.

Kostyanych has chosen a complete undirected graph $ ^{\dagger} $ with $ n $ vertices, and then removed exactly $ (n - 2) $ edges from it. You can ask queries of the following type:

- "? $ d $ " — Kostyanych tells you the number of vertex $ v $ with a degree at least $ d $ . Among all possible such vertices, he selects the vertex with the minimum degree, and if there are several such vertices, he selects the one with the minimum number. He also tells you the number of another vertex in the graph, with which $ v $ is not connected by an edge (if none is found, then $ 0 $ is reported). Among all possible such vertices, he selects the one with the minimum number. Then he removes the vertex $ v $ and all edges coming out of it. If the required vertex $ v $ is not found, then " $ 0\ 0 $ " is reported.

Find a Hamiltonian path $ ^{\ddagger} $ in the original graph in at most $ n $ queries. It can be proven that under these constraints, a Hamiltonian path always exists.

 $ ^{\dagger} $ A complete undirected graph is a graph in which there is exactly one undirected edge between any pair of distinct vertices. Thus, a complete undirected graph with $ n $ vertices contains $ \frac{n(n-1)}{2} $ edges.

 $ ^{\ddagger} $ A Hamiltonian path in a graph is a path that passes through each vertex exactly once.

## 说明/提示

In the first test case, the original graph looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1979F/42089518245c2488c2bfecf2fe23dadea3c789e8.png)Consider the queries:

- There are no vertices with a degree of at least $ 3 $ in the graph, so " $ 0\ 0 $ " is reported.
- There are four vertices with a degree of at least $ 2 $ , and all of them have a degree of exactly $ 2 $ : $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ . Vertex $ 1 $ is reported, because it has the minimum number, and vertex $ 4 $ is reported, because it is the only one not connected to vertex $ 1 $ . After this, vertex $ 1 $ is removed from the graph.
- There are three vertices with a degree of at least $ 1 $ , among them vertices $ 2 $ and $ 3 $ have a minimum degree of $ 1 $ (vertex $ 4 $ has a degree of $ 2 $ ). Vertex $ 2 $ is reported, because it has the minimum number, and vertex $ 3 $ is reported, because it is the only one not connected to vertex $ 2 $ . After this, vertex $ 2 $ is removed from the graph.

The path $ 4 - 3 - 1 - 2 $ is a Hamiltonian path.

In the second test case, the original graph looks as follows:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1979F/8d69c71de95e98946d0d15367d0511bf08d2ba0a.png)Consider the queries:

- Vertex $ 1 $ has a degree of at least $ 3 $ , but it is connected to all vertices, so " $ 1\ 0 $ " is reported. After this, vertex $ 1 $ is removed from the graph.
- The remaining vertices $ 2 $ , $ 3 $ , and $ 4 $ have a degree of at least $ 0 $ , but among them vertex $ 4 $ has the minimum degree of $ 0 $ (vertices $ 2 $ and $ 3 $ have a degree of $ 1 $ ). Vertex $ 4 $ is not connected to both vertices $ 2 $ and $ 3 $ , so vertex $ 2 $ is reported (as it has the minimum number). After this, vertex $ 4 $ is removed from the graph.

The path $ 4 - 1 - 2 - 3 $ is a Hamiltonian path.

In the third test case, the graph consists of $ 2 $ vertices connected by an edge.

## 样例 #1

### 输入

```
3
4

0 0

1 4

2 3

4

1 0

4 2

2

1 0```

### 输出

```
? 3

? 2

? 1

! 4 3 1 2

? 3

? 0

! 4 1 2 3

? 0

! 2 1```

# 题解

## 作者：sunzz3183 (赞：6)

# CF1979F Kostyanych's Theorem 题解

## 前言

有趣的构造，没什么代码强度。~~富有人类智慧，反正赛时不会~~。

## 题意

这是一个交互问题。

有一个 $n$ 点且删除了 $n-2$ 条边的无向完全图。

你需要每次询问一个度数  $d$，评测机会回答 $u,v$，其中 $u$ 是度数至少为 $d$ 且在度数最小情况下的字典序最小的点，$v$ 是与 $u$ 不相连且字典序最小的点。然后评测机会**删除**点 $u$ 和与其相连的边。

最后回答原图的哈密顿路径。

询问次数不要超过 $n$。

## 分析

首先易得原图一定可以得到哈密顿路径。

设某一点 $x$ 的度数为 $deg_x$。

考虑这个图的边的个数：

$$\frac{n(n-1)}{2}-(n-2)=\frac{n^2-3n}{2}+2$$

而假设这个图每个点的度为 $n-3$，个数为：

$$\frac{n(n-3)}{2}=\frac{n^2-3n}{2}$$

所以，一定有至少一个点的度数大于 $n-3$，这是可以按照此做法构造的前提条件。

我们询问 $d=n-2$，通过 $v$ 是否等于 $0$ 来判断是否有度数等于 $n-2$ 的点（如果 $v$ 是 $0$ 则没有 $n-2$ 的点）。接下来我们对有没有度数等于 $n-2$ 的点进行分讨。

- 有

> 我们考虑剩下的图（即删除 $u$ 的图）$G^{\prime}$，显然点数为 $n-1$，我们记为 $n^{\prime}$。
>
> 假设我们已经构造出了 $G^{\prime}$ 中的一个哈密顿路，由于 $deg_u=n-2$，所以 $G^{\prime}$ 里只有一个点与 $u$ 没有连接，而路径的端点有 $2$ 个，所以 $u$ 至少可以与路径的一个端点相连，所以直接把 $u$ 连接到路径有与其相连的端点的一端即可。
>
> 那么怎么证明 $G^{\prime}$ 里一定会有一个路径呢？我们这样考虑：
>
> 易由原图的构型得，删除 $u$ 之后，$G^{\prime}$ 一定连通。
>
> 删除 $u$ 后，设 $G^{\prime}$ 中边的个数为 $E^{\prime}$：
>
> $$E^{\prime}=\frac{n^2-3n}{2}+2-(n-2)=\frac{n^2-5n+8}{2}$$
>
> 假设 $G^{\prime}$ 中每个点的度数为 $n^{\prime}-3$，$G^{\prime}$ 中边的总数为：
>
> $$\frac{n^{\prime}(n^{\prime}-3)}{2}=\frac{(n-1)(n-4)}{2}=\frac{n^2-5n+4}{2}<E^{\prime}$$
>
> 所以 $G^{\prime}$ 中仍然存在至少一个 $x$ 满足 $deg_x\ge n^{\prime}-2$，满足构造前提，可以继续进行递归构造。

- 没有

> 即 $deg_u=n-1$，此时一定存在一个点 $p$，使得 $deg_p\le n-3$。
>
> 同样假设我们已经构造出了 $G^{\prime}$（删去 $u,p$ 后的图）中的一个哈密顿路，我们需要把 $u,p$ 接到路径上，易知 $u$ 与所有点都有连边，所以可以把 $p$ 接到 $u$ 上，再把 $u$ 接到路径的任意端点上。
>
> 但是此时 $G^{\prime}$ 里还一定会有一个路径吗？
>
> 易得删除 $u,p$ 之后，$G^{\prime}$ 一定连通。
>
> 当我们从图中移除 $u,p$ 的时候，图中边数至少为：
>
> $$\begin{aligned}
>  \\&\frac{n^2-3n+4}{2}-(n-1)-(n-3)+1
>  \\=&\frac{n^2-7n+14}{2}
>  \\=&\frac{n^2-5n+6}2-\frac{2n-8}2
>  \\=&\frac{(n-2)(n-3)}2-(n-4)
>  \\=&\frac{(n-2)((n-2)-1)}2-((n-2)-2)
> \end{aligned}
> $$
>
> 令 $n^{\prime}=n-2$ 代入上式，得
>
> $$\frac{n^{\prime}(n^{\prime}-1)}2-(n^{\prime}-2)$$
>
> 即 $G^{\prime}$ 至少也是一个由 $n^{\prime}$ 个点的完全图删掉 $n^{\prime}-2$ 条边得到的图，所以一定存在 $x$ 满足 $deg_x\ge n^{\prime}-2$，满足构造前提，可以继续进行递归构造。

## 代码

先询问 $d=n-2$，得到 $u,v$ 如果 $v$ 不为 $0$，则递归 $d-1$，否则可以询问一个较小的数，比如 $0$，得到 $p$，然后递归 $d-2$ 即可。路径由于只会在两端添加，所以用 `deque` 维护即可，询问次数不会超过 $n$，满足题意。

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
int n,u,v;
deque<int>q;
void query(int d){
    printf("? %d\n",d);
    fflush(stdout);
    u=read(),v=read();
    return;
}
void dfs(int d){
    if(d<-1)return;
    if(d==-1)return query(0),q.push_back(u),void();
    query(d);
    if(v){
        int x=u,y=v;
        dfs(d-1);
        if(q.front()==y)q.push_back(x);
        else q.push_front(x);
    }
    else{
        int x=u;
        query(0);
        int y=u;
        dfs(d-2);
        q.push_back(x);
        q.push_back(y);
    }
}
void Main(){
    n=read();
    dfs(n-2);
    printf("! ");
    while(!q.empty())printf("%d ",q.front()),q.pop_front();
    puts("");
    fflush(stdout);
    return;
}
signed main(){
    int T=read();
    while(T--)Main();
    return 0;
}
```

---

## 作者：daniEl_lElE (赞：2)

初始 $m=\frac{n(n-1)}{2}-(n-2)$。

注意到每次如果询问处一个度数为 $n-2$ 的点，不难发现有且仅有一个点不与他连边，问题可以转化为 $n'=n-1$，$m'=\frac{(n-1)(n-2)}{2}-(n-3)$ 的子问题。在找出新图的一条哈密顿路径后，可以选择路径两端中与这个度数为 $n-2$ 的点相邻的一端连接。

然而，原图有可能没有度数为 $n-2$ 的点。此时由抽屉原理得，一定存在一个度数为 $n-1$ 的点。此时，不难发现一定也存在一个度数小于等于 $n-3$ 的点。考虑分别找出这两个符合要求的点，把这两个点周围的边断开。此时，问题转化为 $n'=n-2$，$m'\geq\frac{(n-2)(n-3)}{2}-(n-4)$ 的子问题。注意到更多的边意味着在后面我们可以直接把 $n-1$ 的点当作 $n-2$ 的点删。在寻找完子任务的解后，可以依次连上度数为 $n-1$ 的点和度数小于等于 $n-3$ 的点。

总复杂度 $O(n)$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
set<int> st;
deque<int> ans;
void dfs(int n){
	if(n<=2){
		vector<int> vv;
		for(auto v:st) ans.push_back(v);
		return ;
	}
	cout<<"? "<<n-2<<"\n"; fflush(stdout);
	int p,q; cin>>p>>q;
	st.erase(st.find(p));
	if(q==0){
		cout<<"? "<<0<<"\n"; fflush(stdout);
		int pp,qq; cin>>pp>>qq;
		st.erase(st.find(pp));
		dfs(n-2);
		ans.push_front(p);
		ans.push_front(pp);
	}
	else{
		dfs(n-1);
		if(ans.front()==q) ans.push_back(p);
		else ans.push_front(p);
	}
}
void solve(){
	while(!ans.empty()) ans.pop_back();
	st.clear();
	int n; cin>>n;
	for(int i=1;i<=n;i++) st.insert(i);
	dfs(n);
	cout<<"! ";
	while(!ans.empty()) cout<<ans.front()<<" ",ans.pop_front();
	cout<<"\n";
	fflush(stdout);
}
signed main(){
	int t; cin>>t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：CCPSDCGK (赞：2)

老年退役选手被 Div.2 薄纱。

这题，一点不会！

首先证明为什么一张完全图删掉 $n-2$ 条边后剩下的图一定能找到一条 Hamilton 路。

考虑直接证明**删掉** $n-3$ **条边后剩下的图 $A$ 一定存在一条 Hamilton 回路**，如果此命题成立，那么任意删掉一条边后也一定会找到一条 Hamilton 路。

设 $d(u)$ 为 $u$ 的度数，那么对于任意一对不相邻的点 $u,v$ 都有 $d(u)+d(v)\ge 2(n-1)-2-(n-4)=n$

首先给出一个引理：

> 无向图 $G$ 中 $u,v$ 为不相邻的一对点，若 $d(u)+d(v)\ge n$，则 $G$ 存在 Hamilton 回路当且仅当 $G+uv$ 存在 Hamilton 回路。

Proof：首先若 $G$ 存在 Hamilton 回路那么 $G+uv$ 存在 Hamilton 回路。如果 $G+uv$ 存在 Hamilton 回路，那么 $G$ 一定存在路径开头为 $v_1=u$，结尾为 $v_n=v$ 的 Hamilton 路径。

设 $S=\{v_i|v_1v_{i+1}\in E(G)\},T=\{v_i|v_nv_i\in E(G)\}$

设 $G$ 点数为 $n$。

显然 $|S\cup T|\le n-2$，又因为 $|S|+|T|=d(u)+d(v)=n$，所以 $S\cap T\not=\empty$。

设 $v_m\in S\cap T\ (1<m<n-1)$，那么一定存在 Hamilton 回路 $v_1v_2……v_mv_nv_{n-1}……v_{m+1}v_1$。

证毕。

因为每对相邻的点都满足此限制，所以 $A$ 可以通过不断加边直至成为完全图（一定存在 Hamilton 回路），归纳得出 $A$ 一定存在 Hamilton 回路，即一张完全图去掉任意 $n-2$ 条边后一定存在 Hamilton 路径。

回到这道题上，发现交互库删点的形式其实就是让我们往递归构造去想，看到是选择**度数至少为** $d$ 的点，可以想到应该是往删度数大的点考虑。

因为这张图很稠密，如果每个点度数都 $\le n-3$，那么整张图边数至多 $\dfrac{n(n-1)}2-n$，不符合要求，所以一定存在一个点度数 $\ge n-2$。

因此，考虑询问 $d=n-2$，然后根据 $v$ 是否等于 $0$  可以判断 $u$ 的度数。

然后根据 $d$ 的度数分类讨论。

当 $d=n-2$ 时，删 $u$ 及邻边后剩下的图的点数为 $n-1$，记为 $n'$，边数为 $\dfrac{n(n-1)}2-(n-2)-(n-2)=\dfrac{n'(n'-1)}2-(n'-2)$，仍存在 Hamilton 路径，且必有一个与 $u$ 直接相连（判断是否相连直接利用 $v$ 即可），直接将这个端点与 $u$ 相连即可。

当 $d=n-1$ 时，删 $u$ 后边数可能小于 $\dfrac{n'(n'-1)}2-(n'-2)$，所以我们要多删一个度数较小的点，好在 $u$ 与其它所有点相连，如果我们找到了这个度数较小的点 $p$（只需满足 $d(p)\le n-3$，显然是能找到的），直接将 $u$ 与 $p$ 相连，并将 $u$ 与接下来的 Hamilton 路径任一端点相邻即可。
```cpp
deque<int> q;
void dfs(int n){
	if(!n) return ;
	if(n==1){
		cout<<"? 0"<<endl;
		int u;cin>>u>>*new int;
		q.eb(u);return ;
	}
	cout<<"? "<<n-2<<endl;
	int u,v;cin>>u>>v;
	if(v){
		dfs(n-1);
		if(q.back()==v) q.emplace_front(u);else q.eb(u);
	}
	else{
		cout<<"? 0"<<endl;
		int p;cin>>p>>*new int;
		dfs(n-2);
		q.eb(u),q.eb(p);
	}
}
int main(){
	int t;cin>>t;
	while(t--){
		int n;cin>>n,dfs(n);
		cout<<"! ";
		while(!q.empty()) cout<<q.front()<<' ',q.pop_front();cout<<endl;
	}
	return 0;
}
```

---

## 作者：Mashu77 (赞：0)

给定一个 $n$ 个点的无向完全图，但是其中少了 $n-2$ 条边，你每次可以询问一个 $d$ 表示问度数大于等于 $d$ 的最小度数最小编号的节点，还会告诉你一个最小编号的不和上面那个点有边相连的点，没有则返回 $0$，每次询问结束删除第一个返回的点，你需要回答这个图的一个哈密顿路。

图很密，很容易有解，有的度很多的点怎么样都有解，其实可以直接删掉。

考察每次把一个恰当多度数的节点删掉递归，不难发现图中肯定有度数大于等于 $n-2$ 的点，每次问 $n-2$，如果有度数是 $n-2$ 而不是 $n-1$ 的点，那你完全可以递归，然后把它接在新路径的前面或者后面，这个根据你对那个点没边来讨论。

否则如果是 $n-1$，你发现删掉后图的性质就不好了，于是你考虑删掉一个度数小于等于 $n-3$ 的点补上，递归也是容易的，你只要在新的路径前面分别加上 $n-1$ 度和另外一个点就好了。

```cpp
#include <bits/stdc++.h>
using namespace std;
deque<int> q;
void dfs(int u){
	if(u<-1)return;
	if(u==-1){
		cout<<"? 0\n";
		int a,b;
		cin>>a>>b;
		q.push_back(a);
		return;
	}
	cout<<"? "<<u<<endl;
	int a,b;
	cin>>a>>b;
	if(b){
		dfs(u-1);
		if(q.front()==b)q.push_back(a);
		else q.push_front(a);
	}
	else{
		int t1=a;
		cout<<"? 0\n";
		cin>>a>>b;
		dfs(u-2);
		q.push_back(t1);
		q.push_back(a);
	}
}
int main(){
	int _;
	cin>>_;
	while(_--){
		int n;
		cin>>n;
		dfs(n-2);
		cout<<"! ";
		while(q.size()){
			cout<<q.front()<<" ";
			q.pop_front();
		}
		cout<<endl;
	}
}

---

