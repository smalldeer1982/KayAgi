# Spanning Tree with One Fixed Degree

## 题目描述

给定一个无向、无权、连通的图，该图包含 $n$ 个顶点和 $m$ 条边。保证图中没有自环和重边。

你的任务是找到该图的任意一棵生成树，使得编号为 $1$ 的顶点的度数恰好等于 $D$（或者说明不存在这样的生成树）。回忆一下，顶点的度数是指与该顶点相连的边的数量。

## 说明/提示

下图对应第一个和第二个样例：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1133F2/517159ebac5fb796da2e35eb5deb42cb16b19928.png)

下图对应第三个样例：![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1133F2/5ec8b5eeba4dc997a4e457a85e595860b2a0bfe0.png)

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4 5 1
1 2
1 3
1 4
2 3
3 4
```

### 输出

```
YES
2 1
2 3
3 4
```

## 样例 #2

### 输入

```
4 5 3
1 2
1 3
1 4
2 3
3 4
```

### 输出

```
YES
1 2
1 3
4 1
```

## 样例 #3

### 输入

```
4 4 3
1 2
1 4
2 3
3 4
```

### 输出

```
NO
```

# 题解

## 作者：_Fontainebleau_ (赞：4)

## CF1133F2 Spanning Tree with One Fixed Degree

### 题意

- 给你一个 $n$ 个点 $m$ 条边的无向图（无自环或重边）。
- 让你构造一个满足编号为 $1$ 的点的度数为 $k$ 的树，树的顶点数与图的顶点数相等。
- 若可以，输出 $\texttt{YES}$ ，并输出这棵树。
- 若不可以，输出 $\texttt{NO}$ 。
- $2\leq n\leq 2 \times 10^5$, $n-1\leq m \leq \min(2 \times 10^5,\frac{n(n-1)}{2})$, $1\leq k \leq n$。

### 分析

前置知识：连通块（当然强连通分量也可以），BFS。

个人认为，本题的难点就在输出 $\texttt{YES/NO}$ 上。只要想出了这个点，剩下的 BFS 基本就是无脑操作。所以本文就讲如何判断能否生成这棵树。

首先，不妨计与结点 $1$ 相连的边的数量为 $cnt$ 。一个很显然不可能的情况是 $cnt <k$ 。

但是这样仅仅是最多连边数小于 $k$ 的情况，我们还需要一种最小连边数大于 $k$ 的情况。

因为题目中说，“树的顶点数于图的顶点书相等”，所以，要满足题意，结点 $1$ 必须至少向此时的每一个连通块连边。因而容易想到，当删去结点 $1$ 后，连通块数量大于 $k$ 也是不行的。

于是这样一个问题就被我们解决了。

生成树的话，先向所有连通块连边，然后如果不够，就再随便向其他点连边。

### 代码

~~目前是最优解~~

连通块采用的是并查集。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,cnt,num,tot;
int fa[200005];
int d[400005];
bool used[200005],inq[200005];
int t[400005],nxt[400005],h[200005];
int q[1001001],f,e;
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
inline void merge(int x,int y)
{
	int p=find(x),q=find(y);
	fa[p]=q;
}
inline void addedge(int a,int b)
{
	t[++tot]=b,nxt[tot]=h[a],h[a]=tot;
}
inline void bfs()
{
	f=e=1,q[1]=1,inq[1]=true;
	while(f<=e)
	{
		int u=q[f++];
		for(int p=h[u];p;p=nxt[p])
		{
			int v=t[p];
			if(!inq[v])	inq[v]=true,q[++e]=v,printf("%d %d\n",u,v);
		}
	}
}
int main()
{
	n=read(),m=read(),k=read();
	for(int i=0;i<=n;i++)	fa[i]=i;
	for(int i=1;i<=m;i++)
	{
		int u=read(),v=read();
		if(u>v)	swap(u,v);
		if(u!=1)
			merge(u,v),addedge(u,v),addedge(v,u);
		else	d[++cnt]=v;
	}
	for(int i=2;i<=n;i++)
		if(fa[i]==i)	num++;
	if(k>cnt||k<num)
	{
		puts("NO");
		return 0;
	}
	puts("YES");
	for(int i=1;i<=cnt;i++)
	{
		int v=d[i];
		if(used[find(v)])	continue;
		used[find(v)]=true;
		d[i]=-1;
		addedge(1,v),addedge(v,1);
		k--;
	}
	if(k)
		for(int i=1;i<=cnt&&k;i++)
		{
			int v=d[i];
			if(d[i]==-1)	continue;
			addedge(1,v),addedge(v,1);
			k--;
		}
	bfs();
	return 0;
}
```


