# Maze

## 题目描述

A maze is represented by a tree (an undirected graph, where exactly one way exists between each pair of vertices). In the maze the entrance vertex and the exit vertex are chosen with some probability. The exit from the maze is sought by Deep First Search. If there are several possible ways to move, the move is chosen equiprobably. Consider the following pseudo-code:

```plain
DFS(x)
    if x == exit vertex then
        finish search
    flag[x] <- TRUE
    random shuffle the vertices' order in V(x) // here all permutations have equal probability to be chosen
    for i <- 1 to length[V] do
        if flag[V[i]] = FALSE then
            count++;
            DFS(y);
    count++;
```

$ V(x) $ is the list vertices adjacent to $ x $ . The $ flag $ array is initially filled as FALSE. $ DFS $ initially starts with a parameter of an entrance vertex. When the search is finished, variable $ count $ will contain the number of moves.

Your task is to count the mathematical expectation of the number of moves one has to do to exit the maze.

## 说明/提示

In the first sample the entrance vertex is always 1 and the exit vertex is always 2.

In the second sample the entrance vertex is always 1 and the exit vertex with the probability of 2/5 will be 2 of with the probability if 3/5 will be 3. The mathematical expectations for the exit vertices 2 and 3 will be equal (symmetrical cases). During the first move one can go to the exit vertex with the probability of 0.5 or to go to a vertex that's not the exit vertex with the probability of 0.5. In the first case the number of moves equals 1, in the second one it equals 3. The total mathematical expectation is counted as $ 2/5×(1×0.5+3×0.5)+3/5×(1×0.5+3×0.5) $

## 样例 #1

### 输入

```
2
1 2
0 1
1 0
```

### 输出

```
1.00000000000000000000
```

## 样例 #2

### 输入

```
3
1 2
1 3
1 0
0 2
0 3
```

### 输出

```
2.00000000000000000000
```

