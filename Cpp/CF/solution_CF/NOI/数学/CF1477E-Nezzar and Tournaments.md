# Nezzar and Tournaments

## 题目描述

In the famous Oh-Suit-United tournament, two teams are playing against each other for the grand prize of precious pepper points.

The first team consists of $ n $ players, and the second team consists of $ m $ players. Each player has a potential: the potential of the $ i $ -th player in the first team is $ a_i $ , and the potential of the $ i $ -th player in the second team is $ b_i $ .

In the tournament, all players will be on the stage in some order. There will be a scoring device, initially assigned to an integer $ k $ , which will be used to value the performance of all players.

The scores for all players will be assigned in the order they appear on the stage. Let the potential of the current player be $ x $ , and the potential of the previous player be $ y $ ( $ y $ equals $ x $ for the first player). Then, $ x-y $ is added to the value in the scoring device, Afterwards, if the value in the scoring device becomes negative, the value will be reset to $ 0 $ . Lastly, the player's score is assigned to the current value on the scoring device. The score of a team is the sum of the scores of all its members.

As an insane fan of the first team, Nezzar desperately wants the biggest win for the first team. He now wonders what is the maximum difference between scores of the first team and the second team.

Formally, let the score of the first team be $ score_f $ and the score of the second team be $ score_s $ . Nezzar wants to find the maximum value of $ score_f - score_s $ over all possible orders of players on the stage.

However, situation often changes and there are $ q $ events that will happen. There are three types of events:

- $ 1 $ $ pos $ $ x $ — change $ a_{pos} $ to $ x $ ;
- $ 2 $ $ pos $ $ x $ — change $ b_{pos} $ to $ x $ ;
- $ 3 $ $ x $ — tournament is held with $ k = x $ and Nezzar wants you to compute the maximum value of $ score_f - score_s $ .

Can you help Nezzar to answer the queries of the third type?

## 说明/提示

In the first query of the first test, the tournament is held with $ k = 5 $ . It would be optimal to arrange players in such way (here their potentials are written):

 $ \underline{7} $ , $ 3 $ , $ 5 $ , $ 4 $ , $ 6 $ , $ \underline{1} $ , $ \underline{2} $ (underlined numbers are potentials of players that are from the first team).

The individual scores of players, numbered in the order of their appearance, are:

- $ \max(5 + (7 - 7), 0) = 5 $ for the $ \underline{1} $ -st player;
- $ \max(5 + (3 - 7), 0) = 1 $ for the $ 2 $ -nd player;
- $ \max(1 + (5 - 3), 0) = 3 $ for the $ 3 $ -rd player;
- $ \max(3 + (4 - 5), 0) = 2 $ for the $ 4 $ -th player;
- $ \max(2 + (6 - 4), 0) = 4 $ for the $ 5 $ -th player;
- $ \max(4 + (1 - 6), 0) = 0 $ for the $ \underline{6} $ -th player;
- $ \max(0 + (2 - 1), 0) = 1 $ for the $ \underline{7} $ -th player.

So, $ score_f = 5 + 0 + 1 = 6 $ and $ score_s = 1 + 3 + 2 + 4 = 10 $ . The score difference is $ 6 - 10 = -4 $ . It can be proven, that it is the maximum possible score difference.

## 样例 #1

### 输入

```
3 4 3
1 2 7
3 4 5 6
3 5
1 1 10
3 5```

### 输出

```
-4
9```

## 样例 #2

### 输入

```
7 8 12
958125 14018 215153 35195 90380 30535 204125
591020 930598 252577 333333 999942 1236 9456 82390
3 123458
2 4 444444
3 123456
1 2 355555
3 123478
3 1111
2 6 340324
3 1111
2 8 999999
2 7 595959
3 222222
3 100```

### 输出

```
1361307
1361311
1702804
1879305
1821765
1078115
1675180```

# 题解

## 作者：xtx1092515503 (赞：6)

