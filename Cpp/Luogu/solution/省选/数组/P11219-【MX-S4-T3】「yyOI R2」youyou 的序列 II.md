# 【MX-S4-T3】「yyOI R2」youyou 的序列 II

## 题目背景

原题链接：<https://oier.team/problems/S4C>。

## 题目描述

给定一个长度为 $n$ 的非负整数序列 $a$，初始时所有数均被标记为**蓝色**，youyou 和 yy 轮流对序列 $a$ 进行操作，由 youyou 开始。

- 如果当前是 youyou 的回合，那么他可以选择一个长度至多为 $c_1$ 的区间，如果该区间内所有数的和小于等于 $w_1$，则标记该区间所有数为**红色**。

- 如果当前是 yy 的回合，那么他可以选择一个长度至多为 $c_2$ 的区间，如果该区间内所有数的和大于 $w_2$，则标记该区间所有数为**蓝色**。

如果当前操作方没有可操作的区间，他将跳过本回合。

定义 youyou 胜利即是在游戏任意时刻，所有数都被标记为红色。定义 yy 胜利则是在 $10^{51971}$ 个回合内，youyou 无法胜利。两者都会以最优策略进行游戏。

但是他们认为这个游戏太简单了，于是决定上上强度。

现在给定 $q$ 个操作，对于每个操作给定三个数 $opt,x,y$。

- 如果 $opt$ 为 $1$，表示将 $a_x$ 增加 $y$（$0\le y \le 10^9$）。
- 如果 $opt$ 为 $2$，表示 youyou 和 yy 将在区间 $[x,y]$ 所形成的序列上进行一轮游戏。

对于每个 $opt=2$ 的操作，请你求出在区间 $[x,y]$ 所形成的序列上进行游戏，youyou 能否获得胜利。如果 youyou 能胜利，输出 ```cont```；否则，输出 ```tetris```。


## 说明/提示

**【样例解释 #1】**

第一次游戏在序列 $[1,0,0,1,1]$ 上进行。

回合 $1$：youyou 将区间 $[1,3]$ 内的数染红。

回合 $2$：yy 没有可操作的区间，**跳过**了本回合。

回合 $3$：youyou 将区间 $[4,5]$ 内的数染红。

此时所有数都被染红，youyou 获胜，输出  ```cont```。

第二次游戏在序列 $[1,0,3,1,1]$ 上进行。

容易发现，此时 youyou 无法获胜，输出 ```tetris```。


**【样例 #3】**

见附件中的 ```seq/seq3.in``` 与 ```seq/seq3.ans```。

该组样例满足测试点 $5\sim 8$ 的约束条件。

**【样例 #4】**

见附件中的 ```seq/seq4.in``` 与 ```seq/seq4.ans```。

该组样例满足测试点 $9\sim10$ 的约束条件。

**【样例 #5】**

见附件中的 ```seq/seq5.in``` 与 ```seq/seq5.ans```。

该组样例满足测试点 $11\sim 14$ 的约束条件。

**【数据范围】**

本题共 $20$ 个测试点，每个 $5$ 分。

|  测试点编号  |          $n$          |         $q$         |  特殊性质  |
| :----------: | :-------------------: | :-----------------: | :--------: |
|  $1\sim 4$   |       $\le10^2$       | $\le 3 \times 10^2$ | A |
|  $5 \sim 8$  |       $\le10^3$       | $\le 3 \times 10^3$ | B |
| $9 \sim 10$  |       $\le10^4$       | $\le 3 \times 10^4$ | C |
| $11 \sim 14$ |     $\le  10 ^ 5$     | $\le 3 \times 10^5$ | D |
| $15\sim 20$  | $\le 3 \times 10 ^ 5$ | $\le 3 \times 10^5$ |     无     |

特殊性质 A：$c_2 > n$，$w_2 = 0$。  
特殊性质 B：$w_1 \le w_2$。  
特殊性质 C：$c_1 \le c_2$。  
特殊性质 D：$c_1,c_2 \le 10^3$。

对于全部数据，保证：
- $1\le n,q,c_1,c_2\le 3\times10^5$。
- $0\le a_i,w_1,w_2\le 10^9$。
- $opt\in \{1,2\}$。
- 对于 $opt=1$ 的操作，$1\leq x\leq n$，$0\leq y\leq 10^9$。
- 对于 $opt=2$ 的操作，$1\leq x\leq y\leq n$。
- 至少有一个 $2$ 类操作。

## 样例 #1

### 输入

```
5 3 4 2 2 3
1 0 0 1 1
2 1 5
1 3 3
2 1 5```

### 输出

```
cont
tetris
```

## 样例 #2

### 输入

```
8 6 10 3 5 2
0 1 0 0 1 0 0 1
2 1 7
1 4 2
2 5 7
1 5 1
1 7 2
2 1 8```

### 输出

```
cont
cont
tetris
```

# 题解

## 作者：modfish_ (赞：11)

## 思路
先提出一个结论（以下讨论均局限于询问的区间 $(x,y)$ 中）：

令第二个人可以操作的区间集合为 $S$，即：

$$S=\{(l,r)\mid r-l+1\le c_2,\sum_{i=l}^ra_i>w_2\}$$

如果存在一个区间 $(L,R)$ 满足：

- 第一个人可以操作 $(L,R)$，即 $R-L+1\le c_1,\sum_{i=l}^r\le w_1$。

- $(L,R)$ 包含 $S$ 中所有的区间，即 $L\le\min_{(l,r)\in S}l,R\ge\min_{(l,r)\in S}r$。

并且如果忽略第二个人的存在，这个区间可以全部变成红色，即 $\max_{i=x}^ya_i\le w_1$。

如果以上两个条件均满足，那么第一个人会赢。否则第二个人会赢。

---

#### 证明

先证充分性：充分性是显然的。第一个人只需要先把 $S$ 没有覆盖的点变成红色，再对 $(L,R)$ 操作，一次性把剩下的点变红，第一个人就赢了。

然后证必要性：考虑反证。假设不存在区间 $(L,R)$，下面给出一种第二个人的操作策略，使得第一个人无法胜利。

设 $S$ 中左端点最靠左的区间为 $(l_1,r_1)$，右端点最靠右的区间为 $(l_2,r_2)$。

假设第一个人操作了区间 $(l_3,r_3)$：

- 若 $l_3\le l_1\le r_3$，即操作影响了 $l_1$，那么操作区间 $(l_1,r_1)$，使 $l_1$ 变回蓝色。

- 若 $l_3\le r_2\le r_3$，即操作影响了 $r_2$，那么操作区间 $(l_2,r_2)$，使 $r_2$ 变回蓝色。

- 否则，可以任意进行操作。

因为第一个人的可操作区间中不存在 $(L,R)$ 满足 $L\le l_1,R\ge r_2$，所以前两种情况不会同时出现，故这个操作是可以实现的。而这样操作保证了每一轮操作后 $a_{l_1},a_{r_2}$ 中至少有一个是蓝色的，故第一个人不可能获胜。

---

于是我们证明了这个结论。于是我们可以对于每次询问，找到集合 $S$ 的左边界和右边界（即证明中提到的 $l_1,r_2$），然后判断是否存在一个区间 $(L,R)$，满足开始提到的两个条件即可。

容易发现，当且仅当第一个人可以操作 $(l_1,r_2)$ 时，满足条件的 $(L,R)$ 存在。这是因为，区间的长度越长，其区间和就越大，就越有可能不满足条件，所以 $(l_1,r_2)$ 是最有可能满足条件的区间。所以直接判断 $r_2-l_1+1\le c_1,\sum_{i=l_1}^{r_2}a_i\le w_1$ 是否成立即可。

那么如何寻找 $(l_1,r_2)$ 呢？同样容易发现，区间的长度越短，其区间和就越小，就越有可能不能被第二个人操作。所以，只需要找所有长度为 $c_2$ 的区间进行判断即可。

可以维护一个值 $f_i$ 表示 $a_i$ 到 $a_{i+c_2-1}$ 的，即：

$$f_i=\sum_{j=i}^{i+c_2-i}a_i$$

那么，$l_1$ 就是满足 $f_i>w_2$ 的最小的 $i$，$r_2-c_2+1$ 就是满足 $f_i>w_2$ 的最大的 $i$。可以用线段树维护 $f_i$，查询时在线段树上二分即可。这样就得到了 $(l_1,r_2)$。

当然，如果 $y-x+1<c_2$，就只需要判一下 $(x,y)$ 能不能被第二个人操作即可。

总结一下，具体的步骤就是：

- 先判一下 $\max_{i=x}^ya_i\le w_1$ 是否成立，若不成立直接输出 `tetris`。

- 然后判断 $y-x+1$ 与 $c_2$ 的大小关系。如果 $y-x+1<c_2$，直接判断 $\sum_{i=x}^ya_i>w_2$ 是否成立，若成立就令 $l_1=x,r_2=y$，否则输出 `cont`（因为这时第二个人无法操作）。

- 如果 $y-x+1\le c_2$，就用之前讲的方法求 $(l_1,r_2)$。

- 最后判断第一个人能否操作 $(l_1,r_2)$，即 $r_2-l_1+1\le c_1,\sum_{i=l_1}^{r_2}a_i\le w_1$ 是否成立。若成立则输出 `cont`，否则输出 `tetris`。

然后就做完了。修改使用线段树、树状数组容易维护。时间复杂度 $O(q\log n)$。

## 代码

