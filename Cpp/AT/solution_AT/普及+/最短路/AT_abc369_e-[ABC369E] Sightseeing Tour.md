# [ABC369E] Sightseeing Tour

## 题目描述

#### 题目大意
给你一张 $N$ 个点，$M$ 条边的无向图（可能有重边）。第 $i$ 条边的端点是 $U_i$ 和 $V_i$，长度是 $T_i$。

给定 $Q$ 个询问，每个询问会给出 $K$ 条边。对于每个询问，请求出经过这 $K$ 条边（一定经过这 $K$ 条边，但是也可以经过其他的边）的 $1$ 到 $N$ 的最短路的长度。

## 说明/提示

- $2 \leq N \leq 400$
- $N-1 \leq M \leq 2 \times 10^5$
- $1 \leq U_i < V_i \leq N$
- $1 \leq T_i \leq 10^9$
- $1 \leq Q \leq 3000$
- $1 \leq K_i \leq 5$
- $1 \leq B_{i,1} < B_{i,2} < \cdots < B_{i,K_i} \leq M$
- 所有输入值都是整数。
- 这个图是连通图。

translate by @wujiawei36

## 样例 #1

### 输入

```
3 5
1 2 10
1 3 20
1 3 30
2 3 15
2 3 25
2
1
1
2
3 5```

### 输出

```
25
70```

## 样例 #2

### 输入

```
6 6
1 5 1
2 5 1
2 4 1
3 4 1
3 6 1
1 6 1
2
5
1 2 3 4 5
1
5```

### 输出

```
5
3```

## 样例 #3

### 输入

```
5 5
1 2 1000000000
2 3 1000000000
3 4 1000000000
4 5 1000000000
1 5 1000000000
1
1
3```

### 输出

```
4000000000```

# 题解

## 作者：Little_Cabbage (赞：7)

# 解题思路

纯粹的暴力题，~~赛时脑子抽了没写出来~~。

我们发现 $n$ 和 $K_i$ 的范围都很小，所以考虑暴力模拟。

先用 `Floyd` 算法求出任意两点之间的最短距离，$i$ 与 $j$ 的最短距离存放在 $a_{i, j}$ 里。

接下来，再枚举每一座桥的方向，里面再枚举经过每一座桥的顺序。

时间复杂度：$O(q\times 2^{K_i}\times K_i!)$

# 核心代码

```cpp
Floyd();
while (q -- ) {
	int k;
	cin >> k;
	rep(i, 0, k - 1) {
		idx[i] = i;
		cin >> b[i];
	}
	int res = inf;
	rep(i, 0, (1 << k) - 1) do{//枚举桥的方向，0表示正向，1表示反向
		int s = 1, now = 0;
		rep(j, 0, k - 1) {
			int u = e[b[idx[j]]].u, v = e[b[idx[j]]].v;
			if (i >> j & 1) swap(u, v);//判读第j座桥是否要反转
			now += a[s][u] + e[b[idx[j]]].w;
			s = v;
		}
		res = min(res, now + a[s][n]);//更新答案
	} while (next_permutation(idx, idx + k));//下一个顺序
	cout << res << endl;
}
```

---

## 作者：I_will_AKIOI (赞：3)

首先发现每次询问给定的边不超过 $5$ 条，这或许是一个突破口。这道题我首先想到了分层图，用一个二进制数表示这 $5$ 条边的经过情况，然后跑最短路，由于他是个稠密图，可以使用未优化的迪杰斯特拉算法，复杂度为 $O(q\cdot n^2 \cdot 2^k)$，会喜提 TLE。

