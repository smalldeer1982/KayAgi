# Tree with Small Distances

## 题目描述

给定一颗有根树（根节点为 $1$）。要求往树中加入一些边使得从根节点到其他节点的距离至多是 $2$。 求加入边的最小数量。(边全部都是无向的)

## 说明/提示

$2 \le n \le 2\times 10^5$

## 样例 #1

### 输入

```
7
1 2
2 3
2 4
4 5
4 6
5 7
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
1 2
1 3
2 4
2 5
3 6
1 7
```

### 输出

```
0
```

## 样例 #3

### 输入

```
7
1 2
2 3
3 4
3 5
3 6
3 7
```

### 输出

```
1
```

# 题解

## 作者：leozhang (赞：10)

一个看起来就不对的贪心居然是正解...

但仔细思考一下，这种贪心倒的确找不到反例..

贪心思想：每次找出离根节点最远的点，然后由根节点向这个点的父节点连边，一直连到所有点都能被覆盖即可，这样构造出的一定是一个可行的最优解

正确性证明（个人YY）：

主要是要证明这种做法的最优性：

首先，由于所有点都要求被覆盖，自然离根节点最远的点也不例外

那么，如果想覆盖上离根节点最远的点，只会有两种覆盖方法：一种是将根节点与这个点本身相连，另一种是将根节点与这个点的父节点相连

不难发现，将根节点与这个点的父节点相连，这样的方案一定不会差

证明：假设这个父节点还有别的子节点，那么与父节点相连后这些子节点都能被覆盖，这样一定是更优的

而即使这个父节点没有别的子节点，他还有自己的父节点，这样连边也能减少根节点与他的父节点的距离，也会达到更好的效果

即使上面两点都没有起作用，至少这样还可以覆盖上最远的点，也并不会使代价增大，所以这样做是完全可行的。

这样就完事了

（ps：树上bfs真好用）

```cpp
#include <cstdio>
#include <cmath>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;
struct Edge
{
	int next;
	int to;
}edge[400005];
bool used[200005];
int head[200005];
int f[200005];
int n;
int cnt=1;
void init()
{
	memset(head,-1,sizeof(head));
	cnt=1;
}
void add(int l,int r)
{
	edge[cnt].next=head[l];
	edge[cnt].to=r;
	head[l]=cnt++;
}
struct node
{
	int num;
	int dep;
}p[200005];
void bfs(int rt)
{
	queue <int> M;
	p[rt].dep=0;
	p[rt].num=rt;
	M.push(rt);
	while(!M.empty())
	{
		int u=M.front();
		M.pop();
		for(int i=head[u];i!=-1;i=edge[i].next)
		{
			int to=edge[i].to;
			if(p[to].dep)
			{
				continue;
			}
			p[to].dep=p[u].dep+1;
			p[to].num=to;
			f[to]=u;
			M.push(to);
			if(p[to].dep<=2)
			{
				used[to]=1;
			}
		}
	}
}
bool cmp(node a,node b)
{
	return a.dep>b.dep;
}
int main()
{	
	scanf("%d",&n);
	init();
	for(int i=1;i<n;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	bfs(1);
	sort(p+1,p+n+1,cmp);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		if(used[p[i].num])
		{
			continue;
		}
		ans++;
		int u=f[p[i].num];
		used[u]=1;
		for(int j=head[u];j!=-1;j=edge[j].next)
		{
			int to=edge[j].to;
			used[to]=1;
		}
	}
	printf("%d\n",ans);
	return 0;
}

```

---

## 作者：Owen_codeisking (赞：6)

今天模拟赛第一题$CodeForces$原题打挂了，爆了只剩$10$分

前排$orz$ @$jszjinshengzhi$贪心秒了此题

非常自然的想法，首先建个堆，每次把深度最大的点取出来，把它周围一圈都标记一下，打过标记的点就不用弄了

当然，深度$\leq 2$的点就不用加进去了

时间复杂度$O(n\ log\ n)$

