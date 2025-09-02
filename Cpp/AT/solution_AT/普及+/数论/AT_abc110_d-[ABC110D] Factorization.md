# [ABC110D] Factorization

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc110/tasks/abc110_d

正整数 $ N,\ M $ が与えられます。

$ a_1\ \times\ a_2\ \times\ ...\ \times\ a_N\ =\ M $ となる正整数からなる長さ $ N $ の数列 $ a $ が何通りあるかを $ 10^9+7 $ で割った余りを求めてください。

ただし、数列 $ a' $ と $ a'' $ が異なるとは、ある $ i $ が存在して $ a_i'\ \neq\ a_i'' $ であることをいいます。

## 说明/提示

### 制約

- 入力はすべて整数である
- $ 1\ \leq\ N\ \leq\ 10^5 $
- $ 1\ \leq\ M\ \leq\ 10^9 $

### Sample Explanation 1

$ \{a_1,\ a_2\}\ =\ \{1,\ 6\},\ \{2,\ 3\},\ \{3,\ 2\},\ \{6,\ 1\} $ の $ 4 $ 通りの数列が条件を満たします。

## 样例 #1

### 输入

```
2 6```

### 输出

```
4```

## 样例 #2

### 输入

```
3 12```

### 输出

```
18```

## 样例 #3

### 输入

```
100000 1000000000```

### 输出

```
957870001```

# 题解

## 作者：ran_qwq (赞：8)

学校模拟赛时找规律过了，写篇题解纪念一下。

怎么找规律呢？先 dfs 打出 $N\leq5,M\leq24$ 的表。

```cpp
void dfs(int k,int sum)
{
	if(k>n)
	{
		if(sum==m) ans++;
		return;
	}
	if(sum>m) return;
	for(int i=1;i<=m;i++) dfs(k+1,sum*i);
}
```

```
 M=1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24
   1   1   1   1   1   1   1   1   1   1   1   1   1   1   1   1   1   1   1   1   1   1   1   1
   1   2   2   3   2   4   2   4   3   4   2   6   2   4   4   5   2   6   2   6   4   4   2   8
   1   3   3   6   3   9   3  10   6   9   3  18   3   9   9  15   3  18   3  18   9   9   3  30
   1   4   4  10   4  16   4  20  10  16   4  40   4  16  16  35   4  40   4  40  16  16   4  80
   1   5   5  15   5  25   5  35  15  25   5  75   5  25  25  70   5  75   5  75  25  25   5 175
```

根据表，首先得到一个结论：答案与 $M$ 究竟是多少无关，只与 $M$ 的质因数的次数有关。如 $M=12=2^2\times3$ 和 $M=18=3^2\times2$ 这两列是一样的。

找出质因数构成不同的那些数，取 $2,4,6,8,12$，设答案为 $ans$，找出这些列的规律（下面的 $p_1,p_2$ 表示两个质数，且 $p_1\neq p_2$）：

$M=2$ 时，即 $M=p_1$ 时，$ans=N$。

$M=4$ 时，即 $M=p_1^2$ 时，$ans=C_{N+1}^2$。

$M=6$ 时，即 $M=p_1\times p_2$ 时，$ans=N^2$。

$M=8$ 时，即 $M=p_1^3$ 时，$ans=C_{N+2}^3$。

$M=12$ 时，即 $M=p_1^2\times p_2$ 时，$ans=C_{N+1}^2\times N$。

综上，可以找到规律：把 $M$ 分解质因数，$M=p_1^{a_1}\times p_2^{a_2}\dots\times p_k^{a_k}$。则 $ans=\prod\limits_{i=1}^kC_{N+a_i-1}^{a_i}$。用逆元求解即可。

