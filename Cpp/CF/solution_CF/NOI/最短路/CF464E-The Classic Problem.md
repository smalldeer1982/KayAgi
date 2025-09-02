# The Classic Problem

## 题目描述

You are given a weighted undirected graph on $ n $ vertices and $ m $ edges. Find the shortest path from vertex $ s $ to vertex $ t $ or else state that such path doesn't exist.

## 说明/提示

A path from vertex $ s $ to vertex $ t $ is a sequence $ v_{0} $ , ..., $ v_{k} $ , such that $ v_{0}=s $ , $ v_{k}=t $ , and for any $ i $ from 0 to $ k-1 $ vertices $ v_{i} $ and $ v_{i+1} $ are connected by an edge.

The length of the path is the sum of weights of edges between $ v_{i} $ and $ v_{i+1} $ for all $ i $ from 0 to $ k-1 $ .

The shortest path from $ s $ to $ t $ is the path which length is minimum among all possible paths from $ s $ to $ t $ .

## 样例 #1

### 输入

```
4 4
1 4 2
1 2 0
2 3 0
3 4 0
1 4
```

### 输出

```
3
4
1 2 3 4 
```

## 样例 #2

### 输入

```
4 3
1 2 4
2 3 5
3 4 6
1 4
```

### 输出

```
112
4
1 2 3 4 
```

## 样例 #3

### 输入

```
4 2
1 2 0
3 4 1
1 4
```

### 输出

```
-1
```

# 题解

## 作者：Kinandra (赞：37)


1. 标签: 主席树, 图论-最短路.  
2. 大体过程和普通的最短路相差无几, 但是最短路要涉及到对权值的两个操作:**比较大小**和**加法**, 设这两个操作的复杂度分别为$\mathcal O(\alpha)$和$\mathcal O(\beta)$, 则算法复杂度为$\mathcal O(\alpha (n+m)\log n+\beta m)$, 看得出用$10$进制高精度来维护权值复杂度是不够优秀的.  
3. 这道题有一个显然要被用到的性质:边权为$2^x$, 直接将权值(**这里包括边权和点到$s$距离**)二进制表示, 可以得到一个字符串(高位不足添0). 比较权值大小, 实际上就是比较字符串的字典序, 这个可用hash求LCP做到$\mathcal O(\log x)$, 但加法操作还是$\mathcal O(x)$的.  
4. 发现加法只涉及到某个值加上一个$2^x$(即某个点到$s$的**距离**加上某条边的**边权**), 在二进制位上的体现就是将某一段$1$置$0$再将某个$0$修改为$1$, 这个可以用线段树来维护, 考虑到我们不能直接在加数上修改, 所以我们要用主席树来维护, 加法操作变为区间置$0$和单点修改为$1$.   
5. 区间置$0$可以通过建一棵满的所有位置权值均为$0$的线段树, 将需要置$0$的区间连到这棵树上来实现, 这里一次操作时空复杂度都是$\mathcal O(\log x)$的; 求出需要置$0$的区间时间上可以做到$\mathcal O(\log^2 x)$(二分区间另一个端点), 所以加法操作的时间复杂度就优化到了$\mathcal O(\log^2 x)$, 总空间复杂度为$\mathcal O(m\log x)$.  
6. $n,m,x$同级所以复杂度为$\mathcal O(n\log^2 n)$.

```cpp
#include <cstdio>
#include <iostream>
#define X 100040
#define mod 1000000007
using namespace std;

int n, m, s, t;
int head[200005], nxt[400005], to[400005], cnt;
int w[200005];
unsigned long long base[200005], base1[200005];

int read();

void add(int f, int t, int wei) {
    nxt[++cnt] = head[f], head[f] = cnt, to[cnt] = t;
    w[cnt] = wei;
    return;
}

int root[400005];

struct Seg {
    int idcnt;
    int ls[4000006], rs[4000006], tsum[4000006];
    unsigned long long ths[4000006], ths1[4000006];

    void update(int k) {
        tsum[k] = tsum[ls[k]] + tsum[rs[k]];
        ths[k] = (ths[ls[k]] + ths[rs[k]]) % mod;
        ths1[k] = ths1[ls[k]] + ths1[rs[k]];
        return;
    }

    int build(int l, int r, int v) {
        int ret = ++idcnt;
        if (l == r) {
            tsum[ret] = v;
            ths[ret] = base[l] * v, ths1[ret] = base1[l] * v;
            return ret;
        }
        int mid = l + r >> 1;
        ls[ret] = build(l, mid, v);
        rs[ret] = build(mid + 1, r, v);
        update(ret);
        return ret;
    }

    int query(int l, int r, int k, int st, int en) {
        if (st > r || en < l) return 0;
        if (st <= l && en >= r) return tsum[k];
        int mid = l + r >> 1;
        return query(l, mid, ls[k], st, en) + query(mid + 1, r, rs[k], st, en);
    }

    int find(int l, int r, int k, int pos) {
        if (l == r) return l;
        int mid = l + r >> 1;
        if (pos > mid) return find(mid + 1, r, rs[k], pos);
        if (query(l, mid, ls[k], pos, mid) == mid - pos + 1)
            return find(mid + 1, r, rs[k], mid + 1);
        return find(l, mid, ls[k], pos);
    }

    int isrt(int l, int r, int k, int pos) {
        int ret = ++idcnt;
        ls[ret] = ls[k], rs[ret] = rs[k];
        if (l == r) {
            tsum[ret] = 1;
            ths[ret] = base[l], ths1[ret] = base1[l];
            return ret;
        }
        int mid = l + r >> 1;
        if (pos <= mid)
            ls[ret] = isrt(l, mid, ls[k], pos);
        else
            rs[ret] = isrt(mid + 1, r, rs[k], pos);
        update(ret);
        return ret;
    }

    int move(int l, int r, int k, int k1, int st, int en) {
        if (st > r || en < l) return k;
        if (st <= l && en >= r) return k1;
        int ret = ++idcnt;
        int mid = l + r >> 1;
        ls[ret] = move(l, mid, ls[k], ls[k1], st, en);
        rs[ret] = move(mid + 1, r, rs[k], rs[k1], st, en);
        update(ret);
        return ret;
    }

    int add(int rt, int w) {
        int pos = find(0, X, rt, w);
        int tmp = isrt(0, X, rt, pos);
        if (pos == w) return tmp;
        tmp = move(0, X, tmp, root[0], w, pos - 1);
        return tmp;
    }

    bool sm(int k1, int k2) {
        return tsum[k1] == tsum[k2] && ths[k1] == ths[k2] &&
               ths1[k1] == ths1[k2];
    }

    bool cmp(int l, int r, int k1, int k2) {
        if (l == r) return tsum[k1] <= tsum[k2];
        int mid = l + r >> 1;
        if (sm(rs[k1], rs[k2])) return cmp(l, mid, ls[k1], ls[k2]);
        return cmp(mid + 1, r, rs[k1], rs[k2]);
    }
} seg;

struct heap {
    int pu[400005], prt[400005];
    int ch[400005][2], h[400005];
    int idcnt, root, sz;

    int merge(int x, int y) {
        if (!x || !y) return x + y;
        if (seg.cmp(0, X, prt[y], prt[x])) swap(x, y);
        ch[x][1] = merge(ch[x][1], y);
        if (h[ch[x][1]] > h[ch[x][0]]) swap(ch[x][0], ch[x][1]);
        h[x] = h[ch[x][0]] + 1;
        return x;
    }

    void push(int u, int rt) {
        sz++;
        pu[++idcnt] = u, prt[idcnt] = rt;
        root = merge(idcnt, root);
    }

    void pop() { sz--, root = merge(ch[root][0], ch[root][1]); }

    int top() { return pu[root]; }

    bool empty() { return sz == 0; }
} q;

bool vis[200005];
int pv[200005];

int st[200005], top;

void Dijkstra() {
    int tmp = seg.build(0, X, 1);
    for (int i = 1; i <= n; ++i) root[i] = tmp;
    root[0] = root[s] = seg.build(0, X, 0);
    q.push(s, root[s]);
    while (!q.empty()) {
        while (!q.empty() && vis[q.top()]) q.pop();
        if (q.empty()) break;
        int u = q.top();
        vis[u] = 1;
        q.pop();
        for (int i = head[u]; i; i = nxt[i]) {
            int v = to[i];
            if (vis[v]) continue;
            int trt = seg.add(root[u], w[i]);
            if (seg.cmp(0, X, root[v], trt)) continue;
            root[v] = trt, pv[v] = u;
            q.push(v, root[v]);
        }
    }
    if (root[t] == tmp) {
        puts("-1");
    } else {
        printf("%d\n", (int)seg.ths[root[t]]);
        for (int u = t; u != s; u = pv[u]) {
            st[++top] = u;
        }
        st[++top] = s;
        printf("%d\n", top);
        for (int i = top; i >= 1; --i) {
            printf("%d ", st[i]);
        }
        puts("");
    }
    return;
}

int main() {
    n = read(), m = read();
    base[0] = 1, base1[0] = 1;
    for (int i = 1; i <= X; ++i)
        base[i] = base[i - 1] * 2 % mod, base1[i] = base1[i - 1] * 17;
    for (int i = 1; i <= m; ++i) {
        int u = read(), v = read(), x = read();
        add(u, v, x), add(v, u, x);
    }
    s = read(), t = read();
    Dijkstra();
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (!isdigit(c)) f = (c == '-') ? -1 : f, c = getchar();
    while (isdigit(c)) x = x * 10 + c - '0', c = getchar();
    return x * f;
}


```


---

## 作者：MoYuFang (赞：29)

模运算下的数值难以比较大小，且这道题涉及加法，不是乘法，不能使用对数放缩，只能用高精度，但直接使用则时空复杂度爆炸。

#### 考虑优化高精度

注意到边权全为 $2$ 的幂次，这提示我们用二进制表示数值。

这里设数值 $val$ 二进制表示下第 $i$ 位为 $val(i)$，每次给数值 $val$ 加 $2^x$ 相当于找最小的 $y$ 使得 $y>=x$ 且 $val(y)=0$，然后让 $x$ 到 $y$ 之间的 $1$ 归零，$val(y)$ 置为 $1$。

归零操作相当于区间覆盖，置 $1$ 的操作相当于单点修改，于是考虑每个数值均用一颗权值线段树维护，寻找 $y$ 则可以通过线段树二分完成，三种操作都可以单次 $O(\log x)$ 完成。

比较的话就相当于字典序比较，先找到两个数值最高的不相同的位，然后比较那一位的大小即可，这一步就是个经典的字符串算法，用 二分+ 进制 $\text{hash}$ 就可以以单次 $O(\log x)$ 完成。

进制 $hash$ 满足结合律且可以 $O(1)$ 快速合并两个子区间的进制 ，于$\text{hash}$是可以在权值线段树上多加一个变量维护每个节点对应区间的 $\text{hash}$ 值。 

进一步的，因为在 $\text{dijkstra}$ 中涉及到 $O(n+m)$ 个数值，如果每个数值都用一颗权值线段树则炸时空，而单次给数值加上 $2$ 的幂次只会影响权值线段树上 $O(\log x)$ 个节点，显然可以用可持久化优化时空，总时间复杂度为 $O(m\log m \log x)$ 。

思路还是很好想的，是道假黑题。

#### 具体实现

直接用 $2$ 作为进制 $\text{hash}$ 的进制，$1000000007$ 作为模数，这样在输出答案时直接输出 $\text{hash}$ 值就行了。

初步判读线段树每个节点需要保存左儿子指针，右儿子指针，$\text{hash}$ 值，区间覆盖懒标记，区间内是否全为 $1$ 标记。

一般来说支持区间覆盖操作需要带上懒标记，但这题是区间归零操作，且用的是动态开点线段树，完全没必要带这一懒标记，因为区间归零操作就相当于让节点变成 $none$，所以可以省去区间覆盖的懒标记。

单点修改也很套路。

寻找 $y$ 这一步用线树二分时需要快速判断某一节点所对应的区间是否全为 $1$，考虑到我们都已经维护了区间的  值$\text{hash}$了，何不好好利用它，没必要再多加一个判断区间内是否为全 $1$ 的标记了，预处理出每个长度的全 $1$ 的区间对应的 $\text{hash}$ 值，每次判断某个区间是否全为 $1$ 直接比较 $\text{hash}$ 值就行了。

比较操作直接在线段树上二分就行了。

总结一下，线段树的每个节点只需保存左儿子指针，右儿子指针和 $\text{hash}$ 值。

在 $\text{dijkstra}$ 时，用 $dis(u)$ 来代表节点 $u$ 到源点的最短路长度数值（实际上存的是权值线段树的根节点），枚举边时也会生成一个临时数值 $tmp = dis(u)+2^{x_{(u,v)}}$ （也是一颗权值线段树）。

当 $tmp$ 与 $dis(v)$ 比较完后，其中一个数值就废弃了，因为目前肯定没有任何数值是通过 $tmp$ 或 $dis(v)$生成的，生成那个废弃数值所新用的节点都回收后不会影响到其它数值，可以回收再利用，考虑如何回收这些节点。

一开始我考虑的是为 $tmp$ 和每个 $dis(*)$ 各开一个 ```vector``` 保存生成它所新用的节点，然后在它废弃时再将对应 ```vector``` 中所有节点回收。

然后 $\text{RE}$ 了，```debug``` 后发现原因在于若废弃的数值是 $dis(v)$，尽管我回收了 $dis(v)$，但优先队列中仍存在 $(v,dis(v))$ 二元组，但关于那个被废弃的数值的所有比较已经失效，于是这基于比较实现的 ```STL``` 就导致 $\text{RE}$ 了。

解决办法有两个，一是放弃回收节点的想法，二是用 ```set``` 代替优先队列，然后每次废弃 $dis(v)$ 前先从 ```set``` 里删掉对应的二元组 $(v,dis(v))$。

既然都打算回收节点了，那就选方法二吧，反正复杂度仍不变。

经过一番仔细分析后，发现自己脑残了，即便回收了节点空间复杂度也没怎么降，只不过是从 $O(m\log x)$ 变为了 $O(n \log x)$，但 $m$ 与 $n$ 同阶，相当于白忙活了，只收获了一个 $\text{RE}$ 技巧。

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <iostream>
#include <assert.h>
#include <vector>
#include <set>
using namespace std;

#define re register
#define sf scanf
#define pf printf
#define nl() putchar('\n')
#define ms(x, val) memset(x, val, sizeof(x))
#define ll long long
#define _for(i, a, b) for(re int (i) = (a); (i) < (b); ++(i))
#define _rfor(i, a, b) for(re int (i) = (a); (i) <= (b); ++(i))
#define _fev(p, u) for(re int (p) = head[(u)]; (p); (p) = nex[(p)])
#define inf 0x7fffffff
#define maxn 101005
#define maxnn 3100005
#define mod 1000000007ll

