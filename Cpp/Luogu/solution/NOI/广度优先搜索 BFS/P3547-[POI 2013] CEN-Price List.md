# [POI 2013] CEN-Price List

## 题目描述

铁路一直是 Byteotia 最受欢迎的交通方式。

在这个国家的 $n$ 个城镇中，有 $m$ 对城镇由 Byteotian State Railways (BSR) 的轨道段连接。

这些轨道不会在城镇外交叉，可能会经过风景如画的桥梁和不太风景如画的隧道。

直接通过铁路连接的任意两个城镇之间的票价为 $a$ 比特勒。

目前，Byteotia 的交通市场正在发生变化。

截至目前，BSR 面临着一个新的竞争对手：Byteotian Airlines (BA)。

BA 计划在一些城镇对之间运营航班。

由于 Byteotian 铁路相当舒适，BA 董事会决定只在那些没有直接铁路连接的城镇对之间运营航班。出于经济原因，BA 只会在那些需要恰好一次换乘的城镇之间飞行。

每张此类航班的票价为 $b$ 比特勒。

为了帮助 Byteotia 的市民规划他们的旅行，Byteotian 交通部 (BMT) 决定发行传单，说明所有可能城镇之间的最便宜路线。任意数量的直接铁路或飞机连接的序列被称为路线。名叫 Byteasar 的 BMT 官员被委派准备传单的价格表。

你能帮他写一个程序来确定正确的价格吗？

让我们明确一下，Byteotia 的所有连接，无论是铁路还是飞机，都是双向的。

## 说明/提示

------------

