# Sheriff's Defense

## 题目描述

给定一张 $n$ 结点 $n - 1$ 条边的有点权的树。初始每个结点都是黑色。

你可以执行任意次以下操作：将一个黑点染成白色，并将所有与它相邻的结点的权值减去 $c$（不包括自己）。

最大化全部白点的权值之和。

## 样例 #1

### 输入

```
5
3 1
2 3 1
1 2
2 3
3 1
3 6 3
1 2
2 3
3 1
-2 -3 -1
1 2
2 3
6 1
5 -4 3 6 7 3
4 1
5 1
3 5
3 6
1 2
8 1
3 5 2 7 8 5 -3 -4
7 3
1 8
4 3
3 5
7 6
8 7
2 1```

### 输出

```
3
8
0
17
26```

# 题解

## 作者：zhlzt (赞：4)

### 题解

树上染色问题，且结点的染色仅关系到儿子和父亲，一眼树形 DP。

不妨设 $dp_{u,0}$ 表示结点 $u$ 为白色时，其子树的最大贡献，$dp_{u,1}$ 表示结点 $u$ 为黑色时，其子树的最大贡献，显然有：

$$\begin{aligned}dp_{u,0}&=a_u+\sum_{v\in\text{son}(u)}\max(dp_{v,1},dp_{v,0}-2\cdot c)\\dp_{u,1}&=\sum_{v\in\text{son}(u)}\max(dp_{v,1},dp_{v,0})\end{aligned}$$

其中 $\text{son(u)}$ 为结点 $u$ 全体儿子结点构成的集合。

于是这题就做完了。

