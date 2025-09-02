# Mocha and Diana (Hard Version)

## 题目描述

给你两棵森林，节点数均为 $n$。

允许你进行加边操作，但是有两个要求：

- 如果在第一个森林加一条 $(u,v)$ 的边，第二个森林也要进行同样的操作。反之同理。
- 加边后两个森林依旧是森林。（一棵树也是森林）

求最多能加几条边，并输出加边方案。

## 样例 #1

### 输入

```
3 2 2
1 2
2 3
1 2
1 3```

### 输出

```
0```

## 样例 #2

### 输入

```
5 3 2
5 4
2 1
4 3
4 3
1 4```

### 输出

```
1
2 4```

## 样例 #3

### 输入

```
8 1 2
1 7
2 6
1 5```

### 输出

```
5
5 2
2 3
3 4
4 7
6 8```

# 题解

## 作者：Demoe (赞：42)

[$\large\text{题目传送门}$](https://www.luogu.com.cn/problem/CF1559D2)

## $\text{Description}$

- 给定图 $A$，$B$，每次操作可在两图内加边 $(u,v)$，要求两图仍为森林。

- 求最大操作次数和一种方案。

## $\text{Solution}$

很好的贪心题。

不妨令 $A$ 图连通块个数不小于 $B$ 图。

我们证明 $B$ 图最后连通块个数为 $1$。

若 $A$ 连通块数量大于 $1$，若此时无法操作，考虑到 $A$ 图中连通块 $a$，$b$。

对于 $a$，$b$ 中的点，他们在 $B$ 图中一定连通。

那么考虑到 $A$ 中所有连通块，可发现 $B$ 全连通，即连通块数量为 $1$。

由此贪心分析可知，随意加可行边即可。

因此 D1 就可以直接暴力枚举点对加边即可，时间复杂度 $O(n^2\alpha(n))$。

---

考虑优化贪心。

考虑一个中心点 $s$。

我们先让所有点与 $s$ 尝试连边。

然后连完后令 $A$ 图中与 $s$ 不连通的点集为 $L$，$B$ 图中与 $s$ 不连通的点集为 $R$。

显然 $L\cap R=\varnothing$。

考虑 $l\in L$ 和 $r\in R$。

由定义有 $A$ 图中 $l$ 与 $s$ 不连通，$r$ 与 $s$ 连通，$B$ 图相反。

那么任意 $l$ 与 $r$ 都可连边。

然后只要随意配对完 $L$ 或 $R$ 就行了，此时一幅图变成一个连通块。

时间复杂度 $O(n\alpha(n))$。

## $\text{Code}$

我写的 $O(n\log n)$ 的并查集，没加按秩合并。

```cpp
const int N=1e5+5;
int n,m1,m2,fa1[N],fa2[N],ans,qaq[N][2],l[N],r[N],cnt1,cnt2;

inline int find1(int x){return fa1[x]==x?x:fa1[x]=find1(fa1[x]);}
inline void merge1(int x,int y){fa1[find1(x)]=find1(y);}

inline int find2(int x){return fa2[x]==x?x:fa2[x]=find2(fa2[x]);}
inline void merge2(int x,int y){fa2[find2(x)]=find2(y);}

// ---------- DSU ---------- //

int main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
//	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	rd(n);rd(m1);rd(m2);
	for(re i=1;i<=n;++i) fa1[i]=fa2[i]=i;
	for(re i=1;i<=m1;++i){
		int x,y;rd(x);rd(y);merge1(x,y);
	}
	for(re i=1;i<=m2;++i){
		int x,y;rd(x);rd(y);merge2(x,y);
	}
	for(re i=2;i<=n;++i)
		if(find1(i)!=find1(1)&&find2(i)!=find2(1)) qaq[++ans][0]=i,qaq[ans][1]=1,merge1(i,1),merge2(i,1);
	for(re i=2;i<=n;++i)
		if(find1(i)!=find1(1)) l[++cnt1]=i,merge1(i,1);
		else if(find2(i)!=find2(1)) r[++cnt2]=i,merge2(i,1);
	wr(ans+min(cnt1,cnt2));puts("");
	for(re i=1;i<=ans;++i) wr(qaq[i][0]),putchar(' '),wr(qaq[i][1]),puts("");
	for(re i=1;i<=min(cnt1,cnt2);++i) wr(l[i]),putchar(' '),wr(r[i]),puts("");
	return 0;
}

// ---------- Main ---------- //
```

---

## 作者：Macesuted (赞：12)

[在我的个人博客中阅读](https://macesuted.cn/article/cf1559d2/)

[题目链接](https://codeforces.com/problemset/problem/1559/D2)

## 题目大意

给出两个 $n$ 个点的无向无环图（可能不连通），你可以进行若干次加边操作，每次加边操作可以在两个图上同时加入一条边 $(x,~y)$，要求加边操作结束后两个图仍然是无向无环图。让你求出最大的加边次数并输出任意一种方案。

$n \le 10^5$

## 分析

由 [CF1559D1](https://codeforces.com/problemset/problem/1559/D1) 我们会发现以任何顺序尽可能多地加入合法边都不会影响最终答案。

考虑先尽可能多地加入形如 $(1,~x)$ 的边，加入完这些边后所有的结点至少在一个图中与 $1$ 在同一个联通块中，此时我们可以将所有的点分为三类：

1. 第一个图中与 $1$ 联通，第二个图中与 $1$ 联通。
2. 第一个图中与 $1$ 不联通，第二个图中与 $1$ 联通。
3. 第一个图中与 $1$ 联通，第二个图中与 $1$ 不联通。

容易发现对于所有的 1 类点其不可能再与其他点连边。因为对于每一个点， $1$ 在至少一个图中与他们联通，而该点在两个图中均与 $1$ 联通，所以每一个点均与该点在至少一个图中联通。

我们将所有的 2 类点和 3 类点找出并放入两个集合。此时对于所有的剩余的合法边，其两个端点一定为 2 类点或 3 类点。而我们发现 2 类点之间互相连通，3 类点间也互相连通，所以所有的可能的合法连边的两个端点一定是一个 2 类点和一个 3 类点，且任意一个 2 类点与任意一个 3 类点均可组成一条合法边。每次从两个集合中分别取出一个点，将他们连边后再从两个集合中删去不符合 2 类点或是 3 类点性质的点并重复此操作至集合为空即可。

## 代码

[View on Github](https://github.com/Macesuted/Code/blob/main/CodeForces/1559D2.cpp)

---

## 作者：云浅知处 (赞：11)

> 给定两个森林 $G_1=(V,E_1)$ 和 $G_2=(V,E_2)$，点数均为 $n$，边数分别为 $m_1,m_2$。
>
> 每次可以选择两个点 $u,v\in V$，如果：
>
> -  $(u,v)\not\in E_1$ 且 $(u,v)\not\in E_2$
> - 连上边 $(u,v)$ 后， $G_1,G_2$ 均仍为森林
>
> 那么就可以把它们连上，求能连上的边数的最大值。要求输出方案。
>
> Easy version: $m_1,m_2\le n\le 1000$
>
> Hard version: $m_1,m_2\le n\le 2\times10^5$

很有趣的题。

首先我们注意到如果此时能连上一条边 $(u,v)$ ，那么把它们连上必然不会使答案变差。

因此对于 Easy version 我们就只需要暴力 $O(n^2)$ 枚举 $u$ 和 $v$，不断加边加边加边，然后加边的时候并查集查询就可以了。

这个复杂度是 $O(n^2\log n)$ 的，$\log $ 来自并查集。

对于 Hard version，我们考虑先令 $u=1$，然后连上尽可能多的边。不过这样连完之后还会剩下一些边。

这样连完之后两个图内就都会有一个 $1$ 附近的很大的连通块，和一些其他的不和 $1$ 连通的点。

我们考虑 $G_1$ 中的一个不和 $1$ 联通的点 $x$ 与 $G_2$ 中不和 $1$ 联通的点 $y$，那么我们注意到一个重要的性质：

> 如果 $G_2$ 中的 $x$ 也不和 $1$ 联通，那么我们就可以连一条边 $(1,x)$，但是这条边在之前的过程中已经连过了。
>
> 所以对于点 $x$，必然是它在 $G_1$ 中和 $1$ 不连通，在 $G_2$ 中和 $1$ 连通。

对于 $y$ 也同理。

接下来我们考虑连一条边 $(x,y)$。

我们发现，由于 $G_1$ 中 $y$ 必然在 $1$ 附近的连通块内，而 $x$ 不在，因此连上 $(x,y)$ 后，$G_1$ 中不会出现环，所以仍然是森林。

对于 $G_2$ 也同理。由此，连接 $(x,y)$ 是一个可行解，由 Easy version 它也一定是最优解。

那么我们在做完第一步之后，只需要处理出 $G_1,G_2$ 中不和 $1$ 联通的两个点集，然后取较小的那个与较大的那个随便连边就行了。

代码很丑，就贴个 Link 吧。

复杂度大概是 $O(n\log n)$，如果使用了按秩合并的优化可以做到 $O(n\alpha(n))$。

[Easy ver.](https://codeforces.com/contest/1559/submission/125981501)

[Hard  ver.](https://codeforces.com/contest/1559/submission/126012244)



---

## 作者：遮云壑 (赞：7)

# Description
- 给定两个点集完全相同的森林 $A$ , $B$ ,两个图的连边方式不一样
- 在两个图中同时选两个点连边，使 $A$, $B$ 仍为森林
- 求最大的连边数量及方案

看不懂的，[出门左转](https://www.luogu.com.cn/problem/CF1559D2)

# Solution
- 分析题目，仅仅需要维护连通性，很显然需要并查集。
- 那么 D1 其实就出来了，暴力枚举 $u$ , $v$ ,看在 $A$ , $B$ 中是否在同一集合中，如果不同在，连边，复杂度 $O(n^2\alpha (n))$


-----------
#### 重点在D2

我们把相连的点视为一个集合

当我们任意选取 $u$ , $v$ 不难发现，一共会有如下几种情况

-  $u$ , $v$ 在 $A$ , $B$ 都是在同一集合
-  $u$ , $v$ 在 $A$ 中是同一集合， $B$ 中不是
-  $u$ , $v$ 在 $B$ 中是同一集合， $A$ 中不是
-  $u$ , $v$ 在 $A$ , $B$ 中都不是同一集合

前三种情况我们都不能连边，只有第四种情况可以连边

如果我们可以控制第四种情况就好了。。。

怎么办呢，于是这题最最关键的一点就出来了

### 确定一个中心点

比如说，我们设1号点为中心点。此时，其他点依然有四种情况

- 在 $A$ , $B$ 中都与1相连
- 仅在 $A$ 中与1相连
- 仅在 $B$ 中与1相连
- 在 $A$ , $B$ 中都不与1相连

对于第一种情况，不可能连边。如果，我们把所有的第四种情况的点都变成第一种（和1连边），那么除去第一种情况的点，剩下的点要么在 $A$ 中与1同一集合（第二类点），要么在 $B$ 中与1同一集合（第三类点），所以在二类点中选一个 $u$ ,在三类点中选一个 $v$ ，那么 $(u,v)$ 在 $A$ , $B$ 中一定都不是同一集合，我们只要选两类点中找数量少的那一类，和另外一类随意连边就可以了。

还有一个小问题，二三类点怎么找， vector 存吗？

其实根本不需要，只要 for 扫一遍，并查集 find(i)!=find(1) 就行了。

# Analyse

这样连完后，任意选取一个点对 $(u,v)$ ，肯定在 $A$ , $B$ 中同时与1在一个集合，不可能再连边，正确性可以保证。

整个过程我们只需要把所有点扫两遍就行了，总时间复杂度 $O(n\alpha(n))$ 。

# Code
这题代码不难，基本上带着说完了

[出门右转](https://codeforces.com/contest/1559/submission/133727526)

# Conclusion

这道题想法很新颖，给森林连边，使用的思路也很巧妙，**选取中心点**连边保证连通性。当一个题目毫无思路的时候，我们是否可以像这题一样特殊化一个点，让问题变简单，这也许是一个新的思路。

---

## 作者：王熙文 (赞：5)

题解区怎么都是与一个点连边的题解？这里提供一个别的做法，应该更好想一些。

upd on 2024.4.12: 连通块大小的总和写错了，修改一下。

## 思路

先考虑 D1，猜想最多的操作次数就是 $n-1-\max(m1,m2)$，即一定可以一直连，直到一个森林变成树。证明就是考虑证明任意两个不是树的森林第一次都可以操作，而这个可以反证，如果不能操作则两棵树必定连通。如果第一次可以操作，则使用数学归纳法即可证明第一个结论。

因此现在只需要每次快速找到可以连边的点，而不需要决策了。对于 D1，直接枚举每个点对即可（因为如果当前点对连不了则以后也连不了，所以可以直接跳过）。

还有一个结论是，在某一棵树一个连通块中一定能选出来一个点连边。这个结论可以在下面的构造中看出来。

因为是集合总和有保证，所以可以想一些奇怪的根号做法。可以发现，每次拿出来最小的连通块，~~这些连通块大小的总和是 $\mathcal O(n\sqrt{n})$ 的。证明是考虑当连通块个数大于根号时最小的集合大小小于等于根号，当连通块个数小于等于根号时合并的个数小于等于根号。~~这些连通块大小的总和是 $\mathcal O(n\log n)$ 的。因为这相当于启发式合并，最小的连通块在两个连通块中一定是较小的。

考虑第一棵树最小的连通块的点在第二棵树的连通块位置，设为 $wz_1,wz_2,\cdots,wz_k$。如果 $wz$ 中有不同的数，则任选一个不在当前连通块的点去尝试匹配这两个不同的数，一定至少有一个不相同，即可连边。否则，在第二棵树中任选一个不是当前连通块的连通块即可连边。


使用 `set` 模拟上述过程即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m1,m2;
int fa[2][100010];
int find(int op,int x)
{
	while(x!=fa[op][x]) x=fa[op][x]=fa[op][fa[op][x]];
	return x;
}
vector<int> vec[100010];
struct Set
{
	int wz;
	bool operator < (Set x) const { return vec[wz].size()==vec[x.wz].size()?wz<x.wz:vec[wz].size()<vec[x.wz].size(); }
}; set<Set> q;
set<int> st;
int tot=0; pair<int,int> ans[100010];
bool vis[100010];
void merge(int x,int y)
{
	int fx=find(0,x),fy=find(0,y);
	q.erase({fx}),q.erase({fy});
	while(!vec[fx].empty()) vec[fy].push_back(vec[fx].back()),vec[fx].pop_back();
	fa[0][fx]=fy,q.insert({fy});
	fx=find(1,x),fy=find(1,y);
	fa[1][fx]=fy,st.erase(fx);
}
int main()
{
	cin>>n>>m1>>m2;
	for(int i=1; i<=n; ++i) fa[0][i]=fa[1][i]=i;
	for(int i=1; i<=m1; ++i)
	{
		int u,v; cin>>u>>v;
		fa[0][find(0,u)]=find(0,v);
	}
	for(int i=1; i<=m2; ++i)
	{
		int u,v; cin>>u>>v;
		fa[1][find(1,u)]=find(1,v);
	}
	for(int i=1; i<=n; ++i) vec[find(0,i)].push_back(i);
	for(int i=1; i<=n; ++i) if(i==fa[0][i]) q.insert({i});
	for(int i=1; i<=n; ++i) if(i==fa[1][i]) st.insert(i);
	while(q.size()>=2 && st.size()>=2)
	{
		vector<int> now=vec[(*q.begin()).wz];
		for(int i:now) vis[i]=1;
		int other=1; while(vis[other]) ++other;
		int fother=find(1,other);
		for(int i:now) vis[i]=0;
		int ffirst=find(1,now[0]);
		bool flag=0;
		for(int i=1; i<now.size(); ++i)
		{
			int fnow=find(1,now[i]);
			if(fnow!=ffirst)
			{
				if(fnow!=fother) ans[++tot]={now[i],other},merge(now[i],other);
				else ans[++tot]={now[0],other},merge(now[0],other);
				flag=1;
				break;
			}
		}
		if(!flag)
		{
			auto wz=st.begin();
			if(*wz==ffirst) ++wz;
			ans[++tot]={now[0],(*wz)},merge(now[0],(*wz));
		}
	}
	cout<<tot<<'\n';
	for(int i=1; i<=tot; ++i) cout<<ans[i].first<<' '<<ans[i].second<<'\n';
	return 0;
}
```

---

## 作者：KaisuoShutong (赞：5)

## CF1559D2 Mocha and Diana (Hard Version)
[弱化版题解](https://www.luogu.com.cn/blog/Criticism/solution-cf1559d1)

### 题意
两片森林，都有一些初始边。求以下操作的最多次数，使得图中无环，并输出方案。  
操作：选择 $x,y$，在两片森林中分别连边。  
$n\leq1000$。

### 题解
这个做法是在 CF 讨论区中看到的，同时建议看之前先浏览弱化版的做法和正确性证明。

我们先对于 $\forall i\in[2,n]$，都尝试和 $1$ 连边 $(1,i)$。  
那么，不难知道此时 $\forall i$ 都在至少一片森林中与 $1$ 属于同一棵树。

此时，对于在第一棵树上与 $1$ 不属于同一棵树的 $i$，加入到栈 $p$ 中；  
同理，对于在第二棵树上与 $1$ 不属于同一棵树的 $i$，加入到栈 $q$ 中。

最后，扫描两个栈，当两个栈都非空时，进行如下操作：
1. 若 $p$ 栈顶在第一棵树上已经与 $1$ 连通，$p$ 弹栈；
2. 若 $q$ 栈顶在第二棵树上已经与 $1$ 连通，$q$ 弹栈；
3. 否则，加边 $(p,q)$，分别合并其与 $1$ 的连通块；

不难证明，最后连通性与弱化版证明中提到的一致。

点个赞吧。

```cpp
//月亮照耀青窗，窗里窗外皆有青色的光。
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int read() {
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+(ch^48),ch=getchar();
	return s*w;
}
const int maxn = 1e5+10;
int n,m1,m2,f[maxn],g[maxn],p[maxn],q[maxn];vector<pair<int,int> >Q;
int GF(int x) {return f[x]==x?x:f[x]=GF(f[x]);}
int gf(int x) {return g[x]==x?x:g[x]=gf(g[x]);}
signed main() {
	n=read(),m1=read(),m2=read();
	for(int i=1;i<=n;i++) f[i]=g[i]=i;
	for(int i=1;i<=m1;i++) f[GF(read())]=GF(read());
	for(int i=1;i<=m2;i++) g[gf(read())]=gf(read());
	GF(1),gf(1);for(int i=2;i<=n;i++)
		if(GF(i)^f[1]&&gf(i)^g[1]) f[f[i]]=f[1],g[g[i]]=g[1],Q.push_back(make_pair(1,i));
		else if(f[i]^f[1]) p[++p[0]]=i;
		else if(g[i]^g[1]) q[++q[0]]=i;
	while(p[0]&&q[0])
		if(GF(p[p[0]])==f[1]) --p[0];
		else if(gf(q[q[0]])==g[1]) --q[0];
		else f[f[p[p[0]]]]=f[1],g[g[q[q[0]]]]=g[1],Q.push_back(make_pair(p[p[0]--],q[q[0]--]));
	cout<<Q.size()<<'\n';for(auto y:Q) cout<<y.first<<' '<<y.second<<'\n';
	return 0;
}
```

---

## 作者：FoXreign (赞：5)

**题意**：给你两张图，顶点数相同，初始边不同，在保证两张图是**树形结构**的情况下同时加边，问最多可以加多少条边，分别是哪些边。

**题目分析**：hard version $n$ 的数据范围显然不允许我们使用 $n^2$ 的算法，官方题解用的是启发式合并，其实评论区神犇给出了一种更优的解决方式：

首先任选一点 $i$ ，尝试将 $i$ 与其它所有点连边，设以点 $i$ 为中心的大集合为 $U$ ，此时会出现三种情况：

- 两张图中，均有 $j \notin U$ ，在点 $i$ 与 点$j$ 间加一条边，并将点 $j$ 丢进 $U$ 中

- 在第一、二张图中，分别有 $j \notin U1$ 与 $j \in U2$ ，我们将 $j$ 记录下来并存入堆栈 $v1$ 中

- 与上述情况相反，我们将 $j$ 记录下来并存入堆栈 $v2$ 中

接下来我们要做的就是匹配这些没有进入“大集合”中的点:

- 如果 $v1$ 顶部的点在大集合 $U1$ 中，则将其删除

- 如果 $v2$ 顶部的点在大集合 $U2$ 中，则将其删除

- 否则，在 $v1$ 顶部的点和 $v2$ 顶部的点之间添加一条边。

感性地理解下，就是先找到一个点，把它能连上的边全连了，然后再根据两张图的情况在剩下的点间连边

可以证明该算法的正确性，且其复杂度近乎为 $O(n+m)$

**AC代码**：
```
#include <bits/stdc++.h>
#define rep(i, x, y) for (register int i = (x); i <= (y); i++)
#define down(i, x, y) for (register int i = (x); i >= (y); i--)
#define pii std::pair<int, int>
#define mp std::make_pair
const int maxn = 1e5 + 10;

int n, m1, m2, x, y, fa1[maxn], fa2[maxn];
std::vector<int> v1, v2;
std::vector<pii> ans;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

inline int find1(int x) { return x == fa1[x] ? x : fa1[x] = find1(fa1[x]); }

inline int find2(int x) { return x == fa2[x] ? x : fa2[x] = find2(fa2[x]); }

void merge1(int x, int y)
{
    int fx = find1(x), fy = find1(y);
    if (fx == fy)
        return;
    fa1[fx] = fy;
}

void merge2(int x, int y)
{
    int fx = find2(x), fy = find2(y);
    if (fx == fy)
        return;
    fa2[fx] = fy;
}

int main(int argc, char const *argv[])
{
    n = read(), m1 = read(), m2 = read();
    rep(i, 1, n) fa1[i] = fa2[i] = i;
    rep(i, 1, m1)
    {
        x = read(), y = read();
        merge1(x, y);
    }
    rep(i, 1, m2)
    {
        x = read(), y = read();
        merge2(x, y);
    }
    rep(i, 2, n)
    {
        int fx1 = find1(1), fy1 = find1(i);
        int fx2 = find2(1), fy2 = find2(i);
        if (fx1 ^ fy1 && fx2 ^ fy2)
        {
            merge1(1, i), merge2(1, i);
            ans.push_back(mp(1, i));
        }
        if (fx1 ^ fy1)
            v1.push_back(i);
        if (fx2 ^ fy2)
            v2.push_back(i);
    }
    while (v1.size() && v2.size())
    {
        x = v1.back(), y = v2.back();
        int f1 = find1(1), f2 = find2(1);
        int fx = find1(x), fy = find2(y);
        if (fx == f1)
        {
            v1.pop_back();
            continue;
        }
        if (fy == f2)
        {
            v2.pop_back();
            continue;
        }
        merge1(x, y), merge2(x, y);
        ans.push_back(mp(x, y));
    }
    printf("%d\n", ans.size());
    while (ans.size())
    {
        printf("%d %d\n", ans.back().first, ans.back().second);
        ans.pop_back();
    }
    return 0;
}

```

---

## 作者：AxDea (赞：1)

[题](https://www.luogu.com.cn/problem/CF1559D2)[面](http://codeforces.com/problemset/problem/1559/D2)

考虑把每个点看成一个二元组 $(A, B)$ ， $A$ 和 $B$ 分别表示这个点在第一个和第二个森林中处在的联通块的标号。

把这些 $(A, B)$ 画到坐标系上，发现有同一个纵坐标或同一个横坐标的两点无法连边。

设 $x_1(a_1, b_1)$ 和 $x_2(a_2, b_2)$，考虑在这两个点之间连边会发生什么（保证连边合法）。

- $x_2$ 的坐标变成了 $x_1$ 的。
- 坐标为 $(?, b_2)$ 的节点都变成了 $(?, b_1)$
- 坐标为 $(a_2, ?)$ 的节点都变成了 $(a_1, ?)$

然后你想到将所有可以与 $1$ 号节点连边的点全部连边，那么最后坐标系上的点只会在直线 $y = y_1$ 和 $x = x_1$ 上存在。

把剩下的点分成两类，一类是 $(?, y_1)$ 另一类是 $(x_1, ?)$，分别按照 $?$ 排序，最后将一类的第 $k$ 小和另一类的第 $k$ 小的点连边，然后你会发现这时坐标轴上其中一条线就会从左往右移动，最后越来越短，且每次操作都是合法的。

时间复杂度 $\mathcal O (dsu + n\log n)$ 。

```cpp
#include <bits/stdc++.h>
#define forn(i,s,t) for(register int i=(s); i<=(t); ++i)
#define form(i,s,t) for(register int i=(s); i>=(t); --i)
#define rep(i,s,t) for(register int i=(s); i<(t); ++i)
using namespace std;
const int N = 1e5 + 3;
struct dsu {
	int fa[N];
	int Fnd(int u) {return fa[u] == u ? u : fa[u] = Fnd(fa[u]);}
	inline void Mrg(int u, int v) {
		u = Fnd(u), v = Fnd(v);
		if(u == v) return ;
		fa[v] = u;
	}
} M, D;
int n, m1, m2, u, v, tot, resx[N], resy[N], r1[N], r2[N], tt1, tt2;
#define x(p) M.Fnd(p)
#define y(p) D.Fnd(p)
inline bool Xcmp(int A, int B) {return y(A) < y(B);}
inline bool Ycmp(int A, int B) {return x(A) < x(B);}
int main() {
	scanf("%d%d%d", &n, &m1, &m2);
	forn(i,1,n) M.fa[i] = D.fa[i] = i;
	forn(i,1,m1) scanf("%d%d", &u, &v), M.Mrg(u, v);
	forn(i,1,m2) scanf("%d%d", &u, &v), D.Mrg(u, v);
	forn(i,2,n) if(x(i) != x(1) && y(i) != y(1)) resx[++tot] = 1, resy[tot] = i, M.Mrg(1, i), D.Mrg(1, i);
	forn(i,1,n) {
		if(x(i) == x(1) && y(i) != y(1)) r1[++tt1] = i, D.Mrg(1, i);
		if(y(i) == y(1) && x(i) != x(1)) r2[++tt2] = i, M.Mrg(1, i);
	}
	sort(r1 + 1, r1 + tt1 + 1, Xcmp);
	sort(r2 + 1, r2 + tt2 + 1, Ycmp);
	forn(i,1,min(tt1, tt2)) resx[++tot] = r1[i], resy[tot] = r2[i];
	printf("%d\n", tot);
	forn(i,1,tot) printf("%d %d\n", resx[i], resy[i]);
	return 0;
}
```

---

## 作者：Alkaid_Star (赞：1)

[可能更好的阅读体验！](https://www.encounter.cool/index.php/2021/08/23/cf1559d2-mocha-and-diana-solution/)
### 题目大意

>给定给定两张分别有 $n$ 个点 $m_1$ 条边，$n$ 个点 $m_2$ 条边的无向图 $A,B$。
>
>现在你有一种操作，可以在两张图中同时加入 $(x,y)$ 这条边。
>
>要求在每次操作后仍然满足两张图都是森林。求最多能加多少边，并输出一种合法方案。
>
>$n,m_1,m_2 \le 10^5$。

### 解题思路

神仙思维题，方法太妙了。

这道题是 [CF1559D1](https://codeforces.com/contest/1559/problem/D1) 的困难版，简单版的数据范围为 $n,m_1,m_2 \le 10^3$。

在简单版中，我们发现：

1. **能加入 $(x,y)$ 当且仅当 $x,y$ 在两张图中都属于同一个连通块。**
2. **加入边的顺序是不会影响结果的。**

对于后者的~~口胡~~证明：考虑一个最终状态，如果两个图的连通块个数均大于 1，那么我们设 $A$ 图中连通块大小分别为 $a,n-a$，$B$ 中连通块大小分别为 $b,n-b$，并且方便起见，我们设 $a,b \le \lfloor \frac{n}{2} \rfloor$ 并且 $a \le b$，那么对于一个 $a$ 中的点 $x$，如果 $x$ 在 $B$ 图的 $b$ 中，那么一定不能与 $a$ 连线的点的个数至多为 $a-1+b-1=a+b-2<n$。如果 $x$ 在 $B$ 图的 $n-b$ 中，一定不能与 $a$ 连线的个数至多为 $a-1+(n-b-1)=n+a-b-2<n$。于是一定可以找到一个点可以与 $a$ 连线。而当有一个图的连通块个数等于 1 时，一定不能再找到连线。

由此可以发现，只要最后是一个连通块，其实**合并的过程是无所谓的，加边的条数是固定的**。

可能有点不严谨，以感性理解为主。

那么考虑如何优化这个东西。官方题解是使用 `std::set` 来维护，时间复杂度 $O(n \log^2 n)$，不想写诶。

那怎么办呢？我们考虑优化这个过程，从过程中挖掘性质。

我们先确定一个点 $x$，然后先进行一波连边。

我们考虑此时连边后的这个图具有什么性质：每个点不可能两个图中都不与 $x$ 连通。

那么我们设 $A$ 中不与 $x$ 连通的点集为 $sta1$，$B$ 中不与 $x$ 连通的点集为 $sta2$。

那么由上面的性质得 $sta1$ 与 $sta2$ 的交集为空集。

我们在这两个集合里面各任取一个点 $a,b$，则 $a$ 在 $A$ 中与 $x$ 在同一连通块，$b$ 在 $B$ 中与 $x$ 不在同一连通块，那么也即 $a$ 与 $b$ 不在同一连通块。在 $B$ 图中也是同理。那么即 $a$ 与 $b$ 可以连边。

所以在 $sta1$，$sta2$ 中，我们任意各取两个点都是可以连边的，总共有 $\min\{|sta1|,|sta2|\}$ 条边，容易发现这就是最大的答案（剩下的点显然不可能再连边了）。

### Code

采用 `struct` 实现 $A,B$ 两图中的并查集，代码应该会优美一点。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500005;

int n,m1,m2;
bool used[N];
vector <int> sta1,sta2;
vector < pair <int,int> > ans;

struct DSU{
	int fa[N];
	
	inline void Init(){ for (int i=1;i<=n;++i) fa[i]=i; }

	inline int getfa(int x){
		if (fa[x]==x) return x;
		else fa[x]=getfa(fa[x]);
		return fa[x];
	}
	
	inline bool Merge(int x,int y){
		int fx=getfa(x),fy=getfa(y);
		if (fx==fy) return false;
		fa[fx]=fy;
		return true;
	}

	inline bool Query(int x,int y){
		return getfa(x)!=getfa(y);
	}
}s1,s2;

inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)){ if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)){ x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

int main(){
	//freopen("CF1559D2.in","r",stdin);
	//freopen("CF1559D2.out","w",stdout);
	n=read(),m1=read(),m2=read();
	s1.Init(),s2.Init();
	for (int i=1;i<=m1;++i){
		int x=read(),y=read();
		s1.Merge(x,y);
	}
	for (int i=1;i<=m2;++i){
		int x=read(),y=read();
		s2.Merge(x,y);
	}
	for (int i=2;i<=n;++i)
		if ((s1.Query(1,i)) && (s2.Query(1,i))){
			s1.Merge(1,i),s2.Merge(1,i);
			ans.push_back(make_pair(1,i));
			used[i]=true;
		}
	for (int i=2;i<=n;++i){
		if (used[i]) continue;
		if (s1.Query(1,i)){ sta1.push_back(i); s1.Merge(1,i); }
		else if (s2.Query(1,i)){ sta2.push_back(i); s2.Merge(1,i); }
	}
	for (int i=0;i<min(sta1.size(),sta2.size());++i)
		ans.push_back(make_pair(sta1[i],sta2[i]));
	printf("%d\n",ans.size());
	for (int i=0;i<ans.size();++i)
		printf("%d %d\n",ans[i].first,ans[i].second);
	return 0;
}
```



---

## 作者：sky_123 (赞：1)

这道题貌似可以用各种随机乱搞等各种玄学卡过去，这里给出一个比较科学的的做法。
先说结论：最终边数较多的图一定连成了一棵树。
首先是加边问题，显然只要遇到满足条件的边就直接加上结果一定不会变差。因为假设加上这一条边会使得有两条及以上边加不上，因为加这条边影响的边只能是连接和这条边一样的连通分量的边，而这样的边要是加两条一定会出现环，这与条件矛盾，因此贪心的加即可。
然后考虑加边的策略，首先先按这种策略加边：枚举所有点，如果在两个图中均可以向节点 $1$ 连边则直接连边。这样处理的结果是一定是下图所示类型：![在这里插入图片描述](https://img-blog.csdnimg.cn/8210663d8ffb45e994da8f7c76b98e97.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzQ1MzIzOTYw,size_16,color_FFFFFF,t_70)
其中一种颜色代表一类点集，相同颜色代表同一点集。
可以发现，此时可以继续加的边只能是蓝色和绿色点集之间的边，进而可以得出对于两图中不包含节点 $1$ 的连通分量只能向外连至多一条边，并且不包含节点 $1$ 的连通分量数量较少的图一定能连成一棵树。由此可以通过双指针 $O(n)$ 将剩余部分连完。并查集操作近似看做常数，总时间复杂度为 $O(n)$ 。
```cpp
#include <bits/stdc++.h>

using namespace std;
const int N = 1e5 + 10;

struct Union_Find {
    int fa[N], rnk[N];

    inline void init(int n) { iota(fa + 1, fa + 1 + n, 1); }

    int get(int x) { return x == fa[x] ? x : (fa[x] = get(fa[x])); }

    inline void merge(int x, int y) {
        x = get(x), y = get(y);
        if (x == y) return;
        if (rnk[x] < rnk[y]) swap(x, y);
        fa[y] = x;
        if (rnk[x] == rnk[y]) rnk[x]++;
    }

    inline bool same(int x, int y) { return get(x) == get(y); }
} U1, U2;

int n, m1, m2, ans;

int main() {
    scanf("%d%d%d", &n, &m1, &m2);
    U1.init(n), U2.init(n);
    for (int i = 1, x, y; i <= m1; i++)
        scanf("%d%d", &x, &y), U1.merge(x, y);
    for (int i = 1, x, y; i <= m2; i++)
        scanf("%d%d", &x, &y), U2.merge(x, y);
    printf("%d\n", ans = n - 1 - max(m1, m2));
    for (int i = 2; i <= n; i++) {
        if (U1.same(1, i) || U2.same(1, i)) continue;
        printf("1 %d\n", i), ans--;
        U1.merge(1, i), U2.merge(1, i);
    }
    for (int i = 2, j = 1; ans; i++) {
        if (U1.same(1, i)) continue;
        while (U2.same(1, j)) j++;
        printf("%d %d\n", i, j), ans--;
        U1.merge(1, i), U2.merge(1, j);
    }
    return 0;
}
```

---

## 作者：FjswYuzu (赞：0)

先判断其他的所有点 $a$，是否可以添加一条 $1,a$ 间的边。如果可以就填上作为答案中的一条边，否则暂先不管。

注意到，在经过这个操作之后，对于每个其他的点 $a$，在两个图 $G_1,G_2$ 中，$(1,a) \in G_1,(1,a) \in G_2$ 中有一个满足。将**只满足一个**的点按属于 $G_1$ 还是 $G_2$ 分类，得到两个点集 $S,T$。显然 $S,T$ 里面的点可以互相连边。于是答案还要多上 $\min(|S|,|T|)$ 条边。输出答案即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct unionFindSet{
	int fa[100005];
	void makeSet(int up){for(int i=0;i<=up;++i)	fa[i]=i;}
	int findSet(int x)
	{
		if(x==fa[x])	return x;
		return fa[x]=findSet(fa[x]);
	}
	void unionSet(int x,int y)
	{
		int xx=findSet(x),yy=findSet(y);
		if(xx==yy)	return ;
		fa[xx]=yy;
	}
}ufs1,ufs2;
#define mp make_pair
int n,m1,m2;
bool Link(int u,int v){return ufs1.findSet(u)!=ufs1.findSet(v) && ufs2.findSet(u)!=ufs2.findSet(v);}
void Merge(int u,int v){ufs1.unionSet(u,v),ufs2.unionSet(u,v);}
int main(){
	scanf("%d %d %d",&n,&m1,&m2);
	ufs1.makeSet(n);
	ufs2.makeSet(n);
	for(int i=1;i<=m1;++i)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		ufs1.unionSet(u,v);
	}
	for(int i=1;i<=m2;++i)
	{
		int u,v;
		scanf("%d %d",&u,&v);
		ufs2.unionSet(u,v);
	}
	vector<pair<int,int>> Ans;
	vector<int> st1,st2;
	for(int i=2;i<=n;++i)	if(Link(1,i))	Merge(1,i),Ans.emplace_back(mp(1,i));
	for(int i=2;i<=n;++i)	if(ufs1.findSet(1)!=ufs1.findSet(i))	ufs1.unionSet(1,i),st1.emplace_back(i);
	for(int i=2;i<=n;++i)	if(ufs2.findSet(1)!=ufs2.findSet(i))	ufs2.unionSet(1,i),st2.emplace_back(i);
	printf("%d\n",int(Ans.size())+int(min(st1.size(),st2.size())));
	for(auto st:Ans)	printf("%d %d\n",st.first,st.second);
	for(unsigned int i=0;i<min(st1.size(),st2.size());++i)	printf("%d %d\n",st1[i],st2[i]);
	return 0;
}
```

---

