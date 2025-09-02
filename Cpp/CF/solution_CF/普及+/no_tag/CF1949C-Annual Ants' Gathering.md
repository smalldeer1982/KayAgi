# Annual Ants' Gathering

## 题目描述

### 题面描述

给定一棵 $n$ 个点的树，每个点的初始点权为 1。你可以将一个点 $u$ 的点权转到点 $v$ 当且仅当 $u$ 的点权小于等于 $v$ 的点权。问是否可以通过若干次操作使一个点的点权为 $n$，即将所有点的点权集中在一个点上。

## 样例 #1

### 输入

```
7
5 1
3 2
4 6
3 6
7 1
1 3```

### 输出

```
YES```

## 样例 #2

### 输入

```
5
1 4
4 2
3 2
5 3```

### 输出

```
NO```

## 样例 #3

### 输入

```
6
4 5
5 6
6 1
2 6
3 2```

### 输出

```
YES```

# 题解

## 作者：znszns (赞：5)

考虑合并之后那些非空节点之间的状态，它们是相互连通的，不然的话最后是不可能合并到一个点的。

所以我们每次向其它节点移动的的节点，与它相连的节点必然只有一个点还有权值。

我们也可以把合并权值理解为删点，每次只能删除度数为 1 的点。

那当前剩下的点在什么情况下是不合法的，剩下的点中权值最小的点为 $u$，与它相连的点是 $v$，如果 `val[u]>val[v]`，那就不行，因为 $v$ 连最小的节点都合并不了，就更合并不了其它的点，它的值就永远不会比 $u$ 的值大，最后就合并不了。

至于实现就可以用一个堆来维护度数为 1 的节点的权值及编号，每次取出最小的，将它删去后，如果与它相连的点度数也变为了 1，就加到堆里。

```cpp
#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
typedef pair<int,int> pii;
const int N=2e5+10;
inline int read()
{
	int res=0;
	char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) res=(res<<1)+(res<<3)+c-'0',c=getchar();
	return res;
}
int n,h[N],e[N<<1],ne[N<<1],idx,val[N],d[N];
bool st[N];//表示节点有没有被删去，true 表示被删了
priority_queue<pii,vector<pii>,greater<pii> > q;
void add(int a,int b)
{
	idx++,e[idx]=b,ne[idx]=h[a],h[a]=idx;
}
int main()
{
	n=read();
	int u,v;
	for(int i=1;i<=n;i++) h[i]=-1,val[i]=1;
	for(int i=1;i<n;i++) u=read(),v=read(),add(u,v),add(v,u),d[u]++,d[v]++;
	for(int i=1;i<=n;i++) if(d[i]==1) q.push({val[i],i});
	for(int i=1;i<n;i++)
	{
		u=q.top().se;
		q.pop();
		st[u]=1;
		for(int j=h[u];~j;j=ne[j]) if(!st[e[j]]) v=e[j];//找到与它相连的中还没被删去的那个点
		if(val[v]<val[u]) return puts("NO");// 如果不能合并直接输出 NO，并结束
		val[v]+=val[u];
		d[v]--;
		if(d[v]==1) q.push({val[v],v});//删了之后，相连的点度数为 1 就加到堆里
	}
	puts("YES");
	return 0;
}
```

---

## 作者：江户川·萝卜 (赞：4)

记 $a_u$ 为 $u$ 上的蚂蚁数。

当 $u$ 周围只有 $a_v>0$ 时，才能从 $u$ 搬家到 $v$。

> 否则无蚂蚁的点无法被搬家，有蚂蚁的点不连通。

也即可以将操作视作删叶子，删到只剩一个点。

首先，每次删能删的点肯定优。

> 若不删，则父节点永远无法成为叶子节点（除非只剩两个点，两点时显然删该点更优）
>
> 若先删去，则父节点的 $a$ 更大，更容易吞并叶子。

发现每次删 $a_i$ 最小的叶子即可。

> 若 $a_i$ 最小的叶子不能删，则其父亲节点也无法吞并其他叶子，父节点的度数就无法 $<2$，则无法只剩一个点。

