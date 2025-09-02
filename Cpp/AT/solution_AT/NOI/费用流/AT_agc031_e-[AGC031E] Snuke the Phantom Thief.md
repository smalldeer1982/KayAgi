# [AGC031E] Snuke the Phantom Thief

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc031/tasks/agc031_e

とある博物館には宝石 $ 1,\ 2,\ ...,\ N $ が展示されています。 宝石 $ i $ の置いてある場所は $ (x_i,\ y_i) $ で、価値は $ v_i $ です (この博物館は二次元平面として解釈できます)。

怪盗すぬけはいくつか宝石を盗みます。

宝石の盗み方には条件 $ 1,\ 2,\ ...,\ M $ があり、すべて満たさないと探偵に捕まってしまいます。 条件はそれぞれ以下の4種類のいずれかです。

- ($ t_i $ =`L`, $ a_i $, $ b_i $) : 盗んだ宝石のうち、$ x $ 座標が $ a_i $ 以下の宝石が $ b_i $ 個以下
- ($ t_i $ =`R`, $ a_i $, $ b_i $) : 盗んだ宝石のうち、$ x $ 座標が $ a_i $ 以上の宝石が $ b_i $ 個以下
- ($ t_i $ =`D`, $ a_i $, $ b_i $) : 盗んだ宝石のうち、$ y $ 座標が $ a_i $ 以下の宝石が $ b_i $ 個以下
- ($ t_i $ =`U`, $ a_i $, $ b_i $) : 盗んだ宝石のうち、$ y $ 座標が $ a_i $ 以上の宝石が $ b_i $ 個以下

怪盗すぬけが盗める宝石の価値の総和の最大値を求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 80 $
- $ 1\ \leq\ x_i,\ y_i\ \leq\ 100 $
- $ 1\ \leq\ v_i\ \leq\ 10^{15} $
- $ 1\ \leq\ M\ \leq\ 320 $
- $ t_i $ は `L`, `R`, `U`, `D` のいずれか
- $ 1\ \leq\ a_i\ \leq\ 100 $
- $ 0\ \leq\ b_i\ \leq\ N\ -\ 1 $
- $ (x_i,\ y_i) $ は互いに相違なる
- $ (t_i,\ a_i) $ は互いに相違なる
- $ (t_i,\ b_i) $ は互いに相違なる

### Sample Explanation 1

