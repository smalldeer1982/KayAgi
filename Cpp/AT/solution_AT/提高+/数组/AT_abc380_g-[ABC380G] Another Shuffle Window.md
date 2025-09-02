# [ABC380G] Another Shuffle Window

## 题目描述

[问题链接](https://atcoder.jp/contests/abc380/tasks/abc380_g)

给定一个排列 $P = (1, 2, \dots, N)$ 和一个整数 $K$。

请计算经过以下操作后，排列 $P$ 的**逆序对数**的期望值模 $998244353$ 的结果：

- 首先，从 $1$ 到 $N-K+1$ 的整数中随机均匀地选择一个整数 $i$；
- 然后，将子数组 $P_i, P_{i+1}, \dots, P_{i+K-1}$ 进行随机均匀打乱。



#### 逆序对是什么？

>  对于一个数组 $(A_1, A_2, \dots, A_N)$，逆序对是满足 $1 \leq i < j \leq N$ 且 $A_i > A_j$ 的整数对 $(i, j)$ 的个数。

#### 期望值模 $998244353$ 是什么？

> 在本问题的约束条件下，期望值可以表示为一个分数 $\frac{P}{Q}$，且 $Q \not \equiv 0 \pmod{998244353}$。  
> 因此可以找到一个唯一的整数 $R$ 满足：
> $$
> R \times Q \equiv P \pmod{998244353}, \quad 0 \leq R < 998244353
> $$
> 你需要输出这个整数 $R$。

## 说明/提示

#### 约束条件

- 所有输入均为整数；
- $1 \leq K \leq N \leq 2 \times 10^5$；
- $P$ 是 $(1, 2, \dots, N)$ 的一个排列。

#### 样例解释 1

通过操作，排列 $P$ 会变为以下形式：

- $(1, 4, 2, 3)$ —— 概率 $\frac{1}{2}$；
- $(4, 1, 2, 3)$ —— 概率 $\frac{1}{6}$；
- $(1, 2, 4, 3)$ —— 概率 $\frac{1}{6}$；
- $(1, 4, 3, 2)$ —— 概率 $\frac{1}{6}$。

对应的逆序对数期望值为：
$$
\displaystyle 2 \times \frac{1}{2} + 3 \times \frac{1}{6} + 1 \times \frac{1}{6} + 3 \times \frac{1}{6} = \frac{13}{6}
$$

将 $\frac{13}{6}$ 转换为模 $998244353$ 的结果为 $166374061$，因此输出 $166374061$。

Translated By [$\mathtt{Mr\_Az}$](/user/536560)。

## 样例 #1

### 输入

```
4 2
1 4 2 3```

### 输出

```
166374061```

## 样例 #2

### 输入

```
1 1
1```

### 输出

```
0```

## 样例 #3

### 输入

```
10 6
7 4 10 5 6 1 8 2 3 9```

### 输出

```
499122200```

# 题解

## 作者：Milthm (赞：23)

如你所见，这是一道 diff 为 $1995$ 的题目，看上去十分困难。

你十分惊慌，恐怕这道题你根本就无法做出来，马上就要面临着 rating $-114$ 的到来。

你冷静地思考了一会，发现这是你最擅长的逆序对题目，你逐渐有了一些自信。

你发现如果把序列分成三段：$[1,i-1],[i,i+k-1],[i+k,n]$，那么三段之间互相的逆序对影响不会改变，设总的逆序对数量为 $s$，当前长度为 $k$ 的区间里的逆序对数量为 $t$，则只要求出 $s-t$，再加上这段区间的期望逆序对数量，最后除以 $n-k+1$ 就好了。

前面这一步可以用树状数组快速解决，但是区间的期望逆序对数量该如何求出？

在耀眼的光芒中，你看见了可爱的 lxy，她只给了你六个字符 [CF749E](https://www.luogu.com.cn/problem/CF749E)，让你自己领会。

在艰难的探索中，你终于发现，因为两个数形成逆序对的概率是 $\frac{1}2$，所以 $\frac{1}2C_n^2$ 就是长度为 $n$ 的排列的期望逆序对数。

你非常高兴，很快就打出了一份代码，它十分的正确，仅一遍就通过了样例，并获得了一个绿色的 AC。


```cpp
#include<bits/stdc++.h>
#define int long long
#define N 200005
using namespace std;
const int mod=998244353;
int n,k,a[N],sum,now,ans;
struct BIT{
	int c[N];
	void add(int x,int k){while(x<=n)c[x]+=k,x+=x&-x;}
	int ask(int x){int ans=0;while(x)ans+=c[x],x-=x&-x;return ans;}
	void clear(){memset(c,0,sizeof(c));}
}A;
int inv(int x,int y=mod-2){
	int ans=1;
	while(y){
		if(y&1)ans=ans*x%mod;
		x=x*x%mod;y>>=1;
	}
	return ans;
}
signed main(){
	cin>>n>>k;
	for(int i=1;i<=n;++i)cin>>a[i];
	for(int i=n;i>=1;--i)sum+=A.ask(a[i]),A.add(a[i],1);
	A.clear();
	for(int i=k;i>=1;--i)now+=A.ask(a[i]),A.add(a[i],1);
	ans=sum-now;
	for(int i=1;i<=n-k;++i){
		A.add(a[i],-1);
		now-=A.ask(a[i]);now+=A.ask(n)-A.ask(a[i+k]);
		A.add(a[i+k],1);ans=(ans+sum-now)%mod;
	}
	cout<<(ans*inv(n-k+1)+k*(k-1)%mod*inv(4))%mod;
	return 0;
}

```

你醒过来，原来这一切都是梦。

你根本就没有看 G，而是被 F 卡了半个多小时，注定只能获得一个失败的青色 perf。

---

## 作者：PineappleSummer (赞：8)

[G - Another Shuffle Window](https://atcoder.jp/contests/abc380/tasks/abc380_g)

对于一个长度为 $k$ 的两两不同的序列，其期望逆序对数为 $\dfrac{k\times (k-1)}{4}$。

因为序列中一共有 $\dfrac{k\times (k-1)}{2}$ 对数，每一对为逆序对的概率为 $\dfrac{1}{2}$，所以其期望逆序对数为 $\dfrac{k\times (k-1)}{4}$。

设原序列的逆序对数为 $C$，$[i,i+k-1]$ 这个区间的逆序对数为 $x$。

将 $[i,i+k-1]$ 随机打乱之后，由于只改变了 $[i,i+k-1]$ 这个区间内部的逆序对，整个序列期望的逆序对数变为 $C-x+\dfrac{k\times (k-1)}{4}$。

那么只需要求出 $x$ 就做完了。

设 $[i,i+k-1]$ 的逆序对数为 $x$，那么将区间改变为 $[i+1,i+k]$ 时逆序对数怎么变化呢？

区间平移过后，减少了 $p_i$ 对答案的贡献，具体就是答案减少了 $[i + 1，i+k-1]$ 中比 $p_i$ 小的数的个数。

增加了 $p_{i+k}$ 对答案的贡献，具体就是答案增加了 $[i+1,i+k-1]$ 中比 $p_{i+k}$ 大的数的个数。

上述操作用 Fenwick Tree 维护即可。

由于有 $n-k+1$ 个区间，将每个区间的答案累加后，还要乘上 $\dfrac{1}{n-k+1}$。

总时间复杂度 $\mathcal O(n\log n)$。

[参考代码](https://atcoder.jp/contests/abc380/submissions/59928945)

---

## 作者：qfy123 (赞：3)

# Solution
在做此题之前，先要知道一个结论：
- 给定一个长度为 $n$ 的序列 $a$，保证序列内的数字**两两不同**，那么随机打乱后形成逆序对**个数**的**期望**是 $\frac{n(n - 1)}{4}$。
> 证明：一个长度为 $n$ 的序列内会有 $\frac{n(n - 1)}{2}$ 对数，每一对数向逆序对个数贡献的期望值为 $\frac{1}{2}$（因为一对数要么是逆序对，要么是顺序对），由此即证。

随机在 $[1,n-k+1]$ 中选一个数 $i$，选到每个 $i$ 的概率为 $\frac{1}{n-k+1}$。然后，对于选中的区间 $[i, i + k - 1]$，我们先计算这个区间内逆序对的个数 $cnt_i$，整个序列逆序对个数 $cnt_0$，以及一个长度为 $k$ 的区间随机打乱后的逆序对个数的期望 $E = \frac{k(k-1)}{4}$，此时对期望的贡献为：

$$\frac{cnt_0 - cnt_i + E}{n-k+1}$$

那么答案就是：

$$\sum_{i=1}^{n-k+1} \frac{cnt_0 - cnt_i + E}{n-k+1} \pmod {998244353}$$

如何快速求出每个 $cnt_i$ 呢？首先算出 $cnt_1$ 的值，然后，每次将长度为 $k$ 的区间向右滑动的时候，先减去 $p_i$ 的贡献，再加上 $p_{i+k}$ 的贡献，这样就能在 $O(\log n)$ 的复杂度下将该区间向右滑动一次。具体详见代码。

最后，由于模数是质数，根据费马小定理，一个数 $x$ 模 $p$ 意义下的逆元（$\frac{1}{x}$ 对 $p$ 取模的结果）就是 $x^{p-2} \pmod p$，用快速幂求即可。
# Code
```cpp
#include<bits/stdc++.h>
#define int long long 
#define ull unsigned long long
#define ri register int
#define rep(i,j,k) for(ri i=(j);i<=(k);++i) 
#define per(i,j,k) for(ri i=(j);i>=(k);--i)
#define repl(i,j,k,l) for(ri i=(j);(k);i=(l))
#define IOS ios::sync_with_stdio(false);cin.tie(0);cout.tie(0)
#define pc(x) putchar(x)
#define fir first
#define se second 
#define MP pair<int,int>
#define pii pair<int,int>
#define PB push_back
#define lson p << 1
#define rson p << 1 | 1
#define ls(p) tr[p].ch[0]
#define rs(p) tr[p].ch[1]
using namespace std;
char BUFFER[100000],*P1(0),*P2(0);
#define gtc() (P1 == P2 && (P2 = (P1 = BUFFER) + fread(BUFFER,1,100000,stdin), P1 == P2) ? EOF : *P1++)
inline int R(){
    int x;char c;bool f = 0;
	while((c = gtc()) < '0') if(c == '-') f = 1;
	x = c ^ '0';
	while((c = gtc()) >= '0') x = (x << 3) + (x << 1) + (c ^ '0');
	return f?(~x + 1):x;
}
inline string Rs(){
	string str = "";
	char ch = gtc();
	while(ch == ' ' || ch == '\n' || ch == '\r') ch = gtc();
	while(ch != ' ' && ch != '\n' && ch != '\r' && ch > '\0') str += ch, ch = gtc();
	return str;
}
inline int rS(char s[]){
	int tot = 0; char ch = gtc();
	while(ch == ' ' || ch == '\n' || ch == '\r') ch = gtc();
	while(ch != ' ' && ch != '\n' && ch != '\r' && ch > '\0') s[++tot] = ch, ch = gtc();
	return tot; 
}
inline void O(int x){
    if(x < 0) pc('-'),x = -x;
    if(x < 10) pc(x + '0');
    else O(x / 10),pc(x % 10 + '0');
}
inline void out(int x,int type){
	if(type == 1) O(x),pc(' ');
	if(type == 2) O(x),pc('\n');
	if(type == 3) O(x);
}
inline void Ps(string s, int type){
	int m = s.length();
	rep(i, 0, m - 1) pc(s[i]); 
	if(type == 1) pc(' ');
	if(type == 2) pc('\n');
}
inline void pS(char *s, int type){
	int m = strlen(s + 1);
	rep(i, 1, m) pc(s[i]);
	if(type == 1) pc(' ');
	if(type == 2) pc('\n');
}
inline void OI(){
	freopen(".in","r",stdin);
	freopen(".out","w",stdout);
}
const int N = 2e5 + 10;
const int mod = 998244353;
int tr[N], n, k, p[N], ans, tot, cnt;
inline int lowbit(int x){
	return x & (-x);
}
inline void mdf(int x, int v){
	while(x <= N - 10){
		tr[x] += v;
		x += lowbit(x);
	}
}
inline int sum(int x){
	int ret = 0;
	while(x){
		ret += tr[x];
		x -= lowbit(x);
	}
	return ret;
}
inline int qry(int l, int r){return sum(r) - sum(l - 1);}
inline int ksm(int a, int b){
	int ret = 1;
	while(b){
		if(b & 1) ret = (ret * a) % mod;
		a = (a * a) % mod;
		b >>= 1;
	}
	return ret;
}
inline void solve(){
	n = R(), k = R();
	rep(i, 1, n) p[i] = R();
	rep(i, 1, n){
		tot += qry(p[i] + 1, n);
		mdf(p[i], 1);
		if(i == k) cnt = tot; 
	}
	per(i, n, k + 1) mdf(p[i], -1);//初始时，将 p[1...k] 加入树状数组中，cnt 记录的是 [1, k] 的逆序对数
	int E = k * (k - 1) % mod * ksm(4, mod - 2) % mod;
 	rep(i, 1, n - k + 1){
		ans = (ans + (tot - cnt + E + mod) % mod * ksm(n - k + 1, mod - 2) % mod) % mod;
		if(i == n - k + 1) return out(ans, 2), void();
		cnt -= sum(p[i] - 1); mdf(p[i], -1); //减去 p[i] 的贡献
		cnt += qry(p[i + k] + 1, n); mdf(p[i + k], 1); //加上 p[i + k] 的贡献
		//在上面两次操作后，cnt 表示的区间滑动到了 [i + 1, i + k]
	}
}
signed main(){
    // OI();
    int T = 1;
    // T = R();
	while(T--) solve();
	return 0;
}

```

---

## 作者：hellolin (赞：2)

下文下标统一从 $0$ 开始。

每个 $i$ 对答案造成的贡献由两部分构成：

1. $[i, i+k)$ 内均匀随机排列的逆序对。
2. 除此之外的逆序对。即，设逆序两数下标为 $x,y$，不同时满足 $x\in [i, i+k)$ 和 $y\in [i, i+k)$ 的逆序对。

> **定理**：均匀随机地生成一个含 $k$ 个数的排列，它的逆序对期望个数为 $\frac{k(k-1)}{4}$。
>
> **证明**：对于 $k=1$，结论显然。
>
> 对于 $k>1$，考虑一个排列 $a$，将他反转后的序列 $\operatorname{reverse}(a)$ 也是合法的排列。这两个排列正序对和逆序对恰好相反，故他们的逆序对和为 $\frac{k(k-1)}{2}$。
>
> 这样的排列共有 $\frac{k!}{2}$ 组，故期望对数为 $\frac{k(k-1)}{4}$。

根据以上定理能够 $O(1)$ 算出第一部分的贡献。

第二部分的贡献为 $[0, n)$ 内的逆序对数减去 $[i, i+k)$ 内的（原序列上的）逆序对数。使用树状数组动态维护即可。这部分的代码：

``` cpp
for (int i = 0; i < n; ++i) {
  int current = tr.sum(n) - tr.sum(a[i]);
  res1 += current;
  res1 %= Mod;
  if (i < k) {
    res2 += current;
    res2 %= Mod;
  }
  tr.add(a[i], 1);
}
for (int i = k; i < n; ++i) {
  tr.add(a[i], -1);
}
for (int i = k; i < n; ++i) {
  ans += ((res1 - res2) % Mod + Mod) % Mod;
  ans %= Mod;
  tr.add(a[i - k], -1);
  res2 -= tr.sum(a[i - k]);
  res2 += tr.sum(n) - tr.sum(a[i]);
  res2 %= Mod;
  tr.add(a[i], 1);
}
ans += ((res1 - res2) % Mod + Mod) % Mod;
ans %= Mod;
```

总时间复杂度 $O(n\log n)$。

---

## 作者：luanyanjia (赞：2)

题目大意：给定 $n,k$ 和一个长度为 $n$ 的排列，问随机选择一个长度为 $k$ 的区间进行随机打乱，排列的逆序对数的期望。

考虑对每一个长度为 $k$ 的区间分别计算答案。先计算随机打乱的这个区间对其他数的贡献，也就是总逆序对数减去原来区间内的逆序对数。这一部分我们在移动区间的时候用树状数组直接计算即可。然后就是区间内部的贡献，一个长为 $m$ 的区间随机打乱之后，对于所有的 $\dfrac{m \times (m-1)}{2}$ 个二元组，显然都有 $\dfrac{1}{2}$ 的概率构成逆序对，因此答案再加上 $\dfrac{k \times (k-1)}{4}$ 即可。

代码：
```cpp

#include<bits/stdc++.h>
using namespace std;
inline void rd(){}
template<typename T,typename ...U>
inline void rd(T &x,U &...args){
	char ch=getchar();
	T f=1;x=0;
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=(x<<1)+(x<<3)+(ch^48),ch=getchar();
	x*=f;rd(args...);
}
const int N=2e5+5,mod=998244353;
int n,k,p[N];
inline int KSM(int x,int n){
	int ans=1;
	while(n){
		if(n&1)ans=1ll*x*ans%mod;
		x=1ll*x*x%mod;
		n>>=1;
	}
	return ans;
}
int t[N];
inline void Add(int x,int v){while(x<=n)t[x]+=v,x+=x&-x;}
inline int Query(int x){int ans=0;while(x)ans+=t[x],x-=x&-x;return ans;}
inline void Insert(int x,int &sum){
	(sum+=(Query(n)-Query(x-1)+mod)%mod)%=mod;
	Add(x,1);
}
inline void Delete(int x,int &sum){
	Add(x,-1);
	(sum+=mod-Query(x))%=mod;
}
signed main(){
	rd(n,k);
	for(int i=1;i<=n;i++)rd(p[i]);
	int now=0,ans=0,sum=0;
	for(int i=1;i<=n;i++)Insert(p[i],sum);
	memset(t,0,sizeof t);
	for(int i=1;i<=k;i++)Insert(p[i],now);
	const int INV=KSM(n-k+1,mod-2),SUM=1ll*(k-1)*k%mod*KSM(4,mod-2)%mod;
	for(int i=1;i+k-1<=n;i++){
		(ans+=INV*(0ll+sum-now+SUM+mod)%mod)%=mod;
		if(i+k-1<n){
			Insert(p[i+k],now);
			Delete(p[i],now);
		}
	}printf("%d\n",ans);
	return 0;
}


```

---

## 作者：GoldSpade (赞：2)

~~纪念一个因打游戏而错过的水题。~~

### 题意 [ABC380G](https://www.luogu.com.cn/problem/AT_abc380_g)

给定长为 $N$ 的排列 $P$ 和常数 $K$，等概率选取一个长为 $K$ 的区间随机打乱，求最终序列逆序对数的期望。

### 思路

回忆使用 $\mathtt{BIT}$ 求逆序对的过程，他的主要思想是对每个元素算贡献，也就是对于每个 $P_i$，求满足 $j<i$ 且 $P_j>P_i$ 的个数，加和就得到逆序对数。

题目中只选取了一个长度为 $K$ 的区间随机打乱，容易发现**除了区间内的元素，其他元素对逆序对的贡献均不会发生变化**。于是我们就把问题划分成了两个子问题：

1. 求原序列的逆序对数，记为 $x$。

2. 求某个长为 $K$ 的区间随机打乱后逆序对数变化 $\Delta x$。

两个子问题的解决方案如下：

1. 归并排序或 $\mathtt{BIT}$。

2. 已知原序列是一个排列，因此不需要担心元素相等的情况，于是这个区间的元素可以等价为一个排列。你可以通过如下方式得知长为 $K$ 的**随机排列**逆序对数的期望值为 $\dfrac{K(K-1)}{4}$：

    - OEIS，打表找规律。

    - 直接推，每一个数对 $(a,b)$（$1\le a < b \le K$）可以对期望产生 $\dfrac{1}{2}$ 的贡献。
  
   变化量 $\Delta x$ 就直接是这个期望值减去原逆序对数。

### solution

- 使用任意方式求出排列的逆序对数，加入答案。

- 使用 $\mathtt{BIT}$ 或线段树等支持单修区查的数据结构动态维护每个长为 $K$ 的区间的逆序对数 $x$；这一步**先去掉**超出区间的元素贡献，**再加上**新加入元素的贡献，类似于滑动窗口。

  答案加上 $\left(\dfrac{K(K-1)}{4}-x\right)\times \dfrac{1}{N-K+1}$，也就是期望变化量。求有理数取模的过程一般使用快速幂，详见[乘法逆元](https://oi-wiki.org/math/number-theory/inverse/#%E5%BF%AB%E9%80%9F%E5%B9%82%E6%B3%95)。

- 输出答案。时间复杂度 $\mathcal O(N \log N)$，空间复杂度 $\mathcal O(N)$。

### code

```cpp
#include <bits/stdc++.h>
#define FASTIO ios::sync_with_stdio(false), cin.tie(0), cout.tie(0)
#define rep(i, l, r) for (int i = l; i <= r; i++)
#define per(i, r, l) for (int i = r; i >= l; i--)
#define cnt1(x) __builtin_popcount(x)
#define int long long
using namespace std;
const int N = 2e5+5, M = 2e6+5, mod = 998244353;
typedef long long LL;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
int n, K, a[N], ans, now, c[N];
// now 表示滑动到某个区间的逆序对数
inline void add(int x, int v) {
	for (; x <= n; x += x & -x) c[x] += v;
}
inline int ask(int x) {
	int res = 0;
	for (; x; x -= x & -x) res += c[x];
	return res;
}
inline int qpow(int a, int b) {
	int res = 1;
	for (; b; b >>= 1) {
		if (b & 1) res = a * res % mod;
		a = a * a % mod;
	}
	return res;
}
signed main() {
	FASTIO;
	cin >> n >> K;
	rep(i, 1, n) cin >> a[i];
	rep(i, 1, n) {
		ans += i-1-ask(a[i]);
		add(a[i], 1);
	}// 求最初逆序对，使用的是 BIT
	memset(c, 0, sizeof c);
	int inv = qpow(4, mod-2), inv2 = qpow(n-K+1, mod-2);
	rep(i, 1, n) {
		if (i > K) now -= ask(a[i-K]-1), add(a[i-K],-1);// 删去超出区间的元素及其贡献
		now += ask(n)-ask(a[i]);// 加入新元素的贡献
		if (i >= K) ans = (ans+(K*(K-1)%mod*inv%mod-now%mod+mod)%mod*inv2)%mod;
		add(a[i], 1);// 加入新元素
	}
	cout << ans;
	return 0;
}
```

---

## 作者：2huk (赞：2)

https://atcoder.jp/contests/abc380/tasks/abc380_g

唉。

> 给定 $n$ 的排列 $p$。你需要随机选择一个长度为 $k$ 的区间，并将其随机打乱。求期望逆序对。

不妨枚举打乱的区间为 $[l, l+k-1]$。此时一个逆序对 $i < j$ 会有 $6$ 种情况。

1. $l \le i < j \le l+k-1$：不难发现恰好有一半的打乱方案能使得 $p_i > p_j$。于是答案为 $1/2$。所有这样的 $i, j$ 的贡献和为 $k(k-1)/4$。

2. $i < l \le l +k-1 < j$：这跟打乱没有关系，原来的逆序关系保持不变。

   考虑 $[l-1,l+k-2]$ 到 $[l, l+k-1]$ 的答案的增量。不难发现：

   - 满足 $i \le l - 2,j=l+k-1$ 的逆序对取消了贡献。
   - 满足 $i=l-1,j \ge l+k$ 的逆序对加入了贡献。

   求这两种逆序对的数量可以可持久化线段树。

3. $i < l \le j \le l+k-1$：仍然考虑考虑 $[l-1,l+k-2]$ 到 $[l, l+k-1]$ 的答案的增量。

   - 满足 $i \le l-2,j = l-1$ 的逆序对取消了贡献；
   - 满足 $i=l-1,l \le j \le l+k-1$ 的逆序对加入了贡献。

   可持久化线段树。

4. $l \le i \le l+k-1 < j$：

   - 满足 $l-1 \le i \le l+k-2,j=l+k-1$ 的逆序对取消了贡献；
   - 满足 $i = l +k-1,j \ge l+k$ 的逆序对加入了贡献。

5. $i < j < l$：预处理前缀和。

6. $r < i < j$：预处理后缀和。

```cpp
#include "bits/stdc++.h"

using namespace std;

#define int long long

const int N = 2e5 + 10, P = 998244353;

int fpm(int a, int b) {
  int res = 1;
  while (b) {
    if (b & 1) res = 1ll * res * a % P;
    b >>= 1, a = 1ll * a * a % P;
  }
  return res;
}

int n, k, a[N];

int root[N], idx;

struct Node {
  int l, r, v;
}tr[N * 40];

int build(int l, int r) {
  int u = ++ idx;
  if (l != r) {
    int mid = l + r >> 1;
    tr[u].l = build(l, mid);
    tr[u].r = build(mid + 1, r);
  }
  return u;
}

void pushup(int u) {
  tr[u].v = tr[tr[u].l].v + tr[tr[u].r].v;
}

int modify(int u, int l, int r, int x) {
  int v = ++ idx;
  tr[v] = tr[u];
  if (l == r) tr[v].v ++ ;
  else {
    int mid = l + r >> 1;
    if (x <= mid) tr[v].l = modify(tr[v].l, l, mid, x);
    else tr[v].r = modify(tr[v].r, mid + 1, r, x);
    pushup(v);
  }
  return v;
}

int query(int u, int tl, int tr, int l, int r) {
  if (tl >= l && tr <= r) return ::tr[u].v;
  int mid = tl + tr >> 1, res = 0;
  if (l <= mid) res = query(::tr[u].l, tl, mid, l, r);
  if (r > mid) res += query(::tr[u].r, mid + 1, tr, l, r);
  return res;
}

int work(int l, int r, int x, int y) {
  if (l > r || x > y) return 0;
  return query(root[r], 0, n + 1, x, y) - (l ? query(root[l - 1], 0, n + 1, x, y) : 0);
}

int fac[N];
int pre[N], suf[N];

signed main() {
  fac[0] = 1;
  for (int i = 1; i < N; ++ i ) fac[i] = 1ll * fac[i - 1] * i % P;

  cin >> n >> k;

  root[n + 2] = build(0, n + 1);
  root[0] = modify(root[n + 2], 0, n + 1, 0);
  for (int i = 1; i <= n; ++ i ) {
    cin >> a[i];
    root[i] = modify(root[i - 1], 0, n + 1, a[i]);
  }
  a[n + 1] = a[n + 2] = n + 1;
  root[n + 1] = modify(root[n], 0, n + 1, n + 1);
  root[n + 2] = modify(root[n + 1], 0, n + 1, n + 1);
	
	for (int i = 1; i <= n; ++ i ) {
		pre[i] = work(0, i - 1, a[i] + 1, n + 1) + pre[i - 1];
	}
	for (int i = n; i; -- i ) {
		suf[i] = work(i + 1, n + 1, 0, a[i] - 1) + suf[i + 1];
	}
	
  int res = 0;
  long long lst1 = 0, lst2 = 0, lst3 = 0;

  for (int l = 1; l + k - 1 <= n; ++ l ) {
    lst1 = (lst1 - work(0, l - 2, a[l + k - 1] + 1, n + 1));
    lst1 = (lst1 + work(l + k, n, 0, a[l - 1] - 1));
		
    res = (res + lst1) % P;
  }
  
  for (int l = 1; l + k - 1 <= n; ++ l ) {
    lst2 = (lst2 - work(0, l - 2, a[l - 1] + 1, n + 1));
    lst2 = (lst2 + work(0, l - 1, a[l + k - 1] + 1, n + 1));
    lst2 = (lst2 + work(l, l + k - 1, 0, a[l - 1] - 1));
    lst2 = (lst2 - (a[l - 1] > a[l + k - 1]));
    
    res = (res + lst2) % P;
  }
  
  for (int r = n; r - k + 1 >= 1; -- r ) {
    lst3 = (lst3 - work(r + 2, n, 0, a[r + 1] - 1));
    lst3 = (lst3 + work(r + 1, n, 0, a[r - k + 1] - 1));
    lst3 = (lst3 + work(r - k + 1, r, a[r + 1] + 1, n + 1));
    lst3 = (lst3 - (a[r - k + 1] > a[r + 1]));
    res = (res + lst3) % P;
  }
  
  for (int l = 1, r = k; r <= n; ++ l, ++ r )
  	res = (res + pre[l - 1] + suf[r + 1]) % P;

  cout << (1ll * res * fpm(n - k + 1, P - 2) % P + 1ll * k * (k - 1) % P * fpm(4, P - 2) % P) % P;

  return 0;
}
```

---

## 作者：SunsetLake (赞：1)

## Solution

操作中每次选取的 $i$ 都是均匀随机的，所以每种情况的概率都一样，那我们就可以先求出所有情况逆序对的总和，再除以概率就好了。

问题便被转化为对于每个 $i \in [1,n - k + 1]$，求出将 $i \sim i + k - 1$ 随机排列后形成的 $k!$ 种序列 $P$ 的逆序对总和。

固定一个 $i$ 后，考虑如何计算当前这 $k!$ 种排列的逆序对数。注意到变化的只有 $i \sim i + k - 1$，那么 $[1,i - 1]$ 和 $[i + k,n]$ 产生的逆序对数都是不会变的，他们的贡献就是 （原序列）总的逆序对之和 减去 $[i,i + k - 1]$ 之间（原序列上）任意两个数产生的逆序对之和。这个东西可以用类似滑动窗口的思想维护，假设已经知道了 $[i - 1,i + k - 2]$ 的值，那么只需要将 $i - 1$ 的贡献删除，再加入 $i + k - 1$ 的贡献就可以得到当前的答案了，用两个树状数组维护即可。

剩下的就是 $[i,i + k - 1]$ 任意排列得到的逆序对总数。由于逆序对只看相对大小关系，于是可以看做是一个 $1 \sim k$ 的排列任意排列求总逆序对数。这个问题十分经典，答案就是 $\frac{k!}{2} \times \binom{k}{2}$。这里给一个大概的证明：举个 $k = 5$ 的例子，取出两个“相反”的排列，如 $13425$ 和 $52431$，那么任意一对数（如 $1,4$）一定会在一个排列中是“正序”（逆序对为 $0$），在另一个排列中是“倒序”（逆序对为 $1$），最终产生 $1$ 的贡献。于是两个排列的答案就是“一对数”的数量，也就是 $\binom{k}{2}$，两个排列的个数是 $\frac{k!}{2}$，于是答案就是$\frac{k!}{2} \times \binom{k}{2}$ 了。

把所有情况的答案加起来，最后除以概率 $(n - k + 1) \times k!$ 即可。

## code
```cpp
#include<bits/stdc++.h>
#define ll long long
#define pb push_back
using namespace std;
const int N = 2e5 + 5,mod = 998244353;
int n,k,a[N];
ll ans,fac;
ll c[N],d[N];
void add(int i,int x){
	for(;i;i -= i & -i) c[i] += x;
}
ll query(int i){
	int res = 0;
	for(;i <= n;i += i & -i) res += c[i];
	return res;
}
void add1(int i,int x){
	for(;i <= n;i += i & -i) d[i] += x;
}
ll query1(int i){
	int res = 0;
	for(;i;i -= i & -i) res += d[i];
	return res;
}
ll qpow(ll x,ll y){
	ll res = 1;
	while(y){
		if(y & 1) res = res * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return res;
}
signed main(){
	cin >> n >> k;
	for(int i = 1;i <= n;++ i) cin >> a[i];
	fac = 1;
	for(int i = 1;i <= k;++ i) fac = fac * i % mod;
	ll tot = 0;
	for(int i = 1;i <= n;++ i){
		tot += query(a[i]);
		add(a[i],1);
	}
	ll q = qpow(fac * (n - k + 1) % mod,mod - 2);
	ll inv2 = qpow(2,mod - 2);
	ll kk = 1ll * k * (k - 1) / 2;kk %= mod;
	kk = kk * fac % mod * inv2 % mod;
	for(int i = 1;i <= n;++ i) c[i] = 0;
	ll now = 0;
	for(int i = 1;i <= k;++ i){
		now += query(a[i]);
		add(a[i],1);add1(a[i],1);
	}
	ll res = 0;
	for(int i = k + 1;i <= n;++ i){
		res = tot - now;
		res %= mod;
		ans = (ans + res * fac % mod) % mod;
		ans = (ans + kk) % mod;
		add1(a[i - k],-1);add(a[i - k],-1);
		now -= query1(a[i - k]);
		now += query(a[i]);
		add(a[i],1);add1(a[i],1);
	}
	res = tot - now;
	res %= mod;
	ans = (ans + res * fac % mod) % mod;
	ans = (ans + kk) % mod;
	cout << ans * q % mod;
	return 0;
}
```

---

## 作者：KinNa_Sky (赞：1)

不会算期望，但是可以算所有方案的逆序对总数最后除以方案数。

方案数是 $n - k + 1$ 个区间每个区间有 $k!$ 种方案共 $(n - k + 1)\cdot k!$。  

一个长度为 $i$ 的排列的全排列所有逆序对数的递推式是 $f_i = if_{i - 1} + \frac{i(i - 1)}{2}(i - 1)!$。  
怎么得到的：  
考虑已知 $f_{i - 1}$，求 $f_i$ 时依次让 $1\sim i$ 作为第一位，第一位和后面的贡献分别为 $0\sim i - 1$，且每个数作第一位有 $(i - 1)!$ 种方案，后 $i - 1$ 位的逆序对数即为 $f_{i - 1}$，贡献了 $i$ 次。


算一个区间的所有方案的逆序对总数时当前区间内的逆序对单独考虑，剩下的逆序对不变重复贡献 $k!$ 次。  
维护区间逆序对由于只有从前面删数和从后面插入数所以直接树状数组维护当前区间有那些数即可。  
删数时会减去后面区间里小于它的数，加数会加上前面区间里大于它的数。

[Code](https://atcoder.jp/contests/abc380/submissions/59923816)

---

## 作者：Mirage_Insane (赞：1)

## 题意

给定长度为 $n$ 的排列和常数 $k$，每次随机选择一个长度为 $k$ 的子区间随机打乱，问最后该序列的逆序对的期望。

## 题解

首先有一个很重要的结论：将长度为 $k$ 的排列随机打乱后，逆序对的期望值为 $\frac{k \times (k - 1)}{4}$。感性理解一下：每次取出一对二元组 $(i, j)$，其构成逆序对的概率为 $\frac{1}{2}$，所以期望就是 ${n \choose 2} \times \frac{1}{2}$。

于是问题就变得很简单了。枚举当前区间的左端点 $l$，那么 $r = l + k - 1$，提前预处理出 $[1, l - 1]$ 和 $[r + 1, n]$ 对逆序对的贡献，剩下的就是该子区间对 $[r + 1, n]$ 的贡献没有计算。这个用滑块思想处理就可以了。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define SF scanf
#define PF printf
#define int long long
const int mod = 998244353;
int qkpow(int a, int b) {
    int ans = 1;
    while(b) {
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return ans;
}
int inv(int x) {
    return qkpow(x, mod - 2);
}
struct Tree {
    int lson, rson, sum;
}tree[200005 << 5];
int a[200005], root[200005], tot;
int new_node(int x) {
    tree[++tot] = tree[x];
    tree[tot].sum++;
    return tot;
}
int update(int i, int l, int r, int x) {
    i = new_node(i);
    if(l == r) return i;
    int mid = l + r >> 1;
    if(mid >= x) tree[i].lson = update(tree[i].lson, l, mid, x);
    else tree[i].rson = update(tree[i].rson, mid + 1, r, x);
    return i;
}
int query(int Le, int Ri, int l, int r, int ql, int qr) {
    if(ql > qr) return 0;
    if(ql <= l && r <= qr) return tree[Ri].sum - tree[Le].sum;
    int mid = l + r >> 1, ans = 0;
    if(mid >= ql) ans += query(tree[Le].lson, tree[Ri].lson, l, mid, ql, qr);
    if(mid + 1 <= qr) ans += query(tree[Le].rson, tree[Ri].rson, mid + 1, r, ql, qr);
    return ans;
}
struct BIT {
    int tree[200005];
    #define lowbit(i) (i & (-i))
    void clear() {memset(tree, 0, sizeof(tree));}
    void update(int x, int k) {
        for(int i = x; i <= 200000; i += lowbit(i)) tree[i] += k;
    }
    int query(int x) {
        if(x <= 0) return 0;
        int ans = 0;
        for(int i = x; i; i -= lowbit(i)) ans += tree[i];
        return ans;
    }
}bit;
int suf[200005];
signed main() {
    int n, k;
    SF("%lld%lld", &n, &k);
    int now = k * (k - 1) % mod * inv(4) % mod;
    for(int i = 1; i <= n; i++) SF("%lld", &a[i]), root[i] = update(root[i - 1], 1, n, a[i]);
    for(int i = n; i; i--) {
        suf[i] = (suf[i + 1] + bit.query(a[i] - 1)) % mod;
        bit.update(a[i], 1); 
    }
    if(k == 1) return PF("%lld", suf[1]), 0;
    bit.clear();
    int ans = 0, sum = 0;
    for(int i = n - k + 1; i; i--) {
        ans = (ans + sum) % mod;
        ans = (ans + now) % mod;
        ans = (ans + suf[1] - suf[i]) % mod;
        ans = (ans + suf[i + k]) % mod;
        if(k == 1) sum = 0;
        else {
            sum = (sum + mod - bit.query(a[i + k - 1] - 1)) % mod;
            sum = (sum + query(root[i - 1], root[i + k - 2], 1, n, a[i + k - 1] + 1, n)) % mod;  //删除一个数带来的影响
            bit.update(a[i + k - 1], 1);
            sum = (sum + bit.query(a[i - 1] - 1)) % mod; //加入一个数多的贡献
        }
    }
    PF("%lld", ans * inv(n - k + 1) % mod);
    return 0;
}
```

---

## 作者：MightZero (赞：1)

### Solution

首先，对取出的长度为 $k$ 的序列任意重排，假设重排后得到的序列是 $p'_1,p'_2,\cdots,p'_k$；则对于一个位置 $i$，满足 $j>i$ 且 $p'_j<p'_i$ 的位置 $j$ 的期望数量必定是 $\frac{k}{2}$，因此 $p'$ 内部的逆序对数量的期望值即为 $\frac{k(k-1)}{4}$。

由于期望具有线性性，实际上只需要对于每个 $i \in \{1,2,\cdots,n-k+1\}$，先选取 $p_i,p_{i+1},\cdots,p_{i+k-1}$ 作为 $p'$，统计整个序列的逆序对数量，再去除 $p_x\in p'\land p_y\in p'$ 的逆序对 $(x,y)$ 的数量；求出的即为去除 $p'$ 内部逆序对后的逆序对数量，记为 $P(i)$；那么重排 $p'$ 后整个序列的逆序对的期望值就是 $E(i)=P(i)+\frac{k(k-1)}{4}$。

最终答案即为 $E=\frac{\sum_{i=1}^{n-k+1}{E(i)}}{n-k+1}$。

考虑用滑动窗口的思想求出 $P(i)$：先统计出整个序列的逆序对数量记为当前的答案；维护两个指针 $l,r$，初始时 $l=r=1$；将 $r$ 右移一位时相当于将 $p_r$ 加入滑动窗口，把当前答案减去所选区间内值大于 $p_r$ 的元素的数量；将 $l$ 右移一位时相当于从滑动窗口中删去 $p_l$，把当前答案加上所选区间内值小于 $p_l$ 的元素的数量；权值树状数组维护滑动窗口即可。

### Code

```cpp
#include<bits/stdc++.h>
#define loop(x,l,r) for(ll (x) = (l);(x)<=(r);++(x))
#define rloop(x,l,r) for(ll (x) = (r);(x)>=(l);--(x))
#define elif else if
using namespace std;
using ll = long long;
inline ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x*=10;x+=ch-'0';ch=getchar();}
    return x*f;
}
inline void write(ll x)
{
    if(x<0){putchar('-');x=-x;}
    if(x%10==x){putchar(x+'0');return;}
    write(x/10);putchar(x%10+'0');
}
const ll N=2e5+5,mod=998244353;
ll n,k,p[N],ans,totp;
ll mpw(ll a,ll x)
{
    ll res=1,tmp=a;
    while(x)
    {
        if(x&1)res=tmp*res%mod;
        tmp=tmp*tmp%mod,x>>=1;
    }
    return res;
}
ll tr1[N],tr2[N];
inline void modify(ll p,ll x,ll* arr)
{
    if(p<1)return;
    while(p<=n)arr[p]+=x,p+=(p&-p);
}
inline ll query(ll p,ll *arr)
{
    ll res=0;
    while(p>=1)res+=arr[p],p-=(p&-p);
    return res;
}
signed main()
{
    n=read(),k=read();
    (ans+=k*(k-1)%mod*mpw(4,mod-2))%=mod;
    loop(i,1,n)p[i]=read();
    ll nl=1,nr=1,totc=0;
    rloop(i,1,n)
    {
        totc+=query(p[i],tr1);
        modify(p[i],1,tr1);
    }
    while(nr<=k)
    {
        totc-=query(n,tr2)-query(p[nr],tr2);
        modify(p[nr],1,tr2);
        nr++;
    }
    (totp+=totc)%=mod;
    while(nl<n-k+1)
    {
        totc-=query(n,tr2)-query(p[nr],tr2);
        modify(p[nr],1,tr2);
        nr++;
        modify(p[nl],-1,tr2);
        totc+=(query(p[nl],tr2));
        nl++;
        (totp+=totc)%=mod;
    }
    (ans+=totp*mpw((n-k+1),mod-2))%=mod;
    write(ans);
    return 0;
}
```

---

## 作者：AmaoFox (赞：0)

有一个长为 $N$ 的排列，和一个长度 $K$。进行下列操作**恰好**一次，求期望逆序对个数：

- 取出一个长度为 $K$ 的区间，对其进行打乱（一共有 $K!$ 种方法），然后再放回到原来的位置。

---

排列里面的每一个元素都是不同的，所以任何一个长度为 $K$ 的序列里面正好也会有 $K$ 个不同的数。

看起来很废话，但是这告诉我们长度为 $K$ 的这样一个区间任意打乱以后，期望逆序对个数都是一样的，并且应该是好算的。

如果在赛前有积累，或者想一想、打个表，便可以发现这么一个事情：假设我们已经排好了该排列的前 $x$ 个数，打算放进去第 $x+1$ 个，那么第 $x+1$ 个数前面期望比该数要大的正好是 $\frac x2$ 个，因为数的大小关系都是独立的。

也就是说，每一个数对是逆序对的概率都是独立为 $\frac 12$ 的。这里一共有 $\frac{K(K-1)}2$ 个数对，所以打乱重排以后期望有 $\frac{K(K-1)}4$ 个逆序对。

由于取出来以后放回原地，所以区间内的元素和区间外的元素构成的逆序对不会变动。区间外之间自己构成的元素也不会变动。所以，我们只需要把区间内原本有的逆序对替换成期望逆序对个数即可。

动态维护该区间内逆序对个数，用权值树状数组/线段树是很方便的。

``` cpp
#include <bits/stdc++.h>
#define int long long

using namespace std;

const int N = 200005, mod = 998244353;

int qmi(int x, int y) {
  int ans = 1;
  while(y) {
    if(y & 1) {
      (ans *= x) %= mod;
    }
    (x *= x) %= mod;
    y >>= 1;
  }
  return ans;
}

int p[N];
int tr[4 * N];

void modify(int id, int l, int r, int p, int v) {
  if(l == r) {
    tr[id] = v;
    return;
  }
  int mid = (l + r) / 2;
  if(p <= mid) {
    modify(id * 2, l, mid, p, v);
  } else {
    modify(id * 2 + 1, mid + 1, r, p, v);
  }
  (tr[id] = tr[id * 2] + tr[id * 2 + 1]) % mod;
}

int query(int id, int l, int r, int ql, int qr) {
  if(ql <= l && r <= qr) {
    return tr[id];
  }
  if(qr < l || r < ql) {
    return 0;
  }
  int mid = (l + r) / 2;
  return (query(id * 2, l, mid, ql, qr) + query(id * 2 + 1, mid + 1, r, ql, qr)) % mod;
}

signed main() {
  ios::sync_with_stdio(0);
  cin.tie(0), cout.tie(0);
  int n, k;
  cin >> n >> k;
  for(int i = 1; i <= n; i++) {
    cin >> p[i];
  }
  int ans = 0;
  int sum = 0;
  for(int i = 1; i <= k; i++) {
    (ans += query(1, 1, n, p[i] + 1, n)) %= mod;
    modify(1, 1, n, p[i], 1);
  }
  (sum += ans) %= mod; // 所有长度为 K 的区间内的逆序对个数
  for(int i = 2; i <= n - k + 1; i++) {
    (ans += mod - query(1, 1, n, 1, p[i - 1] - 1)) %= mod;
    modify(1, 1, n, p[i - 1], 0);
    (ans += query(1, 1, n, p[i + k - 1] + 1, n)) %= mod;
    modify(1, 1, n, p[i + k - 1], 1);
    (sum += ans) %= mod;
  }
  for(int i = 1; i <= n; i++) {
    modify(1, 1, n, i, 0);
  }
  int sum2 = 0; // 在不修改时原排列的逆序对个数
  for(int i = 1; i <= n; i++) {
    (sum2 += query(1, 1, n, p[i] + 1, n)) %= mod;
    modify(1, 1, n, p[i], 1);
  }
  // 将 sum 除以 k 得到重排的区间的期望原逆序对个数，将其从 sum2 中减去，再加上重排后期望逆序对个数
  cout << ((sum2 - sum * qmi(n - k + 1, mod - 2) % mod + k * (k - 1) % mod * qmi(4, mod - 2)) % mod + mod) % mod << '\n';
  return 0;
}
```

此致，纪念我第一场 AK 的 ABC。~~这场题真简单吧其实。~~$\color{#fff}{\scriptsize\texttt{那么，是哪个大聪明蛋写下了 k * (k - 1) * qmi(4, mod - 2) \% mod 导致 WA 了六发呢。}}$

---

## 作者：cosf (赞：0)

首先我们注意到，将区间 $a_{l \dots (l + k - 1)}$ 重排后，区间内与区间外组成的逆序对个数不变，区间内的逆序对个数期望为 $\frac{\binom{k}{2}}{2} = \frac{k(k - 1)}{4}$。

因此，若令 $I(l, r)$ 表示原序列的 $a_{l, \dots, r}$ 子串的逆序对个数，考虑每个区间的逆序对变化，答案就是：

$$
I(1, n) + \frac{k(k - 1)}{4} - \frac{1}{n - k + 1} \times \sum_{i=1}^{n - k + 1}I(i, i + k - 1)
$$

求和前的系数表示等概率选取每一个区间。

至于怎么算，可以维护一个树状数组（简称 FwT），先花 $O(n \log n)$ 的时间算出 $I(1, n)$。然后观察到 $I(i, i + k - 1)$ 可以递推，每次往 FwT 里加上一个 $a_{i + k - 1}$，删掉 $a_{i - 1}$，并删除相应贡献即可。

[AC 记录](https://atcoder.jp/contests/abc380/submissions/59925407)

---

## 作者：wangshulin (赞：0)

# 前言
省流：剩下十分钟开 G 发现会做结果没时间了。
# 思路
由于是排列，所以数组中不存在重复的数。

对于一个长度为 $k$ 的没有重复的数的序列，我们发现每对数都有 $\frac{1}{2}$ 的概率产生逆序对，所以期望逆序对个数为 $\frac{k(k-1)}{4}$。

所以我们枚举每一个长度为 $k$ 的子区间，递推求出每个子区间内的逆序对个数 $c$，设用总的逆序对个数为 $s$，则 $s-c+\frac{k(k-1)}{4}$ 就是当打乱这个区间时总的期望逆序对个数，由于每个区间等概率选择，所以还要除以 $n-k+1$，即枚举到这个区间时 $ans \gets ans+\frac{s-c+\frac{k(k-1)}{4}}{n-k+1}$。

$c$ 的求解见代码。
# 代码
[code](https://atcoder.jp/contests/abc380/submissions/59927963)

---

## 作者：Binah_cyc (赞：0)

~~赛时没场切，不敢评价了。~~

考虑随机打乱一个长度为 $n$ 的排列，它的期望逆序对数为 ${C_n^2 \over 2}$。

- 证明

  我们在这个排列里任取两个数，方案为 $C_n^2$。对于这两个数，较大数排在较小数前面的概率为 ${1 \over 2}$。故答案为 ${C_n^2 \over 2}$。

考虑全局逆序对个数，发现它由两个部分组成：逆序对两端都在选定范围内，存在一端不在选定范围内。

第一种能够 $O(1)$ 的求出，只需要考虑第二种即可。

使用容斥的知识，易得知道第二种实际上就是全局逆序对个数减去选定范围内的逆序对个数。

现在只需要动态求出所有长度为 $k$ 的区间逆序对个数即可，使用滑动窗口，每一次将区间最左边的元素删除，并消除影响，然后加入区间右边的元素，统计答案即可。

代码
```c
// Problem: G - Another Shuffle Window
// Contest: AtCoder - AtCoder Beginner Contest 380
// URL: https://atcoder.jp/contests/abc380/tasks/abc380_g
// Memory Limit: 1024 MB
// Time Limit: 2000 ms
// Author: Binah_cyc

#include<bits/stdc++.h>
using namespace std;
constexpr int N=2e5+5,mod=998244353;
#define int long long
int n,k,a[N],cnt,cnt_k,ans;

int sum[N<<2];
void change(int x,int val)
{
	int tl=0,tr=n+1,p=1;
	while(1)
	{
		sum[p]+=val;
		if(tl==tr) return ;
		int mid=(tl+tr)>>1;
		if(x<=mid) tr=mid,p<<=1;
		else tl=mid+1,p=p<<1|1;
	}
}
int ask(int l,int r,int p=1,int tl=0,int tr=n+1)
{
	if(l<=tl&&tr<=r) return sum[p];
	int mid=(tl+tr)>>1,cnt=0;
	if(l<=mid) cnt+=ask(l,r,p<<1,tl,mid);
	if(r>mid)  cnt+=ask(l,r,p<<1|1,mid+1,tr);
	return cnt;
}

int power(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%mod;
		a=a*a%mod,b>>=1;
	}
	return ans;
}

int moder(int x){return (x>=mod?x-mod:x);}

signed main(signed argc,char** argv)
{
	ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	int exp=(__int128)k*(k-1)*power(4,mod-2)%mod,tot=power(n-k+1,mod-2);
	for(int i=1;i<=n;i++) cnt=moder(cnt+ask(a[i],n)),change(a[i],1);
	memset(sum,0,sizeof(sum));
	for(int i=1;i<k;i++) cnt_k=moder(cnt_k+ask(a[i]+1,n+1)),change(a[i],1);
	for(int i=k;i<=n;i++)
	{
		if(a[i-k]) cnt_k=moder(cnt_k-ask(0,a[i-k]-1)+mod),change(a[i-k],-1);
		cnt_k=moder(cnt_k+ask(a[i]+1,n+1)),change(a[i],1);
		ans=moder(ans+(cnt-cnt_k+exp+mod)*tot%mod);
	}
	cout<<ans;
	return 0;
}
```

---