$Code\ Below:$
```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn=200000+10;
int n,head[maxn],to[maxn<<1],nxt[maxn<<1],tot;
int dep[maxn],vis[maxn],dg[maxn],fa[maxn],ans;
 
priority_queue<pair<int,int> > pq;

inline int read(){
    register int x=0,f=1;char ch=getchar();
    while(!isdigit(ch)){if(ch=='-')f=-1;ch=getchar();}
    while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
    return (f==1)?x:-x;
}
inline void add(int x,int y){
    to[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}

void dfs(int x,int f){
    for(int i=head[x],y;i;i=nxt[i]){
        y=to[i];
        if(y==f) continue;
        dep[y]=dep[x]+1;
        fa[y]=x;
        dfs(y,x);
    }
}

int main()
{
    n=read();
    int x,y;
    for(int i=1;i<n;i++){
        x=read(),y=read();
        add(x,y);add(y,x);
    }
    dfs(1,0);
    for(int i=1;i<=n;i++)
        if(dep[i]>2) pq.push(make_pair(dep[i],i));
    int u,v;
    while(!pq.empty()){
        u=pq.top().second,pq.pop();
        if(vis[u]) continue;
        u=fa[u];vis[u]=1;
        for(int i=head[u];i;i=nxt[i])
            vis[to[i]]=1;
        ans++;
    }
    printf("%d\n",ans);
    return 0;
}
```

---

## 作者：2huk (赞：3)

给定一颗 $n$ 个节点的树，以 $1$ 为根。

求最少在树中加几条边，使得任意一点到 $1$ 的距离均小于等于 $2$。

---

不难发现最优策略中，每条加的边都有端点 $1$。

第一步，最自然的想法就是将 $1$ 和**最深**的叶节点连边。其实不然，最优的策略是连接 $1$ 和叶子节点的父亲。这样能把这个叶子节点的所有兄弟和它父亲的父亲都管控到。

接下来上一步的点就不需要考虑了。我们要做的仍然是连接 $1$ 和最深的点的父亲。如此迭代即可。

实现上，我们可以维护大根堆，以节点的深度从大到小排序。每次取出堆顶即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

//#define int long long
typedef long long ll;
typedef unsigned long long LL;
typedef pair<int, int> PII;

struct FASTREAD {
	template <typename T>
	FASTREAD& operator >>(T& x) {
		x = 0; bool flg = false; char c = getchar();
		while (c < '0' || c > '9') flg |= (c == '-'), c = getchar();
		while (c >= '0' && c <= '9') x = (x << 3) + (x << 1) + c - '0', c = getchar();
		if (flg) x = -x; return *this;
	}
	template <typename T>
	FASTREAD& operator >>(vector<T>& x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) >> *it;
		return *this;
	}
}fin;

struct FASTWRITE {
	template <typename T>
	FASTWRITE& operator <<(T x) {
		if (x < 0) x = -x, putchar('-');
		static int buf[35]; int top = 0;
		do buf[top ++ ] = x % 10, x /= 10; while (x);
		while (top) putchar(buf[ -- top] + '0');
		return *this;
	}
	FASTWRITE& operator <<(char x) {
		putchar(x); return *this;
	}
	template <typename T>
	FASTWRITE& operator <<(vector<T> x) {
		for (auto it = x.begin(); it != x.end(); ++ it ) (*this) << *it, putchar(' ');
		putchar('\n');
		return *this;
	}
}fout;

const int N = 1e6 + 10;
const int P = 998244353;

int n;
vector<int> g[N];
int dep[N];
bool st[N];
int fa[N];

void dfs(int u, int f) {
	fa[u] = f;
	for (int v : g[u]) if (v != f) {
		dep[v] = dep[u] + 1;
		dfs(v, u);
	}
	return;
}

void Luogu_UID_748509() {
	fin >> n;
	for (int i = 1; i < n; ++ i ) {
		int x, y; fin >> x >> y;
		g[x].push_back(y);
		g[y].push_back(x);
	}
	dep[1] = 1;
	int res = 0;
	dfs(1, -1);
	priority_queue<PII> q; 
	for (int i = 1; i <= n; ++ i ) if (dep[i] > 3) q.push({dep[i], i});
	while (q.size()) {
		int u = q.top().second; q.pop();
		if (st[u]) continue;
		u = fa[u];
		st[u] = true;
		for (int v : g[u]) {
			st[v] = true;
		}
		++ res;
	}
	fout << res;
}

