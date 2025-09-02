# [ARC173E] Rearrange and Adjacent XOR

## 题目描述

给定一个长度为 $N$ 的非负整数列 $A=(A_1,A_2,\dots,A_N)$。对于该整数列，进行如下操作 $N-1$ 次，最终得到长度为 $1$ 的整数列。

- 设 $n$ 为 $A$ 的当前长度。首先，可以任意重新排列 $A$ 中的元素。然后，将 $A$ 替换为长度为 $n-1$ 的非负整数列 $(A_1\ \oplus\ A_2,\ A_2\ \oplus\ A_3,\ \dots,\ A_{n-1}\ \oplus\ A_n)$。

其中，$\oplus$ 表示按位异或（XOR）运算。

经过 $N-1$ 次操作后，得到的长度为 $1$ 的整数列中的元素记为 $X$。请你求出 $X$ 可能取得的最大值。

按位异或（XOR）运算的定义如下：对于非负整数 $A, B$，$A\ \oplus\ B$ 的二进制表示中，第 $2^k$ 位（$k\geq 0$）的数值为：若 $A, B$ 的二进制表示在第 $2^k$ 位上仅有一个为 $1$，则该位为 $1$，否则为 $0$。

例如，$3\ \oplus\ 5 = 6$（二进制表示为：$011\ \oplus\ 101 = 110$）。
一般地，$k$ 个非负整数 $p_1, p_2, \dots, p_k$ 的按位异或为 $(\dots((p_1\ \oplus\ p_2)\ \oplus\ p_3)\ \oplus\ \dots\ \oplus\ p_k)$，并且可以证明，这一结果与 $p_1, p_2, \dots, p_k$ 的顺序无关。

## 说明/提示

### 限制条件

- $2 \leq N \leq 100$
- $0 \leq A_i < 2^{60}$
- 输入的所有数均为整数

### 样例解释 1

通过如下 $3$ 次操作，可以将 $A$ 变为 $A=(7)$。

- 第 $1$ 次操作，将 $A=(1,2,3,4)$ 重新排列为 $(3,1,4,2)$。$A$ 被替换为 $(3\ \oplus\ 1,\ 1\ \oplus\ 4,\ 4\ \oplus\ 2) = (2,5,6)$。
- 第 $2$ 次操作，将 $A=(2,5,6)$ 重新排列为 $(2,6,5)$。$A$ 被替换为 $(2\ \oplus\ 6,\ 6\ \oplus\ 5) = (4,3)$。
- 第 $3$ 次操作，将 $A=(4,3)$ 重新排列为 $(4,3)$。$A$ 被替换为 $(4\ \oplus\ 3) = (7)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
1 2 3 4```

### 输出

```
7```

## 样例 #2

### 输入

```
13
451745518671773958 43800508384422957 153019271028231120 577708532586013562 133532134450358663 619750463276496276 615201966367277237 943395749975730789 813856754125382728 705285621476908966 912241698686715427 951219919930656543 124032597374298654```

### 输出

```
1152905479775702586```

# 题解

## 作者：鲤鱼江 (赞：3)

好题，有不少 trick 可以吸收。

我们设集合 $S$ 表示若 $x\in S$，则 $a_x$ 影响了答案。

发现我们可以任意重排 $S$，所以直觉上来讲一个 $S$ 是否合法只与 $|S|$ 有关，手摸几组发现 $|S|$ 必为偶数。

发现有更强的限制，对于 $n\bmod 4=2,n\ne 2$，$S$ 不能为全集否则无所谓，考虑归纳证明。

首先 $n$ 为奇数明显不可能是全集。

首先进行一次操作得到 $a_1\oplus a_2,a_2\oplus a_3,\dots,a_{n-1}\oplus a_n$，记 $b_i=a_{i}\oplus a_{i+1}$。

+ $n\bmod 4=0$，此时我们需要导出 $b_1,b_3,b_5,\dots b_{n-1}$ 共 $\frac n2$ 个元素作为最后答案，而 $\frac n2$ 明显是偶数，有归纳可知正确。
+ $n\bmod 4=2$，此时必然要扣掉两个元素，因为 $\frac n2$ 是奇数。

综上可证。

但是又有一个问题了，如何保证在取出偶数个数的情况下得到异或最大值呢？令 $b_i=a_{i+1}\oplus a_1$，那么直接求 $b$ 的异或最大值就行了。

那不保证能选全集又怎么做呢，每次从线性基里删一个元素就行了，这个可以使用前后缀线性基合并做到。

是 $O(n\log^2 V)$，可能比较难看。

但是 $n=100$ 我为啥不暴力插入？

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;

const int B=60;
const int N=110;
struct Base{
	int v[N];
	inline void ins(int x){
		for(int i=B;~i;--i){
			if((x>>i)&1){
				if(!v[i]){v[i]=x;return ;}
				else x^=v[i];
			}
		}
	}
	inline int ask(){
		int res=0;
		for(int i=B;~i;--i){
			res=max(res,res^v[i]);v[i]=0;
		}
		return res;
	}
}b;
int n,a[N],x;

signed main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>x;--n;for(int i=1;i<=n;++i){cin>>a[i];a[i]^=x;}
	if((n+1)%4!=2||n==1){
		for(int i=1;i<=n;++i) b.ins(a[i]);
		cout<<b.ask()<<endl;
	}else{
		int res=0;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j) if(i!=j) b.ins(a[j]);
			res=max(res,b.ask());
		}
		cout<<res<<endl;
	}
	return 0;
}
```

