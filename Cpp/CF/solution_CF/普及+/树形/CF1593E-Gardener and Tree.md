# Gardener and Tree

## 题目描述

一棵 $n$ 个结点的树。一个人做了多次操作，在每次操作中，他删除了树的所有叶结点。叶结点指的是树中至多有一个相邻节点的结点。

![](http://61.186.173.89:2019/2021/10/15/c4f2d0e1827d5.png)

如上图中所示的树。下图显示了对树进行一次操作后的结果。
![](http://61.186.173.89:2019/2021/10/15/14602247d6f15.png)

注意特殊操作的情况:

1、对空树($0$ 个顶点)进行操作时不会改变它;

2、对于仅有一个顶点的树进行操作时会移除这个顶点(这个顶点被当作一个叶子);

3、对于仅有两个顶点的树进行操作时将删除两个顶点(两个顶点都被当作叶子处理)。

求 $k$ 次操作后还剩下多少个顶点?

## 样例 #1

### 输入

```
6

14 1
1 2
2 3
2 4
4 5
4 6
2 7
7 8
8 9
8 10
3 11
3 12
1 13
13 14

2 200000
1 2

3 2
1 2
2 3

5 1
5 1
3 2
2 1
5 4

6 2
5 1
2 5
5 6
4 2
3 4

7 1
4 3
5 1
1 3
6 1
1 7
2 1```

### 输出

```
7
0
0
3
1
2```

# 题解

## 作者：智子 (赞：12)

## 题意

对一棵 $n$ 个节点的树进行 $k$ 次操作，每次操作删去当前树的所有叶结点，求 $k$ 次操作后树还剩下多少个节点。

## 思路

注意到每个节点“在哪一次操作中被删去”的属性有明显的先后顺序，所以我们可以对这棵树进行一个拓扑排序。

定义每个节点“在哪一次操作中被删去”的值为 $rnk_i$。每次检查到 $deg_v = 1$ 的节点 $v$ 就将其入队，同时用“引荐”它入队的节点 $u$ 计算 $v$ 的 $rnk$ 值，$rnk_v = rnk_u + 1$。

最后检查哪些节点的 $rnk$ 值小于 $k$，这些节点会被剪掉，其他节点的数量就是答案。

## 代码

```cpp
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<queue>
#include<cstring>
using namespace std;

const int MAXN = 400000 + 5;

vector<int> G[MAXN];
int deg[MAXN], rnk[MAXN];
int n, k;

void toposort() {
    queue<int> q;
    for(int i = 1; i <= n; i++) {
        if(deg[i] == 1) {
            q.push(i);
            rnk[i] = 1;
        }
    }
    while(!q.empty()) {
        int u = q.front(); q.pop();

        for(int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];

            if(--deg[v] == 1) {
                rnk[v] = rnk[u] + 1;
                q.push(v);
            }
        }
    }
}

int main() {
    int T;

    cin >> T;
    while(T--) {
        memset(deg, 0, sizeof(deg));
        memset(rnk, 0, sizeof(rnk));

        cin >> n >> k;
        for(int i = 1; i <= n; i++) {
            G[i].clear();
        }
        for(int i = 1; i <= n - 1; i++) {
            int u, v;

            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
            deg[u]++; deg[v]++;
        }
        toposort();
        int ans = n;
        for(int i = 1; i <= n; i++) {
            if(rnk[i] <= k) {
                ans--;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 作者：LinkZelda (赞：3)

**题意**：

给定一棵大小为 $n$ 的树，每次操作会删去所有的叶子结点，问 $k$ 次操作后剩下的树的大小。

$\sum n\leq 4\cdot 10^5$。

**做法**:

考虑转化，记录所有点的度数，那么操作就变成：将全局所有权值为 $1$ 的点删去，并把和这些点有边相连的点权值 $-1$。

我们使用线段树维护区间最小值，如果区间最小值为 $1$ 我们就递归进入该节点，递归到叶子的话就把该点权值设为无穷大，然后暴力把和这个点在原树上有连边的点权值 $-1$ 即可，也就是单点修改。

线段树上所有叶子结点只会被访问一次，那么总的时间复杂度为 $O(n\log n)$。

注意特判只剩下一个点的情况。

- [代码](https://www.luogu.com.cn/paste/seo9aztn)。



---

## 作者：c1ampy (赞：1)

## 前言

蒟蒻做题时没想到拓扑排序，于是开始乱搞。

## 思路

一种再直接不过的想法是，求出每次操作删除的结点数量，再做 $ k $ 次减法得到答案。

做减法的总次数为 $ \sum k $，而题目并没有对 $ \sum k $ 的范围进行限制，所以我们要进行优化。

容易发现，每次操作至少删除 $ 2 $ 个结点（剩余结点数量为 $ 1 $ 的特殊情况除外），而在操作进行至剩余结点个数为 $ 0 $ 时，可视为操作不再进行，故实际做减法的次数不超过 $ \lceil \frac{n}{2} \rceil $。而题目对 $ \sum n $ 做出了限制，所以做减法的过程可以在规定时间内实现。

因此，如果我们能在规定时间内求出每次操作删除的结点数量，就可以解决此题。

稍稍进行转换，我们先求出每个结点在第几次操作时被删除，就能利用桶在 $ \mathcal{O}(n) $ 的时间内统计每次操作删除的结点数量。

设第 $ i $ 个结点在第 $ d_i $ 次操作时被删除，则对于叶子结点，有
$$
d_i = 1
$$

对于非叶子结点，有
$$
d_i = \max_{j \in S_i} \{d_j + 1\}
$$

其中 $ S_i $ 是与结点 $ i $ 相连且比 $ i $ 更早删除的结点组成的集合。

如果对于每个结点 $ i $，都有 $ i $ 的子结点比 $ i $ 更早删除，那么 $ S_i $ 就和 $ i $ 的子结点集合相同，我们就可以通过树上 dp 在 $ \mathcal{O}(n) $ 的时间内求出 $ d_i $，进而解决本题。（本段中「子结点」指与 $ i $ 直接相连的子结点）

如果我们将最后被删除的结点定为根结点，就可以使所有结点都满足以上性质。

至此，问题就转换成了找出最后被删除的结点。

考虑一条链的情况，每次操作只会删除链的两个端点，所以越靠中间的结点被删除的时间越晚，而最后被删除的点一定是链的中点。

把这个性质推广到树的情况，可知最后被删除的结点一定是直径中点。

所以，本题只需求出直径中点，以直径中点为根进行树上 dp，即可统计答案。总时间复杂度为 $ \mathcal{O}(n) $。

## 代码实现

注意细节：当直径长度为偶数时，可以在直径最中间的两个结点任选一个作为根结点，但这样会使另一个结点的 $ d_i $ 值与根节点不同（两者本应相等）。故在做减法时，如果发现剩余结点数量只有 $ 2 $，应在一次操作内全部删除。

代码如下：

```cpp
#include <iostream>
#include <queue>

const int max_n = 4e5 + 10;

struct Edge {
    int next;
    int to;
};

int head[max_n];
Edge edge[max_n << 1];
int edge_idx = 0;

int n, k;
int depth[max_n];
int deepest_node, max_depth;
int endpoint_1, endpoint_2, midpoint;
std::queue <int> q;
int level[max_n]; // 被删除时间
int cnt[max_n]; // 桶

void add_edge(const int from, const int to);
void bfs(const int source);
bool dfs(const int cur, const int fa);
void get_midpoint();
void get_level(const int cur, const int fa);

template <typename T> void clear(T * arr, const int n);
template <typename T> void fast_read(T & num);
template <typename T> void fast_write(const T & num);

int main() {

    int T;
    scanf("%d", &T);

    while (T--) {
        fast_read(n);
        fast_read(k);
        clear(head, n);
        edge_idx = 0;
        for (int i = 1; i <= n - 1; ++i) {
            int from, to;
            fast_read(from);
            fast_read(to);
            add_edge(from, to);
            add_edge(to, from);
        }

        // 特判加速
        if (k << 1 >= n) {
            puts("0");
            continue;
        }

        get_midpoint();
        get_level(midpoint, 0);
        
        // 特判链加速
        if (max_depth == n) {
            int remain = std::max(0, n - (k << 1));
            fast_write(remain);
            putchar('\n');
            continue;
        }

        clear(cnt, n);
        for (int i = 1; i <= n; ++i) {
            ++cnt[level[i]];
        }
        
        int remain = n;
        for (int i = 1; i <= k && remain; ++i) {
            remain <= 2 ? remain = 0 : remain -= cnt[i]; // 如果只剩两个结点要一次性删掉
        }
        fast_write(remain);
        putchar('\n');
    }

    return 0;
}

inline void add_edge(const int from, const int to) {
    edge[++edge_idx].to = to;
    edge[edge_idx].next = head[from];
    head[from] = edge_idx;
}

inline void bfs(const int source) {
    clear(depth, n);
    q = {};

    depth[source] = 1;
    q.emplace(source);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();

        if (depth[cur] > max_depth) {
            deepest_node = cur;
            max_depth = depth[cur];
        }

        for (int i = head[cur]; i; i = edge[i].next) {
            int to = edge[i].to;
            if (depth[to]) {
                continue;
            }
            depth[to] = depth[cur] + 1;
            q.emplace(to);
        }
    }
}

bool dfs(const int cur, const int fa) {
    if (cur == endpoint_2) {
        return true;
    }
    for (int i = head[cur]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (to == fa) {
            continue;
        }
        if (!dfs(to, cur)) {
            continue;
        }
        if (depth[cur] == max_depth + 1 >> 1) {
            midpoint = cur;
        }
        return true;
    }
    return false;
}

void get_midpoint() {
    max_depth = 0;
    bfs(1);
    endpoint_1 = deepest_node;
    max_depth = 0;
    bfs(deepest_node);
    endpoint_2 = deepest_node;
    dfs(endpoint_1, 0);
}

void get_level(const int cur, const int fa) {
    level[cur] = 1;
    for (int i = head[cur]; i; i = edge[i].next) {
        int to = edge[i].to;
        if (to == fa) {
            continue;
        }
        get_level(to, cur);
        level[cur] = std::max(level[cur], level[to] + 1);
    }
}

template <typename T> inline void clear(T * arr, const int n) {
    for (int i = 0; i <= n; ++i) {
        arr[i] = 0;
    }
}

template <typename T> inline void fast_read(T & num) {
    char ch = getchar();
    while (ch < '0' || '9' < ch) {
        ch = getchar();
    }
    num = 0;
    while ('0' <= ch && ch <= '9') {
        num = (num << 3) + (num << 1) + (ch ^ 48);
        ch = getchar();
    }
}

template <typename T> void fast_write(const T & num) {
    if (num > 9) {
        fast_write(num / 10);
    }
    putchar(num % 10 + 48);
}

```


---

## 作者：彭俊皓123 (赞：1)

# CF1593E 题解

看到题解区全是写拓扑排序的做法，那我就来分享一下树上直径的做法。

## 题意

给定 $n$ 个节点的无根树，每次将出度为 $1$ 的节点删去，问 $k$ 次操作后还剩下多少个点。

## 分析

题面要求每次将无根树的叶子节点删去，可以发现如果一个点被删去当且仅当其当前出度为 $1$，即其叶子均被删去的情况。

>考虑树上直径的性质：所有点到直径的距离不超过直径的一半。

有了这条性质之后，我们可以从直径入手。

因为每次删去都只会将直径的长度减少 $2$，而不会导致直径上不在两端的点被删去（因为这些点仍然是出度不小于 $2$ 的）。

因此先考虑将直径通过两遍 BFS 确定两个端点求出，顺便开一个 last 数组方便接下来处理直径： 
```cpp
int bfs(int k){
    for(int i=1;i<=n;++i)vis[i]=dis[i]=last[i]=que[i]=0;
    int hd=1,tl=0,ans=0;
    que[++tl]=k;dis[k]=1;
    while(hd<=tl){
        int x=que[hd++];
        if(vis[x])continue;
        ans=x;vis[x]=1;
        for(int i=head[x];i;i=to[i]){
            int now=nxt[i];
            if(vis[now])continue;
            que[++tl]=now;
            dis[now]=dis[x]+1;
            last[now]=x;
        }
    }
    return ans;
}
```
接着考虑给无根树选根来统计答案，此时最优的情况必然是选择直径的中点，因为中点是被最后删去的。于是我们统计的 dis 路径长和 last 数组就派上用场了：
```cpp
	int x1=bfs(1),x2=bfs(x1);
	int val=dis[x2]>>1;
	root=x2;
	while(val--)root=last[root];
```
这里会出现直径是偶数和直径是奇数的情况，在偶数的情况时有可能出现根节点也变成叶子被最后删去的情况，于是写一个特判：
```cpp
if(dis[x2]<=b<<1){pc('0'),pc('\n');continue;}
```
~~虽然当时觉得这玩意好像特判不掉，但是加上之后就是对了。~~

正确性证明：如果没删到最后一个点的话就不会特判到根节点，就可以直接扫叶子节点得到，因此只用在极端条件（全部删完）时特判即可。

接着就可以直接通过 dfs 统计答案了：
```cpp
int dfs(int x,int fath){
    hson[x]=dpt[x];
    int ans=1;
    for(int i=head[x];i;i=to[i])
    {
        int now=nxt[i];
        if(now==fath)continue;
        dpt[now]=dpt[x]+1;
        ans+=dfs(now,x);
        hson[x]=max(hson[x],hson[now]);
    }
    return hson[x]-dpt[x]<b||to[head[x]]==0?0:ans;
}
```
这里我是将两个 DFS 压在一起了，处理和预处理同时进行。

其中 hson 表示最长的子节点深度，即还需要多少次操作才能变成叶子节点。

返回条件是如果这个点已经被变成叶子删去时就没有答案了，否则将统计到的答案返回。

于是就结束了，以下是完整代码：

~~不要管我脑抽写的快读快写。~~
```cpp
#include<iostream>
#include<algorithm>
#include<string.h>
using namespace std;
const int MAXN=1600005,INF=0x3f3f3f3f;
int t,a,b,c,tot=0,root=0;
int head[MAXN],to[MAXN],nxt[MAXN];
int dpt[MAXN],hson[MAXN];
int que[MAXN],dis[MAXN],last[MAXN];
bool vis[MAXN];
void add(int x,int y){nxt[++tot]=y,to[tot]=head[x],head[x]=tot;}
inline int read()
{
    char x=getchar();int w=1,t=0;
    while(!isdigit(x))w=x=='-'?-1:w,x=getchar();
    while(isdigit(x))t=(t<<3)+(t<<1)+(x^48),x=getchar();
    return t*w;
}
int bfs(int k)
{
    for(int i=1;i<=a;++i)vis[i]=dis[i]=last[i]=que[i]=0;
    int hd=1,tl=0;
    que[++tl]=k;dis[k]=1;
    int ans=0;
    while(hd<=tl)
    {
        int x=que[hd++];
        if(vis[x])continue;
        ans=x;vis[x]=1;
        for(int i=head[x];i;i=to[i])
        {
            int now=nxt[i];
            if(vis[now])continue;
            que[++tl]=now;
            dis[now]=dis[x]+1;
            last[now]=x;
        }
    }
    return ans;
}
int dfs(int x,int fath)
{
    hson[x]=dpt[x];
    int ans=1;
    for(int i=head[x];i;i=to[i])
    {
        int now=nxt[i];
        if(now==fath)continue;
        dpt[now]=dpt[x]+1;
        ans+=dfs(now,x);
        hson[x]=max(hson[x],hson[now]);
    }
    return hson[x]-dpt[x]<b?0:ans;
}
char buf[1024];
int p=0;
inline void pc(char x)
{
    buf[p++]=x;
    if(p==1024)fwrite(buf,p,1,stdout),p=0;
}
inline void print(int x)
{
    int stk[15],to=0;
    while(x)stk[++to]=x%10,x/=10;
    while(to)pc(stk[to--]+'0');
    pc('\n');
}
int main()
{
    t=read();
    while(t--)
    {
        a=read();b=read();tot=root=0;
        for(int i=1;i<=a;++i)head[i]=0,dpt[i]=0,nxt[i]=0,to[i]=0;
        for(int i=1;i<a;++i)
        {
            int x=read(),y=read();
            add(x,y);add(y,x);
        }
        if(b>=a){pc('0'),pc('\n');continue;}
        int x1=bfs(1),x2=bfs(x1);
        int val=dis[x2]>>1;
        root=x2;
        while(val--)root=last[root];
        dpt[root]=0;
        if(dis[x2]<=b<<1){pc('0'),pc('\n');continue;}
        print(dfs(root,0));
    }
    fwrite(buf,p,1,stdout);
    fflush(stdout);
    return 0;
}
```


---

## 作者：Alkaid_Star (赞：1)

### 题目大意

> $T$ 组数据。
>
> 现在有一棵 $n$ 个结点的树，对其进行 $k$ 次操作，每次操作删除树的所有叶子结点。
>
> 现在问 $k$ 次操作后还剩下多少节点。
>
> 特殊情况：
>
> - 对空树进行操作时不改变任何东西。
>
> - 对一个顶点的树进行操作时会移除这个顶点（这个顶点被当作一个叶子）。
>
> - 对有两个顶点的树进行操作时将删除两个顶点（两个顶点都被当作叶子处理）。

### 解题思路

看一下题，脑海中大概是一个从外层逐渐蚕食这棵树的过程。

每个点被删除当且仅当这个点只剩下了与父亲的一条边（叶子结点）或者一条边都不剩（根的特殊情况）。

这玩意儿明显是个拓扑排序。

我们在开始时把树的所有叶子结点入队，每次发现删去当前点后与其相连的点度数 $\le 1$，将其入队即可。

然后对每个点设置一个 $dep$ 值表示第一次被删掉的时候是操作了几次。初始值是一开始入队的点 $dep$ 值为 $1$。

最后只需要统计有多少个 $dep$ 值 $>k$ 的点即可。

我的代码里要特判 $n=1$ 的情况大概是因为开始入队时写丑了，写的是`deg[i]==1`，没有把单独的一个根节点入队（

不过特判一下总没错（

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=400005;
const int inf=100000000000000005;

struct Edge{
	int vet,nxt;
}e[N<<1];

int n,k,edge=0,head[N];
int deg[N],dep[N];
bool inq[N];
queue <int> Q;

inline int read(){
	int x=0,f=1; char ch=getchar();
	while (!isdigit(ch)){ if (ch=='-') f=-1; ch=getchar(); }
	while (isdigit(ch)){ x=x*10+ch-'0'; ch=getchar(); }
	return x*f;
}

inline void addedge(int x,int y){
	e[++edge].vet=y;
	e[edge].nxt=head[x];
	head[x]=edge;
}

signed main(){
// 	freopen("CF1593E.in","r",stdin);
// 	freopen("CF1593E.out","w",stdout);
	int T=read();
	while (T--){
		n=read(),k=read();
		if (n==1){
			if (k>=1) printf("0\n");
			else printf("1\n");
			continue;
		}
		edge=0; for (int i=1;i<=n;++i) head[i]=0,deg[i]=0;
		for (int i=1;i<=n-1;++i){
			int x=read(),y=read();
			addedge(x,y);
			addedge(y,x);
			++deg[x],++deg[y];
		}
		while (!Q.empty()) Q.pop();
		for (int i=1;i<=n;++i) dep[i]=inf,inq[i]=false;
		for (int i=1;i<=n;++i)
			if (deg[i]==1){ Q.push(i); inq[i]=true; dep[i]=1; }
		while (!Q.empty()){
			int x=Q.front(); Q.pop();
			// printf("x=%lld dep[x]=%lld\n",x,dep[x]);
			for (int i=head[x];i;i=e[i].nxt){
				int v=e[i].vet;
				// printf("x=%lld v=%lld deg[v]=%lld\n",x,v,deg[v]-1);
				if ((--deg[v])<=1){
					if (!inq[v]){
						inq[v]=true;
						dep[v]=dep[x]+1;
						Q.push(v);
					}
				}
			}
		}
		// printf("dep: "); for (int i=1;i<=n;++i) printf("%lld ",dep[i]); printf("\n");
		int ans=0;
		for (int i=1;i<=n;++i)
			if (dep[i]>k) ++ans;
		printf("%lld\n",ans);
	}
	return 0;
}
```



---

## 作者：xzhif (赞：1)

### 很明显的拓扑排序啊！
题意：

给你一棵 $n$ 个节点的树，进行 $k$ 次操作。

每次操作会删除所有叶子节点。

问最后还剩多少节点。

特殊的，当树只剩两个节点后一轮操作后将没有节点。

当点的 $x<2$ 时,直接入队！

一个树的叶子节点，显然它的出度为 $1$（因为它只和它父亲有边）。

所以拓扑排序的时候，当度数小于等于 $1$ 时候，就把这个节点删掉。

注意，一定是小于等于 $1$，而不是等于 $1$，因为当 $n=1$ 时，度数为 $0$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,k,u,v,d[100001],cnt,b,vis[100001],l,kk;
vector<int> g[100001];
struct xs{
	int x,l;
};
queue<xs> q;
void init(){
	for(int i=1;i<=100000;i++)g[i].clear();
	memset(vis,0,sizeof(vis));
	memset(d,0,sizeof(d));
	cnt=b=kk=l=0;
	while(!q.empty())q.pop();
}
int topo(){
	for(int i=1;i<=n;i++){
		if(d[i]<2)q.push((xs){i,1});
	}
	while(!q.empty()){
		int u=q.front().x,l=q.front().l;
		q.pop();
		if(l>k||vis[u])continue;
		cnt++;
		vis[u]=1;
		for(int i=0;i<g[u].size();i++){
			v=g[u][i];
			d[v]--;
			if(d[v]<2){
				kk++;
				q.push((xs){v,l+1});
			}
		}
	}
	return max(n-cnt,0);
}
int main(){	
	//freopen("delete.in","r",stdin);
	//freopen("delete.out","w",stdout);
	scanf("%d",&t);
	while(t--){
		init();
		scanf("%d%d",&n,&k);
		for(int i=1;i<n;i++){
			scanf("%d%d",&u,&v);
			g[u].push_back(v);
			g[v].push_back(u);
			d[u]++;
			d[v]++;
		}
		printf("%d\n",topo());
	}
}
```


---

## 作者：cppcppcpp3 (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/CF1593E)。

[CF 传送门](http://codeforces.com/problemset/problem/1593/E)。

## $\textbf{Solution}$

先特判掉 $n=1$ 的情况（答案为 $0$）。

剩下的情况有 $n \ge 2$，一个点被删除当且仅当这个点的度数为 $1$，即每轮的删除都是在删除在上轮操作后度数为 $1$ 的点。这可以用拓扑排序解决。

记 $d_i$ 为点 $i$ 的当前度数，$f_i$ 为 $i$ 在第几轮被删除，$vis_i=1/0$ 表示 $i$ 是否已被删除。

具体而言，在拓扑排序过程中，先将 $d_i=1$ 的点入队。从当前点 $u$ 向所有相邻节点 $v$ 更新（条件是 $f_u < k$），即 $d_v$ 减少 $1$。若 $v$ 满足 $vis_v=0$ 和 $d_v=1$，则 $f_v \leftarrow f_u+1$，并将 $v$ 入队。

时间复杂度为 $O(\sum n)$。

```cpp
#include<bits/stdc++.h>
#define il inline
using namespace std;
const int N=4e5+5;

il int wrd(){
	int x=0,f=1; char c=getchar();
	while(!isdigit(c)){if(c=='-')f=-1; c=getchar();}
	while(isdigit(c)){x=x*10+c-48,c=getchar();}
	return x*f;
}

int n,k,cnt,ans,d[N],head[N],f[N];
bool vis[N];

struct edge{
	int to,nxt;
}e[N<<1];

il void add(int u,int v){
	e[++cnt]=edge{v,head[u]},head[u]=cnt;
}

void bfs(){
	queue<int> q;
	for(int i=1;i<=n;++i) if(d[i]<=1) q.push(i),f[i]=1; //d[i]=0 实际上是对 n=1 的特判。

	while(!q.empty()){
		int u=q.front(); q.pop();
		if(f[u]>k) break;
		vis[u]=1;
		for(int i=head[u];i;i=e[i].nxt){
			int v=e[i].to;
			if(!vis[v] && (--d[v])==1) f[v]=f[u]+1,q.push(v);
		}
	} 
}

void solve(){
	n=wrd(),k=wrd(),ans=cnt=0;
	for(int i=1;i<=n;++i) vis[i]=0,f[i]=d[i]=head[i]=0;
	for(int i=1;i<n;++i){
		int u=wrd(),v=wrd();
		add(u,v),add(v,u);
		++d[u],++d[v];
	}
	bfs();
	for(int i=1;i<=n;++i) ans+=(!vis[i]);
	printf("%d\n",ans);
}

main(){
	int T=wrd();
	while(T--) solve();
	return 0;
}
```

---

## 作者：jr_inf (赞：0)

[原题面](https://www.luogu.com.cn/problem/CF1593E)

### 题意：
给出一个 $n$ 个点的树，删除 $k$ 次叶子节点，求剩下的节点数。

### 思路：

设 $cnt_i$ 为 $k$ 最小为多少时点 $i$ 会被删除。

当 $i$ 将要被删除时，它一定是现在的叶子，联想到拓扑排序的特点，直接跑一遍拓扑排序即可。

初始时所有叶子的 $cnt$ 都为 $1$，跑完拓扑排序后遍历一遍 $cnt$ 数组统计 $cnt_i > k$ 的数量，时间复杂度 $O(n)$。

code：

```cpp
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstring>
using namespace std;
const int N=4e5+10;
int t,n,k,cnt[N],d[N],ans;
bool f[N];
vector<int> g[N];
queue<int> q;
int main()
{
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d%d",&n,&k);
		ans=0;
		memset(f,0,sizeof(f));
		memset(d,0,sizeof(d));
		memset(cnt,0,sizeof(cnt));
		for(int i=1;i<=n;i++)g[i].clear();
		for(int i=1,x,y;i<n;i++)
		{
			scanf("%d%d",&x,&y);
			g[x].push_back(y);
			g[y].push_back(x);
			d[x]++,d[y]++;
		}
		if(k==0)
		{
			printf("%d\n",n);
			continue;
		}
		for(int i=1;i<=n;i++)if(d[i]==1)q.push(i),f[i]=cnt[i]=1;
		while(!q.empty())
		{
			int t=q.front(); 
			q.pop();
			for(int i=0;i<g[t].size();i++)
			{
				int v=g[t][i];
				if(f[v])continue;
				d[v]--;
				if(d[v]==1)
				{
					f[v]=1;
					cnt[v]=cnt[t]+1;
					q.push(v);
				}
			}
		}
		for(int i=1;i<=n;i++)if(cnt[i]>k)ans++;
		printf("%d\n",ans);
	}
}
```


---

## 作者：sycqwq (赞：0)

__题意：__

给你一棵 $n$ 个节点的树，进行 $k$ 次操作。

每次操作会删除所有叶子节点。

问最后还剩多少节点。

特殊的，当树只剩两个节点后一轮操作后将没有节点

__思路：__

这一道题是一个拓扑排序的模板题。

一个树的叶子节点，显然它的出度为 $1$ （因为它只和它父亲有边）

所以拓扑排序的时候，当度数小于等于 $1$ 时候，就把这个节点删掉。

注意，一定是小于等于 $1$ ，而不是等于 $1$ ，因为当 $n=1$ 时，度数为 $0$ 。

__代码：__

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=4e5+655;
int t,n,k,d[maxn],bk[maxn];
vector<int> e[maxn];
int top()
{
    int s=0,tp=1;
    queue<int> q;
    memset(bk,0,sizeof bk);
    for(int i=1;i<=n;i++)
    {
        if(d[i]<=1)
        {
            bk[i]=1;
            q.push(i);
        }
    }
    while(!q.empty())
    {
        int x=q.front();
        q.pop();
        tp=bk[x];
        --tp;
        if(tp>=k)
            break;
        ++s;
        
        for(int i=0;i<e[x].size();i++)
        {
            int v=e[x][i];
            // cout<<x<<' '<<v<<endl;
            --d[v];
            if(d[v]<=1&&!bk[v])
            {
                bk[v]=bk[x]+1;
                // cout<<bk[v]<<endl;
                q.push(v);
            }
        }
    }
    return s;
}
int main()
{
    cin>>t;
    for(int i=1;i<=t;i++)
    {
        cin>>n>>k;
        for(int j=1;j<=n;j++)
            e[j].clear();
        memset(d,0,sizeof(d));
        for(int j=1;j<n;j++)
        {
            int x,y;
            cin>>x>>y;
            ++d[x];
            ++d[y];
            e[x].push_back(y);
            e[y].push_back(x);
        }
        cout<<n-top()<<endl;
        
    }
    return 0;
} 
```


