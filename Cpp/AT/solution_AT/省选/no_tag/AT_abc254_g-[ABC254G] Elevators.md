# [ABC254G] Elevators

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc254/tasks/abc254_g

$ N $ 棟の $ 10^9 $ 階建てのビルからなる建物があります。ビルには $ 1 $ から $ N $ の番号がついています。

任意の異なるビルの同じ階は連絡通路で結ばれているため $ 1 $ 分で移動可能です。

また、$ M $ 基のエレベーターがあります。$ i $ 個目のエレベーターはビル $ A_i $ の $ B_i $ 階から $ C_i $ 階を結ぶものです。このエレベーターを使うと、$ B_i\ \le\ x,y\ \le\ C_i $ を満たす全ての整数の組 $ x,y $ に対し、ビル $ A_i $ の $ x $ 階から $ y $ 階に $ |x-y| $ 分で移動することができます。

以下の $ Q $ 個のクエリに答えてください。

- ビル $ X_i $ の $ Y_i $ 階からビル $ Z_i $ の $ W_i $ 階に移動することが可能か判定し、可能な場合は移動時間の最小値を求めてください。

## 说明/提示

### 制約

- $ 1\ \le\ N,M,Q\ \le\ 2\ \times\ 10^5 $
- $ 1\ \le\ A_i\ \le\ N $
- $ 1\ \le\ B_i\ <\ C_i\ \le\ 10^9 $
- $ 1\ \le\ X_i,Z_i\ \le\ N $
- $ 1\ \le\ Y_i,W_i\ \le\ 10^9 $
- 入力はすべて整数である。

### Sample Explanation 1

$ 1 $ 番目のクエリについては、以下のようにすることで $ 12 $ 分で移動が可能です。 - エレベーター $ 1 $ を使い、ビル $ 1 $ の $ 3 $ 階から $ 9 $ 階へ移動する。この移動には $ 6 $ 分かかる。 - $ 9 $ 階の連絡通路を使い、ビル $ 1 $ からビル $ 3 $ へ移動する。この移動には $ 1 $ 分かかる。 - エレベーター $ 3 $ を使い、ビル $ 3 $ の $ 9 $ 階から $ 14 $ 階で移動する。この移動には $ 5 $ 分かかる。 また、$ 3 $ 番目のクエリについては、移動することが不可能であるため `-1` を出力します。

## 样例 #1

### 输入

```
3 4 3
1 2 10
2 3 7
3 9 14
3 1 3
1 3 3 14
3 1 2 7
1 100 1 101```

### 输出

```
12
7
-1```

## 样例 #2

### 输入

```
1 1 1
1 1 2
1 1 1 2```

### 输出

```
1```

# 题解

## 作者：WaterSun (赞：1)

