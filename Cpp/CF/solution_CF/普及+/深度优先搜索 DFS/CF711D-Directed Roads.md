# Directed Roads

## 题目描述

ZS the Coder and Chris the Baboon has explored Udayland for quite some time. They realize that it consists of $ n $ towns numbered from $ 1 $ to $ n $ .

There are $ n $ directed roads in the Udayland. $ i $ -th of them goes from town $ i $ to some other town $ a_{i} $ ( $ a_{i}≠i $ ). ZS the Coder can flip the direction of any road in Udayland, i.e. if it goes from town $ A $ to town $ B $ before the flip, it will go from town $ B $ to town $ A $ after.

ZS the Coder considers the roads in the Udayland confusing, if there is a sequence of distinct towns $ A_{1},A_{2},...,A_{k} $ ( $ k&gt;1 $ ) such that for every $ 1<=i&lt;k $ there is a road from town $ A_{i} $ to town $ A_{i+1} $ and another road from town $ A_{k} $ to town $ A_{1} $ . In other words, the roads are confusing if some of them form a directed cycle of some towns.

Now ZS the Coder wonders how many sets of roads (there are $ 2^{n} $ variants) in initial configuration can he choose to flip such that after flipping each road in the set exactly once, the resulting network will not be confusing.

Note that it is allowed that after the flipping there are more than one directed road from some town and possibly some towns with no roads leading out of it, or multiple roads between any pair of cities.

## 说明/提示

Consider the first sample case. There are $ 3 $ towns and $ 3 $ roads. The towns are numbered from $ 1 $ to $ 3 $ and the roads are ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/bbf0ca4cbc925b1d673ae3b61e28811a0ccacf51.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/f1138b32236a89525fad2b8c02b9cbfbd546dfad.png), ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/43ec097315a08660c95bbf7f709c76c8ce606dd6.png) initially. Number the roads $ 1 $ to $ 3 $ in this order.

The sets of roads that ZS the Coder can flip (to make them not confusing) are $ {1},{2},{3},{1,2},{1,3},{2,3} $ . Note that the empty set is invalid because if no roads are flipped, then towns $ 1,2,3 $ is form a directed cycle, so it is confusing. Similarly, flipping all roads is confusing too. Thus, there are a total of $ 6 $ possible sets ZS the Coder can flip.

The sample image shows all possible ways of orienting the roads from the first sample such that the network is not confusing.

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711D/329f4376794f6e7da8ed8bb533f70d300253c072.png)

## 样例 #1

### 输入

```
3
2 3 1
```

### 输出

```
6
```

## 样例 #2

### 输入

```
4
2 1 1 1
```

### 输出

```
8
```

## 样例 #3

### 输入

```
5
2 4 2 5 3
```

### 输出

```
28
```

# 题解

## 作者：ChthollyTree (赞：14)

n条边 n个点

显然是基环树

由于不一定联通，可能有多个基环树

要求有向后不能有环

设每个环的点数为$w_i$

对于一条不在环上的边，方向随便取

总共$2^{n - \sum{wi}}$种方案

再考虑环上

对于一个有$w_i$个点的环

如 1 -- 2 -- 3 .... -- $w_i$ -- 1

( -- 表示边 ， -> 和 <- 表示有向边)
那么 只有


1 -> 2 -> 3 .... -> $w_i$ -> 1

和

1 <- 2 <- 3 .... <- $w_i$ <- 1

这种连边方式会形成环，不合法

所以每一个环有 $2^{w_i} -2 $种方案

所以总方案就是

$2^{n - \sum{wi}} * \prod{2^{w_i} -2}$ 种方案

下面是代码

