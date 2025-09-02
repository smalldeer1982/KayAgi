# [QkOI#R1] Quark and Tree

## 题目描述

给定一棵包含 $n$ 个节点的树，每个节点上有一个点权，点的编号为 $1\sim n$，请加一条不存在于给定的树中的边（且不能为自环），使加边后得到的基环树上所有点的深度与该点点权乘积之和最大。

我们认为基环树上的点的深度指该节点到环上的最短距离，特别地，环上的节点深度为 $0$。

形式化地，你需要添加一条不存在于给定的树中的边（且不能为自环），并最大化：

$$\sum_{i=1}^nw_i\times dep_i$$

其中 $w_i$ 为节点 $i$ 的权值，$dep_i$ 为节点 $i$ 在基环树中的深度。

## 说明/提示

### 样例解释

样例 1 给出的树如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/zl7p4xcu.png)

可以添加边 $(1,5)$，则新生成的基环树如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/p1p9jlbx.png)

各节点深度见下表：

![](https://cdn.luogu.com.cn/upload/image_hosting/90ygpc3c.png)



### 数据范围

**本题采用捆绑测试。**

对于所有数据，$3 \le n \le 10^6$，$-10^3 \le w_i \le 10^3$，$1 \le a_i,b_i \le n$。

+ 子任务 $1$（$10$ 分）：$n \le 200$。
+ 子任务 $2$（$20$ 分）：$n \le 10^3$。
+ 子任务 $3$（$40$ 分）：$w_i \ge 0$。
+ 子任务 $4$（$30$ 分）：无特殊限制。

## 样例 #1

### 输入

```
7
1 1 1 1 1 1 1
1 2
1 3
2 5
3 4
3 7
4 6```

### 输出

```
8```

## 样例 #2

### 输入

```
5
-6 3 -1 -7 -2
1 2
1 3
3 4
5 1```

### 输出

```
3```

# 题解

## 作者：xuezhe (赞：7)

首先不考虑加边，若仅计算以某个点为根时树中所有点的深度与点权乘积之和，可以用换根 DP 处理。

指定 $u$ 为基环树环上的一个点，且不是新加的边的端点，将其提为树根。

设以 $u$ 为根时，$i$ 在树中的父节点为 $f_i$，以点 $i$ 为根的子树中所有点的点权和为 $s_i$，$\operatorname{dis}(i,j)$ 为树上点 $i$ 与点 $j$ 的距离，$dep_i=dis(u,i)$。

下面给出一棵树为例：

![](https://cdn.luogu.com.cn/upload/image_hosting/4b53ds1s.png)

为保证 $u$ 在环上，取位于不同子树中的 $v,w$ 两点连边，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/bcwj0aev.png)

则所有点在基环树中的深度变为它到环上的点的最短距离，可以发现离一个点最近的环上的点必然是其本身或其祖先节点中在环上的深度最深的点。这里设离点 $i$ 最近的环上的点为 $d_i$，则基环树中点 $i$ 的深度相比原先在树中的深度减少 $\operatorname{dis}(u,i)-\operatorname{dis}(d_i,i)=\operatorname{dis}(u,d_i)=dep_{d_i}$，故对答案的贡献相比原先减少 $w_i dep_{d_i}$。

考虑将 $d_i$ 相同的点一起计算。设环上的点集为 $S$，则对答案的贡献减少量形如 $\sum_{i\in S} t_i dep_i$，其中 $t_i=\sum_{j=1}^{n}[d_j=i]w_j$。接下来考虑 $d_i$ 相同的点的条件。设环上有一点对 $(x,y)$，满足在原先的树中 $x$ 是 $y$ 的父节点，则若以 $x$ 为根的子树中的一点 $i$ 满足 $d_i \neq x$，当且仅当它是以 $y$ 为根的子树中的点，故 $t_x=s_x-s_y$。考虑到点 $u$ 在树中没有父节点，且 $dep_u=0$，故 $d_i=u$ 的点不对答案的减少造成影响。将上式 $s_x-s_y$ 中 $-s_y$ 的贡献移至点 $y$ 进行计算，可得出答案贡献减少量为 $\sum_{i \in S \land i \neq u} s_i dep_i-s_i dep_{f_i}$，由于父子节点深度差为 1，故最终得出的贡献减少量为 $\sum_{i \in S \land i \neq u} s_i$。

所以最终的问题就是找出两条与 $u$ 相连且无重叠部分的两条链，满足两条链上所有点的 $s_i$ 之和最小，同样也可以用类似于换根 DP 的方法处理。

最终只需要枚举点 $u$，利用换根 DP 得到的信息求出以 $u$ 为根的树的答案。假设以 $u$ 为根时树中所有点的深度与点权乘积之和为 $t_u$，满足上述条件的两条链上所有点的 $s_i$ 之和为 $l_u$（这里的两条链不包括点 $u$），则以 $u$ 为根的树的答案为 $t_u-l_u$，取最小值即可。

时间复杂度 $O(n)$。

代码：
```
//似乎挺多人反映细节多qwq，但出题人感觉这么想细节并不会太多？
#include <cstdio>
#include <cctype>
#include <cstring>
#define MaxN (1000005)
using namespace std;
typedef long long ll;
void Read(int &x){
    static char c;
    static int f;
    f=1;
    while(!isdigit(c=getchar()))
        if(c=='-')
            f=-1;
    x=(c^48);
    while(isdigit(c=getchar()))
        x=x*10+(c^48);
    x*=f;
    return;
}
void Print(ll x){
    if(x<0)
        putchar('-'),x=-x;
    static ll i;
    for(i=1;i*10LL<=x;i*=10);
    for(;i;i/=10)
        putchar(x/i%10|48);
    putchar('\n');
    return;
}
inline ll mmax(ll a,ll b){return a>b?a:b;}
inline ll mmin(ll a,ll b){return a<b?a:b;}
struct LnkNode{
    int v,nxt;
}edge[MaxN*2];
int etot,fst[MaxN];
inline void addedge(int u,int v){
    ++etot;
    edge[etot].v=v;
    edge[etot].nxt=fst[u];
    fst[u]=etot;
    return;
}
int n,w[MaxN],s[MaxN];
ll d[MaxN],dm[MaxN],sdm[MaxN],res=-9223372036854775807LL;
void dfs1(int x,int f){
    s[x]=w[x];
    ll t;
    for(int i=fst[x];i;i=edge[i].nxt)
        if(edge[i].v!=f){
            dfs1(edge[i].v,x);
            s[x]+=s[edge[i].v];
            d[x]+=d[edge[i].v]+s[edge[i].v];
            t=s[edge[i].v]+mmin(dm[edge[i].v],0);
            if(t<dm[x])
                sdm[x]=dm[x],dm[x]=t;
            else if(t<sdm[x])
                sdm[x]=t;
        }
    return;
}
void dfs2(int x,int f){
    if(f){
        d[x]=d[f]+s[1]-s[x]*2;
        ll t=s[1]-s[x]+mmin((dm[f]!=s[x]+mmin(dm[x],0))?(dm[f]):(sdm[f]),0);
        if(t<dm[x])
            sdm[x]=dm[x],dm[x]=t;
        else if(t<sdm[x])
            sdm[x]=t;
    }
    if(sdm[x]!=0x3f3f3f3f3f3f3f3fLL && d[x]-dm[x]-sdm[x]>res)
        res=d[x]-dm[x]-sdm[x];
    for(int i=fst[x];i;i=edge[i].nxt)
        if(edge[i].v!=f)
            dfs2(edge[i].v,x);
    return;
}
int main(){
    int a,b;
    Read(n);
    memset(dm+1,0x3f,sizeof(ll)*n);
    memset(sdm+1,0x3f,sizeof(ll)*n);
    for(int i=1;i<=n;++i)
        Read(w[i]);
    for(int i=1;i<n;++i){
        Read(a);
        Read(b);
        addedge(a,b);
        addedge(b,a);
    }
    dfs1(1,0);
    dfs2(1,0);
    Print(res);
    return 0;
}
```

---

## 作者：suzhikz (赞：3)

首先那个基环树的意思其实就是选一条链，然后求每个店到链的最短距离乘上他的权值。

然后我们发现在 $x$ 子树中经过 $x$ 的链可以分解成他的一颗或两颗子树的链的贡献和其他子树的贡献（有点拗口，往下看就懂了），这样大的问题被划分成了小的问题，这就可以 dp 了。

我们定义 $dp_{0/1/2/3,i}$ 表示 $x$ 这颗子树中，没选，选了一条长度为 2 的链，选了一条长度大于 $2$ 的链，选了两条长度**大于等于** $2$ 的链。注意，我们这里的链要经过 $x$ 并且不能属于 $x$ 的同一颗子树。

为了辅助转移，我们定义 $sizw_i$ 为子树 i 中所有点的权值和。

那么有。


```cpp
void dfs(int x,int fa){
	ll maxx=-inf,tmp;
	sizw[x]=a[x];
	dp[1][x]=dp[2][x]=dp[3][x]=-inf;
	for(int i:g[x]){
		if(i==fa)continue;
		dfs(i,x);sizw[x]+=sizw[i];
		dp[0][x]=dp[0][x]+dp[0][i]+sizw[i];
	}
	for(int i:g[x]){
		if(i==fa)continue;
		dp[1][x]=max(dp[1][x],dp[0][x]-sizw[i]);
		ll tmp=-dp[0][i]-sizw[i]+max(dp[1][i],max(dp[0][i],dp[2][i]));
		dp[3][x]=max(dp[3][x],dp[0][x]+tmp+maxx);
		maxx=max(maxx,tmp);
		dp[2][x]=max(dp[2][x],dp[0][x]+-dp[0][i]-sizw[i]+max(dp[1][i],dp[2][i]));
	}
}
```

现在我们每颗子树中的最优的链都被我们算出来了，接下来考虑一个点的反子树对他的贡献。我们设 $fasizw_x$ 是 $x$ 的反子树的点权和。

假设 $x$ 的反子树的贡献为 $w_1$，那么他的子树 $i$ 的反子树的贡献就是 $w_1+dp_{0,x}-dp_{0,i}-sizw_i+fasizw_i$，其中， $fasizw_i=fasizw_x+sizw_x-sizw_i$。


```cpp
#include<bits/stdc++.h>
#define ll long long
#define reg register
#define db double
#define il inline
using namespace std;
void read(int &x){x=0;int f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=f;}
void read(ll &x){x=0;int f=1;char c=getchar();while(c>'9'||c<'0'){if(c=='-')f=-1;c=getchar();}while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}x*=f;}
const int N=1e6+5; const ll inf =1ll*10000000000000000;
int n,a[N];ll sizw[N];
ll dp[4][N];
vector<int>g[N];
//struct node{
//	ll w,pos;
//}z[N];int tot;
//bool cmp(node a,node b){
//	return a.w>b.w;
//}
void dfs(int x,int fa){
	ll maxx=-inf,tmp;
	sizw[x]=a[x];
	dp[1][x]=dp[2][x]=dp[3][x]=-inf;
	for(int i:g[x]){
		if(i==fa)continue;
		dfs(i,x);sizw[x]+=sizw[i];
		dp[0][x]=dp[0][x]+dp[0][i]+sizw[i];
	}
	for(int i:g[x]){
		if(i==fa)continue;
		dp[1][x]=max(dp[1][x],dp[0][x]-sizw[i]);
		ll tmp=-dp[0][i]-sizw[i]+max(dp[1][i],max(dp[0][i],dp[2][i]));
		dp[3][x]=max(dp[3][x],dp[0][x]+tmp+maxx);
		maxx=max(maxx,tmp);
		dp[2][x]=max(dp[2][x],dp[0][x]+-dp[0][i]-sizw[i]+max(dp[1][i],dp[2][i]));
	}
}
ll ans;
void work(int x,int fa,ll faw,ll fasizw){
	faw+=fasizw;
	if(g[x].size()==1&&fa!=0)return;
	ans=max(ans,max(dp[2][x],dp[3][x])+faw);
	ll summ=sizw[x];
	faw+=dp[0][x];
	for(int i:g[x]){
		if(i==fa)continue;
		work(i,x,faw-dp[0][i]-sizw[i],summ-sizw[i]+fasizw);
	}
	
}
int main(){
	read(n);
	for(int i=1;i<=n;i++)read(a[i]);
	for(int u,v,i=1;i<n;i++){
		read(u);read(v);g[u].push_back(v);g[v].push_back(u);
	}
	dfs(1,0);ans=-inf;
	work(1,0,0,0); 
//	for(int i=1;i<=n;i++)printf("%lld %lld %lld %lld\n",dp[0][i],dp[1][i],dp[2][i],dp[3][i]); 
	cout<<ans;
	return 0;
}

```

---

## 作者：liuyz11 (赞：3)

其实这题和基环树并没有什么关系，相当于以一个点为根选 $2$ 条链。

先算出不加边总答案,每选一个点会对答案减少的贡献等于该点子树的点权之和。

先考虑以 $1$ 为根.

用 $dp1_i$ 表示以 $i$ 为根的子树的减少贡献最小的链,用 $dp2_i$ 表示次小的链.

得出转移方程 $dp1_u = \min \{ \min\{dp1_v, 0\} + sum_v\}$ ，$dp2_u$ 同理为次小的.

初值对于每一个叶子节点的 $dp1$ 为0.

$sum_v$ 表示以 $v$ 为根的子树点权之和.

然后考虑换根.

将根从 $u$ 换到 $v$,总答案会加上 $sum_1 - 2 \cdot sum_v$.

用 $dp3_i$ 表示以 $i$ 为根向上的链会减少的贡献的最少值.

对于一对相邻的点 $u,v$,其中 $u$ 是 $v$ 的父亲.

首先 $(u,v)$ 这条边必选，贡献为 $sum_1 - sum_v$,从 $u$ 转移有三种可能:不选任何其他边，选 $u$ 点以上的链，选以 $u$ 为根的最小的链(如果最小那条链经过 $v$,就选次小的链)

最后对于每个非叶子结点 $i$ ,答案为

总答案$ - dp1_i - min(dp2_i,dp_3) - sum_1$（因为 $i$ 点的贡献没有减所以要减去总点权 $sum_1$ ）

参考代码：

```cpp
#include <bits/stdc++.h>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define clr(x, y) memset(x, y, sizeof(x))
using namespace std;
typedef long long ll;
const int MAXN = 1000005;
const ll INF = 1ll << 60;

int cnt = 0;
ll ans = -INF, res = 0;
ll a[MAXN], sum[MAXN];
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1];
ll dp1[MAXN], dp2[MAXN], dp3[MAXN], d[MAXN];

void addedge(int u, int v){
	nxt[cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
	cnt++;
}

void dfs1(int u, int fa){
	int flag = 0;
	sum[u] = a[u];
	for(int e = head[u]; e != -1; e = nxt[e]){
		int v = to[e];
		if(v == fa) continue;
		flag = 1;
		dfs1(v, u);
		sum[u] += sum[v];
		if(min(0ll, dp1[v]) + sum[v] < dp1[u]){
			dp2[u] = dp1[u];
			dp1[u] = min(0ll, dp1[v]) + sum[v];
			d[u] = v;
		}
		else dp2[u] = min(dp2[u], min(0ll, dp1[v]) + sum[v]);
	}
	if(!flag) dp1[u] = 0;
	res += sum[u];
}

void dfs2(int u, int fa, ll res){
	int flag = 0;
	//printf("%d %lld\n", u, res);
	for(int e = head[u]; e != -1; e = nxt[e]){
		int v = to[e];
		if(v == fa) continue;
		flag = 1;
		if(v == d[u]) dp3[v] = min(0ll, min(dp2[u], dp3[u])) + sum[1] - sum[v];
		else dp3[v] = min(0ll, min(dp1[u], dp3[u])) + sum[1] - sum[v];
		dfs2(v, u, res + sum[1] - 2 * sum[v]);
	}
	if(flag) ans = max(ans, res - dp1[u] - min(dp2[u], dp3[u]) - sum[1]);
}

int main(){
	clr(head, -1); 
	int n;
	scanf("%d", &n);
	rep(i, 1, n){
		scanf("%lld", &a[i]);
		dp1[i] = dp2[i] = dp3[i] = INF;
	}
	rep(i, 1, n - 1){
		int x, y;
		scanf("%d%d", &x, &y);
		addedge(x, y);
		addedge(y, x);
	}
	dfs1(1, -1);
	dfs2(1, -1, res);
	//rep(i, 1, n) printf("%lld %lld %lld %lld\n", i, dp1[i], dp2[i], dp3[i]);
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：tuget (赞：1)

从 $w_i \ge 0$ 开始考虑。

首先观察可知，此时选三元环一定是最优的，证明可以通过调整法证得。

于是考虑如何求出此时的答案，贡献的形式可以分为在两个儿子和自己组成的三元环和一个儿子和父亲组成的三元环，两种答案都可以通过换根求得，具体的定义 $s_u$ 为在以 $u$ 为根的子树内，$w_i$ 的和，$f_u$ 为在以 $u$ 为根的子树内，$\sum w_i \times dep_i$ 的值，转移 $f_u = \sum \limits_{v \in son_u} (f_v+s_v)$，这里 $s_v$ 代表的是 $u-v$ 这一条边的贡献。换根时 $g_v =g_u+s_1-s_u+f_u-f_v-s_v$。对于第一种贡献，答案为 $(f_u-f_{v1}-f_{v2}-s_{v1}-s_{v2})+f_{v1}+f_{v2}+(g_u+s_1-s_u)=f_u-s_{v1}-s_{v2}+g_u+s_1-s_u$，所以维护每个点的儿子中 $s$ 的最小次小值。对于第二种贡献，答案为 $(f_{u}-f_{v}-s_{v})+f_{v}+g_u=f_{u}+g_u-s_v$，维护最小的 $s$。

code

```
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000006
#define ll long long
#define frp freopen
#define fio(in,out) frp(in,"r",stdin),frp(out,"w",stdout)
inline void bug(){cout<<endl;}
template<typename TS,typename ... T>
inline void bug(TS p,T ... x){cout<<p<<" ";bug(x...);}
template<class T=int>
inline T read()
{
	T res=0,f=1;char c;
	for(;(c=getchar())<'0' || c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9')res=(res<<3)+(res<<1)+(c^48),c=getchar();
	return res*f;
}
int n,w[maxn];
ll f[maxn],s[maxn],mn[maxn][2],ans;
vector<int>g[maxn];
void dfs1(int u,int fa)
{
	s[u]=w[u];
	for(int v:g[u])if(v!=fa)
	{
		dfs1(v,u),s[u]+=s[v],f[u]+=f[v]+s[v];
		if(mn[u][1]==0||s[mn[u][1]]>s[v])mn[u][1]=v;
		if(mn[u][0]==0||s[mn[u][0]]>s[mn[u][1]])swap(mn[u][0],mn[u][1]);
	}
}
void dfs(int u,int fa,ll nw)
{
	if(g[u].size()>2)ans=max(ans,f[u]+nw+s[1]-s[u]-s[mn[u][0]]-s[mn[u][1]]);
	if(g[u].size()>1&&u!=1)ans=max(ans,f[u]+nw-s[mn[u][0]]);
	for(int v:g[u])if(v!=fa)
		dfs(v,u,nw+s[1]-s[u]+f[u]-s[v]-f[v]);
}
int main()
{
	int i,u,v;
	n=read();
	for(i=1;i<=n;++i)w[i]=read();
	for(i=1;i<n;++i)u=read(),v=read(),g[u].push_back(v),g[v].push_back(u);
	dfs1(1,0);
	dfs(1,0,0);
	printf("%lld",ans);
	return 0;
}

```

有了三元环的做法后，思考为什么不能推广成 $w_i$ 为任意值的，原因是最终选出的环不一定是三元环了。考虑刻画任意环的贡献，由前面三元环的贡献，容易发现在计算环的时候，若环在以 $u$ 为根的子树内，且包含 $u$，因为在计算过程中，$f_{v1}$ 和 $f_{v2}$ 被抵消了，贡献的形式一定形如：$f_u-\sum s_{v1}-\sum s_{v2}$，$v1$，$v2$ 是两条以 $u$ 为起点的不同的链上的点，所以定义 $val_u$ 表示钦定 $s_u$ 必选，最短的链长，再维护 $h_u$ 表示钦定 $s_u$ 必选，链长至少为 $2$ 的最短链长。这样最终的答案就是 $f_u-val_{v1}-val_{v2}+g_u+s_1-s_u$ 和 $f_{u}+g_u+s_1-s_u-h_v$。

注意一些细节，能贡献第一类贡献的点要么是 $1$ 号点且度数大于 $1$ 要么是度数大于 $2$。

code

```
#include<bits/stdc++.h>
using namespace std;
#define maxn 1000006
#define ll long long
#define frp freopen
#define fio(in,out) frp(in,"r",stdin),frp(out,"w",stdout)
inline void bug(){cout<<endl;}
template<typename TS,typename ... T>
inline void bug(TS p,T ... x){cout<<p<<" ";bug(x...);}
template<class T=int>
inline T read()
{
	T res=0,f=1;char c;
	for(;(c=getchar())<'0' || c>'9';c=='-'?f=-f:0);
	while(c>='0' && c<='9')res=(res<<3)+(res<<1)+(c^48),c=getchar();
	return res*f;
}
int n,w[maxn];
ll f[maxn],s[maxn],h[maxn],mn[maxn][2],ans,val[maxn];
vector<int>g[maxn];
void dfs1(int u,int fa)
{
	s[u]=w[u];
	for(int v:g[u])if(v!=fa)
		dfs1(v,u),s[u]+=s[v],f[u]+=f[v]+s[v];
	val[u]=s[u];
	for(int v:g[u])if(v!=fa)
	{
		val[u]=min(val[u],s[u]+val[v]);
		h[u]=min(h[u],s[u]+val[v]);
		if(mn[u][1]==0||val[mn[u][1]]>val[v])mn[u][1]=v;
		if(mn[u][0]==0||val[mn[u][0]]>val[mn[u][1]])swap(mn[u][0],mn[u][1]);
	}
}
void dfs(int u,int fa,ll nw)
{
	if(g[u].size()>2||(u==1&&g[u].size()>1))ans=max(ans,f[u]+nw+s[1]-s[u]-val[mn[u][0]]-val[mn[u][1]]);
	for(int v:g[u])if(v!=fa)
		dfs(v,u,nw+s[1]-s[u]+f[u]-s[v]-f[v]),
		ans=max(ans,f[u]+nw+s[1]-s[u]-h[v]);
}
int main()
{
	int i,u,v;
	fio("tree.in","tree.out");
	n=read();
	memset(val,63,sizeof(val));
	memset(h,63,sizeof(h));
	ans=-9223372036854775807LL;
	for(i=1;i<=n;++i)w[i]=read();
	for(i=1;i<n;++i)u=read(),v=read(),g[u].push_back(v),g[v].push_back(u);
	dfs1(1,0);
	dfs(1,0,0);
	printf("%lld",ans);
	return 0;
}

```

---

## 作者：wcyQwQ (赞：0)

首先考虑不加边，就是换根 dp 板子。然后我们考虑加边会给答案造成多少贡献，设当前根为 $r$，我们从 $r$ 两棵不同的子树中选出两个点连边，那么我们观察到每个点的贡献可以摊到他祖先上每个点都进行计算，记环上的点集为 $C$。则答案为 $\sum_{i \in C, i \neq r} sz_i$。所以其实就是对于每一个点 $u$，选两条从上往下的链，使得上面那个东西最小，记最小值和次小值即可。容易换根 dp 转移，时间复杂度 $O(n)$。

[Code](https://loj.ac/s/1858754)



---

## 作者：hhhyyyfff (赞：0)

注：原来一篇 Markdown 炸了

### 题意

给出一棵带权树 $(1 \le n \le 10^6)$，添加一条边（不能是重边/自环），求基环树中 $\sum value_i \times depth_i$ 的最大值。

### 算法（$O(n)$）

考虑与加的这条边相连的两个点，分为祖孙关系和在两棵子树内。
- 祖孙关系：

```
  1   <-
 / \
2   3 <-
```

- 非祖孙关系：

```
     1
    / \
-> 2   3 <-
```

设结点 $i$ 为祖先结点时，**祖孙关系**在子树 $i$ 中答案为 $g_i$，则 $g_i=g_{son}+$（其他子树+（整棵树-子树 $i$））到该节点的 `权值` 乘 `距离`（即基环树中的深度）。边界情况为：

```
1
|
2
|
3
```

即长度为 $3$ 的链，枚举子节点的子节点即可。

设结点 $i$ 为**非祖孙关系**中，将基环树的环在原树上的点看作“人”形的“两支”，其中“一支”距离 `LCA` 最近的结点为 $i$，则在子树 $i$ 中的 `权值` 乘 `距离` 为 $f_i$，则 $f_i$ 与 $g_i$ 递推关系相同。边界情况为 $f_i=$ 子树 $i$ 中的 `权值` 乘 `距离`。

然后我们需要预处理一些数组来求 $f,g$（变量缩写，括号内为原词）：
- $s_i$ 表示子树 $i$ 的 权值 和（$sum$），$s_i=v_i+\sum s_{son}$
- $sd_i$ 表示子树 $i$ 的 权值乘距离 和（$sum-distance$），$sd_i=\sum sd_{son}+s_{son}$
- $s1_i$ 表示（整棵树-子树 $i$）的 权值 和（$sum'$），$s1_i=s1_{father}+s_{father}-s_i$
- $sd1_i$ 表示（整棵树-子树 $i$）的 权值乘距离 和（$sum-distance'$），$sd_i=sd_{father}+sd_{father}-(sd_i+s_i)+s1_i$

则

$f_i=\max\{sd_i,f_{son}+sd_i-(sd_{son}+s_{son})\}$

$g_i=\max\{sd_i-(sd_{son}+s_{son})+sd_{son}-(sd_{son_{son}}+s_{son_{son}}+sd_{son_{son}}) =sd_i-s_{son}-s_{son_{son}},g_{son}+sd_i-{sd_{son}+s_{son}}\}$

最后的答案 $ans=\max\{g_i+sd1_i,f_{son1}+f_{son2}+sd_i-(sd_{son1}+s_{son1})-(sd_{son2}+s_{son2})\}$，枚举关于 $f$ 答案时可将 $f_{son}-(sd_{son}+s_{son})$ 视作整体求最大值与次大值。

整个算法中，公式推导难度不大，就是比较多，要仔细。注意初值取 $-\infty$。

求这些数组时，涉及枚举子节点/子节点的子节点，$O(\sum son)=O(n)$。

### 代码

``` cpp
// 细节很多，要注意
#include <cstdio>
#include <algorithm>

using namespace std;
#define N 1000000

struct edge {
  int a, b;
  bool operator< (const edge& edge) const { return a < edge.a; }
};
edge a[2 * N + 10];
int n, head[N + 10], e[2 * N + 10];
int s[N + 10], s1[N + 10];
long long ans, sd[N + 10], sd1[N + 10], f[N + 10], g[N + 10];

void dfs1(int x, int fa) {
  for (int i = head[x]; i < head[x + 1]; ++i)
    if (e[i] != fa) {
      dfs1(e[i], x);
      s[x] += s[e[i]];
      sd[x] += sd[e[i]] + s[e[i]];
    }
  f[x] = sd[x];
  for (int i = head[x]; i < head[x + 1]; ++i)
    if (e[i] != fa) {
      f[x] = max(f[x], f[e[i]] + sd[x] - (sd[e[i]] + s[e[i]]));
      g[x] = max(g[x], g[e[i]] + sd[x] - (sd[e[i]] + s[e[i]]));
      for (int j = head[e[i]]; j < head[e[i] + 1]; ++j)
        if (e[j] != x)
          g[x] = max(g[x], sd[e[j]] + sd[e[i]] - (sd[e[j]] + s[e[j]]) +
              sd[x] - (sd[e[i]] + s[e[i]]));
    }
}

void dfs2(int x, int fa) {
  if (x > 1) {
    s1[x] = s1[fa] + s[fa] - s[x];
    sd1[x] = sd1[fa] + sd[fa] - (sd[x] + s[x]) + s1[x];
  }
  long long m1 = -1e17, m2 = -1e17;
  for (int i = head[x]; i < head[x + 1]; ++i) 
    if (e[i] != fa) {
      dfs2(e[i], x);
      long long tmp = f[e[i]] - (sd[e[i]] + s[e[i]]);
      if (tmp > m1) {
        m2 = m1;
        m1 = tmp;
      } else if (tmp > m2) m2 = tmp;
    }
  ans = max(ans, max(m1 + m2 + sd[x] + sd1[x], g[x] + sd1[x]));
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &s[i]);
    g[i] = -1e17;
  }
  for (int i = 1; i < n; ++i) {
    scanf("%d%d", &a[i].a, &a[i].b);
    a[n + i] = {a[i].b, a[i].a};
  }
  sort(a + 1, a + n + n);
  head[1] = 1;
  for (int i = 1, j = 0; i < n + n; ++i) {
    while (a[i].a != j) {
      head[j + 2] = head[j + 1];
      ++j;
    }
    ++head[j + 1];
    e[i] = a[i].b;
  }
  head[n + 1] = n + n;
  dfs1(1, 0);
  ans = -1e17;
  dfs2(1, 0);
  printf("%lld\n", ans);
  return 0;
}
```

---

