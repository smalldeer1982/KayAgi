# [ABC401E] Reachable Set

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc401/tasks/abc401_e

给定一个包含 $N$ 个顶点和 $M$ 条边的无向图。顶点编号为 $1,2,\ldots,N$，第 $i$ 条边 $(1 \leq i \leq M)$ 连接顶点 $u_i$ 和顶点 $v_i$。

对于每个 $k=1,2,\ldots,N$，请解决以下问题：

> 考虑以下操作：
> 
> - 选择一个顶点，删除该顶点及其所有连接的边。
>  
> 通过重复上述操作，判断是否能够满足以下条件：
> 
> - 从顶点 $1$ 出发，通过边能够到达的顶点集合恰好为 $\{1,2,\ldots,k\}$（共 $k$ 个顶点）。
>  
> 如果可能，求出满足条件所需的最少操作次数；否则输出 `-1`。

## 说明/提示

### 约束条件

- $1 \leq N \leq 2 \times 10^5$
- $0 \leq M \leq 3 \times 10^5$
- $1 \leq u_i < v_i \leq N$ $(1 \leq i \leq M)$
- $(u_i, v_i) \neq (u_j, v_j)$ $(1 \leq i < j \leq M)$
- 输入的所有数值均为整数

### 样例解释 1

例如，当 $k=2$ 时，可以通过删除顶点 $3$、顶点 $4$ 和顶点 $5$（共 3 次操作），使得从顶点 $1$ 可达的顶点仅为 $\{1,2\}$。由于无法通过少于 3 次操作满足条件，因此第 2 行输出 `3`。  
当 $k=6$ 时，不需要删除任何顶点即可满足条件，因此第 6 行输出 `0`。

### 样例解释 3

