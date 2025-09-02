# Shopping

## 题目描述

马上就是小苗的生日了，为了给小苗准备礼物，小葱兴冲冲地来到了商店街。商店街有 $n$ 个商店，并且它们之间的道路构成了一棵树的形状。

第 $i$ 个商店只卖第 $i$ 种物品，小苗对于这种物品的喜爱度是 $w_i$，物品的价格为 $c_i$，物品的库存是 $d_i$。但是商店街有一项奇怪的规定：如果在商店 $u,v$ 买了东西，并且有一个商店 $p$ 在 $u$ 到 $v$ 的路径上，那么必须要在商店 $p$ 买东西。小葱身上有 $m$ 元钱，他想要尽量让小苗开心，所以他希望最大化小苗对买到物品的喜爱度之和。

这种小问题对于小葱来说当然不在话下，但是他的身边没有电脑，于是他打电话给同为OI选手的你，你能帮帮他吗？



## 说明/提示

#### 数据规模与约定

对于全部的测试点，保证 $1\leq n\le 500$，$1\le m\le 4000$，$1\le T \le 5$，$0\le w_i\le 4000$，$1 \leq c_i \leq m$，$1\le d_i\le 2000$。

#### 说明

题目来源：BZOJ4182。

## 样例 #1

### 输入

```
1
3 2
1 2 3
1 1 1
1 2 1
1 2
1 3```

### 输出

```
4```

# 题解

## 作者：lhm_ (赞：21)

考虑若连通块必须包含 $x$，那么就对以 $x$ 为根的有根树做树形背包。

设 $f_{i,j}$ 为考虑了 $dfs$ 序中 $[i,n]$ 对应的节点，体积为 $j$ 的最大价值。转移分两种情况：一个是选 $i$ 对应的节点，然后对该节点的物品跑多重背包，我这里用的是二进制拆分来优化。另一个是不选 $i$ 对应的节点，然后从该节点子树外转移过来，这里可以在 $dfs$ 序上表示转移的位置。

连通块不包含 $x$ 的情况可以用点分治来递归处理。

复杂度为 $O(nm\log d\log n)$。

```cpp
#include<bits/stdc++.h>
#define maxn 1010
#define maxm 4010
using namespace std;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int T,n,m,ans,tot,root,cnt;
int w[maxn],c[maxn],d[maxn],f[maxn][maxm],siz[maxn],mx[maxn],out[maxn],rev[maxn];
bool vis[maxn];
struct edge
{
    int to,nxt;
}e[maxn];
int head[maxn],edge_cnt;
void add(int from,int to)
{
    e[++edge_cnt]={to,head[from]},head[from]=edge_cnt;
}
struct node
{
    int v,w;
}p[maxn];
void dfs_root(int x,int fa)
{
    siz[x]=1,mx[x]=0;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(vis[y]||y==fa) continue;
        dfs_root(y,x),siz[x]+=siz[y];
        mx[x]=max(mx[x],siz[y]);
    }
    mx[x]=max(mx[x],tot-siz[x]);
    if(mx[x]<mx[root]) root=x;
}
void dfs_dfn(int x,int fa)
{
    rev[++cnt]=x;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(vis[y]||y==fa) continue;
        dfs_dfn(y,x);
    }
    out[x]=cnt;
}
void solve(int x)
{
    vis[x]=true,cnt=0,dfs_dfn(x,0);
    for(int i=cnt;i;--i)
    {
        int s=d[rev[i]]-1,num=0;
        for(int j=1;j<=s;s-=j,j<<=1) p[++num]={w[rev[i]]*j,c[rev[i]]*j};
        if(s) p[++num]={w[rev[i]]*s,c[rev[i]]*s};
        for(int j=m;j>=c[rev[i]];--j) f[i][j]=f[i+1][j-c[rev[i]]]+w[rev[i]];
        for(int k=1;k<=num;++k)
            for(int j=m;j>=p[k].w;--j)
                f[i][j]=max(f[i][j],f[i][j-p[k].w]+p[k].v);
        for(int j=0;j<=m;++j) f[i][j]=max(f[i][j],f[out[rev[i]]+1][j]);
    }
    ans=max(ans,f[1][m]);
    for(int i=1;i<=cnt;++i)
        for(int j=0;j<=m;++j)
            f[i][j]=0;
    int now=tot;
    for(int i=head[x];i;i=e[i].nxt)
    {
        int y=e[i].to;
        if(vis[y]) continue;
        root=0,tot=siz[y];
        if(siz[y]>siz[x]) tot=now-siz[x];
        dfs_root(y,x),solve(root);
    }
}
void clear()
{
    edge_cnt=root=ans=0;
    memset(vis,0,sizeof(vis));
    memset(head,0,sizeof(head));
}
int main()
{
    read(T);
    while(T--)
    {
        clear(),read(n),read(m);
        for(int i=1;i<=n;++i) read(w[i]);
        for(int i=1;i<=n;++i) read(c[i]);
        for(int i=1;i<=n;++i) read(d[i]);
        for(int i=1;i<n;++i)
        {
            int x,y;
            read(x),read(y);
            add(x,y),add(y,x);
        }
        tot=mx[0]=n,dfs_root(1,0),solve(root),printf("%d\n",ans);
    }
    return 0;
}
```

---

## 作者：chenxia25 (赞：19)

一个很不寻常的题啊。

首先容易发现题目说的就是所有至少买了一个的点必须构成连通块。考虑在树上跑背包，那必须是有根的。随便设 $1$​ 为根，然后规定若 $x$​ 选了，则 $x$​ 的所有祖先都必须选，这样随后调用 $1$​ 的 DP 数组即可得到必须选 $1$ 时的答案。设 $dp_{i,j}$ 为子树 $i$ 内花了不超过 $j$ 元钱得到的最大收益，转移的时候将若干儿子树的 DP 数组合并起来，然后将 $i$ 加入。这样你会发现，根本不需要令每个点为根跑一遍，因为一个连通块在有根树上的最浅点是唯一的，直接枚举所有点 $x$ 作为最浅点，答案就是它的 $dp_{x,m}$，max 起来即可。

这个树形背包跟普通的复杂度可以分析到 $\mathrm O(nm)$ 的不同，这玩意是基于值域的，背包大小并没有和 size 取 min，每次合并是严格 $\mathrm O\!\left(m^2\right)$ 的，总复杂度是 $\mathrm O\!\left(nm^2\right)$，接受不了。注意到将 $i$ 加入这个操作实际上是多重背包加入一个元素，可以用单调队列优化到 $\mathrm O(m)$，然并卵！毕竟复杂度瓶颈在于背包的「合并」。

我们现在认为必须要根除背包的合并操作。此时引出一个科技：树上依赖性背包。问题就是说在有根树上，$x$​ 选了则必须选所有祖先的一个背包，无论是 01 还是完全还是多重。这玩意除了上述的暴力合并背包的 DP 做法，还有个比较妙的不带合并操作的 DP 做法。  
我们考虑像一个新的 DP 题一样从头开始考虑：一开始的局面是 $1\sim n$​ 所有点未决策，现在考虑决策 $1$​。如果不选 $1$​ 那就直接结束走人吧！否则剩下 $2\sim n$​ 需要决策，做完之后返回一个背包再将 $1$​ 插入。现在问题转化为 $2\sim n$​。注意到这里的精髓：我们并没有将 $2\sim n$​ 拆成若干儿子树再合并，而是直接当做一个整体！毕竟它本来就是一个整体，为啥要拆开再合并呢？（普通树形 DP 这么做是因为不会有「合并复杂度大，插入复杂度小」这样奇怪的事情发生，在这个前提下每个子树作为子问题显然是好理解的）  
现在假设 $2$​ 是 $1$​ 的儿子，对 $2$​ 进行决策。如果选的话那就 $3\sim n$​ 走起；否则剩下 $\{2\sim n\}-\mathrm{subt}(2)$​。对后者下一步应该选 $1$​ 的下一个儿子对吧这很自然。对前者呢？如果也选 $1$​ 的下一个儿子，那么得到的状态就是 $V$​​ 去掉一个儿子树再去掉一个儿子树的根？？？这状态就显得支离破碎，没法封闭。接下来官方给出的下一步决策的方案是这个算法的精髓：选 $3\sim n$​ 中 dfn 最小的。就假设 $dfn_i=i$​ 吧，如果选的话转化到 $4\sim n$​，否则去除 $\mathrm{subt}(3)$​，而注意到 $3$​ 子树里的点都大于 $3$​，而且是连续的，所以是 $3\sim n$​ 的前缀，去掉之后得到 $1\sim n$​ 的某个后缀。这样我们只要对每个状态都对 dfn 最小的点进行决策，转移到的状态就可以封闭在「dfn 后缀」这仅仅 $\mathrm O(n)$​​ 个状态里，而且每次转移都是加入一个点的操作。

