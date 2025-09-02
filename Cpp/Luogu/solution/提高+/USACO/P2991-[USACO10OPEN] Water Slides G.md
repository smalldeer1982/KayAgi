# [USACO10OPEN] Water Slides G

## 题目描述

受到秘鲁马丘比丘新建水上乐园的启发，约翰农夫决定为奶牛们建造一个水上乐园。其最大的吸引力将是一个设计独特的巨型滑梯。超级滑梯由 E (1 <= E <= 150,000) 个迷你滑梯连接 V (2 <= V <= 50,000) 个小水池，这些水池被方便地标记为 1 到 V。每个迷你滑梯必须按照正确的方向滑行，不能逆向滑行。奶牛们从编号为 1 的水池出发，依次滑过迷你滑梯，直到到达编号为 V 的终点水池。每个水池（除了第一个水池 1）至少有一个迷你滑梯进入它，（除了最后一个水池 V）至少有一个（不同的）迷你滑梯从它出去。

此外，奶牛可以通过一系列迷你滑梯从任何水池到达终点水池 V。最后，由于这是一个滑梯，不可能离开一个水池后，再经过一系列迷你滑梯后重新回到该水池。

每个迷你滑梯 i 从水池 P\_i 到水池 Q\_i (1 <= P\_i <= V; 1 <= Q\_i <= V; P\_i != Q\_i)，并且有一个与之关联的乐趣值 F\_i (0 <= F\_i <= 2,000,000,000)。对于任何一次超级滑梯的滑行，贝茜的总乐趣是所有经过的迷你滑梯的乐趣值之和。

贝茜自然希望在滑梯排队等待的漫长时间里尽可能多地享受乐趣。通常，她会仔细选择从每个水池出来的迷你滑梯。然而，她是一头奶牛，在滑下滑梯的过程中最多有 K (1 <= K <= 10) 次会失去控制，随机选择一个迷你滑梯离开水池（这甚至可能发生在水池 1）。

如果贝茜选择以最坏情况下最大化她的乐趣，她在给定的超级滑梯上能保证获得多少乐趣？

例如，考虑一个有 3 个水池（水池编号如括号中所示）和四个迷你滑梯的小型乐园；K 的值为 1（乐趣值如括号外所示）：

[1]
/   \ 5 -> /     \ <- 9 

/       \ 
[2]---3---[3]

\_\_5\_\_/

她总是从水池 1 开始，到达水池 3。如果她可以选择，她会直接从水池 1 到水池 2，然后通过乐趣值较高的迷你滑梯（乐趣值为 5）到达滑梯 3，总乐趣值为 5+5=10。但是，如果她在水池 1 失去控制，她可能会直接从水池 1 滑到水池 3，总乐趣为 9。如果她在水池 2 失去控制，她的总乐趣可能会减少到 5+3 = 8。

贝茜希望找到她能获得的最大乐趣，因此她努力选择 1->3，总乐趣为 9。如果她在水池 1 失去控制而滑到迷你滑梯 1->2，她知道她在水池 2 不会失去控制，并且最终乐趣为 10。因此，她知道她的最小乐趣总是至少为 9。


## 说明/提示

（由 ChatGPT 4o 翻译）

## 样例 #1

### 输入

```
3 4 1 
2 3 5 
1 2 5 
1 3 9 
2 3 3 
```

### 输出

```
9 
```

# 题解

## 作者：fdfdf (赞：5)

本人表示一开始看到这道题的时候并没有看懂

比如这句

**如果Bessie选择了在最坏情况下，最大化她的开心值，那么，她在这种情况下一次冲浪可以得到的最大开心值是多少？**

机房大佬给出的解答是:

**假设你有意想让Bessie的愉悦值最小,题目规定你只能改k条边,在你们双方都做出最优决策的情况下,所能得到的愉悦值是多少?**

我想这不是博弈论吗(惊吓)

其实并不是很复杂

双方最优的意思大概就是:如果其中一方的操作不符合这个步骤,那么另一方总可以通过一些步骤,使得结果更加偏向自己的一方

~~似乎有种命中注定的感觉~~


接下来开始解题吧

**状态设为$f[k][i]$(0≤k≤K)**,

表示Bessie从i号节点出发,在k次失误下能够得到的最优值


因为Bessie一定会冲到n号节点,所以我们**以$f[0][n]=0$作为开始状态**


考虑$f[k][i]$的转移,当前只可能有两种决策:

1.Bessie选择最优决策:此时它应该是从$f[k][v]$(v为以u开始的边指向的结点)中选择一个最大值,然后选择那个方向;如果它不选择那个方向的话,我们就可以通过之后的k次修改使得它达不到比当前更大的愉悦值;即$a=max({f[k][v]})$