由于询问次数较多，因此考虑更快地计算询问。可以对每个询问的边枚举一下全排列，也就是这几条边经过的先后顺序，由于边的方向不固定，因此我们还需要枚举一下方向。然后预处理一下全源最短路，接着依次访问这几条边的端点，最后答案取最小值。时间复杂度为 $O(n^3+q\cdot k! \cdot 2^k \cdot k)$，可以通过。

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 405
#define M 200005
#pragma GCC optimize("O3")
using namespace std;
int n,m,q,x[M],y[M],z[M],a[N][N];
signed main()
{
  ios::sync_with_stdio(0);
  cin>>n>>m;
  for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=1e18;
  for(int i=1;i<=m;i++)
  {
    cin>>x[i]>>y[i]>>z[i];
    a[x[i]][y[i]]=a[y[i]][x[i]]=min(a[x[i]][y[i]],z[i]);
  }
  for(int i=1;i<=n;i++) a[i][i]=0;
  for(int k=1;k<=n;k++) for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
  //全源最短路
  cin>>q;
  while(q--)
  {
    int len,v[5],ans=1e18;
    cin>>len;
    for(int i=0;i<len;i++) cin>>v[i];
    sort(v,v+len);
    do//枚举访问边的顺序
    {
      for(int i=0;i<(1<<len);i++)//枚举边的方向，二进制下的01表示是否正着走边
      {
        int sum=0,last=1;
        for(int j=0;j<len;j++)//模拟走边的过程
        {
          if(i&(1<<j))
          {
            sum+=a[last][x[v[j]]]+z[v[j]];
            last=y[v[j]];
          }
          else
          {
            sum+=a[last][y[v[j]]]+z[v[j]];
            last=x[v[j]];
          }
        }
        ans=min(ans,sum+a[last][n]);
      }
    }
    while(next_permutation(v,v+len));
    cout<<ans<<"\n";
  }
  return 0;
}
```

---

## 作者：卡卡卡卡卡卡 (赞：3)

## 题解
看到 $N\leq 400$ 便考虑 ``floyd`` 来求全源最短路，求出每两个点之间的最短路。

但我们发现会有重边，便考虑取两点的最小边，取最小值。

接着是必须经过 $k$ 条边的选择，乍一看没啥性质但观察到 $k \leq 5$ ，考虑暴力枚举走边的顺序，最后算下来只有 $2^kk!$，可以通过。

时间复杂度：$\mathcal O(2^kk! + N^3)$。
```cpp
#include<bits/stdc++.h>
using namespace std;
long long a[505][505],k,p[50005],ans=1e18,bz[500005];
long long n,m;
struct edge
{
    long long u,v,w;
}e[500005];
void dfs(long long t,long long sum,long long now)
{
    if(t==k+1)
    {
        ans=min(ans,sum+a[now][n]);
        return ;
    }
    for(int i=1;i<=k;i++)
    {
        if(bz[i]==0)
        {
            bz[i]=1;
            dfs(t+1,sum+a[now][e[p[i]].u]+e[p[i]].w,e[p[i]].v);
            dfs(t+1,sum+a[now][e[p[i]].v]+e[p[i]].w,e[p[i]].u);
            bz[i]=0;
        }
    }
}
int main()
{
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            a[i][j]=1e18;
        }
    for(int i=1;i<=n;i++)a[i][i]=0;
    for(int i=1;i<=m;i++)
    {
        cin>>e[i].u>>e[i].v>>e[i].w,a[e[i].u][e[i].v]=min(e[i].w,a[e[i].u][e[i].v]),a[e[i].v][e[i].u]=min(a[e[i].v][e[i].u],e[i].w);
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                if(a[i][j]>(a[i][k]+a[k][j])) a[i][j]=a[i][k]+a[k][j];
            }
    long long q;
    cin>>q;
    while(q--)
    {
        ans=1e18;
        cin>>k;
        for(int i=1;i<=k;i++)cin>>p[i];
        dfs(1,0,1);
        cout<<ans<<'\n';
    }
}
```

---

## 作者：Ivan422 (赞：3)

题意：给出一张可能有重边的无向连通图，每一次查询给出固定要通过的边，求必须要通过这些边时点 $1$ 到点 $n$ 的最短距离。

思路：首先看到数据范围 $n\leq 400$，考虑弗洛伊德求多源最短路。对于有重边的情况，对边权取最小值即可。接着处理这些必须要经过的边，会发现边数 $k\leq 5$，考虑直接全排列枚举。对于每一个访问顺序，你可以选择两端访问，我这里怕时间爆掉，考虑了一个动态规划：$g_{i,j}$ 表示第 $i$ 个访问的边用 $j$ 头进入并走完这条边所花费的最短代价。由于走完了这条边，所以直接加边权，不用考虑重边的问题。具体状态转移按照题意即可，看代码。

代码：[赛时提交记录](https://atcoder.jp/contests/abc369/submissions/57315570)。

---

## 作者：_determination_ (赞：2)

注意到 $k\leq 5$，所以我们可以直接枚举通过边的方向和顺序。使用 Floyd 算法可以求出所有点之间的最短路径，从而计算答案。复杂度 $O(q2^k k!)$。

[Link](https://atcoder.jp/contests/abc369/submissions/57324651) 跑的飞快。

---

## 作者：DengDuck (赞：2)

我怎么会被这种唐诗题硬控 40 分钟......

先用 Floyd 求出最短路。

然后考虑枚举我们访问这些边的顺序和我们是从哪个方向上的这条边，这样我们就能确定这个条件下的最短路径是怎么走的。

这样我们就把路径拆成了几部分，对于每部分直接累加两点之间的最短路统计答案，最后求一个答案的最小值就做完了。

```cpp
#include<bits/stdc++.h>
#define LL long long
#define pLL pair<LL,LL>
#define Fi first
#define Se second
using namespace std;
const int N=405;
const int M=2e5+5;
int n,m,Q,K,B[M],P[M][2];
LL A[N][N],W[M];
int main()
{
	memset(A,27,sizeof(A));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)A[i][i]=0;
	for(int i=1;i<=m;i++)
	{
		LL u,v;
		scanf("%lld%lld%lld",&u,&v,&W[i]);
		P[i][0]=u,P[i][1]=v;
		A[u][v]=A[v][u]=min(A[u][v],W[i]);
	}
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)A[i][j]=min(A[i][j],A[i][k]+A[k][j]);
	scanf("%d",&Q);
	while(Q--)
	{
		scanf("%d",&K);
		for(int i=0;i<K;i++)scanf("%d",&B[i]);	
		LL Ans=1e15;
		do
		{		
			for(int i=0;i<(1<<K);i++)
			{
				LL S=0,L=1;
				for(int j=0;j<K;j++)
				{
					S+=A[L][P[B[j]][(i>>j)&1]]+W[B[j]];
					L=P[B[j]][((i>>j)&1)^1];
				}				
				S+=A[L][n],Ans=min(Ans,S);
			}
		}while(next_permutation(B,B+K));
		printf("%lld\n",Ans);
	}
}
```

---

## 作者：sakura_21 (赞：1)

## 题目描述
给定 $n$ 个点和 $m$ 条无向边，每条边连接点 $u_i$ 和 $v_i$，边权为 $t_i$，可能有重边，无自环。$q$ 次询问，每次给定 $k$ 条必须至少走一次的边，求从点 $1$ 到点 $n$ 需要的最少时间。

## 思路分析
分析题目，无向图中要求最少时间，~~最短路走起！~~

但是同时我们发现一个问题：最短路算法走的一定是边权最小的边，所以给定的边不一定在最短路中出现。

那么，我们就可以先从 $1$ 开始，走一段最短路，再走给定的路，然后继续走最短路和给定的路，直至到达点 $n$。

对于最短路，从多个点走向多个点，即**多源最短路**问题，使用 Floyd 算法就可以~~优雅地~~解决。

如何解决最短路中间穿插的给定边呢？

![](https://cdn.luogu.com.cn/upload/image_hosting/wpweydkz.png)

例如上图， $1$ 为开头， $6$ 为结尾，设红色边为给定边，求 $1-6$ 经过红色边的最短路。我们可以发现，从 $1$ 到 $2$ 走最短路,走第一条红边，然后走 $3$ 到 $4$ 的最短路，然后走第二条红边，最后走 $5$ 到 $6$ 的最短路，得到最短路。

大胆猜想：从开头以最短路走到要求边的一个点，再从另一点以最短路走向另一要求边的一点，重复到所有要求边都走完，最后从最后一条要求边的一点走到点 $n$，就求得了整条路的最短路径。

蒟蒻提问：那我应该先走哪一条要求边呢？

这就不得不提我们的入门题全排列了！

把每一条要求边进行全排列 （dfs），然后对于每一个全排列进行求答案，比较大小，挑最小的输出。

~~完结撒花！~~ 怎么可能 qwq 。

观察每一条边，都有两个端点，那应该先走哪个端点呐 TnT。既然不知道，那就开始枚举吧！每次 dfs 时，走左端点的计算一次，走右端点的计算一次，就可以不重不漏地算出每一种情况。

所有情况都讨论完了，那么，上代码！

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+100;
int n,m,q,k;
int head[N];
struct p{
	int data,to,nxt,u;
}edge[N];
int cnt;
void add(int u,int v,int w)
{
	edge[++cnt].to=v;
	edge[cnt].nxt=head[u];
	edge[cnt].data=w;
	edge[cnt].u=u;
	head[u]=cnt;
}
int b[N],ans[N];
int jl[1010][1010];
int vis[N],minn=LLONG_MAX;

int flag[1010][1010];
void floyd()
{
	for (int i=1;i<=n;i++)
	{
		jl[i][i]=0;
	}
	for (int i=1;i<=n;i++)//中转点
	{
		for (int j=1;j<=n;j++)//左边的点
		{
			for (int l=1;l<=n;l++)
			{
				if (jl[j][l]>jl[j][i]+jl[i][l])
					jl[j][l]=jl[j][i]+jl[i][l];
			}
		 } 
	}
}
int s;//计算总和 
void dfs(int x,int pos)
{
	if (x==k+1)
	{
		minn=min(minn,s+jl[pos][n]);
		return ;
	}
	for (int i=1;i<=k;i++)
	{
		if (vis[b[i]]==0)
		{
			vis[b[i]]=1;
			s+=jl[pos][edge[b[i]*2-1].u]+edge[b[i]*2-1].data;//分别计算每一种情况 
			dfs(x+1,edge[b[i]*2-1].to);
			s-=jl[pos][edge[b[i]*2-1].u]+edge[b[i]*2-1].data;//回溯 
			s+=jl[pos][edge[b[i]*2-1].to]+edge[b[i]*2-1].data;
			dfs(x+1,edge[b[i]*2-1].u);
			s-=jl[pos][edge[b[i]*2-1].to]+edge[b[i]*2-1].data;
			vis[b[i]]=0;
		}
	}
}
inline void Solve()
{
	minn=LLONG_MAX;//要看数据范围！！！ 
	cin>>k;
	s=0;
	memset(vis,0,sizeof vis);
	for (int i=1;i<=k;i++)
	{
		cin>>b[i];
	}
	dfs(1,1);
	cout<<minn<<endl;
	return ;
}
signed main()
{
	memset(jl,0x3f,sizeof jl);
	cin>>n>>m;
	for (int i=1;i<=m;i++)
	{
		int a,b,val;
		cin>>a>>b>>val;
		jl[a][b]=min(jl[a][b],val);
		jl[b][a]=min(jl[b][a],val);
		add(a,b,val);add(b,a,val);
	}
	floyd();
	cin>>q;
	while(q--)
	{
		Solve();
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：1)

[**或许更好的阅读体验。**](https://www.cnblogs.com/rgw2010/p/18391497)

### 题意：

给定一个 $n$ 个节点的无向图，共 $q$ 次询问，每次给定 $k$ 个必须经过的边，问从 $1 \sim n$ 的最短路径是多少。

$1 \le n \le 500,1 \le q \le 3000,1 \le k \le 5$。

### 思路：

考虑先求出任意两点的最短路径 $dis_{i,j}$，因为 $n \le 500$，可以使用 Floyd 算法 $n^3$ 跑出。

然后对于每组询问，必须要经过编号为 $a_1,a_2,a_3,\cdots,a_k$ 的桥，定义编号为 $i$ 的桥为 $(u_i,v_i,w_i)$。

同时注意到 $k \le 5$ 非常小，考虑全排列出依次经过哪些桥，同时爆搜是先到达这个桥的左端还是右端即可。

时间复杂度为 $O(N^3 + QK!2^K)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it=l;it!=r;it++) (*it)=x
#define Full(a) memset(a,0,sizeof(a))
#define open(s1,s2) freopen(s1,"r",stdin),freopen(s2,"w",stdout);
#define For(i,l,r) for(int i=l;i<=r;i++)
#define _For(i,l,r) for(int i=r;i>=l;i--)
using namespace std;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const ll N=505,M=2e5+10;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while(c<'0'||c>'9'){
        if(c=='-')
          f=-1;
        c=getchar();
    }
    while(c>='0'&&c<='9'){
        x=(x<<1)+(x<<3)+(c^48);
        c=getchar();
    }
    return x*f;
}
inline void write(ll x){
	if(x<0){
		putchar('-');
		x=-x;
	}
	if(x>9)
	  write(x/10);
	putchar(x%10+'0');
}
ll n,m,q,k,x,y,w,ans;
ll a[N],p[N],A[M],B[M],W[M];
ll dis[N][N];
void dfs(ll pos,ll pre,ll sum){
	if(sum>ans)
	  return ;
	if(pos==k+1){
		ans=min(ans,sum+dis[pre][n]);
		return ;
	}
	dfs(pos+1,A[a[p[pos]]],sum+dis[pre][B[a[p[pos]]]]+W[a[p[pos]]]);
	dfs(pos+1,B[a[p[pos]]],sum+dis[pre][A[a[p[pos]]]]+W[a[p[pos]]]);
}
int main(){
	n=read(),m=read();
	For(i,1,n){
		For(j,1,n){
			if(i==j)
			  continue;
			dis[i][j]=1e18;
		}
	}
	For(i,1,m){
		x=read(),y=read(),w=read();
		dis[x][y]=min(dis[x][y],w);
		dis[y][x]=min(dis[y][x],w);
		A[i]=x,B[i]=y,W[i]=w;
	}
	for(int k=1;k<=n;k++)
	  for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		  dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	q=read();
	while(q--){
		ans=1e18;
		k=read();
		For(i,1,k){
			a[i]=read();
			p[i]=i;
		}
		while(1){
			dfs(1,1,0);
			if(!next_permutation(p+1,p+k+1))
			  break;	
		}
		write(ans);
		putchar('\n');
	}
	return 0;
}

```

