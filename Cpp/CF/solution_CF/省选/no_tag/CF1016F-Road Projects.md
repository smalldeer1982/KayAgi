# Road Projects

## 题目描述

Berland 王国有 $n$ 座城市，有些城市间由双向道路连接，每条边不会出现超过一次。且每一条边都有它自己的长度。城市从 $1$ 到 $n$ 编号。

城市 $u$ 与 $v$ 间的旅行时间为 从 $u$ 到 $v$ 的最短路径上的边的边权之和。

在 Berland 王国的两座最重要的城市是 $1$ 与 $n$ 。

Berland 王国交通运输部决定修建一条新道路，来分担最重要的城市间的交通压力。然而，很多人已习惯了他们间的现在的旅行时间，因此新建的道路不应造成较大的影响。

新的道路应该建在 $u$ 与 $v$ 间，其中 $u≠v$ 且当前 $u$ 与 $v$ 间不存在道路。

他们提出了 $m$ 种可能的工程。每项工程都含有新建道路的长度 $x$ 。

Polycarp 在 Berland 王国交通运输部担任首席分析师，处理这 $m $ 项工程是他的工作。对于第 $i$ 项工程，他被要求选择城市 $u$ 和 $v$ 去建造这条道路使得 最重要的城市间 的旅行时间尽可能长。

不幸的是，Polycarp 不是程序员，世界上没有分析师能够仅使用笔和纸来处理所有项目。

因此，他要求你帮助他对于每个项目计算最重要的城市之间的最大可能的旅行时间。注意，对于不同的项目， $u$ 和 $v$ 的选择可以不同。

## 样例 #1

### 输入

```
7 2
1 2 18
2 3 22
3 4 24
4 7 24
2 6 4
3 5 12
1
100
```

### 输出

```
83
88
```

# 题解

## 作者：UltiMadow (赞：11)

挺不错的一个树形 dp 题

首先把 $1\to n$ 的链提取出来，显然这一条链上会挂很多子树

考虑链上的一个节点 $u$ 以及它的子树，显然如果这个子树内有大于等于 3 个节点（包括 $u$）则在这个子树内一定能选出两个没有直接连边的点，每次查询只要连这两个点即可，于是答案就是原树上 $1\to n$ 的最短路

考虑不存在这种子树的情况

记 $dis_u$ 为 **链上节点 $u$** 距离一号节点的距离，$f_u$ 为 $u$ 子树内距离 $u$ 最远的那个点离 $u$ 的距离

假设当前选到了一个点 $i$，我们只要找出一个 $j<i$，使得 $f_j+f_i+dis_j+(dis_n+dis_i)+x$ 最大即可

不看所有与 $j$ 无关的量，于是发现只要维护 $f_j+dis_j$ 的最大值，也就是维护一个前缀最大值，用单调栈扫一遍即可

这里有一个细节，就是考虑 $i$ 的时候，如果 $i$ 相邻的点 $j$ 是最优决策点，则需要特判 $i$ 和 $j$ 中是否有一个的子树大小大于 1，否则只能从 $i$ 连到 $j$，为非法情况

时间复杂度 $\mathcal O(n)$，感觉代码实现比其他题解清楚一点？

code:
```cpp
#include<bits/stdc++.h>
#define MAXN 300010
#define int long long
using namespace std;
int n,m;
struct Node{int to,nxt,val;}Edge[MAXN<<1];
int Head[MAXN],cnt_Edge;
void Add_Edge(int u,int v,int w){
	Edge[++cnt_Edge]=(Node){v,Head[u],w};
	Head[u]=cnt_Edge;
}
int st[MAXN],val[MAXN],tp,vis[MAXN];
int dis[MAXN],f[MAXN],sz[MAXN];
int q[MAXN],r,ans,tag;
bool dfs(int u,int fa){
	if(u==n)return true;
	for(int i=Head[u];i;i=Edge[i].nxt){
		int v=Edge[i].to,w=Edge[i].val;
		if(v==fa)continue;
		st[++tp]=v;val[tp]=w;vis[v]=true;
		if(dfs(v,u))return true;
		tp--;vis[v]=false;
	}return false;
}//用栈维护到根的链
void dp(int u,int fa){
	sz[u]=1;
	for(int i=Head[u];i;i=Edge[i].nxt){
		int v=Edge[i].to,w=Edge[i].val;
		if(v==fa||vis[v])continue;dp(v,u);
		sz[u]+=sz[v];f[u]=max(f[u],f[v]+w);
	}
}
signed main(){
	scanf("%lld%lld",&n,&m);ans=0xcfcfcfcfcfcfcfcf;
	for(int i=1;i<n;i++){
		int u,v,w;scanf("%lld%lld%lld",&u,&v,&w);
		Add_Edge(u,v,w);Add_Edge(v,u,w);
	}st[tp=1]=1;vis[1]=true;dfs(1,0);
	for(int i=1;i<=tp;i++)dis[i]=dis[i-1]+val[i];
	for(int i=1;i<=tp;i++)dp(st[i],0),tag|=(sz[st[i]]>2);
	if(sz[st[1]]>1||sz[st[2]]>1)ans=max(ans,f[st[1]]+f[st[2]]+dis[tp]-dis[2]);
	q[r=1]=1;//单调栈
	for(int i=3;i<=tp;i++){
		ans=max(ans,f[st[i]]+f[st[q[1]]]+dis[q[1]]+dis[tp]-dis[i]);
		if(sz[st[i]]>1||sz[st[i-1]]>1)ans=max(ans,f[st[i]]+f[st[i-1]]+dis[tp]-dis[i]+dis[i-1]);//注意特判
		while(r&&f[st[i-1]]+dis[i-1]>=f[st[q[r]]]+dis[q[r]])r--;
		q[++r]=i-1;
	}
	while(m--){
		int x;scanf("%lld",&x);
		printf("%lld\n",tag?dis[tp]:min(dis[tp],ans+x));
	}
	return 0;
}
```

---

## 作者：yzc2005 (赞：6)

