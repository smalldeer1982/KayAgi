# [USACO10HOL] Cow Politics G

## 题目描述

Farmer John's cows are living on N (2 <= N <= 200,000) different pastures conveniently numbered 1..N. Exactly N-1 bidirectional cow paths (of unit length) connect these pastures in various ways, and each pasture is reachable from any other cow pasture by traversing one or more of these paths (thus, the pastures and paths form a graph called a tree).

The input for a particular set of pastures will specify the parent node P\_i (0 <= P\_i <= N) for each pasture. The root node will specify parent P\_i == 0, which means it has no parent.

The cows have organized K (1 <= K <= N/2) different political parties conveniently numbered 1..K. Each cow identifies with a single

political party; cow i identifies with political party A\_i (1 <= A\_i <= K). Each political party includes at least two cows.

The political parties are feuding and would like to know how much 'range' each party covers. The range of a party is the largest distance between any two cows within that party (over cow paths).

For example, suppose political party 1 consists of cows 1, 3, and 6, political party 2 consists of cows 2, 4, and 5, and the pastures are connected as follows (party 1 members are marked as -n-):

-3-
|
-1-
/ | \
2  4  5

|
-6-
The greatest distance between any two pastures of political party 1 is 3 (between cows 3 and 6), and the greatest distance for political party 2 is 2 (between cows 2 and 4, between cows 4 and 5, and between cows 5 and 2).

Help the cows determine party ranges.

TIME LIMIT: 2 seconds

MEMORY LIMIT: 64MB

农夫约翰的奶牛住在N (2 <= N <= 200,000)片不同的草地上，标号为1到N。恰好有N-1条单位长度的双向道路，用各种各样的方法连接这些草地。而且从每片草地出发都可以抵达其他所有草地。也就是说，这些草地和道路构成了一种叫做树的图。输入包含一个详细的草地的集合，详细说明了每个草地的父节点P\_i (0 <= P\_i <= N)。根节点的P\_i == 0, 表示它没有父节点。因为奶牛建立了1到K一共K (1 <= K <= N/2)个政党。每只奶牛都要加入某一个政党，其中， 第i只奶牛属于第A\_i (1 <= A\_i <= K)个政党。而且每个政党至少有两只奶牛。 这些政党互相吵闹争。每个政党都想知道自己的“范围”有多大。其中，定义一个政党的范围是这个政党离得最远的两只奶牛（沿着双向道路行走）的距离。


## 样例 #1

### 输入

```
6 2 
1 3 
2 1 
1 0 
2 1 
2 1 
1 5 
```

### 输出

```
3 
2 
```

# 题解

## 作者：jiangchenyangsong (赞：7)

## 题意
一个树上每一个点都有一个组别，求相同组别的点对相差的最大距离。
## 分析
首先对于任意一个组别，深度最大的点一定在答案的点对里。
### 证明
> 假设答案的点对里没有深度最大的点,设深度最大的点为 $x$,设点对中的点为 $y,z$，假设 $d[y]\leq d[z]\leq d[x] $，$t$ 为 $y,z$ 的 $lca$。

> 1.若 $z,y$ 属于 $t$ 的不同子树，因为 $d[y]\leq d[x]$，$d[z]\leq d[x] $，若 $x$ 不在 $t$ 的子树内，那么，把 $y$ 换为 $x$ 会更优。若 $x$ 在 $t$ 的子树内，如果 $lca(x,z)=t$，显然可以将 $y$ 换成 $x$。如果 $lca(x,z)\ne t$，那么很明显，将 $z$ 换成 $x$ 一定比点对   $y,z$ 的答案更优，或者点对 $x,z$ 比点对 $x,y$ 更优，显然不论哪种情况，$x$ 都在答案里。

> 2.若 $z,y$ 属于 $t$ 的同一棵子树，即 $y=t$，因为 $d[y]\leq d[x]$，$d[z]\leq d[x] $，若 $x$ 不在 $y$  的子树内，那么把 $y$ 换成 $x$ 会更优，若在 $y$ 子树内，那么显然把 $z$ 换成 $x$ 更优。

所以，对于不同组别，我们只需要求出深度最大的点即可，在 $O(n)$ 枚举每一个点，与同组别深度最大的点求一遍 $lca$ 更新答案。

### $code$
```
#include<bits/stdc++.h>
#define N 200005
using namespace std;
int read(){
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-f;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}
	return x*f;
}
queue<int> q;
int n,k,root,tot,t;
int a[N],p[N],d[N],f[N][25],maxd[N],ans[N],pos[N];
int Head[N],to[N<<1],Next[N<<1];
void add(int u,int v){to[++tot]=v,Next[tot]=Head[u],Head[u]=tot;}
void bfs(int s){
	q.push(s);d[s]=1,maxd[a[s]]=1;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=Head[x];i;i=Next[i]){
			int y=to[i];if(d[y]) continue;
			d[y]=d[x]+1,f[y][0]=x;
			if(maxd[a[y]]<d[y]) pos[a[y]]=y;
			maxd[a[y]]=max(maxd[a[y]],d[y]);
			for(int j=1;j<=t;j++) f[y][j]=f[f[y][j-1]][j-1];
			q.push(y); 
		}
	}
}
int lca(int x,int y){
	if(d[x]>d[y]) swap(x,y);
	for(int j=t;j>=0;--j)
		if(d[f[y][j]]>=d[x]) y=f[y][j];
	if(x==y) return x;
	for(int j=t;j>=0;--j)
		if(f[y][j]!=f[x][j]) x=f[x][j],y=f[y][j];
	return f[x][0];
}
int DIS(int x,int y){return d[x]+d[y]-2*d[lca(x,y)];}
signed main(){
	n=read(),k=read();
	for(int i=1;i<=n;++i){
		a[i]=read(),p[i]=read();
		if(p[i]==0) root=i;
		else add(i,p[i]),add(p[i],i);
	}
	t=log(n)/log(2)+1;
	bfs(root);
	for(int i=1;i<=n;++i) ans[a[i]]=max(ans[a[i]],DIS(pos[a[i]],i));
	for(int i=1;i<=k;++i) printf("%d\n",ans[i]);
 	return 0;
}
```


