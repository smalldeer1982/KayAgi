# Leaf Partition

## 题目描述

给定一棵有 $n$ 个节点的有根树，节点编号为 $1$ 到 $n$，树的根为节点 $1$。第 $i$ 个节点的父节点为 $p_i$。叶子节点是没有子节点的节点。对于给定的叶子节点集合 $L$，定义 $f(L)$ 为包含所有叶子节点 $L$ 的最小连通子图。

你希望将所有叶子节点划分为若干组，使得对于任意两个不同的组 $x, y$，$f(x)$ 和 $f(y)$ 互不相交。

请计算有多少种划分叶子节点的方案，答案对 $998244353$ 取模。如果存在两种方案，使得存在两个叶子节点在一种方案中属于同一组，在另一种方案中属于不同组，则认为这两种方案不同。

## 说明/提示

在第一个样例中，叶子节点为 $2,3,4,5$。划分叶子节点的方案如下图所示。![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1146F/2d93c754688fbf52dd6de0ea5eb71d8810080c88.png)

在第二个样例中，唯一的叶子节点是 $10$，因此只有一种划分方案。注意节点 $1$ 不是叶子节点。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5
1 1 1 1
```

### 输出

```
12
```

## 样例 #2

### 输入

```
10
1 2 3 4 5 6 7 8 9
```

### 输出

```
1
```

# 题解

## 作者：ISYRHH (赞：17)

## CF1146F Leaf Partition


------

为了备课写了几道树形 dp，这道就是其中之一，思路比较简单，代码也只有 30 行，但是容斥死活搞不清楚，半天没过第四个点，拍的小数据也不给力，debug 一年后口胡一组数据卡掉了，改完就过了。打完看了看和题解的思路不太一样，就水篇题解。


------

## 题意分析

题目总结一下就是求把一棵树的叶子划分为几个连通块的方案数，要求划分的连通块不相交，并包含所有叶子。


------

## 解法

简单构思就会想到在树上 dfs 处理，对每个节点处理出子树的划分方案数，再向上合并。

记录两种状态：

&emsp;&emsp;1.$dp_{x,0}$ 表示 $x$ 未被划进任何连通块内，即不存在两个不同儿子所在子树的任何叶子被划进同一连通块（否则 $x$ 也必须划进这个连通块）的包含子树中所有叶子的划分数。

&emsp;&emsp;2.$dp_{x,1}$ 表示 $x$ 被划进一个连通块内的包含子树中所有叶子的划分数。

考虑转移：

设当前考虑的节点为 $x$，当前考虑的儿子为 $y$。

（1）

&emsp;&emsp;$dp_{x,1}$ 必须保证有两个 lca 为 $x$ 的点被划进了一个连通块，换种说法就是有至少两个儿子向上延伸在 $x$ 处会合。

&emsp;&emsp;考虑把儿子遍历一遍，用一个 $tot$ 变量记录前面遍历过的儿子向上蔓延和不向上蔓延的总方案数（前缀积），再用一个 $tot2$ 变量记录前面遍历过的儿子都不向上蔓延的方案数，很明显，$tot-tot2$ 就是前面有至少一个儿子向上延伸了的方案数，乘上这个儿子向上延伸的方案数就是这个儿子对 $dp_{x,1}$ 的贡献。

&emsp;&emsp;为了保证方案不重不漏加上一个简单的容斥（ISYRHH 管什么都叫容斥），记录方案时只在后面更新前面的延伸，并保证后面的都不会延伸（通过在遍历下一个儿子时对 $dp_{x,1}$ 乘上下个儿子不向上延伸的方案数实现。

（2）

&emsp;&emsp;$dp_{x,0}$ 要保证没有一个儿子向上延伸（不可能只有一个儿子向上延伸）在遍历完所有儿子后把 $tot2$ 赋给 $dp_{x,0}$ 即可。

开始我把儿子的 $dp_{y,1}$（向上蔓延），$dp_{y,0}$（向上蔓延），$dp_{y,1}$（不向上蔓延），$dp_{y,0}$（不向上蔓延）和的前缀积作为 $tot$，儿子的 $dp_{y,1}$（不向上蔓延），$dp_{y,0}$（不向上蔓延）和的前缀积作为 $tot2$，交上代码后发现在第四个点挂了（而且答案相差很小，我怀疑了半天取模的问题）。

再仔细研究一下题面会发现，对于一个 $dp_{y,1}$ 的向上蔓延没有问题，但是对于一个 $dp_{y,0}$ 的向上蔓延，可能有不止一种的方案，还需要考虑每种方案子树有几个节点可以向上延伸。

于是还需要再引入一个 $dp_{x,2}$ 记录对于 $x$ 没有被包含的方案中，有多少个节点是可以向上蔓延的。

$dp_{x,2}$ 同样必须保证没有一个儿子向上延伸，然后对每个儿子分别考虑使该儿子子树中的节点向上延伸的方案数。

不包含该儿子的方案的贡献即为该儿子的 $dp_{y,2}$。

若包含该儿子，则只有一种方式向上延伸，这部分的贡献为 $dp_{y,1}$。

同样需要乘上 $tot2$，并对于在遍历到每个儿子时将 $dp_{x,2}$ 乘上这个儿子不向上延伸的方案数。

这样就得到了 $dp_{x,2}$ 的转移。

重新把儿子的 $dp_{y,1}$（向上蔓延），$dp_{y,2}$（向上蔓延），$dp_{y,1}$（不向上蔓延），$dp_{y,0}$（不向上蔓延）和的前缀积作为 tot，儿子的 $dp_{y,1}$（不向上蔓延），$dp_{y,0}$（不向上蔓延）和的前缀积作为 $tot2$，按照前面的方式计算出 $dp_{x,0}$ 和 $dp_{x,1}$。

最后的答案就是 $dp_{1,0}+dp_{1,1}$。

（记得开 long long，记得取模……）


------------

## 代码

```cpp
#include<cstdio>
#include<vector>
#define mo 998244353
using namespace std;
long long n,m,in,fa[200001],dp[200001][3];
vector<long long>ed[200001];//《因为太懒就直接邻接表存图了》
void dfs(long long x)
{
    if(ed[x].empty()){dp[x][1]=1;return;}//若为叶子节点直接返回
    long long tot=1,tt=1;//分别记录所有情况的前缀积和不向上延伸的前缀积
    for(vector<long long>::iterator ite=ed[x].begin();ite!=ed[x].end();ite++)
    {
        fa[*ite]=x;dfs(*ite);
        dp[x][1]=(dp[x][1]*((dp[*ite][0]+dp[*ite][1])%mo)%mo+(dp[*ite][1]+dp[*ite][2])%mo*(tot-tt)%mo)%mo;
        dp[x][2]=dp[x][2]*((dp[*ite][0]%mo+dp[*ite][1]%mo)%mo)%mo;dp[x][2]=((dp[*ite][2]+dp[*ite][1])%mo*tt%mo+dp[x][2])%mo;//简单的dp转移
        tot=tot*((dp[*ite][1]%mo+dp[*ite][1]%mo+dp[*ite][0]%mo+dp[*ite][2])%mo)%mo;tt=tt*((dp[*ite][0]%mo+dp[*ite][1]%mo)%mo)%mo;//简单的前缀积转移
    }
    dp[x][0]=(dp[x][0]%mo+tt%mo)%mo;//处理dp[x][0]
}
int main()
{
    scanf("%lld",&n);
    for(long long i=2;i<=n;i++)
    {
        scanf("%lld",&in);
        ed[in].push_back(i);
    }
    dfs(1);
    printf("%lld",((dp[1][0]%mo+dp[1][1]%mo)%mo+mo)%mo);
    return 0;
}
//I can't happy anymore（本来想水点题快乐，就把程序名定成了happy，结果debug过于痛苦……）
```

------------


## **end**

---

## 作者：wucstdio (赞：11)

首先我们考虑转化。

对于每一个颜色，我们把它的虚树从原树上切下来，这样原来的树就变成了若干棵不想交的子树以及可能会剩下的一堆未染色点：

![](https://cdn.luogu.com.cn/upload/pic/61357.png)

想明白这一点，接下来就可以DP了，我们先拎出来一种颜色形成的树，考虑这里面的一棵子树的根可能会有几种情况：

1、被染色，且孩子数量等于$1$，记为$f_i$。

2、被染色，且孩子数量大于等于$2$，记为$g_i$。

3、未被染色，记为$h_i$。

为什么要把12分开？因为2可以作为这种颜色的根，而1不能。

接下来考虑转移：

![](https://cdn.luogu.com.cn/upload/pic/61360.png)

对于$f_i$，可能从本身引出，也可能从$v$这棵子树中引出，所以$f_i=f_i(g_v+h_v)+h_i(f_v+g_v)$

对于$g_i$，可能都在$i$本来的子树里，也有可能有一个孩子在$v$的子树里，所以$g_i=g_i(f_v+2g_v+h_v)+f_i(f_v+g_v)$，中间的那个$2$是因为这两种颜色可能相同也可能不同

对于$h_i$，两边都不能上去，所以$h_i=h_i(g_v+h_v)$

然后就可以直接DP了。注意这三个数组DP的顺序。时间复杂度$O(n)$

```cpp
#include<cstdio>
#include<algorithm>
#include<cstring>
#define ll long long
using namespace std;
const ll MOD=998244353;
struct Edge
{
	int to;
	int nxt;
}e[200005];
int n,m,edgenum,head[200005],pa[200005];
ll f[200005],g[200005],h[200005];
void add(int u,int v)
{
	e[++edgenum].to=v;
	e[edgenum].nxt=head[u];
	head[u]=edgenum;
}
void dfs(int node)
{
	if(!head[node])
	{
		g[node]=1;
		return;
	}
	h[node]=1;
	for(int hd=head[node];hd;hd=e[hd].nxt)
	{
		int to=e[hd].to;
		dfs(to);
		g[node]=(g[node]*(f[to]+2*g[to]+h[to])+f[node]*(f[to]+g[to]))%MOD;
		f[node]=(f[node]*(g[to]+h[to])+h[node]*(f[to]+g[to]))%MOD;
		h[node]=h[node]*(g[to]+h[to])%MOD;
	}
}
int main()
{
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&pa[i]);
		add(pa[i],i);
	}
	dfs(1);
	printf("%I64d\n",(g[1]+h[1])%MOD);
	return 0;
}
```

---

## 作者：Piwry (赞：10)

感觉不错的一道树 dp，状态设计的细节很多

## 解析

可以知道题中要求的 “最小连通子图” 一定是叶子两两间最短路径（到 lca 然后再下来）的并

定义连接两个同组结点的边为 “染色边”；同样地，如果一个结点被划分到某个连通子图内，就称它为 “染色的”（叶子一定染色）

&nbsp;

我们设 $dp(u, 0/1/2)$ 表示 $u$ 向儿子连接了 $0/1/\geq2$ 条染色边的方案数，这里要求 $u$ 不能为叶子（原因后面讲）

可以发现，连了 $0/\geq2$ 条染色边的结点，都是可以确定最后不是/是被染色的；而只连了 $1$ 条染色边的结点，我们必须接着向上连直到 “合并”（否则就不是最小连通子图了）

于是连了 $0$ 条染色边的结点不能再向上连染色边；连了 $1$ 条染色边的结点一定要向上连染色边；连了 $\geq2$ 条染色边的结点可以向上连染色边，也可以不连

通过对儿子染色状态的推断，我们就可得出（加入新儿子时的）转移方程：

$dp'(u, 0)=dp(u, 0)\cdot(dp(v, 0)+dp(v, 2))$

$dp'(u, 1)=dp(u, 0)\cdot(dp(v, 1)+dp(v, 2))+dp(u, 1)\cdot(dp(v, 0)+dp(v, 2))$

$dp'(u, 2)=dp(u, 1)\cdot(dp(v, 1)+dp(v, 2))+dp(u, 2)\cdot(dp(v, 0)+dp(v, 1)+2dp(v, 2))$

其中 $v$ 是新加入的儿子子树根；相乘可以理解为每种方案一一 “配对”（感觉这还是挺好理解的）

注意第三行中的 $2dp(v, 2)$，这是因为 “连了 $\geq2$ 条染色边的结点可以向上连染色边，也可以不连”

而 dp 的初值可以根据定义得出，应为 $dp(u, 0) =1, dp(u, 1) =0, dp(u, 2) =0$

&nbsp;

最后我们再考虑叶子的状态设计

由于我们在转移时，实际上是考虑儿子的染色情况；于是即使叶子不会向下连染色边，我们由在父亲处的转移要求可以推断出，叶子的 dp 初值应为 $dp(u, 0) =0, dp(u, 1) =0, dp(u, 2) =2$（叶子一定被染色）

（如果觉得这种方式不严谨的话，其实也可以考虑在转移时专门处理叶子的贡献；不过简化后代码应该和这种方式是相同的）

## CODE

代码中的变量命名和题解可能有出入，具体见注释

```cpp
#include <cstdio>
#include <vector>
#define ll long long
using std::vector;

