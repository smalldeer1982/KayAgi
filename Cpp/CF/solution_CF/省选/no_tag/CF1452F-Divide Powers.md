# Divide Powers

## 题目描述

You are given a multiset of powers of two. More precisely, for each $ i $ from $ 0 $ to $ n $ exclusive you have $ cnt_i $ elements equal to $ 2^i $ .

In one operation, you can choose any one element $ 2^l > 1 $ and divide it into two elements $ 2^{l - 1} $ .

You should perform $ q $ queries. Each query has one of two types:

- " $ 1 $ $ pos $ $ val $ " — assign $ cnt_{pos} := val $ ;
- " $ 2 $ $ x $ $ k $ " — calculate the minimum number of operations you need to make at least $ k $ elements with value lower or equal to $ 2^x $ .

Note that all queries of the second type don't change the multiset; that is, you just calculate the minimum number of operations, you don't perform them.

## 样例 #1

### 输入

```
6 11
0 1 0 0 1 0
2 1 5
2 4 18
1 1 0
2 2 5
2 0 17
1 0 3
2 1 2
1 1 4
1 4 0
1 5 1
2 2 8```

### 输出

```
4
16
4
-1
0
1```

# 题解

## 作者：tommymio (赞：3)

分析一下，我们一共有三种操作：

- $\forall i\in [0,x]$，操作 $2^i-1$ 次得到 $2^i$ 个 $1$。
- $\forall i\in(x,n)$，操作 $2^{i-x}-1$ 次得到 $2^{i-x}$ 个 $2^x$。
- $\forall i\in (x,n)$，操作 $X$ 次得到 $y$ 个 $\leq 2^x$ 的数，$y\in[2,2^{i-x}]$

对于这一类求最小操作次数的题，可以先考虑操作带来的收益和操作代价的比率。第一个操作每次增加 $2^i-1$ 个 $\leq 2^x$ 的数，比率为 $1$，第三个操作比率不超过 $1$，而第二个操作比率大于 $1$。注意，我们上述提到的操作事实上是一串将 $2^i$ 分为 $2^{i-1}$ 的组合，也就是说操作的代价事实上是相同的。我们自然考虑先尽可能选择比率大的操作，即 $2$ 操作。

选完 $2$ 操作以后，如果 $\leq 2^x$ 的数仍然小于 $k$ 个，我们就要考虑选择 $1$ 操作或者 $3$ 操作。记此时距 $k$ 个 $\leq 2^x$ 这一标准相差的个数为 $now$，即还要再有 $now$ 个 $\leq 2^x$ 的数才能达到至少 $k$ 个的要求。我们发现 $1$ 操作事实上是 $3$ 操作的特殊情况，所以我们在 $now\geq 2^{i-x}$ 时，一定会选用 $1$ 操作。现在我们只需要考虑 $now<2^{i-x}$ 的情况。

这种情况下， 我们一定使用 $3$ 操作和一部分 $1$ 操作，但是 $3$ 操作的次数我们尚不知道，并且在何时使用 $1$ 操作也尚未可知，不妨使用分治来处理这一部分。

时间复杂度为 $O(nq)$，$n$ 非常小，不超过 $30$，因此可以把 $n$ 看作常数。