---

## 作者：Steven_Meng (赞：7)


[传送门](https://www.luogu.org/problemnew/show/P2971)

[你真的不到我的博客看一眼吗？](https://gaisaiyuno.github.io/archives/b13f4097.html)

扫了一眼题解，发现没有一个严谨证明的，那么我就来证明一波吧。

首先，我们看一看如何求树的直径：

$1.$随便定一个根节点，第一遍$bfs$求出树中深度最深的节点，记为$u$。

$2 .$以$u$为根节点，第二遍$bfs$求出树中深度最深的点$v$

$3.$树的直径的端点即为$u,v$

------------------

类比到此题：

我们把政党$p$中的牛最深的记为$\max p$

发现：**$p$政党最长的链一定是某个$p$政党的牛和$\max p$构成的**（类似于树的直径）

考虑如何证明这个结论，采用反证法（自己画一个图比较好理解）：

>  声明：为了简化证明，我们记$ab$为树上$ab$两点的最短路径，$dep(a)$为节点$a$在树中的深度。

设某个$p$政党的牛$a$和另一个深度小于$\max p $的牛$b$构成了最长的链。

首先，我们求出$lca (a,b)$，设为$c$，求出$lca(a,\max p)$，设为$c'$。

我们可以知道，$c'$，$c$有直接的祖先关系，也有可能$c=c'$，简单来说，就是在同一条到根节点的链上。（这一点参见虚树的证明）

考虑两种情况：

$1.c'$的祖先为$c$（如图），那我们有$c'\max p+cc'+dep(c)=dep({\max p})$，且$cb+dep(c)=dep(b)$，

由$dep(b) < dep({\max p})$，两式相减，发现$dep(c)$抵消，我们有$cb<c' \max p+cc'...x$

发现$ab=ac'+c'c+cb$，且$a\max p=ac'+c'\max p$，将$x$式代入，我们有$ab=ac'+c'c+cb<ac'+c'c+c'\max p+c'c=a\max p+cc' \times 2$

由于$c'$的祖先为$c$，所以$cc'>0$，所以$ab<a\max p$，假设错误。

![](https://cdn.luogu.com.cn/upload/pic/65121.png)

$2.c$的祖先为$c'$，证明方法差不多，不再赘述。

所以，我们求一波$LCA$，然后预处理出$\max p$，最后暴力扫过一遍所有的牛，求出答案。

时间复杂度$O(n\log n)$

```cpp
#include <bits/stdc++.h>
#define MAXN 200005
#define MAXM 25
using namespace std;
inline int read(){
    int x=0,f=1;
    char ch=getchar();
    while (ch<'0'||ch>'9'){
        if (ch=='-') f=-1;
        ch=getchar();
    }
    while (ch>='0'&&ch<='9'){
        x=(x<<3)+(x<<1)+(ch^'0');
        ch=getchar();
    }
    return x*f;
}
vector<int>G[MAXN];
inline void AddEdge(int u,int v){
    G[u].push_back(v);
}
int anc[MAXN][MAXM],dep[MAXN],n,m;
void dfs(int u,int father){
    anc[u][0]=father;
    for (register int i=1;i<MAXM;++i){
        anc[u][i]=anc[anc[u][i-1]][i-1];
    }
    for (register int i=0;i<G[u].size();++i){
        int v=G[u][i];
        if (v!=father){
            dep[v]=dep[u]+1;
            dfs(v,u);
        }
    }
}
inline int LCA(int u,int v){
    if (dep[u]<dep[v]) swap(u,v);
    for (register int i=MAXM-1;i>=0;--i){
        if (dep[anc[u][i]]>=dep[v]){
            u=anc[u][i];
        }
    }
    if (u==v) return u;
    for (register int i=MAXM-1;i>=0;--i){
        if (anc[u][i]!=anc[v][i]){
            u=anc[u][i];
            v=anc[v][i];
        }
    }
    return anc[u][0];
}
inline void Init(int root){
    memset(dep,0,sizeof(dep));
    dfs(root,0);
}
int val[MAXN],maxu[MAXN],maxdep[MAXN],ans[MAXN];
inline int Dis(int u,int v){
    return dep[u]+dep[v]-2*dep[LCA(u,v)];
}
int main(){
    int n=read(),k=read();
    int root;
    for (register int i=1;i<=n;++i){
        int a=read(),p=read();
        val[i]=a;
        AddEdge(i,p),AddEdge(p,i);
        if (!p) root=i;
    }
    Init(root);
    for (register int i=1;i<=n;++i){//预处理
        if (dep[maxu[val[i]]]<dep[i]) maxu[val[i]]=i;
    }
    for (register int i=1;i<=n;++i){
        ans[val[i]]=max(ans[val[i]],Dis(maxu[val[i]],i));
    }
    for (register int i=1;i<=k;++i){
        printf("%d\n",ans[i]);
    }
}
```



---

## 作者：Ccliang (赞：6)

这道题中，我们首先可以确定最长的距离的两个点，其中一定有一个是这个政党中深度最深的。

至于证明题解里第一篇就给出了，我这里就不啰嗦，~~其实是我也不会，我实在太菜了~~。

然后因为边的长度都相等，且都为1，所以他们的距离可以直接用他们的深度算，就等于两个节点的深度和减去两倍的两节点的最近公共祖先的深度。即

```cpp
L = deep(x) + deep (y) - 2 * deep ( LCA (x,y) )
```

而点的深度是可以预处理出来的，只需要从没有出度的节点往上遍历一边就好，

在遍历过程中还可以顺便把每个政党的最深的节点找出来。

```cpp
int dfs(int k)
{
    if(dep[k]==-1)//如果还没被处理就一直往上递归找到已经处理的节点
    {
        dep[k]=dfs(father[k]);//当前节点的深度即他的父亲节点的深度+1
        if(dep[zdmax[zd[k]]]<dep[k])
            zdmax[zd[k]]=k;//更新政党的最深节点
    }
    return dep[k]+1;
}
int main()
{
    for(int i=1;i<=n;i++)
        if(out[i]==0)
        {
            dep[i]=dfs(father[i]);
            if(dep[zdmax[zd[i]]]<dep[i])
                zdmax[zd[i]]=i;
        }
}
```

找出了每个点的深度和每个政党的最深的节点，这道题就基本做完了。

接下来只需要枚举每一个政党的最深的节点，然后找出到其他节点的最大距离就可以了。

但是，在找最近公共祖先时，用朴素算法会被卡掉，我一开始就被卡掉了，只有35分。

必须要改成倍增求LCA。

```cpp
int LCA(int u,int v)
{
    if(dep[u]<dep[v])swap(u,v);
    int dist=dep[u]-dep[v];//求出深度差
    for(int i=0;(1<<i)<n;i++)
        if((1<<i)&dist)u=f[u][i];//将两个节点调至同一高度
    if(u==v)return u;
    for(int i=logn;i>=0;i--)
        if(f[u][i]!=f[v][i])
            u=f[u][i],v=f[v][i];
    return f[u][0];
}
void init()
{
    for(int i=1;(1<<i)<=n;i++)
        for(int j=1;j<=n;j++)
            f[j][i]=f[f[j][i-1]][i-1];
}//预处理 f 数组
/*
    f[i][j]表示从 i 开始，往上跳 2^j 步所到的节点
*/
```
不懂倍增的同学可以去网上找找资料。

但是还有一个问题，我在改成倍增求LCA的算法后，还是被卡掉了两个点，找了一阵发现在求答案时暴力枚举每一个点到当前政党的最深节点的距离，时间复杂度太高了，为 O(NK)。


```cpp
    for(int i=1;i<=k;i++)
    {
        for(int j=1;j<=n;j++)
            if(r[j].zd==i&&zdmax[i]!=j)
            {
                int u=LCA(zdmax[i],j);
                ans[i]=max(ans[i],r[zdmax[i]].dep+r[j].dep-(r[u].dep<<1));
            }
        printf("%d\n",ans[i]);
    }
```

就像我这样，肯定会超时。
我们可以像我们用链式前向星存边那样，维护3个数组，分别代表编号为 i 的政党的第一个节点，编号为 i 的节点的下一个相同政党的编号，以及上一个的编号。

int zz[N],nz[N],fz[N];

zz为上一个相同政党节点的编号，nz为下一个，fz为编号为 i 的政党出现的第一个节点的编号
```cpp
    for(int i=1;i<=k;i++)
    {
        for(int j=fz[i];j<=n;j=nz[j])
            if(zdmax[i]!=j)
            {
                int u=LCA(zdmax[i],j);
                ans[i]=max(ans[i],dep[zdmax[i]]+dep[j]-(dep[u]<<1));
            }
        printf("%d\n",ans[i]);
    }
```
这样就可以避免被卡了。

完整代码如下：
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 200000 + 10;
const int K = 100000 + 10;

int f[N][20],out[N];

int father[N],dep[N],zd[N];

int n,k,logn;

int zdmax[K],ans[K];

int zz[N],nz[N],fz[N];

int dfs(int k)
{
    if(dep[k]==-1)
    {
        dep[k]=dfs(father[k]);
        if(dep[zdmax[zd[k]]]<dep[k])
            zdmax[zd[k]]=k;
    }
    return dep[k]+1;
}

int LCA(int u,int v)
{
    if(dep[u]<dep[v])swap(u,v);
    int dist=dep[u]-dep[v];
    for(int i=0;(1<<i)<n;i++)
        if((1<<i)&dist)u=f[u][i];
    if(u==v)return u;
    for(int i=logn;i>=0;i--)
        if(f[u][i]!=f[v][i])
            u=f[u][i],v=f[v][i];
    return f[u][0];
}

void init()
{
    for(int i=1;(1<<i)<=n;i++)
        for(int j=1;j<=n;j++)
            f[j][i]=f[f[j][i-1]][i-1];
}

int main()
{
    scanf("%d%d",&n,&k);
    while((1<<logn)<n)logn++;
    memset(nz,0x3f,sizeof(nz));
    for(int i=1;i<=n;i++)
    {
        int a,p;scanf("%d%d",&a,&p);
        father[i]=p;
        zd[i]=a;
        dep[i]=-1;
        if(p==0)father[i]=i,dep[i]=0;
        f[i][0]=father[i];
        out[p]++;
        if(fz[a]==0)fz[a]=i;
        if(zz[a]==0)zz[a]=i;
        else nz[zz[a]]=i,zz[a]=i;
    }
    for(int i=1;i<=n;i++)
        if(out[i]==0)
        {
            dep[i]=dfs(father[i]);
            if(dep[zdmax[zd[i]]]<dep[i])
                zdmax[zd[i]]=i;
        }
    init();
    for(int i=1;i<=k;i++)
    {
        for(int j=fz[i];j<=n;j=nz[j])
            if(zdmax[i]!=j)
            {
                int u=LCA(zdmax[i],j);
                ans[i]=max(ans[i],dep[zdmax[i]]+dep[j]-(dep[u]<<1));
            }
        printf("%d\n",ans[i]);
    }
    return 0;
}
```

---

## 作者：冷月冰瞳 (赞：5)

首先需要知道在只有一个政党的情况下，题目弱化为求一个树中最远的两个点的距离，这个是可以用两遍BFS的方法求出，具体步骤为：

- 随便选择一个节点x，BFS求出距离x最远的节点y（有相同的随便选）。

- 以节点y为起点，BFS求出距离y最远的节点z（有相同的随便选）。

- 节点y和节点z之间的距离，就是这棵树中最远距离。


有了上面这个之后，在本题中，我们对每个政党都做一遍这个方法即可，但是我们不能进行BFS了。注意到BFS只是为了求距离最远的点，那么如果我们可以通过其他方法来求得任意两点间距离的话，步骤就可以转变为：

- 随便选择该政党的一个节点x，枚举该政党的其他节点，求出距离x最远的节点y。

- 以节点y为起点，枚举该政党的其他节点，求出距离y最远的节点z。

- 节点y和节点z的距离，就是该政党的最远距离。


对于求树上任意两点间的距离，一般转化为求LCA的，即


Dist(x, y) = Depth(x) + Depth(y) - 2 \* Depth(LCA(x, y))

求LCA的方法有很多，这里就不再描述了。


---

## 作者：Cesare (赞：4)

看到题解里面没有虚树的做法，来发一下。

## $Solution$

我们先从简单的情况入手，考虑 $k = 1$ 的情况怎么做。

很显然，此时的最长长度就是树的直径。

那么，如果 $k > 1$ 呢？是不是对于这些点建出的树来说，距离还是树的直径？

所以，可以考虑对每种颜色建一棵虚树，边权为两点之间的距离，然后跑树的直径即可。

复杂度 $O(n\ log\ n)$

## $Code:$

```cpp
#include <bits/stdc++.h>
#include <tr1/unordered_map>
//#include"Bignum/bignum.h"
//#define big bignum
#define lowbit(x) (x & -x)
#define debug(x) (cout << "#x = " << (x) << endl)
#define Set(x, i) memset (x, i, sizeof(x))
#define R register
#define For(i, j, k) for(R int i = (j), ED = (k); i <= ED; ++i)
#define Rep(i, j, k) for(R int i = (j), ED = (k); i >= ED; --i)
#define Cross(i, j, k) for(R int i = (j); i; i = (k))
using namespace std;
typedef long long ll;
const ll N = 200011;
const ll INF = 5e16;

namespace IO {

    inline char gc() {
        static char buf[100000], *p1 = buf, *p2 = buf;
        return (p1 == p2) && (p2 = (p1 = buf) +
            fread(buf, 1, 100000, stdin), p1 == p2)? EOF: *p1++;
    }

    #define dd ch = getchar()
    inline ll read() {
        R ll x = 0; R int f = 0; R char dd;
        for (; !isdigit(ch); dd) f ^= (ch == '-');
        for (; isdigit(ch); dd)  x = x * 10 + (ch ^ 48);
        return f? -x: x;
    }

    inline void write ( ll x ) {
        if (x < 0) x = -x, putchar('-');
        if (x > 9) write(x / 10); putchar(x % 10 | 48);
    }

    inline void wrn ( ll x ) { write(x), putchar(' '); }

    inline void wln ( ll x ) { write(x), putchar('\n'); }

    inline void wlnn ( ll x, ll y ) { wrn(x), wln(y); }

}

using IO::wln;
using IO::read;

namespace Cesare {
    
    ll n, k, cc, tot, Max, pos, Len[N];
    ll top = 0, root = 0, stk[N], dep[N];
    ll Zr[N], ID[N], col[N], dfn[N], f[21][N];
    
    vector <ll> Ve[N >> 1];
    
    inline bool cmp ( ll a, ll b ) { return dfn[a] < dfn[b]; }
    
    struct edge {
        ll To, Next;
    } e[N << 1];
    
    ll cnt = 0, head[N];
    
    inline void add ( ll u, ll v ) {
        e[++cnt].To = v, e[cnt].Next = head[u], head[u] = cnt;
        e[++cnt].To = u, e[cnt].Next = head[v], head[v] = cnt;
    }
    
    struct Edge {
        ll To, Next, w;
    } E[N << 1];
    
    ll Cnt = 0;
    
    tr1::unordered_map <ll, ll> Head;
    
    inline void Add ( ll u, ll v, ll w ) {
        E[++Cnt].To = v, E[Cnt].w = w, E[Cnt].Next = Head[u], Head[u] = Cnt;
        E[++Cnt].To = u, E[Cnt].w = w, E[Cnt].Next = Head[v], Head[v] = Cnt;
    }
    
    inline void dfs ( ll u, ll fa ) {
        dfn[u] = ++tot;
        f[0][u] = fa, dep[u] = dep[fa] + 1;
        For ( i, 1, 19 ) f[i][u] = f[i - 1][f[i - 1][u]];
        Cross ( i, head[u], e[i].Next ) if (e[i].To != fa) dfs(e[i].To, u);
    }
    
    inline ll LCA ( ll x, ll y ) {
        if (dep[x] < dep[y]) swap(x, y);
        Rep ( i, 19, 0 ) 
            if (dep[f[i][x]] >= dep[y]) x = f[i][x];
        if (x == y) return x;
        Rep ( i, 19, 0 ) 
            if (f[i][x] != f[i][y]) x = f[i][x], y = f[i][y];
        return f[0][x];
    }
    
    inline void Dfs ( ll u, ll fa ) {
//		if (nk == 491) debug(u);
        for (R int i = Head[u], v; i; i = E[i].Next)
            if (fa != (v = E[i].To)) {
				Len[v] = Len[u] + E[i].w;
//				cout << "!" << u << " -> " << v << " Cost = " << E[i].w << endl;
                if (Max < Len[v]) Max = Len[v], pos = v;
                Dfs(Zr[++cc] = v, u);
            }
    }
    
    inline void Insert ( ll u ) {
        if (top == 1) 
            return (void) (stk[++top] = u);
        ll lca = LCA(u, stk[top]);
        if (lca == stk[top]) 
            return (void) (stk[++top] = u);
        for (; top > 1 && dfn[lca] <= dfn[stk[top - 1]]; --top) {
            ll Lca = dep[LCA(stk[top - 1], stk[top])];
            ll dis = dep[stk[top - 1]] + dep[stk[top]];
            if (dis - 2 * Lca != 0)
                Add(stk[top - 1], stk[top], dis - 2 * Lca);
        }
        if (lca != stk[top]) {
            ll Lca = dep[LCA(lca, stk[top])];
            ll dis = dep[lca] + dep[stk[top]];
            if (dis - 2 * Lca != 0) 
                Add(lca, stk[top], dis - 2 * Lca), stk[top] = lca;
        } stk[++top] = u;
    }
    
    int main() {
        n = read(), k = read();
        for (R int i = 1, v; i <= n; ++i) {
            col[i] = read(), v = read();
            if (v == 0) root = i; else add(i, v);
        }
        dfs(root, 0);
        For ( i, 1, n ) Ve[col[i]].push_back(i);
        For ( i, 1, k ) {
            Cnt = 0;
            Head.clear();
            ll nk = Ve[i].size();
            For ( j, 1, nk ) ID[j] = Ve[i][j - 1];
            sort(ID + 1, ID + nk + 1, cmp);
            ll Lca = ID[1];
            For ( j, 2, nk ) Lca = LCA(Lca, ID[j]);
            top = 0, stk[++top] = Lca;
            For ( j, 1, nk ) Insert(ID[j]);
            for (ll dis, lca; top > 1; --top) {
                lca = dep[LCA(stk[top - 1], stk[top])];
                dis = dep[stk[top]] + dep[stk[top - 1]];
                if (dis - 2 * lca != 0) 
                    Add(stk[top - 1], stk[top], dis - 2 * lca);
            }
            
            For ( j, 1, nk ) ID[j] = 0;
            cc = Max = 0, Dfs(Lca, 0);
            For ( j, 1, cc ) Len[Zr[j]] = 0;
            cc = Max = 0, Dfs(pos, 0); wln(Max);
//			For ( i, 1, n ) For ( j, Head[i], E[j].Next ) 
//				cout << "!" << i << " -> " << E[j].To << endl;
        } return 0;
    }
    
}

int main()
{
//	freopen("testdata (19).in", "r", stdin);
//	freopen("test.out", "w", stdout);
    return Cesare::main();
}

/*

*/



```

---

## 作者：_Chris° (赞：3)

**没有用点分治的？**
~~我并不是没想到用LCA~~
那么这道题我们可以开一个桶维护扫到的当前子树中每个政党到重心的距离最大值
再取个max就完了，然后就是点分治板子啦

```c
#include<bits/stdc++.h>
#define maxn 200010
#define INF 0x7f7f7f7f
using namespace std;
int n,k,p,t,Maxl,root,Size;
int head[maxn],to[maxn*2],next[maxn*2];
int vis[maxn],size[maxn],ans[maxn],pail[maxn];
//pail就是每个政党到重心的距离最大值 
int a[maxn],dis[maxn],re[maxn];
//dis是每个点到重心的距离,re存扫过的点 
void add(int u,int v)
{
	to[++p]=v; next[p]=head[u];
	head[u]=p;
}
void Getroot(int x,int fa)
{
	int Max=0;size[x]=1;
	for(int i=head[x];i;i=next[i])
	{
		int v=to[i];
		if(v==fa||vis[v]) continue;
		Getroot(v,x);
		size[x]+=size[v];
		Max=max(Max,size[v]);
	}
	Max=max(Max,Size-size[x]);
	if(Maxl>Max) Maxl=Max,root=x;
}
void find(int x,int fa,int len)
{
	re[++t]=x; dis[x]=len;
	for(int i=head[x];i;i=next[i])
	{
		int v=to[i];
		if(vis[v]||v==fa) continue;
		find(v,x,len+1);
	}
}
void calc(int x)
{
	t=0; 
	for(int i=head[x];i;i=next[i])
	{
		int v=to[i];
		if(vis[v]) continue;
		int now=t;
		find(v,x,1);
		for(int j=now+1;j<=t;j++) 
		{
			if(pail[a[re[j]]])
			ans[a[re[j]]]=max(ans[a[re[j]]],dis[re[j]]+pail[a[re[j]]]);
			if(a[re[j]]==a[x])//注意特判一下重心与这个点是否政党相同 
			ans[a[re[j]]]=max(ans[a[re[j]]],dis[re[j]]);	
		}
		for(int j=now+1;j<=t;j++) pail[a[re[j]]]=max(pail[a[re[j]]],dis[re[j]]);
	}
	for(int i=1;i<=t;i++) pail[a[re[i]]]=0,re[i]=0;
}
void Divide(int x,int sum)//分治 
{
	vis[x]=1; calc(x);
	for(int i=head[x];i;i=next[i])
	{
		int v=to[i];
		if(vis[v]) continue;
		Maxl=INF;
		Size=size[v]<size[x]?size[v]:sum-size[x];
		Getroot(v,v);
		Divide(root,Size);
	}
}
int main()
{
	int x;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&a[i],&x);
		if(x) add(x,i),add(i,x);
	}	
	Maxl=INF; Size=n; Getroot(1,1);
	Divide(root,n);
	for(int i=1;i<=k;i++) printf("%d\n",ans[i]);
	return 0;
} 
```


---

## 作者：rui_er (赞：1)

似乎是一个很简洁的新做法。

显然 $k$ 个点集互不干扰，可以分开处理。

对于每个点集，首先取出两个点 $u,v$ 作为最远的两个点（为表述方便下文称为直径），然后考虑向点集中加入点 $w$ 的过程。我们计算出 $d_1=\operatorname{dis}(u,v),d_2=\operatorname{dis}(u,w),d_3=\operatorname{dis}(v,w)$，则点集的直径为 $\max\{d_1,d_2,d_3\}$。判断出哪两个点是新的直径，然后在这个新的直径的基础上继续加点即可。

正确性的话，类似于正常的树的直径，到一个点距离最远的点一定是一条直径的端点。若新的点要作为直径端点，只能是到原来直径两端距离有一个比原来直径要长。

时间复杂度 $\mathcal O(n\log n)$。

```cpp
// Problem: P2971 [USACO10HOL]Cow Politics G
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/P2971
// Memory Limit: 125 MB
// Time Limit: 1000 ms
// 
// Powered by CP Editor (https://cpeditor.org)

//By: OIer rui_er
#include <bits/stdc++.h>
#define rep(x,y,z) for(int x=(y);x<=(z);x++)
#define per(x,y,z) for(int x=(y);x>=(z);x--)
#define debug(format...) fprintf(stderr, format)
#define fileIO(s) do{freopen(s".in","r",stdin);freopen(s".out","w",stdout);}while(false)
using namespace std;
typedef long long ll;
const int N = 2e5+5;

int n, k, a[N], fa[N][19], dis[N], rt;
vector<int> d[N], e[N];
template<typename T> void chkmin(T& x, T y) {if(x > y) x = y;}
template<typename T> void chkmax(T& x, T y) {if(x < y) x = y;}
void dfs(int u) {
	dis[u] = dis[fa[u][0]] + 1;
	rep(i, 1, 18) fa[u][i] = fa[fa[u][i-1]][i-1];
	for(int v : e[u]) dfs(v);
}
int LCA(int u, int v) {
	if(dis[u] < dis[v]) swap(u, v);
	per(i, 18, 0) if(dis[fa[u][i]] >= dis[v]) u = fa[u][i];
	if(u == v) return u;
	per(i, 18, 0) if(fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
	return fa[u][0];
}
int dist(int u, int v) {
	return dis[u] + dis[v] - 2 * dis[LCA(u, v)];
}

int main() {
	scanf("%d%d", &n, &k);
	rep(i, 1, n) {
		scanf("%d%d", &a[i], &fa[i][0]);
		if(!fa[i][0]) rt = i;
		d[a[i]].push_back(i);
		e[fa[i][0]].push_back(i);
	}
	dfs(rt);
	rep(i, 1, k) {
		int u = d[i][0], v = d[i][1], sz = d[i].size();
		for(int j=2;j<sz;j++) {
			int w = d[i][j];
			int d1 = dist(u, v), d2 = dist(u, w), d3 = dist(v, w);
			int diameter = max(d1, max(d2, d3));
			int U = 0, V = 0;
			if(d1 == diameter) U = u, V = v;
			else if(d2 == diameter) U = u, V = w;
			else U = v, V = w;
			u = U; v = V;
		}
		printf("%d\n", dist(u, v));
	}
	return 0;
}
```

---

## 作者：pocafup (赞：1)

说句闲话，我在洛谷上 WA 了第 13 个点，但数据下载下来发现是对的，所以做法没问题，只是有UB，然后懒得查了（

发现这个题题解只有一个点分治，感觉需要稍微详细一点的讲解。

点分治具体做法请查阅[模板](https://www.luogu.com.cn/problem/P3806)，这里仅提供思考过程。

首先假设所有奶牛都为同一种类，那么问题等价于求树上的最远点对。若使用点分治，则我们珂以考虑记录每个节点的深度，然后合并子树时候取两边的叶节点深度和即可。

那么现在问题强化为不同种类的牛，发现光记录叶节点并没有办法保证记录到所有种类的牛。但是，由于节点的数量固定，每个节点的路径是有限的，因此我们考虑把每种奶牛都当成独立的一颗树，在记录路径时分别记录每个节点的深度和他的种类
```cpp
inline void getdis(int u, int fa, int dep=1){
    cor[++cnt] = pos[u];//cor记录节点的种类,judge记录深度
    judge[cnt] = dep;
    trav(i,u){
      int v = edge[i].v;
      if (vis[v] || v==fa) continue;
      getdis(v,u,dep+1);
    }
  }
```

在合并的时候我们只合并相同种类的奶牛。注意如果这个题的 $k$ 扩大到 $10^9$，那我们需要将其离散化（当然这题没有要求）。

```cpp
inline void calc(int u){
    int ptr = 0;
    trav(i,u){
      int v = edge[i].v;
      if (vis[v]) continue;
      cnt = 0;
      getdis(v,u);
      For(j,1,cnt) if (all[cor[j]]) Ans[cor[j]] = chkmax(Ans[cor[j]],all[cor[j]]+judge[j]);//Ans[i]是第 i 种牛的最大距离
      For(i,1,cnt) q[++ptr] = cor[j],all[cor[j]] = chkmax(all[cor[j]],judge[j]),judge[j] = cor[j] = 0;//点分治更新当前链子最大值,基本操作
    }
    For(i,1,ptr) all[q[i]] = 0;
  }
  }
```

最后直接输出每个 Ans 即可。

不加头文件的代码:

```cpp
const int MAXN = 1e7+5;
const int MAXM = 1e7+5;
const int MAXK = 1e7+5;
const int mod = 1e9+7;
int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};
int n,m,t,l,k,a,b,c,pos[MAXN],ans;
namespace AdjEdge{
  //var
  int head[MAXN],tot;
  struct Edge{
    int u,v,d,nxt;
  }edge[MAXM<<1];
  inline void add(int u, int v, int d=0){
    edge[++tot].u = u;
    edge[tot].v = v;
    edge[tot].d = d;
    edge[tot].nxt = head[u];
    head[u] = tot;
  }
}
using namespace AdjEdge;
namespace Centroid_Decomposition{
  int rt=0,judge[MAXK],all[MAXK],dp[MAXN],son[MAXN],sz[MAXN],cnt,Ans[MAXN],sum,Q[MAXN],dis[MAXN],cor[MAXN];
  bool vis[MAXN];
  inline void getroot(int u, int fa=-1){
    dp[u] = 0, sz[u] = 1;
    trav(i,u){
      int v = edge[i].v;
      if (vis[v] || v==fa) continue;
      getroot(v,u);
      sz[u]+=sz[v];
      dp[u] = chkmax(dp[u],sz[v]);
    }
    dp[u] = chkmax(dp[u],sum-sz[u]);
    if (dp[u]<dp[rt]) rt = u;
  }
  inline void getdis(int u, int fa, int dep=1){
    cor[++cnt] = pos[u];//cor记录节点的种类,judge记录深度
    judge[cnt] = dep;
    trav(i,u){
      int v = edge[i].v;
      if (vis[v] || v==fa) continue;
      getdis(v,u,dep+1);
    }
  }
  int q[MAXK];
  inline void calc(int u){
    int ptr = 0;
    trav(i,u){
      int v = edge[i].v;
      if (vis[v]) continue;
      cnt = 0;
      getdis(v,u);
      For(j,1,cnt) if (all[cor[j]]) Ans[cor[j]] = chkmax(Ans[cor[j]],all[cor[j]]+judge[j]);//Ans[i]是第 i 种牛的最大距离
      For(i,1,cnt) q[++ptr] = cor[j],all[cor[j]] = chkmax(all[cor[j]],judge[j]),judge[j] = cor[j] = 0;//点分治更新当前链子最大值,基本操作
    }
    For(i,1,ptr) all[q[i]] = 0;
  }
  inline void divide(int u=rt){
    vis[u] = true;
    calc(u);
    trav(i,u){
      int v = edge[i].v;
      if (vis[v]) continue;
      sum = sz[v]; dp[rt=0] = sz[v];
      getroot(v,u);
      divide(rt);
    }
  }
}
using namespace Centroid_Decomposition;
signed main(){
  n = read(); k = read();
  For(i,1,n){
    a = read(); b = read();
    if (b) add(i,b),add(b,i);
    pos[i] = a;
  }
  dp[rt] = sum = n;
  getroot(1);
  divide();
  For(i,1,k) writeln(Ans[i]);
}
```

---

## 作者：巨型方块 (赞：1)

把图建出来，然后记录每一种颜色的节点的最深点；

可以证明我们取的2个点一定包含这个最深点；

那么我们再枚举其他的点，用lca算一下距离

```cpp
#include<bits/stdc++.h>
#define Ll long long
using namespace std;
const Ll N=2e5+5;
struct cs{int to,nxt;}a[N*2],c[N*2];
int head[N],ll,tim,H[N],LL,f[N][20];
int v[N],X[N],Y[N],dep[N],md[N];
int n,m,x,y,z,k,S,ans;
void init(int x,int y){a[++ll].to=y;a[ll].nxt=head[x];head[x]=ll;}
void Init(int x,int y){c[++LL].to=y;c[LL].nxt=H[x];H[x]=LL;}
void dfs(int x,int y,int z){
    dep[x]=z;X[x]=++tim;
    if(dep[md[v[x]]]<z)md[v[x]]=x;
    for(int k=head[x];k;k=a[k].nxt)
        if(a[k].to!=y)dfs(a[k].to,x,z+1);
    Y[x]=++tim;
}
int lca(int x,int y){
    if(dep[x]<dep[y])swap(x,y);
    for(int j=19;j>=0;j--)if(dep[f[x][j]]>=dep[y])x=f[x][j];
    if(x==y)return x;
    for(int j=19;j>=0;j--)if(f[x][j]!=f[y][j])x=f[x][j],y=f[y][j];
    return f[x][0];
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&v[i],&f[i][0]);
        Init(v[i],i);
        if(f[i][0]==0)S=i;else init(f[i][0],i);
    }
    dfs(S,-1,1);
    for(int j=1;j<=19;j++)
        for(int i=1;i<=n;i++)
            f[i][j]=f[f[i][j-1]][j-1];
    for(int i=1;i<=m;i++){
        ans=0;x=md[i];
        for(int k=H[i];k;k=c[k].nxt){
            int y=lca(x,c[k].to);
            ans=max(ans,dep[x]-dep[y]+dep[c[k].to]-dep[y]);
        }
        printf("%d\n",ans);
    }
}