其实这道题数学推理一点都不难，但是我太菜了没推出来。用插板法也可以推出 $ans=\prod\limits_{i=1}^kC_{N+a_i-1}^{a_i}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=2e5+10,INF=0x3f3f3f3f,Mod=1e9+7;
int read(){int x=0,f=1;char ch=getchar();while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();return x*f;}
void Write(int x){if(x<0){putchar('-'),Write(-x);return;}if(x<10){putchar(x+'0');return;}Write(x/10),putchar(x%10+'0');}
void write(int x,char *s){Write(x),printf("%s",s);}
int n,m,len,ans=1,fac[N],ifac[N],pr[N],cnt[N];
int power(int a,int b=Mod-2) {int ans=1;while(b) {b&1?ans=ans*a%Mod:1,b>>=1,a=a*a%Mod;}return ans;}
int C(int n,int m) {return n>=m?fac[n]*ifac[m]%Mod*ifac[n-m]%Mod:0;}
void solve()
{
	n=read(),m=read(),fac[0]=1;
	for(int i=1;i<=N-10;i++) fac[i]=fac[i-1]*i%Mod;
	ifac[N-10]=power(fac[N-10]);
	for(int i=N-11;~i;i--) ifac[i]=ifac[i+1]*(i+1)%Mod;
	for(int i=2;i*i<=m;i++)
		if(m%i==0)
		{
			pr[++len]=i;
			while(m%i==0) cnt[len]++,m/=i;
		}
	if(m!=1) pr[++len]=m,cnt[len]=1;
	for(int i=1;i<=len;i++) ans=ans*C(n+cnt[i]-1,cnt[i])%Mod;
	write(ans,"");
}
signed main()
{
	int T=1;
	while(T--) solve();
}
```

---

## 作者：Nightingale_OI (赞：5)

### 大意

长度为 $ n $ 的数组 $ a $ 满足：

$$ \prod_{i=1}^{n} a_i = m $$

求所有满足条件的 $ a $ 的个数。

### 思路

将 $ m $ 质因数拆分为 $ m = \prod {p_i}^{c_i} $ 。

对于每个 $ p_i $ 枚举这 $ c_i $ 个数放在 $ n $ 个位置的方案书即可，即 $ C_{n + c_i - 1}^{n - 1} $ 。

每种方案乘积即最终答案。

时间复杂度 $ O(\sqrt{m}) $ 。

### 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,s,l;
#define f(i,j,k) for(register int i=j;i<=k;++i)
#define g(i,j,k) for(register int i=j;i>=k;--i)
const int mo=1e9+7;
int ksm(int x,int p){
    if(p==0)return 1;
    int num=ksm(x,p/2);
    num=1ll*num*num%mo;
    if(p&1)num=1ll*num*x%mo;
    return num;
}
int C(int n,int m){
    if(n<m)return 0;
    int a=1,b=1;
    f(i,n-m+1,n)a=1ll*a*i%mo;
    f(i,1,m)b=1ll*b*i%mo;
    return 1ll*a*ksm(b,mo-2)%mo;
}
int a[30];
int main(){
    cin>>n>>m;
    for(register int i=2;i*i<=m;++i){
        for(l=0;m%i==0;m/=i)++l;
        if(l)a[++s]=l;
    }
    if(m!=1)a[++s]=1;
    l=1;
    f(i,1,s)l=1ll*l*C(n+a[i]-1,n-1)%mo;
    printf("%d\n",l);
    return 0;
}
```

---

## 作者：_Gabriel_ (赞：3)

### 思路

题意很简单，就是求长度为 $n$ 的正整数序列 $a$，且 $\prod a_i=M$ 的方案数。

首先，肯定要把 $M$ 给分解质因数，即 $M= \prod \limits_{i=1}^n p_i^{\alpha_i}$（$p_i$ 为质数）。

现在的工作就是把 $\alpha_i$ 个 $p_i$ 分到 $n$ 组中，也就把问题转换成了这个不定方程解的个数：

$\sum\limits_{i=1}^{n} x_i=\sum\limits_{i=1}^{n} \alpha_i=k$。