```cpp
#include<cstdio>
#define int ll
typedef long long ll;
int n,a[35];
inline int read() {
	register int x=0,f=1;register char s=getchar();
	while(s>'9'||s<'0') {if(s=='-') f=-1;s=getchar();}
	while(s>='0'&&s<='9') {x=x*10+s-'0';s=getchar();}
	return x*f;
}
inline int min(const int &x,const int &y) {return x<y? x:y;}
inline int solve(int x,int k) {
	int enable_sum=0,big_sum=0,res=0,tmp=0,ans=1e15;
	for(register int i=0;i<=x;++i) {enable_sum+=a[i]*((1ll<<i)-1); tmp+=a[i];}
	if(tmp>=k) return 0; //tmp<k \to k>tmp
	k-=tmp; int cur=x+1;
	while(cur<n) {
		tmp=(1ll<<(cur-x)); int need=min(k/tmp,a[cur]); 
		k-=need*tmp; res+=need*(tmp-1); enable_sum+=need*tmp*((1ll<<x)-1);
		if(need<a[cur]) {break;}
		++cur;
	} 
	if(k==0) return res;
	if(cur==n) {
		if(enable_sum>=k) return res+k;
		else return -1;
	}
	//之前选到某一个 cur 停下来不选，因为不优。
    	//现在考虑把这个 2^cur 分掉 
	while(cur>x) {
		if(enable_sum>=k) {ans=min(ans,res+k);}
		++res; --cur; //Warning
		tmp=(1ll<<(cur-x));
		if(k>=tmp) {res+=tmp-1; k-=tmp; enable_sum+=tmp*((1ll<<x)-1);}
	}  
	return min(res,ans); 
}
signed main() {
	n=read(); int Q=read();
	for(register int i=0;i<n;++i) a[i]=read();  
	while(Q--) {
		int op=read(),x=read(),y=read();
		if(op==1) {a[x]=y;}
		else {printf("%lld\n",solve(x,y));}
	}
	return 0;
} 
```



---

## 作者：duyi (赞：2)

# CF1452F Divide Powers

