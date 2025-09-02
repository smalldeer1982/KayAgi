# Zoning Restrictions

## 题目描述

你计划在一条街道上建造住宅。街道上有 $n$ 个可用位置，这些位置从左到右编号为 $1$ 到 $n$。在每个位置，你可以建造一个高度为 $0$ 到 $h$ 的整数高度的房屋。

在每个位置，如果房屋高度为 $a$，你可以获得 $a^2$ 美元的收益。

然而，城市有 $m$ 条规划限制。第 $i$ 条限制规定，如果从第 $l_i$ 到第 $r_i$ 号位置中的最高房屋高度严格大于 $x_i$，你必须支付 $c_i$ 美元的罚款。

你希望通过建造房屋使利润最大化（总收益减去罚款）。请你计算可以获得的最大利润。

## 说明/提示

在第一个样例中，最优方案是建造高度为 $[1, 3, 2]$ 的房屋。你可以获得 $1^2+3^2+2^2=14$ 的收益。没有违反任何限制，因此没有罚款，总利润为 $14-0=14$。

在第二个样例中，最优方案是建造高度为 $[10, 8, 8, 10]$ 的房屋。你可以获得 $10^2+8^2+8^2+10^2=328$ 的收益，但你违反了第二条限制，需要支付 $39$ 的罚款，因此总利润为 $328-39=289$。注意，即使第 $1$ 号位置没有限制，你仍然必须将其高度限制在不超过 $10$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3 3 3
1 1 1 1000
2 2 3 1000
3 3 2 1000
```

### 输出

```
14
```

## 样例 #2

### 输入

```
4 10 2
2 3 8 76
3 4 7 39
```

### 输出

```
289
```

# 题解

## 作者：w4p3r (赞：12)

## 前言:
~~**如果你不想跟我一样从rank+100变成rank-100,写网络流的时候一定要把cnt（边数）设成1**~~

这次CF我就做了A,B,G（B题还调了1个小时左右），你能想象我G题被叉的感受吗（也不知道我cnt没设成1是怎么present accepted的）

## 思路:
一个不算太难的最小割模型，如果你做过**CTSC2009移民站选址**或者**HNOI2013切糕**的话。

这三道题有一个共同点，那就是它们

**都把每个点所有决策(边)排成一条链,再处理点与点之间的联系**

（我画不来图，如果你想看图的话可以去看**CTSC2009移民站选址**那篇题解我julao同学的图）

对于这道题来说，每个点我们共有$h+1$个决策（**即该点修0-h任意高度的建筑**）

但是每个决策带来的是**收益**，不是**代价**，总不可能建负的边吧

没事，我们**假设每个点建的高度都为h**,如果我们实际建的高度为$k$,那么代价即为$h*h-k*k$

那罚款也不难解决,就像类似与**文理分科**，**土地划分**一样，

新建一个点，

**这个点向汇点连c(罚款)**,

然后**l-r所有点中的第x+1个点向新建点连inf**

## 实现

设一个二元组$(x,y)$为第$x$点的第$y$个决策点

则$s->(x,1)$连$inf$(无实际意义)

$(x,i)->(x,i+1)$连$h^2-(i-1)^2$（表示第$x$个点建筑高度为$i-1$）

($1<=i<=h+1$)

$(x,h+2)->t$连$inf$（无实际意义）


然后，

对于系数为$l,r,x,c$的罚款

假设新建点为$V$

$V->t$连$c$

$(i,x+1)->V$连$inf$($l<=i<=r$)

(如果你做过文理分科那这部分应该不需要我解释)

（~~如果你没做过那就快去做吧~~）

## 代码:
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#include<vector>
#include<stack>
#include<map>
#include<deque>
#define inf 0x7fffffff/2
#define eps 1e-6
#define N 1000010
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
inline ll read()
{
	char ch=getchar();
	int s=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){s=s*10+ch-'0';ch=getchar();}
	return s*w;
}
struct edge
{
	int next,to,fl;
}e[N<<1];
int head[N],cnt=1;//我的200rank分就因为这个cnt没了555
int depth[N];queue<int>Q;
int ans,dcnt;
int n,h,m;
int s,t;
inline void add_edge(int from,int to,int fl){e[++cnt].to=to;e[cnt].next=head[from];e[cnt].fl=fl;head[from]=cnt;}
inline int bfs()
{
	memset(depth,0,sizeof(depth));while(!Q.empty())Q.pop();
	Q.push(s);depth[s]=1;
	while(!Q.empty())
	{
		int x=Q.front();Q.pop();
		for(register int i=head[x];i;i=e[i].next){if(e[i].fl&&!depth[e[i].to])depth[e[i].to]=depth[x]+1,Q.push(e[i].to);}
	}
	return depth[t];
}
int dfs(int now,int flow)
{
	if(now==t)return flow;
	int ret=0;
	for(register int i=head[now];i;i=e[i].next)
	{
		if(ret==flow)return ret;
		if(depth[e[i].to]==depth[now]+1&&e[i].fl)
		{
			int fl=dfs(e[i].to,min(e[i].fl,flow-ret));
			if(fl)
			{
				ret+=fl;
				e[i].fl-=fl;
				e[i^1].fl+=fl;
			}
		}
	}
	if(!ret)depth[now]=0;
	return ret;
}
inline int Dinic()
{
	int sum=0;
	while(bfs())
	{
		while(int x=dfs(s,inf))sum+=x;
	}
	return sum;
}//最大流
inline int idx(int x,int y){return (x-1)*(h+2)+y;}//求点的编号而已
int main()
{
	n=read(),h=read(),m=read();t=N-10;
	for(register int i=1;i<=n;i++)ans+=h*h;//假设所有点都建高度为h的建筑
	for(register int i=1;i<=n;i++)
	{
		for(register int j=1;j<=h+1;j++)add_edge(idx(i,j),idx(i,j+1),h*h-(j-1)*(j-1)),add_edge(idx(i,j+1),idx(i,j),0);
	}//这里前面解释过了，就是h+1个决策
	dcnt=n*(h+2);//当前点数
	for(register int i=1;i<=n;i++)
	{
		add_edge(s,idx(i,1),inf);add_edge(idx(i,1),s,0);
		add_edge(idx(i,h+2),t,inf);add_edge(t,idx(i,h+2),0);
	}//应该不用解释
	for(register int i=1;i<=m;i++)
	{
		int l=read(),r=read(),H=read(),val=read();
		if(H==h)continue;
		++dcnt;//V
		add_edge(dcnt,t,val);add_edge(t,dcnt,0);
		for(register int j=l;j<=r;j++)
		{
			add_edge(idx(j,H+2),dcnt,inf);add_edge(dcnt,idx(j,H+2),0);
		}
	}
	printf("%d\n",ans-Dinic());//输出ans
	return 0;
}
```
**如果认为我这篇题解对你有帮助的可以给我点一下赞qwq。如果有任何疑问，或者认为我的题解有什么问题的话，请务必私信我，感激不尽！我会努力把我的题解写得最好的!**



