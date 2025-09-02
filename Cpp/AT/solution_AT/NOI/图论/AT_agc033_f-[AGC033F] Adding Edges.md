# [AGC033F] Adding Edges

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc033/tasks/agc033_f

$ N $ 頂点からなる木 $ T $ と $ N $ 頂点 $ M $ 辺からなる無向グラフ $ G $ が与えられます。 それぞれの各頂点には $ 1 $ から $ N $ の番号が割り振られています。 $ T $ の $ N-1 $ 本の辺のうち、$ i $ 本目の辺は頂点 $ a_i $ と頂点 $ b_i $ を繋いでいます。 $ G $ の $ M $ 本の辺のうち、$ j $ 本目の辺は頂点 $ c_j $ と頂点 $ d_j $ を繋いでいます。

$ G $ に対して以下の操作を繰り返し行うことで、$ G $ に辺を追加することを考えます。

- $ 3 $ つの整数 $ a $,$ b $,$ c $ であって、$ G $ の頂点 $ ab $ 間と $ bc $ 間に辺があり、$ ac $ 間に辺がないようなものを選ぶ。 $ T $ のある単純パス上に頂点 $ a $,$ b $,$ c $ が何らかの順序ですべて含まれるとき、$ G $ の頂点 $ ac $ 間に辺を追加する。

これ以上辺を追加することができなくなったとき、$ G $ の辺の数はいくつになるか求めてください。 この数はどのように操作を行っても変わらないことが示せます。

## 说明/提示

### 制約

- $ 2\ ≦\ N\ ≦\ 2000 $
- $ 1\ ≦\ M\ ≦\ 2000 $
- $ 1\ ≦\ a_i,\ b_i\ ≦\ N $
- $ a_i\ \neq\ b_i $
- $ 1\ ≦\ c_j,\ d_j\ ≦\ N $
- $ c_j\ \neq\ d_j $
- $ G $ は多重辺を含まない
- $ T $ は木である

### Sample Explanation 1

以下の順で辺を追加することで $ 6 $ 本まで辺を増やすことができます。 - $ (a,b,c)=(1,5,4) $ とし、頂点 $ 1 $ と頂点 $ 4 $ の間に辺を追加する。 - $ (a,b,c)=(1,5,2) $ とし、頂点 $ 1 $ と頂点 $ 2 $ の間に辺を追加する。 - $ (a,b,c)=(2,1,4) $ とし、頂点 $ 2 $ と頂点 $ 4 $ の間に辺を追加する。

## 样例 #1

### 输入

```
5 3
1 2
1 3
3 4
1 5
5 4
2 5
1 5```

### 输出

```
6```

## 样例 #2

### 输入

```
7 5
1 5
1 4
1 7
1 2
2 6
6 3
2 5
1 3
1 6
4 6
4 7```

### 输出

```
11```

## 样例 #3

### 输入

```
13 11
6 13
1 2
5 1
8 4
9 7
12 2
10 11
1 9
13 7
13 11
8 10
3 8
4 13
8 12
4 7
2 3
5 11
1 4
2 11
8 10
3 5
6 9
4 10```

### 输出

```
27```

# 题解

## 作者：zhylj (赞：14)

对上面一些题解的补充和修正。

注意到如果一条路径上依次存在三个点 $u,v,w$，且 $(u,v),(u,w)\in E$，那么我们可以删去 $(u,w)$，加上 $(v,w)$ 而不改变最终产生的图。

考虑上述操作无法进行时产生的图 $G'$，我们可以发现一个引理：一条边 $(u,v)$ 存在当且仅当本来就有连边或者存在路径 $u=p_1,p_2,p_3,\cdots,p_{k-1},p_k=v$ 使得对于任意相邻三个点 $p_i,p_{i+1},p_{i+2}$，$(p_i,p_{i+1}),(p_{i+1},p_{i+2})\in E$，且 $p_i,p_{i+1},p_{i+2}$ 在同一条路径上。

对于上述引理的证明，考虑充分性是显然的，必要性根据 $G'$ 的极小性也不难证明。

