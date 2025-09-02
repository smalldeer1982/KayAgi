# [ABC188E] Peddler

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc188/tasks/abc188_e

高橋国には、町 $ 1 $ から町 $ N $ までの $ N $ 個の町があります。  
 また、この国には道 $ 1 $ から道 $ M $ までの $ M $ 本の道があります。道 $ i $ を使うと、町 $ X_i $ から町 $ Y_i $ へ移動することができます。逆向きへは移動できません。ここで $ X_i\ <\ Y_i $ であることが保証されます。  
 この国では金の取引が盛んであり、町 $ i $ では、金 $ 1\,\mathrm{kg} $ を $ A_i $ 円で売ったり買ったりすることができます。

旅商人である高橋君は、高橋国内のある町で金を $ 1\,\mathrm{kg} $ だけ買い、いくつかの道を使った後、**買った町とは別の町で**金を $ 1\,\mathrm{kg} $ だけ売ろうと考えています。  
 このとき、高橋君の利益 (すなわち $ ( $金を売った価格$ )\ -\ ( $金を買った価格$ ) $) として考えられる最大値を求めてください。

## 说明/提示

### 制約

- $ 2\ \le\ N\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ M\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ 10^9 $
- $ 1\ \le\ X_i\ \lt\ Y_i\ \le\ N $
- $ (X_i,\ Y_i)\ \neq\ (X_j,\ Y_j)\ (i\ \neq\ j) $
- 入力に含まれる値は全て整数

### Sample Explanation 1

以下のようにして利益 $ 3 $ 円を達成できます。 - 町 $ 1 $ で $ 2 $ 円で金 $ 1\,\mathrm{kg} $ を買う - 道 $ 2 $ を使って町 $ 2 $ に移動する - 道 $ 1 $ を使って町 $ 4 $ に移動する - 町 $ 4 $ で $ 5 $ 円で金 $ 1\,\mathrm{kg} $ を売る

### Sample Explanation 2

以下のようにして利益 $ 10 $ 円を達成できます。 - 町 $ 2 $ で $ 8 $ 円で金 $ 1\,\mathrm{kg} $ を買う - 道 $ 1 $ を使って町 $ 4 $ に移動する - 道 $ 3 $ を使って町 $ 5 $ に移動する - 町 $ 5 $ で $ 18 $ 円で金 $ 1\,\mathrm{kg} $ を売る

### Sample Explanation 3

金を買った町で売ることはできないため、答えが負になる可能性があることに注意してください。

## 样例 #1

### 输入

```
4 3
2 3 1 5
2 4
1 2
1 3```

### 输出

```
3```

## 样例 #2

### 输入

```
5 5
13 8 3 15 18
2 4
1 2
4 5
2 3
1 3```

### 输出

```
10```

## 样例 #3

### 输入

```
3 1
1 100 1
2 3```

### 输出

```
-99```

# 题解

## 作者：loser_seele (赞：2)

因为题目有一个边默认从编号小的点连到编号大的点的限制，所以这张图其实是一张有向无环图。

于是考虑用 dfs 求出所有的点能到达的点的最大点权，这个可以用一个简单的 DAG 上 DP 实现，在 DP 时顺便记录下当前最大值即可。

然后遍历整张图，对所有点预处理最大点权后直接更新答案即可。注意特判孤立点的情况。

时间复杂度 $ \mathcal{O}(n+m) $，可以通过。

代码：

