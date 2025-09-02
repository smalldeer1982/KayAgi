# NN country

## 题目描述

In the NN country, there are $ n $ cities, numbered from $ 1 $ to $ n $ , and $ n - 1 $ roads, connecting them. There is a roads path between any two cities.

There are $ m $ bidirectional bus routes between cities. Buses drive between two cities taking the shortest path with stops in every city they drive through. Travelling by bus, you can travel from any stop on the route to any other. You can travel between cities only by bus.

You are interested in $ q $ questions: is it possible to get from one city to another and what is the minimum number of buses you need to use for it?

## 说明/提示

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF983E/c42b59e68a69956240c890e5363c8c983d1d430c.png) Routes for first sample are marked on the picture.

## 样例 #1

### 输入

```
7
1 1 1 4 5 6
4
4 2
5 4
1 3
6 7
6
4 5
3 5
7 2
4 5
3 2
5 3
```

### 输出

```
1
3
-1
1
2
3
```

## 样例 #2

### 输入

```
7
1 1 2 3 4 1
4
4 7
3 5
7 6
7 6
6
4 6
3 1
3 2
2 7
6 3
5 3
```

### 输出

```
1
-1
-1
1
-1
1
```

# 题解

## 作者：Acfboy (赞：26)

这题代码其实用不着百来行，如果用主席树实现的话。

遇到树上问题，首先想一想链上的情况。  
如果输入是一条链，我们向某个方向跳的时候一定是要尽可能坐车到远的地方，每次暴力找最远的肯定不行，容易想到可以倍增优化。

现在把链上的情况搬到树上。  
树上仍然是链的情况，因为要求最少乘车，而在树上两点之间不重复经过点的路径是唯一的，所以只要考虑询问的两个点之间的那条链就可以了。  
这里同样可以倍增，把路分成两段，然后两点往它们的 LCA 跳。可是有个问题，万一这个路跳过 LCA 了怎么办？

只需要判断一下是否有一条路能跨过 LCA 就好了！  
也就是说要判断有没有一辆车的线路的俩端点分别在两个查询的点在 LCA 上一次跳到的点的两个子树内，这就变成了二维数点问题，可以用扫描线来实现，但是我推荐主席树，因为似乎短一些。具体地，对每个端点点按 dfs 序在权值线段树插入另一个端点，查询时只需要查询一个端点的子树 dfs 区间内的值有是否大于 $0$ 即可。

其实出题人为了让我们代码少写一点还是做了些什么的，比如题目里保证了一个点的父亲一定比它小，这样从大到小就可以避免父亲的影响。  
还有个小 trick, 在一棵树上多次插入的时候可以插多棵树，最后把根指向最后那棵，这样就不用在写个修改函数了。

代码。

```cpp
#include <cstdio>
#include <vector>
#include <algorithm>
const int N = 200005;
int n, m, cnt, tim, f[N][20], d[N], g[N][20], rt[N], p[N], q[N];
std::vector<int> G[N], bus[N];
struct twt { int ls, rs, s; } t[N*40];
void dfs(int u) {
    p[u] = ++tim, d[u] = d[f[u][0]] + 1;
    for (int i = 0; i < (signed)G[u].size(); i++) dfs(G[u][i]);
    q[u] = tim;
}
int lca(int x, int y) {
    if (d[x] < d[y]) std::swap(x, y);
    int t = d[x] - d[y];
    for (int i = 0; i <= 19; i++)
        if (t & (1 << i)) x = f[x][i];
    if (x == y) return x;
    for (int i = 19; ~i; i--)
        if (f[x][i] != f[y][i]) x = f[x][i], y = f[y][i];
    return f[x][0];
}
void add(int &rt, int l, int r, int x) {
    t[++cnt] = t[rt], t[cnt].s ++;
    rt = cnt;
    if (l == r) return;
    int mid = l + (r-l) / 2;
    if (x <= mid) add(t[rt].ls, l, mid, x);
    else add(t[rt].rs, mid+1, r, x);
}
int Query(int rt, int l, int r, int x, int y) {
    if (!rt) return 0;
    if (l == x && r == y) return t[rt].s;
    int mid = l + (r-l) / 2;
    if (y <= mid) return Query(t[rt].ls, l, mid, x, y);
    else if (x > mid) return Query(t[rt].rs, mid+1, r, x, y);
    else return Query(t[rt].ls, l, mid, x, mid) +
                Query(t[rt].rs, mid+1, r, mid+1, y);
}
int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) 
        scanf("%d", &f[i][0]), G[f[i][0]].push_back(i);
    for (int j = 1; j <= 19; j++)   
        for (int i = 1; i <= n; i++) f[i][j] = f[f[i][j-1]][j-1];
    dfs(1);
    scanf("%d", &m);
    for (int i = 1; i <= n; i++) g[i][0] = i;
    for (int i = 1, x, y; i <= m; i++) {
        scanf("%d%d", &x, &y);
        int l = lca(x, y);
        g[x][0] = std::min(g[x][0], l), g[y][0] = std::min(g[y][0], l);
        bus[p[x]].push_back(p[y]), bus[p[y]].push_back(p[x]);
    }
    for (int i = n; i >= 1; i--) 
        g[f[i][0]][0] = std::min(g[f[i][0]][0], g[i][0]);
    for (int j = 1; j <= 19; j++)
        for (int i = 1; i <= n; i++) g[i][j] = g[g[i][j-1]][j-1];
    for (int i = 1; i <= n; i++) {
        rt[i] = rt[i-1];
        for (int j = 0; j < (signed)bus[i].size(); j++)
            add(rt[i], 1, n, bus[i][j]);
    }
    scanf("%d", &m);
    for (int i = 1, u, v; i <= m; i++) {
        scanf("%d%d", &u, &v);
        if (u == v) { puts("0"); continue; }
        int l = lca(u, v);
        if (g[u][19] > l || g[v][19] > l) { puts("-1"); continue; }
        int ans = 2;
        for (int i = 19; i >= 0; i--)
            if (g[u][i] > l) u = g[u][i], ans += (1 << i);
        for (int i = 19; i >= 0; i--)
            if (g[v][i] > l) v = g[v][i], ans += (1 << i);
        if (l == u || l == v) ans --;
        else ans -= !!(Query(rt[q[u]], 1, n, p[v], q[v]) - 
                       Query(rt[p[u]-1], 1, n, p[v], q[v]));
        printf("%d\n", ans);
    }
    return 0;
}
```

---

## 作者：EuphoricStar (赞：13)

## 思路

神奇贪心+倍增。

首先有一个贪心，就是预处理出每个点**能通过同一条路线到达的**深度最小的点，然后对于每个询问 $(x,y)$，先令 $dfn_x < dfn_y$，然后：

- 如果 $x,y$ 是祖先和后代关系，即 $\operatorname{lca}(x,y) = x$，那么就让 $y$ 向上跳 $dy$ 步直到和 $x$ 只差一步。显然如果跳不到 $x$ 就无解，否则答案为 $dy + 1$，因为每一次跳都切换了一次路线，且此时的 $y$ 和 $x$ 一定在同一条路线上。

- 如果 $x,y$ 不是祖先和后代关系，那么就让 $x$ 向上跳 $dx$ 步直到离 $lca$ 只差一步，$y$ 向上跳 $dy$ 步直到离 $lca$ 只差一步。显然如果 $x$ 或 $y$ 跳不到 $lca$ 就无解，否则如果此时 $x$ 和 $y$ 在同一条路线上，则答案为 $dx + dy + 1$；否则答案为 $dx + dy + 2$（因为 $x$ 必须再跳一步才能与 $y$ 在同一条路线上）。

发现暴力跳太慢了，所以用倍增优化，预处理出倍增数组 $f_{u,j}$ 表示 $u$ 向上跳 $2^j$ 步跳到哪个点。

接下来的问题就是如何判断两个点 $u,v$ 是否在同一条路线上。如果它们在同一条路线，那么 $u$ 的子树中一定存在一个点 $p$，使得**从 $p$ 出发的路线中有一条路线的终点在 $v$ 的子树内**。我们将每一棵子树转化为一段连续的 $dfn$ 区间 $[start_x, end_x]$，那么如果把一条路线看作平面上的一个点 $(dfn_a,dfn_b)$，则问题转化成了二维数点：统计横坐标在 $[start_u,end_u]$ 区间内，纵坐标在 $[start_v,end_v]$ 区间内是否存在点。这个可以用树状数组。

## 代码