[题目链接](https://codeforces.com/contest/1452/problem/F)

> 注：$a$ 就是题面里的 $cnt$。

首先，当 $k\leq \sum_{j=0}^{x}a_j$ 时不需要操作。以下只讨论 $k > \sum_{j=0}^{x}a_j$ 的情况。

考虑我们可以怎么利用这些操作。

1. 把 $x$ 后面的东西，完整地推到 $x$ 位置上。对于第 $i$ ($i>x$) 位而言，需要 $2^{i-x}-1$ 次操作，可以得到 $2^{i-x}$ 个元素。
2. 把前 $1\dots x$ 上的东西，向前推一位。每推 $1$ 次，可以新增 $1$ 个元素。
3. 把 $x$ 后面的东西，不完整地推到 $x$ 上。例如，在第 $i$ ($i>x$) 位上有一个元素，现在我们需要在小于等于 $x$ 的位置上，再增加 $k$ ($k<2^{i-x}$) 个元素。这时就是把第 $i$ 位上的元素，不完整地推到 $x$ 上。操作数为：$\sum_{j=x+1}^{i}\lceil\frac{k}{2^{j-x}}\rceil$。并且显然，$k\leq \sum_{j=x+1}^{i}\lceil\frac{k}{2^{j-x}}\rceil < 2^{i-x}-1$。

显然，尽量优先用第 $1$ 种操作是最优的。因为只有它的【操作次数】是严格小于【增加的元素数量】的。

并且，按照 $i$ 从小到大使用第 $1$ 种操作为最优。具体来说，从小到大扫描所有 $i$，对 $1$ 操作能用就用：每个 $i$ 的用量是 $\min(a_i,\lfloor\frac{\text{rest}}{2^{i-x}}\rfloor)$，然后令 $\text{rest}$ 减去这个用量，考虑 $i+1$。$\text{rest}$ 初始时等于 $k-\sum_{j=0}^{x}a_j$。

> 证明：考虑一种方案，不是按 $i$ 从小到大来使用的，那么一定存在一个较小的 $i_1$ 可以用而没用，并且有另一个较大的 $i_2$ 被用了。现在我们把那个 $i_1$ 用掉。此时要么 $i_2$ 就不需要拆了（操作次数减少），要么 $i_2$ 仍然需要拆，但拆完正好把用掉的 $i_1$ 补上（操作次数不变）。

现在我们已经尽可能多地使用了第 $1$ 种操作。如果在 $x$ 位置恰好新增了 $k-\sum_{j=0}^{x}a_j$ 个元素，那么皆大欢喜，直接输出操作次数。否则记还需要增加的元素数量为 $\text{rest}$。

我们考虑后两种操作。

第 $3$ 种操作的【操作次数】大于等于【增加的元素数量】，而第 $2$ 种操作则是严格等于。所以优先考虑第 $2$ 种操作。对于每个在 $i$ ($1\leq i\leq x$) 位置上的元素，它可以进行 $2^i-1$ 次第 $2$ 种操作。设总共可以进行 $\text{tot}$ 次第 $2$ 种操作，若 $\text{tot}\geq \text{rest}$，则直接做 $\text{rest}$ 次操作，然后输出答案。

否则，不论做不做第 $2$ 种操作，我们必须用第 $3$ 种操作把至少 $1$ 个元素推到 $x$。这个元素原来的位置显然是越小越好，记这个位置为 $i$。我们先用 $i-x$ 次操作，把这个元素推到 $x$。

然后我们发现，接下来每再增加一个元素，用第 $2$ 种操作是否比用第 $3$ 种操作划算，是不一定的。例如，如果把 $2$ 个元素推到 $x$，所花的代价和把 $1$ 个元素推到 $x$ 是一样的。此时可以认为，第 $2$ 个元素新增的代价为 $0$，那显然比用第 $2$ 种操作（代价为 $1$）划算。所以我们从 $i$ 到 $x$，一位一位推，每次推之前决策一下，是用第 $3$ 种操作划算还是用第 $2$ 种操作划算。具体可以见代码。

参考代码：

```cpp
// problem: CF1452F
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mk make_pair
#define lob lower_bound
#define upb upper_bound
#define fi first
#define se second
#define SZ(x) ((int)(x).size())

typedef unsigned int uint;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;

template<typename T> inline void ckmax(T& x, T y) { x = (y > x ? y : x); }
template<typename T> inline void ckmin(T& x, T y) { x = (y < x ? y : x); }

const int MAXN = 30;
int n, q;
ll a[MAXN], ta[MAXN];
void solve(int x, ll K) {
	for (int i = 0; i < n; ++i) ta[i] = a[i];
	
	ll cnt_leq = 0;
	for (int i = 0; i <= x; ++i) {
		cnt_leq += ta[i];
	}
	if (cnt_leq >= K) {
		cout << 0 << endl;
		return;
	}
	ll sum = cnt_leq;
	ll cost = 0;
	for (int i = x + 1; i < n; ++i) {
		ll w = (1LL << (i - x));
		ll buy = min(ta[i], (K - sum) / w);
		ta[i] -= buy;
		ta[x] += buy * w;
		sum += buy * w;
		cost += buy * ((1LL << (i - x)) - 1);
	}
	assert(sum <= K);
	ll cansale = 0;
	for (int i = 1; i <= x; ++i) {
		cansale += ta[i] * ((1LL << i) - 1);
	}
	if (sum + cansale >= K) {
		cost += K - sum;
		cout << cost << endl;
		return;
	}
	for (int i = x + 1; i < n; ++i) {
		ll w = (1LL << (i - x));
		if (ta[i]) {
			assert(sum + w > K);
			for (int j = i; j > x; --j) {
				ll w = (1LL << (j - x));
				ll push = (K - sum) / w + ((K - sum) % w != 0);
				if (x != 0 && push > 1 && (K - sum) % w != 0) {
					push--;
					ll r = (K - sum) % w;
					cost += r;
					sum += r;
				}
				cost += push;
			}
			cout << cost << endl;
			return;
		}
	}
	cout << -1 << endl;
}
int main() {
	cin >> n >> q;
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
	}
	for (int tq = 1; tq <= q; ++tq) {
		int op;
		cin >> op;
		if (op == 1) {
			int p;
			ll v;
			cin >> p >> v;
			a[p] = v;
		} else {
			int x;
			ll K;
			cin >> x >> K;
			solve(x, K);
		}
	}
	return 0;
}
```



---

## 作者：ningago (赞：1)

先把原有的满足条件的数从 $K$ 中减掉。

不难把 split 的数根据指数 $\leq x$ 和 $> x$ 划分。

- 若指数 $i\leq x$，则操作一次相当于一变二，增量 $+1$，且一共可以操作这个数（及这个数延伸出的数）$2^{i}-1$ 次。
- 若指数 $i>x$，则有两种选择：
  - 把 $2^i$ 完全拆分为 $2^{i-x}$ 个 $2^x$，增量 $+2^{i-x}$，耗费 $2^{i-x}-1$ 次操作次数。
  - 把 $2^i$ 不完全的拆分为若干（$<2^{i-x}$） 个 $2^x$，此时与上一种情况进行归纳可知，耗费的操作次数 $\geq 2^{i-x}$。

称其为操作一二三。令“价值”为平均每次操作带了的增量。

有以下性质：

- 操作二的价值严格优于一、三。
  - 所以需要尽可能地进行操作二，而至多进行一次操作三作为调整。
- $i$ 更小时操作二的价值更优。
- 操作二 $i$ 选取越小越能使最后操作三调整范围变小。

所以可以先贪心从小到大对于每个 $i>x$，能进行操作二就进行（$K$ 不能减成负的）。

此时，若 $K$ 减到了 $0$ ，或只用操作一就可以满足条件，就可以直接计算答案。（注意进行操作二会增加操作一的可操作次数）

否则，令最小的没被使用的 $>x$ 的数为 $2^j$，需要对 $j$ 进行操作三。

- 把 $2^j$ 拆分成两个 $2^{j-1}$。
  - 若 $2^{j-1}$ 可以进行操作二（显然不可以两个都进行），则对其中一个进行操作二。
  - 否则舍弃一个 $2^{j-1}$。
- 递归到子问题，判断此时 $K$ 是否可以用操作一满足条件。

```cpp
#define N 33
int n, m;
int cnt[N], tmp[N]; 
int calc(int x, int K)
{
	for(int i = 0; i <= x; i++) K -= cnt[i]; if(K < 0) return 0;
	int leqx = 0, res = 0;
	for(int i = 0; i <= x; i++) leqx += cnt[i] * ((1 << i) - 1);
	for(int i = x + 1; i < n; i++)
	{
		int tot = std::min(cnt[i], K >> (i - x));
		res += tot * ((1 << (i - x)) - 1);
		leqx += tot * (1 << (i - x)) * ((1 << x) - 1);
		K -= tot * (1 << (i - x));
		tmp[i] = tot;
	}
	if(K <= 0) return res;
	if(K <= leqx) return res + K;
	int j = x + 1;
	for(; j < n && tmp[j] == cnt[j]; j++);
	if(j == n) return -1;
	for(int i = j; i > x; i--)
	{
		if(K <= leqx) return res + K;
		res++;
		int v = 1 << (i - 1 - x);
		if(v <= K)
		{
			res += v - 1;
			K -= v;
			leqx += v * ((1 << x) - 1);
		}
	}
	if(K <= leqx) return res + K;
	return -1;
}

void solve()
{
	n = read(), m = read();
	for(int i = 0; i < n; i++) cnt[i] = read();
	for(int i = 1, op, x, y; i <= m; i++)
	{
		op = read(), x = read(), y = read();
		if(op == 1) cnt[x] = y;
		else 
		{
			int ans = calc(x, y);
			print(ans, '\n');
		}
	}
}
```

---

## 作者：Tx_Lcy (赞：0)

## 思路

分析一下题目，可以得到一些简单的性质：

- 操作一个能够操作的 $\le 2^x$ 的数一次会新增一个 $\le 2^x$ 的数。

- 最终答案肯定形如选择若干个 $>2^x$ 的数将它们变成 $2^x$，并且选择的数一定是 $>2^x$ 的数中最小的几个。然后设有 $cnt$ 个 $\le 2^x$ 的数，答案就是前面的操作次数加上 $k-cnt$。

因此我们考虑枚举 $i \in [x+1,n)$，表示我变成 $2^x$ 的那些数全都是 $\le 2^i$ 的，然后计算答案。

我们考虑一共有 $cnt_i$ 个 $2^i$，如果把它们都变成 $2^x$ 需要 $cnt_i \times (2^{i-x}-1)$ 次操作，但是变出了 $cnt_i \times 2^{i-x}$ 个 $2^x$，也就是说平均代价 $<1$，比操作一个 $\le 2^x$ 优秀，那么我们如果能变肯定全变。

现在我们只需考虑 $\sum_{j=x+1}^{i} cnt_j \times 2^{j-x}+res>k$ 的情况（$res=\sum_{j=0}^x cnt_j$），也就是无法全变完。

我们设有 $A$ 个 $2^i$ 能够完全拆成 $2^{i-x}$ 个 $2^x$，首先显然这 $A$ 个 $2^i$ 是全变的，我们设 $B$ 表示再来一个 $2^i$ 最多能变成几个 $2^x$。

暴力的想法就是直接枚举这个 $2^i$ 变成了 $s$ 个 $2^x$，然后计算需要几次操作，这样显然是无法接受的，我们考虑如果 $s$ 不是 $2$ 的幂次一定是不优的，因为这样平均代价就 $>1$ 了，所以只需枚举 $2$ 的幂次即可，可以 $\Theta(1)$ 计算所需的操作次数。

时间复杂度 $\Theta(nq)$。

## 代码

```cpp
//A tree without skin will surely die.
//A man without face will be alive.
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define rep(i,j,k) for(int i=j;i<=k;++i)
#define per(i,j,k) for(int i=j;i>=k;--i)
int n,q,cnt[55],op,x,y;
inline int get(int dep,int qz){
	if (!qz) return 0;
	if (!dep && qz==1) return 0;
	if (qz<=(1<<(dep-1))) return get(dep-1,qz)+1;
	else return get(dep-1,qz-(1<<(dep-1)))+(1<<(dep-1));
}
inline int work2(int sm){
	int tot=0;
	rep(i,1,x){
		int val=cnt[i]*((1<<i)-1);
		tot+=val;
	}
	int res=0,cha=y-sm,sg=0,gg=1e18;
	if (cha<=0) return 0;
	rep(i,x+1,n-1){
		int val=cnt[i]*(1<<(i-x));
		if (sg+val>=cha){
			int wan=(cha-sg)/(1<<(i-x));
			res+=wan*((1<<(i-x))-1);
			sg+=wan*(1<<(i-x));
			if (sg*(1<<x)+tot>=cha) gg=min(gg,res+cha-sg);
			int dur=cha-sg;
			for (int T=1,pw=0;T<=dur;T<<=1,++pw)
				if ((sg+T)*(1<<x)+tot>=cha) gg=min(gg,res+cha-sg-T+i-x-pw+T-1);
			res+=get(i-x,dur),sg=cha;
			break;
		}
		sg+=val,res+=cnt[i]*((1<<(i-x))-1);
	}
	res+=cha-sg,gg=min(gg,res);
	if (sg*(1<<x)+tot>=cha) return gg;
	return 1e18;
}
inline void solve(){
	cin>>n>>q;
	rep(i,0,n-1) cin>>cnt[i];
	while (q--){
		cin>>op>>x>>y;
		switch (op){
			case 1:{
				cnt[x]=y;
				break;
			}
			case 2:{
				int sm=0;
				rep(i,0,x) sm+=cnt[i];
				if (sm>=y){
					cout<<"0\n";
					continue;
				}
				int res=work2(sm);
				if (res<1e18) cout<<res<<'\n';
				else cout<<"-1\n";
				break;
			}
		}
	}
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	int t=1;
	// cin>>t;
	while (t--) solve();
	return 0;
}
```

---