[更好的阅读体验](https://www.cnblogs.com/WaterSun/p/18402924)

# 思路

假定 $y_i < w_i$。

首先有一个很显然的事实：坐电梯只往上，不往下。因为如果坐了一个电梯往下，然后换乘往上，明显不如立刻换乘然后往上。

所以问题转为求最少的换乘次数。为了代码的简洁，我们先把在同一栋楼中有交的电梯合为同一班电梯。即将 $l_1 \leq l_2 \leq r_1 \leq r_2$ 的两班电梯合并为 $[l_1,r_2]$ 的一班电梯。

考虑倍增地跳。定义 $dp_{i,j}$ 表示从第 $i$ 层出发换乘 $2^j$ 能到达的最高的楼层，转移是平凡的。

现在考虑求解 $dp_{i,0}$。对于每一班 $[l,r]$ 的电梯都可以从 $x \in [l,r]$ 到达 $y \in [l,r]$。所以对于 $\forall x \in [l,r],dp_{x,0} \leftarrow \max(dp_{x,0},r,x)$。这个操作可以上线段树解决。

对于每一次询问，需要注意的是如果能够不换乘能直接到达终点，直接输出 $w_i - y_i$，因为倍增地跳会多算出一次换乘。

代码细节较多，用 `vector` 离散化要注意下标问题，容易导致 UB。

# Code

```cpp
#include <bits/stdc++.h>
#define re register
#define fst first
#define snd second
#define chmax(a,b) (a = max(a,b))

using namespace std;

typedef pair<int,int> pii;
const int N = 8e5 + 10,M = 24,inf = 1e9 + 10;
int n,m,q,sz;
int lg[N],dp[N][M];
vector<int> pt;
vector<pii> v[N];

struct Query{
    int a,b,c,d;
}Q[N];

inline int read(){
    int r = 0,w = 1;
    char c = getchar();
    while (c < '0' || c > '9'){
        if (c == '-') w = -1;
        c = getchar();
    }
    while (c >= '0' && c <= '9'){
        r = (r << 3) + (r << 1) + (c ^ 48);
        c = getchar();
    }
    return r * w;
}

struct seg{
    #define ls(u) (u << 1)
    #define rs(u) (u << 1 | 1)

    struct node{
        int l,r;
        int Max,tag;
    }tr[N << 2];

    inline void calc(int u,int k){
        chmax(tr[u].Max,k); chmax(tr[u].tag,k);
    }

    inline void pushup(int u){
        tr[u].Max = max(tr[ls(u)].Max,tr[rs(u)].Max);
    }

    inline void pushdown(int u){
        if (tr[u].tag){
            calc(ls(u),tr[u].tag); calc(rs(u),tr[u].tag);
            tr[u].tag = 0;
        }
    }

    inline void build(int u,int l,int r){
        tr[u] = {l,r};
        if (l == r) return;
        int mid = l + r >> 1;
        build(ls(u),l,mid); build(rs(u),mid + 1,r);
    }

    inline void modify(int u,int l,int r,int k){
        if (l <= tr[u].l && tr[u].r <= r) return calc(u,k);
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (l <= mid) modify(ls(u),l,r,k);
        if (r > mid) modify(rs(u),l,r,k);
        pushup(u);
    }

    inline int query(int u,int x){
        if (tr[u].l == tr[u].r) return tr[u].Max;
        pushdown(u);
        int mid = tr[u].l + tr[u].r >> 1;
        if (x <= mid) return query(ls(u),x);
        else return query(rs(u),x);
    }

    #undef ls
    #undef rs
}T;

#define find(x) (lower_bound(pt.begin(),pt.end(),x) - pt.begin() + 1)

inline pii get(int x,int y){
    int l = y,r = y;
    auto it = upper_bound(v[x].begin(),v[x].end(),make_pair(y,inf));
    if (it != v[x].begin() && (*prev(it)).snd >= y){
        l = (*prev(it)).fst; r = (*prev(it)).snd;
    }
    return {l,r};
}

int main(){
    n = read(),m = read(),q = read();
    for (re int i = 1,a,b,c;i <= m;i++){
        a = read(),b = read(),c = read();
        v[a].push_back({b,c});
        pt.push_back(b); pt.push_back(c);
    }
    for (re int i = 1,a,b,c,d;i <= q;i++){
        a = read(),b = read(),c = read(),d = read();
        if (b > d){
            swap(a,c); swap(b,d);
        }
        Q[i] = {a,b,c,d};
        pt.push_back(b); pt.push_back(d);
    }
    sort(pt.begin(),pt.end());
    pt.erase(unique(pt.begin(),pt.end()),pt.end());
    const int num = pt.size();
    for (re int i = 1;i <= n;i++){
        vector<pii> tmp;
        sort(v[i].begin(),v[i].end());
        pii s = {-1,-1};
        for (pii p:v[i]){
            if (!~s.fst) s = p;
            else{
                if (s.fst <= p.fst && p.fst <= s.snd) chmax(s.snd,p.snd);
                else{
                    tmp.push_back(s);
                    s = p;
                }
            }
        }
        if (~s.fst) tmp.push_back(s);
        v[i] = tmp; sz += v[i].size();
    }
    for (re int i = 2;i <= sz;i++) lg[i] = lg[i >> 1] + 1;
    T.build(1,1,num);
    for (re int i = 1;i <= n;i++){
        for (pii p:v[i]){
            int l = find(p.fst),r = find(p.snd);
            T.modify(1,l,r,r);
        }
    }
    for (re int i = 1;i <= num;i++) dp[i][0] = max(i,T.query(1,i));
    for (re int j = 1;j <= lg[sz];j++){
        for (re int i = 1;i <= num;i++) dp[i][j] = dp[dp[i][j - 1]][j - 1];
    }
    for (re int i = 1;i <= q;i++){
        int a = Q[i].a,b = Q[i].b,c = Q[i].c,d = Q[i].d;
        int ans = d - b;
        pii s1 = get(a,b),s2 = get(c,d);
        if (a == c && s1.snd == s2.snd){
            printf("%d\n",ans); continue;
        }
        int now = find(s1.snd);
        for (re int j = lg[sz];~j;j--){
            int tmp = dp[now][j];
            if (tmp && d > pt[tmp - 1]){
                now = tmp; ans += (1 << j);
            }
        }
        if (pt[now - 1] >= s2.fst) printf("%d\n",ans + 1);
        else{
            int tmp = dp[now][0] - 1;
            if (0 <= tmp && tmp < num && d <= pt[tmp]) printf("%d\n",ans + 2);
            else puts("-1");
        }
    }
    return 0;
}
```

---

## 作者：_lfxxx_ (赞：1)

假设 $y_i < w_i$，如果不满足交换起点终点。

首先不考虑楼之间，答案就为 $w_i-y_i$。

也就是问要转几次楼，注意到不会往下跳再往上跳，因为如果需要先往下跳再往上跳，是一定可以直接向上跳的。那么现在问的就是至少要转几次楼，考虑倍增向上跳。

设 $f_{i,j}$ 表示从高度 $i$ 转了 $2^j$ 次能到达的最上面的位置。

用线段树维护出最开始每个位置向上能跳到哪里，然后直接倍增就行。

询问时开始的位置就是 $(x_i,y_i)$ 所在的最上端。

当然，最后一步要判一下能不能直接跳到 $z_i$ 那一层，能的话就少一步。

时间复杂度 $O(n \log n)$。

注意倍增前要离散化。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned long long
#define i128 __int128
#define pii pair<int, int>
#define pll pair<ll, ll>
#define all(x) (x).begin(), (x).end()
bool be;
constexpr int N = 2e5 + 5, inf = 1e9 + 9;
int n, m, Q, id[N], tmp[4 * N], cnt, fr[4 * N][18], xx[N], yy[N], zz[N], ww[N], a[4 * N];
vector<pii>v[N];
struct seg {
	#define ls k << 1
	#define rs k << 1 | 1
	int mx[N << 4], tag[N << 4];
	seg() {
		fill(mx, mx + (N << 4), -inf);
		fill(tag, tag + (N << 4), -inf);
	}
	void build(int *a, int k = 1, int l = 1, int r = cnt)
	{
		if (l == r) {
			mx[k] = a[l];
			return;
		}
		int mid = l + r >> 1;
		build(a, ls, l, mid);
		build(a, rs, mid + 1, r);
		mx[k] = max(mx[ls], mx[rs]);
	}
	void update(int L, int R, int v, int k = 1, int l = 1, int r = cnt)
	{
		mx[k] = max(mx[k], v);
		if (L <= l && r <= R) {
			tag[k] = max(tag[k], v);
			return;
		}
		int mid = l + r >> 1;
		if (L <= mid) update(L, R, v, ls, l, mid);
		if (R > mid) update(L, R, v, rs, mid + 1, r);
	}
	int query(int L, int R, int k = 1, int l = 1, int r = cnt)
	{
		int ans = tag[k];
		if (L <= l && r <= R) return max(ans, mx[k]);
		int mid = l + r >> 1;
		if (L <= mid) ans = max(ans, query(L, R, ls, l, mid));
		if (R > mid) ans = max(ans, query(L, R, rs, mid + 1, r));
		return ans;
	}
}tmx;
bool en;
int main()
{
	cerr << (&be - &en) / 1024.0 / 1024 << " MB\n--------------------------------" << endl;
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> m >> Q;
	for (int i = 1; i <= m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		v[a].emplace_back(b, c);
		tmp[++cnt] = b, tmp[++cnt] = c;
	}
	for (int i = 1; i <= Q; ++i) {
		cin >> xx[i] >> yy[i] >> zz[i] >> ww[i];
		tmp[++cnt] = yy[i], tmp[++cnt] = ww[i];
	}
	for (int i = 1; i <= n; ++i) {
		sort(all(v[i]));
		vector<pii>a;
		int li = -1, ri = -1;
		for (auto [l, r] : v[i]) {
			if (ri == -1) {
				li = l, ri = r;
				continue;
			}
			if (l > ri) {
				a.emplace_back(li, ri);
				li = l, ri = r;
			} else {
				ri = max(ri, r);
			}
		}
		if (ri != -1) a.emplace_back(li, ri);
		v[i] = a;
		id[i] = id[i - 1] + v[i - 1].size();
	}
	m = id[n] + v[n].size();
	sort(tmp + 1, tmp + 1 + cnt), cnt = unique(tmp + 1, tmp + 1 + cnt) - tmp - 1;
	auto rk = [](int x) {
		return lower_bound(tmp + 1, tmp + 1 + cnt, x) - tmp;
	};
	for (int i = 1; i <= n; ++i) {
		for (auto [l, r] : v[i]) {
			int LL = rk(l), RR = rk(r);
			tmx.update(LL, RR, RR);
		}
	}
	for (int i = 1; i <= cnt; ++i) {
		fr[i][0] = max(i, tmx.query(i, i));
	}
	for (int j = 1; j <= __lg(m); ++j) {
		for (int i = 1; i <= cnt; ++i) {
			fr[i][j] = fr[fr[i][j - 1]][j - 1];
		}
	}
	auto qra = [](int x, int y) {
		int LL = y, RR = y;
		pii p(y, inf);
		auto it = upper_bound(all(v[x]), p);
		if (it != v[x].begin() && prev(it) -> second >= y) {
			LL = prev(it) -> first, RR = prev(it) -> second;
		}
		return pii(LL, RR);
	};
	for (int i = 1; i <= Q; ++i) {
		int x = xx[i], y = yy[i], z = zz[i], w = ww[i];
		if (y > w) {
			swap(x, z), swap(y, w);
		}
		int ans = w - y;
		auto [LL, RR] = qra(x, y);
		auto [L2, R2] = qra(z, w);
		if (x == z && LL == L2 && RR == R2) {
			cout << ans << '\n';
			continue;
		}
		RR = rk(RR);
		for (int j = __lg(m); j >= 0; --j) {
			int RRR = fr[RR][j];
			if (w > tmp[RRR]) {
				RR = RRR;
				ans += 1 << j;
			}
		}
		RR = tmp[RR];
		if (RR >= L2) {
			cout << ans + 1 << '\n';
		} else {
			int RRR = tmp[fr[rk(RR)][0]];
			if (w <= RRR) {
				cout << ans + 2 << '\n';
			} else {
				cout << "-1\n";
			}
		}
	}
	return 0;
}
```

---

## 作者：xyz105 (赞：1)

### 题目描述

有 $n$ 栋摩天大楼，这些楼装了总计 $m$ 部电梯，$i$ 号电梯可达 $a_i$ 号楼的第 $b_i\sim c_i$ 层。乘坐电梯每垂直移动一层耗时 $1$ 分钟，另外可以随时花 $1$ 分钟时间水平移动到其他大楼的同一层。求从 $x_i$ 号楼的第 $y_i$ 层走到 $z_i$ 号楼的第 $w_i$ 层的最短时间（不合法则为 $-1$），$q$ 组询问。


### 解题思路

假定对于所有询问都有 $y_i\le w_i$，即从较低楼层移动到较高楼层。因为如果 $y_i>w_i$，则将 $y_i,w_i$ 交换、$x_i,z_i$ 交换，与上述问题等价。

注意到移动过程中乘坐的所有电梯都必须是**向上层移动**的。如果你乘一部电梯下降，又在较低层换上另一部电梯并上升至比最开始更高的楼层，那么你还不如一开始就水平切换至另一部电梯进行上升呢。所以全程最短耗时至少为 $|w_i-y_i|$。

又注意到同一栋楼的一些电梯可能是**可以合并**的。如果同一栋楼中有一部电梯在 $[l_1,r_1]$ 层运行，另一部电梯在 $[l_2,r_2]$ 层运行，并且楼层 $[l_1,r_1]$ 与 $[l_2,r_2]$ 有交集，那么这两部电梯就可以被合并为一部，在 $[\min\{l_1,l_2\},\max\{r_1,r_2\}]$ 层运行。合并后所有电梯运行的楼层均无任何交集。

将初始答案设为 $|w_i-y_i|$，目标是使大楼间水平移动的次数最少。

考虑求出从起点出发乘坐的**第一部电梯**是哪部。
- 用可变数组（`vector`）从低层到高层存储第 $x_i$ 栋楼的所有电梯运行的楼层范围，即可在这个数组里二分求出哪一部电梯有经过第 $y_i$ 层。
- 如果第 $x_i$ 栋楼没有电梯经过第 $y_i$ 层，则不得不水平切换至别的大楼，答案增 $1$；尝试切换到 $n$ 栋大楼的所有电梯中经过第 $y_i$ 层且能到达的最上层最远的那部电梯。
  - 经过第 $X$ 层 且 能到达的最上层最远 的那部电梯编号 可以用 离散化+排序 预处理，细节详见代码中的 `lmax` 数组求法。

如果这第一部电梯刚好能到第 $w_i$ 层，就直接将答案进行最终微调后输出。

对终点做同样的步骤，可以确保这个做法不被叉掉。原因讲起来有些繁琐。对于 `3 2 1\n2 5 10\n3 4 8\n1 5 3 8` 这个样例，从起点处选最远电梯总的水平切换次数为 $2$，从终点处选第一部电梯总的水平切换次数为 $1$，所以这两者要综合考虑。

接下来就是电梯间的**换乘**。若当前电梯在 $[l,r]$ 层运行，则贪心地想，下一部电梯应为 经过第 $r$ 层 且 能到达的最上层最远 的那部，这个东西刚才处理过了。所以所有电梯对应的下一部换乘电梯都是固定的。

于是可以**倍增**。设 `nxt[i][j]` 表示从第 $i$ 部电梯贪心地换乘 $2^j$ 次所到达的电梯编号，则从起点处的电梯换乘到终点处的电梯可以在 $\log m$ 时间内解决。


### 参考代码

细节还是蛮多的，我断断续续调了一天。

```cpp
#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

const int MAXN = 2e5 + 10, INF = 0x3f3f3f3f;

int n, m, q;

vector<pair<int, int> > vec1[MAXN], vec2[MAXN];

// bnum = building_num, ele = elevator
struct ele{
	int bnum, l, r;
}a[MAXN]; int a2;

bool cmp1(ele a, ele b)
	{return a.l == b.l ? a.r < b.r : a.l < b.l;}
bool cmp2(ele a, ele b)
	{return a.r == b.r ? a.l < b.l : a.r < b.r;}

int b1[MAXN << 1], b1_cnt;
int lmax[MAXN << 1], rmin[MAXN << 1];

inline int b1_num(int x)
	{return upper_bound(b1 + 1, b1 + b1_cnt + 1, x) - b1 - 1;}

inline pair<int, int> get_ele1(int i1, int i2)
{
	bool flag = 0;
	auto j1 = upper_bound(vec1[i1].begin(), vec1[i1].end(), make_pair(i2, INF));
	if (j1 == vec1[i1].begin()) flag = 1;
	else {j1--; if (a[(*j1).second].r < i2) flag = 1;}
	
	int j2 = b1_num(i2);
	if (!flag) return make_pair((*j1).second, 0);
	else if (!lmax[j2] || a[lmax[j2]].r < i2) return make_pair(0, -1);
	else return make_pair(lmax[j2], 1);
}
inline pair<int, int> get_ele2(int i3, int i4)
{
	bool flag = 0;
	auto j1 = lower_bound(vec2[i3].begin(), vec2[i3].end(), make_pair(i4, 0));
	if (j1 == vec2[i3].end()) flag = 1;
	else if (i4 < a[(*j1).second].l) flag = 1;
	
//	int j2 = b1_num(i4);
	int j2 = lower_bound(b1 + 1, b1 + b1_cnt + 1, i4) - b1;
	if (!flag) return make_pair((*j1).second, 0);
	else if (!rmin[j2] || a[rmin[j2]].l > i4) return make_pair(0, -1);
	else return make_pair(rmin[j2], 1);
}

int nxt[MAXN][19];

int main()
{
	scanf("%d%d%d", &n, &m, &q);
	for (int i = 1, i1, i2, i3; i <= m; i++)
		scanf("%d%d%d", &i1, &i2, &i3),
		vec1[i1].push_back(make_pair(i2, i3));
	
	for (int i = 1; i <= n; i++)
	{
		sort(vec1[i].begin(), vec1[i].end());
		if (!vec1[i].size()) continue;
		pair<int, int> i1 = vec1[i].front();
		for (auto j : vec1[i])
		{
			if (j.first <= i1.second) i1.second = max(i1.second, j.second);
			else a2++, a[a2].bnum = i, a[a2].l = i1.first, a[a2].r = i1.second, i1 = j;
		}
		a2++, a[a2].bnum = i, a[a2].l = i1.first, a[a2].r = i1.second;
		vec1[i].clear();
	}
	m = a2;
	
	for (int i = 1; i <= m; i++)
		b1[++b1_cnt] = a[i].l, b1[++b1_cnt] = a[i].r;
	sort(b1 + 1, b1 + b1_cnt + 1);
	b1_cnt = unique(b1 + 1, b1 + b1_cnt + 1) - b1 - 1;
	
	for (int i = 1, i1; i <= m; i++)
	{
		i1 = b1_num(a[i].l);
		if (a[lmax[i1]].r < a[i].r) lmax[i1] = i;
	}
	for (int i = 1; i <= b1_cnt; i++)
		if (a[lmax[i]].r < a[lmax[i - 1]].r) lmax[i] = lmax[i - 1];
	a[0].l = INF;
	for (int i = 1, i1; i <= m; i++)
	{
		i1 = b1_num(a[i].r);
		if (a[rmin[i1]].l > a[i].l) rmin[i1] = i;
	}
	for (int i = b1_cnt; i; i--)
		if (a[rmin[i]].l > a[rmin[i + 1]].l) rmin[i] = rmin[i + 1];
	a[0].l = 0, a[0].r = INF;
	
	for (int i = 1; i <= m; i++)
		vec1[a[i].bnum].push_back(make_pair(a[i].l, i)),
		vec2[a[i].bnum].push_back(make_pair(a[i].r, i));
	for (int i = 1; i <= n; i++)
		sort(vec1[i].begin(), vec1[i].end()),
		sort(vec2[i].begin(), vec2[i].end());
	
	for (int i = 1, i1; i <= m; i++)
	{
		i1 = b1_num(a[i].r);
		if (a[i].r <= a[lmax[i1]].r && i != lmax[i1]) nxt[i][0] = lmax[i1];
	}
	for (int i = 1; i < 19; i++)
		for (int j = 1; j <= m; j++) nxt[j][i] = nxt[nxt[j][i - 1]][i - 1];
	
	int i1, i2, i3, i4;
	while (q--)
	{
		scanf("%d%d%d%d", &i1, &i2, &i3, &i4);
		if (i2 > i4) swap(i1, i3), swap(i2, i4);
		else if (i2 == i4) {printf("%d\n", i1 != i3); continue;}
		
		int ans = i4 - i2;
		auto j1 = get_ele1(i1, i2), j2 = get_ele2(i3, i4);
		
		if (j1.second == -1 || j2.second == -1) {puts("-1"); continue;}
		if (!j1.second && a[j1.first].r >= i4) {printf("%d\n", ans + (a[j1.first].bnum != i3)); continue;}
		else if (!j2.second && a[j2.first].l <= i2) {printf("%d\n", ans + (i1 != a[j2.first].bnum)); continue;}
		else if (j1.second && a[j1.first].r >= i4) {printf("%d\n", ++ans + (a[j1.first].bnum != i3)); continue;}
		else if (j2.second && a[j2.first].l <= i2) {printf("%d\n", ++ans + (i1 != a[j2.first].bnum)); continue;}
		ans += j1.second + j2.second;
		
		int now = j1.first;
		if (now == j2.first) {printf("%d\n", ans); continue;}
		if (a[now].r >= a[j2.first].l) {printf("%d\n", ++ans); continue;}
		for (int i = 18; i >= 0; i--)
			if (a[nxt[now][i]].r < a[j2.first].l) now = nxt[now][i], ans += (1 << i);
		now = nxt[now][0], ans++;
		if (now && a[now].r >= a[j2.first].l) {printf("%d\n", ++ans); continue;}
		puts("-1");
	}
	
	return 0;
}
```

---

## 作者：ethan0328 (赞：1)

## 思路

发现从一层楼到另一侧楼往下走一定不优，所以答案一定有加上层数差。剩下只考虑换几次楼。

考虑把同一楼中的相交的电梯合并，并把低的点转移到同层能到的最高点，把高的点转移到同层能到的最低点，问题就变成求两个点之间的最小覆盖。

容易想到倍增。先用线段树记录只覆盖一次能到的最高点。然后令 ```fa[i][j]``` 表示从 $i$ 转移 $2^j$ 次后能到的最高点，然后从大到小转移即可。

## 代码

```cpp
#include<bits/stdc++.h>
#define mkp make_pair
#define fir first
#define sec second
using namespace std;
const int N=2e5+10,lgN=22;
int n,m,q,ind,que[N][4],b[N*4];
int mx[N],mn[N];
vector<pair<int,int> > v1[N],v2[N];
int tree[N*16],tag[N*16];
int fa[N*4][lgN+10];
void push_up(int p)
{
	tree[p]=max(tree[p*2],tree[p*2+1]);
}
void push_down(int p)
{
	if(tag[p])
	{
		tree[p*2]=max(tree[p*2],tag[p]);
		tag[p*2]=max(tag[p*2],tag[p]);
		tree[p*2+1]=max(tree[p*2+1],tag[p]);
		tag[p*2+1]=max(tag[p*2+1],tag[p]);
		tag[p]=0;
	}
}
void update(int p,int l,int r,int nl,int nr,int x)
{
	if(nl<=l&&r<=nr)
	{
		tree[p]=max(tree[p],x);
		tag[p]=max(tag[p],x);
		return;
	}
	int mid=(l+r)/2;
	push_down(p);
	if(nl<=mid)
	{
		update(p*2,l,mid,nl,nr,x);
	}
	if(nr>mid)
	{
		update(p*2+1,mid+1,r,nl,nr,x);
	}
	push_up(p);
}
int query(int p,int l,int r,int x)
{
	if(l==r)
	{
		return tree[p];
	}
	int mid=(l+r)/2;
	push_down(p);
	if(x<=mid)
	{
		return query(p*2,l,mid,x);
	}else
	{
		return query(p*2+1,mid+1,r,x);
	}
}
int getl(int x,int y)
{
	if(y<mn[x]||y>mx[x])
	{
		return y;
	}
	pair<int,int> tmp;
	tmp=*(--upper_bound(v2[x].begin(),v2[x].end(),mkp(y,(int)2e9)));
	if(tmp.fir<=y&&y<=tmp.sec)
	{
		return tmp.fir;
	}
	return y;
}
int getr(int x,int y)
{
	if(y<mn[x]||y>mx[x])
	{
		return y;
	}
	pair<int,int> tmp;
	tmp=*(--upper_bound(v2[x].begin(),v2[x].end(),mkp(y,(int)2e9)));
	if(tmp.fir<=y&&y<=tmp.sec)
	{
		return tmp.sec;
	}
	return y;
}
int calc(int l,int r)
{
	int ret=1;
	for(int i=lgN;i>=0;i--)
	{
		if(!fa[l][i])
		{
			continue;
		}
		if(fa[l][i]>=r)
		{
			continue;
		}
		ret+=(1<<i);
		l=fa[l][i];
	}
	ret++;
	if(fa[l][0])
	{
		l=fa[l][0];
	}
	if(l<r)
	{
		return -1;
	}
	return ret;
}
int main()
{
	int x,y,z,w,t,t2;
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++)
	{
		mn[i]=2e9;
	}
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y>>z;
		v1[x].push_back(mkp(y,z));
		b[++ind]=y;b[++ind]=z;
	}
	for(int i=1;i<=q;i++)
	{
		cin>>x>>y>>z>>w;
		if(y>w)
		{
			swap(x,z);
			swap(y,w);
		}
		que[i][0]=x;que[i][1]=y;
		que[i][2]=z;que[i][3]=w;
		b[++ind]=y;
		b[++ind]=w;
	}
	sort(b+1,b+1+ind);
	ind=unique(b+1,b+1+ind)-b-1;
	for(int i=1;i<=n;i++)
	{
		x=y=0;
		sort(v1[i].begin(),v1[i].end());
		for(auto j:v1[i])
		{
			if(y<j.fir)
			{
				if(x!=0||y!=0)
				{
					x=upper_bound(b+1,b+1+ind,x)-b-1;
					y=upper_bound(b+1,b+1+ind,y)-b-1;
					v2[i].push_back(mkp(x,y));
					mx[i]=max(mx[i],y);
					mn[i]=min(mn[i],x);
				}
				x=j.fir;
				y=j.sec;
			}else
			{
				x=min(x,j.fir);
				y=max(y,j.sec);
			}
		}
		if(x!=0||y!=0)
		{
			x=upper_bound(b+1,b+1+ind,x)-b-1;
			y=upper_bound(b+1,b+1+ind,y)-b-1;
			v2[i].push_back(mkp(x,y));
			mx[i]=max(mx[i],y);
			mn[i]=min(mn[i],x);
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(auto j:v2[i])
		{
			if(j.sec>j.fir)
			{
				update(1,1,ind,j.fir,j.sec-1,j.sec);
			}
		}
	}
	for(int i=1;i<=ind;i++)
	{
		fa[i][0]=query(1,1,ind,i);
	}
	for(int j=1;j<=lgN;j++)
	{
		for(int i=1;i<=ind;i++)
		{
			fa[i][j]=fa[fa[i][j-1]][j-1];
		}
	}
	for(int i=1;i<=q;i++)
	{
		x=que[i][0];y=que[i][1];
		z=que[i][2];w=que[i][3];
		t=w-y;
		y=upper_bound(b+1,b+1+ind,y)-b-1;
		w=upper_bound(b+1,b+1+ind,w)-b-1;
		y=getr(x,y);
		w=getl(z,w);
		if(y>=w)
		{
			cout<<t+(x==z? 0:1)<<"\n";
			continue;
		}
		t2=calc(y,w);
		if(t2==-1)
		{
			cout<<t2<<"\n";
		}else
		{
			cout<<t+t2<<"\n";
		}
	}
}
```


---

## 作者：Vsinger_洛天依 (赞：0)

首先考虑对于上下楼我们可以统一改为上楼，如果是下楼我们可以直接调转起点和终点的顺序转化为上楼。

我们先不考虑需要转楼层，那么可以发现如果能到达的话就能且只能是 $w_i-y_i$。

那么我们就可以转化问题为需要走几次天桥，为了方便我们可以把所有能合并的电梯全部合并起来，这对答案是没有影响的而且很显然。

只要切换楼层尽量少就可以了，我们在起点所在楼坐电梯一直上到头 $y'$，终点所在楼一直下到底 $w'$，肯定是没啥问题的。

考虑倍增，定义 $dp_{i,j}$ 表示从第 $i$ 层出发换乘 $2^j$ 能到达的最高的楼层，而后用线段树维护即可。

---

## 作者：Nightingale_OI (赞：0)

## AT_abc254_g

### 大意

$N$ 栋大楼，$M$ 部电梯，第 $i$ 部电梯管理第 $A_i$ 栋楼的 $[B_i,C_i]$ 层。

你可以花 $1$ 单位时间在任意两栋大楼同一层之内穿梭。

你可以坐电梯到其管理的任意层，每移动一层花 $1$ 单位时间。

有 $Q$ 次询问，每次形如从第 $X$ 栋第 $Y$ 层到第 $Z$ 栋第 $W$ 层最少要花多少时间。

### 思路

默认询问 $Y\leq W$，反之调换起终点就可以了。

对于每一栋楼，把两个管理区间相交的电梯合并为一个。

显然不可能坐电梯往下，所以就有基础的坐电梯时间 $W-Y$。

只要切换楼层尽量少就可以了，先在起点所在楼坐电梯一直上到头 $Y'$，终点所在楼一直下到底 $W'$，肯定是不亏的。

此时相当于用最少的区间覆盖给定区间 $[Y',W']$。

对于一个点 $i$，用线段树求出用一个区间最右能覆盖到 $[i,a_i]$。

问题变为最少做多少次 $Y'\leftarrow a_{Y'}$ 可以使得 $Y'\geq W'$，这是非常经典的问题，无论是倍增还是分块都非常好实现。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
int n,m,s,l;
const int N=202020;
const int inf=1e9+7;
struct xy{
	int x,y;
};
inline bool operator <(xy a,xy b){return a.y<b.y;}
struct asks{
	int u1,f1,u2,f2;
}t[N];
int b[N<<2];
vector<xy>p[N],q[N];
inline bool cmp(xy a,xy b){return a.x<b.x;}
inline void merge_lines(){
	f(i,1,n){
		sort(p[i].begin(),p[i].end(),cmp);
		xy ep=(xy){0,0};l=-1;
		for(auto e:p[i]){
			if(ep.y<e.x)q[i].push_back(ep=e),++l;
			else q[i][l].y=ep.y=max(q[i][l].y,e.y);
		}
		q[i].push_back((xy){inf,inf});
	}
}
struct Ceobe{
	struct xds{
		int l,r,c;
	}a[N<<4];
	inline void Max(int&x,int y){if(x<y)x=y;}
	void bt(int id,int l,int r){
		a[id]=(xds){l,r,l};
		if(l<r){
			int mid=(l+r)/2;
			bt(id*2,l,mid);
			bt(id*2+1,mid+1,r);
		}
	}
	void set(int id,int l,int r,int c){
		if(a[id].l==l&&a[id].r==r)return Max(a[id].c,c);
		int mid=(a[id].l+a[id].r)/2;
		if(r<=mid)set(id*2,l,r,c);
		else if(mid<l)set(id*2+1,l,r,c);
		else set(id*2,l,mid,c),set(id*2+1,mid+1,r,c);
	}
	int ask(int id,int x){
		if(a[id].l==a[id].r)return a[id].c;
		Max(a[id*2].c,a[id].c);Max(a[id*2+1].c,a[id].c);
		return ask(id*2+(x>(a[id].l+a[id].r)/2),x);
	}
}T;
int a[N<<2],c[N<<2],w[N<<2];
void init_fk(int n){
	int B=sqrt(n)+1,C=B,R=n;
	g(i,n,1){
		if((++C)>B)C=1,R=i;
		a[i]=c[i]=T.ask(1,i);w[i]=(a[i]>i);
		if(c[i]>R)continue;
		c[i]=c[a[i]];w[i]+=w[a[i]];
	}
}
int clac(int l,int r){
	int re=1;
	while(l<r){
		if(a[l]==l)return -1;
		if(c[l]<=r){
			re+=w[l];l=c[l];
		}else{
			re+=1;l=a[l];
		}
	}
	return re;
}
signed main(){
	int k=0,A,B,C,X,Y,Z,W;
	cin>>n>>m>>s;
	f(i,1,m){
		scanf("%lld %lld %lld",&A,&B,&C);
		p[A].push_back((xy){B,C});
		b[++k]=B;b[++k]=C;
	}
	f(i,1,s){
		scanf("%lld %lld %lld %lld",&X,&Y,&Z,&W);
		if(Y<=W)t[i]=(asks){X,Y,Z,W};
		else t[i]=(asks){Z,W,X,Y};
		b[++k]=Y;b[++k]=W;
	}
	merge_lines();
	sort(b+1,b+k+1);k=unique(b+1,b+k+1)-b-1;
	T.bt(1,1,k);
	f(i,1,n)for(auto&e:q[i])if(e.x<inf){
		e.x=lower_bound(b+1,b+k+1,e.x)-b;
		e.y=lower_bound(b+1,b+k+1,e.y)-b;
		T.set(1,e.x,e.y,e.y);
	}
	init_fk(k);
	f(i,1,s){
		X=t[i].u1;Y=t[i].f1;Z=t[i].u2;W=t[i].f2;
		l=W-Y;
		Y=lower_bound(b+1,b+k+1,Y)-b;
		W=lower_bound(b+1,b+k+1,W)-b;
		xy e;
		e=*lower_bound(q[X].begin(),q[X].end(),(xy){Y,Y});
		if(e.x<=Y&&Y<=e.y)Y=e.y;
		e=*lower_bound(q[Z].begin(),q[Z].end(),(xy){W,W});
		if(e.x<=W&&W<=e.y)W=e.x;
		if(Y>=W){
			printf("%lld\n",l+(X!=Z));
		}else{
			m=clac(Y,W);
			printf("%lld\n",m<0?m:l+m);
		}
	}
	return 0;
}
```

---

