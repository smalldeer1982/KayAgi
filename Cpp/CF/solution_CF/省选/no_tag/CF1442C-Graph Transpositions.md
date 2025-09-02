# Graph Transpositions

## 题目描述

给你一个$n$个顶点和$m$条边的有向图。顶点编号从$1$到$n$。顶点$1$处有一个标记。

你可以进行以下两种操作：

- 移动标记：如果存在一条$u\to v$的边，将标记从$u$移动到$v$，这个操作需要$1$秒。
- 图翻转：翻转图上的所有边的方向，将图上**每一条边**$u\to v$替换为$v\to u$，第$k$次使用这个操作需要耗时$2^{k-1}$秒。

你需要找到将标记从$1$移动到$n$的最短时间，请将答案对$998,244,353$取模。

## 说明/提示

$1\leq n,m\leq 200000,1\leq u,v\leq n,u\not =v$。

保证不存在重边并且至少存在一种从$1$到$n$的方案。

translated by $\texttt{lory1608}$

## 样例 #1

### 输入

```
4 4
1 2
2 3
3 4
4 1```

### 输出

```
2```

## 样例 #2

### 输入

```
4 3
2 1
2 3
4 3```

### 输出

```
10```

# 题解

## 作者：QwQcOrZ (赞：19)

介绍一个不需要分层图的做法

看到题的第一想法是如果翻转超过 $O(log)$ 次是不优的，因为花费会超过直接跑一遍的情况

那么有个非常 simple 的想法是记 $f_{i,j}$ 表示到达第 $i$ 个点，翻转 $j$ 次的最短路（不计翻转的代价），然后跑 `bfs`

但我们会发现在有些情况下这样做会假掉，因为从起点出发不翻转超过 $log$ 次甚至可能无法到达某个点

那么我们考虑改变 $f_{i,j}$ 表示的含义，先预处理出 $tim_i$ 表示到达第 $i$ 个点最少要翻转几次。记 $f_{i,j}$ 表示到达第 $i$ 个点，翻转次数为 $tim_i+j$ 次的最短路

可以发现这里的 $j$ 是 $log$ 级别的，因为我们已经保证了必定可以到达点 $i$，如果翻转次数多于 $log$ 必定不优

然后跑个 `bfs` 计算所有的 $f_{i,j}$，然后枚举翻转次数计算最优解即可。$tim_i$ 可以用 `01bfs` 处理

复杂度 $O(nlogn)$

```cpp
#include<bits/stdc++.h>
#define mk make_pair
#define x first
#define y second
#define int long long
using namespace std;
const int N=2e5+5;
const int p=998244353;

int read()
{
	int s=0;
	char c=getchar(),lc='+';
	while (c<'0'||'9'<c) lc=c,c=getchar();
	while ('0'<=c&&c<='9') s=s*10+c-'0',c=getchar();
	return lc=='-'?-s:s;
}
void write(int x)
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
void print(int x,char c='\n')
{
	write(x);
	putchar(c);
}
int power(int a,int b)
{
	int ret=1;
	while (b)
	{
		if (b&1) ret=ret*a%p;
		a=a*a%p;
		b/=2;
	}
	return ret;
}
struct edge
{
	bool f;
	int to,nxt;
}e[N*2];
int head[N],cnt=0;
void add(int u,int v,bool w)
{
	e[++cnt].f=w;
	e[cnt].to=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
int n,m,tim[N],dis[N][20];
deque<int>dq;
void bfs0()
{
	memset(tim,0x3f,sizeof(tim));
	dq.clear();
	tim[1]=0;
	dq.push_back(1);
	while (!dq.empty())
	{
		int now=dq.front();
		dq.pop_front();
		for (int i=head[now];i;i=e[i].nxt)
		{
			int to=e[i].to,f=e[i].f^(tim[now]&1);
			if (f)
			{
				if (tim[to]>tim[now]+1)
				{
					tim[to]=tim[now]+1;
					dq.push_back(to);
				}
			}
			else
			{
				if (tim[to]>tim[now])
				{
					tim[to]=tim[now];
					dq.push_front(to);
				}
			}
		}
	}
}
queue<pair<int,int> >q;
void bfs1()
{
	memset(dis,0x3f,sizeof(dis));
	dis[1][0]=0;
	q.push(mk(1,0));
	while (!q.empty())
	{
		pair<int,int>now=q.front();
		q.pop();
		for (int i=head[now.x];i;i=e[i].nxt)
		{
			int to=e[i].to,f=e[i].f^(now.y&1);
			if (now.y+f-tim[to]>=20) continue;
			if (dis[to][now.y+f-tim[to]]>dis[now.x][now.y-tim[now.x]]+1)
			{
				dis[to][now.y+f-tim[to]]=dis[now.x][now.y-tim[now.x]]+1;
				q.push(mk(to,now.y+f));
			}
		}
	}
}
struct answer
{
	int k,val;
	bool operator <(const answer &a)const
	{
		if (max(k,a.k)>20) return k<a.k;
		return (1<<k)+val<(1<<a.k)+a.val;
	}
}ans({1919810,0});

signed main()
{
	n=read();
	m=read();
	for (int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		add(u,v,0);
		add(v,u,1);
	}
	bfs0();
	bfs1();
	for (int i=0;i<20;i++) ans=min(ans,(answer){tim[n]+i,dis[n][i]});
	print((power(2,ans.k)-1+ans.val)%p);

	return 0;
}
```

---

## 作者：Lynkcat (赞：8)

考虑一种玄学做法。

首先建立分层图

首先观察到 $2^{19}$ 已经大于当前这个 $n$ 了，所以我们可以发现：在 $19$ 层及以上时，如果当前层能到达终点，走到下一层一定不优。

所以我们可以考虑分两种情况：$19$ 层以下和 $19$ 层以上。

显然 $19$ 层以下跑个最短路就行了。

考虑 $19$ 层以上，我们可以将每层之间的转移的代价设为一个极大值（我设的是 $10^7$ )。再跑最短路，最后得出来的结果除以 $10^7$ 就是转移的次数了。接着最后的答案用快速幂计算即可。

