# [ARC185E] Adjacent GCD

## 题目描述

定义一个整数序列 $B=(B_1,B_2,\dots,B_k)$ 的分数为 $\sum_{i=1}^{k-1}\gcd(B_i,B_{i+1})$。

给出一个整数序列 $A=(A_1,A_2,\dots,A_N)$，求出以下问题在 $m=1,2,\dots,N$ 时的答案：

- 序列 $A=(A_1,A_2,\dots,A_m)$ 有 $2^m-1$ 个非空子序列。求出这些子序列的分数之和对 $998244353$ 取模后的值。如果两个子序列在原序列中的位置不同，即使它们的元素全部相同，我们也认为它们是不同的。

## 说明/提示

- $1\le N\le 5\times 10^5$
- $1\le A_i\le 10^5$
- 输入的值全部为整数

## 样例 #1

### 输入

```
3
9 6 4```

### 输出

```
0
3
11```

## 样例 #2

### 输入

```
5
3 8 12 6 9```

### 输出

```
0
1
13
57
155```

## 样例 #3

### 输入

```
10
47718 21994 74148 76721 98917 73766 29598 59035 69293 29127```

### 输出

```
0
2
14
35
97
372
866
1859
4273
43287```

# 题解

## 作者：Nt_Tsumiki (赞：7)

介绍一个直接容斥的做法。

因为它让你求出所有前缀的答案，所以不难想到增量。

继承答案是简单的，有：$ans_i\gets 2ans_{i-1}$，实际上就是在末尾加上一个可选可不选的位。

考虑先如何加入一个数 $a_i$，我们不妨去枚举一个 $j$，钦定 $j$ 到 $i$（不包含端点）不选，$j$ 之前随意，那么贡献是 $\sum2^{j-1}\times\gcd(a_j,a_i)$，直接做显然是做不了的，考虑容斥。

不妨去枚举约数，对于 $i$ 之前的数 $a_j$，在他们的约数处加上一个 $2^{j-1}$ 的贡献，那么对于一个 $a_i$ 的约数 $d$ 直接把他当成 $\gcd$ 算贡献的话，对应的 $d$ 的所有约数都会被当成 $\gcd$ 算一遍，所以我们考虑给每个 $d$ 分配一个 $v_d=d-\sum_{k|d\land k\ne d} v_k$ 的容斥系数，不难发现就容斥掉了。

```cpp
#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

#define N 100005
#define M 500005
#define LL long long
#define MOD 998244353

inline int R() {
    int x=0; bool f=0; char c=getchar();
    while (!isdigit(c)) f|=(c=='-'),c=getchar();
    while (isdigit(c)) x=x*10+c-'0',c=getchar();
    return f?-x:x;
}

template<typename T>
void W(T x,int op=0) {
    if (x<0) return putchar('-'),W(-x,op);
    if (x>9) W(x/10); putchar(x%10+'0');
    if (op) putchar(op==1?' ':'\n');
}

using namespace std;
int n,a[M]; LL w[N],val[N];
vector<LL> d[N];

LL quickpow(LL a,int k) {
    LL res=1;
    while (k) {
        if (k&1) res=res*a%MOD;
        a=a*a%MOD,k>>=1;
    }
    return res;
}

int main() {
    n=R();
    for (int i=1;i<N;i++) {
        (val[i]+=i)%=MOD; d[i].push_back(i);
        for (int j=i+i;j<N;j+=i) d[j].push_back(i),(val[j]-=val[i])%=MOD;
    }
    for (int i=1;i<=n;i++) a[i]=R();
    LL ans=0;
    for (int i=1;i<=n;i++) {
        int tmp=a[i]; LL tw=quickpow(2,i-1);
        ans=ans*2%MOD;
        for (int j:d[a[i]]) (ans+=w[j]*val[j]%MOD)%=MOD,(w[j]+=tw)%=MOD;
        W((ans+MOD)%MOD,2);
    }
    return 0;
}
```

PS：不难发现 $\varphi(d)=v_d$，因为我们有 $n=\sum_{d|n}\varphi(d)$。

---

## 作者：xwh_Marvelous (赞：4)

直接求不好求，考虑算贡献。那么：

$$ans_i=\sum_{x=2}^i\sum_{y=1}^{x-1}\gcd(a_x,a_y)2^{i-(x-y+1)}$$