图中可能不存在任何边。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
6 7
1 2
1 5
2 3
2 4
2 5
3 6
5 6```

### 输出

```
2
3
3
2
1
0```

## 样例 #2

### 输入

```
5 4
1 5
2 3
3 4
4 5```

### 输出

```
1
-1
-1
-1
0```

## 样例 #3

### 输入

```
2 0```

### 输出

```
0
-1```

## 样例 #4

### 输入

```
11 25
6 9
5 9
2 3
1 9
10 11
4 5
9 10
8 9
7 8
3 5
1 7
6 10
4 7
7 9
1 10
4 11
3 8
2 7
3 4
1 8
2 8
3 7
2 10
1 6
6 11```

### 输出

```
5
-1
-1
-1
-1
-1
4
3
2
1
0```

# 题解

## 作者：_hi_ (赞：4)

# 思路

看到好多大佬都用了并查集来做，小蒟蒻膜拜，只能给出一个奇奇怪怪的做法。

考虑递增枚举 $k$ 正向加点，可以发现如果这张图满足要求，第 $k$ 个点的来源必定小于 $k$。所以可以在每次加点的时候把与它相连接的点记下来。

如果第 $k$ 个点没有被记下来，则说明无法完成，输出  $-1$。

否则，还需要查看是否一到 $k$ 全能被到达。可以发现之前没被收录的那些点只能通过点 $k$ 进行拓展。所以，从 $k$ 跑 dfs。注意，大于 $k$ 的点不跑。最后查看是否所有点都被收录了。

答案就是被收录点集的大小减去 $k$。

# AC Code:


```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,m,mp[200005],ans;
vector<long long>poi[200005];
inline void dfs(long long now,long long lm){
    for(int i=0;i<poi[now].size();i++){
        if(mp[poi[now][i]]==0){
            ans++;
            mp[poi[now][i]]=1;
            if(poi[now][i]<=lm)dfs(poi[now][i],lm);
        }
    }
}
int main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=m;i++){
        long long a,b;
        scanf("%lld%lld",&a,&b);
        poi[a].push_back(b);
        poi[b].push_back(a);
    }
    mp[1]=1;
    ans=1;
    for(int i=0;i<poi[1].size();i++){
        mp[poi[1][i]]=1;
        ans++;
    }
    printf("%lld\n",ans-1);
    long long last=1;//优化，只用从上一个成功的 k 往下 check 即可。
    for(int i=2;i<=n;i++){
        if(mp[i]==1){
            dfs(i,i);
            long long flag=1;
            for(int j=last;j<=i;j++){//优化
                if(mp[j]==0){
                    flag=0;
                    break;
                }
            }
            if(flag==1)printf("%lld\n",ans-i),last=i;
            else printf("-1\n");
        }
        else{
            printf("-1\n");
        }
    }
}
```

---

## 作者：WuMin4 (赞：3)

## [[ABC401E] Reachable Set](https://atcoder.jp/contests/abc401/tasks/abc401_e)

## 题意

给你一个 $N$ 个点的无向图，每次操作可以删去一个点及与它相连的边。问对于 $k=1,2,\cdots,N$，使得点 $1$ 的可达点恰好为 $1,2,\cdots,k$ 的最小操作次数为多少或判断无解。

## 思路

考虑满足点 $1$ 的可达点为 $1,2,\cdots,k$ 所需要满足的限制条件是什么。

1. 点 $1$ 可以到达 $1,2,\cdots,k$。

2. 点 $1$ 不能到达 $k+1,k+2,\cdots,n$。

于是对于限制一，我们可以维护一个并查集，对于每个新加入的点跟有连边且比它小的点进行合并。

因为每次合并两个连通块会减少一个连通块，所以当合并到点 $k$ 时的合并次数恰好为 $k-1$ 时，说明前 $k$ 个点均在一个连通块中。

对于限制二，很显然最优方案即为删去与该连通块有连边的所有点。

于是我们可以维护一个 set，表示需要删去的点。当每次加入一个点时若 set 中包含该点，则删除（因为该点变为可达点了），然后再加入所有与它有连边且大于它的点。此时 set 的大小即为最少的操作次数。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,f[200005],tot;
int find(int x){
	if(f[x]!=x) f[x]=find(f[x]);
	return f[x];
}
void uni(int x,int y){
	x=find(x),y=find(y);
	if(x!=y) f[x]=y,tot++;
}
vector<int> t[200005];
set<int> er;
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr),cout.tie(nullptr);
	cin>>n>>m;
	for(int i=1;i<=n;i++) f[i]=i;
	for(int x,y,i=1;i<=m;i++){
		cin>>x>>y;
		t[x].push_back(y);
		t[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		if(er.find(i)!=er.end()) er.erase(i);
		for(int v:t[i]) if(v>i) er.insert(v);
		else if(v<i) uni(i,v);
		if(i!=1&&tot!=i-1) cout<<-1<<endl;
		else cout<<er.size()<<endl;
	}
	return 0; 
}
```

---

## 作者：laiyouming (赞：2)