```
#include<bits/stdc++.h>
using namespace std;

#define MAXN 400005
#define LL long long
#define mo 1000000007 

int n,m;
int a[MAXN];
int c[MAXN];
struct aa
{
	int x,y,ls;
}b[MAXN];
int cnt;
int t[MAXN];
int h[MAXN];
int nn,mm; 

void jb(int x,int y)//建边 （建边的首字母不要误解）
{
	cnt ++;
	b[cnt].x = x;
	b[cnt].y = y;
	b[cnt].ls = t[x];
	t[x] = cnt;
} 

void rd()
{
	scanf("%d",&n);
	for(int i = 1; i <= n; i ++) {
		scanf("%d",&a[i]);
		jb(i,a[i]);
		jb(a[i],i);
	} 
}

int an = 0;
void dfs(int x,int h)//找环
{
	if(c[x])
	{
		an =  h - c[x];
		return;
	}
	c[x] = h;
	dfs(a[x],h+1);
}

bool d[MAXN];

void dff(int x)
{
	d[x] = 1;
	for(int i = t[x]; i != 0; i = b[i].ls)
	{
		if(!d[b[i].y]) {
			dff(b[i].y); 
		}
	}
}

LL kasumi(LL x,LL y) {//快速幂（好像可以不用快速幂的）
	LL ans = 1;
	for( ; y > 0; x = x*x%mo, y >>= 1)
	if(y&1) ans = ans*x%mo;
	return ans;
}

int main()
{
	rd();
	m = 1;
	for(int i = 1; i <= n; i ++)
	{
		if(!d[i]) {
			dff(i);
			nn ++;
			an = 0;
			dfs(i,1);
			h[nn] = an;
			mm += h[nn];
		}
	}
	LL ans = kasumi(2,n - mm);
	for(int i = 1; i <= nn; i ++)
	{
		ans = ans*(kasumi(2,h[i]) - 2) %mo;
	} 
	cout<<ans;
	return 0;
} 
/*
6
2 3 2
5 4 5
*/
```

---

## 作者：Coros_Trusds (赞：6)

