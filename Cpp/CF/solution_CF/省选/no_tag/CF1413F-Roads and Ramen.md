# Roads and Ramen

## 题目描述

In the Land of Fire there are $ n $ villages and $ n-1 $ bidirectional road, and there is a path between any pair of villages by roads. There are only two types of roads: stone ones and sand ones. Since the Land of Fire is constantly renovating, every morning workers choose a single road and flip its type (so it becomes a stone road if it was a sand road and vice versa). Also everyone here loves ramen, that's why every morning a ramen pavilion is set in the middle of every stone road, and at the end of each day all the pavilions are removed.

For each of the following $ m $ days, after another road is flipped, Naruto and Jiraiya choose a simple path — that is, a route which starts in a village and ends in a (possibly, the same) village, and doesn't contain any road twice. Since Naruto and Jiraiya also love ramen very much, they buy a single cup of ramen on each stone road and one of them eats it. Since they don't want to offend each other, they only choose routes where they can eat equal number of ramen cups. Since they both like traveling, they choose any longest possible path. After every renovation find the maximal possible length of a path (that is, the number of roads in it) they can follow.

## 说明/提示

After the renovation of the $ 3 $ -rd road the longest path consists of the roads $ 1 $ , $ 2 $ and $ 4 $ .

After the renovation of the $ 4 $ -th road one of the longest paths consists of the roads $ 1 $ and $ 2 $ .

After the renovation of the $ 1 $ -st road one of the longest paths consists of the roads $ 1 $ , $ 2 $ and $ 3 $ .

After the renovation of the $ 3 $ -rd road the longest path consists of the roads $ 1 $ , $ 2 $ and $ 4 $ .

After the renovation of the $ 4 $ -rd road one of the longest paths consists of the roads $ 2 $ and $ 4 $ .

## 样例 #1

### 输入

```
5
1 2 0
1 3 0
3 5 0
3 4 0
5
3
4
1
3
4```

### 输出

```
3
2
3
3
2```

# 题解

## 作者：panyf (赞：9)

括号序列做法。

首先转化题意。对于每个结点 $x$ ，记录 $c_x$ 表示 $x$ 到根路径上石子路数量的奇偶性。设 $l$ 为 $x$ 和 $y$ 的 lca，点 $x$ 到 $y$ 路径上石子路数量的奇偶性即为 $(c_x\oplus c_l)\oplus(c_y\oplus c_l)=c_x\oplus c_y$。所以 $x$ 到 $y$ 拉面馆数为偶数当且仅当 $c_x=c_y$。

对于边 $(x,y)$ 的修改操作，不妨设 $y=fa_x$，只需要对 $x$ 子树内的点 $c$ 的值取反即可。