代码：
```
#include<bits/stdc++.h>
#define ll long long
#define F(i,a,b) for (int i=(a);i<=(b);i++)
#define R(i,a,b) for (int i=(a);i<(b);i++)
#define D(i,a,b) for (int i=(a);i>=(b);i--)
#define go(i,x) for (int i=head[x];i;i=Next[i])
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
#define mod 998244353
#define int ll
#define N 400005
using namespace std;
inline char gc(){static char buf[100000],*p1=buf,*p2=buf;return p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++;}
#define gc getchar
inline ll read(){char c=gc();ll su=0,f=1;for (;c<'0'||c>'9';c=gc()) if (c=='-') f=-1;for (;c>='0'&&c<='9';c=gc()) su=su*10+c-'0';return su*f;}
inline void write(ll x){if (x<0){putchar('-');write(-x);return;}if (x>=10) write(x/10);putchar(x%10+'0');}
inline void writesp(ll a){if(a<0){a=-a; putchar('-');}write(a); putchar(' ');}
inline void writeln(ll a){if(a<0){a=-a; putchar('-');}write(a); puts("");}
ll quickPower(int x,int y)
{
	int ans=1;x%=mod;
	while (y>0)
	{
		if (y&1) (ans*=x)%=mod;
		(x*=x)%=mod;
		y>>=1;
	}
	return ans;
}
int n,m,dis[19][N],dis1[N],u,v,ans,vis[N];
vector<int>G[N][2];
vector<pair<int,int> >G1[N];
struct wcr
{
	int x,y;
	bool operator <(const wcr &A) const
	{
		return dis[x][y]>dis[A.x][A.y];
	}
};
priority_queue<wcr>q;
priority_queue<pair<int,int> >q1;
wcr now;
pair<int,int>now1;
signed main()
{
	n=read(),m=read();
	F(i,0,18)
		F(j,1,n)
			dis[i][j]=inf;
	F(i,1,n) G1[i].push_back(mp(i+n,10000000)),G1[i+n].push_back(mp(i,10000000));
	F(i,1,m) 
	{
		u=read(),v=read();
		G[u][0].push_back(v);
		G[v][1].push_back(u);
		G1[u].push_back(mp(v,1));
		G1[v+n].push_back(mp(u+n,1));
	}
	q.push({0,1});
	dis[0][1]=0;
	while (!q.empty())
	{
		now=q.top();
		q.pop();
		if (now.x<=17)
		{
			if (dis[now.x+1][now.y]>dis[now.x][now.y]+(1ll<<now.x))
			{
				dis[now.x+1][now.y]=dis[now.x][now.y]+(1ll<<now.x);
				q.push({now.x+1,now.y});
			}
		}
		R(i,0,G[now.y][now.x%2].size())
		{
//			cout<<dis[now.x][G[now.y][now.x%2][i]]<<endl;
			if (dis[now.x][G[now.y][now.x%2][i]]>dis[now.x][now.y]+1)
			{
				dis[now.x][G[now.y][now.x%2][i]]=dis[now.x][now.y]+1;
				q.push({now.x,G[now.y][now.x%2][i]});
			}
		}
	}
	ans=inf;
	F(i,0,18) ans=min(ans,dis[i][n]);
	if (ans!=inf) writeln(ans%mod); else
	{
		F(i,1,2*n+5) dis1[i]=inf;
		dis1[1]=0;
		q1.push(mp(0,1));
		while (!q1.empty())
		{
			now1=q1.top();q1.pop();
			if (vis[now1.second]) continue;
			vis[now1.second]=1;
			R(i,0,G1[now1.second].size())
			{
				if (dis1[G1[now1.second][i].first]>dis1[now1.second]+G1[now1.second][i].second)
				{
					dis1[G1[now1.second][i].first]=dis1[now1.second]+G1[now1.second][i].second;
					q1.push(mp(-dis1[G1[now1.second][i].first],G1[now1.second][i].first));
				}
			}
		}
		writeln((quickPower(2,(min(dis1[n],dis1[n+n])/(10000000)))-1+mod+(min(dis1[n],dis1[n+n])%(10000000)))%mod);
	}	
}

---

## 作者：Tx_Lcy (赞：3)

[题目传送门](https://www.luogu.com.cn/problem/CF1442C)

## 思路

一种比较奇怪的做法。

我们设 $1 \sim u$ 的最短路径是 $w$，则 $w$ 一定能写成 $x+2^y-1$ 的形式，$x$ 表示经过边的数量，$y$ 表示图翻转的次数。

接下来我们考虑如何比较两条最短路径的大小，我们发现 $x$ 不会超过 $m$。

那么，当 $2^y$ 已经远大于 $m$ 的时候，这个值的大小就与 $x$ 几乎无关了（只有当比较的两个 $y$ 相等时才与 $x$ 有关），而这个值的大小与 $x$ 有关，当且仅当 $y \le 18$。

这样一来，我们就可以比较出两条最短路径的大小了。

接下来考虑分层图，直接分层显然是萎的，我们考虑运用刚刚推得的性质：当 $y>18$ 时，两条路径长度的比较就与 $x$ 无关了，换句话说，当 $y>18$ 时，我们只要统一记录一个最小的 $y$ 值即可，$x$ 值不需要去管它了。

这样一来，就做完了，因为所有 $y>18$ 的情况可以压到一个状态 $y=19$ 里。

代码异常好写，简单翻了几页洛谷提交记录，发现没有比我短的。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive
#include<bits/stdc++.h>
using namespace std;
#define int long long
int const N=2e5+10;
int const mod=998244353;
bool vis[N][20][2];
vector< pair<int,int> >a[N];
struct node{int w,x,y,z;}f[N][20][2];
inline int qpow(int a,int b,int t=1){
    for (;b;b>>=1,a=a*a%mod)
        if (b&1) t=t*a%mod;
    return t;
}
bool operator < (node a,node b){
    return (a.y<20 && b.y<20)?
    ((1ll<<a.y)+a.w>(1ll<<b.y)+b.w):
    ((a.y==b.y)?(a.w>b.w):(a.y>b.y));
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0),cout.tie(0);
    int n,m;cin>>n>>m;
    while (m--){
        int u,v;cin>>u>>v;
        a[u].push_back({v,0});
        a[v].push_back({u,1});
    }
    for (int i=1;i<=n;++i)
        for (int j=0;j<20;++j)
            for (int k=0;k<2;++k)
                f[i][j][k]={123582391,0,129477372,0};
    priority_queue<node>q;
    memset(f,0x3f,sizeof(f));
    f[1][0][0]={0,0,0,0};q.push({0,1,0,0});
    while (!q.empty()){
        auto [w,x,y,z]=q.top();q.pop();
        if (x==n){
            cout<<(qpow(2,y)-1+mod+w)%mod<<'\n';
            return 0;
        }
        int s=min(19ll,y);
        if (vis[x][s][z]) continue;
        vis[x][s][z]=1;
        for (auto [v,w]:a[x]){
            int k=y;if (w!=z) ++k;
            if (!(f[v][min(19ll,k)][w]<
                (node){f[x][s][z].w+1,v,k,w})) continue;
            f[v][min(19ll,k)][w]={f[x][s][z].w+1,v,k,w};
            q.push(f[v][min(19ll,k)][w]);
        }
    }
    return 0;
}
```