#### 思路
我们发现想要从顶点 $1$ 出发，通过边能够到达的顶点集合恰好为 $\{1,2,\ldots,k\}$ 必须满足集合中的点是连通的，所以用并查集维护，并记录每一个并查集里有多少个数，如果节点 $1$ 所在的并查集里的数少于 $i$ 个，就输出 $-1$，否则就看 $1$ 所在的并查集里数连向多少个不在集合里的点。
#### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int n,m,b[200010],d[200010],e[200010];
vector<int>a[200001];
set<int>c;
int cz(int x){
	if(b[x]==x){
		return x;
	}
	return b[x]=cz(b[x]);
}
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	for(int i=1;i<=n;i++){
		b[i]=i,d[i]=1;
	}
	for(auto i:a[1]){
		e[i]=1;
		c.insert(i);
	}
	printf("%d\n",c.size());
	for(int i=2;i<=n;i++){
		for(auto j:a[i]){
			if(j<=i){
				int x=cz(i),y=cz(j);
				if(x!=y){
					b[x]=y;
					d[y]+=d[x];
				}
			}
			else{
				if(e[j]==0){
					e[j]=1;
					c.insert(j);
				}
			}
		}
		c.erase(i);
		if(d[cz(i)]==i){
			printf("%d\n",c.size());
		}
		else{
			printf("-1\n");
		}
	}
}
```

---

## 作者：dongzirui0817 (赞：1)

## 思路

分别考虑 $k = 1, \, 2, \dots , \, n$ 时的答案。

首先，对于一个编号不超过 $k$ 的节点，它与 $1$ 号节点之间一定存在一个路径，使得这个路径上所有节点编号都不超过 $k$。不然该节点可以到达 $1$ 号节点时，一定存在一个编号大于 $k$ 的节点，可以到达 $1$ 号节点。

而只要这个条件成立，答案就不可能不存在（对编号大于 $k$ 的节点操作即可，虽然这样操作不一定是最优的）。

所以每次只看连接的两个节点的编号在 $1$ 至 $k$ 之间的边所组成的子图，如果这个子图中，$1$ 至 $k$ 号节点互相联通，那么存在操作方案，否则不存在。

而在存在操作方案时，只要对满足以下条件的节点做操作即可：

- 节点编号大于 $k$。
- 存在一条边，连接了该点与另一个编号不超过 $k$ 的节点。

因为节点编号不大于 $k$ 的节点，做了操作后方案就不满足了。而对于没有与不超过 $k$ 的节点有一条边连接的节点，按照这种操作方案而言已经不可能到达 $1$ 号节点了。

至此，思路推理完毕。

## 实现

先看如何判断有无操作方案。**这可以用并查集来做**（建议不要用其他乱七八糟的方法，样例 $4$ 证实了这一点）。

至于用并查集怎么做，只需对于每一个 $k$ 所直接连接的节点，如果该节点编号小于 $k$，就合并这两个点代表的集合。

至于答案，只需用 set 即可。设操作的节点集合为 $V$。

对于每个 $k$，如果 $k \in V$，那么从 $V$ 中删除 $k$。

然后对于满足以下条件的节点，加入 $V$ 中：

- 该节点编号大于 $k$。
- 该节点不在 $V$ 中。
- 该节点与 $k$ 号节点有一条边直接连接。

最后，答案是 $V$ 的元素个数。

其他细节详见代码。

```
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector <int> edge[200010];
set <int> s;
int si[200010], fa[200010];

int findset(int x) {	//查询代表元
	if (fa[x] == x) return x;
	return findset(fa[x]);
}

inline void mergeset(int x, int y) {	//合并集合
	x = findset(x), y = findset(y);
	if (x == y) return;	
	/*注意特判代表元相同的情况，
	  我就是这样送给 AtCoder 5 minutes 的*/
	if (si[x] > si[y]) swap(x, y);
	fa[x] = y, si[y] += si[x];
}

