# Bermart Ice Cream

## 题目描述

Bermart 连锁店出售各种冰淇淋，每种冰淇淋都有两个参数：价格和口味。

最初，有一家编号为 $1$ 的商店，不出售任何产品。

您必须处理以下类型的 $q$ 个查询：

- `1 x`：新店开张，编号为开张前的最大编号 $+1$，出售与 $x$ 店相同种类的冰淇淋，且顺序与 $x$ 店相同。
- `2 x p t`：一种价格为 $p$、口味为 $t$ 的冰淇淋在 $x$ 店上市。
- `3 x`：$x$ 店中供应时间最长（最早出现）的一种冰淇淋被移除。
- `4 x p`：求在 $x$ 店出售的所有种类的冰淇淋中花费不超过 $p$ 元能获得的最大总美味度，每种冰淇淋只能购买一次。

## 说明/提示

$1\le q\le 3\times 10^4$，$1\le p,t\le 2\times 10^3$，且保证：

- 每个查询中的 $x$ 不超过当前商店数量（即 $1$ 加上类型 $1$ 查询的数量)；
- 查询类型 $3$ 不会用于没有冰淇淋出售的商店；
- 至少有一个类型 $4$ 的查询。

## 样例 #1

### 输入

```
12
2 1 5 7
2 1 3 4
4 1 4
4 1 8
4 1 2
1 1
2 2 4 10
4 1 9
4 2 9
3 1
4 1 9
4 2 9```

### 输出

```
4
11
0
11
17
4
17```

# 题解

## 作者：EuphoricStar (赞：5)

考虑离线，把版本树建出来，然后递归的时候维护一个双端队列，支持向队头或队尾插入物品或弹出物品，询问就是查询队列中的物品的 01 背包数组的某一位。

如果只有 push_back 或 pop_back 的操作，可以用栈维护每个时刻的背包数组。对于原问题，考虑用两个栈维护双端队列：维护两个栈 $L, R$，push_front 和 pop_front 对栈 $L$ 进行，push_back 和 pop_back 对栈 $R$ 进行。若 pop 元素时对应的栈为空则暴力重构，把另一个栈的元素取一半分给这个栈。这样复杂度为 $O(n)$，其中 $n$ 为操作次数。

证明考虑设 $k_i$ 为在第 $i$ 次重构时双端队列的大小，$q_i$ 为在第 $i - 1$ 次到第 $i$ 次重构之间加入双端队列的元素数量。那么有 $k_i = \frac{k_{i - 1}}{2} + q_i$，重构总时间复杂度 $O(\sum k_i)$。发现 $q_i$ 对 $k_{i + j}$ 有 $\frac{q_i}{2^j}$ 的贡献，所以总时间复杂度就是 $O(\sum q_i + \frac{q_i}{2} + \frac{q_i}{4} + \cdots) = O(\sum q_i)$。

对栈进行 push 操作复杂度为 $O(p)$（因为要计算新的背包数组）。总时间复杂度 $O(qp)$。

