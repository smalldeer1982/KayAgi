# Mr. Kitayuta vs. Bamboos

## 题目描述

Mr. Kitayuta's garden is planted with $ n $ bamboos. (Bamboos are tall, fast-growing tropical plants with hollow stems.) At the moment, the height of the $ i $ -th bamboo is $ h_{i} $ meters, and it grows $ a_{i} $ meters at the end of each day.

Actually, Mr. Kitayuta hates these bamboos. He once attempted to cut them down, but failed because their stems are too hard. Mr. Kitayuta have not given up, however. He has crafted Magical Hammer with his intelligence to drive them into the ground.

He can use Magical Hammer at most $ k $ times during each day, due to his limited Magic Power. Each time he beat a bamboo with Magical Hammer, its height decreases by $ p $ meters. If the height would become negative by this change, it will become $ 0 $ meters instead (it does not disappear). In other words, if a bamboo whose height is $ h $ meters is beaten with Magical Hammer, its new height will be $ max(0,h-p) $ meters. It is possible to beat the same bamboo more than once in a day.

Mr. Kitayuta will fight the bamboos for $ m $ days, starting today. His purpose is to minimize the height of the tallest bamboo after $ m $ days (that is, $ m $ iterations of "Mr. Kitayuta beats the bamboos and then they grow"). Find the lowest possible height of the tallest bamboo after $ m $ days.

## 样例 #1

### 输入

```
3 1 2 5
10 10
10 10
15 2
```

### 输出

```
17
```

## 样例 #2

### 输入

```
2 10 10 1000000000
0 10
0 10
```

### 输出

```
10
```

## 样例 #3

### 输入

```
5 3 3 10
9 5
9 2
4 7
9 10
3 8
```

### 输出

```
14
```

# 题解

## 作者：AutumnKite (赞：39)