通过上述科技，我们可以用单调队列在 $\mathrm O(nm)$ 时间内计算出连通块必须包含 $1$ 的答案。但这样一个坏处是不能顺便得到连通块最浅节点为其它点的答案了。那难道要对每个点都跑一遍吗？这样是 $\mathrm O\!\left(n^2m\right)$，虽然比原来的做法优，但还是过不去。不难发现，考虑过包含 $1$ 的情况，剩下不包含 $1$ 的情况，这样必须在 $1$ 的若干个儿子树的其中之一，就转化为了子问题，递归下去。可以用点分治来限制层数，达到 $\mathrm O(nm\log n)$。这里点分治不再是统计路径，而是统计连通块，也很自然对吧？

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define pb push_back
const int inf=0x3f3f3f3f3f3f3f3f;
const int N=510,M=4010;
int n,m;
int v[N],w[N],lim[N];
vector<int> nei[N];
bool vis[N];
int dfn[N],mxdfn[N],nowdfn,mng[N];
void dfs(int x,int fa=0){
	mng[dfn[x]=mxdfn[x]=++nowdfn]=x;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];if(y==fa||vis[y])continue;
		dfs(y,x);
		mxdfn[x]=mxdfn[y];
	}
}
int dp[N][M];
int q[M],head,tail;
int ans;
int sz[N],mxsz[N];
bool cmp(int x,int y){return mxsz[x]<mxsz[y];}
int gtrt(int x=1,int tot=n,int fa=0){
	sz[x]=1,mxsz[x]=0;
	int rt=0;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];if(y==fa||vis[y])continue;
		rt=min(rt,gtrt(y,tot,x),cmp);
		sz[x]+=sz[y],mxsz[x]=max(mxsz[x],sz[y]);
	}
	mxsz[x]=max(mxsz[x],tot-sz[x]);
	return min(rt,x,cmp);
}
void cdq(int x){
	nowdfn=0,dfs(x);
	memset(dp[nowdfn+1],0,sizeof(dp[0]));
	for(int i=nowdfn;i;i--){
		int u=mng[i];
		for(int j=0;j<=m;j++)dp[i][j]=dp[mxdfn[u]+1][j];
		for(int j=0;j<w[u]&&j<=m;j++){
			head=tail=0;
			for(int k=j;k<=m;k+=w[u]){
				if(k>=w[u]){
					while(head<tail&&dp[i+1][q[tail-1]]-q[tail-1]/w[u]*v[u]<=dp[i+1][k-w[u]]-(k-w[u])/w[u]*v[u])tail--;
					q[tail++]=k-w[u];
				}
				while(head<tail&&(k-q[head])/w[u]>lim[u])head++;
				if(head<tail)dp[i][k]=max(dp[i][k],dp[i+1][q[head]]+(k-q[head])/w[u]*v[u]);
			}
		}
	}
	ans=max(ans,dp[1][m]);
	vis[x]=true;
	for(int i=0;i<nei[x].size();i++){
		int y=nei[x][i];if(vis[y])continue;
		cdq(gtrt(y,sz[y]));
	}
}
void mian(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)nei[i].clear();
	for(int i=1;i<=n;i++)scanf("%lld",v+i);
	for(int i=1;i<=n;i++)scanf("%lld",w+i);
	for(int i=1;i<=n;i++)scanf("%lld",lim+i);
	for(int i=1;i<n;i++){
		int x,y;
		scanf("%lld%lld",&x,&y);
		nei[x].pb(y),nei[y].pb(x);
	}
	memset(vis,0,sizeof(vis));
	ans=0,cdq(gtrt());
	cout<<ans<<"\n";
}
signed main(){mxsz[0]=inf;
	int t;
	cin>>t;
	while(t--)mian();
	return 0;
}
```


---

## 作者：耳朵龙_ (赞：10)

提供一个非点分治做法。

多重背包插入一个元素是 $O(m)$ 的，而合并是 $O(m^2)$ 的，如果使用一般的树形 dp 方法复杂度是 $O(nm^2)$，过不去，考虑把合并改为插入以降低复杂度。

与一般的树形 dp 类似，记 $f_{i,j}$ 表示仅考虑 $i$ 的子树内的元素，且选的元素构成一个包含 $i$ 的连通块（为了方便，一个物品也不选也是合法状态），背包容量为 $j$ 时能获得的最大价值。相当于选择时若选择某元素则必须选其父亲（前提是其父亲位于 $i$ 子树内）。

设 $son_x$ 为 $x$ 的重儿子，$nfd_x$ 为 dfn 为 $x$ 的点的编号，$sz_x$ 为 $x$ 子树内点数。虽然合并是做不了了，但是继承一个子树的信息是可以的。直接继承 $f_{son_x}$，然后暴力插入轻子树内的元素即可，即启发式合并。插入时做法与其他题解相同，但是只考虑 $x$ 子树内元素。

具体地，在 dfs 时最后进入重子树，使重儿子 dfn 最大，记 $g_{i,j}$ 表示考虑了 $x$ 子树内 dfn 不小于 $i$ 的元素，且这些元素构成的森林中，若选了某元素则必选其父亲（前提是其父亲 dfn 不小于 $i$），背包容量为 $j$ 时能获得的最大价值。讨论 $nfd_i$ 处的元素选不选，可分别从 $g_{i+1}$ 和 $g_{i+sz_{nfd_i}}$ 处转移，方程不再赘述。注意到在计算重儿子 $son_x$ 子树外的信息时，最多只会访问 $g_{dfn_{son_x}}$ 而不关心 $son_x$ 子树内其他结点的 $g$ 值，而 $g_{dfn_{son_x}}$ 等于 $f_{son_x}$，直接将 $f_{son_x}$ 复制过来然后计算 $i<dfn_{son_x}$ 的 $g_i$ 即可。

$f_i$ 是选择的连通块的根恰为 $i$ 时各容量的最大价值，将所有 $f_{i,m}$ 取 $\max$ 即为答案。

时间复杂度 $O(Tnm\log n)$，常数小。

代码（由于不如某些二进制分组的劣复杂度点分治短，一气之下压了下行）：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505,M=4005;
int T,n,m,w[N],c[N],d[N],sz[N],son[N],dfn[N],nfd[N],tim,ans,f[N][M];
vector<int>E[N];
void dfs(int x,int pr){
	sz[x]=1,son[x]=0;
	for(int y:E[x])
		if(y^pr&&(dfs(y,x),sz[x]+=sz[y],sz[y]>sz[son[x]]))
			son[x]=y;
}
void dsu(int L,int R){
	static int q[M],g[N][M];
	memcpy(g[R+1],f[nfd[R+1]],m+1<<2);
	for(int i=R,x;i>=L;--i){
		if(x=nfd[i],i>L) memcpy(g[i],g[i+sz[x]],m+1<<2);
		else memset(g[i],0,m+1<<2);
		for(int k=0;k<c[x];++k)
			for(int j=k,l=0,r=-1,t=0;j<=m;j+=c[x],++t){
				l+=l<=r&&t-q[l]>d[x];
				if(t) g[i][j]=max(g[i][j],g[i+1][q[l]*c[x]+k]+(t-q[l])*w[x]);
				while(l<=r&&g[i+1][q[r]*c[x]+k]-q[r]*w[x]<=g[i+1][t*c[x]+k]-t*w[x]) --r;
				q[++r]=t;
			}
	}
	memcpy(f[nfd[L]],g[L],m+1<<2);
}
void calc(int x,int pr){
	nfd[dfn[x]=++tim]=x;
	for(int y:E[x]) if(y^pr&&y^son[x]) calc(y,x);
	if(son[x]) calc(son[x],x),dsu(dfn[x],dfn[son[x]]-1);
	else for(int i=0,t=0;i<=m;++i) f[x][i]=w[x]*(t+=t<d[x]&&(t+1)*c[x]<=i);
	ans=max(ans,f[x][m]);
}
void work(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;++i) scanf("%d",&w[i]);
	for(int i=1;i<=n;++i) scanf("%d",&c[i]);
	for(int i=1;i<=n;++i) scanf("%d",&d[i]);
	for(int i=1,u,v;i<n;++i) scanf("%d%d",&u,&v),E[u].push_back(v),E[v].push_back(u);
	dfs(1,1),calc(1,1),printf("%d\n",ans),ans=tim=0;
	for(int i=1;i<=n;++i) E[i].clear();
}
int main(){
	for(scanf("%d",&T);T--;work()) ;
	return 0;
}
```

---

## 作者：MoonCake2011 (赞：6)

这题有亿点点难。

在大佬写的题解的指引下，我写了树上启发式合并。

~~不许食用淀粉质~~。

当时条淀粉质调了很久，留下了很大的心理阴影。

刚好听说此算法很~~暴力，好写~~，于是正好~~练练手~~。

这边会讲解一些误区与细节。

## 大概思路 

设 $dp_{i,j}$ 为在 $i$ 的子树中，钱数为 $j$，选择一个点就必选父亲的最大喜爱度。

答案为 $\max dp_{i,m}$。

能~~感性理解~~简单证明这能覆盖所有方案。

那就设 $1$ 为根。

### 一，树上启发式合并

先讲树上启发式合并，就是有些计算需要子树的信息的。

那么我们可以保留最大子树的信息。

其他子树暴力求，可以做到 $O(n\log n)$。

证明同重链剖分。

### 二，树上多重背包优化 

普通的树上多重背包需要分配 $i$ 的子树的钱，与在那些钱里分配给 $i$ 儿子的子树的钱。

时间复杂度 $O(m^2)$。

总共 $O(nm^2)$，直接爆炸。

我们尝试将以上的合并操作变为~~树上启发式合并能解决的~~插入操作。

对于每个所有子树，将它们的 dfs 序跑出来，好解决一点（树化序列）。

设那个点为 $x$。

因为必选父亲，所以考虑沿着 dfs 序倒着枚举。

设 $f_{i,j}$ 为在 $x$ 子树内，一个 dfs 序为 $i$ 的点，到 $x$ 子树内 dfs 序最大的点，分配 $j$ 块钱的总价值。

首先，必选父亲，所以先尝试从其他子树转移。

于是首先对于 $0\le k \le m$，$f_{i,k}=f_{i+size_i,k}$。

$size_i$ 为那个点的子树大小。

如果 $i+size_i$ 或者 $i+1$ 超过了 $x$ 的子树，那么将 $f_{i+size_i}$ 或者 $f_{i+1}$ 全设为 $0$，每次 dp 完清空就可以实现了。

怎么解决必选父亲的问题，那我们让父亲必须选不就行了。（废话）

首先，dfs 序为 $i$ 的与 $i+1$ 的要么是父子，要么是子树结尾与开头。