根据组合中的插板法可知，总方案数为：$\binom{n+k-1}{n-1}$。

求出这个组合数，题目就解决了。

### 代码


```c++
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll mod = 1e9 + 7; 
const int N = 2e5 + 10;
ll c[N][40];
ll ans = 1;
int n, m;

int main() {
	for (int i = 0; i <= 100030; i++) {
		c[i][0] = 1, c[i][i] = 1;
		for (int j = 1; j <= 30 && j <= i; j++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}//求组合数
	cin >> n >> m;
	for (int i = 2; i * i <= m; i++) {
		if (m % i == 0) {
			int k = 0;
			while (m % i == 0) {
				m /= i;
				k++;
			}
			ans = ans * c[n + k - 1][k] % mod;
		}
	}
	if (m > 1) {
		ans = ans * c[n][1] % mod;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：2huk (赞：2)

> 求有多少长度为 $n$ 的正整数序列 $a$ 满足 $\prod a_i  =m$。

首先我们将 $m$ 分解质因数。令 $m = \prod {p_i}^{q_i}$。

可以发现，对于 $q_i$ 个 $p_i$，我们要把它们分配到 $n$ 个 $a_j$ 中。

相当于是有 $q_i$ 个小球，放在 $n$ 个盒子中，且每个盒子内的小球数量任意（可以为空）。根据插板法答案为 $\dbinom{n + q_i - 1}{n - 1}$。

对于每个 $p_i$，答案应该相乘。因此答案为 $\prod \dbinom{n + q_i - 1}{n - 1}$。

[代码](https://atcoder.jp/contests/abc110/submissions/49210983)。

---

## 作者：xz001 (赞：1)

- 将 $m$ 分解质因数，对于每个质因子 $p_i$，我们计算它的数量 $c_i$，然后计算这 $c_i$ 个质因子分配到 $n$ 个位置的方案数，相乘即可。
- 计算 $c_i$ 个质因子分配到 $n$ 个位置的方案数可以用组合数，但本蒟蒻不会啊，但我听高大佬说过：dp 是万能的。于是我设立 $f_{i,j}$ 表示枚举到第 $i$ 个数字，还剩 $j$ 个质因子的方案数，枚举给第 $i$ 个数字分配的数量 $k$，我采用记忆化搜索的形式，转移为：
$$
f_{i,j}=\sum_{k=0}^{j}f_{i+1,j-k}
$$
- 由于 $c_i\le \log m$，所以复杂度为 $O(\sqrt m+n\log^2m)$。
- 代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;

const int mod = 1e9 + 7;

int T, n, m, ans = 1, f[100005][105];

int dfs (int i, int j) {
	if (i >= n) return 1;
	if (f[i][j] != -1) return f[i][j];
	int ans = 0;
	for (int k = 0; k <= j; ++ k) ans = (ans + dfs (i + 1, j - k)) % mod;
	return f[i][j] = ans;
}

signed main() {
	memset(f, -1, sizeof(f));
	scanf("%lld%lld", &n, &m);
	for (int j = 2; j * j <= m; ++ j) { 
	    if (m % j == 0) {
	    	int cnt = 0;
	    	while (m % j == 0) {
	    		m /= j;
	    		++ cnt;
			}
			ans = ans * dfs (1, cnt) % mod;
		}
	}
	if (m != 1) ans = ans * n % mod; 
	printf("%lld\n", ans);
	return 0;
}
```

---

## 作者：清烛 (赞：1)

题意：给定 $n$ 和 $m$，其中 $1\le n\le 10^5$，$1\le m\le 10^9$，问长度为 $n$ 且满足 $\prod a_i = m$ 的序列 $a$ 的个数。答案模 $10^9 + 7$ 输出。

