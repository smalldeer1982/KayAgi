# [AGC012B] Splatter Painting

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc012/tasks/agc012_b

イカはグラフの頂点に色を塗るのが好きです。

$ 1 $ から $ N $ までの番号がついた $ N $ 個の頂点と $ M $ 本の辺からなる単純無向グラフが与えられます。 全ての頂点ははじめ、色 $ 0 $ で塗られています。$ i $ 番目の辺は頂点 $ a_i $ と頂点 $ b_i $ を双方向につなぐ長さ $ 1 $ の辺です。

イカはこのグラフに対して $ Q $ 回の操作を行いました。 $ i $ 回目の操作では、頂点 $ v_i $ から距離 $ d_i $ 以内にあるような頂点たち全ての色を色 $ c_i $ で上書きしました。

$ Q $ 回の操作後において、各頂点がどの色で塗られているか調べてください。

## 说明/提示

### 制約

- $ 1\ ≦\ N,M,Q\ ≦\ 10^5 $
- $ 1\ ≦\ a_i,b_i,v_i\ ≦\ N $
- $ a_i\ ≠\ b_i $
- $ 0\ ≦\ d_i\ ≦\ 10 $
- $ 1\ ≦\ c_i\ ≦10^5 $
- $ d_i,\ c_i $ いずれも整数
- 与えられるグラフに自己ループや多重辺は存在しない

### 部分点

- $ 1\ ≦\ N,M,Q\ ≦\ 2{,}000 $ を満たすデータセットに正解した場合は、部分点として $ 200 $ 点が与えられる。

### Sample Explanation 1

