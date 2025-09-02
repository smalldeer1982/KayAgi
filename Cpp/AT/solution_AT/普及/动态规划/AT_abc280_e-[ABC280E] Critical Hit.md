# [ABC280E] Critical Hit

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc280/tasks/abc280_e

最初、体力が $ N $ であるモンスターが $ 1 $ 体います。  
 高橋君はモンスターに対し、モンスターの体力が $ 1 $ 以上残っている限り繰り返し攻撃を行います。

高橋君は $ 1 $ 回の攻撃で、$ \frac{P}{100} $ の確率でモンスターの体力を $ 2 $ 減らし、 $ 1-\frac{P}{100} $ の確率でモンスターの体力を $ 1 $ 減らします。

モンスターの体力が $ 0 $ 以下になるまでに行う攻撃回数の期待値を $ \text{mod\ }\ 998244353 $ で出力してください（注記参照）。

## 说明/提示

### 注記

求める期待値は必ず有限値かつ有理数となることが証明できます。また、この問題の制約下では、その値を互いに素な $ 2 $ つの整数 $ P $, $ Q $ を用いて $ \frac{P}{Q} $ と表したとき、$ R\ \times\ Q\ \equiv\ P\pmod{998244353} $ かつ $ 0\ \leq\ R\ \lt\ 998244353 $ を満たす整数 $ R $ がただ一つ存在することが証明できます。この $ R $ を出力してください。

### 制約

- $ 1\ \leq\ N\ \leq\ 2\times\ 10^5 $
- $ 0\ \leq\ P\ \leq\ 100 $
- 入力は全て整数
 
### Sample Explanation 1

高橋君は $ 1 $ 回の攻撃で、 $ \frac{10}{100}=\frac{1}{10} $ の確率でモンスターの体力を $ 2 $ 減らし、 $ 1-\frac{10}{100}=\frac{9}{10} $ の確率でモンスターの体力を $ 1 $ 減らします。 - 最初、モンスターの体力は $ 3 $ です。 - $ 1 $ 回目の攻撃の後、$ \frac{9}{10} $の確率でモンスターの体力は $ 2 $、$ \frac{1}{10} $の確率でモンスターの体力は $ 1 $ となります。 - $ 2 $ 回目の攻撃の後、$ \frac{81}{100} $の確率でモンスターの体力は $ 1 $、$ \frac{18}{100} $ の確率でモンスターの体力は $ 0 $、$ \frac{1}{100} $ の確率でモンスターの体力は $ -1 $ となります。 $ \frac{18}{100}+\frac{1}{100}=\frac{19}{100} $ の確率で体力は $ 0 $ 以下となり、高橋君は $ 2 $ 回で攻撃をやめます。 - $ 2 $ 回目の攻撃の後で体力が $ 1 $ 残っている場合、$ 3 $ 回目の攻撃の後でモンスターの体力は必ず $ 0 $ 以下となり、高橋君は $ 3 $ 回で攻撃をやめます。 よって、期待値は $ 2\times\ \frac{19}{100}+3\times\left(1-\frac{19}{100}\right)=\frac{281}{100} $ となります。$ 229596204\ \times\ 100\ \equiv\ 281\pmod{998244353} $ であるため、$ 229596204 $ を出力します。

### Sample Explanation 2

高橋君は $ 1 $ 回の攻撃で、つねにモンスターの体力を $ 2 $ 減らします。 $ 2 $ 回目の攻撃が終わった時点では体力が $ 5-2\times\ 2=1 $ 残っているため、$ 3 $ 回目の攻撃を行う必要があります。

## 样例 #1

### 输入

```
3 10```

### 输出

```
229596204```

## 样例 #2

### 输入

```
5 100```

### 输出

```
3```

## 样例 #3

### 输入

```
280 59```

### 输出

```
567484387```

# 题解

## 作者：liangbowen (赞：16)

## 思路

