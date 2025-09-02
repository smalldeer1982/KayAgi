# [CERC2014] Parades

## 题目描述

在永恒节日之城，有 $n$ 个街道交叉口和 $n-1$ 条双向街道，每条街道连接两个交叉口。每两个交叉口之间，恰好有一条（直接或间接）路径连接它们。没有交叉口是超过 10 条街道的端点。

每年 9 月 13 日（即一年中的第 256 天），永恒节日之城会举行许多庆祝活动。特别是，市民们想要组织 $m$ 场游行。第 $i$ 场游行从交叉口 $u_i$ 开始，到交叉口 $v_i$ 结束，沿着端点之间的唯一路径进行。

作为城市的市长，你负责市民的安全。因此，你规定任何两场游行都不允许使用相同的街道，尽管它们可以有共同的交叉口，甚至是共同的端点。

为了安抚市民，尽量组织尽可能多的游行，同时不违反安全规定。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
1
6
1 2
2 3
3 4
3 5
3 6
4
1 3
4 5
5 6
6 4```

### 输出

```
2```

# 题解

## 作者：ez_lcw (赞：13)

考虑树形$dp$，设$dp[i]$表示以$i$为根的子树中路线的最大数量（即这棵子树的最优解），$un[i][]$表示以$i$为根的子树中，所有的点$u$，当且仅当$i$到$u$的路径上不与$i$子树的最优解中的某条路径相交。

那么考虑用子树合并根。

对于$dp[u]$，我们先加上每个儿子的$dp$值，然后我们再考虑下面这两种情况：

1. 对于$u$的某一个儿子$son$，如果$son$的子树内（包括$son$自己）有一个点$v=un[son][i]$与$u$之间有路径$(u,v)$，如图：

	![在这里插入图片描述](https://img-blog.csdnimg.cn/20190914145340595.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2V6X2xjdw==,size_16,color_FFFFFF,t_70)
	可能对于某一个儿子$son$，这种路径可能有很多条，但是选任意一条都可以，因为边$(u,v)$只能走一遍。

2. 对于$u$的某两个不同的儿子$son_1$、$son_2$，它们各自子树内（包括$son_1$、$son_2$）分别有两个点$a=un[son_1][i]$、$b=un[son_2][j]$，且有一条路径$(a,b)$，我们就把$link[son_1][son_2]$设为$1$，如图：

	![在这里插入图片描述](https://img-blog.csdnimg.cn/20190914204149599.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2V6X2xjdw==,size_16,color_FFFFFF,t_70)
	那么对于某个儿子$son_1$，它可能可以匹配到很多个$son_2$，所以怎么选择才方案最优是解决问题的关键，所以我们考虑状压$dp$。

	设$f[i]$表示状态$i$的最优解，状态$i$的二进制表达式的第$x$位若为$1$，则表示已经考虑过加入这个儿子的情况了。

	那么我们从小到大枚举$i$，找到$a=\_\_builtin\_ctz(i)$，$lb=lowbit(i)$，则$i$可以从$i-lb$转移过来，因为在$i-lb$的二进制表达式中，第$a$位为$0$；在$i$的二进制表达式中，第$a$位为$1$。

	所以现在我们考虑的是考虑过加入儿子$a$，也就是上文的$son_1$，那么我们还要枚举$son_2$，即下文的$b$。

	对于每一个$b$，当$link(a,b)=1$且$i$的二进制表达式中第$b$位为$1$时，我们取：

	$$f[i]=max(f[i],f[i-(1<<a)-(1<<b)]+1)$$

	即从$i$的第$a$位为$0$且第$b$位为$0$时转移过来。

	最后$dp[u]+=f[2^{u\text{的儿子个数}}-1]$即可。

这样就合并完成了。

记得合并完后维护一下$un[u]$。

最后输出$dp[1]$就好了。

完整代码加注释如下：

```cpp
#include<bits/stdc++.h>
 
#define N 1010
#define D 15
 
using namespace std;
 
int T,n,m;
int dp[N],f[1<<D];
int cnt,head[N],nxt[N<<1],to[N<<1];
bool vis[N][N],link[D][D];
 
vector<int>un[N];
 
int lowbit(int x)
{
    return x&-x;
}
 