---

## 作者：EuphoricStar (赞：2)

不妨考虑最后的结果可以成为哪些 $a_i$ 的组合。为了方便分析，我们令 $a_i = 2^{i - 1}$。

进行一次操作后，所有 $\text{popcount}(a_i)$ 都为偶数。所以一个 $x \in [0, 2^n - 1]$ 能被生成出来的必要条件是 $\text{popcount}(x)$ 为偶数。

然后通过打表可以发现：

- 对于 $n = 2$ 或 $n \bmod 4 \ne 2$，任意一个 $x \in [1, 2^n - 1]$ 且 $\text{popcount}(x)$ 为偶数的 $x$ 都能被生成出来。
- 对于 $n \ne 2$ 且 $n \bmod 4 = 2$，任意一个 $x \in [1, 2^n - 2]$ 且 $\text{popcount}(x)$ 为偶数的 $x$ 都能被生成出来。

考虑归纳证明。因为 $a$ 中元素可以重排，所以不妨只考虑 $2^{2k} - 1$（$k \ge 1$）能否被生成出来：

- $k$ 为偶数，做一次操作后序列变成 $a = [2^0 + 2^1, 2^1 + 2^2, \ldots, 2^{n - 2} + 2^{n - 1}]$。因为 $k$ 为偶数，所以最后剩下的值可以为 $a_1 \oplus a_3 \oplus \cdots \oplus a_{2k - 1}$，所以成立。
- $k$ 为奇数，不妨让一开始的 $a$ 的前 $2k + 1$ 个元素为 $2^0, 2^1, \ldots, 2^{2k - 2}, 2^{n - 1}, 2^{2k - 1}$（要求 $2k < n$）。做一次操作后，因为 $k + 1$ 为偶数且当 $n - 1 > 2$ 时 $k + 1 \ne n - 1$，所以最后剩下的值可以是 $a_1 \oplus a_3 \oplus \cdots \oplus a_{2k - 1} \oplus a_{2k}$，所以成立。

于是现在问题变成了：选一个 $a$ 中的包含偶数个元素的子集，最大化异或和，同时还可能有不能选全集的限制。

对于没有限制的情况，发现 $a$ 中的任意一个包含偶数个元素的子集的异或和都可以表示成 $a_1 \oplus a_2, a_1 \oplus a_3, \ldots, a_1 \oplus a_n$ 的一个子集的异或和。所以直接把这些数塞进一个线性基，然后查询即可。