## 样例 #3

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
3 7
1 1
1 1
1 1
1 1
1 1
1 1
1 1
```

### 输出

```
4.04081632653```

# 题解

## 作者：Xu_brezza (赞：11)

### 前言
自己做出来滴紫色期望！！！好开心！！！

## 简化题意
一颗无根树，每个点有作为起点的权值 $x[i]$ 和作为终点的权值 $y[i]$，这个点作为起点的概率是 $\frac {x[i]}{\sum x} $(话说为什么不能用 ``\cfrac`` 啊)，作为终点的概率同理为 $\frac {y[i]}{\sum y}$，从起点出发深搜，到终点停止（但也可以走到不了终点的路直至走不了了），求到达点数的期望个数。

~~好像并没有特别简化~~。

## Solution

首先我们进行一步转化：
	
   - 根据期望的线性性质，答案就是每个点作为终点，能到达的点数期望之和。
 
接下来考虑点 $u$ 的答案如何统计？

我们可以来发现一些性质：

- 点 $u$ 作为终点，他的所有子树互相不能到达。
   
 - 对于点 $u$ 的每一个子树，从内部的任意一个节点出发，都可以到达该子树内所有的点。
   
这些性质都比较显然，但是合并起来却很有用！

由此我们可以发现：

$$ans[u] = \sum_{v \in son(u)} {\sum_{k \in tree(v)} x[k] \times y[u] \times siz[v]}$$

说白了就是所有起点和他配对的概率乘上到达的点数。

然后发现这个东西是非常好维护的，$siz[v]$ 和 $y[u]$ 都是可以提出来的，那么 $\sum x[k]$ 这个东西就维护一下全局的和以及子树的和，分别搞一搞就做完了qaq。

~~讲完了忽然觉得这题好水，我果然还是个sb~~。

``` cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=(a);i<=(b);++i)
#define Rep(i,a,b) for(int i=(a);i<(b);++i)
#define rrep(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
template <typename T>
inline void read(T &x){
    x=0;char ch=getchar();bool f=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
    if(f)x=-x;
}
template <typename T,typename ...Args>
inline void read(T &tmp,Args &...tmps){read(tmp);read(tmps...);}
const int N = 1e5 + 5;
int n;
vector<int>g[N];
double x[N],y[N];
double ans;
double sx = 0,sy = 0;
int siz[N];
void dfs(int u,int fa){
    siz[u] = 1;
    for(int v : g[u]){
        if(v == fa)continue;
        dfs(v,u);
        siz[u] += siz[v];
        x[u] += x[v];
        ans += x[v] * siz[v] * y[u];
    }
    ans += (sx - x[u]) * (n - siz[u]) * y[u];
}
signed main(){
    read(n);
    rep(i,2,n){
        int u,v;
        read(u,v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    rep(i,1,n){
        scanf("%lf%lf",x + i,y + i);
        sx += x[i];
        sy += y[i];
    }
    rep(i,1,n)x[i] /= sx;
    rep(i,1,n)y[i] /= sy;
    sx = sy = 0;
    rep(i,1,n)sx += x[i];
    rep(i,1,n)sy += y[i];
    dfs(1,0);
    printf("%.10lf",ans);
}
```
都看到这里了，留个赞呗QAQ。

---

## 作者：hwk0518 (赞：9)

发现路径长比较难统计，所以想到统计每条边的期望经过次数。

最后要走到目标点$T$，只有起点到目标点上的路径是正确的。所以这条路径上的边期望经过一次。

考虑其它错误的边的期望经过次数。设这条边连接的子节点是$x$。

(1)$x$在$T$的子树内且不为$T$。显然不会经过。

(2)$x$不在$T$的子树内或$x$为$T$。设$l=LCA(x,T)$，则经过这条边当且仅当从$l$向下遍历时，$x$所在的子树在$T$所在的子树前被走到。不难算出，这个事件发生的概率是$\frac{1}{2}$。而且一旦经过这条边，最后一定会退回去。所以这条边一旦经过，就会经过两次。这样这条边的期望经过次数是：

$E=\frac{1}{2}*2+\frac{1}{2}*0=1$.

所以任何不在$T$子树内的边期望经过次数都是$1$。

所以题目化为：

给定每个点作为起点$S$和终点$T$的概率，问以$S$为根的子树中，去掉以$T$为根的子树后树大小的期望。

使用换根$DP$。以任意点为根遍历整棵树，若$S$在$T$的子树内，且$S$不为$T$，则答案为$n-siz[a]$，其中$a$是$T$的儿子且是$S$的祖先；若$S$在$T$的子树外，则答案为$siz[T]$；若$S=T$，则答案为0.

枚举$T$，讨论$S$在以$T$的哪个儿子为根的子树内或在以$T$为根的子树外即可。

代码：

```

#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<string>
#include<algorithm>
#include<math.h>
using namespace std;

const int N=1e5+5;
const int M=3e5+5;
int n,u,v;
int E,ot[M],ne[M],g[N];
int siz[N];
double sum[N],ans;
pair<double,double> P[N];

void add(int u,int v)
{
    ot[++E]=v;
    ne[E]=g[u];
    g[u]=E;
}

void init()
{
    int i;
    scanf("%d",&n);
    for(i=1;i<n;++i)
    {
        scanf("%d%d",&u,&v);
        add(u,v),add(v,u);
    }
    
    pair<double,double> tot=make_pair(0,0);
    for(i=1;i<=n;++i)
    {
        scanf("%lf%lf",&P[i].first,&P[i].second);
        tot.first+=P[i].first,tot.second+=P[i].second;
    }
    for(i=1;i<=n;++i)
        P[i].first/=tot.first,P[i].second/=tot.second;
}

void dfs(int x,int fath)
{
    int p,to;
    siz[x]=1,sum[x]=P[x].first;
    double ins=0;
    for(p=g[x];p;p=ne[p])
    {
        to=ot[p];
        if(to==fath) continue;
        dfs(to,x);
        siz[x]+=siz[to];
        sum[x]+=sum[to];
        ins+=sum[to]*siz[to];
    }
    ins+=(1-sum[x])*(n-siz[x]);
    ans+=ins*P[x].second;
}

int main()
{
    init();dfs(1,0);printf("%.12lf\n",ans);
    return 0;
}

```

---

## 作者：L_G_J (赞：8)

提供一种不太一样的换根 dp 的做法。

记 $u$ 作为起点的概率为 $q_u$ ，作为终点的概率为 $p_u$。

题目给的代码可以看作一个从某个点开始，以它为根 dfs 到终点的步数，这启发我们直接考虑以每个点为根，到达所有可能终点的期望步数之和。

首先可以观察出几个性质：

假设当前的根为 $x$，终点是 $y$，那么从 $x$ 开始走，考虑其中的一步。

* 如果这一步进入了与 $y$ 所在子树不同的一个子树，一定会把这个子树内的所有点遍历完才出来。假设进入了一个以 $z$ 为根的子树，大小为 $sz_z$，那么这个子树内的边数就是 $sz_z-1$，所需步数即为 $2(sz_z-1)+2=2sz_z$。
* 如果走进了了 $y$ 所在的子树，那么就不会再出来。


对于一个点，记 $y$ 所在的子树的根为 $u$。

由上面的性质可以知道，对于一个点，如果一个它的一个儿子 $v \not=u$ 在 $u$ 之前被访问，那么答案就会加上 $2sz_v$。而 $v$ 在 $u$ 之前被访问的概率相当于给这个点的儿子随机一个排列，其中 $v$ 在 $u$ 之前的概率。考虑对于每种 $v$ 在 $u$ 之前的排列，`swap(u,v)` 之后就会得到一个 $u$ 在 $v$ 之前的排列，所以概率是 $\dfrac 12$。

接下来设 $S$ 为 $(x,fa_y)$ 这条路径上的点分叉出去的点集的并，那么 $x$ 走到 $y$ 的期望就是 $\sum\limits_{u \in S} \dfrac{2sz_u}{2}$，对答案的贡献就是 $q_xp_y\sum\limits_{u \in S}sz_u$。

接下来就考虑对于每个根 $x$ 求出 $p_y\sum\limits_{u \in S}sz_u$，先考虑以 $1$ 为根。

设 $f_u$ 表示以 $u$ 为起点，到达 $u$ 子树的的所有可能终点的期望步数之和，设 $s=\sum\limits_{v \in son_u} sz_v=sz_u-1$，$t_u=\sum\limits_{v\in Subtree_u} p_u$。

那么转移就是 $f_u=\sum\limits_{v \in son_u} (s-sz_v+1)t_v+f_v$。

换根也非常容易，首先对于每个点的 $\sum t_v$ 可以提前维护出来，这样子 $s$ 的变化导致的答案增量也很容易算出，具体的转移可以见代码。

复杂度 $O(n)$。

**代码：**

```cpp
const int N=2e5+50;
int n,x[N],y[N],head[N],cnt;
ld sum[N],sumt[N],sz[N],t[N],p[N],q[N],f[N],g[N],ans;
struct edge{int to,nxt;}e[N<<1];
inline void addedge(int u,int v){e[++cnt]=(edge){v,head[u]},head[u]=cnt;}
void dfs1(int u,int fa)
{
	sz[u]=1,t[u]=p[u];
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		dfs1(v,u),sz[u]+=sz[v],t[u]+=t[v];
		sum[u]+=sz[v],sumt[u]+=t[v];
	}
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		f[u]+=f[v]+(sum[u]-sz[v]+1)*t[v];
	}
}
void dfs2(int u,int fa)
{
	ans+=g[u]*q[u];
	for(int i=head[u];i;i=e[i].nxt)
	{
		int v=e[i].to;
		if(v==fa) continue;
		ld fu=g[u]-sz[v]*(1-p[u])-(n-1-2*sz[v]+1)*t[v]-f[v];
		g[v]=f[v]+(n-sz[v])*sumt[v]+(n-1-(n-sz[v])+1)*(1-t[v])+fu,dfs2(v,u);
	}
}
int main(void)
{
	n=read();int u,v,sumx=0,sumy=0;
	fr(i,2,n) u=read(),v=read(),addedge(u,v),addedge(v,u);
	fr(i,1,n) x[i]=read(),y[i]=read(),sumx+=x[i],sumy+=y[i];
	fr(i,1,n) q[i]=(ld)x[i]/(ld)sumx,p[i]=(ld)y[i]/(ld)sumy;
	dfs1(1,0),g[1]=f[1],dfs2(1,0);
	printf("%.10Lf\n",ans);
	return 0;
}
```


---

## 作者：yangshurong (赞：6)


题目大意：

给定一个迷宫，这个迷宫图是一个树，每个点都有可能作为进入点和离开点。要求求出：从每个点出发到达别的点的期望。

输入格式：
第一行一个数 n，表示个节点。
接下来 n-1 行，每行两个数(u,v),表示有一条从 u，到v的无向边。
然后是n行，每行描述一个节点表示该节点被选为进入点的 x 和该节点被选为离开的 y 。

此处的x和y用于求每个点被选为进入点的概率和被选为离开点的概率，即：
p[x]=x/sum(x),
p[y]=y/sum(y).

输出格式：一个实数表示期望。

解法：
这是一道求期望的题。

期望表示某个事件的结果的平均大小。
等于每种结果的大小与其概率乘积的和。

因此，对于这道题，我们要求出**每个子树的大小**，
和对于每个点：**其被选为离开点时，从别的子树出发到达它的概率**。

这样我们就可以先统计进入的概率，然后用dfs求出每棵子树的大小，和这个子树中，每个点被选为进入点的概率之和。然后枚举每个点作为离开点，然后求出：
1.从以该节点为根节点的子树出发到该节点的期望。
2.从别的子树出发到该节点的期望。

设该节点编号为 u，
因为对于每个“别的子树”，我们可以**将它们作为一个整体，看成u节点的另一个子树**。所以我们可以直接用 (1-ru[u])表示将它们选为出发点的概率。用（n-size[u]）表示它们的大小。

最后统计答案即可。

贴代码：
```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<stack>
#include<algorithm>
#include<cstring>
#include<vector>
#include<ctime>
#include<map>
#include<cstdlib>
#include<cmath>
#define p puts("-1");
#define r(i,a,b) for(int i=a;i<=b;i++)
#define rr(i,a,b) for(int i=a;i>=b;i--)
#define inf 0x3f3f3f3f
#define mem(a) memset(a,0x3f,sizeof(a))
#define re(a) a=read()
#define pr(a) printf("%d\n",a)
#define me(a) memset(a,0,sizeof(a))
#define in inline
#define db double
#define red(a) a=readd()
using namespace std;
const int N=100007;
inline int read(){
	char ch=getchar();
	int w=1,x=0;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+ch-'0',ch=getchar();}
	return x*w;
}//两种不同类型的数的快读
inline db readd(){
	char ch=getchar();
	db w=1,x=0;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0',ch=getchar();}
	return x*w;
}
int n,cnt=0,head[N],size[N],fa[N];
double ru[N],chu[N],ans=0,sumru,sumchu;
struct edge{
	int v,next;
}e[(N<<1)];
in void add(int u,int v){
	e[++cnt]=(edge){v,head[u]};//数组模拟建边 
	head[u]=cnt;
}
in void dfs(int u){
	size[u]=1;//size[]的初始化 
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(v!=fa[u]){//不用vis[],也可以做到每个点只便利一遍 
			fa[v]=u;
			dfs(v);
			size[u]+=size[v];//统计每棵子树的大小 
			ru[u]+=ru[v];//统计每棵子树被选为进入点的概率之和 
		}
	}
}
int main(){
	re(n);
	me(head),me(size);//初始化 
	r(i,1,n-1){
		int u,v;
		re(u);re(v);
		add(u,v);add(v,u);//建边。注意这是无向图 
	}
	r(i,1,n){
		red(ru[i]);red(chu[i]);
		sumru+=ru[i];sumchu+=chu[i];
	}
	r(i,1,n)ru[i]/=sumru;//求出每个点被选为进入点的概率:ru[i]=ru[i]/sumru 
	dfs(1);
	r(u,1,n){//遍历每个点，作为离开点 
		for(int j=head[u];j;j=e[j].next){
			int v=e[j].v;
			//统计期望
			if(fa[u]==v)ans+=(1-ru[u])*(n-size[u])*chu[u]/sumchu; 
			//当前的 v 不是u的子节点，此时统计上述的"别的子树"的期望 。
			//此时概率等于总概率减去这棵树的概率。 
			else ans+=ru[v]*size[v]*chu[u]/sumchu;
			//统计以u作为根节点的子树的期望 
		}
	}
	printf("%.11lf\n",ans);
	return 0;
}
```
本蒟蒻第一次写题解，如有做的不好的地方，还请各位见谅。
最后祝大家NOIP2018 RP+=inf!!!

---

## 作者：Phartial (赞：5)

简述题意：给你一棵树，每个点有一个被选为起点的概率和一个被选为终点的概率，从起点开始随机遍历子树，问到达终点的期望步数。

直接计算答案很难，考虑对一对 $(S,T)$ 来说，以 $S$ 为根，那么有：

- 对 $T$ 的子树里的点：显然不会被遍历到，贡献为 $0$。
- 对 $S\to T$ 路径上的点：显然会被刚好遍历 $1$ 次，贡献为 $1$。
- 对不在上述两种情况中的点：设其为 $x$，当我们遍历到 $x$ 和 $T$ 的分界点时，我们有 $\dfrac{1}{2}$ 的概率往 $x$ 的方向走，此时贡献为 $2$（往返）；同时也有 $\dfrac{1}{2}$ 的概率往 $T$ 的方向走，此时贡献为 $0$。故总贡献为 $\dfrac{1}{2}\times 2+\dfrac{1}{2}\times 0=1$。

那么问题就变成了求对每一对 $(S,T)$，以 $S$ 为根，$n-s'_T$ 的期望（$s'_T$ 表示 $T$ 在以 $S$ 为根的情况下的子树大小）。

首先任选一个根，考虑枚举 $T$，那么有以下几种情况：

- $S=T$：那么 $s'_T$ 显然为 $n$。
- $S$ 在 $T$ 的子树里：那么 $s'_T$ 即为所有点去掉 $S$ 所在的那棵子树，设 $S$ 所在的那棵子树的根为 $p$，那么 $s'_T=n-s_p$。
- $S$ 不在 $T$ 的子树里：那么 $s'_T$ 即为 $s_T$。

我们可以 $O(n)$ 遍历整棵树来计算 $s_T$ 以及 $S$ 在 $T$ 的子树中的概率，直接计算即可。

```cpp
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const int kN = 1e5 + 1;

