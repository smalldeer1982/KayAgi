# [USACO09JAN] Safe Travel G

## 题目描述

Gremlins have infested the farm. These nasty, ugly fairy-like

creatures thwart the cows as each one walks from the barn (conveniently located at pasture\_1) to the other fields, with cow\_i traveling to from pasture\_1 to pasture\_i. Each gremlin is personalized and knows the quickest path that cow\_i normally takes to pasture\_i. Gremlin\_i waits for cow\_i in the middle of the final cowpath of the quickest route to pasture\_i, hoping to harass cow\_i.

Each of the cows, of course, wishes not to be harassed and thus chooses an at least slightly  different route from pasture\_1 (the barn) to pasture\_i.

Compute the best time to traverse each of these new not-quite-quickest routes that enable each cow\_i that avoid gremlin\_i who is located on the final cowpath of the quickest route from pasture\_1 to

pasture\_i.

As usual, the M (2 <= M <= 200,000) cowpaths conveniently numbered 1..M are bidirectional and enable travel to all N (3 <= N <= 100,000) pastures conveniently numbered 1..N. Cowpath i connects pastures a\_i (1 <= a\_i <= N) and b\_i (1 <= b\_i <= N) and requires t\_i (1 <= t\_i <= 1,000) time to traverse. No two cowpaths connect the same two pastures, and no path connects a pasture to itself (a\_i != b\_i). Best of all, the shortest path regularly taken by cow\_i from pasture\_1 to pasture\_i is unique in all the test data supplied to your program.

By way of example, consider these pastures, cowpaths, and [times]:

```cpp
1--[2]--2-------+ 
|       |       | 
[2]     [1]     [3] 
|       |       | 
+-------3--[4]--4
```
``` 
TRAVEL     BEST ROUTE   BEST TIME   LAST PATH 
p_1 to p_2       1->2          2         1->2 
p_1 to p_3       1->3          2         1->3 
p_1 to p_4      1->2->4        5         2->4 
```
When gremlins are present:

```cpp
TRAVEL     BEST ROUTE   BEST TIME    AVOID 
p_1 to p_2     1->3->2         3         1->2 
p_1 to p_3     1->2->3         3         1->3 
p_1 to p_4     1->3->4         6         2->4 
```
For 20% of the test data, N <= 200. 

For 50% of the test data, N <= 3000. 

TIME LIMIT: 3 Seconds

MEMORY LIMIT: 64 MB

## 样例 #1

### 输入

```
4 5 
1 2 2 
1 3 2 
3 4 4 
3 2 1 
2 4 3 
```

### 输出

```
3 
3 
6 
```

# 题解

## 作者：BriMon (赞：17)

我开始做的时候还是蓝牌， 做一半就变紫了？玄学~