对于有限制的情况，我们不妨钦定一个数不被选，删掉这个数，就转化成了没有限制的情况。

时间复杂度 $O(n^2 \log V)$。

[code](https://atcoder.jp/contests/arc173/submissions/51675340)

---

## 作者：Drind (赞：1)

### 题目解析

给定一个数组 $a$，每次重排之后相邻两位异或形成一个长度减一的新数组，以此类推，求最后剩下的一个数的最大值。

我们发现就是求怎样的 $a$ 能组合成最后的数，在这里我们记 $12$ 为 $a_1\oplus a_2$，类似的表达同理。

我们手摸一下就可以发现答案貌似只能由偶数个 $a$ 组成，我们考虑证明。

因为 $a$ 可以重排，所以我们可以把问题简化成能否组合出一段前缀长度为偶数。

考虑归纳法，当答案被 $4k$ 个 $a$ 组成时，我们直接对 $a$ 数组操作，变成 $12,23,34,\dots ,(n-1)n$，然后就可以选中第 $1$，$3\dots 2k-1$ 这若干个数，因为个数为偶数，所以可以组合出。

当答案被 $4k+2$ 个 $a$ 组成时，刚才的策略就失效了，因为需要选出奇数个数，所以我们要从别的地方借一个数过来用，先将 $a$ 数组重排成 $1,2,3,4,5,\dots ,4k+1,n,4k+2,\dots$，也就是借了一个 $n$ 过来，然后进行操作，就可以保证需要选中偶数个数了。因为这个方法需要借，所以必须保证 $4k-2\lt n$。

所以就是如果 $n$ 除以 $4$ 余二就不能选全集，并且要选出偶数个数使得异或起来最大，这个问题我们使用线性基解决。

但是线性基没法只选偶数个数，所以我们魔改一下插入线性基的数，把除 $a_1$ 以外的数都异或上 $a_1$ 再插进去，就保证如果选出奇数个数，一定会多一个 $a_1$，而选出偶数个数就没有 $a_1$ 了。

如果不能选全集，就做 $n$ 次，对于每次少插一个数进去就行。

复杂度 $n^2\times 60$，$n$ 很小完全能跑。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10;

struct node{
	int a[N];
	void init(){
		memset(a,0,sizeof a);
	}
	void insert(int x){
		for(int i=63;i>=0;i--){
			if(x&(1ll<<i)){
				if(a[i]==0){
					a[i]=x;
					break;
				}
				else x^=a[i];
			}
		}
	}
	int query(){
		int ans=0;
		for(int i=63;i>=0;i--){
			ans=max(ans,ans^a[i]);
		}
		return ans;
	}
	
}tr;

int a[N];

void fake_main(){
	int n; cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	if(n==2||n%4!=2){
		for(int i=2;i<=n;i++) tr.insert(a[1]^a[i]);
		cout<<tr.query()<<"\n";
	}else{
		int ans=0;
		for(int i=2;i<=n;i++){
			tr.init();
			for(int j=2;j<=n;j++){
				if(i==j) continue;
				tr.insert(a[1]^a[j]);
			}
			ans=max(ans,tr.query());
		}
		cout<<ans<<"\n";
	}
}

signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	int t; t=1;
	while(t--) fake_main();
}
```

---

## 作者：wxqwq (赞：0)

[洛谷传送门](https://www.luogu.com.cn/problem/AT_arc173_e)

题意在洛谷翻译中写的很清楚了。

---

首先第一部分其他题解已经写的很清楚了，这里就简单说明。考虑最后答案包含哪些元素，设其包含集合 $S$ 内的元素，则一定有 $|S|$ 是偶数。

然后如果 $n\neq 2$ 且 $n \bmod 4 = 2$，则 $S$ 不能为全集，反之就无所谓。

所以如果 $S$ 可以为全集，我们就把 $i\ge 2,\ a_1\oplus a_i$ 丢进线性基中，然后求这里面的最大值就行，容易发现所得到的集合大小都是偶数。这部分的复杂度是 $O(n\log V)$ 的。

反之我们需要枚举某个元素不在集合中，那还是记录 $a_1\oplus a_i$，并维护前缀线性基和后缀线性基，枚举每个 $i\ge 2$，相当于合并一个前缀和后缀的线性基。直接这样做复杂度是 $O(n\log^2V)$ 的。

不过我们发现前缀线性基一共只有 $O(\log V)$ 种，这是因为线性基中最多只会加入 $O(\log V)$ 次元素，后缀同理。对于一个前缀线性基，维护他的标号为这个线性基加入数字的次数，后缀同理，显然前缀标号递增，后缀标号递减，所以最多只会有 $O(\log V)$ 次本质不同的前后缀线性基合并。维护每个前缀线性基是哪一种，然后再做 $O(n)$ 次最大值查询即可。

时间复杂度 $O(n\log V+\log^3V)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define gmx(a,b) (a=max(a,b))
#define fil(a,x) memset(a,x,sizeof(a))
#define rep(i,a,b) for(int i=(a);i<=(b);i++)
#define per(i,a,b) for(int i=(a);i>=(b);i--)
typedef unsigned long long ull;
const int N=110,M=64,D=61;

int n;ull a[N];

struct LB {
	ull d[M];
	LB() {fil(d,0);}
	bool ins(ull x) {
		per(i,D,0) if(x>>i&1) {
			if(!d[i]) return d[i]=x;
			else x^=d[i];
		}
		return 0;
	}
	ull qry() {
		ull res=0;
		per(i,D,0) gmx(res,res^d[i]);
		return res;
	}
};
int ip[N],is[N];
bool st[M][M];
LB pre[M],suf[M],f[M][M];
LB merge(LB a,LB b) {
	per(i,D,0) if(b.d[i]) a.ins(b.d[i]);
	return a;
}

signed main()
{
	scanf("%d",&n); rep(i,1,n) scanf("%llu",&a[i]);
	if(n==2 || n%4!=2) {
		LB t; rep(i,2,n) t.ins(a[1]^a[i]);
		printf("%lld\n",t.qry()); return 0;
	}
	LB t;
	rep(i,2,n) {
		ip[i]=ip[i-1];
		if(t.ins(a[1]^a[i])) pre[++ip[i]]=t;
	} fil(t.d,0);
	per(i,n,2) {
		is[i]=is[i+1];
		if(t.ins(a[1]^a[i])) suf[++is[i]]=t;
	}
	rep(i,2,n) st[ip[i-1]][is[i+1]]=1;
	rep(i,0,ip[n]) rep(j,0,is[2]) if(st[i][j]) f[i][j]=merge(pre[i],suf[j]);
	ull ans=0;
	rep(i,2,n) gmx(ans,f[ip[i-1]][is[i+1]].qry());
	printf("%lld\n",ans);

	return 0;
}

```