---

## 作者：fr200110217102 (赞：3)

根据题意，可以很容易地想到建分层图：$0,2,4...$层是原图，$1,3,5...$层是反图。第$k$层到第$k+1$层的相应点之间连$2^k$的边。

但我们有可能会走很多层才能到达$n$号点。一种最简单的情况就是

```plain
200000 199999
2 1
2 3
4 3
4 5
6 5
6 7
...
199998 199999
200000 199999
```

这样每走一步都需要下一层。所以点数会达到$O(n^2)$而且边权也会非常大。

所以暴力建分层图显然是不可取的。但我们发现$2^k$的增长速度非常快，当$k=18$时$2^k$已经大于$n$了。

而这意味着$k\geq 18$时，每下一层所产生的代价都大于在同一层遍历整张图的代价。也就是说此时首要条件是层数最小，其次才是最短路。

因此我们只对前$18$层建分层图跑一遍$SPFA$。如果前$18$层跑不到$n$号点，就按层进行类似于洪水填充的$SPFA$：限定$SPFA$在当前层跑，当跑不动（即队列为空）时就将所有点入队在下一层跑$SPFA$。同时记录的$dis$是不加$2^k$的。

因为边权都是$0/1$所以这样的$SPFA$是线性的。

这样可保证到达$n$号点时的层数最小。输出答案时加上$2^k-1$即可。

时间复杂度为$O(18m)$，空间复杂度$O(18n)$

代码（头文件等省略）

```cpp
const int N=2e5+10,mod=998244353;
int n,m,x,y;
vector<int> e[2][N];
inline void adde(int x,int y,int o){
	e[o][x].push_back(y);
}

typedef pair<int,int> pii;
int dis[19][N];
bool vis[19][N];
queue<pii> q;
int spfa(){
	memset(dis,63,sizeof(dis));
	q.push(pii(0,1));
	dis[0][1]=0;
	while(!q.empty()){
		int u=q.front().second,k=q.front().first;
		q.pop();vis[k][u]=0;
		for(int v:e[k&1][u]){
			if(dis[k][v]>dis[k][u]+1){
				dis[k][v]=dis[k][u]+1;
				if(!vis[k][v])vis[k][v]=1,q.push(pii(k,v));
			}
		}
		if(k<18){
			if(dis[k+1][u]>dis[k][u]+(1<<k)){
				dis[k+1][u]=dis[k][u]+(1<<k);
				if(!vis[k+1][u])vis[k+1][u]=1,q.push(pii(k+1,u));
			}
		}
	}
	int res=1e9+7;
	for(int i=0;i<=18;++i)res=min(res,dis[i][n]);
	return res;
}

queue<int> Q,tmp;
int diss[N];
inline int qbit(int x){
	int res=1,t=2;
	for(;x;x>>=1)x&1?(res=1ll*res*t%mod):1,t=1ll*t*t%mod;
	return res;
}
int main(){
	n=read(),m=read();
	for(int i=1;i<=m;++i){
		x=read(),y=read();
		adde(x,y,0),adde(y,x,1);
	}
	int ans=spfa();
	if(ans<1e9)return enter(ans),0;
	
	memset(diss,63,sizeof(diss));
	diss[1]=0,Q.push(1),tmp.push(1);
	for(int k=0;;++k){
		while(!Q.empty()){
			int u=Q.front();
			Q.pop();
			if(u==n)return enter((qbit(k)-1+diss[u])%mod),0;
			for(int v:e[k&1][u])
				if(diss[v]>diss[u]+1)diss[v]=diss[u]+1,Q.push(v),tmp.push(v);
		}
		while(!tmp.empty())Q.push(tmp.front()),tmp.pop();
	}
}
```

---

## 作者：tommymio (赞：3)

显然可以想到直接分层图最短路，但是 $m\leq 200000$ 的情况下，最劣是 $O(nm)$ 的。考虑优化这种做法：

可以发现当操作次数不超过 $18$ 时，最大单次操作代价在 $n=200000$ 的情况下比遍历全图的代价要小。这个阶段内我们可能通过反转一些边使代价更小。即，就算在第 $k$ 层 $x\to y$ 是可达的，我们也可能通过第 $k+i$ 层从 $x$ 到达 $y$。

但当操作次数超过 $18$ 时，我们发现此时单次操作的代价甚至大于遍历全图的代价！自然在这种情况下，如果在第 $k$ 层 $x\to y$ 可达，就一定会通过第 $k$ 层从 $x$ 到达 $y$。可以得到此时在层与层之间转移的代价大于在图上直接转移的代价，而我们自然希望这个代价尽可能地小，所以令操作次数最小时 $1\to n$ 可达是一定最优的，并且在这个前提下令在图上直接转移的代价之和最小。

那么就有了一个大概的思路，对于 $k\leq 18$ 的部分，直接分层图最短路。如果在 $k\leq 18$ 内无法出解，则求出最小的 $k$ 及在这个前提下在图上转移的最小代价。由于最小的 $k$ 唯一，所以只需枚举这个 $k$ 并判断在第 $k$ 层能否从 $1\to n$ 即可。对于 $k>18$ 的部分具体来说，就是枚举 $k$，对于每一层直接在图上转移，之后将每一个在最短路过程中被更新的点加入下一层的转移。

这样的话，对于 $k\leq 18$ 的部分是 $O(18m)$ 的，$k>18$ 的部分是 $O(m)$ 的，总时间复杂度就是 $O(19m)$ （奇怪的常数增加了

代码就不贴了，非常好写。

---

## 作者：Cure_Wing (赞：2)

