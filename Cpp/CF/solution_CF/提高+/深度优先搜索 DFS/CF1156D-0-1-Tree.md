# 0-1-Tree

## 题目描述

给定一棵包含 $n$ 个顶点和 $n-1$ 条边的树（无向、连通、无环图）。每条边上都写有一个数字，这个数字要么是 $0$（称为 $0$ 边），要么是 $1$（称为 $1$ 边）。

我们称有序顶点对 $(x, y)$（$x \ne y$）是合法的，如果在从 $x$ 到 $y$ 的简单路径上，**在经过 $1$ 边之后，路径上不会再经过 $0$ 边**。你的任务是计算树中合法的有序顶点对的数量。

## 说明/提示

下图对应于第一个样例：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1156D/638afcedfa6d4eecb5e63ed4a099a832b54e2fbc.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
7
2 1 1
3 2 0
4 2 1
5 2 0
6 7 1
7 2 1
```

### 输出

```
34
```

# 题解

## 作者：_edge_ (赞：15)

搞不懂为啥要用树形 DP 的神奇做法，这题不是搜搜然后组合计数么。

就先把全 $1$ 为边的连通块和全为 $0$ 的连通块找出来。

然后分类讨论。

讨论在全 $1$ 为边的连通块内，随便取两个点都是合法的，因此假设 $sz$ 是这个连通块的点数，对答案的贡献就是 $sz \times (sz-1)$。

全 $0$ 的情况同理可得。

然后考虑一下一段是 $0$，一段是 $1$ 的情况，这种情况下，我们去枚举那个中转点，然后记录中转点所在的全 $1$ 连通块的数量以及全 $0$ 连通块的数量，这样的话从 $0$ 到 $1$ 乘法乘一下即可。

感觉代码很好写，并且复杂度是 $O(n)$ 的，比目前题解区内所有题解都要优秀。

过了样例就一遍切掉了。

```cpp
#include <iostream>
#include <cstdio>
#include <vector>
#define pb push_back
using namespace std;
const int INF=5e5+5;
struct _node_edge{
	int to_,next_,disv_;
}edge[INF<<1];
int n,tot,scc[INF][5],scc_tot,head[INF],vis[INF];
vector <int> w[INF],b[INF];
void add_edge(int x,int y,int z) {
	edge[++tot]=(_node_edge){y,head[x],z};
	head[x]=tot;return ;
}
void DFS(int x,int fa,int dd) {
//	cout<<x<<" "<<fa<<" ????\n";
	if (!dd) w[scc_tot].pb(x);
	else b[scc_tot].pb(x);
	scc[x][dd]=scc_tot;
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_,d=edge[i].disv_;
		if (d!=dd || v==fa) continue;
		DFS(v,x,dd);		
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<n;i++) {
		int x=0,y=0,c=0;cin>>x>>y>>c;
		add_edge(x,y,c);add_edge(y,x,c);
	}
	for (int i=1;i<=n;i++) {
		if (!scc[i][0]) {
			++scc_tot;
			DFS(i,-1,0);
		}
		if (!scc[i][1]) {
			++scc_tot;
			DFS(i,-1,1);	
		}
	} 
	int ans=0;
	for (int i=1;i<=scc_tot;i++) {
		int len=w[i].size(),len1=b[i].size();
		ans+=len*(len-1)+len1*(len1-1);
	}
	for (int i=1;i<=n;i++) {
		int len=w[scc[i][0]].size(),len1=b[scc[i][1]].size();
		ans+=(len-1)*(len1-1);
	}
	cout<<ans<<"\n";
	return 0;
}
```


---

## 作者：ran_qwq (赞：11)

因为经过一条 $1$ 边后不能经过 $0$ 边，所以就有 $3$ 种情况：

- 全为 $0$。

- 全为 $1$。

- 前面若干个 $0$，后面若干个 $1$。

其实也可以把它们归为 $1$ 种情况：前面 $x$ 个 $0$，后面 $y$ 个 $1$（$x,y$ 均为非负整数）。

枚举由 $0$ 到 $1$ 的转化点 $i$（对于三种情况中的情况 $1$，就是路径的终点；对于情况 $2$，就是起点）。那么这条路径可以从和 $i$ 在同一个 $0$ 边的连通块上的任一点开始，到和 $i$ 在同一个 $1$ 边连通块的任一点结束，但是不能起点和终点在同一点。

考虑开 $2$ 个**并查集**维护只由 $0$ 边和只由 $1$ 边组成的连通块，就能知道每一个点所在的连通块大小了。设 $i$ 点所在的 $0$ 边组成的连通块大小为 $a$，$1$ 边组成的连通块大小为 $b$，则 $i$ 点对答案的贡献就是 $a\times b-1$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,INF=0x3f3f3f3f;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void Write(int x){if(x<0){putchar('-'),Write(-x);return;}if(x<10){putchar(x+'0');return;}Write(x/10),putchar(x%10+'0');}
void write(int x,char *s){Write(x),printf("%s",s);}
int n,ans;
struct UF
{
	int fa[N],siz[N];
	void init() {for(int i=1;i<=n;i++) fa[i]=i,siz[i]=1;}
	int find(int x) {return fa[x]==x?x:fa[x]=find(fa[x]);}
	void merge(int x,int y)
	{
		int s=find(x),t=find(y);
		if(s!=t) fa[s]=t,siz[t]+=siz[s];
	}
}b[2];
void solve()
{
	n=read(),b[0].init(),b[1].init();
	for(int i=1,x,y,z;i<n;i++) x=read(),y=read(),z=read(),b[z].merge(x,y);
	for(int i=1;i<=n;i++) ans+=b[0].siz[b[0].find(i)]*b[1].siz[b[1].find(i)]-1;
	write(ans,"");
}
signed main()
{
	int T=1;
	while(T--) solve();
}

```

---

## 作者：_Fontainebleau_ (赞：7)

## [CF1156D 0-1-Tree](https://www.luogu.com.cn/problem/CF1156D)