int n, vs[kN], vt[kN], s[kN], svs, svt;
double ps[kN], pt[kN], p[kN], ans;
vector<int> e[kN];

void D(int x, int f) {
  s[x] = 1, p[x] = ps[x];
  double v = 0;
  for (int i : e[x]) {
    if (i != f) {
      D(i, x);
      s[x] += s[i], p[x] += p[i];
      v += p[i] * s[i];  // S 在 T 的子树里：(S 在 T 的子树 i 的概率) * (n - (n - s_i))
    }
  }
  v += (1 - p[x]) * (n - s[x]);  // S 不在 T 的子树里：（S 不在 T 的子树里的概率）*（n - s_T)
  ans += v * pt[x];
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 1, x, y; i < n; ++i) {
    cin >> x >> y;
    e[x].push_back(y), e[y].push_back(x);
  }
  for (int i = 1; i <= n; ++i) {
    cin >> vs[i] >> vt[i];
    svs += vs[i], svt += vt[i];
  }
  for (int i = 1; i <= n; ++i) {
    ps[i] = 1.0 * vs[i] / svs;
    pt[i] = 1.0 * vt[i] / svt;
  }
  D(1, 0);
  cout << fixed << setprecision(12) << ans;
  return 0;
}
```


---

## 作者：keysky (赞：2)

[传送门](https://codeforces.com/problemset/problem/123/E)
## 题意澄清
对于 dfs 遍历时，在某一个点进入子树的顺序并不是按输入顺序，而是假定随机选择未进入过的子树（这纠结了我好久）。
## 破题思路
首先可以明确这题不能推一个 $O(1)$ 的式子来计算期望（树的结构是随机的，对于所有点不存在均摊期望的可能），但是对于某一刻子树以根节点为起点时，一定是存在一个快速计算期望的式子（不可能枚举起点还要枚举终点吧）。

其次，考虑到需要对于每一个点作起点求出期望步数，又是一棵树，故树形dp 肯定是必要的，同时还需要换根。

那么算法分析完了（树形dp $+$ 推以子树根作起点的步数期望式子），就要具体实现算法了。
## 以子树根作起点的期望步数
对于每一棵子树，假设其根为 $rt$ ，终点在其儿子 $v$ 的子树中，如果下一步并未走向 $v$ ，而是走向 $u$ ，则需要花 $2\times siz[u]$ （ $siz[u]$ 为 $u$ 子树内节点个数1） 步走回 $rt$ ，那么对于在 $v$ 之前走向 $u$ 的概率相当于对于 $rt$ 所有儿子的排列中 $v$ 在 $u$ 之后的概率，明显是 $\frac{1}{2}$ ，故 $u$ 子树对于步数的贡献即为 $2\times siz[u]\times\frac{1}{2}=siz[u]$ ，所以对于以 $rt$ 为根且以 $rt$ 为起点的子树，其期望步数为
$$
g_{rt} \gets \sum\limits_{u\in son_{rt}} ((siz_{rt}-siz_u)\times sum\_p_u+g_u)
$$
其中 $g_u$ 为在 $u$ 的子树中以 $u$ 为根且以 $u$ 为起点的期望步数，$sum\_p_u$ 为以 $u$ 的子树中的结点为终点的概率。
## 树形dp
对于第一次树形dp 的式子我们已经在上一个部分推出来了，难点在于换根时的式子。我经常使用的方法是不去思考意义，只思考原式的 “逆式” 。

先明确一下定义。
$$
\begin{aligned}
 & \text{依据}\ u\ \text{去更新儿子}\ v\\
 & g,siz,sum\_p \text{意义同上}\\
 & f_u:\text{以}\ u\ \text{为起点的期望步数}\\
 & p2_u:\text{以}\ u\ \text{为终点的概率}\\
 & except\_v:\text{对于}\ v\ \text{的父亲}\ u\ \text{没有子树}\ v\ \text{时}\ g_u\ \text{的值}
\end{aligned}
$$

首先我们先处理式子中的 $g_u$ ，即 $except\_v$ ，既然是消去影响，故是用 $f_u$ 去减去影响。
 - 终点不在 $v$ 的子树中\
  概率为 $1-sum\_p_v-p2_u$\
  贡献为 $siz_v$\
  影响为 $(1-sum\_p_v-p2_u)\times(siz_v)$
 - 终点在 $v$ 的子树中\
  概率为 $sum\_p_v$\
  贡献为 $n-siz_v$\
  影响为 $sum\_p_v\times(n-siz_v)$

故
$$
except\_v \gets f_u - siz_v \times (1 - p2_u - sum\_p_v) - (n - siz_v) \times sum\_p_v
$$

接下来我们处理以 $v$ 为起点的期望步数。
 - 终点在原本 $v$ 的子树中\
  概率为 $sum\_p_v-p2_v$\
  贡献为 $n-siz_v$\
  期望步数为 $(sum\_p_v-p2_v)\times(b-siz_v)$
 - 终点不在原本 $v$ 的子树中\
  模仿原dp 式子可得 $(n-(n-siz_v))\times(1-sum\_p_v)+except\_v$

故 
$$
f_v \gets (n - siz_v) \times (sum\_p_v - p2_v) + (n - (n - siz_v)) \times (1 - sum\_p_v) + except\_v
$$
## 实现
综合上述内容，便有了以下代码。
```cpp
/*
address:https://codeforces.com/problemset/problem/123/E
AC 2024/8/28 12:26
*/
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector<int>G[N];
int n;
double p1[N], p2[N];
int sum1, sum2;
double f[N], g[N], sum_p[N];
int siz[N];
inline void dfs1(int u, int fa) {
    sum_p[u] = p2[u];
    siz[u] = 1;
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs1(v, u);
        sum_p[u] += sum_p[v];
        siz[u] += siz[v];
    }
    for (auto v : G[u]) {
        if (v == fa) continue;
        g[u] += (siz[u] - siz[v]) * sum_p[v] + g[v];
    }
}
inline void dfs2(int u, int fa) {
    for (auto v : G[u]) {
        if (v == fa) continue;
        double except_v = f[u] - siz[v] * (1 - p2[u] - sum_p[v]) - (n - siz[v]) * sum_p[v];
        f[v] = (n - siz[v]) * (sum_p[v] - p2[v]) + (n - (n - siz[v])) * (1 - sum_p[v]) + except_v;
        dfs2(v, u);
    }
}
int main() {
    scanf("%d", &n);
    for (int i = 1;i < n;i++) {
        int u, v;scanf("%d%d", &u, &v);
        G[u].push_back(v);G[v].push_back(u);
    }
    for (int i = 1;i <= n;i++) scanf("%lf%lf", &p1[i], &p2[i]), sum1 += p1[i], sum2 += p2[i];
    for (int i = 1;i <= n;i++) p1[i] /= sum1, p2[i] /= sum2;
    dfs1(1, 0);
    f[1] = g[1];
    dfs2(1, 0);
    double ans = 0;
    for (int i = 1;i <= n;i++) ans += p1[i] * f[i];
    printf("%.12lf", ans);
    return 0;
}
```
## The end
一道概率期望加树形 dp 好题，具备一定思维难度，但又可以一步步推出式子，对于学未至极但又学习良多的我是不多的提升较大的练习。

---

## 作者：_maze (赞：1)


思考暴力：枚举起点和终点，再枚举每一种遍历序列得到答案。复杂度起飞。

根据期望的可加性，我们无需硬着头皮统计每一条序列的贡献，而是把序列的贡献拆成遍历序列包含的边的贡献。换句话说，假如 $Edge$ 为遍历时经过的边集，$e$ 为边，则：

$$E[Edge] = \sum_{e\in Edge} E[e]$$

以上为第一部分，我们将路径贡献通过期望的性质拆成了更好计算的边的贡献。

---------

考虑边的贡献：在固定起点与终点的情况下，我们把边分为三种：在起点到终点必经之路（最短路径）上的，不在必经之路上的，与不可能走到的（这些边在以起点为根时终点的子树内）。

第一种边贡献为 $1$。因为我们必须经过这条边，且因为遍历方式为深度优先搜索，一定会在经过这条边后搜到终点结束，不可能再走第二次。

现在我们思考第二种边的贡献。我们设起点为根节点，并设这条边深度较浅的点为 $u$。我们让 $u$ 往上跳，直到遇到一个必经之路上的点 $fa$。我们令这条必经之路上边的下一个点为 $w$。

显然，$u$ 与 $w$ 分属 $fa$ 的不同子树。假如我们先进入了 $u$ 的子树，由于终点不在其中，所以会全遍历一遍后回溯，此时这条边贡献为 $2$，因为进去和出来按照题目要求要算两次。

假如我们先进入了 $w$，就不会再出来，而是遍历到终点后结束答案。此时这条边不会被计算到，贡献为 $0$。

而 $u$ 和 $w$ 先进哪棵子树完全取决于它们在遍历序列中的先后。由于序列随机，所以概率各为 $50\%$。

这时我们可以发现，第二种边对期望的贡献同样为 $1$。也就是说，固定起点终点，假如第三种边有 $m$ 条，那么我们要求的期望就是 $n - 1 - m$。

以上为第二部分，我们将边的贡献分类讨论，最终简化了要求的问题。

--------

那么我们来思考怎么快速求出最终答案。对于一个点 $u$，我们思考他作为终点的情况（此时我们设 $1$ 为根）。对于他的每棵子树，我们求出其内所有节点作为起点的概率和 $f_v$，那么以这些点作为起点能够走到的边数就是子树大小（因为包括了连向 $u$ 的边）。所以贡献为 $u\times f_v\times si_v$。

当然还有不是他子树作为起点的路径，这些路径的概率和为 $1-f_u$，边集大小为 $1-si_u$，按照上面的方式也能简单计算。

当然，钦定 $u$ 作为起点运算也是可以的。以上为第三部分。

---------

顺便一提这道题是我见过的少有的卡关闭同步流 `cin` 的题。请注意使用更快的输入方式。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n;
vector<int> e[N];
double x[N], y[N], sumX, sumY;
int si[N];
double f[N];
double ans;
double now;

void dfs(int u, int fa) {
	si[u] = 1;
	for (auto v : e[u]) {
		if (v == fa) continue;
		dfs(v, u);
		f[u] += f[v];
		si[u] += si[v];
	}
	f[u] += x[u];
}
signed main() {
  // freopen("text.in", "r", stdin);
	scanf("%d", &n);
	int u, v;
	for (int i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	for (int i = 1; i <= n; ++i) {
		scanf("%d%d", &x[i], &y[i]);
		sumX += x[i], sumY += y[i];
	}

	for (int i = 1; i <= n; ++i) x[i] /= sumX;
	for (int i = 1; i <= n; ++i) y[i] /= sumY;

	dfs(1, -1);

	double ans=0;
	for (int now = 1; now <= n; ++now) {
		for (auto v : e[now]) {
			if (si[v] > si[now]) continue;
			ans += f[v] * y[now] * si[v];
		}
		ans += (1 - f[now]) * y[now] * (n - si[now]);
	}

	printf("%.10lf\n", ans);
	
	return 0;
}
```