考虑如何求出 $G'$，我们依次加入每一条边，然后动态地维护 $G'$。于此同时，我们维护 $f(u,v)$ 表示当 $T$ 取 $u$ 为根时，与 $u$ 相连的，离 $v$ 最近的点。那么对于新加入的一条边 $(u,v)$，我们根据 $f(u,v)$ 的值讨论，同时维护一个队列表示正要加入的边：

- 若 $f(u,v)=v$，则已经存在边 $(u,v)$，我们可以忽略这条边。
- 若 $f(u,v)$ 存在且不为 $v$（$f(v,u)$ 存在且不为 $u$ 的情况是类似的，不再赘述），那么 $u,v$ 路径上存在一个点 $f(u,v)$ 与 $u$ 有连边，根据之前的结论我们可以把 $(u,v)$ 缩短为 $(f(u,v),v)$ 而不改变最后的答案，于是把新的这条边放入待处理的队列。
- 若 $f(u,v),f(v,u)$ 均不存在，那这条边可以被直接加入，我们分别从 $u,v$ 开始向以 $v,u$ 为根时 $u,v$ 的子树内修改 $f$，根据 $f$ 的意义，我们只需要修改没有值的点，若遇到一个有值且不为我们修改的值的 $f$，则这个 $f$ 代表的边要修改，我们继续把它丢到队列里。

最后，我们再从每个点开始 DFS 上述引理所述的路径，就可以求出所有边了。

注意到每次搜索要么给一个点的 $f$ 变成有值的，要么缩小一条边，而二者的总次数分别是 $\mathcal O(N^2)$ 和 $\mathcal O(NM)$ 的，故总的时间复杂度为 $\mathcal O(N(N+M))$。

---

## 作者：Elma_ (赞：11)

> 给定一张棵 $n$ 个点的树 $T$ 和一张 $n$ 个点 $m$ 条边的图 $G$，定义一次操作为选择满足下列条件的三个点 $a,b,c$ 并加入边 $(b,c)$：
>
> $1.$ 图 $G$ 中存在边 $(a,b),(a,c)$，且不存在边 $(b,c)$；      
> $2.$ 树 $T$ 中存在中存在一条简单路径以任意顺序同时包含点 $a,b,c$。
> $\quad$

> 求最终无法操作时 $G$ 的边数。可以证明操作的顺序对答案没有影响。
> 
> - $2 \leq n \leq 2000$，$1 \leq m \leq 2000$。

为了方便描述，下文中记初始时的图为 $G_0$，最终的图为 $G$。

考虑如果规定 $a,b,c$ 必须在 $T$ 中的某条路径上顺序出现该怎么做。容易发现对于一条边 $(u,v) \in G$，一定存在一个点列 $v_1=u,v_2,\cdots,v_k=v$ 满足 $(v_i,v_{i + 1}) \in G_0$ 且 $v_1,v_2, \cdots,v_k$ 在 $T$ 的某条路径上顺序出现。

必要性也是显然的，只需进行 $k-2$ 次操作，每次操作依次选择 $v_1,v_i,v_{i+1}$ 并加入边 $(v_1,v_{i + 1})$，最后就得到了边 $(v_1,v_k)$。因此对于这个问题，我们可以直接 dfs 一遍求出答案。

考虑将原问题转化为条件 $2$ 修改后的问题，对于 $T$ 中某条简单路径上顺序出现的三个点 $a,b,c$，若 $(a,b),(a,c) \in G_0$，则我们可以将边 $(a,c)$ 替换为 $(b,c)$ 使得答案不变。

如何快速地处理这个过程呢？考虑依次加入 $G_0$ 中的边，并记 $f(x,y)$ 为 $T$ 的根为 $x$ 时当前生成的图 $G$ 中与 $y$ 有连边的最近的 $y$ 在 $T$ 上的祖先。则加入边 $(x,y)$ 时如下更新 $f(x,y)$：

- 当 $f(x,y) = y$ 时，显然不需要加入这条边；
- 当 $f(x,y)$ 存在且不为 $y$ 时，则依照刚才的结论可以将其转化为加入边 $(f(x,y),y)$；
- 否则我们需要加入边 $(x,y)$，并更新 $y$ 子树中的点的 $f$ 值。