2.我们选择最优决策(即让Bessie走向愉悦值最小的道路),那么我们肯定会从

f[k-1][v](已经用了一次机会了)中选择一个最小值,然后让Bessie走上那条不归路...即$if(k>0)b=min({f[k-1][v]})$

这两种决策的结果应该取最小值,因为我们可以选择从什么时候让BEssis滑稽w

$f[k][u]=min(a,b)$


**最后答案在$f[K][1]$**

最后注意开long long

```cpp
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<queue>
#define RG register
using namespace std;
typedef long long ll;
const int N=50010;
const int M=150010;
const ll inf=((1ll*1)<<60);
ll n,m,k;
ll head[N],to[M],nxt[M],val[M],cnt;
ll f[11][N];
ll d[N],x[N];
bool vis[N];
queue<ll>Q;
inline void add(ll u,ll v,ll w){
    to[++cnt]=v;
    val[cnt]=w;
    nxt[cnt]=head[u];
    head[u]=cnt;
}

ll dfs_memory(ll u,ll s){//记忆化搜索(正推公式太过复杂)
    if(u==n)return 0;
    if(f[s][u])return f[s][u];
    RG ll maxn=0,minn=inf,v;
    for(RG int i=head[u];i;i=nxt[i]){//第一种情况
        v=to[i];
        maxn=max(maxn,dfs_memory(v,s)+val[i]);
    }
    if(s)
        for(RG int i=head[u];i;i=nxt[i]){//第二种情况
            v=to[i];
            minn=min(minn,dfs_memory(v,s-1)+val[i]);
        }
    if(!s)f[s][u]=maxn;
    else f[s][u]=min(maxn,minn);
    //printf("f[%d][%d]=%d\n",s,u,f[s][u]);
    return f[s][u];
}

int main()
{
    scanf("%lld%lld%lld",&n,&m,&k);
    for(RG ll i=1,u,v,w;i<=m;i++){
        scanf("%lld%lld%lld",&u,&v,&w);
        add(u,v,w);
    }
    printf("%lld\n",dfs_memory(1,k));
    return 0;
}
```

---

## 作者：luaddict (赞：4)

主要是用记忆化搜索。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
long long cnt,s[150001][3],o[50005],t[50005][11],m,n,k;
void jia(int a,int b,int c)
{
    cnt++;
    s[cnt][0]=b;
    s[cnt][1]=c;
    s[cnt][2]=o[a];
    o[a]=cnt;//邻接链表
}
long long dfs(long long num,long long k)
{
    if(t[num][k]!=0)//记忆化搜索
    return t[num][k];
    long long a=o[num];
    while(a!=-1)
    {
        long long v=0;
        v+=dfs(s[a][0],k)+s[a][1];
        if(v>t[num][k])
        t[num][k]=v;
        a=s[a][2];
    }
    if(k>0)
    {
        a=o[num];
        while(a!=-1)
        {
            long long v=dfs(s[a][0],k-1)+s[a][1];
            if(v<t[num][k])
            t[num][k]=v;
            a=s[a][2];
        }
    }
    return t[num][k];
}
int main()
{
    int i,j,k,a,b,c;
    cin>>n>>m>>k;
    memset(o,-1,sizeof(o));
    for(i=1;i<=m;i++)
    {
        scanf("%d%d%d",&a,&b,&c);
        jia(a,b,c);
    }
    dfs(1,k);
    cout<<t[1][k];
}
```

---

## 作者：Link_Space (赞：1)

题目解释：给定一个有向图，你需要选择一条路径从1走到v，其中必须有k条边会失误，即选择当前能选择最小的边，求在此条件下的最大距离。

考虑dp，设 $dp[i][j]$ 表示i次失误的情况下从j点到n点的最大距离。

那么对于状态转移，应从终点向起点转移：
# 1  当前点失误
 $dp[i][j]=min(dp[i-1][v]+link)$ 其中v表示当前点的下一个点，link为两点之间的边
# 2 当前点不失误
 $dp[i][j]=min(dp[i][v]+link)$ ,其中v与link的含义同上
 
 那么这个问题就很轻松的解决了，由于是图上的dp，所以不选择直接递推，用记搜来完成。
 
最后的答案即为 $dp[k][1]$ 
以下是代码
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
int head[N], ver[N], nxt[N], cnt;
ll link[N];
void add(int x,int y,ll z)
{
    nxt[++cnt] = head[x];
    head[x] = cnt;
    ver[cnt] = y;
    link[cnt] = z;
}
ll dp[15][N];
ll dfs(int k,int now)
{
    if(dp[k][now])
        return dp[k][now];
    for (int i = head[now]; i;i=nxt[i])
    {
        int v0 = ver[i];
        dp[k][now] = max(dp[k][now], dfs(k, v0) + link[i]);
    }
    if(k)
        for (int i = head[now]; i;i=nxt[i])
        {
            int v0=ver[i];
            dp[k][now] = min(dp[k][now], dfs(k - 1, v0) + link[i]);
        }
    return dp[k][now];
}
int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m;i++)
    {
        int a, b;
        ll c;
        scanf("%d%d%lld", &a, &b, &c);
        add(a, b, c);
    }
    printf("%lld\n", dfs(k, 1));
}
```