signed main() {
	int Testcases = 1;
//	fin >> Testcases;
	while (Testcases -- ) Luogu_UID_748509();
	return 0;
}
```

---

## 作者：封禁用户 (赞：2)

根对一个点连边，那么这个点的邻居到根节点的距离为 $2$。那么一个很显然的贪心是给叶子节点的父亲上标记。然后删掉父亲节点的所有邻居和父亲。显然，对于每个节点，我们都给予了必要的代价。每个点都必须被标记，先后顺序其实也并不重要了。

具体的实现：按深度降序排序，深度 $\le 2$ 的肯定不需要标记。那么我们每次取出深度最大的那个点，用那个点的父亲过掉它的兄弟和祖父。

复杂度 $O(n)$。

---

## 作者：_edge_ (赞：2)

来一发简单的 DP 做法。

我比较傻，不太明白这些神仙贪心做法，怎么办呢？欸其实有更加好想的 DP 做法。

首先，我们如果忽略掉根节点和根节点以下深度 $2$ 的节点，那么我们连一条边就相当于是标记了一个点。

标记了之后，对于他的父亲儿子，也就是距离他 $1$ 的点都会被覆盖掉。

然后这个是经典的树形 DP，非常套路的设状态是 $f_{i,0/1/2}$ 表示他被自己儿子父亲覆盖掉。

然后我们对他进行分类讨论，对于被自己覆盖的，对于儿子来说，没啥影响，儿子可以随便选择，因此取最小的那个。

对于儿子覆盖的，我们会发现只需要有一个儿子被标记即可，设儿子是 $v$，那么我们需要加上的即为 $\min(f_{v,0},f_{v,1})$，如果是前者最好，这样直接被覆盖了，如果是后者的话就有点小麻烦，每次都出现后者的话就选择一个儿子使得 $f_{v,0}$ 和 $f_{v,1}$ 的差值最小即可。

对于父亲覆盖的，那么儿子一定要被自己或者自己的儿子覆盖。

然后我们再来考虑根节点的贡献，简单的想法就是把他到深度为 $1$ 的地方点权都设为 $0$，然后对于深度为 $2$ 的，必然存在一种最优决策使得他被深度为 $1$ 的点覆盖。

总时间复杂度是 $O(n)$ 的。

```cpp
#include <iostream>
#include <cstdio>
using namespace std;
const int INF=2e5+5;
int n;
struct _node_edge{
	int to_,next_;
}edge[INF<<1];
int head[INF],tot,a[INF],f[INF][5],vis[INF];
void add_edge(int x,int y) {
	edge[++tot]=(_node_edge){y,head[x]};
	head[x]=tot;return ; 
}
// f[x][0/1/2] 被自己，儿子，父亲覆盖 
void DFS(int x,int fa,int d) {
	if (d>1) a[x]=1,vis[x]=0;
	else a[x]=0,vis[x]=1;
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		if (v==fa) continue;
		DFS(v,x,d+1);
	}
	return ;
}
void DFS1(int x,int fa) {
	f[x][0]=a[x];f[x][1]=f[x][2]=0;
	int sum=1e9;
	for (int i=head[x];i;i=edge[i].next_) {
		int v=edge[i].to_;
		if (v==fa) continue;
		DFS1(v,x);
		f[x][2]+=min(f[v][0],f[v][1]);
		f[x][0]+=min(min(f[v][1],f[v][0]),f[v][2]);
		if (f[v][1]>f[v][0]) f[x][1]+=f[v][0],sum=0;
		else f[x][1]+=f[v][1],sum=min(sum,f[v][0]-f[v][1]);
	}
	f[x][1]+=sum;
//	cout<<x<<" "<<f[x][0]<<" "<<f[x][1]<<" "<<f[x][2]<<" yiw\n";
	return ;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin>>n;
	for (int i=1;i<n;i++) {
		int x=0,y=0;cin>>x>>y;
		add_edge(x,y);add_edge(y,x);
	}
	DFS(1,0,0);
	DFS1(1,0);
	cout<<min(f[1][0],f[1][1])<<"\n"; 
	return 0;
}
```


---

## 作者：zhenglier (赞：2)

看到题解里的大佬都是用贪心切掉这道题的，但小蒟蒻不会贪心，只能用树形DP

我们设

$dp[i][0]$为不选$i$向根节点建边但以$i$为根的子树（包括$i$）都被覆盖的最小费用

$dp[i][1]$为选$i$向根节点建边且以$i$为根的子树都被覆盖的最小费用

$dp[i][2]$为不选$i$向根节点建边但以$i$为根的子树（**不**包括$i$）都被覆盖的最小费用

然后我们可以愉悦的列出DP方程

$dp[i][1]=1+\sum_{j}^{j\in son_i}min(dp[j][0],dp[j][1],dp[j][2])$  
如果选这个点，它的儿子的状态就无关了，取最小值就可以了。

$dp[i][2]=\sum_j^{j\in son_i}dp[j][0]$

如果这个点不选且要使这个点不被覆盖，就只能取它的儿子的0状态更新。

这两条方程还是比较好推的。主要是0状态比较难转移。

我们可以分类，若他的儿子中有一个点$j$满足$dp[j][1]<dp[j][0]$，就有

$dp[i][0]=\sum_{j}^{j\in son_i}min(dp[j][0],dp[j][1])$ 

注意这里不能用儿子的2状态转移，这会导致那个点不被覆盖

但如果没有儿子满足，我们可以在他的儿子中找一个点$k$，使$dp[k][1]-dp[k][0]$最小，然后使

$dp[i][0]=\sum_{j}^{j\in son_i}dp[j][0]\qquad +dp[k][1]-dp[k][0]$

就行了 。

$\color{white}\text{如果你看到了这句话，就注意一下，如果当前点的深度小于等于1，那就不必在dp[i][1]上加一}$

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
int tot,bian[400010],nxt[400010],head[200010];
int v[200010];
inline int read(){
	register char c;register int ret=0;
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(;c>='0'&&c<='9';ret=(ret<<1)+(ret<<3)+c-'0',c=getchar());
	return ret;
}
inline void add(int x,int y){
    ++tot;bian[tot]=y;nxt[tot]=head[x];head[x]=tot;
}
int dp[200010][3];
void dfs1(int x,int f,int d){
	for(int i=head[x];i;i=nxt[i]){
		if(bian[i]==f)continue;
		dfs1(bian[i],x,d+1);
	}
	for(int i=head[x];i;i=nxt[i]){
		if(bian[i]==f)continue;
		dp[x][1]+=min(min(dp[bian[i]][0],dp[bian[i]][2]),dp[bian[i]][1]);
		if(dp[x][2]<1e9)dp[x][2]+=dp[bian[i]][0];
	}
	int mn=1e9,b=0;
	for(int i=head[x];i;i=nxt[i]){
		if(bian[i]==f)continue;
		if(dp[bian[i]][1]<dp[bian[i]][0])dp[x][0]+=dp[bian[i]][1],b=1;
		else dp[x][0]+=dp[bian[i]][0];
 		mn=min(mn,dp[bian[i]][1]-dp[bian[i]][0]);
	}
	if(!b)dp[x][0]+=mn;
	if(d>1)dp[x][1]++;
}
int main()
{
//	freopen("traffic.in","r",stdin);
//	freopen("traffic.out","w",stdout);
	n=read();
	for(int i=1;i<n;++i){
		int x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	dfs1(1,0,0);
	cout<<min(dp[1][0],dp[1][1]);
}
```