[code](https://codeforces.com/contest/983/submission/157001707)

---

## 作者：封禁用户 (赞：9)

（吐槽一句这题的超大代码量……一堆dfs+一个树剖+一个倍增……）

首先这题我们可以采取树上倍增，即设$dp[i][j]$为点i往**上**走$2^j$条公交车路线能到达的最高点（不行则设为0，我们令$deep[0]=+∞$即可），这个$dp[i][0]$（即向上走一条路线到的最高点）我直接用的树剖，就是有一条路线$s->t$，然后就把这个路径上的点选择性赋值（就是赋值成深度尽量小的点）为$LCA(s,t)$，那个属于纯线段树部分这里就不提了。

然后对于每个询问$(a,b)$，我们用类似倍增$LCA$的方式让他们分别向上跳路线，**直到他们分别到LCA只剩最多一条可行路线为止**，如果跳不到LCA就一定无解，如果它们居然重合了那就不用管直接出答案。然后我们要做的工作就是判断现在的a和b是否能只通过一条过$LCA(a,b)$的路线直接到达，这样的话只需把答案+1，否则就把答案+2就是还得走不同的2条到LCA相遇，那么我们分两种情况：

①$a==LCA(a,b)||b==LCA(a,b)$，那么显然ab一定可以直达。

②ab在$LCA(a,b)$两侧，于是我们就要判断这条折起来的路径是不是被一条路线所覆盖，那就用离线的dfs处理，当到一个路线的一端，就把另一端+1，如果a的子树中存在能使b的子树和改变的点就说明这条路径被覆盖了，ab可互达。至于子树和就随便用个logn数据结构维护dfs序吧。

对了，在您倍增向上跳的时候别忘了把向上跳的路线计入答案，而且加的不是1，而是向上跳的那个$2^j$……（我因为这个WA了一片……）

上代码：

```cpp
#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
using namespace std;
void print(int num){
    if(num==-1){
        putchar('-');putchar('1');return;
    }if(num>=10)print(num/10);putchar(num%10+'0');
}
inline int get(){
    int n;char c;while((c=getchar())||1)if(c>='0'&&c<='9')break;
    n=c-'0';while((c=getchar())||1){
        if(c>='0'&&c<='9')n=n*10+c-'0';
        else return(n);
    }
}
typedef struct _b{
    int dest;int next;
}bian;bian memchi[1000001];int gn=1;int heads[200001];
inline void add(int s,int t){
    memchi[gn].dest=t;memchi[gn].next=heads[s];heads[s]=gn;gn++;
}
int dp[200001][21];int gdfn=1;
int dfn[200001],top[200001],deep[200001],size[200001],zhongson[200001],dad[200001];
//-------------
//  Warning!!!
//线段树部分，deep[0]=+inf
//-------------
typedef struct _n{
    int left;int right;int data;
}node;node nodes[1000001];int gnn=1;
inline void down(int tree){
    int ls=nodes[tree].left,rs=nodes[tree].right,cjr=nodes[tree].data;
    if(cjr!=0){
        if(deep[cjr]<deep[nodes[ls].data])nodes[ls].data=cjr;
        if(deep[cjr]<deep[nodes[rs].data])nodes[rs].data=cjr;
    }
}
int ints[200001];int n,root;
int bun[200001];
inline void incpt(int pt){
    for(register int i=pt;i<=n;i+=(i&-i))bun[i]++;
}
inline int getpt(int pt){
    int ans=0;for(register int i=pt;i>0;i-=(i&-i))ans+=bun[i];return(ans);
}
inline int getsum(int l,int r){
    return(getpt(r)-getpt(l-1));
}
int build(int l,int r){
    int tree=gnn;gnn++;nodes[gnn].data=0;if(l!=r){
        int mid=(l+r)>>1;nodes[tree].left=build(l,mid);nodes[tree].right=build(mid+1,r);
    }return(tree);
}int num;
void change(int rl,int rr,int l,int r,int tree){
    if(deep[nodes[tree].data]<deep[num])return;
    if(rl==l&&rr==r){
        nodes[tree].data=num;return;
    }int mid=(l+r)>>1;down(tree);if(rl>mid)change(rl,rr,mid+1,r,nodes[tree].right);
    else{
        if(rr<=mid)change(rl,rr,l,mid,nodes[tree].left);
        else{
            change(rl,mid,l,mid,nodes[tree].left);
            change(mid+1,rr,mid+1,r,nodes[tree].right);
        }
    }
}
void tui(int l,int r,int tree){
    if(l==r){
        ints[l]=nodes[tree].data;return;
    }
    int mid=(l+r)>>1;down(tree);tui(l,mid,nodes[tree].left);tui(mid+1,r,nodes[tree].right);
}
void dfs(int pt,int baba){int mx=0,best=0;top[pt]=pt;
    size[pt]=1;for(register int i=heads[pt];i;i=memchi[i].next){
        if(memchi[i].dest==baba)continue;
        dad[memchi[i].dest]=pt;deep[memchi[i].dest]=deep[pt]+1;dfs(memchi[i].dest,pt);
        size[pt]+=size[memchi[i].dest];if(size[memchi[i].dest]>mx)mx=size[memchi[i].dest],best=memchi[i].dest;
    }zhongson[pt]=best;
}
void dfs1(int pt,int baba){dfn[pt]=gdfn;gdfn++;
    if(zhongson[pt]){
        top[zhongson[pt]]=top[pt];dfs1(zhongson[pt],pt);
    }for(register int i=heads[pt];i;i=memchi[i].next){
        if(memchi[i].dest==baba||memchi[i].dest==zhongson[pt])continue;dfs1(memchi[i].dest,pt);
    }
}
inline int lca(int a,int b){
    while(top[a]!=top[b]){
        if(deep[top[a]]>deep[top[b]])swap(a,b);b=dad[top[b]];
        //printf("(%d,%d)\n",a,b);
    }if(deep[a]>deep[b])swap(a,b);return(a);
}
inline void setst(int s,int t,int _n){
    num=_n;
    while(top[s]!=top[t]){
        if(deep[top[s]]>deep[top[t]])swap(s,t);change(dfn[top[t]],dfn[t],1,n,root);
        //printf("change(%d,%d,%d)\n",dfn[top[t]],dfn[t],num);
		t=dad[top[t]];
    }if(deep[s]>deep[t])swap(s,t);change(dfn[s],dfn[t],1,n,root);//printf("change(%d,%d,%d)\n",dfn[s],dfn[t],num);
}
int ansq[200001];
typedef struct _psw{
    int other;int tmp;int query;
}eflags;
vector<eflags> cmd[200001];
vector<int> others[200001];
void dfs2(int pt,int baba){
	for(register int i=0;i<cmd[pt].size();i++){
		int her=cmd[pt][i].other;
		cmd[pt][i].tmp=getsum(dfn[her],dfn[her]+size[her]-1);
	}
	for(register int i=0;i<others[pt].size();i++){
		incpt(dfn[others[pt][i]]);
	}
	for(register int i=heads[pt];i;i=memchi[i].next){
		if(memchi[i].dest==baba)continue;
		dfs2(memchi[i].dest,pt);
	}
	for(register int i=0;i<cmd[pt].size();i++){
		int her=cmd[pt][i].other;
		if(getsum(dfn[her],dfn[her]+size[her]-1)==cmd[pt][i].tmp){
			ansq[cmd[pt][i].query]+=2;
		}else{
			ansq[cmd[pt][i].query]++;
		}
	}
}
int main(){
    n=get();for(register int i=2;i<=n;i++){
        int a=get();add(i,a);add(a,i);
    }deep[0]=1234567890;
    dfs(1,0);dfs1(1,0);root=build(1,n);
    int m=get();for(register int i=1;i<=m;i++){
        int s=get(),t=get();setst(s,t,lca(s,t));//printf("set path %d->%d,width %d\n",s,t,lca(s,t));
		others[s].push_back(t);others[t].push_back(s);
    }tui(1,n,root);for(register int i=1;i<=n;i++)dp[i][0]=ints[dfn[i]];
    for(register int i=1;i<=20;i++){
        for(register int j=1;j<=n;j++)dp[j][i]=dp[dp[j][i-1]][i-1];
    }
    //for(register int i=1;i<=n;i++){
    //	printf("dp[%d][0]=%d,dfn=%d\n",i,dp[i][0],dfn[i]);
	//}
    int q=get();for(register int i=1;i<=q;i++){
        int s=get(),t=get();int Lca=lca(s,t);eflags hh;
        //printf("Lca(%d,%d)=%d\n",s,t,Lca);
        for(register int j=20;j>=0;j--){
            if(dp[s][j]!=0&&deep[dp[s][j]]>deep[Lca])s=dp[s][j],ansq[i]+=(1<<j);
        }if(deep[dp[s][0]]>deep[Lca]&&s!=Lca){
            ansq[i]=-1;goto s;
        }for(register int j=20;j>=0;j--){
            if(dp[t][j]!=0&&deep[dp[t][j]]>deep[Lca])t=dp[t][j],ansq[i]+=(1<<j);
        }if(deep[dp[t][0]]>deep[Lca]&&t!=Lca){
            ansq[i]=-1;goto s;
        }
        if(s==t)goto s;
        //printf("new %d,%d\n",s,t);
        if(s==Lca||t==Lca){
        	ansq[i]++;goto s;
		}
        //若确实相同，ansq++，否则ansq+=2
        hh.tmp=0;hh.query=i;hh.other=t;
		cmd[s].push_back(hh);
        s:;
    }dfs2(1,0);
    for(register int i=1;i<=q;i++){
    	print(ansq[i]);putchar('\n');
	}
    return(0);
}
```

---

## 作者：Mobius127 (赞：6)

[题传](https://www.luogu.com.cn/problem/CF983E)

~~这似乎是个比较经典的问题~~

对于一类树上路径问题，我们优先考虑树形态为链怎么做。

首先，若当前有一条路线经过当前点，我们肯定是直接跳到这条线的终点（若能直接跳到终点也差不多），因为如果我们会在 $end$ 前面的位置跳到 $end$ 后面的位置，那这条路肯定也经过了 $end$，所以它肯定是不劣的。

然后我们从两端一直往中间跳，直到两端再跳一次就会相遇的时候停止，若此时有一条路径恰好覆盖了当前两端，则只用跳一次，否则要跳两次（还有无解的情况，只要判是否还能跳即可）。

接下来我们回到树上。

对于每一个询问 $(x, y)$，我们把它拆成 $(x, \operatorname{LCA}(x, y))$ 和 $(y, \operatorname{LCA}(x, y))$ 两条路径，同样跟前面一样，我们将 $x$ 和 $y$ 一起跳到 $\operatorname{LCA}(x, y)$ 最近的位置。接下来大力分讨：

1. 若 $x, y$ 其中有一个就是 $\operatorname{LCA}$，直接看能不能跳就好。

1. 当 $x, y$ 分布在 $\operatorname{LCA}$ 两侧时，我们同样需要判断是否有一条路径直接覆盖了 $x, y$ 即可。

接下来，我们要解决两个问题：

1. 我们在先前暴力跳的复杂度为 $O(m)$，需要优化

1. 怎么快速判断有没有路径同时覆盖了 $(x, y)$。

对于问题 1，由于我们每一次都是直接跳到末尾，所以不难想到使用倍增优化，对于 $ST_{x, 0}$，思考它的本质意义：从 $x$ 向上跳最远能到达的点。

因此，我们对于每一条路径，用 $\operatorname{LCA}(a, b)$ 去更新 $ST_{a, 0}$ 和 $ST_{b, 0}$，若子树某个珂以跑到字数外面，显然子树根也珂以通过那条路出去外面，拓扑倒序递推即可。

对于问题 2，转换问题：是否有一条路径的起始点分别在 $x, y$ 的子树内？

子树判别问题，使用 $\operatorname{dfs}$ 序，设一个二维平面上的点 $(s, t)$ 表示 $s$ 珂以存在单向路径 $(s, t)$ （注意题目里面是双向的，需要打两个），对于一个询问 $(x, y)$，由于子树内每一个结点的 $\operatorname{dfs}$ 序 $c$，有 $dfn_x \le c \le end_x$ ，所以实际上就是查询一个左上角坐标为 $(dfn_x, dfn_y)$、右下角坐标为 $(end_x, end_y)$ 的矩形是否存在一个点，这是个经典的二维数点问题，不会的话出门左转 [模板题](https://www.luogu.com.cn/problem/P2163)。

至此，本问题得到完美解决，复杂度 $O((n+Q)\log m)$。

### Code：

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
const int N=2e5+5;
int n, m, Q, ST[N][18], siz[N], top[N], son[N], dep[N], fa[N], dfn[N], Ed[N], dfn_cnt, ans[N];
vector <int> G[N];//Graph
inline int Mx(int a, int b){return dep[a]<dep[b]?a:b;}
void Get_dep(int x){
	siz[x]=1;dfn[x]=++dfn_cnt;
	for(int i=0, v; i<G[x].size(); i++) 
		dep[v=G[x][i]]=dep[x]+1, Get_dep(v), fa[v]=x,
		siz[x]+=siz[v], son[x]=siz[son[x]]>siz[v]?son[x]:v;
	Ed[x]=dfn_cnt;
}
void dfs(int x, int root){
	top[x]=root;if(son[x]) dfs(son[x], root);
	for(int i=0; i<G[x].size(); i++)
		if(G[x][i]!=son[x]) dfs(G[x][i], G[x][i]);
}
int LCA(int x, int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x, y);
		x=fa[top[x]];
	}
	return Mx(x, y);
}
void Dfs(int x){for(int i=0, v; i<G[x].size(); i++) Dfs(v=G[x][i]), (dep[ST[v][0]]<dep[x])?(ST[x][0]=Mx(ST[x][0], ST[v][0])):0;}
struct Box{int Lx, Ly, Rx, Ry, id;}box[N];int tot;
namespace CntingPoint{//二维数点 
	int res[N];
	pair <int, int> P[N*2];int tot;
	struct Ques{int Ly, Rx, Ry, id, tag;bool operator < (const Ques &X) const{return Rx<X.Rx;}}T[N*2]; 
	#define lowbit(x) ((x)&(-x)) 
	int bit[N*4], cnt, p[N*4];
	void add(int x){if(!x) return ;for(; x<=cnt; x+=lowbit(x)) bit[x]++;}
	int query(int x){int res=0;for(; x; x-=lowbit(x)) res+=bit[x];return res;}
	#undef lowbit
	int pos(int x){return lower_bound(p+1, p+cnt+1, x)-p;}
	signed Solve(int n, int m){
		for(int i=1; i<=n; i++)
			p[++cnt]=P[i].second;
		for(int i=1; i<=m; i++){
			int Lx=box[i].Lx, Ly=box[i].Ly, Rx=box[i].Rx, Ry=box[i].Ry;
			T[++tot]=(Ques){Ly, Rx, Ry, i, 1};T[++tot]=(Ques){Ly, Lx-1, Ry, i, -1};
			p[++cnt]=Ly-1, p[++cnt]=Ry;
		}
		sort(p+1, p+cnt+1), sort(T+1, T+tot+1), sort(P+1, P+n+1);
		cnt=unique(p+1, p+cnt+1)-p-1;int now=1;
		for(int i=1; i<=tot; i++){
			while(now<=n&&P[now].first<=T[i].Rx) add(pos(P[now++].second));
			res[T[i].id]+=T[i].tag*(query(pos(T[i].Ry))-query(pos(T[i].Ly-1)));
		}
		for(int i=1; i<=m; i++) if(res[i]) ans[box[i].id]--;
		return 0;
	}
}
inline bool Can(int lca, int x){return Mx(lca, x)==lca&&x!=lca&&x;}
signed main(){
	n=read();
	for(int i=2; i<=n; i++)
		G[read()].push_back(i);
	Get_dep(dep[1]=1);dep[0]=INF;dfs(1, 1);m=read();
	for(int i=1; i<=m; i++){
		int st=read(), ed=read();
		int lca=LCA(st, ed);
		CntingPoint :: P[i*2-1]=make_pair(dfn[st], dfn[ed]);
		CntingPoint :: P[i*2]=make_pair(dfn[ed], dfn[st]);
		ST[st][0]=Mx(ST[st][0], lca);
		ST[ed][0]=Mx(ST[ed][0], lca);
	}
	Dfs(1);for(int x=1; x<=n; x++) if(ST[x][0]==x) ST[x][0]=0;
	for(int j=1; j<18; j++)
		for(int i=1; i<=n; i++)
			ST[i][j]=ST[ST[i][j-1]][j-1];
	Q=read();
	for(int i=1; i<=Q; i++){
		int x=read(), y=read(), lca=LCA(x, y);
		for(int j=17; j>=0; j--)
			if(Can(lca, ST[x][j])) x=ST[x][j], ans[i]+=(1<<j);
		for(int j=17; j>=0; j--)
			if(Can(lca, ST[y][j])) y=ST[y][j], ans[i]+=(1<<j);
		if(x==lca||y==lca){
			if(y==lca) swap(x, y);
			if(Mx(ST[y][0], lca)==ST[y][0]) ans[i]++;
			else ans[i]=-1;
		}
		else{
			if(Can(lca, ST[x][0])&&Can(lca, ST[y][0])) ans[i]=-1;
			else if((!ST[x][0])||(!ST[y][0])) ans[i]=-1;
			else ans[i]+=2, box[++tot]=(Box){dfn[x], dfn[y], Ed[x], Ed[y], i};
		}
	}
	CntingPoint :: Solve(m*2, tot);
	for(int i=1; i<=Q; i++) printf("%d\n", ans[i]);
	return 0;
}
```






---

## 作者：mRXxy0o0 (赞：5)

# 分析

很明显，有一个贪心的性质，对于每一次选择路线，一定会选择从当前点能走得最远的一条。

这样就得到了一个暴力做法：预处理好每个点向祖先走得最远的一条路，对于每次询问，两个点暴力上跳，在最近公共祖先处特判一下是否可以一下走完即可。

考虑优化这个过程，找最近公共祖先和上跳都可以倍增处理。唯一的问题是最近公共祖先处的特判。

假设现在已经跳到了最靠上的点对 $(u,v)$，考虑是否有一条直通的线路连接它们。这是一个 DFS 序上的二维数点问题。

具体地，我们需要寻找一条线路满足起点在 $u$ 的子树中，终点在 $v$ 的子树中，由于一个子树在 DFS 序上是连续的，子树的限制就转化为区间的限制了，主席树处理即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
char buf[1<<21],*p1=buf,*p2=buf,obuf[1<<21],*p3=obuf;
inline char gc(){
	return p1==p2?p2=(p1=buf)+fread(buf,1,1<<21,stdin),*p1++:*p1++;
}
inline void pc(char ch){
	p3-obuf<1<<20?(*p3++=ch):(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=ch);
}
inline int read(){
	int res=0;
	char ch=gc();
	while(ch<'0'||ch>'9') ch=gc();
	while(ch>='0'&&ch<='9'){
		res=(res<<1)+(res<<3)+(ch^48);
		ch=gc();
	}
	return res;
}
inline void write(int x){
	if(x<0) pc('-'),x=-x;
	if(x>9) write(x/10);
	pc(x%10^48);
}
typedef long long ll;
typedef pair<int,int> pii;
const int N=2e5+10;
int n,m,q,h[N],ne[N],e[N],idx,f[N][20],dep[N],g[N][20],d[N],in[N],out[N],num,tot,root[N],ls[N];
pii line[N];
struct node{
	int ls,rs,sum;
}tr[N<<5];
inline void add(int u,int v){
	ne[++idx]=h[u],h[u]=idx,e[idx]=v;
}
inline void dfs(int u,int fa){
	in[u]=++num;
	dep[u]=dep[fa]+1;
	f[u][0]=fa;
	for(int i=1;1<<i<dep[u];++i) f[u][i]=f[f[u][i-1]][i-1];
	for(int i=h[u];i;i=ne[i]){
		dfs(e[i],u);
	}
	out[u]=num;
}
inline void dfs1(int u){
	for(int i=h[u];i;i=ne[i]){
		dfs1(e[i]);
		if(dep[g[e[i]][0]]<dep[g[u][0]]) g[u][0]=g[e[i]][0];
	}
//	cout<<u<<" "<<g[u][0]<<"\n";
}
inline void dfs3(int u){
	d[u]=d[g[u][0]]+1;
	for(int i=h[u];i;i=ne[i]){
		dfs3(e[i]);
	}
}
inline void dfs2(int u){
	if(g[u][0]==u) g[u][0]=0;
//	cout<<u<<" "<<d[u]<<"--\n";
	for(int i=1;1<<i<d[u];++i){
		g[u][i]=g[g[u][i-1]][i-1];
//		cout<<u<<" "<<i<<" "<<g[u][i]<<"\n";
	}
	for(int i=h[u];i;i=ne[i]){
		dfs2(e[i]);
	}
}
inline int lca(int u,int v){
	if(dep[u]<dep[v]) swap(u,v);
	for(int i=18;i>=0&&dep[u]>dep[v];--i){
		if(dep[u]-(1<<i)>=dep[v]) u=f[u][i];
	}
	if(u==v) return u;
	for(int i=18;i>=0;--i){
		if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	}
	return f[u][0];
}
inline void build(int &u,int l,int r){
	u=++tot;
	if(l==r) return ;
	int mid=l+r>>1;
	build(tr[u].ls,l,mid);
	build(tr[u].rs,mid+1,r);
}
inline void mdf(int u,int &v,int l,int r,int x){
	tr[v=++tot]=tr[u];
	++tr[v].sum;
	if(l==r) return ;
	int mid=l+r>>1;
	if(x<=mid) mdf(tr[u].ls,tr[v].ls,l,mid,x);
	else mdf(tr[u].rs,tr[v].rs,mid+1,r,x);
}
inline int query(int u,int v,int L,int R,int l,int r){
	if(l<=L&&R<=r) return tr[v].sum-tr[u].sum;
	int mid=L+R>>1,res=0;
	if(l<=mid) res+=query(tr[u].ls,tr[v].ls,L,mid,l,r);
	if(r>mid) res+=query(tr[u].rs,tr[v].rs,mid+1,R,l,r);
	return res;
}
inline int ef(int x){
	int l=1,r=m,res=m+1;
	while(l<=r){
		int mid=l+r>>1;
		if(line[mid].first>=x) res=mid,r=mid-1;
		else l=mid+1;
	}
	return res;
}
inline int ef1(int x){
	int l=1,r=m,res=0;
	while(l<=r){
		int mid=l+r>>1;
		if(line[mid].first<=x) res=mid,l=mid+1;
		else r=mid-1;
	}
	return res;
}
inline int exlca(int u,int v){
	if(u==v) return 1;
	int l=lca(u,v),mu=u,mv=v,res=0;
//	cout<<u<<" "<<v<<" "<<l<<" ";
	for(int i=18;i>=0;--i){
		if(d[mu]-(1<<i)>0) mu=g[mu][i];
		if(d[mv]-(1<<i)>0) mv=g[mv][i];
	}
//	cout<<mu<<" "<<mv<<"\n";
	if(dep[mu]>dep[l]||dep[mv]>dep[l]) return -1;
	for(int i=18;i>=0;--i){
		if(d[u]-(1<<i)>0&&dep[g[u][i]]>dep[l]) u=g[u][i],res+=(1<<i);
		if(d[v]-(1<<i)>0&&dep[g[v][i]]>dep[l]) v=g[v][i],res+=(1<<i);
	}
//	cout<<res<<" ";
	res+=(u!=l)+(v!=l);
	int Lu=ef(in[u]),Ru=ef1(out[u]),Lv=ef(in[v]),Rv=ef1(out[v]);
//	cout<<u<<" "<<Lu<<" "<<Ru<<" "<<v<<" "<<Lv<<" "<<Rv<<" ";
//	cout<<res<<" "<<query(root[Lu-1],root[Ru],1,n,in[v],out[v])<<" "<<query(root[Lv-1],root[Rv],1,n,in[u],out[u])<<" ";
	if(u!=l&&v!=l&&(Lu<=Ru?query(root[Lu-1],root[Ru],1,n,in[v],out[v]):0)+(Lv<=Rv?query(root[Lv-1],root[Rv],1,n,in[u],out[u]):0)>0) --res;
	return res;
}
int main(){
	n=read();
	for(int i=2,x;i<=n;++i){
		x=read();
		add(x,i);
		g[i][0]=i;
	}
	g[1][0]=1;
	dfs(1,0);
	m=read();
	for(int i=1,x,y,l;i<=m;++i){
		x=read();y=read();
		line[i]={in[x],in[y]};
		l=lca(x,y);
		if(dep[l]<dep[g[x][0]]) g[x][0]=l;
		if(dep[l]<dep[g[y][0]]) g[y][0]=l;
	}
	sort(line+1,line+1+m);
	build(root[0],1,n);
	for(int i=1;i<=m;++i){
		ls[i]=line[i].first;
		mdf(root[i-1],root[i],1,n,line[i].second);
	}
	dfs1(1);
	dfs3(1);
	dfs2(1);
	q=read();
	for(int i=1;i<=q;++i){
		int x,y;
		x=read();y=read();
//		cout<<x<<" "<<y<<" ";
		write(exlca(x,y)),pc('\n');
	}
	fwrite(obuf,p3-obuf,1,stdout);
	return 0;
}
```


---

## 作者：大菜鸡fks (赞：5)

发现可以贪心，贪心可以倍增优化。

贪心策略：把路径拆开成两条链，起始点和结尾点为祖先后代关系的链，显然是深度越浅越好

然后就可以暴力爬。发现一种特殊情况：有路径可以穿过lca

那么就判一下，是否有路径起始点在（倍增跳过后的停留点）子树中。

如何判？子树中的点的dfs序一定 in[rt]<=x<=out[rt]

两个变量就是二维数点问题咯。。

```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
inline int read(){int x=0,f=1,ch=getchar(); while(ch<'0'||ch>'9'){if(ch=='-') f=-1; ch=getchar();} while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} return x*f;}
inline void write(int x){if (x<0) putchar('-'),x=-x; if (x>=10) write(x/10); putchar(x%10+'0');}
inline void writeln(int x){write(x); puts("");}
const int N=2e5+5;
struct edge{
	int link,next;
}e[N<<1];
struct event{
	int x,y,id,opt;
}b[N*5];
int m,q,n,head[N],tot;
inline void add_edge(int u,int v){
	e[++tot]=(edge){v,head[u]}; head[u]=tot;
}
inline void insert(int u,int v){
	add_edge(u,v); add_edge(v,u);
}
int g[N][20],dep[N],fa[N][20],l[N],r[N],cnt;
void dfs(int u,int Fa){
	dep[u]=dep[Fa]+1; fa[u][0]=Fa; l[u]=++cnt;
	for (int i=1;i<20;i++) fa[u][i]=fa[fa[u][i-1]][i-1];
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v!=Fa) dfs(v,u);
	}
	r[u]=cnt;
}
inline int LCA(int u,int v){
	if (dep[u]<dep[v]) swap(u,v);
	int delta=dep[u]-dep[v];
	for (int i=0;i<20;i++) if (delta&(1<<i)) u=fa[u][i];
	for (int i=19;i>=0;i--) if (fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
	if (u!=v) return fa[u][0];
	return u;
}
inline void init(){
	n=read();
	for (int i=2;i<=n;i++) insert(i,read());
	dfs(1,0); m=read(); tot=0;
	for (int i=1;i<=m;i++){
		int u=read(),v=read(),lca=LCA(u,v);
		if (l[u]>l[v]) swap(u,v);
		if (!g[u][0]||dep[lca]<dep[g[u][0]]) g[u][0]=lca;
		if (!g[v][0]||dep[lca]<dep[g[v][0]]) g[v][0]=lca;
		b[++tot]=(event){l[u],l[v],0,1};
	}
}
void Dfs(int u,int Fa){
	for (int i=head[u];i;i=e[i].next){
		int v=e[i].link;
		if (v!=Fa){
			Dfs(v,u);
			if (!g[u][0]||g[v][0]&&dep[g[v][0]]<dep[g[u][0]]) g[u][0]=g[v][0];
		}
	}
}
inline bool cmp(event A,event B){
	return A.x<B.x||(A.x==B.x&&A.id<B.id);
}
int bit[N];
inline int lowbit(int x){
	return x&(-x);
}
inline void update(int x){
	for (;x<=n;x+=lowbit(x)) bit[x]++;
}
inline int query(int x){
	int sum=0;
	for (;x;x-=lowbit(x)) sum+=bit[x];
	return sum;
}
int ans[N],ANS[N];
inline void solve(){
	Dfs(1,0);
	for (int i=1;i<=n;i++) if (g[i][0]==i) g[i][0]=0;
	for (int i=1;i<20;i++)
		for (int j=1;j<=n;j++) g[j][i]=g[g[j][i-1]][i-1];
	q=read();
	for (int i=1;i<=q;i++){
		int u=read(),v=read(),lca=LCA(u,v);
		if (l[u]>l[v]) swap(u,v);
		for (int j=19;j>=0;j--) if (g[u][j]&&dep[g[u][j]]>dep[lca]) u=g[u][j],ans[i]+=(1<<j);
		for (int j=19;j>=0;j--) if (g[v][j]&&dep[g[v][j]]>dep[lca]) v=g[v][j],ans[i]+=(1<<j);
		if ((!g[u][0]&&u!=lca)||(!g[v][0]&&v!=lca)) {ans[i]=-1; continue;}
		if (u==lca||v==lca) ans[i]++;
			else {
				ans[i]+=2;
				b[++tot]=(event){r[u],r[v],i,1};
				b[++tot]=(event){l[u]-1,r[v],i,-1};
				b[++tot]=(event){r[u],l[v]-1,i,-1};
				b[++tot]=(event){l[u]-1,l[v]-1,i,1};
			}
	}
	sort(b+1,b+1+tot,cmp);
	for (int i=1;i<=tot;i++){
		if (!b[i].id) update(b[i].y);
			else ANS[b[i].id]+=b[i].opt*query(b[i].y);
	}
	for (int i=1;i<=q;i++) writeln(ans[i]-(ANS[i]>0));
}
int main(){
	init(); solve();
	return 0;
}
```

---

## 作者：Inui_Sana (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF983E)

解题思路：倍增+树剖+树状数组

对于每次询问，我们可以看成是两个点都不断往上跳（如果一个点是另一个点的祖先则是只有一个跳），有一个很明显的贪心策略：每次都跳到能跳到的深度最小的点。然而一次一次往上跳可能被极端数据卡掉，所以要用倍增维护跳 $2^i$ 次能跳到哪里。

然而两个点都跳到他们的 ```lca``` 上并不一定是最优方案，所以可以让两个点都跳到差一步能跳到 ```lca``` 的位置，然后判断是否有一条路直接联通两个点。对于这个问题，我们可以处理出 ```dfs``` 序，将每一条公交车线路看成是坐标系上 $(dfn_u,dfn_v)$ 的一个点，每次询问就是判断左下角是 $(dfn_u,dfn_v)$，右上角是 $end_u,end_v$ 的矩形内是否有点，其中 $end_i$ 表示 $i$ 的子树中点的 $dfn$ 的最大值。可以转化成二维偏序问题，用树状数组维护。[板子题链接](https://www.luogu.com.cn/problem/P2163)。其中要特判一下一个点是另一个点的祖先的情况，直接跳即可。

求 ```lca``` 推荐用树剖，顺便还可以处理出一个 ```dfn```。

code：

```cpp
int n,m,q,e[maxn],ans[maxn],res[maxn<<2],fm[maxn][22];
int siz[maxn],dep[maxn],fa[maxn],wt[maxn];
int cnt,top[maxn],dfn[maxn];
int tot,head[maxn];
bool vis[maxn];
struct node{
	int to,nxt;
}edge[maxn<<1];
struct zb{
	int x,y,id;
	bool operator<(const zb &tmp)const{return x<tmp.x;}
}qry[maxn<<2];
std::pii d[maxn<<1];
inline void add(int u,int v){
	edge[++tot]={v,head[u]};
	head[u]=tot;
}
inline int lowbit(int x){return x&(-x);}
inline void update(int x){
	while(x<=n)e[x]++,x+=lowbit(x);
}
inline int query(int x){
	int ret=0;
	while(x)ret+=e[x],x-=lowbit(x);
	return ret;
}
void dfs1(int u,int f){
	fa[u]=f;siz[u]=1;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==f)continue;
		dep[v]=dep[u]+1;
		dfs1(v,u);
		siz[u]+=siz[v];
		if(siz[v]>siz[wt[u]])wt[u]=v;
	}
}
void dfs2(int u,int t){
	top[u]=t;dfn[u]=++cnt;
	if(!wt[u])return;
	dfs2(wt[u],t);
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa[u]||v==wt[u])continue;
		dfs2(v,v);
	}
}
void dfs3(int u){//处理跳一次能跳到哪里
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa[u])continue;
		dfs3(v);
		if(~fm[v][0])fm[u][0]=dep[fm[v][0]]<dep[fm[u][0]]?fm[v][0]:fm[u][0];
	}
	if(fm[u][0]==u||!fm[u][0])fm[u][0]=-1;
}
void dfs4(int u){//倍增
	for(int i=1;i<=20;i++){
		if(~fm[u][i-1])fm[u][i]=fm[fm[u][i-1]][i-1];
		else fm[u][i]=-1;
	}
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].to;
		if(v==fa[u])continue;
		dfs4(v);
	}
}
int get_lca(int u,int v){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])swap(u,v);
		u=fa[top[u]];
	}
	return dep[u]<dep[v]?u:v;
}
int get_ans(int u,int v,int k){//两个/一个点往上跳
	int w=get_lca(u,v),ret=0;
	if(w==u){
		for(int i=20;~i;i--){
			if(~fm[v][i]&&dep[fm[v][i]]>dep[w])v=fm[v][i],ret+=(1<<i);
		}
		return ~fm[v][0]?ret+1:-1;
	}else if(w==v){
		for(int i=20;~i;i--){
			if(~fm[u][i]&&dep[fm[u][i]]>dep[w])u=fm[u][i],ret+=(1<<i);
		}
		return ~fm[u][0]?ret+1:-1;
	}else{
		for(int i=20;~i;i--){
			if(~fm[u][i]&&dep[fm[u][i]]>dep[w])u=fm[u][i],ret+=(1<<i);
		}
		for(int i=20;~i;i--){
			if(~fm[v][i]&&dep[fm[v][i]]>dep[w])v=fm[v][i],ret+=(1<<i);
		}
		vis[k]=true;	
	}
	int x=dfn[u],y=dfn[v],kk=k<<2;
	qry[kk-3]={x+siz[u]-1,y+siz[v]-1,kk-3};qry[kk-2]={x-1,y-1,kk-2};
	qry[kk-1]={x+siz[u]-1,y-1,kk-1};qry[kk]={x-1,y+siz[v]-1,kk};
	return ~fm[u][0]&&~fm[v][0]||fm[u][0]==v||fm[v][0]==u?ret:-1;
}
void solve(){
	read(n);
	for(int u=2,v;u<=n;u++){
		read(v);
		add(u,v);add(v,u);
	}
	dep[0]=inf;
	dfs1(1,0);dfs2(1,1);
	read(m);
	for(int i=1,u,v;i<=m;i++){
		read(u);read(v);
		d[(i<<1)-1]=mp(dfn[u],dfn[v]);d[(i<<1)]=mp(dfn[v],dfn[u]);
		int w=get_lca(u,v);
		fm[u][0]=dep[w]<dep[fm[u][0]]?w:fm[u][0];
		fm[v][0]=dep[w]<dep[fm[v][0]]?w:fm[v][0];
	}
	dfs3(1);dfs4(1);
	read(q);
	for(int i=1,u,v;i<=q;i++){
		read(u);read(v);
		ans[i]=get_ans(u,v,i);
	}
	const int mm=m<<1,qq=q<<2;
	sort(d+1,d+mm+1);sort(qry+1,qry+qq+1);
	for(int i=1,j=1;i<=qq;i++){
		while(j<=mm&&d[j].fi<=qry[i].x)update(d[j++].se);
		res[qry[i].id]=query(qry[i].y);
	}
	for(int i=1;i<=q;i++){
		int now=i<<2;
		if(vis[i]&&~ans[i]){
			if(res[now-3]+res[now-2]-res[now-1]-res[now]==0)ans[i]+=2;
			else ans[i]++;
		}
		write(ans[i]);putchar('\n');
	}
}
```

---

## 作者：LimpidSlirm (赞：1)

## 题意

给定一棵树和若干条路线，每条路线相当于 $a,b$ 之间的路径，途径路径上的每个点。

给出若干个询问，每次询问从 $x$ 到 $y$ 至少需要利用几条路线。

## Solution

考虑子问题，两个询问点在同一条链上，这样问题就类似 [SCOI2015] 国旗计划，只不过这道题是环上问题，但思路相同。

对于链，考虑贪心，对于每一个点 $fr_i$ 跳到能到达的最远的点 $to_i$，容易想到下一步应当是跳到 $to_{to_i}$，故考虑倍增优化这个不断往前跳的过程。定义 $jump_{i,k}$ 为点 $i$ 跳 $2^k$ 步能到达的最远节点，可以用 $\mathcal{O}(n\log n)$ 复杂度的时间来处理出 $jump$ 数组。

考虑树上的两个点，对于 $x$ 是 $y$ 的祖先节点（$y$ 为 $x$ 祖先节点时同理）的情况，同链上情况处理。

对于两个点分别不是对方父亲节点的情况，考虑将问题拆分为 $x$ 到 $lca$ 和 $y$ 到 $lca$ 两个问题处理。令 $ans_x$ 为 $x$ 跳到 $lca$ 的最小步数，$ans_y$ 为 $y$ 跳到 $lca$ 的最小步数，$pre_x$ 为 $x$ 向上跳 $ans_x-1$ 步到达的深度最浅的节点，即跳到 $lca$ 的前一个节点，$pre_y$ 同理。考虑两种情况：

- 有一条路线同时经过 $pre_x$ 和 $pre_y$；
- 不存在一条路线同时经过 $pre_x$ 和 $pre_y$。

对于第二种情况，答案即为 $ans_x+ans_y$，对于第一种情况，答案为 $ans_x+ans_y-1$。问题转化为如何维护是否存在一条路线经过两个点。

发现对于一个节点 $u$，只要 $u$ 的子树中存在一个点，使得存在一条从其出发的路径在 $v$ 的子树中结束，则存在一条路径同时经过 $u$ 和 $v$。考虑通过 dfs 序转化为区间问题，令 $size_i$ 为节点 $i$ 的子树大小，则问题进一步转化为询问是否存在一条路径 $(fr,to)$ 使得 $dfn_{fr}\in[dfn_x,dfn_x+size_x-1]$ ，$dfn_{to}\in[dfn_y,dfn_y+size_y-1]$。考虑二维数点，即查询平面上矩形 $[(dfn_x,dfn_y),(dfn_x+size_x-1,dfn_y+size_y-1)]$ 是否有点。将询问离线排序并用树状数组维护即可。

有个小细节：由于 $(fr,to)$ 和 $(to,fr)$ 在此题中是等价的，故在插入点时都应插入，否则可能会统计不到这个点。

其他具体实现细节见代码，以及由于我不会倍增求 $lca$，所以写了个树剖。

总时间复杂度应该是 $\mathcal{O}(n\log n)$ 的，但是有巨大常数，可以通过本题。

## code

```cpp
#include<bits/stdc++.h>
inline int read()
{
	int res=0,flag=1;
	char ch=getchar();
	while(!isalnum(ch)) (ch=='-')?flag=-1:1,ch=getchar();
	while(isalnum(ch)) res=res*10+ch-'0',ch=getchar();
	return res*flag;
}
struct edge 
{
	int to,nxt;
};
int n,m,q,tot=0;
int head[200010];
struct edge ed[400010];
void add_edge(int fr,int to)
{
	ed[++tot]=(edge){to,head[fr]};
	head[fr]=tot;
	return ;
}
namespace TreePartition
{
	struct node
	{
		int fa,son;
		int top;
		int size;
		int dep;
	};
	const int root=1;
	struct node nd[200010];
	void set(int fa,int fr)
	{
		nd[fr].size=1;
		nd[fr].fa=fa;
		nd[fr].dep=nd[fa].dep+1;
		for(int i=head[fr];i!=0;i=ed[i].nxt)
		{
			int to=ed[i].to;
			if(to==fa)
				continue;
			set(fr,to);
			nd[fr].size+=nd[to].size;
			if(nd[to].size>nd[nd[fr].son].size)
				nd[fr].son=to;
		}
		return ;
	}
	void dfs(int fa,int fr)
	{
		if(nd[fr].son!=0)
		{
			int to=nd[fr].son;
			nd[to].top=nd[fr].top;
			dfs(fr,to);
		}
		for(int i=head[fr];i!=0;i=ed[i].nxt)
		{
			int to=ed[i].to;
			if(to==fa||to==nd[fr].son)
				continue;
			nd[to].top=to;
			dfs(fr,to);
		}
		return ;
	}
	void init()
	{
		nd[root].dep=1;
		nd[root].top=root;
		set(0,root);
		dfs(0,root);
		return ;
	}
	int lca(int x,int y)
	{
		int fx=nd[x].top;
		int fy=nd[y].top;
		while(fx!=fy)
		{
			if(nd[fx].dep<nd[fy].dep)
				std::swap(x,y),std::swap(fx,fy);
			if(x==root)
				return root;
			x=nd[fx].fa;
			fx=nd[nd[fx].fa].top;
		}
		if(nd[x].dep>nd[y].dep)
			std::swap(x,y);
		return x;
	}
}
namespace BIT
{
	struct point
	{
		int x,y;
		bool operator <(const struct point &other)const
		{
			if(this->x==other.x)
				return this->y<other.y;
			return this->x<other.x; 
		}
	};
	struct question
	{
		int id;
		int val;
		int x,y;
		bool operator <(const struct question &other)const
		{
			if(this->x==other.x)
				return this->y<other.y;
			return this->x<other.x; 
		}
	};
	int pts,cnt;
	struct point points[800010];
	struct question questions[1600010];
	int data[400010];
	int lowbit(int x)
	{
		return x&(-x);
	}
	void modify(int pos,int val)
	{
		if(pos==0)
			return ;
		for(int i=pos;i<=n;i+=lowbit(i))
			data[i]+=val;
		return ;
	}
	int query(int pos)
	{
		int res=0;
		for(int i=pos;i>=1;i-=lowbit(i))
			res+=data[i];
		return res;
	}
};
namespace solve
{
	int dfncnt;
	int ans[200010],tmp[200010];
	int dfn[200010];
	int jump[200010][21];
	std::vector<int> graph[200010];
	void dfs(int fa,int fr)
	{
		dfn[fr]=++dfncnt;
		for(int i=head[fr];i!=0;i=ed[i].nxt)
		{
			int to=ed[i].to;
			if(to==fa)
				continue;
			dfs(fr,to);
		}
		return ;
	} 
	void set(int fa,int fr) 
	{
		using namespace TreePartition;
		jump[fr][0]=fr;
		for(auto Lca:graph[fr])
			if(nd[jump[fr][0]].dep>nd[Lca].dep)
				jump[fr][0]=Lca;
		for(int i=head[fr];i!=0;i=ed[i].nxt)
		{
			int to=ed[i].to;
			if(to==fa)
				continue;
			set(fr,to);
			if(nd[jump[fr][0]].dep>nd[jump[to][0]].dep)
				jump[fr][0]=jump[to][0];
		}
		return ;
	}
	void input()
	{
		n=read();
		for(int to=2;to<=n;to++)
		{
			int fr=read();
			add_edge(fr,to);
			add_edge(to,fr);
		}
		TreePartition::init();
		dfs(0,1); 
        m=read();
		for(int i=1;i<=m;i++)
		{
			int fr=read(),to=read();
			int Lca=TreePartition::lca(fr,to);
			if(fr!=Lca)
				graph[fr].push_back(Lca);
			if(to!=Lca)
				graph[to].push_back(Lca);
			using namespace BIT;
			points[++pts]=(point){dfn[fr],dfn[to]};
			points[++pts]=(point){dfn[to],dfn[fr]};
		}
		set(0,1);
        q=read();
		return ;
	} 
	void init()
	{
		for(int i=1;i<=20;i++)
			for(int j=1;j<=n;j++)
				jump[j][i]=jump[jump[j][i-1]][i-1];
		return ; 
	} 
	void solve()
	{
		for(int i=1;i<=q;i++)
		{
			using namespace TreePartition;
			int fr=read(),to=read();
			int Lca=lca(fr,to);
			if(dfn[fr]>dfn[to])
				std::swap(fr,to); 
			for(int j=20;j>=0;j--)
				if(jump[fr][j]!=0&&nd[jump[fr][j]].dep>nd[Lca].dep)
					fr=jump[fr][j],ans[i]+=(1<<j);
			for(int j=20;j>=0;j--)
				if(jump[to][j]!=0&&nd[jump[to][j]].dep>nd[Lca].dep)
					to=jump[to][j],ans[i]+=(1<<j);
			if(nd[jump[fr][0]].dep>nd[Lca].dep||nd[jump[to][0]].dep>nd[Lca].dep) 
			{
				ans[i]=-1;
				continue;
			}
			if(fr==Lca)
			{
				ans[i]++;
				continue;
			};
			ans[i]+=2;
			int sizefr=nd[fr].size;
			int sizeto=nd[to].size;
			using namespace BIT;
			questions[++cnt]=(question){i,1,dfn[fr]+sizefr-1,dfn[to]+sizeto-1};
			questions[++cnt]=(question){i,-1,dfn[fr]+sizefr-1,dfn[to]-1};
			questions[++cnt]=(question){i,-1,dfn[fr]-1,dfn[to]+sizeto-1};
			questions[++cnt]=(question){i,1,dfn[fr]-1,dfn[to]-1};
		}
		using namespace BIT;
		std::sort(points+1,points+pts+1);
		std::sort(questions+1,questions+cnt+1);
		for(int i=1,now=1;i<=cnt;i++)
		{
			while(now<=pts&&points[now].x<=questions[i].x)
				modify(points[now].y,1),now++;
			tmp[questions[i].id]+=questions[i].val*query(questions[i].y);
		}
		for(int i=1;i<=q;i++)
		{
			if(tmp[i]>0)
				ans[i]--;
			printf("%d\n",ans[i]);
		}
		return ;
	}
}; 
int main(int argc,const char *argv[])
{
	solve::input();
	solve::init();
	solve::solve();
	return 0;
}
```

---

## 作者：zhenjianuo2025 (赞：1)

### Solve

神仙题。

考虑链上的情况，直接开贪，每一次跳到最远能跳到的点上。正确性读者自证不难。倍增优化，$f_{u,j}$ 表示 $u$ 跳 $2^j$ 次能跳到哪里。

扩展到树上，记询问的两点为 $u,v$，$\text{lca}$ 为 $u,v$ 的 $\text{LCA}$。和链上的做法一样，把 $u,v$ 跳到 $\text{lca}$ 上。但是容易发现这是错误的，比如说：

![?](https://cdn.luogu.com.cn/upload/image_hosting/vmm4onk4.png)

其中有一条路线 $u\to v$。

那么我们发现，此时的答案不等于 $1+1=2$，因为有可能存在穿过 $\text{lca}$ 的路线。

于是我们只把 $u,v$ 跳到 $\text{lca}$ **之下**就结束，钦定答案为 $u,v$ 跳跃的答案和 $+2$，此时，若存在一条路线 $x\to y$，满足 $x,y$ 分别在 $u,v$ 的子树下，把答案 $-1$。

经典的二维数点。

---

## 作者：北射天狼 (赞：1)

[题目链接](https://www.luogu.com.cn/problem/CF983E)

## 目录

### 1.前言

### 2.贪心思路

### 3.倍增优化

### 4.二维数点详解

### 5.具体代码解释和易错点

----

### 1.前言

看到好多大佬都会树链剖分，在那里爆切。我不会，只好写一种十分巧妙的解法，那就是，贪心倍增。

前置知识：$\operatorname{lca}$，倍增，树状数组。


### 2.贪心思路

题意是，一棵树上，有许多路线（简单路径，即没有经过重复点的路径），有 $q$ 次询问，每次询问给出一条路线，即简单路径。问至少需要几条路线，才能将这条简单路径完全覆盖。若不能，则输出 $-1$。

我们考虑将题意转换，每次询问有两个点沿着路线遍历，问能否使两个点重合？（显然如果有解即可使点相遇，且可以贪心使路线最少。）

假设给出的节点是 $x$，$y$，且 $dfn_x\le dfn_y$( $dfn_x,dfn_y$ 为该节点的 dfs 序)，那么有以下两种情况：


情况一：若 $x$ 是 $\operatorname{lca}(x,y)$，直接考虑从 $y$ 暴力枚举路线，不停向上，统计答案直到到达 $x$。

```
假设有路线 (y -> 2) 和 (2 -> x) 则下图为模拟过程：

      1
     / 
    x <-- 
   /    / 第二次向上，到达 x，答案即为2
  2 <--
 /    / 第一次向上，到达 2
y ---
```

情况二：若 $y$ 不是 $\operatorname{lca}(x,y)$，则有下图这种情况：


```
      1
     / \
   lca   3
   / \
  2   4
 /   / \
x   y   5
```
下文的跳动指沿着路线向着根节点的方向遍历。

这时候我们考虑暴力枚举路线，不断跳动，当再往前走一条路线（也就是到达下一条路线后）可以到达或超过 $\operatorname{lca}(x,y)$ 时，就停下。如果没有看懂可以看下图：

```
假设有路线 （x -> 2），（y -> 4），（2 -> lca），（4 -> 1），（2 -> 4）。

我们进行遍历路线操作：

          1
         / \
       lca  3
       / \
  --> 2   4 <--
 /    /   /   / (再跳一次就要到达 lca 了，停止沿路线跳动)
 ----x   y ---  
```

假设 $x$ 跳动的次数为 $jump_x$，$y$ 跳动的次数为 $jump_y$，答案很显然为 $jump_x + jump_y +2$。（因为很显然 $x$，$y$ 只要再各跳一步就能到达 $\operatorname{lca}$，双方再跳一条路线即可使路线完全覆盖着条路径）

但是这样真的对吗？

观察上面的例子，有一条链 $2 \to 4$ 可以让节点直接从 $2$ 到 $4$，并不需要让 $x$，$y$ 再各跳一步，答案仅为 $jump_x + jump_y + 1$，因此需分类讨论有没有路线经过 $\operatorname{lca}$，关于这一块的内容我们会在第四章讲到如何维护。

那我们怎么贪心呢？考虑节点 $x$ 有在两条路线上，一条通往深度较浅的节点（人话：靠近根节点的），一条通往深度较深的节点，那我们肯定选择去深度较浅的节点。

例如：

```
          1
         /
        2
       /
      3
     /
    4
   /
  x
 /
5
```

有路线 $5\to3$，有路线 $x\to2$，那我们肯定优先选择前往 $2$ 的节点。(在不考虑有无超过 $\operatorname{lca}$ 的情况下)

综上，我们对于每一次询问的路径 $x$，$y$，依次使其沿路径遍历直到在 $\operatorname{lca}$ 下方 (情况一特殊考虑)，同时，判断有没有路径经过 $\operatorname{lca}$，联通遍历完的 $x$，$y$。有则加一，否则加二。

我们发现，如果一条一条路线遍历那太麻烦了，我们考虑倍增优化。

### 3.倍增优化

用数组 $g_{i,j}$ 来表示编号为 $i$ 的节点向上跳了 $2^j$ 条路线，所可以达到的深度最浅的节点。

显然有代码：

```
void bfs(int u){//这个不是bfs,不要想太多
	g[u][0] = u; 
        //显然，在没有路线的情况下，
        //一开始 节点u能到达深度最浅的节点是他自己。
	for (int i:T[u])
        //这里，T是一个vector，用来存储 以u开头为路线的两个节点的 lca 的
        //假设以 u 开头有一条路线(x->y)
        //那 u 能到达深度最浅的节点一定是 lca(x,y) 具体原因参照上图理解。
        //因为显然一条路径中lca为深度最浅的节点
	    if (dep[i] < dep[g[u][0]])
	        g[u][0] = i;//取lca中深度最浅的
	for (int i=head[u];i;i=tree[i].next){
		bfs(tree[i].v);//遍历子节点
		if (dep[g[tree[i].v][0]] < dep[g[u][0]])
                    //显然，如果u的子节点能到达深度更浅的节点，这条路径一定经过u
                    //所以u也能走该路线，到达该节点
		    g[u][0] = g[tree[i].v][0];
	}
}
```

好的，现在我们维护好 $g_{i,0}$ 了，那其余的怎么办呢？

想到我们学过的倍增，则显然有：


```
for (int j=1;j<=20;j++)
    for (int i=1;i<=n;i++)
	g[i][j] = g[g[i][j-1]][j-1]; 
```

由于我们要写 $\operatorname{lca}$ 所以肯定要再维护一个 $f_{i,j}$ 求 $\operatorname{lca}$，但这是前置知识，我就不多讲了。

### 4.二维数点详解

我们在第二章有说道，我们该如何判断从节点 $x$ 到节点 $y$，有无经过 $\operatorname{lca}$ 的路径。

显然有：如果有该条路径，则显然 $x$ 的子树中(包括 $x$)，有至少一个节点有路径经过 $x$ ，经过 $\operatorname{lca}$，经过 $y$，到达 $y$ 的子树。

由 dfs 序可知，由于我们假设 $dfn_x < dfn_y$，则显然有 $x$ 的子树的 $dfn$ 序在 $[dfn_x,dfn_x+size_x - 1]$ 之间，同理 $y$ 的子树的 $dfn$ 序在 $[dfn_y,dfn_y+size_y - 1]$ 之间。其中，$size_i$ 表示的是子树 $i$ 的大小。我们假设 $u$ 在 $x$ 的子树中，$v$ 在 $y$ 的子树中，有一条路径 $u \to v$ 则显然有
$$dfn_x \le dfn_u \le dfn_x + size_x - 1$$

$$dfn_y \le dfn_v \le dfn_y + size_y- 1$$

我们可以抽象地把路径看作是点，构造一个平面直角坐标系（如下图），令若 $(dfn_x,dfn_y) = 1$，则 $x,y$ 之间有路径。
````
注：该图仅为注释，不一定完全准确。

dfn(y)+size(y)-1
    |   . 0 0 0 0 0 0 0 0 0 0 0 0 0
    |-->. 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0 
        . 0 0 0 0 0 0 0 0 0 0 0 0 0 
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
dfn(y)-1. 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
        O . . . . . . . . . . . . .
            |               |
            |dfn(x)-1       |dfn(x)+size(x)-1
````

构造如上图点阵，意义如上文所述，横纵坐标值域均为 $[1,n]$。

我们为了要查询 $[(dfn_x,dfn_y),(dfn_x + size_x-1,dfn_y+size_y-1)]$ 这个方阵中有没有连边，也就是有没有出现 $1$。

特别的，为了方便求和，令方阵初始值为 $0$。

注意到 $N\le 10^5$，无法使用前缀和，考虑树状数组（利用前缀和思想）。

令有一变量 $i$，其意义是节点的 $dfn$ 值，枚举 $i$ 从 $1$ 到 $n$，依次做如下操作：

````     
            
dfn(y)+size(y)-1
    |     i
    |     v
    |   . 0 0 0 0 0 0 0 0 0 0 0 0 0
    |-->. 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0 
        . 0 0 0 0 0 0 0 0 0 0 0 0 0 
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
dfn(y)-1. 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
        O . . . . . . . . . . . . .
            |               |
            |dfn(x)-1       |dfn(x)+size(x)-1
````
假如 $dfn$ 值为 $i$，$j$的节点有路径 $i\to j$，则将 $(i,j)$ 设为 $1$，加入树状数组。

````     
            
dfn(y)+size(y)-1
    |     i
    |     v
    |   . 0 0 0 0 0 0 0 0 0 0 0 0 0
    |-->. 1 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0 
        . 0 0 0 0 0 0 0 0 0 0 0 0 0 
        . 1 0 0 0 0 0 0 0 0 0 0 0 0
dfn(y)-1. 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
        O . . . . . . . . . . . . .
            |               |
            |dfn(x)-1       |dfn(x)+size(x)-1
````

往下操作，继续加边：

````     
            
dfn(y)+size(y)-1
    |       i
    |       v
    |   . 0 0 0 0 0 0 0 0 0 0 0 0 0
    |-->. 1 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 1 0 0 0 0 0 0 0 0 0 0 0 
        . 0 0 0 0 0 0 0 0 0 0 0 0 0 
        . 1 0 0 0 0 0 0 0 0 0 0 0 0
dfn(y)-1. 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 1 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 0 0 0 0 0
        O . . . . . . . . . . . . .
            |               |
            |dfn(x)-1       |dfn(x)+size(x)-1
````

我们发现 $i = dfn_x -1$，这时我们做一次查询 $[dfn_y,dfn_y +size_y - 1]$ 中的和的操作，用树状数组表示就是 ```sum(dfn[y]+size[y]-1) - sum(dfn[y]-1) ```，记作 $sum_1$。

继续往下操作，直到 $i = dfn_i+size_i-1$。


````     
            
dfn(y)+size(y)-1
    |                       i
    |                       v
    |   . 0 0 0 0 0 0 0 0 0 0 0 0 0
    |-->. 1 0 0 0 0 0 1 0 0 1 0 0 0
        . 0 1 0 0 1 0 0 0 0 0 0 0 0 
        . 0 0 0 0 0 0 0 0 1 0 0 0 0 
        . 1 0 0 0 0 1 0 0 0 0 0 0 0
dfn(y)-1. 0 0 0 0 0 0 0 0 0 0 0 0 0
        . 0 1 0 0 0 0 0 0 0 1 0 0 0
        . 0 0 0 0 0 0 1 0 0 0 0 0 0
        . 0 0 0 0 0 0 0 0 1 0 0 0 0
        O . . . . . . . . . . . . .
            |               |
            |dfn(x)-1       |dfn(x)+size(x)-1
````

这时我们做一次查询 $[dfn_y,dfn_y +size_y - 1]$ 操作，用树状数组表示就是 ```sum(dfn[y]+size[y]-1) - sum(dfn[y]-1) ``` 记作 $sum_2$。

我们惊奇的发现，$[(dfn_x,dfn_y),(dfn_x + size_x-1,dfn_y+size_y-1)]$ 这个方阵中 $1$ 的个数，就是 $sum_2 - sum_1$。

注：$sum_1$ 中的 $1$ 用 ```*``` 标记。最终会查询到的点用 ```#``` 表示。

````     
            
dfn(y)+size(y)-1
    |                       
    |   左边的 1 被删除   右边的 1 没有被查询           
    |   . 0 0 | 0 0 0 0 0 0 0 | 0 0 0 0
上面的 1 没有被查询----------------------------
    |-->.*1 0 | 0 0 0 0#1 0 0 | 1 0 0 0
        . 0*1 | 0 0#1 0 0 0 0 | 0 0 0 0 
        . 0 0 | 0 0 0 0 0 0#1 | 0 0 0 0 
        .*1 0 | 0 0 0#1 0 0 0 | 0 0 0 0
下面的 1 没有被查询----------------------------
dfn(y)-1. 0 0 | 0 0 0 0 0 0 0 | 0 0 0 0
        . 0 1 | 0 0 0 0 0 0 0 | 1 0 0 0
        . 0 0 | 0 0 0 0 1 0 0 | 0 0 0 0
        . 0 0 | 0 0 0 0 0 0 1 | 0 0 0 0
        O . . | . . . . . . . | . . . .
            |               |
            |dfn(x)-1       |dfn(x)+size(x)-1
````


相信你现在已经完全理解了！


### 5.具体代码解释和易错点

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int s = 0,f = 1;char c = getchar();
	while (!isdigit(c)){if (c == '-')f = -1;c = getchar();}
	while (isdigit(c)){s = (s << 3) + (s << 1) + (c ^ 48);c = getchar();}
	return s*f;
}
const int N = 2e5 + 5;
int n,m,q;
int f[N][21],g[N][21];
int dep[N],siz[N],dfn[N],ans[N],c[N],s[N];
int idx;
int head[N],cnt;
vector<int> Q[N],T[N];
// Q 是路径连边 T 是 lca
struct qwq{
	int x,val,id;
};
struct awa{
	int now,ans;
};
vector<qwq> P[N];
struct node{
	int v,next;
}tree[N];
void addedge(int u,int v){
	tree[++cnt].next = head[u];
	tree[cnt].v = v;
	head[u] = cnt;
}
//链式前向星
int lowbit(int x){return x & (-x);}
void add(int x,int y){
    for (;x<=n;x+=lowbit(x))c[x]+=y;
}
int query(int x){
    int s = 0;
	for (;x;x-=lowbit(x))s += c[x];
	return s;
}
//朴素的树状数组
void dfs(int u){
	dep[u] = dep[f[u][0]] + 1;
	dfn[u] = ++idx;
	for (int i=head[u];i;i=tree[i].next){
		dfs(tree[i].v);
		siz[u] += siz[tree[i].v];
	}
	siz[u]++;
}
//dfn,dep,siz
int lca(int x,int y){
	if (dep[x] < dep[y])    swap(x,y);
	for (int i=20;i>=0;i--)
	    if (dep[f[x][i]] >= dep[y])
	        x = f[x][i];
	if (x == y)
	    return x;
	for (int i=20;i>=0;i--)
		if (f[x][i] != f[y][i])
		    x = f[x][i],y = f[y][i];
    return f[x][0];
}
//lca
void bfs(int u){
	g[u][0] = u;
	for (int i:T[u])
	    if (dep[i] < dep[g[u][0]])
	        g[u][0] = i;
	for (int i=head[u];i;i=tree[i].next){
		bfs(tree[i].v);
		if (dep[g[tree[i].v][0]] < dep[g[u][0]])
		    g[u][0] = g[tree[i].v][0];
	}
}//注释见上
awa jump(int x,int y){
	if (x == y)
	    return (awa){x,0};//不用跳跃
	int res = 0;
	for (int i=20;i>=0;i--)
	   if (dep[g[x][i]] > dep[y])
	       x = g[x][i],res += (1 << i);//倍增跳跃
	if (dep[g[x][0]] <= dep[y])
        return (awa){x,res};//再跳一步就能超过或到达lca了
    return (awa){x,-1};//到不了了！qwq
}//节点向上遍历路线操作。
signed main()
{
    n = read(); 
    for (int i=2;i<=n;i++){
    	f[i][0] = read();
    	addedge(f[i][0],i);
	}//遍历整个树维护
	for (int j = 1;j <= 20;j++)
	    for (int i=1;i<=n;i++)
	        f[i][j] = f[f[i][j-1]][j-1];
    //lca
    dfs(1);
    m = read();
     for (int i=1,u,v;i<=m;i++){
    	u = read(); v = read();
    	if (u == v)    continue;
    	if (dfn[u] > dfn[v])
    	    swap(u,v);
        //依据我们的假设
    	Q[dfn[u]].push_back(dfn[v]);
        //确定连边，进行二维数点
    	int zzp = lca(u,v);
    	T[u].push_back(zzp);
    	T[v].push_back(zzp);
	}
	bfs(1);
	for (int j=1;j<=20;j++)
	    for (int i=1;i<=n;i++)
	        g[i][j] = g[g[i][j-1]][j-1]; //见上。
	q = read();
	for (int i=1,u,v;i<=q;i++){
		u = read(); v = read();
		int zzp = lca(u,v);
		awa a = jump(u,zzp),b = jump(v,zzp);
		if (a.ans == -1 || b.ans == -1){
			ans[i] = -1;//显然有一个到不了全都到不了
			continue;
		}
		if (u == zzp || v == zzp){
			ans[i] = a.ans + b.ans + 1;//情况一
			continue;
		}
               //情况二
		ans[i] = a.ans + b.ans + 2;
		if (dfn[a.now] > dfn[b.now])
		    swap(a,b);
		//我们假设了 dfn[a] < dfn[b]
                //存储该节点，图见上
        P[dfn[a.now]-1].push_back((qwq){b.now,-1,i});
		P[dfn[a.now]+siz[a.now]-1].push_back((qwq){b.now,1,i});
                //推入 dfn[a],dfn[a]+size[a]-1
                //准备进行二维数点
	}
	for (int i=1,x,y,z;i<=n;i++){
		for (int j:Q[i])
		    add(j,1);//j 能沿路径到达 i,(i,j)设为1
		for (auto p:P[i]){//auto:自动判断类型，这里是判断 dfn 值为 i 时需不需要进行树状数组求值。
			qwq zzp = p;
			s[zzp.id] += zzp.val * (query(dfn[zzp.x] + siz[zzp.x]-1) - query(dfn[zzp.x]-1));
               //累计进行两次减法
               //对于同一个节点，先计算的是 sum1,后计算的是 sum2 
		}
	}
	for (int i=1;i<=q;i++)
	    printf("%lld\n",ans[i] - (s[i] > 0));//如果大于 0 则说明有连边，减去一。
	return 0;
}
```
注意：大部分本题解指的路径是指题目的路径，而并不是简单路径。

#### 易错点

* 检查树状数组有没有写错。
* 倍增有没有写对。
* 有没有少考虑一种情况。
* 鉴于本代码需要的变量较多，有没有写反了。
* 离线操作有没有写炸。

等等等等。

Update：修改了个别错别字，表述错误，图片错误以及程序排版。


---

## 作者：xxasmcd (赞：0)

首先可以求出从某点做 $ 2^k $ 次车能到的最浅的点，这个只要深搜一下，把它的孩子能到的最浅的点更新过来就可以。

然后倍增地往上跳，不能跳到最近公共祖先的上面，记录坐车的次数 $ ans $。

此时有三种情况设最远能跳到 $ x $ 到 $ y $。
　　
  1. 再跳也跳不到 $ lca $ 的上面，就是负一。
　　
  1. 路径 $ x $ 被某趟车覆盖，答案是 $ ans $ 加一。
　　
  1. 并没有被覆盖，答案是 $ ans $ 加二。

那么怎么看有没有覆盖呢？

首先，如果这两个点是直上直下的：有一个是最近公共祖先，只要看下面那个点能不能跳到上面去就行。

对于剩下的 $ x $ 到 $ y $，只要有车的两端点分别在 $ x $ 和 $ y $ 的子树中就可以。

所以做一遍深搜，进某个点 $ x $ 的时候记下来 $ y $ 的子树中车端点的个数，然后把从 $ x $ 发的车的终点加一，出来的时候再次统计那个个数，如果不相同，就说明 $ x $ 到 $ y $ 这条路径被覆盖了。这个用一个树状数组就可以树上作差。

代码如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,q,fa[21][200005],tmp[200005*2],num=0,cnt=0,dfn[200005][2],s[200005],dep[200005],nxt[200005][21];
int ed[200005][2],edh[200005];
int pt[200005*2][2],pth[200005];
int lq[200005*2][2],lqh[200005],ans[200005];
bool co[200005];
void add(int x,int y)
{
    ++num;
    ed[num][0]=y;
    ed[num][1]=edh[x];
    edh[x]=num;
}
void dfs1(int x)
{
     dfn[x][0]=++cnt;
     for(int i=0;fa[i][x]&&fa[i][fa[i][x]];i++)
     {
         fa[i+1][x]=fa[i][fa[i][x]];
     }
     for(int i=edh[x];i>0;i=ed[i][1])
     {
         int to=ed[i][0];
         dep[to]=dep[x]+1;
         dfs1(to);
     }
     dfn[x][1]=cnt;
}
int lca(int x,int y)
{
    if(dep[x]<dep[y])
    {
        swap(x,y);
    }
    for(int i=20;i>=0&&dep[x]!=dep[y];i--)
    {
        if(fa[i][x]&&dep[fa[i][x]]>=dep[y])
        {
            x=fa[i][x];
        }
    }
    if(x==y)return x;
    for(int i=20;i>=0;i--)
    {
        if(fa[i][x]!=fa[i][y])
        {
            x=fa[i][x];
            y=fa[i][y];
        }
    }
    return fa[0][x];
}
void dfs2(int x)
{
     for(int i=edh[x];i>0;i=ed[i][1])
     {
         int to=ed[i][0];
         dfs2(to);
         if(nxt[to][0]&&(dep[nxt[to][0]]<dep[nxt[x][0]]||!nxt[x][0]))
         {
             nxt[x][0]=nxt[to][0];
         }
     }
     if(dep[nxt[x][0]]>=dep[x])nxt[x][0]=0;
}
int lowbit(int x)
{
    return x&(-x);
}
void pre(int x,int y)
{
    while(x<=n)
    {
        s[x]+=y;
        x+=lowbit(x);
    }
}
int getsum(int x)
{
    int sum=0;
    while(x>0)
    {
        sum+=s[x];
        x-=lowbit(x);
    }
    return sum;
}
void dfs3(int x)
{
    for(int i=lqh[x];i>0;i=lq[i][1])
    {
        int to=lq[i][0];
        tmp[i]=getsum(dfn[to][1])-getsum(dfn[to][0]-1);
    }
    for(int i=pth[x];i>0;i=pt[i][1])
    {
        int to=pt[i][0];
        pre(dfn[to][0],1);
    }
    for(int i=edh[x];i>0;i=ed[i][1])
    {
        int to=ed[i][0];
        dfs3(to);
    }
    for(int i=lqh[x];i>0;i=lq[i][1])
    {
        int to=lq[i][0];
        if(tmp[i]!=getsum(dfn[to][1])-getsum(dfn[to][0]-1))
        {
            co[i>>1]=1;
        }
    }
}
int main()
{
    cin>>n;
    for(int i=2;i<=n;i++)
    {
        cin>>fa[0][i];
        add(fa[0][i],i);
    }
    dep[1]=1;
    dfs1(1);
    cin>>m;
    for(int i=1;i<=m;i++)
    {
        int a,b;
        cin>>a>>b;
        pt[i<<1][0]=a,pt[i<<1][1]=pth[b],pth[b]=i<<1;
        pt[i<<1|1][0]=b,pt[i<<1|1][1]=pth[a],pth[a]=i<<1|1;
        int lcaa=lca(a,b);
        if(dep[lcaa]<dep[nxt[a][0]]||!nxt[a][0])nxt[a][0]=lcaa;
        if(dep[lcaa]<dep[nxt[b][0]]||!nxt[b][0])nxt[b][0]=lcaa;
    }
    dfs2(1);
    for(int i=0;i<19;i++)
    {
        for(int j=1;j<=n;j++)
        {
            nxt[j][i+1]=nxt[nxt[j][i]][i];
        }
    }
    cin>>q;
    for(int i=1;i<=q;i++)
    {
        int a,b;
        cin>>a>>b;
        int lcaa=lca(a,b);
        for(int j=19;j>=0;j--)
        {
            if(nxt[a][j]&&dep[nxt[a][j]]>dep[lcaa])
            {
                ans[i]+=1<<j,a=nxt[a][j];
            }
        }
        for(int j=19;j>=0;j--)
        {
            if(nxt[b][j]&&dep[nxt[b][j]]>dep[lcaa])
            {
                ans[i]+=1<<j,b=nxt[b][j];
            }
        }
        if((a==lcaa&&nxt[b][0]&&dep[nxt[b][0]]<=dep[lcaa])||(b==lcaa&&nxt[a][0]&&dep[nxt[a][0]]<=dep[lcaa]))
        {
            ans[i]+=1;
        }
        else if(nxt[b][0]&&nxt[a][0]&&dep[nxt[b][0]]<=dep[lcaa]&&dep[nxt[a][0]]<=dep[lcaa])
        {
            ans[i]+=2;
            lq[i<<1][0]=a,lq[i<<1][1]=lqh[b],lqh[b]=i<<1;
            lq[i<<1|1][0]=b,lq[i<<1|1][1]=lqh[a],lqh[a]=i<<1|1;
        }
        else
        {
            ans[i]=-1;
        }
    }
    dfs3(1);
    for(int i=1;i<=q;i++)
    {
        cout<<ans[i]-co[i]<<endl;
    }
    return 0;
}

```


---

## 作者：tzc_wk (赞：0)

[Codeforces 题面传送门](https://codeforces.ml/contest/983/problem/E) & [洛谷题面传送门](https://www.luogu.com.cn/problem/CF983E)

一道（绝对）偏简单的 D1E，但是我怕自己过~~若干年~~（大雾）忘了自己的解法了，所以过来水篇题解（

首先考虑怎么暴力地解决这个问题，不难发现我们每一步肯定会贪心，贪心地跳到所有经过当前点的公交线路中另一端最浅的位置，直到到达两点的 $\text{LCA}$ 为止。不难发现上述过程可以倍增优化，具体来说我们记 $nxt_{i,j}$ 表示从 $i$ 开始走 $2^j$ 步最浅能够到达哪里，那么我们可以一面树剖求出经过每个点能够到达深度最浅的节点，一面倍增往上跳知道跳到深度 $<\text{LCA}(u,v)$ 的位置为止。

不过上述算法有一个漏洞，就是在我们到达 $\text{LCA}(u,v)$ 的前一步到达的点 $u',v'$ 很可能已经可以通过某条公交线相连了，此时我们大可不必再花费 $2$ 的代价跳到 $\text{LCA}(u,v)$，直接一步就可以搞定，答案需减一。因此考虑再倍增求出 $u,v$ 到达 $\text{LCA}(u,v)$ 之前上一步到达的节点 $u',v'$，不难发现，由于 $u',v'$ 之间不存在祖先关系，因此 $u',v'$ 存在公交线相连的充要条件是存在某个公交线，两个端点分别在 $u',v'$ 子树内，这个可以 DFS 序+离线二维数点/在线主席树求出。

时间复杂度 $n\log^2n$，但显然有复杂度更优秀/更好写的 implementation，比方说树剖换成 `set` 启发式合并代码可以少三十多行，换成线段树合并可以少一个 $\log$。

~~我竟然写这么短的题解，我怕不是精神不正常（大雾~~

代码（这种题我都能码 171 行……zz 这题我实现得跟 sh*t 一样）：

```cpp
const int MAXN=2e5;
const int LOG_N=18;
const int INF=0x3f3f3f3f;
int n,m,qu,qn,hd[MAXN+5],to[MAXN+5],nxt[MAXN+5],ec=0;
void adde(int u,int v){to[++ec]=v;nxt[ec]=hd[u];hd[u]=ec;}
int siz[MAXN+5],wson[MAXN+5],dep[MAXN+5],fa[MAXN+5][LOG_N+2];
int top[MAXN+5],dfn[MAXN+5],tim=0,edt[MAXN+5];
void dfs1(int x){
	siz[x]=1;
	for(int e=hd[x];e;e=nxt[e]){
		int y=to[e];dep[y]=dep[x]+1;
		dfs1(y);siz[x]+=siz[y];
		if(siz[y]>siz[wson[x]]) wson[x]=y;
	}
}
void dfs2(int x,int tp){
	top[x]=tp;dfn[x]=++tim;if(wson[x]) dfs2(wson[x],tp);
	for(int e=hd[x];e;e=nxt[e]) if(to[e]!=fa[x][0]&&to[e]!=wson[x])
		dfs2(to[e],to[e]);
	edt[x]=tim;
}
int getlca(int x,int y){
	while(top[x]^top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		x=fa[top[x]][0];
	} if(dep[x]<dep[y]) swap(x,y);
	return y;
}
struct node{int l,r,val,lz;} s[MAXN*4+5];
void pushup(int k){s[k].val=min(s[k<<1].val,s[k<<1|1].val);}
void build(int k,int l,int r){
	s[k].l=l;s[k].r=r;s[k].lz=INF;if(l==r) return s[k].val=INF,void();
	int mid=l+r>>1;build(k<<1,l,mid);build(k<<1|1,mid+1,r);pushup(k);
}
void pushdown(int k){
	if(s[k].lz!=INF){
		chkmin(s[k<<1].val,s[k].lz);chkmin(s[k<<1|1].val,s[k].lz);
		chkmin(s[k<<1].lz,s[k].lz);chkmin(s[k<<1|1].lz,s[k].lz);
		s[k].lz=INF;
	}
}
void modify(int k,int l,int r,int x){
	if(l<=s[k].l&&s[k].r<=r){
		chkmin(s[k].val,x);chkmin(s[k].lz,x);
		return;
	} pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(r<=mid) modify(k<<1,l,r,x);
	else if(l>mid) modify(k<<1|1,l,r,x);
	else modify(k<<1,l,mid,x),modify(k<<1|1,mid+1,r,x);
	pushup(k);
}
int query(int k,int x){
	if(s[k].l==s[k].r) return s[k].val;pushdown(k);
	pushdown(k);int mid=s[k].l+s[k].r>>1;
	if(x<=mid) return query(k<<1,x);
	else return query(k<<1|1,x);
}
void jumpath(int x,int y,int v){
	while(top[x]^top[y]){
		if(dep[top[x]]<dep[top[y]]) swap(x,y);
		modify(1,dfn[top[x]],dfn[x],v);
		x=fa[top[x]][0];
	} if(dep[x]<dep[y]) swap(x,y);
	modify(1,dfn[y],dfn[x],v);
}
int get_kanc(int x,int k){
	for(int i=LOG_N;~i;i--) if(k>>i&1) x=fa[x][i];
	return x;
}
int nt[MAXN+5][LOG_N+2],cnt[MAXN+5],ans[MAXN+5],mark[MAXN+5];
int step(int x,int d){
	if(dep[x]<=d) return 0;
	if(dep[nt[x][LOG_N]]>d) return -1;int cnt=0;
	for(int i=LOG_N;~i;i--) if(dep[nt[x][i]]>d) x=nt[x][i],cnt|=(1<<i);
	return cnt+(dep[x]>d);
}
int get_kstp(int x,int k){
	for(int i=LOG_N;~i;i--) if(k>>i&1) x=nt[x][i];
	return x;
}
vector<int> pts[MAXN+5];
struct qry{
	int x,y,t,id;
	bool operator <(const qry &rhs) const{
		return x<rhs.x;
	}
} q[MAXN*4+5];
void add_rec(int x1,int x2,int y1,int y2,int id){
//	printf("%d %d %d %d %d\n",x1,x2,y1,y2,id);
	q[++qn]={x2,y2,1,id};q[++qn]={x1-1,y2,-1,id};
	q[++qn]={x2,y1-1,-1,id};q[++qn]={x1-1,y1-1,1,id};
}
struct fenwick{
	int t[MAXN+5];
	void add(int x,int v){for(int i=x;i<=n;i+=(i&(-i))) t[i]+=v;}
	int query(int x){int ret=0;for(int i=x;i;i&=(i-1)) ret+=t[i];return ret;}
} tr;
int main(){
	scanf("%d",&n);
	for(int i=2;i<=n;i++) scanf("%d",&fa[i][0]),adde(fa[i][0],i);
	dfs1(1);dfs2(1,1);build(1,1,n);
	for(int i=1;i<=n;i++) modify(1,dfn[i],dfn[i],dep[i]);
	scanf("%d",&m);
	for(int i=1,x,y;i<=m;i++){
		scanf("%d%d",&x,&y);
		pts[dfn[x]].pb(dfn[y]);pts[dfn[y]].pb(dfn[x]);
//		printf("(%d %d)\n",dfn[x],dfn[y]);
		jumpath(x,y,dep[getlca(x,y)]);
	}
	for(int i=1;i<=LOG_N;i++) for(int j=1;j<=n;j++) fa[j][i]=fa[fa[j][i-1]][i-1];
	for(int i=1;i<=n;i++) nt[i][0]=get_kanc(i,dep[i]-query(1,dfn[i]));
	for(int i=1;i<=LOG_N;i++) for(int j=1;j<=n;j++) nt[j][i]=nt[nt[j][i-1]][i-1];
	scanf("%d",&qu);
	for(int i=1;i<=qu;i++){
		int x,y,l;scanf("%d%d",&x,&y);l=getlca(x,y);
		int sx=step(x,dep[l]),sy=step(y,dep[l]);
		if(!~sx||!~sy) ans[i]=-1;
		else{
			ans[i]=sx+sy;
			if(sx!=0&&sy!=0){
				int ax=get_kstp(x,sx-1);
				int ay=get_kstp(y,sy-1);
				add_rec(dfn[ax],edt[ax],dfn[ay],edt[ay],i);
			}
		}
	}
//	for(int i=1;i<=qu;i++) printf("%d\n",ans[i]);
	sort(q+1,q+qn+1);int cur=1;
	for(int i=1;i<=qn;i++){
		while(cur<=q[i].x){
			for(int y:pts[cur]) tr.add(y,1);
			cur++;
		} cnt[q[i].id]+=q[i].t*tr.query(q[i].y);
//		printf("%d %d %d\n",q[i].x,q[i].y,tr.query(q[i].y));
	}
	for(int i=1;i<=qu;i++) printf("%d\n",ans[i]-(cnt[i]>0));
	return 0;
}
```



---

