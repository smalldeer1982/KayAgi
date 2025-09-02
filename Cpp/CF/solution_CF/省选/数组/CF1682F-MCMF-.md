# MCMF?

## 题目描述

给定两个整数数组 $a$ 和 $b$（$b_i \neq 0$ 且 $|b_i| \leq 10^9$）。数组 $a$ 已按非递减顺序排序。

定义子数组 $a[l:r]$ 的代价如下：

- 如果 $ \sum\limits_{j = l}^{r} b_j \neq 0 $，则该子数组的代价未定义。
- 否则：
  
  - 构建一个二分图流网络，包含 $r-l+1$ 个顶点，编号为 $l$ 到 $r$，所有 $b_i<0$ 的顶点在左侧，$b_i>0$ 的顶点在右侧。对于每一对 $i, j$ 满足 $l \leq i, j \leq r$，$b_i<0$ 且 $b_j>0$，从 $i$ 向 $j$ 连一条容量为无穷大、单位流量费用为 $|a_i-a_j|$ 的边。
  - 再添加两个顶点：源点 $S$ 和汇点 $T$。
  - 对于每个 $l \leq i \leq r$ 且 $b_i<0$，从 $S$ 向 $i$ 连一条容量为 $|b_i|$、费用为 $0$ 的边。
  - 对于每个 $l \leq i \leq r$ 且 $b_i>0$，从 $i$ 向 $T$ 连一条容量为 $|b_i|$、费用为 $0$ 的边。
  - 子数组的代价定义为从 $S$ 到 $T$ 的最大流的最小费用。

你将会得到 $q$ 个询问，每个询问给出两个整数 $l$ 和 $r$。你需要计算每个询问对应的子数组 $a[l:r]$ 的代价，结果对 $10^9+7$ 取模。

如果你不了解最小费用最大流的含义，可以阅读[这里](https://en.wikipedia.org/wiki/Minimum-cost_flow_problem)。

## 说明/提示

在第一个询问中，最大可能流量为 $1$，即从源点到 $2$，再从 $2$ 到 $3$，最后从 $3$ 到汇点，流量均为 $1$。流量的总代价为 $0 \cdot 1 + |2 - 4| \cdot 1 + 0 \cdot 1 = 2$。

在第二个询问中，最大可能流量仍为 $1$，即从源点到 $7$，$7$ 到 $6$，$6$ 到汇点，总代价为 $0 \cdot |10 - 10| \cdot 1 + 0 \cdot 1 = 0$。

在第三个询问中，流网络如左图所示，边上标注了容量，括号内为费用。右图展示了最优流量分配。

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682F/b6040909c6a89f65b5b7d87c18e4b15cd451816a.png) 最大流量为 $3$，总代价为 $0 \cdot 3 + 1 \cdot 1 + 4 \cdot 2 + 0 \cdot 1 + 0 \cdot 2 = 9$。

在第四个询问中，流网络如下所示——

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682F/785b5422d5947aa6cf07e9905d5c183db07a5c80.png)

最小费用最大流的最优分配如下——

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1682F/58ed2fd428ae0881741713ff33b82d81dd69edde.png)