2024/2/4 添加了一部分来自 bzoj 的数据。

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
5 5 1 3 2
1 2
2 3
3 4
4 5
3 1
```

### 输出

```
0
3
3
2
5
```

# 题解

## 作者：i207M (赞：20)

答案有3种可能的来源，分别是

$$da;\lfloor \frac{d}{2}\rfloor b+[d\bmod 2]a;kb$$

注意到前两种都是可以一遍BFS得到的，我们来关注后一项：因为b很小，所以我们为了不走a，不惜多经过几条边。换句话说，我们要求一个“最短偶数路”长度

我们先考虑一个暴力：既然长度是偶数，我们每次走两步不就行了。先枚举u的出边v，再枚举v的出边w，如果u和w没有边，那么w就能被u更新到。

这样的复杂度显然是$O(m^2)$的，如何优化？

像这种枚举两层出边，可以联想到复杂度为$O(m\sqrt{m})$的三元环计数。观察，如果u更新了w，那么$(v,w)$这条边已经发挥了它**作为第二条边**的作用，我们直接将它删除即可。这可以用双向链表实现。

**注意我们要开两个边表！第一层遍历的是原边表，第二层遍历的是可删的边表！**

至于时间复杂度的证明的话，简单的想法就是一个三元环会被遍历三边，所以复杂度为$O(m\sqrt{m})$，而其他边遍历一次后就被删除了；POI官方给出了一个新颖的复杂度证明，有兴趣的同学可以看一下：

![捕获.png](https://i.loli.net/2019/06/16/5d06474a17d1579712.png)



```cpp
#define N 100005
struct Graph
{
    int head[N],cnte,pr[N*2],nx[N*2],v[N*2];
    il void adde(int uu,int vv)
    {
        v[++cnte]=vv,nx[cnte]=head[uu],pr[head[uu]]=cnte,head[uu]=cnte;
        v[++cnte]=uu,nx[cnte]=head[vv],pr[head[vv]]=cnte,head[vv]=cnte;
    }
    il void del(int x,int i)
    {
        nx[pr[i]]=nx[i],pr[nx[i]]=pr[i];
        if(head[x]==i) head[x]=nx[i];
    }
} G,H;
int n,m,S,a,b;
int d[N];
int q[N],hd,tl;
int ans[N];
bool vis[N];
signed main()
{
#ifdef M207
    freopen("in.in","r",stdin);
    // freopen("ot.out","w",stdout);
#endif
    in(n,m,S,a,b);
    for(ri i=1,uu,vv; i<=m; ++i)
    {
        in(uu,vv);
        G.adde(uu,vv),H.adde(uu,vv);
    }
    d[q[hd=tl=1]=S]=1;
    while(hd<=tl)
    {
        int x=q[hd++];
        for(ri i=G.head[x]; i; i=G.nx[i])
            if(!d[G.v[i]]) d[q[++tl]=G.v[i]]=d[x]+1;
    }
    for(ri i=1; i<=n; ++i)
    {
        if(d[i])
        {
            --d[i];
            ans[i]=min(a*d[i],b*(d[i]>>1)+a*(d[i]&1));
            d[i]=0;
        }
        else ans[i]=1e9;
    }
    d[q[hd=tl=1]=S]=1;
    while(hd<=tl)
    {
        int x=q[hd++];
        for(ri i=G.head[x]; i; i=G.nx[i]) vis[G.v[i]]=1;
        for(ri i=G.head[x]; i; i=G.nx[i])
        {
            int V=G.v[i];
            for(ri j=H.head[V]; j; j=H.nx[j])
            {
                if(d[H.v[j]]||vis[H.v[j]]) continue;
                d[q[++tl]=H.v[j]]=d[x]+1;
                H.del(V,j);
            }
        }
        for(ri i=G.head[x]; i; i=G.nx[i]) vis[G.v[i]]=0;
    }
    for(ri i=1; i<=n; ++i)
    {
        if(d[i]) ckmin(ans[i],b*(d[i]-1));
        out(ans[i]);
    }
    return 0;
}
```

---

## 作者：juju527 (赞：9)

### $\texttt{Solution}$
考虑最短路的形式

显然只有3种情况：

全a，全b（末尾有1个a），全b（通过多走几条边使得完全去除a边）

第一种对应 $2a\leq b$，二三种为 $b<2a$，根据 $b$ 究竟有多小决定是情况二还是情况三

前两种情况我们容易处理，跑一边bfs即可（0/1最短路）

最后一种情况我们考虑类似0/1最短路的转移

记 $dis_x$ 为 $k\to x$ 的距离

当用点 $u$ 更新最短路是

枚举 $u$ 一条边能到达的点 $v$，再枚举 $v$ 一条边能到达的点 $w$，满足 $u,w$ 间没有边,用 $u$ 转移 $w$ 即可

这个做法的复杂度为 $O(\sum_{v}d_v^2)=O(m^2)$

我们考虑我们第二次枚举的边 $(v,w)$ 决定了我们要更新 $w$

事实上该条边作为第二条枚举的边有效更新只有这一次，实现时我们可以在边集中删去它

原因是考虑之后的点 $x$，一定有 $dis_x\geq dis_u$，所以之后边 $(v,w)$ 的更新都是无效的

考虑只有3元环被遍历时不会删去边，每个三元环只会被遍历 $O(1)$ 遍，三元环的个数为 $O(m\sqrt m)$

故复杂度为 $O(m\sqrt m)$

[代码](https://www.luogu.com.cn/paste/txuyrofq)

---

## 作者：ywy_c_asm (赞：6)

这个垃圾做法的上界大概是时间$O(m\sqrt m\log n\log m)$，空间$O(m\sqrt m\log m)$的，然而数据比较水所以跑不满……

首先我们有一个比较显然的暴力，在中心点处二重枚举出边，然后如果这两个点之间没有连的边就连一条$b$边。

显然我们需要用度数根号分治来优化这个暴力，如果度数$<=\sqrt m$那么直接暴力，否则的话，我们需要考虑在大度数点处维护一些东西。

一个直观的想法是连有向边，在大度数点处建一个虚点，我们让大度数点周围的一圈点向虚点连$b$边，让虚点向周围一圈点连0边，这样就相当于周围一圈点之间互相连边。

但是这样做显然不对，并不能保证两个有直接的$a$边相连的点之间没有$b$边。

我们发现，如果两个点之间不能连边显然就是它们在一个三元环里，那么，我们可以先找出所有三元环，然后对于一个大度数点我们找出它所在的所有3元环，就得到一堆形如“$x$和$y$不能连边”的关系，然后我们对于大度数点建线段树，然后对于一个$x$我们知道它不能和哪些$y$连边，那么就相当于它能连的部分被分割成了若干个区间，线段树优化建图即可。

上代码~

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_set>
#define blo 600
#define ll long long
using namespace std;
namespace ywy {
	inline int get() {
	    int n = 0;
	    char c;
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            break;
	        if (c == '-')
	            goto s;
	    }
	    n = c - '0';
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 + c - '0';
	        else
	            return (n);
	    }
	s:
	    while ((c = getchar()) || 23333) {
	        if (c >= '0' && c <= '9')
	            n = n * 10 - c + '0';
	        else
	            return (n);
	    }
	}
	vector<int> vec[100001], ds[100001], dt[100001], other[100001];
	int dfn[100001];
	typedef struct _b {
	    int dest;
	    int nxt;
	    unsigned char len;
	} bian;
	bian memchi[13000001];
	int gn = 1, heads[1000001], lef[1000001], rgh[1000001], gseg;  //警告！！！！！
	inline void add(int s, int t, int l) {
	    memchi[gn].dest = t;
	    memchi[gn].nxt = heads[s];
	    memchi[gn].len = l;
	    heads[s] = gn;
	    gn++;
	}
	int build(int l, int r, int pt) {
	    if (l == r)
	        return (vec[pt][l]);
	    int tree = gseg;
	    gseg++;
	    int mid = (l + r) >> 1;
	    lef[tree] = build(l, mid, pt);
	    rgh[tree] = build(mid + 1, r, pt);
	    add(tree, lef[tree], 0);
	    add(tree, rgh[tree], 0);
	    return (tree);
	}
	int n, a, b;
	void lb(int rl, int rr, int l, int r, int tree, int pt) {
	    if (rl > rr)
	        return;
	    if (rl == l && rr == r) {
	        add(pt, tree, 2);
	        return;
	    }
	    int mid = (l + r) >> 1;
	    if (rl > mid)
	        lb(rl, rr, mid + 1, r, rgh[tree], pt);
	    else {
	        if (rr <= mid)
	            lb(rl, rr, l, mid, lef[tree], pt);
	        else {
	            lb(rl, mid, l, mid, lef[tree], pt);
	            lb(mid + 1, rr, mid + 1, r, rgh[tree], pt);
	        }
	    }
	}
	typedef struct _n {
	    int pt;
	    int dis;
	    _n(int a, int b) {
	        pt = a;
	        dis = b;
	    }
	    friend bool operator<(const _n &a, const _n &b) { return (a.dis > b.dis); }
	} node;
	priority_queue<node> que;
	typedef struct _p {
	    int a;
	    int b;
	    _p(int i, int j) {
	        if (i > j)
	            swap(i, j);
	        a = i;
	        b = j;
	    }
	    friend bool operator==(const _p &a, const _p &b) { return (a.a == b.a && a.b == b.b); }
	} pair;
	typedef struct _alloc {
	    size_t operator()(const pair &a) const { return (((ll)a.a << 32) | a.b); }
	} alloc;
	unordered_set<pair, alloc> st;
	vector<int> dag[100001];
	inline void clear(vector<int> &v) {
	    vector<int> tmp;
	    v = tmp;
	}
	unsigned char bv[1000001];
	int dis[1000001];
	int tab[5];
	void ywymain() {
	    n = get();
	    int m = get(), k = get();
	    a = get();
	    b = get();
	    for (register int i = 1; i <= m; i++) {
	        int s = get(), t = get();
	        add(s, t, 1);
	        add(t, s, 1);
	        vec[s].push_back(t);
	        vec[t].push_back(s);
	        st.insert(_p(s, t));
	    }
	    for (register int i = 1; i <= n; i++) {
	        for (register int j = 0; j < vec[i].size(); j++) {
	            int dst = vec[i][j];
	            if (vec[dst].size() > vec[i].size() || (vec[i].size() == vec[dst].size() && dst > i)) {
	                dag[i].push_back(dst);
	            }
	        }
	    }
	    tab[1] = a;
	    tab[2] = b;
	    gseg = n + 1;
	    for (register int i = 1; i <= n; i++) {
	        for (register int j = 0; j < dag[i].size(); j++) {
	            for (register int k = 0; k < j; k++) {
	                int x = dag[i][j], y = dag[i][k];
	                if (st.count(_p(x, y))) {
	                    if (vec[i].size() >= blo)
	                        ds[i].push_back(x), dt[i].push_back(y);
	                    if (vec[x].size() >= blo)
	                        ds[x].push_back(i), dt[x].push_back(y);
	                    if (vec[y].size() >= blo)
	                        ds[y].push_back(i), dt[y].push_back(x);
	                }
	            }
	        }
	    }
	    for (register int i = 1; i <= n; i++) {
	        if (vec[i].size() < blo) {
	            for (register int j = 0; j < vec[i].size(); j++) {
	                for (register int k = 0; k < j; k++) {
	                    if (!st.count(_p(vec[i][j], vec[i][k])))
	                        add(vec[i][j], vec[i][k], 2), add(vec[i][k], vec[i][j], 2);
	                }
	            }
	        } else {
	            for (register int j = 0; j < vec[i].size(); j++) dfn[vec[i][j]] = j, clear(other[vec[i][j]]);
	            int rt = build(0, vec[i].size() - 1, i);
	            for (register int j = 0; j < ds[i].size(); j++) {
	                other[ds[i][j]].push_back(dfn[dt[i][j]]);
	                other[dt[i][j]].push_back(dfn[ds[i][j]]);
	            }
	            for (register int j = 0; j < vec[i].size(); j++) {
	                int me = vec[i][j];
	                sort(other[me].begin(), other[me].end());
	                int lst = -1;
	                for (register int k = 0; k < other[me].size(); k++) {
	                    lb(lst + 1, other[me][k] - 1, 0, vec[i].size() - 1, rt, me);
	                    lst = other[me][k];
	                }
	                lb(lst + 1, vec[i].size() - 1, 0, vec[i].size() - 1, rt, me);
	            }
	        }
	    }
	    memset(dis, 0x7f, sizeof(dis));
	    dis[k] = 0;
	    que.push(_n(k, 0));
	    while (!que.empty()) {
	        node cjr = que.top();
	        que.pop();
	        if (bv[cjr.pt])
	            continue;
	        bv[cjr.pt] = 1;
	        dis[cjr.pt] = cjr.dis;
	        for (register int i = heads[cjr.pt]; i; i = memchi[i].nxt) {
	            if (bv[memchi[i].dest])
	                continue;
	            if (cjr.dis + tab[memchi[i].len] < dis[memchi[i].dest]) {
	                que.push(_n(memchi[i].dest, dis[memchi[i].dest] = cjr.dis + tab[memchi[i].len]));
	            }
	        }
	    }
	    for (register int i = 1; i <= n; i++) cout << dis[i] << endl;
	}
}
int main() {
    ywy::ywymain();
    return (0);
}
```