int rdnt(){
	re int x = 0, sign = 1;
	re char c = getchar();
	while (c < '0' || c > '9') { if (c == '-') sign = -1; c = getchar(); }
	while (c >= '0' && c <= '9') x = (x<<3) + (x<<1) + (c ^ 48), c = getchar();
	return x * sign;
}

bool vis[maxn]; //dijkstra 用的 
int	
	//模 1000000007 意义下 2 的幂次 
	epw[maxn],
	
	//模 1000000007 意义下全 1 区间的 hash 值 
	hsh_one[maxn], 

	//权值线段值域 
	rg = maxn-5, 

	//内存池，用于回收节点 
	pcnt = 0, 
	pool[maxnn], 
	
	//邻接表 
	ecnt = 1, 
	head[maxn],
	to[maxn*2], 
	nex[maxn*2],
	we[maxn*2],
	
	//单元最短路数组（实际上存的是权值线段树的根节点编号） 
	dis[maxn],
	
	//输出路径方案用的 
	top = 0,
	path[maxn], //path(v) 代表 v 是从哪转移过来的 
	stk[maxn];
vector<int>
	tmp_set, //用来装生成临时数值所新用的线段树节点 
	seg_set[maxn]; //用来装生成 dis(v) 所新用的线段树节点 
struct Seg{ int lc, rc, hsh; } seg[maxnn]; //线段树节点，分别代表左、右儿子指针和 hash 值 
#define lc(x) seg[x].lc
#define rc(x) seg[x].rc
#define hsh(x) seg[x].hsh
struct Par{ int u, d; };
bool cmp(int x, int y, int tl, int tr);
inline bool operator<(const Par &p1, const Par &p2){
	//因为删除二元组时要精确查找二元组，所以无向图节点的编号也要纳入比较范围 
	return (hsh(p1.d) != hsh(p2.d)) ? cmp(p1.d, p2.d, 1, rg) : p1.u < p2.u; 
}
set<Par> pq; //set 版优先队列 

void add_edge(re int u, re int v, re int w){
	to[++ecnt] = v; nex[ecnt] = head[u]; head[u] = ecnt; we[ecnt] = w;
	to[++ecnt] = u; nex[ecnt] = head[v]; head[v] = ecnt; we[ecnt] = w;
}

//申请一个新的线段树节点并从 nn 拷贝 
int new_node(re int nn){
	re int x = pool[pcnt--];
	seg[x] = seg[nn];
	return x;
}

//回收单个线段树节点 
void del(re int x){
	pool[++pcnt] = x;
}

//回收 vector 里的线段树节点 
void clr(vector<int> &vec){
	_for(i, 0, vec.size()) del(vec[i]);
	vec.clear();
}

//线段树 push up 
void ud(re int x, re int len){
	hsh(x) = (hsh(lc(x)) + (ll)hsh(rc(x))*epw[len]%mod)%mod;
}

//比较两个数值，即判断 x < y 
bool cmp(int x, int y, int tl, int tr){
	if (tl == tr) return hsh(x) < hsh(y);
	int mi = (tl+tr)>>1;
	return (hsh(rc(x)) == hsh(rc(y))) ? cmp(lc(x), lc(y), tl, mi) : cmp(rc(x), rc(y), mi+1, tr);
}

//线段树二分找到区间 [l,r] 内第一个不为 0 的位置 
int qry(int x, int l, int r, int tl, int tr){
	if (tl > r || tr < l || hsh(x) == hsh_one[tr-tl+1]) return -1;
	if (hsh(x) == 0) return max(l, tl);
	int mi = (tl+tr)>>1, tmp = qry(lc(x), l, r, tl, mi);
	return (tmp > 0) ? tmp : qry(rc(x), l, r, mi+1, tr);
}

//区间归零操作，并将新用的节点加入到 vec 里
void cover(int x, int &y, int l, int r, int tl, int tr, vector<int> &vec){
	if (l == tl && r == tr){ y = 0; return; }
	vec.push_back(y = new_node(x));
	int mi = (tl+tr)>>1;
	if (r <= mi) cover(lc(x), lc(y), l, r, tl, mi, vec);
	else if (l > mi) cover(rc(x), rc(y), l, r, mi+1, tr, vec);
	else cover(lc(x), lc(y), l, mi, tl, mi, vec), cover(rc(x), rc(y), mi+1, r, mi+1, tr, vec);
	ud(y, mi-tl+1);
}

//单点修改，并将新用的节点加入到 vec 里
void addn(int x, int &y, int p, int tl, int tr, vector<int> &vec){
	if (tl == tr){
		vec.push_back(y = new_node(0));
		hsh(y) = 1;
		return;
	}
	vec.push_back(y = new_node(x));
	int mi = (tl+tr)>>1;
	if (p <= mi) addn(lc(x), lc(y), p, tl, mi, vec);
	else addn(rc(x), rc(y), p, mi+1, tr, vec);
	ud(y, mi-tl+1);
}

//数值 x 上加入 2^(w-1)，只所以 w-1 是为了让权值线段树的值域大于等于 1 
//返回生成的数值对应的权值线段树的根节点 
int add(re int x, re int w, vector<int> &vec){
	vec.clear();
	re int p = qry(x, w, rg, 1, rg), tmp = 0;
	addn(x, tmp, p, 1, rg, vec);
	if (p > w) cover(tmp, tmp, w, p-1, 1, rg, vec);
	return tmp;
}

void dijkstra(re int n, re int s){
	re int u, v, d, tmp;
	_rfor(i, 1, n) dis[i] = -1;
	dis[s] = 0;
	pq.insert((Par){s, dis[s]});
	while(!pq.empty()){
		auto it = pq.begin();
		u = it->u; d = it->d; pq.erase(it);
		if (vis[u]) continue;
		vis[u] = true;
		_fev(p, u){
			if (vis[v = to[p]]) continue;
			tmp = add(d, we[p], tmp_set);
			if (dis[v] == -1 || cmp(tmp, dis[v], 1, rg)){
				if (dis[v] != -1){
					//从 set 里精确删除 
					it = pq.find((Par){v, dis[v]});
					pq.erase(it);
				}
				path[v] = u;
				dis[v] = tmp;
				//交换 vector 
				swap(tmp_set, seg_set[v]);
				pq.insert((Par){v, dis[v]});
			}
			//回收节点 
			clr(tmp_set);
		}
	}
}

//求出路径方案 
void dfs(int s, int u){
	stk[top++] = u;
	if (u != s) dfs(s, path[u]);
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("sample.in", "r", stdin);
	freopen("sample.out", "w", stdout);
	#endif
	
	//预处理 
	hsh_one[0] = lc(0) = rc(0) = hsh(0) = 0; epw[0] = 1;
	_for(i, 1, maxnn) pool[++pcnt] = maxnn-i;
	_for(i, 1, maxn) epw[i] = (ll)epw[i-1]*2%mod, hsh_one[i] = (epw[i]+mod-1)%mod;
	
	re int n = rdnt(), m = rdnt(), s, t, u, v, w;
	_rfor(i, 1, m){
		u = rdnt(), v = rdnt(), w = rdnt();
		add_edge(u, v, w+1);
	}
	s = rdnt(); t = rdnt();
	dijkstra(n, s);

	if (dis[t] == -1){ pf("-1\n"); return 0; }
	re int ans = hsh(dis[t]); top = 0;
	pf("%d\n", ans);
	dfs(s, t);
	pf("%d\n", top);
	while(top){
		pf("%d", stk[--top]);
		if (top)putchar(' ');
	}
	nl();
	
	return 0;
}

```



---

## 作者：pldzy (赞：21)

[CF 传送门：CF464E The Classic Problem](https://codeforces.com/problemset/problem/464/e)

首先在此感谢 @[orz_z](https://www.luogu.com.cn/user/257146) 和 @[Albert_van](https://www.luogu.com.cn/user/326780) 两个大佬的学术支持。

## Solution

最短路 + 主席树。

最短路不用说了，主要考虑如何计算那些 $2$ 的若干次方的边权。维护边权不太可行，我们维护最短路中到每一个节点的最近距离 $dis_i$。数据实在太大了，高精度显然不行。

往数据结构方面想，发现若是对一个节点的 $dis_i$ 建一棵线段树，我们要在上面维护什么。显然，只有相加和比大小。线段树的每一位代表数值二进制上的每一位，初始全为 0。

- 相加：

	由于都是 $2$ 的若干次方，所以相加的时候，不妨记加上 $2^x$，实际上就是将从第 $x$ 为开始的、向前的、连续的若干个 $1$ 全部更改为 $0$，然后在这些 $0$ 前面加 $1$。换言之，区间修改 + 单点修改。那比大小呢？对于线段树中的每个区间，我们都维护这个区间所组成的数的数值，维护方式是哈希。
    
- 比大小：

	对于两个相同长度的不同区间，**不能直接比较两者的哈希值**，因为**哈希只能确定两个区间相同，但无法比大小**。所以我们要找到两个区间的最长相同前缀的后一位，根据这一位来确定两个区间的大小关系。

因为是跑最短路，所以每个节点 $i$ 的 $dis$ 值是由某一个与自己直接联通的节点松弛而来的（起点除外），故使用主席树。

最后记录路径较简单，不细说。

## Code

$93$ 行的 CF464E，你值得拥有。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; 
#define rep(i, a, b) for(register int i = a; i <= b; ++i)
#define ls(x) t[x].ls
#define rs(x) t[x].rs
#define s(x) t[x].sum
#define sz(x) t[x].sz
#define h(x) t[x].hsh
#define gmd mid=l+r>>1
const int maxn = 1e5 + 100, N = 1e5 + 20, mod = 1e9 + 7;
int n, m, S, T, tot, u, v, w;
int pw[maxn], rt[maxn], cnt, hd[maxn], pre[maxn], ot[maxn];
bool vis[maxn];
struct node{
	int to, nxt, w;
}e[maxn << 1]; 
struct tree{
	int ls, rs, sum, sz; ll hsh;
}t[maxn * 77];
inline void add(int u, int v, int w){
	cnt++; e[cnt].to = v, e[cnt].nxt = hd[u], e[cnt].w = w, hd[u] = cnt; 
}
inline void up(int x){
	s(x) = s(ls(x)) + s(rs(x));
	h(x) = (pw[sz(ls(x))] * h(rs(x)) % mod + h(ls(x))) % mod;
}
inline void build(int &x, int l, int r){
	x = ++tot, sz(x) = r - l + 1;
	if(l == r) return;
	int mid = l + r >> 1; build(ls(x), l, mid), build(rs(x), mid + 1, r), up(x);
}
inline void upp(int &x, int lst, int l, int r, int pos){
	x = ++tot, t[x] = t[lst];
	if(l == r) {s(x) += 1, h(x) += 1; return;}
	int mid = l + r >> 1; if(pos <= mid) upp(ls(x), ls(lst), l, mid, pos); else upp(rs(x), rs(lst), mid + 1, r, pos); up(x);
}
inline void upr(int &x, int lst, int init, int l, int r, int L, int R){
	if(l >= L and r <= R) {x = init; return;}
	x = ++tot, t[x] = t[lst]; int mid = l + r >> 1;
	if(L <= mid) upr(ls(x), ls(lst), ls(init), l, mid, L, R); if(R > mid) upr(rs(x), rs(lst), rs(init), mid + 1, r, L, R); up(x);
}
inline int qry(int x, int l, int r, int L, int R){
	if(l >= L and r <= R) return s(x); int mid = l + r >> 1;
	return (L <= mid ? qry(ls(x), l, mid, L, R) : 0) + (R > mid ? qry(rs(x), mid + 1, r, L, R) : 0);
}
inline int fnd(int x, int l, int r, int p, int num){
	if(l == r) return l; int mid = l + r >> 1; 
	if(s(ls(x)) >= mid - p + 1 + num) return fnd(rs(x), mid + 1, r, p, num - s(ls(x))); else return fnd(ls(x), l, mid, p, num);
}
inline void mdf(int &x, int lst, int w){
	int c = w > 0 ? qry(lst, 0, N, 0, w - 1) : 0;int y = fnd(lst, 0, N, w, c);
	if(y > w) upr(x, lst, rt[0], 0, N, w, y - 1); else x = lst;
	upp(x, x, 0, N, y);
}
inline bool cmp(int a, int b, int l, int r){
	if(l == r) return s(a) > s(b); int mid = l + r >> 1;
	if(h(rs(a)) == h(rs(b))) return cmp(ls(a), ls(b), l, mid);
	return cmp(rs(a), rs(b), mid + 1, r); 
}
inline void Pre(){
	pw[0] = 1; rep(i, 1, N - 1) pw[i] = pw[i - 1] * 2ll % mod;
}
struct que{
	int id, rt;
	bool operator <(const que &tt) const{return cmp(rt, tt.rt, 0, N);}
}; priority_queue<que> q;
inline void dijkstra(){
	build(rt[0], 0, N), rt[S] = rt[0], q.push({S, rt[S]});
	while(!q.empty()){
		int u = q.top().id; q.pop();
		if(vis[u]) continue; vis[u] = 1;
		if(u == T) break;
		for(int v, i = hd[u]; i; i = e[i].nxt){
			mdf(rt[n + 1], rt[u], e[i].w);
			if(!rt[v = e[i].to] or cmp(rt[v], rt[n + 1], 0, N)){
				rt[v] = rt[n + 1], pre[v] = u; if(!vis[v]) q.push({v, rt[v]});	
			}
		}
	}
}
signed main(){
	Pre(), scanf("%d%d", &n, &m);
	rep(i, 1, m) scanf("%d%d%d", &u, &v, &w), add(u, v, w), add(v, u, w);
	scanf("%d%d", &S, &T), dijkstra();
	if(!vis[T]){printf("-1\n"); return 0;} else printf("%lld\n", h(rt[T]));
	int p; p = ot[++ot[0]] = T;
	while(p != S) 
		p = pre[p], ot[++ot[0]] = p;
	printf("%d\n", ot[0]);
	for(int i = ot[0]; i; i--) printf("%d ", ot[i]);
	return 0;
}
```


------------
感谢阅读。

---

## 作者：SDNetFriend (赞：14)

## CF464E The Classic Problem 题解

### 总体情况

大体仍是主席树+哈希，但在进位处理方面采用了压位优化，目前全谷最优解（2021.10.15）。

### 题意这里不再赘述

