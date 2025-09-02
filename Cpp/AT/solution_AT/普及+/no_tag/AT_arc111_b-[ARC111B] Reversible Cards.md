# [ARC111B] Reversible Cards

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc111/tasks/arc111_b

$ 1 $ から $ N $ の番号がついた $ N $ 枚のカードがあり、各カードの両面には正整数で表される色がついています。

カード $ i $ の片面の色は $ a_i $, もう片面の色は $ b_i $ です。

各カードについてどちらの面を表にするか自由に選べるとき、表側に見える色の種類数の最大値はいくつになるか求めてください。

## 说明/提示

### 制約

- $ 1\ \leq\ N\ \leq\ 200000 $
- $ 1\ \leq\ a_i,b_i\ \leq\ 400000 $
- 入力される数はすべて整数

### Sample Explanation 1

それぞれ、$ 1 $,$ 3 $,$ 4 $,$ 2 $ の側を表にすることで $ 4 $ 色を達成できます。

### Sample Explanation 2

そもそも一色しか使われていません。

## 样例 #1

### 输入

```
4
1 2
1 3
4 2
2 3```

### 输出

```
4```

## 样例 #2

### 输入

```
2
111 111
111 111```

### 输出

```
1```

## 样例 #3

### 输入

```
12
5 2
5 6
1 2
9 7
2 7
5 5
4 2
6 7
2 2
7 8
9 7
1 8```

### 输出

```
8```

# 题解

## 作者：_determination_ (赞：5)

这是一篇二分图匹配做法。

如果你看到这道题想到建图，那这道题就算是做完了。考虑以卡牌作为左部点，颜色作为右部点。按照卡牌是否有这个颜色连边。然后跑二分图最大匹配即可。

点数是 $6\times 10^5$，边数是 $10^6$ 左右。直接跑网络流二分图匹配即可。

代码：
```cpp
#include<bits/stdc++.h>
//#define int long long
#define endl '\n'
using namespace std;
//const int inf=0x3f3f3f3f3f3f3f3f;
const int inf=0x3f3f3f3f;
vector<pair<int,int> >e[1000010]; 
//struct node{
//	int first,second;
//};
//vector<node>e[1000010];
vector<int>id[1000010];
void add(int u,int v,int w)
{
	id[u].push_back(e[v].size());
	id[v].push_back(e[u].size());
	e[u].push_back({v,w});
	e[v].push_back({u,0});
}
int a[200010],b[200010];
int s,t;
int dep[1000010],gap[1000010],maxflow;
queue<int>q;
void bfs()
{
	memset(dep,0x3f,sizeof(dep));
//	memset(gap,0,sizeof(gap));
	gap[0]=1;
	dep[t]=0;
	q.push(t);
	while(!q.empty())
	{
		int x=q.front();
		q.pop();
		for ( int i = 0 ; i < e[x].size() ; i++ )
		{
			int v=e[x][i].first;
			if(dep[v]==inf)
			{
				dep[v]=dep[x]+1;
				gap[dep[v]]++;
				q.push(v);
			}
		}
	}
}
int dfs(int x,int flow)
{
	if(x==t)
	{
		maxflow+=flow;
		return flow;
	}
	int used=0;
	for ( int i = 0 ; i < e[x].size() ; i++ )
	{
		int v=e[x][i].first,w=e[x][i].second;
		if(w==0||dep[v]+1!=dep[x])continue;
		int f=dfs(v,min(flow-used,w));
		if(f)
		{
			used+=f;
			e[x][i].second-=f;
			e[v][id[x][i]].second+=f;
			if(used==flow)return flow;
		}
	}
	gap[dep[x]]--;
	if(!gap[dep[x]])dep[s]=t+1;
	dep[x]++;
	gap[dep[x]]++;
	return used;
}
void isap()
{
	bfs();
	while(dep[s]<=t)
	{
		dfs(s,inf);
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int n;
	cin >> n;
	s=1,t=7e5;
	for ( int i = 1 ; i <= n ; i++ )
	{
		cin >> a[i] >> b[i];
		add(i+1,n+1+a[i],1);
		add(i+1,n+1+b[i],1);
		add(s,i+1,1);
	}
	for ( int i = 1 ; i <= 400000 ; i++ )
	{
		add(n+1+i,t,1);
	}
	isap();
	cout << maxflow;
	return 0;
}
```