---

## 作者：Frozencode (赞：2)

蒟蒻又一次水题解了...

首先我们看到这题范围，便知道肯定不能一个一个枚举，然后会想到贪心，如何保证连的边最少呢？

首先，我们肯定会想到先处理最远的节点，为了保证连的边尽可能少，我们便会想到连他的父亲和1号点。那么贪心方法自然就出来了：

每次寻找当前最远的节点，连1号点和他父亲节点，再更新他父亲节点所连接的点的距离（其父亲和其子孙），直到所得的图符合要求。

比赛时蒟蒻的我先跑了遍dijkstra，然后再不断贪心,莫名wa5...


调了半天也没调对...最后草草收场。

比赛结束之后问了下大佬,大佬说一开始dfs一遍就行了，遂重写了遍E。

AC代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 10;
int n, dep[MAXN], id[MAXN], fa[MAXN], ans;//id数组重新编号由深到浅的点。
bool cov[MAXN];
vector<int> e[MAXN];//邻接表存图。
void dfs(int x) {
    for(vector<int>::iterator i = e[x].begin(); i < e[x].end(); i++) 
    {
        if(*i == fa[x]) continue;
        dep[*i] = dep[fa[*i] = x] + 1; dfs(*i);
    }
}//dfs遍历整个图，获取每个点的深度和其父亲节点。
void setCov(int x) {
    for(vector<int>::iterator i = e[x].begin(); i < e[x].end(); i++)cov[*i] = true;
    cov[x] = true;
}//新增边后更新其附近节点。
bool cmp(int a, int b) {
    return dep[a] > dep[b];
}//由深到浅，方便贪心。
int main() {
    scanf("%d", &n);
    for(int i = 1; i < n; i++) {
        int u, v; scanf("%d%d", &u, &v);
        e[u].push_back(v); e[v].push_back(u);
    }//存图。
    dfs(1);//遍历。
    for(int i = 1; i <= n; i++) if(dep[i] <= 2) cov[i] = true;//更新整个图。
    for(int i = 1; i <= n; i++) id[i] = i;
    sort(id + 1, id + n + 1, cmp);
    for(int i = 1, j; j = id[i]; i++)
        if(!cov[j]) 
        {
            ans++; setCov(fa[j]);
        }//不断贪心直到符合题意。
    printf("%d\n", ans);
}
```

---

## 作者：Graph_Theory (赞：0)

### 思路

每一条新的边显然要连接根节点，若连接的为非根节点，此时距根节点一定为2，若连接根节点，此时该点距根节点为一，可以拓展至该节点的儿子节点及父节点（距离为二）此时连接根节点优于连接非根节点。

其次，若有一点不符合条件，则分两种情况。

从最深向上访问。

若当前点未访问此时该点的父亲节点一定也未访问，该父节点的父节点有可能未访问，该点的兄弟节点有可能未访问，该节点的儿子节点因为访问顺序要优先于该节点，所以符合要求的。

连接该节点的话此时该点及其父节点被访问，若连接的是该点的父节点，则该节点的父节点及该节点被访问，且有可能会连接该节点的兄弟节点。

所以连接该点的儿子节点一定优于直接连接该点。

从上向最深访问同理。

从最深往浅和从浅往深基本没区别，从浅往深要记录儿子节点是谁，父亲节点是谁。从最深往浅记录父亲节点就可以。为了节省空间，我选择从最深往浅。

最后就是深搜计算每一个点的深度，排序之后从最深节点开始往浅的节点计算就可以。

### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int maxn=2e5+10;
int n,dep[maxn],numb[maxn],fa[maxn],ans;
bool cov[maxn];
vector<int> e[maxn];
void dfs(int x) 
{
	int siz=e[x].size();
	for(int i=0;i<siz;i++) 
	{
		if(e[x][i]!=fa[x])
		{ 
			fa[e[x][i]]=x;
			dep[e[x][i]]=dep[fa[e[x][i]]]+1; 
			dfs(e[x][i]);
		}
	}
}

bool cmp(int a,int b){return dep[a]>dep[b];}
signed main()
{
	cin>>n;
	for(int i=1;i<n;i++) 
	{
		int u,v; 
		cin>>u>>v;
		e[u].push_back(v); 
		e[v].push_back(u);
	}
	dfs(1);
	for(int i=1;i<=n;i++) numb[i]=i;
	sort(numb+1,numb+n+1,cmp);
	for(int i=1;i<=n;i++)
		if(dep[i]<=2)
			cov[i]=true;
	for(int i=1,j;j=numb[i];i++)
		if(!cov[j]) 
		{
			ans++;
			int siz=e[fa[j]].size();
			for(int i=0;i<siz;i++) cov[e[fa[j]][i]]=true;
			cov[fa[j]]=true;
		}
	cout<<ans;
}
```