---

## 作者：GaryH (赞：8)

## CF1146G 题解

给一个 `DP` 的做法。

**题意**：

对长 $n$ 的序列 $a$，记 $f(a)=(\sum\limits_{i=1}^na_i^2)+(\sum\limits_{i=1}^mc_i[\max\limits_{j=l_i}^{r_i}a_j>x_i])$，求 $\max\limits_{\forall i\in[1,n],a_i\in[0,h]}f(a)$。

**做法**：

显然需要区间 `DP`，设 $f(l,r)$ 代表区间 $[l,r]$ 内的最大收益。

考虑如何处理对区间高度 $\max$ 的限制，我们可以枚举区间内最大值，来将问题划分成一些子问题。

例如，如果我们想计算 $f(l,r)$ 的值，我们可以枚举二元组 $(p,z)$，代表 $\max\limits_{i=l}^ra_i=a_p=z$，

那么对所有满足 $l\le l_i\le p\le r_i\le r,x_i<z$ 的分区限制 $i$，$c_i$ 的罚款是必须要付的，

而对于其他的分区限制是否需要缴纳罚款，还是暂时不能确定的，但我们可以发现，

此时对于区间 $[l,p-1]$ 和 $[p+1,r]$，这两段区间是两个子问题，唯一的限制是最大值 $a_p=z$ 带来的，