将 $m$ 分解为 $\prod p_i^{k_i}$ 的形式之后，考虑给每一个 $a_i$ 分配质因子。对于 $p_i$，由插板法（本问题等价于 $k_i$ 个相同的球放入 $n$ 个不同的箱子，可以有空箱）可知其分配方案数为 $\dbinom{k_i + n - 1}{n - 1}$。那么算出每个 $p_i$ 对应的方案数然后乘在一起就可以了。时间复杂度 $O(n + \sqrt m)$。

```cpp
const int N = 2e5;
modint fac[N + 5], ifac[N + 5];

modint binom(int n, int m) {return fac[n] * ifac[m] * ifac[n - m];}

int main() {
    int n, m; read(n, m);
    fac[0] = 1;
    FOR(i, 1, N) fac[i] = i * fac[i - 1];
    ifac[N] = qPow(fac[N], mod - 2);
    modint ans = 1;
    DEC(i, N - 1, 0) ifac[i] = (i + 1) * ifac[i + 1];
    for (int i = 2; i * i <= m; ++i) {
        if (m % i) continue;
        int k = 0;
        while (m % i == 0) ++k, m /= i;
        ans *= binom(n + k - 1, n - 1);
    }
    if (m > 1) ans *= n;
    print(ans);
    return output(), 0;
}
```

---

## 作者：SpringFullGarden (赞：1)

## 题意

求 $n$ 个数的积等于 $m$ 的方案数。

## 思路

先分解质因数，设 $m = \prod \limits_{i= 1}^s p_i^{r_i}$。

对于每一个 $r_i$ 的方案数就是：有 $r_i$ 个球，把它分给 $n$ 个箱子里，箱子可以为空的方案数。

这是一个球同箱不同，箱可以为空的箱球模型，对于每一个 $r_i$ 的方案数为 $C_{n + r_i - 1}^{n - 1}$。

所以答案为 $\prod \limits_{i = 1}^s C_{n + i - 1}^{n - 1}$

## 代码

```cpp
ll fac[2000006], inv[2000006];

ll pw(ll x, ll y) {
	ll ans = 1;
	while(y) {
		if(y & 1) ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	return ans;
}
ll C(ll x, ll y) {
	return fac[y] % mod * inv[y - x] % mod * inv[x] % mod;
}
signed main() {
	ll n = rd(), m = rd(), ans = 1;
	fac[0] = 1;
	for(ll i = 1; i <= 2000000; i++) fac[i] = fac[i - 1] * i % mod;
	inv[2000000] = pw(fac[2000000], mod - 2) % mod;
	for(ll i = 1999999; i >= 0; i--) inv[i] = inv[i + 1] % mod * (i + 1) % mod;
	for(ll i = 2; i * i <= m; i++) {
		if(m % i == 0) {
			ll r = 0;
			while(m % i == 0) r++, m /= i;
			ans = ans * C(n - 1, n + r - 1) % mod;
		}
	}
	if(m > 1) ans = ans * n % mod;
	cout << ans;
	return 0;
}
```

---

## 作者：Lele_Programmer (赞：0)

# AT_abc110_d 题解

## 思路

将 $M$ 分解质因数，写成 $M=p_1^{\alpha_1} p_2^{\alpha_2}\cdots p_k^{\alpha_k}$ 的形式。

把 $N$ 个数看成 $N$ 个箱子，对于每一个质因子 $p_i$，相当于将 $\alpha_i$ 个相同的物体放进 $N$ 个箱子，不一定每一个箱子都有物体，方案数：

$$
\begin{aligned}
C_{n+\alpha_i-1}^{n-1} & = \frac{(n+\alpha_i-1)!}{(n+\alpha_i-1-n+1)!(n-1)!} \\
& = \frac{(n+\alpha_i-1)!}{\alpha_i!(n-1)!}
\end{aligned}
$$

所以答案就是 $\prod\limits_{i=1}^k\frac{(n+\alpha_i-1)!}{\alpha_i!(n-1)!} \bmod 1000000007$。

分数取模，考虑使用逆元，设 $ans_1$ 为分子，$ans_2$ 为分母，则求出 $ans_2$ 的逆元，与 $ans_1$ 相乘即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