int main() {
	cin >> n >> m;
	for (int u, v ; m-- ; )
		cin >> u >> v,
		edge[u].push_back(v),
		edge[v].push_back(u);
	for (int i = 1 ; i <= n ; i++)
		si[i] = 1, fa[i] = i;
	for (int i = 1 ; i <= n ; i++) {
		if (s.count(i)) s.erase(i);
		for (auto y : edge[i]) {
			if (y > i) s.insert(y);
			else mergeset(i, y);
		}
		if (si[findset(1)] < i) puts("-1");
		//注意 1 号节点可能已经不是代表元了。
		else cout << s.size() << endl;
	}
	return 0;
}
```

## 后记

A 题输出反了，一次罚单；C 题没判负数的情况，一次罚单；E 题合并没特判，又一次罚单。

加在一起，只不过送了 AtCoder $15$ 分钟罢了……

---

## 作者：xiaoyin2011 (赞：1)

## AT_abc401_e [ABC401E] 可达集 题解

[题目链接](https://www.luogu.com.cn/problem/AT_abc401_e)

### 题目大意

一个无向图中有 $N$ 个顶点和 $M$ 条边。顶点编号为 $1,2,\ldots,N$，第 $i$ 条边连接顶点 $u_i$ 和 $v_i$。

对于每个 $i$，重复删除一个点和其连边，直到从点 $1$ 通过遍历边可到达的顶点集合正好由点 $1,2,\ldots,i$ 组成。确定是否可以通过重复执行这个操作达到以上条件，如果可以，输出最小操作次数，否则输出 `-1`。

每个 $i$ 的删除互相独立。

### 思路及实现

首先考虑能不能实现。删除一些点后，从 $1$ 出发能到达的点只有 $1 \sim i$，说明 $1$ 开始所在的连通块中，删除所有 $j > i$ 的点 $j$，仍能保证块连通。同时，由于删除后剩余点都要和 $1$ 相连，说明此时也仅剩一个大小为 $i$ 的连通块。

每次计算 $i$ 时，临时删除 $j > i$ 相关的边肯定是不能接受的。如果我们递增计算 $i$，被删除的点逐步减少，而且每次恢复的点恰好也是递增。想到可以化拆为并，使用并查集。

从 $1 \le i \le N$ 的每个 $i$，加入和 $i$ 有关的边后，可以理解为删除了所有 $j > i$ 的点，此时判断是否仅有一个连通块即可。但是对于 $1 \le j \le i$ 去判断还是太慢了，由于其他点已被删除，直接检查 $1$ 所在的连通块大小是否为 $i$ 也是正确的答案。

---

接下来考虑最小操作次数。

任何与 $j \le i$ 的点相邻的非 $j \le i$ 的点都必须删除，以此隔离开两部分。反之，其他所有顶点都可以保留。

直接对于 $i$，考虑所有 $j$ 相邻点太过慢了。可以反向思考，这个点在何时被认定为和 $j$ 相邻，即对于点 $u$，设和他相邻的最小编号点 $v$，何时 $v \le i$，且 $u > i$，$u$ 就是需要删除的点。即最少删除次数 `ans` 数组的 $[v, i)$ 都需要加一，可以通过差分解决。

总体时间复杂度接近 $O(N + M)$。

### AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll N, M, u, v;
vector<int> e[200005];
ll mu[200005], ans[200005];
ll fa[200005], sz[200005];
ll find(ll x)
{
    if (fa[x] != x) fa[x] = find(fa[x]);
    return fa[x];
}
void merge(ll x, ll y)
{
    x = find(x);
    y = find(y);
    if (x == y) return ;
    if (sz[x] < sz[y]) swap(x, y);
    fa[y] = x;
    sz[x] += sz[y];
}
bool ok[200005];
int main()
{
    scanf("%lld%lld", &N, &M);
    for (int i = 1; i <= N; i++)
		fa[i] = i, sz[i] = 1;
    for (int i = 1; i <= M; i++)
	{
        scanf("%lld%lld", &u, &v);
        e[u].push_back(v);
        e[v].push_back(u);
    }
    for (int i = 1; i <= N; i++)
	{
        ll mv = 9e18;
        for (int j = 0; j < e[i].size(); j++) 
		{
			ll v = e[i][j];
            if (v < i)
            {
				mv = min(mv, v);
            	merge(i, v);
			}
        }
        if (mv != 9e18)
            mu[i] = mv;
        else
            mu[i] = -1;
        if (sz[find(1)] == i)
            ok[i] = 1;
    }
    for (int i = 1; i <= N; i++)
	{
        if (mu[i] == -1) continue;
        if (mu[i] > i - 1) continue;
        ans[mu[i]]++;
        ans[i]--;
    }
    for (int i = 1; i <= N; i++)
    	ans[i] += ans[i - 1];
    for (int i = 1; i <= N; i++)
	{
        if (ok[i])
            printf("%lld\n", ans[i]);
        else
        	printf("-1\n");
    }
    return 0;
}
```

---

