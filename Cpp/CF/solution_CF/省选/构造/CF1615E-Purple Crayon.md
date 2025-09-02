# Purple Crayon

## 题目描述

Two players, Red and Blue, are at it again, and this time they're playing with crayons! The mischievous duo is now vandalizing a rooted tree, by coloring the nodes while playing their favorite game.

The game works as follows: there is a tree of size $ n $ , rooted at node $ 1 $ , where each node is initially white. Red and Blue get one turn each. Red goes first.

In Red's turn, he can do the following operation any number of times:

- Pick any subtree of the rooted tree, and color every node in the subtree red.

 However, to make the game fair, Red is only allowed to color $ k $ nodes of the tree. In other words, after Red's turn, at most $ k $ of the nodes can be colored red.Then, it's Blue's turn. Blue can do the following operation any number of times:

- Pick any subtree of the rooted tree, and color every node in the subtree blue. However, he's not allowed to choose a subtree that contains a node already colored red, as that would make the node purple and no one likes purple crayon.

 Note: there's no restriction on the number of nodes Blue can color, as long as he doesn't color a node that Red has already colored.After the two turns, the score of the game is determined as follows: let $ w $ be the number of white nodes, $ r $ be the number of red nodes, and $ b $ be the number of blue nodes. The score of the game is $ w \cdot (r - b) $ .

Red wants to maximize this score, and Blue wants to minimize it. If both players play optimally, what will the final score of the game be?

## 说明/提示

In the first test case, the optimal strategy is as follows:

- Red chooses to color the subtrees of nodes $ 2 $ and $ 3 $ .
- Blue chooses to color the subtree of node $ 4 $ .

 At the end of this process, nodes $ 2 $ and $ 3 $ are red, node $ 4 $ is blue, and node $ 1 $ is white. The score of the game is $ 1 \cdot (2 - 1) = 1 $ .In the second test case, the optimal strategy is as follows:

- Red chooses to color the subtree of node $ 4 $ . This colors both nodes $ 4 $ and $ 5 $ .
- Blue does not have any options, so nothing is colored blue.

 At the end of this process, nodes $ 4 $ and $ 5 $ are red, and nodes $ 1 $ , $ 2 $ and $ 3 $ are white. The score of the game is $ 3 \cdot (2 - 0) = 6 $ .For the third test case:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1615E/4f1ce64388408bbdd02cef561a7e83cee70927f0.png)The score of the game is $ 4 \cdot (2 - 1) = 4 $ .

## 样例 #1

### 输入

```
4 2
1 2
1 3
1 4```

### 输出

```
1```

## 样例 #2

### 输入

```
5 2
1 2
2 3
3 4
4 5```

### 输出

```
6```

## 样例 #3

### 输入

```
7 2
1 2
1 3
4 2
3 5
6 3
6 7```

### 输出

```
4```

## 样例 #4

### 输入

```
4 1
1 2
1 3
1 4```

### 输出

```
-1```

# 题解

## 作者：5ab_juruo (赞：7)

赛时在 C 挣扎太久了导致这道题没写……

purple crayon 不是出题人吗（

题读错还在瞎编的人是屑/kk

---

红蓝双方在以 $1$ 为根的树上涂色，红先手。每次一方可以涂一个子树为自己颜色，并可以涂任意次。但红方最多只能涂 $k$ 个节点，且每次任意一方要涂的子树内不能有对方颜色。设最后有 $w$ 个白色节点，$r$ 个红色节点，$b$ 个蓝色节点，则分数为 $w(r-b)$。

红方想最大化分数，蓝方想最小化分数，假设两方都绝顶聪明，求最后的分数。

---

结论 1：红方涂一个节点 $x$，相当于阻止蓝方在 $x$ 到节点 $1$ 的路径上涂色。

只有这条路径上的节点的子树包含了 $x$。

结论 2（关键结论）：红方涂节点越多，能控制的节点越多，蓝方能涂的节点越少，分数不会变小。

注意到 $w+r+b=n$，令 $f(x)=x(n-x)$，则分数可以化简为 $w(r-b)=(n-r-b)(r-b)=r(n-r)-b(n-b)=f(r)-f(b)$。注意到对于 $f(x)$，在 $x=\left\lfloor n\over 2\right\rfloor$ 时取到最大。

设 $R$ 为红色能控制的节点数，则 $b\le n - R$，则 $R$ 越大 $\max f(b)$ 越小。