void init()
{
    cnt=0;
    memset(head,0,sizeof(head));
    memset(vis,false,sizeof(vis));
    memset(dp,0,sizeof(dp));
}
 
void adde(int u,int v)
{
    to[++cnt]=v;
    nxt[cnt]=head[u];
    head[u]=cnt;
}
 
void dfs(int u,int fa)
{
    int son[D],tot=0;
    for(int i=head[u];i;i=nxt[i])
    {
        if(to[i]!=fa)
        {
            dfs(to[i],u);
            dp[u]+=dp[to[i]];
            son[tot++]=to[i];   //存储每一个儿子
        }
    }
    for(int i=0;i<tot;i++)
    {
        for(int j=0;j<un[son[i]].size();j++)
        {
            if(vis[un[son[i]][j]][u])   
            {
                dp[u]++;
                un[son[i]].clear();//由于已经选了一条边了，所以为了下面的维护un[u]，我们把un[son[i]]清零
            }       
        }
    }
    memset(link,false,sizeof(link));
    for(int i=0;i<tot;i++)
    {
        for(int j=i+1;j<tot;j++)
        {
            int a=son[i],b=son[j];
            for(int p=0;p<un[a].size();p++)
            {
                for(int q=0;q<un[b].size();q++)
                {
                    if(vis[un[a][p]][un[b][q]])
                    {
                        link[i][j]=link[j][i]=true;//标记son[i]与son[j]各自子树之间有路径
                        break;
                    }
                }
                if(link[i][j])
                    break;
            }
        }   
    }
    f[0]=0;
    int maxn=(1<<tot)-1;
    for(int i=1;i<=maxn;i++)
    {
        f[i]=f[i-lowbit(i)];
        int a=__builtin_ctz(i);
        for(int b=a+1;b<tot;b++)//枚举son2
            if(link[a][b]&&((i>>b)&1))
                f[i]=max(f[i],f[i-(1<<a)-(1<<b)]+1);
    }
    dp[u]+=f[maxn];
    un[u].push_back(u);
    for(int i=0;i<tot;i++)
        if(f[maxn]==f[maxn-(1<<i)])
            for(int j=0;j<un[son[i]].size();j++)
                un[u].push_back(un[son[i]][j]);//维护un[u]
}
 
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        init();
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            un[i].clear();
        for(int i=1;i<n;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            adde(u,v),adde(v,u);
        }
        scanf("%d",&m);
        for(int i=1;i<=m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            vis[u][v]=vis[v][u]=true;
        }
        dfs(1,0);
        printf("%d\n",dp[1]);
    }
}
```

---

## 作者：木木！ (赞：7)

比较复杂的一道题。

首先可以想到树上 DP。由于数据范围允许 $n^2$，并且在 DP 的过程中需要维护一些边禁用的情况，可以定义 $f_{i,j}$ 表示在第 $i$ 个点的子树中，$i$ 到 $j$ 一段路被禁用的最大收益。特别的，当 $i=j$ 或 $j$ 不在 $i$ 的子树中的时候，没有边被禁用。

因此，对于某一个游行 $(a,b)$，我们在 LCA 处考虑这个游行。设 $a$ 在 LCA 的 $ca$ 孩子的子树中，$b$ 在 $cb$ 孩子的子树中，那么游行 $(a,b)$ 对答案的贡献即为：

$$v((a,b))=f_{ca,a}+f_{cb,b}+1$$

然后考虑怎么转移。因为游行间是互斥的，一个游行能否进行需要考虑到其他游行的占用情况。因此考虑状压 DP，具体过程不赘述。

状压 DP 的话，如果直接暴力枚举游行队伍，设点的最大度数为 $k$，时间复杂度会升至 $m2^k$，无法承受。因此可以先预处理出占用某两个特定孩子的最大贡献，将时间复杂度降至 $m+k^22^k$。

最终时间复杂度，DFS 的时候需要统计每个点的子树以及他们在哪个孩子中，因此这部分耗时 $\Theta(n^2)$；采用 st 表计算 LCA，预处理 $\Theta(n\log n)$；处理每个游行需要找到 LCA 并且采用链表挂到 LCA 处，总时间复杂度 $\Theta(m)$；DP 的时候总时间复杂度为 $\Theta(n(k^2+k^22^k+n)+m)=\Theta(n^2+nk^22^k+m)$；总时间复杂度即为 $\Theta(n^2+m+nk^22^k)$。由于状压 DP，$nk^22^k$ 这一部分跑不满，因此能卡进时限。

代码较长，不过细节比较少，大部分都是默板子和各种麻烦的预处理。

附 AC 代码：

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

void chkmax(int& a,int b) { if(b>a) a=b; }

int beg[1005];
int ed[2005];
int nxt[2005];
int top;

void addedge(int a,int b)
{
	++top;
	ed[top] = b;
	nxt[top] = beg[a];
	beg[a] = top;
}

int dn;
int fa[1005];
int cn[1005];
int dfn[1005];
int depth[1005];
int travbi[2005];
int chx[15][1005];
int chn[1005][1005];
int tratop;

void dfs(int x)
{
	travbi[++tratop] = x;
	dfn[x] = tratop;
	int cnnn = 0;
	for(int p=beg[x]; p; p=nxt[p])
	{
		if(ed[p] != fa[x])
		{
			++cnnn;
			fa[ed[p]] = x;
			chx[cnnn][x] = ed[p];
			depth[ed[p]] = depth[x] + 1;
			
			dfs(ed[p]);
			travbi[++tratop] = x;
			
			for(int i=1; i<=dn; ++i)
			{
				if(chn[ed[p]][i])
				{
					chn[x][i] = cnnn;
				}
			}
			chn[x][ed[p]] = cnnn;
		}
	}
	cn[x] = cnnn;
}

int log2[2005];
int st[12][2005];

int cmp(int a,int b)
{
	return depth[a]<depth[b] ? a : b;
}

void buildst(int n,int* arr)
{
	memcpy(st[0],arr,(n+1)*sizeof(int));
	int logn = log2[n];
	for(int i=1; i<=logn; ++i)
	{
		for(int j=1; j<=n-(1<<i); ++j)
		{
			st[i][j] = cmp(st[i-1][j],st[i-1][j+(1<<(i-1))]);
		}
	}
}

int queryst(int l,int r)
{
	if(l>r) swap(l,r);
	int loglen = log2[r-l+1];
	return cmp(st[loglen][l],st[loglen][r-(1<<loglen)+1]);
}

struct parad
{
	int l,ln;
	int r,rn;
	int monn;
};

int dbeg[1005];
parad pi[500005];
int dnxt[500005];
int dtop;

void addparad(int d,parad p)
{
	++dtop;
	pi[dtop] = p;
	dnxt[dtop] = dbeg[d];
	dbeg[d] = dtop;
}

int unp[1005][1005];

int pdp[1024];
int maxmn[15][15];

void dp(int x)
{
	for(int p=beg[x]; p; p=nxt[p])
	{
		if(ed[p] != fa[x])
		{
			dp(ed[p]);
		}
	}
	int cx = cn[x];
	if(cx)
	{
		for(int i=1; i<=cx; ++i)
		{
			for(int j=1; j<=cx; ++j)
			{
				maxmn[i][j] = 0;
			}
			maxmn[0][i] = maxmn[i][0] = unp[chx[i][x]][chx[i][x]];
		}
		for(int p=dbeg[x]; p; p=dnxt[p])
		{
			pi[p].ln = chn[x][pi[p].l];
			pi[p].rn = chn[x][pi[p].r];
			pi[p].monn = unp[chx[pi[p].ln][x]][pi[p].l] + unp[chx[pi[p].rn][x]][pi[p].r] + 1;
			chkmax(maxmn[pi[p].ln][pi[p].rn],pi[p].monn);
			chkmax(maxmn[pi[p].rn][pi[p].ln],pi[p].monn);
		}
		for(int i=0; i<(1<<cx); ++i)
		{
			pdp[i] = 0;
		}
		for(int i=0; i<(1<<cx); ++i)
		{
			for(int p1=1; p1<=cx; ++p1)
			{
				if(i&(1<<(p1-1))) continue;
				for(int p2=1; p2<p1; ++p2)
				{
					if(i&(1<<(p2-1))) continue;
					chkmax(pdp[i|(1<<(p1-1))|(1<<(p2-1))], pdp[i]+maxmn[p1][p2]);
				}
				chkmax(pdp[i|(1<<(p1-1))], pdp[i]+maxmn[0][p1]);
			}
		}
		int maxx = (1<<cx)-1;
		for(int i=1; i<=dn; ++i)
		{
			if(chn[x][i])
			{
				unp[x][i] = pdp[maxx^(1<<(chn[x][i]-1))] + unp[chx[chn[x][i]][x]][i];
			}
			else
			{
				unp[x][i] = pdp[maxx];
			}
		}
	}
	else
	{
		memset(unp[x],0,sizeof(unp[x]));
	}
}

void init()
{
	memset(beg,0,sizeof(beg));
	memset(chn,0,sizeof(chn));
	memset(dbeg,0,sizeof(dbeg));
	top = dtop = tratop = 0;
}

int main()
{
	for(int i=2; i<=2000; ++i)
	{
		log2[i] = log2[i>>1]+1;
	}
	int T;
	scanf("%d",&T);
	while(T--)
	{
		init();
		
		int n;
		scanf("%d",&n);
		for(int i=1; i<n; ++i)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			addedge(a,b);
			addedge(b,a);
		}
		
		dn = n;
		dfs(1);
		buildst(n*2-1,travbi);
		
		int m;
		scanf("%d",&m);
		for(int i=1; i<=m; ++i)
		{
			int a,b;
			scanf("%d%d",&a,&b);
			int lca = queryst(dfn[a],dfn[b]);
			addparad(lca,(parad){a,0,b,0,0});
		}
		
		dp(1);
		
		printf("%d\n",unp[1][1]);
	}
}
```