看到 CCF 的考纲里有基环树于是赶紧到 [这篇 Blog](https://www.luogu.com.cn/blog/ShadderLeave/ji-huan-shu-bi-ji#) 去学习了下。

$N$ 个点 $N$ 条边，考虑基环树。

首先，看到这道题的问法就不同寻常：

> 求使得图中不出现环的方案数。

感觉有些不对劲，一般的题目大多是问你出现环的方案数，并且这样也好算亿些。

诶，那我们直接拿总的方案数减去出现环的方案数不就好了吗？

答案 = 总方案数 - 出现环的方案数

总方案数 ： 一共有 $N$ 条边，每条边可以任选方向，故共有 $2^N$ 中方案。

出现环的方案数：想一想：一个环，不一定要每个点的出入度相等，但一定需要满足什么？

比如说有一个环上有两条有向边 $(u_1,v_1)$ 和 $(u_2,v_2)$，那么 $u_1$ 一定不能也是 $u_2$ 并且 $v_1$ 一定不能也是 $v_2$。

**也就是环里任意两条边的方向不能相反。**

一颗基环树的方案数就是 $2^{n-pts}\times 2$，其中 $pts$ 是环上边的个数，乘 $2$ 是因为每条边有两个方向可以选择。

合法方案数就是 

$$2^n - 2^{n-pts}\times2$$

把 $2^{n-pts}$ 提出可得：

$$=2^{n-pts}\times (2^{pts} - 2)$$

设有 $num$ 棵基环树（因为图可能不连通），此时方案数为：

$$2^{n-\sum\limits_{i = 1}^{num}pts_i} \times \prod\limits_{i=1}^{num}(2^{pts_i} - 2)$$

代码：

```cpp
//2021/8/2

#include <cstdio>

#define int long long

using namespace std;

const int ma=200005;

const int mod=1e9+7;

struct Node
{
	int v;
	
	int nxt;
};

Node node[ma<<1];

int head[ma];

int dep[ma],link[ma];//分别记录深度和环的大小 

int vis[ma];

int idx,sum,top;

int n;

inline void add(int u,int v)
{
	node[++idx].v=v;
	
	node[idx].nxt=head[u];
	
	head[u]=idx;
}

inline int ksm(int n,int m,int p)
{
	int res=1;
	
	for(;m;m>>=1)
	{
		if(m&1)
		{
			res=res*n%p;
		}
		
		n=n*n%p;
	}
	
	return res%p;
}

inline void dfs(int now,int depth)
{
	dep[now]=depth;
	
	vis[now]=1;
	
	for(register int i=head[now];i;i=node[i].nxt)
	{
		int v=node[i].v;
		
		if(vis[v]==false)
		{
			dfs(v,depth+1);
		}
		
		else if(vis[v]==1)
		{
			link[++top]=dep[now]-dep[v]+1;
			
			sum+=link[top];
		}
	}
	
	vis[now]=2;//弃之不用 
}

#undef int

int main(void)
{
	#define int long long
	
	scanf("%lld",&n);
	
	for(register int i=1;i<=n;i++)
	{
		int x;
		
		scanf("%lld",&x);
		
		add(i,x);
	}
	
	for(register int i=1;i<=n;i++)
	{
		if(dep[i]==0)//没有 dfs 到，即不连通 
		{
			dfs(i,1);//再次 dfs 这一棵基环树 
		} 
	}
	
	int mul=1;
	
	for(register int i=1;i<=top;i++)
	{
		mul=mul*(ksm(2,link[i],mod)-2)%mod;
	}
	
	int lastans=mul;
	
	lastans*=ksm(2,n-sum,mod);
	
	printf("%lld\n",lastans%mod);
	
	return 0;
} 

#undef int
```

---

## 作者：reyik (赞：4)

基环外向树（但没有DP）

题目大意：

$n$个点$n$条边的图，有多少种方法给边定向后没有环出现

用$w$数组存储每一个环上的节点个数

那么对于不在环上的点，就是两种情况，总数是$2^{n-\sum{w[i]}}$种

那么对于在环上的点，每一个点同样有两种情况，但对于每一个环，要减2，因为全是顺时针或逆时针会出现环。

总数是$2^{n-\sum{w[i]}}*\prod{2^{w[i]}-2}$

```
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const int maxn=1e6+10,mod=1e9+7;
struct Edge{
	int to,nxt;
}e[maxn];
int head[maxn],w[maxn],top=0,mi2[maxn],dep[maxn],cnt=0,n,vis[maxn];
int mul(int x,int y) {
	return 1ll*x*y%mod; 
}
void addedge(int x,int y) {
	++cnt;
	e[cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
void dfs(int u,int d) {
	dep[u]=d;vis[u]=1;
	for (int i=head[u];~i;i=e[i].nxt) {
		int v=e[i].to;
		if(!vis[v]) dfs(v,d+1);
		else if(vis[v]==1) w[++top]=dep[u]-dep[v]+1;
	}
	vis[u]=2;
}
int main() {
	memset(head,-1,sizeof(head));
	scanf("%d",&n);
	mi2[0]=1;
	for (int i=1;i<=n;++i) mi2[i]=mul(2,mi2[i-1]);
	for (int i=1;i<=n;++i) {
		int x;scanf("%d",&x);
		addedge(i,x);
	}
	for (int i=1;i<=n;++i) if(!dep[i]) dfs(i,1);
	int sum=0,res=1;
	for (int i=1;i<=top;++i) {
		sum+=w[i];
		res=mul(res,mi2[w[i]]-2+mod);
	}
	printf("%d\n",mul(res,mi2[n-sum]));
	return 0;
}
```

---

## 作者：eEfiuys (赞：3)

题目：[CF711D](https://www.luogu.com.cn/problem/CF711D)

### 判断图的类型：

由于本题特殊的输入格式，我们可以判断出，这是**基环树森林**。**先只考虑一棵基环树**。

------------

### 计算方案数：

首先我们可以转化题意，求出**总方案数减去构成环的方案数**。设共有 $a$ 条边，环上有 $b$ 条边，则不在环上的边有 $a-b$ 条。

- 总方案数为 $2^a$。
- 环上边的方向必须**相同**，因此 $2$ 种方向中，分别有 $2^{a-b}$ 种方案。

则不构成环的方案数为 $2^a-2\times2^{a-b}=2^a-2^{a-b+1}$。

------------

### 统计边数：

由于是基环树，因此**将边数转为便于统计的点数**。

- 总共的边数 `dfs` 即可。
- 考虑环。因为不需要知道有哪些点，所以这里提供一种简单的方法。
	- 记 $siz_u$ 为 $u$ 是第几个被访问到的。`dfs` 中传入参数 $cnt$ 即可统计。
   - 当重复访问时，$cnt-siz_u$ 即为环上的点数（**因为建无向边，所以需要取 $\max$**）。
   - ~~非常氵的~~证明：因为这是唯一的环，所以重复访问间隔最多的一定是从环上走过来的。

------------

### 最终答案：

根据乘法原理，基环树森林中每一棵基环树的答案乘起来即可。**记得开 `long long`，并且先模 $mod$，再加 $mod$，然后还得模 $mod$。**

------------

## Code Time

```cpp
#include<bits/stdc++.h>
using namespace std;
#define un unsigned
#define ll long long
#define int long long
int read(){/*快读*/}
void print(int x,char ch=0){/*快写*/}
const int N=2e5+5;
int inf=(1ll<<31)-1,mod=1e9+7;
int n;
vector<int>g[N];
bool vis[N];//其实有了siz[N]，vis[N]可以省略，但是蒟蒻刚开始没想到统计的方法/kk
int tot,a[N],b[N],siz[N],ans=1;
void dfs(int u,int cnt){
	if(vis[u]){b[tot]=max(b[tot],cnt-siz[u]);return;}
	siz[u]=cnt;
	vis[u]=1,a[tot]++;
	for(int i=0;i<g[u].size();i++)dfs(g[u][i],cnt+1);
}
int ksm(int a,int b){
	int num=1;
	while(b){
		if(b&1)(num*=a)%=mod;
		(a*=a)%=mod;
		b>>=1;
	}
	return num;
}//快速幂
signed main(){
	n=read();
	for(int i=1;i<=n;i++){
		int t=read();
		g[i].push_back(t),g[t].push_back(i);
	}
	for(int i=1;i<=n;i++)
		if(!vis[i])//一棵新的基环树
			tot++,dfs(i,0)/*,print(a[tot],' '),print(b[tot],'\n')*/;
	for(int i=1;i<=tot;i++)ans=(ans*((ksm(2,a[i])-ksm(2,a[i]-b[i]+1))%mod)%mod+mod)%mod;//气急败坏地膜
	print(ans,'\n');
	return 0;
}
```

---

## 作者：Starlight237 (赞：2)

$\text{tarjan}$ 是可以对无向图找环的。

推结论的过程其他题解都已经阐明，此处不再赘述，仅叙述一下使用 $\text{tarjan}$ 对无向图找环的方法和注意事项。

- 由于在无向图中，任何一个连通的局部都构成强连通分量，故采用普通的 $\text{tarjan}$ 就会出现问题。
- 究其原因，任何两点之间都构成了一个环。因此永远可以沿原路返回。
- 我们可以在 `tarjan` 递归函数中加入一个参数 `Fa` 表示当前是从哪个点过来的，往后走的时候就不能再原路折回。
- 此时求得的即是无向图的环。

注意事项：

1. 由于题目可能有重边，故应当 `sort` 一下，对于重边不计入总边数。
2. 容易知道，一个无自环的图中，任何一个的环的边数都等于点数。故我们可以统计环中的点数。
3. 最后统计环的时候，若 `rt[i] == i && siz[i] > 1`，则构成一个环。其中 `rt[i]` 表示 i 所在强连通分量的代表节点。注意，不可以在 `tarjan` 函数中那个 `if` 语句里面更新答案，因为此时可能找到的并不是最终的环，而是一个非简单环的局部，甚至只有一个点。事实上，如果在 `tarjan` 函数中那个 `if` 语句里面更新答案，则样例 2 会输出 `14`。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
extern "C" {
namespace io{
#define BUFS 100000
	static char in[BUFS], *p = in, *pp = in, out[BUFS << 7], *q = out, ch[20], *t = ch;
#define gc() (p == pp && (pp = (p = in) + fread(in, 1, BUFS, stdin), p == pp) ? EOF : *p++)
	inline int read() {
		reg int x = 0; reg char ch, f = 0;
		while (!isdigit(ch = gc())) f |= ch == '-';
		while (isdigit(ch)) x = (x << 1) + (x << 3) + (ch ^ 48), ch = gc();
		return f ? -x : x;
	}
	inline void write(int x, char sp) {
		x || (*q++ = 48), x < 0 && (*q++ = '-', x = -x);
		while (x) *t++ = x % 10 + 48, x /= 10;
		while (t != ch) *q++ = *--t;
		*q++ = sp;
	}
	inline void flush() {fwrite(out, 1, q - out, stdout);}
}}
#define rd io :: read
#define wt io :: write
const int N = 400001, mod = 1e9 + 7;
int n, m, tot, tim, head[N], dfn[N], vis[N], pw[N], ans = 1, rt[N], siz[N], low[N];
struct Eg{int u, v;}EG[N << 1];
inline bool operator<(const Eg&a, const Eg&b) {return a.u != b.u ? a.u < b.u : a.v < b.v;}
struct Edge{int v, nxt;} eg[N << 1];
inline void addedge(int u, int v) {eg[++tot] = Edge{v, head[u]}, head[u] = tot;}
int stk[N], *tp = stk;
void tarjan(int x, int Fa) {
	dfn[x] = low[x] = ++tim, *++tp = x, vis[x] = 1;
	for (reg int i = head[x], v; i; i = eg[i].nxt)
		(v = eg[i].v) != Fa &&(
			!dfn[v] ? tarjan(v, x), low[x] = min(low[x], low[v]) :
			(vis[v] && (low[x] = min(low[x], dfn[v])))
		);
	if (low[x] == dfn[x]) {
		reg int y;
		do
			y = *tp, rt[y] = x, vis[y] = 0, x != y && (siz[x] += siz[y]), --tp;
		while (x != y);
	}
}
int main() {
	n = rd();
	pw[0] = 1;
	for (reg int i = 1; i <= n; ++i) pw[i] = ((long long)pw[i - 1] << 1)%mod;
	for (reg int i = 1, x; i <= n; ++i) x = rd(), EG[i] = Eg{min(i, x), max(i, x)};
	sort(EG + 1, EG + n + 1);
	for (reg int i = 0; i < n; ++i)
		!(EG[i].u == EG[i + 1].u && EG[i].v == EG[i + 1].v) && (addedge(EG[i + 1].u, EG[i + 1].v), addedge(EG[i + 1].v, EG[i + 1].u), ++m, 0);
	for (reg int i = 1; i <= n; ++i) siz[i] = 1;
	for (reg int i = 1; i <= n; ++i) dfn[i] || (tarjan(i, 0), 0);
	for (reg int i = 1; i <= n; ++i)
		rt[i] == i && siz[i] > 1 && (ans = (long long)ans * (pw[siz[i]] - 2 + mod) % mod, m -= siz[i]);
	ans = (long long)ans * pw[m] % mod;
	wt(ans, '\n');
	io :: flush();
	return 0;
}

```

---

## 作者：D2T1 (赞：1)

[$\color{blue}{\text {pwp }~{\to\textbf{My blog}\gets}}~\text{qwq}$](https://www.luogu.com.cn/blog/390770/blogcenter)

纪念一下学会基环树~

## 题意

[题目链接](https://www.luogu.com.cn/problem/CF711D)

有 $n$ 个点和 $n$ 条无向边，第 $i$ 条边从 $i$ 连到 $a_i$。每条边需要指定一个方向（无向边变为有向边）。问**有多少种指定方向的方案使得图中不出现环**。

## 题解

$n$ 个点和 $n$ 条边，就是所谓的**基环树**，一棵基环树中**有且仅有一个环**，但如果不连通且每个连通块的点数都等于边数就是多个基环树组成的**森林**。

而题意给的是每个点都有一条边，所以符合**基环树森林的定义**。

------------

这道题怎么解呢？

首先考虑一种情况：只有一棵基环树（连通）。那么只有基环树上那个**环上的边添加方向后仍为环**时才会形成环，所以成环方案数为 $2^{n-len}*2$（其中 $len$ 为环上的边数）

![](https://cdn.luogu.com.cn/upload/image_hosting/t4rd1uyy.png)

上图为成环方案 图片来自 @_Leaving 博客

而合法方案是 $2^n-2^{n-len}*2$，两项提出 $2^{n-len}$ 得 $2^{n-len}*(2^{len}-2)$。

所以，如果是基环树森林的话，最终的解为 

$$2^{n-\sum\limits_{i=1}^{w}len_i}\prod_{i=1}^{w}(2^{len_i}-2)$$

其中 $w$ 为连通块（基环树）个数，$len$ 数组为每个连通块（基环树）中环上的边数。

------------

好了，现在的重点是：怎么求基环树的环？

我采用的方法是：**并查集+BFS**，使用并查集合并每一条边的两个节点，当出现一条边，它的两个节点都在同一个集合时，这条边就在环上。然后从一个节点进行 BFS 到另一个节点，经过的路径就是完整的环。（这里注意先BFS再连边，不然可能 BFS 经过的是刚连的那条边）。

而每发现一条环上的边就进行一次 BFS 即可求出所有环，最后如上带入公式即可。

## 代码

```cpp
//CF711D
#include <cstdio>
#include <vector>
#include <queue>
typedef long long ll;
using namespace std;
const int N=2e5+10,mod=1e9+7;

int fa[N],len[N],tot,level[N],n,a;
//fa：并查集记录祖先
//len：记录每个环的边数 tot：记录环数
//level：BFS 时的层次序
//n：如题意 a：工具变量
ll ans=1,sum=0;//ans,sum：求答案用
vector<int> E[N];//存图
queue<int> q;//bfs用

inline int gf(int x){ return x==fa[x] ? x :fa[x]=gf(fa[x]); }
inline void bfs(int s,int e){
	q.push(s); level[s]=0;
	while(!q.empty()){
		a=q.front(); q.pop();
		if(a==e){ len[++tot]=level[e]+1; return; }
		for(int i=0; i<E[a].size(); ++i)
			if(!level[E[a][i]]) level[E[a][i]]=level[a]+1, q.push(E[a][i]);
	}
}
inline ll qpow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1) ans=ans*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ans;
}

