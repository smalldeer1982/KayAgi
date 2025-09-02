# Biologist

## 题目描述

SmallR is a biologist. Her latest research finding is how to change the sex of dogs. In other words, she can change female dogs into male dogs and vice versa.

She is going to demonstrate this technique. Now SmallR has $ n $ dogs, the costs of each dog's change may be different. The dogs are numbered from 1 to $ n $ . The cost of change for dog $ i $ is $ v_{i} $ RMB. By the way, this technique needs a kind of medicine which can be valid for only one day. So the experiment should be taken in one day and each dog can be changed at most once.

This experiment has aroused extensive attention from all sectors of society. There are $ m $ rich folks which are suspicious of this experiment. They all want to bet with SmallR forcibly. If SmallR succeeds, the $ i $ -th rich folk will pay SmallR $ w_{i} $ RMB. But it's strange that they have a special method to determine whether SmallR succeeds. For $ i $ -th rich folk, in advance, he will appoint certain $ k_{i} $ dogs and certain one gender. He will think SmallR succeeds if and only if on some day the $ k_{i} $ appointed dogs are all of the appointed gender. Otherwise, he will think SmallR fails.

If SmallR can't satisfy some folk that isn't her friend, she need not pay him, but if someone she can't satisfy is her good friend, she must pay $ g $ RMB to him as apologies for her fail.

Then, SmallR hope to acquire money as much as possible by this experiment. Please figure out the maximum money SmallR can acquire. By the way, it is possible that she can't obtain any money, even will lose money. Then, please give out the minimum money she should lose.

## 样例 #1

### 输入

```
5 5 9
0 1 1 1 0
1 8 6 2 3
0 7 3 3 2 1 1
1 8 1 5 1
1 0 3 2 1 4 1
0 8 3 4 2 1 0
1 7 2 4 1 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
5 5 8
1 0 1 1 1
6 5 4 2 8
0 6 3 2 3 4 0
0 8 3 3 2 4 0
0 0 3 3 4 1 1
0 10 3 4 3 1 1
0 4 3 3 4 1 1
```

### 输出

```
16
```

# 题解

## 作者：liuyz11 (赞：31)

## 这篇题解写给像我这样刚学网络流的萌新
主要因为题解看了很久才懂就决定自己写篇

### 分析

分析题目，发现 $0/1 $比较麻烦，先假设所有的点都被改为 $1$ .当前的答案是：所有 $1$要求的 $w$ 之和 $-$ 所有 $0$ 点的修改代价 $-$ $g$ 乘上 $0$ 要求中要求倒给的个数.

现在，如果要满足一个 $0$要求，那么该要求所有相关的点都必须进行修改，如果一个点进行了修改，那么该点所有有关的$1$要求都不满足.