---

## 作者：AxDea (赞：3)

考虑每一条路径 $(u, v)$ ，在其 LCA 处创造贡献。

设 $dp_u$ 表示以 $u$ 为根节点的子树的最优解，$f_{u, v}$ 表示以 $u$ 为子树时，去掉 $(u,v)$ 这一整条路径的最优贡献。

那么有
$$
f_{u, v} = f_{w'_v, v} + sum_{u, w'_v}
$$
其中 $w$ 表示 $u$ 的子节点， $w'_v$ 表示在 $(u, v)$ 这条路径上的一个 $w$ ， $sum_{u, w_v'}$ 表示去掉这个 $w'_v$ 子树时对于 $u$ 子树的最优解。

考虑每个路径对 $dp_{lca}$ 的贡献，就是 $f_{w'_u, u} + f_{w'_v, v} + 1$ ，当然，如果有根节点为 $w$ 的子树没有路径有贡献，那么贡献就为 $dp_w$ 。

显然，两路径若不能同时出现时，两条路径的四个端点不能有两个出现在同一个子树中。

由于每个点的度数很小，可以直接暴力状压 DP ，枚举每个子树的状态和每条路径，这样总复杂度是 $\mathcal{O}(m 2 ^ d)$ ，在最不科学的时候可以达到 $5\times 10 ^ 8$ 还大的级别，非常玄。