---

## 作者：_Day_Tao_ (赞：0)

看到题之后想到的就是 DP，根本没往贪心上去想（

我们定义覆盖为到根节点的距离小于等于 $2$。首先有个容易得出的结论就是，**从根节点往下连进行覆盖肯定是最优的**。考虑对于那些本来无法被覆盖的点如何被覆盖，只有父亲节点、儿子节点向根节点连边覆盖它，或者它自己向根节点连边。这样我们就容易得出 DP 状态：设 $f_{u,0/1/2}$ 表示 $u$ 节点自己向根节点连边，被儿子节点覆盖，被父亲节点覆盖所要加的最小边数。这样就不难得出转移柿子：

$$\begin{cases}
  f_{u,0}=\sum\limits_{v\in son_u}\min\{f_{v,0},f_{v,1},f_{v,2}\}\\
  f_{u,1}=
  \begin{cases}
    \forall v\in son_u,f_{v,1}\ge f_{v,0} & \min\limits_{v\in son_u}\{f_{v,0}-f_{v,1}\}+\sum\limits_{v\in son_u}\min\{f_{v,0},f_{v,1}\}\\
    \operatorname{otherwise} & \sum\limits_{v\in son_u}\min\{f_{v,0},f_{v,1}\}
  \end{cases}\\
  f_{u,2}=\sum\limits_{v\in son_u}\min\{f_{v,0},f_{v,1}\}
\end{cases}$$

答案就是：

$$\sum\limits_{depth_v=2}\min\{f_{u,0},f_{u,1},f_{u,2}\}$$

$f_{u,0}$ 和 $f_{u,2}$ 的转移还是比较显然的，对于 $f_{u,1}$ 的转移，考虑点 $u$ 要从儿子节点转移至少一次，所以对于 $\sum\limits_{v\in son_u}\min\{f_{v,0},f_{v,1}\}$ 没有取过 $f_{v,1}$ 的情况还要特判一下。

