# Data Center Maintenance

## 题目描述

给出 $n$ 个数据中心，$m$ 份资料。要把 $m$ 份资料放到其中的两个数据中心备份，需要保证任意时刻都可以至少在一个数据中心进行备份。定义一天有 $h$ 个小时，每个数据中心在一天内有一小时维护时间 $u_i$（$0 \leq u_i < h$），在这一小时内该数据中心无法进行备份。

由于某种原因，需要把一些数据中心的维护时间向后推迟 1 小时（一个数据中心的维护时间的向后推迟可能导致有的资料无法在任意时刻进行备份 且 若推迟前 $u_i = h - 1$ 那么推迟后 $u_i = 0$），请你求出最少需要向后推迟多少个数据中心，并把这些数据中心的编号输出出来。

## 样例 #1

### 输入

```
3 3 5
4 4 0
1 3
3 2
3 1
```

### 输出

```
1
3 ```

## 样例 #2

### 输入

```
4 5 4
2 1 0 3
4 3
3 2
1 2
1 4
1 3
```

### 输出

```
4
1 2 3 4 ```

# 题解

## 作者：Stars_Traveller (赞：4)

## 题解：CF949C Data Center Maintenance
### 题意
有 $n$ 个数据中心，$m$ 份资料，每份资料保存在两个不同的数据中心，且两个数据中心的维护时间不一样，现在求最少推迟几个数据中心的维护时间，使得 $m$ 份资料仍然保证每份的两个数据中心维护时间不一样。

注意：最少推迟 $1$ 个数据中心。

### 分析
当 $1$ 个数据中心 $x$ 推迟 $1$ 小时维护，可能会引起连锁反应。

我们可以将数据中心当作点，若 $x$ 推迟导致 $y$ 必须也推迟，$x$ 向 $y$ 连有向边。

若第 $i$ 份资料的两个数据中心 $x_i$ 和 $y_i$ 满足 $(t_{x_i}+1) \bmod h = t_{y_i}$，$x$ 向 $y$ 建边，若第 $i$ 份资料的两个数据中心 $x_i$ 和 $y_i$ 满足 $(t_{y_i}+1) \bmod h = t_{x_i}$，$y$ 向 $x$ 建边。

若图是无环的，则答案必然为 $1$，并任意选择出度为 $0$ 的点输出即可。

考虑图有环的情况，缩点，并维护强连通分量中原始点的个数 $num_i$，答案是新图中出度为 $0$ 的强连通分量中 $num$ 数组的最小值。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+5;
vector<int>nbr[maxn], SCC[maxn];
stack<int>stk;
int out[maxn], a[maxn];
int n, m, dfn[maxn], used[maxn], vis[maxn], low[maxn], scc[maxn], cntc, cnt, ans, h, num[maxn];
void tarjan(int cur)
{
    dfn[cur]=low[cur]=++cnt;
    stk.push(cur);
    for(int q:nbr[cur])
    {
        if(!dfn[q])
        {
            tarjan(q);
            low[cur]=min(low[cur],low[q]);
        }
        else if(!scc[q]) 
        {
            low[cur]=min(low[cur],dfn[q]);
        }
    }
    if(low[cur]==dfn[cur])
    {
        cntc++;
        scc[cur]=cntc;
        num[cntc]++;
        SCC[cntc].push_back(cur);
        while(stk.top()!=cur)
        {
            int t=stk.top();
            stk.pop();
            scc[t]=cntc;
            num[cntc]++;
            SCC[cntc].push_back(t);
        }
        stk.pop();
    }
}
 
signed main()
{
    cin>>n>>m>>h;
    for(int i=1;i<=n;i++)cin>>a[i];
    for(int i=1;i<=m;i++)
    {
        int x, y;
        cin>>x>>y;
        if((a[x]+1)%h==a[y])
        {
            nbr[x].push_back(y);
        }
        if((a[y]+1)%h==a[x])
        {
            nbr[y].push_back(x);
        }
    }
    for(int i=1;i<=n;i++)if(!dfn[i])tarjan(i);
    for(int i=1;i<=n;i++)
    {
        for(auto nxt:nbr[i])
        {
            if(scc[i]!=scc[nxt])
            {
                out[scc[i]]++;
            }
        }
    }   
    int ans=114514191981000, id;
    for(int i=1;i<=cntc;i++)
    {
        if(out[i]==0&&num[i]<ans)
        {
            ans=num[i];
            id=i;
        }
    }
    sort(SCC[id].begin(),SCC[id].end());
    cout<<ans<<"\n";
    for(auto idd:SCC[id])cout<<idd<<" ";
}
```

---

## 作者：yuzhechuan (赞：4)

这题如果没有搞清楚题意，其实结论是并不“显然”的

---

题目其实是让你主动推迟有且仅有一个点，并将所有会因此受影响的点也都连锁着推迟下去，问最少会有几个点推迟

注意这个”主动推迟“，这意味着即使已经满足条件了你还是得要推迟一个点

搞懂了题意，接下来的思路就好理解了

---

我们发现“推迟”是一种单向关系，即，如果我使你不得不推迟，而你却不会使我不得不推迟

将这种单向关系转成图论的单向边

<x,y>边的是否添加，即询问两者的是否满足

$$ u_x +1 \equiv x_y  \  \  ( mod {h} ) $$

发现一个点只要有出度那它肯定不是最优的

如A->B，选A必带B，选B可无A

所以首先可以确定答案节点没有出度的

其次，由于强联通分量里的点都是可以互相到达的，所以只要其一推迟，另外的都得推迟

于是缩点，经保留size

问题变成在DAG上找一个没有出度的最小的点

$O(n)$扫一遍即可

---


```cpp
#include <bits/stdc++.h>
using namespace std;
template<class t> inline t read(t &x){
	x=0;char c=getchar();bool f=0;
	while(!isdigit(c)) f|=c=='-',c=getchar();
	while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
	if(f) x=-x;return x;
}
template<class t> inline void write(t x){
	if(x<0){putchar('-'),write(-x);}
	else{if(x>9)write(x/10);putchar('0'+x%10);}
}

const int N=1e5+5;
int h[N],en,H,n,m,scc[N],dfn[N],low[N],st[N],lim,cnt,du[N],sn,ans,sz[N],a[N];
bool v[N];

struct edge{
	int n,u,v;
}e[N];

void add(int x,int y){
	e[++en]=(edge){h[x],x,y};
	h[x]=en;
}