はじめ、各頂点は色 $ 0 $ で塗られています。 $ 1 $ 回目の操作により、頂点 $ 5,6 $ が色 $ 1 $ で塗られます。 $ 2 $ 回目の操作により、頂点 $ 1,2,3,4,5 $ が色 $ 2 $ で塗られます。 !\[2ab7e180230b159d42d35ea7e555b3b0.png\](https://atcoder.jp/img/agc012/2ab7e180230b159d42d35ea7e555b3b0.png)

### Sample Explanation 2

与えられるグラフは連結とは限りません。

## 样例 #1

### 输入

```
7 7
1 2
1 3
1 4
4 5
5 6
5 7
2 3
2
6 1 1
1 2 2```

### 输出

```
2
2
2
2
2
1
0```

## 样例 #2

### 输入

```
14 10
1 4
5 7
7 11
4 10
14 7
14 3
6 14
8 11
5 13
8 3
8
8 6 2
9 7 85
6 9 3
6 7 5
10 3 1
12 9 4
9 6 6
8 2 3```

### 输出

```
1
0
3
1
5
5
3
3
6
1
3
4
5
3```

# 题解

## 作者：zhylj (赞：11)

[广告](http://zhylj.cc/tags/AtCoder/)

这题我的做法似乎和其他人不一样。

考虑两种染色 $i,j$，如果 $i > j$ （也就是 $i$ 在 $j$ 之后）且 $d_i > d_j$，那 $j$ 就没有用了。

考虑设 $t(i, j)$ 代表在点 $i$ 的染色方案中，$d$ 为 $j$ 的**最晚的操作**的编号。

每次将 $t(i,j)$ 的操作转移到与它相邻的所有点 $v$ 的 $t(v, j - 1)$（取 $\max$）。我们按 $j$ 从大到小倒着转移，即可在 $\mathcal O(d\cdot (n + m))$ 的时间内解决。

最后取 $\max_jt(i,j)$ 操作的颜色即为 $i$ 的颜色。

```cpp
const int kN = 1e5 + 5, kD = 12;

int n, m, c[kN], t[kN][kD];
std::vector <int> E[kN];

int main() {
	rd(n, m); // 快读
	for(int i = 1; i <= m; ++i) {
		int x, y; rd(x, y);
		E[x].push_back(y); E[y].push_back(x);
	}
	int q; rd(q);
	for(int i = 1; i <= q; ++i) {
		int v, d; rd(v, d, c[i]);
		t[v][d] = i;
	}
	for(int k = 10; k; --k) 
		for(int i = 1; i <= n; ++i)
			for(auto v : E[i]) // 枚举相邻点
				t[v][k - 1] = std::max(t[i][k], t[v][k - 1]);
	for(int i = 1; i <= n; ++i) {
		int x = 0;
		for(int j = 0; j <= 10; ++j) x = std::max(x, t[i][j]);
		printf("%d\n", c[x]);
	}
	return 0;
}
```

---

## 作者：曾爷爷 (赞：6)

这道题如果将输入的操作正着处理的话，会使修改点的颜色变得麻烦

正难则反

我们倒着考虑，如果从最后一个询问开始处理是不是就不用考虑修改点的颜色了呢？

因为每一组修改都用可能会将之前的修改给覆盖了，如果倒着做，就是直接得到最终状态

然后直接dfs就好了，需要加点剪枝

具体思想康代码

```cpp
//#pragma GCC optimize(2)
//#pragma GCC optimize(3)
#include <bits/stdc++.h>
#define N 100005
#define int long long
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<22,stdin),p1 == p2)?EOF:*p1++)
using namespace std ;
//char buf[(1 << 22)] , *p1 = buf , *p2 = buf ;
inline int read ()
{
    char c = getchar () ; int x = 0 , f = 1 ;
    while (c < '0' || c > '9') { if (c == '-') f = -1 ; c = getchar () ; }
    while (c >= '0' && c <= '9'){ x = x * 10 + c - '0' ; c = getchar () ; }
    return x * f ;
}
int n , m , ver[N << 1] , nxt[N << 1] , hed[N] , tot , ans[N] , Dis[N] ;
struct as {
	int v , d , c ;
} a[N] ;
void add (int x , int y) { ver[++ tot] = y ; nxt[tot] = hed[x] ; hed[x] = tot ; }
void dfs (int x , int col , int dis)
{
	if (! ans[x]) ans[x] = col ;//如果当前这个点没有颜色那么就把它染色，染色过得点就不会再改变了，因为是倒着做的
	if (! dis || Dis[x] >= dis) return ;//如果距离x的距离为零那么就返回
	Dis[x] = dis ;//Dis数组记录的是x点染过的最远的距离，那么上面这个[Dis[x] >= dis] 的剪枝的意思就是如果当前x点染过色的最远距离比当前距离长，那么就返回
	for (int i = hed[x] ; i ; i = nxt[i])
	{
		int y = ver[i] ;
		dfs (y , col , dis - 1) ;//继续递归染色，距离x的距离-1
	}
}
signed main ()
{
	n = read () , m = read () ;
	for (int i = 1 , u , v ; i <= m ; u = read () , v = read () , add (u , v) , add (v , u) , i ++) ;//邻接表建图不讲
	int q = read () ;
	for (int i = 1 ; i <= q ; i ++) a[i].v = read () , a[i].d = read () , a[i].c = read () ;
	for (int i = q ; i >= 1 ; i --) dfs (a[i].v , a[i].c , a[i].d) ;//倒着染色
	for (int i = 1 ; i <= n ; i ++) printf ("%d\n" , ans[i]) ;
}

```

---

## 作者：CHHC (赞：4)

这道题N、M、Q的范围为1e5，如果直接模拟……必定TLE。

所以我们要想方法改进（废话）

然而……模拟是一切的基础。还是先看一下模拟吧……

```cpp
using namespace std;

#define iii pair<pair<int,int>,int> 
#define V first.first
#define D first.second
#define C second

int N,M;
vector<int> edge[100010];  //edge[i][j]表示从i到j的边 
int Q;
iii q[100010]; 

int colour[100010];

void f(int v,int d,int c)  //表示将到点v的距离为d以内的点染成c
{
    colour[v]=c;           //将点v染色 
    if(d==0) return;       //不能再延伸了 
    for(int i=0;i<edge[v].size();i++) 
    {
    	int to=edge[v][i];
        f(to,d-1,c);       //以点v的邻居为出发点，将到此距离为d-1以内的点染成c
    }
}

void work()
{
    for(int i=1;i<=Q;i++)
    {
        f(q[i].V,q[i].D,q[i].C);
    }
}

```
TLE：11/35

![](https://cdn.luogu.com.cn/upload/pic/45051.png)

~~（啊啊啊#1和#2中间的那个空格看着好难受啊啊）~~



------------


**分析一下可以发现：纯模拟的最大弊端就是重复染色**

而后来的染色会覆盖掉先前的染色，则

可(wu)以(fa)想到从后往前处理染色的操作，对已经染过了的点不重复染色，即改成这个样子……

```cpp
void f(int v,int d,int c)
{
    if(colour[v]==0) colour[v]=c;      
    if(d==0) return;   
    for(int i=0;i<edge[v].size();i++) 
    {
    	int to=edge[v][i];
        f(to,d-1,c);
    }
}

void work()
{
    for(int i=Q;i>=1;i--)
    {
        f(q[i].FIR,q[i].SEC,q[i].THI);
    }
}
```

但这样总时间复杂度仍没有改观，仍然TLE11/35。

（原因：若某一点已经染色，它的“邻居”们仍然可能没有被染过色，无法立即剪枝）


------------

所以，我们现在需要改进的，是要避免重复处理的情况发生。

由此，就有了两种方案：**（都需要从后往前处理染色的操作）**

1.对于每一次f(v,d,c)，若已经处理过从v点出发而d更大的染色操作，则这一次f(v,d,c)必定无效，可以return掉。

时间：706ms。

```cpp
int maxd[100010]; //初始值要赋为-1

void f(int v,int d,int c)
{
    if(d<=maxd[v]) return; 
    maxd[v]=d;
    
    if(colour[v]==0) colour[v]=c;
    for(int i=0;i<edge[v].size();i++)
    {
    	int to=edge[v][i];
        f(to,d-1,c);
    }
}
```

2.更容易想到的，对于每一个{v,d}，必定只有最后一次f(v,d)是有效的，直接开一个bool数组（done）来存储这一个f(v,d)是否已经被调用过。由于题目中说d的范围是d<=10，很小，所以复杂度也是正确的。

稍微慢一些，846ms。

```cpp
bool done[100010][15];
void f(int v,int d,int c)
{
    if(done[v][d]) return;
    done[v][d]=true;
    
    if(colour[v]==0) colour[v]=c;
    if(d==0) return;
    for(int i=0;i<edge[v].size();i++)
    {
    	int to=edge[v][i];
        f(to,d-1,c);
    }
}
```

就这样吧……

求管理大大通过QAQ~

另外……这道题是AGC的B题……难度（应该）没有 [ 省选/NOI- ] 吧……~~（你看我这么蒻怎么可能做紫题）~~

 $$$$
 $$$$

~~（号爸太强了233）~~




---

## 作者：Aw顿顿 (赞：3)

某日，在夕阳下的操场边，绿茵地泛起一阵柔柔的光，晚风吹过一帘爬山虎，拂开图书馆后的山间萦绕的晚岚，那天，我和学长谈了很久。

时至今日仍记忆犹新的，是在题目和人生中都适用的一句话，“**正难则反**”。

-------

给一个 $n$ 个点 $m$ 条边的无向图，有 $q$ 次操作，每次操作给出 $v,d,c$ 表示把所有到点 $v$ 距离不超过 $d$ 的点都染上颜色 $c$，只要求给出**最后每个点的颜色**。

暴力显然不行，反过来考虑，如果我们离线倒序处理，排除不必要的冗余操作，就能够大大减少浪费的时间，那么我们解题的重点就在于如何标记不需要染色的结点。

对于每一个结点，我们都需要维护一个数组 $dis$，譬如说 $dis_x$ 表示 $x$ 染色过的最远距离，显然这个染色用递归实现是很合适的，而中途我们要如何维护这个 $dis$ 数组呢？

```cpp
void dfs(int v,int d,int c){
	if(!col[v])col[v]=c;
	if(!d||dis[v]>=d)return;
	dis[v]=d;
	for(int i=h[v];i;i=e[i].nxt)
		dfs(e[i].v,d-1,c);
}
```

接下来我们需要说明这种操作的正确性，假设 $v$ 节点距离 $x$ 节点为 $a$，我们需要染色 $x$ 周围距离小于等于 $d$ 的节点，那么距离 $v$ 节点小于等于 $d-a$ 的节点一定全部被染色。

而这就是为什么我们判断到 $dis_v>d$ 的时候就可以退出，因为既然关于 $v$ 节点最远染色到 $dis_v$，那么一定存在以下两种情况之一：

- 要么某一次染色是关于 $v$，距离 $dis_v$ 的节点都已经染色。
- 染色这些节点的时候途径了 $v$，存在距离 $dis_v$ 的节点需要被染色，那么离他更近的节点一定离起始点更近。

那么，我们可以大胆剪枝，同时维护 $dis$ 数组，接下来给出全文代码实现：

```cpp
#include<bits/stdc++.h>
#define int long long
#define N 100005
using namespace std;
struct edge{int v,nxt;}e[N<<1];
struct deal{int v,d,c;}op[N];
int n,m,q,h[N],cnt,col[N],dis[N];
void add(int u,int v){e[++cnt].v=v;e[cnt].nxt=h[u];h[u]=cnt;}
void dfs(int v,int d,int c){
	if(!col[v])col[v]=c;
	if(!d||dis[v]>=d)return;
	dis[v]=d;
	for(int i=h[v];i;i=e[i].nxt)
		dfs(e[i].v,d-1,c);
}signed main(){
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=m;i++){
		int u,v;scanf("%lld%lld",&u,&v);
		add(u,v);add(v,u);
	}scanf("%lld",&q);
	for(int i=1;i<=q;i++)
		scanf("%lld%lld%lld",&op[i].v,&op[i].d,&op[i].c);
	for(int i=q;i>=1;i--)
		dfs(op[i].v,op[i].d,op[i].c);
	for(int i=1;i<=n;i++)
		printf("%lld\n",col[i]);
	return 0;
}
```

---

## 作者：Yukinoshita_Yukino (赞：1)

[Link](https://www.luogu.com.cn/problem/AT2362)

题意：给一个无向图，有 $q$ 次操作，每次操作指定一个点 $v$ ,给它距离不大于 $d$ 的点染色，求最后每个点的颜色。

按照题意模拟显然会 T 飞。

因为后面的操作会覆盖前面的操作，我们不妨先处理后面的操作，再处理前面的操作。

具体来说，从后往前依次 dfs ，给搜索到的但是没有被染色的点染色。但是如果不加剪枝的话也会 T 。因为搜索的时候经过了很多无效的点。

考虑加剪枝，还是由于后面能覆盖前面的点的性质，我们可以给每个点加一个标记 $dis$ 。$dis_i$ 代表第 $i$ 个点目前走过的最远距离，即搜到 $i$ 这个点时历史最大能走的步数。当再次搜到 $i$ 这个点时，如果目前能走的步数小于 $dis_i$ 的话，那么这个搜索肯定没有贡献，于是就可以剪枝了。


代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=300000;
int n,m,cnt=0,h[maxn],col[maxn],v[maxn],d[maxn],c[maxn],q;
int vis[maxn];
struct edge
{
	int to;
	int next;
}e[maxn+10];
void add(int u,int v)
{
	e[++cnt].to=v;
	e[cnt].next=h[u];
	h[u]=cnt;
}
void dfs(int id,int dis,int now)
{
	if(dis==-1) return ;
	if(vis[now]>=dis) return ;
	vis[now]=dis;
	if(!col[now]) 
	{
		col[now]=c[id];
	//	cout<<now<<"qwq"<<c[id]<<endl; 
	}
	for(int i=h[now];i;i=e[i].next)
	{
		int qwq=e[i].to;
		dfs(id,dis-1,qwq);
	}
}
int main()
{
	memset(vis,-1,sizeof vis);
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		int a,b;
		cin>>a>>b;
		add(a,b);
		add(b,a);
	}
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		cin>>v[i]>>d[i]>>c[i];
	}
	for(int i=q;i>=1;i--)
	{
		dfs(i,d[i],v[i]);
	}
	for(int i=1;i<=n;i++)
	{
		cout<<col[i]<<endl;
	}
	return 0;
 } 

```

---

## 作者：FutaRimeWoawaSete (赞：1)

考虑一个点最后的颜色应该是被一个尽量靠后的操作更新到的。          

由于我们 $d \leq 10$，考虑直接 $O(nk)$ 把每个点最后被更新到的时间戳给 dp 出来。            

令 $dp_{i,j}$ 表示在 $j$ 存在一个 $d$ 为 $i$ 的操作的最大时间戳，可以如下转移：           

$dp_{i - 1,k} = \max(dp_{i,j} , dp_{i - 1,k}),(k,j) \in E$        

然后直接倒序枚举 $i$ 转移后输出即可。



---

## 作者：离散小波变换° (赞：1)

## 题解

注意到 $d\le 10$，于是可以考虑分层图。具体而言，我们将每个点拆成 $11$ 个，分别对应 $d=0,1,2\cdots 10$。首先，第 $i$ 层上的 $u$ 号点向 $i-1$ 层上的 $u$ 号点连有向边。

对于每条边 $u\leftrightarrow v$，枚举 $i=1,2\cdots 10$，进行如下操作：

- 将第 $i$ 层上的 $u$ 号点连向第 $i-1$ 层上的 $v$ 号点。
- 将第 $i$ 层上的 $v$ 号点连向第 $i-1$ 层上的 $u$ 号点。

我们设从点 $u$ 出发可以到达的第 $0$ 层上的点称为被 $u$ 控制的点。容易发现，第 $i$ 层上的 $u$ 号点控制的点恰好就是原图上到 $u$ 的距离不超过 $i$ 的点的集合。这是容易证明的，因为每向下走一层，能够到达的点到 $u$ 的距离就会增加 $1$。

那么对于第 $i$ 个操作 $v,d,u$，我们向第 $d$ 层上的点 $v$ 打上标记 $\{i,c\}$。$i$ 是时间戳，$c$ 是我们给它染上的颜色。$q$ 次操作以后，从最高层开始沿着有向边往下转移标记。注意：时间戳更大的标记可以覆盖时间戳更小的标记。这样就保证了总时间复杂度的正确性。

容易发现，时间复杂度为 $\mathcal O(d_{\max}\times (n+m))$。值得注意的是，我们一共创建了 $(d_{\max}+1)\times n$ 个点，建立了 $d_{\max}\times (2\times m+n)$ 条边。不要开小数组导致 $\text{RE}$。

## 参考代码

```cpp
#include<bits/stdc++.h>
#define up(l,r,i) for(int i=l,END##i=r;i<=END##i;++i)
#define dn(r,l,i) for(int i=r,END##i=l;i>=END##i;--i)
using namespace std;
typedef long long i64;
const int INF =2147483647;
const int MAXN=1e5+3;
const int MAXM=1e5+3;
const int MAXD=10+3;
int H[MAXN*MAXD],V[MAXN*MAXD*2],N[MAXN*MAXD*2],t;
void add(int u,int v){
    V[++t]=v,N[t]=H[u],H[u]=t;
}
int n,m,q,X[MAXD][MAXN],Y[MAXN*MAXD];
int qread(){
    int w=1,c,ret;
    while((c=getchar())> '9'||c< '0') w=(c=='-'?-1:1); ret=c-'0';
    while((c=getchar())>='0'&&c<='9') ret=ret*10+c-'0';
    return ret*w;
}
struct Node{
    int t,c; Node(int _t=0,int _c=0):t(_t),c(_c){}
}O[MAXD][MAXN];
int main(){
    n=qread(),m=qread(); int o=0;
    up(0,10,i) up(1,n,j) X[i][j]=++o,Y[o]=j;
    up(1,10,i) up(1,n,j) add(X[i][j],X[i-1][j]);
    up(1,m,i){
        int u=qread(),v=qread();
        up(1,10,j){
            add(X[j][u],X[j-1][v]);
            add(X[j][v],X[j-1][u]);
        }
    }
    q=qread();
    up(1,q,i){
        int v=qread(),d=qread(),c=qread();
        O[d][v]={i,c};
    }
    dn(10,0,i){
        up(1,n,u){
            for(int j=H[X[i][u]];j;j=N[j]){
                int v=Y[V[j]];
                if(O[i][u].t>O[i-1][v].t)
                    O[i-1][v]=O[i][u];
            }
        }
    }
    up(1,n,i) printf("%d\n",O[0][i].c);
    return 0;
}
```

---

## 作者：_52hz (赞：0)

## 题目大意

给你  **_$n_{}$_**  个点  **_$m_{}$_**  条边的无向图，然后  **_$q_{}$_**  次操作，每次给出一组    **_$v_{i}$_**  ,  **_$d_{i}$_** ,  **_$c_{i}$_** ,   表示将以  **_$v_{i}$_**  为中心点 ， 距离不超过  **_$d_{i}$_**  的节点染成  **_$c_{i}$_**  的颜色

## 解法

因为有 $q_{}$ 次操作，所以很自然想到读入询问后逆过来染色 ，加上判断条件可减去很多不必要操作；

在搜索过程中处理 $cor[i][j]$ 的判断条件，表示以 $i$ 为中心点，距离不超过 $j$ 被染成了 $c$ 的颜色，如果 $cor[i][j]$ 大于零则证明 $j$ 范围内已经被染色，不必再搜； 

有一个小技巧就是把每个点 $push$_$back$ 道自己的后面，最后 $cor[i][0]$ 即为所求；

## Code

~~快读打错了真难受~~

```cpp
#include<bits/stdc++.h>

typedef long long ll;

const int maxn = 1e5 + 10;

int n, m, a, b, q, cor[maxn][14], qwq[maxn], qaq[maxn], c[maxn];

std::vector <int> pb[maxn];

void Work(int st, int deep, int cl)
{
    if(deep == -1) return;
    if(cor[st][deep]) return;
    cor[st][deep] = cl;
    for(int i = 0; i < pb[st].size(); ++ i) Work(pb[st][i], deep-1, cl);
}

int read()
{
	int x=0, ch= getchar(), f=1;
	while(!isdigit(ch)) if(ch == '-')f = -1, ch = getchar();
	while(isdigit(ch)) x = x *10 + ch-'0', ch = getchar();
	return x * f;
} 

int main()
{
    n=read(), m=read();
    for(int i=1;i<=m;i++) a=read(), b=read(), pb[a].push_back(b), pb[b].push_back(a);
    for(int i=1;i<=n;i++) pb[i].push_back(i);
    q=read();
    for(int i=1;i<=q;i++) qwq[i]=read(), qaq[i] = read(), c[i] = read();
    for(int i=q;i>=1;i--) Work(qwq[i], qaq[i], c[i]);
    for(int i=1;i<=n;i++) std::cout<<cor[i][0]<<std::endl;
    return 0;
}
```


---

