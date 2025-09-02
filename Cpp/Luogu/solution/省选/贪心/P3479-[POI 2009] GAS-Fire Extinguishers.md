# [POI 2009] GAS-Fire Extinguishers

## 题目描述

Byteasar 新建了一座宫殿。它由 $n$ 个房间和 $n-1$ 条走廊连接而成。每条走廊正好连接两个房间。房间编号从 $1$ 到 $n$。宫殿只有一个入口，通向编号为 $1$ 的房间。对于每个房间，从入口到它只有一条不回头的路线。换句话说，房间和走廊形成了一棵树——一个连通无环图。

负责批准建筑的消防员要求在内部放置灭火器。

他的具体要求如下：

- 灭火器应放置在（某些）房间中，一个房间可以存放任意数量的灭火器。
- 每个房间必须分配一个灭火器，尽管它可以存放在另一个房间中。
- 每个灭火器最多可以分配给 $S$ 个不同的房间。
- 对于每个房间，其分配的灭火器在 $K$ 条走廊范围内。

Byteasar 对奢华的宫殿情有独钟，所以毫不奇怪，在完成另一个辉煌的宫殿后，他现在几乎没有钱。

因此，他对满足消防员要求所需的最少灭火器数量感兴趣。

## 说明/提示

$1 \leq n,m \leq 100000, 1 \leq k \leq 20 , x_i \geq 1$。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
12 3 1
1 12
3 8
7 8
8 9
2 12
10 12
9 12
4 8
5 8
8 11
6 8
```

### 输出

```
4
```

# 题解

## 作者：ysner (赞：5)

这道题应为树形DP。

感性的理解一下，灭火器应该放在越上面的地方越好。

那么就按照深度由大到小来放灭火器。

对于一个节点x，

如果在它的子树中仍存在着距离它k的节点没有灭火器，

那么这些灭火器就一定要在x这个位置分配出去，

因为再上面的节点无法给这些节点分配。

设f[x][k]表示在x的子树中，距离x为k的灭火器有多少个点能分配。

设g[x][k]表示在x的子树种，距离x为k的灭火器需求的点数。

gx,k 是一定要在x这个节点分配完的。

lca为x的也一个在这课子树里面匹配完。

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#define ll long long
#define re register
#define il inline
#define fp(i,a,b) for(re int i=a;i<=b;i++)
#define fq(i,a,b) for(re int i=a;i>=b;i--)
using namespace std;
const int N=2e5+50;
int n,s,k;
int f[N][22],g[N][22],ans=0,h[N],cnt;//G[x][k]表示x下面距离为k的需要灭火器的房间数，F[x][k]表示x下面距离为k的多余灭火器数
struct Edge
{
    int to,next;
}e[N];
il int gi()
{
    re int x=0;
    re int t=1;
    re char ch=getchar();
    while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
    if(ch=='-') t=-1,ch=getchar();
    while(ch>='0'&&ch<='9') x=x*10+ch-48,ch=getchar();
    return x*t;
}
il int ceil(int x)//除以s的向上取整
{
    return x ? (x-1)/s+1 : 0;
}
il void add(int u,int v)
{
    e[++cnt]=(Edge){v,h[u]};h[u]=cnt;
}
il void dfs(int u,int fa)
{
    for(re int i=h[u];i+1;i=e[i].next)
    {
        int v=e[i].to;
        if(v==fa) continue;
        dfs(v,u);
        fp(j,1,k)
            f[u][j]=min(n,f[u][j]+f[v][j-1]),g[u][j]+=g[v][j-1];//把能分配的点数向上汇总（当然要小于等于n），需要的点数也向上
    }
    g[u][0]++;//子树根节点需要灭火器
    if(g[u][k])
    {
        int t=ceil(g[u][k]);//如果要分配点数，向上取整取灭火器个数
        f[u][0]=min(1ll*n,1ll*t*s),ans+=t;//保证能灭点数小于n
    }
    fp(i,0,k)
    {
        int j=k-i,d=min(f[u][i],g[u][j]);
        f[u][i]-=d,g[u][j]-=d;
    }
    fp(i,0,k-1)//此循环基本是对上一个循环的重复，因如果灭火器和一个需要配对的点距离为k或k-1，那么在他们的lca处肯定要进行匹配，因为如果往上就是k+2
    {
        int j=k-1-i,d=min(f[u][i],g[u][j]);
        f[u][i]-=d,g[u][j]-=d;
    }
}
int main()
{
//    freopen("repulsed.in","r",stdin);
//    freopen("repulsed.out","w",stdout);
    memset(h,-1,sizeof(h));
    n=gi();s=gi();k=gi();
    fp(i,1,n-1)
    {
        int u=gi(),v=gi();
        add(u,v);add(v,u);
    }
    dfs(1,0);
    fp(i,0,k)
        fq(j,k,0)
        if(i+j<=k)
        {
            int d=min(f[1][i],g[1][j]);
            f[1][i]-=d,g[1][j]-=d;
        }
    int tot=0;
    fp(i,0,k) tot+=g[1][i];
    ans+=ceil(tot);
    printf("%d\n",ans);
    //fclose(stdin);
    //fclose(stdout);
    return 0;
}

```