即要求 $\max\limits_{i=l}^{p-1}a_i$ 和 $\max\limits_{i=p+1}^ra_i$ 都不超过 $z$，那么我们可以在 `DP` 状态中记录 $z$ 这一维，来处理这个限制。

即，记 $f(l,r,z)$ 代表区间 $[l,r]$ 内，满足 $\max\limits_{i=l}^ra_i\le z$ 的最大收益。

此时，区间 $[l,p-1]$ 和 $[p+1,r]$ 内的最大收益，就可用 $\max\limits_{x\le z}f(l,p-1,x)$ 和 $\max\limits_{x\le z}f(p+1,r,x)$ 表示，

我们维护 `DP` 数组的前缀最大值，即可做到 $O(n^4)$ 转移。

**code**：

```
#include<bits/stdc++.h>
#define ckmax(a, b) ((a) = max((a), (b)))
#define rep(i, a, b) for (int i = (a); i <= (b); i++)
using namespace std;
int read() {/*快读*/}
const int N (55);
int n, m, h, f[N][N][N], lim[N][N][N][N];
struct Node { int l, r, x, c; } q[N];
int dp (int l, int r, int x, int res = -2e9) {
	if (x < 0 || l > r) return 0;
	if (f[l][r][x] != -1) return f[l][r][x];
	rep (p, l, r) ckmax (res, dp (l, p - 1, x) + dp (p + 1, r, x) + x * x + lim[l][r][p][x]);
	return f[l][r][x] = max (res, dp (l, r, x - 1));
}
int main() {
	n = read(), h = read(), m = read();
	rep (i, 1, m) {
		int l = read(), r = read(), x = read(), c = read();
		q[i].l = l, q[i].r = r, q[i].x = x, q[i].c = c;
	}
	rep (l, 1, n) rep (r, l, n) rep (p, l, r) rep (i, 1, m) {
		int L = q[i].l, R = q[i].r, X = q[i].x, C = q[i].c;
		if (l <= L && L <= p && p <= R && R <= r) lim[l][r][p][X + 1] -= C;
	}
	rep (l, 1, n) rep (r, l, n) rep (p, l, r) rep (x, 1, h) lim[l][r][p][x] += lim[l][r][p][x - 1];
	memset (f, -1, sizeof(f)), cout << dp (1, n, h); return 0;
}
```



---

## 作者：Reunite (赞：4)

## 零

其他的题解已经把具体做法写的比较清楚了，此题解主要以图片的方式帮助读者更好的理解建图。

## 一

看到 $n,m,h$ 的数据范围，不难想到**网络流**算法。对于一个点只能从若干方案（高度）中选择一种，也不难想到最小割。直接说建图。

先不考虑约束。

对于每个位置上的点，我们把它拆成 $h$ 个点，记为 $H_{pos,i}$。$H_{pos,i}$ 与 $H_{pos,i+1}$ 的边权为 $i^2$。将 $s$ 与 $H_{pos,1}$ 相连，边权为 $0$。将 $H_{pos,h}$ 与 $t$ 相连，边权为 $h^2$。这样我们不难发现，每一种割边的方案都会割掉 $n$ 条边，且恰好每个点选择了一种高度的值。

