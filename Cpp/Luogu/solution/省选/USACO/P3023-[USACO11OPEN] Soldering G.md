# [USACO11OPEN] Soldering G

## 题目描述

The cows are playing with wires! They have learned a technique called soldering, in which they connect two pieces of wire together by attaching the endpoint of one wire to a location along the length of the other. (Soldering endpoint to endpoint is not allowed.) There can be multiple solder junctions at the same point.

The cows have a plan for an Amazing Structure they would like to build. It is in the form of a graph with N (1 <= N <= 50,000) nodes and N-1 edges of unit length so that each pair of nodes is connected. Each edge is described by a pair of integers, A and B (1 <= A <= N; 1 <= B <= N; A != B).

The cows are able to buy wire from a local store; however longer wire is more expensive. In particular the cows can buy a wire of length L with cost L\*L, but they cannot cut wires or join wires together.

Given the plan, the cows would like solder wires together to build their Amazing Structure. Please help them find the minimum possible cost!

Test data worth at least 50% of the points will have N <= 2,000.

Partial feedback will be provided on your first 50 submissions to this problem.

TIME LIMIT: 2 seconds

MEMORY LIMIT: 64 MB

奶牛决定用电线焊接出一张图，这张图是连通的，由 $N$ 个点，$N-1$ 条边组成，每条边的长度都是 $1$。焊接所用的电线要从当地的商店里买。越长的电线越贵，一条长度为 $L$ 的电线售价为 $L^2$。奶牛们已经学会了基本的焊接方法，她们会把某条电线的一个端点焊接到另一条电线的中间某个位置，但她们没有学会如何把两条电线的端点直接焊接起来，也没有学会怎么把电线剪断。给定奶牛准备焊接的图，请告诉奶牛怎么焊接才能最节约材料费用。

## 说明/提示

Since all nodes in the structure are connected to node 1, we only need to buy one wire of length 2 and three of length 1, for a total cost of 2 \* 2 + 1 \* 1 + 1 \* 1 + 1 \* 1 = 7.

## 样例 #1

### 输入

```
6 
1 2 
1 3 
1 4 
1 5 
1 6 
```

### 输出

```
7 
```

# 题解

## 作者：ケロシ (赞：13)

提供一种复杂度正确的算法。

因为穿过一条边的链只有一条，所以考虑 dp 记录这条链的信息，设 $f_{u,k} ~ (k \in subtree(u))$，表示经过 $u$ 以及其父亲的链的底端是点 $k$，不计这条链的最小代价。

不难发现链穿过点 $u$ 的方式有两种，分别是一段连到父亲和不连到父亲：

