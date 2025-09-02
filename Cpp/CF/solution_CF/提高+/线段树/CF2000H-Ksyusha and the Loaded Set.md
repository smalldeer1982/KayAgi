# Ksyusha and the Loaded Set

## 题目描述

Ksyusha 决定创办一家游戏开发公司。为了在竞争中脱颖而出并取得成功，她决定编写一个属于自己的游戏引擎。这个引擎需要支持一个初始包含 $n$ 个不同整数 $a_1, a_2, \ldots, a_n$ 的集合。

接下来，这个集合将依次进行 $m$ 次操作。可进行的操作类型如下：

- 向集合中插入一个元素 $x$；
- 从集合中移除一个元素 $x$；
- 查询集合的 $k$-负载。

集合的 $k$-负载定义为最小的正整数 $d$，使得整数 $d, d + 1, \ldots, d + (k - 1)$ 全都不在这个集合中。例如，集合 $\{3, 4, 6, 11\}$ 的 $3$-负载是 $7$，因为数字 $7, 8, 9$ 不在集合里，并且没有更小的值满足这个条件。

由于 Ksyusha 忙于管理工作，所以需要你来帮忙实现这个引擎的操作支持。

## 样例 #1

### 输入

```
3
5
1 2 5 905 2000000
15
- 2
? 2
? 1
- 1
? 1
+ 4
+ 2
? 2
+ 6
- 4
+ 7
? 2
? 3
? 4
? 2000000
5
3 4 5 6 8
9
? 5
- 5
? 5
+ 1
? 2
- 6
- 8
+ 6
? 5
5
6 7 8 9 10
10
? 5
- 6
? 4
- 10
+ 5
- 8
+ 3
+ 2
- 3
+ 10```

### 输出

```
2 2 1 6 3 8 8 2000001 
9 9 9 7 
1 1```

# 题解

## 作者：Ke_scholar (赞：2)