具体地，当我们从 $y$ 往下更新到一个节点 $z$ 时，若 $f(x,z)$ 不存在，则 $f(x,z) = y$，否则我们需要加入边 $(y,z)$ 并退出对 $z$ 子树的 dfs。然后由于这题是无向边，因此加入 $(x,y)$ 的同时也需加入 $(y,x)$。

最后以每个点为根对 $T$ 进行 dfs 统计答案即可。注意每个三元组都会被统计到两次，因此最后要将答案除以 $2$。时间复杂度 $O(n(n + m))$。

```cpp
int N, M, X[MN], Y[MN];
vector <int> G[MN];

int fa[MN][MN];
inline void dfs1(int u, int ff, int rt) {
	fa[rt][u] = ff;
	for (int v : G[u]) {
		if (v != ff) dfs1(v, u, rt);
	}
}

int f[MN][MN];
queue <int> qx, qy;
inline void dfs2(int u, int rt, int t) {
	if (u != t && f[rt][u]) {
		qx.push(t), qy.push(u);
		return;	
	}
	f[rt][u] = t;
	for (int v : G[u]) {
		if (v != fa[rt][u]) dfs2(v, rt, t);
	}
}
inline void bfs(int x, int y) {
	qx.push(x), qy.push(y);
	while (!qx.empty()) {
		int x = qx.front(), y = qy.front();
		qx.pop(), qy.pop();
		if (f[x][y] == y) continue;
		if (f[x][y]) {
			qx.push(f[x][y]), qy.push(y);
			continue;
		}
		if (f[y][x]) {
			qx.push(f[y][x]), qy.push(x);
			continue;
		}
		f[x][y] = y;
		f[y][x] = x;
		dfs2(y, x, y);
		dfs2(x, y, x);
	}
}

int Ans;
inline void getans(int u, int rt, int p) {
    if (u != p && f[p][u]) {
        ++Ans, p = u;
    } 
    for (int v : G[u]) {
        if (v != fa[rt][u]) getans(v, rt, p);
    }
}

signed main(void) {
	N = read(), M = read();
	for (int i = 1, u, v; i < N; i++) {
		u = read(), v = read();
		G[u].pb(v), G[v].pb(u);
	}
	for (int i = 1; i <= M; i++) {
		X[i] = read(), Y[i] = read();
	}
	for (int i = 1; i <= N; i++) dfs1(i, 0, i);
    for (int i = 1; i <= M; i++) bfs(X[i], Y[i]);
    for (int i = 1; i <= N; i++) getans(i, i, i);
    printf("%lld\n", Ans / 2);
	return 0;
}
```


---

## 作者：letitdown (赞：9)

看到题目中的 $n\leq 2000$ 很小，很好欺负，那么我们考虑一个 $O(\frac{n^3}{w})$ 做法。

借鉴 $\rm Bellman-Ford$ 算法，我们尝试让每一条边去扩展出新的边。

很显然每条边只会进出队列一次。暴力的思路是对于这条边的两个端点 $x$ 和 $y$，分 $x$ 成为 $b$ 和 $y$ 成为 $b$ 枚举第三个点，尝试让它和另一个点连边接着扩展。

如果爆扫的话 可以用 $\rm ST$ 表做到 $O(1)$ 判断，但是总的复杂度最坏是 $O(n^3)$ 的，无法通过此题。

那么我们就可以使用 `std::bitset` 优化复杂度。

枚举一个点 $x$ 为根，那么对于一个点 $y$ 能够构成一条路径的 $z$ 会在 $x$ 的其它子树或者 $y$ 子树内或者 $x$ 到 $y$ 的路径上。

前两个情况可以通过 $\rm dfn$ 序解决，第三个情况可以通过一遍 dfs 解决。

那么每次扩展时只枚举有用的点，每次都会让现在的答案增加，而答案个数是 $O(n^2)$ 的，所以复杂度有了保证。

那么这道题就被我们完美解决......了吗？

并不是，还有个小细节，把 $\frac{n^3}{w}$ 的 `std::bitset` 开出来会发现用了 $\rm 1000+ MB$，正好超过本题空间限制，那么我们考虑记录答案时只记录比当前根编号大的答案，这样空间就少了一半，可以通过此题。