```cpp
#include <bits/stdc++.h>
#define ll long long

using namespace std;

const int maxn = 3e5 + 5;

int n, q, c1, c2;
ll w1, w2;
ll a[maxn], tr[maxn];

void upd(int id, ll k){
	for(int i = id; i <= n; i += i & -i) tr[i] += k; 
}
ll que(int id){
	ll s = 0;
	for(int i = id; i > 0; i -= i & -i) s += tr[i];
	return s;
}
namespace seg{
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
ll max1[maxn << 2], tag[maxn << 2];
void up(int x){
	max1[x] = max(max1[l(x)], max1[r(x)]);
}
void down(int x){
	max1[l(x)] += tag[x], tag[l(x)] += tag[x];
	max1[r(x)] += tag[x], tag[r(x)] += tag[x];
	tag[x] = 0;
}
void update(int x, int l, int r, int ql, int qr, ll k){
	if(ql <= l && r <= qr){
		max1[x] += k, tag[x] += k;
		return;
	}
	down(x);
	int mid = l + r >> 1;
	if(ql <= mid) update(l(x), l, mid, ql, qr, k);
	if(qr > mid) update(r(x), mid + 1, r, ql, qr, k);
	up(x);
}
int query1(int x, int l, int r, int ql, int qr, ll k){
	if(ql <= l && r <= qr){
		if(max1[x] <= k) return 0;
		if(l == r){
			if(max1[x] > k) return l;
			else return 0;
		}
		down(x);
		int mid = l + r >> 1;
		if(max1[l(x)] > k) return query1(l(x), l, mid, ql, qr, k);
		else return query1(r(x), mid + 1, r, ql, qr, k);
	}
	down(x);
	int mid = l + r >> 1, res = 0;
	if(ql <= mid) res = query1(l(x), l, mid, ql, qr, k);
	if(res) return res;
	if(qr > mid) res = query1(r(x), mid + 1, r, ql, qr, k);
	return res;
}
int query2(int x, int l, int r, int ql, int qr, ll k){
	if(ql <= l && r <= qr){
		if(max1[x] <= k) return 0;
		if(l == r){
			if(max1[x] > k) return l;
			else return 0;
		}
		down(x);
		int mid = l + r >> 1;
		if(max1[r(x)] > k) return query2(r(x), mid + 1, r, ql, qr, k);
		else return query2(l(x), l, mid, ql, qr, k);
	}
	down(x);
	int mid = l + r >> 1, res = 0;
	if(qr > mid) res = query2(r(x), mid + 1, r, ql, qr, k);
	if(res) return res;
	if(ql <= mid) res = query2(l(x), l, mid, ql, qr, k);
	return res;
}}
namespace seg2{
#define l(x) (x << 1)
#define r(x) (x << 1 | 1)
ll max1[maxn << 2];
void up(int x){
	max1[x] = max(max1[l(x)], max1[r(x)]);
}
void build(int x, int l, int r){
	if(l == r){
		max1[x] = a[l];
		return;
	}
	int mid = l + r >> 1;
	build(l(x), l, mid), build(r(x), mid + 1, r);
	up(x);
}
void update(int x, int l, int r, int id, ll k){
	if(l == r){
		max1[x] += k;
		return;
	}
	int mid = l + r >> 1;
	if(id <= mid) update(l(x), l, mid, id, k);
	else update(r(x), mid + 1, r, id, k);
	up(x);
}
ll query(int x, int l, int r, int ql, int qr){
	if(ql <= l && r <= qr) return max1[x];
	int mid = l + r >> 1;
	ll res = 0;
	if(ql <= mid) res = max(res, query(l(x), l, mid, ql, qr));
	if(qr > mid) res = max(res, query(r(x), mid + 1, r, ql, qr));
	return res;
}}

int main(){
	scanf("%d %d %d %d %lld %lld", &n, &q, &c1, &c2, &w1, &w2);
	for(int i = 1; i <= n; i ++) scanf("%lld", &a[i]);
	for(int i = 1; i <= n; i ++){
		upd(i, a[i]);
		seg::update(1, 1, n, max(1, i - c2 + 1), i, a[i]);
	}
	seg2::build(1, 1, n);
	while(q --){
		int op;
		scanf("%d", &op);
		if(op == 1){
			int x;
			ll y;
			scanf("%d %lld", &x, &y);
			upd(x, y);
			seg::update(1, 1, n, max(1, x - c2 + 1), x, y);
			seg2::update(1, 1, n, x, y);
			a[x] += y;
		}else{
			int l, r;
			scanf("%d %d", &l, &r);
			if(seg2::query(1, 1, n, l, r) > w1){
				printf("tetris\n");
				continue;
			}
			int L = 0, R = 0;
			if(r - l + 1 <= c2){
				if(que(r) - que(l - 1) > w2) L = l, R = r;
			}else{
				L = seg::query1(1, 1, n, l, r - c2 + 1, w2);
				R = seg::query2(1, 1, n, l, r - c2 + 1, w2) + c2 - 1;
			}
			if(!L || !R){
				printf("cont\n");
				continue;
			}
			if(que(R) - que(L - 1) <= w1 && R - L + 1 <= c1) printf("cont\n");
			else printf("tetris\n");
		}
	}
	return 0;
}
```

---

## 作者：Heptagon18 (赞：6)