[可能有更好的阅读体验](https://www.cnblogs.com/Kescholar/p/18360076#h-ksyusha-and-the-loaded-set)

# [Ksyusha and the Loaded Set](https://codeforces.com/contest/2000/problem/H)

## 思路

考虑题中所给 $k$ 的性质，其实就是在集合中从左往右找到第一段两两相差长度至少为 $k$ 的位置。

所以我们可以维护一个权值线段树，对于集合中出现的数，我们可以在线段树中标记为 $1$，那么两个 $1$ 之间相差的 $0$ 的个数不就等于两数相差的长度吗，那我们只用维护这个区间中最大的 $0$ 的个数即可，想到这，其实就可以发现这是个比较板的维护 $0/1$ 串中最大连续 $0$ 的个数线段树，对于找长度为 $k$ 的位置，我们可以线段树上二分，因为是从左往右找，所以找完左边还得看下中间是否符合，即判断左区间后缀连续 $0\ +$右区间前缀连续 $0$ 是否 $\ge k$，最后找右区间。

每次可以维护一个 $set$ 代表集合中的数，最后将线段树清空，减少每次新开线段树带来的时间和空间上的损耗。

## 代码

```c++
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

template<class Node>
struct SegmentTree {
#define lc u<<1
#define rc u<<1|1
    const int n, N;
    vector<Node> tr;

    SegmentTree(): n(0) {}
    SegmentTree(int n_): n(n_), N(n * 4 + 10) {
        tr.reserve(N);
        tr.resize(N);
        build(1, 1, n);
    }

    void build(int u, int l, int r) {
        tr[u].l = l, tr[u].r = r;
        if (l == r) {
            tr[u] = {l, r, 1, 1, 1};
            return ;
        }
        i64 mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushup(tr[u], tr[lc], tr[rc]);
    };

    void pushup(Node& U, Node& L, Node& R) { //上传
        U.l = L.l, U.r = R.r;

        if (L.presum == L.r - L.l + 1) {
            U.presum = L.presum + R.presum;
        } else {
            U.presum = L.presum;
        }

        if (R.lastsum == R.r - R.l + 1) {
            U.lastsum = L.lastsum + R.lastsum;
        } else {
            U.lastsum = R.lastsum;
        }

        U.Maxsum = max({L.Maxsum, R.Maxsum, L.lastsum + R.presum});
    }

    void modify(int u, int pos) {
        if (tr[u].l >= pos && tr[u].r <= pos) {
            tr[u].Maxsum ^= 1;
            tr[u].presum = tr[u].lastsum = tr[u].Maxsum;
            return ;
        }
        int mid = (tr[u].l + tr[u].r) >> 1;
        if (pos <= mid)
            modify(lc, pos);
        else
            modify(rc, pos);
        pushup(tr[u], tr[lc], tr[rc]);
    }

    int query(int u, int k) { //区查
        if (tr[u].l == tr[u].r)
            return tr[u].l;
        if (tr[lc].Maxsum >= k)
            return query(lc, k);

        if (tr[lc].lastsum + tr[rc].presum >= k) {
            return tr[lc].r - tr[lc].lastsum + 1;
        }

        return query(rc, k);
    }
};

struct Node { //线段树定义
    i64 l, r;
    i64 presum, lastsum, Maxsum;
};

constexpr int N = 2e6 + 10, M = N - 10;
SegmentTree<Node> tr(M);

void solve() {

    set<int> s;

    int n;
    cin >> n;

    for (int i = 1; i <= n; i ++) {
        int x;
        cin >> x;
        s.insert(x);
        tr.modify(1, x);
    }

    int m;
    cin >> m;
    while (m--) {
        char op;
        int x;
        cin >> op >> x;
        if (op == '+') {
            s.insert(x);
            tr.modify(1, x);
        } else if (op == '-') {
            s.erase(x);
            tr.modify(1, x);
        } else {
            if (x > tr.tr[1].Maxsum) {
                cout << M - tr.tr[1].lastsum + 1 << ' ';
            } else {
                cout << tr.query(1, x) << ' ';
            }
        }
    }

    cout << '\n';

    for (auto &x : s) {
        tr.modify(1, x);
    }

}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }

    return 0;
}

```

---

## 作者：CoderMeow (赞：2)

# CF2000H 题解

## 前言

感觉挺有意思的一道题；赛时想到了基本正确的做法，但可惜最后并没能调出来。个人感觉整体思路比较容易得到，但细节不少。

## 题意简述

维护一个正整数组成的集合，需支持以下操作：

1. 向集合中插入（原先不存在的）数 $x$
2. 从集合中删除（原先存在的）数 $x$
3. 查询相邻 $k$ 个不在集合中的正整数组成的数段的起点（多个满足条件的正整数段中取起点最小者）

## 数据结构

观察到集合元素值域比较小，$O((n+q)\log V)$ 的复杂度可过，同时集合中元素不会有重复的，可以想到对于 $1 \sim 2\cdot 10^6$ 这些数在集合中与否建立线段树，维护连续不在集合中的数的段的最长长度。插入和删除都是单点修改，查询操作可递归寻找答案。

具体地，对每个线段树节点维护其管辖区间内从左端开始的最长不在集合中的数段长度 $lMax$，到右端位置的的最长段长度 $rMax$，以及整个区间内的最长段长度 $cMax$。单点修改时，对所修改的点的三个值全赋 $0$（操作 1）或全赋 $1$（操作 2）。向上合并时，$cMax$ 在左半段内的最长段的长度、右半段内的最长段的长度、左右半段相接处的左半段右端最长段和右半段左端最长段所拼成的段的长度中取最大值，而 $lMax$ 和 $rMax$ 则简单分讨一下：若左半段内有在集合中的数则 $lMax$ 直接取左半段的 $lMax$，否则取左半段长度与右半段的 $lMax$ 之和；若右半段内有在集合中的数则 $rMax$ 直接取右半段的 $rMax$，否则取右半段长度与左半段的 $rMax$ 之和。形式化地，有
$$\left\{\begin{aligned} 
    &cMax=\max\{cMax_{left}, cMax_{right}, rMax_{left}+lMax_{right}\}, \\  
    &lMax=\left\{\begin{aligned} 
        &lMax_{left}, & lMax_{left}<length_{left}, \\  
        &lMax_{left}+lMax_{right}, & otherwise,
    \end{aligned}\right. \\
    &rMax=\left\{\begin{aligned} 
        &rMax_{right}, & rMax_{right}<length_{right}, \\  
        &rMax_{right}+lMax_{right}, & otherwise
    \end{aligned}\right. 
\end{aligned}\right. $$
（其中 $\text{-}Max_{left/right}$ 表示当前线段树节点左/右儿子的对应值，$length_{left/right}$ 为左/右儿子管辖区间的长度）。该过程具体如下图。
![cMax](https://cdn.luogu.com.cn/upload/image_hosting/rwxu5axl.png)

![lMax](https://cdn.luogu.com.cn/upload/image_hosting/oqgmd22j.png)

![rMax](https://cdn.luogu.com.cn/upload/image_hosting/cw6d0d8v.png)

递归查询时，考虑到若有多段满足条件的段取起点最小的，那么对于每一个当前线段树节点，若左半段内的最长段长度 $\ge k$ 则递归至左儿子，否则若左半段右端与右半段左端所拼成的段长 $\ge k$ 则答案为该拼成的段的起点，再否则则递归至右儿子。实现上，可以对于每个节点先判断是否有 $cMax\ge k$，若否，则取其 $rMax$ 对应段的起点；若是，则 $cMax_{left} \ge k$ 或 $rMax_{left} + lMax_{right} \ge k$ 则递归至左儿子，否则递归至右儿子。形式化地，对于节点 $p$ 有
$$kLoad(p)=\left\{\begin{aligned} 
    & kLoad(leftChild), & cMax_{left} \ge k\ \vee\ rMax_{left} + lMax_{right} \ge k, \\
    & kLoad(rightChild), & cMax_{right} \ge k, \\
    & end_p - rMax + 1, &otherwise. 
\end{aligned}\right. $$
过程具体如下图。
![k-load](https://cdn.luogu.com.cn/upload/image_hosting/fcy9lc5z.png)

## 实现

```cpp
# include <iostream>
# include <set>

using namespace std;

const int N = 2000000;

struct node {
    int lMax, cMax, rMax;
};

set<int> inSet;
node tree[N * 4];

void build(int p, int s, int t) {
    if (s == t) {
        tree[p] = {1, 1, 1};
        return;
    }

    int mid = s + ((t - s) >> 1);

    build(2 * p + 1, s, mid);
    build(2 * p + 2, mid + 1, t);

    tree[p] = {
        tree[2 * p + 1].cMax + tree[2 * p + 2].cMax,
        tree[2 * p + 1].cMax + tree[2 * p + 2].cMax,
        tree[2 * p + 1].cMax + tree[2 * p + 2].cMax
    };
}

int x;
bool mode;
void update(int p, int s, int t) {
    if (s == t) {
        tree[p] = {mode, mode, mode};
        return;
    }

    int mid = s + ((t - s) >> 1);

    if (x <= mid) {
        update(2 * p + 1, s, mid);
    } else {
        update(2 * p + 2, mid + 1, t);
    }

    tree[p] = {
        (tree[2 * p + 1].cMax == (mid - s + 1)) ? (tree[2 * p + 1].cMax + tree[2 * p + 2].lMax) : tree[2 * p + 1].lMax,
        max(tree[2 * p + 1].rMax + tree[2 * p + 2].lMax, max(tree[2 * p + 1].cMax, tree[2 * p + 2].cMax)),
        (tree[2 * p + 2].cMax == (t - mid)) ? (tree[2 * p + 2].cMax + tree[2 * p + 1].rMax) : tree[2 * p + 2].rMax
    };
}

int k;
int kLoad(int p, int s, int t) {
    int mid = s + ((t - s) >> 1);
    if (tree[p].cMax >= k) {
        if ((tree[2 * p + 1].cMax >= k) || (tree[2 * p + 1].rMax + tree[2 * p + 2].lMax >= k)) {
            return kLoad(2 * p + 1, s, mid);
        } else {
            return kLoad(2 * p + 2, mid + 1, t);
        }
    } else {
        return t - tree[p].rMax + 1;
    }
}

int main() {
    int t;
    scanf("%d", &t);

    build(0, 0, N - 1);

    while (t--) {
        int n;
        scanf("%d", &n);

        while (n--) {
            scanf("%d", &x);
            x -= 1;

            mode = false;
            update(0, 0, N - 1);

            inSet.insert(x);
        }

        int m;
        scanf("%d", &m);

        while (m--) {
            char opt;
            cin >> opt;

            if (opt == '+') {
                scanf("%d", &x);
                x -= 1;

                mode = false;
                update(0, 0, N - 1);

                inSet.insert(x);
            }
            if (opt == '-') {
                scanf("%d", &x);
                x -= 1;

                mode = true;
                update(0, 0, N - 1);

                inSet.erase(x);
            }
            if (opt == '?') {
                scanf("%d", &k);

                if (tree[0].lMax >= k) {
                    printf("1 ");
                } else {
                    printf("%d ", kLoad(0, 0, N - 1) + 1);
                }
            }
        }

        printf("\n");

        for (auto y: inSet) {
            x = y;
            mode = true;
            update(0, 0, N - 1);
        }

        inSet.clear();
    }

    return 0;
}

```

该代码中下标从 $0$ 开始利用，所以往线段树里放的时候有一个减 $1$（把 $1\sim 2000000$ 变为 $0\sim 1999999$）。

函数 `update` 中，$mode=0$ 则为插入，否则为删除。

多测的清空中只将最后剩在集合内的数（直接用 set 维护）一一删除，如果每次重新 `build` 显然复杂度会爆。

---

## 作者：Super_Cube (赞：1)

# Solution

询问的实质是从小到大找到第一个相邻两数差大于 $k$ 的位置。

维护一颗权值线段树，有值的地方置为 $1$，那就是找到最靠前的连续 $0$ 个数不小于 $k$ 的位置。线段树上维护三个信息：左边连续的 $0$ 个数，右边连续的 $0$ 个数，区间内最多的连续 $0$ 个数。询问时在线段树上二分，若左子树的最大值不小于 $k$ 就往左走；若左子树的右连续 $0$ 个数加上右子树的左连续 $0$ 个数不小于 $k$，那这一段就是答案；否则往右子树走。 

不过不能每组数据重新建树，会起飞（当然你可以打离散化，但是我不喜欢）。一个不太有趣的方法是用 `set` 维护还存在的值，在每组数据末尾把它们在线段树上置 $0$；或者直接动态开点解决问题。

---

## 作者：BrotherCall (赞：1)

给一个好想的 $O(m\log^2V)$ 的做法。

考虑一棵值域线段树，若数字 $x$ 在集合中，则令该位为 $0$；若 $x$ 不在集合中，则令该位为 $1$。

题意即转换为，找到最左边出现连续 $k$ 个 $1$ 的位置。

不难发现，对于一个位置 $s$，$[1 , s]$ 中最长连续 $1$ 的长度是随 $s$ 单调不降的。

所以我们只需要找到最左边满足 $[1,s]$ 中最长连续段长度为 $k$ 的位置，这个直接二分答案即可。

至于如何维护 $[1,s]$ 最长的连续 $1$ 的长度，线段树记三个变量即可：最左端有连续多少个 $1$，最右端有连续多少个 $1$，整个区间最长连续段长度。好像有个经典题：[小白逛公园](https://www.luogu.com.cn/problem/P4513)。

有个小细节是，多测每次开一个 $4\times10^6$ 的值域线段树空间会炸，所以只开一个线段树，每一轮询问结束之后把操作逆着还原回去就行了，复杂度也就只多一倍的常数。

[提交记录](https://codeforces.com/contest/2000/submission/281697664)。

---

## 作者：Wuming_Shi (赞：1)

# CF2000H 题解
（蒟蒻解法，可能比较麻烦）
## 题意
维护一个正整数集合，支持以下操作：
1. 插入、删除数字。
2. 给定 $k$，询问最小的整数 $d$ 满足 $[d,d+k-1]$ 均不在集合内。
## 思路
### 询问
可以想到差分。具体地：维护每个数与其前驱的差分，每次询问即在差分值 $\ge k$ 的位置中找数值最小的；若不存在这样的差分值，则答案为集合中最大值 $+1$。可使用平衡树或权值线段树实现。
### 修改
对于修改，发现插入或删除一个数 $x$，只会对差分数组产生较小的改变，即：添加/删除 $x$ 与其前驱的差分，修改 $x$ 的后继的差分值。

考虑使用平衡树或权值线段树维护原数组，支持插入、删除、查前驱、查后继。

#### 具体过程：

设需要添加/删除的数字为 $x$，其前驱为 $q$， 后继为 $h$。

添加 $x$ 时，在差分数组中插入 $x-q$ 和 $h-x$，删除$h-q$。

删除 $x$ 时，在差分数组中删除 $x-q$ 和 $h-x$，插入 $h-q$。

## 实现
平衡树时间复杂度 $O(m\log{n})$。权值线段树复杂度 $O(m\log{V})$。\
[Code](https://www.luogu.com.cn/paste/6mvlg377)

---

## 作者：aeiouaoeiu (赞：1)

记录 $a_i+1$ 最多能到 $b_i$-load。

先考虑如何维护 $b$。发现每次插入/删除只会影响到最大的比 $x$ 小的数的 $b$ 值，于是可以使用 `std::set` 维护。

知道了 $b$ 值，查询 $k$-load 相当于找到一个 $i$ 使得 $b_i\ge k$ 且 $a_i$ 最小。

先将 $b_i$ 相同的 $a_i$ 扔进同一个 `std::multiset`，这样可以维护使得 $b_i=k$ 的最小的 $a_i$。

然后开一个权值线段树，节点 $[l,r]$ 记录满足 $l\le b_i \le r$ 的最小的 $a_i$，支持单点修改与区间查询，查询 $k$-load 即为查询区间 $[k,2\times 10^6]$ 的最小值。

注意记录 $a_0=0$ 的贡献。注意初始化只需要初始化修改过的值，时间复杂度大概是 $\mathcal{O}(\sum n\log n+m(\log n+\log V))$，其中 $V=2\times 10^6$。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=2000007,ee=1e18;
ll n,m,tar,a[200007];
pair<ll,ll> tmp;
set<pair<ll,ll> > st;
multiset<ll> val[maxn];
char opt;
struct Tree{
	ll val[maxn<<2];
	void init(void){memset(val,0x3f,sizeof(val));}
	void upd(ll l,ll r,ll x,ll z,ll rt){
		//cout<<"+ "<<x<<" "<<z<<"\n";
		if(!x) return;
		if(l==r) return val[rt]=z,void(); ll mid=(l+r)>>1;
		if(x<=mid) upd(l,mid,x,z,rt<<1); else upd(mid+1,r,x,z,rt<<1|1);
		val[rt]=min(val[rt<<1],val[rt<<1|1]);
	}
	ll qry(ll l,ll r,ll x,ll y,ll rt){
		if(x<=l&&r<=y) return val[rt]; ll mid=(l+r)>>1,res=ee;
		if(x<=mid) res=min(res,qry(l,mid,x,y,rt<<1)); if(mid<y) res=min(res,qry(mid+1,r,x,y,rt<<1|1));
		return res;
	}
}tree;
void updP(ll x,ll z){
	val[x].insert(z);
	//cout<<"+ "<<x<<" "<<z<<"\n";
	tree.upd(1,2e6,x,*val[x].begin(),1);
}
void delP(ll x,ll z){
	val[x].erase(val[x].find(z));
	//cout<<"- "<<x<<" "<<*val[x].begin()<<"\n";
	tree.upd(1,2e6,x,*val[x].begin(),1);
}
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0),cin.tie(0);
	ll T=1;
	cin>>T;
	tree.init();
	for(int i=1;i<=2e6;i++) val[i].insert(ee);
	for(;T--;){
		for(auto x:st) delP(x.second,x.first);
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i]; st.clear();
		for(int i=1;i<=n;i++){
			tar=((i!=n)?(a[i+1]-a[i]-1):2e6);
			st.insert(mp(a[i],tar)); updP(tar,a[i]);
		}
		st.insert(mp(0,a[1]-1)); updP(a[1]-1,0);
		cin>>m;
		for(int i=1,x;i<=m;i++){
			cin>>opt>>x;
			if(opt=='+'){
				auto it=st.upper_bound(mp(x,0ll)); auto suf=it; it--;
				if(suf!=st.end()) tar=suf->first-x-1;
				else tar=2e6;
				delP(it->second,it->first);
				tmp=*it,tmp.second=x-tmp.first-1,st.erase(it),st.insert(tmp);
				updP(tmp.second,tmp.first);
				st.insert(mp(x,tar));
				updP(tar,x);
			}else if(opt=='-'){
				auto it=st.lower_bound(mp(x,0ll));
				delP(it->second,it->first);
				st.erase(it);
				it=st.upper_bound(mp(x,0ll)); auto suf=it; it--; tmp=*it;
				if(suf!=st.end()) tar=tmp.second=suf->first-tmp.first-1;
				else tar=tmp.second=2e6;
				delP(it->second,it->first);
				st.erase(it),st.insert(tmp);
				updP(tmp.second,tmp.first);
			}else cout<<tree.qry(1,2e6,x,2e6,1)+1<<" ";
			//for(int i=1;i<=6;i++) cout<<tree.qry(1,2e6,i,i,1)<<" "; cout<<tree.qry(1,2e6,2e6,2e6,1)<<"\n";
			//for(auto x:st) cout<<x.first<<" "<<x.second<<"\n"; cout<<"\n";
		}cout<<"\n";
	}
	return 0;
}
```

---

## 作者：tr1pTreap (赞：0)

简单题。不过有点诈骗。

题面简述：要求你维护一个可以增删的正整数 ```set```，一开始有 $n$ 个元素，对 $m$ 个操作或询问进行回答，每个操作插入或者删除一个数，或者查询**长度为 $k$ 的连续正整数段 $[d,d+k-1]$ 使得任意段内元素不在集合内的最小 $d$** 。

按照经典套路，我们维护集合内相邻元素间的间隙。加入一个数就是把前驱 $a$ 后继 $b$ 的间隙长度 $(a, b)$ 删掉，加入两个以新加入的数 $c$ 为端点的区间 $(a, c)$ 和 $(b, c)$ 。查询就是在长度的集合里二分，第一关键字为长度第二关键字为编号。

然后你发现错完了。因为 $k = 2$ 时 $(4, 2)$ 一对优于 $(3, 9)$ 一对（前面是长度后面是编号）。考虑动态开点线段树维护 ```max``` ，在线段树上更新二分就是正确做法。

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
// #define int long long
const int N=4e5+5,I=1e9;
struct node{
	int ls,rs,mx;
}t[N*4];int tim,rt;
int newnode(){
	t[++tim]={0,0,-I};
	return tim;
}
void update(int &i,int k,int x,int ql,int qr){
	if(!i) i=newnode();
	// cerr<<"going:"<<i<<' '<<k<<' '<<x<<' '<<ql<<' '<<qr<<'\n';
	if(ql==qr){
		t[i].mx=x;
		// cerr<<"to spot!:"<<ql<<'\n';
		return;
	}
	int mid=(ql+qr)/2;
	if(k<=mid) update(t[i].ls,k,x,ql,mid);
	else update(t[i].rs,k,x,mid+1,qr);
	t[i].mx=max(t[t[i].ls].mx,t[t[i].rs].mx);
}
int query(int i,int l,int r,int ql,int qr){
	if(!i) return -I;
	if(l<=ql&&qr<=r) return t[i].mx;
	int mid=(ql+qr)/2,ans=-I;
	if(l<=mid) ans=max(ans,query(t[i].ls,l,r,ql,mid));
	if(r>mid) ans=max(ans,query(t[i].rs,l,r,mid+1,qr));
	return ans;
}
int binfind(int i,int k,int ql,int qr){
	// cerr<<"going:"<<' '<<k<<' '<<ql<<' '<<qr<<'\n';
	if(ql==qr) return ql; // leaf node
	if(!i) return -1; // middle of nothing
	int mid=(ql+qr)/2;
	if(t[i].ls&&t[t[i].ls].mx>=k) return binfind(t[i].ls,k,ql,mid);
	if(t[i].rs&&t[t[i].rs].mx>=k) return binfind(t[i].rs,k,mid+1,qr);
	return -1;
}
int n,m,a[N];
set<int> s;
// set<pair<int,int> > gap;
void PUSH(int x){
	// cerr<<"getin\n";
	auto it=s.lower_bound(x); // <=x
	int aft=*it;
	// assert(it!=s.begin());
	it--;
	int beg=*it;
	// gap.erase(gap.find({aft-beg-1,beg+1}));
	update(rt,beg+1,-I,1,I);
	s.insert(x);
	update(rt,beg+1,x-beg-1,1,I);
	update(rt,x+1,aft-x-1,1,I);
	// gap.insert({x-beg-1,beg+1});
	// gap.insert({aft-x-1,x+1});
}
void POP(int x){
	// cerr<<"getout\n";
	auto it=s.find(x);
	it++;
	int aft=*it;
	it--;it--;
	int beg=*it;it++;
	// gap.erase({x-beg-1,beg+1});
	// gap.erase({aft-x-1,x+1});
	update(rt,beg+1,-I,1,I);
	update(rt,x+1,-I,1,I);
	s.erase(it);
	// gap.insert({aft-beg-1,beg+1});
	update(rt,beg+1,aft-beg-1,1,I);
}
int QUERY(int k){
	// pair<int,int> q={k,0};
	// auto it=gap.lower_bound(q);
	// return it->second;
	return binfind(rt,k,1,I);
}
void groove(){
	cin>>n;
	t[rt=tim=1]={0,0,-I};
	for(int i=0;i<=4*n+5;i++) t[i]={0,0,-I};
	s.clear();
	s.insert(0);
	for(int i=1;i<=n;i++) cin>>a[i],s.insert(a[i]);
	s.insert(I); // sky
	int lst=1;
	for(auto x:s)if(x!=0){
		// gap.insert({x-lst,lst});
		// cerr<<"!:"<<rt<<' '<<lst<<' '<<x-lst<<'\n';
		update(rt,lst,x-lst,1,I);
		lst=x+1;
	}
	// for(auto x:s) cerr<<x+1<<' '<<query(rt,x+1,x+1,1,I)<<'\n';
	cin>>m;
	for(int w=1;w<=m;w++){
		char op;int x;cin>>op>>x;
		// cerr<<"!"<<x<<'\n';
		// if(0){
		// 	cerr<<"The info in segment tree\n";
		// 	for(auto x:s) cerr<<x+1<<' '<<query(rt,x+1,x+1,1,I)<<'\n';
		// }
		if(op=='+') PUSH(x);
		else if(op=='-') POP(x);
		else cout<<QUERY(x)<<' ';
		// if(0){
		// 	cerr<<"The info in segment tree\n";
		// 	for(auto x:s) cerr<<x+1<<' '<<query(rt,x+1,x+1,1,I)<<'\n';
		// }
		// cerr<<"----------------\n";
	}
	cout<<'\n';
	// cerr<<'\n';
}
signed main(){
	// freopen("test.in","r",stdin);
	// freopen("data.out","w",stdout);
	// freopen("diag.txt","w",stderr);
	ios::sync_with_stdio(false),cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while(t--) groove();
	return 0;
}
/*

*/
```

---

## 作者：abensyl (赞：0)

原题：[CF2000H Ksyusha and the Loaded Set](https://www.luogu.com.cn/problem/CF2000H)。

线段树好题。

## 思路

本题是区间问题，相当于求起始下标最小的包含连续 $k$ 个 $0$ 的区间，显然可以用值域线段树维护，在这里，我们将值域设定为 $[0,2\times 10^6]$。

使用线段树维护 $[l,r]$ 内最长连续为 $0$ 的数列的长度，我们显然要找的就是最左侧的 $\geq k$ 的那个。

考虑如何 push up，对于两个区间 $[l,mid]$ 和 $[mid+1,r]$，需要考虑三种情况：

- 最长连续为 $0$ 区间来自 $[l,mid]$；  
- 最长连续为 $0$ 区间来自 $[mid+1,r]$；  
- 最长连续为 $0$ 区间由 $[l,mid]$ 的后缀和 $[mid+1,r]$ 的前缀组合而成。

前两种情况很容易考虑，第三种情况中我们需要维护一个最长连续为 $0$ 的前缀和后缀即可。

对于 $k$ 进行查询时，分以下三种情况：

如果左区间包含一个 $\geq k$ 的连续为 $0$ 的子段，进入左区间查找；
如果后缀和前缀组合成了一个 $\geq k$ 的连续为 $0$ 的子段，返回后缀第一个值的下标；
如果右区间包含一个 $\geq k$ 的连续为 $0$ 的子段，进入右区间查找。

显然会有查不到的情况，那就说明在 $[0,2\times 10^6]$ 中找不到一个长度为 $k$ 的连续全为 $0$ 的子段，这种情况下，答案应该是目前所有数中的最大值加 $1$，所以我们还需要维护一下最大值即可。

注意多测清空。

[代码 + 我的 AC 记录](https://codeforces.com/contest/2000/submission/281921253)。

---

## 作者：huangboning (赞：0)

这题的思路是，使用 $4\times10^6$ 个集合，来保存每个长度的区间的左端点。然后将每个长度的区间的最小左端点存入一颗线段树。对于每次查询，输出区间长度 $\ge k+1$ 的区间左端点中最小的一个。

对于每次 $+$ 操作，相当于将一个大区间分为两个小区间，此时只要在集合中删除大区间左端点，插入两个小区间左端点，并且在线段树中修改新的最小值即可。

对于 $-$ 操作，也是类似的，就不再解释。

代码：

```cpp
#include<bits/stdc++.h>
#define INF 4000010
using namespace std;
struct SegmentTree{//线段树
	int l,r,minl;
}t[INF*4+10];
void build(int x,int l,int r){
	t[x].l=l;
	t[x].r=r;
	if(l==r){
		t[x].minl=INF;
		return;
	}
	int mid=(l+r)/2;
	build(x*2,l,mid);
	build(x*2+1,mid+1,r);
	t[x].minl=INF;
}
void change(int x,int d,int k){
	if(t[x].l==t[x].r){
		t[x].minl=k;
		return;
	}
	int mid=(t[x].l+t[x].r)/2;
	if(d<=mid)change(x*2,d,k);
	else change(x*2+1,d,k);
	t[x].minl=min(t[x*2].minl,t[x*2+1].minl);
}
int ask(int x,int l,int r){
	if(l<=t[x].l&&r>=t[x].r)return t[x].minl;
	int mid=(t[x].l+t[x].r)/2,minl=INF;
	if(l<=mid)minl=min(minl,ask(x*2,l,r));
	if(r>mid)minl=min(minl,ask(x*2+1,l,r));
	return minl;
}
int T,n,a[200010],m,x;
char op;
set<int>s[INF+10],st,se;//se用来保存每个数，st用来清空
int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
	build(1,1,INF);
	cin>>T;
	while(T--){
		cin>>n;
		a[0]=0;
		se.insert(0);
		for(int i=1;i<=n;i++){
			cin>>a[i];
			se.insert(a[i]);
		}
		a[n+1]=INF;
		se.insert(a[n+1]);
		for(int i=1;i<=n+1;i++){
			int k=a[i]-a[i-1];
			if(k==0)continue;
			s[k].insert(a[i-1]+1);//插入左端点
			change(1,k,*s[k].begin());//线段树单点修改
			st.insert(k);
		}
		cin>>m;
		for(int i=1;i<=m;i++){
			cin>>op>>x;
			if(op=='+'){
				se.insert(x);
				set<int>::iterator it=se.find(x);
				int b=*(++it),a=*(--(--it)),k=b-a,k1=x-a,k2=b-x;//a,b为这个数的前驱，后继
				s[k].erase(a+1);
				if(s[k].size())change(1,k,*s[k].begin());
				else change(1,k,INF),st.erase(k);//删去大区间左端点，并修改线段树权值，注意特判集合为空的情况
				s[k1].insert(a+1);
				change(1,k1,*s[k1].begin());//插入小区间左端点，并修改线段树权值
				s[k2].insert(x+1);
				change(1,k2,*s[k2].begin());
				
				st.insert(k1);
				st.insert(k2);//k1,k2加入待清空集合
			}
			else if(op=='-'){//同理，删去小区间左端点，插入大区间左端点
				se.erase(x);
				set<int>::iterator it=se.lower_bound(x);
				int b=*it,a=*(--it),k=b-a,k1=x-a,k2=b-x;
				s[k].insert(a+1);
				change(1,k,*s[k].begin());
				s[k1].erase(a+1);
				if(s[k1].size())change(1,k1,*s[k1].begin());
				else change(1,k1,INF),st.erase(k1);
				s[k2].erase(x+1);
				if(s[k2].size())change(1,k2,*s[k2].begin());
				else change(1,k2,INF),st.erase(k2);
				st.insert(k);
			}
			else cout<<ask(1,x+1,INF)<<" ";//查询大于k的区间里最小的左端点
		}
		cout<<endl;
		se.clear();
		while(st.size()){//遍历待清空集合
			int k=*st.begin();
			s[k].clear();//清空
			st.erase(k);
			change(1,k,INF);//线段树初始化
		}
	}
 }
```

---

## 作者：无名之雾 (赞：0)

大晚上睡觉的时候被同学叫起来看 div3 只看了一眼 H 感觉不难并场切，写篇题解记录之。

## 思路

很常规的区间修改和查询问题。不难想到使用 SGT。

维护三个 lazytag 区间左端点开始的空串长度，区间右端点开始的空串长度，区间最长的空串长度。

对于区间合并，为了维护大区间的最长的空串长度，我们可以对其分类讨论：

- 最长空串区间在左儿子。
- 最长空串区间在右儿子。
- 最长空串区间跨越左右儿子。

在区间合并时，如果出现某个儿子全是空串，以区间端点开始的空串长度也会贯穿个儿子。

找到最靠左的答案位置。递归查找，在进入递归时检查该结点区间内是否存在答案，在以上文的顺序分别检查最长空串长度的三种情况。一旦找到解，立即结束查询。

## 实现细节

因为是多测所以要考虑如何清空。

首先每次新建一个线段树是不现实的。所以考虑开一个 vector 记录哪些位置被用过了。

set 的使用可能更加方便但是多以 log 实在太不优美了。

时间复杂度 $O(n\log V)$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
struct IO{
	inline int read(){
	   int s=0,w=1;
	   char ch=getchar();
	   while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	   while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
	   return s*w;
	}
	inline void write(int x){
	    if(x==0){putchar('0');return;}
		int len=0,k1=x,c[10005];
		if(k1<0)k1=-k1,putchar('-');
		while(k1)c[len++]=k1%10+'0',k1/=10;
		while(len--)putchar(c[len]);
	}
}io;
const int N=4e6+5;
struct SGT{
	int len[N<<2],sum[N<<2],ml[N<<2],mr[N<<2],tag[N<<2];
	int ls(int p){return p<<1;}
	int rs(int p){return p<<1|1;}
	void pushup(int p){
	    if(sum[ls(p)]==len[ls(p)])ml[p]=sum[ls(p)]+ml[rs(p)];
	    else ml[p]=ml[ls(p)];
	    if(sum[rs(p)]==len[rs(p)])mr[p]=sum[rs(p)]+mr[ls(p)];
	    else mr[p]=mr[rs(p)];
	    sum[p]=max(max(sum[ls(p)],sum[rs(p)]),mr[ls(p)]+ml[rs(p)]);
	    return;
	}
	void pushdown(int p){
	    if(tag[p]==0)return;
	    if(tag[p]==1){
	        tag[ls(p)]=tag[rs(p)]=1;
	        sum[ls(p)]=ml[ls(p)]=mr[ls(p)]=0;
	        sum[rs(p)]=ml[rs(p)]=mr[rs(p)]=0;
	    }
	    if(tag[p]==2){
	        tag[ls(p)]=tag[rs(p)]=2;
	        sum[ls(p)]=ml[ls(p)]=mr[ls(p)]=len[ls(p)];
	        sum[rs(p)]=ml[rs(p)]=mr[rs(p)]=len[rs(p)];
	    }
	    tag[p]=0;
	}
	void build(int l,int r,int p){
	    ml[p]=mr[p]=sum[p]=len[p]=r-l+1;
	    tag[p]=0;
	    if(l==r)return;
	    int m=(l+r)>>1;
	    build(l,m,ls(p));
	    build(m+1,r,rs(p));
	}
	void update(int l,int r,int p,int L,int R,int c){
	    pushdown(p);
	    if(L<=l&&r<=R){
	        if(c==1)sum[p]=ml[p]=mr[p]=0;
	        else sum[p]=ml[p]=mr[p]=len[p];
	        tag[p]=c;
	        return;
	    }
	    int m=(l+r)>>1;
	    if(L<=m)update(l,m,ls(p),L,R,c);
	    if(R>m)update(m+1,r,rs(p),L,R,c);
	    pushup(p);
	}
	int query(int l,int r,int p,int x){
	    pushdown(p);
	    if(l==r)return l;
	    int m=(l+r)>>1;
	    if(sum[ls(p)]>=x)return query(l,m,ls(p),x);
	    if(mr[ls(p)]+ml[rs(p)]>=x)return m-mr[ls(p)]+1;
	    else return query(m+1,r,rs(p),x);
	}
}sgt;
void solve(){
	vector<int>use;
    int n=io.read();
    for(int i=1;i<=n;i++){
    	int a=io.read();
    	sgt.update(1,N,1,a,a,1);
    	use.push_back(a);
	}
	int q=io.read();
    while(q--){
        char op;cin>>op;
		int x=io.read();
        if(op=='+'){
        	sgt.update(1,N,1,x,x,1);
        	use.push_back(x);
        }
        else if(op=='-')sgt.update(1,N,1,x,x,0);
        else cout<<sgt.query(1,N,1,x)<<" ";
    }
    puts("");
    for(int i=0;i<use.size();i++)sgt.update(1,N,1,use[i],use[i],0);
}
signed main(){
	sgt.build(1,N,1);
	int t=io.read();
	while(t--)solve();
	return 0;
}
```

---

## 作者：Anamnesis (赞：0)

一种不需要在线段树上做复杂操作的做法（显然 在一棵权值线段树上直接处理题目所求是比较麻烦的）。只需要一棵单点修改、区间查最小值线段树。

注意到每次询问是想找到一个 $len=r-l+1\geq k$ 的区间 $[l,r]$，满足该区间内的数均未出现过，且最小化 $l$。

对于新增/删除数字的操作，可以用 `std::set` 动态维护上述区间。
- 新增一个数：可能会将一个区间分成左右两半
- 删除一个数：可能会将左右两个区间合为一个

按题意模拟即可。使用 `lower_bound` 就可以快速定位到每次操作涉及的区间，细节实现稍微麻烦，有些近似珂朵莉树的操作。注意区间 $r$ 和 $len$ 的最大值 $W=4\times10^6$。

在上述操作中，我们时刻知道每个新区间的 $len$ 和 $l$，可以用一个 `std::map<int, set<int>>` 记录所有长为 $len$ 的区间的 $l$，这支持实时增删。增删次数的量级为 $\mathcal{O}(n+m)$，复杂度正确。

然后就是要在每次询问 $k$ 时回答 $\min\limits_{i=k}^{W}\min\limits_{len=i}l$。内层 $\min$ 已经在刚才实现了，处理外层 $\min$ 只需要套一个区间查最小值线段树即可。内层 `set` 的每次修改对应一次单点赋值操作。

因为多测每次开一棵新树会爆，可以记下当前 testcase 出现过的所有 $len$，并在每组结束时仅重置线段树上这些 $len$ 的值。因为 $len$ 的数量和区间数量显然是同级别的，所以一共会重置 $\mathcal{O}(n+m)$ 次，没有问题。

```cpp
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
  int n = v.size();
  for (int i = 0; i < n; ++i)
    os << v[i] << ' ';
  return os;
}
using namespace std;
using i64 = long long;

template <class node>
class segtree {
#define p ((l + r) >> 1)
#define q (o + ((p - l + 1) << 1))
 public:
  using T = decltype(node::v);
  vector<node> t;
  vector<T> src;
  int n;

  segtree(const vector<T> &arr) : src(arr) {
    n = src.size();
    assert(n > 0);
    t.resize(n << 2);
    build(0, 0, n - 1);
  }
  segtree(int _n, T val = node().v) : n(_n) {
    assert(n > 0);
    src.assign(n, val);
    t.resize(n << 2);
    build(0, 0, n - 1);
  }
  void upd(int o, int l, int r, int x, T v) {
    if (l == r && r == x) {
      t[o].apply(l, r, v);
      return;
    }
    if (x <= p) upd(o + 1, l, p, x, v);
    if (x > p) upd(q, p + 1, r, x, v);
    t[o] = t[o + 1] + t[q];
  }
  node get(int o, int l, int r, int ll, int rr) {
    if (ll <= l && r <= rr)
      return t[o];
    node res{};
    if (rr <= p) res = get(o + 1, l, p, ll, rr);
    else if (ll > p) res = get(q, p + 1, r, ll, rr);
    else res = get(o + 1, l, p, ll, rr) + get(q, p + 1, r, ll, rr);
    return res;
  }
  int find_first_knowingly(int o, int l, int r, const function<bool(const node &)> &f, node &base) {
    if (l == r)
      return base = base + t[o], l;
    int res;
    if (f(t[o + 1] + base)) res = find_first_knowingly(o + 1, l, p, f, base);
    else res = find_first_knowingly(q, p + 1, r, f, base = base + t[o + 1]);
    t[o] = t[o + 1] + t[q], base = base + t[o];
    return res;
  }
  int find_first(int o, int l, int r, int ll, int rr, const function<bool(const node &)> &f, node &base) {
    if (ll <= l && r <= rr) {
      if (!f(t[o] + base)) return base = base + t[o], -1;
      return find_first_knowingly(o, l, r, f, base);
    }
    int res = -1;
    if (ll <= p) res = find_first(o + 1, l, p, ll, rr, f, base);
    if (rr > p && res == -1) res = find_first(q, p + 1, r, ll, rr, f, base);
    t[o] = t[o + 1] + t[q];
    return res;
  }
  int find_last_knowingly(int o, int l, int r, const function<bool(const node &)> &f, node &base) {
    if (l == r)
      return base = base + t[o], l;
    int res;
    if (f(t[q] + base)) res = find_last_knowingly(q, p + 1, r, f, base);
    else res = find_last_knowingly(o + 1, l, p, f, base = base + t[q]);
    t[o] = t[o + 1] + t[q], base = base + t[o];
    return res;
  }
  int find_last(int o, int l, int r, int ll, int rr, const function<bool(const node &)> &f, node &base) {
    if (ll <= l && r <= rr) {
      if (!f(t[o] + base)) return base = base + t[o], -1;
      return find_last_knowingly(o, l, r, f, base);
    }
    int res = -1;
    if (rr > p) res = find_last(q, p + 1, r, ll, rr, f, base);
    if (ll <= p && res == -1) res = find_last(o + 1, l, p, ll, rr, f, base);
    t[o] = t[o + 1] + t[q];
    return res;
  }
  void upd(int x, T v) {
    assert(0 <= x && x <= n - 1);
    upd(0, 0, n - 1, x, v);
  }
  node get(int ll, int rr) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    return get(0, 0, n - 1, ll, rr);
  }
  node get(int x) {
    assert(0 <= x && x <= n - 1);
    return get(0, 0, n - 1, x, x);
  }
  int find_first(int ll, int rr, const function<bool(const node &)> &f) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    node _base{};
    return find_first(0, 0, n - 1, ll, rr, f, _base);
  }
  int find_last(int ll, int rr, const function<bool(const node &)> &f) {
    assert(0 <= ll && ll <= rr && rr <= n - 1);
    node _base{};
    return find_last(0, 0, n - 1, ll, rr, f, _base);
  }

 private:
  void build(int o, int l, int r) {
    if (l == r) {
      t[o].apply(l, r, src[l]);
      return;
    }
    build(o + 1, l, p);
    build(q, p + 1, r);
    t[o] = t[o + 1] + t[q];  // pull
  }
#undef p
#undef q
};

struct node {
  int v = 1e9;
  node operator+(const node &rhs) {
    node res{};
    res.v = min(v, rhs.v);
    return res;
  }
  void apply(int _l, int _r, int w) { // valType w
    v = w;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int T;
  cin >> T;

  const int W = 4e6;
  segtree<node> findmin(W + 1);

  while (T--) {
    int n;
    cin >> n;
    set<int> s;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
      cin >> a[i];
      s.insert(a[i]);
    }
    sort(all(a));

    struct segment {
      int l, r;
      bool operator<(const segment &y) const {
        return l < y.l;
      }
    };
    set<segment> segs;
    set<int> IMPACT;
    map<int, set<int>> len_mp;

    auto add_seg = [&](int l, int r) {
      int len = r - l + 1;
      IMPACT.insert(len);
      segs.insert({l, r});
      len_mp[len].insert(l);
      findmin.upd(len, *len_mp[len].begin());
    };
    auto del_seg = [&](int l, int r) {
      int len = r - l + 1;
      IMPACT.insert(len);
      segs.erase({l, r});
      len_mp[len].erase(l);
      if (!len_mp[len].empty()) {
        findmin.upd(len, *len_mp[len].begin());
      } else {
        findmin.upd(len, 1e9);
      }
    };

    if (a[0] != 1)
      add_seg(1, a[0] - 1);
    for (int i = 1; i < n; ++i) {
      if (a[i] != a[i - 1] + 1) {
        add_seg(a[i - 1] + 1, a[i] - 1);
      }
    }
    add_seg(a[n - 1] + 1, W);

    int m;
    cin >> m;
    while (m--) {
      char c;
      int x;
      cin >> c >> x;

      if (c == '+') {
        s.insert(x);
        auto to_be_split = --segs.upper_bound({x, W});
        auto [l, r] = *to_be_split;

        del_seg(l, r);

        if (x != l) {
          add_seg(l, x - 1);
        } 
        if (x != r) {
          add_seg(x + 1, r);
        }
      } else if (c == '-') {
        s.erase(x);
        int l, r;
        auto pl = s.upper_bound(x), pr = s.lower_bound(x);
        if (pl != s.begin()) {
          l = *--pl;
        } else {
          l = 0;
        }
        if (pr != s.end()) {
          r = *pr;
        } else {
          r = 4e6 + 1;
        }
        if (l + 1 <= x - 1) {
          del_seg(l + 1, x - 1);
        }
        if (x + 1 <= r - 1) {
          del_seg(x + 1, r - 1);
        }

        add_seg(l + 1, r - 1);
      } else {
        int ans = findmin.get(x, W).v;
        cout << ans << ' ';
      }
    }
    cout << '\n';
    for (auto i : IMPACT)
      findmin.upd(i, 1e9);
  }
  return 0;
}
```

---

## 作者：conti123 (赞：0)

vp 两小时，调这题也有了两小时......

官方题解是一颗 Treap?

我来一发线段树的题解。

### 分析

考虑构建线段树，把在集合内的数的权值设为 $-\inf$，不在的设为 $1$。

于是我们发现，若一段区间的 **最大子段和** $\ge k$，则说明这一段区间内有我们要找的 $d$。

维护最大子段和也比较套路，不会的出门左转 [GSS1](https://www.luogu.com.cn/problem/SP1043)。

在说一下查询的方法。

我们依次判断：

1. 检查左儿子区间内的最大子段和若 $\ge k$ ，则往左儿子递归。
2. 检查左儿子和右耳子是否可以拼出一段 $\ge k$ 的最大子段和，如果可以返回左边的开始端点。
3.  检查右儿子区间内的最大子段和若 $\ge k$ ，则往右儿子递归。
4.  返回正无限表示没有。

那我们一次查询即可搞定。

一些坑：
- 不能建 $t$ 次线段树，考虑开始时建出，单点修改原来给出的 $a_i$。
- 需要对 **现有的最大的** $a_i+1$ 取一个 $\min$，这个可以用 set 维护，但是别忘记判断 set 是否为空。
- 请不要兼用 read 和 ios。

Code:
```cpp
#include<bits/stdc++.h>
//#pragma GCC optimize(3,"Ofast","inline")
#define int long long
using namespace std;
const int N=2.2e6+1,mod=3e6+7;
int n,m,a[N],b[N],c[N];
int idx;
struct Tr{
#define ls x<<1
#define rs x<<1|1
#define mid ((l+r)>>1)
	struct fy{
		int sum,lx,rx,mx;
	}tr[N<<2];
	int L[N<<2],R[N<<2];
	void build(int x,int l,int r){
		L[x]=l,R[x]=r;
		if(l==r){
			tr[x].lx=tr[x].rx=tr[x].mx=tr[x].sum=1;
			return ;
		}
		build(ls,l,mid);
		build(rs,mid+1,r);
		pushup(x);
	}
	void pushup(int x){//套路
		tr[x].sum=tr[ls].sum+tr[rs].sum;
		tr[x].lx=max(tr[ls].lx,tr[ls].sum+tr[rs].lx);
		tr[x].rx=max(tr[rs].rx,tr[rs].sum+tr[ls].rx);
		tr[x].mx=max(max(tr[ls].mx,tr[rs].mx),tr[ls].rx+tr[rs].lx);
	}
	int ask(int x,int l,int r,int qx){//查询
		if(l==r){
			return L[x];
		}
		//		cout<<x<<" "<<l<<" "<<r<<" "<<qx<<" "<<tr[ls].mx<<" "<<tr[rs].mx<<"\n";
		if(tr[ls].mx>=qx)
			return ask(ls,l,mid,qx);
		//	cout<<L[ls]<<" "<<R[ls]<<" "<<tr[ls].rx<<" "<<tr[rs].lx<<"\n";
		if(tr[ls].rx+tr[rs].lx>=qx){
			//		cout<<R[ls]<<" "<<tr[ls].rx<<"\n";
			return R[ls]-tr[ls].rx+1;
		}
		if(tr[rs].mx>=qx)
			return ask(rs,mid+1,r,qx);
		return 3e6;
	}
	void modify(int x,int l,int r,int pos,int qx){//单点修改
		if(l==r){
			int o=0;
			tr[x].rx=tr[x].lx=max(qx,o),tr[x].mx=tr[x].sum=qx;
			return ;
		}
		if(pos<=mid)
			modify(ls,l,mid,pos,qx);
		else
			modify(rs,mid+1,r,pos,qx);
		pushup(x);
	}
	void check(int x,int l,int r){
		//	assert(r-l+1==tr[x].sum);
		if(l==r)
			return ;
		check(ls,l,mid);
		check(rs,mid+1,r);
	}
}tree;
signed main(){
	ios::sync_with_stdio(false),cin.tie(NULL),cout.tie(NULL);
	memset(b,1,sizeof b);
	int k=2e6;
	int T;
	cin>>T;
	tree.build(1,1,k);//只建一次树
//	tree.check(1,1,k);
//	cout<<"check 预处理 ok\n";
	set<int>A;
	while(T--){
		cin>>n;
		A.clear();
		for(int i=1;i<=n;i++)
			cin>>a[i],A.insert(a[i]),tree.modify(1,1,k,a[i],-3e6);
		sort(a+1,a+n+1);
		cin>>m;
		while(m--){
			char op;
			int x;
			cin>>op>>x;
			if(op=='+')
				tree.modify(1,1,k,x,-3e6),A.insert(x);
			if(op=='-')
				tree.modify(1,1,k,x,1),A.erase(x);
			if(op=='?'){
				set<int>::iterator it;
				it=A.end();
				int ans;
				if(!A.empty())//一定记得
					it--,ans=min(*it+1,tree.ask(1,1,k,x));
				else
					ans=ans;
				if(tree.tr[1].sum==k)//特判(雾
					ans=1;
				cout<<ans<<" ";
			}
		}
		cout<<"\n";
		for(set<int>::iterator it=A.begin();it!=A.end();it++)
			tree.modify(1,1,k,*it,1);
		//	tree.check(1,1,k);
	}
//	cout<<clock()-be<<"\n";
	return 0;
}
/*
1
4
2 5 6 8 
9
- 6
+ 10
? 6
- 8
? 4
+ 7
? 6
? 3
- 10

*/
```

---

