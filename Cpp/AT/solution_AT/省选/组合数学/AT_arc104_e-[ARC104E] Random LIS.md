# [ARC104E] Random LIS

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc104/tasks/arc104_e

長さ $ N $ の整数列 $ A_1,\ A_2,\ \cdots,\ A_N $ が与えられます。

同じく長さ $ N $ の整数列 $ X $ は、 各 $ i\ (1\ \leq\ i\ \leq\ N) $ について独立に、 $ 1\ \leq\ X_i\ \leq\ A_i $ を満たす整数の一様分布からランダムに選ばれます。

このとき、$ X $ の最長増加部分列の長さの期待値を mod $ 1000000007 $ で計算してください。

より正確には、期待値が有理数、つまりある既約分数 $ \frac{P}{Q} $ で表せること、更に $ R\ \times\ Q\ \equiv\ P\ \pmod\ {1000000007} $, $ 0\ \leq\ R\ <\ 1000000007 $ を満たす整数 $ R $ が一意に定まることがこの問題の制約より証明できますので、この $ R $ を出力してください。

## 说明/提示

### 注釈

列 $ X $ の部分列とは $ X $ の要素をいくつか抜き出して元の順に並べてできる列のことを指し、また、列 $ X $ の最長増加部分列とは、$ X $ の狭義単調増加な部分列の中で列の長さが最大のものを指します。

### 制約

- $ 1\ \leq\ N\ \leq\ 6 $
- $ 1\ \leq\ A_i\ \leq\ 10^9 $
- 入力は全て整数である

### Sample Explanation 1

$ X $ はそれぞれ確率 $ 1/6 $ で次のいずれかになります。 - $ X\ =\ (1,1,1) $ のとき、最長増加部分列の長さは $ 1 $ です。 - $ X\ =\ (1,1,2) $ のとき、最長増加部分列の長さは $ 2 $ です。 - $ X\ =\ (1,1,3) $ のとき、最長増加部分列の長さは $ 2 $ です。 - $ X\ =\ (1,2,1) $ のとき、最長増加部分列の長さは $ 2 $ です。 - $ X\ =\ (1,2,2) $ のとき、最長増加部分列の長さは $ 2 $ です。 - $ X\ =\ (1,2,3) $ のとき、最長増加部分列の長さは $ 3 $ です。 よって、最長増加部分列の長さの期待値は $ (1\ +\ 2\ +\ 2\ +\ 2\ +\ 2\ +\ 3)\ /\ 6\ \equiv\ 2\ \pmod\ {1000000007} $ です。

### Sample Explanation 2

$ X $ はそれぞれ確率 $ 1/4 $ で次のいずれかになります。 - $ X\ =\ (1,1,1) $ のとき、最長増加部分列の長さは $ 1 $ です。 - $ X\ =\ (1,1,2) $ のとき、最長増加部分列の長さは $ 2 $ です。 - $ X\ =\ (2,1,1) $ のとき、最長増加部分列の長さは $ 1 $ です。 - $ X\ =\ (2,1,2) $ のとき、最長増加部分列の長さは $ 2 $ です。 よって、最長増加部分列の長さの期待値は $ (1\ +\ 2\ +\ 1\ +\ 2)\ /\ 4\ =\ 3\ /\ 2 $ ですが、$ 2\ \times\ 500000005\ \equiv\ 3\ \pmod\ {1000000007} $ であるので、$ 500000005 $ を出力してください。

## 样例 #1

### 输入

```
3
1 2 3```

### 输出

```
2```

## 样例 #2

### 输入

```
3
2 1 2```

### 输出

```
500000005```

## 样例 #3

### 输入

```
6
8 6 5 10 9 14```

### 输出

```
959563502```

# 题解

## 作者：EuphoricStar (赞：6)

首先期望转化成 $\text{LIS}$ 总和除以方案总数（即 $a_i$ 乘积）不必多说了。观察可发现题目 $n$ 特别小，考虑 $O(n^n)$ 枚举 $x_i$ 的相对大小关系（排名），固定排名后算出 $\text{LIS}$，再计算这种排名对应的方案数。