void tarjan(int x){ //找强联通分量
	low[x]=dfn[x]=++cnt;
	v[x]=1;
	st[++lim]=x;
	for(int i=h[x];i;i=e[i].n){
		int y=e[i].v;
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else{
			if(v[y]) low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		int top;
		sn++;
		for(;;){
			top=st[lim--];
			scc[top]=sn;
			v[top]=0;
			sz[sn]++;
			if(top==x) return ;
		}
	}
}

signed main(){
	read(n);read(m);read(H);
	for(int i=1;i<=n;i++) read(a[i]);
	for(int i=1,x,y;i<=m;i++){
		read(x);read(y);
		if((a[x]+1)%H==a[y]) add(x,y); //边的添加（关系的判断）
		if((a[y]+1)%H==a[x]) add(y,x);
	}
	for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
	for(int i=1;i<=en;i++){
		int x=scc[e[i].u],y=scc[e[i].v]; //根据原先加的边判定出度
		if(x^y) du[x]++;
	}
	sz[0]=0x3f3f3f3f;
	for(int i=1;i<=sn;i++) if(!du[i]){
		if(sz[i]<sz[ans]) ans=i; //取无出度节点的最小size
	}
	write(sz[ans]);puts("");
	for(int i=1;i<=n;i++) if(scc[i]==ans) //是这个强联通分量的就输出
		write(i),putchar(' ');
}
```

---

## 作者：Stone_Xz (赞：3)

## [传送门：CF949C Data Center Maintenance](https://www.luogu.com.cn/problem/CF949C)

## 简要题意：

> 给定 $n$ 个数据中心以及它们的维护时间，$m$ 份资料。每份资料用两个数据中心备份，且这两个数据中心的维护时间不同。求最少对几个数据中心的维护时间推迟一小时，使得每份资料的两个数据中心维护时间仍然不同。（必须推迟不少于一个的数据中心）

## 分析：

1. 一份资料的两个数据中心维护时间必须不同，如果其中一个数据中心推迟维护 $1$ 个小时后，刚好等于另一个数据中心的维护时间，那么另一个数据中心也要推迟维护。以此类推，所以推迟一个数据中心可能引起连锁反应。

2. 于是考虑选择推迟后影响最小的数据中心。将数据中心看作点，如果某个点 $x$ 推迟后 $y$ 也要推迟，那么 $x$ 向 $y$ 连有向边。答案显然为出度为 $0$ 的点。

3. 因为有 $h$ 的存在，$h - 1$ 的时间向后推迟一个小时是 $0$ 的时间，所以图中可能有环。对于有环的情况，若推迟一个点，这个点所在的 scc（强连通分量）中的所有点就都要推迟。一个 scc 可以绑定成一个点考虑，这样就可以得到一张有向无环图了。考虑缩点并维护每个 scc 的大小。

4. 缩点后，答案就是新图中出度为 $0$ 的最小的 scc。

# Code

```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5, M = 1e5 + 5;

int n, m, h, cnt, tot, mini = 1e9, ans_id;

int t[N], dfn[N], low[N], scc[N], dis[N], sum[N], out[N];

int x[M], y[M];

bool vis[N], onstk[N];

stack<int> stk;

vector<int> nbr[N], have_[N];

void tarjan(int cur)
{
	stk.push(cur);
	onstk[cur] = true;
	dfn[cur] = low[cur] = ++cnt;
	for(auto nxt : nbr[cur])
	{
		if(!dfn[nxt])
		{
			tarjan(nxt);
			low[cur] = min(low[cur], low[nxt]); 
		}
		else if(onstk[nxt])
			low[cur] = min(low[cur], dfn[nxt]);
	}
	if(low[cur] == dfn[cur])
	{
		tot++;
		while(stk.top() != cur)
		{
			int tmp = stk.top(); stk.pop();
			onstk[tmp] = false;
			sum[tot]++;
			have_[tot].push_back(tmp);
			scc[tmp] = tot;
		}
		stk.pop();
		onstk[cur] = false;
		sum[tot]++;
		have_[tot].push_back(cur);
		scc[cur] = tot;
	}
}

int main()
{
	cin >> n >> m >> h;
	for(int i = 1; i <= n; i++)
		cin >> t[i];
	for(int i = 1; i <= m; i++)                    // 建图 
	{
		cin >> x[i] >> y[i];
		if((t[x[i]] + 1) % h == t[y[i]])
			nbr[x[i]].push_back(y[i]);
		if((t[y[i]] + 1) % h == t[x[i]])
			nbr[y[i]].push_back(x[i]);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i]) tarjan(i);                     // 求 scc 
	for(int i = 1; i <= n; i++)
		for(auto j : nbr[i]) if(scc[i] != scc[j])
			out[scc[i]]++;                         // 维护每个 scc 的出度 
	for(int i = 1; i <= tot; i++)
		if(out[i] == 0 && sum[i] < mini)           // 求答案 
		{
			mini = sum[i];
			ans_id = i;
		}
	cout << mini << "\n";
	vector<int> tmp = have_[ans_id];
	sort(tmp.begin(), tmp.end());
	for(auto i : tmp) cout << i << " ";
	return 0; 
}
```

---

## 作者：Weekoder (赞：2)

这道题目的建边方式很新颖，而不像传统的题目，一眼就能看破。

### 题意

如果不搞清楚这道题目的题意，就很难做这道题。有 $n$ 个站点用于备份 $m$ 份文件，每份文件依赖两个站点备份文件，每个站点有一个维护时间 $u_i$，也就是在 $u_i$ 时刻，站点 $i$ 无法备份文件。现在，我们的目标是让 $m$ 份文件在**任意时刻**都能备份。为了达成这个目标，我们可能需要推迟一些站点的维护时间一个小时，即 $u_i\gets u_i+1$，而当 $u_i=h$ 时，一天过完了，$u_i=0$。$h$ 即为一天有多少个小时。注意：必须推迟至少一个站点。

### 思路

对于一份文件，在任意时刻只要有一个站点不在维护，就可以成功备份。也就是说，文件 $i$ 依赖的两个站点 $x,y$ 需要满足 $u_x\ne u_y$。如果 $u_x=u_y$，那么推迟其中一个站点就好了：可是，这样会产生问题！假设有两份文件，第一份依赖站点 $a,b$，第二份依赖站点 $b,c$。此时 $u_a=u_b$，如果我们推迟 $b$ 号站点，那么 $c$ 号站点就也有可能被迫被推迟。也就是说，推迟一个站点虽然能解决当下的燃眉之急，可是会有可能引发更加复杂的**连锁反应**！此时，问题的建模也逐渐有了些眉目：我们或许可以用连锁反应来建边，即 $u\to v$ 代表 $u$ 推迟后会使得 $v$ 也必须推迟。

那么，最优策略是什么？我们当然不希望有连锁反应出现，所以，如果当前建出来的图是一个 DAG（有向无环图） ，那么最优的策略一定是选择一个出度为 $0$ 的点，因为这样就不会产生任何连锁反应了。

然而实际建出来的图有可能是一个有环的有向图，也就是有可能没有出度为 $0$ 的点。那该怎么办呢？我们注意到，一个环内的推迟数量即为环内点的数量，而当我们用 tarjan 算法将整个图缩点为一个有向无环图后，答案就是出度为 $0$ 的点中，环的大小最小的点。于是，我们只需要用 tarjan 跑一遍强连通分量，维护大小与环内点的编号即可。

请注意：强连通分量事实上不是一个点就是一个环（有可能是复杂环）。由于 $u_i\gets h$ 时 $u_i$ 又要变为 $0$，所以我们可以直接写为 $u_i\gets (u_i+1)\bmod h$。

代码：


```cpp
#include <bits/stdc++.h>