```cpp
#include<bits/stdc++.h>
using namespace std;
constexpr int maxn=2e5+5;
int n;unordered_set<int> e[maxn];
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
int sz[maxn];
int main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    cin>>n;for(int i=1,u,v;i<n;i++) cin>>u>>v,e[u].insert(v),e[v].insert(u);
    for(int i=1;i<=n;i++) sz[i]=1;
    priority_queue<pii,vector<pii>,greater<pii> > q;for(int i=1;i<=n;i++) if(e[i].size()==1) q.push(mp(1,i));
    for(int i=1;i<n;i++){
        int p=q.top().se;q.pop();int to=*e[p].begin();
        if(sz[p]>sz[to]) return puts("NO"),0;
        sz[to]+=sz[p];e[to].erase(p);
        if(e[to].size()==1) q.push(mp(sz[to],to));
    }
    puts("YES");
}
```

---

## 作者：Day_Tao (赞：3)

### 题目大意

给定一棵 $n$ 个点的树，每个点的初始点权为 1。你可以将一个点 $u$ 的点权转到点 $v$ 当且仅当 $u$ 的点权小于等于 $v$ 的点权。问是否可以通过若干次操作使一个点的点权为 $n$，即将所有点的点权集中在一个点上。

### Sol

因为所有的点最终要汇聚到一起，所以这棵树的子节点一定要尽量向它的父亲节点转移。这时就可以想到将所有子节点都塞到一个队列里面，用这些子节点去更新父亲节点，更新的条件是 $val_{son}\le val_{father}$，假如更新不了就塞到队尾，因为在前面的更新中可能改变这个点的父亲节点大小，从而使得父亲节点可以被这个子节点更新。当然，如果这个队列里一直保存着相同的数，无法更新，就代表肯定行不通。详细的解析见代码部分啦。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAX = 2e5 + 1;
const int INF = 0x7fffffff;
const int mod = 998244353;
int n, cnt; // cnt 表示删掉点的数量
int f[MAX], node[MAX];
// f[i] 存的是点 i 对外的连边边数，node[i]存的是点 i 的点权
bool vis[MAX];      // 记录哪些点已经被访问过了
vector<int> a[MAX]; // 存边
queue<int> q;
inline void bfs()
{
    int cntt = 0;
    while (!q.empty())
    {
        cntt++;
        if (cntt >= n * 2)
            puts("NO"), exit(0); // 循环次数大于 2n 就表示进入循环情况了，直接退出
        if (cnt == n - 2)
            puts("YES"), exit(0); // 还剩最后 2 个点时显然是成立的，也直接退出
        int u = q.front();
        q.pop();
        bool fl = 0;
        for (auto v : a[u])
            if (!vis[v] && node[v] >= node[u]) // 可以更新的父节点
            {
                vis[u] = 1, node[v] += node[u], f[v]--, f[u]--, fl = 1, cnt++; // 更新操作
                if (f[v] == 1)
                    q.push(v); // 在 v 是子节点时加入队列
                break;
            }
        if (!fl)
            q.push(u); // 不能更新的话把该点加入队尾
    }
}
int main()
{
    scanf("%d", &n);
    if (n == 1) // 记得判这种情况，不然会 WA on test 4
    {
        puts("YES");
        return 0;
    }
    int u, v;
    for (int i = 1; i < n; i++)
    {
        scanf("%d%d", &u, &v), f[u]++, f[v]++;
        node[i] = 1, a[v].push_back(u), a[u].push_back(v);
    }
    node[n] = 1;
    for (int i = 1; i <= n; i++)
        if (f[i] == 1)
            q.push(i); // 将叶子节点加入队列
    bfs();
    return 0;
}
```

---
### END

---

## 作者：tbdsh (赞：0)

# 题意简述
[洛谷题目传送门](/problem/cf1949c)

[CodeForces 题目传送门](//codeforces.com/contest/1949/problem/c)

[更好的阅读体验](/article/d35r0oz5/)


给定一棵树，每个点初始点权均为 $val_x=1$。若 $v$ 是 $u$ 的儿子，且 $val_v\le val_u$，那么 $v$ 的点权可以被转移至 $u$，即 $val_u\gets val_u+val_v,val_v\gets 0$。

问是否能够通过若干次转移，使得 $\exists u\in[1,n]\ val_u=n$。

# 分析
首先给出结论：如果有解，那么满足条件的 $x$ 一定是这颗树的重心。

考虑反证法：

设点 $x$ 不是树的重心。

由于树的重心的最大子树大小不超过 $\left\lfloor\dfrac{2}{n}\right\rfloor$，所以点 $x$ 的最大子树大小超过 $\left\lfloor\dfrac{2}{n}\right\rfloor$。那么在将 $x$ 的其它子树合并上来后，$x$ 的权值小于 $\left\lfloor\dfrac{2}{n}\right\rfloor$，最后的子树大小大于等于 $\left\lfloor\dfrac{2}{n}\right\rfloor$，无法完成转移。

即 $x$ 不是树的重心时一定无法完成合并，原结论成立。

那么我们就只需要求出树的重心，随后以重心为根，把边模拟一遍整个过程看能否完成转移即可。

考虑模拟的过程中如何完成判断。

显然优先合并权值小的点是更优的，那么我们就对所有边按照连接的点的子树大小排序，然后从根开始挨个判断即可。

时间复杂度：$O(n\log n)$，瓶颈是对边排序。

# Code
```cpp
#include<bits/stdc++.h>