---

## 作者：Alcl000000 (赞：1)

先跑一个全源最短路，计算出每两个点之间的最短路。

对于每次询问，注意到 $k_i$ 很小，于是可以枚举每条边的经过顺序，再枚举每条边的正反，计算即可。

若当前点为 $now$，要经过从 $u_i$ 到 $v_i$ 的边，且边是正向的（即先到 $u_i$ 再到 $v_i$），用 $dis_{x,y}$ 表示从 $x$ 到 $y$ 的最短路，则经过这条边的代价为 $dis_{now,u_i}+t_i$，然后令 $now=v_i$，边是反向的同理。

code：

```cpp
#include<bits/stdc++.h>
#define int long long
#define ios ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
using namespace std;
int vis[10],b[15],dis[405][405],k,n,q,m,u[200005],v[200005],t[200005];
int dfs(int x,int now,int res){
	if(x==k+1){
		return res+dis[now][n];
	}
	int ans=1e18;
	for(int i=1;i<=k;i++){
		if(!vis[i]){
			vis[i]=1;
			ans=min(ans,min(dfs(x+1,v[b[i]],res+dis[now][u[b[i]]]+t[b[i]]),dfs(x+1,u[b[i]],res+dis[now][v[b[i]]]+t[b[i]])));
			vis[i]=0;
		}
	}
	return ans;
}
signed main(){
	ios;
	cin>>n>>m;
	memset(dis,0x1f,sizeof dis);
	for(int i=1;i<=n;i++) dis[i][i]=0;
	for(int i=1;i<=m;i++){
		cin>>u[i]>>v[i]>>t[i];
		dis[u[i]][v[i]]=dis[v[i]][u[i]]=min(dis[u[i]][v[i]],t[i]);
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
			}
		}
	}
	cin>>q;
	while(q--){
		memset(vis,0,sizeof vis);
		cin>>k;
		for(int i=1;i<=k;i++) cin>>b[i];
		cout<<dfs(1,1,0)<<'\n';
	}
	return 0;
}
```

---

## 作者：sherry_lover (赞：1)

# AT_abc369_e [ABC369E] Sightseeing Tour 题解