```cpp
#import <bits/stdc++.h>
#define int long long
const int MAX_SIZE = 2e5+5;
using namespace std;
int n, m, tmp, ans=-1e18;
int x, y;
bool start;
vector<int> a(MAX_SIZE), dp(MAX_SIZE), G[MAX_SIZE];
bitset<MAX_SIZE> vis;
void DFS(int now)
{
    if (vis[now]==0 && start==1)
    {
        start=0;
        dp[now]=0;
        vis[now]=1;
    }
    else if (vis[now]==0)
    {
        dp[now]=a[now];
        vis[now]=1;
    }
    else
    return;
    for (auto x : G[now])
    {
        DFS(x);
        dp[now]=max(dp[now], dp[x]);
    }
} 
signed main()
{
    cin >> n >> m;
    for (int i=1 ; i<=n ; i++)
    {
        cin >> tmp;
        a[i]=tmp;
    }
    for (int i=0 ; i<m ; i++)
    {
        cin >> x >> y;
        G[x].push_back(y);
    }
    for (int i=1 ; i<=n ; i++)
        if (!vis[i])
        {
            start=1;
            DFS(i);
        }
        for (int i=1 ; i<=n ; i++)
            if (G[i].size())
                ans=max(ans, dp[i]-a[i]);
        cout<<ans;
}
```


---

## 作者：xuchuhan (赞：1)

考虑对于每个点 $i$ 求出 $x$，表示能到达这个点的所有点的最小点权。那么在 $i$ 卖出黄金的最大价格即 $a_i-x$。

建反图对于每个点 $i$ 跑 DFS 求出 $x$ 即可实现，但是这样做是 $\mathcal{O(n^2)}$ 的，考虑记忆化。设 $dp_i$ 表示能到达点 $i$ 的所有点的最小点权（和 $x$ 的含义是一样的）。那么对于原图中边 $to\to x$（反图中边 $x\to to$），易得转移 $dp_x\leftarrow \min(dp_{to},a_{to})$。

记忆化后复杂度降为 $\mathcal{O(n)}$，可以通过本题。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+5,inf=0x3f3f3f3f3f3f3f3f3f3f3f;
int n,m,ans,a[N],dp[N];
vector<int>v[N];
int DFS(int x){
	if(dp[x]!=inf)return dp[x];
	int tmp=inf;
	for(int i=0;i<v[x].size();i++)tmp=min(tmp,min(DFS(v[x][i]),a[v[x][i]]));
	return dp[x]=tmp;
}
signed main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1,x,y;i<=m;i++)cin>>x>>y,v[y].push_back(x);
	memset(dp,0x3f,sizeof(dp));
	ans=-inf;for(int i=1;i<=n;i++)ans=max(ans,a[i]-DFS(i));
	cout<<ans;
	return 0;
}
```

---

## 作者：lyh0217 (赞：1)

### 题目大意

给定一个 $n$ 个点 $m$ 条边的有向无环图，寻找一个点对 $(x,y)$ 使得能从 $x$ 出发到达到达 $y$，**且 $x  \neq y$**，点对 $(x,y)$ 的价值为 $dis_x - dis_y$，其中 $dis$ 数组表示每个点的点权，求最大的点对价值？

### 思路

~~我太唐了没看到有向无环图这个条件导致我写了个很唐的方法。~~

我们考虑先进行暴力模拟，从每个点开始搜索，令这个点为答案点对的后一项，找到它能到达的所有点的点权最大值，再让后者减去前者的点权即可。时间复杂度为 $O(n^2)$，不可通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[200005];
int dis[200005],a[200005],rt;
vector<int>v[200005];
void dfs(int x)
{
	for(auto i:v[x])
	{
		if(!vis[i])
		{
			dis[rt]=max(dis[rt],a[i]);//更新可以到达的点的最大值
			vis[i]=1;
			dfs(i);
		}
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		dis[i]=INT_MIN;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		v[x].push_back(y);//重要的事情说三遍！单向边！单向边！单向边！
	}
	int ans=INT_MIN;
	for(int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));//记得清空OvO
		rt=i;
		vis[i]=1;
		dfs(i);
		if(dis[i]!=INT_MIN)//如果从i开始能到达一个点
		ans=max(ans,dis[i]-a[i]);
	}
	printf("%d",ans);
	return 0;
}
```

