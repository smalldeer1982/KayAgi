# Bridge Club

## 题目描述

There are currently $ n $ hot topics numbered from $ 0 $ to $ n-1 $ at your local bridge club and $ 2^n $ players numbered from $ 0 $ to $ 2^n-1 $ . Each player holds a different set of views on those $ n $ topics, more specifically, the $ i $ -th player holds a positive view on the $ j $ -th topic if $ i\ \&\ 2^j > 0 $ , and a negative view otherwise. Here $ \& $ denotes the [bitwise AND operation](https://en.wikipedia.org/wiki/Bitwise_operation#AND).

You are going to organize a bridge tournament capable of accommodating at most $ k $ pairs of players (bridge is played in teams of two people). You can select teams arbitrarily while each player is in at most one team, but there is one catch: two players cannot be in the same pair if they disagree on $ 2 $ or more of those $ n $ topics, as they would argue too much during the play.

You know that the $ i $ -th player will pay you $ a_i $ dollars if they play in this tournament. Compute the maximum amount of money that you can earn if you pair the players in your club optimally.

## 说明/提示

In the first example, the best we can do is to pair together the $ 0 $ -th player and the $ 2 $ -nd player resulting in earnings of $ 8 + 5 = 13 $ dollars. Although pairing the $ 0 $ -th player with the $ 5 $ -th player would give us $ 8 + 10 = 18 $ dollars, we cannot do this because those two players disagree on $ 2 $ of the $ 3 $ hot topics.

In the second example, we can pair the $ 0 $ -th player with the $ 1 $ -st player and pair the $ 2 $ -nd player with the $ 3 $ -rd player resulting in earnings of $ 7 + 4 + 5 + 7 = 23 $ dollars.

## 样例 #1

### 输入

```
3 1
8 3 5 7 1 10 3 2```

### 输出

```
13```

## 样例 #2

### 输入

```
2 3
7 4 5 7```

### 输出

```
23```

## 样例 #3

### 输入

```
3 2
1 9 1 5 7 8 1 1```

### 输出

```
29```

# 题解

## 作者：幻影星坚强 (赞：6)

因为每个人都只能匹配与其仅有一个观点不同的人，所以同意数为奇数的人只能匹配同意数为偶数的人。于是将同意数为奇数的人放一边，同意数为偶数的边放一边，跑带权二分图匹配即可。

不过这样点数是 $O(2^n)$ 级别，边数是 $O(n\times2^n)$ 级别， 所以我们看能不能优化建图来减少点数和边数。

我们发现每个点会与 $n$ 个人相连，那么每匹配一对就会让剩下匹配的方案数最多减少 $2\times(n-1)$ （这两个人都不能与他另外 $n-1$ 个与其仅有一个观点不同的人匹配），加上这两个人匹配的这条边总共减少$2\times n-1$，所以说假如匹配 $k$ 次最多只会减少 $k\times(2\times n-1)$ 种匹配方式，也就是假如选择 $k\times(2\times n-1)$ 个匹配那么至少会存在 $k$ 种匹配方式。

那么我们将每个匹配的权值设为其对应的两个人的权值和，并选取权值最大的 $k\times(2\times n-1)$ 种匹配，那么它首先一定存在 $k$ 种匹配，其次最大权值的匹配一定只需要这些匹配。因为假如有 $d$ 个匹配不在这些权值较大匹配里面，那么先不选这 $d$ 个匹配，然后剩余选择 $k-d$ 个权值较大的匹配最多会减少 $(k-d)\times (2\times n - 1)$ 种匹配，剩余 $d\times (2\times n - 1)$ 种权值较大的匹配既能组成 $d$ 个匹配，而且里面的匹配权值肯定比先前的匹配权值更大。

这样点数和边数都变成了 $O(nk)$ 级别

```cpp
#include <iostream>
#include <cstdio>
#include <queue>
#include <cstring>
#include <queue>
using namespace std;
const int N = (1 << 20) + 10;
const int M = N << 2;
int n;
struct bian
{
    int from, to;
    long long w, val;
}eg[M << 1];
int front[N], num;
void add(int x, int y, long long w, long long val)
{
    eg[++ num].to = y;
    eg[num].from = front[x];
    front[x] = num;
    eg[num].w = w;
    eg[num].val = val;

    eg[++ num].to = x;
    eg[num].from = front[y];
    front[y] = num;
    eg[num].val = -val;
}
long long dis[N];
int _front[N];
int s, t;
int dy[N], tt;
int vis[N];
bool bfs()
{
    queue<int>q;
    q.push(s);
    for (int i = 1; i <= tt; ++ i)
    {
        dis[i] = -1e18;
    }
    dis[s] = 0;
    while (!q.empty())
    {
        int o = q.front();
        q.pop();
        vis[o] = 0;
        for (int i = front[o]; i; i = eg[i].from)
        {
            int to = eg[i].to;
            if(eg[i].w && dis[to] < dis[o] + eg[i].val)
            {
                dis[to] = dis[o] + eg[i].val;
                if(vis[to] == 0)
                {
                    vis[to] = 1;
                    q.push(to);
                }
            }
        }
    }
    // for (int i = 1; i <= n; ++ i)
    // {
    //     printf("dis : %d %lld\n", i, dis[i]);
    // }
    return dis[t] != -1e18;
}
long long cost;
long long dfs(int o, long long lim)
{
    // printf("%d %lld\n", o, lim);
    if(o == t)
    return lim;
    vis[o] = 1;
    long long mins = 0;
    for (int &i = _front[o]; i; i = eg[i].from)
    {
        int to = eg[i].to;
        // printf("%d\n", to);
        if(vis[to] == 1 || dis[to] != dis[o] + eg[i].val || eg[i].w == 0)continue;
        long long now = dfs(to, min(lim - mins, eg[i].w));
        if(now)
        {
            cost += now * eg[i].val;
            eg[i].w -= now;
            eg[((i - 1) ^ 1) + 1].w += now;
            mins += now;
            if(mins == lim)break;
        }
    }
    vis[o] = 0;
    return mins;
}
long long dinic()
{
    long long re = 0;
    while(bfs())
    {
        memcpy(_front, front, sizeof(front));
        long long gu;
        while(gu = dfs(s, 1e18))
        {
	        re += gu;
		}
        //printf("%lld %lld\n", re, cost);
    }
    return re;
}
int m, k, w[(1 << 20) + 10];
int popcnt[(1 << 20) + 10];
bool us[(1 << 20) + 10][20], adds[(1 << 20) + 10];
priority_queue<pair<int, pair<int, int> > >q;
int main()
{
	scanf("%d%d", &n, &k);
	for (int i = 0; i < (1 << n); ++ i)
	scanf("%d", &w[i]);
	for (int i = 0; i < (1 << n); ++ i)
	popcnt[i] = popcnt[i >> 1] + (i & 1);
	s = 1;
	t = 2;
	add(s, 3, k, 0);
	tt = 3;
	for (int i = 0; i < (1 << n); ++ i)
	{
		if(popcnt[i] & 1)
		{
			int maxs = 0, to = 0, ids = 0;
			for (int j = 0; j < n; ++ j)
			if(w[i] + w[(i ^ (1 << j))] > maxs)
			maxs = w[i] + w[(i ^ (1 << j))], to = (i ^ (1 << j)) + 1, ids = j;
			us[i][ids] = 1;
			q.push(make_pair(maxs, make_pair(i + 1, to)));
		}
	}
	for (int i = 1; i <= (2 * n - 1) * k; ++ i)
	{
		int o = q.top().second.first;
		if(dy[q.top().second.first] == 0)
		dy[q.top().second.first] = ++ tt, add(3, tt, 1, 0);
		if(dy[q.top().second.second] == 0)
		dy[q.top().second.second] = ++ tt, add(tt, t, 1, 0);
		add(dy[q.top().second.first], dy[q.top().second.second], 1, q.top().first);
		q.pop();
		-- o;
			int maxs = 0, to = 0, ids = 0;
			for (int j = 0; j < n; ++ j)
			if(us[o][j] == 0 && w[o] + w[(o ^ (1 << j))] > maxs)
			maxs = w[o] + w[(o ^ (1 << j))], to = (o ^ (1 << j)) + 1, ids = j;
			us[o][ids] = 1;
			q.push(make_pair(maxs, make_pair(o + 1, to)));
	}
	dinic();
	printf("%d", cost);
}
```


---

## 作者：freoepn (赞：2)

将所有二进制串看作点，能匹配的连边，可以发现此图一定为二分图，因为 $1$ 个数为奇数的二进制串肯定只能连 $1$ 个数为偶数的二进制串，$1$ 个数为偶数的二进制串肯定只能连 $1$ 个数为奇数的二进制串，跑 $dinic$ 二分图最大匹配即可完成，但是点的数量为 $2^n$ 个，边比点更多，会超时。

观察到，$k$ 只有 $200$，从 $k$ 的角度入手，因为每个点与 $n$ 个点相邻，所以每匹配一对就会使匹配数减少 $2 \times (n-1)$，加上匹配成功的那一对会减少 $2 \times n - 1$ 对，匹配 k 对顶多减少 $k \times (2n-1)$ 个匹配，也就是说 $k \times (2n-1)$ 匹配中肯定能选出 $k$ 个匹配，所以只需要连最大的 $k \times (2n-1)$ 条边，跑 $dinic$ 二分图最大匹配即可。

注意连最大的 $k \times (2n-1)$ 条边要桶排序。

---

## 作者：_Hugoi_ (赞：2)

[CF1572D Brifge Club](https://www.luogu.com.cn/problem/CF1572D)

## 题意

有 $2^n$ 个点从 $0$ 到 $2^n-1$ 编号，每个点有点权。

若两个点 $u$ 和 $v$ 有且仅有一个二进制位不同，则两点之间有边。


要求从这个图中选一个最多 $k$ 条边的匹配，使其所包含的 $2k$ 个点点权和最大。

输出最大点权和。

## 思路

首先发现，如果两点间有边，则一个点编号二进制下 1 的个数为奇数，另一个点编号二进制下 1 的个数为偶数。

所以想到按编号二进制下 1 的个数的奇偶分类，然后将 $i$ 向 $i\ \mathrm{xor} 2^j$ 连边 $(j \in 1\sim n-1)$。

然后发现这是一个二分图，边权为两个端点的权值和。

问题转化为在二分图上找包含 $k$ 条边的最大权匹配。

一开始想抽象建图跑最大流，但是发现不是太好做，于是考虑费用流。

因为边权只能计算一次，每个点也只能经过一次，所以容量均为 $1$，费用为端点的点权和，超级源点/汇点与点的连边费用为 $0$。

这样跑最大费用最大流，找到 $k$ 条增广路即可。

(不知道为啥我的最大费用最大流挂了，所以把费用取反，跑的最小费用最大流......)

但是，发现这样复杂度是过不了的，因为边数、点数实在是太多了。

由于我们要找的是一个包含 $k$ 条边的最大权匹配，那么有一些权值较小的边是不需要的。

因为求的是匹配，所以选中一条边后，有一些边就不可能再选了。

由于一个点会作为 $n$ 条边的端点，所以选中一条边后会有 $2n-2$ 条边无法再选。

所以只需要考虑权值前 $2nk$ 大的边即可。

时间复杂度 $O(n2^n+nk^2\log(nk))$。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
map<int,int> mp;
const int N=(1<<20)+10,inf=1e18;
int ans,n,k,s,t,a[N],tot,tott=1,dis[N],vis[N],cur[N],h[N],cntt,tmp;
struct node{
	int u,v,w;
}e[N*20];
struct Node{
	int nxt,to,w,c;
}E[N];
void add(int u,int v,int w){
	e[++tot]={u,v,w};
}
void ad(int u,int v,int w,int c){
	E[++tott]={h[u],v,w,c};
	h[u]=tott;
}
int spfa(){
	for(int i=0;i<=t;i++){
		dis[i]=inf;
		cur[i]=h[i];
		vis[i]=0;
	}
	queue<int> q;
	q.push(s);
	dis[s]=0;
	vis[s]=1;
	while(!q.empty()){
		int u=q.front();
		q.pop();
		vis[u]=0;
		for(int i=h[u];i;i=E[i].nxt){
			int v=E[i].to,w=E[i].w,c=E[i].c;
			if(dis[v]<=dis[u]+c||w==0) continue;
			dis[v]=dis[u]+c;
			if(!vis[v]){
				q.push(v);
				vis[v]=1;
			}
		}
	}
	return dis[t]!=inf;
}
int dfs(int u,int fl){
	if(u==t) return fl;
	int res=fl;
	vis[u]=1;
	for(int &i=cur[u];i;i=E[i].nxt){
		int v=E[i].to,w=E[i].w,c=E[i].c;
		if(dis[v]!=dis[u]+c||w==0||vis[v]) continue;
		int flow=dfs(v,min(res,w));
		if(flow){
			res-=flow;
			E[i].w-=flow;
			E[i^1].w+=flow;
			if(res<=0) break;
		}
	}
	return fl-res;
}
signed main(){
	ios::sync_with_stdio(0);
	cin>>n>>k;
	s=(1<<n),t=(1<<n)+1;
	for(int i=0;i<=(1<<n)-1;i++)
		cin>>a[i];
	for(int i=0;i<=(1<<n)-1;i++){
		int cnt=__builtin_popcount(i);
		if(__builtin_popcount(i)&1){
			for(int j=0;j<n;j++){
				int o=i^(1<<j);
				add(i,o,a[i]+a[o]);
			}
		}
	}
	sort(e+1,e+tot+1, [](node a,node b){
		return a.w>b.w;
	});
	for(int i=1;i<=2*n*k;i++){
		ad(e[i].u,e[i].v,1,-e[i].w);
		ad(e[i].v,e[i].u,0,e[i].w);
		if(!mp[e[i].u]){
			ad(s,e[i].u,1,0);
			ad(e[i].u,s,0,0);
			mp[e[i].u]=1;
		}
		if(!mp[e[i].v]){
			ad(e[i].v,t,1,0);
			ad(t,e[i].v,0,0);
			mp[e[i].v]=1;
		}
	}
	while(spfa()){
		int flow=dfs(s,inf);
		if(tmp+flow>k){
			ans+=(k-tmp)*dis[t];
			break;
		}
		ans+=flow*dis[t];
		tmp+=flow;
	}
	cout<<-ans<<'\n';
}
//3 3
//10 5 4 10 4 8 5 5 
```

---

## 作者：清烛 (赞：2)

## Description
问 $n$ 维超立方体，选 $k$ 条边的最大权匹配。$1\le n\le 20$，$1\le k\le 200$。

## Solution
显然，图为二分图，按照二进制表示下 $1$ 的个数即可分为左部和右部，中间连权为 $a_i + a_j$ 的边。

但是直接费用流或者 KM 都会死掉，因为点数为 $O(2^n)$ 级别，边数为 $O(n2^n)$ 级别，必死无疑。但是注意到这个 $k$ 是很小的，我们需要从 $k$ 上下手。

不难发现，每个点会连出去 $n$ 条边，如果我们选择了一个匹配，那么剩下能匹配的方案数就会减少 $2(n - 1)$，所以我们选了 $k$ 个匹配后最多只会减少 $k(2n - 1)$ 个匹配方式，即我们选了 $k(2n - 1)$ 个匹配就会至少存在 $k$ 个匹配。

所以我们只需要选出最大的 $k(2n - 1)$ 条边，然后跑费用流就行了，不难发现一定有最优的方案存在在这最大的 $k(2n - 1)$ 条边里面，证明可用反证法。

具体实现中，选出最大的 $k(2n - 1)$ 条边我们使用 STL 的 `nth_element()` 函数，其复杂度为 $O(\text{length of the seq})$，本题中为 $n2^n$，然后注意加边的时候不要给每个 $[0, 2^n - 1]$ 的球员都加边，否则会 TLE。

## Implementation

直接粘的 SPFA 费用流，好慢啊（（（

[评测记录](https://codeforces.com/contest/1572/submission/131155272)。

---

## 作者：云浅知处 (赞：1)

显然图是二分图。注意每个点度数不超过 $2n$，考虑取出前 $(2n-1)(k-1)+1$ 大的边，我们声称最大权匹配一定在这些边中取到。

这是因为，考虑一条边最多和 $2n-2$ 条边相邻，算上自己一共有 $2n-1$ 条边在选上这条边之后无法再选，

所以如果取出的边中只取了不到 $k$ 条边，目前不能选的边数至多为 $(2n-1)(k-1)$，因此一定有一条取出的边还可以选上，于是选上它自然比选一个未取出的更小的边更优。

这样就变成要对一个 $O(nk)$ 个点，$O(nk)$ 条边跑最大费用最大流的过程。注意增广只会进行 $k$ 轮，如果使用 dij 费用流，总复杂度为 $O(n2^n+n^2k^2+nk^2\log(nk))$。

但注意到一开始的图是严格分成三层的 DAG，且任意时刻图中最多出现 $O(k)$ 条负边，于是最短路长度为 $O(k)$ 级别，spfa 的实际复杂度为 $O(nk^2)$。

于是 dij 费用流的实际复杂度为 $O(n2^n+nk^2\log(nk))$，直接 spfa 的复杂度为 $O(n2^n+nk^3)$，均可通过。

https://codeforces.com/contest/1572/submission/246330855

---

## 作者：Leasier (赞：1)

将编号的 popcount 为偶数的项视为左部点，为奇数者视为右部点，$i$ 向 $i \operatorname{xor} 2^{j - 1}$ 连边、边权为其权值和，则答案为大小 $\leq k$ 的最大权匹配。

但点数为 $O(2^n)$、边数为 $O(2^n n)$、最大流量为 $O(k)$，直接跑费用流显然不能通过。
### 法一：模拟费用流
增广 $u_1 \to v_1 \to u_2 \to v_2 \to \cdots \to u_t \to v_t$ 的费用增量为 $a_{u_1} + a_{v_t}$。

考虑增广 $k - 1$ 次后的结果：此时有 $O(k)$ 条反悔边；考虑这些反悔边所容纳的点及其出边指向的点，共有 $O(nk)$ 个；除了这些点之外，其他点的出边是固定的。

注意到增广过程中一定不会出现负环，于是反悔边相关点的子图是一个 DAG。

对每个点开一个堆维护可选项信息，对全局开一个 set 维护所有非反悔边相关点的最优出边，在 DAG 上拓扑排序求出每个反悔边相关点的最优反悔终点即可。

时间复杂度为 $O(2^n n \log n + n^2 k^2)$。

但很显然这玩意听着就没有人想写。~~反正我没写（~~
### 法二：减少边数
首先有结论：设二分图左右部点数为 $n, m$，则求出大小 $\leq k$ 的最大权匹配只需保留边权前 $(n + m - 1)k$ 大的边。

证明：考虑一组此条件下的最大权匹配，则其至多占用 $(n + m - 1)k$ 条边；若选择了不在此边集内的边，不难反证出其不优。

在本题中，用 `nth_element` 保留边权前 $(2n - 1)k$ 大的边后跑最大费用流即可。

时间复杂度为 $O(2^n n + n^2 k^2)$。

法二代码：
```cpp
#include <iostream>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

typedef struct Match_tag {
	int x;
	int y;
	int z;
	Match_tag(){}
	Match_tag(int x_, int y_, int z_){
		x = x_;
		y = y_;
		z = z_;
	}
} Match;

typedef struct {
	int nxt;
	int end;
	int dis;
	int cost;
} Edge;

int cnt = 1;
int a[1048577], head[15607], refer[1048577], dis[15607], pre_dot[15607], pre_edge[15607];
bool vis[15607];
Match match[10485767];
Edge edge[23407];
queue<int> q;

bool operator <(const Match a, const Match b){
	return a.z > b.z;
}

inline void init(int n){
	for (register int i = 1; i <= n; i++){
		dis[i] = 0x80000000;
		vis[i] = false;
	}
}

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

inline void add_edge(int start, int end, int dis, int cost){
	cnt++;
	edge[cnt].nxt = head[start];
	head[start] = cnt;
	edge[cnt].end = end;
	edge[cnt].dis = dis;
	edge[cnt].cost = cost;
}

inline void spfa(int start){
	dis[start] = 0;
	vis[start] = true;
	q.push(start);
	while (!q.empty()){
		int cur = q.front();
		q.pop();
		vis[cur] = false;
		for (register int i = head[cur]; i != 0; i = edge[i].nxt){
			if (edge[i].dis != 0){
				int x = edge[i].end, y = dis[cur] + edge[i].cost;
				if (dis[x] < y){
					dis[x] = y;
					pre_dot[x] = cur;
					pre_edge[x] = i;
					if (!vis[x]){
						vis[x] = true;
						q.push(x);
					}
				}
			}
		}
	}
}

inline pair<int, int> maxcost(int n, int start, int end){
	pair<int, int> ans(0, 0);
	while (true){
		init(n);
		spfa(start);
		if (dis[end] <= 0) break;
		int flow = 0x7fffffff;
		for (register int i = end; i != start; i = pre_dot[i]){
			flow = min(flow, edge[pre_edge[i]].dis);
		}
		for (register int i = end; i != start; i = pre_dot[i]){
			edge[pre_edge[i]].dis -= flow;
			edge[pre_edge[i] ^ 1].dis += flow;
		}
		ans.first += flow;
		ans.second += flow * dis[end];
	}
	return ans;
}

int main(){
	int n = read(), k = read(), full = (1 << n) - 1, cnt = 0, require = (n * 2 - 1) * k, id = 3;
	for (register int i = 0; i <= full; i++){
		a[i] = read();
	}
	for (register int i = 0; i <= full; i++){
		if (__builtin_popcount(i) % 2 == 0){
			for (register int j = 1; j <= n; j++){
				int x = i ^ (1 << (j - 1));
				match[++cnt] = Match(i, x, a[i] + a[x]);
			}
		}
	}
	if (require >= cnt){
		require = cnt;
	} else {
		nth_element(match + 1, match + require + 1, match + cnt + 1);
	}
	add_edge(1, 2, k, 0);
	add_edge(2, 1, 0, 0);
	for (register int i = 1; i <= require; i++){
		if (refer[match[i].x] == 0) refer[match[i].x] = ++id;
		if (refer[match[i].y] == 0) refer[match[i].y] = ++id;
		add_edge(refer[match[i].x], refer[match[i].y], 1, match[i].z);
		add_edge(refer[match[i].y], refer[match[i].x], 0, -match[i].z);
	}
	for (register int i = 0; i <= full; i++){
		if (refer[i] != 0){
			if (__builtin_popcount(i) % 2 == 0){
				add_edge(2, refer[i], 1, 0);
				add_edge(refer[i], 2, 0, 0);
			} else {
				add_edge(refer[i], 3, 1, 0);
				add_edge(3, refer[i], 0, 0);
			}
		}
	}
	cout << maxcost(id, 1, 3).second;
	return 0;
}
```

---

## 作者：intel_core (赞：1)

注意到 $2^n$ 很大而 $k$ 很小，考虑从 $k$ 入手来做。

取一条匹配边后，最多只会影响 $2n-2$ 个点的状态，对其余点没有影响。为了考虑到这种影响，我们应该把这 $2n-2$ 个点对应的不包含这两个点边权最大的边加进考虑范围。

但是这样做我们需要先钦定上一条匹配边才能确定下一条边的范围。注意到我们如果一开始就只加 $(2n-1)k$ 条边进入匹配范围，就一定能保证得到的是最大结果（因为受到影响的点连出的边不在其中就说明边权太小，一定不会被选）。

这样点数和边数都是 $O(nk)$ 级别的，跑一遍 Dinic 即可。复杂度 $O(n^2k^3)$，问题不大。

---