---

## 作者：yitinboge_fan (赞：3)

# CF1133F2 Spanning Tree with One Fixed Degree

经 @scyFBM 大神许可转发此code。

观察题目发现可以进行随机化+二分。对每一条边随机一个权值，然后每次尝试给和 $1$ 相邻的边加一个偏移量控制程序是否倾向于选择与 $1$ 相邻的边，二分这个偏移量，每次计算最小生成树并检查这个生成树是否符合要求。时间复杂度 $O(m\log m\log A)$ ，其中 $A$ 为权值范围。

code：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+9;
int n,m,k,fa[N];
int get(int x){
	while(x!=fa[x]) x=fa[x]=fa[fa[x]];
	return x;
}
bool use[N];
struct edge{int u,v,w;bool is;}e[N];
bool cmp(const edge&a,const edge&b){return a.w<b.w;}
bool check(int x){
	int cnt=0;
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++){
		use[i]=0;
		if(e[i].is) e[i].w+=x;
	}
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;i++){
		int fx=get(e[i].u),fy=get(e[i].v);
		if(fx==fy) continue;
		fa[fx]=fy,use[i]=1;
		if(e[i].is) cnt++;
	}
	for(int i=1;i<=m;i++)if(e[i].is) e[i].w-=x;
	if(cnt==k){
		puts("YES");
		for(int i=1;i<=m;i++)if(use[i]) cout<<e[i].u<<' '<<e[i].v<<endl;
		exit(0);
	}
	return cnt>k;
}
int main(){
	srand(time(0));
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++){
		cin>>e[i].u>>e[i].v,e[i].w=rand();
		if(e[i].u==1||e[i].v==1) e[i].is=1;
	}
	int l=-RAND_MAX,r=RAND_MAX;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	check(l-1);
	puts("NO");
	return 0;
}
```

---

## 作者：zzqDeco (赞：3)

交了翻译也来交个题解

首先可以想到如果连在一号的边数小于要求的$D$，那一定不行

其次，就要考虑块数量了，这也是我一开始没想到的

先dfs一边，看一下**除了一号以外的**连通块的个数

很容易想到，一个块中一定有一个是要连一号的，不然就不能构成生成树

最后再bfs或者dfs，就可以输出边了，我由于比较懒，判断连一的边放在bfs里面做了

```cpp
#include <cstdio>
#include <iostream>
#include <queue>
#include <iostream>
#include <cstring>

using namespace std;

struct Edge
{
  int to,next;
}e[400010];

int n,m,k,cnt;

int head[200010],num;

int vis[200010],chose[200010],d[200010];

void addedge(int a,int b)
{
  e[++num].to=b;
  e[num].next=head[a];
  head[a]=num;
}

void dfs(int u)
{
  vis[u]=1;
  for(int i=head[u];i;i=e[i].next)
  {
    if(!vis[e[i].to]) dfs(e[i].to);
  }
  return ;
}

void bfs()
{
  memset(vis,0,sizeof(vis));
  queue <int>q;
  q.push(1);
  vis[1]=1;
  while(!q.empty())
  {
    int now=q.front();
    q.pop();
    for(int i=head[now];i;i=e[i].next)
    {
      if(((now==1&&chose[e[i].to])||now!=1)&&!vis[e[i].to])
      {
        vis[e[i].to]=1;
        printf("%d %d\n",now,e[i].to);
        q.push(e[i].to);
      }
    }
  }
}

int main()
{
  scanf("%d%d%d",&n,&m,&k);
  for(int i=1;i<=m;i++)
  {
    int a,b;
    scanf("%d%d",&a,&b);
    if(b!=1) addedge(a,b);
    if(a!=1) addedge(b,a);
    d[a]++;
    d[b]++;
  }
  vis[1]=1;
  for(int i=head[1];i;i=e[i].next)
  {
    if(!vis[e[i].to])
    {
      cnt++;
      chose[e[i].to]=1;
      dfs(e[i].to);
    }
  }
  if(k>=cnt&&k<=d[1])
  {
    printf("YES\n");
    for(int i=head[1];i&&cnt<k;i=e[i].next)
    {
      if(!chose[e[i].to])
      {
        cnt++;
        chose[e[i].to]=1;
      }
    }
    bfs();
  }
  else
  {
    printf("NO\n");
    return 0;
  }
}