如果是父子，那么我们不像普通的背包。

我们让父亲如果不选，就不继承 $f_{i+1,j}$ 的遗产。

那就是枚举每种多重背包的策略 $1\le p\le d_k$，去直接从 $f_{i+1,j}$ 转移，而不枚举 $0$。

这样不就好了吗，不选，你儿子的贡献就没了，满足。

对于第二类情况，相当于继承了那个子树呗。

啊，那这不就是正确的吗？

最后，在背包中加入 $x$，从 dfs 序最小的点（一个为 $x$ 的儿子）按原方法转移过来。

这样最后转移到的 $f$ 数组就是 $dp_x$ 这个一维数组的答案。

于是，玩一手单调队列优化，时间复杂度 $O(n^2m)$。（怎么感觉有点像从 EK 优化到 Dinic）

### 三，对二进制优化证伪

先放一放继续~~用树上启发式合并~~优化的念头。

这里有需要注意的点，**不能用二进制优化**。

首先来证明一个东西，二进制优化的拆分，只会计算到那几个拆分数的贡献。

很好证，每个拆分数是直接从上一个 dp 数组转移，而没有继承。

所以不能形成和的匹配，直接没掉。

这就使得贡献没有**可合并性**。

~~你看莫队都能不删除了，要不来一个多重背包不合并吧~~。

如果要使这完成和的匹配这一步，其实也可以，但感觉实现起来很麻烦，还不如直接用单调队列。

### 四，树上启发式合并优化

终于来了，我们想一下，$x$ 的最后一个子树的 $f$ 数组是等于它的 $dp$ 数组的。

哦，我的~~上帝~~天哪！

我们让最后一个子树枚举到重儿子。

那么就可以直接在算 $f$ 数组时排掉枚举重儿子的子树的时间。

那时间复杂度 $O(nm\log n)$。

代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int head[510],to[1010],nxt[1010],tot;
inline void add(int u,int v){
	to[++tot]=v;
	nxt[tot]=head[u];
	head[u]=tot;
}
int w[510],v[510],d[510];
int siz[510],son[510];
void dfs(int x,int fa){
	siz[x]=1;
	for(int i=head[x];i;i=nxt[i]){
		if(to[i]==fa) continue;
		dfs(to[i],x);
		siz[x]+=siz[to[i]];
		if(siz[son[x]]<siz[to[i]]) son[x]=to[i];
	}
}
int dp[510][4010],f[510][4010],dfn[510],idx;
int e[510],q[4010];
void DP(int l,int r){
	int head,tail;
	for(int i=0;i<=m;i++) f[r+1][i]=dp[e[r+1]][i];//r+1 就是重儿子
	for(int i=r;i>=l;i--){
		int x=e[i];
		for(int j=0;j<=m;j++) f[i][j]=f[i+siz[x]][j];//继承子树 
		int num=d[x];
//		for(int j=1;j<=num;j++) for(int k=m;k>=w[x]*j;k--) f[i][k]=max(f[i][k],f[i+1][k-w[x]*j]+v[x]*j);//暴力
		for(int j=0;j<w[x];j++){//单调队列优化，不多说 
			head=1,tail=0;
			for(int k=j;k<=m;k+=w[x]){
				if(head<=tail && q[head]<k-w[x]*d[x]) head++;
				if(head<=tail) f[i][k]=max(f[i][k],f[i+1][q[head]]+(k-q[head])/w[x]*v[x]);
				while(head<=tail && f[i+1][k]>=f[i+1][q[tail]]+(k-q[tail])/w[x]*v[x]) tail--;
				q[++tail]=k;
			} 
		}
	}
	int i=l-1;//l-1 就是 x 
	int x=e[l-1];
	int num=d[x];//转移 
//	for(int j=1;j<=num;j++) for(int k=m;k>=w[x]*j;k--) f[i][k]=max(f[i][k],f[i+1][k-w[x]*j]+v[x]*j);
	for(int j=0;j<w[x];j++){
		head=1,tail=0;
		for(int k=j;k<=m;k+=w[x]){
			if(head<=tail && q[head]<k-w[x]*d[x]) head++;
			if(head<=tail) f[i][k]=max(f[i][k],f[i+1][q[head]]+(k-q[head])/w[x]*v[x]);
			while(head<=tail && f[i+1][k]>=f[i+1][q[tail]]+(k-q[tail])/w[x]*v[x]) tail--;
			q[++tail]=k;
		} 
	}
	for(int i=0;i<=m;i++) dp[x][i]=f[l-1][i];//统计回来 
}
int ans;
void dfs2(int x,int fa){
	dfn[x]=++idx,e[idx]=x;//计算 dfs 序，与 dfs 序所对应的编号 
	for(int i=head[x];i;i=nxt[i]){//枚举所有轻儿子并计算 
		if(to[i]==fa || to[i]==son[x]) continue;
		dfs2(to[i],x);
	}
	if(son[x]){//不是叶子节点，有重儿子
		dfs2(son[x],x);
		DP(dfn[x]+1,dfn[son[x]]-1);//转移非重儿子的子树内的所有点  
	}
	else for(int i=0;i<=m;++i) dp[x][i]=(i/w[x]<=d[x] ? i/w[x]*v[x] : d[x]*v[x]);//否则计算叶子节点的贡献（简单）
	ans=max(ans,dp[x][m]);//统计答案
}
void solve(){
	ans=0,idx=0;//多测不清空，爆零两行泪 
	memset(head,0,sizeof head);
	memset(to,0,sizeof to);
	memset(nxt,0,sizeof nxt);
	memset(dp,0,sizeof dp);
	memset(f,0,sizeof f);
	memset(son,0,sizeof son);
	tot=0;
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>v[i];
	for(int i=1;i<=n;i++) cin>>w[i];
	for(int i=1;i<=n;i++) cin>>d[i];
	for(int i=1;i<n;i++){
		int u,v;
		cin>>u>>v;
		add(u,v),add(v,u);
	}
	dfs(1,0);//处理子树大小，重儿子等基本信息 
	dfs2(1,0);//开始 dp
	cout<<ans<<"\n";
}
int main() {
	int t;
	cin>>t;
	while(t--) solve();
	return 0;
} 
//1
//5 10
//1 2 3 4 5
//1 3 2 5 4
//5 4 3 2 1
//1 2
//1 3
//2 4
//2 5
```
~~能不用淀粉质，就不用淀粉质，从我做起~~。

## 附录 

### 单调队列优化多重背包

[模板](https://www.luogu.com.cn/problem/P1776)。

虽然此题可以用二进制优化，但是用单调队列也做一下。

首先，先看朴素 01 背包。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int v[100010],w[100010],d[100010];
int dp[100010],f[100010],q[100010],head,tail;
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>v[i]>>w[i]>>d[i];
	for(int i=1;i<=n;i++){
	    for(int j=m;j>=w[i];j--)
	        for(int k=0;k<=d[i] && k*w[i]<=j;k++) dp[j]=max(dp[j],dp[j-k*w[i]]+k*v[i]);
	}
	cout<<dp[m];
	return 0;
}
```
发现，对于每个 $j$ 取模 $w_i$ 的余数相同的数才能转移。

而这又变成一个单调队列优化 dp 的板子题了。

注意单调队列优化 dp 需要从小枚举到大。

所以需要辅助数组。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int v[100010],w[100010],d[100010];
int dp[100010],f[100010],q[100010],head,tail;
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>v[i]>>w[i]>>d[i];
	for(int i=1;i<=n;i++){
		for(int i=0;i<=m;i++) f[i]=dp[i];//记录到辅助数组里 
		for(int j=0;j<w[i];j++){
			head=1,tail=0;
			for(int k=j;k<=m;k+=w[i]){
				if(head<=tail && q[head]<k-w[i]*d[i]) head++;//滑窗模板 
				if(head<=tail) dp[k]=max(dp[k],f[q[head]]+(k-q[head])/w[i]*v[i]);
				while(head<=tail && f[k]>=f[q[tail]]+(k-q[tail])/w[i]*v[i]) tail--;
				q[++tail]=k;
			} 
		}
	}
	cout<<dp[m];
	return 0;
}
```
因为单调队列优化 dp 除法太多了，所以跑不过二进制优化。

再次贴出二进制优化。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int dp[int(4e4)+10];
int v[110],w[110],num[110];
int main() {
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		cin>>v[i]>>w[i]>>num[i];
	for(int i=1;i<=n;i++){
		int d=num[i];
		for(int j=1;j<=d;j<<=1){
			for(int k=m;k>=w[i]*j;k--)
				dp[k]=max(dp[k],dp[k-w[i]*j]+v[i]*j);
			d-=j;
		}
		for(int k=m;k>=w[i]*d;k--)
			dp[k]=max(dp[k],dp[k-w[i]*d]+v[i]*d);
	}
	cout<<dp[m];
	return 0;
}
```

还有一个问题，就是此题中的单调队列优化与上题有什么区别。

区别就是一个记录了原来的 dp 值，一个没有。

这样在没有转移的时候值就为 $0$，才满足题意。

恭喜你，成功完全搞懂了此题。

---

## 作者：一扶苏一 (赞：5)

## 【点分治 & dp】【P6326】Shopping

### Description

给定一棵树，每个节点有一种物品，价格为 $c_i$，数量为 $d_i$，价值为 $w_i$。请选一些物品，最大化价值和。所选物品所属的的节点必须构成一个连通块。

### Analysis

考虑点分治，建出点分树后对于每个重心统计必过该节点的答案。

如果直接跑树形 dp 的话，在节点处转移是 $O(m^2)$ 的，无法接受。

考虑从重心进行 dfs，一边 dfs 一边 dp 当前节点的答案，在 dp 过程中需要保证该节点到重心的链都至少选了一个物品。