---

## 作者：Yanami_Anna (赞：0)

~~感觉爆杀了题解区的一些做法~~

[LINK](https://www.luogu.com.cn/problem/CF123E)

考虑计算贡献，一个点能做出什么贡献？

把点 $i$ 提起来然后考虑如果起点和终点以 $i$ 为界在不同的子树之中就一定要经过 $i$ 而且只过一遍，那就只计算一点贡献。

如果在同一棵子树之中，我们发现因为是 dfs 所以如果搜过去了就一定要搜完，所以相当于是在 dfs 的时候，如果在拐角处搜过去了就一定能搜到我这个点而且计算两次贡献，我们把点的邻接表全排列一下发现拐点要么在他前面要么在他后面，就是 $\frac{1}{2}$ 的概率能搜过去，因为和终点不在一个方向所以肯定会回溯，是两点贡献，乘起来刚好是 $1$ 点贡献。

但是有一种情况是搜不过去的，就是把起点提起来做根时，点 $i$ 在终点的子树中。

你考虑对于一个点这个很好计算，大概就是先求出子树的然后统起来再算上自己作为终点时的贡献，多个点呢？考虑换根 DP，换根下去的时候，首先把换上来的根对他的贡献去掉然后再把他作为终点的贡献中起点在原来换上来的根的子树中的也去掉，换根上来就把原来的根的贡献加上。

然后因为对期望贡献都是 $1$，所以求总期望可以直接求和。

然后就做完了。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
vector<int> ljb[100005];
double down[100005];
int allx,ally;
int X[100005];
int Y[100005];
int sizX[100005];
int sizY[100005];
double ans;
void dfs(int cur,int fa){
    sizX[cur]=X[cur];
    sizY[cur]=Y[cur];
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        if(v==fa)continue;
        dfs(v,cur);
        sizX[cur]+=sizX[v];
        sizY[cur]+=sizY[v];
    }
    return;
}
void getdown(int cur,int fa){
    down[cur]=0;
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        if(v==fa)continue;
        getdown(v,cur);
        down[cur]+=down[v];
    }
    down[cur]+=1.*Y[cur]/ally*sizX[cur]/allx;
    return;
}
void calc(int cur,int fa){
    ans+=1-down[cur];
    double tmp=down[cur];
    for(int i=0;i<ljb[cur].size();i++){
        int v=ljb[cur][i];
        if(v==fa)continue;
        down[cur]-=down[v];
        down[cur]-=(1.*Y[cur]/ally);
        down[cur]+=(1.*Y[cur]/ally*(allx-sizX[v])/allx);
        double T=down[v];
        down[v]+=down[cur];
        down[v]-=(1.*Y[v]/ally*(sizX[v])/allx);
        down[v]+=1.*Y[v]/ally;
        calc(v,cur);
        down[cur]=tmp;
        down[v]=T;
    }
    return;
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<n;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        ljb[u].push_back(v);
        ljb[v].push_back(u);
    }
    for(int i=1;i<=n;i++){
        scanf("%d%d",&X[i],&Y[i]);
        allx+=X[i];
        ally+=Y[i];
    }
    dfs(1,0);
    getdown(1,0);
    calc(1,0);
    printf("%.11lf",ans);
    return 0;
}
```

---

## 作者：LiveZoom (赞：0)

## Description

[link](https://www.luogu.com.cn/problem/CF123E)

## Solution

伪代码就是求从起点深搜到终点的步数。

考虑已经确定了起点和终点后如何求期望。

设 $p_i$ 表示 $i$ 作为起点的概率，$q_i$ 表示 $i$ 作为终点的概率，$t_i$ 表示 $i$ 的子树里的 $q$ 之和。$f_i$ 表示以 $i$ 为起点，往子树里走的期望值。

首先如果走到了一个以 $i$ 为根的子树且这个树里面没有终点，那么就要走 $2\cdot (sz_i-1)$ 步。

不妨设起点是 $u$，终点所在的子树为 $v$，那么对于 $u$ 所有不等于 $v$ 的儿子 $w$，那么他有 $\dfrac{1}{2}$ 概率在 $v$ 之前被遍历，所以 $w$ 这个子树的贡献就是 $\big[2\cdot(sz_w-1)+2\big]\times\dfrac{1}{2}$，即 $sz_w$。

所以 $v$ 对期望和的贡献就是 $f_v+(sz_u-1-sz_v+1)\cdot t_v$，也就是 $f_v+(sz_u-sz_v)\cdot t_v$。

那么 $f_u=\sum{\big[f_v+(sz_u-sz_v)\cdot t_v\big]}$。

---

然后考虑如何换根。

设 $g_v$ 表示以 $v$ 为根的期望答案。

那么考虑 $\sum{\big[f_v+(sz_u-sz_v)\cdot t_v\big]}$ 这个式子里 $f_v$ 就是多了一个 $g_u$ 去掉 $v$ 这个子树的答案，设其为 $k$。

那么 $k=g_u-(n-sz_v)\cdot t_v-f_v-sz_v\cdot (1-t_v-q_u)$，$g_v=f_v+k+sz_v\cdot(1-t_v)+(n-sz_v)\cdot (1-q_v)$。

最终答案就是 $\sum g_ip_i$。

时间复杂度：$O(n)$。

## Code

```cpp
#include <bits/stdc++.h>

