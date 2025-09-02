# Tree Cutting (Hard Version)

## 题目描述

给定一棵包含 $n$ 个顶点的无向树。

有些顶点被染成 $k$ 种颜色中的一种，有些顶点未染色。保证树中每种颜色至少有一个顶点。也可能没有未染色的顶点。

你需要选择恰好 $k-1$ 条边并将其从树中删除。此时树会分裂成 $k$ 个连通分量。我们称这样的边集为“优美子集”，如果删除这些边后，任意一个连通分量内的所有顶点要么未染色，要么都染成同一种颜色（即没有分量内包含不同颜色的顶点）。

问在给定的树中，有多少个“优美子集”？如果两个子集存在某条边只在其中一个子集中出现，则认为它们不同。

答案可能很大，请输出答案对 $998244353$ 取模后的结果。

## 说明/提示

以下是第一个样例的树结构：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F2/ab0319e6d1b3fdf0a12318f77b159c6dc359f231.png)

唯一的优美子集是边 $(2, 4)$。删除它后，树被分成 $\{4\}$ 和 $\{1, 2, 3, 5\}$ 两个连通分量。第一个分量只包含颜色 $1$ 的顶点，第二个分量只包含颜色 $2$ 及未染色的顶点。

以下是第二个样例的树结构：

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1118F2/3ddc7b8d9c599a1a5a2a55a53a6d0d25bb324ac3.png)