#define _rep(i,a,b) for (int i=(a);i<=(b);++i)
#define _iter(i,a) for (auto i=a.begin();i!=a.end();++i)

const int N=200005;
const int mod=1e9+7;

int n,m;
unordered_map<int,int> hs;
int ans1=1,ans2=1;
int fac[N];

int exgcd(int a,int b,int& x,int& y) {
    if (!b) {
        x=1,y=0;
        return a;
    }
    int d=exgcd(b,a%b,y,x);
    y=y-a/b*x;
    return d;
}

int inv(int k) {
    int x,y;
    int t=exgcd(k,mod,x,y);
    return ((x%mod)+mod)%mod;
}

void init() {
    fac[1]=1;
    _rep(i,2,N-1) fac[i]=(fac[i-1]*i)%mod;
}

signed main() {
    init();
    scanf("%lld %lld",&n,&m);
    if (n==1) {
        printf("1");
        return 0;
    }
    _rep(i,2,sqrt(m+1)) while (m%i==0) m/=i,hs[i]++;
    if (m>=2) hs[m]++;
    _iter(it,hs) ans1=(ans1*fac[n+it->second-1])%mod,ans2=(((ans2*fac[it->second])%mod)*fac[n-1])%mod;
    printf("%lld",(ans1*inv(ans2))%mod);
    return 0;
}
```

---

## 作者：ForgetOIDuck (赞：0)

### 思路
按照正常的分解每个因数的话会爆（看样例 3）。

所以我们换一种思路，考虑将 $M$ 的每个质因数分到 $N$ 个数里，求方案数。

由于不同质因数之间的选择互相独立，所以我们考虑先分解质因数，然后对于每个质因数 $p_i$ 及其个数 $c_i$ 求解。

问题就转化成 **将 $c_i$ 个质数分到 $N$ 个数里的方案数**，相当于 **将 $c_i$ 个球放到 $N$ 个箱子里的方案数**。

由插板法可得方案数应为 $C_{n+c_i-1}^{n-1}$。

最后对于每个求出的方案数相乘即可。

### 代码
```cpp
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;//c(n + l, l)
const ll mod = 1e9 + 7;
ll f[200002], nf[200002], n, m, a, b, ans = 1;
ll qmi(ll x, ll y) {
    ll res = 1;
    while (y) {
        if (y & 1) res = res * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return res;
}
ll cc(ll a, ll b) {
	return f[a] * nf[b] % mod * nf[a - b] % mod;
}
int main() {
    f[0] = nf[0] = 1;
    for (int i = 1; i <= 200000; i ++ ) f[i] = f[i - 1] * i % mod, nf[i] = nf[i - 1] * qmi(i, mod - 2) % mod;
    cin >> n >> m;
    for (int c = 0, i = 2; i * i <= m; i ++ ) {
    	c = 0;
    	while (m % i == 0) c ++, m /= i;
    	if (c) ans = ans * cc(n + c - 1, n - 1) % mod;
    	
	}
	if (m > 1) ans = ans * cc(n, n - 1) % mod;
	cout << ans;
}
```

---

## 作者：XYQ_102 (赞：0)

隔板法：将 $n$ 个球放入 $m$ 个盒子中，盒子可以为空，那么方案数为 $C_{n+m-1}^{m-1}$。

**证明**：用隔板法相当于在 $n$ 个球中间插入 $m-1$ 块板子，但是有可能会出现连续空着的盒子出现，例如 `xx|xx|||xx` 的情况（用 `x` 代表球，`|` 代表插入的隔板）。那么最好的办法就是增加 $m$ 个球，假装每个盒子内至少有一个球。假设某个盒子内球的数量为 $x$ 个，那么盒子内实际的球数为 $x-1$ 个。相当于将 $n+m$ 个球分割为 $m$ 个空间，每个空间内至少要有一个球。所以方案数即为 $C_{n+m-1}^{m-1}$。

对于本题思路即是对于 $m$ 进行质因子分解，$m=p_1^{a_1}\times p_2^{a_2}\times p_3^{a_3}\times\cdots$ ，每一个质因子都是相对独立的，那么对于一个质因子就变成独立的小问题：将 $a_i$ 个球放入 $n$ 个盒子的方案数，总方案数就是将每一个质因子的方案数乘起来即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
const int N = 2e5 + 10;
#define gcd __gcd
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

LL f[N], inv[N];
vector<int> nums;
bool st[N];

LL kpow(LL a, LL n) {
	LL res = 1;
	while(n) {
		if(n & 1) res = res * a % mod;
		n >>= 1;
		a = a * a % mod;
	}
	return res;
}

void init() {
	int n = 2e5;
	f[0] = f[1] = 1;
	inv[0] = inv[1] = kpow(1, mod - 2);
	for(int i = 2; i <= n; i++) {
		f[i] = 1LL * f[i - 1] * i % mod;
		inv[i] = 1LL * inv[i - 1] * kpow(i, mod - 2) % mod;
		if(!st[i]) nums.push_back(i);
		for(int j = 0; j < nums.size() && i <= n / nums[j]; j++) {
			st[i * nums[j]] = true;
			if(i % nums[j] == 0) break;
		}
	}
}

LL C(LL a, LL b) {
	return f[a] * inv[b] % mod * inv[a - b] % mod;
}

void solve() {
	int n, m;
	scanf("%d%d", &n, &m);
	LL res = 1;
	for(int i = 0; i < nums.size() && nums[i] <= m / nums[i]; i++) {
		int cnt = 0;
		while(m % nums[i] == 0) {
			cnt++;
			m /= nums[i];
		}
		if(cnt > 0) {
			res = 1LL * res * C(n + cnt - 1, n - 1) % mod;
		}
	}
	if(m > 1) {
		res = 1LL * res * C(n, n - 1) % mod;
	}
	printf("%lld\n", res);
}

int main() {
	init();
	// freopen("in.txt", "r", stdin);
	// int t; cin >> t; while(t--)
	solve();
	return 0;
}
```

---

## 作者：Symbolize (赞：0)

# $\tt{Solution}$

先将 $M$ 质因数分解，拆成 $\prod p_i^{c_i}$ 的形式，那么实际上，就是对于每一个质数 $p_i$ 进行分配，因为唯一分解定理的存在，所以每一种分配都对应着一种不同的情况（在其他质数都分配好了的情况下），显然可以使用排列组合，重新转化以下问题，将 $c_i$ 个完全相同的小球放入 $n$ 个完全相同的盒子，利用插板法易得答案为 $C^{n-1}_{n+c_i-1}$，所以说答案即为 $\prod C^{n-1}_{n+c_i-1}$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define pii pair<int,int>
#define x first
#define y second
#define rep1(i,l,r) for(int i=l;i<=r;i++)
#define rep2(i,l,r) for(int i=l;i>=r;i--)
const int N=1e5+10;
const int mod=1e9+7;
using namespace std;
int n,m,id,a[N],ans=1;
inline int read()
{
	int x=0,f=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0'&&ch<='9')
	{
		x=(x<<1)+(x<<3)+(ch^48);
		ch=getchar();
	}
	return f*x;
}
int power(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%mod;
		b>>=1;
		a=(a*a)%mod;
	}
	return ans;
}
int C(int n,int m)
{
	if(n<m) return 0;
	int a=1,b=1;
	rep1(i,n-m+1,n) a=a*i%mod;
	rep1(i,1,m) b=b*i%mod;
	return a*power(b,mod-2)%mod; 
}
signed main()
{
	n=read();
	m=read();
	rep1(i,2,sqrt(m))
	{
		int len=0;
		while(m%i==0)
		{
			++len;
			m/=i;
		}
		if(len) a[++id]=len;
	}
	if(m!=1) a[++id]=1;
	rep1(i,1,id) ans=ans*C(a[i]+n-1,n-1)%mod;
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

# [Factorization 传送门](https://www.luogu.com.cn/problem/AT_abc110_d)

### 写在前面
本题在比赛打了 90 分，发个题解纪念一下~~这个耻辱~~。

# 题目解释
输入 $n$，$m$，输出 $n$ 个数连乘的积是 $m$ 的数量。$ans$ 模 $10^{9}+7$。同时序列是有序的，即序列 $A$ 和序列 $B$ 只要有两数 $A_{i}\ne B_{i}$，序列 $A$ 和 $B$ 就是不同的。

# 题目分析
乍一眼看，序列是**有序**的。同时任意正整数 $T$ 可以分解成：$T=a_{1}^{s_{1}}\times a_{2}^{s_{2}}\times \cdots\times a_{k}^{s_{k}}$，其中 $\forall i\in \left [ 1,k \right]$，$a_{i}$ 都是质数。
## 方法：
1. 构造一个数组 $ans_{i}$，其中每个数均为 1。
2. 对于 $m$ 的分解方法中的 $a_{i}$，$s_{i}$，将 $s_{i}$ 次的 $a_{i}$ 分配到每一个 $ans_{i}$ 中。因为 $a_{i}$ 是质数，所以这种方法与后面的分配**不会冲突**。其中分配方案有 $C_{n+s_{i}-1}^{n-1}$ 种。

Tips：如果最有有一个大于 $\sqrt{m}$ 的质数，需要特判。不然答案会是 $\frac{ans}{2}$。

# 参考代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=1e5+5;
const int MAX=1e5+100;
const int mod=1e9+7;
int n,m,ans=1;
int a[MAXN];
int pri[MAXN];
int inv[MAX];
int fac[MAX];
void checkk(){
	for(int i=2;i*i<=n;i++)
		if(a[i])return ;
	cout<<m;
	exit(0);
}
int ksm(int a,int b){
	int ans=1;
	while(b!=0){
		if(b&1)ans=(1ll*ans*a)%mod;
		a=(1ll*a*a)%mod;
		b>>=1; 
	}
	return ans;
}
void init(){
	fac[1]=1;
	inv[1]=1;
	for(int i=2;i<MAX;i++)
		fac[i]=fac[i-1]*i%mod;
	for(int i=2;i<MAX;i++)
		inv[i]=inv[i-1]*ksm(i,mod-2)%mod;
}
int c(int p,int q){ //p>q;
	if(p<q){
		return 0;
		exit(0);
	}
	return ((fac[p]*inv[q])%mod*inv[p-q])%mod;
}
signed main(){
	cin.tie(0);
	cout.tie(0);
	ios::sync_with_stdio(false);
	cin>>m>>n;//m个数连乘是n 
	if(n==1||m==1){
		cout<<1;
		exit(0);
	}
	for(int i=2;i*i<=n;i++)
		if(n%i==0)a[i]=1;
	for(int i=2;i*i<=n;i++){
		if(pri[i])continue;
		for(int j=2;j*i*j*i<=n;j++)
			pri[i*j]=1;
	}
	checkk();
	int k=n;
	for(int i=2;i*i<=n;i++){
		if(pri[i]||(!a[i]))continue;
		int cnt=0;
		while(!(k%i)){
			k=k/i;
			cnt++;
		}
		a[i]=cnt;
	}
	init();
	int kkk=n;
	for(int i=2;i*i<=n;i++){
		if(!a[i]||pri[i])continue;
		for(int j=1;j<=a[i];j++)kkk/=i;
		ans=ans*c(m+a[i]-1,m-1)%mod;
	}
	if(kkk!=1)ans=ans*m%mod;
	cout<<ans%mod; 
}
```

---

## 作者：_zzzzzzy_ (赞：0)

## 思路
我们对于这类的题有一个经典的套路，就是通过分解然后对于他的质因子进行组合，最后变成我们要求的数。

我们把题目中的 $m$ 分解成了 $\prod_{i=1}^{k}p_i^{c_i}$，最后我们考虑怎么组合，我们可以把每一个质因子的个数看作球的个数，那么 $n$ 就是盒子的个数，可以分析出这个模型是球相同盒不同可以有空盒的情况，这个的模型的公式是 $C_{n+m-1}^{m-1}$，下面简单证明一下。

我们先看另一个模型，球相同盒不同盒不能空，可以用插板法简单得出是在 $n$ 个球中插 $m-1$ 个板子分成 $m$ 份，第 $i$ 份的球放在第 $i$ 个盒子里面，就可以推出公式 $C_{n-1}^{m-1}$。

我们在回过来看球相同盒不同可以有空盒，我们可以把球的个数增加 $m$ 个，表示在每个盒子里面先放一个，这样就保证了可以空盒，所以最后的公式是 $C_{n-1}^{n+m-1}$。

因为我们有 $k$ 个质因子，根据乘法原理相乘可以轻松得出答案。

## 代码
```cpp
const int maxn = 100;
int c[maxn], tot;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	int n, m;
	cin >> n >> m;
	for (int i = 2; i * i <= m; i++) {
		if (m % i == 0) {
			++tot;
		}
		while (m % i == 0) {
			c[tot]++;
			m /= i;
		}
	}
	if (m != 1) {
		c[++tot]++;
	}
	Z ans = 1;
	for (int i = 1; i <= tot; i++) {
		ans = ans * comb.C(n + c[i] - 1, n - 1);
	}
	cout << ans << "\n";
	return 0;
}