int main(){
	for(int i=1; i<N; ++i) fa[i]=i;
	
	scanf("%d",&n);
	for(int i=1; i<=n; ++i){
		scanf("%d",&a);
		if(gf(i)==gf(a)) bfs(i,a);//发现一条环上的边，进行 BFS
		else fa[gf(i)]=gf(a);//否则并查集合并
		E[i].push_back(a),E[a].push_back(i);
	}
	
   //统计答案
	for(int i=1; i<=tot; ++i) ans=ans*(qpow(2,len[i])-2)%mod,sum+=len[i];
	ans=ans*qpow(2,n-sum)%mod;
	printf("%lld",ans);
	return 0;
}

//qwq
```

## 推荐博客

[基环树笔记 by _Leaving](https://www.luogu.com.cn/blog/ShadderLeave/ji-huan-shu-bi-ji)

---

## 作者：Hexarhy (赞：1)

### Preface

虽说是基环树，但感觉零基础人思考起来还是蛮容易的。

可以当作图论简单思维题~~基环树味淡~~。

### Solution

**慢慢读题很重要。** 稍微熟悉的话不难发现给定的是一个基环树。

对于一个 $n$ 条边的连通子图中，节点数为 $t$ 的环，能成环的方案只能是所有边指向同一方向，也就是只有 $2$ 种方案会形成环，即合法方案数为 $2^t-2$。

剩下的边方向就随意，方案数为 $2^{n-t}$。

那么一个连通子图的总方案就为 $2^{n-t}(2^t-2)$

每个连通子图都是互不影响的，那么整张图的方案数显然为：

$$\prod 2^{n_i-t_i}(2^{t_i}-2)$$

把其中一项提出来就可以得到大部分题解的式子：

$$2^{n-\sum t_i}\prod(2^{t_i}-2)$$

快速幂计算即可。

### Code

```cpp
void dfs(cint u,cint depth)//常见的找环方法
{
	dep[u]=depth;
	visit[u]=1;
	for(const auto& v:edge[u])
	{
		if(!visit[v])	dfs(v,depth+1);
		else if(visit[v]==1)	ring.emplace_back(dep[u]-dep[v]+1);//记录环的大小
	}
	visit[u]=2;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		int x;cin>>x;
		edge[i].emplace_back(x);
	}
	for(int i=1;i<=n;i++)
		if(!dep[i])	dfs(i,1);
	cint sum=accumulate(ring.begin(),ring.end(),0);//计算 sigma ti
	for(const auto& t:ring)	res=res*(qpow(2,t)-2+MOD)%MOD;
	ll ans=res*qpow(2,n-sum)%MOD;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：AIskeleton (赞：0)