容易想到，设 $dp_i$ 表示将怪物打剩下 $i$ 滴血时，期望攻击次数。

$p$ 是百分数，所以实际概率是 $\dfrac{p}{100}$。以下的 $p$ 直接表示了 $\dfrac{p}{100}$。

那么显然有转移方程：

$$dp_i = \begin{cases}
0 & i \ge n \\
dp_{i  + 1} \times p + dp_{i + 2} \times (1- p) + 1 & \text{otherwise}
\end{cases}$$

答案即为 $dp_{0}$。

## 代码

```cpp
const int mod = 998244353;
ll qpow(ll x, int y = mod - 2) //费马小定理求逆元
{
    ll ans = 1;
    while (y)
    {
        if (y & 1) ans = (1ll * ans * x) % mod;
        x = (1ll * x * x) % mod;
        y >>= 1;
    }
    return ans;
}
ll dp[200005];
void solve()
{
	int n, p;
	scanf("%d%d", &n, &p);
	p = 1ll * p * qpow(100) % mod; //p = p / 100
 
	dp[n] = 0;
	for (int i = n - 1; i >= 0; i--)
		dp[i] = (dp[i + 1] * (mod + 1 - p) % mod + dp[i + 2] * p % mod) % mod + 1;
	cout << dp[0] << '\n';
}
```

希望能帮助到大家！

---

## 作者：泥土笨笨 (赞：11)

# 题意简述

有一只初始 $N$ 滴血的怪物。你去攻击它一次，有 $P/100$ 的概率伤害它两滴血，有 $1-p/100$ 的概率伤害它一滴血。让怪物血量到 $0$ 或者 $0$ 以下的时候就死了，问你打死他的攻击次数的期望是多少。

# 期望DP

数学期望是试验中每次可能结果的概率乘以其结果的总和。

我们采取倒推的方法，定义 $f(i)$ 表示打死一只血量为 $i$ 的怪所需要的攻击次数的期望。边界条件显然有 $f(0)=0, f(1)=1$，即生命值为 $0$ 的怪是不需要攻击的。生命值为 $1$ 的怪，打一下，不管是伤害为 $1$ 还是 $2$ ，它都会死。

对于 $i \gt 2$ 的情况，攻击一次会出现两种可能的结果，分别是掉一滴血和两滴血，可以用这两种情况发生的概率，乘以掉一滴血和两滴血以后，继续需要攻击的期望次数即可。所以有状态转移方程：

$$f(i)=f(i-2) \times p / 100 + f(i-1) \times (1-p /100) + 1$$

这样从 $i=2$ 推到 $n$ 就行了，$f(n)$就是答案。

# 分数取模

本题中为了避免浮点数计算丢失精度，要求答案模$998244353$。分数取模的问题，我认为能接触期望DP的同学已经会了。如果不了解，可以移步乘法逆元，分数取模的相关题目题解区。比如洛谷《P2613 【模板】有理数取余》

# 代码

```cpp
#include <iostream>

using namespace std;
typedef long long ll;
const ll MAXN = 2e5 + 5;
const ll MOD = 998244353;

//快速幂
ll fastPow(ll a, ll b) {
    ll base = a % MOD;
    ll r = 1;
    while (b) {
        if (b & 2) {
            r = r * base % MOD;
        }
        base = base * base % MOD;
        b >>= 1;
    }
    return r;
}

//费马小定理求逆元
ll inv(ll x) {
    return fastPow(x, MOD - 2);
}

ll n, p, f[MAXN];//f[i]表示生命值i的敌人需要打多少下的期望

int main() {
    cin >> n >> p;
    ll hit2 = p * inv(100) % MOD;//一次打两滴血的概率（取模后）
    ll hit1 = (100 - p) * inv(100) % MOD;//一次打一滴血的概率（取模后）
    f[0] = 0;
    f[1] = 1;
    for (ll i = 2; i <= n; ++i) {
        f[i] = (hit2 * f[i - 2] % MOD + hit1 * f[i - 1] % MOD + 1) % MOD;
    }
    cout << f[n] << endl;
    return 0;
}
```