## Description
[原题链接](https://www.luogu.com.cn/problem/P11219)。

[更好的浏览体验](https://www.luogu.com.cn/article/2vxyzhjt)。

-----

## Solution

首先进行一个特判，如果询问的区间中含有大于 $w_1$ 的数字，那么 youyou 无论如何都无法将这个数染色，输出 ```tetris```。

随后我们默认当前询问的部分没有大于 $w_1$ 的单个数字。

**Hint 1：对于所有子区间，除非序列总长度小于 $c_2$，否则 yy 选择长度正好为 $c_2$ 的子区间是一定不劣的。**

显然，因为所有数均非负，所以对于任意一个长度小于 $c_2$，总和大于 $w_2$ 的子区间，都有一个长度为 $c_2$，总和大于等于它的子区间将其包含。

接着，我们来思考 youyou 获胜的条件。

以下称长度为 $c_2$，总和大于 $w_2$ 的子区间为“合法区间”。也即 yy 可以操作的区间。

**Hint 2：对于序列中不在任何一个“合法区间”内的数，一定不会对答案产生影响。**

对于这些数字，youyou 可以用任意多次回合将它们染红，且 yy 无法重新将它们染蓝。而由于回合数是可视作无限的，youyou 总有时间去将这些数字染色。

接下来我们分情况讨论。

性质 $1$：对于不存在任何一个“合法区间”的序列，youyou 显然必胜。

性质 $2$：存在“合法区间”，若 youyou 可以一次性染红所有未染红的合法区间，则 youyou 必胜。

性质 $3$：存在“合法区间”，若 youyou 不可以做到一次性染红所有未染红的合法区间，则 yy 必胜。

假如满足性质 $2$，显然，yy 没有办法防的住。

下面对性质 $3$ 进行证明。

**Hint 3：yy 的最优策略是：尽量在整个数列的边缘进行染色。**

这一点很好理解，作为防守方，yy 的目的是防止 youyou 将整个序列染成红色。设所有“合法区间”中位于最左边的左端点为 $l$，最右边的右端点为 $r$。

如果满足性质 $3$，只考虑位置 $l,r$。若 youyou 每次把哪个点染了，yy 就可以跟着染。进而回到上述讨论。此时 youyou 必须重新将所有“合法区间”染色。此时进入循环，那么 youyou 必败。

那么只要 youyou 无法一次染红 $l$ 和 $r$，即 $r-l+1>c_1$ 或 $sum(l,r)>w_1$ 时，yy 必胜。

瓶颈在于求出：在 $[x,y]$ 内，满足 $\sum^{l+c_2-1}_{i =l}a_i > w_2$ 的最小 $l$ 和满足 $\sum^{r}_{i =r-c_2+1}a_i > w_2$ 的最大 $r$。

如果暴力求值，时间复杂度 $O(qn)$，不可接受，预计得分 $40$ 。

注意到 $c_2$ 恒定，因为有修改，选择线段树进行维护。以长度为 $c_2$ 的所有区间作为线段树的一个叶子结点。考虑二分。$[x,mid]$ 中是否存在 $1$，与 $[mid,y]$ 是否存在 $1$ 满足单调性。时间复杂度 $O(q\log^2 n )$。预计得分 $40\sim 70$。

可以暴力更新所有修改时受影响的区间，时间复杂度 $O(qc_2)$。预计得分 $70$。

实现线段树上二分，可以做到 $O(q \log n)$，预计得分 $100$。

特别的，在求出 $l,r$ 后，用一个树状数组即可判断 $sum(l,r)>w_1$，而开头的特判也容易使用线段树实现，总时间复杂度 $O(q \log n)$。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long

namespace fastio {
const int MAXBUF = 1 << 23;
char buf[MAXBUF], *p1 = buf, *p2 = buf;
char pbuf[MAXBUF], *pp = pbuf;
inline char getc() { return (p1 == p2) && (p2 = (p1 = buf) + fread(buf, 1, MAXBUF, stdin)), p1 == p2 ? EOF : *p1++; }
inline void putc(char c) { (pp == pbuf + MAXBUF) && (fwrite(pbuf, 1, MAXBUF, stdout), pp = pbuf), *pp++ = c; }
inline void print_final() { fwrite(pbuf, 1, pp - pbuf, stdout), pp = pbuf; }
} // namespace fastio
using fastio::getc; using fastio::putc; using fastio::print_final;
template <class _Tp>
inline _Tp& read(_Tp& x) {
  bool sign = 0;
  char ch = getc();
  for (; !isdigit(ch); ch = getc()) sign |= (ch == '-');
  for (x = 0; isdigit(ch); ch = getc()) x = x * 10 + (ch ^ 48);
  return sign ? (x = -x) : x;
}
template <class _Tp>
inline void write(_Tp x) {
  if (x > 9) write(x / 10);
  putc((x % 10) ^ 48);
}

int maxx[1200005];
int tr[300005];
int tag[1200005];
int reg[1200005];
int a[300005];

int n,q,c1,c2,w1,w2;

int lowbit(int t)
{
	return t&(-t);
}

void upd(int t,int x)
{
	while(t<=n)
	{
		tr[t]+=x;
		t+=lowbit(t);
	}
}

int ad(int t)
{
	int ans=0;
	while(t)
	{
		ans+=tr[t];
		t-=lowbit(t);
	}
	return ans;
}

void down(int p,int l,int r)
{
	if(tag[p]==0||l==r) return;
	maxx[p*2]+=tag[p];
	maxx[p*2+1]+=tag[p];
	tag[p*2]+=tag[p];
	tag[p*2+1]+=tag[p];
	tag[p]=0;
}

void update(int p,int l,int r,int nl,int nr,int u)
{
	if(nl<=l&&nr>=r)
	{
		maxx[p]+=u;
		tag[p]+=u;
		return;
	}
	down(p,l,r);
	int mid=(l+r)/2;
	if(mid>=nl) update(p*2,l,mid,nl,nr,u);
	if(mid+1<=nr) update(p*2+1,mid+1,r,nl,nr,u);
	maxx[p]=max(maxx[p*2],maxx[p*2+1]);
}

int query(int p,int l,int r,int nl,int nr)
{
	if(nl>nr) return 0;
	if(nl<=l&&nr>=r) return maxx[p];
	if(nl>r||nr<l) return 0;
	down(p,l,r);
	int mid=(l+r)/2;
	int u=0;
	if(mid>=nl) u=max(u,query(p*2,l,mid,nl,nr));
	if(mid+1<=nr) u=max(u,query(p*2+1,mid+1,r,nl,nr));
	return u;
}

void update2(int p,int l,int r,int d,int x)
{
	if(l==r)
	{
		reg[p]+=x;
		return;
	}
	int mid=(l+r)/2;
	if(d<=mid) update2(p*2,l,mid,d,x);
	else update2(p*2+1,mid+1,r,d,x);
	reg[p]=max(reg[p*2],reg[p*2+1]);
}

int query2(int p,int l,int r,int nl,int nr)
{
	if(nl<=l&&nr>=r) return reg[p];
	int mid=(l+r)/2;
	int v=0;
	if(mid>=nl) v=max(v,query2(p*2,l,mid,nl,nr));
	if(mid+1<=nr) v=max(v,query2(p*2+1,mid+1,r,nl,nr));
	return v;
}

int searchl(int p,int l,int r,int nl,int nr,int k)
{
	if(r<nl||l>nr) return 0;
    if(maxx[p]<=k) return 0;
    if(l==r) return l;
    int mid=(l+r)/2;
    down(p,l,r);
    if(nl<=l&&nr>=r)
    {
    	if(maxx[p*2]>k) return searchl(p*2,l,mid,nl,nr,k);
    	else return searchl(p*2+1,mid+1,r,nl,nr,k);
    }
    int ans=0;
    if(maxx[p*2]>k&&mid>=nl) ans=searchl(p*2,l,mid,nl,nr,k);
    if(ans) return ans;
    if(maxx[p*2+1]>k&&mid+1<=nr) return searchl(p*2+1,mid+1,r,nl,nr,k);
    else return 0;
}

int searchr(int p,int l,int r,int nl,int nr,int k)
{
	
	if(l>nr||r<nl) return 0;
    if(maxx[p]<=k) return 0;
    if(l==r) return l;
    int mid=(l+r)/2;
    down(p,l,r);
    if(nl<=l&&nr>=r)
    {
    	if(maxx[p*2+1]>k) return searchr(p*2+1,mid+1,r,nl,nr,k);
    	else return searchr(p*2,l,mid,nl,nr,k);
    }
    int ans=0;
    if(maxx[p*2+1]>k&&mid+1<=nr) ans=searchr(p*2+1,mid+1,r,nl,nr,k);
    if(ans) return ans;
    if(maxx[p*2]>k&&mid>=nl) return searchr(p*2,l,mid,nl,nr,k);
    else return 0;
}

void work(int ld,int rd)
{
	int f=query(1,1,n,ld+c2-1,rd);
	int uop=query2(1,1,n,ld,rd);
	if(uop>w1)
	{
		printf("tetris\n");
		return;
	}
	if(rd-ld+1<=c2)
	{
		f=ad(rd)-ad(ld-1);
	}
	if(w1<=w2)
	{
		if(f>w2) printf("tetris\n");
		else printf("cont\n");
		return;
	}
	if(f>w1)
	{
		printf("tetris\n");
		return;
	}
	if(f<=w2)
	{
		printf("cont\n");
		return;
	}
	if(rd-ld+1<=c2)
	{
		if(rd-ld+1<=c1)
		{
			printf("cont\n");
			return;
		}
		else
		{
			printf("tetris\n");
			return;
		}
	}
	if(c1<c2)
	{
		printf("tetris\n");
		return;
	}
	int l=ld+c2-1,r=rd;
	int ans1=searchl(1,1,n,l,r,w2);
	int ans2=searchr(1,1,n,l,r,w2);
	ans1-=c2-1;
	if(ans2-ans1+1>c1||ad(ans2)-ad(ans1-1)>w1) printf("tetris\n");
	else printf("cont\n");
}

signed main()
{
    read(n);
    read(q);
    read(c1);
    read(c2);
    read(w1);
    read(w2);
    for(int i=1;i<=n;i++)
    {
    	read(a[i]);
    	upd(i,a[i]);
    	update2(1,1,n,i,a[i]);
    }
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
    	cnt+=a[i];
    	if(i>=c2)
    	{
    		cnt-=a[i-c2];
    		update(1,1,n,i,i,cnt);
    	}
    }
    for(int i=1;i<=q;i++)
    {
    	int opt,x,y;
    	read(opt);
    	read(x);
    	read(y);
    	if(opt==1)
    	{
    		a[x]+=y;
    		upd(x,y);
    		update(1,1,n,x,min(x+c2-1,n),y);
    		update2(1,1,n,x,y);
    	}
    	else work(x,y);
    }
}
```

---

## 作者：Hoks (赞：6)

## 前言
感觉还好的题。

实现可能有点问题。
## 思路分析
发现，是一个博弈是否必败的判断。

而且给很多个区间还带修判断，感觉看着就很 DS。

进行条件的充要转换。

假设我们当前的区间是 $[l,r]$。

1. 若 $\max\limits_{i=l}^r a_i>w1$，显然是不行的，因为最大值这个点肯定不能染红啊。
2. 若 $\sum\limits_{i=l}^r a_i\le w2$，显然是可以的，因为此时 yy 无法操作。
3. 若 $\sum\limits_{i=l}^r a_i\le w1$，显然是可以的，因为 youyou 一步就可以获胜了。
4. 若 $c2>r-l+1$，显然是不可以的，因为不管 youyou 怎么操作，yy 都可以让区间立刻回到初始状态。
5. 设 yy 最远能操作的左端点为 $ll$，最远能操作的右端点为 $rr$，那么若 $\sum\limits_{i=ll}^{rr} a_i\le w1$，就是 youyou 胜，否则就是 yy 胜。

    这个稍微要考虑一下，因为 yy 的最大能操作的就是 $ll,rr$，所以 youyou 先用一些步数把这个区间外的都操作掉，最后一步操作这里就赢了。

    而如果 youyou 不能一步操作掉这个区间，那他只要给左/右边的染红了，右/左边就还是蓝色的，此时 yy 可以直接给左/右边重新染蓝，youyou 永远也无法获胜。

接着来实现上述的分讨。

$1,2,3,4$ 是平凡的，唯一的难点就是 $5$ 里的分讨，我们要处理出最左 $ll$ 和最右 $rr$。

考虑对于每个点 $i$ 维护 $[i,i+c2-1]$ 这个区间的和。

那就是找到最左的 $i$ 满足这个值比 $w2$ 大，右边同理。

这样就是一个线段树上二分的过程，可以 $\log n$ 解决。

有了这个区间 $[ll,rr]$ 后判断下能不能一步解决就行了，这也是平凡的。

最后考虑下单点改怎么解决。

单点改，对于我们维护的区间而言，就是一个区间改，差分一下改就行了。
## 代码
记得判一下初始区间合法性。
```cpp
#include<bits/stdc++.h>
#define ls (p<<1)
#define rs (ls|1)
#define mid ((l+r)>>1)
#define int long long
using namespace std;
const int N=3e5+10,V=1e5,INF=0x3f3f3f3f3f3f3f,mod=998244353;
struct BIT//binary_indexed_tree
{
    int c[N],n;BIT(){memset(c,0,sizeof c);}
    void modify(int x,int v){for(;x<=n;x+=x&-x) c[x]+=v;}
    int query(int x){int res=0;for(;x;x-=x&-x) res+=c[x];return res;}
    void mdf(int l,int r,int v){modify(l,v),modify(r+1,-v);}
    int qry(int l,int r){return query(r)-query(l-1);}
}tt;
int n,m,q,c1,c2,w1,w2,a[N],b[N],mx[N<<2],t[N<<2],lz[N<<2];
namespace Fast_IO
{
	static char buf[1000000],*paa=buf,*pd=buf,ot[10000000];int length=0;
	#define getchar() (paa==pd)&&(paa=(pd=buf)+fread(buf,1,1000000,stdin),paa==pd)?EOF:*pd++
	inline int read()
	{
		char c(getchar());int x=0,t=1;
		while(!isdigit(c)){if(c=='-') t=-1;c=getchar();}
		while(isdigit(c)) x=(x<<1)+(x<<3)+(c^48),c=getchar();
		return x*t;
	}
	inline void flush(){fwrite(ot,1,length,stdout);length=0;}
	inline void put(char c){ot[length++]=c;}
	inline void put(string s){for(char c:s) put(c);}
	inline void print(int x)
	{
		if(x<0) put('-'),x=-x;
		if(x>9) print(x/10);
		put(x%10+'0');
	}
	inline bool chk(char c){return !(c>='a'&&c<='z'||c>='A'&&c<='Z'||c>='0'&&c<='9'||c=='<'&&c=='>');}
	inline bool ck(char c){return c!=' '&&c!='\n'&&c!='\r'&&c!=EOF;}
	inline void rd(char s[],int&n)
	{
		s[n]=getchar();
		while(chk(s[n])) s[n]=getchar();
		while(ck(s[n])) s[++n]=getchar();n--;
	}
}
using namespace Fast_IO;
inline void build(int p,int l,int r)
{
	if(l==r) return t[p]=a[l],void();
	build(ls,l,mid);build(rs,mid+1,r);t[p]=max(t[ls],t[rs]);
}
inline void modify(int p,int l,int r,int x,int w)
{
	if(l==r) return t[p]+=w,void();
	(mid>=x)?(modify(ls,l,mid,x,w)):(modify(rs,mid+1,r,x,w));
	t[p]=max(t[ls],t[rs]);
}
inline int query(int p,int l,int r,int s,int e)
{
	if(l>=s&&r<=e) return t[p];int res=0;
	if(mid>=s) res=query(ls,l,mid,s,e);
	if(mid<e) res=max(res,query(rs,mid+1,r,s,e));
	return res;
}
inline void bld(int p,int l,int r)
{
	if(l==r) return mx[p]=b[l+c2-1]-b[l-1],void();
	bld(ls,l,mid);bld(rs,mid+1,r);mx[p]=max(mx[ls],mx[rs]);
}
inline void pushson(int p,int w){mx[p]+=w;lz[p]+=w;}
inline void pushdown(int p){pushson(ls,lz[p]);pushson(rs,lz[p]);lz[p]=0;}
inline void modify(int p,int l,int r,int s,int e,int w)
{
	if(l>=s&&r<=e) return pushson(p,w);pushdown(p);
	if(mid>=s) modify(ls,l,mid,s,e,w);
	if(mid<e) modify(rs,mid+1,r,s,e,w);
	mx[p]=max(mx[ls],mx[rs]);
}
inline int getl(int p,int l,int r,int s,int e)
{
	if(l>e||r<s||mx[p]<=w2) return INF;if(l==r) return l;
	int w=0;pushdown(p);w=getl(ls,l,mid,s,e);
	if(w==INF) return getl(rs,mid+1,r,s,e);return w;
}
inline int getr(int p,int l,int r,int s,int e)
{
	if(l>e||r<s||mx[p]<=w2) return INF;if(l==r) return l;
	int w=0;pushdown(p);w=getr(rs,mid+1,r,s,e);
	if(w==INF) return getr(ls,l,mid,s,e);return w;
}
signed main()
{
	tt.n=n=read(),q=read(),c1=read(),c2=read(),w1=read(),w2=read();
	for(int i=1;i<=n;i++) b[i]=b[i-1]+(a[i]=read()),tt.modify(i,a[i]);
	build(1,1,n);bld(1,1,m=max(1ll,n-c2+1));
	for(int i=1,op,l,r;i<=q;i++)
	{
		op=read(),l=read(),r=read();
		if(op==1)
		{
			tt.modify(l,r);modify(1,1,n,l,r);
			modify(1,1,m,max(1ll,l-c2+1),min(m,l),r);continue;
		}if(query(1,1,n,l,r)>w1){put("tetris\n");continue;}
		int w=tt.qry(l,r),len=r-l+1;
		if(w<=w2){put("cont\n");continue;}
		if(w<=w1&&len<=c1){put("cont\n");continue;}
		if(len<=c2){put("tetris\n");continue;}
		int L=getl(1,1,m,l,r-c2+1),R=getr(1,1,m,l,r-c2+1);
		if(L==INF||R==INF){put("cont\n");continue;}
		put((tt.qry(L,R+c2-1)>w1||R+c2-L>c1)?"tetris\n":"cont\n");
	}
	genshin:;flush();return 0;
}
```

---

## 作者：Corzica (赞：3)

先考虑对于固定的一个序列的情况。

我们可以观察得到一个结论：yy 只会操作最左侧的符合条件的区间和最右侧的符合条件的区间。这个结论其实不难理解，yy 肯定希望场上尽可能多的存在蓝色，分开来能尽可能减少一次染红带来的损失。

那么，我们就不难想到怎么判定胜负。**yy 能赢当且仅当最左侧的能被操作到的点和最右侧的能被操作到的点所形成的区间不能被一次染成红色或者存在一个数无法被染红**。

有数字无法被染红时的结论显然，下面假定所有数字均能被一次操作染红。

接下来会给出剩余部分的证明。

充分性：因为 yoyo 的一次操作不能覆盖这个最大区间，所以一次操作至多会让两个端点中的一个被覆盖，我们只需要把那个端点染回来即可，这样 yoyo 始终无法染成全红，即 yy 赢。

必要性：如果一次操作能够覆盖这个最大区间，那么 yoyo 可以先将最大区间外的数字全部染完，然后用一次操作把这个最大区间染红。

有了这个结论之后就很好做了，只需要在线段树上维护区间最大值用来判断有没有数字无法被染，维护每一个长度为 $c_2$ 的区间和，询问时二分得到最左侧和最右侧符合条件的点。如果区间长度小于 $c_2$，只需判断能否一次染红和一次染蓝，所以还要维护区间和。

时间复杂度 $O(n\log n)$。

代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
long long a[400005], sum[400005];
struct SGT {
	struct node {
		int l, r;
		long long sum, maxn;
	} b[1200005];
	inline void update(int p) {
		b[p].sum = b[2 * p].sum + b[2 * p + 1].sum;
		b[p].maxn = max(b[2 * p].maxn, b[2 * p + 1].maxn);
	}
	inline void build(int p, int l, int r) {
		b[p].l = l, b[p].r = r;
		if (l == r) {
			b[p].maxn = b[p].sum = a[l];
			return;
		}
		build(2 * p, l, (l + r) >> 1);
		build(2 * p + 1, ((l + r) >> 1) + 1, r);
		update(p);
	}
	inline void change(int p, int q, long long w) {
		if (b[p].l == b[p].r) {
			b[p].sum = b[p].maxn = w;
			return;
		}
		if (q <= ((b[p].l + b[p].r) >> 1)) change(2 * p, q, w);
		else change(2 * p + 1, q, w);
		update(p);
	}
	inline long long querysum(int p, int l, int r) {
		if (b[p].l >= l && b[p].r <= r) return b[p].sum;
		int mid = (b[p].l + b[p].r) >> 1;
		long long cnt = 0;
		if (l <= mid) cnt += querysum(2 * p, l, r);
		if (r > mid) cnt += querysum(2 * p + 1, l, r);
		return cnt;
	}
	inline long long querymax(int p, int l, int r) {
		if (b[p].l >= l && b[p].r <= r) return b[p].maxn;
		int mid = (b[p].l + b[p].r) >> 1;
		long long cnt = 0;
		if (l <= mid) cnt = querymax(2 * p, l, r);
		if (r > mid) cnt = max(cnt, querymax(2 * p + 1, l, r));
		return cnt;
	}
} t;
int c, w, cc, ww;
struct SGTS {
	struct node {
		int l, r;
		long long tag, maxn;
	} b[1200005];
	inline void ads(int p, long long q) {
		b[p].tag += q, b[p].maxn += q;
	}
	inline void push_down(int p) {
		if (b[p].tag) {
			ads(2 * p, b[p].tag), ads(2 * p + 1, b[p].tag);
			b[p].tag = 0;
		}
	}
	inline void update(int p) {
		b[p].maxn = max(b[2 * p].maxn, b[2 * p + 1].maxn);
	}
	inline void build(int p, int l, int r) {
		b[p].l = l, b[p].r = r;
		if (l == r) {
			b[p].maxn = sum[l + cc - 1] - sum[l - 1];
			return;
		}
		build(2 * p, l, (l + r) >> 1);
		build(2 * p + 1, ((l + r) >> 1) + 1, r);
		update(p);
	}
	inline void change(int p, int l, int r, long long w) {
		if (b[p].l >= l && b[p].r <= r) {
			ads(p, w);
			return;
		}
		push_down(p);
		int mid = (b[p].l + b[p].r) >> 1;
		if (l <= mid) change(2 * p, l, r, w);
		if (r > mid) change(2 * p + 1, l, r, w);
		update(p);
	}
	inline int queryl(int p, int l, int r) {
		if (b[p].maxn < ww) return b[p].r + 1;
		if (b[p].l == b[p].r) return b[p].r;
		push_down(p);
		if (b[p].l >= l && b[p].r <= r) {
			if (b[2 * p].maxn >= ww) return queryl(2 * p, l, r);
			return queryl(2 * p + 1, l, r);
		}
		int mid = (b[p].l + b[p].r) >> 1;
		if (r <= mid) return queryl(2 * p, l, r);
		if (l > mid) return queryl(2 * p + 1, l, r);
		int op = queryl(2 * p, l, mid);
		if (op == mid + 1) return queryl(2 * p + 1, mid + 1, r);
		return op;
	}
	inline int queryr(int p, int l, int r) {
		if (b[p].maxn < ww) return b[p].l - 1;
		if (b[p].l == b[p].r) return b[p].r;
		push_down(p);
		if (b[p].l >= l && b[p].r <= r) {
			if (b[2 * p + 1].maxn >= ww) return queryr(2 * p + 1, l, r);
			return queryr(2 * p, l, r);
		}
		int mid = (b[p].l + b[p].r) >> 1;
		if (r <= mid) return queryr(2 * p, l, r);
		if (l > mid) return queryr(2 * p + 1, l, r);
		int op = queryr(2 * p + 1, mid + 1, r);
		if (op == mid) return queryr(2 * p, l, mid);
		return op;
	}
} tt;
int n, m;
signed main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m >> c >> cc >> w >> ww;
	c = min(c, n), cc = min(cc, n);
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
		sum[i] = sum[i - 1] + a[i];
	}
	int op, p, q;
	t.build(1, 1, n);
	tt.build(1, 1, n - cc + 1);
	for (int i = 1; i <= m; i++) {
		cin >> op;
		if (op == 1) {
			cin >> p >> q;
			a[p] += q;
			t.change(1, p, a[p]);
			tt.change(1, max(p - cc + 1, 1), min(p, n - cc + 1), q);
		} else {
			cin >> p >> q;
			if (t.querymax(1, p, q) > w) {
				cout << "tetris\n";
			} else {
				if (q - p + 1 < cc) {
					if (t.querysum(1, p, q) < ww) {
						cout << "cont\n";
					} else if (q - p + 1 <= c && t.querysum(1, p, q) <= w) {
						cout << "cont\n";
					} else {
						cout << "tetris\n";
					}
				} else {
					int ops = tt.queryl(1, p, q - cc + 1), opp = tt.queryr(1, p, q - cc + 1);
					if (ops > opp) {
						cout << "cont\n";
					} else {
						opp += cc - 1;
						if (opp - ops + 1 <= c && t.querysum(1, ops, opp) <= w) {
							cout << "cont\n";
						} else {
							cout << "tetris\n";
						}
					}
				}
			}
		}
	}
}
```

---

## 作者：FlyPancake (赞：2)

### [P11219 【MX-S4-T3】「yyOI R2」youyou 的序列 II](https://www.luogu.com.cn/problem/P11219) 题解

首先，如果 $\max{a_i} > w_1$，则 youyou 无论如何都无法染完全部点。

接下来我们分析博弈的部分：

- 因为 $a_i \ge 0$，所以 yy 每次操作都会尽量染 $c_2$ 的长度，否则特地分开多次染肯定不优。

- yy 不能染色到的区间，youyou 至少肯定能一个一个地染完。

- yy 能染色到的最大区间 youyou 如果不能一次染完则无法获胜。
    证明：可以将此区间看成左右两部分。如果 youyou 先染了左边部分，则 yy 可以把左边部分染回来，右边部分同理。

也就是说，**youyou 能获胜当且仅当询问区间 yy 染不了或者该区间内 yy 能染的最大区间 youyou 能一次染完**。

问题在于如何找到 yy 能染色到的最大区间的左右端点 $L, R$。

两端点需要分别满足 $\sum\limits_{i=L}^{L+c_2-1} a_i > w_2$ 和 $\sum\limits_{i=R-c_2+1}^{R} a_i > w_2$。

当我们遇到需要查找一类合法区间或者是利用线段树的性质去找第一个合法点或者最后一个合法点的时候，一般就需要线段树二分来解决这些问题了。此题中因为 $c_2$ 是定值，可以将线段树的节点 $i$ 的权值当作 $\sum\limits_{k = i}^{i+c_2-1} a_k$，这样就将查询转化成了区间最大值，需要找到最左/右侧权值大于 $w_2$ 的点。此时单点修改位置 $x$ 相当于区间修改 $[x-c_2+1, x]$。

最后考虑询问区间 $[x,y]$：

- 如果 $y-x+1<c_2$，那么直接判断该区间权值和是否 $ \le w_2$ 或者 $y-x+1 \le c_1$ 且区间权值和 $\le w_1$。

- 否则找到 $L, R$。若找不到则说明 yy 不能染。否则使 $R \leftarrow R+c_2-1$ 转化到原区间。判断是否 $R-L+1 \le c_1$ 且原区间 $[L, R]$ 权值和 $\le w_1$。

因为同时需要原区间的区间最大值和权值和，所以一共需要维护两个线段树。实现时注意边界。

---

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
constexpr int N = 3e5+5;
#define pll pair<ll, ll>
#define fi first
#define se second

int a[N], pre[N];
int n, q, c1, c2, w1, w2;

struct segtree{
    ll sum[N<<2], mx[N<<2], tag[N<<2];
    #define ls (x<<1)
    #define rs (x<<1|1)
    void pushdown(int x, int l, int r){
        if(!tag[x]) return;
        int mid = (l+r)>>1;
        sum[ls] += tag[x]*(mid-l+1), sum[rs] += tag[x]*(r-mid);
        mx[ls] += tag[x], mx[rs] += tag[x];
        tag[ls] += tag[x], tag[rs] += tag[x];
        tag[x] = 0;
    }
    void pushup(int x){
        sum[x] = sum[ls]+sum[rs];
        mx[x] = max(mx[ls], mx[rs]);
    }
    void build(int x, int l, int r, bool op){
        tag[x] = 0;
        if(l==r && op==0){
            sum[x] = mx[x] = a[l];
            return;
        }
        if(l==r && op==1){
            sum[x] = mx[x] = pre[l+c2-1]-pre[l-1];
            return;
        }
        int mid = (l+r)>>1;
        build(ls, l, mid, op);
        build(rs, mid+1, r, op);
        pushup(x);
    }
    void update(int x, int l, int r, int ql, int qr, ll v){
        if(l>=ql && r<=qr){
            sum[x] += (r-l+1)*v;
            tag[x] += v; mx[x] += v;
            return;
        }
        int mid = (l+r)>>1;
        pushdown(x, l, r);
        if(ql<=mid) update(ls, l, mid, ql, qr, v);
        if(qr>mid) update(rs, mid+1, r, ql, qr, v);
        pushup(x);
    }
    pll querys(int x, int l, int r, int ql, int qr){
        if(l>=ql && r<=qr)
            return {sum[x], mx[x]};
        int mid = (l+r)>>1; pll res = {0, 0};
        pushdown(x, l, r);
        if(ql<=mid){
            pll tmp = querys(ls, l, mid, ql, qr);
            res = {res.fi+tmp.fi, max(res.se, tmp.se)};
        }
        if(qr>mid){
            pll tmp = querys(rs, mid+1, r, ql, qr);
            res = {res.fi+tmp.fi, max(res.se, tmp.se)};
        }
        return res;
    }
    int getl(int x, int l, int r, int ql, int qr, ll k){
        if(l>=ql && r<=qr){
            if(mx[x]<=k) return -1;
            if(l==r) return l;
            int mid = (l+r)>>1;
            pushdown(x, l, r);
            if(mx[ls]>k) return getl(ls, l, mid, ql, qr, k);
            else return getl(rs, mid+1, r, ql, qr, k);
        }
        int mid = (l+r)>>1, res = -1;
        pushdown(x, l, r);
        if(ql<=mid && mx[ls]>k) res = getl(ls, l, mid, ql, qr, k);
        if(qr>mid && res==-1 && mx[rs]>k) res = getl(rs, mid+1, r, ql, qr, k);
        return res;
    }
    int getr(int x, int l, int r, int ql, int qr, ll k){
        if(l>=ql && r<=qr){
            if(mx[x]<=k) return -1;
            if(l==r) return l;
            int mid = (l+r)>>1;
            pushdown(x, l, r);
            if(mx[rs]>k) return getr(rs, mid+1, r, ql, qr, k);
            else return getr(ls, l, mid, ql, qr, k);
        }
        int mid = (l+r)>>1, res = -1;
        pushdown(x, l, r);
        if(qr>mid && mx[rs]>k) res = getr(rs, mid+1, r, ql, qr, k);
        if(ql<=mid && res==-1 && mx[ls]>k) res = getr(ls, l, mid, ql, qr, k);
        return res;
    }
}tr, extr;

int main(){
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin>>n>>q>>c1>>c2>>w1>>w2;
    for(int i=1; i<=n; i++){
        cin>>a[i];
        pre[i] = pre[i-1]+a[i];
    }
    int m = max(n-c2+1, n);
    tr.build(1, 1, n, 0);
    extr.build(1, 1, m, 1);
    while(q--){
        int op, x, y; cin>>op>>x>>y;
        if(op==1){
            tr.update(1, 1, n, x, x, y);
            extr.update(1, 1, m, max(1, x-c2+1), min(x, m), y);
        } else{
            pll res = tr.querys(1, 1, n, x, y);
            if(res.se > w1){
                cout<<"tetris\n";
                continue;
            }
            if(y-x+1 < c2){
                if((res.fi<=w2) || (y-x+1<=c1 && res.fi<=w1)){
                    cout<<"cont\n";
                    // 如果 yy 不能染，那么 youyou 一定可以一个一个染
                    // 或者 youyou 能一次染完，否则相当于两边 yy 必有一边可染
                } else{
                    cout<<"tetris\n";
                }
                continue;
            }
            int L = extr.getl(1, 1, m, x, y-c2+1, w2), R = extr.getr(1, 1, m, x, y-c2+1, w2);
            if(L==-1 || R==-1){
                cout<<"cont\n";
            } else if(R+c2-1-L+1<=c1 && tr.querys(1, 1, n, L, R+c2-1).fi<=w1){
                cout<<"cont\n";
            } else{
                cout<<"tetris\n";
            }
        }
    }
    return 0;
}
```

---

## 作者：caibet (赞：2)

[tp](https://www.luogu.com.cn/problem/P11219)

考时+考后总共写了 150+ 行的无用代码，被自己菜晕了。

为了方便我们认为题目是 A 和 B 在进行操作（对应 $c_1,w_1$ 和 $c_2,w_2$），A 的操作将区间内的数打上标记而 B 把区间内数的标记去除。

先考虑不带修改的情况。首先观察到 A 在 B 之前操作，则 A 做完操作之后 B 可能可以立刻将其中的一部分标记清除。那有没有某些位置的标记是永远无法被 B 清除的呢？答案是肯定的，我们不妨考察一个位置 $i$ 能被打标记但不能被清除的条件：

- 能被打标记：只考虑这个位置，A 操作区间尽量短显然是不劣的（即区间长为 $1$ 和为 $a_i$），则有条件 $\bold{a_i\le w_1}$。
- 不能被清除：此时 B 操作区间尽量长显然是不劣的。则有条件 **不存在一个长为 $\min(n,c_2)$ 的区间使得总和 $> w_2$ 且包含了位置 $i$**。

然而注意到如果存在 $a_i>w_1$ 则这个点永远打不了标记，我们特判掉这种情况，此后一个点不能被 B 操作到就是满足条件的。

那么 A 当然可以先把这些点打上标记。之后剩下一些点，A 给剩下的点打标记时有些会被 B 清掉。怎么样才能让 B 来不及清掉呢？

可以想到一个很容易让 B 清不掉的条件：A 能操作一个区间使得所有剩下的点被覆盖（这之后全部的点有标记，游戏直接结算了）。对于更弱的情况是否能做到呢？

**结论**：当且仅当 A 能操作一个区间使得所有剩下的点被覆盖时才能胜利。

**证明**：充分性显然。如果不能一次操作全部覆盖，我们考虑 B 的所有最优合法（即长为 $\min(n,c_2)$，总和 $> w_2$）操作区间，显然覆盖所有剩下的点就是覆盖这些区间。我们取其中最左边和最右边的区间，由于 A 不能一次全部覆盖，一次最多只能完全覆盖最左边和最右边中的一个，B 只要把被覆盖的那个区间的标记删除即可，此后又会回到最左边和最右边的区间都未被打标记的情况。只有一个区间也同理。

于是思路就明朗了。对于无修改的情况，我们可以先确保每个 $a_i\le w_1$，然后求出 B 当前的所有最优合法操作区间，检视 A 覆盖所有 B 操作区间需要的最小区间，检查区间是否合法即可。这会就可以做 $O(n^2)$ 了。

考虑优化。判断所有 $a_i\le w_1$ 是简单的，方法很多。至于求询问区间中的 B 的操作区间，由于单个数据内可能的长为 $c_2$ 的区间只有 $O(n)$ 个，排序后单点修改对其贡献是连续的，且在 $O(\log n)$ 的复杂度内找到一个符合条件的区间并加入复杂度是正确的，可以用线段树维护。我们把符合条件的区间加入一个 set，对于一个询问二分找出符合条件的区间有哪些即可。注意询问区间长度不足 $c_2$ 时 B 一次操作长度不能达到 $c_2$，需要特判！这样就知道了 B 能操作的区间的范围，用树状数组求和判断 A 能否操作这个范围即可。

复杂度 $O(n\log n)$。

```cpp
namespace{
//
const int N=3e5+3;
int n,m,num2;
ll c1,c2,w1,w2,a[N];
// st: B 能操作的区间的左端点的集合
// st2: 满足 ai > w1 的 i 的集合
set<int> st,st2;
struct bit{
	ll c[N];
	void write(int x,ll k){
		for(;x<=n;x+=x&-x) c[x]+=k;
	}
	ll query(int x,ll res=0){
		for(;x;x&=x-1) res+=c[x];
		return res;
	}
} T;
ll b[N];
struct seg2{// (max, +)
	struct node{
		ll v,lz;
	} t[N<<2];
	inline void pushup(int f){
		t[f].v=max(t[f<<1].v,t[f<<1|1].v);
	}
	inline void pend(int f,ll k){
		t[f].v+=k;t[f].lz+=k;
	}
	inline void pushdown(int f){
		if(t[f].lz){
			pend(f<<1,t[f].lz);pend(f<<1|1,t[f].lz);
			t[f].lz=0;
		}
	}
	void build(int f,int l,int r){
		if(l==r){
			t[f].v=b[l];
			return;
		}
		int mid=l+r>>1;
		build(f<<1,l,mid);build(f<<1|1,mid+1,r);
		pushup(f);
	}
	void write(int f,int l,int r,int x,int y,ll k){
		if(x<=l&&r<=y) return pend(f,k);
		pushdown(f);
		int mid=l+r>>1;
		if(x<=mid) write(f<<1,l,mid,x,y,k);
		if(y>mid) write(f<<1|1,mid+1,r,x,y,k);
		pushup(f);
	}
	int maxpos(int f,int l,int r){
		if(l==r) return l;
		pushdown(f);
		int mid=l+r>>1;
		if(t[f<<1].v==t[f].v) return maxpos(f<<1,l,mid);
		return maxpos(f<<1|1,mid+1,r);
	}
} T2;
void upd(){
	while(T2.t[1].v>w2){
		int p=T2.maxpos(1,1,num2);
		// 找到这个区间后将其值减去无穷也就是删除
		// 单次查找 O(log n)，区间共 O(n) 个
		T2.write(1,1,num2,p,p,-lnf);
		st.insert(p);
	}
}
void work(){
	n=read();m=read();c1=read();c2=read();w1=read();w2=read();
	c2=min(c2,1ll*n);
	num2=n-c2+1;
	F(i,1,<=n){
		a[i]=read();T.write(i,a[i]);
		if(a[i]>w1) st2.insert(i);
	}
	F(i,1,<=c2) b[1]+=a[i];
	// 计算每个区间的区间和
	F(i,2,<=num2) b[i]=b[i-1]-a[i-1]+a[c2-1+i];
	T2.build(1,1,num2);
	upd();
	F(i,1,<=m){
		int op=read(),x=read(),y=read();
		if(op==1){
			a[x]+=y;
			T.write(x,y);
			if(a[x]>w1) st2.insert(x);
			int l2=max(1ll,x-c2+1),r2=min(num2,x);
			T2.write(1,1,num2,l2,r2,y);
			upd();
		}else{
			auto it=st2.lower_bound(x);
			if(it!=st2.end()&&*it<=y){
				puts("tetris");continue;
			}
			int l=n+1,r=0;
			if(y-x+1>=c2){
				auto il=st.lower_bound(x),ir=st.upper_bound(y-c2+1);
				if(il!=ir){
					--ir;
					l=*il;r=*ir+c2-1;
				} 
			}else{
				if(T.query(y)-T.query(x-1)>w2) l=x,r=y;
			}
			bool b=0;
			if(l>r) b=1;
			else if(r-l+1<=c1&&T.query(r)-T.query(l-1)<=w1) b=1;
			else b=0;
			puts(b?"cont":"tetris");
		}
	}
}
}
```

---

## 作者：dengjunhaodejia09 (赞：1)

这道题首先你可以先把所有的 yy 能涂色的区间找到，此时你会发现这些区间的最左边的左端点到最右边的右端点若 youyou 能一次性读完，即是 youyou 胜，否则 yy 胜。这是为什么呢？让我们来证明一下。

首先，我们判掉区间最大值大于 w1 的情况，若 youyou 此时能一次全部涂红，那 youyou 可以先把除了这个区间以外的所有位置全涂红，再把这个区间涂红。如果 youyou 一次不能涂完这个区间，那 yy 可以反复涂边界上的区间，这样 youyou 便不能涂完这个区间了，那么 yy 获胜。

接下来只需要话区间为单点，改单点修改为区间修改，再线段树二分找的这个区间即可。注意要特判几种情况。


```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
struct node{
    int tree[1919810],vis[1919810];
    void push_down(int id,int l,int r){
        int mid=(l+r)/2;
        tree[id*2]+=vis[id];
        tree[id*2+1]+=vis[id];
        vis[id*2]+=vis[id];
        vis[id*2+1]+=vis[id];
        vis[id]=0;
    }
    void push_up(int id){
        tree[id]=max(tree[id*2],tree[id*2+1]);
    }
    void change(int id,int l,int r,int L,int R,int W){
        if(L<=l && r<=R){
            tree[id]+=W;
            vis[id]+=W;
            return;
        }
        push_down(id,l,r);
        int mid=(l+r)/2;
        if(R<=mid){
            change(id*2,l,mid,L,R,W);
        }else if(L>mid){
            change(id*2+1,mid+1,r,L,R,W);
        }else{
            change(id*2,l,mid,L,R,W);
            change(id*2+1,mid+1,r,L,R,W);
        }
        push_up(id);
    }
    int query(int id,int l,int r,int L,int R){
        if(L<=l && r<=R){
            return tree[id];
        }
        push_down(id,l,r);
        int mid=(l+r)/2;
        if(R<=mid){
            return query(id*2,l,mid,L,R);
        }else if(L>mid){
            return query(id*2+1,mid+1,r,L,R);
        }else{
            return max(query(id*2,l,mid,L,R),query(id*2+1,mid+1,r,L,R));
        }
    }
    int mid_query_r(int id,int l,int r,int L,int R,int ans){
        if(L<=l && r<=R){
            if(tree[id]<=ans){
                return -1;
            }
        }
        if(l==r){
            return 1;
        }
        push_down(id,l,r);
        int mid=(l+r)/2;
        if(R<=mid){
            return mid_query_r(id*2,l,mid,L,R,ans);
        }else if(L>mid){
            int ansa=mid_query_r(id*2+1,mid+1,r,L,R,ans);
            if(ansa==-1){
                return -1;
            }
            return mid-l+1+ansa;
        }else {
            int Ans=mid_query_r(id*2+1,mid+1,r,L,R,ans);
            if(Ans==-1){
                return mid_query_r(id*2,l,mid,L,R,ans);
            }
            return mid-l+1+Ans;
        }
    }
    int mid_query_l(int id,int l,int r,int L,int R,int ans){
        // cout<<l<<' '<<r<<' '<<L<<" "<<R<<' '<<tree[id]<<"\n";
        if(L<=l && r<=R){
            if(tree[id]<=ans){
                return -1;
            }
        }
            // cout<<"\n"<<"SS "<<l<<' '<<r<<' '<<L<<" "<<R<<' '<<tree[id]<<'\n';
        if(l==r){
            return 1;
        }
        push_down(id,l,r);
        int mid=(l+r)/2;
        if(R<=mid){
            return mid_query_l(id*2,l,mid,L,R,ans);
        }else if(L>mid){
            int ansa=mid_query_l(id*2+1,mid+1,r,L,R,ans);
            if(ansa==-1){
                return -1;
            }
            return mid-l+1+ansa;
        }else {
            int Ans=mid_query_l(id*2,l,mid,L,R,ans);
            if(Ans==-1){
                int ansa=mid_query_l(id*2+1,mid+1,r,L,R,ans);
                if(ansa==-1){
                    return -1;
                }
                return mid-l+1+ansa;
            }
            return Ans;
        }
        
    }
}Tree_l;
struct nodea{
    int tree[1919810],vis[1919810],M=1;
    void build(int n){
        while(M<n+2){
            M<<=1;
        }
    }
    void insert(int id,int W){
        int idl=id+M;
        while(idl){
            tree[idl]+=W;
            idl>>=1;
        }
    }
    int query(int L,int R){
        int l=L+M-1,r=R+M+1,ans=0;
        for(;(l>>1)!=(r>>1);l>>=1,r>>=1){
            if(!(l&1)){
                ans+=tree[l^1];
            }
            if(r&1){
                ans+=tree[r^1];
            }
        }
        return ans;
    }
}Tree;
struct nodeb{
    int tree[1919810],vis[1919810],M=1;
    void build(int n){
        while(M<n+2){
            M<<=1;
        }
    }
    void insert(int id,int W){
        int idl=id+M;
        tree[id+M]+=W;
        while(idl){
            tree[idl]=max(tree[id+M],tree[idl]);
            idl>>=1;
        }
    }
    int query(int L,int R){
        int l=L+M-1,r=R+M+1,ans=0;
        for(;(l>>1)!=(r>>1);l>>=1,r>>=1){
            if(!(l&1)){
                ans=max(ans,tree[l^1]);
            }
            if(r&1){
                ans=max(ans,tree[r^1]);
            }
        }
        return ans;
    }
}Tree_M;
int read(){
    int ch=getchar(),x=0,f=1;
    for(;!isdigit(ch);ch=getchar())f=(ch=='-'?-1:1);
    for(;isdigit(ch);ch=getchar())x=(x<<1)+(x<<3)+(ch^48);
    return x*f;
}
int a[1919810];
signed main(){
    int n,q,cx,cy,wx,wy;
    n=read();
    q=read();
    cx=read();
    cy=read();
    wx=read();
    wy=read();
    Tree.build(n);
    Tree_M.build(n);
    for(int i=1;i<=n;i++){
        a[i]=read();
        Tree.insert(i,a[i]);
        Tree_M.insert(i,a[i]);
    }
    int Sum=0,l=1,r=0;
    for(int i=1;i<=n;i++){
        r++;
        Sum+=a[r];
        if(r-l+1>cy){
            Sum-=a[l];
            l++;
        }
        if(r-l+1==cy){
            Tree_l.change(1,1,n,l,l,Sum);
        }
    }
    int cnt=0;
    for(int i=1;i<=q;i++){
        int opt=read(),l=read(),r=read();
        if(opt==1){
            Tree_l.change(1,1,n,max(1ll,l-cy+1),l,r);
            Tree.insert(l,r);
            Tree_M.insert(l,r);
        }else{
                cnt++;
                // cout<<cnt<<'\n';
                // cout<<wy<<'\n';
            if(Tree_M.query(l,r)>wx){
                cout<<"tetris\n";
                continue;
            }
            if(r-l+1<=cx && Tree.query(l,r)<=wx){
                cout<<"cont\n";
                continue;
            }
            if(r-l+1<=cy){
                if(Tree.query(l,r)>wy){
                    cout<<"tetris\n";
                }else{
                    cout<<"cont\n";
                }
            }else{
                // cout<<l<<' '<<r<<"\n";
                if(Tree_l.query(1,1,n,l,r-cy+1)<=wy){
                    cout<<"cont\n";
                    continue;
                }
                int L=Tree_l.mid_query_l(1,1,n,l,r-cy+1,wy),R=-1+cy+Tree_l.mid_query_r(1,1,n,l,r-cy+1,wy);
                // cout<<L<<' '<<R<<' '<<l<<' '<<r-cy+1<<"\n";
                // cout<<Tree_l.query(1,1,n,1,1)<<"\n";
                if(R-L+1<=cx && Tree.query(L,R)<=wx){
                    cout<<"cont\n";
                }else{
                    cout<<"tetris\n";
                }
            }
        }
    }
    return 0;
}
```

---

## 作者：Genius_Star (赞：1)

场上没看这题，亏大了呜呜呜。

### 思路：

因为 $a$ 序列中都是非负数，则对于 `yy` 来说，肯定是能选多长就选多长。

则定义一个点 $i$ 是合法的当且仅当区间 $[i,i + c_2 - 1]$ 的和是 $>w_2$ 的（即 `yy` 能染蓝），定义 $\sum(l,r),\max(l,r)$ 表示区间的和，最大值。 

对于一个询问 $[l,r]$，先进行分类讨论。

若 $r - l + 1 < c_2$：

- 若 `youyou` 能一次全部染红当且仅当 $r - l + 1 \le c_1$ 且 $\sum(l,r) \le w_1$ 的，此时 `youyou` 显然胜利。
- 否则，若 $\sum(l,r) > w_2$ 的，那么 `yy` 能一次全部染蓝，故每次 `youyou` 操作完后，`yy` 都可以将其覆盖掉，则 `youyou` 不可能胜利。
- 否则若 $\sum(l,r) \le w_2$，此时 `yy` 无法进行任何操作，故只要 $\max(l,r) \le w_1$，`youyou` 就能在有限次数内全部染红获得胜利。

对于 $r - l + 1 \ge c_2$ 的情况，设区间 $[l,r]$ 中最近的合法点是 $i$，最远的合法点是 $j$，那么 `yy` 可以选择在 $[i, i + c_2 - 1],[j, j + c_2  - 1]$ 进行染色。

那么若 `youyou` 无法一次性将 $[i, j + c_2 - 1]$ 进行染色，则肯定无法胜利；因为若 `youyou` 刚染了左/右边，`yy` 就可以将左/右边重新染蓝，这样就会无限进行下去。

现在问题变为找到最近的合法点 $i$ 和最远的合法点 $j$，暴力找最坏是 $O(nq)$ 的，实现好的话可以得到 80pts，考虑继续优化。

令每个点 $i$ 的权值为 $\sum(i,i + c_2 - 1)$，使用线段树维护区间权值最大值，此时就可以在线段树上二分了；则题目中的单点修改就变为了区间修改。

时间复杂度为 $O(q \log n)$。

### 完整代码：

```cpp
#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/hash_policy.hpp>
#define Add(x,y) (x+y>=mod)?(x+y-mod):(x+y)
#define lowbit(x) x&(-x)
#define pi pair<ll,ll>
#define pii pair<ll,pair<ll,ll>>
#define iip pair<pair<ll,ll>,ll>
#define ppii pair<pair<ll,ll>,pair<ll,ll>>
#define fi first
#define se second
#define full(l,r,x) for(auto it = l; it != r; ++it) (*it)=x
#define Full(a) memset(a, 0, sizeof(a))
#define open(s1,s2) freopen(s1, "r", stdin), freopen(s2, "w", stdout);
#define For(i,l,r) for(register int i = l; i <= r; ++i)
#define _For(i,l,r) for(register int i = r; i >= l; --i)
using namespace std;
using namespace __gnu_pbds;
typedef double db;
typedef unsigned long long ull;
typedef long long ll;
bool Begin;
const int N = 3e5 + 10; 
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
bool F;
int n, q, op, x, y, l, r, c1, c2;
ll w1, w2;
ll a[N], s[N];
namespace Tree{
	ll a[N];
	inline void add(int x, int v){
		for(int i = x; i <= n; i += lowbit(i))
		  a[i] += v;
	}
	inline ll query(int x){
		ll ans = 0;
		for(int i = x; i; i -= lowbit(i))
		  ans += a[i];
		return ans;
	}
};
namespace Seg{
	#define ls(k) k << 1
	#define rs(k) k << 1 | 1
	struct Node{
		int l, r;
		ll data;
		ll Max;
		ll tag;
	}X[N<<2];
	inline void pushup(int k){
		X[k].Max = max(X[ls(k)].Max, X[rs(k)].Max);
		X[k].data = max(X[ls(k)].data, X[rs(k)].data);
	}
	inline void add(int k, ll v){
		X[k].Max += v;
		X[k].tag += v;
	}
	inline void push_down(int k){
		if(X[k].tag){
			add(ls(k), X[k].tag);
			add(rs(k), X[k].tag);
			X[k].tag = 0;
		}
	}
	inline void build(int k, int l, int r){
		X[k].l = l, X[k].r = r;
		if(l == r){
			X[k].data = a[l];
			X[k].Max = s[min(l + c2 - 1, n)] - s[l - 1];
			return ;
		}
		int mid = (l + r) >> 1;
		build(ls(k), l, mid);
		build(rs(k), mid + 1, r);
		pushup(k);
	}
	inline void update(int k, int i, int v){
		if(X[k].l == i && i == X[k].r){
			X[k].data += v;
			return ;
		}
		push_down(k); 
		int mid = (X[k].l + X[k].r) >> 1;
		if(i <= mid)
		  update(ls(k), i, v);
		else
		  update(rs(k), i, v);
		pushup(k);
	}
	inline void update(int k, int l, int r, int v){
		if(X[k].l == l && r == X[k].r){
			add(k, v);
			return ;
		}
		push_down(k);
		int mid = (X[k].l + X[k].r) >> 1;
		if(r <= mid)
		  update(ls(k), l, r, v);
		else if(l > mid)
		  update(rs(k), l, r, v);
		else{
			update(ls(k), l, mid, v);
			update(rs(k), mid + 1, r, v);
		} 
		pushup(k);
	}
	inline ll query(int k, int l, int r){
		if(X[k].l == l && r == X[k].r)
		  return X[k].data;
		push_down(k);
		int mid = (X[k].l + X[k].r) >> 1;
		if(r <= mid)
		  return query(ls(k), l, r);
		else if(l > mid)
		  return query(rs(k), l, r);
		else
		  return max(query(ls(k), l, mid), query(rs(k), mid + 1, r));
	} 
	inline int ask1(int k){
		if(X[k].l == X[k].r)
		  return X[k].l;
		push_down(k);
		if(X[ls(k)].Max > w2)
		  return ask1(ls(k));
		else
		  return ask1(rs(k));
	}
	inline int ask2(int k){
		if(X[k].l == X[k].r)
		  return X[k].l;
		push_down(k);
		if(X[rs(k)].Max > w2)
		  return ask2(rs(k));
		else
		  return ask2(ls(k));
	}
	inline int Ask1(int k, int l, int r){
		if(X[k].l == l && r == X[k].r){
			if(X[k].Max > w2 && F){
				F = 0;
				return ask1(k);
			}
			return 1e9 + 10;
		}
		push_down(k);
		int mid = (X[k].l + X[k].r) >> 1;
		if(r <= mid)
		  return Ask1(ls(k), l, r);
		else if(l > mid)
		  return Ask1(rs(k), l, r);
		else{
			int x = Ask1(ls(k), l, mid);
			int y = Ask1(rs(k), mid + 1, r);
			return min(x, y);
		}	
	}
	inline int Ask2(int k, int l, int r){
		if(X[k].l == l && r == X[k].r){
			if(X[k].Max > w2 && F){
				F = 0;
				return ask2(k);
			}
			return 0;
		}
		push_down(k);
		int mid = (X[k].l + X[k].r) >> 1;
		if(r <= mid)
		  return Ask2(ls(k), l, r);
		else if(l > mid)
		  return Ask2(rs(k), l, r);
		else{
			int y = Ask2(rs(k), mid + 1, r);
			int x = Ask2(ls(k), l, mid);
			return max(x, y);
		}	
	}
};
bool End;
int main(){
	n = read(), q = read(), c1 = read(), c2 = read(), w1 = read(), w2 = read();
	for(int i = 1; i <= n; ++i){
		a[i] = read();
		s[i] = s[i - 1] + a[i];
		Tree::add(i, a[i]);
	}
	Seg::build(1, 1, n);
	while(q--){
		op = read();
		if(op == 1){
			x = read(), y = read();
			Tree::add(x, y);
			Seg::update(1, x, y);
			Seg::update(1, max(1, x - c2 + 1), x, y);
		}
		else{
			l = read(), r = read();
			if(r - l + 1 < c2){
				ll sum = Tree::query(r) - Tree::query(l - 1);
				if(sum <= w1 && r - l + 1 <= c1)
				  puts("cont");
				else{
					if(sum > w2)
					  puts("tetris");
					else{
						if(Seg::query(1, l, r) <= w1)
						  puts("cont");
						else
						  puts("tetris");
					}
				}
				continue;
			}
			F = 1;
			int L = Seg::Ask1(1, l, r - c2 + 1);
			F = 1;
			int R = Seg::Ask2(1, l, r - c2 + 1) + c2 - 1;
			if(L == 1e9 + 10){
				if(Seg::query(1, l, r) <= w1)
				  puts("cont");	
				else
				  puts("tetris");
				continue;
			}
			if(R - L + 1 > c1 || Tree::query(R) - Tree::query(L - 1) > w1)
			  puts("tetris");
			else
			  puts("cont");	
		}
	}
	cerr << '\n' << abs(&Begin - &End) / 1048576 << "MB";
	return 0;
}
```

---

## 作者：_zuoqingyuan (赞：0)

youyou $\to$ Alice，yy $\to$ Bob。

# 思路分析

首先思考 Bob 胜利的局面可能有哪些。

如果 Alice 不可能把整个序列染标记，那么 Bob 躺着就可以赢，出现这种局面则必须满足整个序列的最大值大于 $w_1$，此时无论如何 Alice 都无法胜利。

如果 Alice 可以把整个序列染标记，那么 Bob 就必须做出一定行动阻止 Alice 达成胜利。因此此时必须有 Bob 有可操作的区间，即区间和大于 $w_2$ 长度小于 $c_2$ 的区间，因为数非负，所以 Bob 操作的区间越长越好，即只要满足区间 $[l,l+c_2-1]$ 满足 $S_{l+c_2-1}-S_{l-1}>w_2$，其中 $S$ 是前缀和数组。

如果存在一个 Alice 不能操作，但 Bob 可操作的区间，则 Alice 必输，因为无论如何它都不能使 Bob 可操作的区间都打上标记。

那么如果 Bob 可操作的所有区间，Alice 都可以操作呢？

**结论**：假设 Bob 有 $k$ 个可操作的区间 $[l_1,r_1],[l_2,r_2],\dots,[l_k,r_k]$，如果 Alice 无法通过一次操作将 $[l_1,r_k]$ 内全部标记，那么 Alice 必输。

证明：非常好证，如果 Alice 将 $l_1$ 打上标记，下一步 Bob 就可以清除 $r_k$ 上的标记；反之，若 Alice 将 $r_k$ 打上标记，下一步 Bob 就可以清除 $l_1$ 上的标记。如此循环，Alice 注定无法在有限的回合内取胜。

综上可得：

1. 若区间最大值大于 $w_1$，则 Bob 必胜。

2. 若 Bob 无可操作的区间，则 Alice 必胜。

3. 假设 Bob 有 $k$ 个可操作的区间 $[l_1,r_1],[l_2,r_2],\dots,[l_k,r_k]$，若 Alice 无法操作 $[l_1,r_k]$ 这个区间，则 Bob 必胜。

4. Alice 必胜。

只需按照顺序模拟，就可以得到 50 pts。


```
#include <iostream>
#include <cstdio>
using namespace std;
const int N=3e5+10;
typedef long long ll;
ll n,q,c1,c2,w1,w2,a[N],op,l,r,s[N],len,lef,righ,flag;
int main(){
	scanf("%lld %lld %lld %lld %lld %lld",&n,&q,&c1,&c2,&w1,&w2);
	for(int i=1;i<=n;i++){
		scanf("%lld",a+i);
	}
	while(q--){
		scanf("%lld %lld %lld",&op,&l,&r);
		if(op==1)a[l]+=r;
		else{
			for(int i=1;i<=n;i++)s[i]=s[i-1]+a[i];
			len=min(r-l+1,c2),lef=righ=flag=0;
            for(int i=l;i<=r;i++)if(a[i]>w1)flag=1;
            if(flag){
                printf("tetris\n");
                continue;
            }
			for(int i=l+len-1;i<=r;i++){
				if(s[i]-s[i-len]>w2){
					if(!lef)lef=i-len;
					righ=i;
				}
			}
			if(!lef&&!righ)printf("cont\n");
			else if(righ-lef<=c1&&s[righ]-s[lef]<=w1)printf("cont\n");
            else printf("tetris\n");
		}
	}
	return 0;
}

```

思考如何快速维护。

首先可以用线段树维护区间最大值。

然后用另一颗线段树维护数组 $v$，其中 $v_i=S_i-S_{i-c_2}$。单点查询就可以转化为区间加，同时维护区间最大值。然后线段树二分即可找到 $l_1,r_k$。时间复杂度 $O(n\log n)$。

```cpp
#include <iostream>
#include <cstdio>
#define ls (p<<1)
#define rs (p<<1|1)
using namespace std;
const int N=3e5+10;
typedef long long ll;
int n,q,c1,c2,op,l,r,lef,righ;
ll w1,w2,s[N],val,tmp;
struct sgt1{
	ll mx[N<<2],sm[N<<2];
	void push_up(int p){
		mx[p]=max(mx[ls],mx[rs]);
		sm[p]=sm[ls]+sm[rs];
	}
	void add(int p,int l,int r,int x,ll v){
		if(l==r){
			mx[p]+=v,sm[p]+=v;
		}else{
			int mid=(l+r)>>1;
			if(x<=mid)add(ls,l,mid,x,v);
			if(x>mid)add(rs,mid+1,r,x,v);
			push_up(p); 
		}
		return;
	}
	ll ask(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)return mx[p];
		int mid=(l+r)>>1;ll cnt=0;
		if(L<=mid)cnt=max(cnt,ask(ls,l,mid,L,R));
		if(R>mid)cnt=max(cnt,ask(rs,mid+1,r,L,R));
		return cnt;
	}
	ll sum(int p,int l,int r,int L,int R){
		if(L<=l&&r<=R)return sm[p];
		int mid=(l+r)>>1;ll cnt=0;
		if(L<=mid)cnt+=sum(ls,l,mid,L,R);
		if(R>mid)cnt+=sum(rs,mid+1,r,L,R);
		return cnt;
	}
}a;
struct sgt2{
	ll mx[N<<2],tag[N<<2];
	void push_up(int p){
		mx[p]=max(mx[ls],mx[rs]);
	}
	void push_down(int p){
		if(!tag[p])return;
		tag[ls]+=tag[p],tag[rs]+=tag[p];
		mx[ls]+=tag[p],mx[rs]+=tag[p];
		tag[p]=0;return;
	}
	void add(int p,int l,int r,int L,int R,ll v){
		if(L<=l&&r<=R){
			mx[p]+=v,tag[p]+=v;
		}else{
			int mid=(l+r)>>1;
			push_down(p);
			if(L<=mid)add(ls,l,mid,L,R,v);
			if(R>mid)add(rs,mid+1,r,L,R,v);
			push_up(p); 
		}
	}
	int find_left(int p,int l,int r,int L,int R,ll v){
		if(L<=l&&r<=R){
			if(mx[p]<=v)return -1;
			if(l==r)return l;
			push_down(p);int mid=(l+r)>>1;
			if(mx[ls]>v)return find_left(ls,l,mid,L,R,v);
			else return find_left(rs,mid+1,r,L,R,v);
		}
		int mid=(l+r)>>1,res=-1;push_down(p);
		if(L<=mid)res=find_left(ls,l,mid,L,R,v);
		if(res!=-1)return res;
		if(R>mid)res=find_left(rs,mid+1,r,L,R,v);
		return res;
	}
	int find_right(int p,int l,int r,int L,int R,ll v){
		if(L<=l&&r<=R){
			if(mx[p]<=v)return -1;
			if(l==r)return l;
			push_down(p);int mid=(l+r)>>1;
			if(mx[rs]>v)return find_right(rs,mid+1,r,L,R,v);
			else return find_right(ls,l,mid,L,R,v);
		}
		int mid=(l+r)>>1,res=-1;push_down(p);
		if(R>mid)res=find_right(rs,mid+1,r,L,R,v);
		if(res!=-1)return res;
		if(L<=mid)res=find_right(ls,l,mid,L,R,v);
		return res;
	}
}b;
int main(){
	scanf("%d %d %d %d %lld %lld",&n,&q,&c1,&c2,&w1,&w2);
	for(int i=1;i<=n;i++){
		scanf("%lld",s+i);
		a.add(1,1,n,i,s[i]);
		s[i]+=s[i-1]; 
	}
	for(int i=c2;i<=n;i++)b.add(1,1,n,i,i,s[i]-s[i-c2]);
	c1=min(c1,n),c2=min(c2,n);
	while(q--){
		scanf("%d %d",&op,&l);
		if(op==1){
			scanf("%lld",&val);
			a.add(1,1,n,l,val);
			b.add(1,1,n,l,min(n,l+c2-1),val); 
		}else{
			scanf("%d",&r);
			if(a.ask(1,1,n,l,r)>w1){
				printf("tetris\n");
				continue;
			}
			if(r-l+1<=c2){
				tmp=a.sum(1,1,n,l,r);
				if(tmp>w2){
					if(r-l+1<=c1&&tmp<=w1)printf("cont\n");
					else printf("tetris\n");
				}else printf("cont\n");
			}else{
				lef=b.find_left(1,1,n,l+c2-1,r,w2);
				righ=b.find_right(1,1,n,l+c2-1,r,w2);
				if(lef==-1&&righ==-1)printf("cont\n");
				else{
					lef-=c2;
					if(righ-lef<=c1&&a.sum(1,1,n,lef+1,righ)<=w1)printf("cont\n");
            		else printf("tetris\n");
				}
			}
		}
	}
	return 0;
} 