### 题意

有 $n$ 个点和 $n$ 条边，第 $i$ 条边从 $i$ 连到 $a_i$。每条边需要指定一个方向（无向边变为有向边）。问有多少种指定方向的方案使得图中不出现环。

### 题解

> $n$ 个点和 $n$ 条边。

所以是**基环树**。

先只考虑**单棵基环树**的情况。
##### 
> 使得图中不出现环。

基环树环外的边对题目没有影响，既不会影响当前的环，也不会增加新的环。

如果基环树的环上的任意一条边与其他的边的方向不同，就不会产生环。

所以在所有的方案中，只有**环上边的方向全部相同**的情况是会产生环的。

假设环上边的条数为 $m$，那么此时的产生环的方案数就是 $2\times2^{n-m}$ 种，不产生环的方案数就是 $(2^m+2)\times2^{n-m}$ 种。

因为题目不保证图联通，所以考虑基环树森林的情况。

所以对于基环树森林中的每一棵基环树，找出其中的环，都像上面那样计算，将结果相加就是答案。

所以最终的答案是： $ 2^{n- \sum m} \prod (2^m-2) $

### 代码：

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=3e5;int n,m=1e9+7,tot,vis[N],si[N],a[N],b[N],ans=1;
struct edge{int v,nt;}e[N<<1];
int fir[N],cnt;
void add(int u,int v){e[++cnt].v=v;e[cnt].nt=fir[u];fir[u]=cnt;}
int k(int a,int b){int s=1;while(b){if(b&1)(s*=a)%=m;(a*=a)%=m;b>>=1;}return s;}
void dfs(int u,int c){
	if(vis[u]){b[tot]=max(b[tot],c-si[u]);return;}
	si[u]=c;vis[u]=1;a[tot]++;
	for(int i=fir[u];i;i=e[i].nt)dfs(e[i].v,c+1);
}signed main(){
	std::ios::sync_with_stdio(false);
	cin>>n;for(int i=1,x;i<=n;i++)	cin>>x,add(i,x),add(x,i);
	for(int i=1;i<=n;i++)
		if(!vis[i])	tot++,dfs(i,0);
	for(int i=1;i<=tot;i++)
		ans=(ans*((k(2,a[i])-k(2,a[i]-b[i]+1))%m)%m+m)%m;
	cout<<ans<<endl;return 0;
}
```

---

## 作者：xixike (赞：0)

[博客食用更佳](https://www.cnblogs.com/xixike/p/15497096.html)

# Description

> [洛谷传送门](https://www.luogu.com.cn/problem/CF711D)

# Solution

看到 $n$ 个点 $n$ 条边，显然的基环树（可能是基环树森林），所以我们对于环上的点和非环上的点分别处理。

假设一共有 $cnt$ 个环，每个环上有 $d_i$ 个点，我们来分类讨论一下：

- 对于环上的点，我们发现只有两种情况会产生环，即

  - $1 \rightarrow 2 \rightarrow 3 \rightarrow ··· \rightarrow d_i - 1 \rightarrow d_i \rightarrow 1$
  - $d_i \rightarrow d_i - 1 \rightarrow ··· \rightarrow 3 \rightarrow 2 \rightarrow 1 \rightarrow d_i$

  所以我们用总情况数减去 $2$即可。方案数：

  $$ans = \prod\limits_{i = 1}^{cnt}{(2^{d_i} - 2)}$$

- 对于非环上的点，我们发现不论朝哪个方向连，都不会影响是否会产生环，所以方案数为 $2^{非环上点的个数}$：

  $$ans = 2^{n - \sum\limits_{i = 1}^{cnt}d_i}$$

至此，我们就讨论完了（事实上还是很简单的），总结一下：

$$ans = \prod\limits_{i = 1}^{cnt}{(2^{d_i} - 2)} \times 2^{n - \sum\limits_{i = 1}^{cnt}d_i}$$

那么如何找环呢？我这里写了个 Tarjan 缩点，大小大于 2 的强连通分量就是环（感觉用牛刀杀鸡了……不管了）。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#define ll long long

using namespace std;

const ll mod = 1e9 + 7;
const ll N = 2e5 + 10;
ll n;
struct node{
    ll v, nxt;
}edge[N];
ll head[N], tot;
ll dfn[N], low[N], tim;
ll stk[N], top, t[N];
ll cnt, siz[N];

inline void add(ll x, ll y){
    edge[++tot] = (node){y, head[x]};
    head[x] = tot;
}

void tarjan(ll x){
    low[x] = dfn[x] = ++tim;
    stk[++top] = x;
    t[x] = 1;
    for(ll i = head[x]; i; i = edge[i].nxt){
        ll y = edge[i].v;
        if(!dfn[y])tarjan(y), low[x] = min(low[x], low[y]);
        else if(t[y]) low[x] = min(low[x], dfn[y]);
    }
    if(low[x] == dfn[x]){
        cnt++;
        do{
            siz[cnt]++;
            t[stk[top--]] = 0;
        }while(stk[top + 1] != x);
    }
}

inline ll qpow(ll a, ll b){
    ll res = 1;
    while(b){
        if(b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}

signed main(){
    scanf("%lld", &n);
    for(ll i = 1, x; i <= n; ++i){
        scanf("%lld", &x);
        add(i, x);
    }
    for(ll i = 1; i <= n; ++i)
        if(!dfn[i]) tarjan(i);
    ll sum = 0, ans = 1;
    for(ll i = 1; i <= cnt; ++i)
        if(siz[i] > 1) ans = ans * (qpow(2, siz[i]) - 2 + mod % mod) % mod, sum += siz[i];
    ans = ans * qpow(2, n - sum) % mod;
    printf("%lld\n", ans);
    return 0;
}
```