## 作者：xxr___ (赞：1)

提供一种超级好想好写的方法。

题目实际上要求只能从 $1$ 走到 $j\in[1,k]$ 的点，且路径上编号也是 $j\in[1,k]$ 所以我们可以直接开个 `set` 表示当前**需要删**的点的集合。

刚开始我们让 $1$ 进入，由于我们需要保留 $[1,i]$ 的点，所以我们要让 `set` 中小于等于 $i$ 的点进来，并且，它的连边中，如果编号大于 $i$ 我们必须要把这个点加进来，表示需要删除这个点，不然从 $i$ 就能走到 $j,j > i$ 了，然后开个数组记录下是否入过队就做完了。

代码：
```cpp
#include<iostream>
#include<set>
#include<vector>

using std::cin;
using std::set;
using std::vector;
const int N = 3e5 + 5;
bool vs[N];
set<int> st;
vector<int> e[N];
int main(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	int n,m,V = 0;
	std::cin >> n >> m;
	for(int i = 1;i <= m; ++i){
		int u , v;
		std::cin >> u >> v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	st.insert(1);
	vs[1] = 1;
	for(int i = 1;i <= n; ++i){
		while((int)st.size() && *st.begin() <= i){
			int u = *st.begin();
			++ V;
			for(auto it:e[u]){
				if(!vs[it]){
					st.insert(it);
					vs[it] = 1;
				}
			}
			st.erase(u);
		}
		std::cout << ((V ^ i) ? -1 : (int)st.size()) << '\n';
	}
	return 0;
}
```

---

## 作者：yyrwlj (赞：1)

我们考虑从起点到一个点的路径上最大编号最小是多少，而这个东西我们可以直接最短路求，令这个东西叫 $dis_i$。

那么对于一个合法的 $k$，当且仅当 $\forall i \le k, dis_i \le k$，我们做个前缀 $\max$，即令 $mx_i = \max_{j=1}^i dis_j$，那么合法条件就变成了 $mx_k \le k$。

需要删的点就是 $1$ 到 $k$ 组成的联通块内连向联通块外的出点，我们将边排个序，每次将编号小的点合法的点对应的编号大的点在树状数组上标记一下，需要删的点的个数就是 $k + 1$ 到 $n$ 中被标记的点的个数。

```cpp
#include <bits/stdc++.h>
#define lowbit(o) o & -o
#define pb push_back
#define x first
#define y second
using namespace std;
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int, int> PII;
typedef pair<LL, LL> PLL;
const int N = 200005;
const int mod = 1e9;
const int inf = 0x3f3f3f3f;
const LL INF = 2e18;
vector<int> g[N];
int dis[N], mx[N], n, m;
PII G[N*5];
bool st[N];
int tr[N];
inline void add(int x,int y)
{
	for (;x<=n;x+=lowbit(x))
		tr[x]+=y;
}
inline int ask(int x)
{
	int res = 0;
	for (;x;x-=lowbit(x))
		res += tr[x];
	return res;
}
void work()
{
	cin >> n >> m;
	for (int i=1;i<=m;i++){
		int a,b;
		cin>>a>>b;
		g[a].pb(b);
		g[b].pb(a);
		if (a>b)swap(a,b);
		G[i]={a,b};
	}
	sort(G+1,G+m+1);
	memset(dis,0x3f,sizeof dis);
	dis[1] = 1;
	priority_queue<int,vector<int>,greater<int> > q;
	q.push(1);
	while (!q.empty())
	{
		int t = q.top();
		q.pop();
		if (st[t])continue;
		st[t]=true;
		for (int i : g[t])
			if (dis[i] > max(dis[t], i))
				dis[i] = max(dis[t],i),q.push(i);
	}
	int mn=n+1;
	for (int i=1;i<=n;i++)
		if (dis[i]==inf)
			{mn=i;break;}
	for (int i=1;i<=n;i++)
		mx[i]=max(mx[i-1],dis[i]);
	memset(st,false,sizeof st);
	for (int i=1,j=1;i<mn;i++)
	{
		if (mx[i]>i)
		{
			cout<<"-1\n";
			continue;
		}
		while (j<=m && G[j].x<=i)
		{
			if (!st[G[j].y])
			{
				add(G[j].y, 1);
				st[G[j].y]=true;
			}
			j ++;
		}
		cout<<ask(n)-ask(i)<<'\n';
	}
	for (int i=mn;i<=n;i++)cout<<"-1\n";
}
signed main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int _T = 1;
    //cin >> _T;
    while (_T--)
    	work();
    return 0;
}
```

