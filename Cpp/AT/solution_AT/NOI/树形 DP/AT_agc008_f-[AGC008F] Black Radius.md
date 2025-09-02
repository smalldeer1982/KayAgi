# [AGC008F] Black Radius

## 题目描述

Snuke 君有一棵 $n$ 个节点的全白的树，其中有一些节点他喜欢，有一些节点他不喜欢。他会选择一个他喜欢的节点 $x$，然后选择一个距离 $d$，然后将所有与 $x$ 距离不超过 $d$ 的节点都染成黑色，**恰好操作一次**，问有多少种可能的染色后状态。

两个状态不同当且仅当存在一个节点，它在两个状态中不同色。

## 说明/提示

$2\le n\le2\times 10^5$，$1\le a_i,b_i\le n$，$|s|=n$。

部分分（$1300$ 分）：$s_i=1$（$1\le i\le n$）。

## 样例 #1

### 输入

```
4
1 2
1 3
1 4
1100```

### 输出

```
4```

## 样例 #2

### 输入

```
5
1 2
1 3
1 4
4 5
11111```

### 输出

```
11```

## 样例 #3

### 输入

```
6
1 2
1 3
1 4
2 5
2 6
100011```

### 输出

```
8```

# 题解

## 作者：Otomachi_Una_ (赞：24)