```

---

## 作者：tobie (赞：0)

直接考虑操作策略似乎有点困难，考虑这么一个弱化：假设当前操作序列长度为 $n$，小 X 可以一次染一个长度为 $n-1$ 的连续段，小 Y 每次只能染一个长度为 $1$ 的单点，在这种情况下小 X 能否完成目标？

很遗憾，即使小 X 在如此巨大的优势下仍然无法获胜。究其原因，小 Y 只需要防守好编号为 $1$ 和 $n$ 的点，则这两个点在任何时刻都不能同时变成红色，就可以打乱小 X 的操作。

所以，我们考虑从 "小 X 在什么情况下无法达到目标" 出发进行考虑。从上面的例子可以观察到，只要小 Y 能够控制两个点 $a,b$，并且小 X 无法同时对 $a,b$ 位置染色，那小 X 就寄了。

显然我们让小 Y 防守好他能控制到的最左和最右的点一定不劣。

那我们接下来从反面考虑：如果小 X 能够一步之内对这染色两个点，能不能达到目标？

其实是可以的。假设小 Y 能防守 $L,R$ 两个位置，则小 X 可以进行单点修改 $[1,L)$ 和 $(R,n]$ 中的点，把它们蚕食干净后，一步端掉 $[L,R]$ 即可。

所以我们把这题转换成两个部分：

- 找到小 Y 能够防守到的最靠边的点 $L,R$
- 查询小 X 能否在一步内覆盖 $[L,R]$

第二部分我们只要求出 $[L,R]$ 内所有数的和即可，可以用树状数组维护。

对于第一部分，我们发现，小 Y 在把 $c_2$ 的长度全部用上一定不劣，所以考虑维护 $b_i\leftarrow \sum_{j\in[i,i+c_2)} a_j$ 之后线段树二分即可。

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long ll;
const int N=6e5+9;
int n,Q,c1,c2,w1,w2;
ll a[N];
ll sL[N],sR[N];

ll BIT[N];
void Add(int i,int x){for(;i<=n;i+=(i&(-i))) BIT[i]+=x;}
ll Ask(int i){ll x=0;for(;i;i-=(i&(-i))) x+=BIT[i];return x;}
ll Ask(int l,int r){return Ask(r)-Ask(l-1);}

class SegTree{
private:
#define lson (u<<1)
#define rson ((u<<1)|1)
#define mid ((l+r)/2)
	ll mx[N<<2],tag[N<<2];
	void pushup(int u){mx[u]=max(mx[lson],mx[rson]);}
	void Add(int u,int x){mx[u]+=x,tag[u]+=x;}
	void pushdown(int u)
	{
		if(tag[u]==0) return;
		Add(lson,tag[u]);Add(rson,tag[u]);
		tag[u]=0;
	}
	void Build(int u,int l,int r,ll *num)
	{
		tag[u]=0;
		if(l==r) return mx[u]=num[l],void();
		Build(lson,l,mid,num);Build(rson,mid+1,r,num);
		pushup(u);
	}
	void Modify(int u,int l,int r,int L,int R,int x)
	{
		if(L<=l&&r<=R) return Add(u,x);
		pushdown(u);
		if(L<=mid) Modify(lson,l,mid,L,R,x);
		if(mid<R) Modify(rson,mid+1,r,L,R,x);
		pushup(u);
	}
	ll Query(int u,int l,int r,int L,int R)
	{
		if(L<=l&&r<=R) return mx[u];
		pushdown(u);
		if(L<=mid&&mid<R) return max(Query(lson,l,mid,L,R),Query(rson,mid+1,r,L,R));
		return L<=mid?Query(lson,l,mid,L,R):Query(rson,mid+1,r,L,R);
	}
	int getpos1(int u,int l,int r,int x,int d)
	{
		if(l>=x&&mx[u]<=d) return r+1;
		if(l==r) return l;
		pushdown(u);
		if(x<=mid)
		{
			int res=getpos1(lson,l,mid,x,d);
			if(res<=mid) return res;
		}
		return getpos1(rson,mid+1,r,x,d);
	}
	int getpos2(int u,int l,int r,int x,int d)
	{
		if(r<=x&&mx[u]<=d) return l-1;
		if(l==r) return l;
		pushdown(u);
		if(x>mid)
		{
			int res=getpos2(rson,mid+1,r,x,d);
			if(res>mid) return res;
		}
		return getpos2(lson,l,mid,x,d);
	}
#undef lson
#undef rson
#undef mid
public:
	void Modify(int l,int r,int x){Modify(1,1,n,l,r,x);}
	ll Query(int l,int r){return Query(1,1,n,l,r);}
	void Build(ll *num){Build(1,1,n,num);}
	int getpos1(int x,int d){return getpos1(1,1,n,x,d);}
	int getpos2(int x,int d){return getpos2(1,1,n,x,d);}
};
SegTree xds_a,xds_sL,xds_sR;


ll Read()
{
	ll x=0;
	char ch=getchar();
	while(ch<'0'||'9'<ch) ch=getchar();
	while('0'<=ch&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return x;
}

signed main()
{
//	freopen("seq.in","r",stdin);
//	freopen("seq.out","w",stdout);
	n=Read(),Q=Read(),c1=Read(),c2=Read(),w1=Read(),w2=Read();
	for(int i=1;i<=n;i++) a[i]=Read();
	
	for(int i=1;i<=n;i++) Add(i,a[i]);
	for(int i=1;i+c2-1<=n;i++) sL[i]=Ask(i,i+c2-1);
	for(int i=n;i>=c2;i--) sR[i]=Ask(i-c2+1,i);
	xds_a.Build(a);
	xds_sL.Build(sL);
	xds_sR.Build(sR);
	
	while(Q--)
	{
		int op,x,y;
		op=Read(),x=Read(),y=Read();
		if(op==1)
		{
			a[x]+=y;
			Add(x,y);
			xds_a.Modify(x,x,y);
			xds_sL.Modify(max(x-c2+1,1),x,y);
			xds_sR.Modify(x,min(x+c2-1,n),y);
		}
		else
		{
			if(xds_a.Query(x,y)>w1){puts("tetris");continue;}
			int L0=-1,R0=-1;
			if(y-x+1<=c2)
			{
				if(Ask(x,y)>w2) L0=x,R0=y;
			}
			else
			{
				L0=xds_sL.getpos1(x,w2),R0=xds_sR.getpos2(y,w2);
				if(L0>y-c2+1) L0=R0=-1;
			}
			if(L0==-1) puts("cont");
			else
			{
				if(R0-L0+1>c1) puts("tetris");
				else if(Ask(L0,R0)>w1) puts("tetris");
				else puts("cont");
			}
		}
	}
}
```

