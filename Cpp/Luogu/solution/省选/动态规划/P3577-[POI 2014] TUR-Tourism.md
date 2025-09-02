# [POI 2014] TUR-Tourism

## 题目描述

国王 Byteasar 认为 Byteotia 是一个充满美丽景色的地方，应该吸引大量游客，他们应该花很多钱，这些钱最终应该流入皇家国库。

但现实并没有达到他的梦想。

因此，国王指示他的顾问调查这个问题。

顾问发现外国人因为 Byteotia 稀疏的道路网络而避开这里。

我们注意到 Byteotia 有 $n$ 个城镇，由 $m$ 条双向道路连接，每条道路连接两个不同的城镇。

这些道路可能经过风景如画的高架桥和不那么美观的隧道。

不能保证每个城镇都可以从其他城镇到达。

顾问观察到当前的道路网络不允许进行长途旅行。

也就是说，无论从哪里开始旅行，都不可能在不经过某个城镇两次的情况下访问超过 10 个城镇。

由于国库资金有限，目前不会修建新的道路。

相反，Byteasar 决定建立一个旅游信息点（TIPs）网络，由官员负责宣传可用的短途旅行。

对于每个城镇，应该在该城镇或通过道路直接连接的城镇之一设立一个 TIP。

此外，每个城镇建设 TIP 的成本是已知的。

通过找到满足上述条件的最便宜的建设 TIP 的方式来帮助国王。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
6 6
3 8 5 6 2 2
1 2
2 3
1 3
3 4
4 5
4 6
```

### 输出

```
7
```

# 题解

## 作者：QwQcOrZ (赞：12)

考虑在无向图的生成树上dp（实际上是生成森林，因为可能会不连通，但为了方便讨论我们把它看成一棵树）

因为题设，所以树的深度不会超过 $10$，那么可以把当前节点到根的路径上的点的状态都压起来

设 $dp_{i,j}$ 表示当节点 $i$ 到根节点的路径上的点的状态为 $j$ 时，生成树中除了节点 $i$ 到根节点的路径上的点（也就是状态被压入 $j$ 的点），其它所有 $dfs$ 序比 $i$ 小的节点都被覆盖了的最小费用

其中 $j$ 表示的每个点的状态有三种：$0$ 表示选了，$1$ 表示不选但没被覆盖，$2$ 表示不选且已被覆盖

这个状态可能理解起来有点抽象，所以我画了张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/n6cz94uj.png)

其中三角形表示子树，圆形表示节点，$A$ 点为当前处理到的点，红点为压入状态 $j$ 的点，绿点为要求被覆盖的点，白点为还未处理过的点

每次转移时从父亲节点的 $dp$ 值继承过来，选或不选分类讨论一下，对应更改状态即可

要注意的是每次 dfs 完儿子后要从儿子向上更新当前节点的 $dp$ 值，因为已经处理过的点如果不在状态内表示的话必须是被覆盖的

最后答案即为森林内每棵树的最优解之和

$Code\ Below$（我这里为了方便 $dp_{i,j}$ 中的 $i$ 表示的是深度）

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e4+5;
const int M=2.5e4+5;
const int D=15;
const int S=59059;
const int inf=1e9+7;

inline int read()
{
	register int s=0;
	register char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(register int x)
{
	if (x<0)
	{
		putchar('-');
		x=-x;
	}
	if (x<10) putchar(x+'0');
	else
	{
		write(x/10);
		putchar(x%10+'0');
	}
}
inline void print(const register int x,const register char c='\n')
{
	write(x);
	putchar(c);
}
struct edge
{
	int to,nxt;
}e[M*2];
int head[N],cnt=0;
void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
bool vis[N];
int a[N],dep[N],Pow[D],q[N],dp[D][S];//0:选了，1:不选且没覆盖，2:不选且覆盖 
inline int get(register int i,register int j)//返回i在三进制下的第j位
{
	return i/Pow[dep[j]]%3;
}
inline void up(register int &x,register int y)
{
	x=min(x,y);
}
void dfs(register int now)
{
	register int cnt=0;
	vis[now]=1;
	for (register int i=head[now];i;i=e[i].nxt)
	if (vis[e[i].to]&&dep[e[i].to]<dep[now])
	q[++cnt]=e[i].to;//把当前节点的所有返祖边存到q中
	if (dep[now]==0)
	{
		dp[0][0]=a[now];
		dp[0][1]=0;
		dp[0][2]=inf;
	}//如果是根节点则不需要从父亲继承dp值
	else
	{
		for (register int i=0;i<Pow[dep[now]+1];i++) dp[dep[now]][i]=inf;
		for (register int i=0;i<Pow[dep[now]];i++)//枚举父亲的状态
		{
			register int No=1,Yes=i;
            //No表示的是当前节点不选时，当前节点的状态
            //Yes表示的是当前节点选时，当前节点到根路径上所有节点的状态
			for (register int j=1;j<=cnt;j++)
			{
				if (get(i,q[j])==0) No=2;
                //当当前节点不选时，如果返祖边有连向被选的点，那么当前节点会被覆盖
				if (get(i,q[j])==1) Yes+=Pow[dep[q[j]]];
                //当当前节点选时，如果返祖边连向未被选且没有被覆盖的点，那么被连向的点会被覆盖
			}
			up(dp[dep[now]][i+No*Pow[dep[now]]],dp[dep[now]-1][i]);
			up(dp[dep[now]][Yes],dp[dep[now]-1][i]+a[now]);
		}
	}
	for (register int i=head[now];i;i=e[i].nxt)
	{
		register int to=e[i].to;
		if (vis[to]) continue;
		dep[to]=dep[now]+1;
		dfs(to);
		for (register int j=0;j<Pow[dep[to]];j++)
		dp[dep[now]][j]=min(dp[dep[to]][j],dp[dep[to]][j+2*Pow[dep[to]]]);
        //从儿子向上更新dp值
	}
}

signed main()
{
	Pow[0]=1;
	for (register int i=1;i<=10;i++) Pow[i]=Pow[i-1]*3;
	memset(vis,0,sizeof(vis));
	memset(dep,0,sizeof(dep));
	register int n=read(),m=read(),ans=0;
	for (register int i=1;i<=n;i++) a[i]=read();
	for (register int i=1;i<=m;i++)
	{
		register int u=read(),v=read();
		add(u,v);
		add(v,u);
	}
	for (register int i=1;i<=n;i++)
	if (!vis[i])
	{
		dfs(i);
		ans+=min(dp[0][0],dp[0][2]);
	}
	print(ans);

	return 0;
}
```