---

## 作者：大菜鸡fks (赞：3)

这题真没什么思路，感觉自己还是太菜了。想的贪心貌似不全面，naive！

主要思路就是万不得已一定要用的时候才用。下面说一下贪心的过程。

设f[u][d]表示在子树中与点u距离为d的点有多少能分配

设g[u][d]表示在子树中与点u距离为d的点有多少需要被分配（未被管理）

1.继承儿子的数组值。

接下来就是处理必要的点了。

2.覆盖离当前根节点距离为d的未覆盖的点。

3.覆盖两点之间距离为d的未覆盖的点。

4.覆盖两点之间距离为d-1的未覆盖的点。（如果向上爬一步，两点间距离会变成d+1）

最后再处理一下根节点的特殊情况。

```cpp
#include<cstdio>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=100005;
struct edge{
	int link,next;
}e[N<<1];
int n,s,d,head[N],tot;
inline void add_edge(int u,int v){
	e[++tot]=(edge){v,head[u]}; head[u]=tot;
}
inline void insert(int u,int v){
	add_edge(u,v); add_edge(v,u);
}
inline void init(){
	n=read(); s=read(); d=read();
	for (int i=1;i<n;i++){
		int u=read(),v=read();
		insert(u,v);
	}
}
int ans,f[N][25],g[N][25];
inline int ceil(int x){return x?(x-1)/s+1:0;}
void dfs(int u,int fa){
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v!=fa){
			dfs(v,u);
			for (int j=1;j<=d;j++){
				f[u][j]=min(f[u][j]+f[v][j-1],n);
				g[u][j]+=g[v][j-1];
			}
		}
	}
	g[u][0]++;
	if (g[u][d]){
		int t=ceil(g[u][d]);
		f[u][0]=min(n,s*t); ans+=t;
	}
	for (int i=0;i<=d;i++){
		int j=d-i,res=min(g[u][j],f[u][i]);
		f[u][i]-=res; g[u][j]-=res;
	}
	for (int i=0;i<d;i++){
		int j=d-1-i,res=min(g[u][j],f[u][i]);
		f[u][i]-=res; g[u][j]-=res;
	}
}
inline void solve(){
	dfs(1,0);
	for (int i=0;i<=d;i++){
		for (int j=d;j>=0;j--){
			if (i+j<=d){
				int res=min(f[1][i],g[1][j]);
				f[1][i]-=res; g[1][j]-=res;
			}
		}
	}
	int res=0;
	for (int i=0;i<=d;i++){
		res+=g[1][i];
	}
	ans+=ceil(res);
	writeln(ans); 
}
int main(){
	init();
	solve();
	return 0;
}
```

---

## 作者：AlanSP (赞：3)

## 又双叒叕丢人的树形DP。
感觉题解里dalao们讲得不是很详细~~是我太菜了吗~~。  
首先我开了无向图，判断fa（好像有向也可以？。 

记录两个数组f[u][i]，g[u][i],分别表示u的子树中，有i个可以分配的点和必须分配的点。
  
这题我仅仅是样例就调了n遍，下面分享一下坑点qwq  。  

### 1.每次dfs时，要把根节点u的g++ 。 
因为在目前状态来看，只有根节点的灭火器可以覆盖自己，所以要加1。  
### 2.每次转移时要下取整。  
节点数除以s可能会是小数，要进上那一位（进一法）。 
### 3.对子树来说，距离为k和k-1的点都要考虑  
距离为k的点显然。  