我们考虑找到一组好的排列方式。

首先考虑假如这个排列中有一段连续且属于同一个队的部分应该怎样排列。

不妨假设这段开始时，$K$ 的值足够大，则每个位置 $x_i$ 的贡献都是 $K+x_i-z$，其中 $z$ 是这段开头前一个数。

但是现在 $K$ 不够大。于是现在其贡献可以比 $\sum K+x_i-z$ **更大**，因为把 $K$ 减到 $0$ 就不会更小了。

于是我们便想让其更早被减到 $0$。那么把它递增排列即可。同理，$b$ 应该递减排列。

然后考虑 $a,b$ 间的关系。得出结论是，$b$ 的所有元素都应该放在 $a$ 之前——除了一个特殊的东西，即 $c_1$。

这需要我们写出在 $c$ 固定时的式子：$K-c_1+c_i+\max(0,c_1-K-\min\limits_{j\leq i}\{c_j\})$。其中，$K-c_1+c_i$ 是不与 $0$ 取 $\max$ 时的贡献，而后面的那个 $\max$ 是取 $\max$ 时出现的额外贡献。

可以发现 $c_1$ 确实是在这个式子中扮演一个很重要的角色。

令 $f(x)$ 表示选择一个 $a_i=x$ 作为 $c_1$ 时的答案。则有 

$$
f(x)=K+\sum\limits_{a_i\text{ except one equals to }x}\Big(K-x+a_i+\max(0,x-K-\min\{a,b\})\Big)-\sum\limits_{b_i}\Big(K-x+b_i+\max(0,x-K-b_i)\Big)\\=K+(n-1)\Big(K-x+\max(0,x-K-\min\{a,b\})\Big)+\Big(\sum a_i\Big)-x-m(K-x)-\sum\limits_{b_i}\Big(b_i+\max(0,x-K-b_i)\Big)\\=(n-m)(K-x)+(n-1)\max(0,x-K-\min\{a,b\})+\Big(\sum a_i\Big)-\Big(\sum b_i\Big)-\sum\limits\max(0,x-K-b_i)
$$

把常数提出来。令 $C=(n-m)K+\sum a_i-\sum b_i$，最终得到

$$f(x)=(m-n)x+(n-1)\max(0,x-K-\min\{a,b\})-\sum\limits\max(0,x-K-b_i)+C$$

考虑把这个函数画在坐标系上：初始有一个 $(m-n)$ 的斜率；在 $K+\min$ 处斜率增加了 $n-1$（也即，变成了 $m-1$），然后随着 $x$ 增加在若干个位置减少一。最大值显然发生在斜率为 $0$ 的位置——这意味着是 $b$ 中的次大值加 $K$ 附近。

故可能的极值候选只有这些元素：

- $\min\{a\}$（这可能发生在 $m$ 远小于 $n$ 的场合）
- （$b$ 中的次大值加 $K$）在 $a$ 中的前驱或后缀。

现在考虑 $g$。仍然要推一下式子：

$$
g(x)=\sum\limits_{a_i}\Big(K-x+a_i+\max(0,x-K-\min\{a,b\})\Big)-\sum\limits_{b_i\text{ except one equals to }x}\Big(K-x+b_i+\max(0,x-K-b_i)\Big)-K
\\=n\Big(K-x+\max(0,x-K-\min\{a,b\})\Big)+\Big(\sum a_i\Big)-(m-1)(K-x)-\Big(\sum\limits_{b_i}b_i\Big)+x-\sum\limits_{b_i}\max(0,x-K-b_i)-K
\\=(n-m)(K-x)+n\max(0,x-K-\min\{a,b\})+\Big(\sum a_i\Big)-\Big(\sum b_i\Big)-\sum\limits\max(0,x-K-b_i)
\\=(m-n)x+n\max(0,x-K-\min\{a,b\})-\sum\limits\max(0,x-K-b_i)+C
$$