### 代码实现

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=2e5+10;
int n,c,a[maxn];
ll dp[maxn][2];
vector<int>edge[maxn];
void dfs(int u,int dad){
	dp[u][0]=a[u],dp[u][1]=0;
	for(int v:edge[u]){
		if(v==dad) continue;
		dfs(v,u);
		dp[u][0]+=max(dp[v][0]-(c<<1),dp[v][1]);
		dp[u][1]+=max(dp[v][0],dp[v][1]);
	}
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int t;cin>>t;
	while(t--){
		cin>>n>>c;
		for(int i=1;i<=n;i++){
			edge[i].clear(),cin>>a[i];
		}
		int u,v;
		for(int i=1;i<n;i++){
			cin>>u>>v;
			edge[u].push_back(v);
			edge[v].push_back(u);
		}
		dfs(1,0);
		cout<<max(dp[1][0],dp[1][1])<<"\n";
	}
	return 0;
}
```

---

## 作者：Super_Cube (赞：3)

# Solution

树形 dp。设 $dp_{i,0/1}$ 表示在是否选择 $i$ 的情况下，$i$ 及其子树内最大权值和。转移：$dp_{i,0}=\displaystyle\sum_{j\in\operatorname{son}_i}\max(dp_{j,0},dp_{j,1}),dp_{i,1}=a_i+\sum_{j\in\operatorname{son}_i}\max(dp_{j,0},dp_{j,1}-2c)$。随便选根不影响答案。

# Code

```cpp
#include<bits/stdc++.h>
std::vector<int>v[200005];
long long dp[200005][2];
int T,n,m;
void dfs(int p,int dad){
	for(const int&i:v[p])
		if(i!=dad)
			dfs(i,p),
			dp[p][0]+=std::max(dp[i][0],dp[i][1]),
			dp[p][1]+=std::max(dp[i][0],dp[i][1]-(m<<1));
}
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;++i)
			v[i].clear(),dp[i][0]=0,scanf("%lld",&dp[i][1]);
		for(int i=1,x,y;i<n;++i)
			scanf("%d%d",&x,&y),
			v[x].push_back(y),v[y].push_back(x);
		dfs(1,0);
		printf("%lld\n",std::max(dp[1][0],dp[1][1]));
	}
	return 0;
}
```

---

## 作者：thh_loser (赞：1)

# CF2014F Sheriff's Defense 题解

[题目链接](https://www.luogu.com.cn/problem/CF2014F)

## 题意

给定一棵树，每个节点有一个权值，现在可以选择保留某些点，但选择一个点需要将与该点相连的点权值减去 $c$，求保留的权值最大值。

## 思路

显然的树形 dp，我们设计状态 $f_{i,j}$，其中 $i$ 表示 $i$ 号结点，$j$ 为 $0$ 或 $1$，分别表示不选择或选择。

接下来是如何转移，如果不选择该结点，则无论下面结点选不选都不影响，即 $f_{x,0}=\sum\limits_{e}\text{max}(f_{e,0},f_{e,1})$，这里 $e$ 为 $x$ 的子节点。

而如果要选择这个结点，则我们需要考虑子节点的状态。具体的，如果子节点不选，则无影响，而如果选择了子节点，当前结点影响子节点一次，子节点影响当前结点一次，因此需要减去 $2\times c$。即 $f_{x,1}=\sum\limits_{e}\text{max}(f_{e,0},f_{e,1}-2\times c)$。

然后呢，就没有然后了，答案就是 $\text{max}(f_{1,0},f_{1,1})$。



## code

```c++
#include<bits/stdc++.h>
#define N 200010
#define ll long long
using namespace std;
int t,n,c;
int fir[N],ne[N<<1],to[N<<1],tot;
int w[N];
ll f[N][2];
void dfs(int x,int fa=0){
	f[x][1]=w[x];
	for(int i=fir[x];i;i=ne[i]){
		int e=to[i];
		if(e==fa)continue;
		dfs(e,x);
		f[x][0]+=max(f[e][0],f[e][1]);//当前结点不选则下面选不选没有任何影响 
		if(w[e]>=c&&w[x]>=c)f[x][1]+=max(f[e][0],f[e][1]-2*c);//在两个结点都能够减的情况下才能转移 
		else f[x][1]+=f[e][0];//如果不能满足两个结点都减，则只能加上不选的情况 
	}
}
void add(int x,int y){
	ne[++tot]=fir[x];
	fir[x]=tot;
	to[tot]=y;
}
int main(){
	cin>>t;
	while(t--){
		scanf("%d%d",&n,&c);
		for(int i=1;i<=n;i++)scanf("%d",&w[i]);
		for(int i=1,u,v;i<n;i++){
			scanf("%d%d",&u,&v);
			add(u,v);
			add(v,u);
		}
		dfs(1);
		cout<<max(f[1][0],f[1][1])<<"\n"; 
		for(int i=1;i<=n;i++)f[i][0]=f[i][1]=0ll;//多组数据记得初始化 
		for(int i=1;i<=n;i++)fir[i]=0;
		tot=0;
	}
	return 0;
}

