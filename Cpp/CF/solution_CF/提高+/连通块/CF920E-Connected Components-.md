# Connected Components?

## 题目描述

You are given an undirected graph consisting of $ n $ vertices and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF920E/2671f3d87e6b285ebb30abeafea800e65bb56d51.png) edges. Instead of giving you the edges that exist in the graph, we give you $ m $ unordered pairs ( $ x,y $ ) such that there is no edge between $ x $ and $ y $ , and if some pair of vertices is not listed in the input, then there is an edge between these vertices.

You have to find the number of connected components in the graph and the size of each component. A connected component is a set of vertices $ X $ such that for every two vertices from this set there exists at least one path in the graph connecting these vertices, but adding any other vertex to $ X $ violates this rule.

## 样例 #1

### 输入

```
5 5
1 2
3 4
3 2
4 2
2 5
```

### 输出

```
2
1 4 ```

# 题解

## 作者：142857cs (赞：32)

删去的边数只有m条，所以至少存在一个点，删去的与它连接的边的条数不超过m/n。

找出这个点，然后找出所有与这个点有边相邻的点，将它们合并成一个连通块。

显然，连通块内部的边不用考虑，需要考虑的边一定与连通块外的某个点相连。

连通块外最多只有m/n个点，每个点最多与n条边相连，所以这样的边最多只有m条，暴力即可

```cpp
#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
int head[262144],last[524288],to[524288],cnt=0;
int fa[262144];
int deg[262144];
bool vis[262144];
bool vis2[262144];
int sb[262144];
int sz[262144];
void add(int u,int v)
{
    cnt++;
    last[cnt]=head[u];
    head[u]=cnt;
    to[cnt]=v;
    deg[v]++;
}
int findroot(int x)
{
    if(fa[x]==x)
    {
        return x;
    }
    return fa[x]=findroot(fa[x]);
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        fa[i]=i;
    }
    while(m--)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    int u=0,md=n;
    for(int i=1;i<=n;i++)
    {
        if(deg[i]<md)
        {
            md=deg[i];
            u=i;
        }
    }
    for(int i=head[u];i;i=last[i])
    {
        vis[to[i]]=true;
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            fa[i]=u;
        }
    }
    for(int i=1;i<=n;i++)
    {
        if(!vis[i])
        {
            continue;
        }
        memset(vis2,0,sizeof(vis2));
        int x=findroot(i);
        for(int j=head[i];j;j=last[j])
        {
            vis2[to[j]]=true;
        }
        for(int j=1;j<=n;j++)
        {
            if(vis2[j])
            {
                continue;
            }
            int y=findroot(j);
            fa[y]=x;
        }
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(fa[i]==i)
        {
            sb[i]=ans;
            ans++;
        }
    }
    for(int i=1;i<=n;i++)
    {
        sz[sb[findroot(i)]]++;
    }
    sort(sz,sz+ans);
    printf("%d\n",ans);
    for(int i=0;i<ans;i++)
    {
        printf("%d",sz[i]);
        if(i==ans-1)
        {
            putchar('\n');
        }
        else
        {
            putchar(' ');
        }
    }
    return 0;
}
```

---

## 作者：zzqDeco (赞：18)

这里提供一种不同的做法

考虑到我们边很多，就不能够每次拓展的时候枚举每一个点，去判断是否和当前点有边

那么我们从删去的边很少的角度来考虑，把求连通块看作染色拓展

当我们以某一个颜色染色的时候，他肯定只可能向还没染色的点染色，不然如果可以染已经染过色的点，这个点在之前就已经被其他店染色了

我们用一个 `vector` 来存储还没有被染色的点，每有一个点被染色我们就把他从里面去除，因为他不再可能再被染色

每次bfs扫 `vector` 就行了

为啥这样 `bfs` 复杂度是对的?

考虑到我们每个点都只会被拿来bfs一次，这里的复杂度是 $O(n)$ ，那么主要考虑的是我们每个点出入 `vector` 的次数

我们每有一个删去的边的时候，才会使得这个点再次进入 `vector` ，显然这个和删边数量有关，整体复杂度就是 $O(n+m)$

```cpp
#include <cstdio>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

unordered_set <int>mp[200010];

queue <int>vec;

int n,m,cnt;

int ans[200010];

bool vis[200010];

void bfs(int x,int cnt)
{
  queue <int>q;
  q.push(x);
  while(!q.empty())
  {
    int x=q.front(),nowsize=vec.size();
    q.pop();
    for(int i=1;i<=nowsize;i++)
    {
      int now=vec.front();
      vec.pop();
      if(vis[now]) continue ;
      if(mp[x].find(now)!=mp[x].end()||mp[now].find(x)!=mp[now].end()) vec.push(now);
      else ans[cnt]++,q.push(now),vis[now]=1;
    }
  }
}

int main()
{
  scanf("%d%d",&n,&m);
  for(int i=1;i<=m;i++)
  {
    int a,b;
    scanf("%d%d",&a,&b);
    mp[a].insert(b);
  }
  for(int i=1;i<=n;i++) vec.push(i);
  for(int i=1;i<=n;i++)
  {
    if(!vis[i])
    {
      vis[i]=1;
      bfs(i,++cnt);
    }
  }
  sort(ans+1,ans+cnt+1);
  printf("%d\n",cnt);
  for(int i=1;i<=cnt;i++) printf("%d ",ans[i]+1);
}
```

