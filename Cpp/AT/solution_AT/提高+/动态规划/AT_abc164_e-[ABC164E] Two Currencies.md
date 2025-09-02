# [ABC164E] Two Currencies

## 题目描述

有 $n$ 个城市，它们由 $m$ 条双向道路连接，保证它们能够彼此到达。第 $i$ 条道路连接 $u_i,v_i$，需要花费 $x_i$ 个银币，耗费 $t_i$ 秒的时间。每个城市处都有兑换银币处，第 $i$ 个城市中你可以用 $1$ 个金币兑换 $c_i$ 个银币，可以兑换无限次，不过兑换 $1$ 次需要花费 $d_i$ 秒的时间。你一开始在 $1$ 号城市，有 $s$ 个银币和无限多的金币，求到其它城市需要耗费的最小时间。

$1 \leq n \leq 50$，$n - 1 \le m \le 100$，$1 \leq x_i \leq 50$，$1 \leq t_i,d_i \leq 10^9$，$1 \leq s,c_i \leq 10^9$

## 样例 #1

### 输入

```
3 2 1
1 2 1 2
1 3 2 4
1 11
1 2
2 5```

### 输出

```
2
14```

## 样例 #2

### 输入

```
4 4 1
1 2 1 5
1 3 4 4
2 4 2 2
3 4 1 1
3 1
3 1
5 2
6 4```

### 输出

```
5
5
7```

## 样例 #3

### 输入

```
6 5 1
1 2 1 1
1 3 2 1
2 4 5 1
3 5 11 1
1 6 50 1
1 10000
1 3000
1 700
1 100
1 1
100 1```

### 输出

```
1
9003
14606
16510
16576```

## 样例 #4

### 输入

```
4 6 1000000000
1 2 50 1
1 3 50 5
1 4 50 7
2 3 50 2
2 4 50 4
3 4 50 3
10 2
4 4
5 5
7 7```

### 输出

```
1
3
5```

## 样例 #5

### 输入

```
2 1 0
1 2 1 1
1 1000000000
1 1```

### 输出

```
1000000001```

# 题解

## 作者：lzyqwq (赞：13)