```

---

## 作者：OneLeft (赞：0)

## 题意
[题目传送门](https://codeforces.com/problemset/problem/2014/F)

## 思路
这道题要求整颗树上被保护节点的权值和最大，考虑使用动态规划解决。

设 $dp_{u,0/1}$ 表示在以 $u$ 为根节点的子树中，$u$ 不受保护/受到保护的最大权值和，再设 $u$ 的子节点为 $v$，考虑转移：
- $u$ 不受保护，$v$ 的权值不变：
  - $v$ 不受保护，$u$ 的权值不变，故 $v$ 对 $u$ 的贡献为 $dp_{v,0}$。
  - $v$ 受到保护，$u$ 的权值减少了 $c$，但是因为 $u$ 不受保护，不计入答案，故这种情况下 $v$ 对 $u$ 的贡献为 $dp_{v,1}$。
- $u$ 收到保护，$v$ 的权值减少 $c$：
  - $v$ 不受保护，不计入答案，故这种情况下 $v$ 对 $u$ 的贡献为 $dp_{v,0}$。
  - $v$ 受到保护，$u$ 的权值减少 $c$，$u$ 和 $v$ 权值的减少都需要计入答案（$u$ 和 $v$ 受到保护），故这种情况下 $v$ 对 $u$ 的贡献为 $dp_{v,1}-2c$。

最终的转移方程：
$$
dp_{u,0}=\sum\max(dp_{v,0},dp_{v,1})\\
dp_{u,1}=a_u+\sum\max(dp_{v,0},dp_{v,1}-2c)
$$

## 代码
```cpp
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int N=2e5+5;
list<int>edge[N];
void build(int u,int v){edge[u].push_back(v);}
int c,a[N],dp[N][2];
void DFS(int u,int fa)
{
	dp[u][0]=0,dp[u][1]=a[u];
	for(int v:edge[u])
	{
		if(v==fa)continue;
		DFS(v,u);
		dp[u][0]+=max(dp[v][0],dp[v][1]);
		dp[u][1]+=max(dp[v][0],dp[v][1]-2*c);
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int T;
	cin>>T;
	while(T--)
	{
		int n;
		cin>>n>>c;
		for(int i=1;i<=n;i++)cin>>a[i],edge[i].clear();
		for(int i=1,u,v;i<n;i++)cin>>u>>v,build(u,v),build(v,u);
		DFS(1,0);
		cout<<max(dp[1][0],dp[1][1])<<'\n';
	}
	return 0;
}
```

---

## 作者：Michael1234 (赞：0)

- 本题可以使用**树形动态规划**的思路：

- 我们考虑一种状态 $dp_{i,j}(j \in \{0,1\})$。代表**选或不选**第 $i$ 个点时，其子树的最优答案。

- 可以推出转移式（$v$ 为 $u$ 的子节点）：

$$dp_{u,0}=\sum_{v}{\max(dp_{v,0},dp_{v,1})}$$

- 当我们选这个点时，若其子节点**也被选择**，则当前节点和子节点**都会被**减去权值，因此还可推出：

$$dp_{u,1}=a_u+\sum_{v}{\max(dp_{v,0},dp_{v,1}-2\times c)}$$

- **深搜统计**，最终答案就是：

$$\max(dp_{1,0},dp_{1,1})$$

## CODE

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+5;//双倍空间
int t,n,c,u,v,cnt,a[N],dp[N][2],head[N];
struct Edge
{
	int to,nxt;
}edge[N];
inline void add(int u,int v)
{
	edge[++cnt].to=v;
	edge[cnt].nxt=head[u];
	head[u]=cnt;
	return;
}
inline void dfs(int u,int f)
{
	dp[u][1]=a[u];
	for(int i=head[u];i;i=edge[i].nxt)
	{
		int v=edge[i].to;
		if(f==v)
		{
			continue;
		}
		dfs(v,u);
		dp[u][0]+=max(dp[v][0],dp[v][1]);
		dp[u][1]+=max(dp[v][0],dp[v][1]-2*c);//转移
	}
	return;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	for(cin>>t;t;t--)
	{
		cin>>n>>c;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=1;i<n;i++)
		{
			cin>>u>>v;
			add(u,v);
			add(v,u);//双向建边
		}
		dfs(1,0);
		cout<<max(dp[1][0],dp[1][1])<<"\n";
		for(int i=1;i<=cnt;i++)
		{
			edge[i]=(Edge){0,0};
		}
		cnt=0;
		for(int i=1;i<=n;i++)
		{
			dp[i][0]=0;
			dp[i][1]=0;
			head[i]=0;
		}//清空
	}
	exit(0);
}
```

---

## 作者：liuli688 (赞：0)

声明：由于 CF RemoteJudge 炸了，所以我在洛谷上并没有通过此题（但是在 CF 上 AC）。
### 思路
树上问题，很容易想到树形 DP。

设 $f _ {u, 0}$ 表示结点 $u$ 为黑色的情况下以 $u$ 为根的子树的白点权值和，$f _ {u, 1}$ 表示结点 $u$ 为白色的情况。

考虑状态转移方程。以任意一个点进行 DFS，设当前结点为 $u$，$u$ 的子结点为 $v$，则转移方程为：
$$\begin{cases}
f _ {u, 0} = \sum \max(f _ {v, 0}, f _ {v, 1}) \\
f _ {u, 1} = a _ u + \sum \max(f _ {v, 0}, f _ {v, 1} - c \cdot 2)
\end{cases}$$
其中 $a _ i$ 表示结点 $i$ 的点权。

解释：若不将点 $u$ 染白，则无论子结点 $v$ 是黑是白都不需要因为 $u \to v$ 这条边而减去 $u$ 或 $v$ 的点权（可能因为 $v$ 的子结点而减 $v$ 的点权，但是已经在计算 $f _ v$ 时考虑过了）。因此可以在 $v$ 的两种状态中取最大。但是如果 $u$ 是白色，则 $v$ 也是白色时需要减两个 $c$（因为 $u \to v$ 减一次， $v \to u$ 减一次）。

最终答案是在根节点的两种状态中取最大。
### 代码
```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
using ll = long long;

constexpr int N = 2e5 + 1;
std::vector<int> e[N];
int T, n, c, a[N];
ll f[N][2];

void dfs(int u, int fa)
{
    f[u][0] = 0;
    f[u][1] = a[u];
    for (register auto v : e[u])
    {
        if (v == fa)
          	continue;
        dfs(v, u);
        f[u][0] += std::max(f[v][0], f[v][1]);
        f[u][1] += std::max(f[v][0], f[v][1] - (c << 1));
        }
    }
     
signed main()
{
    for (scanf("%d", &T); T--; )
    {
        scanf("%d%d", &n, &c);
        for (register int i = 1; i <= n; ++i)
          	e[i].clear();
        for (register int i = 1; i <= n; ++i)
          	scanf("%d", a + i);
        for (register int u, v; --n; )
        {
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dfs(1, -1);
        printf("%lld\n", std::max(f[1][0], f[1][1]));
    }
    return 0;
}
```
注意有可能会爆 int 呦！

---

## 作者：Hide_In_The_Shadow (赞：0)

树形 DP。

注意到当一个点不选时，不会对最终答案造成任何影响，任意两个相邻点都选时，答案 $-2\times c$。

定义 $dp[i][1/0]$ 表示第 $i$ 个点选或者不选时以它为根的子树的最大答案，并且初始化 $dp[i][1]=a[i]$。那么对于它的儿子 $j$，我们有如下转移方程：
$$
dp[i][0]=dp[i][0]+\max(dp[j][0],dp[j][1])\\
dp[i][1]=dp[i][1]+\max(dp[j][0],dp[j][1]-2\times c)\\
$$


最终答案就是 $\max (dp[1][0],dp[1][1])$。时间复杂度 $O(n)$。

```c++
#include<bits/stdc++.h>
#define ll long long
#define pii pair<int,int>
#define fio std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
using namespace std;
template<typename T>inline void read(T &x){
	x=0;
	char c=getchar();
	T ret=0;
	while(!isdigit(c))ret|=!(c^'-'),c=getchar();
	while(isdigit(c))x=(x<<3)+(x<<1)+(c^48),c=getchar();
	if(ret)x=(~x)+1;
	return;
}
template<typename T>inline void print(T x){
	if(x<0)putchar('-'),x=(~x)+1;
	if(x>9)print(x/10);
	putchar((x-x/10*10)^48);
	return;
}
template<typename T>inline void wr1(T x){
	print(x);
	putchar(' ');
	return;
}
template<typename T>inline void wr2(T x){
	print(x);
	putchar('\n');
	return;
}
int t,n,tot,head[214514];
struct edg
{
    int v,nex;
}e[214514<<1];
void add(int u,int v){
    e[++tot].v=v;
    e[tot].nex=head[u];
    head[u]=tot;
}
bool vis[214514];
ll c,a[214514],dp[214514][2];
void dfs(int x){
    dp[x][1]=a[x];
    vis[x]=1;
    for(int i=head[x];i;i=e[i].nex){
        int v=e[i].v;
        if(vis[v])continue;
        dfs(v);
        dp[x][0]+=max(dp[v][0],dp[v][1]);
        dp[x][1]+=max(dp[v][0],dp[v][1]-c*2);
    }
    
}
int main(){
	read(t);
    while(t--){
        read(n);
        read(c);
        tot=0;
        for(int i=1;i<=n;++i){
            read(a[i]);
            vis[i]=false;
            head[i]=dp[i][0]=dp[i][1]=0;
        }
        for(int i=1;i<n;++i){
            int u,v;
            read(u);
            read(v);
            add(u,v);
            add(v,u);
        }
        dfs(1);
        wr2(max(dp[1][0],dp[1][1]));
    }
	return 0;
}
```

---

## 作者：xAlec (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF2014F)

## solution

显然这是树形 $\text{dp}$。

记 $dp_{u,1/0}$ 表示是否选择根为 $u$ 的子树的白点最大权值，初始化有 $dp_{i,0} = 0,dp_{i,1} = val_i,i \in [1,n]$，可以得到以下转移方程：

>$dp_{u,0} = \displaystyle\max_{v \in son_u}\{dp_{v,0},dp_{v,1}\}$
>
>$dp_{u,1} = \displaystyle\max_{v \in son_u}\{dp_{v,0},dp_{v,1} - 2c\}$
>

答案即为 $\max\{dp_{root,0},dp_{root,1}\}$。

## code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN = 2e5 + 10;
int T,n,c,val[MAXN];
int idx,head[MAXN],dp[MAXN][2];
struct node{
	int v,nxt;
}tree[MAXN << 1];

inline void add(int u,int v)
{
	tree[++ idx].v = v;
	tree[idx].nxt = head[u];
	head[u] = idx;
}

inline void Dp(int u,int fa)
{
	for(int i = head[u];i;i = tree[i].nxt)
	{
		int v = tree[i].v;
		if(v == fa) continue;
		Dp(v,u);
		dp[u][0] += max(dp[v][0],dp[v][1]);
		dp[u][1] += max(dp[v][0],dp[v][1] - c * 2);
	}
}

signed main()
{
	scanf("%lld",&T);
	while(T --)
	{
		for(int i = 1;i <= idx;i ++)
			tree[i].v = tree[i].nxt = head[i] = 0;
		idx = 0;
		scanf("%lld %lld",&n,&c);
		for(int i = 1;i <= n;i ++)
		{
			scanf("%lld",&val[i]);
			dp[i][1] = val[i];
			dp[i][0] = 0;
		}
		for(int i = 1;i < n;i ++)
		{
			int u,v;
			scanf("%lld %lld",&u,&v);
			add(u,v),add(v,u);
		}
		Dp(1,0);
		printf("%lld\n",max(dp[1][0],dp[1][1]));
	}
	return 0;
}
```

---

## 作者：ivyjiao (赞：0)

如果不选当前节点：

$$dp_{u,0}=\sum_{v~\text{is a son of}~u}\max(dp_{v,0},dp_{v,1})$$

如果选当前节点：

$$dp_{u,1}=a_u+\sum_{v~\text{is a son of}~u}\max(dp_{v,0},dp_{v,1}-2\times c)$$

因为选子节点影响当前节点和选当前节点影响子节点的影响都需要计算，所以 $-2\times c$。如果子节点不选，那么子节点会被摧毁，不计入答案。

答案是 $\max(dp_{1,0},dp_{1,1})$。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+1;
int t,n,c,a[N],u,v,dp[N][2];
vector<int>G[N];
void dfs(int u,int fa){
    dp[u][0]=0;
    dp[u][1]=a[u];
    for(int i=0;i<G[u].size();i++){
        int v=G[u][i];
        if(v==fa) continue;
        dfs(v,u);
        dp[u][0]+=max(dp[v][0],dp[v][1]);
        dp[u][1]+=max(dp[v][0],dp[v][1]-2*c);
    }
}
signed main(){
    cin>>t;
    while(t--){
        cin>>n>>c;
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<=n;i++) cin>>a[i];
        for(int i=1;i<n;i++){
            cin>>u>>v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        dfs(1,0);
        cout<<max(dp[1][0],dp[1][1])<<endl;
    }
}
```

---

## 作者：sad_lin (赞：0)

明显树形 dp 题，设状态 $f_{i,0/1}$ 为将当前节点不染/染成白色的最大权值和，那对于不染这个节点可以直接转移 $f_{i,0}=\sum_{j\in son_i} max{\{  f_{j,0},f_{j,1} \}}$。

否则染这个节点的话，儿子不染色则可以直接转移，儿子染色的需要减去 $2c$（儿子节点染色减 $c$，当前节点染色减 $c$，总权值和减 $2c$），转移方程有 $f_{i,1}=\sum_{j\in son_i} max{\{  f_{j,0},f_{j,1}-2c \}}$。

```cpp
#include <bits/stdc++.h>
#define int long long
#define ls p<<1
#define rs p<<1|1 
#define re register 
const int N=2e5+10;
const int mod=998244353;
using namespace std;

int n,c;
int f[N][3];
vector<int> v[N];

void dfs(int x,int fa){
	for(int y:v[x]){
		if(y==fa){
			continue;
		}
		dfs(y,x);
		f[x][0]+=max(f[y][0],f[y][1]);
		f[x][1]+=max(f[y][0],f[y][1]-2*c);	
	}
}

void solve(){
	cin>>n>>c;
	
	for(int i=1;i<=n;i++){
		cin>>f[i][1];
	}
	
	for(int i=1;i<=n-1;i++){
		int u,vv;
		cin>>u>>vv;
		v[u].push_back(vv);
		v[vv].push_back(u);
	}
	
	dfs(1,0);
	
	cout<<max(f[1][1],f[1][0])<<"\n";
	
	for(int i=1;i<=n;i++){
		f[i][0]=f[i][1]=0;
		v[i].clear();
	}
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr); 
	int t;
	cin>>t;
	while(t--){
		solve();
	}
	return 0;
}
```

---

## 作者：xuan_never (赞：0)

# 题目大意
给出一棵**树**，每个节点都有一个价值。要求在树上选取若干个节点，与**每个选择节点**相邻的节点都要扣除一定的价值（价值**可以为负**），求选择的节点的价值的最大和。

# 思路做法
任选一点作根，考虑树上dp。  
设计状态 $f_{u,0}$ 表示在以 $u$ 为根的子树下，**不选择** $u$ 所能获得的最大价值，初始值为 $0$；  
$f_{u,1}$ 表示在以 $u$ 为根的子树下，**选择** $u$ 所能获得的最大价值，初始值为 $a_u$。

如果子节点 $v$ 未被选择，则无论其扣费与否，都不会对结果产生影响，所以两种情况都可以直接加上 $f_{v,0}$。

在不选择 $u$ 的情况下，就算子节点 $v$ 被选择，也不会引起 $u$ 扣费对结果的影响，所以有
$$f_{u,0}=f_{u,0}+\max(f_{v,0},f_{v,1})$$
。

而在选择 $u$ 时，选择了子节点 $v$ 意味着会引起 $u,v$ 各一次影响结果的扣费，所以有
$$f_{u,1}=f_{u,1}+\max(f_{v,0},f_{v,1}-c\times2)$$
。

状态转移方程就出来了。

# 代码
别忘了多测时要清空图。
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int T, n, u, v;
ll c, a[200005], f[200005][2];
vector<int> G[200005];
void dfs(int u, int fa) {
	f[u][0] = 0;
	f[u][1] = a[u];
	for (int v : G[u]) {
		if (v == fa) continue;
		dfs(v, u);
		f[u][0] += max(f[v][0], f[v][1]);
		f[u][1] += max(f[v][0], f[v][1] - c * 2);
	}
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
	for (cin >> T; T--; ) {
		cin >> n >> c;
		for (int i = 1; i <= n; ++i)
			cin >> a[i], G[i].clear();
		for (int i = 1; i < n; ++i)
			cin >> u >> v,
			G[u].emplace_back(v),
			G[v].emplace_back(u);
		dfs(1, 0);
		cout << max(f[1][0], f[1][1]) << '\n';
	}
	return 0;
}
```

---