小清新代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define SZ(a) ((int)(a).size())
const int N = 2e5+5;
int n,f[N][3],ans;
vector<int>e[N];
void dfs(int u,int fa,int dep)
{
	int minn=n+1,fl=0;f[u][0]=1;
	if(SZ(e[u])==1)f[u][1]=n+1;
	for(int v:e[u])
	{
		if(v==fa)continue;dfs(v,u,dep+1);
		f[u][0]+=min(f[v][0],min(f[v][1],f[v][2]));
		if(f[v][1]>=f[v][0])fl=1;else minn=min(minn,f[v][0]-f[v][1]);
		f[u][1]+=min(f[v][1],f[v][0]),f[u][2]+=min(f[v][0],f[v][1]);
	}
	if(!fl)f[u][1]+=minn;
	if(dep==2)ans+=min(min(f[u][0],f[u][1]),f[u][2]);
}
signed main()
{
	scanf("%d",&n);
	for(int i=1,u,v;i<n;i++)scanf("%d%d",&u,&v),e[u].push_back(v),e[v].push_back(u);
	dfs(1,0,0),printf("%d\n",ans);
	return 0;
}
```

---

## 作者：OIer_ACMer (赞：0)

# 题目解析：

这道题作为一道从树开始的题目，很明显要用树的知识。由于本道题要求的是最少加多少条边，所以，我们从树形动态规划考虑。

通过纸上枚举，我们可以发现，对于根节点到任意一个节点，其**距离就是每个点的深度**，那么，我们连一条边从根节点到 $x$ 节点，那么与 $x$ 距离为 $1$ 的点都会被覆盖（满足要求），因此，这道题就被我们转化为了选一些点使所有点满足距离为 $1$。

我们的动态规划数组对于每个点有三种情况，$0$ 和 $1$ 表示的是目前已经延伸到了 $i$ 点，是否在往上延伸，至于 $2$ 表示还没有延到 $i$ 点，需要父亲来延伸。

我们分三种情况讨论，一种是状态为 $0$ 的情况，这种情况我们**直接将前面所有状态为 $1$ 或 $0$ 的答案取最小值就行了**，毕竟 $0$ 状态只用保存最小答案，别的不用管，毕竟不用建边。情况 $2$ 同理。第二种是选择往上延伸，也很简单，只用在 $0$ 状态的基础上加 $1$，因为我们往上路径长度加 $1$。

# 代码如下：

```

#include <bits/stdc++.h>
using namespace std;
int n;
struct node
{
    int to, next, w;
} edge[1000009];
int head[1000009], cnt;
void add(int u, int v, int w)
{
    edge[++cnt].to = v;
    edge[cnt].next = head[u];
    edge[cnt].w = w;
    head[u] = cnt;
}
int dp[1000009][3];
int ans = 0;
void dfs(int x, int fa, int dep)
{
    int siz = 0;
    for (int i = head[x]; i; i = edge[i].next)
    {
        int y = edge[i].to;
        if (y == fa)
        {
            continue;
        }
        siz++;
        dfs(y, x, dep + 1);
    }
    if (siz == 0)
    {
        dp[x][2] = 0;
        dp[x][1] = 1;
        return;
    }
    if (dep > 2)
    {
        int ggg = 0;
        dp[x][0] = 0;
        for (int i = head[x]; i; i = edge[i].next)
        {
            int y = edge[i].to;
            if (y == fa)
            {
                continue;
            }
            if (dp[y][0] >= dp[y][1])
            {
                dp[x][0] += dp[y][1], ggg = 1;
            }
            else
            {
                dp[x][0] += dp[y][0];
            }
        }
        if (!ggg)
        {
            dp[x][0]++;
        }
        dp[x][1] = 1;
        dp[x][2] = 0;
        for (int i = head[x]; i; i = edge[i].next)
        {
            int y = edge[i].to;
            if (y == fa)
            {
                continue;
            }
            dp[x][1] += min(dp[y][0], min(dp[y][1], dp[y][2]));
            dp[x][2] += min(dp[y][0], dp[y][1]);
        }
        if (dep == 3)
        {
            ans += min(dp[x][0], min(dp[x][1], dp[x][2]));
        }
    }
}
int main()
{
    cin >> n;
    for (int i = 1; i < n; i++)
    {
        int u, v;
        cin >> u >> v;
        add(u, v, 1);
        add(v, u, 1);
    }
    memset(dp, 0x3f, sizeof(dp));
    dfs(1, -1, 1);
    cout << ans << endl;
    return 0;
}