上述网络的最大流量为 $4$，最小费用为 $15$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
8 4
1 2 4 5 9 10 10 13
6 -1 1 -3 2 1 -1 1
2 3
6 7
3 5
2 6```

### 输出

```
2
0
9
15```

# 题解

## 作者：feecle6418 (赞：18)

~~完全不知道这题的题解在说什么？？？？把非常简单的东西搞得看上去很复杂。~~

注意到 $a$ 是递增的。可以把图想象成这样：中间的边不是直接连 $O(n^2)$ 条，而是在相邻之间连双向边，费用为 $(a_i-a_{i-1})$。

可以发现这个问题与 [LNOI2022] 盒 完全等价。考虑每条边被经过的次数，立得答案为

$$
\sum_{l\le i<r}(a_{i+1}-a_i)|s_i-s_{l-1}|
$$

$s$ 是 $b$ 的前缀和。用任何方式计算都是 $O(n\log n)$。

---

## 作者：qczrz6v4nhp6u (赞：1)

唐题，小丑官解。

### Solution

首先直接嗯造 MCMF 显然很小丑。我们考虑构造一个问题，使它能建模出这样的 MCMF。

可以构造出如下的问题：

> 有一个数轴，在 $a_i$ 处有一个出 / 入口。若 $b_i>0$ 则该处为入口，可以容纳 $b_i$ 个人；否则该处为出口，可以容纳 $-b_i$ 个人。最开始每个入口都挤满了人，这些人要全部移动到出口。求每个人走过的长度之和。

很唐的问题！我们考虑把出入口在数轴上画出来，统计每一段被走过的次数。由于 $a$ 不降，不难得到答案：

$$\sum_i(a_{i+1}-a_i)|\sum_{l\le j\le i}b_j|$$

对 $b$ 做前缀和，分类讨论绝对值就变成了二维数点，离线乱做。

最终的答案是（记 $s_i=\sum_{j=1}^ib_i$，$c_i=a_{i+1}-a_i$）：

$$\Big(\sum_{s_i>s_{l-1}}c_is_i\Big)-\Big(s_{l-1}\sum_{s_i>s_{l-1}}c_i\Big)-\Big(\sum_{s_i\le s_{l-1}}c_is_i\Big)+\Big(s_{l-1}\sum_{s_i\le s_{l-1}}c_i\Big)$$

[提交记录](https://codeforces.com/contest/1682/submission/236042371)。

---

## 作者：lingfunny (赞：1)

# CF1682F [MCMF?](https://codeforces.com/problemset/problem/1682/F)

~~高难度紫属于是~~

~~反正题解写起来还挺复杂度，代码就还行~~

## 第一步

**拆点**。把 $i$ 拆成 $|b_i|$ 个点，然后这 $|b_i|$ 个点和之前一样连边。

此时就是左右有相同数量的点，然后两个点 $(u, v)$ 相连的花费是 $|a_u-a_v|$，要把左右都匹配的最小花费。

此时最优解显然是左右分别按 $a_i$ 排序，然后左边 $i$ 连右边 $i$。

可以反证，设有一个别的构造，连了 $(u_i,v_i),(u_j,v_j),u_i\neq v_i, u_j\neq v_j$，读者自证不难。

## 第二步

此时已经有 $\Theta(\sum b_i)$ 回答询问的做法了，显然寄。瓶颈在于绝对值，考虑拆绝对值。

一个 $(a_i,b_i), (b_i>0)$，即一个右半部分的点的贡献是正还是负取决于前面还剩下多少个左半部分的点；记前缀和 $s_i=\sum\limits_{k=1}^i b_i$。

（为方便，下文中 $s$ 出现时，实际意义上下标均含 $-1$，于是将 $s$ 右移，下文的 $s_p$ 表示实际的 $s_p-1$）

对于一个询问 $[l,r]$，可以枚举每个 $b_i$，在 $O(r-l)$ 内做完：

1. $b_i > 0, \Delta =s_{i} - s_{l} < 0$，左边部分的点还有剩下的。
   1. $|b_i| \le |\Delta|$：贡献是 $a_i|b_i|$；
   2. $|b_i| > |\Delta|$：贡献是 $2a_i|\Delta|-a_i|b_i|$。
2. $b_i>0, \Delta \ge 0$，没有左半部分点，贡献是 $-a_i|b_i|$。

$b_i<0$ 同理。

## 第三步

现在复杂度是 $O(nq)$ 的，显然寄。考虑能否快速回答询问。

记后缀 $i$ 的答案为 $\mathrm{ans}_i$，会发现询问 $[l,r]$ 的答案为 $\mathrm{ans}_l - \mathrm{ans}_{r+1}$。~~（前缀也就算了，为什么会有人观察后缀性质啊喂~~

原因在于，$\sum\limits_{i=l}^rb_i=0$，对于后缀 $l$ 的答案，$[l,r]$ 和 $(r, n]$ 是不会相互影响的，计算 $(r, n]$ 时的起始状态，和计算后缀 $r+1$ 的起始状态是完全相同的。

## 第四步

现在复杂度是 $O(n^2)$ 的（每次重新算后缀答案），考虑怎么快速计算 $\mathrm{ans}_i$。

经典考虑 $(a_i, b_i)$ 对所有后缀 $1,2,\dots,i$ 的贡献。发现贡献和一个后缀 $k$ 没什么屁关系，只和 $s_{k}$ 有关系。

于是开一棵线段树，从 $1\sim n$ 遍历后缀 $k$：

1. 先给 $\mathrm{ans}_k$ 赋值为 $-\mathrm{val}_{s_k}$，这里的 $\mathrm{val}_p$ 指的是线段树上位置 $p$ 的值。
2. 再根据第二步添加贡献。
3. 遍历完所有后缀后，查询 $1\sim n$，令 $\mathrm{ans}_k \gets \mathrm{ans}_k + \mathrm{val}_{s_k}$。

关于添加贡献，会发现有个贡献和 $|\Delta|$ 有关，可以拆绝对值，此时对于修改位置 $i$，改变的量和 $s_i$ 有关，可以直接记该位置 $s_i$ 的系数，详见代码。

总时间复杂度 $O(n\log n + q)$。

什么？你说 $O(n\log 4\cdot10^{14}+q)$？不会离散化吗。

## 我的码呀

```cpp
// Problem: F. MCMF?
// From: Codeforces - Codeforces Round #793 (Div. 2)
// URL: https://codeforces.com/contest/1682/problem/F
// Time: 2022-05-22 22:36
// Author: lingfunny