```

---

## 作者：Siteyava_145 (赞：0)

题意：一个序列 $a$，长度为 $n$，且 $\prod a_i=m$。求这样的 $a$ 序列有多少个。

先把 $m$ 分解质因数：$m={p_1}^{c_1}\times {p_2}^{c_2} ...... \times {p_i}^{c_i}$，其中 $i$ 为互不相同的质因数的个数。

再将这些数分配进 $n$ 个数里，每一次 $c_i$ 个 $p_i$ 分配进 $n$ 个数，共有 $C_{n+c_i-1}^{n-1}$ 种方法。（隔板法，相当于 $c_i$ 个球放进 $n$ 个盒子里）

注意这里组合数较大，需要取模。除法取模要乘它的逆元。

代码：

```
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll fac[400005],p=1000000007;
ll zys[400005];
ll fp(ll a,ll b,ll c){
	ll ans=1;
	while(b){
		if(b&1){
			ans=ans*a%c;
		}
		a=a*a%c;
		b>>=1; 
	}
	return ans;
} 
ll C(ll n,ll m){
	if(m>n)return 0;
	return (fac[n]*fp(fac[m],p-2,p)%p*fp(fac[n-m],p-2,p)%p)%p;
}
ll lucas(ll n,ll m){//......n,m很大时的组合数求法
	if(m==0)return 1;
	else return C(n%p,m%p)*lucas(n/p,m/p)%p;
}
int main(){
	ll n,m,cnt=0,as=2;
	cin>>n>>m;
	fac[0]=1;//预处理阶乘
	for(int i=1;i<=400000;i++)fac[i]=(fac[i-1]*i)%p;
	for(int i=2;i<=sqrt(m);i++){//分解质因数
		int ci=0;
		while(m%i==0){
			m/=i;
			ci++;
		}
		if(ci!=0)zys[++cnt]=ci;//pi^ci
		as+=ci;
	}
	if(m!=1){zys[++cnt]=1;as++;}
    
	ll ans=1;
	for(int i=1;i<=cnt;i++){
		ans*=lucas(n+zys[i]-1,n-1)%p;
		ans%=p;
	}
	cout<<ans<<endl;
}
```


---