const int MAXN =2e5+50;
const int M =998244353;

/*------------------------------Map------------------------------*/

vector<int> E[MAXN];

/*------------------------------Dfs------------------------------*/

/*u 现在相连的染色儿子数为 0, >= 2, 1 ( 也可以定义为 ( 最终 ) 染色什么，但都有瑕疵 )*/
int f[MAXN], g[MAXN], h[MAXN];
int f2, g2, h2;
void dfs(int u){
	/*这里对叶子的状态缺省值设定，是由在父亲处的合并要求推断出的 : 只有 >= 2 才能确定被染色，叶子确定被染色*/
	/*可能还是不严谨，或可对叶子特殊定义状态*/
	if((int)E[u].size() == 0)
		g[u] =1;
	else
		f[u] =1;
	for(int v:E[u]){
		dfs(v);
		f2 =f[u], g2 =g[u], h2 =h[u];
		f[u] =1ll*f2*((ll)f[v]+g[v])%M;
		g[u] =(1ll*g2*((ll)f[v]+h[v]+2ll*g[v]/*因为既可以连也可不连*/)%M+1ll*h2*((ll)g[v]+h[v])%M)%M;
		h[u] =(1ll*f2*((ll)h[v]+g[v])%M+1ll*h2*((ll)f[v]+g[v])%M)%M;
	}
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int main(){
	int n =read();
	for(int i =2; i <= n; ++i){
		int pi =read();
		E[pi].push_back(i);
	}
	dfs(1);
	printf("%d", (f[1]+g[1])%M);
}
```

---

## 作者：Graphcity (赞：5)

一道转移较为复杂的树形 DP 题。

考察以 $i$ 为根时的子树状态：

- 点 $i$ 无颜色：所有的子结点要么无色，要么颜色互不相同
- 点 $i$ 有颜色，但暂时还不合法：只有一个子结点跟它颜色相同，其它点要么无色，要么互不相同，且与 $i$ 点颜色不同。**这种情况需要和另外一棵子树合并才能达成合法状态。**
- 点 $i$ 有颜色，且已经合法：至少两个子结点跟它颜色相同，其它点要么无色，要么互不相同，且与 $i$ 点颜色不同。

对着状态设 DP 数组：我们把三种状态分别称为 $f_{i,0},g_i,f_{i,1}$。由于 $g$ 为暂时的不合法状态，所以答案为 $f_{1,0}+f_{1,1}$。

首先考虑叶子结点，它只能够被染色，$f_{i,1}=1$。

接着考虑其它结点。设它为 $x$，需要和子结点 $y$ 合并答案，考虑如下决策：

- 初始情况，根结点无色，$f_{x,0}=1$。
- $x$ 无色时子树 $y$ 要么无色，要么跟其它子结点颜色都不同：$f_{x,0}\gets f_{x,0}\times (f_{y,0}+f_{y,1})$。
- 新接入一个有色结点，由无色状态转变成暂时不合法状态：$g_x\gets g_x+f_{x,0}\times (f_{y,1}+g_y)$。
- 暂时不合法时，新接入一个不影响状态的点：$g_x\gets g_x\times (f_{y,0}+f_{y,1})$。
- 合法时，新接入一个不影响状态的点：$f_{x,1}\gets f_{x,1}\times (f_{y,0}+f_{y,1})$。
- 合法时，新接入一个与根结点颜色相同的点：$f_{x,1}\gets f_{x,1}\times (f_{y,1}+g_y)$。
- 暂时不合法的状态拼接一个有色结点，成为合法状态：$f_{x,1}\gets f_{x,1}+g_x\times (g_y+f_{y,1})$。

整理如下：
$$
\begin{cases}
f_{x,0}&\gets f_{x,0}\times (f_{y,0}+f_{y,1})\\
g_x &\gets g_x\times (f_{y,0}+f_{y,1})+f_{x,0}\times(f_{y,1}+g_y)\\
f_{x,1} &\gets f_{x,1}\times(f_{y,0}+g_y+2f_{y,1})+g_x\times(g_{y}+f_{y,1})
\end{cases}
$$
注意转移顺序和取模问题。时间复杂度 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5,Mod=998244353;

inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch<'0' || ch>'9')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' && ch<='9')
    {
        x=x*10+ch-'0';
        ch=getchar();
    }
    return x*f;
}

int n,ans,fa[Maxn+5],f[Maxn+5][2],g[Maxn+5];
vector<int> v[Maxn+5];

inline void dfs(int x,int fa)
{
    if(v[x].empty()) {f[x][1]=1; return;}
    f[x][0]=1;
    for(auto y:v[x]) dfs(y,x);
    for(auto y:v[x])
    {
        f[x][1]=(1ll*f[x][1]*(f[y][0]+(f[y][1]*2%Mod+g[y])%Mod)%Mod+1ll*g[x]*(g[y]+f[y][1])%Mod)%Mod;
        g[x]=(1ll*g[x]*(f[y][0]+f[y][1])%Mod+1ll*f[x][0]*(f[y][1]+g[y])%Mod)%Mod;
        f[x][0]=1ll*f[x][0]*(f[y][0]+f[y][1])%Mod;
    }
}

int main()
{
    n=read();
    For(i,2,n) v[fa[i]=read()].push_back(i);
    dfs(1,0);
    ans=(f[1][0]+f[1][1])%Mod;
    printf("%d\n",ans);
    return 0;
}
```



---

## 作者：Lgx_Q (赞：3)

[orz](https://www.luogu.com.cn/problem/CF1146F)

题意：给叶子结点划分若干个集合，使得每个结点集合的最小连通子图互补相交，有多少种划分方案。

#### 这里给出一种更简便的DP方法

类似于样例的图解，考虑根结点是否染上颜色。

如果不染上，说明根不属于任何一个集合的最小连通子图，根的儿子子树各自划分为相同的子问题。

如果染上，说明**根的儿子中，至少有$2$个子树包含的叶子在同一集合**。比如根是 $1$，他的儿子是 $2,3$，$\operatorname{subtree}(2)$ 中的一些叶子和 $\operatorname{subtree}(3)$ 中的一些叶子在同一集合，结点 $1$ 才能被染色。

考虑 $1$ 的儿子，假设是 $2$，考虑子树 $2$ 的答案。

如果 $1$ 不染色，那么子树 $2$ 的计算与 $1$ 相同。

如果 $1$ 染色，那么**子树 $2$ 至少有一个颜色“抬”到了结点 $2$**。

设树有 $5$ 个点，边为 $1-2,1-3,2-4,2-5$。

如果 $4$ 和 $5$ 在同一集合，那么 $1$ 就要染色。如果 $1$ 染色，那么 $2$ 也要染色。正是 $2$ 和 $3$ 分别至少有一个颜色“抬”到了 $2,3$ 自己本身，这两个颜色才能在 $1$ 合并（即：$4,5$ 合并在同一集合），此时 $1$ 才能染色。

所以，我们不难设状态：

$f_{u,0}$ 表示只考虑子树 $u$ 的答案。

$f_{u,1}$ 表示至少有一个颜色“抬”到了 $u$（为了给父亲合并）。

不妨设 $a$ 表示没有颜色在 $u$ 合并的计数，$b$ 表示只有 $1$ 个颜色到达 $u$ 的计数，$c$ 表示至少 $2$ 个颜色在 $u$ 合并的计数。

显然，$f_{u,0}=a+c,f_{u,1}=b+c$。

而 $a,b,c$ 的计算也很简单。

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll maxn=4e5+10,mod=998244353;
ll n,p,f[maxn][2];
vector<ll>vec[maxn];
void dfs(ll u)
{
	if(vec[u].empty())
	{
		f[u][0]=f[u][1]=1;
		return;
	}
	ll a=1,b=0,c=0;
	for(ll i=0;i<vec[u].size();i++)
	{
		ll v=vec[u][i];
		dfs(v);
		c=(c*(f[v][0]+f[v][1])+b*f[v][1])%mod;
		b=(b*f[v][0]+a*f[v][1])%mod;
		a=a*f[v][0]%mod;
	}
	f[u][0]=(a+c)%mod;
	f[u][1]=(b+c)%mod;
}
int main()
{
	scanf("%lld",&n);
	for(ll i=2;i<=n;i++)
	{
		scanf("%lld",&p);
		vec[p].push_back(i);
	}
	dfs(1);
	printf("%lld",f[1][0]);
	return 0;
}
```

---

## 作者：JiaY19 (赞：2)

一道优秀的树形 $\text{dp}$ 题目。

#### 题意

首先简化一下题意。

求的是一颗有根树的连通块划分方案。

#### 思路

观察题目，由于要统计方案，所以很容易确定是树形 $\text{dp}$ 题目。

但树形 $\text{dp}$ 的式子还是值得思考一下的。

我们可以设 $f_{x,0}$ 表示与父亲相连的方案数，$f_{x,1}$ 表示不与父亲相连的方案数。

这样还是无法快速转移。

我们可以再设 $g_{x,0}$ 表示与 $0$ 个儿子相连。

$g_{x,1}$ 表示与 $1$ 个儿子相连。

$g_{x,2}$ 表示与 $2$ 个儿子相连。

我们会发现，没有与儿子相连的点，必然不会在连通块内，所以必须不与父亲相连。

而只与一个儿子相连的点那么必然要与父亲相连，因为下面的叶子节点肯定会对应其他子树中的一个叶子节点。

而有两个儿子以上的点则可以随意。

所以：

$$f_{x,0}=(g_{x,0}+g_{x,2})$$

$$f_{x,1}=(g_{x,1}+g_{x,2})$$

此时，$\text{dp}$ 就能进行转移了。

复杂度：$O(n)$

#### Code

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn = 200010;
const int mod  = 998244353;

int n , f[maxn][2] , g[3];

/*
f[i][1] 与父亲相连 
f[i][0] 不与父亲相连。
g[0] 合并0个儿子 g[1] 合并1个儿子 g[2] 合并2个儿子
*/

vector<int> son[maxn];

inline int read()
{
    int asd = 0 , qwe = 1; char zxc;
    while(!isdigit(zxc = getchar())) if(zxc == '-') qwe = -1;
    while(isdigit(zxc)) asd = asd * 10 + zxc - '0' , zxc = getchar();
    return asd * qwe;
}

signed main()
{
    n = read() ;
    for(int i = 2;i <= n;i++) son[read()].push_back(i);
	for(int i = n;i >= 1;i--)
	{
		if(son[i].empty()) f[i][1] = f[i][0] = 1;
		else
		{
			int g0 = 1 , g1 = 0 , g2 = 0;
			for(auto j : son[i])
				g[0] = g0 * f[j][0],
				g[1] = g0 * f[j][1] + g1 * f[j][0],
				g[2] = g1 * f[j][1] + g2 * f[j][0] + g2 * f[j][1],
				g[0] %= mod , g[1] %= mod , g[2] %= mod,
				g0 = g[0] , g1 = g[1] , g2 = g[2];
			f[i][0] = (g[0] + g[2]) % mod , f[i][1] = (g[1] + g[2]) % mod;
		}
	}
	cout << f[1][0];
    return 0;
}


```

---

## 作者：λᴉʍ (赞：2)

有一个$1$为根的有根树，设$L$是一个叶子节点的集合，$f(L)$就是这些集合的虚树。

你要给叶子分成若干个集合，使得任意$f(x)$和$f(y)$（$x,y$都是你分出来的集合），$f(x)\cap f(y)=\emptyset$。求方案数。

定义$x,y$相连表示，最终存在一个$f(L)$使得$x,y\in f(L)$。

设$f[x][0]$表示$x$最终不与父亲相连的方案数，$f[x][1]$表示$x$最终与父亲相连的方案数。

然后还要将$x$与一些儿子合并。

如果合并了$0$个儿子，那么$x$最终不在任何一个集合，当然不能和父亲相连；

如果合并了$1$个儿子，那么一定在其他子树还有相同集合的，也就是必须和父亲相连；

如果合并了$\geq 2$个儿子，可以任意决定是否与父亲相连。

直接dp就好了。

https://codeforces.com/contest/1146/submission/53121149


---

## 作者：Purslane (赞：1)

# Solution

转移很复杂吗……

考虑每个节点有三种状态：

1. 这个点不被任何一个 $f(S)$ 包含；
2. 这个点被某一个 $f(S)$ 包含，**但是 $f(S)$ 可以完全在这个点的子树中，也可以不完全在**；
3. 这个点被某一个 $f(S)$ 包含，必须和子树外的某个联通块合并。

分别用 $dp_{u,1,2,3}$ 来表示。

对于 $u$ 的儿子 $v$ 来说：

1. 如果 $v$ 的状态是 $1$，那么 $u$ 和 $v$ 必定不被同一个 $f$ 覆盖；
2. 如果 $v$ 的状态是 $2$，可以选择和 $u$ 不被同一个 $f$ 覆盖，也可以选择被同一个 $f$ 覆盖；
3. 如果 $v$ 的状态是 $3$，则必须和 $u$ 被同一个 $f$ 覆盖。
4. 特别的，如果 $u$ **和且只和一个 $v$ 被同一个 $f$ 覆盖**，则 $u$ 的状态是 $3$；否则，如果 $u$ 和至少一个 $v$ 被同一个 $f$ 覆盖，则 $u$ 的状态是 $2$；否则，$u$ 的状态是 $1$。

首先考虑计算 $dp_{u,1}$，显然是：

$$
\prod_{v} (dp_{v,1} + dp_{v,2})
$$

再考虑计算 $dp_{u,3}$，显然是：

$$
\sum_v (dp_{v,2} + dp_{v,3}) \prod_{w \neq v} (dp_{w,1}+dp_{w,2})
$$

但是 $dp_{u,2}$ 不是很好算，但是我们知道

$$
dp_{u,1}+dp_{u,2}+dp_{u,3} = \prod_v (dp_{v,1} + 2dp_{v,2} + dp_{v,3})
$$

就可以做到 $O(n)$。

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=200000+10,MOD=998244353;
int n,dp[MAXN][3],tmp[MAXN];
vector<int> G[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n;
	ffor(i,2,n) {int fa;cin>>fa,G[fa].push_back(i);}
	roff(u,n,1) if(G[u].size()==0) dp[u][1]=1;
	else {
		int mul=1;
		for(auto v:G[u]) tmp[v]=mul,mul=(dp[v][0]+dp[v][1])%MOD*mul%MOD;
		mul=1,reverse(G[u].begin(),G[u].end());
		for(auto v:G[u]) tmp[v]=tmp[v]*mul%MOD,mul=(dp[v][0]+dp[v][1])%MOD*mul%MOD;
		mul=1;
		for(auto v:G[u]) dp[u][2]=(dp[u][2]+(dp[v][1]+dp[v][2])%MOD*tmp[v])%MOD,mul=(dp[v][0]+dp[v][1])%MOD*mul%MOD;
		dp[u][0]=mul,mul=1;
		for(auto v:G[u]) mul=(dp[v][0]+dp[v][1]*2+dp[v][2])%MOD*mul%MOD;
		dp[u][1]=(mul-dp[u][0]-dp[u][2])%MOD;
	}
	cout<<((dp[1][0]+dp[1][1])%MOD+MOD)%MOD;
	return 0;
}
```

---

## 作者：Rem_CandleFire (赞：1)

**题目大意**

一棵树，给其叶子结点染色，要求每种颜色的节点构成的最小连通子图不交。

**分析与做法**

子节点的颜色直接影响到父节点的颜色，所以先分为某个父节点 $u$ 有无颜色两种情况。而如果节点 $u$ 有颜色，但此时可能为不合法的状态（譬如有且只有一个子节点 $v$ 与 $u$ 同色）。所以我们作如下定义：

- $f_{u,0}$：点 $u$ 无颜色时方案数，此时**其所有子节点颜色均不相同**。
- $f_{u,1}$：点 $u$ 有颜色时的方案数，此时**有两个及以上的子节点颜色相同**。
- $d_u$：点 $u$ 有颜色，但是**有且仅有一个子节点颜色与其相同**的方案数。

不妨设对于 $u$ 的一个任意子节点为 $v$。考虑转移，不妨按照三个数组分类考虑。

对于 $f_{u,0}$，显然只能再接入合法点才能保持无色，于是有 $f_{u,0}=f_{u,0}\times(f_{v,0}+f_{v,1})$。

对于 $d_u$，节点 $u$ 可以跟子节点 $v$ 颜色相同（这个时候也要考虑当 $v$ 不染色时随便选一个颜色并上去），即 $d_u=d_u+f_{u,0}\times(f_{v,1}+d_v)$。

也可以不管节点 $v$，自己维持原样，此时要保证 $v$ 子树合法，即 $d_u=d_u\times(f_{v,0}+f_{
v,1})$。

对于 $f_{u,1}$，继续分讨。首先算上不管节点 $v$ 的情况，同上 $f_{u,1}\times(f_{v,0}+f_{v,1})$。

然后考虑如何保证 $u$ 子树合法：要么节点 $v$ 的颜色和节点 $u$ 相同，即 $f_{u,1}=f_{u,1}\times(f_{v,1}+d_v)$，要么通过节点 $v$ 使节点 $u$ 从不合法转变成了合法状况，即 $f_{u,1}=f_{u,1}+d_u\times(d_v+f_{v,1})$。

那么，到此我们所有的情况讨论都结束了，总结一下。

- $f_{u,1}=f_{u,1}\times(f_{v,0}+2\times f_{v,1}+d_v)+d_u\times(d_v+f_{v,1})$
- $d_u=d_u\times(f_{v,0}+f_{v,1})+f_{u,0}\times(f_{v,1}+d_v)$
- $f_{u,0}=f_{u,0}\times(f_{v,0}+f_{v,1})$

注意到三者有相互调用的情况，所以在实现过程中要注意转移顺序。

[AC code](https://www.luogu.com.cn/paste/lz7dk726)

---

## 作者：derta (赞：1)

[CF1146F Leaf Partition](https://www.luogu.com.cn/problem/CF1146F)

我的方法不敢说是最简单的，但是 DP 数组数量是洛谷题解区最少的。

为了方便叙述，假设每个叶子集合与其最小联通子图上的点均被染上同一种颜色，如样例说明所示。

十分自然地，设 $f_i$ 为以 $i$ 为根的子树的划分数。转移时可以分为两种情况（本质上是相同的，但第二种目前不能直接计算）：

- $i$ 的孩子都有颜色。此时从孩子里揪出若干个，把与它们（揪出的孩子）同色的点染成相同的颜色，并将 $i$ 染成这个颜色（这样才是连通的）。当然，不改变孩子颜色的情况也计入在内，此时 $i$ 无色。注意不能只揪出来一个孩子，否则不满足最小子图。
- $i$ 的某些孩子无色。不妨设其中的一个为 $j$。可以发现，只要一个在子树 $j$ 中的**有色**点 $k$ 满足路径 $k \to j$ 上的点（$k$ 除外）全部无色，就可以用与上文相同的方法把 $k$ 揪出来再染色。当然，每棵子树 $j$ 中只能揪出来一个 $k$。另外，当 $j$ 有色时，$k$ 必然为 $j$，恰好包含第一种情况。

经过这样的思考，我们可以设 $g_i$ 为子树 $i$ **所有情况中**满足上述要求的 $k$ 的个数。

现在可以考虑转移了。如果揪出来了孩子 $j$，它会贡献 $g_j$ 种情况；反之，则会贡献 $f_j$ 种情况。所以随便揪的式子即为：

$$\sum_{S \subset \mathrm{son}(i)}\left(\prod_{j \in S}f_j\right)\left(\prod_{j\not\in S,j\in \mathrm{son}(i)}g_j\right)$$

化简得：

$$\prod_{j \in \mathrm{son}(i)}(f_j+g_j)$$

然后减去只揪一个的情况，得出转移方程：

$$f_{i}=\left(\prod_{j \in \mathrm{son}(i)}(f_j+g_j)\right)-\sum_{j\in \mathrm{son}(i)}\left(g_j \cdot\prod_{k\in \mathrm{son}(i)\setminus\{j\}}f_k\right)$$

之后转移 $g_i$，分类讨论：

- $i$ 被染色。每种情况贡献为 $1$，总贡献为：

  $$f_i-\prod_{j \in \mathrm{son}(i)}f_j$$
- $i$ 未被染色。考虑每一个孩子的贡献。孩子 $j$ 被计算

  $$\prod_{k\in \mathrm{son}(i)\setminus\{j\}}f_k$$
  
  次。累加之，即可得出：
  
  $$\sum_{j\in \mathrm{son}(i)}g_j\prod_{k\in \mathrm{son}(i)\setminus\{j\}}f_k$$
  
综上所述，$g_i$ 有转移方程：

$$g_i=\left(\prod_{j \in \mathrm{son}(i)}(f_j+g_j)\right)-\prod_{j \in \mathrm{son}(i)}f_j$$

时间复杂度 $\Theta(n)$。

注意在计算

$$g_j \cdot\prod_{k\in \mathrm{son}(i)\setminus\{j\}}f_k$$

时，由于逆元可能不存在，所以更简便的方法是转化为 
$$g_j\textit{pre}_{j-1}\textit{suf}_{j+1}$$

其中 $\textit{pre},\textit{suf}$ 分别表示 $f$ 的前缀积与后缀积。

代码（可读性极差）：

```cpp
#include <cstdio>
#include <vector>
const int MAXN = 200005, MOD = 998244353;
int n, f[MAXN], g[MAXN], pref[MAXN], suff[MAXN];
//f[i]:以i为根方案数，g[i]:以i为根无障碍染色节点数 
std::vector<int> G[MAXN];

inline int pm(int x)
{ return x < 0 ? x + MOD : x; }

inline int mm(int x)
{ return x >= MOD ? x - MOD : x; }

void DP(int x) {
	if(G[x].size() == 0) {
		f[x] = g[x] = 1;
		return ;
	}
	if(G[x].size() == 1) { //特判，因为后面有对首尾的特殊处理，而size=1时首尾相同，导致重复计算。
		DP(G[x][0]);
		f[x] = f[G[x][0]], g[x] = g[G[x][0]];
		return ;
	}
	f[x] = 1;
	for(int i = 0; i < G[x].size(); ++i) {
		int v = G[x][i];
		DP(v);
		f[x] = 1LL*f[x]*(f[v] + g[v])%MOD;
	}
	pref[0] = f[G[x].front()], suff[(int)G[x].size() - 1] = f[G[x].back()];
	for(int i = 1; i < G[x].size(); ++i)
		pref[i] = 1LL*pref[i - 1]*f[G[x][i]]%MOD;
	for(int i = (int)G[x].size() - 2; i >= 0; --i)
		suff[i] = 1LL*suff[i + 1]*f[G[x][i]]%MOD;
	g[x] = pm(f[x] - suff[0]); //这和转移方程是一样的
	f[x] = pm(pm(f[x] - 1LL*suff[1]*g[G[x].front()]%MOD) - 1LL*pref[(int)G[x].size() - 2]*g[G[x].back()]%MOD); //记得之前size=1的特判吗
	for(int i = 1; i < (int)G[x].size() - 1; ++i)
		f[x] = pm(f[x] - 1LL*pref[i - 1]*suff[i + 1]%MOD*g[G[x][i]]%MOD);
}

int main() {
	scanf("%d", &n);
	for(int i = 2; i <= n; ++i) {
		int p;
		scanf("%d", &p);
		G[p].push_back(i);
	}
	DP(1);
	printf("%d", f[1]);
	return 0;
}
```

---

## 作者：_Cheems (赞：0)

尝试找性质，无果。

尝试直接树形 $\rm dp$，那么应当是枚举 $u$ 是否作为 $\rm lca$ 被选取。

计算不钦定 $u$ 的方案是容易的，那么钦定呢？我们需要枚举哪些子树 $v$ 向上延伸，剩下的子树随意取即可。

注意一下，假如只考虑 $v$ 子树，记 $v$ 被选取的方案为 $cnt$。那么对其父亲 $u$ 而言，这个 $cnt$ 其实有两种含义：$v$ 向上延伸与 $u$ 相连的方案数、$v$ 不向上延伸自己做主的方案数。

（其实是在打代码时发现的问题。）

于是树形 $\rm dp$ 的状态，应该要根据其是否与父亲相连而决定。不难得出定义 $f_{u,0/1}$ 表示 $u$ 子树，$u$ 是否向上延伸（$u$ 父亲是否被选取）的方案数。

然后对 $u$ 处理出 $g_{u,0/1/2}$，表示有 $0/1/\ge2$ 个子树向上延伸相连的方案数。

那么转移就是：$f_{u,0}=g_{u,0}+g_{u,2}$，$f_{u,1}=g_{u,1}+g_{u,2}$。

复杂度 $O(n)$。
#### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;

#define int long long
#define ADD(a, b) a = (a + (b)) % mod
const int N = 2e5 + 5, mod = 998244353;
int n, fa, f[N][2];
vector<int> to[N];

inline void dfs(int u, int fa){
	if(to[u].empty()) {f[u][0] = f[u][1] = 1; return ;}
	int g[5], _g[5]; memset(g, 0, sizeof g), g[0] = 1;
	for(auto v : to[u])
		if(v ^ fa){
			dfs(v, u);
			memcpy(_g, g, sizeof _g), memset(g, 0, sizeof g);
			for(int j = 2; ~j; --j) 
				ADD(g[min(2ll, j + 1)], _g[j] * f[v][1] % mod), ADD(g[j], _g[j] * f[v][0] % mod);
		}
	f[u][0] = (g[0] + g[2]) % mod;
	f[u][1] = (g[1] + g[2]) % mod;
}
signed main(){
	cin >> n;
	for(int i = 2; i <= n; ++i) scanf("%lld", &fa), to[fa].push_back(i);
	dfs(1, 0);
	cout << f[1][0];
	return 0;
}
```

---

## 作者：L_zaa_L (赞：0)

一道非常不错的树形 dp 题。

我们需要记一个 $dp_{u,0/1/2}$，来表示这棵树某个状态的方案数，这三个状态分别是：

1. $dp_{u,0}$ 表示这个节点没有被选的方案数。
2. $dp_{u,1}$ 表示这个节点被选了，但是所选部分不满足最小连通子图的性质，也就是不合法的方案数（这种情况需要和其他子树合并也能合法，所以需要统计）。
3. $dp_{u,2}$ 表示这个节点选了，也是合法的的方案数。

然后考虑利用这些进行转移。

如果当前节点是叶子节点，那么肯定得选：$dp_{u,2}=1$。

对于所有非叶子节点，都有不选的方案：$dp_{u,0}=1$。

对于合法的情况我们需要考虑一下：

首先合法的情况，首先可以在已经合法的方案中，接入一个与当前无关，可以直接形成了一个集合的：$(dp_{v,0}+dp_{v.2})\times dp_{u,2}$，这样最后还是合法的。

也可以在原先合法的接上一个子树之后可以使得这个合法的：$(dp_{v,1}+dp_{v,2})\times dp_{u,2}$。

同时也可以从一个不合法的加上一个合法的使得它合法：$(dp_{v,1}+dp_{v,2})\times dp_{u,1}$。

所以对于合法的情况我们可以得到：$dp_{u,2}=(dp_{v,0}+dp_{v.2})\times dp_{u,2}+(dp_{v,1}+dp_{v,2})\times dp_{u,2}+(dp_{v,1}+dp_{v,2})\times dp_{u,1}$

然后再考虑不合法的，首先可以加上和他无关的，这样还是原来的样子：$(dp_{v,0}+dp_{v,2})\times dp_{u,1}$。

然后还可以靠没有染色的进行染色只接一棵子树得到新的不合法：$(dp_{v,1}+dp_{v,2})\times dp_{u,0}$。


最后不染色的随便添几个合法的就行了：$dp_{u,0}\times (dp_{v,0}+dp_{v,2})$。

然后最后的方程是：

$$\begin{cases}dp_{u,2}=(dp_{v,0}+dp_{v.2})\times dp_{u,2}+(dp_{v,1}+dp_{v,2})\times dp_{u,2}+(dp_{v,1}+dp_{v,2})\times dp_{u,1}\\dp_{u,1}=(dp_{u,1}\times(dp_{v,0}+dp_{v,2})+dp_{u,0}\times(dp_{v,1}+dp_{v,2}))\\dp_{u,0}=dp_{u,0}\times(dp_{v,0}+dp_{v,2})\end{cases}$$

顺序不能错，因为有些调用了其他的，而一棵子树不能重复计算。

---

## 作者：封禁用户 (赞：0)

### 题目传送门

[洛谷](https://www.luogu.com.cn/problem/CF1146F)

[CF](https://codeforces.com/problemset/problem/1146/F)

### 题意

在一颗树上，把每一个叶子节点进行染色，要求各个颜色的最小联通子树的集合不相交的方案数。

### 分析

当一个节点与其某个子节点的颜色相同时，认为这条边“被染色”。

显然，一条边都没有被染色，那么到父亲节点一定也没有染色。如果恰好有一条边被染色，如果有父亲节点其到父亲节点的边一定要染色。如果大于等于两条边被染色，那么到父亲节点的边染不染色均可。

定义状态 $dp_{u,0/1/2}$ 表示 $u$ 和子节点中的 $0/1/ \ge 2$ 条边被染色的方案数。

令 $v \in son(u)$，$t0 = dp_{v,2} + dp_{v,0}$，$t1 = dp_{v,2} + dp_{v,1}$。

其中 $t_0$ 表示不染色边 $(u,v)$ 的方案数，$t_1$ 表示染边 $(u,v)$ 的方案数。

对于非叶子节点，定义初值 $dp_{u,0} = 1$，$dp_{u,1} = dp_{u,2} = 0$。


状态转移方程：

$$
dp_{u',2} \leftarrow dp_{u,1} \times t_1 + dp_{u,2} \times (t_0 + t_1)
$$
$$
dp_{u',1} \leftarrow dp_{u,1} \times t_0 + dp_{u,0} \times t_1
$$
$$
dp_{u',0} \leftarrow dp_{u,0} \times t_0
$$
对于叶子结点，到父亲的边既可以染色，也可以不染色，符合 $dp_{u,2}$ 的意义，故定义 $dp_{u,2} = 1$，$dp_{u,0} = dp_{u,1} = 0$。

答案就是 $dp_{1,0} + dp_{1,2}$。

### 代码

```cpp
 #include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	static char c,p;
	c = getchar(),p = 1,x = 0;
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -1;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		x = (x<<3)+(x<<1)+(c^48);
		c = getchar();
	}
	x *= p;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10^48);
}
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define ull unsigned long long
#define ll long long
#define pii pair<int,int>
#define fi first
#define se second
#define N 200010
constexpr int mod = 998244353;
inline void add(int &x,int y) {(x += y) >= mod&&(x -= mod);}
int head[N],nxt[N],to[N],cnt = 0;
inline void addedge(int u,int v)
{
	nxt[++cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
}
int n,dp[N][3],t0,t1;
void dfs(int u)
{
	if(!head[u])
	{
		dp[u][2] = 1;
		return;
	}
	dp[u][0] = 1;
	for(register int i = head[u];i;i = nxt[i])
	{
		int v = to[i];
		dfs(v);
		t0 = t1 = dp[v][2];
		add(t0,dp[v][0]);
		add(t1,dp[v][1]);
		dp[u][2] = (1ll * dp[u][1] * t1 + 1ll * dp[u][2] * (t0 + t1)) % mod;
		dp[u][1] = (1ll * dp[u][1] * t0 + 1ll * dp[u][0] * t1) % mod; 
		dp[u][0] = 1ll * dp[u][0] * t0 % mod;
	}
}
int main()
{
	read(n);
	F(i,2,n)
	{
		int x;
		read(x);
		addedge(x,i);
	}
	dfs(1);
	write((dp[1][0] + dp[1][2]) % mod);
	return 0;
}

```

---

## 作者：Luciylove (赞：0)

这个题还是蛮有趣的，其实弄清楚这个染色的方案，这个题还是简单的。

本质上只是对于考虑对于连通块染色，但是带有一些限制。

所以我们考虑在 LCA 上**拼接**若干条根到叶子的路径。

那我们就可以依据这一想法来设计状态。

第一是这个点没有染色，那我们记这一状态为 $h$。

第二是这个点连接着一条到**一个**叶子的链，值得注意，这种情况不符合最小联通图的定义，所以不可以作为一个根来算答案，要一直连到祖先上，记为 $f$。

第三是拼接了至少两条同色的到叶子的链，记为 $g$。

考虑依次插入 $v$ 这个子节点的答案，那么转移就很明显了：

首先是如果不染，那么这个点可以随便算，但是注意不能算 $f$ 这种不合法的答案。

$$h_u = \prod(h_v + g_v)$$

如果只染一条链，那么可以从无色染到有，也可以原本有色，不进行拼接。

$$f_u = f_u \times (g_v + h_v) + h_u \times (g_v + f_v)$$

如果是染了至少两条链，那就可由一个一条或者多条的连上来，或者随便算一下儿子。

$$g_u = g_u \times (f_v + 2 \times g_v + h_v) + f_u \times (g_v + f_v)$$

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = l; i <= r; i ++)
#define per(i, r, l) for (int i = r; i >= l; i --)
#define lc u << 1
#define rc u << 1 | 1
#define int long long
// g -> f -> h 
using namespace std;

const int N = 2e5 + 5, mod = 998244353;

vector <int> e[N];
int n, g[N], h[N], f[N];

void dp (int u) {
	if (! e[u].size()) { g[u] = 1; return ; }
	h[u] = 1;
	for (int v : e[u]) {
		dp(v);
		g[u] = g[u] * (f[v] + 2 * g[v] + h[v]) + f[u] * (g[v] + f[v]);
		f[u] = f[u] * (g[v] + h[v]) + h[u] * (g[v] + f[v]);
		h[u] = h[u] * (h[v] + g[v]);
		g[u] %= mod, f[u] %= mod, h[u] %= mod;
	}
}
signed main () {
	ios :: sync_with_stdio(0);
	cin >> n;
	for (int i = 2, fa; i <= n; i ++)
		cin >> fa, e[fa].push_back(i);
	dp(1), cout << (g[1] + h[1]) % mod;
	return 0;
}
```


---