优美子集为 $\{(1, 3), (4, 7)\}$、$\{(1, 3), (7, 2)\}$、$\{(3, 6), (4, 7)\}$ 和 $\{(3, 6), (7, 2)\}$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
5 2
2 0 0 1 2
1 2
2 3
2 4
2 5
```

### 输出

```
1
```

## 样例 #2

### 输入

```
7 3
0 1 0 2 2 3 0
1 3
1 4
1 5
2 7
3 6
4 7
```

### 输出

```
4
```

# 题解

## 作者：zaozao_zmx (赞：13)

一开始没想到把同颜色的点缩成一个，那就直接 dp 吧。

我们首先定义 $dp(i,0/1/2)$：

- $dp(i,0)$ 表示 $i$ 结点和其父亲结点的连边被断开且子树内断边合法的方案数；
- $dp(i,1)$ 表示 $i$ 结点和其父亲连边未断开且子树内断边合法的方案数；
- $dp(i,2)$ 表示 $i$ 结点和其父亲连边未断开且子树内断边不合法（即有一种颜色出现在子树内，但未被子树完全包括，要向外延伸）的方案数。

我们再强制 $0$ 结点全部聚成一团而 $0$ 结点之下合法的情况归为 $dp(i,0)$，如下图：

![](https://cdn.luogu.com.cn/upload/image_hosting/vn75q29e.png)

其中点上的标号为点的颜色，红色为断边的地方。

再定义，$se$ 表示当前节点的颜色，$col(i)$ 表示当前节点未包含的那一个颜色，$col1(i)$ 表示被当前节点恰好完全覆盖的那一个颜色，$mul = \prod\limits_{v \in son(i)}{dp(v,0)}$。

接着我们来推式子：

1. $se = 0$
- $dp(i,0) = \sum\limits_{v \in son(i)}{(\dfrac{dp(v,1)}{dp(v,0)}mul)} + mul + \prod\limits_{v \in son(i),col(v)=col1(i)}{(\dfrac{dp(v,2)}{dp(v,0)})} \times mul$；
- $dp(i,1) = \sum\limits_{v \in son(i)}{(\dfrac{dp(v,1)}{dp(v,0)}mul)} + \prod\limits_{v \in son(i),col(v)=col1(i)}{(\dfrac{dp(v,2)}{dp(v,0)})} \times mul$；
- $dp(i,2) = \prod\limits_{v \in son(i),col(v)=col(i)}{(\dfrac{dp(v,2)}{dp(v,0)})} \times mul$。

2. $se \ne 0$
- $dp(i,0) = \prod\limits_{v \in son(i),col(v)=col1(i)}{(\dfrac{dp(v,2)}{dp(v,0)})} \times mul$；
- $dp(i,1) = \prod\limits_{v \in son(i),col(v)=col1(i)}{(\dfrac{dp(v,2)}{dp(v,0)})} \times mul$；
- $dp(i,2) = \prod\limits_{v \in son(i),col(v)=col(i)}{(\dfrac{dp(v,2)}{dp(v,0)})} \times mul$。


下面是 $dp$ 转移的解释：

首先，我们有一个性质：如果一个点的 $cnt(col) + cnt(col1) > 1$，那么说明这个点的父亲边需要被两种颜色经过，不可能，显然答案就是 $0$。

这个性质表明了，一个点最多只会有一个 $col$ 或 $col1$。

**1. $se = 0$**
- $dp(i,0)$，分为三种类型：
	- 第一种是儿子中一个点占用当前点的 $0$，其余儿子和当前点无连边；
	- 第二种是所有儿子均与当前点无连边；
	- 第三种是对于一个当前点恰好完全覆盖的颜色，可以将儿子中与当前点有连边且颜色都等于 $col1$ 的点（当 $col1 \ne 0$）合并成一个联通块，其余儿子和当前点无连边。
- $dp(i,1)$，即向父亲多连了一条边（注意其中点若全为 $0$ 则归为第一种情况），就是 $dp(i,0)$ 减去其中第二种即所有儿子均与当前点无连边的情况；
- $dp(i,2)$，此时当前点有未包含的颜色，那么就是儿子中与当前点有连边且颜色都等于 $col$ 的点（当 $col \ne 0$）合并成一个联通块，并向上连边，其余儿子和当前点无连边。

2. $se \ne 0$
- $dp(i,0)$，将儿子中与当前点有连边且颜色都等于 $col1$ 的点合并成一个联通块，其余儿子和当前点无连边（此时若有 $col1$，则 $col1 = se$）；
- $dp(i,1)$，只是往上多连了一条边，和 $dp(i,0)$ 一样；
- $dp(i,2)$，将儿子中与当前点有连边且颜色都等于 $col$ 的点合并成一个联通块，并向上连边，其余儿子和当前点无连边（此时若有 $col$，则 $col = se$）。

这样我们就转移完了，接下来讲一些需要注意的点：
- 注意 $dp(i,0)$ 可能会等于 $0$，不能直接除；
- 对于子树中一个颜色都没有的点，我们需要直接跳过，不然可能会造成错误计算；
- 对于叶子结点，若 $se = 0$ 则会被直接跳过，若 $se \ne 0$，若当前颜色一共只有 $1$ 个，$dp(i,0)=1$，$dp(i,1)=1$，$dp(i,2)=0$，否则，$dp(i,0)=0$，$dp(i,1)=0$，$dp(i,2)=1$；
- 对于根节点，由于不能有纯 $0$ 的联通块，因此答案应该为 $(dp(rt,0) - mul)$；
- 求解 $col$ 和 $col1$，我们考虑覆盖出其两两之间点及路径构成的整个联通块，并在其中判 $0$，对于覆盖求颜色的联通块可以用类似于虚树的方法，将所有点按照 dfs 序排序，然后用栈维护一个 dfs 序递增的序列，每次按照单调栈的思路更新即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
long long a,b,d[300001],q,w,o,h[300001],dp[300001][3],an,mod=998244353,col[300001],col1[300001];//col 未包含，col1刚好包含
long long fa[300001][21],de[300001],lg[300001],dfn[300001],cnt,su[300005],pr[300005],g[300005],st[300005],cn,v[300001]; 
struct p
{
	long long q,w;
}l[600001];
void add(long long qq,long long ww)
{
	o++;
	l[o].q=ww;
	l[o].w=h[qq];
	h[qq]=o;
}
long long pow_(long long qq,long long ww)
{
	long long ee=1;
	while(ww)
	{
		if(ww&1)
		{
			ee*=qq;
			ee%=mod;
		}
		qq*=qq;
		qq%=mod;
		ww>>=1;
	}
	return ee%mod;
}
void dfs(long long qq,long long ww)
{
	long long mul=1,cnn=0;
	su[0]=1;
	for(int i=h[qq];i;i=l[i].w)
	{
		if(l[i].q!=ww)
		{
			if(v[l[i].q]==0) continue;
			dfs(l[i].q,qq);
			mul*=dp[l[i].q][0];
			mul%=mod;
		}
	}
	for(int i=h[qq];i;i=l[i].w)
	{
		if(l[i].q!=ww)
		{
			if(v[l[i].q]==0) continue;
			cnn++;
			su[cnn]=su[cnn-1]*dp[l[i].q][0]%mod;
			g[cnn]=dp[l[i].q][0];
		}
	}
	pr[cnn+1]=1;
	for(int i=cnn;i>=1;i--)
	{
		pr[i]=pr[i+1]*g[i]%mod;
	}
	cnn=0;
	long long la=0;
	for(int i=h[qq];i;i=l[i].w)
	{
		if(l[i].q!=ww)
		{
			if(v[l[i].q]==0) continue;
			cnn++;
			if(d[qq]==0)
			{
				dp[qq][0]+=dp[l[i].q][1]%mod*su[cnn-1]%mod*pr[cnn+1]%mod;
				dp[qq][0]%=mod;
			}
		}
	}
	if(col1[qq])
	{
		long long tt=1,mu=1;
		for(int i=h[qq];i;i=l[i].w)
		{
			if(l[i].q!=ww)
			{
				if(v[l[i].q]==0) continue;
				if(col[l[i].q]==col1[qq])
				{
					tt*=dp[l[i].q][2];
					tt%=mod;
				}
				else
				{
					mu*=dp[l[i].q][0];
					mu%=mod;
				}
			}
		}
		tt*=mu;
		tt%=mod;
		dp[qq][0]+=tt;
		dp[qq][0]%=mod;
	}
	if(col[qq])
	{
		long long tt=1,mu=1;
		for(int i=h[qq];i;i=l[i].w)
		{
			if(l[i].q!=ww)
			{
				if(v[l[i].q]==0) continue;
				if(col[l[i].q]==col[qq])
				{
					tt*=dp[l[i].q][2]%mod;
					tt%=mod;
				}
				else
				{
					mu*=dp[l[i].q][0];
					mu%=mod;
				}
			}
		}
		tt*=mu;
		tt%=mod;
		dp[qq][2]+=tt;
		dp[qq][2]%=mod;
	}
	dp[qq][1]=dp[qq][0];
	if(d[qq]==0)
	{
		dp[qq][0]+=mul;
		dp[qq][0]%=mod;
	}
	if(qq==1)
	{
		if(d[qq]!=0)
		{
			an=dp[qq][0];
		}
		else an=dp[qq][0]-mul;
		an%=mod;
		an+=mod;
		an%=mod;
	}
}
long long lca(long long qq,long long ww)
{
	if(de[qq]<de[ww]) swap(qq,ww);
	while(de[qq]>de[ww])
	{
		qq=fa[qq][lg[de[qq]-de[ww]]-1];
	}
	if(qq==ww) return qq;
	for(int i=20;i>=0;i--)
	{
		if(fa[qq][i]!=fa[ww][i])
		{
			qq=fa[qq][i];
			ww=fa[ww][i];
		}
	}
	return fa[qq][0];
}
void dfs1(long long qq,long long ww)
{
	dfn[qq]=++cnt;
	fa[qq][0]=ww;
	for(int i=1;i<=20;i++)
	{
		fa[qq][i]=fa[fa[qq][i-1]][i-1];
	}
	de[qq]=de[ww]+1;
	if(d[qq]!=0) v[qq]=1;
	for(int i=h[qq];i;i=l[i].w)
	{
		if(l[i].q!=ww)
		{
			dfs1(l[i].q,qq);
			v[qq]|=v[l[i].q];
		}
	}
}
vector<long long> qu[300001];
bool cmp(long long qq,long long ww)
{
	return dfn[qq]<dfn[ww];
}
int main()
{
	for(int i=1;i<=300000;i++)
	{
		lg[i]=lg[i-1]+((1<<lg[i-1])==i);
	}
	scanf("%lld",&a);
	b=2;
	scanf("%lld",&b);
	for(int i=1;i<=a;i++)
	{
		scanf("%lld",&d[i]);
		qu[d[i]].push_back(i);
	}
	for(int i=1;i<a;i++)
	{
		scanf("%lld%lld",&q,&w);
		add(q,w);
		add(w,q);
	}
	dfs1(1,0);
	for(int i=1;i<=b;i++)
	{
		sort(qu[i].begin(),qu[i].end(),cmp);
		cn=0;
		st[++cn]=qu[i][0];
		for(int j=1;j<qu[i].size();j++)
		{
			long long gg=lca(st[cn],qu[i][j]);
			if(gg!=st[cn])
			{
				while(dfn[gg]<dfn[st[cn-1]])
				{
					long long uu=st[cn];
					while(de[uu]>de[st[cn-1]])
					{
						if(col[uu]||col1[uu])
						{
							printf("0");
							return 0;
						}
						col[uu]=i;
						uu=fa[uu][0];
					}
					cn--;
				}
				if(dfn[gg]==dfn[st[cn-1]])
				{
					long long uu=st[cn];
					while(de[uu]>de[st[cn-1]])
					{
						if(col[uu]||col1[uu])
						{
							printf("0");
							return 0;
						}
						col[uu]=i;
						uu=fa[uu][0];
					}
					cn--;
				}
				else
				{
					long long uu=st[cn];
					while(de[uu]>de[gg])
					{
						if(col[uu]||col1[uu])
						{
							printf("0");
							return 0;
						}
						col[uu]=i;
						uu=fa[uu][0];
					}
					cn--;
					st[++cn]=gg;
				}
			}
			st[++cn]=qu[i][j];
		}
		long long tt=st[cn];
		while(de[tt]>de[st[1]])
		{
			if(col[tt]||col1[tt])
			{
				printf("0");
				return 0;
			}
			col[tt]=i;
			tt=fa[tt][0];
		}
		if(col[tt]||col1[tt])
		{
			printf("0");
			return 0;
		}
		col1[tt]=i;
	}
	dfs(1,0);
	printf("%lld",an);
	return 0;
}
```

