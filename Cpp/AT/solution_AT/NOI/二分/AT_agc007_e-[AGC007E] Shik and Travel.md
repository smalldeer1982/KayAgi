# [AGC007E] Shik and Travel

## 题目描述

[problemUrl]: https://atcoder.jp/contests/agc007/tasks/agc007_e

ある国には $ N $ 個の都市があり、それらは $ N-1 $ 本の道路で結ばれています。道路は双方向に通行できます。便宜上、都市には $ 1 $ から $ N $ の、道路には $ 1 $ から $ N-1 $ の番号が振られています。グラフ理論の用語を用いると、任意の二つの都市に対し、それらを結ぶ単純道がちょうど一つ存在します。すなわち、都市と道路から構成されるグラフは木です。また、$ 1 $ 番の都市をこの木の根とみなすと、この木は全二分木となっています。（全二分木とは、葉以外の任意の頂点がちょうど二つの子を持つような根付き木のことをいいます。）$ i $ 番の道路は $ i+1 $ 番の都市と $ a_i $ 番の都市を結び、一回の通行ごとに $ v_i $ の通行料が発生します。（$ v_i $ が $ 0 $ であるような道路では通行料は発生しません。）

$ 1 $ 番の都市に、社員の旅行を奨励していることで有名な会社があります。この会社には道路通行料補助制度という制度があり、社員の旅行中に発生する道路の通行料のほとんどを会社が負担します。旅行がこの制度の適用対象となるためにはいくつかの制約を満たす必要があり、その範囲内であれば好きなように旅程を決めることができます。これらの詳細は以下の通りです。

- 制度の適用対象となるためには、旅行の出発点と終着点はともに $ 1 $ 番の都市でなければならない。また、この国の都市と道路を $ 1 $ 番の都市を根とする根付き木とみなしたとき、この木の葉の個数を $ m $ とすると、旅行日程は $ m $ 泊 $ m+1 $ 日でなければならない。これらの $ m $ 回の宿泊は、木の葉に相当する都市のすべてで一度ずつ行わなければならない。
- 旅行全体を通じて、この国のすべての道路をそれぞれちょうど二度ずつ通行しなければならない。
- 旅行中に発生する道路の通行料のうち、社員自身が負担しなければならない金額は、発生する通行料の合計が最大であるような日（ただし旅行初日および最終日を除く）に発生する通行料の合計である。残りの金額は会社の負担となる。

シックはこの会社の従業員です。道路通行料補助制度のもとで行う今度の旅行では、発生する通行料のうち自分自身で支払わなければならない金額を最小にすることだけを考えています。そのような旅程を組む手伝いをしてあげてください。

## 说明/提示

### 制約

- $ 2\ <\ N\ <\ 131,072 $
- すべての $ i $ に対し、$ 1\ \leq\ a_i\ \leq\ i $
- $ 0\ \leq\ v_i\ \leq\ 131,072 $
- $ v_i $ は整数である。
- 与えられる木は全二分木である。

### Sample Explanation 1

都市と道路を $ 1 $ 番の都市を根とする根付き木とみなしたとき、この木には $ 4 $ 個の葉が存在するため（$ 4,\ 5,\ 6,\ 7 $ 番の都市に相当する頂点）、 旅行日程は $ 4 $ 泊 $ 5 $ 日となります。これらの $ 4 $ つの都市に宿泊する順序は $ 4!\ =\ 24 $ 通り存在しますが、そのうちの一部では道路通行料補助制度の対象外となってしまいます。例えば、$ (4,5,6,7) $ や $ (6,7,5,4) $ の順に都市を訪れると制度の対象になりますが、$ (5,6,7,4) $ の順に訪れると経路中に $ 1 $ 番の都市と $ 2 $ 番の都市を結ぶ道路を $ 4 $ 回通ってしまい、制度の対象外となってしまいます。下図にこれらの訪問順序に対応する旅行の経路を示します。 !\[04b39e0341af562ba20ba2d49c6f2b69.jpg\](https://atcoder.jp/img/agc007/04b39e0341af562ba20ba2d49c6f2b69.jpg) 制度の対象となるような都市の訪問順序すべてにおいて、対応する旅程では $ 3 $ 日目に $ 4 $ 本の道路を通行して合計で $ 4 $ の通行料が発生し、発生する通行料の合計が最大であるような日はこの日となります。

### Sample Explanation 2

下図に負担金額が最小となるような旅行の経路をひとつ示します。 !\[92271892911b34032766803fa9c9e159.jpg\](https://atcoder.jp/img/agc007/92271892911b34032766803fa9c9e159.jpg) 負担金額を算出する際に、旅行初日および最終日に発生する通行料は考えないことに注意してください。

## 样例 #1

### 输入

```
7
1 1
1 1
2 1
2 1
3 1
3 1```

### 输出

```
4```

## 样例 #2

### 输入

```
9
1 2
1 2
3 2
3 2
5 2
5 2
7 2
7 2```

### 输出

```
6```

## 样例 #3

### 输入

```
15
1 2
1 5
3 3
4 3
4 3
6 5
5 4
5 3
6 3
3 2
11 5
11 3
13 2
13 1```

### 输出

```
15```

## 样例 #4

### 输入

```
3
1 0
1 0```

### 输出

```
0```

# 题解

## 作者：wurzang (赞：20)

显然这题的答案满足可二分性。

问题变成判断是否存在一种方案，能使所有的叶子节点间的路径费用小于等于一个定值 $Value$ 且满足题目中的限制。

发现一条边不能经过两次，显然当我们进入一棵子树时，必须要把子树中所有的叶子节点全部遍历后才能离开这棵子树。

考虑判定性相关的 dp ，设 $f_u(a,b)$ 表示当前节点 $u$ 的子树中是否存在一种方案：

- 从 $u$ 出发到第一个叶子节点的路径长度为 $a$ ，从 $u$ 出发到最后一个叶子节点的路径长度为 $b$。

- 所有的路径长度都不大于 $Value$。

- 在满足所有以上限制的情况下，遍历完 $u$ 的整棵子树。

对于这个 dp，可以考虑从 $u$ 的左儿子和右儿子处进行转移。

设 $u$ 的左儿子为 $lson_u$，$u$ 到左儿子的距离为 $val_l$，右儿子为 $rson_u$ ，$u$ 到右儿子的距离为 $val_r$。

有转移式 $f_u(a,b)=f_{lson_u}(a,i)  \ \& \ f_{rson_u}(j,b) \ (i+j+val_l+val_r \le Value)$

（对转移式的解释：从 $u$ 出发到 $lson_u$ 的第一个叶子节点，从该叶子节点到 $lson_u$ 的最后一个叶子节点，从该叶子节点出发到 $rson_u$ 的第一个叶子节点）

复杂度爆炸，考虑怎么优化这个 dp。

发现当 $f_u(a_1,b_1)$ 和 $f_u(a_2,b_2)$ 满足 $a_1\le a_2,b_1\le b_2$ 的时候，$f_u(a_2,b_2)$ 是显然不必要存在的。

考虑把 $f_u$ 的状态按 $a$ 排序，根据上面的性质，排序后的 $f_u$ 状态在 $b$ 递减时是最少的。

显然，对于每一个 $f_{lson_u}(a_1,b_1)$ 都只需要考虑一个令 $b_2$ 最小且满足转移式的 $f_{rson_u}(a_2,b_2)$。所以，每一个 $f_{lson_u}$ 对应的状态只需要与一个对应的 $f_{rson_u}$ 的状态转移到 $f_u$ 上，每次转移增加的状态数是 $2\times \min(x,y)$ （$x$ 是 $f_{lson_u}$ 的状态数，$y$ 是 $f_{rson_u}$ 的状态数，注意 $lson_u$ 和 $rson_u$ 是可以反过来再转移一次的），显然状态总数是 $n \log n$ 的。

至于如何找到这个最小的 $b_2$，直接 `two-points` 即可。（至于为什么可以 `two-points` 是因为 $a$ 递增而 $b$ 递减）

时间复杂度 $\mathcal{O}(n \log n \log v)$，其中 $v$ 是二分答案中 $r$ 的权值。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define pb push_back
#define pii pair<ll,ll>
#define fi first
#define se second
typedef long long ll;
const int N=2e5+5;
int ch[N][2],val[N][2];
vector<pii> v[N];
void dfs(int x,ll Value){
	v[x].clear();
	if(!ch[x][0]) return (void)(v[x].pb({0,0}));
	for(int i=0;i<2;++i)
		if(ch[x][i]) dfs(ch[x][i],Value);
	vector<pii> vec;
	for(int dy=0;dy<2;++dy){
		int ls=ch[x][0^dy],rs=ch[x][1^dy];
		ll tmp=Value-val[x][0]-val[x][1];
		for(int i=0,j=0;i<v[ls].size();++i){
			while(j+1<v[rs].size() && v[rs][j+1].fi<=tmp-v[ls][i].se) ++j;
			if(j>=v[rs].size() || v[rs][j].fi>tmp-v[ls][i].se) continue;
			vec.pb({v[ls][i].fi+val[x][0^dy],v[rs][j].se+val[x][1^dy]});
		}
	}
	sort(vec.begin(),vec.end());
	for(int i=0;i<vec.size();++i){
		if(!v[x].empty() && v[x].back().se<=vec[i].se) continue;
		v[x].pb(vec[i]);
	}
}
bool check(ll mid){
	dfs(1,mid);
	return v[1].size()>=1;
}
signed main(){
	freopen("eight.in","r",stdin);
	freopen("eight.out","w",stdout);
	int n,fa,Val;
	cin>>n;
	ll l=0,r=0,ans=0,mid;
	for(int i=2;i<=n;++i){
		cin>>fa>>Val;
		r+=Val;
		if(ch[fa][0]) ch[fa][1]=i,val[fa][1]=Val;
		else ch[fa][0]=i,val[fa][0]=Val;
	}
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)) r=mid-1,ans=mid;
		else l=mid+1;
	}
	cout<<ans;
	return 0;
}
```


---

## 作者：CYJian (赞：8)

## AGC 007 E

这题也算是比较简单的题目吧。

首先按照题目的这个走法，我们每次到达一个点之后，只能先把其一个子树遍历完之后才能遍历另一个子树。

不难发现，我们有一个非常显然而暴力的 $dp$：

设 $f_{x,l,r,v}$ 表示 $x$ 号点，其子树内第一个被遍历的叶子节点到 $x$ 的距离为 $l$，最后一个被遍历的叶子节点到 $x$ 的距离为 $r$，此时的最小值为 $v$ 是否可行。

转移非常显然，就只需要每次枚举 $x$ 的左儿子的所有状态，右儿子的所有状态，然后枚举先遍历左儿子还是右儿子，然后把中间两个距离加起来合并一下就好了。

然后这种做法理论上肯定无法通过此题，考虑优化：

首先最后一维我们可以在外层套一个二分答案，然后省去这一维，只需要检查根节点是否有可行状态就行了。

然后现在的问题就在于如何缩减状态数以及快速转移。

首先对于两个状态： $f_{x,l_1,r_1}$ 和 $f_{x,l_2,r_2}$ ，如果有： $l_1 \leq l_2$ 并且 $r_1 \leq r_2$ ，那么 $f_{x,l_2,r_2}$ 这个状态是完全不必要的了。

这样我们就有了单调性。考虑在转移的时候利用这种单调性：

我们考虑两个子树都按照 $l$ 升序排好序之后，$r$ 一定是降序排的。那么对于一个状态 $f_{x,l_1,r_1}$，其在另一棵子树中的可合并转移的状态一定是一个前缀。那么我们每次只需要取这个前缀中 $l$ 最大的那个 $r$ 就行了。

容易发现由于事先已经排好序了，所以可以使用 ${\rm two-points}$ 做到 $O(\text{状态数})$。但是状态数是多少呢？

不难发现，如果一个点 $x$ 所连接的两个儿子的子树内的状态数分别为 $L$ 和 $R$，那么 $x$ 的状态数最坏是 $2 \times \min(L,R)$ 的。那么数量级的证明就可以类似启发式合并的复杂度分析方法，得到状态数是 $O(n \log n)$ 的。那么加上外层的二分答案就是 $O(n \log^2 n)$ 的了。

${\rm Code}$

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int __SIZE = 1 << 18;
char ibuf[__SIZE], *iS, *iT;

#define ge (iS == iT ? (iT = (iS = ibuf) + fread(ibuf, 1, __SIZE, stdin), (iS == iT ? EOF : *iS++)) : *iS++)
#define ri read_int()
#define rl read_ll()
#define FILE(s) freopen(s"in", "r", stdin), freopen(s"out", "w", stdout)

template<typename T>
inline void read(T &x) {
		char ch, t = 0; x = 0;
		while(!isdigit(ch = ge)) t |= ch == '-';
		while(isdigit(ch)) x = x * 10 + (ch ^ 48), ch = ge;
		x = t ? -x : x;
}
inline int read_int() { int x; return read(x), x; }
inline ll read_ll() { ll x; return read(x), x; }

template<typename T>
inline void chkmin(T&a, T b) { a = a < b ? a : b; }

const int MAXN = 132000;

int tot;
int fi[MAXN];
int ne[MAXN << 1];
int to[MAXN << 1];
int vl[MAXN << 1];

inline void Link(int u, int v, int w) {
	tot++;
	to[tot] = v;
	vl[tot] = w;
	ne[tot] = fi[u];
	fi[u] = tot;
}

struct Node {
	ll a, b;

	Node() {}
	Node(ll a, ll b):a(a), b(b) {}

	friend bool operator < (Node a, Node b) {
		return a.a < b.a;
	}
}A[MAXN * 20], tmp[MAXN * 20];

int L[MAXN];
int R[MAXN];
int n;
int cnt;

inline void gb_Merge(int l1, int r1, int l2, int r2) {
	int l = l1, r = r2, k = l1;
	while(l1 <= r1 && l2 <= r2) {
		if(A[l1] < A[l2]) tmp[k++] = A[l1++];
		else tmp[k++] = A[l2++];
	}
	while(l1 <= r1) tmp[k++] = A[l1++];
	while(l2 <= r2) tmp[k++] = A[l2++];
	while(k > l) --k, A[k] = tmp[k];
}

inline void Merge(int x, int l, int r, ll lim) {
	int pl1 = cnt + 1, pr1 = cnt;
	ll mi = 1LL << 61;
	for(int i = L[l], j = L[r] - 1; i <= R[l]; ++i) {
		while(j < R[r] && A[i].b + A[j + 1].a <= lim) ++j, mi = mi < A[j].b ? mi : A[j].b;
		if(j < L[r]) continue;
		A[++pr1] = Node(A[i].a, mi);
	} cnt = pr1;
	int pl2 = cnt + 1, pr2 = cnt;
	mi = 1LL << 61, swap(l, r);
	for(int i = L[l], j = L[r] - 1; i <= R[l]; ++i) {
		while(j < R[r] && A[i].b + A[j + 1].a <= lim) ++j, mi = mi < A[j].b ? mi : A[j].b;
		if(j < L[r]) continue;
		A[++pr2] = Node(A[i].a, A[j].b);
	} cnt = pr2, L[x] = pl1, R[x] = pr2;
	if(L[x] > R[x]) return ;
	gb_Merge(pl1, pr1, pl2, pr2);
	int Sum = 0;
	for(int i = L[x] + 1; i <= R[x]; ++i) {
		if(A[i].b >= A[L[x] + Sum].b) continue;
		else ++Sum, A[L[x] + Sum] = A[i];
	} cnt = R[x] = L[x] + Sum;
}

inline void dfs(int x, ll lim) {
	if(!fi[x]) {
		L[x] = R[x] = ++cnt;
		A[cnt] = Node(0, 0);
	}
	else {
		L[x] = cnt + 1, R[x] = cnt;
		int val, Ls = to[fi[x]], Rs = to[ne[fi[x]]];
		
		dfs(Ls, lim), val = vl[fi[x]];
		if(L[Ls] > R[Ls]) return;
		for(int i = L[Ls]; i <= R[Ls]; i++) A[i].a += val, A[i].b += val; 

		dfs(Rs, lim), val = vl[ne[fi[x]]];
		if(L[Rs] > R[Rs]) return ;
		for(int i = L[Rs]; i <= R[Rs]; i++) A[i].a += val, A[i].b += val; 
		
		Merge(x, Ls, Rs, lim);
	}
}

inline bool chk(ll lim) {
	cnt = 0, dfs(1, lim);
	return L[1] <= R[1];
}

int main() {
#ifndef ONLINE_JUDGE
	FILE("");
#endif
	n = ri;
	ll mx = 0;
	for(int i = 2; i <= n; i++) {
		int f = ri, v = ri;
		Link(f, i, v);
		mx += v;
	} ll l = 0, r = mx, res;
	while(l <= r) {
		ll mid = (l + r) >> 1;
		if(chk(mid)) r = mid - 1, res = mid;
		else l = mid + 1;
	} printf("%lld\n", res);
	return 0;
}
```