---

## 作者：jdfz2251533 (赞：0)

# 题解：P2991 \[USACO10OPEN] Water Slides G

## 题意

题目描述实在抽象。大概题意：给定了一个带权有向图，要从 $1$ 号点走到 $n$ 号点，有 $k$ 次会在选边的时候选最短的一条（以下称为选错），最大化路径总长。

## 思路

很明显是图上 dp，不妨使用记忆化搜索，避免朴素 dp 转移更复杂的问题。

设 $f_{u, k}$ 为走到 $u$ 时选错了 $k$ 次得到的最大答案。

dfs 中每个点的两种决策方式：

1\. 最优，$f_{u, k} = \max(f_{v, k} + dis_{u, v})$，其中的 $f_{v, k}$ 可以用 $dfs(v, k)$ 求出。

2\. 选错，$f_{u, k} = \min(f_{v, k - 1} + dis_{v, k})$，其中的 $f_{v, k - 1}$ 可以用 $dfs(v, k - 1)$ 求出。

以上的 $v$ 均为 $u$ 连接的点。

## 细节问题

1\. 单向边。

2\. 两种决策方式**不能**在一个循环内转移，原因：如果一起转移，可能会导致 max 和 min 互相覆盖，得到的结果不是正确结果。

3\. 选错的转移有前提 $k > 0$，但最优的转移没有此前提。

4\. 根据数据范围可见要开 long long。

## code

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 5;

int n, m, k, h[N], tot;
ll f[N][15];
struct node {
	int to, nxt;
	ll w;
} e[N << 1];

void add(int u, int v, ll w) {
	e[++tot].nxt = h[u];
	e[tot].to = v;
	e[tot].w = w;
	h[u] = tot;
}

ll dfs(int u, int k) {
	if (f[u][k]) {
		return f[u][k];
	}
	for (int i = h[u]; i; i = e[i].nxt) {
		int v = e[i].to;
		f[u][k] = max(f[u][k], dfs(v, k) + e[i].w);
	}
	if (k) {
		for (int i = h[u]; i; i = e[i].nxt) {
			int v = e[i].to;
			f[u][k] = min(f[u][k], dfs(v, k - 1) + e[i].w);
		}
	}
	return f[u][k];
}

int main() {
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) {
		int u, v;
		ll w;
		cin >> u >> v >> w;
		add(u, v, w);
	}
	cout << dfs(1, k);
	return 0;
}
```

---

## 作者：Jorisy (赞：0)

考虑 DAG 上 dp。

记 $f_{i,k}$ 表示位于节点 $i$ 时，恰好失误了 $k$ 次时到达节点 $n$ 的最长路。

于是在 $k=0$ 时，就不难得到 $f_{i,k}=\max\limits_{(i,j)\in E}\{f_{j,k}+w_{i,j}\}$。

而在 $k>0$ 时，就可能会出现失误的情况，于是就**另外有**（这意味着上述的转移仍然需要做，这也是显然的） $f_{i,k}=\min\limits_{(i,j)\in E}\{f_{j,k-1}+w_{i,j}\}$。

于是就做完了。

参考代码：
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;

vector<pair<int,int>>g[50005];
int n,m,k;
ll f[50005][15];

ll dp(int x,int t)
{
    if(f[x][t]) return f[x][t];
    for(auto i:g[x])
    {
        int y=i.first;
        f[x][t]=max(f[x][t],dp(y,t)+i.second);
    }
    if(t)
    {
        for(auto i:g[x])
        {
            int y=i.first;
            f[x][t]=min(f[x][t],dp(y,t-1)+i.second);
        }
    }
    return f[x][t];
}

int main()
{
    //freopen(".in","r",stdin);
    //freopen(".out","w",stdout);
    scanf("%d%d%d",&n,&m,&k);
    while(m--)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        g[u].push_back({v,w});
    }
    cout<<dp(1,k);
    return 0;
}
```