发现这个性质符合[最大权闭合子图](https://blog.csdn.net/can919/article/details/77603353)，考虑建图.

对于原先为 $0$ 的点，因为之前已经被修改过一次，如果修改该点就相当于反悔，会产生 $v$ 的贡献.

对于原先为 $1$ 的点，如果修改该点，会产生 $-v$ 的贡献.

对于每个 $0$要求，如果将该要求改为满足，那么对答案会产生 $w$ 贡献，如果该节点还要倒贴，一共会产生 $w+g$ 贡献，将贡献作为点的权值，而且所有与它相关的点都必须选，于是连该要求到所有有关的点的边.

对于每个原先 $1$ 要求，如果将该要求改为不满足，那么对答案会产生 $-w $贡献，如果还要倒贴，一共会产生 $-w-g$ 贡献，将贡献作为点的权值，而且所有与它相关的点一个被修改该要求也会不满足，所以连所有有关的点到该要求的边。

于是问题变成了当前答案加上这个图的最大权闭合子图，剩下问题就很好解决.

### 题解

把图建成网络，对于原先为 $0$ 的点，建一条源点到该点的边，边权为 $v$ ，对于原先为 $1$ 的点，建一条该点到汇点的边，边权为 $v$ .

对于 $0$要求，建一条源点到该要求的边，边权为 $w$ ，如果需要倒贴边权为 $w+g$ ，再建该要求到所有有关点的边，边权为 $\infty$ .

对于 $1$要求，建该要求到汇点的边，边权为 $-w$ ，如果需要倒贴边权为 $-w-g$ ，再建所有有关点到该要求的边，边权为 $\infty$.

最后答案加上所有正边权 $-$ 最小割，发现正边权和为所有 $0$要求 的$w$之和 $+$ 所有$0$点的修改代价 $+$ $g$ 乘上$0$要求中要求倒给的个数，发现这个数与最初答案加起来就是$\sum w$.

最后答案就是 $\sum w-$ 最小割.

如有不理解的可以画图模拟小数据方便理解.

### 代码
```cpp
//limit txdy
#include <bits/stdc++.h>
#define rep(x, l, r) for(int x = l; x <= r; x++)
#define repd(x, r, l) for(int x = r; x >= l; x--)
#define clr(x, y) memset(x, y, sizeof(x))
#define all(x) x.begin(), x.end()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define SZ(x) ((int)x.size())
using namespace std;
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pii;
const int MAXN = 3e5 + 5;
const int INF = 1 << 30;
const int mod = 1000000009;
int lowbit(int x){ return x & (-x);}
int fast_power(int a, int b){ int x; for(x = 1; b; b >>= 1){ if(b & 1) x = 1ll * x * a % mod; a = 1ll * a * a % mod;} return x % mod;}

queue<int> que;
int s, t, cnt;
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], value[MAXN << 1];
int a[MAXN], v[MAXN], dep[MAXN], cur[MAXN];

void init(){
	cnt = 0;
	clr(head, -1);
}

void add(int u, int v, int val){
	nxt[cnt] = head[u];
	head[u] = cnt;
	to[cnt] = v;
	value[cnt] = val;
	cnt++;
}

void addedge(int u, int v, int val){
	add(u, v, val);
	add(v, u, 0);
}

int bfs(){
	while(!que.empty()) que.pop();
	clr(dep, 0);
	que.push(s);
	dep[s] = 1;
	while(!que.empty()){
		int u = que.front();
		que.pop();
		for(int e = head[u]; e != -1; e = nxt[e]){
			int v = to[e];
			if(dep[v] || !value[e]) continue;
			dep[v] = dep[u] + 1;
			que.push(v);
		}
	}
	if(dep[t]) return 1;
	return 0;
}

int dfs(int u, int flow){
	if(u == t) return flow;
	for(int& e = cur[u]; e != -1; e = nxt[e]){
		int v = to[e];
		if(!value[e] || dep[v] != dep[u] + 1) continue;
		int q = dfs(v, min(flow, value[e]));
		if(q > 0){
			value[e] -= q;
			value[e ^ 1] += q;
			return q;
		}
	}
	return 0;
}

int dinic(){
	int ans = 0;
	while(bfs()){
		rep(i, s, t) cur[i] = head[i];
		while(int d = dfs(s, INF)) ans += d;
	}
	return ans;
}

int main(){
	init();
	int n, m, g;
	scanf("%d%d%d", &n, &m, &g);
	s = 0, t = n + m + 1;
	rep(i, 1, n) scanf("%d", &a[i]);
	rep(i, 1, n) scanf("%d", &v[i]);
	rep(i, 1, n){
		if(!a[i]) addedge(0, i, v[i]);
		else addedge(i, t, v[i]);
	}
	int ans = 0;
	rep(i, 1, m){
		int b, w, k;
		scanf("%d%d", &b, &w);
		ans += w;
		scanf("%d", &k);
		rep(j, 1, k){
			int x;
			scanf("%d", &x);
			if(!b) addedge(n + i, x, INF);
			else addedge(x, n + i, INF);
		}
		int p;
		scanf("%d", &p);
		if(p) w += g;
		if(!b) addedge(s, n + i, w);
		else addedge(n + i, t, w);
	}
	printf("%d\n", ans - dinic());
    return 0;
}
```

---

## 作者：fy1234567ok (赞：14)

## 最小割
### 思路
假设我们已经满足了所有的要求，那么最大的收益是每个要求满足后的收益的和那么问题就等价于，我损失哪些要求，可以让我得到最小的损失。在建图的时候用最小割的思维考虑，使得最后的最小割就是最小的损失。

$$  ans=\sum_{i=1}^{m} w_{i} -MinCut $$

所以边就一定要和价值联系到一起。我们考虑一个要求：

* 要么我割断所有改变0和1的边来满足它
* 要么我放弃这个要求，割断它的价值边

### 建图
那么我们的建图就可以这么考虑：

* **原始结点**

如果一个点是1，那么向t连边，价值是转换的价值。如果一个点是0，就从s向它连边，价值也是对应转换的价值。

* **要求**

如果是要0的要求，那么从起点向它连边权为对应收益的边，然后从该要求点向所有的有关节点连正无穷的边。

如果是要1的要求，那么从所有有关节点向它连正无穷的边，然后从该要求节点连向终点，价值为对应的收益。

如果一个要求不满足会扣钱，也就是说满足了是$w_{i}$的收益，没有满足时$-g$ 的收益。两者差值是$w_{i}+g$ ，所以它来作为边权。

### 举例

一共3个节点分别是101，2个要求，第一个要求1和2是0，第二个要求2和3是1并且不满足要扣钱，那么可以画出下面的示意图
![示意图](https://cdn.luogu.com.cn/upload/image_hosting/39a3l6mo.png)

### 代码
``` cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 100010*2;

typedef long long typec;  // 为了方便转换类型
const typec oo = 1e9;

int n, m, s, g, t, head[maxn], nxt[maxn], to[maxn], dep[maxn], cur[maxn], tot = 1;
int W[maxn], A[maxn];
typec w[maxn], sum;

queue<int> Q; 

void add(int x, int y, int v) {
    to[++tot] = y, w[tot] = v, nxt[tot] = head[x], head[x] = tot;
    to[++tot] = x, w[tot] = 0, nxt[tot] = head[y], head[y] = tot;
}

bool bfs() {
    memset(dep, 0, sizeof(dep));
    Q.push(s); dep[s] = 1;
    while(!Q.empty()) {
        int u = Q.front();
        Q.pop();
        for (int i = head[u]; i; i = nxt[i]) 
            if (w[i] && !dep[to[i]]) {
                dep[to[i]] = dep[u] + 1;
                Q.push(to[i]);
            }
    }
    return dep[t];
}

typec dfs(int x, typec flow) {
    if (x == t) return flow;
    typec rest = flow;
    for (int& i = cur[x]; i; i = nxt[i]) 
        if (w[i] && dep[to[i]] == dep[x] + 1) {
            typec k = dfs(to[i], min(w[i], rest));
            if (!k) dep[to[i]] = 0;
            rest -= k; w[i] -= k; w[i ^ 1] += k;
        }
    return flow - rest;
}

typec dinic() {
    typec ret = 0, flow;
    while (bfs()) {
        memcpy(cur, head, sizeof(cur));
        while (flow = dfs(s, oo)) ret += flow;
    } 
    return ret;
}

int main() {
    cin >> n >> m >> g;
    s = 0; t = n + m + 1;
    for (int i = 1;i <= n; ++i) cin >> A[i];
    for (int i = 1,x;i <= n; ++i) {
        cin >> x;
        if (A[i]) add(s, i, x);
        else add(i, t, x);
    }

    for (int i = 1,x,y,z;i <= m; ++i) {
        int op, k, neg;
        cin >> op >> W[i] >> k;
        sum += W[i];
        for (int j = 1;j <= k; ++j) {
            cin >> x; 
            if (op) add(n+i, x, oo);
            else add(x, n+i, oo);
        }
        cin >> neg;
        if (op) add(s, n+i, W[i] + neg*g);
        else add(n+i, t, W[i] + neg*g);
    }
    cout << sum - dinic() << endl;
    return 0;
}


---

## 作者：Gmt丶FFF (赞：9)

前置知识：最大权闭合子图。

这是个什么东东呢，它是对于每一个点赋一个值，求一个点集，点集内的所有点都必须包含它的所有后继，使这个点集的和最大。

如以下图：
![](https://cdn.luogu.com.cn/upload/image_hosting/7cccrdgd.png)

图中的编号代表点权。

可以知道的是，能选择的点集有：$\left\{-3\right\},\left\{-3,4\right\},\left\{-3,5\right\},\left\{-3,4,5\right\},\left\{-3,4,5,-1\right\},\left\{-3,4,5,-1,2\right\},\emptyset$。

最大的明显为 $\left\{-3,4,5,-1,2\right\}$，为 $-3+4+5-1+2=7$。

这种类型的题我们如何解决呢，首先对于点权为负的，我们对其于汇点建边，而为正的点则用源点与其建边，其他边不变，原来图上的边设为正无穷，而新建的边为点权的绝对值。

![](https://cdn.luogu.com.cn/upload/image_hosting/zyj0uvs4.png)

没有设边权的代表边权无限大。

那么我们在这上面跑一次最小割，然后用所有从源点出发的边权和减去最小割即可，如图中，边权和为 $11$，最小割为 $4$，那么答案即为 $7$。

考虑证明：

首先割掉一条源点上的边代表你不会选择这个点，而割掉连向汇点上的一条边代表你会选择这个点。

很好说明，因为在割去汇点上的边时，代表你要选这个点，且正点也用流量与负点进行了抵消。

如果图不联通，那么选的点集一定合法，因为如果联通，说明你选择了正点，而正点有负点后继没有进行选择。

所以综上所言，我们就可以用最小割求出这个问题了。

那么如何证明这是最优解呢。

我们知道：最小割为：$\text{不选的正权}+\text{要选的负权的绝对值}$。

而答案为：$\text{正权和}-\text{不选的正权和}+\text{选择的负权和}$，后面那个即是最小割，由于最小割保证了最小，所以答案也就最大。

---

那么这个最大权闭合子图有什么用呢，那就先看到我们这道题：[CF311E Biologist](https://www.luogu.com.cn/problem/CF311E)。

这题一下貌似没什么思路，先进行分析。

首先我们假设所有点初始为 $1$，那么所有的 $1$ 的询问我们都是满足的。

现在我们想满足一些 $0$ 的询问，那么对于本来是 $0$ 的点，等同于我们需要把点权加回来，而本来是 $1$ 的点，则要扣去其费用。

对于本来是 $0$ 的询问，满足以后要加回本应有的钱，如果要倒扣也要加回来。

而对于本来是 $1$ 的询问，由于点变为 $0$ 导致无法满足，所以将其全部扣除应得的钱。

那么可以把加操作看成点权为正，源点与其相连，而减操作看成点权为负，与汇点相连。

那么这次的最后答案是什么呢。

首先最小割为：$\text{没加上的点}+\text{减去的点的绝对值}$。

而由于我们假使所有数为 $1$，所以答案为 $1$ 询问减去修改 $0->1$ 再减去 $0$ 的倒扣钱。而这次与源点连接的所有边权和为 $0$ 询问加上修改 $0->1$ 加上 $0$ 的倒扣钱。

两者加起来即为所有询问的价值，即 $\sum W_i$。

最终答案即为 $\sum W_i-\text{最小割}$。

总结一下总过程：

1、对原来为 $0$ 的点，用源点与其建边，边权为其改变状态的价值。

2、对原来为 $1$ 的边，对汇点建边，边权为其改变状态的价值。

3、对于每一个 $0$ 询问，单独重新创一个点，用源点与其相连，边权为其钱数，如果要倒扣，边权加上倒扣的钱即可，然后用这个新点对询问的点建边，边权为无限（即如果选这个询问它的后继都要选择改变状态）。

4、对于每一个 $1$ 询问，单独创一个点，对汇点建边，边权为其钱数，如果要倒扣，边权加上倒扣的钱即可，然后用询问的点对这个新点建边，边权为无限（即如果要选择一个连向新点的点，那就要扣除这个点）。

建了边后跑最小割即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
const int N=1e6+5;
const int M=2e6+5;
int n,m,g,h[M],p[N],s,t,st[N],cnt,vis[N],dep[N];
struct node
{
	int to,data,next;
}a[M];
inline void addedge(int x,int y,int k)
{
	a[cnt]={y,k,h[x]};
	h[x]=cnt++;
	a[cnt]={x,0,h[y]};
	h[y]=cnt++;
}
queue<int>q;
bool bfs()
{
	//cout<<'b';
	for(int i=1;i<=n+m+2;i++)dep[i]=0;
	q.push(s);
	dep[s]=1;
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for(int i=h[x];i!=-1;i=a[i].next)
		{
			if(a[i].data==0)continue;
			if(!dep[a[i].to])
			{
				dep[a[i].to]=dep[x]+1;
				q.push(a[i].to);
			}
		}
	}
	return dep[t];
}
int dfs(int x=s,int num=1e9)
{
	if(x==t)return num;
	if(vis[x])return 0;
	for(int i=h[x];i!=-1;i=a[i].next)
	{
		if(a[i].data==0)continue;
		if(dep[a[i].to]==dep[x]+1)
		{
			vis[x]=1;
			int sum=dfs(a[i].to,min(num,a[i].data));
			if(sum)
			{
				a[i].data-=sum;
				a[i^1].data+=sum;
				return sum;
			}
		}
	}
	return 0;
}
int main()
{
	memset(h,-1,sizeof(h));
	scanf("%d%d%d",&n,&m,&g);
	s=n+m+1;
	t=n+m+2;
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<=n;i++)
	{
		int x;
		scanf("%d",&x);
		if(p[i]==0)addedge(s,i,x);
		else addedge(i,t,x);
	}
	int ans=0;
	for(int i=1;i<=m;i++)
	{
		int opt,w,k,ss;
		scanf("%d%d%d",&opt,&w,&k);
		ans+=w;
		for(int j=1;j<=k;j++)scanf("%d",&st[j]);
		scanf("%d",&ss);
		for(int j=1;j<=k;j++)
		{
			if(opt==0)addedge(i+n,st[j],w+ss*g);
			else addedge(st[j],i+n,w+ss*g);
		}
		if(opt==0)addedge(s,i+n,w+ss*g);
		else addedge(i+n,t,w+ss*g);
	}
	while(bfs())
	{
		memset(vis,0,sizeof(vis));
		int num=dfs();
		while(num)
		{
			ans-=num;
			memset(vis,0,sizeof(vis));
			num=dfs();
		}
	}
	printf("%d",ans);
	return 0;
}
```


---

## 作者：wuzhaoxin (赞：8)

# 最小割

~~感觉和[P1646 [国家集训队]happiness](https://www.luogu.org/problemnew/show/P1646)差不多~~

记 $sum = \sum_{i = 1}^{m} w_i$，答案就是 $sum$ 减去最小割

## 建图

对于 $v_i = 0$ 的点，我们把它和源点连边，权值为修改的代价，表示让这个点不为 $0$ 需要的代价，对于其它的点，我们把它和汇点连边，权值为修改的代价，表示让这个点不为 $1$ 需要的代价

对于一个 $op = 0$ 的要求，从它向每个在这个集合中的点连权值为 $inf$ 的边，如果需要到给钱，则从源点连一条权值为 $w_i + g$ 的边，否则连一条权值为 $w_i$ 的边，表示如果这个条件没有满足，需要减少这么多的利润

对于一个 $op = 1$ 的要求，和上面相反（详见代码）

然后直接最大流就做完了

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int gi() {
	register int x, op = 1, c;
	while(c = getchar(), c < '0' || c > '9')if(c == '-')op = -op;
	x = c ^ 48;
	while(c = getchar(), c >= '0' && c <= '9')x = (x << 3) + (x << 1) + (c ^ 48);
	return x * op;
}
#define MAXV 100001
#define MAXE 1000001
int head[MAXV] = {0}, ver[MAXE], val[MAXV], nxt[MAXV], tot = 1;
void add(int x, int y, int v) {
	ver[++ tot] = y, val[tot] = v, nxt[tot] = head[x], head[x] = tot;
	ver[++ tot] = x, val[tot] = 0, nxt[tot] = head[y], head[y] = tot;
}
int d[MAXV];
int s, t;
queue<int>q;
bool bfs() {
	memset(d, 0, sizeof(d));
	register int x;
	q.push(s);
	d[s] = 1;
	while(!q.empty()) {
		x = q.front(), q.pop();
		for(int i = head[x]; i; i = nxt[i])
			if(val[i] && ! d[ver[i]]) {
				d[ver[i]] = d[x] + 1;
				q.push(ver[i]);
			}
	}
	return d[t];
}
int dfs(int x, int flow) {
	if(x == t) return flow;
	register int k, rest = flow;
	for(int i = head[x]; i && rest; i = nxt[i])
		if(val[i] && d[ver[i]] == d[x] + 1) {
			k = dfs(ver[i], min(val[i], rest));
			if(! k) d[ver[i]] = 0;
			rest -= k;
			val[i] -= k;
			val[i ^ 1] += k;
		}
	return flow - rest;
}
int dinic() {
	int ans = 0, flow;
	while(bfs()) while((flow = dfs(s, 1e9))) ans += flow;
	return ans;
}
bool a[10001];
int main() {
	int n = gi(), m = gi(), g = gi();
	for(int i = 1; i <= n; i ++)a[i] = gi();
	int sum = 0;
	s = 0, t = n + m + 1;
	for(int i = 1, v; i <= n; i ++) {
		v = gi();
		if(! a[i]) add(s, i, v);
		else add(i, t, v);
	}
	for(int i = 1; i <= m; i ++) {
		int op = gi(), w = gi(), k = gi();
		if(op) {
			for(int j = 1; j <= k; j ++) add(gi(), n + i, 1e9);
			op = gi();
			if(op)add(n + i, t, g + w);
			else add(n + i, t, w);
			sum += w;
		} else {
			for(int j = 1; j <= k; j ++) add(n + i, gi(), 1e9);
			op = gi();
			if(op) add(s, n + i, g + w);
			else add(s, n + i, w);
			sum += w;
		}
	}
	printf("%d\n", sum - dinic());
	return 0;
}
```



---

## 作者：AmiyaCast (赞：2)

## 两者选其一的建模思路
相信很多人都是因为学最大权闭合子图然后找到的这道题，我在这里提供一种一般的 **两者选其一** 的建模思路。

首先，我们回顾一下两者选其一的模型：有若干个元素，元素 $p_i$ 放在集合 $A$ 中有 $a_i$ 的收益，放在集合 $B$ 中有 $b_i$ 的收益（下称第一部分），某些元素 $p_{k_1},p_{k_2} ,p_{k_3}...$ 同时放在集合 $A$ 有 $a_J$ 的收益,放在集合 $B$ 有 $b_J$ 的收益（ $J$ 是上述 $k_1,k_2,k_3...$ 所属的集合）（下称第二部分）。

两者选其一模型的建模方法不多赘述，可以参考[两者选其一](https://zhuanlan.zhihu.com/p/123308502)。

我们考虑一下很直接的建模方式，一个位置 $i$，那么不修改他的收益是 $0$，修改他的收益是 $-v_i$，负边权怎么处理？

我们可以这样，先假设所有的位置全被反转，这样的初始的收益就是 $-\sum{v_i}$，这样可以转化成，如果一个位置 $i$ 原来是 $0$，那么他在 $0$ 集合的收益就是 $v_i$，在 $1$ 集合就是 $0$（$0$ 体现在网络流上可以不用建边）；如果位置 $i$ 原来是 $1$，那么他放在 $1$ 集合的收益就是 $v_i$，在 $0$ 集合就是 $0$。这样就完成了第一部分。

然后就是同时放进集合的收益，这个正常按照套路建模就行了。注意怎样去处理题目中损友的 $g$，这个我们想一下两者选其一的求解思路，是收益和减去建模后的最小割，在最小割中，收益和代表了所有条件都满足的总收益，最小割中一条边表示不选这个收益，那我们可以这样建模：求和的部分还是正常的对 $w_i$ 求和，在建图的时候，如果一个条件是损友提出的，那么只需要把这条边的边权改成 $w_i$ + $g$ 就可以了。

### Code

```cpp
#include<bits/stdc++.h>
#define ll long long
#define pii make_pair
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define per(i,a,b) for(int i=b;i>=a;--i)
const ll inf = 1145141919810;
using namespace std;
inline ll read(){
    ll x=0,f=1;
    char c=getchar();
    while (c<'0' || c>'9'){
        if (c=='-')  f=-1;
        c=getchar();
    }
    while (c>='0' && c<='9'){
        x=x*10+c-'0';
         c=getchar();
    }
    return x*f;
}
inline void print(ll x){
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) print(x / 10);
	putchar(x % 10 + '0');
	return ;
}
inline void pprint(ll x){print(x); puts("");}
#define ll long long
const int N = 1e4 + 7;
struct Dinic {//Dinic的板子，封装在了结构体中
	ll st, ed, n, m, cnt;
	vector<int> nxt, to, head, pre, cur;
	vector<ll> c, d;
	Dinic(int _n, int _m, int _st, int _ed){//点数，边数，原点，会点。
		n = _n, m = _m, st = _st, ed = _ed, cnt = 1;
		nxt.resize(2 * m + 1), to.resize(2 * m + 1), c.resize(2 * m + 1);
		head.resize(n + 1), pre.resize(n + 1), cur.resize(n + 1), d.resize(n + 1);
	}
	void Add(int x, int y, ll z) {
		nxt[++cnt] = head[x], to[cnt] = y, c[cnt] = z, head[x] = cnt;
	}
	void add(int x, int y, ll z){
		Add(x, y, z), Add(y, x, 0);
	}
	bool bfs() {
		for(int i = 1; i <= n; ++i) d[i] = 0;
		queue<ll>q;
		q.push(st);
		d[st] = 1;
		while(q.size()) {
			int x = q.front();
			q.pop();
			for(int i = head[x]; i; i = nxt[i]) {
				int y = to[i];
				if(d[y] == 0 && c[i]) {
					d[y] = d[x] + 1;
					q.push(y);
					if(y == ed) return 1;
				}
			}
		}
		return 0;
	}
	ll dfs(int x, ll mf) { // mf表示剩余的流量
		if(x == ed) return mf;
		ll sum = 0;
		for(int i = cur[x]; i; i = nxt[i]) {
			cur[x] = i;
			int y = to[i];
			if(d[y] == d[x] + 1 && c[i]) {
				ll f = dfs(y, min(c[i], mf));
				c[i] -= f;
				c[i ^ 1] += f;
				sum += f;
				mf -= f;
				if(mf == 0) break;
			}
		}
		if(sum == 0) d[x] = 0;//剪枝
		return sum;//这个就是这个点的ans
	}
	ll dinic() {
		ll flow = 0;
		while(bfs()) {
			cur = head;
			flow += dfs(st, inf);
		}
		return flow;
	}
};

int t[N];
int v[N];
ll s = 0;
int main() {
	int n = read(), m = read();
	ll g = read();
	rep(i, 1, n)
		t[i] = read();
	rep(i, 1, n)
		v[i] = read(), s -= v[i];

	int st = n + m + 1, ed = n + m + 2;
	Dinic d(n + m + 5, n + m * (11 + 1), st, ed);
	
	rep(i, 1, n){
		if(t[i] == 0){
			d.add(st, i, v[i]);
		}else{
			d.add(i, ed, v[i]);
		}
		s += v[i];
	}
	
	int cnt = 0;
	rep(i, 1, m){
		int want = read();
		int nd = n + (++cnt);
		ll w = read(); s += w;
		int k = read();
		
		rep(j, 1, k){
			if(want == 0){
				d.add(nd, read(), inf);
			}else{
				d.add(read(), nd, inf);
			}
		}
		
		int opt = read();

		if(opt == 1)
			w += g;
		
		if(want == 0){
			d.add(st, nd, w);
		}else{
			d.add(nd, ed, w);
		}
	}
	pprint(s - d.dinic());
	return 0;
}
```

~~回想一下，最大权闭合子图好像就是用的两者选其一的思路?~~

---

## 作者：Aftglw (赞：2)

### 最小割

[双倍经验！！](https://www.luogu.com.cn/problem/P4313)

[三倍经验！！！](https://www.luogu.com.cn/problem/P1361)

这道题又是一道的经典的最小割模型：**集合划分**。

思路和建图大致都和我放的**经验**一样：先将所有利润加起来，再减去最小代价（即最小割），便是最大利润了。而对于每个要求新建两个节点连边即可。详细可见[这道题](https://www.luogu.com.cn/problem/P4313)的思路和建图，这里顺便安利一波我写的[题解](https://www.luogu.com.cn/blog/hzxswer/solution-p4313)qwq。

但是这道题不同的地方就在于对于每个位置，改变数字有代价；对于每个要求，无法满足也有代价。但是我们的最小割算的是收益。

其实很简单，我们发现在最小割中，格割掉一条边，也就是付出这条边容量的代价。所以我们只需根据题意将一些边的容量设为这个代价即可（具体哪些边建图里面讲）。

### 建图

以下每个位置在最小割后，若与 $s$ 联通，则表明该位置最终为 $0$，若与 $t$ 联通，则表明该位置最终为 $1$。

源点连每个位置，每个位置连汇点，容量均为 $0$。如果该位置的初始数为 $1$，则将该位置与 $s$ 连的边容量改为修改代价；反之若为 $0$，则将该位置与 $t$ 连的边容量改为修改代价。（这里有点绕：如果初始为 $0$，那么以后想要将他改为 $1$，也就意味着在最小割中，让这个点从 $s$ 子集转到 $t$ 子集，那么就需要割掉这条与 $s$ 相连的边，并付出代价）。

对于每一个要求 $i$，新建两个点 $x_i,y_i$：

$s$ 连 $x_i$ 容量为 $0$，$y_i$ 连 $t$ 容量为 $0$。然后要求是什么就把利润给哪条边（$0$ 就将连 $s$ 边容量改为利润，$1$ 就改连 $t$ 的边）

对于该要求的每个位置 $j\in i$：
   
$x_i$ 连 $j$ 容量为 $+\infty$，$j$ 连 $y_i$ 容量为 $+\infty$。连 $+\infty$ 是为了保证该要求内的每个位置的数值统一。

如果完成不了有代价，那么就将容量为利润的边的容量再加上 $g$，但是这个 $g$ 不用加入到利润之和中。如果无法完成要求，自然就会割掉这条代表利润的边，表示放弃这份利润，同时也付出了代价，最终利润也就减掉了这份利润 $+$ $g$。

最后答案为 $\sum_{i=1}^mW_i-Mincut$。

### Code
```cpp
#include<bits/stdc++.h>
//#define int long long
#define pair pair<int,int>
using namespace std;
inline void end()
{
	puts("");
	system("pause");
}
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9') {if(c=='-') f=-1;c=getchar();}
	while (c>='0'&&c<='9') x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return x*f;
}
const int N=3e4+4,M=5e5+5;
int n,m,g,s,t,ans,Maxflow;
int first[N],nex[M],to[M],w[M],num=1;
inline void add(int u,int v,int val)
{
	nex[++num]=first[u];
	first[u]=num;
	to[num]=v;
	w[num]=val;
}
inline void Add(int u,int v,int val)
{
	add(u,v,val);
	add(v,u,0);
}
namespace ISAP
{
	int dep[N],gap[N],cur[N];
	void bfs()
	{
		memset(dep,-1,sizeof(dep));
		memset(gap,0,sizeof(gap));
		queue<int> q;
		q.push(t);
		dep[t]=0;gap[0]=1;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int i=first[u];i;i=nex[i])
			{
				int v=to[i];
				if(dep[v]!=-1) continue;
				dep[v]=dep[u]+1;
				gap[dep[v]]++;
				q.push(v);
			}
		}
	}
	inline int dfs(int u,int in)
	{
		if(u==t) return in;
		int out=0;
		for(int i=cur[u];i;i=nex[i])
		{
			cur[u]=i;
			int v=to[i];
			if(!w[i]||dep[v]!=dep[u]-1) continue;
			int res=dfs(v,min(w[i],in-out));
			w[i]-=res;
			w[i^1]+=res;
			out+=res;
			if(in==out) return out;
		}
		gap[dep[u]]--;
		if(!gap[dep[u]]) dep[s]=n+m+m+3;
		dep[u]++;
		gap[dep[u]]++;
		return out;
	}
	void work()
	{
		bfs();
		while(dep[s]<n+m+m+2)
		{
			memcpy(cur,first,sizeof(first));
			Maxflow+=dfs(s,1e9);
		}
	}
}
int kind[N];
int main()
{//s->0,t->1
	n=read(),m=read(),g=read();
	s=0,t=n+m+m+1;//n个位置+2m个因要求新建的点
	for(int i=1;i<=n;++i) kind[i]=read();
	for(int i=1;i<=n;++i)
	{
		int x=read();//这里注意别建反了
		if(kind[i]) Add(i+m,t,x),Add(s,i+m,0);
		else Add(i+m,t,0),Add(s,i+m,x);
	}
	for(int i=1;i<=m;++i)
	{
		int kk=read(),val=read(),siz=read();ans+=val;//只加利润，别加代价
		if(kk) Add(i+n+m,t,val),Add(s,i,0);
		else Add(s,i,val),Add(i+n+m,t,0);
		while(siz--)
		{
			int x=read();
			Add(i,x+m,1e9);
			Add(x+m,i+m+n,1e9);
		}
		int kkk=read();
		if(kkk)
		{
			if(kk) Add(i+n+m,t,g);
			else Add(s,i,g);
		}
	}
	ISAP::work();
	printf("%d",ans-Maxflow);
	end();
	return 0;
}
```


---

## 作者：CAICAIA (赞：1)

# CF311E Biologist题解

非常好的一道最小割。

## 思路

首先看到每一个位置又会有 $0 1$ 两种情况，然后要满足一些要求，求最大收益，考虑类似于 [P4313 文理分科](https://www.luogu.com.cn/problem/P4313) 和 [P1361 小M的作物](https://www.luogu.com.cn/problem/P1361) 这种**集合划分**的建图方法，也就是要用最小割求解。

由于我们要求的是最大收益，所以我们要先明确要最小化什么，然后用 **所有可能获得的收益** 减去 **最小割** 就是 **最大收益**。

根据题意，我们首先希望反转某个位置的代价尽可能小，同时被割去的收益和朋友的赔礼也应该尽可能小，也就是要最小化 **反转的代价** **不能选的要求** 和 **朋友的赔礼**。

每一个位置有 $0 1$ 两种情况，考虑将所有一开始为 $1$ 的点放在左边 ( $1$ 集合)，为 $0$ 的点放在右边 ( $0$ 集合)，分别于 $S,T$ 连容量为 $v_i$ 的边。

其中，割掉 $1$ 集合中的点 与 $S$ 相连的边则表示这个点属于 $0$ 这个集合，同样，割掉 $0$ 集合中的点 与 $T$ 相连的边则表示这个点属于 $1$ 集合。

反转某个位置的代价考虑完了，现在开始解决那些要求。

先考虑 要求每个位置都为 $1$ 的要求。

现在考虑这样一种情况。

![](https://cdn.luogu.com.cn/upload/image_hosting/9gvn8qx8.png)

其中 `2 3 4` 属于 $1$ 集合， `1 5` 属于 $0$ 集合。 同时我们要求 `2 3` 都为 $1$ 可以获得 $w_i$ 的收益。

考虑这么建图：

![](https://cdn.luogu.com.cn/upload/image_hosting/2gs0fjls.png)

如果 `2 3` 都为 $1$ ,则不会割去任何边。如果 `2 3` 有一个不为 $1$ ，则会割去 $w_i$ 和那些点反转的边，满足题意。

![](https://cdn.luogu.com.cn/upload/image_hosting/ei3y7lv1.png)

现在我们要求 `1 4 5` 都为 $0$ 可以获得 $w_i$ 收益。

也就是这种情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/15npulmu.png)

同样的，因为我们不能割去 $inf$ 的边，所以，如果我们不想割掉这个要求，就必须让 `4` 属于 $0$ 集合，也就是得割去 $2$ 那条边，否则就必须割去 $w_i$ 。

现在只剩下朋友的要求没有解决了。

很简单，如果某个要求是朋友提出的，只需要在 $w_i$ 上加上 $g$ 。

分析这样做的正确性：我们的答案为 $\sum\limits_{i=1}^m{w_i}-最小割$ ，再加上朋友的要求之后，如果某个要求被割掉了，答案同样也会减去 $g$ ，满足题意。

综上所述：

```cpp
S -> 一开始为1的点 连容量为 vi 的边。
一开始为0的点 -> T 连容量为 vi 的边。