---

## 作者：Cure_Wing (赞：3)

[AT_agc007_e [AGC007E] Shik and Travel](https://www.luogu.com.cn/problem/AT_agc007_e)

### 解析

看到这种求最大值最小的问题，首先想二分，不要在意对还是不对。

对于单调性，一定存在一个值 $x$ 满足不存在小于 $x$ 的答案，所以可以二分。

假设我们二分的值是 $x$，接下来计算答案是否合法。

因为“要求到过所有叶子并且每条边经过恰好两次”，所以你走到一个节点时，必须先走完左右儿子在回到父亲，比如图 $\texttt{c15mgasc-1}$。

![](https://cdn.luogu.com.cn/upload/image_hosting/4c3k2xkb.png)

由于走到一个节点时，子树内没有任何处理；走出一个节点时，子树内全部处理完了，这样我们可以很方便的在子树的根节点上记录信息。

记录什么信息呢？我们发现除了子树内部两两相连的叶子节点，存在两个叶子结点各留下一条没有对应的路径（如图 $\texttt{c15mgasc-1}$ 节点处两段绿色部分），一条进入子树，一条离开子树。由于在这个节点处，四条路径最终只能留下两条，所以有两条需要合并。记录点 $u$ 的两条路径为 $fx_u$ 和 $fy_u$，需要合并的节点为 $p$ 和 $q$。对于合并的两条，显然需要满足 $fx_p+fy_q\le x$（或 $fx_p+fx_q\le x$ 如此之类）,然后把 $fy_p$ 和 $fx_q$（或 $fy_q$ 和 $fx_p$ 如此之类）传递到父亲的 $fx$ 和 $fy$。注意到符合条件的 $(fx_u,fy_u)$ 可能不止一对，所以都要存下来。这个时候如果暴力枚举 $(p,q)$ 的 $fx$ 和 $fy$ 时间复杂度就是 $O(n^2)$ 的。

优化这个过程非常简单，我们对所有的 $(fx_u,fy_u)$ 复制出一个 $(fy_u,fx_u)$，然后按第一个元素从小到大排序，强制让第一个元素参与匹配。定义 $fx_{u,i}$ 表示 $u$ 子树内合法链的第 $i$ 条。对于需要匹配的 $fx_{p,i}$，假设对应的 $q$ 匹配为 $fx_{q,j}$，由于随着 $i$ 的增大，$fx_{p,i}$ 也增大，所以 $fx_{q,j}$ 需要减小，也就是 $j$ 也要减小。当然 $j$ 可以用一个指针维护。对于一个 $fx_{p,i}$，我们一定会去取在符合条件的 $fx_{q,j}$ 中 $fy_{q,j}$ 最小的那个，这有助于减小之后向上出去的链的长度。

像这样一直合并直到 $1$ 号节点。如果到 $1$ 号节点存在合法的路径对，说明这个 $x$ 值可以实现；否则由于路径被废弃，$1$ 号节点没有记录下任何信息。

但是全部都由左子树向右子树合并统计的信息数量会爆炸，考虑每次合并都会增加至多 $n$ 对路径。这个优化考虑启发式合并。因为对于 $fx_{p,a}$，匹配出去的对数不会超过 $a$。同样我们考虑有效链数 $a$ 小的去匹配有效链数大的，这样合并上去的链的对数只有 $\min\{siz_p,siz_q\}\le\dfrac{siz_u}{2}$（$siz_i$ 表示 $i$ 子树内的节点数量）,综合起来记录的每一层信息数最坏是 $O(n)$，总信息数最坏是 $O(n\log_2n)$，在完全二叉树的条件下。二分检查答案时单次的时间复杂度也是这个级别。


结合上二分，时间复杂度为 $O(n\log_2n\log_2v)$（$v$ 是答案的上界，不超过输入的 $v$ 之和），空间复杂度和信息数差不多，为 $O(n\log_2n)$。

至于为什么“每个节点要么有两个儿子要么没有儿子”，考虑三个及以上儿子就不能这么简单的合并链了，一个儿子没有任何用处，完全可以跳过这个儿子把它的边权带到它的儿子去。

不优化直接交可以获得 $\texttt{1174 ms}$ 的好成绩。可以过，但是模拟赛时间限制 $1$ 秒被卡了（这也成为了第一道切了但是没完全切的黑题）。有什么可以优化的呢？考虑 $(fx_{u,i},fy_{u,i})$，如果存在一对 $c,d$，满足 $fx_{u,c}\le fx_{u,d}$ 且 $fy_{u,c}\le fy_{u,d}$，显然可以把 $(fx_{u,d},fy_{u,d})$ 直接丢弃。这样时间复杂度虽然没变，但是大大减小了计算次数，最终获得了 $\texttt{255 ms}$ 的好成绩。根据写本篇题解时洛谷上的最优解记录，这份代码排在第 $6$ 位。

```cpp
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<vector>
using std::cin;using std::cout;
constexpr int N=131076,M=262156;
constexpr long long inf=1e18;
int n,f,v,cnt,k,ent;
struct A{int u,v;};
std::vector<A>g[N];
struct B{long long u,v;}d[M],e[M];
std::vector<B>p[N];
inline void down(int u,long long x){
	if(g[u].empty()){p[u].push_back(B{0,0});return ;}//叶子节点不要忘记插入一对 (0,0)。
	down(g[u][0].u,x);down(g[u][1].u,x);
	if(p[g[u][0].u].size()<p[g[u][1].u].size()) std::swap(g[u][0],g[u][1]);//启发式合并。
	cnt=ent=0;
	for(B i:p[g[u][0].u]){d[++cnt]=B{i.u,i.v};d[++cnt]=B{i.v,i.u};}
	std::sort(d+1,d+cnt+1,[](B a,B b){return a.u<b.u||a.u==b.u&&a.v<b.v;});
	int w=cnt;cnt=0;
	for(int i=1;i<=w;++i) if(d[i].v<d[cnt].v) d[++cnt]=d[i];
	for(B i:p[g[u][1].u]){e[++ent]=B{i.u,i.v};e[++ent]=B{i.v,i.u};}
	std::sort(e+1,e+ent+1,[](B a,B b){return a.u<b.u||a.u==b.u&&a.v<b.v;});//去重减少计算次数。
	int l=ent;ent=0;
	for(int i=1;i<=l;++i) if(e[i].v<e[ent].v) e[++ent]=e[i];
	long long minn=inf;
	int pos=1;
	for(int i=ent;i;--i){
		for(;pos<=cnt&&d[pos].u+e[i].u+g[u][0].v+g[u][1].v<=x;++pos) minn=std::min(d[pos].v,minn);//指针维护最优秀的位置。
		if(pos>1) p[u].push_back(B{minn+g[u][0].v,e[i].v+g[u][1].v});//当心无解。
	}
}
class fastIO{private:char ibuf[50007],*p1=ibuf,*p2=ibuf,obuf[50007],*p3=obuf,sta[50];bool file_end=false;char get(){return p1==p2&&(p2=(p1=ibuf)+fread(ibuf,1,50007,stdin),p1==p2)?(file_end=true),char(EOF):*p1++;}void put(const char x){p3-obuf<50007?*p3++=x:(fwrite(obuf,p3-obuf,1,stdout),p3=obuf,*p3++=x);}public:explicit operator bool(){return!file_end;}size_t flush(){size_t f=fwrite(obuf,p3-obuf,1,stdout);p3=obuf;*p3=0;return f;}fastIO&operator>>(char&t){for(t=get();!isgraph(t);t=get());return*this;}template<typename any>typename std::enable_if<std::is_same<any,char>::value,any>::type tpval(){char t;for(t=get();!isgraph(t);t=get());return t;}fastIO&operator>>(char*t){char c;for(c=get();!isgraph(c);c=get());for(;isgraph(c);c=get())*t=c,t++;*t=0;return*this;}fastIO&operator>>(std::string&t){t.clear();char c;for(c=get();!isgraph(c);c=get());for(;isgraph(c);c=get())t+=c;return*this;}template<typename any>typename std::enable_if<std::is_same<any,std::string>::value,any>::type tpval(){std::string t;char c;for(c=get();!isgraph(c);c=get());for(;isgraph(c);c=get())t+=c;return t;}template<typename any>typename std::enable_if<(std::is_signed<any>::value&&std::is_integral<any>::value&&!std::is_same<any,char>::value)||std::is_same<any,__int128_t>::value,fastIO>::type&operator>>(any&t){t=0;bool y=0;char c=get();for(;!isdigit(c);c=get())if(c==45)y=true;for(;isdigit(c);c=get())t=t*10+c-48;if(y==1)t=-t;return*this;}template<typename any>typename std::enable_if<(std::is_signed<any>::value&&std::is_integral<any>::value&&!std::is_same<any,char>::value)||std::is_same<any,__int128_t>::value,any>::type tpval(){any t=0;bool y=0;char c=get();for(;!isdigit(c);c=get())if(c==45)y=true;for(;isdigit(c);c=get())t=t*10+c-48;if(y==1)t=-t;return t;}template<typename any>typename std::enable_if<(std::is_unsigned<any>::value&&std::is_integral<any>::value&&!std::is_same<any,char>::value)||std::is_same<any,__uint128_t>::value,fastIO>::type&operator>>(any&t){t=0;char c=get();for(;!isdigit(c);c=get());for(;isdigit(c);c=get())t=t*10+c-48;return*this;}template<typename any>typename std::enable_if<(std::is_unsigned<any>::value&&std::is_integral<any>::value&&!std::is_same<any,char>::value)||std::is_same<any,__uint128_t>::value,any>::type tpval(){any t=0;char c=get();for(;!isdigit(c);c=get());for(;isdigit(c);c=get())t=t*10+c-48;return t;}template<typename any1,typename any2>fastIO&operator>>(std::pair<any1,any2>&t){return*this>>t.first>>t.second;}template<typename any1,typename any2>std::pair<any1,any2>tpval(){return std::pair<any1,any2>(tpval<any1>(),tpval<any2>());}template<typename any>fastIO&read(any&t){return*this>>t;}fastIO&read(char*t){char c;for(c=get();!isgraph(c);c=get());for(;isgraph(c);c=get())*t=c,t++;*t=0;return*this;}template<typename any,typename...args>fastIO&read(any&t1,args&...t2){return(*this>>t1).read(t2...);}fastIO&operator<<(const char t){put(t);return*this;}fastIO&operator<<(const char*t){for(;*t;t++)put(*t);return*this;}fastIO&operator<<(const std::string&t){for(const char it:t)put(it);return*this;}template<typename any>typename std::enable_if<(std::is_signed<any>::value&&std::is_integral<any>::value&&!std::is_same<any,char>::value)||std::is_same<any,__int128_t>::value,fastIO>::type&operator<<(any t){if(!t){put(48);return*this;}int len=0;if(t<0)t=-t,put(45);while(t)sta[len++]=char(t%10+48),t/=10;while(len--)put(sta[len]);return*this;}template<typename any>typename std::enable_if<(std::is_unsigned<any>::value&&std::is_integral<any>::value&&!std::is_same<any,char>::value)||std::is_same<any,__uint128_t>::value,fastIO>::type&operator<<(any t){if(!t){put(48);return*this;}int len=0;while(t)sta[len++]=char(t%10+48),t/=10;while(len--)put(sta[len]);return*this;}template<typename any1,typename any2>fastIO&operator<<(const std::pair<any1,any2>&t){return*this<<t.first<<' '<<t.second;}template<typename any>fastIO&write(const any&t){return*this<<t;}template<typename any,typename...args>fastIO&write(const any&t1,const args&...t2){return(*this<<t1).write(t2...);}~fastIO(){fwrite(obuf,p3-obuf,1,stdout);}}fio;
signed main(){
	freopen("eight.in","r",stdin);
	freopen("eight.out","w",stdout);
	std::ios::sync_with_stdio(false);
	cin.tie(nullptr);cout.tie(nullptr);
	fio>>n;for(int i=2;i<=n;++i){fio>>f>>v;g[f].push_back(A{i,v});k=std::max(k,v);}
	long long l=0,r=1ll*n*k;d[0]=e[0]=B{inf,inf};//虽说二分上界应该是 v 的和，但是实测 n*k 更快；注意边界。
	while(l<=r){
		long long mid=(l+r)>>1;
		for(int i=1;i<=n;++i) p[i].clear();
		down(1,mid);
		if(p[1].empty()) l=mid+1;
		else r=mid-1;//1 号节点没有信息则不合法，寻找更小的 x。
	}
	fio<<l;//考虑 l=r 时，此时合法，r=l+1，所以答案为 l。
	return 0;fio<<"猫屋敷真由";
}//第九十八回 苦绛珠魂归离恨天 病神瑛泪洒相思地
```

最后纪念在模拟赛中第一道切了但是没完全切的这道黑题。

---

## 作者：Kinandra (赞：3)

标签: DP.

#### Part1

二分答案 $ans$ , 设 $f[u][x]$ 表示 $u$ 子树内**第一个走到的叶子节点**到 $u$ 的距离不小于 $x$ 且 每天的路径长度不超过 $ans$ 时, **最后一个走到的叶子节点**的距离 $u$ 的最小值. 转移很简单:

 $f[u][x]=min(f[R][x-f[L][x-wl]-(wl+wr)], f[L][x-f[R][x-wr]-(wl+wr)])$, 其中 $L, R$ 分别表示 $u$ 的左右儿子, $wl,wr$ 分别表示 $u$ 到 $L,R$ 的距离.

当 $f[u][x]$ 无法从其他状态转移时无解, 对于每个 $u$ 有用的状态数(记为 $g[u]$)为其子树内的叶子节点个数.

时间复杂度 $\mathcal O(n^2\log n)$.

### Part 2

深入研究发现对于每个 $u$ , 不妨令$g[L]<g[R]$ , 要么**第一个走到的叶子节点**在 $L$ 内, 要么**最后走到的叶子节点**在 $L$ 内, 则有用的状态在这两类中取到, 即 $g[u]=2g[L]$. 类似于启发式合并, 我们分析出一次判断的复杂度为 $\mathcal O(n\log n)$.

时间复杂度 $\mathcal O(n\log^2n)$.

```cpp
#include <bits/stdc++.h>
using namespace std;
int read();

int fa[200005], ch[200005][2], w[200005][2], c[200005];
struct P {
    long long l, r;
};
vector<P> p[200005], tmp;

void ins(int u, long long l, long long r) {
    if (!p[u].size() || r < (--p[u].end())->r) p[u].push_back((P){l, r});
}

bool dfs(int u, long long x) {
    if (!c[u]) return p[u].clear(), p[u].push_back((P){0, 0}), 1;
    int L, R, Wl = w[u][0], Wr = w[u][1];
    if (!dfs(L = ch[u][0], x) || !dfs(R = ch[u][1], x)) return 0;
    if (p[L].size() > p[R].size()) swap(L, R), swap(Wl, Wr);

    tmp.clear(), p[u].clear();
    int i, j;
    for (i = 0, j = -1; i < p[L].size(); ++i) {
        long long tl = p[L][i].l + Wl, tr = x - p[L][i].r - (Wl + Wr);
        while (j + 1 < p[R].size() && p[R][j + 1].l <= tr) ++j;
        if (j < 0) continue;
        if (!tmp.size() || p[R][j].r + Wr < (--tmp.end())->r)
            tmp.push_back((P){tl, p[R][j].r + Wr});
    }

    for (i = 0, j = tmp.size() - 1; i < tmp.size() && j >= 0;)
        if (tmp[i].l < tmp[j].r)
            ins(u, tmp[i].l, tmp[i].r), ++i;
        else if (tmp[i].l > tmp[j].r)
            ins(u, tmp[j].r, tmp[j].l), --j;
        else {
            tmp[i].r <= tmp[j].l ? ins(u, tmp[i].l, tmp[i].r)
                                 : ins(u, tmp[j].r, tmp[j].l);
            ++i, --j;
        }
    while (j >= 0) ins(u, tmp[j].r, tmp[j].l), --j;
    while (i < tmp.size()) ins(u, tmp[i].l, tmp[i].r), ++i;

    return p[u].size();
}
int main() {
    int n = read();
    for (int i = 2; i <= n; ++i)
        fa[i] = read(), ch[fa[i]][c[fa[i]]] = i, w[fa[i]][c[fa[i]]++] = read();
    long long l = 0, r = 40000000000, rs = r, m;
    while (l <= r) dfs(1, m = l + r >> 1) ? r = m - 1, rs = m : l = m + 1;
    printf("%lld\n", rs);
    return 0;
}

int read() {
    int x = 0, f = 1;
    char c = getchar();
    while (c < '0' || c > '9') f = (c == '-') ? -1 : f, c = getchar();
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * f;
}

```


---

## 作者：和弦 (赞：3)

# 思路
每条边只能经过一次， 那么我们进入一棵子树的时候就必须遍历完这棵子树内的所有叶节点才能再退出。

又因为这是一颗二叉树， 所以我们进入一棵以x为根的子树的时候一定是进入x的一个子树的叶节点访问到第一个在x子树中被访问到的点， 最后一个被访问的点一定在另一个子树内。
#### 见代码
```cpp
#include<bits/stdc++.h>

template <class T>
IN void in(T &x)
{
	x = 0; R char c = gc;
	for (; !isdigit(c); c = gc);
	for (;  isdigit(c); c = gc)
	x = (x << 1) + (x << 3) + c - 48;
}
template <class T> IN T max(T a, T b) {return a > b ? a : b;}
template <class T> IN T min(T a, T b) {return a < b ? a : b;}
FILE* fl;
int n, cnt;
ll bd;
struct INFO {ll din, dout;};
IN bool cmp1(const INFO &x, const INFO &y) {return x.dout < y.dout;}
IN bool cmp2(const INFO &x, const INFO &y) {return x.din == y.din ? x.dout < y.dout : x.din < y.din;}
struct Edge {int to, len, nex;} edge[MX << 1];
std::vector <INFO> stat[MX];
int head[MX], son[MX][2], dis[MX][2];
ll mn[MX];
IN void add(R int from, R int to, R int len)
{edge[++cnt] = {to, len, head[from]}, head[from] = cnt;}
void DFS(R int now, R int fa)
{
	for (R int i = head[now]; i; i = edge[i].nex)
	{
		if (edge[i].to == fa) continue;
		if (!ls) DFS(ls = edge[i].to, now), dls = edge[i].len;
		else if (!rs) DFS(rs = edge[i].to, now), drs = edge[i].len;
	}
}
void solve(std::vector <INFO> &l, std::vector <INFO> &r, std::vector <INFO> &res, R int id)
{
	if (l.size() > r.size()) std::swap(l, r);
	int lsiz = l.size(), rsiz = r.size(), cur;
	if (!lsiz) return;
	std::sort(l.begin(), l.end(), cmp1);//dout inc
	std::sort(r.begin(), r.end(), cmp2);//din inc
	mn[0] = r[0].dout; cur = rsiz - 1;
	for (R int i = 1; i < rsiz; ++i) mn[i] = min(mn[i - 1], r[i].dout);
	for (R int i = 0; i < lsiz; ++i)
	{
		W ((~cur) && l[i].dout + r[cur].din > bd) --cur;
		if (~cur) res.push_back({l[i].din, mn[cur]});
	}
	for (R int i = 0; i < lsiz; ++i) std::swap(l[i].din, l[i].dout);
	for (R int i = 0; i < rsiz; ++i) std::swap(r[i].din, r[i].dout);
	std::sort(l.begin(), l.end(), cmp1);
	std::sort(r.begin(), r.end(), cmp2);
	mn[0] = r[0].dout; cur = rsiz - 1;
	for (R int i = 1; i < rsiz; ++i) mn[i] = min(mn[i - 1], r[i].dout);
	for (R int i = 0; i < lsiz; ++i)
	{
		W ((~cur) && l[i].dout + r[cur].din > bd) --cur;
		if (~cur) res.push_back({mn[cur], l[i].din});
	}
}
void DFS(R int now)
{
	stat[now].clear();
	if (!ls) return stat[now].push_back({0, 0}), void();
	DFS(ls); DFS(rs);
	for (R int i = stat[ls].size() - 1; ~i; --i) stat[ls][i].din += dls, stat[ls][i].dout += dls;
	for (R int i = stat[rs].size() - 1; ~i; --i) stat[rs][i].din += drs, stat[rs][i].dout += drs;
	solve(stat[ls], stat[rs], stat[now], now);
}
IN bool check(R ll v)
{
	bd = v; DFS(1);
	return stat[1].size();
}
int main(void)
{
	in(n); int foo, bar;
	ll lef = 0, rig = 1e10, mid, ans;
	for (R int i = 2; i <= n; ++i)
	in(foo), in(bar), add(foo, i, bar), add(i, foo, bar);
	DFS(1, 0);
	W (lef <= rig)
	{
		mid = lef + rig >> 1;
		if (check(mid)) ans = mid, rig = mid - 1;
		else lef = mid + 1;
	}
	printf("%lld", ans);
}

```
### define
```cpp
 R register
 IN inline
 W while
 gc getchar()
 ls son[now][0]
 rs son[now][1]
 dls dis[now][0]
 drs dis[now][1]
 MX 200500
 ll long long 
```

---

## 作者：ღꦿ࿐ (赞：2)

首先考虑题目要求每条边被经过两次，这说明了我们进入一个子树后一定会处理完子树内所有的叶子后离开该子树，否则子树上端那条边会进出至少两次，即经过至少四次。所以这说明了子树之间的独立性：某个子树在答案中一定是一个连续的区间，这引导我们从有根树信息自下向上拼接的角度考虑。

我们就可以将一个有根树抽象成三部分：从根进入 $in$，内部最大值 $max$，离开回到根 $out$。内部的部分不会再发生改变，我们只关心它的最大值 $max$，然后可以通过拼接两个子树离开-进入的信息来得到父亲的信息：$(in_a,out_b,\max(max_a,max_b,out_a+in_b))$。

因为这个过程是可以倒过来走的，于是我们就只需要设置 $f_{a,b}$ 表示进入左子树的 $a$，从右子树的 $b$ 离开的最大值的最小值即可。

![](https://cdn.luogu.com.cn/upload/image_hosting/kpyhp00x.png)

于是我们通过记录所有每个点所有 $(in,out)$ 对应的 $max$ 就有了一个 $O(\text{poly}(n))$ 的做法（取决于你咋搞，反正难以低于 $O(n^2)$）。

考虑优化：若要记录内部最大值是一件很浪费的事情，我们需要最小化最大的一次，又因为我们的过程涉及到了边的加和，故肯定得考虑二分答案转化为可行性问题，问题变为需要检测答案 $Dis$ 是否可行。

然后对于刚刚那个问题，我们便不再关心每个 $(in,out)$ 了，我们只关心每个 $in$ **值**可以对应的 $out$，且如果存在 $in_1 \geq in_1,out_1 \geq out_2$，那么 $(in_1,out_1)$ 一定没用，于是我们可以通过维护一组单增的 $in$ 及其对应的一组单减的 $out$ 值来描述这个子树的信息。

考虑信息的拼接，即需要合并两组 $A(in,out),B(in,out)$，合并的条件为若有 $Aout_i + Bin_j \leq Dis$ 则有 $(Ain_i,Bout_j)$，因为 $A$ 和 $B$ 都满足随着 $in$ 增，$out$ 减，所以可以按顺序枚举 $Aout_i$ 双指针维护可行的 $Bin_j$ 即可。因为过程是可以倒过来走的，我们再把所有 $(out,in)$ 也加入，最终再排序/归并排序，去除掉没用的就可以得到父亲树内的 $(in,out)$ 序列。

直接这样做看上去复杂度是 $O(\sum siz_i)=O(n^2)$ 的，但是考虑因为我们记录的 $(in,out)$ 对中 $(in,out)$ 一者一定是左子树或右子树中的一个点深度，又因为我们保留的 $in$ 单增，$out$ 单减，所有这样的 $(in,out)$ 最多只有 $2\times light_i$ 对，其中 $light_i$ 表示 $i$ 的轻子树大小，所以复杂度是 $O(\sum light_i)=O(n\log n)$，加上外层二分，若使用归并时间复杂度 $O(n\log ^2n)$，直接 ``sort`` 三只 $\log$ 也没啥问题。


这里是[代码](https://www.luogu.com.cn/paste/a4ve93r7)，实现使用了直接上传 ```vector``` 的做法，由于累计向父亲上传的大小之和仍然不大于轻子树大小，不会影响复杂度。











---

感觉这也不难啊为啥评了 *3900 .jpg

---

## 作者：zzzYheng (赞：2)

#### 题意：

给你一棵带边权完满二叉树，即每个点儿子数要么为 $0$，要么为 $2$ 的二叉树。

你第一天从根出发到达一个叶子，然后每一天，从一个叶子出发到达另一个叶子，最后一天从一个叶子回到根。要求达到所有叶子并且经过每条边 **恰好两次**。

你的路费是你除第一天和最后一天的每一天的路径长度的最大值，你要最小化路费。

数据范围：$n \le 2\times 10^5$。

#### 思路：

首先为了方便表示路径长度，我们记 $dis_i$ 表示根节点到节点 $i$ 的距离。

显然路径的形态是欧拉环游序。

容易想到一个 naive 的树形 $\text{dp}$：令 $f_{u,i,j}$ 表示考虑对 $u$ 的子树走欧拉环游序，走到的第一个叶子为 $i$，最后一个叶子为 $j$，最小费用是多少。

转移考虑把 $u$ 的两个儿子的环游方案合并，复杂度比较高。

注意到问题的形式是经典的最大值最小化，考虑二分一个 $lim$ 后转化为判定性问题。

问题变为要求每天的路径长度都不超过 $lim$。

再考虑那个 $\text{dp}$，发现最小费用显然不必要了，我们只关心可不可行，因此状态的值可以改成 $01$。

对于这种状态的值只有 $01$ 的 $\text{dp}$，一般有两种优化思路：

1. bitset 优化，这种优化方法本质也是第二种优化方法。
2. 对于一个状态（方案分组）只记录一个 $01$ 信息太亏了，考虑是否可以用更复杂的状态值来实现用一个状态就能表示原本的多个状态。

考虑对于所有 $f_{u,i,j}$ 可行的 $j$ 只有 $dis_j$ 最小的那个是有意义的。

所以我们可以把状态改成：令 $f_{u,i}$ 表示考虑欧拉环游 $u$ 的子树，第一个到达的叶子为 $i$，最后一个到达的叶子 $dis$ 最小是多少。

然后考虑转移，令 $u$ 的两个儿子为 $v_1$ 和 $v_2$，我们要通过合并两个儿子的环游方案得到 $u$ 的环游方案。

假设先走 $v_1$ 再走 $v_2$，假设到达的 $v_1$ 中的第一个叶子为 $i$，到达的 $v_2$ 中的最后一个叶子为 $j$，那么转移为：如果 $f_{v_1,i}+f_{v_2,j}-2\cdot dis_{u} \le lim$，那么把这两个方案拼接就合法，转移 $dis_{j}\to f_{u,i}$。（注意这里欧拉环游 $v_2$ 的子树，最后一个到达的叶子为 $j$，第一个到达的叶子 $dis$ 最小是多少的答案也是 $f_{v_2,j}$）

先走 $v_2$ 再走 $v_1$ 的转移也是一样。

枚举 $i$ 后找到满足 $f_{v_1,i}+f_{v_2,j}-2\cdot dis_{u} \le lim$ 的 $dis$ 最小的 $j$ 显然可以数据结构优化，可以做到单次查询 $\Theta(\log n)$。

分析下复杂度，每次转移相当于把 $v_1$ 子树中的叶子集合和 $v_2$ 子树中的叶子集合合并得到 $u$ 中的叶子集合。但不幸的是，我们每次合并的复杂度为两个集合的大小之和乘 $\Theta(\log n)$，复杂度容易卡到 $\Theta(n^2\log n)$。

考虑用类似于启发式合并的方法完成 $v_1$ 和 $v_2$ 方案的合并。假设 $v_1$ 中的叶子数少于 $v_2$ 中的叶子数，考虑是否能做到每次合并只枚举 $v_1$ 中的叶子。

发现是可以的，枚举 $v_1$ 中的叶子显然可以完成先走 $v_1$ 再走 $v_2$ 的转移，而先走 $v_2$ 再走 $v_1$ 的转移其实不用再算，因为它的方案和先走 $v_1$ 再走 $v_2$ 的方案是完全相反的，所以最优的 $(i,j)$ 是完全相同的（只是反过来变成 $(j,i)$ 了），所以可以做到每次合并的复杂度为较小儿子的大小乘 $\Theta(\log n)$。

总复杂度 $\Theta(n\log^3 n)$。

考虑怎么继续优化，考虑找到最小的 $j$ 具体怎么用数据结构优化。

考虑把所有叶子按 $dis$ 从小到大排序，会发现 $f_{u,i}$ 只有在单调栈上的值是有意义的，具体的，如果 $dis_i<dis_j$ 且 $f_{u,i}<f_{u,j}$，那么 $f_{u,j}$ 就没有意义。

所以我们可以处理出每个节点 $f_{u,i}$ 的单调栈，这样转移就只需要在单调栈上跑一个双指针即可。

双指针的总复杂度等于每个节点的单调栈大小和，根据启发式合并的复杂度分析，这个值为 $\Theta(n\log n)$。

总复杂度 $\Theta(n \log ^2 n)$。

---

## 作者：Piwry (赞：2)

可能写得有点繁琐X

感觉主要需要注意的细节是尝试线性合并从子树得到的状态序列时的讨论

## 解析

### Part 0

简单地可以想到三个状态的 dp。具体来说，发现每个子树会且仅会进出各一次，于是枚举每个子树进出的结点，朴素转移即可

还能发现答案可二分。二分答案后，固定子树内进入的结点，不难发现出去的结点的深度一定是越浅越利于转移；这样就优化掉了一维

这样朴素地实现是 $O(n^3\log n)$ 的。注意到每次转移时我们实际上就是想找到所有进入的结点 $s$ 的深度满足限制的结点对 $(s, t)$ 中，出去的结点 $t$ 的深度最小的结点，于是不难想到按 $s$ 的深度为关键字排序后，处理一个前缀 $t$ 深度最浅的结点编号（干脆直接叫 “前缀最小值”），每移时双指针找到最后一个不满足限制的位置 $i$，那么 $[0, i-1]$ 的元素都是可行（但不一定最优）的转移，这时再查一个前缀最小值即可。这样做就是 $O(n^2\log^2 n)$ 的了

### Part 1

为了方便接下来的讨论，这里优化一些定义。首先不难发现，若子树有一对满足二分时限制的进出结点对 $(s, t)$，那么 $(t, s)$ 也是满足限制的。接着可以发现过程中我们始终只关心结点对内两个结点的深度，因此实际上我们不需要记具体进出的结点，只需记录它们的深度即可。下面设 $(u, v)$ 表示这样的结点对的深度

考虑到起点或终点必须分别在两个不同的子树，且每个结点对 $(u, v)$ 相对应的状态 $(v, u)$ 可以直接交换结点顺序得到，因此转移时实际上只需枚举状态数量较小的子树的状态即可。参照启发式合并的复杂度分析，这样状态的合并次数就是 $n\log n$ 的；于是 $\texttt{Part 0}$ 的算法就被优化到了 $O(n\log^3 n)$

关于具体实现，只需仅枚举状态数量较小的子树的状态并用刚才提到的双指针前缀最小值等为每个状态在另一颗子树中找到最优的状态合并，并且在每次添加状态 $(u, v)$ 时一并添加状态 $(v, u)$ 即可

### Part 2

不难发现，若对于两个结点对 $(u, v), (u', v')$ 满足 $u\leq u', v\leq v'$，那么 $(u, v)$ 一定比 $(u', v')$ 更优。去掉所有可以判断为不优的结点对后，不难发现，若将所有结点对按 $u$ 从小到大排序，排序的 $v$ 也一定是从大到小不增的。证明只需考虑反证即可

（下面为了描述方便，维护的实际上是 $u$ 单调不减，$v$ 单调不增；即仅去除 $(u, v), (u', v')$ 满足 $u< u', v< v'$ 的结点对。事实上改一改也可以做到上面的要求）

继续优化 $\texttt{Part 1}$ 的做法。假定每次我们从子树得到的状态序列都是去掉可判断为不优的状态并且排好序的，考虑接下来怎么做。由于 $v$ 也满足单调性，因此前缀最小值这个处理可以直接略去；考虑将每次得到的 $(u, v), (v, u)$ 放到两个不同的序列中（按得到元素的顺序的话，其中一个是以第一个元素为关键词正序，另一个则是倒叙的；不过这无所谓，对于倒叙的序列我们可以反转一下或倒着扫），于是现在的问题就是如何在线性时间内合并两个满足第一个关键词 $x$ 单调不减，第二个关键词 $y$ 单调不增的序列，且使它们在合并后仍然有序

考虑这样一种做法：先归并排序式地合并，使得按顺序添加的元素的 $x$（第一个关键词）不减；每次添加元素时，若发现 $y$ 不满足单调不增了，就抛弃新添加的元素；由于保证添加的 $x$ 不减，因此抛弃的元素一定是不优的。事实上这种合并方式的思路就来源于去除不优元素后序列满足单调性的证明

最终得到的复杂度就是 $O(n\log^2 n)$

## CODE

代码里在合并后没有显式的存下每个状态 $(u, v)$ 对应的状态 $(v, u)$；毕竟这两个序列的顺序是恰好反过来的，从两端用两个指针扫就行了。具体可见代码

我还不太确定代码中维护的序列是严格单调 递增/递减 的还是 不减/不增 的，因为分析实在有点麻烦 \fad；不过这并不影响代码正确性

```cpp
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define ll long long
using std::max;
using std::min;
using std::vector;

const int MAXN =1.5e5;

/*------------------------------IO------------------------------*/

int read(){
	int x =0; char c =getchar();
	while(c < '0' || c > '9') c =getchar();
	while(c >= '0' && c <= '9') x =(x<<1)+(x<<3)+(48^c), c =getchar();
	return x;
}

/*------------------------------Arr------------------------------*/

int n;
int ch[2][MAXN], val[2][MAXN];
ll dep[MAXN];

/*------------------------------Work------------------------------*/

void dfs_pre(const int &u){
	if(ch[0][u]){
		dep[ch[0][u]] =dep[u]+val[0][u], dfs_pre(ch[0][u]);
		dep[ch[1][u]] =dep[u]+val[1][u], dfs_pre(ch[1][u]);
	}
}

struct pad{
	// 到两个结点 ( 路径向子树外的两个结点 ) 的距离 //
	ll u, v;
	
	pad(const ll &U, const ll &V):u(U), v(V){}
	
	bool operator < (const pad &B) const{
		if(u == B.u)
			return v < B.v;
		else
			return u < B.u;
	}
	bool operator > (const pad &B) const{
		if(u == B.u)
			return v > B.v;
		else
			return u > B.u;
	}
};
vector<pad> dp[MAXN];

inline void free(vector<pad> &v){
	vector<pad> tmp;
	tmp.swap(v);
}

void dfs(const int &u, const ll &Limit){
	#define LS ch[0][u]
	#define RS ch[1][u]
	if(LS){
		dfs(LS, Limit);
		dfs(RS, Limit);
		if((int)dp[LS].size() > (int)dp[RS].size())
			dp[LS].swap(dp[RS]);
		
		vector<pad> tmp;
		tmp.reserve(dp[LS].size());
		for(int i =0, j =(int)dp[RS].size()-1; i < (int)dp[LS].size() && j >= 0; ++i){
			while(j >= 0 && dp[RS][j].u+dp[LS][i].u-2*dep[u] > Limit)
				--j;
			if(j >= 0 && (tmp.empty() || tmp.back().u != dp[RS][j].v))
				tmp.push_back(pad(dp[RS][j].v, dp[LS][i].v));
			else if(!tmp.empty() && tmp.back().u == dp[RS][j].v)
				tmp.back().v =dp[LS][i].v;/*可以注意到 dp[LS][i].v 是不增的*/
		}
		free(dp[LS]);
		free(dp[RS]);
		
		dp[u].reserve(2*tmp.size());
		auto push =[&](const pad &elm){
			if(dp[u].empty() || dp[u].back().v >= elm.v)
				dp[u].push_back(elm);
		};
		for(int i =0, j =(int)tmp.size()-1; i < (int)tmp.size() || j >= 0;){
			if(i < (int)tmp.size() && j >= 0){
				// V- 这里的判断可能不一定有必要；但懒得推了 \fad //
				if(tmp[i].u == tmp[j].v){
					if(tmp[i].v < tmp[j].u)
						push(tmp[i]);
					else
						push(pad(tmp[j].v, tmp[j].u));
					++i, --j;
				}
				else if(tmp[i].u < tmp[j].v)
					push(tmp[i++]);
				else
					push(pad(tmp[j].v, tmp[j].u)), --j;
			}
			else if(i < (int)tmp.size())
				push(tmp[i++]);
			else
				push(pad(tmp[j].v, tmp[j].u)), --j;
		}
	}
	else
		dp[u].push_back(pad(dep[u], dep[u]));
	#undef LS
	#undef RS
}

bool check(const ll &mx){
	free(dp[1]);
	dfs(1, mx);
	return !dp[1].empty();
}

/*------------------------------Main------------------------------*/

int main(){
	n =read();
	for(int i =2; i <= n; ++i){
		int fa =read(), v =read();
		if(ch[0][fa])
			ch[1][fa] =i, val[1][fa] =v;
		else
			ch[0][fa] =i, val[0][fa] =v;
	}
	dfs_pre(1);
	
	ll ans =0x3f3f3f3f3f3f3f3f;
	ll l =0, r =2e10;
	while(l <= r){
		ll mid =(l+r)>>1;
		if(check(mid)){
			r =mid-1;
			ans =min(ans, mid);
		}
		else
			l =mid+1;
	}
	
	printf("%lld", ans);
}
```

---

## 作者：Phartial (赞：1)

考虑二分答案，问题转化为判定答案是否 $\le v$。每条边恰好经过两次的约束等价于我们必须以深度优先遍历的顺序经过所有叶子，这启示我们使用树形 dp。

设 $f_{x,a,b}$ 表示只考虑以 $x$ 为根的子树，并且从 $x$ 到第一个儿子的距离为 $a$，从最后一个儿子回到 $x$ 的距离为 $b$ 时是否存在可行方案。

有转移方程 $f_{l_x,a,b}\land f_{r_x,c,d}\land b+w(x,l_x)+w(x,r_x)+c\le v\implies f_{x,a+w(x,l_x),d+w(x,r_x)}\land f_{x,c+w(x,r_x),b+w(x,l_x)}$。

直接做这个东西显然是会爆炸的，考虑优化。

注意到如果 $f_{x,a,b}$ 成立，那么对所有 $c\ge a,d\ge b$，$f_{x,c,d}$ 都是没用的了。把有效的状态留下后对 $a$ 升序排序，则 $b$ 相应的单调递减。

设点 $x$ 处的有效状态数为 $F_x$。由于 $x$ 上的一个状态 $f_{x,a,b}$ 里的 $a$ 必然来自于 $l_x$ 与 $r_x$，且 $b$ 必然来自于相应的 $r_x$ 与 $l_x$，因为有效状态的 $a$ 和 $b$ 不能重复（否则我们必然可以删掉另一维更大的状态），所以有不等式 $F_x\le 2\min(F_{l_x},F_{r_x})$，由启发式合并可以知道总状态数是 $\mathcal{O}(n\log n)$，因此我们只需要在较优的时间复杂度内不重不漏的进行转移。

> 关于 $\sum F=\mathcal{O}(n\log n)$ 的一个证明：
>
> 由 $F_x\le 2\min(F_{l_x},F_{r_x})\le F_{l_x}+F_{r_x}$ 可以得到 $F_x\le\mathrm{size}_x$，因此有 $\sum F\le 2\sum\min(F_{l_x},F_{r_x})\le 2\sum\min(\mathrm{size}_{l_x},\mathrm{size}_{r_x})$，而最后这个式子就是经典的启发式合并，因此 $\sum F=\mathcal{O}(n\log n)$。

跑两遍双指针可以得到所有合法状态，合并后去除没用的状态即可。时间复杂度 $\mathcal{O}(n\log n\log v)$。

```cpp
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using LL = long long;
using Pll = pair<LL, LL>;

const int kN = (1 << 17) + 1;

struct E {
  int y, w;
};
int n;
vector<E> e[kN];
vector<Pll> f[kN];

void D(int x, LL v) {
  if (e[x].empty()) {
    f[x].emplace_back(0, 0);
    return;
  }
  D(e[x][0].y, v), D(e[x][1].y, v);
  vector<Pll> _f[2];
  for (int o = 0; o < 2; ++o) {
    int l = e[x][o].y, r = e[x][!o].y;
    int lw = e[x][o].w, rw = e[x][!o].w;
    for (int i = 0, j = 0; i < f[l].size(); ++i) {
      for (; j + 1 < f[r].size() && f[l][i].second + f[r][j + 1].first + lw + rw <= v; ++j) {
      }
      if (j < f[r].size() && f[l][i].second + f[r][j].first + lw + rw <= v) {
        _f[o].emplace_back(f[l][i].first + lw, f[r][j].second + rw);
      }
    }
  }
  vector<Pll> rf(_f[0].size() + _f[1].size());
  merge(_f[0].begin(), _f[0].end(), _f[1].begin(), _f[1].end(), rf.begin());
  for (Pll i : rf) {
    if (f[x].empty() || f[x].back().first < i.first && f[x].back().second > i.second) {
      f[x].push_back(i);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  cin >> n;
  for (int i = 2, y, w; i <= n; ++i) {
    cin >> y >> w;
    e[y].push_back({i, w});
  }
  LL l = 0, r = 1e12;
  while (l < r) {
    LL m = l + r >> 1;
    for (int i = 1; i <= n; ++i) {
      f[i].clear();
    }
    D(1, m);
    if (f[1].empty()) {
      l = m + 1;
    } else {
      r = m;
    }
  }
  cout << l;
  return 0;
}
```


---

## 作者：cbdsopa (赞：1)

[AGC007E Shik and Travel](https://www.luogu.com.cn/problem/AT2172)

题目大意：$n$ 个点的二叉树，每个点要么两个儿子，要么没有儿子，每条边有边权。

你从 $1$ 号节点出发，走到一个叶子节点。然后每一天，你可以从当前点走到另一个叶子。最后回到 $1$ 号节点，要求到过所有叶子并且每条边经过**恰好两次**。求一种遍历顺序，使得每相邻两叶子间的边权和的最大值最小。

### 题解

考虑二分最大值，看是否可行。这个点是一种类似等号转限制的做法。

因此我们只需考虑能否在不经过权值和大于 $k$ 的叶子间的路径即可。这个怎么做呢？由于我们只关心距离，我们对于每个点可以得到一些数对 $(a,b)$ ，表示当前点子树中可以从距离当前点距离为 $a$ 的叶子进入，从距离当前点距离为 $b$ 的叶子退出。并且记 $S_u$  为对于 $u$ 这个点来说形如 $(a,b)$ 的数对集合。

对于没有儿子的点，存在数对 $(0,0)$ 。而对于有儿子的点，由题目限制每条边和每个叶子恰好过两次，可知一个子树内的叶子肯定先互相到达，再离开当前子树，去与最近的子树中的叶子互达。因此我们得到一个非叶子节点的数对，等价于我们将其左右子树的某两个叶子相连接，用左右子树的数对表示，可以得到对于一个子树的数对 $(a,b)$ 和另一个子树的数对 $(c,d)$ ，当 $b+c+val[u][0]+val[u][1]\le k$ 时（$val[u][0/1]$ 表示 $u$ 向左右儿子的边权），这两个数对可以合并，得到数对 $(a+val[u][0],b+val[u][1])$ ,这是默认 $(a,b)$ 为左子树数对，反过来的话 $val$ 换一下就好。

但是直接暴力合并数对是寄的。我们考虑优化，显然对于两个点对 $(a,b)$ 和 $(c,d)$ ，如果 $a\le c,b\le d$ ，那么可以知道 $(c,d)$ 是无用的。其次由于我们希望合并出来的数对的两个值都尽量小，且每个数对 $(a,b)$ 都满足 $a+b\le k$ ，我们对于一个子树中的数对肯定有唯一的一个另一个子树的数对与之对应来得到最小的数对。

我们对于数对按照 $a$ 从小到大排序，那么由于 $a+b\le k$ 显然 $b$ 递减，我们考虑决策单调性来合并即可。

然后我们有决策单调性的话，显然复杂度就是数对总数的，然后由于是一个二叉树，易证复杂度 $O(n\log^2 n)$ ，总复杂度 $O(34n\log^2 n)$。（$34$ 是二分复杂度）

参考代码：

```cpp
#include<bits/stdc++.h>
#define ll long long
#define db double
#define filein(a) freopen(#a".in","r",stdin)
#define fileot(a) freopen(#a".out","w",stdout)
#define sky fflush(stdout);
#define gc getchar
#define pc putchar
namespace IO{
	inline bool blank(const char &c){
		return c==' ' or c=='\n' or c=='\t' or c=='\r' or c==EOF;
	}
	inline void gs(char *s){
		char ch=gc();
		while(blank(ch) ) {ch=gc();}
		while(!blank(ch) ) {*s++=ch;ch=gc();}
		*s=0;
	}
	inline void gs(std::string &s){
		char ch=gc();s+='#';
		while(blank(ch) ) {ch=gc();}
		while(!blank(ch) ) {s+=ch;ch=gc();}
	}
	inline void ps(char *s){
		while(*s!=0) pc(*s++);
	}
	inline void ps(const std::string &s){
		for(auto it:s) 
			if(it!='#') pc(it);
	}
	template<class T>
	inline void read(T &s){
		s=0;char ch=gc();bool f=0;
		while(ch<'0'||'9'<ch) {if(ch=='-') f=1;ch=gc();}
		while('0'<=ch&&ch<='9') {s=s*10+(ch^48);ch=gc();}
		if(ch=='.'){
			db p=0.1;ch=gc();
			while('0'<=ch&&ch<='9') {s=s+p*(ch^48);p*=0.1;ch=gc();}
		}
		s=f?-s:s;
	}
	template<class T,class ...A>
	inline void read(T &s,A &...a){
		read(s);read(a...);
	}
};
using IO::read;
using IO::gs;
using IO::ps;
const int N=(1<<17)+3;
int n;
int ch[N][2],val[N][2];
struct node{
	int a,b;
};
std::vector<node>S[N],psc;
void dfs(int u,ll k){
	S[u].clear();
	if(!ch[u][0]){
		S[u].push_back({0,0});
		return;
	}
	dfs(ch[u][0],k);
	dfs(ch[u][1],k);
	int lc=ch[u][0],rc=ch[u][1];
	psc.clear();
	int j=-1;
	for(auto it:S[lc]){
		while(j+1<S[rc].size() and S[rc][j+1].a+it.b+val[u][1]+val[u][0]<=k){
			++j;
		}
		if(j>=S[rc].size() ) continue;
		if(S[rc][j].a+it.b+val[u][1]+val[u][0]>k) continue;
		psc.push_back({it.a+val[u][0],S[rc][j].b+val[u][1]});
	}
	j=-1;
	for(auto it:S[rc]){
		while(j+1<S[lc].size() and S[lc][j+1].a+it.b+val[u][1]+val[u][0]<=k){
			++j;
		}
		if(j>=S[lc].size() ) continue;
		if(S[lc][j].a+it.b+val[u][1]+val[u][0]>k) continue;
		psc.push_back({it.a+val[u][1],S[lc][j].b+val[u][0]});
	}
	int sz=psc.size();
	std::sort(psc.begin(),psc.end(),[](node x,node y){
		return x.a<y.a;
	});
	for(int i=0;i<sz;++i){
		if(i!=0){
			if(psc[i-1].b<=psc[i].b){
				continue;
			}
		}
		S[u].push_back(psc[i]);
	}
}
inline bool check(int u,ll k){
	dfs(1,k);
	return S[1].size();
}
int main(){
	filein(a);fileot(a);
	read(n);
	for(int u=2;u<=n;++u){
		int f,w; read(f,w);
		if(!ch[f][0]) ch[f][0]=u,val[f][0]=w;
		else ch[f][1]=u,val[f][1]=w;
	}
	ll l=0,r=1ll*(1ll<<17)*(1ll<<17),hf=r;
	while(l<=r){
		ll mid=(l+r)>>1;
		if(check(1,mid) ){
			r=mid-1;hf=mid;
		}else{
			l=mid+1;
		}
	} 
	printf("%lld\n",hf);
	return 0;
}

```


---

## 作者：tylon2006 (赞：1)

## solution
看到最大值最小，先来个二分答案。

转化成判定性问题，发现问题简化不少，可以树形 dp。

因为是二叉树，且每条边只能经过两次，必然是一进一出，那么每走到一个点就必须一次性走完它的子树中所有叶子。

根据一进一出，我们可以大力设 dp 状态 $dp[x][l][r]$ 表示是否存在进入 x 子树，走到第一个叶子经过的距离为 l，从最后一个叶子回到 x 的距离为 r。

显然存这么多 $(l,r)$ 很蠢，只每个点存下可能的 $(l,r)$ 即可。

然后发现如果存在 $(l_1,r_1),(l_2,r_2)$ 使得 $l_1<l_2$ 且 $r_1<r_2$，那么 $(l_2,r_2)$ 明显没有任何贡献。

通过这种决策单调性就可以大大减少每个点的决策点数，具体表现为维护一个 $l$ 递增而 $r$ 递减的序列。

合并两个儿子转移时，对于一个儿子的 $(l,r)$，能够与其合并的必然是另一个儿子的决策点序列的前缀。那么我们只需要选择最靠后的与其合并，显然这样更优。

设 $siz[x]$ 表示 x 的决策点序列大小。可知这样合并，x 的决策点序列大小为 $2\times \min(siz[lson]+siz[rson])$。

类似于启发式合并，可以简单证明 dp 时间复杂度是 $O(n\log n)$ 的。或是考虑每个叶子决策点的被统计次数，根据树高为 $\log n$ 亦可得出。

那么总时间复杂度为 $O(n\log n\log V)$，其中 $V=2n\log n$。

---
## code

此处使用数组实现。由于取到的决策点序列大小总是不超过两个儿子的序列大小之和且连续，于是可以记录在同一段区间上，反复利用空间。

另外一点是 vector 的 clear() 并不会真正释放空间，而是标记为释放过。但是它会重复利用其空间。实际上不释放空间的空间复杂度是 $O(n\log n)$ 的。感觉比较不爽，而且有大常数。

于是虽然判断边界有点麻烦，常数有点大，但是还是拿下 rank1。

```cpp
#include<bits/stdc++.h>
using namespace std;
struct Data{
	int l,r;
	Data(int x=0,int y=0){
		l=x,r=y;
	}
}a[140010];
Data q[140010][2];
int son[140010][2];
int val[140010][2];
int bd[140010][2];
int s[2];
int n,tot,mx;
void dfs(int x){
	if(son[x][0]==0){
		a[++tot]=Data(0,0);
		bd[x][0]=bd[x][1]=tot;
		return;
	}
	dfs(son[x][0]);
	int y=son[x][0],z=val[x][0];
	for(int i=bd[y][0];i<=bd[y][1];i++) a[i].l+=z,a[i].r+=z;
	if(son[x][1]==0){
		bd[x][0]=bd[y][0];
		bd[x][1]=bd[y][1];
		return;
	}
	dfs(son[x][1]);
	y=son[x][1],z=val[x][1];
	for(int i=bd[y][0];i<=bd[y][1];i++) a[i].l+=z,a[i].r+=z;
	s[0]=s[1]=0;
	for(int i=0;i<2;i++){
		y=son[x][i],z=son[x][i^1];
		for(int j=bd[y][0],k=bd[z][0];j<=bd[y][1];j++){
			while(k<=bd[z][1]&&a[j].r+a[k].l<=mx) k++;
			if(k==bd[z][0]) continue;
			q[++s[i]][i]=Data(a[j].l,a[k-1].r); 
		}
	}
	y=son[x][0],z=son[x][1];
	int i=1,j=1,k=bd[y][0]-1;
	for(;i<=s[0];i++){
		while(j<=s[1]&&q[j][1].l<=q[i][0].l){
			if(k<bd[y][0]||q[j][1].r<a[k].r) a[++k]=q[j][1];
			j++;
		}
		if(k>=bd[y][0]&&a[k].l==q[i][0].l) a[k].r=min(a[k].r,q[i][0].r);
		else if(k<bd[y][0]||q[i][0].r<a[k].r) a[++k]=q[i][0];
	}
	for(;j<=s[1];j++) 
	if(k<bd[y][0]||q[j][1].r<a[k].r) a[++k]=q[j][1];
	bd[x][0]=bd[y][0];
	bd[x][1]=k;
}
bool check(int mid){
	tot=0,mx=mid;
	dfs(1);
	return bd[1][0]<=bd[1][1];
}
inline int read(){
	int x=0,f=1; 
	char c=getchar();
	for(;isdigit(c);c=getchar()) x=x*10+c-'0';
	return x*f;
}
int main(){
	int x,y;
	n=read();
	for(int i=2;i<=n;i++){
		x=read(),y=read();
		if(son[x][0]==0) son[x][0]=i,val[x][0]=y;
		else son[x][1]=i,val[x][1]=y;
	}
	int l=-1,r=4200000;
	while(l<r-1){
		int mid=(l+r)>>1;
		if(check(mid)) r=mid;
		else l=mid;
	}
	printf("%d",r);
}
```



---

## 作者：0xyz (赞：0)

最大值最小，一眼二分。问题转化为对于一个 $v$，问存不存在一个遍历所有叶子节点的顺序使得相邻两个叶子节点距离 $\le v$，并且一旦进入一个子树，就会访问完所有的叶子再离开。

考虑 DP。令 $f_{x,l,r}$ 表示 $x$ 的子树内，存不存在一个合理的访问顺序使得第一个叶子距离 $x$ 为 $l$，最后一个叶子距离 $x$ 为 $r$。显然，$l,r$ 越小越好，对于 $l_1\le l_2,r_1\le r_2$，$f_{x,l_1,r_1}$ 能做的贡献覆盖了 $f_{x,l_2,r_2}$。所以我们对于每个点 $x$ 维护一个集合 $s_x$，它存储的是满足 $f_{x,l,r}=1$，并且在 $l$ 相同时，不存在更小的 $r$，$r$ 相同时，不存在更小的 $l$ 的所有 $(l,r)$。显然，如果 $(l,r)\in s_x$，那么 $(r,l)\in s_x$。所以，任意一对 $(l,r)$ 一定有一个数来自较小的子树，从而 $|s_x|\le 2\min(sz_{ls},sz_{rs}),\sum|s_x|=O(n\log n)$。所以，我们直接从叶子节点开始暴力维护每个点的 $s_x$，将右子树的每一个 $(l,r)$ 找到左子树中满足 $l'+r+v_{ls}+v_{rs}\le v$ 且 $l'$ 最大，同时 $r'$ 最小的那一对 $(l',r')$，直接匹配即可。对于 $l$ 在左子树的情况，将前面找到的所有 $(l,r')$ 交换 $l,r'$ 即可，最后排序并且去掉不满足最优性的 $(l,r)$ 即可得到 $s_x$。时间复杂度 $O(\log v\sum|s_x|\log |s_x|)=O(n\log v\log^2 n)$，可以通过此题。

```cpp
#include<bits/stdc++.h>
#define X first
#define Y second
#define P push_back
using namespace std;
typedef long long ll;
typedef pair<ll,ll> L;
const ll _=2e5+5;
vector<L>s[_],e[_];
ll n,m,w,l,r=2e10,z;
void dfs(ll x,ll v){
	if(e[x].size()){
		vector<L>S,U;
		for(L y:e[x])dfs(y.X,z),v-=y.Y;
		for(ll i=0,j=-1;i<s[e[x][1].X].size();i++){
			while(j+1<s[e[x][0].X].size()&&s[e[x][0].X][j+1].X+s[e[x][1].X][i].Y<=v)j++;
			if(~j)S.P({s[e[x][1].X][i].X+e[x][1].Y,s[e[x][0].X][j].Y+e[x][0].Y});
		}
		s[e[x][0].X].clear();s[e[x][1].X].clear();
		for(L i:S)U.P(i),U.P({i.Y,i.X});
		sort(U.begin(),U.end());
		if(U.size())s[x].P(U[0]);
		for(ll i=1;i<U.size();i++)
			if(s[x].back().X<U[i].X&&U[i].Y<s[x].back().Y)s[x].P(U[i]);
	}else s[x].P({0,0});
}
int main(){
	cin>>n;
	for(ll i=2,x,y;i<=n;i++)cin>>x>>y,e[x].P({i,y});
	while(l<=r)s[1].clear(),dfs(1,z=l+r>>1),s[1].size()?r=z-1:l=z+1;
	cout<<l<<'\n';
	return 0;
}
```

注意到其实 $s_{ls},s_{rs}$ 本身有序，所以可以把 `sort` 改成归并，时间复杂度 $O(n\log v\log n)$。但是细节太多，且 `sort` 常数极小，我就没有写。

---

## 作者：yqr123YQR (赞：0)

### 分析
感觉很显然。

二分最大值，重点来到 `check` 上。设要 `check` 的值为 $lim$。

对于一个子树 $\operatorname{sub}(k)$，必有一条 **入路径** 与一条 **出路径**，且完整路径在子树中的部分必为先走一个儿子的子树，走完了再走另一个。

考虑先走左子树的情况，右子树同理。枚举左右子树的状态 $({in}_l,{out}_l),({in}_r,{out}_r)$，若 $out_l+in_r+v_l+v_r\leqslant lim$，说明可以衔接，即添加状态 $({in}_l+v_l,{out}_r+v_r)$。

前面都是写暴力时应该想到的东西，~~下面除了复杂度证明也是~~。直接记录状态数爆炸，极易想到缩减无用状态（话说打暴力的也会这么想吧）：若同时存在合法状态 $(a,b),(c,d)$，不妨设 $a\leqslant c$，且 $b\leqslant d$，则 $(c,d)$ 完全无用。故将状态 $(in,out)$ 以 $in$ 作关键字从小到大排序后，$in$ 单调递增，$out$ 单调递减。

有了单调性，合并时，对于枚举的左子树状态 $({in}_l,{out}_l)$，就能用双指针快速确定可选的右子树状态，且只需取其中 $out$ 最小的那个。最后将左右子树各自先走的状态合并、排序，`check` 返回根结点 $1$ 是否有合法状态。这样就能解决此题。

时间复杂度 $O(n\log n\log V)$，$V=\sum v$。**若不采用归并实现，为 $O(n\log n^2\log V)$。**

  $\log V$ 来自二分，$n\log n$ 来自看似极易超时的合并。合并时，由于精简了状态，设 ${sz}_i$ 表示 $i$ 子树的合法状态数，$l_i/r_i$ 表示 $i$ 的左右儿子，则对于非叶结点 $i$，${sz}_i\leqslant 2\min\{{sz}_{l_i},{sz}_{r_i}\}$，总状态数即为 $O(\sum{sz})=O(n\log n)$。

> 注意：合并后 $in,out$ 均不能出现相同的值，否则 ${sz}_i={sz}_{l_i}+{sz}_{r_i}$，总复杂度退化为 $O(n^2)$。
### 代码
```cpp
#include<stdio.h>
#include<ctype.h>
#include<vector>
namespace IO {
	constexpr int bufsize = 230005;
	char buf[bufsize], *f1, *f2;
	#define gtchar() (f1 == f2 && (f2 = buf + fread(f1 = buf, 1, bufsize, stdin)) == buf? EOF: *f1++)
	template<typename t> void read(t &ret)
	{
		int f = ret = 0;
		char ch = gtchar();
		while(!isdigit(ch)) f = ch == '-', ch = gtchar();
		while(isdigit(ch)) ret = (ret << 3) + (ret << 1) + (ch ^ 48), ch = gtchar();
		if(f) ret = -ret;
	}
	#undef gtchar
	template<typename t, typename ...T> void read(t &a, T &...b) {read(a), read(b...);}
}using IO::read;
typedef long long ll;
typedef std::pair<ll, ll> pll;
constexpr int maxn = 150005;
int n, l[maxn], r[maxn], val[maxn];
std::vector<pll> state[maxn];
bool dfs(int k, ll limit)// 判断 k 子树是否有合法状态
{
	if(!l[k]) return true;
	if(!dfs(l[k], limit)) return false;
	if(!dfs(r[k], limit)) return false;
	state[k].clear();
	std::vector<pll> &s = state[k];
	auto it = state[r[k]].begin();
	ll tmp = val[l[k]] + val[r[k]];
	std::vector<pll> a, b;
	// printf("k:%d\n", k);
	for(auto i : state[l[k]])// 先走左子树
	{
		while(it != state[r[k]].end() && tmp + i.second + it->first <= limit) ++it;
		if(it != state[r[k]].begin()) a.push_back({i.first + val[l[k]], prev(it)->second + val[r[k]]});
	}
	// printf("k:%d\n", k);
	it = state[l[k]].begin();
	for(auto i : state[r[k]])// 先走右子树
	{
		while(it != state[l[k]].end() && tmp + i.second + it->first <= limit) ++it;
		if(it != state[l[k]].begin()) b.push_back({i.first + val[r[k]], prev(it)->second + val[l[k]]});
	}
	// printf("k:%d\n", k);
	// 归并
	auto ita = a.begin(), itb = b.begin();
	while(ita != a.end() && itb != b.end())
	{
		if(ita->first < itb->first)
		{
			if(s.empty() || s.rbegin()->second > ita->second) s.push_back(*ita);
			++ita;
		}
		else
		{
			if(s.empty() || s.rbegin()->second > itb->second) s.push_back(*itb);
			++itb;
		}
	}
	while(ita != a.end())
	{
		if(s.empty() || s.rbegin()->second > ita->second) s.push_back(*ita);
		++ita;
	}
	while(itb != b.end())
	{
		if(s.empty() || s.rbegin()->second > itb->second) s.push_back(*itb);
		++itb;
	}
	return !s.empty();
}
bool check(ll mid)
{
	// printf("check %lld\n", mid);
	return dfs(1, mid);
}
int main()
{
	// freopen("b.in", "r", stdin);
	// freopen("b.out", "w", stdout);
	read(n);
	ll L = 0, R = 0;
	for(int i = 2, f; i <= n; i++)
	{
		read(f, val[i]), R += val[i];
		if(!l[f]) l[f] = i;
		else r[f] = i;
	}
	for(int i = 1; i <= n; i++) if(!l[i]) state[i].push_back({0, 0});
	while(L < R)// 二分最大值
	{
		ll mid = L + R >> 1;
		if(check(mid)) R = mid;
		else L = mid + 1;
	}
	printf("%lld\n", L);
	return 0;
}
```

---

## 作者：KingPowers (赞：0)

模拟赛搬了这题，感觉是很厉害的题啊，可惜我一点不会。

答案显然具有可二分性，所以先考虑二分答案，判断最远的相邻叶子距离是否可以不超过 $mid$。

先分析一下我们走的过程，因为要求每条边恰好走了两次，所以对于每一棵子树我们一定是完整地走完了子树内的所有叶子之后再出来，且这棵子树恰好进出各一次。

直接做是很不方便的，所以我们考虑设计一个 dp 来判断。因为一共就两个儿子，所以我们不妨枚举先走哪个。这里称先进入的儿子为左儿子，后进入的儿子为右儿子。根据我们上面的分析，我们发现合并两个儿子子树内的路径只需要关心每个儿子先走到的叶子和最后走到的叶子到它的距离，所以可以这么设计：设 $f_{u,a,b}$ 表示考虑 $u$ 子树的内部，是否存在一个走法，使得第一个叶子到自己的距离为 $a$，最后一个叶子到自己的距离为 $b$，且相邻距离不超过 $mid$。

转移是容易的，假设当前点 $u$ 的左右儿子分别为 $x,y$，那么 $f_{x,a,b}\& f_{y,c,d}$ 可以转移到 $f_{u,a+wl,d+wr}$，条件为 $b+c+wl+wr\le mid$，其中 $wl,wr$ 表示 $u$ 连接左右儿子的边的边权。但是这样复杂度显然爆炸了。

我们考虑优化这个过程，注意到如果 $f_{u,a,b}$ 和 $f_{u,c,d}$ 均合法且 $a\le c,b\le d$，那么 $f_{u,c,d}$ 这个状态是完全没用的，因为用 $f_{u,a,b}$ 来代替它肯定更优。所以我们如果把 $f_{u,a,b}$ 视作 $u$ 点上的一个点对 $(a,b)$ 的话，那么我们只需要维护之间没有偏序关系的点对，具体来说我们考虑把所有点对按照 $a$ 升序排序，那么这时候我们就强制要求 $b$ 递减，否则一定是没用的。

现在我们顺序枚举左儿子一个点对 $(a,b)$，那么右儿子 $(c,d)$ 应当是最靠后的满足 $c\le mid-wl-wr-b$ 的点，可以双指针维护转移（这里需要仔细思考下，因为左儿子的 $b$ 是递减的，右儿子的 $c$ 是递增的，而且越靠后 $d$ 越小，合并起来更优）。

合并出来所有的点对之后，像刚才说的方式一样，按 $a$ 升序排序后去掉 $b$ 不递减的点对。注意一点，这里需要将两种情况合并出来的点对归并处理而不是使用 `std::sort`，否则复杂度会多 $\log$。

然后似乎就没有进展了，但现在这题其实已经做完了。考虑分析下现在的复杂度，我们每次转移的复杂度关于状态数是线性的，假设两个儿子分别有 $a,b$ 个点对，我们发现自己最多只会产生 $2\times\min(a,b)$ 个点对，这样产生的点对数和启发式合并是相同的，只有 $O(n\log n)$ 对，也就是说现在我们整个判断过程的复杂度是 $O(n\log n)$ 的。

带上二分，我们就以 $O(n\log n\log V)$ 的时间复杂度解决了本题。

```cpp
#include<bits/stdc++.h>
#define int long long
#define For(i, a, b) for(int i = (a); i <= (b); i++)
#define Rof(i, a, b) for(int i = (a); i >= (b); i--)
#define deb(x) cerr << #x"=" << x << '\n';
using namespace std;
using PII = pair<int, int>;
const int N = 2e5 + 5;
int n, ch[N][2], val[N][2];
vector<PII> v[N];
vector<PII> merge(vector<PII> A, vector<PII> B){
	vector<PII> res;
	int i = 0, j = 0;
	while(i < A.size() && j < B.size()){
		if(A[i] < B[j]) res.emplace_back(A[i]), i++;
		else res.emplace_back(B[j]), j++;
	}
	while(i < A.size()) res.emplace_back(A[i]), i++;
	while(j < B.size()) res.emplace_back(B[j]), j++;
	return res;
}
void dfs(int now, int mid){
	if(!ch[now][0]) return v[now].push_back({0, 0});
	dfs(ch[now][0], mid); dfs(ch[now][1], mid);
	vector<PII> va, vb;
	For(tmp, 0, 1){
		int ls = ch[now][tmp], rs = ch[now][tmp ^ 1];
		int wl = val[now][tmp], wr = val[now][tmp ^ 1];
		for(int i = 0, j = 0; i < v[ls].size(); i++){
			int goal = mid - wl - wr - v[ls][i].second;
			while(j + 1 < v[rs].size() && v[rs][j + 1].first <= goal) j++;
			if(j >= v[rs].size() || v[rs][j].first > goal) continue;
			if(tmp == 0) va.push_back({v[ls][i].first + wl, v[rs][j].second + wr});
			else vb.push_back({v[ls][i].first + wl, v[rs][j].second + wr});
		}
	}
	auto res = merge(va, vb);
	for(int i = 0; i < res.size(); i++){
		if(!v[now].empty() && v[now].back().second <= res[i].second) continue;
		v[now].emplace_back(res[i]);
	}
}
bool check(int mid){
	For(i, 1, n) v[i].clear();
	dfs(1, mid);
	return !v[1].empty();
}
void Solve(){
	cin >> n;
	For(i, 2, n){
		int j, w; cin >> j >> w;
		if(!ch[j][0]) ch[j][0] = i, val[j][0] = w;
		else ch[j][1] = i, val[j][1] = w;
	}
	int l = 0, r = 2e10, ans = 2e10;
	while(l <= r){
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	cout << ans << '\n';
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	int T = 1; //cin >> T;
	while(T--) Solve();
	return 0;
}
```

---