# End

---

## 作者：某珂学的超OIer (赞：0)

# CF711D Directed Roads 题解
## 题目大意

有 $n$ 个点和 $n$ 条边的 **森林** ，第 $i$ 条边从 $i$ 连到 $a_i$ （没有自环）

每条边需要指定一个方向（无向边变为有向边）

问有多少种指定方向的方案使得图中不出现环

## 解题思路

**考虑重边**（由重边构成的环也是环）

首先珂以注意以下几点：

- 不一定只有一个连通块
- 每个连通块都是一个基环树

考虑没有环的 $n-1$ 条边的树，那么显然珂以证明，方案数为 $2^{n-1}$ 

考虑一个基环树，在环上的边显然存在两种情况形成环（顺着和逆着），并且此时不在环上的边仍然珂以乱动

所以记这棵基环树的全部边为 $\text{sum}$ ，环所包含的边为 $\text{cnt}$ ，那么珂以发现，这棵基环树的方案数为：
$$
2^{\text{sum}}-2\times(2^{\text{sum}-\text{cnt}})=2^{\text{sum}}-2^{\text{sum}-\text{cnt}+1}
$$
由于在基环树中，边数等于点数，以及在一个环中，边数也等于点数，所以珂以用点数代替边数

多个基环树的方案数根据乘法原理计算乘起来即可

