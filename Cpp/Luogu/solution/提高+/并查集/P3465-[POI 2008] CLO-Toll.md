# [POI 2008] CLO-Toll

## 题目描述

给你 $n$ 个点和 $m$ 条双向边，问能否将其中的一些边改成有向边，使得只考虑有向边的情况下每个点的入度都为 $1$ 。

## 样例 #1

### 输入

```
4 5
1 2
2 3
1 3
3 4
1 4```

### 输出

```
TAK
3
3
4
1```

## 样例 #2

### 输入

```
4 3
1 3
3 4
2 3```

### 输出

```
NIE```

# 题解

## 作者：kkksx (赞：15)

~~搞不懂为啥要用并查集~~

思路: 

从任一点出发遍历整个联通块，把走的点和边构成一棵树，当出现返祖边（即遍历过的点再一次被遍历），就把这一点以及它所有祖先所连的有向边全部反向，当然有可能点不在同一联通块内，那么直接枚举每一个点看有没有遍历过就行了

如图（表示不会画图）

正常遍历ing![](https://cdn.luogu.com.cn/upload/pic/50956.png)

返祖![](https://cdn.luogu.com.cn/upload/pic/50958.png)

反向![](https://cdn.luogu.com.cn/upload/pic/50957.png)


这样就满足每个点都有入度了

容易知道一棵树只需要一条返祖边就可以使得整个联通块有解，之后再出现返祖边直接不管。

无解：如果没有返祖边，那么整个联通块形成树结构，这棵树的根节点没有入度，就判无解。

巨丑代码如下（感觉很多地方可以省略~~，但谁叫我懒呢233~~）
```
#include<bits/stdc++.h> 
#define N 100001
#define M 200001
#define orz
using namespace std;
int n,m;
int ans[N],father[N];
bool vis[N],fanzu,ok=1;

struct Edge
{
	int next,to;
}edge[M*2]; int head[N],cnt;
void add_edge(int from,int to)
{
	edge[++cnt].next=head[from];
	edge[cnt].to=to;
	head[from]=cnt;
}

template <class T>
void read(T &x)
{
	char c;int sign=1;
	while((c=getchar())>'9'||c<'0') if(c=='-') sign=-1; x=c-48;
	while((c=getchar())>='0'&&c<='9') x=(x<<1)+(x<<3)+c-48; x*=sign;
}

void dfs2(int rt,int son)
{
	if(ans[rt]) dfs2(ans[rt],rt);//一直跳到根
	ans[rt]=son;
}

void dfs1(int rt)
{
	vis[rt]=1;
	for(int i=head[rt];i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(v==father[rt]) continue;//回头 
		if(vis[v])//返祖 
		{
			if(!fanzu)//当前联通块未返祖，否则不管这条边 
			{
				fanzu=1;
				dfs2(v,rt);//回头更新 
			}
		}
		else//树边 
		{
			ans[v]=father[v]=rt;
			dfs1(v);
		}
	}
}

int main()
{
	read(n);read(m);
	for(int i=1;i<=m;++i)
	{
		int x,y;
		read(x);read(y);
		add_edge(x,y);
		add_edge(y,x);
	}
	for(int i=1;i<=n;++i)
	{
		if(!vis[i])//未走过 
		{
			fanzu=0;
			dfs1(i);
			if(!fanzu) {printf("NIE\n"); return 0;} 
		}
	}
	printf("TAK\n");
	for(int i=1;i<=n;++i) printf("%d\n",ans[i]);
	return orz;
}
```

---

## 作者：shame_djj (赞：11)

一遍 AC， 非常舒适，发篇题解，纪念一下

原题链接[【[POI2008]CLO-Toll】](https://www.luogu.org/problem/P3465)

本题的难点在于读题，没错，就是读题

仔细的读一下题目：

		给你 n 个点和 m 条双向边，

		问能否将其中的一些边改成有向边，

		使得只考虑有向边的情况下每个点的入度都为 1 。

只考虑有向边，只考虑有向边，只考虑有向边

~~然后本题就完了啊~~

只考虑有向边，意思就是别的边都不用考虑

也就是说只要本图存在一个子图满足每个点只有一个入度就行

解题思路：

		1、直接跑一棵生成树，或者说是生成森林

		2、枚举每一条非树边，若两点在同一生成树上，就 dfs 出这整棵树的 ans

		3、判断，并输出

嗯，就完了，真的完了 QwQ~~

说一下我完成我的思路的代码实现：

		1、跑生成树，直接用并查集，并建好只有树边的图，再给树边都打上标记

		2、非树边即为没有打标记的边，并查集判断是否在同一棵树上，树上 dfs 就不说了

		3、只要有一个点没有答案，那么就输出 “NIE”，否则就输出答案就好了

然后真的完了，上代码

```cpp
#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cmath>

using namespace std;
const int maxn = 1e5 + 10;
const int maxm = 1e6 + 10;

inline int read() {
    char c = getchar(); int x = 0, f = 1;
    for (; c > '9' || c < '0'; c = getchar()) if (c == '-') f = -1;
    for (; c >='0' && c <='9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ 48);
    return x * f;
}

struct Edge {
    int u, v; bool col;
} h[maxm];

int ver[maxm], nxt[maxm], head[maxn], tot;
int n, m, fx, fy;
int ans[maxn];

int f[maxn];
inline int find (int x) {
    return x == f[x] ? x : f[x] = find (f[x]);
}

void add (int u, int v) {
    ver[++ tot] = v, nxt[tot] = head[u], head[u] = tot;
}

void dfs (int x, int f) {
    ans[x] = f;
    for (register int i = head[x]; i; i = nxt[i])
        if (!ans[ver[i]])
            dfs (ver[i], x);
}

void djj () {
    n = read(), m = read();
    for (register int i = 1; i <= m; i ++)
        h[i].u = read(), h[i].v = read();
    for (register int i = 1; i <= n; i ++)
        f[i] = i;
    for (register int i = 1; i <= m; i ++) {
        fx = find (h[i].u), fy = find (h[i].v);
        if (fx == fy) continue ;
        add (h[i].u, h[i].v), add (h[i].v, h[i].u);
        f[fx] = fy, h[i].col = 1;
    }
}

void lxy () {
    for (register int i = 1; i <= m; i ++) {
        if (h[i].col == 1) continue ;
        if (find (h[i].u) != find (h[i].v))
            continue ;
        if (ans[h[i].u]) continue ;
        dfs (h[i].u, h[i].v);
    }
    for (register int i = 1; i <= n; i ++)
        if (!ans[i]) {
            puts ("NIE");
            exit (0);
        }
    puts ("TAK");
    for (register int i = 1; i <= n; i ++)
        printf ("%d\n", ans[i]);
    exit (0);
}

void djj_lxy () {
    djj (), lxy ();
}

int main () {
    djj_lxy ();
}

/*
4 5
1 2
2 3
1 3
3 4
1 4

TAK
3
3
4
1
*/

```
~~鬼畜的码风，打了八十行~~

注意好好读题，~~然后本题实在是没什么好说的了啊~~

离新 Noip 还有不到两个月的时间，祝大家 rp ++

也是希望自己能更努力一些，加油！

---

## 作者：theStarMaster (赞：6)

### 1.洛谷[P3465[POI2008]CLO-Toll](https://www.luogu.com.cn/problem/P3465)

题目大意：给你 $n$ 个点和 $m$ 条双向边，问能否将其中的一些边改成有向边，**使得只考虑有向边的情况下** 每个点的入度都为 $1$ 。

#### 分析：

从 $m$ 条双向边中选取一些边，选定方向后使每个点入度为 $1$。

那么问题来了，什么样的图中所有点入度都为 $1$ 呢？

答案 ~~显而易见~~ -----存在环的图（基环树）；
![](https://cdn.luogu.com.cn/upload/image_hosting/ycvem36w.png)  
如图所示：
我们发现只要存在环它就能使入度为一，因为我们只需保证入度为一出度，且我们只需选出路径即可即无需考虑多出的边，所以存在一个环时我们一定可以选出一条入度为一的有向路径。

## 代码如下

```cpp
#include<bits/stdc++.h>
using namespace std;
inline int read()
{
    int x=0,f=1;
    char ch=getchar();
    while(ch>'9' or ch<'0')
    {
        if(ch=='-') f=-1;
        ch=getchar();
    }
    while(ch>='0' and ch<='9')
    {
        x=(x<<1)+(x<<3)+(ch^48);
        ch=getchar();    
    }
    return f*x; 
}
const int MM=1e6+55;
int n,m,tot,fa[MM];
int head[MM],nxt[MM],ver[MM],ans[MM];
struct node
{
    int x;
    int y;
    bool f;
}e[MM];
inline int Find(int x)
{
    if(x==fa[x]) return x;
    else return fa[x]=Find(fa[x]);
}
inline void merge(int x,int y)
{
    int fx=Find(x),fy=Find(y);
    fa[fx]=fy;
    return ;
}
inline void add(int x,int y)
{
    ver[++tot]=y;
    nxt[tot]=head[x];
    head[x]=tot;
}//链式前向星建图 
inline void dfs(int x,int y)
{
    ans[x]=y;
    for(int i=head[x];i;i=nxt[i])
    {
        int v=ver[i];
        if(!ans[v])
        {
            dfs(v,x);
        }
    }
}//寻找路径 
inline int StarMaster()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
    {
        fa[i]=i;
    }
    for(int i=1;i<=m;i++)
    {
        e[i].x=read(),e[i].y=read();
        if(Find(e[i].x)==Find(e[i].y)) continue;
        add(e[i].x,e[i].y);add(e[i].y,e[i].x);
        merge(e[i].x,e[i].y);
        e[i].f=true;
    }
//建立初始树（无环），之后遍历剩余的边，是否能出现环 
    for(int i=1;i<=m;i++)
    {
        if(e[i].f) continue;
        if(ans[e[i].x]) continue;//如果已出现在路径里则不进行DFS 
        dfs(e[i].x,e[i].y); 
    }
//dfs即为找环的过程 
    for(int i=1;i<=n;i++)
    {
        if(!ans[i])
        {
            cout<<"NIE"<<'\n';
            return 0;
        }//但凡有一个点没有被遍历到，则说明无环即无解 
    }
    cout<<"TAK"<<'\n';
    for(int i=1;i<=n;i++)
    {
        cout<<ans[i]<<'\n';
    }
    return 0;
}

int Star_Master=StarMaster();
signed main(){;}
```

------

---

## 作者：_cnk (赞：5)

## P3465

大概是一道~~凸轮小水题~~？ 顺便纪念一下 $pecky$ ~~神犇~~ (提供的思路

---

使每一个点的入度为 $1$ （在只考虑有向边的情况下

然后 只要 有环 就成立 ... 思路这样大概就结束了

代码主要在 :

$1.$ 找环 : 可用并查集 在两点连边时 判断一下是否已经在同一集合中， 如果已经在一个集合中 再连一条边 必然构成一个环 (注意图不连通要找多个环)

```cpp
for(int i = 1;i <= m;i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v); add(v, u);
		int fx = find(u), fy = find(v);
    	//注意在这里
		if(fx == fy) s[++s[0]] = u; //#4789的点 (多个环 
    
		f[fx] = fy;
	}
```



$2.\ dfs:\ $ 对于每一个连通图， 我们只需要选取其中一个环任意一点作为起点必然能找到一条路径使每个点入度为一 (注意是双向边建图 要判一下不要连成双向边)

```cpp
void dfs(int u, int ss) {
	for(int i = head[u]; i;i = nxt[i]) {
		int v = to[i]; 
        
        //注意在这里
		if(ans[v] || ans[u] == v/*#5#6的点*/ ) continue;
        
		ans[v] = u;
		if(v == ss) continue;
		dfs(v, ss);
	}
}
```

 

$3.$ 也算一个小注意吧 ： 整张图不连通 要保证每个连通图都有环

完整代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5 + 10;
int n, m;
int nxt[maxn << 1], to[maxn << 1], head[maxn], cnt;
void add(int u, int v) {
	to[++cnt] = v;
	nxt[cnt] = head[u];
	head[u] = cnt;
}
int f[maxn], s[maxn];
int find(int x) {
	return x == f[x] ? x : find(f[x]);
}
int ans[maxn], p[maxn];
void dfs(int u, int ss) {
	for(int i = head[u]; i;i = nxt[i]) {
		int v = to[i];
		if(ans[v] || ans[u] == v/*#5#6的点*/ ) continue;
		ans[v] = u;
		if(v == ss) continue;
		dfs(v, ss);
	}
}
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1;i <= n;i++) f[i] = i;
	for(int i = 1;i <= m;i++) {
		int u, v;
		scanf("%d%d", &u, &v);
		add(u, v); add(v, u);
		int fx = find(u), fy = find(v);
		if(fx == fy) s[++s[0]] = u; //#4789的点 (多个环 
		f[fx] = fy;
	}
	if(!s) {
		printf("NIE\n");
		return 0;
	}
	for(int i = 1;i <= s[0];i++) 
		if(!ans[s[i]])
			dfs(s[i], s[i]);
    
    //注意在这里
	for(int i = 1;i <= n;i++) {
		if(ans[i] == 0) {
			printf("NIE\n"); //#2#3的点 
			return 0; 
		}
	}
    
	printf("TAK\n");
	for(int i = 1;i <= n;i++) printf("%d\n", ans[i]);
	return 0;
}
```



---

## 作者：0xFF (赞：4)

#### 题目大意


------------
给定一张有 $n$ 个点 $m$ 条边的无向图，问能否通过将其中的无向边改为有向边使得整张图上的点全部入度为 $1$，入度只计算**有向边**。

#### 思路分析


------------

注意题目中入度只计算有向边这一条件，也就是说只需要在题目中选出一些无向边改为有向边，其他剩余的直接删除即可。


![样例1](https://cdn.luogu.com.cn/upload/image_hosting/qtcf5aat.png)

上图是题目中给出的样例 $1$ 在操作前的样子。

似乎并不是很好构造。仔细阅读题干，考虑如何构造一张图满足入度为 $1$。

考虑将一张图退化为一棵树，这棵树除了根节点之外所有的边都满足题设要求，那么如何处理根节点呢？

考虑将任意一个叶子结点向根节点连一条**返祖边**，经过上述操作就可以构造出一张符合题意的图，样例 $1$ 在经过处理后即为下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/tuzrjn9w.png)

所以只需要处理出如图中 $3 → 1 → 2$ 这样的环。用并查集处理出**返祖边**，即在图上任意找出一棵生成树，再找出一条连接着树上两个顶点的边。

在树上 ```DFS``` 一遍找出所有顶点的父节点，最后输出答案即可。

#### 代码实现


------------

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<cstdlib>

using namespace std;
const int N = 2000010;

inline int read(){
    int x=0,f=1;
    char ch=getchar();
    for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
    for(; isdigit(ch);ch=getchar()) x=(x<<3)+(x<<1)+ch-'0';
    return x*f;
}

struct node{
	int nxt,to;
}edge[N<<1]; 
int cnt,head[N<<1],dis[N<<1];
void add(int x,int y){
	edge[++cnt].to = y;
	edge[cnt].nxt = head[x];
	head[x] = cnt;
}
int f[N],fa[N];
int find(int x){
	if(f[x] == x) return x;
	else return f[x] = find(f[x]);
}
void dfs(int now,int fath){
	fa[now] = fath;
	for(int i=head[now];i;i=edge[i].nxt){
		if(!fa[edge[i].to])
			dfs(edge[i].to,now);
	}
	return;
}
int x[N] , y[N];
bool vis[N];
int main(){
	int n = read() , m = read();
	for(int i=1;i<=m;i++){
		x[i] = read() , y[i] = read();
	}
	for(int i=1;i<=n;i++){
		f[i] = i;
	}
	for(int i=1;i<=m;i++){
		int fx = find(x[i]) , fy = find(y[i]);
		if(fx != fy){
			add(x[i],y[i]); add(y[i],x[i]);
			f[fy] = fx;
			vis[i] = true;
		}
	}
	for(int i=1;i<=m;i++){
		if(!vis[i] && find(x[i]) == find(y[i]) && !fa[x[i]]){
			dfs(x[i],y[i]);
		}
	}
	for(int i=1;i<=n;i++){
		if(!fa[i]){
			printf("NIE");
			return 0;
		}
	}
	printf("TAK\n");
	for(int i=1;i<=n;i++){
		printf("%lld\n",fa[i]);
	}
	return 0;
}
```


---

## 作者：A_Đark_Horcrux (赞：3)

## 并查集

观察题目发现：

> 问能否将其中的 __一些边__ 改成有向边

意味着只需要构造一个满足题意的子图即可。那什么样的图满足每个点的入度都为 1 呢？首先很容易想到一棵树：

![](https://cdn.luogu.com.cn/upload/image_hosting/14o363s6.png)

树上的每个节点都往它的父节点连有向边，除了根节点以外的节点入度都为 1。那根节点怎么办呢？再找一条指向根节点的边即可，比如这样：

![](https://cdn.luogu.com.cn/upload/image_hosting/mhakbuhq.png)

可以发现最终构成了一棵基环外向树，环上的每个节点都满足入度为 1，满足题意。由于题目使只考虑有向边的情况，剩下的边忽略 qwq

现在只需要把这个环找出来。可以 dfs 找返祖边，也可以用并查集，先任意找一棵生成树，再找一条连接着树上两个节点的边即可。

最后记录答案，以找到的边的端点为起点向下一边 dfs 一边记录即可，因为要求输出入度是由哪个点出发的边所得到的，所有答案即为父亲节点。

```cpp
#include<cstdio>
using namespace std;
const int N=2e6+10;
int read()
{
	int s=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') s=s*10+c-'0',c=getchar();
	return s;
}struct edge
{
	int nxt,to;
}a[N*2];
int t,h[N*2],dis[N*2];
void build(int x,int y) {a[++t]=edge{h[x],y},h[x]=t;}
//链式前向星基本操作


//--------------------------------------------------------- 

int f[N],fa[N];
int find(int x) {return x==f[x]?x:f[x]=find(f[x]);}//并查集找爸爸操作
void dfs(int now,int last)//dfs更新答案
{
	fa[now]=last;//答案是父亲节点
	for(int i=h[now];i;i=a[i].nxt)
		if(!fa[a[i].to]) dfs(a[i].to,now);//没更新的下去更新
	return ;
}
int n,m,i,j,x[N],y[N],tag[N];
int main()
{
	n=read(),m=read();
    for(i=1;i<=m;i++) x[i]=read(),y[i]=read();
    for(i=1;i<=n;i++) f[i]=i;//初始化
    for(i=1;i<=m;i++) 
	{
		int p=find(x[i]),q=find(y[i]);
        if(p!=q) build(x[i],y[i]),build(y[i],x[i]),f[q]=p,tag[i]=1;//不在同一棵树里，建边，改爸爸，标记树边
    }//这里就把森林建好了。
    for(i=1;i<=m;i++)
    	if(!tag[i]&&find(x[i])==find(y[i])&&!fa[x[i]])//非树边，在同一棵树内，且未更新答案
	    	dfs(x[i],y[i]);//dfs更新
    for(i=1;i<=n;i++)
        if(!fa[i]) {puts("NIE"); return 0;}//还有没更新过的，输出NIE
    puts("TAK");
    for(i=1;i<=n;i++) printf("%d\n",fa[i]);//输出答案。
    return 0;
}
```


---

## 作者：Loser_Syx (赞：2)

在思考正解之前，不妨来考虑下如何才能使每个点的入度都是 $1$，诶感觉非常熟悉啊，一看这不就是一个环（如下图）吗，当当前图形成环的时候，那么此时全图的入度一个可以是 $1$。

![](https://cdn.luogu.com.cn/upload/image_hosting/xzupq2r1.png)

那如果全图不保证一定是环的情况呢？我们思考有什么图可以满足当前所有/大部分的点都是入度为 $1$ 的，可以发现，当图是一棵树的时候，除了当前的树根都是满足条件的，那如何才能使树根也有入度为 $1$ 呢？那显然是需要一条返祖边连住树根和一个点。  
由于本题原来的就是无向边，所以树的根是可以随意决定的（暂定当前遍历到的节点为根），那么仅需一条返祖边连住深度比他小的便符合条件（此时以被连的点作为树根），便可符合要求，如果不存在如上的返祖边则无法实现。  
那么本题样例一按照作者的方法就可以变成：

![](https://cdn.luogu.com.cn/upload/image_hosting/timackm9.png)

注意可能存在多个联通块的情况，所以需要判定多次。

```cpp
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
typedef pair<int, int> pii;
const int N = 2e5 + 19;
int head[N], nxt[N << 1], edge[N << 1], idx, start, depth[N], ans[N];
bool vis[N];
void insert(int x, int y) {
	edge[++idx] = y;
	nxt[idx] = head[x];
	head[x] = idx;
}
void dfs(int u, int fa, int deep) {
	if (depth[u] < deep) {
		if (start == 0) {
			start = u;
			ans[u] = fa;
		}
		return ;
	}
	depth[u] = deep;
	for (int i = head[u]; i; i = nxt[i]) {
		if (edge[i] != fa) dfs(edge[i], u, deep + 1);
	}
}
bool pd(int n) {
	for (int i = 1; i <= n; ++i) {
		if (depth[i] == 0x3f3f3f3f) return 1;
	}
	return 0;
}
int main() {
	memset(depth, 0x3f, sizeof depth);
	int n, m;
	scanf("%d%d", &n, &m);
	while (m--) {
		int x, y;
		scanf("%d%d", &x, &y);
		insert(x, y);
		insert(y, x);
	}
	for (int i = 1; i <= n; ++i) {
		if (ans[i] == 0) {
			start = 0;
			dfs(i, -1, 1);
			if (start == 0) {
				return puts("NIE"), 0;
			}
			queue<pii> q;
			q.push({start, ans[start]});
			vis[start] = 1;
			while (!q.empty()) {
				pii f = q.front();
				q.pop();
				int u = f.first;
				int fa = f.second;
				ans[u] = fa;
				for (int i = head[u]; i; i = nxt[i]) {
					if (vis[edge[i]] == 0 && !(start == u && edge[i] == ans[u])) {
						vis[edge[i]] = 1;
						q.push({edge[i], u});
					}
				}
			}
		}
	}
	if (pd(n)) puts("NIE");
	else {
		puts("TAK");
		for (int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
	}
	return 0;
}
```

---

## 作者：kczno1 (赞：2)

要求每个点一个入度，则形成环套树。


求出联通块的任意一个生成树，只要还有环就好了。(看一下是否存在返祖边就好了)

```cpp
#include<bits/stdc++.h>
using namespace std;

#define rep(i,l,r) for(int i=l;i<=r;++i)
#define gc (c=getchar())
int read()
{
    char c;
    while(gc<'0');
    int x=c-'0';
    while(gc>='0')x=x*10+c-'0';
    return x;
}
const int N=1e5+5,M=2e5+5;
int t[N];
struct edge
{
    int to,next;
};
edge l[M*2];int e;
//int du[N],q[N];
int fa[N],ansfa[N];//bool vis[N]; 

bool in[N];
int havey,havex;
namespace DFS
{
int *fa;
void dfs(int x)
{
    in[x]=1;
    for(int i=t[x];i;i=l[i].next)
    {
        int y=l[i].to;
        if(!fa[y]){fa[y]=x;dfs(y);}
        else
        if(!in[y]){havey=y;havex=x;}
    }
    in[x]=0;
}
};
#define dfs(x,f) {DFS::fa=f;DFS::dfs(x);}

int main()
{
    //freopen("1.in","r",stdin);freopen("1.out","w",stdout);
    int n=read(),m=read();
    while(m--)
    {
        int x=read(),y=read();
        l[++e]=(edge){y,t[x]};t[x]=e;
        l[++e]=(edge){x,t[y]};t[y]=e;
    //    ++du[x];++du[y];
    }
    rep(x,1,n)
    if(!fa[x])
    {
        havex=0;
        fa[x]=-1;
        dfs(x,fa);
        if(!havex)
        {
            puts("NIE");
            exit(0);
        }
        
        for(int i=havey;i!=havex;i=fa[i])ansfa[i]=fa[i];
        ansfa[havex]=havey; 
        for(int i=havey;i!=-1;i=fa[i])
            dfs(i,ansfa);
    }
    puts("TAK");
    rep(x,1,n)printf("%d\n",ansfa[x]);
}
```

---

## 作者：Heart_Of_Iron_4 (赞：1)

搞不懂为啥都用的基环树qwq  
这题和P1640很相似。既然不算无向边，把边看成点，跑一遍二分图匹配，确保每个点都匹配上就行了。  
（话说为啥我搜并查集的题目出来的都是二分图匹配啊）  
代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
namespace IO{
	char ibuf[(1<<20)+1],*iS,*iT;
#if ONLINE_JUDGE
#define gh() (iS==iT?iT=(iS=ibuf)+fread(ibuf,1,(1<<20)+1,stdin),(iS==iT?EOF:*iS++):*iS++)
#else
#define gh() getchar()
#endif
	inline long long read(){
		char ch=gh();
		long long x=0;
		bool t=0;
		while(ch<'0'||ch>'9')   t|=ch=='-',ch=gh();
		while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=gh();
		return t?-x:x;
	}
}
using namespace IO;
int n,m,tag[314514],p[314514],t1,t2,e[314514][2],mc[314514];
vector<int> g[314514];
inline bool xyl(int x,int y)
{
	if(tag[x]==y)return 0;
	tag[x]=y;
	for(auto i:g[x])
	{
		if((p[i]==0)||(xyl(p[i],y)))
		{
			p[i]=x;
			mc[i]=x;
			mc[x]=i;
			return 1;
		}
	}
	return 0;
}
signed main()
{
	n=read();m=read();
	//dot:t->t edge:t->t+n
	for(int i=1;i<=m;++i)
	{
		t1=read();
		t2=read();
		g[t1].push_back(i+n);
		g[t2].push_back(i+n);
		g[i+n].push_back(t1);
		g[i+n].push_back(t2);
		e[i][0]=t1;
		e[i][1]=t2;
	}
	for(int i=1;i<=n;++i)
	{
		if(xyl(i,i)==0)
		{
			printf("NIE\n");
			exit(0);
		}
	}
	printf("TAK\n");
	for(int i=1;i<=n;++i)
	{
		if(e[mc[i]-n][0]==i)printf("%lld\n",e[mc[i]-n][1]);
		else printf("%lld\n",e[mc[i]-n][0]);
	}
	return 0;
}
```

---

## 作者：TernaryTree (赞：1)

## 题目大意

给定一个有 $n$ 个点和 $m$ 条双向边的有向图，问能否将其中的一些边改成有向边，使得只考虑有向边的情况下每个点的入度都为 $1$。

## 思路分析

因为只考虑有向边，所以另外的什么都不需要特别考虑。

那么这题就很简单了：

首先在原图上生成一棵树，原图有可能不联通，所以可能有好几棵树。此步使用 `Kruskal`。

然后对每一条不在生成树上且两端在同一个生成树上的边枚举遍历，并标记答案。

最后扫一遍答案，如果有没有被标记到的就是 `NIE`，否则输出 `TAK` 并且输出答案。

## 完整答案

```cpp
#include <bits/stdc++.h>
#define int long long
#define debug fout << "Debug: " << __LINE__ << endl;

using namespace std;

namespace FastIO
{
    struct instream
    {
        int base = 10;

        friend instream &operator>>(instream &in, int &num)
        {
            int flag = 1;
            int ans = 0;
            char ch = getchar();
            while (ch < '0' || ch > '9')
            {
                if (ch == '-')
                {
                    flag = -flag;
                }
                ch = getchar();
            }

            while (ch >= '0' && ch <= '9')
            {
                ans = ans * in.base + (ch - '0');
                ch = getchar();
            }
            num = ans * flag;
            return in;
        }
    };

    struct outstream
    {
        template<typename _CharT, typename _Traits = char_traits<_CharT>>
        struct typ {
            typedef basic_ostream<_CharT, _Traits>& (* end) (basic_ostream<_CharT, _Traits>&);
        };

        int base = 10;

        friend outstream &operator<<(outstream &out, int num)
        {
            if (num < 0)
            {
                putchar('-');
                num = -num;
            }
            if (num >= 10)
            {
                out << num / 10;
            }
            putchar(num % 10 + '0');
            return out;
        }

        friend outstream &operator<<(outstream &out, const char * s) {
            printf("%s", s);
            return out;
        }

        friend outstream &operator<<(outstream &out, string s) {
            cout << s;
            return out;
        }

        friend outstream &operator<<(outstream &out, typ<char>::end e) {
            puts("");
            return out;
        }
    };

    instream fin;
    outstream fout;
}

using namespace FastIO;

const int maxn = 2e5 + 1;
const int maxm = 7e5 + 1;
const int maxd = 50;

struct edge {
    int from, to, next;
};

struct tree {
    int n, cnt;
    int head[maxn];
    edge e[maxm];
    int ans[maxn];
    
    void add_edge(int u, int v) {
        e[++cnt] = (edge) {u, v, head[u]};
        head[u] = cnt;
    }
    
    void dfs(int u, int fa) {
    	ans[u] = fa;
    	for (int i = head[u]; i; i = e[i].next) {
    		int v = e[i].to;
    		if (!ans[v]) {
    			dfs(v, u);
			}
		}
	}
};

struct dsu {
    int fa[maxn];

    void init(int n) {
        for (int i = 1; i <= n; i++) {
            fa[i] = i;
        }
    }
    
    int find(int x) {
        if (fa[x] == x) {
            return x;
        }
        return fa[x] = find(fa[x]);
    }
};

tree tr;

struct graph {
    int n, m, cnt;
    int head[maxn];
    edge e[maxm];
    bool intree[maxm];
    dsu d;

    void add_edge(int u, int v) {
        e[++cnt] = (edge) {u, v, head[u]};
        head[u] = cnt;
    }

    void init() {
        fin >> n >> m;
        for (int i = 1; i <= m; i++) {
        	int u, v;
            fin >> u >> v;
            add_edge(u, v);
        }
    }
    
    void tree() {
        d = dsu();
        d.init(n);
        tr.n = n;
        for (int i = 1; i <= cnt; i++) {
        	int u = d.find(e[i].from);
            int v = d.find(e[i].to);
            if (u != v) {
                d.fa[u] = v;
                intree[i] = true;
                tr.add_edge(e[i].from, e[i].to);
                tr.add_edge(e[i].to, e[i].from);
            }
		}
	}
    
    bool judge() {
    	for (int i = 1; i <= cnt; i++) {
    		int u = e[i].from;
    		int v = e[i].to;
    		if (!intree[i] && d.find(u) == d.find(v) && !tr.ans[u]) {
    			tr.dfs(u, v);
			}
		}
		for (int i = 1; i <= n; i++) {
			if (!tr.ans[i]) return false;
		}
		return true;
	}
};

graph g;

signed main() {
    g.init();
    g.tree();
    bool flg = g.judge();
    if (flg) {
    	fout << "TAK" << endl;
    	for (int i = 1; i <= tr.n; i++) {
    		fout << tr.ans[i] << endl;
		}
	} else {
		fout << "NIE" << endl;
	}
    
    return 0;
}
```

---

## 作者：fls233666 (赞：1)

首先我们知道 $n$ 个点肯定需要 $n$ 条不同的边才能让在把边定向后做到每个点的入度为 $1$。问题在于怎么选这 $n$ 条边。

在考虑这种情况前，我们先考虑图退化树的情况。

假设有这样一个 $5$ 个点的树：

![Pic1](https://cdn.luogu.com.cn/upload/image_hosting/uiwuit9c.png)

我们观察后发现，无论我们以哪一个节点为根，把边定向为从父亲节点指向子节点，**最后只有根的入度是 $0$**。

那我们就需要再搞一条边出来，把这条边指向根，使根的入度为 $1$。

![Pic2](https://cdn.luogu.com.cn/upload/image_hosting/95r1wv7r.png)

进一步考虑，我们发现添加的这一条边所连接的两个点都必须在同一棵树上。如果不在同一棵树上，**那么这条边一定可以作为一个树边把把两个联通块连起来构成一个更大的树**。于是我们得出一个简要的思路：求生成树，然后找一条连接的两个点都在同一个生成树上的边，把这条边连接的两个点其中一个当作根，遍历整个树给边定向，计算答案。

于是我们推广到图上。首先我们注意到，**整张图可能不连通**！那么我们考虑使用 **并查集** 维护联通性，考虑对所有的边扫描两次。

先用 $O(m)$ 的时间扫一遍全部的边，如果边所连接的两个点不联通，就连接这条边，**并标记这条边**。能连的边全连完后，整个图会成一个“森林”的状态。我们记这个森林中有 $cnt$ 棵树。

这时我们再用 $O(m)$ 的时间扫一遍全部的边，给“森林”中的每个树找到它需要的指向根的那条边。具体地，就是给每个树找 **一条没有被打标记的边**，让这条边指向根，并从这个根开始遍历整个树计算每个节点的答案。如果此时找不到 $cnt$ 条边能对应森林中的 $cnt$ 棵树，无解。

于是这题就做完了。把上文思路转化成代码实现，得到以下代码：

```cpp
#include<iostream>
#include<cstdio>
#define ll long long
#define rgt register int
using namespace std;

const int mxn = 2e5+5;

int fa[mxn],ans[mxn];
int ai[mxn],bi[mxn];
bool ci[mxn],get_rt[mxn];
int n,m,tot,rt,cnt;
int lst[mxn],to[mxn<<1],nxt[mxn<<1];

int fd(int x){
    return x==fa[x]?x:fa[x]=fd(fa[x]);
}

inline void add(int u,int v){
    tot++;
    to[tot]=v;
    nxt[tot]=lst[u];
    lst[u]=tot;
}

inline int rd(){
    int x=0;
    bool ntv=false;
    char c=getchar();
    while(c!='-'&&(c<'0'||c>'9'))
        c=getchar();
    if(c=='-')
        ntv=true;
    else
        x=(c^48);
    c=getchar();
    while(c>='0'&&c<='9'){
        x=x*10+(c^48);
        c=getchar();
    }
    return  ntv?-x:x;
}

inline void print(int d){
    if(d==0){
        putchar('0');
        return;
    }
    if(d<0){
        putchar('-');
        d=-d;
    }
    int num=d,siz=0,buf[22];
    while(num){
        siz++;
        buf[siz]=num%10;
        num/=10;
    }
    while(siz){
        putchar('0'+buf[siz]);
        siz--;
    }
}

void dfs(int pt,int ptfa){
    for(rgt i=lst[pt];i;i=nxt[i]){
        if(to[i]!=ptfa){
            ans[to[i]]=pt;
            dfs(to[i],pt);
        }
    }
}  //遍历整个树计算答案

int main(){
    n=rd();
    m=rd();
    for(rgt i=1;i<=n;i++)
        fa[i]=i;
    cnt=n;  //一开始 n 个点是独立的，即有 n 个联通块
    
    for(rgt fai,fbi,i=1;i<=m;i++){  //第一轮扫描边
        ai[i]=rd();
        bi[i]=rd();
        fai=fd(ai[i]);
        fbi=fd(bi[i]);
        if(fai!=fbi){  //找到一条边能连
            cnt--;  //少一个联通块
            ci[i]=true;  //标记
            fa[fai]=fbi;  //连边
            add(ai[i],bi[i]);
            add(bi[i],ai[i]);
        }
    }  //此时 cnt 就是剩下的联通块个数，即为森林中树的个数
    
    for(rgt fai,fbi,i=1;i<=m;i++){  //第二轮扫描边，找 cnt 条边指向根
        if(!ci[i]){
            fai=fd(ai[i]);
            if(!get_rt[fai]){
                cnt--;
                get_rt[fai]=true;
                ans[ai[i]]=bi[i];
                dfs(ai[i],0);
            }  //找到一个没有边指向根的树，统计答案
        }
    }
    
    if(cnt){  //没有找齐 cnt 条边，无解
        putchar('N');
        putchar('I');
        putchar('E');
        return 0;
    }
    
    putchar('T');
    putchar('A');
    putchar('K');
    putchar('\n');
    for(rgt i=1;i<=n;i++){
        print(ans[i]);
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：1234567890sjx (赞：0)

首先对于一张图 $G$，求出其所有的连通块 $g_1,g_2,g_3,\ldots,g_k$。

如果 $\forall i\in [1,k]$ 有 $g_i$ 存在至少一个环，那么很显然可以以这个环造一个有向基环树，容易发现若基环树中环上的边方向一致并且基环树是一棵外向的基环树，那么所有点的度数必然都为 $1$。

那么结论就得到了：如果图 $G$ 的所有连通块 $g_1,g_2,g_3,\ldots g_k$ 都存在至少一个环，那么必然有解，否则必然无解。

------

那么问题就变成了怎么判断一个图 $G$ 的连通子图 $g$ 中存在一个环。

有三种方法判断一个**连通的**图 $g$ 是否存在环：

+ 拓扑排序。
+ Tarjan 强连通分量。
+ 并查集。

其中前两种的时间复杂度是 $O(n)$ 的，最后一种的时间复杂度是 $O(\alpha n)$ 的但是十分甚至是一百分的好写。

这里介绍并查集的写法：对于连通子图 $g$ 中任意的一条边 $u\to v$，如果 $u$ 和 $v$ 在并查集的祖先节点相同那么必然存在一个经过 $u\to v$ 的环，否则合并 $u$ 和 $v$ 节点。

------

但是题目还要求输出任意一种方案。

按照第一部分的算法直接搜一遍。

> 如果 $\forall i\in [1,k]$ 有 $g_i$ 存在至少一个环，那么很显然可以以这个环造一个有向基环树，容易发现若基环树中环上的边方向一致并且基环树是一棵外向的基环树，那么所有点的度数必然都为 $1$。

对于这个连通子图 $g$，找到 $g$ 中任意的一个环并把环上所有的边按照顺序往相同的方向建一条新的有向边。剩下的点从环上再搜一遍，往外连有向边即可。

这部分的时间复杂度是 $O(n)$ 的。

---

## 作者：FutaRimeWoawaSete (赞：0)

考虑对于任意一个连通块判定什么是否存在答案，发现如果一个连通块存在至少一个环时连通块内有解。            

证明：考虑任意一个连通块的生成树，我们随机令其中一个点为根那么将父亲向儿子连有向边，现在只有根节点没有入度了。           

如果其中有一个环，我们考虑先把一条边去掉，选这个边连接的两个点中一个点作为根后 dfs 全树，最后把另一个点指向根即可构造。             

```cpp
#include "bits/stdc++.h"
using namespace std;
const int Len = 2e5 + 5;
int n,m,fa[Len],siz[Len],head[Len],cnt,From[Len],To[Len],f[Len];
void makeSet(int x){for(int i = 1 ; i <= x ; i ++) fa[i] = i , siz[i] = 0;}
int findSet(int x){return fa[x] == x ? fa[x] : fa[x] = findSet(fa[x]);}
struct Node
{
	int x,y;
}line[Len << 2];
struct node
{
	int next,to;
}edge[Len << 1];
void add(int from,int to)
{
	edge[++ cnt].to = to;
	edge[cnt].next = head[from];
	head[from] = cnt;
}
bool vis[Len];
void unionSet(int x,int y)
{
	int u = findSet(x) , v = findSet(y);
	if(u == v)
	{
		siz[u] ++;
		if(siz[u] == 1) From[u] = x , To[u] = y;
		return;
	}
	fa[v] = u;
	add(x , y) , add(y , x);
	siz[u] += siz[v];
	if(From[v]) From[u] = From[v] , To[u] = To[v];	 
}
void dfs(int x,int ff)
{
	f[x] = ff;
	for(int e = head[x] ; e ; e = edge[e].next)
	{
		int to = edge[e].to;
		if(to == ff) continue;
		dfs(to , x);
	}
}
int main()
{
	scanf("%d %d",&n,&m);
	makeSet(n);
	for(int i = 1 ; i <= m ; i ++)
	{
		int x,y;scanf("%d %d",&x,&y);
		unionSet(x , y);
	}
	for(int i = 1 ; i <= n ; i ++)
	{
		int x = findSet(i);
		if(!vis[x])
		{
			if(!siz[x]) return puts("NIE") & 0;
			vis[x] |= 1;
			int u = From[x];
			dfs(u , 0);
			f[u] = To[x];
		}
	}
	puts("TAK");
	for(int i = 1 ; i <= n ; i ++) printf("%d\n",f[i]);
	return 0;
}
```

---

## 作者：AuCloud (赞：0)

# 题意
给你一张图，让你求出一个由它生成的基环树森林

# 解法
明确题意之后做法就十分明显了：

对图的每个连通块求一个生成树，然后枚举每条边，不在生成树上的话就将这条边的一个端点设置成当前生成树的根，另一端点就是这个根的入度来源

最后对于每棵树跑一边dfs遍历，让每个节点的入度来源=它的父亲即可

注意图不保证联通，要判断是否有不能形成基环树的连通块

具体方法就是记录连通块个数，每次确定一个根时将连通块个数--，最后判断是否有剩余即可

# 代码

因为是cin所以跑得好慢/youl

建议加快读
```cpp
#include <bits/stdc++.h>
using namespace std;
int head[100001], nxt[200001], to[200001], tot, fa[100001], fat[100001], rt[100001], rrt[100001], frr[100001];
struct hehe{
	int x, y;
}e[200001];
bool used[200001];
int qwq[100001];
void add(int x, int y)
{
	nxt[++tot] = head[x];
	head[x] = tot;
	to[tot] = y;
}
int find(int x)
{
	if(fa[x] == x) return x;
	return fa[x] = find(fa[x]);
}
void dfs(int x, int from)
{
	// cout << x << endl;
	fat[x] = from;
	for(int i = head[x]; i; i = nxt[i])
	{
		int y = to[i];
		if(y == from) continue;
		dfs(y, x);
	}
}
int main()
{
	int n, m;
	cin >> n >> m;
	int cnt = n;
	for(int i = 1; i <= n; i++) fa[i] = i;
	if(m == n - 1)
	{
		cout << "NIE";
		return 0;
	}
	for(int i = 1; i <= m; i++)
	{
		int x, y;
		cin >> x >> y;
		e[i].x = x, e[i].y = y;
		int fx = find(x), fy = find(y);
		if(fx != fy) fa[fx] = fy, used[i] = 1, add(x, y), add(y, x), cnt--;
	}
	for(int i = 1; i <= m; i++)
	{
		int fx = find(e[i].x), fy = find(e[i].y);
		if(!used[i] && !rt[fx])
		{
			rt[fx] = e[i].x;
			frr[e[i].x] = e[i].y;
			qwq[e[i].x] = fx;
			cnt--;
		}
	}
	if(cnt)
	{
		cout << "NIE" << endl;
		return 0;
	}
	for(int i = 1; i <= n; i++)
	{
		if(qwq[i])
		{
			if(!rt[qwq[i]])
			{
				cout << "NIE";
				return 0;
			}
			dfs(i, 0);
		}
	}
	cout << "TAK\n";
	for(int i = 1; i <= n; i++)
	{
		if(!fat[i]) cout << frr[i] << endl;
		else cout << fat[i] << endl;
	}
	return 0;
}

```

---

## 作者：傅思维666 (赞：0)

## 题解：

其实很简单的。就是在每个连通块里拎出来基环树。

如果拎不出连通块，那就是NIE。

然后考虑怎么拎基环树。

基环树是啥啊，就是一棵树加上任意一条边呗。这条边就是“返祖边”啊。所以我们只需要对每个连通块DFS一遍，只拎一条返祖边（这个用flag维护），碰到返祖边，就说明可以和一些节点构成一个环，这样的话就回溯，把所有沿途节点全部反向即可。

代码：

```cpp
#include<cstdio>
using namespace std;
const int maxn=1e5+5;
const int maxm=2e5+5;
int n,m;
int tot,head[maxn],nxt[maxm<<1],to[maxm<<1];
int fa[maxn],ans[maxn];
bool v[maxn];
bool flag;
void add(int x,int y)
{
	to[++tot]=y;
	nxt[tot]=head[x];
	head[x]=tot;
}
void dfsback(int x,int s)
{
	if(ans[x])
		dfsback(ans[x],x);
	ans[x]=s;
}
void dfs(int x)
{
	v[x]=1;
	for(int i=head[x];i;i=nxt[i])
	{
		int y=to[i];
		if(y==fa[x])
			continue;
		if(v[y])
		{
			if(!flag)
			{
				flag=1;
				dfsback(y,x);
			}
		}
		else
		{
			ans[y]=fa[y]=x;
			dfs(y);
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	for(int i=1;i<=n;i++)
		if(!v[i])
		{
			flag=0;
			dfs(i);
			if(!flag)
			{
				puts("NIE");
				return 0;
			}
		}
	puts("TAK");
	for(int i=1;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
```



---

