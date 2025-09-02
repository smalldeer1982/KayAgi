# 仓鼠找 sugar

## 题目描述

小仓鼠的和他的基（mei）友（zi）sugar 住在地下洞穴中，每个节点的编号为 $1\sim n$。地下洞穴是一个树形结构。这一天小仓鼠打算从从他的卧室（$a$）到餐厅（$b$），而他的基友同时要从他的卧室（$c$）到图书馆（$d$）。他们都会走最短路径。现在小仓鼠希望知道，有没有可能在某个地方，可以碰到他的基友？


小仓鼠那么弱，还要天天被 zzq 大爷虐，请你快来救救他吧！


## 说明/提示

**本题时限 1s，内存限制 128M，因新评测机速度较为接近 NOIP 评测机速度，请注意常数问题带来的影响。**


$20\%$ 的数据 $n, q\le200$。

$40\%$ 的数据 $n, q\le 2\times10^3$。

$70\%$ 的数据 $n, q\le 5\times10^4$。

$100\%$ 的数据 $1\le n, q\le10^5$。


## 样例 #1

### 输入

```
5 5
2 5
4 2
1 3
1 4
5 1 5 1
2 2 1 4
4 1 3 4
3 1 1 5
3 5 1 4```

### 输出

```
Y
N
Y
Y
Y```

# 题解

## 作者：zhyh (赞：324)

询问树上$a$到$b$，$c$到$d$的两条路径是否相交  
我们容易发现，如果相交，记 $x=lca(a,b)$，$y=lca(c,d)$，则必有$x$在$c$~$d$路径上或$y$在$a$~$b$路径上  
之前类似的题解都没有给出证明。为什么呢？  
首先易知两点的lca在其路径上。如果路径相交，那么$x$要么在相交的路径上，要么不在。我们不妨记相交的那段为$e$~$f$  
如果不在，由对称性，不妨设$x$靠近$a$，那么有$a$到$x$深度递减，$b$到$e$、$e$到$f$、$f$到$x$深度递减；同样，肯定有$c$到$f$、$d$到$e$深度递减，由此可知，$y$必定为$f$，由此得证（以上的$e$、$f$和$c$、$d$的相对位置是由对称性直接设的，我表达不太好，各位不妨画图理解一下qwq）  
如果在的话就更好证了，各位不妨试试qwq  
那么如何查看一个点是否在一条路径上呢？我找了一个性质，即须满足该点到路径两端点的距离和等于两端点的距离，距离用lca和深度就可以了  
代码如下，用倍增做的：
```cpp
#include <cstdio>
#define DEBUG printf("Passing [%s] in LINE %d.\n", __FUNCTION__, __LINE__);
#define MAXN 100005
using namespace std;

struct edge {
    int v, pre;
} e[MAXN<<1];
int N, T, fst[MAXN], dep[MAXN], dp[MAXN][18];
int vis[MAXN], lg[MAXN];

inline int read()
{
    register int o = 0;
    register char c = getchar();
    while (c < '0' || c > '9') c = getchar();
    while (c >='0' && c <='9') o = (o<<3)+(o<<1)+(c&15), c = getchar();
    return o;
}
inline int abs(int x) { return x > 0 ? x : -x; }
inline int swap(int &x, int &y) { x ^= y ^= x ^= y; }
inline int addedge(int a, int b, int k)
{
    e[k] = (edge){b, fst[a]}, fst[a] = k;
}
int build(int k, int d)
{
    vis[k] = 1, dep[k] = d;
    for (register int o=fst[k]; o; o=e[o].pre)
        if (!vis[e[o].v]) dp[e[o].v][0] = k, build(e[o].v, d+1);
}
int prepare(int k)
{
    vis[k] = 0;
    for (register int i=1; i<=lg[dep[k]]; i++)
    	dp[k][i] = dp[dp[k][i-1]][i-1];
    for (register int o=fst[k]; o; o=e[o].pre)
        if (vis[e[o].v]) prepare(e[o].v);
}
int init()
{
    N = read(), T = read();
    for (register int i=1, a, b, c; i<N; i++) {
        a = read(), b = read();
        addedge(a, b, i);
        addedge(b, a, i+N);
    }
    build(1, 0);
    for (register int i=1; i<=N; i++)
        lg[i] = lg[i-1] + ((1<<(lg[i-1]+1)) == i);
    prepare(1);
}
int lca(int a, int b)
{
    if (dep[a] < dep[b]) swap(a, b);
    while (dep[a] > dep[b]) a = dp[a][lg[dep[a]-dep[b]]];
    if (a == b) return a;
    for (register int i=lg[dep[a]]; i>=0; i--) 
    	if (dp[a][i] != dp[b][i]) a = dp[a][i], b = dp[b][i];
    return dp[a][0];
}
inline int dis(int a, int b)
{
    register int c = lca(a, b);
    return abs(dep[c]-dep[a]) + abs(dep[c]-dep[b]); 
}
int work()
{
    for (register int a, b, c, d, x, y; T; T--)
    {
        a = read(), b = read(), c = read(), d = read();
        x = lca(a, b), y = lca(c, d);
        if (dis(a, y)+dis(b, y)==dis(a, b) || dis(c, x)+dis(d, x)==dis(c, d)) puts("Y");
        else puts("N");
    }
}
int main()
{
    init();
    work(); 
}
```

---

## 作者：沧澜 (赞：91)

其实，多画几个图模拟一下，可以发现如下一个神奇的规律：

**如果两条路径相交，那么一定有一条路径的LCA在另一条路径上**

而判断一个节点x，是否在路径s-t上需要满足如下几个条件

        - deep[x]>=deep[LCA(s,t)]

        - LCA(s,x)=x或LCA(t,x)=x;

所以分两种情况讨论一下即可

时间复杂度O(n log n)

下面是树剖LCA的代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#define MAXN 100000+15 
using namespace std;
vector<int>vec[MAXN];
int n,q,v,u,a,b,c,d;
int deep[MAXN],dad[MAXN],size[MAXN],top[MAXN];
int dfs(int x){
    size[x]=1;
    deep[x]=deep[dad[x]]+1;
    for(int i=0;i<vec[x].size();i++)
        if(dad[x]!=vec[x][i]){
            dad[vec[x][i]]=x;
            dfs(vec[x][i]);
            size[x]+=size[vec[x][i]]; 
        } 
} 
int dfs1(int x){
    int t=0;
    if(!top[x])    top[x]=x;
    for(int i=0;i<vec[x].size();i++)
        if(dad[x]!=vec[x][i]&&size[vec[x][i]]>size[t])
            t=vec[x][i];
    if(t){
        top[t]=top[x];
        dfs1(t);
    }    
    for(int i=0;i<vec[x].size();i++)
        if(dad[x]!=vec[x][i]&&vec[x][i]!=t)
            dfs1(vec[x][i]);
}
int LCA(int x,int y){
    for(;top[x]!=top[y];){
        if(deep[top[x]]<deep[top[y]])
            swap(x,y);
        x=dad[top[x]];
    }
    if(deep[x]>deep[y])    swap(x,y);
    return x;
}
int main(){
    cin>>n>>q;
    for(int i=1;i<n;i++){
        cin>>u>>v;
        vec[u].push_back(v);
        vec[v].push_back(u);
    }
    dfs(1);
    dfs1(1);
    for(int i=1;i<=q;i++){
        cin>>a>>b>>c>>d;
        int S=LCA(a,b);
        int T=LCA(c,d);
        if(deep[S]<deep[T]){
            swap(S,T);
            swap(a,c);
            swap(b,d);
        }    
        if(LCA(S,c)==S||LCA(S,d)==S)    cout<<"Y"<<endl;
        else    cout<<"N"<<endl;
    }
}
```

---

## 作者：凉城無愛 (赞：70)

# 独特的思路

题意：现有A,B,C,D四点，判断A到B的最短路和C到D的最短路有无交汇

以下为结论(可以大概看一下，了解大概过程，以便更好的看懂思路过程)

>先套两遍lca,把A和B的，C和D的最近公共祖先求出来，然后求出A和C，A和D，B和C，B和D中lca深度最大的，把得到的深度与A和B，C和D的lca深度作比较。如果都大于等于A和B，C和D的lca深度，则输出“Y”，否则输出“N”

#### 为什么呢？
如图，在树中，A,B的最短路走法如下

![](https://cdn.luogu.com.cn/upload/pic/55316.png )

从B一直向上走，直到走到K点，然后在向下走，直到A点，我们把需要回头的K点称为
#### “回头点”
因为树的特性(向上的路只有一条)所以A和B的回头点就是lca(A,B),而且走法只有一条

- 另外，如果不走最短路，你当然可以走到X点，甚至更上面的点，但你还是要回到K点，而且你永远不能不过K点到达A点

现有A，B，C，三点，A，B的回头点是K，B和C的回头点是N。A到C的过程中，因为向上的路只有一条，所以如果N的深度小于K的深度，则A到了K点后还将继续向上走，才能到达N点，然后回头到C点。如果N的深度大于K的深度，则A还没到达K点，就到达了N点，可以回头了。

- 注意一点：A到B和A到C的过程中，必然有一段是重合的，因为出发点一样。而且这重合的一段就是A->K和N中深度小的那一点。

回到题目，由于我们要求两条最短路有没有交汇，转换一下，可以成为以下问题

> 求任意一组 不同组的两点(即A和C 或A和D 或B和C 或B和D)能否在 只能走同组之间最短路的情况下 相互到达(为什么是这样呢，各位可以自己画画图，独自探究一下)

之前我们讲过三点之间的路线规律，扩大到四个点也同样适用，如图。

![](https://cdn.luogu.com.cn/upload/pic/55317.png )

我们拿B和C为例：

可以知道B和C的回头点是2，因为2的深度等于A和B的回头点的深度(大于等于都可以)，所以B到2的之间的路程都在A和B的最短路上。同理2，的深度大于C和D的回头点的深度，所以C到2的之间的路程都在C和D的最短路上。此时满足条件，输出“Y”。

再来看看这幅图

![](https://cdn.luogu.com.cn/upload/pic/55320.png )

此时，B和C的回头点是2，因为2的深度小于A和B的回头点的深度，所以B到了A和B的回头点后仍然还要继续向上走到B和C的回头点，这时A和B的回头点->B和C的回头点的这一段路程是不能走的，所以B不能到C。

因为只要满足一组，而且只与回头点的深度有关，所以就像结论中所说的：然后求出A和C，A和D，B和C，B和D中lca深度最大的，把它与A和B，C和D的回头点的深度作比较，如果都大于等于，则输出“Y”，否则输出“N”。

见代码(采用树上倍增法)：

```cpp
struct qqq{
    int y,next;
}a[200001];
//邻接表存树
int h[100001],d[100001],f[100001][18],v[100001];
//h：head(与邻接表相配队)，d：深度，f，v：见lca模板中的解释
```
关于lca的模板，本题解就不再赘述(~~其实是我懒~~)

关键代码：
```cpp
for(int i=1;i<=q;i++){
	int x1,y1,x2,y2;
	scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	int lac1=lca(x1,y1),lac2=lca(x2,y2);
	int st=max(d[lca(x1,x2)],d[lca(x1,y2)]);
	//st是存不同组的两点(即A和C 或A和D 或B和C 或B和D)的最大深度 
	st=max(st,d[lca(y1,x2)]);
	st=max(st,d[lca(y1,y2)]);
	if(st>=d[lac1]&&st>=d[lac2])cout<<"Y"<<endl;
	else cout<<"N"<<endl;
} 
```
好了，本题解就到这了，代码有点少呵，但只要你看懂了前面的思路，自然能知道代码的实现吧，拜拜！


---

## 作者：Mathison (赞：52)

可以说是最简单的一种解法了

## LCA加路径长度判断不等式

我们先用lca处理树上任意两点间距离，即：

`dis[a]+dis[b]-2*dis[lca(a,b)]`

然后我们可以用数学归纳（或者说是试出来的吧）发现：

如果**两个起点的距离** + **两个终点的距离** >= **两条路径的长度和**

那么两条路径有一部分一定是**重合**的（或者说一定是**存在公共点**的）

或许也可以用容斥原理解释~~（其实怎么证明正确性我也没想好……直观感觉吧）~~

也就是`dist(x1,y1)+dist(x2,y2)>=dist(x1,x2)+dist(y1,y2)`

## AC code:

```
#include<bits/stdc++.h>
using namespace std;
const int N=100010;
int f[N][25],d[N],dis[N],T,n,m,tot,t,ver[2*N],next[2*N],head[N];
queue <int> q;
void add(int x,int y)
{
	ver[++tot]=y;
	next[tot]=head[x];
	head[x]=tot;
}
int lca(int x,int y)
{
	if(d[x]>d[y]) swap(x,y);
	for(int i=t;i>=0;i--) if(d[f[y][i]]>=d[x]) y=f[y][i];
    if(x==y) return x;
    for(int i=t;i>=0;i--) if(f[x][i]!=f[y][i]) x=f[x][i],y=f[y][i];
    return f[x][0];
}
int dist(int a,int b) {return dis[a]+dis[b]-2*dis[lca(a,b)];}//lca求树上两点距离
int main()
{
   	scanf("%d%d",&n,&m);
   	t=(int)(log(n)/log(2))+1;
	for(int i=1;i<=n;i++) head[i]=d[i]=0;
   	for(int i=1;i<n;i++)
   	{
   		int x,y;
     	scanf("%d%d",&x,&y);
   		add(x,y);add(y,x);
	}
	q.push(1);
	d[1]=1;
	while(q.size())
	{
		int x=q.front();q.pop();
		for(int i=head[x];i;i=next[i])
		{
			int y=ver[i];
			if(d[y]) continue;
			d[y]=d[x]+1;
			dis[y]=dis[x]+1;
			f[y][0]=x;
			for(int j=1;j<=t;j++)
			    f[y][j]=f[f[y][j-1]][j-1];
			q.push(y);
		}	
	}
	for(int i=1;i<=m;i++)
	{
		int x1,y1,x2,y2;
		scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
		if(dist(x1,y1)+dist(x2,y2)>=dist(x1,x2)+dist(y1,y2)) printf("Y\n");
		else printf("N\n");
    }	
	return 0;
}