设 $f_{i}$ 是考虑已经遍历过的节点，花了 $i$ 元的最大价值。在遍历到一个节点时，先将已有的 dp 值存储一下，然后在该节点强行选一个物品，对于该节点剩下的物品跑多重背包，然后递归该节点的子节点即可。

当然，也有可能该节点和其子树都不选，所以在回溯时，将每个 dp 值都与进入该节点是存储的 dp 值取个 max 即可。

考虑复杂度：遍历节点的复杂度是 $O(n \log n)$，dp 过程是一个多重背包，朴素做的复杂度是 $O(nm \log n \max d)$，单调队列优化的复杂度是 $O(nm \log n)$，代码里选择的是二进制分组，复杂度 $O(nm \log n \log d)$。

我也不知道为什么屑花的单调队列跑的比我二进制分组还慢好几倍（

### Code

```cpp
const int maxn = 505;
const int maxm = 4005;
const int INF = 0x3f3f3f3f;

void Init();
void Calc();
void Clear();
void Divide();

int main() {
  freopen("1.in", "r", stdin);
  int t;
  for (qr(t); t; --t) {
    Clear();
    Init();
    Divide();
    Calc();
  }
  return 0;
}

int n, m;
int w[maxn], c[maxn], d[maxn];
std::vector<int> e[maxn];

void Init() {
  qr(n); qr(m);
  qra(w + 1, n);
  qra(c + 1, n);
  qra(d + 1, n);
  for (int i = 1, u, v; i < n; ++i) {
    qr(u); qr(v);
    e[u].push_back(v);
    e[v].push_back(u);
  }
}

int sz[maxn], wson[maxn];
bool vis[maxn];
std::vector<int> pit;

void GetSz(const int u) {
  sz[u] = 1;
  vis[u] = true;
  pit.push_back(u);
  wson[u] = 0;
  for (auto v : e[u]) if (vis[v] == false) {
    GetSz(v);
    sz[u] += sz[v];
    if (sz[v] > sz[wson[u]]) wson[u] = v;
  }
  vis[u] = false;
}

int GetRoot(const int rt) {
  pit.clear();
  GetSz(rt);
  int maxs = n, rot = 0;
  for (auto u : pit) {
    int v = std::max(sz[wson[u]], sz[rt] - sz[u] - 1);
    if (v < maxs) {
      rot = u;
      maxs = v;
    }
  }
  return rot;
}

std::vector<int> dtree; // divided tree
void divide(const int u) {
  vis[u] = true;
  dtree.push_back(u);
  for (auto v : e[u]) if (vis[v] == false) {
    int rt = GetRoot(v);
    divide(rt);
  }
}

void Divide() {
  int rt = GetRoot(1);
  divide(rt);
}

int f[maxm], g[maxn][maxm];
void dfs(const int u, int sw) {
  if ((sw += c[u]) > m) return;
  int sm = sw;
  vis[u] = true;
  for (int i = 0; i <= m; ++i) g[u][i] = f[i];
  for (int i = m; i >= sm; --i) f[i] = f[i - c[u]] + w[u];
  for (int i = 0; i < sm; ++i) f[i] = -INF;
  int j = 1, tw = w[u], tc = c[u], sum = j;
  while (sum < d[u]) {
    for (int i = m; (i - tc) >= sw; --i) {
      f[i] = std::max(f[i], f[i - tc] + tw);
    }
    sum += (j <<= 1); tw <<= 1; tc <<= 1;
  }
  if (j != 1) {
    j = d[u] - 1 - (sum - j);
    tw = w[u] * j; tc = c[u] * j;
    for (int i = m; (i - tc) >= sw; --i) {
      f[i] = std::max(f[i], f[i - tc] + tw);
    }
  }
  for (auto v : e[u]) if (vis[v] == false) {
    dfs(v, sw);
  }
  for (int i = 0; i <= m; ++i) f[i] = std::max(f[i], g[u][i]);
  vis[u] = false;
}

void Calc() {
  for (int i = 1; i <= n; ++i) vis[i] = false;
  int ans = 0;
  for (auto u : dtree) {
    for (int i = 0; i <= m; ++i) f[i] = 0;
    dfs(u, 0);
    vis[u] = true;
    for (int i = 1; i <= m; ++i) {
      ans = std::max(ans, f[i]);
    }
  }
  qw(ans, '\n');
}

void Clear() {
  for (int i = 1; i <= n; ++i) {
    vis[i] = false;
    e[i].clear();
  }
  for (int i = 1; i <= m; ++i) f[i] = 0;
  dtree.clear();
}
```



---

## 作者：Melo_DDD (赞：4)

很不一般的好题，感觉有很多比较难搞的点啊，尽量讲得清楚一点吧。

#### 在阅读本题解之前，您需要知道：

1. dfn 序（很多大佬说是 dfs 序，不太明白啊，错了踢我，不影响正确性）。
1. 多重背包及其优化（单调队列或者二进制分解）。
2. 点分治。

首先发现一个性质，就是最终选的所有点在树上一定处于同一个联通块里面，根据题意可得。

我们可以考虑去钦定一个根，规定这个根必须被选，可以用 dp 求出此时的最大答案。具体的，对于这棵有根树的任意节点 $cur$ 而言，有两种情况：

- 如果不选它，那么它的子树里的所有点都不能被选（因为它一定在它后代节点和根的路径上），我们跳到下一个可以考虑的点。
- 如果选它，进入子树中递归求解。

转移显然是一个树上多重背包，设 $dp_{i,j}$ 表示以 $i$ 为根 $i$ 的子树中花费 $j$ 元的最大收益，但是我们发现，不太好啊，正常树形 dp 可以做到 $\Theta(nm)$ 的原因是有子树大小的限制，但是我们这个 dp 状态显然是基于值域而言的啊，所以上下界优化子虚乌有了，复杂度直接 $\Theta(nm^2)$ 已经爆了。而我们肯定没办法更改 dp 数组的意义，只能从优化角度考虑了。

一个常见的技巧是，我们树上背包是劣于序列背包的，所以对于这类问题，可以想办法把它拍成序列上的问题。注意到一个根以及它的后代节点的时间戳在 dfn 序列上一定是连续的一段，可以由此入手。

稍微更改一下 dp 数组的意义，设 $dp_{i,j}$ 表示 dfn 序列上已经枚举完 $[i,n]$ 的点，用了 $j$ 元的最大收益。

那么我们讨论的两中情况可以转化为：
- 如果跳出子树，由 $dp_{i,j}$ 继承 $dp_{i+sz_i,j}$（$sz$ 是子树大小，$i+sz_i$ 即为枚举完点 $i$ 的子树后下一个点的 dfn 序）。
- 如果进入子树，那么 $dp_{i,j}$ 将从 $dp_{i+1,k}$ 转化过来，由于是序列上，可以单调队列优化多重背包（注意至少拿 $1$ 个）。

最后我们要求的答案就是最大的 $dp_{1,j}$（根节点的 dfn 序是 $1$）。复杂度是 $\Theta(nm)$ 的。

但是这里有一个小疑问，首先最优性是可以保证的，但是为啥这样更新出来的 $dp_{1,j}$ 最大的时候能保证取的点在树上一定是一个满足条件的连通块啊？

~~考虑抽象~~，对于一个以 $1$ 开头的序列，如果截止到一个位置 $i$，使得对任意的 $j\in[1,i-1]$，$dp_j$ 都是由 $dp_{j+1}$ 更新过来的话，取的这些点显然构成一个联通块。

那么 $i$ 就是像第一种情况一样，是从子树之外跳着转移过来的，我们注意到，转移时的 $i+siz_i$ 这个点在树上一定是 $i$ 的某位祖先的儿子，不明白可以考虑一下 dfs 的过程。注意 $i$ 的祖先必定属于 $[1,i-1]$，肯定已经在连通块里，那么 $i+sz_{i}$ 肯定也能并到这个连通块里面。

接下来就变成证明以 $i+sz_i$ 开头的序列是否满足条件了，数学归纳一下即可得证。

再想一想，发现，我靠，要是每次去枚举根，是 $\Theta(n^2m)$ 的，一样爆啊，所以再去考虑优化枚举的过程，发现可以点分治，每次枚举重心，以重心为根跑一次上面过程，优化到对数级，正确性肯定是毋庸置疑的吧。

整体复杂度 $\Theta(nm\log n)$。要是二进制优化会多一只 $\log$。

还有一些细节，看代码吧：