---

## 作者：RedreamMer (赞：12)

[$\Large\texttt{CF920E}$](https://www.luogu.com.cn/problem/CF920E)

[$\small\texttt{In my blog}$](https://www.cnblogs.com/RedreamMer/p/13473388.html)

思路：并查集、~~暴力~~

思路和大家都差不多，但是想给一个细致一点的证明。

$\large\texttt{Meaning}$

给你一张 $N$ 个点 $M$ 条边的图，求这个图的补图的连通块个数以及每个连通块的大小。

$\large\texttt{Solution}$

在这个图中选一个度数最小的点 $n$，和它连通（指补图）的点个数一定是所有点中最多的，将它们并在一起，然后对剩下没联通的点暴力操作，寻找连通块并合并。

虽然是暴力，但是它的复杂度也不是很大。

$\large\texttt{Prove}$

首先这样先选一个度最小的点先做联通操作肯定是其他方案中最优的，因为与它联通的点一定是最多的，省去了不必要的考虑。

令点数为 $n$，边数为 $m$。

先暴力枚举出那个度最小的点，它**最坏情况最多**有 $\frac{m}{n}$ 条边连接 $\frac{m}{n}$ 个点，那么剩下的$n-\frac{m}{n}$ 个点是不用考虑的，因为都在一个连通块里面，考虑这 $\frac{m}{n}$ 个点,而我们枚举这些点的出边，共 $m-\frac{m}{n}$ 条，显然可过。

对每一个不与第一个联通的点，还要枚举一遍所有的点，复杂度为 $\frac{m}{n}\times n = m$ 显然可过。 

复杂度为 $O(n+m)$（最坏情况）。

$\large\texttt{Code}$

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PB push_back
const int N = 200000;
inline int read()
{
    register int s = 0;
    register bool neg = 0;
    register char c = getchar();
    for (; c < '0' || c > '9'; c = getchar())
        neg |= (c == '-');
    for (; c >= '0' && c <= '9'; s = s * 10 + (c ^ 48), c = getchar())
        ;
    return (neg ? -s : s);
}

int a, b, in[N + 10], fa[N + 10], scc, bel[N + 10], siz[N + 10];
bool vis[N + 10], vis1[N + 10];
vector<int> st[N + 10];

inline int f(int n)//并查集模板
{
    return fa[n] == n ? n : fa[n] = f(fa[n]);
}

signed main()
{
    a = read();
    b = read();
    int x, y;
    for (int i = 1; i <= b; i++)
    {
        x = read();
        y = read();
        st[x].PB(y);
        st[y].PB(x);
        in[x]++;
        in[y]++;
    }
    int mx = 1;
    for (int i = 1; i <= a; i++)
        fa[i] = i;
    for (int i = 2; i <= a; i++)
        if (in[i] < in[mx])//找到度最小的点
            mx = i;
    for (int i = 0; i < st[mx].size(); i++)
        vis[st[mx][i]] = 1;
    for (int i = 1; i <= a; i++)
        if (!vis[i])
            fa[i] = mx;
    for (int i = 1; i <= a; i++)
    {
        if (!vis[i] || i == mx)//对其他没有联通的点进行合并操作
            continue;
        memset(vis1, 0, sizeof(vis1));
        int f1 = f(i);
        for (int j = 0; j < st[i].size(); j++)
            vis1[st[i][j]] = 1;
        for (int j = 1; j <= a; j++)//暴力合并（（（并非
            if (!vis1[j])
                fa[f(j)] = f1;
    }
    for (int i = 1; i <= a; i++)
        if (fa[i] == i)
            bel[i] = ++scc;
    for (int i = 1; i <= a; i++)
        siz[bel[f(i)]]++;
    sort(siz + 1, siz + scc + 1);
    printf("%d\n", scc);
    for (int i = 1; i <= scc; i++)
        printf("%d ", siz[i]);
    return 0;
}
```

---

## 作者：Great_Influence (赞：5)

开set记录还没被访问的点，在对每个点都开1个set记录被删的边。然后一遍扫，用bfs强行搜出联通块。最后记得给答案排序。

代码：

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(i=(a);i<=(b);++i)
#define Forward(i,a,b) for(i=(a);i>=(b);--i)
#define Rep(i,a,b) for(register int i=(a),i##end=(b);i<=i##end;++i)
#define Repe(i,a,b) for(register int i=(a),i##end=(b);i>=i##end;--i)
using namespace std;
template<typename T>inline void read(T &x){
	T s=0,f=1;char k=getchar();
	while(!isdigit(k)&&k^'-')k=getchar();
	if(!isdigit(k)){f=-1;k=getchar();}
	while(isdigit(k)){s=s*10+(k^48);k=getchar();}
	x=s*f;
}
void file(void){
	#ifndef ONLINE_JUDGE
	freopen("water.in","r",stdin);
	freopen("water.out","w",stdout);
	#endif
}
const int MAXN=2e5+7;
#define Chkmax(a,b) a=a>b?a:b
static int n,m;
static set<int>K;
static set<int>G[MAXN];
inline void init()
{
    read(n);read(m);
    static int u,v;
    Rep(i,1,n)K.insert(i);
    Rep(i,1,m)read(u),read(v),G[u].insert(v),G[v].insert(u);
}
static set<int>::iterator it,del;
static int top,ans[MAXN];
static queue<int>R;
int bfs(int x)
{
    static int u,sz,z;sz=0;
    R.push(x);
    while(!R.empty())
    {
        u=R.front();R.pop();++sz;
        for(it=K.begin();it!=K.end();)if(!G[u].count(z=*it))
        {
            R.push(z);del=it;
            ++it;K.erase(del);
        }else ++it;
    }
    return sz;
}
inline void solve()
{
    static int u;
    while(!K.empty())
    {
        u=*K.begin();K.erase(K.begin());
        ans[++top]=bfs(u);
    }
    sort(ans+1,ans+top+1);
    printf("%d\n",top);
    Rep(i,1,top)printf("%d ",ans[i]);puts("");
}
int main(void){
	file();
    init();
    solve();
	return 0;
}

```

---

## 作者：intel_core (赞：4)

没见过就不会系列。。

根据抽屉原理，存在一个点被删掉的边不超过 $\lfloor \frac{2m}{n} \rfloor$ 条。

也就是说，这个点所在的连通块内几乎包含了所有的点。

把剩下的点取出来并查集暴力即可。

复杂度 $O(n+\frac{m^2}{n^2})$，因为 $m\le n^2$ 所以可以理解为 $O(m+n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int NR=2e5+10;
const int MR=610;
int n,m,cnt[NR],x[NR],y[NR],flag[NR],buc[NR];
bool lcy[MR][NR];
int idx[NR],rnk[NR],tot;

int fa[NR],pos=0,minn=1e9;
void init(){
	for(int i=1;i<=n;i++)
		if(flag[i])fa[i]=i;
		else fa[i]=pos;
}
int get(int x){
	if(fa[x]==x)return x;
	return fa[x]=get(fa[x]);
}
void merge(int x,int y){
	x=get(x);y=get(y);
	if(x==y)return;
	fa[x]=y;
}
priority_queue<int,vector<int>,greater<int> >q;

int main(){
	cin>>n>>m;
	for(int i=1;i<=m;i++)
		scanf("%d%d",&x[i],&y[i]),cnt[x[i]]++,cnt[y[i]]++;
	for(int i=1;i<=n;i++)
		if(minn>cnt[i])minn=cnt[i],pos=i;
	for(int i=1;i<=m;i++){
		if(x[i]==pos)flag[y[i]]=1;
		if(y[i]==pos)flag[x[i]]=1;
	}
	init();
	for(int i=1;i<=n;i++)
		if(flag[i])idx[++tot]=i,rnk[i]=tot;
	for(int i=1;i<=m;i++){
		if(flag[x[i]])lcy[rnk[x[i]]][y[i]]=1;
		if(flag[y[i]])lcy[rnk[y[i]]][x[i]]=1;
	}
	for(int i=1;i<=tot;i++)
		for(int j=1;j<=n;j++)
			if(!lcy[i][j])merge(idx[i],j);
	for(int i=1;i<=n;i++)buc[get(i)]++;
	for(int i=1;i<=n;i++)
		if(buc[i])q.push(buc[i]);
	cout<<q.size()<<endl;
	while(!q.empty())printf("%d ",q.top()),q.pop();
	return 0;
}
```

---

## 作者：Daidly (赞：3)

- $n$ 个点 $m$ 条边的无向图，求其补图的每个联通分量大小。
- $n,m\leq 10^5$

考虑原图与补图的关系：

若原图中 $(u,v)$ 有边，则补图中 $(u,v)$ 无边。

若原图中 $(u,v)$ 无边，则补图中 $(u,v)$ 有边。

形象地说，$(u,v_k)$ 像是隔板把区间 $[1,n]$ 分成许多段，每一段中的点在补图中都与 $u$ 属于同一连通分量。

段内合并，合并多段，可以考虑使用并查集合并区间解决。

但在普通的区间上我们可以将并查集带方向处理，记最右端为根节点，但在图中，方向性难以保证。

观察区间中的另一个性质：连续！

考虑将集合中点的最大编号记为并查集的根节点，则只需保证集合内点编号连续即可。

进行以下操作：

1. 将所有在原图上不与点 $u$ 相连的点组成的连续区间合并；
2. 所有连续区间合并完之后再互相合并以及与 $u$ 合并，保证不出现漏连现象。

![](https://cdn.luogu.com.cn/upload/image_hosting/nrxlgadu.png)

如上图红色边为原图中的连边，而绿色区间便是补图中的同一联通分量的点。

```cpp
#include<bits/stdc++.h>
using namespace std;

inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		x=(x<<1)+(x<<3)+(c^48);
		c=getchar();
	}
	return x*f;
}

const int MAXN=2e5+5;
int n,m,f[MAXN],siz[MAXN],ans[MAXN],num;
vector<int>e[MAXN];
bool vis[MAXN];

void add(int u,int v){
	e[u].push_back(v);
}

void init(){
	for(int i=1;i<=n;++i)f[i]=i,siz[i]=1;
}

int find(int x){
	if(x==f[x])return x;
	return f[x]=find(f[x]);
}

void merge(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx==fy)return;
	if(fx>fy)swap(fx,fy);
	f[fx]=fy,siz[fy]+=siz[fx];
}