反证法，距离为k-1的点如果不处理，在往上调的时候距离会变成k+1，不符合了。  

### 4.子树中相对应的点要抵消掉

理解很容易，因为如果距离根为i点在根处解决了，那么和根距离k-i点也被覆盖了。

### 5.根节点特判

因为无法向上跳，所以特判。
并且所有的信息都要在根处汇总。

没什么可说的了qwq。
```
#include <bits/stdc++.h>
using namespace std;
const int N=100009;

int n,s,k,ans;
int h[N],ver[N<<1],nxt[N<<1],tot;
int g[N][29],f[N][29];

inline void add(int x,int y)
{
	ver[++tot]=y,nxt[tot]=h[x],h[x]=tot;
}

inline void dfs(int u,int fa)
{
	for(int i=h[u];i;i=nxt[i])
	{
		int v=ver[i];
		if(v!=fa) 
		{
			dfs(v,u);
			for(int j=1;j<=k;j++) f[u][j]=min(n,f[u][j]+f[v][j-1]),g[u][j]+=g[v][j-1];
		}
	}
	g[u][0]++;
	if(g[u][k])
	{
		int tem=(g[u][k]+s-1)/s;
		f[u][0]=min(n,s*tem),ans+=tem;
	}
	if(u==1)
	{
		for(int i=0;i<=k;i++)
			for(int j=k-i;j>=0;j--)
			{
				int tem=min(f[1][i],g[1][j]);
				f[1][i]-=tem,g[1][j]-=tem;
			}
		return;
	}
	for(int i=0;i<=k;i++)
	{
		int tem=min(f[u][i],g[u][k-i]);
		f[u][i]-=tem,g[u][k-i]-=tem;//可以合并，能够满足f[u][i]的一定满足g[u][k-i]
	}
	for(int i=0;i<=k-1;i++)
	{
		int tem=min(f[u][i],g[u][k-i-1]);
		f[u][i]-=tem,g[u][k-i-1]-=tem;
	}
}

int main()
{
	scanf("%d%d%d",&n,&s,&k);
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y),add(y,x);
	}
	dfs(1,0);
	int tem=0;
	for(int i=0;i<=k;i++) tem+=g[1][i];
	ans+=(tem+s-1)/s;
	printf("%d",ans);
	return 0;
}
```


---

## 作者：Blithe_C (赞：2)

一道烧脑的树上优化问题. 目前的几篇题解并没有把关键想法以及定义说得足够清楚，而且这个优化思路值得一看，因此写一篇新的题解.

***
简明题意：在一棵树上安装尽可能少的灭火器，希望其影响范围覆盖整棵树. 每个灭火器的影响节点数目和半径有限制. 求出最少的灭火器数.

形式化题意：给定正整数 $n,s,k$ 和一棵 $n$ 节点的树 $T$. 定义一个**灭火器** $E$ 为一个二元组 $(loc, range)$，其中**位置** $loc$ 是 $T$ 的一个节点，**管辖范围** $range$ 是元数 $\leq s$ 的点集，其每个点（称其被 $E$ 管辖）都在 $T$ 上且与 $loc$ 间的路径长皆不超过 $k$. 你可以构造 $m$ 个灭火器并任意指定其位置和管辖范围，求最小的 $m$ 使得所有灭火器的管辖范围之并为 $T$  的全体节点.

数据范围：$1\leq s\leq n\leq 10^5$，$1\leq k \leq 20$.