---

## 作者：rui_er (赞：5)

我们将值域中每个数视作一个节点，将每张卡片视作连接两个节点的边，则问题转化为：对于每条边都选择一个端点，使得被选择的节点总数最大。

显然每个连通块可以分开处理。设连通块的点数、边数为 $v,e$，可以证明这个连通块内被选择的节点总数为 $\min\{v,e\}$：

对于每个连通块，它要么是一棵树，要么有环（废话）。显然无论哪种情况，都不可能选超过 $\min\{v,e\}$ 个节点。

对于一棵树，我们最多选 $e$ 个节点：指定一个点当根，每条边都选更深的节点。

对于有环的图，我们最多选 $v$ 个节点：找出一棵生成基环树，保证环上的每条边选择的节点都不同，然后指定环当根按照与树相同的策略就可以选到环外的所有节点。

洪水填充统计每个连通块的点数、边数即可。

```cpp
// Problem: B - Reversible Cards
// Contest: AtCoder - AtCoder Regular Contest 111
// URL: https://atcoder.jp/contests/arc111/tasks/arc111_b
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
#define likely(exp) __builtin_expect(!!(exp), 1)
#define unlikely(exp) __builtin_expect(!!(exp), 0)
using namespace std;
typedef long long ll;

mt19937 rnd(std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()).count());
int randint(int L, int R) {
	uniform_int_distribution<int> dist(L, R);
	return dist(rnd);
}

template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}

const int N = 4e5+5;

int n, vis[N], cntV, cntE, ans;
vector<int> e[N];

void dfs(int u) {
	vis[u] = 1;
	++cntV;
	for(int v : e[u]) {
		if(!vis[v]) dfs(v);
		++cntE;
	}
}

int main() {
	for(scanf("%d", &n); n; n--) {
		int u, v;
		scanf("%d%d", &u, &v);
		e[u].push_back(v);
		e[v].push_back(u);
	}
	rep(i, 1, N-1) {
		if(!vis[i]) {
			cntV = cntE = 0;
			dfs(i);
			cntE >>= 1;
			ans += min(cntV, cntE);
		}
	}
	printf("%d\n", ans);
	return 0;
}
```

---

## 作者：CJerryR (赞：3)

