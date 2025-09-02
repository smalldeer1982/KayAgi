# 放置街灯 Placing Lampposts

## 题目描述

# 题面描述

给定一个 $n$ 个点 $m$ 条边的无向无环图，在尽量少的节点上放灯，使得所有边都与灯相邻（被灯照亮）。

在灯的总数最小的前提下，被两盏灯同时照亮的边数应该尽可能大。

## 样例 #1

### 输入

```
2
4 3
0 1
1 2
2 3
5 4
0 1
0 2
0 3
0 4```

### 输出

```
2 1 2
1 0 4```

# 题解

## 作者：Prurite (赞：11)

### 树形DP

因为原图保证无重边无环无自环, 所以原图一定是一颗树(或森林).  如果不考虑被双边照亮的边数问题, 我们可以很容易地写出方程:   
设 $dp[0,1][i]$ 分别表示不在/在第 $i$ 个点放灯时的最小灯数,  $v$ 是 $i$ 的儿子, 则  
```
dp[0][i]=sum{ dp[1][v] }
dp[1][i]=sum{ min( dp[0][v], dp[1][v] ) }
```
> 按此思路做的题: UVA1292 Strategic game

但是这道题还要使尽可能多的边被从双端照亮. 

因为这两个量一个要尽可能大, 一个要尽可能小, 我们不妨进行一下转换, 换为 `总共放的灯数a` 和 `只被单边照亮的边数b` .
因为 $a$ 对于结果的影响会比 $b$ 对结果的影响更大, 并且 $a,b$ 是同时更新的, 所以我们不妨把 $a,b$ 放到一个量进行处理, 我们把它称为 `花费m` .
为了体现出 $a,b$ 对 $m$ 的影响不同, 我们把 $a$ 乘以一个权值 $k$ , 这样也使得我们可以直接从 $m$ 中分离出 $a$ 和 $b$.  
比如, 如果转移到某个点的时候, 我们已经放了3盏灯, 有1条边被单边照亮, 令 $k=1000$ , 则 $m=3*1000+1=3001$ .
最后分离的时候 $a=m/k , b=m\%k$ 即可.   
注意, $k$ 应该足够大(大于 $b$ 的总和的最大值), 否则可能使得 $b$ 的值影响到 $a$ 的值. 对于此题而言, $k$ 应当大于 $n$ (所有边数的总和).

所以回到DP:   
设 $dp[0,1][i]$ 表示不在/在第i个点放灯时的最小花费  
初始化: $dp[ ][ ]=0$ (全部置0)  
设v是i的儿子, 状态转移:   
```
dp[0][i]=sum{ dp[1][v]+1 }
```
转移到儿子的花费是dp[1][v], 由于边i-v是单边照亮, 花费+1;  
```
dp[1][i]=sum{ min( dp[0][v]+1, dp[1][v] ) }+k
```
(1) 儿子不放灯, 类似于上一种情况;  
(2) 儿子也放灯, 边i-v就被两端照亮了, 不用额外加花费了.  
注意不要忘记放灯本身还要花费k.

最后不要忘了一点: 原图可能是森林.

