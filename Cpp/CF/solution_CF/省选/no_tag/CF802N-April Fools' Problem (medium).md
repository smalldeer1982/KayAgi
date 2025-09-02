# April Fools' Problem (medium)

## 题目描述

The marmots need to prepare $ k $ problems for HC $ ^{2} $ over $ n $ days. Each problem, once prepared, also has to be printed.

The preparation of a problem on day $ i $ (at most one per day) costs $ a_{i} $ CHF, and the printing of a problem on day $ i $ (also at most one per day) costs $ b_{i} $ CHF. Of course, a problem cannot be printed before it has been prepared (but doing both on the same day is fine).

What is the minimum cost of preparation and printing?

## 说明/提示

In the sample testcase, one optimum solution is to prepare the first problem on day $ 1 $ and print it on day $ 1 $ , prepare the second problem on day $ 2 $ and print it on day $ 4 $ , prepare the third problem on day $ 3 $ and print it on day $ 5 $ , and prepare the fourth problem on day $ 6 $ and print it on day $ 8 $ .

## 样例 #1

### 输入

```
8 4
3 8 7 9 9 4 6 8
2 5 9 4 3 8 9 1
```

### 输出

```
32```

# 题解

## 作者：dead_X (赞：12)

## 前言
Q:为什么这是网络流？          
A:因为标签里有flow。
## 忠告
~~不开longlong见祖宗~~         
~~开了longlongINF不够大见祖宗~~                       
~~开了longlongINF够大%d输出见祖宗~~           
开了longlongINF够大%lld输出大于int的值不打``1145141919810ll``见祖宗
## 思路
易知这是网络流题。