[CF1442C Graph Transpositions](https://www.luogu.com.cn/problem/CF1442C)

### 思路

注意到翻转图上的所有有向边的代价是 $2^{k-1}$，这玩意是指数级增长的。当 $k=21$ 的时候已经超过了 $10^6$，而走一条边的代价只有 $1$，总和也不会超过 $2\times10^5$。所以如果我们翻转的次数超过了 $20$ 次，那么我们在 $k$ 的奇偶性相同时，$k$ 越小越好，在 $k$ 相同时才考虑走过的边数 $dis$。对于这种情况，我们定义 $f_{i,0/1}$ 表示走到第 $i$ 点时 $k$ 为偶数/奇数的最小 $k$ 值，在记录 $d_{i,0/1}$ 表示对应状态下走过的最小边数。

但是如果 $k\le20$ 时，$k$ 越小不一定意味着总时间越少，因为它走的边数可能更多超过了 $2^k$。但是 $k$ 只有不到 $20$，我们可以直接跑分层图最短路，定义 $dis_{i,k}$ 表示走到第 $i$ 点时，翻转了 $j$ 次所用的最小时间。

由于边权显然为正，所以跑 Dijkstra 即可。

对于边方向的处理，我们发现边的方向与 $k$ 的奇偶性相关。于是我们对 $k$ 为偶数时存在的边赋 $0$，$k$ 为奇数时存在的边赋 $1$，走到时比较即可。

时间复杂度 $O(m\log m)$，因为每条边只会存在翻转前和翻转后两种情况。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
using std::cin;using std::cout;
constexpr int N=200005,inf=1e9,p=998244353;
int n,m,u,v,t[N][2],dis[N][20],ans=inf,d[N][2];
bool vis[N][20],tag[N][2];
struct A{int v;bool tag;};
struct B{
	int u,t,dis;
	inline bool operator<(const B &a)const{return (1<<t)+dis>(1<<a.t)+a.dis;}
};
struct C{
	int u,t,dis;
	inline bool operator<(const C &a)const{if(t!=a.t) return t>a.t;return dis>a.dis;}
};
std::vector<A>edge[N];
std::priority_queue<B>q;
std::priority_queue<C>w;
inline int qpow(int a,int b,int p,int t=1){for(;b;b>>=1,a=1ll*a*a%p)if(b&1)t=1ll*t*a%p;return t;}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=m;++i){
		cin>>u>>v;
		edge[u].push_back(A{v,0});//k 为偶数时存在的边赋 0
		edge[v].push_back(A{u,1});//k 为奇数时存在的边赋 1
	}
	for(int i=1;i<=n;++i)	
		for(int j=0;j<=19;++j)
			dis[i][j]=inf;
	dis[1][0]=0;q.push(B{1,0,0});
	while(!q.empty()){//k<=19
		B k=q.top();q.pop();
		if(vis[k.u][k.t]) continue;
		vis[k.u][k.t]=1;
		for(A i:edge[k.u]){
			int x=k.t+((k.t&1)!=i.tag),y=(1<<k.t)*((k.t&1)!=i.tag)+1;
			if(x<=19&&dis[k.u][k.t]+y<dis[i.v][x]){
				dis[i.v][x]=dis[k.u][k.t]+y;
				q.push(B{i.v,x,dis[i.v][x]});
			}
		}
	}
	for(int i=0;i<=19;++i) ans=std::min(ans,dis[n][i]);
	if(ans<inf){cout<<ans;return 0;}//有解一定小于 724288=2^19+200000，后面无论如何也不可能小于这个值。
	for(int i=1;i<=n;++i)
		for(int j=0;j<=1;++j)
			t[i][j]=d[i][j]=inf;
	t[1][0]=d[1][0]=0;
	w.push(C{1,0,0});
	while(!w.empty()){//k>=20
		C k=w.top();w.pop();
		if(tag[k.u][k.t&1]) continue;
		tag[k.u][k.t&1]=1;
		for(A i:edge[k.u]){
			bool x=(k.t&1)!=i.tag;
			if(t[k.u][k.t&1]+x<t[i.v][(k.t+x)&1]||t[k.u][k.t&1]+x==t[i.v][(k.t+x)&1]&&d[k.u][k.t&1]+1<d[i.v][(k.t+x)&1]){
				t[i.v][(k.t+x)&1]=t[k.u][k.t&1]+x;
				d[i.v][(k.t+x)&1]=d[k.u][k.t&1]+1;
				w.push(C{i.v,t[i.v][(k.t+x)&1],d[i.v][(k.t+x)&1]});
			}
		}
	}
	if(t[n][0]<t[n][1]) cout<<(qpow(2,t[n][0],p)-1+d[n][0])%p;
	else cout<<(qpow(2,t[n][1],p)-1+d[n][1])%p;
	return 0;
}
```

---

## 作者：crimson000 (赞：2)

本题很容易想到一种简单的做法：建立 $n$ 层图，每层图中间连上边权为 $2^{k-1}$ 的边，每层图要么是正图要么是反图，但是本题中 $n \le 2 \times 10^5$，这样的做法空间复杂度会爆炸，因此考虑别的建图方式。

本题也很容易想出一种贪心的做法：如果能在小于 $\log n$ 次翻转之后就到达终点，那么最优解一定不会翻转超过 $\log n$ 次，因为那样的话越往后翻转的次数就会超过遍历整张图的代价。

因此建立一张 20 层的分层图，每层间连边权为 $2^{k-1}$ 的边，跑一遍 Dijkstra 即可。

但是如果跑到也不一定代表最优解，请看下面这张图：

[![ppYeeDe.png](https://s1.ax1x.com/2023/03/19/ppYeeDe.png)](https://imgse.com/i/ppYeeDe)

只需要反向一下，然后再走过去即可，不需要绕一大圈再到。

因此我们考虑反向超过 $\log n$ 的图和这种情况。

我们建立两层图，每层图间连边的边权认为是正无穷（当然也别爆 long long），然后直接跑 Dijkstra，看看要经过几条正无穷的边（直接除就可以）。

如果经过次数不超过 $\log n$ 次，这种情况不会爆 long long，因此和上面那种情况取最小值即可。

如果超过了，那么第一遍 Dijkstra 一定跑不到终点（因为一共只建了 $\log n$ 层，要走正无穷的反向边都走了超过 $\log n$ 层，所以上面的一定搜不到终点），于是直接取余输出即可。

- 完整代码

```cpp
#define LOCAL
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<long long, int> PII;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    while(ch < '0' || ch > '9')
    {
        if(ch == '-') f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
    {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x * f;
}

const int N = 1e7 + 10, mod = 998244353, M = 10000000;
const ll INF = 0x3f3f3f3f3f3f3f3f;
int a[N], b[N];
int h[N], e[N], ne[N], w[N], idx;
ll dist[N];
bool st[N];
int n, m;

void init()
{
    memset(h, -1, sizeof h);
    memset(st, 0, sizeof st);
    idx = 0;
}

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++;
}