---

## 作者：2020HZ06 (赞：0)

首先如果 $\max a_i>w_1$ 则 yy 必胜。

否则 yy 要将尽可能大的一段区间染为蓝色。

那么每次操作 yy 一定是选长为 $\min(c_2,len)$ 的一段，因为区间长度越大数的总和越可能 $> w_2$。这也能尽量阻止 youyou 获胜。把序列中所有长为 $\min(c_2,len)$，总和 $>w_2$ 的区间称为 **“合法区间”**。

现在考虑 youyou 的策略，序列中不属于任何一个合法区间的元素 youyou 都可以随时染色，对答案**无影响**。考虑合法区间中的元素，若 youyou 能一次把所有这些元素全部染色，那么 youyou **必胜**。否则 youyou 在染色后**属于合法区间**的最左边的元素和最右边的元素**最多被染了一个**。yy 可以把这一个再**染回去**，因此 youyou **必败**。

当 $c_2\le len$ 时我们需要维护所有长度为 $c_2$ 且 $sum>w_2$ 的合法区间。把序列中长度为 $c_2$ 的所有子区间都**对应**缩成一个点。每次 $a_x+=y$ 时左端点在 $[x-c_2+1,x]$ 的合法区间值都加上 $y$。

要求出最左边合法区间和最右边合法区间的位置（判断 $r-l\le c_1$)，**线段树上二分**即可。另外还需要动态维护区间和（判断 $sum_{l,r} \le w_1$），求区间最大值（判断 $\max a_i\le w_1$）。 再开一棵线段树。