// #define int long long

using namespace std;
using f64 = long double;

const int kMaxN = 1e5 + 5;

int n, sumx, sumy;
int x[kMaxN], y[kMaxN], sz[kMaxN];
f64 ans, p[kMaxN], q[kMaxN], f[kMaxN], g[kMaxN], t[kMaxN];
vector<int> G[kMaxN];

void dfs1(int u, int fa) {
  sz[u] = 1, t[u] = q[u];
  for (auto v : G[u]) {
    if (v == fa) continue;
    dfs1(v, u);
    sz[u] += sz[v];
    t[u] += t[v];
  }
  for (auto v : G[u]) {
    if (v == fa) continue;
    f[u] += f[v] + (sz[u] - sz[v]) * t[v];
  }
}

void dfs2(int u, int fa) {
  ans += p[u] * g[u];
  for (auto v : G[u]) {
    if (v == fa) continue;
    f64 f_u = g[u] - (n - sz[v]) * t[v] - f[v] - sz[v] * (t[1] - t[v] - q[u]);
    g[v] = f[v] + f_u + sz[v] * (t[1] - t[v]) + (n - sz[v]) * (t[v] - q[v]);
    dfs2(v, u);
  }
}

void dickdreamer() {
  cin >> n;
  for (int i = 1; i < n; ++i) {
    int u, v;
    cin >> u >> v;
    G[u].emplace_back(v);
    G[v].emplace_back(u);
  }
  for (int i = 1; i <= n; ++i) {
    cin >> x[i] >> y[i];
    sumx += x[i];
    sumy += y[i];
  }
  for (int i = 1; i <= n; ++i) {
    p[i] = x[i] * 1.0 / sumx;
    q[i] = y[i] * 1.0 / sumy;
  }
  dfs1(1, 0);
  g[1] = f[1];
  dfs2(1, 0);
  cout << fixed << setprecision(10) << ans << '\n';
}

int32_t main() {
#ifdef ORZXKR
  freopen("in.txt", "r", stdin);
  freopen("out.txt", "w", stdout);
#endif
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  int T = 1;
  // cin >> T;
  while (T--) dickdreamer();
  // cerr << 1.0 * clock() / CLOCKS_PER_SEC << 's';
  return 0;
}
```



---