[然鹅，甚至只T了2个点](https://atcoder.jp/contests/abc188/submissions/61935269)

考虑优化，发现有些点在更新其他点的答案的时候重复算了，考虑记忆化搜索。

记忆化写的有点丑见谅QwQ。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[200005];
int dis[200005],a[200005];
vector<int>v[200005];
void dfs(int x)
{
	for(auto i:v[x])
	{
		if(!vis[i])//如果这个点还未查找过答案
		{
			vis[i]=1;
			dfs(i);
			dis[x]=max(dis[x],max(dis[i],a[i]));
		}
		else//直接更新答案
		{
			dis[x]=max(dis[x],max(dis[i],a[i]));
		}
	}
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&a[i]);
		dis[i]=INT_MIN;
	}
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		v[x].push_back(y);//重要的事情说三遍！单向边！单向边！单向边！
	}
	int ans=INT_MIN;
	for(int i=1;i<=n;i++)
	{
		dfs(i);
		if(dis[i]!=INT_MIN)//如果从i开始能到达一个点
		ans=max(ans,dis[i]-a[i]);
	}
	printf("%d",ans);
	return 0;
}
```

[评测记录](https://atcoder.jp/contests/abc188/submissions/61936136)

---

## 作者：_shine_ (赞：1)

观察题目，可发现本题的重点显然是在有向无环图中找到一个以下满足条件中的黄金价格最小的，最高的城市，使得小的能到达大的城市，使得利润最大。

因为 $2\le n \le 2\times10^5$ ,显然不能去暴力找条件符合的点，时间显然超时，考虑使用其它方法。

设 $f_i$ 表示可以到达点 $i$，并且黄金价最低的城市的价格，显然，答案显然为最小的 $a_{y_i}-f_{x_i}$，而 $f_{y_i}$ 显然等于 $a_{y_i}$ 和 $f_{x_i}$ 中更小的那个，则显然对输入的建边操作进行排序，把 $x_i$ 小的排在前面，这样才能使得 $f_{x_i}$ 能及时更新。
### code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+10;
int n,m;
int a[maxn];
struct node{
	int l,r;
}b[maxn];
int f[maxn];
int ans=INT_MIN;
bool cmp(node c,node d){
	if(c.l!=d.l)return c.l<d.l;
	else return c.r<d.r;
}
signed main(){
	cin >> n >> m;
	for(int i=1;i<=n;++i){
		cin >> a[i];
	}
	for(int i=1;i<=m;++i){
		cin >> b[i].l >> b[i].r;
	}
	sort(b+1,b+m+1,[](node c,node d){if(c.l!=d.l)return c.l<d.l;else return c.r<d.r;});
//	for(int i=1;i<=m;++i){
//		cout << b[i].l << " " << b[i].r << endl;
//	}
	for(int i=1;i<=n;++i){
		f[i]=a[i];
	}
	for(int i=1;i<=m;++i){
		f[b[i].r]=min(f[b[i].l],f[b[i].r]);//更新f_i
		ans=max(ans,a[b[i].r]-f[b[i].l]);//更新答案
	}
	cout << ans << endl;
	return 0;
}
```


---

## 作者：wwt100127 (赞：0)