```

---

## 作者：Kwork (赞：22)

来一发倍增的题解。

根据题意，我们可以先把不可能相遇的情况判断一下。设p是a,b的LCA，q是c,d的LCA，如果说一对点的LCA的深度比另外一对点中任意一个点的深度都要深的话则不可能相遇，输出N。

然后，如果不满足上面的条件则继续进行判断，我们假设p的深度大于q的深度，那么，如果可能相遇的话（a或b）与（q）的LCA就是q。q的深度大于p的深度的情况亦然。输出Y。

否则输出N。

对于每次询问，每次最少做2次LCA，最多做4次。还是比较快的。


```cpp
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <algorithm>
//头文件
using namespace std;
//std空间名
const int MAXN=100005,log_n=17;
//常数
vector<int>G[MAXN];
int n,m,depth[MAXN],parent[log_n+1][MAXN];
//变量
inline void read(int &n){
    n=0;
    char ch=getchar();
    while(ch<'0' || ch>'9') ch=getchar();
    do{
        n=n*10+ch-'0';
        ch=getchar();
    }while(ch>='0' && ch<='9');
    return;
}
inline int min(int x,int y){
    return x<y ? x:y;
}
void in_data(){
    read(n);read(m);
    int u,v;
    for(int i=1;i<n;i++){
        read(u);read(v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    return;
}
void dfs(int u,int fa,int dep){
    depth[u]=dep;parent[0][u]=fa;
    int v;
    for(int i=0;i<G[u].size();i++){
        v=G[u][i];
        if(v!=fa){
            dfs(v,u,dep+1);
        }
    }
    return;
}
void do_before_query(){
    dfs(1,0,0);
    for(int i=1;i<=log_n;i++)
        for(int u=1;u<=n;u++)
            parent[i][u]=parent[i-1][parent[i-1][u]];
    return;
}
int lca(int u,int v){
    if(depth[u]>depth[v]) swap(u,v);
    int tmp=depth[v]-depth[u];
    for(int i=0;i<=log_n;i++){
        if((tmp>>i)&1)
            v=parent[i][v];
    }
    if(u==v) return u;
    for(int i=log_n;i>=0;i--){
        if(parent[i][u]!=parent[i][v]){
            u=parent[i][u];
            v=parent[i][v];
        }
    }
    return parent[0][u];
}
void solve_query(){
    do_before_query();
    int a,b,c,d,p,q;
    while(m--){
        read(a);read(b);read(c);read(d);
        p=lca(a,b);q=lca(c,d);
        if(depth[p]>depth[c] && depth[p]>depth[d]){
            putchar('N');
            putchar('\n');
            continue;
        }
        if(depth[q]>depth[a] && depth[q]>depth[b]){
            putchar('N');
            putchar('\n');
            continue;
        }
        if(depth[p]>=depth[q]){
            if(lca(p,c)==p || lca(p,d)==p){
                putchar('Y');
                putchar('\n');
                continue;
            }
        }
        else{
            if(lca(q,a)==q || lca(q,b)==q){
                putchar('Y');
                putchar('\n');
                continue;
            }
        }
        putchar('N');
        putchar('\n');
    }
    return;
}
int main(){
    in_data();
    solve_query();
    return 0;
}
```

---

## 作者：一扶苏一 (赞：20)


# 大家好，我是个毒瘤，并没有想到什么两路径有重合则两LCA是其中一个LCA这样的神仙结论，只会暴力上数据结构解决。于是我就暴力树剖然后链上查询修改过了这题。

## Solution

考虑两条链有相交的部分，等价于把一条链染色以后，查询另一条链上有没有被染色的部分。如果有则有重合，否则没有。

发现染色可以等价于链上权值+1（查询初始权值为0），查询有被染色的则等价于查询链上最大值，如果不为0则有位置被染色

每次查询完后将第一条链上的权值-1，去掉这次查询的贡献，即可做到两次查询互不影响。

于是树剖一下用线段树维护边权即可。

代码十分好写。

## Code

```cpp
#include <cstdio>
#include <algorithm>
#ifdef ONLINE_JUDGE
#define freopen(a, b, c)
#endif
#define rg register
#define ci const int
#define cl const long long

typedef long long int ll;

namespace IPT {
	const int L = 1000000;
	char buf[L], *front=buf, *end=buf;
	char GetChar() {
		if (front == end) {
			end = buf + fread(front = buf, 1, L, stdin);
			if (front == end) return -1;
		}
		return *(front++);
	}
}

template <typename T>
inline void qr(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch=IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = (x << 1) + (x << 3) + (ch ^ 48), ch = IPT::GetChar();
	if (lst == '-') x = -x;
}

template <typename T>
inline void ReadDb(T &x) {
	rg char ch = IPT::GetChar(), lst = ' ';
	while ((ch > '9') || (ch < '0')) lst = ch, ch = IPT::GetChar();
	while ((ch >= '0') && (ch <= '9')) x = x * 10 + (ch ^ 48), ch = IPT::GetChar();
	if (ch == '.') {
		ch = IPT::GetChar();
		double base = 1;
		while ((ch >= '0') && (ch <= '9')) x += (ch ^ 48) * ((base *= 0.1)), ch = IPT::GetChar();
	}
	if (lst == '-') x = -x;
}

namespace OPT {
	char buf[120];
}

template <typename T>
inline void qw(T x, const char aft, const bool pt) {
	if (x < 0) {x = -x, putchar('-');}
	rg int top=0;
	do {OPT::buf[++top] = x % 10 + '0';} while (x /= 10);
	while (top) putchar(OPT::buf[top--]);
	if (pt) putchar(aft);
}

const int maxn = 100010;
const int maxm = 200010;

struct Edge {
	int to, nxt;
};
Edge edge[maxm]; int hd[maxn], ecnt = 1;
inline void cont(ci from, ci to) {
	Edge &e = edge[++ecnt];
	e.to = to; e.nxt = hd[from]; hd[from] = ecnt;
}

int n, q, vistime;
int sz[maxn], son[maxn], dfn[maxn], top[maxn], deepth[maxn], fa[maxn];

struct Tree {
	Tree *ls, *rs;
	int l, r, v, tg;
	
	inline void make_tag(ci _v) {
		this->v += _v;
		this->tg += _v;
	}
	
	inline void pushdown() {
		if (!this->tg) return;
		if (this->ls) this->ls->make_tag(tg);
		if (this->rs) this->rs->make_tag(tg);
		this->tg = 0;
	}
	
	inline void pushup() {
		this->v = this->ls ? (this->rs ? std::max(this->ls->v, this->rs->v) : this->ls->v) : this->rs->v;
	}
};
Tree *pool[maxm], qwq[maxm], *rot;
int Top;

void reading();
void dfs(ci, ci);
void DFS(ci, ci);
void buildpool();
void buildroot();
void build(Tree*, ci, ci);
void change(int, int, ci);
void update(Tree*, ci, ci, ci);
bool check(int, int);
int ask(Tree*, ci, ci);

int main() {
	freopen("1.in", "r", stdin);
	qr(n); qr(q);
	reading();
	dfs(1,0); DFS(1, 1);
	buildpool(); buildroot();
	build(rot, 1, n);
	int a, b, c, d;
	while(q--) {
		a = b = c = d = 0;
		qr(a); qr(b); qr(c); qr(d);
		change(a, b, 1);
		if(check(c, d)) puts("Y");
		else puts("N");
		change(a, b, -1);
	}
	return 0;
}

void reading() {
	int a, b;
	for (rg int i = 1; i < n; ++i) {
		a = b = 0; qr(a); qr(b);
		cont(a, b); cont(b, a);
	}
}

void dfs(ci u, ci pree) {
	deepth[u] = deepth[fa[u] = edge[pree].to] + 1;
	sz[u] = 1;
	for (int i = hd[u]; i; i = edge[i].nxt) if (i != pree) {
		int &to = edge[i].to;
		dfs(to, i ^ 1);
		sz[u] += sz[to];
		if(sz[to] > sz[son[u]]) son[u] = to;
	}
}

void DFS(ci u, ci tp) {
	if ((!u) || (dfn[u])) return;
	dfn[u] = ++vistime; top[u] = tp;
	DFS(son[u], tp);
	for (int i = hd[u]; i; i = edge[i].nxt) {
		int &to = edge[i].to;
		DFS(to, to);
	}
}

void buildpool() {
	for (rg int i = 0; i < maxm; ++i) pool[i] = qwq + i;
	Top = maxm - 1;
}

void buildroot() {
	rot = pool[Top--];
}

void build(Tree *u, ci l, ci r) {
	u->l = l; u->r = r;
	if(l == r) return;
	int mid = (l + r) >> 1;
	if (l <= mid) build(u->ls = pool[Top--], l, mid);
	if (mid < r) build(u->rs = pool[Top--], mid + 1, r);
}

void change(int u, int v, ci p) {
	while (top[u] != top[v]) {
		if (deepth[top[u]] < deepth[top[v]]) std::swap(u, v);
		update(rot, dfn[top[u]], dfn[u], p);
		u = fa[top[u]];
	}
	if (deepth[u] < deepth[v]) std::swap(u, v);
	update(rot, dfn[v], dfn[u], p);
}

void update(Tree *u, ci l, ci r, ci v) {
	if ((u->l > r) || (u->r < l)) return;
	if ((u->l >= l) && (u->r <= r)) {u->make_tag(v);return;}
	u->pushdown();
	if (u->ls) update(u->ls, l, r, v);
	if (u->rs) update(u->rs, l, r, v);
	u->pushup();
}

bool check(int u, int v) {
	while (top[u] != top[v]) {
		if (deepth[top[u]] < deepth[top[v]]) std::swap(u, v);
		if (ask(rot, dfn[top[u]], dfn[u])) return true;
		u = fa[top[u]];
	}
	if (deepth[u] < deepth[v]) std::swap(u, v);
	return ask(rot, dfn[v], dfn[u]);
}

int ask(Tree *u, ci l, ci r) {
	if ((u->l > r) || (u->r < l)) return 0;
	if ((u->l >= l) && (u->r <= r)) return u->v;
	u->pushdown();
	return u->ls ? (u->rs ? std::max(ask(u->ls, l, r), ask(u->rs, l ,r)) : ask(u->ls, l, r)) : ask(u->rs, l, r);
}
```

## Summary

### 我爱暴力上数据结构！

---

## 作者：ZORO (赞：19)

# $Description$
有一颗$n$个节点的树，给你两条路径各自的端点$a->b$、$c->d$，询问这两条路径是否有公共点

# $Solution$
**判断树上两条路径有无公共点：求$LCA$**

若两条路径有公共点，那么到达公共点可以选择顺着链往上走或者往下拐进另一颗子树。

进一步说，**向上走的路只有一条，两条链有公共点后一起往上走到最后一个公共点一定有一条链结束或者是往下拐**

结合这张图看的更明白
![](https://s2.ax1x.com/2019/10/10/uTPcge.png)
**所以说一定有一条链两端点的$LCA$位于另一条链上，这是两条链相交的充要条件**

设这个点为$c$，这个点位于的链的两个端点为$a,b$,$a,b$的$LCA$为$d$，$dis(a,d)+dis(d,c)+dis(b,c)=dis(a,b)$

根据树上路径只有一条的性质，$dis(a,c)+dis(c,b)=dis(a,b)$
![](https://s2.ax1x.com/2019/10/10/uTPODs.png)
又因为可能$X$链的$LCA$位于$Y$链上，反过来也有可能，所以两种情况验证取$or$即可

# $Code$
```
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cmath>
#define re register
#define maxn 200010
#define ll long long
using namespace std;
inline int read()
{
	int x=0,f=1; char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
	return x*f;
}
int q,a,b,c,d;
int tmp1,tmp2,tmp3,n,x,y,vis[maxn],f[maxn][23],lg[maxn],root;
int cnt,head[maxn],dep[maxn];
struct Edge{
	int v,nxt;
}e[maxn<<2];
inline void add(int u,int v)
{
	e[++cnt].v=v;
	e[cnt].nxt=head[u];
	head[u]=cnt;
}
void dfs(int now,int fa)
{
	dep[now]=dep[fa]+1;
	f[now][0]=fa;
	for(int i=1;(1<<i)<=dep[now];++i)
	 f[now][i]=f[f[now][i-1]][i-1]; 
	for(int i=head[now];i;i=e[i].nxt)
	{
		int ev=e[i].v;
		if(ev==fa) continue;
		dfs(ev,now);
	}
}
int lca(int x,int y)
{
	if(dep[y]>dep[x]) swap(x,y);
	for(re int i=lg[dep[x]-dep[y]];i>=0;--i)
	{
		if(dep[f[x][i]]<dep[y]) continue;
		x=f[x][i];
	}
	if(x==y) return x;
	for(re int i=lg[dep[x]-1];i>=0;--i)
	{
		if(f[x][i]==f[y][i]) continue;
		x=f[x][i],y=f[y][i];
	}
	return f[x][0];
}
void pre()
{
	tmp1=1,tmp2=0;
	while(tmp1<=n)
	{
		lg[tmp1]=tmp2;
		tmp2++;
		tmp1*=2;
	}
	for(re int i=1;i<=n;++i)
	{
		if(lg[i]) continue;
		lg[i]=lg[i-1];
	}
}
int dis(int a,int b)//计算一条链的长度 
{
	re int c=lca(a,b);
	return abs(dep[a]-dep[c])+abs(dep[b]-dep[c]);
}
int main()
{
	n=read(),q=read();
	pre();
	for(re int i=1;i<n;++i)
	{
		x=read(),y=read();
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	for(re int i=1;i<=q;++i)
	{
		a=read(),b=read(),c=read(),d=read();
		tmp1=lca(a,b);
		tmp2=lca(c,d);
		if(dis(a,tmp2)+dis(b,tmp2)==dis(a,b)||dis(c,tmp1)+dis(d,tmp1)==dis(c,d)) printf("Y\n");
		else printf("N\n");
	}
	return 0;
}
```

---

## 作者：George1123 (赞：12)

[${\color{orange}\text{欢迎拜访我这个蒟蒻的博客}}$](https://www.luogu.org/blog/Wendigo/)

[P3398 【仓鼠找sugar】](https://www.luogu.org/problem/P3398)

鸣谢 @Rem°  @Oops！

### 此题算法:图论+LCA

大致思路:

>1.$ $输入图，通过$dfs$得出每个点的深度$dep[]$，其中$dep[1]=1$。

>2.$ $构造倍增数组$pro[node][lg]$并敲好$LCA$的板子。

>3.$ $如果两个路径相交，则其中一条路径两个端点的最近公共祖先必须被另一条路径所穿过。

![1030-1.jpg](https://i.loli.net/2019/10/30/8fudoY7B4PDyNKm.jpg)

>而如果$dis(from1,to1)+dis(from2,to2)\geq dis(from1,from2)+dis(to1,to2)$则上面结论会满足(如下，$dis(x,y)=dep[x]-dep[lca]+dep[y]-dep[lca]$)。

```cpp
int dis(int x,int y){
    int mid=lca(x,y);
    return dep[x]-dep[mid]+dep[y]-dep[mid];
}
```

## 以下是代码+注释



```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,q,dep[N],
pro[N][20];
struct edge{
    int adj,nex;
}e[N*2];
int g[N],top;
void add(int x,int y){
    e[++top]=(edge){
        y,g[x]
    }; g[x]=top;
} void dfs(int x,int fa,int d){
    dep[x]=d; pro[x][0]=fa; //初始化深度和父亲
    for(int j=1;j<18;j++)
        pro[x][j]=pro[pro[x][j-1]][j-1];
    for(int i=g[x];i;i=e[i].nex){
        int to=e[i].adj;
        if(to==fa) continue;
        dfs(to,x,d+1);
    }
} int lca(int x,int y){  //lca的板子
//  printf("lca(%d,%d)=",x,y);
    if(dep[x]<dep[y])
        swap(x,y);
    for(int i=17;i>=0;i--)
        if(dep[pro[x][i]]>=dep[y])
            x=pro[x][i];
//  printf("%d\n",x);
    if(x==y) return x;
    for(int i=17;i>=0;i--)
        if(pro[x][i]!=pro[y][i]){
            x=pro[x][i];
            y=pro[y][i];
        }
    return pro[x][0];
} int dis(int x,int y){ //树上两点距离
    int mid=lca(x,y);
    return dep[x]-dep[mid]
    +dep[y]-dep[mid];
} int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        add(x,y); add(y,x);
    } dfs(1,1,1); //dfs
    while(q--){
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        if(dis(a,b)+dis(c,d)>=dis(a,c)+dis(b,d))
            puts("Y"); //判断符合条件
        else puts("N");  //注意大小写
    } return 0;
}
```
[这是WA代码](https://www.luogu.org/discuss/show/161296)

至今仍不知之前代码为何错了。

谢谢大家! !


---

## 作者：清远学会 (赞：11)

# 树链剖分可做
> what？

考虑树上节点期初为0，在小仓鼠与他朋友的起止位置为a,b,c,d;

我先想60分的暴力是，打两个DFS，第一遍是a->b打标记，第二遍c->d是找标记；很自然想到树上问题区间(a,b)赋1，在另一区间找是否(c,d)之间也被付过值即为相交；

那么对于(a,b)打上标记，有没有更好的方法呢？

显然，树剖是维护这样的高效数据结构，那么对于(c,d)我也执行这样的操作，维护区间最大，当(1,n)中最大值为2，那么这个点被覆盖两次，即为相交；

### 那么树剖维护区间修改与区间最大就行：tr[1] == 2 表相交；
### 奉上代码：
```cpp
#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#define N 300500
using namespace std;

int T,n,m;
int head[N],cnt;
struct node {
	int nxt,to;
}e[N];
int tr[N * 4],lz[N * 4];
int fa[N],wson[N],dep[N];
int tpos[N],sz[N],tp[N],tot;

inline void cp(int u,int v) {
	cnt ++;
	e[cnt].to = v;
	e[cnt].nxt = head[u];
	head[u] = cnt;
}

inline void dfs1(int u,int f) {
	sz[u] = 1;
	for(int i = head[u];i;i = e[i].nxt) {
		int v = e[i].to;
		if(v == f) continue;
		fa[v] = u; dep[v] = dep[u] + 1;
		dfs1(v,u); sz[u] += sz[v];
		if(sz[v] > sz[wson[u]]) wson[u] = v;
	}
}

inline void dfs2(int u,int Top) {
	tpos[u] = ++ tot;
	tp[u] = Top;
	if(wson[u]) dfs2(wson[u],Top);
	for(int i = head[u];i;i = e[i].nxt) {
		int v = e[i].to;
		if(v == wson[u] || v == fa[u]) continue;
		dfs2(v,v);
	}
}

inline void Update(int k) {
	tr[k] = max(tr[k << 1],tr[k << 1 | 1]);
}

inline void Pushdn(int k) {
	if(lz[k] != 0) {
		tr[k << 1] += lz[k];
		tr[k << 1 | 1] += lz[k];
		lz[k << 1] += lz[k];
		lz[k << 1 | 1] += lz[k];
		lz[k] = 0;
	}
}

inline void Change_max(int k,int l,int r,int a,int b,int c) {
	if(a <= l && r <= b) {
		tr[k] += c;
		lz[k] += c;
		return ;
	}
	Pushdn(k);
	int mid = (l + r) >> 1;
	if(a <= mid) Change_max(k << 1,l,mid,a,b,c);
	if(b > mid) Change_max(k << 1 | 1,mid + 1,r,a,b,c);
	Update(k);
}

inline void Change(int u,int v,int c) {
	while(tp[u] != tp[v]) {
		if(dep[tp[u]] < dep[tp[v]]) swap(u,v);
		Change_max(1,1,n,tpos[tp[u]],tpos[u],c);
		u = fa[tp[u]];
	}
	if(tpos[u] > tpos[v]) swap(u,v);
	Change_max(1,1,n,tpos[u],tpos[v],c);
	return ;
}

int main() {
	scanf("%d%d",&n,&m);
	for(int i = 1;i < n;i ++) {
		int u,v; scanf("%d%d",&u,&v);
		cp(u,v); cp(v,u);
	}
	dep[1] = 1,fa[1] = 1;
	dfs1(1,-1); dfs2(1,1);
	for(int i = 1;i <= m;i ++) {
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		Change(a,b,1); Change(c,d,1);
		if(tr[1] == 2) printf("Y\n");
		else printf("N\n");
		Change(a,b,-1); Change(c,d,-1);//别忘减掉
	}
	return 0;
}
```
~~~想到之后码模板就行~~~~~

---

## 作者：llzzxx712 (赞：10)

# 求两条路径是否有公共点
题目的意思就是给出树上两条路径的两个端点，询问是否有公共点

通过分析题目可以发现以下几点：
1. 一条路径的两个端点的LCA一定是该条路径上深度最小的点

2.两个节点xy的距离=de[x]+de[y]-2*de[lca(x,y)]

3.如果一个点在一条路径上，那么它到两个端点的距离和等于这段路径的长度

4.如果两条路径相交，那么这深度较大的LCA一定在另一条路径上

比如我们看这棵树![](https://cdn.luogu.com.cn/upload/image_hosting/zb9lk2az.png)
比如这里有一条从4到8的路径（设为路径1）和一条11到5的路径（设为路径2），可以发现，路径1的LCA为节点2（深度2），路径2的LCA为节点5（深度3）。可以看到节点5是两条路径的交点。

若把路径2变为11到1，那么它的LCA为1（深度1），此时节点2是两条路径的交点。

那么我们就可以用以下思路进行判断
1.写倍增LCA，预处理nlogn

2.读入4个节点，分别求出两个节点的LCA

3.选择LCA深度大的节点，判断它是否在另外两个节点构成的路径上，如果是，输出Y，否则输出N

单次询问复杂度4*logn

如果不会求LCA可以去看我的倍增[LCA题解](https://www.luogu.com.cn/blog/llzzxx712/solution-sp14932)

最后，附上AC代码

```cpp
#include<bits/stdc++.h>
#define N 100002
#define ml 20
using namespace std;
int to[N*2],ne[N*2],head[N],de[N],anc[N][ml];
int n,tot,q;
void add(int x,int y){
	to[++tot]=y,ne[tot]=head[x],head[x]=tot;
}
void read(int &x) {
    int f = 1; x = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9')   {if (ch == '-') f = -1; ch = getchar();}
    while (ch >= '0' && ch <= '9') {x = x * 10 + ch - '0'; ch = getchar();}
    x *= f;
}
void dfs(int x,int fa){
	de[x]=de[fa]+1,anc[x][0]=fa;
	for(int i=1;i<ml;i++) anc[x][i]=anc[anc[x][i-1]][i-1];
	for(int i=head[x];i;i=ne[i]) if(to[i]!=fa) dfs(to[i],x);
}
int getlca(int x,int y){
	if(de[x]<de[y]) swap(x,y);
	for(int i=ml-1;i>=0;i--){
		if(de[anc[x][i]]>=de[y]) x=anc[x][i];
	}
	if(x==y) return x;
	for(int i=ml-1;i>=0;i--){
		if(anc[x][i]!=anc[y][i]) x=anc[x][i],y=anc[y][i];
	}
	return anc[x][0];
}
bool pan(int x,int y,int z){
	int a,b,c,xy,yz,xz;
	a=getlca(x,z),b=getlca(y,z),c=getlca(x,y);
	xy=de[x]+de[y]-2*de[c];
	yz=de[y]+de[z]-2*de[b];
	xz=de[x]+de[z]-2*de[a];
	if(xz+yz==xy) return 1;
	return 0;
}
int main()
{
    read(n),read(q);
    for(int i=1;i<n;i++){
    	int x,y;
    	read(x),read(y);
    	add(x,y),add(y,x);
	}
	dfs(1,1);
	for(int i=1;i<=q;i++){
		int x,y,x1,y1,lcaxy,lcax1y1;
		read(x),read(y),read(x1),read(y1);
		lcaxy=getlca(x,y),lcax1y1=getlca(x1,y1);
		if(de[lcaxy]>de[lcax1y1]){
			if(pan(x1,y1,lcaxy)) printf("Y\n");
			else printf("N\n");
		}
		else{
			if(pan(x,y,lcax1y1)) printf("Y\n");
			else printf("N\n");
		}
	}
	return 0;
}
	

```



---

## 作者：LevenKoko (赞：10)

### 同步发表于[我的博客](https://www.cnblogs.com/zhenglw/p/11003681.html)


------------

### 无关:


竞赛课想找一道水一点的tarjan题，看看这么久没做题手感有没有掉...

结果这题貌似不是tarjan啊...应该是裸的LCA...假的标签！！

一遍过样例+一遍AC祭（好吧这么水的题也没啥好开心的）

###  题意：

大概就是给一棵树，和两条路径，判断两条路径有无公共顶点。

### 分析:

随便画一棵树，然后会发现，两条路径有公共部分的话，必定有一条路径（的两个端点）的LCA在另一条路径上

这样我们只要判断一个节点是否在一条路径上即可

然后联想到绝对值的几何意义（反正我是这么想到的...）满足以下规律的才有可能满足节点lca在路径a-b上

$$dis(lca,a)+dis(lca,b)==dis(a,b)$$

 

 注意:要判断两次，因为有可能是LCA(a,b)在c-d上，也有可能是LCA(c,d)在a-b上

然后我打的树剖LCA，看着不爽的可以换成自己LCA啦



```cpp
#include<cstdio>
#include<iostream>
#include<cstring>
#define writeln(x)  write(x),puts("")
#define writep(x)   write(x),putchar(' ')
using namespace std;
inline int read(){
    int ans=0,f=1;char chr=getchar();
    while(!isdigit(chr)){if(chr=='-') f=-1;chr=getchar();}
    while(isdigit(chr)){ans=(ans<<3)+(ans<<1)+chr-48;chr=getchar();}
    return ans*f;
}void write(int x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}const int M = 1e5+5;
int head[M],ver[M<<1],nxt[M<<1],tot,n,m,idx[M],fa[M],son[M],sz[M],tp[M],dep[M];
inline void add(int x,int y){ver[++tot]=y;nxt[tot]=head[x];head[x]=tot;}
void dfs1(int x,int f){
    fa[x]=f,dep[x]=dep[f]+1;sz[x]=1;
    for(int i=head[x];i;i=nxt[i]){
        if(ver[i]==f) continue;
        dfs1(ver[i],x);
        sz[x]+=sz[ver[i]];
        if(sz[son[x]]<sz[ver[i]]) son[x]=ver[i];
    }
}int t;
void dfs2(int x,int topf){
    tp[x]=topf,idx[x]=++t;
    if(!son[x]) return;
    dfs2(son[x],topf);
    for(int i=head[x];i;i=nxt[i])
        if(!idx[ver[i]]) dfs2(ver[i],ver[i]);
}
int LCA(int x,int y){
    while(tp[x]!=tp[y]){
        if(dep[tp[x]]<dep[tp[y]]) swap(x,y);
        x=fa[tp[x]];
    }if(dep[x]>dep[y]) swap(x,y);
    return x;
}
int DIS(int x,int y){return dep[x]+dep[y]-2*dep[LCA(x,y)];}
inline bool check(int a,int b,int c,int d){
    int x=LCA(a,b);
    if(DIS(x,c)+DIS(x,d)==DIS(c,d)) return 1;
    return 0;
}
int main(){
    n=read(),m=read();
    for(int i=1,x,y;i<n;i++){
        x=read(),y=read();
        add(x,y),add(y,x);
    }dfs1(1,0),dfs2(1,1);
    while(m--){
        int a=read(),b=read(),c=read(),d=read();
        if(check(a,b,c,d)||check(c,d,a,b)) puts("Y");
        else puts("N");
    }
    return 0;
}
```
 

---

## 作者：唔啊唔 (赞：7)

若答案为“Y”，会有一个十分明显的特点：

一条路径的最近公共祖先会在另一条路径上。

如以下这幅图（从a到c,从b到d）

![](https://cdn.luogu.com.cn/upload/pic/55315.png)

你会发现层数较大那个最近公共祖先（b与d的最近公共祖先）会在另一条的路径上，

并且另一条的路径的一个端点（a）与这个层数较大的最近公共祖先的最近公共祖先
就是这个层数较大的最近公共祖先本身，另一个端点（c）与这个层数较大的最近公共祖先的最近公共祖先是层数较低的最近公共祖先（a与c的最近公共祖先）

不仅如此我还发现了一种特别的“N”：

当a和c的最近公共祖先与b和d的最近公共祖先共层时，若这两个点不相同，这两条路径将不可能相交。

如以下这幅图（从a到c,从b到d）

![](https://cdn.luogu.com.cn/upload/pic/55318.png )

所以这道题可谓一个裸的LCA了。

所以附上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,num,n,m,x,y,dep[100010],f[100010][30],head[100010];
struct Node{
	int to,next;
}a[100000*2+10];
inline void add(int from,int to){	//加边 
	num++;
	a[num].to=to;
	a[num].next=head[from];
	head[from]=num;
}
inline void dfs(int son,int fa){	//LCA模板 
	dep[son]=dep[fa]+1;
	f[son][0]=fa;
	for(int i=1;i<=t;i++){
		f[son][i]=f[f[son][i-1]][i-1];
	}
	for(int i=head[son];i;i=a[i].next){
		if(a[i].to!=fa)dfs(a[i].to,son);
	}	
}
inline int lca(int x,int y){		//LCA模板
	if(dep[x]>dep[y])swap(x,y);
	for(int i=t;i>=0;i--){
		if(dep[f[y][i]]>=dep[x])y=f[y][i];
	}
	if(x==y)return x;
	for(int i=t;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	return f[x][0];
}
int main(){
	cin>>n>>m;
	t=log2(n);
	for(int i=1;i<=n-1;i++){
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs(1,0);
	int xa,xb,ya,yb;
	int l,q,w,djd,e,r;
	for(int i=1;i<=m;i++){
		cin>>xa>>xb>>ya>>yb;
		if(xa==ya||xb==ya||xa==yb||xb==yb){	//我想这个应该不需要解释了 
			puts("Y");
			continue;
		}
		int la=lca(xa,xb),lb=lca(ya,yb);	//找最近公共祖先 
		if(la==lb){	//是一个点 
			puts("Y");
			continue;
		}
		if(dep[la]==dep[lb]){//不同一个点，但同层 
			puts("N");
			continue;
		}
		if(dep[la]>dep[lb]){	//判断那个层数更大 
			l=la;				//l：层数较大那个最近公共祖先 
			q=ya;				//q:另一条的路径的一个端点 
			w=yb;				//w:另一个端点
			djd=lb;				//djd:层数较低的最近公共祖先
		}
		else{
			l=lb;
			q=xa;
			w=xb;
			djd=la;
		}
		e=lca(q,l),r=lca(w,l);
		if((e==l&&r==djd)||(e==djd&&r==l)){	//判断 
			puts("Y");
			continue;
		}
		puts("N");
	}
	return 0;//谢谢观看 
}//绝对原创 
```
宣传一位和我合作的dalao的博客：https://www.luogu.org/blog/wangrxgod/

可能做的有点难看，但也希望多多包涵！！！（花了很多时间）

---

## 作者：w_x_c_q (赞：5)

**解法：lca**
	
    
    刚刚讲过lca和树剖  可是树剖还没有了解透彻
	只好用lca来解这道题（其实是树剖裸题啦，会树剖的大佬略过哦）；
	
    
    讲讲我的lca做法（倍增lca）
    首先dfs预处理出每个点的深度（一开始的时候，
    我每次都会统计入度来判断哪个点是根，后来发现
    没有必要，直接强制认为1是根就好啦）；
    然后我们就要对这棵树搞点事情了：
    首先，对于给出的两对点,如果有一对的lca深度深于另外一对的任意一个点的深度，那么肯定是无解的，直接输出N就好了
    再然后，通过yy，我们很容易想出一个非常重要的性质：
    如果两条路径相交，那么交点一定是某一组点的lca；而这某一组点，其lca一定比另一组的lca深度要大；（为什么想到这个性质？实在是举不出反例呀）
    所以我们可以默认第一对点（a，b）的lca的深度要小
    那么直接判断c,d的lca是否在a,b之间的路径上即可
    怎么判断这个点是不是在a,b之间路径上呢？
    只要a,b中的任意一个点与c,d的lca的lca是c,d的lca这个点就可以了；
    emmm 好像不太好理解
    其实就是
    ```cpp
	if(lca(q1,lca(q2,w2))==lca(q2,w2)||lca(w1,lca(q2,w2))==lca(q2,w2)){
				printf("Y\n");
			}
			else{
				printf("N\n");
			}
```
	这么简单啦。。。
    还是不太理解？自己去画图吧小哥哥（小姐姐）
    大致思路就是这些了 又不懂的请私信我哦。。
    
    代码在这里
    ```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#define cq(i,s,n) for(int i=s;i<=n;i++)
using namespace std;
int n,q,x,y,q1,q2,w1,w2;
struct edge{
	int nxt,to;
}edge[200005];
int num;
int f[200005][31];
int head[200005],vis[200005],dep[200005];
void add(int from,int to){
	edge[++num].nxt=head[from];
	edge[num].to=to;
	head[from]=num;
}

void dfs(int u,int depth){
	vis[u]=1;
	dep[u]=depth;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(!vis[v]){
			dfs(v,depth+1);
			f[v][0]=u;
		}
	}
}

void init(){
	for(int i=1;(1<<i)<=n;i++){
		cq(j,1,n){
			f[j][i]=f[f[j][i-1]][i-1];
		}
	}
}

int lca(int x,int y){
	int l=0;
	while((1<<l)<=n)l++;
	l--;
	if(dep[x]<dep[y])swap(x,y);
	for(int i=20;i>=0;i--){
		if(dep[y]<=dep[x]-(1<<i))x=f[x][i];
	}
	if(x==y)return x;
	for(int i=20;i>=0;i--){
		if(f[x][i]!=f[y][i]){
			x=f[x][i];
			y=f[y][i];
		}
	}
	return f[x][0];
}

int main(){
	scanf("%d%d",&n,&q);
	cq(i,1,n-1){
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs(1,1);
	init();
	while(q--){
		scanf("%d%d%d%d",&q1,&w1,&q2,&w2);
		if(dep[lca(q1,w1)]>dep[lca(q2,w2)]){
			swap(q1,q2);
			swap(w1,w2);
		}
		if((dep[lca(q1,w1)]>dep[q2]&&dep[lca(q1,w1)]>dep[w2])||(dep[lca(q2,w2)]>dep[q1]&&dep[lca(q2,w2)]>dep[w1]))
		{
			printf("N\n");
		}
		else{
			if(lca(q1,lca(q2,w2))==lca(q2,w2)||lca(w1,lca(q2,w2))==lca(q2,w2)){
				printf("Y\n");
			}
			else{
				printf("N\n");
			}
		}
	}
	return 0;
}
```
    

---

## 作者：Capella (赞：4)

用通行的树剖模板就可以做的题目。

首先引用 @A4paper 的[题解](https://www.luogu.org/blog/A4paper/solution-p3398)，此题解使我更加直观地理解了两条路径相交的充要条件。

“令 $x = \mathrm{LCA}(a, b)$，$y = \mathrm{LCA}(c, d)$，则 $c, d$ 至少有一个点在 $y$ 的子树上，并且 $a, b$ 至少有一个点在 $x$ 的子树上。”

推荐通过画图，从“深度”的角度理解这个结论。

如果两条路径相交，其中一条路径两个点 $a, b$ 的 LCA $x$，一定在另一条路径 $c, d$ 上（路径 $c, d$ 的 LCA 为 $y$）。（不妨设是这样，两条路交换一下也是同理）

这就要求 $x$ 到 $c$ 和到 $d$ 的距离和等于 $c$ 到 $d$ 的距离。

如图。

![1.png](https://i.loli.net/2018/11/06/5be08f1ee1a75.png)

![2.png](https://i.loli.net/2018/11/06/5be08f22d525e.png)

![3.png](https://i.loli.net/2018/11/06/5be08f2662f90.png)

在树剖过程中的第一次 DFS 时，把字数大小 size 求出来——树剖模板的常规操作。

由于 DFN（DFS 序）在一个子树内的连续性，判断点 $x$ 是否在点 $y$ 的子树里，是非常简单的事情。我们只需要判断 $y$ 的 DFN 是否在 $[\mathrm{DFN}_x, \mathrm{DFN}_x + \mathrm{size}_x)$ 这个区间里，一步搞定。

于是，只需判断四个点，就能得出答案了。具体见代码的 Query 与 Range 函数。

```cpp
#include <algorithm>
#include <cstdio>

const int MAXN = 100010; 

int n, q; 

struct Graph
{
    struct Edge
    {
        int to; 
        Edge *next; 
        Edge(int to, Edge* next): to(to), next(next) {}
        ~Edge(void)
        {
            if(next != NULL)
                delete next; 
        }
    }*head[MAXN]; 
    Graph(int n)
    {
        std :: fill(head + 1, head + n + 1, (Edge*)NULL); 
    }
    ~Graph(void)
    {
        for(int i = 1; i <= n; ++i)
            delete head[i]; 
    }
    void AddEdges(int u, int v)
    {
        head[u] = new Edge(v, head[u]); 
        head[v] = new Edge(u, head[v]); 
    }
}*G; 

namespace HLD
{
    int num; 
    struct Node
    {
        int depth, father, son, top, size, DFN; 
    }s[MAXN]; 
    void DFS1(int u, int k)
    {
        s[u].depth = k; 
        s[u].size = 1; 
        int v; 
        for(Graph :: Edge *i = G -> head[u]; i != NULL; i = i -> next)
            if(!s[v = i -> to].size)
            {
                DFS1(v, k + 1); 
                s[u].size += s[v].size; 
                s[v].father = u; 
                if(s[v].size > s[s[u].son].size)
                    s[u].son = v; 
            }
    }
    void DFS2(int u, int top)
    {
        s[u].top = top; 
        s[u].DFN = ++num; 
        if(s[u].son)
            DFS2(s[u].son, top); 
        int v; 
        for(Graph :: Edge *i = G -> head[u]; i != NULL; i = i -> next)
            if(!s[v = i -> to].DFN)
                DFS2(v, v); 
    }
    void Init(void)
    {
        DFS1(1, 1); 
        DFS2(1, 1); 
    }
    int LCA(int x, int y)
    {
        int a, b; 
        while((a = s[x].top) ^ (b = s[y].top))
            if(s[a].depth > s[b].depth)
                x = s[a].father; 
            else
                y = s[b].father; 
        return s[x].depth < s[y].depth ? x : y; 
    }
    bool Range(int x, int y)
    {
        return s[x].DFN <= s[y].DFN && s[y].DFN < s[x].DFN + s[x].size; 
    }
    bool Query(int a, int b, int c, int d)
    {
        int x = LCA(a, b), y = LCA(c, d); 
        return (Range(x, c) || Range(x, d)) && (Range(y, a) || Range(y, b)); 
    }
}

int main(void)
{
    scanf("%d %d", &n, &q); 
    G = new Graph(n); 
    for(int i = 1, u, v; i < n; ++i)
    {
        scanf("%d %d", &u, &v); 
        G -> AddEdges(u, v); 
    }
    HLD :: Init(); 
    for(int i = 1, a, b, c, d; i <= q; ++i)
    {
        scanf("%d %d %d %d", &a, &b, &c, &d); 
        puts(HLD :: Query(a, b, c, d) ? "Y" : "N"); 
    }
    return 0; 
}
```

谢谢阅读w

---

## 作者：lzpclxf (赞：4)

关于这道题目

很明显的是要求最近公共祖先

求最近公共祖先大概四种方法

1.暴力  
2.倍增  
3.离线tarjan  
4.树链剖分

个人最喜欢树剖所以这道题就用树剖了

题解里用树剖dalao的有很多

但是我还是写了这篇关于树剖的题解

原因是我觉得题解里的树剖我可能看不太明白

STL什么的（我太弱了

所以发一个比较朴素一点的

希望dalao看到不要骂gai吖

这道题目最最最重要的是要发现一个规律：

（至于怎么发现多画几个图试试~~或者看题解~~

只要两条路径相交的话， 那么一条路径的lca一定在另一条路径上

证明我属实不会

话说信息学奥赛不是不需要证明嘛（逃

还有需要注意的一个小细节

是双向边

```cpp
add(u, v), add(v, u);
```

可能只有像我这么弱的才会调这么久没发现

树剖两个dfs

第一个更新dad与size

```cpp
void dfs(int now) {
	size[now] = 1;
	deep[now] = deep[dad[now]] + 1;
	for(int i = head[now]; i; i = e[i].next)
		if(e[i].to != dad[now]) 
			dad[e[i].to] = now, dfs(e[i].to), size[now] += size[e[i].to];
}
```


第二个更新top链顶

```cpp
void dfs1(int now) {
	int k = 0;
	if(!top[now]) top[now] = now;
	for(int i = head[now]; i; i = e[i].next) 
		if(e[i].to != dad[now] && size[e[i].to] > size[k])
			k = e[i].to;
	if(k) top[k] = top[now], dfs1(k);
	for(int i = head[now]; i; i = e[i].next)
		if(e[i].to != dad[now] && e[i].to != k)
			dfs1(e[i].to);
}
```

为什么是这样的顺序

因为更新top是需要区分重链与轻链需要用到size

The Last

```cpp
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100100;
int n, q, head[N], cnt, dad[N], top[N], size[N], deep[N];
struct edge{
	int next, to;
}e[N << 1];
int read() {
	int s = 0, w = 1;
	char ch = getchar();
	while(!isdigit(ch)) {if(ch == '-') w = -1;ch = getchar();}
	while(isdigit(ch)) {s = s * 10 + ch - '0';ch = getchar();}
	return s * w;
}
void add(int x, int y) {
	e[++cnt].next = head[x];
	e[cnt].to = y;
	head[x] = cnt;
}
void dfs(int now) {
	size[now] = 1;
	deep[now] = deep[dad[now]] + 1;
	for(int i = head[now]; i; i = e[i].next)
		if(e[i].to != dad[now]) 
			dad[e[i].to] = now, dfs(e[i].to), size[now] += size[e[i].to];
}
void dfs1(int now) {
	int k = 0;
	if(!top[now]) top[now] = now;
	for(int i = head[now]; i; i = e[i].next) 
		if(e[i].to != dad[now] && size[e[i].to] > size[k])
			k = e[i].to;
	if(k) top[k] = top[now], dfs1(k);
	for(int i = head[now]; i; i = e[i].next)
		if(e[i].to != dad[now] && e[i].to != k)
			dfs1(e[i].to);
}
int lca(int x, int y) {
	while(top[x] != top[y]) {
		if(deep[top[x]] < deep[top[y]]) swap(x, y);
		x = dad[top[x]];
	}
	return deep[x] > deep[y] ? y : x;
}
int main () {
	n = read();q = read();
	for(int i = 1, u, v; i < n; i++) {
		u = read();v = read();
		add(u, v), add(v, u);
	} 
	dfs(1);
	dfs1(1);
	for(int i = 1, a, b, c, d; i <= q; i++) {
		a = read(), b = read(), c = read(), d = read();
		int fir = max(deep[lca(a, b)], deep[lca(c, d)]);
		int sec = max(max(deep[lca(a, c)], deep[lca(a, d)]), max(deep[lca(b, c)], deep[lca(b, d)]));		
		if(sec >= fir) puts("Y");
		else puts("N");
	}
	return 0;
}
```
谢谢收看， 祝身体健康！









---

## 作者：7KByte (赞：2)

为什么都是直接上结论：两点$LCA$在另外两点路径上


其实我们可以打一个优雅的暴力……


显然对于$a-b$的路径，直接将路径上的所有点权加1


再对于$c-d$的路径，查询路径上的点权和，如果点权和不为$1$则说明两条路径有交集


显然对于路径加和路径和查询我们直接硬上树链剖分即可


特别注意每次查询后要将$a-b$路径上的边权清空


唯一的缺点就是代码有点长……


```cpp
#include<bits/stdc++.h>
#define N 100005
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
int n,q,h[N],tot;
struct edge{
	int to,nxt;
}e[N<<1];
void add(int x,int y){
	e[++tot].nxt=h[x];h[x]=tot;e[tot].to=y;
}
int d[N],f[N],tp[N],sz[N],son[N],dfn[N],idx;
void dfs(int x,int fa){
	f[x]=fa;d[x]=d[fa]+1;sz[x]=1;
	for(int i=h[x];i;i=e[i].nxt)
	  if(e[i].to!=fa){
	  	dfs(e[i].to,x);sz[x]+=sz[e[i].to];
	  	if(sz[e[i].to]>sz[son[x]])son[x]=e[i].to;
	  }
}
void dfs2(int x,int top){
	tp[x]=top;dfn[x]=++idx;
	if(!son[x])return;
	dfs2(son[x],top);
	for(int i=h[x];i;i=e[i].nxt)
	  if(e[i].to!=f[x]&&e[i].to!=son[x])
	    dfs2(e[i].to,e[i].to);
}
struct node{
	int l,r,val,add;
}a[N<<2];
#define L a[x].l
#define R a[x].r
#define ls (x<<1)
#define rs (ls|1)
#define A a[x].add
void build(int x,int l,int r){
	L=l;R=r;A=0;a[x].val=0;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(ls,l,mid);
	build(rs,mid+1,r);
}
void updata(int x){
	a[x].val=a[ls].val+a[rs].val;
}
void pushup(int x,int val){
	A+=val;a[x].val+=(R-L+1)*val;
}
void down(int x){
	if(A){
		pushup(ls,A);
		pushup(rs,A);
		A=0;
	}
}
int ask(int x,int l,int r){
	if(L>=l&&R<=r)return a[x].val;
	down(x);
	int mid=(L+R)>>1,sum=0;
	if(mid>=l)sum+=ask(ls,l,r);
	if(mid<r)sum+=ask(rs,l,r);
	return sum;
}
void change(int x,int l,int r,int val){
	if(L>=l&&R<=r)pushup(x,val);
	else{
		down(x);
		int mid=(L+R)>>1;
		if(mid>=l)change(ls,l,r,val);
		if(mid<r)change(rs,l,r,val);
		updata(x);
	}
}
void treechange(int x,int y,int val){
	while(tp[x]^tp[y]){
		if(d[tp[x]]<d[tp[y]])swap(x,y);
		change(1,dfn[tp[x]],dfn[x],val);
		x=f[tp[x]];
	}
	if(d[x]>d[y])swap(x,y);
	change(1,dfn[x],dfn[y],val);
}
int treeask(int x,int y){
	int sum=0;
	while(tp[x]^tp[y]){
		if(d[tp[x]]<d[tp[y]])swap(x,y);
		sum+=ask(1,dfn[tp[x]],dfn[x]);
		x=f[tp[x]];
	}
	if(d[x]>d[y])swap(x,y);
	return sum+ask(1,dfn[x],dfn[y]);
}
int main(){
	scanf("%d%d",&n,&q);
	rep(i,1,n-1){
		int x,y;scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	dfs(1,0);dfs2(1,1);build(1,1,n);
	rep(i,1,q){
		int u,v,x,y;
		scanf("%d%d%d%d",&u,&v,&x,&y);
		treechange(u,v,1);
		int val=treeask(x,y);
		if(val)puts("Y");
		else puts("N");
		treechange(u,v,-1);
	}
	return 0;
}
```

---

## 作者：EarthGiao (赞：2)

先说一下题意：

在一颗树上一个仓鼠从a走到b,一个他的基友从c走到d求他两个是不是会有相遇的地方。

一道求lca的题目。

这道题只看题目是很难找出规律的，但是一画图他的规律就很显然了

可以发现如果两条路径如果相交那一对点的最近公共祖先一定在另一台的路径上

不然如果相交那就这能两条边交叉，这在树中是不可能出现的
否则就不是一棵树

但是怎么确定这到底是不是回相遇的呢？

可以先求出仓鼠目的地b和出发点a的最近公共祖先qwq和surger的

目的地d和出发点c的最近公共祖先awa 

然后分别求出a和d，a和c，b和d，b和c的最近公共祖先来和

前面求出的两个最近公共祖先的深度比较如果有一个这两个

深度小那就是不可行的不然如果都比他深度深或者等于的话

那就是可能遇见的

但是怎么证明只要他们的最近公共祖先的深度大于等于awa和qwq

那就是可行的呢？

这个在三克油大佬的博客里面已经证明的很好啦，我就不多说了
附上链接
## [这里](https://www.luogu.org/blog/I-am-so-low/solution-p3398)

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>

using namespace std;
const int Max = 100005;
struct node
{
	int y,ne;
}a[Max << 1];
int head[Max];
int f[Max][22];
int tot = 0;
void insert(int x,int y)
{
	a[++ tot].y = y;
	a[tot].ne = head[x];
	head[x] = tot;
}
bool use[Max];
int de[Max];
void dfs(int x)
{
	use[x] = true;
	for(int i = head[x];i != 0;i = a[i].ne)
	{
		int ii = a[i].y;
		if(use[ii] == false)
		{
			f[ii][0] = x;
			de[ii] = de[x] + 1;
			dfs(ii);
		}
	}
}

int lca(int x,int y)
{
	if(de[x] < de[y])swap(x,y);
	for(int j = 20;j >= 0;j --)
		if(de[f[x][j]] >= de[y])
			x = f[x][j];
	if(x == y)
		return x;
	for(int i = 20;i >= 0;i --)
		if(f[x][i] != f[y][i])
			x = f[x][i],y = f[y][i];
	return f[x][0];
}

int main()
{
	int n,q;
	int x,y;
	scanf("%d%d",&n,&q);
	for(int i = 1;i < n;++ i)
	{
		scanf("%d%d",&x,&y);
		insert(x,y);
		insert(y,x);
	}
	de[1] = 1;
	dfs(1);
	for(int j = 1;j <= 20;j ++)
		for(int i = 1;i <= n;++ i)
			f[i][j] = f[f[i][j - 1]][j - 1];
	while(q --)
	{
		int aa,bb,cc,dd;
		scanf("%d%d%d%d",&aa,&bb,&cc,&dd);
		int ab = lca(aa,bb);
		int cd = lca(cc,dd);
		
		//int ac = lca(aa,cc);
		//int ad = lca(aa,dd);
		//int bc = lca(bb,cc);
		//int bd = lca(bb,dd);
		int ans = max(de[lca(aa,cc)],de[lca(aa,dd)]);
		ans = max(ans,de[lca(bb,cc)]);
		ans = max(ans,de[lca(bb,dd)]);
		if(ans >= de[ab] && ans >= de[cd])
			cout<<"Y"<<endl;
		else
			cout<<"N"<<endl;
	}
	return 0;
}
```


---

## 作者：用户已注销 (赞：2)


是我校骄傲zzq学长的题耶，当然要来贡献一篇题解咯。

有一个非常清奇的思路，利用路径长度处理。结果发现和作者Mathison的思路一样。这里给出有一点点严谨的证明：

**命题：**

**树上两条路径 A-B C-D 有交点，当且仅当 A->B + C->D ≥ A->C + B->D（X->Y表示X到Y的最短路径长）**

~~证明：闭上眼睛，感受一下，啊，是对的。~~

**证明（口胡）：**

事实上手玩几次也就差不多发现规律了。

如果没有交点，那么A->C就是A->LCA(A,B)->LCA(C,D)->C，显然远了（两个祖先之间的路是白跑的）。B->D同理。

如果有交点/交段，设相交部分端点为P和Q，令：

A->B = A->P->Q->B

则

C->D = C->P->Q->D

或

C->D = C->Q->P->D

对于两种情况，分别有：

A->C = A->P->C , B->D = B->Q->D

或

A->C = A->P->Q->C , B->D = B->P->Q->D

两种情况都满足上面的式子。


---

## 作者：nekko (赞：2)

相遇<=>两条路径有交点

那样的话就直接暴力怼某条链的权值都为1，然后查询另一条链的权值是否有1的地方就行了

树刨维护一下就行

``` cpp
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cmath>
#include <map>

#ifdef ONLINE_JUDGE
    #define debug
    void input() {}
#else
    #define debug printf("passing [%s] in line %d\n", __FUNCTION__, __LINE__)
    void input() {freopen("in", "r", stdin);}
#endif

using namespace std;

typedef long long ll;

const int N = 200010;

int n, q;

int head[N], rest[N], to[N], tot;

void add(int u, int v) {
    ++ tot;
    to[tot] = v;
    rest[tot] = head[u];
    head[u] = tot;
}

namespace segTree {
    int l[N * 4], r[N * 4], tag[N * 4], sum[N * 4];
    void build(int id, int cl, int cr) {
        int cm = (cl + cr) >> 1;
        id[l] = cl;
        id[r] = cr;
        if(cl != cr) {
            build(id << 1, cl, cm);
            build(id << 1 | 1, cm + 1, cr);
        }
    }
    void push(int id) {
        if(id[tag]) {
            (id << 1)[tag] += id[tag];
            (id << 1 | 1)[tag] += id[tag];
            id[sum] += id[tag] * (id[r] - id[l] + 1);
            id[tag] = 0;
        }
    }
    void update(int id) {
        push(id), push(id << 1), push(id << 1 | 1);
        id[sum] = (id << 1)[sum] + (id << 1 | 1)[sum];
    }
    void modify(int id, int ql, int qr, int v) {
        push(id);
        if(id[l] > qr || id[r] < ql) return;
        if(ql <= id[l] && id[r] <= qr) id[tag] += v;
        else {
            modify(id << 1, ql, qr, v);
            modify(id << 1 | 1, ql, qr, v);
            update(id);
        }
    }
    int query(int id, int ql, int qr) {
        push(id);
        if(id[l] > qr || id[r] < ql) return 0;
        if(ql <= id[l] && id[r] <= qr) return id[sum];
        else return query(id << 1, ql, qr) + query(id << 1 | 1, ql, qr);
    }
}

namespace splitTree {
    int sz[N], deep[N], top[N], fa[N], son[N], l[N], r[N], cnt;
    void dfs1(int u) {
        u[sz] = 1;
        u[deep] = u[fa][deep] + 1;
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(v != u[fa]) {
                v[fa] = u;
                dfs1(v);
                u[sz] += v[sz];
                if(u[son][sz] < v[sz]) {
                    u[son] = v;
                }
            }
        }
    }
    void dfs2(int u, int tp) {
        u[top] = tp;
        u[l] = ++ cnt;
        if(u[son]) dfs2(u[son], tp);
        for(int i = head[u] ; i ; i = rest[i]) {
            int v = to[i];
            if(v != u[fa] && v != u[son]) {
                dfs2(v, v);
            }
        }
        u[r] = cnt;
    }
    void work() {
        dfs1(1);
        dfs2(1, 1);
        segTree :: build(1, 1, n);
    }
}

namespace solve {
    using namespace splitTree;
    using namespace segTree;
    void add(int u, int v, int val) {
        while(u[top] != v[top]) {
            if(u[top][deep] < v[top][deep]) swap(u, v);
            modify(1, u[top][splitTree :: l], u[splitTree :: l], val);
            u = u[top][fa];
        }
        if(u[deep] > v[deep]) swap(u, v);
        modify(1, u[splitTree :: l], v[splitTree :: l], val);
    }
    bool check(int u, int v) {
        while(u[top] != v[top]) {
            if(u[top][deep] < v[top][deep]) swap(u, v);
            if(query(1, u[top][splitTree :: l], u[splitTree :: l])) return 1;
            u = u[top][fa];
        }
        if(u[deep] > v[deep]) swap(u, v);
        return query(1, u[splitTree :: l], v[splitTree :: l]);
    }
    void work(int u1, int v1, int u2, int v2) {
        add(u1, v1, 1);
        if(check(u2, v2)) puts("Y");
        else puts("N");
        add(u1, v1, -1);
    }
}

int main() {
    input();
    scanf("%d%d", &n, &q);
    for(int i = 1, u, v ; i < n ; ++ i) {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    splitTree :: work();
    for(int i = 1, u1, v1, u2, v2 ; i <= q ; ++ i) {
        scanf("%d%d%d%d", &u1, &v1, &u2, &v2);
        solve :: work(u1, v1, u2, v2);
    }
}
```

---

## 作者：在想Peach (赞：2)

~~说了各位可能不信，老衲利用tarjan的毒瘤属性451ms切了这个小东西~~

方法和诸位大佬都一样，唯一和诸位大佬都不一样的是老衲写的是两遍tarjan。

```cpp
#include<iostream>
#include<algorithm>
#include<cstring>
#include<cstdio>
#include<queue>
#include<stack>
#include<cmath>
using namespace std;
const int maxn=1000005;
struct node
{
    int to,nxt,fr,kl;
}t[maxn],tl[maxn];
int x,y,a[maxn],b[maxn],c[maxn],d[maxn],n,m,deep[maxn];
int to[maxn],nxt[maxn],head[maxn],headl[maxn],tot,totl;
int headll[maxn],totll,fl[maxn];
int ans[maxn][3],f[maxn];
bool p[maxn],ansy[maxn],pl[maxn];
int read()
{
    char z=getchar();
    int x=0,y=1;
    while(z<'0'||z>'9'){if(z=='-')y=-1;z=getchar();}
    while(z>='0'&&z<='9'){x=x*10+z-'0';z=getchar();}
    return x*y;
}
int find(int x)
{
    if(f[x]==x)return x;
    return f[x]=find(f[x]);
}
int findl(int x)
{
    if(fl[x]==x)return x;
    return fl[x]=findl(fl[x]);
}
void add(int x,int y)
{
    to[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}
void addl(int x,int y,int c,int kl)
{
    t[++totl].fr=c;
    t[totl].kl=kl;
    t[totl].to=y;
    t[totl].nxt=headl[x];
    headl[x]=totl;
}
void addll(int x,int y,int c,int kl)
{
    tl[++totll].fr=c;
    tl[totll].kl=kl;
    tl[totll].to=y;
    tl[totll].nxt=headll[x];
    headll[x]=totll;
}
void tarjan(int x,int faa,int dep)
{
    f[x]=x;deep[x]=dep;
    for(int i=head[x];i;i=nxt[i])
    {
        int g=to[i];
        if(g==faa)continue;
        tarjan(g,x,dep+1);f[g]=x;
    }
    for(int i=headl[x];i;i=t[i].nxt)
    {
        int g=t[i].to;
        if(f[g])ans[t[i].fr][t[i].kl]=find(g);
    }
}
void tarjan2(int x,int faa)
{
    fl[x]=x;
    for(int i=head[x];i;i=nxt[i])
    {
        int g=to[i];
        if(g==faa)continue;
        tarjan2(g,x);fl[g]=x;
    }
    for(int i=headll[x];i;i=tl[i].nxt)
    {
        int g=tl[i].to;
        if(tl[i].kl==1){if(fl[g]&&findl(g)==x)ansy[tl[i].fr]=1;}
        else if(fl[g]&&findl(g)==g)ansy[tl[i].fr]=1;
    }
}
int main()
{
    n=read();m=read();
    for(int i=1;i<=n-1;i++)
    {
        x=read();y=read();add(x,y);add(y,x);
    }
    for(int i=1;i<=m;i++)
    {
        a[i]=read();b[i]=read();c[i]=read();d[i]=read();
        addl(a[i],b[i],i,1);addl(b[i],a[i],i,1);
        addl(c[i],d[i],i,2);addl(d[i],c[i],i,2);
    }
    f[1]=1;
    tarjan(1,0,1);
    for(int i=1;i<=m;i++)
    {
        if(ans[i][1]==ans[i][2])ansy[i]=1;
        else
        {
        	if(deep[ans[i][1]]>=deep[ans[i][2]])
        	{
            addll(ans[i][1],c[i],i,1);addll(c[i],ans[i][1],i,2);
            addll(ans[i][1],d[i],i,1);addll(d[i],ans[i][1],i,2);
        }
        else
        {
        	addll(ans[i][2],a[i],i,1);addll(a[i],ans[i][2],i,2);
            addll(ans[i][2],b[i],i,1);addll(b[i],ans[i][2],i,2);
		}
        }
    }
    fl[1]=1;
    tarjan2(1,0);
    for(int i=1;i<=m;i++)if(ansy[i])puts("Y");else puts("N");;
    return 0;
}
```


---

## 作者：Qglin_ (赞：1)

一道图论题。大意就是给你一个树，问两条树上两点间最短路径有没有交点。看到这一题的第一反应是树剖，分别把两点路径上的所有点点权+1，然后求树上有没有点权不小于2的点，如果有就输出Y。然后发现有多组询问，遂GG。



换一个思路。树上两点$u,v$间最短路径记为$(u,v)$，则$(u,v)$一定经过两点$LCA(u,v)$。而判断两条路$(a,b)$和$(c,d)$是否有交点的方法，就是判断$LCA(a,b)$是不是在$(c,d)$上，或者$LCA(c,d)$是不是在$(a,b)$上。我们先分别求出$O=LCA(a,b),P=LCA(c,d)$，设$dep[x]$表示$x$的深度，且$dep[O]>dep[P]$，那么如下这一棵树：

![](http://wx1.sinaimg.cn/mw690/005KG2V0ly1fzrfu62oo6j30rs0rsgmj.jpg)

显然，$(c,d)$是这样的：

![](http://wx1.sinaimg.cn/mw690/005KG2V0ly1fzrfueihw4j30ru0rtmxv.jpg)

显然可见，在这个树上，联系树的定义，当$O$点在$P,2,3,c,d$时，$(a,b)$和$(c,d)$有交点,此时$LCA(O,c)==O$或$LCA(O,d)==O$。不难归纳出，扩展到任何树上，这个结论都是成立的。



根据这些就不难写出代码了。实现的时候使用树链剖分LCA，求解的时候调整$O$和$P$就可以了。



帖代码：

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
const int N = 100005;

inline int fd() {
    int x = 0, f = 1; char ch = getchar();
    while(!isdigit(ch)) {if(ch == '-') f = -f; ch = getchar();}
    while(isdigit(ch)) {x = x*10+ch-'0'; ch = getchar();}
    return x*f;
}

int cnt, n, m;
int id[N], dep[N], fa[N], siz[N], son[N], top[N];

int head[N], edcnt;
struct edge {int to, nxt;} ed[N << 1];
inline void ADD(int x,int y) {
    ed[++edcnt].nxt = head[x];
    head[x] = edcnt;
    ed[edcnt].to = y;
}

void dfs1(int x,int f,int deep) {
    dep[x] = deep;
    fa[x] = f;
    siz[x] = 1;
    int maxson = -1;
    for (int i = head[x]; i; i = ed[i].nxt) {
        int y = ed[i].to;
        if (y == f) continue;
        dfs1(y, x, deep+1);
        siz[x] += siz[y];
        if (maxson < siz[y]) {
            son[x] = y;
            maxson = siz[y];
        }
    }
}
void dfs2(int x,int topf) {
    id[x] = ++cnt;
    top[x] = topf;
    if (!son[x]) return;
    dfs2(son[x], topf);
    for (int i = head[x]; i; i = ed[i].nxt) {
        int y = ed[i].to;
        if (y == fa[x] || y == son[x]) continue;
        dfs2(y, y);
    }
}
inline int LCA(int x,int y) {
    while (top[x] != top[y]) {
        if (dep[top[x]] < dep[top[y]]) swap(x, y);
        x = fa[top[x]];
    }
    return dep[x] < dep[y] ? x : y;
}

int a, b, c, d, O, P;
int main() {
    n = fd(); m = fd();
    for (int i = 1; i < n; ++i) {
        a = fd(); b = fd();
        ADD(a, b); ADD(b, a);
    }
    dfs1(1, 0, 1);
    dfs2(1, 1);
    for (int i = 1; i <= m; ++i) {
        a = fd(); b = fd(); c = fd(); d = fd();
        O = LCA(a, b);
        P = LCA(c, d);
        if (dep[O] < dep[P]) {
            swap(O, P); swap(a, c); swap(b, d);
        }
        if (LCA(O, c)==O || LCA(O, d)==O) puts("Y");
        else puts("N");
    }
    return 0;
}
```

~~树剖一时爽，一直树剖一直爽~~

---

## 作者：伊斯卡尔的风 (赞：1)

求LCA裸题。。。 可以用倍增或者tarjan求 （建议用倍增，好像有人用tarjanTLE了。。。）

另外最好写输入输出优化。。不然可能会挂掉几个点。。

思路：设从A到B，经过的深度最小的点为X 同理，C,D的为Y

题目是一个点从A出发到B  一个从C出发到D

那么从A到B可以分解成 先从A到X 再从X到B。。。 C同理

假设能相遇 那么

要么在A到X的过程A,B相遇 要么在X到B的过程A,B相遇


对于在A到X的过程相遇的情况 又可以分解为：

情况1：

在A到X的过程和 C到Y的过程 中A,B相遇 此时相遇点的深度必然大于等于MIN（X深度，Y深度）

情况2：

在A到X的过程和 Y到D的过程 中A,B相遇 此时相遇点的深度必然大于等于MIN （X深度，Y深度）

另一种情况同理。。。

所以显然只要求出MIN=min(lca(a,b),lca(c,d));(lca返回的是两个点公共祖先的最大深度)

假如lca(a,c) lca(a,d) lca(b,c) lca(b,d) 中有任意一个大于等于MIN 的话 那么可以相遇 否则不能

倍增的算法代码：

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
#define repi(i,a,b) for(int i=a;i<=b;i++)
#define repd(i,a,b) for(int i=a;i>=b;i--)
#define debug(x) cout<<#x<<'='<<x<<' '
#define endl cout<<'\n'
const int MAXN=100001+100;
int ZS,n,q;
struct edge
{
    int s,t,next;
    edge(int s=0,int t=0,int next=0):s(s),t(t),next(next) {}
};

    int fa[MAXN][30];
    vector<edge> edges;
    int head[MAXN],depth[MAXN],root=1;
    void add(int s,int t)
    {
        edges.push_back(edge(s,t,head[s]));
        head[s]=edges.size()-1;
        edges.push_back(edge(t,s,head[t]));
        head[t]=edges.size()-1;
    }
    void build(int pre,int u,int dp)
    {
//        repi(i,1,n) cout<<depth[i]<<' '; endl;
        depth[u]=dp;
        repi(i,1,ZS) fa[u][i]=fa[fa[u][i-1]][i-1];
        for(int i=head[u];i!=-1;i=edges[i].next)
        {
            edge& e=edges[i];
            if(e.t!=pre)
            {
                fa[e.t][0]=u;
                build(u,e.t,dp+1);
            }
        }
    }
    int lca(int a,int b)
    {
        if(depth[a]>depth[b]) swap(a,b);
        repd(i,ZS,0) if(depth[a]<=depth[fa[b][i]]) b=fa[b][i];
        if(a==b) return depth[a];
        repd(i,ZS,0) if(fa[a][i]!=fa[b][i]) {a=fa[a][i]; b=fa[b][i];}
        return depth[fa[a][0]];
    }

int _read()
{
    int x=0; char tem;
    while(!isdigit(tem=getchar()));
    do{x=(x<<3)+(x<<1); x+=tem-'0';}
    while(isdigit(tem=getchar()));
    return x;
}

int main()
{
    memset(head,-1,sizeof(head));
//    cout<<"run";
//    freopen("data.in","r",stdin);
    n=_read(); q=_read();
    ZS=log(n)/log(2)+1;
    repi(i,1,n-1)
    {
        int s,t; s=_read(); t=_read();
        add(s,t);
    }
    repi(i,1,n) fa[i][0]=i;
    build(root,root,1);
//    debug(lca(2,2)); debug(depth[2]);
    repi(i,1,q)
    {
        int a,b,c,d;
        a=_read(); b=_read(); c=_read(); d=_read();
//        cout<<a<<' '<<b<<' '<<c<<' '<<d<<'\n';
        int MAX=max(lca(a,b),lca(c,d));
//        debug(MAX); debug(lca(a,c)); endl;
        int TEM1=max(lca(a,c),lca(a,d));
        int TEM2=max(lca(b,c),lca(b,d));
        int CMP=max(TEM1,TEM2);
        if(CMP>=MAX) printf("Y\n");
            else printf("N\n");
    }
    return 0;
}

```

---

## 作者：legend_life (赞：1)

这题细节太多了，感觉非常毒瘤，花了我好长时间才调出来的，写篇题解纪念一下。~~我太弱了QwQ~~

好，废话不多说，开始讲题。

首先，一句话题意。这道题让我们求树上两条路径是否相交。

大家画一画树上的某两点之间的路径就会发现它们可能长这样

![](https://cdn.luogu.com.cn/upload/pic/62506.png )

或者这样

![](https://cdn.luogu.com.cn/upload/pic/62506.png )

总之，一条路径要么从一个点先向上，再向下。要么只有这两步中的一步。而路径上的最高点恰恰就是这两个点的LCA。

由此，这题用LCA算法应该是没有问题的了。

于是开始愉快地打代码，细节在文章的末尾说。

```cpp
#include <cmath>
#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

const int MAXN = 100010;
int head[MAXN], lg2[MAXN], depth[MAXN], fa[MAXN][21];
int n, q, cnt;

struct Edge
{
	int to;
	int nxt;
}e[MAXN << 1];

void AddEdge (int from, int to)
{
	e[++ cnt].to = to;
	e[cnt].nxt = head[from];
	head[from] = cnt;
}

void dfs (int now, int father)
{
	depth[now] = depth[father] + 1;
	fa[now][0] = father;
	for (int i = head[now]; i; i = e[i].nxt)
	{
		int v = e[i].to;
		if (v == father)
			continue;
		dfs (v, now);
	}
}

void init ()
{
	for (int i = 2; i <= n; ++ i)
		lg2[i] = lg2[i - 1] + ((1 << (lg2[i - 1] + 1)) == i);      	
	
	dfs (1, 1);
	for (int j = 1; j < 20; ++ j)
		for (int i = 1; i <= n; ++ i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
}

int lca (int x, int y)
{
	if (depth[x] > depth[y])
		swap (x, y);
	while (depth[x] < depth[y])
		y = fa[y][lg2[depth[y] - depth[x]]];
	if (x == y)
		return x;
	
	for (int i = lg2[depth[x]]; i >= 0; -- i)
		if (fa[x][i] != fa[y][i])
		{
			x = fa[x][i];
			y = fa[y][i];
		}
	return fa[x][0];
}

int main()
{
	scanf ("%d%d", &n, &q);
	for (int i = 1; i < n; ++ i)
	{
		int u, v;
		scanf ("%d%d", &u, &v);
		AddEdge (u, v);
		AddEdge (v, u);
	}
	init ();
	for (int i = 1; i <= q; ++ i)
	{
		int u1, v1, u2, v2;
		scanf ("%d%d%d%d", &u1, &v1, &u2, &v2);
		int lca1 = lca (u1, v1), lca2 = lca (u2, v2);
		if (dis (u2, lca1) + dis (lca1, v2) == dis (u2, v2) || dis (u1, lca2) + dis (v1, lca2) == dis (u1, v1))
		{
			printf ("Y\n");
		}
		else
			printf ("N\n");
	}
	return 0;
}
```

这题细节一大堆，

1. 对于判断两条路径相不相交的问题，如果用LCA直接判断真的极为麻烦，还要各种讨论。。。我讨论了半天，从未改变过我爆零的结果（可能是我太菜了）。于是我就参考了题解中的用距离判断的方法，效果显著。

2. dis函数这一段要加绝对值，如果不加会凉凉

```cpp
int dis (int p1, int p2)
{
	int p = lca (p1, p2);
	return abs (depth[p1] - depth[p]) + abs (depth[p2] - depth[p]);
}
```

3. LCA函数中这一句话 i 要 >= 0。

```cpp
	for (int i = lg2[depth[x]]; i >= 0; -- i)
```

这些都是我曾经凉过的点，希望大家不要犯这样的错误。

这是我第一篇题解，卖个萌求管理员大大给过QwQ

---

## 作者：A4paper (赞：1)

蒟蒻做完题后看了一眼题解，发现没人用我这种方法做的，于是决定分享一下这种做法。

首先说明，我用的树剖。

先上代码为敬：

```cpp
#include <stdio.h>
#include <iostream>
using namespace std;
#define MAXN 100005

int n,m,cnt;
int head[MAXN];
int FA[MAXN],dep[MAXN],size[MAXN],son[MAXN];
int Top[MAXN],DFN[MAXN],END[MAXN];

struct node{
	int to,next;
}map[2*MAXN];

void add(int u, int v)
{
	map[++cnt] = (node){v,head[u]};
	head[u] = cnt;
}

void dfs1(int u, int fa)
{
	FA[u] = fa;	size[u] = 1;
	dep[u] = dep[fa]+1;
	for(int k=head[u];k;k=map[k].next)
	{
		int v = map[k].to;
		if(v == fa) continue;
		dfs1(v,u);
		size[u] += size[v];
		if(size[son[u]] < size[v]) son[u] = v;
	}
}

void dfs2(int u, int top)
{
	DFN[u] = ++cnt;
	Top[u] = top;	END[u] = cnt;
	if(!son[u]) return;
	dfs2(son[u],top);
	END[u] = END[son[u]];
	for(int k=head[u];k;k=map[k].next)
	{
		int v = map[k].to;
		if(v==FA[u] || v==son[u]) continue;
		dfs2(v,v);
		END[u] = END[v];
	}
}

int LCA(int x, int y)
{
	int nx = Top[x]; int ny = Top[y];
	while(nx != ny)
	{
		if(dep[nx] < dep[ny])
		{
			swap(nx,ny);
			swap( x, y);
		}
		x = FA[nx];
		nx = Top[x];
	}
	if(x == y) return x;
	if(dep[x] > dep[y]) swap(x,y);
	return x;
}

int main(void)
{
	cin >> n >> m;
	for(int i=1;i<n;i++)
	{
		int u,v;	cin >> u >> v;
		add(u,v);	add(v,u);
	}
	cnt = 0;	dfs1(1,0);	dfs2(1,1);
	for(int j=1;j<=m;j++)
	{
		int a,b,c,d;
		cin >> a >> b >> c >> d;
		int t1 = LCA(a,b);
		int t2 = LCA(c,d);
		if (((END[t1]>=DFN[c] && DFN[t1]<=DFN[c]) || (END[t1]>=DFN[d] && DFN[t1]<=DFN[d]))
		 && ((END[t2]>=DFN[a] && DFN[t2]<=DFN[a]) || (END[t2]>=DFN[b] && DFN[t2]<=DFN[b])))
			 cout << "Y\n";
		else cout << "N\n";
	}
	return 0;
}
```

大家可能看到代码中一坨判断非常的头大，不过不要急，让我从头说起。

首先，我们设 $t1  = LCA(a,b)\ ,\ t2 = LCA(c,d)$

很多题解都提到了，**如果两条路径相交，那么一定有一条路径的LCA在另一条路径上**（这里引用的 @沧澜 的题解，因为他总结的很到位）。那么我们在这个基础上继续考虑一下（当然，结合画图口感更佳），可以得到如下结论：

$c$ 或 $d$ 在 $t1$ 的子树中 ，并且， $a$ 或 $b$ 在 $t2$ 的子树中。（也有可能 $a,b$ 都在 $t2$ 的子树中 或 $c,d$ 都在 $t1$ 的子树中，不过这不影响），那么，求两遍 $LCA$ 后只要判断这四个点与子树的关系就好。怎么判断呢？答案是利用树剖记下的 $DFS$ 序，并记录子树 $i$ 中的最大 $DFS$ 序 $END[i]$ （参考代码中的 $dfs2()$ 函数）然后比大小就好了（参考那一大坨判断）

求过求过，安利[博客](https://www.luogu.org/blog/A4paper/)


---

## 作者：Drifterming (赞：1)

```cpp
//今天考试题T1的单组数据版 
//看着贼眼熟 就是想不起咋做来
//考虑了一下特判情况，好麻烦，就写了个树剖打打暴力，竟然A了2333

//题目就是让着判断两条路径是否有交
//我们树剖建起线段树来，就成了一个线段树上对应区间是否相交的问题
//那么我们对其中一个人的路染色，另一个人去线段树立找它的路径上是否有被染色的点就好了
//线段树在修改的时候对沿途的节点染色，flag=1表示这个节点的区间内有被染色的点，tag=1表示这个区间被完全染色 
//查询的时候，如果递归过程中到了一个tag==col的点，说明肯定相交了，return true
//否则继续递归，直到找到一个tag==col的点或合法区间的点 
//如果当前节点flag=1，不能像tag那样直接return true，因为可能被染色的那些点不在查询区间内 
 
//时间复杂度O(m*log^2n) 比倍增多一个log  
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

inline int read()
{
	char c=getchar();int num=0;
	for(;!isdigit(c);c=getchar());
	for(;isdigit(c);c=getchar())
		num=num*10+c-'0';
	return num;
}

const int N=1e5+5;

int n,m,col;

int head[N],num_edge;
struct Node
{
    int fa,son;
    int size,dep,top;
    int s,t;
}node[N];

struct Edge
{
    int v,nxt;
}edge[N<<1];

#define lson tree[root].ls
#define rson tree[root].rs
struct TREE
{
    int ls,rs;
	int flag,tag;
}tree[N<<1];
int now_node,Root;

inline void add_edge(int u,int v)
{
    edge[++num_edge].v=v;
    edge[num_edge].nxt=head[u];
    head[u]=num_edge;
}

void dfs1(int u)
{
    node[u].size=1;
    node[u].son=0;
    for(int i=head[u],v;i;i=edge[i].nxt)
    {
        v=edge[i].v;
        if(v==node[u].fa)
            continue;
        node[v].fa=u;
        node[v].dep=node[u].dep+1;
        dfs1(v);
        node[u].size+=node[v].size;
        if(node[v].size>node[node[u].son].size)
            node[u].son=v;
    }
}

int bound;
void dfs2(int u,int top)
{
    node[u].top=top;
    node[u].s=++bound;
    if(node[u].son)
    {
        dfs2(node[u].son,top);
        for(int i=head[u],v;i;i=edge[i].nxt)
        {
            v=edge[i].v;
            if(v==node[u].fa||v==node[u].son)
                continue;
            dfs2(v,v);
        }
    }
    node[u].t=bound;
}

void build(int &root,int l,int r)
{
    root=++now_node;
    tree[root].flag=0;
    if(l==r)
    	return;
    int mid=l+r>>1;
    build(lson,l,mid);
    build(rson,mid+1,r);
}

void modify(int root,int l,int r,int L,int R)
{
	tree[root].flag=col;	//这个区间内有被染色的点 
	if(l==L&&r==R)
	{
		tree[root].tag=col;		//打上tag标记：这个区间被完全染色 
		return;
	}
	int mid=l+r>>1;
	if(R<=mid)
		modify(lson,l,mid,L,R);
	else if(L>mid)
		modify(rson,mid+1,r,L,R);
	else
		modify(lson,l,mid,L,mid),modify(rson,mid+1,r,mid+1,R);
	return;
}

bool query(int root,int l,int r,int L,int R)
{
	if(tree[root].flag!=col)	//区间内没有被染色的点 
		return false;
	if(l==L&&r==R)		//找到一个查询区间 
		return true;
	if(tree[root].tag==col)		//区间被完全染色了 
		return true;
	int mid=l+r>>1;
	if(R<=mid)
		return query(lson,l,mid,L,R);
	else if(L>mid)
		return query(rson,mid+1,r,L,R);
	else
	{
		bool f1=query(lson,l,mid,L,mid);
		if(f1)
			return true;
		bool f2=query(rson,mid+1,r,mid+1,R);
		return f2;
	}
}

inline void Modify(int x,int y)
{
    int fx=node[x].top,fy=node[y].top;
    while(fx!=fy)
    {
        if(node[fx].dep>node[fy].dep)
        {
            modify(Root,1,n,node[fx].s,node[x].s);
            x=node[fx].fa;
            fx=node[x].top;
        }
        else
        {
            modify(Root,1,n,node[fy].s,node[y].s);
            y=node[fy].fa;
            fy=node[y].top;
        }
    }
    if(node[x].dep>node[y].dep)
        modify(Root,1,n,node[y].s,node[x].s);
    else
        modify(Root,1,n,node[x].s,node[y].s);
    return;
}

inline bool Query(int x,int y)
{
    int fx=node[x].top,fy=node[y].top;
	bool ans=0;
    while(fx!=fy)
    {
        if(node[fx].dep>node[fy].dep)
        {
            ans|=query(Root,1,n,node[fx].s,node[x].s);
            x=node[fx].fa;
            fx=node[x].top;
        }
        else
        {
            ans|=query(Root,1,n,node[fy].s,node[y].s);
            y=node[fy].fa;
            fy=node[y].top;
        }
        if(ans==1)
        	return true;
    }
    if(node[x].dep>node[y].dep)
        ans|=query(Root,1,n,node[y].s,node[x].s);
    else
        ans|=query(Root,1,n,node[x].s,node[y].s);
    return ans;
}

int main()
{
	n=read(),m=read();
	for(int i=1,a,b;i<n;++i)
	{
		a=read(),b=read();
		add_edge(a,b);
		add_edge(b,a);
	}	
	node[1].dep=0;
	dfs1(1);
	dfs2(1,1);
	build(Root,1,n);
	for(int i=1,a,b,c,d;i<=m;++i)
	{
		++col;
		a=read(),b=read(),c=read(),d=read();
		Modify(a,b);
		if(Query(c,d))
			puts("Y");
		else
			puts("N");
	}
	return 0;
}
```

---

## 作者：pzc2004 (赞：0)

[题目传送门](https://www.luogu.org/problem/P3398)

题目要求两个点之间的路径和另外两个点之间的路径有没有公共点，我们可以先将前两个点之间的路径都打上标记，再查询后两个点之间的路径上是否存在标记即可，每组查询完成后记得清空一下标记。用树链剖分维护，复杂度$O(Nlog^2N)$。

代码：
``` cpp
#include<bits/stdc++.h>
using namespace std;
#define N 100001
inline int read(){int x=0;char c=getchar();while(c<'0' || c>'9')c=getchar();while(c>='0' && c<='9')x=(x<<3)+(x<<1)+(c^'0'),c=getchar();return x;}//快读
int n,q,head[N],cnt1,cnt2,id[N],fa[N],dep[N],top[N],siz[N],son[N];
struct sb2//链式前向星存图
{
    int a,b;
}e[N<<1];
struct sb
{
    int s,la;
}tre[N<<2];
inline void add(const int &a,const int &b){e[++cnt1].a=head[a],e[cnt1].b=b,head[a]=cnt1;}
inline void dfs1(const int &x,const int &y)//树剖模板
{
    fa[x]=y;
    dep[x]=dep[y]+1;
    siz[x]=1;
    for(register int i=head[x];i;i=e[i].a)
    {
        if(e[i].b==y)continue;
        dfs1(e[i].b,x);
        siz[x]+=siz[e[i].b];
        if(siz[e[i].b]>siz[son[x]])son[x]=e[i].b;
    }
}
inline void dfs2(const int &x,const int &y)
{
    top[x]=y;
    id[x]=++cnt2;
    if(!son[x])return;
    dfs2(son[x],y);
    for(register int i=head[x];i;i=e[i].a)
    {
        if(e[i].b==son[x] || e[i].b==fa[x])continue;
        dfs2(e[i].b,e[i].b);
    }
}
inline void pushdown(int p)//线段树模板
{
    if(tre[p].la==1)
    {
        tre[p<<1].s=tre[p<<1].la=tre[p<<1|1].s=tre[p<<1|1].la=1;tre[p].la=0;
    }
    else if(tre[p].la==-1)
    {
        tre[p<<1].s=tre[p<<1|1].s=0,tre[p<<1].la=tre[p<<1|1].la=-1;tre[p].la=0;
    }
}
inline void add(int p,int l,int r,int a1,int a2,int a3)
{
    if(a1<=l && r<=a2)if(a3==1){tre[p].s=tre[p].la=1;return;}else{tre[p].s=0,tre[p].la=-1;return;}
    pushdown(p);
    int mid=l+r>>1;
    if(mid>=a1)add(p<<1,l,mid,a1,a2,a3);
    if(mid<a2)add(p<<1|1,mid+1,r,a1,a2,a3);
    tre[p].s=tre[p<<1].s|tre[p<<1|1].s;
}
inline int query(int p,int l,int r,int a1,int a2)//
{
    if(a1<=l && r<=a2)return tre[p].s;
    pushdown(p);
    int mid=l+r>>1,ans=0;
    if(mid>=a1)ans=ans || query(p<<1,l,mid,a1,a2);
    if(mid<a2)ans=ans || query(p<<1|1,mid+1,r,a1,a2);
    return ans;
}
signed main()
{
    n=read(),q=read();
    for(register int i=1,a,b;i<n;i++)a=read(),b=read(),add(a,b),add(b,a);
    dfs1(1,0);
    dfs2(1,1);
    while(q--)
    {
        int x=read(),y=read();
        bool bb=0;
        while(top[x]!=top[y])//打标机
        {
            if(dep[top[x]]<dep[top[y]])swap(x,y);
            add(1,1,n,id[top[x]],id[x],1);
            x=fa[top[x]];
        }
        if(dep[x]>dep[y])swap(x,y);
        add(1,1,n,id[x],id[y],1);
        x=read(),y=read();
        while(top[x]!=top[y])//查询标记
        {
            if(dep[top[x]]<dep[top[y]])swap(x,y);
            bb=bb || query(1,1,n,id[top[x]],id[x]);
            x=fa[top[x]];
        }
        if(dep[x]>dep[y])swap(x,y);
        bb=bb || query(1,1,n,id[x],id[y]);
        if(bb)putchar('Y');else putchar('N');
        putchar('\n');
        add(1,1,n,1,n,0);//查询后记得清空标记
    }
}
```
![](https://www.luogu.org/images/congratulation.png)

---

## 作者：wanxiang_zx (赞：0)

```
#include<iostream>
#include<cmath>
#include<cstdio>
#include<string>
#include<algorithm>
using namespace std;
const int maxn=1100000;
int n,m,num=0;
int d[maxn],next[2*maxn],head[maxn],e[maxn];
int dep[maxn],anc[maxn][30];
void add(int x,int y)
{
     e[++num]=y;
     next[num]=head[x];
     head[x]=num;
}
//链式前向星 存图 ，需建双向边 
void dfs(int x,int fa)
{
     //fa为父结点 
     dep[x]=dep[fa]+1;
     //dep记录每个结点到根结点的深度 
     d[x]=d[fa]+1;
     //dep记录每个结点到根结点的距离 因为这道题边权为1，所以与深度数值相同 
     for(int i=1;(1<<i)<=dep[x];i++)
       anc[x][i]=anc[anc[x][i-1]][i-1];
     //anc[x][i]记录x的第2的i次方个祖先点 
     //例如anc[x][0]为x的第2的0次方个祖先点，也就是它的父结点 
     //因为x的祖先点深度一定小于x，所以(1<<i)<=dep[x]
     for(int i=head[x];i;i=next[i])
     {
       int y=e[i];
       if(y==fa)
         continue;
       anc[y][0]=x;
       dfs(y,x);
     }
}
int lca(int x,int y)
{
    if(dep[x]<dep[y])  swap(x,y);
    for(int i=20;i>=0;i--)
      if(dep[anc[x][i]]>=dep[y])
        x=anc[x][i];
    if(x==y)
      return x;
    for(int i=20;i>=0;i--)
      if(anc[x][i]!=anc[y][i])
      {
        x=anc[x][i];
        y=anc[y][i];
      }
    return anc[x][0];
}
int main()
{
    //如果相交,记k1=lca(a,b),k2=lca(c,d)
    //则必有k1在c~d路径上或k2在a~b路径上
    //如果一个点在一条路径上,则满足该点到路径两端点的距离之和等于两端点的距离
    scanf("%d%d",&n,&m);
    for(int i=1;i<n;i++)
    {
      int x,y;
      scanf("%d%d",&x,&y);
      add(x,y);
      add(y,x);
    }
    dep[0]=0;
    anc[1][0]=0;
    dfs(1,0);
    for(int i=1;i<=m;i++)
    {
      int a,b,c,dd;
      scanf("%d%d%d%d",&a,&b,&c,&dd);
      int k1=lca(a,b);
      //k1为a,b两端点的最近公共祖先 
      int k2=lca(c,dd);
      //k2为c,dd两端点的最近公共祖先 
      int x1=d[a]+d[b]-2*d[k1];
      //x1为a,b两端点的距离 
      int x2=d[c]+d[dd]-2*d[k2];
      //x2为c,dd两端点的距离
      int y1=d[a]+d[k2]-2*d[lca(a,k2)]+d[b]+d[k2]-2*d[lca(b,k2)];
      //y1为k2到a,b两端点的距离和 
      int y2=d[c]+d[k1]-2*d[lca(c,k1)]+d[dd]+d[k1]-2*d[lca(dd,k1)];
      //y2为k1到c,dd两端点的距离和 
      if(y1==x1 || y2==x2)//如果k1在a,b区间上 或 k2在c,dd区间上，说明两区间有公共部分，即有可能相遇 
        printf("Y\n");
      else
        printf("N\n");
    }
    system("pause");
    return 0;
}

```


---

## 作者：寒鸽儿 (赞：0)

[博客食用效果更佳](https://www.luogu.org/blog/oldherd/solution-p3398)  
### 本题考察了对lca的理解，在这里提供一种新的推导思路。  
锁定一条存在的公共路径，如下图。  
![](https://i.loli.net/2019/05/17/5cdeb357eadbd36465.png)  
图1  
那么路径的起始点一定存在于该两个节点的两侧。  
我们记x = lca(a, b), y = lca(c, d)。x, y必定是路径上较高的点。由于树的节点有且仅有一个父亲，故向深度较低出回溯时仅有一条路径。假设dep[y] > dep[x] (深度)。则类似下图的情况：  
![](https://i.loli.net/2019/05/17/5cdeb359efc0081230.png)  
图2  
假设a, c在这两个点(公公路径端点)的下方。则a, c必定在路径中深度较大节点的子树上,如图：  
![](https://i.loli.net/2019/05/17/5cdeb35bb0bc586669.png)  
图3  
然后补全c, d,如图：  
![](https://i.loli.net/2019/05/17/5cdeb35e9453a62331.png)  
图4  
由图1可知y在x到公共路径的道路上,由图3可知y在a到公公路径的道路上。  
因而得出结论：  
y必定处在x到a的路径上。  
以上证明的是该结论的充分性，必要性比较简单，请自行思考。  
上述结论等价于:  
lca(x, y) == x && (lca(a, y) == y || lca(b, y) == y)， dep[x] < dep[y].  
(因为不知道a, b哪一个在我们锁定的公共路径较深节点的子树上所以a, b都要比较一下)  
附上ac代码：  
```cpp
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 100010, maxp = 30;
inline void swap(int &x, int &y) {
	int t = x; x = y; y = t;
} 

int head[maxn], ver[maxn<<1], nex[maxn<<1], tot;
inline void addedge(int u, int v) {
	ver[tot] = v; nex[tot] = head[u]; head[u] = tot++;
}

int fa[maxn][maxp], dep[maxn];
inline void dfs(int pre, int cur) {
	fa[cur][0] = pre; dep[cur] = dep[pre] + 1;
	for(int i = 1; i <= 25; i++) fa[cur][i] = fa[fa[cur][i-1]][i-1];
	for(int i = head[cur]; i != -1; i = nex[i])
		if(!dep[ver[i]])
			dfs(cur, ver[i]);
}

inline int lca(int u, int v) {
	if(dep[u] > dep[v]) swap(u, v);
	for(int i = 25; i > -1; --i) if(dep[fa[v][i]] >= dep[u]) v = fa[v][i];
	if(u == v) return v;
	for(int i = 25; i > -1; --i) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}

int main() {
	int n, q, u, v, a, b, c, d;
	scanf("%d %d", &n, &q);
	memset(head, -1, sizeof(head));
	for(int i = 1; i < n; i++) {
		scanf("%d %d", &u, &v);
		addedge(u, v);
		addedge(v, u);
	}
	dfs(0, 1);
	while(q--) {
		scanf("%d %d %d %d", &a, &b, &c, &d);
		int x = lca(a, b), y = lca(c, d);
		if(dep[x] > dep[y]) swap(x, y), swap(a, c), swap(b, d);
		if(lca(x, y) == x && (lca(a, y) == y || lca(b, y) == y)) printf("Y\n");
		else printf("N\n"); 
	}
	return 0;
} 
```
欢迎互相关注(然而在oi界蒟蒻的圈很小)。  
最后再次安利一下[蒟蒻的洛谷博客](https://www.luogu.org/blog/oldherd/)  


---

## 作者：dell20050604 (赞：0)

本题基本思路为数剖找lca 最后再根据深度来判断Yes还是No，最后建议大家用邻接表，少用邻接矩阵，废话不说了，请各位大佬欣赏我这位红名蒟蒻的题解！！上代码！！！


```cpp
#include<iostream>
#include<iomanip>
#include<algorithm>
#include<string>
#include<map>
#include<vector>
#include<stack>
#include<queue>
#include<cstring>
#include<cmath>
#include<cstdio>
using namespace std;
int n,k,i,x,y,xx,yy;
int ans[300005];
vector<int>v[300005<<1];
int a,b,c,d;
int dep[300005<<1],size[300005<<1],son[300005<<1],fat[300005<<1],top[300005<<1];
int vis[300005];
void dfs1(int x,int f)
{
    fat[x]=f;
    vis[x]=1;
    size[x]=1;
    dep[x]=dep[f]+1;
    int k;
    for(k=0;k<v[x].size();++k)
    {
        int s=v[x][k];
        if(vis[s]==0)
        {
            dfs1(s,x);
            size[x]+=size[s];	
            if(size[s]>size[son[x]]) son[x]=s;
        }	
    } 
}
void dfs2(int x,int t)
{
    top[x]=t;
    if(son[x]==0) return ;
    dfs2(son[x],t);
    int k;
    for(k=0;k<v[x].size();++k)
    {
        if(v[x][k]!=son[x]&&v[x][k]!=fat[x])
        {
            dfs2(v[x][k],v[x][k]);
        }
    }
}
int lca(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]>dep[top[y]]) x=fat[top[x]];
        else y=fat[top[y]];
    }
    if(dep[x]>dep[y]) return y;
    else return x;
}
void getdfs(int x)
{
    if(son[x]==0) return ;
    else
    {
        int k;
        for(k=0;k<v[x].size();++k)
        {
            if(v[x][k]!=fat[x])
            {
                getdfs(v[x][k]);
                ans[x]+=ans[v[x][k]];
            }	
        }	
    } 
}
int main()
{
    scanf("%d%d",&n,&k);
    for(i=1;i<=n-1;++i)
    {
        scanf("%d%d",&x,&y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(i=1;i<=k;++i)
    {
        scanf("%d%d%d%d",&a,&b,&c,&d);
        int p1,p2,p3;
        p1=max(dep[lca(a,b)],dep[lca(c,d)]);
        p2=max(dep[lca(a,c)],dep[lca(a,d)]);
        p3=max(dep[lca(b,c)],dep[lca(b,d)]);
        if(max(p2,p3)>=p1) cout<<"Y"<<endl;
        else cout<<"N"<<endl; 
    }
    return 0;
}
```

---

## 作者：Dispwnl (赞：0)

很蒟的我用的树剖。。。

先修改仓鼠走过的路径

做个标记

在查询基友走过的路径上是否有标记

开始我用bool标记路径

每次询问就memset清空。。。

然后超时了~~竟然还有40分~~

于是用int标记

每次询问++

维护区间最大值

最后看是否相等。。。

就行了

似乎比我写（chao）的lca快些

```cpp
# include<iostream>
# include<cstdio>
# include<cstring>
# include<queue>
#define mid (l+r>>1)
#define tl (k<<1)
#define tr (k<<1|1)
#define ini inline int
#define inv inline void
using namespace std;
const int MAX=1e5+1;
struct p{
    int lazy,use;
}s[MAX<<2];
struct q{
    int x,y;
}c[MAX<<1];
int n,m,num,cnt,tot;
int h[MAX],d[MAX],son[MAX],top[MAX],fa[MAX],id[MAX],siz[MAX];
ini read()
{
    int x=0;
    char ch=getchar();
    while(!isdigit(ch)) ch=getchar();
    while(isdigit(ch))
    {
        x=x*10+ch-48;
        ch=getchar();
    }
    return x;
}
inv add(int x,int y)
{
    c[++num].x=h[x];
    c[num].y=y;
    h[x]=num;
}
void dfs(int x,int f)
{
    fa[x]=f;
    d[x]=d[f]+1;
    siz[x]=1;
    for(int i=h[x];i;i=c[i].x)
      {
          int y=c[i].y;
          if(y==f) continue;
          dfs(y,x);
          siz[x]+=siz[y];
          if(siz[son[x]]<siz[y])
          son[x]=y;
      }
}
void dfs1(int x,int tp)
{
    top[x]=tp;
    id[x]=++cnt;
    if(son[x]) dfs1(son[x],tp);
    for(int i=h[x];i;i=c[i].x)
      {
          int y=c[i].y;
          if(y==fa[x]||y==son[x])
          continue;
          dfs1(y,y);
      }
}
inv pus(int k)
{
    s[k].use=max(s[tl].use,s[tr].use);
}
inv down(int k)
{
    int f=s[k].lazy;
    s[tl].lazy=s[tr].lazy=f;
    s[tl].use=s[tr].use=f;
    s[k].lazy=0;
}
void change(int l,int r,int k,int L,int R,int dis)
{
    if(l>R||r<L) return;
    if(l>=L&&r<=R)
    {
        s[k].lazy=s[k].use=dis;
        return;
    }
    if(s[k].lazy) down(k);
    change(l,mid,tl,L,R,dis);
    change(mid+1,r,tr,L,R,dis);
    pus(k);
}
inv CHANGE(int x,int y,int dis)
{
    while(top[x]!=top[y])
    {
        if(d[top[x]]<d[top[y]]) swap(x,y);
        change(1,n,1,id[top[x]],id[x],dis);
        x=fa[top[x]];
    }
    if(d[x]>d[y]) swap(x,y);
    change(1,n,1,id[x],id[y],dis);
}
int ask(int l,int r,int k,int L,int R)
{
    if(l>R||r<L) return 0;
    if(l>=L&&r<=R)
    return s[k].use;
    if(s[k].lazy) down(k);
    return max(ask(l,mid,tl,L,R),ask(mid+1,r,tr,L,R));
}
char ASK(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(d[top[x]]<d[top[y]]) swap(x,y);
        if(ask(1,n,1,id[top[x]],id[x])==tot) return 'Y';
        x=fa[top[x]];
    }
    if(d[x]>d[y]) swap(x,y);
    if(ask(1,n,1,id[x],id[y])==tot) return 'Y';
    return 'N';
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<n;i++)
      {
          int x=read(),y=read();
          add(x,y),add(y,x);
      }
    dfs(1,0);
    dfs1(1,1);
    for(int i=1;i<=m;i++)
      {
          int a1=read(),b1=read(),a2=read(),b2=read();
        CHANGE(a1,b1,++tot);
        printf("%c\n",ASK(a2,b2));
      }
    return 0;
}
```

---

## 作者：Undefined_Myth (赞：0)

```cpp
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#define rint register int
#define MAXN 100005
#define LOGN 17
using namespace std;
int n,q;
int FA[MAXN+1],Log[MAXN+1],dep[MAXN+1];
int go[MAXN+1][LOGN+1];
int lowbit(int x)
{
    return x & (-x);
}
```
namespace QXX
```cpp
{
    int tot=1,head[MAXN+1];
    struct Edge{
        int next;
        int node;
    }h[MAXN << 1];
    inline void add(int u,int v)
    {
        h[++tot].next = head[u];
        head[u] = tot;
        h[tot].node = v;
    }    
    inline void dfs(int x,int fa)//fa是x的爸爸 
    {
        for(int i = head[x]; i ;i = h[i].next)
        {
            int d = h[i].node;
            //由于存的无向边，所以连出去的点，不是他的父亲就是他的儿子 
            if(d == fa)    continue;//是爸爸 
            FA[d] = x;
            dep[d] = dep[x] + 1;//初始化FA和深度 
            dfs(d,x);
        }
    }
};
using namespace QXX;
//记 Go[i][j] 为 i 往上跳 2^j 步所到达的节点（如不存在则记为 0）
inline void Get_ST()
{
    for(int i=2;i<=n;i++)
        Log[i] = Log[i >> 1] + 1;
    //要记得初始化
    for(int i=1;i<=n;i++)
        go[i][0] = FA[i]; 
    for(int j = 1;(1 << j) < n;j++)//<=　?? 
        for(int i = 1;i <= n;i++)
            go[i][j] = go[go[i][j-1]][j-1];
//超过界限为0没有影响？？？    
}
inline int LCA(int u,int v)
{
    if(dep[u] < dep[v])
        swap(u,v);//要保证u的深度大于v——即在它的下面
    //先处理同时跳到等深线 
    /*for(int i = dep[u] - dep[v]; i ;){
        int temp = lowbit(i);//i & (-i)
            u = go[u][Log[temp]];
        i -= temp;
        //由于这里后面[k2]代表之后会将跳上他的2 ^ k2 次布，所以我们要先取他的log才能保证跳的是2^k布 
    }*/
    for(int i = dep[u] - dep[v]; i ;i -= (i & -i))
        u = go[u][Log[i & -i]];
    if(u == v)//特判，LCA就是其中的一个点
        return u;
    //注意要从大到小来枚举步数
    for(int i = Log[n]; ~i ;i --)
        if(go[u][i] != go[v][i])//跳到的点 
        {
            u = go[u][i];
            v = go[v][i];
        }
    return go[u][0];
}
```
/\*实现从一个点往上跳 t 步的快速操作：
1、每次取 t 的 lowbit，即取 2^k | t 的最大的 k，此时 t & -t = 2^k。

2、然后把 u 往上跳 2^k 步，即 u = Go[u][Log[t & -t]]，并令 t -= (t & -t)。

3、直到 t = 0 时跳步完成。

\*/
```cpp
int main()
{
    scanf("%d%d",&n,&q);
    for(int i = 1;i <= n -1 ; i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add(u,v);
        add(v,u);
    }
    dfs(1,0);//强制认为1是起点 
    Get_ST();
    for(int i=1;i<=q;i++)
    {
        int a,b,c,d;
        scanf("%d%d%d%d",&a,&b,&c,&d);
        int LCA_1 = LCA(a,b);
        int LCA_2 = LCA(c,d);
        if(dep[LCA_1] < dep[LCA_2]){
            swap(a,c);
                swap(b,d);
                    swap(LCA_1,LCA_2);//特别注意LCA也一定要进行交换！ 
        }    
        if(LCA(LCA_1,c) == LCA_1 || LCA(LCA_1,d) == LCA_1)//当且仅当x在(c,d)链上
            printf("Y\n");
        else
            printf("N\n"); 
    }
        return 0;
}
```

---

## 作者：陈国凯 (赞：0)

首先安利时间：个人博客： chenguokai.16mb.com 备用站： chenguokai.16mb.com

###**算法：倍增求LCA**

首先这题目可以看出跟LCA必然有关系，但是当时做月赛时并不知道到底怎么搞（我说今天做这道题目时怎么这么熟悉，一查记录当时月赛时做过。。。爆零了。。。）然后先不管到底有什么关系，先把LCA搞定再说（众：怎么可以这样！）然后就可以放倍增出来了（话说其实我不愿意写倍增的，但是毕竟tarjan在这道题并不怎么好使啊），首先预处理出每个节点往上跳2^k高度的节点是谁，然后即可每次以logN复杂度求出LCA了，然后就要想LCA到底和这道题有什么关系了。经过题解大神的指引（众：竟然看题解！），我发现只要某个LCA的深度大于另两个点的深度最大值，则它怎样也无法与另两个点间的道路有公共路径，而如果其中一个LCA的深度较深，就看另外的两点与它的LCA是否是它本身（如果不是则说明这两点与它无公共路径，自然更不会与初始位置有公共路径）。此外此题目数据很强，倍增时如果在两点高度不同时直接一点点地向上跳也会超时。。。因此必须也倍增往上跳。


代码：

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
int lca1,lca2,n,q,a,b,c,d,aa,bb,deep[100010],fa[100010],rmq[100010][18];
vector<int>v[100010];
bool vis[100010];
struct rec{
  int a,b,c,d;
}Q[100010];
void dfs(int src,int dep){
  vis[src]=true;
  deep[src]=dep;
  for (int i=0;i<v[src].size();++i)
    if (!vis[v[src][i]]){
      fa[v[src][i]]=src;
      dfs(v[src][i],dep+1);
    }
}
int LCA(const int a,const int b){
  int xx=a,yy=b;
  if (deep[xx]>deep[yy]){
    for (int i=17;i>=0;--i){
      if (rmq[xx][i]==0) continue;
      if (deep[rmq[xx][i]]>=deep[yy]) xx=rmq[xx][i];
      if (deep[xx]==deep[yy]) break;
    }
  }
  if (xx==yy) return yy;
  if (deep[yy]>deep[xx]){
    for (int i=17;i>=0;--i){
      if (rmq[yy][i]==0) continue;
      if (deep[rmq[yy][i]]>=deep[xx]) yy=rmq[yy][i];
      if (deep[xx]==deep[yy]) break;
    }
  }
  if (xx==yy) return xx;
  for (int i=17;i>=0;--i){
    if (rmq[xx][i]==0) continue;
    if (rmq[xx][i]!=rmq[yy][i]){
      xx=rmq[xx][i];
      yy=rmq[yy][i];
    }
  }
  return fa[xx];
}
inline int getint(){
  int i=0;
  char ch;
  for (ch=getchar();ch<'0'||ch>'9';ch=getchar());
  for (;ch>='0'&&ch<='9';ch=getchar()) i=i*10+(ch-48);
  return i;
}
int main(){
  //scanf("%d%d",&n,&q);
  n=getint(),q=getint();
  for (int i=1;i<n;++i){
    //scanf("%d%d",&aa,&bb);
    aa=getint(),bb=getint();
    v[aa].push_back(bb);
    v[bb].push_back(aa);
  }
  for (int i=1;i<=q;++i){
    Q[i].a=getint(),Q[i].b=getint(),Q[i].c=getint(),Q[i].d=getint();
    //scanf("%d%d%d%d",&Q[i].a,&Q[i].b,&Q[i].c,&Q[i].d);
  }
  memset(vis,0,sizeof(vis));
  dfs(1,1);
  for (int i=1;i<=n;++i) rmq[i][0]=fa[i];
  for (int i=1;i<=17;++i)
    for (int j=1;j<=n;++j){
      if (rmq[j][i-1]==0) continue;
      rmq[j][i]=rmq[rmq[j][i-1]][i-1];
    }
  for (int i=1;i<=q;++i){
    lca1=LCA(Q[i].a,Q[i].b);
    lca2=LCA(Q[i].c,Q[i].d);
    if (deep[lca2]>deep[Q[i].a]&&deep[lca2]>deep[Q[i].b]){
      printf("N\n");
    }else if (deep[lca1]>deep[Q[i].c]&&deep[lca2]>deep[Q[i].d]){
      printf("N\n");
    }else{
      if (deep[lca1]>deep[lca2]){
        if (LCA(Q[i].c,lca1)==lca1||LCA(Q[i].d,lca1)==lca1){
          printf("Y\n");
        }else{
          printf("N\n");
        }
      }else{
        if (LCA(Q[i].a,lca2)==lca2||LCA(Q[i].b,lca2)==lca2){
          printf("Y\n");
        }else{
          printf("N\n");
        }
      }
    }
  }
  return 0;
}
```

---