#define int long long

#define debug(x) (cout << #x << " " << x << "\n")

using namespace std;

const int N = 1e5 + 5, M = 5e5 + 5;

struct Edge {
	int u, v;
}e[M];

int n, m, h, dfn[N], low[N], scc[N], dfncnt, sum, sz[N], out[N], t[N], cnt;

bool inStack[N];

stack<int> stk;

vector<int> nbr[N], ans[N];

void tarjan(int cur) {
	dfn[cur] = low[cur] = ++ dfncnt;
	inStack[cur] = 1;
	stk.push(cur);
	for (auto nxt : nbr[cur]) {
		if (!dfn[nxt]) {
			tarjan(nxt);
			low[cur] = min(low[cur], low[nxt]);
		} else if (inStack[nxt]) {
			low[cur] = min(low[cur], dfn[nxt]);
		}
	}
	if (dfn[cur] == low[cur]) {
		sum ++;
		while (stk.top() != cur) {
			inStack[stk.top()] = 0;
			scc[stk.top()] = sum;
			sz[sum] ++;
			ans[sum].emplace_back(stk.top());
			stk.pop();
		}
		inStack[stk.top()] = 0;
		scc[stk.top()] = sum;
		sz[sum] ++;
		ans[sum].emplace_back(stk.top());
		stk.pop();
	}
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cin >> n >> m >> h;
	for (int i = 1; i <= n; i++) cin >> t[i];
	for (int i = 1, u, v; i <= m; i++) {
		cin >> u >> v;
		if ((t[u] + 1) % h == t[v] % h) {
			nbr[u].emplace_back(v);
			e[++ cnt] = (Edge){u, v};
		} 
		if ((t[v] + 1) % h == t[u] % h) {
			nbr[v].emplace_back(u);
			e[++ cnt] = (Edge){v, u};
		} 
	}
	for (int i = 1; i <= n; i++) if (!dfn[i]) {
		tarjan(i);
	}
	for (int i = 1; i <= cnt; i++) scc[e[i].u] != scc[e[i].v] && (out[scc[e[i].u]] ++);
	int mini = 0;
	sz[0] = 1e18;
	for (int i = 1; i <= sum; i++) if (!out[i] && sz[i] < sz[mini]) {
		mini = i;
	}
	cout << sz[mini] << "\n";
	for (auto i : ans[mini]) cout << i << " ";
	return 0;
}
```

---

## 作者：Z1qqurat (赞：2)

再摆，就废了！

### 思路

看到这种题，可以想到图论。而作为一道图论题，建模是很重要的。

$m$ 份资料，每一份都要有两个可以在不同时间备份的数据中心。而题目要求我们至少推迟一个数据中心，那我们自然地想到：那就尽量推迟一个不会影响到别的数据中心的。这其实对我们建边有很大启发。

在图论里面，建边有很多思路：

1.表示连接，可到达关系（类似于路径），比如我们跑最短路时的建边，所以就会有边权表示到达的代价，并查集建的边也是表示可以到达。

2.表示差距，比如在差分约束系统里面为不等式建的边。

3.表示顺序，比如一棵树的父亲到儿子结点就可以这么理解为遍历时要从上到下，从父亲到儿子。

**4.表示影响，制约关系，也就是本题的建模。**

什么时候推迟一个数据中心，会影响到别的数据中心，从而要推迟多个？那就是当两个数据中心被同一份资料用，并且它们的维护时间相差 $1$ 的时候，推迟较早那个会影响较晚的。

于是我们对于同一份资料对应的两个数据中心，若维护时间相差 $1$ 就从较早的数据中心向较晚的连边，表示推迟了较早的，较晚的就会受到影响，从而也会推迟。

那么现在的图里面，如果有环，环里面有一个数据中心需要推迟，整个环里面的都需要推迟。于是我们做一个 Tarjan 缩点，贪心地选出点数最少的出度为 $0$ 的强连通分量。

至此，就很清楚了。

### Code

可能有注释。

```cpp
#include<bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define gc getchar()
#define vc vector
#define pii pair<int, int>
#define St string
#define em emplace
#define eb emplace_back
using namespace std;
const int N = 1e5 + 10;
int n, m, h, t[N], a, b, scc[N], dfn[N], low[N], sz[N], cnt, tot, ans = N, pos, out[N];
bool ons[N];
vc <int> og[N];
stack <int> stk;

inline int read() {
    int x = 0, f = 0; char c = gc;
    while(c < '0' || c > '9') f |= c == '-', c = gc;
    while(c >= '0' && c <= '9') x = (x << 1) + (x << 3) + (c ^ 48), c = gc;
    return f ? -x : x;
}

void tarjan(int u) {//缩点。
    stk.em(u), ons[u] = 1;
    dfn[u] = low[u] = ++tot;
    for (auto v : og[u]) {
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(ons[v]) low[u] = min(low[u], dfn[v]);
    }
    if(dfn[u] == low[u]) {
        ++cnt;
        while(!stk.empty()) {
            int cr = stk.top(); stk.pop();
            scc[cr] = cnt, ons[cr] = 0;
            sz[cnt]++;//记得记录每一个强连通分量的大小（点数）。
            if(cr == u) break;
        }
    }
    return ;
}