f. **[[AGC008F] Black Radius](https://atcoder.jp/contests/agc008/tasks/agc008_f)（8）**

神仙题！

先考虑 $s$ 全为 $1$ 的情况。

假设 $S(u,d)$ 表示和 $u$ 距离不超过 $d$ 的点组成的集合。我们先不考虑全集的情况，那么 $d<f_u$，其中 $f_u$ 表示 $u$ 到树上最远点的距离。不难发现对任何的 $u\not =v$ 都有 $S(u,d)\not= S(v,d)$。

但是对于直接算 $\sum(f_i-1)$ 会有重复，但是根据上面的结论，我们知道给定集合 $S,d$ 至多存在一个 $u$ 满足 $S(u,d)=S$。这让我们想到我们**对于一个 $\bm S$ 只对最小的 $\bm d$ 算贡献。**

也就是对任意和 $u$ 相邻的 $v$ 都有 $S(u,d)\not=S(v,d-1)$。换句话说也就是 **以 $\bm u$ 为根，有一个点不在 $\bm v$ 的子树当中且和 $\bm u$ 距离为 $\bm{d-1}$**。再转化一下，也就是 **以 $\bm u$ 为根的次小深度子树深度大于等于 $\bm{d-1}$**。假设 $g_u$ 为次小深度子树，也就是 $g_u\geq d-1$。

上面两个条件加一起，就会有 $d\leq \min(f_u-1,g_u+1)$。直接求和发现过了。

至此我们获得了 $1300$ 的部分点。

我们接下来要考虑 $s$ 有 $0$ 的情况。

和上面类似的，只是 $d$ 比较小的时候不可取。于是我们推测 $d$ 的取值还是一个区间。

-  如果 $s_u=1$，那么 $d$ 下限为 $0$。
-  反之，我们要找到一个点 $v$ 满足 $s_v=1$ 且存在 $d_0$ 满足 $S(v,d_0)=S(u,d)$。这要求 $d$ 大于等于 $v$ 所在子树的最大深度。于是 $d$ 的下限 $h_u$ 为所有含有 $1$ 子树最大深度的最小值。

完结撒花！

[submission](https://atcoder.jp/contests/agc008/submissions/43699110)

---

## 作者：litble (赞：22)

[戳我＝￣ω￣＝](https://blog.csdn.net/litble/article/details/83118814)

**先假设树上所有点都是关键点**。然后设$f(x,d)$表示距离$x$小于等于$d$的节点的集合。

我们想一个精妙的不重不漏计数方法，假设有若干$f(x,d)$同构，我们希望只在$d$最小的那个位置计算贡献，则我们计算满足以下条件的数对个数：

1. $f(x,d)$不覆盖整棵树（计数完成后让答案+1即可统计整棵树被染色的情况）
2. 对于与$x$相邻的点$y$，都不存在$f(x,d)=f(y,d-1)$对于与$x$相邻的点$y$，都不存在$f(x,d)=f(y,d-1)$

所以我们发现，每个点上可以取的$d$存在一个上界。

设离$x$最远的点离$x$的距离为$mx(x)$，显然条件1等价于$d<mx(x)$。

而条件2，考虑若存在一个这样的$y$，把$x$看做树根。由于$y$能够染周围$d-1$的点，所以在$y$子树里的点，若存在于$f(x,d)$中必然存在在$f(y,d-1)$中，反之不存在于。而若在$y$子树以外的地方有一个点$z$和$x$的距离大于$d-2$，则$f(y,d-1)$中没有它，而$f(x,d)$中有它。

因此若设$se(x)$表示删掉$y$子树后剩余节点中找一个点，使得$x$离它的距离最远，则条件2满足等价于$d-2<se(x)$。显然在$y$子树里存在到$x$距离最远的点时，$se(x)$最小，最能产生约束。

现在看有的点不是关键点的情况。

那么对于不是关键点的点$x$，若要$f(x,d)$是与它相同的集合表示中，$d$最小的那个，且也是一个关键点$y$的某种染色集合，则这个集合必须包含以$x$为根，**它的儿子们的子树**中，包含$y$的那个子树中的所有节点。（有点拗口啊，建议多读几遍QAQ）

证明：

如果不包含的话，如下图，$k$以下的部分没包含，则$f(x,d_2+d_3)=f(y,d_1+d_3)$，从$y$走到$x$的距离是$d_1+d_2$，走到$x$再走到$x$的其他儿子，还能走的距离是$d_3-d_2$。而对于状态$f(z,d_3)$，从$z$走到$x$后再能走的距离也是$d_3-d_2$，而且也能走到$k$，所以$f(z,d_3)=f(x,d_2+d_3)$，$f(x,d_2+d_3)$不是与它相同的集合表示中$d$最小的那个。
![灵魂画手litble](https://img-blog.csdn.net/20181018074100574?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2xpdGJsZQ==/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

于是我们就做换根DP即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define RI register int
int read() {
	int q=0;char ch=' ';
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9') q=q*10+ch-'0',ch=getchar();
	return q;
}
typedef long long LL;
const int N=200005,inf=0x3f3f3f3f;
int h[N],ne[N<<1],to[N<<1],mx[N],se[N],d[N],sz[N];
int n,tot;LL ans;char S[N];

void add(int x,int y) {to[++tot]=y,ne[tot]=h[x],h[x]=tot;}
void dfs1(int x,int las) {
	if(S[x]=='1') d[x]=0,sz[x]=1;
	else d[x]=inf;
	for(RI i=h[x];i;i=ne[i]) {
		if(to[i]==las) continue;
		int y=to[i];dfs1(y,x),sz[x]+=sz[y];
		if(mx[y]+1>mx[x]) se[x]=mx[x],mx[x]=mx[y]+1;
		else if(mx[y]+1>se[x]) se[x]=mx[y]+1;
		if(sz[y]) d[x]=min(d[x],mx[y]+1);
	}
}
void dfs2(int x,int las) {
	int R=min(se[x]+1,mx[x]-1);
	if(d[x]<=R) ans+=(LL)(R-d[x]+1);
	for(RI i=h[x];i;i=ne[i]) {
		if(to[i]==las) continue;
		int y=to[i],kl=(mx[y]+1==mx[x]?se[x]+1:mx[x]+1);
		if(kl>mx[y]) se[y]=mx[y],mx[y]=kl;
		else if(kl>se[y]) se[y]=kl;
		if(sz[1]-sz[y]) d[y]=min(d[y],kl);
		dfs2(y,x);
	}
}
int main()
{
	int x,y;
	n=read();
	for(RI i=1;i<n;++i) x=read(),y=read(),add(x,y),add(y,x);
	scanf("%s",S+1);
	dfs1(1,0),dfs2(1,0);
	printf("%lld\n",ans+1);
	return 0;
}
```

---

## 作者：ღꦿ࿐ (赞：16)

[更好的阅读体验](https://www.cnblogs.com/Dreamerkk/p/18112488)

题意：给出一个 $n$ 个点的树（边权为 $1$）和集合 $S$，求有多少个点集 $T$ 可以被表示为离 $S$ 中的一个点 $u$ 距离不超过 $d$ 的点构成的集合（下文称为 $u$ 的 $d$ 级邻域）。

考虑 $S$ 为所有点的特殊情况：

我们直接求每个点邻域的个数再求和，会算重一些点集，这种情况发生仅当这个邻域在某些方向“满了”，从而可以认为是向没满的方向移动一些并把这个点当作邻域的中心。

如下图中的黑色点集既可以表示为 $v$ 的 $3$ 级邻域也可以表示为 $u$ 的 $2$ 级邻域。

![](https://cdn.luogu.com.cn/upload/image_hosting/21umcdpp.png?x-oss-process=image/resize,m_lfit,h_300,w_500)
于是我们考虑在点集的“中心”，即邻域的 $d$ 最小时统计，容易发现对于所有不是全集的某个邻域，都存在唯一的一个点 $u$ 使得邻域的  $d$ 最小（尽可能不溢出），于是我们单独统计全集，接下来考虑枚举一个点并统计它作为中心的邻域。

令 $f_u$ 表示 $u$ 在树上最远点的距离，$g_u$ 表示次远点的距离，容易换根求出 $f_u,g_u$。

首先 $d$ 不能取 $\geq f_u$ 的值，因为我们现在只统计不是全集的集合。

接下来考虑 $u$ 是中心的条件：不能存在某个相邻的 $v$ 使得 $v$ 的 $d-1$ 级领域和 $u$ 的 $d$ 级领域相同，可以发现这种情况仅当除了 $v$ 方向的其它方向的子树内都是满的，显然 $v$ 只能在 $f_u$ 所在子树的方向，且其它方向最远距离的点的距离都 $\leq d-2$。（在  $v$ 处 $d-1$ 也能统计到）于是我们得到 $d$ 不能取 $\geq g_u+2$ 的值。

则 $u$ 可以选择的 $d$ 在 $[0,\min(f_u-1,g_u+1)]$ 任意取，对所有值求和后加上全集即可。

---


接下来并不是所有点都可以选了，但我们仍然考虑在邻域邻域的中心 $u$ 处统计答案，即使这个中心并不能选择（我们统计的其它某个可以选的 $v$ 的 $d_1$ 级邻域但因为溢出而以 $u$ 为中心）。


若 $u$ 可以选择，则它作为中心的情况和上面相同。

若 $u$ 不能选择，则需要 $u$ 某个方向的一个可选择的 $v$，填满它的子树并从 $u$ 向外延伸向其它方向。

我们把 $u$ 当作中心的话，需要这个 $v$ 所在的子树被填满（这样才能使中心向 $u$ 偏移，否则中心显然不能是 $u$），并向外蔓延的距离至少要比这个子树的深度大，才可以把 $u$ 当作中心。

![](https://cdn.luogu.com.cn/upload/image_hosting/spxlad3v.png?x-oss-process=image/resize,m_lfit,h_300,w_500)

所以考虑 $d$ 能够取的最小值，即所有存在可以选择的点 的子树中，最深点深度的最小值，称为 $h_u$，通过换根求出即可，那么这个点可取的区间即 $[h_u,\min(f_u-1,g_u+1)]$，对所有点求和再加上全集即可。

----

其实最开始解决这个问题时，我采用的办法是树定一个根，然后对于每个点集在可行的最靠上的 $u$ 的邻域统计。

在解决 $S$ 为所有点的情况时还可以用类似的办法解决（在钦定邻域中心不能上移的位置统计），但是无法拓展到 $S$ 不是全集的情况。

这启示我们在统计无根树问题的时候，最好还是采用更加「无根」的统计方式，比如“中心”、“重心”、“最近”之类的，而不是“公共祖先”、“最上方”之类的有根树方向。

---

---

## 作者：LinkWish (赞：7)

题解里面好像用的都是 dp，提供一种不用 dp 的方法。

以这棵树直径的径心为根，进行 dfs。这里我们先只讨论直径上点数为奇数的情况，点数是偶数的情况是类似的。

设集合 $S(x,d)=\{ y \in [1,n] |dis(x,y) \le d \}$。

假设当前访问到节点 $x$ 且 $x$ 是一个关键点，已经访问过的节点中关键点组成的点集为 $P$，那么 $x$ 对答案的贡献为 $\sum\limits_{d=0}^n \prod\limits_{y \in P}[S(x,d) \ne S(y,\max\limits_{z \in S(x,d)}dis(y,z))]$。经过观察，发现对于所有的关键的 $x$，满足条件的 $d$ 构成一个从 $0$ 开始的区间。也就是说我们只需要对于每一个关键点 $x$ 求出满足条件的最大的 $d$ 就可以了。

考虑 dfs 的过程。设对于一个点 $x$，满足条件的最大的 $d$ 为 $d_x$，这里不要求 $x$ 是一个关键点，我们需要计算非关键点的 $d$，但是不对答案进行贡献。

假设当前访问到 $x$，并且已知 $d_x$ 的值。分三种情况讨论。设 $g_x$ 为 $x$ 子树内距离 $x$ 最远的点距 $x$ 的距离。

- $x$ 是一个关键点。这时对于 $x$ 的一个儿子 $y$ 一定有 $\forall d > g_y+1, S(x,d-1)=S(y,d)$。所以 $d_y=\min(d_x,g_y)+1$。

- $x$ 不是一个关键点，但是 $x$ 有至少一个儿子的子树内有关键点。设 $y$ 为子树内存在关键点且 $g_y$ 最小的 $x$ 的儿子。因为 $x$ 不是关键点，所以 $x$ 不会为 $y$ 增添限制，所以 $d_y=d_x+1$。因为对于任意的 $x$ 的其他儿子 $z$，有 $\forall d > g_z + 1, S(y,d)=S(z,d)$，所以 $d_z=\min(d_x,g_z)+1$。

- $x$ 不是一个关键点，$x$ 的子树内也没有关键点。这种情况对答案没有贡献，不用考虑。

容易发现，径心的 $d$ 一定是直径长度的一半，所以就可以以径心为根开始这个过程。

对于直径上点数是偶数的情况，把最中间那条边断开分开算就可以了，注意其中一侧在开始时的 $d$ 要比另一侧少 $1$，否则会算重。

答案即为 $\sum\limits_{i=1}^n [s_i=1] \cdot (d_i+1)$。

时间复杂度 $O(n)$。

```cpp
//Linkwish's code
#include<bits/stdc++.h>
#define endl '\n'
#define si inline
#define fi first
#define se second
using namespace std;
typedef long long ll;typedef __int128 li;typedef long double ld;
typedef pair<int,int> pii;typedef pair<ll,ll> pll;
typedef const int ci;typedef const ll cl;ci iinf=INT_MAX;cl linf=LLONG_MAX;
template<typename T>si bool gmax(T &x,const T y){if(x<y)return x=y,1;return 0;}
template<typename T>si bool gmin(T &x,const T y){if(y<x)return x=y,1;return 0;}

namespace LinkWish{

	ci N=200005;

	int n;
	string s;
	vector<int> e[N];

	void dfs(int x,int fa,int d,int &mx,int &res){
		if(gmax(mx,d))res=x;
		for(int to:e[x])if(to!=fa)dfs(to,x,d+1,mx,res);
	}

	int path[N],len;
	int mxd[N];bool exi[N];
	void init(int x,int fa){
		mxd[x]=0,exi[x]=s[x]=='1';
		for(int to:e[x])if(to!=fa)init(to,x),gmax(mxd[x],mxd[to]+1),exi[x]|=exi[to];
	}
	bool getp(int x,int fa,int goal){
		if(x==goal)return path[++len]=x,1;
		for(int to:e[x])if(to!=fa&&getp(to,x,goal))return path[++len]=x,1;
		return 0;
	}

	ll ans;
	void work(int x,int fa,int mx){
		if(s[x]=='1')ans+=mx+1;
		int p=0;
		if(s[x]=='1')p=x;
		else for(int to:e[x])if(to!=fa&&exi[to]&&(!p||mxd[to]<mxd[p]))p=to;
		if(p&&p!=x)work(p,x,mx+1);
		for(int to:e[x])if(to!=fa&&exi[to]&&to!=p)work(to,x,min(mx+1,mxd[to]+1));
	}

	void mian(){
		cin>>n;
		for(int i=1,x,y;i<n;i++)cin>>x>>y,e[x].push_back(y),e[y].push_back(x);
		cin>>s,s=' '+s;

		int X,Y,nd=-1;
		dfs(1,0,0,nd,X),nd=-1,dfs(X,0,0,nd,Y);
		getp(X,0,Y);
		
		if(len&1){
			int rt=path[len/2+1];
			init(rt,0);
			work(rt,0,len/2);
		}
		else{
			int rt1=path[len/2],rt2=path[len/2+1];
			init(rt1,rt2),init(rt2,rt1);
			work(rt1,rt2,len/2),work(rt2,rt1,len/2-exi[rt1]);
		}

		cout<<ans<<endl;
	}
}

signed main(){
	#ifndef ONLINE_JUDGE
	assert(freopen("in.in","r",stdin));
	// assert(freopen("out.out","w",stdout));
	assert(freopen("out.err","w",stderr));
	#endif
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);   
	LinkWish::mian();
	return 0;
}
```

---

## 作者：pitiless0514 (赞：7)

## Statement
Snuke 君有一棵 $n$ 个节点的全白的树，其中有一些节点他喜欢，有一些节点他不喜欢。他会选择一个他喜欢的节点 $x$，然后选择一个距离 $d$，然后将所有与 $x$ 距离不超过 $d$ 的节点都染成黑色，问最后有多少种可能的染色后状态。

## Solution
什么神仙题！！

问题要统计的可以转化为一个涂黑的连通块，把每一个合法连通块用另外一种方法表示出来。

将一个连通块表示为 $(x,d)$ 的二元组，其中 $x$ 还可以是一条边，表示以 $x$ 为直径中心，半径为 $d$ 的连通块，这个是可以证明没啥问题的。

现在只要知道了中心和半径就可以确定一个连通块，可以考虑枚举中心 $x$，然后求出对应的 $d$ 有多少种取值就好了。

分类讨论一下 $x$ 是边还是点。

假如 $x$ 是连接 $(u,v)$ 的边，且 $maxdep_u \leq maxdep_v$，那么我们显然需要填满子树 $u$ 之后才会蔓延到 $v$，否则 $x$ 这条边不会是中心，于是如果 $u$ 中有喜欢的点，那么最终会有 $1$ 的贡献，否则没有贡献。

接下来考虑 $x$ 是一个点的情况，还需要再分类一下这是个喜欢的点还是不喜欢的点。

在这种情况下直观感受 $d$ 会是一段区间（。

如果 $x$ 是一个喜欢的点，那么 $d$ 的下界显然为 $0$，可以只涂自己一个点。

上界考虑一下 $x$ 中 $maxdep$ 最大的 $y$，也就是 $maxdep_y$ 发现不太行，因为假如这样的话直径中心应该会偏向 $y$ 方向，所以减小一下，取个次大值发现就很对。

如果 $x$ 不是一个喜欢的点，上界和这个无关，那么上界不变，只用思考下界怎么变。

下界应该是有喜欢的点的子树中最小的 $maxdep$，因为为了涂到 $x$，让 $x$ 作为一个直径中点，所以最小的那个喜欢点 $u$ 必须被涂到，但是这样 $u$ 的下面部分也会被涂到，要让 $x$ 作为直径中点而不偏移，于是将下面的也涂掉。

然后对于实现，每次都是让一个点或者一条边作为根，所以随便做一个换根 dp 就好了，然后实现有些细节，可以看代码，我写的好长啊。

总复杂度 $O(n)$。

```cpp
// 德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱德丽莎你好可爱
// 德丽莎的可爱在于德丽莎很可爱，德丽莎为什么很可爱呢，这是因为德丽莎很可爱！
// 没有力量的理想是戏言，没有理想的力量是空虚
#include <bits/stdc++.h>
#define LL long long
#define int long long
using namespace std;
char ibuf[1 << 15], *p1, *p2;
#define getchar() (p1 == p2 && (p2 = (p1 = ibuf) + fread(ibuf, 1, 1 << 15, stdin), p1==p2) ? EOF : *p1++)
inline int read() {
  char ch = getchar();  int x = 0, f = 1;
  while (ch < '0' || ch > '9')  {  if (ch == '-')  f = -1;  ch = getchar();  }
  while (ch >= '0' && ch <= '9')  x = (x << 1) + (x << 3) + (ch ^ 48), ch = getchar();
  return x * f;
}
void print(LL x) {
  if (x > 9)  print(x / 10);
  putchar(x % 10 + '0');
}
template<class T> bool chkmin(T &a, T b) { return a > b ? (a = b, true) : false; }
template<class T> bool chkmax(T &a, T b) { return a < b ? (a = b, true) : false; }
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define repd(i, l, r) for (int i = (l); i >= (r); i--)
#define REP(i, l, r)  for (int i = (l); i < (r); i++)
const int N = 2e6;
int n, num, nex[N], first[N], v[N], a[N];
char s[N];
void add(int from,int to) {
  nex[++num] = first[from];  first[from] = num;  v[num] = to; 
}
int dep[N], mxdep1[N];
struct node {
  int mx, mx2, id;
  void pre() {  mx = mx2 = id = -1;  }
  void upd(int val,int now) {
    if (val > mx) {  mx2 = mx;  mx = val;  id = now;  }
    else if (val > mx2)  mx2 = val;
  }
} pt[N];
void dfs1(int x,int fa) {
  dep[x] = dep[fa] + 1;
  for (int i = first[x]; i; i = nex[i]) {
    int to = v[i];  if (to == fa)  continue;  dfs1(to, x);
  }
}
int f[N], g[N], mxdep2[N];
void dfs2(int x,int fa) {
  int son = 0;
  mxdep1[x] = 0;  g[x] = f[x] = a[x];
  pt[x].pre();  pt[x].upd(0, x);
  for (int i = first[x]; i; i = nex[i]) {
    int to = v[i];  if (to == fa)  continue;
    dfs2(to, x);  mxdep1[x] = max(mxdep1[x], mxdep1[to] + 1);  f[x] += f[to];
    pt[x].upd(mxdep1[to] + 1, to);
  }
}
void dfs3(int x,int fa) {
  int mx = 0, mx2 = 0, id = 0, id2 = 0;
  if (fa) {
    g[x] = g[fa] + f[fa] - f[x];
    if (x == pt[fa].id) {
      if (pt[fa].mx2 != -1) {
        mxdep2[x] = max(mxdep2[x], pt[fa].mx2 + 1);
        pt[x].upd(pt[fa].mx2 + 1, fa);
      }
    }  else {
      if (pt[fa].mx != -1) {
        mxdep2[x] = max(mxdep2[x], pt[fa].mx + 1);
        pt[x].upd(pt[fa].mx + 1, fa);
      }
    }
  }
  for (int i = first[x]; i; i = nex[i]) {
    int to = v[i];  if (to == fa)  continue;  dfs3(to, x);
  }
}
int ans, sum;
pair <int,int> e[N];
int solveedge(int i) {
  int x = e[i].first, y = e[i].second;
  if (dep[x] > dep[y])  swap(x, y);
  int now;
  if (pt[x].id == y)  now = pt[x].mx2;
  else  now = pt[x].mx;
  if (now == mxdep1[y]) {
    if (sum - f[y] || f[y])  return 1;
    return 0;
  }
  if (now < mxdep1[y]) {
    if (sum - f[y])  return 1;
    return 0;
  }
  if (now > mxdep1[y]) {
    if (f[y])  return 1;
    return 0;
  }
  return 1;
}
int solvever(int x) {
  int son = 0;
  for (int i = first[x]; i; i = nex[i])  son++;
  if (son <= 1)  return a[x];
  int u, d = n + 1, mx = -1, mx2 = -1;
  if (a[x])  d = 0;
  mx = mxdep2[x];
  if (mxdep2[x]  && sum - f[x])  d = min(d, mxdep2[x]);
  for (int i = first[x]; i; i = nex[i]) {
    int to = v[i];
    if (dep[to] < dep[x])  continue;
    if (f[to])  d = min(d, mxdep1[to] + 1);
    if (mxdep1[to] + 1 > mx) {
      mx2 = mx,  mx = mxdep1[to] + 1;
    }  else  if (mxdep1[to] + 1 > mx2) {
      mx2 = mxdep1[to] + 1;
    }
  }
  u = mx2;
  if (d == n + 1 || u < d)  return 0;
  return u - d + 1;
}
void solve() {
  cin >> n;
  rep (i, 2, n) {
    int x, y;  cin >> x >> y;
    add(x, y), add(y, x);
    e[i] = {x, y};
  }
  cin >> (s + 1);
  rep (i, 1, n)  a[i] = s[i] - '0', sum += a[i];
  dfs1(1, 0);  dfs2(1, 0);
  dfs3(1, 0);
  int ans = 0;
  // for (int i = 1; i <= n; i++) {
  //   cout << mxdep1[i] << " " << mxdep2[i] << " " << f[i] << " " << g[i] << " " << pt[i].mx << " " << pt[i].mx2 << " " << pt[i].id << "\n";
  // }
  // cout << "---\n";
  rep (i, 2, n)  ans += solveedge(i);
  // cout << ans << "\n" ;
  rep (i, 1, n)  ans += solvever(i);
  cout << ans << "\n";
}
signed main () {
#ifdef LOCAL_DEFINE
  freopen("1.in", "r", stdin);
  freopen("1.ans", "w", stdout);
#endif
  int T = 1;  while (T--)  solve();
#ifdef LOCAL_DEFINE
  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
#endif
  return 0;
}
```

---

## 作者：syzf2222 (赞：6)

设 $F(x,d)$ 表示以 $x$ 为中心距离不超过 $d$ 的点集。

我们希望对于每一个可能的点集，在 $d$ 最小的时候计数。

同时我们把全集单独算，这样留空的集合就会有很好的性质。

如果每个点都是关键点的话，我们发现 $d$ 越小越独特，也就是 $d$ 一定是一个前缀。

对于点 $x$，设其最远距离为 $M$，则一定有 $d<M$，否则覆盖全树了。

其次不能存在 $F(x,d)=F(y,d-1)$，其中 $y$ 是 $x$ 的儿子（将 $x$ 视为根）。

我们发现只要 $F(y,d-1)$ 覆盖不了除了 $y$ 子树外的所有那就一定不行。

于是我们设 $S$ 为 $x$ 所有子树中最远距离的次大值，有 $d<S-2$

那么对于有些点不是关键点的情况，我们考虑本应在此算到的集合有哪些还能背算到。

观察到只要我们能完全覆盖某一个关键点的那一整棵子树即可。

于是我们记 $D$ 为到此点的关键点子树的最大深度的最小值（若此点为关键点则 $D=0$）。

那么 $d\in[D,\min\{M,S-2\})$

换根 $dp$ 出每个点的 $M,S,D$ 然后统计答案即可。

```
#include<bits/stdc++.h>
using namespace std;
#define inf 1e9
const int maxn=2e5+10;
const int mod=1e9+7;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-1;c=getchar();}
	while(c>='0'&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
#define pb push_back
vector<int>G[maxn];
char S[maxn];
int n,m,Mx1[maxn],Mx2[maxn],d[maxn],sz[maxn];
long long ans;
inline void dfs1(int x,int fa){
	if(S[x]=='1')sz[x]=1;else d[x]=inf;
	for(auto t:G[x])if(t^fa){
		dfs1(t,x);sz[x]+=sz[t];
		if(Mx1[t]+1>Mx1[x])Mx2[x]=Mx1[x],Mx1[x]=Mx1[t]+1;
		else if(Mx1[t]+1>Mx2[x])Mx2[x]=Mx1[t]+1;
		if(sz[t])d[x]=min(d[x],Mx1[t]+1);
	}
}
inline void dfs2(int x,int fa){
	ans+=max(0,min(Mx1[x],Mx2[x]+2)-d[x]);
	for(auto t:G[x])if(t^fa){
		int up=(Mx1[x]==Mx1[t]+1)?(Mx2[x]+1):(Mx1[x]+1);
		if(up>Mx1[t])Mx2[t]=Mx1[t],Mx1[t]=up;
		else if(up>Mx2[t])Mx2[t]=up;
		if(sz[1]-sz[t])d[t]=min(d[t],up);
		dfs2(t,x);
	}
}
int main(){
	n=read();
	for(int i=1;i<n;i++){
		int x=read(),y=read();
		G[x].pb(y),G[y].pb(x);
	}scanf("%s",S+1);
	dfs1(1,0);dfs2(1,0);
	printf("%lld\n",ans+1);
    return 0;
}

```

深深地感到自己的弱小。

---

## 作者：EuphoricStar (赞：4)

神题！！！！111

考虑如何不重不漏地计数。先考虑全为 `1` 的情况，令 $f(u,d)$ 为与 $u$ 的距离 $\le d$ 的点集。

首先单独算全集，那么对于不是全集的集合就会有一些比较好的性质。

考虑若有若干个 $f(u,d)$ 同构，那 **只在 $d$ 最小的时候计数**。

那么 $f(u,d)$ 需要满足不能覆盖全集，且不存在与 $u$ 相邻的点 $v$，使得 $f(u,d) = f(v,d-1)$（由于 $d$ 最小的约束）。

考虑若存在后者时发生了什么。把 $v$ 这棵子树抠掉之后，存在一个点使得它与 $u$ 距离 $\ge d - 2$。

令 $f_u$ 为以 $u$ 为根的子树最大深度，$g_u$ 为以 $u$ 为根的子树次大深度（不存在则为 $0$），$d_u$ 为 $f(u,d)$ 最大能取到的 $d$，则等价于 $d_u < \min(f_u,g_u+2)$。

换根求出 $f_u,g_u$ 即可。于是我们就做完了全为 `1` 的情况。

现在有一些点是 `0`。但是我们发现不能完全不考虑它们，因为我们发现有些 `1` 点的 $d_u$ 上界过于严苛导致有些情况没有考虑到，那我们将这些情况放到 `0` 点计算。

发现 `0` 点的上界仍然可以取到，但是下界并非 $0$。设任意 `0` 点为 $u$，则未算到的情况满足 `1` 点所在子树中全被覆盖，并且还可能覆盖了别的子树。设 $h_u$ 为以 $u$ 为根的存在 `1` 点的子树的最大深度，则对于 `0` 点，$h_u \le d_u < \min(f_u,g_u+2)$。

此时的 $h_u$ 仍然可以换根求出，于是我们就以 $O(n)$ 的时空复杂度做完了。

---

## 作者：ezoiLZH (赞：4)

## 题解：

设$f(i,d)$，为把距 $i$ 点小于等于 $d$ 染成黑色的集合。

不过这样染色的时候会有重复的方案，我们考虑下何时会重复。

当 $f(i,d_1) $ 和 $f(j,d2)$，重复时，当且仅当 $i$，$j$ 之间存在一点 $k$，使得 $f(k,d1-dist(i,k))$，$dist(i,j)$ 表示 $i$，$j$ 的树上距离。

这个很显然吧……

所以对于某个$f(i,d)$，如果有$f(k,d1-dist(i,k))=f(i,d)$，那么 $f(i,d)$ 就会被重复算。

对于每一个$i$，我们只用考虑更他相邻的点和他的重复情况就可以了。（也很显然吧）

那我们再考虑一下，何时 $f(i,d)=f(k,d-1)$。

还是很显然，如果以 $k$ 为根，$i$ 的子树全部被染成黑色的话，他们就相等。

所以可以得知，$d$ 的上界为 $i$ 到他子树中的最远点的距离。

那我们用树形dp，$O(n)$ 算出，然后暴力枚举每个 $i$，算 $d$ 的上界。

那下界呢？ 如果 $i$ 点是特殊点，无疑是0，那如果不是呢？

如果不是，那么若存在一个特殊节点j满足方案$(i,d)$中 $j$ 所在子树内所有节点均被染成黑色，$(i,d)$ 就是一个合法的染色方案。故我们只需要求出从 $i$ 出发的至少经过 1 个特殊节点到达 $j$ 子树中的最远节点的距离的最小值，就是可行的 $d$ 的最小值。

知道每个 $i$，$d$ 的上下界，那就算吧！

## CODE：
```cpp
#include<iostream>
#include<cstdio>
using namespace std;

int d1[200005],d2[200005];
int d3[200005],d4[200005];
//d1:子树中的最远距离
//d2:非子树中的最远距离
//d3:这个节点到子树中至少经过1个特殊节点到达子树中的最远节点最小距离 
//d4:从他父亲出发，不经过这棵子树的最远路径 
int n,x,y,siz[200005],col[200005],fa[200005];
long long ans=0;
int tot=0,h[200005];
struct Edge{
	int x,next;
}e[400005];
char ch[200005];

inline void add_edge(int x,int y){
	e[++tot].x=y;
	e[tot].next=h[x],h[x]=tot;
}

void dfs1(int x,int father){
	siz[x]=col[x],fa[x]=father;
	d3[x]=col[x]?0:1e9;
	for(int i=h[x];i;i=e[i].next){
		if(e[i].x==father)continue;
		dfs1(e[i].x,x);
		siz[x]+=siz[e[i].x];
		d1[x]=max(d1[x],d1[e[i].x]+1);
		if(siz[e[i].x])
			d3[x]=min(d3[x],d1[e[i].x]+1);
	}
}

void dfs2(int x,int father){
	if(father)d4[x]=d2[x]-1;
	int maxn=0,sec=0;
	for(int i=h[x];i;i=e[i].next){
		if(e[i].x==father)continue;
		if(d1[e[i].x]+1>maxn)
			sec=maxn,maxn=d1[e[i].x]+1;
		else sec=max(sec,d1[e[i].x]+1);
	}
	for(int i=h[x];i;i=e[i].next){
		if(e[i].x==father)continue;
		if(d1[e[i].x]+1==maxn)
			d2[e[i].x]=max(d2[x],sec)+1;
		else d2[e[i].x]=max(d2[x],maxn)+1;
		dfs2(e[i].x,x);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<n;i++){
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	scanf("%s",ch+1);
	for(int i=1;ch[i];i++)
		col[i]=ch[i]-'0';
	dfs1(1,0),dfs2(1,0);
	for(int i=1;i<=n;i++){
		int minv,maxv;
		minv=min(d3[i],siz[1]==siz[i]?(int)1e9:d2[i]);
		maxv=max(d1[i],d2[i])-1;
		for(int j=h[i];j;j=e[j].next){
			if(e[j].x==fa[i])maxv=min(maxv,d1[i]+1);
			else maxv=min(maxv,d4[e[j].x]+1);
		}
		if(maxv>=minv)ans+=1LL*maxv-minv+1;
	}
	printf("%lld",ans+1);
}
```

---

## 作者：OtoriEmu (赞：3)

这个题还是在模拟赛遇到的，但是这次的部分分在原题里也给出来了，也许会好讲一些。

首先如果不考虑算重的话这个很简单，每个点的贡献就是每个点到树上最远的点的距离再加一。当然有重复的，问题就并不那么简单了。

将一个被覆盖的连通块用 $F(u,r)$ 表示，其中 $u$ 表示“圆心”，$r$ 表示半径。注意到除了整棵树以外，每个连通块不同时存在 $F(u_0,r)$ 和 $F(u_1,r)$ 两种表示（证明可以考虑连通块的边界点），那么对于一个连通块 $F(u,r)$，其有 $F(u_0,r_0),F(u_1,r_1),\cdots$ 若干种表示。假设 $r_0$ 是其中最小的，我们只计数 $F(u_0,r_0)$，这样就做到了去重的效果。注意到这里的特殊情况是整棵树，我们先不考虑这东西。

先做一下部分分，也即每个点都可以作为圆心。此时对于每个 $u$，能造成贡献的 $F(u,r)$ 满足 $r$ 不超过一个值 $p_u$。例如，假设有 $F(u,r) = F(v,r-1)$，首先 $F(u,r)$ 不计算贡献，这体现了每个点造成贡献的 $r$ 的上限。然后通过分析可以知道，$v$ 是 $u$ 的邻接结点，并且如果以 $u$ 为根，$F(u,r)$ 包含除了 $v$ 这棵子树的所有子树。邻接结点这个性质比较好理解，后面那个仍然可以用维护边界点的方法来考虑。

那么可以知道这个 $v$ 取 $u$ 到最远的点所在的以 $u$ 为根时 $u$ 的子树内与 $u$ 相连的点比较科学。同时发现次远的点不能被 $F(v,r-1)$ 覆盖。记最远的距离为 $f_u$，次远为 $g_u$。那么 $p_u = \min(f_u-1, g_u+1)$（$f_u-1$ 的原因是 $F(u,r)$ 不能包含整棵树）。一个点 $u$ 的贡献就是 $p_u+1$。

接下来的情况是并不是每个点都可以作为圆心，因此对于 $u$，有贡献的 $F(u,r)$ 可能并不是 $[0, p_u]$ 的一段简单的区间。我们仍然考虑 $F(u,r)$ 是否造成贡献，当然此时 $u$ 并非可以作为圆心的点（否则就是上面的问题）。假设有另外一个圆心 $v$ 满足 $F(u,r_u) = F(v,r_v)$，这样就可能造成贡献，但是有一定要求。

这个要求直接给出，具体的是 $F(u,r_u)$ 需要在以 $u$ 为根时包含整棵 $v$ 所在的 $u$ 的子树。证明采用分类讨论：如果 $v$ 的子树内有没覆盖的点，这根本不符合题设，因为这样 $r_v < r_u$；否则的话 $v$ 的子树内满足覆盖，有另外一个点 $c$ 及其子树没有被覆盖，两点的最近公共祖先为 $d$，$\operatorname{dis}(v,d) = d_1 \leq d_3 = \operatorname{dis}(c,d)$，而 $r_u = d_2+d_3, r_v=d_1+d_3$，则 $F(d,d_3) = F(u,d_2+d_3)$，构造出了满足题设的解。证明完毕，可以手画一下验证。

现在需要找到所有子树内，有可以作为圆心的点并且深度最小的，这个可以知道下界，上界仍沿用一开始的方法。问题解决，可以采用换根 DP 的手法解决问题。[评测链接](https://atcoder.jp/contests/agc008/submissions/35957563)。

---

## 作者：SalN (赞：2)

~~重新提交修改了一处笔误。重新提交致歉。~~

先考虑所有点都喜欢的情况，设 $S(u,d)$ 表示选择了点 $u$ 和距离 $d$ 时被染黑的点集，我们要统计本质不同的 $S$ 的数量。在钦定 $u$ 的情况下，设 $mx_u$ 表示离 $u$ 的最远距离，重复的只有 $d\geq mx_u$ 的情况，我们不妨只统计不为全集的 $S$ 的数量最后再加入这个贡献（下面可能会默认 $S$ 不是全集，不然就认为不存在这种 $S$，不存在的不考虑），这样子钦定 $u$ 之后对于不同的 $d$ 对应的 $S$ 不会重复，在钦定 $d$ 之后对于不同的 $u$ 对应的 $S$ 也不会重复。可以得出重复的形式应该是 $S(u,d)=S(v,d+\Delta)$ 其中 $u\neq v,\Delta>0$，我们让一个 $S$ 在 $d$ 最小的时候贡献，令人欢喜的，能得到 $S$ 的最小 $S(,d)$ 显然只有一个，因此可以转换成计算对于任意 $v,d'$ 有 $S(u,d)\neq S(v,d'(<d))$ 的 $(u,d)$ 对数，我们称这个 $d$ 是对于 $u$ 优秀的，基本的约束有一个 $d<mx_u$。

枚举 $u$ 并令其为树根，现在要计算有多少对其优秀的 $d$，那需要知道是否存在 $u\neq v,d_0<d$ 满足 $S(u,d)=S(v,d_0)$，我们来考虑 $S(u,d)=S(v,d_0)$ 的情况，首先 $u\to v$ 路径一定是黑的，假设 $v$ 的子树里面有白点 $p$，那一定存在一个父亲是黑点的白点 $p$，为了使这个 $p$ 是白的 $fa_p$ 是黑的，一定要有 $d=d_0+dis(u,v)$，这个前提下 $S(v,d_0)\subseteq S(u,d)$，那么 $S$ 在非 $v$ 子树内一定没有白点，不然白点 $p$ 旁边的黑点 $q$ 是被 $S(u,d)$ 极限染黑的，$S(v,d_0)$ 到那里一定还有距离，然后如果 $v$ 子树内没有白点，类似容易分析出 $u$ 的没有 $v$ 的儿子树一定全都是黑的因为如果有白点一定有 $S(v,d_0)$ 距离不够的相邻黑点，然后画图很难不发现对于没有被分析的位置也就是 $u\to v$ 的路径上的点不包括 $u,v$ 的的子树中如果有白点，画图微调容易发现 $S(u,d)$ 的 $d$ 不是最小的了。总结上述分析发现对于优秀的 $S(u,d)$， $S(u,d)$ 和 $S(v,d_0)$ 等价的情况只有 $S(u,d_0+dis_v)=S(v,d_0)$，要求只有 $v$ 的子树里面有白点。

我们现在终于可以回过头来分析 $S(u,d)$ 是优秀的条件了，根据上面的理论容易得到只看儿子就行了，那么应该对于任意 $u$ 的儿子 $v$ 有 $S(u,d)\neq S(v,d-1)$，那么不应该存在不在 $u$ 的包含 $v$ 的子树里的点 $p$ 使得 $dis(u,p)=d-1$ 这样 $v$ 刚好染不到，实际判定是否存在 $u$ 的不包含 $v$ 的子树里的点 $p$ 使得 $dis(u,p)\geq d-1$ 即可，这个最严格的约束显然在 $v$ 在 $u$ 最大深度最大的子树里的时候出现，此时需要知道 $u$ 的次大深度子树深度 $se_u$，约束就是 $d\leq se_u+1$。

现在考虑有不喜欢的点怎么办，我们上面已经分析出了「对于优秀的 $S(u,d)$， $S(u,d)$ 和 $S(v,d_0)$ 等价的情况只有 $S(u,d)=S(v,d+dis_v)$，要求只有 $u$ 的包含 $v$ 的子树里面没有白点」的平替论（虽然换了定义但这个显然一样吧），现在考虑不喜欢的 $u$ 的优秀的 $S(u,d)$ 能不能喜欢的 $v$ 的 $S(v,d+dis_v)$ 平替，额外的要求显然只有 $S(u,d)$ 可以把 $u$ 的包含 $v$ 的子树全部染黑，设 $u$ 有喜欢的点的子树的最大深度的最小值为 $mi_u$，那么应该有 $d\geq mi_u$。

换根 dp 求出上面的 $mx_u/se_u/mi_u$ 即可，代码非常短。

```cpp
#include<bits/stdc++.h>
#define int long long
#define up(i,l,r) for(int i=l; i<=r; ++i)
#define dn(i,r,l) for(int i=r; i>=l; --i)
#define pb push_back

using namespace std;

const int N=200005;

int n, siz[N], mx[N], se[N], mi[N], Ans;
char str[N];
vector<int> to[N];

void dfs1(int x,int fad) {
	if(str[x]=='1') mi[x]=0, siz[x]=1; else mi[x]=1e9;
	for(int y:to[x]) if(y!=fad) {
		dfs1(y,x), siz[x]+=siz[y];
		if(mx[y]+1>mx[x]) se[x]=mx[x], mx[x]=mx[y]+1;
		else if(mx[y]+1>se[x]) se[x]=mx[y]+1;
		if(siz[y]) mi[x]=min(mi[x],mx[y]+1);
	}
}

void dfs2(int x,int fad) {
	int limit=min(mx[x]-1,se[x]+1);
	if(mi[x]<=limit) Ans+=limit-mi[x]+1; 
	for(int y:to[x]) if(y!=fad) {
		int ran=(mx[y]+1==mx[x])?(se[x]+1):(mx[x]+1);
		if(ran>mx[y]) se[y]=mx[y], mx[y]=ran;
		else if(ran>se[y]) se[y]=ran;
		if(siz[1]-siz[y]) mi[y]=min(mi[y],ran);
		dfs2(y,x);
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n;
	up(i,2,n) {
		int u, v;
		cin >> u >> v;
		to[u].pb(v);
		to[v].pb(u);
	}
	cin >> (str+1);
	dfs1(1,0), dfs2(1,0);
	cout << Ans+1;
	return 0;
}
```

---

## 作者：_Cheems (赞：2)

蒟蒻看完题解后的一些理解。

先考虑每个点都可以选的情况，记 $S(u,k)$ 表示所有与 $u$ 的距离不超过 $k$ 的点构成的连通块。

本题难点在于可能有 $S(u,k)=S(u^\prime,k^\prime)$，导致算重。但是可以发现，除了整棵树的情况，对于一个连通块 $S$，在所有 $S(u,k)=S$ 中恰有唯一一个最小的 $k$。这不难证明，对于所有 $S(u,k)=S$，那么两点 $u\ne v$ 它们的 $k$ 必然不同。

把整棵树的情况扔掉最后再加进来。考虑让一个 $S$ 在最小的 $k$ 处被统计。枚举 $u$ 提为根，考虑哪些 $k$ 使得不存在更小的点 $v$。那么 $v$ 必然在 $u$ 的“未溢出”子树中，也就是距离 $u$ 最远的点所在的子树。

补充一下概念，在 $S(u,k)$ 中，$u$ 的“未溢出子树”是指子树内存在一点未被覆盖，“溢出子树”反之。

进一步的，只需考虑该子树的根也就是与 $u$ 相邻的点 $v$ 即可，判断 $S(v,k-1)=S(u,k)$。首先 $v$ 子树肯定能被覆盖，考虑 $u$ 的其它溢出子树是否能被覆盖。记 $f_u$ 表示距离 $u$ 最远的点的距离，$g_u$ 表示次远点（不能和 $f_u$ 在同一棵子树中，假如 $u$ 只有一棵子树那么取 $0$），那么 $S(v,k-1)=S(u,k)$ 当且仅当 $g_u\le k-2$。

注意一下，上述讨论默认了 $S(u,k)$ 有且仅有一棵未溢出子树。其实就算存在其它未溢出子树，上述判定式仍然成立，因为 $g_u>k>k-2$。

对了因为不考虑整棵树所以 $k\le f_u-1$。综上，合法的 $k\in [0,\min(f_u-1,g_u+1)]$。

现在考虑有的点不可选择的情况。我们仍然让 $S$ 在其最小点 $u$ 被统计，即使该点不可选择。只不过要额外判定存在一个可选择点 $v$ 满足 $S(v,k^\prime)=S$。

假如 $u$ 可以选择那么没有影响，否则，考虑何时存在 $S(v,k^\prime)=S(u,k)$。由于 $u$ 是最小点所以 $v$ 只能在 $u$ 的溢出子树中。不难发现只要 $u$ 的溢出子树中存在一个可选择的点 $v$，那么必然可以构造 $k^\prime$ 使得 $S(v,k^\prime)=S(u,k)$。

于是我们记录 $h_u$ 表示 $u$ 的合法子树中最大深度最小的子树深度是多少，合法子树满足子树内存在一个可被选择的点。那么 $k\in [h_u,\min(f_u-1, g_u+1)]$。

$f,g,h$ 不难换根 dp 维护，复杂度 $O(n)$。
#### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

#define LL long long
const int N = 2e5 + 5, inf = 1e8;
int n, u, v, g[N], h[N], vis[N], dis2[N], vis2[N];
vector<int> to[N];
struct node{int x, y;} f[N], dis[N];
LL ans;
char c[N]; 

inline void upd(node &a, int x){
	if(x >= a.x) a.y = a.x, a.x = x;
	else a.y = max(a.y, x); 
}
inline void dfs(int u, int fa){
	f[u] = {0, 0}, h[u] = c[u] == '1' ? 0 : inf;
	dis[u] = {0, 0}, vis[u] = c[u] == '1';
	for(auto v : to[u])
		if(v ^ fa){
			dfs(v, u), vis[u] += vis[v];
			upd(f[u], f[v].x + 1);
			upd(dis[u], dis[v].x + 1);
			if(vis[v]) h[u] = min(h[u], dis[v].x + 1);  
		}
}
inline void dfs2(int u, int fa){
	g[u] = 0;
	dis2[u] = 0;
	if(fa){
		g[u] = g[fa] + 1;
		if(f[fa].x == f[u].x + 1) g[u] = max(g[u], f[fa].y + 1);
		else g[u] = max(g[u], f[fa].x + 1);
		dis2[u] = dis2[fa] + 1; 
		if(dis[fa].x == dis[u].x + 1) dis2[u] = max(dis2[u], dis[fa].y + 1);
		else dis2[u] = max(dis2[u], dis[fa].x + 1);
		if(vis[1] - vis[u] > 0) h[u] = min(h[u], dis2[u]);
	}
	for(auto v : to[u])
		if(v ^ fa) dfs2(v, u);
}
signed main(){
	cin >> n;
	for(int i = 1; i < n; ++i) scanf("%d%d", &u, &v), to[u].push_back(v), to[v].push_back(u);
	scanf("%s", c + 1);
	dfs(1, 0), dfs2(1, 0);
	for(int i = 1; i <= n; ++i){
		upd(f[i], g[i]);
		int L = h[i], R = min(f[i].x - 1, f[i].y + 1);
		ans += max(0, R - L + 1);
	}
	cout << ans + 1;
	return 0;
}
```

---

## 作者：Felix72 (赞：2)

这是我做过的最好的树上问题，强烈推荐。

经过一段时间的手玩，我们很快就会明白这题的难点在于有些连通块的染色方法是唯一的，有些则不唯一。因此这题的关键是找到一个合适的去重方法。为方便讨论，这里不计算全黑，最后再加上。

![](https://cdn.luogu.com.cn/upload/image_hosting/fv0jdnq6.png)

（这个图把颜色反了一下）

如图，这里把树当作无根树。那么定义一种操作**扩散**，即对于一个黑连通块，把距离它只有一步的点也涂黑，并且**要求中心黑点操作前后至少还有两棵子树里有白点**。为什么要有这个要求呢？因为我们注意到，对于上面这个图，如果没有这个要求，则既可以看作最上面节点**扩散**两次的结果，也可以看作它最右边儿子**扩散**三次的结果。而有了这个要求，就达到了一个去重的效果。（上面这个图只能看做最上面节点扩散两次的结果）

定义没有这种限制的扩散操作为**广义扩散**。

我们得知，有些连通块可以直接通过**扩散**若干次得到。对于这种连通块，记作**一类块**。

![](https://cdn.luogu.com.cn/upload/image_hosting/li4rlm7z.png)

对于这种不能通过扩散达成的情况，我们成为**二类块**。我们考虑分类统计这两种块。

#### 一类块

对这种东西，如果所有点都能选，那么自然是容易统计的。但是有些点无法选择。那么我们对于一个点 $u$ 分情况讨论，记扩散次数为 $d$。（$d$ 小于次长链长度）

若 $s_u$ 为 ```1```，则 $d$ 最小能取到 $0$；

若 $s_u$ 为 ```0```，则需要有一棵子树，其中有一个点经过若干次**广义扩散**，达到了与在 $u$ 上**扩散**同样的效果（显然，这个子树应该被填满了）。这个选点可以很多，但我们只用关心 $d$ 的范围。若把整棵树当作有根树，记录 $g_i$ 为在 $i$ 的子树内选一个点，使得这个子树被填满的同时，涉及到子树外点范围的最小值。通过计算 $g$，我们能知道 $d$ 的下界。

#### 二类块

这种块能看成填满了子树内的某个点经过**广义扩散**填满某棵子树，并在子树的根节点在进行若干次**扩散**得到。那么我们枚举哪颗子树被填满，剩下的依旧是算范围，过程相似。

这时可能会有疑问：如果我们把树看作有根树，那么得分类讨论填满的是父亲边的部分还是子树，算范围时也得考虑上，这不是太麻烦了吗？因此，我们用直径的中心作为根节点，避免了讨论父亲边的问题。

---

## 作者：DaiRuiChen007 (赞：2)

# AGC008F 题解

[Problem Link](https://www.luogu.com.cn/problem/AT_agc008_f)

**题目大意**

> 给定一棵 $n$ 个点的数，$f(u,d)$ 定义为距离 $u$ 不超过 $d$ 的点构成的集合，给定一个集合 $S\subseteq V$，求对于所有 $u\in S$ 共有多少本质不同的 $f(u,d)$。
>
> 数据范围：$n\le 2\times 10^5$。

**思路分析**

首先考虑 $S=V$ 的情况，容易发现 $f(u,d)$ 容易产生重复，因此考虑最小表示法计数，对于每个 $\ne V$ 的 $f(u,d)$，一定有一个 $u$ 能最小化 $d$，那么我们在这个 $u$ 处记录 $d$ 即可。

以 $u$ 为根考虑，首先 $f(u,d)<V$，因此 $d<fi_u$，其中 $fi_u$ 表示 $u$ 所有儿子中的最大深度，然后考虑最小化 $d$ 的限制，如果存在一个 $u$ 的儿子 $v$ 满足 $f(v,d-1)=f(u,d)$ 则此时 $d$ 不合法。

此时删掉 $v$ 子树，不存在和 $u$ 距离 $d-1/d$ 的点，考虑取删除 $fi_u$ 对应子树，显然找次大深度子树，记为 $se_u$，那么 $d-1\le se_u$，可以证明 $d<\min(fi_u,se_u+2)$ 是充分的。

然后考虑 $S\ne V$ 的情况，对于一个 $u\not\in S$，依然考虑以 $u$ 为最小表示的点集，且这个点集能被另一个 $S$ 中的点 $v$ 表示，显然要求 $v$ 对应的子树全部属于 $f(u,d)$，求出这些 $v$ 对应子树里深度最小的一个，记为 $lo_u$，$u$ 的贡献就是 $\min(fi_u,se_u+2)-lo_u$。

换根 dp 维护即可，记得最后加上全集。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5,INF=1e9;
int dis[MAXN],sum[MAXN],ans=1;
vector <int> G[MAXN];
char col[MAXN];
inline void dfs0(int u,int fa) {
	for(int v:G[u]) if(v^fa) {
		dfs0(v,u),sum[u]+=sum[v];
		dis[u]=max(dis[u],dis[v]+1);
	}
}
inline void dfs1(int u,int fa,int out) {
	int fi=out,se=0,lo=col[u]=='1'?0:(sum[u]<sum[1]?out:INF);
	for(int v:G[u]) if(v^fa) {
		se=max(se,min(fi,dis[v]+1)),fi=max(fi,dis[v]+1);
		if(sum[v]) lo=min(lo,dis[v]+1);
	}
	ans+=max(0ll,min(se+2,fi)-lo);
	for(int v:G[u]) if(v^fa) dfs1(v,u,dis[v]+1==fi?se+1:fi+1);
}
signed main() {
	int n;
	scanf("%lld",&n);
	for(int i=1,u,v;i<n;++i) scanf("%lld%lld",&u,&v),G[u].push_back(v),G[v].push_back(u);
	for(int i=1;i<=n;++i) scanf(" %c",&col[i]),sum[i]=col[i]-'0';
	dfs0(1,0),dfs1(1,0,0);
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：Hilaria (赞：1)

### [AGC008F Black Radius](https://www.luogu.com.cn/problem/AT_agc008_f)

- 题意：

  Snuke 君有一棵 $n$ 个节点的全白的树，其中有一些节点他喜欢，有一些节点他不喜欢。

  他会选择一个他喜欢的节点 $x$，然后选择一个距离 $d$，然后将所有与 $x$ 距离不超过 $d$ 的节点都染成黑色，问有多少种本质不同的染色状态。

  $2\leq N\leq 2\times 10^5 $

- 思路：

  首先，经过观察和手玩，容易发现一个黑色连通块可以由不同的节点扩散得到，也就是说，我们会算重，所以这题重点在于如何去重，那么去重我们可以考虑加钦定使得在计算时每种方案都只会在一个地方算到，即在计算时就不会重复。

  然后我们从简单的开始考虑，先考虑所有点都可以进行扩散的情况（即 Snuke 君喜欢所有点）。

  对于一个黑色点的连通块 $S$，我们定义一个点 $p$ 要扩散成 $S$ 的最小扩散半径为 $d_p$，我们称能扩散成 $S$ 的点中 $d_p$ 最小的点称为这个集合的中心点。

  那么我们进行一个手玩，然后就可以发现，有两种情况：

  - $S$ 为全集，即整棵树都是黑的，那么可能有两个中心点。
  - 当 $S$ 非全集时，一定只有一个中心点（证明见下文）。

  所以我们可以将 $S$ 为全集的情况分开考虑，然后考虑在每个集合的中心点进行统计，这样我们就不会算重复了。

  证明：

  - 当 $S$ 为全集时，显然重心为中心点，然后重心确实最多就俩。

  - 当 $S$ 非全集，那么我们将一个中心点 $p$ 作为根，该连通块的最小扩散半径为 $d_p$，考虑能不能找到另一个点 $v$ 使得其 $d_v=d_p$。

    由于 $S$ 非全集，所以 $p$ 至少还有一个子树还有扩散空间（即还有子树有白点），那么分讨：

    1. $v$ 往有扩散空间的子树转，那么由于集合 $S$ 不能变，那么 $d_v$ 起码得是 $d_p-1$，不合法。
    2. $v$ 往没有扩散空间的子树转，那么由于集合 $S$ 不能变，那么 $d_v$ 起码得是 $d_p+1$，不合法。

    综上所述，当 $S$ 非全集时，一定只有一个中心点。

  那么此时，我们就可以对于每个点 $p$ 算当该点为中心点的所有集合 $S$。

  那么为了方便分析，我们假设树是以 $p$ 为根的，然后注意到 $S$ 不能取到全集，所以 $d_p\leq f_p-1$（$f_p$ 为 $p$ 在树上最远点的距离）。

  由于只有当 $d_p\geq f_p$ 也就是取全集时会出现重复 $S$，其余的 $d_p$ 会对应唯一一个 $S$，所以我们可以直接讨论 $d_p$ 的取值范围。

  然后我们反向思考，若能找到一个 $v\ |\ v\in p,d_v=d_p-1$ 的充要条件是什么（$v\in p$ 意思是 $v$ 是 $p$ 的儿子节点）：

  画个丑图（图为不存在这样的 $v$ 的情况）：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/rjy961ao.png)

  首先 $v$ 肯定是要往可扩展子树转的，解释和上面的证明相似，然后显然可扩展子树只能有一个，因为若有两个的话，$v$ 无论往哪个转移，剩下那个子树最远的黑点和 $v$ 的距离就一定为 $d_p+1$ 了。

  然后由于转移后 $v$ 要覆盖不可扩展子树，那么我们记 $L$ 为不可扩展子树中离 $p$ 最远的点的距离，那么是不是要满足 $L+1\leq d_v=d_p-1$。

  那么综上，存在这样一个 $v$ 的充要条件为 ：

  1. $p$ 的可扩展子树的数量为 $1$；
  2. $L\leq d_p-2$

  那么 $p$ 是中心点就等价于不存在这样一个可以转移的 $v$，那么是不是破坏上述两个条件中任意一个即可。

  那么我们再定义一个 $g_p$ 为 $p$ 子树中次远点的距离（注意不能和最远点同一个子树），画个丑图：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/cwfhi35r.png)


  然后对于第一个条件，那么是不是只要我们让可扩展子树的数量 $\geq 2$ 即可，那么只要 $d_p\leq g_p-1$ 就可以满足，所以 $d_p\in[0,g_p-1]$ 全部合法。

  那么现在我们只考虑 $d_p\geq g_p$ 的情况，显然此时第一个条件自动满足。

  对于第二个条件，此时 $L=g_p$，那么我们要让 $L>d_p-2$ 即 $d_p\leq g_p +1$ 都合法，那么 $d_p\in [g_p,g_p+1]$ 合法。

  所以综上，$d_p\in [0,g_p+1]$ 都合法，再加上 $S$ 非全集的限制，即 $d_p\in [0,min(g_p+1,f_p-1)]$。

  然后 $f_p,g_p$ 都可以换根求出，最后再加上 $S$ 为全集就做完了所有点都能选的情况。

---

  现在不是所有点都能作为扩散点了，但是为了不重复，我们仍然在一个集合 $S$ 的中心点统计它（$S$ 非全集，当然这个 $S$ 得确实能被扩散到）。

  我们仍假设这个中心点为 $p$，那么如果 $p$ 可以作为扩散点，那么他作为中心的情况和上面相同。

  若 $p$ 不能作为扩散点，那么由于我们默认这个集合 $S$ 是能被扩散的，所以 $p$ 一定是由一个可以作为扩散点的 $v,d_v>d_p$ 移过来的。

  那么这个 $v$ 存在的充要条件是什么，我们对此进行分析：

  首先根据上面的条件，$d_p$ 至少要满足 $d_p\leq min(g_p+1,f_p-1)$。

  再画一个丑图帮助理解：

  ![](https://cdn.luogu.com.cn/upload/image_hosting/6oc128vy.png)

  我们 $v$ 的转移路径是红色路径，根据上文，$v$ 往 $p$ 转移的条件是：可扩展子树数量为 $1$，$L\leq d-2$，而且只会往可扩展子树转移。

  所以 $v$ 的子树一定是不可扩展的，即灰色点全部覆盖。

  然后转移到上面的 $6$ 号点，$6$ 要是还想往上，那么 $6$ 的子树也得全覆盖，以此类推，就是到 $2$ 的子树全覆盖。

  所以 $p$ 需要覆盖 $2$ 的子树，由于只要存在这样一个 $v$ 即可，所以 $d_p$ 的下限应取 $p$ 的包含可扩展点（Snuke 君喜欢的点）的子树的深度最大的最小值，我们记这个值为 $h_p$，那么若 $p$ 的不是可扩展点，那么他的取值范围是 $d\in[h_p,min(g_p+1,f_p-1)]$。

  然后换根做即可。


```cpp
#include<bits/stdc++.h>
#define int long long
#define ull unsigned long long
#define pb push_back
#define mp make_pair
#define pii pair<int,int>
#define db double
using namespace std;

const int MAXX=2e5+10;
const int inf=1ll<<60;

int n,fla[MAXX],m;
string s;
int tot,in[MAXX],out[MAXX];
int f[MAXX],g[MAXX],h[MAXX];
vector<int> ed[MAXX];
vector<int> Pre[MAXX],Las[MAXX];
int pid[MAXX],lid[MAXX];
int c[MAXX];
void add(int x) { for(;x<=n;x+=(x&(-x))) c[x]++;}
int ask(int x) {
	int res=0;
	for(;x;x-=(x&(-x))) res+=c[x];
	return res;
}
int check(int l,int r) { return ask(r)-ask(l-1);}
void init(int p,int fa) {
	in[p]=++tot;
	int len=ed[p].size();
	for(int i=0;i<len;i++) {
		int v=ed[p][i];
		if(v!=fa) init(v,p);
	}
	out[p]=tot;
}
void dfs(int p,int fa) {
	int len=ed[p].size(),cnt=0;
	h[p]=inf;
	Pre[p].pb(0);
	for(int i=0;i<len;i++) {
		int v=ed[p][i];
		if(v==fa) continue;
		dfs(v,p);
		if(f[v]+1>=f[p]) g[p]=f[p],f[p]=f[v]+1;
		else if(f[v]+1>g[p]) g[p]=f[v]+1;
		Pre[p].pb(f[v]+1),pid[v]=++cnt;
		if(check(in[v],out[v])) h[p]=min(h[p],f[v]+1);
	}
	cnt=0;
	Las[p].pb(0);
	for(int i=len-1;i>=0;i--) {
		int v=ed[p][i];
		if(v==fa) continue;
		Las[p].pb(f[v]+1),lid[v]=++cnt;
	}
	int lenp=Pre[p].size(),lenl=Las[p].size();
	for(int i=1;i<lenp;i++) Pre[p][i]=max(Pre[p][i-1],Pre[p][i]);
//	cout<<"check : "<<p<<'\n';
//	for(int i=0;i<lenl;i++) cout<<Las[p][i]<<" ";
//	cout<<'\n';
	for(int i=1;i<lenl;i++) Las[p][i]=max(Las[p][i-1],Las[p][i]);
}
void dfs2(int p,int fa,int pre) {
//	cout<<"check "<<p<<" "<<pre<<'\n';
	int len=ed[p].size();
	if(pre>=f[p]) g[p]=f[p],f[p]=pre;
	else if(pre>g[p]) g[p]=pre;
	if((m-check(in[p],out[p]))>0) h[p]=min(h[p],pre);
	for(int i=0;i<len;i++) {
		int v=ed[p][i];
		if(v==fa) continue;
		int tmp=max(Pre[p][pid[v]-1],Las[p][lid[v]-1]);
//		cout<<"v = "<<v<<" : "<<pid[v]-1<<" "<<lid[v]-1<<'\n';
		dfs2(v,p,max(pre,tmp)+1);
	}
}
int ans;
void sol(int p,int fa) {
	int len=ed[p].size();
	if(fla[p]) ans+=min(g[p]+1,f[p]-1)+1;
	else ans+=max(0ll,min(g[p]+1,f[p]-1)-h[p]+1);
	for(int i=0;i<len;i++) {
		int v=ed[p][i];
		if(v!=fa) sol(v,p);
	}
}
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n;
	for(int i=1,u,v;i<n;i++) cin>>u>>v,ed[u].pb(v),ed[v].pb(u);
	cin>>s;
	init(1,0);
	for(int i=1;i<=n;i++) {
		if(s[i-1]=='0') fla[i]=0;
		else fla[i]=1,m++,add(in[i]);
	}
	if(!m) { cout<<"0";return 0; }
	dfs(1,0),dfs2(1,0,0);
//	for(int i=1;i<=n;i++) cout<<i<<" = "<<f[i]<<" "<<g[i]<<" "<<h[i]<<'\n';
	sol(1,0);
	cout<<ans+1;

	return 0;
}
```

---

## 作者：0xyz (赞：0)

一个点集可能会被算很多次。所以对于一个点集 $S(x,d)=\{y\mid\text{dis}(x,y)\le d\}$ 且 $S(x,d)\ne \{1,2,…,n\}$，我们令它被 $d$ 最小的那对 $(x,d)$ 表示。

先假设所有点都关键，那么每个点 $x$ 的 $d$ 是从 $0$ 开始的若干连续整数，考虑如何求它的上界 $d_x$。假定以 $x$ 为根时最深的点深度为 $f_x$，子树内的最深点第二深的深度为 $g_x$。首先，$S(x,d_x)$ 不能覆盖整棵树，所以 $d_x<f_x$；其次，对于 $x$ 的任一个子节点 $y$，$S(x,d_x)$ 不能被 $S(y,d_x-1)$ 覆盖，这要求 $x$ 在 $y$ 的子树外应该存在满足 $\text{dis}(x,z)\ge d_x-1$。我们取 $y$ 为子树最深的点最深的子节点，此时 $\max\{\text{dis}(x,z)\}=g_x$，取到最小，约束最严，所以有 $d_x\le g_x+1$。综上，有 $d_x=\min(f_x-1,g_x+1)$。

接下来有一些点不关键，对于 $x$ 是关键点依然有其 $d$ 范围为 $[0,\min(f_x-1,g_x+1)]$；如果 $x$ 不是关键点，那么 $S(x,d)$ 要是答案求取的集合，就必须完全包括 $x$ 的一个有关键点的子树，所以此时我们求出 $h_x$ 表示以 $x$ 为根时 $x$ 的所有有关键点的子树内最深点深度最小值，其 $d$ 范围为 $[h_x,\min(f_x-1,g_x+1)]$。

最后的答案就是所有点区间长度之和，再 $+1$（全集）。

$f_x,g_x,h_x$ 可以用换根 DP 做。$O(n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll _=2e5+5;
string s;
ll n,w,d[_],f[_],g[_],h[_],z[_];
vector<ll>e[_];
void dfs1(ll x,ll fa){
	if(s[x-1]^48)h[x]=0,z[x]=1;
	else h[x]=1e18;
	for(ll y:e[x])
		if(y!=fa){
			d[y]=d[x]+1;dfs1(y,x);z[x]+=z[y];
			if(f[y]+1>f[x])g[x]=f[x],f[x]=f[y]+1;
			else g[x]=max(g[x],f[y]+1);
			if(z[y])h[x]=min(h[x],f[y]+1);
		}
}
void dfs2(ll x,ll fa){
	w+=max(0ll,min(f[x]-1,g[x]+1)-h[x]+1);
	for(ll y:e[x])
		if(y!=fa){
			ll vl=(f[y]+1==f[x]?g[x]:f[x])+1;
			if(vl>f[y])g[y]=f[y],f[y]=vl;
			else g[y]=max(g[y],vl);
			if(z[1]-z[y])h[y]=min(h[y],vl);
			dfs2(y,x);
		}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(ll i=1,x,y;i<n;i++)cin>>x>>y,e[x].push_back(y),e[y].push_back(x);
	cin>>s;dfs1(1,0);dfs2(1,0);cout<<w+1<<'\n';
	return 0;
} 
```

---