- 若 $r\le \left\lceil{n\over 2}\right\rceil$，则 $f(r)$ 随 $r$ 增大而增大，$f(b)$ 不减，所以分数递增；

- 若 $r>\left\lceil{n\over 2}\right\rceil$，易得此时 $f(b)$ 在 $b=n-R$ 时取到最大，则分数就是 $g(r)=f(r)-f(n-R)=f(r)-f(R)$，又因为 $R(r)-R(r-1)\ge 1$ 且 $f^{''}(x)<0$，则

$$
\begin{aligned}
g(r+1)&=f(r+1)-f(R(r+1))\\
&\ge f(r+1)-f(R(r)+1)\\
&=f(r)-f(R(r))+(-2r+n+1-(-2R(r)+n+1))\\
&\ge f(r)-f(R(r))=g(r)
\end{aligned}
$$

综上，分数随 $r$ 递增。

结论 3：红方会优先涂叶子节点。

根据结论 2，如果我们将涂色的节点换成其中一个儿子，那么能控制的节点数不会减少，类推可得。

---

所以，红方只需要每次取叶子节点，使增加的控制的节点数尽可能多即可。注意到这一过程类似长链剖分，所以我们只需要跑长链，然后根据链长倒序取即可。

有一个细节：如果叶子节点数 $\le k$，即红色能覆盖所有节点时，可以不必覆盖所有节点，而让 $r$ 尽可能接近 $n\over 2$ 是最优的。

代码：

```cpp
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long ll;
const int max_n = 200000;

int hd[max_n], des[max_n<<1], nxt[max_n<<1], dep[max_n], dd[max_n], ln[max_n], e_cnt = 0, lac = 0;

void add(int s, int t)
{
	des[e_cnt] = t;
	nxt[e_cnt] = hd[s];
	hd[s] = e_cnt++;
}

inline void chmax(int& a, int b) { if (a < b) a = b; }
void dfs(int id, int fa)
{
	for (int p = hd[id]; p != -1; p = nxt[p])
		if (des[p] != fa)
		{
			dd[des[p]] = dd[id] + 1;
			dfs(des[p], id);
			chmax(dep[id], dep[des[p]]);
		}
	dep[id]++;
}

void dfs2(int id, int top)
{
	if (nxt[hd[id]] == -1 && id)
	{
		ln[lac++] = dd[id] - dd[top] + 1;
		return;
	}
	
	int mx = -1, mxp;
	for (int p = hd[id]; p != -1; p = nxt[p])
		if (dep[des[p]] < dep[id] && dep[des[p]] > mx)
			mx = dep[des[p]], mxp = des[p];
	
	dfs2(mxp, top);
	for (int p = hd[id]; p != -1; p = nxt[p])
		if (dep[des[p]] < dep[id] && des[p] != mxp)
			dfs2(des[p], des[p]);
}

signed main()
{
	memset(hd, -1, sizeof hd);
	
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	
	int n, k;
	
	cin >> n >> k;
	for (int i = 1, x, y; i < n; i++)
	{
		cin >> x >> y;
		add(x-1, y-1), add(y-1, x-1);
	}
	dfs(0, -1), dfs2(0, 0);
	
	if (k >= lac)
	{
		if (k > n / 2 && lac <= n / 2) k = n / 2;
		else if (lac > n / 2) k = lac;
		cout << 1ll * k * (n - k) << endl;
	}
	else
	{
		sort(ln, ln + lac, [](int a, int b) { return a > b; });
		
		int pn = n;
		for (int i = 0; i < k; i++)
			pn -= ln[i];
		
		if (pn > n / 2) pn = n / 2;
		cout << 1ll * k * (n - k) - 1ll * pn * (n - pn) << endl;
	}
	
	return 0;
}
```

---

## 作者：Cry_For_theMoon (赞：3)

挺不错的一道题。我尽可能自然地把思考过程展示出来。

#### 分析

首先，游戏只会进行一轮，先确定 $r$，然后确定 $b$。答案式子为 $w(r-b)$，三个量有点多，我们把 $w$ 换成 $n-r-b$ 然后代入展开，发现原式等价于 $r(n-r)-b(n-b)$。

也就是说，第一步确定了 $r$ 后，第二个人的选择是有规律可循的：最大化 $b(n-b)$ 的值。这个函数的最大值是众所周知的，只要让 $b$ 和 $n-b$ 尽可能接近，即 $b$ 尽可能接近 $\frac{n}{2}$ 即可。