---

## 作者：MutU (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/AT_abc401_e)

首先如果说对于某个 $k$ 存在解，意味着从一出发，只经过编号小于等于 $k$ 的点，能够到达所有编号小于等于 $k$ 的点。

考虑从小到大利用并查集维护连通性。从小到大枚举每个点，把这个点所有连向编号小于等于 $k$ 点的边的两端并在一起。这样每次结束后所有小于等于 $k$ 点都和 $1$ 并在一起说明可以走到。

直接暴力检查是 $O(n^2)$ 的。假设在处理完一个点后我们用某种奇妙的方法知道了哪些点和一并在一起，哪些点没有。我们把没有并在一起的点全部扔进一个队列。每处理到一个新点也把他扔进队列。

遍历队列元素，如果当前元素和 $1$ 并起来了就出队列，否则直接 `break`。

显然一个点只要跟 $1$ 并上了，在今后整个过程中也能并上。所以用上述过程遍历队列后，如果队列为空说明有解。

只要确定有解就很简单了。所有与小于等于 $k$ 的点=一条边直接相连的点必须删（否则通过这条边肯定能到）。所有不与小于等于 $k$ 的点直接相连的都不用删（因为删完了直接相邻的边，没有可能到这些点）。

维护多少个点直接相连较为简单，可以见代码部分。


```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N = 3000100;
int n,m,tot;
struct edge{
	int nxt,to;
}e[N*2];
bool vis[N]; //记录这个点有没有计入答案的计算
int ans;
int head[N],cnt;
inline void add(int u,int v){
	e[++cnt].nxt=head[u];
	e[cnt].to=v;
	head[u]=cnt;
}
int f[N];
queue <int> q;
int find(int x){
	if(f[x]==x) return x;
	else return f[x]=find(f[x]);
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++) f[i]=i;
	for(int i=1;i<=m;i++){
		int u,v;
		cin>>u>>v;
		add(u,v); add(v,u);
	}
	for(int i=1;i<=n;i++){
		if(vis[i]) ans--; //清除这个点对答案的影响
		q.push(i);
		for(int j=head[i];j;j=e[j].nxt){
			int v=e[j].to;
			if(v<=i){
				int U=find(i),V=find(v);
				if(U!=V) f[U]=V;
			}else if(!vis[v]){
				vis[v]=true;
				ans++;
			}
		}
		while(!q.empty()){
			int u=q.front();
			if(find(u)!=find(1)) break;
			q.pop();
		}
		if(!q.empty()) cout<<-1<<'\n';
		else cout<<ans<<'\n';
	}
	return 0;
}
```

---

## 作者：_Weslie_ (赞：0)

## Solution AT_abc401_e

### Idea

我们使用 dijstkra 预处理 $1$ 为起点的单源最小路，其中最小路的定义是途径节点最大编号的最小值。

如果 $dis_i>i$，这说明加入点 $1$ 到 $i$ 之后，$1$ 点和 $i$ 点肯定不联通，于是无解。

否则判断解。

先下一个结论：假如我们要保留前 $i$ 个点，只需要删除编号大于 $i$ 且与前 $i$ 的点中至少一个相连的点即可。这个是显然的。