inline int get(int x, int floor)
{
    return x + floor * n;
}

void build1(int floor, int p)
{
    for(int i = 1; i <= m; i ++ )
    {
        if(p == 1) add(get(a[i], floor), get(b[i], floor), 1);
        else add(get(b[i], floor), get(a[i], floor), 1);
    }
}

void build2(int floor, int nxtf, int cost)
{
    for(int i = 1; i <= n; i ++ )
        add(get(i, floor), get(i, nxtf), cost);
}

void dijkstra(int u)
{
    memset(dist, 0x3f, sizeof dist);
    priority_queue<PII, vector<PII>, greater<PII>> heap;
    heap.push({0, u});
    dist[u] = 0;

    while(heap.size())
    {
        auto t = heap.top();
        heap.pop();

        ll distance = t.first;
        int ver = t.second;

        if(st[ver]) continue;
        st[ver] = true;

        for(int i = h[ver]; i != -1; i = ne[i])
        {
            int j = e[i];
            if(dist[j] > distance + w[i])
            {
                dist[j] = distance + w[i];
                heap.push({dist[j], j});
            }
        }
    }
}

ll qmi(ll a, ll k)
{
    ll res = 1;
    while(k)
    {
        if(k & 1) res = res * a % mod;
        a = a * a % mod;
        k >>= 1;
    }
    return res;
}

int main()
{
    #ifdef LOCAL
        freopen("D:\\workspace\\in_and_out\\in.in", "r", stdin);
        freopen("D:\\workspace\\in_and_out\\out.out", "w", stdout);
    #endif

    memset(h, -1, sizeof h);
    n = read(), m = read();
    for(int i = 1; i <= m; i ++ ) 
        a[i] = read(), b[i] = read();

    for(int i = 1; i <= 21; i ++ )
    {
        if(i & 1) build1(i - 1, 1);
        else build1(i - 1, -1);
    }

    for(int i = 0; i <= 19; i ++ )
        build2(i, i + 1, 1 << i);

    dijkstra(1);

    ll ans1 = INF;
    for(int i = 0; i <= 19; i ++ )
        ans1 = min(ans1, dist[get(n, i)]);

    init();
    build1(0, 1);
    build1(1, -1);
    build2(0, 1, M);
    build2(1, 0, M);

    dijkstra(1);

    ll ans2 = 0;
    ll k = min(dist[n], dist[n * 2]);

    if(k / M > 19)
    {
        ans2 = (qmi(2, k / M) + k % M - 1 + mod) % mod;
        cout << ans2 << endl;
    }
    else
    {
        ans2 = ((1ll << (k / M)) + k % M - 1);
        cout << min(ans2, ans1) % mod << endl;
    }
    
    return 0;
}

```

---

## 作者：RyexAwl (赞：2)

首先有一个很显然的分层图建模。令 $dist[i,j]$ 表示从 $1$ 到 $i$ 翻转了恰好 $j$ 次的最短路。至多翻转 $O(n)$ 次。层从 $0\sim n$ 编号。对于编号为偶数的层建正图，编号为奇数的层建反图，边权均为 $1$。$\forall 1\le i\le n$，从第 $j$ 层的 $i$ 连向第 $j+1$ 层的 $i$ 边权 $2^j$ 的边。

但是 $n$ 比较大的情况下边权会非常大，而且复杂度不太行。

这里的一个 intution 是如果翻转的次数很多才能到达 $n$，那么我们一定是在保证最小化翻转次数的前提下再走尽量少的边。

更具体一点，令 $k$ 表示从 $1$ 到达 $n$ 至少翻转多少次，如果 $2^k\ge n-1$，那么一定是要在最小化翻转次数的前提下走尽量少的边。

求翻转次数可以建一个两层的图，一个正图，一个反图，边权均为 $0$。$\forall 1\le i\le n$，在正图和反图之间的 $i$ 连一条无向边，边权为 $1$。求单源最短路即可。

而在最小化翻转次数的前提下走的最少的边的数量也是好求的。考虑求翻转次数建的分层图。对于任意一条从 $1$ 到 $n$ 的路径方案都可以对应到该分层图的一条路径。并且我们可以根据 $k$ 的奇偶性确定最后的终点是在正图中还是在反图中。我们希望求一条从源点到某个点在经过“层间边”最少的前提下经过“层内边”数最少的路径。

即我们考虑的所有路径一定是求最小翻转次数图中的最短路。而只考虑最短路的限制可以使用最短路图进行刻画：建立一个新图，为分层图，一个正图，一个反图，不考虑边权，其边集是求最小翻转次数建立的分层图的子集，对于求最小翻转次数建立的分层图中边权为 $w$ 的一条边 $u\to v$ 其在新图中的充要条件是 $dist[u]+w=dist[v]$，其中 $dist[u]$ 表示在求最小翻转次数的图中从源点到 $u$ 的最短路。接下来为新图中的边赋上合适的边权。“层内边”边权为 $1$，“层间边”边权为 $0$。求单源最短路即可。

如果 $2^k<n-1$，使用最开始提到的分层图建模即可。

复杂度 $O(n\log ^2n)$。


```cpp
#include <bits/stdc++.h>

#define rep(i,l,r) for (int i = l; i <= r; i++)
#define per(i,r,l) for (int i = r; i >= l; i--)
#define fi first
#define se second
#define prt std::cout
#define gin std::cin
#define edl std::endl