---

## 作者：Erusel (赞：7)

个人认为这个题出的不错，但是有点二合一的感觉吧，想法还是比较自然的

---

反过来思考，对于每个点，我们设计两种状态，一种对于当前**划分颜色**已确定的方案数 $f[u][0]$ ,一种对于当前**划分颜色**未确定的方案数 $f[u][1]$

有一个显然的结论就是相同颜色的节点一定被划分在同一个连通块中，因为你只有 $k$ 种颜色，要划分 $k$ 个连通块

定义一个节点的**划分颜色**为根据上述性质，能够确定该节点被分在的连通块的颜色

在后面，我们会具体阐述怎么确定这些点是被划分还是未被划分

我们考虑每一个已经确定被划分的点，和每一个未被染色且不确定是否要被划分的点

对于一个已经确定被划分的点 $u$，显然 $f[u][1]=0$ 

考虑它的一个子节点 $v$ ，如果子节点 $v$ 已经拥有了**划分颜色**，那么对于 $f[u][0]$ 来说显然可以继承 $f[v][0]$ ，如果子节点 $v$ 没有**划分颜色**，那么它只能被它的父亲染色

所以可以得到 $f[u][0]=\mathop{\Pi}\limits_{v}(f[v][0]+f[v][1])$

对于一个没有确定被划分的点 $u$ ，显然 $f[u][1]=\mathop{\Pi}\limits_{v}(f[v][0]+f[v][1])$

由于这个点未被划分，我们要考虑选中该节点的一个子节点 $v$ ，去染色节点 $u$

所以$\huge f[u][0]=\sum\limits_{v}\frac{\mathop{\Pi}\limits_{v}(f[v][0]+f[v][1])}{f[v][0]+f[v][1]}f[v][0]$

算上求逆元的时间复杂度，这一部分的时间复杂度是 $O(nlogn)$ 的

---

接下来我们考虑划分

对于任意两个相同颜色的点，他们简单路径上的所有点都会被划分到同一个连通块

很容易想到一个 $n^2logn$ 的做法，暴力枚举两个点，随便用一个数据结构推平一下

但显然我们有更优秀的做法

我们用一个优先队列维护每一个已经被染色的点，每次取出深度最大的点

对于一个节点的父亲，如果当前节点的颜色与父亲相同，我们把这个节点弹出队列后，这个颜色在队列中的出现次数需要减 $1$

如果在队列中这个节点的颜色不只一次出现，

我们考虑以下两种情况：

$1.$父亲已经有颜色且颜色与当前节点不同，此时显然无解

$2.$父亲没有颜色，此时要通过父亲与其他节点联通，我们把父亲划分到与当前节点同一个连通块中，并把父亲加入队列，注意到此时该颜色在队列中的出现次数一进一出，没有变化，不需要更新

这一部分的时间复杂度是 $O(nlogn)$ 的，因此总时间复杂度为 $O(nlogn)$

**Code:**

```cpp
#include<bits/stdc++.h>
 
#define rd(x) x=read()
 
#define N 300005
 
using namespace std;
 
int n,k;
vector<int>e[N];
int a[N],c[N],dep[N],fa[N],f[N][2];
 
struct P{
	int x,dep;
	P(int _x=0,int _dep=0){x=_x,dep=_dep;}
	inline bool operator < (const P &r)const{return dep<r.dep;}
};
 
inline int read()
{
    int x=0,f=1;char ch=getchar();
    while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
 
inline void write(int x)
{
    if(x<0){putchar('-');x=-x;}
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}
 
const int p=998244353;
 
inline int fastPow(int a,int b){int ans=1;for(;b;b>>=1,a=1ll*a*a%p)if(b&1)ans=1ll*ans*a%p;return ans;}
 
inline int inv(int x){return fastPow(x,p-2);}
 
inline void addEdge(int u,int v){e[u].push_back(v);}
 
void dfs(int u,int faa)
{
	dep[u]=dep[faa]+1,fa[u]=faa;
	for(int i=0;i<e[u].size();i++)
	{
		int v=e[u][i];
		if(v==faa)continue;
		dfs(v,u);
	}
}
 
priority_queue<P>q;
 
void dfss(int u)
{
	int t=1;
	for(int i=0;i<e[u].size();i++)
	{
		int v=e[u][i];
		if(v==fa[u])continue;
		dfss(v),t=1ll*t*(f[v][0]+f[v][1])%p;
	}
	if(a[u])f[u][0]=t,f[u][1]=0;
	else
	{
		f[u][0]=0,f[u][1]=t; 
		for(int i=0;i<e[u].size();i++)
		{
			int v=e[u][i];
			if(v==fa[u])continue;
			f[u][0]=(f[u][0]+1ll*f[u][1]*inv(f[v][0]+f[v][1])%p*f[v][0]%p)%p;
		}
	}
}
 
int main()
{
	rd(n),rd(k);
	for(int i=1;i<=n;i++)rd(a[i]),c[a[i]]++;
	for(int i=1,u,v;i<n;i++)rd(u),rd(v),addEdge(u,v),addEdge(v,u);
	dfs(1,0);for(int i=1;i<=n;i++)if(a[i])q.push(P(i,dep[i])); 
	while(!q.empty())
	{
		P tp=q.top();q.pop();
		int u=tp.x,faa=fa[u];
		if(a[u]==a[faa])c[a[u]]--;
		else if(c[a[u]]!=1)
		{
			if(a[faa]){return puts("0"),0;}
			else a[faa]=a[u],q.push(P(faa,dep[faa])); 
		}
	}
	dfss(1);cout<<f[1][0]<<endl;
	
 
 
    return 0;
}
```

---

## 作者：Rainybunny (赞：7)

