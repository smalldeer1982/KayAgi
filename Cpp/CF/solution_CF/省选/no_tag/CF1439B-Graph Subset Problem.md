# Graph Subset Problem

## 题目描述

You are given an undirected graph with $ n $ vertices and $ m $ edges. Also, you are given an integer $ k $ .

Find either a clique of size $ k $ or a non-empty subset of vertices such that each vertex of this subset has at least $ k $ neighbors in the subset. If there are no such cliques and subsets report about it.

A subset of vertices is called a clique of size $ k $ if its size is $ k $ and there exists an edge between every two vertices from the subset. A vertex is called a neighbor of the other vertex if there exists an edge between them.

## 说明/提示

In the first test case: the subset $ \{1, 2, 3, 4\} $ is a clique of size $ 4 $ .

In the second test case: degree of each vertex in the original graph is at least $ 3 $ . So the set of all vertices is a correct answer.

In the third test case: there are no cliques of size $ 4 $ or required subsets, so the answer is $ -1 $ .

## 样例 #1

### 输入

```
3
5 9 4
1 2
1 3
1 4
1 5
2 3
2 4
2 5
3 4
3 5
10 15 3
1 2
2 3
3 4
4 5
5 1
1 7
2 8
3 9
4 10
5 6
7 10
10 8
8 6
6 9
9 7
4 5 4
1 2
2 3
3 4
4 1
1 3```

### 输出

```
2
4 1 2 3 
1 10
1 2 3 4 5 6 7 8 9 10 
-1```

# 题解

## 作者：Piwry (赞：9)

~~搞崩 $\texttt{U} \texttt{\red m\red\_\red n\red i\red k}$ 心态的题目X~~

## 解析

不难发现度数小于 $k-1$ 的点对两种答案都没有贡献

于是就将这些点删除；注意删除时可能还会产生新的度数小于 $k-1$ 的点，因此可以用类似拓扑排序的删除方法

现在剩下的点的度数均不小于 $k-1$

考虑随便选一个度数恰好为 $k-1$ 的点 $u$，假设它就在大小为 $k$ 的团中，将和 $u$ 有边的且未被删除的点都拉出来，暴力枚举 $\frac {k(k-1)} 2$ 对结点，验证每对结点间是否存在边；验证边可以考虑用 `vector` 存下每个结点的边，然后排序后用二分查找。这样验证一次的复杂度是 $O(k^2\log m)$ 的（实现常数较小的话这样就能过 \fad）

如果发现 $u$ 不在团中，就删掉 $u$，再重复上面的几个步骤。最后若还有点剩余，那么剩下的点的度数都至少为 $k$，因此剩下的点即是要求的答案 $1$；否则只需考虑每步我们删除的结点都不能成为答案的一部分，因此就可以证明图中不存在任何满足要求的答案

考虑枚举团的总复杂度。对于 $\frac {k(k-1)} 2> m$ 的情况，我们不再尝试枚举团，于是可能尝试枚举团时，有 $k\leq \sqrt m$（约）；接着考虑枚举团的次数，不难发现度数不小于 $k-1$ 的结点个数是 $\frac m k$ 的。于是总的枚举团的复杂度就为 $O(\frac m k \cdot k^2\log m)=O(mk\log m)=O(m\sqrt m\log m)$

具体实现时，我们可以考虑直接删所有度数小于 $k$ 的结点；在将要删除度数为 $k-1$ 的结点时，验证一次它是否在大小为 $k$ 的团内

这样做仍然是正确的。证明只需考虑我们删的每一个度数小于 $k-1$ 的结点不会作为大小为 $k$ 的团的一部分；而删除的度数为 $k-1$ 的结点在删除前都会被检查一次

## CODE