[题目链接qwq](https://www.luogu.com.cn/problem/CF1016F)
# 一、题意
给定一棵树，有 $q$ 次询问，每次询问：给定一条长度为 $l$ 的边，任选两个**没有边直接相连的点**接上这条边， 最大化连边后 $mindis(1, n)$ 。
# 二、题解
考虑将树拆成这样的形态：

![](https://cdn.luogu.com.cn/upload/image_hosting/6759v92s.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们把这种树的形态称作 `链树` （我自己瞎起的），即以一条主干为线将以整棵树串起来。我们把$path(1, n)$称作 `main` ，把 `main` 上的点称为 `主干点` ，把以主干点 $u$ 为根分叉开的子树称作 `branch(u)`。

如果存在一个主干点 $u$  ，使得 $size(branch(u))>=3$，则 $branch(u)$ 内必有一对点 $u, v$ 间没有连边，因为 $C^n_2-(n-1)=\frac{n*(n-1)}{2}-n+1=\frac{n(n-3)}{2}+1$ 。显然， $n >= 3$ 时为正数。对于任何询问直接将两点连起来即可。故直接输出 $q$ 次原树的 $mindis(1,n)$ 即可。

否则，每个主干点必定只有一个孩子。然后问题就被简化了许多，把 $main$ 上的点扫一遍，维护一下前缀最大值即可。注意：两个已经相连的边不能再相连！坑点很多，具体请康代码。
# 三、代码

```
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define rg register
#define fu(i, a, b) for(rg int i = (a), I = (b) + 1; i < I; ++i)
#define fd(i, a, b) for(rg int i = (a), I = (b) - 1; i > i; --i)
#define go(u) for(rg int o = head[u], v = to[o], w = val[o]; o; o = nxt[o], v = to[o], w = val[o])
template <class T> inline void read(T &x) {
	x = 0; char ch = getchar();
	while(ch < 48 || ch > 57) ch = getchar();
	while(ch >= 48 && ch <= 57) x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar();
}
template <class T> inline void ckmax(T &a, T b) {a = max(a, b);}
template <class T> inline void ckmin(T &a, T b) {a = min(a, b);}

const int N = 3e5 + 5;
const ll inf = 1e18;
int n, q, to[N << 1], nxt[N << 1], val[N << 1], head[N], fa[N], cnt, a[N];
bool vis[N], flg, sz;
ll dis[N], l;
/*
answer = min(dis[n], dis[n] - s[y] + s[x] + a[x] + a[y] + l =)
So our mission is maximizing f(x, y) (x < y) = (a[x] + s[x]) + (a[y] - s[y]) = f(x) + g(y);
*/

inline void add(int u, int v, int w) {
	to[++cnt] = v, val[cnt] = w, nxt[cnt] = head[u];
	head[u] = cnt; 
} 

void dfs(int u) {
	go(u) 
		if(v != fa[u]) {
			fa[v] = u;
			dis[v] = dis[u] + w;
			dfs(v); 
	}
}

inline void getpath() {
	int u = n;
	while(u) vis[u] = 1, u = fa[u];
}

void getsub(int u, int fa) {
	go(u) 
		if(!vis[v] && v != fa) {
			if(sz) {
				fu(i, 1, q) printf("%lld\n", dis[n]);
				exit(0);
			}
			sz = 1;
			a[u] = w;
			getsub(v, u);
	} 
}

inline void work() {
	int u = n;
	ll mx1 = -inf, mx2 = -inf, lst = -inf, ans = -inf;
	while(u) {
		if(a[u]) {
			ckmax(ans, a[u] + dis[u] + max(mx1, mx2));
			ckmax(mx1, a[u] - dis[u]);
		}
		else {
			ckmax(ans, a[u] + dis[u] + max(mx1, lst));
			lst = mx2, ckmax(mx2, a[u] - dis[u]);
		}
		u = fa[u];
	}
	fu(i, 1, q) read(l), printf("%lld\n", min(dis[n], dis[n] + ans + l));
}

int main() {
	read(n), read(q);
	for(int i = 1, u, v, w; i < n; ++i) {
		read(u), read(v), read(w);
		add(u, v, w), add(v, u, w);
	}
	dfs(1), getpath();
	fu(i, 1, n) if(vis[i]) sz = 0, getsub(i, 0);
	work();
}
```

# 四、总结
上文提到的树的这种形态( `链树` ）很重要！想到之后就不难了。

---

## 作者：Haishu (赞：5)

### 思路
可以考虑另一种想法：因为我们发现，答案是肯定不会大于在原来的树上的最短路径的。所以原来的最短路是（有可能的）最大值！

我们把树变成这样，提取出1~n的路径，方便观看撕烤：

![](https://cdn.luogu.com.cn/upload/image_hosting/6759v92s.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

（它有个我起的名字，叫**灯笼树态**,处理树上路径与其余部分之间的关系时画图用，并非真实的数据结构)

我们称被提取出来的树上路径（本题为1~n）为**灯笼线**，路径上每一个节点及其下悬挂的子树称为**灯笼子树**，每一个灯笼子树的根节点叫**悬挂点**。

**(这一段可以跳过,太烦了影响思维)** ~~显然，悬挂点一定在灯笼线上。任意一个点的悬挂点就是它所在的灯笼子树的悬挂点。一个点如果在灯笼线上，那么它的悬挂点是自己。~~

那么什么时候原来的最短路不是答案呢？

那么就是对于任何的u和v，将它们连接起来后，新的最短路都比原来的最短路小。

换句话说:设**灯笼线**上的两个点x和y分别为准备新加边的u，v的**悬挂点**。那么只需比较(x到y的路径长度)和（u~x，v~y的长度和再加上每次询问时的那个值)即可。

~~（重头戏来了！)~~

**如果上文的u和v再同一颗灯笼子树内呢？**

 （*）于是,你发现一个结论：如果一颗灯笼子树除悬挂点外有超过两个以上的节点，那么连接这颗灯笼子树内的两个没有直接边相连的点，无论询问多少，Ans会取到原图的最短路，也就是理论最大值。 

**所以，我们仅需考虑每颗颗灯笼子树除悬挂点外仅有1的点的原树即可。**

由于要比较(x到y的路径长度)和（u~x，v~y的长度和再加上每次询问时的那个值），所以我们可以算出最大的(x到y的路径长度)-（u~x，v~y的长度和）,每次询问将其加上询问值并与0比较即可。

如何算出(x到y的路径长度)-（u~x，v~y的长度和）？将这个式子拆开分别维护，一遍dfs，用heap维护一下。建议读者自行撕烤这部分内容。

Code：
```cpp
#include <cstdio>
#include <queue>
using namespace std;
const int S=600006;
struct info
{
	int x;
	long long s;
	inline bool operator<(const info &a) const
	{
		return s<a.s;
	}
}st[S];
priority_queue<info> pq;
int n,m,h[S],nx[S],v[S],w[S],eg=1,s[S],fa[S],top,lc[S],rc[S];
const long long infl=(1ll<<60)-1;
long long dep[S],res=-infl;
bool flag,mk[S];
void read(int &s)
{
	s=0;char c=getchar();
	while (c<'0' || c>'9') c=getchar();
	while (c>='0' && c<='9') s=(s<<1)+(s<<3)+(c^48),c=getchar();
}
inline void egadd(int uu,int vv,int ww)
{
	nx[++eg]=h[uu];h[uu]=eg;
	v[eg]=vv;w[eg]=ww;
}
void dfs_1(int x)
{
	s[x]=1;
	for (int i=h[x];i;i=nx[i])
		if (v[i]!=fa[x])
		{
			fa[v[i]]=x;
			dep[v[i]]=dep[x]+w[i];
			dfs_1(v[i]);
			s[x]+=s[v[i]];
		}
}
bool check()
{
	int o=n;
	if (s[o]>2) return false;
	while (o!=1)
	{
		if (s[fa[o]]-s[o]>2) return false;
		mk[o]=true;
		o=fa[o];
	}
	mk[1]=true;
	return true;
}
inline long long ma(long long a,long long b){return a>b?a:b;}
inline long long mi(long long a,long long b){return a<b?a:b;}
void dfs_3(int x)//这里是将原树转为二叉树，因为灯笼子树大小不超过两个点的树就是一颗二叉树
{
	for (int i=h[x];i;i=nx[i])
		if (v[i]!=fa[x])
		{
			dfs_3(v[i]);
			if (mk[v[i]])
			{
				lc[x]=v[i];
				break;
			}
		}
	for (int i=h[x];i;i=nx[i])
		if (v[i]!=fa[x])
			if (!mk[v[i]])
			{
				rc[x]=v[i];
				break;
			}
}
void dfs_2(int x)
{
	if (lc[x]) dfs_2(lc[x]);
	if (rc[x]) dfs_2(rc[x]);
	while (!pq.empty() && fa[pq.top().x]==x)
		st[++top]=pq.top(),pq.pop();
	if (!pq.empty()) res=ma(res,pq.top().s+dep[x]);
	while (top) pq.push(st[top--]);
	pq.push((info){x,2*(mk[x]?0:dep[x]-dep[fa[x]])-dep[x]});
}
int main()
{
	read(n);read(m);
	for (int i=1;i<n;i++)
	{
		int uu,vv,ww;
		read(uu);read(vv);read(ww);
		egadd(uu,vv,ww);
		egadd(vv,uu,ww);
	}
	dfs_1(1);
	flag=check();
	if (flag) dfs_3(1),dfs_2(1);
	int x;
	while (m--)
	{
		read(x);
		if (flag) printf("%lld\n",dep[n]+mi(0,res+x));
		else printf("%lld\n",dep[n]);
	}
	return 0;
}

```

---

## 作者：kkxacj (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1016F)
#### 思路

提供一个 $O\left ( n \log n \right ) $ 做法。

设 $dis\left (i,j \right)$ 为 $i$ 到 $j$ 的简单路径距离，题目要求找到两个点 $x,y$，使得 $dis\left (1,x \right) + dis\left (y,n \right)$ 最大且两条路径没有重合部分。

考虑预处理 $dis\left (i,n \right)$，将 $1$ 到 $n$ 间的路径提取出来，可以得到下图：



![](https://cdn.luogu.com.cn/upload/image_hosting/5rneqwhu.png)

图中的三角形表示子树，圆点表示 $1$ 到 $n$ 经过的点，接下来提到的**三角形**和**圆点**都是上面这个意思，**每个圆点可能不止一个子树**。

首先，你要知道一个很重要的东西：**如果我在 $i$ 时计算了与 $j$ 的贡献，在 $j$ 时不计算 $i$ 也没影响**。

现在要求每个点向**之后的点**连边最大贡献为多少。

**$i$ 之后的点**定义为没有计算过连 $i$ 的贡献的点。

假设圆点由从 $1$ 到 $n$ 的便利顺序编号。

**对于第 $i$ 个圆点**，计算所有 $i$ 之后的子树和第 $i+2$ 之后的圆点中 $dis\left (j,n \right)$ 最大为多少。

**对于第 $i$ 个子树内的点**，若它的父亲是 $i$，计算所有 $i$ 之后的子树和第 $i+1$ 之后的圆点中 $dis\left (j,n \right)$ 最大为多少，否则计算所有 $i$ 之后的子树和第 $i$ 之后的圆点中 $dis\left (j,n \right)$ 最大为多少。

这就很好做了，直接用的优先队列维护，删除的话可以另开一个优先队列每次插入要删的数，然后如果两个栈顶一样就一起删除，代码实现如下。

```
p1.push(x);//要删的数
while(!p.empty() && !p1.empty() && p.top() == p1.top()) p.pop(),p1.pop();//删数
```

从 $1$ 开始递归，先递归不是 $1$ 到 $n$ 间经过的点，先把贡献删去，再计算，然后在递归是 $1$ 到 $n$ 间经过的点，然后顺便计算该点的贡献就行了。

**code**
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO
{
	template<typename T>
	void read(T &_x){_x=0;int _f=1;char ch=getchar();while(!isdigit(ch)) _f=(ch=='-'?-1:_f),ch=getchar();while(isdigit(ch)) _x=_x*10+(ch^48),ch=getchar();_x*=_f;}
	template<typename T,typename... Args>
	void read(T &_x,Args&...others){Read(_x);Read(others...);}
	const int BUF=20000000;char buf[BUF],top,stk[32];int plen;
	#define pc(x) buf[plen++]=x
	#define flush(); fwrite(buf,1,plen,stdout),plen=0;
	template<typename T>inline void print(T x){if(!x){pc(48);return;}if(x<0) x=-x,pc('-');for(;x;x/=10) stk[++top]=48+x%10;while(top) pc(stk[top--]);}
}
using namespace IO;
int n,m,cnt,x,y,z,head[300010],f[300010],dis[300010],v[300010],ma;
priority_queue<int>p,p1; 
struct w
{
	int to,nxt,z;
}a[600010];
inline void add(int x,int y,int z)
{
	a[++cnt].to = y;
	a[cnt].nxt = head[x];
	a[cnt].z = z;
	head[x] = cnt;
}
void dfs(int x,int fa)
{
	if(x == 1) v[x] = 1;
	for(int i = head[x];i;i = a[i].nxt)
		if(a[i].to != fa) dis[a[i].to] = dis[x]+a[i].z,dfs(a[i].to,x);
	for(int i = head[x];i;i = a[i].nxt)
		if(a[i].to != fa && v[a[i].to]) v[x] = 1;
}
void dfs1(int x,int fa,int z,int id)
{
	if(id == 0) p1.push(dis[x]);
	while(!p.empty() && !p1.empty() && p.top() == p1.top()) p.pop(),p1.pop();
	if(id <= 1)//非1到n间的点 
	{
		for(int i = head[x];i;i = a[i].nxt)
			if(a[i].to != fa && !v[a[i].to])
				dfs1(a[i].to,x,z+a[i].z,id);
	}
	else
	{
		for(int i = head[x];i;i = a[i].nxt)//先将子树的贡献都删了 
			if(a[i].to != fa && !v[a[i].to])
				dfs1(a[i].to,x,z+a[i].z,0);
		for(int i = head[x];i;i = a[i].nxt)//算贡献 
			if(a[i].to != fa && !v[a[i].to])
				dfs1(a[i].to,x,z+a[i].z,1);
	}
	if(id == 2) p1.push(dis[x]);
	if(!v[x] && !p.empty()) 
	{
		if(v[fa])//边不能重复 
		{
			p1.push(dis[fa]);
			while(!p.empty() && !p1.empty() && p.top() == p1.top()) p.pop(),p1.pop();
			if(!p.empty()) f[x] = z + p.top();
			p.push(dis[fa]);
			while(!p.empty() && !p1.empty() && p.top() == p1.top()) p.pop(),p1.pop();//先删掉在加回去 
		}
		else f[x] = z + p.top();
	}
	if(v[x])
	{
		for(int i = head[x];i;i = a[i].nxt)
			if(a[i].to != fa && v[a[i].to])
			{
				p1.push(dis[a[i].to]);
				while(!p.empty() && !p1.empty() && p.top() == p1.top()) p.pop(),p1.pop();//不能和下一个点连边。 
				if(!p.empty()) f[x] = z + p.top();
				p.push(dis[a[i].to]);
				while(!p.empty() && !p1.empty() && p.top() == p1.top()) p.pop(),p1.pop();
				dfs1(a[i].to,x,z+a[i].z,2);
			}
	}
}
signed main()
{
	read(n),read(m);
	for(int i = 1;i < n;i++) read(x),read(y),read(z),add(x,y,z),add(y,x,z);
	dfs(n,0);
	for(int i = 1;i <= n;i++) p.push(dis[i]);
	dfs1(1,0,0,2);
	for(int i = 1;i <= n;i++) ma = max(ma,f[i]);
	sort(f + 1,f + 1 + n);
	for(int i = 1;i <= m;i++)
	{
		read(x);
		print(min(ma+x,dis[1])),pc('\n');
	}
	flush();
	return 0;
}
//1 2 3
```

---

## 作者：2018ljw (赞：3)

一种很好想但没人提的思路。

题目大意：给定一棵树，边带权，任选两个不相邻的点连一条权值为 $k$ 的边，$1$ 与 $n$ 之间最短路的最大值是多少。多次询问。

首先将 $1$ 作为根，把 $1$ 到 $n$ 的链提出来，上面的点认为是关键点，其余点认为是非关键点。考虑什么情况下连边一定可以不改变最短路。

1. 某个关键点与至少两个非关键点相连。在这两个非关键点之间连边即可。
2. 某两个非关键点之间有祖辈关系。让较深的点向比其深度小 $2$ 的点连边即可。

特判完这两种情况，我们发现，剩下的树大概长这样：从 $1$ 到 $n$ 一条链，链上每个点可能连了一个非关键点。出于方便，我们假设没有连非关键点的节点也各连了一个点，边权为 $0$。显然如果连边的话肯定在非关键点之间相连更优。

令 $d_x$ 表示$1$ 到 $x$ 的最短路，$a_x$ 表示节点 $x$ 和与其相邻的非关键点之间边权大小。现在连一条长为 $k$ 的边，假设 $x,y$ 为我们连边的两个点且与 $x$ 相连的关键点深度较浅。

有影响的只有 $x,y$ 之间的路径，$d_y-d_x$ 与 $a_x+a_y+k$ 取最小。前者做最小对答案没影响，假设后者最小，那么最短路会变小 $d_y-d_x-(a_x+a_y+k)=d_y-a_y-(d_x+a_x)-k$。我们的目标就是最小化这个柿子。

$k$ 是常量不用管，所以我们就是要找到最小的 $(d_y-a_y)-(d_x+a_x)$。从根往下扫一遍，维护 $\max\{d_x+a_x\}$ 更新最小值。然后处理询问，看减去 $k$ 后值是负数最短路不变，否则减去这个值，就行了...吗？

大体上，这个思路是没问题的。但找的时候，我们会发现如果相邻两个点权均为 $0$，说明这两个点都是我们的虚拟点，原图中还有这条边，因此是不能连边的！所以我们还要维护刨去父节点的最大值。

```cpp
#include<cstdio>
#include<vector>
using namespace std;
vector<int>g[300001],gg[300001];
int fa[300001],a[300001],n,son[300001];
bool imp[300001];
long long d[300001];
void dfs(int x){
	int i;
	for(i=0;i<g[x].size();i++){
		int y=g[x][i];
		if(fa[x]==y)continue;
		fa[y]=x;
		d[y]=d[x]+gg[x][i];
		dfs(y);
	}
}
long long maxn(long long x,long long y){
	return x>y?x:y;
}
int main(){
	int i,m;
	bool nf=0;
	scanf("%d%d",&n,&m);
	for(i=1;i<n;i++){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		g[x].push_back(y);
		g[y].push_back(x);
		gg[x].push_back(z);
		gg[y].push_back(z);
	}
	dfs(1);
	imp[1]=1;i=n;while(i!=1)imp[i]=1,i=fa[i];
	for(i=1;i<=n;i++){
		if(g[i].size()>=4-(i==1||i==n)||(!imp[i]&&g[i].size()>1)){
			nf=1;
			break;
		}
	}
	if(nf){
		while(m--)printf("%lld\n",d[n]);
		return 0;
	}
	i=n;while(i!=1)son[fa[i]]=i,i=fa[i];
	for(i=1;i<=n;i++)if(!imp[i])a[fa[i]]=gg[i][0];
	long long mx=d[1]+a[1],rs=1ll<<60,pmx=-rs;
	for(i=son[1];i;i=son[i]){
		if(a[i]||a[fa[i]]){
			if(d[i]-a[i]-mx<rs)rs=d[i]-a[i]-mx;
		}
		else if(d[i]-a[i]-pmx<rs)rs=d[i]-a[i]-pmx;
		pmx=mx;
		if(d[i]+a[i]>mx)mx=d[i]+a[i];
	}
	while(m--){
		scanf("%d",&i);
		printf("%lld\n",d[n]-maxn(rs-i,0));
	}
}
```

---

## 作者：LS_Z_66066 (赞：2)

~~一道诈骗题。~~

称 $1$ 到 $n$ 的路径为主干路径 $G$。

把 $G$ 上的每个点当作根，如图：
![](https://cdn.luogu.com.cn/upload/image_hosting/hbhcu1jp.png?x-oss-process=image/resize,m_lfit,h_600,w_600)

这棵树就被分成的许多**根相连的树**。

这就是本题最重要的思路。

先跑一遍 dfs 求 $dis_i$ 为 $1$ 到 $i$ 的距离。

显然，如果其中一棵树的结点数 $\ge3$ 那么答案一定就是原路径 $dis_n$。

接着讨论剩余情况。
![](https://cdn.luogu.com.cn/upload/image_hosting/d12czmb8.png?x-oss-process=image/resize,m_lfit,h_600,w_600)

$f_u$ 为该点到其子节点的距离，其中 $u$ 为 $G$ 上的结点。

题目要求最短路径最长，所以新加的边形成的路径一定要是能到 $n$ 号点的距离最远的路径，在 $i$ 和 $j$ 间，新添一条边权为 $w$ 的边得到的新路径的距离为 $dis_j  + f_j+w+f_i+(dis_n-dis_i)$，其中 $i$ 和 $j$ 均为 $G$ 上的点，最后跑 $G$ 求式子的最大值即可。

注意判断新连的两点之间不能有路径。

[AC记录](https://codeforces.com/contest/1016/submission/321618058)

---

## 作者：_edge_ (赞：2)

简单的 $2600$，个人认为难度虚高，但是还是调了挺久了。

各位 dalao 都是 $O(n)$ 的做法，那我来个 $O(n \log n)$ 的做法吧。

我们先预处理一个 $dis_{0,i}$ 表示 $1$ 到它的距离，以及 $dis_{1,i}$ 表示 $n$ 到它的距离。

容易观察就可以知道 $(u,v)$ 有效的只有一组，那就是 $\min(dis_{0,u}+dis_{1,v},dis_{1,u}+dis_{0,v})$ 最大的那一组。

如果我们连上了 $u$ 到 $v$ 的这条边，那么答案肯定是走过它或者直接走 $1$ 到 $n$ 的最短路，前者就是上面的式子加个边权。

然后我们需要找到 $(u,v)$ 有效的那组，那样的话，先讨论拆掉 $\min$。

$dis_{0,u}+dis_{1,v} \le dis_{1,u}+dis_{0,v}$，那么移项得到 $dis_{0,u}-dis_{1,u} \le dis_{0,v}-dis_{1,v}$，然后按照这个差值排序，一个数的前缀就是和它取 $\min$ 里面前者的值，后缀是后者。

那么就可以用线段树进行维护了！

思维难度不高，可以尝试自己玩一下。

```cpp
#include <bits/stdc++.h>
#define int long long 
using namespace std;
const int INF=6e5+5;
struct _node_edge{
	int to_,next_,disv_;
}edge[INF<<1];
int n,m,tot,head[INF];
int dis_[3][INF],cnt[INF],p[INF],pp[INF],Max2[INF],Max3[INF];
void add_edge(int x,int y,int z) {
	edge[++tot]={y,head[x],z};
	head[x]=tot;
}
queue <int> q;
void SPFA(int s,int t) {
	memset(dis_[t],63,sizeof dis_[t]);
	q.push(s);dis_[t][s]=0;
	while (q.size()) {
		int x=q.front();q.pop();
		for (int i=head[x];i;i=edge[i].next_) {
			int v=edge[i].to_,d=edge[i].disv_;
			if (dis_[t][v]>dis_[t][x]+d) {
				dis_[t][v]=dis_[t][x]+d;
				q.push(v);
			}
		}
	}
}
struct BIT3{
	#define ls(x) x<<1
	#define rs(x) x<<1|1
	int tree[INF<<2],m;
	void build() {
		m=1;
		while (m<=n+1) m*=2;
		for (int i=n+m+1;i;i--)
			if (i>=m) {
				tree[i]=dis_[0][p[i-m+1]];
				tree[n+1+m]=tree[n+m]=-1e15;
			}
			else tree[i]=max(tree[ls(i)],tree[rs(i)]);
		
//		for (int i=m;i<=n+m+1;i++)
//			cout<<tree[i]<<" iyw?\n";
	}
	void add(int x,int y) {
		x+=m;x--;tree[x]+=y;
//		cout<<x<<" "<<tree[x]<<" "<<y<<" kelkel\n";
		while (x>1) {
			x>>=1;
			if (x) 
				tree[x]=max(tree[ls(x)],tree[rs(x)]);
		}
		
//		for (int i=1;i<=n+m+1;i++)
//			cout<<i<<" "<<tree[i]<<" endl\n";
	}
	int query(int x,int y) {
		if (x>y) return -1e15;
		int l=x+m-1,r=y+m-1,ans=max(tree[l],tree[r]);
		while (l || r) {
//			cout<<l<<" "<<r<<" "<<tree[l]<<" "<<tree[r]<<" kel\n";
			if (l/2!=r/2) {
				if (l%2==0) ans=max(ans,tree[l+1]);
				if (r%2==1) ans=max(ans,tree[r-1]);
			}
			else break;
			l/=2,r/=2;
		}
		return ans;
	}
}T2;
struct BIT{
	#define ls(x) x<<1
	#define rs(x) x<<1|1
	int tree[INF<<2],m;
	void build() {
		m=1;
		while (m<=n+1) m*=2;
		for (int i=n+m+1;i;i--)
			if (i>=m) {
				tree[i]=dis_[1][p[i-m+1]];
				tree[n+1+m]=tree[n+m]=-1e15;
			}
			else tree[i]=max(tree[ls(i)],tree[rs(i)]);
		
//		for (int i=m;i<=n+m+1;i++)
//			cout<<tree[i]<<" iyw?\n";
	}
	void add(int x,int y) {
		x+=m;x--;tree[x]+=y;
		while (x>1) {
			x>>=1;
			if (x) 
				tree[x]=max(tree[ls(x)],tree[rs(x)]);
		}
		
//		for (int i=1;i<=n+m+1;i++)
//			cout<<i<<" "<<tree[i]<<" endl\n";
	}
	int query(int x,int y) {
		if (x>y) return -1e15;
		int l=x+m-1,r=y+m-1,ans=max(tree[l],tree[r]);
		while (l || r) {
			if (l/2!=r/2) {
				if (l%2==0) ans=max(ans,tree[l+1]);
				if (r%2==1) ans=max(ans,tree[r-1]);
			}
			else break;
			l/=2,r/=2;
		}
		return ans;
	}
}T1;
//struct Segment{
//	#define ll tl[id]
//	#define rr tr[id]
//	#define ls(x) x<<1
//	#define rs(x) x<<1|1
//	int tl[INF<<2],tr[INF<<2],sum[INF<<2];
//	void push_up(int id) {sum[id]=max(sum[ls(id)],sum[rs(id)]);}
//	void build(int l,int r,int id) {
//		ll=l;rr=r;
//		if (l==r) {sum[id]=dis_[1][p[l]];return ;}
//		int Mid=(l+r)>>1;
//		build(l,Mid,ls(id));
//		build(Mid+1,r,rs(id));
//		push_up(id);
//	}
//	void add(int l,int x,int id) {
//		if (ll==rr) {sum[id]=x;return ;}
//		int Mid=(ll+rr)>>1;
//		if (l<=Mid) add(l,x,ls(id));
//		else add(l,x,rs(id));
//		push_up(id);
//	}
//	int query(int l,int r,int id) {
//		if (l<=ll && rr<=r) return sum[id];
//		int Mid=(ll+rr)>>1;
//		if (l>Mid) return query(l,r,rs(id));
//		else if (r<=Mid) return query(l,r,ls(id));
//		else return max(query(l,r,ls(id)),query(l,r,rs(id)));
//	}
//}T1;
int check(int xx,int i) {
	// min(dis_[0][i]+dis_[1][j],dis_[1][i]+dis_[0][j])>=xx
	int l=1,r=n,ans=-1,yy=xx-dis_[1][i];
	while (l<=r) {
		int Mid=(l+r)>>1;
		if (dis_[0][p[Mid]]>=yy) r=(ans=Mid)-1;
		else l=Mid+1;
	}
	if (ans==-1) return 0;
	if (T1.query(ans,n)+dis_[0][i]>=xx) return 1;
	return 0;
}
signed main()
{
//	freopen("test.in","r",stdin);
//	freopen("test.out","w",stdout);
	memset(T1.tree,-63,sizeof T1.tree);
	memset(T2.tree,-63,sizeof T2.tree);
	cin>>n>>m;
	for (int i=1;i<n;i++) {
		int x=0,y=0,z=0;
		cin>>x>>y>>z;
		add_edge(x,y,z);
		add_edge(y,x,z);
	}
	
	SPFA(1,0);
	SPFA(n,1);
	for (int i=1;i<=n;i++) p[i]=i;
	sort(p+1,p+1+n,[](int x,int y){return dis_[0][x]<dis_[0][y];});
	sort(p+1,p+1+n,[](int x,int y){return dis_[0][x]-dis_[1][x]<dis_[0][y]-dis_[1][y];});
	int sum=0;
	T2.build(); T1.build();
	for (int i=1;i<=n;i++) pp[p[i]]=i;
//	for (int i=1;i<=n;i++)
//		cout<<dis_[0][p[i]]<<" "<<dis_[1][p[i]]<<" over?\n";
//	for (int i=1;i<=n;i++) cout<<p[i]<<" ";
//	cout<<" alding\n";
	for (int i=1;i<=n;i++) {
		for (int j=head[i];j;j=edge[j].next_) {
			T1.add(pp[edge[j].to_],-1e15);
			T2.add(pp[edge[j].to_],-1e15);
		}
		T1.add(pp[i],-1e15);
		T2.add(pp[i],-1e15);
//		cout<<i<<" "<<sum<<" "<<T2.query(1,pp[i]-1)+dis_[1][i]<<" "<<T1.query(pp[i]+1,n)+dis_[0][i]<<" over?=======================================\n"; 
//		for (int j=1;j<=n;j++) {
//			if (cnt[j]) continue;
//			if (i==j) ;
//			else sum=max(sum,min(dis_[0][i]+dis_[1][j],dis_[1][i]+dis_[0][j]));
//		}
//      dis_[0][i]+dis_[1][j]<=dis_[1][i]+dis_[0][j]
//      dis_[0][i]-dis_[1][i]<=dis_[0][j]-dis_[1][j] 
//		int l=0,r=3e14,ans=-1;
//		while (l<=r) {
//			int Mid=(l+r)>>1;
//			if (check(Mid,i)) l=(ans=Mid)+1;
//			else r=Mid-1;
//		}
		
		// T1 ->1 T2 -> 0
		sum=max(sum,max(T2.query(1,pp[i]-1)+dis_[1][i],T1.query(pp[i]+1,n)+dis_[0][i]));
		T1.add(pp[i],1e15);
		T2.add(pp[i],1e15);
		for (int j=head[i];j;j=edge[j].next_) {
			T1.add(pp[edge[j].to_],1e15);
			T2.add(pp[edge[j].to_],1e15);
		}
	}
//	cout<<sum<<" iyw?\n";
	for (int i=1;i<=m;i++) {
		int x=0;cin>>x;
		cout<<min(sum+x,dis_[0][n])<<"\n";
	}
	return 0;
}
```


---

## 作者：Piwry (赞：2)

## 解析

这里介绍一种相对更好写的做法

考虑添加一条边 $(u, v)$ 后会发生什么事。有两种情况：

1. 如果这令 $1, n$ 间的简单路径数增加了（一条），容易证明其权为 $\min(d_1[u]+d_n[v], d_n[u]+d_1[v])+w(u, v)$，其中 $d_1[x], d_n[x]$ 分别表示原树中 $x$ 到 $1, n$ 的路径的权

2. 如果这没有令 $1, n$ 间的简单路径数增加，那么显然 $\min(d_1[u]+d_n[v], d_n[u]+d_1[v])+w(u, v)$ 一定比原树中 $1$ 到 $n$ 的路径权（即 $d_1[n]$）大

于是只要我们能求出 $ans=\max\{\min(d_1[u]+d_n[v], d_n[u]+d_1[v])\}$（当然 $u, v$ 间在原树中不能有边），对每次询问 $x_j$ 就只需输出 $\min(d_1[n], ans+x_j)$ 即可

我们枚举 $u$，且只选择满足 $d_1[u]+d_n[v] < d_n[u]+d_1[v]$ 的 $v$，显然需要在其中找到 $d_n[v]$ 最大的 $v$ 与其配对。考虑如何快速找到这个东西：

将刚才的不等式变形一下，转为 $d_1[u]-d_n[u] < d_1[v]-d_n[v]$。设排序后第 $x$ 位的元素对应的结点编号为 $number[x]$，如果我们将元素以 $d_1[x]-d_n[x]$ 为关键字排序，容易发现对于 $i, j$，且 $j$ 满足 $j>i$，一定有 $d_1[number[i]]+d_n[number[j]] < d_n[number[i]]+d_1[number[j]]$。

于是刚才的问题就很容易解决了，只需按上述关键字排序后，按排序顺序枚举 $u$，再用数据结构维护 $d_n[v]$ 最大的 $v$ 即可

最后考虑找到的 $v$ 如果与 $u$ 在原树间存在边（即非法时）时该怎么办。其实我们可以直接顺次枚举 $d_n[v]$ 更小的 $v$（于是这里需要用平衡树维护 $v$ 集合，而不能用堆）。注意到这样的枚举次数是依赖于边数的，因此不会出问题

## CODE

```cpp
#include <cstdio>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#define ll long long
using std::vector;
using std::map;
using std::set;
using std::pair;
using std::sort;
using std::max;
using std::min;
typedef pair<ll, int> pad;

/*------------------------------IO------------------------------*/

namespace IO_number{
	int read(){
		int x =0; char c =getchar(); bool f =0;
		while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
		while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
		return (f) ? -x : x;
	}
	
	void write(const ll &x){
		if(x < 0){
			putchar('-');
			write(-x);
		}
		else{
			if(x/10)
				write(x/10);
			putchar('0'+x%10);
		}
	}
}
using namespace IO_number;

/*------------------------------Func------------------------------*/

namespace Graph{
	struct edge{
		int to, nxt, w;
		
		edge(const int &_to, const int &_nxt, const int &_w)
			:to(_to), nxt(_nxt), w(_w){}
	};
	vector<int> first;
	vector<edge> e(1, edge(0, 0, 0));
	
	inline void addedge(const int &u, const int &v, const int &w){
		e.push_back(edge(v, first[u], w)), first[u] =e.size()-1;
		e.push_back(edge(u, first[v], w)), first[v] =e.size()-1;
	}
}
using namespace Graph;

struct node{
	ll to_1, to_n;
	int node_number;
	
	node(){}
	node(const ll &_to_1, const ll &_to_n, const int &_node_number)
		:to_1(_to_1), to_n(_to_n), node_number(_node_number){}
};
vector<node> dp;

void dfs_dp(const int &u, const int &fa, const char &typ){
	dp[u].node_number =u;
	for(int l =first[u]; l; l =e[l].nxt)
		if(e[l].to != fa){
			if(typ == '1')
				dp[e[l].to].to_1 =dp[u].to_1+e[l].w;
			else
				dp[e[l].to].to_n =dp[u].to_n+e[l].w;
			dfs_dp(e[l].to, u, typ);
		}
}

/*------------------------------Main------------------------------*/

int main(){
	const int n =read(), m =read();
	first.resize(n+1);
	e.reserve(2*(n-1)+1);
	vector<set<int> > e_(n+1, set<int>());
	for(int i =0; i < n-1; ++i){
		const int u =read(), v =read(), w =read();
		addedge(u, v, w);
		e_[u].insert(v), e_[v].insert(u);
	}
	
	dp =vector<node>(n+1, node(0, 0, 0));
	dfs_dp(1, 0, '1'), dfs_dp(n, 0, 'n');
	ll ans_ =dp[n].to_1;
	
	sort(dp.begin()+1, dp.end(), [&](const node &A, const node &B){ return A.to_1-A.to_n < B.to_1-B.to_n; });
	/* -tips: (A_1+B_n < A_n+B_1) => (A_1-A_n < B_1-B_n) */
	map<ll, int> Map;
	ll ans =0;
	for(int i =n; i >= 1; --i){
		auto it =Map.begin();
		while(it != Map.end() && e_[dp[i].node_number].count(dp[it->second].node_number))
			++it;
		if(it != Map.end())
			ans =max(ans, dp[i].to_1+dp[it->second].to_n);
		Map.insert(pad(-dp[i].to_n, i));
	}
	
	for(int _t =0; _t < m; ++_t)
		write(min(ans_, ans+read())), putchar('\n');
}
```

---

## 作者：cyffff (赞：1)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF1016F)
## 题意
给一颗 $n$ 个结点的带权树，$q$ 组询问在树上加一条长度为 $x$ 的边后 $1\to n$ 的最短路的最大值。

$n,q\le 3\times 10^5$.
## 思路
锐评：看不懂某篇单调栈，于是来写个前缀和。

照样把 $1\to n$ 的链拉出来并标记它们，令它们的 $v_i=1$，链长为 $t$。

令 $p_i$ 表示被标记的点 $i$ 到 $1$ 的权值和，$d_i$ 表示被标记的点 $i$ 到它不被标记的儿子的子树中最大的距离，$s_i$ 表示点 $i$ 不被标记的儿子的子树中的点数和。

首先答案不大于 $p_n$。考虑 $\exists v_i=1,s_i\ge 2$，则连接它的链外子树中任意两点，不改变最短路，答案为 $p_n$。

否则，考虑在 $i$ 或它的的链外子树和 $j$ 或它的的链外子树中选两个点连边，答案为 
$$\max_{i<j,v_{i,j}=1}(p_i+d_i-p_j+d_j+p_n+x)$$

可以发现，答案只与前四项有关，处理出 $p_i+d_i$ 的前缀 $\max pr_i$ 和取到的位置 $prp_i$，处理出 $-p_i+d_i$ 的后缀 $\max sf_i$ 和取到的位置 $sfp_i$，答案则为
$$\max_{i=1}^{t-1} (pr_i+sf_{i+1})+p_n+x$$

特别地，当最优决策相邻并且都没有链外子树时不能取到。

做完了，时间复杂度 $\Theta(n+q)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
namespace IO{//by cyffff
	
}
const int N=3e5+10;
struct Edge{
	int to,nxt,w;
}a[N<<1];
int n,q,siz[N],fa[N],cnt,head[N];
ll p[N],d[N];
bool vis[N];
vector<int>vec;
inline void add(int u,int v,int w){
    cnt++;
    a[cnt].to=v;
    a[cnt].nxt=head[u];
    a[cnt].w=w;
    head[u]=cnt;
}
inline void dfs1(int rt,int f){
	fa[rt]=f;
	for(int i=head[rt];i;i=a[i].nxt){
		int t=a[i].to;
		if(t==f) continue;
		dfs1(t,rt);
	}
}
inline void dfs2(int rt){
	siz[rt]=1;
	if(vis[rt]) vec.push_back(rt);
	for(int i=head[rt];i;i=a[i].nxt){
		int t=a[i].to;
		if(t==fa[rt]) continue;
		if(vis[t])
			p[t]=p[rt]+a[i].w;
		dfs2(t);
		if(!vis[t])
			siz[rt]+=siz[t],
			d[rt]=max(d[rt],d[t]+a[i].w);
	}
}
bool fl;
int prp[N],sup[N];
ll pr[N],sf[N],sep[N],ses[N],ans=-2e18;
int main(){
	n=read(),q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}
	dfs1(1,0);
	for(int i=n;i;i=fa[i])
		vis[i]=1;
	vec.push_back(0);
	dfs2(1);
	for(int i=1;i<=n;i++)
		if(siz[i]>=3) 
			fl=1;
	pr[0]=sf[vec.size()]=-2e18;
	for(int i=1;i<vec.size();i++){
		ll tmp=p[vec[i]]+d[vec[i]];
		if(tmp>pr[i-1]) pr[i]=tmp,prp[i]=i;
		else pr[i]=pr[i-1],prp[i]=prp[i-1];
	}
	for(int i=vec.size()-1;i;i--){
		ll tmp=-p[vec[i]]+d[vec[i]];
		if(tmp>sf[i+1]) sf[i]=tmp,sup[i]=i;
		else sf[i]=sf[i+1],sup[i]=sup[i+1];
	}
	for(int i=1;i<vec.size();i++){
		if(prp[i-1]==i-1&&sup[i]==i&&siz[vec[i-1]]==1&&siz[vec[i]]==1) continue;
		ans=max(ans,pr[i-1]+sf[i]);
	}
	ans+=p[n];
	for(int i=1;i<vec.size()-2;i++)
		ans=max(ans,p[vec[i]]+p[n]-p[vec[i+2]]);
	for(int i=1;i<vec.size();i++){
		if(siz[vec[i]]==1) continue;
		if(i!=1) ans=max(ans,p[vec[i-1]]+d[vec[i]]+p[n]-p[vec[i]]);
		if(i!=vec.size()-1) ans=max(ans,p[vec[i]]+d[vec[i]]+p[n]-p[vec[i+1]]);
	}
	while(q--){
		int x=read();
		write(fl?p[n]:min(ans+x<=0?p[n]:ans+x,p[n])),putc('\n');
	}
	flush();
}
```
再见 qwq~

---

## 作者：YellowBean_Elsa (赞：1)

### 这题出的挺妙的

先找出原树中1-n这条链

情况1：原树中1-n链上有点有>=2个非链的儿子，那直接连起来，不影响最短路，

情况2：每个链上点只有<=1个非链儿子，

我们可以假设添加了一条长度为0边，添加后最短路改变最小的那个是永远最优的添边方案。

计算1到链上每个点的距离($dis[i]$)和到链上每个点及其非链子节点（如果存在）的最大距离($mx[i]$)

维护 $dis[i]*2-mx[i]-mx[j]$ 最小值

这不是前缀维护线性扫描一下就好了吗（我由于菜用了单调队列）

注意链上相邻两点不能连边。

```cpp
//coder: Feliks Hacker of IOI == YB an AKer of IMO
//acknowledgement: https://www.cnblogs.com/myx12345/p/10065082.html
//码风丑见谅 
#include<bits/stdc++.h>
#define ll long long
#define re register
using namespace std;
const int N=1e6;
inline int read(){
	int x=0,f=1;char ch=getchar();
	while(!isdigit(ch) && ch!='-')ch=getchar();
	if(ch=='-')f=-1,ch=getchar();
	while(isdigit(ch))x=(x<<1)+(x<<3)+ch-'0',ch=getchar();
	return x*f;
}inline ll Min(ll x,ll y){
	if(x<y)return x;
	return y;
}inline ll Max(ll x,ll y){
	if(x>y)return x;
	return y;
}
int n,m;
int v[N],w[N],nex[N],first[N],tot;
inline void add(int x,int y,int z){
	v[++tot]=y;w[tot]=z;
	nex[tot]=first[x];
	first[x]=tot;
}
ll dis[N],mx[N];
int sz[N],fa[N];
bool vis[N],is[N],got;
//is: 一个点是否在链上
//got: 是否符合情况1 
int lian[N],cnt;
//记录链 
int a,b;
int q[N];//单调队列 
int mn[N];//对于链上每个点，和哪个点连边
//可以使2*dis[i] - mx[i] - mx[j]最小 
ll Mn=1e18;
void find(int x,int f){//找链，找父亲 
	vis[x]=1;fa[x]=f;
	if(x==n)for(re int i=1;i<=n;i++)if(vis[i])is[i]=1;
	for(re int i=first[x];i;i=nex[i]){
		int y=v[i];
		if(y==f)continue;
		find(y,x);
	}vis[x]=0;
}void dfs(int x,int f){//dis，子节点个数 
	sz[x]=1;
	for(re int i=first[x];i;i=nex[i]){
		int y=v[i];
		if(y==f)continue;
		dis[y]=dis[x]+w[i];
		dfs(y,x);
		sz[x]+=sz[y];
	}
}void DFS(int x){//记录链 
	lian[++cnt]=x;
	for(re int i=first[x];i;i=nex[i]){
		int y=v[i];
		if(y==fa[x] || !is[y])continue;
		sz[x]-=sz[y];
		//我们想让sz记录自身和非链子节点总个数 
		//所以要把某些东东减掉 （自行理解是哪些东东） 
		DFS(y);
	}
}void get_mx(int x){//看函数名即懂 
	mx[x]=dis[x];
	for(re int i=first[x];i;i=nex[i]){
		int y=v[i];
		if(y==fa[x])continue;
		get_mx(y);
		if(!is[y])//y是x的非链子节点 
			mx[x]=Max(mx[x],mx[y]);
	}
}
inline void prework(){
	find(1,0);
	dis[1]=0;dfs(1,0);
	DFS(1);
	for(re int i=1;i<=cnt;i++)
		if(sz[lian[i]]>=3)got=1;//由于sz算上自己，
		//所以需要>=3
	if(got)return; 
	get_mx(1);
	int l=1,r=0;q[++r]=1;//单调队列上场 
	if(!(dis[lian[1]]==mx[lian[1]]&&dis[lian[2]]==mx[lian[2]]))mn[2]=1;
	//相邻两点特判 
	for(re int i=3;i<=cnt;i++){
		mn[i]=q[l];
		while(l<=r && mx[lian[q[r]]]<mx[lian[i-1]])--r;
		q[++r]=i-1;
		//扫描到i时把i-2加进队列，防止相邻两点连边 
		if(!(dis[lian[i]]==mx[lian[i]]&&dis[lian[i-1]]==mx[lian[i-1]])
			&&mx[lian[i-1]]>mx[lian[mn[i]]])mn[i]=i-1;
		//判断相邻两点到底能不能连（即是否两点至少有一个有非链子节点） 
	}//计算最短路最小影响 
	if(mn[2])
		Mn=-mx[lian[2]]-mx[lian[mn[2]]]+(dis[lian[2]]<<1);
	for(re int i=3;i<=cnt;i++)
		Mn=Min(Mn,-mx[lian[i]]-mx[lian[mn[i]]]+(dis[lian[i]]<<1));
}
int main(){
	n=read(),m=read();
	for(re int i=1;i<n;i++){
		int x=read(),y=read(),z=read();
		add(x,y,z),add(y,x,z);
	}prework();
	while(m--){
		int x=read();
		if(got)printf("%lld\n",dis[n]);
		else printf("%lld\n",Min(dis[n],dis[n]-Mn+x));
		//若经过新连的边的路径竟然更长，则最短路不变（dis[n]） 
	}
	return 0;
}
```



---

## 作者：空の軌跡 (赞：1)

## 前言

不得不说 CF 的数据是真的强，但是还是有点漏洞，两份有些区别的代码都过了。感兴趣的同学可以看看我的记录，做了差不多三个小时。

# 思路

原图是棵树，我们可以先求 $1$ 到 $n$ 的距离，

题目要求添加新边后使得最短路最长，我们容易想到新加的边会造成影响，因此必须使得新的路径尽量的长。如果过长的话，最短路径肯定就是原路径了。

我们把 $1$ 到 $n$ 作为主链揪出来，其余边均作为支链摆到一侧，可以想到我们新加入的边会作为一条 “ 近路” 而不必经过主链上的边，从而直接经过这条路径来减少路程。


接下来我们仍然分类讨论 ( 我们将 $1$ 分在左侧 ， $n$ 分在右侧 ，新加入的边连接左右两侧) ：

- 加入的边的一点在支链上。

1. 该点在左侧 。当我们在左侧的某一点时，可以拐入这个点的支链到达这个点从而走这条边到达右侧。

2. 该点在右侧 。当我们从左侧经过这条边到达这个点时，从这个点所在支链返回主链。

3. 不难看出，以上加入的边后导致的长度为 支链长度 + 边长度 。因此我们应该尽量让支链长，所以如果选择了这条支链，就直接建在最深的叶子节点。
- 加入的边的一点在支链上。

1. 这个无需太多讨论，你可以将其认为成没有长度的支链上的点。

2. 长度为 边长度。

从上面的讨论中我们可以得到新建边后，若要使用这条边的需要的额外长度。

于是我们就应该与其节省的长度作比较。

节省的长度和容易计算，就是这条新建边的两个点所对应的主链上的点间的距离。

所以，我们应当以 $1$ 为根处理所有点的深度和子树内的最大深度以及子树内节点数量。

然后从 $n$ 向上跳并计算其所以的支链子树内的点的贡献。

期间，你记录一个值 $maxx$ 表示 支链长度 $-$ 主链长度 的最大值。通过这个值，你可以在计算贡献时，尝试将子树内深度最大的点与其匹配，最终长度即为 $maxx+dep[x]-dep[now]$ （其中 $x$ 为子树内最深的点 , $now$ 为当前的点）。计算完后并尝试更新 $maxx$ . 当你向上跳时，减去主链上边的长度来进行维护。但是你也可能将主链上的点作为匹配点，所以记得取个 $maxx$ 。

然而可能会出现一种错误情况，就是当你将主链上的某一点作为 匹配点 后，你向上跳之后， 这两个点间相互匹配了。 所以我又记录了一个 $maxx2$ ，来继承 $maxx$ ，然后只让 主链上点 与 $maxx2$ 匹配，就不会出现问题了。

对于一点，其所有支链的子树内点数之和多余 $2$ 的，你可以直接把 $ans$ 设满了，因为将新边建在这个子树内的话，最短路肯定就是主链了，新边不会减少路程的，因为两点对应的主链上的点间距离为 $0$ ，只会增加长度。

# 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline void read(int &x)
{
	int w=1;x=0;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')w=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	x*=w;
}
struct road
{
	int to,val;
};
vector<road>side[300010];
int fa[300010],dep[300010],siz[300010],maxdep[300010];
bool used[300010];
void dfs(int x)
{
	siz[x]=1;maxdep[x]=dep[x];
	for(int i=0;i<side[x].size();i++)
	{
		int to=side[x][i].to;
		int val=side[x][i].val;
		if(to==fa[x])continue;
		dep[to]=dep[x]+val;
		fa[to]=x;
		dfs(to);
		siz[x]+=siz[to];
		maxdep[x]=max(maxdep[x],dep[to]);
	}
}
signed main()
{
	int n,m,a,b,c;read(n);read(m);
	for(int i=1;i<n;i++)
	{
		read(a);read(b);read(c);
		side[a].push_back((road){b,c});
		side[b].push_back((road){a,c});
	}
	fa[1]=1;dfs(1);
	int now=n,maxx=-9999999999999999,ladep=-9999999999999,ladep2=-9999999999999,qa=9999999999999999,qb=999999999999999;
	while(1)
	{
	//	cout<<now<<" "<<qa<<" "<<qb<<" "<<ladep<<" "<<maxx<<"\n";
		int tofa,sizz=0;used[now]=1;
		maxx=max(ladep2,maxx);
		for(int i=0;i<side[now].size();i++)
		{
			int to=side[now][i].to;
			int val=side[now][i].val;
			if(to==fa[now])
			{
				tofa=val;
				continue;
			}
			if(used[to])continue;
			maxx=max(maxdep[to]-dep[now]+ladep,maxx);
			sizz+=siz[to];
			ladep=max(ladep,maxdep[to]-dep[now]);
		}
		if(sizz>1)maxx=99999999999999999;
		ladep2=max(ladep,ladep2);
		ladep2-=tofa;
		ladep=max(0ll,ladep);
		ladep-=tofa;
		maxx=max(-qa-qb,maxx);
		qb=qa;qa=tofa;
		if(now==1)break;
		now=fa[now];
	}
	for(int i=1;i<=m;i++)
	{
		read(a);
		cout<<dep[n]+min(0ll,maxx+a)<<"\n";
	}
}
```

---

## 作者：redegg (赞：1)

题意：
给你一个树，然后给您$m$次询问，询问间互相独立，每个询问让你添加一条长度给定的边，使$1$~$n$的最短路变化最小。

特判+树形$dp$（可能是贪心？）

可以确定的是，如果$1$~$n$的最短路链上有一个点拥有两个以上的不在最短路链表上的点，那么我们添加边的时候就直接随便连在那两个点上了，不会对最短路产生影响。所有询问都直接输出最短路长度。

剩下的就是每一个在最短路链上的点都只有一个或没有子节点的情况，注意此处的字节点是不包括链上的点的。

我们可以假设添加了一条长度为$0$边，添加后最短路改变最小的那个是最优的添边方案。

那么我们可以跑两次最短路，分别从$1$出发和从$n$出发，从$1$出发记为$dis1[]$，从$n$出发为$dis2[]$。记录一个$maxn1[i]$表示到了$i$这个点，从$1$出发到$i$这个点（同时也到了$i$的链外子节点）的最长路径，那么如果$son[i]$存在，那么一定是$maxn1[i]=max(dis1[son[i]],maxn1[father[i]])$，否则是$maxn1[i]=max(dis1[i],maxn1[father[i]])$，$father[i]$代表的是从$1$到$i$链上的$i$的相邻点，$i$和$father[i]$必须在最短路链上，$son[i]$必须不在最短路链上。此外$maxn2$代表的是从$n$反向过来的$maxn1$，差不多一样。

我们现在添加$0$边的最大最短路。

我们沿着最短路链枚举，设最大最短路是$ans$。当$i$和$father[i]$中有一点拥有链外子节点，$ans=max(ans,maxn1[father[i]]+maxn2[i])$，否则我们无法在这两个点之间连边，只能是跳过$father[i]$连边，则$ans=max(ans,maxn1[father[father[i]]]+maxn2[i])$，当然要保证连边的两个点都存在！

最后询问输入$k$，判断$k+ans$是否大于最短路长度，大于的话输出最短路长度，否则输出$k+ans$。

你们不可能看得懂的玄学代码：

```
#include <bits/stdc++.h>
using namespace std;

int n,m;
int v[300005];
long long dis[300006];
long long dis2[300005];
long long nxt[300005];
long long maxn[300005];
long long maxn2[300005];
long long an;
bool t;

vector<int> q[300005];
vector<long long> l[300005];

void back(int x,int father)
{
	for(int i=0;i<q[x].size();i++)
	{
		int nx=q[x][i];
		if(nx==father)continue;
		dis2[nx]=dis2[x]+l[x][i];
		back(nx,x);
	}
}

bool dfs(int x,int father)
{
    bool ok=0;
	v[x]++;
    if(x==n)
    {
        ok=1;
    }
    for(int i=0;i<q[x].size();i++)
    {
        int nx=q[x][i];
        if(nx==father)continue;
        dis[nx]=dis[x]+l[x][i];
        bool op=dfs(nx,x);
        if(op)
        	nxt[x]=nx;
        if(op==0)
            v[x]+=v[nx];
        ok|=op;
    }
    if(v[x]>2)t=1;
    maxn[x]=dis[x];
    maxn2[x]=dis2[x];
    for(int i=0;i<q[x].size();i++)
    {
    	int nx=q[x][i];
    	maxn2[x]=max(maxn2[x],maxn2[nx]);
		if(nx==nxt[x])continue;
		maxn[x]=max(maxn[x],maxn[nx]);
	}
	if(x!=n){
		if(v[x]>1||v[nxt[x]]>1){
			an=max(an,maxn[x]+maxn2[nxt[x]]);
		}
		else if(nxt[nxt[x]]!=0)
			an=max(an,maxn[x]+maxn2[nxt[nxt[x]]]);
	}
    return ok;
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
        int x,y;
		long long z;
        scanf("%d%d%lld",&x,&y,&z);
        q[x].push_back(y);
        q[y].push_back(x);
        l[x].push_back(z);
        l[y].push_back(z);
    }
    back(n,n);
    dfs(1,1);
	for(int i=1;i<=m;i++)
	{
		long long k;
		scanf("%lld",&k);
		if(k+an>dis2[1]||t==1)
			printf("%lld\n",dis2[1]);
		else
			printf("%lld\n",an+k);
	}
    return 0;
}
```

---

## 作者：lfxxx (赞：0)

你考虑分别令 $dis_{i},g_{i}$ 表示从 $i$ 到 $1,n$ 的距离，实际上你要求的是 $\max(\min_{(u,v) \not \in E}(dis_u+g_v,dis_v+g_u))$。由于可以交换边的端点顺序，不放先加上一个限制 $dis_u+g_v \leq dis_v + g_u$，也就是 $dis_u - g_u \leq dis_v - g_v$，然后问题变成 $\max_{(u,v) \not \in E}(dis_u+g_v)$，考虑按照 $dis_u - g_u$ 排序后扫描过去，维护所有 $v$ 的答案，如果当前取出的最大 $v$ 是出边之一就丢掉取下一个，考虑完再把丢掉的加回来，时间复杂度 $O(n \log n + m)$。

[代码](https://codeforces.com/contest/1016/submission/277140344)

---

## 作者：MiRaciss (赞：0)

## 题目链接

[Link.](https://www.luogu.com.cn/problem/CF1016F)

## 题解

因为是 $1$ 到 $n$ 在树上的最短路，所以一定是 $1$ 到 $n$ 这条链，我们先把链拉出来，那么链上的每一个节点可以看做挂上了剩余的不在链上的节点。

如果链上的一个节点挂着的节点超过或等于两个，那么我们可以选择在这两个之间连边，所以无论询问所给的边是什么都不会对答案产生影响。这种情况特判即可。

那么现在我们的节点就最多只会挂一个不在链上的节点了。

因为只有能连边才可能会对答案产生影响，所以考虑哪些点之间可以连边。容易发现，只有当链上的两个点相邻且他们都没有挂其他点的时候，他们不可以连边。

为了表现连边的贡献，定义 $\mathrm {dep}$ 数组，$\mathrm{dep_i}$表示从 $1$ 开始到 $i$ 的距离；定义 $\mathrm {now}$ 数组，$\mathrm{now_i}$表示从 $1$ 开始到 $i$ 的距离，如果 $i$ 挂了点，那么 $\mathrm{now_i}$ 再加上 $i$ 到它挂的点的距离。

设在 $i,j$ 间连了一条长度为 $\mathrm {sum}$ 的边$(i<j)$。

因为在 $i,j$ 连了一条边，所以构成了一个环，那么从不在链上的边走到 $n$ 的代价就为 $\mathrm {dep_n} + \mathrm {now_i} + \mathrm{now_j} - \mathrm{dep_j} \times 2 + \mathrm{sum}$。

发现除了 $\mathrm {sum}$ 以外其他东西都是固定的所以我们可以先求出来，然后再加上读入的 $\mathrm {sum}$，最后和 $\mathrm {dep_n}$ 比较一个最小值输出即可。

所以我们现在只需要考虑怎么求出$\mathrm {now_i} + \mathrm{now_j} - \mathrm{dep_j} \times 2$ 。发现我们只需要从后往前便利，再用个优先队列维护 $\mathrm{now_j} - \mathrm{dep_j} \times 2$ 的最大值即可~~其实可以单调队列但我懒~~。

### code.
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int INF=1e15;
int n,m;

struct zz{
	int u,w;
};
bool operator <(zz x,zz y){
	if(x.u==y.u) return x.w>y.w;
	return x.u<y.u; 
} 
vector<zz> v[300005];
bool f[300005];
int dep[300005],Max[300005],siz[300005];
void DFS_1(int x,int fa){
	if(x==n) f[x]=1;
	Max[x]=dep[x];siz[x]=1;
	for(const auto &qwq:v[x]) if(qwq.u^fa){
		int y=qwq.u,w=qwq.w;
		dep[y]=dep[x]+w;
		Max[x]=max(Max[x],Max[y]);
		DFS_1(y,x);
		if(f[y]) f[x]=1;
		else siz[x]+=siz[y];
	}
}
vector<int> q;
int now[300005];
void DFS_2(int x,int fa){
	q.push_back(x);now[x]=dep[x];
	for(auto qwq:v[x]) if(!f[qwq.u]) now[x]+=(Max[qwq.u]-dep[x]);
	for(auto qwq:v[x]) if(f[qwq.u]&&(qwq.u^fa)) DFS_2(qwq.u,x);
}

priority_queue<zz> qq;

signed main(){
	cin>>n>>m;
	for(int i=1,x,y,z;i<n;i++) 
		scanf("%lld%lld%lld",&x,&y,&z),v[x].push_back((zz){y,z}),v[y].push_back((zz){x,z});
	dep[1]=0;DFS_1(1,0);
	for(int i=1;i<=n;i++){
		if(f[i]) if(siz[i]>=3){
			for(int k=1;k<=m;k++) printf("%lld\n",dep[n]); return 0;
		}
		
	}
	DFS_2(1,0);
	int ans=now[1]+now[n]-dep[n]*2;
	
	for(int i=q.size()-1;i>=0;i--){
		zz qwq;
		if(!qq.size()) goto Fuck;
		qwq=qq.top();
		if(qwq.w==q[i+1]&&siz[qwq.w]<2&&siz[q[i]]<2){
			qq.pop();
			if(!qq.size()){ qq.push(qwq);goto Fuck; }
			else{ zz qaq=qq.top();qq.push(qwq);qwq=qaq; }
		}
		ans=max(ans,qwq.u+now[q[i]]);
		Fuck:;qq.push((zz){now[q[i]]-dep[q[i]]*2,q[i]});
	}
	
	for(int i=1,x;i<=m;i++){
		scanf("%lld",&x),printf("%lld\n",min(dep[n],dep[n]+ans+x));
	}
	return 0;
}
```
哦对了，这份代码只能在私下用，在西西弗的比赛中用会被封号的/jk


---

