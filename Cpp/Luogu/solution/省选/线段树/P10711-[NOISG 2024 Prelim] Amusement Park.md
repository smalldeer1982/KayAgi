# [NOISG 2024 Prelim] Amusement Park

## 题目背景

翻译自 [NOI SG 2024 Prelim D.Amusement Park](https://github.com/noisg/noi-2024-prelim)。

## 题目描述

有一家游乐园，在大门处有一项观光车服务。很显然，一辆观光车只能承载有限的人数，那么如果一个团队来到大门时，发现观光车不够坐时，他们需要决定是否愿意分开。有些团队愿意，有些不愿意。

为了解决这个复杂的问题，公园的管理者蜗牛 Stuart 想请你帮忙写一个程序，支持以下三种操作：

- `join`：一个新的团队进入了队列。我们用两个整数 $s,w$ 描述此次操作：$s$ 表示该团队的总人数；如果 $w=1$，那么这个团队愿意在乘坐观光车时分开；如果 $w=0$，表示他们不愿意分开。假设这次操作是所有操作中第 $i$ 次 `join` 操作，则该团队的编号为 $i$。

- `leave`：给定 $i$，编号为 $i$ 的团队从队伍中离开。

- `board`：给定 $b$，表示新开来一辆能坐 $b$ 人的观光车。从队头开始，如果到一个团队时，观光车可以承载所有人，那么所有人上车；否则如果该团队愿意分开，那么部分人上车；否则该团队留在原位置，在下一个团队重复该过程，直到观光车坐满，或没有人愿意上车。

## 说明/提示

### 【数据范围】

|$\text{Subtask}$|分值|特殊性质|
|:-:|:-:|:-:|
|$0$|$0$|样例|
|$1$|$12$|$q\le1000$|
|$2$|$7$|$s=1,w=0$，没有 `leave` 操作|
|$3$|$20$|$s\le10,w=0$，没有 `leave` 操作|
|$4$|$16$|$s\le10$，没有 `leave` 操作|
|$5$|$10$|$s\le10$|
|$6$|$35$|无特殊性质|

对于 $100\%$ 的数据：

- $1 \le q \le 200000$

- 对于所有 `join` 操作，$1 \le s \le 200000,0 \le w \le 1$。

- 对于所有 `leave` 操作，保证所有 $i$ 在操作时都在队列中。

- 对于所有 `board` 操作，$1 \le b \le 10^{12}$。

- 至少有一次 `board` 操作。

## 样例 #1

### 输入

```
7
1 2 0
1 6 0
1 6 1
3 5
2 2
1 3 0
3 123456789012```

### 输出

```
2
1 2
3 3
2
3 3
4 3```

## 样例 #2

### 输入

```
5
1 1 0
1 1 0
1 1 0
3 2
1 1 0```

### 输出

```
2
1 1
2 1
```

## 样例 #3

### 输入

```
4
1 19 1
3 10
3 10
3 10
```

### 输出

```
1
1 10
1
1 9
0
```

# 题解

## 作者：船酱魔王 (赞：6)

## Changelog

修改了码风和影响理解的变量名，抱歉影响管理员时间导致重新审核。

## 题意回顾

请你维护三种对于一个队列的操作：

* 在队尾增加一个小团队，给定人数和类型；
* 在队伍中间踢出一个小团队；
* $ k $ 个人进入游乐场，从队头开始，若该小团队可以全部进入就全部进入，否则若可以拆分就进入剩余名额个人。**请输出进游乐场的人员所属小团队及该小团队进入人数。**

操作次数不超过 $ 2 \times 10^5 $。

## 分析

可以发现一个小团队只会被完整地离开队列一次，每次操作最多导致一个小团队部分离开队列。因此小团队的人员变动次数是线性量级的。考虑设计关于此的势能复杂度算法。

我们需要快速找到下一个需要人员变动的位置，数据范围较小考虑分块，考虑如果一个段内都没有人员变动的条件：这个段内没有还在队列里的可拆分小团队，并且这个段内的所有小团队的人数都严格大于剩余名额数。显然这两个数值都可以被修改时快速维护。

对于一个段，如果被跳过，则带来 $ O(1) $ 的时间复杂度；如果不被跳过，会至少出现一次人员变动。对于一次修改，耗时是 $ O(\sqrt{n}) $。

所以，时间复杂度为 $ O(n\sqrt n) $。

## AC 代码 

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
#define ll long long
#define whr pair<int, int>
using namespace std;
const int N = 2e5 + 5;
const int S = 448;
int q, n;
int a[N];
int b[N];
int lmq1[N];// min of all
int lmq2[N];// sum of free
ll remb;
vector<whr> lyh;
inline void eat(int i) {
    if(!a[i]) return;
    if(remb >= a[i]) remb -= a[i], lyh.push_back((whr){i, a[i]}), a[i] = 0;
    else if(b[i]) a[i] -= remb, lyh.push_back((whr){i, remb}), remb = 0;
}
inline void abcde(int x) {
    int blo = x / S * S;
    int bd = min(n, blo + S - 1);
    lmq1[x / S] = N, lmq2[x / S] = 0;
    for(int i = blo; i <= bd; i++) {
        lmq1[x / S] = min(lmq1[x / S], ((a[i] == 0) ? N : a[i])), lmq2[x / S] += b[i] && a[i];
    }
}
int main() {
    scanf("%d", &q);
    int op, tp;
    ll x;
    for(int qi = 1; qi <= q; qi++) {
        scanf("%d", &op);
        if(op == 1) {
            scanf("%lld%d", &x, &tp);
            a[++n] = x, b[n] = tp;
            abcde(n);
        } else if(op == 2) {
            scanf("%lld", &x);
            a[x] = 0;
            abcde(x);
        } else if(op == 3) {
            scanf("%lld", &x);
            remb = x;
            for(int blo = 0; blo <= n / S; blo++) {
                if(!lmq2[blo] && (lmq1[blo] > remb || lmq1[blo] == N)) continue;
                int lf, rt;
                lf = blo * S;
                rt = min(n, lf + S - 1);
                for(int i = lf; i <= rt; i++) {
                    eat(i);
                    if(!remb) break;
                }
                abcde(blo * S);
                if(!remb) break;
            }
            printf("%d\n", (int)lyh.size());
            for(int i = 0; i < lyh.size(); i++) printf("%d %d\n", lyh[i].first, lyh[i].second);
            lyh.clear();
        } else puts("dthkxy AK IOI");
    }
    return 0;
}
```

---

## 作者：EricWan (赞：4)

这题还是很有难度的，建议评紫。

没想到 STD 写的比我的代码还屎，我研究了老半天。

题意已经很清楚了，但看到后让人没头绪。

可以证明输出总长是线性的，考虑每次放走一组中的若干人。

假设当前的空位数为 $x$，我们只需要知道编号最小的组且可以被这辆车带走至少一人一组的编号即可。

我们可以设定一个组在线段树中的位置为人数（如果不可拆）或 $0$（如果可拆），价值为编号，用 `set` 映射到一个线段树上，每次查询前缀最大值或修改单点。

思路就是这样，具体请看代码：

```cpp
#include <bits/stdc++.h>
#define int long long
#define INF 1000000000000000000ll
#define MAXN 1000005
using namespace std;
int X[MAXN], Y[MAXN], minn[MAXN];
set<int> st[MAXN];
int query(int id, int l, int r, int x, int y) { // 线段树前缀最小查询
	if (y < l || x > r) return INF;
	if (x <= l && y >= r) return minn[id];
	int mid = (l + r) / 2;
	return min(query(id * 2, l, mid, x, y), query(id * 2 + 1, mid + 1, r, x, y));
}
void update(int id, int l, int r, int x, int k) { // 线段树单点修改
	if (l == r) {
		minn[id] = k;
		return;
	}
	int mid = (l + r) / 2;
	if (x <= mid) update(id * 2, l, mid, x, k);
	else update(id * 2 + 1, mid + 1, r, x, k);
	minn[id] = min(minn[id * 2], minn[id * 2 + 1]);
}
signed main() {
	for (int i = 0; i < MAXN; i++) { // 初始化
		st[i].insert(INF); // 防止后面访问 begin 时 RE
		minn[i] = INF; // 线段树
	}
	register int Q, op, x, y, cnt = 0;
	cin >> Q;
	while (Q--) {
		cin >> op >> x;
		if (op == 1) {
			cin >> y;
			y = (1 - y) * x; // 可拆分标记
			cnt++;
			X[cnt] = x;
			Y[cnt] = y;
			st[y].insert(cnt); // 在 set 中存一份
			update(1, 0, 200000, y, *st[y].begin()); // 更新线段树
		}
		else if (op == 2) {
			y = Y[x];
			st[y].erase(x); // 在 set 中删除
			update(1, 0, 200000, y, *st[y].begin()); // 更新线段树
		}
		else {
			vector<pair<int, int> > ans;
			while (x) {
				int now = query(1, 0, 200000, 0, x);
				if (now > cnt) break; // 没有可走的组
				int nowx = X[now];
				int nowy = Y[now];
				if (nowy == 0) {
					if (nowx > x) { // 当前的散装人类可以塞满车
						ans.push_back({now, x});
						X[now] -= x;
						x = 0;
					}
					else { // 车可以装下当前组的散装人类
						ans.push_back({now, nowx});
						X[now] = 0;
						x -= nowx;
						st[nowy].erase(now); // 删掉这个组
						update(1, 0, 200000, nowy, *st[nowy].begin());
					}
				}
				else { // 车可以装下当前组
					ans.push_back({now, nowx});
					X[now] = 0;
					x -= nowx;
					st[nowy].erase(now); // 删掉这个组
					update(1, 0, 200000, nowy, *st[nowy].begin());
				}
			}
			cout << ans.size() << endl;
			for (pair<int, int> i : ans)
				cout << i.first << " " << i.second << endl;
		}
	}
	return 0;
}
```

---

## 作者：SolIII (赞：3)

## 前言

`2024/9/30 upd：更新简化题意`

[更好的阅读体验](https://www.luogu.com.cn/article/urkscum6)

模拟赛的 T3，因为没题解调了好久，现在自己写一个造福人民。

## 题目分析

### 简化题意

~~（这个简化题意为什么和原题一样长）~~

有一个空序列，有 $q$ 次操作，共有以下三种操作：

1. `join` 将一个新的正整数加入到序列尾，其编号为它被加入时的 `join` 操作的数量。每个数有一个属性 $w$。若 $w$ 为 $0$，则该整数不可分；若 $w$ 为 $1$，则该整数可分。

2. `leave` 移除编号为 $i$ 的整数。

3. `board` 给定 $b$。从第一个整数 $s_1$ 开始依次考虑，直到考虑完整个序列或 $b$ 为零。若 $b \ge s_i$，则 $b \gets b - s_i$ 并将 $s_i$ 移出序列；若 $b < s_i$ 且 $s_i$ 可分，则 $s_i \gets s_i - b$ 并 $b \gets 0$；否则考虑下一个整数。

   考虑完后，输出所有被移除的整数和被修改的整数。

给出所有操作，求每次操作 $3$ 的询问。

### 思路

考虑 $s \le 10$ 的情况：可以开 $11$ 个桶子分别存可以分开的团队和不可以分开的大小为 $1$ 到大小为 $10$ 的团队。对于每个 `join` 操作，直接将其加入到对应的桶子里；对于每个 `leave` 操作，直接将离开的团队从其所对应的桶子中删掉；对于每个 `board` 操作，令车中剩下的空间为 $b$，重复在能分开的团队的桶子和大小为 $1$ 到 $b$ 的桶子中找排在最前面的团队并让它（或它的一部分）上车，直到车满或无人可上。

对于 $1 \le s \le 200000$ 的情况下，上述做法如果暴力找排在最前面的团队的话必定超时，考虑对其优化。

发现这一部分所在做的事其实是在找每个桶子中最小数构成的数列的区间最小值（可以将其想象为每个桶子中的团队都按大小从小到大的顺序从上到下摆放，要从这 $s + 1$ 个桶子的最顶部的团队中找到一个最小的，它就是所有团队中排在最前面的那一个）。也就是说可以用线段树将总复杂度优化为 $O(n \log n)$。

然后就是正解了。

## 参考代码

蒟蒻的码风有些烂，巨佬们请将就着看。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define LL long long    // 不开 long long 见祖宗
// 方便起见，重定义了线段树左子节点和右子节点的编号
#define leftson u << 1
#define rightson (u << 1) + 1
const LL NR = 2e5;
const LL inf = 1e18;     //无穷大，某个桶子中尚无团队时其在线段树上对应的节点的值就是 inf
// 线段树板子，不做过多解释
struct Node{
    LL l, r;
    LL Min, add;
};
struct Segtree{
    Node tr[4 * NR + 10];
    LL n;
    LL root;
    void pushup(LL u){
        tr[u].Min = min(tr[leftson].Min, tr[rightson].Min);
    }
    void pushdown(LL u){
        if(tr[u].add){
            tr[leftson].add += tr[u].add;
            tr[leftson].Min += tr[u].add;
            tr[rightson].add += tr[u].add;
            tr[rightson].Min += tr[u].add;
            tr[u].add = 0;
        }
    }
    void modify(LL u, LL l, LL r, LL d){
        if(l <= tr[u].l && r >= tr[u].r){
            tr[u].Min += (LL)d;
            tr[u].add += d;
            return;
        }
        pushdown(u);
        LL mid = (tr[u].l + tr[u].r) >> 1;
        if(l <= mid) modify(leftson, l, r, d);
        if(r > mid) modify(rightson, l, r, d);
        pushup(u);
    }
    LL query(LL u, LL l, LL r){
        if(l <= tr[u].l && r >= tr[u].r){
            return tr[u].Min;
        }
        pushdown(u);
        LL mid = (tr[u].l + tr[u].r) >> 1;
        pushup(u);
        LL ret = inf;
        if(l <= mid) ret = min(ret, query(leftson, l, r));
        if(r > mid) ret = min(ret, query(rightson, l, r));
        return ret;
    }
    void build(LL u, LL l, LL r){
        if(l == r){
            tr[u] = Node{l, r, inf, 0};
            return ;
        }
        tr[u].l = l;
        tr[u].r = r;
        LL mid = (l + r) >> 1;
        build(leftson, l, mid);
        build(rightson, mid + 1, r);
        pushup(u);
    }
};
Segtree seg;
struct Team{    // 输出答案用，表示编号为 id 的团队走了 x 个人
    LL x;
    bool flag;
    LL id;
};
vector<Team> v;      // 用来统计答案
LL sz[NR + 10];      // 表示团队 i 还剩下 sz[i] 个人
LL pos[NR + 10];     // 表示团队 i 被存在了第 pos[i] 个桶子里
set<LL> st[NR + 10]; // 桶子
void leave(LL id){          //团队离开队列时与团队全部上车后需要将其删除
    st[pos[id]].erase(id);  // 从桶子中删除编号为 id 的团队
    seg.modify(1, pos[id], pos[id], (st[pos[id]].empty() ? inf : *st[pos[id]].begin()) - seg.query(1, pos[id], pos[id])); // 更新这个桶子在线段树中对应的节点，注意若桶子为空，一定要在线段树中将其设为 inf
}

int main(){
    seg.build(1, 0, NR); // 建树
    LL T;
    scanf("%lld", &T);  // 读入
    LL cnt = 0;
    while(T--){
        LL op;
        scanf("%lld", &op);
        if(op == 1){ // join
            LL x, y;
            scanf("%lld%lld", &x, &y);
            cnt++;
            sz[cnt] = x;
            pos[cnt] = x;
            if(y) pos[cnt] = 0;
            st[pos[cnt]].emplace(cnt);
            seg.modify(1, pos[cnt], pos[cnt], *st[pos[cnt]].begin() - seg.query(1, pos[cnt], pos[cnt]));
        }
        else if(op == 2){ // leave
            LL x;
            scanf("%lld", &x);
            leave(x);
        }
        else if(op == 3){ // board
            v.clear();    // 多测要清空
            LL x;
            scanf("%lld", &x);
            while(x > 0){                               // 模拟上车
                LL tmp = seg.query(1, 0, x);            // 找到最靠前的团队
                if(tmp == inf) break;                   // 没有则 break
                LL del = min(x, sz[tmp]);               // 注意有的团队可以拆分，只要 x < sz[tmp] 时，团队一定都可以拆分(因为找的时候就保证了只要是不可拆的团队，其大小一定都小于 x)
                v.emplace_back(Team{del, false, tmp});  // 计入答案
                x -= del;                               // 更新车上剩余空间
                sz[tmp] -= del;                         // 更新团队没上车的人的数量
                if(sz[tmp] == 0) leave(tmp);            // 若全部上车，将空的团队删掉并更新这个桶子中排在最前面的
            }
            printf("%lld\n", (LL)v.size());   // 输出答案
            if(v.size() == 0) continue;
            for(auto i : v){
                printf("%lld %lld\n", i.id, i.x);
            }
        }
    }
    return 0;
}
```

---

## 作者：George222 (赞：2)

假设现在有一辆载客量为 $b$ 的观光车，现在有人数为 $num$ 的团队即将上车，根据题意我们可以知道如果想上这辆车有两种情况：

$
\begin{cases}
    w = 0 & num \le b \\
    w = 1
\end{cases}
$

对于 `board` 操作我们需要按编号从小到大输出，所以我们需要找的“上车的团队”满足上述条件编号最靠前的团队。

令每个允许分开的团队的值为 $0$，不允许分开的值为 $num$，维护一个集合 $S$，$S_i$ 中存储所有权值为 $i$ 的团队；维护一个线段树，将 $S_i$ 最靠前的值放置于线段树上的位置，寻找权值 $0 \sim num$ 中最靠前（$minn$）的位置即可。

代码如下：

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long
int n;
int op, x, y;

struct Node
{
	int l, r;
	int minn;
} tree[800005];
void pushup(int now)
{
	tree[now].minn = min(tree[now << 1].minn, tree[now << 1 | 1].minn); 
}
void build(int now, int l, int r)
{
	tree[now].l = l, tree[now].r = r;
	if (l == r)
	{
		tree[now].minn = INT_MAX;
		return ;
	}
	int mid = (l + r) >> 1;
	build(now << 1, l, mid);
	build(now << 1 | 1, mid + 1, r);
	pushup(now);
}
void modify1(int now, int x, int num)
{
	if (tree[now].l == x && tree[now].r == x)
		tree[now].minn = num;
	else
	{ 
		int mid = (tree[now].l + tree[now].r) >> 1;
		if (x <= mid)
			modify1(now << 1, x, num);
		else
			modify1(now << 1 | 1, x, num);
		pushup(now);
	}
	return ;
}
int check(int now, int l, int r)
{
	if (tree[now].l == l && tree[now].r == r)
		return tree[now].minn;
	int mid = (tree[now].l + tree[now].r) >> 1;
	int res = INT_MAX;
	if (r <= mid)
		return check(now << 1, l, r);
	else if (l > mid)
		return check(now << 1 | 1, l, r);
	else
		return min(check(now << 1, l, mid), check(now << 1 | 1, mid + 1, r));
}
int num[200005];
int id[200005];
set<int> S[200005];
void del(int x)
{
	S[id[x]].erase(x);
	if (S[id[x]].empty())
		modify1(1, id[x], INT_MAX);
	else
		modify1(1, id[x], *S[id[x]].begin());
}

signed main()
{
	cin >> n;
	build(1, 0, 200000);
	int i = 0;
	while (n--)
	{
		cin >> op >> x;
		if (op == 1)
		{
			i++;
			cin >> y;
			if (y)
				y = 0;
			else
				y = x;
			S[y].insert(i);
			modify1(1, y, *S[y].begin());
			id[i] = y, num[i] = x;
		}
		if (op == 2)
			del(x);
		if (op == 3)
		{
			vector<pair<int, int>> ans;
			while (x)
			{
				int t = check(1, 0, min(x, 1ll * 200000));
				if (t == INT_MAX)
					break;
				int tt = min(x, 1ll * num[t]);
				x -= tt, num[t] -= tt;
				ans.push_back({t, tt});
				if (!num[t])
					del(t);
			}
			cout << ans.size() << "\n";
			for (auto team : ans)
				cout << team.first << " " << team.second << "\n";
		}
	}
	return 0;
}
```

---

## 作者：Genius_Star (赞：0)

### 思路：

考虑势能，一个团队，要么一次全走完，要么进行多次分裂，且显然分裂总次数最多是 $O(q)$ 级别的，因为需要分裂只可能是把观光车填满。

于是我们只需要找到上车的团队，进行清空与修改，复杂度就是对的；现在问题是如何仅找到上车的团队。

我们考虑去找下一个上车的团队，显然需要满足以下条件：

- 若允许分开，大小任意。

- 若不允许分开，大小 $s \le b$。

我们需要找到满足上述条件中最靠前的团队，考虑使用线段树维护，令允许分开的权值为 $0$，不允许分开的权值为其大小 $s$；那么相当于询问所有权值 $\le b$ 中最靠前的位置。

维护一个 $S_x$ 表示权值为 $x$ 的团队集合，插入删除很容易维护，然后将 $S_x$ 中编号最小（即最靠前）的位置放在线段树的 $x$ 上。

时间复杂度为 $O(N \log N)$。

### 完整代码：

```cpp
 #include<bits/stdc++.h>
#define lowbit(x) x & (-x)
#define ls(k) k << 1
#define rs(k) k << 1 | 1
#define fi first
#define se second
#define add(x, y) ((x + y >= mod) ? (x + y - mod) : (x + y))
#define dec(x, y) ((x - y < 0) ? (x - y + mod) : (x - y))
#define ctz(x) __builtin_ctz(x)
#define popcnt(x) __builtin_popcount(x)
#define open(s1, s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
using namespace std;
typedef __int128 __;
typedef long double lb;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 2e5 + 10, INF = 1e9;
inline ll read(){
    ll x = 0, f = 1;
    char c = getchar();
    while(c < '0' || c > '9'){
        if(c == '-')
          f = -1;
        c = getchar();
    }
    while(c >= '0' && c <= '9'){
        x = (x << 1) + (x << 3) + (c ^ 48);
        c = getchar();
    }
    return x * f;
}
inline void write(ll x){
	if(x < 0){
		putchar('-');
		x = -x;
	}
	if(x > 9)
	  write(x / 10);
	putchar(x % 10 + '0');
}
struct Node{
	int l, r;
	int Min;
}X[N << 2];
ll n, op, x, y, now;
int a[N], id[N];
set<int> S[N];
inline void pushup(int k){
	X[k].Min = min(X[k << 1].Min, X[k << 1 | 1].Min);
}
inline void build(int k, int l, int r){
	X[k].l = l, X[k].r = r;
	if(l == r){
		X[k].Min = INF;
		return ;
	}
	int mid = (l + r) >> 1;
	build(k << 1, l, mid);
	build(k << 1 | 1, mid + 1, r);
	pushup(k);
}
inline void update(int k, int i, int v){
	if(X[k].l == i && i == X[k].r){
		X[k].Min = v;
		return ;
	}
	int mid = (X[k].l + X[k].r) >> 1;
	if(i <= mid)
	  update(k << 1, i, v);
	else
	  update(k << 1 | 1, i, v);
	pushup(k);
}
inline int ask(int k, int l, int r){
	if(X[k].l == l && r == X[k].r)
	  return X[k].Min;
	int mid = (X[k].l + X[k].r) >> 1;
	if(r <= mid)
	  return ask(k << 1, l, r);
	else if(l > mid)
	  return ask(k << 1 | 1, l, r);
	else
	  return min(ask(k << 1, l, mid), ask(k << 1 | 1, mid + 1, r));
}
inline void del(int x){
	S[id[x]].erase(x);
	if(S[id[x]].empty())
	  update(1, id[x], INF);
	else
	  update(1, id[x], *S[id[x]].begin());
}
bool End;
int main(){
	n = read();
	build(1, 0, 2e5);
	while(n--){
		op = read(), x = read();
		if(op == 1){
			++now;
			y = read();
			if(y)
			  y = 0;
			else
			  y = x;
			S[y].insert(now);
			update(1, y, *S[y].begin());
			id[now] = y, a[now] = x;
		}
		else if(op == 2)
		  del(x);
		else{
			vector<pair<int, int>> ans;
			while(x){
				int t = ask(1, 0, min(x, 200000ll));
				if(t == INF)
				  break;
				int h = min(x, (ll)a[t]);
				x -= h, a[t] -= h;
				ans.push_back({t, h});
				if(!a[t])
				  del(t);
			}
			write(ans.size());
			putchar('\n');
			for(auto t : ans){
				write(t.fi);
				putchar(' ');
				write(t.se);
				putchar('\n');
			}
		}
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：ddxrS_loves_zxr (赞：0)

首先，每个不愿意分开的团队至多只会在查询中被删除一次。每个愿意被分开的团队只有部分被删除的情况在每个查询最多只会出现一次。

所以对于每次查询我们可以依次找到所有的团队。

具体实现时，可以使用线段树来维护两个信息：区间中，人数最少的团队数量以及是否有愿意分开的团队。

这样每次找团队就只需要找编号最小的，人数符合条件或愿意分开的团队即可。

时间复杂度 $O(n\log n)$。

```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll N = 2e5 + 5, inf = 0x3f3f3f3f3f3f3f3f;
int q, n, id;
ll tr[N << 2], flg[N << 2], a[N];
void change(int p, int l, int r, int x, ll y, int z) {
    int mid = l + r >> 1;
    if(l == r) return tr[p] = y, flg[p] = z, void();
    (x <= mid ? change(p << 1, l, mid, x, y, z) : change(p << 1 | 1, mid + 1, r, x, y, z));
    tr[p] = min(tr[p << 1], tr[p << 1 | 1]), flg[p] = flg[p << 1] | flg[p << 1 | 1];
}
int Find(int p, int l, int r, ll s) {
    if(tr[p] > s && !flg[p]) return -1;
    int mid = l + r >> 1;
    if(l == r) return l;
    if(tr[p << 1] <= s || flg[p << 1]) return Find(p << 1, l, mid, s);
    else return Find(p << 1 | 1, mid + 1, r, s);
}
int main() {
#ifdef ddxrS
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    memset(tr, 0x3f, sizeof tr);
    cin>>q; n = q;
    while(q--) {
        ll opt, x, y;
        cin>>opt>>x;
        if(opt == 1) cin>>y, a[++id] = x, change(1, 1, n, id, x, y);
        else if(opt == 2) change(1, 1, n, x, inf, 0), a[x] = 0;
        else {
            vector<pair<int, int> > ans;
            int p = Find(1, 1, n, x);
            while(p != -1 && x) {
                ll tmp = min(a[p], x);
                ans.push_back({p, tmp});
                if(tmp < a[p]) a[p] -= tmp, change(1, 1, n, p, a[p], 1), x = 0;
                else a[p] = 0, change(1, 1, n, p, inf, 0), x -= tmp;
                p = Find(1, 1, n, x);
            }
            cout<<ans.size()<<'\n';
            for(auto i : ans) cout<<i.first<<' '<<i.second<<'\n';
        }
    }
    return 0;
}
```

---