using namespace std;
const int MAXN = 2e5 + 5;
int n, sz[MAXN], dis[MAXN], p;
vector<int> g[MAXN];
void dfs1(int x, int fa){
  sz[x] = 1;
  for (auto v : g[x]){
    if (v != fa){
      dfs1(v, x);
      sz[x] += sz[v];
      dis[x] = max(dis[x], sz[v]);
    }
  }
  dis[x] = max(dis[x], n - sz[x]);
  if (dis[x] <= n / 2){
    p = x;
  }
}
void dfs2(int x, int fa){
  int t = 1;
  for (auto v : g[x]){
    if (v == fa){
      continue;
    }
    if (sz[v] > t){
      cout << "NO";
      exit(0);
    }
    dfs2(v, x);
    t += sz[v];
  }
}
bool cmp(int x, int y){
  return sz[x] < sz[y];
}
signed main(){
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1, u, v; i < n; i++){
    cin >> u >> v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs1(1, 0);
  dfs1(p, 0);
  for (int i = 1; i <= n; i++){
    sort(g[i].begin(), g[i].end(), cmp);
  }
  dfs2(p, 0);
  cout << "YES";
  return 0;
}
```

---

## 作者：jiazhichen844 (赞：0)

太逆天了……

### $n\le 1000$

先思考如果确定了最后点权为 $n$ 的点怎么做，记这个点为 $rt$，以 $rt$ 为根。

首先求出每个点的子树大小 $sz$。

对于 $u$ 点的儿子 $v$，令 $v$ 的权值为 $sz_v$，考虑此时 $u$ 的儿子里的权值能否汇集到 $u$。如果能，记 $g_u=1$，否则，$g_u=0$

令 $f_u$ 为 $u$ 子树内 $g_u$ 的和，有 $f_u=g_u+\sum\limits_{v\in son_u}f_v$

考虑 $g_u$ 的求法，其本质上就是要给儿子排序成 $p_1,p_2,\cdots,p_k$，满足 $\forall i\in\{1,2,\cdots,k\},sz_{p_i}\le\sum\limits_{j=1}^{i-1} sz_{p_j}+1$

使用邻项交换法，容易发现需要按 $sz$ 从小到大排序，如果符合上述条件，则 $g_u=1$

最后 $rt$ 合法当且仅当 $f_{rt}=n$

于是 $O(n\log n)$ 可以判断**一个** $rt$ 是否合法。

但是，我们并不知道最后汇集的点，于是还要枚举 $rt$，然后时间就退化到了 $O(n^2\log n)$……

### $n\le 2\times10^5$

考虑换根 dp

$fa_u$ 代表 $u$ 在以 $1$ 为根意义上的父亲

$sz$ 换根是容易的。

如果我们可以快速求出 $g$，那么 $f$ 换根也是容易的。

考虑 $g$ 如何换根。

注意到，如果根是从 $fa$ 换到 $u$，那么变化的只有 $g_{fa}$ 和 $g_u$

如果我们重新暴力求 $g_u$ 与 $g_{fa}$，时间就变成了 $O(n^2)$（PS：菊花图）

但是如果我们只是暴力求新的 $g_u$，时间并不会超，因为每个 $u$ 只会算一次。

所以我们只要快速求出新的 $g_{fa}$ 即可。

我们将以 $1$ 为根时 $x$ 的儿子的 $sz$ 集合称为 $S_{1,x}$，将以 $x$ 为根时 $x$ 的儿子集合称为 $S_{2,x}$，将以 $x$ 为根时 $fa_x$ 的儿子集合称为 $S_{3,x}$

我们有 $S_{3,u}=S_{2,fa_u}\backslash\{u\}$

令 $check(S)$ 为“如果一个点 $y$ 的儿子的 $sz$ 集合为 $S$，$g_y$ 的值“

我们要快速求出每个 $check(S_{3,u})$

对于某个固定的 $fa_u$，$S_{3,u}$ 只会是 $S_{2,fa_u}$ 每次删一个数

这启发我们对于每个 $fa_u$ 考虑。

首先，将儿子按 $sz$ 排序，设此时序列为 $p$，然后预处理 $\Delta_i=sz_{p_i}-\sum\limits_{j=1}^{i-1} sz_{p_j}$

同时，处理 $pre_i=\max\limits_{j=1}^i\Delta_j,suf_i=\max\limits_{j=i}^k\Delta_j$（$k$ 为儿子个数）

当删掉 $p_k$ 时，相当于 $\Delta_x(x<k)$ 不变，$\Delta_y(y>k)$ 增加 $sz_{p_k}$，此时只需要查询 $pre_{k-1},suf_{k+1}+sz_{p_k}$ 并比较和 $0$ 的大小关系即可。

时间复杂度 $O(n\log n)$

### code

submission：https://codeforces.com/contest/1949/submission/284528764 （用第 $3$ 个小号交的）

```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int> e[200005];
int sz[200005];
int f[200005];
int g[200005];
int ansr[200005],gr[200005];
int n;
int rk[200005];
multiset<int>::iterator iter[200005];
vector<int> suf[200005],pre[200005];
multiset<int> st[200005];
int get(multiset<int> st)
{
	int s=1;
	for(int x:st)
	{
		if(s<x)
			return 0;
		s+=x;
	}
	return 1;
}
bool cmp(int a,int b)
{
	return sz[a]<sz[b];
}
void dfs_pre(int pos,int fa)
{
	sz[pos]=1;
	f[pos]=0,g[pos]=1;
	for(int x:e[pos])
	{
		if(x==fa)
			continue;
		dfs_pre(x,pos);
		st[pos].insert(sz[x]);
		sz[pos]+=sz[x];
		f[pos]+=f[x]; 
	}
	sort(e[pos].begin(),e[pos].end(),cmp);
	g[pos]=get(st[pos]);
	f[pos]+=g[pos];
}
void work(int pos)
{
	int s=1;
	for(int x:st[pos])
	{
		pre[pos].push_back(x-s);
		suf[pos].push_back(x-s);
		s+=x;
	}
	if(pre[pos].size()<2)
		return;
	for(int i=1;i<pre[pos].size();i++)
		pre[pos][i]=max(pre[pos][i],pre[pos][i-1]);
	for(int i=suf[pos].size()-2;i>=0;i--)
		suf[pos][i]=max(suf[pos][i],suf[pos][i+1]);
}
void dfs(int pos,int fa)
{
	if(fa)
	{
		int ffa=ansr[fa]-gr[fa];
		ffa-=f[pos];
		int szfa=n-sz[pos];
		while(iter[fa]!=st[fa].end()&&*iter[fa]!=sz[pos])
			iter[fa]++,rk[fa]++;
		int gfa=1;
		if(rk[fa]-1>=0&&pre[fa][rk[fa]-1]>0)
			gfa=0;
		if(rk[fa]+1<pre[fa].size()&&suf[fa][rk[fa]+1]>-sz[pos])
			gfa=0;
		ffa+=gfa;
		ansr[pos]=f[pos]-g[pos]+ffa;
		st[pos].insert(szfa);
		work(pos);
		rk[pos]=0;
		iter[pos]=st[pos].begin();
		gr[pos]=get(st[pos]);
		ansr[pos]+=gr[pos];
	}
	for(int x:e[pos])
	{
		if(x==fa)
			continue;
		dfs(x,pos);
	}
}
int main()
{
	cin>>n;
	for(int i=1;i<n;i++)
	{
		int u,v;
		cin>>u>>v;
		e[u].push_back(v);
		e[v].push_back(u);
	}
	dfs_pre(1,0);
	ansr[1]=f[1];
	gr[1]=g[1];
	work(1);
	rk[1]=0;
	iter[1]=st[1].begin();
	dfs(1,0);
	for(int i=1;i<=n;i++)
	{
		if(ansr[i]==n&&gr[i])
		{
			cout<<"YES";
			return 0;
		}
	}
	cout<<"NO";
}
```

---