---

## 作者：7KByte (赞：5)

我们都知道对于 dijkstra 算法，每条边只会被遍历一次。因为对于每个点 $x$，遍历到它时它的 dis 一定是最小的且不会再被更新了。

这同样适用与类似的 bfs 算法。

对于本题。原图上的最短路可以直接求出来，然后可以选择将路径上相邻两条边合成一条边（一定能合，否则最短路会更短）。当然最后可能会剩下一条长度为 $1$ 的 $a$ 边。

如果 $a$ 远大于 $b$，那么我们就有可能额外绕一大圈用多个 $b$ 消去 $a$，此时路径一定全部为 $b$。

考虑 BFS，当前出队的节点为 $x$，标记 $x$ 所有的相邻点，枚举一条边 $x\to y$，再枚举另一条边 $y\to z$，如果 $z$ 上面没有标记，显然可以更新 $d_x + 1\to d_z$。

但是直接枚举是 $\mathcal{O}(M^2)$ 的，但是根据 BFS 的性质，如果我们松弛了 $d_x+1\to d_z$，那么 $y\to z$ 一定不会再被使用，直接删掉即可。

由于松弛一次就删一条边，这部分复杂度是 $\mathcal{O}(M)$ 的，但是考虑到存在 $z$ 已经被标记的情况。这种情况一定是 $x,y,z$ 存在三元组，而三元组的数量是 $\mathcal{O}(M\sqrt M)$ 级别的，所以总复杂度是 $\mathcal{O}(N + M\sqrt{M})$。