```

---

## 作者：FL_sleake (赞：0)

### 题意简述

给定一颗有根树（根节点为 $1$）。要求往树中加入一些边使得从根节点到其他节点的距离至多是 $2$。求加入边的最小数量。(边全部都是无向的)

### 解题思路

还是采用贪心的思路。

对于一个到根节点的距离大于 $2$ 的叶子节点，我们只有两种方法使它到根节点的距离小于等于 $2$，要么直接连它和根节点，要么连接它的父亲和根节点。比较显然的是，如果连接它的父亲和根节点，一定不劣于连接它和根节点。

然后接下来这一步和其他题解说的都不太一样。大部分题解在得出贪心的策略后是把所有点按深度排序，然后开始贪心。但是根据我们上面推出的东西，我们只需要保证每次处理的是叶子节点就可以，这启示我们使用拓扑排序。

具体地，先 dfs 一遍求出每个点的父亲，然后进行拓扑排序，将拓扑排序的结果记录下来，进行贪心即可。

由于不需要排序，所以时间复杂度其实是优于其他题解所述的贪心。

### 代码示例

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,vis[200010],ans=0,du[200010],fa[200010],num[200010],cnt=0;
vector<int> G[200010];
void dfs(int u,int Fa){
	fa[u]=Fa;
	for(int v:G[u]) if(v!=Fa) dfs(v,u);
}
signed main(){
	cin>>n;
	for(int i=1;i<=n-1;i++){
		int u,v;
		cin>>u>>v;
		G[u].push_back(v);
		G[v].push_back(u);
		du[u]++,du[v]++;
	}
	dfs(1,0);//找父亲
	vis[1]=1;
	for(int u:G[1]){
		vis[u]=1;
		for(int v:G[u]) vis[v]=1;
	}
    //把根节点周围先标记了
	queue<int> q;
	for(int i=1;i<=n;i++) if(!vis[i]&&du[i]==1) q.push(i);
	while(!q.empty()){
		int u=q.front();q.pop();
		num[++cnt]=u;
		for(int v:G[u]){
			du[v]--;
			if(du[v]==1) q.push(v);
		}
	}
    //拓扑
	for(int i=1;i<=cnt;i++){
		int u=num[i];
		if(vis[u]) continue;
		vis[fa[u]]=1;
		ans++;
		for(int v:G[fa[u]]) vis[v]=1;
	}
    //贪心
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：傅思维666 (赞：0)

## 题解：

看到最优化想DP，没想出来。正解是贪心。

肯定深度深的最不好伺候，先把深度深的搞定了之后，一层一层再逼近根节点这么搞，肯定是更优秀的。

那怎么伺候深度深的呢？

假设现在深度深的点为$x$，如果直接连$x$，肯定不划算的。我们如果连上他的父亲$f$，那么肯定能使得更多的点符合条件。

于是贪心原则就出来了。感性认知是对的。

具体实现就是用堆来维护一个二元组，先处理深度打的节点，每次取出堆顶节点就打一圈标记。就解决了。

代码：

```cpp
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int maxn=2e5+5;
int n,ans;
int tot,head[maxn],nxt[maxn<<1],to[maxn<<1];
int deep[maxn],fa[maxn];
bool v[maxn];
priority_queue<pair<int,int> >q;
void add(int x,int y)
{
    to[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
void dfs(int x,int f)
{
    deep[x]=deep[f]+1;
    fa[x]=f;
    if(deep[x]>2)
        q.push(make_pair(deep[x],x));
    for(int i=head[x];i;i=nxt[i])
    {
        int y=to[i];
        if(y==f)
            continue;
        dfs(y,x);
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y);
        add(y,x);
    }
    deep[0]=-1;
    dfs(1,0);
    while(!q.empty())
    {
        int x=q.top().second;
        q.pop();
        if(v[x])
            continue;
        int f=fa[x];
        v[f]=1;
        for(int i=head[f];i;i=nxt[i])
        {
            int y=to[i];
            v[y]=1;
        }
        ans++;
    }
    printf("%d",ans);
    return 0;
}
```



---

## 作者：Bring (赞：0)

[更好的阅读体验请点这里](https://www.cnblogs.com/BrianPeng/p/12284707.html)

## 核心思想：贪心

先将树转化为以$1$为根的有根树

考虑如果想要连上一个点$u$，并且$u$的所有子树都已经通过其他方式连上了

那么就有三种方法：

1. 连上$u$自己，那么可以顺势连上$u$的父亲$f_u$

2. 连上$u$的一个儿子，那么除了连上$u$以外没有任何效果

3. 连上$u$的父亲$f_u$，那么$f_u$的所有儿子都可以顺带连上

综上，连上$f_u$是贪心最优的

给每一个点$u$一个深度$d_u$，其中$d_1=0$

为了保证$u$的所有子树都连上，可以建以$d_u$为键值的大根堆，把所有$d_u>2$的$u$丢进去

每次弹出一个$u$，就把$f_u$连上，即将$f_u$及其周围的点打上标记

如果弹出的$u$打过了标记，直接忽略即可

**Time complexity: $O(n\log n)$**

**Memory complexity: $O(n)$**

细节见代码（$2.82$s / $17.77$MB）
```cpp
//This program is written by Brian Peng.
#pragma GCC optimize("Ofast","inline","no-stack-protector")
#include<bits/stdc++.h>
using namespace std;
#define Rd(a) (a=read())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
int read(){
	register int x;register char c(getchar());register bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	if(c^'-')k=1,x=c&15;else k=x=0;
	while(isdigit(Gc(c)))x=(x<<1)+(x<<3)+(c&15);
	return k?x:-x;
}
void wr(register int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(register int i(a);i<(b);++i)
#define Frn1(i,a,b) for(register int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(register int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
#define N (200010)
int n,u,v,f[N],d[N],ans;
bool vs[N];
vector<int>e[N];
struct Cmp{bool operator()(int a,int b){return d[a]<d[b];}};
priority_queue<int,vector<int>,Cmp>q;
void dfs(int u);
signed main(){
	Rd(n);
	Frn0(i,1,n)e[Rd(u)].push_back(Rd(v)),e[v].push_back(u);
	dfs(1);
	while(!q.empty()){
		u=q.top(),q.pop();
		if(vs[u])continue;
		vs[f[u]]=1,++ans;
		for(int i:e[f[u]])vs[i]=1;
	}
	wr(ans),exit(0);
}
void dfs(int u){
	if(d[u]>2)q.push(u);
	for(int i:e[u])if(i!=f[u])f[i]=u,d[i]=d[u]+1,dfs(i);
}
```
---
## 接下来是优化部分

发现时间瓶颈在于堆操作是$O(\log n)$的

而且事实上根本不需要堆，因为只有在dfs时进行的push()操作，之后都是弹出

但是如果对$u$按照$d_u$排序，用sort()还是$O(n\log n)$的

其实如果要生成一个按$d_u$排序的序列有$O(n)$做法，那就是……

## BFS大法好！！！！！

BFS序就是一个按照$d_u$从小到大排序的序列

所以只要把$d_u>2$的BFS序记录下来，然后倒着做就可以了，其它操作不变

**Time complexity: $O(n)$**

**Memory complexity: $O(n)$**

细节见代码（$2.04$s / $10.11$MB）（效果不错）
```cpp
//This program is written by Brian Peng.
#pragma GCC optimize("Ofast","inline","no-stack-protector")
#include<bits/stdc++.h>
using namespace std;
#define Rd(a) (a=read())
#define Gc(a) (a=getchar())
#define Pc(a) putchar(a)
int read(){
	register int x;register char c(getchar());register bool k;
	while(!isdigit(c)&&c^'-')if(Gc(c)==EOF)exit(0);
	if(c^'-')k=1,x=c&15;else k=x=0;
	while(isdigit(Gc(c)))x=(x<<1)+(x<<3)+(c&15);
	return k?x:-x;
}
void wr(register int a){
	if(a<0)Pc('-'),a=-a;
	if(a<=9)Pc(a|'0');
	else wr(a/10),Pc((a%10)|'0');
}
signed const INF(0x3f3f3f3f),NINF(0xc3c3c3c3);
long long const LINF(0x3f3f3f3f3f3f3f3fLL),LNINF(0xc3c3c3c3c3c3c3c3LL);
#define Ps Pc(' ')
#define Pe Pc('\n')
#define Frn0(i,a,b) for(register int i(a);i<(b);++i)
#define Frn1(i,a,b) for(register int i(a);i<=(b);++i)
#define Frn_(i,a,b) for(register int i(a);i>=(b);--i)
#define Mst(a,b) memset(a,b,sizeof(a))
#define File(a) freopen(a".in","r",stdin),freopen(a".out","w",stdout)
#define N (200010)
int n,u,v,f[N],ans,s[N],sz;
bool vs[N];
struct Q{int u,d;}p;
vector<int>e[N];
queue<Q>q;
signed main(){
	Rd(n),q.push({1,0});
	Frn0(i,1,n)e[Rd(u)].push_back(Rd(v)),e[v].push_back(u);
	while(!q.empty()){
		p=q.front(),q.pop();
		if(p.d>2)s[++sz]=p.u;
		for(int i:e[p.u])if(i!=f[p.u])f[i]=p.u,q.push({i,p.d+1});
	}
	Frn_(i,sz,1){
		if(vs[s[i]])continue;
		vs[f[s[i]]]=1,++ans;
		for(int j:e[f[s[i]]])vs[j]=1;
	}
	wr(ans),exit(0);
}
```

---