附上代码(其实本题代码不长, 重点在于思维)
```cpp
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int MAXN=1000+10, MAXM=MAXN<<1, K=3000;
struct edge { int to, next; } e[MAXM];
int fe[MAXN], eid;
int dp[2][MAXN];
bool vis[MAXN];
vector<int> root; // 可能是森林
int n, m;

inline void adde( int a, int b )
{	e[++eid]=(edge){ b, fe[a] }, fe[a]=eid; }
void dfs( int now );

int main( )
{
	int T;
	scanf( "%d", &T );
	while ( T-- )
	{
		memset( fe, 0, sizeof fe ), eid=0;
		scanf( "%d %d", &n, &m );
		for ( int i=1; i<=m; i++ )
		{
			int a, b;
			scanf( "%d %d", &a, &b );
			adde( a, b ), adde( b, a );
		} // 加边
		memset( vis, 0, sizeof vis );
		root.clear( );
		for ( int i=1; i<=n; i++ )
			if ( !vis[i] )
				root.push_back( i ), dfs( i ); // 搜索每棵树
		int ans=0;
		for ( int i=0; i<root.size(); i++ )
			ans+=min( dp[0][root[i]], dp[1][root[i]] ); // 统计每棵树的dp值
		printf( "%d %d %d\n", ans/K, m-ans%K, ans%K ); //分离输出
	}
	return 0;
}

void dfs( int now )
{
	vis[now]=1;
	dp[0][now]=0, dp[1][now]=K; // 初始化
	for ( int i=fe[now]; i!=0; i=e[i].next )
	{
		int to=e[i].to;
		if ( vis[to] )
			continue;
		dfs( to );
		dp[0][now]+=dp[1][to]+1;
		dp[1][now]+=min( dp[1][to], dp[0][to]+1 );
	}
	return;
}
```
[提交记录](https://www.luogu.org/recordnew/show/8400576)

---

## 作者：maker (赞：5)

交了N次，重构一次代码终于过了.....

题意：一片森林，1.输出占领所有边需要的最小的路灯个数  2.输出两端点均被占领的边的条数  3.只有一端被占领的边的条数

还是比较简单的

开始的时候思路不够清晰，写的时候很多东西都没注意到

导致一直WA，重构的时候好多了，一遍过

开两个DP数组，一个存路灯个数，一个存两端都被占领的边的个数
感觉更好理解一些

以下是代码

```cpp
#include<cstdio>
#include<cstring>
#define N 100005

int n,m,cnt,T,ans1,ans2,a,b;
int head[N],vis[N];
int dp[N][2],f[N][2];

struct node{
	int v,nex;
}e[N];

void dfs(int u,int fa){
	dp[u][1]=1;
	vis[u]=1;
	for(int i=head[u];i;i=e[i].nex){
		int v=e[i].v;
		if(vis[v]) continue;
		dfs(v,u);
		dp[u][0]+=dp[v][1];
		f[u][0]+=f[v][1];
		if(dp[v][1]<dp[v][0]){
			dp[u][1]+=dp[v][1];
			f[u][1]+=f[v][1]+1;
		}
		else if(dp[v][1]>dp[v][0]){
			dp[u][1]+=dp[v][0];
			f[u][1]+=f[v][0];
		}
		else{					//这里进行一步特判，满足第二个条件
			dp[u][1]+=dp[v][0];
			if(f[v][1]+1>f[v][0]){
				f[u][1]+=f[v][1]+1;
			}
			else{
				f[u][1]+=f[v][0];
			}
		}
	}
}

void add(int u,int v){
	cnt++;
	e[cnt].v=v;
	e[cnt].nex=head[u];
	head[u]=cnt;
}

void init(){
	cnt=ans1=ans2=0;
	memset(head,0,sizeof head);
	memset(vis,0,sizeof vis);
	memset(dp,0,sizeof dp);
	memset(f,0,sizeof f);
}

int main(){
	scanf("%d",&T);
	while(T--){
		init();
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++){
			scanf("%d%d",&a,&b);
			a++,b++;
			add(a,b);add(b,a);
		}
		for(int i=1;i<=n;i++){
			if(!vis[i]){		//可能是森林，注意！！
				dfs(i,0);
				if(dp[i][0]>dp[i][1]){
					ans1+=dp[i][1];
					ans2+=f[i][1];
				}
				else if(dp[i][0]<dp[i][1]){
					ans1+=dp[i][0];
					ans2+=f[i][0];
				}
				else{			//同上
					ans1+=dp[i][0];
					if(f[i][1]>f[i][0]){
						ans2+=f[i][1];
					}
					else{
						ans2+=f[i][0];
					}
				}
			}
		}
		printf("%d %d %d\n",ans1,ans2,m-ans2);
	}
	return 0;
}
```

---

## 作者：chihik (赞：2)

 $n$ 个点 $m$ 条边的无向无环图，其实就是一个森林。

题目要求最小化两个量：灯数和只被一边照亮的边数。

一个做法是定义两个 $dp$ 数组，分别表示最小灯数和在灯数最小情况下的一边被照亮的最小边数。

然后你发现它们是一起转移的，那么就有一个极妙的做法：

将它们的贡献算在一起，因为灯数的优先级高，所以给它乘上一个权值 $k$。（这里 $k$ 可以取任意不小于 $n$ 的值 ，可以理解为 $k$ 进制的高低位），那么加一个灯贡献加 $k$ ，加一条单灯边贡献加 $1$，

那么转移就变为：

$$\begin{cases}
dp[u][0]=\sum_{v \in son_u}  dp[v][1]+1   \\
dp[u][1]=k+\sum_{v \in son_u}   \min\{  dp[v][0]+1,dp[v][1] \}
\end{cases}$$

最后只需要除以 $k$ ，和膜 $k$ 便能得到分别的答案。

```cpp
#include <cstdio>
#include <vector>
using namespace std;

const int MAXN = 1000 , k = 1005;
int T , n , m;
vector< int > Graph[ MAXN + 5 ];

int dp[ 2 ][ MAXN + 5 ];
void dfs( int u , int fa ) {
    dp[ 0 ][ u ] = 0 , dp[ 1 ][ u ] = k;
    for( int i = 0 ; i < Graph[ u ].size() ; i ++ ) {
        int v = Graph[ u ][ i ];
        if( v == fa ) continue;
        dfs( v , u );
        dp[ 0 ][ u ] += dp[ 1 ][ v ] + 1;
        dp[ 1 ][ u ] += min( dp[ 0 ][ v ] + 1 , dp[ 1 ][ v ] );
    }
}

int main( ) {
    scanf("%d",&T);
    while( T -- ) {
        scanf("%d %d",&n,&m);
        for( int i = 1 ; i <= n ; i ++ ) Graph[ i ].clear() , dp[ 0 ][ i ] = 0 , dp[ 1 ][ i ] = 0;
        for( int i = 1 , u , v ; i <= m ; i ++ ) {
            scanf("%d %d",&u,&v); u ++ , v ++;
            Graph[ u ].push_back( v );
            Graph[ v ].push_back( u );
        }

        int Ans1 = 0 , Ans2 = 0;
        for( int i = 1 ; i <= n ; i ++ )
            if( !dp[ 1 ][ i ] ) {
                dfs( i , 0 );
                Ans1 += min( dp[ 0 ][ i ] , dp[ 1 ][ i ] ) / k;
                Ans2 += min( dp[ 0 ][ i ] , dp[ 1 ][ i ] ) % k;
            }
        printf("%d %d %d\n", Ans1 , m - Ans2 , Ans2 );
    }
    return 0;
}
```

---

## 作者：RoRoyyy (赞：2)

这道题这种解法很神奇， 确实很有道理。

这道题让我们求的是灯数最小， 被两盏灯照亮尽可能大。
这种同时满足两个条件的题我们可以这样思考。

首先要求满足第一个条件， 再第一个条件相等的基础上继续满足第二个条件。我们可以这样抽象：第一条件更重要， 那么我们再把两个条件合并成一个条件的时候， 我们就让在第一个条件不同的情况下， 第二个条件在表达式里的地位失效。那么我们可以这样设：设$f=MAX*ans1+ans2$,其中$ans1$是最小灯数， $ans2$是被一盏灯照亮的最小道路， 这样我们只需要最小化$f$就行了， 最终答案就是$f/MAX$，因为$ans2$远小于$MAX$， 被两盏灯照亮的道路就是
$m-f$%$MAX$。

设$MAX = 2000$

再考虑$dp$来计算$f$, 设$dp[i][0/1]$为在以$i$为根的子树下（包含$i$和父亲那条边）的最小$f$。那么很显然：

当$i$不为根节点的时候：
$dp[i][1] = min(dp[son(i)][0] + 1, dp[son(i)][1] + 2000)$
$dp[i][0] = min(dp[son(i)][1] + 1 + 2000)$

当$i$为根节点的时候:
$dp[root][0] = min(dp[son[root][1]] + 2000, dp[son[root][0])$

```cpp
#include <cstring>
#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;
const int N = 1500;
vector <int> gr[N];
int vis[N][2], dp[N][2];
int DP(int now, int state, int pa) {
    if(vis[now][state]) return dp[now][state];
    vis[now][state] = 1;
    int &ans = dp[now][state];
    //这点放灯一定合法
    ans = 2000;
    for(int i = 0; i < gr[now].size(); i++) {
        int to = gr[now][i];
        if(to == pa) continue;
        ans += DP(to, 1, now);
    }
    if(pa >= 0 && !state) ans++;//如果这个点父亲节点没放灯， 那么这条边一定只经过了一次
    if(state || pa < 0) {//考虑父亲节点放灯的情况， 此时才可以此节点不放灯 把这种情况的答案存下来和这点放灯的情况比较
        int sum = 0;
        for(int i = 0; i < gr[now].size(); i++) {
            int to = gr[now][i];
            if(to == pa) continue;
            sum += DP(to, 0, now);
        }
        if(pa >= 0) sum++;//如果有父亲， 那么一定这条边只经过了一次
        ans = min(ans, sum);
    }
    return ans;
}
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        int n, m;
        scanf("%d%d", &n, &m);
        memset(vis, 0, sizeof(vis));
        memset(dp, 0, sizeof(dp));
        for(int i = 0; i < n; i++) gr[i].clear();
        for(int i = 1; i <= m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            gr[u].push_back(v);
            gr[v].push_back(u);
        }
        int ans = 0;
        for(int i = 0; i < n; i++) 
            if(!vis[i][0]) ans += DP(i, 0, -1);
        printf("%d %d %d\n", ans / 2000, m - ans % 2000, ans % 2000);
    }
    return 0;
}
```


---

## 作者：wanggiaoxing (赞：1)

### 树形dp
显然如果没有“在灯的总数最小的前提下，被两盏灯同时照亮的边数应该尽可能大”，我们可以把状态设计成。
```cpp
dp[i][0/1]表示在 i 节点放或不放灯情况下最少灯数。
```
那么我们很容易推出dp方程。

$ dp[i][0]=\sum dp[j][1]$

其中 $i$ 表示 $j$ 的父亲,这样转移的原因是如果这个点不放，那么这条边的另一个点必须放。

$ dp[i][1]=\sum \min( dp[j][0],dp[j][1] ) $

同理可得意思为这个点放了那么这条边的另一端可放可不放。
那我们何不在加上开头说的条件时也类似于这样设计呢？
```cpp
dp1[i][0/1]表示在 i 节点放或不放灯情况下最多的被两盏灯同时照亮的边数。
```
状态方程就不赘述了，详情见代码。
### 一些细节
因为这是一个 $n$ 个点 $m$ 条边的无向无环图,所以可能是一个森林，处理见代码。
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,m,dp[1005][2],dp1[1005][2];
vector<int>v[1005];
void dfs(int x,int fa)
{
	dp[x][1]=1;
	for(int i=0;i<v[x].size();i++)
	{
		int y=v[x][i];
		if(y==fa)
			continue;
		dfs(y,x);
		dp[x][0]+=dp[y][1];
		dp1[x][0]+=dp1[y][1];
		dp[x][1]+=min(dp[y][1],dp[y][0]);
		if(dp[y][1]<dp[y][0])
			dp1[x][1]+=dp1[y][1]+1;
		if(dp[y][1]==dp[y][0])
			dp1[x][1]+=max(dp1[y][0],dp1[y][1]+1);
		if(dp[y][0]<dp[y][1])
			dp1[x][1]+=dp1[y][0];
	}
}
int main()
{
	cin>>t;
	while(t--)
	{
		int ans=0,ans1=0;
		memset(dp,0,sizeof(dp));//万恶的初始化
		memset(dp1,0,sizeof(dp1));
		cin>>n>>m;
		for(int i=0;i<n;i++)
			v[i].clear();
		for(int i=1;i<=m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			v[x].push_back(y);
			v[y].push_back(x);
		}	
		for(int i=0;i<n;i++)//处理森林
		{
			if(!dp[i][1])
			{
				dfs(i,-1);
				ans+=min(dp[i][0],dp[i][1]);
				if(dp[i][0]<dp[i][1])
					ans1+=dp1[i][0];
				else
				if(dp[i][0]==dp[i][1])
					ans1+=max(dp1[i][0],dp1[i][1]);
				else
					ans1+=dp1[i][1];
			}
		}
		printf("%d %d %d\n",ans,ans1,m-ans1);
	}
	return 0;
}
```


---

## 作者：Plus_Ultra (赞：1)

一. 分析：

- 可以发现这道题和父亲上是否放灯有关.

- f(i, 1) 表示 i 的父亲放灯，使用最少的边将 i 的子树照亮使用的边数.

- f(i, 0) 表示 i 的父亲未放灯，使用最少的边将 i 的子树照亮使用的边数.

- g(i, 1) 表示 i 的父亲放灯，使用最少的边将 i 的子树照亮, 被 2 盏灯同时照亮的边的数量.

- g(i, 0) 表示 i 的父亲不放灯，使用最少的边将 i 的子树照亮, 被 2 盏灯同时照亮的边的数量.

二. 决策：

1. 父亲不放灯.

   则 i 必须放灯，但是儿子就可以放或不放了, 即 f(i, 0) = 1 + ∑ f(son(i), 1或0),取较小的.
   
   g(i, 0) = ∑ g(son(i), 1或0).
   
   注意,当 f(son(i), 0) 比较大的时候 g(i, 0) += g(son(i), 0) + 1;(又多了一条被两盏灯覆盖的边) .
   
   
2. 父亲放灯.

- i 放灯. 这种情况其实和 f(i, 0) 是一样的, 不记录.

- i 不放灯. 则 f(i, 1) = f(son(i), 0), g(i, 1) = g(son(i), 0);

三. 代码:

```
#include<iostream>
#include<cstring>

#define N 1010

using namespace std;

int T,n,m,tot,ans,cnt,f[N][2],g[N][2],vis[N];
int head[N],edge[2*N],nxt[2*N];

void add(int x,int y)
{
	edge[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}

void dfs(int x)
{
	f[x][0]=vis[x]=1;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=edge[i];
		if(vis[y]) continue;
		dfs(y);
		f[x][1]+=f[y][0];
		g[x][1]+=g[y][0];
		if(f[y][0]<f[y][1])
		{
			f[x][0]+=f[y][0];
			g[x][0]+=g[y][0]+1;
		}
		else if(f[y][0]>f[y][1])
		{
			f[x][0]+=f[y][1];
			g[x][0]+=g[y][1];
		}
		else if(g[y][0]+1>g[y][1])
		{
			f[x][0]+=f[y][0];
			g[x][0]+=g[y][0]+1;
		}
		else
		{
			f[x][0]+=f[y][1];
			g[x][0]+=g[y][1];
		} 
	}
}

int main()
{
	cin>>T;
	while(T--)
	{
		memset(head,0,sizeof(head));
		memset(vis,0,sizeof(vis));
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		tot=ans=cnt=0;
		cin>>n>>m;
		for(int i=1,u,v;i<=m;i++)
		{
			cin>>u>>v;
			u++,v++;
			add(u,v),add(v,u);
		}
		for(int i=1;i<=n;i++)
		{
			if(vis[i]) continue;
			dfs(i);
			if(f[i][0]<f[i][1])
			{
				ans+=f[i][0];
				cnt+=g[i][0];
			}
			else if(f[i][0]>f[i][1])
			{
				ans+=f[i][1];
				cnt+=g[i][1];
			}
			else if(g[i][0]>g[i][1])
			{
				ans+=f[i][0];
				cnt+=g[i][0];
			}
			else
			{
				ans+=f[i][1];
				cnt+=g[i][1]; 
			}
		}
		cout<<ans<<" "<<cnt<<" "<<m-cnt<<endl;
	}
	
	return 0;
}
```



---

## 作者：torque (赞：1)

### 链接

先做UVA1292[戳我](https://www.luogu.org/problem/UVA1292)

原题[戳我](https://www.luogu.org/problem/UVA10859)

### 题意

给你一个森林（无向无环图），在一些节点上放灯可以使得与其相邻的边被照亮，要使得所有边被照亮的灯数尽量小，在灯数相同的情况下使得同时被两盏灯照亮的边尽量多

### 题解

### Sol.1

这应该是大多数人都能想到的算法了，就是简单的树形DP（我就这么写的）

不过要注意两点：

1.图是一个森林，要对所有未DP点dfs

2.要在灯少时被两盏灯同时照亮的边尽量多，就再开一个和DP数组类似的数组，同时也使得它尽量大

这里我用的是$d[i][0/1]$代表不选择(0)/选择(1)第$i$个放灯时以i为根的子树中最小的灯的数量

同理$f[i][0/1]$是在$d[i][0/1]$最小的情况下被两盏灯照亮的边数最大值

贴一波代码，仅供参考

```cpp
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define N 2001
#define rnt register int
using namespace std;
struct node{
	int to,nxt;
	node(int X,int Y):to(X),nxt(Y){}
	node(){}
}e[N*2];
int T,n,m,x,y,cnt,ans1,ans2,head[N],f[N][2],dp[N][2];
inline void ins(int x,int y){e[++cnt]=node(y,head[x]);head[x]=cnt;}
void dfs(int u,int v){
	dp[u][1]=1;dp[u][0]=f[u][1]=f[u][0]=0;
	for(rnt i=head[u];i;i=e[i].nxt) if(e[i].to!=v){
		int t=e[i].to;
		dfs(t,u);
		f[u][0]+=f[t][1];
		dp[u][0]+=dp[t][1];
		dp[u][1]+=min(dp[t][0],dp[t][1]);
		if(dp[t][0]<dp[t][1]) f[u][1]+=f[t][0];
		else if(dp[t][0]>dp[t][1]) f[u][1]+=f[t][1]+1;
		else f[u][1]+=max(f[t][0],f[t][1]+1);
	}
}
int main(){
	scanf("%d",&T);
	Work:if(T){
		scanf("%d%d",&n,&m);
		cnt=ans1=ans2=0;
		memset(dp,0,sizeof(dp));
		memset(head,0,sizeof(head));
		for(rnt i=1;i<=m;i=-~i){
			scanf("%d %d",&x,&y);
			ins(x,y);ins(y,x);
		}
		for(rnt i=0;i<n;i=-~i) if(!dp[i][1]){
			dfs(i,-1);
			ans1+=min(dp[i][0],dp[i][1]);
			if(dp[i][1]==dp[i][0]) ans2+=max(f[i][0],f[i][1]);
			else if(dp[i][1]>dp[i][0]) ans2+=f[i][0];
			else ans2+=f[i][1];
		}
		printf("%d %d %d\n",ans1,ans2,m-ans2);
		--T;goto Work;
	}
	return 0;
}
```

### Sol.2

然后来介绍一种鬼畜做法，这里由于我很懒，所以就没有代码辣（勿喷）

我们知道灯的数量对答案状态的影响远大于边数的影响

也就是说无论边数怎么优，只要灯数改变状态就要重新看

那么我们能不能把这两个状态放在一起呢？

假设灯数为$x$，边数为$y$，当前状态记做$ans$

就是要使得$x$对$ans$的影响比$y$对$ans$的影响大

怎么办呢？

不妨另$ans=M*x+y$

$x$表示**放置的灯的数量**，$y$表示**只被一盏灯照亮的边**

其中$M$是一个很大的数，使得$M>>y$

目力观察，发现$M$可以取到$2000$

就是$dp[i][0/1]$存下第$i$个节点不放(0)/放(1)时ans的最小值

是不是很神奇？~~显然不是我能想出来的~~

如果状态为$ans$，那么最终三个问题的答案就分别是$ans/M,m-ans\;mod\;M,ans\;mod\;M$

[![](https://ss3.bdstatic.com/70cFv8Sh_Q1YnxGkpoWK1HF6hhy/it/u=2921431843,3149119026&fm=26&gp=0.jpg)](https://www.luogu.org/blog/oneJURUO/)

---

## 作者：Strelitzia (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/UVA10859)

---

此题重点在转换，我们将使被两盏照亮的边最多，也就是让被一盏灯照亮的边最少。

但我们有个优先的条件，就是放尽量少的灯，开两个 $dp$ 搞有点麻烦，所以我们可以变一下。

我们定义将开最小灯数乘上一个极大值，再加上被一盏灯照亮的边的值，

因为最小灯数已经乘上一个极大值，所以取 $\min$ 的时候吗，优先考虑了最小灯数。

我们定义 $dp_{u,0/1}$ $\operatorname 0$ 为不放灯，$\operatorname 1$ 为放灯，初始化 $dp_{u,1} = 10000$，$dp_{u,0} = 0$。

可得转移式:

$$
dp_{u,0} = \Sigma_{v}^{son(u)}dp_{v,1} + 1
$$

$$
dp_{u,1} = 10000 + \Sigma_{v}^{son(u)}\min(dp_{v,0} + 1,dp_{v,1})
$$

```cpp
#include <cmath>
#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>void read(T &x) {
	T f = 1;x = 0;char s = getchar();
	while(s < '0' || s > '9') {if(s == '-')f = -1;s = getchar();}
	while(s >= '0' && s <= '9') {x = x * 10 + s - '0';s = getchar();}
	x *= f;
}
template<typename T>void print(T x) {
	if(x < 0) putchar('-'),x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
}

const int maxn = 1e5 + 5;
const int base = 1e3;

int nxt[maxn << 1],ver[maxn << 1],head[maxn],tot;
void addEdge(int u,int v) {
    nxt[++ tot] = head[u];ver[tot] = v;head[u] = tot;
}

int n,m,T,vis[maxn],dp[maxn][2],ans;

void dfs(int u,int fa) {
	dp[u][1] = base;
	vis[u] = 1;
	for (int e = head[u] ; e ; e = nxt[e]) {
		int v = ver[e];
		if (v == fa) continue;
		dfs(v,u);
		dp[u][1] += min(dp[v][0] + 1,dp[v][1]);
		dp[u][0] += dp[v][1] + 1;
	}
}

int main () {
	read(T);
	while (T -- > 0) {
		tot = 0;
		memset(head,0,sizeof head);
		memset(vis,0,sizeof vis);
		memset(dp,0,sizeof dp);
		read(n);read(m);
		int u,v;
		for (int i = 1 ; i <= m ; ++ i) {
			read(u);read(v);
			addEdge(u + 1,v + 1);addEdge(v + 1,u + 1);
		}
		ans = 0;
		for (int i = 1 ; i <= n ; ++ i) {
			if (!vis[i]) {
				dfs(i,0);
				ans += min(dp[i][0],dp[i][1]);
			}
		}
		printf("%d %d %d\n",ans / base,m - ans % base,ans % base);
	}
	return 0;
}
```

---

## 作者：mzw2006 (赞：0)

## 前置知识：
树形 $DP$   
简单的哈希思想（或者说是进制思想）**重点** 
## 思考：
拿到本题，如果只求灯的最少数量，就相当于 [没有上司的舞会](https://www.luogu.com.cn/problem/P1352)，相信大家都做过，还有类似的题目 [UVA1292 Strategic game](https://www.luogu.com.cn/problem/UVA1292)。   

考虑如何加上第二层限制：题目要求灯最少的前提下，被两盏灯照亮的边数最多-->被一盏灯照亮的边数最少。一个最多一个最少，显然很难维护和转移，通过这个简单的转换，同时求最小值就比较方便了。

### 重点:

如何把这两个信息并到一个信息并且可以逆着找回原来的信息。上面说的进制思想就是这儿，让第一个数乘以一个大于等于 $1500$ （边数最多为$1500$ ）的数 $M$ ，因为最小灯数和边数都不会大于 $N$ ，所以让第一个信息乘上 $M$ 之后就相当于一个两位的 $M$ 进制数，一位是最小灯数，一位是最小边数，哪位在前都可以，都是求最小，到这里就是本题的重点与思考点，
接下来就和没有上司的舞会基本一样了。答案再根据进制数的性质取出来。
## 细节处理：

 $1.$ 点的编号是从 $0$ 开始的，所以用链式前向星存图的话，$head$ 数组要初始化为 $-1$ ；    
$2.$ $dp$ 数组的初始化：将你定的前边那一位的基值定为 $M$ ；  
$3.$ 多任务问题一定要初始化!!!；          
$4.$ 因为边数小于等于 $n-1$，所以图可能是树或森林，需要一个判断数组来看哪个点有没有被遍历，没有遍历就遍历这个点，标记遍历过程中的点。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=3e3;
int n,head[N],cnt,m,t,ans,f[N][2];
bool v[N];
struct edge
{
	int fr,to;
}e[N<<1];
void add(int x,int y)
{
	e[++cnt].to=y;
	e[cnt].fr=head[x];
	head[x]=cnt;
}
void dfs(int x)
{
	v[x]=1;
	f[x][0]=0;
	f[x][1]=N;
	for(int i=head[x];i!=-1;i=e[i].fr)
	{
		int y=e[i].to;
		if(v[y])
		{
			continue;
		}
		dfs(y);
		f[x][0]+=f[y][1]+1;
		f[x][1]+=min(f[y][1],f[y][0]+1);
	}
}
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		cnt=0;
		ans=0;
		memset(head,-1,sizeof(head));
		memset(v,0,sizeof(v));
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			add(x,y);
			add(y,x);
		}
		for(int i=1;i<=n;i++)
		{
			if(!v[i])
			{
				dfs(i);
				ans+=min(f[i][0],f[i][1]);
			}
		}
		printf("%d %d %d\n",ans/N,m-ans%N,ans%N);
	}
	return 0;
}

---

## 作者：crashed (赞：0)

&emsp;&emsp;**去往[原博客](https://www.cnblogs.com/crashed/p/13404607.html)食用更佳。**
# 题目
&emsp;&emsp;[点这里](https://www.luogu.com.cn/problem/UVA10859)看题目。   
# 分析
&emsp;&emsp;题目本身不难想，只需要在正常的 DP 外多加一个辅助状态即可求解附加问题。   
&emsp;&emsp;这个方法就不细讲了。重点说的是一个比较优雅的做法。   
&emsp;&emsp;考虑我们要最大化被两端覆盖的边的数量，也即是最小化只被一端覆盖的边的数量。现在我们就是同时**最小化两个信息，并且存在优先级**。     
&emsp;&emsp;思考一下哪里存在天然的优先级？**数位**！如果我们把灯的数量压入高位，一端覆盖的边压入低位，对状态取 $\min$ 的时候，我们自然而然地满足了灯数量的优先。    
&emsp;&emsp;具体而言，我们可以找到一个大于 $m$ 的数 $K$ ，并且将信息压成 $K$ 进制的两位数，其中高位存灯、低位存边，然后就有：   
&emsp;&emsp;$f(u,0/1)$：经过信息压缩的意义不变、信息改变的状态；其中高位为**灯数信息**，低位为**覆盖信息**。    
&emsp;&emsp;此时对状态$\pm K$就相当于修改灯的数量，$\pm1$就相当于修改边的数量。     
&emsp;&emsp;然后存在转移：   
$$
\begin{aligned}
f(u,0)&=\sum_v f(v,1)+1\\
f(u,1)&=K+\sum_v \min\{f(v,0)+1,f(v,1)\}
\end{aligned}
$$     
&emsp;&emsp;有意思吧。     
# 代码
&emsp;&emsp;由于 LG 上提交起来~~怪怪的~~，我这里给出 Vjudge 的 AC 记录。    
## ~~粗暴~~版本
&emsp;&emsp;[ AC 记录](https://vjudge.net/solution/26601612/YPxJdOzzj1dKE3qyFn8V)。
```cpp
#include <cstdio>

const int MAXN = 1e5 + 5, MAXM = 1e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MAX( const _T a, const _T b )
{
	return a > b ? a : b;
}

struct edge
{
	int to, nxt;
}Graph[MAXN << 1];

int f[MAXN][2], g[MAXN][2];
int head[MAXN];
int N, M, cnt;
bool vis[MAXN];

void addEdge( const int from, const int to )
{
	Graph[++ cnt].to = to, Graph[cnt].nxt = head[from];
	head[from] = cnt;
}

void DFS( const int u, const int fa )
{
	vis[u] = true;
	f[u][0] = 0, f[u][1] = 1;
	g[u][0] = g[u][1] = 0;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		if( ( v = Graph[i].to ) ^ fa )
		{
			DFS( v, u );
			f[u][0] += f[v][1], g[u][0] += g[v][1];
			if( f[v][1] < f[v][0] ) f[u][1] += f[v][1], g[u][1] += g[v][1] + 1;
			else if( f[v][1] > f[v][0] ) f[u][1] += f[v][0], g[u][1] += g[v][0];
			else f[u][1] += f[v][1], g[u][1] += MAX( g[v][1] + 1, g[v][0] );
		}
}

void clr()
{
	cnt = 0;
	for( int i = 1 ; i <= N ; i ++ ) 
		vis[i] = head[i] = 0;
}

int main()
{
	int T;
	read( T );
	while( T -- )
	{
		int ans1 = 0, ans2 = 0;
		read( N ), read( M ), clr();
		for( int i = 1, a, b ; i <= M ; i ++ )
			read( a ), read( b ), a ++, b ++,
			addEdge( a, b ), addEdge( b, a );
		for( int i = 1 ; i <= N ; i ++ )
			if( ! vis[i] )
			{
				DFS( i, 0 );
				if( f[i][0] < f[i][1] ) ans1 += f[i][0], ans2 += g[i][0];
				else if( f[i][0] > f[i][1] ) ans1 += f[i][1], ans2 += g[i][1];
				else ans1 += f[i][0], ans2 += MAX( g[i][0], g[i][1] );
			}
		write( ans1 ), putchar( ' ' ), write( ans2 ), putchar( ' ' ), write( M - ans2 ), putchar( '\n' );
	}
	return 0;
}
```
## 优雅版本   
&emsp;&emsp;[ AC 记录](https://vjudge.net/solution/26603645)。   
```cpp
#include <cstdio>

const int K = 1e3;
const int MAXN = 1e5 + 5, MAXM = 1e5 + 5;

template<typename _T>
void read( _T &x )
{
	x = 0;char s = getchar();int f = 1;
	while( s > '9' || s < '0' ){if( s == '-' ) f = -1; s = getchar();}
	while( s >= '0' && s <= '9' ){x = ( x << 3 ) + ( x << 1 ) + ( s - '0' ), s = getchar();}
	x *= f;
}

template<typename _T>
void write( _T x )
{
	if( x < 0 ){ putchar( '-' ); x = ( ~ x ) + 1; }
	if( 9 < x ){ write( x / 10 ); }
	putchar( x % 10 + '0' );
}

template<typename _T>
_T MIN( const _T a, const _T b )
{
	return a < b ? a : b;
}

struct edge
{
	int to, nxt;
}Graph[MAXN << 1];

int f[MAXN][2];
int head[MAXN];
int N, M, cnt;
bool vis[MAXN];

void addEdge( const int from, const int to )
{
	Graph[++ cnt].to = to, Graph[cnt].nxt = head[from];
	head[from] = cnt;
}

void DFS( const int u, const int fa )
{
	vis[u] = true;
	f[u][0] = 0, f[u][1] = K;
	for( int i = head[u], v ; i ; i = Graph[i].nxt )
		if( ( v = Graph[i].to ) ^ fa )
		{
			DFS( v, u );
			f[u][0] += f[v][1] + 1;
			f[u][1] += MIN( f[v][1], f[v][0] + 1 );
		}
}

void clr()
{
	cnt = 0;
	for( int i = 1 ; i <= N ; i ++ ) 
		vis[i] = head[i] = 0;
}

int main()
{
	int T;
	read( T );
	while( T -- )
	{
		int ans1 = 0, ans2 = 0;
		read( N ), read( M ), clr();
		for( int i = 1, a, b ; i <= M ; i ++ )
			read( a ), read( b ), a ++, b ++,
			addEdge( a, b ), addEdge( b, a );
		for( int i = 1 ; i <= N ; i ++ )
			if( ! vis[i] )
			{
				DFS( i, 0 );
				int tmp = MIN( f[i][0], f[i][1] );
				ans1 += tmp / K;
				ans2 += tmp % K;
			}
		write( ans1 ), putchar( ' ' ), write( M - ans2 ), putchar( ' ' ), write( ans2 ), putchar( '\n' );
	}
	return 0;
}
```

---

## 作者：clockwhite (赞：0)

# [UVA10859 放置街灯 Placing Lampposts]

## 一.前言

​	啊啊啊啊啊啊我竟然会做树形DP！！！！！（好吧不会其实

有一说一UVA是真的慢奥，放个[题目链接](https://www.luogu.com.cn/problem/UVA10859)	

## 二.思路

​	首先，什么是无向无环图呢？我个人倾向认为是“森林”。很显然的，一**棵树上将任意两个点额外加一条边连起来就会有一个环出现**，而一个图的生成**树**（包含原图所有点）就**是这个图中的最大无向无环图**（毕竟再加边就有环了），但是这道题不是最大，相当于是从树上取几条边删掉，就形成了森林。

​	明确了是森林之后，需要将整个森林分为几颗树来解决。对于一个点及他的子树，**我们设 $f[x][0],g[x][0]$ 分别为 x点无灯时的它的子树（包含它）中最小灯数以及被两个灯所覆盖的道路数。（有灯二维为1）**

​	之所以只记录被两个灯所覆盖的，而不是记录三个值，是因为后两个的和为边的总数。

​	由于每一条边都要有灯，显然的，$f[x][0]$ **只能由 $f[children[x]][1]$ 转移过来。**而 $f[x][1]$ 则有可能由 $f[children[x]][1/0]$转移过来，这个转移**涉及到被两个灯照耀的边数+1，而这个又是第二关键字**。种种因素结合起来，得出一段转移代码。

```c++
for(int i=head[x];i!=-1;i=ne[i]){
		int v=to[i];
		if(v==fa)continue;
		dfs(v,x);
		f[x][0]+=f[v][1];g[x][0]+=g[v][1];
		if(f[v][1]>f[v][0])f[x][1]+=f[v][0],g[x][1]+=g[v][0];
		else if(f[v][1]==f[v][0]&&g[v][0]>g[v][1]+1)
			f[x][1]+=f[v][0],g[x][1]+=g[v][0];
		else f[x][1]+=f[v][1],g[x][1]+=g[v][1]+1;
	}
```

（应该还算简明易懂）

然后设置边界条件为 $f[x][1]=1$ 这是初始值，很显然。

最后整体采用**自叶到根的转移，（DFS），**因为从儿子转移过来，并且儿子的决策对父亲没有影响。因为森林，要对每一个树分别dfs。

## 三.CODE

```cpp
const int MAXN=1005;
int t,n,m,ans1,ans2;
int head[MAXN],to[2*MAXN],ne[2*MAXN],tot;
int f[MAXN][2],g[MAXN][2];
bool vis[MAXN];
void add(int x,int y){
	to[++tot]=y;
	ne[tot]=head[x];
	head[x]=tot;
}
void dfs(int x,int fa){
	vis[x]=1;
	f[x][1]=1;
	for(int i=head[x];i!=-1;i=ne[i]){
		int v=to[i];
		if(v==fa)continue;
		dfs(v,x);
		f[x][0]+=f[v][1];g[x][0]+=g[v][1];
		if(f[v][1]>f[v][0])f[x][1]+=f[v][0],g[x][1]+=g[v][0];
		else if(f[v][1]==f[v][0]&&g[v][0]>g[v][1]+1)
			f[x][1]+=f[v][0],g[x][1]+=g[v][0];
		else f[x][1]+=f[v][1],g[x][1]+=g[v][1]+1;
	}
}
int main(){
	t=read();
	while(t--){
		n=read();m=read();
		ans1=ans2=tot=0;
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
		memset(g,0,sizeof(g));
		memset(f,0,sizeof(f));
		for(int i=1,u,v;i<=m;++i){
			u=read();v=read();
			add(u,v);add(v,u);
		}
		for(int i=0;i<n;++i){
			if(!vis[i]){
				vis[i]=1;
				dfs(i,-1);
				if(f[i][0]<f[i][1])ans1+=f[i][0],ans2+=g[i][0];
				else if(f[i][0]==f[i][1]&&g[i][0]>g[i][1])
					ans1+=f[i][0],ans2+=g[i][0];
				else ans1+=f[i][1],ans2+=g[i][1];
			}
		}
		cout<<ans1<<" "<<ans2<<" "<<m-ans2<<endl;
	}
	return 0;
}
```



---