void work(int l,int r){
	int fl=find(l),fr;
	for(int i=fl+1;i<=r;++i){
		fr=find(i);
		merge(fl,fr);
		fl=fr;
	}
}

int main(){
	n=read(),m=read();
	init();
	for(int i=1;i<=m;++i){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	for(int i=1;i<=n;++i){
		sort(e[i].begin(),e[i].end());
	}
	int l,r,len,pos;
	for(int i=1;i<=n;++i){
		if(!e[i].size()){
			if(1<i-1)work(1,i-1);
			if(i+1<n)work(i+1,n);
			break;
		}
		l=1,r=e[i][0]-1,len=e[i].size();
		if(l<=i&&i<=r){
			int tmp=r;
			r=i-1;
			if(l<r)work(l,r);
			l=i+1,r=tmp;
		}
		if(l<r)work(l,r);
		for(int j=1;j<len;++j){
			l=e[i][j-1]+1,r=e[i][j]-1;
			if(l<r)work(l,r);
		}
		if(e[i][len-1]==n)l=r=n;
		else l=e[i][len-1]+1,r=n;
		if(l<r)work(l,r);
	}
	for(int i=1;i<=n;++i){
		if(!e[i].size()){
			if(i==n)merge(i,i-1);
			else merge(i,i+1);
			continue;
		}
		if(e[i][0]>1)merge(1,i);
		for(int j=1;j<e[i].size();++j){
			if(e[i][j]-e[i][j-1]>1)merge(i,e[i][j]-1);
		}
	}
	for(int i=1;i<=n;++i){
		int fx=find(i);
		if(!vis[fx]){
			ans[++num]=siz[fx];
			vis[fx]=1;
		}
	}
	cout<<num;puts("");
	sort(ans+1,ans+num+1);
	for(int i=1;i<=num;++i)cout<<ans[i]<<" ";
	return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

考虑直接暴力 dfs。设搜到点 $u$，把 $u$ 打上 tag，然后我们枚举 $v$ 使得 $v$ 没被打上 tag 且边 $(u, v)$ 不存在，搜点 $v$ 即可。复杂度 $O(n^2)$。

发现瓶颈在于寻找没被打上 tag 的点。考虑使用链表，维护还没被打上 tag 的点，搜到 $u$ 时将 $u$ 从链表中删除，再遍历一遍链表即可。

实现时可以用并查集模拟链表。时间复杂度 $O((n + m) \log n)$。

[code](https://codeforces.com/problemset/submission/920/213103244)

---

## 作者：Mickey_snow (赞：2)

[CF920E](http://codeforces.com/contest/920/problem/E) _Connected Components?_ : 链表优化广度优先搜索。

题目大意：给定一张无向图 $G$ , 求 $G$ 的补图的连通块的个数。

这里补图就是完全图 $K$ 去掉所有 $G$ 中的连边，也就是断掉所有原本连着的两个点，连上所有原本没有连接的两个点。记 $G$ 的补图为 $T$ 。如果点 $s$ 和点 $t$ 处于同一个连通块中，那么一定有一条路径可以从 $s$ 到 $t$ ,所有满足上述条件的 $s$ 和 $t$ 点的集合称为一个连通块。

我们先将所有的边读入进来，假定一开始所有的点都不属于任何一个连通块，然后将所有的点扫一遍，如果发现一个点 $s$  不属于任何一个连通块，以 $s$ 为起点广度优先搜索，枚举一下点 $t$ ，如果 $s$ 和 $t$ 在 $G$ 中没有连边，就将 $t$ 加入队列中，与此同时记录一下当前连通块的大小。这么做是正确的，除了这个补图有点非同寻常以外几乎与正常地求连通块没有区别，但是，这么做每一次枚举 $t$ 都要尝试所有可能的点，时间复杂度高达 $O(N^2)$，难以承受。

BFS代码如下，我们可以以这个为模型考虑优化的方案。

```cpp
int _count(const int &start) {
	queue<int> que; que.push(start);
	vis[start] = true;

	int nowAt, _cnt = 1, i;
	while (!que.empty()) {
		nowAt = que.front(); que.pop();
		sort(G[nowAt].begin(), G[nowAt].end());
		for (int to = i = 0; to < totPoints; to++) {
			if (i < G[nowAt].size() && to == G[nowAt][i]) { i++; continue; }
			if (!vis[to]) { vis[to] = true; que.push(to); _cnt++; }
		}
	}
	return _cnt;
}
```

时间超出限制的根本原因就是枚举 $t$ 的时候浪费了大量的计算能力，事实上，大部分的 $t$ 都已经属于其它的连通块了，因此永远不可能用得上，能不能不枚举这些点呢？其实是可以的，如果发现了一个 $t$ 可以加入当前的连通块，我们将其删掉就可以了，这可以用一种数据结构在 $O(1)$ 的时间复杂度内完成这一操作。

套上了链表，我们还可以用一个集合 $S$ 保存图 $G$ 中所有的连边，最后判断一下如果 $s \to t$ 这条边不在集合 $S$ 中，说明这是一个合法的 $t$. 

AC代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;

//链表----------------------------
struct Node {
	int val; Node *nxt;
	void DeleteNext() {	
		if (this->nxt == nullptr)return;
		Node *it = this->nxt; this->nxt = it->nxt;
		it = nullptr;
	}
}*frnt = nullptr;
Node* newNode() {
	Node* ext = (Node*)malloc(sizeof(Node));
	ext->nxt = nullptr; return ext;
}
void build(size_t siz) { //在一开始，所有的点都在链表中
	frnt = newNode(); frnt->val = 0;
	Node *it = frnt, *ext;
	for (int i = 1; i < siz; i++) {
		ext = newNode(); ext->val = i;
		it->nxt = ext; it = ext;
	}
}
//-------------------------------------

#define MAXPOINTS 200005
vector<int> cnt;	//每一个连通块包含的点的个数
int totPoints, totEdges;
bool vis[MAXPOINTS];

struct Edge {
	int fr, to;
	bool operator < (Edge comp) const {
		return fr == comp.fr ? to < comp.to : fr < comp.fr;
	}
};
set<Edge> G;	//图G

int _count(const int &start) {//广搜
	queue<int> que; que.push(start);
	int nowAt, _cnt = 1;

	while (!que.empty()) {
		nowAt = que.front(); que.pop();
		for (Node *it = frnt; it != nullptr && it->nxt != nullptr;) {//我也不知道这里到底循环了多少次
			if (vis[it->nxt->val]) { it->DeleteNext(); continue; }
			if (G.count({ nowAt,it->nxt->val }) || it->nxt->val == nowAt) { it = it->nxt; continue; }
			vis[it->nxt->val] = true; _cnt++;
			que.push(it->nxt->val);
			it->DeleteNext();
		}
	}
	return _cnt;
}

int main()
{
	memset(vis, false, sizeof(vis));
	int a, b;

	cin >> totPoints >> totEdges;
	for (int i = 0; i < totEdges; i++) {
		scanf("%d%d", &a, &b); --a; --b;
		G.insert({ a,b }); G.insert({ b,a });
	}
	build(totPoints);

	for (Node* it = frnt; it != nullptr; it = it->nxt) {
		if (vis[it->val])continue;
		vis[it->val] = true;
		cnt.push_back(_count(it->val));
	}

	cout << cnt.size() << endl;
	sort(cnt.begin(), cnt.end());//输出时要是排好序了的
	for (const auto &it : cnt)
		printf("%d ", it);
	putchar('\n');

	//system("pause");
	return 0;
}
```

 ~~其实，如果去掉链表的部分不看，代码还是非常直观的~~ 

有了链表的优化可以将所有枚举将为 $N$ 次，由于每次判断是否在集合中为 $O(logN)$ ，所以时间复杂度为 ~~O(玄学)~~  $O(NlogN)$ ?

---

## 作者：Felix72 (赞：1)

大家在小学二年级就学过线段树优化建图了，今天我也来个线段树优化并查集。

注意到原题可以转化为一个点向区间连边的问题，也就是合并单点和区间的并查集。我们先建一个线段树出来，每次再以对数复杂度合并单点和线段树上的点。最后我们再从根搜索一遍，如果发现一个树点被合并过，那他们的子树肯定在一个集合里，直接合并即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 400010;
int n, m, add, bel[N], tot, trans[N], mp[N * 4], hve[N];
bool vis[755][755];
struct node {int u, v; long long w;} s[N * 4];
vector < int > con[N];
list < int > q;
int rt, idx, siz[N * 4], prt[N * 4];
inline int find(int x)
{
	if(prt[x] == x) return x;
	prt[x] = find(prt[x]);
	return prt[x];
}
inline void merge(int x, int y)
{
	int u = find(x), v = find(y);
	if(u != v)
	{
		if(siz[u] > siz[v]) swap(u, v);
		prt[u] = v, siz[v] += siz[u], siz[u] = 0;
	}
}
inline bool cmp(node u, node v) {return u.w < v.w;}
struct SGT
{
	struct SGTnode
	{
		int ls, rs, data, tag;
		#define ls(x) tree[x].ls
		#define rs(x) tree[x].rs
		#define data(x) tree[x].data
		#define tag(x) tree[x].tag
	}tree[N * 4];
	inline void build(int &now, int l, int r)
	{
		if(!now) now = ++idx, prt[idx] = idx, siz[idx] = 1;
		if(l == r) {trans[l] = now; return ;}
		int mid = l + r >> 1;
		if(l <= mid) build(ls(now), l, mid);
		if(mid < r) build(rs(now), mid + 1, r);
	}
	inline void insert(int now, int l, int r, int L, int R, int pos)
	{
//		cout << now << " " << l << " " << r << " " << L << " " << R << " " << pos << endl;
		if(L <= l && r <= R) {merge(trans[pos], now); tag(now)++; return ;}
		int mid = l + r >> 1;
		if(L <= mid) insert(ls(now), l, mid, L, R, pos);
		if(mid < R) insert(rs(now), mid + 1, r, L, R, pos);
	}
	inline void floippy(int now, int l, int r, int num)
	{
		num += tag(now);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(l <= mid)
		{
			if(num) merge(now, ls(now));
			floippy(ls(now), l, mid, num);
		}
		if(mid < r)
		{
			if(num) merge(now, rs(now));
			floippy(rs(now), mid + 1, r, num);
		}
	}
}T;
int main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for(int i = 1; i <= m; ++i) cin >> s[i].u >> s[i].v;
	for(int i = 1; i <= m; ++i) con[s[i].u].push_back(s[i].v), con[s[i].v].push_back(s[i].u);
	T.build(rt, 1, n);
	for(int i = 1; i <= n; ++i)
	{
		if(con[i].size())
		{
			int sig = con[i].size();
			con[i].push_back(-1);
			sort(con[i].begin(), con[i].end());
			for(int j = 1; j < sig; ++j)
				if(con[i][j] + 1 < con[i][j + 1])
					T.insert(rt, 1, n, con[i][j] + 1, con[i][j + 1] - 1, i);
			if(con[i][1] > 1) T.insert(rt, 1, n, 1, con[i][1] - 1, i);
			if(con[i][sig] < n) T.insert(rt, 1, n, con[i][sig] + 1, n, i);
		}
		else T.insert(rt, 1, n, 1, n, i);
	}
	T.floippy(rt, 1, n, 0);
	for(int i = 1; i <= n; ++i)
	{
		if(!mp[find(trans[i])]) mp[find(trans[i])] = ++tot;
		bel[i] = mp[find(trans[i])];
	}
	for(int i = 1; i <= n; ++i) ++hve[bel[i]];
	sort(hve + 1, hve + tot + 1);
	cout << tot << '\n';
	for(int i = 1; i <= tot; ++i) cout << hve[i] << " ";
	return 0;
}
```

---

## 作者：Coros_Trusds (赞：1)

并查集做法。

# 题目大意

给你一张 $n$ 个点 $m$ 条边的无向图 $G$，求这个图的补图 $G'$ 的连通块个数以及每个连通块的大小。

# 题目分析

首先我们在 $G$ 中找到度数最小的点 $minn$，在 $G$ 中度数最小即说明在 $G'$ 中度数最大。然后对于 $G$ 中的边 $(minn,v)$，把 $v$ 打上标记。剩下的未打上标记的点就是 $G'$ 中有边与 $minn$ 相连的点，把这些点和 $minn$ 合并起来。

然后对于所有的打上标记的点 $i$，若 $G$ 中存在 $(i,v)$，那么又对 $v$ 打上标记。原因同上。注意对于每个点 $i$，这些标记都是相互独立的，换句话说，对点 $i$ 进行操作时打的标记不会对其他 $i'$ 有影响。

合并操作使用并查集完成。

最后统计一下就好了。

# 时间复杂度分析

看起来复杂度非常高，似乎就是暴力，但实际上最多只会进行 $n+m$ 次。

**（下面不考虑并查集复杂度的 $\alpha$ 常数）**

先暴力枚举出那个度最小的点，它最坏情况最多连接 $\dfrac{m}{n}$ 个点，剩下 $n-\dfrac{m}{n}$ 个点是不用考虑的，因为都在一个连通块里面。

这 $\dfrac{m}{n}$ 个点,而我们枚举这些点的出边，共 $m-\frac{m}{n}$ 条。

最坏时间复杂度 $\mathcal{O(n+m)}$。

# 代码

```cpp
//2022/5/3
//2022/5/10
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdio>
#include <climits>//need "INT_MAX","INT_MIN"
#include <cstring>//need "memset"
#include <numeric>
#include <algorithm>
#define enter putchar(10)
#define debug(c,que) std::cerr << #c << " = " << c << que
#define cek(c) puts(c)
#define blow(arr,st,ed,w) for(register int i = (st);i <= (ed); ++ i) std::cout << arr[i] << w;
#define speed_up() ios::sync_with_stdio(false),cin.tie(0),cout.tie(0)
#define mst(a,k) memset(a,k,sizeof(a))
#define Abs(x) ((x) > 0 ? (x) : -(x))
#define stop return(0)
const int mod = 1e9 + 7;
inline int MOD(int x) {
	if(x < 0) x += mod;
	return x % mod;
}
namespace Newstd {
	char buf[1 << 21],*p1 = buf,*p2 = buf;
	inline int getc() {
		return p1 == p2 && (p2 = (p1 = buf) + fread(buf,1,1 << 21,stdin),p1 == p2) ? EOF : *p1 ++;
	}
	inline int read() {
		int ret = 0,f = 0;char ch = getc();
		while (!isdigit(ch)) {
			if(ch == '-') f = 1;
			ch = getc();
		}
		while (isdigit(ch)) {
			ret = (ret << 3) + (ret << 1) + ch - 48;
			ch = getc();
		}
		return f ? -ret : ret;
	}
	inline void write(int x) {
		if(x < 0) {
			putchar('-');
			x = -x;
		}
		if(x > 9) write(x / 10);
		putchar(x % 10 + '0');
	}
}
using namespace Newstd;

const int N = 2e5 + 5;
struct Graph {
	int v,nxt;
} gra[N << 1];
int head[N],deg[N],fa[N],siz[N],ans[N];
bool vis[N],st[N];
int n,m,idx;
inline int getf(int x) {
	return fa[x] == x ? x : fa[x] = getf(fa[x]);
}
inline void merge(int x,int y) {
	int f1 = getf(x),f2 = getf(y);
	if (f1 != f2) fa[f1] = f2;
}
inline void add(int u,int v) {
	gra[++ idx].v = v,gra[idx].nxt = head[u],head[u] = idx;
}
int main(void) {
#ifndef ONLINE_JUDGE
	freopen("in.txt","r",stdin);
#endif
	n = read(),m = read();
	for (register int i = 1;i <= m; ++ i) {
		int u = read(),v = read();
		add(u,v),add(v,u);
		deg[u] ++,deg[v] ++;
	}
	int minn = 1;
	for (register int i = 1;i <= n; ++ i) {
		if (deg[i] < deg[minn]) {
			minn = i;
		}
	}
	for (register int i = head[minn];i;i = gra[i].nxt) {
		int v = gra[i].v;
		vis[v] = true;
	}
	for (register int i = 1;i <= n; ++ i) {
		fa[i] = i;
	}
	for (register int i = 1;i <= n; ++ i) {
		if (!vis[i]) {
			merge(i,minn);
		}
	}
	for (register int i = 1;i <= n; ++ i) {
		if (vis[i]) {
			mst(st,false);
			for (register int j = head[i];j;j = gra[j].nxt) {
				int v = gra[j].v;
				st[v] = true;
			}
			for (register int j = 1;j <= n; ++ j) {
				if (!st[j]) {
					merge(j,i);
				}
			}
		}
	}
	int col = 0;
	for (register int i = 1;i <= n; ++ i) {
		if (fa[i] == i) {
			ans[i] = ++ col;
		}
	}
	for (register int i = 1;i <= n; ++ i) {
		siz[ans[getf(i)]] ++;
	}
	std::sort(siz + 1,siz + col + 1);
	printf("%d\n",col);
	for (register int i = 1;i <= col; ++ i) {
		printf("%d ",siz[i]);
	}

	return 0;
}
```

---

## 作者：w33z8kqrqk8zzzx33 (赞：1)

对一个图做 dfs 既可以直接 $O(n+m)$ 做，也有 $O(n+(\binom{n}{2}-m))$ 的枚举补边的方法。对这道题目来说我们想要的是一个时间复杂度是关于这些补边的时间复杂度。  
直接跑 dfs 的时间复杂度是 $O(n^2-m)$，但是只会访问到 $O(n)$ 个节点，瓶颈在于需要判断每一条边是否存在和是否给原来遍历过这个节点。于是考虑如何保证每一个节点和补边只会枚举到一次。  
先维护一个 set，这个 set 仅仅有当前没有遍历到的东西。每一次深搜遍历到某一个节点删除对应元素。  
然后，每一次到一个节点遍历一整个 set 来找还可以遍历到哪里。由于每一条补边都最多给统计两次，所有在 set 里节点均摊枚举到的次数是 $O(n+m)$，时间复杂度 $O((n+m)\log n)$，可以过。

核心代码：

```cpp
set<int> has;
set<pii> ed;

set<int>::iterator dfs(int u, int& cnt) {
	has.erase(u); cnt++;
	auto at = has.begin();
	while(at != has.end()) {
		if(ed.count({u,*at})) ++at;
		else at=dfs(*at, cnt);
	}
	return has.upper_bound(u);
}

signed main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; gi(n), gi(m);
	rep1(i, n) has.insert(i);
	while(m--) {
		int u, v; gi(u), gi(v);
		ed.insert({u, v});
		ed.insert({v, u});
	}
	multiset<int> ans;
	while(has.size()) {
		int cnt = 0;
		dfs(*has.begin(), cnt);
		ans.insert(cnt);
	}
	print(ans.size()), pc('\n');
	for(int k:ans) print(k), pc(' ');
}
```

---

## 作者：hehelego (赞：1)

这个套路实在太常见了...而且直觉做法就是对的.

用到的符号与意义
- $V,E$边集合,点集合.
- $complete(G),c(G)$补图,$G=(V,E)\implies c(G)=(V,E(K_{|V|})\setminus E)$就是另一个图$G'$满足$G,G'$边集不相交,并起来是完全图.
- $adj(u)$与$u$相邻的点,$v\in adj(u)\iff (u,v)\in E$

------

### staetment
给出无向图$G=(V,E)$求补图,在$complete(G)$上面BFS.  
其中$|E|\ll \binom{|V|}{2}$.  
大概复杂度在$O(T\log T),T=|V|+|E|$就可以过.

### sol
感性理解一下,这个图的联通分量应该非常少.  
我们不能直接BFS,这样复杂度不低于边数,这里是$n^2-m$显然过不去.  

但是我们还是应该分析一下暴力在$c(G)$上面BFS为什么慢,毕竟$O(V+E)$已经和图大小同阶了,没什么直接优化可以做了.  
可以说,对于每个点$v$我们检查的边数大概都是$O(n)$的,然而实际上可用的边数量甚至是$O(1)$的(0条的没有时间消耗,n点只用n-1边就联通了).  
这启发我们尝试优化寻找**未访问,不在**$adj(v)$**中的点**
这一步,这一步的总复杂度下界是$O(n)$而不是$O(n^2-m)$  

我们想一个直觉暴力,用数据结构维护未访问点集$S$,对于一个点$u$,枚举里面的点,跳过$adj(u)$中的点.显然这样不会重复访问重复的点.....并且,每个原图中的边,只会被考虑一次.我们得到了惊人的$O(Tf(T))$其中$T=|V|+|E|$而$f(T)$表示这个数据结构的单次操作平均复杂度.  
如果是平衡树,那么就是$O(n\log n)$如果是hash表,甚至链表,可以真的做到线性.  


回顾一下,暴力的问题在于$c(G)$的边集比起$G$实在是太大了.我们不能操作$c(G)$而只能在$G$上面玩. 找相邻点,继续搜索,在补图上面需要每次枚举$O(n)$个边,而在原图上面,删掉不相邻的点其实只有$\sum deg(u)=m=O(n)$的复杂度,所以维护未访问点,暴力在集合里面查询不与$u$相邻的点,把这些点都删掉.  


自然语言描述下,似乎不太容易看懂它的复杂度,但是写出程序来,这个复杂度就比较显然了,看solve(int S);

### code
```cpp
#include <bits/stdc++.h>
int read(){
	int x=0,f=1; char c;
	do{c=getchar();if(c=='-')f=-1;}while(!isdigit(c));
	do{x=x*10+c-'0';c=getchar();}while(isdigit(c));
	return x*f;
}
const int N=200000+10;
int n,m,col[N],cnt[N],qwq;
int q[N],ql,qr;
std::vector<int> g[N];
std::set<int> tr;

void solve(int S){
	tr.erase(S); col[S]=++qwq;
	q[ql=0]=S;qr=1;
	while(ql<qr){
		int u=q[ql++]; std::vector<int> tmp;
		for(int v:g[u])if(tr.count(v)) tmp.push_back(v);
		for(int v:tmp) tr.erase(v);
		for(int v:tr) col[q[qr++]=v]=col[u];
		tr.clear();
		for(int v:tmp) tr.insert(v);
	}
// 第一个,第二个,第四个for:这部分总复杂度$O(m\log n)$
//       每条边只考虑一次,每次都是在大小为$O(n)$的平衡树里面查询.
// 第三个for以及下面的clear:总复杂度是$O(n\log n)$
//       因为这里每个点只能被考虑一次,用完就删掉了.
// 最好是整个while循环,我们实际上走的边,是补图每个联通块的一个生成树,所以其实只能进入while部分$O(n)$次.
}
int main(){
	n=read();m=read();
	for(int i=0,a,b;i<m;i++){
		a=read();b=read();
		g[a].push_back(b);
		g[b].push_back(a);
	}
	for(int i=1;i<=n;i++) tr.insert(i);
	for(int i=1;i<=n;i++) if(col[i]==0) solve(i);
	for(int i=1;i<=n;i++) cnt[col[i]-1]++;
	std::sort(cnt,cnt+qwq); printf("%d\n",qwq);
	for(int i=0;i<qwq;i++) printf("%d ",cnt[i]);
	printf("\n");
	return 0;
}
```

---