本题样例图示：![](https://szkopul.edu.pl/problemset/problem/b6w9exQhg7_bIqOTUqj3cTGk/site/images/OI16/gas1.gif).

***
首先，我们免不了任选一个根对树 DFS（这边采用后根周游），此过程中可能以树上 DP 的方式更新答案.

每个节点 $pos$ 的子问题是什么？目标是在 $pos$ 上放灭火器，但是需要**最优**地放置.

$s$ 和 $k$ 分别约束了灭火器的影响数量和半径，可从其入手. 由于一个节点可以放多个灭火器，而相对位置是确定的，试着优先卡 $k$ 的界，即尽量在距离（路径长）达到 $k$ 时放灭火器. 很自然地，需要知道 $pos$ 的子树中与其距离为 $k$ 的点有多少个，故用二维变量 $neibs(pos, dist)$ 记录 $pos$ 的子树中与其距离为 $dist$ 的点数，DFS 时递推更新.

因为不希望同一个节点被多个灭火器管辖，新增的灭火器管辖的点应该“扣除”掉，故需要一个动态量. 改用变量 $unasn(pos, dist)$ 表示子树中与 $pos$ 距离为 $dist$ 的**未被管辖点数**. 假设在当前位置 $unasn(pos, k)>0$，则必须在 $pos$ 新增 $d=\lceil\frac{unasn(pos, k)}{s}\rceil$ 个灭火器.

***
接下来，一种平凡的贪心思路就是把 $unasn(pos, k)$ 内的点全部扣除，然后从远到近分配子树里刚放置的灭火器的**剩余可管辖点数** $d×s-unasn(pos, k)$，并扣除直到其为 $0$.

这样合适吗？

且不说这样剩余管辖权可能扣不完，一个点的灭火器除了可以管辖 DFS 正向的子树，还可以管到**反向的那棵子树**，这同样需要斤斤计较.

所以之前安装过的灭火器之后仍需定位和更新，于是引入第二个动态变量 $margin(pos, dist)$ 表示子树中与 $pos$ 距离为 $dist$ 的**灭火器**的**剩余可管辖点数**. 平凡思路也不能用，暂时只把 $pos$ 处的灭火器分配给 $unasn(pos, k)$ 这些点.

***
一句预警，下面贪心策略的最优性证明不仅我不会，而且网上也没找到，应该不是三言两语的问题. 贪心方法很多时候是微妙的，我们好做的只是直觉上理解为什么它好、以及说明其它策略没有它优.

下边是两个主要观察：

i) 为处理一个位于 $p$ 的灭火器管辖反向子树的情况，只需处理 $p$ 与其具有共同 LCA 的那些子树中未被管辖点的关系. 换言之，DFS 到一个位置 $pos$ 时，要考虑**子树间管辖权的分配**.

ii) 我们仍想「**尽量只管与灭火器相距 $k$ 的点**」，那就将其实施下去. 记 $D(u, v)$ 为节点距离，我们寻找子树间这样的点对 $x, y$，其满足 $D(x, pos)+D(pos, y)=k$，且 $x$ 位置有没耗尽管辖权的灭火器且 $y$ 点还没被管辖. 除非 $x$ 和 $y$ 在一棵子树上，否则 $k=D(x, pos)+D(pos, y)=D(x, y)$. **然后把 $x$ 位的灭火器管辖权分给 $y$**，即让 $margin(pos, D(x, pos))$ 和 $unasn(pos, D(pos, y))$ 值同时减小至一个为 $0$.（注意 $D(x, pos)=0$ 就是前面分配 $pos$ 处灭火器的情况.）

换言之，我们需要在每个 $pos$ 处合并所有子树的信息，然后**枚举子树间节点的“中间距离” $D(x, pos)$** 作上述更新：
```
using std::min;

int nodes, capacity, reach; // n, s, k
vector<vector<int>> edge, unassigned, margin; // unassigned 即 unasn
int count = 0; // 统计灭火器

inline int ceil_div(int above, int below){
	return (above+below-1)/below;
}

void travel_and_assign(int pos, int prev){
	unassigned[pos][0] = 1;
	for(auto &neib: edge[pos]){ // 遍历子节点
		if(neib==prev) continue;
		travel_and_assign(neib, pos);
		for(int dist = 1; dist<=reach; ++ dist){
			unassigned[pos][dist] += unassigned[neib][dist-1];
			margin[pos][dist] += margin[neib][dist-1]; margin[pos][dist] = min(margin[pos][dist], nodes); // 灭火器可管辖点数超过 nodes 时，无意义
		}
	}
	if(unassigned[pos][reach]>0){ // 决定在 pos 处放灭火器
		int employed = ceil_div(unassigned[pos][reach], capacity);
		count += employed;
		margin[pos][0] = min(employed*capacity, nodes);
	}
	for(int dist = 0; dist<=reach; ++ dist){ // 枚举中间距离并“再分配”
		int offset = min(unassigned[pos][reach-dist], margin[pos][dist]);
		unassigned[pos][reach-dist] -= offset; margin[pos][dist] -= offset;
	}
}
```
这基本是正解了，可得 ${\rm 20\,pts}$，还需~~亿~~些修改.