可以改变一下枚举对象，每次枚举两个子树，若两个子树中分别有点能连成一条链相连，就可以取其中最大值转移了，时间复杂度变成了 $\mathcal{O}(\sum d_u ^ 2 2 ^ d)$ ，在极为不科学的情况下，可以达到 $10 ^ 8$ ，可以卡过。

发现状压 DP 顺便解决了上述 $sum$ 的问题，问题得到解决。

由于查询 LCA 的次数是 $\mathcal{O} (n ^ 2)$ 级别的，所以用 ST 表求 LCA 的效率更高。

时间复杂度 $\mathcal{O}(n\log n + n ^ 2 + m + \sum d_u^ 2 2 ^ d) = \mathcal{O}(n ^ 2 + \sum d_u^ 2 2^d)$ 。

---

## 作者：dengchengyu (赞：1)

### [P4757 [CERC2014] Parades](https://www.luogu.com.cn/problem/P4757)

模拟赛场切的一道题。

由于贪心不可做，所以考虑 DP，首先想设 $f_x$ 表示子树 $x$ 内最多选多少条路径。

那么考虑把路径挂在 LCA 上选，对于当前点 $x$，对于一条路径 $(u,v)$ 满足 $\text{LCA}(u,v)=x$，选这条路径的贡献就是 $f_u+f_v+1$ 再加上这条路径上挂着的那些子树的贡献。