---

## 作者：Xhesika_Frost (赞：0)

每一次删除叶子并且叶子的度数为 $1$ ，怎么看都和拓扑序有关系。

并且确实如此，我们只需要在读图的时候统计一下每一个点的度数，把度数为 $1$   和度数为零的点放进一个队列，并且记录它们属于第几轮被删除的。这样就像拓扑排序一样，删除一个点，让所有与它相邻的点的度数 $-1$ 然后把度数编程 $1,0$ 的点放进队列里，循环往复，直到删完了 $k$ 轮或者是没有点可以删了为止。

这里有一个很奇怪的地方，度数为零的点是什么情况？是为了处理这棵树只有一个节点以及这棵树没删空了的情况。

这样就是一个简单的拓扑问题了。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<stack>
#include<map>
#define lll long long
using namespace std;
int t;
int n,k;
int del[400005];
queue<pair<int,int> > q;
int head[400005];
struct ed{
	int to;
	int ne;
}ed[800005];
int du[400005];
int p;
pair<int,int> xx;
void add(int f,int to){
	ed[++p].to=to;
	ed[p].ne=head[f];
	head[f]=p;
}
int x,y;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d%d",&n,&k);
		p=0;
		memset(head,0,sizeof(head));
		memset(du,0,sizeof(du));
		memset(del,0,sizeof(del));
		while(!q.empty())
		q.pop();
		for(int i=1;i<n;++i){
			scanf("%d%d",&x,&y);
			add(x,y);
			add(y,x);
			du[x]++;
			du[y]++;
		}
		for(int i=1;i<=n;++i){
			if(du[i]==1||du[i]==0){
				q.push(make_pair(i,1));
			}
		}
		int cnt=n;
		while(!q.empty()){
			xx=q.front();
		//	cout<<xx.first<<endl;
			q.pop();
			if(del[xx.first]) continue;
			if(xx.second==k+1){
				break;
			}
			cnt--;
			del[xx.first]=1;
			int no=xx.first;
			for(int i=head[no];i;i=ed[i].ne){
				int v=ed[i].to;
				du[v]--;
				if(du[v]==1||du[v]==0){
					if(del[v]!=1){
					q.push(make_pair(v,xx.second+1));
					}
				}
			}
		}
		cout<<cnt<<endl;
	}
	return 0;
}
	
 
```

---

## 作者：Ryo_Yamada (赞：0)

> 给你一棵树，每次删除它的所有叶子节点（叶子节点定义为仅有一条边与其相连的点），称为一次操作。问 $k$ 次操作后还会剩余多少个点。

> 特殊地，对于当前剩余点数 $=0$，则这次操作不会有任何效果。对于当前剩余点数 $=1$，则删掉这个点。对于当前剩余点数 $=2$，则删除这两个点。

容易想到，用拓扑的方式做，两个 queue 存储，每次操作将一个 queue 里的所有点删掉，如果这个点的度 $=1$ 则加入另一个 queue。

需要注意特判当前点数 $=1$ 的情况。因为一个数只会删一次，而有 $k$ 次操作，所以时间复杂度是线性的。

$\text{Code}$：

```cpp
int n, k;
int deg[N];
vector<int> e[N];
 
void topo(int x) {
	queue<int> q[2];
	int ans = n, f = 0;
	rep(i, 1, n) if(deg[i] == 1) q[0].push(i);
	while(ans && x) {
		if(ans == 1) {
			ans = 0;
			break;
		}
		--x;
		while(!q[f].empty()) {
			--ans;
			int u = q[f].front();
			q[f].pop();
			for(int v : e[u]) {
				--deg[v];
				if(deg[v] == 1) q[f ^ 1].push(v);
			}
		}
		f ^= 1;
	}
	cout << ans << endl;
}
 
int main() {
	int T; cin >> T;
	W(T) {
		qread(n, k);
		rep(i, 1, n) deg[i] = 0, e[i].clear();
		rep(i, 1, n - 1) {
			int u, v;
			qread(u, v);
			++deg[u], ++deg[v];
			e[u].pb(v), e[v].pb(u);
		}
		topo(k);
	}
	return 0;
}
```


---