约束很套路，对于四元组 $(l,r,x,c)$，先新建一个点 $tt$，$tt$ 与 $t$ 相连，边权为 $-c$；对于 $pos\in[l,r]$，将 $H_{pos,x+1}$ 与 $tt$ 相连，边权为 $+\infty$。总的图如下（举例）：
![图1，使用 Graph Editor 制作](https://cdn.luogu.com.cn/upload/image_hosting/30iq3smk.png)

上述约束的巧妙在于，要想割掉 $-10$ 那条边，因为 $\inf$ 的边不可能割掉，所以必须在 $pos=1,2$ 中选择至少一个大于 $1$ 的边割掉，也就是满足了约束条件。

**值得注意的是，我们求的是最大割，容量不能为负，考虑先取反，再减。注意割掉的高度边边数为 $n$。**

## Code:

```cpp
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define ll long long
using namespace std;

int n,m,H,s,t;
int cnt=1;
int dep[100005];
int h[100005];
int cur[100005];
queue <int> q;
struct Edge{int v,nxt;ll cup;}edge[1000005];

inline void in(int &n){
	n=0;
	char c=getchar();
	while(c<'0' || c>'9') c=getchar();
	while(c>='0'&&c<='9') n=n*10+c-'0',c=getchar();
	return ;
} 

inline void addedge(int u,int v,ll c){
	edge[++cnt]=(Edge){v,h[u],c};h[u]=cnt;
	edge[++cnt]=(Edge){u,h[v],0};h[v]=cnt;
	return ;
}

inline bool bfs(){
	while(!q.empty()) q.pop();
	memset(dep,0,sizeof(dep));
	dep[s]=1;
	q.push(s);
	int u,v;
	while(!q.empty()){
		u=q.front();
		q.pop();
		for(int i=h[u];i;i=edge[i].nxt){
			v=edge[i].v;
			if(edge[i].cup&&!dep[v])
				dep[v]=dep[u]+1,q.push(v);
		}
	}
	return (dep[t]>0);
}

ll dfs(int u,ll flow){
	if(flow==0||u==t) return flow;
	ll ret=0;
	int v;
	for(int i=cur[u];i;i=edge[i].nxt){
		cur[u]=i;
		v=edge[i].v;
		if(dep[v]==dep[u]+1&&edge[i].cup){
			int dd=dfs(v,min(flow,edge[i].cup));
			flow-=dd;ret+=dd;
			edge[i].cup-=dd;
			edge[i^1].cup+=dd;
		}
	}
	return ret;
}

inline ll Dinic(){
	ll ans=0;
	while(bfs()){
		for(int i=1;i<=t;i++) cur[i]=h[i];
		ans+=dfs(s,1e15);
	}
	return ans;
}

int main(){
	in(n),in(H),in(m);
	int tt=n*H;
	s=n*H+m+1;t=s+1;
	for(int i=1;i<=n;i++){
		addedge(s,i*H-H+1,114514-0);
		addedge(i*H,t,114514-H*H);
		for(int j=1;j<=H-1;j++) addedge(i*H-H+j,i*H-H+j+1,114514-j*j);
	}
	int l,r,x,c;
	while(m--){
		in(l),in(r),in(x),in(c);
		tt++;
		addedge(tt,t,c);
		if(x==H) continue;
		for(int i=l;i<=r;i++)
			addedge(i*H-H+x+1,tt,1e14);
	}
	printf("%lld\n",114514*n-Dinic());

	return 0;
}
```


---

## 作者：ifffer_2137 (赞：2)

~~从小到大做过最顺的网络流~~。
### 题意
$n$ 座房子高度值域为 $[0,h]$，一座高度为 $x$ 的房子价值为 $x^2$。有 $m$ 条限制，形如 $[l_i,r_i]$ 中如果 $\max\ge k_i$ 则扣除 $c_i$ 的价值。问总价值最大值。
### 分析
数据范围与题意结合理解，明示网络流。

容易想到的是 $O(nh)$ 的点数表示所有房子的所有选择，数量可以接受。然后一座房子最终只有一种选择，比较经典，考虑最小割，把每座房子的点全部串起来再和源点汇点相连，相当于最开始钦定选 $h$，然后每个点上挂条边，边权表示实际选这个高度需要减去的价值。

然后考虑刻画每一条限制，注意我们已经转了最小割，所以相当于 $[l_i,r_i]$ 之间的房子存在割掉的边表示的所选高度大于 $k_i$ 的那么需要再割掉一条权值为 $c_i$ 的边。你仔细抿一下，相当于所有的都割了小于等于 $k_i$ 的就不用割，那把区间内所有表示 $k_i$ 的点选出来连向一个虚点，再从虚点向汇点连一条边权为 $c_i$ 的就好了。

剩下直接跑 Dinic。无敌好写。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
inline int read(){
    char ch=getchar();int x=0,w=1;
    while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
namespace MF{
	const int maxn=2.5e3+5;
	int tot;
	struct edge{int to,nxt,val;}e[maxn<<2];
	int head[maxn<<1],cnt;
	void init(){
		memset(head,-1,sizeof(head));
		cnt=-1;
	} 
	void add(int u,int v,int w){
		e[++cnt].nxt=head[u],head[u]=cnt,e[cnt].to=v,e[cnt].val=w;
		e[++cnt].nxt=head[v],head[v]=cnt,e[cnt].to=u,e[cnt].val=0;
	}
	int dis[maxn<<1],cur[maxn<<1];
	queue<int> q;
	bool bfs(){
		while(!q.empty()) q.pop();
		for(int i=1;i<=tot;i++) dis[i]=inf;
		dis[1]=0,q.push(1),cur[1]=head[1];
		while(!q.empty()){
			int u=q.front();q.pop();
			for(int i=head[u];~i;i=e[i].nxt){
				int v=e[i].to,w=e[i].val;
				if(dis[v]==inf&&w>0){
					dis[v]=dis[u]+1;
					q.push(v);
					cur[v]=head[v];
				}
			}
		}
		return dis[tot]!=inf;
	}
	int dfs(int u,int s){
		if(u==tot) return s;
		int res=0;
		for(int i=cur[u];~i&&s;i=e[i].nxt){
			cur[u]=i;
			int v=e[i].to,w=e[i].val;
			if(w<=0||dis[v]!=dis[u]+1) continue;
			int k=dfs(v,min(w,s));
			s-=k,e[i].val-=k;
			res+=k,e[i^1].val+=k;
		}
		return res;
	}
	int Dinic(){
		int ans=0;
		while(bfs()) ans+=dfs(1,inf);
		return ans;
	}
}
using namespace MF;
//------------------
const int maxm=55;
int n,m,h;
int vot[maxm],c[maxm];
int id[maxm][maxm];
signed main(){
	cin.tie(0),cout.tie(0);
	init();++tot;
	n=read(),h=read(),m=read();
	for(int i=1;i<=n;i++){
		id[i][0]=++tot; add(1,tot,h*h);
		for(int j=1;j<=h;j++){
			id[i][j]=++tot;
			add(id[i][j-1],tot,h*h-j*j);
		}
	}
	for(int i=1;i<=m;i++){
		int l=read(),r=read(),x=read();
		c[i]=read();int u=++tot;
		for(int j=l;j<=r;j++) add(id[j][x],u,inf);
		vot[i]=u;
	}
	++tot;
	for(int i=1;i<=n;i++) add(id[i][h],tot,inf);
	for(int i=1;i<=m;i++) add(vot[i],tot,c[i]);
	cout<<h*h*n-Dinic()<<'\n';
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：2)

Trick：遇到最高，考虑区间 dp 刻画笛卡尔树。

考虑 $dp_{l,r,k}$ 表示 $[l,r]$ 区间所有位置小于等于 $k$ 的情况下，收益最大是多少。由于不被 $[l,r]$ 包含的限制房子高度还有可能大于 $k$，故在后续再考虑。

考虑转移，考虑两种情况：

* 合并两个区间，并加入一个高度为 $k$ 的房子：$dp_{l,r,k}\leftarrow dp_{l,q-1,k}+dp_{q+1,r,k}+k^2-\sum_{i=1}^m[l_i\leq q\leq r_i]\times[x_i<k]\times c_i$。
* 将高度限制加一：$dp_{l,r,k}\leftarrow{dp_{l,r,k-1}}$。

边界情况是容易的，在此不再阐述。

总复杂度 $O(n^3mh)$，可以通过。

```cpp
#include <bits/stdc++.h>
#define int long long
#define lowbit(i) (i&(-i))
#define add(i,j) ((i+j>=mod)?i+j-mod:i+j)
using namespace std;
int dp[55][55][55],l[55],r[55],x[55],c[55];
signed main(){
	int n,h,m; cin>>n>>h>>m;
	for(int i=1;i<=m;i++) cin>>l[i]>>r[i]>>x[i]>>c[i];
	for(int i=1;i<=n;i++){
		for(int j=1;j<=h;j++){
			int del=0;
			for(int k=1;k<=m;k++){
				if(l[k]==i&&r[k]==i&&j>x[k]) del+=c[k];
			}
			dp[i][i][j]=max(dp[i][i][j-1],j*j-del);
		}
	}
	for(int len=2;len<=n;len++){
		for(int lp=1,rp=len;rp<=n;lp++,rp++){
			for(int j=1;j<=h;j++){
				dp[lp][rp][j]=dp[lp][rp][j-1];
				for(int k=lp;k<=rp;k++){
					//[l,k-1],[k+1,r]
					int del=0;
					for(int p=1;p<=m;p++){
						if(lp<=l[p]&&r[p]<=rp){
							if(r[p]>=k&&l[p]<=k){
								if(j>x[p]){
									del+=c[p];
								}
							}
						}
					}
					dp[lp][rp][j]=max(dp[lp][rp][j],dp[lp][k-1][j]+dp[k+1][rp][j]+j*j-del);
				}
			}
		}
	}
	cout<<dp[1][n][h];
	return 0;
}
```

---

## 作者：Purslane (赞：1)

# Solution

网络流做法是显然的，只需要建立出最小割模型即可，不做赘述。

学习了 zxx 大神的 $\rm DP$ 做法。设 $dp_{i,j,k}$ 表示区间 $i$ 到 $j$ 的楼房如果有 $k$ 的限高，能获得的最大价值。可以考虑先预收取罚款，如果满足要求再返还。

对于这种**区间最大值**的限制，可以考虑枚举区间最大值的位置。

1. 增加高度，$dp_{i,j,k} \leftarrow dp_{i,j,k-1}$。
2. 枚举第一个最大值的位置，即  $dp_{i,j,k} \leftarrow dp_{i,t-1,k-1} + dp_{t+1,j,k} + f(i,t,j,k)$。

其中，$f(i,t,j,k)$ 表示所有左端点在 $[i,t]$ 中，右端点在 $[t,j]$ 中，限制值 $\le k$ 的限制权值之和，可以暴力计算。

复杂度 $O(n^2hm)$（其实那一段可以不暴力计算，直接前缀和即可，但是懒。）

```cpp
#include<bits/stdc++.h>
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=50+5;
int n,m,h,L[MAXN],R[MAXN],X[MAXN],C[MAXN],dp[MAXN][MAXN][MAXN],tot; 
int f(int i,int t,int j,int k) {
	int ans=0;
	ffor(z,1,m) if(i<=L[z]&&L[z]<=t&&t<=R[z]&&R[z]<=j&&X[z]>=k) ans+=C[z];
	return ans;	
}
int main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>h>>m;
	ffor(i,1,m) cin>>L[i]>>R[i]>>X[i]>>C[i],tot+=C[i];
	ffor(len,1,n) for(int l=1,r=len;r<=n;l++,r++) ffor(k,0,h) {
		if(k) dp[l][r][k]=dp[l][r][k-1];
		ffor(t,l,r) dp[l][r][k]=max(dp[l][r][k],dp[l][t-1][k]+dp[t+1][r][k]+k*k+f(l,t,r,k));
	}
	cout<<dp[1][n][h]-tot;
	return 0;
}
```

---

## 作者：dd_d (赞：1)

[更好的阅读体验](https://www.cnblogs.com/dd-d/p/16130079.html)
### Sol  
题解区好像都是网络流的题解，这里给一篇区间 dp 的题解。  
思路 by e3c8f1a924  
发现数据范围很小，考虑区间 dp。  
容易发现，一个限制只与该区间内最高的房屋有关。  
那么记 $dp(l,r,k)$ 表示 区间 $\left[l,r\right]$ 中最高房屋为 $k$ 时的最大收益。  
转移的话对于每个区间找出所有完全被这个区间包含的限制。然后暴力枚举最高的房屋进行转移。在用前缀 max 优化即可。  
具体实现看代码。  
时间复杂度 $O(n^3h)$  
### Code  
```cpp
//LYC_music yyds!
#include<bits/stdc++.h>
#define IOS ios::sync_with_stdio(0)
#define lowbit(x) (x&(-x))
using namespace std;
inline char gc()
{
	static char buf[1000000],*p1=buf,*p2=buf;
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++;
}
int read()
{
	int pos=1,num=0;
	char ch=getchar();
	while (!isdigit(ch))
	{
		if (ch=='-') pos=-1;
		ch=getchar();
	}
	while (isdigit(ch))
	{
		num=num*10+(int)(ch-'0');
		ch=getchar();
	}
	return pos*num;
}
void write(int x)
{
	if (x<0)
	{
		putchar('-');
		write(-x);
		return;
	}
	if (x>=10) write(x/10);
	putchar(x%10+'0');
}
void writesp(int x)
{
	write(x);
	putchar(' ');
}
void writeln(int x)
{
	write(x);
	putchar('\n');
}
const int N=60;
int n,h,m,L[N],R[N],x[N],c[N],id[N],dp[N][N][N];
signed main()
{
	n=read(); h=read(); m=read();
	for (int i=1;i<=m;i++)
		L[i]=read(),R[i]=read(),x[i]=read(),c[i]=read(),id[i]=i;
	sort(id+1,id+m+1,[](int a,int b)
	{
		return x[a]>x[b];
	});
	for (int i=1;i<=n;i++)
	{
		vector<int> G;
		for (int j=1;j<=m;j++)
			if (L[id[j]]==i&&R[id[j]]==i) G.emplace_back(id[j]);
		int tot=0,cnt=(int)G.size()-1;
		for (int j=0;j<=h;j++)
		{
			while (cnt>=0&&j>x[G[cnt]]) tot+=c[G[cnt]],cnt--;
			dp[i][i][j]=j*j-tot;
			if (j>0) dp[i][i][j]=max(dp[i][i][j],dp[i][i][j-1]); 
		}
	}
	for (int len=2;len<=n;len++)
		for (int l=1;l<=n-len+1;l++)
		{
			int r=l+len-1;
			for (int k=l;k<=r;k++)
			{
				vector<int> G;
				for (int j=1;j<=m;j++)
					if (L[id[j]]>=l&&r>=R[id[j]]&&L[id[j]]<=k&&R[id[j]]>=k) G.emplace_back(id[j]);
				int tot=0,cnt=(int)G.size()-1;
				for (int i=0;i<=h;i++)
				{
					while (cnt>=0&&i>x[G[cnt]]) tot+=c[G[cnt]],cnt--;
					dp[l][r][i]=max(dp[l][r][i],dp[l][k-1][i]+dp[k+1][r][i]+i*i-tot);
				}
			}
			for (int i=1;i<=h;i++)
				dp[l][r][i]=max(dp[l][r][i],dp[l][r][i-1]);
		}
	writeln(dp[1][n][h]);
}

 


```

---

## 作者：KING_OF_TURTLE (赞：1)

从 CF1430G 学来的思路，几乎一致。

首先发现 $h \le 50$ ，暗示了我们可以根据高度连边。

每个点我们把它拆成 $(h+1)$ 个点，编号 $0 \to h$ ，相邻点连边，第 $i$ 条边连接 $i$ 和 $i+1$ 容量为 $i^2$ 。这样我们选择高度为 $i$ 就是割掉哪条边。最后把 $0$ 号点和 $S$ 连边，$h$ 号点与 $T$ 连边（然而我因为没考虑高度为 $0$ WA了无数发，wtcl）。

接下来再考虑代价。只需要一种连边方式表示“选 $x$ 以上的高度就需要 $c$ 的代价”。~~根据CF1430G的套路~~ 只需要新建一个节点，向 $T$ 连边，容量为 $-c$ ，再从 $l \to r$ 的每个点中的第 $x+1$ 号向这个新点连边，容量 $ +\infty $ 。表示你不选这个 $c$ 就割不掉“高度”为 $x$ 以上的边。

然后建图就建完了，但是发现题目要求的是最大，所以把所有边的容量取反就是最大割了。出现负数容量了?加上一个值转化为正数最后再减掉就可以。别忘了再取反回来。

$code$:
```
#include<bits/stdc++.h> 
using namespace std;
const int N=10005;
const int inf=0x3f3f3f3f;
int s,t,n,m,h;
struct edge{
	int v,nxt,w;
}e[N*205];
int head[N],cnt=1,u[N],v[N],d[N],hd[N];
void adde(int u,int v,int w)
{e[++cnt].v=v;e[cnt].w=w;e[cnt].nxt=head[u];head[u]=cnt;}
void add(int u,int v,int w){adde(u,v,w);adde(v,u,0);}
bool bfs()
{
	memset(d,0,sizeof(d));
	queue<int> q;q.push(s);d[s]=1;
	for(int i=1;i<=t;++i)hd[i]=head[i];                                                                                         
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=head[u];i;i=e[i].nxt)
		{
			int v=e[i].v;if(!e[i].w||d[v])continue;
			d[v]=d[u]+1;q.push(v);if(v==t)return 1;
		}
	}
	return d[t];
}
int sum,col[N];
int dfs(int u,int fl)
{
	if(u==t)return fl;int res=0;
	for(int i=hd[u];i;i=e[i].nxt)
	{
		hd[u]=i;int v=e[i].v;
		if(!e[i].w||d[v]!=d[u]+1)continue;
		int tmp=dfs(v,min(fl-res,e[i].w));
		if(!tmp)continue;
		e[i].w-=tmp;e[i^1].w+=tmp;
		res+=tmp;if(fl-res<=0)return fl;
	}
	if(!res)d[u]=0;return res;
}
int main()
{
	scanf("%d%d%d",&n,&h,&m);s=n*(h+2)+m+1;t=n*(h+2)+m+2;
	for(int i=1;i<=n;++i)add(s,i,inf),add(i+n*(h+1),t,inf);
	for(int i=1;i<=n;++i)for(int j=0/*8次提交才发现这里错了……*/;j<=h;++j)
	add(i+j*n,i+(j+1)*n,114514-j*j);
	for(int i=1,l,r,x,c;i<=m;++i)
	{
		scanf("%d%d%d%d",&l,&r,&x,&c);
		for(int j=l;j<=r;++j)
		add(j+(x+1)*n,n*(h+2)+i,inf);
		add(n*(h+2)+i,t,c);
	}
	int ans=0;while(bfs())ans+=dfs(s,inf);
	printf("%d",n*114514-ans);
	return 0;
}

---

## 作者：roger_yrj (赞：0)

对于每个区间，我们只关注最大值，所以我们考虑从大到小填数。

当我们填了一个数时，由于是从大到小填，所以可以立刻处理所有跨过这个点的区间。那么此时就能将问题分裂为两个子问题。

举个例子：当我们处理 $[l,r]$ 中的问题时，当我们在位置 $x$ 填了一个数 $y$，那么就能分裂为两个子问题：$[l,x-1]$ 中填 $[0,y]$，$[x+1,r]$ 中填 $[0,y]$。

记忆化搜索即可，时间复杂度 $O(n^3h(h+m))$。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define mp make_pair
#define A first
#define B second
using namespace std;
const int N=55;
int n,q,a[N],b[N],H;
ll f[N][N][N];
vector<pii>cnt[N][N][N];
ll dfs(int l,int r,int x){
	if(l>r)return 0;
	if(~f[l][r][x])return f[l][r][x];
	f[l][r][x]=0;
	for(int i=l;i<=r;i++){
		array<int,55>vis;
		for(int j=0;j<=x;j++)vis[j]=0;
		for(pii j:cnt[i][l][r])vis[j.A+1]+=j.B;
		for(int j=1;j<=x;j++)vis[j]+=vis[j-1];
		for(int j=0;j<=x;j++)f[l][r][x]=max(f[l][r][x],dfs(l,i-1,j)+dfs(i+1,r,j)+j*j-vis[j]);
	}
	return f[l][r][x];
}
int main(){
	memset(f,-1,sizeof(f));
	cin>>n>>H>>q;
	for(int i=1,l,r,x,c;i<=q;i++){
		scanf("%d%d%d%d",&l,&r,&x,&c);
		for(int j=l;j<=r;j++){
			for(int L=1;L<=l;L++){
				for(int R=r;R<=n;R++){
					cnt[j][L][R].push_back(mp(x,c));
				}
			}
		}
	}
	cout<<dfs(1,n,H);
}
```

---