### 并查集做法
  
 ~~可以看看[这道题](https://www.luogu.com.cn/problem/P1640)获得双倍经验~~。

想象每个卡片的两面数字的使用情况，一张牌上两个数字的使用互斥所以其中一个值是必用的。

因此可以考虑连成大根树（每条边上大下小），假设这个树上没有环，那么树上使用的点是 $n-1$ 次（让结果最大时，只有祖先节点取不到），同时如果有环（包括自环）出现的话，那么这个树上的所有点都可以取到。

判断环的方法可以采用并查集，因此存储 $reach$ 数组，表示如果 $i$ 是祖先节点时能否取到（不是祖先节点无意义），并且记录子树大小 $siz$ 即可。

代码如下，~~给蒟蒻点个赞吧~~。

```cpp
#include<bits/stdc++.h>
#define endl '\n'
using namespace std;
const int MAXN = 4e5 + 6;
inline int read() {
    int x = 0, w = 1;
    char ch = 0;
    while (ch < '0' || ch >'9') {
        if (ch == '-')w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = (x << 3) + (x << 1) + (ch - '0');
        ch = getchar();
    }
    return x * w;
}
int fa[MAXN + 10];
int siz[MAXN + 10];
int come[MAXN + 10];
bool reach[MAXN + 10];//是否必然能到达(每条边上两点必有一点可以到达)
inline int findfa(int x) {
    return x == fa[x] ? x : fa[x] = findfa(fa[x]);
}
signed main() {
    int n = read();
    for (int i = 1; i < MAXN; i++)fa[i] = i, siz[i] = 1;
    for (int i = 1; i <= n; i++) {
        int u = findfa(read()), v = findfa(read());
        come[u] = come[v] = 1;
        if (u == v)reach[u] = 1;
        //两边其中一点如果连边前必达 那么另一点必达
        //小点往大点上接
        else {
            if (u < v)swap(u, v);
            fa[v] = u, reach[u] |= reach[v];
            siz[u] += siz[v];
        }
    }
    int ans = 0;
    for (int i = 1; i <= MAXN; i++) {
        if (come[i] && findfa(i) == i) {
            ans += siz[i];
            if (!reach[i])ans--;
        }
    }
    cout << ans << "\n";
    return (1 ^ 0 ^ 1);
}
```
完结撒花。

---

## 作者：Laisira (赞：2)

## 一道缩点模板题啊
### 题目大意
给出 $n$ 张牌，每张牌正面颜色 $a_i$ 背面 $b_i$，决定每张牌正反，最大化颜色种类。

### 思路
很容易想到把颜色做点、牌做边建图。

对于这张图呢，又很容易发现，一张图如果有环贡献就是他的点数，但有时要减一。于是我们把它缩个点，然后图就成了一片森林。

然后判个是否有环，如果一个森林原来有至少一个环或大小为一，就可以全部点都算上，否则要减一，这个可以直接在缩点的时候打打标记就行了。

### 代码
```cpp
#include<bits/stdc++.h>
#define Maxn 400010
using namespace std;
vector<int> q[Maxn];
int sz[Maxn],vis[Maxn];
int dfn[Maxn],low[Maxn],Time;
stack<int> st;
int root[Maxn],tot,ft[Maxn];
int siz[Maxn];
void Tarjan(int x,int fa)
{
    siz[root[tot]]++;
    st.push(x); 
    low[x]=dfn[x]=++Time;
    for(int u:q[x]) {
        if(u==fa)continue;
        if(u==x)ft[root[tot]]=1;
        if(!dfn[u]) {
            Tarjan(u,x);
            low[x]=min(low[x],low[u]);
        } else 
            low[x]=min(low[x],dfn[u]);
    }
    if(low[x]==dfn[x])
    {
        int y;
        while(y=st.top())
        {
            st.pop();
            low[y]=low[x];
            sz[low[x]]++;
            if(y==x)break;
        }
        if(sz[low[x]]>1)
            ft[root[tot]]=1;
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        int u,v;
        cin>>u>>v;
        q[u].push_back(v);
        q[v].push_back(u);
    }
    long long ans=0;
    for(int i=1;i<Maxn;i++)
        if(!dfn[i]&&!q[i].empty())
            root[++tot]=i,Tarjan(i,0);
    for(int i=1;i<Maxn;i++)
        if(!vis[low[i]]&&!q[i].empty())
            ans+=sz[low[i]],vis[low[i]]=1;
    for(int i=1;i<=tot;i++)
        ans-=(ft[root[i]]^1);
    cout<<ans;
    return 0;
}
```

---

## 作者：DegChuZm (赞：2)

### sol
~~其实可以编网络流~~

考虑到每个卡片有两面，两面有不同的颜色。

考虑每张卡片向对应的两个颜色分别建一条有向边。

然后这个图建出来后我们发现似乎好像求个最大匹配就行了。

然后使用一下 dinic 就做完了。

这里简单讲一下怎么建图才能用网络流跑最大匹配。

首先建一个超级源点和一个超级汇点，从超级源点到所有左半边部分的点集连一条长度为 $1$ 的边，从所有右半边部分的点集到超级汇点连一条长度为 $1$ 的边。

然后两个点集之间的边长度为 $1$。

以样例为例，图建出来大概长这样：

![graph](https://cdn.fzoi.top/upload/user/c20150000/24041008507813.png)

然后正常跑你的网络流就行了。

注意如果 TLE 了两个点那么考虑判一下重边，判了快一半。

### code

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,k,dep[600010],head[600001],now[600010],cnt=1,ans,s,x,y,z,g,tot;
struct dcz{
	int nex,to,val;
}a[2000001];
void add(int x,int y,int z){
	a[++cnt].nex=head[x];
	a[cnt].to=y;
	a[cnt].val=z;
	head[x]=cnt;
}
queue<int> q;
inline bool bfs(int u){
	for(int i=0;i<=600001;i++) dep[i]=0x3f3f3f3f;
	while(q.size()) q.pop();
	dep[u]=0;
	now[u]=head[u];
	q.push(u);
	while(q.size()){
		int u=q.front();
		q.pop();
		for(int i=head[u];i;i=a[i].nex){
			int v=a[i].to,w=a[i].val;
			if(dep[v]==0x3f3f3f3f&&w>0){
				q.push(v);
				dep[v]=dep[u]+1;
				now[v]=head[v];
				if(v==k) return 1;
			}
		}
	}
	return 0;
}
int dfs(int u,int d){
	if(u==k) return d;
	int flow=0;
	for(int i=now[u];i&&d>0;i=a[i].nex){
		int v=a[i].to,w=a[i].val;
		now[u]=i;
		if(dep[v]==dep[u]+1&&w>0){
			int sum=dfs(v,min(d,w));
			if(sum==0) dep[v]=0x3f3f3f3f;
			a[i^1].val+=sum;
			a[i].val-=sum;
			flow+=sum;
			d-=sum;
		}
	}
	return flow;
}
int mp[400001];
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	cin>>n;
	s=0,k=3*n+1;
	for(int i=1;i<=n;i++){
		add(s,i,1);
		add(i,s,0);
		
		add(i+n,k,1);
		add(k,i+n,0);
		
		add(i+2*n,k,1);
		add(k,i+2*n,0);
	}
	for(int i=1;i<=n;i++){
		cin>>x>>y;
		if(!mp[x]) mp[x]=++tot;
		if(!mp[y]) mp[y]=++tot;
		x=mp[x],y=mp[y];
		add(i,x+n,1);
		add(x+n,i,0);
		if(x!=y){
			add(i,y+n,1);
			add(y+n,i,0);
		}
	}
	while(bfs(s)){
		ans+=dfs(s,0x3f3f3f3f);
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：hstt (赞：1)

## Solution
将一张卡牌的两面的颜色连边，考虑贪心，发现以下结论：

1. 若某种颜色只能通过选某张卡牌的一面得到（度为 $1$），那么翻这一面使答案加 $1$，一定比翻另一面更优。

2. 若一个联通块中每一个点度 $\geq 2$，则至少存在一个环，每一个点都能得到。

我们只需要不断将度为 $1$ 的点入队删边，就能使图中只剩下结论二中的连通块和入度为零的点。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=2e5+5;
int m,ans;
int mn=1e9,mx;
int fir[N*2],nex[N*2],to[N*2],tot=1;
int in[N*2];//度
bool vis[N*2],used[N];//vis 标记是否选过颜色，used 标记是否用过卡牌
void add(int x,int y){
    nex[++tot]=fir[x];
    to[tot]=y;
    fir[x]=tot;
}
queue<int>q;
int main(){
    scanf("%d",&m);
    int x,y;
    while(m--){
        scanf("%d%d",&x,&y);
        mn=min(mn,min(x,y));
        mx=max(mx,max(x,y));
        if(x==y){//只能选 x 颜色
            vis[x]=1;
            continue;
        }
        add(x,y);
        add(y,x);
        ++in[x],++in[y];
    }
    for(int i=mn;i<=mx;i++){
        if(!vis[i]&&in[i]==1){
            q.push(i);
        }
    }
    while(!q.empty()){
        int u=q.front();q.pop();
        for(int i=fir[u];i;i=nex[i]){
            if(used[i/2])continue;
            int v=to[i];
            if(in[v]){
                used[i/2]=1;
                --in[v];
                vis[u]=1;
                if(!vis[v]&&in[v]==1){
                    q.push(v);
                }
                break;
            }
        }
    }
    for(int i=mn;i<=mx;i++)
        if(vis[i]||in[i])++ans;//剩下度不为 0 的点均可选
    printf("%d",ans);
    return 0;
}
```

---

## 作者：FrozenDream (赞：1)

### 思路：
将 $a_i$，$b_i$ 视作 $a_i$ 和 $b_i$ 连一条双向边。这样问题就是对于每条边只可以选择一个点，让选中的点最多。

考虑每个联通块。设联通块点数为 $n$，边数为 $m$，则 $m \ge n-1$。

若 $m=n-1$，即为一棵树，则一定可以选出 $n-1$ 个点。任意钦定一个点为根，每条边都选择作为儿子的那个点即可实现。

若 $m \ge n$，则一定可以选出 $n$ 个点。这种情况至少存在一个环，容易证明一定能选出 $n$ 个点。
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
vector<int>a[400005];
int n,u,v,f[400005],s,dsum,esum;
void dfs(int x) {
	f[x]=1;
	ans++;
	dsum++;
	for(int i=0; i<a[x].size(); i++) {
		esum++;
		if(f[a[x][i]]==0) {
			dfs(a[x][i]);
		}
	}
}
int main() {
	cin>>n;
	for(int i=1; i<=n; i++) {
		cin>>u>>v;
		a[u].push_back(v);
		a[v].push_back(u);
	}
	for(int i=1; i<=400000; i++) {
		if(f[i]==0&&a[i].size()!=0) {
			esum=0;
			dsum=0;
			dfs(i);
			s+=min(dsum,esum-dsum+1);
		}
	}
	cout<<s;
}
```


---

## 作者：CodingOIer (赞：0)

## [ARC111B] Reversible Cards 题解

### 思路分析

看着这个题的输入就很像一个图，所以我们先把图建出来试一试……

发现对于每一条边，其可以分配到其端点之一上。

扩展到树，假设其有 $n$ 个点，则它对答案的贡献为 $n - 1$，因为它只有 $n - 1$ 条边。

但对于一个简单环，假设其有 $n$ 个点，那么它绝对有 $n$ 条边。而且如果想在其上面增加点，则必须对应地增加边。

所以答案统计如下：

对于每一个大小为 $n$ 的联通块：

- 如果它包含一个环，则 $answer \gets answer + n$。
- 否则，$answer \gets answer + (n - 1)$。

注意，由于本题可能会有重边，所以请在第一次遍历到父亲边是将父亲设置为一个特殊的值来支持重边。（自环同理）

### 代码实现

```cpp
#include <cstdio>
#include <vector>
constexpr int MaxN = 4e5 + 5;
int n;
int answer;
bool back;
bool vis[MaxN];
std::vector<int> link[MaxN];
int dfs(int u, int f)
{
    if (vis[u])
    {
        back = true;
        return 0;
    }
    vis[u] = true;
    int size = 1;
    for (auto v : link[u])
    {
        if (v == f)
        {
            f = 0;
            continue;
        }
        size += dfs(v, u);
    }
    return size;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        link[u].push_back(v);
        link[v].push_back(u);
    }
    for (int i = 1; i <= 400000; i++)
    {
        if (link[i].size() == 0)
        {
            continue;
        }
        back = false;
        int size = dfs(i, 0);
        if (back)
        {
            answer += size;
        }
        else
        {
            answer += size - 1;
        }
    }
    printf("%d\n", answer);
    return 0;
}
```

---

## 作者：XiaoQuQu (赞：0)

考虑将 $a_i,b_i$ 之间连边，发现题目可以被转化为给定一个图，要求对于每条边将其一个顶点染色，问最多能将多少个点染色。

于是我们对于每个连通块分开来考虑。对于一个连通块，注意到我们不能将每个顶点染色当且仅当这个连通块是树，且此时可以染色的定点数量为连通块大小减一，如下：

1. 如果当前连通块是树，则我们可以固定一个点作为根节点，其余所有非根节点，用它连向父亲的那条边对他进行染色。
2. 如果当前连通块不是树，则我们可以求出他的一个生成树，以一个在环中的节点作为根节点，以 (1) 的方案将这个连通块除了这个根节点以外的点染色，接下来用这个环上的与根节点连接的非树边将这个根节点染色。

于是得证，时间复杂度 $O(n+V)$。

```cpp
const int MAXN = 4e5 + 5;
int n, a[MAXN], vis[MAXN], b[MAXN], sz[MAXN];
vector<int> G[MAXN];

bool dfs(int x, int fa) {
	vis[x] = true; sz[x] = 1;
	auto res = true;
	for (auto u:G[x]) {
		if (u == fa) continue;
		if (vis[u]) res = false;
		else res &= dfs(u, x), sz[x] += sz[u];
	}
	return res;
}

void work() {
	cin >> n;
	for (int i = 1; i <= n; ++i) {
        cin >> a[i] >> b[i];
		G[a[i]].push_back(b[i]);
		G[b[i]].push_back(a[i]);
	}
	int N = max(*max_element(a + 1, a + 1 + n), *max_element(b + 1, b + 1 + n)), ans = 0;
	for (int i = 1; i <= N; ++i) {
		if (vis[i]) continue;
		auto res = dfs(i, 0);
		if (res) ans += sz[i] - 1;
		else ans += sz[i];
	}
	cout << ans << endl;
}
```

---

## 作者：harmis_yz (赞：0)

## 分析

考虑建图。

对于 $(A_i,B_i)$，将图上节点 $A_i,B_i$ 之间连边。然后答案就是在每个连通块（需要保证连通块大小至少为 $2$）中每条边的两端取一个值，取出来不同的数量最大值。

对于一个连通块，如果其点数为 $n$，则边数 $m \ge n-1$。有 $2$ 种情况：

1. $m=n-1$，此时相当于在树上选 $n-1$ 个点，使任意一点为树根都有每条边取儿子时最优（必能取 $n-1$ 个不同的点）。

2. $m \ge n$，此时必有 $1$ 个以上的环，环外点相当于若干棵树，环内点必能取完，即一共能取 $n$ 个不同的点。

然后就是乱搞。离散化之后用启发式每次合并 $A_i,B_i$ 的集合，并更新集合中的边的数量即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define re register
#define il inline
#define PII pair<int,int>
#define x first
#define y second

il int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();}
	while(ch>='0'&&ch<='9') x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	return x*f;
}

const int N=2e5+10;
int n;
struct ed{
	int a,b;
}s[N];
int B[N<<1],id[N<<1],len;
struct dsu{
	int edge;
	vector<int> v;
	il int size(){return v.size();}
}sub[N<<1];

il void solve(){
	n=read();int ans=0;
	for(re int i=1;i<=n;++i) 
		s[i]={read(),read()},
		B[++len]=s[i].a,B[++len]=s[i].b;
	sort(B+1,B+len+1),len=unique(B+1,B+len+1)-(B+1);
	for(re int i=1;i<=n;++i) s[i]={lower_bound(B+1,B+len+1,s[i].a)-B,lower_bound(B+1,B+len+1,s[i].b)-B};
	for(re int i=1;i<=len;++i) id[i]=i,sub[i].v.push_back(i);
	for(re int i=1;i<=n;++i){
		int x=id[s[i].a],y=id[s[i].b];
		if(sub[x].size()>sub[y].size()) swap(x,y);
		++sub[y].edge;
		if(x==y) continue;
		for(re int j=0;j<sub[x].v.size();++j) sub[y].v.push_back(sub[x].v[j]),id[sub[x].v[j]]=y;
		sub[y].edge+=sub[x].edge;
	}
	for(re int i=1;i<=len;++i){
		if(id[i]==i)
			if(sub[i].edge==sub[i].size()-1) ans+=sub[i].size()-1;
			else ans+=sub[i].size();
	}
	printf("%lld\n",ans);
	return ;
}

signed main(){
	solve();
	return 0;
}
```
双倍经验：[種類数 β](https://www.luogu.com.cn/problem/AT_chokudai_S002_k)。

---

## 作者：do_it_tomorrow (赞：0)

[更好的阅读体验](https://www.doittomorrow.xyz/post/arc111b-reversible-cards-de-ti-jie/)
## 题目大意
有 $n$ 卡片在桌子上，每张卡牌正反两面分别有一个颜色。第 $i$ 牌的正面的颜色为 $a_i$，背面为 $b_i$。

对于每张牌，可以选择正面或者背面朝上。所有可能的情况中出现的不同的颜色的数量的最大值。
## 思路
考虑建图，将 $a_i$ 与 $b_i$ 连边。如果一个联通块内有环则整个联通块都可以选择，否则有 $1$ 个点将被舍弃。

因为如果出现环的情况，换上的所有点都可以通过自己一侧的边被选择，而因为环上的点全部都自给自足了，所有从环外连到环内的点都可以由向环内连接的那条进行选择。

具体来说，假设一个联通块如图所示：

![https://cdn.luogu.com.cn/upload/image_hosting/ztu6usk9.png](https://cdn.luogu.com.cn/upload/image_hosting/ztu6usk9.png)

那么 $1,2,3,4,5$ 号在环上的节点均可以通过环上的边 $\texttt{a},\texttt{b},\texttt{c},\texttt{d},\texttt{e}$ 进行选择。

而因为这些环上的节点均已经通过环上的边进行选择，那么 $6,7,8$ 号节点就可以通过他们向环的方向连的边 $\texttt{f},\texttt{g},\texttt{h}$ 进行选择。

对于不存在环的情况，如下图：

![https://cdn.luogu.com.cn/upload/image_hosting/80ofweul.png](https://cdn.luogu.com.cn/upload/image_hosting/80ofweul.png)

$8,2,3,4,5,6,7$ 号节点均可以通过 $\texttt{h},\texttt{b},\texttt{c},\texttt{e},\texttt{f},\texttt{g}$ 进行选择。

而 $1$ 号节点则无边可用，自然就被舍弃了。
## AC Code
```c++
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=4e5+6;
int n,m,ans,cnt,flag;
bool vis[N];
vector<int> v[N];
void dfs(int x,int fa){
	cnt++;
	for(int i:v[x]){
		if(i!=fa&&vis[i]){
			flag=0;
		}
		if(!vis[i]){
			vis[i]=1;
			dfs(i,x);
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin>>m;
	for(int i=1,x,y;i<=m;i++){
		cin>>x>>y;
		v[x].push_back(y);
		v[y].push_back(x);
		n=max({n,x,y});
	}
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			vis[i]=1;
			flag=1,cnt=0;
			dfs(i,0);
			ans+=cnt-flag;
		}
	}
	cout<<ans<<'\n';
	return 0;
}
```

---

## 作者：f_hxr_ (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_arc111_b)[ AT 传送门](https://atcoder.jp/contests/arc111/tasks/arc111_b)

[双倍经验](https://www.luogu.com.cn/problem/AT_chokudai_S002_k)

我们给颜色之间连边。

则题意变为：给定 $N$ 条边，每条边**必须且仅能**选择一个它的其中一个端点，求最多能选择多少点。

当然，这条边的另一个端点也可以被其他点选择。

### 分析

考虑对每个连通块分别求解。

设当前处理的连通块的大小为 $N$。如果连通块是一棵树，那么答案就是 $N-1$。

为什么呢？因为 $N$ 个点的树只有 $N-1$ 条边，而一条边最多选一个点。

构造方法也很简单，随便找一个点作为根，化无根树为有根树，每条边选择儿子节点，这样就只有根节点没有被选择。

就像下面这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/jc3y62zb.png)

如果连通块不是树呢？

如果不是树，那么它肯定有环。原因很简单，在一棵树上加一条非树边后，这条边的两个端点之间，既有原来在树上的路径，也有加的这条边本身，自然就形成了一个环。

诶？既然多了一条边，那么它能不能把原来树上的根节点给选了呢？

当然可以。因为根节点是随便选的，我们在环上随便找一个点为根，再随便断开一条连接根的环上边，处理完后把被断掉的环上边加回来，祖先节点就能被选了。

就像下面这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/1ifukoha.png)

![](https://cdn.luogu.com.cn/upload/image_hosting/qfn6h538.png)

如果多出来几条边就更好办了，多出来边就意味着能多选择一些点，何乐而不为呢？~~当然重边除外。~~

当然，因为所有点都能被选上，该连通块的答案就是 $N$。

这样，我们只需要判断一个连通块是否有环即可。

你或许第一时间想到了 DFS，当然可以这样做。你也可以用并查集，一边判环一边合并。这里我用的并查集。

[AC ](https://www.luogu.com.cn/record/155193324)代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
const int maxn=200005;
int N,cnt,ans;
int f[maxn<<1],sz[maxn<<1],OOO[maxn<<1];//图 上 有 原 吗 
int getf(int v){if(f[v]==v)return v;return f[v]=getf(f[v]);}
unordered_map<int,int>mp;
int main(){
	scanf("%d",&N);
	for(int i=1;i<=N*2;i++)f[i]=i,sz[i]=1;
	for(int i=1;i<=N;i++){
		int u,v,fu,fv;scanf("%d %d",&u,&v);
		if(!mp[u])mp[u]=++cnt;
		if(!mp[v])mp[v]=++cnt;
		u=mp[u];v=mp[v];
		fu=getf(u);fv=getf(v);
		if(fu==fv){OOO[fu]=1;}
		else{sz[fu]+=sz[fv];f[fv]=fu;OOO[fu]|=OOO[fv];}
	}
	for(int i=1;i<=cnt;i++){
		if(f[i]!=i)continue;
		ans+=sz[i]-1;
		if(OOO[i])++ans;
	}
	printf("%d",ans);
	return 0;
}
```

---