实现 [参考](https://codeforces.com/contest/1439/submission/98704924)

实现常数较小的话这样就能过

再实在不行就上 hash 把 \fad（于是赛时一堆哈希被 hack...）

```cpp
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using std::vector;
using std::queue;
using std::sort;
using std::binary_search;

/*------------------------------IO------------------------------*/

int read(){
	int x =0; char c =getchar(); bool f =0;
	while(c < '0' || c > '9') (c == '-') ? f =1, c =getchar() : c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return (f) ? -x : x;
}

void write(const int &x){
	if(x/10)
		write(x/10);
	putchar('0'+x%10);
}

/*------------------------------Main------------------------------*/

int main(){
	for(int t =0, T =read(); t < T; ++t){
		int n =read(), m =read(), k =read();
		vector<vector<int> > E(n);
		for(int i =0; i < m; ++i){
			int u =read()-1, v =read()-1;
			E[u].push_back(v), E[v].push_back(u);
		}
		vector<int> d(n), vis(n)/*0 表示未访问，1 表示访问，2 表示删除*/;
		for(int i =0; i < n; ++i){
			d[i] =E[i].size();
			sort(E[i].begin(), E[i].end());
		}
		
		queue<int> que;
		for(int i =0; i < n; ++i)
			if(d[i] < k){
				que.push(i);
				vis[i] =1;
			}
		vector<int> cilque;
		while(!que.empty() && cilque.empty()){
			int u =que.front();
			que.pop();
			vis[u] =2;
			
			if(1ll*(k-1)*k/2 <= m && d[u] == k-1 && cilque.empty()){
				cilque.push_back(u);
				for(int v:E[u])
					if(vis[v] != 2)
						cilque.push_back(v);
				bool OK =1;
				for(int v:cilque){
					for(int w:cilque){
						if(v == w)/*一条无向边仅判一次*/
							break;
						else if(!binary_search(E[v].begin(), E[v].end(), w)){
							OK =0;
							break;
						}
					}
					if(!OK)
						break;
				}
				if(!OK)
					cilque.clear();
			}
			
			for(int v:E[u])
				if(--d[v] == k-1 && vis[v] == 0){
					vis[v] =1;
					que.push(v);
				}
		}
		
		if(!cilque.empty()){
			putchar('2'), putchar('\n');
			for(int u:cilque)
				write(u+1), putchar(' ');
			putchar('\n');
		}
		else if(count(vis.begin(), vis.end(), 0) > 0){
			vector<int> ans;
			for(int i =0; i < n; ++i)
				if(vis[i] == 0)
					ans.push_back(i);
			putchar('1'), putchar(' '), write(ans.size()), putchar('\n');
			for(int u:ans)
				write(u+1), putchar(' ');
			putchar('\n');
		}
		else
			putchar('-'), putchar('1'), putchar('\n');
	}
}
```

---

## 作者：lgswdn_SA (赞：2)

对于第二个（每个点都至少有 $k$ 个点集内出边）我们称为  k-core 子图。对于二可以用一个经典的求 k-core 的算法，每次拓扑删除那些度数小的点。然后到了 $k$ 的时候我们就直接看一下是不是全部被删光了即可。

关于第一个求团。我们发现一个大小为 $k$ 的团在不存在 k-core 的情况，这些点都必然是 (k-1)-core 中的点。于是我们对于每个在求 $k-1$ 的时候求出来的点遍历它所有连接的点，然后判断是否是团。这个单次操作是 $O(k^2)$ 的。

但是，实际上 k-core 点的个数是 $O(m/k)$ 的级别的，这意味着求团的复杂度为 $O(mk)$。然后，团的边数应该在 $O(k^2)=O(m)$，也就是说复杂度是 $O(m\sqrt{m})$。

具体操作时，我们维护一下 deg，然后用 unordered_map 作邻接矩阵。本人曾经使用过 unordered_set 来代替 vector 和 deg 存邻接表，然后被卡常死了。然后数据中还存在卡 unordered_map 的数据……

https://codeforces.com/contest/1439/submission/131558660

---

## 作者：Pengzt (赞：1)

# Graph Subset Problem

[题目链接](https://www.luogu.com.cn/problem/CF1439B)。[cnblogs](https://www.cnblogs.com/Pengzt/p/18665313)。

### Problem

$T$ 组数据。

给你一个有 $n$ 个顶点和 $m$ 条边的无向图，和一个整数 $k$。

请你找到一个大小为 $k$ 的团（称一个 $k$ 个点的集合为团，当且仅当点集大小为 $k$，并且该子集的每两个顶点之间存在一条边）或一个非空的顶点子集，使该子集的每个顶点在该子集中至少有 $k$ 个邻居。

输出方案。

对于每个测试用例：

- 如果找到一个合法点集，在第 $1$ 行输出 `1` 和子集的大小。在第 $2$ 行，以任意顺序输出子集的顶点。
- 如果找到一个大小为 $k$ 的团，那么在第 $1$ 行输出 `2`。第 $2$ 行中，以任意顺序输出该团的顶点。
- 如果没有所需的子集和集团，请输出 `-1`。
- 如果存在多个可能的答案，输出其中任意一个。

数据范围：$1 \le n, m, k \le 10^5$，$1 \le \sum n \le 2 \times 10^5$。

### Sol

首先如果 $k > \sqrt m$，那么一定无解。然后先把所有度数小于 $k - 1$ 的点删掉（要更新度数）。发现如果满足条件的团一定可以有一个点在当前的图中度数为 $k - 1$，不然我可以找到一个点集。对于所有当前度数为 $k - 1$ 的点，暴力枚举所有连出去的点，判断两两之间是否有连边，由于这样的点不超过 $\lfloor \frac mk \rfloor$ 个，使用 umap 可以使判定变为 $\mathcal{O}(1)$。这一部分的复杂度为 $\mathcal{O}(mk)$。然后删掉所有度数小于 $k$ 的点。如果这个时候，点集被变成了空集，此时就是无解的。如果还有剩下的点，则这些点构成一个合法的点集。然后删点的过程显然可以用一个类似于拓扑排序的东西解决。时间复杂度 $\mathcal{O}(m\sqrt m)$。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
int n, m, K;
int deg[100005], vis[100005], vse[100005];
vector<pii> e[100005];
queue<int> que;
unordered_map<int, int> mp[100005];
int tp, stk[100005];
int Work(int x) {
	if ((int) mp[x].size() == K - 1) {
		tp = 0;
		for (auto i : mp[x])
			stk[++tp] = i.first;
		int mark = 1;
		for (int i = 1; i <= tp && mark; i++)
			for (int j = i + 1; j <= tp && mark; j++)
				if (!mp[stk[i]].count(stk[j]))
					mark = 0;
		if (mark) {
			printf("2\n%d ", x);
			for (int i = 1; i <= tp; i++)
				printf("%d%c", stk[i], " \n"[i == tp]);
			return 1;
		}
	}
	for (auto i : mp[x]) {
		deg[i.first]--;
		if (deg[i.first] == K - 1)
			que.emplace(i.first);
		mp[i.first].erase(x);
	}
	mp[x].clear(), deg[x] = 0;
	return 0;
}
int ans[200005];
void Solve() {
	for (int i = 1; i <= n; i++)
		deg[i] = vis[i] = 0, e[i].clear(), mp[i].clear();
	scanf("%d%d%d", &n, &m, &K);
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		e[u].emplace_back(v, i), e[v].emplace_back(u, i);
		deg[u]++, deg[v]++;
	}
	if (K > ceil(sqrt(2 * m)))
		return puts("-1"), void();
	for (int i = 1; i <= n; i++)
		if (deg[i] < K - 1)
			que.emplace(i), vis[i] = 1;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		for (auto i : e[u]) {
			int v = i.first, id = i.second;
			if (vse[id])
				continue;
			vse[id] = 1;
			deg[v]--;
			if (deg[v] < K - 1 && !vis[v])
				que.emplace(v), vis[v] = 1;
		}
	}
	for (int i = 1; i <= n; i++)
		for (auto j : e[i])
			if (!vse[j.second])
				mp[i][j.first] = 1;
	for (int i = 1; i <= m; i++)
		vse[i] = 0;
	for (int i = 1; i <= n; i++)
		if (deg[i] == K - 1)
			que.emplace(i);
	int mark = 0;
	while (!que.empty()) {
		int u = que.front();
		que.pop();
		if (!mark)
			mark = Work(u);
	}
	if (mark)
		return;
	int aCnt = 0;
	for (int i = 1; i <= n; i++)
		if (deg[i] >= K)
			ans[++aCnt] = i;
	if (!aCnt)
	    return puts("-1"), void();
	printf("1 %d\n", aCnt);
	for (int i = 1; i <= aCnt; i++)
		printf("%d%c", ans[i], " \n"[i == aCnt]);
}
int main() {
	int T;
	scanf("%d", &T);
	while (T--)
		Solve();
	return 0;
}
```

---

## 作者：lory1608 (赞：1)

### CF1439B题解

**这题真的就是毒瘤，卡这卡了一个半小时。**

- 首先我们考虑如何判断是否存在$1$的情况
  - 我们只用把所有点的度数记录下来，然后把度数$<k$的加入一个队列中，不断删边并减少度数，知道队列为空，此时有两种情况。
    - 若总点数为$0$，可以判断不存在上述情况。
    - 若总点数不为$0$，将所有的点报告之。

- 其次我们考虑是否存在$2$的情况
  - 我们只用在上述过程中，没到一个点的度数$=k-1$，那么我们就暴力判断这$k$个点是否组成一个合法的完全子图，如存在则报告之，否则继续执行上述操作。
  - **注意到：当$k\geq \sqrt{2\times m}$我们一定不存在这种情况，这样我们暴力判断的过程最多只有$O(\dfrac{m}{k})$次（原因是删去一个点,会删去与之相连的边），每次复杂度$O(k^2)$，这样这部分的复杂度就是$O(m\sqrt{m})$了**，由于我们用```set```存边，总复杂度为$O(m\sqrt{m}\log m)$。可以通过此题。

参考代码：

```cpp
#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define REP(u) for(int i=p[u];i!=-1;i=e[i].nxt)
#define PII pair<int,int>
#define ll long long
#define pb push_back
#define rd (rand()<<16^rand())
#define sz(x) (int)(x.size())
#define gc (_p1==_p2&&(_p2=(_p1=_buf)+fread(_buf,1,100000,stdin),_p1==_p2)?EOF:*_p1++)
using namespace std;
char _buf[100000],*_p1=_buf,*_p2=_buf;
inline int gi()
{
	int x=0,f=1;
	char ch=gc;
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')f=-1;
		ch=gc;
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<3)+(x<<1)+(ch^48);
		ch=gc;
	}
	return (f==1)?x:-x;
}
inline int max(int a,int b){return a>b?a:b;}
inline int min(int a,int b){return a<b?a:b;}
const int maxn=2e5+5;
int n,m,T;
vector<int>vec[maxn];
int ind[maxn],k;
set<int>s[maxn];
bool vis[maxn],vis2[maxn];
vector<int>ans;
queue<int>q;
inline void init()
{
	FOR(i,1,n)vec[i].clear(),ind[i]=0,s[i].clear(),vis[i]=0,vis2[i]=0;
	ans.clear();while(!q.empty())q.pop();
}
inline void input()
{
	n=gi(),m=gi(),k=gi();
	FOR(i,1,m)
	{
		int u=gi(),v=gi();
		vec[u].pb(v),vec[v].pb(u);
		ind[u]++,ind[v]++;
	}
}
inline void dfs(int u)
{
	vis2[u]=1;
	ans.pb(u);
	for(auto v:vec[u])
	{
		if(!vis[v]&&!vis2[v])
		{
			dfs(v);
		}
	}
}
struct node
{
	int u,indd;
	node(int uu=0,int ii=0){u=uu,indd=ii;}
	inline bool operator<(const node &b)const
	{
		return indd<b.indd;
	}
};
inline bool check(int u,int xx)
{
	vector<int>vec1;vec1.clear();
	vec1.pb(u);
	for(auto x:s[u])
	{
		if(ind[x]<k-1)return 0;
		for(auto y:vec1)
		{
			if(!s[x].count(y))
			{
				return 0;
			}
		}
		vec1.pb(x);
	}
	return 1;
}
inline void solve(int xx)
{
	if(k==1)
	{
		printf("2\n1\n");
		return ;
	}
	FOR(i,1,n)
	{
		for(auto x:vec[i])s[i].insert(x);
		ind[i]=s[i].size();
	}
	FOR(i,1,n)
	{
		if(ind[i]<k)q.push(i),vis[i]=1;
		if(ind[i]==k-1)
		{
			if(1LL*k*(k-1)<=2*m&&check(i,xx))
			{
				printf("2\n");
				for(auto x:s[i])printf("%d ",x);
				printf("%d\n",i);
				return ;
			}
		}
	}
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		for(auto v:s[u])
		{
			ind[v]--;
			s[v].erase(u);
			if(!vis[v]&&ind[v]<k)vis[v]=1,q.push(v);
			if(1LL*k*k<=2*m&&ind[v]==k-1)
			{
				if(check(v,xx))
				{
					printf("2\n");
					for(auto x:s[v])printf("%d ",x);
					printf("%d\n",v);
					return ;
				}
			}
		}
		s[u].clear();
	}
	bool ok=0;
	FOR(i,1,n)
	{
		if(!vis[i])
		{
			ok=1;
			dfs(i);
			break;
		}
	}
	if(ok)
	{
		printf("1 %d\n",sz(ans));
		for(auto x:ans)printf("%d ",x);
		printf("\n");
		return ;
	}
	printf("-1\n");
}
int main()
{
	T=gi();
	FOR(i,1,T)
	{	
		init();
		input();
		solve(i);
	}
	return 0;
}
```



---

## 作者：沉石鱼惊旋 (赞：0)

# 题目翻译

给定 $n$ 个点 $m$ 条边的无向图，给定 $k$，求一个非空点集 $S$ 满足对于所有 $S$ 中的点 $u$，$u$ 在 $S$ 中的邻居个数 $\geq k$，**或者**一个大小为 $k$ 的团。

无解输出 $-1$。

多测。$1\leq T\leq 10^5$，$1\leq n,m,\sum n,\sum m\leq 10^5$，$1\leq k\leq n$。

# 题目思路

首先 $deg \lt k-1$ 的点肯定都没用。直接类似拓扑排序的操作删掉即可。

如果图中的团最大为 $k$，那么团中至少有一个 $deg=k-1$ 的点。否则的话这个团不是最大的，本题中我们就可以通过第 1 类构造来构造出答案。

我们每次找到一个 $deg=k-1$ 的点，暴力找到他的所有邻居，再判断构不构成团。单次复杂度 $\mathcal O(k^2)$，据实现可能多带个 $\log$。

如果不构成团，我们删掉这个点，还是类似拓扑排序找到下一个 $deg=k-1$ 的点。直至我们找不到这样的点。

找不到之后，如果剩下的除了被删掉的点，都是 $deg\geq k$ 的，直接把剩下的点用第 1 类构造当答案。

否则的话，即为无解。

分析一下复杂度，首先在 $k(k-1)\gt 2m$ 的时候一定不构成团。所以如果需要找团，一定有 $k=\mathcal O(\sqrt m)$。

那么像这样需要被拉出来判团的点只有 $\mathcal O(m/k)$ 个。一次复杂度 $\mathcal O(k^2\log m)$，总复杂度 $\mathcal O(m\sqrt m\log m)$。而判 $deg \geq k$ 是线性的，不是复杂度瓶颈。故这种做法复杂度就是 $\mathcal O(m\sqrt m\log m)$，实现精细可以通过。

我因为实现太丑被卡了一发常。避免使用 `std::set` 或 `std::unordered_set` 存图。存图的时候用 `std::vector` 存，然后删点打删除标记，判断是否为邻居用 `std::binary_search`。这样常数很小，改完之后快了三倍。

# 完整代码

<https://codeforces.com/contest/1439/submission/306185838>

```cpp
#include <bits/stdc++.h>
using namespace std;
#define getchar() p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++
char buf[1000000], *p1 = buf, *p2 = buf;
template <typename T>
void read(T &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        if (c == '-')
            f = -f;
    for (; c >= '0' && c <= '9'; c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
template <typename T, typename... Args>
void read(T &x, Args &...y)
{
    read(x);
    read(y...);
}
template <class T>
void write(T x)
{
    static int stk[30];
    if (x < 0)
        putchar('-'), x = -x;
    int top = 0;
    do
    {
        stk[top++] = x % 10, x /= 10;
    } while (x);
    while (top)
        putchar(stk[--top] + '0');
}
template <class T>
void write(T x, char lastChar) { write(x), putchar(lastChar); }
void solve()
{
    int n, m, k;
    read(n, m, k);
    vector<int> a[n + 1];
    int deg[n + 1] = {};
    bool del[n + 1] = {};
    while (m--)
    {
        int u, v;
        read(u, v);
        a[u].emplace_back(v);
        a[v].emplace_back(u);
        deg[u]++, deg[v]++;
    }
    queue<int> q;
    for (int i = 1; i <= n; i++)
    {
        sort(a[i].begin(), a[i].end());
        if (deg[i] < k - 1)
            q.push(i);
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        for (int v : a[u])
        {
            if (del[v])
                continue;
            if (deg[v]-- == k - 1)
                q.push(v);
        }
        a[u].clear();
        deg[u] = 0;
        del[u] = 1;
    }
    int totdeg = 0;
    for (int i = 1; i <= n; i++)
        totdeg += deg[i];
    if (totdeg < 1LL * k * (k - 1))
        return write(-1, '\n'), void();
    for (int i = 1; i <= n; i++)
    {
        if (!del[i] && deg[i] == k - 1)
            q.push(i);
    }
    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (del[u])
            continue;
        if (deg[u] != k - 1)
        {
            for (int v : a[u])
            {
                if (del[v])
                    continue;
                if (--deg[v] == k - 1)
                    q.push(v);
            }
            a[u].clear();
            deg[u] = 0;
            del[u] = 1;
            continue;
        }
        vector<int> vec;
        vec.emplace_back(u);
        for (int v : a[u])
        {
            if (!del[v])
                vec.emplace_back(v);
        }
        bool f = 1;
        for (int i : vec)
        {
            for (int j : vec)
            {
                if (i == j)
                    continue;
                if (!binary_search(a[i].begin(), a[i].end(), j))
                {
                    f = 0;
                    break;
                }
            }
            if (!f)
                break;
        }
        if (f)
        {
            write(2, '\n');
            for (int i : vec)
                write(i, ' ');
            putchar('\n');
            return;
        }
        for (int v : a[u])
        {
            if (del[v])
                continue;
            if (--deg[v] == k - 1)
                q.push(v);
        }
        a[u].clear();
        deg[u] = 0;
        del[u] = 1;
    }
    bool f = 0;
    for (int i = 1; i <= n; i++)
        f |= deg[i];
    for (int i = 1; i <= n; i++)
    {
        if (!del[i])
            f &= deg[i] >= k;
    }
    if (f)
    {
        vector<int> vec;
        for (int i = 1; i <= n; i++)
        {
            if (!del[i])
                vec.emplace_back(i);
        }
        write(1, ' ');
        write(vec.size(), '\n');
        for (int i : vec)
            write(i, ' ');
        putchar('\n');
        return;
    }
    write(-1, '\n');
}
int main()
{
    int t;
    read(t);
    while (t--)
        solve();
    return 0;
}
```

---

## 作者：Purslane (赞：0)

# Solution

只需要做一些必要条件转化就能做出来。

考虑删掉所有度数 $< k-1$ 的点，因为在两种构造中都不会用到。

如果所有点度数都 $\ge k$，则给问题 $2$ 一个构造。

否则，考虑一个度数为 $k-1$ 的点，判断与它相邻的 $k-1$ 个点是否两两有连边。如果没有，将这个 $k-1$ 度数的点删掉，并重复执行删点、判断的流程。

判断的总复杂度为 $O(m k \log m)$（只有在删掉一条边时才会进行 $O(k)$ 次检查边是否存在的操作）

注意到如果 $k > \sqrt{2m} +C$（$C$ 是无关紧要的常数），一定无解，不会进行团的判断。所以复杂度为 $O(m \sqrt m \log m)$。

---