```cpp
namespace melo {
	inline void add (int u ,int v) {
		e[++ tot].nxt = head[u] ;
		head[u] = tot ;
		e[tot].to = v ;
	}
	inline void get_wei (int cur ,int fa) {
		sz[cur] = 1 ;
		int maxsz = 0 ;
		for (int i = head[cur] ;i ;i = e[i].nxt) {
			int nex = e[i].to ;
			if (nex == fa || del[nex]) 
				continue ;
			melo :: get_wei (nex ,cur) ;
			sz[cur] += sz[nex] ;
			maxsz = max (maxsz ,sz[nex]) ;
		}
		maxsz = max (maxsz ,nowsz - sz[cur]) ;
		if (minsz > maxsz) {
			rt = cur ;
			minsz = maxsz ;
		}
	} // 简单的找重心过程，rt 开全局变量
	inline void pre (int cur ,int fa) {
		inf[++ cnt] = cur ,sz[cur] = 1 ;
		for (int i = head[cur] ;i ;i = e[i].nxt) {
			int nex = e[i].to ;
			if (nex == fa || del[nex]) 
				continue ;
			melo :: pre (nex ,cur) ;
			sz[cur] += sz[nex] ;
		}
		return (void) (r[cur] = cnt) ;
	} // dfn 序，r 数组就是这棵树最大的那个 dfn 序
	inline void div (int cur) {
		melo :: get_wei (cur ,0) ; // 找到重心
		cnt = 0 ;
		melo :: pre (rt ,0) ; // 以重心为根，重新预处理
		del[rt] = true ; 
		int frt = 0 ,tail = -1 ;
		memset (dp[cnt + 1] ,0 ,sizeof dp[cnt + 1]) ; // 一定要赋值
		for (int i = cnt ;i ;i --) {
			int v = inf[i] ;
			f (j ,0 ,m ,1) 
				dp[i][j] = dp[r[v] + 1][j] ; // r[v] + 1 即是 v + sz[v]
			memcpy (g ,dp[i + 1] ,sizeof g) ; // 副本
			f (j ,0 ,c[v] - 1 ,1) {
				frt = 0 ,tail = -1 ;
				f (k ,0 ,(m - j) / c[v] ,1) {
					while (frt <= tail && k - q[frt] > d[v]) 
						frt ++ ;
					if (frt <= tail) // 判断一下是否可以更新 
						dp[i][j + k * c[v]] = max (dp[i][j + k * c[v]] ,g[j + q[frt] * c[v]] + (k - q[frt]) * w[v]) ; 
					while (frt <= tail && g[j + q[tail] * c[v]] - w[v] * q[tail] <= g[j + k * c[v]] - w[v] * k) 
						tail -- ;
					q[++ tail] = k ;
				}
			}
		}
		f (i ,0 ,m ,1)
			ans = max (ans ,dp[1][i]) ;
		for (int i = head[rt] ;i ;i = e[i].nxt) {
			int nex = e[i].to ;
			if (del[nex]) 
				continue ;
			nowsz = sz[nex] ,minsz = 0x7f7f7f7f ;
			melo :: div (nex) ;
		} // 拆树的过程
	}
} 
signed main () {
	read (t) ;
	while (t --) {
		read (n ,m) ;
		nowsz = n ,minsz = 0x7f7f7f7f ;
		f (i ,1 ,n ,1) 
			read (w[i]) ;
		f (i ,1 ,n ,1) 
			read (c[i]) ;
		f (i ,1 ,n ,1) 
			read (d[i]) ;
		f (i ,1 ,n - 1 ,1) {
			int u ,v ;
			read (u ,v) ;
			melo :: add (u ,v) ;
			melo :: add (v ,u) ;
		}
		melo :: div (1) ;
		cout << ans << '\n' ;
		f (i ,1 ,n ,1)
			w[i] = c[i] = d[i] = 0 ;
		mem (head) ,mem (q) ,mem (del) ,mem (dp) ;
		tot = rt = ans = 0 ;
	}
	return 0 ;
}
```
彩蛋：附避雷小指北。

如果你的单调队列是这么写的：


```cpp
f (j ,0 ,c[v] - 1 ,1) {
	frt = 0 ,tail = -1 ;
	f (k ,0 ,(m - j) / c[v] ,1) {
		while (frt <= tail && k - q[frt] > d[v]) 
			frt ++ ;
		while (frt <= tail && g[j + q[tail] * c[v]] - w[v] * q[tail] <= g[j + k * c[v]] - w[v] * k) 
			tail -- ;
		q[++ tail] = k ;
		if (q[frt] != k)
			dp[i][j + k * c[v]] = max (dp[i][j + k * c[v]] ,g[j + q[frt] * c[v]] + (k - q[frt]) * w[v]) ;
	}
}
```
会挂，可以发现是先弹还是先更新有区别，如果选择先弹再判断，可能会出现，$k$ 前面其实有符合条件的情况，只不过没有那么优，你给它全扔了，于是你错失了更新的机会。

感觉写的挺细的，给个赞和评论不过分吧？

---

## 作者：win114514 (赞：4)

非常好题目。

### 思路

考虑题目需要求一个连通块的背包。

点分治是平凡的，很容易想到，因为要统计的东西恰好可以把树分成几段。

但点分治操作时的背包确实卡了一下。

以前也没有见过这样的做法。

我们考虑如果直接做树上背包的话。

复杂度是绝对受不了的。

因为合并两个多重背包是基于值域的。

无法体现在树上的优势。

这个时候，就可以用一种新的巧妙思路。

1. 我们考虑进入某个节点时，将此时的背包存下来。

2. 然后先强制选一个物品。

3. 再对当前节点做多重背包，可以使用二进制优化。

4. 继续遍历后面的儿子。

5. 离开时将每个值与进入是所存储的值取较小值。

然后发现我们的背包的复杂度惊人的变成了 $O(nm\log v)$。

好像这个东西被称为树上依赖性背包。

个人感觉确实比较巧妙。

最终时间复杂度 $O(nm\log v\log n)$。

### Code

```cpp
/**
 * @file P6326.cpp
 * @author win114514
 * @date 2023-11-24
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <bits/stdc++.h>
using namespace std;

#define x first
#define y second
#define mp(x, y) make_pair(x, y)
#define eb(...) emplace_back(__VA_ARGS__)
#define fro(i, x, y) for(int i = (x);i <= (y);i++)
#define pre(i, x, y) for(int i = (x);i >= (y);i--)
#define dbg cerr << "Line " << __LINE__ << ": "
#define EVAL(x) #x " = " << (x)

typedef int64_t i64;
typedef uint32_t u32;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef pair<int, int> PII;

bool ed;

const int N = 510;
const int M = 4010;
const int mod = 998244353;

int n, m, w[N], c[N], d[N], dp[M];
int rt, rtsz, sz[N], mz[N], vs[N], ans;
vector<int> to[N];

inline void frt(int x, int fa)
{
	sz[x] = 1, mz[x] = 0;
	for(auto i : to[x])
	{
		if(i == fa || vs[i]) continue;
		frt(i, x), sz[x] += sz[i];
		mz[x] = max(mz[x], sz[i]);
	}
	mz[x] = max(mz[x], rtsz - sz[x]);
	if(mz[x] < mz[rt]) rt = x;
}
inline void dfs(int x, int fa)
{
	sz[x] = 1;
	int f[M], sy = d[x];
	memcpy(f, dp, sizeof(dp));
	pre(j, m, c[x]) dp[j] = dp[j - c[x]] + w[x];
	fro(j, 0, c[x] - 1) dp[j] = -2e7; sy--;
	for(int i = 1;sy;i <<= 1)
	{
		int r = min(i, sy); sy -= r;
		int y = c[x] * r, z = w[x] * r;
		pre(j, m, y) dp[j] = max(dp[j], dp[j - y] + z);
	}
	for(auto i : to[x])
	{
		if(vs[i] || i == fa) continue;
		dfs(i, x), sz[x] += sz[i];
	}
	fro(j, 0, m) dp[j] = max(dp[j], f[j]);
}
inline void calc(int now)
{
	memset(dp, 0, sizeof dp), dfs(now, 0);
	fro(i, 0, m) ans = max(ans, dp[i]);
}
inline void solve(int now)
{
	vs[now] = 1, calc(now);
	for(auto i : to[now])
	{
		if(vs[i]) continue;
		rt = 0, rtsz = sz[i];
		frt(i, now), solve(rt);
	}
}
inline void solve()
{
	cin >> n >> m, ans = 0;
	fro(i, 1, n) cin >> w[i];
	fro(i, 1, n) cin >> c[i];
	fro(i, 1, n) cin >> d[i];
	fro(i, 1, n - 1)
	{
		int x, y;
		cin >> x >> y;
		to[x].eb(y), to[y].eb(x);
	}
	rtsz = mz[rt = 0] = n, frt(1, 0), solve(rt);
	cout << ans << endl;
	fro(i, 1, n) to[i].clear();
	memset(vs, 0, sizeof vs);
}

bool st;

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	double Mib = fabs((&ed-&st)/1048576.), Lim = 125;
	cerr << " Memory: " << Mib << "\n", assert(Mib<=Lim);
	int t; cin >> t;
	while(t--) solve();
	return 0;
}
```

---

## 作者：born_to_sun (赞：2)

### 前言
提供一个不用 dfs 序的方法，如果你觉得 dfn 序理解起来比较困难，可以采纳我的方法。

树形 dp 可以父亲转移到儿子，也可以儿子转移到父亲，但在本题，你将会同时见到两种转移，令你大跌眼镜。

### 思路
前面的点分治就不提了，我们直接跳到背包优化那一步。

设状态 $f_{u,i}$ 为 $u$ 到分治中心的每个点至少都选一个，花费为 $i$ 的最大收益。

转移直接从父亲转移即可，但是这样我们只能维护一条链，无法维护树上连通块。

接下来是**智慧的一步**，设当前节点为 $u$，父亲为 $fa$，儿子为 $v$，我们考虑这样做：
+ 在进入 $u$ 时从 $fa$ 转移
+ 在递归完 $u$ 一个儿子 $v$ 后，将 $f_u$ 的每个位置对 $f_v$ 取 $\max$，即 $f_{u,i}\leftarrow \max(f_{u,i},f_{v,i})$

手玩几组后，你们发现这样就能维护出来连通块的信息了。

时间复杂度：$O(nm\log n\log d)$

