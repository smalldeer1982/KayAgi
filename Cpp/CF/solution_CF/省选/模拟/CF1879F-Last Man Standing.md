# Last Man Standing

## 题目描述

There are $ n $ heroes in a videogame. Each hero has some health value $ h $ and initial armor value $ a $ . Let the current value of armor be $ a_{\mathit{cur}} $ , initially equal to $ a $ .

When $ x $ points of damage are inflicted on a hero, the following happens: if $ x < a_{\mathit{cur}} $ , then $ x $ gets subtracted from $ a_{\mathit{cur}} $ ; otherwise, $ 1 $ gets subtracted from $ h $ and $ a_{\mathit{cur}} $ gets assigned back to $ a $ .

In the start of the game, you choose the value $ x $ (an integer strictly greater than $ 0 $ , arbitrarily large). Then you keep attacking all heroes in rounds: in one round, you inflict $ x $ points of damage to all alive heroes. A hero dies when his health becomes $ 0 $ . The game ends when all heroes are dead.

The last hero to die earns the number of points, equal to the number of rounds he was the only hero alive. The other heroes get $ 0 $ points. In particular, if the last round ends with multiple heroes dying, then every hero gets $ 0 $ points.

The game is played for every possible $ x $ (from $ 1 $ to infinity). The points are reset between the games. What's the maximum number of points each hero has had?

## 说明/提示

In the first testcase, the game for $ x = 1 $ is played as follows:

- before all rounds: the heroes have $ h = [3, 1, 2] $ , $ a_{\mathit{cur}} = [3, 11, 5] $ ;
- round $ 1 $ : $ 1 $ damage is inflicted on every hero: $ h $ remains $ [3, 1, 2] $ , $ a_{\mathit{cur}} $ becomes $ [2, 10, 4] $ ;
- round $ 2 $ : $ h = [3, 1, 2] $ , $ a_{\mathit{cur}} = [1, 9, 3] $ ;
- round $ 3 $ : the first hero runs out of armor, so he loses a health point: $ h = [2, 1, 2] $ , $ a_{\mathit{cur}} = [3, 8, 2] $ ;
- ...
- round $ 9 $ : the first hero dies, since his health reaches $ 0 $ : $ h = [0, 1, 1] $ , $ a_{\mathit{cur}} = [0, 2, 1] $ ;
- round $ 10 $ : the third hero dies: $ h = [0, 1, 0] $ , $ a_{\mathit{cur}} = [0, 1, 0] $ ;
- round $ 11 $ : the second hero dies: $ h = [0, 0, 0] $ , $ a_{\mathit{cur}} = [0, 0, 0] $ .

The second hero was the last hero to die, and he was the only hero alive during one round. Thus, he gets $ 1 $ point for that game.

The game for $ x = 4 $ is played as follows:

- round $ 1 $ : $ h = [2, 1, 2] $ , $ a_{\mathit{cur}} = [3, 7, 1] $ ;
- round $ 2 $ : $ h = [1, 1, 1] $ , $ a_{\mathit{cur}} = [3, 3, 5] $ ;
- round $ 3 $ : $ h = [0, 0, 1] $ , $ a_{\mathit{cur}} = [0, 0, 1] $ ;
- round $ 4 $ : $ h = [0, 0, 0] $ , $ a_{\mathit{cur}} = [0, 0, 0] $ ;

The third hero was the last hero to die, and he was the only hero alive during one round.

## 样例 #1

### 输入

```
3
3
3 1 2
3 11 5
1
100
200
4
5 9 5 1
9 2 9 10```

### 输出

```
1 1 1 
20000 
0 4 0 0```

# 题解

## 作者：RockyYue (赞：3)

### 题意
$n$ 个人。第 $i$ 个人有 $h_i$ 条命，每条命生命值为 $a_i$。

你可以选择一个攻击值 $x$，每轮攻击中所有人当前命的生命值减 $x$，若小于等于 $0$ 则这条命作废，$h_i$ 条命用完即死亡，执行若干轮攻击，直到最终只剩下一个人（若最后若干个人同时死亡则当前 $x$ 作废）。则最终的这个人的分数为还能承受的攻击轮数。

对于每个人，选择适当的 $x$，求其最大的分数。

其中 $n,h_i,a_i\le 2\times 10^5$。

### 题解

确定 $x$ 后，一个人可以承受的攻击次数为 $h_i\cdot \lceil\frac{a_i}{x} \rceil$。那么我们可以按 $x$ 处理，对于每个 $x$ 更新对应最后一个人的答案。设 $l=\max_{i=1}^{n}{\{a_i \}}$，枚举 $1\le x\le l$，对于每个人分别计算次数即可，复杂度 $O(nl)$。

考虑优化这个找最后一个人的过程。由分块我们可以知道 $\lceil\frac{a_i}{x} \rceil$ 的取值至多有 $\sqrt {a_i}$ 种，而如果若干个人这个式子的值相同，其中 $h_i$ 最大者最优，也就是说只有这个人可能成为最后的人。

具体实现，考虑将 $a$ 升序排列，这样相同的若干段 $\lceil\frac{a_i}{x} \rceil$ 便会聚集在一起，段数不超过 $\sqrt l$，可以对这一段用线段树或 ST 表求最大的$h_i$及其位置，复杂度 $O(l\sqrt l \cdot \log n)$，这里的 $\log$ 是二分当前区间右端点的过程。

考虑从 $\sqrt l$ 这里继续优化。换一个角度考虑，按 $a$ 取值的区间而非 $a$ 中下标区间来考虑，对于 $\lceil\frac{a_i}{x} \rceil$ 相同的一段 $a$ 的取值区间求 $h_i$ 最大值和次大值。

具体地，维护区间 ```max1,max2,maxid``` 其中 ```max1,max2``` 定义如上，```maxid``` 表示 ```max1``` 对应的 $h$ 的下标。更新答案时，我们对于当前 $x$ 将对于所有 $\lceil\frac{a_i}{x} \rceil$ 取值区间中最大的 $h$ 与上式相乘再比较，得出当前 $x$ 下对于所有人的 ```max1,max2,maxid```，此时分别表示承受次数最大承受次数，次大承受次数和最后留下的人。最后答案更新，将人 ```maxid``` 的最大分数与 ```max1-max2``` 取 $\max$ 即可。