注意到确定了 $r$ 后，每个红色节点到根的路径上所有点，都必须是白色。我们设有 $x$ 个点是可以涂蓝的，容易发现涂 $\le x$ 个蓝点的方案都是存在的（每次选能染蓝色的叶子染色，然后删除这个点，重复这个过程）。根据上面的关于后手的选择方案的结论，对先手来说，在确定 $r$ 情况下，$x$ 越小越好。

换言之，在 $r$ 确定的情况下，红色点到根的路径上所有点的并集大小要尽可能大。此时我们容易考虑一些贪心。一个直观的贪心是：每次选到根路径未染色节点最多的点，然后把它到根路径的所有点染色。重复这个过程。

考虑证明这个贪心，只用证明等价于第一步选到根路径未染色节点最多的点 $u$，因为策略是递归进行的。考虑反证，假设存在一个不含 $u$ 的选法，从中选一个和 $u$ 的 lca 深度最深的点 $v$，把 $u$ 换成 $v$ 答案一定不差。

那么现在我们维护这个贪心过程。当 $k\ge$ 叶子数的时候是 trivial 的。仅考虑 $k\lt$ 叶子数的情况，此时先手只会染叶子。把所有叶子按 dfs 序排序，初始的值为深度，每次找值最大的点，然后一路向上对于所有未访问过的点，把子树内所有叶子的值减一。所以需要用一个支持区间减区间求最大值的线段树。

复杂度：$O(n\log n)$。

```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
#define op(x) ((x&1)?x+1:x-1)
#define odd(x) (x&1)
#define even(x) (!odd(x))
#define lc(x) (x<<1)
#define rc(x) (lc(x)|1)
#define lowbit(x) (x&-x)
#define Max(a,b) (a>b?a:b)
#define Min(a,b) (a<b?a:b)
#define next Cry_For_theMoon
#define il inline
#define pb(x) push_back(x)
#define is(x) insert(x)
#define sit set<int>::iterator
#define mapit map<int,int>::iterator
#define pi pair<int,int>
#define ppi pair<int,pi>
#define pp pair<pi,pi>
#define fr first
#define se second
#define vit vector<int>::iterator
#define mp(x,y) make_pair(x,y)
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef double db;
using namespace std;
const int MAXN=2e5+10,INF=1e9;
int n,u,v,k,sz[MAXN],dfn[MAXN],fa[MAXN],top[MAXN],depth[MAXN];
int m,leaf[MAXN],leafd[MAXN];
vector<int>e[MAXN];
void dfs(int u){
	sz[u]=1;dfn[u]=++dfn[0];
	depth[u]=depth[fa[u]]+1;
	top[u]=u;
	for(auto v:e[u]){
		if(v==fa[u])continue;
		fa[v]=u;
		dfs(v);
		sz[u]+=sz[v];
	}
}
int Find(int x){
	if(top[x]==x)return x;
	return top[x]=Find(top[x]); 
}
void up(pi& a,pi b){
	if(a.fr<b.fr)a=b;
}
bool cmp(int a,int b){
	return dfn[a]<dfn[b];
}
struct seg{
	int tag[MAXN<<2],maxn[MAXN<<2],pos[MAXN<<2];
	void pushup(int x){
		if(maxn[lc(x)]>maxn[rc(x)])maxn[x]=maxn[lc(x)],pos[x]=pos[lc(x)];
		else maxn[x]=maxn[rc(x)],pos[x]=pos[rc(x)];
	}
	void pushdown(int x){
		if(!tag[x])return;
		maxn[lc(x)]+=tag[x];maxn[rc(x)]+=tag[x];
		tag[lc(x)]+=tag[x];tag[rc(x)]+=tag[x];
		tag[x]=0;
	}
	void build(int x,int l,int r){
		if(l==r){
			pos[x]=l;maxn[x]=depth[leaf[l]];
			return;
		}
		int mid=(l+r)>>1;
		build(lc(x),l,mid);build(rc(x),mid+1,r);
		pushup(x);
	}
	void upd(int x,int l,int r,int ql,int qr,int val){
		if(ql<=l && qr>=r){
			maxn[x]+=val;tag[x]+=val;return;
		}
		pushdown(x);int mid=(l+r)>>1;
		if(ql<=mid)upd(lc(x),l,mid,ql,qr,val);
		if(qr>mid)upd(rc(x),mid+1,r,ql,qr,val);
		pushup(x);
	}
}t;
int ban;
void Remove(int u){
	int L=dfn[u],R=dfn[u]+sz[u]-1;
	//[L,R]
	int l=lower_bound(leafd+1,leafd+1+m,L)-leafd;
	int r=upper_bound(leafd+1,leafd+1+m,R)-leafd-1;
	if(l<=r)t.upd(1,1,m,l,r,-1);
}
int main(){
	scanf("%d%d",&n,&k);
	rep(i,1,n-1){
		scanf("%d%d",&u,&v);
		e[u].pb(v);e[v].pb(u); 
	}
	dfs(1);
	rep(i,1,n)if(sz[i]==1){
		leaf[++m]=i;
	}
	sort(leaf+1,leaf+1+m,cmp);
	rep(i,1,m)leafd[i]=dfn[leaf[i]];
	if(k>=m){
		if(k<n/2){
			printf("%lld",1LL*(n-k)*k);
		}else{
			if(m<=n/2)printf("%lld",1LL*(n-n/2)*(n/2));
			else printf("%lld",1LL*(n-m)*m);
		}
		return 0; 
	}
	t.build(1,1,m);
	ll ans=-1e18;
	rep(i,1,k){
		pi tmp=mp(t.maxn[1],t.pos[1]);
		ban+=(tmp.fr-1);
		int u=leaf[tmp.se];
		while(u){
			Remove(u);
			top[Find(u)]=Find(fa[u]);
			u=Find(u);
		}
		int b=min(n/2,n-i-ban);
		ans=max(ans,1LL*(n-i-b)*(i-b));
	}
	printf("%lld",ans);
	return 0;
}

```


