# [USACO19DEC] Milk Visits G

## 题目描述

Farmer John 计划建造 $N$ 个农场，用 $N-1$ 条道路连接，构成一棵树（也就是说，所有农场之间都互相可以到达，并且没有环）。每个农场有一头奶牛，品种为 $1$ 到 $N$ 之间的一个整数 $T_i$。

Farmer John 的 $M$ 个朋友经常前来拜访他。在朋友 $i$ 拜访之时，Farmer John 会与他的朋友沿着从农场 $A_i$ 到农场 $B_i$ 之间的唯一路径行走（可能有 $A_i = B_i$）。除此之外，他们还可以品尝他们经过的路径上任意一头奶牛的牛奶。由于 Farmer John 的朋友们大多数也是农场主，他们对牛奶有着极强的偏好。他的每个朋友都只喝某种特定品种的奶牛的牛奶。任何 Farmer John 的朋友只有在他们访问时能喝到他们偏好的牛奶才会高兴。

请求出每个朋友在拜访过后是否会高兴。



## 说明/提示

测试点性质：

测试点 $2$ 为以下第二个样例。

测试点 $3$ 满足 $N\le 10^3$，$M\le 2\cdot 10^3$。

测试点 $4\sim 7$ 满足 $C_i\le 10$。

对于 $100\%$ 的数据，$1 \leq N \leq 10^5$，$1 \leq M \leq 10^5$。

供题：Spencer Compton

## 样例 #1

### 输入

```
5 5
1 1 2 1 2
1 2
2 3
2 4
1 5
1 4 1
1 4 2
1 3 2
1 3 1
5 5 1```

### 输出

```
10110```

## 样例 #2

### 输入

```
6 4
1 2 3 3 3 3
1 2
2 3
3 4
2 5
5 6
4 6 1
4 6 2
4 6 3
4 6 4```

### 输出

```
0110```

# 题解

## 作者：密期望 (赞：33)

时间复杂度：$O(n+m)$且不需要$O(1)LCA$