```

---

## 作者：Night_fall (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1133F2)

前置知识：[并查集](https://www.luogu.com.cn/problem/P3367)。

--------

~~由于全程没有用搜索，所以自认为还是能提供一些新思路的吧。~~

看到题目，直接分两个部分：判断和连边。

### 判断部分

首先一个最简单的判定，与 $1$ 节点相连的边数小于 $D$，直接输出 $\texttt {NO}$。

然后，我们可以使用连通块来判断。

这里连通块指的是去掉节点 $1$ 后，相互连接的若干个节点。

显而易见，在每个连通块中必须有至少一个节点与节点 $1$ 相连。

那么可以使用并查集计连通块个数，数量大于 $D$ 输出 $\texttt {NO}$，否则为 $\texttt{YES}$。

### 连边部分

现将每个联通块中必连的一个边连好。

再根据 $D$ 的大小从节点 $1$ 连出其他边。

最后根据树的性质用并查集连出一棵树。个人认为这个过程类似于最小生成树。

其中 $vis$ 数组表示该节点是否与 $1$ 相连，$f$ 数组表示连通块（前半段）或该点是否在树中（后半段）。

------------

## code

```cpp
#include<iostream>
#include<algorithm>
using namespace std;

struct EDGE{int u,v,c;}e[200010];
int f[200010];
bool vis[200010];
int find(int x){return f[x]=(f[x]==x?x:find(f[x]));}

int main(){
    int n,m,d,cnt=0;
    cin>>n>>m>>d;
    for(int i=1;i<=n;i++) f[i]=i;
    for(int i=1;i<=m;i++){
    	cin>>e[i].u>>e[i].v;
    	if(e[i].u>e[i].v) swap(e[i].u,e[i].v); //规范化数据，便于代码编写
    	if(find(e[i].u)!=find(e[i].v)&&e[i].u!=1) f[find(e[i].u)]=find(e[i].v); //统计连通块
    	if(e[i].u==1) cnt++; //统计边数
    }
    if(cnt<d) puts("NO"),exit(0); //边数不够
    cnt=0;
    for(int i=2;i<=n;i++){
    	if(f[i]==i) cnt++; //统计连通块个数
    }
    if(cnt>d) puts("NO"),exit(0); //连通块数量过多
    puts("YES");
    cnt=0;
    for(int i=1;i<=m;i++){
    	if(f[find(e[i].v)]&&!vis[e[i].v]&&e[i].u==1) cnt++,cout<<"1 "<<e[i].v<<'\n',f[find(e[i].v)]=0,vis[e[i].v]=1;
    } //连接必连的边
    for(int i=1;i<=m&&cnt<d;i++){
    	if(e[i].u==1&&!vis[e[i].v]) vis[e[i].v]=1,cout<<"1 "<<e[i].v<<'\n',cnt++;
    } //满足D的要求
    for(int i=1;i<=n;i++) f[i]=vis[i]?1:i; //统计节点是否已在树中（与1连接）
    for(int i=1;i<=m;i++){
        int u=e[i].u,v=e[i].v;
        if(find(u)!=find(v)&&u!=1) f[find(u)]=find(v),printf("%d %d\n",u,v),cnt++;
        if(cnt==n-1) exit(0);
    } //最小生成树板子稍作修改
}
```

---

## 作者：incra (赞：1)

### Sol
简单题。

首先不连通一定无解。

假设 $deg_i$ 表示 $i$ 的点的度，那么 $deg_1 < d$ 显然无解。

注意到如果把 $1$ 删了以后，如果连通块数量大于 $d$ 那么也无解。

否则我们只需要考虑先在把 $1$ 删掉以后各个连通块各选一个点与 $1$ 联通，假设选了 $p$ 个点，那么随后在和 $1$ 联通的点里面再选 $d-p$ 个未选过的点即可，这样就保证了 $1$ 度为 $1$。

剩下的边只需要保证是树即可，直接能连就连即可。
### Code
[Link](https://codeforces.com/contest/1133/submission/317534759)。

---

## 作者：FiraCode (赞：1)

## 思路：

可以先考虑将不经过一号点的连通分量找出来。

然后若连通分量个数 $>D$ 则无解（因为无法通过选 $D$ 条边而使其联通）。

否则对于 $1$ 连接每个连通分量的边任选一条，然后剩余的边随便选即可。

最后对于每个和 $1$ 相连的点，从他 dfs 一遍，当然不经过 $1$ 节点，对于每个点若当前位于它联通就将这条边加上并继续 dfs，否则跳过。

## Code：
代码写的有点丑（
```cpp
#include <bits/stdc++.h>