```cpp
#define N 100005
int n, m, s, a, b, ans = inf, d[N], h[N], tot, u[N], f[N], nt[N << 1], ls[N << 1], v[N];
struct edge{int to, nxt;}e[N << 1];
void add(int x,int y){e[++tot].nxt = h[x], h[x] = tot, e[tot].to = y;}
queue<int>q;
void bfs(){
	d[s] = 1, q.push(s);
	while(!q.empty()){
		int x = q.front(); q.pop();
		for(int i = h[x]; i; i = e[i].nxt)if(!d[e[i].to])
			d[e[i].to] = d[x] + 1, q.push(e[i].to);
	}
	rp(i, n)d[i]--, u[i] = min(a * d[i], b * (d[i] >> 1) + a * (d[i] & 1));
}
void calc(){
	rp(x, n){
		for(int i = h[x]; i; i = e[i].nxt)
			ls[f[x]] = i, nt[i] = f[x], ls[i] = 0, f[x] = i;
	}
	memset(d, 0, sizeof(d));
	d[s] = 1, q.push(s);
	while(!q.empty()){
		int x = q.front(); q.pop();
		for(int i = h[x]; i; i = e[i].nxt)v[e[i].to] = 1;
		for(int i = h[x]; i; i = e[i].nxt){
			int y = e[i].to;
			for(int j = f[y]; j; j = nt[j])if(!v[e[j].to]){
				if(ls[j])nt[ls[j]] = nt[j], ls[nt[j]] = ls[j];
				else ls[nt[j]] = 0, f[y] = nt[j];
				if(!d[e[j].to])d[e[j].to] = d[x] + 1, q.push(e[j].to);
			}
		}
		for(int i = h[x]; i; i = e[i].nxt)v[e[i].to] = 0;
	}
	rp(i, n)if(d[i])d[i]--, u[i] = min(u[i], b * d[i]);
}
int main() {
	read(n, m, s, a, b);
	rp(i, m){
		int x, y; read(x, y);
		add(x, y), add(y, x);
	}
	bfs(), calc();
	rp(i, n)printf("%d\n", u[i]);
	return 0;
}
```

