# [AGC061C] First Come First Serve

## 题目描述

有 $N$ 位顾客会光顾某家店，我们将他们编号为 $1,\ldots,N$。第 $i$ 位顾客在时刻 $A_i$ 进入店内，在时刻 $B_i$ 离开店铺。该店的排队方式为“先进先出”，并且 $A_i$ 和 $B_i$ 都是严格递增的。此外，所有的 $A_i$ 和 $B_i$ 互不相同。

在店门口有一份顾客可以签名的名单。每位顾客仅能在入店时或离店时，将自己的名字写在名单的末尾一次。请问，最终名单上名字的可能排列方式有多少种？请将答案对 $998\,244\,353$ 取模后输出。

## 说明/提示

## 限制条件

- $1 \leq N \leq 5 \cdot 10^5$
- $1 \leq A_i < B_i \leq 2N$
- $A_i < A_{i+1}$（$1 \leq i \leq N-1$）
- $B_i < B_{i+1}$（$1 \leq i \leq N-1$）
- $A_i \neq B_j$（$i \neq j$）
- 输入中的所有值均为整数。

## 样例解释 1

可能的排列有 $(1,\ 2,\ 3),\ (2,\ 1,\ 3),\ (1,\ 3,\ 2)$。

## 样例解释 2

可能的排列仅有 $(1,\ 2,\ 3,\ 4)$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
1 3
2 5
4 6```

### 输出

```
3```

## 样例 #2

### 输入

```
4
1 2
3 4
5 6
7 8```

### 输出

```
1```

# 题解

## 作者：Leasier (赞：21)

如果不考虑重复，我们有 $2^n$ 种选择。

那什么时候会重复呢？注意到去重后我们的选择实际上形如：

- 选择 $a_i$。
- 若 $(a_i, b_i)$ 间有数被选择，选择 $b_i$。

考虑对条件 2 容斥：

- 选择 $a_i$，系数为 $1$。
- 选择 $b_i$，系数为 $1$。
- 若 $(a_i, b_i)$ 间没有数被选择，选择 $b_i$，系数为 $-1$。

考虑 dp，设 $dp_i$ 表示考虑了 $a/b_{1 \sim i}$ 的选择，系数之积的和。

前两种选择对 $dp_i$ 的贡献显然为 $dp_{i - 1}$。

对于第三种选择，我们对一个 $[a_i, b_i]$，取最大的 $p$ 满足 $b_p < a_i$，取最小的 $q$ 满足 $a_q > b_i$，则 $[p, q]$ 中的选择完全确定，对 $dp_q$ 的贡献为 $dp_{p - 1}$。

双指针即可。时间复杂度为 $O(n)$。

代码：
```cpp
#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

const int mod = 998244353;
int a[500007], b[500007], l[500007], r[500007], dp[500007];
vector<int> v[500007];

inline int read(){
	int ans = 0;
	char ch = getchar();
	while (ch < '0' || ch > '9'){
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9'){
		ans = ans * 10 + (ch ^ 48);
		ch = getchar();
	}
	return ans;
}

int main(){
	int n = read();
	for (int i = 1; i <= n; i++){
		a[i] = read();
		b[i] = read();
	}
	for (int i = 1, j = 0; i <= n; i++){
		while (j < n && b[j + 1] < a[i]) j++;
		l[i] = j;
	}
	for (int i = 1, j = 0; i <= n; i++){
		while (j < n && a[j + 1] < b[i]) j++;
		r[i] = j;
	}
	for (int i = 1; i <= n; i++){
		v[r[i]].push_back(l[i]);
	}
	dp[0] = 1;
	for (int i = 1; i <= n; i++){
		int size = v[i].size();
		dp[i] = dp[i - 1] * 2 % mod;
		for (int j = 0; j < size; j++){
			dp[i] = ((dp[i] - dp[v[i][j]]) % mod + mod) % mod;
		}
	}
	cout << dp[n];
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：15)