namespace wxy{

const int N = 2e5 + 50,mod = 998244353;

int n,m,st[N],ed[N];

namespace Dijkstra {
    int head[N * 20],edge[N * 40],fail[N * 40],w[N * 40],tot;
    bool vis[N * 20];
    int dist[N * 20];
    using PII = std::pair<int,int>;
    inline void add(int x,int y,int z) {
        edge[++ tot] = y,w[tot] = z,fail[tot] = head[x],head[x] = tot;
    }
    inline void Init(){
        memset(head,0,sizeof head); tot = 0;
    }
    inline void dijkstra(int S){
        memset(dist,0x3f,sizeof dist); memset(vis,false,sizeof vis);
        std::priority_queue<PII,std::vector<PII>,std::greater<PII> > q;
        dist[S] = 0; q.push({0,S});
        while (q.size()) {
            int x = q.top().second; q.pop();
            if (vis[x]) continue;
            vis[x] = true; 
            for (int i = head[x]; i; i = fail[i]) {
                int v = edge[i];
                if (dist[v] > dist[x] + w[i]) {
                    dist[v] = dist[x] + w[i];
                    q.push({dist[v],v});
                }
            }
        }
    }
}

namespace solve1 {
    int idx[2][N],power[N],tot;
    inline void Main(){
        power[0] = 1; rep(i,1,n) power[i] = 1ll*power[i-1]*2%mod;
        tot = 0; Dijkstra::Init(); rep(i,1,n) rep(j,0,1) idx[j][i] = ++ tot;
        rep(i,1,m) rep(j,0,1) {
            if (j & 1) {
                Dijkstra::add(idx[j][ed[i]],idx[j][st[i]],0);
            } else {
                Dijkstra::add(idx[j][st[i]],idx[j][ed[i]],0);
            }
        }
        rep(i,1,n) {
            Dijkstra::add(idx[0][i],idx[1][i],1);
            Dijkstra::add(idx[1][i],idx[0][i],1);
        }
        Dijkstra::dijkstra(idx[0][1]); int k = std::min(Dijkstra::dist[idx[0][n]],Dijkstra::dist[idx[1][n]]);
        int ans = 0; rep(i,0,k-1) ans = (1ll*ans+power[i]) % mod;
        Dijkstra::Init(); 
        rep(i,1,m) rep(j,0,1) {
            if (j & 1) {
                if (Dijkstra::dist[idx[j][st[i]]] == Dijkstra::dist[idx[j][ed[i]]]) {
                    Dijkstra::add(idx[j][ed[i]],idx[j][st[i]],1);
                }
            } else {
                if (Dijkstra::dist[idx[j][st[i]]] == Dijkstra::dist[idx[j][ed[i]]]) {
                    Dijkstra::add(idx[j][st[i]],idx[j][ed[i]],1);
                }
            }
        } 
        rep(i,1,n) {
            if (Dijkstra::dist[idx[1][i]] == Dijkstra::dist[idx[0][i]] + 1)
                Dijkstra::add(idx[0][i],idx[1][i],0);
            if (Dijkstra::dist[idx[0][i]] == Dijkstra::dist[idx[1][i]] + 1)
                Dijkstra::add(idx[1][i],idx[0][i],0);
        } Dijkstra::dijkstra(idx[0][1]);
        if (k & 1) ans = (1ll*ans+Dijkstra::dist[idx[1][n]]) % mod;
        else ans = (1ll*ans+Dijkstra::dist[idx[0][n]]) % mod;
        prt << ans;
    }   
}

namespace solve2 {
    int idx[20][N],tot;
    inline void Main(){
        tot = 0; Dijkstra::Init(); rep(i,1,n) rep(j,0,19) idx[j][i] = ++ tot;
        rep(i,1,m) rep(j,0,19) {
            if (j & 1) {
                Dijkstra::add(idx[j][ed[i]],idx[j][st[i]],1);
            } else {
                Dijkstra::add(idx[j][st[i]],idx[j][ed[i]],1);
            }
        }
        rep(i,1,n) rep(j,0,18) Dijkstra::add(idx[j][i],idx[j+1][i],1<<j);
        Dijkstra::dijkstra(idx[0][1]); 
        int ans = 0x3f3f3f3f; rep(j,0,19) ans = std::min(ans,Dijkstra::dist[idx[j][n]]);
        if (ans != 0x3f3f3f3f) printf("%d",ans);
        else solve1::Main();
    }
}

inline void main(){
    #ifndef ONLINE_JUDGE
        freopen("in.in","r",stdin);
        freopen("out.out","w",stdout);
    #endif
    scanf("%d%d",&n,&m); rep(i,1,m) scanf("%d%d",&st[i],&ed[i]);
    solve2::Main();
}

}signed main(){wxy::main(); return 0;}
```

---

## 作者：Priestess_SLG (赞：0)

很厉害的题。首先套路的发现 $f(x)=2^x$ 这个函数增长速度十分的快，在 $x\approx 20$ 的时候代价就超过了直接遍历整张图。因此考虑建 $20$ 层的分层图，若此时能跑到最短路，则可以证明答案一定最优。

还有一种可能就是说 $20$ 层走不到最短路，但是最短路是肯定存在的。因此考虑换一个方式建图。建立两层的分层图，第一层为奇数次，第二层为偶数次。之间的边边权为 $2\times 10^9$，跑一遍最短路，就能得到翻转整张图的次数。于是这道题就做完了。

```cpp
#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define eb emplace_back
#define int long long
using namespace std;
const int N=200100,mod=998244353,inf=mod+1;
int n,m,dis[N*22];
vector<pair<int,int>>z[N*22];
pair<int,int>ed[N];
struct qwq{
    int u,dis;
    bool operator<(const qwq&r)const{
        return dis>r.dis;
    }
};
int ksm(int a,int b,int c){
    if(!b)return 1;
    int ans=ksm(a,b>>1,c);
    ans=ans*ans%c;
    if(b&1)ans=ans*a%c;
    return ans;
}
signed main(){
    cin>>n>>m;
    for(int i=0;i<m;++i){
        int x,y;cin>>x>>y;
        ed[i]={x,y};
        for(int j=0;j<20;++j){
            if(~j&1)
                z[j*n+x].eb(j*n+y,1);
            else
                z[j*n+y].eb(j*n+x,1);
        }
    }
    for(int i=1;i<=n;++i)
        for(int j=0;j<19;++j)
            z[j*n+i].eb((j+1)*n+i,1ll<<j);
    priority_queue<qwq>q;
    memset(dis,0x3f,sizeof dis);
    q.push({1,dis[1]=0});
    while(q.size()){
        auto [x,d]=q.top();q.pop();
        if(dis[x]>=d){
            for(auto &[g,w]:z[x])
            if(dis[g]>dis[x]+w)
            q.push({g,dis[g]=dis[x]+w});
        }
    }
    int mi=1e18;
    for(int i=0;i<20;++i)
        mi=min(mi,dis[i*n+n]);
    if(mi<1e18)cout<<mi<<'\n';
    else{
        for(int i=0;i<N*20;++i)z[i].clear();
        for(int i=0;i<m;++i){
            auto [x,y]=ed[i];
            for(int j=0;j<2;++j){
                if(~j&1)z[j*n+x].eb(j*n+y,1);
                else z[j*n+y].eb(j*n+x,1);
            }
        }
        for(int i=1;i<=n;++i)
            for(int j=0;j<2;++j){
                int k=j^1;
                z[j*n+i].eb(k*n+i,inf);
                z[k*n+i].eb(j*n+i,inf);
            }
        memset(dis,0x3f,sizeof dis);
        q.push({1,dis[1]=0});
        while(q.size()){
            auto [x,d]=q.top();q.pop();
            if(dis[x]>=d){
                for(auto &[g,w]:z[x])
                if(dis[g]>dis[x]+w)
                q.push({g,dis[g]=dis[x]+w});
            }
        }
        int x=min(dis[n],dis[n+n]);
        int lu=x/inf,ki=x%inf;
        cout<<(ki+ksm(2,lu,mod)+mod-1)%mod<<'\n';
    }
}
```

---

## 作者：Tachibana_Kimika (赞：0)

首先看到这个题我们肯定会去想分层图，每层要么是正的要么是反的，然后往上连边，权值就是 $2^{k-1}$，但是看到 $n,m\le 2\times 10^5$ 的数据范围，再一想，只要构造一个一正一反的链就能卡满翻转 $m$ 次，只能作罢。

然后我们发现翻转太贵了，所以要少翻转几次，那么把翻转的权值设为无穷大，然后只需要建一正一反两层，然后循环着跑就行了，最后翻转了多少次就直接答案除以无穷大即可（程序设计的时候可以把无穷大当成 $10^9$）结果一看，第一个样例都过不去，因为前几次翻转还是很便宜的。

考虑结合以上两种做法，在前 $\log m$ 次翻转中，我们暴力建分层图，如果跑不到终点，那么一定需要超过 $\log m$ 次翻转，用第二种方法贪心找翻转次数最少的解法即可。

为什么是 $\log m$？因为 $2^{\log_2 m}=m$，所以超过 $\log m$ 次翻转，比走完一整张图还劣。

设 $n,m$ 同阶，复杂度 $O(n\log^2 n)$，常数虽大，三秒足矣。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;
const int p=998244353;
int _abs(int x){if(x<0) return -x; return x;}

int qpow(int a,int index){
	int ans=1;
	while(index){
		if(index&1) ans=ans*a%p;
		a=a*a%p; index>>=1;
	}
	return ans;
} 

struct node{
	int to,nxt,w;
}edge[N*40]; int head[N*20],cnt;
void add(int u,int v,int w){
	//cout<<u<<" "<<v<<" "<<w<<"\n";
	edge[++cnt].to=v;
	edge[cnt].w=w;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
}

pair<int,int>E[N]; int res;

int dis[N*20],vis[N*20];
void dijkstra(int s){
	memset(dis,0x3f,sizeof dis);
	memset(vis,0,sizeof vis);
	priority_queue<pair<int,int>>q;
	dis[s]=0; q.push({0,s});
	while(!q.empty()){
		int u=q.top().second; q.pop();
		if(vis[u]) continue; vis[u]=1; 
		for(int i=head[u];i;i=edge[i].nxt){
			int v=edge[i].to;
			if(dis[v]>dis[u]+edge[i].w){
				dis[v]=dis[u]+edge[i].w; q.push({-dis[v],v});
			}
		}
	}
}

inline void fake_main(){
	int n,m; cin>>n>>m;
	for(int i=1;i<=m;i++){
		int u,v; cin>>u>>v; E[++res]={u,v}; int base=1;
		for(int j=0;j<20;j++,base*=2){
			if(j%2==0){
				add(u+j*n,v+j*n,1);
			}
			else{
				add(v+j*n,u+j*n,1);
			}
		}
	} 
	for(int i=1;i<=n;i++){
		int base=1;
		for(int j=0;j<19;j++,base*=2){
			add(i+j*n,i+(j+1)*n,base);
		}
	}//先暴力建20层
	dijkstra(1);
	int ans=dis[0];
	for(int j=0;j<20;j++) ans=min(ans,dis[n+j*n]);
	if(ans!=dis[0]){
		cout<<ans<<"\n"; return;
	}//如果能跑，就输出答案
	
	memset(head,0,sizeof head); cnt=0;
	for(int i=1;i<=m;i++){
		int u=E[i].first; int v=E[i].second;
		add(u,v,1); add(v+n,u+n,1);
	}//只建两层，因为可以循环着跑
	for(int i=1;i<=n;i++){
		add(i,i+n,1e9); add(i+n,i,1e9);
	}
	dijkstra(1);
	ans=min(dis[n],dis[n+n]);
  
	int tmp=ans/((int)1e9); ans=(ans%((int)1e9));
	//贪心找最少需要几次翻转
	cout<<(ans+qpow(2,tmp)+p-1)%p<<"\n";//快速幂求解即可

}

signed main(){
	//ios::sync_with_stdio(false);
	int t; t=1;
	while(t--) fake_main();
}

```