---

## 作者：QueenSi (赞：4)

[传送门](https://www.luogu.com.cn/problem/P3547)

题面讲解十分清晰，这里不再赘述。

首先给出一个结论： 在这张图中的最短路一定要么是原路径上的最小值（也就是全是 $a$ ）， 要么就是除了开始或者末尾是 $a$ 其他的地方都是 $b$ ， 要么就是全部都是 $b$ 。

这一点是非常好想的，考虑如果 $2 \times a \le b$ 则最短路就是原路径上的值，如果考虑 $2 \times a > b$ ，那么你可以想方设法把 $2 \times a$ 的代价用 $b$ 跳过， 那么最短的路径也就是最小的距离 $dis_u$ , 如果他是奇数，就加上最后一条边的 $a$ , 其他的每两条路径都用 $b$ 跳过 $2 \times a$ 的代价。

这两种情况可以直接用 $bfs$ 找到最小的 $dis_u$ 然后直接计算，大概就是下面这个样子。

```cpp
For(i,1,n) ans[i]=min(dis[i]*a,(dis[i]&1)*a+(dis[i]/2)*b);
```


另外一种情况是可能只跳 $b$ , 这个时候就相当于每次都要跳两条边的最短路，很明显有一个暴力就是考虑 $u$ 当前连上的点集是 $V$ , 考虑对于 $\forall v \in V$ , 找出其连接的点集 $nxt$ = { $ x | x \notin V,x\ne u$ } , 然后考虑用 $u$ 去更新 $nxt$ 点集里的点 ， 这样做明显是 $O(m^2)$ 的。

我们发现对于 $u$ 更新的点 $nxt$ , 那么 $ v \to nxt$ 的这条边已经被 $u$ 更新过了，不会被其他的点更新，可以在链表中删除这一条边，这样就会使得复杂度大大降低。

具体实现用 $list$ , 代码见下：

```cpp
// powered by shenxinge
#include<bits/stdc++.h>
#define Debug if(false)
#define pb push_back
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Rep(i,a,b) for(int i=a;i>=b;i--)
using namespace std;
const int maxn=100500;
inline int read()
{
	int x=0,f=1;char c;
	for(;!isdigit(c);c=getchar()) if(c=='-') f=-f;
	for(;isdigit(c);c=getchar()) x=(x<<1)+(x<<3)+(c^48);
	return x*f;
}
int n,m,k,a,b;
// rec为删去一条边的结果
int ans[maxn],dis[maxn];
bool vis[maxn];
list<int> vec[maxn],rec[maxn];
signed main()
{
	n=read(),m=read(),k=read(),a=read(),b=read();
	For(i,1,m)
	{
		int u=read(),v=read();
		vec[u].pb(v),vec[v].pb(u);
		rec[u].pb(v),rec[v].pb(u);
	}
	queue<int> que;
	memset(dis,-1,sizeof dis);
	que.push(k),dis[k]=0;
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(int v:vec[u]) if(!~dis[v])
			dis[v]=dis[u]+1,que.push(v);
	}
	For(i,1,n)
		ans[i]=min(dis[i]*a,(dis[i]&1)*a+(dis[i]/2)*b);
	memset(dis,-1,sizeof dis);
	que.push(k),dis[k]=0;
	while(!que.empty())
	{
		int u=que.front();que.pop();
		for(int v:vec[u])
			vis[v]=true;
		for(int v:vec[u])
		{
			auto it=rec[v].begin();
			while(it!=rec[v].end())
			{
				int nxt=(*it);
				if(~dis[nxt]||vis[nxt]) it++;
				else dis[nxt]=dis[u]+1,
					 que.push(nxt),
					 it=rec[v].erase(it);
			}
		}
		for(int v:vec[u])
			vis[v]=false;
	}
	For(i,1,n) if(~dis[i])
		ans[i]=min(ans[i],dis[i]*b);
	For(i,1,n)
		printf("%d\n",ans[i]);
	return 0;
}
```


---

## 作者：Cx114514 (赞：3)

### 题目链接：[[POI2013] CEN-Price List](https://www.luogu.com.cn/problem/P3547)

考虑答案的可能情况：

1. 边权均为 $a$。
2. 边权均为 $b$。
3. 最后一条边边权为 $a$，其余边权为 $b$。

前面两种情况很好求。

令原图中路径长度为 $1$。

则答案分别为 $len\times a$ 和 $\frac{len}{2}\times b$。

但如果 $len$ 为奇数，此时如果均改为 $b$ 最后会剩下一条边，这时就是第三种情况。

正常的 BFS 是每次向外拓展一条边，但这里要求偶数条边，因此我们可以每次向外拓展两条边。

每次选中一个点 $u$，枚举和它连接的 $v$，再连接和它连接的 $w$。

如果 $u,w$ 间没有边相连，则可以直接遍历到 $w$。

因为这是 BFS，所以第一次遍历到一个点时一定是最短路。那么当一条边被当作第二条边遍历了，那么以后就不用考虑它了，直接删除即可。这样每次遍历到就删掉了，每条边只会当一次第二条边。删除可以用 STL list 维护。只有三元环中的两条边不会被删，有 $O\left(m\sqrt m\right)$ 条三元环，因此时间复杂度为 $O\left(m\sqrt m\right)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;

int n, m, S, A, B, vis[100005], dis[100005], ans[100005], isedge[100005];

struct node
{
	int u, v, w;
} edge[100005];

vector < int > G1[100005];

list < int > G2[100005];

queue < int > q;

int main()
{
	cin >> n >> m >> S >> A >> B;
	for (int i = 1; i <= m; i++)
	{
		int u, v;
		cin >> u >> v;
		G1[u].push_back(v);
		G2[u].push_back(v);
		G1[v].push_back(u);
		G2[v].push_back(u);
	}
	q.push(S);
	vis[S] = 1;
	dis[S] = 0;
	while (!q.empty())
	{
		int t = q.front();
		q.pop();
		for (int i = 0; i < G1[t].size(); i++)
		{
			int v = G1[t][i];
			if (!vis[v])
			{
				dis[v] = dis[t] + 1;
				vis[v] = 1;
				q.push(v);
			}
		}
	}
	for (int i = 1; i <= n; i++)
		ans[i] = min(dis[i] * A, (dis[i] / 2) * B + (dis[i] % 2) * A);
	for (int i = 1; i <= n; i++)
		vis[i] = 0;
	for (int i = 1; i <= n; i++)
		dis[i] = -1;
	q.push(S);
	vis[S] = 1;
	dis[S] = 0;
	while (!q.empty())
	{
		int t = q.front();
		q.pop();
		for (int i = 0; i < G1[t].size(); i++)
		{
			int v = G1[t][i];
			isedge[v] = 1;
		}
		for (int i = 0; i < G1[t].size(); i++)
		{
			int v = G1[t][i];
			auto it = G2[v].begin();
			while (it != G2[v].end())
			{
				if (isedge[*it]) it++;
				else
				{
					if (!vis[*it])
					{
						vis[*it] = 1;
						dis[*it] = dis[t] + 1;
						q.push(*it);
					}		
					it = G2[v].erase(it);
				} 
			}
		}
		for (int i = 0; i < G1[t].size(); i++)
		{
			int v = G1[t][i];
			isedge[v] = 0;
		}
	}
	for (int i = 1; i <= n; i++)
		if (dis[i] != -1) ans[i] = min(ans[i], dis[i] * B);
	for (int i = 1; i <= n; i++)	
		cout << ans[i] << endl;
	return 0;
}
```

---

## 作者：DYYqwq (赞：2)

神仙题。

考虑答案的来源。

- 只走 $a$ 边。
- 只走 $b$ 边。
- 走 $\left \lfloor \frac{k}{2} \right \rfloor$ 条 $a$ 边，走 $k \operatorname{mod} 2$ 条 $b$ 边。

显然除了第二种情况，都是可以随便算的。

针对这种情况，我们先设计一个暴力。我们每次找一个 $i \rightarrow j \rightarrow k$，且使得  $i$ 不能直接到达 $k$，于是发现要想 $i \rightarrow k$，就可以走一条  $b$ 边。

发现这东西很垃圾，就是个 $O(M^2)$。

考虑 bfs 的核心——松弛操作。一根 $u \rightarrow v \rightarrow w$ 松弛以后，$v \rightarrow w$ 必然不会再产生贡献，于是删掉即可。

使用 vector 存储可以没啥细节的删掉。

分析复杂度：设 $u$ 为转移的中间点，$ru_u$ 表示一个点的度。考虑总体时间复杂度是 $\sum_{u \in S} \min(ru_u^2,M)$，然后化一下发现这东西 $\leq \sum_{u \in S} \sqrt{ru_u^2 \times M}=\sum_{u \in S} ru_u \times \sqrt{m}=O(m\sqrt{m})$。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct node
{
	int to , nxt;
}e[200010];
int n , m , k , a , b , head[100010] , tot , dis[100010] , dis2[100010];
bool vis[100010];
vector<int> t[200010];
queue<int> q;
void add(int u , int v)
{
	++ tot;
	e[tot].to = v;
	e[tot].nxt = head[u];
	head[u] = tot;
}
void bfs1(int s)
{
	memset(dis , 0x3f , sizeof(dis));
	q.push(s);
	dis[s] = 0;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = head[u] ; i != 0 ; i = e[i].nxt)
		{
			int v = e[i].to;
			if(dis[v] > dis[u] + 1) dis[v] = dis[u] + 1 , q.push(v);
		}
	}
}
void bfs2(int s)
{
	memset(dis2 , 0x3f , sizeof(dis2));
	q.push(s);
	dis2[s] = 0;
	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		for(int i = head[u] ; i != 0 ; i = e[i].nxt) vis[e[i].to] = 1;
		for(int i = head[u] ; i != 0 ; i = e[i].nxt)
		{
			int v = e[i].to;
			for(int qwq = 0 ; qwq < t[v].size() ; qwq ++)
			{
				int j = t[v][qwq];
				if(vis[j]) continue;
				if(dis2[j] > dis2[u] + b)
				{
					dis2[j] = dis2[u] + b;
					q.push(j);
					swap(t[v][qwq] , t[v][t[v].size() - 1]);
					t[v].pop_back();
					qwq --;
				}
			}
		}
		for(int i = head[u] ; i != 0 ; i = e[i].nxt) vis[e[i].to] = 0;
	}
}
int main()
{
	scanf("%d%d%d%d%d" , &n , &m , &k , &a , &b);
	for(int i = 1 , u , v ; i <= m ; i ++)
	{
		scanf("%d%d" , &u , &v);
		add(u , v) , add(v , u);
		t[u].push_back(v) , t[v].push_back(u);
	}
	bfs1(k);
//	for(int i = 1 ; i <= n ; i ++) dis[i] = min(dis[i] * a , dis[i] / 2 * b + (dis[i] & 1 ? a : 0));
	bfs2(k);
	for(int i = 1 ; i <= n ; i ++) printf("%d\n" , min(min(dis[i] * a , dis[i] / 2 * b + (dis[i] & 1 ? a : 0)) , dis2[i]));
	return 0;
}
```

---

## 作者：Anonymely (赞：2)

很不错的图论题。

考虑对 $a,2a,b$ 大小进行讨论。

1. $2a \le b$，这种情况是简单的，根本不会走 $b$ 边，直接 bfs 即可，此时答案为 $d \times a$。

2. $a \le b < 2a$，这种情况下能走两条 $a$ 边就会用 $b$ 边替换掉，同时不用担心三元环的情况（因为三元环会出现三个点最短路都是 $1$，但是从 $u \to v \to w$ 的 $2a$ 被替换成 $b$），此时答案为 $\frac{d}{2} \times b+[d\bmod2] \times b$。

3. $b < a$，此时可能出现为了多走 $b$ 而少走 $a$ 的情况，此时答案为 $\min(D \times b,\frac{d}{2} \times b+[d\bmod2] \times b)$，注意这里的 $D$ 指的是每次走两步的最短路。

由于求最小值，对上面几种情况取 $\min$ 即可。

除了 $d'$ 其他都是平凡的。

暴力考虑每次扩展两条边，复杂度为 $m^2$，注意对于三个点 $u,v,w$ 来说，若出现 $u \to v \to w$ 的扩展，则说明 $D_{w} > D_{u}$，也就不可能出现 $w \to u$ 的扩展，同理若 $u,w$ 同时能扩展到的点也不会以 $w$ 扩展，故可删除 $(v,w)$ 这条边。

再次思考下复杂度，此时的三元环会被扩展最多三边，而其他边扩展一次会被删除，总复杂度为三元环个数，复杂度为 $O(m \sqrt m)$。

---

## 作者：happybob (赞：0)

考虑最终路径是怎么样的。我们可以证明，路径要么全都是 $a$ 类边，要么至多一条 $a$ 类边。

考虑归纳证明这个事实。假设 $b < 2a$，首先可以知道路径中一定不存在连续两条 $a$，然后考虑最优路径中一条 $a$ 类边的下一条是 $b$ 类边，可以分类讨论将这条 $a$ 类边向下调整一步，所以最终必然至多只有一条 $a$ 类边。

所以问题难点在于求 $k$ 到每个点的最短的长度为偶数的路径，使得路径上不存在 $u \leftrightarrow v \leftrightarrow w$ 使得 $(u,w) \in E$。

考虑 BFS 过程每次枚举 $u$ 的邻点 $v$ 的邻点 $w$，若 $(u,w) \notin E$ 则尝试更新 $dis_w$，然后删除通过 $v$ 松弛 $w$ 的边，原因是只要 $(u,w) \notin E$，无论松弛是否成功，对于未出队的 $x$，$x,v,w$ 都不可能更新答案，这是因为 $dis_x \geq dis_u$。

使用链表模拟这个过程，考虑一对 $(u,v,w)$ 被枚举到但没有删边，当且仅当这是一个三元环。根据三元环计数结论可得复杂度 $O(m\sqrt m)$。

---