[在我的 cnblogs 阅读](https://www.cnblogs.com/LJC001151/p/14497594.html)

#### 题意

- 给定一颗 $n$ 个点的边权为 $0$ 或 $1$ 的树。
- 定义 **合法路径 $(x,y)$ $(x\not= y)$** 为，满足从 $x$ 走到 $y$ 一旦经过边权为 $1$ 的边，就不能再经过边权为 $0$ 的边的路径。
- 求合法路径个数。
-  $2\le n \le 2 \times 10^5$ 。

#### 分析

前置芝士：[并查集](https://www.luogu.com.cn/problem/P3367)

有 $O(n)$ 的换根 DP 做法，可惜我不会。

但是 $O(n\log n)$ 的并查集又好打，又好理解，何乐而不为？

首先，如何求合法路径个数？

我们可以枚举树上的所有结点，不妨记通过当前节点 $i$ 的路径数量为 $num_i$ 。最后的答案即是 $\sum_{i=1}^{n} num_i$ 。

如何避免重复算？

我们考虑并查集。先不着急，一步步来。

我们发现合法路径的边权一定是

- 情况 $1$ ：全为 $0$ ，
- 情况 $2$ ：全为 $1$ ，
- 情况 $3$ ：前一部分全为 $0$ ，后一部分全为 $1$ ，

上述三者之一。

放一张图。

[![6MX1oj.md.png](https://s3.ax1x.com/2021/03/08/6MX1oj.md.png)](https://imgtu.com/i/6MX1oj)

我们不妨用一个并查集维护所有边权为 $0$ 的边组成的连通块，如上图黄色部分。对于边权为 $1$ 的边同理，上图绿色部分。记维护 $0$ 边的并查集为 $a$ ， $1$ 边的为 $b$ 。用 $sza_i$ 表示点 $i$ 所在边权为 $0$ 的联通块大小， $szb_i$ 同理。

例：图中 $sza_1=3,szb_1=3$ 。

那么， $num_i=sza_i\times szb_i - 1$ 。

这里的 $num_i$ 为， $i$ 作为所在连通块内的合法路径的某一  **顶点** 时的合法路径数，加上 $i$ 作为前文情况 $3$ 中的 $01$ **分界点** 时合法路径数的和。然后这个和可以用上面的式子表示，是一个排列组合。以上图为例，可以看作是黄色部分有 $3$ 个点与绿色部分 $3$ 个点的搭配。为什么是 $3$ 而非 $2$ ？因为此时包括分界点 $1$ ，而当分界点被看成属于黄色时，与绿色搭配，求得即是以 $1$ 为顶点时绿色区域内合法路径的个数。当分界点被看作属于绿色时，同理。而分界点不能与自己形成合法路径，因而要 $-1$ 。

 这样就可以避免重复 / 漏 掉某些路径。大家可以好好想想为什么加粗的字可以有效避免重复或漏算。

大致解释一下。当 $i$ 为顶点时，假设存在一合法路径 $(i,j)$ ，则必然存在合法路径 $(j,i)$ ，而在枚举到 $j$ 时，会计算路径 $(j,i)$ ，所以不会漏，而 $i,j$ 在同一连通块，不可能在枚举到其他点时也统计上这个路径，所以不会重。当 $i$ 为分界点时，很显然，每种满足情况 $3$ 的路径都 **有且仅有一个分界点** ，故而既不会重，也不会漏。

#### 代码

有一些小细节，放在代码注释里。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,cnt;
int fa[200005],fb[200005];
int sza[200005],szb[200005];
//a-1 b-0
int finda(int x)
{
	return fa[x]==x?x:fa[x]=finda(fa[x]);
}
int findb(int x)
{
	return fb[x]==x?x:fb[x]=findb(fb[x]);
}
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int main()
{
	n=read();
	for(int i=0;i<=n;i++)	fa[i]=fb[i]=i,szb[i]=sza[i]=1;
	for(int i=1;i<n;i++)
	{
		int u=read(),v=read(),w=read();
		if(w==1)
		{
			int p=finda(u),q=finda(v);
			fa[p]=q;
			sza[q]+=sza[p];//注意，fa[p]=q 表示 p 的祖先是 q ，所以 sz 是修改 q 的而非 p 的。
		}
		if(w==0)
		{
			int p=findb(u),q=findb(v);
			fb[p]=q;
			szb[q]+=szb[p];//同上
		}//这里的 merge 写的有点丑，不过问题不大
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		int p=finda(i),q=findb(i);
		ans=ans+1ll*sza[p]*szb[q]-1;
	}
	printf("%lld\n",ans);
	return 0;
}
```



完结撒花~

---

## 作者：AThousandSuns (赞：7)

这场edu可谓毒瘤……

B差点没做出，C完全不会，D口胡出但打不出……

幸好unr了，不然要掉到连自己都不认识……

---
首先那条有趣的路径其实就是先一段 $0$，再一段 $1$。

那么考虑dp。$f[u][0/1/2/3]$ 表示从下往上到 $u$ 的路径中，全 $0$、全 $1$、先全 $0$ 再全 $1$、先全 $1$ 再全 $0$ 的有多少条。

那么对于一条边 $(u,v,0)$：

先更新全局 $ans$。

当从下往上到 $u$ 的路径是全 $0$ 或空的时，$v$ 可以接全 $0$，全 $1$，先 $1$ 再 $0$ 或者空的。其中 $v$ 选全 $0$ 和空的时，这条路可以双向走。
$$ans+=(f[u][0]+1)(2(f[v][0]+1)+f[v][1]+f[v][3])$$
同理，到 $u$ 的路径是全 $1$ 或先 $1$ 再 $0$ 时，$v$ 那边可以接全 $0$ 或者空的。
$$ans+=(f[u][1]+f[u][3])(f[v][0]+1)$$
到 $u$ 的路径如果是先 $0$ 再 $1$，那么一定是不合法的路径。

接下来更新 $f[u]$。（下面这几条比较显然，就不解释了）
$$f[u][0]+=f[v][0]+1$$
$$f[u][3]+=f[v][1]+f[v][3]$$

对于边 $(u,v,1)$ 也同理。时间复杂度与空间复杂度均为 $O(n)$。

另外似乎有复杂度 $O(n\log n)$ 但是好打也好理解很多的并查集做法，然而我真的只能想到这个……
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> PII;
const int maxn=400040;
#define MP make_pair
#define PB push_back
#define lson o<<1,l,mid
#define rson o<<1|1,mid+1,r
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define ROF(i,a,b) for(int i=(a);i>=(b);i--)
#define MEM(x,v) memset(x,v,sizeof(x))
inline ll read(){
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
int n,el,head[maxn],to[maxn],w[maxn],nxt[maxn];
ll f[maxn][4],ans;
inline void add(int a,int b,int c){
	to[++el]=b;nxt[el]=head[a];head[a]=el;w[el]=c;
}
void dfs(int u,int F){
	ll s=0;
	for(int i=head[u];i;i=nxt[i]){
		int v=to[i];
		if(v==F) continue;
		dfs(v,u);
		if(w[i]){
			s+=f[u][0]*(f[v][1]+1);
			s+=f[u][1]*(f[v][0]+2*f[v][1]+f[v][2]+2);
			s+=f[u][2]*(f[v][1]+1);
			s+=f[v][0]+2*f[v][1]+f[v][2]+2;
			f[u][1]+=f[v][1]+1;
			f[u][2]+=f[v][2]+f[v][0];
		}
		else{
			s+=f[u][0]*(2*f[v][0]+f[v][1]+f[v][3]+2);
			s+=f[u][1]*(f[v][0]+1);
			s+=f[u][3]*(f[v][0]+1);
			s+=2*f[v][0]+f[v][1]+f[v][3]+2;
			f[u][0]+=f[v][0]+1;
			f[u][3]+=f[v][3]+f[v][1];
		}
	}
	ans+=s;
}
int main(){
	n=read();
	FOR(i,1,n-1){
		int u=read(),v=read(),w=read();
		add(u,v,w);add(v,u,w);
	}
	dfs(1,0);
	cout<<ans;
}
```

---

## 作者：timefinder (赞：6)

第一道完全自己切的 dp 紫。

---

定义状态：$f_{x}$ 表示从 $x$ 出发时，终点在其子树内，合法的路径数。因为题中 $(u,v)$ 与 $(v,u)$ 是不同的路径，所以不会重复。

很暴力地，可以枚举每一个点作为原树的根，然后各自单独计算其 $f_{root}$，则答案即为所有 $f_{root}$ 的和。这是 $O(n^2)$ 的。

但是，发现难以直接转移，所以可以设辅助状态：$f_{x,0/1}$。

$f_{x,0}$ 表示从 $x$ 出发，终点在其子树内，路径合法的条数。

$f_{x,1}$ 表示从 $x$ 出发，终点在其子树内，路径全为 $1$ 的条数。

初步方程：（这里 $y\in son_x$，$cur$ 代表从 $x$ 到 $y$ 的边权）

$f_{x,1}=f_{x,1}+f_{y,1}+1$ ，这一行易得。

$f_{x,0}=f_{x,0}+f_{y,cur}+1$ ，即：如果当前点与 $y$ 之间边权为 $0$ ，那么能作为 $y$ 终点的点也能作为 $x$ 的终点，$y$ 本身也可以作为 $x$ 的终点，也就是 $f_{y,0}+1$ ；
如果边权为 $1$,那么在 $y$ 后面的所有边必须为 $1$ ，外加 $y$ 本身，也就是 $f_{y,1}+1$ 。

但是这样太慢了。想到不管根是哪个点，dp 方式相同，因此可以考虑：换根 dp。

先做第一遍 dfs，用上面的暴力做法解决根为 $1$ 的答案。

用 $ans$ 数组记录以 $x$ 为根的路径数，$ans_1=f_{1,0}$ 。

接下来开始换根。首先，假设当前节点的祖先已经被计算过。从当前点出发的合法路径，包括以下几部分。
（ $x$ 代表当前点，$fa$ 代表 $x$ 的父亲，$head_x$ 代表从 $x$ 向根的方向，全是 $1$ 的链的末端）

如果 $x$ 到 $y$ 之间边权为 $0$，那么不管 $fa$ 能到哪里，$x$ 也能到；虽然 $fa$ 能到 $x$ （ $x$ 不能到它自己），但是 $x$ 也能到 $fa$（又是 $fa$ 不能到的），相互抵消。
$ans_x=ans_{fa}$ 。

如果边权为 $1$ ，就要分类讨论。

1、终点恰好在 $x$ 子树内而且路径随意，有 $f_{x,0}$ 种（这是状态的定义）。

2、终点恰好在 $x$ 与 $head_x$ 中间，或者在 $head_x$ 的其它子树内，从 $x$ 到终点必须全部为 $1$。显然 $x$ 子树内，从 $x$ 开始的全 $1$ 路径终点也包含在 $head_x$ 的全 $1$ 终点中，应当减去。最后有 $f_{head_x,1}-f_{x,1}$ 种。

所以 $ans_x=f_{x,0}+f_{head_x,1}-f_{x,1}$ 。

最终答案即为所有 $ans$ 之和。

**code**

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,root=1;
int n,anss,f[N][2],ans[N],head[N];
vector<pair<int,int> > g[N];

void dfs1(int x,int fa){
	if(f[x][0] || f[x][1]) return;
	if(g[x].size()==1 && x!=root) return;
	for(int i=0;i<g[x].size();i++){
		int y=g[x][i].first,cur=g[x][i].second;
		if(y==fa) continue;
		if(cur) head[y]=head[x];
		dfs1(y,x);
		f[x][0]=f[x][0]+f[y][cur]+1;
		if(cur) f[x][1]=f[x][1]+f[y][1]+1;
	}
}
void dfs2(int x,int fa){
	for(int i=0;i<g[x].size();i++){
		int y=g[x][i].first,cur=g[x][i].second;
		if(y==fa) continue;
		if(cur) ans[y]=f[y][0]+f[head[y]][1]-f[y][1];
		else ans[y]=ans[x];
		dfs2(y,x);
	}
}

signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,p;cin>>u>>v>>p;
		g[u].push_back({v,p});
		g[v].push_back({u,p});
	}
	for(int i=1;i<=n;i++) head[i]=i;
	dfs1(1,0);ans[1]=f[1][0];
	dfs2(1,0);
	
	for(int i=1;i<=n;i++) anss+=ans[i];
	cout<<anss;
}
```

---

## 作者：Ruan_ji (赞：5)

### 题目大意
题目其实很好理解，需要注意的一点是边是无向边，需要存两遍，不然很容易寄掉不知道为什么。

其实这题就是 ~~（一眼丁真，鉴定为动态规划）~~。我们很好发现是动态规划。如果贸然使用深搜容易寄。

### 思路
我们首先读入 $n$，和 $n-1$ 条边，并建边 $u$，$v$，$w$ 双边。因为需要存边权所以我们使用 ```pair```。

从点 $1$ 开始深搜，标记 $1$ 的父亲节点为 $0$，开始遍历。

我们定义一个 dp 数组。计算 $dp[u][0,1,2,3]$，枚举儿子 $v$，继递归遍历 ```dfs(v,u)```，准备好 $dp[u][0,1,2,3]$。

如果 $(u,v)$ 的边权，也就是 ```w[u,v]==1```，考虑  $dp[u][0,1,2,3]$，按照公式更新。 如果 $(u,v)$ 的边权，也就是 ```w[u,v]==0```，考虑 $dp[v][0,1,2,3]$，按照公式更新。

注意 $u$ 本身的键，记得计数加一。最后我们输出答案，答案是累计得到的。

这道题目就是动态规划和深度优先搜索的一个非常好的结合体，看起来很难，其实只要知道思路就迎刃而解了。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
typedef long long ll;
const int maxn=400040;
int n,e;
int head[maxn],to[maxn],w[maxn],nxt[maxn];
ll f[maxn][4],ans;
inline ll read()
{
	char ch=getchar();ll x=0,f=0;
	while(ch<'0' || ch>'9') f|=ch=='-',ch=getchar();
	while(ch>='0' && ch<='9') x=x*10+ch-'0',ch=getchar();
	return f?-x:x;
}
inline void add(int a,int b,int c)
{
	to[++e]=b;
	nxt[e]=head[a];
	head[a]=e;
	w[e]=c;
}
void dfs(int u,int F)
{
	ll s=0;
	for(int i=head[u];i;i=nxt[i])
	{
		int v=to[i];
		if(v==F) continue;
		dfs(v,u);
		if(w[i])
		{
			s+=f[u][0]*(f[v][1]+1);
			s+=f[u][1]*(f[v][0]+2*f[v][1]+f[v][2]+2);
			s+=f[u][2]*(f[v][1]+1);
			s+=f[v][0]+2*f[v][1]+f[v][2]+2;
			f[u][1]+=f[v][1]+1;
			f[u][2]+=f[v][2]+f[v][0];
		}
		else
		{
			s+=f[u][0]*(2*f[v][0]+f[v][1]+f[v][3]+2);
			s+=f[u][1]*(f[v][0]+1);
			s+=f[u][3]*(f[v][0]+1);
			s+=2*f[v][0]+f[v][1]+f[v][3]+2;
			f[u][0]+=f[v][0]+1;
			f[u][3]+=f[v][3]+f[v][1];
		}
	}
	ans+=s;
}
int main()
{
	n=read();
	FOR(i,1,n-1)
	{
		int u=read(),v=read(),w=read();
		add(u,v,w);
		add(v,u,w);
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}
```

---

## 作者：Oxide (赞：5)

# Solution
感觉很久没有自己调出来一道 $DP$ 了。

我们分类 $DP$。令 $f[i][0]$ 为以这个点为根的子树内部起点为 $i$ 的类似 $00011111$ 与 $00000000$ 串的个数， $f[i][1]$ 为以这个点为根的子树内部起点为 $i$ 的类似 $11111111$ 串的个数。

首先我们讨论 $x$，$y$，其中 $y$ 是 $x$ 的爸爸。

考虑计算 $f$ 数组。易得无论 $w(x,y)$ 是什么值，首先爸爸的值是儿子的相应边权的值加一。考虑 $w(x,y)==0$ 的情况，还要加上 $f[x][1]$。（注意还要加上连接 $x$ 与 $y$ 的边）

好了我们令 $g[i][0]$ 为以这个点为根起点为 $i$ 的类似 $00011111$ 与 $00000000$ 串的个数， $g[i][1]$ 为以这个点为根，起点为 $i$ 的类似 $11111111$ 串的个数，$g$ 的初始值赋为 $f$。（代码实现里我是直接用 $f$，但是推导过程是有区别的）

好了我们放图（画质感人）：
![](https://img2020.cnblogs.com/blog/1889894/202006/1889894-20200605111816214-316419144.png)

分类讨论：

- $w(x,y)==1$：儿子不可能继承父亲的 $0$ 情况，所以直接用爸爸减儿子得到其他儿子的值再把儿子加回去。$ans=g[y][1]-f[x][1]+f[x][1]+f[x][0]$。
- $w(x,y)==0$：这里有个坑。父亲在算 $x$ 的时候，不仅会加 $f[x][0]$，还会加 $f[x][1]$，方法同上，最后还要记得加上父亲的全 $1$ 串个数。

# Code
```cpp
#include <cstdio>
typedef long long ll;

const int N = 2e5 + 5;

int n, head[N], nxt[N << 1], to[N << 1], w[N << 1], cnt;
ll f[N][2], ans;

int read() {
	int x = 0, f = 1; char s;
	while((s = getchar()) > '9' || s < '0') if(s == '-') f = -1;
	while(s <= '9' && s >= '0') x = (x << 1) + (x << 3) + (s ^ 48), s = getchar();
	return x * f;
}

void addEdge(const int u, const int v, const int val) {
	nxt[++ cnt] = head[u], to[cnt] = v, head[u] = cnt, w[cnt] = val;
}

void dfs1(const int u, const int fa) {
	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(v == fa) continue;
		dfs1(v, u);
		f[u][w[i]] += f[v][w[i]] + 1;
		if(! w[i]) f[u][0] += f[v][1];
	}
}

void dfs2(const int u, const int fa) {
	for(int i = head[u]; i; i = nxt[i]) {
		int v = to[i];
		if(v == fa) continue;
		if(w[i] == 1) f[v][1] = f[u][1];
		if(! w[i]) f[v][0] = f[u][0] - f[v][1] + f[u][1];
		dfs2(v, u);
	}
}

int main() {
	int u, v, w;
	n = read();
	for(int i = 1; i < n; ++ i) {
		u = read(), v = read(), w = read();
		addEdge(u, v, w); addEdge(v, u, w);
	}
	dfs1(1, 0); dfs2(1, 0);
	for(int i = 1; i <= n; ++ i) ans += f[i][0] + f[i][1];
	printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：Linge_Zzzz (赞：3)

教练把这题出在了模拟赛。

很快啊，上来一眼感觉是点分治板子题，就赶紧写，写完了之后一直 WA on test #4，调了三个小时没调出来，气人，后来同学用各种方法切了，我还在沉迷于淀粉质无法自拔。

以上为闲话。

看到题目描述中的“路径”，很容易想到点分治。点分治的板子我就不说了，重点说说统计路径条数的部分。

假设我们当前遍历到的路径是以 $u$ 为根的子树，我们统计下面几种东西：

1. **从根到当前子树的点**，边全部是 $0$ 的路径条数，记为 $c0$。
2. 从根到当前子树的点，边全部是 $1$ 的路径条数，记为 $c1$。
3. 从根到当前子树的点，边权先 $0$ 后 $1$ 的路径条数，记为 $c01$。
4. 从根到当前子树的点，边权先 $1$ 后 $0$ 的路径条数，记为 $c10$。

对于已经遍历过的子树，同样地统计出 $t0,t1,t01,t10$。

考虑如何统计答案，分类讨论。

首先，根节点也要统计在内，所以答案要加上 $2\times c0$（从$c0$走到根 和 从根走到 $c0$）。

同理，答案还要加上 $2\times c1,c01,c10$。

1. 路径的起点在 $c0$，合法的路径终点有 $t0$、$t1$、$t01$，所以答案要加上 $c0\times (t0+t1+t01)$。
2. 路径的起点在 $c1$，合法的路径终点只有 $t1$，所以答案要加上 $c1\times t1$。
3. 路径的起点在 $c10$，合法的路径终点只有 $t1$，所以答案要加上 $c10\times t1$。
4. 路径的起点在 $c01$，**没有合法的路径终点**（我就挂在这）。

对于路径的起点在 $t0,t1,t10,t01$ 的情况，同样地，答案要加上 $t0\times (c0+c1+c01)+t1\times c1+t10 \times c1$。

这样我们就 ~~优雅地~~ 解决了这道题。

最后强调一下不要求错重心。

# Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+10,INF=0x3f3f3f3f3f3f3f3f;
int n;
struct edge{
	int v,w,nxt;
}e[N*2];
int head[N],cnt=1;
void add(int u,int v,int w){
	e[cnt].v=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt++;
} 
int ans=0;
bool vis[N];
int root,mnroot;
int siz[N],s;
void getroot(int u,int fa){
	siz[u]=1;
	int mx=0;
	for(int i=head[u];i;i=e[i].nxt){
		if(e[i].v!=fa&&!vis[e[i].v]){
			getroot(e[i].v,u);
			siz[u]+=siz[e[i].v];
			mx=max(mx,siz[e[i].v]);
		}
	}
	mx=max(mx,s-siz[u]);
	if(mx<mnroot){
		mnroot=mx;
		root=u;
	}
}
int c0,c01,c10,c1;
void getdis(int u,int s1,int s2,int fa){
	if(s2==-1){
		if(s1)c1++;
		else c0++;
	}else{
		if(s1)c10++;
		else c01++;
	}
	for(int i=head[u];i;i=e[i].nxt){
		if(e[i].v!=fa&&!vis[e[i].v]){
			int t;
			if(e[i].w!=s1){
				if(s2==-1)t=e[i].w;
				else t=s2;
			}else{
				if(s2==-1)t=-1;
				else continue;
			}
			getdis(e[i].v,s1,t,u);
		}
	}
}
void calc(int u,int fa){
	int t0=0,t1=0,t01=0,t10=0;
	for(int i=head[u];i;i=e[i].nxt){
		if(!vis[e[i].v]&&e[i].v!=fa){
			c0=c1=c01=c10=0;
			getdis(e[i].v,e[i].w,-1,u);
			ans+=2*c0+2*c1+c01+c10;
			ans+=c0*(t1+t0+t01);
			ans+=c1*t1;
			ans+=c10*t1;
			ans+=t0*(c0+c1+c01);
			ans+=t1*c1;
			ans+=t10*c1;
			t1+=c1,t0+=c0,t01+=c01,t10+=c10;
		}
	}
}
void solve(int u,int fa){
	vis[u]=1;
	calc(u,fa);
	for(int i=head[root];i;i=e[i].nxt){
		if(!vis[e[i].v]&&e[i].v!=fa){
			s=siz[e[i].v];
			mnroot=INF;
			getroot(e[i].v,u);
			solve(root,u);
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n;
	for(int i=1;i<n;i++){
		int u,v,w;cin>>u>>v>>w;
		add(u,v,w);add(v,u,w);
	}
	s=n;
	mnroot=INF;
	getroot(1,0);
	solve(root,0);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：xhhhh36 (赞：3)

[传送门](https://www.luogu.com.cn/problem/CF1156D)

考虑组合计数：将 $1$ 边和 $0$ 边分开建图，把全 $1$ 为边的连通块和全为 $0$ 的连通块找出来分类讨论，经过全 $1$ 或者全 $0$ 的边情况比较简单。考虑前一段走 $1$ 后一段走 $0$ 的情况，此时枚举连接 $0$、$1$ 边权的点，计算此点所在的全 $1$ 连通块的数量以及全 $0$ 连通块的点数量，乘起来计数即可。
# AC code
```cpp
#include <bits/stdc++.h>
using namespace std;
struct Edge
{
	int to,nxt;
}e[1000005],e1[1000005];
int h[500005],h1[500005],cnt1,cnt;
void add_edge(int u,int v,int c)
{
	if (c==1)
	{
		e1[++cnt1].to=v;
		e1[cnt1].nxt=h1[u];
		h1[u]=cnt1;
	}
	else
	{
		e[++cnt].to=v;
		e[cnt].nxt=h[u];
		h[u]=cnt;
	}
}
int n;
bool v[500005],v1[500005],v2[500005];
long long ct=0;
long long tmp[500005];
long long tmp1[500005];
void dfs1(int x,int fa)
{
	v[x]=1;
	ct++;
	for (int i=h[x];i!=-1;i=e[i].nxt)
	{
		int u=e[i].to;
		if (u==fa) continue;
		dfs1(u,x);
	}
}
void dfs2(int x,int fa)
{
	tmp[x]=ct;
	for (int i=h[x];i!=-1;i=e[i].nxt)
	{
		int u=e[i].to;
		if (u==fa) continue;
		dfs2(u,x);
	}
}
void dfs3(int x,int fa)
{
	v1[x]=1;
	ct++;
	for (int i=h1[x];i!=-1;i=e1[i].nxt)
	{
		int u=e1[i].to;
		if (u==fa) continue;
		dfs3(u,x);
	}
}
void dfs4(int x,int fa)
{
	tmp1[x]=ct;
	for (int i=h1[x];i!=-1;i=e1[i].nxt)
	{
		int u=e1[i].to;
		if (u==fa) continue;
		dfs4(u,x);
	}
}
long long ans;
void dfs_ans(int x,int fa)
{
	v2[x]=1;
	ans+=(tmp[x]-1)*(tmp1[x]-1);
	for (int i=h[x];i!=-1;i=e[i].nxt)
	{
		int u=e[i].to;
		if (u==fa) continue;
		dfs_ans(u,x);
	}
}
signed main()
{
	memset(h,-1,sizeof(h));
	memset(h1,-1,sizeof(h1));
	cin>>n;
	for (int i=1;i<n;i++)
	{
		int u,v,c;
		cin>>u>>v>>c;
		add_edge(u,v,c);
		add_edge(v,u,c);
	}
	for (int i=1;i<=n;i++)
	{
		if (!v[i])
		{
			ct=0;
			dfs1(i,0);
			dfs2(i,0);
			ans+=ct*(ct-1);
		}
	}
	for (int i=1;i<=n;i++)
	{
		if (!v1[i])
		{
			ct=0;
			dfs3(i,0);
			dfs4(i,0);
			ans+=ct*(ct-1);
		}
	}
	for (int i=1;i<=n;i++)
	{
		if (!v2[i])
		{
			dfs_ans(i,0);
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：AbsMatt (赞：3)

## [题目传送器](https://www.luogu.com.cn/problem/CF1156D)
## [更爽的阅读体验](https://yaohaoyou.blog.luogu.org/solution-cf1156d)

# 题意
一条路径有 $3$ 种类型。
1. 从头到尾每条边的权值都是 $0$。
2. 从头到尾每条边的权值都是 $1$。
3. 刚开始有一段权值都是 $1$，剩下权值都是 $0$。

问共有多少条满足的方案。

# 思路
### 做法
这题可以直接分成题意的 $3$ 种类型讨论，每个点 $i$ 都要进入两个并查集，一个是记录 $i$ 在哪个边权为 $1$ 的连通块，另一个是记录 $i$ 在哪个边权为 $0$ 的连通块。

设第 $i$ 个点的祖先为 $fa_{i,0}$ 和 $fa_{i,1}$，$i$ 号点所在边权为 $k(k\in[0,1])$ 的连通块大小为 $siz_{i,k}$，则 $ans=\sum_{i=1}^{n} siz_{fa_{i,0}} \times (siz_{fa_{i,0}}-1)+ siz_{fa_{i,1}} \times (siz_{fa_{i,1}}-1)+(siz_{fa_{i,0}}-1) \times (siz_{fa_{i,1}}-1)$。

### 模拟样例
```
输入数据：
7
2 1 1
3 2 0
4 2 1
5 2 0
6 7 1
7 2 1

输出数据：
34
```

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1156D/638afcedfa6d4eecb5e63ed4a099a832b54e2fbc.png)

$fa_{1,0}=1$，$fa_{1,1}=1$。

$fa_{2,0}=2$，$fa_{2,1}=1$。

$fa_{3,0}=2$，$fa_{3,1}=3$。

$fa_{4,0}=4$，$fa_{4,1}=1$。

$fa_{5,0}=2$，$fa_{5,1}=5$。

$fa_{6,0}=6$，$fa_{6,1}=1$。

$fa_{7,0}=7$，$fa_{7,1}=1$。

---
$siz_{1,0}=1$，$siz_{1,1}=5$。

$siz_{2,0}=3$，$siz_{2,1}=0$。

$siz_{3,0}=0$，$siz_{3,1}=1$。

$siz_{4,0}=1$，$siz_{4,1}=0$。

$siz_{5,0}=0$，$siz_{5,1}=1$。

$siz_{6,0}=1$，$siz_{6,1}=0$。

$siz_{7,0}=1$，$siz_{7,1}=0$。

---

**注：由于遍历顺序等影响因素，这个具体的结果可能不同，以上数据是手动模拟得出的，仅供理解，请不要拿代码输出进行比较。**

### 总结
本题考查**并查集**，并查集最开始记得初始化。时间复杂度为 $O(n)$。最后输出的答案较大，要开 long long。

## AC Code
```cpp
#include <bits/stdc++.h>  // 开始了
#define int long long     // 开 long long
using namespace std;
const int maxn = 4e5 + 10;
int n, m, ans;
bool vis[maxn];
int siz[maxn][2], fa[maxn][2];  // siz 数组 和 fa 数组
// 建图
struct edge
{
    int nxt, to, w;
} e[maxn];
int cnt = 0, head[maxn];
void add(int u, int v, int w)
{
    e[++cnt] = {head[u], v, w};
    head[u] = cnt;
}
// 并查集
int find(int x, int y)  // 寻找祖先
{
    if (fa[x][y] == x)
        return x;
    return fa[x][y] = find(fa[x][y], y);
}
void join(int x, int y, int c)  // 合并
{
    int fx = find(x, c), fy = find(y, c);
    if (fx == fy)
        return;
    fa[fx][c] = fy;
    return;
}

// 遍历整棵树
void dfs(int u, int fa)
{
    for (int i = head[u]; i; i = e[i].nxt)
    {
        int v = e[i].to;
        if (v == fa)
            continue;
        join(u, v, e[i].w);
        dfs(v, u);
    }
}

signed main()
{
    // 输入
    scanf("%lld", &n);
    for (int i = 1; i < n; i++)
    {
        int u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    // 初始化
    for (int i = 1; i <= n; i++)
    {
        fa[i][0] = i;
        fa[i][1] = i;
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
    {
        siz[find(i, 0)][0]++;
        siz[find(i, 1)][1]++;
    }
    // 统计答案
    for (int i = 1; i <= n; i++)
    {
        ans += (siz[i][0] * (siz[i][0] - 1));
        ans += (siz[i][1] * (siz[i][1] - 1));
    }
    for (int i = 1; i <= n; i++)
    {
        ans += ((siz[find(i, 0)][0] - 1) * (siz[find(i, 1)][1] - 1));
    }
    // 输出
    printf("%lld\n", ans);
}

```


---

## 作者：William2022 (赞：2)

# CF1156D  
## 入手  
一条有效路径上，边权一定先是若干个 $0$，然后再是若干个 $1$。  
![](https://cdn.luogu.com.cn/upload/image_hosting/ntv5re30.png)   
就像这样，当然，也可以没有 $0$ 或者没有 $1$。  

如上图，$2$ 是一个很特殊的点，这个点分割了“合法”路径，分割成了一段只有 $0$，一段只有 $1$。  
我们就可以枚举每个点，计算每个点作为这种分割点能产生多少“合法”路径。  
## 解法  
![](https://cdn.luogu.com.cn/upload/image_hosting/q1jsckvt.png)  
这里举一个特殊点为 $X$ 的情况。  
注意到：  
1. 包括 $X$ 点，有 $4$ 个点可仅通过 $0$ 边到达 $X$  
2. 包括 $X$ 点，有 $X$ 可仅通过 $1$ 边到达 $7$ 个点  

因此包括 $X\to X$，$X$ 作为分割点共有 $4\times7=28$ 种可能路径。  
因为题目要求不能自己到自己，所以还需要减一。

这下明白了，只要对每个点 $u$ 算出：  
1. 有几个点能通过全 $0$ 的边与 $u$ 联通，记作 $in_u$
2. 有几个点能通过全 $1$ 的边与 $u$ 联通，记作 $out_u$

答案即为 $ans=\sum (in_u\times out_u - 1)$

至于怎么求 $in_u$ 和 $out_u$，方法应该不少，我选择使用两个并查集，一个只有 $0$ 边，一个只有 $1$ 边，$in_u$ 与 $out_u$ 就分别是这两个并查集中 $u$ 所在连通块的大小。   
## 代码  
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N=2e5+10;
int n;

struct dsu{
	int fa[N],sz[N];
	
	void init(){
		for(int i=1;i<=n;i++)fa[i]=i;
		for(int i=1;i<=n;i++)sz[i]=1;
	}
	int rt(const int &x){
		if(x==fa[x])return x;
		return fa[x]=rt(fa[x]);
	}
	void merge(int x,int y){
		x=rt(x);y=rt(y);
		fa[x]=rt(y);
		sz[y]+=sz[x];
	}
	int cnt(int x){//表示这个节点所在的联通块内有总共有多少个节点
		return sz[rt(x)];
	}
}a,b;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);
	
	cin>>n;
	
	a.init();b.init();
	
	for(int i=1;i<n;i++){
		int u,v,w;
		cin>>u>>v>>w;
		if(w){
			a.merge(u,v);
		}else{
			b.merge(u,v);
		}
	}
	long long ans=0;
	for(int i=1;i<=n;i++){
		ans+=(1LL*a.cnt(i)*b.cnt(i))-1;
	}
	cout<<ans;
}
```

---

## 作者：Tyyyyyy (赞：2)

# CF1156D

这题居然没人用点分治吗qwq

### 题目分析
~~点分治，求解树上路径问题的利器，你值得拥有。~~

我们考虑套点分治板子，然后只需要解决统计答案的问题。

我们在点分治过程中依次遍历每棵子树，记 $cnt_{0/1/2/3}$ 表示**已经遍历完的所有子树中**，到当前根节点的路径为全 $0$、全 $1$、先 $1$ 后 $0$、先 $0$ 后 $1$ 的节点数量，记 $tmp_{0/1/2/3}$ 表示**当前遍历的这棵子树中**，到当前根节点的路径为全 $0$、全 $1$、先 $1$ 后 $0$、先 $0$ 后 $1$ 的节点数量。

然后大力分类讨论合法的情况：

- 全 $0$ 或全 $1$ 的路径肯定合法，因此答案要加上 $2cnt_0tmp_0+2cnt_1tmp_1$。注意根节点也能与当前子树中的点配对，所以答案还要加上 $2tmp_0+2tmp_1$。

- 其他合法的路径只能是先一段 $0$，后一段 $1$，其中又分几种情况：

  - $0$ 段**完全**来自其他子树，$1$ 段**完全**来自当前子树。所以答案要加上 $tmp_1cnt_0$。
  - $1$ 段**完全**来自其他子树，$0$ 段**完全**来自当前子树。所以答案要加上 $tmp_0cnt_1$。
  - 其他子树贡献了一段先 $0$ 后 $1$ 的段，因此当前子树只能全为 $1$。所以答案要加上 $tmp_1cnt_3$。
  - 当前子树贡献了一段先 $0$ 后 $1$ 的段，因此其他子树只能全为 $1$。所以答案要加上 $tmp_3cnt_1$。
  - 其他子树贡献了一段全 $0$ 段，因此当前子树可以为**自上而下**先 $0$ 后 $1$，即**自下而上**先 $1$ 后 $0$。所以答案要加上 $tmp_2cnt_0$。
  - 当前子树贡献了一段全 $0$ 段，因此其他子树可以为**自上而下**先 $0$ 后 $1$，即**自下而上**先 $1$ 后 $0$。所以答案要加上 $tmp_0cnt_2$。
  - 当前子树中的先 $0$ 后 $1$ 和先 $1$ 后 $0$ 段都可以与当前根节点配对，所以答案还要加上 $tmp_2+tmp_3$。

剩下的就是点分治模板内容了，就不再赘述。~~注意重心不要求假了。~~

Code：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=2e5+10;
int n,tot,h[N];
struct edge
{
	int v,w,nxt;
}e[N<<1];
void add(int u,int v,int w)
{
	e[++tot]=(edge){v,w,h[u]};
	h[u]=tot;
}
bool vis[N];
int cor,ss,siz[N];
void getcor(int u,int fa,int all)
{
	int mxw=0;siz[u]=1;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v])continue;
		getcor(v,u,all),siz[u]+=siz[v]; 
		mxw=max(mxw,siz[v]);
	}
	mxw=max(mxw,all-mxw);
	if(mxw<ss)ss=mxw,cor=u;
}
void getsiz(int u,int fa)
{
	siz[u]=1;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v])continue;
		getsiz(v,u),siz[u]+=siz[v]; 
	}
}
ll tmp[4],cnt[4];//0,1,10,01（叶子到根） 
void getdata(int u,int fa,int typ)
{
	tmp[typ]++;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v])continue;
		int nxt;
		if(typ==0&&e[i].w)nxt=2;
		else if(typ==1&&!e[i].w)nxt=3;
		else if(typ==2&&!e[i].w)continue;
		else if(typ==3&&e[i].w)continue;
		else nxt=typ;
		getdata(v,u,nxt);
	}
}
ll ans;
void solve(int u,int fa)
{
	vis[u]=1;
	cnt[0]=cnt[1]=cnt[2]=cnt[3]=0;
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v])continue;
		tmp[0]=tmp[1]=tmp[2]=tmp[3]=0;
		getdata(v,u,e[i].w);
		ans+=tmp[0]*cnt[0]*2+tmp[1]*cnt[1]*2;
		ans+=tmp[0]*cnt[2]+tmp[2]*cnt[0]+tmp[1]*cnt[3]+tmp[3]*cnt[1]+tmp[0]*cnt[1]+tmp[1]*cnt[0];
		ans+=tmp[0]*2+tmp[1]*2+tmp[2]+tmp[3];
		cnt[0]+=tmp[0],cnt[1]+=tmp[1],cnt[2]+=tmp[2],cnt[3]+=tmp[3];
	}
	for(int i=h[u];i;i=e[i].nxt)
	{
		int v=e[i].v;
		if(v==fa||vis[v])continue;
		getsiz(v,u),ss=1e9,getcor(v,u,siz[v]);
		solve(cor,u);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1,u,v,w;i<n;i++)
		scanf("%d%d%d",&u,&v,&w),add(u,v,w),add(v,u,w);
	ss=1e9,getcor(1,0,n);
	solve(cor,0);
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：orson111 (赞：2)

## 前言
搞不懂为啥难度评分这么高。。。
## 正片开始
这一条路径上会有一个转折点 $u$，从 $x$ 到 $u$ 全是 $0$，从 $u$ 到 $y$ 全是 $1$。

建立两个并查集，边权为 $1$ 的边连在第一个并查集，边权为 $0$ 的边连在第二个并查集，维护好 $sz$ 数组。

小 M：硕以整么维护呢？

并查集合并的时候，假设合并两点的最高祖宗分别是 $fu$ 和 $fv$，那么。。。
```cpp
    sz[fu]+=sz[fv];    //...就把 fv 的 sz 累加到 fu 上
    sz[fv]=0;          //你可以省略这一步
    fa[fv]=fu;         //最后是常规 Union
```


最后，我们使用乘法原理推算出，以一个点 $u$ 为转折点的合法路径数是 $sz_{find_u}sz2_{find_u}$ **再减掉一！（$x \ne y$）**

## 上代码！
直接复制将会受到评测机的惩罚！
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll n,fa[200009],sz[200009],fa2[200009],sz2[200009];
ll Find(ll u){return (fa[u]==u?u:(fa[u]=Find(fa[u])));}
void Union(ll u,ll v){
    u=Find(u),v=Find(v);
    if(u==v) return;
    sz[u]+=sz[v];
    sz[v]=0;
    fa[v]=u;
}
ll Find2(ll u){return (fa2[u]==u?u:(fa2[u]=Find2(fa2[u])));}
void Union2(ll u,ll v){
    u=Find2(u),v=Find2(v);
    if(u==v) return;
    sz2[u]+=sz2[v];
    sz2[v]=0;
    fa2[v]=u;
}
int mian(){
    cin>>n;
    for(ll i=1;i<=n;i++) fa[i]=i,sz[i]=1,fa2[i]=i,sz2[i]=1;
    for(ll i=1,u,v,c;i<n;i++){
        cin>>u>>v>>c;
        if(c) Union(u,v);
        else Union2(u,v);
    }
    ll ans=0;
    for(ll i=1;i<=n;i++) ans+=sz[Find(i)]*sz2[Find2(i)]-1;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：hfctf0210 (赞：2)

很容易想到一个DP，令f[i]表示以i为根的子树，从下面的节点走上来，最后一步是黑边的点数，g[i]表示全走白边的点数，于是就有f[u]=Σ(f[son]+g[son]+1)，son为经过黑边的son，g[u]=Σ(g[son]+1)，son为经过白边的son。然后这个东西很容易换根DP，根据黑白边讨论一下即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+7;
int n,cnt,f[N],g[N],nf[N],ng[N],hd[N],v[N<<1],nxt[N<<1],w[N<<1];
ll ans;
void adde(int x,int y,int z){v[++cnt]=y,nxt[cnt]=hd[x],w[cnt]=z,hd[x]=cnt;}
void dfs(int u,int fa)
{
	for(int i=hd[u];i;i=nxt[i])
	if(v[i]!=fa)
	{
		dfs(v[i],u);
		if(!w[i])g[u]+=g[v[i]]+1;
		else f[u]+=f[v[i]]+g[v[i]]+1;
	}
}
void dfs2(int u,int fa)
{
	ans+=nf[u]+ng[u];
	for(int i=hd[u];i;i=nxt[i])
	if(v[i]!=fa)
	{
		if(!w[i])nf[v[i]]=f[v[i]],ng[v[i]]=ng[u];
		else nf[v[i]]=nf[u]-g[v[i]]+ng[u],ng[v[i]]=g[v[i]];
		dfs2(v[i],u);
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=1,x,y,z;i<n;i++)scanf("%d%d%d",&x,&y,&z),adde(x,y,z),adde(y,x,z);
	dfs(1,0);
	nf[1]=f[1],ng[1]=g[1],dfs2(1,0);
	cout<<ans;
}
```


---

## 作者：huangmingyi (赞：1)

#### 分析
1. 枚举分界点 $x$，在 $x$ 之前全走 $0$ 或者不走，$x$ 之后全走 $1$ 或者不走。
2. 维护并查集统计与点 $x$ 只靠边权 $0$ 相连的点数 $siz0_{x}$，同理 $siz1_{x}$。
3. 用函数 $\operatorname{find}$ 来查找祖先结点。
4. 答案为：$ans = ans + siz0_{\operatorname{find}(x)} \times siz1_{\operatorname{find}(x)} -1$。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int nxt,w;
};
vector<node> nbr[(int)2e5+5];
int n,cnt,f[(int)2e5+5],dp[(int)2e5+5],fa0[(int)2e5+5],fa1[(int)2e5+5],siz0[(int)2e5+5],siz1[(int)2e5+5];
int find1(int x){
	if(fa1[x]==x){
		return x;
	}
	return fa1[x]=find1(fa1[x]);
}
int find0(int x){
	if(fa0[x]==x){
		return x;
	}
	return fa0[x]=find0(fa0[x]);
}
void un0(int x,int y){
	x=find0(x);
	y=find0(y);
	if(x!=y){
		fa0[x]=y;
		siz0[y]+=siz0[x];
		siz0[x]=0; 
	}
	return ;
}
void un1(int x,int y){
	x=find1(x);
	y=find1(y);
	if(x!=y){
		fa1[x]=y;
		siz1[y]+=siz1[x];
		siz1[x]=0;
	}
	return ;
}
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		fa1[i]=fa0[i]=i;
		siz1[i]=siz0[i]=1;
	}
	for(int i=1;i<n;i++){
		int x,y,w;
		cin>>x>>y>>w;
		nbr[x].push_back((node){y,w});
		nbr[y].push_back((node){x,w});
		if(w==1){
			un1(x,y);
		}else{
			un0(x,y);
		}
	}
	for(int i=1;i<=n;i++){
		cnt+=siz1[find1(i)]*siz0[find0(i)]-1;
	}
	cout<<cnt<<endl;
    return 0;
}
```

---

## 作者：王熙文 (赞：1)

## 题解

比较套路的换根 dp，但我过了样例后没有一次 AC（忘了一种情况），以后需要注意。

（为了下面表述方便，$u$ 到 $v$ 的边权设为 $w_{u,v}$。）

首先，看到在树上与路径和边权的形态有关的题，很容易想到树形 dp，而对路径上边权的要求，需要将 dp 的状态多设一维：$dp_{u,0/1}$ 表示从 $u$ 到 $v$，走的第一条边是 $0/1$ 时，路径满足要求的 $v$ 的个数。

先考虑子树内的：

$dp_{u,0}$：对于 $u$ 的所有与它边权为 $0$ 的子节点 $v$，$v$ 往下的边权可以是 $0$ 也可以是 $1$，而答案也要加上 $u \to v$ 这条路径，所以这里的转移是：$dp_{u,0} = \sum dp_{v,0} + dp_{v,1} + 1$（当 $w_{u,v}=0$ 时）

$dp_{u,1}$：对于 $u$ 的所有与它边权为 $1$ 的子节点 $v$，$v$ 往下的边权只能是 $1$，而答案也要加上 $u \to v$ 这条路径，所以这里的转移是：$dp_{u,1} = \sum dp_{v,1} + 1$（当 $w_{u,v}=1$ 时）

因为这里是求的子树内的，没有考虑子树外的情况，所以考虑换根：（设 $u$ 的父亲为 $fa$）

$dp_{u,0}$：如果 $w_{u,fa}=0$，则 $u$ 可以扩展到子树外。显然，$dp_{fa,0}$ 能到的点 $dp_{u,0}$ 都能到，那我们能不能直接将答案加上 $dp_{fa,0}$ 呢？不行的。因为 $dp_{fa,0}$ 也可以到达 $dp_{u,1}$ 能到的地方（我就在这里 WA 了一次），所以答案需要减去 $dp_{u,1}$。接下来，还要加上 $dp_{fa,1}$，这是显然的（实在不懂可以画个图理解），所以状态转移方程为 $dp_{u,0} = dp_{fa,0} + dp_{fa,1}-dp_{u,1}$。

$dp_{u,1}$：如果 $w_{u,fa}=1$，那么 $dp_{u,1}$ 能到的点 $dp_{fa,1}$ 也能到，而 $dp_{fa,0}$ 不能用是因为第一条边权为 $1$ 后之后的边权不能有 $0$。这里的转移是 $dp_{u,1} = dp_{fa,1}$。

最后的答案便是所有的 $dp_{u,0}+dp_{u,1}$ 加起来。

## 启发

讨论的情况不能少，不能漏，要想明白。过了样例不要掉以轻心。

## 参考代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int tot=0,var[400010],len[400010],nxt[400010],head[200010];

void add(int u,int v,int w)
{
    var[++tot]=v;
    len[tot]=w;
    nxt[tot]=head[u];
    head[u]=tot;
}

int dp[200010][2];

void dfs1(int u,int fa) // 子树内
{
    for(int i=head[u]; i; i=nxt[i])
    {
        int v=var[i],w=len[i];
        if(v==fa) continue;
        dfs1(v,u);
        if(w==0)
        {
            dp[u][0]+=dp[v][0]+dp[v][1]+1;
        }
        else
        {
            dp[u][1]+=dp[v][1]+1;
        }
    }
}

void dfs2(int u,int fa) // 换根
{
    for(int i=head[u]; i; i=nxt[i])
    {
        int v=var[i],w=len[i];
        if(v==fa) continue;
        if(w==0)
        {
            dp[v][0]=dp[u][0]+dp[u][1]-dp[v][1];
        }
        else
        {
            dp[v][1]=dp[u][1];
        }
        dfs2(v,u);
    }
}

int main()
{
    int n,u,v,w;
    long long ans=0;
    scanf("%d",&n);
    for(int i=1; i<n; ++i)
    {
        scanf("%d%d%d",&u,&v,&w);
        add(u,v,w),add(v,u,w);
    }
    dfs1(1,0);
    dfs2(1,0);
    for(int i=1; i<=n; ++i)
    {
        ans+=dp[i][0]+dp[i][1];
    }
    printf("%lld",ans);
    return 0;
}
```



---

## 作者：xvl_ (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/CF1156D)

一道树形 dp 题。

看到路径计数就很容易想到换根。

设 $dp_{u,0}$ 表示以 $u$ 为根的子树中满足条件的路径个数，$dp_{u,1}$ 表示以 $u$ 为根的子树中边权全为 $1$ 的路径个数。

假设现在遍历到了结点 $u$，它有一个儿子是 $v$。若边权为 $1$，令 
$$dp_{u,0} \leftarrow dp_{u,0}+dp_{v,1}+1$$
$$dp_{u,1} \leftarrow dp_{u,1}+dp_{v,1}+1$$
否则，令
$$dp_{u,0}\leftarrow dp_{u,0}+dp_{v,0}+1$$
接下来要再进行一次换根 dp，计算以其它结点为根时的答案。

假设现在遍历到了结点 $u$，它有一个儿子是 $v$。若边权为 $1$，令
$$dp_{v,0} \leftarrow dp_{v,0}+dp_{u,1}-dp_{v,1}$$
$$dp_{v,1} \leftarrow dp_{u,1}$$
否则，令
$$dp_{v,0} \leftarrow dp_{cur,0}$$
最后 $\sum_{u=1}^{n}\limits dp_{u,0}$ 即是答案。

### Code

```cpp
#include <bits/stdc++.h>

const long long IMX = 1ll << 30;
const long long LMX = 1ll << 60;

const long long MOD1 = 998244353;
const long long MOD2 = 1000000007;
const long long MOD3 = 1000000009;

using ll = long long;
// using i128 = __int128;
using ld = long double;
using f128 = __float128;

namespace xvl_ {
    #define SP(n, x) std :: setprecision(n) << std :: fixed << x
    #define DEBUG(x) std :: cerr << #x << " = " << x << '\n'
    #define fst first
    #define snd second
    template <typename T> T Max(T a, T b) { return a > b ? a : b; } template <typename T, typename... Args> T Max(T a, Args... args) { return a > Max(args...) ? a : Max(args...); }
    template <typename T> T Min(T a, T b) { return a < b ? a : b; } template <typename T, typename... Args> T Min(T a, Args... args) { return a < Min(args...) ? a : Min(args...); }
}
using namespace std;
using namespace xvl_;
const int N = 200005;
struct Edge { int to, w; };
ll n, ans;
ll dp[N][2];
vector <Edge> G[N];
void dfs(int cur, int p) {
    for (auto v : G[cur]) {
        if (v.to == p) continue;
        dfs(v.to, cur);
        if (v.w == 1) {
            dp[cur][1] += dp[v.to][1] + 1;
            dp[cur][0] += dp[v.to][1] + 1;
        }
        else dp[cur][0] += dp[v.to][0] + 1;
    }
}
void get(int cur, int p) {
    for (auto v : G[cur]) {
        if (v.to == p) continue;
        if (v.w == 1) {
            dp[v.to][0] += dp[cur][1] - dp[v.to][1];
            dp[v.to][1] = dp[cur][1];
        }
        else dp[v.to][0] = dp[cur][0];
        get(v.to, cur); 
    }
}
int main() {
    // freopen("InName.in", "r", stdin);
    // freopen("OutName.out", "w", stdout);
    ios :: sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> n;
    for (int i = 1; i < n; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        G[u].push_back({v, w});
        G[v].push_back({u, w});
    }
    dfs(1, 0);
    get(1, 0);
    for (int i = 1; i <= n; i++) ans += dp[i][0];
    cout << ans;
    return 0;
}
```

---

## 作者：toolong114514 (赞：1)

# CF1156D 0-1-Tree 题解
被搬到 GZFLS 今天的一场比赛当 T2，赛时想出正解但是写挂了。
## 解题思路
首先能够想到一种 $O(n^2)$ 的做法。

注意到路径可以分为 3 种：经过的边先 0 后 1、只有 0 和只有 1。

容易发现，第一种需要特别考虑。

第一种路径中，一定存在一个点，将其分为两半：前面的链都为 1，这里到后面的链。

将它们造成的数量贡献乘起来，再加上全为 0 和 全为 1 的贡献，就是答案。

给个暴力的代码：
```cpp
#include<iostream>
#include<cstring>
using namespace std;
const int N=1e6+10;
struct node{
	int to,nxt,val;
}edge[N];
int head[N];
int cnt;
void add(int u,int v,int w){
	edge[++cnt]={v,head[u],w};
	head[u]=cnt;
}
int dep[N];
int f[N][3];
void dfs(int x,int last){
	//cout<<x<<endl;
	for(int i=head[x];i!=-1;i=edge[i].nxt){
		if(edge[i].to!=last){
			dfs(edge[i].to,x);
			if(edge[i].val==0){
				f[x][0]+=f[edge[i].to][0]+1;
			}else{
				f[x][1]+=f[edge[i].to][1]+1; 
			}
		}
	}
}
int n,ans;
int main(){
	ios::sync_with_stdio(false);
	memset(head,-1,sizeof(head));
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z);
		add(y,x,z);
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			f[j][0]=f[j][1]=0;
		}
		dfs(i,0);
		for(int j=head[i];j!=-1;j=edge[j].nxt){
			//cout<<edge[j].to<<endl;
			if(edge[j].val==0) ans+=(f[edge[j].to][0]+1)*f[i][1];
			//else ans+=(f[edge[j].to][1]+1)*f[i][0];
		}
		ans+=f[i][0]+f[i][1];
	}
	cout<<ans;
	return 0;
}
```
这份代码在 CF 上可以过大概 13 个点，但是剩下的会 TLE。

上述做法可以优化为 $O(n)$。

钦定 $1$ 号点为数的根。

定义一个树形 DP 数组 $f_{i,j}$ $(j=0,1,3 \texttt{ or } 4)$。

$f_{i,0}$ 表示从点 $i$ 开始，向儿子走的链中，全为 $0$ 的数量。

$f_{i,1}$ 表示从点 $i$ 开始，向儿子走的链中，全为 $1$ 的数量。

$f_{i,3}$ 表示从下往上到达点 $i$ 的链中，边先全是 $0$，后全是 $1$ 的数量。

$f_{i,4}$ 表示从下往上到达点 $i$ 的链中，边先全是 $1$，后全是 $0$ 的数量。

~~不码 $\LaTeX$ 了~~，状态转移方程直接看代码。

```cpp
for(int i=head[x];i!=-1;i=edge[i].nxt){
	if(edge[i].to!=last){
		dfs(edge[i].to,x);
		if(edge[i].val==0){
			f[x][0]+=f[edge[i].to][0]+1;
			f[x][4]+=f[edge[i].to][4]+f[edge[i].to][1];
		}else{
			f[x][1]+=f[edge[i].to][1]+1;
			f[x][3]+=f[edge[i].to][3]+f[edge[i].to][0];
		}
	}
}
```
计数很好推，注意一下去重即可。
```cpp
for(int i=head[x];i!=-1;i=edge[i].nxt){		
	if(edge[i].to==last) continue;
	if(edge[i].val==1){
		ans+=(f[edge[i].to][1]+1)*f[x][0];
		ans+=(f[edge[i].to][3]+f[edge[i].to][0])*(f[x][1]-f[edge[i].to][1]-1);
		ans+=(f[edge[i].to][1]+1)*(f[x][1]-f[edge[i].to][1]-1);
	}else{
		ans+=(f[edge[i].to][4]+f[edge[i].to][1])*(f[x][0]-f[edge[i].to][0]-1);
		ans+=(f[edge[i].to][0]+1)*(f[x][0]-f[edge[i].to][0]-1);
	}
}
ans+=2*f[x][0]+2*f[x][1]+f[x][3]+f[x][4];

```
## 参考代码
```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define int long long
const int N=2e6+10;
struct node{
	int to,nxt,val;
}edge[N]; 
int head[N];
int cnt;
void add(int u,int v,int w){
	edge[++cnt]={v,head[u],w};
	head[u]=cnt;
}
int f[N][5];//f[i][0]:0 f[i][1]:1 f[i][3]:0+1 f[i][4]:1+0
int n,ans;
void dfs(int x,int last){
	for(int i=head[x];i!=-1;i=edge[i].nxt){
		if(edge[i].to!=last){
			dfs(edge[i].to,x);
			if(edge[i].val==0){
				f[x][0]+=f[edge[i].to][0]+1;
				f[x][4]+=f[edge[i].to][4]+f[edge[i].to][1];
			}else{
				f[x][1]+=f[edge[i].to][1]+1;
				f[x][3]+=f[edge[i].to][3]+f[edge[i].to][0];
			}
		}
	}
	for(int i=head[x];i!=-1;i=edge[i].nxt){
		if(edge[i].to==last) continue;
		if(edge[i].val==1){
			ans+=(f[edge[i].to][1]+1)*f[x][0];
			ans+=(f[edge[i].to][3]+f[edge[i].to][0])*(f[x][1]-f[edge[i].to][1]-1);
			ans+=(f[edge[i].to][1]+1)*(f[x][1]-f[edge[i].to][1]-1);
		}else{
			ans+=(f[edge[i].to][4]+f[edge[i].to][1])*(f[x][0]-f[edge[i].to][0]-1);
			ans+=(f[edge[i].to][0]+1)*(f[x][0]-f[edge[i].to][0]-1);
		}
	}
	ans+=2*f[x][0]+2*f[x][1]+f[x][3]+f[x][4];
} 
signed main(){
	ios::sync_with_stdio(false);
	memset(head,-1,sizeof(head));
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y,z;
		cin>>x>>y>>z;
		add(x,y,z);
		add(y,x,z);
	}
	dfs(1,0);
	cout<<ans;
	return 0;
}
```
[本代码可以通过 CF 的评测](https://www.luogu.com.cn/record/144995356)。

written by [toolong114514](www.luogu.com.cn/user/477821) in 2024.1.29.

~~好像是第一道紫题题解。~~

---

## 作者：D2T1 (赞：1)

# 题解 [Codeforces1156D] 0-1-Tree

题目来源：Codeforces Educational Round #64

tag：树形 DP，计数

------------

## Solution

很容易想到树形 DP，设 $f_{x,0/1/2/3}$ 表示 $x$ 的子树中有多少个点，到 $x$ 的路径为全 $\texttt0$、全 $\texttt1$、先 $\texttt0$ 再 $\texttt1$，先 $\texttt1$ 再 $\texttt0$。注意四个状态互相没有重合，且单点不算在路径里。

设当前考虑点 $x$ 的答案，每遍历到 $x$ 的一棵子树 $y$，就要先计算 $y$ 和已经遍历过的 $x$ 的子树的答案，再来更新 $f_x$。否则会存在类似于 $y\to x\to y$ 的路径，不符合题意。所以先统计答案，再考虑状态转移。

统计答案时，先根据 $w(x,y)$ 分类。当 $w(x,y)=1$ 时，路径可以分为三类，其中前两类不考虑全 $\texttt1$，第三类为全 $\texttt1$：

1. $y\to x$，$y$ 的子树中可以取 $f_{y,0}+f_{y,2}$ 个点，$x$ 已经遍历过的子树中可以取 $f_{x,1}+1$ 个点。（因为 $x$ 本身也可以取）
2. $x\to y$，$x$ 已经遍历过的子树中可以取 $f_{x,0}+f_{x,2}$ 个点，$y$ 的子树中可以取 $f_{y,1}+1$ 个点。（因为 $y$ 本身也可以取）
3. 全 $\texttt1$ 路径，$x$ 已经遍历过的子树中可以取 $f_{x,1}+1$ 个点，$y$ 的子树中可以取 $f_{y,1}+1$ 个点。因为方向有两种，所以答案要再乘上 $2$。

所以答案累加上 $(f_{y,0}+f_{y,2})(f_{x,1}+1)+(f_{x,0}+f_{x,2})(f_{y,1}+1)+2(f_{x,1}+1)(f_{y,1}+1)$。

状态转移式即为：

$$\begin{cases}f_{x,1}=\sum\limits_{y\in Son(x),w(x,y)=1}f_{y,1}+1\\f_{x,2}=\sum\limits_{y\in Son(x),w(x,y)=1}f_{y,0}+f_{y,2}\end{cases}$$

同理，当 $w(x.y)=0$ 时：

答案累加上 $(f_{y,1}+f_{y,3})(f_{x,0}+1)+(f_{x,1}+f_{x,3})(f_{y,0}+1)+2(f_{x,0}+1)(f_{y,0}+1)$。

状态转移：

$$\begin{cases}f_{x,0}=\sum\limits_{y\in Son(x),w(x,y)=0}f_{y,0}+1\\f_{x,3}=\sum\limits_{y\in Son(x),w(x,y)=0}f_{y,1}+f_{y,3}\end{cases}$$

```cpp
const int N = 2e5 + 10;
long long ans, f[N][4];
vector<pii> G[N];
int n;

void dfs(int x, int fa){
	for(int i = 0; i < G[x].size(); ++ i){
		int y = G[x][i].first, z = G[x][i].second;
		if(y == fa){
			continue;
		}
		dfs(y, x);
		if(z){
			ans += 2 * (f[y][1] + 1) * (f[x][1] + 1);
			ans += (f[y][0] + f[y][2]) * (f[x][1] + 1);
			ans += (f[x][0] + f[x][2]) * (f[y][1] + 1);
			f[x][1] += f[y][1] + 1;
			f[x][2] += f[y][2] + f[y][0];
		} else {
			ans += 2 * (f[y][0] + 1) * (f[x][0] + 1);
			ans += (f[y][1] + f[y][3]) * (f[x][0] + 1);
			ans += (f[x][1] + f[x][3]) * (f[y][0] + 1);
			f[x][0] += f[y][0] + 1;
			f[x][3] += f[y][3] + f[y][1];
		}
	}
}

void solve(){
	n = rdi;
	for(int i = 1; i < n; ++ i){
		int x = rdi;
		int y = rdi;
		int z = rdi;
		G[x].push_back(make_pair(y, z));
		G[y].push_back(make_pair(x, z));
	}
	dfs(1, 0);
	writen(ans);
}
```

![](https://啧.tk/hsh)。

---

## 作者：Trimsteanima (赞：1)

### Description
有一棵$n$个节点的树，每条边都有个权值$0$或者$1$，要求不能从$0$边到$1$边，求有多少点对符合要求。
### Solution
维护两个块，一个全部为$1$，另一个全部为$0$。
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 200010;
int n, a, b, c, a1, b1;
long long ans;
int f[N][5], A[N], B[N];
int find(int x, int y) {
    if (!f[x][y])
        return x;
    else  {
        f[x][y] = find(f[x][y], y);
        return f[x][y];
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d%d", &a, &b, &c);
        a1 = find(a, c), b1 = find(b, c);
        if (a1 != b1)
            f[a1][c] = b1;
    }
    for (int i = 1; i <= n; i++)
        A[find(i, 1)]++, B[find(i, 0)]++;
    for (int i = 1; i <= n; i ++)
        ans += 1ll * (A[find(i, 1)]) * (B[find(i, 0)]) - 1;
    printf("%lld\n", ans);
    return 0;
}
```

---

## 作者：2huk (赞：0)

这有蓝？最开始还是紫？建议降黄/绿。

显然一条路径合法等价于前面只走 $0$ 边后面只走 $1$ 边。不妨枚举转折点。

令其为 $x$。现在我们要求有多少 $u, v$ 使得 $u \sim x$ 路径上的边都是 $0$，$x \sim v$ 路径上的边都是 $1$。

显然可以分别求然后乘法原理。以求 $u$ 的数量为例。

注意到，合法的 $x$ 在树上一定是一个连通块，且这个连通块内的边都是 $0$。于是可以开一个并查集，维护这样的全 $0$ 边连通块。那么统计 $x$ 的数量就很简单了。

注意题目中路径 $(u, v)$ 需要保证 $u \ne v$。所以答案还要减 $n$。

代码：<https://codeforces.com/contest/1156/submission/289097972>

---

## 作者：wusixuan (赞：0)

一种换根 dp 的做法，但是是一种和题解区不同的做法。

由于这种树上路径的问题若假定一个点为根会更加的好求，所以我们可以枚举 $x$，然后假定 $x$ 为根节点，再去找有多少个满足条件的 $y$。

显然有对于每个 $x$ 复杂度为 $O(n)$ 的搜索，记录 $u,val$ 分别表示目前的点的编号 $u$，以及 $x$ 到 $u$ 走过的最大权值 $val$，记录 $val$ 的原因是需要根据目前的路径最大权值选择可以走过的边，例如 $val$ 为 $1$ 的时候就不可以经过权值为 $0$ 的边了。答案显然就是每一个 $x$ 可以到达的 $u$ 的数量。复杂度为 $O(n^2)$，需要优化。

发现 $(u,val)$ 的总个数就只有 $2 \times n$ 个，如果使用记忆化搜索的话可以把时间复杂度优化到 $O(n)$。记录 $dp_{u,val}$ 表示从根节点 $x$ 走到 $u$ 时，路径最大权值为 $val$ 时，$u$ 可以到达的点的个数。

但是这样显然不可行，在不同的 $x$ 下面这个值可以是不同的。

于是我们可以先跑出来根节点为 $1$ 的所有 dp 的值，然后再跑换根 dp，这个时候已经和前面提到的搜索没多大关系了。

前面的树形 dp 的转移方程很好想，就是对于每一个 $u$ 枚举可以到的点 $v$ 并得到两点之间的边的权值 $w$，如果 $w=0$，就是 $dp_{u,0}+dp_{v,0}+1 \to dp_{u,0}$，否则就是 $dp_{u,0}+dp_{v,1}+1 \to dp_{u,0}$ 并且 $dp_{u,1}+dp_{v,1}+1 \to dp_{u,1}$。

然后的换根 dp 就是这样的反着来，最后答案显然就是对于每一个根节点 $x$ 下面的 $dp_{x,0}$ 即可。具体可以看代码。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n;
const int N=200010;
vector<pair<int,int> > v[N];
int dp[N][2];//dp数组
int ans=0;
void dfs(int u,int pre){
	for(auto [i,w]:v[u]){
		if(i==pre) continue;
		dfs(i,u);
		if(w==0) dp[u][0]+=dp[i][0]+1;
		else dp[u][0]+=dp[i][1]+1,dp[u][1]+=dp[i][1]+1;//转移方程
	}
}
void change(int u,int i,int w){
	if(w==0) dp[u][0]-=dp[i][0]+1;
	else dp[u][0]-=dp[i][1]+1,dp[u][1]-=dp[i][1]+1;//反着来，先断边再加边
	if(w==0) dp[i][0]+=dp[u][0]+1;
	else dp[i][0]+=dp[u][1]+1,dp[i][1]+=dp[u][1]+1;
}
void dfs2(int u,int pre){
	ans+=dp[u][0];
	for(auto [i,w]:v[u]){
		if(i==pre) continue;
		change(u,i,w);//换根
		dfs2(i,u);
		change(i,u,w);
	}
}
signed main(){
	cin>>n;
	for(int i=1;i<n;i++){
		int x,y,w;
		cin>>x>>y>>w;
		v[x].push_back({y,w});
		v[y].push_back({x,w});
	}
	dfs(1,0);//树形dp
	dfs2(1,0);//换根dp
	cout<<ans;
	return 0;
}
```

如果对本题题解有疑问，欢迎在讨论区提出，我会尽量给出解答。

---

## 作者：Rachel_liu (赞：0)

## 前置（都是废话不用看）
~~审核严严的很安心导致~~不~~敢~~想起过于莫名其妙的标题，也不~~敢~~想打莫名其妙的半个括号。

言归正传，本题是比换根 DP 模板题还简单的换根 DP，但其实只用了换根 DP 的思路，其递推式过于简单根本算不上 DP。

所以本题是适合换根 DP 零基础宝宝体质入门换根 DP 的法宝。

~~最后还是觉得该降绿，毕竟苯蒟蒻都能做出来。~~
## 思路
首先，合法的路径只有三种，边权: 
1. 全为 $0$
1. 全为 $1$
1. 前面若干个 $0$，后面紧跟若干个 $1$。

其次，我们发现，这三种可以归类为一种，它们其实都属于第 $3$ 种。
- 第 $1$ 种就是 “前面若干个 $0$，后面紧跟 $0$ 个 $1$”。
- 第 $2$ 种就是 “前面 $0$ 个 $0$，后面紧跟若干个 $1$”。

因此，我们想到，可以枚举每一个边权从 $0$ 到 $1$ 的转折节点（也就是所有的节点），求出从任意一个点 $i$ 出发，只通过边权为 $0$ 的边有几条可能的路径 $cnt0_i$ ，只通过边权为 $1$ 的边有几条可能的路径 $cnt1_i$ 。每一个点的答案即为 $cnt0_i + cnt1_i + cnt0_i \times cnt1_i$，而最终的答案即为每一个点的答案之和。
## 实现
首先之前的首先，建议大家可以直接读代码，因为代码非常简洁易懂，而接下来的题解部分反倒是我的表达有点力不从心（秃）。

现在的问题就在于如何 “求出从任意一个点 $i$ 出发，只通过边权为 $0 / 1$ 的边有几条可能的路径”。

看到关键词 “树上”、“任意一点”，容易想到换根 DP ，所以我们使用换根 DP 的思路。

首先，以节点 $1$ 为根节点（其实哪个点作根节点都无所谓，但是只有节点 $1$ 每棵树都一定有），DFS 一遍得到每个点 $i$ **只往自己的子树延伸的** $cnt0_i$ 和 $cnt1_i$（意思是不考虑通过父节点的那些合法路径）。

注意到，如果一个点和它的父节点之间的路径边权为 $0$，则**第一遍 DFS 算出来的 $cnt0_i$ 比真实值小，而 $cnt1_i$ 就是真实值**，因为没有从该节点开始的、通过其父节点的、边权均为 $1$ 的合法路径。

那 $cnt0_i$ 的真实值是什么呢？我们发现，在边权均为 $0$ 的生成树中，每一个点的真实的 $cnt0_i$ 都相等。那么对于任何不真实的 $cnt0_i$，我们只需知道点 $i$ 所在生成树的根节点的 $cnt0_r$ 值（因为它一定是真实的）并把它赋给 $cnt0_i$ 即可。

反之亦然，与父节点的路径边权为 $1$ 的情况不多赘述。 

接下来，以节点 $1$ 为根节点再 DFS 一遍，计算每个点的 $cnt0_i$ 和  $cnt1_i$ 的真实值。事实上，除了根节点 $1$ 之外，每个点的 $cnt0_i$ 和  $cnt1_i$ 中一定有且仅有一个是真实的（因为其与父节点之间的路径边权要么是 $1$ 要么是 $0$），不真实的值沿用其父节点的即可，因为其父节点的两个值都是刚刚算好的真实值。而根节点 $1$ 的两个值都是真实的。

正如前文提到，其实干讲听起来有点复杂，但是代码其实非常极其简单，所以建议大家读读代码 ↓。
## 代码
```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
struct ES{ll v, w;};
const ll MAXN = 200005;
ll n, cnt1[MAXN], cnt0[MAXN];
vector<ES> es[MAXN];

void dfs1(ll u, ll fa){
	for (auto e: es[u]){
		ll v = e.v, w = e.w;
		if (v == fa) continue;
		dfs1(v, u);
		if (w == 1)
			cnt1[u] += cnt1[v] + 1;
		else
		    cnt0[u] += cnt0[v] + 1;
	}
}

void dfs2(ll u, ll fa){
	for (auto e: es[u]){
		ll v = e.v, w = e.w;
		if (v == fa) continue;
		if (w == 1)
		    cnt1[v] = cnt1[u];
		else
		    cnt0[v] = cnt0[u];
		dfs2(v, u);
	}
}

int main(){
	ll x, y, z;
	scanf("%lld", &n);
	for (ll i = 1; i < n; i++){
		scanf("%lld%lld%lld", &x, &y, &z);
		es[x].push_back((ES){y, z});
		es[y].push_back((ES){x, z});
	}
	dfs1(1, 0);
	dfs2(1, 0);
	ll ans = 0;
	for (ll i = 1; i <= n; i++){
		//cout << cnt1[i] <<" "<< cnt0[i] <<" "<< cnt1[i] * cnt0[i] << endl;
		ans += cnt1[i] + cnt0[i] + cnt1[i] * cnt0[i];
	}
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：dbxxx (赞：0)

[您可以在我的博客中查看本文，谢谢！](https://www.cnblogs.com/crab-in-the-northeast/p/cf1156d.html)

考虑对每个点 $u$ 统计：在点 $u$ 中转的路径有多少条？

其中一条路径在点 $u$ 中转的意思为：这条路径在到达点 $u$ 前访问的均为 $0$ 边，到达点 $u$ 后访问的边均为 $1$ 边。特别地，如果一条路径起点为 $u$ 在 $u$ 中转，它经过的边权全为 $1$ ；如果一条路径终点为 $u$ 在 $u$ 中转，它经过的边权全为 $0$。

我们一开始先对树 $T$ 预处理：断开所有边权为 $1$ 的边后形成的连通块称作一类连通块；断开所有边权为 $0$ 的边后形成的连通块称作二类连通块。

容易证明 $u$ 所在一类连通块和 $u$ 所在二类连通块存在且仅存在一个交点，这个交点就是 $u$。

那么，一条路径 $(s, t)$ 在点 $u$ 中转，充要条件是：

- $s$ 在 $u$ 所在的一类连通块中；
- $t$ 在 $u$ 所在的二类连通块中；
- $s, t$ 不同时等于 $u$。

如此，$s \rightsquigarrow u \rightsquigarrow t$ 才是一个合法的在 $u$ 中转的路径。

因此，若 $u$ 所在一类连通块大小为 $p$，所在二类连通块大小为 $q$，那么在 $u$ 中转的路径有 $p \times q - 1$ 条。$-1$ 是扣除 $s = u = t$ 的情况。

时间复杂度 $\mathcal{O}(n)$。

```cpp
/*
 * @Author: crab-in-the-northeast 
 * @Date: 2022-10-18 16:36:45 
 * @Last Modified by: crab-in-the-northeast
 * @Last Modified time: 2022-10-18 17:02:35
 */
#include <bits/stdc++.h>
#define int long long
inline int read() {
    int x = 0;
    bool flag = true;
    char ch = getchar();
    while (!isdigit(ch)) {
        if (ch == '-')
            flag = false;
        ch = getchar();
    }
    while (isdigit(ch)) {
        x = (x << 1) + (x << 3) + ch - '0';
        ch = getchar();
    }
    if(flag)
        return x;
    return ~(x - 1);
}

const int maxn = (int)2e5 + 5;
typedef std :: pair <int, int> pii;
std :: vector <pii> G[maxn];

int con[2][maxn];
int siz[2][maxn];

void dfs(int u, int x, int id) {
    con[x][u] = id;
    ++siz[x][id];
    for (pii e : G[u]) {
        int v = e.first, w = e.second;
        if (w != x || con[x][v])
            continue;
        dfs(v, x, id);
    }
}


signed main() {
    int n = read();
    for (int i = 1; i < n; ++i) {
        int u = read(), v = read(), w = read();
        G[u].emplace_back(v, w);
        G[v].emplace_back(u, w);
    }

    for (int u = 1; u <= n; ++u) {
        if (!con[0][u])
            dfs(u, 0, u);
        if (!con[1][u])
            dfs(u, 1, u);
    }

    int ans = 0;
    for (int u = 1; u <= n; ++u)
        ans += siz[0][con[0][u]] * siz[1][con[1][u]] - 1;
    
    printf("%lld\n", ans);
    return 0;
}
```

如果觉得这篇题解写得好，请不要忘记点赞，谢谢！

---