[Problem Link](https://www.luogu.com.cn/problem/AT_agc061_c)

**题目大意**

> 给定 $a_1\sim a_n,b_1\sim b_n$ 构成 $1\sim 2n$ 的排列，且 $a_i<b_i,a_i<a_{i+1},b_i<b_{i+1}$。
>
> 令 $t_i\in\{a_i,b_i\}$，求 $t_i$ 的相对顺序有多少种可能。
>
> 数据范围：$n\le 5\times 10^5$。

**思路分析**

对于一对 $(a_i,b_i)$，选 $a_i,b_i$ 等价当且仅当 $[a_i,b_i]$ 中间没有其他 $t_j$。

因此我们可以用 dp 容斥掉这种情况，$dp_{i}$ 表示选择了 $t_1\sim t_i$ 的方案数。

那么 $dp_i\gets 2dp_{i-1}$，然后找到最大的 $b_j<a_i$ 和 $a_k<b_i$，那么我们想要容斥掉 $[a_i,b_i]$ 就要求 $(j,k]$ 区间选择一定，因此转移 $dp_k\gets -dp_j$。

双指针求解即可。

时间复杂度 $\mathcal O(n)$。

**代码呈现**

```cpp
#include<bits/stdc++.h>
using namespace std;
const int MAXN=5e5+5,MOD=998244353;
int n,l[MAXN],r[MAXN],dp[MAXN];
vector <int> d[MAXN];
signed main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d%d",&l[i],&r[i]);
	for(int i=1,j=0,k=0;i<=n;++i) {
		while(j<n&&r[j+1]<l[i]) ++j;
		while(k<n&&l[k+1]<r[i]) ++k;
		d[k].push_back(j);
	}
	dp[0]=1;
	for(int i=1;i<=n;++i) {
		dp[i]=dp[i-1]*2%MOD;
		for(int j:d[i]) dp[i]=(dp[i]+MOD-dp[j])%MOD;
	}
	printf("%d\n",dp[n]);
	return 0;
}
```

---

## 作者：pengyule (赞：13)

> 有 $n$ 个人在排队进门，第 $i$ 个人在 $A_i$ 时进 $B_i$ 时出（保证先进去的先出来），每人须在进去或者出来时在名单的最后写上自己的名字，求最终名单有几种不同的顺序？$n\le 5\times 10^5$，$A_i,B_i$ 取遍 $[1,2n]\cap \mathbb{Z}$。

先考虑答案是 $2^{n}$，发现会算重。考虑什么时候会算重，发现如果一个区间完全独立于其他区间时随便取就会算重，两个区间 $[1,3]$ 和 $[2,4]$ 取 $1,2$ 和 $3,4$ 这两种情况也是算重的。总的来说，就是取 $A$ 还是取 $B$ 太任性了——考虑设计一种规则，使得严格遵循这种规则取就不会算重。

发现有一种规则可以达到这个条件：一开始全取 $A$，如果你想改成取 $B$ 必须要有人取区间 $(A,B)$ 里的数。但是，并不要求你改的时候 $(A,B)$ 里就有数，而是最后都定下来的时候对于每个取 $B$ 的数都满足这个条件。

这个条件很苛刻，但不难发现确实不会算重了。由于只是最终的状态决定了它，我们很难按照时间线统计有多少种合法方案。题解给出的做法是容斥。

按照套路容斥有多少个不满足条件的取 $B$ 的人。下面用记号 $C_i=0$ 代表 $i$ 取 $A$，$C_i=1$ 代表 $i$ 取 $B$。

设 $L_i$ 表示最小的 $j$ 使得 $B_j\ge A_i$，$R_i$ 表示最大的 $j$ 使得 $A_j\le B_i$。那么如果 $i$ 不满足条件，一定有 $C_{L_i\sim i-1}=0,C_{i+1\sim R_i}=1$，于是 $C_{L_i\sim R_i}$ 就是固定的。观察到两个有交的区间 $[L_x,R_x]$ 和 $[L_y,R_y]$ 是不能同时不满足条件的，因此一种容斥局面的就是若干个不相交的 $[L,R]$ 组成的集合，一个局面的权值就是 $2^{n-\sum len}(-1)^{|\{[L_i,R_i]\}|}$，所求就是所有合法局面的权值和。

自然用简单的容斥 DP 解决：设 $f_i$ 表示完全包含于前缀 $i$ 的局面们的权值和，转移：$f_i=\sum_{x(R_x=i)}\left(\sum_{j=0}^{L_x-1}(-2^{-(R_x-L_x+1)}f_j)\right)-2^{n-(R_x-L_x+1)}$，边界 $f_0=2^n$。

[submission](https://atcoder.jp/contests/agc061/submissions/40097095)

---

## 作者：UltiMadow (赞：7)

记录一个暴力的思路（

按照套路，考虑给每个登记序列一一对应一种登记方式。

不妨让每个人都尽量在区间左端点处登记，也即只有在区间内有人登记时才可以选右端点。

考虑一个暴力 dp：记 $f_{i,j}$ 表示当前处理到第 $i$ 个人，最后一个登记的人是在时刻 $j$，且对后续登记没有限制的方案数；$g_{i,j}$ 表示当前处理到第 $i$ 个人，要求后续登记中至少有一个人在 $j$ 时刻前登记的方案数。

先考虑 $f$ 的转移，记当前区间为 $[l_i,r_i]$，则显然对于所有 $j<l_i$ 有 $f_{i,j}=0$；考虑当前选择区间左端点还是右端点，若选择左端点，则对于 $j< l_i$ 有 $f_{i,l_i}\leftarrow f_{i-1,j}$，对于 $j>l_i$ 有 $f_{i,j}\leftarrow f_{i-1,j}$；若选择右端点，由于要对后面的选择没有要求，于是只对 $j< l_i$ 有 $f_{i,r_i}\leftarrow f_{i-1,j}$。

再考虑 $g$ 的转移，首先同样对于所有 $j< l_i$ 有 $g_{i,j}=0$；由于此时我们选择的显然是右端点，则对于 $j>l_i$ 有 $g_{i,j}\leftarrow g_{i-1,j}$，并且可以从 $f$ 转移过来，即对于 $j< l_i$，有 $g_{i,r_i}\leftarrow f_{i-1,j}$。

最后还有 $g$ 向 $f$ 的转移，此时显然选择的是左端点，上一个选择的一定是右端点，于是对于 $j>l_i$ 有 $f_{i,r_{i-1}}\leftarrow g_{i-1,j}$。

上述过程涉及到单点加，区间设 $0$，区间求和，可以用线段树维护。

时间复杂度 $\mathcal O(n\log n)$。

code:
```cpp
#include<bits/stdc++.h>
#define int long long
#define MAXN 500010
#define mod 998244353
using namespace std;
int n,ql[MAXN],qr[MAXN];
struct Segtree{
	int t[MAXN<<3],tag[MAXN<<3];
	void pushup(int p){t[p]=(t[p<<1]+t[p<<1|1])%mod;}
	void paint(int p){t[p]=0;tag[p]=1;}
	void pushdown(int p){
		if(!tag[p])return;
		paint(p<<1);paint(p<<1|1);
		tag[p]=0;
	}
	void paint(int p,int l,int r,int L,int R){
		if(L>R)return;if(L<=l&&r<=R)return paint(p);
		int mid=(l+r)>>1;pushdown(p);
		if(L<=mid)paint(p<<1,l,mid,L,R);
		if(R>mid)paint(p<<1|1,mid+1,r,L,R);
		pushup(p);
	}
	void update(int p,int l,int r,int pos,int d){
		if(l==r)return (void)(t[p]=(t[p]+d)%mod);
		int mid=(l+r)>>1;pushdown(p);
		if(pos<=mid)update(p<<1,l,mid,pos,d);
		else update(p<<1|1,mid+1,r,pos,d);
		pushup(p);
	}
	int query(int p,int l,int r,int L,int R){
		if(L>R)return 0;if(L<=l&&r<=R)return t[p];
		int mid=(l+r)>>1;pushdown(p);
		if(R<=mid)return query(p<<1,l,mid,L,R);
		if(L>mid)return query(p<<1|1,mid+1,r,L,R);
		return (query(p<<1,l,mid,L,R)+query(p<<1|1,mid+1,r,L,R))%mod;
	}
}f,g;
signed main(){
	scanf("%lld",&n);int m=n<<1;
	for(int i=1;i<=n;i++)scanf("%lld%lld",&ql[i],&qr[i]);
	f.update(1,1,m,ql[1],1);g.update(1,1,m,qr[1],1);
	for(int i=2;i<=n;i++){
		int fl=f.query(1,1,m,1,ql[i]),fr=f.query(1,1,m,ql[i]+1,qr[i]);
		int gr=g.query(1,1,m,ql[i]+1,qr[i]);
		g.paint(1,1,m,1,ql[i]);f.paint(1,1,m,1,ql[i]);
		f.update(1,1,m,ql[i],fl);f.update(1,1,m,qr[i],fr);
		f.update(1,1,m,qr[i-1],gr);g.update(1,1,m,qr[i],fl);
	}
	printf("%lld",f.t[1]);
	return 0;
}
```

---

## 作者：苹果蓝17 (赞：5)

> 结论：对于每一个合法排列 $P$，存在唯一的长为 $n$ 的序列 $i_1,i_2,\cdots,i_n$ 使得 $\forall t, A_{P_t}=i_t \vee (B_{P_t}=i_t \wedge i_{t-1}>A_{P_t})$。

> 证明：先证明存在性：由于 $P$ 合法，先选出序列 $i'_1,\cdots,i_n$ 满足前两个条件 $\forall t, A_{P_t}=i_t \vee B_{P_t}=i_t$；再对不满足第三个条件的 $t$ 进行调整，每次调整 $\sum i_t$ 严格变小，故有限次调整后得到合法序列。
> 
> 再证明唯一性：设序列 $i_1,\cdots,i_n$  和 $j_1,j_2,\cdots,j_n$ 均合法。求出两个序列的最长公共前缀长度 $l(l<n)$，则由于 $i_{l+1} \neq j_{l+1}$，有 $A_{P_{l+1}}=i_{l+1},B_{P_{l+1}}=j_{l+1}$，那么 $i_l=j_l < j_{l+1}$，于是 $j_{l+1}$ 不满足第三个条件，矛盾，故唯一性得证。
> 
> 综上，证毕。

那么现在每个人有两种选择：

- 选择 $A_i$。

- 选择 $B_i$，要求 $[A_i,B_i)$ 内有数被选择。

对第二种选择容斥，每个人有三种选择：

- 选择 $A_i$，容斥系数为 $1$。

- 选择 $B_i$，容斥系数为 $1$。

- 选择 $B_i$，要求 $[A_i,B_i)$ 内无数被选择，容斥系数为 $-1$。

由于题目保证 $A,B$ 均递增，考虑朴素 DP，设 $dp_i$ 表示考虑前 $i$ 个人，第 $i$ 个人选择第三种选择的方案数。转移枚举上一个选择第三种选择的人 $j$，可以计算出 $(j,i)$ 的人选择前两种选择的方案数。

DP 可以前缀和优化，总时间复杂度 $O(n)$。

[**Code**](https://atcoder.jp/contests/agc061/submissions/38949043)

---

## 作者：Jim_Franklin (赞：4)

如果不考虑会不会数重，答案就是 $2^n$ ，即每个人分别在来时或走时的情况，我们可以把每一种情况看成一个 $01$ 序列。

此时对于每一个 $01$ 序列，我们都能唯一地对应到一种登记的顺序，但是对于同一种登记顺序却有可能对应多个 $01$ 序列。

于是考虑增加某种限制去约束 $01$ 序列的生成方式，使得 $01$ 序列和登记顺序形成双射，这样只需要数符合要求的 $01$ 序列的数量即可。

有一个想法是在 $01$ 序列中，在不改变登记顺序的情况下能填 $0$ 就尽可能填 $0$，容易发现这就能满足我们的要求。

同时我们又发现在当前条件下如果一个位置 $i$ 能够填 $1$ ，当且仅当 $[a_i,b_i]$ 中有人登记过了。

自然地想到一个 DP ：令 $f_{i,0/1}$ 表示仅考虑前 $i$ 个人，且当前的人选择在 $a_i/b_i$ 时刻登记的合法（即符合上述约束条件）的 $01$ 序列的数量。

由于题面中 $a_i<a_{i+1},b_i<b_{i+1}$ 的限制使得我们可以方便地进行处理。

设 $j$ 为第一个满足 $j<i$ 且 $b_j\ge a_i$ 的位置。

对于 $f_{i,0}$ 我们枚举上一个填 $0$ 的位置 $k$，显然对于 $k\in [j-1,i-1]$ 的位置填零都是合法的，而对于 $k<j-1$ 的位置他们填 $0$ 还是 $1$ 并不会影响当前的答案，但是此时意味着 $k\in[j-1,i-1]$ 的位置都填了 $1$ 因此只需要算上 $f_{j-1,1}$ 的方案数就好。

所以 $f_{i,0}=\sum _{k=j-1}^{i-1} f_{k,0}+f_{j-1,1}$。

对于 $f_{i,1}$ 可以直接由 $f_{i-1,0}$ 和 $f_{i-1,1}$ 转移过来，同时我们发现在 $f_{i-1,0}$ 中会存在一些不合法的情况，具体的就是 $k\in[j,i-1]$ 没有一个选了右端点，这样会产生不合法的方案，容易发现这样的方案的个数就是 $f_{j,0}$。

所以 $f_{i,1}=f_{i-1,0}+f_{i-1,1}-f_{j,0}$。

不难发现 $f_{i,0}$ 的转移可以用前缀和来优化，所以时间复杂度为 $\mathcal{O(n)}$。

https://atcoder.jp/contests/agc061/submissions/59280990

---

## 作者：2008verser (赞：2)

明确计数对象：人的排列数目，排列需要合法。

考虑一种排列，自上到下将每个人的二元组 $(a,b)$ 写出来。那么合法就是说，存在从第一行到最后一行的路线，每步向下面两个数随便一个走且路线上数字递增。

问题转为计数**存在路线的排列**数目。直接对着路线 dp 不管用，原因是一个排列存在若干可行的路线。

考虑设计对于一个排列生成唯一路线的方式（双射）。经过感受，将路线能往左掰就掰。现在一个排列的唯一路线可以贪心刻画。（换句话说，下一行的左边能走就走，不能走再看右边能不能走）

现在需要计数**路线数目**，路线满足：其中不存在路线上元素是右边且能往左掰（掰了以后路线仍递增）。

进行容斥，计算存在零个能往左掰的。

钦定一个能往左掰会导致向上的一段路线必选左边，向下的一段路线必选右边。

接下来的工作就很常见了：带着容斥系数 $O(n)$ dp 即可。

**启示：利用最方便的直观。**

[AC 链接](https://atcoder.jp/contests/agc061/submissions/60878020)

---

## 作者：5k_sync_closer (赞：2)

考虑 $i$ 人仅当存在某人选择 $(a_i,b_i)$ 的位置时，可以选择 $b_i$，此时选法与排列唯一对应，问题变为统计符合条件的选法数。

设 $l_i$ 表示最小的 $j$ 使得 $b_j\ge a_i$，$r_i$ 表示最大的 $j$ 使得 $a_j\le b_i$，则 $i$ 人不符合条件时 $[l_i,r_i]$ 的人都可以确定选法，

于是两个 $[l,r]$ 有交集的人不可能同时不符合条件，则钦定 $S$ 中的人不符合条件，共有 $2^{n-\sum\limits_{i\in S}r_i-l_i+1}$ 种选法，答案即为 $\sum\limits_{S}(-1)^{|S|}2^{n-\sum\limits_{i\in S}r_i-l_i+1}$。

设 $f_i=\sum\limits_{\forall j\in S,[l_j,r_j]\in[1,i]}(-1)^{|S|}2^{n-\sum\limits_{i\in S}r_i-l_i+1}$，考虑加入 $r_j=i$ 的区间，则 $f_i=\sum\limits_{r_x=i}(\sum\limits_{j=0}^{l_x-1}-2^{-(r_x-l_x+1)}f_j)-2^{n-(r_x-l_x+1)}$。

```cpp
#include <cstdio>
#include <vector>
#define M 998244353
#define int long long
using namespace std;
int P(int x, int y)
{
    int q = 1;
    for (; y; y >>= 1, x = x * x % M)
        if (y & 1)
            q = q * x % M;
    return q;
}
vector<int> v[500050];
int n, a[500050], b[500050], l[500050], r[500050], f[500050];
signed main()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld%lld", a + i, b + i);
    for (int i = 1, p = 0; i <= n; ++i)
    {
        while (b[p + 1] < a[i])
            ++p;
        l[i] = p + 1;
    }
    for (int i = n, p = n + 1; i >= 1; --i)
    {
        while (a[p - 1] > b[i])
            --p;
        r[i] = p - 1;
    }
    for (int i = 1; i <= n; ++i)
        v[r[i]].push_back(l[i]);
    f[0] = P(2, n);
    for (int i = 1; i <= n; ++i)
    {
        for (auto j : v[i])
            f[i] = (f[i] + M - P(P(2, i - j + 1), M - 2) * f[j - 1] % M) % M;
        f[i] = (f[i] + f[i - 1]) % M;
    }
    printf("%lld", f[n]);
    return 0;
}
```


---

## 作者：OoXiao_QioO (赞：1)

这题纯容斥，首先考虑找到一种统计答案序列而非操作序列的方式：一般而言会选择建立某种双射。考虑一个答案序列可以怎么被操作到：或者说，对于一个答案序列，判断它能否操作到。

注意到序列中第一个元素，肯定是选择左端点比较合理。因为这样它对后面的限制要少一些。那么其实双射方式就呼之欲出了：就是从左往右扫，能取左端点就取左端点。我们就可以对这个操作序列进行计数。

这个操作序列怎么计数呢？考虑这个序列满足啥条件：其实就是能选左边的就不会选右边的，那也就是不可能出现一个空的区间，这个区间没有任何数字。对着这个条件容斥即可。

---

## 作者：do_it_tomorrow (赞：0)

比较容易漏掉的是 $\forall i<n,a_i<a_{i+1},b_{i}<b_{i+1}$。

考虑当 $(a_i,b_i)$ 会对答案造成 $2$ 次当且仅当 $(a_i,b_i)$ 中有被选择的点，那么我们就可以设 $f_i$ 表示考虑了 $1$ 到 $i$ 的方案数。

于是考虑容斥，显然 $f_i\gets 2\times f_{i-1}$。

需要注意的，不可能有包含关系。

那么如果我们找到最大的 $b_j<a_i$ 且 $a_k<b_i$，则 $(j,k]$ 区间只有在至少一个在 $(a_i,b_i)$ 中选择才会有效果，于是我们 $f_k\gets f_{k}-f_{j}$，相当于减去了一种全部都在外面的情况。

那么双指针就可以做到 $O(n)$，但是我写的 $O(n\log n)$ 的二分。

[Submission #68002345 - AtCoder Grand Contest 061](https://atcoder.jp/contests/agc061/submissions/68002345)

---

## 作者：MiRaciss (赞：0)

很神仙的一道题。先考虑所有的人都选择 $a_i$ 时刻登记。那么对于一个人来说他变成 $b_i$ 的时会增加贡献当且仅当 $[a_i,b_i]$ 之间有其他人被登记。

定义 $C$ 数组, $C_i$ 为 0 表示第 $i$ 个人在 $a_i$ 被登记，为 $1$ 表示第 $i$ 个人在 $b_i$ 被登记。考虑将计数转换成对 $C$ 计数，但是由上所述，有时候 C 数组不同所得到的序列却是相同的。于是考虑定义合法，将序列对应的最终顺序唯一化。合法不好算，转换成全部的减去不合法的。

定义不合法为存在一个 $i$ 满足 $C_i=1$ 但 $C_i$ 变为 $0$ 后最终顺序不改变。

还是由上所述，对于 i 来说他不合法说明 $[a_i,b_i]$  没有其他人被登记了，也就是说对于任意的 j 来说，如果 $a_j\in [a_i,b_i]$ 那么 j 就只能在 $b_j$ 被登记才有可能让 i 不合法。$b_j\in [a_i,b_i]$ 也是同理。

处理出每个位置 $ i $ 的 $ l_i $ 和 $ r_i $，其中 $ l_i $ 表示最小的满足 $ b_j > a_i $ 的 $ j $ ，$ r_i $ 表示最大的 $ j $ 满足 $ a_j < b_i $ 的 $ j $。所以当 $ i $ 不合法时有 $ C_{l_i} = C_{l_i + 1} = \cdots = C_{i - 1} = 0 $ ，$ C_{i} = C_{i + 1} = \cdots = C_{r_i} = 1 $，此时 $ l_i \sim r_i $ 的值是确定的。

显然 $l,r$ 是单调的，然后如果对于 i,j 有 $[l_i,r_i] $ 和 $[l_j,r_j]$ 是相交的，那么两个位置一定不能同时不合法。

所以问题就转换成了选择 $k$ 个区间，$k\in [0,n]$，区间内不不相交，每个选择方案的容斥贡献是 $2^x(-1)^y$，$x$ 为未被覆盖的节点个，$y$ 为区间选择个数。然后考虑刷表。可以做到线性复杂度但是教我这道题的人用了二分来找 $l_i,r_i$。

```cpp
// LUOGU_RID: 124999403
#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll Mod=998244353;

ll Pow(ll a,ll b){
	ll ans=1;
	while(b){
		if(b&1) ans*=a,ans%=Mod;
		a*=a,a%=Mod,b>>=1;
	}
	return ans;
}

int l[500005],r[500005];
int a[500005],b[500005];
ll dp[500005];
int n;

int main(){
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
	for(int i=1;i<=n;i++){
		l[i]=upper_bound(b+1,b+n+1,a[i])-b;
		r[i]=lower_bound(a+1,a+n+1,b[i])-a-1;
	}
	dp[0]=1;
	for(int i=1;i<=n;i++){
		dp[i]+=dp[i-1]*2%Mod,dp[i]%=Mod;
		dp[r[i]]-=dp[l[i]-1],dp[r[i]]=(dp[r[i]]+Mod)%Mod;
	}
	cout<<dp[n];
	return 0;
}  
```

---

## 作者：User_Authorized (赞：0)

## 题意
有两个长度为 $n$ 的正整数列 $A,B$。表示数 $i$ 可以填到 $A_i$ 或 $B_i$ 两个位置中的一个。问删去空位之后可以形成的排列种数。

（$1 \le n \le 5 \times 10^5$，$A_i,B_i$ 取遍 $\left[1, 2n\right]$ 且单调递增）。

## 题解
首先可以发现填数的方案数为 $2^n$，发现会计算进重复情况，考虑什么时候会有重复情况，如果 $\forall i \neq x, \left[A_i, B_i\right] \cap \left[A_x, B_x\right] = \varnothing$ 或是 $\exists j \neq i,A_i < A_j \land B_i < B_j$ 均会产生重复情况。换句话说就是有一些数选择 $A_i$ 和 $B_i$ 对最终形成的排列没有影响，却被计算了多次。

设一个序列 $C_i$，满足 $C_i = 0 \Rightarrow$ 数字 $i$ 填在位置 $A_i$， $C_i = 1 \Rightarrow$ 数字 $i$ 填在位置 $B_i$。考虑一个数什么时候会有重复情况，如果数字 $i$ 选择了填在 $B_i$ 但是没有其他数字填在 $\left(A_i, B_i\right)$，那么这个数字就会产生重复情况，记这种状态为 $i$ 不合法，考虑从所有状态中容斥掉不合法状态。

记 $L_i = \min\limits_{j = 1}^{n} B_j > A_i,R_i = \max\limits_{j = 1}^{n} A_j < B_i$，那么如果 $i$ 不合法，可以推出 $\forall j \in \left[L_i, i\right] C_j = 0 \land \forall j \in \left(i, R_i\right] C_j = 1$，换句话说就是区间 $\left[L_i,R_i\right]$ 的选择情况会被确定下来。再发现一点性质，如果存在 $i < j$，使得 $R_i \ge L_j$，那么 $i, j$ 一定同时合法，也就是说，最终需要容斥的局面中的区间集一定两两不交。

考虑容斥，设当前的状态集合 $S$ 为形如 $\left\{\left(L_i, R_i\right)\right\}$ 的区间集，那么最终的答案为

$$2^n - \sum\limits_{S \neq \varnothing} (-1)^{\lvert S \rvert - 1} 2^{n - \operatorname{len}(S)} = \sum\limits_{S}(-1)^{\lvert S \rvert}2^{n - \operatorname{len}(S)}$$

其中 $\operatorname{len}(S) = \sum\limits_{\left(l, r\right) \in S} r - l + 1$，即集合内所有区间的长度之和。

考虑进行容斥 DP，设 $f_i$ 为只考虑了完全包含于 $\left[1, i\right]$ 的区间组成的状态且**钦定状态中存在右端点为 $i$ 的区间**的方案数。边界为 $f_0 = 2^n$，因为没有考虑任何一个状态。考虑将所有区间按右端点存储，转移时枚举右端点为 $i$ 的所有区间的左端点，并计算当前区间的贡献即可。转移式如下

$$f_i = \sum\limits_{R_x = i}\sum\limits_{j = 0}^{L_x - 1} -2^{-(R_x - L_x + 1)}f_j$$


使用前缀和优化即可以 $\mathcal{O}(n)$ 的复杂度通过本题，因为最终状态右端点可以取遍 $\left[1, n\right]$，所以最终答案为 $\sum\limits_{i = 0}^{n} f_i$。

发现上述 DP 定义限制过紧，考虑放松限制。设 $g_i$ 为只考虑了完全包含于 $\left[1, i\right]$ 的区间组成的状态且**不要求状态中存在右端点为 $i$ 的区间**的方案数，转移时依旧考虑枚举右端点为 $i$ 的所有区间的左端点，得到转移式为

$$g_i = g_{i - 1} + \sum\limits_{R_x = i}-2^{-(R_x - L_x + 1)}g_{L_x - 1}$$

因为 $g$ 的定义限制进行了放松，所以最终答案为 $g_n$。不难看出其实 $g_n = \sum\limits_{i = 0}^{n} f_i$，即 $g$ 在数值上等于 $f$ 的前缀和。

## Code
```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

constexpr valueType MOD = 998244353;

template<typename T1, typename T2, typename T3 = valueType>
void Inc(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a + b;

    if (a >= mod)
        a -= mod;
}

template<typename T1, typename T2, typename T3 = valueType>
void Dec(T1 &a, T2 b, const T3 &mod = MOD) {
    a = a - b;

    if (a < 0)
        a += mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
    return (long long) a * b % MOD;
}

template<typename T1, typename T2, typename T3 = valueType>
void Mul(T1 &a, T2 b, const T3 &mod = MOD) {
    a = (long long) a * b % mod;
}

template<typename T1, typename T2, typename T3 = valueType>
T1 pow(T1 a, T2 b, const T3 &mod = MOD) {
    T1 result = 1;

    while (b > 0) {
        if (b & 1)
            Mul(result, a, mod);

        Mul(a, a, mod);
        b = b >> 1;
    }

    return result;
}

class Inverse {
public:
    typedef ValueVector container;

private:
    valueType size;
    container data;
public:
    explicit Inverse(valueType n) : size(n), data(size + 1, 0) {
        data[1] = 1;

        for (valueType i = 2; i <= size; ++i)
            data[i] = mul((MOD - MOD / i), data[MOD % i]);
    }

    valueType operator()(valueType n) const {
        return data[n];
    }
};

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    valueType N;

    std::cin >> N;

    ValueVector A(N + 1), B(N + 1), L(N + 1), R(N + 1);

    for (valueType i = 1; i <= N; ++i)
        std::cin >> A[i] >> B[i];

    valueType pointer = 0;
    for (valueType i = 1; i <= N; ++i) {
        while (pointer < N && B[pointer + 1] < A[i])
            ++pointer;

        L[i] = pointer + 1;
    }

    pointer = N + 1;
    for (valueType i = N; i >= 1; --i) {
        while (pointer > 1 && A[pointer - 1] > B[i])
            --pointer;

        R[i] = pointer - 1;
    }

    ValueMatrix left(N + 1);
    for (valueType i = 1; i <= N; ++i)
        left[R[i]].emplace_back(L[i]);

    ValueVector F(N + 1, 0);

    F[0] = pow(2, N);
    Inverse Inv(2);

    for (valueType i = 1; i <= N; ++i) {
        Inc(F[i], F[i - 1]);

        for (auto const &iter: left[i])
            Dec(F[i], mul(pow(Inv(2), i - iter + 1), F[iter - 1]));
    }

    std::cout << F[N] << std::endl;

    return 0;
}
```

---