接下来的问题是维护区间这三个值使用的数据结构。因为没有修改，容易想到 ST 表。但是仔细想想即可排除：ST 表的问题需要满足可重复贡献性，而这里维护的 ```max2``` 却不符合。具体地，若 ST 表中计算重复的区间中包含 ```max1```，相当于 ```max1``` 在这个区间中贡献了两次，有 ```max2=max1```，故错误。
所以我们用权值线段树，每次查询复杂度 $O(\log l)$，枚举$a$取值区间复杂度为调和级数的 $O(n\log n)$，总复杂度 $O(n \log n \log l)$。

后面就是激动人心的卡常部分，注意以下几点：

- 一些形式：快读、long long、inline、不要 memset、开 O2
- 写法优化
```cpp
if (y <= mid) return qry(id << 1, l, mid, x, y);
if (x > mid) return qry(id << 1 | 1, mid + 1, r, x, y);
node res = qry(id << 1, l, mid, x, y); pushup(res, qry(id << 1 | 1, mid + 1, r, x, y));
return res;
```

以下是 5615 ms 的代码。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimized(2)
using namespace std;
#define ll long long
const ll N = 2e5 + 5;
struct node {
	ll max1, max2, maxid;
} t[N << 2];
ll h[N], a[N];
inline ll Max(ll x, ll y) { return x > y ? x : y; }
inline ll Min(ll x, ll y) { return x < y ? x : y; }
inline void pushup(node &rt, node tt, ll k = 1) {
	tt.max1 *= k, tt.max2 *= k;
	rt = {Max(rt.max1, tt.max1), Max(Max(rt.max2, tt.max2), Min(rt.max1, tt.max1)), rt.max1 >= tt.max1 ? rt.maxid : tt.maxid};
}
inline void upd(ll id, ll l, ll r, ll x, node v) {
	if (l == r) return pushup(t[id], v);
	ll mid = (l + r) >> 1;
	if (x <= mid) upd(id << 1, l, mid, x, v);
	else upd(id << 1 | 1, mid + 1, r, x, v);
	t[id] = t[id << 1], pushup(t[id], t[id << 1 | 1]);
}
inline node qry(ll id, ll l, ll r, ll x, ll y) {
	if (x <= l && r <= y) return t[id];
	ll mid = (l + r) >> 1;
//	node res = {0, 0, 0};
	if (y <= mid) return qry(id << 1, l, mid, x, y);
	if (x > mid) return qry(id << 1 | 1, mid + 1, r, x, y);
	node res = qry(id << 1, l, mid, x, y); pushup(res, qry(id << 1 | 1, mid + 1, r, x, y));
	return res;
//	if (x <= mid) pushup(res, qry(id << 1, l, mid, x, y));
//	if (y > mid) pushup(res, qry(id << 1 | 1, mid + 1, r, x, y));
//	return res;
}
ll b[N];
inline void tmax(ll &x, ll y) {
	if (x < y) x = y;
}
namespace fasti{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*(p1++);}
	inline void read(ll&x){
		char c=getc(),f=0;
		for(;!isdigit(c);c=getc())f^=!(c^'-');
		for(x=0;isdigit(c);c=getc())x=x*10+(c^48);
		if(f)x=-x;--p1;
	}
	template<typename... Args>
	inline void read(ll&x,Args&...args){read(x),read(args...);}
}
using fasti::getc;
using fasti::read;
inline void write(ll x) {
	if (x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main() {
	ll T; read(T);
	while (T--) { 
		ll n; read(n); ll maxa = 0; 
		for (ll i = 1; i <= n; ++i) read(h[i]);
		for (ll i = 1; i <= n; ++i) read(a[i]), tmax(maxa, a[i]);
		for (ll i = 1; i <= n; ++i) upd(1, 1, maxa, a[i], {h[i], 0, i});
		for (ll i = 1; i <= maxa; ++i) {
			node res = {0, 0, 0};
			for (ll j = i; j <= maxa; j += i) pushup(res, qry(1, 1, maxa, j - i + 1, j), j / i);
			if (maxa % i != 0) {
				ll k = maxa / i * i;
				pushup(res, qry(1, 1, maxa, k + 1, maxa), k / i + 1);
			}
			tmax(b[res.maxid], res.max1 - res.max2);
		}
		for (ll i = 1; i <= n; ++i) write(b[i]), putchar(' '), b[i] = 0; putchar('\n');
		for (ll i = 0; i <= maxa * 4; ++i) t[i] = {0, 0, 0};
	}
	return 0;
}
```

### 2023.10.1 Upd:
经 [small_rubbish](https://www.luogu.com.cn/user/378346) 指点，本题确实可以使用 ST 表维护区间最大及次大的 $h$，可以省掉一个 $\log l$，总复杂度 $O(n\log n)$，具体见 [ST表维护次大值](https://rockyyue.blog.luogu.org/st-biao-wei-hu-ou-jian-ci-tai-zhi)。

```cpp
#include <bits/stdc++.h>
#pragma GCC optimized(2)
using namespace std;
#define int long long
const int N = 2e5 + 5, M = 20;
struct node {
	int max1, max2, maxid;
};
int h[N], a[N];
inline void pushup(node &rt, node tt, int k = 1) {
	tt.max1 *= k, tt.max2 *= k;
	rt = {max(rt.max1, tt.max1), max(max(rt.max2, tt.max2), min(rt.max1, tt.max1)), rt.max1 >= tt.max1 ? rt.maxid : tt.maxid};
}
int b[N];
inline void tmax(int &x, int y) {
	if (x < y) x = y;
}
node f[N][M];
int l[N][M], r[N][M];
void init(int n) {
	for (int j = 1; j < M; ++j) {
		for (int i = 1; i + (1 << j) - 1 <= n; ++i) {
			int t = i + (1 << (j - 1)), fl = f[i][j - 1].max1, fr = f[t][j - 1].max1;
			if (fl >= fr) f[i][j].max1 = fl, f[i][j].maxid = f[i][j - 1].maxid;
			else f[i][j].max1 = fr, f[i][j].maxid = f[t][j - 1].maxid;
			if (fl == fr) l[i][j] = l[i][j - 1], r[i][j] = r[t][j - 1];
			else if (fl > fr) l[i][j] = l[i][j - 1], r[i][j] = r[i][j - 1];
			else l[i][j] = l[t][j - 1], r[i][j] = r[t][j - 1];
			f[i][j].max2 = max(f[i][j - 1].max2, f[t][j - 1].max2);
			if (fl != fr) f[i][j].max2 = max(f[i][j].max2, min(fl, fr));
		}
	}
}
node qry(int x, int y) {
	int t = log2(y - x + 1), tt = y - (1 << t) + 1, fl = f[x][t].max1, fr = f[tt][t].max1;
	int max1, maxid, max2 = max(f[x][t].max2, f[tt][t].max2);
	if (fl != fr) max2 = max(max2, min(fl, fr));
	if (fl >= fr) max1 = fl, maxid = f[x][t].maxid;
	else max1 = fr, maxid = f[tt][t].maxid;
	bool mul_max1 = 0;
	if (fl == fr) mul_max1 = l[x][t] != r[tt][t];
	else if (fl > fr) mul_max1 = l[x][t] != r[x][t];
	else mul_max1 = l[tt][t] != r[tt][t];
	if (mul_max1) max2 = max1;
	return {max1, max2, maxid};
}
namespace fasti{
	char buf[1<<21],*p1=buf,*p2=buf;
	inline char getc(){return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*(p1++);}
	inline void read(int &x){
		char c=getc();
		for(;!isdigit(c);c=getc());
		for(x=0;isdigit(c);c=getc())x=x*10+(c^48);
	}
}
using fasti::getc;
using fasti::read;
inline void write(int x) {
	if (x >= 10) write(x / 10);
	putchar(x % 10 + '0');
}
signed main() {
	int T; read(T);
	while (T--) { 
		int n, maxa = 0; read(n);
		for (int i = 1; i <= n; ++i) read(h[i]);
		for (int i = 1; i <= n; ++i) read(a[i]), tmax(maxa, a[i]);
		for (int i = 1; i <= n; ++i) pushup(f[a[i]][0], {h[i], 0, i}), l[a[i]][0] = r[a[i]][0] = a[i];
		init(maxa);
		for (int i = 1; i <= maxa; ++i) {
			node res = {0, 0, 0};
			for (int j = i; j <= maxa; j += i) pushup(res, qry(j - i + 1, j), j / i);
			if (maxa % i != 0) {
				int k = maxa / i * i;
				pushup(res, qry(k + 1, maxa), k / i + 1);
			}
			tmax(b[res.maxid], res.max1 - res.max2);
		}
		for (int i = 1; i <= n; ++i) write(b[i]), putchar(' '); putchar('\n');
		for (int i = 1; i <= n; ++i) f[a[i]][0] = {0, 0, 0}, l[a[i]][0] = r[a[i]][0] = b[i] = 0;
	}
	return 0;
}
```

---

## 作者：Leo_LeLe (赞：2)

对于每个 $x$，我们可以很容易地知道每个英雄将持续多少回合。这等于 $h\lceil\frac ax\rceil$。

最后死亡的英雄就是这个值最大的那个，而他是唯一活着的英雄的回合数由次大值决定。

同时注意到所有 $x$ 大于或等于最大值 $a$ 的行为都是一样的。在一个回合中，所有英雄都只损失一点生命值。

因此，计算所有 $x\in[1,\max a]$。

目前的问题如下：对于每个 $x\in[1,\max a]$ 计算 最大值和次大值的索引和值。

让我们按 $c=\lceil\frac ax\rceil$ 的值将所有英雄分组，

组中英雄的 $a$ 的值构成了从 $x⋅(c-1)+1$ 到 $x⋅c$ 的区间。

在每组中，我们只关心 $h$ 上的最大值和次大值。

因此，如果我们能在 $O(1)$ 的时间内提取出最大值和次大值，那么解法将只需 $O(a\ln a)$ 的时间。

首先，对于每个 $a$ 的最大值和次大值，要查询某段上的最大值，我们可以使用 $ST$ 表。

显然，我们也可以修改它来查询次大值。

总体复杂度 $O(n+a\log a)$。

```cpp
#include <bits/stdc++.h>

#define forn(i, n) for (int i = 0; i < int(n); i++)

using namespace std;

int main() {
	int t;
	scanf("%d", &t);
	while (t--){
		int n;
		scanf("%d", &n);
		vector<int> h(n), a(n);
		forn(i, n) scanf("%d", &h[i]);
		forn(i, n) scanf("%d", &a[i]);
		int mxa = *max_element(a.begin(), a.end()) + 1;
		
		int l = mxa == 1 ? 0 : (__lg(mxa - 1) + 1);
		vector<vector<pair<int, int>>> st(l, vector<pair<int, int>>(mxa, make_pair(0, -1)));
		vector<vector<int>> st2(l, vector<int>(mxa));
		forn(i, n){
			if (h[i] > st[0][a[i]].first){
				st2[0][a[i]] = st[0][a[i]].first;
				st[0][a[i]] = {h[i], i};
			}
			else if (h[i] > st2[0][a[i]]){
				st2[0][a[i]] = h[i];
			}
		}
		
		auto combine = [&st, &st2](int i, int x, int y){
			int mx = max(st[i][x].first, st[i][y].first);
			if (mx == st[i][x].first)
				return max(st2[i][x], st[i][y].first);
			return max(st[i][x].first, st2[i][y]);
		};
		
		for (int j = 1; j < l; ++j) forn(i, mxa){
			if (i + (1 << (j - 1)) < mxa){
				st[j][i] = max(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
				st2[j][i] = combine(j - 1, i, i + (1 << (j - 1)));
			}
			else{
				st[j][i] = st[j - 1][i];
				st2[j][i] = st2[j - 1][i];
			}
		}
		vector<int> pw(mxa + 1);
		for (int i = 2; i <= mxa; ++i) pw[i] = pw[i / 2] + 1;
		
		auto getmx = [&st, &pw](int l, int r){
			int len = pw[r - l];
			return max(st[len][l], st[len][r - (1 << len)]);
		};
		auto getmx2 = [&st, &st2, &pw, &combine](int l, int r){
			int len = pw[r - l];
			if (st[len][l].second != st[len][r - (1 << len)].second)
				return combine(len, l, r - (1 << len));
			return max(st2[len][l], st2[len][r - (1 << len)]);
		};
		
		vector<long long> svmx(mxa), svmx2(mxa);
		vector<int> svwho(mxa, -1);
		for (int x = 1; x < mxa; ++x){
			for (int l = 1; l < mxa; l += x){
				int r = min(mxa, l + x);
				int ac = (l - 1) / x + 1;
				auto tmp = getmx(l, r);
				long long mx = tmp.first * 1ll * ac;
				int who = tmp.second;
				long long mx2 = getmx2(l, r) * 1ll * ac;
				if (who == -1) continue;
				if (mx > svmx[x]){
					svmx2[x] = svmx[x];
					svmx[x] = mx;
					svwho[x] = who;
				}
				else if (mx > svmx2[x]){
					svmx2[x] = mx;
				}
				svmx2[x] = max(svmx2[x], mx2);
			}
		}
		
		vector<long long> ans(n);
		forn(i, mxa) if (svwho[i] != -1)
			ans[svwho[i]] = max(ans[svwho[i]], svmx[i] - svmx2[i]);
		
		forn(i, n) printf("%lld ", ans[i]);
		puts("");
	}
	return 0;
}
```

> LZM 的做法。

---

## 作者：yshpdyt (赞：1)

## 题意
有点抽象。

~~使用一下~~ [RockyYue](https://www.luogu.com.cn/chat?uid=308106) ~~概括的，感觉很简洁。~~

$n $个人每人有 $h_i$ 条命，生命值为 $a_i$，你可以选择一个伤害 $x$，每轮攻击中所有人当前命的生命值减少 $x$，若小于等于 $0$，则这条命作废，所有条命用完即死亡，执行若干轮攻击，直到最终只剩下一个人，最终的这个人的分数为还能承受的攻击轮数，若最终有两人及以上同时死亡，则所有人不得分数。

对于每个人，选择适当的 $x$，求其最大的分数。
## Sol
鲜花：一个点跑 $7$ 秒，总共 $43$ 个点，交一次乐观来看测两分钟，~~网差半天不出结果~~，卡常大半天人已经疯了。

不难发现一条命被攻击 $\left\lceil \frac{a_i}{x} \right\rceil$ 次后就会换到下一条命，所以总的存活回合是 $h_i\left\lceil \frac{a_i}{x} \right\rceil$ 。

对于最暴力的做法，枚举所有 $x$，再枚举所有位置，计算出每个人活到的最大回合，然后用最大值减去次大值，就是活到最后的人能获得的积分，最后每个人对可能的积分取最大值。


现在考虑优化，尝试从 $h_i$，$x$，$a_i$ 分别下手。

对于 $x$，虽然题目中没有给上限，但是 $x$ 如果比所有怪物的血量都高，砍谁都是一刀秒，答案就只剩下 $h_i$ 了，这种情况只需要算一次，所以可以规定 $x\in[1,\max\limits_{i=1}^n a_i]$，为了后续方便表达，设 $m=\max\limits_{i=1}^n a_i$。

对于 $a_i$，因为是向上取整，所以当 $x$ 充分大时不会有特别多个 $\left\lceil \frac{a_i}{x} \right\rceil$ 的值不同。可以直接枚举 $x$ 以及 $\left\lceil \frac{a_i}{x} \right\rceil$ 可能的取值，复杂度为调和级数，比较可行，接着令固定 $x$ 不变，考虑里面的枚举。

由于进行了枚举，我们考虑尽可能把相同的值放到一块进行一起计算，对 $a_i$ 进行排序就可以做到。我们只需要套一个二分就能找到 $\left\lceil \frac{a_i}{x} \right\rceil=j$ 的区间左右端点，事实上，只需要二分右端点，左端点可以从上次二分继承。

然后对于相同的值的连续一段区间，区间中的差异只有 $h_i$ 。则对于这一段区间，最大值和次大值就是 $h_i$ 的最大值和次大值。

那么剩下的就是维护 $h_i$ 了，维护最大值和次大值以及最大值的位置，可以考虑线段树，但是这玩意每次查询 $O(\log)$ ，本题需要频繁查询，很容易被卡，换用查询 $O(1)$ 的 st 表。

看了其他几篇题解，感觉把 st 表维护次大值写的有点麻烦了，事实上，我们只需要找到区间 $[l,r]$ 最大值的位置 $i$，然后再在 $[l,i-1]$ 和 $[i+1,r]$ 再次查询最大值，两个区间取最大就是次大值了。这样我们仅需要维护区间最大值即可。

对于一个 $x$，维护一个 $fmx$，$pos$，$smx$，分别代表 伤害为 $x$ 时积分最大值，最大值位置，次大值，$res_i$ 表示 $i$ 位置可能的积分的最大值：
$$fmx=\max\limits_{j=1}^{j\times x\le m} \left(j\times  \max\limits_{k=l}^r h_k\right)$$

$$res_{pos}=\max\limits(res_{pos},fmx-smx)$$ 

次大值计算同理。

时间复杂度 $O(Tn \log^2 n)$。

这道题比较卡常，并且需要开 ` long long` ，提供一份超级快读：

```cpp
namespace MYINPUT{
    const int S=(1<<20)+5;char B[S],*H=B,*T=B;
    inline char gc(){if(H==T) T=(H=B)+fread(B,1,S,stdin);return H==T?EOF:*H++;}
    inline int fr(){int x=0;bool fh=0;char ch=gc();while(ch<'0'||ch>'9'){if(ch=='-') fh=1;ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=gc();}return fh?-x:x;}
}using MYINPUT::fr;
```

## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define N 300005
#define endl "\n" 
#define fi first
#define se second
using namespace std;
const int mod=1e9+7;
const int inf=1e18;
const double eps=1e-6;
namespace MYINPUT{
    const int S=(1<<20)+5;char B[S],*H=B,*T=B;
    inline char gc(){if(H==T) T=(H=B)+fread(B,1,S,stdin);return H==T?EOF:*H++;}
    inline int fr(){int x=0;bool fh=0;char ch=gc();while(ch<'0'||ch>'9'){if(ch=='-') fh=1;ch=gc();}while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch^48);ch=gc();}return fh?-x:x;}
}using MYINPUT::fr;
struct node{
    int h,p,id;
    friend bool operator<(const node &a,const node &b){
        return a.p<b.p;
    }
}a[N];
int n,b[N];
ll res[N];
ll f[25][N];
int lg[N],g[25][N];
inline void work(){
    for(int i=1;i<=lg[n];i++){
        for(int j=1;j+(1<<i)-1<=n;j++){
            f[i][j]=max(f[i-1][j],f[i-1][(1<<(i-1))+j]);
            if(f[i][j]==f[i-1][j])g[i][j]=g[i-1][j];
            else g[i][j]=g[i-1][(1<<(i-1))+j];    
        }
    }
}
inline pair<ll,ll> qr(ll l,ll r) {
    ll len=r-l+1;
    ll t=max(f[lg[len]][l],f[lg[len]][r-(1<<lg[len])+1]);
    ll p=g[lg[len]][l];
    if(t==f[lg[len]][r-(1<<lg[len])+1])p=g[lg[len]][r-(1<<lg[len])+1];
    return {t,p};
}
ll mxpos=0,mxval=0,sxval=0;;
inline void calc(ll i,ll l,ll r){
    ll k=(b[l]-1)/i+1;
    auto t=qr(l,r);
    pair<ll,ll> t1={0,0},t2={0,0};
    if(t.se>l)t1=qr(l,t.se-1);
    if(t.se<r)t2=qr(t.se+1,r);
    t1=max(t1,t2);
    if(t.fi*k>mxval){
        sxval=mxval;
        mxval=t.fi*k;
        mxpos=a[t.se].id;
        if(t1.fi*k>sxval)sxval=t1.fi*k;
        return ;
    }
    if(t.fi*k>sxval)sxval=t.fi*k;
    if(t1.fi*k>sxval)sxval=t1.fi*k;   
}
inline void sol(){
    n=fr();
    for(int i=1;i<=n;i++){
        a[i].h=fr();
        a[i].id=i;
    }
    for(int i=1;i<=n;i++)a[i].p=fr();
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++){
        b[i]=a[i].p;
        f[0][i]=a[i].h;
        g[0][i]=i;
    }
    work();
    for(int i=1;i<=a[n].p;i++){
        ll l=0,r=1;
        mxpos=0,mxval=0,sxval=0;
        for(ll j=0;j*i<=a[n].p&&r<=n;j++){
            r=upper_bound(b+1,b+n+1,i*j)-(b); 
            if(l==r)continue;
            calc(i,l,r-1);
            l=r;
        }
        if(r<=n)calc(i,r,n);
        res[mxpos]=max(res[mxpos],mxval-sxval);
    }
    for(int i=1;i<=n;i++){
        cout<<res[i]<<" ";
        res[i]=0;
    }
    cout<<endl;
}
int main(){
    lg[1]=0;
    for(int i=2;i<=N-5;i++)lg[i]=lg[i/2]+1;
    int ttt=fr();
    while(ttt--)sol();
    return 0;
}
```

---

## 作者：Demeanor_Roy (赞：1)

- [原题链接](https://www.luogu.com.cn/problem/CF1879F)

------------

这 *$2800$？怕不是千位打错了。整得我一直以为自己读错题了。

考虑对于第 $i$ 位选手，若选择难度为 $x$ 的题目，则他持续的轮数为 $h_i\lceil \dfrac{v_i}{x} \rceil$。这一点不难通过简单模拟得出。

从选手的角度不方便计算答案，不妨从题的角度来看。

显然 $+\infty$ 是假的，任意 $x \geq \max(v_i)$ 的题目效果相同。

于是考虑枚举题目难度，对每道题目用最大轮数与次大轮数的差更新最大轮数选手的答案。

于是问题转化为对给定题目难度，快速求最大、次大轮数的选手。

不妨观察式子，显然 $\lceil \dfrac{v_i}{x} \rceil$ 很容易让我们联想到调和级数枚举，显然枚举后问题就变为了在 $v$ 的一段值域区间查询 $h$ 的最大值与次大值。而最大值、次大值显然是 st 表可维护的，预处理即可。

至此整道题目解决完毕，时间复杂度 $O(n + V\log V)$。

[代码](https://codeforces.com/contest/1879/submission/229666345)

---

## 作者：qczrz6v4nhp6u (赞：1)

很唐的题，但想歪到数论分块没有场切，是我更唐。

### Solution

显然对于每个 $x$，我们统计 $h_i\lceil\frac{a_i}{x}\rceil$ 的最大和次大值并将其做差即可得到当前难度 $x$ 的得分。

令 $v=\max a_i$。容易发现当 $x>v$ 时不会对答案产生任何贡献，于是我们只需要统计 $x\in [1,v]$ 内的贡献。

枚举 $x$。考虑此时的贡献。

一种优化思路是：由经典结论，对于每个 $a_i$，不同的 $\lceil\frac{a_i}{x}\rceil$ 最多有 $2\sqrt {a_i}$ 个。同时发现当 $x\gets x-1$ 时，最大和次大值是单调不降的。于是我们把 $x$ 从 $v$ 扫到 $1$，用两个变量维护最大和次大值，过程中朴素更新即可。

时间复杂度 $O(tn\sqrt{v})$，喜提 TLE/MLE。

换一种思路。对于每个 $x$，不同的 $\lceil\frac{a_i}{x}\rceil$ 最多有 $\lceil\frac{v}{x}\rceil$ 个，而由经典结论得 $O(\sum_{i=1}^n\frac{n}{i})=O(n\ln n)$，比上面有戏。

考虑一个数轴，我们在每个 $a_i$ 处丢下一个权值为 $h_i$ 的点。

设一段极大的 $[l,r]$ 满足 $\forall k\in[l,r]$，$\lceil\frac{k}{x}\rceil$ 相等。不难发现 $[l,r]$ 对全局的贡献即为数轴上 $[l,r]$ 内的最大与次大值乘上 $\lceil\frac{l}{x}\rceil$。

发现不带修，我们用 ST 表维护区间最大与次大值，即可得到一个 $O(t(n\ln n+v\log v))$ 的算法。

注意 ST 表维护次大值时需要排除重复贡献的情况。记录其在原数组中的位置容易解决。

另外注意到 $k$ 增加时 $\lceil\frac{k}{x}\rceil$ 单调不降，我们可以直接一个后缀最大与次大值搞定，不过同样要注意排除重复贡献的情况。我比较唐就没写。

### Code

感觉很卡常。fread + fwrite + inline 也只跑到 4196ms。

当然多半是我人傻常数大。

```cpp
#include<bits/stdc++.h>
#define Tp template<typename T>
#define Ts template<typename T,typename... _T>
using namespace std;
using ll=long long;
using ull=unsigned long long;
char ibuf[1<<22],*p1=ibuf,*p2=ibuf;
#define getchar() (p1==p2&&(p2=ibuf+fread(p1=ibuf,1,1<<22,stdin),p1==p2)?EOF:*p1++)
Tp inline void read(T& x){
    x=0;char c=getchar();
    for(;c<48||c>57;c=getchar());
    for(;c>47&&c<58;c=getchar())x=(x<<1)+(x<<3)+(c^48);
}
Ts inline void read(T& x,_T&... y){read(x),read(y...);}
char obuf[1<<22],*p3=obuf;
#define flush() (fwrite(obuf,p3-obuf,1,stdout))
#define putchar(x) ((p3-obuf<(1<<22))?(*p3++=x):(flush(),p3=obuf,*p3++=x))
Tp inline void write(T x){
	if(x>9)write(x/10);
	putchar(x%10^48);
}
Tp inline void assign(T *a,int n,T b){while(n--)*a++=b;}
Tp inline void copy(T *a,T *b,int n){while(n--)*a++=*b++;}
Tp inline void ckmin(T &a,T b){b<a&&(a=b);}
Tp inline void ckmax(T &a,T b){a<b&&(a=b);}
using node=pair<ll,int>;
const int N=2e5+5;
int t,n,lim,lg[N],h[N],a[N];ll pts[N];
node T[N][20][2];
inline void upd(node a[2],node v){
	if(a[0]<v)a[1]=a[0],a[0]=v;
	else if(a[1]<v)a[1]=v;
}
inline void build(){
	for(int i=1;i<=lim;i++)
		T[i][0][0]=T[i][0][1]=make_pair(0,0);
	for(int i=1;i<=n;i++)
		upd(T[a[i]][0],make_pair(h[i],i));
	for(int j=1;j<=19;j++)
		for(int i=1;i<=lim-(1<<j)+1;i++){
			T[i][j][0]=T[i][j-1][0];
			T[i][j][1]=T[i][j-1][1];
			upd(T[i][j],T[i+(1<<(j-1))][j-1][0]);
			upd(T[i][j],T[i+(1<<(j-1))][j-1][1]);
		}
}
node res[2];
inline void query(int l,int r){
	int len=lg[r-l+1];
	node obj[4]={T[l][len][0],T[l][len][1],T[r-(1<<len)+1][len][0],T[r-(1<<len)+1][len][1]};
	res[0]=res[1]=make_pair(0,0);
	for(auto &o:obj)
		if(o.second!=res[0].second&&o.second!=res[1].second)
			upd(res,o);
}
int main(){
	read(t);
	lg[1]=0;for(int i=2;i<=2e5;i++)lg[i]=lg[i>>1]+1;
	while(t--){
		read(n);lim=0;
		for(int i=1;i<=n;i++)read(h[i]);
		for(int i=1;i<=n;i++)read(a[i]),ckmax(lim,a[i]);
		build();
		for(int x=1;x<=lim;x++){
			node ans[2];
			for(int y=1,i=1;y<=lim;y+=x,i++){
				query(y,min(x*i,lim));
				res[0].first*=i,res[1].first*=i;
				upd(ans,res[0]),upd(ans,res[1]);
			}
			ckmax(pts[ans[0].second],ans[0].first-ans[1].first);
		}
		for(int i=1;i<=n;i++)write(pts[i]),pts[i]=0,putchar(' ');
		putchar('\n');
	}
	return flush(),0;
}
```

---

## 作者：spdarkle (赞：1)

**谨防双指针引起复杂度退化**。

> 给定 $n$ 个怪，每个怪有 $h_i$ 条命，每条命有 $a_i$ 格血。
>
>你可以选择一个正整数 $x$。在每一回合中，你将会对每一个还活着的怪造成 $x$ 点伤害。当一个怪的血条归零后，就会消耗一条命并且满血复活。
>
>定义一个怪的得分（奇怪为什么不是玩家的得分）为：
>
>- 如果这个怪没有存活到最后一轮，亦或者和其他怪一起在最后一轮死去，得分为零
>- 如果这个怪存活到了最后一轮，得分为有且仅有这个怪存活的回合数。
>求对于所有的 $x\in\mathbb{Z^+}$，每一个怪的得分的最大值。

这里值域与 $n$ 同级，以下关于时间复杂度的计算，$\max\lbrace a\rbrace$ 均用 $n$ 代替。

首先，容易发现，对于一个确定的 $x$，某怪存活的回合数为 $h_i\left\lceil\frac{a_i}{x}\right\rceil$。则对于 $x\ge \lbrace a\rbrace$，答案不变，故真正可能会对答案产生影响的 $x$ 有且只有 $O(n)$ 个。

这里就足以得到一个 $O(n^2)$ 的解决方案：我们枚举 $x$，计算出相应的回合数，然后选出**最大值和次大值**进行做差，去更新回合数最大的那个数的答案。

考虑优化这一步。

有两个常用的思路：第一个是进行数论分块，得到 $O(n\sqrt n)$ 个不同的得分，然后进行比对。这个比对可以借助各种数据结构，但无论怎么搞，复杂度下界也是  $O(n\sqrt n)$。对于 $1\le t\le 10,1\le n\le 2\times 10^5$，是无论如何也跑不过的。一组估计都够呛。

第二个是倍数法。

结合调和级数的知识我们知道，$\sum_{i=1}^n\frac{n}{i}\approx n\log n$，而又由简单放缩： $1\le\frac{a}{b}\implies \left\lceil\frac{a}{b}\right\rceil\le 2\frac{a}{b}$，可以得到 $O(\sum_{i=1}^{n}\left\lceil\frac{n}{i}\right\rceil)=O(n\log n)$。

故另一个想法是枚举 $x$，将 $a_i$ 排序后分段处理。这个做法下界是 $O(n\log n)$，显然具有更多的操作空间。

我们将原来的每个怪按照 $a$ 从小到大排序。那么我们拆出每一个区间 $[l,r]$，满足 $\forall i\in[l,r],\left\lceil\frac{a_i}{x}\right\rceil$ 相同。

这样的区间最多有 $\left\lceil\frac{\max\lbrace a\rbrace}{x}\right\rceil$ 个，求和一下就是 $O(n\log n)$。

那么设我们对于单次求解一个区间 $[l,r]$ 的最大和次大得分的复杂度为 $t$，则单组数据的总时间复杂度为 $O(tn\log n)$。注意这里是非严格的最大和次大。

而注意到这个得分中，$\left\lceil\frac{a_i}{x}\right\rceil$ 是确定的。那么问题就化为在尽可能少地时间内，处理出区间 $[l,r]$ 中 $h$ 的最大值和次大值。

这个问题太简单了，线段树之类的随便做好吧。但注意到，除了 ST 表，没有一个算法可以做到 $O(1)$ 地解决问题。

这时候可能有人会说了，ST 表不是只能维护最大值，要满足区间可加性吗？仔细想想，其实是可以办到的。

对于 ST 表的每一个元素所代表区间 $[l,r]$，我们存下其最大值和次大值的下标。当我们在查询的时候，可能出现两区间重叠的情况，此时我们特判一下最大值是否取到同一个数即可。

```cpp
struct node{
	int id1,id2;
	node operator+(const node b){
		node c;
		if(h[id1]>h[b.id1])c.id1=id1;
		else c.id1=b.id1;
		if(id1==b.id1){
			if(h[id2]>h[b.id2])c.id2=id2;
			else c.id2=b.id2;
		}
		else {
			if(c.id1==id1){
				if(h[b.id1]>h[id2])c.id2=b.id1;
				else c.id2=id2;
			}
			else {
				if(h[id1]>h[b.id2])c.id2=id1;
				else c.id2=b.id2;
			}
		}
		return c;
	}
}f[N][22];
```

然后，可能在实现上还有问题，如何快速地处理出每个 $[l,r]$ 呢？我的第一反应是双指针，然后没有发现双指针的复杂度已经爆表成 $O(n)$，程序时间复杂度直接退化为 $O(n^2)$。

第二个想法是二分查找，但这样的复杂度仍然会乘上一个 $\log n$。

然，我们可以预处理出每一个值 $i$，大于等于它的第一个 $a$ 值的下标，然后直接查询即可。

这个预处理系简单递推，这里不多说。但需要注意预处理需要处理到 $399998$。因为这是可以取到的最大的 $\left\lceil\frac{a_i}{x}\right\rceil x$。

最后你就切掉了这个题。嗯不对？为什么超时了？

注意到**会读入约 $4\times 10^6$ 个数，输出 $2\times 10^6$ 个数**，老老实实写快读吧。

[巨慢代码](https://codeforces.com/contest/1879/submission/225758992)


---

## 作者：ifffer_2137 (赞：0)

\*2800 有点抽象了。
### 题意$
$n$ 个人有血条和命数，对于 $[1,+\infty]$ 内的所有攻击力求出存活到最后的人比倒数第二个人长的时间作为他的积分，求每个人积分的最大值。
### 分析
设攻击力为 $x$，存活时间为 $h_i\lceil\frac{a_i}{x}\rceil$。

然后显然攻击力大于最大血条时没有区别，攻击力上限缩小到值域范围，然后就可以枚了。

注意到取上整只有 $\frac{V}{x}$ 种取值，同样取值的分一段，总段数即为调和级数 $O(n\log n)$ 级别的。然后这段值域里只有 $h_i$ 的最大值和次大值有可能有用，弄个 ds 查一下合并起来，把 $\text{maxpos}$ 的答案更新即可。

然后你发现双 log 会卡常。然后我不会 st 表求次大值。

虽然次大值不是严格的 RMQ，但是是半群，上个猫树就过了，时间复杂度 $O(n\log n)$。
### 代码

```cpp
//From: ifffer_2137
#include <bits/stdc++.h>
using namespace std;
#define int long long
#define ull unsigned long long
#define inf 0x7fffffff
#define eb emplace_back
#define pii pair<int,int>
#define mkpr make_pair
#define fir first
#define sec second
#define arr(x) array<int,x>
inline int read(){
	char ch=getchar();int x=0,w=1;
	while(ch<'0'||ch>'9'){if(ch=='-')w=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+ch-48,ch=getchar();return w==1?x:-x;
}
inline void getmn(auto &x,auto y){if(y<x)x=y;}
inline void getmx(auto &x,auto y){if(y>x)x=y;}
mt19937 rnd(time(NULL));
const int maxn=4e5+5;
int lg[maxn];
int _;
int n,m,N;
int h[maxn],a[maxn];
int ans[maxn];
struct Data{
	int mx,se,pos;
	Data(int a=0,int b=0,int c=0){mx=a,se=b,pos=c;}
	Data operator + (const Data &b) const{
		Data z;
		z.mx=max(mx,b.mx);
		if(z.mx==mx) z.pos=pos;
		else z.pos=b.pos;
		if(z.mx==mx) z.se=max(se,b.mx);
		else z.se=max(mx,b.se);
		return z;
	}
}x[maxn];
class Cat_Segment_Tree{
#define ls (o<<1)
#define rs (o<<1|1)
private:
	Data tr[20][maxn];
	int dep[maxn<<2],id[maxn];
public:
	void build(int o,int l,int r,int d){
		dep[o]=d;
		if(l==r) return id[l]=o,void();
		int m=(l+r)>>1;
		tr[d][m+1]=x[m+1];
		for(int i=m+2;i<=r;i++) tr[d][i]=tr[d][i-1]+x[i];
		tr[d][m]=x[m];
		for(int i=m-1;i>=l;i--) tr[d][i]=tr[d][i+1]+x[i];
		build(ls,l,m,d+1),build(rs,m+1,r,d+1);
	}
	Data query(int l,int r){
		if(l==r) return x[l];
		int x=id[l],y=id[r];
		int d=dep[x>>(lg[x^y]+1)];
		return tr[d][l]+tr[d][r];
	}
#undef ls
#undef rs
}sgt;
void mymain(){
	n=read();m=0;
	for(int i=1;i<=n;i++) h[i]=read();
	for(int i=1;i<=n;i++) a[i]=read(),getmx(m,a[i]);
	N=1;while(N<m) N<<=1;
	for(int i=1;i<=N;i++) x[i]=Data();
	for(int i=1;i<=n;i++){
		if(h[i]>=x[a[i]].mx) x[a[i]].se=x[a[i]].mx,x[a[i]].mx=h[i],x[a[i]].pos=i;
		else if(h[i]>x[a[i]].se) x[a[i]].se=h[i];
	}
	sgt.build(1,1,N,1);
	for(int i=1;i<=n;i++) ans[i]=0;
	for(int i=1;i<=m;i++){
		Data c; 
		for(int j=i,k=1;j-i+1<=m;j+=i,k++){
			Data t=sgt.query(j-i+1,min(j,m));
			t.mx*=k,t.se*=k;c=c+t;
		}
		if(c.mx==c.se) continue;
		getmx(ans[c.pos],c.mx-c.se);
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
	cout<<'\n';
}
signed main(){
	#ifdef LOCAL
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	#endif
	cin.tie(0),cout.tie(0);
	for(int i=2;i<maxn;i++) lg[i]=lg[i>>1]+1;
	_=read();
	while(_--) mymain();
	//cerr<<1.0*clock()/CLOCKS_PER_SEC<<'\n';
	return 0;
}
```

---

## 作者：daniEl_lElE (赞：0)

每个人的次数实际上是 $h_i\times\lceil\frac{a_i}{x}\rceil$。

对于每个 $x$，本质不同的 $\lceil\frac{a_i}{x}\rceil$ 只有 $\frac{V}{x}$ 种。考虑预处理出每种对应的前两大的 $h_i$ 和对应是谁，$O(\frac{V}{x})$ 计算前两大的 $h_i\times\lceil\frac{a_i}{x}\rceil$，并对最大的那个的答案与差值取 $\max$ 即可。具体如何维护前两大见代码。

注意到 $\sum_{x=1}^V\frac{V}{x}=O(V\ln V)$。总复杂度 $O(tV\log V)$，可以通过。

```cpp
#pragma GCC optimize(2,3,"Ofast","inline")
#include <bits/stdc++.h>
#define int long long
#define mid ((l+r)>>1)
using namespace std;
struct node{
	pair<int,int> maxv;
	pair<int,int> smaxv;
}ept;
void merge(node &x,node y){
	if(y.maxv.first>x.maxv.first) swap(x,y);
	if(y.maxv.second==x.maxv.second) swap(y.maxv,y.smaxv);
	if(y.maxv.first>x.smaxv.first) swap(x.smaxv,y.maxv);
}
void insert(node &x,pair<int,int> v){
	if(v.first>x.maxv.first) swap(x.maxv,x.smaxv),x.maxv=v;
	else if(v.first>x.smaxv.first) x.smaxv=v;
}
int a[200005],h[200005],ans[200005],val[200005];
node p[200005];
void solve(){
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>h[i];
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++) ans[i]=val[i]=0;
	for(int i=1;i<=200002;i++) p[i]=ept;
	for(int i=1;i<=n;i++){
		insert(p[a[i]],make_pair(h[i],i));
	}
	for(int i=200002;i>=1;i--){
		node tmp=p[i];
		merge(p[i-1],p[i]);
		assert((p[i].maxv==tmp.maxv)&&(p[i].smaxv==tmp.smaxv));
	}
	int maxv=0,lstmax=0;
	for(int i=200001;i>=1;i--){
		for(int j=0;j<=200001;j+=i){
			if(p[j+1].maxv.second!=0){
				if(p[j+1].maxv.first*(j/i+1)>val[p[j+1].maxv.second])
				if(val[p[j+1].maxv.second]==maxv){
					val[p[j+1].maxv.second]=maxv=p[j+1].maxv.first*(j/i+1);
				}
				else{
					val[p[j+1].maxv.second]=p[j+1].maxv.first*(j/i+1);
					if(val[p[j+1].maxv.second]>maxv) lstmax=maxv,maxv=val[p[j+1].maxv.second];
					else if(val[p[j+1].maxv.second]>lstmax) lstmax=val[p[j+1].maxv.second];
				}
			}
			if(p[j+1].smaxv.second!=0){
				if(p[j+1].smaxv.first*(j/i+1)>val[p[j+1].smaxv.second])
				if(val[p[j+1].smaxv.second]==maxv){
					val[p[j+1].smaxv.second]=maxv=p[j+1].smaxv.first*(j/i+1);
				}
				else{
					val[p[j+1].smaxv.second]=p[j+1].smaxv.first*(j/i+1);
					if(val[p[j+1].smaxv.second]>maxv) lstmax=maxv,maxv=val[p[j+1].smaxv.second];
					else if(val[p[j+1].smaxv.second]>lstmax) lstmax=val[p[j+1].smaxv.second];
				}
			}
		}
		for(int j=0;j<=200001;j+=i){
			if(p[j+1].maxv.second!=0){
				if(val[p[j+1].maxv.second]==maxv) ans[p[j+1].maxv.second]=max(ans[p[j+1].maxv.second],maxv-lstmax);
			}
		}
	}
	for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
	cout<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t; cin>>t; while(t--) solve();
	return 0;
}
```

---