---

## 作者：XL4453 (赞：0)

### $\text{Difficulty : 2400}$
---
### 解题思路：

使用翻转的情况可以分为两种，一种情况下在只经过较小次数的翻转时，有可能能够让一些本来距离很长的点之间可以快速到达，达到缩小距离的目的。另一种情况下则是过不去，必须要翻转，这种情况下的翻转次数可能会非常多。

一种朴素的思想是建立一个分层图，奇数层建立正向边，偶数层则建立反向边，相邻两层的相同点之间有一条有向边，表示进行翻转，这种建图的层数不能太多。

可以发现，如果使用翻转的次数超过了 $18$ 次，一次翻转的代价就超过了遍历整个图的代价，所以一定是用于走过不能走过的边的。

---
由此思路就比较清晰了。

先建立一个 $19$ 层的分层图，跑一遍最短路观察是否能够到达某一层的目标节点，如果能够到达，则这个最小代价就是答案。

否则建立一个新的图，这个图只有两层，两层之间的转移代价为一个相对于遍历图代价的无穷大，直接跑最短路，求出最小代价后将无穷大更换成原来的 $2^k$ 并取模。

---
我在写代码的时候额外处理了一下两者边界的情况，防止出现恰好在边界上而不好判断的情况。

另外注意额外边的数量，不要把数组开小。