对于每个要求：
    新建一个点a。
    
    如果要求每个数字为1：
      S -> a 容量为 wi (+pi)
      a -> 所以要求的点 容量为 inf 的边

    如果要求每个数字为0：
      b -> T 容量为 wi (+pi)
      所以要求的点 -> b 容量为 inf 的边

```

最后答案为 $\sum\limits_{i=1}^m{w_i}-最小割$ 。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MX_N=50100,MX_M=500100;
const int INF=0x3f3f3f3f;
struct node{
    int to,next,w;
}edge[MX_M<<1];
int head[MX_N]={0},edge_cnt=0;
inline void Add(int x,int y,int w){
    node &i=edge[edge_cnt];
    i.w=w,i.to=y,i.next=head[x];
    head[x]=edge_cnt++;
}
inline void add(int x,int y,int w){
    Add(x,y,w),Add(y,x,0);
}
int s=0,t=MX_N-1;
int cur[MX_N]={0},dist[MX_N]={0};
bool bfs(){
    for(int i=0;i<MX_N;i++)  cur[i]=head[i],dist[i]=-1;
    queue<int > qu;qu.push(s);dist[s]=0;
    while(!qu.empty()){
        int now=qu.front();qu.pop();
        for(int i=head[now];i!=-1;i=edge[i].next){
            int to=edge[i].to;
            if(dist[to]==-1&&edge[i].w){
                dist[to]=dist[now]+1;
                qu.push(to);
            }
        }
    }
    return dist[t]!=-1;
}
int dfs(int now,int flow){
    if(now==t)  return flow;
    int left=flow;
    for(int &i=cur[now];i!=-1;i=edge[i].next){
        int to=edge[i].to,w=edge[i].w;
        if(dist[to]==dist[now]+1&&w){
            int cur_flow=dfs(to,min(left,w));
            left-=cur_flow;
            edge[i].w-=cur_flow;
            edge[i^1].w+=cur_flow;
            if(left==0)  break;
        }
    }
    if(flow==left)  dist[now]=-1;
    return flow-left;
}
int dinic(){
    int sum=0;
    while(bfs()){
        sum+=dfs(s,INF);
    }
    return sum;
}
bool st[10100]={0};
signed main(){
    memset(head,-1,sizeof(head));
    //=======================================================
    int n,m,g;scanf("%d%d%d",&n,&m,&g);
    for(int i=1;i<=n;i++)  scanf("%d",&st[i]);
    for(int i=1;i<=n;i++){
        int vi;scanf("%d",&vi);
        if(st[i]){
            add(s,i,vi);
        }
        else{
            add(i,t,vi);
        }
    }
    int sum=0;
    for(int i=1;i<=m;i++){
        int op,wi,ki;scanf("%d%d%d",&op,&wi,&ki);sum+=wi;
        for(int j=1;j<=ki;j++){
            int xi;scanf("%d",&xi);
            if(op)  add(i+n,xi,INF);
            else  add(xi,i+n,INF);
        }
        int fri;scanf("%d",&fri);
        if(op){
            add(s,i+n,wi+fri*g);
        }
        else{
            add(i+n,t,wi+fri*g);
        }
    }
    printf("%d",sum-dinic());
    //=======================================================
    return 0;
}//CF311E
```