[code](https://codeforces.com/problemset/submission/2026/288823790)

---

## 作者：Register_int (赞：4)

这也太牛了。

只考虑查询的话是个朴素的 01 背包问题，但是前面有各种奇怪的修改，貌似不好解决。

首先将“新开连锁店”的操作解决。这里可以使用 [可持久化并查集](/problem/P3402) 中的技巧，将所有版本建成一棵树，在树上跑搜即可。这样就只需支持撤销。

题目剩下两种操作又是从两种方向修改，要支持头尾插入撤销。我们知道 01 背包是容易支持撤销的，所以朴素的想法是维护两个栈，一个负责头一个负责尾，分别维护自身的 01 背包，查询时可以将两个背包的这一单点 $O(V)$ 合并。

那一个栈空了怎么办呢？参考 C++ 中的 deque 是怎么维护的。它的底层是两个 vector，一个被删空时会将满的那边分一半过去，复杂度是均摊 $O(n)$ 的。证明也很简单：分一半过去之后两个栈的地位平等，我们可以直接认为每个元素只会被从头栈扔到尾栈恰好一次，故复杂度为 $O(n)$。并且重新背包时的复杂度和分过去的元素个数是等同的，所以 dp 也只会跑 $O(n)$ 遍。

总时间复杂度 $O(nV)$，可以通过。

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int MAXN = 3e4 + 10;
const int MAXM = 2e3 + 10;

vector<pair<int, int>> G[MAXN], q[MAXN]; vector<int> af, ag;

int rt[MAXN], p[MAXN], t[MAXN], tf, tg, tot, cnt, tp, tq;

int n, f[MAXN][MAXM], g[MAXN][MAXM], ans[MAXN];

inline 
void addf(int x) {
	af.emplace_back(x), tf++, memcpy(f[tf], f[tf - 1], sizeof f[tf - 1]);
	for (int i = 2e3; i >= p[x]; i--) f[tf][i] = max(f[tf - 1][i], f[tf - 1][i - p[x]] + t[x]);
	for (int i = 1; i <= 2e3; i++) f[tf][i] = max(f[tf][i], f[tf][i - 1]);
}

inline 
void addg(int x) {
	ag.emplace_back(x), tg++, memcpy(g[tg], g[tg - 1], sizeof g[tg - 1]);
	for (int i = 2e3; i >= p[x]; i--) g[tg][i] = max(g[tg][i], g[tg - 1][i - p[x]] + t[x]);
	for (int i = 1; i <= 2e3; i++) g[tg][i] = max(g[tg][i], g[tg][i - 1]);
}

inline 
void rebuild(bool t) {
	vector<int> tmp;
	for (int x : af) tmp.emplace_back(x);
	reverse(tmp.begin(), tmp.end());
	for (int x : ag) tmp.emplace_back(x);
	int x = (tmp.size() + t) >> 1; tf = tg = 0, af.clear(), ag.clear();
	for (int i = x - 1; ~i; i--) addf(tmp[i]);
	for (int i = x; i < tmp.size(); i++) addg(tmp[i]);
}

inline 
int delf() {
	if (af.empty()) rebuild(1);
	int x = af.back(); return af.pop_back(), tf--, x;
}

inline 
int delg() {
	if (ag.empty()) rebuild(0);
	int x = ag.back(); return ag.pop_back(), tg--, x;
}

inline 
int ask(int x) {
	int ans = 0;
	for (int i = 0; i <= x; i++) ans = max(ans, f[tf][i] + g[tg][x - i]);
	return ans;
}

void dfs(int u) {
	for (pair<int, int> x : q[u]) ans[x.second] = ask(x.first);
	for (pair<int, int> x : G[u]) {
		int v = x.first, w = x.second;
		if (w) addg(w), dfs(v), delg();
		else w = delf(), dfs(v), addf(w);
	}
}

int main() {
	scanf("%d", &n), rt[1] = tot = cnt = 1;
	for (int i = 1, op, x, y; i <= n; i++) {
		scanf("%d%d", &op, &x);
		if (op == 1) rt[++cnt] = rt[x];
		if (op == 2) {
			tp++, scanf("%d%d", &p[tp], &t[tp]);
			G[rt[x]].emplace_back(++tot, tp), rt[x] = tot;
		}
		if (op == 3) G[rt[x]].emplace_back(++tot, 0), rt[x] = tot;
		if (op == 4) scanf("%d", &y), q[rt[x]].emplace_back(y, ++tq);
	}
	dfs(1);
	for (int i = 1; i <= tq; i++) printf("%d\n", ans[i]);
}
```

---

## 作者：Albert_van (赞：3)

[题](https://www.luogu.com.cn/problem/CF2026F) [题](https://mirror.codeforces.com/contest/2026/problem/F)。题外话：这场有点水平，E 题让我重拾了最大权闭合子图的记忆。

首先考虑没有这个可持久化（只有 $2,3,4$ 操作）怎么做。$0/1$ 背包问题，动态维护当前的 dp 数组 $f_i$ 表示总体积 $\sum p$ **不超过** $i$ 的前提下，总价值 $\sum t$ 的最大值，$f$ 大小为值域 $V=2000$。不方便撤销的滑动窗口，自然想单调队列，但是 $f$ 这个东西不符合单调队列的底层逻辑“更靠前且更小的元素没用”，因为每个物品的贡献不是简单的取 $\max$。

考虑如果把滑动窗口换成栈（要求 $\mathcal O(V)$ 将某个元素压入栈或弹栈、给出体积限制 $p$ 查询最大价值和），就可以直接做，对栈内每个物品维护它到栈底的所有物品构成的 $f$ 即可。回到队列，引入[普及组算法——双栈模拟队列](https://cp-algorithms.com/data_structures/stack_queue_modification.html#queue-modification-method-3)就能够把问题规约到栈上。具体地，开前后两个栈 $L,R$，入队压入 $R$，出队时若 $L$ 为空则把 $R$ 中元素全部搬到 $L$，然后从 $L$ 弹出。显然均摊 $\mathcal O(1)$。

![](https://cdn.luogu.com.cn/upload/image_hosting/htciomd6.png)

回到原问题，暴力可持久化不能接受（修改量总共 $\Theta(qV)$，多不了 $\log$）。这类可持久化问题[在操作可逆的情况下可以建出版本依赖树离线处理](https://www.luogu.com.cn/article/kzzo7rlv)，对于本题，对 $2,3$ 操作同样新建版本。考虑逆操作，要支持 `pop_back` 和 `push_front`，也就是把上文队列换成双端队列。双栈模拟仍然正确（插入删除都在对应一边，删除时如果那边的栈空了就把另一个栈全倒腾过来），不过复杂度是假的（多次 `push_back` 然后 `pop_front` 和 `pop_back` 交错能卡掉）。

发现每次把整个栈转移过去有点极端了。事实上，每次只转移栈底的 $\frac{siz}2$ 个物品即可均摊 $\mathcal O(1)$，[这是一种在国外普及度很高的神秘科技](https://mirror.codeforces.com/blog/entry/122003)。大概证明是，把底部 $\frac{siz}2$ 个物品和顶部 $\frac{siz}2$ 个物品一一配对，形成一种关系 $(u,v)$，后续只有在 $u$ 或 $v$ 出队时，另一个才可能继续发生栈间的转移。于是总的转移物品个数与入队次数 $+$ 出队次数相当，整体复杂度 $\mathcal O(qV)$。

另外一开始把 $f_i$ 定义成了体积**恰好**为 $i$ 导致查询变成 $\Theta(V^2)$。。联考前得复习下普及组算法，真不知道自己能这么唐。

```cpp
#include <cstdio>
#include <vector>
#include <stack>
#include <cstring>

using namespace std;

void cmx(int &x,int y){if(x<y) x=y;}

const int W=2327;

int rbq[W];

struct BMI{int p,t;};

void ad(int* f,BMI x){
	for(int i=W-1;i>=x.p;--i) cmx(f[i],f[i-x.p]+x.t);
}

namespace DS{
	class st{
		struct node{BMI x;int f[W];}tmp;
		public:stack<node> s;
		bool emp(){return s.empty();}
		void push(BMI x){
			memcpy(tmp.f,s.empty()?rbq:s.top().f,W<<2);
			ad(tmp.f,x);tmp.x=x;s.push(tmp);
		}
		BMI acs_tp(){BMI x=s.top().x;s.pop();return x;}
	}l,r,t;
	void adj(){
		bool flg=r.emp();if(flg) l.s.swap(r.s);
		int s=(int)r.s.size()>>1;
		while(s--) t.push(r.acs_tp());
		while(!r.emp()) l.push(r.acs_tp());
		while(!t.emp()) r.push(t.acs_tp());
		if(flg) l.s.swap(r.s);
	}
	int qry(int p){
		int *f=l.emp()?rbq:l.s.top().f,*g=r.emp()?rbq:r.s.top().f,res=0;
		for(int i=0;i<=p;++i) cmx(res,f[i]+g[p-i]);
		return res;
	}
	BMI acs_frt(){if(l.emp()) adj();return l.acs_tp();}
	void pop_bck(){if(r.emp()) adj();r.acs_tp();}
}

const int N=34102;

vector<int> vc[N];

struct qry{int p,i;};
vector<qry> qr[N];

bool del[N],ref[N];BMI w[N];int ans[N];

void dfs(int u){
	if(del[u]) w[u]=DS::acs_frt();
	if(ref[u]) DS::r.push(w[u]);
	for(auto[p,i]:qr[u]) ans[i]=DS::qry(p);
	for(int v:vc[u]) dfs(v);
	if(ref[u]) DS::pop_bck();
	if(del[u]) DS::l.push(w[u]);
}

int cur[N],v;

int main()
{
	int q,V=1,qc=0;scanf("%d",&q);
	while(q--){int f,x;scanf("%d%d",&f,&x);switch(f){
		case 1:vc[cur[x]].push_back(cur[++V]=++v);break;
		case 2:vc[cur[x]].push_back(++v),ref[cur[x]=v]=1,scanf("%d%d",&w[v].p,&w[v].t);break;
		case 3:vc[cur[x]].push_back(++v),del[cur[x]=v]=1;break;
		case 4:int p;scanf("%d",&p);qr[cur[x]].push_back((qry){p,++qc});break;
	}}
	dfs(0);for(int i=1;i<=qc;++i) printf("%d\n",ans[i]);
}
```

---

## 作者：xiezheyuan (赞：1)

## 简要题意

你需要维护一些冰淇淋店，初始时只有一家店，编号为 $1$，不出售任何冰淇淋。有 $n$ 次操作，支持：

- `1 x` 开一家新冰淇淋店，分配一个最小的没有分配过的正整数为编号，销售的冰淇淋与**此时** $x$ 销售的冰淇淋相同。
- `2 x p t` 冰淇淋店 $x$ 开始出售一种价格为 $p$ 元美味度为 $t$ 的冰淇淋。
- `3 x` 冰淇淋店 $x$ 停止销售最早开始销售的冰淇淋。
- `4 x p` 询问在冰淇淋店 $x$ 花费至多 $p$ 元购买冰淇淋（每种冰淇淋至多买一个），最大的冰淇淋美味度总和。

$1\leq n\leq 3\times 10^4,1\leq p,t\leq 2\times 10^3$，保证操作合法。

## 思路

### Part 1

首先不妨离线，将每种操作都挂到冰淇淋店上，然后可以从店 $1$ 开始遍历，如果遇到了 $1$ 操作，就递归（因为此时正好保存了此时这个冰淇淋店出售的冰淇淋状态，可以实现类似可持久化的效果），否则处理对应的操作，最后撤销本次进行的操作（可以直接反向操作）。这个算法不妨称为操作树分治。

然后观察我们如何进行操作，不妨将冰淇淋按照开始出售的时间排序，那么我们始终只会在这个冰淇淋序列的首尾进行插入删除操作，而查询其实可以看成 $01$ 背包，于是我们需要维护一个维护物品双端队列，支持首尾增删和查询此时双端队列的所有物品的 $01$ 背包的结果。

使用线段树分治，可以做到 $O(pn\log n)$ 足以通过本题，不过不是最优的。关于本做法，可以参考 [CF601E A Museum Robbery](https://www.luogu.com.cn/problem/CF601E)。

### Part 2

我们讲一下另一个做法：对顶栈（Minimum / Maximum Deque），因为这个算法通常用于维护双端队列的最值而得名。

为了引入这个算法，先来考虑一个经典问题：

> 你需要维护一个双端队列，支持首尾增删、查询整个队列的最小值。**要求所有操作时间复杂度 $O(1)$。**

我们发现如果将双端队列换成栈，问题是极为容易的，单独维护一个栈表示前缀最小值即可。我们称这个数据结构为最值栈（Minimum / Maximum Stack）。

这启发我们用栈模拟双端队列。**我们将双端队列分成两个栈，两端是栈顶，中间是栈底。**，如图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/d4xsnsdw.png)

于是首尾插入操作就很好完成了，直接用最值栈模拟即可。查询也是容易的，取两个最值栈的答案的最小值即可。

对于首尾删除操作，如果删除完后，每个栈都是非空的，那么也是容易的，直接套用最值栈的删除即可，关键是如果有一个栈被删空了，我们应该如何处理？

这时我们引入重构（Rebalance）操作，用于将剩下的存在元素的栈，将一半（向上取整）的元素分给另一个空栈，如下图所示：

![](https://cdn.luogu.com.cn/upload/image_hosting/49zpdl4b.png)

至于重构的实现，可以直接暴力将所有元素提取出来，然后进行分配，方法很多，不再赘述。

这样，我们就可以在栈删空时进行一次重构，这样就可以继续完成接下来的操作了。

使用势能分析法，容易证明所有操作均摊 $O(1)$，事实上 STL 中的 `std::deque` 就使用了类似的维护方法，使用两个栈（`std::vector` 而不是 `std::stack`）来实现双端队列的效果。

### Part 3

通过 Part 2 的铺垫，我们很容易的将对顶栈技术应用到本题，只需要一个物品栈，支持尾部插入删除，查询整个栈的 $01$ 背包，由于本题是求最大值而不是计数，因此无法使用传统的可撤销背包，不过我们可以维护前缀的 dp 数组来变相的实现可撤销（如果你学习过线段树分治，可能会觉得很熟悉，我们只是省略了每个位置的记录更改过程）。这样插入只需要进行一次背包 dp，删除只需要弹栈。

最后一个问题是如何将两个栈的背包信息合并，这同样是容易的，枚举第一个栈的最大总重量即可。

于是我们借助对顶栈出色地完成了本题，时间复杂度 $O(pn)$。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 3e4 + 5;
int m;

struct min_stack{
    stack<pair<int,int>> s;
    stack<vector<int>> f;
    min_stack(){
        vector<int> h; h.resize(2001);
        f.push(h);
    }
    void push(pair<int,int> val){
        auto [w, v] = val;
        vector<int> h; h.resize(2001);
        vector<int> &g = f.top();
        copy(g.begin(), g.begin() + w, h.begin());
        for(int i=w;i<=2000;i++) h[i] = max(g[i], g[i - w] + v);
        f.push(h), s.push(val);
    }
    void pop(){ s.pop(), f.pop(); }
    bool empty(){ return s.empty(); }
    int size(){ return s.size(); }
    pair<int,int> top(){ return s.top(); }
    int operator[](int x){ return f.top()[x]; }
    void reverse(){
        queue<pair<int,int>> t;
        while(!s.empty()) t.push(s.top()), pop();
        while(!t.empty()) push(t.front()), t.pop();
    }
};

struct min_queue{
    min_stack s[2];
    void push(bool x, pair<int,int> v){ s[x].push(v); }
    void fix(bool x){
        if(!s[x].empty()) return;
        int cnt = s[!x].size() >> 1;
        while(cnt--) s[x].push(s[!x].top()), s[!x].pop();
        s[x].reverse(), s[!x].reverse();
        swap(s[0], s[1]);
    }
    pair<int,int> top(bool x){ return fix(x), s[x].top(); }
    void pop(bool x){ fix(x), s[x].pop(); }
    int query(int x){
        int ans = 0;
        for(int i=0;i<=x;i++) ans = max(ans, s[0][i] + s[1][x - i]);
        return ans;
    }
} mq;

struct option{ int op, x, y; };
vector<option> opts[N];
int answer[N];

void dfs(int u){
    vector<option> tmp;
    for(auto [op, x, y] : opts[u]){
        if(op == 1) dfs(x);
        if(op == 2) mq.push(1, {x, y}), tmp.push_back({3, 0, 0});
        if(op == 3){
            auto [w, v] = mq.top(0);
            tmp.push_back({2, w, v}), mq.pop(0);
        }
        if(op == 4) answer[y] = mq.query(x);
    }
    reverse(tmp.begin(), tmp.end());
    for(auto [op, x, y] : tmp){
        if(op == 2) mq.push(0, {x, y});
        if(op == 3) mq.pop(1);
    }
}

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);cout.tie(0);
    cin >> m; int cnt = 1, tot = 0;
    for(int i=1;i<=m;i++){
        int op, x, y, z;
        cin >> op >> x;
        if(op == 1) opts[x].push_back({op, ++cnt, 0});
        if(op == 2) cin >> y >> z, opts[x].push_back({op, y, z});
        if(op == 3) opts[x].push_back({op, 0, 0});
        if(op == 4) cin >> y, opts[x].push_back({op, y, ++tot});
    }
    dfs(1);
    for(int i=1;i<=tot;i++) cout << answer[i] << '\n';
    return 0;
}

// Written by xiezheyuan
```

---

## 作者：yhylivedream (赞：1)

不看 1 操作和 3 操作，是一个普通的 01 背包，可以做到修改 $O(p)$，查询 $O(1)$。

再看 2 操作，删除第一个比较困难，因为前面的状态会转移到后面的状态，而删除最后一个很简单，考虑维护两个栈，和两个栈里的 01 背包，这样就转化为尾插和尾删，查询时 $O(p)$ 合并状态求最值。

当一个栈空时，考虑重构，将另一栈分一半给空的栈，可得复杂度是 $O(n)$ 的，证明：设 $i-1,i$ 次重构加进去 $c_i$ 个元素，可知每个元素至多会从右边到左边一次，所以每次重构，$c_i$ 对复杂度贡献除 $2$，即对复杂度贡献 $O(c_i+\frac{c_i}{2}+\frac{c_i}{4}+\cdots)=O(c_i)$，而 $O(\sum c_i)\le O(n)$，所以算法复杂度是 $O(n)$。

对于 1 操作，因为题目并没有要求在线且操作可逆，考虑建出版本树，若版本 $i$ 依赖版本 $a_i$ 则，$a_i$ 为 $i$ 的父亲，DFS 遍历树即可。

代码不给了。

---

## 作者：BMnya (赞：0)

先按照操作 1 建树，然后把所有操作按顺序挂在树上，再按照 DFS 的顺序重新排列所有操作（包括加物品、删物品、求 01 背包三种）。

这样当 DFS 到节点 $x$ 时，当前物品集合正好是 $x$ 所对应的集合，然后就不需要考虑不同的节点了，问题转化为一个序列的操作。

01 背包不支持物品的删除，但是添加物品以及撤销（存备份然后覆盖）是容易的，所以可以用 [线段树分治](https://oi-wiki.org/topic/segment-tree-offline/) 解决。

时间复杂度为 $O(q\log q\max p)$，具体细节见代码注释。

---

顺带提一下 [官方题解](https://codeforces.com/blog/entry/135680) 的 $O(q\max p)$ 做法：DFS 的过程与上述相同，但是在 DFS 的过程中计算答案。

现在需要在两端处添删物品，求 01 背包。如果只需要在一端修改，只需要开一个栈即可；在两端修改的话可以开两个栈分别向左向右，修改时修改对应的栈，如果对应的栈为空就重构，查询时花费 $O(p)$ 的时间合并两个栈的答案。

---

[提交记录](https://codeforces.com/contest/2026/submission/288612638)，以下是主要部分代码：

```cpp
const int N=3e4+10,M=2e3+10;
int n,q,op[N],x[N],p[N],t[N],ans[N],id[N],vis[N];

// 注意这里最终处理出的操作序列（vc）长度最大为 2q。

vector<int> G[N]; vector<int> vc,ps[N*8]; vector<int> f(M,0);

#define ls  (x<<1)
#define rs  (x<<1|1)
#define mid ((l+r)>>1)

// 线段树分治的标记。

void add(int x,int l,int r,int p,int q,int k){
    if(l==p&&r==q) return ps[x].emplace_back(k),void();
    if(q<=mid) add(ls,l,mid,p,q,k);
    else if(p>mid) add(rs,mid+1,r,p,q,k);
    else add(ls,l,mid,p,mid,k),add(rs,mid+1,r,mid+1,q,k);
}

// 线段树分治的处理。

void solve(int x,int l,int r){
    auto tmp=f;
    for(auto id:ps[x]){
        int p=::p[id],t=::t[id];
        for(int i=M-1;i>=p;--i) f[i]=max(f[i],f[i-p]+t);
    }
    if(l==r){
        if(vc[l]<0) ans[-vc[l]]=f[p[-vc[l]]];
    }
    else solve(ls,l,mid),solve(rs,mid+1,r);
    f=tmp;
}

// id 数组内按顺序存当前节点的所有物品。

void dfs(int x,int L,int R){
    int sL=L,sR=R;
    for(auto i:G[x]){
        if(op[i]==1) dfs(p[i],L,R); // 此时的物品序列正好是子店刚开张时的物品序列，先递归处理子店的问题。
        else if(op[i]==2) id[++R]=i,vc.emplace_back(i); // 加。
        else if(op[i]==3) vc.emplace_back(id[L++]); // 删。
        else vc.emplace_back(-i); // 查。
    }
    // 向上返回时记得恢复到父店的序列。
    while(L>sL) vc.emplace_back(id[--L]);
    while(R>sR) vc.emplace_back(id[R--]);
}

inline void solve(){
    n=1,q=read();
    for(int i=1;i<=q;++i){
        op[i]=read();
        if(op[i]==1) x[i]=read(),p[i]=++n,G[x[i]].emplace_back(i);
        else if(op[i]==2) x[i]=read(),p[i]=read(),t[i]=read(),G[x[i]].emplace_back(i);
        else if(op[i]==3) x[i]=read(),G[x[i]].emplace_back(i);
        else x[i]=read(),p[i]=read(),G[x[i]].emplace_back(i);
    }
    dfs(1,1,0);
    memset(vis,-1,sizeof vis);
    for(int i=0;i<vc.size();++i)
        if(vc[i]>0){
            if(vis[vc[i]]!=-1) add(1,0,vc.size()-1,vis[vc[i]],i-1,vc[i]),vis[vc[i]]=-1;
            else vis[vc[i]]=i;
        }
    solve(1,0,vc.size()-1);
    for(int i=1;i<=q;++i) if(op[i]==4) printf("%d\n",ans[i]);
}
```

---

## 作者：luckydrawbox (赞：0)

[$\text{Link}$](https://www.luogu.com.cn/problem/CF2026F)

## 题意

初始时，有一个商店，编号为 $1$，其中没有物品。接下来有 $q$ 次操作，操作有 $4$ 种：

- $1\ x$：新建一个商店，编号为目前的商店数 $+1$，且该商店内的物品种类与当前商店 $x$ 中的相同。
- $2\ x\ p\ t$：在商店 $x$ 中新建一种物品，体积为 $p$，价值为 $t$。
- $3\ x$：把商店 $x$ 中最早出现的一种物品删除，保证删除前 $x$ 内至少有一种物品。
- $4\ x\ p$：对商店 $x$ 中的物品做 $01$ 背包，求在总体积不超过 $p$ 时的最大总价值。

所有操作均合法，$1\le q\le 3\times 10^4,1\le p,t\le 2000$，对于每个操作 $4$ 输出答案。

## 分析

由于 $p,q$ 很大，所以不能出现背包合并，这启发我们只用加入单个物品的做法更新背包。

不妨先考虑物品构成的形态，不考虑删除，显然新加入物品时商店会继承前面的物品，这样物品之间的关系就构成了一棵树，同时，一个商店是一条从根到某个节点的链。若有删除，则相当于把链顶向下扩展，任意时刻的商店都是一条祖先-后代链，而查询就是查询这样一条链。

先不考虑细节（，我们考虑大概怎么做，可以先建出这棵树，然后离线出所有的询问，现在问题形如树上每个点都是一个物品，查询了若干条祖先-后代链的 $01$ 背包的点值（本来是前缀 $\max$，但显然可以每次转移后取前缀 $\max$ 使其变成点值）。考虑枚举一个分支中心 $x$，把跨过这个中心的链全部处理掉，具体的，找出这些链中深度最浅的链顶 $u$，先求出从 $x$ 到 $x\rightarrow u$ 的路径上的所有点的链的背包数组，接下来从 $x$ 往下延伸到所有经过 $x$ 的链的链底，每次都从祖先继承下来，在链底处背包合并求点值，在合理枚举分支中心的情况下，感觉每次移动都会对应一次原来的操作，所以是 $O(pq)$ 的，可以接受。

那么如何枚举才最优呢，我们考虑在 dfs 到点 $x$ 时，先递归处理子树，然后判断是否有未被处理的链的链顶为 $x$，若有就以 $x$ 为中心做一次，显然这样是最优的，因为到父亲就处理不到这条链了。简单证明一下复杂度，假设有个商店的某两个询问不相交，分别为 $u_1\rightarrow v_1,u_2\rightarrow v_2$，$dep_{u_1}<dep_{v_1}<dep_{u_2}<dep_{v_2}$，那么处理 $u_2\rightarrow v_2$ 时就处理不到 $u_1\rightarrow v_1$，但注意到这么下来链 $u_1\rightarrow u_2$ 的点被插入、删除各一次，所以完全可以把 $u_1\rightarrow v_1$ 当成一个独立开创的商店，因此每次背包都可以对应到一次操作，总复杂度为 $O(pq)$。

做完了？不，才刚刚开始。看起来没什么思维含量的一个题，为什么算上 unofficial 只有 $4$ 个 AK ？因为这是一道【】的细节~~码农~~题。

可能遇到的问题有：商店中途没有物品时，链怎么处理？复制节点 $1$ 怎么处理？

这里提供我的写法：我们把整个做法大致分为三个步骤：

1. 建出物品树。
1. 处理出询问。
1. 背包求答案。

我们希望无论何时商店链都存在，所以不妨让商店链为**上开下闭**，即链顶的物品不会记入答案。同时给商店 $1$ 强行塞一个物品（节点 $1$） $(p_1,t_1)=(0,0)$，使商店 $1$ 的链为 $1\rightarrow 1$，插入物品时动态维护商店链；另外再建一个空根 $0$，方便复制节点 $1$。查询时也是类似的做即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
long long read(){
	long long x=0,f=1;char ch=getchar();
	while(!isdigit(ch))
	{if(ch=='-') f=-1;ch=getchar();}
	while(isdigit(ch)){x=x*10+ch-48;ch=getchar();}
	return x*f;
}
void write(long long x){
    if(x<0) putchar('-'),x=-x;
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
const int N=3e4+10,M=2010;
int T,q,tot,tx,ta,P=2000,lq;
vector<int>g[N];
int f[N][16],dep[N];
int p[N],t[N];
struct clain{
	int st,ed,aks;
}a[N];
int e[N],s1[N];
int id[N],ans[N],vis[N],sum[N];
void add(int fa,int x){
	g[fa].push_back(x);
	dep[x]=dep[fa]+1;
	f[x][0]=fa;
	for(int i=1;i<16;i++)f[x][i]=f[f[x][i-1]][i-1];
}
int find(int x,int fa){
	for(int i=15;i>=0;i--){
		if(dep[f[x][i]]>dep[fa])x=f[x][i];
	}
	return x;
}
vector<int>es[N],es2[N],ts[N];
int Dp[N][M];
void dfs2(int x,int fx,int *dp){
	int dp2[M];
	memcpy(dp2,dp,sizeof(dp2));
	if(x!=fx){
		for(int j=P-p[x];j>=0;j--){
			dp[j+p[x]]=max(dp[j+p[x]],dp2[j]+t[x]);
		}
		for(int j=1;j<=P;j++)dp[j]=max(dp[j],dp[j-1]);
	}
	for(auto y:es2[x]){
		ans[y]=0;vis[y]=1;
		for(int j=0;j<=a[y].aks;j++){
			ans[y]=max(ans[y],dp[j]+Dp[dep[a[y].st]][a[y].aks-j]);
		}
	}
	sum[x]=0;
	for(auto y:g[x]){
		if(sum[y]){
			memcpy(dp2,dp,sizeof(dp2));
			dfs2(y,fx,dp2);
		}
	}
}
void dfs1(int x){
	int son=x;
	for(auto y:g[x]){
		dfs1(y);
		if(es[id[y]].size()>es[id[son]].size())son=y;
		sum[x]+=sum[y];
	}
	if(id[x]!=id[son])
		while(es[id[x]].size()){
			es[id[son]].push_back(es[id[x]].back());
			es[id[x]].pop_back();
		}
	id[x]=id[son];
	for(auto y:g[x]){
		if(y==son)continue;
		while(es[id[y]].size()){
			es[id[son]].push_back(es[id[y]].back());
			es[id[y]].pop_back();
		}
	}
	while(ts[x].size()&&vis[ts[x].back()]){
		ts[x].pop_back();
	}
	if(ts[x].size()){
		int md=dep[x];
		for(auto y:es[id[x]]){
			md=min(md,dep[a[y].st]);
		}
		memset(Dp[dep[x]],0,sizeof(Dp[dep[x]]));
		memset(Dp[dep[x]+1],0,sizeof(Dp[dep[x]+1]));
		for(int y=x;dep[y]>md;){
			int fa=f[y][0];
			memcpy(Dp[dep[fa]],Dp[dep[y]],sizeof(Dp[dep[fa]]));
			for(int j=P-p[y];j>=0;j--){
				Dp[dep[fa]][j+p[y]]=max(Dp[dep[fa]][j+p[y]],Dp[dep[y]][j]+t[y]);
			}
			for(int j=1;j<=P;j++)Dp[dep[fa]][j]=max(Dp[dep[fa]][j],Dp[dep[fa]][j-1]);
			y=fa;
		}
		memcpy(Dp[0],Dp[N-5],sizeof(Dp[0]));
		dfs2(x,x,Dp[0]);
		es[id[x]].clear();
	}
}
int main(){
	//freopen(".in","r",stdin);
	//freopen(".out","w",stdout);
	q=read();
	tot=1;tx=1;
	s1[1]=e[1]=1;dep[1]=1;
	add(0,1);
	lq=0;
	while(q--){
		int op=read(),x,y,z;
		x=read();
		if(op==1){
			tot++;
			e[++tx]=e[x];s1[tx]=s1[x];
			p[tot]=p[e[tx]];
			t[tot]=t[e[tx]];
			add(f[e[tx]][0],tot);
			if(s1[x]==e[x])s1[tx]=tot;
			e[tx]=tot;
		}
		else if(op==2){
			y=read();z=read();
			tot++;
			add(e[x],tot);
			e[x]=tot;p[tot]=y;t[tot]=z;
		}
		else if(op==3){
			y=find(e[x],s1[x]);
			s1[x]=y;
		}
		else{
			y=read();
			a[++ta]=(clain){s1[x],e[x],y};
			es[e[x]].push_back(ta);
			es2[e[x]].push_back(ta);
			ts[s1[x]].push_back(ta);
			sum[e[x]]++;
		}
	}
	for(int i=1;i<=tot;i++)id[i]=i;
	for(auto y:g[0])dfs1(y);
	for(int i=1;i<=ta;i++)printf("%d\n",ans[i]);
	return 0;
}
```

---