```

---

## 作者：Dispwnl (赞：1)

我找了半天错，结果发现LCA没处理父子关系。。。

先找出根，从根遍历，找出每个点的深度（就是LCA版子。。。）

找出每个政党最深的点，枚举这个政党其他点，用LCA求出它们间的距离，从而求出这个政党的最大范围

c++
```cpp
# include<iostream>
# include<cstdio>
# include<cstring>
using namespace std;
struct q{
    int x,y;
}c[500001];
int n,k,num,root;
int h[200001],use[200001],maxn[100001],deep[200001],ans[100001],maxn2[100001];
int p[500001][21];
int max(int x,int y)
{
    return x>y?x:y;
}
void add(int x,int y)
{
    c[++num].x=h[x];
    c[num].y=y;
    h[x]=num;
}
void dfs(int x)//求深度
{
    for(int i=h[x];i;i=c[i].x)
      {
          int t=c[i].y;
          if(t==p[x][0]) continue;
          deep[t]=deep[x]+1;
          p[t][0]=x;
          dfs(t);
      }
}
void init()//处理父子关系
{
    for(int j=1;(1<<j)<=n;j++)
      for(int i=1;i<=n;i++)
        p[i][j]=p[p[i][j-1]][j-1];
}
int lca(int x,int y)//LCA
{
    if(deep[x]>deep[y]) swap(x,y);
    int f=deep[y]-deep[x];
    for(int i=0;(1<<i)<=f;i++)
      if((1<<i)&f) y=p[y][i];
    if(x!=y)
    {
        for(int i=20;i>=0;i--)
          if(p[x][i]!=p[y][i])
          x=p[x][i],y=p[y][i];
        x=p[x][0];
    }
    return x;
}
int main()
{
    cin>>n>>k;
    for(int i=1;i<=n;i++)
      {
          int a1,a2;
          cin>>a1>>a2;
          use[i]=a1;
          add(a2,i);
          add(i,a2);
        if(!a2) root=i;
      }
    dfs(root);
    init();//就是这忘加了。。。
    for(int i=1;i<=n;i++)
      if(maxn[use[i]]<deep[i])
      {
          maxn[use[i]]=deep[i];//最深的点的深度
        maxn2[use[i]]=i;    //最深的点
      }
    for(int i=1;i<=n;i++)
      {
          int x=lca(maxn2[use[i]],i);//枚举
          ans[use[i]]=max(ans[use[i]],maxn[use[i]]-deep[x]+deep[i]-deep[x]);
      }
    for(int i=1;i<=k;i++)
      cout<<ans[i]<<endl;
    return 0;
}
```

---

## 作者：Chester (赞：0)

线段树合并  
线段树维护每种政党的最大深度。 子节点向父节点合并的同时更新答案。  
时间复杂度$O(NlogN)$, 空间$O(NlogN)$  
代码实现挺简单的，吸氧气490ms，算是挺优秀的？  
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define rd read()
#define N 200005
using namespace std;

int n, m, k, cnt;
int head[N], tot, bl[N], dep[N], ans[N];

struct edge {
    int nxt, to;
}e[N << 1];

queue<int> q;

int read() {
    int X = 0, p = 1; char c = getchar();
    for (; c > '9' || c < '0'; c = getchar())
        if (c == '-') p = -1;
    for (; c >= '0' && c <= '9'; c = getchar())
        X = X * 10 + c - '0';
    return X * p;
}

void add(int u, int v) {
    e[++tot].to = v;
    e[tot].nxt = head[u];
    head[u] = tot;
}

void cmax(int &A, int B) {
    if (A < B) A = B;
}

namespace SegT {
    struct node {
        int lson, rson, Max;
    }a[N * 50];
    int root[N];
#define lc(x) a[x].lson
#define rc(x) a[x].rson
#define Max(x) a[x].Max
#define mid ((l + r) >> 1)
    
    int get() {
        if (q.empty()) return ++cnt;
        int res = q.front(); q.pop();
        return res;
    }

    void del(int x) {
        Max(x) = lc(x) = rc(x) = 0;
        q.push(x);
    }

    void modify(int pos, int c, int l, int r, int &x) {
        if (!x) x = get();
        if (l == r) {
            cmax(Max(x), c); return;
        }
        if (pos <= mid) 
            modify(pos, c, l, mid, lc(x));
        else modify(pos, c, mid + 1, r, rc(x));
    }
    
    int merge(int x, int y, int l, int r, int lca) {
        if (!x || !y) return x + y;
        int now = get();
        if (l == r) {
            Max(now) = max(Max(x), Max(y));
            if (Max(x) && Max(y))
                cmax(ans[l], Max(x) + Max(y) - 2 * dep[lca]);
            del(x); del(y);
            return now;
        }
        lc(now) = merge(lc(x), lc(y), l, mid, lca);
        rc(now) = merge(rc(x), rc(y), mid + 1, r, lca);
        del(x); del(y);
        return now;
    }

    int query(int pos, int l, int r, int x) {
        if (!x) return 0;
        if (l == r) return Max(x);
        if (pos <= mid) return query(pos, l, mid, lc(x));
        else return query(pos, mid + 1, r, rc(x));
    }
}using namespace SegT;

void dfs(int u, int fa) {
    for (int i = head[u]; i; i = e[i].nxt) {
        int nt = e[i].to;
        if (nt == fa) continue;
        dep[nt] = dep[u] + 1;
        dfs(nt, u);
        root[u] = merge(root[u], root[nt], 1, k, u);
    }
    int tmp = query(bl[u], 1, k, root[u]);
    cmax(ans[bl[u]], tmp - dep[u]);
    modify(bl[u], dep[u], 1, k, root[u]);
}

int main()
{
    n = rd; k = rd;
    int fr;
    for (int i = 1; i <= n; ++i) {
        bl[i] = rd; int fa = rd;
        if (fa == 0) fr = i;
        else add(fa, i), add(i, fa);
    }
    dep[fr] = 1;
    dfs(fr, 0);
    for (int i = 1; i <= k; ++i) 
        printf("%d\n", ans[i]);
}

```


---