我们先把样例画出来。
![](https://cdn.luogu.com.cn/upload/image_hosting/1jjlqv9x.png)

发现了什么？这个东西很像二分图。但是和二分图又不一样，这玩意只需要连 $k$ 条边即可。这玩意当然不能用匈牙利这种东西去求，然而网络流还是可以搞定的。我们只需要把**源点**往**上方点**连边，**下方点**往**伪汇点**连边，**伪汇点**往**真汇点**连一条流量为 $k$ 的边跑**费用流**即可。

我们发现上方点只能往右下角的下方点连边，于是这玩意就能跑了。

时间复杂度是多少呢？$O(nmf)=O(n^4)$，显然过不了 $2\times 10^3$。

那么怎么优化呢？我们考虑是否有些边是没有意义的。

显然这题的优化思路并不困难。我们只要拆分动作即可。例如从 $i_2$ 到 $j_4$ 的这条边，我们可以想象它先从 $i_2$ 到了 $p_2$，$p_2$ 到了 $p_3$，$p_3$ 再到了 $p_4$，最后从 $p_4$ 到了 $j_4$。由于中转点 $p$ 中只会从小往大流，我们只要把中转点 $i$ 向 $i+1$ 连一条流量为 $\inf$ 的边即可。

于是上面的图就变成了这样。

![](https://cdn.luogu.com.cn/upload/image_hosting/0misxza2.png)

这样做的时间复杂度是多少呢？$O(nmf)=O(n^3)$，虽然看着过不了，可是由于网络流的复杂度都卡不满，这玩意就过去了（
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
int read(){
    int x=0,f=1;char ch=getchar();
    while(ch<'0' || ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while('0'<=ch && ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
    return x*f;
}
using namespace std;
deque<int> Q;
int ans=0,res=0,n,S,T,cnt=0;
int d[5003],a[5003];
bool inq[5003],vis[5003];
struct Edge{
    int to,cap,cost,next;
}e[100003];
void addedge(int u,int v,int w,int c)
{
    e[cnt].to=v;e[cnt].cap=w;e[cnt].cost=c;e[cnt].next=a[u],a[u]=cnt++;
}
bool bfs(){
    for(int i=0;i<=n;i++) d[i]=1000000000000000ll;
    memset(inq,0,sizeof(inq));
    d[T]=0,Q.push_back(T),inq[T]=true;
    while(!Q.empty()){
        int u=Q.front();
		Q.pop_front(),inq[u]=false;
        for(int p=a[u]; p!=-1; p=e[p].next)
		{
            int v=e[p].to;
            if(e[p^1].cap && d[v]>d[u]-e[p].cost)
			{
                d[v]=d[u]-e[p].cost;
                if(!inq[v])
				{
                    inq[v]=true;
                    if(Q.empty() || d[v]>=d[Q.front()]) Q.push_back(v); else Q.push_front(v);
                    //Happy 卡常 Time! 
                }
            }
        }
    }
    return d[S]<d[0];
}
int dfs(int u,int f)
{
    vis[u]=true;
    if(u==T || f==0)return f;
    int used=0;
    for(int p=a[u]; p!=-1; p=e[p].next)
	{
        int v=e[p].to;
        if((!vis[v]) && e[p].cap && d[v]==d[u]-e[p].cost){
            int w=f-used;
            w=dfs(v,min(e[p].cap,w));
            e[p].cap-=w,e[p^1].cap+=w,used+=w;
            if(used==f) return used;
        }
    }
    return used;
}
int A[5003],B[5003],K,TT;
signed main(){
    n=read(),K=read(),S=n+1,TT=n+2,T=n+3;
	for(int i=1; i<=n; i++) A[i]=read();
	for(int i=1; i<=n; i++) B[i]=read();
    memset(a,0xff,sizeof(a));
    for(int i=1; i<=n; i++)
	{
        addedge(S,i,1,A[i]),addedge(i,S,0,-A[i]);
        addedge(i,TT,1,B[i]),addedge(TT,i,0,-B[i]);
    	if(i!=n) addedge(i,i+1,1000000,0),addedge(i+1,i,0,0);
	}
	addedge(TT,T,K,0),addedge(T,TT,0,0);
	n=n+3;
    while(bfs())
	{
        vis[T]=1;
        while(vis[T])
		{
            memset(vis,0,sizeof(vis));
            int flow=dfs(S,1000000000000000ll);
            res+=d[S]*flow;
            ans+=flow;
        }
    }
    printf("%lld",res);
    return 0;
}
```

---

## 作者：RioBlu (赞：7)

* 本题合理运用 **wqs 二分** 和 **反悔贪心** 就可以过了

如果对上述算法不算了解：

* [反悔贪心](https://www.luogu.com.cn/blog/luo1gu1zui1bang1/post-tan-xin-fan-hui-tan-xin) $\text{by Welikestudying }$

* [wqs 二分](https://www.luogu.com.cn/blog/daniu/wqs-er-fen) $\text{by Leap Frog}$

更通俗的题意：

$n$ 道题, 第 $i$ 天可以花费 $a_i$ 准备一道题, 花费 $b_i$ 打印一道题, 每天最多准备一道, 最多打印一道, 准备的题可以留到以后打印, 求最少花费使得准备并打印 $k$ 道题。

### 凸性证明

可以发现，越小的选择一定会放在前面，而后面多选择的一定是相比以前的选择更劣的，所以这是一个下凸包。

此证明可以把本问题转化成 wqs 二分题，我们也就去掉了 $k$ 的限制。

### 反悔贪心

贪心找到的是局部最优解，而且并不回退，而反悔贪心不一样，我们贪心的过程中，当我们发现当前的选择比之前更加优秀时，进行“反悔”。

比如本题，经过转换现在已经没有 $k$ 的限制了。

如何反悔贪心呢？

1. 对于一个 $a_i-mid$ ， $mid$ 是 wqs 二分得到的数字，我们先放入一个优先队列$q$（小的优先级大）中

2. 如果当前的 $b_i + q_{top} < 0$ 我们就把 $b_i + q_{top}$ 加入答案，把 $q_{top}$ 删除,并且把$b_i$放入另一个优先队列 $p$ （大的优先级大）中

3. 如果 $b_i + q_{top} \geq 0$ 同时我们发现 $b_i<p_{top}$ 说明我们之前的选择比较劣，我们要反悔！于是我们的答案减去 $p_{top}$ 同时加上 $b_i$ ，再把 $p_{top}$ 弹出，加入 $b_i$

但是这样会有**问题**，因为我们有些时候发现有些时候，虽然 $b_i + q_{top} < 0$ 但是呢，进行操作 $3$ 会更加优秀，所以我们还需要比较这个 $b_i$ 放在哪里会更加优秀

所以操作 $2,3$ 的条件改成：

$3.$ $b_i<p_{top}$ 且有下者之一： $-p_{top}+b_i<q_{top}+b_i $，或者 $b_i + q_{top} \geq 0$ ，执行本操作

$2.$如果上面的 $3$ 的条件不满足，执行本操作

### code

```cpp
ll n,k,a[500005],b[500005];
ll l,r,mid;
priority_queue<ll,vector<ll>,greater<ll> >q;
priority_queue<ll,vector<ll>,less<ll> >p;
ll cnt,sum;
ll check()
{
	sum=cnt=0;
	while(q.size())q.pop();
	while(p.size())p.pop();
	for(int s=1;s<=n;s++)
	{
		q.push(a[s]-mid);
		if(p.size()&&(-p.top()+b[s]<0&&-p.top()+b[s]<q.top()+b[s]||q.top()+b[s]>0&&p.top()>b[s]))
		{
			sum=sum-p.top()+b[s];
			p.pop();
			p.push(b[s]);
		}
		else
		{
			if(q.top()+b[s]<0)
			{
				cnt++;
				sum=sum+q.top()+b[s];
				q.pop();p.push(b[s]);
			}
		}
	}
	return cnt;
}
int main()
{
	in(n),in(k);
	for(int s=1;s<=n;s++)in(a[s]);
	for(int s=1;s<=n;s++)in(b[s]);
	l=-1e10,r=1e10;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(check()<=k)l=mid+1;
		else r=mid-1;
	}
	mid=l-1;check();
	cout<<sum+k*mid<<endl;
	return 0;
}
```

---

## 作者：David_H_ (赞：5)

## 题意简述

给定两个序列，$\{a_i\}$ 和 $\{b_i\}$。要求选出 $\{i_k\}$ 和 $\{j_k\}$，满足：

- $i_l\le i_m(1\le l\le m\le k)$，$j_l\le j_m(1\le l\le m\le k)$；
- $i_p\le j_p(1\le p\le k)$；

求 $\min\left(\displaystyle\sum_{p=1}^k (a_{i_p}+b_{j_p})\right)$。

## 思路简述

我们先看一眼数据范围——$n\le 2200$，这暗示我们时间复杂度应该会**劣于**$O(n^2)$。

我们考虑一个图，满足：

- 有 $n+2$ 个节点，其中第 $i$ 天 $1$ 个节点，编号为 $i$（$i=1,2,3,\cdots,n$），有一个起点（源）$s$，一个终点（宿）$t$。
- 对于每一天（记当天为第 $i$ 天，$i=1,2,3,\cdots,n$），加 $3$ 条边：
  - 从 $s$ 到 $i$，流量为 $1$，费用为 $a_i$。
  - 从 $i$ 到 $i+1$，第 $n$ 天无此边，流量为 $k$，费用为 $0$。
  - 从 $i$ 到 $t$，流量为 $1$，费用为 $b_i$。

不难看出，在该图中，当流量为 $k$ 时，最小费用刚好为我们所求的 $\min\left(\displaystyle\sum_{p=1}^k (a_{i_p}+b_{j_p})\right)$。随便分析一下时间复杂度，为 $O(nm)$，足以通过此题。

核心代码如下（用到了 AtCoder 的模板库）：

````cpp
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    cin >> n >> k;
    mcf_graph<ll, ll> graph(n + 2);
    for (int i = 1; i <= n; i++) {
        int temp;
        cin >> temp;
        graph.add_edge(0, i, 1, temp);
        if (i < n) graph.add_edge(i, i + 1, k, 0);
    }
    for (int i = 1; i <= n; i++) {
        int temp;
        cin >> temp;
        graph.add_edge(i, n + 1, 1, temp);
    }
    pair<long long, long long> ans = graph.flow(0, n + 1, k);
    cout << ans.second << endl;
    return 0;
}
````



---

## 作者：xfrvq (赞：1)

[$\tt CF802N$](/problem/CF802N)。

网络流，网络流，网络流。

首先比较显然的一个想法是流量用 $0,1$ 来代表每个点的选不选，然后

1. 源点连向每个 $i$，容量 $1$ 费用 $a_i$。
2. 每个 $i$ 连向汇点，容量 $1$ 费用 $b_i$。
3. 每对 $i\le j$ 都直接连边
4. 但是这样无法保证总流量是 $k$，所以在之前的那个汇点连容量 $k$ 的边向真正汇点，保证流量 $k$

但是这样边太多了（第 3 类边）网络流复杂度挂了，那我们尝试改进。

我们直接连 $i\to i+1$，$+\infty$ 流量 $0$ 费用（代替 3 类边）。这一步可以使得 $i$ 以前的 1 类边正常流到 $i+1$，2 类边可以正常离开。

那就做完了。

---

## 作者：sqrtqwq (赞：0)

[problem](https://www.luogu.com.cn/problem/CF802N) & [双倍经验](https://www.luogu.com.cn/problem/P4694) & [三倍经验](https://www.luogu.com.cn/problem/CF802O)

------

这是一个取 $k$ 个物品的问题，然后我们发现它是一个凸函数，所以可以联想到 wqs 二分。

不会 wqs 二分的可以看 [这个](https://www.luogu.com/article/knpufhxe) 文章。

我们来考虑 check 怎么写。

每次我们往堆中加入 $a_i$，然后再考虑怎么配对 $b_i$。

那么有如下两种情况：

1. 和之前最小的 $a_x$ 配对，代价为 $a_x + b_i$。

2. 拆散原本的一对配对，然后再组合，那么代价就是 $(a_x + b_i) - (a_x - b_y) = -b_y + b_i$。

然后拿一个小根堆维护匹配的情况即可。有没有匹配的 $a_i$ 都要 push 进去。

---

## 作者：ty_mxzhn (赞：0)

## 题意

$n$ 道题，第 $i$ 天可以花费 $a_i$ 准备一道题，花费 $b_i$ 打印一道题，每天最多准备一道，最多打印一道，准备的题可以留到以后打印，求最少花费使得准备并打印 $k$ 道题。$1\le k\le n\le 5\times 10^5$。

## 题解

贪心太厉害！

$k$ 道题的限制不用管，因为这个答案函数显然是下凸的，直接 wqs 二分即可。

我们每天打印的时候，显然是可以选一道自己喜欢的题打印下来，一个贪心的想法是每次打一道准备花费最小的还没有打的，并且这次打完不会对代价产生正贡献的打下来。

显然是错误的，考虑反悔。之前打印完了的匹配，我们可以让之前那个不打印，然后让这个新的换上去。当然的，我们也需要这次代价不存在正贡献。

可以用堆来维护反悔贪心。

---

## 作者：happybob (赞：0)

比较简单的费用流。

考虑这样一个建模：$S$ 连向每个 $a_i$，容量为 $1$，费用为 $0$，每个 $a_i$ 连向所有 $b_j(j \geq i)$，容量为 $1$，费用为 $a_i$。现在我们要考虑怎么使得恰好选 $k$ 个。显然可以每个 $b_i$ 连向一个虚点 $P$，容量为 $1$，费用为 $b_i$。然后 $P \rightarrow T$，容量为 $k$，费用为 $0$。跑最小费用最大流即可。

然而此时要连 $O(n^2)$ 条边，跑费用流复杂度会达到 $O(n^4)$，复杂度瓶颈在于边数。注意到每个 $i$ 会连向 $j \geq i$，直接后缀优化建图即可。$b_i \rightarrow b_{i+1}$，容量为 $+\infty$，费用为 $0$ 即可做到 $O(n^3)$ 的复杂度。

理论上应该过不了，实际上这是网络流，所以能过。

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int N = 1e5 + 5;
int n, k, a[N], b[N];

class MCMF
{
public:
	int S, T;
	int e[N], h[N], c[N], sc[N], ne[N], idx;
	int sum;
	void Init()
	{
		memset(h, -1, sizeof h);
	}
	void add(int u, int v, int w, int cs)
	{
		e[idx] = v, c[idx] = w, sc[idx] = cs, ne[idx] = h[u], h[u] = idx++;
		e[idx] = u, c[idx] = 0, sc[idx] = -cs, ne[idx] = h[v], h[v] = idx++;
	}
	int dis[N], cur[N];
	bool isin[N];
	bool spfa()
	{
		for (int i = 0; i <= T; i++)
		{
			dis[i] = (int)4e18;
			cur[i] = -1;
		}
		queue<int> q;
		q.push(S);
		dis[S] = 0;
		cur[S] = h[S];
		while (q.size())
		{
			int u = q.front();
			q.pop();
			isin[u] = 0;
			for (int i = h[u]; ~i; i = ne[i])
			{
				int j = e[i];
				if (c[i] > 0 && dis[j] > dis[u] + sc[i])
				{
					dis[j] = dis[u] + sc[i];
					cur[j] = h[j];
					if (!isin[j])
					{
						isin[j] = 1;
						q.push(j);
					}
				}
			}
		}
		return (dis[T] != (int)4e18);
	}
	int dfs(int u, int lim)
	{
		if (u == T) return lim;
		isin[u] = 1;
		int ans = 0;
		for (int i = cur[u]; ~i && ans < lim; i = ne[i])
		{
			int j = e[i];
			cur[u] = i;
			if (c[i] > 0 && dis[j] == dis[u] + sc[i] && !isin[j])
			{
				int p = dfs(j, min(c[i], lim - ans));
				ans += p;
				c[i] -= p;
				c[i ^ 1] += p;
				sum += p * sc[i];
			}
		}
		isin[u] = 0;
		return ans;
	}
	int dinic()
	{
		int ans = 0;
		while (spfa())
		{
			int u;
			while (u = dfs(S, (int)4e18)) ans += u;
		}
		return ans;
	}
}f;

signed main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	f.Init();
	cin >> n >> k;
	f.S = 0, f.T = 2 * n + 2;
	for (int i = 1; i <= n; i++)
	{
		cin >> a[i];
		f.add(f.S, i, 1, 0);
		f.add(i, i + n, 1, a[i]);
	}
	for (int i = 1; i < n; i++) f.add(i + n, i + n + 1, (int)4e18, 0);
	for (int i = 1; i <= n; i++) cin >> b[i], f.add(i + n, 2 * n + 1, 1, b[i]);
	f.add(2 * n + 1, f.T, k, 0);
	f.dinic();
	cout << f.sum << "\n";
	return 0;
}
```


---

## 作者：Iniaugoty (赞：0)

我是在反悔贪心题单里找到它的，但是貌似费用流更好理解一些。而且这个范围也是放费用流过的。

考虑很平凡的套路，以 $A$ 序列的下标为左部点，$B$ 序列的下标为右部点，建立两个超级源点和一个超级汇点，然后跑最小费用最大流。

第一个超级源点向第二个超级源点连边，容量 $k$，费用 $0$，表示 $A$ 中要选 $k$ 个数；第二个超级源点向左部 $i (1\le i \le n)$ 连边，容量 $1$，费用 $a _ i$，表示 $A$ 中每个下标 $i$ 最多选一次，如果选了代价要增加 $a _ i$；左部 $i (1 \le i \le n)$ 向右部 $j (i \le j \le n)$，容量 $1$，费用 $0$，表示对于每个已经选了的 $A$ 中的下标，$B$ 中还要再选一个不小于它的下标；右部 $j (1 \le j \le n)$ 向超级汇点连边，容量 $1$，费用 $b _ i$，表示 $B$ 中每个下标 $j$ 最多选一次，如果选了代价要增加 $b _ j$。

但是会 T，毕竟这个东西也是暴力。

这样建出来的图中，点数是 $\mathcal O(n)$ 量级的，显然不能再少了，但是边数是 $\mathcal O(n ^ 2)$，可以在这上面搞一搞。超级源汇及其连边保持不变，试着把某个下标对应的左部点和右部点合起来，$i$ 向 $i + 1$ 连一条边，容量 $n$，费用 $0$。这样一来，选完某个 $A$ 中的下标之后，都可以顺着这一串边去选某个 $B$ 中不小于它的下标，由于超级源汇的连边不变，并不会选重啥的。边数降低到 $\mathcal O(n)$，复杂度直接少一个 $n$，加上网络流自带极小常数直接莽过去。

```cpp
#include <bits/stdc++.h>

#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
const int N = 2205;
const int M = 1.5e4;
const int inf = 1e9;
const LL Inf = 1e18;

int n, k, s, s0, t, flow; LL cost;
int tot = 1, head[N];
struct edge { int nxt, v, w, c; } e[M];
void Addedge(int u, int v, int w, int c) {
	e[++tot] = {head[u], v, w, c};
	head[u] = tot;
}

LL dis[N];
int now[N];
bool vis[N];
bool Spfa() {
	F(i, 1, n + 3) dis[i] = Inf;
	dis[s] = 0;
	queue<int> q;
	q.push(s);
	while (!q.empty()) {
		int u = q.front();
		q.pop(), vis[u] = 0;
		now[u] = head[u];
		for (int i = head[u]; i; i = e[i].nxt) {
			int v = e[i].v, w = e[i].w, c = e[i].c;
			if (w > 0 && dis[u] + c < dis[v]) {
				dis[v] = dis[u] + c;
				if (!vis[v]) q.push(v), vis[v] = 1;
			}
		}
	}
	return dis[t] != Inf;
}
int Dfs(int u, int sum) {
	if (u == t) return sum;
	int res = 0, r;
	vis[u] = 1;
	for (int i = now[u]; i && sum; i = e[i].nxt) {
		now[u] = i;
		int v = e[i].v, c = e[i].c;
		if (!vis[v] && e[i].w > 0 && dis[u] + c == dis[v])
			r = Dfs(v, min(sum, e[i].w)),
			e[i].w -= r, e[i ^ 1].w += r,
			res += r, sum -= r,
			cost += (LL) c * r;
	}
	vis[u] = 0;
	return res;
}
void Dinic() {
	flow = cost = 0;
	while (Spfa())
		flow += Dfs(s, inf);
	return ;
}

int main() {
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> k;
	s = n + 1, s0 = s + 1, t = s0 + 1;
	Addedge(s, s0, k, 0);
	Addedge(s0, s, 0, 0);
	F(i, 1, n) {
		int a; cin >> a;
		Addedge(s0, i, 1, a);
		Addedge(i, s0, 0, -a);
	}
	F(i, 1, n) {
		int b; cin >> b;
		Addedge(i, t, 1, b);
		Addedge(t, i, 0, -b);
	}
	F(i, 1, n - 1)
		Addedge(i, i + 1, n, 0),
		Addedge(i + 1, i, 0, 0);
	Dinic();
	cout << cost << "\n";
	return 0;
}
```

---

## 作者：Pwtking (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF802N)

首先尝试贪心，但是发现贪心会假，再尝试 dp，但发现 dp 有后效性，于是尝试万能算法网络流。

首先有一种很显然的连边方式：

将 $a_i$ 和 $b_i$ 分开排列，将源点连向所有 $a_i$，容量 $1$ 代表每个 $a_i$ 只能选一次，费用 $a_i$，将每个 $a_i$ 连向每一个 $b_j,j\ge i$，容量 $1$，费用 $0$。再将每个 $b_j$ 连向汇点。

但是显然这样不能满足只选 $k$ 个数，所以我们将汇点拆点为 $t_0$ 和 $t$，将所有的 $b_j$ 连向 $t_0$，再将 $t_0$ 连向 $t$，费用 $0$ 容量 $k$ 以满足选数的个数限制。

但是此时复杂度又超了！

仔细观察发现其实我们将 $a_i$ 连向每个 $b_j$ 的实质是让源点向 $a_i$ 连的边与 $b_j$ 连的边连通以达到选每个数的目的，但其实完全没必要，我们可以把所有的 $a$ 和 $b$ 缩成一个点 $i$。将源点向每个 $i$ 连边，费用 $a_i$ 容量 $1$，将每个 $i$ 向 $t_0$ 连费用 $b_i$ 容量 $1$ 的边，最后将每一个 $i\in[1,n)$ 向 $i+1$ 连费用 $0$ 容量 $1$ 的边代表我可以选所有比当前 $i$ 更大的 $i+x$。 



---

## 作者：dengjunhaodejia09 (赞：0)

发现恰好选 $k$ 次，所以考虑 wqs 二分，发现具有凸性，因为一开始会先选最优的，再选次优的再一直选下去。

考虑如何在 wqs 二分后求最小答案，因为不选的代价为 0 ，所以选择的代价必须小于等于 0 才能选，这是为了比少选一个更优，此处要选的尽量多，因为 wqs 二分有可能会共线，这样才好处理。此时就可以反悔贪心了。

遍历每一位，每次将 $a_{i}-mid$ 加入堆，若是堆顶加当前的 $b_{i}$ 小于 0 ，就可以选，选了就要塞 $-b_{i}$ 进入堆。那么若是选了 $-b_{k}$ ，就是在那个操作中把原来的 $b_{k}$ 替换为 $b_{i}$。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[500005],b[500005];
int n,m,vis=0;;
priority_queue<pair<int,int> ,vector<pair<int,int> > ,greater<pair<int,int> > > q;
int check(int mid){
    while(q.size()){
        q.pop();
    }
    int num=0,ans=0;
    for(int i=1;i<=n;i++){
        q.push(make_pair(a[i]-mid,-1));
        if(b[i]+q.top().first<=0){//考虑还有一个都不选
            num-=q.top().second;
            ans+=q.top().first+b[i];
            q.push(make_pair(-b[i],0));
            q.pop();
        }
    }
    if(vis){
        return ans;
    }
    return num>=m;
}
signed main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>a[i];
    }
    for(int i=1;i<=n;i++){
        cin>>b[i];
    }
    int l=0,r=2e9,ans=0;
    while(l<=r){
        int mid=(l+r)/2;
        if(check(mid)){
            r=mid-1;
            ans=mid;
        }else{
            l=mid+1;
        }
    }
    vis=1;
    cout<<check(ans)+ans*m;
    return 0;
}
```

---

