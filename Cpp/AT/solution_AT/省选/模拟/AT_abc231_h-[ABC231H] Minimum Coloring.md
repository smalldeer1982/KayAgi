# [ABC231H] Minimum Coloring

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc231/tasks/abc231_h

$ H $ 行 $ W $ 列のグリッドがあります。上から $ i $ 行目、左から $ j $ 列目のマスをマス $ (i,j) $ と表します。

グリッド上には $ 1 $ から $ N $ の番号がついた $ N $ 個の白い駒が置かれています。駒 $ i $ が置かれているマスは $ (A_i,B_i) $ です。

あなたはコストを $ C_i $ 払うことで、駒 $ i $ を黒い駒に変えることができます。

どの行どの列にも黒い駒が $ 1 $ 個以上ある状態にするために必要なコストの和の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ H,W\ \leq\ 10^3 $
- $ 1\ \leq\ N\ \leq\ 10^3 $
- $ 1\ \leq\ A_i\ \leq\ H $
- $ 1\ \leq\ B_i\ \leq\ W $
- $ 1\ \leq\ C_i\ \leq\ 10^9 $
- $ (A_i,B_i) $ は相異なる
- 全ての行、全ての列に $ 1 $ 個以上の白い駒が置かれている
- 入力に含まれる値は全て整数である

### Sample Explanation 1

コスト $ 1110 $ を払い駒 $ 2,3,4 $ を黒い駒に変えることで、どの行どの列にも黒い駒がある状態にすることができます。

## 样例 #1

### 输入

```
2 3 6
1 1 1
1 2 10
1 3 100
2 1 1000
2 2 10000
2 3 100000```

### 输出

```
1110```

## 样例 #2

### 输入

```
1 7 7
1 2 200000000
1 7 700000000
1 4 400000000
1 3 300000000
1 6 600000000
1 5 500000000
1 1 100000000```

### 输出

```
2800000000```

## 样例 #3

### 输入

```
3 3 8
3 2 1
3 1 2
2 3 1
2 2 100
2 1 100
1 3 2
1 2 100
1 1 100```

### 输出

```
6```

# 题解

## 作者：Btls (赞：11)

大家都用的是网络流的做法，本人才疏学浅，想不到这种方法，于是写一个线性规划做法。

#### 前置知识