---
### 代码：
```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define int long long
const int MOD=998244353;
const int MAXN=20*200005;
int n,m,u[MAXN],v[MAXN],head[MAXN],nxt[2*MAXN],num[2*MAXN],w[2*MAXN],f[MAXN],tot,vis[MAXN],N,ans,ans_2;
priority_queue <pair<int,int> > p; 
int pow(int a,int b){
	int ans=1;
	while(b){
		if(b&1)ans=(ans*a)%MOD;
		a=(a*a)%MOD;
		b=b>>1;
	}
	return ans;
}
void init(){
	memset(head,0,sizeof(head));
	memset(nxt,0,sizeof(nxt));
	memset(num,0,sizeof(num));
	memset(w,0,sizeof(w));
	tot=0;
}
void add(int x,int y,int z){
	nxt[++tot]=head[x];
	head[x]=tot;
	num[tot]=y;
	w[tot]=z;
}
void build_1(int t,int p){//建立普通边
	//     层数  正反
	for(int i=1;i<=m;i++){
		if(p==1)add(t*n+u[i],t*n+v[i],1);
		if(p==-1)add(t*n+v[i],t*n+u[i],1);
	}
}
void build_2(int t,int w,int u){//层与层之间的边 
	for(int i=1;i<=n;i++)
	add(t*n+i,(t+u)*n+i,w);
}
void Dij(int s){
	while(!p.empty())p.pop();
	memset(vis,0,sizeof(vis));
	p.push(make_pair(0,s));
	for(int i=0;i<=N;i++)f[i]=1e13;
	f[s]=0;
	while(!p.empty()){
		int now=p.top().second,d=-p.top().first;p.pop();
		if(f[now]!=d)continue;
		vis[now]=1;
		for(int i=head[now];i;i=nxt[i]){
			if(f[now]+w[i]<f[num[i]]){
				f[num[i]]=f[now]+w[i];
				p.push(make_pair(-f[num[i]],num[i]));
			}
		}
	}
}
signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++)
	scanf("%lld%lld",&u[i],&v[i]);
	for(int i=1;i<=20;i++){
		if(i%2==1)build_1(i-1,1);
		else build_1(i-1,-1);
	}
	for(int i=1;i<=18;i++)
	build_2((i-1),(1<<(i-1)),1);
	N=20*n;Dij(1);ans=1e13;
	for(int i=1;i<=20;i++)
	ans=min(ans,f[i*n]);
	
	init();N=3*n;
	build_1(0,1);build_1(1,-1);
	build_2(0,10000000,1);build_2(1,10000000,-1);
	Dij(1);ans_2=min(f[n],f[2*n]);
	
	if(ans_2/10000000>19){
		ans_2=(pow(2,ans_2/10000000)+ans_2%10000000-1+MOD)%MOD;
		printf("%lld",ans_2);
	}
	else{
		ans_2=(1ll<<(ans_2/10000000))-1ll+(ans_2%10000000);
		printf("%lld",min(ans,ans_2)%MOD);
	}
	return 0;
}
```



---

## 作者：happybob (赞：0)

求出 $f_u$ 表示 $1$ 到 $u$ 的最少翻转次数，这一部分容易使用最短路处理。具体来说可以把每个状态拆成 $g_{u,0/1}$ 表示 $1$ 到 $u$，目前翻转次数为偶数或者奇数的最少翻转次数，跑最短路即可。

然后考虑每个点 $u$ 在最终最短路下的翻转次数，显然必然不会超过 $f_u + O(\log n)$，这里直接取 $f_u+20$，那么每个点的翻转次数为 $[f_u,f_u+20]$，直接跑分层图最短路即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
using namespace std;

const int N = 2e5 + 5;

int n, m;
using ll = long long;
const ll MOD = 998244353ll;

vector<pair<int, int>> G[N];
ll powe[N];
int f[N][2]; // 1->u：最小翻转次数
int f2[N][21];

struct Node2
{
	int u, x, d;
	Node2() = default;
	Node2(int u, int x, int d) : u(u), x(x), d(d) {}
	bool operator<(const Node2& x) const
	{
		return d > x.d;
	}
};

bool vis[N][2];
bool vis2[N][21];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	powe[0] = 1ll;
	for (int i = 1; i < N; i++) powe[i] = powe[i - 1] * 2ll % MOD;
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		G[u].emplace_back(make_pair(v, 0));
		G[v].emplace_back(make_pair(u, 1));
	}
	memset(f, 0x3f, sizeof f);
	auto dijkstra = [&]()
		{
			priority_queue<Node2> q;
			q.push(Node2(1, 0, 0));
			q.push(Node2(1, 1, 1));
			f[1][0] = 0;
			f[1][1] = 1;
			while (q.size())
			{
				auto [u, x, d] = q.top();
				q.pop();
				if (vis[u][x]) continue;
				vis[u][x] = 1;
				for (auto& [j, w] : G[u])
				{
					if (f[j][w] > f[u][x] + (x != w))
					{
						f[j][w] = f[u][x] + (x != w);
						q.push(Node2(j, w, f[j][w]));
					}
				}
			}
		};
	auto dijkstra2 = [&]
		{
			memset(f2, 0x3f, sizeof f2);
			priority_queue<Node2> q;
			for (int i = 0; i <= 20; i++) f2[1][i] = 0, q.push(Node2(1, i, 0));
			while (q.size())
			{
				auto [u, x, d] = q.top();
				q.pop();
				if (vis2[u][x]) continue;
				vis2[u][x] = 1;
				// 到u，翻转min(f[u][0],f[u][1])+x次
				int now = min(f[u][0], f[u][1]) + x;
				for (auto& [j, w] : G[u])
				{
					int nj = min(f[u][0], f[u][1]) + x + ((now & 1) != w) - min(f[j][0], f[j][1]);
					if (nj >= 0 && nj <= 20 && f2[j][nj] > f2[u][x] + 1)
					{
						f2[j][nj] = f2[u][x] + 1;
						q.push(Node2(j, nj, f2[j][nj]));
					}
				}
			}
		};
	dijkstra();
	dijkstra2();
	ll ans = (ll)1e18;
	int ri = 0;
	for (int i = 1; i <= 20; i++)
	{
		int k = min(f[n][0], f[n][1]) + i;
		ll cz = powe[k - 1];
		if (k - 1 <= 20 && f2[n][ri] - f2[n][i] > cz)
		{
			ri = i;
		}
	}
	int k = min(f[n][0], f[n][1]) + ri;
	ans = powe[k] - 1ll + f2[n][ri];
	cout << ans << "\n";
	return 0;
}
```

---