---

## 作者：FFTotoro (赞：3)

## 前言

第一次赛时 $10$ 分钟内切掉一道 E，感动。

## 解法

设 $f_i$ 为把怪物的血量打到**正好**为 $i$ 的期望次数。

很显然，边界条件 $f_N=0$；

由题意，可知每次攻击有 $\frac{P}{100}$ 的概率血量 $-2$，即 $f_i=f_{i+2}+1$；有 $1-\frac{P}{100}$ 的概率血量 $-1$，即 $f_i=f_{i+1}+1$；

整理得 $f_i=\frac{P(f_{i+2}+1)}{100}+\frac{(100-P)(f_{i+1}+1)}{100}(1\le i<N)$。

特别地，因为血量小于等于 $0$ 即算胜利，所以定义 $f_0$ 为**血量小于等于** $0$ 的期望次数，易得 $f_0=f_1+1$。

除法用乘法逆元实现即可。

放代码：

```cpp
#include<bits/stdc++.h>
#define int long long // 记得开 long long
using namespace std;
const int mod=998244353;
main(){
  ios::sync_with_stdio(false);
  int n,p,inv=828542813; cin>>n>>p; // inv 为 mod 998244353 意义下 100 的逆元
  vector<int> a(n+1); a[n]=0;
  for(int i=n-1;~i;i--) // 往前倒推，注意处理边界情况
    a[i]=((i?(p*inv%mod*(i==n-1?0:a[i+2]+1))+((100-p)*inv%mod*(a[i+1]+1)):a[1]+1)%mod);
  cout<<a[0]<<endl;
  return 0;
}

---

## 作者：Moyou (赞：2)

# 题意

有一个血量为 $n$ 的怪，你每一次攻击有 $\dfrac{p}{100}$ 的概率暴击造成 $2$ 点伤害，$1-\dfrac{p}{100}$ 的概率造成 $1$ 点伤害，怪血量 $\leq 0$ 时视作死亡。

求怪死亡前攻击次数的期望值，答案对 $998244353$ 取模。


# 思路

期望 dp。

**状态表示：** $f[i]$ 表示怪剩余血量为 $i$ 时的期望攻击次数。

**状态转移：** 考虑递推，血量为 $i$ 时攻击一次有且仅有两种情况：

1. 打出了暴击，造成 $2$ 点伤害，血量变为 $i - 2$ ；
2. 没打出暴击，造成 $1$ 点伤害，血量变为 $i - 1$。

当前状态可以从两个子状态转移而来，即为两种情况的期望之和 $ + 1$，表示攻击了一次，两种情况期望分别为：

1. $f[i - 2] \times \dfrac{p}{100}$，打出暴击的概率 $\times$ 打出暴击的期望；
2. $f[i - 1] \times (1- \dfrac{p}{100})$，没打出暴击的概率 $\times$ 没打出暴击的期望。

**初始情况：** $f[1] = 1$，血量为 $1$ 时，只有攻击一次直接结束游戏的情况，期望为 $1$。

**最终答案：** $f[n]$，血量为 $n$ 的时候，期望攻击次数。

# 代码

注意为了避免对浮点数取模，我们在一开始对 $p$ 求 $100$ 的逆元，这里用快速幂实现。


```cpp
// Author: Moyou
// Date: 2022-12-04 13:42:21

#include <iostream>
using namespace std;
typedef long long LL;

const int N = 2e5 + 10, mod = 998244353;

LL f[N]; // dp 状态数组