求过，求关注。

---

## 作者：AC_love (赞：1)

一开始想法是把互相矛盾的要求两两连边容量为 `inf`，注意到这是个二分图，两边分别向源点和汇点连边，然后跑一跑最小割，但是很快发现这样做是错的：因为本题中修改某个位置也需要付出一定代价。

那么我们就考虑把修改某个位置的代价也加进图里。

我们先把所有位置都加入图中，如果一个点初始为 $0$，我们就从源点向它连边，容量为修改代价。如果为 $1$，就从它向汇点连边，容量为修改代价。

对于每个要求，如果要求每个位置都是 $0$，那么从源点向它连边，容量为收益，再从这个点向所有要求的节点连边，容量为 `inf`。如果要求每个位置都是 $1$，那么从这个点向汇点连边，容量为收益，再从所有它要求的点向它连边，容量为 `inf`。

注意如果某个要求不满足还要倒贴钱，这个要求的容量要加上 $g$，代表舍弃这个要求需要额外付出 $g$ 的代价。

此时跑一跑最小割即可，答案为总收益减去最小割。

---

## 作者：Illusory_dimes (赞：1)

### 题目大意
已经不知道还会有几倍经验了

[一倍](https://www.luogu.com.cn/problem/P1361)

[两倍](https://www.luogu.com.cn/problem/P4313)

[三倍](https://www.luogu.com.cn/problem/P1646)

[四倍（也就是本题](https://www.luogu.com.cn/problem/CF311E)

有一个长度为 $n$ 的 $01$ 串，将第 $i$ 个位置变为另外一个数字的代价是 $v_i$ 。

有 $m$ 个要求，给定 $k$ 个位置，确定条件是 $0$ 或者 $1$ ，只有全部给定的位置都满足条件，才可以得到 $w_k$ 收益，而且其中一些要求没满足还要倒贴 $g$ 收益

求最大收益

$1\leq n\leq 10^4$ ， $1\leq m\leq 2\cdot 10^3$ ， $1\leq k\leq 10$ ， $1\leq g,v_i,w_k\leq 10^4$

### solution
一共就两种初始情况，“二分图”上最小割无疑了，左边一溜就定为初始为 $0$ 的位置，右边一溜就定为初始为 $1$ 的位置。

设一个源点，一个汇点，对于 $v_i$ ，直接加边就行了。

那么怎么处理所有要求呢？

因为一旦有一个位置没有达到与其他为同一个条件，这个要求的收益值就作废了，那么就意味着要用一个手段，促使所有位置会被“绑定”到一起，才能触发这个收益。

所以，对于每一个要求，珂以新建一个点，把要求里面的位置与新点建立联系，权值为 $\infty$ 。

完了吗？

没有，

直接由要求内所有位置连向新点肯定是有问题的，大概画一下图应该就能明白，如果要跟着整个图的大潮流走（跑“二分图”），要由初始为 $0$ 的位置连向新点，由新点连向初始为 $1$ 的位置。

最大收益就是全部要求提供的的收益值总和减去最小割。（注：千万不要加上倒贴的 $g$ ，因为这不是算在收益中，而是算在代价中）。

具体看看代码吧（码风很清奇，请慎用
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e4+10,M=8e4+10;
const int INF=0x3f3f3f3f;
int n,m,g,s,t,cur[N],gap[N],dep[N],q[N];
//cur[i]:当前弧优化,gap[i]:GAP优化 
int fst[N],nxt[M],to[M],val[M],tot=2;
int ans,a[N];
inline int read()
{
	int s=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	return s*w;
}
inline void add(int u,int v,int w)
{
	nxt[tot]=fst[u];
	to[tot]=v,val[tot]=1ll*w;
	fst[u]=tot;++tot;
	nxt[tot]=fst[v];
	to[tot]=u,val[tot]=0;
	fst[v]=tot;++tot;
}
inline void bfs()
{
	for(int i=s;i<=t;++i)
	dep[i]=q[i]=gap[i]=0;
	int hd=0,tl=1;
	dep[t]=1,gap[1]=1;q[tl]=t;
	//这是从汇点开始
	while(hd<tl)
	{
		int u=q[++hd];
		for(int i=fst[u];i;i=nxt[i])
		{
			int v=to[i];
			if(!dep[v])
			{
				dep[v]=dep[u]+1;
				++gap[dep[v]];
				q[++tl]=v;
			}
		}
	}
}
ll dfs(int u,ll lim)
{
	if(u==t)return lim;
	int ans=0,tmp;
	for(int i=cur[u];i;i=nxt[i])
	{
		int v=to[i];
		cur[u]=i;
		if(dep[v]==dep[u]-1&&val[i])
		{
			tmp=dfs(v,min(lim,1ll*val[i]));
			val[i]-=tmp,lim-=tmp;
			ans+=tmp,val[i^1]+=tmp;
			if(!lim)break;
		}
	}
	if((!ans)||lim)
	{
		if(--gap[dep[u]]==0)dep[s]=n+m+3;
		++gap[++dep[u]];
	}
	return ans;
}
inline ll isap()
{
	ll ans=0;
	bfs();
	while(dep[s]<=n+m+2)
	{
		memcpy(cur,fst,sizeof(cur));
		ans+=dfs(s,INF);
	}
	return ans;
}
int main()
{
	n=read(),m=read(),g=read(),s=0,t=n+m+1;
	for(int i=1;i<=n;++i)a[i]=read();
	for(int i=1;i<=n;++i)
	{
		int w=read();
		if(!a[i])add(s,i,w);
		else add(i,t,w);
	}
	for(int i=1;i<=m;++i)
	{
		int sign=read(),w=read(),k=read();
		ans+=w;
		for(int j=1;j<=k;++j)
		{
			int x=read();
			if(!sign)add(i+n,x,INF);
			else add(x,i+n,INF);
		}
		int opt=read();
		if(opt)w+=g;
		if(!sign)add(s,i+n,w);
		else add(i+n,t,w);
	}
	printf("%d",ans-isap());
	return 0;
}
```
只求能帮助到几个人罢。。

---

## 作者：Yuno (赞：1)

# 最大权闭合子图  
1.对于每个取值为0的位置，  
向S连一条容量为v[i]的边表示把这个点变为1的代价。  
2.取值为1的位置同理。  
3.对于每个要求，向它所要求的所有点连一条容量为+∞的边， 
以此保证这些要求只会被同时选或同时不选。  
4.对于每个要求集合为0的，向S连一条容量为w[i]的边。  
若失败了要额外付出价值，就把边的容量改成w[i]+g。  
转化为最大权闭合子图。  
$ans = \sum_{i = 1}^{m} w_i$  - 最小割。  
于是跑一遍Dinic即可。  
[宣传一波我的blog](https://www.luogu.org/blog/MYJ-blog-blog/solution-cf311e)  
Code：  
```
#include <bits/stdc++.h>
#define N 2000001
#define inf 0x3f3f3f3f
using namespace std;

int n, m, g, s, t, ans;
int tot = 1, to[N], val[N], nex[N], dep[N], head[N], cur[N];
int a[N];

inline int read(){
	int x = 0;
	int flag = 1;
	char ch = getchar();
	while (!isdigit(ch)){
		if (ch == '-') flag = -1;
		ch = getchar();
	}
	while (isdigit(ch)){
		x = (x << 3) + (x << 1) + ch - 48;
		ch = getchar();
	}
	return x * flag;
}


void add(int x, int y, int z) {
	tot++;
	to[tot] = y;
	val[tot] = z;
	nex[tot] = head[x];
	head[x] = tot;
	tot++;
	to[tot] = x;
	val[tot] = 0;
	nex[tot] = head[y];
	head[y] = tot;
}

inline bool bfs() {
	memset(dep, 0, sizeof(dep));
	dep[t] = 1;
	queue <int> q;
	q.push(t);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int i = head[u]; i; i = nex[i]) {
			int d = to[i];
			if (dep[d] == 0 && val[i ^ 1]) {
				dep[d] = dep[u] + 1;
				q.push(d);
			}
		}
	}
	return dep[s] > 0;
}

inline int dfs(int k, int flow) {
	int rlow = 0;
	if (k == t) return flow;
	for (int &tot = cur[k]; tot; tot = nex[tot]) {
		int d = to[tot];
		if (val[tot] && dep[d] + 1 == dep[k]) {
			int delta = dfs(d, min(flow, val[tot]));
			rlow += delta;
			flow -= delta;
			val[tot] -= delta;
			val[tot ^ 1] += delta;
			if (flow == 0) break;
		}
	}
	return rlow;
}

int Dinic() {
	int maxflow = 0;
	while (bfs()) {
		for (int i = s; i <= t; i++)
			cur[i] = head[i];
		maxflow += dfs(s, inf);
	}
	return maxflow;
}

int main() {
	n = read(), m = read(), g = read();
	s = 0, t = n + m + 1;
	for (int i = 1; i <= n; i++) {
		a[i] = read();
	}
	for (int i = 1; i <= n; i++) {
		int val = read();
		if (a[i] == 0) add(s, i, val);
		else add(i, t, val);
	}
	for (int i = 1; i <= m; i++) {
		int opt = read(), val = read(), k = read();
		if (opt == 0) {
			for (int j = 1; j <= k; j++) {
				int op = read();
				add(n + i, op, inf);
			}
			int op = read();
			if (op == 0) add(s, n + i, val);
			else add(s, n + i, val + g);
		}
		if (opt == 1) {
			for (int j = 1; j <= k; j++) {
				int op = read();
				add(op, n + i, inf);
			}
			int op = read();
			if (op == 0) add(n + i, t, val);
			else add(n + i, t, val + g);
		}
		ans += val;
	}
	printf("%d\n", ans - Dinic());
	return 0;
}
```


---

## 作者：do_while_true (赞：0)

我写的第一道最小割¿¿¿

二选一，考虑一个鱼刺型建图（自己编的名字），然后用最小割求最小花费。

鱼刺性建图大概就是，中间有一排点，然后位于左侧的 $S$ 连向这一排点，这一排点连向右侧的 $T$，看起来就很像鱼刺(?)

**trick：最大价值=总价值-最小花费**

如果这个位置是 $0$，那么源点 $S$ 连到它一条流量为 $v$ 的边，若存在则代表选 $0$，若割掉则代表花费了 $v$ 的代价选为 $1$；如果这个位置是 $1$，那么它连到汇点 $T$ 一条流量为 $v$ 的边，若存在则代表选 $1$，若割掉则代表花费了 $v$ 的代价选为 $0$．

首先这个 $g$ 是没有用的，就如果当二五仔要赔钱的话，把 $W$ 加上 $g$，然后最后总答案再减去 $g$ 即可。

现在这个限制是：如果这些位置你都选 $0/1$，就可以喜提 $W$ 的价值。对应到最小割上：先假定满足条件，获得 $W$ 的价值；如果这些位置的 $1/0$ 点与 $T/S$ 边有一条没被割掉，那么就需要付出 $W$ 的代价。

那么建一个新点 $x$，如果它限制的位置都选 $0$，就连 $(x,\text{限制的位置},+\infty)$，$(S,x,W)$，也就是 $x$ 在二分图中和 $0$ 点位于一部分。如果它限制的位置都选 $1$ 也同理，只不过它在二分图中和 $1$ 点位于一部分。

感性理解一下为什么这样子的最小割是最小花费：假设它限制若干位置都选 $0$，如果某些位置本来填的是 $1$，那么如果那个位置连向 $T$ 的边没有被割掉，不符合限制，$(S,x,W)$ 一定要被割掉，符合题意；如果某些位置本来填的是 $0$，如果这个位置 $p$ 对应的边被割掉了，在最小割中，那么从它开始一定至少可以到达一个没有被割掉的限制 $y$，这样流可以从 $S\to x\to p\to y\to T$ 流过，在这一路中，只有 $S\to x$ 的边是可以割的（若割掉所有的 $y\to T$，那么 $S\to p$ 一定不会割掉，因为割掉的话就不优了），所以 $(S,x,W)$ 一定要割掉，符合题意。

至于可能出现 $0$ 流量的边，其实是无关紧要的(?)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
#include<queue>
#define pb emplace_back
#define mp std::make_pair
#define fi first
#define se second
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
typedef std::pair<int, int> pii;
typedef std::vector<int> vi;
const ll mod = 998244353;
ll Add(ll x, ll y) { return (x+y>=mod) ? (x+y-mod) : (x+y); }
ll Mul(ll x, ll y) { return x * y % mod; }
ll Mod(ll x) { return x < 0 ? (x + mod) : (x >= mod ? (x-mod) : x); }
ll cadd(ll &x, ll y) { return x = (x+y>=mod) ? (x+y-mod) : (x+y); }
ll cmul(ll &x, ll y) { return x = x * y % mod; }
template <typename T> T Max(T x, T y) { return x > y ? x : y; }
template<typename T, typename... T2> T Max(T x, T2 ...y) { return Max(x, y...); }
template <typename T> T Min(T x, T y) { return x < y ? x : y; }
template<typename T, typename... T2> T Min(T x, T2 ...y) { return Min(x, y...); }
template <typename T> T cmax(T &x, T y) { return x = x > y ? x : y; }
template <typename T> T cmin(T &x, T y) { return x = x < y ? x : y; }
template <typename T>
T &read(T &r) {
	r = 0; bool w = 0; char ch = getchar();
	while(ch < '0' || ch > '9') w = ch == '-' ? 1 : 0, ch = getchar();
	while(ch >= '0' && ch <= '9') r = r * 10 + (ch ^ 48), ch = getchar();
	return r = w ? -r : r;
}
template<typename T1, typename... T2>
void read(T1 &x, T2& ...y) { read(x); read(y...); }
const int N = 100010;
const int M = 500010;
const ll INF = 0x7fffffffffffffff;
int n, m, g;
int a[N], v[N];
int tot, S, T, ent = 1, head[N], cur[N], dis[N];
struct Edge {
	int to, nxt;
	ll fl;
}e[M << 1];
inline void add(int x, int y, ll z) {
	//printf("%d %d %d\n", x, y, z);
	e[++ent].to = y; e[ent].fl = z; e[ent].nxt = head[x]; head[x] = ent;
	e[++ent].to = x; e[ent].fl = 0; e[ent].nxt = head[y]; head[y] = ent;
}
bool bfs() {
	for(int i = 1; i <= tot; ++i) dis[i] = -1, cur[i] = head[i];
	std::queue<int>q;
	q.push(S); dis[S] = 0;
	while(!q.empty()) {
		int x = q.front(); q.pop();
		for(int i = head[x]; i; i = e[i].nxt) {
			int v = e[i].to;
			if(dis[v] == -1 && e[i].fl) {
				dis[v] = dis[x] + 1;
				q.push(v);
			}
		}
	}
	return dis[T] != -1;
}
ll dfs(int x, ll lim) {
	if(x == T) return lim;
	ll flow = 0;
	for(int i = cur[x]; i && flow < lim; i = e[i].nxt) {
		int v = e[i].to; cur[x] = i;
		if(dis[v] == dis[x] + 1 && e[i].fl) {
			ll f = dfs(v, Min(e[i].fl, lim - flow));
			flow += f; e[i].fl -= f; e[i^1].fl += f;
		}
	}
	return flow;
}
ll dinic() {
	ll mxfl = 0;
	while(bfs())
		mxfl += dfs(S, INF);
	return mxfl;
}
signed main() { //freopen("data.in", "r", stdin);
	ll sum = 0;
	read(n, m, g); tot = n; S = ++tot; T = ++tot;
	for(int i = 1; i <= n; ++i) read(a[i]);
	for(int i = 1; i <= n; ++i) read(v[i]);
	for(int i = 1; i <= n; ++i) {
		if(!a[i]) add(S, i, v[i]);
		else add(i, T, v[i]);
	}
	for(int i = 1; i <= m; ++i) {
		int p = ++tot, to, W, k, f; read(to, W, k); vi vec;
		for(int j = 1, x; j <= k; ++j) {
			read(x);
			if(!to) add(p, x, INF);
			else add(x, p, INF);
		}
		read(f);
		if(f) W += g, sum -= g;
		sum += W;
		if(!to) add(S, p, W);
		else add(p, T, W);
	}
	printf("%lld\n", sum - dinic());
	return 0;
}
```

---

## 作者：Thunder_S (赞：0)

## Solution

答案=所有赞助费-变性费用-没拿到的赞助费-请喝茶的费用。

所有的赞助费是已知的，要最大化答案，就是要最小化后面那部分。

因此可以想到最小割，建源点 $S$ 表示雄性，$T$ 表示雌性。

然后 $S$ 向所有雄性牛连边，流量是 $v_i$。雌性牛向 $T$ 连边，代价同理。

然后考虑将朋友也放到图中。

如果朋友要求雄性，就 $S\to n+i\to $ 牛。代价分别是 $w_i(+g)$ 和 $inf$（因为要保证这条边绝对不被割掉）。反之亦然。

那么此时割牛边相当于变性，给人边相当于不要某人的赞助费。

然后就可以愉快的跑最大流了。

## Code

```cpp
#include<queue>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 10005
#define inf 107374180
using namespace std;
struct node
{
    int to,next,head,flow;
}a[200005];
queue<int> q;
int n,m,g,S,T,tot=1,xxb,gg,k,x,isf,ans,xb[N],v[N],cur[N<<1],dep[N<<1];
int read()
{
    int res=0;char ch=getchar();
    while (ch<'0'||ch>'9') ch=getchar();
    while (ch>='0'&&ch<='9') res=(res<<1)+(res<<3)+(ch-'0'),ch=getchar();
    return res;
}
void add(int x,int y,int z)
{
    a[++tot].to=y;
    a[tot].flow=z;
    a[tot].next=a[x].head;
    a[x].head=tot;
}
bool bfs()
{
    for (int i=1;i<=n+m+2;++i)
        dep[i]=0;
    while (!q.empty()) q.pop();
    dep[S]=1;q.push(S);
    while (!q.empty())
    {
        int x=q.front();q.pop();
        for (int i=a[x].head;i;i=a[i].next)
        {
            if (a[i].flow>0&&dep[a[i].to]==0)
            {
                dep[a[i].to]=dep[x]+1;
                q.push(a[i].to);
                if (a[i].to==T) return true;
            }
        }
    }
    return false;
}
int dfs(int x,int ff)
{
    if (x==T) return ff;
    int fw=0;
    for (int &i=cur[x];i;i=a[i].next)
    {
        if (a[i].flow>0&&dep[a[i].to]==dep[x]+1)
        {
            int f=dfs(a[i].to,min(a[i].flow,ff));
            a[i].flow-=f;
            a[i^1].flow+=f;
            fw+=f;
            ff-=f;
            if (ff<=0) break;
        }
    }
    return fw;
}
int dinic()
{
    int res=0;
    while (bfs())
    {
        for (int i=1;i<=n+m+2;++i)
            cur[i]=a[i].head;
        res+=dfs(S,inf);
    }
    return res;
}
int main()
{
    n=read();m=read();g=read();
    S=n+m+1;T=n+m+2;
    for (int i=1;i<=n;++i)
        xb[i]=read();
    for (int i=1;i<=n;++i)
        v[i]=read();
    for (int i=1;i<=n;++i)
    {
        if (xb[i]==1) add(S,i,v[i]),add(i,S,0);
        else add(i,T,v[i]),add(T,i,0);
    }
    for (int i=1;i<=m;++i)
    {
        xxb=read();gg=read();
        ans+=gg;
        k=read();
        for (int j=1;j<=k;++j)
        {
            x=read();
            if (xxb==1) add(n+i,x,inf),add(x,n+i,0);
            else add(x,n+i,inf),add(n+i,x,0);
        }
        isf=read();
        if (isf==1) gg+=g;
        if (xxb==1) add(S,n+i,gg),add(n+i,S,0);
        else add(n+i,T,gg),add(T,n+i,0);
    }
    printf("%d\n",ans-dinic());
    return 0;
}
```



---

## 作者：When (赞：0)

挺绕的一道题。

### 算法
最大权闭合子图（网络流）

### 思路

对于这类 $0/1$ 翻转的问题，我们不妨假设所有的位置都变成了 $1$，这时候的利润为要求为 $1$ 的利润之和 $-$ 将 $0$ 变成 $1$ 的花费之和 $-$ 需要倒贴的要求为 $0$ 的代价之和。

考虑如果要满足一个要求为 $0$ 的询问，我们要将与其相关的位置全部变为 $0$，并且所有与这些位置相关的要求为 $1$ 的询问都无法满足。如果将询问与位置的相互限制抽象成边，可以发现这是一个最大权比合子图模型。

若一个 $0$ 的要求被满足，那么可以获得 $w_i+g$ （如果有的话）的利润，若一个 $1$ 的要求不能满足了，那么会承受 $w_i+g$（如果有的话）的损失，不妨将前者视为正权点，将后者视为负权点。对于一个原本为 $0$ 的位置，将其重新变为 $0$ 相当于反悔了，可以获得 $v+i$ 的利润，对于一个原本为 $1$ 的点，将其置为 $0$ 则需要花费 $v_i$ 的代价，同样，前者为正权点，后者为负权点。

至此，我们已经知道了原图的建法，然后按照最大权闭合子图的套路求出来就行了。事实上，答案就是 $\sum w-Maxflow$。

### 参考代码
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#define LL long long

using namespace std;

inline LL read(){
    LL x = 0, f = 1; char c = getchar();
    while(c < '0' || c > '9'){if(c == '-') f = -1; c = getchar();}
    while(c >= '0' && c <= '9'){x = x * 10 + c - '0'; c = getchar();}
    return x * f;
}

const int maxn = 1e5 + 10, inf = 0x3f3f3f3f;
int n,m,a[maxn],g;
int head[maxn],num = 1,s,t;
LL Ans;
struct Edge{int then,to,val;}e[maxn << 1];

void add(int u, int v, int val){
    e[++num] = (Edge){head[u], v, val}; head[u] = num;
    e[++num] = (Edge){head[v], u, 0}; head[v] = num;
}

int dep[maxn]; bool vis[maxn];
bool bfs(int st, int en){
    queue<int> q;
    memset(vis, 0, sizeof(vis));
    memset(dep, 0x3f, sizeof(dep));
    q.push(st), dep[st] = 0, vis[st] = 1;
    while(!q.empty()){
        int u = q.front(); q.pop();
        vis[u] = 0;
        for(int i = head[u]; i; i = e[i].then){
            int v = e[i].to;
            if(e[i].val > 0 && dep[v] == inf){
                dep[v] = dep[u] + 1;
                if(!vis[v]) vis[v] = 1, q.push(v);
            }
        }
    }
    return (dep[en] != inf);
}

int cur[maxn];
int dfs(int u, int sum){
    if(u == t) return sum;
    int now = 0;
    for(int &i = cur[u]; i; i = e[i].then){
        int v = e[i].to;
        if(e[i].val > 0 && dep[v] == dep[u] + 1){
            int a = dfs(v, min(sum - now, e[i].val));
            e[i].val -= a, e[i ^ 1].val += a, now += a;
            if(now == sum) return now;
        }
    }
    return now;
}

int Dinic(){
    int Maxflow = 0;
    while(bfs(s, t)){
        memcpy(cur, head, sizeof(head));
        Maxflow += dfs(s, inf);
    }
    return Maxflow;
}

int main(){

    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    
    n = read(), m = read(), g = read();
    s = n + m + 1, t = n + m + 2;
    for(int i = 1; i <= n; ++ i) a[i] = read();
    for(int i = 1; i <= n; ++ i){
        int val = read();
        if(a[i]) add(i, t, val);
        else add(s, i, val);
    }
    for(int i = 1; i <= m; ++ i){
        int op = read(), w = read(), k = read();
        int now = i + n; Ans += w;
        while(k--){
            int pos = read();
            if(op) add(pos, now, inf);
            else add(now, pos, inf);
        }
        int fg = read(); if(fg) w += g;
        if(op) add(now, t, w);
        else add(s, now, w);
    }
    Ans -= Dinic();
    printf("%lld\n", Ans);
    return 0;
}
```

---