int main() {
    n = read(), m = read(), h = read();
    for (int i = 1; i <= n; ++i) t[i] = read();
    while(m--) {
        a = read(), b = read();
        if((t[a] + 1) % h == t[b]) og[a].eb(b);
        if((t[b] + 1) % h == t[a]) og[b].eb(a);//建边，记得加的时候取模。
    }
    for (int i = 1; i <= n; ++i) {
        if(!dfn[i]) tarjan(i);
    }
    for (int i = 1; i <= n; ++i)  {
        int fx = scc[i];
        for (auto j : og[i]){
            int fy = scc[j];
            if(fx != fy) out[fx]++;//记录出度。
        }
    }
    for (int i = 1; i <= cnt; ++i){
        if(!out[i] && sz[i] < ans) {
            ans = sz[i];
            pos = i;//选择出度为0且点数最小的强连通分量。
        }
    }
    cout << ans << "\n";
    for (int i = 1; i <= n; ++i){
        if(scc[i] == pos) cout << i << ' ';//输出答案。
    }
    puts("");
    return 0;
}
```

---

## 作者：Hercules (赞：2)

## 题解：CF949C Data Center Maintenance

这道题主要还在于阅读理解，明白它想让干什么，可以在题意不变的情况下将题目改变一下，使得更好理解。

其中一种思想可以看为：n个节点，m条边的有色图，每次更新时间当作它的颜色，若第i个用户使用的2个节点，则在两点之间建立一条边。

询问的是：有多少条边它连接的是两个颜色不同的节点。

我们可以选择最少的节点，使这些节点的颜色变为$w_i+1 \ mod \ h$，仍要有任意一条边连接的两个节点颜色不同。

总结来说就是求新的有向图的最小强联通分量，并且这个强联通分量保证无出边。（否则就会和别的节点颜色相同）

---

代码：

```c
//#pragma GCC optimize(3, "Ofast", "inline")
#include <bits/stdc++.h>

const int MAXN = 1e5 + 5;
const int INF = 0x3f3f3f3f;
struct Edge {
    int x, y, nxt;
} e[MAXN << 1];
bool instack[MAXN];
int a[MAXN], head[MAXN], node[MAXN];
int n, m, h, cnt, tot, top, ans, TimeClock;
int belong[MAXN], dfn[MAXN], low[MAXN], stack[MAXN], size[MAXN];

inline int read() {
    int X = 0, flag = 0;
    char ch = 0;
    while (!isdigit(ch))
        flag |= ch == '-', ch = getchar();
    while (isdigit(ch))
        X = (X << 3) + (X << 1) + (ch ^ 48), ch = getchar();
    return flag ? -X : X;
}

inline void write(int x) {
    if (x < 0)
        x = -x, putchar('-');
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}

inline void add_edge(int x, int y) {
    e[++cnt].x = x, e[cnt].y = y;
    e[cnt].nxt = head[x], head[x] = cnt;
}

inline void Tarjan(int x) {
	low[x] = dfn[x] = ++TimeClock;
    stack[++top] = x, instack[x] = true;
	for (register int i = head[x]; i; i = e[i].nxt) {
		if (!dfn[e[i].y]) {
			Tarjan(e[i].y);
			low[x] = std::min(low[x], low[e[i].y]);
		} else {
			if (instack[e[i].y])
				low[x] = std::min(low[x], dfn[e[i].y]);
		}
	}
	if (dfn[x] == low[x]) {
		tot++;
		while (stack[top + 1] != x) {
            size[tot]++;
			belong[stack[top]] = tot;
			instack[stack[top--]] = false;
		}
	}
}

signed main() {
#ifndef ONLINE_JUDGE
#ifdef LOCAL
    freopen("testdata.in", "r", stdin);
    freopen("testdata.out", "w", stdout);
#endif
#ifndef LOCAL
    freopen("CF949C.in", "r", stdin);
    freopen("CF949C.out", "w", stdout);
#endif
#endif
    n = read(), m = read(), h = read();
	for (int i = 1; i <= n; i++)
		a[i] = read();
	for (int i = 1, x, y; i <= m; i++) {
		x = read(), y = read();
		if ((a[x] + 1) % h == a[y])
			add_edge(x, y);
		if ((a[y] + 1) % h == a[x])
			add_edge(y, x);
	}
	for (int i = 1; i <= n; i++)
		if (!dfn[i])
			Tarjan(i);
	for (int i = 1, x, y; i <= cnt; i++) {
		x = belong[e[i].x], y = belong[e[i].y];
		if (x ^ y)
			node[x]++;
	}
	size[0] = INF;
	for (int i = 1; i <= tot; i++)
		if (!node[i])
			if (size[i] < size[ans])
				ans = i;
	write(size[ans]), putchar('\n');
	for (int i = 1; i <= n; i++)
		if (belong[i] == ans)
			write(i), putchar(' ');
    return 0;
}
```



---

## 作者：shao0320 (赞：1)

容易发现对于一种文件，假设其两个备份点分别为 $x$ 和 $y$，则 $u_x+1=u_y$ 时，若 $x$ 推迟，则 $y$ 必定推迟，在这种情况下建立一条 $x$ 至 $y$ 的单向边，则得到一张有向图，对于每个强连通分量，其必定都是全推迟或全不推迟，那么缩点后找到一个没有出度的最小强连通分量即可。

code：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 500005
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-48,ch=getchar();
	return x*f;
}
int n,m,h,v[N],head[N],nxt[N],cnt,u[N],dfn[N],low[N];
int stk[N],top,co[N],tot,col,siz[N],out[N];
void dfs(int x)
{
    dfn[x]=low[x]=++tot;
    stk[++top]=x;
    for(int i=head[x];i;i=nxt[i])
    {
        if(!dfn[v[i]])
        {
            dfs(v[i]);
            low[x]=min(low[x],low[v[i]]);
        }
        else if(!co[v[i]])
        {
            low[x]=min(low[x],low[v[i]]);
        }
    }
    if(dfn[x]==low[x])
    {
        ++col;
        while(stk[top]!=x)
        {
            co[stk[top]]=col;
            siz[col]++;
            --top;
        }
        co[x]=col;
        siz[col]++;
        --top;
    }
}
void add(int a,int b)
{
    v[++cnt]=b;
    nxt[cnt]=head[a];
    head[a]=cnt;
}
int main()
{
    #ifdef LOCAL
    freopen("1.in","r",stdin);
    freopen("1.out","w",stdout);
    #endif
    n=read();m=read();h=read();
    for(int i=1;i<=n;i++)u[i]=read();
    for(int i=1;i<=m;i++)
    {
        int x=read(),y=read();
        if((u[x]+1)%h==u[y])add(x,y);
        if((u[y]+1)%h==u[x])add(y,x);
    }
    for(int i=1;i<=n;i++)if(!dfn[i])dfs(i);
    for(int i=1;i<=n;i++)
    {
        for(int j=head[i];j;j=nxt[j])
        {
            if(co[v[j]]!=co[i])out[co[i]]++;
        }
    }
    int ans=n+1;
    for(int i=1;i<=col;i++)if(!out[i])ans=min(ans,siz[i]);
    for(int i=1;i<=col;i++)
    {
        if(!out[i]&&ans==siz[i])
        {
            printf("%d\n",ans);
            for(int j=1;j<=n;j++)
            {
                if(co[j]==i)
                {
                    printf("%d ",j);
                }
            }
            return 0;
        }
    }
}
```

