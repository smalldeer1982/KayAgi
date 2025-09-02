# [JRKSJ R9] 在相思树下 III

## 题目背景

>我知 
>
>再迷恋他也非我能私有
>
>就当神爱世人遥远温柔 
>
>未必要牵手
>
>隔千万光年宇宙献吻 
>
>亦真切感受
>
>不用 
>
>强求 
>
>对号入座那虚构

## 题目描述

给你一个长为 $n$ 的序列 $a_{1\dots n}$，你需要对它进行两种操作共 $n-1$ 次。

对一个长度为 $l$ 的序列 $b_{1\dots l}$ 进行一次操作将会把序列变为一个长为 $l-1$ 的序列 $c_{1\dots l-1}$：

- 操作一中，$\forall i\in[1,l),c_i=\max(b_i,b_{i+1})$；
- 操作二中，$\forall i\in[1,l),c_i=\min(b_i,b_{i+1})$。

给定整数 $m$，你只能进行**至多** $m$ 次操作一。进行 $n-1$ 次操作后序列 $a$ 的长度变为 $1$。你可以任意安排操作的顺序，求最终剩余的数 $a_1$ 的最大值。

## 说明/提示

### 样例解释

一种可能的操作顺序是：
- 进行一次操作一，序列变为 $2,3,3$；
- 进行一次操作二，序列变为 $2,3$；
- 进行一次操作一，序列变为 $3$。

显然最终剩余的数不可能大于 $3$。

### 数据规模与约定

**本题采用捆绑测试。**

| $\mathrm{Subtask}$ | $n\le$ | 特殊性质 | 分数 |
| :----------: | :----------: | :----------: | :----------: |
| $1$ | $10$ |  | $10$ |  
| $2$ | $5000$ |  | $30$ |  
| $3$ | $10^6$ | $\checkmark$ | $20$ |  
| $4$ | $10^6$ |  | $40$ |  

特殊性质：保证 $\forall i\in[1,n],a_i\le10$。

对于所有数据，保证 $1\leq m < n \leq 10^6$，$1 \leq a_i \leq 10^{9}$。

## 样例 #1

### 输入

```
4 2
1 2 3 3```

### 输出

```
3```

# 题解

## 作者：Rannio (赞：10)

先说结论：先把操作一用完是最优的。

证明：

每次操作一都是在 $a_i$ 与 $a_{i+1}$ 中取最大值，做 $x-1$ 次取最大值操作就相当于删去一个最小值，取出前 $x-1$ 大的值。容易发现这样会使最小值变大。

而做一次操作二就相当于删去一个最大值，取出前 $x-1$ 小的值。做 $x-1$ 次操作二就相当于取出原数组最小值，那么此时使最小值最大一定是最优的。

此时我们回过来看做 $m$ 次操作的影响，容易发现做 $m$ 次在 $a_i$ 与 $a_{i+1}$ 中取最大值的操作就相当于删去 $a_i$ 至 $a_{i+m}$ 的 $m-1$ 个最小值，取出最大值，而此时再做 $n-m$ 次操作二就是在做完 $m$ 次操作一的数组中取最小值，这个就是答案。

区间最值用线段树维护即可，时间复杂度 $\mathcal{O}(n \log n)$。

```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,m,ans=LLONG_MAX;
int a[1000005],b[1000005];
struct node{
	int l,r,sum1;
}tree[4000005];
void upd(int now){
    tree[now].sum1=max(tree[now<<1].sum1,tree[now<<1|1].sum1);
}
void build(int now,int l,int r){
    tree[now].l=l;
	tree[now].r=r;
	if(l==r){
        tree[now].sum1=a[l];
		return;
	}
	int mid=(l+r)>>1;
	build(now<<1,l,mid);
	build(now<<1|1,mid+1,r);
	upd(now);
}
int search1(int now,int l,int r){
	if(tree[now].l>=l&&tree[now].r<=r) return tree[now].sum1;
	int mid=(tree[now].l+tree[now].r)>>1;
	if(r<=mid) return search1(now<<1,l,r);
	else if(l>mid) return search1(now<<1|1,l,r);
	else return max(search1(now<<1,l,mid),search1(now<<1|1,mid+1,r));
}
signed main(){
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;i++){
        scanf("%lld",&a[i]);
    }
    build(1,1,n);
    for(int i=1;i<=n-m;i++){
        b[i]=search1(1,i,i+m);
        ans=min(ans,b[i]);
    }
    printf("%lld",ans);
    return 0;
}
```