宣传一波[博客](https://www.cnblogs.com/rill7747/p/9903386.html)

# 题意

有$n$根竹子，竹子$i$初始高度为$h_i$，每天**晚上**会长高$a_i$。

每天**白天**，你可以选择$k$根竹子（同一根竹子在同一个白天可以多次选择），把他们的高度减少$p$，若竹子当前高度$-p$后$<0$，则竹子高度变为$0$。

最小化$m$天后最高的竹子的高度。

# 题解

首先`最小化最大的...`这种问题，显然可以用二分答案。

二分$m$天后最高的竹子的高度$H$，然后问题就变成了判定性问题：是否存在一种方案，使得$m$天后竹子高度都$\le H$。

考虑怎么解决这个判定性问题。

如果按照题意一天一天模拟，就需要考虑把竹子高度减$p$后$<0$的情况，会比较麻烦。

所以我们尝试倒着模拟这一过程。

即：竹子初始高度都设为$H$，每根竹子每天会**减少**$a_i$的高度，然后你可以选择$k$根竹子，把它们“拔高”$p$。问$m$天后竹子高度是否都$\ge h_i$。

此时你**必须保证**竹子减少$a_i$的高度后不会$<0$。

这样就好做了。我们用一个堆维护  当前状态下继续减少高度而不“拔高”，第$m$天结束后竹子高度会$<h_i$的竹子  一直减少高度  多少天后的高度会$<0$。

（不理解这句话可以尝试看代码理解）

每次取出最快$<0$的竹子，对它“拔高”即可。注意中间可能会出现无论怎么“拔高”还是会$<0$的竹子，此时直接返回错误即可。

最后判断堆是否为空即可，因为堆中维护的是$m$天后竹子高度会$<h_i$的竹子，所以堆空即代表所有竹子高度都$\ge h_i$。

时间复杂度$O((n+mk)\log n\log mx)$，其中$mx$表示$\max\limits_{1\le i\le n} h_i+a_im$（二分的上界）。

# 代码

[Code](http://codeforces.com/contest/505/submission/45262032)

```cpp
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
int read(){
	register int x = 0;
	register char f = 1, ch = getchar();
	for (; !isdigit(ch); ch = getchar()) if (ch == '-') f = 0;
	for (; isdigit(ch); ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ '0');
	return f ? x : -x;
}
int n, m, k, c[100005];
long long p, a[100005], h[100005], l = 0, r, mid, ans;
struct node{
	int day, id;  // 表示当前状态下（二分的高度+c[id]*p）day+1天后竹子id的高度会<0
	bool operator < (const node &b) const {  // 默认大根堆，所以重载<时写的是>
		return day > b.day;
	}
};
struct Heap{  // 用algorithm中的堆相关的算法封装实现。
	node h[200005];
	int sz;
	void clear(){ sz = 0; }
	bool empty(){ return !sz; }
	void push(node x){ h[++sz] = x, std :: push_heap(h + 1, h + 1 + sz); }
	node pop(){ return std :: pop_heap(h + 1, h + 1 + sz), h[sz--]; }
	node top(){ return h[1]; }
}H;
bool check(long long x){
	H.clear(), memset(c, 0, sizeof c); // c[i]表示竹子i被“拔高”了几次
	for (register int i = 1; i <= n; ++i)
		if (x - a[i] * m < h[i]) H.push((node){x / a[i], i});  // 初始堆的状态
	for (register int i = 1; !H.empty() && i <= m; ++i)  // i表示倒着的第几天
		for (register int j = 1; !H.empty() && j <= k; ++j){ // 拔高k根竹子
			node u = H.pop();
			if (u.day < i) return 0;  // 无论怎么“拔高”都不能满足条件
			++c[u.id];  // “拔高”
			if (x + c[u.id] * p - a[u.id] * m < h[u.id])  // 还是不满足条件，就插入堆中
				H.push((node){(x + c[u.id] * p) / a[u.id], u.id});
		}
	return H.empty();
}
int main(){
	n = read(), m = read(), k = read(), p = read();
	for (register int i = 1; i <= n; ++i)
		h[i] = read(), a[i] = read(), r = std :: max(r, h[i] + a[i] * m);  // 二分上界
	while (l <= r) check(mid = l + r >> 1) ? ans = mid, r = mid - 1 : l = mid + 1;
	printf("%lld", ans);
}
```

蒟蒻代码，巨佬勿喷。有错误私信哦~

---

## 作者：installb (赞：16)

直接讲我做这题的思路吧  
我的做法好像不太一样？  

看到最小化最大值，感觉可以**二分答案**，答案也确实有单调性.. 然后看 check 怎么做。  

先抛开每天砍几次的限制，二分最大的那棵的高度之后，我们可以得知每棵竹子总计要被砍多少长度，进而求出**总次数**，先把这个判掉，如果总次数之和大于 $mk$，显然不行。  

![](https://cdn.luogu.com.cn/upload/image_hosting/xj4ws0ll.png)  
图中相当于把这个竹子分成四段，最优情况下，在没有第几天的限制时，我一定会让每一次砍操作都砍掉其中一段，总次数就是所有竹子的段数之和 $sum$。

注意到**时间靠后的“砍”操作一定比时间靠前的更有价值**，比如我对于同一个竹子，本来在第 $k$ 天砍，把这次机会移到第 $k+1$ 天后，这棵竹子要么长度减小要么不变，**不会增加**。  

也就是说我**可以把“砍”操作任意后移**。所以我们可以贪心的让“砍”操作尽量在前面，然后在这样的最优方案下，保证按时间的每一个后缀和符合要求，即后 $i$ 天的总操作数（砍的次数）$\leq ik$。每个后缀符合要求的话一定可以通过把“砍”操作后移使最终方案符合要求。

事实上不同的竹子可以相互**独立**考虑。于是给出贪心方法：我们枚举每个竹子，按时间顺序，只要当前长到长度大于等于 $p$，就砍 $p$，否则看长度是不是大于等于顶上那段 $fir$，因为把 $fir$ 砍掉也能使它少掉一次需要砍的次数，不过砍了就一定砍成 0，可能会把 $fir$ 下面那段 $p$ 砍去一部分，要注意一下这个。

为什么贪心正确：假设按该贪心算法某个竹子需要砍 $x$ 次。在恰好砍 $x$ 次的情况下这样砍一定是最优的方法。砍少于 $x$ 次不可行。如果砍多于 $x$ 次，可以证明对于任意砍多于 $x$ 次的方案，一定不会有某个后缀 $i$ 的总操作数比贪心方案更小。

这样复杂度是 $O(nm\log W)$ 的，过不了，但是在枚举天数的时候，很多次枚举都是等它长到长度足够，这没有意义，把这些合并起来一起处理，就是每次让它一下直接长到能砍（当然对应的天数也要加上去）的高度。由于最多砍 $mk$ 次（否则之前判掉了），时间复杂度降为 $O((n+mk)\log W)$。

```cpp
using namespace std;
typedef long long LL;
const LL N = 200005;

LL n,m,k,p;
LL to[N],h[N],dv[N],fir[N],a[N];
LL val[5005];

LL chk(LL x){
	LL sum = 0,td;
	for(LL i = 1;i <= n;i ++){
		to[i] = h[i] + a[i] * m - x;
		fir[i] = -1; dv[i] = 0;
		if(to[i] <= 0) continue;
		dv[i] = (to[i] - 1) / p;
		fir[i] = to[i] - dv[i] * p;
		sum += (dv[i] + 1);
	} if(sum > m * k) return 0; // 判总次数
	
	for(LL i = 1;i <= m;i ++) val[i] = 0;
	for(LL i = 1;i <= n;i ++){
		to[i] = h[i];
		for(LL j = 1;j <= m;){
			while(to[i] >= p && dv[i]){
				to[i] -= p; dv[i] --;
				val[j] ++;
			}
			if(to[i] >= fir[i] && fir[i] != -1){
				to[i] -= fir[i]; fir[i] = -1;
				val[j] ++;
			}
			if(fir[i] == -1 && !dv[i]) break;
			
			td = ((fir[i] == -1 ? p : fir[i]) - to[i] - 1) / a[i];
			to[i] += a[i] * (td + 1); j += (td + 1);
		}
	} sum = 0;
	for(LL i = m;i >= 1;i --){
		sum += val[i];
		if(sum > k * (m - i + 1)) return 0;
	} return 1;
}

int main(){
	ios::sync_with_stdio(false);
	LL mxa = 0,l,r,mid,ans;
	cin >> n >> m >> k >> p;
	for(LL i = 1;i <= n;i ++){
		cin >> h[i] >> a[i];
		mxa = max(mxa,a[i]);
        // 这是二分下界，最后一轮全部砍成 0 后，还是会再长一段，不取这个会错，见样例 2
	}
	
	l = mxa,r = 0x3f3f3f3f3f3f3f3f;
	while(l <= r){
		mid = (l + r) >> 1;
		if(chk(mid)){
			ans = mid;
			r = mid - 1;
		}
		else l = mid + 1;
	}
	cout << ans << '\n';
	return 0;
}
```

挺有趣的一道题。

---

## 作者：xht (赞：11)

> [CF505E Mr. Kitayuta vs. Bamboos](https://codeforc.es/contest/505/problem/E)

## 题意

- 给定 $n$ 个数 $h_{1 \dots n}$。
- 你需要进行 $m$ 轮操作，每轮操作为 $k$ 次修改，每次修改可以选择一个数 $h_i$ 修改为 $\max(h_i - p, 0)$。
- 每轮操作后每个 $h_i$ 将会被修改为 $h_i + a_i$。
- 你需要最小化最终 $h_{1 \dots n}$ 中的最大值。
- $n \le 10^5$，$m \le 5 \times 10^3$，$k \le 10$。

## 题解

首先二分答案。

判定的时候，发现正着判很麻烦，考虑倒序。

那么就相当于，每轮操作为：

- 将每个 $h_i$ 修改为 $h_i - a_i$，这里需要保证 $h_i - a_i \ge 0$。
- $k$ 次修改，每次修改可以选择一个数 $h_i$ 修改为 $h_i + p$。
- 要求最终的 $h_{1 \dots n}$ 均不小于给定的 $n$ 个数。

那么可以考虑贪心：

- 每次选择最容易导致 $h_i - a_i < 0$ 的位置加上 $p$，如果选完了还是会导致则判定不合法。
- 如果不存在可能导致 $h_i - a_i < 0$ 的位置，则直接判定剩下的次数是否足够使最终的 $h_{1 \dots n}$ 均不小于给定的 $n$ 个数。

时间复杂度 $\mathcal O((n + mk) \log n \log w)$。

## 代码

```cpp
const int N = 1e5 + 7;
int n, m, k, c[N];
ll h[N], a[N], p, l, r;

inline bool pd(ll o) {
	pq< pi > q;
	for (int i = 1; i <= n; i++) {
		if (h[i] + m * a[i] <= o) continue;
		q.push(mp(-(o / a[i]), i)), c[i] = 0;
	}
	int cnt = 0;
	for (int i = 1; q.size() && i <= m; i++)
		for (int j = 1; q.size() && j <= k; j++) {
			if (-q.top().fi < i) return 0;
			int x = q.top().se;
			q.pop();
			ll w = (o + (++c[x]) * p) / a[x];
			if (w < m) q.push(mp(-w, x));
			++cnt;
		}
	for (int i = 1; i <= n; i++) {
		ll w = o + c[i] * p - m * a[i];
		if (h[i] <= w) continue;
		w = (h[i] - w - 1) / p + 1;
		if (cnt + w > m * k) return 0;
		cnt += w;
	}
	return 1;
}

int main() {
	rd(n), rd(m), rd(k), rd(p);
	for (int i = 1; i <= n; i++)
		rd(h[i]), rd(a[i]),
		l = max(l, a[i]), r = max(r, h[i] + m * a[i]);
	while (l < r) {
		ll o = (l + r) >> 1;
		if (pd(o)) r = o;
		else l = o + 1;
	}
	print(l);
	return 0;
}
```

---

## 作者：ShuYuMo (赞：9)

[My Blog](https://shuyumo2003.github.io/2020/%E3%80%8C%E9%A2%98%E5%8D%95%E3%80%8DIOI2020%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F%E4%BD%9C%E4%B8%9A-Part-1/#CF505E-Mr-Kitayuta-vs-Bamboos)
# CF505E Mr. Kitayuta vs. Bamboos
- 给定 $n$ 个数（竹子的高度） $h_{1 \dots n}$。
- 你需要进行 $m$ 轮操作，每轮操作为 $k$ 次修改，每次修改可以选择一个数 $h_i$ 修改为 $\max(h_i - p, 0)$（砸到地下）。
- 每轮操作后每个 $h_i$ 将会被修改为 $h_i + a_i$（每天竹子会生长）。
- 你需要最小化最终 $h_{1 \dots n}$ 中的最大值。
- $n \le 10^5$，$m \le 5 \times 10^3$，$k \le 10$
<!-- more -->
要求最小化最大值，考虑二分一个最大的高度，将问题转化成可行性问题，即，给出一个高度，问能否使这些竹子最终不超过这个高度。

考虑限制这个问题不平凡的因素：因为每次降低竹子高度的时候不能保证竹子一定降低 p ，也就是说，“砸竹子”这一动作存在浪费。我们考虑尽可能的让“砸竹子”这一动作更少的浪费，即：尽可能在后面的时间点砸竹子，但是无法保证到底是在哪一次砸竹子，有可能已经结束了，没有形式化的计算流程。

可以考虑反向思考，即：假设已经长到 二分的高度。每次生长操作相当于每次会下落 $a_i$，而每次砸的操作相当于提升了 $p$ 的高度。

开始时，对每一个竹子计算出其需要多少次会下落到负高度，用堆维护，每次取出最快的可能下落到负高度的 k 个竹子，进行 “拔高” 操作。然后判断最后的高度是否大于等于$h_i$。

其实二分的本质是为了确定“尽可能的靠后砸竹子”的标准。反向思考是为了便于贪心处理策略。
## code
{% note info CF505E Mr. Kitayuta vs. Bamboos %}
```cpp
int n, m, k, p;
int H[_], A[_];
#define mp make_pair
#define fi first
#define se second
int height[_];
bool check(int MaxH){
	fill(height + 1, height + 1 + n, MaxH);
	priority_queue<pair<int, int>, vector<pair<int, int> > , greater<pair<int, int> > > Q;
	while(!Q.empty()) Q.pop();
	for(int i = 1; i <= n; i++) if(MaxH - m * A[i] < H[i]) Q.push(mp( MaxH / A[i], i ));

	for(int i = 1; i <= m; i++) {
		for(int j = 1; j <= k; j++){
			if(Q.empty()) return true;
			pair<int, int> now = Q.top(); Q.pop(); 
			if(now.fi < i) return false;
			height[now.se] += p;
			now.fi = height[now.se] / A[now.se];
			if(height[now.se] - m * A[now.se] < H[now.se]) Q.push(now);
		}
	}
	return Q.empty();
}
signed main(){
	n = read(), m = read(), k = read(), p = read(); // 竹子数 天数 修改次数 最大降低高度 
	for(int i = 1; i <= n; i++) H[i] = read(), A[i] = read();

	int L = 0, ans = 0, R = 1LL << 60; for(int i = 1; i <= n; i++) L = min(L, A[i]);
	while(L < R){
		int mid = (L + R) >> 1;
		if(check(mid)) ans = mid, R = mid;
		else L = mid + 1;
	}
	printf("%lld\n", ans);
	return 0;
}
```
{% endnote %}



---

## 作者：YouXam (赞：7)

设第 $i$ 个竹子在第 $j$ 被砍了 $c_{i,j}$ 次， 则最后的高度为

$$H_i = \max\{h_i+m \times a_i - p \times \sum^m_{k=1}c_{i,k}, \max^m_{k=1}\{(m - j + 1) \times a_i - p \times \sum^m_{k=j+1} c_{i,k}\}\}$$

二分答案$mid$为最后竹子最大高度

$\because H_i \le mid$

$\therefore h_i+m \times a_i - p \times \sum^m_{k=1}c_{i,k} \le mid$ 且 $max^m_{k=1}\{(m - j + 1) \times a_i - p \times \sum^m_{k=j+1} c_{i,k}\} \le mid$

所以可以解出 $s_{i,j} = \sum_{k>j} c_{i,k}$ 的下界

最后往前判断， 贪心算 $s_{i,j}$ ，如果 $k$ 次没用完就存起来， 下次继续用。 时间复杂度 $ O(nm\log(\max^{n}_{i=1}\{h_i + m \times a_i\})) $

因为有效砍伐次数只有 $mk$ 次， 可以找到 $s_{i, j}$ 下次变化的位置， 给每个位置维护一个队列。 把 $i$ 塞到 $s_{i,j} $ 下次变化的位置所对应的队列里。

时间复杂度 $ O((n+mk)\log(\max^{n}_{i=1}\{h_i + m \times a_i\})) $

```cpp
#include <bits/stdc++.h>
#define gc() (p1 == p2 ? (p2 = buf + fread(p1 = buf, 1, 1 << 20, stdin), p1 == p2 ? EOF : *p1++) : *p1++)
#define rd() ({ register int x = 0; register char c = gc(); while (!isdigit(c)) c = gc(); while (isdigit(c)) x = x * 10 + (c & 15), c = gc(); x; })
char buf[1 << 20], *p1, *p2;
int n, m, k;
long long a[100005], h[100005], p;
std::queue<std::pair<int, int> > q[100005];
long long max(long long a, long long b) { return a > b ? a : b; }
bool check(long long x) {
	for (int i = 1; i <= m; i++) while (!q[i].empty()) q[i].pop();
	for (int i = 1; i <= n; i++) 
		if (x / a[i] + 1 <= m) 
			q[x / a[i] + 1].push(std::make_pair(i, 0));
	for (int i = 1, c = 0; i <= m; i++, c += k)
		while (q[i].size()) {
			if (c) c--;
			else return 0;
			std::pair<int, int> f = q[i].front();
			q[i].pop(), f.second++;
			long long s = (f.second * p + x) / a[f.first] + 1;
			if (s <= m) q[s].push(f);
		}
	long long s = 0;
	for (int i = 1; i <= n; i++) s += (max(a[i] * m + h[i] - x, 0ll) + p - 1) / p;
	return s <= m * k;
}
int main() {
	n = rd(), m = rd(), k = rd(), p = rd();
	for (int i = 1; i <= n; i++) h[i] = rd(), a[i] = rd();
	long long l = 0, r = 0, mid;
	for (int i = 1; i <= n; i++)
		r = max(r, h[i] + m * a[i]);
	while (l < r) {
		if (check(mid = l + r >> 1)) r = mid;
		else l = mid + 1;
	}
	printf("%lld\n", r);
}

```

---

## 作者：StudyingFather (赞：6)

看到“最大值最小”，首先想到二分答案。

但存在一个问题：高度是非负的，处理负高度这个问题会稍微有些棘手（当然也不是不能实现）。

如果我们让时间倒流呢？我们会看到这样一种景象：刚开始所有竹子的高度都为 $x$，竹子每天高度会下降 $a_i$，而我们的操作呢，则是将选定的竹子拔高 $p$。

我们的目标是让任何时刻竹子的高度都非负，而倒推到最开始的时候，第 $i$ 个竹子的高度不能低于 $h_i$。

这样我们就避开了可能的负高度的问题。

针对上面的场景，我们可以贪心解决：如果一个竹子有高度变为负的风险，我们就把它拔高。假如不存在这样的竹子，我们则选择最终高度可能会低于 $h_i$ 的竹子。

```cpp
#include <iostream>
#include <queue>
using namespace std;
struct node
{
 long long d;
 int id;
 bool operator<(const node&a)const
 {
  return d>a.d;
 }
};
long long a[100005],h[100005],t[100005],n,m,k,p;
bool check(long long x)
{
 priority_queue<node> q;
 for(int i=1;i<=n;i++)
 {
  t[i]=x;
  if(x-a[i]*m<h[i])q.push({x/a[i],i});
 }
 for(int i=1;i<=m;i++)
  for(int j=1;j<=k;j++)
  {
   if(q.empty())return true;
   int d=q.top().d,id=q.top().id;
   q.pop();
   if(d<i)return false;
   t[id]+=p;
   if(t[id]-a[id]*m<h[id])q.push({t[id]/a[id],id});
  }
 return q.empty();
}
int main()
{
 cin>>n>>m>>k>>p;
 for(int i=1;i<=n;i++)
  cin>>h[i]>>a[i];
 long long l=0,r=1ll<<60;
 while(l<r)
 {
  long long mid=(l+r)>>1;
  if(check(mid))r=mid;
  else l=mid+1;
 }
 cout<<l<<endl;
 return 0;
}
```


---

## 作者：Su_Zipei (赞：5)

最先想到的一般都是贪心思想，但是的确不是很好贪，主要原因是要保证高度不小于$0$ ，这一点使得当前做出的选择可能不是最优决策，我的做法和大部分题解的写法差不多，都是时光倒流然后二分答案+贪心判断，但是在二分的时候写法略有不同，用了$m$ 个队列来代替堆，这样也可以做到一个$log$ ，虽然可能常数略微大一些。

其余的思路和其他题解相似，主要说明一下怎么用$m$ 个队列实现，首先一定知道如果一棵竹子即使被砍很多次也不会小于初始高度那就不用管他，其余的考虑被被削成$0$ 的时间，如果大于$m$ ，那么它在任意时刻的高度一定都是正数，只需要让它的高度最后大于初始高度即可，将它放到一个$vector$ 里边，最后再处理，因为什么时候拔高它都无所谓，优先拔高其余的容易被削成$0$ 的才是应该先做的，如果不大于$m$ ，那就直接将它扔到对应时间的队列礼拜，竹子与竹子之间如果高度成为$0$ 的时间一样那就没有区别。

然后需要做的就是模拟每一天的过程，将必须拔高的竹子拔高，如果不能就不合法，如果这一天的次数用不完就累加到下一天，下次用的时候就当作是在这一天拔的，也无所谓，记得每次拔完之后更新一下下次成为$0$ 的时间，具体处理和刚开始的时候一样。

最后还要判断一下$vector$ 里边的元素，因为它们虽然不会变成$0$，但是高度也没有达到初始高度，一直将它们拔到初始高度即可，还是如果不能拔高就不合法。

```cpp
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
#define rg register
const int N=1e5+10;
char buf[1<<20],*p1,*p2;
inline char gc(){return p1==p2?p2=buf+fread(p1=buf,1,1<<20,stdin),p1==p2?EOF:*p1++:*p1++;}
inline int read(){
	rg int x=0,f=1;rg char ch=gc();
	while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=gc();}
	while(ch<='9'&&ch>='0'){x=x*10+ch-'0';ch=gc();}
	return x*f;
}
ll a[N],h[N];
queue<int> q[N];
vector<int> vec;
int cnt[N],n,m,k,p;
bool check(ll x){
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=m;i++)while(!q[i].empty())q[i].pop();
	vec.clear();
	for(rg int i=1;i<=n;i++)
	    if(x-a[i]*m<h[i]){
	    	if(x/a[i]==0)return 0;
            if(x/a[i]>m)vec.push_back(i);
            else q[x/a[i]].push(i);
        }
	rg int now=0;
	for(rg int i=1;i<=m;i++){
		now+=k;
		while(!q[i].empty()){
			if(!now)return 0;
			rg int u=q[i].front();q[i].pop();
			++cnt[u];--now;
			if(x+(ll)cnt[u]*p-a[u]*m<h[u]){
			    if((x+(ll)cnt[u]*p)/a[u]>m)vec.push_back(u);
                else q[(x+(ll)cnt[u]*p)/a[u]].push(u);
            }
		}
	}
	for(rg int i=0;i<vec.size();i++){
	    rg int u=vec[i];
	    while(x+(ll)cnt[u]*p-a[u]*m<h[u]){
            if(!now)return 0;
	        cnt[u]++;
	        now--;
	    }
	}
	return 1;
}
int main(){
	n=read(),m=read(),k=read(),p=read();
	ll l=0,r=0;
	for(rg int i=1;i<=n;i++){
		h[i]=read();a[i]=read();
		r=max(r,h[i]+a[i]*m);
	}
	ll res=0;
	while(l<=r){
		ll mid=l+r>>1;
		if(check(mid))res=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%lld\n",res);
	return 0;
}

```


---

## 作者：VenusM1nT (赞：3)

由“最大值的最小值”想到二分，考虑二分答案 $\text{mid}$，此时如果正向判断，就会陷入不知道每次操作选谁砍的境地，如果考虑 dp 之类的就会花很多时间，因此考虑逆向操作，先让每根竹子的初值都为 $\text{mid}$，然后逆向增长，判断能否最终使每根竹子的长度都 $\ge h_i$，此时就可以贪心了。开一个优先队列（堆）维护所有会逆向生长到 $<0$ 的竹子，每次对其中最快“长没” 的若干竹子进行逆向生长，最终判断能否满足要求。
```cpp
#include<bits/stdc++.h>
#define N 100000
#define reg register
#define inl inline
#define int long long
using namespace std;
struct Node
{
	int val,id;
	friend bool operator < (const Node &x,const Node &y)
	{
		return x.val>y.val;
	}
};
int n,m,Q,k,a[N+5],h[N+5],f[N+5];
inl bool Check(reg int mid)
{
	priority_queue <Node> q;
	for(reg int i=1;i<=n;i++)
	{
		f[i]=mid;
		if(mid-a[i]*m<h[i]) q.push((Node){mid/a[i],i});
	}
	for(reg int i=1;i<=m && !q.empty();i++)
	{
		for(reg int j=1;j<=Q && !q.empty();j++)
		{
			reg Node now=q.top();
			q.pop();
			reg int x=now.id;
			if(f[x]-a[x]*i<0) return 0;
			f[x]+=k;
			if(f[x]-a[x]*m<h[x]) q.push((Node){f[x]/a[x],x});
		}
	}
	for(reg int i=1;i<=n;i++) if(f[i]-a[i]*m<h[i]) return 0;
	return 1;
}
signed main()
{
	scanf("%lld %lld %lld %lld",&n,&m,&Q,&k);
	reg int maxn=0;
	for(reg int i=1;i<=n;i++)
	{
		scanf("%lld %lld",&h[i],&a[i]);
		maxn=max(maxn,a[i]*m+h[i]);
	}
	reg int l=0,r=maxn;
	reg int ans=1e18;
	while(l<=r)
	{
		reg int mid=(l+r)>>1;
		if(Check(mid))
		{
			ans=min(ans,mid);
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：zzw4257 (赞：2)

**修改了几个不影响理解的笔误**

>给定一些位置初始值$h_i$,需要进行$m$轮操作
>每轮操作定义为
>
>- 执行$K$次，每次选一个$i,h_i\leftarrow \max{h_i-p,0}$
>- $\forall i,h_i\leftarrow h_i+a_i$
>
>最小化最终序列最大值 

肯定想到二分，二分这个最大值$x$相当于把问题转为一些初始值为$x$的数执行操作能否均$\leqslant h_i$

然后发现第一个操作的结果很耐人寻味每次都会与$0$取$\max$,只能单次单次贪心做

对本题而言直接给出做法，考虑把两个操作反转，转化判定性问题为

>给定一些位置初始值均为$x$,需要进行$m$轮操作
>每轮操作定义为
>
>- $\forall i,h_i\leftarrow h_i-a_i$
>- 执行$K$次，每次选一个$i,h_i\leftarrow h_i+p$
>
>每个时刻均要保证$a_i$不$<0$
>
>询问是否可以使得每个位置都$\geqslant h_i$

~~翻题解翻到了一个有趣的方法~~

首先肯定可以像题解那样直接贪最容易被减没的数加，其余尽量加隔得远的

不如独立考虑每个位置尽量合法的去安排位置

合法包含两个意思

- 结果在$h_i$以上
- 每一刻不掉下$0$

首先满足条件$1$我们可以算出$tim_i=\lceil \frac{h_i+a_im-mid}{p}\rceil$表示$i$位置必须被加$p$的次数

在满足条件一情况下，考量条件二，更一般的说，其实这两个问题是等价的

- 在$m$个阶段每次$k$次内判定能否让所有位置跳出生死线(即不会$<0$)
- 让每个位置在**不得不**$+p$的阶段才加，问每个阶段的操作次数够不够

$dead_{i,j}=\lfloor\frac{mid+jp}{a_i}\rfloor$表示$i$位置加过$j-1$次$p$还没死，$dead_{i,j}$是最小的阶段使得如果不在$dead_{i,j}$放一次$+p$就会在$dead_{i,j}+1$阶段死掉

然后我们这样处理

- 首先整体考虑$\sum tim_i$放不放的下
- 可以的话我们就把每个位置放到$dead_{i,j}$然后逐次考虑每个操作前放不放的下那么多个提升

```cpp
inline char Check(ll mid){
	int i,j;ll res,sum=0,tim;memset(v,0,sizeof v);
	for(i=1;i<=n;++i){
		tim=(mid-1ll*a[i]*m>=h[i])?0:(h[i]+1ll*a[i]*m-mid+p-1)/p;//要加多少次 
		if((sum+=tim)>m*k)return 0;
		for(j=0;j<tim;++j)if((mid+1ll*j*p)/a[i]<m)++v[(mid+1ll*j*p)/a[i]];
	}res=0;
	for(i=0;i<m;++i){res+=v[i];if(res>i*k)return 0;}
	return 1;
}
```

---

## 作者：RQ。。。 (赞：0)

# T1 CF505E Mr. Kitayuta vs. Bamboos

- 给定 n 个数 $h_{ 1 \dots n}$。
- 你需要进行 m 轮操作，每轮操作为 k 次修改，每次修改可以选择一个数 $h_i$ 修改为 $\max(h_i - p, 0)$。
- 每轮操作后每个 $h_i$ 将会被修改为 $h_i + a_i$。
- 你需要最小化最终 $h_{1 \dots n}$ 中的最大值。
- $n \le 10^5$，$m \le 5 \times 10^3$ $ k≤10$。

**solution**

首先二分答案，之后反着考虑，考虑这些竹子是每天减少$a_i$，你可以给k个拔高$p$ ， 最后，要让最小的尽可能的大，也就是所有的竹子的高度都要$ >= h_i$ ， 维护一个堆，每次把最可能变成0的加进去即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5+10;
#define int long long
inline int read()
{
	register int x = 0 , f = 0; register char c = getchar();
	while(c < '0' || c > '9') f |= c == '-' , c = getchar();
	while(c >= '0' && c <= '9') x = (x << 3) + (x << 1) + (c ^ 48) , c = getchar();
	return f ? -x : x;
}
int n , m , k , p;
int h[N] , a[N] , t[N];
struct node
{
	int d , id;
	bool operator < (const node &A) const { return d > A.d; }
};
priority_queue<node> q;

bool check(int mid)
{
	while(q.size()) q.pop();
	for(int i = 1 ; i <= n ; ++i)
	{
		t[i] = mid;
		if(t[i] - a[i] * m < h[i]) q.push((node){t[i] / a[i] , i});
	}
	for(int i = 1 ; i <= m ; ++i)
		for(int j = 1 ; j <= k ; ++j)
		{
			if(q.empty()) return true;
			int d = q.top().d , id = q.top().id; q.pop();
			if(d < i) return false;
			t[id] += p; if(t[id] - a[id] * m < h[id]) q.push((node){t[id] / a[id] , id});
		}
	return q.empty();
}

signed main()
{
	n = read(); m = read(); k = read(); p = read();
	for(int i = 1 ; i <= n ; ++i) h[i] = read() , a[i] = read();
	int l = 0 , r = 0 , mid , ans = 0;
	for(int i = 1 ; i <= n ; ++i) r = max(r , h[i] + a[i] * m);
	while(l <= r)
	{
		mid = (l + r) >> 1;
		if(check(mid)) ans = mid , r = mid - 1; else l = mid + 1;
	}	
	cout << ans << '\n'; return 0;
}
```



---

## 作者：MikukuOvO (赞：0)

首先不难想到二分出最大值是多少。

当然，如果没有$0$这个下界，那么这道题就是一道入门题。

现在加上$0$这个下界，发现如果正向维护并不方便，于是考虑反着维护。

首先我们将所有初始高度都设为二分出的$val$，这样就变成了有$m$轮操作，每一次可以选择$k$个物品，将他们的高度$+p$，每轮后所有物品的高度$-a_i$，这样我们只要保证没有一个物品的高度小于$0$即可。

这样我们对于每一个物品用一个堆维护一下还有多少天它的高度会$<0$，当然如果到最后高度仍$\ge h_i$那么就不用加入堆中了，这样每次贪心的修改快要$<0$的即可，如果修改仍然会$<0$就不合法。

对于一个$val$，如果不存在一个物品不合法且最后的堆为空则满足条件。

---

## 作者：lgswdn_SA (赞：0)

## [CF505E Mr. Kitayuta vs. Bamboos](https://www.luogu.com.cn/problem/CF505E)

最大值最小，果断二分。

二分好了现在主要的问题是这个 $\max(0,a_i-p)$。因为 $\max(0,i-p)$ 我们无法直接判断应该给哪个数减去 $p$。

于是这里有个很巧妙的做法，**逆向模拟**。假设最后每个竹子的高度是 $H$，那么我们倒过来做，看最后是不是能够大于等于 $h_i$ 即可。至于为什么是对的，假如算出来的初始高度是 $h'_i\ge h_i$，那么我们按照同样的方法去加，最终算出来的结果一定会 $\le H$。

所以现在一轮的操作转化为：  
1. 每个 $h_i$ 减去 $a_i$ 且必须保证 $\ge 0$。  
2. 选择 $k$ 个点让他们增加 $p$。  

增加就要加那些最危险的数。所谓最危险的数，有两种：$h_i-a_i$ 会 $<0$ 的数和最后会 $<h_i$ 的数。由于现在什么时候加都一样，我们优先处理最紧急的数（$h_i-a_i<0$），然后再处理那些什么时候都可以处理的点。

对于紧急和危险的判断，我们可以采用堆的方式。堆中存储每个数还要几天才会 $<0$。显然，这个值越小的数一定是越紧急的。如果最后全部堆空了且中途没有遇到不满足的情况，那么这个 $H$ 就是合法的。

时间复杂度 $O(n\log h+mk\log n\log h)$。

```cpp
#define int long long
using namespace std;
const int N=1e5+9;

int n,m,k,p,h[N],a[N];

struct bb {
	int id,h,a,day;
	bool operator < (const bb &b) const {return day>b.day;}
};
bool check(int H) {
	priority_queue<bb>q;
	for(int i=1;i<=n;i++) if(H-m*a[i]<h[i]) q.push((bb){i,H,a[i],H/a[i]});
	for(int i=1;i<=m&&!q.empty();i++) {
		for(int j=1;j<=k&&!q.empty();j++) {
			bb u=q.top(); q.pop();
			if(u.day<i) return 0;	//在i时刻已经<0了 
			u.h+=p, u.day=u.h/u.a;	//加上p，更新剩余天数 
			if(u.h-u.a*m<h[u.id]) q.push(u);	//如果加上后还是危险的那么就再push回去 
		}
	}
	return q.empty(); 
}

signed main() {
	scanf("%lld%lld%lld%lld",&n,&m,&k,&p);
	for(int i=1;i<=n;i++) scanf("%lld%lld",&h[i],&a[i]);
	int l=1, r=1, ans=0;
	for(int i=1;i<=n;i++) r=max(r,h[i]+a[i]*m);
	while(l<=r) {
		int mid=(l+r)/2;
		if(check(mid)) ans=mid, r=mid-1;
		else l=mid+1;
	}
	printf("%lld",ans);
	return 0;
}
```

---

## 作者：WaviFreka (赞：0)

   我的思路也是借鉴了其他大佬的思路，最早我用的是贪心尝试去做这道题，最后不出所料的TLE。
   
   
   这道题的题目还是很容易理解的，就是要在经过一个锤子的处理后让m天后最高的竹子最矮。
   
   我们先假设第m天后，自然生长下最高的竹子高度是max_height。那么我们经过处理后的答案一定会在区间[0,max]内。不可能超过我们最高的竹子。
   
   此时我们假定一个最后的答案ans，然后二分查找的方法去找到正确的答案。
   
   如果这个答案是正确的那么第m天的时候所有的竹子高度都会小于等于ans。那么前一天的最高的竹子高度就是ans-a[i]+p*times，times是我们对这个竹子处理的次数。然后再前一天一次类推。我们反向处理我们的竹子。
   
   如果我们无论怎么处理最后这个竹子的高度还是会大于我们的预想答案ans，则说明我们的答案小了，继续在区间(ans,max]寻找。反之则在[0,ans]寻找。




```cpp
#include <bits/stdc++.h>
#define ull unsigned long long
#define ll long long
#define MAXL 100005
#define MAX(X,Y) ((X)>(Y)?(X):(Y))
#define ll long long

using namespace std;

int n,m,k,p_times[MAXL];
ll p,a[MAXL],h[MAXL];
ll indexs=0,max_height,mid,ans;

struct bamboo{
    int day;
    int id;
    
    bool operator < (const bamboo &b) const {
        return day>b.day;
    }
};

struct Heap{
    bamboo h[MAXL];
    int size;
    
    
    void clear(){
		size=0;
	}
    bool empty(){
    	if(size==0) return true;
    	else return false;
	}
    void push(bamboo x){
    	size++;
		h[size]=x;
		push_heap(h+1,h+1+size); //将元素压入队列的最后 
	}
    bamboo pop(){
		pop_heap(h+1,h+1+size);
		return h[size--]; //弹出队列中最后放入的元素 
	}
    bamboo top(){
		return h[1];
	}
}H;


bool check(long long x){
    H.clear();
	memset(p_times,0,sizeof(p_times)); //清空
	
    for(int i=1;i<=n;i++){
    	if(x-a[i]*m<h[i]) //如果检查的高度前一天的高度小于本来的高度 
			H.push((bamboo){
				x/a[i],
				i
				});  //将长到x高要多少天，和序号放入H中 
    }
        
    
    for(int i=1;!H.empty() && i<=m;i++)  // i表示倒着的第几天
        for(int j=1;!H.empty() && j<=k;j++){ //每天只能处理k根竹子 
            bamboo now_operation=H.pop();
            
            if(now_operation.day<i)
				return 0;  //如果竹子长到这么高的时间小于，我们能够处理的天数，则无法满足条件 
			
            p_times[now_operation.id]++;  //进行一次处理 
            if(x+p_times[now_operation.id]*p-a[now_operation.id]*m<h[now_operation.id])  //如果一次处理不足以把竹子压在区间之内就再处理一次 
                H.push((bamboo){(
					x+p_times[now_operation.id]*p)/a[now_operation.id],
					now_operation.id
					}); //一次处理之后还需要的天数 
        }

    if(H.empty()) return true; //如果把所有竹子都处理完成，则满足条件 
    else return false;
}

int main(){
	cin>>n>>m>>k>>p;
    for(int i=1;i<=n;i++){
    	scanf("%d %d",&h[i],&a[i]);
		max_height=MAX(max_height,h[i]+a[i]*m); //保存的当前在m天后，自然状态下最高的那个 
	}
    while(indexs<=max_height){
    	mid=(indexs+max_height)/2; //检查中间的高度 
    	if(check(mid)){
    		ans=mid;
    		max_height=mid-1;  //如果符合条件向前检查 
    	}
    	else{
    		indexs=mid+1; //如果不符合条件向后检查 
    	}
    }
    printf("%lld\n", ans);
}
```


---