---

## 作者：lfxxx (赞：1)

想一想什么时候一个资料不会在任意时候都能在一个地方备份。

就是它备份的两个地方在同时间维护。

所以假若有一个资料在 $x,y$ 出备份，假若 $x$ 维护的时间往后推迟一个小时与 $y$ 维护的时间相同，那么 $y$ 便也要推迟维护时间。

根据这个关系可以建出一张有向图，边代表的推迟的传递关系，不难发现一个强连通分量内的点一个推迟就全部要推迟。

所以将原图的强连通分量缩成一个点，那么在这张缩点后的有向无环图上一个点推迟它的所有出边的点也需要推迟。

所以枚举所有出边为 $0$ 的点一定是最优的，记录每个强连通分量内的点的数量即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 1e6+114;
vector<int> edge[maxn],road[maxn];
int dfn[maxn],low[maxn],vis[maxn],dfncnt;
stack<int> s;
int n,m,h;
int col[maxn],cl,dp[maxn],sz[maxn];
vector<int> Outans[maxn];
int t[maxn];
int ans = INT_MAX;
int In[maxn],Out[maxn];
void tanjan(int u){
	dfn[u]=low[u]=++dfncnt;
	s.push(u);
	vis[u]=1;
	for(int v:edge[u]){
		if(!dfn[v]){
			tanjan(v);
			low[u]=min(low[u],low[v]);
		}	
		else if(vis[v]==1){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		cl++; 
		while(s.top()!=u){
			Outans[cl].push_back(s.top());
			vis[s.top()]=0;
			col[s.top()]=cl;
			sz[cl]++;
			s.pop();
		}
		Outans[cl].push_back(u);
		s.pop();
		sz[cl]++;
		vis[u]=0;
		col[u]=cl;
	}
}
void build(){
	for(int i=1;i<=n;i++){
		for(int nxt:edge[i]){
			int u=col[i],v=col[nxt];
			if(u==v) continue;
			In[v]++;
			Out[u]++;
		}
	}
	for(int i=1;i<=cl;i++) if(Out[i]==0) ans=min(ans,sz[i]);
}
signed main(){
ios::sync_with_stdio(0);
cin.tie(0);
cout.tie(0);
cin>>n>>m>>h;
for(int i=1;i<=n;i++) cin>>t[i];
for(int i=1;i<=m;i++){
	int u,v;
	cin>>u>>v;
	if((t[u]+1)%h==(t[v])%h) edge[u].push_back(v);
	if((t[v]+1)%h==(t[u])%h) edge[v].push_back(u);
}
for(int i=1;i<=n;i++) if(!dfn[i]) tanjan(i);
build();
cout<<ans<<'\n';
for(int i=1;i<=cl;i++){
	if(sz[i]==ans){
		for(int output:Outans[i]) cout<<output<<' ';
		return 0;
	}
}
return 0;
}
```


---

## 作者：xixike (赞：1)

[博客食用更佳](https://www.cnblogs.com/xixike/p/15496428.html)

# Description

> [洛谷传送门](https://www.luogu.com.cn/problem/CF949C)

## 题目描述

>给出 $n$ 个数据中心，$m$ 份资料。要把 $m$ 份资料放到其中的两个数据中心备份，需要保证任意时刻都可以至少在一个数据中心进行备份。定义一天有 $h$ 个小时，每个数据中心在一天内有一小时维护时间 $u_i$（$0 \leq u_i < h$），在这一小时内该数据中心无法进行备份。
>
>由于某种原因，需要把一些数据中心的维护时间向后推迟 1 小时（一个数据中心的维护时间的向后推迟可能导致有的资料无法在任意时刻进行备份且若 $u_i = h - 1$ 那么推迟后 $u_i = 0$），请你求出最少需要向后推迟多少个数据中心，并把这些数据中心的编号输出出来。

## 输入格式

>第一行 3 个整数 $n$，$m$，$h$，含义如上。
>
>第二行 $n$ 个整数，为 $u_i$ 到 $u_n$。
>
>接下来 $m$ 行，每行 2 个整数$c_1$，$c_2$（$u_{c_1} \neq u_{c_2}$），分别表示第 $i$ 份资料可以在哪两个数据中心进行备份。

**注意：输入的 $u_{c_1} \ne u_{c_2}$，意味着刚开始时任意资料都可以在任意时间进行备份。**

## 输出格式

>第一行 1 个整数 $k$，表示最少需要推迟 $k$ 个数据中心。
>
>第二行 $k$ 个整数，分别为 $x_1$ 到 $x_k$，表示需要推迟的数据中心的编号。

# Solution

通过观察样例可以发现，不管你初始时是否合法都必须有向后推迟的数据中心，即至少一个。

所以题目就是要求我们选择一个点 +1，并将因此而被迫推迟的点都推迟 1，然后计算最少推迟多少个点。

那么我们如何找到哪些点是被迫推迟的呢？

对于一组条件 $x$ 和 $y$：

- 若 ${a_x + 1}\equiv{a_y} \pmod {h}$，我们就从 $x$ 向 $y$ 建一条边。

- 若 ${a_y + 1}\equiv{a_x} \pmod {h}$，我们就从 $y$ 向 $x$ 建一条边。

然后就形成了一张 $DAG$，考虑到在一个环里的点，不管选哪一个整个环都会被选，所以可以 $Tarjan$ 缩点。

然后不难发现，若选择出度不为 0 的点，那么它指向的那个点也会被迫选上，这明显不如只选被指向的点优。

所以我们只用找出度为 0 的点中的 $siz$ 最小的点即可。

如果还是无法理解的话，可以看着代码理解一下。

# Code

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1e5 + 10;
int n, m, h;
int a[N];
struct node{
    int u, v, nxt;
}edge[N << 1];
int head[N], tot;
int low[N], dfn[N], tim;
int stk[N], top, t[N];
int siz[N], scc[N], cnt;
int out[N];

inline void add(int x, int y){
    edge[++tot] = (node){x, y, head[x]};
    head[x] = tot;
}

void tarjan(int x){
    low[x] = dfn[x] = ++tim;
    stk[++top] = x;
    t[x] = 1;
    for(int i = head[x]; i; i = edge[i].nxt){
        int y = edge[i].v;
        if(!dfn[y])tarjan(y), low[x] = min(low[x], low[y]);
        else if(t[y]) low[x] = min(low[x], dfn[y]);
    }
    if(low[x] == dfn[x]){
        cnt++;
        do{
            siz[cnt]++;
            scc[stk[top]] = cnt;
            t[stk[top--]] = 0;
        }while(stk[top + 1] != x);
    }
}

int main(){
    scanf("%d%d%d", &n, &m, &h);
    for(int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for(int i = 1, x, y; i <= m; ++i){
        scanf("%d%d", &x, &y);
        if((a[x] + 1) % h == a[y]) add(x, y);
        if((a[y] + 1) % h == a[x]) add(y, x);
    }
    for(int i = 1; i <= n; ++i)
        if(!dfn[i]) tarjan(i);
    for(int i = 1; i <= tot; ++i){
        int u = scc[edge[i].u], v = scc[edge[i].v];
        if(u != v) out[u]++;
    }
    int ans = 0;
    siz[0] = 1e9;
    for(int i = 1; i <= cnt; ++i) 
        if(!out[i]) ans = siz[ans] > siz[i] ? i : ans;
    printf("%d\n", siz[ans]);
    for(int i = 1; i <= n; ++i)
        if(scc[i] == ans) printf("%d ", i);
    puts("");
    return 0;
}
```

# End


---

## 作者：lihongqian__int128 (赞：0)

# CF949C Data Center Maintenance题解
## 题意
$n$ 个数据中心，$m$ 份资料，每份资料存在于两个不同的数据中心，且两个数据中心的维护时间不一样，现在求最少推迟几个数据中心的维护时间，使得 $m$ 份资料仍然保证每份两个数据中心维护时间不一样。

**注意，至少推迟 $1$ 个数据中心的维护时间。**
## 分析
1. 当一个数据中心 $x$ 推迟一小时维护，可能会引起连锁反应（其他的数据中心也需要推迟）。
2. 将数据中心当做点，若 $x$ 推迟将导致 $y$ 必须推迟，则 $x$ 向 $y$ 连边（即若 $(u_x+1)\bmod h=u_y$，则 $x$ 向 $y$ 连边）。
3. 若图无环，则答案为 $1$，任意输出一个出度为 $0$ 的点即可，否则将图缩点，答案即为出度为 $0$ 的强联通分量的大小的最小值。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=1e5+5,M=1e5+5;
int n,m,h,s[N],u[N],x[M],y[M],dp[N],cnt,low[N],dfn[N],sc,scc[N],out[N],siz[N],ans=INT_MAX;
bitset<N>ins;
vector<int>g[N];
stack<int>t;
queue<int>q;
vector<int>v[N];
void SCC(int u){
	low[u]=dfn[u]=++cnt,t.push(u),ins[u]=1;
	for(int v:g[u]){
		if(!dfn[v])SCC(v),low[u]=min(low[u],low[v]);
		else if(ins[v])low[u]=min(low[u],low[v]);
	}
	if(dfn[u]==low[u]){
		++sc;
		while(t.top()!=u)scc[t.top()]=sc,ins[t.top()]=0,siz[sc]++,t.pop();
		scc[t.top()]=sc,ins[t.top()]=0,siz[sc]++,t.pop();
	}
}
bool yes(int l,int r){
	return (u[l]+1)%h==u[r];
}
int main(){
	cin>>n>>m>>h;
	for(int i=1;i<=n;i++)cin>>u[i];
	for(int i=1;i<=m;i++){
		cin>>x[i]>>y[i];
        //连边
		if(yes(x[i],y[i]))g[x[i]].push_back(y[i]);
		if(yes(y[i],x[i])){
			swap(x[i],y[i]);
			g[x[i]].push_back(y[i]);
		}
	}
    //缩点
	for(int i=1;i<=n;i++)if(!dfn[i])SCC(i);
    //统计出度
	for(int i=1;i<=m;i++)if(yes(x[i],y[i])&&scc[x[i]]!=scc[y[i]])out[scc[x[i]]]++;
    //记录答案
	for(int i=1;i<=sc;i++)if(!out[i])ans=min(ans,siz[i]);
	cout<<ans<<'\n';
    //输出方案
	for(int i=1;i<=sc;i++)
		if(siz[i]==ans){
			for(int j=1;j<=n;j++)if(scc[j]==i)cout<<j<<' ';
			return 0;
		}
	return 0;
}
```

---

## 作者：O_v_O (赞：0)

# CF949C Data Center Maintenance

## 题意

有 $n$ 个信息中心，$m$ 个客户，一天有 $h$ 个小时，编号为 $0 \dotsb h-1$。每个信息中心一天恰好有一个小时休息，每个中心的休息时间都可以推迟一个小时 （注意：推迟到 $h+1$ 小时就是 $0$），每个客户有两个中心可以使用，要求至少有一个中心的休息时间加一小时，使得每个客户任意时刻至少有一个信息中心可以使用。求改变数量最少的方案。保证有解。

## 思路

我们可以发现，如果一个信息中心的休息时间加一，他有可能会影响到其他的信息中心休息，换句话说，就是这个信息中心推迟休息，跟他有关联的信息中心就必须推迟休息，所以，我们就可以将其转化为图论问题。

我们可以将每个信息中心看作一个节点，将他会影响到的信息中心连边，然后我们就可以得到一个有向图。

然后，我们需要画一张图来理解一下：

![](https://cdn.luogu.com.cn/upload/image_hosting/kgk7jmrk.png)

我们假设图中没有环，我们看上面这张图，很明显，我们选择没有出度的那个点，也就是 $3$ 号点，如果选择其他的点，我们就会要让跟多的点推迟休息，所以，我们可以得到一个贪心策略，就是选择出度为 $0$ 的点，这样一定最优。

但是，我们只是假设图中没有环，如果存在环应该怎样呢？其实很简单，我们再套个缩点模板，将每个点的个数进行累加，然后，我们再按照上面的贪心策略，选择出度为 $0$ 的点，然后每个点取极大值就可以得到答案了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int N = 1e5 + 10;

int a[N], dfn[N], low[N], cnt, top, num[N], col[N], sum[N], b[N];
int u[N], v[N];
bool vis[N];
stack<int> s;
int n, m, h;
vector<int> e[N], ans[N];

void tarjan(int u) { // tarjan 缩点模板
  dfn[u] = low[u] = ++cnt;
  s.push(u);
  vis[u] = true;
  for (auto v : e[u]) {
    if (!dfn[v]) {
      tarjan(v);
      low[u] = min(low[u], low[v]);
    } else if (vis[v]) {
      low[u] = min(low[u], dfn[v]);
    }
  }
  if (dfn[u] == low[u]) {
    int x;
    ++top;
    do {
      x = s.top();
      s.pop();
      vis[x] = false;
      col[x] = top;
      ans[top].push_back(x);
      num[top]++; // 累加每个点的个数
    } while (x != u);
  }
}

signed main() {
  cin >> n >> m >> h;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  for (int i = 1; i <= m; i++) {
    int x, y;
    cin >> x >> y;
    if ((a[x] + 1) % h == a[y] % h) { // 如果有关系，就加边
      e[x].push_back(y);
      u[i] = x;
      v[i] = y;
    }
    // 注意，不要写 else if，因为有可能两个点都满足条件
    if ((a[y] + 1) % h == a[x] % h) {
      e[y].push_back(x);
      u[i] = y;
      v[i] = x;
    }
  }
  // tarjan 缩点模板
  for (int i = 1; i <= n; i++) {
    if (!dfn[i]) {
      tarjan(i);
    }
  }
  for (int i = 1; i <= m; i++) {
    int x = col[u[i]], y = col[v[i]];
    if (x != y) {
      // 记录每个店有没有出度
      b[x] = 1;
    }
  }
  int sum = INT_MAX, id = 0;
  for (int i = 1; i <= top; i++) {
    if (b[i] == 0) {
      if (sum > num[i]) {
        sum = num[i];
        id = i;
      }
    }
  }
  cout << sum << endl;
  for (auto x : ans[id]) {
    cout << x << " ";
  }
  return 0;
}
```

---

## 作者：GJX_Algorithm (赞：0)

# CF949C题解
## 题目描述
- $n$ 个数据中心，$m$ 份资料。

- 每份资料存在两个不同的数据中心，且两个数据中心的维护时间不一样。

- 现在求最少推迟几个数据中心的维护时间，使得 $m$ 份资料仍然保持每份的两个数据中心维护时间不一样

## 解题思路

### 1. 建图：
- 当 $1$ 个数据中心 $x$ 推迟维护 $1$ 小时维护，可能会引起连锁反应。

- 将数据中心当作点，若 $x$ 推迟导致 $y$ 必须也推迟，$x$ 向 $y$ 连有向边

- 若 $(t_x + 1) \bmod h = t_y \bmod h$，建边 $x \to y$，$(t_y + 1) \bmod h = t_x \bmod h$，建反边。

### 2. 求答案：
- 先看个图：
  ![](https://cdn.luogu.com.cn/upload/image_hosting/6rkzu03f.png)
  我们发现，答案肯定为出度为 $0$ 的点，即点 $d$ 和点 $f$。

- 那万一没有出度为 $0$ 的点怎么办？只有一种可能，**有环**。

- 考虑图有环，缩点，并维护强连通分量中原始点的个数 $num_i$。

- 答案是新图中出度为 $0$ 的强连通分量中 $num$ 的最小值。

## AC Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 1e6 + 5;
stack<int> stk;
vector<int> nbr[N];
int sum, cnt, low[N], dfn[N], scc[N], n, m, h, t[N], out[N], u[N], v[N], num[N];
bool onstack[N];
void tarjan(int cur)
{
    stk.push(cur);
    onstack[cur] = 1;
    low[cur] = dfn[cur] = ++cnt;
    for (int nxt : nbr[cur])
    {
        if (dfn[nxt] == 0)
        {
            tarjan(nxt);
            low[cur] = min(low[cur], low[nxt]);
        }
        else if (onstack[nxt] == 1) low[cur] = min(low[cur], dfn[nxt]);
    }
    if (dfn[cur] == low[cur])
    {
        sum++;
        while(stk.top() != cur)
        {
            int tmp = stk.top();
            stk.pop();
            onstack[tmp] = 0, scc[tmp] = sum, num[sum]++;
        }
        stk.pop();
        onstack[cur] = 0, scc[cur] = sum, num[sum]++;
    }
    return ;
}
signed main()
{
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> n >> m >> h;
    for (int i = 1; i <= n; i++) cin >> t[i];
    for (int i = 1; i <= m; i++)
    {
        cin >> u[i] >> v[i];
        if ((t[u[i]] + 1) % h == t[v[i]] % h) nbr[u[i]].push_back(v[i]);
        if ((t[v[i]] + 1) % h == t[u[i]] % h) nbr[v[i]].push_back(u[i]);

    }
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0)
            tarjan(i);
    for (int i = 1; i <= n; i++)
    {
        int x = scc[i];
        for (int j : nbr[i])
            if (x != scc[j]) out[x]++;
    }
    int ans = 1e18, ansid = 0;
    for (int i = 1; i <= sum; i++)
        if (out[i] == 0 && num[i] < ans) ans = num[i], ansid = i;
    cout << ans << "\n";
    for (int i = 1; i <= n; i++) if (scc[i] == ansid) cout << i << " ";
    return 0;
}

```

---

## 作者：little_cindy (赞：0)

## 算法
- Tarjan

这里就不详细解释 Tarjan 缩点原理了，如果想了解见 [P3387 【模板】缩点](https://www.luogu.com.cn/problem/P3387) 的 [题解区](https://www.luogu.com.cn/problem/solution/P3387)。
## 前言
这题的主要难度就在建图上。

关键是一眼看上去和图论好像没什么大关系。

别人说这是图论的时候我还以为是二分图（

好了，进入正题：
## 思路
我们观察可以发现，如果一个数据中心推迟一个小时，可能会影响和它共同存储某个文件的另一个数据中心。

如果数据中心 $A$ 的推迟会影响数据中心 $B$，那么 $A$ 向 $B$ 连边。

那么，什么情况会其它的数据中心呢？

假定存储数据中心 $A,B$ 存储同一个文件，如果 $A+1\equiv B(\mod h)$，那么建一条 $A$ 向 $B$ 的边。

如果有环，那么环中只要有一个延迟，整个环都必须延迟。

所以我们可以把一个环看作一个整体即可。所以，我们把这个图用 Tarjan 进行缩点。

缩完点，找到每条链的末端，即出度为 $0$ 的点。

可是，出度为 $0$ 的点中点数最少的怎么找？

用一个 $res$ 数组存储 SCC 的点数。

最后扫描一遍出度为 $0$ 的点的 $res$ 的最小值即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e5+5;//大小我瞎开的，这么大坑定够/doge
stack<int> s;//栈
int n,m,h;//如题目
int SCC[maxn];//第i个点所在的SCC编号
bool vis[maxn];//是否在栈中
int dfn[maxn],low[maxn];
vector<int> nbr[maxn];//vector存边
int cnt;//时间戳
int sum;//SCC编号
struct node{//记录边信息
	int u,v;
}edge[maxn];
int res[maxn];//SCC权值 
int w[maxn];//单点权值 
int out[maxn];//统计出度
void Tarjan(int u){//SCC板子
	s.push(u);
	vis[u]=1;
	dfn[u]=low[u]=++cnt;
	for(int i=0;i<nbr[u].size();i++){
		int nxt=nbr[u][i];
		if(dfn[nxt]==0){
			Tarjan(nxt);
			low[u]=min(low[u],low[nxt]);
		}
		else if(vis[nxt]){
			low[u]=min(low[u],dfn[nxt]);
		}
	}
	if(dfn[u]==low[u]){
		sum++;
		while(s.top()!=u){
			int cur=s.top();
			s.pop();
			vis[cur]=0;
			SCC[cur]=sum;
			res[sum]+=w[cur];//统计SCC权值 
		}
		s.pop();
		vis[u]=0;
		SCC[u]=sum;
		res[sum]+=w[u];//统计SCC权值 
	}
	return;
}
int t[maxn];
int main(){
	cin>>n>>m>>h;
	for(int i=1;i<=n;i++){
		w[i]=1;
		cin>>t[i];
	}
	for(int i=1;i<=m;i++){
		int x,y;
		cin>>x>>y;
		if((t[x]+1)%h==t[y]%h){
			nbr[x].push_back(y);
			edge[i]={x,y};
		}
		if((t[y]+1)%h==t[x]%h){
			nbr[y].push_back(x);
			edge[i]={x,y};
		}
	}
	cnt=0;
	for(int i=1;i<=n;i++){
		if(dfn[i]==0){
			Tarjan(i);
		}
	}
	for(int i=1;i<=m;i++){
		if(edge[i].u==0){
			continue;
		}
		int fx=SCC[edge[i].u];
		int fy=SCC[edge[i].v];
		int x=edge[i].u;
		int y=edge[i].v;
		if(fx!=fy){
			if((t[x]+1)%h==t[y]%h){
				out[fx]++;
			}
			if((t[y]+1)%h==t[x]%h){
				out[fy]++;
			}
		}
	}
	int ans=1e9;
	int pos=0;
	for(int i=1;i<=sum;i++){
		if(out[i]==0){
			if(res[i]<ans){
				ans=res[i];
				pos=i;
			}
		}
	}
	cout<<ans<<endl;
	for(int i=1;i<=n;i++){
		if(SCC[i]==pos){
			cout<<i<<' ';
		}
	}
	return 0;
}
```

---

## 作者：__Hacheylight__ (赞：0)

题意：

n个点，每个点有一个值a[i]。m个条件，每个条件有2个点x，y且a[x]!=a[y]。选择最少的k个点，使其值加1后，m个条件仍成立。

思路：

对于m个条件，若(a[x]+1)%h=a[y]，则加上x->y这条边；若(a[y]+1)%h=a[x]，则加上y->x这条边。则我们只需找到最小的且出度为0的SCC即可。

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <stack>
#define moder 1e9 + 7 
using namespace std ;
const int N = 1e5 +10 ;
vector <int> G[N] ;
stack <int> S ;
bool vis[N] ;
int belong[N],low[N],dfn[N],num[N],b[N],a[N] ;
int dfn_max=0,scc=0,n,m,k ; 
void Tarjan(int now){
	dfn[now]=low[now]=++dfn_max;
	S.push(now),vis[now]=true ; 
	for (int i=0;i<G[now].size();i++){
		int to=G[now][i] ;
		if (!dfn[to]){
			Tarjan(to) ;
			low[now]=min(low[now],low[to]) ;
		}
		else if (vis[to]) low[now]=min(low[now],dfn[to]);
	}
	if (dfn[now]==low[now]){
		scc++ ;
		while (1){
			int x=S.top();S.pop() ;
			belong[x]=scc ;
			num[scc]++ ;
			if (x==now) break ;
		}
	}
	return ;
}
int main(){
	scanf("%d%d%d",&n,&m,&k) ;
	for (int i=1;i<=n;i++) scanf("%d",&a[i]) ;
	for (int i=1;i<=m;i++) {
		int u,v ;
		scanf("%d%d",&u,&v) ;
		if ((a[u]+1)%k==a[v]) G[u].push_back(v) ;
		if ((a[v]+1)%k==a[u]) G[v].push_back(u) ;
	}
	for (int i=1;i<=n;i++)
	if (!dfn[i]) Tarjan(i) ;
	for (int i=1;i<=n;i++){
		for (int j=0;j<G[i].size();j++){
			int x=G[i][j] ;
			if (belong[x]!=belong[i]) b[belong[i]]++ ;
		}
	}
	int ans,MINI=moder;
	for (int i=1;i<=n;i++){
		if (!b[belong[i]] && num[belong[i]]<MINI){
			MINI=num[belong[i]] ;
			ans=belong[i] ; 
		}
	}
	printf("%d\n",MINI) ;
	for (int i=1;i<=n;i++)
	if (ans==belong[i]) printf("%d ",i) ;
	return 0 ; 
}
```

---