using namespace std;

int n, m, D;
int idx, st[200010];
vector<int> e[200010];
int vis[200010], stt[200010];
map<pair<int, int>, int> ma1;

void dfs(int u) {
	st[u] = idx;
	for (auto v : e[u]) {
		if (v != 1 && !st[v]) {
			dfs(v);
		}
	}
}

void dfs1(int u) {
	vis[u] = 1;
	for (auto v : e[u]) {
		if (v != 1 && !vis[v]) {
			// cout << u << ' ' << v << "---\n";
			ma1[{u, v}] = 1;
			dfs1(v);
		}
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &D);
	for (int i = 1; i <= m; ++i) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (u > v) swap(u, v);
		e[u].push_back(v);
		e[v].push_back(u);
	}

	if (e[1].size() < D) {
		puts("NO");
		// cout << 1 << endl;
		return 0;
	}

	for (auto v : e[1])
		if (!st[v]) {
			++idx;
			dfs(v);	
		}

	for (auto v : e[1]) {
		if (stt[st[v]]) continue;
		stt[st[v]] = true;
		--D;
		if (D < 0) {
			puts("NO");
			return 0;
		}
		vis[v] = true;
		ma1[{1, v}] = 1;
	}

	for (auto v : e[1]) {
		if (D) {
			if (!vis[v]) {
				vis[v] = true;
				--D;
				ma1[{1, v}] = true;
			}
		}
	}

	puts("YES");

	for (auto v : e[1]){
		if (ma1.count({1, v})) {
			// cout << v << endl;
			dfs1(v);
		}
	}

	for (auto [u, v] : ma1) printf("%d %d\n", u.first, u.second);
	return 0;
}
```

---

## 作者：GGapa (赞：0)

构造题考虑上下界，上界很容易，下界从菊花图的角度进行思考，发现每个节点都要和 1 连通，那么处理出 1 节点最少需要和多少个节点连边，这就是下界。把 1 删掉看连通块数量就可以轻松解决。

注意：将 1 号节点连边的时候要优先从不同的连通块中选点，如果不够就随便连。

```cpp
#include <bits/stdc++.h>
#define rep(i, a, b) for(int i = (a), stOwxc = (b); i <= stOwxc; i++)
#define per(i, a, b) for(int i = (a), stOwxc = (b); i >= stOwxc; i--)
using namespace std;
using LL = long long;
using VI = vector<int>;
const int N = 2e5 + 5;

int n, m, d; 
vector<int> G[N], T[N];
int vis[N];
int num = 0;

void dfs(int x) {
    vis[x] = 1; num++;
    for(auto to : T[x]) if(!vis[to])
        dfs(to);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    cin >> n >> m >> d;
    for(int i = 1, u, v; i <= m; i++) {
        cin >> u >> v, G[u].emplace_back(v), G[v].emplace_back(u);
        if(u == 1 || v == 1) continue;
        T[u].emplace_back(v), T[v].emplace_back(u);
    }
    int cnt = 0;
    vector<array<int, 2>> sc;
    for(auto i : G[1]) if(!vis[i]) {
        num = 0;
        cnt++, dfs(i); 
        sc.push_back({num, i});
    }
    if(G[1].size() < d || cnt > d) return cout << "NO\n", 0;
    cout << "YES\n";
    queue<int> q;
    fill(vis, vis + 1 + n, 0);
    sort(sc.begin(), sc.end());
    for(auto a : sc) {
        int i = a[1] ;
        if(q.size() >= d) break;
        cout << 1 << " " << i << '\n';
        q.push(i); vis[i] = 1;
    }
    for(auto i : G[1]) {
        if(q.size() >= d) break;
        if(vis[i]) continue;
        cout << 1 << " " << i << '\n', q.push(i), vis[i] = 1;
    }
    vis[1] = 1;
    while(!q.empty()) {
        int x = q.front(); q.pop();
        for(auto to : G[x]) if(!vis[to]) {
            vis[to] = 1;
            q.push(to);
            cout << x << " " << to << '\n';
        }
    }
    return 0;
}
```

---