#include <bits/stdc++.h>
#define LL long long
using namespace std;
#define int LL	// 这是一个违背祖宗的决定（但我真找不出来哪没开 long long :(
const int mxn = 2e5+10, mod = 1e9+7;

int n, q, a[mxn], b[mxn], tot, rk[mxn], ans[mxn];
LL sa[mxn], s[mxn];

int mul() { return 1; }
template <typename... A>
int mul(int x, A... a) { return (LL)(x < 0 ? x + mod : x)*mul(a...)%mod; }
struct segtr {
#define mid ((L+R)>>1)
#define lc (o<<1)
#define rc (lc|1)
	int tag[mxn<<2], pre[mxn<<2];
    // pre: 系数 tag: 显式值
	inline void add(int o, int t) { (tag[o] += t) %= mod; }
	inline void adp(int o, int t) { (pre[o] += t) %= mod; }
	int ask(int p, int k, int o = 1, int L = 1, int R = tot) {
		if(L == R) return (tag[o] + mul(pre[o], s[k])) % mod;
		return ((LL)tag[o] + mul(pre[o], s[k]) + (p <= mid ? ask(p, k, lc, L, mid) : ask(p, k, rc, mid+1, R)))%mod;
	}
	void mdf(int cl, int cr, int k, int p, int o = 1, int L = 1, int R = tot) {
		if(cl <= L && R <= cr) return p ? add(o, k) : adp(o, k);
		if(cl <= mid) mdf(cl, cr, k, p, lc, L, mid);
		if(cr > mid) mdf(cl, cr, k, p, rc, mid+1, R);
	}
} T;