于是本题转化为 [[ZJOI2007]捉迷藏](https://www.luogu.com.cn/problem/P2056) 的子树修改版本.

先讲捉迷藏的做法。

对一棵树 dfs，进入一个点时加入一个左括号和点的编号（加入编号是便于单点修改），离开一个点时加入一个右括号，就是树的括号序列。

对于本题样例，按 1->2->3->4->5 的顺序 dfs，括号序列为 (1(2(3(4)(5))))。

括号序列有一个性质：两个点在树上的距离，等于括号序列上两点之间去掉匹配的括号后的括号数量。例如 2 和 5 之间的序列为 2(3(4)(5，去掉匹配的括号后为 ((，所以距离为 2。

证明：对于两点路径上的点（lca 除外），左右括号中有且只有一个出现在序列中，对答案的贡献总和即为两点距离。对于其他点，一定有 0 个或 2 个括号在序列中出现，对答案没有贡献。

因为有修改操作，考虑用线段树维护括号序列。对于每个区间 $a$ 表示右括号数量，$b$ 表示左括号数量，合并两个区间时将左区间的 $b$ 和右区间的 $a$ 匹配。再维护 $d$ 表示当前区间的最大距离，则 $d=l.a+\operatorname{abs}(l.b-r.a)+r.b$。

然而还要判断点的 $c$ 值是否为 0，所以 $d$ 并不能直接用 $a$ 和 $b$ 求出。再维护四个值 $l1$,$l2$,$r1$,$r2$。$l1$ 表示当前区间合法前缀的 $a+b$ 的最大值（“合法”指前缀的右端点 $c$ 值为 0），$l2$ 表示前缀 $b-a$ 的最大值，$r1$ 表示后缀 $a+b$ 的最大值，$r2$ 表示后缀 $a-b$ 的最大值。于是 $d=\max(\max(l.d,r.d),\max(l.r1+r.l2,l.r2+r.l1))$。$l1$,$l2$,$r1$,$r2$ 的维护也很简单，具体见代码。对于 $c$ 值为 0 的结点，将这四个值初始化为 0，否则初始化为极小值。

接下来是本题的做法。

子树修改可以转化为括号序上的区间修改，线段树区间修改打标记即可。对于线段树上每个结点，再维护将其对应的所有结点的 $c$ 值取反后的状态，修改结点时交换两种状态。查询时对线段树根节点的两种状态取最大值。

时间复杂度 $O(n+m\log n)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+3,M=1e6+3,O=15e5+3,P=42e5+3;
int he[N],x[N],y[N],to[M],ne[M],p[N],ed[N],a[O],id,u,v;
bool c[N],len[M],t[P];
void dfs(int x,int y){//求c数组和括号序列
	++id,a[++id]=x,p[x]=id;
	for(int i=he[x],j;i;i=ne[i])if((j=to[i])!=y)c[j]=c[x]^len[i],dfs(j,x);
	ed[x]=id,a[++id]=-1;
}
struct T{
	int d,a,b,l1,l2,r1,r2;
};
struct S{
	T a,b;
}s[P];
void get(T&k,int x,bool f){//初始化
	k.d=-1,k.l1=k.l2=k.r1=k.r2=-1e9,k.a=k.b=0;
	if(a[x]==0)k.b=1;else if(a[x]==-1)k.a=1;
	else if(c[a[x]]^f)k.l1=k.l2=k.r1=k.r2=k.d=0;
}
void mg(T&k,T&a,T&b){//本题核心部分：区间合并
	if(a.b>b.a)k.a=a.a,k.b=a.b-b.a+b.b;
	else k.a=a.a-a.b+b.a,k.b=b.b;
	k.d=max(max(a.d,b.d),max(a.r2+b.l1,a.r1+b.l2));
	k.l1=max(a.l1,max(b.l1+a.a-a.b,b.l2+a.a+a.b));
	k.l2=max(a.l2,b.l2+a.b-a.a);
	k.r1=max(b.r1,max(a.r1+b.b-b.a,a.r2+b.a+b.b));
	k.r2=max(b.r2,a.r2+b.a-b.b);
}
void build(int k,int l,int r){//建树
	if(l==r)return get(s[k].a,l,1),get(s[k].b,l,0);
	int m=l+r>>1,a=k*2,b=a+1;
	build(a,l,m),build(b,m+1,r),mg(s[k].a,s[a].a,s[b].a),mg(s[k].b,s[a].b,s[b].b);
}
void upd(int k,int l,int r){//区间修改
	if(u<=l&&r<=v)return t[k]^=1,swap(s[k].a,s[k].b);
	int m=l+r>>1,a=k*2,b=a+1;
	if(t[k])swap(s[a].a,s[a].b),swap(s[b].a,s[b].b),t[a]^=1,t[b]^=1,t[k]=0;
	if(u<=m)upd(a,l,m);
	if(m<v)upd(b,m+1,r);
	mg(s[k].a,s[a].a,s[b].a),mg(s[k].b,s[a].b,s[b].b);
}
int main(){
	int n,m,i,j,k,l,t=0;
	scanf("%d",&n);
	for(i=1;i<n;++i){
		scanf("%d%d%d",&j,&k,&l),x[i]=j,y[i]=k;
		ne[++t]=he[j],to[t]=k,len[t]=l,he[j]=t;
		ne[++t]=he[k],to[t]=j,len[t]=l,he[k]=t;
	}
	dfs(1,0),build(1,1,id);
	scanf("%d",&m);
	while(m--){
		scanf("%d",&i);
		if(p[x[i]]<p[y[i]])u=p[y[i]],v=ed[y[i]];else u=p[x[i]],v=ed[x[i]];
		upd(1,1,id),printf("%d\n",max(s[1].a.d,s[1].b.d));
	}
	return 0;
}
```


---

## 作者：tzc_wk (赞：7)

[Codeforces 题目传送门](https://codeforces.com/contest/1413/problem/F) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1413F)

其实是一道还算一般的题罢……大概是最近刷长链剖分，被[某道长链剖分与直径结合的题](https://codeforces.ml/contest/526/problem/G)爆踩之后就点开了这题。

本题的难点就在于看出一个性质：最长路径的其中一个端点一定是直径的某一个端点。

证明：首先我们找出原树的一个直径，如果直径上标记边的个数为偶数那显然这条直径就是最优解，符合题意，否则我们假设我们找出的直径为 $AB$，我们已经找出了一条符合要求的路径 $CD$，下证我们总可以通过调整 $CD$ 的端点，找出一条以 $A$ 或 $B$ 为端点的符合要求的路径，并且长度不劣于路径 $CD$。

分两种情况讨论：

- 若 $CD$ 与 $AB$ 没有公共边，那么我们总可以找到一个点 $E$ 属于路径 $CD$，并且 $E$ 到直径 $AB$ 的最短路径上不包含属于路径 $CD$ 的边，假设直径 $AB$ 上到 $E$ 距离最短的点为 $F$，由 $CD$ 为符合要求的路径可知 $CE,DE$ 两条路径上标记边的奇偶性相同，而由 $AB$ 不符合题意可知 $AF,BF$ 路径上标记边奇偶性不同，从而 $AE,BE$ 奇偶性也不同，根据抽屉原理，在 $AE,BE$ 中总有一者奇偶性与 $CE$ 相同，不妨设为 $AF$，那么考虑路径 $AC$，由于 $AE,CE$ 奇偶性相同，故路径 $AC$ 符合条件，而由 $AB$ 为直径可知 $AE\ge DE$，否则 $BD$ 长度就超过 $AB$ 了，因此我们得到了长度不劣于 $CD$ 的路径 $AB$。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/yq1chiaz.png)

- 若 $CD,AB$ 有公共部分，不妨设公共部分为 $EF$，根据路径 $EF$ 上标记边的奇偶性又可分为两类，若 $EF$ 上有奇数条标记边，由 $AB$ 不合法可知 $AE,BF$ 上标记边奇偶性相同，$CD$ 合法可知 $CE,DF$ 上标记边奇偶性不同，故 $CE,DF$ 中总有一者奇偶性与 $AE$ 相同，若为 $DF$，则 $AF$ 满足条件，否则 $CE$ 与 $AE$ 奇偶性相同，$AE$ 由与 $BF$ 奇偶性相同，故 $BF,CE$ 奇偶性相同，故 $BE$ 满足条件，而根据直径的性质可知 $AF,BE$ 的长度都不小于 $CD$ 的长度，符合题意。若 $EF$ 上有偶数条标记边，仿照之前的推理过程可知 $AF,BE$ 中恰好存在一个符合要求的路径，得证。

  ![](https://cdn.luogu.com.cn/upload/image_hosting/pb0s5jeu.png)

接下来考虑知道这个性质之后怎样解题，我们先两边 DFS 在线性时间内求出树的直径，然后以两个直径分别为根再跑一遍 DFS 求出 DFS 序（这样方便后面修改，可用 DFS 序将子树操作转化为区间操作）并分别建一棵线段树，线段树上每个区间 $[l,r]$ 维护两个值 $mx0,mx1$，分别表示 DFS 序在 $[l,r]$ 中并且到当前根节点路径上有**偶数**条标记边的点中，深度的最大值；以及DFS 序在 $[l,r]$ 中并且到当前根节点路径上有**奇数**条标记边的点中，深度的最大值，修改则相当于对子树打标记，这个可用区间懒标记实现，下推标记时交换节点的 $mx0,mx1$ 即可，查询则直接返回全局最大值，两种情况取个 $\max$ 即可。时间复杂度 $\mathcal O(n\log n)$。

这道题告诉我们，碰到那种求满足什么条件的长度最大的路径时，常可以往树的直径方面想。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
typedef unsigned int u32;
typedef unsigned long long u64;
namespace fastio{
	#define FILE_SIZE 1<<23
	char rbuf[FILE_SIZE],*p1=rbuf,*p2=rbuf,wbuf[FILE_SIZE],*p3=wbuf;
	inline char getc(){return p1==p2&&(p2=(p1=rbuf)+fread(rbuf,1,FILE_SIZE,stdin),p1==p2)?-1:*p1++;}
	inline void putc(char x){(*p3++=x);}
	template<typename T> void read(T &x){
		x=0;char c=getchar();T neg=0;
		while(!isdigit(c)) neg|=!(c^'-'),c=getchar();
		while(isdigit(c)) x=(x<<3)+(x<<1)+(c^48),c=getchar();
		if(neg) x=(~x)+1;
	}
	template<typename T> void recursive_print(T x){if(!x) return;recursive_print(x/10);putc(x%10^48);}
	template<typename T> void print(T x){if(!x) putc('0');if(x<0) putc('-'),x=~x+1;recursive_print(x);}
	void print_final(){fwrite(wbuf,1,p3-wbuf,stdout);}
}
const int MAXN=5e5;
int n,qu,hd[MAXN+5],to[MAXN*2+5],val[MAXN*2+5],nxt[MAXN*2+5],ec=0;
void adde(int u,int v,int w){to[++ec]=v;val[ec]=w;nxt[ec]=hd[u];hd[u]=ec;}
namespace getdia{
	int dep1[MAXN+5],dep2[MAXN+5],rt1=1,rt2=1;
	void dfs1(int x,int f){
		for(int e=hd[x];e;e=nxt[e]){
			int y=to[e];if(y==f) continue;
			dep1[y]=dep1[x]+1;dfs1(y,x);
		}
	}
	void dfs2(int x,int f){
		for(int e=hd[x];e;e=nxt[e]){
			int y=to[e];if(y==f) continue;
			dep2[y]=dep2[x]+1;dfs2(y,x);
		}
	}
	void finddia(){
		dfs1(1,0);for(int i=1;i<=n;i++) if(dep1[i]>dep1[rt1]) rt1=i;
		dfs2(rt1,0);for(int i=1;i<=n;i++) if(dep2[i]>dep2[rt2]) rt2=i;
	}
}
struct solver{
	int rt,dfn[MAXN+5],edt[MAXN+5],tim=0,rid[MAXN+5];
	int par[MAXN+5],dw[MAXN+5],dep[MAXN+5];
	void dfs(int x,int f){
		dfn[x]=++tim;rid[tim]=x;
		for(int e=hd[x];e;e=nxt[e]){
			int y=to[e],z=val[e];if(y==f) continue;
			dw[e+1>>1]=y;par[y]=par[x]^z;dep[y]=dep[x]+1;dfs(y,x);
		} edt[x]=tim;
	}
	struct node{int l,r,mx[2],flp;} s[MAXN*4+5];
	void pushup(int k){
		s[k].mx[0]=max(s[k<<1].mx[0],s[k<<1|1].mx[0]);
		s[k].mx[1]=max(s[k<<1].mx[1],s[k<<1|1].mx[1]);
	}
	void build(int k,int l,int r){
		s[k].l=l;s[k].r=r;if(l==r){s[k].mx[par[rid[l]]]=dep[rid[l]];return;}
		int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);pushup(k);
	}
	void pushdown(int k){
		if(s[k].flp){
			swap(s[k<<1].mx[0],s[k<<1].mx[1]);s[k<<1].flp^=1;
			swap(s[k<<1|1].mx[0],s[k<<1|1].mx[1]);s[k<<1|1].flp^=1;
			s[k].flp=0;
		}
	}
	void modify(int k,int l,int r){
		if(l<=s[k].l&&s[k].r<=r){
			s[k].flp^=1;swap(s[k].mx[0],s[k].mx[1]);return;
		} pushdown(k);int mid=s[k].l+s[k].r>>1;
		if(r<=mid) modify(k<<1,l,r);
		else if(l>mid) modify(k<<1|1,l,r);
		else modify(k<<1,l,mid),modify(k<<1|1,mid+1,r);
		pushup(k);
	}
	int query(){return s[1].mx[0];}
	void init(){dfs(rt,0);build(1,1,n);}
	void toggle(int x){modify(1,dfn[dw[x]],edt[dw[x]]);}
} t[2];
int main(){
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++) scanf("%d%d%d",&u,&v,&w),adde(u,v,w),adde(v,u,w);
	getdia::finddia();t[0].rt=getdia::rt1;t[1].rt=getdia::rt2;t[0].init();t[1].init();
	int qu;scanf("%d",&qu);
	while(qu--){
		int x;scanf("%d",&x);t[0].toggle(x);t[1].toggle(x);
		printf("%d\n",max(t[0].query(),t[1].query()));
	}
	return 0;
}
```



---

## 作者：世凪 (赞：5)

**动态DP做法。**


[更好的阅读体验](https://www.cnblogs.com/HolyK/p/14152777.html)

- 给定一棵 $n$ 个点的无根树，每条边都有标记0或1。现在有 $m$ 次操作，每次操作将第 $id$ 条边的标记异或1。在每次操作后输出当前树上最长的有偶数个1的路径长度。

- $n,m \leq 5 \times 10^5$。

设 $dp[x][0/1]$ 表示 $x$ 向下有偶数/奇数个1的最长路径，$dp[x][2]$ 表示 $x$ 子树内偶数个1的直径。

容易写出转移（$val_y$ 表示 $y$ 的父边的权值）：
$$
\begin{aligned}
dp'[x][0] &= \max\{dp[x][0], dp[y][val_y] + 1\}\\
dp'[x][1] &= \max\{dp[x][1], dp[y][val_y \oplus 1] + 1\}\\
dp'[x][2] &= \max\{dp[x][0] + dp[y][val_y] + 1, dp[x][1] + dp[y][val_y \oplus 1] + 1, dp[x][2],dp[y][2]\}
\end{aligned}
$$
改写成 $x$ 从重儿子 $y$ 转移的矩阵（这里以 $val_y = 0$ 为例）
：
$$
\begin{bmatrix}
dp'[x][0]\\
dp'[x][1]\\
dp'[x][2]\\
0
\end{bmatrix}
=
\begin{bmatrix}
1 & -\infty & -\infty & dp[x][0]\\
-\infty & 1 & -\infty & dp[x][1]\\
dp[x][0] + 1 & dp[x][1] + 1 & 0 & dp[x][2]\\
-\infty & -\infty & -\infty & 0
\end{bmatrix}
\begin{bmatrix}
dp[y][0]\\
dp[y][1]\\
dp[y][2]\\
0
\end{bmatrix}
$$
上面的 $dp[x]$ 是指排除掉 $x$ 重儿子的答案，$dp'[x]$ 是指完整的 $x$ 的答案。

$dp[x]$ 考虑直接用 `std::multiset` 存一下每个节点虚儿子的 $dp[y][0], dp[y][1], dp[y][2]$，取每个的最大和次大值即可快速求出。

复杂度是 $O(4^3 m \log n + m \log^2n)$，能跑过 $5 \times 10^5$ 也是奇迹。

**细节**：在 `multiset` 中删除 $-\infty$ 时不能直接查找对应的值，应该直接删除 `multiset` 中最小的那个值（具体见函数 `void erase(std::multiset<int>&, int)`）。

```cpp
#include <bits/stdc++.h>
#ifdef LOCAL
#define dbg(args...) std::cerr << "\033[32;1m" << #args << " -> ", err(args)
#else
#define dbg(...)
#endif
inline void err() { std::cerr << "\033[0m\n"; }
template<class T, class... U>
inline void err(const T &x, const U &... a) { std::cerr << x << ' '; err(a...); }
template <class T>
inline void readInt(T &w) {
  char c, p = 0;
  while (!isdigit(c = getchar())) p = c == '-';
  for (w = c & 15; isdigit(c = getchar());) w = w * 10 + (c & 15);
  if (p) w = -w;
}
template <class T, class... U>
inline void readInt(T &w, U &... a) { readInt(w), readInt(a...); }
template <class T, class U>
inline bool smin(T &x, const U &y) { return y < x ? x = y, 1 : 0; }
template <class T, class U>
inline bool smax(T &x, const U &y) { return x < y ? x = y, 1 : 0; }

typedef long long LL;
typedef std::pair<int, int> PII;

using Matrix = std::array<std::array<int, 4>, 4>;
Matrix operator*(const Matrix &a, const Matrix &b) {
  Matrix r;
  r[0][0] = std::max({ a[0][0] + b[0][0], a[0][1] + b[1][0], a[0][2] + b[2][0], a[0][3] + b[3][0] });
  r[0][1] = std::max({ a[0][0] + b[0][1], a[0][1] + b[1][1], a[0][2] + b[2][1], a[0][3] + b[3][1] });
  r[0][2] = std::max({ a[0][0] + b[0][2], a[0][1] + b[1][2], a[0][2] + b[2][2], a[0][3] + b[3][2] });
  r[0][3] = std::max({ a[0][0] + b[0][3], a[0][1] + b[1][3], a[0][2] + b[2][3], a[0][3] + b[3][3] });
  r[1][0] = std::max({ a[1][0] + b[0][0], a[1][1] + b[1][0], a[1][2] + b[2][0], a[1][3] + b[3][0] });
  r[1][1] = std::max({ a[1][0] + b[0][1], a[1][1] + b[1][1], a[1][2] + b[2][1], a[1][3] + b[3][1] });
  r[1][2] = std::max({ a[1][0] + b[0][2], a[1][1] + b[1][2], a[1][2] + b[2][2], a[1][3] + b[3][2] });
  r[1][3] = std::max({ a[1][0] + b[0][3], a[1][1] + b[1][3], a[1][2] + b[2][3], a[1][3] + b[3][3] });
  r[2][0] = std::max({ a[2][0] + b[0][0], a[2][1] + b[1][0], a[2][2] + b[2][0], a[2][3] + b[3][0] });
  r[2][1] = std::max({ a[2][0] + b[0][1], a[2][1] + b[1][1], a[2][2] + b[2][1], a[2][3] + b[3][1] });
  r[2][2] = std::max({ a[2][0] + b[0][2], a[2][1] + b[1][2], a[2][2] + b[2][2], a[2][3] + b[3][2] });
  r[2][3] = std::max({ a[2][0] + b[0][3], a[2][1] + b[1][3], a[2][2] + b[2][3], a[2][3] + b[3][3] });
  r[3][0] = std::max({ a[3][0] + b[0][0], a[3][1] + b[1][0], a[3][2] + b[2][0], a[3][3] + b[3][0] });
  r[3][1] = std::max({ a[3][0] + b[0][1], a[3][1] + b[1][1], a[3][2] + b[2][1], a[3][3] + b[3][1] });
  r[3][2] = std::max({ a[3][0] + b[0][2], a[3][1] + b[1][2], a[3][2] + b[2][2], a[3][3] + b[3][2] });
  r[3][3] = std::max({ a[3][0] + b[0][3], a[3][1] + b[1][3], a[3][2] + b[2][3], a[3][3] + b[3][3] });
  return r;
}

constexpr int N(5e5 + 5), INF(1e9);

int n, m, val[N], fa[N], son[N], siz[N];

std::vector<int> g[N];

void dfs1(int x) {
  siz[x] = 1;  
  for (int y : g[x]) {
    if (y == fa[x]) continue;
    fa[y] = x;
    dfs1(y);
    siz[x] += siz[y];
    if (siz[y] > siz[son[x]]) son[x] = y;
  }
}

struct Node {
  Node *ls, *rs, *fa;
  Matrix val, sum;
  inline void pushup() {
    sum = ls ? ls->sum * val : val;
    if (rs) sum = sum * rs->sum;
  }
} t[N];
std::multiset<int> vir[N][3];
void updateVal(int x) {
  auto &v = t[x].val;
  auto p0 = vir[x][0].rbegin(), p1 = vir[x][1].rbegin();
  int k = val[son[x]], m0 = *p0, m1 = *p1;
  v[0][k] = 1, v[0][!k] = v[0][2] = -INF, v[0][3] = m0;
  v[1][!k] = 1, v[1][k] = v[1][2] = -INF, v[1][3] = m1;
  v[2][k] = m0 + 1, v[2][!k] = m1 + 1, v[2][2] = 0;
  v[2][3] = vir[x][0].size() > 1 ? std::max(m0 + *++p0, m1 + *++p1) : 0;
  smax(v[2][3], *vir[x][2].rbegin());
  v[3][0] = v[3][1] = v[3][2] = -INF, v[3][3] = 0;
}
int f[N][3];
void dfs2(int x) {
  f[x][0] = f[x][2] = 0, f[x][1] = -INF;
  vir[x][0].insert(0), vir[x][1].insert(-INF), vir[x][2].insert(0);
  for (int y : g[x]) {
    if (y == fa[x]) continue;
    dfs2(y);
    smax(f[x][2], f[y][2]);
    smax(f[x][2], f[x][0] + f[y][val[y]] + 1);
    smax(f[x][2], f[x][1] + f[y][!val[y]] + 1);
    smax(f[x][0], f[y][val[y]] + 1);
    smax(f[x][1], f[y][!val[y]] + 1);
    if (y == son[x]) continue;
    vir[x][0].insert(f[y][val[y]] + 1);
    vir[x][1].insert(f[y][!val[y]] + 1);
    vir[x][2].insert(f[y][2]);
  }
  updateVal(x);
}
int top[N], s[N], sum[N];
Node* build(int l, int r) {
  if (l == r) return t[s[l]].pushup(), t + s[l];
  int m = l, tot = sum[r] + sum[l - 1];
  while (m < r && sum[m] << 1 < tot) m++;
  Node *o = t + s[m];
  if (l < m) o->ls = build(l, m - 1), o->ls->fa = o;
  if (m < r) o->rs = build(m + 1, r), o->rs->fa = o;
  o->pushup();
  return o;
}
Node *root;
void dfs3(int x, int tp) {
  top[x] = tp;
  if (x == tp) {
    int m = 0;
    for (int i = x; i; i = son[i]) {
      s[++m] = i;
      sum[m] = sum[m - 1] + siz[i] - siz[son[i]];
    }
    if (x > 1)
      build(1, m)->fa = t + fa[x];
    else
      root = build(1, m);
  }
  if (!son[x]) return;
  dfs3(son[x], tp);
  for (int y : g[x]) {
    if (y == fa[x] || y == son[x]) continue;
    dfs3(y, y);
  }
}
inline void erase(std::multiset<int> &s, int x) {
  if (x < 0)
    assert(*s.begin() < 0), s.erase(s.begin());
  else 
    s.erase(s.find(x));
}
void work(int x, int y) {
  assert(fa[y] == x);
  Node *o = t + x;
  int &v = val[y];
  if (son[x] == y) {
    v ^= 1;
  } else {
    Node *p = t + y;
    while (p->fa != o) p = p->fa;
    erase(vir[x][0], p->sum[v][3] + 1);
    erase(vir[x][1], p->sum[!v][3] + 1);
    v ^= 1;
    vir[x][0].insert(p->sum[v][3] + 1);
    vir[x][1].insert(p->sum[!v][3] + 1);
  }
  for (updateVal(x); o->fa; o = o->fa) {
    if (o->fa->ls != o && o->fa->rs != o) {
      x = o->fa - t, y = val[top[o - t]];
      erase(vir[x][0], o->sum[y][3] + 1);
      erase(vir[x][1], o->sum[!y][3] + 1);
      erase(vir[x][2], o->sum[2][3]);
      o->pushup();
      vir[x][0].insert(o->sum[y][3] + 1);
      vir[x][1].insert(o->sum[!y][3] + 1);
      vir[x][2].insert(o->sum[2][3]);
      updateVal(x);
    } else {
      o->pushup();
    }
  }
  o->pushup();
}
struct Edge {
  int x, y, z;
} e[N];
int main() {
  readInt(n);
  for (int i = 1; i < n; i++) {
    auto &[x, y, z] = e[i];
    readInt(x, y, z);
    g[x].push_back(y), g[y].push_back(x);
  }
  dfs1(1);
  for (int i = 1; i < n; i++) {
    auto &[x, y, z] = e[i];
    if (fa[y] != x) std::swap(x, y);
    assert(fa[y] == x);
    val[y] = z;
  }
  
  dfs2(1);
  dfs3(1, 1);
  readInt(m);
  while (m--) {
    int i; readInt(i);
    work(e[i].x, e[i].y);
    printf("%d\n", root->sum[2][3]);
  }
  return 0;
}

```





---

## 作者：xlh_01 (赞：4)

[题目传送门](https://www.luogu.com.cn/problem/CF1413F)

---

### 题意

给出一棵 $n$ 个点的树，每条边上有权值 $0/1$，定义路径的长度为路径上的边的数量。

$q$ 次修改，每次修改会改变一条边的权值，每次修改后回答最长的有偶数个 $1$ 的路径长度。

范围：$2 \le n \le 5 \times 10^{5}$，$1 \le q \le 5 \times 10^{5}$

---

### Solution

先随意定一个根，令点 $x$ 到根路径上的边权异或和为 $s_{x}$，那么一条路径 $\{x,y\}$ 上有偶数个 $1$ 当且仅当 $s_{x}=s_{y}$。

对于直径 $\{p,q\}$，如果 $s_{p}=s_{q}$，显然答案为直径的长度。

否则，对于任意的一个点 $u$，由于 $s_{p} \ne s_{q}$，必有 $s_{u}=s_{p}$ 或 $s_{u}=s_{q}$，所以答案的链的一个端点必然是直径的一个端点。

用线段树维护区间 $0/1$ 反转即可维护最长链，分类讨论直径两端并比较即可。

时间复杂度：$O(n+q\log n)$。


---

**Code**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=5e5+5;
struct E{int to,next;bool val;}edge[N<<1];
int n,q,head[N],cnt=1,dep[N];
inline void add(const int u,const int v,const bool w){
    edge[++cnt].next=head[u];
    edge[cnt].to=v;
    edge[cnt].val=w;
    head[u]=cnt;
}
namespace rw{
    inline int read(){
        int tot=0,t=1;char ch=getchar();
        while(ch<'0'||ch>'9'){if(ch=='-') t=-1;ch=getchar();}
        while(ch>='0'&&ch<='9'){tot=tot*10+ch-'0';ch=getchar();}
        return tot*t;
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        static int sta[35];int top=0;
        do{sta[top++]=x%10,x/=10;}while(x);
        while(top) putchar(sta[--top]+'0');
    }
    inline void print(const int x,const char ch){return (write(x),putchar(ch)),void(0);}
}using namespace rw;
inline void dfs(const int u,const int fa){
    dep[u]=dep[fa]+1;
    for(int i=head[u];i;i=edge[i].next){
        int v=edge[i].to;
        if(fa==v) continue;
        dfs(v,u);
    }
}
struct Tree{
    int inx[N],in[N],out[N],dfn[N],dep[N],num;bool val[N];
    inline void dfs(const int u,const int fa){
        dep[u]=dep[fa]+1;dfn[++num]=u;in[u]=num;
        for(int i=head[u];i;i=edge[i].next){
            int v=edge[i].to;bool w=edge[i].val;
            if(fa==v){inx[i>>1]=u;continue;}
            val[v]=(val[u]^w);dfs(v,u);
        }
        out[u]=num;
    }
    struct node{int l,r,maxn[2];bool tag;}tree[N<<2];
    inline void pushup(const int p){
        tree[p].maxn[0]=max(tree[p<<1].maxn[0],tree[p<<1|1].maxn[0]);
        tree[p].maxn[1]=max(tree[p<<1].maxn[1],tree[p<<1|1].maxn[1]);
    }
    inline void swp(const int p){
        tree[p].tag^=1;
        swap(tree[p].maxn[0],tree[p].maxn[1]);
    }
    inline void pushdown(const int p){
        if(tree[p].tag){
            swp(p<<1),swp(p<<1|1);
            tree[p].tag=0;
        }
    }
    inline void build(const int p,const int l,const int r){
        tree[p].l=l,tree[p].r=r;
        if(l==r) return tree[p].maxn[val[dfn[l]]]=dep[dfn[l]],void(0);
        int mid=(l+r)>>1;
        build(p<<1,l,mid);
        build(p<<1|1,mid+1,r);
        pushup(p);
    }
    inline void upd(const int p,const int l,const int r){
        if(r<tree[p].l||tree[p].r<l) return;
        if(l<=tree[p].l&&tree[p].r<=r) return swp(p),void(0);
        pushdown(p);
        upd(p<<1,l,r);
        upd(p<<1|1,l,r);
        pushup(p);
    }
    inline int ask(){return tree[1].maxn[0];}
    inline void init(const int root){dfs(root,0);build(1,1,n);}
    inline void update(const int x){upd(1,in[inx[x]],out[inx[x]]);}
}T1,T2;
inline void ask(const int x){
    T1.update(x),T2.update(x);
    print(max(T1.ask(),T2.ask())-1,'\n');
}
signed main(){
    n=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read(),w=read();
        add(u,v,w),add(v,u,w);
    }int tmp=1;
    dfs(tmp,0);for(int i=1;i<=n;i++) if(dep[i]>dep[tmp]) tmp=i;T1.init(tmp);
    dfs(tmp,0);for(int i=1;i<=n;i++) if(dep[i]>dep[tmp]) tmp=i;T2.init(tmp);
    q=read();while(q--) ask(read());
    return 0;
}
```


---

---

## 作者：hegm (赞：2)

### [Roads and Ramen](https://www.luogu.com.cn/problem/CF1413F)

和捉迷藏非常像。

考虑将点按照到根的路径上标记数量的奇偶性分类。

容易发现，在同一类的点之间是合法的。

现在需要证明一些奇怪的性质：

假如当前我们知道了一个集合的最远点对 $x,y$，那么我们考虑新加入一个点 $k$。

首先我们要在当前集合中选出一个点 $p$，使得 $p$ 距离 $k$ 最远，然后更新最远点对。

>性质：$p$ 是 $x$ 或者 $y$，不可能有其他选择。

尝试证明，我们考虑分类讨论。

1. $k$ 在 $x\to y$ 的路径上

这个很好想，必然 $p=x/y$。

![](https://cdn.luogu.com.cn/upload/image_hosting/ia4bki2m.png)

如果存在一个点 $p(p\ne x/y)$，使得 $k\to p$ 的距离最大，那么我们就可以使用黄色的路径替换掉 $x\to k\to y$ 的 $k\to y$ 这一段，获得更远的点对，可以推翻 $x,y$ 为最远点对，所以不存在这样的点 $p$。

2. $k$ 不在 $x\to y$ 的路径上

我们还是假设 $p$ 不是 $x/y$ 那么 $k\to p$ 的路径可以分为两种情况：

- $k\to p$ 的路径经过了 $x\to y$ 的路径

![](https://cdn.luogu.com.cn/upload/image_hosting/gc8l8pos.png)

容易发现，和之前差别不大，既然 $y$ 不是 $k$ 最远点就说明 $w_{s,y}<w_{s,p}$，但是这样又会推翻我们的 $x,y$ 为最远点对的假设，所以这样的 $p$ 不存在。

- $k\to p$ 的路径不经过 $x\to y$ 的路径

![](https://cdn.luogu.com.cn/upload/image_hosting/0e90p3qk.png)

那么如果 $k$ 距离 $x\to y$ 的路径比较近，就会成为图上的情况，我们知道红色边权大于 $s\to y+s\to k$ 的边权，既然如此，我们红色边权加上黄色边权肯定比 $y\to s$ 更大，那么我们的 $x,y$ 最远点对又被推翻了。

而如果 $p$ 距离 $s$ 更近，那么我们会发现，我们 $k\to p\to y$ 的路径多了一条边，而边权又是正的，那么加上肯定不亏，所以又能推翻上述假设。

综上我们推出了：

>$p$ 是 $x$ 或者 $y$，不可能有其他选择。

那么加入一个点就简单了，我们只需要求出它到当前最远点对的距离即可，复杂度是 $\log n$ 的。

现在我们考虑每次不是加入一个点，而是加入一个集合，换句话说，合并两个集合。

将 $B$ 集合加入到 $A$ 集合，我们先考虑暴力的一个一个往里面加，那么我们会枚举 $B$ 中的每一个点，我们设 $ans_i$ 表示 $B_i$ 和 $A$ 中的最远距离点的距离。那么我们每个 $B_i$ 都要和 $A_x,A_y$ 计算距离得到 $ans_i$。

然后在这些 $ans_i$ 中，再次取最大值。

这样很麻烦，我们不妨换一个角度，我们计算出所有 $B_i$ 到 $A_x$ 的距离取最大值记作 $ansx$，同理也可以得到 $ansy$，我们考虑 $ansx$ 和 $ansy$ 的值，是不是就相当于我将 $A_x$ 加入 $B$ 中的最远点对和将 $A_y$ 加入 $B$ 中的最远点对，又因为性质 $1$，最远点 $p=B_x/B_y$，那么性质就显而易见了，将两个区间合并，新的最远点对只会在两个区间的最远点对中产生！

这其实就是一个经典结论，可以优秀的用来维护直径（边权全为正数）。

那么转化到这道题目，我可以使用线段树维护区间信息，表示 $l\sim r$ 这个区间的直径，合并区间就如同上面合并集合一样。

然后这道题有一个特点就是分为两个大集合，那么分开维护就可以，更改一条边的标记就等同于子树修改，修改的内容是交换奇集合的内容和偶集合的内容，并且打上懒标记日后下传即可。

这道题很卡时间，可以用 $O(1) \text{lca}$ 来优化，复杂度为 $n\log n$。

## CODE

```cpp
#include<bits/stdc++.h>
#define N 500005
#define ls (now<<1)
#define rs (now<<1|1)
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int n;
struct fig
{
	int to,next,w,id;
}k[N*2];
int head[N],tot,dep[N],awa,cnt,id[N],st[21][N*2],dfn[N],siz[N],g[N],e[N],pl[N];
void add(int from,int to,int w,int id)
{
	k[++tot].to=to;
	k[tot].w=w;
	k[tot].id=id;
	k[tot].next=head[from];
	head[from]=tot;
}
void dfs(int now,int f)
{
	dep[now]=dep[f]+1;st[0][++cnt]=now;
	dfn[now]=++awa;id[now]=cnt;siz[now]=1;
	pl[awa]=now;
	for(int i=head[now];i;i=k[i].next)
	{
		if(k[i].to==f)continue;
		st[0][++cnt]=now;
		e[k[i].id]=k[i].to;
		g[k[i].to]=(g[now]^k[i].w);
		dfs(k[i].to,now);
		siz[now]+=siz[k[i].to];
	}
}
int lca(int a,int b)
{
	if(id[a]>id[b])swap(a,b);
	int len=__lg(id[b]-id[a]+1),x,y;
	x=st[len][id[a]];
	y=st[len][id[b]-(1<<len)+1];
	if(dep[x]<dep[y])return x;
	return y;
}
int get(int a,int b)
{
	if(!a||!b)return 0;
	return dep[a]+dep[b]-2*dep[lca(a,b)];
}
struct line
{
	int u,v,w;
}tr[2][N*4];int lz[N*4];
line merge(line x,line y)
{
	line s;
	if(x.u==0)return y;
	if(y.u==0)return x; 
	if(x.w<y.w)s=y;
	else s=x;
	int p1=get(x.u,y.u),p2=get(x.u,y.v),p3=get(x.v,y.u),p4=get(x.v,y.v);
	if(p1>s.w)s={x.u,y.u,p1};
	if(p2>s.w)s={x.u,y.v,p2};
	if(p3>s.w)s={x.v,y.u,p3};
	if(p4>s.w)s={x.v,y.v,p4};
	return s;
}
void up(int now)
{
	tr[0][now]=merge(tr[0][ls],tr[0][rs]);
	tr[1][now]=merge(tr[1][ls],tr[1][rs]);
}
void down(int now)
{
	if(lz[now])
	{
		swap(tr[0][ls],tr[1][ls]);
		swap(tr[0][rs],tr[1][rs]);
		lz[ls]^=lz[now];
		lz[rs]^=lz[now];
		lz[now]=0;
	}
}
void midy(int now,int l,int r,int ql,int qr)
{
	if(l>=ql&&r<=qr)
	{
		lz[now]^=1;
		swap(tr[0][now],tr[1][now]);
		return ;
	}
	int mid=(l+r)>>1;down(now);
	if(mid>=ql)midy(ls,l,mid,ql,qr);
	if(mid<qr)midy(rs,mid+1,r,ql,qr);
	up(now);
}
void build(int now,int l,int r)
{
	if(l==r)
	{
		tr[g[pl[l]]][now].u=pl[l];
		tr[g[pl[l]]][now].v=pl[l];
		tr[g[pl[l]]][now].w=0;
		return ;
	}
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
	up(now);
}
signed main()
{
	n=read();
	for(int i=1,u,v,w;i<n;i++)
	{
		u=read();v=read();w=read();
		add(u,v,w,i);add(v,u,w,i);
	}
	dfs(1,0);dep[0]=1000000000;
	for(int i=1;i<=20;i++)
	{
		for(int j=1;j<=cnt;j++)
		{
			if(dep[st[i-1][j]]<dep[st[i-1][j+(1<<(i-1))]])st[i][j]=st[i-1][j];
			else st[i][j]=st[i-1][j+(1<<(i-1))];
		}
	}
	build(1,1,n);
	int q=read(),x;
	while(q--)
	{
		x=e[read()];
		midy(1,1,n,dfn[x],dfn[x]+siz[x]-1);
		cout<<max(tr[1][1].w,tr[0][1].w)<<"\n";
	}
	return 0;
}

```

---

## 作者：_Sein (赞：2)

[Roads and Ramen](https://codeforces.com/contest/1434/problem/D)

题目要我们找一条路径，拉面馆数为偶数，且长度最长。

这道题要猜一个性质，最长路径的其中一个端点一定是直径的某一个端点。

证明见下:

![](https://lb2003.top/usr/uploads/2020/10/1079144940.png)

我们分两种情况进行讨论，一种与直径无交，另一种与直径有交。

无交的情况:

如图，假设路径为 $JL$ ，那么 $JC,CL$ 路径的拉面馆数的奇偶性应该是一样的。

直径 $AF$ 不是一条合法路径，从这个我们可以得知，$AC,CF$ 的奇偶性应该是不一样的。

因此 $AC,CF$ 至少有一条与 $JC$ 的奇偶性相同，根据直径的性质，那么 $AC,CF\ge JC$ ，进而说明从直径某一端点出发，也能找到最优路径。

因此路径的其中一个端点可以被替换成直径的其中一个端点。

有交的情况：

如图，假设路径为 $NL$ ，那么 $NC,LC$ 奇偶性相同，$LD,ND$ 奇偶性相同。

如果 $AC$ 和 $CL$ 奇偶性不同，则 $CF$ 与 $CL$ 奇偶性相同，成立。

如果相同，也成立。

故命题成立。

之后就是线段树维护一个深度以及奇偶性的问题了。

 ```cpp
vector<pii> e[N]; int fa[N], dep[N];
int Q[N], ans[N]; vector<pii> G; int m, n;
 
struct state {
	int f[N], dfn[N], cnt, yss[N], ed[N];
	void dfs(int x) {
		dfn[x] = ++cnt; yss[cnt] = x;
		for (pii k : e[x]) {
			if (k.fi == fa[x]) continue; int y = k.fi;
			fa[y] = x; dep[y] = dep[x] + 1; f[y] = (f[x] + k.se) & 1;
			dfs(y); 		
		} ed[x] = cnt;
	}
	struct Seg {
		int w[2]; bool rv;
		Seg(int a = 0, int b = 0) {w[0] = a, w[1] = b, rv = 0;}  
	} t[N << 2];
	
	Seg friend operator + (const Seg &a, const Seg &b) {
		return Seg(max(a.w[0], b.w[0]), max(a.w[1], b.w[1]));
	}
	
	void rev(int p) {
		swap(t[p].w[0], t[p].w[1]); t[p].rv ^= 1;
	}
	
	void pushdown(int p) {
		if (t[p].rv) rev(p << 1), rev(p << 1 | 1), t[p].rv = 0;
	}
 
	void build(int p, int l, int r) {
		if (l == r) {
			l = yss[l]; t[p].w[f[l]] = dep[l]; return ;
		} int mid = l + r >> 1;
		build(p << 1, l, mid); build(p << 1 | 1, mid + 1, r);
		t[p] = t[p << 1] + t[p << 1 | 1];
	}
	
	void modify(int p, int l, int r, int L, int R) {
		if (L <= l && R >= r) return rev(p); 
		int mid = l + r >> 1; pushdown(p);
		if (L <= mid) modify(p << 1, l, mid, L, R);
		if (R > mid) modify(p << 1 | 1, mid + 1, r, L, R);
		t[p] = t[p << 1] + t[p << 1 | 1];
	}
	
	void solve(int rt) {
		fa[rt] = dep[rt] = cnt = 0; dfs(rt);
		build(1, 1, n);
		for (int i = 1; i <= m; ++i) {
			int x = G[Q[i] - 1].fi, y = G[Q[i] - 1].se;
			if (fa[x] == y) swap(x, y);
			modify(1, 1, n, dfn[y], ed[y]);
			ans[i] = max(ans[i], t[1].w[0]);
		} 
	}
} A, B;
 
int rt;
 
void dfs(int x) {
	for (pii k : e[x]) {
		if (k.fi == fa[x]) continue; int y = k.fi;
		fa[y] = x; dep[y] = dep[x] + 1; dfs(y);
	} if (!rt || dep[x] > dep[rt]) rt = x;
} 
 
void solve() {
    qr(n);
    for (int i = 1; i < n; ++i) {
    	int x, y, z; qr(x), qr(y), qr(z);
    	e[x].emplace_back(y, z); e[y].emplace_back(x, z);
    	G.emplace_back(x, y);
    } 
	qr(m);
	for (int i = 1; i <= m; ++i) qr(Q[i]); 
	rt = 0; fa[1] = dep[1] = 0; dfs(1); 
	int r1, r2; r1 = rt; 
	rt = 0; fa[r1] = dep[r1] = 0; dfs(r1); r2 = rt;
	A.solve(r1); 
	B.solve(r2); 
	for (int i = 1; i <= m; ++i) pr2(ans[i]);
}
 ```









---

## 作者：封禁用户 (赞：1)

题意：

给定一个树，边带权 $0,1$，支持单边翻转。每次查询长度为 $0$ 的链的最大值。

解决：

首先我们发现了一个性质，答案路径必然经过直径一端。感性理解的话就是从直径不断删一端的边。
然后就做完了，可以考虑维护单点的深度，然后支持区间乘上 $-1$，查询区间最大值。

```cpp
#include<bits/stdc++.h>
using namespace std;typedef long long ll;
template<typename T>inline void read(T &x)
{
	x=0;char c=getchar(),f=0;
	for(;c<48||c>57;c=getchar()) if(!(c^45)) f=1;
	for(;c>=48&&c<=57;c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	f?x=-x:x;
}
template<typename T,typename...L>inline void read(T &x,L&...l) {read(x),read(l...);}//}}}
const int N=500005;struct edge{int to,w,nxt;}e[N<<1];int et=1,head[N],id[N],Ca,q[N];
int n,d[N],ds[N],sz[N],dfn[N],dt,nfd[N],rs[N];struct segm{int mx,mn,fg;}T[N<<2];
inline void adde(int x,int y,int w) {e[++et]=(edge){y,w,head[x]},head[x]=et;}
inline void allc(int x) {swap(T[x].mx,T[x].mn),T[x].mx=-T[x].mx,T[x].mn=-T[x].mn,T[x].fg^=1;}
inline void pushdw(int x) {if(T[x].fg) allc(x<<1),allc(x<<1|1),T[x].fg=0;}
inline void pushup(int x) {T[x].mx=max(T[x<<1].mx,T[x<<1|1].mx),T[x].mn=min(T[x<<1].mn,T[x<<1|1].mn);}
inline void build(int x,int l,int r)
{
	T[x].fg=0;if(l==r) return T[x].mx=T[x].mn=d[nfd[l]],void();
	build(x<<1,l,(l+r)>>1),build(x<<1|1,((l+r)>>1)+1,r),pushup(x);
}
inline void modif(int x,int l,int r,int dl,int dr)
{
	if(l>dr||dl>r) return;else if(dl<=l&&r<=dr) return allc(x);else pushdw(x);
	modif(x<<1,l,(l+r)>>1,dl,dr),modif(x<<1|1,((l+r)>>1)+1,r,dl,dr),pushup(x);
}
inline void dfs0(int x,int fa)
{
	d[x]=d[fa]+1;for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa) dfs0(e[i].to,x);
}
inline void dfs1(int x,int fa)
{
	sz[x]=1,dfn[x]=++dt,nfd[dt]=x;for(int i=head[x];i;i=e[i].nxt) if(e[i].to!=fa)
		ds[e[i].to]=ds[x]+e[i].w,dfs1(e[i].to,x),sz[x]+=sz[e[i].to],id[i>>1]=e[i].to;
}
inline void chg(int x) {x=id[x],modif(1,1,n,dfn[x],dfn[x]+sz[x]-1);}
inline void solve()
{
	int rt=0;for(int i=1;i<=n;i++) if(d[rt]<=d[i]) rt=i;
	dt=0,d[0]=-1,dfs0(rt,0),dfs1(rt,0),build(1,1,n);
	for(int i=1;i<n;i++) if(e[i<<1].w==1) chg(i);
	for(int i=1;i<=Ca;i++) chg(q[i]),rs[i]=max(rs[i],T[1].mx);
}
int main()
{
	read(n);for(int i=1,x,y,w;i<n;i++) read(x,y,w),adde(x,y,w),adde(y,x,w);
	dfs0(1,0);read(Ca);for(int i=1;i<=Ca;i++) read(q[i]);
	solve(),solve();for(int i=1;i<=Ca;i++) printf("%d\n",rs[i]);
	return 0;
}

``````

---

## 作者：lyhqwq (赞：0)

# Solution

遇到与树上最长路径有关的题，考虑与树的直径的关系。

结论：答案的链一定和直径共用一个端点。

证明：首先考虑答案与直径没有交点的情况，其他情况同理。

如果答案和直径没有交点，那么一定通过一条链相连，答案和直径分别被链分为两部分，直径的每一部分长度大于相应的答案的部分的长度。答案的两部分同奇偶，直径的两部分异奇偶。所以一定可一找到一条有直径的一部分和答案的一部分组成的链满足要求，且长度更长。

我们两遍 dfs 找出直径的两个端点，分别作为根建树，记录点到根的路径异或，修改一条边即将子树内的点的异或值取反，查询异或值为 $0$ 的点的最大深度，线段树板子。

# Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=500005;
struct edge{
    int v,w,nxt;
}edge[N<<1];
int head[N],cnt;
int n,m,r[2];
int u[N],v[N];
int d[N];
int dfn[N][2],tot[2],rnk[N][2],siz[N][2],dep[N][2],sum[N][2];
void addedge(int u,int v,int w){
    edge[++cnt].v=v,edge[cnt].w=w,edge[cnt].nxt=head[u],head[u]=cnt;
}
void dfs1(int u,int fa,int op){
    for(int i=head[u];i;i=edge[i].nxt){
        int v=edge[i].v;
        if(v==fa) continue;
        d[v]=d[u]+1;
        dfs1(v,u,op);
        if(d[v]>d[r[op]]) r[op]=v;
    }
}
void dfs2(int u,int fa,int op){
    siz[u][op]=1;
    dfn[u][op]=++tot[op],rnk[tot[op]][op]=u;
    for(int i=head[u];i;i=edge[i].nxt){
        int v=edge[i].v,w=edge[i].w;
        if(v==fa) continue;
        sum[v][op]=sum[u][op]^w;
        dep[v][op]=dep[u][op]+1;
        dfs2(v,u,op);
        siz[u][op]+=siz[v][op];
    }
}
namespace SgT{
    struct node{
        int mx[2];
        int lazy;
    }tree[N<<2][2];
    int lc(int x){return x<<1;}
    int rc(int x){return x<<1|1;}
    void push_up(int rt,int op){
        for(int i=0;i<=1;i++){
            tree[rt][op].mx[i]=max(tree[lc(rt)][op].mx[i],tree[rc(rt)][op].mx[i]);
        }
    }
    void push_down(int rt,int l,int r,int op){
        if(tree[rt][op].lazy){
            tree[lc(rt)][op].lazy^=tree[rt][op].lazy;
            tree[rc(rt)][op].lazy^=tree[rt][op].lazy;
            swap(tree[lc(rt)][op].mx[0],tree[lc(rt)][op].mx[1]);
            swap(tree[rc(rt)][op].mx[0],tree[rc(rt)][op].mx[1]);
        }
        tree[rt][op].lazy=0;
    }
    void build(int rt,int l,int r,int op){
        if(l==r){
            tree[rt][op].mx[sum[rnk[l][op]][op]]=dep[rnk[l][op]][op];
            return;
        }
        int mid=(l+r)>>1;
        build(lc(rt),l,mid,op);
        build(rc(rt),mid+1,r,op);
        push_up(rt,op);
    }
    void update(int rt,int l,int r,int L,int R,int op){
        if(L<=l&&r<=R){
            tree[rt][op].lazy^=1;
            swap(tree[rt][op].mx[0],tree[rt][op].mx[1]);
            return;
        }
        push_down(rt,l,r,op);
        int mid=(l+r)>>1;
        if(L<=mid) update(lc(rt),l,mid,L,R,op);
        if(R>mid) update(rc(rt),mid+1,r,L,R,op);
        push_up(rt,op);
    }
}
using namespace SgT;
int solve(int u,int v,int op){
    if(dep[u][op]>dep[v][op]) swap(u,v);
    update(1,1,n,dfn[v][op],dfn[v][op]+siz[v][op]-1,op);
    return tree[1][op].mx[0];
}
int main(){
    scanf("%d",&n);
    for(int i=1,w;i<n;i++){
        scanf("%d%d%d",&u[i],&v[i],&w);
        addedge(u[i],v[i],w);
        addedge(v[i],u[i],w);
    }
    dfs1(1,0,0),d[r[0]]=0;
    dfs1(r[0],0,1);
    dfs2(r[0],0,0),dfs2(r[1],0,1);
    build(1,1,n,0),build(1,1,n,1);
    scanf("%d",&m);
    while(m--){
        int id;
        scanf("%d",&id);
        printf("%d\n",max(solve(u[id],v[id],0),solve(u[id],v[id],1)));
    }
    return 0;
}

```

---