实际上也可以把序列复制一份，转为查询区间异或线性基，然后用 [ABC223H](https://www.luogu.com.cn/problem/AT_abc223_h) 的方法，使用时间戳线性基做到 $O(n\log V)$。

---

## 作者：DaiRuiChen007 (赞：0)

[Problem Link](https://www.luogu.com.cn/problem/AT_arc173_e)

**题目大意**

> 给定 $a_1\sim a_n$，一次操作可以把所有 $a$ 重排，然后把 $a$ 替换成 $a'_i=a_i\oplus a_{i+1}(1\le i<n)$，最大化 $n-1$ 次操作后序列中剩下的元素。
>
> 数据范围：$n\le100,a_i<2^{60}$。

**思路分析**

考虑最终的元素是可能 $a$ 的哪些子集 $S$ 的异或和。

由于我们可以进行任意重排，因此一个子集是否合法只和 $|S|$ 有关。

由于异或不改变 $|S|$ 奇偶性，且我们至少进行一次操作，因此 $|S|$ 一定是偶数。

考虑如何构造，设 $S=a_1\sim a_{2k}$。

- 如果 $k$ 是偶数，那么直接用原排列，我们就要在 $n-1$ 个元素中导出 $a'_1,a'_3\sim a'_{2k-1}$ 这 $k$ 个元素的异或和。
- 如果 $k$ 是奇数，那么构造 $a_1\sim a_{2k-1},a_n,a_{2k},\dots$，我们要在 $n-1$ 个元素中导出 $a'_1,a'_3\sim a'_{2k-1},a'_{2k}$ 这 $k+1$ 个元素的异或和。

容易发现无法构造当且仅当 $k$ 是奇数时 $2k=n$，且 $n>2$。

因此 $4\mid n$ 或 $n=2$ 时，$S$ 可以是所有 $a_1\sim a_n$ 大小为偶数的子集，把所有 $a_1\oplus a_i$ 插入线性基后查询即可。

否则 $S$ 是所有 $a_1\sim a_n$ 大小为偶数且不为全集的子集，枚举一个 $a_i$ 删除，然后做上一部分的过程。

可以预处理 $a_1\oplus a_i$ 的前后缀线性基，这样只要做 $\mathcal O(n)$ 次线性基合并。

时间复杂度 $\mathcal O(n\log^2V)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int MAXN=105;
struct LB {
	ll a[60];
	LB() { memset(a,0,sizeof(a)); }
	void ins(ll x) {
		for(int k=59;~k;--k) if(x>>k&1) {
			if(!a[k]) return a[k]=x,void();
			else x^=a[k];
		}
	}
	ll qry() {
		ll x=0;
		for(int k=59;~k;--k) x=max(x,a[k]^x);
		return x;
	}
	friend LB operator +(LB x,LB y) {
		for(int k=59;~k;--k) if(y.a[k]) x.ins(y.a[k]);
		return x;
	}
}	B,e[MAXN];
ll a[MAXN];
signed main() {
	int n; scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%lld",&a[i]);
	if(n==2||n%4==0) {
		for(int i=2;i<=n;++i) B.ins(a[1]^a[i]);
		return printf("%lld\n",B.qry()),0;
	}
	for(int i=3;i<=n;++i) B.ins(a[i]^a[2]);
	ll ans=B.qry();
	B=LB();
	for(int i=n;i>=2;--i) e[i]=e[i+1],e[i].ins(a[1]^a[i]);
	for(int i=2;i<=n;++i) {
		ans=max(ans,(B+e[i+1]).qry()),B.ins(a[1]^a[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：intel_core (赞：0)

考虑 $n=3$ 的情况，假设已经排好顺序，不难发现答案就是 $A_1\oplus A_3$。

进一步，考虑 $n=4$ 的情况，相当于就是从 $A_1\oplus A_2,A_2\oplus A_3,A_3\oplus A_4$ 中选择两个异或起来最大，发现就是 $A_1\oplus A_2\oplus A_3\oplus A_4$ 和 $A_i\oplus A_j(i<j)$ 的最大值。

注意到在上述情况中答案一定是偶数个数异或起来得到的，因为奇数个数异或起来得到的数一定无法拆分成若干对数的异或和。

不难发现对于大部分 $k\le n$ 为偶数，最终剩下的数都可以是 $k$ 个数的异或和。只有 $n=4m+2(m>0)$ 时无法取到 $k=n$。

考虑归纳证明 $k<n$ 时的结论：初始时可以选定 $k(k<n)$ 个数，使得它们的异或和为答案。

* $n=2,3,4$ 成立。

* 假设 $n-1$ 成立，那么对于 $n$ 时的情况，设 $k=4p+2q(q=0,1)$。

	- 若 $q=0$，可选取 $A_1\oplus A_2,A_3\oplus A_4,\cdots,A_{4p-1}\oplus A_{4p}$，且 $k'$ 仍然为偶数。
    
   - 若 $q=1$，如果 $k=2$ 显然。否则考虑选取 $A_1\oplus A_2,A_3\oplus A_4,\cdots,A_{4p-3}\oplus A_{4p-2},A_{4p-1}\oplus A_{4p},A_{4p}\oplus A_{4p+1}$，这样就保留了 $A_1,A_2,\cdots,A_{4p-1},A_{4p+1}$ 到下一轮，并且 $k'=2p+2$ 仍然为偶数。
   
对于 $k=n$ 的情况，不难发现只能取 $\frac{n}{2}$ 对来保留所有数，故只有 $4|n$ 时合法。

对于一般情况，我们把所有数对扔进线性基里，求最大异或和就是答案。因为如果有重复的数相当于数的个数 $-2$，不影响可行性。

对于 $n=4m+2(m>0)$ 的情况，枚举 ban 掉一个数后把所有答案取最大值即可。

一般情况复杂度 $O(n^2\log V)$，$n=4m+2$ 时复杂度 $O(n^3\log V)$。

---

## 作者：cwfxlh (赞：0)

# [AT_arc173_e](https://www.luogu.com.cn/problem/AT_arc173_e)     

这个题的关键在于观察到，什么样的结果是可以生成的。   

最终的结果一定是若干个 $a$ 异或起来的值。不妨让 $a$ 互相独立，即 $a_i=2^i$，然后考虑有哪些 $a$ 的集合 $S$ 满足，存在一种方式，使得最后的结果恰好是 $S$ 的元素的异或。     

不难发现，一个集合 $S$ 是否合法只与 $|S|$ 有关。     

首先有必要条件，$|S|$ 是偶数，因为进行一次操作后，每个元素都变为了两个 $a$ 的异或，接下来每一次，进行的相邻元素异或都是将两个偶数个 $a$ 构成的元素异或，所以最终结果也是偶数个 $a$。     

但是发现这个条件是不充分的，首先 $|S|$ 不等于 $0$，另外发现，在 $n=6$ 的时候，不能取到全集。     

先来证明对于小于 $n$ 的正偶数 $|S|=2k$ 都是可行的，如果 $k$ 是偶数，排布成 $a_1,a_2,a_3\dots a_{2k-1},a_{2k}\dots$，于是问题可以转化为 $n-1$ 选 $k$ 个的子问题。如果 $k$ 是奇数，排布成 $a_1,a_2,a_3\dots a_{2k-1},a_n,a_{2k}\dots$，转化为 $n-1$ 选 $k+1$ 个的子问题。两个转化都满足转化后的 $k<n$ 且 $k$ 为偶数，唯一的边界情况是会转化为 $2$ 选 $2$，这显然可以解决。于是证明了不选全集的话正偶数是充要的。      

如果选择全集，当 $n=4t$ 的时候，按上边 $k$ 为偶数的情况转化。当 $n=2$ 的时候有平凡解。当 $n=4t+2$ 且 $n\neq 2$ 的时候无解，具体证明如下。    

第一轮肯定是没必要排的，进行一轮操作后变为 $a_1\bigoplus a_2 ,a_2\bigoplus a_3,\dots a_{n-1}\bigoplus a_n$，接下来将证明我们必须从中选 $2t+1$ 个拼起来才能得到全集。如果少于 $2t+1$，显然不可能，如果多于 $2t+1$，则必定有相邻两个被选中，那么最后结果也不是全集，所以必须选 $2t+1$ 个，但是 $2t+1$ 为奇数且 $\frac{n}{2}\neq 1$，所以是无解的。        

最后问题转化为了选偶数个数求最大异或值，或者不选完的最大异或值。不选完的话可以钦定一个数不选。在一个序列 $a_1,\dots a_n$ 里选偶数个，可以看作在 $a_1\bigoplus a_2,a_1\bigoplus a_3,\dots a_1\bigoplus a_n$ 里任意选，使用线性基解决。    

于是问题解决了，复杂度 $O(n^2\log V)$，如果把钦定一个数不选改成合并前后缀线性基，复杂度可以做到 $O(n\log^2V)$，但因为 $n$ 比较小且 $V$ 比较大，所以没啥差异。    

代码：    

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,p[503],ans,fsp[503];
int a[503],len;
int v[503];
int calc(){
    for(int i=0;i<=61;i++)v[i]=0;
    for(int i=2;i<=len;i++){
        for(int j=a[i],u=61;u>=0;u--){
            if((j&fsp[u])==0)continue;
            if(v[u]!=0)j^=v[u];
            else{
                v[u]=j;
                break;
            }
        }
    }
    int ret=0;
    for(int i=61;i>=0;i--){
        if((ret&fsp[i])!=0)continue;
        if(v[i]!=0)ret^=v[i];
    }
    return ret;
}
signed main(){
    ios::sync_with_stdio(false);
    fsp[0]=1;
    for(int i=1;i<=61;i++)fsp[i]=fsp[i-1]*2ll;
    cin>>n;
    for(int i=1;i<=n;i++)cin>>p[i];
    if(n%4!=2||n==2){
        a[1]=p[1];
        for(int i=2;i<=n;i++)a[i]=p[i]^a[1];
        len=n;
        ans=calc();
        cout<<ans;
        return 0;
    }
    for(int i=1;i<=n;i++){
        len=0;
        for(int j=1;j<=n;j++)if(j!=i)a[++len]=p[j];
        for(int j=2;j<=len;j++)a[j]^=a[1];
        ans=max(ans,calc());
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：daduoli (赞：0)

# 题目大意

给一个长度为 $n$ 的序列 $a$。

每次操作前可将序列重排，然后操作之后变成：

$a_1\oplus a_2,a_2\oplus a_3...a_{n-1}\oplus a_n$

询问操作 $n-1$ 次之后最大剩下的数为多少。

------------

一般可能会陷入套路想一位一位填，但是这题不行，你得倒着考虑答案可能由哪些 $a$ 组成。

首先有一个 key observation。

答案只能由偶数个 $a$ 组成，这个是比较显然的（当然对于 $n>1$ 而言）。

反证法：

倘若两个长度为偶数的 $a$ 异或起来，得到长度为奇数的 $a$，假设两个长度分别为 $l_1,l_2$。

然后设他们都有的元素有 $p$ 个。

最后剩下元素个数是 $l_1+l_2-2\times p$，容易发现一定为偶数。

由于 $a$ 可以重排，现在问题变成了能否将我们所需要的偶数个 $a$ 变成一段长度为偶数的长度。

这时候有两种情况。

- $len=4k$

这时候我们可以重排然后把我们需要的元素变成前 $2k$ 个。$1,2,3,4...4k-1,4k,4k+1...n$

操作完之后，我们需要的元素就是 $1,3,5...4k-1$。

这样数量是偶数个的答案可以得到。

- $len=4k+2$

这时候因为把我们需要的元素按照上面的方法排是不行的。

所以我们要借一个数。

$1,2,3...4k-1,n,4k,4k+1...n-1$

就是随便拿一个数放在 $4k-1,4k$ 中间，这样我们操作完之后就是：

$1\oplus 2,3\oplus 4...4k-1\oplus n,n\oplus4k+1$

这样前面偶数个还是可以选上，合法。不过这种情况中不能选择全集。

------------

现在考虑如何选出偶数个值，使他们的异或值最大，只需要改改线性基即可，将所有数都异或上 $a_1$，这样选了奇数个的时候就一定带了 $a_1$，选了偶数个的时候一定不带 $a_1$。

然后对于 $n=4k+2$ 的情况，就只能插入 $n-1$ 个数，有一个数不能插入。

时间复杂度 $O(n^2\log V)$。

---