LL qmi(LL a, LL b, LL p) // 快速幂板子
{
    LL res = 1 % p;
    while (b)
    {
        if (b & 1)
            res = (res * a) % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}

int main()
{
    LL n, p;
    cin >> n >> p;
    p = p * qmi(100, mod - 2, mod) % mod; // 快速幂求逆元
    f[1] = 1; // 初始情况
    for (int i = 2; i <= n; i++)
    {
        f[i] = (f[i - 2] * p + f[i - 1] * (1 - p + mod) % mod + 1) % mod;
    }
    cout << f[n] << endl;

    return 0;
}
```

---

## 作者：VanishmentThisWorld (赞：1)

算期望，考虑 dp。

设 $f_i$ 表示打败血量为 $i$ 怪兽的期望次数，$p_1$ 表示打出一点伤害的概率，$p_2$ 同理。

有 $f_i = f_{i-1} \times p_1 + f_{i-2} \times p_2 + 1$。

边界 $f_0=0,f_1=1$，注意取模。

```
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5+5,mod=998244353;
int n,p1,p2,f[N];
int qpow(int x,int y=mod-2){
  int res=1;
  while(y){
    if(y&1)res=res*x%mod;
    x=x*x%mod;y>>=1;
  }
  return res;
}
signed main(){
  scanf("%lld%lld",&n,&p2);p2=p2*qpow(100)%mod;p1=(1+mod-p2)%mod;
  f[0]=0;f[1]=1;
  for(int i=2;i<=n;i++){
    f[i]=(f[i-1]*p1%mod+f[i-2]*p2%mod+1)%mod;
  }
  printf("%lld\n",f[n]);
  return 0;
}
```

---

## 作者：hejianxing (赞：1)

# 题目大意

有一生命值为 $N$ 的怪兽，你对其攻击一次，有 $1-\frac P{100}$ 的概率使其扣 $1$ 点生命值，有 $\frac P{100}$ 的概率使其扣 $2$ 点生命值。求击杀其（指其生命值不大于 $0$）的期望攻击次数（$\bmod 998244353$）.

# 分析

~~首先你需要了解期望 dp~~

显然，这是一个期望 dp 的板题。

设 $f[i]$ 为怪兽生命值为 $i$ 时需要击杀的期望攻击次数，明显地，$f[0]=0$.

$f[1]=1$，因为当其生命值为 $1$ 时，只要进行 $1$ 次攻击，无论是扣 $1$ 点还是 $2$ 点生命值，怪兽都会死亡。

由于有 $1-\frac P{100}$ 的概率扣 $1$ 点生命值，那么有 $1-\frac P{100}$ 的概率由 $f[i-1]$ 转移而来，也就是当怪兽生命值为 $i$ 时，有 $1-\frac P{100}$ 的概率有如下结果：攻击 $1$ 次扣 $1$ 点生命值，此时再攻击 $f[i-1]$ 次就能杀死怪兽。

同理，当怪兽生命值为 $i$ 时，有 $\frac P{100}$ 的概率有如下结果：攻击 $1$ 次扣 $2$ 点生命值，此时再攻击 $f[i-2]$ 次就能杀死怪兽。

那么有

$$f[i]=(1-\frac P{100})\times (f[i-1]+1)+\frac P{100}\times (f[i-2]+1)$$

最终输出 $f[N]$.
 
注意这个式子是在 $\bmod998244353$ 意义下的，所以对于分数 $1-\frac P{100} = \frac{100-P}{100}$ 及 $\frac{P}{100}$ 都要在模意义下运算。


# code

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
const int N = 200005;
const LL mod = 998244353;
int n;
LL p, f[N];
LL qpow(LL x, LL y) {
    LL sum = 1;
    while (y) {
        if (y & 1) sum = sum * x % mod;
        x = x * x % mod, y >>= 1;
    }
    return sum;
}
int main() {
    scanf("%d%lld", &n, &p);
    f[1] = 1;
    for (int i = 2; i <= n; i++)
    	f[i] = (p * qpow(100, mod - 2) % mod * (f[i - 2] + 1) % mod + (100 - p) * qpow(100, mod - 2) % mod * (f[i - 1] + 1) % mod) % mod;
    printf("%lld", f[n]);
    return 0;
}
```
若模数为 $\bmod$，

时间复杂度为 $O(N\log\bmod)$.

---

## 作者：Fire_flame (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc280_e)

## 前置知识

费马小定理以及证明：

**命题：**

若 $p$ 为质数时，$a^{p-1} ≡ 1\pmod p$。

**证明：**

首先，我们把这个式子做一个简单变换得：$a^{p-1}\times a ≡ a\pmod p$。

因为 $a≡a\pmod p$ 恒成立，所以 $a^{p-1} \bmod p$ 为 $1$ 时费马小定理才成立，又因为 $p$ 是质数，所以 $φ(p)=p-1 $。

根据欧拉定理：若 $(a,p)=1$ 则 $a^{p-1}≡ 1\pmod p$ 成立。那么对于 $(a,p)≠1$，因为$p$是质数，所以 $a$ 一定是 $p$ 的倍数,那么 $a^p≡a≡0\pmod p$。

综上所述，费马小定理成立，其实它算是欧拉定理的一个特例。

# $\mathtt{Solution}$

假设最终的期望值为 $ans\%$。

令 $ans=1$ 时：

$$x\times 100≡1 \pmod {998244353}$$

根据费马小定理，$100^{998244352} ≡ 1\pmod p$。

所以原式可以转化为 $x\times 100≡100^{998244352} \pmod {998244353}$

所以 $x≡100^{998244351} \pmod {998244353}$

用快速幂解得 $x=828542813$。

用记忆化搜索可以解出 $ans$ 的值，就搞定了。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MAXN=2e5+5,MOD=998244353;
int n,p,k,f[MAXN];
int dfs(int x){
	if(x<=0)return 0;
	if(f[x]!=-1)return f[x];
	int s=dfs(x-2)*p%MOD*k%MOD;
	s+=dfs(x-1)*(100-p)%MOD*k%MOD;
	return f[x]=++s%MOD;
}
signed main(){
	scanf("%lld%lld",&n,&p);
	k=828542813;
	memset(f,-1,sizeof(f));
	printf("%lld",dfs(n));
	return 0;
}

```


---

## 作者：SkyLines (赞：0)

### 题目大意

你要打死一个 $n$ 滴血的怪物，对于每次攻击，有 $P\%$ 的概率让怪物失去 $2$ 滴血，有 $(100-P)\%$ 的概率让怪物失去 $1$ 滴血。如果怪物的血量 $\le0$，怪物就死了。输出攻击次数的期望对 $998244353$ 取模的值。

### 思路

设 $dp_i$ 表示怪物打到 $i$ 滴血时的期望攻击次数。

不难得到：$dp_0=0$，$dp_1=1$，当 $i>1$ 时，有 $dp_i=dp_{i-2} \times p\%+dp_{i-1} \times (100-p)\%+1$。

答案就是 $dp_n$。

对于分数取模，见 [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)

这里给出代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
char s[10005], s2[10005];
int q, p, mod = 19260817, maxn, x, y, z;
void gcd(int a, int b)
{
	if(b == 0)
	{
		x = 1;
		y = 0;
		z = a;
	}
	else
	{
		gcd(b, a % b);
		int tmp = x;
		x = y;
		y = tmp - a / b * y;
	}
	return ;
}
signed main()
{
	scanf("%s %s", s, s2);
	for(int i = 0; i < strlen(s); i++) q = (q * 10 + (s[i] - '0')) % mod;
	for(int i = 0; i < strlen(s2); i++) p = (p * 10 + (s2[i] - '0')) % mod;
	gcd(p, mod);
	if(q % z != 0) printf("Angry!");
	else printf("%lld", (q * ((x + mod) % mod)) % mod);
	return 0;
}
```

对于此题，可以用费马小定理做，$a$ 的逆元（对 $p$ 取模）就是 $a^{p-2} \bmod p$，其中 $a^{p-2}$ 可以用快速幂。一个数除以 $a$ 就相当于乘 $a$ 的逆元。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n, p, mod = 998244353, aa, bb, dp[200005];
int qmi(int a, int b)
{
	int ans = 1;
	while(b)
	{
		if(b & 1) ans = ans * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return ans;
}
int inv(int a)
{
	return qmi(a, mod - 2);
}
signed main()
{
	scanf("%lld %lld", &n, &p);
	dp[0] = 0;
	dp[1] = 1;
	aa = p * inv(100) % mod;
	bb = (100 - p) * inv(100) % mod;
	for(int i = 2; i <= n; i++) dp[i] = (dp[i - 1] * bb + dp[i - 2] * aa + 1) % mod;
	printf("%lld", dp[n]);
	return 0;
}
```

---

## 作者：Demons_Killer (赞：0)

# 解题思路：
考虑动态规划。

由于这里取余的是实数，我们需要用到快速幂来求逆元。刚开始把 $p$ 的概率的取余算出来，随后就可以枚举状态。$f_{i}$ 表示血量为 $i$ 时的期望值。可得状态转移方程为 $f_{i}=f_{j+1}\times p+f_{j+2}\times (1-p) +1$。

最后的结果为 $f_{0}$。

# code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int p=998244353,N=2e5+10;
int f[N],n,m;
int ksm(int a,int b,int c){
    int res=1;
    while(b>0){
        if(b%2==1){
            res=a*res%c;
        }
        b/=2;
        a=a*a%c;
    }
    return res;
}
signed main(){
	cin>>n>>m;
	m=1ll*m*ksm(100,p-2,p)%p;
	f[n]=0;
	for(int i=n-1;i>=0;i--){
		f[i]=(f[i+1]*(p+1-m)%p+f[i+2]*m%p)%p+1;
	}
	cout<<f[0];
	return 0;
}
```

---

## 作者：Zhao_daodao (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/AT_abc280_e)
# 题目分析
为了简化分析，以下设 `double` 类型 $p=P/100.0$。

考虑 `dp`。
### 状态
对于 $dp_{i}$，代表怪物剩余 $i$ 滴血时的期望攻击次数。
### 转移方程
因为一次攻击最多打掉怪物 `2` 滴血，所以可以在 $O(1)$ 的时间内转移。

转移方程如下。

$dp_{i}=\left\{\begin{matrix} 
  0 &i=0 \\  
  1 &i=1 \\
  dp_{i-2}\times p+dp_{i-1}\times(1-p)+1& otherwise
\end{matrix}\right. $

### 答案
$ans=dp_{n}$。
### Tips
只需要对 $p$ 用费马小定理逆元就可以解决有理数整除的问题。

---

## 作者：_Kamisato_Ayaka_ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc280_e)

# 1.题目大意

有一只 $ n $ 滴血的怪物，你有 $ P\% $ 的概率打掉它两滴血，有 $ (100-P)\% $ 打掉它一滴血，如果它的血量小于零，他就死了。输出攻击次数的期 998244353 取模的值。

# 2.解题思路

这道题是一道典型的概率与期望的 $ dp $，需要用到有理数取模。用 $ f_i $ 表示打死一只怪物攻击次数的期望，所以可以得到 $ dp $ 方程如下：

$ f_i = f_{i-1} \times P\% + f_{i-2} \times (100-P)\% $ 

这里有理数取模我用到了费马小定理求逆元。

# 3.AC代码

```cpp
#include<bits/stdc++.h>
#define int long long//记得开longlong 
using namespace std;
const int mod = 998244353;
int n,p,f[400005];
inline int read(){//快读 
	int res=0,f=1;
	char ch=getchar();
	while(ch<'0' || ch>'9'){
		if(ch=='-') f=-1;
		ch=getchar();
	}
	while(ch>='0' && ch<='9'){
		res=res*10+ch-'0';
		res%=mod;
		ch=getchar();
	}
	return res*f;
} 
int qpow(int x,int q){//二进制快速幂 
	int k=1;
	x%=mod;
	while(q>0){	
		if(q&1) k=k*x%mod;
		x=x*x%mod;
		q>>=1; 
	}
	return k;
}
int inv(int x){//求逆元 
	return qpow(x,mod-2);
}
signed main(){
	n=read(),p=read();
	int p1=p*inv(100)%mod,p2=(100-p)*inv(100)%mod;//概率 
	f[0]=0;
	f[1]=1;//初始化 
	for(int i=2;i<=n;i++)
		f[i]=(f[i-1]*p2%mod+f[i-2]*p1%mod+1)%mod;//开始dp(注意取模)
	cout<<f[n]<<endl;//输出结果 
	return 0;
} 
```


---

## 作者：zzx0102 (赞：0)

首先，求逆元可以使用费马小定理。

设 $\dfrac{a}{b}\equiv x\pmod p$

则根据费马小定理，$b^{p-1}\equiv 1\pmod p$，

所以 $\dfrac{a}{b}\times b^{p-1}\equiv 1x\pmod p$

化简，得 $\dfrac{a}{b}\equiv a\times b^{p-2}\pmod p$。

详见 [P2613](/problem/P2613)

接下来，考虑设状态。

令 $dp_i$ 表示打掉 $i$ 的血的期望步数。

那么 $dp_i$ 可以分类讨论，由 $i-1$ 到 $i$ 的可能性是 $p\%$，由 $i-2$ 到 $i$ 的可能性是 $(100-p)\%$。

那么 $dp_i=dp_{i-1}\times p\%+dp_{i-2}\times (100-p)\%$。

注意初始化，$dp_0=0,dp_1=1$。

为了计算逆元，$dp$ 数组要边转移变求逆元。

剩下的代码就很没用必要了吧，都分析到这了。

---

## 作者：c20231020 (赞：0)

### 题目链接
[luogu](https://www.luogu.com.cn/problem/AT_abc280_e)

[atcoder](https://atcoder.jp/contests/abc280/tasks/abc280_e)

### 题目大意

最初，有 $1$ 个生命值为 $N$ 的怪物。

只要怪物剩余的生命值不低于 $1$，高桥就会反复攻击它。

在高桥的 $1$ 次攻击中，有 $\frac{P}{100}$ 的概率怪物的生命值减少 $2$，$1-\frac{P}{100}$ 的概率怪物的生命值减少 $1$.

在怪物的生命值低于 $0$ 之前，输出攻击次数的期望值 $\bmod 998244353$（见注释）。

（这就是我的翻译）

### 思路

一道期望 dp 板子题。

设 $dp_i$ 表示怪物当前生命值为 $i$ 时的期望攻击次数。则 dp 转移方程如下：

$$
dp_i=\frac{P}{100}(dp_{i-2}+1)+(1-\frac{P}{100})(dp_{i-1}+1)
$$

前半段表示攻击伤害为 $2$ 时的期望次数，后半段表示攻击伤害为 $1$ 时的期望次数。

#### code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define mod 998244353
ll qpow(ll a,ll b){//快速幂
	ll res=1;
	for(;b;(a*=a)%=mod,b>>=1)if(b&1)(res*=a)%=mod;
	return res;
}
ll n,p,dp[200010];
int main(){
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>n>>p;
	for(int i=1;i<=n;++i){
		int a=p,b=100,c=__gcd(a,b);
		a/=c;b/=c;//处理逆元
		dp[i]+=(dp[max(0,i-2)]+1)*a%mod*qpow(b,mod-2)%mod;//注意边界条件
		a=100-p,b=100,c=__gcd(a,b);
		a/=c;b/=c;
		dp[i]+=(dp[i-1]+1)*a%mod*qpow(b,mod-2)%mod;
		dp[i]%=mod;
	}
	//其实逆元的处理完全可以预处理，但我在比赛时没想这么多，反正代码可过
	cout<<dp[n]<<'\n';
	return 0;
}
```
---
End.

---