---

## 作者：Alex_Wei (赞：3)

[CF1615E Purple Crayon](https://www.luogu.com.cn/problem/CF1615E)

考虑在某个节点涂上红色，则它的所有祖先都不能涂黄色。

考虑给 $r$ 个节点涂上红色，有 $c$ 个节点可以涂蓝色，则分值为 $\min\limits_{b = 0} ^ c \{(n - r - b) (r - b)\}$。显然 R 希望 $c$ 越小越好，这样 B 的决策严格变少，对 R 来说一定不劣。

考虑选 $r$ 个节点，它们到根的链覆盖最多节点，这是经典长链剖分贪心。选最长的 $r$ 个长链即可。

从 $0$ 到 $k$ 枚举 $r$，对每个 $r$ 求出对应的 $c$，然后求二次函数 $(n - r - b)(r - b)$ 在 $b\in [0, c]$ 的最小值，再将所有最小值求最大值即可。

实际上，当 $r$ 小于重链条数 $d$ 且 $r < k$ 时，增加 $r$ 一定不劣。考虑 $r = z + 1$ 相较于 $r = z$ 增加了一条重链，则 $r = z$ 时 B 总可以将该重链涂蓝，这样 $r = z$ 时 $n - r - b$ 相较于 $r = z + 1$ 不变，但 $b$ 变大，则 $(n - r - b)(r - b)$ 变小，对 R 不优。

因此，当 $k\leq d$ 时，直接令 $r = k$ 算出 $c$，然后枚举 $b$ 求 $\min\{(n - k - b)(k - b)\}$。当 $k > d$ 时，从 $d$ 开始枚举 $r$，此时 $c = 0$，所以求 $\max \{(n - r) r\}$。

时间复杂度容易 $\mathcal{O}(n)$。[代码](https://codeforces.com/contest/1615/submission/182197422)。

---

## 作者：Purslane (赞：2)

# Solution

套路题。本题限制条件较多，令人眼花缭乱难以下手，下面展示一下如何拆解问题，对后面的 $\rm NOIp$ 也有帮助。

~~`*2400` 的题目花了四十分钟才搞定，可以重开了~~

- 如果你是 Bob，如何让得分最小？

注意 $w$ 变量完全是没用的，因此目标是 $\text{minimize} (n-r-b)(r-b)$，也就是 $b^2-nb+r(n-r)$。这是一个二次函数，因此 Bob 的目的就是让 $b$ 尽量接近 $\frac{n}{2}$。

还有一个很重要的观察：$b$ 可能得取值范围是 $0$ 到 $s$ 的一个前缀，$s$ 是所有**子树中不包含红点**的节点个数。显然可以通过构造将这所有数都取到。（如果分析不出这条性质，你会对整个最优化问题都感到头疼，因为你甚至无法直观的得到自变量的取值范围）

- 如果你是 Alice，如何让得分最大？

我们显然要枚举 $r$。注意 $b$ 的取值范围越小，显然对 Bob 来说更劣，因此我们要让 **$s$ 尽可能小**。

问题转化为：在树上选 $r$ 个点，覆盖所有点到 $1$ 的路径，使得**被覆盖的点个数最多**。

- 上述经典问题的解法

假装你不知道这个结论，你应该怎么处理？

首先是进行调整法，得出**最优解应当满足的结构**，从而获得额外限制。显然，我们选取的点都应当是叶子，否则往下移更优。

考虑分析一下比较小的情况。只选一个叶子，显然选树上的最长链。

如果选了两个叶子，**必然有一个是最长链**（还是可以通过调整得到）和删去这条链以后得最长链。

对于更多的叶子，显然同理。这个过程就可以刻画为：给你一棵树，每次删掉最长链，记录所有长度。这就是我们熟知的长链剖分。

这个贪心的正确性也是很好保证的：将叶子构成的虚树进行长链剖分，显然所有链的长度都小于等于原树对应排名链的长度，取出对应的链显然更优。使用优先队列维护即可。

综合以上分析，我们就完成了本题。

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10;
int n,k,mx[MAXN];
vector<int> G[MAXN];
priority_queue<int> len;
void dfs(int u,int f) {
	vector<int> vc;
	vc.push_back(0);
	for(auto v:G[u]) if(v!=f) dfs(v,u),vc.push_back(mx[v]);
	sort(vc.begin(),vc.end(),[](int A,int B) {
		return A>B;	
	});
	mx[u]=vc[0]+1;
	ffor(i,1,vc.size()-1) len.push(vc[i]);
	return ;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	ffor(i,1,n-1) {
		int u,v;
		cin>>u>>v,G[u].push_back(v),G[v].push_back(u);	
	}
	dfs(1,0);
	len.push(mx[1]);
	int ans=-n/2*(n-n/2),b=n;
	ffor(r,1,k) {
		if(!len.empty()) b-=len.top(),len.pop();
		if(b<=n/2) ans=max(ans,b*b-n*b+r*(n-r));
		else ans=max(ans,(n/2)*(n/2)-n*(n/2)+r*(n-r));
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：Loser_Syx (赞：1)

首先，我们需要明确一个东西，原题目求的是 $\max\ (n-r-b)(r-b)$，而 $b$ 越小答案就越小，所以变相的是在要求 $b$ 最小。

然后我们来随便选一个点 $u$，观察它所带来的影响。

不难发现它使蓝色方不能选择 $u \rightarrow 1$ 的路径上的点，又发现如果选择 $u$ 的子孙的话，蓝方选择的点数量更小，所以要选一定先选叶子结点。

再来考虑如果叶子结点选不完怎么办，那一定是要选影响最大的几个节点，使得 $b$ 是足够小的，发现这个过程就是选长链，长链剖分即可。

所以剖分完选最长的 $k$ 个长链即可。

有个细节是，无论答案如何，都要以 $\frac{n}{2}$ 为一个基准值，这是最优情况了。

[code](https://codeforces.com/contest/1615/submission/292468615)。

---

## 作者：Silvestorm (赞：1)

### 题目大意

[题目链接](https://www.luogu.com.cn/problem/CF1615E)。

给你一个 $n$ 个节点的树。A，B 两人在树上操作。一开始节点全为白色。

A 先操作，在树上取任意多个子树，将子树内部节点全部染红，要求所有子树节点数总和不超过 $k$。

B 后操作，在树上选任意多个子树，条件是所有子树内部无红色节点。将子树内部染蓝。

最后假设有 $r$ 个红色节点，$b$ 个蓝色节点和 $w$ 个白色节点，则分数为 $w\times (r-b)$。A 想让分数大，B 想让分数小，若两人都很聪明，问最后分数是多少。

$2\le n\le 2\times 10^5$，$1\le k\le n$。

### 题目类型

树，dfs，三分，贪心。

### 解题思路

首先，B 希望自己能染蓝的节点最多，后手的他能通过染蓝若干数量的节点使得答案最小。

A 的首要任务是限制 B，使其能染蓝的节点数尽可能少。那么，基于贪心思路，在所有 B 可以选择的子树中，A 总是选择节点数量最多的一棵。

一个不难想的小结论：A 优先给叶子节点染色，因为这样会影响最多的子树。

那么我们统计每一个子树的节点数，将其提取出来并降序排序，同时，对于一个节点的所有儿子，我们根据儿子作为子树的节点数进行降序排序，这样我们往下遍历时，首先遍历到节点数量最多的子树，使得影响最大化。

将所有子树提取出来并排序后，直接遍历染色即可，经过上述操作后，我们的每次染色都是最有效的，同时，我们给以及染色的子树打上标记，后续访问时直接返回即可，这样每个节点只会遍历 $1$ 次，所以染色是 $O(n)$ 的。

A 对于非叶子节点的染色是非必须的，所以上述染色后我们可以得到 A 染色节点的上下界。

B 的染色，dfs 遍历那些子树不被染色即可，这样可以得到B的染色节点数的上界，而下界是 $0$。

最后，枚举 A 的染色节点数，三分得到答案，取最优即可。

时间复杂度为 $O(n\log{n})$。

### code


```cpp
#include <bits/stdc++.h>
#define ll long long
#define N 200100
using namespace std;

ll n, m, k, x, tem, sum, a, b, num[N];
ll ans, vis[N];
struct lint
{
	ll en, w;
};
vector<ll> v[200100];
vector<lint> v1;
bool cmp(ll q, ll e)
{
	return num[q] > num[e]; // 根据节点数量进行排序
}
bool cmp1(lint q, lint e)
{
	return q.w > e.w;
}
void dfs(ll x, ll fa)
{
	for (int i = 0; i < v[x].size(); i++)
	{
		if (v[x][i] == fa)
		{
			v[x].erase(v[x].begin() + i); // 删除连接父亲的边，建立单向数，这样后续好访问
			i--;
			continue;
		}
		dfs(v[x][i], x);
		num[x] += num[v[x][i]] + 1;
	}
	v1.push_back({x, num[x]});			 // 提取节点及其节点数
	sort(v[x].begin(), v[x].end(), cmp); // 按照节点数排序
}
ll change(ll x) // 染色
{
	if (vis[x])
		return 1;
	if (v[x].size() == 0)
	{
		vis[x] = 1;
		m--;   // 染色后，剩余可染色数量减1
		tem++; // A的下界增加
		return vis[x];
	}
	vis[x] = vis[x] | change(v[x][0]);
	return vis[x];
}
ll check(ll x) // 统计B的可染色数量
{
	for (int i = 0; i < v[x].size(); i++)
		vis[x] = vis[x] | check(v[x][i]);
	if (vis[x] == 0)
		sum++;
	return vis[x];
}
void solve()
{
	cin >> n >> m;
	k = m;
	for (int i = 1; i < n; i++)
	{
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	dfs(1, 0);
	sort(v1.begin(), v1.end(), cmp1);
	for (int i = 0; i < v1.size() && m > 0; i++)
		change(v1[i].en);
	check(1);
	// cout << tem << " " << sum << '\n';
	ans = -1e17;
	for (; tem <= k; tem++) // 从下界枚举到上界
	{
		ll l = 0, r = sum;
		while (l < r) // 三分
		{
			ll mid = (l + r) >> 1;
			ll mid1 = mid + 1;
			if ((n - tem - mid) * (tem - mid) >= (n - tem - mid1) * (tem - mid1))
				l = mid + 1;
			else
				r = mid;
		}
		ans = max(ans, (n - tem - l) * (tem - l));
	}
	cout << ans << '\n';
}
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	int t = 1;
	// cin >> t;
	while (t--)
	{
		solve();
	}
	return 0;
}
```

---

## 作者：清烛 (赞：1)

## Description
红蓝双方在一棵 $1$ 为根的树上涂色。红先涂，每次可以选择一个子树内的点涂成红色，但涂的个数不能超过 $k$。然后蓝涂，每次可以选择一个子树内的点涂成蓝色，但该子树内不能有红色节点。设最后白、红、蓝三种颜色的点各有 $w$、$a$ 和 $b$ 个，则分数定义为 $w(r - b)$。红方想最大化分数，蓝方想最小化分数。双方都绝顶聪明，问最后的分数。

## Solution
需要仔细观察题目性质的好题。

拆开式子：$w(r-  b) = (n - r - b)(r - b) = r(n - r) - b(n - b)$。所以对于红方，他想要做的就是最大化 $r(n - r)$ 和最小化 $b(n - b)$。到了蓝方这里，他一定是想最大化 $b(n - b)$，其在 $b = \lfloor n / 2\rfloor$ 处有最大值。

另外我们可以发现，红方选择了 $u$ 子树意味着 $1$ 到 $u$ 上的点都不能被蓝方涂色，相当于控制了一条链。为了使得蓝方能达到的最大的 $b(n - b)$ 最小，红方的最优策略一定是尽可能最小化 $b$ 的最大值。所以说，**红方尽可能多控制点，一定是最优的**。

而且，为了尽可能多控制点，**红方选的一定是叶子节点**，若选的不是叶子，则选一个儿子节点能控制的节点肯定更多。

所以，我们从大到小取 $k$ 根长链，取的时候算一下蓝方还能涂多少个 $b$，若 $b > \lfloor n / 2\rfloor$ 则取 $b = \lfloor n / 2\rfloor$。依此计算答案。

## Implementation

```cpp
const int maxn = 2e5 + 5;
vector<int> G[maxn];
int n, k, son[maxn], h[maxn], fa[maxn], len[maxn], cnt;

void dfs1(int u, int pre) {
    fa[u] = pre;
    for (auto v : G[u]) {
        if (v == pre) continue;
        dfs1(v, u);
        if (h[v] > h[son[u]])
            son[u] = v;
    }
    h[u] = h[son[u]] + 1;
    return;
}

void dfs2(int u, int topf) {
    if (!son[u]) {
        len[++cnt] = h[topf];
        return;
    }
    dfs2(son[u], topf);
    for (auto v : G[u]) {
        if (v == son[u] || v == fa[u]) continue;
        dfs2(v, v);
    }
    return;
}

int main() {
    read(n, k);
    FOR(i, 1, n - 1) {
        int u, v; read(u, v);
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs1(1, 0), dfs2(1, 1);
    sort(len + 1, len + cnt + 1, greater<int>());
    long long ans = -1e18;
    int b = n;
    FOR(a, 1, k) {
        int x = min(n / 2, b -= len[a]);
        chkmax(ans, 1ll * (n - a - x) * (a - x));
    }
    print(ans);
    return output(), 0;
}
```



---

## 作者：WRuperD (赞：1)

简单题。

首先考虑不考虑 $k$ 这一限制怎么做。

发现但你选完了所有的叶子节点后，后手就没用了，相当于没得选。那你有什么理由不选所有的叶子节点呢？

因为假设你不选一个叶子节点，那后手是必选的，这样 $b$ 增大， $w$ 减少，总和一定不优。

选完所有的叶子结点后，把节点数补到最优情况即可。

考虑一下 $k$ 的限制，这里只用考虑如果限制你选不完叶子节点。

回到问题本质，你考虑选一个叶子节点相当于什么，相当于后手不能选这个叶子结点到根的简单路径上的一点。明显我们是要后手可以选的点越少越好。这是一个经典的长链剖分贪心

---

## 作者：xiazha (赞：0)

神仙题。

- 首先设 $A$ 给 $r$ 个点涂上红色，则 $B$ **至多**给 $c$ 个点涂上蓝色。

- 性质 $1$：在 $r$ 为定值的情况下，$A$ 尽量使 $c$ 更小一定不劣，因为这样 $B$ 的决策集合元素严格减少，于是先设 $c$ 的最小值为 $cmin$。

- 性质 $2$：$A$ 增加 $r$ 一定不劣，因为若不增加则 $B$ 会尽量多的选点，$(n-r-b)$ 不变的情况下 $(r-b)$ 变小，对 $A$ 不优。

- 然后你就会想该怎么求 $cmin$，显然红色染叶节点能最大化答案，那么设树的叶节点个数为 $x$，可知当 $x\le k$ 时 $cmin$ 一定等于 $0$。考虑 $x > k$ 的情况，那么根据性质 $2$，$r=k$ 时最优。于是要求出选择 $r$ 个叶节点时每个叶节点到根路径上覆盖点的并的元素个数最大值。这个问题很好解决，求出树**长链剖分**后的所有链然后选出前 $r$ 条，设**降序排序后**第 $i$ 条链的长度为 $len_i$，则 $cmin=n-\sum_{i=1}^{r}len_i$。

- 来到最后一步，求答案，还是分情况：

当 $x\le k$ 时，答案为 $\max_{i=x}^{n} i(n-i)$。

否则，答案为 $\min_{i=0}^{cmin} (n-r-i)(r-i)$。

注意您若不会长链剖分，见[这个博客](https://www.cnblogs.com/maoyiting/p/14178833.html#/cnblog/works/article/14178833)。

---

## 作者：Engulf (赞：0)

我发现我一开始读错这个题了，是 Red 染完色后，Blue 染色，然后就结束了，我以为是个博弈的过程。

因为 $w = n - r - b$，所以最终分值就是 $(n - r - b)(r - b) = r(n - r) - b(n - b)$。Blue 想让得分小，即让 $-b(n-b) = (b - \dfrac{n}{2})^2 - \dfrac{n^2}{4}$ 尽可能小，当 $b = \dfrac{n}{2}$ 取得。

证明一个单调性：若 Blue 能将 $x$ 个点染为蓝，那么他能将 $x - 1$ 个点染为蓝。

Blue 一定是操作了一些子树，这些子树内都是没有红色点的，那只要分别操作其中一个子树 $G$ 的所有子树，这是合法的，现在就只剩 $G$ 的根没有染色，所以答案减少 $1$。这样，若 Blue 能将 $x$ 个点染为蓝，那么他能将任意的 $y \le x$ 个点染为蓝。

所以，若 $b \ge \dfrac{n}{2}$，他就一定能让答案最小。而 Red 为了阻止这种事情的发生，他要让 Blue 能选的点尽量少。

将 $u$ 染成红色，那么 $u$ 到根这条路径上的所有点不能作为 Blue 操作的点，取叶子一定是比不取叶子优的，不然 Blue 还能在 $u$ 子树内取，而且 $u$ 作为叶子，使 Blue 不能操作的点还更多。

为了 Blue 操作的点尽量少，我们希望选出一些节点，它们到根的路径的并集大小尽量大。这是经典问题，使用长链剖分解决，每一条长链，都将长链底端那个叶子染红即可覆盖住整条链，记有 $d$ 条长链（也就是有 $d$ 个叶子）。

- 若 $k < d$，取不了所有的长链，那就取前 $k$ 大的即可，即 $r = k$。那么剩下的 $d - k$ 个链都可以染成蓝色，记这些链的长度和为 $b$，根据上面的单调性，若 $b \ge \dfrac{n}{2}$ 那它能取到最值，否则在对称轴左侧是单调递增的，在 $b$ 处取到。整理一下 $r = \min(b, \dfrac{n}{2})$。
- 若 $k \ge d$，染不了蓝色了，那最终得分就是 $(n - r)r = -(r - \dfrac{n}{2}) + \dfrac{n^2}{4}$，同样在 $\dfrac{n}{2}$ 处取到。如果 $k < \dfrac{n}{2}$，对称轴左侧单调递增，就在 $r = k$ 处取得。注意 $\dfrac{n}{2} < d$ 有可能发生，这种情况下在对称轴右侧，单调递减，取 $d$ 即可。整理一下得 $r = \max(d, \min(k, \dfrac{n}{2}))$。

由于 $r$ 得是一个整数，$n$ 是奇数的时候取不到最值，最值就在 $\left\lfloor \dfrac{n}{2} \right\rfloor$ 和 $\left\lceil \dfrac{n}{2} \right\rceil$ 取得。这两个是一样的。代码实现直接用了下取整那个，方便。

```cpp
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int, int>;

#ifdef ONLINE_JUDGE
#define debug(...) 0
#else
#define debug(...) fprintf(stderr, __VA_ARGS__), fflush(stderr)
#endif

const int N = 2e5 + 5;

int n, k;

vector<int> g[N];

int dep[N], mxdep[N], son[N];

vector<int> chain;

void dfs1(int u, int fa) {
    mxdep[u] = dep[u] = dep[fa] + 1;
    for (auto v: g[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        mxdep[u] = max(mxdep[u], mxdep[v]);
        if (mxdep[v] > mxdep[son[u]])
            son[u] = v;
    }
}

void dfs2(int u, int fa, int len) {
    if (!son[u]) chain.emplace_back(len);
    else dfs2(son[u], u, len + 1);

    for (auto v: g[u])
        if (v != son[u] && v != fa)
            dfs2(v, u, 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> k;
    for (int i = 1, x, y; i < n; i++) {
        cin >> x >> y;
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }

    dfs1(1, 0);
    dfs2(1, 0, 1);

    if (k < chain.size()) {
        sort(chain.begin(), chain.end(), greater<>());
        int r = k, b = 0;
        for (int i = k; i < chain.size(); i++) b += chain[i];

        auto f = [=](int x) {return 1ll * (n - r - x) * (r - x);};
        cout << f(min(b, n / 2)) << "\n";
    } else {
        auto f = [](int x) {return 1ll * x * (n - x);};
        cout << f(max((int)chain.size(), min(k, n / 2))) << "\n";
    }

    return 0;
}
```

---