[戳这里](https://www.cnblogs.com/zZh-Brim/p/9069469.html)食用效果更佳；

欢迎互关；


题意：
给你一些点， 他们与节点1的最短路的最后一条边不可走， 求每一个点到1的最短距离；

这道题很折磨人...

首先我们考虑一颗最短路径树（就是1到每个节点的最短路径路过的边构成的集合）；

然后我们要找一个点对(x, y),且xy之间有边，xy不在最短路径树上,y在节点i的子树里,x不在节点i的子树里；

这样，我们要找的节点i的"非最短路径"，就是dis(x) + dis(y) - dis(i) + w(x, y)；
其中， dis代表节点到根节点的最短路径， w(x, y)代表x 到 y 的路径长度；

我们发现 : dis(i) 是确定的, 所以我们要最小化dis(x） + dis(y) + w(x, y);

我们可以用左偏树维护（才不会写） 想学戳这里

我直接排序；

选出不在最短路径树上的边， 按dis(x） + dis(y) + w(x, y)最小sort一遍；

然后更新答案；

我们接着想 : 一个点如果已经被更新， 那么一定是最优的， 为什么， 因为他的dis值确定， 而我们已经对以上那一坨式子的值按由小到大排序，所以我们第一次更新一定是他的最优值；

所以我们可以用并查集维护， 确保他们只被更新一次；

那么我们再想 ： 一个点对(x, y)，能更新那些点的ans呢? 

能更新到x -> LCA(x, y) 和 y -> LCA(x, Y) 的所有点；
为什么？ 

因为 边 x-y 一定不是点i的父亲边 (题面说了)， 如果我们更新到LCA(x, y) 那么x, y就在同一个子树里了；

而我们能更新i的前提是x, y不在同一子树里；

所以我们就像跳LCA一样一直往上跳， 一路更新答案， 然后修改并查集， 直到调到LCA;

应该比较好懂；

代码奉上：

```cpp
//By zZhBr
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <queue>
using namespace std;
const int N = 100010;
const int M = 400010;

inline int read()
{
    int res = 0;
    bool flag = 0;
    char c = getchar();
    while (c < '0' or c > '9')
    {
        if (c == '-') flag = 1;
        c = getchar();
    }
    while (c >= '0' and c <= '9')
    {
        res = res * 10 + c - '0';
        c = getchar();
    }
    return flag ? -res : res;
}


int n, m;
int A[M], B[M], C[M];
int what[M];//第几条边属于的编号 what[i] = what[i^1];
int is[M]; //记录最短路径中第i个点的入边 
bool itis[M];//记录是否是最短路径树的树边 
int fafa[N];//记录在最短路径树中一个节点的父亲
int fa[N];//并查集
int ans[N];//记录答案 

inline int Find(int x) 
{
    return x == fa[x] ? x : fa[x] = Find(fa[x]);
}

struct edge
{
    int nxt;
    int to;
    int val;
}ed[M];

int head[N], cnt;

inline void add(int x, int y, int z, int gg)
{
    cnt++;
    ed[cnt].nxt = head[x];
    ed[cnt].to = y;
    ed[cnt].val = z;
    head[x] = cnt;
    what[cnt] = gg;
}

inline void add(int x, int y)
{
    cnt++;
    ed[cnt].nxt = head[x];
    ed[cnt].to = y;
    head[x] = cnt;
}

struct date
{
    int x;
    int y;
    int w;
//    date(){}
//    date(int xx, int yy, int ww){x = xx, y = yy, w = ww;}
}cf[M];

bool cmp(date a, date b)
{
    return a.w < b.w;
}

void dfs(int x) //简陋的寻找父亲的函数 
{
    for (register int i = head[x] ;i ; i = ed[i].nxt)
    {
        int to = ed[i].to;
        if (to == fafa[x]) continue;
        fafa[to] = x;
        dfs(to);
    }
}

/*.............................Dijkstra...................................*/
struct dij{int x, w;};

bool operator <(const dij &a,const dij &b)
{
    return a.w > b.w;
}

int dis[N];
bool vis[N];

inline void Dijkstra(int haha)
{
    memset(dis, 0x3f, sizeof dis);
    
    priority_queue < dij > q;
    
    dis[haha] = 0;
    q.push((dij){haha, 0});
    
    while (!q.empty())
    {
        dij t = q.top(); q.pop();
        int x = t.x;
        if (vis[x]) continue;
        vis[x] = 1;
        for (register int i = head[x] ; i ; i = ed[i].nxt)
        {
            int to = ed[i].to;
            if (!vis[to] and dis[to] > dis[x] + ed[i].val) //!
            {
                is[to] = what[i];
                dis[to] = dis[x] + ed[i].val;
                q.push((dij){to, dis[to]});
            }
        }
    }
}
/*.................................End..............................................*/


int main()
{    
    n = read(), m = read();
    
    for (register int i = 1 ; i <= m ; i ++)
    {
        A[i] = read(), B[i] = read(), C[i] = read();
        add(A[i], B[i], C[i], i);
        add(B[i], A[i], C[i], i);
    }
    
    Dijkstra(1);
    
    
    cnt = 0;
    memset(head, 0, sizeof head);
    
//    for (int i=2;i<=n;i++)cout<<is[i]<<endl;
    
    for (register int i = 2 ; i <= n ; i ++)
    {
        int x = is[i];
        add(A[x], B[x]);
        add(B[x], A[x]);
        itis[x] = 1;
    }
    
    dfs(1);
    
    int num = 0;
    for (register int i = 1 ; i <= m ; i ++) //该搞非树边了 
    {
        if (itis[i]) continue;
    //    printf("%d\n", i);
        cf[++num] = (date) {A[i], B[i], dis[A[i]] + dis[B[i]] + C[i]};
    }
    
    sort (cf + 1, cf + 1 + num, cmp);
    
    for (register int i = 1 ; i <= n ; i ++) fa[i] = i, ans[i] = -1;
    
    for (register int i = 1 ; i <= num ; i ++)
    {
        int x = cf[i].x, y = cf[i].y;
        x = Find(x), y = Find(y);
        
        //printf("x = %d, y = %d\n", x, y);
        while (x != y)
        {
            if (dis[x] < dis[y]) swap(x, y);
            ans[x] = cf[i].w - dis[x];
            fa[x] = fafa[x];
            x = Find(x);
        }
        
    }
    
    for (register int i = 2 ; i <= n ; i ++)
    {
        printf("%d\n", ans[i]);
    }
    return 0;
    
}

zZhBr
```

---

## 作者：juruo999 (赞：14)

# P2934 [USACO09JAN] Safe Travel G

[更好体验](https://juruo999.blog.luogu.org/solution-p2934)  
[题目](https://www.luogu.com.cn/problem/P2934)

考点：最短路树 & 并查集缩点
 
## 正式开始讲解

题意：求在不经过原来 $1$ 节点到 $i$ 节点最短路上最后一条边的前提下，$1$ 节点到 $i$ 节点的最短路。

样例的图画出来是这样：

![图片](https://s3.bmp.ovh/imgs/2022/01/75683b3a05cb0d40.png)
 
既然最短路唯一，我们可以记录 $1$ 节点到每个节点的最短路的最后一条边的起点，也就是最后一个松弛它的节点，作为它的父亲，构造出一棵根为 $1$ 号节点的**最短路树**。因为最短路唯一，最短路树也是唯一的。

由样例构造出的最短路树是这样的：

![图片](https://i.bmp.ovh/imgs/2022/01/7f6d0881b9d89ae6.png)

红色边为最短路树上的边，黑色边不属于最短路树，我们将不属于最短路树的边称为**非树边**。为了方便，我们把树边标记为红色，非树边为黑色。

题目求的路径，也就是在不经过最短路树上 $i$ 节点到它父亲的边的前提下，$1$ 节点到 $i$ 节点的最短路，为方便，我们将其称为**最好路径**。

很显然，如果每次都断开边重构最短路树的话，本质上就是跑了 $n$ 遍最短路，时间复杂度 $O(n^2\log n)$。

根据最短路树的性质，在断开 $i$ 节点到它父亲的边后，最短路一定会经过至少一条非树边，而且**仅经过一条非树边**，因为如果该路径经过多条非树边，那么总有一条非树边可以用最短路树上的一条不包含被断开边的链替代。

因此，断开边后，$1$ 节点到 $i$ 节点的满足要求的最短路一定是 `树上路径-->非树边-->树上路径` 的形式。

我们做如下定义：
+ $d_i$ 表示 $1$ 到 $i$ 的最短路长度
+ $ans_i$ 表示 $1$ 到 $i$ 的最好路径长度
+ $L(u,v)$ 表示 最短路树上 $u$ 和 $v$ 的 LCA
+ $w_{u,v}$ 表示 $u$ 到 $v$ 的边权

![此处应有图片](https://s4.ax1x.com/2022/01/08/7CTcCj.png)

那么我们不妨换一个角度，枚举每一条非树边，考虑有哪些节点到源点的“最好路径”可能经过这条边。经过一些考虑，我们发现，对于边 $(u,v)$，一个节点 $i$ 到 $1$ 的最好路径可能经过它，当且仅当 $i$ 是 $L(u,v)$ 的后代且是 $u$ 或 $v$ 的祖先。

![图片](https://s4.ax1x.com/2022/01/08/7CbfKI.png)

因此，对于每个点 $i$，$ans_i=\min\limits_{u,v}{(d_v+w_{u,v}+d_u-d_i)}$

因为 $d_i$ 不变，所以 $d_v+w_{u,v}+d_u-d_i$ 取得最小值，当且仅当 $d_v+w_{u,v}+d_u$ 取得最小值。

所以，如果将非树边 $(u,v)$ 按 $d_u+w_{u,v}+d_v$ 从小到大排序，再枚举这条边能更新的点，那么每个点第一次被更新时的 $ans_i$ 就是最终答案。那么我们每次更新完就将这个点删除，正确性仍保证。用并查集缩点解决即可。

时间复杂度：$O(n\log n+m\log m)$

# Code

删除上一条边后如果 $1$ 号节点不能到达 $i$，输出 $-1$

~~翻译这道题的人漏了好多要素~~

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;

typedef long long ll;
typedef pair<ll,int> pr;

int n,m;
struct edge{
	int v;
	ll w;
	edge(){} edge(int v_,ll w_){ v=v_,w=w_; }
};
vector<edge> e[100005];

ll d[100005];
int fa[100005][30],dep[100005];

priority_queue<pr> q;
void dijkstra(){
	while(!q.empty()){ q.pop(); }
	for(int i=1;i<=n;i++){ d[i]=-1; }
	d[1]=0;q.push(make_pair(0,1));
	while(!q.empty()){
		pr nw=q.top();q.pop();
		int u=nw.second;
		for(int i=e[u].size()-1;i>=0;i--){
			int v=e[u][i].v;
			ll w=e[u][i].w;
			if(d[v]==-1 || d[v]>d[u]+w){
				d[v]=d[u]+w;
				fa[v][0]=u;
				dep[v]=dep[u]+1;
				q.push(make_pair(-d[v],v));
			}
		}
	}
}

void init(){
	for(int j=1;j<=25;j++){
		for(int i=1;i<=n;i++){
			fa[i][j]=fa[fa[i][j-1]][j-1];
		}
	}
}
int lca(int u,int v){
	if(dep[v]>dep[u]){
		swap(u,v);
	}
	for(int i=25;i>=0;i--) if(dep[fa[u][i]]>=dep[v]) u=fa[u][i];
	for(int i=25;i>=0;i--) if(fa[u][i]!=fa[v][i]){ u=fa[u][i];v=fa[v][i]; }
	return fa[u][0];
}

struct nont{
	int u,v;
	ll w;
	nont(){} nont(int u_,int v_,ll w_){ u=u_,v=v_,w=w_; }
};
bool operator<(nont a,nont b){
	return d[a.u]+d[a.v]+a.w < d[b.u]+d[b.v]+b.w;
}

nont nt[200005];int tp=0;

ll ans[100005];

int nx[100005];
int getfa(int u){
	return (u==nx[u])?u:(nx[u]=getfa(nx[u]));
}

int main(){

	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b;ll t;
		scanf("%d%d%lld",&a,&b,&t);
		e[a].push_back(edge(b,t));
		e[b].push_back(edge(a,t));
	}

	dijkstra();
	init();

	for(int i=1;i<=n;i++){
		ans[i]=-1;	// 没有满足条件路径一定要输出 -1 否则 100Pts -> 40Pts
		nx[i]=i;
		for(int j=e[i].size()-1;j>=0;j--){
			int u=i,v=e[i][j].v;
			ll w=e[i][j].w;
			if(fa[v][0]!=u && fa[u][0]!=v && u<v){
				nt[++tp]=nont(u,v,w);
			}
		}
	}
	sort(nt+1,nt+tp+1);

	for(int i=1;i<=tp;i++){
		int x=nt[i].u,y=nt[i].v;
		ll kw=d[x]+d[y]+nt[i].w;
		int u=getfa(x),v=getfa(y);
		while(u!=v){
			if(dep[u]<dep[v]){
				swap(u,v);
			}
			ans[u]=kw-d[u];
			nx[u]=fa[u][0];
			u=getfa(u);
		}
	}

	for(int i=2;i<=n;i++){
		printf("%lld\n",ans[i]);
	}

	return 0;

}
```


---

## 作者：juju527 (赞：11)

### 一些闲话

很有意思的一道题

~~给我普及了普及组知识点 最短路树~~

### $\texttt{Solution}$

#### 最短路树
已经知道的同学可以跳过

考虑我们跑最短路算法时的松弛操作

用该点对于源点的最短距离更新其他点的最短距离

我们可以记录下来每个点最后一次继承了哪个点的距离

这形成了一个**树结构**，我们简单的将他称为**最短路树**

准确的说，我们能得到一个最短路图，最短路树是最短路图的任意一颗生成树

我们把非最短路树上的边称为非树边

最短路树有一些优越的性质

>它是原图的一颗生成树
>
>每个点与树上任意祖先之间的路径是原图的最短路径

证明比较简单 ~~读者自证不难~~

```cpp
void dijkstra(){
	memset(d,0x3f,sizeof(d));
	q.push((node){1,0});
	d[1]=0;
	while(!q.empty()){
		int k=q.top().id;
		q.pop();
		if(vis[k])continue;
		vis[k]=1;
		for(int i=head[k];i!=-1;i=e[i].nxt){
			int tmp=e[i].to;
			if(d[tmp]<=d[k]+e[i].w)continue;
			d[tmp]=d[k]+e[i].w;
			f[tmp]=k;
			q.push((node){tmp,d[tmp]});
		}
	}
	return ;
}

```
代码实现多一句话记录父亲即可

#### 原题
考虑原题的奇怪问法

我们要得到去掉最短路中最后一条边的最短路，即该点的父边

容易发现，我们只能经过非树边绕过这条父边

能不能经过多条非树边得到呢？

由于证明较为简单，大多数题解忽略了，在这里简证下

考虑两条非树边 $(u_1,v_1),(u_2,v_2)$

其中 $v_1,u_2$ 在一条树链上，可直接到达

$i$ 是 $v_2$ 的祖先

有两种方案 

$1\to u_1\to(u_1,v_1)\to v_1\to u_2\to(u_2,v_2)\to v_2\to i$

$1\to u_2\to (u_2,v_2)\to v_2\to i$

由于最短路树的性质

$1\to u_2<1\to u_1\to(u_1,v_1)\to v_1\to u_2$

故最优方案总是只经过一条非树边到达的方案

有了这个结论

我们只需考虑每条非树边的贡献即可

>一条非树边只能更新两端在最短路树上的路径

这是因为当走到两端lca之上时会走出环来，不再是简单路径

发现对于非树边 $(u,v)$ 点 $i$ 有 $d_u+d_v+w(u,v)-d_i$ 的一种正确走法

其中 $d_i$ 表示 $1\to i$ 的最短路

$w(u,v)$ 表示边 $(u,v)$ 的权值

这里有两种解决方法

一种是上并查集($O(m\alpha(n)+mlogm)$)，一种是暴力树剖（$O(mlog^2n)$）

~~孰优孰劣一目了然~~

考虑 $d_u+d_v+w(u,v)$ 对于一条非树边是固定的，暴力树剖覆盖即可（清新无脑）

同样考虑 $d_u+d_v+w(u,v)$ ，并查集做法将其升序排序依次暴力上跳计算贡献

由于权值经过排序，每个节点仅会被一条非树边贡献一次，用并查集维护已被贡献过的链即可

代码也很小清新

放下树剖的覆盖部分

```cpp
void modify_dist(int x,int y,int w){
	int p=lca(x,y),X=x,val=w+d[x]+d[y];
	while(dep[top[x]]>dep[p]){
		modify(1,1,n,dfn[top[x]],dfn[x],val);
		x=f[top[x]];
	}
	if(dep[x]>dep[p])modify(1,1,n,dfn[p]+1,dfn[x],val);
	while(dep[top[y]]>dep[p]){
		modify(1,1,n,dfn[top[y]],dfn[y],val);
		y=f[top[y]];
	}
	if(dep[y]>dep[p])modify(1,1,n,dfn[p]+1,dfn[y],val);
	return ;
}
```

完整代码就不放了

---

## 作者：伟大的王夫子 (赞：10)

首先，这道题保证最短路径唯一。这有两个意义。首先可以保证 1 到每个点 $i$ 的最短路径的最后一条边唯一。并且可以保证这棵树的最短路径树唯一。所以说，这个信息提醒我们去建最短路径树。这是这类题目的传统套路。最短路径树说白了就是由最短路径上的边构成的树。

那么我们可以先用迪杰斯特拉算法求出 1 到每个节点的最短路，然后构造出以 1 为根的最短路径树。而 1 到 $i$ 的最短路就对应着这棵树上从 1 到 $i$ 的路径。

我们考虑如果不经过最后一条边从 1 到 $i$ 的最短路，也就是说不能经过 $i$ 与他的父亲这条边。于是如果从 $i$ 到 1 这个节点，必须先经过 $i$ 的子树中一个节点 $x$，下一步去一个不在 $i$ 这个子树中的节点 $y$，最后一步显然是走从 $y$ 到 1 的最短路。于是，边 $(x,y,z)$ 可以提供 $dis_x - dis_i + dis_y + z$ 的贡献。其中 $dis_x$ 表是 1 到 $x$ 最短路的值。

那么我们在考虑一下每一条不在最短路径树上的边 $(x,y)$ 可以去更新那些点的答案。根据我们上面的分析，假设他更新了一个点 $i$，那么 $i$ 必然是 $x, y$ 两个点恰好一个点的祖先。于是我们可以求出 $x, y$ 的最近公共祖先，更新一下 $x$ 与 $y$ 到最近公共祖先的路径上的点的答案。当然不包括最近公共祖先这个点。

更新路径是树链剖分的拿手操作。这时我们已经可以在 $O(n \log^2 n)$ 的时间复杂度内完成此题，但显然这个做法还不够优美。

考虑到这题相较一般的树剖题比较特殊，修改全部完成之后再进行询问，并且如果一个节点的答案如果已经被小的数更新过，再用大的数更新也没什么意义。所以说我们可以将每条边按照所更新的这个值从小到大排序，并用并查集进行合并以保证每个节点只更新一次，那么时间复杂度就变成了最短路的复杂度 $O((n+m)\log n)$，效率较高。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int n, m, vc[N << 2], Ne[N << 2], he[N], edv[N << 2], tot, f[N][17], d[N], dep[N], ans[N], fa[N], dis[N];
bool v[N], istree[N << 2];
struct P {
	int x, y, z;
	bool t;
	bool operator < (const P &a) const {
		return z < a.z;
	}
} a[N << 1];
inline void add(int x, int y, int z) {
	vc[++tot] = y, edv[tot] = z, Ne[tot] = he[x], he[x] = tot;
}
int get(int x) {
	return fa[x] == x ? x : fa[x] = get(fa[x]);
}
void dij() {
	priority_queue<pair<int, int> > q;
	memset(d, 0x3f, sizeof d);
	q.push(make_pair(0, 1));
	d[1] = 0;
	while (q.size()) {
		int x = q.top().second;
		q.pop();
		if (v[x]) continue;
		v[x] = 1;
		for (int i = he[x]; i; i = Ne[i]) {
			int y = vc[i], z = edv[i];
			if (d[y] > d[x] + z) {
				d[y] = d[x] + z;
				q.push(make_pair(-d[y], y));
			}
		}
	}
}
int lca(int x, int y) {
	if (dep[x] > dep[y]) swap(x, y);
	for (int i = 16; i >= 0; --i)
		if (dep[f[y][i]] >= dep[x]) y = f[y][i];
	if (x == y) return x;
	for (int i = 16; i >= 0; --i)
		if (f[x][i] ^ f[y][i]) x = f[x][i], y = f[y][i];
	return f[x][0];
}
void dfs(int x) {
	dep[x] = dep[f[x][0]] + 1;
	for (int i = he[x]; i; i = Ne[i]) {
		int y = vc[i], z = edv[i];
		if (d[y] != d[x] + z || y == f[x][0]) continue;
		istree[i] = istree[i ^ 1] = 1;
		f[y][0] = x;
		dis[y] = dis[x] + z;
		dfs(y);
	}
}
int main() {
	tot = 1;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &a[i].x, &a[i].y, &a[i].z);
		add(a[i].x, a[i].y, a[i].z);
		add(a[i].y, a[i].x, a[i].z);
	}
	dij();
	dfs(1);
	for (int i = 1; i <= n; ++i) fa[i] = i;
	for (int j = 1; j <= 16; ++j)
		for (int x = 1; x <= n; ++x)	
			f[x][j] = f[f[x][j - 1]][j - 1];
	for (int i = 1; i <= m; ++i) 
		if (istree[i << 1]) a[i].t = 1;
	for (int i = 1; i <= m; ++i)
		a[i].z += dis[a[i].x] + dis[a[i].y];
	sort(a + 1, a + m + 1, [](const P &a, const P &b) {return a.z < b.z;});
	memset(ans, 0x3f, sizeof ans);
	for (int i = 1; i <= m; ++i) {
		if (a[i].t) continue;
		int x = a[i].x, y = a[i].y, LCA = lca(x, y);
		x = get(x), y = get(y), LCA = get(LCA);
		while (x != LCA) {
			ans[x] = min(ans[x], a[i].z - dis[x]);
			fa[x] = LCA;
			x = get(f[x][0]);
		}
		while (y != LCA) {
			ans[y] = min(ans[y], a[i].z - dis[y]);
			fa[y] = LCA;
			y = get(f[y][0]);
		}
	}
	for (int i = 2; i <= n; ++i) printf("%d\n", ans[i] == 0x3f3f3f3f ? -1 : ans[i]);
}
```

感觉已经讲的比较清楚了，如果有不懂可以提出。

---

## 作者：Piwry (赞：10)

（话说做这道题时我还想了想题目要求求的东西是不是就是次短路...最后当然假了）

## 解析

（文中的记号比较多，而且为了方便一些符号我只在**第一次出现**时进行解释...还请见谅qaq）

我们先思考删去题目所述的一条边（到某点最短路径的最后一条边）后新图的最短路生成树 $T'$ 较原来的最短路生成树 $T$ 的变化

记 $\delta(u, v)$ 表示 $u$ 到 $v$ 的最短路。如果不考虑删去的边来源于哪条最短路，该操作就相当于在 $T$ 上删除一条树边

显然这会让树 $T$ 分为两个连通块。设删除的边 $(u, v)$，我们令 $v$ 所在的连通块不含源点 $s$

这里先设想一种较简单的情况，$v$ 所在连通块只有一个结点：

![eazy](https://cdn.luogu.com.cn/upload/image_hosting/l2scrt7e.png)

显然新的生成树 $T'$ 就是由 $T$ 没有删除的边加上一条原图的边（非树边）组成的，且这条非树边将删除边后 $T$ 分为的两个连通块连通了

那么如果 $v$ 所在连通块的结点数量不止一个呢？

![hard](https://cdn.luogu.com.cn/upload/image_hosting/s78kop26.png)

可能你会直觉地认为 $T'$ 只会在这两个连通块间添加一条边，但思考这样的样例：

![one](https://cdn.luogu.com.cn/upload/image_hosting/m8u40abn.png)

以及 $v$ 所在的子树也可能会重构：

![rebuild](https://cdn.luogu.com.cn/upload/image_hosting/mf1w2b54.png)

&nbsp;

这看起来让问题变得复杂了起来

但我们其实并不关心 $T'$ 的具体形态；我们实际上只想求出 $T'$ 上的 $\delta(s, v)$

思考最短路的**最优子结构**性质，实际上我们有这样一个结论：

> $\text{Lemma 1.}$ 最短路生成树上，若对于点 $x, y$，有 $\text{lca}(x, y)=x$ 或 $y$，则树上的路径 $p(x, y)=\delta(x, y)$

接着我们又发现，虽然我们不知道这两个连通块之间会多加上多少边，但它们之间至少会加上一条边，否则 $T'$ 将会不连通

再联系 $\text{Lemma 1}$，可以发现在新树 $T'$ 上，$\delta(s, v)$ 一定是由原树 $T$ 上的路径 $p(s, x), p(y, v)$，加上一条边 $(x, y)$ 组成的（注意这两个路径可能没有边）

于是我们就可以枚举结点，并对每个结点枚举所有非树边，并在所有可能的答案中取个 $\text{min}$

**具体来说**，一条非树边 $(x, y)$ 连接了两个连通块（可以判断 $x, y$ 是否一个在点 $v$ 的子树中，另一个不在，可用倍增查找父亲实现），其对结点 $v$ 的贡献就是 $|p(s, x)|+|(x, y)|+|p(y, v)|$，其中 $p(.)$ 指原图最短路生成树的路径，$|.|$ 指某条路径的权重（边权和）

&nbsp;

但这样复杂度绝对会爆掉的

我们考虑**先**枚举非树边。设这条边为 $(x, y)$，可以想到只有 $p(x, y)$ 上的点，且不含 $\text{lca}(x, y)$ 才会被这条边更新答案。这样让我们的复杂度少了一些，但还是太大

思考有没有办法先枚举 "**更优的**"，非树边，以期望不每次都更新链上的结点

这里有一个跳跃性的结论（我没直接想到，是听了题解才懂的...）：

> $\text{Lemma 2.}$ 若将所有非树边 $(x, y)$ 按权值 $|p(s, x)|+|(x, y)|+|p(s, y)|$ 从小到大排序并枚举（其中 $p(.)$ 指原图最短路生成树的路径）每个结点**第一次**被更新时一定是最优的

$\text{Proof.}$ 设两条非树边 $(x, y), (x', y')$，且令 $|p(s, x)|+|(x, y)|+|p(s, y)|\leq|p(s, x')|+|(x', y')|+|p(s, y')|$，由结论阐述可知 $(x, y)$ 会比 $(x', y')$ 先枚举到

我们发现，对于一个结点 $v$，只有其满足 $v\in\{p(x, y)\cup p(x', y')\}, v\notin\{\text{lca}(x, y), \text{lca}(x', y')\}$ 时才会**同时**被这两条边更新贡献，因此我们只考虑这些点的答案情况

一条非树边 $(x, y)$ 对结点 $v$ 的贡献是 $|p(s, x)|+|(x, y)|+|p(y, v)|$；而我们发现，根据上面的不等式其实可以推出：

$|p(s, x)|+|(x, y)|+|p(s, y)|\leq|p(s, x')|+|(x', y')|+|p(s, y')|$

$|p(s, x)|+|(x, y)|+(|p(s, y)|-|p(s, v)|)\leq|p(s, x')|+|(x', y')|+(|p(s, y')|-|p(s, v)|)$

$|p(s, x)|+|(x, y)|+|p(y, v)|\leq|p(s, x')|+|(x', y')|+|p(y', v)|$（因为 $x, y, x', y'$ 的深度一定比 $v$ 大）

不等式左右两边实际上就是用 $(x, y), (x', y')$ 更新结点 $v$ 时 $v$ 的答案

也就是说，用 $(x, y)$ 更新 $v$ 一定比用 $(x', y')$ 更优

由此证毕

（觉得式子有点难懂可以结合下面四种图例思考下；图有点丑qaq）

![sample](https://cdn.luogu.com.cn/upload/image_hosting/ae919tr0.png)

&nbsp;

至于如何让每个结点只被访问到一次，可以考虑用**并查集**将已访问的连通块缩成一个结点

最后算法的复杂度就大约是 $O(m\log m+n+m)$

## CODE

```cpp
#include <cstdio>
#include <queue>
#include <cstring>
#include <algorithm>
#define ll long long
using std::priority_queue;
using std::vector;
using std::sort;

/*------------------------------Map------------------------------*/

const int MAXN =1e5+50, MAXM =4e5+50;

int fst[MAXN], tote, dist[MAXN];
bool vis[MAXN], usede[MAXM]/*记录该边是否作为树边被使用*/;
struct edge{
	int net, to, val;
}e[MAXM];
struct elm{
	int to, dist, val, from, eid;
	elm(int tt, int d, int v, int f, int ei):to(tt), dist(d), val(v), from(f), eid(ei){}
	bool operator < (const elm &B) const{ return dist > B.dist; }
};

priority_queue<elm, vector<elm> > que;

inline void addedge2(int u, int v, int val);

inline void dijkstra(){
	memset(dist, 0x3f, sizeof(dist));
	dist[1] =0;
	que.push(elm(1, 0, 0, 0, 0));
	while(que.size()){
		elm nw =que.top();
		que.pop();
		if(vis[nw.to]) continue;
		if(nw.from != 0){
			addedge2(nw.from, nw.to, nw.val);
			usede[nw.eid] =1;
			if(nw.eid%2 == 0)
				usede[nw.eid-1] =1;
			else
				usede[nw.eid+1] =1;
		}
		vis[nw.to] =1;
		for(int l =fst[nw.to]; l; l =e[l].net)
			if(!vis[e[l].to] && dist[nw.to]+e[l].val < dist[e[l].to]){
				dist[e[l].to] =dist[nw.to]+e[l].val;
				que.push(elm(e[l].to, dist[nw.to]+e[l].val, e[l].val, nw.to, l));
			}
	}
}

inline void addedge(int u, int v, int val){
	tote++;
	e[tote].net =fst[u], fst[u] =tote, e[tote].to =v;
	e[tote].val =val;
}

/*------------------------------dfs------------------------------*/

edge e2[MAXM];
int fst2[MAXN], tote2;

inline void addedge2(int u, int v, int val){
	tote2++;
	e2[tote2].net =fst2[u], fst2[u] =tote2, e2[tote2].to =v;
	e2[tote2].val =val;
}

int f[MAXN], topl[MAXN], size[MAXN], ws[MAXN]/*重儿子*/, dep[MAXN], dep2[MAXN]/*经过树边数*/;

void dfs1(int u, int fa){
	size[u] =1;
	f[u] =fa;
	for(int l =fst2[u]; l; l =e2[l].net){
		/*dep 的值其实和 dist 一样*/
		dep[e2[l].to] =dep[u]+e2[l].val;
		dep2[e2[l].to] =dep2[u]+1;
		dfs1(e2[l].to, u);
		size[u] +=size[e2[l].to];
	}
	if(size[u] > size[ws[fa]])
		ws[fa] =u;
}

void dfs2(int u, int fa){
	if(fa != 0 && ws[fa] == u)
		topl[u] =topl[fa];
	else
		topl[u] =u;
	for(int l =fst2[u]; l; l =e2[l].net)
		dfs2(e2[l].to, u);
}

int Lca(int x, int y){
	while(topl[x] != topl[y]){
		/*优先跳链顶深的*/
		if(dep2[topl[x]] < dep2[topl[y]])
			x ^=y ^=x ^=y;
		x =f[topl[x]];
	}
	if(dep2[x] < dep2[y])
		x ^=y ^=x ^=y;
	return y;
}

/*------------------------------Slove------------------------------*/

struct edge2{
	int u, v, val, key;
	edge2(){}
	edge2(int uu, int vv, int va, int ke):u(uu), v(vv), val(va), key(ke){}
	bool operator < (const edge2 &B) const{ return key < B.key; }
}cross[MAXM];/*横叉边*/
int tot;

int ans[MAXN];
int f2[MAXN];

/*这里偷懒没加按矢合并 qaq，这题反正没卡*/
int get(int x){
	if(f2[x] != x)
		return f2[x] =get(f2[x]);
	else
		return x;
}

/*------------------------------Main------------------------------*/

inline int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (48^c), c =getchar();
	return x;
}

int main(){
	int n =read(), m =read();
	for(int i =1; i <= m; ++i){
		int u =read(), v =read(), w =read();
		addedge(u, v, w);
		addedge(v, u, w);
	}
	dijkstra();
	dfs1(1, 0), dfs2(1, 0);
	for(int i =1; i <= tote; i +=2){
		if(usede[i])
			continue;
		int u =e[i].to, v =e[i+1].to;
		cross[tot++] =edge2(u, v, e[i].val, e[i].val+dep[u]+dep[v]);
	}
	sort(cross, cross+tot);
	memset(ans, -1, sizeof(ans));
	for(int i =1; i <= n; ++i)
		f2[i] =i;
	for(int i =0; i < tot; ++i){
		edge2 nw =cross[i];
		int lca =Lca(nw.u, nw.v);
		int x =nw.u;
		while(dep2[x] > dep2[lca]){
			x =get(x);
			if(!(dep2[x] > dep2[lca]))/*<- 填锅*/
				continue;
			if(ans[x] == -1)
				ans[x] =(dep[nw.u]-dep[x])+nw.val+dep[nw.v];
			/*确保每个并查集只有代表节点可能没被更新过*/
			f2[x] =f[x];
			x =f[x];
		}
		x =nw.v;
		while(dep2[x] > dep2[lca]){
			x =get(x);
			if(!(dep2[x] > dep2[lca]))
				continue;
			if(ans[x] == -1)
				ans[x] =(dep[nw.v]-dep[x])+nw.val+dep[nw.u];
			f2[x] =f[x];
			x =f[x];
		}
	}
	for(int i =2; i <= n; ++i)
		printf("%d\n", ans[i]);
}
```

---

## 作者：iostream (赞：9)

这题可以用最短路算法做，求出单源最短路之后，形成一颗最短路树。

我们发现从点u走到点v，显然必须要通过不在树上的边，这样我们只要求min{w(u,v)+d(u)+d(v)-d(f)}

枚举点f，统计答案时再用并查集维护u,v是否联通即可。

注意：这里必须用堆优化Dijkstra跑最短路，spfa要TLE

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<queue>
using namespace std;
const int N=200010;
int n,m,adj[N<<1],nxt[N<<1],head[N],tot,w[N<<1];
int vis[N],dis[N],fa[N];
inline void adde(int u,int v,int d){
    adj[++tot] = v;
    w[tot] = d;
    nxt[tot] = head[u];
    head[u] = tot;
}
inline void spfa(int start){
    queue<int> q;
    q.push(start);
    memset(dis,127,sizeof(dis));
    memset(vis, 0 ,sizeof(vis));
    vis[start]=1;dis[start]=0;
    while(!q.empty()){
        int u=q.front();q.pop();
        vis[u]=0;
        for(int e=head[u],v;e;e=nxt[e]){
            v=adj[e];
            if(dis[u]+w[e]<dis[v]){
                dis[v]=dis[u]+w[e];
                fa[v]=u;
                if(!vis[v]){
                    vis[v]=1;
                    q.push(v);
                }
            }
        }
    }
}
void SPFA(int S)
{
    priority_queue<pair<int,int>,vector<pair<int,int> >,greater<pair<int,int> > > q;
    for (int i=1; i<=n; i++) dis[i]=1<<30;
    q.push(make_pair(0,S)); dis[S]=0;
    while (!q.empty())
        {
            int now=q.top().second;
            int Dis=q.top().first;
            q.pop();
            if (Dis>dis[now]) continue;
            for (int i=head[now]; i; i=nxt[i])
                if (Dis + w[i] < dis[adj[i]])
                    dis[adj[i]]=Dis+w[i],
                    fa[adj[i]]=now,
                    q.push(make_pair(dis[adj[i]],adj[i]));
        }
}
struct road{
    int u,v,w;
}a[N];
int cnt;
inline bool cmp(road a,road b){
    return a.w<b.w;
}
int f[N],ans[N],num;
inline int find(int i){return f[i]==i?i:f[i]=find(f[i]);} 
inline void calc(road x){
    int u=x.u,v=x.v,t=x.w;
    while(find(u)!=find(v)){ num++;
        if(dis[find(u)]<dis[find(v)])swap(u,v);
        ans[find(u)]=min(ans[find(u)],t-dis[find(u)]);
        u=f[find(u)]=fa[find(u)];
    }
}
inline int get(){
    char c; int s;
    for(c=getchar();c<'0'||c>'9';c=getchar());
    for(s=0;c>='0'&&c<='9';c=getchar())s=(s<<1)+(s<<3)+c-'0';
    return s;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1,u,v,l;i<=m;i++){
        u=get(),v=get(),l=get();
        adde(u,v,l);adde(v,u,l);
    }
    //spfa(1);
    SPFA(1);
    for(int i=2;i<=tot;i+=2){
        int u=adj[i],v=adj[i-1];
        if(u!=fa[v]&&v!=fa[u]){
            a[++cnt].u=u,a[cnt].v=v,a[cnt].w=w[i]+dis[u]+dis[v];
        }
    }
    sort(a+1,a+1+cnt,cmp);
    for(int i=1;i<=n;i++)f[i]=i,ans[i]=1<<30;
    for(int i=1;i<=cnt&&num<n-1;i++)
        calc(a[i]);
    for(int i=2;i<=n;i++)
        printf("%d\n",ans[i]==1<<30?-1:ans[i]);
    return 0;
}
```

---

## 作者：Hoks (赞：8)

## 前言
某模拟赛中打到的，场上切了，感觉还挺有趣的？
## 思路分析
这个题目操作是封住最后一条边，而给的限制条件也很奇怪：特别地，保证 $1$ 到任何一个点 $i$ 的最短路都是唯一的。

最后一条边不好考虑，我们考虑从限制条件下手。

这个限制条件告诉我们，如果我们只保留最短路会走过的边，那么剩下的就是一颗树。

因为路径唯一，所以最后一条边也唯一，推一下也就是对于每个点他的父亲唯一，那么显然就是一个树的形状。

考虑用 dijkstra 求出最短路的同时处理出最短路树。

这样第一步就完成了，我们有了一颗最短路树，接下来按照题目的要求要封住最后一条边球最短路。

显然大力的方法会 T 飞，考虑优化。

考虑我们已经求出 $1$ 到点 $i$ 的距离数组 $d_i$。

假设我们要求的点为 $x$，目前有条边 $u\rightarrow v$ 边权为 $w$ 且 $v$ 在 $x$ 子树里，那么经过这条边到 $x$ 这条边的路径长度即为 $d_u+w+d_v-d_x$。

因为对于每条边，他的 $d_u+w+d_v$ 是固定的，而对于每个点，他的 $d_x$ 是固定的，所以说一个点的答案最多被一条边更新一次即可。

显然的是考虑先用 $d_u+w+d_v$ 小的边更新点的答案，所以先按照这个值对于所有非树边排序。

然后考虑更新过程如何做到让一个点最多被更新一次。

想到并查集，对于一个点，更新他后把他合进父亲中即可。

显然，这题树剖也可以做，做法类似于其结合 MST 时的做法，在此不多赘述，读者可以自行思考一二（其实是我考场懒得码就上并查集了）。

Tips：题目有无解，无解输出 $-1$。
## 代码
```cpp
#include <bits/stdc++.h>
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=200010,p=338651,INF=0x3f3f3f3f3f3f3f3f;
struct edge{int v,w,id;};
struct node{int u,v,w;};
int n,m,cnt;bool mp[N];
int bcu[N<<1],bcv[N<<1],bcw[N<<1],a[N],d[N],ans[N],fa[N],dep[N];
vector<int>e[N];vector<edge>g[N];vector<node>eg;
namespace Fast_IO
{
    static char buf[1000000],*paa=buf,*pd=buf;
    #define getchar() paa==pd&&(pd=(paa=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*paa++
    inline int read()
    {
        int x(0),t(1);char fc(getchar());
        while(!isdigit(fc)){if(fc=='-') t=-1;fc=getchar();}
        while(isdigit(fc)) x=(x<<1)+(x<<3)+(fc^48),fc=getchar();
        return x*t;
    }
    inline void print(int x)
    {
        if(x<0) putchar('-'),x=-x;
        if(x>9) print(x/10);
        putchar(x%10+'0');
    }
}
using namespace Fast_IO;
void dij()
{
    priority_queue<pair<int,int>>q;q.push(make_pair(0,1));memset(d,0x3f,sizeof d);d[1]=0;
    while(!q.empty())
    {
        int u=q.top().second;if(d[u]<-q.top().first){q.pop();continue;}q.pop();dep[u]=dep[fa[u]]+1;
        for(auto to:g[u])
        {
            int v=to.v,w=to.w;
            if(d[u]+w<d[v])
            {
                d[v]=d[u]+w;mp[a[v]]=0;
                q.push(make_pair(-d[v],v));fa[v]=u;
            }
        }
    }
}
inline void add(int u,int v) { e[u].emplace_back(v),e[v].emplace_back(u); }
struct DSU
{
    vector<int> h;
    inline void init(int n){h=vector<int>(n+10);for(int i=1;i<=n;i++) h[i]=i;}
    inline int find(int x){return h[x]==x?x:h[x]=find(h[x]);}
}f;
bool cmp(node x,node y){return d[x.u]+d[x.v]+x.w<d[y.u]+d[y.v]+y.w;}
signed main()
{
	n=read(),m=read();
	for(int i=1,u,v,w;i<=m;i++) bcu[i]=u=read(),bcv[i]=v=read(),bcw[i]=w=read(),g[u].emplace_back((edge){v,w,i}),g[v].emplace_back((edge){u,w,i});
	dij();memset(ans,-1,sizeof ans);
	for(int i=1;i<=m;i++) if(fa[bcu[i]]!=bcv[i]&&fa[bcv[i]]!=bcu[i]) eg.emplace_back((node){bcu[i],bcv[i],bcw[i]});
	sort(eg.begin(),eg.end(),cmp);f.init(n);
	for(auto i:eg)
	{
		int u=f.find(i.u),v=f.find(i.v);
		while(u!=v)
		{
			if(dep[u]<dep[v]) swap(u,v);
			ans[u]=d[i.u]+d[i.v]+i.w-d[u];
			f.h[u]=fa[u];u=f.find(u);
		}
	}
	for(int i=2;i<=n;i++) print(ans[i]),puts("");
    return 0;
}
```

---

## 作者：rhdeng (赞：8)

[传送~](https://www.luogu.org/problemnew/show/P2934)

## Description

有一张n个点m条边的无向图，对于每个u($1<u \leq n$)，求删去1到u的最短路的最后一条边后，从1到u的最短距离

## Solution

首先建出最短路树。新的最短路肯定不能走它到父亲的边，那么必须要找一个或两个中介点，使得它与1连通。设当前点位i，其中一个中介点位u。如果i与u有一条边直接连接，则距离为$dis_u+w_{u,i}$；或者在i的子树中存在一点v与u有边相连，则距离为$dis_u+w_{u,v}+dis_v-dis_i$。将两种情况统一，若u与点v有边相连(v=i或v在i的子树内)，则新的距离为$dis_u+w_{u,v}+dis_v-dis_i$。由于$dis_i$确定，所以只要$dis_u+w_{u,v}+dis_v$最小即可。到这里与上面的题解都差不多，但是这里给出一种用堆的做法。

在dfs的过程中，把每个点可以得到的所有$dis_u+w_{u,v}+dis_v$存在一个堆里。具体做法是先把所有儿子的堆合并(要用左偏树)，再枚举出边把新的u及其值加入堆中，最后取堆顶时删掉不满足条件的(即两个点都在子树内)。

## Code
```cpp
#include <bits/stdc++.h>
#define mk make_pair
#define fst first
#define snd second
using namespace std;
const int maxn = 1e5;
const int maxm = 2e5;
const int maxt = 4e6; 
const int inf = 1e9;
typedef pair<int, int> pii;
int n, m, tot, cnt, head[maxn+10], dis[maxn+10], done[maxn+10], pd[maxm*2+10], dfn[maxn+10], size[maxn+10], ans[maxn+10], root[maxn+10];
struct edge {
	int to, nex, dis;
} edges[maxm*2+10];
struct node {
	int to, ls, rs, fa, dis, val;
} t[maxt+10];
void addedge(int u, int v, int w) {
	edges[++tot] = (edge){v, head[u], w}; head[u] = tot;
	edges[++tot] = (edge){u, head[v], w}; head[v] = tot;
}
int find(int x) {
	return x == t[x].fa ? x : t[x].fa = find(t[x].fa);
}
int merge(int x, int y) {
	if (!x || !y) return x+y;
	if (t[x].val > t[y].val) swap(x, y);
	t[x].rs = merge(t[x].rs, y);
	t[t[x].rs].fa = x;
	if (t[t[x].ls].dis < t[t[x].rs].dis) swap(t[x].ls, t[x].rs);
	t[x].dis = t[t[x].rs].dis+1;
	return x;
}
int remove(int x) {
    /*t[t[x].ls].fa = t[x].ls;
    t[t[x].rs].fa = t[x].rs;
    t[x].fa = merge(t[x].ls, t[x].rs);
    t[x].ls = t[x].rs = t[x].dis = 0;
    return t[x].fa;*/
	return merge(t[x].ls, t[x].rs);
}
void dijkstra() {
	memset(dis, 0x3f, sizeof(dis));
	priority_queue<pii, vector<pii>, greater<pii> > q;
	q.push(mk(dis[1] = 0, 1));
	while (!q.empty()) {
		int x = q.top().snd; q.pop();
		if (done[x]) continue;
		done[x] = 1;
		for (int i = head[x]; i; i = edges[i].nex) {
			edge e = edges[i];
			if (dis[e.to] > dis[x]+e.dis)
				q.push(mk(dis[e.to] = dis[x]+e.dis, e.to));
		}
	}
}
int check(int u, int v) {
	return dfn[v] >= dfn[u] && dfn[v] < dfn[u]+size[u];
}
void dfs(int u, int fa) {
	dfn[u] = ++size[0]; size[u] = 1;
	for (int i = head[u]; i; i = edges[i].nex) {
		int v = edges[i].to;
		if (v == fa || !pd[i]) continue;
		dfs(v, u); root[u] = merge(root[u], root[v]);
		size[u] += size[v];
	}
	for (int i = head[u]; i; i = edges[i].nex) {
		int v = edges[i].to;
		if (v == fa || pd[i]) continue;
		t[++cnt] = (node){v, 0, 0, cnt, 0, dis[u]+dis[v]+edges[i].dis};
		root[u] = merge(root[u], cnt);
	}
	while (check(u, t[root[u]].to)) root[u] = remove(root[u]);
	ans[u] = root[u] ? t[root[u]].val-dis[u] : - 1;
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int u, v, w;
		scanf("%d%d%d", &u, &v, &w);
		addedge(u, v, w);
	}
	dijkstra();
	for (int i = 1; i <= n; ++i)
		for (int j = head[i]; j; j = edges[j].nex)
			if (dis[edges[j].to] == dis[i]+edges[j].dis) pd[j] = 1;
	cnt = n; dfs(1, 0);
	for (int i = 2; i <= n; ++i)
		printf("%d\n", ans[i]);
	return 0;
} 
```
> *THANK YOU FOR READING THIS!*

---

## 作者：panxz2009 (赞：6)

经典好题，写篇题解加深一下理解。
### Part1 50pts
模拟整个过程。先从 $1$ 到其他所有点各跑一遍最短路，找出每条最短路的最后一条边，手动删除这条边，然后再跑一遍最短路。时间复杂度是 $O(nm \log m)$。可以通过 $N \le 3000$ 的数据。
### Part2 100pts
首先，关注到题中一句话：  
> 特别地，保证 $1$ 到任何一个点 $i$ 的最短路都是唯一的。 

故容易得知，当 $1$ 到其他任一点都跑一遍最短路后，所有被最短路经过的边形成一个新的无向图，该无向图**一定无环**，从而该图**一定是一棵树**，不妨把它称作“**最短路树**”。  

当我们求出最短路树后，再对每一个非 $1$ 的点到 $1$ 的最短路分别进行考虑。  
假设现在考虑点 $i$。显然，在删除了最后一条边后，如果要到达点 $i$，需要一条边连接 $i$ 的子树内任意一节点 $u$，和子树外任意一节点 $v$。  
原先的 $1→k$ 现在转化为 $1→u→v→k$，而 $1→u→v→k=u→1+u→v+v→1-k→1$。因为 $k→1$ 是已知的定值，所以只要关注 $u→1+v→1+u→v$ 这个和非树边 $(u,v)$ 有关联的值即可，令它等于 $f(u,v)$。

一方面，我们先树链剖分，然后用线段树维护 $f(u,v)$ 的最小值即可，时间复杂度 $O(n \log^2 n)$。

~~但这样显然不够优雅~~。但事实上可以使用并查集，做法更加简洁，时间复杂度可以达到 $O(n)$。  
我们发现，一个点被一条边权最小的边更新之后，就不会再被更新了。于是考虑对边**按照其 $f(u,v)$ 的值排**序，对于每条边暴力找路径，更新答案。但是每次更新完一个点，下次如果再访问它，直接跳到它的最近没被删的祖先。这样的操作就类似于并查集路径压缩，所以用并查集实现，于是这题就做完了。

---

## 作者：xtx1092515503 (赞：4)

神题。

首先是用$Dijkstra$建出最短路径树。即为：所有的边$(u,v,w)$，使得$dis_u=dis_v+w$成立。因为数据保证，这个边集构成一颗树，因此我们可以尝试各种树上操作。

这个时候我们就可以搬出经典老题[network](http://poj.org/problem?id=3417)了。考虑如何计算每条非树边对答案的影响。

显然，一条从$i$到$1$的新最优路径，肯定是这样的：

$i\rightarrow i$子树中的某个点$j\rightarrow$非树边$(j,k,l)\rightarrow$不在$i$子树内的点$k \rightarrow 1$

而这条路径的长度为$dis_j+dis_k-dis_i+l$

显然，对于同一条$(j,k,l)$，$dis_j+dis_k+l$是定值；

而对于同一个点$i$，$dis_i$也是定值。

考虑边$(j,k,l)$能影响到的点为：路径$[j,lca_{j,k})\cup [k,lca_{j,k})$上的点。

注意不包括$lca_{j,k}$，因为此时点$j,k$都在它的子树里。

则对于每一条$(j,k,l)$，它可以对$[j,lca_{j,k})\cup [k,lca_{j,k})$上的点产生$dis_j+dis_k+l$的贡献。

如果将每一条新边按照$dis_j+dis_k+l$从大到小排序的话，就可以在最短路径树上用树链剖分暴力覆盖（将两个点路径上的所有点的点权覆盖成$dis_j+dis_k+l$。

则最后点$i$的答案就是$($树剖中点$i$最后被覆盖的点权$)-dis_i$。

如果点$i$没有被覆盖过，则答案是$-1$。~~（我不会告诉你因为没有注意到这一点我debug了一下午的）~~

~~并查集是看不懂的，这辈子都是看不懂的。~~

总复杂度为$O(nlog_2^2n)$。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1)
int n,m,head[100100],cnt,dep[100100],fa[100100],dfn[100100],sz[100100],son[100100],top[100100],rev[100100],dis[100100],tot,tag[400100];
struct Edge{
	int to,next,val;
}edge[400100];
void ae(int u,int v,int w){
	edge[cnt].next=head[u],edge[cnt].to=v,edge[cnt].val=w,head[u]=cnt++;
}
struct EDGE{
	int u,v,w;
	friend bool operator <(const EDGE &x,const EDGE &y){
		return x.w>y.w;
	}
}e[200100];
bool vis[100100];
priority_queue<pair<int,int> >q;
void Dijkstra(){
	memset(dis,0x3f3f3f3f,sizeof(dis)),dis[1]=0,q.push(make_pair(0,1));
	while(!q.empty()){
		int x=q.top().second;q.pop();
		if(vis[x])continue;vis[x]=true;
		for(int i=head[x];i!=-1;i=edge[i].next)if(dis[edge[i].to]>dis[x]+edge[i].val)dis[edge[i].to]=dis[x]+edge[i].val,q.push(make_pair(-dis[edge[i].to],edge[i].to));
	}
}
void dfs1(int x,int Fa){
	sz[x]=1,fa[x]=Fa,dep[x]=dep[Fa]+1;
	for(int i=head[x],y;i!=-1;i=edge[i].next){
		if((y=edge[i].to)==Fa)continue;
		dfs1(y,x),sz[x]+=sz[y];
		if(sz[y]>sz[son[x]])son[x]=y;
	}
}
void dfs2(int x){
	if(son[x]){
		top[son[x]]=top[x];
		rev[son[x]]=++tot;
		dfn[tot]=son[x];
		dfs2(son[x]);
	}
	for(int i=head[x],y;i!=-1;i=edge[i].next){
		y=edge[i].to;
		if(y==fa[x]||y==son[x])continue;
		top[y]=y,rev[y]=++tot,dfn[tot]=y;
		dfs2(y);
	}
}
vector<EDGE>v;
void pushdown(int x){
	if(!tag[x])return;
	tag[lson]=tag[rson]=tag[x];
	tag[x]=0;
}
void modify(int x,int l,int r,int L,int R,int val){
	if(l>R||r<L)return;
	if(L<=l&&r<=R){tag[x]=val;return;}
	pushdown(x),modify(lson,l,mid,L,R,val),modify(rson,mid+1,r,L,R,val);
}
int query(int x,int l,int r,int P){
	if(l>P||r<P)return 0;
	if(l==r)return tag[x];
	pushdown(x);
	return query(lson,l,mid,P)+query(rson,mid+1,r,P);
}
void Add(int x,int y,int w){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
//		printf("N:%d %d %d\n",top[x],x,w);
		modify(1,1,n,rev[top[x]],rev[x],w);
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	if(rev[x]!=rev[y])modify(1,1,n,rev[x]+1,rev[y],w);
}
int main(){
	scanf("%d%d",&n,&m),memset(head,-1,sizeof(head));
	for(int i=1,x,y,z;i<=m;i++)scanf("%d%d%d",&x,&y,&z),ae(x,y,z),ae(y,x,z),e[i].u=x,e[i].v=y,e[i].w=z;
	Dijkstra(),memset(head,-1,sizeof(head)),cnt=0;
	for(int i=1;i<=m;i++){
		if(dis[e[i].u]==dis[e[i].v]+e[i].w||dis[e[i].v]==dis[e[i].u]+e[i].w)ae(e[i].u,e[i].v,e[i].w),ae(e[i].v,e[i].u,e[i].w);
		else e[i].w+=dis[e[i].u]+dis[e[i].v],v.push_back(e[i]);
	}
//	for(int i=1;i<=n;i++)printf("%d ",dis[i]);puts("");
//	for(int i=0;i<v.size();i++)printf("%d %d %d\n",v[i].u,v[i].v,v[i].w);
	sort(v.begin(),v.end());
	dfs1(1,0),dfn[1]=rev[1]=top[1]=tot=1,dfs2(1);
	for(int i=0;i<v.size();i++)Add(v[i].u,v[i].v,v[i].w);
	for(int i=2;i<=n;i++){
		int t=query(1,1,n,rev[i]);
		if(t)printf("%d\n",t-dis[i]);
		else puts("-1");
	}
	return 0;
}
/*
7 10
1 3 2
1 2 4
1 4 2
4 3 4
2 3 6
2 5 1
5 6 4
5 7 8
7 6 1
7 3 1
*/
```
最后附赠了一组样例方便后人，答案应为$8,6,6,8,9,10$。

---

## 作者：MikukuOvO (赞：4)

先把最短路树建出来，然后我们考虑一条非树边$(u,v)$对于答案的贡献，我们不难发现如果一个点$x$在$v->lca(u,v)$的路径上，那么我们可以走$1->u->v->x$这样的路径来更新$x$的答案$val(u,v)+dis[u]+dis[v]-dis[x]$，不难发现这个不太好区间维护，那么我们考虑每个点的最优解，我们把边按照$val(u,v)+dis[u]+dis[v]$来排序即可，这样在前面的边对于答案的贡献一定比后面优，因此每个点只要更新一遍，并查集维护即可。

[$code$](https://pastebin.com/zjZeJFDZ)

---

## 作者：A_Sunny_Day (赞：3)

## [USACO09JAN]Safe Travel G

​	题目链接：[[USACO09JAN]Safe Travel G](https://www.luogu.com.cn/problem/P2934)

​	又是一道初见杀的题目，这道题是跟**最短路树**有关。何为最短路树？

​	考虑一个连通无向图 $G$，一个顶点 $v$ 为根节点的最短路径树 $T$ 是图 $G$ 满足下列条件的生成树——树 $T$ 中从根节点 $v$ 到其他顶点 $u$ 的路径距离，在图 $G$ 中是 $v$ 到 $u$ 的最短路径距离。

​	这个定义还是比较好理解的，那么我们怎么构造出最短路径树呢？既然跟最短路有关，我们先用 Dijkstra 算法预处理出图 $G$ 中 $v$ 节点到其他所有顶点 $u$ 的最短距离。然后对于一条边 $E$ 设它两端的节点为 $x,y$，边权值为 $w$ 如果 $dis_x+w=dis_y$ 就说明在最短路径树中 $x$ 是 $y$ 的父亲节点。这样在本题中是正确的。因为据题意描述，根节点 $v$ 到任意一个顶点 $u$ 的路径是**唯一**的。这么连，首先它是**连通**的，因为每个节点的最短路径都是**存在**的。其次，一共有 $n$ 个节点，我们对除了根节点 $v$ 外的每个节点都找了一个父亲，所以有 $n-1$ 条边。那么我们这么构造出来的就是一棵**最短路径树**了。

​	构造出一棵最短路径树后，我们来试着添加**无用边**，这里的无用边指的是**题目中给出，但最短路径树中没用到的边**。首先看下图。

[![WhPevF.png](https://z3.ax1x.com/2021/07/26/WhPevF.png)](https://imgtu.com/i/WhPevF)

​	图中的红边是一条**无用边**。边权为 $w$，而两端节点为 $x,y$ 我们来考虑下怎么更新 $u$ 点的答案。如果要更新 $u$ 点的话那么只能通过无用边走过去。通过最短路径树的定义可知。从根节点到一个顶点 $u$ 的距离为 $dis_u$。那么我们可以通过这个性质可知，$u$ 到 $y$ 的距离就为 $dis_y-dis_u$。那么我们就可以得知：
$$
ans_u=\min(ans_u,dis_x+w+dis_y-dis_u)
$$
​	所以我们可以知道，我们可以用这条边，将图中这个环所有的除了 LCA 外的点全部更新。为什么LCA不能更新呢，因为 LCA 最短路径的最后一条边不在这个子树里了。

​	但是这么更新我们的时间是肯定承受不住的。因为我们重复更新了许多点。那能不能让每个点只更新一次呢，我们考虑将边排序，对于更新的点 $u$ 来说 $dis_u$ 是不变的，我们考虑对于每条边$E$，它两边的节点为 $x,y$，边权为 $w$。我们按照 $dis_x+dis_y+w$ 从小到大进行排序，这样我们使得每个点在第一次更新时就是它的最小值。

​	但是我们在更新时，依然会遍历无用的点导致时间复杂度丝毫没有下降，那么我们得跳过已经更新过的点，这个时候我们可以使用一个常规的套路**并查集缩点**。

​	[![WhAbf1.png](https://z3.ax1x.com/2021/07/26/WhAbf1.png)](https://imgtu.com/i/WhAbf1)

​	考虑一个一维数组，我们将遍历过一次的点 $i$ 的祖先设为 $i+1$。然后每次访问我们都访问这个节点的祖先，效果像图中所示，假设 2，3都已经被遍历过，我们从1开始遍历，遍历到2时，由于访问的是它的祖先节点，所以直接会跳到4去，这样我们就实现了**不重复遍历**的目的。

​	一维数组并查集缩点伪代码如下：

```cpp
for(int i=1;i<=n;i=find(i+1))
{
	.....//操作
	f[i]=i+1; 
}
```

​	并查集缩点的优势就在于多次遍历同一段不会重复，我们将一维数组想像成一条链运用在树上，这题就成了，树上并查集缩点代码如下：

```cpp
	for(int i=1;i<=m;++i)
	{
		int u=edge[i].u,v=edge[i].v,w=edge[i].w;
		if(dis[u]+w==dis[v]||dis[v]+w==dis[u]) continue;
		int x=find(u),y=find(v);
		while(x!=y)
		{
			if(dep[x]<dep[y]) swap(x,y);
			ans[x]=dis[u]+dis[v]+w-dis[x];
			f[x]=fa[x];
			x=find(x);
		}
	}
```

​	如果 $x$ 直接跳到 LCA 上面了会不会有问题呢？实际上并不会， $x$ 跳到 LCA 上面说明 LCA 已经更新过了，这时候另一个点跳到 LCA 时就会与 $x$ 重合。

​	代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 1e5+5;
const int MAXM = 2e5+5;
const int INF = 0x3f3f3f3f;
int tot_E,head[MAXN],fa[MAXN],f[MAXN],dep[MAXN];
int find(int x)
{
	return f[x]==x?x:f[x]=find(f[x]);
}
struct E
{
    int to,w,pre;
}e[MAXM<<1];
void add(int u,int v,int w)
{
    e[++tot_E]=E{v,w,head[u]};
    head[u]=tot_E;
}
int dis[MAXN],n,m,ans[MAXN];
bool vis[MAXN];
struct node
{
    int p,dis;
    bool operator < (const node &x)const
    {
        return dis>x.dis;
    }
};
struct Edge
{
    int u,v,w;
    bool operator < (const Edge &x)const
    {
    	return dis[u]+dis[v]+w<(dis[x.u]+dis[x.v]+x.w);
	}
}edge[MAXM<<1];
void dij()
{
    priority_queue <node> q;
    q.push(node{1,0});
    memset(dis,0x3f,sizeof dis);
    dis[1]=0;
    while(!q.empty())
    {
        int p=q.top().p,dism=q.top().dis;
        q.pop();
        if(vis[p]) continue;
        vis[p]=1;
        for(int i=head[p];i;i=e[i].pre)
        {
            int to=e[i].to,w=e[i].w;
            if(dis[to]>dism+w)
            {
                dis[to]=dism+w;
                q.push(node{to,dis[to]});
            }
        }
    }
}
void dfs(int cur ,int father)
{
	fa[cur]=father;dep[cur]=dep[father]+1;
	for(int i=head[cur];i;i=e[i].pre)
	{
		int to=e[i].to,w=e[i].w;
		if(to==father||dis[cur]+w!=dis[to]) continue;
		dfs(to,cur);
	}
}
int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1;i<=m;++i)
    {
        int a,b,t;
        scanf("%d %d %d",&a,&b,&t);
        add(a,b,t);add(b,a,t);
        edge[i].u=a,edge[i].v=b,edge[i].w=t;
    }
    memset(ans,0x3f,sizeof ans);ans[1]=0;
    dij();
    dfs(1,0);
	sort(edge+1,edge+1+m);
	for(int i=1;i<=n;++i) f[i]=i;
	for(int i=1;i<=m;++i)
	{
		int u=edge[i].u,v=edge[i].v,w=edge[i].w;
		if(dis[u]+w==dis[v]||dis[v]+w==dis[u]) continue;
		int x=find(u),y=find(v);
		while(x!=y)
		{
			if(dep[x]<dep[y]) swap(x,y);
			ans[x]=dis[u]+dis[v]+w-dis[x];
			f[x]=fa[x];
			x=find(x);
		}
	}
    for(int i=2;i<=n;++i)
    	printf("%d\n",ans[i]==INF?-1:ans[i]);
    return 0;
}
```

总结：最短路径树，普及组的知识点我居然第一次听到，还是见识狭小了 。以及在别的博客看到一句话还是比较有用的：**如果题目给出最短路径唯一，那么十有八九与最短路径树有关。**



---

## 作者：XuYueming (赞：3)

## UPDATE on 2024.5.10

删去左偏树代码中令人误解的 `fa` 数组。

## 前话

貌似别人都是使用并查集维护的方法，然而由于排序、最短路等算法瓶颈，以下令 $n$ 和 $m$ 同阶，总的时间复杂度依然是 $\Theta(n \log n)$ 的，那么并查集是否有点大材小用了。事实上，在建完最短路径树后，我给出了两种带 $\log$ 的数据结构完成此题。

## 题目分析

翻译里已经把问题抽象出来了，这里不过多赘述。考虑到从 $1$ 到任意结点的最短路是唯一的，说明将所有最短路径保留，删去其它边，一定能形成一棵树，这棵树就是最短路径树。我们称保留下来的边为树边，删去的边为非树边。

题目要求不经过原来最短路上最后一条边的最短路，也就是删去 $u$ 和 $fa[u]$ 之间的树边后，通过剩余的树边非树边到达 $u$ 的最短路。很容易想到，必然要经过一条非树边，而且最多只经过一条非树边。前者考虑连通性证明显然，后者有如下证明：

> 证明：  
> 假设删去 $u$ 和 $fa[u]$ 之间的树边后，经过了两条非树边得到最短路径是 $1 \stackrel{\color{blue}{\texttt{树边}}}{\color{blue}{\longrightarrow}} xym \stackrel{\color{red}{\texttt{非树边}}}{\color{red}{\longrightarrow}} xym' \stackrel{\color{blue}{\texttt{树边}}}{\color{blue}{\longrightarrow}} yzh \stackrel{\color{red}{\texttt{非树边}}}{\color{red}{\longrightarrow}} yzh' \stackrel{\color{blue}{\texttt{树边}}}{\color{blue}{\longrightarrow}} u$，那么根据最短路径树的相关性质，有路径 $1 \stackrel{\color{blue}{\texttt{树边}}}{\color{blue}{\longrightarrow}} yzh \stackrel{\color{red}{\texttt{非树边}}}{\color{red}{\longrightarrow}} yzh' \stackrel{\color{blue}{\texttt{树边}}}{\color{blue}{\longrightarrow}} u$ 比以上路径更短，原假设不成立，经过多条非树边情况同理。证毕。

考虑走的过程，容易知道 $yzh$ 不能是 $u$ 子树里的节点，因为如果是的话，走到 $yzh$ 的时候就经过了 $fa[u] \rightarrow u$ 这条边，与题意不符。另外，$yzh'$ 是 $u$ 子树里的结点（当然 $u$ 也属于 $u$ 的子树里），这样才能一路向上走走到 $u$。放张图吧。

![](https://cdn.luogu.com.cn/upload/image_hosting/y4bkba12.png)

记 $d_u$ 为 $u$ 的最短路长度，即 $1 \rightarrow u$ 这条路径的距离，记 $\operatorname{dist}(u, v)$ 为 $u$ 经过一条非树边走到 $v$ 的长度。

所以先跑一遍最短路建出最短路径树。考虑第一遍深搜，枚举 $yzh$ 连出的所有非树边 $yzh \rightarrow yzh'$，在 $yzh'$ 上打上一个标记 $d_{yzh} + \operatorname{dist}(yzh, yzh')$，这样在第二遍深搜的时候，就可以把子树的标记不断向上传递、合并，把子树的所有标记加上到父节点的距离，再和父节点合并，就是模拟 $yzh'$ 到 $u$ 的过程。然后得到答案的时候就是取出标记里最小的那个就行了。但是发现这样存在一个问题，就是不能保证不会出现上文提到的 $yzh$ 不能是 $u$ 子树里的节点这个要求，也就是在不断向上传递的时候，有可能传递到了 $yzh$ 甚至 $yzh$ 的祖先，这显然会造成问题。解决方法就是将标记增加一个信息变为 $(d_{yzh} + \operatorname{dist}(yzh, yzh'), yzh)$，这样每次取出当前最小值时，发现 $yzh$ 不满足要求，就将这个标记删除。判断合法可以在第一遍深搜时处理出 dfs 序判断。这个过程套路化地有以下两种方法解决。

### 1. 左偏树 + 懒惰标记

合并、整体加、删除最小值、获取最小值，明显是可合并堆的范畴啊，这里使用左偏树解决。顺带一提，由于有整体加这个操作，不好使用启发式合并，~~所以老老实实写左偏树吧~~。

### 2. 线段树

~~什么？你竟然不会使用左偏树，那就快乐地打线段树吧！~~

为什么要合并？我们只用知道整个子树的信息啊，所以可以在另外记一个信息的 dfs 序，然后树上问题有变成序列上的问题了，区间加、求最小值，使用线段树维护，删除的时候将其赋成 $\infty$ 就能不会对之后产生影响。注意区分两个 dfs 序的区别。

## 代码（已略去快读快写，码风清新，注释详尽）

### 1. 左偏树 + 懒惰标记

```cpp
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx", "sse2", "sse3", "sse4", "mmx")
#include <iostream>
#include <cstdio>
#define debug(a) cerr << "Line: " << __LINE__ << " " << #a << endl
#define print(a) cerr << #a << "=" << (a) << endl
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)
#define main Main(); signed main(){ return ios::sync_with_stdio(0), cin.tie(0), Main(); } signed Main
using namespace std;
 
#include <cstring>
#include <queue>
 
int n, m;
int ans[100010];
 
struct Graph{
	struct node{
		int to, len, nxt;
	} edge[200010 << 1];
	int eid, head[100010];
	inline void add(int u, int v, int w){
		edge[++eid] = {v, w, head[u]};
		head[u] = eid;
	}
	node & operator [] (const int x){
		return edge[x];
	}
} xym, yzh;
// 一个是原图，一个是最短路径树
 
// 最短路，父亲，和父亲的距离
int dist[100010], fr[100010], lenfa[100010];
template <class T> using MinHeap = priority_queue<T, vector<T>, greater<T> >;
 
// dfs 序判断子树
int L[100010], R[100010], timer;
 
int root[100010];  // u 在左偏树里的结点
int dis[400010], lson[400010], rson[400010];  // 左偏树
int lazy[400010];  // 左偏树懒惰标记
pair<int, int> val[400010];  // 信息
int pcnt;
 
int NewNode(pair<int, int> v){
	return val[++pcnt] = v, pcnt;
}
 
void pushtag(int u, int tag){
	val[u].first += tag;
	lazy[u] += tag;
}
 
void pushdown(int u){
	if (lazy[u] == 0) return;
	if (lson[u]) pushtag(lson[u], lazy[u]);
	if (rson[u]) pushtag(rson[u], lazy[u]);
	lazy[u] = 0;
}
 
int combine(int a, int b){
	if (!a || !b) return a | b;
	if (val[a] > val[b]) swap(a, b);
	pushdown(a), rson[a] = combine(rson[a], b);
	if (dis[lson[a]] < dis[rson[a]]) swap(lson[a], rson[a]);
	dis[a] = dis[rson[a]] + 1;
	return a;
}
 
// 第一遍 dfs
void dfs(int now){
	L[now] = ++timer;  // 记录 dfs 序
	for (int i = xym.head[now]; i; i = xym[i].nxt){  // 枚举 yzh -> yzh' 这条非树边
		int to = xym[i].to, len = xym[i].len;
		if (fr[to] == now && len == lenfa[to]) continue;  // 这里要很小心地判断树边
		int node = NewNode({dist[now] + len, now});
		if (!root[to]) root[to] = node;
		else root[to] = combine(root[to], node);
	}
	for (int i = yzh.head[now]; i; i = yzh[i].nxt) dfs(yzh[i].to);
	R[now] = timer;
}
 
// 第二遍 dfs
void redfs(int now){
	for (int i = yzh.head[now]; i; i = yzh[i].nxt){  // 把子树标记合并过来
		int to = yzh[i].to, len = yzh[i].len;
		redfs(to);
		if (!root[to]) continue;
		pushtag(root[to], len);
		if (!root[now]) root[now] = root[to];
		else root[now] = combine(root[now], root[to]);
	}
	// 弹出不符合的标记
	while (root[now] && L[now] <= L[val[root[now]].second] && L[val[root[now]].second] <= R[now]){
		if (lson[root[now]] == 0 && rson[root[now]] == 0){
			root[now] = 0;
		} else {
			root[now] = combine(lson[root[now]], rson[root[now]]);
		}
	}
	// 统计答案
	if (root[now]) ans[now] = val[root[now]].first;
	else ans[now] = -1;
}
 
// 迪迦哥斯拉算法（逃
// 迪杰斯特拉求最短路，并建出最短路径树
void build(){
	memset(dist, 0x3f, sizeof dist);
	MinHeap<pair<int, int> > Q; Q.push({dist[1] = 0, 1});
	while (!Q.empty()){
		auto [ndis, now] = Q.top(); Q.pop();
		if (dist[now] < ndis) continue;
		for (int i = xym.head[now]; i; i = xym[i].nxt){
			int to = xym[i].to, len = xym[i].len;
			if (dist[to] > dist[now] + len){
				Q.push({dist[to] = dist[now] + len, to});
				fr[to] = now, lenfa[to] = len;
			}
		}
	}
	for (int i = 2; i <= n; ++i) yzh.add(fr[i], i, lenfa[i]);
}
 
signed main(){
	read(n, m);
	for (int i = 1, u, v, w; i <= m; ++i) read(u, v, w), xym.add(u, v, w), xym.add(v, u, w);
	build(), dfs(1), redfs(1);
	for (int i = 2; i <= n; ++i) write(ans[i], '\n');
	return 0;
}
```

### 2. 线段树

```cpp
//#pragma GCC optimize(3)
//#pragma GCC optimize("Ofast", "inline", "-ffast-math")
//#pragma GCC target("avx", "sse2", "sse3", "sse4", "mmx")
#include <iostream>
#include <cstdio>
#define debug(a) cerr << "Line: " << __LINE__ << " " << #a << endl
#define print(a) cerr << #a << "=" << (a) << endl
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)
#define main Main(); signed main(){ return ios::sync_with_stdio(0), cin.tie(0), Main(); } signed Main
using namespace std;

#include <cstring>
#include <queue>
#include <vector>

const int inf = 0x3f3f3f3f;

int n, m;
int ans[100010];

struct Graph{
	struct node{
		int to, len, nxt;
	} edge[200010 << 1];
	int eid, head[100010];
	inline void add(int u, int v, int w){
		edge[++eid] = {v, w, head[u]};
		head[u] = eid;
	}
	node & operator [] (const int x){
		return edge[x];
	}
} xym, yzh;
// 一个是原图，一个是最短路径树

// 最短路，父亲，和父亲的距离
int dist[100010], fr[100010], lenfa[100010];
template <class T> using MinHeap = priority_queue<T, vector<T>, greater<T> >;

// dfs 序判断子树
int L[100010], R[100010], timer;

// 信息的 dfs 序
int infoL[100010], infoR[100010], infot;
vector<pair<int, int> > info[100010];
pair<int, int> val[400010];  // 注意这里要开大一些

struct Segment_Tree{
	#define lson (idx << 1    )
	#define rson (idx << 1 | 1)
	
	struct Info{
		pair<int, int> val;
		int pos;
		Info operator + (const Info & o) const {
			if (val.first == inf) return o;
			if (o.val.first == inf) return *this;
			if (val.first < o.val.first) return *this;
			return o;
		}
		Info operator + (const int o) const {
			if (val.first == inf) return *this;
			return {{val.first + o, val.second}, pos};
		}
	};
	// 信息
	
	struct node{
		int l, r;
		Info info;
		int tag;
	} tree[400010 << 2];
	
	void pushup(int idx){
		tree[idx].info = tree[lson].info + tree[rson].info;
	}
	
	void build(int idx, int l, int r){
		tree[idx] = {l, r, {{inf, -1}, -1}, 0};
		if (l == r) return tree[idx].info = {val[l], l}, void();
		int mid = (l + r) >> 1;
		build(lson, l, mid), build(rson, mid + 1, r), pushup(idx);
	}
	
	void pushtag(int idx, const int t){
		tree[idx].info = tree[idx].info + t;
		tree[idx].tag = tree[idx].tag + t;
	}
	
	void pushdown(int idx){
		if (!tree[idx].tag) return;
		pushtag(lson, tree[idx].tag), pushtag(rson, tree[idx].tag);
		tree[idx].tag = 0;
	}
	
	Info query(int idx, int l, int r){
		if (tree[idx].l > r || tree[idx].r < l) return {{inf, -1}, -1};
		if (l <= tree[idx].l && tree[idx].r <= r) return tree[idx].info;
		return pushdown(idx), query(lson, l, r) + query(rson, l, r);
	}
	
	void modify(int idx, int l, int r, const int t){
		if (tree[idx].l > r || tree[idx].r < l) return;
		if (l <= tree[idx].l && tree[idx].r <= r) return pushtag(idx, t);
		pushdown(idx), modify(lson, l, r, t), modify(rson, l, r, t), pushup(idx);
	}
	
	void erase(int idx, int p){
		if (tree[idx].l > p || tree[idx].r < p) return;
		if (tree[idx].l == tree[idx].r) return tree[idx].info = {{inf, -1}, -1}, void();
		pushdown(idx), erase(lson, p), erase(rson, p), pushup(idx);
	}
	
	#undef lson
	#undef rson
} tree;

// 第一遍 dfs
void dfs(int now){
	L[now] = ++timer;  // 记录 dfs 序
	for (int i = xym.head[now]; i; i = xym[i].nxt){  // 枚举 yzh -> yzh' 这条非树边
		int to = xym[i].to, len = xym[i].len;
		if (fr[to] == now && len == lenfa[to]) continue;  // 这里要很小心地判断树边
		info[to].push_back({dist[now] + len, now});
	}
	for (int i = yzh.head[now]; i; i = yzh[i].nxt) dfs(yzh[i].to);
	R[now] = timer;
}

// 其实也算一次深搜，记录标记的 dfs 序
void prework(int now){
	infoL[now] = infot + 1;
	for (auto x: info[now]) val[++infot] = x;
	for (int i = yzh.head[now]; i; i = yzh[i].nxt) prework(yzh[i].to);
	infoR[now] = infot;
}

// 第二遍 dfs
void redfs(int now){
	if (infoL[now] > infoR[now]) return;
	for (int i = yzh.head[now]; i; i = yzh[i].nxt){  // 把子树标记合并过来
		int to = yzh[i].to, len = yzh[i].len;
		redfs(to), tree.modify(1, infoL[to], infoR[to], len);
	}
	// 弹出不符合的标记
	while (true){
		Segment_Tree::Info res = tree.query(1, infoL[now], infoR[now]);
		if (res.val.first == inf || res.pos == -1) break;
		if (L[now] <= L[res.val.second] && L[res.val.second] <= R[now]){
			tree.erase(1, res.pos);
			continue;
		}
		// 统计答案
		ans[now] = res.val.first;
		break;
	}
}

// 迪迦哥斯拉算法（逃
// 迪杰斯特拉求最短路，并建出最短路径树
void build(){
	memset(dist, 0x3f, sizeof dist);
	MinHeap<pair<int, int> > Q; Q.push({dist[1] = 0, 1});
	while (!Q.empty()){
		auto [ndis, now] = Q.top(); Q.pop();
		if (dist[now] < ndis) continue;
		for (int i = xym.head[now]; i; i = xym[i].nxt){
			int to = xym[i].to, len = xym[i].len;
			if (dist[to] > dist[now] + len){
				Q.push({dist[to] = dist[now] + len, to});
				fr[to] = now, lenfa[to] = len;
			}
		}
	}
	for (int i = 2; i <= n; ++i) yzh.add(fr[i], i, lenfa[i]);
}

signed main(){
	read(n, m);
	for (int i = 1, u, v, w; i <= m; ++i) read(u, v, w), xym.add(u, v, w), xym.add(v, u, w);
	for (int i = 2; i <= n; ++i) ans[i] = -1;
	build(), dfs(1), prework(1), tree.build(1, 1, infot), redfs(1);
	for (int i = 2; i <= n; ++i) write(ans[i], '\n');
	return 0;
}
```

## 总结 & 后话

考场上没想到可以将长度拆开来算，也就是计算答案的时候不用一步一步加与父亲的长度加上去，而是用 $d_{yzh'} - d_u$ 计算，这样对于 $u$ 来说，$d_u$ 是确定的，要求的就是 $\min \lbrace d_{yzh} + \operatorname{dist}(yzh, yzh') + d_{yzh'} \rbrace$，这样可以愉快地用启发式合并秒了啊！但是练习一道左偏树懒惰标记的题目，感觉也颇有收获呢。~~但是但是，线段树无敌爱敲~~。

---

## 作者：小塘空明 (赞：3)

首先一边dijkstra求出最短路树。

关于每个节点x，题目会断掉它在最短路上与父节点相连的那条边。

断掉这条边后，树会裂成两颗，分别视为S、T，其中x是T的根节点。

关于每个x，它一定由一条非树边更新而来。假设非树边一端为u，另一端为v，边长为z，v在T中，那么这时x的次短路的一个候补答案为dis[u]+dis[v]+z-dis[x].

我们发现，关于每条非树边和每个点，dis[u]+dis[v]+z、dis[x]都为不变的量。所以我们将非树边按照dis[u]+dis[v]+z从小到大排序，那么第一次更新到x节点时的答案就是最优答案。

关于每条非树边u、v，我们执行一个类似于跳lca的过程，在合并的过程中更新答案。因为第一次求出的解就是最优解，我们将所有求出答案的点合并到lca(u,v)。

注意lca(u,v)不能被更新，因为这时候已经不处于两颗不同的树中。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<string>
#include<queue>
using namespace std;
typedef long long ll;
const int size=2e5+10;
struct node{int x,y,z;}c[size];
int n,m,tot,cnt,w,x[size],y[size],z[size],fa[size],d[size],dis[size],vis[size],ans[size];
int head[size],ver[size*2],next[size*2],edge[size*2];
priority_queue<pair<int,int> >q;
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+ch-'0';ch=getchar();}
	return x*f;
}
inline bool operator<(const node&a,const node&b){
	return a.z<b.z;
}
inline void add(int px,int py,int pz){
	ver[++tot]=py;edge[tot]=pz;next[tot]=head[px];head[px]=tot;
}
inline int get(int px,int py){
	if(px==py) return px;
	if(d[px]<d[py]) swap(px,py);
	if(!ans[px]) ans[px]=w-dis[px];
	return get(fa[px],py);
}
inline void dijkstra(){
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;q.push(make_pair(0,1));
	while(q.size()){
		int px=q.top().second;q.pop();
		if(vis[px]) continue;
		vis[px]=1;
		for(int i=head[px];i;i=next[i]){
			int py=ver[i],pz=edge[i];
			if(dis[py]>dis[px]+pz){
				fa[py]=px;dis[py]=dis[px]+pz;
				if(!vis[py]) q.push(make_pair(-dis[py],py));
			}
		}
	}
}
inline int solve(int px){
	if(d[px]) return d[px];
	return d[px]=solve(fa[px])+1;
}
int main(){
	n=read();m=read();fa[1]=1;
	for(int i=1;i<=m;i++){
		x[i]=read();y[i]=read();z[i]=read();
		add(x[i],y[i],z[i]);add(y[i],x[i],z[i]);
	}
	dijkstra();d[1]=1;
	for(int i=2;i<=n;i++) d[i]=solve(i);
	for(int i=1;i<=m;i++){
		int px=x[i],py=y[i],pz=z[i];
		if(dis[px]>dis[py]) swap(px,py);
		if(dis[px]+pz==dis[py]) continue;
		c[++cnt]=(node){px,py,dis[px]+dis[py]+pz};
	}
	sort(c+1,c+1+cnt);
	for(int i=1;i<=cnt;i++){
		int px=c[i].x,py=c[i].y;
		w=c[i].z;get(px,py);
	}
	for(int i=2;i<=n;i++){
		if(!ans[i]) printf("-1\n");
		else printf("%d\n",ans[i]);
	}
	return 0;
}
```


---

## 作者：ccxswl (赞：2)

一个用平衡树，不用脑子的写法。（目前没有用平衡树的诶。）

---
## 题意

不经过最短路的最后一条边的最短路，保证最短路唯一。

## 思路

看到最短路唯一容易想到建出的最短路 DAG 其实是最短路树（以 $1$ 为根）。

那题意转化为求每个节点不经过与父亲的连边，所能到根节点的最短路。

容易发现每个点的答案都是被子树内的点与子树外的点的连边贡献的，称这些边为关键边。

记节点 $u,v$ 之间边的边权是 $w(u,v)$。节点 $u$ 到 $1$ 的最短路为 $dis_u$。

比如：

![](https://cdn.luogu.com.cn/upload/image_hosting/h9ngbu0v.png)

节点 $2$ 的答案是 $\min(w(2,4)+w(4,7)+dis_7,w(2,5)+w(5,6)+dis_6)$。红边为关键边。

在最短路树中 dfs 求解。

用平衡树来维护关键边的信息。

具体的，维护经过这条边的到当前节点的路径长度，以及这条边连接的子树外的节点的 dfn 序。

平衡树内的点按记录的 dfn 序有序排列。

子节点的信息合并到当前节点，暴力合并即可，具体可以看[这个](https://www.luogu.com.cn/article/p4ejw9j6)，[这个](https://codeforces.com/blog/entry/108601)。

但要注意多了一条边，需要给这颗子树内所有路径的长度加上这条边的权值。

还需要解决一个问题，当我们计算节点 $8$ 的答案时，那两条关键边失效了，需要删除。这时刚才记录的这些边连接的点的 dfn 序就有用了。这些边的终点都是当前子树内的点（起点不用说，所有边的起点都在子树内），根据这个直接删除即可。

平衡树实现了全局最小值，全局加，带交合并。

复杂度的瓶颈在于平衡树的带交合并。

## 代码
```cpp
#include <bits/stdc++.h>

using namespace std;

int read() {
  int s = 0, w = 1;
  char c = getchar();
  while (!isdigit(c)) {
    w = c == '-' ? -w : w;
    c = getchar();
  }
  while (isdigit(c)) {
    s = s * 10 + c - 48;
    c = getchar();
  }
  return s * w;
}

const int inf = 1e9;
const int maxN = 1e5 + 7;

int n, m;

int head[maxN], tot;
struct edge {
  int to, ls, w;
} e[maxN * 4];
void add(int u, int v, int w) {
  e[++tot] = {v, head[u], w};
  head[u] = tot;
}

int dis[maxN], pre[maxN], prw[maxN];
bool vis[maxN];
using pii = pair<int, int>;
void dij() {
  fill(dis + 1, dis + n + 1, inf);
  dis[1] = 0;
  priority_queue<pii, vector<pii>, greater<pii>> Q;
  Q.emplace(0, 1);
  while (!Q.empty()) {
    int f = Q.top().second;
    Q.pop();
    if (vis[f]) continue;
    vis[f] = true;
    for (int i = head[f]; i; i = e[i].ls) {
      int to = e[i].to, w = e[i].w;
      if (dis[to] > dis[f] + w) {
        pre[to] = f, prw[to] = w;
        dis[to] = dis[f] + w;
        Q.emplace(dis[to], to);
      }
    }
  }
}

struct wei {
  int to, w;
  wei(int to, int w) : to(to), w(w) {}
  friend bool operator < (wei A, wei B) {
    return A.to < B.to;
  }
};
vector<wei> E[maxN];

int dfn[maxN], cnt, siz[maxN];
void initdfs(int x) {
  dfn[x] = ++cnt;
  siz[x] = 1;
  for (auto [to, w] : E[x])
    initdfs(to), siz[x] += siz[to];
}

mt19937 rd(5222568);
int nwn, root[maxN];
struct tree {
  int l, r;
  int to, w;
  int key;
  int siz;
  int mn;
  int tg;
} t[maxN * 4];
int New(int to, int v) {
  int p = ++nwn;
  t[p].l = t[p].r = t[p].tg = 0;
  t[p].siz = 1;
  t[p].to = to;
  t[p].mn = t[p].w = v;
  t[p].key = rd();
  return p;
}
void upd(int p) {
  t[p].siz = t[t[p].l].siz + t[t[p].r].siz + 1;
  t[p].mn = min({t[t[p].l].mn, t[t[p].r].mn, t[p].w});
}
void make(int p, int v) {
  if (!p) return;
  t[p].mn += v;
  t[p].w += v;
  t[p].tg += v;
}
void down(int p) {
  if (!t[p].tg) return;
  make(t[p].l, t[p].tg);
  make(t[p].r, t[p].tg);
  t[p].tg = 0;
}
int merge(int x, int y) {
  if (!x || !y) return x | y;
  if (t[x].key <= t[y].key) {
    down(x);
    t[x].r = merge(t[x].r, y);
    upd(x);
    return x;
  } else {
    down(y);
    t[y].l = merge(x, t[y].l);
    upd(y);
    return y;
  }
}
void split(int p, int k, int &x, int &y) {
  if (!p) x = y = 0;
  else {
    down(p);
    if (t[p].to <= k)
      x = p, split(t[p].r, k, t[x].r, y);
    else
      y = p, split(t[p].l, k, x, t[y].l);
    upd(p);
  }
}
int M(int x, int y) {
  if (!x || !y) return x | y;
  if (t[x].key > t[y].key) swap(x, y);
  int L, R;
  down(x), down(y);
  split(y, t[x].to, L, R);
  t[x].l = M(t[x].l, L);
  t[x].r = M(t[x].r, R);
  upd(x);
  return x;
}
void insert(int &p, int to, int v) {
  int L, R;
  split(p, to, L, R);
  p = merge(merge(L, New(to, v)), R);
}
void del(int &p, int x) {
  int L, M, R;
  split(p, dfn[x] + siz[x] - 1, L, R);
  split(L, dfn[x] - 1, L, M);
  p = merge(L, R);
}

int ans[maxN];
void dfs(int x) {
  for (auto [to, w] : E[x]) {
    dfs(to);
    make(root[to], w);
    root[x] = M(root[x], root[to]);
  }
  for (int i = head[x]; i; i = e[i].ls) {
    int to = e[i].to, w = e[i].w;

    if (dfn[x] <= dfn[to] && dfn[to] <= dfn[x] + siz[x] - 1)
      continue;
    if (to == pre[x] && w == prw[x]) continue;

    insert(root[x], dfn[to], w + dis[to]);
  }
  del(root[x], x);

  ans[x] = root[x] ? t[root[x]].mn : -1;
}

signed main() {
//  freopen("in.in", "r", stdin);
//  ofstream cout("out.out");

  t[0].mn = inf;

  n = read(), m = read();
  for (int i = 1; i <= m; i++) {
    int u = read(), v = read(), w = read();
    add(u, v, w), add(v, u, w);
  }
  dij();

  for (int i = 1; i <= n; i++)
    if (pre[i])
      E[pre[i]].emplace_back(i, prw[i]);

  initdfs(1);

  dfs(1);

  for (int i = 2; i <= n; i++)
    cout << ans[i] << '\n';
}
```

---

## 作者：tanghg (赞：2)

# 题目大意
给定一张有 $n$ 个节点，$m$ 条边的无向图，对于任意的 $i$（$2\le i\le n$），请求出在不经过原来 $1$ 节点到 $i$ 节点最短路上最后一条边的前提下，$1$ 节点到 $i$ 节点的最短路。满足每一个点只对应**一条**最短路。
$n\leq 10^5,m\leq 2\times 10^5$
# 思路
考虑对于这个图现求出最短路，之后建一个最短路树。不妨设这棵树上节点 $u$ 的父亲为 $f_u$，$1$ 到 $u$ 的最短路长度为 $d_i$。则对于本题我们要求的是在树上删掉 $f_u$ 到 $u$ 这条边后通过树外的一条边获得的最小最短路。

之后我们设选择一条树外的边 $(x,y)$，。其中因为 $u$ 到不了 $f_u$，即到不了 $1$。所以我们只能从 $u$ 的子树走到不在 $u$ 的子树内的另一个点。不妨设 $y$ 在子树内，$x$ 在子树外。所以我们要选择一对 $(x,y)$ 使得 $d_x+d_y+w_{(x,y)}-d_u$ 最小，其中 $w_{(x,y)}$ 表示 $(x,y)$ 这条边的边权。这个式子简单画一画就能看懂。

所以不妨将所有树外的边按照上面的式子从小到大排序，这样每一次更新后的元素就不用再更新了。所以我们用并查集去维护树上每一个节点是否遍历过，然后就可以快速跳过。这样每一个节点最多被更新一次。

之后我们考虑每条树外的边 $(x,y)$ 能更新哪些节点。因为 $y$ 在子树内，$x$ 在子树外，所以我们能更新到 $x,y$ 的最近公共祖先，且**不能更新这个最近公共祖先**，因为从这个节点（包括它）以后的所有节点被更新时 $x,y$ 都在同一个子树内了，不符合题意。

之后就做完了。
# 代码
```cpp
#include <bits/stdc++.h>
#define endl "\n"
using namespace std;
typedef long long ll;
const ll MAXN=1e6+5;
ll dis[MAXN];
struct edge{
    ll id,u,v,w;
    bool operator<(const edge&K)const{
        return dis[u]+dis[v]+w<dis[K.u]+dis[K.v]+K.w;
    }
};
vector<edge>adj[MAXN],e,E;
bool vis[MAXN];
ll fe[MAXN];
void dijkstra(){
    memset(dis,0x3f,sizeof(dis));
    priority_queue<pair<ll,ll>,vector<pair<ll,ll>>,greater<>>q;
    dis[1]=0;
    q.push({0,1});
    while(!q.empty()){
        ll u=q.top().second;
        q.pop();
        if(vis[u]){
            continue;
        }
        vis[u]=true;
        for(auto i:adj[u]){
            ll v=i.v,w=i.w;
            if(dis[v]>dis[u]+w){
                fe[v]=i.id;
                dis[v]=dis[u]+w;
                q.push({dis[v],v});
            }
        }
    }
}
ll n,m;
ll fa[MAXN],dep[MAXN];
void dfs(ll u){
    for(auto i:adj[u]){
        ll v=i.v;
        if(v==fa[u]){
            continue;
        }
        fa[v]=u;
        dep[v]=dep[u]+1;
        dfs(v);
    }
}
ll f[MAXN];
ll find(ll u){
    return u==f[u]?u:f[u]=find(f[u]);
}
ll ans[MAXN];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin>>n>>m;
    for(int i=0;i<m;++i){
        ll u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({i,u,v,w});
        adj[v].push_back({i,v,u,w});
        e.push_back({i,u,v,w});
    }
    dijkstra();
    for(int i=1;i<=n;++i){
        adj[i].clear();
        f[i]=i;
        ans[i]=-1;
    }
    memset(vis,false,sizeof(vis));
    for(int i=2;i<=n;++i){
        ll u=e[fe[i]].u,v=e[fe[i]].v,w=e[fe[i]].w;
        adj[u].push_back({i,u,v,w});
        adj[v].push_back({i,v,u,w});
        vis[fe[i]]=true;
    }
    for(int i=0;i<m;++i){
        if(!vis[i]){
            E.push_back(e[i]);
        }
    }
    dfs(1);
    sort(E.begin(),E.end());
    for(auto ee:E){
        ll u=ee.u,v=ee.v,w=ee.w,val=dis[u]+dis[v]+w;
        u=find(u);
        v=find(v);
        while(u!=v){
            if(dep[u]<dep[v]){
                swap(u,v);
            }
            ans[u]=val-dis[u];
            f[u]=fa[u];
            u=find(u);
        }
    }
    for(int i=2;i<=n;++i){
        cout<<ans[i]<<endl;
    }
    return 0;
}
```

---

## 作者：under_the_time (赞：2)

## 题意

> 给定一张 $n$ 个点 $m$ 条边的无向图，对于每个除 $1$ 以外的点 $u$，求在不允许经过原来从 $1$ 到 $u$ 的最短路径的最后一条边时，$1$ 到 $u$ 的最短路。
>
> 保证 $1$ 到其他点的最短路唯一，无解输出 `-1`。

## 解法

如果每次暴力删边后再跑一次最短路复杂度显然不行。题目中给了最短路唯一的条件，可以建出**最短路径树**，把每条从 $1$ 到其他所有点的最短路径上的边拎出来单独建一棵树。

对于一条最短路径上的最后一条边 $(u,v)$（$u$ 为 $v$ 的祖先），我们删去它后会导致树上 $1$ 与 $v$ 不连通（最短路径唯一），意味着需要走至少一条非树边。

推理可知：新的最短路**只会经过一条**非树边。假设需要经过两条及以上的非树边，那么总是有至少一条非树边可以用几条树边拼起来（否则这条非树边就应当是树边）。可以脑补一下走多条非树边的情况，一定存在一个更优的只走一条非树边的路径。

所以，从 $1$ 到 $v$ 的新最短路径可以用一条非树边连接两条树上路径组成。不妨枚举每一条非树边对新最短路径的贡献。

对于一条非树边 $(u,v)$，记 $u,v$ 的最近公共祖先为 $lca$，如果将其加进最短路树中，则会产生一个环，环上的点为 $u\to lca$ 和 $v\to lca$ 两条链上的点。那么 $(u,v)$ 可能可以更新的点即为**这个环上除了 $lca$ 的其他点**（对 $u$ 和 $v$ 也能够产生贡献）。

- 如果一个点 $x$ 在这个环上，且不是 $lca$，那么断开它和其父亲的这条边后，就可以以另一个方向绕这个环（比如说一开始要从 $lca$ 往 $u$ 的方向走，那么这次就往 $v$ 的方向走，然后再走 $(u,v)$ 这条边，从 $u$ 往上爬爬到 $x$），途中只会经过 $(u,v)$ 这一条非树边。
- 如果一个点 $x$ 是 $lca$ 及其祖先，那么断开这么一条边后从 $1$ 甚至无法到达这个环，再多花一条非树边走到环上不如另找一个非树边，走另一个环，回到第一种情况。
- 如果一个点 $x$ 是 $u$ 或 $v$ 的后代，那么断开这条边后也无法到达环上，与情况二相同，不如另找一个环。

此时，如果点 $x$ 满足条件并打算走 $(u,v)$ 这条边，设 $1\to a$ 的最短路（即树上路径长度）为 $dis_a$，则新的 $1\to x$ 的路径长度为 $dis_u+w(u,v)+dis_v-dis_i$，其中 $w(u,v)$ 为 $(u,v)$ 的边权。建议看图理解。

![](https://cdn.luogu.com.cn/upload/image_hosting/q3actpz6.png)

- 把 $u$ 和 $v$​ 的位置反过来是同理的。

$dis_i$ 是不变的，所以我们把每条边按照 $dis_u+w(u,v)+dis_v$ 从小到大进行排序，每次遍历一遍环上没有被确定答案的点并更新答案，这样可以保证每个点被最优的非树边计算答案，不会重复计算。

## 实现

用 `Dijkstra` 算出最短路，根据松弛操作 $dis_v\gets\min(dis_v,dis_u+w(u,v))$，只需在算法结束后遍历每条边 $(u,v)$，判断 $dis_v$ 是否与 $dis_u+w(u,v)$ 相等，如果是则说明有一条最短路经过了 $(u,v)$，$(u,v)$ 即为最短路树树边。

跳过已经确定答案的点考虑使用并查集缩点。在环上的点的答案被更新以后，我们把它们全部归到一个并查集里，根节点为 $lca$ 或者它的祖先。在遍历另一个环时，如果环上某一段被更新完了，则直接用并查集往上跳到环上下一个没被更新过的点。

~~复杂度不太会分析所以就是 O(能过)~~ 因为每个点的答案只会被计算一次，否则会被跳过，复杂度应该就是 $O(m\log m)$​ 的（对非树边进行排序）。

个人认为这个并查集更像是记录每个点最近的没被计算过贡献的祖先，加快了在环上跳的过程；而路径压缩的过程就是把跳的好几下压缩成跳一下就到。

## 代码

```cpp
// Dijkstra构建最短路径树
// 按照dis[u]+w[u][v]+dis[v]排序
// 最后并查集缩点（类似Kruskal）
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn = 2e5 + 5;
struct Edge { 
    int u,v; ll w; int nxt;
    Edge(int a = 0,int b = 0,ll c = 0,int d = 0) { u = a, v = b, w = c, nxt = d; }
} e[maxn << 1];
int head[maxn],cnt,n;
void addEdge(int u,int v,ll w) {
    e[++ cnt] = Edge(u,v,w,head[u]);
    head[u] = cnt;
}
ll dis[maxn]; bool vis[maxn]; int tot;
pair<ll,pair<int,int> > newEdge[maxn << 1];
vector<int> mp[maxn];
void Dijkstra() {
    #define type pair<ll,int>
    priority_queue<type,vector<type>,greater<type> > q;
    for (int i = 2;i <= n;i ++) dis[i] = 2e18;
    q.push({0,1}); dis[1] = 0;
    while (!q.empty()) {
        int u = q.top().second; q.pop();
        if (vis[u]) continue; vis[u] = true;
        for (int i = head[u];i;i = e[i].nxt) {
            int v = e[i].v; ll w = e[i].w;
            if (dis[v] > dis[u] + w) {
                dis[v] = dis[u] + w;
                if (!vis[v]) q.push({dis[v], v});
            }
        }
    }
    // 选出非树边
    for (int i = 1;i <= cnt;i ++) {
        int u = e[i].u, v = e[i].v, w = e[i].w;
        if (dis[v] != dis[u] + w && u <= v)
            newEdge[++ tot] = {dis[u] + dis[v] + w, {u, v}};
        else if (dis[v] == dis[u] + w) mp[u].push_back(v);
    }
    #undef type
}
int dep[maxn],fat[maxn]; // 算深度和每个点的父亲。
void dfs(int u,int fa) {
    dep[u] = dep[fat[u] = fa] + 1;
    for (auto v : mp[u])
        if (v != fa) dfs(v,u);
}
int m,fa[maxn]; ll ans[maxn];
int find(int x) { return x == fa[x] ? x : fa[x] = find(fa[x]); }
int main() {
    scanf("%d%d",&n,&m); ll w;
    for (int i = 1,u,v;i <= m;i ++) {
        scanf("%d%d%lld",&u,&v,&w);
        addEdge(u,v,w); addEdge(v,u,w);
    }
    Dijkstra(); dfs(1,0);
    sort(newEdge + 1,newEdge + tot + 1);
    for (int i = 1;i <= n;i ++)
        ans[i] = -1, fa[i] = i;
    // 算答案
    for (int i = 1;i <= tot;i ++) {
        int u = find(newEdge[i].second.first); // 直接找到一个最近的没被计算过答案的点。
        int v = find(newEdge[i].second.second);
        ll w = newEdge[i].first;
        while (u != v) { // 当u,v相等时说明跳到了lca及以上，不在环上了。
            if (dep[u] < dep[v]) u ^= v, v ^= u, u ^= v; // 每次把u,v中深度较大的点往上挪。
            ans[u] = w - dis[u], fa[u] = fat[u]; // 可以往上跳但还在环上，那么自己被计算过了，下一个没被计算过的点就是fa[fat[u]]。
            u = find(u); // 往上跳，注意有路径压缩。
        }
    }
    for (int i = 2;i <= n;i ++)
        printf("%lld\n",ans[i]);
    return 0;
}
// 记得开long long！
```

---

## 作者：KazamaRuri (赞：1)

题意清晰，不再赘述。

## 分析

根据 $1$ 到每个点的最短路唯一，考虑建出最短路树（以 $1$ 为根）。

发现删掉某个点最短路上的最后一条边，就是在最短路树上删掉这个点和父亲的连边。那么想要到达这个点就必须从其子树内“爬”上来，因为不能走祖先节点下来。

具体的，对于点 $i$ 来说，其子树内点 $u$ 引出到**其他子树**的非树边 $(u,v)$，会有一条路径 $ 1 \rightarrow v \rightarrow u \rightarrow i $，画图理解更佳。那么考虑用可并堆维护，注意在非树边不能对其两端点的公共祖先做贡献。

## 代码


```cpp
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <cstring>
#include <vector>
#include <bitset>
#include <queue>
#include <cmath>
#include <map>
#include <set>
#define lb(x) (x&-x)
#define IT set<node>::iterator
using namespace std;
using ll=long long;
const int N=2e5+5; const ll inf=0x3f3f3f3f3f3f3f3f;
int n,m,cnt,head[N],p[N],rt[N],tot,tim,dfn[N],low[N];
ll dis[N],f[N]; priority_queue<pair<ll,int>>q;
struct node{ int u,v; ll f; };
struct tree{ node x;  int s[2],d; ll tg; }t[N<<2];
inline int create(int u,int v,int w){ t[++tot]={{u,v,dis[v]+w},{0,0},0,0}; return tot; }
inline int& rc(int x){
	return t[x].s[t[t[x].s[0]].d>t[t[x].s[1]].d];
}
void push_down(int x){
	ll &k=t[x].tg; if(!k||!x) return ;
	t[t[x].s[0]].x.f+=k,t[t[x].s[1]].x.f+=k,
	t[t[x].s[0]].tg+=k,t[t[x].s[1]].tg+=k,k=0;
}
int merge(int x,int y){
	push_down(x),push_down(y);
	if(!x||!y) return x|y;
	if(t[x].x.f>t[y].x.f) swap(x,y);
	rc(x)=merge(rc(x),y);
	return t[x].d=t[rc(x)].d+1,x;
}
struct Edge{ int to,next,val; }e[N<<1];
void add_edge(int u,int v,int w){ e[++cnt]={v,head[u],w},head[u]=cnt; }
void add(int u,int v,int w){ add_edge(u,v,w),add_edge(v,u,w); }
inline bool sub(int x,int y){ return dfn[x]<=dfn[y]&&dfn[y]<=low[x]; }
void dfs0(int u){
	dfn[u]=++tim;
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to,w=e[i].val;
		if(dis[v]==dis[u]+w) dfs0(v);
	} low[u]=tim;
}
void dfs1(int u){
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].to,w=e[i].val;
		if(dis[v]==dis[u]+w) dfs1(v),
			t[rt[v]].tg+=w,t[rt[v]].x.f+=w,
			rt[u]=merge(rt[u],rt[v]);
		else if(dis[u]!=dis[v]+w)
			rt[u]=merge(rt[u],create(u,v,w));
	}
	while(rt[u]&&sub(u,t[rt[u]].x.u)&&sub(u,t[rt[u]].x.v))
		push_down(rt[u]),rt[u]=merge(t[rt[u]].s[0],t[rt[u]].s[1]);
	if(rt[u]) push_down(rt[u]),f[u]=t[rt[u]].x.f; else f[u]=inf;
}
int main(){
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,u,v,w;i<=m;i++)
		scanf("%d%d%d",&u,&v,&w),add(u,v,w);
	memset(dis,0x3f,sizeof(dis)),q.push({dis[1]=0,1});
	while(q.size()){
		int u=q.top().second; q.pop();
		if(p[u]) continue; p[u]=1;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].to,w=e[i].val;
			if(dis[v]>dis[u]+w)
				q.push({-(dis[v]=dis[u]+w),v});
		}
	} dfs0(1),dfs1(1);
	for(int i=2;i<=n;i++)
		printf("%lld\n",f[i]==inf?-1ll:f[i]);
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

首先，我们关注到题目说了：

> 特别地，保证 $1$ 到任何一个点 $i$ 的最短路都是唯一的。

所以考虑建立**最短路树**，以 $1$ 为根节点。（补充，若最短路不唯一则建立的是最短路图）

如果把点 $i$ 到它父亲的边断了怎么办？为了到达 $i$，我们需要一条边连接 $i$ 的子树内任意一节点，和子树外任意一节点。

这样思考，似乎很难处理。我们不妨转换角度：

对于任意一条非树边 $(u,v)$，它能给哪些点做贡献呢？

显然，要求 $u,v$ 在不同子树内。于是，这个子树的根必须在 $u,v$ 的路径上（不含 LCA）。

那，对路径上的这些点的贡献是多少呢？

我们思考，假设当前节点为 $k$，本来它应该是 $1 \to k$ 的最短路，现在变成了 $1 \to u \to v \to k$ 了。

树上问题，我们常用的手段是**把路径转化为到 $1$ 的路径**。

于是，$1 \to u \to v \to k=u \to v+u \to 1+v \to 1-k \to 1$。其中，$u,v$ 是当前枚举的非树边边权。

这里推荐画图辅助理解。

我们发现，$k \to 1$ 是定值，而 $u \to v,u \to 1,v \to 1$ 均只和当前的非树边 $(u,v)$ 有关。因此，我们可以对于每条非树边算出刚才的式子的值。

于是，一个节点最终答案的大小与更新它的边的最小值有直接关系。

### Solution 1
接下来，答案就很显然了：我们树链剖分，然后线段树维护区间最小值即可。时间复杂度 $O(n \log^2 n)$。

### Solution 2
Solution 1 十分的粗鲁：直接用数据结构解决了，但是双 $\log$。能不能用更简单的方法呢？

我们发现，一个点被一条边权最小的边更新之后，就不会再被更新了。于是考虑**对边按照其对应值进行从小到大排序**，每条边暴力找路径，更新答案，但是**每次更新完一个点，就把他删掉**。删掉？就是下次访问它，直接跳到它的最近没被删的祖先。这让我们想到**并查集路径压缩**。于是，这道题~~被优雅解决了~~。时间复杂度 $O(n)$ 左右。

### Code
```cpp
#include <bits/stdc++.h>
#define lowbit(x) (x & -x)
using namespace std;
typedef long long ll;
const int Inf = 2147483647, Mod = 1000000007, MOD = 998244353;
const int in3f = 1061109567, in7f = 2139062143, n3f = -1044266559, n7f = -2122219135;
//以上为模板
const int N = 100005, M = N << 2;
int n, m, gtot, head[N], fa[N], dis[N], tot, dep[N];
struct Edge {
    int u, v, c, nxt;
    bool operator<(const Edge ano) const { return dis[u] + dis[v] + c < dis[ano.u] + dis[ano.v] + ano.c; }
} g[M], es[M];
void Add(int u, int v, int c) {
    g[++gtot] = { u, v, c, head[u] };
    head[u] = gtot;
}
struct Node {
    int u, d;
    bool operator<(const Node ano) const { return d > ano.d; }
};
void Dijkstra() {
    memset(dis, 0x3f, sizeof dis);
    dis[1] = 0;
    priority_queue<Node> pq;
    pq.push({ 1, 0 });
    while (!pq.empty()) {
        int u = pq.top().u, d = pq.top().d;
        pq.pop();
        if (d > dis[u])
            continue;
        dep[u] = dep[fa[u]] + 1;
        for (int i = head[u]; i; i = g[i].nxt) {
            int v = g[i].v;
            if (dis[v] > dis[u] + g[i].c) {
                dis[v] = dis[u] + g[i].c;
                pq.push({ v, dis[v] });
                fa[v] = u;
            }
        }
    }
}
int pa[N];
void Dset_init() {
    for (int i = 0; i < N; i++) pa[i] = i;
}
int Get_pa(int x) { return x == pa[x] ? x : (pa[x] = Get_pa(pa[x])); }
int ans[N];
signed main() {
    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v, c;
        cin >> u >> v >> c;
        Add(u, v, c);
        Add(v, u, c);
    }//建图
    Dijkstra();//找出最短路树上每个点的父亲
    for (int i = 1; i <= gtot; i++) {
        if (g[i].u == fa[g[i].v] || g[i].v == fa[g[i].u] || g[i].u > g[i].v)
            continue;
        es[++tot] = g[i];
    }//找出非树边
    sort(es + 1, es + tot + 1);//按照其代数式值排序
    Dset_init();//并查集初始化
    memset(ans, -1, sizeof ans);//坑人的就是这个
    for (int i = 1; i <= tot; i++) {
        int u = Get_pa(es[i].u), v = Get_pa(es[i].v);//找到两个节点，开始向上跳
        while (u != v) {
            if (dep[u] < dep[v])
                swap(u, v);//跳深度更深的那个
            ans[u] = dis[es[i].u] + dis[es[i].v] + es[i].c - dis[u];//更新答案
            pa[u] = fa[u];
            u = Get_pa(u);//删点
        }
    }
    for (int i = 2; i <= n; i++) cout << ans[i] << "\n";//输出，Accepted!
    return 0;
}
```

---

## 作者：happybob (赞：1)

题意：[P2934 [USACO09JAN] Safe Travel G](https://www.luogu.com.cn/problem/P2934)。

简要题意：$n$ 个点 $m$ 条边的简单无向连通图，对于 $i \in [2,n]$，求出如果删掉 $1$ 到 $i$ 最短路的最后一条边，新的最短路长度。保证 $1$ 到任意一个点最短路唯一。

解法：

首先介绍最短路树。

考虑求出从 $1$ 到每个点的最短路，以及每个点的前驱，也就是最短路上倒数第二个点，记为 $fa_u$（在本题中是唯一的，一般图不一定唯一）。然后考虑一个图，有 $n-1$ 条边，每条边是 $fa_u \leftrightarrow u(u \in [2,n])$。

这个图有 $n$ 个点，$n-1$ 条边。事实上可以发现，无论最短路是否唯一，只要无负环，这个图必然连通，于是这个图必然是一棵树。

考虑将这棵树视为以 $1$ 为根的有向树。有什么性质？首先，比较显然，由于最短路有最优子结构，$1$ 到每个点 $i$ 的最短路，就是树上 $1 \rightarrow i$ 的简单路径。其次，对于树上两个点 $u,v$，$u$ 为 $v$ 的祖先，那么 $u \rightarrow v$ 的简单路径也是原图上 $u \rightarrow v$ 的最短路。

现在考虑原题。相当于我要删掉每条边，设这条边的两个端点较深的是 $u$，我现在要求 $1 \rightarrow u$ 的最短路。那么必然是，从 $1$ 沿着树走到某个点，然后通过一条非树边，跳到 $u$ 的子树内，然后走回 $u$。我们可以证明只会经过一条非树边。

证明：

假如我们走进了 $u$ 子树，那肯定不会在通过任何非树边走，因为这不优，与性质 $2$ 矛盾。

其次，假如在进入 $u$ 子树前走了两次非树边，容易注意到这和性质 $1$，即 $1 \rightarrow i$ 最短路是树上路径矛盾。

证毕。

那只要考虑枚举每条非树边 $(u,v)$。我们知道 $u,v$ 需要走 $u,v$ 这条边的必然是从非子树内跨入子树内，于是那些要被更新答案的点必然在 $u$ 到 $v$ 路径上，**且不是 $\operatorname{LCA}(u,v)$**。然后，考虑这些点中每一个，记为 $k$。容易观察到，这时 $k$ 的答案其实是 $dis_u+dis_v+w-dis_k$。$dis_i$ 是 $1 \rightarrow i$ 最短路长度，$w$ 是 $(u,v)$ 这条边的权值。而 $dis_k$ 与 $(u,v)$ 无关，可以单独处理。剩余的 $dis_u+dis_v+w$，可以从小到大排序，然后就变成了这样的问题；一棵树，每次给两个点和一个权值，然后将链上没有覆盖过的点覆盖为这个权值。当然你可以树剖做到 $2\log$，不过我们考虑并查集！每个点维护 $f_u$ 表示 $u$ 的祖先（不包含 $u$），最深的没被覆盖过的点，没有记为 $0$。然后每次暴力跳并查集即可。每个点只会被覆盖 $1$ 次。如果使用 $O(1)$ LCA，就可以做到 $O(n \alpha(n))$。然而我写的还是 $O(n \log n)$ 的。

特别注意，$\operatorname{LCA}(u,v)$ 不能被覆盖答案。

代码：

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <set>
#include <cassert>
#include <map>
using namespace std;

const int N = 2e5 + 5;

int n, m;
vector<pair<int, int>> G[N];
vector<int> NG[N];
int pre[N];
int dis[N];
bool vis[N];

struct Node
{
	int u, d;
	Node(int u, int d) :u(u), d(d) {}
	Node() = default;
	bool operator<(const Node& g) const
	{
		return d > g.d;
	}
};

int fa[N][20];
int dep[N];

void dfs(int u, int f)
{
	dep[u] = dep[f] + 1;
	fa[u][0] = f;
	for (auto& j : NG[u]) if (j ^ f) dfs(j, u);
}

struct Edge
{
	int u, v, w;
	Edge() = default;
	Edge(int u, int v, int w) :u(u), v(v), w(w) {}
};

bool chk[N];

class Dsu
{
public:
	int f[N];
	void Init()
	{
		for (int i = 1; i <= n; i++) f[i] = fa[i][0];
	}
	int find(int u)
	{
		if (u == 0) return u;
		if (!chk[f[u]]) return f[u];
		return f[u] = find(f[u]);
	}
}dsu;

int ans[N];

int u[N], v[N], w[N];

int main()
{
	ios::sync_with_stdio(0), cin.tie(0);
	memset(dis, 0x3f, sizeof dis);
	memset(ans, 0x3f, sizeof ans);
	cin >> n >> m;
	for (int i = 1; i <= m; i++)
	{
		int u, v, w;
		cin >> u >> v >> w;
		::u[i] = u, ::v[i] = v, ::w[i] = w;
		G[u].emplace_back(make_pair(v, w));
		G[v].emplace_back(make_pair(u, w));
	}
	auto dijkstra = [&](int st)->void
		{
			priority_queue<Node> q;
			dis[st] = 0;
			q.push(Node(st, 0));
			while (q.size())
			{
				auto [u, d] = q.top();
				q.pop();
				if (vis[u]) continue;
				vis[u] = 1;
				for (auto& [j, w] : G[u])
				{
					if (dis[j] > dis[u] + w)
					{
						pre[j] = u;
						dis[j] = dis[u] + w;
						q.push(Node(j, dis[j]));
					}
				}
			}
		};
	dijkstra(1);
	for (int i = 2; i <= n; i++) NG[pre[i]].emplace_back(i);
	dfs(1, 0);
	auto Init = [&]()->void
		{
			for (int j = 1; j <= 19; j++)
			{
				for (int i = 1; i <= n; i++) fa[i][j] = fa[fa[i][j - 1]][j - 1];
			}
		};
	Init();
	auto LCA = [&](int u, int v)->int
		{
			if (u == v) return u;
			if (dep[u] < dep[v]) swap(u, v);
			int c = 0, k = dep[u] - dep[v];
			while (k)
			{
				if (k & 1) u = fa[u][c];
				c++;
				k >>= 1;
			}
			if (u == v) return u;
			for (int i = 19; i >= 0; i--) if (fa[u][i] ^ fa[v][i]) u = fa[u][i], v = fa[v][i];
			return fa[u][0];
		};
	vector<Edge> ve;
	for (int i = 1; i <= m; i++)
	{
		int u = ::u[i], v = ::v[i], w = ::w[i];
		int nval = dis[u] + dis[v] + w;
		ve.emplace_back(Edge(u, v, nval));
	}
	sort(ve.begin(), ve.end(), [&](const auto& h, const auto& x) {return h.w < x.w; });
	dsu.Init();
	for (auto& [u, v, w] : ve)
	{
		if (pre[u] == v || pre[v] == u) continue;
		if (dep[u] > dep[v]) swap(u, v);
		int k = LCA(u, v);
		if (k != u)
		{
			if (!chk[u])
			{
				chk[u] = 1;
				ans[u] = w;
			}
		}
		if (k != v && !chk[v]) chk[v] = 1, ans[v] = w;
		int j = u;
		while (true)
		{
			int p = dsu.find(j);
			if (!p || dep[p] <= dep[k]) break;
			chk[p] = 1, ans[p] = w;
		}
		j = v;
		while (true)
		{
			int p = dsu.find(j);
			if (!p || dep[p] <= dep[k]) break;
			chk[p] = 1, ans[p] = w;
		}
	}
	for (int i = 2; i <= n; i++)
	{
		if (ans[i] == ans[0]) cout << "-1\n";
		else cout << ans[i] - dis[i] << "\n";
	}
	return 0;
}
```

---

## 作者：xhhhh36 (赞：0)

[传送门](https://www.luogu.com.cn/problem/P2934)

根据题目限制：特别地，保证 $1$ 到任何一个点 $i$ 的最短路都是唯一的。容易想到将最短路会经过的所有边建立成一棵最短路树。

建立出最短路树之后，考虑如何求出断开 $i$ 的父亲和 $i$ 之间的边到达 $i$ 的最短路。首先可以发现，最终的答案路径必须经过一条非树边，因为如果该路径经过更多条非树边，那么最多只有一条非树边会包含被断开的边，那么将其他的非树边替换成树边可以使答案更优，如果不经过非树边就必须经过$i$ 的父亲和 $i$ 之间的边。

那么我们可以考虑枚举每条非树边 $(u,v)$，那么位于 $u$ 到 $lca(u,v)$ 和 $v$ 到 $lca(u,v)$ 路径上的点的答案路径都有可能是经过 $(u,v)$ 后得到的，此时经过 $(u,v)$ 到达可能更新的点 $i$ 的代价就为 $dis_u+dis_v-dis_i+w_{u,v}$。

因为 $dis_i$ 为定值，所以可以考虑将每条非树边按照 $dis_u+dis_v+w_{u,v}$ 从小到大排序，每次拿当前的边去尝试更新能够更新的点的答案。因为权值已经从小到大排序，所以已经被更新过的点的答案已经是最有的了，可以考虑使用并查集将被更新过的点和他的父亲合并在一起，每次只用更新每个并查集的父亲即可。

# AC code
```cpp
#include <bits/stdc++.h>
#define int long long
#define pa pair<int,int>
#define f first
#define s second
using namespace std;
const int N=2e5+5;
int n,m,h[N],cnt=0,dis[N],ans[N],fa[N],dep[N],f[N];
struct node{
	int to,nxt,w;
}e[N*2];
void add_edge(int u,int v,int w){
	e[++cnt].to=v;
	e[cnt].nxt=h[u];
	e[cnt].w=w;
	h[u]=cnt;
}
priority_queue<pa,vector<pa>,greater<pa> > q;
void dj(){
	memset(dis,0x3f,sizeof(dis));
	q.push({0,1});
	while (!q.empty()){
		pa t=q.top();q.pop();
		if (t.f>=dis[t.s]) continue ;
		dis[t.s]=t.f;
		for (int i=h[t.s];i!=-1;i=e[i].nxt){
			int v=e[i].to,w=e[i].w;
			if (dis[v]>dis[t.s]+w) q.push({dis[t.s]+w,v});
		}
	}
}
struct ask{
	int u,v,w;
}z[N*2];
void dfs(int x){
	for (int i=h[x];i!=-1;i=e[i].nxt){
		int u=e[i].to,w=e[i].w;if (u==f[x]||dis[x]+w!=dis[u]) continue ;
		f[u]=x;dep[u]=dep[x]+1;dfs(u);
	}
}
int find(int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
bool cmp(ask a,ask b){
	return a.w<b.w;
}
signed main(){
	ios::sync_with_stdio(0);
	memset(h,-1,sizeof(h));memset(ans,-1,sizeof(ans));
	cin>>n>>m;
	for (int i=1;i<=m;i++){
		int u,v,w;cin>>u>>v>>w;
		add_edge(u,v,w);add_edge(v,u,w);
	}dj();cnt=0;dfs(1);f[1]=1;
	for (int i=1;i<=n;i++){
		fa[i]=i;
		for (int j=h[i];j!=-1;j=e[j].nxt){
			int v=e[j].to,w=e[j].w;
			if (dis[v]+w==dis[i]||dis[i]+w==dis[v]) continue ;
			z[++cnt]={i,v,dis[i]+dis[v]+w};
		}
	}sort(z+1,z+1+cnt,cmp);
	for (int i=1;i<=cnt;i++){
		int u=find(z[i].u),v=find(z[i].v);
		while (u!=v){
			if (dep[u]<dep[v]) swap(u,v);
			ans[u]=z[i].w-dis[u];fa[u]=f[u];
			u=find(u);
		}
	}
	for (int i=2;i<=n;i++) cout<<ans[i]<<endl;
	return 0;
}
```

---

## 作者：hh弟中弟 (赞：0)

另类做法！\
先建出最短路 DAG，因为保证最短路径唯一，所以建出来的 DAG 是一棵树。考虑一个点的答案可以由谁来更新，假设当前点为点 $u$，它的 dfs 序控制范围是 $l,r$。首先，它可以由子树外除了父亲的节点来更新，形如 `ans[u]=dis[v]+w`，它也可以由子树内的节点更新，路径形如 $1\to zc\to v\to u$，要求中转点 $zc$ 必须在 $u$ 的子树外，形式化的来说 $ans_u=\min(dis_{zc}+w_{zc\to v})+w_{v\to u}[1\le dfn_{zc}<l\lor r<dfn_{zc}\le n]$，然后问题就成了一个单点修改，区间查询最小值的问题，从下往上线段树合并即可，时间复杂度 $\mathcal{O}(n\log n)$，常数比较小，甚至在最优解第三页。

```cpp
#include<bits/stdc++.h>
#define int long long
#define fi first
#define se second
#define pii std::pair<int,int>
#define eb emplace_back
typedef long long ll;
typedef unsigned long long ull;
std::mt19937 myrand(std::chrono::high_resolution_clock::now().time_since_epoch().count());
inline int RR(int n){return myrand()%n+1;}
inline int read(){char ch=getchar();int x=0,f=1;for(;ch<'0'||ch>'9';ch=getchar())if(ch=='-')f=-1;for(;ch>='0'&&ch<='9';ch=getchar())x=(x<<3)+(x<<1)+(ch^48);return x*f;}
const int N=1e5+10,mod=998244353;
const int inf=1e18;
inline void Min(ll &x,ll y){if(x>y)x=y;}
inline void Max(int &x,int y){if(x<y)x=y;}
inline void W(int &x,int y){x=(x+y)%mod;}
int n,m,in[N],head[N],headg[N],tot,fa[N],L[N],R[N],dn,rub[N*20],num;
ll dis[N],ans[N];
struct EDGE{int v,next,w;}e[N<<2],g[N<<1];
inline void adde(int u,int v,int w){e[++tot]={v,head[u],w};head[u]=tot;}
inline void addg(int u,int v,int w){g[++tot]={v,headg[u],w};headg[u]=tot;}
bool vis[N],zhan[N<<2];
struct NODE{
	int pos;ll w;
	inline bool operator<(const NODE &A)const{return w>A.w;}
};
std::priority_queue<NODE> q;
inline int fan(int x){if(x&1)return x+1;else return x-1;}
inline void dij(){
	memset(dis,0x3f,sizeof(dis));
	dis[1]=0;q.push({1,0});
	while(!q.empty()){
		int u=q.top().pos;q.pop();
		if(vis[u])continue;vis[u]=1;
		for(int i=head[u];i;i=e[i].next){
			int v=e[i].v,w=e[i].w;
			if(dis[v]>dis[u]+w){
				dis[v]=dis[u]+w;
				zhan[in[v]]=0;zhan[fan(in[v])]=0;
				in[v]=i;zhan[in[v]]=zhan[fan(in[v])]=1;fa[v]=u;
				if(!vis[v]){q.push({v,dis[v]});}
			}
		}
	}
}
int root[N],cnt;
struct TREE{ll res;int ls,rs;}t[N*20];
inline int NEW(){int wk=num?rub[num--]:++cnt;t[wk]={inf,0,0};return wk;}
inline void Del(int &p){t[p]={inf,0,0};rub[++num]=p;}
inline void update(int p){
	t[p].res=std::min(t[t[p].ls].res,t[t[p].rs].res);
}
inline void insert(int &p,int l,int r,int pos,ll x){
	if(!p)p=NEW();
	if(l==r){Min(t[p].res,x);return;}
	int mid=l+r>>1;if(pos<=mid)insert(t[p].ls,l,mid,pos,x);
	else insert(t[p].rs,mid+1,r,pos,x);update(p);
}
inline int merge(int a,int b,int l,int r){
	if(!a||!b)return a|b;
    if(l==r){Min(t[a].res,t[b].res);Del(b);return a;}
    int mid=l+r>>1;
    t[a].ls=merge(t[a].ls,t[b].ls,l,mid);
    t[a].rs=merge(t[a].rs,t[b].rs,mid+1,r);
    update(a);Del(b);return a;
}
inline ll query(int p,int l,int r,int L,int R){
	if(t[p].res>=inf)return inf;
	if(L>R)return inf;
	if(l>=L&&r<=R)return t[p].res;
	int mid=l+r>>1;ll res=inf;
	if(L<=mid)Min(res,query(t[p].ls,l,mid,L,R));
	if(R>mid)Min(res,query(t[p].rs,mid+1,r,L,R));
	return res;
}
inline void init(int u){
	L[u]=++dn;
	for(int i=headg[u];i;i=g[i].next)init(g[i].v);
	R[u]=dn;
}
inline void dfs(int u,ll dep){
	for(int i=headg[u];i;i=g[i].next){
		dfs(g[i].v,dep+g[i].w);
		root[u]=merge(root[u],root[g[i].v],1,n);
	}
	if(u==1)return;
	Min(ans[u],std::min(query(root[u],1,n,1,L[u]-1),query(root[u],1,n,R[u]+1,n))-dep);
	for(int i=head[u];i;i=e[i].next){
		int v=e[i].v;
		if(zhan[i]||L[v]>=L[u]&&R[v]<=R[u])continue;
		ll res=dis[v]+e[i].w;insert(root[u],1,n,L[v],res+dep);
		Min(ans[u],res);
	}
}
signed main(){
    freopen("path.in","r",stdin);freopen("path.out","w",stdout);
    // freopen("in.in","r",stdin);freopen("out.out","w",stdout);
    std::ios::sync_with_stdio(false);std::cin.tie(0);std::cout.tie(0);
    n=read(),m=read();for(int i=1;i<=m;++i){int u=read(),v=read(),w=read();adde(u,v,w);adde(v,u,w);}
    dij();tot=0;for(int i=2;i<=n;++i)addg(fa[i],i,e[in[i]].w);
	init(1);t[0].res=inf;for(int i=1;i<=n;++i)ans[i]=inf;
    dfs(1,0);
	for(int i=2;i<=n;++i)std::cout<<(ans[i]>=1e17?-1:ans[i])<<'\n';
}
```

---