我们考虑一个点对答案的影响。我们设 $minn_i$ 为点 $i$ 连的编号最小的点，那么从 $minn_i$ 开始，到 $i$ 结束，这 $x\in [minn_i,i-1]$ 的区间里，$i$ 一定满足编号大于 $x$ 且与前 $x$ 个点至少有一个相连，于是在这个区间里答案要加一。

显然的静态区间加法，这里我选择用了差分。

### Code

```
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=500005;
const ll INF=0x3f3f3f3f3f3f3f3f;
struct node{
	int u,v;
	ll w;
	int nxt;
}e[N<<2];
int head[N],cnt;
void add(int u,int v,ll w){
	e[++cnt].u=u;
	e[cnt].v=v;
	e[cnt].w=w;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
struct pt{
	int pos;
	ll dis;
	friend bool operator <(pt _,pt __){
		return __.dis<_.dis;
	}
};
priority_queue<pt>q;
int n,m,s,vis[N];
ll dis[N];
pt make_node(int pos,ll dis){
	pt new_pt;
	new_pt.pos=pos;
	new_pt.dis=dis;
	return new_pt;
}
void dj(){
	dis[s]=1;
	q.push(make_node(s,dis[s]));
	while(!q.empty()){
		pt p=q.top();
		q.pop();
		int now=p.pos;
		if(vis[now])continue;
		vis[now]=1;
		for(int i=head[now],v;i;i=e[i].nxt){
			v=e[i].v;
			if(dis[v]>max(dis[now],e[i].w)){
				dis[v]=max(dis[now],e[i].w);
				if(!vis[v])q.push(make_node(v,dis[v]));
			}
		}
	}
}
int ans[N],minn[N];
int main(){
	scanf("%d%d",&n,&m);
    s=1;
    memset(minn,0x3f3f3f3f,sizeof minn);
	for(int i=1,u,v;i<=m;i++){
		scanf("%d%d",&u,&v);
        minn[u]=min(minn[u],v);
        minn[v]=min(minn[v],u);
		add(u,v,max(u,v));
		add(v,u,max(u,v));
	} 
	for(int i=1;i<=n;i++)dis[i]=0x3f3f3f3f;
	dj();
    for(int i=1;i<=n;i++){
        if(minn[i]>=i)continue;
        ans[minn[i]]++;ans[i]--;
    }
    int sum=0;
    long long maxx=0;
    for(int i=1;i<=n;i++){
        sum+=ans[i];maxx=max(maxx,dis[i]);
        if(maxx>i)printf("-1\n");
        else printf("%d\n",sum);
    }
	return 0;
}
```

---

## 作者：cyq32ent (赞：0)

我们先考虑最小操作次数的问题。设 $h_v$ 是节点 $v$ 相连的最小的节点 $u$，且 $u<v$，那么，当 $h_v\leq k<v$ 时，我们必须要删除 $v$ 节点，否则剩下的树里会出现 $v$。所以，对于每个节点 $v$，都对 $h_v\leq k<v$ 的 $k$ 的答案有 $1$ 的贡献。

下面考虑存在性的问题。将每条边按照其较大的端点的编号排序，并依次加入并查集，检查连通性即可。

以下代码省略了并查集模板。

```cpp
vector<int>E[333333];
int N,M,mn[333333],diff[333333],ans[333333];
int main(){
	cin>>N>>M;
	memset(mn,0x3f,sizeof mn);
	for(int u,v;M--;)
		cin>>u>>v,E[v].push_back(u),mn[v]=min(mn[v], u);
	for(int v=2;v<=N;v++)if(mn[v]<0x3f3f3f3f)diff[mn[v]]++,diff[v]--;
	for(int k=1;k<=N;k++)ans[k]=ans[k-1]+diff[k];
	for(int k=2;k<=N;k++){
		for(auto u:E[k])union_(u, k);
		ans[k]=(find_(1)==find_(k)&&size_[find_(1)]==k)?ans[k]:-1;
	}for(int k=1;k<=N;k++)cout<<ans[k]<<endl;
}

```

---