于是现在问题变成了有 $m$ 个数，每个数的上界为 $b_i$，要求序列单调递增的方案数。考虑直接套 [CF1295F Good Contest](https://codeforces.com/problemset/problem/1295/F) 的做法，$b_i$ 离散化后设 $f_{i,j}$ 为第 $i$ 个数位于值域第 $j$ 段的方案数。转移枚举以 $i$ 为右端点的极长值域位于同一段的区间左端点 $k$，以及 $k-1$ 位于哪个段。系数是在 $[1,len_j]$ 中选 $i-k+1$ 个互不相同的数的方案数（为 $\binom{len_j}{i-k+1}$）。可得：

$$f_{i,j} \gets \sum\limits_{k=1}^{i-1} \sum\limits_{x=1}^{j-1} \binom{len_j}{i-k+1} f_{k-1,x}$$

暴力计算即可。

总时间复杂度大概是 $O(n^{n+5})$（没仔细算，实际远远达不到）。

[code](https://atcoder.jp/contests/arc104/submissions/40678861)

---

## 作者：ax_by_c (赞：5)

首先期望转计数，最后除以总情况数即可。

发现范围极小，考虑先爆搜数的相对大小。对于相同的数，取值范围为并。

我们需要统计符合要求的情况总数，考虑从小到大，相当于给出 $B_1,\dots,B_m$，求满足 $b_i\le B_i$ 且 $b_i\operatorname{<} b_{i+1}$ 的数列总数。

值域很大，考虑分为 $m$ 段，然后 DP，设 $f_{i,j}$ 表示前 $i$ 个数，最后一个数在第 $j$ 段的方案数。每次枚举当前段和当前段的数的个数即可转移，系数为组合数，暴力计算即可。

时间复杂度 $O(n^{2n-1})$ 且跑不满，可以通过。

```cpp
#include<bits/stdc++.h>
using namespace std;
namespace ax_by_c{
typedef long long ll;
const ll mod=1e9+7;
ll ksm(ll a,ll b,ll p){
	a=a%p;
	ll r=1;
	while(b){
		if(b&1){
			r=r*a%p;
		}
		a=a*a%p;
		b>>=1;
	}
	return r%p;
}
const int N=8;
int n,a[N];
ll ans;
int rk[N];
bitset<N>mk;
int b[N],m;
int l[N],r[N],idx;
ll f[N][N];
ll C(ll n,ll m){
	if(n<m)return 0;
	ll res=1;
	for(ll i=n;i>=n-m+1;i--){
		res=res*i%mod;
	}
	for(ll i=m;i>=1;i--){
		res=res*ksm(i,mod-2,mod)%mod;
	}
	return res;
}
int dp[N];
void cal(){
	mk=0;
	for(int i=1;i<=n;i++){
		mk[rk[i]]=1;
	}
	int val=1;
	while(mk[val])val++;
	for(int i=1;i<=n;i++){
		if(rk[i]>val)return ;
	}
	m=val-1;
	for(int i=1;i<=m;i++){
		b[i]=0;
	}
	for(int i=1;i<=n;i++){
		if(!b[rk[i]]){
			b[rk[i]]=a[i];
		}
		else{
			b[rk[i]]=min(b[rk[i]],a[i]);
		}
	}
	set<int>eds;
	for(int i=1;i<=m;i++){
		eds.insert(b[i]);
	}
	int lst=0;
	idx=0;
	for(auto it:eds){
		l[++idx]=lst+1;
		r[idx]=it;
		lst=it;
	}
	memset(f,0,sizeof f);
	f[0][0]=1;
	for(int R=1;R<=m;R++){
		for(int i=1;i<=idx;i++){
			for(int j=0;j<i;j++){
				for(int L=R;L>=1;L--){
					if(b[L]<r[i]){
						break;
					}
					f[R][i]=(f[R][i]+C(r[i]-l[i]+1,R-L+1)*f[L-1][j]%mod)%mod;
				}
			}
		}
	}
	ll sum=0;
	for(int i=0;i<=idx;i++){
		sum=(sum+f[m][i])%mod;
	}
	int mx=0;
	for(int i=1;i<=n;i++){
		dp[i]=0;
		for(int j=0;j<i;j++){
			if(rk[j]<rk[i]){
				dp[i]=max(dp[i],dp[j]+1);
			}
		}
		mx=max(mx,dp[i]);
	}
	ans=(ans+sum*mx)%mod;
}
void dfs(int u){
	if(u==n+1){
		cal();
		return ;
	}
	for(int i=1;i<=n;i++){
		rk[u]=i;
		dfs(u+1);
	}
}
void main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	dfs(1);
	for(int i=1;i<=n;i++){
		ans=ans*ksm(a[i],mod-2,mod)%mod;
	}
	printf("%lld\n",ans);
}
}
int main(){
	ax_by_c::main();
	return 0;
}
```

---

## 作者：lsj2009 (赞：4)

### Solution

说实话感觉这个题质量不是很高，不如与它相似的 P3643 和 CF1295F。

看到 $n\le 6$，这几乎所有和值域无关的做法都能跑过去，所以给了我们充足的乱搞空间。

首先考虑暴力钦定每个数的相对大小 $\{rk_n\}$，需要 $\Theta(n^n)$ 的时间（因为可能有数相等，所以不是 $\Theta(n!)$）。

然后丢与每个下标，我们取排名等于他的最小值。即 $a_i=\min\limits_{rk_j=i} A_j$，然后 $m=\max\limits_{i=1}^n rk_i$。

那么我们就把问题转换成了：

> 求有多少个序列 $\{b_m\}$ 满足：
> 1. $b_i\in[1,a_i]$。
> 2. $\forall i\in[1,m-1]$ 满足 $b_i<b_{i+1}$。

然后这个东西就和 CF1295F 基本上一样啊，只不过前者要求严格单调，后者要求非严格单调。简单来说就是，先把 $a_i$ 离散化出来，变成若干个值域段，设 $f_{i,j}$ 为对于前 $i$ 个数而言，第 $i$ 个 数在第 $j$ 段的方案总数。

那么我们考虑去枚举一个 $k$，让前 $k-1$ 个数在第 $1\sim j-1$ 段；第 $k\sim i$ 个数在第 $j$ 段。而前 $k-1$ 个数在第 $1\sim j-1$ 段的方案总数即为 $\sum\limits_{x=1}^{j-1} f_{k-1,x}$；第 $k\sim i$ 个数在第 $j$ 段的方案总数为 $len_j \choose i-k+1$。当然还需要判断的是第 $k\sim i$ 个是否都可以取到第 $j$ 段。

对于这个组合数的计算，虽然 $len_j$ 很大，但是 $i-k+1$ 确很小，所以每次可以直接 $\Theta(n)$ 去暴力算。

所以得到方程：

$$f_{i,j}=\sum\limits_{k=1}^i {len_j \choose i-k+1}\sum\limits_{x=1}^{j-1} f_{k-1,x}$$

最终答案即为 $\sum\limits_{i=1}^{a_m} f_{m,i}$，由于本题数据范围非常小，所以也不需要 P3643 的前缀和优化，直接 $\Theta(n^5)$ 暴力 dp 即可，最终复杂度是 $\Theta(n^{n+5})$。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
#define ll long long
#define ull unsigned long long
#define ld long double
#define PII pair<int,int>
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define chkmax(a,b) a=max(a,b)
#define chkmin(a,b) a=min(a,b)
#define rep(k,l,r) for(int k=l;k<=r;++k)
#define per(k,r,l) for(int k=r;k>=l;--k)
#define cl(f,x) memset(f,x,sizeof(f))
using namespace std;
const int N=10,MOD=1e9+7;
int qpow(int a,int b) {
	int res=1,base=a;
	while(b) {
		if(b&1)
			res=res*base%MOD;
		base=base*base%MOD; b>>=1;
	}
	return res;
}
int t[N],len;
int get_id(int x) {
	return lower_bound(t+1,t+len+1,x)-t;
}
void add(int &a,int b) {
	a+=b;
	if(a>=MOD)
		a-=MOD;
}
int C(int n,int m) {
	if(n>m)
		return 0;
	if(n>m-n)
		n=m-n;
	int res=1;
	rep(i,1,n)
		res=res*(m-i+1)%MOD*qpow(i,MOD-2)%MOD;
	return res;
}
int b[N],s[N],g[N],a[N],f[N][N],ans,n;
int solve() {
    cl(a,0x3f);
	int m=0;
    rep(i,1,n) {
        chkmin(a[s[i]],b[i]);
        chkmax(m,s[i]);
    }
	t[++len]=0;
	rep(i,1,m) 
		t[++len]=a[i];
	sort(t+1,t+len+1);
	len=unique(t+1,t+len+1)-t-1;
	rep(i,1,m)
		a[i]=get_id(a[i]);
    cl(f,0);
	f[0][1]=1;
	rep(i,1,m) {
		rep(j,2,a[i]) {
			int res=INFLL;
			per(k,i,1) {
				chkmin(res,a[k]);
				if(j>res)
					break;
				rep(x,1,j-1)
					add(f[i][j],C(i-k+1,t[j]-t[j-1])*f[k-1][x]%MOD);
			}
		}
	}
	int ans=0;
	rep(i,2,len)
		add(ans,f[m][i]);
	return ans;
}
int c[N];
bool check() {
	rep(i,1,n)
		c[i]=s[i];
	sort(c+1,c+n+1);
	rep(i,1,n) {
		if(c[i]-c[i-1]>1)
			return false;
	}
	return true;
}
void dfs(int x) {
    if(x==n+1) {
        if(!check())
			return;
        int res=0;
		cl(g,0);
        rep(i,1,n) {
            rep(j,0,i-1) {
                if(s[i]>s[j])
                    chkmax(g[i],g[j]+1);
            }
            chkmax(res,g[i]);
        }
        add(ans,res*solve()%MOD);
        return;
    }
    rep(i,1,n) {
        s[x]=i; dfs(x+1);
    }
}
signed main() {
    scanf("%lld",&n);
    rep(i,1,n)
        scanf("%lld",&b[i]);
    dfs(1);
    rep(i,1,n)
        ans=ans*qpow(b[i],MOD-2)%MOD;
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：Argon_Cube (赞：3)

题目初看起来无从下手，我们需要找到一个可以枚举的量。注意到我们不需要知道每个数，我们只需要知道它们的相对大小关系。于是我们可以枚举将所有数排序后每个数的排名（一共 $n!$ 中，相同的我们认为前面那个大）。

算出每种排名的 LIS，接下来就是求出这种排名出现的概率。那么我们实际上就得到了一个形如 $a_{p_1}\dbinom<\leq\ a_{p_2}\dbinom<\leq\ \cdots\dbinom<\leq\ a_{p_n}$（其中 $\dbinom<\leq$ 代表这个位置可以为 $<$ 或 $\leq$ 中的一个）的不等式以及每个数的取值范围，现在要求这个不等式的解数。

首先作一步处理：将不等式中变量取值范围的上界变为其后缀 $\min$，因为如果一个数大于后面的数肯定是不合法的，同时也方便我们之后的处理。

考虑容斥，对大小关系容斥不可行，枚举第一个值超过最大可填的值的位置。设 $f_n$ 为只考虑长度为 $n$ 的前缀的合法方案个数，得到

$$f_n=\binom{a_n+c_{\leq,[1,n)}}{n}-\sum_{i=0}^{n-1}f_{i}\binom{a_n-a_{i+1}+c_{\leq,[i+1,n)}}{n-i}$$

其中 $a_n$ 是**第 $n$ 小的数的取值上界**，$c_{\leq,[l,r)}$ 代表第 $l$ 个到第 $r-1$ 个比较符号中有几个小于等于。

于是我们就得到了合法方案数，将其乘以 LIS 长度并求和，最后除以 $\prod a_i$ 即可。

复杂度 $\Theta(n^3n!)$（$n!$ 种排列，每种排列的递推要求 $n$ 个值，每个值要求 $n+1$ 个组合数，计算组合数是 $\mathrm O(n)$ 的），是目前的最优解。

---

## 作者：fjy666 (赞：3)

比 [这份题解](https://www.luogu.com.cn/blog/615348/ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-ha-h) 更加娱乐性质的 sol。

首先把数组离散化，把值域打散成 $n$ 份，枚举 $a_i$ 在哪一份里（这一部分 $n!$）。

然后我们考虑，对于在用一个值域块里的 $a_i$ 要确定顺序，自然想到状态压缩。  

考虑状压每个数的名次成一个 $n$ 进制的数，这里又是有 $6^6$ 种名次。  
但是我们发现，并不是每个 $n$ 进制的数都是合法的，因此我们只需要打一个表，保留合法的即可。

[submission(32417 Byte)](https://atcoder.jp/contests/arc104/submissions/43285817) 

---

## 作者：OrezTsim (赞：1)

看到巨大的 $a_i$ 和巨小的 $n$，考虑离散化。

由于 LIS 只跟偏序关系有关，考虑枚举偏序关系，复杂度 $\mathcal O(n^n)$。

在确定了偏序关系之后我们就可以直接暴力求 LIS 了。

那么如何计算答案呢？

根据给定的范围，我们很容易得到每一个值的取值范围。

由于序列离散化、去重后单调递增，我们发现每次的增加值 $>0$。

那么只要枚举增加值就行。

如果相邻的两个值在同一个值域内，用组合数爆算即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int N = 7, Mod = 1e9 + 7;
int n, all = 1, res, a[N], p[N], lim[N], tmp[N];

inline int qpow(int bas, int pw, int mul = 1) {
    for (; pw; pw >>= 1, (bas *= bas) %= Mod)
        if (pw & 1) (mul *= bas) %= Mod; return mul;
}

inline int C(int u, int v) {
    if (v == 0) return 1; if (v == 1) return u;
    if (v == 2) return u * (u - 1) % Mod * 500000004ll % Mod;
    if (v == 3) return u * (u - 1) % Mod * (u - 2) % Mod * 166666668ll % Mod;
    if (v == 4) return u * (u - 1) % Mod * (u - 2) % Mod * (u - 3) % Mod * 41666667ll % Mod;
    if (v == 5) return u * (u - 1) % Mod * (u - 2) % Mod * (u - 3) % Mod * (u - 4) % Mod * 808333339ll % Mod;
    if (v == 6) return u * (u - 1) % Mod * (u - 2) % Mod * (u - 3) % Mod * (u - 4) % Mod * (u - 5) % Mod * 301388891ll % Mod;
}

inline int _dfs(int len, int Max) {
    if (len == Max + 1) {
        int cur = 1; vector <int> ct; ct.resize(Max + 1);
        for (int i = 1; i <= Max; ++i) ++ct[tmp[i]];
        for (int i = 1; i <= Max; ++i) (cur *= C(lim[i], ct[i])) %= Mod;
        return tmp[0] = 0, cur;
    }
    int ret = 0;
    for (tmp[len] = tmp[len - 1]; tmp[len] <= len; ++tmp[len])
        (ret += _dfs(len + 1, Max)) %= Mod; return ret;
}

inline void dfs(int len) {
    if (len == n + 1) {
        for (int i = 1; i <= n; ++i) tmp[i] = p[i];
        sort(tmp + 1, tmp + 1 + n); bool f = true;
        for (int i = 1; i <= n; ++i) f &= (tmp[i] - tmp[i - 1] <= 1);
        if (!f) return ; vector <int> dp; dp.resize(n + 1);
        for (int i = 1; i <= n; ++i) dp[i] = 1;
        for (int i = 1; i <= n; ++i) for (int j = 1; j < i; ++j)
            if (p[j] < p[i]) dp[i] = max(dp[i], dp[j] + 1);
        int ls = 0; for (int i = 1; i <= n; ++i) ls = max(ls, dp[i]);
        int Max = tmp[n]; for (int i = 1; i <= Max; ++i) lim[i] = 1e18;
        for (int i = 1; i <= n; ++i) lim[p[i]] = min(lim[p[i]], a[i]);
        for (int i = Max - 1; i; --i) lim[i] = min(lim[i], lim[i + 1]), lim[i + 1] -= lim[i];
        tmp[0] = 1; return (res += _dfs(1, Max) * ls % Mod) %= Mod, void();
    }
    for (int i = 1; i <= n; ++i) p[len] = i, dfs(len + 1); return ;
}

signed main() {
    cin >> n; for (int i = 1; i <= n; ++i)
        cin >> a[i], (all *= a[i]) %= Mod;
    all = qpow(all, Mod - 2); dfs(1);
    return cout << res * all % Mod << endl, 0;
}
```

---

## 作者：shinkuu (赞：0)

好题，随机讲讲。

首先期望转 LIS 长度和除以方案数。LIS 这个东西不好刻画，但是发现 $n=6$ ，所以考虑直接枚举每个数排名，也就是枚举 $X_i$ 离散化后的序列。

然后考虑知道这个序列之后怎么求方案数。先想一个弱化版的问题：有 $m$ 个数，已知他们的排名，每个数的取值范围为 $[1,k]$，$k$ 为定值。求方案数。答案显然是 $\binom{k}{m}$。

回到原问题，尝试转化成弱化版问题。注意到值域非常大（$V=10^9$）但是 $n=6$ 非常小。这启示我们，要不只有小部分值是有用的，要不可以把一段值放在一起算。这题显然是后者。

考虑把序列 $A$ 排序后去重得到序列 $B$，于是发现对于 $(B_{j-1},B_j]$ 这个区间，能取到区间内任意一个数的 $X_i$ 的集合相同。也就是说，我们如果知道了对于每个 $(B_{i-1},B_i]$，哪些 $X_i$ 在这个区间中，就可以用弱化版的方法算出每个 $i$ 的方案数，最后再乘起来即可。

这里再次暴力枚举每个排名所对应的数属于哪个 $(B_{i-1},B_i]$ 的区间即可。时间复杂度远小于 $O(n^{2n})$，轻松跑过。

code：

```cpp
int n,m,a[N],b[N],c[N],d[N],lim[N],dp[N];
bool vis[N];
int ans,mx,ifac[N];
il int Mod(int x,int y){
	return x+y>=mod?x+y-mod:x+y;
}
il int qpow(int x,int y){
	int ret=1;
	while(y){
		if(y&1){
			ret=1ll*ret*x%mod;
		}
		x=1ll*x*x%mod,y>>=1;
	}
	return ret;
}
il int binom(int x,int y){
	if(x<y){
		return 0;
	}
	int s=1;
	drep(i,x,x-y+1){
		s=1ll*s*i%mod;
	}
	return 1ll*s*ifac[y]%mod;
}
int dfs2(int u,int p,int cnt){
	if(u==mx+1){
		return binom(d[p],cnt);
	}
	int ret=0;
	if(lim[u]>=b[p]){
		ret=Mod(ret,dfs2(u+1,p,cnt+1));
	}
	rep(i,p+1,m){
		if(lim[u]>=b[i]){
			ret=Mod(ret,1ll*dfs2(u+1,i,1)*binom(d[p],cnt)%mod);
		}
	}
	return ret;
}
il void solve(){
	int res=1;mx=0;
	mems(lim,0x3f);
	rep(i,1,n){
		mx=max(mx,c[i]);
		lim[c[i]]=min(lim[c[i]],a[i]);
		dp[i]=1;
		rep(j,1,i-1){
			if(c[j]<c[i]){
				dp[i]=max(dp[i],dp[j]+1);
			}
		}
		res=max(res,dp[i]);
	}
	ans=Mod(ans,1ll*dfs2(1,1,0)*res%mod);
}
void dfs1(int u,int p,int lst){
	if(u==n+1){
		solve();
		return;
	}
	rep(i,lst+1,n){
		if(vis[i]){
			continue;
		}
		c[i]=p,vis[i]=1;
		dfs1(u+1,p,i);
		if(u<n){
			dfs1(u+1,p+1,0);
		}
		vis[i]=0;
	}
}
void Yorushika(){
	read(n);
	int fac=1,s=1;
	rep(i,1,n){
		read(a[i]),b[i]=a[i];
		fac*=i;
		ifac[i]=qpow(fac,mod-2);
		s=1ll*s*a[i]%mod;
	}
	sort(b+1,b+n+1);
	m=unique(b+1,b+n+1)-b-1;
	rep(i,1,m){
		d[i]=b[i]-b[i-1];
	}
	dfs1(1,1,0);
	printf("%lld\n",1ll*ans*qpow(s,mod-2)%mod);
}
signed main(){
	int t=1;
	//read(t);
	while(t--){
		Yorushika();
	}
}
```

---

## 作者：cqbzlzm (赞：0)

### Description

给出一个长度为 $N$ 的序列 $A$，按照下列方式随机生成一个长度为 $N$ 的序列 $X$：

$X_i$ 为在 $[1,a_i]$ 中等概率随机一个数。求其最长**上升**子序列长度的期望，对 $10^9+7$ 取模。

### Solution

先把期望转换为长度之和除以序列数量。然后花费 $O(n^n)$ 把这 $n$ 个数的大小关系枚举出来。（只记录相对关系，如 $(1,1,2)$。$(1,1,3)$ 就是一个不合法的）。

然后要具体地确定每个相对的数对应了哪个实际的数，这里同 [Good Contest](https://www.luogu.com.cn/problem/CF1295F)，具体看[我的题解](https://www.luogu.com.cn/article/n8ed30kg)。

大概就是这样 dp，设 $dp_{i,j}$ 表示前 $i$ 个数，最后一个数在第 $j$ 组的合法方案数。通过枚举 $k$，表示 $a_{k+1,\cdots ,i}$ 全在第 $j$ 组，进行转移：
$$
dp_{i,j}=\sum^{i-1}_{k=1}{\sum^{p<j}{dp_{k,p}\times \binom{len}{i-k}}}
$$
 这个内层求和可以用前缀和优化，所以 dp 复杂度为 $O(n^3)$。总复杂度为 $O(n^{n+3})$。但是第一步枚举相对大小肯定跑不满，大概只有 4000 多个，所以跑得很快。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int mod = 1e9+ 7, MAXN = 6;
int qpow(int a, int b) {
	int ans = 1;
	while (b) {
		if (b & 1ll) ans = ans * a % mod;
		a = a * a % mod;
		b = b / 2ll;
	}
	return ans;
}
int n, s;
int l[MAXN + 5], r[MAXN + 5];
int re[MAXN * 2 + 5], rcnt;
int dp[MAXN + 5][MAXN * 2 + 5], C[MAXN * 2 + 5];
int mx[MAXN + 5];
int calc() {
    memset(dp, 0, sizeof(dp));
    dp[0][0] = 1; re[0] = 0;
    for (int i = 1; i < rcnt; i ++) dp[0][i] = 1;
    for (int i = 1; i <= s; i ++) {
        for (int j = l[i]; j < mx[i]; j ++) {
            int len = re[j + 1] - re[j];
            C[0] = 1;
            for (int j = 1; j <= i; j ++)
                C[j] = C[j - 1] * (len - j + 1) % mod * qpow(j, mod - 2) % mod;
            for (int k = i - 1; k >= 0; k --) {
                dp[i][j] = (dp[i][j] + dp[k][j - 1] * C[i - k] % mod) % mod;
                if (j < l[k] || j >= mx[k]) break;
            }
        }
        for (int j = 1; j < rcnt; j ++) dp[i][j] = (dp[i][j] + dp[i][j - 1]) % mod;
    }
    return dp[s][rcnt - 1];
}
int b[MAXN + 5], c[MAXN + 5];
int ans = 0;
void dfs(int i) {
    if (i == n + 1) {
        // for (int i= 1; i <= n; i ++) cout<<b[i]<<' ';
        // cout<<endl;
        memset(c, 0, sizeof(c));
        memset(mx, 0x3f3f3f3f, sizeof(mx));
        for (int i = 1; i <= n; i ++) c[b[i]] ++;
        for (int i = n; i >= 1; i --)
            if (c[i] != 0) {
                s = i;
                for (int j = 1; j < i; j ++) if (c[j] == 0) return ;
                break;
            }
        // for (int i= 1; i <= n; i ++) cout<<b[i]<<' ';
        // cout<<endl;
        for (int i = 1; i <= n; i ++)
            mx[b[i]] = min(mx[b[i]], r[i]);
        int f[MAXN + 5]; memset(f, 0, sizeof(f));
        int ll = 0;
        for (int i = 1; i <= n; i ++) {
            for (int j = 0; j < i; j ++)
                if (b[j] < b[i]) f[i] = max(f[i], f[j] + 1);
            ll = max(ll, f[i]);
        }
        // cout<<ll<<endl;
        // cout<<calc()<<endl;
        (ans += calc() * ll % mod) %= mod;
        return ;
    }
    for (int j = 1; j <= n; j ++) {
        b[i] = j;
        dfs(i + 1);
    }
    return ;
}
signed main() {
	scanf("%lld", &n);
	for (int i = 1; i <= n; i ++) {
        l[i] = 1;
		scanf("%lld", &r[i]);
		re[++ rcnt] = l[i];
		re[++ rcnt] = ++ r[i];
	}
	sort(re + 1, re + rcnt + 1);
	rcnt = unique(re + 1, re + rcnt + 1) - re - 1;
	for (int i = 1; i <= n; i ++) {
		l[i] = lower_bound(re + 1, re + rcnt + 1, l[i]) - re;
		r[i] = lower_bound(re + 1, re + rcnt + 1, r[i]) - re;
	}
    dfs(1);
    for (int i = 1; i <= n; i ++) {
        ans = ans * qpow(re[r[i]] - 1, mod - 2) % mod;
    }
    cout<<ans;
	return 0;
}
```

---

## 作者：User_Unauthorized (赞：0)

## 题意

给定一个长度为 $N$ 的序列 $A$，按照下列方式生成一个长度为 $N$ 的序列 $X$：  
$\forall i\in[1,n]$，$X_i$ 在 $[1,A_i]$ 中的整数中均匀随机生成。

求其最长**上升**子序列长度的期望，对 $10^9+7$ 取模。

$1 \le N \le 6, 1 \le A_i \le 10^9$。

## 题解

由于 $N$ 很小，故我们可以直接枚举 $X_i$ 的排名，然后计算其贡献。

发现并非所有的 $N^N$ 种情况都是合法的，例如当 $N = 3$ 时，排名序列 $\left\{1,1,3\right\}$ 就是不合法的，而排名序列 $\left\{1,1,2 \right \}$ 是合法的。所有可能的合法排名序列叫做有序贝尔数，其 OEIS 编号为 [A000670](https://oeis.org/A000670)。当 $N = 6$ 时，其值为 $4683$。

现在问题变为了，在钦定的排名序列下，求最长上升子序列的长度和取到该排名的序列的方案数。

前者是平凡的，由于 $N$ 很小，故可以肆意求。

现在考虑如何求方案数，首先我们可以将排名相同的数视为一类数，设我们有 $M$ 类书，那么对于每一类数我们可以求出其最大取值为多少，设其为 $H_i$，其中 $H_0 = 0$，那么我们可以得出随着排名递减 $H_i$ 应也为递减的，即 $\forall i \in \left[1, M \right ), H_i \le H_{i + 1}$，若存在 $i \in \left[1, M\right)$，使得$ H_i > H_{i + 1}$，那么更新 $H_i \leftarrow \min\left\{H_i, H_{i + 1} \right \}$ 即可。

可以发现数的取值范围是 $\mathcal{O}(M)$ 个区间，故我们可以按区间去考虑，设 $f_{i, j}$ 表示前 $i$ 个区间中有 $j$ 个数的方案数，通过枚举前 $i - 1$ 个区间中有多少个数即可实现转移，因为钦定了前 $i - 1$ 个区间中有多少个数，不妨设其为 $k$，那么区间 $\left(H_{i - 1}, H_{i} \right ]$ 中的数有 $j - k$ 种，其方案数为 $\dbinom{H_{i} - H_{i - 1}}{j - k}$，至此可以写出转移式

$$
f_{i, j} = \sum\limits_{k = i - 1}^{j} \dbinom{H_{i} - H_{i - 1}}{j - k} f_{i - 1, k}
$$

初始状态为 $f_{0, 0} = 1$，答案状态为 $f_{M, M}$，这部分的复杂度为 $\mathcal{O}(N^3)$。

设 $a(N)$ 表示有序贝尔数，那么总复杂度为 $\mathcal{O}(N^{N + 1} + a(N) N^3)$，肆意通过。

## Code

```cpp
#include <bits/stdc++.h>

typedef long long valueType;
typedef std::vector<valueType> ValueVector;
typedef std::vector<ValueVector> ValueMatrix;

namespace MODINT {
    constexpr valueType MOD = 1e9 + 7;

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
    T1 sum(T1 a, T2 b, const T3 &mod = MOD) {
        return a + b >= mod ? a + b - mod : a + b;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 sub(T1 a, T2 b, const T3 &mod = MOD) {
        return a - b < 0 ? a - b + mod : a - b;
    }

    template<typename T1, typename T2, typename T3 = valueType>
    T1 mul(T1 a, T2 b, const T3 &mod = MOD) {
        return (long long) a * b % mod;
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
}// namespace MODINT

using namespace MODINT;

valueType N, ans;
ValueVector A;

namespace MATH {
    ValueVector Fact, InvFact;

    void init(valueType n) {
        Fact.resize(n + 1);
        Fact[0] = 1;
        for (valueType i = 1; i <= n; ++i)
            Fact[i] = mul(Fact[i - 1], i);

        InvFact.resize(n + 1);
        InvFact[n] = pow(Fact[n], MOD - 2);
        for (valueType i = n - 1; i >= 0; --i)
            InvFact[i] = mul(InvFact[i + 1], i + 1);
    }

    valueType C(valueType n, valueType m) {
        valueType result = 1;

        for (valueType i = 0; i < m; ++i)
            Mul(result, (n - i) % MOD);

        Mul(result, InvFact[m]);

        return result;
    }
}// namespace MATH

using MATH::C;

bool check(ValueVector const &rank) {
    ValueVector copy(rank.begin(), rank.begin() + N + 1);

    std::sort(copy.begin(), copy.end());

    for (valueType i = 1; i <= N; ++i)
        if (copy[i] - copy[i - 1] > 1)
            return false;

    return true;
}

valueType length(ValueVector const &rank) {
    ValueVector F(N + 1, 0);
    valueType result = 0;

    for (valueType i = 1; i <= N; ++i)
        for (valueType j = 0; j < i; ++j)
            if (rank[i] > rank[j])
                result = std::max(result, F[i] = std::max(F[i], F[j] + 1));

    return result;
}

valueType calc(ValueVector const &rank) {
    valueType const M = *std::max_element(rank.begin(), rank.end());

    ValueVector limit(M + 1, std::numeric_limits<valueType>::max());

    for (valueType i = 1; i <= N; ++i)
        limit[rank[i]] = std::min(limit[rank[i]], A[i]);

    for (valueType i = M - 1; i >= 0; --i)
        limit[i] = std::min(limit[i], limit[i + 1]);

    limit[0] = 0;

    ValueMatrix F(M + 1, ValueVector(M + 1, 0));

    F[0][0] = 1;

    for (valueType i = 1; i <= M; ++i) {            // 前 i 段
        for (valueType j = i; j <= M; ++j) {        // 放了 j 种数
            for (valueType k = i - 1; k <= j; ++k) {// 前 i - 1 段放了 j 种数
                Inc(F[i][j], mul(F[i - 1][k], C(limit[i] - limit[i - 1], j - k)));
            }
        }
    }

    return F[M][M];
}

namespace DFS {
    ValueVector rank;

    void init(valueType n) {
        rank.resize(n + 1);
    }

    void dfs(valueType x) {
        if (x > N) {
            if (check(rank))
                Inc(ans, mul(length(rank), calc(rank)));

            return;
        }

        for (valueType i = 1; i <= N; ++i) {
            rank[x] = i;

            dfs(x + 1);
        }
    }
}// namespace DFS

using DFS::dfs;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> N;

    MATH::init(N);
    DFS::init(N);

    A.resize(N + 1);

    for (valueType i = 1; i <= N; ++i)
        std::cin >> A[i];

    dfs(1);

    for (valueType i = 1; i <= N; ++i)
        Mul(ans, pow(A[i] % MOD, MOD - 2));

    std::cout << ans << std::endl;

    return 0;
}
```

---

## 作者：henrytb (赞：0)

如果暴力枚举钦定 LIS 是谁的话，看似可以容斥，但是会数重。

正确的做法是发现 $n$ 实在是很小，因此甚至可以把整个序列的序都钦定出来，这样是 $O(n^n)$ 的。

然后钦定出序来了之后统计这个序的方案数，可以再 `dfs` 一次枚举每个作为序的数在哪个值域区间内，这样就很好统计答案。如果是多个数在同一个区间内，用组合数即可。

```cpp
#include <bits/stdc++.h>
#define int long long
#define rep(i, a, b) for (int i = (a); i <= (b); ++i)
#define per(i, a, b) for (int i = (a); i >= (b); --i)
using namespace std;
const int N = 7;
const int mod = 1e9 + 7;
int n, a[N], b[N], nn;
int ds[N], p[N], now[N];
int res = 0;
int f[N], ned[N];
int fac[N], ifac[N];
inline int qpow(int a, int b) {
    int res = 1;
    while (b) {
        if (b & 1) res = res * a % mod;
        a = a * a % mod;
        b >>= 1;
    }
    return res;
}
inline int C(int n, int m) {
    int res = ifac[m];
    per(i, n, n - m + 1) res = res * i % mod;
    return res;
}
void dfs2(int dep, int gx) {
    if (dep > n) {
        rep(i, 1, nn) ned[i] = 0;
        int lst = 0;
        int tmpp = 1;
        rep(i, 1, n) {
            int tmp = 0;
            bool flg = 0;
            rep(j, 1, n) if (p[j] == i) {
                flg = 1;
                if (tmp && tmp != now[j]) goto fail;
                tmp = now[j];
            }
            if (!flg) break;
            if (tmp < lst) goto fail;
            ++ned[tmp];
            lst = tmp;
        }
        rep(i, 1, nn) {
            tmpp = tmpp * C(ds[i], ned[i]) % mod;
        }
        res = (res + tmpp * gx % mod) % mod;
        fail:
        return;
    }
    rep(i, 1, a[dep]) now[dep] = i, dfs2(dep + 1, gx);
}
void dfs(int dep) {
    if (dep > n) {
        rep(i, 1, n) b[i] = p[i];
        sort(b + 1, b + n + 1);
        int lis = 0;
        if (b[1] != 1) goto fail;
        rep(i, 1, n - 1) if (b[i + 1] - b[i] > 1) goto fail;
        rep(i, 1, n) {
            f[i] = 1;
            rep(j, 1, i - 1) if (p[j] < p[i]) f[i] = max(f[i], f[j] + 1);
            lis = max(lis, f[i]);
        }
        dfs2(1, lis);
        fail:
        return;
    }
    rep(i, 1, n) {
        p[dep] = i;
        dfs(dep + 1);
    }
}
signed main() {
    scanf("%lld", &n);
    fac[0] = 1;
    rep(i, 1, n) fac[i] = fac[i - 1] * i % mod;
    ifac[n] = qpow(fac[n], mod - 2);
    per(i, n - 1, 0) ifac[i] = ifac[i + 1] * (i + 1) % mod;
    int inv = 1;
    rep(i, 1, n) scanf("%lld", &a[i]), inv = inv * a[i] % mod;
    rep(i, 1, n) b[i] = a[i];
    sort(b + 1, b + n + 1);
    nn = unique(b + 1, b + n + 1) - b - 1;
    rep(i, 1, nn) {
        ds[i] = b[i] - b[i - 1];
    }
    rep(i, 1, n) {
        a[i] = lower_bound(b + 1, b + nn + 1, a[i]) - b;
    }
    dfs(1);
    printf("%lld\n", res * qpow(inv, mod - 2) % mod);
    return 0;
}
```

---

## 作者：1234567890sjx (赞：0)

（很抱歉前面忘记记是第多少题了）

发现 $n$ 巨小无比，因此考虑和 $n$ 强相关且和值域无关的指数级高复杂度算法。

发现 LIS 只和两个数的相对大小有关系。因此考虑把每一个数都离散化到 $[1,n]$ 范围内，然后暴力 dp 算 lis 长度，之后随便组合计数算出不同的满足相对大小关系的方案数乘起来即可。

思路理顺之后，代码还是蛮好写的。时间复杂度大于 $O(n^n)$，但是 $n$ 太小所以仍然可过。

---