咱都知道通常二进制分组比单调队列跑的快对吧，我造了 $T=5,n=500,m=4000,w_i=1,c_i=1,d_i=2000$ 的链都卡不掉。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=505;
const int inf=1e9;
vector<int> e[N];
int w[N],c[N],d[N];
struct no{
	int val,cs;
};
vector<no> a[N];
int rt,tot_sz;
int siz[N],vis[N];
int ans;
int n,m;
void find_rt(int u,int ft){
	for(auto v:e[u]){
		if(vis[v]||v==ft) continue;
		find_rt(v,u);
	}
	if(!rt&&siz[u]*2>=tot_sz) rt=u;
}
void find_tot(int u,int ft){
	siz[u]=1;tot_sz++;
	for(auto v:e[u]){
		if(vis[v]||v==ft) continue;
		find_tot(v,u);
		siz[u]+=siz[v];
	}
}
int f[N][4005];
void dfs2(int u,int ft){
	memcpy(f[u],f[ft],sizeof(f[u]));
	for(auto x:a[u]){
		int val=x.val,cs=x.cs;
		for(int i=m;i>=cs;i--) f[u][i]=max(f[u][i],f[u][i-cs]+val);
	}
	for(int i=m;i>=c[u];i--) f[u][i]=f[u][i-c[u]]+w[u];
	for(int i=0;i<c[u];i++) f[u][i]=-inf;
	for(auto v:e[u]){
		if(vis[v]||v==ft) continue;
		dfs2(v,u);
		for(int i=0;i<=m;i++) f[u][i]=max(f[u][i],f[v][i]);
	}
}
void dfs(int u){
	if(vis[u]) return;
	vis[u]=1;
	dfs2(u,0);
	for(int i=0;i<=m;i++) ans=max(ans,f[u][i]);
	for(auto v:e[u]){
		if(vis[v]) continue;
		rt=tot_sz=0;
		find_tot(v,u);find_rt(v,u);
		dfs(rt);
	}
}
void solve(){
	rt=tot_sz=0;
	find_tot(1,0);find_rt(1,0);
	dfs(rt);
}
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	int T;cin>>T;
	while(T--){
		for(int i=1;i<=n;i++) vis[i]=0,e[i].clear(),a[i].clear();
		ans=0;
		cin>>n>>m;
		for(int i=1;i<=n;i++) cin>>w[i];
		for(int i=1;i<=n;i++) cin>>c[i];
		for(int i=1;i<=n;i++){
			int sum;cin>>sum;sum--;
			int x=1;
			while(x<=sum){
				a[i].push_back({x*w[i],x*c[i]});
				sum-=x;
				x<<=1;
			}
			if(sum) a[i].push_back({sum*w[i],sum*c[i]});
		}
		for(int i=1;i<n;i++){
			int u,v;cin>>u>>v;e[u].push_back(v);e[v].push_back(u);
		}
		solve();
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：lingfunny (赞：2)

## 前言

一个经典的按 DFS 序转移与点分治题目，在 [2018 国家集训队论文](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2018%E8%AE%BA%E6%96%87%E9%9B%86.pdf)的《解决树上连通块问题的一些技巧和工具》一文中有较为完整的总结。

本题属于树上连通块 DP 问题，这类问题一般有两种形式：

1. 计数类问题：给定树 $T$ 和性质 $A$，查询树上满足性质 $A$ 的连通块数量。
1. 最优化问题：给定树 $T$ 和价值函数，查询树上所有满足某性质的连通块的最优价值。

显然本题就是一类最优化问题，价值函数为背包。

## 题解

本题的朴素做法是直接记录 $f_{i, j}$ 表示对于在子树 $i$ 内包含 $i$ 的所有连通块，花费 $j$ 元可以得到的最大价值。

一个比较明显的特征是，这个 dp 需要合并子树，而背包合并的复杂度是 $O(m^2)$ 的（$m$ 为值域）。相反，加入一个点（物品）的复杂度是 $O(m)$ 的（单调队列优化，也可以用二进制分组做到 $O(m\log d)$ 的复杂度）。

对于这类合并信息不够高效，但是加入单点的信息比较高效的问题，往往可以按照 DFS 序转移，把合并子树变成加入单点。树上背包就是一个典型的例子。

设 $f_i$ 表示考虑 DFS 序上 $[i, n]$ 这些节点的答案。则 $f_1$ 可以由 $[2, n]$ 的答案添加物品 $1$ 转移。

一般的，$f_i$ 可以由 $\operatorname{add}(f_{i+1}, \mathrm{item}_i)$ 转移，表示添加 $i$ 物品。如果不选择 $i$，则也不能选择 $i$ 的子树，所以另一个是直接由 $f_j$ 转移，这里的 $j$ 是 $i$ 子树在 DFS 序上的右端点 $+1$。

但是有个问题……这里的 DFS 序转移是以 $1$ 为根的，换句话说，$f_1$ 的结果是必须选择 $1$ 的答案（不选择就是 $0$ 了）。不过解决方案也很简单，直接对树进行点分治便可以考虑所有情况。即考虑强制选择重心的情况，否则递归下去处理。

总时间复杂度 $O(nm\log n)$。

---

## 作者：Purslane (赞：1)

# Solution

所以背包问题怎么做？

有关“树上连通块”的背包问题有两种常见套路：树上背包 $\rm DP$，拍成 $\rm DFS$ 序之后 $\rm DP$。

具体的，如果我们点 $u$（$\rm DFS$ 序为 $t$）已经取了一个数，我们可以选择进入 $u$ 的子树，即 $t \leftarrow t+1$；如果我们打算跳过 $u$ 的子树，则 $t \leftarrow t+ \text{sze}_u$。本题在此基础上使用单调队列优化多重背包。

不过这个做法有一个前提：你得钦定根节点被选入。使用点分治即可。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=500+10,MAXM=4000+10;
int T,n,m,w[MAXN],c[MAXN],d[MAXN];
vector<int> G[MAXN];
int ans,tot,flg[MAXN],sze[MAXN],mx[MAXN],dfn[MAXN],dp[MAXN][MAXM],f[MAXN][MAXM],rev[MAXN];
void dfs(int u,int f) {sze[u]=1,mx[u]=0;for(auto v:G[u]) if(v!=f&&!flg[v]) dfs(v,u),sze[u]+=sze[v],mx[u]=max(mx[u],sze[v]);return ;}
int find_core(int u,int f,int al) {
	if(max(mx[u],al-sze[u])<=al/2) return u;
	for(auto v:G[u]) if(v!=f&&!flg[v]) {
		int tans=find_core(v,u,al);
		if(tans!=-1) return tans;
	}
	return -1;
}
void build_t(int u,int f) {dfn[u]=++tot,rev[tot]=u;for(auto v:G[u]) if(v!=f&&!flg[v]) build_t(v,u);return ;}
void generate(int id) {
	ffor(i,0,c[rev[id]]-1) {
		deque<pair<int,int>> dq;
		dq.push_back({i,f[id][i]});
		int tval=i+c[rev[id]],rnk=1;
		while(tval<=m) {
			while(tval-dq.front().first>d[rev[id]]*c[rev[id]]) dq.pop_front();
			dp[id][tval]=dq.front().second+rnk*w[rev[id]];
			pair<int,int> pr={tval,f[id][tval]-rnk*w[rev[id]]};
			while(!dq.empty()&&pr.second>=dq.back().second) dq.pop_back();
			dq.push_back(pr);
			tval+=c[rev[id]],rnk++;
		}
	}
	return ;
}
void solve(int u) {
	tot=0,dfs(u,0),u=find_core(u,0,sze[u]),dfs(u,0),build_t(u,0);
	ffor(i,1,tot) memset(dp[i],-0x3f,sizeof(dp[i])),memset(f[i],-0x3f,sizeof(f[i]));
	f[1][0]=0;
	ffor(i,1,tot) {
		generate(i);
		ffor(j,0,m) f[i+1][j]=max(f[i+1][j],dp[i][j]);
		ffor(j,0,m) f[i+sze[rev[i]]][j]=max(f[i+sze[rev[i]]][j],dp[i][j]);
		ffor(j,0,m) f[i+sze[rev[i]]][j]=max(f[i+sze[rev[i]]][j],f[i][j]);
	}
	ffor(i,1,tot)ffor(j,0,m)ans=max(ans,dp[i][j]);
	flg[u]=1;for(auto v:G[u])if(!flg[v])solve(v);
	return ;
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>T;
	while(T--) {
		cin>>n>>m,ans=0;ffor(i,1,n)G[i].clear(),cin>>w[i];ffor(i,1,n)cin>>c[i];ffor(i,1,n)cin>>d[i];	
		memset(flg,0,sizeof(flg));ffor(i,1,n-1){int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
		solve(1),cout<<ans<<'\n';
	}
	return 0;
}
//久未放晴的天空 依旧留着你的笑容 哭过 去无法忘记歉疚 
```

---

## 作者：封禁用户 (赞：1)

### 题意

对于一颗树，每个节点都是一个多重背包，问选择一个连通块的最优解。

### 前置知识

+ 多重背包的二进制优化

这个应该大家都会，时间复杂度：$O(nm \log D)$。

+ 点分治 

简单来说，就是把一颗树，先取一棵树的重心，在被重心拆分的若干颗子树中，继续取重心，进行分治。可以证明时间复杂度是 $O(n \log n)$ 的。

+ dfs 序优化树形 DP。

我们把对于子树的 DP 转化成一个序列的 DP。如果取这个节点，就从 dfs 序的下一个（也就是自己最先遍历的子节点）转移过来；否则，就从自己子树内最大的 dfs 序的下一个转移过来。

### 分析

首先，由于是一个连通块，我们可以选取一个节点为根。我们采用点分治，先选取重心为根，在每个字树种继续选取重心为根，进行多重背包 DP。

要注意，如果要选一个节点的子树，这个节点是**必须选取的**，我们必须先强制转移。

状态转移方程就是多重背包的状态转移方程。

总时间复杂度：$O(nm \log n \log D)$。

### 代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
template<typename T>inline void read(register T &x)
{
	register T p = 1,num = 0;
	char c = getchar();
	while(c < '0'||c > '9')
	{
		if(c == '-') p = -p;
		c = getchar();
	}
	while('0' <= c&&c <= '9')
	{
		num = (num<<3)+(num<<1)+(c^48);
		c = getchar();
	}
	x = p * num;
}
template<typename T>inline void write(register T x)
{
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) write(x/10);
	putchar(x%10+48);
}
#define D(i,a,b) for(register int i=a;i>=b;--i)
#define F(i,a,b) for(register int i=a;i<=b;++i)
#define ll long long
#define pii pair<int,int>
#define M 4010
#define N 510
int t,n,m,w[N],c[N],d[N],sz[N],mx[N],dp[N][M],rt,tot,ans;
int head[N],nxt[N<<1],to[N<<1],ct;
bitset<N> vis;
inline void add(int u,int v)
{
	nxt[++ct] = head[u];
	head[u] = ct;
	to[ct] = v; 
}
void dfs(int u,int fa)
{
	sz[u] = 1,mx[u] = 0;
	for(register int i = head[u];i;i = nxt[i])
	{
		int v = to[i];
		if(v == fa||vis[v]) continue;
		dfs(v,u);
		sz[u] += sz[v];
		mx[u] = max(mx[u],sz[v]);
	}
	mx[u] = max(mx[u],tot - sz[u]);
	if(mx[u] < mx[rt]) rt = u;
}
int b[N],e[N],id[N],cnt;
void dfs1(int u,int fa)
{
	b[u] = ++cnt,id[cnt] = u;
	for(register int i = head[u];i;i = nxt[i])
	{
		int v = to[i];
		if(v == fa||vis[v]) continue;
		dfs1(v,u); 
	}
	e[u] = cnt;
}
int num[20];
void solve(int u)
{
	vis[u] = 1;
	cnt = 0;
	dfs1(u,0);	
	F(i,1,cnt+1)
		F(j,0,m)
			dp[i][j] = 0;
	D(i,cnt,1)
	{
		int C = c[id[i]],W = w[id[i]],D = min(m/C,d[id[i]])-1,len = 0;
		if(D < 0) continue;
		for(register int j = 1;j <= D;j <<= 1)
		{
			D -= j;
			num[++len] = j;		
		}	
		if(D) num[++len] = D;
		F(j,C,m) dp[i][j] = max(dp[i][j],dp[i+1][j-C]+W);
		F(j,1,len)
			D(k,m,num[j]*C)
				dp[i][k] = max(dp[i][k],dp[i][k-num[j]*C] + num[j]*W);
		F(j,0,m) dp[i][j] = max(dp[i][j],dp[e[id[i]]+1][j]);
	}
	ans = max(ans,dp[1][m]);
	int T = tot;
	for(register int i = head[u];i;i = nxt[i])
	{
		int v = to[i];
		if(vis[v]) continue;
		tot = sz[v];
		if(sz[v] > sz[u]) tot = T - sz[v];
		rt = 0;
		dfs(v,0);
		solve(rt);
	}
}
int main()
{
	mx[0] = 1e9;
	read(t);
	while(t--)
	{
		memset(dp,0,sizeof(dp));
		memset(head,0,sizeof(head));
		vis = 0;
		ct = rt = ans = 0; 
		read(n),read(m);
		F(i,1,n) read(w[i]);
		F(i,1,n) read(c[i]);
		F(i,1,n) read(d[i]);
		F(i,1,n-1)
		{
			int u,v;
			read(u),read(v);
			add(u,v),add(v,u);
		}
		tot = n;
		dfs(1,0);
		solve(rt);
		write(ans);
		putchar('\n');
	}
	return 0;
}
```


---

## 作者：ax_by_c (赞：0)

这个显然是多重背包，至少买一个相当于提前买一个然后再 DP。

我一开始读题读成链了，那么就不难想到用点分治快速统计贡献，每次统计所有包含重心的连通块的贡献。

那么就是一个树上多重背包，使用单调队列优化，直接暴力合并应该是 $O(nm^2)$ 的。

考虑设计一种不需要合并的状态，只能是放到序列上去做。

思考确定了选的点后遍历这些点的一种方法：若当前点选则进入第一个儿子，否则跳过整个子树。

于是变成了一个序列上的 DP，时间复杂度 $O(nm)$。（其实写起来还是 dfs 序方便）

总时间复杂度 $O(nm\log n)$。

本题启示我们看到树上问题考虑链，看到很多难以计算的东西考虑分治，从解法的不足和可能的优化方向去思考。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef pair<int,int> pii;
const int N=505;
const int M=4005;
int n,m,ans;
int v[N],w[N],s[N];
vector<int>g[N];
bitset<N>rem;
int rt,asz,sz[N];
int dfa[N],Tim;
void ddfs(int u,int fa){
	dfa[++Tim]=u;
	sz[u]=1;
	int mx=0;
	for(auto v:g[u]){
		if(v==fa||rem[v])continue;
		ddfs(v,u);
		sz[u]+=sz[v];
		mx=max(mx,sz[v]);
	}
	mx=max(mx,asz-sz[u]);
	if(mx*2<=asz)rt=u;
}
int f[N][M],h[M];
deque<pii>dq;
void add(int *f,int v,int w,int s){
	for(int i=m;i>=w;i--)f[i]=f[i-w]+v;
	for(int i=w-1;i>=0;i--)f[i]=0;
	s--;
	for(int i=0;i<=m;i++)h[i]=0;
	for(int c=0;c<w;c++){
		while(dq.size())dq.pop_front();
		for(int i=c,j=0;i<=m;i+=w,j++){
			pii tmp={f[i]-v*j,i};
			while(dq.size()&&dq.back().first<=tmp.first)dq.pop_back();
			while(dq.size()&&dq.front().second<i-s*w)dq.pop_front();
			dq.push_back(tmp);
			h[i]=max(h[i],f[dq.front().second]+(i-dq.front().second)/w*v);
		}
	}
	for(int i=0;i<=m;i++)f[i]=max(f[i],h[i]);
}
void dfz(int u,int sz_){
	asz=sz_;
	Tim=0;ddfs(u,0);
	Tim=0;ddfs(rt,0);
	for(int i=1;i<=Tim+1;i++){
		for(int j=0;j<=m;j++)f[i][j]=0;
	}
	for(int i=Tim;i>=1;i--){
		for(int j=0;j<=m;j++)f[i][j]=f[i+1][j];
		add(f[i],v[dfa[i]],w[dfa[i]],s[dfa[i]]);
		for(int j=0;j<=m;j++)f[i][j]=max(f[i][j],f[i+sz[dfa[i]]][j]);
	}
	ans=max(ans,f[1][m]);
	rem[rt]=1;
	for(auto v:g[rt]){
		if(!rem[v])dfz(v,sz[v]);
	}
}
void slv(){
	scanf("%d %d",&n,&m);ans=0;
	for(int i=1;i<=n;i++){
		g[i].clear();
		rem[i]=0;
	}
	for(int i=1;i<=n;i++)scanf("%d",&v[i]);
	for(int i=1;i<=n;i++)scanf("%d",&w[i]);
	for(int i=1;i<=n;i++)scanf("%d",&s[i]);
	for(int i=1,x,y;i<n;i++){
		scanf("%d %d",&x,&y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dfz(1,n);
	printf("%d\n",ans);
}
void main(){
	int T;
	scanf("%d",&T);
	while(T--)slv();
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：__ycx2010__ (赞：0)

直接树上 dp 复杂度为 $O(nm^2)$，瓶颈在于子树合并时的 $O(m^2)$，考虑将树拍成 dfs 序，设 $f_{i,j}$ 表示只考虑 dfs 序在 $[i,n]$ 中的点，有 $j$ 元钱的最大价值。

转移为若选择当前点，那么从 $f_{i+1}$ 转移，此处需要用到二进制分组优化多重背包。

若不选当前点，则跳过当前子树，从 $f_{i+siz}$ 转移。

最终只能求出包含根节点的值，所以我们使用点分治，单次背包复杂度 $O(nm\log d)$，总复杂度 $O(nm\log n\log d)$。

```cpp
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pii pair<int, int>

using namespace std;

const int N = 510, M = 4010, inf = 0x3f3f3f3f;
vector<int> to[N];
int n, m, vis[N], ans;
int f[N][2][M], w[N], c[N], d[N];

int qsiz(int u, int fa) {
	int siz = 1;
	for (int j : to[u]) {
		if (j == fa || vis[j]) continue;
		siz += qsiz(j, u);
	}
	return siz;
}

int find(int u, int fa, int all, int &d) {
	int mx = 0, siz = 1;
	for (int j : to[u]) {
		if (j == fa || vis[j]) continue;
		int t = find(j, u, all, d);
		mx = max(mx, t), siz += t;
	}
	mx = max(mx, all - siz);
	if (mx <= all / 2) d = u;
	return siz;
}

int dfn[N], g[N], sz[N], tot;

void dfs(int u, int fa) {
	dfn[u] = ++ tot, g[tot] = u;
	sz[u] = 1;
	for (int j : to[u]) {
		if (j == fa || vis[j]) continue;
		dfs(j, u);
		sz[u] += sz[j];
	}
}

void dp(int wn, int cost, int dn, int *dp, int *g) {
	vector<int> f(m + 5);
	for (int j = 0; j < cost; j ++ ) f[j] = -inf;
	for (int j = cost; j <= m; j ++ ) f[j] = g[j - cost] + wn;
	dn -- ;
	int t = 1;
	while ((t << 1) <= dn) t <<= 1;
	vector<int> p;
	for (int i = 1; i < t; i <<= 1) {
		p.pb(i);
	}
	p.pb(dn - (t - 1));
	for (int k : p) {
		for (int j = m; j >= k * cost; j -- )
			f[j] = max(f[j], f[j - k * cost] + k * wn);
	}
	for (int j = 0; j <= m; j ++ ) dp[j] = max(dp[j], f[j]);
}

void backpack(int u) {
	tot = 0;
	dfs(u, 0);
	for (int j = c[g[1]]; j <= m; j ++ ) f[1][0][j] = -inf, f[1][1][j] = min(j / c[g[1]], d[g[1]]) * w[g[1]];
	for (int j = 0; j < c[g[1]]; j ++ ) f[1][0][j] = f[1][1][j] = -inf;
	for (int i = 1; i < tot; i ++ ) {
		if (sz[g[i]] > 1) {
			for (int j = 0; j <= m; j ++ ) f[i + 1][0][j] = max(f[i + 1][0][j], f[i][1][j]); 
			dp(w[g[i + 1]], c[g[i + 1]], d[g[i + 1]], f[i + 1][1], f[i][1]);
		}
		if (i + sz[g[i]] <= tot) {
			for (int j = 0; j <= m; j ++ ) f[i + sz[g[i]]][0][j] = max(f[i + sz[g[i]]][0][j], max(f[i][0][j], f[i][1][j]));
			dp(w[g[i + sz[g[i]]]], c[g[i + sz[g[i]]]], d[g[i + sz[g[i]]]], f[i + sz[g[i]]][1], f[i][1]);
			dp(w[g[i + sz[g[i]]]], c[g[i + sz[g[i]]]], d[g[i + sz[g[i]]]], f[i + sz[g[i]]][1], f[i][0]);
		}
	}
	for (int i = 1; i <= tot; i ++ ) {
		ans = max(ans, f[i][1][m]);
		for (int j = 0; j <= m; j ++ )
			f[i][0][j] = f[i][1][j] = -inf;
	}
}

void divide(int u) {
	backpack(u);
	vis[u] = 1;
	for (int j : to[u]) {
		if (vis[j]) continue;
		int d;
		find(j, u, qsiz(j, u), d);
		divide(d);
	}
}

void rda(int *a, int len) {
	for (int i = 1; i <= len; i ++ ) scanf("%d", &a[i]);
}

void solve() {
	ans = 0;
	scanf("%d%d", &n, &m);
	rda(w, n); rda(c, n); rda(d, n);
	for (int i = 1; i < n; i ++ ) {
		int a, b;
		scanf("%d%d", &a, &b);
		to[a].pb(b), to[b].pb(a);
	}
	memset(vis, 0, sizeof vis); 
	int rt;
	find(1, 0, n, rt);
	divide(rt);
	printf("%d\n", ans);
	for (int i = 1; i <= n; i ++ ) to[i].clear();
}

int main() {
	memset(f, 0x8f, sizeof f);
	int T;
	scanf("%d", &T);
	while (T -- ) solve();
	return 0;
}
```

---

## 作者：不知名用户 (赞：0)

题意：一棵树上有一些物品，做多重背包且选的物品点必须是树上的连通块。点数 500，背包体积 4000。**注意每种物品最多 100 个，体积最多 4000，即物品总体积很大。**

看到连通块考虑是否可以在最浅点树形 DP。很遗憾，物品总体积很大，直接做合并两棵子树是 $\Theta(v^2)$，但是背包体积很小有一些启发。

看到连通块想到点分治（不知道题解怎么想到的），因为连通块可以像路径一样经过或不经过重心来区分再向下分治。我们考虑在一棵分治子树内如何 `DP`。

（以下是这种思路可能的来源，可以跳过直接看如何 `DP`）肯定要选根，然后考虑第一棵子树的根选不选，不选则只用考虑其它子树，选则继续望下考虑。发现不同子树并不干扰，于是可以按照 $dfn$ 序从大到小 `DP`。

按照 $dfn$ 序从大到小 `DP`。记 $l_i,r_i$ 表示 $i$ 子树 $dfn$ 区间的左右端点，$pos$ 是满足 $pos_{l_i}=i$ 的数组。记 $f_{i,j}$ 表示从后往前考虑到 $pos_i$，体积为 $j$，且选一个点必选所有祖先当中 $dfn$ 大于等于 $i$ 的点。如果选 $pos_i$，从 $f_{i+1}$ 传过来+单调队列优化即可（注意**一定要选**），否则继承 $f_{r_{pos_i}+1}$。分治子树内复杂度 $\Theta(nv)$，加上点分治的 $\log$ 总复杂度为 $\Theta(nv\log n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 510, M = 4010;

int n, m, vis[N], sz[N], mx[N], rt, w[N], c[N], d[N], f[N][M], sd[N], ans, l[N], r[N], pos[N], dfn, q[M], h, t;
vector<int>g[N];

void grt(int x, int fa, int t)
{
	sz[x] = 1, mx[x] = 0;
	for(auto j:g[x]) if(j!=fa&&!vis[j])
		grt(j,x,t), sz[x] += sz[j], mx[x] = max(mx[x],sz[j]);
	mx[x] = max(mx[x],t-sz[x]);
	if(mx[x]<mx[rt]) rt = x;
}

void getdfn(int x, int fa)
{
	pos[l[x]=++dfn] = x;
	for(auto j:g[x]) if(j!=fa&&!vis[j]) getdfn(j,x);
	r[x] = dfn;
}

void slv(int x)
{
	vis[x] = 1;
	dfn = 0, getdfn(x,0);
	int i, j, k;
	for(i=0;i<=m;i++) f[dfn+1][i] = 0;
	for(i=dfn;i;i--)
	{
		for(j=0;j<=m;j++) f[i][j] = f[r[pos[i]]+1][j];
		for(j=0;j<c[pos[i]];j++)
		{
			h = 1, t = 0;
			for(k=j;k<=m;k+=c[pos[i]])
			{
				while(h<=t&&q[h]<k-c[pos[i]]*d[pos[i]]) h++;
				if(h<=t) f[i][k] = max(f[i][k],f[i+1][q[h]]+(k-q[h])/c[pos[i]]*w[pos[i]]);
				while(h<=t&&f[i+1][q[t]]+(k-q[t])/c[pos[i]]*w[pos[i]]<=f[i+1][k]) t--;//必须选所以要后插入 
				q[++t] = k;
			}
		}
	}
	ans = max(ans,f[1][m]);
	for(auto j:g[x]) if(!vis[j]) rt = 0, grt(j,0,sz[j]), slv(rt);
}

int Main()
{
	int a, b, i;
	cin>>n>>m;
	for(i=1;i<=n;i++) cin>>w[i];
	for(i=1;i<=n;i++) cin>>c[i];
	for(i=1;i<=n;i++) cin>>d[i];
	for(i=1;i<=n;i++) g[i].clear(), vis[i] = 0;
	for(i=1;i<n;i++) cin>>a>>b, g[a].emplace_back(b), g[b].emplace_back(a);
	mx[0] = 1e9, ans = rt = 0, grt(1,0,n);
	slv(rt);
	cout<<ans<<'\n';
	return 0;
}
int main(){ios::sync_with_stdio(0);int t;cin>>t;while(t--)Main();return 0;}
```

---

## 作者：0xyz (赞：0)

- 给出一棵树，求所有连通块里的节点的多重背包。

首先，由于多重背包单次合并是 $O(m^2)$ 的，所以考虑每次只加入一种物品，对于连通块的要求，可以按照 DFS 序从大到小 DP，令 $g_{i}$ 表示解决 DFS 序为 $[i,n]$ 的物品的状态，我们可以选择 DFS 序为 $i$ 个物品，也可以不选择，从而我们不能选择 $i$ 的子树，所以有 $g_i=\max(g_{i+1}+item_i,g_{i+s_{i}})$，其中 $s_i$ 是这个节点的子树大小。那么这样单次转移就是 $O(m)$ 的了。注意到这样求出的 $g_1$ 要求必须选择物品 $1$，所以我们点分治，对于选择每一个重心的连通块 DP 一次即可。多重背包可以是用二进制优化，时间复杂度 $O(nm\log n\log d)$，可以通过此题。

代码很短。注意 $g_i$ 从 $g_{i+1}$ 转移时必须要至少买一个。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int _=505;
int T,n,m,c,r,s[_],p[_],a[_],o[_],g[_][_*8],w[_],v[_],d[_],ans;
vector<int>e[_];
void get(int x,int f,int t,int l){
	s[x]=1;p[x]=0;if(!l)o[++c]=x;
	for(auto y:e[x])
		if(!a[y]&&y!=f)get(y,x,t,l),s[x]+=s[y],p[x]=max(p[x],s[y]);
	if((p[x]=max(p[x],t-s[x]))<p[r])r=x;
}
void sol(int x,int f){
	for(int i=c,y,l;i>=1;i--){
		l=d[y=o[i]]-1;memcpy(g[i],g[i+s[y]],_<<5);
		for(int j=v[y];j<=m;j++)g[i][j]=max(g[i][j],g[i+1][j-v[y]]+w[y]);
		for(int j=1;j<=l;l-=j,j<<=1)
			for(int k=m;k>=v[y]*j;k--)g[i][k]=max(g[i][k],g[i][k-v[y]*j]+w[y]*j);
		for(int j=m;j>=v[y]*l;j--)g[i][j]=max(g[i][j],g[i][j-v[y]*l]+w[y]*l);
	}
	ans=max(ans,g[1][m]);a[x]=1;
	for(int i=1;i<=c;i++)memset(g[i],0,_<<5);
	for(auto y:e[x])
		if(!a[y]&&y!=f)p[r=0]=1e9,get(y,x,s[y],1),get(r,0,s[y],c=0),sol(r,x);
}
int main(){
	cin>>T;
	while(T--){
		cin>>n>>m;ans=0;
		for(int i=1;i<=n;i++)cin>>w[i],e[i].clear(),a[i]=0;
		for(int i=1;i<=n;i++)cin>>v[i];
		for(int i=1;i<=n;i++)cin>>d[i];
		for(int i=1,x,y;i<n;i++)cin>>x>>y,e[x].push_back(y),e[y].push_back(x);
		p[r=0]=1e9;get(1,0,n,1);get(r,0,n,c=0);sol(r,0);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

