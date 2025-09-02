# Weird journey

## 题目描述

Little boy Igor wants to become a traveller. At first, he decided to visit all the cities of his motherland — Uzhlyandia.

It is widely known that Uzhlyandia has $ n $ cities connected with $ m $ bidirectional roads. Also, there are no two roads in the country that connect the same pair of cities, but roads starting and ending in the same city can exist. Igor wants to plan his journey beforehand. Boy thinks a path is good if the path goes over $ m-2 $ roads twice, and over the other $ 2 $ exactly once. The good path can start and finish in any city of Uzhlyandia.

Now he wants to know how many different good paths are in Uzhlyandia. Two paths are considered different if the sets of roads the paths goes over exactly once differ. Help Igor — calculate the number of good paths.

## 说明/提示

In first sample test case the good paths are:

- $ 2→1→3→1→4→1→5 $ ,
- $ 2→1→3→1→5→1→4 $ ,
- $ 2→1→4→1→5→1→3 $ ,
- $ 3→1→2→1→4→1→5 $ ,
- $ 3→1→2→1→5→1→4 $ ,
- $ 4→1→2→1→3→1→5 $ .

There are good paths that are same with displayed above, because the sets of roads they pass over once are same:

- $ 2→1→4→1→3→1→5 $ ,
- $ 2→1→5→1→3→1→4 $ ,
- $ 2→1→5→1→4→1→3 $ ,
- $ 3→1→4→1→2→1→5 $ ,
- $ 3→1→5→1→2→1→4 $ ,
- $ 4→1→3→1→2→1→5 $ ,
- and all the paths in the other direction.

Thus, the answer is $ 6 $ .

In the second test case, Igor simply can not walk by all the roads.

In the third case, Igor walks once over every road.

## 样例 #1

### 输入

```
5 4
1 2
1 3
1 4
1 5
```

### 输出

```
6```

## 样例 #2

### 输入

```
5 3
1 2
2 3
4 5
```

### 输出

```
0```

## 样例 #3

### 输入

```
2 2
1 1
1 2
```

### 输出

```
1```

# 题解

## 作者：Gary818 (赞：5)