## 思路
第一眼看过去以为是[最优贸易](https://www.luogu.com.cn/problem/P1073)。

注意到 $X_i < Y_i$，也就是说这是一个拓扑图。

记 $P_i$ 表示所有能到达 $i$ 的点（不包括 $i$）的 $A_i$ 的最小值。

一边跑拓扑排序一边求 $P_i$ 即可。

## 代码
```cpp
const int N=2e5+5;
const int INF=0x3f3f3f3f3f3f3f3fll;
int n,m,a[N],deg[N];

namespace Graph
{
	int head[N],tot;
	struct edge
	{
		int v,next;
	}e[N<<1];
	void G_init()
	{
		memset(head,-1,sizeof(head));
		tot=-1;
	}
	void add(int u,int v)
	{
		e[++tot]=(edge){v,head[u]};
		head[u]=tot;
		deg[v]++;
	}
	void add_edge(int u,int v)
	{
		add(u,v),add(v,u);
	}
} using namespace Graph;

int P[N];
int Topsort()
{
	int i,ans=-INF;
	memset(P,0x3f,sizeof(P));
	queue<int> q;
	for(i=1;i<=n;i++)
	{
		if(deg[i]==0)
		q.push(i);
	}
	while(q.size())
	{
		int x=q.front();
		q.pop();
		ans=max(ans,a[x]-P[x]);
		P[x]=min(P[x],a[x]);
		for(i=head[x];~i;i=e[i].next)
		{
			int y=e[i].v;
			P[y]=min(P[y],P[x]);
			if(--deg[y]==0)
			q.push(y);
		}
	}
	return ans;
}

bool Ending;
signed main()
{
	int i,u,v;
	read(n,m);
	G_init();
	for(i=1;i<=n;i++) a[i]=read();
	for(i=1;i<=m;i++)
	{
		read(u,v);
		add(u,v);
	}
	write(Topsort(),'\n');
	return 0;
}
```

---

## 作者：copper_ingot (赞：0)

简要题意：给定一个 $n$ 个节点的有向无环图 $G$，以及数组 $a$，求满足下列条件的最大的 $a_j-a_i$ 的值：

- $1 \le i,j \le n$ 且 $i \neq j$。

- 从 $i$ 开始走可以到达 $j$。

$G$ 是个 DAG，所以可以在 DAG 上跑 DP 求出每个节点 $i$ 可以到达的最大 $a_j$，记为 $dp_i$。然后取最大的 $dp_i - a_i$。

因为必须交易，所以利润可能为负，答案要初始化为 $-\inf$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
int n, m, a[200001], dp[200001], vis[200001], maxn = -1e9;
vector<int> g[200001];
void dfs(int u){
	for (int i = 0; i < g[u].size(); i++){
		int v = g[u][i];
		if (!vis[v]){vis[v] = 1; dfs(v);}
		dp[u] = max(dp[u], max(dp[v], a[v]));
	}
}
signed main(){
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
	for (int i = 1; i <= m; i++){
		int u, v; scanf("%d%d", &u, &v);
		g[u].push_back(v);
	}
	for (int i = 1; i <= n; i++){
		if (!vis[i]) dfs(i);
		if (dp[i]) maxn = max(maxn, dp[i] - a[i]);
	}
	printf("%d\n", maxn);
	return 0;
}
```

---

## 作者：xmy201315 (赞：0)

# Peddler
## 思路分析
这道题是个 dp 题。我们定义一个数组 $f$，$f_i$ 表示从 $i$ 前面的点走到 $i$ 这个点，我们假设买黄金一定要在前面买，那么最便宜是多少钱。

我们假设在 l 这个点把黄金卖掉，那么我们赚的钱就是 $a_l - f_i$。

但是我们也不确定黄金在哪里卖最优，所以我们让 $l$ 从 $1$ 枚举到 $n$，求出 $a_l - f_i$ 的最大值就可以了。

### 现在问题就来了，$f_i$ 怎么求呢？ 

现在假设有一些点能走到 $i$ 这个点，能么假设某个点是 $j$，那么黄金有可能是在 $j$ 前面买的，最便宜的就是 $f_j$ 块钱。

但是 $j$ 这个点也可以买黄金，那么从 $j$ 点走过来的黄金最便宜是 $\min(f_j,a_j)$ 。

那么到 $i$ 这边最便宜是对于每个 $j$ 进行一次 $\min(f_j,a_j)$ 后。

然后把这几个数再取出一个最小值，就是 $f_i$ 的值了。这样就可以算出 $a_l - f_i$ 的最大值了 。

时间复杂度是 $\mathcal O(n+m)$,因为求出 $f$ 所有数的时间复杂度是 $\mathcal O(n+m)$,我们求出 $a_l - f_i$ 的时间复杂度是 $\mathcal O(n)$ 的，合并起来就是 $\mathcal O(n+m)$ 。

很多人可能做这道题用到了拓扑排序，但实际上用不到，因为只能从编号小的走到编号大的。你写拓扑排序反而会加大你的工作量。

光看文字描述可能不太理解，那么让我们看看代码理解吧！

**AC CODE:**
``` cpp
#include <bits/stdc++.h> 
using namespace std;
int n , m,a[200010] ,f[200010];
vector<int> edges[200010];
int main(){
	scanf("%d%d" , &n , &m);
	for(int i = 1;i <= n;i++)
		scanf("%d" , &a[i]);
	for(int i = 1;i <= m;i++){
		int x , y;
		scanf("%d%d" , &x , &y);
		edges[y].push_back(x);  //存图 
	}
	if(n == 2){// 进行特判 
		printf("%d\n" , a[2]-a[1]);
		return 0;
	}
	for(int i = 1;i <= n;i++)f[i] = 1<<30;
	for(int i = 1;i <= n;i++)
		for(auto x : edges[i])
			f[i] = min(f[i] , min(f[x] , a[x]));//详见题解 
	int ans = -(1<<30);
	for(int i = 1;i <= n; i++)
		ans = max(ans , a[i] - f[i]);
	printf("%d\n" , ans);
}
```

---

## 作者：lqsy002 (赞：0)

[题目链接](https://www.luogu.com.cn/problem/AT_abc188_e)。

## 解题思路

利润最大的条件是找到满足条件且黄金价格最小、最高的城市，使得价格最小的到达价格最大的城市。

如果 $u$ 能够到达 $v$ 且是黄金价格最小的城市，$dp_u$ 为黄金价格，则有 $ans \gets \min( a_{y_u} - dp_{x_u} )$，并且 $dp_{y_u} \gets  \min( a_{y_u} , dp_{x_u} )$。

## 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 200005
using namespace std;
int n,m,a[maxn];
int ans=-2e9,dp[maxn];
struct edge{
	int u;
	int v;
	bool operator<(const edge &other)const{
		if(v==other.v)
			return u<other.u;
		return v<other.v;
	}
}e[maxn]; 
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;++i) 
		cin>>a[i];
	for(int i=1,x,y;i<=m;++i){
		cin>>x>>y;
		e[i]={x,y};
	}
	sort(e+1,e+1+m);
	memset(dp,0x3f,sizeof(dp));
	for(int i=1;i<=n;++i) 
		dp[i]=a[i];
	for(int i=1;i<=m;++i){
		ans=max(ans,a[e[i].v]-dp[e[i].u]);
		dp[e[i].v]=min(dp[e[i].v],dp[e[i].u]);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：sunzz3183 (赞：0)

# [ABC188E] Peddler题解

## 题意

题目翻译说的很清楚了，这里就不说了。

## 分析

注意两个东西：

1. $X_i<Y_i$；

2. 必须只买一次，也只卖一次。

第二个很简单，就是告诉你必须要**买卖**。

但是第一个就是我们这道题的关键：它可以从**线性的最小的点买到最大的点**。

我们把每条边 $u,v$ 按照 $v$ 的编号大小从小到大排序，然后我们遍历时，$u$ 这个点一定被处理过了，这就保证了方法的正确性。

然后我们去处理一个东西 $mia_u$，意思是以 $u$ 这个点结尾的路径上的最小值，所以当前点 $v$ 卖出的最大价值就是 $a_v-mia_u$，统计答案的时候对于所有的价值取最大值就行。

时间复杂度 $O(N\log N)$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    char ch=getchar();int x=0;bool f=1;
    while(ch<'0'||'9'<ch){if(ch=='-')f=0;ch=getchar();}
    while('0'<=ch&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
    return f?x:-x;
}
const int N=2e5+5,M=2e5+5,inf=0x3f3f3f3f3f3f3f3f;
struct qwq{
    int l,r;
}q[N];
int n,m,ans=-inf,a[N],mia[N];
signed main(){
    n=read();m=read();
    for(int i=1;i<=n;i++)mia[i]=a[i]=read();
    for(int i=1;i<=m;i++)q[i]={read(),read()};
    sort(q+1,q+m+1,[](qwq x,qwq y){return x.r==y.r?x.l<y.l:x.r<y.r;});//排序
    for(int i=1;i<=m;i++)ans=max(ans,a[q[i].r]-mia[q[i].l]),mia[q[i].r]=min(mia[q[i].r],mia[q[i].l]);//如题意
    printf("%lld\n",ans);
    return 0;
}
```


---