你要会[单纯形算法](https://oi-wiki.org/math/simplex/)。

#### 做法

考虑每行每列都至少有一个黑色节点，相当于如果设 $x_i$ 表示第 $i$ 个点黑色为 $1$，白色为 $0$，则相当于：
$$
\min \sum_{i=1}^n c_i x_i\\
\forall 1 \leq i \leq H,\sum_{a_j=i}x_j \geq 1\\
\forall 1 \leq i \leq W,\sum_{b_j=i}x_j \geq 1
$$
使用线性规划对偶原理，转换为标准型：
$$
\max \sum_{i=1}^{H}y_i+\sum_{i=1}^{W}z_i\\
\forall 1 \leq i \leq n,y_{a_i}+z_{b_i} \leq c_i
$$
实际上对 $c_i,y_i,z_i$ 同时取相反数也可以达到转换为标准型的效果，但是用对偶的方法能使得有基本解（零解），不需要写 `init()` 函数。

直接套模板即可。

#### 代码：

```cpp
#include<bits/stdc++.h>
#define rg int
#define ll long long
#define ci const int
#define ld double 
using namespace std;
ci N=60005;
const ld eps=1e-12;
const ll inf=1e12;
ll n,m;
ld a[2001][2001];
inline ll read(){ll u,f=1;char o;while((o=getchar())<48||o>57)if(o==45)f=-1;u=(o^48);while((o=getchar())>=48&&o<=57)u=(u<<1)+(u<<3)+(o^48);return u*f;}
void write(ll x){if(x<0)putchar(45),x=-x;if(x>9)write(x/10);putchar(x%10+48);}
mt19937 rd(time(0));
void Pivot(ci l,ci e){
	const ld u=a[l][e];a[l][e]=1;
	for(rg i=0;i<=n;++i)a[l][i]/=u;
	for(rg i=0;i<=m;++i)if(i!=l&&fabs(a[i][e])>eps){
		const ld u=a[i][e];a[i][e]=0;
		for(rg j=0;j<=n;++j)a[i][j]-=a[l][j]*u;
	}
}
ld Simplex()
{
	while(1){
		int e=0,l=0;
		for(rg i=1;i<=n;++i)if(a[0][i]>eps){
			e=i;
			break;
		}
		if(!e)return a[0][0];
		ld minn=inf;
		for(rg i=1;i<=m;++i)if(a[i][e]>eps&&minn>a[i][0]/a[i][e])minn=a[i][0]/a[i][e],l=i;
		Pivot(l,e);
	}
}
int main()
{
	int id=0,T=1;
	while(T--)
	{
		ll nn=read();ll mm=read();m=read();
		n=nn+mm;
		for(rg i=1;i<=n;++i)a[0][i]=1;
		for(rg i=1;i<=m;++i)
		{
			ll x=read(),y=read(),z=read();
			a[i][x]=1;
			a[i][nn+y]=1;
			a[i][0]=z;
		}
		write(-Simplex()+0.5),putchar('\n');
	}
	return 0;
}
```

---

## 作者：Tx_Lcy (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc231_h)

## 思路

我们把每行每列都抠出来，连出下面这张图：

![](https://cdn.luogu.com.cn/upload/image_hosting/fez5fdln.png)

假设我们当前有 $4$ 行，$4$ 列，行的编号分别为 $h1,h2,h3,h4$，列的编号分别为 $w1,w2,w3,w4$，每行有 $m$ 个节点，每列有 $n$ 个节点，此时每条边的费用都是 $0$，容量如上图所示。

$s$ 表示超级源点，$p$ 表示中转点，$t$ 表示超级汇点。

随着一些另外边的加入，$h$ 和 $w$ 之间也会连边，这些边的容量为 $1$，费用为 $c_i$。

然后直接跑最小费用最大流即可。

思考这样为什么是对的。

由于题目保证有解，再加上最小费用最大流本身就是在保证最大流的基础上的，所以从 $s$ 到 $h1,h2,h3,h4$ 这些边一定会流满，因为每个 $h$ 都会至少与一个 $w$ 连边，所以一定会流出去，从 $w$ 到 $t$ 的边同理，一定会有流量流入。

所以我们发现，连出来的方案满足了题目的限制条件。

直接模拟即可。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mid ((l+r)>>1)
#define sqr(x) ((x)*(x))
#define all(x) (x).begin(),(x).end()
#define Tim ((double)clock()/CLOCKS_PER_SEC)
#define lowbit(x) (x&-x)
int const N=1e4+10;
int flw[N],cst[N],pre1[N],pre2[N];
int dis[N],fow[N],vis[N];
int s,t,p,cnt=1;
vector< pair<int,int> >a[N];
inline void add(int u,int v,int rl,int w){
	a[u].push_back({v,++cnt});flw[cnt]=rl;cst[cnt]=w;
	a[v].push_back({u,++cnt});flw[cnt]=0;cst[cnt]=-w;
}
inline bool SPFA(){
	memset(dis,0x3f,sizeof(dis));
	memset(fow,0x3f,sizeof(fow));
	memset(vis,0,sizeof(vis));
	int Max=dis[0];queue<int>q;
	q.push(s);vis[s]=1;dis[s]=0;
	while (!q.empty()){
		int x=q.front();q.pop();
		vis[x]=0;
		for (auto [v,id]:a[x]){
			if (!flw[id]) continue;
			if (dis[v]<=dis[x]+cst[id]) continue;
			dis[v]=dis[x]+cst[id];
			fow[v]=min(fow[x],flw[id]);
			pre1[v]=x;pre2[v]=id;
			if (!vis[v]) q.push(v);
		}
	}
	if (dis[t]==Max) return 0;
	return 1;
}
inline int EK(){
	int Ans=0;
	while (SPFA()){
		int now=t;Ans+=fow[t]*dis[t];
		while (now){
			flw[pre2[now]]-=fow[t];
			flw[pre2[now]^1]+=fow[t];
			now=pre1[now];
		}
	}
	return Ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n,m,k;cin>>n>>m>>k;
	s=0;t=n+m+1;p=n+m+2;
	for (int i=1;i<=n;++i) add(s,i,m,0),add(i,p,m-1,0);
	for (int i=1;i<=m;++i) add(p,i+n,n-1,0),add(i+n,t,n,0);
	while (k--){
		int u,v,w;cin>>u>>v>>w;
		add(u,v+n,1,w);
	}
	cout<<EK()<<'\n';
	return 0;
}
```

---

## 作者：ZnPdCo (赞：4)

可以用单纯形方法解决。

首先，我们设 $x_i=0/1$ 表示第 $i$ 个涂不涂。然后为了保证每一行都有，前 $h$ 个约束为这一行所有的 $x$ 加起来大于等于 $1$，为了保证每一列都有，后 $w$ 个约束为这一列所有的 $x$ 加起来大于等于 $1$。目标就是要求 $\sum x_ic_i$ 尽可能小。

这题没有卡单纯形，对偶一下就可以了。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define N 2010
double eps = 1e-8, inf = 1e15;
ll h, w, n, m;
double a[N][N];
void pivot(ll l, ll e) {
	double t = a[l][e];
	a[l][e] = 1;
	for(ll i = 0; i <= m; i ++) {
		a[l][e] /= t;
	}
	for(ll i = 0; i <= n; i ++) if(i != l && abs(a[l][e]) > eps) {
		t = a[i][e], a[i][e] = 0;
		for(ll j = 0; j <= m; j ++) {
			a[i][j] -= t * a[l][j];
		}
	}
}
void simplex() {
	while(1) {
		ll l = 0, e = 0;
		double mn = inf;
		for(ll i = 1; i <= m; i ++) if(a[0][i] > eps) {
			e = i;
			break;
		}
		if(!e) break;
		for(ll i = 1; i <= n; i ++) if(a[i][e] > eps && a[i][0] / a[i][e] < mn) {
			l = i;
			mn = a[i][0] / a[i][e];
		}
		pivot(l, e);
	}
}
int main() {
	scanf("%lld %lld %lld", &h, &w, &n);
	m = h + w;
	for(ll i = 1; i <= n; i ++) {
		ll x, y, c;
		scanf("%lld %lld %lld", &x, &y, &c);
		a[i][0] = c;
		a[i][x] = 1;
		a[i][h + y] = 1;
	}
	for(ll i = 1; i <= m; i ++) {
		a[0][i] = 1;
	}
	simplex();
	printf("%.lf", -a[0][0]);
}
```

---

## 作者：Purslane (赞：0)

# Solution

最小费用上下界可行流！

先建立最基础的网络流模型：建立二分图。左部点表示行，右部点表示列。在 $X_{a_i}$ 和 $Y_{b_i}$ 连上 $c_i$ 的边。

建立超级源点 $s$，和左部点所有点连上下界为 $1$ 的边。同理建立超级汇点。

求这张网络的最小费用可行流即可。复杂度理论上是 $O(n^3)$（认为 $h$、$w$、$n$ 同阶），但是网络长的太规律了所以跑得很快，很快！

```cpp
#include<bits/stdc++.h>
#define int long long
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXV=2000+10,MAXE=MAXV*100;
int h,w,e,s,t,mc,mf,tmp,tot=1,ev,deg[MAXV],hd[MAXV],cur[MAXV],dis[MAXV],vis[MAXV];
struct Edge {int to,nxt,f,c;}edge[MAXE];
void add_edge(int u,int v,int f,int c) {return edge[++tot]={v,hd[u],f,c},hd[u]=tot,edge[++tot]={u,hd[v],0,-c},hd[v]=tot,void();}
int spfa(int s,int t) {
	ffor(i,0,t) dis[i]=0x3f3f3f3f3f3f3f3f,vis[i]=0,cur[i]=hd[i];
	queue<int> q;
	dis[s]=0,q.push(s);
	while(!q.empty()) {
		int u=q.front();
		vis[u]=0,q.pop();
		for(int i=hd[u];i;i=edge[i].nxt) {
			int to=edge[i].to,f=edge[i].f,c=edge[i].c;
			if(!f||dis[to]<=dis[u]+c) continue ;
			dis[to]=dis[u]+c;
			if(!vis[to]) vis[to]=1,q.push(to);
		}
	}
	return dis[t]!=0x3f3f3f3f3f3f3f3f;
}
int dinic(int u,int mx) {
	if(u==t) return mx;
	int res=0;
	vis[u]=1;
	for(int i=cur[u];i;i=edge[i].nxt) {
		int to=edge[i].to,f=edge[i].f,c=edge[i].c; cur[u]=i;
		if(dis[to]!=dis[u]+c||vis[to]||!f) continue ;
		int tmp=dinic(to,min(mx,f));
		if(tmp) {
			res+=tmp,mx-=tmp,mc+=c*tmp,edge[i].f-=tmp,edge[i^1].f+=tmp;
			if(!mx) break;
		}
		else dis[to]=0x3f3f3f3f3f3f3f3f;
	}
	return vis[u]=0,res;
}
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>h>>w>>e,s=h+w+2,t=h+w+3;
	add_edge(h+w+1,0,10000,0);
	ffor(i,1,h) deg[0]++,deg[i]--,add_edge(0,i,10000,0);
	ffor(i,h+1,h+w) deg[i]++,deg[h+w+1]--,add_edge(i,h+w+1,10000,0);
	ffor(i,1,e) {
		int x,y,c;
		cin>>x>>y>>c;	
		add_edge(x,y+h,1,c);
	}
	ffor(i,0,h+w+1) if(deg[i]>0) add_edge(i,t,deg[i],0);
	else add_edge(s,i,-deg[i],0);
	while(spfa(s,t)) while(dinic(s,10000));
	cout<<mc;
	return 0;
}
```

---

## 作者：XZhuRen (赞：0)

本题类似 [P3153 [CQOI2009] 跳舞](https://www.luogu.com.cn/problem/P3153) 都要进行拆匹配成两种。

更详细解释一下第三篇题解的图是怎么建的。

先假设理想情况：**一对一**，考虑费用流模型，二分图匹配。

建两排点，一行，一列。

易知这个图是满流的，流量不定，考虑图强制满流为 $f=H\times W$，则多建了每行每列一一对应的边，这些边的 $cost$ 为 $0$。

现在考虑用满流构造限制：

全图满流易知为 $H\times W$。

设本图 $S,T$ 对每个行列节点的流为 $c$ ，这个是满流的。限制是必须用**至少一个有效匹配**。而用**不存在的匹配**流出去的就是最多 $c-1$ 个。

所以现在构造模型：

$S$ 向行点连边，$c=W,cost=0$，列点向 $T$ 连边，$c=H,cost=0$。用满流限制住，则相当于每两个行列之间都有一条 $c=H,cost$ 的边。

由于必须选一个真的匹配，所以这里的流量限制就是 $H$ 点：$W-1$，$W$ 点：$H-1$，$cost$ 都是 $0$。

真的匹配直接连两个点，$c=1$，$cost$ 就是真实代价。

总连上一个中继点就好，不需要真的建 $10^{6}$ 条加限制。

最后图长得是一样的。

![](https://cdn.luogu.com.cn/upload/image_hosting/ey1ivei5.png)

虽然套路但是不好想，题解区里那是真大神。


```cpp
#include<bits/stdc++.h>
using namespace std;
template<typename T>
void in(T &n){
    n=0;char c=getchar();bool flag=0;
    for(;c<'0'||c>'9';c=getchar()) if (c=='-') flag=1;
    for(;c>='0'&&c<='9';c=getchar()) (n*=10)+=(c^48);
    if (flag) n=-n;
}
int wlsk[45];int wltp;
template<typename T>
void out(T n,char c=0){
    if (n==0){putchar('0');if (c)putchar(c);return ;}
    if (n<0) putchar('-'),n=-n;
    while(n) wlsk[++wltp]=(n%10),n/=10;
    while(wltp) putchar(wlsk[wltp--]^48);
    if (c) putchar(c);
}
typedef long long ll1;
const ll1 inf=1e14+9;
const int N=3e4+3;
const int M=5e5+5;

struct edge{//费用流模型
	int u,v,nxt;
	ll1 c,w;
}g[N*2];
int head[N],tote=1;
void ae(int u,int v,ll1 c,ll1 w=0){
	g[++tote]=(edge){u,v,head[u],c,w};
	head[u]=tote;
}
void Ae(int u,int v,ll1 c,ll1 w=0){
	ae(u,v,c,w);
	ae(v,u,0,-w);
}
int S,T;
int totn=0;
namespace flows{
	// ll1 dis[N];
	int thead[N];
	int que[N],hd=0,tl=0;
	ll1 dis[N];
	bool in[N];
	bool vis[N];
	bool bfs(){
		int u;
		for(u=1;u<=totn;u++)dis[u]=inf,thead[u]=head[u],in[u]=0,vis[u]=0;
		dis[S]=0;
		que[hd=tl=1]=S;
		while(hd<=tl){
			u=que[hd++];
			in[u]=0;
			for(int v,e=head[u];e;e=g[e].nxt){
				v=g[e].v;
				if(!g[e].c)continue;
				if(dis[u]+g[e].w>=dis[v])continue;
				dis[v]=g[e].w+dis[u];
				if(!in[v]){
					que[++tl]=v;
					in[v]=1;
				}
			}
		}
		return dis[T]!=inf;
	}
	ll1 cost;
	ll1 dfs(int u,ll1 F){
		vis[u]=1;
		if(!F||u==T)return F;
		ll1 rf=0,tmp=0;
		for(int e=thead[u],v;F&&e;e=g[e].nxt){
			thead[u]=e;
			v=g[e].v;
			if(!g[e].c||dis[v]!=dis[u]+g[e].w||vis[v])continue;
			tmp=dfs(v,min(F,g[e].c));
			cost+=tmp*g[e].w;
			g[e].c-=tmp,g[e^1].c+=tmp;
			F-=tmp,rf+=tmp;
		}
		vis[u]=0;
		return rf;
	}
	ll1 flow(){//最小费用最大流
		cost=0;
		ll1 res=0;
		while(bfs()){
			res+=dfs(S,inf);
		}
		return res;
	}
}
#define A(x) (x)
#define B(x) (x+H)
int H,W;
int n;
int mld;
void init(){
	in(H),in(W);
	totn=H+W;
	mld=++totn,S=++totn;
	T=++totn;
	for(int i=1;i<=H;i++){
		Ae(S,A(i),W,0);
		Ae(A(i),mld,W-1,0);
	}
	for(int i=1;i<=W;i++){
		Ae(mld,B(i),H-1,0);
		Ae(B(i),T,H,0);
	}
	in(n);
	int u,v,w;
	for(int i=1;i<=n;i++){
		in(u),in(v),in(w);
		Ae(A(u),B(v),1,w);
	}
}
void work(){
	flows::flow();
	out(flows::cost,'\n');
}
int main(){
	init();
	work();
	return 0;
}
```

---

## 作者：Filberte (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc231_h)

## 思路

看到**每行每列**至少有一个黑色节点，对应到这类问题的一个经典套路：二分图。

原问题可以转化为以下形式：

给定一个二分图 $G = (X,Y,E)$，每条边有正边权 $c_i$。选择 $E$ 的一个子集 $E'$ ，使得 $\forall u \in V$，$u$ 存在邻边 $e \in E'$，最小化 $\sum\limits_{e\in E} c(e)$。

考虑分两步来选择一些边构成边覆盖集。

1. 选择 $E$ 的任意子集 $E_1$。
2. 对于所有邻边都不在 $E_1$ 中的顶点 $u$，选择与 $u$ 相邻的所有边中权值最小的一条加入 $E_0$ 中。令  $E_2 = E_1 \bigcup E_0$。那么 $E_2$ 是原图 $G$ 的一个边覆盖集。

因为 $E_1$ 可以任意选择，所以通过这个方法一定可以构造出答案。经过观察，$E_1$ 中不可能包含两条共顶点的边，否则删除其中一条一定不会更劣。具体的，如果删去的这条边两个顶点都已经被覆盖，则答案更优；如果被删去的边另一顶点被覆盖，那么最差的情况就是在 $E_2$ 中把这条边加回来，也有可能加入边权更小的边，不会更劣。

同时，在 $E_1$ 确定后，$E_2$ 就确定了。所以最终答案只跟我们选的 $E_1$ 集合有关。

设 $V_1$ 是 $E_1$ 中边覆盖的点集， $C_u$ 表示 $u$ 的所有邻边中的最小代价，$c'(e) = c(e_u,e_v) - C_{e_u} - C_{e_v}$。有：
$$
\begin{aligned}
\sum\limits_{e\in E_2} c(e) 
&= \sum\limits_{e\in E_1} c(E) + \sum\limits_{u \in V \setminus V_1} C_u\\
&= \sum\limits_{u \in V} C_u + \sum\limits_{e\in E_1} c(E) - \sum\limits_{u \in V_1} C_u\\
&= \sum\limits_{u \in V} C_u + \sum\limits_{e\in E_1} c'(e)\\
\end{aligned}
$$


由于 $\sum\limits_{u\in V} C_u$ 的值是固定的，所以只需要最小化 $\sum\limits_{e\in E_1} c'(e)$。考虑以 $c'(e)$ 为边权构造二分图 $G_2$，问题转化为求带（负）权二分图上的**最小带权匹配**。注意此不要求最大匹配（你甚至可以不选），因此 $\forall e\in E_1$，$c'(e) < 0$。

构造一个费用流模型：

从源点 $S$ 向二分图每个左部点 $X_i$ 连一条容量为 $1$，代价为 $0$ 的边；从二分图每个右部点 $Y_i$ 向汇点 $T$ 连一条容量为 $1$，费用为 $0$ 的边。若 $X_i,Y_j$ 两点间有一条边 $e$，满足 $c'(e) < 0$，则由 $X_i$ 向 $Y_j$ 之间连一条容量为 $1$，代价为 $k + c'(e)$ 的边，其中 $k$ 是一个足够大的常数。

因为 $G_2$ 的最大匹配数不会超过 $x = \min(H,W)$，所以再从 $S$ 向 $T$ 连一条容量为 $x$，代价为 $k$ 的边。假如在原二分图中只匹配了 $m(m < x)$ 组点，那么这条额外边就会有 $x - m$ 的流量，这就很巧妙地找到了所有可能的匹配中权值最小的那一种情况，且保证了在网络中最少也能有 $x$ 的流量。

限定流量为 $x$，在原网络上跑最小费用流，设 $c$ 表示最小费用，则答案为 $\sum\limits_{u\in V} C_u + c - kx$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int N = 2050, M = 12500;
const int k = 1e9, s = 0, t = N - 1;
const int inf = 2147483645;
struct Edge{
    int v, w, c, nxt;
}e[M];
int h[N], idx = 1;
void add(int u, int v, int w, int c){
    e[++idx] = {v, w, c, h[u]};h[u] = idx;
    e[++idx] = {u, 0, -c, h[v]};h[v] = idx;
}
int mf[N], dis[N];
bool inq[N];
int eid[M];
int flow;
bool spfa(){
    memset(mf, 0, sizeof(mf));
    memset(dis, 0x3f, sizeof(dis));
    mf[s] = flow, dis[s] = 0, inq[s] = 0;
    queue<int> q;q.push(s);
    while(!q.empty()){
        int u = q.front();q.pop();
        inq[u] = 0;
        for(int i = h[u];i;i = e[i].nxt){
            int v = e[i].v, w = e[i].w, c = e[i].c;
            if(dis[u] + c < dis[v] && w){
                dis[v] = dis[u] + c;
                eid[v] = i;
                mf[v] = min(mf[u], w);
                if(!inq[v]){
                    q.push(v);
                    inq[v] = 1; 
                }
            }
        }
    }
    return mf[t] > 0;
}
ll cost;
void EK(){
    while(spfa()){
        int u = t;
        while(u != s){
            int i = eid[u];
            e[i].w -= mf[t];
            e[i ^ 1].w += mf[t];
            u = e[i ^ 1].v;
        }
        flow -= mf[t];
        cost += 1ll * mf[t] * dis[t];
    }
}
int L[N], R[N], u[N], v[N], wt[N];
int main(){
    ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    int nods, n, m, Mn;
    cin >> n >> m >> nods;
    Mn = min(n, m);
    for(int i = 1;i <= n;i++) L[i] = inf;
    for(int i = 1;i <= m;i++) R[i] = inf;
    for(int i = 1;i <= nods;i++){
        int x, y, z;
        cin >> x >> y >> z;
        L[x] = min(L[x], z);
        R[y] = min(R[y], z);
        u[i] = x, v[i] = y, wt[i] = z;
    }
    for(int i = 1;i <= nods;i++){
        add(u[i], v[i] + n, 1, wt[i] - (L[u[i]] + R[v[i]]) + k);
    }
    ll sum = 0;
    for(int i = 1;i <= n;i++){
        add(s, i, 1, 0);
        sum += L[i];
    }
    for(int i = 1;i <= m;i++){
        add(i + n, t, 1, 0);
        sum += R[i];
    }
    add(s, t, Mn, k);
    flow = Mn;
    EK();
    cout << sum + cost - 1ll * k * Mn << endl;
    return 0;
}
```

---