### Code

```cpp
#include<vector>
#include<bitset>
#include<cstring>
#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
namespace EMT{
	typedef long long ll;typedef double db;typedef std::pair<int,int> pii;
	#define pf printf
	#define F(i,a,b) for(int i=a;i<=b;i++)
	#define D(i,a,b) for(int i=a;i>=b;i--)
	inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
	inline void file(){freopen("in.in","r",stdin);freopen("my.out","w",stdout);}
	inline int max(int a,int b){return a>b?a:b;}inline int min(int a,int b){return a<b?a:b;}
	inline void pi(int x){pf("%d ",x);}inline void pn(){pf("\n");}
	const int N=2010;
	std::vector<int>g[N];int dfn[N],lst[N],time[N];
	std::bitset<N>pre[N],now;
	int n,m,hd=1,tl;pii q[N*N];
	std::bitset<N>w[N];
	struct tree{
		int rt,ti;
		std::vector<std::bitset<N> >bit;
		inline int id(int x){
			return x-rt;
		}
		inline void dfs1(int x,int fa){
			time[dfn[x]=++ti]=x;
			for(auto y:g[x])if(y!=fa)
				dfs1(y,x);
			lst[x]=ti;
		}
		inline void dfs2(int x,int fa,int son){
			now[x]=1;
			if(x>rt){
				bit[id(x)]|=now;
				bit[id(x)]|=pre[dfn[son]-1];
				bit[id(x)]|=pre[n]^pre[lst[son]];
				bit[id(x)]|=pre[lst[x]]^pre[dfn[x]-1];
			}
			for(auto y:g[x])if(y!=fa)
				dfs2(y,x,son?son:y);
			now[x]=0;
		}
		inline void init(){
			bit.resize(n-rt+1);
			dfs1(rt,0);
			F(i,1,n)pre[i]=pre[i-1],pre[i][time[i]]=1;
			dfs2(rt,0,0);
		}
	}t[N];
	inline short main(){
		n=read(),m=read();
		F(i,2,n){
			int x=read(),y=read();
			g[x].push_back(y),
			g[y].push_back(x);
		}
		F(i,1,n)t[i].rt=i,t[i].init();
		F(i,1,m){
			int x=read(),y=read();
			w[x][y]=w[y][x]=1;
			q[++tl]=(pii){x,y};
		}
		std::bitset<N> nxt;
		while(hd<=tl){
			auto yubaisb=q[hd++];
			int x=yubaisb.first,y=yubaisb.second;
			now=x<y?t[x].bit[y-x]:t[y].bit[x-y];
			nxt=(now&w[x])^(now&w[x]&w[y]);
			for(int i=nxt._Find_first();i!=nxt.size();i=nxt._Find_next(i))if(i!=x&&i!=y){
				w[i][y]=w[y][i]=1;q[++tl]=(pii){i,y};
			}
			std::swap(x,y);
			nxt=(now&w[x])^(now&w[x]&w[y]);
			for(int i=nxt._Find_first();i!=nxt.size();i=nxt._Find_next(i))if(i!=x&&i!=y){
				w[i][y]=w[y][i]=1;q[++tl]=(pii){i,y};
			}
		}
		int cnt=0;
		F(i,1,n)F(j,i+1,n)cnt+=w[i][j];
		pi(cnt);
		return 0;
	}
}
signed main(){return EMT::main();}
```

---

## 作者：约瑟夫用脑玩 (赞：8)

本文偏理解，~~故不讲究完全的严谨~~。

以下的边均指图 $G$ 中的边，而树边才指 $T$ 中的边。

首先我们发现 $G$ 中连边与在 $T$ 中路径顺序有关，我们希望用 $G$ 转化出性质相同的 $G'$ 尽可能像 $T$ 从而得到一些有利条件方便处理。

注：性质相同指可以生成相同的最终图，这里说的是转化，也就是说可能删边，但性质相同即可。

考虑一个三元组 $(a,b,c)$，满足以某种顺序在 $T$ 中的一条路径上，且在 $G_x$ 中连通，$G_x$ 表示 $G$ 转化到 $G'$ 过程中的某个图。