思路与我发的[简化版题目题解](https://www.luogu.com.cn/blog/mikiwang/solution-p5836)类似，记录每个询问的top即可。但由于这里有多种颜色，所以我们只能离线询问，对每个节点上挂的询问分别处理。

```
#include<cstdio>
#include<vector>
using std::vector;
typedef long long ll;
typedef long double ld;
const int N=1e5+10;
void file(const char *str){
    char in[100],out[100];
    sprintf(in,"%s.in",str),sprintf(out,"%s.out",str);
    freopen(in,"r",stdin),freopen(out,"w",stdout);
}
#define fast_io
#ifdef fast_io
const int _IB=1e6;
char _ibuf[_IB],*_s,*_t;
#define getchar()\
 (_s==_t&&(_t=(_s=_ibuf)+fread(_ibuf,1,_IB,stdin),_s==_t)?EOF:*_s++)
#endif
ll read(){
    ll a=0;int op=1;char ch=getchar();
    while(ch<'0'||'9'<ch){if(ch=='-')op=-1;ch=getchar();}
    while('0'<=ch&&ch<='9'){a=(a<<3)+(a<<1)+(48^ch);ch=getchar();}
    return a*op;
}
struct L{
    int to,next;
};
int head[N];
L l[N<<1];
int lcount;
void add(int from,int to){
    l[++lcount].to=to;
    l[lcount].next=head[from];
    head[from]=lcount;
}
#define REPL(S,I,T) for(int I=head[S],T;T=l[I].to,I;I=l[I].next)
int n,m;
int c[N];
int top[N];
int q[N];
int ans[N];
vector<int>mount[N];
void dfs(int now=1,int f=0){
    int buf=top[c[now]];
    for(int i=0;i<(int)mount[now].size();i++){
#define x mount[now][i]
        if(~ans[x]){
            ans[x]=(top[q[x]]!=ans[x]);
        }else{
            ans[x]=top[q[x]];
        }
#undef x
    }
    REPL(now,i,to)if(to!=f){
        top[c[now]]=to;
        dfs(to,now);
    }
    top[c[now]]=buf;
}
void input(){
    n=read();
    m=read();
    for(int i=1;i<=n;i++)c[i]=read();
    int p1,p2;
    for(int i=1;i<n;i++){
        p1=read();
        p2=read();
        add(p1,p2);
        add(p2,p1);
    }
    for(int i=0;i<m;i++){
        p1=read();
        p2=read();
        q[i]=read();
        if(c[p1]==q[i]||c[p2]==q[i]){
            ans[i]=1;
        }else{
            ans[i]=-1;
            mount[p1].push_back(i);
            mount[p2].push_back(i);
        }
    }
}
void ini(){
}
void solve(){
    dfs();
}
void output(){
    for(int i=0;i<m;i++)printf("%d",ans[i]);
}
void test(){
    input();
    ini();
    solve();
    output();
}
void all(){
    file("tmp");
    test();
}
int main(){
    all();
    return 0;
}
```
吐槽一句：一个写了$O(nlog^2n)$算法的人为什么会有自信说别人数据结构学傻了？

---

## 作者：serverkiller (赞：24)

# 牛奶之旅

~~你校提高组基础训练考树剖是真的狠。~~
## 题意:
给一棵树，问树上两点之间的最短路径上是否有某种颜色的节点。
## solution:
我们考虑求点$u$到点$v$的路径上是否有颜色为$c$的路径。

很naive地，我们可以考虑遍历这条路径 我们需要求这两个点的lca 然后从两个点分别遍历到lca，并且检查路径上是否有颜色为$c$的节点

这样很明显，复杂度是$O(n^2+nlogn)$的，在使用树剖之后，我们做到了小常数求lca，但是这样远远不够。

这个时候，我们考虑优化寻找某种颜色的节点的方法，注意到在重链上的dfn序是连续的，所以事实上我们是在每条重链上的$[dfn[top[u]],dfn[u]]$区间内寻找颜色为$c$的节点。

可以将所有颜色为$c$的节点的dfn序存到一个vector之中，然后问题就转化成了问一个数列中，是否存在一个数，在$[dfn[top[u]],dfn[u]]$内。

这个问题可以通过二分求大于等于$dfn[top[u]]$的最小的数$x$ 判断$x < dfn[u]$是否成立就可以解决这个问题，这样对于每个链上做到了$O(logn)$的判断是否有颜色为$c$的节点。

这样的总复杂度是$O(nlog^2n)$

事实上这个理论最坏复杂度很难被卡满

最后帖一下代码:
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
 
int n,m,a[100005],head[100005],pnt[200005],nxt[200005],E = 0;
int son[100005],siz[100005],fa[100005],top[100005],dfn[100005],rnk[100005],cnt = 0;
int ans[100005],qwq = 0;
vector <int> v[100005];
 
void add_edge(int u,int v)
{
    pnt[E] = v;
    nxt[E] = head[u];
    head[u] = E++;
}
 
void dfs1(int u,int f)
{
    siz[u] = 1;
    son[u] = -1;
    for (int i = head[u]; i != -1; i = nxt[i])
    {
        int v = pnt[i];
        if (v == f) continue;
        fa[v] = u;
        dfs1(v,u);
        siz[u] += siz[v];
        if (son[u] == -1 || siz[son[u]] < siz[v]) son[u] = v;
    }
}
 
void dfs2(int u,int tp)
{
    top[u] = tp;
    dfn[u] = ++cnt;
    rnk[cnt] = u;
    if (son[u] == -1) return ;
    dfs2(son[u],tp);
    for (int i = head[u]; i != -1; i = nxt[i])
    {
        int v = pnt[i];
        if (v == fa[u] || v == son[u]) continue;
        dfs2(v,v);
    }
}
 
signed main()
{
    memset(head,-1,sizeof(head));
    scanf("%lld%lld",&n,&m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld",&a[i]);
    }
    for (int i = 1; i < n; i++)
    {
        int u,v;
        scanf("%lld%lld",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    dfs1(1,1);
    dfs2(1,1);
    for (int i = 1; i <= cnt; i++)
    {
        v[a[rnk[i]]].push_back(i);
    }
    while (m--)
    {
        int a,b,c;
        scanf("%lld%lld%lld",&a,&b,&c);
        int flag = 0;
        while (top[a] != top[b])
        {
            if (dfn[top[a]] < dfn[top[b]]) swap(a,b);
            vector <int> :: iterator it = lower_bound(v[c].begin(),v[c].end(),dfn[top[a]]);
            if (it != v[c].end() && *it <= dfn[a])
            {
                flag = 1;
                break;
            }
            a = fa[top[a]];
        }
        if (!flag)
        {
            if (dfn[a] > dfn[b]) swap(a,b);
            vector <int> :: iterator it = lower_bound(v[c].begin(),v[c].end(),dfn[a]);
            if (it != v[c].end() && *it <= dfn[b]) flag = 1;
        }
        ans[++qwq] = flag;
    }
    for (int i = 1; i <= qwq; i++)
    {
        printf("%lld",ans[i]);
    }
    puts("");
    return 0;
}
```

---

## 作者：RedreamMer (赞：19)

[$\Large\texttt{P5838}$](https://www.luogu.com.cn/problem/P5838)

[$\small\texttt{In My cnblog}$](https://www.cnblogs.com/RedreamMer/p/13768013.html)

## 前言

这道题似乎是我遇到的第一道用 $\texttt{tarjan}$ 求 $\texttt{LCA}$ **思想**的题目，感谢一楼题解神仙的点拨

不会$\texttt{tarjan}$ 求 $\texttt{LCA}$ 的可以参考[我的博客](https://www.cnblogs.com/RedreamMer/p/13708436.html)~~（也没啥必要）~~



## 题意

给你一棵树，每个点有点权，每次询问节点 $n$ 到节点 $m$ 的路径上是否有点权为 $p$ 的点。

$n,m \le 10^5$



## 思路

以下$[n,m]$均表示为 $n$ 到 $m$ 的路径

观察 $n$ 到  $m$ 的路径，若路径上有点权为 $p$ 的点（我们只要找到一个这样的点，所以就假设这个点只有一个），那么可能在 $[\texttt{LCA}(n,m),n]$ 上，也可能在 $[\texttt{LCA}(n,m),m]$ 上。

如何记录这个点？

记录每个询问在 $[\texttt{LCA}(n,m),n]$ 上或许有些困难，我们发现其实维护 $DFS$ 访问到 $n$ 时 $[1,n]$ 上很好维护，如何利用起来？

可以发现一个性质，若有一个点权为 $p$ 的点在 $[1,n]$ 上，且它是点权为 $p$ 的在这路径上最深的，若它不在 $[\texttt{LCA}(n,m),n]$ 上，则没有点权为 $p$ 的在 $[\texttt{LCA}(n,m),n]$ 上~~(好像又是废话)~~。

并且，若这个权值为 $p$ 的节点不在 $[\texttt{LCA}(n,m),n]$ 上，也不在 $[\texttt{LCA}(n,m),m]$ 上，则 $[1,n]$ 和 $[1,m]$ 上的最深权值为 $p$ 的节点是**相同的**， **若不同，则答案为TRUE**

**因此：遍历到节点 $n$ ，只需记录 $[1,n]$ 上，每种 $C_i$ 的最深点**

发现这两条性质，就可以愉快做题了，因为$\forall C_i\le10^5$ ，完全可以给开一个桶（不用离散化），遍历到每一个节点 $n$ 时，维护好这个桶，遍历到点 $n$ 时，将关于 $n$ 的所有询问遍历一遍（先离线询问），若询问第一次遍历到，标记次询问，即 $[1,n]$ 上深度最低、点权为 $p$ 的节点，遍历到点 $m$ 时，比较标记的点与是否 $[1,m]$ 上中深度最低、点权为 $p$ 的节点是否相同，**不同则代表必定有一条路径上有要找的点权 $p$ 的节点**（注意特判这个点为 $\texttt{LCA}(n,m)$ ）。

为了特判 $\texttt{LCA}(n,m)$，可以在桶里面标记点权为 $p$ 的节点为它在 $[1,n]$ **这条链上**儿子。

注意特判询问 $n$ 和 $m$ 相等时 。

有时候看似很显然的性质，却有令人意想不到的思路。

时间复杂度 $\texttt{O(N + 2M)}$ 。

不管是码量还是效率，都远超大部分题解。



## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define PB push_back
const int N = 1e5;
inline char nc()
{
        static char buf[1000000], *p1 = buf, *p2 = buf;
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 1000000, stdin), p1 == p2) ? EOF : *p1++;
}
#define getchar nc
inline int read()
{
        int s = 0;
        register bool neg = 0;
        register char c = getchar();
        for (; c < '0' || c > '9'; c = getchar())
                neg |= (c == '-');
        for (; c >= '0' && c <= '9'; s = s * 10 + (c ^ 48), c = getchar())
                ;
        s = (neg ? -s : s);
        return s;
}

int a, b, s[N + 10], p[N + 10], ans[N + 10], top[N + 10];
vector<int> st[N + 10], ask[N + 10];

inline void dfs(int n, int fa)
{
        int pp = top[s[n]];
        for (int i = 0; i < ask[n].size(); i++)
        {
                int x = ask[n][i];
                if (ans[x] == -1)
                        ans[x] = top[p[x]];
                else
                        ans[x] = (top[p[x]] != ans[x]);
        }
        for (int i = 0; i < st[n].size(); i++)
        {
                int v = st[n][i];
                if (v == fa)
                        continue;
                top[s[n]] = v;
                dfs(v, n);
        }
        top[s[n]] = pp;
}

signed main()
{
        memset(ans, -1, sizeof(ans));
        a = read();
        b = read();
        for (int i = 1; i <= a; i++)
                s[i] = read();
        int x, y, z;
        for (int i = 1; i < a; i++)
        {
                x = read();
                y = read();
                st[x].PB(y);
                st[y].PB(x);
        }
        for (int i = 1; i <= b; i++)
        {
                x = read();
                y = read();
                p[i] = read();
                if (s[x] == p[i] || s[y] == p[i])
                        ans[i] = 1;
                ask[x].PB(i);
                ask[y].PB(i);
        }
        dfs(1, 0);
        for (int i = 1; i <= b; i++)
                printf("%d", ans[i]);
        return 0;
}
```



---

## 作者：KarL05 (赞：12)


## 树链剖分

看了一下题解，好像各位的做法比较复杂，这里介绍一下我的思路，希望可以帮到各位。

首先看到没有修改，**考虑离线。**

看到是链上的询问，**考虑树链剖分。**

因此问题可以转化为，$(u,v)$ 的若干个区间内是含有值为 $k$ 的值。

然后考虑数据结构部分，可以考虑主席树，但是过于复杂，这里提供一种解决的方式，如果在线，则需要同时考虑一个线段树区间是否包括很多个颜色，则会有很大的空间开销。

**区间查询，单点修改**

但是若是根据颜色排序然后在线段树中维护当前询问的值的话，则不需要考虑比它小的值 (由于已经询问过了)，也不需要考虑比他大的值 (因为还没有询问)，换句话来说，询问的顺序在满足单调性的前提之下，线段树中只需要维护当前颜色的数值。

## 则我们可以得到以下做法:

#### $O(n\log^2 n)$

### 树链剖分转换成区间查询

### 把询问根据颜色大小排序

### 维护线段树，维护线段中出现过最大的值 - 单点修改

线段树 - 单点修改
```
void update(int p,int pos,int cow) {
    if (t[p].l==t[p].r) {
        t[p].color = cow;
        return;
    }
    t[p].color = cow;
    int mid = (t[p].l+t[p].r)>>1;
    if(pos<=mid) update(p*2,pos,cow);
    if(pos>mid) update(p*2+1,pos,cow);
}
```

线段树 - 区间查询
```
bool query(int p,int x,int y,int cow) {
    if (x<=t[p].l && t[p].r<=y) return (t[p].color == cow);
    int mid = (t[p].l+t[p].r)>>1;
    if(x<=mid) {
        if (query(p*2,x,y,cow)) return true;
    }
    if(y>mid) {
        if (query(p*2+1,x,y,cow)) return true;
    }
    return false;
}
```

树链剖分查询
```
bool ask (int u, int v, int cow) {
    int fu = top[u];
    int fv = top[v];
    while (fu!=fv) {
        if (depth[fu]>depth[fv]) {
            if (query(1,id[fu],id[u],cow)) return true;
            u = fa[fu];
            fu = top[u];
        }
        else {
            if(query(1,id[fv],id[v],cow)) return true;
            v = fa[fv];
            fv = top[v];
        }
    }
    if (query(1,min(id[u],id[v]),max(id[u],id[v]),cow)) return true;
    return false;
}
```

主函数核心代码 
```
sort(q+1,q+1+m,cmp);
for (int i=1;i<=m;i++) {
    int col = q[i].color;
    if (!color[col].size()) continue;
    if (!vis[col]) {
        for (int j=0;j<color[col].size();j++) {
            int npos = color[col][j];
            update(1,id[npos],col);
        }
        vis[col] = 1;
    }
    ans[q[i].id] = ask(q[i].x,q[i].y,col);
}
```

---

## 作者：FZzzz (赞：12)

这……什么啊……大家ds都学傻了吗？

这题……是怎么想到主席树的啊？

------------
说下我的思路吧：

首先题意就是判一条路径上是否有某个点权的点。

显然树剖，然后问题就转到了序列上。

发现品种都在 $1$ 到 $n$ 之间（其实如果不是这样由于本题不带修也可以离散化），那我们就开 $n$ 个 `vector` 来把每一种的所有牛存下来。

然后看树剖序中一个区间是否有某一种牛就直接二分就行了。

最坏复杂度 $O(n\log^2n)$，常数很小，而且根本跑不满。

并且这东西还可以强制在线，带修就改成 `set` 就行了。

code：
```cpp
#include<algorithm>
#include<vector>
#include<cctype>
#include<cstdio>
using namespace std;
inline int readint(){
    int x=0;
    bool f=0;
    char c=getchar();
    while(!isdigit(c)&&c!='-') c=getchar();
    if(c=='-'){
        f=1;
        c=getchar();
    }
    while(isdigit(c)){
        x=x*10+c-'0';
        c=getchar();
    }
    return f?-x:x;
}
const int maxn=1e5+5;
int n,m,t[maxn];
vector<int> g[maxn];
int fa[maxn],dep[maxn],size[maxn],hson[maxn];
void dfs1(int u){
	dep[u]=dep[fa[u]]+1;
	size[u]=1;
	hson[u]=0;
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa[u]) continue;
		fa[v]=u;
		dfs1(v);
		size[u]+=size[v];
		if(size[v]>size[hson[u]]) hson[u]=v;
	}
}
int top[maxn],pos[maxn];
vector<int> f;
void dfs2(int u){
	pos[u]=f.size();
	f.push_back(u);
	if(hson[u]){
		top[hson[u]]=top[u];
		dfs2(hson[u]);
	}
	for(int i=0;i<g[u].size();i++){
		int v=g[u][i];
		if(v==fa[u]||v==hson[u]) continue;
		top[v]=v;
		dfs2(v);
	}
}
vector<int> v[maxn];
int main(){
    #ifdef LOCAL
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
    #endif
    n=readint();
    m=readint();
    for(int i=1;i<=n;i++) t[i]=readint();
    for(int i=1;i<n;i++){
    	int x,y;
    	x=readint();
    	y=readint();
    	g[x].push_back(y);
    	g[y].push_back(x);
	}
	fa[1]=0;
	dep[0]=0;
	size[0]=0;
	dfs1(1);
	top[1]=1;
	dfs2(1);
	for(int i=0;i<n;i++) v[t[f[i]]].push_back(i);
	while(m--){
		int a,b,c;
		a=readint();
		b=readint();
		c=readint();
		bool ok=0;
		while(top[a]!=top[b]){
			if(dep[top[a]]<dep[top[b]]) swap(a,b);
			vector<int>::iterator it=lower_bound(v[c].begin(),v[c].end(),pos[top[a]]);
			if(it!=v[c].end()&&*it<=pos[a]) ok=1;
			a=fa[top[a]];
		}
		if(!ok){
			if(dep[a]<dep[b]) swap(a,b);
			vector<int>::iterator it=lower_bound(v[c].begin(),v[c].end(),pos[b]);
			if(it!=v[c].end()&&*it<=pos[a]) ok=1;
		}
		printf("%d",ok);
	}
	printf("\n");
    return 0;
}
```


------------
所以说什么呢……ds不要学的太死，能 kiss 就 kiss 吧（别想歪，是 keep it simple and stupid），想太复杂反而不好，p5826 不是已经给我们了一个很好的例子吗？

---

## 作者：Y25t (赞：9)

**upd：本代码效率是$O(Nlog^3N)$。**

看到这题的第一个想法就是：

**树链剖分+线段树套平衡树（set）**

对于每个线段树节点维护一个set，记录该节点代表的区间有哪几种奶牛。

效率大概是$O(Nlog^3N)$，吸个氧就过了。

代码：

```cpp
#include<cstdio>
#include<algorithm>
#include<set>
#define N 100005

inline void rd(int &x){
	x=0;char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
} 

int n,m,a[N];

int hd[N],_hd;
struct edge{
	int v,nxt;
}e[N<<1];
inline void addedge(int u,int v){
	e[++_hd]=(edge){v,hd[u]};
	hd[u]=_hd;
}

int fa[N],dep[N],sz[N],son[N];
inline void dfs1(int u,int Fa){
	fa[u]=Fa;
	dep[u]=dep[Fa]+1;
	sz[u]=1;
	for(int i=hd[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==Fa)
			continue;
		dfs1(v,u);
		sz[u]+=sz[v];
		if(sz[v]>sz[son[u]])
			son[u]=v;
	}
}
int id[N],_id,pos[N],top[N];
inline void dfs2(int u){
	id[u]=++_id;
	pos[_id]=u;
	top[u]=u==son[fa[u]]?top[fa[u]]:u;
	if(son[u])
		dfs2(son[u]);
	for(int i=hd[u];i;i=e[i].nxt){
		int v=e[i].v;
		if(v==fa[u]||v==son[u])
			continue;
		dfs2(v);
	}
}

std::set<int> s[N<<2];
inline void build(int p,int L,int R){
	for(int i=L;i<=R;i++)
		s[p].insert(a[pos[i]]);
	if(L==R)
		return;
	int mid=(L+R)>>1;
	build(p<<1,L,mid);
	build(p<<1|1,mid+1,R);
}
inline bool sch(int p,int L,int R,int l,int r,int x){
	if(L>r||R<l)
		return 0;
	if(l<=L&&R<=r)
		return s[p].count(x);
	int mid=(L+R)>>1;
	return sch(p<<1,L,mid,l,r,x)||sch(p<<1|1,mid+1,R,l,r,x);
}

inline bool lca_sch(int u,int v,int x){
	while(top[u]!=top[v]){
		if(dep[top[u]]<dep[top[v]])
			std::swap(u,v);
		if(sch(1,1,n,id[top[u]],id[u],x))
			return 1;
		u=fa[top[u]];
	}
	if(dep[u]<dep[v])
		std::swap(u,v);
	return sch(1,1,n,id[v],id[u],x);
}

int main(){
//	freopen("milkvisits.in","r",stdin);
//	freopen("milkvisits.out","w",stdout);
	rd(n),rd(m);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<n;i++){
		int u,v;
		rd(u),rd(v);
		addedge(u,v);
		addedge(v,u);
	}
	dfs1(1,0);
	dfs2(1);
	build(1,1,n);
	while(m--){
		int u,v,x;
		rd(u),rd(v),rd(x);
		printf("%d",lca_sch(u,v,x));
	}
	
	#define w 0
	return ~~('0')?(0^w^0):(0*w*0);
}
```


---

## 作者：lzyqwq (赞：8)

[**更好的阅读体验**](https://www.cnblogs.com/MnZnOIerLzy/articles/17114627.html)

# $\texttt{Description}$


**[洛谷题目链接](https://www.luogu.com.cn/problem/P5838 "洛谷题目链接")**

> - 有一棵 $n$ 个节点的树，第 $i$ 个节点有颜色 $a_i$，$q$ 次询问，每次询问 $u,v$ 节点之间（含）是否存在颜色为 $w$ 的节点。
>
> - $n,q\le 10^5$，$1\le a_i,w\le n$。

# $\texttt{Solution}$

和[**洛谷 P3313**](https://www.luogu.com.cn/problem/P3313 "洛谷 P3313") 一样，对于这类维护颜色的问题，可以考虑使用**动态开点线段树**来解决。

首先进行**树链剖分**把树上路径问题转化成序列问题，然后对每种颜色建立线段树。由于是存在性的问题，可以考虑建树时将每个点权值赋成 $1$，维护区间**或和**。

对于每次询问，在颜色 $c$ 对应的线段树上跳链查询即可。

时间复杂度为 $\mathcal{O}((n+q)\log^2n)$，空间复杂度为 $\mathcal{O}(n\log n)$，可以接受。


# $\texttt{Code}$

代码实现时一些小细节：

- 我使用指针实现动态开点线段树，注意判左右儿子是不是 `NULL`。以及修改的时候参数传的是地址，否则修改的不是线段树本身，而是形参创造的一个副本（个人理解，轻喷）。

- 查询或合并左右儿子的时候如果遇到了 $1$ 就直接返回，因为已经说明存在性了。

[**评测记录**](https://www.luogu.com.cn/record/102039319)



```cpp
#include<bits/stdc++.h>
#define N 100005
#define ls x->lson
#define rs x->rson
using namespace std;
int n,q,a[N],h[N],t[N],d[N],f[N],sz[N],dfn[N];
struct node{
    bool v;
    node*lson,*rson;
}*rt[N];
vector<int>g[N];
void dfs1(int u,int fa){
    sz[u]=1;
    for(int v:g[u]){
        if(v^fa){
            d[v]=d[u]+1;
            dfs1(v,f[v]=u);
            sz[u]+=sz[v];
        }
    }
}
void dfs2(int u,int fa){
    for(int v:g[u]){
        if(v^fa){
            if((sz[v]<<1)>sz[u]){
                t[h[u]=v]=t[u];
            }else{
                t[v]=v;
            }
            dfs2(v,u);
        }
    }
}
void dfs3(int u,int fa){
    dfn[u]=++dfn[0];
    if(h[u]){
        dfs3(h[u],u);
    }
    for(int v:g[u]){
        if((v^fa)&&(v^h[u])){
            dfs3(v,u);
        }
    }
}
void add(node*&x,int l,int r,int k){
    if(x==NULL){
        x=new node;
    }
    if(l^r){
        int m=(l+r)>>1;
        if(k<=m){
            add(ls,l,m,k);
        }else{
            add(rs,m+1,r,k);
        }
        x->v=0;
        if(ls!=NULL){
            x->v|=ls->v;
        }
        if(x->v){
            return;
        }
        if(rs!=NULL){
            x->v|=rs->v;
        }
    }else{
        x->v=1;
    }
}
bool query(node*x,int l,int r,int ql,int qr){
    if(ql<=l&&r<=qr){
        return x->v;
    }
    int m=(l+r)>>1;
    bool v=0;
    if(ql<=m&&ls!=NULL){
        v|=query(ls,l,m,ql,qr);
    }
    if(v){
        return 1;
    }
    if(qr>m&&rs!=NULL){
        v|=query(rs,m+1,r,ql,qr);
    }
    return v;
}
bool chainquery(int x,int y,int c){
    bool v=0;
    while(t[x]^t[y]){
        if(d[t[x]]<d[t[y]]){
            swap(x,y);
        }
        v|=query(rt[c],1,n,dfn[t[x]],dfn[x]);
        if(v){
            return 1;
        }
        x=f[t[x]];
    }
    if(d[x]>d[y]){
        swap(x,y);
    }
    return query(rt[c],1,n,dfn[x],dfn[y]);
}
int main(){
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i){
        scanf("%d",a+i);
    }
    for(int i=1,u,v;i<n;++i){
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(1,0);
    dfs2(t[1]=1,0);
    dfs3(1,0);
    for(int i=1;i<=n;++i){
        add(rt[a[i]],1,n,dfn[i]);
    }
    for(int i=1,u,v,w;i<=q;++i){
        scanf("%d%d%d",&u,&v,&w);
        if(rt[w]==NULL){
            putchar(48);
            continue;
        }
        printf("%d",chainquery(u,v,w));
    }
}
```


---

## 作者：kradcigam (赞：5)

这题一眼看出了可以用主席树维护暴力在线的做法，时间复杂度 $O(n \log^2n)$。方法类比[宝石](https://www.luogu.com.cn/problem/P7518)。

后来在想出了一个 $O(n \log n)$ 的做法，不需要任何高级数据结构。

这题用主席树的话，会发现所有查询都是已知的，不会有任何改变，且总查询次数是在 $O(m)$ 级别的。

我们可以将所有需要的询问都先存下来，然后一遍 $dfs$ 遍历解决所有询问，瓶颈在于求 LCA，时间复杂度 $O(n \log n)$。

```cpp
#include<bits/stdc++.h>
#define pb push_back
#define F(i,a,b) for(int i=(a);i<=(b);++i)
#define DF(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
inline int read(){char ch=getchar(); int w=1,c=0;
	for(;!isdigit(ch);ch=getchar()) if (ch=='-') w=-1;
	for(;isdigit(ch);ch=getchar()) c=(c<<1)+(c<<3)+(ch^48);
	return w*c;
}
const int N=1e5+10,M=1e5+10;
int n,m,t[N],dep[N],fa[25][N],a[M],b[M],c[M],k[M],pos[3][M],kind[N];
vector<int>v[N],qry[N],asw[N];
void dfs(int x,int fa){
	dep[x]=dep[fa]+1;::fa[0][x]=fa;
	F(i,1,20)::fa[i][x]=::fa[i-1][::fa[i-1][x]];
	for(int i:v[x])
		if(i!=fa)dfs(i,x);
}
int lca(int x,int y){
	if(dep[x]>dep[y])swap(x,y);
	DF(i,20,0)
		if(dep[fa[i][y]]>=dep[x])y=fa[i][y];
	if(x==y)return x;
	DF(i,20,0)
		if(fa[i][x]!=fa[i][y])x=fa[i][x],y=fa[i][y];
	return fa[0][x];
}
void dfs2(int x,int fa){
	kind[t[x]]++;
	for(int i:qry[x])asw[x].pb(kind[i]);
	for(int i:v[x])
		if(i!=fa)dfs2(i,x);
	kind[t[x]]--;
}
signed main(){
	n=read();m=read();
	F(i,1,n)t[i]=read();
	F(i,2,n){
		int x=read(),y=read();
		v[x].pb(y);
		v[y].pb(x);
	}
	dfs(1,0);
	F(i,1,m){
		a[i]=read(),b[i]=read(),c[i]=read();
		k[i]=lca(a[i],b[i]);
		pos[0][i]=qry[a[i]].size();
		qry[a[i]].pb(c[i]);
		pos[1][i]=qry[b[i]].size();
		qry[b[i]].pb(c[i]);
		pos[2][i]=qry[k[i]].size();
		qry[k[i]].pb(c[i]);
	}
	dfs2(1,0);
	F(i,1,m)
		putchar(asw[a[i]][pos[0][i]]+asw[b[i]][pos[1][i]]-asw[k[i]][pos[2][i]]*2+(t[k[i]]==c[i])?'1':'0');
	return 0;
}
```


---

## 作者：hater (赞：4)

蒟蒻表示太菜了不会主席树

只能菜菜的用树上莫队 

讲讲树上莫队吧 ：

众所周知 ， 

莫队一般是离线在序列上的 

解决关于区间和颜色的问题 

后人又在此基础上弄出带修的莫队

但是跟本题无关 所以不谈

如果把序列放在树上 莫队似乎有不可行了 

利用树剖的dfs序是无法胜任的 

这个时候就有一个叫**欧拉序**的玩意 

欧拉序是这样组成的 

1 . 把根节点加入序 （ 记为$in$）

2 . 访问子树 

3 . 又把根节点加入序中 ( 记为 $out$ ) 

那么显然 一颗 节点数为n的树 欧拉序长度为 2*n 

回看题目 题目给出两个点

两个节点对应着欧拉序的四个端点 

如果两个节点在一条链上 那么 区间端点就是$in_{x}$到$in_{y}$

如果两个节点不在一条链上 那么 区间端点就是$out_{x}$到$in_{y}$ 

而且这个时候 x y 的 lca 不在区间里 但是根据题目要求需要统计

x y 的 lca 还需要特判处理

在这段数列中 出现2次的数不是路径上的节点 

我们只关心出现1次的节点 

code : 

```cpp
#include <bits/stdc++.h> 
#define MAX 100005 
#define IL inline 
#define Rg register 
using namespace std ; 
vector <int> v[MAX] ;   
int son[MAX] , siz[MAX] , pre[MAX] , dep[MAX] , top[MAX] , Ans[MAX] ; 
int in[MAX] , a[MAX] , out[MAX] , n , m ,  tot , lis[MAX*2] , pos[MAX*2] , num[MAX] ;  
struct Node { 
	int l , r , id , lca , c ; 
} Ask[MAX] ; bool vis[MAX] ;  
bool cmp ( Rg Node A , Rg Node B ) { 
	if( pos[A.l] == pos[B.l] ) return  A.r < B.r ;
	return A.l < B.l ; 
}  
IL void dfs1( int x , int fa ) { 
    siz[x] = 1 ;  dep[x] = dep[fa]+1 ; 	pre[x] = fa ; 
	for(Rg int i=0; i<v[x].size(); i++) {
		int u = v[x][i] ; if( u == fa ) continue ;
		dfs1( u , x ) ; siz[x] += siz[u] ;
		if( siz[son[x]] < siz[u] ) son[x] = u ;  
	}
} 
IL void dfs2( int x ) { 
	if( son[x] )  top[son[x]] = top[x] , dfs2( son[x] ) ; 
	for(Rg int i=0; i<v[x].size(); i++) {
		int u = v[x][i] ; 
		if( u == pre[x] || u == son[x] ) continue ;
		top[u] = u ; dfs2( u ) ;    
	}  
} 
IL void dfs( int x ) { 
	in[x] = ++tot ; lis[tot] = x ; 
	for(Rg int i=0; i<v[x].size(); i++) {
		int u = v[x][i] ; 
		if( u == pre[x] ) continue ;
		dfs( u ) ; 
	} out[x] = ++tot ; lis[tot] = x ;  
} 
IL int Lca ( Rg int x , Rg int y ) { 
	Rg int fx = top[x] , fy = top[y] ;
	while( fx != fy ) {
		if( dep[fx] < dep[fy] ) swap( x , y ) , swap( fx , fy ) ;
		x = pre[fx] ; fx = top[x]; 
	} 
	if( dep[x] > dep[y] ) swap( x , y ) ;
	return x ; 
}   
IL void Work( Rg int whe ) {   
	if( vis[lis[whe]] == 0 ) num[a[lis[whe]]]++ , vis[lis[whe]] = 1 ;    
	 else num[a[lis[whe]]] -- , vis[lis[whe]] = 0 ; 
} 
signed main() {  
    Rg int x , y , z ; 
	ios::sync_with_stdio(false) ; 
	cin.tie(0) ; cout.tie(0) ; 
	cin >> n >> m ; 
	for(Rg int i=1; i<=n; i++) 
	  cin >> a[i] ; 
	for(Rg int i=1; i<n; i++) { 
		cin >> x >> y ; 
		v[x].push_back(y) ;  
		v[y].push_back(x) ; 
	} 
	Rg int Rot = rand()%n+1 , block = sqrt(2*n) ;  
	dfs1( Rot , 0 ) ; dfs2( Rot ) ; dfs( Rot ) ;   
	for(Rg int i=1; i<=2*n; i++) 
	  pos[i] = (i-1)/block+1 ; 
	for(Rg int i=1; i<=m; i++) { 
		cin >> x >> y >> Ask[i].c ;  Ask[i].id = i ;  
		if( x == y ) { 
			Ask[i].l = in[x] , Ask[i].r = in[x] ; 
			Ask[i].lca = -1 ;  continue ; 
		}  z = Lca( x , y ) ;  
		if( in[x] > in[y] ) swap( x , y ) ;   
		if( z == x ) Ask[i].l = in[x] , Ask[i].r = in[y] , Ask[i].lca = -1 ;  
		 else Ask[i].l = out[x] , Ask[i].r = in[y] , Ask[i].lca = z ; 
	}  sort( Ask+1 , Ask+1+m , cmp ) ;  
	Rg int l = 1 , r = 0 ;   
	for(Rg int i=1; i<=m; i++) {  
		while( Ask[i].l < l ) Work( --l ) ;   
		while( r < Ask[i].r ) Work( ++r ) ;  
		while( l < Ask[i].l ) Work( l++ ) ;   
		while( Ask[i].r < r ) Work( r-- ) ;     
		if( Ask[i].lca != -1 )  Work( in[Ask[i].lca] ) ;
		Ans[Ask[i].id] = num[Ask[i].c] ;  
		if( Ask[i].lca != -1 )  Work( in[Ask[i].lca] ) ;
	} 
	for(Rg int i=1; i<=m; i++) 
	 if( Ans[i] == 0 ) cout << 0 ; 
	  else cout << 1 ; cout << endl; 
	return 0 ; 
}
```

o2 才能过 莫队差不多都是吸氧跑的飞快







---

## 作者：7KByte (赞：4)

抢第一篇题解


本题作为银组$T3$加强版，确实加强了不少(雾


仔细观察问题，我们发现我们要解决的实际上是


>查询一条链上是否有颜色$C$


更加良心的是本题不带修改


这不是$Count\ on\ tree$的改编吗


直接$Dfs+\text{主席树}$即可


```cpp
#include<bits/stdc++.h>
#define rep(i,a,b) for(int i=a;i<=b;i++)
using namespace std;
struct node{
	int l,r;
	int val;
}t[200005*20];
int c[200005],root[200005];
int n,m,tot=0;
int build(int l,int r){
	int p=++tot;
	t[p].val=0;
	if(l==r)return p;
	int mid=(l+r)>>1;
	t[p].l=build(l,mid);
	t[p].r=build(mid+1,r);
	return p;
}
int insert(int now,int l,int r,int where){
	int p=++tot;t[p]=t[now];
	if(l==r){
		t[p].val++;
		return p;
	}
	int mid=(l+r)>>1;
	if(mid>=where)t[p].l=insert(t[now].l,l,mid,where);
	else t[p].r=insert(t[now].r,mid+1,r,where);
	return p;
}
int ask(int p,int q,int x,int y,int l,int r,int where){
	if(l==r)return t[p].val+t[q].val-t[x].val-t[y].val;
	int mid=(l+r)>>1;
	if(mid>=where)return ask(t[p].l,t[q].l,t[x].l,t[y].l,l,mid,where);
	return ask(t[p].r,t[q].r,t[x].r,t[y].r,mid+1,r,where);
}
#define N 100005
int h[N],tt;
struct edge{
	int to,nxt;
}e[N<<2];
void add(int x,int y){
	e[++tt].to=y;e[tt].nxt=h[x];h[x]=tt;
}
int f[N][20],mt,d[N];
void dfs(int x,int fa){
	d[x]=d[fa]+1;f[x][0]=fa;
	rep(i,1,mt)f[x][i]=f[f[x][i-1]][i-1];
	root[x]=insert(root[fa],1,n,c[x]);
	for(int i=h[x];i;i=e[i].nxt){
		if(e[i].to!=fa)dfs(e[i].to,x);
	}
}
int lca(int x,int y){
	if(d[x]<d[y])swap(x,y);
	for(int i=mt;i>=0;i--)if(d[f[x][i]]>=d[y])x=f[x][i];
	if(x==y)return x;
	for(int i=mt;i>=0;i--)if(f[x][i]^f[y][i])x=f[x][i],y=f[y][i];
	return f[x][0];
}
int ans[N];
int main()
{
	//freopen("testdata(8).in","r",stdin);
	//freopen("testdata(8).out","w",stdout);
	//freopen("milkvisits.in","r",stdin);
	//freopen("milkvisits.out","w",stdout);
	scanf("%d%d",&n,&m);
	rep(i,1,n)scanf("%d",&c[i]);
	root[0]=build(1,n);
	rep(i,1,n-1){
		int x,y;scanf("%d%d",&x,&y);
		add(x,y);add(y,x);
	}
	mt=log2(n);
	dfs(1,0);
	rep(i,1,m){
		int x,y,z;scanf("%d%d%d",&x,&y,&z);
		int L=lca(x,y);
		ans[i]=(ask(root[x],root[y],root[L],root[f[L][0]],1,n,z)?1:0);
	}
	rep(i,1,m)printf("%d",ans[i]);
	putchar('\n');
	return 0;
}

```

---

## 作者：Parabola (赞：4)

#### Part0. 题外话
首先，奶牛社保

然后因为去陪女朋友了所以没有打这场usaco（手动滑稽）

回到学校发现一堆同学都卡在金了，于是我就问了下题。

觉得是三道sb题，全部跟他们口胡了一遍，他们说做不出来这道。

于是现在我有时间了就把口胡实现一下~

#### Part1.思路

看到树上路径，考虑树链剖分，将一条路径拆成$\log N$条序列上的区间。

接着，考虑原问题在序列上的转化。

一段序列中，是否存在一个数？

这个时候我看到其它的题解就直接上线段树加set了，这种就是数据结构学傻了的典范。有的时候很多简单的问题，用基础知识就能解决，但我们只想着硬上数据结构。

注意到权值范围是与点的个数范围相同的，我们给每个权值开一个vector，每个vector中存这个权值在序列上出现的位置。

那么，询问一段区间$(l,r)$中是否存在$x$，只用在x的vector中把$l$,$r$扔进去二分即可。只要存在x，那么两个数二分的结果应该不相同。

这个做法的好处一个是好写，第二个是它不但可以处理是否存在，还可以处理出现次数。

时间复杂度$O(N \log^2 N)$，注意到这两个$\log$分别是树链剖分和二分查找的$\log$，常数很小，吸口氧甚至能艹一部分一只log的主席树。

#### Part2.Code

```
#include<bits/stdc++.h>
using namespace std;
#define rep(i , a , b) for(int i = (a) ; i <= (b) ; ++i)
#define irep(i , a , b) for(int i = (b) ; i >= (a) ; --i)
#define IO ios::sync_with_stdio(false)
#define ms(A) memset(A , 0 , sizeof A)
#define msinf(A) memset(A , 0x3f , sizeof A)
typedef long long ll;
typedef pair <int , int> pii;

const int inf = 0x3f3f3f3f;
const ll infLL = 0x3f3f3f3f3f3f3f3fLL;

const int N = 100000 + 5;

int n , m , A[N];
int tot , ver[N << 1] , nxt[N << 1] , head[N];
vector <int> p[N];

int f[N] , dep[N] , sz[N] , son[N] , top[N] , num[N] , id[N];

inline void add(int u , int v) {
	ver[++tot] = v;
	nxt[tot] = head[u];
	head[u] = tot;
}

int dfs(int u , int fa) {
	sz[u] = 1; f[u] = fa; dep[u] = dep[fa] + 1;
	for(int i = head[u] , v ; i ; i = nxt[i]) {
		if((v = ver[i]) == fa) continue;
		sz[u] += dfs(v , u);
		if(sz[son[u]] < sz[v]) son[u] = v;
	}
	return sz[u];
}

void Get(int u , int tp) {
	top[u] = tp;
	id[num[u] = ++num[0]] = u;
	if(son[u]) Get(son[u] , tp);
	for(int i = head[u] , v ; i ; i = nxt[i]) {
		if((v = ver[i]) == f[u] || v == son[u]) continue;
		Get(v , v);
	}
}

inline bool query(int u , int v , int k) {
	bool ans = 0;
	while(top[u] != top[v]) {
		if(dep[top[u]] < dep[top[v]]) swap(u , v);
		if(upper_bound(p[k].begin() , p[k].end() , num[u]) - lower_bound(p[k].begin() , p[k].end() , num[top[u]]))
			return 1;
		u = f[top[u]];
	}
	if(dep[u] < dep[v]) swap(u , v);
	return upper_bound(p[k].begin() , p[k].end() , num[u]) - lower_bound(p[k].begin() , p[k].end() , num[v]);
}

int main() {
	scanf("%d %d" , &n , &m);
	rep(i , 1 , n) scanf("%d" , A + i);
	rep(i , 1  , n - 1) {
		int u , v;
		scanf("%d %d" , &u , &v);
		add(u , v); add(v , u);
	}
	dfs(1 , 0); Get(1 , 1);
	rep(i , 1 , n) p[A[id[i]]].push_back(i);
	rep(i , 1 , m) {
		int u , v , k;
		scanf("%d %d %d" , &u , &v , &k);
		printf("%d" , query(u , v , k));
	}
	return 0;
} 
```


---

## 作者：JS_TZ_ZHR (赞：3)

看了一下题解，发现都是（我不会的）平衡树，主席树和神仙离线线性算法等，还没有分块题解，就交了这一发。

题目的意思是给出一棵树和树上每个点的点权，每次给出树上的两个节点$a$,$b$，求两节点之间的简单路径上有没有节点的权值为$c$。我的思路是用树剖把树上操作转移到序列上来，再用分块维护。

先说分块，分块是把应该序列平均分成$\lceil\frac{n}{\lfloor\sqrt{n}\rfloor}\rceil$个长度为$\lfloor\sqrt{n}\rfloor$的块来维护，不过最后一个块会短一点。在查询的时候，边角块直接暴力，一个整块直接二分，单次查询的复杂度为$O(\sqrt{n})$。

再说树链剖分,这是一个通过把树分成几条互不相交的链，从而让分块，线段树这样用来维护序列的数据结构可以用在树上。这里的树剖是轻重链剖分，优先遍历节点中子树最大的儿子，给每个节点标记一下$dfs$序，维护时根据$dfs$序当做序列维护就可以了。

代码不长，不到90行，2.91$s$，时间复杂度$O(n\sqrt{n}\log^2n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[100005],u,v,p[100005],sum[100005],top[100005];
int son[100005],dep[100005],size[100005],f[100005];
int begin[100005],end[100005],s[100005],block,cnt;
vector<int>ve[100005];
void dfs1(int now,int fa,int deep) {//预处理 
	dep[now]=deep;
	f[now]=fa;
	size[now]=1;
	int maxsize=0;
	for(int i=0; i<ve[now].size(); i++) {
		int y=ve[now][i];
		if(y==fa)continue;
		dfs1(y,now,deep+1);
		if(size[y]>maxsize)maxsize=size[y],son[now]=y;
		size[now]+=size[y];
	}
	return;
}
void dfs2(int now,int _top) {
	top[now]=_top;
	p[now]=++cnt;
	sum[cnt]=a[now];
	if(!son[now])return;
	dfs2(son[now],_top);//先访问重儿子 
	for(int i=0; i<ve[now].size(); i++) {
		int y=ve[now][i];
		if(y==f[now]||y==son[now])continue;
		dfs2(y,y);
	}
	return;
}
void build() {
	block=sqrt(n);
	int total=0;
	for(int i=1; i<=n; i++)s[i]=sum[i];
	for(int i=1; i<=n; i+=block) {
		total++;
		begin[total]=i;
		end[total]=min(n,i+block-1);
		sort(s+i,s+min(n,i+block-1)+1);//排序，便于二分 
	}
	return;
}
bool find1(int l,int r,int k) {
	int numl=l/block+(l%block!=0),numr=r/block+(r%block!=0);
	if(numl==numr) {
		for(int i=l; i<=r; i++)if(sum[i]==k)return true;
		return false;
	}
	for(int i=l; i<=end[numl]; i++)if(sum[i]==k)return true;
	for(int i=begin[numr]; i<=r; i++)if(sum[i]==k)return true;
	for(int i=numl+1; i<numr; i++) {
		int z=s[lower_bound(s+begin[i],s+end[i]+1,k)-s];//块内二分 
		if(z==k)return true;
	}
	return false;
}
bool find2(int x,int y,int k) {
	while(top[y]!=top[x]) {
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		if(find1(p[top[x]],p[x],k))return true;
		x=f[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	return find1(p[x],p[y],k);
}
int main() {
	scanf("%d%d",&n,&m);
	for(int i=1; i<=n; i++)scanf("%d",&a[i]);
	for(int i=1; i<n; i++) {
		scanf("%d%d",&u,&v);
		ve[u].push_back(v);
		ve[v].push_back(u);
	}
	dfs1(1,0,1);
	dfs2(1,1);
	build();
	int x,y,z;
	while(m--) {
		scanf("%d%d%d",&x,&y,&z);
		if(find2(x,y,z))printf("1");
		else printf("0");
	}
}
```


---

## 作者：红尘仙 (赞：2)

### 写在前面
这份代码并不能够直接AC，你改改块长应该是可以的， 但是你来口氧，跑的就贼快。 

双倍经验 ：[SP11985 GOT - Gao on a tree](https://www.luogu.com.cn/problem/SP11985)

### 正文
+ 点有点权 
+ 查询树上两点路径上是否存在一个点权为 c 的点 。

因为这道题是查询树上两点间的路径，那么我们就很显然能够想到树链剖分。然后我们对 $id$ 这个值建立一棵线段树，但是线段树不能够区间查询某一个点，然后我们建立平衡树，也就是树套树，那么这时候我们发现，是不是过于麻烦了，只是为了查询一下点是否在这条路径上，所以我们考虑一下分块，给下变量说明：

+ $b_i$ 剖完之后每一个点对应的权值，计算的话，就是 $b_{id_i} = a_i$

那么流程就为 : 
+ 先进行一下树链剖分，得到我们的 $b_i$ 这个值，然后我们建立分块。

> 先说明一下，我的分块向来比较丑，但是很好写，需要吸氧。

+ 分完块之后我们就可以直接查询，不再需要什么其他的 $nb$ 操作了。 


这里给一个函数 $find$ ，相信有的大佬是明白他的，因为我的二分写挂了，所以用的是这个

```
/*
By : Zmonarch
*/
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#define int long long
#define qwq register
const int kmaxn = 1e6 + 10 ;
const int kmod = 998244353 ;
inline int read() {
	int x = 0 , f = 1 ; char ch = getchar() ;
	while(!isdigit(ch)) {if(ch == '-') f = - 1 ; ch = getchar() ;}
	while( isdigit(ch)) {x = x * 10 + ch - '0' ; ch = getchar() ;}
	return x * f ;
}
std::vector<int> block[kmaxn] ; 
int n , m , tot , cnt , len; 
struct node{
	int nxt , u , v , val ; 
}e[kmaxn << 1]; 
int h[kmaxn << 1] , siz[kmaxn] , id[kmaxn] , f[kmaxn] , top[kmaxn] , a[kmaxn] , b[kmaxn] , pos[kmaxn]; 
int dep[kmaxn] , son[kmaxn] , ans[kmaxn]; 
inline void add(int u , int v) {
	e[++tot].nxt = h[u] ; 
	e[tot].u = u ; 
	e[tot].v = v ; 
	h[u] = tot ; 
}
inline void dfs1(int u , int fa) {
	f[u] = fa ; siz[u] = 1 ; 
	dep[u] = dep[fa] + 1 ; 
	for(qwq int i = h[u] ; i ; i = e[i].nxt) 
	{
		int v = e[i].v ; 
		if(v == fa) continue ; 
		dfs1(v , u) ; 
		siz[u] += siz[v] ; 
		if(siz[son[u]] < siz[v]) son[u] = v ; 
	}
}
inline void dfs2(int u , int ftop) {
	top[u] = ftop ; id[u] = ++ cnt ; 
	if(son[u]) dfs2(son[u] , ftop) ; 
	for(qwq int i = h[u] ; i ; i = e[i].nxt) 
	{
		int v = e[i].v ; 
		if(v == f[u] || v == son[u]) continue ; 
		dfs2(v , v) ; 
	}
}
inline int query(int l , int r , int c) {
	int p = pos[l] , q = pos[r] ; 
	for(qwq int i = l ; i <= std::min(p * len , r) ; i++) 
	if(b[i] == c) return 1 ; 
	if(p != q) 
	 for(qwq int j = (q - 1) * len + 1 ; j <= r ; j++) 
	  if(b[j] == c) return 1 ;
	for(qwq int i = p + 1 ; i <= q - 1 ; i++) 
	{
		std::vector<int>::iterator x = std::find(block[i].begin() , block[i].end() , c);  
		if(x == block[i].end()) continue ;  
		if(x != block[i].end()) return 1 ;
	}
	return 0 ; 
}
inline int Query(int u , int v , int c) {
	while(top[u] ^ top[v]) 
	{
		if(dep[top[u]] < dep[top[v]]) std::swap(u , v) ; 
		int fl = query(id[top[u]] , id[u] , c) ; 
		if(fl == 1) return 1 ; 
		u = f[top[u]] ; 
	}
	if(dep[u] > dep[v]) std::swap(u , v) ; 
	return query(id[u] , id[v] , c);
}
signed main() {
	n = read() , m = read() , len = sqrt(n) ; 
	for(qwq int i = 1 ; i <= n ; i++) a[i] = read() ; 
	for(qwq int i = 1 ; i <= n - 1 ; i++) 
	{
		int u = read() , v = read() ; 
		add(u , v) ; add(v , u) ; 
	}
	dfs1(1 , 0) ; dfs2(1 , 1) ; 
	for(qwq int i = 1 ; i <= n ; i++) b[id[i]] = a[i] ; 
	for(qwq int i = 1 ; i <= n ; i++)
	{
		pos[i] = (i - 1) / len + 1 ; 
		block[pos[i]].push_back(b[i]) ; 
	}
	for(qwq int i = 1 ; i <= pos[n] ; i++) 
	std::sort(block[i].begin() , block[i].end()) ; 
	for(qwq int i = 1 ; i <= m ; i++) 
	{
		int u = read() , v = read() , c = read() ; 
		ans[i] = Query(u , v , c); 
	}
	for(qwq int i = 1 ; i <= m ; i++) 
	printf("%lld" , ans[i]) ; 
	return 0 ;
}
```

---

## 作者：Martin_MHT (赞：2)

思路来自@[alpha1022](https://www.luogu.com.cn/user/75840)

~~我MHT就是爆零，从这里原地爆零，也不会学一点树剖~~  

好了，这题有很多树剖的解法，但是~~爷不会~~我想要追求极致简洁——那么我就说说这位大佬的思路。

既然可以离线，那就要好好利用，我们知道一个询问可以分成三部分：$u$， $v$和$lca(u,v)$，那么就可以把每一个询问挂在树上，在dfs的时候求出从根节点到这三个点的颜色分别的个数，并把每一个当前点上的询问处理掉

很明显是$O(n+m)$的。（感谢@wlzhouzhuan指出问题，LCA是$O(n\log n)$）的，不过希望您能友好交流。

```cpp
#include <cstdio>
#include <vector>
#define N 100010
#define gc getchar
#define fo(i, a, b) for(int i = (a); i <= (b); ++i)
#define fd(i, a, b) for(int i = (a); i >= (b); --i)
using namespace std;
int n, q, ans[N], a[N], qaq[N], dep[N], f[N][20], sum[N];
int head[N], len;
struct Edge
{
	int v, x;
}edge[N << 1];
struct Opt
{
	int tp, id;
};
vector<Opt> p[N];
void add(int u, int v)
{
	edge[++len] = (Edge){v, head[u]};
	head[u] = len;
}
void dfs1(int u, int fat)
{
	dep[u] = dep[fat] + 1;
	f[u][0] = fat;
	fo(i, 1, 19)
		f[u][i] = f[f[u][i - 1]][i - 1];
	for(int i = head[u]; i; i = edge[i].x)
	{
		int v = edge[i].v;
		if(v == fat)	continue ;
		dfs1(v, u);
	}
}
void dfs2(int u, int fat)
{
	++sum[a[u]];
	int sz = p[u].size();
	for(int i = 0; i < sz; ++i)
	{
		Opt t = p[u][i]; int tsc = qaq[t.id];
		if(t.tp == 1)	ans[t.id] += sum[tsc];
		else ans[t.id] += (a[u] == tsc) - (sum[tsc] << 1);
	}
	for(int i = head[u]; i; i = edge[i].x)
	{
		int v = edge[i].v;
		if(v == fat)	continue ;
		dfs2(v, u);
	}
	--sum[a[u]];
}
int lca(int u, int v)
{
	if(dep[u] < dep[v]){int t = u; u = v; v = t;}
	fd(i, 19, 0)
		if(dep[f[u][i]] >= dep[v])
			u = f[u][i];
	if(u == v)	return u;
	fd(i, 19, 0)
		if(f[u][i] != f[v][i])
			u = f[u][i], v = f[v][i];
	return f[u][0];
}
int main()
{
//	freopen("milkvisits.in", "r", stdin);
//	freopen("milkvisits.out", "w", stdout);
	scanf("%d %d", &n, &q);
	fo(i, 1, n)	scanf("%d", &a[i]);
	int u, v;
	fo(i, 2, n)
	{
		scanf("%d %d", &u, &v);
		add(u, v); add(v, u);
	}
	dfs1(1, 0);
	fo(i, 1, q)
	{
		scanf("%d %d %d", &u, &v, &qaq[i]);
		int fkw = lca(u, v);
		p[u].push_back((Opt){1, i});
		p[v].push_back((Opt){1, i});
		p[fkw].push_back((Opt){-1, i});
	}
	dfs2(1, 0);
	fo(i, 1, q)	printf("%d", ans[i] > 0);
	return 0;
}
```

---

## 作者：ETHANK (赞：1)


题意：
------------
给定一棵带点权的树，询问树上路径$(u,v)$是否包含点权为$c$的节点。

思路
------------
没有修改，**考虑离线算法**。

### 标程：

当遍历到$u$的时候，我们可以通过数组或者栈记录下路径$(1,u)$上权值为$c$的最深节点,这里记为$top[c]$。如果$top[c]$在$(u,v)$这条路径上则成立。设$L$为$LCA(u,v)$，则当$top[c]$在路径$(L,u)$上时，该询问的答案为$1$。

我们有两种方法判断上述条件，注意到$top[c]$在链$(1,u)$上的子节点$Y$不是$v$的祖先，等价于$top[c]$在路径$(L,u)$上。我们可以通过预处理前序遍历和后序遍历来完成$O(1)$查询$Y$是否是$v$的祖先。

时间复杂度：$O(N+M)$

### Tarjan:

也有一种实现更为巧妙的做法，不过总体思路不变。对于第$i$个询问$(u,v,c)$,我们发现如果$(1,u)$上和$(1,v)$上的$top[c]$不同时，$(u,v)$上一定存在点权值为$c$。如果$top[c]$相同，当且仅当$top[c]=L$时,$(u,v)$上存在权值为$c$的点。

同样的，当遍历到$u$的时候，我们选择用$top[c]$去存储$(1,u)$上权值为$c$的最深节点的子节点（相当于上种做法的$Y$）。当第一次遇到询问$i$时，$ans[i]=top[C[i]]$。第二次则$ans[i]=(ans[i]!=top[C[i]])$。（判断$(1,u)$和$(1,v)$上的$top[C[i]]$是否是同一点）。

时间复杂度：$O(N+M)$

代码
------------
#### 这里提供两种关于以上思路类似的解法，分别是**Benq**大神在官网上给出的标程和蒟蒻写的代码QWQ。

标程：[Link](http://usaco.org/current/data/sol_milkvisits_gold_dec19.html)
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
const int N=1e5+5;
int n,m,T[N],C[N],ans[N],top[N],cnt,dat[N][2];
pi range[N];
vector <int> v[N],query[N];
inline void work(int x,int fa){//预处理前序&后序遍历
    range[x].first=cnt++;
    for(int i=0;i<v[x].size();i++){
        int y=v[x][i];
        if(y==fa)continue;
        work(y,x);
    }
    range[x].second=cnt-1;
}
inline bool anc(int a,int b){//O(1)判断祖先
    return range[a].first<=range[b].first&&range[b].second<=range[a].second;
}
vector <int> order;
vector <pi> stor[N];
inline void dfs(int x,int fa){
    //按颜色存下路径[1,x]上的点
    stor[T[x]].push_back({x,(int)order.size()}),order.push_back(x);
    for(int i=0;i<query[x].size();i++){
        int t=query[x][i];
        if(!stor[C[t]].size())continue;
        pi y=stor[C[t]].back();
        if(y.first==x)ans[t]=1;//如果查询的颜色和x点相同
        else{
            int Y=order[y.second+1];//找该点在[1,x]上的儿子
            //如果它不为另一点的祖先
            if(!anc(Y,dat[t][0]+dat[t][1]-x))ans[t]=1;
        }
    }
    for(int i=0;i<v[x].size();i++){
        int y=v[x][i];
        if(y==fa)continue;
        dfs(y,x);
    }
    stor[T[x]].pop_back();order.pop_back();//弹出栈
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&T[i]);
    }
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    work(1,0);
    for(int i=1;i<=m;i++){
        scanf("%d%d%d",&dat[i][0],&dat[i][1],&C[i]);
        int x=dat[i][0],y=dat[i][1];
        query[x].push_back(i);
        query[y].push_back(i);
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        printf("%d",ans[i]);
    }
    printf("\n");
    return 0;
}
```
Tarjan做法:
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N=1e5+5;
int n,m,T[N],C[N],ans[N],top[N];
vector <int> v[N],query[N];
//记录[1,n]上每种Ci最深点的儿子
inline void dfs(int x,int fa){
    int back=top[T[x]];
    for(int i=0;i<query[x].size();i++){
        int t=query[x][i];
        if(ans[t]==-1){
            ans[t]=top[C[t]];//第一次来
        }else ans[t]=(ans[t]!=top[C[t]]);//判断两点是否相同
    }
    for(int i=0;i<v[x].size();i++){
        int y=v[x][i];
        if(y==fa)continue;
        top[T[x]]=y;//存儿子
        dfs(y,x);
    }
    top[T[x]]=back;//回溯
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%d",&T[i]);
    }
    for(int i=1;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    memset(ans,-1,sizeof(ans));
    for(int i=1;i<=m;i++){
        int x,y;
        scanf("%d%d%d",&x,&y,&C[i]);
        if(T[x]==C[i]||T[y]==C[i])ans[i]=1;
        query[x].push_back(i);
        query[y].push_back(i);
    }
    dfs(1,0);
    for(int i=1;i<=m;i++){
        printf("%d",ans[i]);
    }
    printf("\n");
    return 0;
}
```


---

## 作者：DPair (赞：1)

还是那句话，树剖的题为什么要用树剖来做呢？

在此提供一种DFS序的解法.

## 【前置知识】
- dfs序

## 【思路】
离线。

先把所有询问按要求的牛奶的品种排序，然后用dfs序和线段树来维护树上某一条路径上的 **该品种奶牛** 数量，然后 $O(logn)$ 查询，最后输出即可。

现在考虑怎么用dfs序维护。

由于是单点修改，区间求值，而dfs序难以处理路径上的问题，考虑转化成子树问题，这里考虑使用前缀和的思想。

令每一个节点的权值都表示 **这个节点到根节点的路径上的符合条件的奶牛数**。 

那么单点修改时，这个点以及这个点子树中的所有点都要发生改变，转化成了子树问题，处理一条路径上的问题时，借助 $LCA$ 然后求 $f[u]-f[LCA] + f[v]-f[LCA]$ 即可。发现修改和查询都是 $log$ 级的。

而且每一只奶牛都只会修改一次，每一个人都只会询问一次，所以复杂度也是对的。

于是我们就用dfs序完成了一道树剖的题目。

实现细节详见代码，大体思路其实也就这些。

## 【代码】
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
template <typename T>
inline void read(T &x){
    x = 0;int fu = 1;
    char c = getchar();
    while(c > 57 || c < 48){
        if(c == 45) fu = -1;
        c = getchar();
    }
    while(c <= 57 && c >= 48){
        x = (x << 3) + (x << 1) + c - 48;
        c = getchar();
    }
    x *= fu;
}
template <typename T>
inline void fprint(T x){
    if(x < 0) putchar(45), x = -x;
    if(x > 9) fprint(x / 10);
    putchar(x % 10 + 48);
}
template <typename T>
inline void fprint(T x, char ch){
    fprint(x);putchar(ch);
}

int n, m;
struct QUEST{
    int u, v;
    int c, id;
    inline bool operator < (const QUEST &tmp) const{
        return c < tmp.c;
    }
}q[100005];

bitset <100005> app, ret;//app存这一品种的询问是否出现过，ret存答案
vector <int> vec[100005];//存每一品种牛奶有哪些奶牛

int head[100005], nxt[200005], e[200005], cnt;
inline void add(int u, int v){
    nxt[++ cnt] = head[u];
    head[u] = cnt;
    e[cnt] = v;
}
//以下是LCA与DFS序预处理
int dep[100005], fa[100005][25], dfn[100005], low[100005], tot;
void build(int x, int pre){
    dfn[x] = ++ tot;
    for (register int i = head[x];i;i = nxt[i]){
        if(e[i] == pre) continue;
        dep[e[i]] = dep[x] + 1;
        fa[e[i]][0] = x;
        for (register int j = 1;j <= 20;j ++) fa[e[i]][j] = fa[fa[e[i]][j - 1]][j - 1];
        build(e[i], x);
    }
    low[x] = tot;
}

inline int LCA(int x, int y){
    if(dep[x] < dep[y]) swap(x, y);
    for (register int i = 20;i >= 0;i --){
        if(dep[fa[x][i]] >= dep[y]) x = fa[x][i];
        if(dep[x] == dep[y]) break;
    }
    if(x == y) return x;
    for (register int i = 20;i >= 0;i --){
        if(fa[x][i] ^ fa[y][i]){
            x = fa[x][i];
            y = fa[y][i];
        }
    }
    return fa[x][0];
}
//以下是线段树
#define LSON rt << 1, l, mid
#define RSON rt << 1 | 1, mid + 1, r
LL sig[400005], lazy[400005];
inline void pushup(int rt){sig[rt] = (sig[rt << 1] + sig[rt << 1 | 1]);}
inline void update(int rt, int l, int r, LL val){
    sig[rt] = sig[rt] + 1ll * (r - l + 1) * val;
    lazy[rt] += val;
}
inline void pushdown(int rt, int l, int r){
    if(lazy[rt]){
        int mid = (l + r) >> 1;
        update(LSON, lazy[rt]);
        update(RSON, lazy[rt]);
        lazy[rt] = 0;
    }
}
void modify(int rt, int l, int r, int x, int y, LL z){
    if(x <= l && r <= y) return update(rt, l, r, z);
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid) modify(LSON, x, y, z);
    if(y > mid) modify(RSON, x, y, z);
    pushup(rt);
}

LL query(int rt, int l, int r, int x){
    if(l == r && x == l) return sig[rt];
    pushdown(rt, l, r);
    int mid = (l + r) >> 1;
    if(x <= mid) return query(LSON, x);
    else return query(RSON, x);
}
int col[100005];
int main(){
    read(n);read(m);
    for (register int i = 1;i <= n;i ++){
        int x;read(x);col[i] = x;
        vec[x].push_back(i);
    }
    for (register int i = 1;i < n;i ++){
        int u, v;read(u);read(v);
        add(u, v);add(v, u);
    }
    dep[1] = 1;build(1, 0);
    for (register int i = 1;i <= m;i ++){
        read(q[i].u);read(q[i].v);read(q[i].c);
        q[i].id = i;app[q[i].c] = 1;
    }
    sort(q + 1, q + m + 1);
    int it = 1;
    for (register int i = 1;i <= n;i ++){
        if(app[i]){
            for (register int j = 0;j < (int)vec[i].size();j ++){
                modify(1, 1, n, dfn[vec[i][j]], low[vec[i][j]], 1);
            }
            while(q[it].c == i && it <= m){
                if(col[q[it].u] == i || col[q[it].v] == i){ret[q[it].id] = 1;it ++;continue;}//不知道算不算优化的优化
                int lca = LCA(q[it].u, q[it].v);
                if(col[lca] == i) {ret[q[it].id] = 1;it ++;continue;}
                LL q1 = query(1, 1, n, dfn[lca]);
                LL q2 = query(1, 1, n, dfn[q[it].u]);
                LL q3 = query(1, 1, n, dfn[q[it].v]);
                if(q2 - q1 + q3 - q1) ret[q[it].id] = 1;
                it ++;
            }
            for (register int j = 0;j < (int)vec[i].size();j ++){
                modify(1, 1, n, dfn[vec[i][j]], low[vec[i][j]], -1);
            }
        }
    }
    for (register int i = 1;i <= m;i ++) putchar(ret[i] + 48);
    putchar(10);return 0;
}
```

---

## 作者：tiger2005 (赞：1)

### 做题全过程

开了Gold之后扫了三道题，发现这道题就是我AC Silver T3的时候想到的拓展。

按Ctrl+Z找回代码之后，开始想修改方法。

我开始在黑板上乱涂乱画，想着Silver T3的思路。

到根的路径……LCA……信息只差1……

等等，信息只差1？

跑到机子前坐下，键盘声再次响起。

---

### 题意简述

给定一棵树，树上的点有N种状态。

Q次询问，每次询问两点间路径有没有一种状态的节点。

---

### 做法

建议先解决这道题：[这里](https://www.luogu.com.cn/problem/P5836)。

这是本人的题解：[这里](https://www.luogu.com.cn/blog/tiger2005/solution-p5836)。我将在这篇题解的基础上写。

在上面的题中只有两种状态，那么我们怎么拓展到N种状态呢？

我们可以确定的是，一个节点的信息和其父亲节点的信息只差一个。

那么，我们可以想到主席树来解决这个问题。

主席树储存每一个节点到根路径上每一种状态的节点个数。每一次DFS的时候，将该节点从父亲节点的信息中将该点的状态加上1就行了。

剩下的东西就和简化的题一样了。查询的时候只用查要求的状态。

复杂度：$O(NlogN+QlogN)$(前面是DFS+主席树修改，后面是询问时的LCA查询+主席树查询)。

Code:
```cpp
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int N,M,PZ[100010];
int qxx[200010][2],tt[100010],ll;
int fa[100010],dep[100010];
int bz[100010][20];
int rt[100010];
void ad(int u,int v){
	qxx[++ll][0]=v;
	qxx[ll][1]=tt[u];
	tt[u]=ll;
}
int c[4000010][2],nm[4000010],nn;
int bld(int l,int r){
	if(l==r){
		nm[++nn]=(l == PZ[1] ? 1 : 0);
		return nn;
	}
	int q=++nn;
	int m=(l+r)>>1;
	c[q][0]=bld(l,m);
	c[q][1]=bld(m+1,r);
	return q;
}
int cng(int o,int l,int r,int p){
	if(l == r){
		++nn;
		nm[nn]=nm[o]+1;
		return nn;
	}
	int q = ++nn;
	int m = (l+r)>>1;
	if(p<=m){
		c[q][0]=cng(c[o][0],l,m,p);
		c[q][1]=c[o][1];
	}
	else{
		c[q][0]=c[o][0];
		c[q][1]=cng(c[o][1],m+1,r,p);
	}
	return q;
}
int che(int o,int l,int r,int p){
	if(l == r)	return nm[o];
	int m = (l+r)>>1;
	if(p<=m)	return che(c[o][0],l,m,p);
	else	return che(c[o][1],m+1,r,p);
}
void dfs(int u){
	if(u!=1)
		rt[u]=cng(rt[fa[u]],1,N,PZ[u]);
	dep[u]=dep[fa[u]]+1;
	for(int i=tt[u];i;i=qxx[i][1]){
		int v=qxx[i][0];
		if(v==fa[u])	continue;
		fa[v]=u;
		dfs(v);
	}
}
int lca(int u,int v){
	if(dep[u]<dep[v])	swap(u,v);
	for(int i=17;i+1;i--)
		if(dep[bz[u][i]]>=dep[v])	u=bz[u][i];
	if(u==v)	return u;
	for(int i=17;i+1;i--)
		if(bz[u][i]!=bz[v][i])	u=bz[u][i],v=bz[v][i];
	return fa[u];
}
int main(){
	freopen("milkvisits.in","r",stdin);
	freopen("milkvisits.out","w",stdout);
	scanf("%d%d",&N,&M);
	rt[1]=bld(1,N);
	for(int i=1;i<=N;i++)	scanf("%d",&PZ[i]);
	for(int i=1,a,b;i<N;i++){
		scanf("%d%d",&a,&b);
		ad(a,b);ad(b,a);
	}
	fa[1]=1;dfs(1);
	for(int i=1;i<=N;i++)	bz[i][0]=fa[i];
	for(int i=1;i<18;i++)
		for(int j=1;j<=N;j++)
			bz[j][i]=bz[bz[j][i-1]][i-1];
	for(int i=1,a,b,c;i<=M;i++){
		scanf("%d%d%d",&a,&b,&c);
		int u=lca(a,b);
		int o=che(rt[a],1,N,c)+che(rt[b],1,N,c)-2*che(rt[u],1,N,c)+(PZ[u]==c);
		printf("%d",(bool)o);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
```

---

## 作者：UperFicial (赞：1)

# 粪块+熟练剖粪

**前言**

提名感谢帮我调我这坨恶心代码的[@阿丑神仙](https://www.luogu.com.cn/user/364963)Orz。

感觉做这道题的只有我数据结构学傻了。

题目链接：[$\texttt{Link}$](https://www.luogu.com.cn/problem/P5838)。

**题意简述**

给定 $n$ 个点带点权的树，$m$ 次询问，每次询问一条路径 $u$ 到 $v$ 上有没有点权等于 $c$ 的点。

**题目分析**

发现是树并有 $m$ 次询问，先上树剖。

然后发现询问挺难搞，用线段树的话我不搞，所以突发奇想上分块

用一个经典 trick，将每一块重构排序，这样每一块就具有了**可二分性**。

那么我们对于零散块儿暴力，询问的两个端点在同一个块内时还是打暴力，而对于完整块，我们考虑**二分**得到第一个大于等于 $c$ 的位置，然后判断一下这个位置是否等于 $c$ 即可。

讲一下我犯的错误，这也是 @阿丑 神仙帮我找出来的，也一块儿将容易犯的错儿说一下吧。在查询零散块时候要询问没有拍过序的数组，当然完整块二分出的位置需要判断重构排序后的数组是否合法，**因为排完序后真实的位置并不在重构数组相应的位置中**。

然后这道题就做完了，但也不知道咋地，跑到了最优解第四。

然后我这个菜鸡想卡最优解~~痴心妄想~~，发现不管块长是 $\sqrt{n}$ 还是其它都是最优解第四，但是实测当块长等于 $1000$ 时跑的相对会最快。

算一下复杂度：树剖为 $O(n\log n)$，分块为 $O(\sqrt{n}\log \sqrt{n})$，然后复杂度就是 $O(n\sqrt n\log(n+\sqrt n))$。吊打 $O(n\log^2 n)$。

$\texttt{AC}$ 链接：[$\texttt{Link}$](https://www.luogu.com.cn/record/55574640)

[$\texttt{code}$](https://paste.ubuntu.com/p/96FmFQptt4/)

$$\texttt{The End.by UF}$$



---

## 作者：摸鱼酱 (赞：0)

大致题意：给定一棵 $n$ 个点的树，每个结点有一个颜色，询问 $q$ 次 $u,v$ 路径上是否有颜色为 $c$ 的结点。

$1\leq n,q\leq 10^5$。

我算法学傻了，这题可以通过类似 Tarjan 求 LCA 的思想，把询问挂在 $u,v$ 上再 dfs 一遍即可，时间复杂度 $\mathcal O(n)$，在线。

其他题解已经有详细的介绍了，这里再讲两种其它解决方法，可能会略微复杂，但是可以 ~~锻炼一下码力~~ 拓展一下思维。

首先是主席树，点 $u$ 上的对应的树就是根到 $u$ 路径上颜色对应的桶，在 dfs 的时候从父亲的版本继承过来，只会修改一个点的信息，可以很方便地使用主席树来维护。

对于每个询问，就求出两个点的 LCA，把询问拆成两段来查询即可，时间复杂度 $\mathcal O(n\log n)$，在线。

然后是树上莫队，模拟赛遇到这题时我由于不是很会正经的树上莫队，但是大概知道是在欧拉序上跑普通莫队，欧拉序就是在 dfs 访问时加入序列，dfs 退出时再加入一次序列，分别把两次加入时的下标记为 $in_u,out_u$。显然对于 $u$ 是 $v$ 的祖先，有 $[out_u,in_v]$ 中只出现了一次的点就是 $u$ 到 $v$ 路径上的点，于是 yy 了一个拆询问来做的方法，也在无 O2 的情况下最慢点 0.8s 通过了，耗时大概是主席树做法的两倍，时间复杂度 $\mathcal O(n\sqrt n)$，常数较大，离线。

当然这都不是最优解法，但不失为赛场上无脑过题的思路，祝大家在各种比赛中都能有自己的办法通过一道道题目。

---

## 作者：Purple_wzy (赞：0)

推荐一下我的[博客](https://www.cnblogs.com/Purple-wzy/)，这里有12月月赛的全部12篇题解~~

####B Milk Visits

[题目](https://www.luogu.com.cn/problem/P5838)

题解：

提供一种更加平民化的做法---离线。

我们将每个点的点权当做修改，和查询中每个人的喜好牛奶一起排序，按点权排序。

这样，我们就只需要在一棵线段树上进行修改、查询操作了。每次先打个

lazytag清空

之前的信息，然后将一个点权的所有点插入线段树，然后查询。

具体实现还是看代码。

复杂度：O(nlog^2n)

代码：
```
#include<bits/stdc++.h>
using namespace std;
#define re register int
#define F(x,y,z) for(re x=y;x<=z;x++)
#define FOR(x,y,z) for(re x=y;x>=z;x--)
#define I inline void
#define IN inline int
typedef long long ll;
I read(int &res){
    re g=1;register char ch=getchar();res=0;
    while(!isdigit(ch)){
        if(ch=='-')g=-1;
        ch=getchar();
    }
    while(isdigit(ch)){
        res=(res<<3)+(res<<1)+(ch^48);
        ch=getchar();
    }
    res*=g;
}
char c[101000];
struct E{
	int to,nt;
}e[202000];
struct Q{
	int x,y,p,id;
	friend bool operator < (Q a,Q b){
		return a.p==b.p?a.id<b.id:a.p<b.p;
	}
}q[202000];
#define T e[k].to
char sit;
int n,m,now,ans[101000],a[100100],tr[404000],laz[404000],head[101000],fa[101000],X,Y,tot=-1,siz[101000],top[101000],son[101000],id[101000],dep[101000];
I D_1(int x,int fat,int depth){
	siz[x]=1;dep[x]=depth;son[x]=-1;fa[x]=fat;
	re maxi=-1;
	for(re k=head[x];k!=-1;k=e[k].nt){
		if(T==fat)continue;
		D_1(T,x,depth+1);
		siz[x]+=siz[T];
		if(maxi<siz[T])maxi=siz[T],son[x]=T;
	}
}
I D_2(int x,int fat,int topi){
	top[x]=topi;id[x]=++tot;
	q[tot].x=x;q[tot].y=id[x];q[tot].p=a[x];q[tot].id=-1;
	//将每个点看做修改，id为负是为了使其排序时排在查询前面 
	if(son[x]!=-1)D_2(son[x],x,topi);
	for(re k=head[x];k!=-1;k=e[k].nt){
		if(T==fat||T==son[x])continue;
		D_2(T,x,T);
	}
}
#define all 1,1,n
#define lt k<<1,l,mid
#define rt k<<1|1,mid+1,r
I modi(int k,int l,int r,int x){
	if(l==r){
		tr[k]=1;
		return;
	}
	if(laz[k])tr[k<<1]=tr[k<<1|1]=laz[k]=0,laz[k<<1]=laz[k<<1|1]=1;
	re mid=(l+r)>>1;
	if(x<=mid)modi(lt,x);
	else modi(rt,x);
	tr[k]=tr[k<<1]|tr[k<<1|1];
}
IN ques_sum(int k,int l,int r,int x,int y){
	if(x>r||y<l)return 0;
	if(x<=l&&r<=y)return tr[k];
	if(laz[k])tr[k<<1]=tr[k<<1|1]=laz[k]=0,laz[k<<1]=laz[k<<1|1]=1;
	re mid=(l+r)>>1;
	return ques_sum(lt,x,y)|ques_sum(rt,x,y);
}
IN ques(int x,int y){
	re res=0;
	while(top[x]!=top[y]){
		if(dep[top[x]]<dep[top[y]])swap(x,y);
		res|=ques_sum(all,id[top[x]],id[x]);
		if(res)return 1;
		x=fa[top[x]];
	}
	if(dep[x]>dep[y])swap(x,y);
	res|=ques_sum(all,id[x],id[y]);
	if(res)return 1;
	return 0;
}
int main(){
	freopen("milkvisits.in","r",stdin);
	freopen("milkvisits.out","w",stdout);
	read(n);read(m);
	F(i,1,n){
		read(a[i]);
	}
	memset(head,-1,sizeof(head));
	tot=-1;
	F(i,1,n-1){
		read(X);read(Y);
		e[++tot].to=Y;
		e[tot].nt=head[X];
		head[X]=tot;
		e[++tot].to=X;
		e[tot].nt=head[Y];
		head[Y]=tot;
	}
	D_1(1,0,1);
	tot=0;
	D_2(1,0,1);
	F(i,1,m){
		tot++;
		read(q[tot].x);read(q[tot].y);read(q[tot].p);q[tot].id=i;
	}
	sort(q+1,q+1+tot);
	now=q[1].p;
	F(i,1,tot){
		if(q[i].p>now)laz[1]=1,tr[1]=0,now=q[i].p;//点权变化时，清空线段树，打懒标记是一个不错的处理方式 
		if(q[i].id<0)modi(all,q[i].y);
		else ans[q[i].id]=ques(q[i].x,q[i].y);
	}
	F(i,1,m){
		cout<<ans[i];
	}
    return 0;
}
```

---