# CF788B [Weird Jouney]  
好久不写题解了，主博客同步发表[blogs](https://www.cnblogs.com/rui-4825/p/13644614.html)

[原题目地址](http://codeforces.com/problemset/problem/788/B)

一句话题意：总共有$n$个节点，$m$条路径，要求其中$m-2$条路径走两遍，剩下$2$条路径仅走一遍，问不同的路径总数有多少，如果仅走一遍的两条边不同则将这两条路径视为不同。

## Solution

直接把边拆成两条，显然这样每个点的度数都是偶数  
整个图构成欧拉路  
题目意思就是说删去两条边之后仍然构成欧拉路  
那么根据欧拉路的性质可以知道  
删去的两条边必连在同一个点上  
这样保证了有两个点的度数变成奇数的情况下  
和他们连的那个点度数-2，仍然为偶数  
整张图依然是欧拉路  
![](https://cdn.luogu.com.cn/upload/image_hosting/b8vr4jy7.png)
![](https://cdn.luogu.com.cn/upload/image_hosting/bvb3y5ey.png)

下面考虑对答案有贡献的三种情况$(circle为自环数量)$  
* 两个自环对答案做贡献，总贡献$\frac {circle * (circle - 1) } 2$建议手模  
* 一个自环一条边，贡献值$(circle) * (m - circle)$
* 两条边$\frac {(du[i] * (du[i] - 1)} 2$


注意 
* 统计答案开$long \:\ long$，最后一种两条边的情况也要开 
* 判断整张图是否连通，若不连通输出0，可以选择冰茶几或者dfs，总之随便搞搞都能判

## Code
```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

inline int read(){
	int x = 0, w = 1;
	char ch = getchar();
	for(; ch > '9' || ch < '0'; ch = getchar()) if(ch == '-') w = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
	return x * w;
}

const int ss = 2000010;

int fa[ss], du[ss];

inline int find(int u){
	if(u == fa[u]) return u;
	return fa[u] = find(fa[u]);
}

inline void link(int u, int v){
	int xx = find(u), yy = find(v);
	if(xx != yy) fa[xx] = yy;
}

long long ans;
int l[ss], r[ss];
int circle;

signed main(){
	int n = read(), m = read();
	for(int i = 1; i <= n; i++) fa[i] = i;
	for(int i = 1; i <= m; i++){
		l[i] = read(), r[i] = read();
		link(l[i], r[i]);
		if(l[i] == r[i]) circle++;
		else{
			du[l[i]]++;
			du[r[i]]++;
		}
	}
	int begin = find(l[1]);
	for(int i = 2; i <= m; i++)
		if(find(l[i]) != begin)
			return puts("0"), 0;
	ans += (circle - 1) * circle / 2;
	ans += (circle) * (m - circle);
	for(int i = 1; i <= n; i++)
		ans += (long long)du[i] * (du[i] - 1) / 2;
	printf("%lld\n", ans);
	return 0;
}
```

小声bb：818写题解越来越敷衍了呢……

---

## 作者：字如其人 (赞：2)

前置：一个图中存在欧拉路，当且仅当图连通，且 n-2 个点的度数都是偶数，剩下 2 个点的度数为奇数。

图不连通直接输出 0。

每条边两边可以变为两条一样的边，原题目转化为 2m 条边删去两对边（剩 2(m-2) 条边），使得剩下的图中存在欧拉路。

所以剩下的图度数有两个点的度数为奇数。

因为删去一个自环不改变一个点的奇偶性，所以考虑以下三种情况（自环个数为 $cnt$，点 x 的度数为 $deg[x]$）：

- 两个自环（$\binom{cnt}{2}$）
- 一个自环和一条非自环边（$cnt*(m-cnt)$）
- 两条有公共点的边（$\sum_{x} {\binom{deg[x]}{2}}$）


---

## 作者：This_Rrhar (赞：1)

本题与陈通《欧拉图相关的生成与计数问题探究》中的例题 4.1 基本相同，区别在于本题需要判断图的连通性。

题目让我们求满足如下两个条件的路径数量：

1. 图里的两条边仅走一次。

2. 图里的其它边要走两次。

我们先不考虑条件 1，那么我们将原图中的每条边都重复两次，得到一个新图。此时新图中的顶点均为偶点。如果原图存在欧拉路径，那么新图也存在欧拉路径。

再考虑条件 1，我们在新图中删去两条两条边，并保证新图仍然存在欧拉路径，我们有如下三种删边的方式：

- 删去两条自环边：由于自环边的度为 $2$，此时奇点个数仍为 $0$。

- 删去一条自环边和非自环边：删去自环边的顶点同上，删去非自环边的两个顶点变为奇点，此时奇点个数为 $2$。

- 删去两条非自环边：若删去的两条非自环边没有公共顶点，则共有 $4$ 个顶点变为奇点，不合题意；若删去两条具有公共顶点的非自环边，则公共顶点仍为偶点，另外两个顶点变为奇点，共 $2$ 个奇点。

最后使用并查集判断图的连通性。

代码如下（C++20）：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define _r return*this
#define _o &operator
namespace IO
{
	const int _S=1<<21;
	char b[_S],*p1=b,*p2=b,pb[_S],*pp=pb;
	void fl(){fwrite(pb,1,pp-pb,stdout),pp=pb;}
	struct input
	{
		char gc(){if(p1==p2)p2=(p1=b)+fread(b,1,_S,stdin);return p1==p2?' ':*p1++;}
		input _o>>(char&c){do c=gc();while(c==' '||c=='\n'||c=='\r'||c=='\t');_r;}
		template<class T>input _o>>(T&x)
		{
			char c=gc();T f=1;
			for(x=0;!isdigit(c);)(c=='-'?f=-1:1),c=gc();
			while(isdigit(c))x=(x*10)+(c^48),c=gc();
			x*=f;_r;
		}
		input(){}
	}in;
	struct output
	{
		void pc(char c){*pp++=c;if(pp-pb==_S)fl();}
		output _o<<(char c){pc(c);_r;}
		template<class T>output _o<<(T x)
		{
			if(!x){pc(48); _r;}
			if(x<0)pc('-'),x=-x;
			int s[64],t=0;
			while(x)s[++t]=x%10,x/=10;
			while(t)pc(s[t--]+48);
			_r;
		}
		output _o<<(const char*s){int c=0;while(s[c])pc(s[c++]);_r;}
		output(){}
	}out;
	struct fe{~fe(){fl();}}fls;
}
using IO::in;
using IO::out;
using ll=long long;

#define N 1000001
#define M 1000001

ll n,m;
ll x[N],y[N];

ll f[N];
ll F(ll i){return i==f[i]?i:f[i]=F(f[i]);}
bool check()
{
	ll ca=F(x[1]);
	for(int i=2;i<=m;i++)if(F(x[i])!=ca)return false;
	return true;
}

ll deg[N],k,ans;

int main()
{
	in>>n>>m;
	for(int i=1;i<=n;i++)f[i]=i;
	for(int i=1;i<=m;i++)
	{
		in>>x[i]>>y[i];
		if(F(x[i])^F(y[i]))f[F(x[i])]=F(y[i]);
		if(x[i]^y[i])deg[x[i]]++,deg[y[i]]++;
		else k++;
	}
	if(!check())return out<<"0",0;
	for(int i=1;i<=n;i++)ans+=deg[i]*(deg[i]-1)/2;
	out<<k*(k-1)/2+k*(m-k)+ans;
}
```

---

## 作者：Logey (赞：1)

从国家集训队的论文集里看到的题，既然没人写题解那我也就参考一下论文集里的话写一篇题解了。

这里把陈通写的论文放上来供大家看一下吧。

[欧拉图相关的生成与计数问题探究](https://oi.logey.cn/EulerPath.pdf)

#### 解法

题意转化一下就是说让原图 $G$ 的每条边建两遍，那么显然是一张欧拉回路。要求删去两条边之后这张图存在欧拉路径。

既然存在欧拉路径，那么必然存在两个或者零个奇度点。删去一条边会使得两个端点的度数减一，那么只存在以下三种合法的删边方式。

 1.删除两条自环（删除后为欧拉图）。
 2.删除两条有公共点的边（删除后为半欧拉图）。
 3.删除一条自环与一条边（删除后为半欧拉图）。
 
那么分别统计方案就可以了。

注意这张图不一定连通，可能存在无解的方案。需要想办法判断每条边是不是都走过了，我的代码里是是用 $dfs$ 判断了一下边的度数。

#### Source Code

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>

const int MAXN = 1e6 + 7;

int f[MAXN], h[MAXN], self[MAXN];
int deg[MAXN], my, es;
int tot, t2;

struct Edge {
    int t, next;
} edge[MAXN << 1];

int head[MAXN], cnt;
bool vis[MAXN];
long long ans;

void add(int u, int v) {
    edge[++cnt] = (Edge){v, head[u]}; head[u] = cnt;
}

void dfs(int u) {
    tot += deg[u];
    t2 += self[u];
    vis[u] = true;

    ans += (1LL * deg[u] * (deg[u] - 1LL) / 2LL);
    for (int e = head[u]; e; e = edge[e].next) {
        int v = edge[e].t;
        if (!vis[v]) dfs(v);
    }
}

int main(int argc, char *argv[]) {
    int n, m, r;
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        if (u == v) my++, self[u]++;
        else deg[u]++, deg[v]++, es++, add(u, v), add(v, u);
    }

    ans = 1LL * es * my + 1LL * (1LL * my * (my - 1)) / 2;

    for (int i = 1; i <= n; i++) {
        if (!vis[i] && deg[i]) {dfs(i); break;}
    }

    if (tot != es * 2) ans = 0;
    if (t2 != my) ans = 0;

    printf("%lld\n", tot == es * 2 ? ans : 0);
    return 0;
}
```

---

## 作者：lx_zjk (赞：1)

新的方法，不会告诉你这道题和普及组期末测试T2一样，用并查集维护判断联通块
```
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;


inline ll read(){
	ll x=0,f=1;char ch;
	do{ch=getchar();if(ch=='-')f=-1;}while(ch>'9'||ch<'0');
	do{x=x*10+ch-'0';ch=getchar();}while(ch<='9'&&ch>='0');
	return f*x;
}

const int maxn=1e6 + 7;

ll res;

int n,m,a[maxn],b[maxn],fa[maxn],x[maxn],cnt;

inline int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

int main(){
	n=read();m=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=0;i<m;i++){
		a[i]=read();b[i]=read();
		fa[find(a[i])]=find(b[i]);
		if(a[i]==b[i])cnt++;
		else x[a[i]]++,x[b[i]]++;
	}
	for(int i=1,k=find(a[0]);i<m;i++) {
		//cout<<k<<" "<<find(a[i])<<"\n";
		if(find(a[i])!=k)
		{
			puts("0");
			return 0;
		}
	}
	for(int i=1;i<=n;i++)
		res+=1LL*x[i]*(x[i]-1)/2;
	res+=1LL*cnt*(m-cnt)+1LL*cnt*(cnt-1)/2;
	printf("%lld\n",res);
	return 0;
}

```

---

## 作者：Imerance1018 (赞：0)

## Description

给定一个不一定连通，有自环，无重边的无向图，求有两条边走过一次，其他边走过两次的路径数。

## Solution

显然每两条边都与一条路径一一对应，问题等价于选出满足条件的两条边。

我们先不考虑自环的情况。

那么就有如下结论：两条边满足条件当且仅当它们有一个公共端点。

对于给定的两条边，不妨先删去。再将其他的边拆成两条无向边。这个图的任意一个顶点度数为偶数，每个顶点必然存在一条从它出发的欧拉回路。

那么对于每个顶点相连的边，他对答案产生贡献当且仅当回路走了一圈回来，即只能在同样与这个顶点相连的边里选。

定义 $in_i$ 为有一个端点为 $i$ 的边的数量，每个端点的贡献即为 $\dbinom{in_i}{2}$。

那么考虑自环呢？

显然，自环在什么地方都可以走，所以它可以与任意一条边组合，都是合法的，证明同上。

所以每个自环的贡献就是 $m-1-tot$，其中 $tot$ 表示在它之前输入的自环数。

注意如果有边不与其他边连通，答案为 $0$。

## Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
int n,m,in[N],fa[N],tot,ans,rt;
bool pd[N]; 
int find(int x){return (fa[x]==x)?fa[x]:fa[x]=find(fa[x]);}
void merge(int x,int y){fa[find(x)]=find(y);}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int u,v;
		cin>>u>>v;
		rt=u;
		if(u==v)
		{
			ans+=m-1-tot;
			tot++;
			pd[u]=1;
			continue;
		}
		merge(u,v);
		pd[u]=pd[v]=1;
		in[u]++;
		in[v]++;
	}
	for(int i=1;i<=n;i++)
		if(find(i)!=find(rt)&&pd[i])
		{
			cout<<0;
			return 0;
		}
	for(int u=1;u<=n;u++)ans+=in[u]*(in[u]-1)/2;
	cout<<ans; 
	return 0;
}
``````

---

## 作者：2020kanade (赞：0)

提供一个基于 DFS 生成树的不一样的思路。

通过瞪样例我们可以猜想：对于原图为树的情况，选取的两条边必须相邻。

为什么？考虑对树 DFS,删掉两条边将树拆成三部分，两个子树可以直接从根 DFS 一遍，显然每条边经过两次；直接先 DFS 一个子树，回到根后走两条边到达另一个根，之后对剩下的子树 DFS 即可构造，容易证明其他情况一定不行。

之后，考虑扩展到一般图，我们在 DFS 生成树上进行讨论。

先不考虑自环，如果被选中的边都不是返祖边，直接把返祖边正着反着走两边即可规约到树的情况；否则，把没有被选中的返祖边的端点对应的树边链视作返祖边，正着反着走两遍，也可以规约到树的情况。

那么，不考虑自环的情况下，答案是 $\sum_{i=1}^{n} \frac{(deg_i-1)\times(deg_i)}{2}$，$deg_i$ 是结点 $i$ 在 **不考虑自环** 的情况下的度数。

接下来考虑自环：注意到自环走任意次不对其他边造成影响，如果选择的两条边都是自环，规约到去掉自环的图每条边经过两遍，树的情况显然，图的情况用 DFS 生成树规约，返祖边正反两遍即可；如果只选择一条自环，也能够规约到树与 DFS 生成树的情况，此时可以发现另一条边可以任选。

那么，设自环数量为 $cyc$，其贡献为 $\frac{(cyc-1)\times cyc}{2}+cyc\times(m-cyc)$。

两部分相加即为答案。注意 **度数不为零的所有点不连通** 时由于不存在一条路径遍历所有边所以答案为 $0$。


```cpp
#include<bits/stdc++.h>
using namespace std;
using ll=long long;
const int N=1e6+11;
int deg[N],cyc,fa[N],usz[N];
int ask(int u)
{
	if(u==fa[u]) return u;
	return fa[u]=ask(fa[u]);
}
void aws(int u,int v)
{
	u=ask(u),v=ask(v);
	if(u==v) return;
	fa[v]=u,usz[u]+=usz[v];
}
int n,m,cnt;
bool qaq[N];
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) fa[i]=i,usz[i]=1;
	for(int i=1,iu,iv;i<=m;++i)
	{
		cin>>iu>>iv;
		if(iu==iv)
		{
			++cyc;
			qaq[iu]=1;
			continue;
		}
		else
		{
			++deg[iu],++deg[iv];
			aws(iu,iv);
			qaq[iu]=qaq[iv]=1;
		}
	}
	for(int i=1;i<=n;++i) cnt+=qaq[i];
	for(int i=1;i<=n;++i) if(qaq[i])
	if(usz[ask(i)]<cnt)
	{
		cout<<0<<endl;
		return 0;
	}
	ll ans=0;
	for(int i=1;i<=n;++i) ans+=(1ll*deg[i]*(deg[i]-1ll))/2ll;
	ans+=(1ll*cyc*(cyc-1ll))/2+1ll*cyc*(m-cyc);
	cout<<ans<<endl;return 0;
}
```

---

## 作者：_ZHONGZIJIE0608_ (赞：0)

总共有 $n$ 个节点，$m$ 条路径，要求其中 $m-2$ 条路径走两遍，剩下 $2$ 条路径仅走一遍，问不同的路径总数有多少，如果仅走一遍的两条边不同则将这两条路径视为不同。

首先考虑把所有边拆成 $2$ 份再删除两条边。

首先原图肯定是有欧拉回路的。考虑怎么删 $2$ 条边，使得新的图有欧拉路。

众所周知，如果一个图上有欧拉路，度数为奇数的点最多 $2$ 个。在此问题中自环的度数不对总度数产生贡献，所以删自环等于没删边。 

那么就要考虑删除的两条边是不是自环了。设自环个数是 $c$。

如果删除两个自环，自环可以随便删，答案就是在 $c$ 个自环里面选 $2$ 个的方案数 $\frac{c(c-1)}{2}$。

如果删除一个自环和一条边，此时有两个点度数为奇数，仍然存在欧拉路径。所以自环和边都可以随便删，方案数 $c(m-c)$。

如果删除两条边，此时不能让更多的边度数为奇数，所以两边一定共一点。方案数为 $\sum_{i=1}^n \frac{deg_i(deg_i-1)}{2}$。其中 $deg_i$ 表示点 $i$ 除自环外的度数。

答案为上述三种方案数的和。

当然你还要维护**连了边的点**是否连通，并查集和 DFS 都很好解决。没连通就是无解的。

```cpp
//憂鬱鰐龜襲擊烏鴉飛機
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
unordered_set<int>s;
int n,m,deg[N],c;
vector<int>vec;
int fa[N];
int find(int x){return fa[x]==x?fa[x]:fa[x]=find(fa[x]);}
void Union(int x,int y){
	int fax=find(x),fay=find(y);
	fa[fay]=fax;return;
} 
signed main(){
	ios::sync_with_stdio(false);cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i)fa[i]=i;
	for(int i=1;i<=m;++i){
		int u,v;cin>>u>>v;
		Union(u,v);
		s.insert(u);s.insert(v);
		if(u==v)++c;
		if(u!=v)++deg[u],++deg[v];
	}
	for(int i=1;i<=n;++i)if(find(i)==i)vec.push_back(i);
	int tmp=0;
	if(vec.size()>1){
		for(auto i:vec){
			if(s.count(i))++tmp;
		}
		if(tmp>1){
			cout<<0;return 0;
		}
	}
	int ans=0;
	for(int i=1;i<=n;++i)ans+=(deg[i]*(deg[i]-1))/2;
	cout<<(c*(c-1)/2+c*(m-c)+ans);
	return 0;
}
/*
羣賢畢至 
少長咸集 
*/
```

---

## 作者：Mashu77 (赞：0)

分析：考虑直接将每条边都当作两条边，那么题意及从 $2 n$  条边任选 $2$ 条不是连接相同节点的边删除后图存在欧拉路，求删边的方案数。

如果本来的图不连通，那么肯定没有合适的方案，直接输出 $0$ 就可以了。

否则我们在分析：由于我们是将每条边当作两条边的，那么对于建的图来说，每个顶点的度数为偶数，及一定存在欧拉路。

那么就来考虑删的边了。

我们可以把边分为自环和非自环两类。

为什么呢？

因为自环只跟一个顶点有关系，而非自环跟两个顶点有关系。
如果删除了一个自环，那剩下的所有点的度数仍然为偶数，所以可以随意删除下一条边。
而对于删除的第二条边，如果是非自环，那么图就有两个积点，存在欧拉路径，如果是自环，那么图所有点为偶点，存在欧拉回路。

所以可以得出自环的贡献为：$cnt \times (m-cnt)+\dfrac{cnt\times (cnt-1)}{2}$
其中 $c n t$ 为自环数，$m$ 是边数。

如果删除两条非自环，如果可行，那么它们一定共顶点，只有这样才会使共顶点的度数 $− 2$，仍为偶点，两外两个点的度数 $- 1$，为积点，存在欧拉路径。

所以非自环的贡献为：$\displaystyle \sum_{i=1}^{n}\frac{l_i\times(l_i-1)}{2}$，其中 $l_i$ 为每个顶点连接的边数（不包括自环）。

```cpp
#include<bits/stdc++.h>
#define int long long
const int N=1e6+1;
using namespace std;
vector<int>E[N];
int n,m,x[N],y[N],deg[N],ans,vis[N],cnt,fa[N];
inline int ga(int x)
{
	return x==fa[x]?fa[x]:fa[x]=ga(fa[x]);
}
inline void uni(int x,int y)
{
	int fx=ga(x),fy=ga(y);
	if(fx!=fy)
		fa[fx]=fy;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL),cout.tie(NULL);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		cin>>x[i]>>y[i];
		uni(x[i],y[i]);
		if(x[i]==y[i])
			cnt++;
		else
			E[x[i]].push_back(y[i]),E[y[i]].push_back(x[i]);
	}
	for(int i=2;i<=m;i++)
		if(ga(x[i])!=ga(x[1]))
			cout<<"0",exit(0);
	for(int i=1;i<=n;i++)
	{
		int le=E[i].size();
		ans+=le*(le-1)/2;
	}
	ans+=cnt*(cnt-1)/2;
	ans+=cnt*(m-cnt);
	cout<<ans;
	return 0;
}

---

## 作者：_Spectator_ (赞：0)

[可能更好的食用体验](/blog/523641/CF788B) $|$ 
[题目传送门](/problem/CF788B) $|$ 
[我的其他题解](/blog/523641/#type=题解-New)

------------

${\large\color{#00CD00}\text{题意}}$

给定一个 $n$ 个点 $m$ 条边的无向图，求有多少种选择两条边的方案，使得图中存在一条路径满足这两条边恰好经过 $1$ 次，且其它 $m-2$ 条边恰好经过 $2$ 次。

------------

${\large\color{#00CD00}\text{思路}}$

先假设图中无自环且图联通。令这个图为 $G$：

![](https://cdn.luogu.com.cn/upload/image_hosting/d9ctxmg2.png)

题目要求每条边走两遍，那我们可以看作成把原图中的每条无向边“拆”成两条边，每条边走一遍。令这个图为 $G'$：

![](https://cdn.luogu.com.cn/upload/image_hosting/br0ypkcu.png)

这样一来，每个点的度数都为偶数，因此整个图肯定是个欧拉图。

但是我们还需要有两条边只走一次。体现在 $G'$ 中，就是要删掉两条本质不同的边（即这两条边不是由 $G$ 中的同一条边拆出来的），仍然存在欧拉路径。

而存在欧拉路径则需要满足图中恰有两个点的度为奇数。如果删除的两条边没有公共顶点，那么这两条边所连的四个点的度都会变成奇数，不符合。

![](https://cdn.luogu.com.cn/upload/image_hosting/l52a5m9z.png)  
（如图，删除两条红色边后，四个标黄的点的度变为奇数。）

因此，删除的两条边必须要有一个公共顶点。这样的话，这个公共顶点的度仍然为偶数，而其它两个点的度为奇数，存在欧拉路径。

![](https://cdn.luogu.com.cn/upload/image_hosting/8oozadn1.png)  
（如图，删除两条红色边后，只有两个点的度变为奇数。）

这种情况下，设原图中第 $i$ 个点的度为 $d_i$，则方案数为 $\sum\limits_{i=1}^n d_i\times (d_i-1)\div 2$。

然而，图中还有可能存在自环。由于自环无论经过 $1$ 次还是 $2$ 次都对后续的路径没有影响，因此不将自环边计入到结点的度中，而将其单独考虑。设图中自环有 $cnt$ 个，可以分两种情况考虑：
- 选一条自环边与一条非自环边。相当于在 $G'$ 中只选择一条边删除，有两个点的度变为奇数，符合条件。方案数为 $cnt\times (m-cnt)$。
- 选两条自环边。相当于在 $G'$ 中不删除任何边，也符合条件。方案数为 $cnt\times (cnt-1)\div 2$。

将以上的三种情况（不选自环、选自环+非自环、选两条自环）的方案数加起来，即为最终的答案。

最后，本题还有一个坑点，即图不联通应输出 $0$。这个可以用并查集判断。不过如果是孤立点则不算不联通。具体实现见代码，[这里](/paste/ka4vdcfm)有三组卡掉过我的判联通的 hack 数据。

------------

${\large\color{#00CD00}\text{代码}}$

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
long long n,m,cnt,ans;
int x[N],y[N],d[N],f[N];
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
int main()
{
	ios::sync_with_stdio(false);
	cin>>n>>m;
	for(int i=1;i<=n;i++)f[i]=i; //并查集初始化
	for(int i=1;i<=m;i++)
	{
		cin>>x[i]>>y[i];
		if(x[i]==y[i])cnt++; //统计自环数量
		else d[x[i]]++,d[y[i]]++,f[find(x[i])]=find(y[i]);
	}
	for(int i=1;i<=m;i++) //注意这里是枚举边而不是点，这样可以避开孤立点
		if(find(x[i])!=find(x[1])){
        //不要跟 find(1) 比较，因为有可能 1 号点是孤立点
        //也不要写 f[x[i]]!=f[x[1]]
			cout<<0;
			return 0;
		}
	for(int i=1;i<=n;i++)ans+=d[i]*(d[i]-1ll)/2; //不选自环
	cout<<ans+cnt*(cnt-1)/2+cnt*(m-cnt);
	//cnt*(cnt-1)/2：选两条自环
	//cnt*(m-cnt)：选自环+非自环
	return 0;
}
```

---

## 作者：xfrvq (赞：0)

[$\tt Link$](/problem/CF788B)，$\tt^{\ast}2100$。

---

回顾欧拉路的存在条件：图联通且度数为奇数的点个数是 $0$ 或 $2$。  
我们考虑把所有边复制一遍，然后问题变成删去两条边使原图存在欧拉路。  
好像复制后所有边的度数都是偶数，然后可以瞎 jb 乱删。  
是吗？  
但是好像删的边必须有公共点不然走不通诶。  
观察样例，还有自环？自环的删除并不影响原来点的度数奇偶性，所以这时剩下一条边就不一定要有公共点了。  
观察样例，图还可以不联通，所以还需判。

---

```cpp
const int N = 1e6 + 5;

int n,m,deg[N],sum,fa[N];
vector<int> point;

int fnd(int i){
	if(i == fa[i]) return i;
	return fa[i] = fnd(fa[i]);
}

int main(){
	scanf("%d%d",&n,&m);
	iota(fa,fa + n + 1,0);
	for(int i = 1;i <= m;++i){
		int u,v;
		scanf("%d%d",&u,&v);
		point.push_back(u);
		point.push_back(v);
		u == v ? ++sum : (++deg[u],++deg[v]);
		fa[fnd(u)] = fnd(v);
	}
	point.resize(unique(begin(point),end(point)) - begin(point));
	for(int x : point) if(fnd(x) != fnd(point.front())) return printf("0\n"),0;
	long long ans1 = 1LL * sum * (sum - 1) / 2;
	long long ans2 = 1LL * sum * (m - sum);
	long long ans3 = 0;
	for(int i = 1;i <= n;++i) ans3 += 1LL * deg[i] * (deg[i] - 1) / 2;
	printf("%lld\n",ans1 + ans2 + ans3);
	return 0;
}
```

---

## 作者：little_cindy (赞：0)

## 题解中将包含的内容
并查集，欧拉路径。
## 思路
如题目中：
> 要求其中 $m-2$ 条路径走两遍，剩下 $2$ 条路径仅走一遍

其实我们可以换个角度理解这句话。

一条要走两遍的路径 $(u,v)$ 其实可以看为两条边 $(u,v)$。

而只能走一遍的路径，其实可以看做删去 $2$ 条边。

满足以上条件，还需要同时兼备存在欧拉路径。

那么，怎样选变才可以删去呢？

只要满足删去 $2$ 条边之后使得度数为奇数的点只有 $2$ 个或 $0$ 个。

由于最开始都有两条边，所有的点的度数都为偶数。每删去一条边可以使得两端的点的度数奇偶性反转。

从而，我们可以知道，**删去自环不影响任何一个点的度数的奇偶性。** 为了方便接下来的计算，我们再次假定自环有 $tot$ 个。

我们先考虑删一条非自环边，此时已经有了 $2$ 个度数为奇数的点。我们可以：
- **再删除一个自环**

上文已经提到，删除自环没有对任何一个点的度数的奇偶性没有影响，所以度数为奇数的点依然为 $2$ 个。非自环边有 $m-tot$ 个，故该方案方案数为 $(m-tot)\times tot$。
- **再删除一条边**

这个可能大家想不到。由于每删去一条边可以使得两端的点的度数奇偶性反转，所以只要将其中的一个度数为奇数的点和另外一个度数为偶数的点之间的边删去就好了。这样，原来的边中的一个度数为奇数的点的度数变为偶数，然后有新增了一个度数为为奇数的点，这样度数为奇数的点仍然为 $2$ 个。由于其中一个点是公共点，所以我们只需要枚举这个公共点，任意选两条边即可。假设点 $i$ 的度数为 $du_i$，则该方案方案数为 $\sum\limits^n_{i=1}C^2_{du_i}$。

另外，我们也可以不增加任何一个度数为奇数的点，即删除两个自环，故该方案方案数为 $C^2_{tot}$。

综上，总方案数为 $\sum\limits^n_{i=1}C^2_{du_i}+C^2_{tot}+tot\times(m-tot)$。

**注意：要保证图联通才能满足条件。** 此题当中，我们选用并查集维护。

## code
```cpp#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=2000005;
int n,m;
int du[maxn];
vector<int> nbr[maxn];
//bool vis[maxn];
int tot;
int fa[maxn];
int pos[maxn];
int find(int x){
	if(fa[x]==x){
		return x;
	}
	return fa[x]=find(fa[x]);
}
void onion(int x,int y){
	int fx=find(x);
	int fy=find(y);
	if(fx!=fy){
		fa[fy]=fx;
	}
	return;
}
int main(){
	ios::sync_with_stdio(0);//不写第14个点会TLE
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++){//初始化
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		pos[i]=u;//方便下面判定联通
		if(u==v){
			tot++;//统计自环
		}
		else{
			du[u]++;
			du[v]++;
			onion(u,v);//合并
		}
	}
	int st=find(pos[1]);
	for(int i=2;i<=m;i++){//如果不连通
		if(st!=find(pos[i])){
			cout<<"0";
			return 0;
		}
	}
	long long ans=0;
	for(int i=1;i<=n;i++){//两条边
		ans+=1ll*du[i]*(du[i]-1)/2;
	}
	ans+=1ll*tot*(tot-1)/2;//两个自环
	ans+=1ll*tot*(m-tot);//一个自环一条边
	cout<<ans;
	return 0;
}
```

---

## 作者：hzoi_liuchang (赞：0)

## 分析
根据题目中的信息大概可以想到用欧拉路。

我们可以把一条边看成两条，问题转化为删去两条不同的边，使原图中存在欧拉回路

首先，如果图是不联通的，那么直接输出 $0$ 即可

如果图是联通的

那么存在欧拉回路的条件是所有点的度数为偶数或者只有两个点的度数为奇数

那么我们就有以下三种方案

1、删去两个自环

2、删去一个自环和任意一条边

3、删去一个节点所连接的两条边

注意开 $long\ long$
## 代码
``` cpp
#include<cstdio>
#define int long long
inline int read(){
	int x=0,fh=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') fh=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return x*fh;
}
const int maxn=3e6+5;
int n,m,rd[maxn],cntt,cnt[maxn],fa[maxn],anss[maxn];
long long ans=0;
int zhao(int xx){
	if(xx==fa[xx]) return xx;
	return fa[xx]=zhao(fa[xx]);
}
void bing(int xx,int yy){
	fa[zhao(xx)]=zhao(yy);
}
signed main(){
	n=read(),m=read();
	for(int i=1;i<=n;i++){
		fa[i]=i;
	}
	for(int i=1;i<=m;i++){
		int aa,bb;
		aa=read(),bb=read();
		if(aa==bb){
			cnt[aa]++;
			cntt++;
			continue;
		}
		bing(aa,bb);
		rd[aa]++;
		rd[bb]++;
	}
	for(int i=1;i<=n;i++){
		anss[zhao(i)]+=rd[i];
		anss[zhao(i)]+=cnt[i]*2;
	}
	for(int i=1;i<=n;i++){
		if(anss[i]==0 || anss[i]==m*2) continue;
		printf("0\n");
		return 0;
	}
	for(int i=1;i<=n;i++){
		if(rd[i]>=2){
			ans+=1LL*(rd[i]-1)*rd[i]/2LL;
		}
	}
	ans+=cntt*(m-cntt);
	ans+=1LL*(cntt-1)*cntt/2LL;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：yzh_Error404 (赞：0)

前置知识：并查集（或任意可以判断图是否联通的算法），欧拉路。

对于一条边只能走两次的限制，可以将一条边拆成两条边。

接下来可以删掉两条边来满足要求，而不重复的走过剩下的边就是欧拉路的定义。

题意就转化为求在有 $2\times m$ 条边的图中删去两条边之后的欧拉路条数。

因为要保证度数一直为偶数，所以删的两条边必须要满足特定的条件。

可以有三种删边的方法（设自环数量为 $c$ ，第 $i$ 个点的度数为 $du_i$）

1. 删两个自环，方案数为 $\dfrac{c\times(c-1)}{2}$
2. 删一个自环再任意删一条边，方案数为 $c\times (m-c)$
3. 删两条共点的边，方案数为 $\sum\limits_{i\in V}\dfrac{du_i\times(du_i-1)}{2}$

最后并查集判断图是否联通即可。

有一个小细节，数据中的点的编号不一定是 $1$ 到 $n$ ，最好是记录下来。

其实这道题只需要欧拉路的思想。

代码实现：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e6+5;
struct node
{
	int to,nxt;
}e[MAXN];
int head[MAXN],cnt;
inline void add(int x,int y)
{
	e[++cnt].to=y;
	e[cnt].nxt=head[x];
	head[x]=cnt;
}
int n,m,c;
int fa[MAXN];
inline int find(int x)
{
	if(fa[x]==x)return fa[x];
	return fa[x]=find(fa[x]);
}
inline void merge(int x,int y)
{
	int fx=find(x),fy=find(y);
	fa[fx]=fy;
}
int l[MAXN],r[MAXN];
int du[MAXN];
signed main()
{
	scanf("%lld%lld",&n,&m);
	for(register int i=1;i<=n;i++)
		fa[i]=i;
	for(register int i=1;i<=m;i++)
	{
		scanf("%lld%lld",&l[i],&r[i]);
		add(l[i],r[i]);
		merge(l[i],r[i]);
		if(l[i]==r[i])c++;//累加自环的个数
		else
		{
			du[l[i]]++;
			du[r[i]]++;
		}
	}
	int Ups=find(l[1]);
	for(register int i=2;i<=m;i++)//并查集判断图是否联通
		if(Ups!=find(l[i]))
		{
			puts("0");
			return 0;
		}
	int ans=0;
	ans+=(c*(c-1)/2);
	ans+=(c*(m-c));
	for(register int i=1;i<=n;i++)
		ans+=(du[i]*(du[i]-1)/2);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：wind_whisper (赞：0)

## $\text{Description}$
总共有 $n$ 个节点，$m$ 条路径，要求其中 $m-2$ 条路径走两遍，剩下 $2$ 条路径仅走一遍，问不同的路径总数有多少，如果仅走一遍的两条边不同则将这两条路径视为不同.    
$n,m\le10^6$
## $\text{Solution}$
把每条边拆成两个一样的边，考虑欧拉回路的条件.  
由于拆了边，显然每个点的度数都是偶数.  
所以选择的两条边**必须含有公共端点**.  
考虑自环如何处理.  
删掉自环后该点的度数还是偶数，所以剩下的一条边随便删即可.  
细节上，需要判断**含有边的**点必须连通.
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double 
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1e6+100;
const double eps=1e-12;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m;
int du[N];
int fa[N],tag[N];
ll num;
int find(int x){return x==fa[x]?x:fa[x]=find(fa[x]);}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();m=read();
  for(int i=1;i<=n;i++) fa[i]=i;
  for(int i=1;i<=m;i++){
    int x=read(),y=read();
    fa[find(x)]=find(y);
    tag[x]=tag[y]=1;
    if(x==y){
      ++num;continue;
    }
    ++du[x];++du[y];
  }
  int cnt(0);
  for(int i=1;i<=n;i++){
    cnt+=(find(i)==i&&tag[i]!=0);
  }
  if(cnt>1||m<2){
    printf("0");return 0;
  }
  ll ans(0);
  for(int i=1;i<=n;i++){
    ans+=1ll*du[i]*(du[i]-1)/2;
    //printf("i=%d du=%d ans=%lld\n",i,du[i],ans);
  }
  ans+=num*(m-num)+num*(num-1)/2;
  printf("%lld\n",ans);
  return 0;
}
/*

*/

```


---