![](https://cdn.luogu.com.cn/upload/image_hosting/hg7ty3a5.png)

考虑分别进行转移。

考虑在 $u$ 点断掉的链的贡献，
设儿子 $v$ 的贡献为 $g_{v}=\min (f_{v,k}+(d_u-d_k)^2)$，再考虑穿过 $u$ 的链的贡献。

如果穿过点 $u$ 的链连到父亲，其转移：

$f_{u,k}=\sum g + \min_{v\in son(u)} (f_{v,k}-g_v)$

如果穿过点 $u$ 的链不连到父亲，其转移：

$f_{u,u}=\sum g + \min_{v_1,v_2 \in son(u), v_1\ne v_2} (f_{v_1,l}+f_{v_2,r}-g_{v_1}-g_{v_2}+(2d_u-d_l-d_r)^2)$

最后如果根节点度数大于 $1$，则只有 $f_{rt,rt}$ 可以贡献答案，反之 $f_{rt,k}$ 都可以贡献。

这里时间复杂度均摊 $O(n^2)$，考虑优化。

先看 $g_{v}=\min (f_{v,k}+(d_u-d_k)^2)$，如何快速求这个东西。发现贡献是平方形式，考虑各种关于斜率的优化，先把式子拆一下：

$f_{v,k}+(d_u-d_k)^2=f_{v,k}+d_k^2-2d_ud_k+d_u^2$

$(2d_u-d_l-d_r)^2=(2d_u-d_l)^2-2d_r(2d_u-d_l)+d_r^2$

不难想到把 $d_u$ 固定掉，变为一根一次函数，斜率为 $-2d_u$，然后用数据结构查询，比如凸包，这里使用李超线段树。

考虑将所有的 $f_{u,k}$ 插进点 $u$ 的李超树，对于求 $g_u$，直接在李超树查询即可。

对于 $f_{u,k}=\sum g + \min_{v\in son(u)} (f_{v,k}-g_v)$，不难发现就是对 $f_{v,k}$ 里所有函数的截距全部加上 $\sum g - g_v$，整体打个 tag 即可，然后合并到 $f_{u,k}$ 即可。

这里使用启发式合并，将小的合并到大的李超树上去。

对于求 $f_{u,u}$，不难想到在启发式合并的时候顺便遍历小子树，去查询大子树即可。

时间复杂度 $O(n \log^2 n)$。

```cpp
const int N = 5e4 + 5;
const int M = 3e6 + 5;
const ll LNF = 1e12 + 128;
int n;
int fi[N], ne[N << 1], to[N << 1], ecnt;
int ru[N], d[N];
struct Line {
	ll k, b;
} p[N]; int cnt;
int ls[M], rs[M], F[M], tot;
vector<int> e[N]; int id[N], rt[N];
ll b[N], g[N];
ll sq(ll x) {
	return x * x;
}
ll calc(ll i, ll x) {
	return p[i].k * x + p[i].b;
}
void push(int & u, int l, int r, int x) {
	if(! u) u = ++ tot;
	int mid = l + r >> 1;
	int & y = F[u];
	if(calc(x, mid) < calc(y, mid)) swap(x, y);
	if(l == r) return;
	if(calc(x, l) < calc(y, l)) push(ls[u], l, mid, x);
	if(calc(x, r) < calc(y, r)) push(rs[u], mid + 1, r, x);
}
ll query(ll u, int l, int r, int p) {
	if(! u) return LNF;
	ll res = calc(F[u], p);
	if(l == r) {
		return res;
	}
	int mid = l + r >> 1;
	if(p <= mid) chmin(res, query(ls[u], l, mid, p));
	else chmin(res, query(rs[u], mid + 1, r, p));
	return res;
}
void add(int u, int v) {
	ne[++ecnt] = fi[u];
	to[ecnt] = v;
	fi[u] = ecnt;
}
void dfs(int u, int fa) {
	if(u != 1 && ru[u] == 1) {
		p[u] = {- 2 * d[u], sq(d[u])};
		push(rt[u], 1, n << 1, u);
		e[id[u]].push_back(u);
		return;
	}
	ll res = 0;
	for(int i = fi[u]; i; i = ne[i]) {
		int v = to[i];
		if(v == fa) continue;
		d[v] = d[u] - 1;
		dfs(v, u);
		g[v] = query(rt[v], 1, n << 1, d[u]) + sq(d[u]) + b[v];
		res += g[v];
	}
	p[u].b = LNF; p[u].k = - 2 * d[u];
	for(int i = fi[u]; i; i = ne[i]) {
		int v = to[i];
		if(v == fa) continue;
		int pos = v;
		b[v] += res - g[v];
		if(SZ(e[id[v]]) > SZ(e[id[u]])) {
			swap(id[u], id[v]);
			swap(rt[u], rt[v]);
			swap(b[u], b[v]);
		}
		for(int x : e[id[v]]) {
			int val = 2 * d[u] - d[x];
			chmin(p[u].b, query(rt[u], 1, n << 1, val) + b[u] + sq(val) - res + p[x].b + b[v] - sq(d[x]));
		}
		for(int x : e[id[v]]) {
			p[x].b += b[v] - b[u];
			push(rt[u], 1, n << 1, x);
			e[id[u]].push_back(x);
		}
	}
	e[id[u]].push_back(u);
	p[u].b -= b[u];
	p[u].b += sq(d[u]);
	push(rt[u], 1, n << 1, u);
}
void solve() {
	cin >> n;
	REP(_, n - 1) {
		int u, v;
		cin >> u >> v;
		add(u, v), add(v, u);
		ru[u] ++, ru[v] ++;
	}
	FOR(i, 1, n) id[i] = i;
	p[0] = {0, LNF};
	d[1] = n;
	dfs(1, 0);
	if(ru[1] == 1) {
		ll ans = LNF;
		FOR(i, 1, n) chmin(ans, p[i].b + p[i].k * d[1] + sq(d[1]) + b[1]);
		cout << ans << endl;
	}
	else {
		cout << p[1].b - sq(d[1]) + b[1] << endl;
	}
}
```

---

## 作者：hansang (赞：5)

## P3023 [USACO11OPEN] Soldering G
提供一篇复杂度正确且没有被 hack 原版官方解法。

做法解释是本人从英语题解翻译而来，为效果有删减增添。代码同上，为易懂做了小改。

经 @WZRYWZWY 提议，二编给出[官方题解](https://www.luogu.com.cn/paste/237o6yp9)。

---
### 解法说明：

考虑使用动态规划。
选择点（最优的）作为根，并考虑在根处焊接电线连边（以下称该边为切割线）成为树。
这样会有两种情况，分别是切割线**竖穿**当前点（连接父节点和子节点）和切割线**横穿**当前点（连接两个子节点）。
成本就为切割线的长度与所有其他线的总成本，且切割线的长度取决于其余焊接的边。

这里给出一个相对简单的动态规划解决方案：
对于当前点，如何计算最小成本？
我们从下到上计算，如果为**叶子节点**，则将其切割线视为长度为 $0$ 的边。
对于不是叶子节点的点，检查其子节点并找到两条切割线，让两个子节点的切割线**合并**成一条线。
因此任何点的可选切割线数最多是子树中的两个节点对数。
而计算当前点的成本为该点切割线的长度成本加上其他子树的总成本。
那么整个算法的总时间为节点对的总数，即 $O(N^2)$。

为了进一步减少运行时间，必须注意**成本函数的凸性特性**。
设当前子树的长度 $l$ 和成本 $c$，总成本函数就为 $(L+l)^2+c$，其中 $L$ 是子树外切割线的长度。
因为 $(L+l)^2+c=L^2+2 \times L \times l+l^2+c$，将 $l^2+c$ 和 $L^2+2 \times L \times l$ 分开。
单看 $l^2+c$，只要取它的最小值，再选择合适的 $L$，整个函数就最小。
而这个函数相当于**凸包**，维护它的**下凸壳**，也就是相邻两点更劣解可以删除。
可以对凸包进行**二分**查找，找到与当前子树外的边的最优解。

我们可以从所有子树中更新值，同时使用**启发式**算法加快时间。
存储所有解添加到数据结构，这些解的长度和成本都会随着合并子树而变化。
对于二分搜索节点的操作总数，最多是每个子树节点的总和（由于凸包所以可能比子树少），时间为 $O(N \log{N})$。
考虑合并解次数并注意它总是小于 $\log{N}$，且每次合并只会增加较小一半的值，时间为 $O(\log{N})$。

总共时间复杂度为 $O(N \log^2{N})$，可以通过。

### 代码：
请结合代码注释和以上说明理解，有问题欢迎指出。

```cpp
#include<bits/stdc++.h> //by: hansang
using namespace std;
typedef long long LL;
const int N=5e4+10;
const LL inf=1e9;
LL dep[N], dp[N]; int n, p[N]; 
//dp[i]为i子树的最小成本但缺少切割线有关的部分值（看calc函数和主函数注释），p数组表示偏移（启发式） 
struct node{
    LL d, c, f; //层数，当前点切割线有关花费，特殊值（后面会解释） 
    bool tag; //0表示切割线竖穿当前点（连接父节点和子节点），1表示切割线横穿当前点（连接两个子节点） 
};
 
vector<int> G[N]; set<node> b[N];
bool operator<(node a, node b) {
    if(a.tag || b.tag) return (a.f<b.f); //结合主函数的注释理解 
    if(a.d!=b.d) return (a.d>b.d); //非查找情况下 
    return (a.c<b.c); 
}
LL sqe(LL x) {return x*x;}
 
LL calc(node n1, node n2){ //这个函数是求出特殊值f（可以理解为斜率，那我们维护的就是一个下凸壳） 
    if(n1.d>n2.d) swap(n1, n2);
    //这个函数面向dep较小的，联系79，100和127行自行理解 
    LL res=(sqe(n1.d)+n1.c-sqe(n2.d)-n2.c)/(2*(n2.d-n1.d));
    //L^2+2*L*l+(l^2+c)，目前只有l和c确定，那么就先计算2*L*l+(l^2+c)
    //当前我们有2*L*l1+(l1^2+c1)和2*L*l2+(l2^2+c2)
    //相减得到：(l1^2+c1)-(l2^2+c2)+2*L*l1-2*L*l2 (一种符号) 0
    //化一下：  l1^2+c1-l2^2-c2 (一种符号) -2*(l1-L2)*L 
    //将-2*(l1-L2)除过去(不用变号)，就有：(l1^2+c1-l2^2-c2)/(2*(l2-L1)(一种符号)L 
    //当(一种符号)为大于号时，代表着2*L*l1+(l1^2+c1)>2*L*l2+(l2^2+c2)
    //而我们要改变L直到(一种符号)为小于或等于号，这样n1才比n2优  
    //就像这样：(l1^2+c1-l2^2-c2)/(2*(l2-L1)>L，只要不断给 L+1，总会变号的 
    while((sqe(n1.d)+n1.c-sqe(n2.d)-n2.c)>res*2*(n2.d-n1.d)) res++;
    //实际上，L(f)就代表着该节点较优时，子树外切割线的最小值，所以上面才按f排序 
    return res;
}
 
void dfs(int x, int fa) {
    LL res=-1, sum=0; //成本最小的切割线的目前x子树成本，不含切割线的目前x子树成本 
    for(auto y: G[x]) if(y!=fa){
        dep[y]=dep[x]+1; dfs(y, x);
        auto n1=*(--b[p[y]].upper_bound({0, 0, -dep[x], 1})); //f查找x就代表着要查找子树外切割线为x的最优解 
        //如果n1的f!=dep[x]，那么t就会大一点 
        LL t=sqe(n1.d-dep[x])+n1.c+dp[y]; //由y的切割线延申到x
        if(res!=-1) res+=t; //如果y不是第一个子节点，就累计 
         
        if(b[p[x]].empty()){ //启发式，如果x没有切割线 
            swap(p[x], p[y]);
            dp[x]=dp[y];
            //dp[y]=0; 
            //到时候取答案会直接取x，dp[y]不重要 
        }
         
        else{
            LL os=dp[x]+t, ot=dp[y]+sum; //分别为切割线在y上x的最小成本，切割线不在y上x的最小成本
            if(b[p[x]].size()<b[p[y]].size()){ //启发式，如果y的切割线比x的多话 
                swap(p[x], p[y]);
                swap(os, ot);
                //不改dp的原因是os和ot后面会赋值dp 
            }
            for(auto it: b[p[y]]){ //合并两条边 
                auto n2=*(--b[p[x]].upper_bound({0, 0, it.d-2*dep[x], 1})); //见39行 
                LL tmp=sqe(it.d+n2.d-2*dep[x])+it.c+n2.c+dp[x]+dp[y]; //把x的切割线和y的切割线连在一起 
                if(res==-1 || tmp<res) res=tmp; //找到了成本更小的切割线，更新 
            }
             
            for(auto it: b[p[y]]){ 
                it.c+=ot-os; //加上差值，代表当前情况切割线变到x其它不变（感性理解 
                auto n2=b[p[x]].insert(it).first; //这里first代表着插入it之后it在set里的位置 
                bool flag=0; //当前解是否最深 
                while(n2!=b[p[x]].begin()){ //不是最深的（维护it前的下凸壳） 
                    auto n3=n2; n3--; 
                    if((*n3).d==it.d){ //有层数和当前一样的解还更优 
                        b[p[x]].erase(n2); //删除当前解 
                        flag=1;
                        break;
                    }
                    node no=*n3;
                    it.f=calc(no, it); //赋值 
                    b[p[x]].erase(n2);
                    n2=b[p[x]].insert(it).first;
                    if(it.f<=(*n3).f) b[p[x]].erase(n3); //维护下凸壳 
                    else break;
                }
                if(flag) continue;
                 
                if(n2==b[p[x]].begin()){ //当前最深解 
                    it.f=-inf; //第一个的特殊值为无穷小 
                    b[p[x]].erase(n2); 
                    n2=b[p[x]].insert(it).first;
                }
                auto n3=n2; n3++;
                while(n3!=b[p[x]].end()){ //维护it后的下凸壳 
                    if(it.d==(*n3).d){ //同上 
                        b[p[x]].erase(n3);
                        n3=n2; n3++;
                        continue;
                    }
                    node no=*n3;
                    no.f=calc(it, no);
                    if(no.f<=it.f){
                        b[p[x]].erase(n2);
                        break;
                    }
                    b[p[x]].erase(n3);
                    n3=b[p[x]].insert(no).first;
                    auto n4=n3; n4++;
                    if(n4!=b[p[x]].end() && (*n4).f<=no.f) {
                        b[p[x]].erase(n3);
                        n3=n4;
                    }
                    else break;
                }
            }
            dp[x]=os; //更新（加上y的贡献） 
        }
        sum+=t;
    }
     
    if(b[p[x]].empty()){ //没有切割线或叶子节点
        b[p[x]].insert({dep[x], 0, -inf, 0}); //见88行 
    }
    else if(res!=-1){ //之前x有切割线（其实还是维护下凸壳） 
        node tmp={dep[x], res-dp[x], 0, 0}; //res-dp[x]为x点最优切割线有关花费 
        while(!b[p[x]].empty()){
            node n1=*b[p[x]].rbegin();
            tmp.f=calc(n1, tmp);
            if(tmp.f>n1.f) break;
            else b[p[x]].erase(n1); //tmp更优 
        }
         
        if(b[p[x]].empty()) tmp.f=-inf; //同88行 
        b[p[x]].insert(tmp); //插入 
    }
}
 
int main()
{
    scanf("%d", &n);
    for(int i=1; i<=n; i++) p[i]=i; //偏移值初始化 
    for(int i=1; i<n; i++){
        int a, b; scanf("%d%d", &a, &b);
        G[a].push_back(b);
        G[b].push_back(a);
    }
     
    dep[1]=0; dfs(1, 0);
    if(G[1].size()==1){
        auto it=--b[p[1]].upper_bound({0, 0, 0, 1}); //查找最优解 
        printf("%lld\n", dp[1]+(*it).c+sqe((*it).d));
        //1除切割线外花费+某点切割线花费+1到某点距离的平方 
    }
    else{
        auto it=b[p[1]].rbegin(); //取最后一个最靠近1的，含信息量高且因为维护过是最优的
        printf("%lld\n", dp[1]+(*it).c+sqe((*it).d));
    }
    return 0;
}
```

感谢观看。

 _"‌‌Non mollare mai. "_

---