# 题目
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;[$luogu$](https://www.luogu.org/problem/CF1118F2).
# 题解
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;一道神奇的树形$DP$, 难度大概在紫题到黑题, 管理员大大可以完善一下...
## $Part_1$ 问题转化
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;可能翻译不太准确, 必须强调的是, 给定的树保证$k$种颜色的结点都会出现. 那么由于只能划分为$k$个连通块, 所以可以发现重要的隐含条件:  
> **同种颜色的结点一定在同一个联通块中**.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;理解到这一点, 其实问题已经并不复杂了. ( 这一结论会在下文反复应用, 我们给它取一个好听的名字: $X$结论. ( 大雾$QwQ$ ) )
## $Part_2$ 无解判定
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;由上文结论, 你会发现这很简单吧? ( 雾 )  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于第$i$种颜色的所有结点, 我们找到它们的$LCA$ ( 令为$LCA_i$ ). 如果任意一个颜色为$i$的结点$u$到$LCA$的路径上有其它颜色的结点, 或者与其它颜色的路径相交, 显然无法满足$X$结论, 判定为无解.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;在这一环节, 复杂度均摊$O(n\log n)$, 不用担心超时.
## $Part_3$ "缩点"
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;还是通过我们可爱的$X$结论, **任意一个颜色为$i$的结点$u$到$LCA_i$路径上的所有结点一定会被划分到颜色为$i$的联通块中.** 所以这些结点就不会产生多种情况了. 我们可以把它们缩成一个颜色为$i$的点. 例如 ( 本蒟蒻深知没图的痛苦 ):  
![CF1118F2_P1](https://cdn.luogu.com.cn/upload/image_hosting/b8h5o7je.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;当然, 在程序实现方面, 我们并不需要建立新图. 在进行$part_2$的时候, 我们暴力将所有路径上的结点染为颜色$i$, 让$LCA_i$作为"首领"接收所有颜色为$i$的结点的状态更新信息即可. 此处将在$part_5$具体分析.
## $Part_4$ $DP$的定义及转移
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;( 由于$luogu$的$KaTeX$渲染比较灵性, 一些求和求积的式子请自行脑补下标... )  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;~~在一波灵魂分析之后,~~ 定义状态$f(u,0/1)$表示, **结点$u$(没有划入/划入)某个带颜色的连通块时, 以$u$为根的子树的划分方案**.  

![CF1118F2_P2](https://cdn.luogu.com.cn/upload/image_hosting/bk489r3v.png) 

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于$u$的颜色$c_u$是否为$0$, 转移方程是不同的:  

### $a)~c_u=0$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于此时的$f(u,0)$, 随遇而安的无色结点$u$就像不存在一样, 所以由乘法原理:  
$$
f(u,0)=\prod(f(v,0)+f(v,1))
$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于此时的$f(u,1)$, 我们任意钦定与$u$相连的一个带色块与$u$相连, 其余的随便选即可. 令$t=\prod(f(v,0)+f(v,1))$:  
$$
f(u,1)=\sum(\frac{t\times f(v,1)}{f(v,0)+f(v,1)})
$$  
### $b)~c_u\not=0$
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;注意, 我们现在讨论的是$part_3$缩点之后的树. 所以, 如果此时的$u$再不构成带色块, 它就再也没有机会了. 对于此时的$f(u,0)$, 当然是:  
$$
f(u,0)=0
$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;把$u$分到一个带色块里, 这个块显然是新的. 同样是让子树任意分配, 然后让状态为$0$的与$u$联通, 所以此时的$f(u,1)$, 有:  
$$
f(u,1)=\prod_{v\in son_u}(f(v,0)+f(v,1))
$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;没错, 它和$c_u=0$时的$f(u,0)$长得一模一样.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$Now~let's~sum~up$:  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;( 这是对转移方程的整理, 上文均有提及, 若$KaTeX$爆炸可以放心跳过. )  
$$
f(u,0)=\lbrack c_u=0\rbrack\prod(f(v,0)+f(v,1))
$$  

$$
f(u,1)=\sum(\frac{t\times f(v,1)}{f(v,0)+f(v,1)}),c_u=0
$$  

$$
f(u,1)=\prod_{v\in son_u}(f(v,0)+f(v,1)),c_u\not=0
$$  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;我们以$1$为根, 则答案就是$f(1,1)$.
## $Part_5$ 细节问题
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;首先, $catch$住来自$part_3$的锅, 来分析一下几份代码.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;下面是自闭的$A$同学 ( 我 ) 对路径染色的代码:
```cpp
inline bool Paint ( int lf, const int rt ) {
	int TarCol = c[lf]; // 目标颜色
	while ( lf ^ rt ) {
		if ( DiffColor ( TarCol, c[lf = Par[lf][0]] ) ) { // c[lf]有颜色且不是目标颜色
			return false;
		}
		c[lf] = TarCol; // 染色
	}
	return true; // 没有异常
}
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对, 它$T$了. 如果所有点同色, $n$个结点分别爬向根节点, $O(n^2)$...  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考虑$u$在爬树的过程中, 遇到了与目标颜色相同的结点$v$, 它们相视一笑...  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;感性理解, 可以$return$了?  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;理性分析, $v$可能本来就有颜色, 或在一条被染色的路径中. 对于第一类, $v$爬向$LCA$的途中就会完成$u$的染色任务; 对于第二类, 也表明有其它结点比$u$捷足先登了.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;综上, 一旦遇到与目标颜色相同的结点, 苦逼爬树的$u$就能下班了.  

&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;于是, 有了另一位自闭同学$B$ ( 还是我 ) 的代码:
```cpp
inline bool Paint ( int lf, const int rt ) {
	int TarCol = c[lf];
	while ( lf ^ rt ) {
		if ( c[lf = Par[lf][0]] ) return c[lf] == TarCol; // 一旦lf有颜色, 要不"下班", 要不出现异常
		c[lf] = TarCol;
	}
	return true;
}
```
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;震惊, 它$WA$了!  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$B$同学冥想了半个小时, 大叫一声:"我$duang$!"  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;来看看他想到了什么.  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;对于下图, 我们按$1$, $LCA(1,2)$, $LCA(LCA(1,2),3)$, ...的方式求$LCA$, 并在第$i$次求$LCA$之后让$LCA(1,2,...,i-1)$和$i$爬向$LCA(1,2,...,i)$:  
![CF1118F2_P3](https://cdn.luogu.com.cn/upload/image_hosting/nswjkss4.png)  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;( 对不起, $LCA(1,2)$, 是无色的, 但我懒得改了$QwQ$ )  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;灵魂拷问: 红色虚线发生了什么?  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;$LCA(1,2)$向上爬树时, 因为爬向自己的结点在中途遇到了同色结点, $LCA(1,2)$并没有被染色, 目标颜色是$0$, 它与$3$号点颜色相斥...  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"原来是小问题呀!"$B$同学老激动了.
## $Part_6$ 代码
```cpp
#include <cstdio>
#include <vector>

#define Int register int

using namespace std;

const int MAXN = 3e5, MAXK = MAXN, LGMAXN = 19, MOD = 998244353;
int n, k, Cnte, c[MAXN + 5] = {}, Head[MAXN + 5] = {}, Depth[MAXN + 5] = {}, Top[MAXK + 5] = {};
																	// Top[i]是颜色为i的结点的LCA 
int Par[MAXN + 5][LGMAXN + 5] = {}, F[MAXN + 5][2] = {};
vector<int> Colnd[MAXK + 5] = {}; // 记录各种颜色的结点 

struct Edge {
	int To, _nxt;
} Graph[MAXN << 1] = {};

inline void Link ( const int From, const int To ) {
	Graph[++ Cnte] = { To, Head[From] };
	Head[From] = Cnte;
}

inline int qkpow ( int a, int b, const int p ) {
	int ret = 1;
	while ( b ) {
		ret = 1LL * ret * ( b & 1 ? a : 1 ) % p;
		a = 1LL * a * a % p, b >>= 1;
	}
	return ret;
}

inline void Prepare ( const int u, const int fa ) { // LCA倍增预处理 
	Depth[u] = Depth[fa] + 1, Par[u][0] = fa;
	for ( Int i = 1; i ^ 20; ++ i ) Par[u][i] = Par[Par[u][i - 1]][i - 1];
	for ( Int i = Head[u], v; i; i = Graph[i]._nxt ) {
		if ( ( v = Graph[i].To ) ^ fa ) {
			Prepare ( v, u );
		}
	}
}

inline int LCA ( int a, int b ) { // LCA 
	for ( Int i = 19; ~ i; -- i ) {
		if ( Depth[Par[a][i]] >= Depth[b] ) a = Par[a][i];
		if ( Depth[Par[b][i]] >= Depth[a] ) b = Par[b][i];
	}
	if ( a ^ b ) {
		for ( Int i = 19; ~ i; -- i ) {
			if ( Par[a][i] ^ Par[b][i] ) {
				a = Par[a][i], b = Par[b][i];
			}
		}
		return Par[a][0];
	}
	return a;
}

inline bool Paint ( int lf, const int rt, const int cl ) { // 暴力爬树, 涂色 
	while ( lf ^ rt ) {
		if ( c[lf = Par[lf][0]] ) return c[lf] == cl;
		c[lf] = cl;
	}
	return true;
}

inline int GetColTop ( const int cl ) { // 反复LCA求得Top 
	int ret = Colnd[cl][0], tmp;
	for ( unsigned int i = 1; i ^ Colnd[cl].size (); ++ i ) {
		tmp = ret, ret = LCA ( tmp, Colnd[cl][i] );
		if ( ! Paint ( tmp, ret, cl ) || ! Paint ( Colnd[cl][i], ret, cl ) ) return -1;
	}
	return ret;
}

inline void DFS ( const int u, const int fa ) {
	int t = 1;
	for ( Int i = Head[u], v; i; i = Graph[i]._nxt ) {
		if ( ( v = Graph[i].To ) ^ fa ) {
			DFS ( v, u ); 
			if ( c[u] && c[v] ^ c[u] ) { // 直接为Top提供更新信息 
				F[Top[c[u]]][1] = 1LL * F[Top[c[u]]][1] * ( F[v][0] + F[v][1] ) % MOD;
			} else if ( ! c[u] ) {
				t = 1LL * t * ( F[v][0] + F[v][1] ) % MOD;
			}
		}
	}
	if ( c[u] ) return ;
	F[u][0] = t, F[u][1] = 0; // c[u] = 0时的更新 
	for ( Int i = Head[u], v; i; i = Graph[i]._nxt ) {
		if ( ( v = Graph[i].To ) ^ fa ) {
			F[u][1] = ( F[u][1] + 1LL * F[v][1] * t % MOD * qkpow ( F[v][0] + F[v][1], MOD - 2, MOD ) % MOD ) % MOD;
		}
	}
}

inline void Work () {
	scanf ( "%d %d", &n, &k );
	for ( Int i = 1; i <= n; ++ i ) {
		scanf ( "%d", &c[i] );
		Colnd[c[i]].push_back ( i );
	}
	for ( Int i = 1, u, v; i ^ n; ++ i ) {
		scanf ( "%d %d", &u, &v );
		Link ( u, v ), Link ( v, u );
	}
	Prepare ( 1, 1 );
	for ( Int i = 1; i <= k; ++ i ) {
		if ( ! ~ ( Top[i] = GetColTop ( i ) ) ) {
			puts ( "0" );
			return ;
		}
		F[Top[i]][1] = 1; // 记得赋初值 
	}
	DFS ( 1, 1 );
	printf ( "%d\n", F[1][1] );
}

int main () {
	Work ();
	return 0;
}
```

---

## 作者：cyfff (赞：3)

给出一个优美且好写的线性做法。

首先需要把同色点缩成一个连通块。我们把同色点按 $dfs$ 序排序后，直接暴力对相邻两个点的路径上的点打上标记，若标记冲突则直接结束程序。容易发现一条边最多只会遍历到两次，故复杂度是线性的。

缩完点后的 $dp$ 部分是容易的。

```
#include<bits/stdc++.h>
#define F first
#define S second
#define G(x) if(co[x]!=i&&co[x]){puts("0");return 0;}else co[x]=i;
using namespace std;
typedef long long LL;
typedef pair<LL,LL> pr;
inline LL rd(){
	LL x=0,y=1;char c=getchar();
	for(;c<'0'||c>'9';c=getchar())if(c=='-')y=-1;
	for(;c>='0'&&c<='9';c=getchar())x=(x<<1)+(x<<3)+(c^48);
	return x*y;
}
const LL N=300005,p=998244353;
LL qp(LL x,LL y){LL z=1;for(;y;y>>=1,x=x*x%p)if(y&1)z=z*x%p;return z;}
LL n,m,dfn[N],dfc,co[N],f[N],de[N],F[N],u[N],v[N];vector<LL>vc[N],ve[N],g[N];
void dfs(LL x,LL fa){
	dfn[x]=++dfc;f[x]=fa;de[x]=de[fa]+1;
	for(auto y:ve[x])if(y!=fa)dfs(y,x);
}
bool cmp(int x,int y){return dfn[x]<dfn[y];}
LL fd(LL x){return x==F[x]?x:F[x]=fd(F[x]);}
void df(LL x,LL fa){
	if(co[x])u[x]=1;else v[x]=1;
	for(auto y:g[x])if(y!=fa)df(y,x),u[x]=(u[x]*(v[y]+u[y])+v[x]*u[y])%p,v[x]=v[x]*(u[y]+v[y])%p;
}
int main(){
	n=rd();m=rd();
	for(int i=1;i<=n;++i){co[F[i]=i]=rd();if(co[i])vc[co[i]].push_back(i);}
	for(int i=1,x,y;i<n;++i)ve[x=rd()].push_back(y=rd()),ve[y].push_back(x);
	dfs(1,0);
	for(int i=1;i<=m;++i){
		sort(vc[i].begin(),vc[i].end(),cmp);
		for(int j=0;j<vc[i].size();++j){
			int u=vc[i][j],v=vc[i][(j+1)%vc[i].size()];
			if(de[u]<de[v])swap(u,v);
			while(de[u]>de[v]){G(u) u=f[u];}
			while(u!=v){G(u) G(v) u=f[u];v=f[v];}
			G(u)
		}
	}
	for(int i=1;i<=n;++i)for(auto j:ve[i])if(co[i]&&co[i]==co[j])F[fd(i)]=fd(j);
	for(int i=1;i<=n;++i)for(auto j:ve[i])if(co[i]!=co[j]||!co[i])g[fd(i)].push_back(fd(j));
	df(fd(1),0);cout<<u[fd(1)];
	return 0;
}

---

## 作者：_edge_ (赞：2)

头一次写这种题，写篇题解。

但是其实不是特别困难。

由于他要求我们只能断开 $k-1$ 条边，因此，我们肯定是一个连通块内只留下同一个颜色。

我们大致初步猜测，他应该是缩成若干个有颜色的连通块和若干个空节点，块内不能断边，然后要求断开边使得每个标记点都被互相独立。

我们具体去思考这部分该怎么做。

首先是缩点，我们把同一个颜色的点都抽出来，然后需要搞出属于他的连通块。

这东西是个经典的东西，就是相邻做一下 LCA，求出他们深度最小的 LCA，然后每个点暴力往上跳即可。

我们发现，如果有两个连通块是有交集的，那么必定无解，也就是说我们跳 LCA 的时候每个点至多跳 $1$ 次。

然后我们再用并查集去把他缩成一个点。

然后就变成了若干个标记点和空节点的树，要求在这棵树上断 $k-1$ 条边，使得他变成若干个恰好包含一个标记点的连通块。

打过 NOIP 2022 的应该都明白，这东西和建造军营类似，那么我们类似设出 dp 状态，设 $f_{x,0/1,0/1}$ 表示当前到 $x$ 节点，子树外是否有点，子树内是否有点。

然后我们思考转移。

比如当前枚举到的点是 $x$，他的儿子设为 $v$。

这里可以直接得出一个不合法状态 $f_{x,1,1}$ 是永远应该为 $0$ 的。

那么假如说要断开，就是 $f_{x,j,k}=f_{x,j,k} \times f_{v,0,1}$，什么意思呢？就是他儿子内部肯定都有个关键点，否则不能断开。

假如不断开，那么就分类讨论。

$f_{x,0,0}$ 的情况，要么儿子里有，要么没有。

$f_{x,1,0}$ 的情况，那么就是儿子里不能有，儿子的子树外有。

$f_{x,0,1}$ 的情况，儿子里面不能有，儿子的子树外有。

搞清楚这些就做完了，这边注意细节。

```cpp
#include <bits/stdc++.h>
#define int long long 
#define pb push_back
using namespace std;
const int INF=5e5+5;
const int Mod=998244353;
int n,m,a[INF];
struct _node_edge{
    int to_,next_;
}edge[INF<<1];
signed tot,head[INF],dep[INF],vis2[INF],fath[INF][25],fa_set[INF],vis[INF];
void add_edge(int x,int y) {
    edge[++tot]={y,head[x]};
    head[x]=tot;
}
map <int,map<int,int> >Map;
vector <int> co[INF];
int find_set(int x) {return x==fa_set[x]?x:fa_set[x]=find_set(fa_set[x]);}
void mer(int x,int y) {
    x=find_set(x);y=find_set(y);
    if (x==y) return ;
    fa_set[x]=y;
}
void DFS(int x,int fa) {
    dep[x]=dep[fa]+1;fath[x][0]=fa;
    int len=__lg(dep[x]);
    for (int i=1;i<=len;i++)
        fath[x][i]=fath[fath[x][i-1]][i-1];
    for (int i=head[x];i;i=edge[i].next_) {
        int v=edge[i].to_;
        if (v==fa) continue;
        DFS(v,x);
    }
    return ;
}
int LCA(int x,int y) {
    if (dep[x]<dep[y]) swap(x,y);
    while (dep[x]!=dep[y]) 
        x=fath[x][__lg(dep[x]-dep[y])];
    if (x==y) return x;
    int len=__lg(dep[x]);
    for (int i=len;~i;i--) {
        int xx=fath[x][i],yy=fath[y][i];
        if (xx==yy) continue;
        x=xx;y=yy;
    }
    return fath[x][0];
}
vector <int> cnt;
int Get(int x) {return lower_bound(cnt.begin(),cnt.end(),x)-cnt.begin()+1;}
namespace S{
    struct _node_edge{
        int to_,next_;
    }edge[INF<<1];
    int tot,head[INF],aa[INF],n;
    void add_edge(int x,int y) {
        n=max(n,x);n=max(n,y);
        edge[++tot]={y,head[x]};
        head[x]=tot;
    }
    int f[INF][3][3],f1[3][3];
    void DFS2(int x,int fa) {
        if (aa[x]) f[x][0][1]=f[x][1][1]=1;
        else f[x][0][0]=f[x][1][0]=1;
        // cout<<x<<" "<<fa<<"\n";
        for (int i=head[x];i;i=edge[i].next_) {
            int v=edge[i].to_;
            if (v==fa) continue;
            DFS2(v,x);
            memset(f1,0,sizeof f1);
            for (int j=0;j<2;j++) {
                for (int k=0;k<2;k++) {
                    for (int l=1;l<2;l++) {
                        // break
                        f1[j][k]+=f[x][j][k]*f[v][0][l]%Mod;
                    }
                }
            }

            f1[0][0]+=f[x][0][0]*f[v][0][0]%Mod;f1[0][0]%=Mod;
            f1[1][0]+=f[x][1][0]*f[v][1][0]%Mod;f1[1][0]%=Mod;
            f1[0][1]+=f[x][0][0]*f[v][0][1]%Mod;f1[0][1]%=Mod;
            f1[0][1]+=f[x][0][1]*f[v][1][0]%Mod;f1[0][1]%=Mod;

            for (int j=0;j<2;j++)
                for (int k=0;k<2;k++)
                    f[x][j][k]=f1[j][k];
        }
        f[x][1][1]=0;
        return ;
    }
    int ksm(int x,int y) {
        int ba=x%Mod,ans=1;
        while (y) {
            if (y&1) ans=(ans*ba)%Mod;
            ba=(ba*ba)%Mod;y>>=1;
        }
        return ans;
    }
    void main() {
        // for (int i=1;i<=n;i++) cout<<aa[i]<<" ";
        // cout<<"\n";
        DFS2(1,0);
        cout<<f[1][0][1]<<"\n";
        return ;
    }
}
void solve() {
    cin>>n>>m;
    for (int i=1;i<=n;i++) {
        cin>>a[i];
        fa_set[i]=i;
        co[a[i]].pb(i);
    }
    for (int i=1;i<n;i++) {
        int x=0,y=0;
        cin>>x>>y;
        add_edge(x,y);
        add_edge(y,x);
    }
    DFS(1,0);
    for (int i=1;i<=m;i++) {
        if (co[i].size()==0) continue;
        int L=co[i][0],len=co[i].size();
        for (int j=1;j<len;j++) {
            L=LCA(L,co[i][j]);
            mer(co[i][j],co[i][j-1]);
        }
        vector <int> cnt;
        if (vis[L]) {
            // if (fl) {cout<<"26127360\n";return ;}
            // if (fl1) {cout<<"395652393\n";return ;}
            // if (fl2) {cout<<"267406296\n";return ;}
            // if (fl) cout<<L<<" bomb\n";
            cout<<"0\n";
            return ;
        }
        cnt.pb(L);mer(L,co[i][0]);
        for (int j=0;j<len;j++) {
            int X=co[i][j];
            while (X!=L) {
                if (vis[X]) {
                    // if (fl) {cout<<"26127360\n";return ;}
                    // if (fl1) {cout<<"395652393\n";return ;}
                    // if (fl2) {cout<<"267406296\n";return ;}
                    cout<<"0\n";
                    return ;
                }
                if (vis2[X]) break;
                vis2[X]=1;
                cnt.pb(X);mer(X,co[i][j]);
                X=fath[X][0];
            }
        }
        for (int j:cnt) vis[j]=1;
        len=cnt.size();
        while (len--) cnt.pop_back();
    }
    for (int x=1;x<=n;x++) cnt.pb(find_set(x));
    sort(cnt.begin(),cnt.end());
    cnt.erase(unique(cnt.begin(),cnt.end()),cnt.end());

    
    for (int x=1;x<=n;x++) {
        // cout<<x<<" "<<find_set(x)<<" kelkel\n";
        if (a[x]) S::aa[Get(find_set(x))]=1;
        for (int i=head[x];i;i=edge[i].next_) {
            int v=edge[i].to_;
            if (find_set(x)==find_set(v)) continue;
            int xx=find_set(x),yy=find_set(v);
            if (Map[xx][yy]) continue;
            Map[xx][yy]=Map[yy][xx]=1;
            S::add_edge(Get(xx),Get(yy));
            S::add_edge(Get(yy),Get(xx));
        }
    }

    S::main();
    return ;
}
signed main()
{
    ios::sync_with_stdio(false);
    int t=1;
    while (t--) solve();
    return 0;
}
```


---

## 作者：Graphcity (赞：2)

首先，对于同颜色的点集，它们的最小连通块一定不能够被切开。所以先把每个同颜色点集的最小连通块找出来，如果有交那就不合法。

具体而言，先求出点集的 LCA，再对每个点向 LCA 暴力向上跳打标记即可。如果遇到有标记的点，就判断颜色是否相同。由于每个点至多被标记一次，时间复杂度 $O(n)$。

然后对于这些连通块显然可以缩成一个点。那么问题就变成了这样：在一棵树上且若干刀，使得每一个被染色的点都恰好在一个连通块中，且所在的连通块互不相同。

设 $f_{i,0/1}$ 为在 $i$ 结点的子树中，以 $i$ 为根的连通块是否存在染色结点的方案数。初始 $f_{x,col_x}=1$，其中 $col_x$ 为 $x$ 是否被染色。

每次合并 $x$ 与它的一个儿子 $y$：

$$
\begin{cases}
f_{x,0}&\gets f_{x,0}\times (f_{y,0}+f_{y,1})\\
f_{x,1}&\gets f_{x,1}\times (f_{y,0}+f_{y,1})+f_{x,0}\times f_{y,1}
\end{cases}
$$

转移的含义可以结合这张表来解释：

| 不切开 | $y$ 无色 | $y$ 有色 |
| :----------: | :----------: | :----------: |
| **$x$ 无色** | $x$ 无色 | $x$ 有色 |
| **$x$ 有色** | $x$ 有色 | 不合法 |

| 切开 | $y$ 无色 | $y$ 有色 |
| :----------: | :----------: | :----------: |
| **$x$ 无色** | 不合法 | $x$ 无色 |
| **$x$ 有色** | 不合法 | $x$ 有色 |

最后答案即为 $f_{root,1}$。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=3e5,Mod=998244353;

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

int n,m,val[Maxn+5],vis[Maxn+5];

struct Graph
{
    int f[Maxn+5][2];
    vector<int> v[Maxn+5];
    inline void dfs(int x,int fa)
    {
        f[x][vis[x]]=1;
        for(auto y:v[x]) if(y!=fa) dfs(y,x);
        for(auto y:v[x]) if(y!=fa)
        {
            int a=1ll*f[x][0]*(f[y][0]+f[y][1])%Mod;
            int b=(1ll*f[x][1]*(f[y][0]+f[y][1])%Mod+1ll*f[x][0]*f[y][1]%Mod)%Mod;
            f[x][0]=a,f[x][1]=b;
        }
    }
    inline void Run()
    {
        dfs(1,0);
        printf("%d\n",f[1][1]);
    }
} G;

struct Tree
{
    int col[Maxn+5],fa[Maxn+5],dep[Maxn+5];
    int top[Maxn+5],son[Maxn+5],siz[Maxn+5],chk[Maxn+5];
    vector<int> v[Maxn+5],w[Maxn+5];
    inline void dfs1(int x,int f)
    {
        fa[x]=f,siz[x]=1,dep[x]=dep[f]+1;
        for(auto y:v[x]) if(y!=f)
        {
            dfs1(y,x),siz[x]+=siz[y];
            son[x]=(siz[y]>siz[son[x]]?y:son[x]);
        }
    }
    inline void dfs2(int x,int t)
    {
        top[x]=t;
        if(son[x]) dfs2(son[x],t);
        for(auto y:v[x]) if(y!=fa[x] && y!=son[x]) dfs2(y,y);
    }
    inline int LCA(int x,int y)
    {
        while(top[x]!=top[y]) (dep[top[x]]>dep[top[y]]?x=fa[top[x]]:y=fa[top[y]]);
        return (dep[x]<dep[y]?x:y);
    }
    inline void Jump(int x,int y,int id,int c)
    {
        while(x!=y && !col[x]) col[x]=id,chk[x]=c,x=fa[x];
        if(chk[x] && chk[x]!=c) {printf("0\n"); exit(0);}
        col[y]=id,chk[y]=c;
    }
    inline void Run()
    {
        n=read(),m=read();
        For(i,1,n)
        {
            col[i]=read();
            if(col[i]) w[col[i]].push_back(i);
        }
        For(i,1,n) col[i]=0;
        For(i,1,n-1)
        {
            int a=read(),b=read();
            v[a].push_back(b),v[b].push_back(a);
        }
        dfs1(1,0),dfs2(1,1);
        For(id,1,m)
        {
            int lca=0;
            for(auto i:w[id])
            {
                if(!lca) lca=i;
                else lca=LCA(lca,i);
            }
            for(auto i:w[id]) Jump(i,lca,lca,id);
            vis[lca]=1;
        }
        For(i,1,n) for(auto j:v[i])
        {
            if(col[i]!=col[j] || !col[i] || !col[j])
            {
                int a=(!col[i]?i:col[i]),b=(!col[j]?j:col[j]);
                G.v[a].push_back(b);
            }
        }
    }
} T;

int main()
{
    T.Run(),G.Run();
    return 0;
}
```

---

## 作者：rizynvu (赞：0)

[我的博客](https://www.cnblogs.com/rizynvu/p/18184370)。

发现一共有 $k$ 种颜色，只能切 $k - 1$ 刀，那么就说明肯定每个连通块都必须有一种颜色。  
那么相当于就是求把树划分为 $k$ 个连通块，且每个连通块刚好包含一种颜色的所有点。

对于同一种颜色，因为其要连通所以可以先找出来最小连通块，必须要包含这个最小连通块才合法。  
对于找最小连通块，可以考虑类似虚树的求法，即按 $\text{dfn}$ 排序，相邻的两个点暴力往上跳找 $\text{LCA}$ 并在过程中染色。  
暴力向上跳的点数是 $2\times$ 最小连通块的大小的，所以如果每个颜色的最小连通块无交的话肯定不会超过 $2n$。  
否则若有交则肯定无解，可以在染色的时候判一下是否被染过不是当前颜色的颜色即可。

然后接下来若已经得到了最小连通块，那么因为肯定需要包含最小连通块，可以考虑缩成一个点来考虑。  
接下来以 $col_i$ 表示 $i$ 点是否有颜色。  
因为对于每个连通块，相当于就是要存在一个 $col_i = 1$ 的点，考虑把这个放进状态来 $\text{DP}$。  
即设 $f_{u, 0 / 1}$ 为 $u$ 所在的连通块是否有 $col_i = 1$ 的点。

考虑 $v\in son_u$ 处理完后，信息如何合并上 $f_u$：  
- $u, v$ 中都不存在点，那么 $(u, v)$ 肯定不能切开。
- $u$ 中不存在点，$v$ 中存在点，不切开那么 $u$ 连通块就存在了，否则若切开还是不存在。
- $u$ 中存在点，$v$ 中不存在点，那么肯定不能切开让 $v$ 所在的连通块存在点。
- $u, v$ 都存在点，则肯定需要切开。

于是有转移式：  
$f_{u, 0} = f'_{u, 0}\times f_{v, 0} + f'_{u, 0}\times f_{v, 1}, f_{u, 1} = f'_{u, 1}\times f_{v, 0} + f'_{u, 1}\times f_{v, 1} + f'_{u, 0}\times f_{v, 1}$。

时间复杂度 $\mathcal{O}(n\log n)$。

```cpp
#include<bits/stdc++.h>
using ll = long long;
constexpr ll mod = 998244353;
const int maxn = 3e5 + 10;
int a[maxn];
std::vector<int> son[maxn];
int fa[maxn], dep[maxn], dfn[maxn], dt;
void dfs1(int u) {
   dep[u] = dep[fa[u]] + 1, dfn[u] = ++dt;
   for (int v : son[u]) {
      fa[v] = u, son[v].erase(std::find(son[v].begin(), son[v].end(), u));
      dfs1(v);
   }
}
int col[maxn];
inline void lcacol(int u, int v, int c) {
   auto upd = [&](int p) {
      if (! col[p] || col[p] == c) col[p] = c;
      else puts("0"), exit(0);
   };
   while (dep[u] > dep[v]) upd(u), u = fa[u];
   while (dep[v] > dep[u]) upd(v), v = fa[v];
   while (u != v) upd(u), upd(v), u = fa[u], v = fa[v];
   upd(u);
}
std::vector<int> cp[maxn];
std::vector<int> to[maxn];
ll f[maxn][2];
void dfs2(int u) {
   f[u][col[u] > 0] = 1;
   for (int v : to[u]) {
      to[v].erase(std::find(to[v].begin(), to[v].end(), u));
      dfs2(v);
      ll f0 = f[u][0], f1 = f[u][1];
      f[u][0] = (f0 * f[v][0] + f0 * f[v][1]) % mod;
      f[u][1] = (f1 * f[v][0] + f1 * f[v][1] + f0 * f[v][1]) % mod;
   }
}
int main() {
   int n, k; scanf("%d%d", &n, &k);
   for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
   for (int i = 1, x, y; i < n; i++) {
      scanf("%d%d", &x, &y);
      son[x].push_back(y), son[y].push_back(x);
   }
   dfs1(1);
   for (int i = 1; i <= n; i++) cp[a[i]].push_back(i);
   for (int i = 1; i <= k; i++) {
      std::sort(cp[i].begin(), cp[i].end(), [&](int x, int y) {return dfn[x] < dfn[y];});
      int p = cp[i][0];
      if (cp[i].size() == 1) lcacol(cp[i][0], cp[i][0], p);
      for (int j = 0; j + 1 < cp[i].size(); j++) lcacol(cp[i][j], cp[i][j + 1], p);
   }
   for (int i = 1; i <= n; i++)
      for (int j : son[i]) {
         int x = ! col[i] ? i : col[i], y = ! col[j] ? j : col[j];
         if (x == y) continue;
         to[x].push_back(y), to[y].push_back(x);
      }
   dfs2(! col[1] ? 1 : col[1]);
   printf("%lld\n", f[! col[1] ? 1 : col[1]][1]);
   return 0;
}
```

---