[题目传送门](https://www.luogu.com.cn/problem/AT4845)

此题有城市和银币两个条件，普通的最短路肯定是不行的。

我们观察数据发现，$ 1≤n≤50,1 \leq x_i \leq 50$，这两个数据很小，是否在给我们提示。

的确如此，最短路径最坏的情况下是要经过所有其他的城市共 $50-1=49$ 个（起点一开始就在已经到达了不需要时间、银币所以不算），每到一个新的城市最多花费 $50$ 个银币，所以最坏情况下需要花费 $49×50=2450$ 个银币，也算挺小了。如果一开始的银币数量超过 $2450$，也看作 $2450$，因为都足够到达了。

由于银币数量的不同会引起最短路线的不同，所以我们可以把一个点拆成 $2451$ 个点（$0-2450$），$g[u][a]$ 表示到城市 $u$ 花费 $a$ 个银币的节点。这样一来，我们一共要开 $55×2455=135025$ 的数组（多开一点看着舒服 doge），不会超限。

讲完节点，接下来讲建边。由于从城市 $u$ 到 城市 $v$ 要花 $x_i$ 个银币，$t_i$的时间。假设在城市 $u$ 有 $a$ 个银币，则到城市 $v$ 后有 $a-x_i$ 个银币，所以我们从 $g[u][a]$ 到 $g[v][a-x_i]$ 之间建一条长 $t_i$ 的有向边，再把 $u$ 和 $v$ 反过来按照同样的方法再建一条有向边，这样就建成了一条无向边。由于最少要 $x_i$ 个银币才能到达，最多要 $2450$ 个银币就足够到达，所以 $a$ 的取值范围为 $x_i \leq a \leq 2450$。故建图代码如下：
```cpp
for(int j=p;j<=2450;j++)//变量名称与上面的讲解略有不同
{
	g[u][j].push_back(edge{v,j-p,t});
	g[v][j].push_back(edge{u,j-p,t});
}
```


然后是换银币，假设我们在第 $i$ 个城市换银币，换后有 $b$ 个银币，由于每次换 $c_i$ 个，所以换之前有 $b-c_i$ 个银币。换一次需要花费 $d_i$ 的时间，所以从 $g[i][b-c_i]$ 到 $g[i][b]$ 建一条长 $d_i$ 的有向边。这里只能建一条，因为换银币是从少到多，所以也只能从少到多建，不能从多到少建。由于换银币后（就是换了，排除不换的情况）最少有 $c_i$ 个银币，最多有 $2450$ 个银币就足够了，所以 $b$ 的取值范围为 $c_i \leq b \leq 2450$。故建图代码如下：
```cpp
for(int j=c;j<=2450;j++)//变量名与上面的讲解略有不同
{
	g[i][j-c].push_back(edge{i,j,d});
}
```
然后我们在这个图上跑最短路，对于城市 $i$，答案为 $dis[i][0...2450]$ 中的最小值。注意不是银币越少时间越短，比如说在一个点用 $1$ 秒换 $700$ 个银币，另一个点用 $700$ 秒换 $1$ 个银币，那肯定还是 $700$ 个银币更快（虽然不是在同一个点，但是前面多了后面肯定也多了）。我用的是堆优化的 Dijkstra，保证码风不毒瘤（这一点我身为蒟蒻要批评一下楼上的巨佬们，你们的码风真的太毒瘤了，自己本身就很巨不需要用毒瘤的码风来掩盖）。
# AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
long long dis[55][2455];
bool vis[55][2455];
struct edge
{
	int x,p,t;
};
vector<edge>g[55][2455];
struct node
{
	int x,p;
	long long t;
	bool operator<(const node&a)const
	{
		return t>a.t;
	}
};
priority_queue<node>pq;
int main()
{
	memset(dis,0x3f,sizeof(dis));
	int n,m,s;
	scanf("%d%d%d",&n,&m,&s);
	s=min(s,2450);//2450个就够了
	for(int i=1;i<=m;i++)
	{
		int u,v,p,t;
		scanf("%d%d%d%d",&u,&v,&p,&t);
		for(int j=p;j<=2450;j++)//u和v之间的双向边
		{
			g[u][j].push_back(edge{v,j-p,t});
			g[v][j].push_back(edge{u,j-p,t});
		}
	}
	for(int i=1;i<=n;i++)
	{
		int c,d;
		scanf("%d%d",&c,&d);
		for(int j=c;j<=2450;j++)//换银币的单向边
		{
			g[i][j-c].push_back(edge{i,j,d});
		}
	}
	dis[1][s]=0;//到自己距离为0
	pq.push(node{1,s,0});//起点入队
	while(pq.size())//Dijkstra
	{
		node k=pq.top();
		pq.pop();
		int a=k.x,b=k.p;
		long long c=k.t;
		if(vis[a][b])
		{
			continue;
		}
		vis[a][b]=1;
		for(int i=0;i<g[a][b].size();i++)
		{
			edge f=g[a][b][i];
			int x=f.x,y=f.p,z=f.t;
			if(c+z<dis[x][y])
			{
				dis[x][y]=c+z;
				pq.push(node{x,y,c+z});
			}
		}
	}
	for(int i=2;i<=n;i++)
	{
		long long ans=0x3f3f3f3f3f3f3f3f;
		for(int j=0;j<=2450;j++)//注意不是银币越少时间越短
		{
			ans=min(ans,dis[i][j]);
 		}
		printf("%lld\n",ans);
	}
	return 0;
}
```
码风是不是不毒瘤，没骗你们吧？

[最后安利一发自己的博客](https://www.luogu.com.cn/blog/juruo-lzy/)，完结撒花！
跪求管理大大过审 orz！！！

---

## 作者：feecle6418 (赞：8)

设 $f_{i,j}$ 为在 $i$，有 $j$ 个银币的方案数。由于 $a_i\le 50$，$\sum a_i\le 5000$，因此 $j$ 的最大值只会有 $5000$。

容易观察到对于每个 $i$，$j$ 是单调不减的。这意味着我们可以用类似于 Dijkstra 的方法转移（可以看作分层图最短路）。按照以下两种方式转移即可（$v$ 为时间，$a$ 为金钱）：

$$f_{i,j}\leftarrow f_{k,j+a(k,i)}+v(k,i)$$

$$f_{i,j+c_i}\leftarrow f_{i,j}+d_i$$

用二叉堆实现转移，时间复杂度为 $\Theta(T\log T)$，其中 $T=n\sum a_i$ 约为 $250000$。


---

## 作者：small_john (赞：6)

## 前言

简单的~~水~~蓝题。

## 思路

设每个点有两个值 $x,y$，其中 $x$ 表示点的编号，$y$ 表示当前拥有的硬币数。我们知道，整个路径最多花 $2500$ 个硬币，那么，就可以在以下点之间连边：

1. 对于 $2\sim m+1$ 行输入的 $U,V,A,B$，在 $(U,j)$ 和 $(V,j-A)$ 中建边，花费为 $B$（$j$ 是 $A\sim 2500$ 中的一个数，枚举当前拥有的硬币），在 $(V,j)$ 和 $(U,j-A)$ 中建边，花费为 $B$（$j$ 和上面意思一样）。即花 $B$ 个时间在 $U,V$ 之间往返。

2. 对于 $m+2\sim m+n+2$ 行输入的 $C,D$，在 $(i,j)$ 和 $(i,j+C)$ 中建边（$i$ 是当前的点，$j$ 是拥有的硬币，保证 $j+C\le2500$），花费为 $D$。即在第 $i$ 个点花 $D$ 个时间换 $C$ 个硬币。

建完边后，这道题就转换为一道单源最短路，第一个点就是 $(1,\min\{2500,S\})$，跑一遍 Dijkstra 就行了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define x first
#define y second
#define mp(x,y) make_pair(x,y)
using namespace std;
const int M = 2500;
priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
int n,m,cnt,to[2000005],nxt[2000005],head[2000005],f[2000005],g[2000005],dis[2000005],d[55],s[55][2505],S,k;
bool vis[2000005];
void add(int x,int y,int z)
{
	nxt[++cnt] = head[x];
	head[x] = cnt;
	to[cnt] = y;
	g[cnt] = z;
}
int get(int x,int y)
{
	if(!s[x][y]) s[x][y] = ++k,f[k] = x;
	return s[x][y];
}
void dijkstra()
{
	memset(dis,0x3f,sizeof dis);
	dis[get(1,min(M,S))] = 0;
	q.push(mp(0,get(1,min(M,S))));
	while(!q.empty())
	{
		int t = q.top().y;q.pop();
		if(vis[t]) continue;
		vis[t] = 1;
		for(int i = head[t];i;i = nxt[i])
		{
			int u = to[i];
			if(!vis[u]&&dis[u]>dis[t]+g[i])
			{
				dis[u] = dis[t]+g[i];
				d[f[u]] = min(d[f[u]],dis[u]);
				q.push(mp(dis[u],u));
			}
		}
	}
}
signed main()
{
	memset(d,0x3f,sizeof d);
	d[1] = 0;
	cin>>n>>m>>S;
	for(int i = 1;i<=m;i++)
	{
		int a,b,c,d;
		cin>>a>>b>>c>>d;
		for(int j = c;j<=M;j++)
			add(get(a,j),get(b,j-c),d);
		for(int j = c;j<=M;j++)
			add(get(b,j),get(a,j-c),d); 
	}
	for(int i = 1;i<=n;i++)
	{
		int x,y;
		cin>>x>>y;
		for(int j = 0;j+x<=M;j++)
			add(get(i,j),get(i,j+x),y);
	}
	dijkstra();
	for(int i = 2;i<=n;i++)
		cout<<d[i]<<'\n';
	return 0;
}
```

---

## 作者：Lynkcat (赞：5)

考虑一种乱搞做法。

首先我们可以看到 $a_i \leq 50$ ，首先可以想到跑分层图最短路。然后做法可想而知……

但是

作为菜鸡的我模拟赛时完全没有看出来这是个分层图最短路，所以我这个菜鸡只写出来了一个 $dp$ 方程。

$dp_{i,j}$ 为从 $1$ 到 $n$ 金钱为 $j$ 时的最少时间。因为我没看出来这是个分层图最短路，所以我直接怒写暴力 $dp$ 。

$dp_{to,j+val}=min(dp_{i,j}+time,dp_{to,j+val})$ 。我们可以不考虑转移顺序，直接从 $1$ 到 $n$ 暴力转移 $30$ 遍。

由于数据范围的限制，我们发现这样做在随机数据下的正确性非常非常的高。

于是我们就可以过了这题。

```
//QwQcOrZ yyds!!!
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=e[i].nx)
#define mp make_pair
#define pb push_back
#define pa pair < int,int >
#define fi first
#define se second
#define re register
#define be begin()
#define en end()
#define sqr(x) ((x)*(x))
#define ret return puts("-1"),0;
#define put putchar('\n')
#define inf (1e18)
#define mod 100000007
#define int ll
#define N 5001
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll x){write(x),putchar(' ');}
inline void writeln(ll x){write(x);putchar('\n');}
int n,m,S,f[51][51],dp[51][N],ans,x,y,val,val1,c[51],d[51],ansl[51],xu[51],sums;
bool Cmp(int x,int y)
{
	return (f[1][x]<f[1][y])||(f[1][x]==f[1][y])&&(x<y);
}
struct nod
{
	int to,val,val1;
};
vector<nod>G[N];
signed main()
{
	n=read(),m=read(),S=read();
	if (S>=2450ll)//如果能跑完整张图，那就完全没有必要打工，直接输出最短路。
	{
		memset(f,0x3f,sizeof(f));
		for (int i=1;i<=n;i++) f[i][i]=0;
		for (int i=1;i<=m;i++)
		{
			x=read(),y=read(),val=read(),val1=read();
			f[x][y]=val1;
			f[y][x]=val1;
		}
		for (int k=1;k<=n;k++)
			for (int i=1;i<=n;i++) 
				if (i!=k)
					for (int j=1;j<=n;j++)
						if (i!=j&&j!=k)
							f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
		for (int i=2;i<=n;i++) writeln(f[1][i]);
	} else {
	memset(dp,0x3f,sizeof(dp));
	memset(ansl,0x3f,sizeof(ansl));
		memset(f,0x3f,sizeof(f));
	for (int i=1;i<=m;i++)
	{
		x=read(),y=read(),val=read(),val1=read();
		G[x].push_back({y,val,val1});
		G[y].push_back({x,val,val1});
		f[x][y]=val1;
		f[y][x]=val1;
		sums+=val;
	}
	dp[1][S]=0;
	for (int k=1;k<=n;k++)
			for (int i=1;i<=n;i++) 
				if (i!=k)
					for (int j=1;j<=n;j++)
						if (i!=j&&j!=k)
							f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	for (int i=1;i<=n;i++) xu[i]=i;
	sort(xu+1,xu+n+1,Cmp);//正确性优化，把离 $1$ 的距离近的先做。
	S=min(2450ll,sums*3);
	for (int i=1;i<=n;i++) c[i]=read(),d[i]=read();
	for (int rt=0;rt<=min(30ll,3*m);rt++)
	{
		for (int i=1;i<=n;i++)
		{
			
			if (c[xu[i]]<=S)
			{
			for (int j1=0;j1<=S-c[xu[i]];j1++)
					dp[xu[i]][j1+c[xu[i]]]=min(dp[xu[i]][j1]+d[xu[i]],dp[xu[i]][j1+c[xu[i]]]);}//如果打工不能跑完整张图那就老老实实在当前这个点一次次打工
         else 
			{
			int pp=0x3f3f3f3f3f3f3f3f;
			for (int j=0;j<=S;j++) pp=min(pp,dp[xu[i]][j]);
			for (int j=1;j<=n;j++)
					if (i!=j)
						ansl[j]=min(ansl[j],pp+f[xu[i]][j]+c[xu[i]]);}//否则直接更新用最短路走到每个点的答案，正确性优化
			for (int j=0;j<G[xu[i]].size();j++)
				for (int k=S-G[xu[i]][j].val;k>=0;k--)
					dp[G[xu[i]][j].to][k]=min(dp[xu[i]][k+G[xu[i]][j].val]+G[xu[i]][j].val1,dp[G[xu[i]][j].to][k]);//用边来更新
		}
	}
	for (int t=2;t<=n;t++)
	{
		ans=ansl[t];
		for (int i=0;i<=S;i++) ans=min(ans,dp[t][i]);
		writeln(ans);	
	}
				}
}
```


---

## 作者：gyh20 (赞：3)

一道分层图最短路的题。

看到 $S\leq 10^9$，不要害怕，因为当 $S\geq 2500$ 时已经足够了，因为你至多经过 $n-1$ 条边，每条边的代价又不超过 $50$，所以多了也没用。

令 $f_{i,j}$ 表示当前在点 $i$，有 $j$ 个银币的最短时间消耗，每一个 $f_{i,j}$ 向 $f_{i,j+d_{i}}$ 连 $c_i$ 的有向边，表示花 $c_i$ 的时间在这里换$d_i$ 个银币。对于每条边 $(x,y)$，拆成两条有向边 $x->y$ 和 $y->x$，再对于每一条有向边 $x->y$，从 $f_{x,j}$ 向 $f_{y,j-a_i}$ 连 $b_i$ 的边，表示花费 $a_i$ 个银币，$b_i$ 的时间从 $x$ 走向 $y$。对于每一个 $f_{i,j}$，向 $f_{i,j-1}$ 连边，方便操作。

最后求出 $f_{1,S}$ 到每一个 $f_{i,0}$ 的答案即可。

为了方便操作，把二维数组强行拍成一维的。

数组要开的足够大，记得要开 long long。

```cpp
#include<bits/stdc++.h>
#define re register
#define int long long
using namespace std;
inline int read(){
	re int t=0;re char v=getchar();
	while(v<'0')v=getchar();
	while(v>='0')t=(t<<3)+(t<<1)+v-48,v=getchar();
	return t;
}
struct edge{
	int to,next,w;
}e[20000002];
int n,m,head[300002],ans,cnt,sum,s;
inline void add(re int x,re int y,re int w){
	e[++cnt].to=y;
	e[cnt].next=head[x];
	head[x]=cnt;
	e[cnt].w=w;
}
struct node{
    int pos,dis;
    bool operator <(const node x)const{
        return dis>x.dis;
    }
}h[300002];
priority_queue <node> q;
bool v[300002];
inline int pos(re int x,re int y){
	return x*(sum+1)+y;
}
inline void dis(re int s){for(re int i=1;i<=pos(n,sum);++i)h[i].dis=1e18,h[i].pos=i;
    h[s].dis=0;
    q.push(h[s]);
    while(!q.empty()){
        while((h[q.top().pos].dis<q.top().dis)){q.pop();if(q.empty())break;
        }
        if(q.empty())break;
        node tmp=q.top();
        q.pop();
        for(re int i=head[tmp.pos];i;i=e[i].next){
            if((tmp.dis+e[i].w)<h[e[i].to].dis){
                h[e[i].to].dis=tmp.dis+e[i].w;
                q.push(h[e[i].to]);
            }
        }
     
    }
}
signed main(){
	n=read();m=read();s=read();
	sum=5000;
	for(re int i=1,x,y,a,b;i<=m;++i){
		x=read();y=read();a=read();b=read();
		for(re int j=a;j<=sum;++j)add(pos(x,j),pos(y,j-a),b),add(pos(y,j),pos(x,j-a),b);
	}
	for(re int x,y,i=1;i<=n;++i){
		x=read();y=read();
		for(re int j=0;j<=sum;++j){
		add(pos(i,j),pos(i,min(j+x,sum)),y);if(j)add(pos(i,j),pos(i,j-1),0);}
	}
	dis(pos(1,min(s,sum)));
	for(re int i=2;i<=n;++i)printf("%lld\n",h[pos(i,0)].dis);
}

```


---

## 作者：Tenshi (赞：2)

## 分析
二维 dijktra + 状态转移思想。
在一个城市 $u$ ，有两个去处：
- 在原地买币（币增加，时间耗费增加）。
- 去其它城市（币减少，时间耗费增加）。

在建图的时候可以把第一个操作看做是：从 $u$ 到 $u$ ，然后时间耗费（边权）为题目所说的 $D$ ，而币消耗为题目所说的 $C$ 取负。

（代码如下，~~码风保证不毒瘤~~）

```cpp
#pragma GCC optimize("O3")
#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define dwn(i,a,b) for(int i=(a);i>=(b);i--)
#define ceil(a,b) (a+(b-1))/b
#define ll_INF 0x7f7f7f7f7f7f7f7f
typedef long long ll;

#define int long long

inline void read(int &x) {
    int s=0;x=1;
    char ch=getchar();
    while(ch<'0'||ch>'9') {if(ch=='-')x=-1;ch=getchar();}
    while(ch>='0'&&ch<='9') s=(s<<3)+(s<<1)+ch-'0',ch=getchar();
    x*=s;
}

const int N=55, M=N*N<<1;

int n, m, s;
int lim;
int S=1;

struct node{
	int to, c, w, next;
}e[M];

int tot, h[N];
int C[N], D[N]; // coin and time

void add(int u, int v, int c, int w){
	e[tot].to=v, e[tot].c=c, e[tot].w=w, e[tot].next=h[u], h[u]=tot++;
}

struct element{
	int u, c, w;
	bool operator < (const element &o)const{
		return w==o.w? c>o.c: w>o.w;
	}
};

int d[N][M];
bool vis[N][M];

void dijk(){
	memset(d, 0x3f, sizeof d); 
	priority_queue<element> q;
	d[S][s]=0; 
	q.push({S, s, 0});
	
	while(q.size()){
		auto hd=q.top(); q.pop();
		
		int u=hd.u, c=hd.c, w=hd.w; 
		if(vis[u][c]) continue;
		vis[u][c]=true;
		
		for(int i=h[u]; ~i; i=e[i].next){
			int go=e[i].to;
			if(go==u && c>=lim) continue;
			int t=c-e[i].c; t=min(lim, t);
			if(t<0) continue;
			if(d[go][t]>d[u][c]+e[i].w){
				d[go][t]=d[u][c]+e[i].w;
				q.push({go, t, d[go][t]});
			}
		}
	}
}

signed main(){
	memset(h, -1, sizeof h);
	cin>>n>>m>>s;
	
	rep(i,1,m){
		int u, v, c, w; // cost dist
		read(u), read(v), read(c), read(w); lim+=c;
		add(u, v, c, w), add(v, u, c, w);
	}
	s=min(s, lim);
	
	rep(i,1,n) read(C[i]), read(D[i]);
	rep(i,1,n) add(i, i, -C[i], D[i]);
	
	dijk();
	
	rep(i,2,n){
		int res=ll_INF;
		rep(j,0,lim) res=min(res, d[i][j]);
		cout<<res<<endl;
	}
	
    return 0;
}
```

---

## 作者：rainygame (赞：1)

模拟赛的简单题。

观察数据范围，可以发现 $N,M,A_i$ 很小，但是其它的都很大。

然后可以发现 $\sum A_i\le100\times 50=5000$，所以从任意节点到任意节点最多就是把 $M$ 条边都走一遍，最多只需要 $5000$ 个银币。所以我们只需要记录 $5000$ 及以下的银币数量。

我们将图分层，令第 $i$ 的 $j$ 节点表示走到 $j$ 节点还有 $i$ 个银币的情况，显然最多只有 $5001$ 层（即 $i \in [0,5000]$）。普通的边就是将第 $i$ 层的 $u$ 号点和第 $i-a$ 层的 $v$ 号点连接（注意是双向边）。在格子上购买银币就可以从第 $i$ 层往第 $\min\{i+c,5000\}$ 层连一条边。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define MAXN 51
#define MAXM 5001

int n, m, s, u, v, a, b, ans, c, d, w;
int dis[MAXN*MAXM];
bitset<MAXN*MAXM> vis;
vector<pair<int, int>> e[MAXN*MAXM];

struct Node{
    int u, dis;
    bool operator<(Node b)const{
        return dis > b.dis;
    }
};
priority_queue<Node> pq;

void dijkstra(){
    memset(dis, 0x3f, sizeof(dis));
    dis[s*n] = 0;
    pq.push({s*n, 0});
    while (!pq.empty()){
        u = pq.top().u;
        pq.pop();
        if (vis.test(u)) continue;
        vis.set(u);

        for (auto i: e[u]){
            v = i.first;
            w = i.second;
            if (dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                pq.push({v, dis[v]});
            }
        }
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    cin >> n >> m >> s;
    s = min(s, 5000ll);
    while (m--){
        cin >> u >> v >> a >> b;
        --u;
        --v;
        for (int j(a); j<MAXM; ++j){
            e[u+j*n].push_back({v+(j-a)*n, b});
            e[v+j*n].push_back({u+(j-a)*n, b});
        }
    }
    for (int i(0); i<n; ++i){
        cin >> c >> d;
        for (int j(0); j<MAXM; ++j) e[i+j*n].push_back({i+min(5000ll, j+c)*n, d});
    }
    dijkstra();

    for (int i(1); i<n; ++i){
        ans = LLONG_MAX;
        for (int j(0); j<MAXM; ++j) ans = min(ans, dis[i+j*n]);
        cout << ans << '\n';
    }

    return 0;
}
```


---

## 作者：FL_sleake (赞：1)

本题解未建图、未跑最短路，~~使用乱搞大法~~，码量大概是目前题解区最少的吧。

### 题意简述

有 $n$ 个城市，它们由 $m$ 条双向道路连接，保证它们能够彼此到达。第 $i$ 条道路连接 $u_i,v_i$，需要花费 $x_i$ 个银币，耗费 $t_i$ 秒的时间。每个城市处都有兑换银币处，第 $i$ 个城市中你可以用 $1$ 个金币兑换 $c_i$ 个银币，可以兑换无限次，不过兑换 $1$ 次需要花费 $d_i$ 秒的时间。你一开始在 $1$ 号城市，有 $s$ 个银币和无限多的金币，求到其它城市需要耗费的最小时间。

### 解题思路

考虑 dp。设 $dp_{i,j}$ 表示在 $i$ 城市，有 $j$ 个银币时所需的最短时间。显然，转移方式有两种，一种是从一个城市走到另一个城市，一种是兑换银币。这两种转移的式子对应如下：

$$dp_{u,j-x}=\min(dp_{u,j-x},dp_{v,j}+t)$$

$$dp_{i,j}=\min(dp_{i,j},dp_{i,j-c}+d)$$

其中 $u,v,x,t,c,d$ 均为题中所给条件，下标已省略，$i,j$ 为枚举的变量。

然后考虑把上面两个东西转移个 $100$ 次，就可以通过本题了。正确性方面，我个人感觉是类似 bellman-ford，借助本题数据范围小的特点，所以转移 $100$ 次就对了。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,m,s,u[10010],v[10010],x[10010],t[10010];
int c[10010],d[10010],dp[55][2510];
signed main(){
	memset(dp,0x3f,sizeof(dp));
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++) cin>>u[i]>>v[i]>>x[i]>>t[i];
	for(int i=1;i<=n;i++) cin>>c[i]>>d[i];
	s=min(s,2500ll);//银币太多是无用的
	dp[1][s]=0;//初始化
	for(int _=0;_<=100;_++){//转移100次
		for(int i=1;i<=n;i++){
			for(int j=c[i];j<=2500;j++) dp[i][j]=min(dp[i][j],dp[i][j-c[i]]+d[i]);
		}//兑换银币的转移
		for(int i=1;i<=m;i++){
			for(int j=x[i];j<=2500;j++){
				dp[u[i]][j-x[i]]=min(dp[u[i]][j-x[i]],dp[v[i]][j]+t[i]);
				dp[v[i]][j-x[i]]=min(dp[v[i]][j-x[i]],dp[u[i]][j]+t[i]);
			}
		}//城市的转移，这个和bellman-ford几乎一样
	}
	for(int i=2;i<=n;i++){
		int ans=0x3f3f3f3f3f3f3f3f;
		for(int j=0;j<=2500;j++) ans=min(ans,dp[i][j]);
		cout<<ans<<endl;
	}
	return 0;
}
```

---

## 作者：XenonKnight (赞：0)

> 题意：有 $n$ 个城市，它们由 $m$ 条双向道路连接，保证它们能够彼此到达。第 $i$ 条道路连接 $u_i,v_i$，需要花费 $x_i$ 个银币，耗费 $t_i$ 秒的时间。每个城市处都有兑换银币处，第 $i$ 个城市中你可以用 $1$ 个金币兑换 $c_i$ 个银币，可以兑换无限次，不过兑换 $1$ 次需要花费 $d_i$ 秒的时间。你一开始在 $1$ 号城市，有 $s$ 个银币和无限多的金币，求到其它城市需要耗费的最小时间。

> $1 \leq n \leq 50$，$1 \leq x_i \leq 50$，$1 \leq t_i,d_i \leq 10^9$，$1 \leq s,c_i \leq 10^9$

~~abc 的 F 都切不掉，只好水 E 的题解了~~

观察到虽然 $s,c_i$ 很大，但是 $x_i$ 只有 $50$。这也就意味着到其它需要花费的银币绝对不会超过 $49 \times 50=2450$，所以如果当前银币数超过 $2450$，就可以将它看作 $2450$。

我们将“当前位于城市 $i$，手中有 $j$ 个银币”**这一状态**看成一个点 $(i,j)$，那么我们可以重新建一张图，两个状态 $(x_1,y_1),(x_2,y_2)$ 之间有一条**有向边**当且仅当 $(x_1,y_1)$ 可以到达 $(x_2,y_2)$，边权为花费的时间。

有了这一思想的启发，接下来便是建图：

- $(i,j) \rightarrow (i,j+c_i)$，边权为 $d_i$
- $(i,j) \rightarrow (k,j-x_p)$，边权为 $t_p$，其中 $(i,k)$ 之间有边，编号为 $p$，$j \geq x_p$

跑一遍 dijkstra，起点为 $(1,s)$，点 $u$ 的答案就是 $\min\ (1,s)$ 到 $(u,i)$ 的距离。

总结：这道题本身虽然不是很难，但是其建图思想还是挺重要的，尤其在网络流这一板块中，将“一种状态”表示为“一个点”的思想经常用到。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi			first
#define se			second
#define fz(i,a,b)	for(int i=a;i<=b;i++)
#define fd(i,a,b)	for(int i=a;i>=b;i--)
#define foreach(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define all(a)		a.begin(),a.end()
#define giveup(...) return printf(__VA_ARGS__),0;
#define fill0(a)	memset(a,0,sizeof(a))
#define fill1(a)	memset(a,-1,sizeof(a))
#define fillbig(a)	memset(a,0x3f,sizeof(a))
#define fillsmall(a) memset(a,0xcf,sizeof(a))
#define mask(a)		(1ll<<(a))
#define maskx(a,x)	((a)<<(x))
#define _bit(a,x)	(((a)>>(x))&1)
#define _sz(a)		((int)(a).size())
#define filei(a)	freopen(a,"r",stdin);
#define fileo(a)	freopen(a,"w",stdout);
#define fileio(a) 	freopen(a".in","r",stdin);freopen(a".out","w",stdout)
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#define put(x)		putchar(x)
#define eoln        put('\n')
#define space		put(' ')
#define y1			y_chenxiaoyan_1
#define y0			y_chenxiaoyan_0
#define int long long
typedef pair<int,int> pii;
inline int read(){
	int x=0,neg=1;char c=getchar();
	while(!isdigit(c)){
		if(c=='-')	neg=-1;
		c=getchar();
	}
	while(isdigit(c))	x=x*10+c-'0',c=getchar();
	return x*neg;
}
inline void print(int x){
	if(x<0){
		putchar('-');
		print(abs(x));
		return;
	}
	if(x<=9)	putchar(x+'0');
	else{
		print(x/10);
		putchar(x%10+'0');
	}
}
inline int qpow(int x,int e,int _MOD){
	int ans=1;
	while(e){
		if(e&1)	ans=ans*x%_MOD;
		x=x*x%_MOD;
		e>>=1;
	}
	return ans;
}
int n=read(),m=read(),s=read(),c[55],d[55];
struct edge{
	int u,v,w;
	edge(){/*ycxakioi*/}
	edge(int _u,int _v,int _w){
		u=_u;v=_v;w=_w;
	}
};
const int MAGIC=2456;
inline int id(int x,int y){
	return x*(MAGIC+1)+y;
}
vector<edge> g[55*2555];
int dist[55*2555],vis[25*2555];
priority_queue<pii,vector<pii>,greater<pii> > q;
signed main(){
	fz(i,1,m){
		int u,v,a,b;cin>>u>>v>>a>>b;
		fz(j,0,MAGIC){
			if(j>=a){
				g[id(u,j)].push_back(edge(id(u,j),id(v,j-a),b));
				g[id(v,j)].push_back(edge(id(v,j),id(u,j-a),b));
			}
		}
	}
	fz(i,1,n)	c[i]=read(),d[i]=read();
	fz(i,1,n){
		fz(j,0,MAGIC-1){
			int cur=j+c[i];
			if(cur>=MAGIC){
				g[id(i,j)].push_back(edge(id(i,j),id(i,MAGIC),d[i]));
			}
			else{
				g[id(i,j)].push_back(edge(id(i,j),id(i,cur),d[i]));
			}
		}
	}
	fillbig(dist);
	dist[id(1,min(s,MAGIC))]=0;
	q.push({0,id(1,min(s,MAGIC))});
	while(!q.empty()){
		pii p=q.top();q.pop();
		int sum=p.fi,x=p.se;
		if(sum>dist[x])	continue;
		foreach(it,g[x]){
			int y=it->v,z=it->w;
			if(dist[y]>dist[x]+z){
				dist[y]=dist[x]+z;
				q.push({dist[y],y});
			}
		}
	}
	fz(i,2,n){
		int mn=0x3f3f3f3f3f3f3f3fll;
		fz(j,0,MAGIC)	mn=min(mn,dist[id(i,j)]);
		cout<<mn<<endl;
	}
	return 0;
}
```

---