[题目传送门](https://www.luogu.com.cn/problem/AT_abc369_e)

## 思路

发现 $k$ 很小，可以针对 $k$ 来做。

$O(k!)$ 全排列一下边的经过顺序，然后 $O(2^k)$ 枚举每条边的经过顺序，提前计算一下最短路，枚举完算一下总距离即可。时间复杂度 $O(n^3+2^kk!)$。

Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct edge{
	int u,v;
	long long w;
}b[200005];
int n,m,q,k,a[10];
long long dis[405][405],ans = 1e18;
bool vis[10];
vector<pair<int,int> > l;
long long f()
{
	long long tot = 0;
	l.clear();
	for(int i = 1;i <= k;i++)
	{
		if(vis[i]) l.push_back({b[a[i]].v,-1}),l.push_back({b[a[i]].u,i});
		else l.push_back({b[a[i]].u,-1}),l.push_back({b[a[i]].v,i});
	}
	int id = 1;
	for(auto i:l)
	{
		tot += (i.second == -1?dis[id][i.first]:b[a[i.second]].w);
		id = i.first;
	}
	tot += dis[id][n];
	return tot;
}
void floyd()
{
	for(int k = 1;k <= n;k++)
	{
  		for(int x = 1;x <= n;x++) 
  		{
    		for(int y = 1;y <= n;y++)
			{
      			dis[x][y] = min(dis[x][y],dis[x][k]+dis[k][y]);
   		 	}
  		}
	}	
}
void dfs(int x)
{
	if(x == k+1)
	{
		ans = min(ans,f());
		return;
	}
	vis[x] = 0;
	dfs(x+1);
	vis[x] = 1;
	dfs(x+1);
}
int main()
{
	memset(dis,0x3f,sizeof(dis));
	cin >> n >> m;
	for(int i = 1;i <= m;i++)
	{
		cin >> b[i].u >> b[i].v >> b[i].w;
		dis[b[i].u][b[i].v] = dis[b[i].v][b[i].u] = min(dis[b[i].u][b[i].v],b[i].w);
	}
	for(int i = 1;i <= n;i++) dis[i][i] = 0;
	floyd();
	cin >> q;
	while(q--)
	{
		ans = 1e18;
		cin >> k;
		for(int i = 1;i <= k;i++) cin >> a[i];
		sort(a+1,a+k+1);
		do{
			memset(vis,0,sizeof(vis));
			dfs(1);
		}while(next_permutation(a+1,a+k+1));
		cout << ans << endl;
	} 
	return 0;
}
```

---

## 作者：沃若 (赞：1)

#### 做法一

定义 $dp_{s,i,0/1}$ 表示当前走过的桥的状态是 $s$，最后一次路过的桥是 $i$，$0/1$ 表示最后一次过桥的方向（$u_i \rightarrow v_i$ 或者 $v_i \rightarrow u_i$）。转移时先枚举一座 $s$ 中的桥 $x$，从去掉该桥的状态中再枚举一个最后一次路过的桥 $y$，由 $dp_{s-2^x,y,0/1}$ 转移即可。这个做法**不需要枚举全排列**。

时间复杂度为：$O(n^3+m+q\cdot2^k\cdot k^2)$。

[Submission #57315524 - AtCoder Beginner Contest 369](https://atcoder.jp/contests/abc369/submissions/57315524)

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
long long g[405][405];
int u[200005], v[200005], w[200005];
int q;
int b[5];
long long dp[1 << 5][5][2];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			g[i][j] = g[j][i] = LLONG_MAX / 2;
	for (int i = 1; i <= m; i++) {
		cin >> u[i] >> v[i] >> w[i];
		g[u[i]][v[i]] = min<long long>(g[u[i]][v[i]], w[i]);
		g[v[i]][u[i]] = min<long long>(g[v[i]][u[i]], w[i]);
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	for (cin >> q; q--; ) {
		int k;
		cin >> k;
		for (int i = 0; i < k; i++)
			cin >> b[i];
		for (int i = 1; i < (1 << k); i++)
			for (int j = 0; j < k; j++)
				dp[i][j][0] = dp[i][j][1] = LLONG_MAX / 2;
		for (int i = 1; i < (1 << k); i++) {
			for (int x = 0; x < k; x++) {
				if ((i & (1 << x)) != 0) {
					if ((i & (i - 1)) == 0) {
						dp[i][x][0] = g[1][v[b[x]]] + w[b[x]];
						dp[i][x][1] = g[1][u[b[x]]] + w[b[x]];
						continue;
					}
					for (int y = 0; y < k; y++) {
						if ((i & (1 << y)) != 0 && x != y) {
							dp[i][x][0] = min(dp[i][x][0], min(dp[i ^ (1 << x)][y][0] + g[u[b[y]]][v[b[x]]], dp[i ^ (1 << x)][y][1] + g[v[b[y]]][v[b[x]]]) + w[b[x]]);
							dp[i][x][1] = min(dp[i][x][1], min(dp[i ^ (1 << x)][y][0] + g[u[b[y]]][u[b[x]]], dp[i ^ (1 << x)][y][1] + g[v[b[y]]][u[b[x]]]) + w[b[x]]);
						}
					}
				}
			}
		}
		long long res = LLONG_MAX / 2;
		for (int i = 0; i < k; i++)
			res = min(res, min(dp[(1 << k) - 1][i][0] + g[u[b[i]]][n], dp[(1 << k) - 1][i][1] + g[v[b[i]]][n]));
		cout << res << '\n';
	}
	return 0;
}
```

#### 做法二

全排列枚举过桥的顺序，然后模拟即可。看到很多人都又套了一个 $O(2^k)$ 的状压，实际上没有必要。与做法一类似，记录上一次过桥的方向及答案即可做到 $O(n^3+m+q\cdot k!\cdot k)$。

[Submission #57335924 - AtCoder Beginner Contest 369](https://atcoder.jp/contests/abc369/submissions/57335924)

```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m;
long long g[405][405];
int u[200005], v[200005], w[200005];
int q;
int b[5];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			g[i][j] = g[j][i] = LLONG_MAX / 2;
	for (int i = 1; i <= m; i++) {
		cin >> u[i] >> v[i] >> w[i];
		g[u[i]][v[i]] = min<long long>(g[u[i]][v[i]], w[i]);
		g[v[i]][u[i]] = min<long long>(g[v[i]][u[i]], w[i]);
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	for (cin >> q; q--; ) {
		int k;
		cin >> k;
		for (int i = 0; i < k; i++)
			cin >> b[i];
		sort(b, b + k);
		long long res = LLONG_MAX;
		do {
			int pu = 1, pv = 1;
			long long ansu = 0, ansv = 0;
			for (int i = 0; i < k; i++) {
				const long long preu = ansu, prev = ansv;
				ansu = min(preu + g[pu][v[b[i]]], prev + g[pv][v[b[i]]]) + w[b[i]];
				ansv = min(preu + g[pu][u[b[i]]], prev + g[pv][u[b[i]]]) + w[b[i]];
				pu = u[b[i]];
				pv = v[b[i]];
			}
			res = min(res, min(ansu + g[pu][n], ansv + g[pv][n]));
		} while (next_permutation(b, b + k));
		cout << res << '\n';
	}
	return 0;
}
```

#### 总结

实际上这个记录最后位置的优化从 TSP 问题出发可以很自然地想到，写过 Hamilton 路径/环路的话应该是比较显然的。

**Update**: 套了个快读以后拿到了最优解榜一，4 秒时限只跑了 60 毫秒。

[Submission #57336507 - AtCoder Beginner Contest 369](https://atcoder.jp/contests/abc369/submissions/57336507)

```cpp
#include <bits/stdc++.h>

using namespace std;

inline char nextchar() {
	static char buf[1 << 20], *p = buf, *q = buf;
	return p == q && (q = (p = buf) + fread(buf, 1, 1 << 20, stdin), p == q) ? EOF : *p++;
}

template <typename T, typename = enable_if_t<is_integral_v<T>>>
inline void read(T& x) {
	x = 0;
	char c = nextchar();
	for (; !isdigit(c); c = nextchar()) ;
	for (;  isdigit(c); c = nextchar()) x = x * 10 + c - '0';
}

template <typename T, typename... other>
inline void read(T& x, other&... y) {
	read(x);
	read(y...);
}

int n, m;
long long g[405][405];
int u[200005], v[200005], w[200005];
int q;
int b[5];

int main() {
	read(n, m);
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			g[i][j] = g[j][i] = LLONG_MAX / 2;
	for (int i = 1; i <= m; i++) {
		read(u[i], v[i], w[i]);
		g[u[i]][v[i]] = min<long long>(g[u[i]][v[i]], w[i]);
		g[v[i]][u[i]] = min<long long>(g[v[i]][u[i]], w[i]);
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
	for (read(q); q--; ) {
		int k;
		read(k);
		for (int i = 0; i < k; i++)
			read(b[i]);
		sort(b, b + k);
		long long res = LLONG_MAX;
		do {
			int pu = 1, pv = 1;
			long long ansu = 0, ansv = 0;
			for (int i = 0; i < k; i++) {
				const long long preu = ansu, prev = ansv;
				ansu = min(preu + g[pu][v[b[i]]], prev + g[pv][v[b[i]]]) + w[b[i]];
				ansv = min(preu + g[pu][u[b[i]]], prev + g[pv][u[b[i]]]) + w[b[i]];
				pu = u[b[i]];
				pv = v[b[i]];
			}
			res = min(res, min(ansu + g[pu][n], ansv + g[pv][n]));
		} while (next_permutation(b, b + k));
		printf("%lld\n", res);
	}
	return 0;
}
```

---

## 作者：ZPB2011 (赞：1)

# Sightseeing Tour

[题目传送门](https://www.luogu.com.cn/problem/AT_abc369_e)

## 思路

看完题后看数据点，发现这题的数据非常小 $2\le N\le400$ 且 $k\le5$，所以就可以向到一个非常暴力的思路：先 `floyd` 求出多源最短路，然后用 `dfs` 全排列找出答案。

## 代码

```cpp
#include <iostream>
#include <cstring>
#define int long long//十年OI一场空，不开long long见祖宗
using namespace std;

int n, m, k, minn, b[500005], dis[405][405];
bool vis[500005];

struct node {
	int u, v, w;
}g[500005];

void dfs(int cur, int sum, int x) {//全排列
	if(cur == k + 1) {
		minn = min(minn, sum + dis[x][n]);
		return;
	}
	for(int i = 1; i <= k; i++) {
		if(!vis[i]) {
			vis[i] = true;
			int u = g[b[i]].u, v = g[b[i]].v, w = g[b[i]].w;
			dfs(cur + 1, sum + dis[x][u] + w, v);
			dfs(cur + 1, sum + dis[x][v] + w, u);
			vis[i] = false;
		}
	}
}

signed main() {
	cin >> n >> m;
	memset(dis, 0x3f, sizeof(dis));
	for(int i = 1; i <= n; i++) dis[i][i] = 0;
	for(int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		g[i] = {u, v, w};
		dis[u][v] = dis[v][u] = min(dis[u][v], w);
	}
	for(int k = 1; k <= n; k++) {
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);//floyd
			}
		}
	}
	int q;
	cin >> q;
	while(q--) {
		minn = 1e18;
		cin >> k;
		for(int i = 1; i <= k; i++) cin >> b[i];
		dfs(1, 0, 1);
		cout << minn << endl;
	}
	return 0;
}
```

~~这E题也太水了~~

---

## 作者：_radio_ (赞：0)

# AT_abc369_e [ABC369E] Sightseeing Tour 题解
## 题意
给你一个 $n$ 个点 $m$ 条边的带边权无向图，每次询问指定 $k$ 条必须经过的边，你可以用任何方向和顺序通过它们，问你在这种情况下从 $1$ 到 $n$ 经过的最小边权总和。

## 思路
前置知识：[Floyd](https://www.luogu.com.cn/problem/B3647)

注意到 $k$ 很小，考虑暴力枚举通过每条必须经过的边的方向与顺序。可以用提前求出的全源最短路快速计算答案，时间复杂度 $O(n^3+qk_i!2^{k_i})$。

## 细节
+ 对于每两个点之间的边，在跑最短路时只考虑边权最小的即可。

+ 记得双向连边。

+ 记录每一条边，无论它的边权是否最小，因为在询问时可能查到。

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,x[200010],y[200010],t[200010],dp[410][410],q,k,a[10],ans,flg[10];
void dfs(int u,int now,int d){
	if(d>k){
		ans=min(ans,now+dp[u][n]);
		return;
	}
	for(int i=1;i<=k;i++)
		if(!flg[i]){
			flg[i]=1;
			dfs(y[a[i]],now+dp[u][x[a[i]]]+t[a[i]],d+1),dfs(x[a[i]],now+dp[u][y[a[i]]]+t[a[i]],d+1);
			flg[i]=0;
		}
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dp[i][j]=1e18;
	for(int i=1;i<=n;i++)
		dp[i][i]=0;
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i]>>t[i];
		dp[x[i]][y[i]]=min(dp[x[i]][y[i]],t[i]),dp[y[i]][x[i]]=min(dp[y[i]][x[i]],t[i]);
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dp[i][j]=min(dp[i][j],dp[i][k]+dp[k][j]);
	cin>>q;
	while(q--){
		ans=1e18;
		cin>>k;
		for(int i=1;i<=k;i++)
			cin>>a[i];
		dfs(1,0,1);
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：PikachuQAQ (赞：0)

### Description

[Link](https://www.luogu.com.cn/problem/AT_abc369_e)

### Solution

一座桥用一次以上一定不会更优，发现给定的桥最多只有 $5$ 座，因此可以枚举桥的使用顺序，转移每座桥的方向。

发现 $n$ 最多 $500$，可以用 `floyd` 预处理出两两间的距离。

令 $g_{i,0/1}$ 表示询问的第 $i$ 座桥，是 $u \rightarrow v$ 还是 $v \rightarrow u$。

令 $t(u,v)$ 为 $u$ 到 $v$ 的时间。

转移可以表示为 $t(1,u_{b_1}) + t(v_{b_1}, u_{b_2}) + \cdots + t(u_{b_k}, n) + w_{b_1} + \cdots + w_{b_k}$。

枚举所有方向和顺序，最后的答案就是它们的最小值。记录答案输出即可。

### Code

```cpp
// PikachuQAQ 2024/09/02

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll INF = 1e18;
const int kMaxN = 402, kMaxM = 2e5 + 2;

struct E {
    int u, v; ll w;
} a[kMaxM];

int n, m, q, k;
ll f[kMaxN][kMaxN], ans, g[7][2];
int b[7], c[7];

int main() {
    ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
    cin >> n >> m;
    fill(f[0], f[0] + 161604, INF);
    for (int i = 1; i <= n; i++) f[i][i] = 0;
    for (int i = 1, u, v, w; i <= m; i++){
        cin >> u >> v >> w;
        a[i] = {u, v, w};
        f[u][v] = min(f[u][v], 1ll * w);
        f[v][u] = min(f[v][u], 1ll * w);
    }
    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= n; i++) {
            for (int k = 1; k <= n; k++) {
                f[i][k] = min(f[i][k], f[i][j] + f[j][k]);
            }
        }
    }
    for (cin >> q; q--; ) {
        cin >> k;
        for (int i = 1; i <= k; i++) cin >> b[i];
        iota(c + 1, c + k + 1, 1);
        fill(g[0], g[0] + 14, 0), ans = INF;
        do {
            g[1][0] = f[1][a[b[c[1]]].v] + a[b[c[1]]].w;
            g[1][1] = f[1][a[b[c[1]]].u] + a[b[c[1]]].w;
            for (int i = 1; i < k; i++) {
                auto [u1, v1, w1] = a[b[c[i]]];
                auto [u2, v2, w2] = a[b[c[i + 1]]];
                g[i + 1][0] = min(g[i][0] + f[u1][v2], g[i][1] + f[v1][v2]) + w2;
                g[i + 1][1] = min(g[i][0] + f[u1][u2], g[i][1] + f[v1][u2]) + w2;
            }
            auto [u, v, w] = a[b[c[k]]];
            ans = min({ans, g[k][0] + f[u][n], g[k][1] + f[v][n]});
        } while (next_permutation(c + 1, c + k + 1));
        cout << ans << '\n';
    }

    return 0;
}
```

---

## 作者：wangshulin (赞：0)

# 前言
被硬控 47 min。

写了个很笨的做法啊啊啊！
# 思路
$m$ 太大了，询问绝对不能套上 $m$。不难发现 $n$ 很小，所以用弗洛伊德可以直接 $O(n^{3})$ 求出 $\forall 1 \le i,j \le n$，$i,j$ 两点之间的最短路 $dis_{i,j}$，然后每次询问做一次 dp，设 $f_{S,i}$ 为走过了集合 $S$ 中的所有编号对应的要走的边，最终到了点 $i$ 的最小路径长度，发现只转移满足 $(i=1) \vee (\exists j,i=U_{B_{j}}) \vee (\exists j,i=V_{B_{j}})$ 的 $i$ 同样可以求出最终的最短路径，
对于不满足的 $i$，只需要设 $\forall S,f_{S,i}=\infty$。

dp 转移式如下：
$$
f_{S \cup j,U_{B_{j}}} \gets \min(f_{S,U_{B_{j}}},f_{S,i}+dis_{i,V_{B_{j}}}+T_{B_{j}}) \\
f_{S \cup j,V_{B_{j}}} \gets \min(f_{S,V_{B_{j}}},f_{S,i}+dis_{i,U_{B_{j}}}+T_{B_{j}})
$$

分别代表：
- $i$ 走到 $V_{B_{j}}$ 再通过边 $B_{j}$ 走到 $U_{B_{j}}$。
- $i$ 走到 $U_{B_{j}}$ 再通过边 $B_{j}$ 走到 $V_{B_{j}}$。

设 $T$ 为包含所有要求走过的边的编号集合，最终：
$$
ans=\min\{f_{T,i}+dis_{i,n}\}
$$

时间复杂度为 $O(m+n^{3}+q \times k^{2} \times 2^{k})$。

# 代码
~~其实赛时代码写成了 $O(m+n^{3}+q \times n \times k \times 2^{k})$，但是这个时间还是能过。~~

赛时 [code](https://atcoder.jp/contests/abc369/submissions/57315594)。

赛后调整 [code](https://atcoder.jp/contests/abc369/submissions/57387998)。

---

## 作者：Shadow_T (赞：0)

省流：暴力。

### 题目分析

看到 $n\leq 400$，我们发现对于每个点之间的距离是可以直接 Floyd 的。那么就处理出 Floyd，以便后面使用。

对于每次询问，我们发现 $Q \leq 5$。这种大小基本怎么写都是能接受的。我们可以直接给每座桥暴力全排列顺序，然后对于每座桥，都去 dfs 暴力搞他是先走桥头还是先走桥尾，因为他是双向的。统计出最小值输出。

复杂度 $O(n^3+QK!2^K)$。可以接受。

### 代码


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ll long long
#define ld long double
#define ull unsgined long long
#define fir first
#define sec second
#define pb push_back
namespace IO
{
	void Ios()
	{
		ios::sync_with_stdio (0);
		cin.tie(0);
		cout.tie(0);
	}
	void Read(int n,int a[])
	{
		for(int i=1;i<=n;i++)
		cin>>a[i];
	}
	void Print(int n,int a[])
	{
		for(int i=1;i<=n;i++)
		cout<<a[i]<<" ";
	}
};
using namespace IO;
//This is My namespace.
const int maxn=4e5+10;
ll dis[501][501];
const ll inf=1e18;
ll u[maxn],v[maxn],w[maxn];
ll ans=1e18;
int g[11],k,n;
void dfs(int x,int i,ll t)
{
	if(t>=ans) return;
	if(i>k)
	{
		ans=min(ans,t+dis[x][n]);
		return;
	}
	dfs(v[g[i]],i+1,t+dis[x][u[g[i]]]+w[g[i]]);
	swap(v[g[i]],u[g[i]]);
	dfs(v[g[i]],i+1,t+dis[x][u[g[i]]]+w[g[i]]);
}
signed main()
{
	Ios();
	int m;
	cin>>n>>m;
	for(int i=0;i<=500;i++)
	for(int j=0;j<=500;j++)
	if(i!=j) dis[i][j]=inf;
	for(int i=1;i<=m;i++)
	{
		cin>>u[i]>>v[i]>>w[i];
		dis[u[i]][v[i]]=min(dis[u[i]][v[i]],w[i]);
		dis[v[i]][u[i]]=dis[u[i]][v[i]];
	}
	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
	if(dis[i][k]!=inf&&dis[k][j]!=inf)
	dis[i][j]=min(dis[i][k]+dis[k][j],dis[i][j]);
	int q;
	cin>>q;
	while(q--)
	{
		cin>>k;
		for(int i=1;i<=k;i++)
		cin>>g[i];
		ll Min=1e18;
		sort(g+1,g+1+k);
		do
		{
			ans=1e18;
			dfs(1,1,0);
			Min=min(Min,ans);
		}
		while(next_permutation(g+1,g+1+k));
		cout<<Min<<"\n";
	}
}
```

### 笑点解析

我因为这一行吃了一发罚时：

```cpp
const int inf=1e18;
```

---

## 作者：O_v_O (赞：0)

# abc369_e Sightseeing Tour 题解

原题链接：[abc369_e](https://atcoder.jp/contests/abc369/tasks/abc369_e)。

## 题意

给定一张图，有 $n$ 个点，$m$ 条边，每个边有他的边权。现在给定 $q$ 次询问，会给定 $k$ 条边，要求你从节点 $1$ 走到节点 $n$ 必须经过这 $k$ 条边，请问最小代价是多少。

## 思路

我们可以发现 $n$ 的值都很小，所以，我们就可以直接跑 Floyd，将每个点的最短路求出来。再看每一次的 $k$ 也很小，所以我们就可以直接爆搜求最小值。

时间复杂度：$\mathcal{O}(n^3 + q \times 2^k)$。

## 代码

```cpp
#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 410;
const int M = 2e5 + 10;

int n, m, u[M], v[M], a[10], x;
ll dis[N][N], w[M], ans = 1e18; // long long 注意

void dfs(int pre, int k, ll sum) { // 爆搜
  if (k > x) {
    sum += dis[pre][n];
    ans = min(ans, sum);
    return;
  }
  dfs(u[a[k]], k + 1, sum + dis[pre][v[a[k]]] + w[a[k]]);
  dfs(v[a[k]], k + 1, sum + dis[pre][u[a[k]]] + w[a[k]]);
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) 
    for (int j = 1; j <= n; j++)
      dis[i][j] = 1e12 * (i != j);
  for (int i = 1; i <= m; i++) {
    cin >> u[i] >> v[i] >> w[i];
    dis[u[i]][v[i]] = min(dis[u[i]][v[i]], w[i]);
    dis[v[i]][u[i]] = min(dis[v[i]][u[i]], w[i]);
  }
  for (int k = 1; k <= n; k++) // Floyd
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= n; j++) 
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
  int q;
  cin >> q;
  while (q--) {
    cin >> x;
    for (int i = 1; i <= x; i++) {
      cin >> a[i];
    }
    sort(a + 1, a + x + 1); // 记得要排序
    ll num = 1e18;
    do {
      ans = 1e18;
      dfs(1, 1, 0);
      num = min(num, ans);
    } while (next_permutation(a + 1, a + x + 1));
    cout << num << endl;
  }
  return 0;
}
```

---

## 作者：tai_chi (赞：0)

### 题意

给出一张带边权的无向图，$Q$ 次询问当指定 $K$ 条必经边时，$1$ 到 $n$ 的最短路。

### 解法

称必经边的端点以及起点、终点为关键点。注意到 $K \le 5$，于是可以阶乘地枚举必经边的通过顺序，依次走过每个关键点即可。

依次走过每个关键点的最短路统计可以使用 Floyd 预处理，$N \le 400$，可以接受。

时间复杂度 $O(N^3 + Q \times K! \times K)$，足以通过本题。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 2e3 + 5, M = 5e6 + 5;
int n, m;
typedef tuple<int, int, int> piii;
piii e[M];
int f[N][N];
signed main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			f[i][j] = 1e15;
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		e[i] = {u, v, w};
		f[u][v] = min(f[u][v], w), f[v][u] = min(f[v][u], w);
	}
	for (int k = 1; k <= n; k++)
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
	for (int i = 1; i <= n; i++)
		f[i][i] = f[i][i] = 0;
	int Q;
	cin >> Q;
	while (Q--)
	{
		int b;
		cin >> b;
		vector<piii> r, p;
		for (int i = 1; i <= b; i++)
		{
			int x;
			cin >> x;
			r.push_back(e[x]);
		}
		int ans = 1e17;
		for (int i = 0; i <= (1 << b) - 1; i++)
		{
			p = r;
			for (int j = 0; j < b; j++)
			{
				if (((i >> j) & 1) == 1)
				{
					auto [u, v, w] = p[j];
					p[j] = {v, u, w};
				}
			}
			sort(p.begin(), p.end());
			do
			{
				int res = 0, pos = 1;
				for (auto [u, v, w] : p)
				{
					res += f[pos][u] + w;
					pos = v;
				}
				res += f[pos][n];
				ans = min(ans, res);
			} while (next_permutation(p.begin(), p.end()));
		}
		cout << ans << endl;
	}
	return 0;
}
```

---

## 作者：Lydia1010__ (赞：0)

## 本题思路：
~~这道题赛时想炸了，想成了分层图，一看时间空间全炸，直接放弃了。~~

我们一看 $n$ 的大小，可以直接考虑 Floyd 求两点之间的最短路，然后暴力枚举必须要通过的边的通过顺序，然后直接枚举通过桥的方向，直接维护上一个移到的位置到当前桥选择方向的起点的时间，加上通过桥的时间。

最后答案取最小值即可。
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[405][405];
int u[200005],v[200005],t[200005];
int jl[15],b[405],ans=1e18,n1;
void dfs(int p,int n,int q,int sum){
	if(p>n){ans=min(ans,sum+a[q][n1]);return;}
	for(int i=1;i<=n;i++){
		if(jl[i]==0){
			jl[i]=1;
			dfs(p+1,n,v[b[i]],sum+a[q][u[b[i]]]+t[b[i]]);
			dfs(p+1,n,u[b[i]],sum+a[q][v[b[i]]]+t[b[i]]);
			jl[i]=0;
		}
	}
}
signed main(){
	int n,m;
	cin>>n>>m;n1=n;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=1e18;
		}
		a[i][i]=0;
	}
	for(int i=1;i<=m;i++){
		int x,y,k;
		cin>>x>>y>>k;
		u[i]=x,v[i]=y;t[i]=k;
		a[x][y]=min(a[x][y],k),a[y][x]=min(a[y][x],k);
	}
	for(int k=1;k<=n;k++){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				a[i][j]=min(a[i][j],a[i][k]+a[k][j]);
			}
		}
	}
	int q;
	cin>>q;
	while(q--){
		int k;ans=1e18;
		cin>>k;
		for(int i=1;i<=k;i++) cin>>b[i];
		dfs(1,k,1,0);
		cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：__Allen_123__ (赞：0)

> $q$ 次询问，每次询问求出经过特定 $k$ 条边的从 $1$ 号点到 $n$ 号点的最短路径。

赛时往 dij 分层图想了，$50$ 分钟左右才过，掉大分。

由于点数很少，考虑先使用 Floyd 求出任意两点间的最短路径。对于每次询问我们先考虑当 $k=1$ 时怎么做。

显然当 $k=1$ 时，唯二可能是最优的做法就是：（设必须经过的边是 $(u,v)$）

1. 先走从 $1$ 到 $u$ 的最短路径，再经过这一条边到达 $v$，最后走从 $v$ 到 $n$ 的最短路径。
2. 先走从 $1$ 到 $v$ 的最短路径，再经过这一条边到达 $u$，最后走从 $u$ 到 $n$ 的最短路径。

当 $k$ 更大时，我们可以随意决定自己走这几条边的顺序，进行 dfs 枚举每种情况即可。答案计算参考如上的方式就可解决本题。

[AC 记录](https://atcoder.jp/contests/abc369/submissions/57312370)。

---

## 作者：Liyunze123 (赞：0)

# 题意
给定 $n$ 个点和 $m$ 条带权无向边，有 $q$ 次询问，每次询问给出 $d$ 数组，要你求走了所有第 $d_i$ 条边，从 $1$ 到 $n$ 的最短路。
# 题解
$n\le 400$，可以 $O(n^3)$ 或 $O(n^2 \log n)$ 求所有点之间的最短路。又因为 $k \le 5$，可以爆搜走边的顺序。

我们枚举每个 $d$ 的排列，枚举每条边从 $a_{d_i}$ 走还是从 $b_{d_i}$ 走。在 dfs 过程中计一个 $cnt$，表示当前总边权，一个 $start$ 表示从哪个点走到 $a_{d_i}$ 或者 $b_{d_i}$ 然后走这条边，还需要记录哪些边已经走过了（显然，走两次肯定不优）。对于一条没走过的边，枚举走 $a_{d_i}$ 还是 $b_{d_i}$，对 $cnt$ 做相应的增加，将这条边记录为选过。
# 优化
1. 如果你用堆优化 dijkstra 求最短路，要去重边。
2. 剪枝，$cnt\ge ans$ 不要继续搜。
# 代码
```
// LUOGU_RID: 175557348
#include<bits/stdc++.h>
#include<queue>
#define int long long
using namespace std;
typedef pair<int,int>P;
int n,m,a[200010],b[200010],c[200010],e[400010],ne[400010],h[410],r[400010],idx,q,k,d[6],s[6],st[410],g[410][410],l[410][410],ans;
void add(int a,int b,int c){e[idx]=b,r[idx]=c,ne[idx]=h[a],h[a]=idx++;}
priority_queue<P,vector<P>,greater<P> >t;
void dij(int i){
	for(int w=1;w<=n;w++)g[i][w]=9e18,st[w]=0;
	g[i][i]=0,t.push({0,i});
	while(t.size()){
		int k=t.top().second;t.pop();
		if(st[k])continue;
		st[k]=1;
		for(int w=h[k];~w;w=ne[w])if(g[i][e[w]]>g[i][k]+r[w]){
			g[i][e[w]]=g[i][k]+r[w];
			if(!st[e[w]])t.push({g[i][e[w]],e[w]});
		}
	}
}
void dfs(int i,int cnt,int p){
	if(cnt>=ans)return;
	if(i==k){ans=min(ans,cnt+g[p][n]);return;}
	for(int w=1;w<=k;w++)
		if(!s[w])s[w]=1,cnt+=g[p][a[d[w]]]+c[d[w]],dfs(i+1,cnt,b[d[w]]),cnt-=g[p][a[d[w]]]-g[p][b[d[w]]],dfs(i+1,cnt,a[d[w]]),s[w]=0,cnt-=c[d[w]]+g[p][b[d[w]]];
}
signed main(){
    scanf("%d%d",&n,&m),memset(h,-1,sizeof(h)),memset(l,0x3f,sizeof(l));
    for(int w=1;w<=m;w++)scanf("%d%d%d",&a[w],&b[w],&c[w]),l[a[w]][b[w]]=min(l[a[w]][b[w]],c[w]);
    for(int w=1;w<=n;w++)for(int x=w+1;x<=n;x++)if(l[w][x]!=0x3f3f3f3f)add(w,x,l[w][x]),add(x,w,l[w][x]);
    for(int w=1;w<=n;w++)dij(w);
	scanf("%d",&q);
	while(q--){
		scanf("%d",&k);
		for(int w=1;w<=k;w++)scanf("%d",&d[w]);
		ans=9e18,dfs(0,0,1),printf("%lld\n",ans);
	}
    return 0;
//赛时 dfs 时仅仅恢复了不选的状态没恢复答案无缘 ac，痛失 8 rating，降到 1201 蓝名的最低下限
}
```

---

## 作者：liruixiong0101 (赞：0)

# E - Sightseeing Tour
## 题意：
给定一张 $n$ 个点 $m$（$2\le n\le 400,n-1\le m\le 2\times 10^5$）条边的无向带权图，图中可能会有重边，但不会有自环。给定 $T$ 次询问，每次询问给出 $k$（$1\le T\le 3000,1\le k\le 5$）条图上的边，求从 $1$ 到 $n$ 经过这 $k$ 条边的最短路。

## 思路：
经过这 $k$ 条边相当于每次从到达的点开始往还没经过的边的任意一个端点走，然后再走该边，这样题目就化成选边的顺序了，又观察到 $1\le k\le 5$，考虑状压 dp。

设 $f_{i,S}$ 为到达第 $i$ 个点，已经过给定边集的子集 $S$ 的最短路径（这里的 $i$ 数量很有限，只可能是给定边的端点）。

枚举集合 $S$，再枚举集合 $S$ 中的元素 $i$，设集合 $T$ 为集合 $S$ 中除去元素 $i$ 的集合，再枚举集合 $T$ 中的元素 $j$（若集合 $S$ 中只有 $1$ 个及以下的元素，那么会被预处理算出），考虑用 $f_{u_j/v_j,T}$ 转移得到 $f_{u_i/v_i,S}$，很显然有 $f_{u_i,S}\gets f_{u_j,T}+d_{u_j,v_i}+w_i$（$d_{u,v}$ 表示图中 $u$ 到 $v$ 的最短路径。$v_i,v_j$ 同理转移）。

考虑初始化，$f_{u_i/v_i,\varnothing}=d_{1,u_i/v_i},f_{u_i/v_i,\{i\}}=d_{1,u_i/v_i}+w_i$。

求解 $d$ 数组可以用 floyd 求解，总时间复杂度应该是：$O(n^3+m+T\cdot k^2\cdot 2^k)$。

## 代码：
<https://atcoder.jp/contests/abc369/submissions/57335439>

---

## 作者：osfly (赞：0)

### something interesting

赛后 VP 看到本题时限竟然有 4s 以为我这位大常数选手要寄了，结果写出来发现最慢的点都才 539 ms。

### 正文

发现 $n$ 才 $400$，直接给他安排个 Floyd 套餐。

发现 $k$ 才 $5$，直接给他安排个暴力套餐。

把答案拆成两部分：必须经过的和非必须经过的。

对于必须经过的，直接加这些桥的总长即可。

对于非必须经过的，我们把 $b$ 全排列，然后枚举长度为 $k$ 的 $01$ 串 $c$。对于第 $i$ 条必须经过的桥梁 $b_i$，如果 $c_i=0$ 那么我们就走到这座桥的 $u$ 然后经过桥到 $v$，否则就走到 $v$ 再经过桥到 $u$。然后直接计算答案即可。

时间复杂度 $O(n^3+qk2^kk!)$，一个长得令人害怕的复杂度。但是跑得很快。

```cpp
#include<bits/stdc++.h>
using namespace std;

#define ll long long

const int N=1e3+10;
const int M=2e5+10;
const ll INF=1e18;

struct edge
{
	int u,v;
	ll w;
}e[M<<1];

int n,m,q,s,b[10],c[10];
ll f[N][N],ans1,ans2;

ll calc()
{
	ll res=0;
	stack<int> st;
	st.push(1);
	for(int i=1;i<=s;i++)
	{
		if(c[i]) st.push(e[b[i]].u),st.push(e[b[i]].v);
		else st.push(e[b[i]].v),st.push(e[b[i]].u);
	}
	st.push(n);
	while(!st.empty())
	{
		int u=st.top();
		st.pop();
		int v=st.top();
		st.pop();
		res+=f[u][v];
	}
	return res;
}

void dfs(int x)
{
	if(x>s)
	{
		ans2=min(ans2,calc());
		return ;
	}
	c[x]=0,dfs(x+1);
	c[x]=1,dfs(x+1);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) f[i][j]=INF;
		f[i][i]=0;
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lld",&e[i].u,&e[i].v,&e[i].w);
		f[e[i].u][e[i].v]=f[e[i].v][e[i].u]=min(f[e[i].u][e[i].v],e[i].w);
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	scanf("%d",&q);
	while(q--)
	{
		ans1=0,ans2=INF;
		scanf("%d",&s);
		for(int i=1;i<=s;i++) scanf("%d",&b[i]),ans1+=e[b[i]].w;
		sort(b+1,b+1+s);
		do
		{
			dfs(1);
		}while(next_permutation(b+1,b+1+s));
		printf("%lld\n",ans1+ans2);
	}
	return 0;
}
```

---

## 作者：ma_niu_bi (赞：0)

### E-Sightseeing Tour

#### 题意

给定一张 $n$ 个点 $m$ 条边的图，有 $q$ 次查询。

每次查询给出 $k$ 条边，求一条 $1$ 到 $n$ 并且经过这 $k$ 条边的最短路径。

#### 思路

先用 Floyd 求出全源最短路，再枚举给出的边的排列，即经过顺序。

搜索从每条边的哪个点进入，在两条边的端点之间走最短路，并加上该边权。

时间复杂度：$O(n^3+q k!2^k)$。

#### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int N = 405, M = 2e5 + 5;
int n, m, q, K, id[N];
ll f[N][N], ans;
int u[M], v[M], w[M];
void dfs(int p, int x, ll cost) {
    if (cost > ans) return ;
    if (x == u[id[p]]) x = v[id[p]];
    else x = u[id[p]];
    cost += w[id[p]];
    if (p == K) {
        cost += f[x][n];
        ans = min(ans, cost);
        return ;
    }
    dfs(p + 1, u[id[p + 1]], cost + f[x][u[id[p + 1]]]);
    dfs(p + 1, v[id[p + 1]], cost + f[x][v[id[p + 1]]]);
}
void solve() {
    cin >> n >> m;
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= m; i ++) {
        cin >> u[i] >> v[i] >> w[i];
        f[u[i]][v[i]] = min(f[u[i]][v[i]], 1ll * w[i]);
        f[v[i]][u[i]] = min(f[v[i]][u[i]], 1ll * w[i]);
    }
    for (int i = 1; i <= n; i ++) f[i][i] = 0;
    for (int k = 1; k <= n; k ++) {
        for (int i = 1; i <= n; i ++) {
            for (int j = 1; j <= n; j ++) {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
    cin >> q;
    for (int i = 1; i <= q; i ++) {
        cin >> K;
        for (int j = 1; j <= K; j ++) cin >> id[j];
        sort(id + 1, id + K + 1);
        ans = 1e18;
        do {
            dfs(1, u[id[1]], f[1][u[id[1]]]);
            dfs(1, v[id[1]], f[1][v[id[1]]]);
        } while(next_permutation(id + 1, id + K + 1));
        cout << ans << "\n";
    }
}
int main() {
    int T = 1;
    // cin >> T;
    while (T --) 
        solve();
    return 0;
}
```

---

## 作者：Shunpower (赞：0)

提供一个 $\mathcal O(n^3+qk!k)$ 的做法。

设必须经过的桥梁边序列为 $(u_i,v_i)$。

考虑答案形态可以发现，最短路应当形如 $1\to u_{a_1}\to v_{a_1}\to u_{a_2}\to v_{a_2}\cdots \to u_{a_n}\to v_{a_n}$，其中 $a$ 应该是一个 $k$ 的排列。注意因为桥梁总是双向的，所以这里的 $u\to v$ 不一定就是原来的 $u\to v$，也可以是 $v\to u$，换而言之，一座桥梁可以以两种方向加入答案。

考虑枚举全排列，得到桥的顺序。但无需再次枚举桥加入答案的方向。

设 $f_{i,0/1}$ 表示第 $i$ 座桥梁以 $u\to v$（正向）或 $v\to u$（反向）加入答案时走过第 $i$ 座桥梁的最短路，从 $i\to i+1$ 转移时只需要考虑上一座桥梁的某一端到这一座桥梁的某一端的最短路（因为不限制反复经过给定桥梁，显然可以在询问开始前用一个 Floyd 跑出来），然后加上这座桥梁的边权到达另一端，然后继续 dp 下去即可。

dp 到最后算上最后一座桥两端到 $n$ 的最短路即可。初值显然是 $1$ 到第一座桥两端的最短路。

显然第一维可以滚动掉，于是拿两个变量维护即可。

```cpp
int n,m;
ll dis[410][410];
struct edge{
    int u,v;
    ll w;
} E[N];
int p[N];
int k[10];
int main(){
#ifdef SHUN
    freopen("hack.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    ios::sync_with_stdio(false);
    memset(dis,0x3f,sizeof dis);
    cin>>n>>m;
    fr1(i,1,n) dis[i][i]=0;
    fr1(i,1,m){
        int u,v;
        ll w;
        cin>>u>>v>>w;
        E[i]={u,v,w};
        dis[v][u]=min(dis[v][u],w);
        dis[u][v]=min(dis[u][v],w);
    }
    fr1(k,1,n){
        fr1(i,1,n){
            fr1(j,1,n) dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
        }
    }
    int q;
    cin>>q;
    while(q--){
        int l;
        cin>>l;
        fr1(i,1,l) cin>>k[i];
        fr1(i,1,l) p[i]=i;
        ll minn=1e18;
        do{
            ll sumu=dis[1][E[k[p[1]]].u],sumv=dis[1][E[k[p[1]]].v];
            fr1(i,1,l-1){
                int u=E[k[p[i]]].u,v=E[k[p[i]]].v;
                int u2=E[k[p[i+1]]].u,v2=E[k[p[i+1]]].v;
                ll w=E[k[p[i]]].w;
                sumu+=w;
                sumv+=w;
                ll tmpu=min(sumu+dis[v][u2],sumv+dis[u][u2]);
                ll tmpv=min(sumu+dis[v][v2],sumv+dis[u][v2]);
                sumu=tmpu,sumv=tmpv;
            }
            minn=min(minn,min(sumu+E[k[p[l]]].w+dis[E[k[p[l]]].v][n],sumv+E[k[p[l]]].w+dis[E[k[p[l]]].u][n]));
        }while(next_permutation(p+1,p+l+1));
        cout<<minn<<'\n';
    }
    ET;
}
```

---

## 作者：No_Rest (赞：0)

# 思路

不知道为什么会放在 E。

下文的 $k$ 均指 $K_i$。

观察到 $k$ 范围较小，可以暴力全排列枚举必经的每条边的遍历顺序，然后再二进制枚举这些边被遍历的方向。然后就可以 $\mathcal O(k)$ 遍历这些边，计算出最终长度。观察到 $n$ 也很小，所以可以 Floyd 一下，这样就可以 $\mathcal O(1)$ 算出两点间的距离。这样对于每个询问的时间复杂度为 $\mathcal O(k! \times 2^k \times k)$，总复杂度为 $\mathcal O(n^3 + q \times k! \times 2^k \times k)$，可以通过此题。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll maxn = 4e2 + 5;
const ll maxm = 2e5 + 5;
const ll inf = 1e18;
ll n, m, u[maxm], v[maxm], t[maxm], f[maxn][maxn], q, K, a[maxn], b[maxn], ans, now;
int main(){
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for(ll i = 1; i <= n; ++i)
		for(ll j = 1; j <= n; ++j)
			if(i != j) f[i][j] = inf;
	for(ll i = 1; i <= m; ++i){
		cin >> u[i] >> v[i] >> t[i];//注意到有重边，要必经的边不一定是两点间最短的边，所以相邻两点的距离不能直接调用 f 数组
		f[u[i]][v[i]] = min(f[u[i]][v[i]], t[i]);//同样这里要取 min
		f[v[i]][u[i]] = min(f[v[i]][u[i]], t[i]);
	}
	for(ll k = 1; k <= n; ++k)//Floyd
        for(ll i = 1; i <= n; ++i)
            for(ll j = 1; j <= n; ++j) f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
	cin >> q;
	for(ll i = 1; i <= q; ++i){
		cin >> K, ans = inf;
		for(ll j = 1; j <= K; ++j) cin >> b[j], a[j] = j;
		do{//全排列枚举
			for(ll j = 0; j < (1 << K); ++j){//二进制枚举
				for(ll k = 1; k <= K; ++k)
					if((j >> (k - 1)) & 1) swap(u[b[a[k]]], v[b[a[k]]]);//处理边的方向
				now = f[1][u[b[a[1]]]] + t[b[a[1]]];//计算该方案的长度
				for(ll k = 2; k <= K; ++k) now += f[v[b[a[k - 1]]]][u[b[a[k]]]] + t[b[a[k]]];
				now += f[v[b[a[K]]]][n];
				ans = min(ans, now);
				for(ll k = 1; k <= K; ++k)
					if((j >> (k - 1)) & 1) swap(u[b[a[k]]], v[b[a[k]]]);//记得还原
			}
		}while(next_permutation(a + 1, a + K + 1));
		cout << ans << '\n';
	}
	return 0;
}

```

---

## 作者：stripe_python (赞：0)

E 最暴力的一集。

给出的图 $m \gg n$，所以先跑一次 $O(n^3)$ floyd 预处理多源最短路。对于每次询问，有一个显然的暴力：

暴力枚举边的全排列，对于每条边，先从当前点走到边的起点，然后走过该边。

不过边是双向的，所以还要再套一个二进制枚举，枚举每条边是正着走还是反着走的。总复杂度 $O(n^3+qk!2^k)$。

```cpp
int n, m, u[M], v[M], w[M], g[N][N], q, k, b[20];
void _main() {
	read(n, m);
	memset(g, 0x3f, sizeof(g));
	for (int i = 1; i <= m; i++) {
		read(u[i], v[i], w[i]);
		g[u[i]][v[i]] = min(g[u[i]][v[i]], w[i]);
		g[v[i]][u[i]] = min(g[v[i]][u[i]], w[i]);
	}
	for (int i = 1; i <= n; i++) g[i][i] = 0;
	for (int k = 1; k <= n; k++) {
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) {
				g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
			}
		}
	}
	for (read(q); q--; ) {
		read(k), read(b + 1, b + k + 1);
		sort(b + 1, b + k + 1);
		int res = LLONG_MAX;
		do {
			int t = LLONG_MAX;
			for (int s = 0; s < (1 << k); s++) {
				int ans = 0, st = 1;
				for (int i = 1; i <= k; i++) {
					if (s >> (i - 1) & 1) {
						ans += g[st][u[b[i]]] + w[b[i]];
						st = v[b[i]];
					} else {
						ans += g[st][v[b[i]]] + w[b[i]];
						st = u[b[i]];
					}
				}
				ans += g[st][n];
				t = min(ans, t);
			}
			res = min(t, res);
		} while (next_permutation(b + 1, b + k + 1));
		writeln(res);
	}
}
```

---