!\[図\](https://img.atcoder.jp/agc031/rghe0iwfjoievjw4epdfmengow.png) 宝石 $ 1,\ 5,\ 6,\ 7 $ を盗むと価値の総和が $ 36 $ となります。

## 样例 #1

### 输入

```
7
1 3 6
1 5 9
3 1 8
4 3 8
6 2 9
5 4 11
5 7 10
4
L 3 1
R 2 3
D 5 3
U 4 2```

### 输出

```
36```

## 样例 #2

### 输入

```
3
1 2 3
4 5 6
7 8 9
1
L 100 0```

### 输出

```
0```

## 样例 #3

### 输入

```
4
1 1 10
1 2 11
2 1 12
2 2 13
3
L 8 3
L 9 2
L 10 1```

### 输出

```
13```

## 样例 #4

### 输入

```
10
66 47 71040136000
65 77 74799603000
80 53 91192869000
24 34 24931901000
91 78 49867703000
68 71 46108236000
46 73 74799603000
56 63 93122668000
32 51 71030136000
51 26 70912345000
21
L 51 1
L 7 0
U 47 4
R 92 0
R 91 1
D 53 2
R 65 3
D 13 0
U 63 3
L 68 3
D 47 1
L 91 5
R 32 4
L 66 2
L 80 4
D 77 4
U 73 1
D 78 5
U 26 5
R 80 2
R 24 5```

### 输出

```
305223377000```

# 题解

## 作者：dottle (赞：24)

限制很复杂，数据范围不像指数级别，看起来不像能贪心。这三点加起来会想到尝试使用流来解决。

尝试对原问题直接建模。然而，在原问题上建出的模型应该都是这种形式的：求出每个方向上最严的限制，然后每个点向四个方向的限制分别连边。这样并不是网络流可以解决的模型。这是因为，在网络流的模型中，我们不能给一条流量非单位流量的边加上“要么不流，要么流满”的限制。换言之，我们不能保证每一个选中的点在四个方向上的限制都被满足。一旦发现自己的模型存在上述限制，那么一定是找错了方向。此时最好的选择是尝试再寻找一下题目性质，再次转化题目；否则就会在错误的方向上浪费很多时间。

那么考虑原题应该怎么进一步转化。观察原题的限制（以 `L` 为例）：在 $a_i$ 左侧选中点的个数不大于 $b_i$。此限制可以倒过来，即从左往右数，第 $b_i$ 个选中点在 $a_i$ 右侧。这样，我们可以求出第 $b_i$ 个点横坐标的下界。考虑四个限制一起，我们就可以求出从左往右数第 $b_i$ 个选中点的横坐标限制、从右往左的、从上往下的、从下往上的，这样四种限制。

四种限制还是有些麻烦，但是这些限制有两个是关于横坐标的，另两个是关于纵坐标的。考虑枚举我们总共选的点的个数，这样可以求出从左往右每个选中点的横坐标范围，从上往下每个选中点的纵坐标范围。根据这个可以进一步求出每个点能否成为从左往右数第 $i$ 个点，能否成为从上往下数第 $i$ 个点。

这样，问题转化为了一个经典的费用流模型。即为每个点分配两个坐标，两个坐标分别不能重复，要使被分配了坐标的点点权和最大。设坐标有 $k$ 个，点有 $n$ 个。则建模方法是：

-   从源点向 $k$ 个横坐标连边，流量为 $1$，边权为 $0$。
-    $k$ 个纵坐标向汇点连边，流量为 $1$，边权为 $0$。
-   中间的点拆成左右两部分，左侧点向右侧点连边，流量为 $1$，边权为该点点权。
-   若某个点可以取到某个横坐标，从该横坐标向其左侧点连边，流量为 $1$，边权为 $0$。
-   若某个点可以取到某个纵坐标，从该纵坐标向其右侧点连边，流量为 $1$，边权为 $0$。

这样，原点到汇点的一条流的含义是为中间流过的点分配了左右流过的坐标，费用为中间那个点的点权。

代码使用高贵的 AtCoder Library 写成。

```cpp
#include<bits/stdc++.h>
#include<atcoder/all>
#define int long long
const int N=1000005,inf=2e15;
using namespace atcoder;
using namespace std;

array<int,N> a,b,c,d,x,y,w,A,B,C,D;// A 从左往右，B 从右往左，C 从上往下，D 从下往上
int n,m;

int calc(int k){
	mcf_graph<int,int> e(2*k+2*n+2);
	int s=0,t=2*k+2*n+1;
	for(int i=1;i<=k;i++)
    	e.add_edge(s,i,1,0),
		e.add_edge(i+2*n+k,t,1,0);
	for(int i=1;i<=n;i++){
		e.add_edge(i+k,i+k+n,1,-w[i]+inf);
		for(int j=1;j<=k;j++){
			if(x[i]>=A[j]&&x[i]<=B[k-j+1])
				e.add_edge(j,i+k,1,0);
			if(y[i]>=C[j]&&y[i]<=D[k-j+1])
				e.add_edge(i+k+n,j+k+n*2,1,0);
		}
	}
	auto x=e.flow(s,t);
	return -x.second+inf*x.first;
}

void solve(){
	cin>>n;
	for(int i=1;i<=n;i++)
		cin>>x[i]>>y[i]>>w[i];
	fill(B.begin(),B.end(),inf);
	fill(D.begin(),D.end(),inf);
	cin>>m;
	for(int i=1;i<=m;i++){
		char t;int x,y;cin>>t>>x>>y;++y;
		if(t=='L')A[y]=max(A[y],x+1); 
		if(t=='R')B[y]=min(B[y],x-1); 
		if(t=='D')C[y]=max(C[y],x+1); 
		if(t=='U')D[y]=min(D[y],x-1);
	}
	for(int i=1;i<=n;i++)
		A[i]=max(A[i],A[i-1]),B[i]=min(B[i],B[i-1]),
		C[i]=max(C[i],C[i-1]),D[i]=min(D[i],D[i-1]);
	int ans=0;
	for(int i=1;i<=n;i++)
		ans=max(ans,calc(i));
	cout<<ans<<endl;
}

main(){
	solve();
}
```



---

## 作者：justin_cao (赞：16)

这种奇怪的数据范围可以想到费用流。

先假设只有一维的情况。

考虑枚举偷的珠宝的个数$k$，且假设它们按照坐标大小排好了序。

那么可以将条件转化一下，大于等于$a_i$的最多取$b_i$个可以转化为取的前$k-b_i$个珠宝的坐标要小于$a_i$。同理，小于等于$a_i$的最多可以取$b_i$个可以转化为取的后$k-b_i$个珠宝的坐标要大于$a_i$。

那么这样的话，就可以计算出取的每个珠宝的取值范围$[l,r]$。

如果是两维的话就类似可得。

那么就可以建出费用流的图了。具体而言，从源点向左边的$k$个点连$(1,0)$的边，从左边的$k$个点往它们右边相邻的$n$个点按照算出来的取值范围连$(1,0)$的边，再从这$n$个点往右边的$n$个点一一对应连$(1,v_i)$的边，然后再从这$n$个点向右边的$k$个点按照算出来的取值范围连$(1,0)$的边，最后再从这$k$个点往汇点连$(1,0)$的边。

这样跑费用流即可。

code：
```cpp
#include<bits/stdc++.h>
#define maxn 505
#define inf 1000000007
using namespace std;
typedef long long ll;
ll read()
{
    ll x=0,f=1;
    char ch=getchar();
    while(ch-'0'<0||ch-'0'>9){if(ch=='-') f=-1;ch=getchar();}
    while(ch-'0'>=0&&ch-'0'<=9){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
int n,m,s,t;
struct P{
    int x,y;
    ll v;
}p[85];
struct X{
    char d;
    int a,b;
}co[325];
int Lx[85],Rx[85],Ly[85],Ry[85];
int head[325],nxt[140010],to[140010],c[140010],tot;
ll v[140010];
void add(int x,int y,int z,ll u)
{
    tot++;
    nxt[tot]=head[x];
    head[x]=tot;
    to[tot]=y;
    c[tot]=z;
    v[tot]=u;
}
void addx(int x,int y,int z,ll u)
{
    add(x,y,z,u);
    add(y,x,0,-u);
}
ll ans,res,dis[325];
int vis[325],pre[325],pre_num[325];
queue<int>q;
int spfa()
{
    for(int i=1;i<=t;i++)  dis[i]=-1e18;
    dis[s]=0;q.push(s);vis[s]=1;
    while(q.size())
    {
        int now=q.front();q.pop();vis[now]=0;
        for(int i=head[now];i;i=nxt[i])
        {
            if(dis[to[i]]<dis[now]+v[i]&&c[i])
            {
                dis[to[i]]=dis[now]+v[i];
                pre[to[i]]=now;
                pre_num[to[i]]=i;
                if(!vis[to[i]])  q.push(to[i]),vis[to[i]]=1;
            }
        }
    }
    if(dis[t]==-1e18)  return 0;
    int di=inf;
    for(int i=t;i!=s;i=pre[i])  di=min(di,c[pre_num[i]]);
    for(int i=t;i!=s;i=pre[i])  c[pre_num[i]]-=di,c[pre_num[i]^1]+=di;
    ans+=dis[t]*di;
    return di;
}
int main()
{
    n=read();
    for(int i=1;i<=n;i++)  p[i].x=read(),p[i].y=read(),p[i].v=read();
    m=read();
    for(int i=1;i<=m;i++)  co[i].d=getchar(),co[i].a=read(),co[i].b=read();
    for(int k=1;k<=n;k++)
    {
        tot=1;memset(head,0,sizeof(head));
        s=2*k+2*n+1;t=s+1;
        for(int i=1;i<=k;i++)  addx(s,i,1,0);
        for(int i=k+2*n+1;i<=2*n+2*k;i++)  addx(i,t,1,0);
        for(int i=k+1;i<=k+n;i++)  addx(i,i+n,1,p[i-k].v);
        for(int i=1;i<=k;i++)  Lx[i]=Ly[i]=0,Rx[i]=Ry[i]=inf;
        for(int i=1;i<=m;i++)
        {
            if(co[i].d=='U')
            {
                for(int j=1;j<=k-co[i].b;j++)  Ry[j]=min(Ry[j],co[i].a-1);
            }
            if(co[i].d=='D')
            {
                for(int j=co[i].b+1;j<=k;j++)  Ly[j]=max(Ly[j],co[i].a+1);
            }
            if(co[i].d=='L')
            {
                for(int j=co[i].b+1;j<=k;j++)  Lx[j]=max(Lx[j],co[i].a+1);
            }
            if(co[i].d=='R')
            {
                for(int j=1;j<=k-co[i].b;j++)  Rx[j]=min(Rx[j],co[i].a-1);
            }
        }
        for(int i=1;i<=k;i++)
          for(int j=1;j<=n;j++)
            if(Lx[i]<=p[j].x&&p[j].x<=Rx[i])  addx(i,k+j,1,0);
        for(int i=1;i<=k;i++)
          for(int j=1;j<=n;j++)
            if(Ly[i]<=p[j].y&&p[j].y<=Ry[i])  addx(k+n+j,k+2*n+i,1,0);
        ans=0;
        while(spfa()){};
        res=max(res,ans);   
    }
    cout<<res<<endl;
    return 0;
}
```

---

## 作者：agicy (赞：12)

本文将同步发布于：

- [洛谷博客](https://www.luogu.com.cn/blog/Lu-Anlai/solution-at4695)；
- [csdn](https://blog.csdn.net/Lu_Anlai/article/details/117451605)；
- [博客园](https://www.cnblogs.com/Lu-Anlai/p/14838752.html)；
- [简书](https://www.jianshu.com/p/cd0a16672db3)。

## 题目

题目链接：[洛谷 AT4695](https://www.luogu.com.cn/problem/AT4695)、[AtCoder agc031_e](https://atcoder.jp/contests/agc031/tasks/agc031_e)。

### 题意简述

在二维平面上，有 $n$ 颗珠宝，第 $i$ 颗珠宝在 $(x_i,y_i)$ 的位置，价值为 $v_i$。

现在有一个盗贼想要偷这些珠宝。

现在给出 $m$ 个限制约束偷的珠宝，约束有以下四种：

- 横坐标小于等于 $a_i$ 的珠宝最多偷 $b_i$ 颗。
- 横坐标大于等于 $a_i$ 的珠宝最多偷 $b_i$ 颗。
- 纵坐标小于等于 $a_i$ 的珠宝最多偷 $b_i$ 颗。
- 纵坐标大于等于 $a_i$ 的珠宝最多偷 $b_i$ 颗。

现在问你在满足这些约束的条件下，盗贼偷的珠宝的最大价值和是多少。

## 题解

### 约束与转化

这个约束有点难办，似乎并没有可能对其进行动态规划，因此我们考虑额外添加信息。

我们添加什么信息呢？考虑到限制是有关珠宝数量的，我们决定添加一个 **偷珠宝的总数** 的信息。

设偷珠宝 $k$ 颗，并且珠宝按照的横坐标排序被偷的顺序编号为 $1\sim k$，那么前两种限制条件转化如下：

- 横坐标小于等于 $a_i$ 的珠宝最多偷 $b_i$ 颗：  
若一个珠宝的编号 $\texttt{id}\in[b_i+1,k]$，那么一定有 $x_{\texttt{id}}>a_i$。
- 横坐标大于等于 $a_i$ 的珠宝最多偷 $b_i$ 颗：  
若一个珠宝的编号 $\texttt{id}\in[1,k-b_i]$，那么一定有 $x_{\texttt{id}}<a_i$。

同理，我们可以得出珠宝按照的纵坐标排序被偷的顺序编号为 $1\sim k$，那么后两种限制条件转化如下：

- 纵坐标小于等于 $a_i$ 的珠宝最多偷 $b_i$ 颗：  
若一个珠宝的编号 $\texttt{id}\in[b_i+1,k]$，那么一定有 $y_{\texttt{id}}>a_i$。
- 纵坐标大于等于 $a_i$ 的珠宝最多偷 $b_i$ 颗：  
若一个珠宝的编号 $\texttt{id}\in[1,k-b_i]$，那么一定有 $y_{\texttt{id}}<a_i$。

因此，我们得出，一个珠宝想要在按横坐标排序为第 $i$，纵坐标排序为第 $j$ 时被偷，需要满足的坐标范围。

### 化腐朽为神奇的网络流

考虑上面的条件也不是很好动态规划，我们需要想到一种化腐朽为神奇的算法——网络流。

由于这个题目有多个互不相关的限制：

- 珠宝不能同时被偷两次及以上；
- 偷的珠宝价值要最大化；

我们考虑运用费用流建立网络流模型。

因为我们要限制横坐标，所以必须要有 $k$ 个横坐标的限制，对应 $s\to p_{1\sim k}$，流量为 $1$，费用为 $0$。。

因为我们要限制纵坐标，所以必须要有 $k$ 个纵坐标的限制，对应 $q_{1\sim k}\to t$，流量为 $1$，费用为 $0$。

因为我们要限制一个点不能被选择多次，所以我们需要拆点限流，对应 $a_{1\sim n}\to b_{1\sim n}$，流量为 $1$，费用为 $v_i$。

考虑到我们上面需要满足的限制，按照限制加边 $p_i\to a_j$ 和 $b_j\to q_i$ 即可，流量为 $1$，费用为 $0$。

如果上面的语言有点抽象，我们不妨画图理解。

![graph.png](https://i.loli.net/2021/06/01/rysYW3S2LXlApqO.png)

整个建图如上所示，点数为 $\Theta(n^2)$，边数 $\Theta(n^2)$。

### 参考程序

```cpp
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=80+5;
const int MAXM=320+5;
const int inf=0x3f3f3f3f;

namespace Network{
	const int MAXV=4*MAXN;
	const int MAXE=(MAXN*MAXN*2+3*MAXN)*2;
	const ll inf=0x3f3f3f3f3f3f3f3f;
	int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
	ll p[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg int len,reg ll val){
		Next[++cnt]=head[u];
		to[cnt]=v,w[cnt]=len,p[cnt]=val;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int v,reg int len,reg ll val){
		Add_Edge(u,v,len,val);
		Add_Edge(v,u,0,-val);
		return;
	}
	bool inque[MAXV];
	int cur[MAXV];
	ll dis[MAXV];
	queue<int> Q;
	inline bool spfa(int s,reg int t){
		fill(dis+s,dis+t+1,inf);
		inque[s]=true,dis[s]=0,Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			inque[u]=false;
			cur[u]=head[u];
			for(reg int i=head[u];i;i=Next[i]){
				int v=to[i];
				if(dis[v]>dis[u]+p[i]&&w[i]){
					dis[v]=dis[u]+p[i];
					if(!inque[v]){
						inque[v]=true;
						Q.push(v);
					}
				}
			}
		}
		return dis[t]!=inf;
	}
	bool vis[MAXV];
	inline int dfs(reg int u,reg int t,reg ll lim){
		if(u==t)
			return lim;
		vis[u]=true;
		reg int flow=0;
		for(reg int &i=cur[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]==dis[u]+p[i]&&w[i]&&!vis[v]){
				reg int f=dfs(v,t,min(lim-flow,w[i]));
				if(f){
					flow+=f;
					w[i]-=f,w[i^1]+=f;
					if(flow==lim)
						break;
				}
			}
		}
		vis[u]=false;
		return flow;
	}
	inline pair<int,ll> dinic(reg int s,reg int t){
		int res=0;
		ll cost=0;
		while(spfa(s,t)){
			reg int flow=dfs(s,t,inf);
			res+=flow,cost+=flow*dis[t];
		}
		return make_pair(res,cost);
	}
	inline void init(reg int s,reg int t){
		cnt=1,fill(head+s,head+t+1,0);
		return;
	}
}

struct Point{
	int x,y;
	ll v;
};

struct Limits{
	char ch;
	int a,b;
};

struct Interval{
	int l,r;
	inline Interval(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
	inline bool in(reg int x)const{
		return l<=x&&x<=r;
	}
};

inline Interval cap(const Interval& a,const Interval& b){
	return Interval(max(a.l,b.l),min(a.r,b.r));
}

int n,m;
Point a[MAXN];
Limits b[MAXM];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].x=read(),a[i].y=read(),a[i].v=readll();
	m=read();
	for(reg int i=1;i<=m;++i){
		do
			b[i].ch=getchar();
		while(!isalpha(b[i].ch));
		b[i].a=read(),b[i].b=read();
	}
	reg ll ans=0;
	for(reg int k=1;k<=n;++k){
		static Interval invx[MAXN],invy[MAXN];
		fill(invx+1,invx+k+1,Interval(-inf,inf));
		fill(invy+1,invy+k+1,Interval(-inf,inf));
		for(reg int i=1;i<=m;++i){
			switch(b[i].ch){
				case 'L':{
					for(reg int j=b[i].b+1;j<=k;++j)
						invx[j]=cap(invx[j],Interval(b[i].a+1,inf));
					break;
				}
				case 'R':{
					for(reg int j=1;j<=k-b[i].b;++j)
						invx[j]=cap(invx[j],Interval(-inf,b[i].a-1));
					break;
				}
				case 'D':{
					for(reg int j=b[i].b+1;j<=k;++j)
						invy[j]=cap(invy[j],Interval(b[i].a+1,inf));
					break;
				}
				case 'U':{
					for(reg int j=1;j<=k-b[i].b;++j)
						invy[j]=cap(invy[j],Interval(-inf,b[i].a-1));
					break;
				}
			}
		}
		reg int s=0,t=2*k+2*n+1;
		Network::init(s,t);
		for(reg int i=1;i<=k;++i){
			Network::Add_Tube(s,i,1,0);
			Network::Add_Tube(k+n+n+i,t,1,0);
		}
		for(reg int i=1;i<=n;++i)
			Network::Add_Tube(k+i,k+n+i,1,-a[i].v);
		for(reg int i=1;i<=k;++i)
			for(reg int j=1;j<=n;++j){
				if(invx[i].in(a[j].x))
					Network::Add_Tube(i,k+j,1,0);
				if(invy[i].in(a[j].y))
					Network::Add_Tube(k+n+j,k+n+n+i,1,0);
			}
		pair<int,ll> res=Network::dinic(s,t);
		if(res.first==k)
			ans=max(ans,-res.second);
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：GreenDay (赞：8)

## AT4695 [AGC031E] Snuke the Phantom Thief 题解

[题面](https://www.luogu.com.cn/problem/AT4695) [代码](https://atcoder.jp/contests/agc031/submissions/12968364)

---

这么奇怪的限制和比较小的数据范围，不难想到网络流吧。

我们可以想到用流量来限制小贼的取舍，但这条路显然是不通的。

---

我们先考虑一维。把们排好序，我们转化一下限制：**枚举偷窃珠宝个数k**

- 横坐标小于等于 $a_i$的珠宝最多偷 $b_i$个 $\Leftrightarrow$ 如果$k>b_i$，那么珠宝编号$\ge b_i+1$，其横纵标$>a_i$

- 横坐标大于等于 $a_i$的珠宝最多偷 $b_i$个 $\Leftrightarrow$ 如果$k>b_i$， 那么珠宝编号$\le k-b_i$，其横纵标$<a_i$

我们可以的得到每一个珠宝的取值范围，那么偷珠宝相当于$k$个取值范围，和$n$个珠宝的价值做二分图最大权匹配。$EK$费用流即可。

两维情况，和一维情况差不多吧。

建出来的图大概长这样：(建图是网络流的灵魂)

![](https://cdn.luogu.com.cn/upload/image_hosting/d1zcd10r.png)

图例中表示$N=4,K=3$的情况。

$x,y$表示横纵坐标上的取值范围。

$(a,b)$表示流量$a$,费用$b$。$w_i$表示每个珠宝的价值。

其中$x->a$ $A->y$会根据坐标是否匹配连一些$(1,0)$的边（没画出来）。

最后跑从S到T的最大费用最大流就可以了，注意最大流必须等于k时才更新答案。


---

## 作者：Locix_Elaina_Celome (赞：6)

>夕凪の静寂が僕を包んだ
>
>君を連れていった青嵐のあとで
>
>例え十年先も二十年先も
>
>きっと ずっと
>
>忘れられないんだよ
>
>手を繋いで誓った 幼い約束を
>
>夏の終わりを告げるような
>
>微温い風とともに
>
>淡い紅掛けの空の色に
>
>染まっていくよ
>
>——青嵐のあとで

（听歌听激动了挂一小段歌词）

# [AGC031E Snuke the Phantom Thief](https://www.luogu.com.cn/problem/AT_agc031_e) 题解

## 题意

> 在一个 $100\times 100$ 的网格图上有若干个点，每个点用三元组 $(x_i,y_i,v_i)$ 表示，其中 $v_i$ 表示这个点的点权。
>
> 给出若干个形如 $(t_i,a_i,b_i)$ 的限制，表示横/纵坐标大于等于/小于等于 $a_i$ 的点最多选择 $b_i$ 个。$t_i$ 为限制的类型。
>
> 现在要选出若干个点，使得总点权最大。

## 题解

凭感觉这个题和「CF704D」有点像，尝试把每个点转化成横纵坐标之间的连边。

然后尝试在左右部点上分别搞限制，发现不会。

如果只有前/后缀操作是很好做的，但是这里前后缀混着搞，很烦。

发现如果就这样进行费用流建模不行，因为费用流优先保证最大流，其次再是费用，而这里我们不关心最大流。而这里数据范围又比较小，所以枚举选点的数量 $k$。

又发现很难在左右部上搞限制，尝试对每个“决策”进行限制。

对于一个限制 $(t_i,a_i,b_i)$ ，假设是限制 $x$ 坐标。

对于“$x\le a_i$ 的点最多选择 $b$ 个”这样的限制，转化为“将所选出的点按 $x$ 排序后，$\forall i\in [b+1,k]$，满足 $x_i\ge a+1$“。

同理，对于“$x\ge a_i$ 的点最多选择 $b$ 个”这样的限制，转化为“将所选出的点按 $x$ 排序后，$\forall i\in [1,k-b]$，满足 $x_i\le a-1$“。

$y$ 坐标也是一样的，不再赘述。

然后我们就得到了每个”选择“的合法坐标区间，建图跑费用流即可。

具体的，先把横、纵坐标作为左、右部得到一张二分图，每个点是一条 $(x_i,y_i,1,v_i)$ 的边。然后再将每个”选择“也拆成横、纵坐标两个点。每个表示横坐标的点向左部中其合法区间内的点连一条容量为 $(1,0)$ 的边；左部中每个合法区间内的点向每个表示纵坐标的点向连一条 $(1,0)$ 的边。最后由 $S$ 向表示横坐标的点连一条 $(1,0)$ 的边，表示纵坐标的点向 $T$ 连一条 $(1,0)$ 的边，跑最大费用最大流即可。

## 代码
```cpp
using namespace std;
//#include<bits/stdc++.h>
#include<cstdio>
#include<queue>
//#include<cstring>
//#include<string>
//#include<iostream>
//#include<utility>
//#include<algorithm>
#define MAX(x,y) (x<y?y:x)
#define MIN(x,y) (x<y?x:y)
#define ABS(x) (x<0?-x:x)
#define lb(x) ((x)&(-(x)))
#define N 100005
#define M 100005
#define V 100
#define LL long long
#define LD long double
#define int LL
//#define double LD
#define P 1000000007
#ifdef _WIN32
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#elif _WINDOWS_
#define getchar _getchar_nolock
#define putchar _putchar_nolock
#else
#define getchar getchar_unlocked
#define putchar putchar_unlocked
#endif
constexpr double EPS=(1e-9);
#ifdef int
constexpr int INF=1211081101201201140;
#else
constexpr int INF=1145141919;
#endif
template<typename T>T Max(T x,T y){return MAX(x,y);}
template<typename T>T Min(T x,T y){return MIN(x,y);}
template<typename T>T Abs(T x){return ABS(x);}
template<typename T>void Swap(T&x,T&y){x^=y^=x^=y;}
template<typename T>T Gcd(T x,T y){while(y^=x^=y^=x%=y);return x;}
template<typename T>
T qp(T a,T b){T sum=1;
while(b){if(b&1)sum=(sum*a)%P;a=(a*a)%P;b>>=1;}return sum;}
template<typename T>
void read(T&x){
x=0;char c=getchar();/*T fl=1;*/
while(c<'0'||c>'9'){/*if(c == '-')fl=-1;*/c=getchar();}
while('/'<c&&c<':'){x=(x<<3)+(x<<1)+c-'0';c=getchar();}/*x*=fl;*/}
template<typename T>
void write(T x){if(x<0){x=-x;putchar('-');}
if(x>9){write(x/10);}putchar(x%10|48);} 
int n,m;
int cnt,S,T;
int t[M],las[M],fir[N],c[M],val[M],num=1;
void add(int u,int v,int w,int x){
t[++num]=v;c[num]=w;las[num]=fir[u];fir[u]=num;val[num]=x;
t[++num]=u;c[num]=0;las[num]=fir[v];fir[v]=num;val[num]=-x;}
int dis[N];
int inq[N];
int del[N];
int a[N];
int lev[N];
int vis[N];
int build(){
	for(int i=1;i<=cnt;i++)dis[i]=INF,inq[i]=0,del[i]=fir[i];
	queue<int>q;
	q.push(S),dis[S]=0,inq[S]=1;
	while(q.size()){
		int u=q.front();
		q.pop();
		inq[u]=0;
		for(int i=fir[u];i;i=las[i]){
			if(c[i]<=0||dis[t[i]]<=dis[u]+val[i])continue;
			dis[t[i]]=dis[u]+val[i];
			if(!inq[t[i]])q.push(t[i]);
			inq[t[i]]=1;
		}
	}
	return dis[T]<INF;
}
int sum=0;
int dfs(int u,int mn){
	if(u == T||!mn)return mn;
	int st=mn;
	vis[u]=1;
	for(int i=del[u];i&&mn;i=las[i]){
		del[u]=i;
		if(vis[t[i]]||!c[i]||dis[t[i]]!=dis[u]+val[i])continue;
		int x;
		if(x=dfs(t[i],Min(mn,c[i])))sum+=x*val[i],c[i]-=x,c[i^1]+=x,mn-=x;
		else dis[t[i]]=INF;
	}
	vis[u]=0;
	return st-mn;
}
void solve(){while(build())dfs(S,INF);}
struct Nd{int x,y,v;}nd[N];
struct St{char op;int a,b;}st[N];
int xx[N],xn[N],yx[N],yn[N];
#undef int
int main(){
#define int LL
	read(n);
	for(int i=1;i<=n;i++)read(nd[i].x),read(nd[i].y),read(nd[i].v);
	read(m);
	for(int i=1;i<=m;i++){
		st[i].op=getchar();
		while(st[i].op<'A'||'Z'<st[i].op)st[i].op=getchar();
		read(st[i].a);
		read(st[i].b);
	}
	int ans=0;
	for(int k=1;k<=n;k++){
		num=1;
		sum=0; 
		for(int i=0;i<=V+V+2+2*n;i++)fir[i]=0;
		cnt=V+V;
		S=++cnt;
		T=++cnt;
		for(int i=1;i<=k;i++)xx[i]=yx[i]=V,xn[i]=yn[i]=1; 
		for(int i=1;i<=n;i++)add(nd[i].x,V+nd[i].y,1,-nd[i].v);
		for(int i=1;i<=m;i++){
			switch(st[i].op){
				case 'L':{
					for(int j=st[i].b+1;j<=k;j++)xn[j]=Max(xn[j],st[i].a+1);
					break;
				}
				case 'R':{
					for(int j=1;j<=k-st[i].b;j++)xx[j]=Min(xx[j],st[i].a-1);
					break;
				}
				case 'D':{
					for(int j=st[i].b+1;j<=k;j++)yn[j]=Max(yn[j],st[i].a+1);
					break;
				}
				case 'U':{
					for(int j=1;j<=k-st[i].b;j++)yx[j]=Min(yx[j],st[i].a-1);
					break;
				}
			}
		}
		for(int i=1;i<=k;i++){
			++cnt;
			add(S,cnt,1,0);
			for(int j=xn[i];j<=xx[i];j++)add(cnt,j,1,0);
			++cnt;
			add(cnt,T,1,0);
			for(int j=yn[i];j<=yx[i];j++)add(j+V,cnt,1,0);
		}
		ans=Max(ans,-(solve(),sum));
	}
	write(ans);
	return 0;
}
```

---

## 作者：Misaka14285 (赞：5)

来一个上下界最大费用可行流建模。~~我边数少，我了不起~~

首先枚举总共偷的宝石数，记为 $k$。

那么 $\sum [x_i\ge a_i] \le b_i\iff \sum[x_i\le a_i-1]\ge k-b_i$

设 $sx_j=\sum [x_i\le j]$，则限制 $L,R$ 被转化为 $sx_i\in [lx_i,rx_i]$ 的形式。$U,D$ 同理。

因为 $sx$ 是前缀和的形式，可以想到让宝石对应边，流量代表偷不偷，然后让他们汇入一根有向的链，这样链上每个位置的流量就是 $sx$。

具体地，连边 $X_{i+1}\to X_i$，流量 $[lx_i,rx_i]$；连边 $Y_i\to Y_{i+1}$，流量 $[ly_i,r_i]$。这些边费用都是 $0$。

对于宝石 $(x,y,v)$，连边 $X_x\to Y_y$，容量 $1$，费用 $v$。

令源为 $S=X_{101}$，汇为 $T=Y_{101}$，连边 $T\to S$，流量 $[k,k]$，费用 $0$，表示必须恰好偷 $k$ 颗宝石。

代码：

```cpp
const int N = 310;
int n, m;
int x[N], y[N];
ll v[N];
int typ[N], a[N], b[N];
int lim[N][4];
int deg[N];

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n;
	F(i, 1, n) cin >> x[i] >> y[i] >> v[i];
	map<char, int> mbg;
	mbg['L'] = 0;
	mbg['R'] = 1;
	mbg['D'] = 2;
	mbg['U'] = 3;
	cin >> m;
	F(i, 1, m) {
		string s;
		cin >> s >> a[i] >> b[i];
		typ[i] = mbg[s[0]];
	}
	ll ans = 0;
	F(i, 1, 101) F(j, 0, 3) lim[i][j] = n;
	F(i, 1, m) chkmn(lim[a[i]][typ[i]], b[i]);

	flow::s = 203, flow::t = flow::n = 204;
	using flow::add;
	auto myadd = [](int u, int v, int l, int r, ll c) {
		if (l > r) throw 1;
		add(u, v, c, r - l);
		deg[u] += l, deg[v] -= l;
	};
	F(tot, 1, n) { try {
		if (tot > lim[1][1] || tot > lim[1][3]) throw 1;
		memset(deg, 0, sizeof deg);
		flow::reset();
		F(i, 1, 100) {
			int lower = max(0, tot - lim[i + 1][1]), upper = lim[i][0];
			myadd(i + 1, i, lower, upper, 0);
		}
		F(i, 1, 100) {
			int lower = max(0, tot - lim[i + 1][3]), upper = lim[i][2];
			myadd(i + 101, i + 102, lower, upper, 0);
		}
		myadd(202, 101, tot, tot, 0);
		F(i, 1, n) myadd(x[i], y[i] + 101, 0, 1, -v[i]);
		ll sum = 0;
		F(i, 1, 202) if (deg[i]) {
			if (deg[i] < 0)
				add(flow::s, i, 0, -deg[i]);
			else
				add(i, flow::t, 0, deg[i]), sum += deg[i];
		}
		flow::mcmf();
		if (flow::flow == sum) {
			ans = max(ans, -flow::cost);
		}
	} catch (...) { } }
	cout << ans << "\n";
}
```

---

## 作者：xht (赞：1)

## [Snuke the Phantom Thief](https://atcoder.jp/contests/agc031/tasks/agc031_e)

### 题意

- 有 $n$ 个两两不同的点，第 $i$ 个点的坐标为 $(x_i,y_i)$，价值为 $v_i$。
- 你要选择一些点，满足 $m$ 条限制，每条限制形如：
  - `L a b`，最多选择 $b$ 个 $x_i \le a$ 的点。
  - `R a b`，最多选择 $b$ 个 $x_i \ge a$ 的点。
  - `D a b`，最多选择 $b$ 个 $y_i \le a$ 的点。
  - `U a b`，最多选择 $b$ 个 $y_i \ge a$ 的点。
- 求选择的点的最大价值和。
- $n \le 80$，$m \le 320$。

### 题解

枚举选择的点的个数 $k$，考虑费用流。

对于每一维，那么最多 $b$ 个 $\le a$ 的点可以转化为按坐标从小到大选择的第 $[b+1,k]$ 个点的坐标要 $\ge a + 1$，最多 $b$ 个 $\ge a$ 的点可以转化为选择的第 $[1,k-b]$ 个点的坐标要 $\le a - 1$。

考虑如何建图，将点 $i$ 拆成两个点 $P_i,Q_i$，另外加入 $2k$ 个点 $X_{1\dots k},Y_{1\dots k}$，表示某一维上选择的第 $i$ 个点。

连边如下：

- $(S, X_i, 1, 0)$。
- $(X_i,P_j,1,0)$，其中点 $j$ 在 $X_i$ 的坐标限制内。
- $(P_j,Q_j,1,-v_j)$。
- $(Q_j,Y_i,1,0)$，其中点 $j$ 在 $Y_i$ 的坐标限制内。
- $(Y_i,T,1,0)$。

跑最小费用最大流即可。

### 代码

```cpp
namespace Dinic {
	const int N = 1e5 + 7, M = 2e6 + 7;
	const ll inf = 1e18;
	int n, S, T;
	int h[N], hi[N], e[M], t[M], tot;
	ll d[N], f[M], c[M], mxf, ans;
	bool v[N];

	inline void add(int x, int y, ll z, ll w, bool o = 1) {
		e[++tot] = y, f[tot] = z, c[tot] = w, t[tot] = h[x], h[x] = tot;
		if (o) add(y, x, 0, -w, 0);
	}

	inline bool bfs() {
		for (int i = 1; i <= n; i++) d[i] = inf, v[i] = 0;
		queue<int> q;
		q.push(S), d[S] = 0, v[S] = 1;
		while (q.size()) {
			int x = q.front();
			q.pop(), v[x] = 0;
			for (int i = h[x]; i; i = t[i]) {
				int y = e[i];
				ll z = f[i], w = c[i];
				if (d[y] <= d[x] + w || !z) continue;
				d[y] = d[x] + w;
				if (!v[y]) q.push(y), v[y] = 1;
			}
		}
		return d[T] != inf;
	}

	ll dfs(int x, ll now = inf) {
		if (x == T) return now;
		v[x] = 1;
		ll rst = now;
		for (int &i = hi[x]; i; i = t[i]) {
			int y = e[i];
			ll z = f[i], w = c[i];
			if (v[y] || d[y] != d[x] + w || !z) continue;
			ll k = dfs(y, min(z, rst));
			if (!k) d[y] = inf;
			else ans += k * w, f[i] -= k, f[i^1] += k, rst -= k;
			if (!rst) break;
		}
		v[x] = 0;
		return now - rst;
	}

	inline void main() {
		while (bfs()) {
			for (int i = 1; i <= n; i++) hi[i] = h[i];
			ll now;
			while ((now = dfs(S))) mxf += now;
		}
	}

	inline void init(int _n, int _S, int _T) {
		n = _n, S = _S, T = _T, tot = 1, mxf = 0, ans = 0;
		for (int i = 1; i <= n; i++) h[i] = 0; 
	}
}
using Dinic::add;

const int N = 87, M = 327;
int n, m, x[N], y[N], a[M], b[M];
char t[M];
ll v[N], ans;

inline bool in(int l, int x, int r) {
	return l <= x && x <= r;
}

inline ll work(int k) {
	static int lx[N], rx[N], ly[N], ry[N];
	for (int i = 1; i <= k; i++)
		lx[i] = ly[i] = 1, rx[i] = ry[i] = 100;
	for (int i = 1; i <= m; i++)
		switch (t[i]) {
			case 'L' : {
				for (int j = b[i] + 1; j <= k; j++)
					lx[j] = max(lx[j], a[i] + 1);
				break;
			}
			case 'R' : {
				for (int j = 1; j <= k - b[i]; j++)
					rx[j] = min(rx[j], a[i] - 1);
				break;
			}
			case 'D' : {
				for (int j = b[i] + 1; j <= k; j++)
					ly[j] = max(ly[j], a[i] + 1);
				break;
			}
			case 'U' : {
				for (int j = 1; j <= k - b[i]; j++)
					ry[j] = min(ry[j], a[i] - 1);
				break;
			}
		}
	for (int i = 1; i <= n; i++)
		if (lx[i] > rx[i] || ly[i] > ry[i]) return 0;
	static int S, T, P[N], Q[N], X[N], Y[N], C;
	S = 1, T = 2, C = 2;
	for (int i = 1; i <= n; i++) P[i] = ++C, Q[i] = ++C;
	for (int i = 1; i <= k; i++) X[i] = ++C, Y[i] = ++C;
	Dinic::init(C, S, T);
	for (int i = 1; i <= n; i++) add(P[i], Q[i], 1, -v[i]);
	for (int i = 1; i <= k; i++) {
		add(S, X[i], 1, 0), add(Y[i], T, 1, 0);
		for (int j = 1; j <= n; j++) {
			if (in(lx[i], x[j], rx[i])) add(X[i], P[j], 1, 0);
			if (in(ly[i], y[j], ry[i])) add(Q[j], Y[i], 1, 0);
		}
	}
	Dinic::main();
	return Dinic::mxf == k ? -Dinic::ans : 0;
}

int main() {
	rd(n);
	for (int i = 1; i <= n; i++) rd(x[i], y[i]), rd(v[i]);
	rd(m);
	for (int i = 1; i <= m; i++) rdc(t[i]), rd(a[i], b[i]);
	for (int k = 1; k <= n; k++) ans = max(ans, work(k));
	print(ans);
	return 0;
}
```

---

## 作者：xlpg0713 (赞：0)

这题我觉得很 edu 啊。

看着就很像网络流，但是很可惜这个问题直接做是做不了的。所以需要一些思考。

考虑原题给出的一个条件：$a_i$ 左侧的点不超过 $b_i$ 个。这等价于，如果我们选了大于 $b_i$ 个点，那么第 $b_i$ 即以后的横坐标要大于 $a_i$。

进一步的，如果把所有的条件都改写一遍，可以得到每个点横纵坐标的下界和上界，也可以得知（原图中的）某个点是否可以作为第 $i$ 个点出现。

接下来就是网络流经典问题。枚举填的点的个数 $k$。

建出 $k$ 个点表示横坐标，源点向每个这样的点连边，流量为 $1$，费用为 $0$。

同样 $k$ 个点表示纵坐标，向汇点连边，流量为 $1$，费用为 $0$。

原图的每个点拆成左右两个点，左边的点向右边的连边，流量为 $1$，费用为该点权值。

如果这个点的横坐标可以作为第 $i$ 个点，表示横坐标的第 $i$ 号点向这个点的左部点连边，流量为 $1$，费用为 $0$。

如果这个点的纵坐标可以作为第 $i$ 个点，这个点的右部点向表示纵坐标的第 $i$ 个点连边，流量为 $1$，费用为 $0$。

跑最大费用最大流即可。复杂度 $O(n\times nmf)=O(n^5)$。

```cpp
#include<iostream>
#include<algorithm>
#include<atcoder/all>
#define int long long
const int N = 105, inf = 2e15;
int n, m, x[N], y[N], w[N], a[N], b[N], c[N], d[N];
int f(int k){
    atcoder::mcf_graph<int, int> g(2 * k + 2 * n + 2);
    int s = 0, t = 2 * k + 2 * n + 1;
    for(int i = 1; i <= k; i++) g.add_edge(s, i, 1, 0), 
        g.add_edge(i + n * 2 + k, t, 1, 0);
    for(int i = 1; i <= n; i++){
        g.add_edge(i + k, i + k + n, 1, -w[i] + inf);
        for(int j = 1; j <= k; j++){
            if(x[i] >= a[j] && x[i] <= b[k - j + 1])
                g.add_edge(j, i + k, 1, 0);
            if(y[i] >= c[j] && y[i] <= d[k - j + 1])
                g.add_edge(i + k + n, j + k + n * 2, 1, 0);
        }
    } auto [a, b] = g.flow(s, t); return -b + a * inf;
}
signed main(){
    std::cin >> n; for(int i = 1; i <= n; i++) 
        std::cin >> x[i] >> y[i] >> w[i];
    std::fill(b, b + n + 1, inf); std::fill(d, d + n + 1, inf);
    std::cin >> m; for(int i = 1; i <= m; i++){
        char ch; int x, y; std::cin >> ch >> x >> y; ++y;
        if(ch == 'L') a[y] = std::max(a[y], x + 1);
        if(ch == 'R') b[y] = std::min(b[y], x - 1);
        if(ch == 'D') c[y] = std::max(c[y], x + 1);
        if(ch == 'U') d[y] = std::min(d[y], x - 1);
    }
    for(int i = 1; i <= n; i++)
        a[i] = std::max(a[i], a[i - 1]),
        b[i] = std::min(b[i], b[i - 1]),
        c[i] = std::max(c[i], c[i - 1]),
        d[i] = std::min(d[i], d[i - 1]);
    int rs(0); for(int i = 1; i <= n; i++) rs = std::max(rs, f(i));
    std::cout << rs;
}
```

---

## 作者：yyrwlj (赞：0)

## 解题思路

当看到某道题目的限制比较复杂时，可以试试往网络流的方向思考。

考虑枚举偷的珠宝数 $k$，分别处理出第 $i$ 颗珠宝能放置的横纵坐标范围。

将 $n$ 颗珠宝拆成入点和出点，入点向对应的出点连一条容量为 $1$、费用为该珠宝价值的边（以保证每个珠宝最多被选一次）。

分别为横纵建出 $k$ 个点，第 $i$ 个横点向每个横坐标满足第 $i$ 颗选的珠宝的横坐标范围的珠宝连边，纵点同理。源点向每个横点连边，每个纵点向汇点连边，这样一个最大匹配的网络流模型就建好了，跑最大费用最大流即可。

接下来考虑要偷 $k$ 颗珠宝时，第 $i$ 颗珠宝能取的横纵坐标范围是什么。先考虑一维，即坐标大于等于 $a$ 的珠宝最多偷 $b$ 颗，可以转化为前 $k-b$ 颗的坐标要小于等于 $a-1$，若是小于等于则反之。

这样的思路扩展到二维也一样，横纵分别做一遍即可。

## Code

```cpp
cin >> n;
for (int i=1;i<=n;i++)
	cin >> x[i] >> y[i] >> v[i];
cin >> m;
for (int i=1;i<=m;i++)
	cin >> op[i] >> a[i] >> b[i];
int ans = 0;
for (int k=1;k<=n;k++)
{
	T = 2 * k + 2 * n + 1;
	for (int i=0;i<=T;i++)
		h[i] = 0;
	idx = 1;
	for (int i=1;i<=k;i++)
		add(S, i, 1, 0);
	for (int i=k+1;i<=2*k;i++)
		add(i, T, 1, 0);
	for (int i=2*k+1;i<=2*k+n;i++)
		add(i, i + n, 1, v[i - 2 * k]);
	for (int i=1;i<=k;i++)
	{
		ly[i] = lx[i] = 0;
		ry[i] = rx[i] = inf;
	}
	for (int i=1;i<=m;i++)
		if (op[i] == 'L')
			for (int j=b[i]+1;j<=k;j++)
				lx[j] = max(lx[j], a[i] + 1);
		else if (op[i] == 'R')
			for (int j=1;j<=k-b[i];j++)
				rx[j] = min(rx[j], a[i] - 1);
		else if (op[i] == 'D')
			for (int j=b[i]+1;j<=k;j++)
				ly[j] = max(ly[j], a[i] + 1);
		else
			for (int j=1;j<=k-b[i];j++)
				ry[j] = min(ry[j], a[i] - 1);
	for (int i=1;i<=k;i++)
		for (int j=1;j<=n;j++)
			if (ly[i] <= y[j] && y[j] <= ry[i])
				add(i, 2 * k + j, 1, 0);
	for (int i=1;i<=k;i++)
		for (int j=1;j<=n;j++)
			if (lx[i] <= x[j] && x[j] <= rx[i])
				add(2 * k + n + j, k + i, 1, 0);
	ans = max(ans, EK());
}
cout << ans;
```

---

## 作者：Rainsleep (赞：0)

[cnblog](https://www.cnblogs.com/Rainsheep/p/18026415)

限制很棘手，因为约束性并不强，我们尝试转化。

枚举当前选了 $k$ 个点，那么对于“横坐标小于等于 $a_i$ 的珠宝最多偷 $b_i$ 颗。”的限制，我们对于 $\forall i \in [b_i + 1, k]$，有 $y_i > a_i$。其他的三个限制也可以做类似的转化，于是我们对每个点的横纵坐标做出了约束，而我们想满足的条件除了选取的点数需要是 $k$ 外，还有权值和最大，进而想到费用流。

为了限制每个点只能选择一次，对每个点拆点 $p, q$ 作为该点的入点和出点，连边 $(p, q, 1, v_i)$ 限制该点最多选一次，且可以获得贡献 $v_i$。为了满足 $x$ 的限制，我们建 $k$ 个虚点 $g_i$ 表示当前选择的 $k$ 个点，同时连边 $(s, g_i, 1, 0)$。如法炮制另外 $k$ 个点 $h_i$ 用来限制 $y$ 坐标，并且连边 $(h_i, t, 1, 0)$。

考虑对于每组限制连边，例如 $\forall i \in [b_i + 1, k]$，有 $y_i > a_i$，那么就可以从 $i \in [b_i + 1, k]$ 连边 $(g_i, p_j, 1, 0)(y_i > a_j)$，其他几种限制类似。

实现上，可能会出现坐标限制更宽松，但是点数更严格的情况，所以需要对每一维度维护前缀/后缀的最值。之后跑最大费用最大流即可。

```cpp
// 如果命运对你缄默, 那就活给他看。
#pragma GCC optimize(1)
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast", "inline", "-ffast-math")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#include <bits/stdc++.h>
using namespace std;
typedef long long LL; 
#define int LL
const int maxn = 1000, maxm = maxn * maxn << 4;
const int maxL = 320;
int n, m, tot = -1, h[maxn], idx;
struct E { int v, nx, f; LL c; } e[maxm];
const int INF = 1e9;
inline void add(int u, int v, int f, LL c) { 
	e[++ tot] = {v, h[u], f, c}, h[u] = tot;
	e[++ tot] = {u, h[v], 0, -c}, h[v] = tot;
}
struct Point { int x, y; LL v; } a[maxn];
int A[maxn], B[maxn], C[maxn], D[maxn];
LL ans = 0;
int s, t, f[maxn], pr[maxn];
LL d[maxn];
inline bool spfa() {
	static int q[maxn << 2];
	int hh = 0, tt = 0; q[0] = s;
	memset(f, 0, sizeof f), f[s] = INF;
	memset(d, -0x3f, sizeof d), d[s] = 0;
	bitset <maxn> st;
	while(hh <= tt) {
		int u = q[hh ++ ];
		st[u] = 0;
		for(int i = h[u]; ~i; i = e[i].nx) {
			int v = e[i].v, f = e[i].f, c = e[i].c;
			if(f && d[v] < d[u] + c) {
				d[v] = d[u] + c;
				:: f[v] = min(:: f[u], f);
				pr[v] = i;
				if(!st[v]) q[++ tt] = v, st[v] = 1;
			}
		}
	}
	return f[t] > 0;
}
inline LL EK() {
	int flow = 0;
	LL cost = 0;
	while(spfa()) {
		flow += f[t], cost += 1LL * f[t] * d[t];
		for(int u = t; u ^ s; u = e[pr[u] ^ 1].v) {
			e[pr[u]].f -= f[t], e[pr[u] ^ 1].f += f[t];
		}
	}
	return cost;
}
inline void solve(int k) {
	memset(h, -1, sizeof h), tot = -1;
	s = n << 1 | 1, t = (n << 1) + 2;
	idx = t;
	for(int i = 1; i <= k; ++ i) {
		add(s, idx + i, 1, 0);
		add(idx + k + i, t, 1, 0);
	}
	for(int i = 1; i <= n; ++ i) {
		add(i, i + n, 1, a[i].v);
		for(int j = 1; j <= k; ++ j) {
			if(A[j] <= a[i].x && a[i].x <= B[k - j + 1]) add(idx + j, i, 1, 0);
			if(C[j] <= a[i].y && a[i].y <= D[k - j + 1]) add(i + n, idx + k + j, 1, 0);
		}
	}
	ans = max(ans, EK());
} 
signed main() {
	ios :: sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for(int x, y, i = 1; i <= n; ++ i) {
		LL v;
		cin >> x >> y >> v;
		a[i] = {x, y, v};
	}
	cin >> m;
	memset(B, 0x3f, sizeof B);
	memset(D, 0x3f, sizeof D);
	for(int i = 1; i <= m; ++ i) {
		char ty[2]; int x, b;
		cin >> ty >> x >> b, b ++ ;
		if(*ty == 'L') A[b] = max(A[b], x + 1);
		else if(*ty == 'R') B[b] = min(B[b], x - 1);
		else if(*ty == 'D') C[b] = max(C[b], x + 1);
		else if(*ty == 'U') D[b] = min(D[b], x - 1);
	}
	for(int i = 1; i <= n; ++ i) {
		A[i] = max(A[i], A[i - 1]), B[i] = min(B[i], B[i - 1]);
		C[i] = max(C[i], C[i - 1]), D[i] = min(D[i], D[i - 1]);
	}
	for(int i = 1; i <= n; ++ i) solve(i);
	cout << ans << '\n';
	return 0;
}

// qwq
```

---

## 作者：wYYSZLwSSY (赞：0)

挺好的题，感觉能学到不少东西。

## 题解
注意到限制比较复杂，不太好拆贡献或者限制，考虑网络流。

较多的限制第一反应是直接最大费用流最大流，但是这个题没有一个限制是类似“最大流”的限制，即使建出图可能求的也是最多选取下的最大价值之类的东西。

考虑能不能直接把一个物品的价值直接当成流量，想到最小割，但是连通性很难和“不超过”这种东西联系上，故也否定。

想一下我们建图的难点在哪里，首先是可能会加上一些其他的限制，其次是不好满足题目中的限制。

先解决第一个问题，还是考虑费用流（毕竟还是很像这个东西），前面的建图问题是可能会要求选取最多的（强制流最大），那我们不妨枚举流的大小，然后就可以控制选取的个数可以不是最多。

再考虑如何满足题目中的限制，先考虑一维的情况，假设我们选了 $k$ 个点，一个条件是坐标小于等于 $a$ 的不超过 $b$ 个，那么我们可以转化为“从小到大的第 $b+1$ 及以后的点坐标超过 $a$”，其他类似。转化后，按顺序排下来的每一个选择了的点都有了一定的坐标范围，并向满足条件的点连边。

两个维度的限制其实就是在另外一边也做这样的限制。

## 具体做法

枚举选择的数量 $k$，建 $k$ 个点，源点和它连费用 $0$，流量 $1$ 的边，假定这 $k$ 个点的编号就是它们在选好点后的排序位置，按照这个条件，根据前面的转化，确定 x 轴的范围 $[l,r]$，向右边 $n$ 个点中横坐标在范围内的点连边，费用为 $0$ 流量为 $1$。

之后，将 $n$ 个点向它们右侧的 $n$ 个点连费用 $v_i$，流量 $1$ 的边，把右侧的 $n$ 个点与它们右侧的 $k$ 个点连边，类似上面的，不过这次的限制是纵坐标。

这样一来，如果满流，求出来的最大费用就是选取 $k$ 个的最大价值；如果不能满流，说明没有选取 $k$ 个的方法。

实际操作中，并不需要判定是否满流，因为不满流也不会出现不符合的情况（就是说在这样的操作下，选 $k$ 个的限制比选比 $k$ 少个的限制更紧）。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
int n,m,x[85],y[85],v[84];
char c[355];
int a[355],b[355],ans,st,ed;
int num,hd[505];
int minn[505],maxx,dis[505],last[505];
bool in[505];
int l[85],r[85];
struct P{int nxt,to,dis,c;}line[51303];
void add(int x,int y,int z,int a){
	++num;
	line[num]={hd[x],y,z,a};
	hd[x]=num;

	++num;
	line[num]={hd[y],x,0,-a};
	hd[y]=num;
	return ;
}
queue<int>dl;
bool SPFA(int st){
	while(dl.size())dl.pop();
	dl.push(st);
	memset(dis,0xf0,sizeof(dis));
	dis[st]=0;
	memset(in,0,sizeof(in));
	in[st]=1;
	minn[st]=3e18;
	while(dl.size()){
		int tp=dl.front();
		dl.pop();in[tp]=0;
		for(int i=hd[tp];i;i=line[i].nxt){
			int to=line[i].to;
			if(!line[i].dis)continue;
			if(dis[to]<dis[tp]+line[i].c){
				dis[to]=dis[tp]+line[i].c;
				last[to]=i;
				minn[to]=min(minn[tp],line[i].dis);
				if(!in[to])in[to]=1,dl.push(to);
			}
		}
	}
	return dis[ed]>-1e16;
}
void WHE(){
	int tp=ed,qr=minn[ed];
	while(tp!=st){
		line[last[tp]].dis-=qr;
		line[last[tp]^1].dis+=qr;
		tp=line[last[tp]^1].to;
	}
	ans+=qr*dis[ed];
	return ;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
// 	freopen("1.in","r",stdin);
	cin>>n;
	for(int i=1;i<=n;++i)cin>>x[i]>>y[i]>>v[i];
	cin>>m;
	for(int i=1;i<=m;++i)cin>>c[i]>>a[i]>>b[i];
	for(int i=1;i<=n;++i){//枚举选取个数
     // x 轴的限制
		for(int j=1;j<=i;++j)l[j]=-3e18,r[j]=3e18;
		for(int j=1;j<=m;++j){
			if(c[j]=='L')
				for(int k=b[j]+1;k<=i;++k)
					l[k]=max(l[k],a[j]+1);//b+1 及之后的要大于 a
			else if(c[j]=='R')
				for(int k=1;k<=i-b[j];++k)
					r[k]=min(r[k],a[j]-1);//i-b 及之前第要小于 a
		}
		st=4*n+1,ed=4*n+2;
		num=1;
		memset(hd,0,sizeof(hd));
		for(int j=1;j<=i;++j){
			add(st,j,1,0);//保证是一个
			for(int k=1;k<=n;++k)
				if(x[k]<=r[j] and x[k]>=l[j])
					add(j,k+n,1,0);			
		}
		for(int j=1;j<=n;++j)add(j+n,j+2*n,1,v[j]);//一个物品仅仅可以选一次+价值产生
	// y 轴限制
		for(int j=1;j<=i;++j)l[j]=-3e18,r[j]=3e18;
		for(int j=1;j<=m;++j){
			if(c[j]=='D')
				for(int k=b[j]+1;k<=i;++k)
					l[k]=max(l[k],a[j]+1);
			else if(c[j]=='U')
				for(int k=1;k<=i-b[j];++k)
					r[k]=min(r[k],a[j]-1);
		}
		for(int j=1;j<=i;++j){
			add(j+3*n,ed,1,0);
			for(int k=1;k<=n;++k)
				if(y[k]<=r[j] and y[k]>=l[j])
					add(k+2*n,j+3*n,1,0);			
		}
		ans=0;
		while(SPFA(st))WHE();
		maxx=max(ans,maxx);
	}
	cout<<maxx<<'\n';
	return 0;
}
```

---