---

## 作者：WZWZWZWY (赞：0)

[题目](https://www.luogu.com.cn/problem/P2991)：一个带权值的有向无环图，从 $1$ 走到 $n$ 点，有 $k$ 次失误的最坏情况下，问最大化的价值。

原来我想拓扑+DP，但是发现确实有些困难，最后还是选择了记忆化搜索。QAQ。

$f_{i,j}$，$i$ 表示当前判断到了哪个点，$j$ 表示失误的次数。

**当前点不失误时**：$f_{i,j}=\max(f_{i,j},f_{to,j}+value)$。

**当前点失误**：$f_{i,j}=\min(f_{i,j},f_{to,j-1}+value)$。

还有就是一定要先执行当前点不失误的转移，再执行失误的转移。因为你并不是你想什么时候失误就能失误，而是不可控的，并且一定是最坏的情况。

需要注意的一点是：失误时的转移一般不能和不失误时的转移同时进行。先看代码，等会解释。

不开 `long long` 见祖宗。

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
struct edge {
	int to, v;
};
vector <edge> a[150005];

int f[50005][15];

int dp(int d, int mess) {
	if (f[d][mess]) return f[d][mess];
	for (int i = 0; i < a[d].size(); i++) {
		edge r = a[d][i];
		f[d][mess] = max(f[d][mess], dp(r.to, mess) + r.v);
	}
	if (mess) {
		for (int i = 0; i < a[d].size(); i++) {
			edge r = a[d][i];
			f[d][mess] = min(f[d][mess], dp(r.to, mess - 1) + r.v);
		}
	}
	return f[d][mess];
}

signed main() {
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 1; i <= m; i++) {
		int u, v, f;
		cin >> u >> v >> f;
		a[u].push_back((edge){v, f});
	}
	cout << dp(1, k);
}
```


刚才说到，失误时的转移[一般](https://www.luogu.com.cn/paste/nhmuav31)不能和不失误时的转移同时进行。也就是不能写成这样：

```
int dp(int d, int mess) {
	if (f[d][mess]) return f[d][mess];
	for (int i = 0; i < a[d].size(); i++) {
		edge r = a[d][i];
		f[d][mess] = max(f[d][mess], dp(r.to, mess) + r.v);
		if (mess) f[d][mess] = min(f[d][mess], dp(r.to, mess - 1) + r.v);
	}
	return f[d][mess];
}
```


举个最简单的例子：

```
3 2 1
1 2 2
1 3 3
```

如果同时进行，就会输出 $3$，但是失误一次的话应该输出 $2$。这是因为循环第二次的 $\max$ 把上一次的取 $\min$ 给覆盖掉了。



还有什么不懂的可以在评论区问我哦。

---

## 作者：Gaode_Sean (赞：0)

这道题可以用 dp 来解决。

设 $dp_{c,x}$ 表示从 $n$ 走到 $x$，失误 $c$ 次的最大开心值。

对于每一个点，需要考虑两种情况：

- 失误

此时应选择最优策略，即 $dp_{c,x}=\max \ (dp_{c-1,y}+edge_{x,y})$。

- 不失误

此时应选择最劣策略，即 $dp_{c,x}=\min \ (dp_{c,y}+edge_{x,y})$。

## AC Code

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=5e4+1,M=1e5+5e4+1;
ll n,m,val,tot,ver[M],edge[M],nxt[M],head[N],f[11][N];
void add(ll x,ll y,ll z)
{
	ver[++tot]=y;
	edge[tot]=z;
	nxt[tot]=head[x];
	head[x]=tot;
}
ll dp(ll c,ll x)
{
	if(f[c][x]) return f[c][x];
	for(ll i=head[x];i;i=nxt[i])
	{
		ll y=ver[i];     
	    f[c][x]=max(f[c][x],dp(c,y)+edge[i]);
		//if(c) f[c][x]=min(f[c][x],dp(c-1,y)+edge[i]);
	}
	for(ll i=head[x];i;i=nxt[i])
	{
		ll y=ver[i];     
	    //f[c][x]=max(f[c][x],dp(c,y)+edge[i]);
		if(c) f[c][x]=min(f[c][x],dp(c-1,y)+edge[i]);
	}
	return f[c][x];
}
int main()
{
	scanf("%lld%lld%lld",&n,&m,&val);
	for(ll i=1;i<=m;i++)
	{
		ll x,y,z;
		scanf("%lld%lld%lld",&x,&y,&z);
		add(x,y,z);
	}
	f[0][n]=0;
	printf("%lld",dp(val,1));
	return 0;
}
```

---