除此之外选路径 $(u,v)$ 还要满足 $x$ 的在 $u$ 和 $v$ 方向上的边没有选，于是我们改进状态，加入状态压缩，设 $f_{x,S}$ 表示选了儿子集合 $S$ 的答案。

我们可以先用这些路径初始化 $f$，然后再 $3^{10}$ 枚举子集合并 $f$。

最后的问题如何算路径的贡献，有了状态压缩的 $f$ 后就很容易做这个问题，对于 $x,fa_x$，我们只要把 $f_{fa_x,U-x}$ 加到 $x$ 的子树中即可，其中 $U$ 表示全集。

可以使用树状数组运用差分做子树加、单点查。

时间复杂度 $O(3^{d}n+(m+n)\log n)$，其中 $d$ 为节点的度数。

代码：

```cpp
const int N=1005;
int n,m,dfn1,dfn[N],top[N],son[N],sz[N],dep[N],fa[N],lst[N];
vi g[N];
vp q[N];
void dfs1(int x,int y) {
	sz[x]=1, fa[x]=y, dep[x]=dep[y]+1;
	for(int v:g[x]) {
		if(v==y) continue;
		dfs1(v,x);
		sz[x]+=sz[v];
		if(sz[v]>sz[son[x]]) son[x]=v;
	}
}
void dfs2(int x) { 
	dfn[x]=++dfn1;
	if(son[fa[x]]==x) top[x]=top[fa[x]];
	else top[x]=x;
	if(son[x]) dfs2(son[x]);
	for(int v:g[x]) {
		if(v!=son[x] && v!=fa[x]) dfs2(v);
	}
	lst[x]=dfn1;
}
int lca(int x,int y) {
	while(top[x]!=top[y]) {
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y]) return y;
	return x;
}
#define lowbit(x) (x&(-x))
struct BIT{
	int s[N];
	void add(int x,int y) {
		while(x<=n) s[x]+=y,x+=lowbit(x);
	}
	int query(int x) {
		int res=0;
		while(x) res+=s[x],x-=lowbit(x);
		return res;
	}
}bit;
int num[N],f[1024],a[N];
void solve(int x) {
	for(int v:g[x]) {
		if(v==fa[x]) continue;
		solve(v);
	}
	int tot=0;
	for(int v:g[x]) {
		if(v==fa[x]) continue;
		num[v]=tot++;
	}
	fu(i,0,1<<tot) f[i]=0;
	for(int v:g[x]) if(v!=fa[x]) f[1<<num[v]]=a[v]; 
	for(auto i:q[x]) {
		int u=0,v=0;
		if(i.fi!=x) for(auto j:g[x]) {
			if(j==fa[x]) continue;
			if(dfn[i.fi]>=dfn[j]&&dfn[i.fi]<=lst[j]) {u=1<<num[j]; break;}
		}
		if(i.se!=x) for(auto j:g[x]) {
			if(j==fa[x]) continue;
			if(dfn[i.se]>=dfn[j]&&dfn[i.se]<=lst[j]) {v=1<<num[j]; break;}
		}
		f[u|v]=max(f[u|v],bit.query(dfn[i.fi])+bit.query(dfn[i.se])+a[i.fi]+a[i.se]+1);
	}
	fu(i,0,1<<tot) for(int j=i;j;j=(j-1)&i) {
		f[i]=max(f[i],f[j]+f[i^j]);
	}
	a[x]=f[(1<<tot)-1];
	for(int v:g[x]) {
		if(v==fa[x]) continue;
		int t=f[((1<<tot)-1)^(1<<num[v])];
		bit.add(dfn[v],t), bit.add(lst[v]+1,-t);
	}
}
signed main(){
	int Test=0;
	read(Test);
	while(Test--){
	read(n);
	fo(i,1,n) g[i].clear(), son[i]=0, bit.s[i]=0, a[i]=0, q[i].clear();
	dfn1=0;
	fu(i,1,n) {
		int u,v; read(u,v);
		g[u].pb(v), g[v].pb(u);
	}
	dfs1(1,0); dfs2(1);
	read(m);
	fo(i,1,m) {
		int u,v; read(u,v);
		q[lca(u,v)].pb({u,v});
	}
	solve(1);
	write(a[1],'\n');
	}
	return 0;
}
```

---