其中有若干有序对 $(x,y)$ 重叠，可以发现如下事实：

$$ans_i=2ans_{i-1}+\sum_{y=1}^{i-1}\gcd(a_i,a_y)2^{y-1}$$

因此只需要对于每个 $i$ 计算：

$$\sum_{y=1}^{i-1}\gcd(a_i,a_y)2^{y-1}$$

考虑欧拉反演，

$$\sum_{y=1}^{i-1}2^{y-1}\sum_{d|\gcd(a_i,a_y)}\varphi(d)$$

由于 $\gcd(a_i,a_y)$ 的因数也必然是 $a_i$ 的因数，因此可写作：

$$\sum_{d|a_i}\varphi(d)\sum_{y=1}^{i-1}2^{y-1}[d|a_y]$$

记 $g_i=\sum_{y=1}^{i-1}2^{y-1}[i|a_y]$

$$\sum_{d|a_i}\varphi(d)g_d$$

求这个式子是 $O(\sigma(a_i))$ 的，其中 $\sigma(a_i)$ 表示其因数个数。

只需要维护 $g$ 即可，每次考虑加入 $a_i$，枚举其因数 $d$，使 $g_d \larr g_d+2^{i-1}$ 即可，这也是 $O(\sigma(a_i))$ 的。

由于 $\max_{i=1}^{10^5}\sigma(i)=128$，不严谨的表示一下复杂度为 $O(128n)$，可过，最慢点大概不超过 $500ms$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define mod 998244353
#define N 500005
#define V 100005
//#define pii pair<int,int>
//#define fi first
//#define se second
//#define rep(i,j,k) for(int i=j;i<=k;i++)
int fpow(int x,int y){
	int ret=1,op=x;
	op%=mod;
	while(y){
		if(y&1)ret=ret*op%mod;
		op=op*op%mod;
		y>>=1;
	}
	return ret;
}
int a[N];
int n;
int vis[V];
int val[V];
vector<int>d[V];
void init(){
	for(int i=1;i<=V-5;i++){
		for(int j=i;j<=V-5;j+=i){
			d[j].push_back(i);
		}
	}
	for(int i=1;i<=V-5;i++){
		val[i]=i;
		for(int v:d[i])if(v!=i)val[i]-=val[v];
		val[i]=(val[i]%mod+mod)%mod;
	}
}
int ans[V];
int f[N];
signed main(){
	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
	init();
	cin>>n;
	for(int i=1;i<=n;i++)cin>>a[i];
	for(int i=1;i<=n;i++){
		for(int v:d[a[i]])f[i]=(f[i]+ans[v])%mod;
		int o=fpow(2,i-1);
		// int o=1;
		for(int v:d[a[i]])ans[v]=(ans[v]+o*val[v])%mod;
	}
	for(int i=2;i<=n;i++)f[i]=(f[i]+f[i-1]*2)%mod;
	for(int i=1;i<=n;i++)cout<<f[i]<<'\n';
	return 0;
}
```

---

## 作者：Super_Cube (赞：3)

# Solution

题意：$\forall m\in[1,n]$，求 $\displaystyle\sum_{i=1}^m\sum_{j=i+1}^m\gcd(a_i,a_j)\cdot 2^{i-1}\cdot 2^{m-j}$。

设 $m$ 的答案为 $f_m$，那么 $f_{m+1}=2f_m+\displaystyle\sum_{i=1}^m\gcd(a_i,a_{m+1})\cdot 2^{i-1}$。

有个结论：$n=\displaystyle\sum_{d\mid n}\varphi(d)$。

证明？$n=\displaystyle\sum_{i\mid n}\sum_{j=1}^n[\gcd(j,n)=i]=\sum_{i\mid n}^n\varphi\left(\dfrac{n}{i}\right)$

于是：$\displaystyle\sum_{i=1}^m\gcd(a_i,a_{m+1})\cdot 2^{i-1}=\sum_{i=1}^m2^{i-1}\sum_{j|\gcd(a_i,a_{m+1})}\varphi(j)$。

枚举 $a_{m+1}$ 的因数 $j$，打个桶对 $j$ 累加 $i\in[1,m]$ 且 $j\mid a_i$ 的倍率 $2^{i-1}$。欧拉函数值可提前预处理得到。

时间复杂度：$O(n\sqrt V)$。

---

## 作者：ran_qwq (赞：2)

赛时差点就切了，被卡常了（悲）。

记 $f_i$ 为 $i=m$ 的答案，则 $f_i=2f_{i-1}+\sum\limits_{j=1}^{i-1}\gcd(a_j,a_i)\cdot2^{j-1}$。前面的贡献有 $i$ 取或不取两种方案，所以是 $2f_{i-1}$。后面的 $S=\sum\limits_{j=1}^{i-1}\gcd(a_j,a_i)\cdot2^{j-1}$ 意思是当前最后两个数是 $j,i$，前面的 $j-1$ 个数可取可不取。

后面那堆形式有点复杂，先把枚举下标变成枚举值：$S=\sum\limits_dg_d$，其中 $g_d$ 表示 $\gcd(a_j,a_i)$ 的 $2^{j-1}$ 之和。

再容斥一下转化为 $d$ 的倍数，记 $h_d$ 为 $\gcd(a_j,a_i)$ 是 $d$ 倍数的 $2^{j-1}$ 之和。

做到这里就可以把 gcd 拆开了，当 $d$ 为 $a_i$ 因数时，$h_d$ 又表示 $a_j$ 是 $d$ 倍数的 $2^{j-1}$ 之和。

$h_d$ 可以动态维护了：每新加一个数 $x$，就把所有 $x$ 的因数 $d$ 的 $h$ 值加上 $2^{i-1}$。

求 $S$ 时对每个 $d$，暴力枚举 $d$ 的倍数，$a_i$ 的因数容斥即可。

总复杂度是 $O(nd^2(V))$ 的（$d(i)$ 表示 $i$ 以内约数个数最大值），$d(V)=128$，执行次数（令 $n=5\times10^5,a_i=83160$）高达 $8\times10^9$，会超时。

优化一下，预处理出每个数的因子，不用每次都一个一个判，执行次数 $1.2\times10^9$，常数较小加上 AT 机子快，可以 1.6 秒通过。

```cpp
int n,ans,a[N],b[M],pw[N],w[M]; vi v[M];
void QwQ() {
	n=rd(),pw[0]=1;
	for(int i=1;i<=n;i++) pw[i]=vmul(pw[i-1],2);
	for(int i=1;i<=M-10;i++) {
		for(int j=1;j*j<=i;j++) if(i%j==0) 
			{v[i].pb(j); if(j*j!=i) v[i].pb(i/j);}
		sort(v[i].begin(),v[i].end());
	}
	for(int i=1;i<=n;i++) {
		a[i]=rd();
		if(i==1) puts("0");
		else {
			cmul(ans,2);
			for(int x:v[a[i]]) w[x]=b[x];
			for(int j=v[a[i]].size()-1;~j;j--) {
				cadd(ans,vmul(v[a[i]][j],w[v[a[i]][j]]));
				for(int k:v[v[a[i]][j]]) if(k!=v[a[i]][j]) csub(w[k],w[v[a[i]][j]]);
			}
			wr(ans,"\n");
		}
		for(int x:v[a[i]]) cadd(b[x],pw[i-1]);
	}
}
```

---

## 作者：jr_zch (赞：2)

# Adjacent GCD

## 题目大意

给定一个序列，对于其每一个前缀求出每一个子序列的权值。

一个序列的权值定义为相邻两个数的 $\gcd$ 之和。

## 解题思路

由于对于每一个前缀都要求，所以考虑加入一个数之后会产生的新贡献，设当前加入的数为 $a_i$。

考虑子序列选和不选 $a_i$ 两种情况，如果不选就是上一位的答案，如果选，产生的新贡献即为下式。

$$
\sum_{j=1}^i \gcd(a_i,a_j) \times 2^{j-1}
$$

就是枚举和它相邻的数是谁，然后发现这个式子很欧拉反演，于是可以用欧拉反演化简。

$$
\sum_{j=1}^i \gcd(a_i,a_j) \times 2^{j-1}\\

= \sum_{j=1}^i 2^{j-1} \sum_{d|\gcd(a_i,a_j)} \varphi(d)\\

= \sum_{j=1}^i 2^{j-1} \sum_{d|a_i,d|a_j} \varphi(d)\\

= \sum_{d|a_i} \varphi(d) \sum_{j=1}^n [d|a_j] \times 2^{j-1}
$$

先预处理欧拉函数，然后对于每一个 $i$，枚举 $a_i$ 的因数，然后看前面的数对于系数的贡献即可。

时间复杂度瓶颈在于枚举因数，我写的 $\sqrt V$ 的暴力枚举，总时间复杂度为 $O(V + n \sqrt V)$，其中 $V$ 表示值域。

## Code：

```c++
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=5e5+7,mod=998244353;
int n,cnt,ans;
int a[maxn],phi[maxn],pri[maxn],base[maxn],f[maxn];
bool is[maxn];