[CF464E The Classic Problem](https://www.luogu.com.cn/problem/CF464E)

### 朴素思路

首先最短路可以想到 Dijkstra。

我们需要支持两个数比较大小和加法操作，但问题是边权范围太大无法直接储存，如果用高精度的话时间复杂度又会多一个 $x$，难以承受。

### 考虑优化

发现每次更新长度时，如一条 $u\to v$ 的路径，可能会使 $dis_v$ 成为 $dis_u$ 加上 $2$ 的次幂，如果在二进制下的话可以发现不考虑进位那么发生变化的只有一位。这个性质可以让我们想到用二进制的主席树来维护 $dis$。

### 比较大小

比较常见的问题，朴素地做即找到两个数从高到低第一个不一样的位置并且比较大小，这一步操作可以用哈希在线段树上二分来实现。

### 加法

刚才我们分析“只有一位产生变化”前提是不产生进位。对于进位，有一种做法即找到当前位置向高位最长的连续一段一并将其置零，下一个零的位置变成一，但这样可能维护较为麻烦并且较慢，考虑优化。

我们刚才提到一次只加一个 $2$ 的次幂，那有个有趣的做法，即二进制压位，比如我们每 $50$ 位压成一位，那么线段树每个点对应的区间就分别是 $[0,49],[50,99],...$ 这种。

我们发现如果这样操作进位操作是非常少的，因为这样的话比如在 $[0,49]$ 这个区间内最可能产生进位的操作是加上 $2^{49}$，但我们发现如果进位的话只会在 $[50,99]$ 加上 $1$，这样的话在下一位几乎是不会产生进位的，除非下一个区间 $50$ 位全都是 $1$，但这样也只会产生一次进位。

总而言之如果把 $50$ 位压到一起的话进位操作就会非常少，实测这样速度快得飞起，当场冲到最优解。

### 实现细节

注意这里主席树比较的话是要创建新根的，也就是每次比较都会产生一定的空间消耗，那我们就要尽量减少比较次数。

每次我们把点入队时，可能还没处理就被再次入队，显然每次入队对应的根是不同的，我们在结构体里加一下入队时的根，如果和当前根不同说明被再次入队了，就可以直接跳过不进行计算，蒟蒻因为没加这个优化被卡了一个多小时（雾）。

### 最后

其实这种方法是可以被 Hack 掉的，比如可以从起点开始到某个点来一条链，边权依次 $+1$，然后在这个点再接个类似菊花图的东西，各点再连向终点，边权都是 $2^0$ 就会被卡成 $O(n^2\log n)$。

不过善良的出题人并没有卡这种做法，实际上真的要卡的话加上找连续段也是可以通过的。如果不是很严格地来卡这种做法的话复杂度是很难退化的。

### 贴代码

```cpp
#include <bits/stdc++.h>
#define lint long long
#define rint register int
using namespace std;
inline lint read(){
    char c;lint f=1,res=0;
    while(c=getchar(),!isdigit(c))if(c=='-')f*=-1;
    while(isdigit(c))res=res*10+c-'0',c=getchar();
    return res*f;
}
const int N=1e5+5,M=2e5+5,B=50,R=2e3+5,P=1e7+5;
const lint md=1e9+7,bas=2333333;
int hed[N],nxt[M],ver[M],w[M],ne=1;
inline void ade(int u,int v,int _w){
    ver[++ne]=v;
    nxt[ne]=hed[u];
    hed[u]=ne;
    w[ne]=_w;
}
inline void adbe(int u,int v,int _w)
    {ade(u,v,_w);ade(v,u,_w);}
int n,m,s,t;
int rt[N],tot=0;
lint ans=0,pw[B+1],_pw[R];
int ch[P][2],mx[P];
lint hsh[P],pwb[N],sum[P];
inline int cpy(int y){
    int x=++tot;
    if(y){
        memcpy(ch[x],ch[y],sizeof ch[x]);
        sum[x]=sum[y];mx[x]=mx[y];
    }else mx[x]=-1;
    return x;
}
inline lint qpow(lint x,lint y){
    lint res=1;
    while(y){
        if(y&1)res=res*x%md;
        x=x*x%md;y>>=1;
    }return res;
}
//sum只存在于最底层 
inline void pushup(int x,int l,int r){
    int lc=ch[x][0],rc=ch[x][1],mid=l+r>>1;
    mx[x]=max(mx[lc],mx[rc]);
    hsh[x]=(pwb[r-mid]*hsh[ch[x][1]]%md+hsh[ch[x][0]])%md;
}
void add(int x,int l,int r,int p,lint v){
    if(l==r){
        sum[x]+=v;hsh[x]=sum[x];
        if(sum[x])mx[x]=l;
        else mx[x]=-1;
        return;
    }int mid=l+r>>1;
    if(p<=mid)add(ch[x][0]=cpy(ch[x][0]),l,mid,p,v);
    else add(ch[x][1]=cpy(ch[x][1]),mid+1,r,p,v);
    pushup(x,l,r);
}
lint gsum(int x,int l,int r,int p){
    if(!x)return 0;
    if(l==r)return sum[x];
    int mid=l+r>>1;
    if(p<=mid)return gsum(ch[x][0],l,mid,p);
    else return gsum(ch[x][1],mid+1,r,p);
}
//获取整棵树答案对md取模的结果 
//编号从0开始，第零段对应 [0,49] 
lint gans(int x,int l,int r){
    if(!x||mx[x]==-1)return 0;
    if(l==r)return sum[x]%md*_pw[l]%md;
    lint mid=l+r>>1,res=0;
    res+=gans(ch[x][0],l,mid);
    res+=gans(ch[x][1],mid+1,r);
    return res%md;
}
//在u的根的基础上加上2^x产生一个新根 
inline int upd(int u,int x){
    int nrt=cpy(rt[u]);
    add(nrt,0,R,x/B,pw[x%B]);
    int p=x/B;lint tmp;
    while((tmp=gsum(nrt,0,R,p))>=pw[B]){
        add(nrt,0,R,p,tmp%pw[B]-tmp);
        add(nrt,0,R,p+1,tmp/pw[B]);
        ++p;
    }return nrt;
}
//返回x的值是否小于y 
bool les(int x,int y,int l,int r){
    if(mx[x]!=mx[y])return mx[x]<mx[y];
    if(l==r)return sum[x]<sum[y];
    int mid=l+r>>1;
    if(hsh[ch[x][1]]!=hsh[ch[y][1]])
        return les(ch[x][1],ch[y][1],mid+1,r);
    else return les(ch[x][0],ch[y][0],l,mid);
}
struct node{int id,rt;};
inline bool operator>(node x,node y)
    {return les(rt[y.id],rt[x.id],0,R);}
priority_queue<node,vector<node>,greater<node> > q;
int pre[N],rd[N],cnt;
inline void Dijkstra(){
    q.push(node{s,rt[s]});
    while(!q.empty()){
        node tp=q.top();
        q.pop();int u=tp.id;
        if(tp.rt!=rt[u])continue;
        for(rint e=hed[u];e;e=nxt[e]){
            int v=ver[e];
            int tmp=upd(u,w[e]);
            if(!rt[v]||les(tmp,rt[v],0,R)){
                rt[v]=tmp;pre[v]=u;
                q.push(node{v,rt[v]});
            }
        }
    }
    ep:if(!rt[t])ans=-1;
    else ans=gans(rt[t],0,R);
    int u=t;
    while(u){
        rd[++cnt]=u;
        u=pre[u];
    }
}
inline void init(){
    pw[0]=1;pwb[0]=1;
    for(rint i=1;i<=B;++i)
        pw[i]=pw[i-1]*2;
    for(rint i=1;i<N;++i)
        pwb[i]=pwb[i-1]*bas%md;
    _pw[0]=1;_pw[1]=qpow(2,B);
    for(rint i=1;i<R;++i)
    	_pw[i]=_pw[i-1]*_pw[1]%md;
    rt[s]=++tot;mx[s]=-1;
}
int main(){
    n=read();m=read();
    for(rint i=1;i<=m;++i){
        int u=read(),v=read();
        int _w=read();
        adbe(u,v,_w);
    }
    s=read();t=read();
    init();Dijkstra();
    printf("%lld\n",ans);
    if(ans==-1)return 0;
    printf("%d\n",cnt);
    for(rint i=cnt;i>=1;--i)
        printf("%d ",rd[i]);
    return 0;
}
```



---

## 作者：bztMinamoto (赞：12)

话说居然没人发题解……赶紧水一发

先打一发广告[blog](https://www.cnblogs.com/bztMinamoto/p/9404175.html)

跑一边dijstra大家应该都想的到

但问题是维护最短路的距离怎么实现

~~我太菜了除了python啥都想不到~~

我们可以把距离拆成每一位，因为每一次只会加上一个数，直接开主席树维护就好了

时间复杂度什么的……感性理解一下就好了

比较大小直接二分哈希
```
//minamoto
#include<bits/stdc++.h>
using namespace std;
#define getc() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
char buf[1<<21],*p1=buf,*p2=buf;
template<class T>inline bool cmax(T&a,const T&b){return a<b?a=b,1:0;}
inline int read(){
    #define num ch-'0'
    char ch;bool flag=0;int res;
    while(!isdigit(ch=getc()))
    (ch=='-')&&(flag=true);
    for(res=num;isdigit(ch=getc());res=res*10+num);
    (flag)&&(res=-res);
    #undef num
    return res;
}
const int N=1e5+5,mod=1e9+7;
int n,m,head[N],Next[N<<1],ver[N<<1],edge[N<<1];
int S,T,lim,b[N<<1],rt[N],Pre[N],tot,cnt;
int L[N*120],R[N*120],sum[N*120];
inline void add(int u,int v,int e){
    ver[++tot]=v,Next[tot]=head[u],head[u]=tot,edge[tot]=e;
    ver[++tot]=u,Next[tot]=head[v],head[v]=tot,edge[tot]=e;
}
bool cmp(int u,int v,int l,int r){
    if(l==r) return sum[u]>sum[v];
    int mid=(l+r)>>1;
    if(sum[R[u]]==sum[R[v]]) return cmp(L[u],L[v],l,mid);
    else return cmp(R[u],R[v],mid+1,r);
}
int update(int last,int &now,int l,int r,int k){
    L[now=++cnt]=L[last],R[now]=R[last];
    if(l==r){
        sum[now]=sum[last]^1;
        return sum[last];
        //每一个节点存的只有一位，如果加之前是1就要进位 
    }
    int mid=(l+r)>>1,res;
    if(k>mid) res=update(R[last],R[now],mid+1,r,k);
    else{
        res=update(L[last],L[now],l,mid,k);
        if(res) res=update(R[last],R[now],mid+1,r,k);
    }
    sum[now]=(1ll*sum[R[now]]*b[mid-l+1]+sum[L[now]])%mod;
    return res;
}
struct node{
    int x,rt;
    bool operator <(const node &b)const
    {return cmp(rt,b.rt,0,lim);}
};
priority_queue<node> q;
void dfs(int u,int dep){
    if(u==S){printf("%d\n%d ",dep,u);return;}
    dfs(Pre[u],dep+1);
    printf("%d ",u);
}
void print(int u){
    printf("%d\n",sum[rt[u]]);
    dfs(u,1);exit(0);
}
int main(){
    //freopen("testdata.in","r",stdin);
    n=read(),m=read();
    for(int i=1;i<=m;++i){
        int u,v,e;
        u=read(),v=read(),e=read();
        add(u,v,e);
        cmax(lim,e);
    }
    lim+=100;
    b[0]=1;for(int i=1;i<=lim;++i) b[i]=(1ll*b[i-1]<<1)%mod;
    S=read(),T=read();
    q.push((node){S,rt[S]});
    while(!q.empty()){
        node u=q.top();q.pop();
        if(u.rt!=rt[u.x]) continue;
        //如果不一样，说明已经在主席树上被修改了
        //就给普通的判dijkstra一样就好了 
        if(u.x==T) print(T);
        for(int i=head[u.x];i;i=Next[i]){
            int v=ver[i],RT;
            update(u.rt,RT,0,lim,edge[i]);
            if(!rt[v]||cmp(rt[v],RT,0,lim))
            rt[v]=RT,q.push((node){v,rt[v]}),Pre[v]=u.x;
        }
    }
    puts("-1");
    return 0;
}
```

---

## 作者：abruce (赞：8)

挺有意思的一道题，结合的很巧妙。  
首先这个题让我们求 $s$ 到 $t$ 的最短路，肯定是要用一个 dijkstra 来跑出来的。但这道题的边权非常大，而且如果用高精度的话要超时，我们考虑怎么优化这个存储和转移。  
由于边权都是 $2$ 的若干次方，我们可以考虑用一个线段树去存储。但是这样空间很明显是会爆的，所以我们用一棵可持久化线段树去存储。这样，在转移的时候我们就可以继承从而省下很多空间。  
存储的问题解决了，现在我们来解决 dijkstra 中的核心：比较和转移。  
### 1.比较  
我们有两棵线段树，里面存储了路径长度，该如何比较呢？  
想到平常的字符串比较怎么做？可以二分哈希。在这里也是一样，我们在线段树上每个节点维护一个哈希值，然后在线段树上面二分找到最长公共前缀。比较最长公共前缀的下一位就是答案。  
### 2.转移  
在普通的 dijkstra 中，转移是类似于 `d[j]=d[u]+e[i].v`。在这里我们相当于是执行二进制下的加法。  
二进制加法会产生进位，这个看似不好维护。但是 `e[i].v` 是 $2$ 的若干次方，也就是说，进位只会取出极长的一段 $1$，把它们赋值成 $0$，然后将下一位置成 $1$。  
这样就好办了，我们用线段树二分取出极长的一段 $1$，然后区间赋 $0$，单点赋 $1$，这些线段树都可以支持。于是这题就做完了。  

在实际实现中，由于取出极长的一段 $1$ 不好写。我用了二分+线段树维护，但不影响 $O(n\log ^2n)$ 的复杂度。  

```cpp
#include<bits/stdc++.h>
#define lc(x) t[x].c[0]
#define rc(x) t[x].c[1]
using namespace std;
const int maxn=1e5+114,mod=1e9+7;
typedef long long ll;
inline int read() {
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9')c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x;
}
struct tree {
	int c[2];
	bool pd;
	ll sum,has;
} t[maxn*200];
struct edge {
	int next,to,v;
} e[maxn*2];
int rt[maxn],n,m,cnt,tot,mx,pre[maxn],zc[maxn],zcnt,h[maxn],S,T;
ll pw[maxn],pw2[maxn];
bool vis[maxn];
void addedge(int x,int y,int z) {
	e[++tot].next=h[x];
	e[tot].to=y;
	e[tot].v=z;
	h[x]=tot;
}
void dfscout(int id,int l,int r) {
	if(l==r)return cout<<t[id].pd,void();
	int mid=l+r>>1;
	dfscout(rc(id),mid+1,r),dfscout(lc(id),l,mid);
}
void pushup(int id) {
	t[id].pd=t[lc(id)].pd&t[rc(id)].pd;//pd：区间是否全为1
	t[id].sum=(t[lc(id)].sum+t[rc(id)].sum)%mod;//区间实际和
	t[id].has=(t[lc(id)].has+t[rc(id)].has)%mod;//区间哈希值
}
void build(int &id,int l,int r,int v) {
	id=++cnt;
	if(l==r)return t[id].sum=pw[l]*v,t[id].has=pw2[l]*v,t[id].pd=v,void();
	int mid=l+r>>1;
	build(lc(id),l,mid,v),build(rc(id),mid+1,r,v);
	pushup(id);//建一棵全0/全1树
}
bool ask(int id,int l,int r,int L,int R) {
	if(!id)return 0;
	if(l>=L&&r<=R)return t[id].pd;
	int mid=l+r>>1;
	bool sum=1;
	if(L<=mid)sum&=ask(lc(id),l,mid,L,R);
	if(R>mid)sum&=ask(rc(id),mid+1,r,L,R);
	return sum;//询问是否全为1
}
void clear(int &id,int o,int l,int r,int L,int R) {
	id=++cnt,t[id]=t[o];
	if(l>=L&&r<=R)return id=0,void();//因为赋值的是0，所以可以丢掉儿子，不用标记永久化
	int mid=l+r>>1;
	if(L<=mid)clear(lc(id),lc(o),l,mid,L,R);
	if(R>mid)clear(rc(id),rc(o),mid+1,r,L,R);
	pushup(id);//区间赋值0
}
void add(int &id,int o,int l,int r,int v) {
	id=++cnt,t[id]=t[o];
	if(l==r)return t[id].sum=pw[l],t[id].has=pw2[l],t[id].pd=1,void();
	int mid=l+r>>1;
	v<=mid?add(lc(id),lc(o),l,mid,v):add(rc(id),rc(o),mid+1,r,v);
	pushup(id);//单点赋值1
}
void addone(int i,int v) {
	int l=v,r=mx,now=v-1;
	while(l<=r) {
		int mid=l+r>>1;
		if(ask(rt[i],0,mx,v,mid))now=mid,l=mid+1;
		else r=mid-1;//二分极长段
	}
	rt[n+1]=rt[i];
	if(v<=now)clear(rt[n+1],rt[n+1],0,mx,v,now);
	add(rt[n+1],rt[n+1],0,mx,now+1);
}
bool cmp(int a,int b,int l,int r) {
	if(l==r)return t[a].pd>t[b].pd;
	int mid=l+r>>1;
	return t[rc(a)].sum!=t[rc(b)].sum&&t[rc(a)].has!=t[rc(b)].has?cmp(rc(a),rc(b),mid+1,r):cmp(lc(a),lc(b),l,mid);//判断大小
}
struct que {
	int id,v;
	que(int i,int V) {
		id=i,v=V;
	}
	friend bool operator<(que a,que b) {
		return cmp(a.v,b.v,0,mx);//一定要用那个时候的根来比较，否则会导致push不上来！ 
	}
};
priority_queue<que> q;
void dijkstra() {
	build(rt[S],0,mx,0);
	build(rt[0],0,mx,1);
	for(register int i=1; i<=n; i++)if(i!=S)rt[i]=rt[0];
	q.push(que(S,rt[S]));
	while(!q.empty()) {
		int u=q.top().id;
		q.pop();
		if(vis[u])continue;
		vis[u]=1;
		if(u==T)break;
		for(register int i=h[u]; i; i=e[i].next) {
			int j=e[i].to;//用一个临时版本n+1来比较
			addone(u,e[i].v);
			if(cmp(rt[j],rt[n+1],0,mx)) {
				rt[j]=rt[n+1],pre[j]=u;
				if(!vis[j])q.push(que(j,rt[j]));
			}
		}
	}
}
int main() {
	int x,y,z;
	n=read(),m=read();
	for(register int i=1; i<=m; i++) {
		x=read(),y=read(),mx=max(mx,z=read());
		addedge(x,y,z);
		addedge(y,x,z);
	}
	S=read(),T=read();
	mx+=22,pw[0]=pw2[0]=1;
	for(register int i=1; i<=mx; i++)pw[i]=pw[i-1]*2%mod,pw2[i]=pw2[i-1]*114%mod;
	dijkstra();
	if(t[rt[T]].pd) {
		puts("-1");
		return 0;
	}
	printf("%lld\n",t[rt[T]].sum);
	zc[zcnt=1]=T;
	while(T!=S)T=pre[T],zc[++zcnt]=T;
	printf("%d\n",zcnt);
	for(register int i=zcnt; i; i--)printf("%d%c",zc[i]," \n"[i==1]);//倒推方案
	return 0;
}
```

---

## 作者：Mobius127 (赞：7)

~~简直做得爽炸了~~

[题传](https://www.luogu.com.cn/problem/CF464E)

以下令 $n, m, w$ 同阶。

边权恒正，显然使用 dijkstra，现在要解决高精的问题，我们需要支持的操作有：高精加 与 比较大小。

比较肯定不能 $O(n)$ 比，考虑上哈希+二分，这样就能做到比较复杂度 $O(\log n)$。

注意到加法操作是在二进制下单点加，所以只会出现以下两种情况：

1. 原来的二进制串第 $w$ 位为 0，修改成 1 即可；

1. 原来的二进制串第 $w$ 位为 1，需要进位，但也有可能产生连续地进位，需要找到从 $w$ 位开始的极长 1 连续段，全部赋为 0，再把前一位改为 1。

考虑到加了之后还要维护一个哈希值，且修改的是一段区间，上线段树维护，对于每一个值上都放上一个线段树，但这样空间太大吃不消。

又想到我们是在一个原来的值上面修改，那么把线段树可持久化，改成主席树即可。

复杂度 $O(n \log^2 n)$。

### Code：

```cpp
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cctype>
#include <stdlib.h>
#include <queue>
using namespace std;
typedef long long ll;
const int INF=0x3f3f3f3f;
const unsigned int P=19260817;
const int mo=1e9+7;
inline int read(){
	char ch=getchar();int x=0, f=1;
	while(!isdigit(ch)){if(ch=='-') f=-1; ch=getchar();}
	while(isdigit(ch)){x=(x<<3)+(x<<1)+ch-'0';ch=getchar();}
	return x*f;
}
inline void write(int x){
    if(x<0) putchar('-'), x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
inline int ksm(int a, int b){
	int ret=1;
	for(; b; b>>=1, a=1ll*a*a%mo)
		if(b&1) ret=1ll*ret*a%mo;
	return ret;
}
const int N=1e5+50;
const int S=100020;
unsigned int H[S+5];
int n, m, pre[N], msk[S+5], cnt, root[N];
#define ls d[k].lc
#define rs d[k].rc
#define mid (l+r>>1) 
struct Node{int lc, rc, cnt1;unsigned int hsah;}d[N*100];
inline void pushup(int k, int len){
	d[k].cnt1=d[ls].cnt1&d[rs].cnt1;
	d[k].hsah=d[ls].hsah+d[rs].hsah*H[len];
}
inline void build(int &k, int l, int r, int v){
	k=++cnt;
	if(l==r){d[k].hsah=d[k].cnt1=v;return ;} 
	build(ls, l, mid, v);build(rs, mid+1, r, v);
	pushup(k, mid-l+1);
}
int cmb(int a, int b){return a==b?0:(a<b?-1:1);}
inline int CMP(int p, int q, int l, int r){
	if(l==r) return cmb(d[p].hsah, d[q].hsah);
	if(d[d[p].rc].hsah!=d[d[q].rc].hsah) return CMP(d[p].rc, d[q].rc, mid+1, r);
	else return CMP(d[p].lc, d[q].lc, l, mid);
}
inline int find(int k, int l, int r){//找到这一段内最右的（因为线段树上的串是反过来的） 
	if(d[k].cnt1) return r;
	if(l==r) return -1;
	int L=find(ls, l, mid), R=-1;
	if(L==mid) R=find(rs, mid+1, r);
	return max(L, R);
}
inline int position(int k, int l, int r, int x){
	if(x<=l) return find(k, l, r);int L=-1, R=-1;
	if(x<=mid){
		L=position(ls, l, mid, x);
		if(L==mid) R=position(rs, mid+1, r, x);
		return max(L, R);
	}
	else return position(rs, mid+1, r, x);
}
inline void change(int &k, int X, int Y, int l, int r, int x, int y){
	if(x<=l&&r<=y){k=Y;return ;}
	k=++cnt;d[k]=d[X];
	if(x<=mid) change(ls, d[X].lc, d[Y].lc, l, mid, x, y);
	if(mid<y) change(rs, d[X].rc, d[Y].rc, mid+1, r, x, y);
	return pushup(k, mid-l+1);
}
inline void modify(int &k, int pre, int l, int r, int x){
	k=++cnt;;d[k]=d[pre];if(l==r){d[k].cnt1=d[k].hsah=1;return ;}
	if(x<=mid) modify(ls, d[pre].lc, l, mid, x);
	else modify(rs, d[pre].rc, mid+1, r, x);
	return pushup(k, mid-l+1);
}
int Add(int rt, int v){
	int pos=position(rt, 0, S, v);
	int ret=rt;
	if(pos<0) pos=v-1;
	else change(ret, rt, root[0], 0, S, v, pos);
	int ans;modify(ans, ret, 0, S, pos+1);
	return ans;
}
#undef ls
#undef rs
#undef mid
int h[N], tot, dis[N];
bool vis[N]; 
deque <int> ans;
struct Edge{int to, nxt, w;}e[N*2];
void add(int x, int y, int z){e[++tot]=(Edge){y, h[x], z};h[x]=tot;}
struct data{
	int x, id;
	bool operator < (const data &X) const{return CMP(id, X.id, 1, S)>0;}
};
void dij(){
	build(root[0], 0, S, 0), build(root[n+1], 0, S, 1);
	int s=read(), t=read();root[s]=root[0];
	priority_queue <data> Q;Q.push((data){s, root[s]});dis[s]=0;
	for(int i=1; i<=n; i++)
		if(i!=s) root[i]=root[n+1];
	while(!Q.empty()){
		data pos=Q.top();Q.pop();
		int x=pos.x, id=pos.id;
		if(vis[x]) continue;vis[x]=1;
		for(int i=h[x], v, w; i; i=e[i].nxt){
			v=e[i].to, w=e[i].w;
			int newrt=Add(id, w);
			if(CMP(newrt, root[v], 0, S)<0){
//				puts("Acepet");
				dis[v]=(dis[x]+msk[w])%mo;
				root[v]=newrt, pre[v]=x;
				Q.push((data){v, root[v]});
			}
		}
	}
	if(vis[t]){
		printf("%d\n", dis[t]);
		while(t!=s) ans.push_back(t), t=pre[t];ans.push_back(s);
		printf("%d\n", ans.size());
		while(!ans.empty()) printf("%d ", ans.back()), ans.pop_back();
		return ;
	}
	puts("-1");
}
signed main(){
	n=read(), m=read();
	for(int i=1, x, y, z; i<=m; i++)
		x=read(), y=read(), z=read(),
		add(x, y, z), add(y, x, z);
	msk[0]=1, H[0]=1;
	for(int i=1; i<=S; i++)
		msk[i]=1ll*msk[i-1]*2%mo,
		H[i]=H[i-1]*P;
	dij();
	return 0;
}

```


---

## 作者：Kewth (赞：6)

**真 - 题解**  
亲测可以通过讨论区提到的 Hack 数据。

这是道主席树 + Hash 神仙题。

直观的想法是高精套 dijkstra 。  
如果用高精，需要用到 + 和 < 运算，复杂度均为 $ O(x) $，  
总复杂度 $O(m x log(n)) $  

有个特殊的地方：边的权值都是 2 的整次幂。  
那么用二进制表示权值的话， + 运算只会加一位。  
考虑用可持久化线段树维护这个高精度，  
- '+' 运算二分找到一段最长的连续 1 区间修改为 0 再把一个 0 变成 1 。  
- '<' 运算二分哈希值找到 lcs 再判断第一个不同的位（类似于哈希比较字符串大小）。  

每个运算的复杂度都是 $ O(log^2) $  
不对啊，套上 dijkstra 总复杂度有三个 log ，  
事实上 < 运算可以利用线段数的结构直接在线段树里面递归（二分），一个 log 。  
而 + 运算只会用到 O(m) 次，因此总复杂度 $ O(m log(n) log(x) + m log^2(x)) $ 。

```cpp
#include <bits/stdc++.h>

typedef unsigned long long Hash;

Hash power(Hash x, int k) {
	Hash res = 1;
	while(k) {
		if(k & 1) res *= x;
		x *= x;
		k >>= 1;
	}
	return res;
}

class Tree {
private:
	int L, R, sum;
	bool fuck_memory[4];
	Hash hash, Rpow; // 需要预处理 Rpow, 否则复杂度会多一个 log
	Tree *lt, *rt;
	void update() {
		sum = lt -> sum + rt -> sum;
		hash = lt -> hash * Rpow + rt -> hash;
	}
	void get_son() {
		int mid = (L + R) >> 1;
		if(lt == null) lt = new Tree(L, mid);
		if(rt == null) rt = new Tree(mid + 1, R);
	}
public:
	static Tree *const null;
	Tree *lain(int p) {
		Tree *node = new Tree(*this);
		if(L == R) {
			node -> sum ++;
			node -> hash ++;
			return node;
		}
		int mid = (L + R) >> 1;
		get_son();
		if(p <= mid)
			node -> lt = lt -> lain(p);
		else
			node -> rt = rt -> lain(p);
		node -> update();
		return node;
	}
	Tree *clear(int l, int r) {
		if(r < L or l > R) return this;
		Tree *node = new Tree(*this);
		if(l <= L and R <= r) {
			node -> sum = 0;
			node -> hash = 0;
			node -> lt = node -> rt = null;
			return node;
		}
		get_son();
		node -> lt = lt -> clear(l, r);
		node -> rt = rt -> clear(l, r);
		node -> update();
		return node;
	}
	int query_sum(int l, int r) {
		if(not sum or r < L or l > R) return 0;
		if(l <= L and R <= r) return sum;
		return lt -> query_sum(l, r) + rt -> query_sum(l, r);
	}
	static int cmp(Tree *a, Tree *b) {
		if(a -> hash == b -> hash) return 0;
		if(not a -> sum) return -1;
		if(not b -> sum) return 1;
		if(a -> L == b -> R)
			return a -> sum < b -> sum ? -1 : 1;
		int rres = cmp(a -> rt, b -> rt);
		if(rres) return rres;
		return cmp(a -> lt, b -> lt);
	}
	Tree(int l, int r): L(l), R(r), sum(0), hash(0), lt(null), rt(null) {
		Rpow = power(3, R - ((L + R) >> 1));
	}
	Tree(): L(-1), R(-1), sum(0), hash(0), lt(nullptr), rt(nullptr) { }
};
Tree *const Tree::null = new Tree();

const int maxn = 100050, maxv = 100100; // maxv 的值开小会 wei
class Value {
private:
	Tree *T;
public:
	bool operator < (Value an) const {
		return Tree::cmp(T, an.T) == -1;
	}
	Value operator + (int k) {
		int l = k, r = maxv;
		while(l < r) {
			int mid = (l + r) >> 1;
			if(T -> query_sum(k, mid) == mid - k + 1)
				l = mid + 1;
			else
				r = mid;
		}
		Tree *node = T;
		if(k <= l - 1)
			node = T -> clear(k, l - 1);
		node = node -> lain(l);
		return Value(node);
	}
	bool empty() { return T == Tree::null; }
	void init() {
		T = new Tree(0, maxv);
	}
	int fuck_ans() {
		int ans = 0, pp = 1, mod = 1000000007;
		for(int i = 0; i <= maxv; i ++) {
			if(T -> query_sum(i, i))
				(ans += pp) %= mod;
			(pp <<= 1) %= mod;
		}
		return ans;
	}
	Value(Tree *T = Tree::null): T(T) { }
};

struct Edge {
	int to, val;
	Edge(int to, int val): to(to), val(val) { }
};
Value dist[maxn];
int last[maxn];
bool vis[maxn];
std::vector<Edge> G[maxn];

void dijk(int s) {
	typedef std::pair<Value, int> par;
	std::priority_queue<par, std::vector<par>, std::greater<par>> q;
	dist[s].init();
	q.push(par(dist[s], s));
	while(not q.empty()) {
		int u = q.top().second;
		q.pop();
		if(vis[u]) continue;
		vis[u] = true;
		for(Edge &e : G[u])
			if(not vis[e.to]) {
				Value d = dist[u] + e.val;
				if(dist[e.to].empty() or d < dist[e.to]) {
					dist[e.to] = d;
					last[e.to] = u;
					q.push(par(d, e.to));
				}
			}
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	int n, m;
	std::cin >> n >> m;
	for(int i = 1; i <= m; i ++) {
		int u, v, w;
		std::cin >> u >> v >> w;
		G[u].push_back(Edge(v, w));
		G[v].push_back(Edge(u, w));
	}
	int s, t;
	std::cin >> s >> t;
	dijk(s);
	std::vector<int> path;
	for(int u = t; u; u = last[u])
		path.push_back(u);
	if(path[path.size() - 1] == s) {
		std::cout << dist[t].fuck_ans() << std::endl;
		std::cout << path.size() << std::endl;
		for(size_t i = path.size() - 1; i; i --)
			std::cout << path[i] << ' ';
		std::cout << path[0] << std::endl;
	} else {
		std::cout << -1 << std::endl;
	}
}
```

---

## 作者：xfrvq (赞：5)

[$\tt Link$](/problem/CF464E)。

下面的讨论默认 $n,m,x_i$ 同阶。

这个问题与常规 $\tt dij$，仅仅差在高精度。而 $\tt dij$ 所需的高精度如下：

+ $dis_u+w(u,v)$ 中的加法，应该有 $m$ 次。
+ $dis_u+w(u,v)$ 与 $dis_v$ 的比较，应该有 $m\log$ 次。

考虑数据结构维护 $dis$ 的二进制分解。直接维护空间是 $\mathcal O(nx)$ 的，但是 $dis$ 之间互相转移、取 $\min$，必然有很多位是相同的，于是考虑主席树。

对于加法，
1. 找到当前位置之前的连续 $1$ 总数，这一步可以线段树上二分
2. 将这一部分 $1$ 推平为 $0$，这一部分可以先维护好一棵全 $0$ 的线段树，然后使用其中节点替换原主席树的节点即可。
3. 在更前一位添加 $1$，这一部分直接单点修改。

对于比较，
+ 同时两个指针遍历两棵线段树
+ 如果左子树不同，那么比较左子树，否则比较右子树
+ 判断两个子树是否相同，可以维护子树哈希值

```cpp
#include<bits/stdc++.h>
using namespace std;
 
#define rep(i,a,b) for(int i = (a);i <= (b);++i)
 
using hsh = unsigned long long;
 
const int N = 1e5 + 5;
const int S = N * 60;
const hsh mod = 1e9 + 7;
const int X = 1e5 + 50;
 
int n,m,s,t,rt[N],pre[N],dis[N]; bool vis[N];
vector<pair<int,int> > G[N];
hsh pow2[X + 10]; int fa[N],XX;
 
int lc[S],rc[S],cc; hsh w[S]; bool i1[S];
 
#define mid ((L + R) >> 1)
#define ls lc[i],L,mid
#define rs rc[i],mid + 1,R
 
void psu(int i,int L,int R){
	i1[i] = i1[lc[i]] && i1[rc[i]];
	w[i] = (w[rc[i]] * pow2[mid - L + 1] % mod + w[lc[i]]) % mod;
}
 
void build(int &i,int L,int R,int x){
	i = ++cc;
	if(L == R) return void(i1[i] = w[i] = x);
	build(ls,x); build(rs,x); psu(i,L,R);
}
 
bool cmp(int i,int j,int L,int R){
	if(L == R) return w[i] > w[j];
	return w[rc[i]] == w[rc[j]] ? cmp(lc[i],lc[j],L,mid) : cmp(rc[i],rc[j],mid + 1,R);
}
 
int fnd(int i,int L,int R){
	if(i1[i]) return R; if(L == R) return -1;
	int _ = fnd(ls); return _ == mid ? max(fnd(rs),mid) : _;
}
 
int pos(int i,int L,int R,int p){
	if(p <= L) return fnd(i,L,R);
	if(p > mid) return pos(rs,p);
	int _ = pos(ls,p); return _ == mid ? max(mid,pos(rs,p)) : _;
}
 
struct node{
	int u,r;
	node(int u = 0,int r = 0) : u(u),r(r){}
	bool operator<(const node &p) const { return cmp(r,p.r,0,XX); }
};
 
void chg(int &p,int i,int j,int L,int R,int l,int r){
	if(l <= L && R <= r) return void(p = j);
	p = ++cc; rc[p] = rc[i]; lc[p] = lc[i]; i1[p] = i1[i]; w[p] = w[i];
	if(l <= mid) chg(lc[p],lc[i],lc[j],L,mid,l,r);
	if(r > mid) chg(rc[p],rc[i],rc[j],mid + 1,R,l,r);
	psu(p,L,R);
}
 
void upd(int &p,int i,int L,int R,int x){
	p = ++cc; rc[p] = rc[i]; lc[p] = lc[i]; i1[p] = i1[i]; w[p] = w[i];
	if(L == R) return void(i1[p] = w[p] = 1);
	x <= mid ? upd(lc[p],ls,x) : upd(rc[p],rs,x);
	psu(p,L,R);
}
 
int pls(int rt,int v){
	int p = pos(rt,0,XX,v),RT = rt;
	if(p < 0) p = v - 1; else chg(RT,rt,::rt[0],0,XX,v,p);
	int ret; upd(ret,RT,0,XX,p + 1); return ret;
}
 
priority_queue<node> Q;
 
void dij(){
	build(rt[0],0,XX,0);
	build(rt[n + 1],0,XX,1);
	rep(i,1,n) rt[i] = rt[n + 1];
	Q.emplace(s,rt[s] = rt[0]);
	while(!Q.empty()){
		int u = Q.top().u,r = Q.top().r; Q.pop();
		if(vis[u]) continue; vis[u] = 1;
		if(u == t) return;
		for(auto e : G[u]){
			int v = e.first,w = e.second;
			int RT = pls(r,w);
			if(cmp(rt[v],RT,0,XX)){
				Q.emplace(v,rt[v] = RT),pre[v] = u;
				dis[v] = (dis[u] + pow2[w]) % mod;
			}
		}
	}
}
 
void print(){
	printf("%d\n",dis[t]);
	deque<int> P;
	while(t != s) P.push_front(t),t = pre[t];
	P.push_front(s);
	printf("%d\n",P.size());
	for(int x : P) printf("%d ",x); printf("\n");
}
 
int fnd(int i){ return i == fa[i] ? i : fa[i] = fnd(fa[i]); }
 
int main(){
	scanf("%d%d",&n,&m);
	rep(i,1,n) fa[i] = i;
	rep(i,1,m){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		fa[fnd(u)] = fnd(v);
		G[u].emplace_back(v,w);
		G[v].emplace_back(u,w);
		XX = max(XX,w);
	}
	scanf("%d%d",&s,&t);
	if(fnd(s) != fnd(t)) return printf("-1\n"),0;
	pow2[0] = 1; XX += 25;
	rep(i,1,XX + 2) pow2[i] = (pow2[i - 1] * 2) % mod;
	dij(); print();
	return 0;
}
```

---

## 作者：orz_z (赞：4)

### CF464E The Classic Problem
最短路，显然不具备单 $\log$ 做法，考虑维护高精二进制数，支持单点加一。

显然高精不行，维护二进制数的 `trie` 较为复杂，考虑本质相同的值域线段树。

支持比较大小、区间赋零和单点赋一操作。

分别想，比较大小，即维护区间哈希值，先比较高位大小是否相同，若相等递归低位；否则递归高位判断。

对于区间赋零，永久化标记过于麻烦，找到对应的 $\log$ 个区间，接上提前预处理好的全零子树即可。

对于单点赋一，板子不讲。

最后考虑空间问题，回顾最短路算法松弛，$dis_v$ 会用到 $dis_u$ 绝大部分值，可持久化一下即可。

时间复杂度 $\mathcal O(n\log^2 n)$。

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define ha putchar(' ')
#define he putchar('\n')
inline int read()
{
	int x = 0;
	char c = getchar();
	while (c < '0' || c > '9')c = getchar();
	while (c >= '0' && c <= '9')
		x = (x << 3) + (x << 1) + (c ^ 48), c = getchar();
	return x;
}
inline void write(int x)
{
	if(x < 0) putchar('-'), x = -x;
	if(x > 9) write(x / 10);
	putchar(x % 10 + 48);
}
#define lc(o) tr[o].lc
#define rc(o) tr[o].rc
#define s(o) tr[o].s
#define si(o) tr[o].si
#define hs(o) tr[o].hs
const int _ = 1e5 + 100, N = 1e5 + 20, mod = 1e9 + 7;
int n, m, s, t, cnt, p2[_], rt[_];
int tot, head[_], to[_ << 1], nxt[_ << 1], w[_ << 1];
bool vis[_]; int zct, zc[_], pre[_];
struct abc
{
	int s, si, lc, rc; ll hs;
} tr[_ * 80];
void add(int u, int v, int d) {to[++tot] = v, nxt[tot] = head[u], w[tot] = d, head[u] = tot;}
void pushup(int o)
{
	s(o) = s(lc(o)) + s(rc(o));
	hs(o) = (p2[si(lc(o))] * hs(rc(o)) % mod + hs(lc(o))) % mod;
}
void build(int &o, int l, int r)
{
	o = ++cnt, si(o) = r - l + 1;
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(lc(o), l, mid), build(rc(o), mid + 1, r);
	pushup(o);
}
void upd1(int &a, int b, int l, int r, int x)
{
	a = ++cnt, tr[a] = tr[b];
	if(l == r) return s(a)++, hs(a)++, void();
	int mid = (l + r) >> 1;
	x <= mid ? upd1(lc(a), lc(b), l, mid, x) : upd1(rc(a), rc(b), mid + 1, r, x);
	pushup(a);
}
void upd2(int &a, int b, int p0, int l, int r, int L, int R)
{
	if(L <= l && r <= R) return a = p0, void();
	a = ++cnt, tr[a] = tr[b];
	int mid = (l + r) >> 1;
	if(L <= mid) upd2(lc(a), lc(b), lc(p0), l, mid, L, R);
	if(R > mid) upd2(rc(a), rc(b), rc(p0), mid + 1, r, L, R);
	pushup(a);
}
int qry(int o, int l, int r, int L, int R)
{
	if(L <= l && r <= R) return s(o);
	int mid = (l + r) >> 1, ret = 0;
	if(L <= mid) ret = qry(lc(o), l, mid, L, R);
	if(R > mid) ret += qry(rc(o), mid + 1, r, L, R);
	return ret;
}
int find(int o, int l, int r, int x, int c)
{
	if(l == r) return l;
	int mid = (l + r) >> 1;
	if(s(lc(o)) >= mid - x + 1 + c) return find(rc(o), mid + 1, r, x, c - s(lc(o)));
	return find(lc(o), l, mid, x, c);
}
void upd(int &a, int b, int x)
{
	int c = x > 0 ? qry(b, 0, N, 0, x - 1) : 0;
	int y = find(b, 0, N, x, c);
	if(y > x) upd2(a, b, rt[0], 0, N, x, y - 1);
	else a = b;
	upd1(a, a, 0, N, y);
}
bool cmp(int a, int b, int l, int r)
{
	if(l == r) return s(a) > s(b);
	int mid = (l + r) >> 1;
	if(hs(rc(a)) == hs(rc(b))) return cmp(lc(a), lc(b), l, mid);
	return cmp(rc(a), rc(b), mid + 1, r);
}
struct Node
{
	int id, rt;
	bool operator < (const Node &t) const{return cmp(rt, t.rt, 0, N);}
}; priority_queue<Node> q;
void dij(int s)
{
	build(rt[0], 0, N), rt[s] = rt[0];
	q.push({s, rt[s]});
	while(!q.empty())
	{
		int nw = q.top().id;
		q.pop();
		if(vis[nw]) continue;
		vis[nw] = 1;
		if(nw == t) break;
		for(int i = head[nw]; i; i = nxt[i])
		{
			int v = to[i];
			upd(rt[n + 1], rt[nw], w[i]);
			if(!rt[v] || cmp(rt[v], rt[n + 1], 0, N))
			{
				rt[v] = rt[n + 1];
				pre[v] = nw;
				if(!vis[v]) q.push({v, rt[v]});
			}
		}
	}
}

signed main()
{
	p2[0] = 1; for(int i = 1; i < N; ++i) p2[i] = p2[i - 1] * 2ll % mod;
	n = read(), m = read();
	for(int i = 1, u, v, w; i <= m; ++i)
	{
		u = read(), v = read(), w = read();
		add(u, v, w), add(v, u, w);
	}
	s = read(), t = read();
	dij(s);
	if(!vis[t]) return write(-1), he, 0;
	write(hs(rt[t])), he;
	zc[zct = 1] = t;
	while(t != s)
	{
		t = pre[t];
		zc[++zct] = t;
	}
	write(zct), he;
	for(int i = zct; i >= 1; --i)
		write(zc[i]), ha;
	return 0;
}
```

---

## 作者：vectorwyx (赞：3)

沿用 dij 的思路，如果直接维护 $01$ 串比较和单点加都是 $O(x)$ 的，无法承受。考虑从高到低在 $01$ 串上建立一棵动态开点的线段树，维护区间哈希值，在线段树上二分就可以做到单次 $O(\log n)$ 比较两个串的大小。而 dij 还要支持一个操作是把 $dis_y$ 与 $dis_x+v$ 比较，后者把单点加可持久化掉，额外维护一个区间所有数是否均为 $1$ 的信息，在线段树上二分，用 $O(\log n)$ 段区间拼出以该点为结尾的极长 $1$ 段，全部清零并把下一个位置变成 $1$，这些都是经典线段树操作。时间复杂度为 $O(m\log^2n+m\log n)$。

顺带一提这题还有很多阴间数据，比如 $m=0$，$s=t$。

代码如下：
```cpp
//author:望远星 
#include<bits/stdc++.h>
#define pii pair<int,int>
#define fi first
#define se second
#define pb push_back
#define mk make_pair
#define sml(x,y) (x=min(x,y))
#define big(x,y) (x=max(x,y))
#define ll long long
#define ull unsigned long long
#define db double
#define fo(i,x,y) for(int i=x;i<=y;++i)
#define go(i,x,y) for(int i=x;i>=y;--i)
using namespace std;
ull seed=chrono::system_clock::now().time_since_epoch().count();
mt19937 rnd(seed);
inline int rm(int x,int y){return rnd()%(y-x+1)+x;}
inline int read(){ int x=0,f=1; unsigned char ch=getchar()-48; while(ch>9){ if(ch==253) f=-1; ch=getchar()-48; } while(ch<=9){ x=x*10+ch; ch=getchar()-48; } return x*f; }
inline void out(int *a,int l,int r){fo(i,l,r) cout<<*(a+i)<<' ';puts("");}

const int N=1.1e5+5,base1=3,base2=29,mod1=1e9+7,mod2=998244353;
struct Edge{
	int to,next,val;
}e[N<<1];
int pw1[N],pw2[N],n,m,head[N],tot,root[N],V,num;

void connect(int x,int y,int v){
	e[++tot]=(Edge){y,head[x],v};
	head[x]=tot; 
}

struct Node{
	int lt,rt,hx1,hx2,tag,ok;
	Node(){lt=rt=hx1=hx2=tag=ok=0;}
	void rep(){hx1=hx2=ok=0;tag=1;}
	void outit(){printf("%d,%d hx1=%d hx2=%d tag=%d ok=%d\n",lt,rt,hx1,hx2,tag,ok);} 
}tree[N*100];

#define ls(x) tree[x].lt
#define rs(x) tree[x].rt
void push_up(int x,int l,int r){
	tree[x].ok=tree[ls(x)].ok&tree[rs(x)].ok;
	int mid=(l+r)>>1;
	tree[x].hx1=(tree[ls(x)].hx1+1ll*tree[rs(x)].hx1*pw1[mid-l+1])%mod1;
	tree[x].hx2=(tree[ls(x)].hx2+1ll*tree[rs(x)].hx2*pw2[mid-l+1])%mod2;
}

void push_down(int x){
	if(!tree[x].tag||!x) return;
	tree[++num]=tree[ls(x)];ls(x)=num;
	tree[++num]=tree[rs(x)];rs(x)=num;
	tree[ls(x)].rep();tree[rs(x)].rep();
	tree[x].tag=0;
}

struct cmp{
	bool operator()(int x,int y)const{
		int l=1,r=V;
		x=root[x],y=root[y];
		if(tree[x].hx1==tree[y].hx1&&tree[x].hx2==tree[y].hx2) return x<y;
		while(l<r){
			push_down(x),push_down(y);
			if(tree[rs(x)].hx1!=tree[rs(y)].hx1||tree[rs(x)].hx2!=tree[rs(y)].hx2){
				x=rs(x),y=rs(y);
				l=(l+r)/2+1;
			}else x=ls(x),y=ls(y),r=(l+r)>>1;
		}
		return tree[x].hx1<tree[y].hx1;
	}
}A;
//注意在这里是对 [1,V] 建线段树 

void modify(int &x,int l,int r,int aim,int &y){//把 aim 改成 1 
	//printf("modify(%d,%d,%d,%d,%d)\n",x,l,r,aim,y);
	y=++num;tree[y]=tree[x];
	if(l==r){
		tree[y].hx1=tree[y].hx2=tree[y].ok=1;
		return;
	}
	push_down(x),push_down(y);
	int mid=(l+r)>>1;
	if(aim<=mid) modify(ls(x),l,mid,aim,ls(y));
	else modify(rs(x),mid+1,r,aim,rs(y));
	push_up(y,l,r);
}

int solve(int x,int l,int r,int L){
	if(!x) return max(l,L);
	if(tree[x].ok) return r+1;
	if(l==r) return l;
	push_down(x);
	int mid=(l+r)>>1;
	if(L<=mid){
		int R=solve(ls(x),l,mid,L);
		if(R<=mid) return R;
		return solve(rs(x),mid+1,r,L);
	}else return solve(rs(x),mid+1,r,L);
}

void update(int &x,int l,int r,int L,int R){
	//if(!x) x=++num;
	tree[++num]=tree[x];x=num;
	//printf("update(%d,%d,%d,%d,%d)\n",x,l,r,L,R);
	if(l>=L&&r<=R){
		//tree[++num]=tree[x];
		//可持久化，即使在原版本上改也需要新建结点，不然会影响其他共享该结点的版本 
		//x=num;
		//printf("real upd is %d\n",x);
		tree[x].rep();
		return;
	}
	push_down(x);
	int mid=(l+r)>>1;
	if(L<=mid) update(ls(x),l,mid,L,R);
	if(R>mid) update(rs(x),mid+1,r,L,R);
	push_up(x,l,r);
}

int mi[N],ans,pre[N];

void dfs(int x,int l,int r){
	//printf("dfs(%d,%d,%d)\n",x,l,r);
	if(l==r){
		//printf("v=%d %d\n",tree[x].hx1,tree[x].ok);
		ans=(ans+1ll*tree[x].hx1*mi[l-1])%mod1;
		return;
	}
	push_down(x);
	int mid=(l+r)>>1;
	dfs(ls(x),l,mid);
	dfs(rs(x),mid+1,r);
}

int dlt[N];

void outit(){
	out(root,1,n);
	fo(i,1,num) cout<<i<<':',tree[i].outit();
}

signed main(){
	cin>>n>>m;
	fo(i,1,m){
		int x=read(),y=read(),v=read()+1;
		connect(x,y,v);
		connect(y,x,v);
		big(V,v);
	}
	if(m) V+=ceil(log2(m)+3);
	else V+=3;
	pw1[0]=pw2[0]=1;fo(i,1,V) pw1[i]=1ll*pw1[i-1]*base1%mod1,pw2[i]=1ll*pw2[i-1]*base2%mod2;
	mi[0]=1;fo(i,1,V) mi[i]=(mi[i-1]<<1)%mod1;
	set<int,cmp> q;
	int s=read(),t=read();
	if(s==t){
		printf("0\n1\n%d\n",s);
		return 0;
	}
	root[s]=++num;q.insert(s);
	fo(i,1,n) if(i!=s) modify(root[s],1,V,V,root[i]);
	//outit();
	while(!q.empty()){
		int x=*(q.begin());q.erase(q.begin());
		if(dlt[x]) continue;
		dlt[x]=1;
		for(int i=head[x];i;i=e[i].next){
			int p=e[i].to;
			if(dlt[p]) continue;
			int R=solve(root[x],1,V,e[i].val),y=0;
			//printf("%d->%d [%d,%d]\n",x,p,e[i].val,R);
			modify(root[x],1,V,R,y);
			//printf("y=%d\n",y);
			if(R>e[i].val) update(y,1,V,e[i].val,R-1);
			root[n+1]=y;
			if(A(n+1,p)) q.erase(p),root[p]=y,q.insert(p),pre[p]=x;//puts("ok"),
			//if(x==2&&p==3) outit();
			//if(x==3&&p==4) outit(); 		
		}
	}
	if(!pre[t]) return puts("-1"),0;
	//outit();
	dfs(root[t],1,V);
	cout<<ans<<'\n';
	vector<int> qaq;
	int x=t;
	while(x){
		qaq.pb(x);
		x=pre[x];
	}
	reverse(qaq.begin(),qaq.end());
	cout<<qaq.size()<<'\n';
	for(auto i:qaq) cout<<i<<' ';
	return 0;
}
/*
4 4
1 4 2
1 2 0
2 3 0
3 4 0
1 4
-------------------------------------------------
3
4
1 2 3 4 
*/

```


---

## 作者：fanypcd (赞：2)

最短路，但是边长是 2 的幂次。

如果硬写高精度肯定超时，又因为转移是一个二进制数只在某一位 $+1$，所以考虑用主席树的继承思想维护。

---

### 加法：

可能有进位的情况，这个时候就需要找到线段树上第一个比加的数位高且为 $0$ 的位置，可以在每个区间上维护一个是否为全 $1$ 的标记，实现 $\Theta(\log^2 n)$ 的查找。

找到位置后将当前位 $+1$，加法位到当前位之前的区间置为 $0$。

---

### 比较：

暴力逐位比较显然是 $\Theta(n)$ 的，考虑复杂度瓶颈在哪里：从高位到低位找到第一个**不相同**的位置，比较之。

如果能快速确定两个区间对应的二进制数是否完全相同，就可以用二分实现 $\Theta(\log n)$ 的比较。

于是对于线段树每个区间维护对应二进制数的哈希值（双哈希保险）。

题目询问的是长度 $\% (10^9+7)$ 的值，那其中一个 hash 参数可以选 $base = 2,mod = 10^9+7$ 的方便直接回答。

### 最短路：

dijkstra 套上数据结构即可，需要注意的是，点入队的时候需要存储当时对应的树根，因为在之后点的距离值可能被更新，树根会变，优先队列维护会出锅。

[CODE](https://www.luogu.com.cn/paste/e8zraw0k)

---

## 作者：louhao088 (赞：2)

果然是经典问题。


------------


首先最短路肯定还是要用 dijkstra ，可是由于数字很大，不能直接操作，我们考虑用数据结构来进行维护。


------------

首先我们要支持的操作是比较两个数的大小，这里有一个经典套路就是 Hash ，然后二分 LCP。


------------


然后我们要支持的是对某一位加 $1$，然后复制。由于有这个复制操作，我们很容易想到用主席树进行维护。但是这个加 $1$ 可能会遇到进位，怎么才能快速对某一位加 $1$ 呢？

我们考虑用线段树二分查找从一个位置开始向后的最长 $1$ 段。然后我们的操作就变成把一段区间赋为 $0$，然后单点修改。

区间赋值直接把儿子连到起点所代表的的那棵树上即可。

输出路径的话，直接在 dijkstra 时记录上一个的点即可。

复杂度 $O(n \log^2 n )$


------------


注意：

1. 主席树要从 $0$ 开始维护，最大值要略微超过 $10^5$，如 $10^5+100$，因为加和后可能会超过。

2. 用 dijkstra 时访问到已经改过的节点就直接返回，不然要多比一次大小，浪费空间。 


------------
代码如下

```cpp
// Problem: CF464E The Classic Problem
// Contest: Luogu
// URL: https://www.luogu.com.cn/problem/CF464E
// Memory Limit: 750 MB
// Time Limit: 5000 ms
// 2022-03-10 19:24:03
// Author : louhao088
#include<bits/stdc++.h>
using namespace std;
//static char buf[1000000],*p1=buf,*p2=buf;
//#define getchar() p1==p2&&(p2=(p1=buf)+fread(buf,1,1000000,stdin),p1==p2)?EOF:*p1++
#define pi pair<int,int>
#define mp make_pair
#define fi first
#define se second
#define pb push_back
#define mid (l+r>>1)
#define lowbit (x&-x)
const int maxn=1e5+105,M=34005,mod=1e9+7,mod2=1396716913;
inline int read()
{
	char ch=getchar();bool f=0;int x=0;
	for(;!isdigit(ch);ch=getchar())if(ch=='-')f=1;
	for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
	if(f==1)x=-x;return x;
}
inline void print(int x)
{
    static int a[55];int top=0;
    if(x<0) putchar('-'),x=-x;
    do{a[top++]=x%10,x/=10;}while(x);
    while(top) putchar(a[--top]+48);
}
int n,m,x,y,z,S,T,rt[maxn],las[maxn],ans[maxn],g,ls[maxn*200],rs[maxn*200],sum[maxn*200],tot=0;
bool vis[maxn];
vector<pi>e[maxn];
struct Hash
{
	int x,y;
	Hash operator +(const Hash &k)const{return{(x+k.x)%mod,(y+k.y)%mod2};}
	Hash operator -(const Hash &k)const{return{(x-k.x+mod)%mod,(y-k.y+mod2)%mod2};}
	Hash operator *(const Hash &k)const{return{1ll*x*k.x%mod,1ll*y*k.y%mod2};}
	bool operator ==(const Hash &k)const{return x==k.x&&y==k.y;}
}base,fac[maxn],s[maxn*200];
bool cmp(int rt,int rt1,int l,int r)
{
	if(l==r){return sum[rt]<sum[rt1];}
	if(s[rs[rt]]==s[rs[rt1]])return cmp(ls[rt],ls[rt1],l,mid);
	else return cmp(rs[rt],rs[rt1],mid+1,r);
}
int query(int rt,int l,int r,int L,int R)
{
	if(l>R||r<L)return 0;
	if(l>=L&&r<=R)return sum[rt];
	return query(ls[rt],l,mid,L,R)+query(rs[rt],mid+1,r,L,R);
}
void build(int &rt,int l,int r)
{
	rt=++tot;s[rt]={0,0};sum[rt]=0;
	if(l==r)return;build(ls[rt],l,mid);build(rs[rt],mid+1,r);
}
int find(int rt,int l,int r,int pos)
{
	if(l==r)return l;
	if(mid<pos)return find(rs[rt],mid+1,r,pos);
	else if(query(rt,l,r,pos,mid)==mid-pos+1)return find(rs[rt],mid+1,r,mid+1);
	else return find(ls[rt],l,mid,pos);
}
void add(int &rt,int rt1,int l,int r,int pos)
{
	if(l>pos||r<pos)return;rt=++tot;
	ls[rt]=ls[rt1],rs[rt]=rs[rt1];s[rt]=s[rt1];sum[rt]=sum[rt1];
	if(l==r){s[rt]={1,1};sum[rt]=1;return;}
	add(ls[rt],ls[rt1],l,mid,pos);add(rs[rt],rs[rt1],mid+1,r,pos);
	s[rt]=s[rs[rt]]*fac[mid-l+1]+s[ls[rt]];sum[rt]=sum[ls[rt]]+sum[rs[rt]];
}
void change(int &rt,int rt1,int rt2,int l,int r,int L,int R)
{
	if(l>R||r<L)return;rt=++tot;
	ls[rt]=ls[rt1],rs[rt]=rs[rt1];s[rt]=s[rt1];sum[rt]=sum[rt1];
	if(l>=L&&r<=R){ls[rt]=ls[rt2],rs[rt]=rs[rt2];s[rt]=s[rt2;sum[rt]=sum[rt2];return;}
	change(ls[rt],ls[rt1],ls[rt2],l,mid,L,R);change(rs[rt],rs[rt1],rs[rt2],mid+1,r,L,R);
	s[rt]=s[rs[rt]]*fac[mid-l+1]+s[ls[rt]];sum[rt]=sum[ls[rt]]+sum[rs[rt]];
}
void upd(int &Rt,int rt1,int pos)
{
	int x=find(rt1,0,n,pos);add(Rt,rt1,0,n,x);
	if(pos<x)change(Rt,Rt,rt[S],0,n,pos,x-1);
}
struct node{int x,rt;bool operator < (const node &a)const{return cmp(a.rt,rt,0,n);}};
void dij(int S)
{
	priority_queue<node>q;q.push({S,rt[S]});
	while(!q.empty())
	{
		int x=q.top().x;q.pop();
		if(vis[x])continue;vis[x]=1;
		if(x==T)break;
		for(auto i:e[x])
		{
			if(vis[i.fi])continue;
			int Rt;upd(Rt,rt[x],i.se);
			if(!rt[i.fi]||cmp(Rt,rt[i.fi],0,n))rt[i.fi]=Rt,q.push({i.fi,Rt}),las[i.fi]=x;
		}
	}
	if(!vis[T])puts("-1"),exit(0);
}
signed main()
{
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	g=read(),m=read();
	for(int i=1;i<=m;i++)
		x=read(),y=read(),z=read(),e[x].pb(mp(y,z)),e[y].pb(mp(x,z));
	n=1e5+50;base={2,17};fac[0]={1,1};
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*base;
	S=read(),T=read();build(rt[S],0,n);dij(S);
	cout<<s[rt[T]].x<<endl;int cnt=0;
	for(int i=T;i;i=las[i])ans[++cnt]=i;cout<<cnt<<endl;
	for(int i=cnt;i>=1;i--)printf("%d ",ans[i]);
 	return 0;
}


```


---

## 作者：弦巻こころ (赞：2)

我们发现,如果这题的边权没有这么大,那这就是最短路板子,但是这题边权大到无法直接比较,于是我们考虑用一个数据结构去维护它,我们需要实现比较以及加法.

我们可以用主席树维护这个东西,每个节点$[l,r]$表示$2^l-2^r,01$的状态.

对于加法,我们需要想办法方便的实现进位,考虑如何实现这个东西,对于一个区间$l,r$假设查询点在中点右方,那么我们就直接查询右区间,如果查询点在左方,我们就在$add$的时候记一个$0/1$表示是否进位然后如果进位就在加一下就好了.

对于比较,我们考虑记一个hash值,如果右区间相同就查询左区间,如果不同就查询右区间,然后到子节点时直接返回大小关系即可.

实现非常简便(

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N=514514,md=1e9+7;
int hd[N],nt[N*2],to[N*2],d[N*2],pw2[N*2],rt[N],pr[N];
int n,m,s,t,mx,tt=0,ct=0;
void add(int x,int y,int z){nt[++ct]=hd[x];to[ct]=y;hd[x]=ct;d[ct]=z;}
struct seg{int ls,rs,w;}tr[N<<5];
bool bij(int x,int y,int l,int r){
	if(l==r)return tr[x].w>tr[y].w;//子节点返回大小关系
	int mi=(l+r)>>1;
	if(tr[tr[x].rs].w==tr[tr[y].rs].w)return bij(tr[x].ls,tr[y].ls,l,mi);//右区间相同查左边
	return bij(tr[x].rs,tr[y].rs,mi+1,r);反之则查右边.
}
bool add(int x,int &y,int l,int r,int s){//bool值表示是否进位
	y=++tt;tr[y]=tr[x];
	if(l==r){tr[y].w=tr[x].w^1;return tr[x].w;}
	int mi=(l+r)>>1,ty;
	if(s>mi)ty=add(tr[x].rs,tr[y].rs,mi+1,r,s);
	else{ty=add(tr[x].ls,tr[y].ls,l,mi,s);
		if(ty)ty=add(tr[x].rs,tr[y].rs,mi+1,r,mi+1);//记得进位是进位到mi+1
	}tr[y].w=(1ll*tr[tr[y].rs].w*pw2[mi-l+1]+tr[tr[y].ls].w)%md;//计算hash值
	return ty;
}
struct pai{int x,rt;
	bool operator <(const pai &p)const{return bij(rt,p.rt,0,mx);}
};
priority_queue<pai>p;
void dfs(int x,int d){
	if(x==s){printf("%d\n%d ",d,x);return ;}
	dfs(pr[x],d+1);printf("%d ",x);
}
void put(int x){printf("%d\n",tr[rt[x]].w);dfs(x,1);exit(0);}
int main(){scanf("%d%d",&n,&m); 
	int x,y,z;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z);add(y,x,z);mx=max(mx,z);
	}mx+=114;pw2[0]=1;
	for(int i=1;i<=mx;i++)pw2[i]=pw2[i-1]*2%md;
	scanf("%d%d",&s,&t); 
	p.push({s,rt[s]});//dijkstra板子
	while(!p.empty()){pai yy=p.top();p.pop();
		if(yy.rt!=rt[yy.x])continue;
		if(yy.x==t)put(t);
		for(int i=hd[yy.x],ro;i;i=nt[i]){y=to[i],ro;
			add(yy.rt,ro,0,mx,d[i]);
			if(!rt[y]||bij(rt[y],ro,0,mx))//如果之前没访问过或者答案更小就更新
				rt[y]=ro,p.push({y,rt[y]}),pr[y]=yy.x;
		}
	}puts("-1");
}
 
```



---

## 作者：lingfunny (赞：1)

## 题解

[CF464E The Classic Problem](https://www.luogu.com.cn/problem/CF464E)。

首先边权是二进制，肯定可以连一条链然后组合出任意数，这样组合之后就是正经最短路了，所以在最短路这方面大概率是不能依靠二进制来走捷径。

考虑 dijkstra 的过程，需要在堆中插入和提取一个数。记比较两个数的时间复杂度是 $\mathcal O(A)$ 的，则总时间复杂度为 $\mathcal O(An\log n)$。在跑最短路的过程中，因为边权为正，所以最后肯定是简单路径，那么对于每一条边只会被走过一次，会造成一次加法运算的贡献。记加法的时间复杂度是 $\mathcal O(B)$ 的，总时间复杂度是 $\mathcal O(mB)$ 的。

考虑用一些数据结构维护数，让这两个时间复杂度尽可能均衡，或者达到 $\mathcal O(\text{能过})$。

因为是二进制，把数看成 $\texttt{01}$ 串，对于比较两个数，如果不考虑哈希冲突，从最高位开始二分/倍增哈希应该是一个较优的做法，打开标签发现果然有哈希，没跑了。比较可以做到 $\mathcal O(\log n)$。考虑用主席树维护数的哈希值，问题在于如何处理加法。

注意到这里的加法是只加一位（边权只有一位），在树上的表现应该是从 $x_i$ 开始找到一段极长的 $1$ 改为 $0$ 并将下一位修改为 $1$，修改似乎可以在主席树上 $\mathcal O(\log n)$ 暴力跑（如果能记父亲结点的话），当然也可以二分 $\mathcal O(\log^2 n)$ 跑。但，主席树区间覆盖会寄。

考虑开一棵全 $0$ 的单位元权值线段树，然后把要覆盖的区间新建节点然后接到单位元上，时间复杂度 $\mathcal O(\log n)$。

总时间复杂度 $\mathcal O(n\log X\log n+m\log^2 X)$。[提交记录](https://codeforces.com/contest/464/submission/156161301)。

### Code

```cpp
// Problem: CF464E The Classic Problem
// From: Luogu
// URL: https://www.luogu.com.cn/problem/CF464E
// Time: 2022-05-06 19:59
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
#define ULL unsigned long long
using namespace std;
const int mxn = 1e5+100, X = 1e5+50, mod = 1e9+7, mxz = 1e7+10, md = 998244353;

int n, m, S, T, conf[mxn], rpw[mxn], from[mxn], ans[mxn], top;
typedef pair<int, int> edge;
#define ev first
#define ew second
vector <edge> G[mxn];
int lc[mxz], rc[mxz], all[mxz], tot;
ULL hs[mxz], pw[mxn];
#define mid ((L+R)>>1)
inline void psup(int o, int L, int R) {
	all[o] = all[lc[o]] && all[rc[o]];
	hs[o] = (hs[lc[o]] * pw[R-mid] + hs[rc[o]]) % md;
}
int Judge(int cl, int cr, int o, int L = 0, int R = X) {
	if((cl <= L && R <= cr) || !o) return all[o];
	return (cl <= mid ? Judge(cl, cr, lc[o], L, mid) : 1) && (cr > mid ? Judge(cl, cr, rc[o], mid+1, R) : 1);
}
void Set(int p, int& o, int r, int L = 0, int R = X) {
	if(!o) o = ++tot;
	if(L == R) return all[o] = 1, hs[o] = 1, void();
	if(p <= mid) Set(p, lc[o], lc[r], L, mid), rc[o] = rc[r];
	else Set(p, rc[o], rc[r], mid+1, R), lc[o] = lc[r];
	psup(o, L, R);
}
inline int copy(int u, int v) {
	lc[u] = lc[v], rc[u] = rc[v];
	all[u] = all[v], hs[u] = hs[v];
	return u;
}
void cover(int cl, int cr, int& o, int L = 0, int R = X) {
	if(cl <= L && R <= cr) return o = 0, void();
	if(cl <= mid) {
		lc[o] = copy(++tot, lc[o]);
		cover(cl, cr, lc[o], L, mid);
	}
	if(cr > mid) {
		rc[o] = copy(++tot, rc[o]);
		cover(cl, cr, rc[o], mid+1, R);
	}
	psup(o, L, R);
}
int calc(int o, int L = 0, int R = X) {
	if(!o) return 0;
	if(L == R) return all[o]*rpw[L]%mod;
	return (calc(lc[o], L, mid) + calc(rc[o], mid+1, R)) % mod;
}
struct TreeNum {
	int rt;
	inline TreeNum(int x=0): rt(x) {}
	inline bool operator < (const TreeNum& rhs) const {
		int u = rt, v = rhs.rt, L = 0, R = X;
		if(hs[u] == hs[v]) return false;
		while(L != R) {
			while(hs[rc[u]] != hs[rc[v]]) u = rc[u], v = rc[v], L = mid+1;
			if(L != R) u = lc[u], v = lc[v], R = mid;
		}
		return all[u] < all[v];	// less
	}
	inline TreeNum operator + (const int& rhs) const {
		TreeNum New;
		int L = rhs, R = X, res = L;
		while(L <= R) {
			if(Judge(rhs, mid, rt)) L = mid+1;
			else res = mid, R = mid-1;
		}
		assert(!Judge(res, res, rt));
		Set(res, New.rt, rt);
		if(rhs < res) cover(rhs, res-1, New.rt);
		return New;
	}
} dis[mxn], INF, A;
typedef pair<TreeNum, int> node;
#define id second
priority_queue <node, vector <node>, greater<node>> di;

signed main() {
	pw[0] = rpw[0] = 1;
	for(int i = 1; i <= X; ++i) pw[i] = pw[i-1]*3 % md, rpw[i] = (rpw[i-1]<<1) % mod;
	scanf("%d%d", &n, &m);
	for(int x, y, z, i = 1; i <= m; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		G[x].emplace_back((edge){y, z});
		G[y].emplace_back((edge){x, z});
	}
	scanf("%d%d", &S, &T);
	Set(X, INF.rt, 0); Set(X-1, INF.rt, INF.rt);
	for(int i = 1; i <= n; ++i) if(i != S) dis[i] = INF;
	di.push({dis[S], S});
	while(di.size()) {
		int u = di.top().id; di.pop();
		if(conf[u]) continue;
		conf[u] = 1;
		for(edge e: G[u]) if(!conf[e.ev]) {
			TreeNum x = dis[u] + e.ew;	// O(Bm)
			if(x < dis[e.ev]) {
				dis[e.ev] = x; from[e.ev] = u;
				di.push({dis[e.ev], e.ev});	// O(Am log n)
			}
		}
	}
	if(!conf[T]) { puts("-1"); return 0; }
	printf("%d\n", calc(dis[T].rt));
	while(T != S) ans[++top] = T, T = from[T];
	ans[++top] = S; printf("%d\n", top);
	for(int i = top; i; --i) printf("%d%c", ans[i], " \n"[i==1]);
	return 0;
}
```

---

## 作者：ZZ作者 (赞：1)

主要做法其他题解写得很清楚，这里对于加 $2^k$ 操作提供常数较小的一种做法

~~虽然 cf 不卡常~~

现有的题解大多是二分了连续段长度，然后用单点修改，区间推平来做

我的做法是在线段树上走时，同时维护”当前认为要加一“的位置

如果当前区间为 $[l,r]$，”当前认为要加一“的位置为 $\text{lst}$:

在线段树上走时，先考虑左边，后考虑右边，如果 $\text{lst}$ 在相应区间内就走

若 $[l,r]$ 为全 $1$，那么 $\text{lst}=r+1$

否则若 $l=r$，这时必定这一位要加一，那么直接加一并返回

这样就不需二分查询连续段长度了，复杂度一样，但是常数较小

这部分的代码（另外还用建全 0/1 树的方法减少空间消耗，R0，R1 即为 0/1 树上的结点）：

```cpp
int lst;
inline void set1(int R0,int R1,int &x,int l,int r){ // + 2^k
	if(lst<l||lst>r)return;
	if(l==lst&&tr[R1].hs==tr[x].hs){ // [l,r] 全为1
		lst=r+1;
		x=R0;
		return;
	}
	else if(l==r){ // 找到地方，赋为1
		x=R1;
		return;
	}
	clone(x);
	if(lst<=mi)set1(tr[R0].l,tr[R1].l,lson);
	if(lst>mi)set1(tr[R0].r,tr[R1].r,rson);
	up(x,l,r);
}
struct Pos{
	int id,rt;
	inline Pos(int _id=0,int _rt=0){ id=_id; rt=_rt; }
	inline bool operator<(const Pos &b)const{
		return cmp(R0,R1,b.rt,rt,0,d)==1;
	}
};
Pos dis[N];
priority_queue<Pos> Q;
bool vis[N];
int la[N];
inline void dij(){
	for(int i=1;i<=n;i++)dis[i].id=i;
	for(int i=1;i<=n;i++)if(i!=s)dis[i].rt=R1;
	for(int i=1;i<=n;i++)vis[i]=0;
	dis[s].rt=R0;
	Q.push(dis[s]);
	while(!Q.empty()){
		Pos u=Q.top(); Q.pop();
		if(vis[u.id])continue;
		vis[u.id]=1;
		for(int i=h[u.id];i;i=nx[i]){
			int tc=cnt;
			int Rt=u.rt;
			lst=w[i]; // 从 w[i] 开始找
			set1(R0,R1,Rt,0,d); // + 2^w[i] 操作
			if(cmp(R0,R1,Rt,dis[to[i]].rt,0,d)==1){
				dis[to[i]].rt=u.rt;
				lst=w[i];
				la[to[i]]=u.id;
				dis[to[i]].rt=Rt;
				Q.push(dis[to[i]]);
			}
			else cnt=tc;
		}
	}
}
```

---

## 作者：shao0320 (赞：1)

#### CF464E The Classic Problem

码农数据结构题。

由于$2^{100000}$次方过大，因此考虑高精度最短路。

但是高精太慢了，无法通过此题。

然而这道题有个特殊性质在于边权都是$2$的次幂，因此考虑二进制的做法。

考虑$dijkstra$需要用到的操作，即需要支持两个数相加和两个数的比较。

首先考虑两个数相加，一个$2$的次幂和一个正整数相加，手玩即可发现其本质是先找到对应的二进制位，如果是$0$就置为$1$，如果是$1$就置为$0$并将其前边的一串$1$改为$0$，在最前头再添加一个$0$。因为需要用到的位数很少但是点的数量很多，所以只能用主席树没法用线段树。

这里有一点黑科技就是说，一般的主席树不太能支持区间修改，因此我们可以建一棵全零的主席树，只要需要置零的时候，我们就把对应节点连到上面，就可以快速置$0$了。

搞完这些以后，直接线段树上二分即可找到位置，然后进行上述操作即可。

而两个数比较的话也比较麻烦，因为我们首先需要比较右子树相不相等，但如果只记录$1$的个数无法比较，因此考虑记录一个$Hash$值，比较子树相不相等可以直接比较哈希值，可以在$O(1)$内完成比较。

然后套上$Dijkstra$模板即可。

```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define N 6000005
#define M 200005
#define mod 1000000007
#define P 100055
#define int long long
using namespace std;
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
int n,m,v[M],w[M],head[M],nxt[M],cnt,S,T;
int lc[N],rc[N],sum[N],now,rt[M],pre[M],vis[M],ans[M],top;
int Hash[N],bas[N];
void init()
{
	bas[0]=1ll;
	for(int i=1;i<=P;i++)
	{
		bas[i]=bas[i-1]*2ll;
		bas[i]%=mod;
	}
}
void add(int a,int b,int c)
{
	v[++cnt]=b;
	w[cnt]=c;
	nxt[cnt]=head[a];
	head[a]=cnt;
}
void pushup(int x)
{
	sum[x]=sum[lc[x]]+sum[rc[x]];
	Hash[x]=(Hash[lc[x]]+Hash[rc[x]])%mod;
}
int build(int l,int r,int val)
{
	int x=++now;
	if(l==r)
	{
		Hash[x]=bas[l]*val%mod;
		sum[x]=val;
		return x;
	}
	int mid=(l+r)>>1;
	lc[x]=build(l,mid,val);
	rc[x]=build(mid+1,r,val);
	pushup(x);
	return x;
}
int query(int x,int l,int r,int ql,int qr)
{
	if(l>=ql&&r<=qr)return sum[x];//l>=x&&r<=y
	int mid=(l+r)>>1;
	int res=0;
	if(ql<=mid)res+=query(lc[x],l,mid,ql,qr);
	if(qr>mid)res+=query(rc[x],mid+1,r,ql,qr);
	return res;
}
int find(int x,int l,int r,int p)
{
	if(l==r)return l;
	int mid=(l+r)>>1;
	if(p>mid)return find(rc[x],mid+1,r,p);
	if(query(lc[x],l,mid,p,mid)==mid-p+1)return find(rc[x],mid+1,r,mid+1);
	return find(lc[x],l,mid,p);
}
int modify(int x,int l,int r,int p)
{
	int u=++now;
	lc[u]=lc[x];rc[u]=rc[x];
	if(l==r)
	{
		sum[u]=1;
		Hash[u]=bas[l];
		return u;
	}
	int mid=(l+r)>>1;
	if(p<=mid)lc[u]=modify(lc[x],l,mid,p);
	else rc[u]=modify(rc[x],mid+1,r,p);
	pushup(u);
	return u;
}
int move(int u1,int u2,int l,int r,int ql,int qr)
{
	if(qr<l||ql>r)return u1;
	if(l>=ql&&r<=qr)return u2;
	int mid=(l+r)>>1;
	int u=++now;
	lc[u]=move(lc[u1],lc[u2],l,mid,ql,qr);
	rc[u]=move(rc[u1],rc[u2],mid+1,r,ql,qr);
	pushup(u);
	return u;
}
int Add(int Rt,int w)
{
	int p=find(Rt,0,P,w);
	//cout<<"!!!"<<p<<" "<<endl;
	int tmp=modify(Rt,0,P,p);
	//cout<<tmp<<endl;
	if(p==w)return tmp;
	tmp=move(tmp,rt[0],0,P,w,p-1);
	return tmp;
}
int same(int a,int b)
{
	return (sum[a]==sum[b]&&Hash[a]==Hash[b]);
}
int cmp(int a,int b,int l,int r)
{
	if(l==r)return sum[a]<=sum[b];
	int mid=(l+r)>>1;
	if(same(rc[a],rc[b]))return cmp(lc[a],lc[b],l,mid);
	else return cmp(rc[a],rc[b],mid+1,r);
}
struct info
{
	int x,d;
	bool operator<(const info &B)const{
		return cmp(B.d,d,0,P);	
	};
};
void Dij()
{
	priority_queue<info>q;
	int tmp=build(0,P,1);
	for(int i=1;i<=n;i++)rt[i]=tmp;
	rt[0]=rt[S]=build(0,P,0);
	q.push((info){S,rt[S]});
	//for(int i=1;i<=10;i++)
	//{
	//	cout<<i<<" "<<lc[i]<<" "<<rc[i]<<" "<<sum[i]<<" "<<Hash[i]<<endl;
	//}
	while(!q.empty())
	{
		while(!q.empty()&&vis[q.top().x])q.pop();
		if(q.empty())break;
		info c=q.top();
		q.pop();
		int x=c.x;
		//cout<<x<<endl;
		if(vis[x])continue;
		vis[x]=1;
		if(x==T)break;
		for(int i=head[x];i;i=nxt[i])
		{
			if(!vis[v[i]])
			{
				int new_rt=Add(rt[x],w[i]);
				//cout<<new_rt<<endl;
				if(cmp(rt[v[i]],new_rt,0,P))continue;
				rt[v[i]]=new_rt;pre[v[i]]=x;
				q.push((info){v[i],rt[v[i]]});
			}
		}
	}
	if(rt[T]==tmp)
	{
		puts("-1");
		return;
	}
	//puts("ANSWER!!!!!!!!");
	//for(int i=1;i<=n;i++)printf("%lld ",Hash[rt[i]]);
	//puts("");
	printf("%lld\n",Hash[rt[T]]%mod);
	for(int u=T;u!=S;u=pre[u])ans[++top]=u;ans[++top]=S;
	printf("%lld\n",top);
	for(int i=top;i>=1;i--)printf("%lld ",ans[i]);
}
signed main()
{
	//freopen("A.out","w",stdout);
	n=read();m=read();init();
	for(int i=1;i<=m;i++)
	{
		int x=read(),y=read(),z=read();
		add(x,y,z);add(y,x,z);
	}
	S=read();T=read();
	Dij();
	return 0;;
}
```



---

## 作者：chenzida (赞：1)

考虑高精度最短路，发现很简单但是过不了。

由于它给的性质 $2^x$，我们很容易想到用二进制来储存。

这样两个之间差的位数就可控了，可以主席树维护了。

1.比较大小

使用一下 $hash$ 值，找到第一个 $hash$ 值不等的地方，然后看看哪个是 $0$ 哪个是 $1$ 即可。

2.区间赋值为0

这个还挺人类智慧的，我们考虑建一个全 $0$ 的线段树，然后把这个要置为 $0$ 的区间连到哪个全 $0$ 的线段树即可。

至于找到第一个 $0$ ，我们线段树上二分一下即可。

代码如下：

```
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<queue>
#define int long long
using namespace std;
const int NR=1e5+100;
const int mod=1e9+7;
int add(int x,int y){return (x+y)%mod;}
int mul(int x,int y){return x*y%mod;}
int n,m,mx,a,b;
int power[NR]; 
int root[NR],Len[NR];
struct Segment
{
	int tot,siz[NR*51],hash[NR*51],ls[NR*51],rs[NR*51],Ans;
	void update(int rt,int t)
	{
		siz[rt]=siz[ls[rt]]+siz[rs[rt]]; 
		hash[rt]=add(mul(hash[rs[rt]],power[t]),hash[ls[rt]]);
	}
	void build(int &rt,int l,int r)
	{
		if(!rt)rt=++tot;int mid=(l+r>>1);
		Len[r-l+1]=rt;if(l==r)return;
		build(ls[rt],l,mid),build(rs[rt],mid+1,r);
	}
	void build1(int &rt,int l,int r)
	{
		if(!rt)rt=++tot;int mid=(l+r>>1);
		if(l==r){hash[rt]=1;siz[rt]=1;return;}
		build1(ls[rt],l,mid),build1(rs[rt],mid+1,r);
		update(rt,mid-l+1);
	}
	void cover(int &rt,int p,int q,int l,int r)
	{
		if(p==l&&q==r){rt=Len[r-l+1];return;}int mid=(l+r>>1);
		int la=rt;rt=++tot;ls[rt]=ls[la],rs[rt]=rs[la];
		if(q<=mid)cover(ls[rt],p,q,l,mid);
		else if(p>mid)cover(rs[rt],p,q,mid+1,r);
		else cover(ls[rt],p,mid,l,mid),cover(rs[rt],mid+1,q,mid+1,r);
		update(rt,mid-l+1);
	}
	bool cmp(int x,int y,int l,int r)
	{
		if(l==r)return hash[x]<hash[y];int mid=(l+r>>1);
		if(hash[rs[x]]!=hash[rs[y]])return cmp(rs[x],rs[y],mid+1,r);
		return cmp(ls[x],ls[y],l,mid);
	}
	void change(int &rt,int x,int l,int r)
	{
		int la=rt;rt=++tot;if(l==r){siz[rt]=hash[rt]=1;return;}
		ls[rt]=ls[la],rs[rt]=rs[la];int mid=(l+r>>1);
		if(x<=mid)change(ls[rt],x,l,mid);
		else change(rs[rt],x,mid+1,r);
		update(rt,mid-l+1);
	}
	void find1(int rt,int l,int r)
	{
//		printf("%lld %lld %lld\n",l,r,hash[rt]);
		if(l==r){Ans=l;return;}int mid=(l+r>>1);
		if(siz[ls[rt]]==mid-l+1)find1(rs[rt],mid+1,r);
		else find1(ls[rt],l,mid);
	}
	void find2(int rt,int p,int q,int l,int r)
	{
		if(Ans!=-1)return;int mid=(l+r>>1);
		if(p==l&&q==r){if(siz[rt]==r-l+1)return;find1(rt,l,r);return;}
		if(q<=mid)find2(ls[rt],p,q,l,mid);else if(p>mid)find2(rs[rt],p,q,mid+1,r);
		else{find2(ls[rt],p,mid,l,mid);if(Ans!=-1)return;find2(rs[rt],mid+1,q,mid+1,r);}
	}
	int find(int rt,int pos){Ans=-1;find2(root[rt],pos,mx,1,mx);return Ans;}
	void Add(int rt,int w){int x=find(rt,w);if(w<=x-1)cover(root[rt],w,x-1,1,mx);change(root[rt],x,1,mx);}
}S;
bool vis[NR];
int pre[NR],ans[NR];
int to[NR<<1],nxt[NR<<1],val[NR<<1],head[NR],tot=1;
void add(int x,int y,int z){mx=max(mx,z+21);to[tot]=y;val[tot]=z;nxt[tot]=head[x];head[x]=tot++;}
struct Nd{int x,d;bool operator<(const Nd &A)const{return !S.cmp(d,A.d,1,mx);}};
int read()
{
	int x=0,f=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}
	return x*f;
}
signed main()
{
//	freopen("1.in","r",stdin);
//	freopen("1.out","w",stdout);
	n=read(),m=read();mx=21;
	for(int i=1,x,y,z;i<=m;i++)
		x=read(),y=read(),z=read()+1,add(x,y,z),add(y,x,z);mx=100020;
	a=read(),b=read();
	power[0]=1;for(int i=1;i<=mx;i++)power[i]=mul(power[i-1],2);
	priority_queue<Nd>q;Nd O;O.x=a;q.push(O);S.build(root[a],1,mx);
	S.build1(root[n+2],1,mx);for(int i=1;i<=n;i++)if(i!=a)root[i]=root[n+2];
	while(!q.empty())
	{
		int x=q.top().x;q.pop();if(vis[x])continue;vis[x]=1;
		if(x==b)
		{
			int all=0,tt=x;while(x){ans[++all]=x;x=pre[x];}
			printf("%lld\n%lld\n",S.hash[root[tt]],all);
			for(int i=all;i>=1;i--)printf("%lld ",ans[i]);
			return 0;
		}
		for(int i=head[x];i;i=nxt[i])
		{
			int y=to[i];if(vis[y])continue;
			root[n+1]=root[x];S.Add(n+1,val[i]);
			if(S.cmp(root[n+1],root[y],1,mx))
			{
				pre[y]=x,root[y]=root[n+1];
				Nd X;X.x=y,X.d=root[y];q.push(X);
			}
		}
	}puts("-1");
	return 0;
}
//I love Chtholly forever

---