## 代码

```cpp
#include<queue>
#include<cstdio>
#include<vector>
#define int long long
#define MOD 1000000007
using namespace std;
int ans=1;
int n,cnt,sum;
int in[200001];
vector<int> G[200001];
int FastPow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1)
        {
            res*=x;
            res%=MOD;
        }
        x*=x;
        x%=MOD;
        y>>=1;
    }
    return res%MOD;
}
void toposort()
{
    queue<int> q;
    for(int i=1;i<=n;i++)
    {
        if(in[i]==1)
        {
            q.push(i);
        }
    }
    while(q.size())
    {
        int u=q.front();
        q.pop();
        for(int i=0;i<G[u].size();i++)
        {
            int v=G[u][i];
            if(in[v]>1)
            {
                in[v]--;
                if(in[v]==1)
                {
                    q.push(v);
                }
            }
        }
    }
}
void dfs(int u)
{
    sum++;
    if(in[u]==2)
    {
        cnt++;
    }
    in[u]=-114514;
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i];
        if(in[v]!=-114514)
        {
            dfs(v);
        }
    }
}
signed main()
{
    scanf("%lld",&n);
    for(int u=1,v;u<=n;u++)
    {
        scanf("%lld",&v);
        in[u]++;
        in[v]++;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    toposort();
    for(int i=1;i<=n;i++)
    {
        if(in[i]!=-114514)
        {
            sum=0;
            cnt=0;
            dfs(i);
            int k=(FastPow(2,sum)-FastPow(2,sum-cnt+1)+MOD)%MOD;
            ans*=k;
            ans%=MOD;
        }
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：C_S_X_ (赞：0)

对于森林中的某一棵基环树，有可能使其出现环的方案必定是使得这个唯一的环成为环，其他不在环上的边可以任意方向。

假设这个基环树的大小为size，其环的大小为ringsize，则它的方案就是

pow（2，size - ringsize）* ( pow ( 2 , ringsize ) - 2 ) 

pow（2，size - ringsize）就是其他边可以随便方向

pow ( 2 , ringsize ) - 2 就是环上的边随便方向减去两个非法情况（顺时针和逆时针）

由于每棵基环树相对独立，所以在统计答案时累乘即可
```cpp
#include<bits/stdc++.h>
#define N 3000000
#define MOD 1000000007
using namespace std;
long long n,tmp,tot=0,first[N],nxt[N<<1];
long long vis[N],depth[N],ringsize,size,Ans=1;
struct Edge
{
	long long u,v;
}edge[N<<1];
long long qpow(long long a,long long b)
{
	long long ret=1;
	while (b)
	{
		if (b&1) ret=ret*a%MOD;
		b>>=1;
		a=a*a%MOD;
	}
	return ret;
}
void Add(long long u,long long v)
{
	tot++;
	nxt[tot]=first[u];
	first[u]=tot;
	edge[tot]=(Edge){u,v};
	return;
}
void DFS(int u,int fa,int dep)
{
	if (!ringsize&&vis[u])
	{
		if (dep-depth[u]) ringsize=dep-depth[u];
		else ringsize=2;
        //这里的判断是防止样例2中的情况，1连2，2连1，这是一个大小为2的环，但是需要特判
		return;
	}
	else if (vis[u]) return;
	depth[u]=dep;
	vis[u]=1;
	size++;
	for (int j=first[u];j!=-1;j=nxt[j])
	{
		int v=edge[j].v;
		if (v==fa) continue;
		DFS(v,u,dep+1);
	}
	return;
}
int main()
{
	freopen("testdata.in","r",stdin);
	memset(first,-1,sizeof(first));
	scanf("%lld",&n);
	for (long long i=1;i<=n;i++)
	{
		scanf("%lld",&tmp);
		Add(i,tmp);
		Add(tmp,i);
	}
    for (long long i=1;i<=n;i++) if (!vis[i])
    {
    	ringsize=size=0;
    	DFS(i,0,1);
    	Ans=((Ans*(qpow(2,ringsize)-2)%MOD+MOD)*qpow(2,size-ringsize))%MOD;
	}
	printf("%lld\n",Ans);
	return 0;
}
```

---