如果有边 $(a,b)$ 和 $(b,c)$，那么 $(a,c)$ 是可以生成的，也就是说三条边最后都一定会出现，于是我们先不关心每条边原本是否出现。

考虑 $(a,b,c)$ 在 $T$ 路径上的顺序，如果顺次是 $a,b,c$：

![](https://cdn.luogu.com.cn/upload/image_hosting/n8wgtwym.png?x-oss-process=image/resize,m_lfit,h_75,w_75)

那么两端的边 $(a,c)$ 在 $G'$ 中没有什么必要，而 $(a,b),(b,c)$ 就得出现在 $G'$ 中。

现在考虑边原本是否出现，如果 $(a,b),(b,c)$ 中有边原本没有出现，就把它加上，可以看作是用 $(a,b)/(b,c)$ 替换掉了 $(a,c)$。

那么我们直接把 $(a,c)$ 丢掉，看 $(a,b),(b,c)$ 中没有就补上，一直这样转化，最后生成了一个图 $G'$。

从 $T$ 的角度看这个过程，每条 $G_x$ 的边相当于是 $T$ 的一条路径，每次把跨越了，或者说包含了，有相同端点的其他路径的路径给截成两段，如果后面一段没出现就添加那一段路径。

那么 $G'$ 的长相应当是：很多个连通块，每条边代表 $T$ 上的一条路径且有端点相同代表的路径在 $T$ 上无包含，但注意，这些路径是可以有交的，只是不能包含。

$G'$ 与 $T$ 长得像的好处是我们可以得到性质：对于两个点有边当且仅当在 $G'$ 上对应了一段路径，且这段路径上的点对应到 $T$ 上顺次为简单路径。

充分性显然，我们可以依次连边连过去，必要性也显然，因为每种能连出来的边的连边过程按 $G'$ 的转化方法那么截最后一定对应 $G'$ 上一段路径。

我们对每个点在 $T$ 上 DFS（也可以 BFS），把 $G'$ 路径上的上一个点带着走，顺便就可以把上面的性质判断出来，于是可以做到统计答案。

如何转化 $G'$？设计一个函数 $L(x,y)$ 表示加一段 $(x,y)$ 的路径。

再设状态 $f_{x,y}$ 表示如果有 $(x,y)$ 这段路径 $x$ 会被截到哪里，初始 $f_{x,y}=x$，如果 $f_{x,y}=y$ 代表之前已经有了这样的一段路径。

函数 $L(x,y)$ 实现：

- 先用 $f_{x,y},f_{y,x}$ 把 $(x,y)$ 截到最短，并标记 $f_{x,y}=y,f_{y,x}=x$，代表现在有了这样的一段路径，当然如果已经有了就退出。
- 对于端点 $x$ 预处理会怎么截后面的路径，即更新 $f_{x,z}$ 或截出后面一段路径，对端点 $y$ 同理:

  - 如果有包含 $(x,y)$ 的路径 $(x,z)$ 且 $f_{x,z}=x$ 表示没被截，就把它截成 $(y,z)$，即 $f_{x,z}=y$。并继续向后找路径截（起码包含了 $(x,z)$ 的其他路径，肯定也包含了 $(x,y)$）。
    
  - 如果有包含 $(x,y)$ 的路径 $(x,z)$ 且 $f_{x,z}=p$ 一定表示是有这样一段路径，即一定有 $p=z$，因为 $(x,y)$ 已经被截得最短了。那么截掉它，调用 $L(y,z)$，表示加一段路径 $(y,z)$，不再往后找路径，因为后面一定都被 $(x,z)$ 给截掉了。
  
将上述所说拼成一份代码就完了，将 $n,m$ 看作同阶，则复杂度 $O(n^2)$。

复杂度分析：先考虑截短，每次加边调用一次 $L(c_i,d_i)$，令 $d=dist(c_d,d_i)$，每次截短 $d$ 都会减少，至多减少 $d$ 次，故复杂度 $O(n)$，加边截短总复杂度 $O(mn)$。

再考虑更新，$f_{x,y}$ 总共只有 $O(n^2)$ 的状态，且每个只会更新一次，故复杂度为 $O(n^2)$。

特殊的，这里有递归截短，令 $d'=(y,z)$，这样一段路径中间必定要更新 $f_{x,y},f_{x,v_1},f_{x,v_2},\dots,f_{x,v_k}(,f_{x,z})$ 这 $d'$ 个状态，故与更新复杂度相同，$O(n^2)$。

[代码](https://www.luogu.com.cn/paste/p6i2halw)：其中 $Lnk$ 函数就是题解中的 $L$ 函数。

Upd：复杂度分析。

Upd：更正了对 $L(x,y)$ 函数的一些描述。

Upd：补充了代码。

---

## 作者：xht (赞：4)

## [Adding Edges](https://atcoder.jp/contests/agc033/tasks/agc033_f)

### 题意

- 给定一棵 $n$ 个点的树 $T$ 和一张 $n$ 个点 $m$ 条边的无向图 $G$。
- 每次可以选择三个满足下列条件的整数 $a,b,c$，在 $G$ 中添加边 $(a,c)$：
  - $G$ 中存在边 $(a,b)$ 和 $(b,c)$，但不存在边 $(a,c)$。
  - $T$ 中存在一条简单路径以某种顺序包含了 $a,b,c$。
- 求最终 $G$ 中的边数。
- $n,m \le 2 \times 10^3$。

### 题解

考虑压缩 $G$，如果存在 $(a,b),(a,c)$ 且在 $T$ 中存在一条路径**顺次**包含 $a,b,c$，那么删除 $(a,c)$ 加上 $(b,c)$ 不改变答案。

对 $G$ 进行充分压缩后，有结论：最终 $(x,y)$ 有边当且仅当存在 $a_1,a_2,\cdots,a_t$ 满足：

- $a_1 = x$，$a_t = y$。
- $G$ 中存在边 $(a_i,a_{i+1})$。
- $T$ 中存在一条路径顺次包含 $a_1,a_2,\cdots,a_t$。

这个就很好统计了，考虑如何压缩 $G$。

对于一条加边 $(a,b)$，记 $p(a,b)$ 表示在 $T$ 中以 $a$ 为根离 $b$ 最近且在 $G$ 中与 $b$ 相连的祖先，若 $p(a,b)$ 存在，则应该直接加 $(b,p(a,b))$，否则将 $b$ 子树打上标记，碰到边时压缩即可。

时间复杂度 $\mathcal O(n(n+m))$。

### 代码

```cpp
const int N = 2e3 + 7;
int n, m, ans;
vi e[N];
int f[N][N], p[N][N];
bool g[N][N];

void dfs(int x, int *f) {
	for (int y : e[x])
		if (y != f[x]) f[y] = x, dfs(y, f);
}

inline void add(int x, int y) {
	if (p[x][y] == y || p[y][x] == x) return;
	if (p[x][y]) return add(p[x][y], y);
	if (p[y][x]) return add(p[y][x], x);
	vector<pi> a;
	for (int i = 0; i < 2; i++) {
		g[x][y] = 1, p[x][y] = y;
		queue<int> q;
		q.push(y);
		while (q.size()) {
			int u = q.front();
			q.pop();
			for (int v : e[u])
				if (v != f[x][u]) {
					if (!p[x][v]) p[x][v] = y, q.push(v);
					else if (g[x][v]) g[x][v] = g[v][x] = 0, a.pb(mp(y, v));
				}
		}
		swap(x, y);
	}
	for (pi o : a) add(o.fi, o.se);
}

void dfs1(int x, int t, int *f) {
	if (p[t][x] == x) ++ans, t = x;
	for (int y : e[x])
		if (y != f[x]) dfs1(y, t, f);
}

int main() {
	rd(n, m);
	for (int i = 1, x, y; i < n; i++) rd(x, y), e[x].pb(y), e[y].pb(x);
	for (int x = 1; x <= n; x++) dfs(x, f[x]);
	for (int i = 1, x, y; i <= m; i++) rd(x, y), add(x, y);
	for (int x = 1; x <= n; x++)
		for (int y : e[x]) dfs1(y, x, f[x]);
	print(ans >> 1);
	return 0;
}
```

---