可以发现这也是类似的。只不过因为斜率是 $m$，进而直接采取最大值即可。

进而极值候选即为：

- $\min\{b\}$。
- $\max\{b\}$。

于是每次询问时就挑出上述 $O(1)$ 个数进行询问即可。维护询问是简单的。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
const int V=1000000;
typedef long long ll;
int n,m,q,a[200100],b[200100];
ll C;
multiset<int>A,B;
void insertA(int x){A.insert(x),C+=x;}
void eraseA(int x){A.erase(A.find(x)),C-=x;}
#define lson x<<1
#define rson x<<1|1
#define mid ((l+r)>>1)
struct SegTree{int num;ll sum;}seg[V<<2];
void modify(int x,int l,int r,int P,int tp){
	seg[x].num+=tp,seg[x].sum+=tp*P;
	if(l!=r)P<=mid?modify(lson,l,mid,P,tp):modify(rson,mid+1,r,P,tp);
}
ll query(int x,int l,int r,int P){
	if(l>P)return 0;
	if(r<=P)return 1ll*P*seg[x].num-seg[x].sum;
	return query(lson,l,mid,P)+query(rson,mid+1,r,P);
}
int Kth(int x,int l,int r,int K){
	if(l==r)return l;
	return seg[lson].num>=K?Kth(lson,l,mid,K):Kth(rson,mid+1,r,K-seg[lson].num);
}
void insertB(int x){B.insert(x),C-=x,modify(1,0,V,x,1);}
void eraseB(int x){B.erase(B.find(x)),C+=x,modify(1,0,V,x,-1);}
ll queryA(int K,int x){
//	printf("%d %d\n",K,x);
	return 1ll*(n-m)*K+C+1ll*(m-n)*x+1ll*(n-1)*max(0,x-K-min(*A.begin(),*B.begin()))-query(1,0,V,x-K);
}
ll queryB(int K,int x){
	return 1ll*(n-m)*K+C+1ll*(m-n)*x+1ll*n*max(0,x-K-min(*A.begin(),*B.begin()))-query(1,0,V,x-K);
}
ll solve(int K){
	ll ret=max(queryA(K,*A.begin()),queryB(K,*B.begin()));
	auto it=A.lower_bound(Kth(1,0,V,m-1)+K);
	if(it!=A.end())ret=max(ret,queryA(K,*it));
	if(it!=A.begin())ret=max(ret,queryA(K,*--it));
	ret=max(ret,queryB(K,*B.rbegin()));
	return ret;
}
int main(){
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)scanf("%d",&a[i]),insertA(a[i]);
	for(int i=1;i<=m;i++)scanf("%d",&b[i]),insertB(b[i]);
	for(int i=1,tp,x;i<=q;i++){
		scanf("%d%d",&tp,&x);
		if(tp==1)eraseA(a[x]),scanf("%d",&a[x]),insertA(a[x]);
		if(tp==2)eraseB(b[x]),scanf("%d",&b[x]),insertB(b[x]);
		if(tp==3)printf("%lld\n",solve(x));
	}
	return 0;
}
```



---

## 作者：tzc_wk (赞：3)

[Codeforces 题目传送门](https://codeforces.com/contest/1477/problem/E) & [洛谷题目传送门](https://www.luogu.com.cn/problem/CF1477E)

~~1477 可还行（My rating is 1477.~~

~~部分思路借鉴了 ymx 鸽鸽的题解，因为现在好像全网除了官方题解只有这一篇题解。~~

首先考虑对于一种固定的安排选手顺序的方案 $c$，如何求遍历到第 $i$ 个选手时的得分。如果不考虑对 $0$ 取 $\max$ 的限制，那显然就是 $K+(c_2-c_1)+(c_3-c_2)+\cdots+(c_i-c_{i-1})=K+c_i-c_1$。但由于每次得分对 $0$ 取 $\max$ 这一机制的存在，对于得分小于 $0$ 的时刻，归零这一操作相当于给得分加上了当前得分的相反数，也就是说，真实得分其实是不小于我们算出来的得分 $K+c_i-c_1$ 的，那么我们究竟应该如何计算真实得分比我们算出来的得分大多少呢？考虑取出下标 $\le i$ 且值最小的 $c_j$，那么总的增量就是使得 $K+c_j-c_1$ 变得 $\ge 0$ 的最大增量，即 $\max(c_1-K-c_j,0)$。因此我们有 $d_i=K+c_i-c_i+\max(c_1-K-(\min\limits_{j\le i}c_j),0)$。

注意到上面的式子中，$c_1$ 起一个类似于主元的作用，因此考虑将其拎出来，不妨假设其值已经确定，如何安排后面位置上的值。显然对于 $b$ 中的数而言，我们希望后面的 $\max$ 越小越好，因此我们会将其降序排序，同理，对于 $a$ 中的数而言，我们希望后面的 $\max$ 越大越好，因此我们会将其升序排序，至于 $a,b$ 的相对顺序关系……我们肯定希望 $b$ 尽量排在前面，$a$ 尽量排在后面，因此我们肯定会先安排 $b$ 再安排 $a$，即假设去掉 $c_1$ 后 $a$ 升序排序的结果为 $p$，长度为 $n’$，$b$ 降序排序的结果为 $q$，长度为 $m’$，那么最优方案的 $c$ 序列将会是 $q_1,q_2,\cdots,q_{m’},p_1,p_2,\cdots,p_{n’}$。 

接下来考虑带上 $c_1$ 的限制，考虑什么样的 $c_1$ 可能成为最优解。假设 $f(t)$ 表示 $c_1$ 出自 $a$ 序列且 $=t$ 的最大分数差，$g(t)$ 表示 $c_1$ 出自 $b$ 序列且 $=t$ 的最大分数差，那么：
$$
\begin{aligned}
f(t)&=k-\sum\limits_{i=1}^m(k-t+b_i+\max(t-k-b_i,0))+\sum\limits_{i=1}^n(k-t+a_i+\max(t-k-M,0))-(k-t+t-\max(t-k-M,0)\\
&=(k-t)·(n-m)+\sum\limits_{i=1}^na_i-\sum\limits_{j=1}^mb_i-\sum\limits_{i=1}^m\max(t-k-b_i,0)+\max(t-k-M,0)·(n-1)\\
&=t·(m-n)-\sum\limits_{i=1}^m\max(t-k-b_i,0)+\max(t-k-M,0)·(n-1)+(k·(n-m)+\sum\limits_{i=1}^na_i-\sum\limits_{j=1}^mb_i)
\end{aligned}
$$
其中 $M=\min(\min\limits_{i=1}^na_i,\min\limits_{j=1}^mb_j)$。

考虑将与 $t$ 有关的项提出来并画出 $f(t)$ 关于 $t$ 的函数图像，那么应是先一段斜率为 $m-n$ 的折线，然后在 $k+M$ 处斜率突增 $n-1$，变为 $m-1$，再后来，每 $\ge$ 一个 $k+b_i$ 斜率都会 $-1$，最后斜率变为 $-1$。大致图像如下图所示（图片来自 CF 官方题解）：

![](https://espresso.codeforces.com/9244f64d31ceb89bee57a166ae05c97bc980ab85.png)

不难发现最优解要么在最左端取到，要么在倒数第二段线段的两个断点处取到，因此只要暴力计算这三个值的 $f$ 后取 $\max$ 即可算出 $a$ 中元素作为 $c_1$ 的最大分数差。

接下来考虑 $g$，式子推法基本一样：
$$
\begin{aligned}
g(t)&=-k-\sum\limits_{i=1}^m(k-t+b_i+\max(t-k-b_i,0))+\sum\limits_{i=1}^n(k-t+a_i+\max(t-k-M,0))-(k-t+t-\max(t-k-t,0))\\
&=-k+(k-t)·(n-m)+\max(t-k-M,0)·n-\sum\limits_{i=1}^m\max(t-k-b_i,0)+\sum\limits_{i=1}^na_i-\sum\limits_{i=1}^mb_i\\
&=t·(m-n)+\max(t-k-M,0)·n+\sum\limits_{i=1}^m\max(t-k-b_i,0)+(k·(n-m-1)+\sum\limits_{i=1}^na_i-\sum\limits_{i=1}^mb_i)
\end{aligned}
$$
和上面的折线形态基本一致，只不过少了最后斜率为 $-1$ 的部分，因此我们只用 check $b$ 中最小值和最大值即可。

至于怎么计算 $f(t),g(t)$，注意到式子大部分都至于 $k,t,n,m,M,\sum a_i,\sum b_i$ 有关，都可以 $\mathcal O(1)$ 求得，唯独 $\sum\limits_{i=1}^m\max(t-k-b_i,0)$ 与序列 $b$ 的具体数值有关，这个可以通过对 $b$ 建权值线段树轻松搞定。

时间复杂度 $(n+q)\log n$。

```cpp
const int MAXN = 2e5;
const int MAXV = 1e6;
const int MAXP = MAXV * 4;
const int INF = 0x3f3f3f3f;
const ll INFll = 0x3f3f3f3f3f3f3f3fll;
int n, m, qu, a[MAXN + 5], b[MAXN + 5];
multiset<int> stA, stB; ll sumA, sumB;
struct node {int ch[2], siz; ll sum;} s[MAXP + 5];
int rt, ncnt;
void insert(int &k, int l, int r, int p, int v) {
	if (!k) k = ++ncnt; s[k].siz += v; s[k].sum += p * v;
	if (l == r) return; int mid = l + r >> 1;
	(p <= mid) ? insert(s[k].ch[0], l, mid, p, v) : insert(s[k].ch[1], mid + 1, r, p, v);
}
pair<int, ll> query(int k, int l, int r, int ql, int qr) {
	if (!k || ql > qr) return mp(0, 0);
	if (ql <= l && r <= qr) return mp(s[k].siz, s[k].sum);
	int mid = l + r >> 1;
	if (qr <= mid) return query(s[k].ch[0], l, mid, ql, qr);
	else if (ql > mid) return query(s[k].ch[1], mid + 1, r, ql, qr);
	else {
		auto pl = query(s[k].ch[0], l, mid, ql, mid);
		auto pr = query(s[k].ch[1], mid + 1, r, mid + 1, qr);
		return mp(pl.fi + pr.fi, pl.se + pr.se);
	}
}
void insA(int v) {sumA += v; stA.insert(v);}
void insB(int v) {sumB += v; stB.insert(v); insert(rt, 0, MAXV, v, 1);}
void delA(int v) {sumA -= v; stA.erase(stA.find(v));}
void delB(int v) {sumB -= v; stB.erase(stB.find(v)); insert(rt, 0, MAXV, v, -1);}
ll ask(int k, int t, int opt) {
	int M = INF;
	if (!stA.empty()) chkmin(M, *stA.begin());
	if (!stB.empty()) chkmin(M, *stB.begin());
	ll res = opt * k + 1ll * (k - t) * (n - m) + sumA - sumB;
//	printf("! ask %d %d %d %lld\n", k, t, M, res);
	res += 1ll * max(t - k - M, 0) * n;
	auto P = query(rt, 0, MAXV, 0, t - k);
	res -= 1ll * (t - k) * P.fi - P.se;
	return res;
}
ll queryA(int k, int t) {delA(t); --n; ll res = ask(k, t, 1); insA(t); ++n; return res;}
ll queryB(int k, int t) {delB(t); --m; ll res = ask(k, t, -1); insB(t); ++m; return res;}
ll query(int k) {
	ll res = -INFll;
	chkmax(res, queryA(k, *stA.begin()));
	if (stB.size() >= 2) {
		int v = (*++stB.rbegin()) + k;
		multiset<int> :: iterator it = stA.lower_bound(v);
		int A = -1, B = -1;
		if (it != stA.end()) A = *it;
		if (it != stA.begin()) B = *--it;
		if (~A) chkmax(res, queryA(k, A));
		if (~B) chkmax(res, queryA(k, B));
	}
	chkmax(res, queryB(k, *stB.begin()));
	chkmax(res, queryB(k, *stB.rbegin()));
	return res;
}
int main() {
	scanf("%d%d%d", &n, &m, &qu);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i]), insA(a[i]);
	for (int i = 1; i <= m; i++) scanf("%d", &b[i]), insB(b[i]);
	while (qu--) {
		int opt; scanf("%d", &opt);
		if (opt == 1) {
			int p, x; scanf("%d%d", &p, &x);
			delA(a[p]); a[p] = x; insA(a[p]);
		} else if (opt == 2) {
			int p, x; scanf("%d%d", &p, &x);
			delB(b[p]); b[p] = x; insB(b[p]);
		} else {
			int k; scanf("%d", &k);
			printf("%lld\n", query(k));
		}
	}
	return 0;
}
```



---

## 作者：约瑟夫用脑玩 (赞：3)

*3300

题和题解都很 der，但是我实力不到 *800，**实力是远低于这道题的，记录一下是有必要的**（见昨晚比赛![](https://cdn.luogu.com.cn/upload/image_hosting/t41xgunq.png)

------------

先解决翻译问题：给你长为 $n,m$ 的两个数列 $a,b$，初始有个值为 $k$ 的计分板。

设 $c$ 一个长为 $n+m$ 的数列，$c$ 中每个数**恰对应 $a,b$ 中的某个数**，令 $d_i$ 为第 $i$ 个数原本属于哪个数列。

依次往计分板中加入数 $c_i$，计分板增加 $c_i-c_{i-1}$ 的权值（可负），**初始有 $c_0:=c_1$ 避开边界情况**。

**计分板始终对 $0$ 取 $\max$，设第 $i$ 个数加入后计分板为 $v_i$，形式化的有 $v_i=\max{(0,v_{i-1}+c_i-c_{i-1})}$。**

在加入 $c_i$ 这个数时，会对 $d_i$ 这个数列产生 $v_i$ 的贡献，设最终的贡献分别为 $W_a,W_b$。

求 $c$ 的所有情况中 $W_a-W_b$ 的最大值。

支持操作：单点修改 $a,b$，给定 $k$ 进行询问。

------------

解法一：手玩，需要比较好的感觉。

首先不考虑支持修改，先手玩一下这个询问。

一秒会做 $k=0$ 的情况，即先倒序的把 $b$ 数列放完，使得 $b$ 的贡献全部没有，$W_b=0$，然后再升序的放 $a$ 数列，可以使得贡献最大。

为了方便默认 $a,b$ 按从小到大排好了序，有：

$$sum=W_a-W_b=W_a=\sum_{i=1}^n(\max(0,a_1-b_1)+a_i-a_1)$$

考虑 $k$ 有值会发生什么变化，首先倒序的把 $b$ 数列放完然后再升序的放 $a$ 数列的策略仍然是我们的优选方案之一。

也即上式加上 $k$ 的贡献，由于要考虑 $b_1\to a_1$ 处的转折，为了方便定义 $M=\min(a_1,b_1)$：

$$sum=W_a-W_b=-\sum_{i=1}^m\max(0,k-(b_n-b_i))+\sum_{i=1}^n(\max(0,k-b_n+M)+a_i-M)$$

发现唯一的可能性就是我们单独拎出一个 $a_x$ 垫在所有的 $b$ 前面，剩下的数同上策略的相对顺序不变。

感性理解一下如果多拎了一个出来把两个中大的那个放回 $a$ 去贡献更大。

于是我们考虑放哪个 $a$ 的得到最优的答案，直接列式：

$$sum=W_a-W_b=k-\sum_{i=1}^m\max(0,k-(a_x-b_i))+\sum_{i=1}^n(\max(0,k-a_x+M)+a_i-M)-(\max(0,k-a_x+M)+a_x-M)$$

考虑维护上述两式的最大值，第一式是简单的，每次改变量 $O(1)$ 整个式子也可以 $O(1)$ 的计算。

第二个式子不太一样，因为有一个变量 $a_x$，考虑按 $a_x$ 为主元归类，有：

$$sum=(-a_x+M)+(n-1)\max(0,k-a_x+M)-\sum_{i=1}^m\max(0,k-a_x+b_i)+k+\sum_{i=1}^na_i-M$$

单调的考察 $a_x$ 变化时的贡献，发现 $a_x$ 的系数一来是 $m-n$，然后会先遇到 $k+M$ 加一个 $n-1$ 变成 $m-1$，后来遇到一个 $k+b_i$ 就减一，直到走过 $b_n$ 变成 $-1$。

故第二式最优值的取值可能为：

- $m<n$ 时：$a_x=a_1$。
- 考虑从 $m-1\to -1$ 的峰，显然是斜率为 $0$ 的段 $[b_{n-1},b_n]$ 内的 $a_x$，若没有则找前后，即维护 $a_x$ 为 $b$ 次大/最大前驱后继的值即可。

$O(1)$ 改变量显然也能维护。

------------

解法二：理性理解。

考虑数列 $c$，先不考虑数列 $d$，即先考虑每个数的贡献而不考虑贡献到了哪里。

发现 $c_1$ 的存在很不利于我们的计算，于是单独拎出来，有这样的公式：

$$v_i=k+c_i-c_1+\max(0,c_1-k-\min_{j\le i}c_j)$$

另外两篇题解都是这种做法然而在这**关键一招**上没解释清楚，实际上可以这样理解：

我们令 $w_i=v_i-c_i$，那么 $v_i=\max{(0,w_{i-1}+c_i)},w_i=v_i-c_i$，考虑维护 $w_i$，就是加上 $c_i$ 后和 $0$ 取个 $\max$ 再减回来。

如果 $c_i$ 抬高了显然碰不到 $0$ 这个位置，于是抬的最低的那次显然决定了当前 $w_i$ 的值。

初始有 $w_0=k-c_1$ 可以使得 $v_1=k$，于是 $w_i=w_1+\max{(0,0-w_1-\min_{j\le i}c_j)}$，即考虑抬 $c_i$ 最低的那次对 $w$ 的贡献，将 $v_i$ 代回此式子即得到上述公式。

发现当 $c_1$ 定了 $v_i$ 就只与自己的 $c_i$ 和在它前面的数有关了，考虑当 $c_1$ 确定时其他数该如何确定 $c_i,d_i$。

首先 $d_i=b$ 的贡献要最少，而 $-\min_j{c_j}$ 不减，于是将它们都放在前面，而为了让 $-\min_j{c_j}$ 小显然倒序放即可。

考虑让剩下的 $d_i=a$ 的贡献尽量多，显然先把最小的 $a$ 放了即可（为了不和我的手玩矛盾可以看作正序放qwq，实际上也可以发现对推式子没有任何影响

然后就根据这个列式即可，和上述手玩出来的式子一模一样，分析斜率即可得到 $c_1$ 的选择在哪里最优。

两种方法的理解过程不同，哪种好想也不好说，你看我就是解法一推了大半找题解的解法二验证了自己的想法。

实际上推其他题解的 $g$ 的式子会得到和手玩一样的发现：直接取最大的 $b$ 当 $c_1$ 即可。

---