int _mod(int x){
	return x>=mod?x-mod:x;
}

signed main(){
	//线性筛预处理欧拉函数 
	phi[1]=1;
	for(int i=2;i<=1e5;i++){
		if(!is[i]) pri[++cnt]=i,phi[i]=i-1;
		for(int j=1;j<=cnt&&i*pri[j]<=1e5;j++){
			is[i*pri[j]]=1;
			if(!(i%pri[j])){
				phi[i*pri[j]]=phi[i]*pri[j];
				break;
			}
			phi[i*pri[j]]=phi[i]*(pri[j]-1);
		}
	}
	scanf("%lld",&n),base[0]=1;
	for(int i=1;i<=n;i++) base[i]=_mod(base[i-1]+base[i-1]);
	for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=n;i++){
		ans=_mod(ans+ans);
		//枚举因数算答案 
		for(int j=1;j*j<=a[i];j++){
			if(!(a[i]%j)){
				ans=(ans+phi[j]*f[j])%mod;
				if(j*j!=a[i]) ans=(ans+phi[a[i]/j]*f[a[i]/j])%mod;
			}
		}
		//计算对后续的贡献 
		for(int j=1;j*j<=a[i];j++){
			if(!(a[i]%j)){
				f[j]=_mod(f[j]+base[i-1]);
				if(j*j!=a[i]) f[a[i]/j]=_mod(f[a[i]/j]+base[i-1]);
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
```

---

## 作者：LostKeyToReach (赞：1)

纪念第一次场切 ARC E。

对于每个 $1 \le m \le n$，我们把求和式给写下来：

$$
\sum_{S \notin \empty, S \in \{1, 2, \ldots, n\}}\sum_{i = 1} ^ {|S| - 1}\gcd(A_{S_i}, A_{S_{i + 1}})
$$

直接枚举是 $O(2^n\times n)$ 的，考虑计算每对 $(i, j)$ 对答案的贡献，那么转换为：

$$
\sum_{i = 1} ^ n \sum_{j = i + 1} ^ n\gcd(i, j)f(i, j)
$$

$f(i, j)$ 即为 $2^{n - j} \times 2 ^{i - 1}$，因为 $1 \sim i - 1$ 随便选，$j + 1 \sim n$ 同理，因此这个式子成立。

接下来就开始大力推式子了：

$$
\begin{aligned}
\sum_{i = 1} ^ n \sum_{j = i + 1} ^ n\gcd(i, j)f(i, j) &= \sum_{i = 1} ^ n \sum_{j = i + 1} ^ n\gcd(i, j)2^{i - 1}2^{n - j} \\
&= \sum_{i = 1}^n\sum_{j = i + 1}^n2^{i - 1}2^{n - j}\sum_{d \mid A_i, d \mid A_j} \varphi(d) \\
&= \sum_{d = 1} ^ D\varphi(d)\sum_{1 \le i < j \le n, d \mid a_i, d \mid a_j}2^{i - 1}2^{n - j} \\
&= \sum_{d = 1}^ D \varphi(d)\sum_{i = 1}^n[d \mid a_i]2^{i - 1}\sum_{j = i + 1}^n[d \mid a_j]2^{n - j} \\
&= \sum_{d = 1}^D \varphi(d)\sum_{i = 1}^n[d \mid a_i]2^{n + i - 1}\sum_{j = i + 1}^n[d \mid a_j]2^{-j}
\end{aligned}
$$


做一波前缀和即可。

时间复杂度 $O(n + V \log V + \sum d_{a_i})$。

参考代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
constexpr int mx = 1e5 + 6, P = 998244353;
int n, a[500006];
int phi[mx], vis[mx], pr[mx], tot;
int pw[500006], pw_inv[500006]; 
int s[500006], sd[mx];
int pre[500006];
int32_t main() {
  ios::sync_with_stdio(0); cin.tie(0), cout.tie(0);
  cin >> n;
  for (int i = 1; i <= n; ++i) cin >> a[i];
  phi[1] = 1;
  for (int i = 2; i < mx; ++i) {
    if (!vis[i]) {
      pr[++tot] = i;
      phi[i] = i - 1;
    }
    for (int j = 1; j <= tot && i * pr[j] < mx; ++j) {
      vis[i * pr[j]] = 1;
      if (i % pr[j] == 0) {
        phi[i * pr[j]] = phi[i] * pr[j];
        break;
      }
      phi[i * pr[j]] = phi[i] * (pr[j] - 1);
    }
  }
  vector<vector<int>> divs(mx);
  for (int i = 1; i < mx; ++i) {
    for (int j = i; j < mx; j += i) {
      divs[j].emplace_back(i);
    }
  }
  int inv2 = (P + 1) / 2;
  pw[0] = pw_inv[0] = 1;
  for (int i = 1; i <= n; ++i) {
    pw[i] = pw[i - 1] * 2 % P;
    pw_inv[i] = pw_inv[i - 1] * inv2 % P;
  }
  for (int i = 1; i <= n; ++i) {
    for (auto v : divs[a[i]]) {
      s[i] += phi[v] * sd[v] % P;
      s[i] %= P;
    }
    for (auto v : divs[a[i]]) {
      sd[v] = (sd[v] + pw[i - 1]) % P;
    }
  }
  for (int i = 1; i <= n; ++i) {
    pre[i] = (pre[i - 1] + s[i] * pw_inv[i] % P) % P;
  }
  for (int i = 1; i <= n; ++i) {
    cout << pre[i] * pw[i] % P << '\n';
  }
}
```

---

## 作者：cancan123456 (赞：0)

一场 ARC 只会 CDE /kx

设 $a_1,\dots,a_m$ 的答案为 $f_m$，拆贡献，设 $(a_i,a_j)$ 在选出的子序列中相邻，这样的子序列有 $2^{m-j+i-1}$ 个，所以 $f_m=\sum_{i=1}^m\sum_{j=i+1}^m\gcd(a_i,a_j)2^{m-j+i-1}$。

直接计算是 $O(n^3)$ 的，过不去，考虑增量计算，容易发现 $f_1=0,f_m=2f_{m-1}+\sum_{i=1}^{m-1}2^{i-1}\gcd(a_i,a_m)$，则只需计算 $\sum_{i=1}^{m-1}2^{i-1}\gcd(a_i,a_m)$。

考虑经典反演 $\gcd(x,y)=\sum_{k|x,k|y}\varphi(k)$，所以：

$$\begin{aligned}\sum_{i=1}^{m-1}2^{i-1}\gcd(a_i,a_m)&=\sum_{i=1}^{m-1}2^{i-1}\sum_{k|a_i,k|a_m}\varphi(k)\\&=\sum_{k|a_m}\varphi(k)\sum_{i=1}^{m-1}[k|a_i]2^{i-1}\end{aligned}$$

则只需要维护 $g_k=\sum_{i=1}^{m-1}[k|a_i]2^{i-1}$ 即可，容易发现 $m$ 增加 $1$ 时只有 $d(a_m)$ 个 $g$ 发生改变，可以暴力维护，其中 $d(n)$ 为 $n$ 的约数个数。

总时间复杂度为 $O\Big(\sum_{k=1}^nd(a_k)\Big)$，可以通过此题。

```cpp
#include <cstdio>
#include <vector>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int N = 500005;
int prime[N], pcnt, phi[N];
bool is_prime[N];
int a[N];
int gcd(int a, int b) {
	return b == 0 ? a : gcd(b, a % b);
}
vector < int > divisor[N];
void Euler(int n) {
	for (int i = 2; i <= n; i++) {
		is_prime[i] = true;
	}
	phi[1] = 1;
	for (int i = 2; i <= n; i++) {
		if (is_prime[i]) {
			pcnt++;
			prime[pcnt] = i;
			phi[i] = i - 1;
		}
		int ub = n / i;
		for (int j = 1; j <= pcnt && prime[j] <= ub; j++) {
			is_prime[i * prime[j]] = false;
			if (i % prime[j] == 0) {
				phi[i * prime[j]] = phi[i] * prime[j];
			} else {
				phi[i * prime[j]] = phi[i] * (prime[j] - 1);
			}
		}
	}
	for (int i = 1; i <= n; i++) {
		for (int j = i; j <= n; j += i) {
			divisor[j].push_back(i);
		}
	}
}
ll sum[N];
int main() {
//	freopen("in.txt", "r", stdin);
	Euler(100000);
	int n;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	for (ll ans = 0, i = 1, pow2 = 1; i <= n; i++, pow2 = pow2 * 2 % mod) {
		ans = ans * 2 % mod;
		for (int d : divisor[a[i]]) {
			ans = (ans + sum[d] * phi[d]) % mod;
		}
		for (int d : divisor[a[i]]) {
			sum[d] = (sum[d] + pow2) % mod;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
```

---

## 作者：WRuperD (赞：0)

[本题解同步发表于我的博客中](https://wruperd.github.io/post/arc185e-adjacent-gcd-ti-jie/)

第一次场切 ARC E。提供一种简单思考角度的解法。

首先考虑 $m -1$ 的答案推到 $m$ 的答案。发现 $Ans_{m} = 2Ans_{m-1}+ \sum\limits_{i=1}^{m-1} \operatorname{gcd}(a_i,a_m) \cdot 2^{i-1}$。

观察到 $O(n\sqrt V)$ 可过于是考虑枚举 $\sum \limits_{\operatorname{gcd}(a_i, a_m) = x} x \cdot pos_x$ 其中 $pos_x = \sum \limits_{i=1}^{m-1} [\operatorname{gcd}(a_i,a_m) = x] \cdot i$。

但是发现你没办法快速确定 $pos_x$ 的值。所以你考虑直接容斥。枚举 $a_m$ 的因数 $d$。

$$\sum \limits_{\operatorname{gcd}(a_i, a_m) = x} x \cdot pos_x = \sum \limits_{d| a_i, d | a_m} w_d \cdot pos_d$$

接下来考虑 $w_d$ 的意义。发现如果 $d$ 就是 $\operatorname{gcd}(a_i,a_m)$ 的话那么所有 $d$ 的因数的贡献都会再次被算一遍。所以可以简单的看出:

$$ w_x = x - \sum \limits_{d|x} w_d$$

预处理所有的 $w$ 就做完了。

```cpp
// Problem: E - Adjacent GCD
// URL: https://atcoder.jp/contests/arc185/tasks/arc185_e
// Writer: WRuperD
// Powered by CP Editor (https://cpeditor.org)
#include<bits/stdc++.h>
using namespace std;
const long long inf = 1e18;
const int mininf = 1e9 + 7;
#define int long long
#define pb emplace_back
inline int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9'){x=(x<<1)+(x<<3)+(ch^48);ch=getchar();}return x*f;}
inline void write(int x){if(x<0){x=~(x-1);putchar('-');}if(x>9)write(x/10);putchar(x%10+'0');}
#define put() putchar(' ')
#define endl puts("")
const int MAX = 5e5 + 10;
const int MAX2 = 1e5 + 10;

const int mod = 998244353;

int a[MAX];
int w[MAX];

int cnt[MAX];

void solve(){
	
	int n = read();
	// write(w[2]), endl;
	for(int i = 1; i <= n; i++){
		a[i] = read();
	}
	
	int preans = 0;
	int now = 1;
	for(int i = 1; i <= n; i++){
		preans = preans * 2 % mod;
		// write(preans), endl;
		for(int j = 1; j * j <= a[i]; j++){
			if(a[i] % j)	continue;
			preans = (preans + w[j] * cnt[j] % mod) % mod;
			if(a[i] / j != j)	preans = (preans + w[a[i] / j] * cnt[a[i] / j] % mod) % mod;
		}
		for(int j = 1; j * j <= a[i]; j++){
			if(a[i] % j)	continue;
			cnt[j] = (cnt[j] + now) % mod;
			if(a[i] / j != j)	cnt[a[i] / j] = (cnt[a[i] / j] + now) % mod;
		}
		write(preans), endl;
		now = now * 2 % mod;
	}
	
	
}

signed main(){
	for(int i = 1; i <= MAX2; i++){
		w[i] = i;
		if(i == 1)	continue;
		for(int j = 1; j * j <= i; j++){
			if(i % j)	continue;
			w[i] = (w[i] + mod - w[j]) % mod;
			if(i / j != j and j > 1)	w[i] = (w[i] + mod - w[i / j]) % mod;	
		}
	}
	int t = 1;
	while(t--)	solve();
	return 0;
}

```

---

## 作者：baoyangawa (赞：0)

# 题意简述

定义一个序列的权值为：相邻两项的 $\gcd$ 之和。

给定序列 $a$，对于其每个前缀 $a_{1\dots m}$，求该前缀的所有子序列的权值和。答案对 $998244353$ 取模。

# 题解

我们记 $f_i$ 为前缀 $i$ 的答案。有初值：

$$f_1 = 0,f_2 = \gcd(a_1, a_2)$$

假设已经算出了 $f_i$，考虑如何求出 $f_{i+1}$。

$a_{1\dots i}$ 的每个子序列，选择是否把 $a_{i+1}$ 加在序列末尾，能够构成 $a_{i\dots i+1}$ 的所有子序列。所以 $2\times f_{i}$ 会贡献到 $f_{i+1}$ 中。

考虑由 $a_{i+1}$ 造成的贡献。我们枚举 $a_{i+1}$ 的前一项是 $a_{j},1\le j \le i$。此时 $a_{j}$ 和 $a_{i+1}$ 一定被选中在子序列中，而对于所有的 $a_k$ 满足 $j<k<i+1$，都一定不在子序列中。

剩余的 $a_k$ 满足 $1 \le k < j$ 都可以在 / 不在子序列中，故贡献为 $\gcd(a_j, a_{i+1})\times 2^{j-1}$。这部分的总贡献：

$$\sum_{j=1}^{i}\gcd(a_j,a_{i+1})\times2^{j-1}$$

推一下式子。我们记 $v=a_{i+1}$。枚举 $v$ 的因数 $d$：

$$\sum_{d=1}^{N}[d\mid v]d\sum_{j=1}^{i}[d\mid a_j][\gcd(\frac{a_j}{d}, \frac{v}{d})=1]2^{j-1}$$

对 $[\gcd(\frac{a_j}{d}, \frac{v}{d})=1]$ 进行莫反：

$$\sum_{d=1}^{N}[d\mid v]d\sum_{j=1}^{i}[d\mid a_{j}]\sum_{k\mid \gcd(a_j/d, v/d)}\mu(k)2^{j-1}$$

我们考虑直接枚举 $k$：

$$\sum_{d=1}^{N}\sum_{k=1}^{N}d\mu(k)[dk \mid v]
\sum_{j=1}^{i}[dk \mid a_j]2^{j-1}$$

使用推式子经典套路：枚举 $T=dk$：

$$\sum_{T=1}^{N}[T|v]\sum_{d|T}d\mu(\frac{T}{d})\sum_{j=1}^{i}[T \mid a_j]2^{j-1}$$

发现其中 $\sum\limits_{d|T}d\mu(\frac{T}{d})$ 就是 $id\ast\mu$（$id(n)=n$ 函数和 $\mu$ 函数的狄利克雷卷积），也就是 $\varphi$：

$$\sum_{T|v}\varphi(T)\sum_{j=1}^{i}[T \mid a_j]2^{j-1}$$

我们可以预处理处 $1\sim 10^5$ 每个数的因数，以及 $\varphi$。

此时直接枚举 $v$ 的因数 $T$，用 $\varphi(T)$ 去乘上一个关于 $T$ 的系数（记作 $c_T$）。

我们发现这个系数可以随着 $i$ 的枚举实时计算。具体的，枚举到 $i$ 时，先计算出 $f_{i}$，再枚举 $a_i$ 的因数 $T$，向 $c_T$ 加上 $2^{i-1}$。

总时间复杂度：$O(\sum_{i=1}^n d(a_i))$，其中 $d(x)$ 为 $x$ 的因数个数。

查表可得 $\max_{x=1}^{10^5} d(x)$ 为 $128$，可以通过本题。

[提交记录](https://atcoder.jp/contests/arc185/submissions/58799142)

---