signed main() {
	scanf("%lld%lld", &n, &q);
	for(int i = 1; i <= n; ++i) scanf("%lld", a+i);
	for(int i = 1; i <= n; ++i) scanf("%lld", b+i);
	for(int i = 1; i <= n; ++i) sa[i] = s[i] = s[i-1] + b[i-1];
	sort(sa+1, sa+n+1); tot = unique(sa+1, sa+n+1) - sa - 1;
	for(int i = 1; i <= n; ++i) rk[i] = lower_bound(sa+1, sa+tot+1, s[i]) - sa;
	for(int i = 1, L, R; i <= n; ++i) {
		ans[i] = (mod - T.ask(rk[i], i)) % mod;
		L = R = -1;
		if(b[i] > 0) {
			L = rk[i], R = lower_bound(sa+1, sa+tot+1, b[i]+s[i]) - sa;
			// [1, L] -ab
			// (L, R) 2as[l] - 2as[i] - ab
			// [R, tot] ab
			T.mdf(1, R - 1, mod - mul(a[i], b[i]), 1);
			if(R <= tot) T.mdf(R, tot, mul(a[i], b[i]), 1);
			if(R - L > 1) T.mdf(L+1, R-1, mod - mul(2, a[i], s[i]), 1), T.mdf(L+1, R-1, mul(2, a[i]), 0);
		} else if(b[i] < 0) {
			b[i] = -b[i];
			L = upper_bound(sa+1, sa+tot+1, s[i]-b[i]) - sa - 1, R = rk[i];
			// [R, tot] -ab
			// (L, R) 2as[i] - 2as[l] - ab
			// [1, L] ab
			T.mdf(L+1, tot, mod - mul(a[i], b[i]), 1);
			if(L >= 1) T.mdf(1, L, mul(a[i], b[i]), 1);
			if(R - L > 1) T.mdf(L+1, R-1, mul(2, a[i], s[i]), 1), T.mdf(L+1, R-1, mod - mul(2, a[i]), 0);
		}
	}
	for(int i = 1; i <= n; ++i) (ans[i] += T.ask(rk[i], i)) %= mod;
	while(q--) {
		int l, r; scanf("%lld%lld", &l, &r);
		printf("%lld\n", (ans[l] - ans[r+1] + mod) % mod);
	}
	return 0;
}
```



---

## 作者：Purslane (赞：0)

# Solution

发动技能『自信』，秒了。

首先注意到流量就是 $\dfrac{1}{2} \sum | b_i |$，因此每个点都要“完全匹配”。

考虑最终“匹配”的结构，如果出现了四个点 $a \le b \le c \le d$，使得 $a$ 和 $c$ 有匹配，$b$ 和 $d$ 有匹配，那么一定可以通过调整使得这种结构不存在。（$a$、$b$、$c$、$d$ 指的是在原数列中的下标）

- 如果 $a$ 和 $b$ 同号，$c$ 和 $d$ 同号，那么调整为 $a$ 与 $d$ 匹配，$b$ 和 $c$ 匹配。

- 如果 $a$ 和 $d$ 同号，$b$ 和 $c$ 同号，调整为 $a$ 和 $b$ 匹配，$c$ 和 $d$ 匹配。

因此最终的“匹配”类似于括号匹配，所以如果要 $O(nq)$ 暴力，直接使用一个栈跑。

在正解中我们显然不能用“栈”来刻画这种结构。考虑拆开每个数的贡献，为 $\pm a_i$ 中的一个。

稍微分析一下，发现总的贡献为 $a_i(|pre_{i-1} - pre_l| - |pre_i-pre_l|)$，使用扫描线和两个树状数组即可。（暴力拆绝对值）

> 这里做的时候有点意识流，大概就是发现贡献和查询左端点的 $pre_{l-1}$ 相对大小关系是一个分段函数的区间和，然后猜出了这个结构。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long 
#define ffor(i,a,b) for(int i=(a);i<=(b);i++)
#define roff(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
const int MAXN=2e5+10,MOD=1e9+7;
int n,q,tot,ans[MAXN],a[MAXN],b[MAXN],pre[MAXN],l[MAXN],r[MAXN],lsh[MAXN];
struct BIT {
	int n;vector<int> tr;	
	void init(int N) {return n=N,tr.resize(N+1),void();}
	void update(int pos,int v) {while(pos<=n) tr[pos]=(tr[pos]+v)%MOD,pos+=pos&-pos;return ;}
	int query(int pos) {int ans=0;while(pos) ans=(ans+tr[pos])%MOD,pos-=pos&-pos;return ans;}
};
vector<pair<int,pair<int,int>>> qr[MAXN];
signed main() {
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>q;
	ffor(i,1,n) cin>>a[i];
	ffor(i,1,n) cin>>b[i],pre[i]=pre[i-1]+b[i];
	ffor(i,1,q) cin>>l[i]>>r[i];
	ffor(i,0,n) lsh[++tot]=pre[i];
	sort(lsh+1,lsh+tot+1),tot=unique(lsh+1,lsh+tot+1)-lsh-1;
	ffor(i,0,n) pre[i]=lower_bound(lsh+1,lsh+tot+1,pre[i])-lsh;
	BIT bit1,bit2;
	bit1.init(tot),bit2.init(tot);
	ffor(i,1,q) qr[r[i]].push_back({pre[l[i]-1],{i,1}}),qr[l[i]-1].push_back({pre[l[i]-1],{i,-1}});	
	ffor(i,1,n) {
		bit1.update(pre[i-1],lsh[pre[i-1]]%MOD*a[i]%MOD);
		bit2.update(pre[i-1],a[i]);
		bit1.update(pre[i],-lsh[pre[i]]%MOD*a[i]%MOD);
		bit2.update(pre[i],-a[i]);
		for(auto pr:qr[i]) {
			int val=pr.first,res=0;
			res=(res+lsh[val]%MOD*bit2.query(val)-bit1.query(val))%MOD;
			res=(res+bit1.query(tot)-bit1.query(val)-lsh[val]%MOD*((bit2.query(tot)-bit2.query(val))%MOD)%MOD)%MOD;
			ans[pr.second.first]=(ans[pr.second.first]+pr.second.second*res)%MOD;
		}
	}
	ffor(i,1,q) cout<<(ans[i]%MOD+MOD)%MOD<<'\n';
	return 0;
}
```

---