i) 根节点要特殊处理.

因为之前在每个 $pos$ 都没有把灭火器的管辖分配彻底，必须给最后剩下的**全部**未被管辖点分配. 对应的改动是，上面代码中的 ``reach-dist`` 需要改成一个从 ``reach-dist`` 枚举到 ``0`` 的循环变量. 有可能分完还有未被管辖点，则最后在根节点补灭火器解决. ${\rm 60\,pts}$.

ii) 如上所说，每个 $pos$ 都没有把灭火器的管辖分配彻底，影响最优性.

这里是此贪心法最微妙的地方.

我们也不愿意在每个 $pos$ 像根节点那样彻底分配，直到子树不留未被管辖点，这样会浪费管辖半径. —— 实际上本人这样写竟通过了本题，${\rm 326\,ms}$，似乎数据较水，但样例的输出是错的......

我们可以做个折衷，前面将子树内所有灭火器的管辖权分给了与其距离为 $k$ 的点，现在我们再分给“**次必要**”的与其距离为 $k-1$ 的点：考虑 $pos$ 子树内满足 $D(x, pos)+D(pos, y)=k-1$ 的点 $x, y$，当 DFS 跳到 $pos$ 的前驱 $pos'$ 时，$D(x, pos')+D(pos', y)=(k-1)+2=k+1>k$，故 $x$ 和 $y$ 如果不在 $pos$ 处理就无法再在 $pos'$ 同法处理.

即递归中要再加一条枚举：
```
	for(int dist = 0; dist<=reach-1; ++ dist){
		int offset = min(unassigned[pos][reach-1-dist], margin[pos][dist]);
		unassigned[pos][reach-1-dist] -= offset; margin[pos][dist] -= offset;
	}
```
如此可通过本题，${\rm 794\,ms}$.

算法的时间复杂度 $O(kn)$，空间复杂度 $O(kn)$.

本题最大的看点在于设计子问题（DP 状态）以及对贪心原则的坚持.

***
完整代码. 不嫌累式码风警告.
```
#include <bits/stdc++.h>

#define IOS_SPEED std::ios::sync_with_stdio(false)

using std::cin, std::cout;
using std::vector;
using std::min;

using lli = long long;

int nodes, capacity, reach;
vector<vector<int>> edge;

inline int ceil_div(int above, int below){
	return (above+below-1)/below;
}

void travel_and_assign(int pos, int prev, vector<vector<int>> &unassigned, vector<vector<int>> &margin, int &count){
	unassigned[pos][0] = 1;
	for(auto &neib: edge[pos]){
		if(neib==prev) continue;
		travel_and_assign(neib, pos, unassigned, margin, count);
		for(int dist = 1; dist<=reach; ++ dist){
			unassigned[pos][dist] += unassigned[neib][dist-1];
			margin[pos][dist] += margin[neib][dist-1]; margin[pos][dist] = min(margin[pos][dist], nodes);
		}
	}
	if(unassigned[pos][reach]>0){
		int employed = ceil_div(unassigned[pos][reach], capacity);
		count += employed;
		margin[pos][0] = min(employed*capacity, nodes);
	}
	for(int dist = 0; dist<=reach; ++ dist){
		int offset = min(unassigned[pos][reach-dist], margin[pos][dist]);
		unassigned[pos][reach-dist] -= offset; margin[pos][dist] -= offset;
	}
	for(int dist = 0; dist<=reach-1; ++ dist){
		int offset = min(unassigned[pos][reach-1-dist], margin[pos][dist]);
		unassigned[pos][reach-1-dist] -= offset; margin[pos][dist] -= offset;
	}
}

int least_extinguishers(){
	int ret = 0;
	auto unassigned = vector(nodes+1, vector<int>(reach+1, 0)), margin = vector(nodes+1, vector<int>(reach+1, 0));
	travel_and_assign(1, 0, unassigned, margin, ret);
	for(int dist = 0; dist<=reach; ++ dist){
		for(int other = reach-dist; other>=0; -- other){
			int offset = min(unassigned[1][other], margin[1][dist]);
			unassigned[1][other] -= offset; margin[1][dist] -= offset;
		}
	}
	int rest = 0;
	for(int dist = 0; dist<=reach; ++ dist) rest += unassigned[1][dist];
	ret += ceil_div(rest, capacity);
	return ret;
}

void interface(){
	cin >> nodes >> capacity >> reach;
	edge.resize(nodes+1);
	for(int i=0; i<nodes-1; ++i){
		int X, Y; cin >> X >> Y;
		edge[X].emplace_back(Y); edge[Y].emplace_back(X);
	}
	cout << least_extinguishers() << "\n";
	edge.clear();
}

int main()
{
	IOS_SPEED;
	interface();
	return 0;
}
```

---

## 作者：MikukuOvO (赞：2)

好难的一道题。。。

首先我们从下往上考虑，直到必须要选的时候再选，可以证明这样一定最优。

我们设计两个状态。

$f[i][j]$表示以$i$为根的子树中距离$i$为$j$的灭火器还有多少点能分配。

$g[i][j]$表示以$i$为根的子树中距离$i$为$j$的点还有多少没有灭火。

我们考虑点$x$是否放置灭火器的条件，当且仅当距离$x$为$k$的点还需要放置灭火器。因为如果不考虑$x$，那么子树已经达到最优，而且我们不能使用$x$的其他子树中的灭火器，因为距离和大于$k$。

接着，我们还要考虑子树之间的情况。

考虑两个位于不同子树中的灭火器和点，如果他们的距离和为$k$或$k-1$，那么就将他们相消。

关于证明，如果他们都匹配了距离之和小于$k-1$的点，那么交换匹配不会使得答案更劣。

根结点需要特殊考虑。

---

## 作者：SnowTrace (赞：0)

我们考虑这种在树上的限制。

遍历一棵树，一般我们都是在已经到达边界情况，不得不取的情况下才去做一步操作。

-----

在这道题里面，就是，如果我们选了点 $i$ 当灭火器，那么我们尽量是让它满足和它距离是 $k$ 的点。

这是一个最基本的想法。

我们优先满足子树内的点，再考虑子树外的点，因为这样才能使得以 1 为根的这个树的结构得到最大利用。

什么情况下会需要满足子树外的点？

实际上就是子树里面的灭火器出现了剩余，子树里面距离为 $k$ 的点已经全部消除的情况。

我们记录 $g_{i,j}$ 表示以 $i$ 为根的子树中距离 $i$ 为 $j$ 的灭火器还有多少个点剩余下来可以进行匹配。

每次我们以当前根为 lca，满足当前距离为 $k-1$ 和 $k$ 的所有点。$k-1$ 是因为，再往上一格路径就变成 $k+1$ 了，所以 $k-1$ 的时候也必须匹配。

然后我们对根节点特殊处理一下即可，在根节点所有的点都应该被匹配了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
vector<int>p[200005];
int f[200005][21],g[200005][21];
// f表示需要分配的  g表示多余的
int n,k,s; int ans = 0;
void dfs(int now,int fa){
	f[now][0] = 1;	
	for(int x:p[now]){
		if(x == fa)continue;
		dfs(x,now);
		for(int i = 0;i<=k-1;i++){
			f[now][i+1]+=f[x][i],g[now][i+1]+=g[x][i];
		}
	}int need = (f[now][k]+s-1)/s;ans+=need;
	int l = s*need-f[now][k];f[now][k] = 0;
	g[now][0]+=l;
	for(int i = 0;i<=k;i++){
		int j = k-i;
		int d = min(f[now][i],g[now][j]);
		f[now][i]-=d,g[now][j]-=d; 
	}
	for(int i = 0;i<=k-1;i++){
		int j = k-1-i;
		int d = min(f[now][i],g[now][j]);
		g[now][j]-=d,f[now][i]-=d;
	}
}
signed main(){
	cin >> n >> s >> k; 
	for(int i = 1;i<n;i++){
		int a,b;cin >> a >> b;
		p[a].push_back(b),p[b].push_back(a);
	}dfs(1,1);
	for(int i =0;i<=k;i++){
		for(int j =0;j<=k;j++){
			if(i+j<=k){
				int d = min(f[1][i],g[1][j]);
				f[1][i]-=d,g[1][j]-=d;
			}
		}
	}int tot =0 ;
	for(int i =0;i<=k;i++)tot+=f[1][i];
	ans+=(tot+s-1)/s;
	cout << ans << endl;
	return 0;
}
```

---