最后，此题卡常，记得开 O2

---

## 作者：Sheep_ (赞：9)

**此题做法：状压DP！**

f[d][s]表示深度为d时，当前节点及其祖先状态为s是，以该节点为根的子树及其祖先的最小费用和。

由于任意两点之间的简单路径不超过十个点因此可以状态压缩。

其中s的（从左往右）第一位表示该点状态，第二位表示该点的父亲节点的状态，第三位表示爷爷，以此类推。

此处需要的时三进制状态，因为共有三种状态。0表示该点建立了旅游站点，1表示该点没有建旅游站点且没有被覆盖，2表示该点没有建旅游站点但被覆盖。

那么转移方程深思熟虑一下~~~可以得出

若该点不建旅游站点那么 如果该点被覆盖那么

f[d][s + 2 * pow[d]] = min(f[d][s + 2 * pow[d],f[d - 1][s]) 

否则如果该点没有被覆盖那么 

f[d][s + pow[d]] = min(f[d][s + pow[d],f[d - 1][s])。

若该点建旅游站点那么

f[d][sta] = min(f[d][sta],f[d - 1][s] + val[u]);

此处sta表示当前节点选后的状态即s中与它直接相连的点且状态为1的全部更改为2之后的状态。

那么主要的转移便结束了，此题还需要用dfs辅助完成。因为儿子的状态还有可能还会影响到父亲的状态。因此有个比较显然的转移

f[d][s] = min(f[d + 1][s],f[d + 1][s + 2 * pow[d + 1]]);

那么对于最终答案只用对每棵dfs树中的f[0][0] 和 f[0][2] 取min后累加即可。即ans += min(f[0][0],f[0][2]).

本题最后的时间复杂度为O（3^10（n + m)）;大约二十亿，那么再配上一句#pragma GCC optimize(2)，即可通过。

```cpp
#pragma GCC optimize(2)
#include <cstdio>
using namespace std;

const int maxn = 2.5e4 + 10;
const int inf = 0x3f3f3f3f;
struct Node{
    int to,next;
} f[maxn << 1];
int n,m,val[maxn],stu[maxn],dp[15][1 << 15],dep[maxn],cnt = 0,ans,tmp[maxn],pow[maxn];
bool vis[maxn];

int min(int a,int b) {return a < b ? a : b;}

int read()
{
    int x = 0;
    char ch = getchar();
    while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0';ch = getchar();}
    return x;
}

void add(int u,int v) {f[++ cnt].to = v;f[cnt].next = stu[u];stu[u] = cnt;}

void dfs(int u)
{
    vis[u] = 1;
    int d = dep[u],cnt = 0;
    if (!d) dp[0][0] = val[u],dp[0][1] = 0,dp[0][2] = inf; else 
    {
        for (int i = stu[u]; i; i = f[i].next)
            if (vis[f[i].to] && dep[f[i].to] < d) tmp[++ cnt] = dep[f[i].to];
        for (int s = 0; s < pow[d + 1]; ++ s) dp[d][s] = inf;
        for (int s = 0; s < pow[d]; ++ s) 
        {
            int sta = s,t = 1;
            for (int i = 1; i <= cnt; ++ i)
                if (s / pow[tmp[i]] % 3 == 0) t = 2; //s / pow[tmp[i]] % 3 是s中深度为tmp[i]的点的状态。
                else if (s / pow[tmp[i]] % 3 == 1) sta += pow[tmp[i]];
            dp[d][s + t * pow[d]] = min(dp[d][s + t * pow[d]],dp[d - 1][s]);
            dp[d][sta] = min(dp[d][sta],dp[d - 1][s] + val[u]);
        }
    }
    for (int i = stu[u]; i; i = f[i].next)
    {
        if (vis[f[i].to]) continue;
        dep[f[i].to] = d + 1;
        dfs(f[i].to);
        for (int s = 0; s < pow[d + 1]; ++ s)
            dp[d][s] = min(dp[d + 1][s],dp[d + 1][s + 2 * pow[d + 1]]);
    }
}

int main()
{
    pow[0] = 1;
    for (int i = 1; i <= 13; ++ i) pow[i] = pow[i - 1] * 3;
    n = read(),m = read();
    for (int i = 1; i <= n; ++ i) val[i] = read();
    for (int i = 1,u,v; i <= m; ++ i) 
        u = read(),v = read(),add(u,v),add(v,u);
    for (int i = 1; i <= n; i ++)
    {
        if (vis[i]) continue;
        dfs(i);
        ans += min(dp[0][0],dp[0][2]);
    }
    printf("%d",ans);
    return 0;
}
```



---

## 作者：zifanwang (赞：8)

考虑在无向图上进行 dfs，可以得到很多棵 dfs 树（因为图不一定连通），这些树形成了一个森林。

然后由任意两点间不存在节点数超过 $10$ 的简单路径这个限制可以得出这些树的深度都不超过 $10$，然后可以想到树上状压 dp。

有一个重要的性质，就是无向图 dfs 树上的非树边，一定是回边，所以**不存在横叉边**。这也是我们状压这些节点的父亲状态的原因。

对于一个节点，我们用一个数（$0,1,2$）表示这个节点的状态：

* 用 $0$ 表示在这个节点上没有建立站点 且 所有已经访问过的且跟这个节点相邻的节点都没有建立站点。

* 用 $1$ 表示 在这个节点没有建立站点 但是 存在一个已经访问过的且跟这个节点相邻的节点建立了站点。

* 用 $2$ 表示在这个节点上有建立站点。

下面就是动态规划。

我们用 $dp[i][j]$ 记录一个最小费用。其中 $j$ 在三进制表示下从低到高的每一位分别表示从根节点到节点 $i$ 的路径上的每一个节点的状态。

$dp[i][j]$ 表示现在从根节点到节点 $i$ 的路径的状态是 $j$，在所有已经访问过的节点里，除了从根节点到节点 $i$ 的路径上的节点以外的所有节点都已经满足了题目中的条件，最小费用是多少。

在 dfs 的过程中当访问到一个节点 $x$ 时，若 $x$ 是根节点，则 $dp[x][0]=0,dp[x][1]=\inf,dp[x][2]=c[x]$，否则我们用 $fa$ 表示 $x$ 的父亲，$d_x$ 表示 $x$ 的深度（根节点深度为 $0$），我们枚举每一个 $dp[fa][i]$ 对 $x$ 进行转移（也就是刷表法）。

我们先枚举每一个跟 $x$ 相邻且已经访问过的节点 $y$（由前面的性质可以知道这个节点一定是 $x$ 的祖先），求出两个值 $S$ 和 $T$，初始化 $T=0,S=i$：

* 若 $y$ 的状态是 $2$，则令 $T=1$

* 若 $y$ 的状态是 $0$，则令 $S=S+3^{d_y}$

下面考虑是否在 $x$ 建立站点：

* 若不在 $x$ 建立站点，可以这样更新：

$$dp[x][i+T\times3^{d_x}]=\min(dp[x][i+T\times3^{d_x}],dp[fa][i])$$

* 若在 $x$ 建立站点，可以这样更新：

$$dp[x][S+2\times3^{d_x}]=\min(dp[x][S+2\times3^{d_x}],dp[fa][i]+c[x])$$

从父亲转移过了以后下面就继续 dfs，每访问一个 $x$ 的儿子 $y$，就会增加很多已经访问过的节点，所以这时候 $x$ 的 $dp$ 状态就不对了，我们要用 $y$ 来更新 $x$（因为 $y$ 的 $dp$ 状态是正确的）。

对于每一个 $dp[x][i]$，我们令：

$$dp[x][i]=\min(dp[y][i+3^{d_y}],dp[y][i+2\times 3^{d_y}])$$

$\min$ 里的两个值分别代表在 $y$ 不建立和建立站点的费用。

最终的答案就是每一棵树的 $\min(dp[root][1],dp[root][2])$ 的和，这里 $root$ 表示根节点。

到这里差不多就结束了，但是你会发现内存太大了。

由于每一个节点的状态只跟它的父亲和儿子有关，我们可以用这个节点的深度表示这个节点，具体的方法详见代码。

时间复杂度 $O(3^{10}(n+m))$。

代码：
```cpp
#include<bits/stdc++.h>
#define mxn 20003
#define pb push_back
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define rept(i,a,b) for(int i=a;i<b;++i)
using namespace std;
int n,m,ans,pw[13],ds[mxn],c[mxn],dp[13][59049];
vector<int>g[mxn];
bool v[mxn];
void dfs(int x,int d){
	v[x]=1,ds[x]=d;
	if(!d){
		dp[0][0]=0;
		dp[0][1]=1e9;
		dp[0][2]=c[x];
	}else{
		rept(i,0,pw[d+1])dp[d][i]=1e9;
		rept(i,0,pw[d]){
			int t=0,s=i;
			for(int j:g[x])if(v[j]){
				if(i/pw[ds[j]]%3==2)t=1;
				else if(i/pw[ds[j]]%3==0)s+=pw[ds[j]];
			}
			dp[d][i+t*pw[d]]=min(dp[d][i+t*pw[d]],dp[d-1][i]);
			dp[d][s+2*pw[d]]=min(dp[d][s+2*pw[d]],dp[d-1][i]+c[x]);
		}
	}
	for(int i:g[x])if(!v[i]){
		dfs(i,d+1);
		rept(j,0,pw[d+1])dp[d][j]=min(dp[d+1][j+pw[d+1]],dp[d+1][j+pw[d+1]*2]);
	}
}
signed main(){
	pw[0]=1;
	rep(i,1,11)pw[i]=pw[i-1]*3;
	scanf("%d%d",&n,&m);
	rep(i,1,n)scanf("%d",&c[i]);
	for(int i=0,x,y;i<m;++i){
		scanf("%d%d",&x,&y);
		g[x].pb(y),g[y].pb(x);
	}
	rep(i,1,n)if(!v[i]){
		dfs(i,0);
		ans+=min(dp[0][1],dp[0][2]);
	}
	cout<<ans;
	return 0;
}
```

最后提醒：记得开 O2。


---

## 作者：Purslane (赞：2)

# Solution

这么喜欢卡常 /fn

显然求出一棵 DFS 树，深度不超过 $10$。在 DFS 树上进行树形 DP。

记录 $dp_{S}$ 表示当前 $u$ 和 $u$ 的所有祖先的状态：

- $0$ 表示当前节点没有放置关键点，且目前也没有相邻关键点；
- $1$ 表示当前节点放置了关键点；
- $2$ 表示当前节点没有放置关键点，且存在相邻关键点。

随着你的遍历，有两种操作：

1. 访问到儿子去。这时候枚举儿子节点有没有放置关键点即可。
2. 回溯。这时候要求儿子节点必须是状态 $1/2$。

可以做到 $O(3^{10}(n+m))$。

注意常数。以及图可能有多个连通块，需要依次累加。

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=20000+10,MAXM=60000+10;
int n,m,ans,c[MAXN],dep[MAXN],dp[MAXM],p3[MAXN];
vector<int> G[MAXN],T[MAXN],U[MAXN];
inline void dfs(const int u,const int f) {
	dep[u]=dep[f]+1;
	for(auto v:G[u]) {
		if(dep[v]) {
			if(dep[v]<dep[u]) U[u].push_back(v);
			continue ;	
		}
		dfs(v,u),T[u].push_back(v);
	}
	return ;
}
int w[15][MAXM];
inline void solve(const int u) {
	ffor(i,0,p3[dep[u]-1]-1) {
		int st=i;
		for(auto v:U[u]) if(w[dep[v]-1][st]==1) {st+=2*p3[dep[u]-1];break ;}
		dp[st]=min(dp[st],dp[i]); 
		st=i+p3[dep[u]-1];
		for(auto v:U[u]) if(w[dep[v]-1][st]==0) st+=2*p3[dep[v]-1];
		dp[st]=min(dp[st],dp[i]+c[u]);	
	}
	for(auto v:T[u]) solve(v);
	ffor(i,0,p3[dep[u]]-1) {
		if(i<p3[dep[u]-1]) {dp[i]=0x3f3f3f3f;continue ;}
		dp[i%p3[dep[u]-1]]=min(dp[i%p3[dep[u]-1]],dp[i]);
		if(i>p3[dep[u]-1]-1) dp[i]=0x3f3f3f3f;
	}
	return ;
}
vector<int> rt;
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>m,memset(dp,0x3f,sizeof(dp)),p3[0]=1;
	ffor(i,1,10) p3[i]=p3[i-1]*3;
	ffor(i,0,p3[10]) ffor(j,0,10) w[j][i]=(i/p3[j])%3;	
	ffor(i,1,n) cin>>c[i];
	ffor(i,1,m) {int u,v;cin>>u>>v,G[u].push_back(v),G[v].push_back(u);}
	ffor(i,1,n) if(!dep[i]) rt.push_back(i),dfs(i,0);
	for(auto id:rt) dp[0]=0,solve(id),ans+=dp[0];
	cout<<ans;
	return 0;
}
```

---

## 作者：i_love_xqh (赞：2)

# 题目链接

[P3577 [POI2014] TUR-Tourism](https://www.luogu.com.cn/problem/P3577)。

# 分析

## 题目大意

给出 $n$ 个点 $m$ 条边的无向图，在第 $i$ 个点建立旅游站点花费 $c_i$，求最小的花费使每个点要么建立了旅游站点，要么它连出去的点中至少一个建立了旅游站点。

## 题目分析

注意到一个关键的信息：

> **任意两点间不存在节点数超过 $10$ 的简单路径。**

这也就说明了该图的每个连通块内的生成树深度不超过 $10$，于是便容易想出用树形加状压 dp，~~虽然在老师讲之前我就没往 dp 上想过~~。

考虑状态设计，$f_{s,u}$ 肯定有一维 $s$ 表示从根节点到当前节点的路径上的状态，那至于 $u$，如果表示为当前位于节点 $u$，那么空间将会爆，便考虑表示当前位于第 $u$ 层。

现在考虑每个点的状态。因为要考虑是否建站点和它周围节点是否建站点，所以可以得出 $3$ 种状态，$0$ 表示在该点建了站点，$1$ 表示没建站点且周围也没有站点，$2$ 表示没建站点但周围有站点。所以这是一个三进制下的状压。

现在考虑状态转移。

当 dfs 到一个点 $u$ 时，肯定会先被它的父亲转移，所以先枚举一维 $s$，表示从深度为 $0$（即根节点）到深度为 $dep_u-1$ 经过的路径的状态。然后在看它所连出去的点 $v$ 满足 $dep_v<dep_u$（因为要在路径上）在 $s$ 中的状态，然后可分为几种情况讨论（以下 $v$ 均表示满足 $u$ 与 $v$ 有边且 $dep_v<dep_u$ 的点）：

- 在当前 $u$ 点建站点，那么状态 $s$ 加上 $0\times 3^{dep_u}$ 即不变，然后由于 $u$ 建点的原因，所以如果 $s$ 的第 $v$ 位是 $1$，那么就会变为 $2$，所以 $s$ 还要再加上 $\sum{3^{dep_v}}$，记作 $cnt_u$，所以即可得出完整的转移方程：

$$
f_{s+cnt_u,dep_u}= f_{s,dep_u-1}+c_{u}
$$

- 接下来两种不在 $u$ 建站点的情况和 $s$ 的状态有关：
  - $\forall v$ 满足 $s$ 的第 $v$ 位不为 $0$，代表 $u$ 周围没有站点，那么状态 $s$ 加上 $1\times 3^{dep_u}$，则转移方程为：
  
  $$
  f_{s+1\times 3^{dep_u},dep_u}= f_{s,dep_u-1}
  $$
  
  - 至少一个 $v$ 满足 $s$ 的第 $v$ 为 $0$，代表 $u$ 周围有站点，那么状态 $s$ 加上 $2\times 3^{dep_u}$，则转移方程为：
  
  $$
  f_{s+2\times 3^{dep_u},dep_u}= f_{s,dep_u-1}
  $$
  
注意一点，第一种转移需要跟它本身取 $\min$，因为状态可能会重复。

但是这只是从父亲转移，当 dfs 完它儿子时，回溯时也要更新它自己，相当于将它下面的状态给处理完了，此时转移已经包含下面的了。

即枚举一维 $s$，但此时是枚举从深度为 $0$ 到深度为 $dep_u$ 了，需包含它自己，然后有：

$$
f_{s,dep_u}= \min(f_{s,dep_u+1},f_{s+2\times 3^{dep_u+1},dep_u+1})
$$

这里就有点抽象，其实本来有三种：

- $s$ 的 $dep_u$ 位为 $0$，那么就在 $f_{s,dep_u+1}$ 与 $f_{s+2\times 3^{dep_u+1},dep_u+1}$ 中取小，因为它儿子要么建要么不建，不建的话因为 $u$ 有站点，所以周围有站点。

- $s$ 的 $dep_u$ 位为 $1$，那么只能赋值为 $f_{s+2\times 3^{dep_u+1},dep_u+1}$，因为如果它儿子建了，那它应该是 $2$。

- $s$ 的 $dep_u$ 位为 $2$，那么只能赋值为 $f_{s,dep_u+1}$，因为它没建，所以它儿子必须建。

那为什么可以直接赋值为两个中的较小值呢？因为后两种情况的另外一种赋值都没有被更新过，所以都是初始值正无穷。也可以换一种理解，这两种取值的更新都考虑过 $s$ 的第 $dep_u$ 位状态，所以可以理解为 $s$ 是确定的。

然后是一些细节，因为 $f_{s,u}$ 存的是第 $u$ 层，所以在每次从父节点更前时，都应初始化正无穷；至于根节点的赋值，有 $f_{0,0}=c_{u}$，$f_{0,1}=0$，$f_{0,2}=\infty$，最终答案即为 $\min(f_{0,0},f_{0,2})$。然后还要考虑不连通的情况，答案每次累加。

Code：
```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int y,next;
}e[50010];
bool vis[20010];
int cnt,elast[20010];
void add(int x,int y){
	e[++cnt].y=y;
	e[cnt].next=elast[x];
	elast[x]=cnt;
}//链式前向星
int k[11];//预处理3的次幂
int f[11][60000];//0:建,1:不建未覆盖,2:不建但覆盖 
int dep[20010];
int c[20010];
int getnum(int s,int p){
	return s/k[p]%3;
}//看s的第p位
vector<int>fath;
void dfs(int u){
	vis[u]=true;
	if(!dep[u]){
		f[0][0]=c[u];
		f[0][1]=0;
		f[0][2]=1e9;//给根节点初始化
	}
	else{
		fath.clear();
		for(int i=elast[u];i;i=e[i].next){
			int v=e[i].y;
			if(dep[v]<dep[u]){
				fath.push_back(v);
			}//先存入所有满足条件的v，节省时间复杂度
		}
		for(int s=0;s<k[dep[u]+1];s++)f[dep[u]][s]=1e9;//初始化为正无穷
		for(int s=0;s<k[dep[u]];s++){//枚举状态
			int sum=0,ts=0;
			for(auto v:fath){
				if(getnum(s,dep[v])==1)sum+=k[dep[v]];
				if(getnum(s,dep[v])==0)ts++;
			}
			f[dep[u]][s+sum]=min(f[dep[u]][s+sum],f[dep[u]-1][s]+c[u]);
			if(ts)f[dep[u]][s+2*k[dep[u]]]=f[dep[u]-1][s];
			else f[dep[u]][s+k[dep[u]]]=f[dep[u]-1][s];//由父节点更新
		}
	}
	for(int i=elast[u];i;i=e[i].next){
		int v=e[i].y;
		if(!vis[v]){
			dep[v]=dep[u]+1;
			dfs(v);
			for(int s=0;s<k[dep[u]+1];s++){//枚举状态
				f[dep[u]][s]=min(f[dep[u]+1][s],f[dep[u]+1][s+2*k[dep[u]+1]]);//由子节点更新
			}
		}
	}
}
int main(){
	int ans=0;
	k[0]=1;
	for(int i=1;i<=10;i++)k[i]=k[i-1]*3;
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&c[i]),dep[i]=11;
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){//可能存在多个连通块的情况
			dep[i]=0;
			dfs(i);
			ans+=min(f[0][0],f[0][2]);//求和
		}
	}
	printf("%d",ans);
	return 0;
}
```

---

## 作者：Forg1weN (赞：2)

## 题面


给定一个 $n$ 个点，$m$ 条边的无向图，其中你在第 $i$ 个点建立旅游站点的费用为 $C_i$。在这张图中，任意两点间不存在节点数超过 $10$ 的简单路径。请找到一种费用最小的建立旅游站点的方案，使得每个点要么建立了旅游站点，要么与它有边直接相连的点里至少有一个点建立了旅游站点。

$2\le n\le 20\ 000$ ,$0\le m\le 25\ 000,c_i\le10^5$

## Solution

介绍几个概念

**无向图的生成树**：指根据某一个节点根据 dfs 序构造出的树

**返祖边**：由深度深的节点连向深度浅的祖先的边

题目给出了一个无向图的生成树森林。

记 $f_{i,j}$ 表示当前深度为 $i$ 的节点其连向祖先的链的状态为 $j$。其中，$j$ 由若干个 $0/1/2$ 组成，意义如下。

- $0$：当前节点选。
- $1$：当前节点不选且不覆盖。
- $2$：当前节点不选但被覆盖。

每一个节点会影响儿子，同时也会被儿子影响。

记 $i$ 为从根节点到 $i$ 节点链的状态，记 $x$ 为当前节点状态。

**首先，在递归到下一层之前要考虑祖先对当前节点的影响。**

如果 $i$ 不选，但是祖先选了，则 $x=2$。

$f_{dep_u,i+2\times 3^{dep_u}}\leftarrow f_{dep_u-1,i}$

如果 $i$ 不选，但是祖先不选，则 $x=1$。

$f_{dep_u,i+1\times 3^{dep_u}}\leftarrow f_{dep_u-1,i}$

如果 $i$ 选了，则当前节点无论如何 $x=0$

若祖先没选，则祖先 $fa$ 位置上数字为 $1$，将会变成 $2$。

 $f_{dep_u,i+3^{dep_{fa}}}\leftarrow f_{dep_u-1,i}+a_u$。
 
 若祖先选了，则：
 
$f_{dep_u,i}\leftarrow f_{dep_u-1,i}+a_u$。

在儿子节点 $v$ 递归完后，当前的 $f_{dep_u,i}$ 就不代表整棵树的最优解了，要从 $v$ 递归回去，这里的转移要求 $v$ 被覆盖。

$f_{dep_u,i}\leftarrow f_{dep_v,i,},f_{dep_v,i+2\times 3^{dep_v}}$

复杂度是跟深度挂钩的，如本题最大为 $10$，可以通过。

时间复杂度 $O(3^{dep}\times m)$。

## code 
自写不难，主要解释了缺乏注释的题解，略去。

---

## 作者：lupengheyyds (赞：2)

# P3577 [POI2014] TUR-Tourism

可能很多人看到这道题既可以从父亲更新到儿子，又可以从儿子更新到父亲的时候，很多人都跟我一样是这样的：

![pADjOoV.jpg](https://s21.ax1x.com/2024/11/02/pADjOoV.jpg)

于是这里分享一下我的一种思考。

---

直径 $\le 10$，可以先求出 DFS 生成森林，这样树高不超过 $10$ 且没有横叉边，我们使返祖边是通过祖先限制后代，于是可以记录节点到根节点所有点的状态，共三种：

- $0$：这个点选择了。

- $1$：这个点没选择且相邻点没有选择（没被覆盖）。

- $2$：这个点没选择且相邻点有选择（被覆盖）。

首先求出这个树的欧拉序，下文中 $x_i$ 表示欧拉序第 $i$ 个位置的节点编号。

令 $f_{i,j}$  表示考虑欧拉序前 $i$ 个位置，$x_i$ 到根的路径上的状态为 $j$ 时的最小代价。由于一个节点需要受到其祖先节点状态的限制，所以每个节点的决策（选或不选）应该在其欧拉序中第一个位置进行。
考虑 $i-1\to i$ 的一次转移，假设之前的状态为 $s=j$。

- 如果 $x_{i-1}=fa_{x_i}$ 也就是说这是一条向下的边，考虑 $x$的的决策：
  
  - 如果 $x_i$ 选择，那么当前节点的状态无论如何都是 $0$，考虑与 $x_i$ 有边的一个祖先 $z$：
    
    - 如果 $z$ 的状态为 $0,2$，则 $s$ 不作改变。
    
    - 如果 $z$ 的状态为 $1$，则 $s\to s+2\times 3^{dep_z}$。
  
  - 如果 $x_i$ 不选择，那么看当前节点有没有被自己的祖先覆盖：
    
    - 如果没覆盖，则 $s\to s+3^{dep_{x_i}}$。
    
    - 如果被覆盖，则 $s\to s+2\times 3^{dep}$。
  
  最后让 $dp_{i,s}\leftarrow dp_{i-1,j}$。

- 如果 $fa_{x_{i-1}}=x_i$，也就是说这是一条向上的边，直接 $dp_{i,j}=\min\{dp_{i-1,j},dp_{i-1,j+2\times 3^{dep_{x_{i-1}}}}\}$。

最后一棵树的答案就是 $\min\{dp_{2n-1,0},dp_{2n-1,2}\}$，最终答案就是所有树的答案之和。

---

其实我们没有必要真正的把欧拉序列求出来，直接在 DFS 遍历的过程中求一下就行了，复杂度 $\mathcal O(3^hm)$，但是很多状态是不必要的，卡卡常就过了。

---

## 作者：DYYqwq (赞：1)

首先考虑在这个图上生成一个森林，然后在上面 dp。

注意到“任意两点间不存在节点数超过 $10$ 的简单路径”，于是得知树的深度必然 $\le 10$。

然后发现这是唯一的入手点，考虑状态压缩。

考虑设 $dp_{i,j}$ 表示 dfs 序小于 $i$ 节点的所有节点（不包括节点 $i$ 到根节点的这条路径上的）都被覆盖的最小费用，$j$ 为一个三进制数字，表示节点 $i$ 到根节点的这条路径上的所有节点的状态。

至于为什么要设 $3$ 种状态：因为只有一个“是否被覆盖”或者只有一个”是否放置旅游站点“是不够用的。

那么就考虑把它们拼起来：$0$ 表示被覆盖，且放置旅游站点；$1$ 表示没被覆盖，且不放置旅游站点；$2$ 表示被覆盖，且放置旅游站点。

每次看当前点放不放置，然后从父亲节点继承一下，算一下就行。

但是有一个严峻的问题。

举个例子，比如给你一个链，你按照前文正常的继承，转移，但是回溯的时候发现一个问题：

当前节点的儿子可能还没被覆盖。

因为你在转移孩子的时候，孩子的状态是被压在 $j$ 里的，但是现在它不在 $j$ 中压缩了，按照我们的 dp 设计，它现在必然要被覆盖了。

因此要记得回溯的时候更新当前节点 dp 值。

然后还有一个细节问题，我们最开始就说过我们生成出了一个森林，因此最终答案是每棵树的最优加起来。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int to , nxt;
}e[400010];
int n , m , a[20010] , head[20010] , tot , q[20010] , dep[20010];
long long ans , dp[20][177148] , pow3[12] = {1 , 3 , 9 , 27 , 81 , 243 , 729 , 2187 , 6561 , 19683 , 59049 , 177147}; // pow3 处理到第 11 个，因为最高就是 10. 
bool vis[20010];
void add(int u , int v)
{
	++ tot;
	e[tot].to = v;
	e[tot].nxt = head[u];
	head[u] = tot;
}
#define calc(x , y) (x / pow3[dep[y]] % 3) //	用于计算 x 的 3 进制第 y 位。这东西没法左右移很烦人。 
// long long calc(int x , int y)
// {
// 	return x / pow3[dep[y]] % 3;
// }
void dfs(int u)
{
	vis[u] = 1;// , dep[u] = dep[fa] + 1;
	int cnt = 0;
	for(int i = head[u] ; i != 0 ; i = e[i].nxt)
	{
		int v = e[i].to;
		if(vis[v] && dep[v] < dep[u]) q[++ cnt] = v;
	}
	if(!dep[u]) dp[0][0] = a[u] , dp[0][1] = 0 , dp[0][2] = INT_MAX;
	else
	{
		for(int j = 0 ; j < pow3[dep[u] + 1] ; j ++) dp[dep[u]][j] = INT_MAX;
		for(int i = 0 ; i < pow3[dep[u]] ; i ++)
		{
			long long sum1 = 1 , sum2 = i;
			for(int j = 1 ; j <= cnt ; j ++)
			{
				if(calc(i , q[j]) == 0) sum1 = 2;
				if(calc(i , q[j]) == 1) sum2 += pow3[dep[q[j]]];
			}
			dp[dep[u]][i + sum1 * pow3[dep[u]]] = min(dp[dep[u]][i + sum1 * pow3[dep[u]]] , dp[dep[u] - 1][i]);
			dp[dep[u]][sum2] = min(dp[dep[u]][sum2] , dp[dep[u] - 1][i] + 1ll * a[u]);
		}
	}
	for(int i = head[u] ; i != 0 ; i = e[i].nxt)
	{
		int v = e[i].to;
		if(vis[v]) continue;
		dep[v] = dep[u] + 1;
		dfs(v);
		for(int j = 0 ; j < pow3[dep[v]] ; j ++) dp[dep[u]][j] = min(dp[dep[v]][j] , dp[dep[v]][j + 2 * pow3[dep[v]]]);
	}
}
signed main()
{
	scanf("%d%d" , &n , &m);
	for(int i = 1 ; i <= n ; i ++) scanf("%d" , &a[i]);
	for(int i = 1 , u , v ; i <= m ; i ++) scanf("%d%d" , &u , &v) , add(u , v) , add(v , u);
	for(int i = 1 ; i <= n ; i ++)
		if(!vis[i]) dfs(i) , ans += min(dp[0][0] , dp[0][2]); // !vis 说明这是一个树的根节点，所以算一下 
	printf("%lld" , ans);
	return 0;
}
```

---