时间复杂度 $O((n+q)\log n)$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ls rt*2
#define rs rt*2+1
#define mid (l+r)/2
const int N=300005;
int n,q,c1,c2,w1,w2;
ll a[N];
struct node{
	ll s,mx;
	node operator +(const node &a)const{
		return {s+a.s,max(mx,a.mx)};
	}
};int tot;
struct tree{
	ll tr[4*N],mx[4*N],lz[4*N];
	void pd(int l,int r,int rt){
		if(lz[rt]){
			tr[ls]+=lz[rt]*(mid-l+1),tr[rs]+=lz[rt]*(r-mid);
			mx[ls]+=lz[rt],mx[rs]+=lz[rt],lz[ls]+=lz[rt],lz[rs]+=lz[rt];
			lz[rt]=0;
		}
	}
	void build(int l,int r,int rt){
		lz[rt]=0;
		if(l==r){
			mx[rt]=tr[rt]=a[l];return;
		}
		build(l,mid,ls),build(mid+1,r,rs);
		mx[rt]=max(mx[ls],mx[rs]);
		tr[rt]=tr[ls]+tr[rs];
	}
	void add(int l,int r,int rt,int L,int R,ll k){
		if(l>=L&&r<=R){
			tr[rt]+=k*(r-l+1),mx[rt]+=k,lz[rt]+=k;
			return;
		}
		pd(l,r,rt);
		if(L<=mid) add(l,mid,ls,L,R,k);
		if(R>mid) add(mid+1,r,rs,L,R,k);
		mx[rt]=max(mx[ls],mx[rs]);
		tr[rt]=tr[ls]+tr[rs];
	}
	node query(int l,int r,int rt,int L,int R){
		if(l>=L&&r<=R) return {tr[rt],mx[rt]};
		pd(l,r,rt);
		node res={0,0};
		if(L<=mid) res=res+query(l,mid,ls,L,R);
		if(R>mid) res=res+query(mid+1,r,rs,L,R);
		return res;
	}
	int find(int l,int r,int rt,int L,int R,int k,bool tp){
		if(l>=L&&r<=R){
			if(mx[rt]<=k) return -1;
			if(l==r) return l;
			pd(l,r,rt);
			if(tp==0){
				if(mx[ls]>k) return find(l,mid,ls,L,R,k,tp);
				return find(mid+1,r,rs,L,R,k,tp);
			}
			else{
				if(mx[rs]>k) return find(mid+1,r,rs,L,R,k,tp);
				return find(l,mid,ls,L,R,k,tp);
			}
		}
		pd(l,r,rt);//if(tot==432) cerr<<l<<" "<<r<<" "<<mx[rt]<<endl;
		int res=-1;
		if(tp==0){
			if(L<=mid&&mx[ls]>k) res=find(l,mid,ls,L,R,k,tp);
			if(R>mid&&res==-1&&mx[rs]>k) res=find(mid+1,r,rs,L,R,k,tp);
		}
		else{
			if(R>mid&&mx[rs]>k) res=find(mid+1,r,rs,L,R,k,tp);
			if(L<=mid&&res==-1&&mx[ls]>k) res=find(l,mid,ls,L,R,k,tp);
		}
		return res;
	}
}T[2];
int main(){
	int op,x,y;
	scanf("%d%d%d%d%d%d",&n,&q,&c1,&c2,&w1,&w2);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	T[0].build(1,n,1);
	for(int i=1;i+c2-1<=n;i++) a[i]=T[0].query(1,n,1,i,i+c2-1).s;
	int m=n-c2+1;
	if(c2<=n) T[1].build(1,m,1);
	while(q--){
		scanf("%d%d%d",&op,&x,&y);
		if(op==1) T[0].add(1,n,1,x,x,y),T[1].add(1,m,1,max(1,x-c2+1),min(x,m),y);
		else{
			int len=y-x+1;
			node u=T[0].query(1,n,1,x,y);
			if(u.mx>w1) printf("tetris\n");
			else{
				if(c2>len){
					if(u.s>w2&&(u.s>w1||len>c1)) printf("tetris\n");
					else printf("cont\n");
				}
				else{
					int p1=T[1].find(1,m,1,x,y-c2+1,w2,0),p2=T[1].find(1,m,1,x,y-c2+1,w2,1);
					if(p1==-1){
						printf("cont\n");
						continue;
					}
					int l=p1,r=p2+c2-1;
					u=T[0].query(1,n,1,l,r);
					if(u.s>w1||r-l+1>c1) printf("tetris\n");
					else printf("cont\n");
				}
			}
		}
	}
	return 0;
}
```

---