---

## 作者：晴空一鹤 (赞：7)

结论应该很好猜，就是先用 $\max$ 再用 $\min$，考虑证明。

假设最优方案不是这个，那一定存在一个 $\min$ 紧接其后用了 $\max$。考虑交换这两个操作，交换前序列每个数改变为向后的第 $1$ 小或第 $2$ 小，交换后改变为向后的第 $2$ 小或第 $3$ 小，显然换了不会更劣。

考虑处理操作。连着的 $m$ 次 $\max$ 会把每个数变为向后 $m$ 个数的最大值，最后的答案即为这些数的最小值。

可以使用优先队列。每次取出最大值的时候把超过范围的删掉就行了。


```
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000005],mi=1e9;
struct no{
  int x,y;
  friend bool operator<(no a,no b){
  return a.x<b.x;
  }
}t;
priority_queue<no>q;
int main(){
  cin>>n>>m;
  for(int i=1;i<=n;i++){
  cin>>a[i];
  t.x=a[i];t.y=i;
  q.push(t);
  if(i>m){
  while(!q.empty()&&i-q.top().y>m)q.pop();
  mi=min(mi,q.top().x);
  }
  }
  cout<<mi<<"\n";
}
```

---

## 作者：XuYueming (赞：4)

## 前言

题目链接：[洛谷](https://www.luogu.com.cn/problem/P10878)。

[更好的体验](https://www.cnblogs.com/XuYueming/p/18364514)。

赛时脑子坨成一坨了，估计是 T1 的影响，写一篇题解来理清思路。

## 题意简述

给你一个长为 $n$ 的序列 $a_{1\dots n}$，你需要对它进行两种操作共 $n-1$ 次。

对一个长度为 $l$ 的序列 $b_{1\dots l}$ 进行一次操作将会把序列变为一个长为 $l-1$ 的序列 $c_{1\dots l-1}$：

- 操作一中，$\forall i\in[1,l),c_i=\max(b_i,b_{i+1})$；
- 操作二中，$\forall i\in[1,l),c_i=\min(b_i,b_{i+1})$。

给定整数 $m$，你只能进行**至多** $m$ 次操作一。进行 $n-1$ 次操作后序列 $a$ 的长度变为 $1$。你可以任意安排操作的顺序，求最终剩余的数 $a_1$ 的最大值。

## 题目分析

### 方法 $1$：二分 + 差分

很容易想到二分，把序列中 $\geq mid$ 的统统看成 $1$，反之是 $0$，问题变成了最后留下的那一个数是不是 $1$。

我们不需要考虑 $1$ 之间，$0$ 之间的相互操作，应为无论是 $\min$ 或 $\max$，$\geq mid$ 的永远不会 $< mid$，反之亦然。所以，我们把序列分成若干极长的 $\tt 01$ 段，考虑这两个操作对两段交界处的影响。

对于取 $\max$，会把 $\tt 01$ 变成 $\tt 11$；对于取 $\min$，会把 $\tt 10$ 变成 $\tt 00$。由于我们关心 $1$，所以，前者是把所有极长的 $1$ 段左边界向左扩展，后者是对所有极长的 $1$ 段右边界向左收缩。

考虑扩展和收缩的先后顺序。在答案的操作序列中，对于相邻的两个操作，把先收缩再扩展的，变成先扩展再收缩一定不劣。原因是，先收缩可能会完全消除某一个长度为 $1$ 的段，但是后者不会。邻项交换证明得，答案就是先扩展，再收缩。显然，多用扩展一定不劣。所以，我们确定了答案的操作序列。

先扩展 $m$ 次，再收缩 $n - m - 1$ 次，相当于我们对于初始的极长 $1$ 段的左端点 $l$，把 $[l - m, l - 1]$ 覆盖成 $1$，最后看看 $[1, n - m]$ 是否均为 $1$。这些操作直接差分就行了。因为我们只用知道那些地方一次都没被覆盖过。

时间复杂度：$\Theta(n \log V)$，当然离散化后 $V = \mathcal{O}(n)$。

### 方法 $2$：单调队列

能否优化呢？我们可以从另一种思路来分析。感觉是贪心，考虑答案操作序列的相邻两个操作，是先取 $\max$ 还是先取 $\min$。不妨列出式子，对于之前连续的三个数 $a, b, c$，操作两次后得到的 $a'$ 分别为 $\max \lbrace \min \lbrace a, b \rbrace, \min \lbrace b, c \rbrace \rbrace$，$\min \lbrace \max \lbrace a, b \rbrace, \max \lbrace b, c \rbrace \rbrace$。然后凭借你的数学直觉……额，看不出来……没关系！枚举 $1 \sim 3$ 的全排列来看看：

|   $a, b, c$   |   先 $\min$ 再 $\max$   |   先 $\max$ 再 $\min$   |
| ---- | ---- | ---- |
|   $1, 2, 3$   |   $\max \lbrace \min \lbrace 1, 2 \rbrace, \min \lbrace 2, 3 \rbrace \rbrace = 2$   |   $\min \lbrace \max \lbrace 1, 2 \rbrace, \max \lbrace 2, 3 \rbrace \rbrace = 2$   |
|   $1, 3, 2$   |   $\max \lbrace \min \lbrace 1, 3 \rbrace, \min \lbrace 3, 2 \rbrace \rbrace = 2$   |   $\min \lbrace \max \lbrace 1, 3 \rbrace, \max \lbrace 3, 2 \rbrace \rbrace = 3$   |
|   $2, 1, 3$   |   $\max \lbrace \min \lbrace 2, 1 \rbrace, \min \lbrace 1, 3 \rbrace \rbrace = 1$   |   $\min \lbrace \max \lbrace 2, 1 \rbrace, \max \lbrace 1, 3 \rbrace \rbrace = 2$   |
|   $2, 3, 1$   |   $\max \lbrace \min \lbrace 2, 3 \rbrace, \min \lbrace 3, 1 \rbrace \rbrace = 2$   |   $\min \lbrace \max \lbrace 2, 3 \rbrace, \max \lbrace 3, 1 \rbrace \rbrace = 3$   |
|   $3, 1, 2$   |   $\max \lbrace \min \lbrace 3, 1 \rbrace, \min \lbrace 1, 2 \rbrace \rbrace = 1$   |   $\min \lbrace \max \lbrace 3, 1 \rbrace, \max \lbrace 1, 2 \rbrace \rbrace = 2$   |
|   $3, 2, 1$   |   $\max \lbrace \min \lbrace 3, 2 \rbrace, \min \lbrace 2, 1 \rbrace \rbrace = 2$   |   $\min \lbrace \max \lbrace 3, 2 \rbrace, \max \lbrace 2, 1 \rbrace \rbrace = 2$   |

容易发现，由于大的数在取最值得时候没取到，前者是不优的。这也恰好对应了我们方法 $1$ 中的结论。

所以，依然得出了先弄 $m$ 次操作一，再弄 $n - m - 1$ 次操作二。

在前 $m$ 次操作后，对于一个数 $a_i$，它最终的值便是 $\max \lbrace a_{i \dots i + m} \rbrace$，使用 ST 表，线段树都行，或者滑动窗口用单调队列。对于后 $n - m - 1$ 次操作同理，不过我们只要知道 $a_1$，所以求一遍 $a_{1 \dots n - m}$ 的 $\min$ 即可。

时间复杂度：$\Theta(n)$。

## 代码

### 方法 $1$：二分 + 差分

```cpp
#include <cstdio>
#include <iostream>
using namespace std;

const int N = 1000010;

int n, m, val[N];

int yzh[N];

inline bool check(int x) {
    for (int i = 1; i <= n; ++i) yzh[i] = (val[i] >= x) - (val[i + 1] >= x);
    for (int i = n; i >= 1; --i) {
        if (val[i] >= x && val[i - 1] < x)
            --yzh[max(0, i - m - 1)], ++yzh[i - 1];
        yzh[i] += yzh[i + 1];
    }
    for (int i = 1; i <= n - m; ++i) if (yzh[i] <= 0) return false;
    return true;
}

signed main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &val[i]);
    int l = 1, r = 1e9, ans = 736520;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (check(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d", ans);
    return 0;
}
```

### 方法 $2$：单调队列

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 1000010;

inline void read(int &x) {
	x = 0; char ch = getchar();
	for (; !isdigit(ch); ch = getchar());
	for (; isdigit(ch); x = (x << 3) + (x << 1) + (ch ^ 48), ch = getchar());
}

int n, m, val[N];
int ans = 0x3f3f3f3f;

int Q[N], head, tail;

signed main() {
    read(n), read(m);
    for (register int i = 1; i <= n; ++i) read(val[i]);
    
    head = 0, tail = -1;
    for (register int i = n; i >= 1; --i) {
        while (head <= tail && Q[head] > i + m) ++head;
        while (head <= tail && val[Q[tail]] <= val[i]) --tail;
        Q[++tail] = i;
        if (i <= n - m) ans = min(ans, val[Q[head]]);
    }
    
    printf("%d", ans);
    return 0;
}
```

## 后记

遇到贪心操作的题目，考虑答案的操作序列，然后对这个操作序列邻项交换。

二分答案，能够成为答案的和不能成为答案的，看做 $1$ 和 $0$，分别考虑。

---

## 作者：佬头 (赞：3)

## Description
一个长为 $n$ 的序列 $a_{1\dots n}$ 要进行两种操作共 $n-1$ 次，每次操作后序列长度会缩短 $1$：
- 操作一，$\forall i\in[1,l),a_i'=\max(a_i,a_{i+1})$；
- 操作二，$\forall i\in[1,l),a_i'=\min(a_i,a_{i+1})$。

你只能进行**至多** $m$ 次操作一，且可以任意安排操作顺序，求最终剩余的数 $a_1$ 的最大值。

## Solution
考虑先后进行两种操作的差别：
- 先进行操作一，$a_{i1}\gets\min(\max(a_i,a_{i+1}),\max(a_{i+1},a_{i+2}))$；
- 先进行操作二，$a_{i2}\gets\max(\min(a_i,a_{i+1}),\min(a_{i+1},a_{i+2}))$。

接着分类讨论：
- 当 $a_{i+1}\le\min(a_i,a_{i+2})$ 时，$a_{i1}\gets \min(a_i,a_{i+2}),a_{i2}\gets a_{i+1}$；
- 当 $a_{i+1}\ge\max(a_i,a_{i+2})$ 时，$a_{i1}\gets a_{i+1},a_{i2}\gets \max(a_i,a_{i+2})$；
- 否则，$a_{i1}\gets a_{i+1},a_{i2}\gets a_{i+1}$。

可以发现 $a_{i1}\ge a_{i2}$ 始终成立，因此考虑优先进行 $m$ 次操作一，再进行操作二。因而对于前 $n-m$ 个数有 $a_i'=\max(a_i,\dots,a_{i+m})$，最后答案是 $\min(a_1',\dots,a_{n-m}')$。

从后往前遍历序列 $a$，用单调队列维护连续 $m+1$ 个数的最大值，取前 $n-m$ 个数时单调队列队首的最小值即可。时间复杂度 $\mathcal O(n)$。

## Code
```cpp
#include <iostream>
using namespace std;
const int N = 1000006;
int n, m, a[N], q[N], front = 1, back, minn = 1e9;
int read(){
	int x = 0;
	char a = getchar();
	while(a < '0' || '9' < a) a = getchar();
	while('0' <= a && a <= '9') x = (x << 1) + (x << 3) + (a ^ 48), a = getchar();
	return x;
}
void write(int x){
	if(x > 9) write(x / 10);
	putchar(x % 10 | 48);
}
int main(){
	n = read(), m = read();
	for(int i = 1; i <= n; ++ i) a[i] = read();
	for(int i = n; i >= 1; i --){
		while(front <= back && a[q[back]] <= a[i]) back --;
		q[++ back] = i;
		if(i + m <= n){
			while(q[front] > i + m) ++ front;
			if(a[q[front]] < minn) minn = a[q[front]];
		}
	}
	write(minn);
	return 0;
}
```

---

## 作者：Kotobuki_Tsumugi (赞：3)

手动模拟一下过程，发现操作一删去了序列中一个最小的数，操作二删去了一个最大的数。那我们肯定不希望大的数被删去，我们尽量先删小数。那么我们有了一个贪心思路。

先使用 $m$ 次操作一。保证大数（尽可能）不被删去。最后我们使用 $n-m-1$ 次操作二。

为什么这样说是正确的？观察到，当我们使用完操作一时，接下来序列会不断缩短，直至只有一个最小的数。那么这个数就是答案。换言之，我们要让序列中的最小值最大。

直接模拟贪心将超时。我们考虑优化。每一次操作一，是将某个元素替换为自己与下一个元素中的大者。那么 $m$ 次操作一，就是讲第 $i$ 个元素替换为 $\left [i,i+m\right ]$ 中的最大值，这实际上是一个 RMQ 问题。我们可以用线段树、树状数组等数据结构解决。

使用完 $m$ 次操作一，答案就是剩下序列中的最小值。

赛时采用线段树写法通过。代码如下。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e6+10;
const int INF = 1e9;
int n,m,a[N],b[N][2],now = 1,tree[N<<2];
inline int ls(int p){return p<<1;}
inline int rs(int p){return (p<<1)|1;}
void Build(int s,int t,int p){
	if(s == t){
		tree[p] = a[s];
		return;
	}
	int mid = s+((t-s)>>1);
	Build(s,mid,ls(p));
	Build(mid+1,t,rs(p));
	tree[p] = max(tree[ls(p)],tree[rs(p)]);
}
int Getnum(int l,int r,int s,int t,int p){
	if(l <= s && t <= r) return tree[p];
	int mid = s+((t-s)>>1),ans = -INF;
	if(l <= mid) ans = max(ans,Getnum(l,r,s,mid,ls(p)));
	if(r > mid)  ans = max(ans,Getnum(l,r,mid+1,t,rs(p)));
	return ans;
}
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin>>n>>m;
	for(int i = 1;i<=n;i++)
		cin>>a[i],b[i][now] = a[i];	
	Build(1,n,1);
	for(int i = 1;i<=n-m;i++)
		b[i][1] = Getnum(i,i+m,1,n,1);
	int ans = INF; 
	for(int i = 1;i<=n-m;i++)
		ans = min(ans,b[i][1]);
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：ICU152_lowa_IS8 (赞：3)

和官方题解内核貌似是相同的，但实现不太一样，算是殊途同归吧。

首先感性理解，一开始用操作一可以让整个数组尽量变大，后面用操作二的时候也能保持尽量大。

当然感性理解肯定是不行的，这里给一种作者的证明：

最后一定会有一连串的操作二（次数可能为零），显然，这一连串的操作二相当于给整个数组取最小值。

于是我们的操作序列可以分为两部分：

1. 从第一次操作直到最后一次操作一；
2. 对整个数组取最小值。

显然第一段操作完成后的数列一定要尽可能大。那么直接全部把操作一放在前面就行。

那么如何求出 $m$ 次操作一后的序列？

先看一个图，假设橙色方块为最大值，那么进行一次操作一之后，红色的值会变成和橙色相同，相当于橙色被向左“拖拽”了一次。

![](https://cdn.luogu.com.cn/upload/image_hosting/bfumm2hw.png)

显然，对于元素 $a_i$，进行 $m$ 次操作，所有可能（即先不管大小）覆盖到的元素为 $a_{i+1}\sim a_{i+m}$。

至于最后的结果，显然是所有可覆盖元素（包括 $a_i$）的最大值。求区间最大值显然可以用线段树解决。

代码：


```
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[1000005];
struct tree{
	int val,tag;
}tree[1000005<<2];
//int a[100005];
inline int ls(int p){
	return p<<1;
}
inline int rs(int p){
	return p<<1|1;
}
inline void pushup(int p){
	tree[p].val=max(tree[ls(p)].val,tree[rs(p)].val);
}
inline void build(int p,int l,int r){
	if(l==r){
		tree[p].val=a[l];
		return;
	}
	int mid=l+r>>1;
	build(ls(p),l,mid);
	build(rs(p),mid+1,r);
	pushup(p);
}
inline int query(int p,int l,int r,int ql,int qr){
	if(l>qr||r<ql)return 0;
	if(qr>=r&&ql<=l){
		return tree[p].val;
	}
	if(l==r)return tree[p].val;
//	pushdown(p,l,r);
	int mid=l+r>>1;
	return max(query(ls(p),l,mid,ql,qr),query(rs(p),mid+1,r,ql,qr));
}
signed main(){
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	build(1,1,n);
	for(int i=1;i<=n-m;i++){
		a[i]=query(1,1,n,i,i+m);
	}
	int ans=INT_MAX;
	for(int i=1;i<=n-m;i++){
		ans=min(ans,a[i]);
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Larryyu (赞：2)

## _Description_

给定一个长为 $n$ 的序列 $a_{1\dots n}$，需要对它进行两种操作共 $n-1$ 次。

对一个长度为 $l$ 的序列 $b_{1\dots l}$ 进行一次操作将会把序列变为一个长为 $l-1$ 的序列 $c_{1\dots l-1}$：

- 操作一中，$\forall i\in[1,l),c_i=\max(b_i,b_{i+1})$；
- 操作二中，$\forall i\in[1,l),c_i=\min(b_i,b_{i+1})$。

给定整数 $m$，你只能进行**至多** $m$ 次操作一。进行 $n-1$ 次操作后序列 $a$ 的长度变为 $1$。你可以任意安排操作的顺序，求最终剩余的数 $a_1$ 的最大值。

## _Solution_

比第一题简单。

两个关键性质就是操作一做满 $m$ 次最优，且做完操作一再做操作二。

我们发现操作一每次一定会把当前最小值消去，使最大值数量变多，操作二一定会把当前最大值消去，使最小值数量变多。

先做操作一则能抬高数值下限，做满 $m$ 次使最小值最大，最大值数量最多，此种决策最优。

而在一次操作一前做操作二，不仅会使最小值变多，还会降低数值上限，不优于上种决策。

确定了操作顺序后就完了吗？并不是，还需要找到最小值，而直接模拟是 $O(n^2)$ 的。

发现在一次操作一后可能不止最小值会消去，如 $[1,3,2,3]$ 做一次操作一变成 $[3,3,3]$。

又发现一个数会被左右两边第一个比它大的数 $a_l,a_r$ 消去，会在 $r-1-l$ 次操作一后消失。

然后在在所有不能在 $m$ 次操作一之内消去的数中取最小值即可。

用单调栈找 $a_l,a_r$ 可 $O(n)$ 做完。

## _Code_

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m;
int a[1000010];
int l[1000010],r[1000010];
stack<int> s;
int main(){
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		cin>>a[i];
	}
	for(int i=1;i<=n;i++){
		while(s.size()&&a[s.top()]<=a[i]){
			s.pop();
		}
		l[i]=s.size()?s.top():0;
		s.push(i);
	}
	while(s.size()) s.pop();
	for(int i=n;i>=1;i--){
		while(s.size()&&a[s.top()]<=a[i]){
			s.pop();
		}
		r[i]=s.size()?s.top():n+1;
		s.push(i);
	}
	int minn=1e9;
	for(int i=1;i<=n;i++){
		if(r[i]-1-l[i]>m){
			minn=min(minn,a[i]);
		}
	}
	cout<<minn;
	return 0;
}
```

---

## 作者：sansesantongshun (赞：2)

~~这道题本蒟蒻胡错很多遍结论才过的，快来踩爆本蒟蒻。~~

首先我们读题后发现想要让答案更大就要尽可能选操作一，似乎是个简单贪心，但操作一的次数却有限制，所以我们需要换一种思路。

我们发现如果有连续 $k$ 个大于等于 $x$ 的数，那么进行 $k$ 次操作二后，将不存在大于等于 $x$ 的数，使答案更劣。

而操作一会减少小于 $x$ 的数，使大于等于 $x$ 的数连在一起，而且可能会在两边增加大于等于 $x$ 的数，使连续大于等于 $x$ 的数的数量大大增加，抵御更多的操作二。

所以得出结论：先进行操作一，后进行操作二，答案是最优的。

得出结论后，我们发现 $n$ 个数的数列进行 $m$ 次操作一时，新数列第一项是第 $1$ 项到第 $m+1$ 项的最大值，第二项是第 $2$ 项到第 $m+2$ 项的最大值，依此类推。

等等，这不就是[滑动窗口](https://www.luogu.com.cn/problem/P1886)吗？

然后就很容易了。取新数列最小值即可。

上代码：


```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[1000005],ans=0x7fffffff;
deque<int> d;//单调队列
int main()
{
	cin>>n>>m;
	for (int i=1;i<=n;++i)
	{
		scanf("%d",&a[i]);
		while (!d.empty() && a[d.back()]<=a[i])
		d.pop_back();//弹出较小的元素
		d.push_back(i);
		while (d.front()<i-m)
		d.pop_front();//弹出不符合条件的元素
		if (i>m)
		ans=min(ans,a[d.front()]);//取最小值
	}
	cout<<ans;
}
```

---

## 作者：Exp10re (赞：2)

官方题解给出了先进行操作一一定更优的证明，本篇题解将**在此基础上**给出另一种不同于官方题解的实现。

## 解题思路

考虑在某个状态下，对数列 $a_{1,\cdots,n}$ 连续进行 $k$ 次操作一之后数列的形态：手推可以发现，对于进行连续 $k$ 次操作一之后的数列 $b_{1,\cdots,n-k}$，有 $b_i=\max\limits_{i\leq j \leq i+k-1} a_j$。

而在某个状态下一直进行操作二直到只剩一个数，这个数必然是当前数列的最小值。

故考虑使用 ST 表维护对原始数列进行 $m$ 次操作一之后的数列。总计 $n-m+1$ 次查询，时间复杂度 $O(n\log n)$。

---

## 作者：_LTC_Augenstern_ (赞：1)

对于此问题，我们考虑两种操作：
- 操作一：肯定是多多益善，如果只用这种操作，肯定保留下来的是最大值；
- 操作二：每次操作一定会让该区间中最大值的数少一个。

既然如此，那么给出的至多 $m$ 次操作一肯定是要全部用上的。

此时，我们考虑一个问题：如果一个数 $x$ 能够成为经过这 $n-1$ 次操作所剩下来的数，那么另一个数 $y(y<x)$ 是否能成为经过这 $n-1$ 次操作所剩下来的数呢？

肯定是可以的，因为只要将其中包含 $x$ 的一次操作一和不包含 $x$ 的操作二调换一下，那么就可以构造出 $y$。也就是说，这种操作所剩的结果具有单调性，可以考虑二分。

那么，如何判断一个数是否能够被构造出来呢？我们知道每次操作都会使数列少一个数，而操作二只会将所有的数中取最小值，所以我们把数列中的数分成两类：
1. 小于想构造的数的数
2. 大于等于想构造的数的数

因为操作二只会把所有数的最小值取出来，所以我们现在要考虑怎么把小于想构造的数的这些数全部通过 $m$ 次操作一搞定，所以我们不得不使比想构造的数小的所有数连续的个数小于等于 $m$。

具体实现见代码：
```cpp
#include <bits/stdc++.h>
#define IOS ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#define endl "\n"
using namespace std;
typedef long long ll;
int n, m, tmp;
vector<int> nums;
//<=
bool chck(int t)
{
    int now = 0, ret = 0;
    for(auto it : nums)
    {
        if(it < t) now ++;
        else ret = max(ret, now), now = 0;
    }
    ret = max(ret, now);
    return ret <= m;
}
int main()
{
    IOS;
    cin >> n >> m;
    for(int i = 0; i < n; i ++) cin >> tmp, nums.push_back(tmp);
    int l = 1, r = 1e9;
    int ans = 0;
    while(l <= r)
    {
        int mid = (l + r) >> 1;
        if(chck(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    cout << ans;
    return 0;
}
```

---

## 作者：liuli688 (赞：1)

### 思路
考虑贪心。先将 $m$ 次操作一用完后全部用操作二。

证明：

- 设当前使用了 $i$ 次操作一，且 $i < m$。

- 若当前数组中最小值的下标为 $p$（即 $a_p$ 最小），则对于 $a_p$，$a_{p + 1}$，$a_{p + 2}$，考虑使用两种操作：
  - 操作一：一次操作一后变为 $\{a_{p + 1}, \max(a_{p + 1}, a_{p + 2})\}$，即使下一次使用操作二也是 $\max(a_{p + 1}, a_{p + 2})$。
  - 操作二：一次操作二后变为 $\{a_p, \min(a_{p + 1}, a_{p + 2})\}$，即使下一次使用操作一也是 $\min(a_{p + 1}, a_{p + 2})$。

- 可见，在操作次数相等的情况下先用操作一比先用操作二更优。

- 同理，该证明也对 $\forall p, a_p \le a_{p + 1}, a_p \le a_{p + 2}$ 的$p$ 适用。若不存在这样的 $p$，只需找到（并且一定存在）一个 $p$，使 $a_p \le a_{p - 1}, a_p \le a_{p - 2}$。

证毕。

所以，只需每次暴力更新数组即可拿到 $40\ \text{pts}$。

接下来需要优化。场上想出来了乱搞的单调队列优化：

由于先使用完 $m$ 次操作一，则 $m$ 次操作后 $a_i$ 的值为原 $a$ 数组中的 $\displaystyle\max _ {j = i} ^ {i + m} a_j$。

那么，求 $m$ 次操作后的 $a$ 就和 [滑动窗口 /【模板】单调队列](https://www.luogu.com.cn/problem/P1886) 很像了：这不就是一个长为 $m$ 的滑动窗口嘛！

接下来的事就很简单了。剩下的全用操作二，所以最后遍历一遍找 $\min$ 即可。

时间复杂度 $O(n)$。
### 代码：

```cpp
#include <bits/stdc++.h>

#define reg register

//单调队列
std::deque<int> dq;
std::vector<int> sliding_window(int a[], int n, int m)
{
	std::vector<int> res;
	for (reg int i = 1; i <= n; ++i)
    {
		while (dq.size() and a[dq.back()] <= a[i])
            dq.pop_back();
        dq.push_back(i);
        while (dq.size() and dq.front() <= i - m)
            dq.pop_front();
        if (i >= m)
        	res.push_back(a[dq.front()]);
    }
    return res;
}

constexpr int N = 1e6 + 1;
int n, m, a[N], ans = (1u << 31) - 1;
std::vector<int> res;

signed main()
{
	scanf("%d%d", &n, &m);
	for (reg int i = 1; i <= n; ++i)
		scanf("%d", a + i);
        //先执行操作一
	res = sliding_window(a, n, m + 1);
        //操作二
	for (reg auto i : res)
		ans = std::min(ans, i);
	printf("%d", ans);
	return 0;
} 
```

---

## 作者：I_will_AKIOI (赞：1)

可以发现先用完这 $m$ 次操作一肯定不劣，因为你先用操作二，那么最大值可能就被消掉了。接着考虑用完这 $m$ 次操作后，剩下的 $n-m$ 次操作完的答案肯定是 $m$ 次操作后 $a$ 的最小值。所以问题就变成了求 $m$ 次操作后 $a$ 的最小值。

求出最小值比较困难，所以考虑枚举 $a$ 数组的每一个元素，看看哪些元素可能成为最小值。

然后手搓几个样例玩一下，其中我们把连续的同一个数字叫做块。发现对于一个块，如果他左边和右边的块都比他小，那么一次操作一之后当前块的长度会 $+1$。如果都比他大，那么块长 $-1$，否则长度不变。因此一个块和他左右的块有关。

我们知道一个块可能是最小值，需要满足他没有被消掉，所以只需要判断这个块是否会被消掉即可。由于一个块和他左右的块有关，所以我们考虑求出在当前块的左边最近的比他大的块，右边同理，这个过程可以用两个单调栈求出。我们设当前块长度为 $len$，求出的左边的块距离为 $x$，右边为 $y$。

因为在当前块没有碰到左边块和右边块之前，他的长度都会 $+1$，所以长度会变为 $len+\min(x,y)$。接着在碰到一个块之后，碰到第二个块之前，长度不变，碰到第二个块之后到 $m$，长度会 $-1$。所以当前块 $m$ 次操作后的长度就是 $len+\min(x,y)-[m-\max(x,y)]$，判断他是否大于 $0$ 即可，最后对所有可能成为答案的值取最小值。

```cpp
#include<bits/stdc++.h>
#define N 1000005
using namespace std;
int n,m,len,l=1,ans=INT_MAX,a[N],s[N],pre[N],nxt[N];
vector<pair<int,int> >v;
int main()
{
  ios::sync_with_stdio(0);
  cin>>n>>m;
  for(int i=1;i<=n;i++) cin>>a[i];
  for(int i=1;i<n;i++) if(a[i]!=a[i+1]) v.push_back({l,i}),l=i+1;
  v.push_back({l,n});
  a[n+1]=INT_MAX,a[0]=INT_MIN;
  for(int i=0;i<=n+1;i++)
  {
    while(len&&a[s[len]]<=a[i]) len--;
    pre[i]=s[len];
    s[++len]=i;
  }
  len=0;
  for(int i=n+1;i>=0;i--)
  {
    while(len&&a[s[len]]<=a[i]) len--;
    nxt[i]=s[len];
    s[++len]=i;
  }
  for(auto now:v)
  {
    int x=now.first,y=now.second,nx=pre[x],ny=nxt[y];
    if(y-x+1+min(x-nx-1,ny-y-1)>m-max(x-nx-1,ny-y-1)) ans=min(ans,a[x]);
  }
  cout<<ans;
  return 0;
}
```

---

