# Good Trip

## 题目描述

There are $ n $ children in a class, $ m $ pairs among them are friends. The $ i $ -th pair who are friends have a friendship value of $ f_i $ .

The teacher has to go for $ k $ excursions, and for each of the excursions she chooses a pair of children randomly, equiprobably and independently. If a pair of children who are friends is chosen, their friendship value increases by $ 1 $ for all subsequent excursions (the teacher can choose a pair of children more than once). The friendship value of a pair who are not friends is considered $ 0 $ , and it does not change for subsequent excursions.

Find the expected value of the sum of friendship values of all $ k $ pairs chosen for the excursions (at the time of being chosen). It can be shown that this answer can always be expressed as a fraction $ \dfrac{p}{q} $ where $ p $ and $ q $ are coprime integers. Calculate $ p\cdot q^{-1} \bmod (10^9+7) $ .

## 说明/提示

For the first test case, there are no pairs of friends, so the friendship value of all pairs is $ 0 $ and stays $ 0 $ for subsequent rounds, hence the friendship value for all excursions is $ 0 $ .

For the second test case, there is only one pair possible $ (1, 2) $ and its friendship value is initially $ 1 $ , so each turn they are picked and their friendship value increases by $ 1 $ . Therefore, the total sum is $ 1+2+3+\ldots+10 = 55 $ .

For the third test case, the final answer is $ \frac{7}{9} = 777\,777\,784\bmod (10^9+7) $ .

## 样例 #1

### 输入

```
4
100 0 24
2 1 10
1 2 1
3 1 2
2 1 1
5 2 4
1 2 25
3 2 24```

### 输出

```
0
55
777777784
40000020```

# 题解

## 作者：Diaоsi (赞：18)

[Good Trip](https://www.luogu.com.cn/problem/CF1925D)

提供一个符合人类直觉的做法。

设 $p=\dfrac{2}{n(n-1)}$，表示每一对人被选中的概率。记 $s$ 表示友谊值的总和，初始时 $s=\sum\limits_{i=1}^m f_i$。

每一轮选择时，选择到的友谊值的期望为 $p\cdot s$，友谊值总和增加的期望为 $p\cdot m$。

所以只需要重复以下流程即可：

$$ans\leftarrow ans+p\cdot s$$

$$s\leftarrow s+p\cdot m$$

时间复杂度 $\mathcal{O}(n)$，代码十分甚至九分好写。

```Code:```
```cpp
void solve(){
	ans=sum=0;
	scanf("%lld%lld%lld",&n,&m,&k);
	p=n*(n-1)%lpw;p=2*qpow(p,lpw-2)%lpw;
	for(ll i=1;i<=m;i++){
		scanf("%lld%lld%lld",&a,&b,&f);
		sum=(sum+f)%lpw;
	}
	for(int i=1;i<=k;i++)
		ans=(ans+sum*p%lpw)%lpw,
		sum=(sum+m*p%lpw)%lpw;
	printf("%lld\n",ans);
}
```


---

## 作者：Svemit (赞：11)

# Solution

发现我们并不关下每一组人到底是哪些人。

不妨从 dp 的角度去考虑这个问题。

设 $p = 2 / (n \times (n - 1))$，$dp_i$ 为选了 $i$ 组人后期望得到的友谊值。

第 $i$ 次选人，有 $1 - p \times m$ 的概率选中不是朋友的一组人。

设 $x_j$ 为此时第 $j$ 组的期望友谊值。

可以得到方程：

$$ dp_i = dp_{i - 1} + (1 - p \times m) \times 0 + \sum_{j =  1}^{m} p \times x_j $$

现在考虑怎么求出 $x_j$。

假设一组初始友谊值为 $t$, $f_i$ 表示经过 $i$ 次之后友谊值的期望。

对于一组好朋友，每次有 $p$ 的概率被选中，友谊值增加 1，有 $1 - p$ 的概率不被选中，友谊值不变，于是得到：

$$ f_i = f_{i - 1} + p \times 1 + (1 - p) \times 0$$

不难发现 $f_i = t + i \times p$。

即 $x_j = f_j + (i - 1) \times p$。此时 $f_j$ 的含义为题目所给。

得到：

$$dp_i = dp_{i - 1} + p \times \sum_{j = 1}^{m} (f_j + (i - 1) \times p)$$

$$dp_i = dp_{i - 1} + p \times (\sum_{j = 1}^{m} f_j + m \times (i - 1) \times p)$$

令 $s = \sum_{i = 1}^{m} f_i $。

$$dp_i = dp_{i - 1} + p \times (s + m \times (i - 1) \times p)$$

直接做即可，时间复杂度 $O(n)$。

```cpp
void solve() {
	LL n, m, k;
	cin >> n >> m >> k;
	Z s = 0, p = (Z)2 / (n * (n - 1));
	for(int i = 0; i < m; i ++) {
		int a, b;
		Z c;
		cin >> a >> b >> c;
		s += c;
	}
	Z f = 0, g = 0;
	for(int i = 0; i < k; i ++) {
		f = g + p * (s + m * (Z)i * p);
		g = f;
	}
	cout << f << '\n';
}
```

---

## 作者：Creeper_l (赞：5)

考虑分别计算 $p$ 和 $q$。

按照期望的定义，$q$ 应该等于方案的总数，也就是 $s^k$，其中 $s$ 表示一共有多少个不同的组。

考虑如何求 $p$，我们先只计算第 $i$ 组对 $p$ 的贡献。如果第 $i$ 组一共被选了 $1$ 次，那么贡献为：

$$g=f_i \times C_{k}^{1}\times (s-1)^{k-1}$$

这个式子中的三个值分别表示：这个组的价值，哪 $1$ 次选了这个组，另外 $k - 1$ 次选了哪些组。将上式推广到选 $j$ 次，那么有：

$$g=(f_{i}+(f_{i}+1)+\dots+(f_{i}+j-1)) \times C_{k}^{j}\times (s-1)^{k-j}$$

前面的等差数列可以在线地去维护（第 $w$ 次加上 $f_i+w-1$），后面的可以用组合数 & 快速幂求解。

会发现每组的贡献的后一段都和上式一样，只有 $f$ 的值在变化。所以我们可以提公因式，把 $f_i$ 换成 $\sum f_i$ 即可。

会发现 $a_i$ 和 $b_i$ 可以忽略，因为题目对每一次选的人没有任何限制。

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN = 4e6 + 10;
const int mod = 1e9 + 7;
inline int Qpow(int x,int k)
{
	if(x == 0 || k < 0) return 0;
	int res = 1;x = x % mod;
	for(;k;k >>= 1)
	{
		if(k & 1) res = (res * x) % mod;
		x = (x * x) % mod;
	} return res;
}
int inv[MAXN],fac[MAXN],invfac[MAXN];
inline int C(int n,int m)
{return (fac[n] * invfac[n - m] % mod) * invfac[m] % mod;}
int t,n,m,k,a[MAXN],b[MAXN],c[MAXN],p,q;
signed main()
{
	cin >> t;
	inv[0] = fac[0] = invfac[0] = 1;
	inv[1] = fac[1] = invfac[1] = 1;
	for(int i = 2;i <= 400000;i++)
	{
		inv[i] = (inv[mod % i] * (mod - mod / i)) % mod;
		fac[i] = (fac[i - 1] * i) % mod;
		invfac[i] = (invfac[i - 1] * inv[i]) % mod; 
	}
	while(t--)
	{
		cin >> n >> m >> k;
		p = 0,q = n * (n - 1) / 2;
		int sum = 0,s = 0;
		for(int i = 1;i <= m;i++)
		{
			cin >> a[i] >> b[i] >> c[i];
			sum = (sum + c[i]) % mod;
		}
		if(n == 2)
		{
			if(sum == 0) p = 0;
			else for(int i = 1;i <= k;i++) 
				p = (p + sum) % mod,sum = (sum + 1) % mod;
		}
		else for(int i = 1;i <= k;i++)
		{
			s = (s + (sum + (i - 1) * m)) % mod;
			int f = (s * C(k,i) % mod) * Qpow(q - 1,k - i) % mod;
			p = (p + f) % mod;
		}	
		q = Qpow(q,k);
		cout << (p * Qpow(q,mod - 2)) % mod << endl;
	} 
	return 0;
} 
```




---

## 作者：Iniaugoty (赞：4)

数学题。

老师的每一次选择有 $ \dfrac {n(n - 1)} {2} $ 种选法，选了 $ k $ 次，所以总情况数是 $ (\dfrac {n(n - 1)} {2}) ^ k $。枚举每一种情况是不理智的。~~废话~~。

我们注意到，每次选择一对人，对总和的贡献，**与此前何时被选择无关，与被选择的次数有关**。

所以按时间 DP 是不行的。考虑将这 $ (\dfrac {n(n - 1)} {2}) ^ k $ 种情况挂到每一对人身上。

- 如果 $ u, v $ 不是朋友，显然不管如何他们的贡献都是 $ 0 $。

- 如果 $ u, v $ 是朋友，设其初始友谊值为 $ f $。考虑对于每个 $ 0 \le i \le k $，计算恰好被选择 $ i $ 次的概率和被选择 $ i $ 次对总和做出的贡献，将这两个东西乘起来。

在 $ k $ 天中选出 $ i $ 天的方案数是 $ C _ {k} ^ {i} $，这 $ i $ 天全部选中的概率 是 $ (\dfrac {1} {\frac {n(n - 1)} {2}}) ^ {i} $，剩下 $ k - i $ 天全部没选中的概率是 $ (1 - \dfrac {1} {\frac {n(n - 1)} {2}}) ^ {k - i} $。故恰好被选择 $ i $ 次的概率是 $ w _ i = C _ {k} ^ {i} (\dfrac {1} {\frac {n(n - 1)} {2}}) ^ {i}(1 - \dfrac {1} {\frac {n(n - 1)} {2}}) ^ {k - i} $。

被选择 $i$ 次对总和做出的贡献显然是 $ \displaystyle\sum _ {j = 1} ^ {i} f + (j - 1) = \frac {i(i - 1)} {2} + if $。

那么每对朋友对答案的贡献就是 $ \displaystyle \sum _ {i = 1} ^ {k} w _ i \times (\frac {i(i - 1)} {2} + if) $。

（$ i = 0 $ 时全是 $0$ 显然可以忽略）。

进一步地，得到 $ \displaystyle \sum _ {i = 1} ^ {k} w _ i \times \frac {i(i - 1)} {2} + f \times \sum _ {i = 1} ^ {k} w _ i \times i $。

预处理出 $ \displaystyle \sum _ {i = 1} ^ {k} w _ i \times \frac {i(i - 1)} {2} $ 和 $ \displaystyle \sum _ {i = 1} ^ {k} w _ i \times i $ 就可以对每一对朋友快速计算出贡献。

实现得好可以做到线性，但我写了线性对数，也能过。

```cpp
#include <bits/stdc++.h>

#define F(i, a, b) for(int i = (a); i <= (b); ++i)
#define dF(i, a, b) for(int i = (a); i >= (b); --i)

using namespace std;
typedef long long LL;
typedef unsigned long long ull;
const int N = 2e5 + 5;
const int mod = 1e9 + 7;

int qPow(int x, int y) {
    int res = 1;
    while (y) {
        if (y & 1) res = (LL) res * x % mod;
        x = (LL) x * x % mod, y >>= 1;
    }
    return res;
}
int fac[N], inv[N];
int C(int n, int m) { return (LL) fac[n] * inv[m] % mod * inv[n - m] % mod; }

int _, n, m, k, u, v, f, ans;
int nn, invnn, w[N], sum1, sum2;

int main() {
    // freopen("wmyr.in", "r", stdin);
    // freopen("wmyr.out", "w", stdout);
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> _;
    while (_--) {
        cin >> n >> m >> k;
        fac[0] = 1; F(i, 1, k) fac[i] = (LL) fac[i - 1] * i % mod;
        inv[0] = 1; F(i, 1, k) inv[i] = qPow(fac[i], mod - 2);
        nn = (LL) n * (n - 1) / 2 % mod, invnn = qPow(nn, mod - 2);
        F(i, 1, k) w[i] = (LL) qPow(invnn, i) * qPow(1 - invnn + mod, k - i) % mod * C(k, i) % mod;
        F(i, 1, k) sum1 += (LL) i * (i - 1) / 2 % mod * w[i] % mod, sum1 %= mod;
        F(i, 1, k) sum2 += (LL) w[i] * i % mod, sum2 %= mod;
        F(i, 1, m) cin >> u >> v >> f, ans += ((LL) f * sum2 % mod + sum1) % mod, ans %= mod;
        cout << ans << "\n", ans = sum1 = sum2 = 0;
    }
    return 0;
}
```

---

## 作者：jr_inf (赞：3)

令 $all=\frac{n(n-1)}{2},sum=\sum f_i$。每次都有 $\frac{m}{all}$ 的概率选到一对有贡献的人，并且有相同的概率让总贡献 +1，所以对于第 $i$ 次选择，它的贡献的期望是 $\frac{sum+(i-1)\frac{m}{all}}{all}$，所以答案就是 $\sum_{i=1}^{k}\frac{sum+(i-1)\frac{m}{all}}{all}$，化简得到 $\frac{all \times k \times sum+m\frac{k(k-1)}{2}}{all^2}$，时间复杂度取决于逆元的时间。

---

## 作者：lfxxx (赞：3)

考虑对于每对朋友计数。

对于一对朋友 $i$，被恰好抽中 $j$ 次的概率为 ${k \choose j} \times (\frac{1}{E})^j \times (1-\frac{1}{E})^{k-j}$。这里 $E$ 代表选择的总方案数。

其意义是先枚举在 $k$ 中哪 $j$ 次出现了，出现的地方出现的概率与不出现的地方不出现的概率相乘。

而被选择 $j$ 次带来的贡献为 $f_i \times j + \frac{j^2-j}{2}$。这个的意义是本身的贡献与贡献增量。

由于每队之间互不干扰，所以答案就是 $\sum_{i=1}^{m} \sum_{j=1}^{k} {k \choose j} \times (\frac{1}{E})^j \times (1-\frac{1}{E})^{k-j} \times (f_i \times j + \frac{j^2-j}{2})$。

然后有 $\sum_{i=1}^{m} \sum_{j=1}^{k} {k \choose j} \times (\frac{1}{E})^j \times (1-\frac{1}{E})^{k-j} \times (f_i \times j + \frac{j^2-j}{2}) = (\sum_{j=1}^{k} {k \choose j} \times (\frac{1}{E})^j \times (1-\frac{1}{E})^{k-j}) \times (\sum_{i=1}^{m} f_i) \times j + m \times \sum_{j=1}^{k} {k \choose j} \times (\frac{1}{E})^j \times (1-\frac{1}{E})^{k-j} \times \frac{j^2-j}{2}$。

发现 $\sum_{i=1}^{m} f_i$ 可以预处理出来，然后预处理组合数加快速幂处理逆元即可做到 $O(n + m + k \log mod)$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int maxn = 2e5+114;
const int mod = 1e9+7;
int fac[maxn];
int sum,ans;
int qpow(int a,int b){
    if(b==0) return 1;
    if(b==1) return a%mod;
    int res=qpow(a,b/2);
    res=(res*res)%mod;
    if(b%2==1) res=(res*a)%mod;
    return res;
}
int C(int x,int y){
    return ((fac[x]*qpow(fac[y],mod-2)%mod)*qpow(fac[x-y],mod-2))%mod;
}
int n,m,k;
void work(){
    ans=sum=0;
    cin>>n>>m>>k;
    for(int i=1;i<=m;i++){
        int u,v,f;
        cin>>u>>v>>f;
        sum=(sum+f)%mod;
    }
    fac[0]=1;
    for(int i=1;i<=k;i++){
        fac[i]=(fac[i-1]*i)%mod;
    }
    int E=((n*(n-1)%mod)*qpow(2,mod-2))%mod;
    for(int j=1;j<=k;j++){
        ans=(ans+((((C(k,j)*qpow(qpow(E,mod-2),j)%mod)*qpow((mod+1-qpow(E,mod-2))%mod,k-j)%mod)*sum%mod)*j%mod)%mod)%mod;
        //cout<<ans<<'\n';
        ans=(ans+((((((m*C(k,j)%mod)*qpow(qpow(E,mod-2),j)%mod)*qpow((mod+1-qpow(E,mod-2))%mod,k-j)%mod)*j%mod)*(j-1)%mod)*qpow(2,mod-2))%mod)%mod;
    }
    cout<<ans<<'\n';
    return ;
}
/*
1
2 1 10
1 2 1
*/
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin>>T;
    while(T--) work();
    return 0;
}

```


---

## 作者：1234567890sjx (赞：2)

对于每一对人 $(i,j)$，都有 $\frac{2}{n\times(n-1)}$ 的概率被选中，设这个概率为 $p$。

令 $g_0=\sum\limits_{i=1}^n f_i$，其中 $g_i$ 表示在第 $i$ 次远足**之后**总的友谊值的期望。

显然，每一次远足每一对人 $(i,j)$ 都有 $p$ 的概率被选中，也就是说，每一次远足让 $g_i$ 增加 $1$ 的概率均为 $p\times m$。同样的，所有被选中远足的人 $(i,j)$ 的期望也会同样的增加 $p\times g_i$。

所以直接按照上述的流程模拟即可。时间复杂度 $O(n)$。

[Code](https://www.luogu.com.cn/paste/xeo26uxu)

---

## 作者：EricWan (赞：0)

我真谢谢 CF 的赛后评测机制，赛场最后一分钟过了，重测因为服务器波动 T 飞了，总而言之，我太菜了。

我们不需要关系哪两个人类幼崽是朋友，只需要关心朋友的对数。

推式子：

$$\sum_{j=1}^{m}\sum_{i=0}^{k}(\frac{\frac{n\times(n-1)}{2}-1}{\frac{n\times(n-1)}{2}})^{k-i}\times(\frac{1}{\frac{n\times(n-1)}{2}})^i\times C_k^i\times\frac{((f_j)+(f_j+i-1))\times i}{2}$$

$i$ 为这对人类幼崽被选择的次数，$(\frac{\frac{n\times(n-1)}{2}-1}{\frac{n\times(n-1)}{2}})^{k-i}$ 为这对人类幼崽没有被选中的那些次的概率值之积，$(\frac{1}{\frac{n\times(n-1)}{2}})^i$ 为这对人类幼崽被选中的那些次的概率值之积，$C_k^i$ 用来枚举有多少种情况可以让这对人类幼崽被选中，$\frac{((f_j)+(f_j+i-1))\times i}{2}$ 就是这对人类幼崽对答案的贡献。

整理：

$$\sum_{i=0}^{k}(\frac{\frac{n\times(n-1)}{2}-1}{\frac{n\times(n-1)}{2}})^{k-i}\times(\frac{1}{\frac{n\times(n-1)}{2}})^i\times C_k^i\times\frac{(\sum_{j=1}^{m}(2\times f_j+i-1)))\times i}{2}$$

之后我们预处理出 $\sum_{j=1}^{m}f_j$ 的结果，逆元快速幂暴算即可。

结果我常数大了一点就寄了。

赛后同样代码同样语言过了。

祝愿 CF 早日换评测机。

---

## 作者：Zemu_Ooo (赞：0)

很久没有碰到在赛场上让我头大的题了（指在我能力范围内头大）。前三题基本如鱼得水，看到 D 是一道组合数学 + 概率论，头一下就疼了（

设有 $n$ 个孩子和 $m$ 对朋友，总共进行 $k$ 次远足。对于每一对朋友，他们的初始友谊值为 $f_i$。我们的目标是计算 $k$ 次远足后所有被选中的朋友对的友谊值总和的期望值。

概率论里有个经典的统计学概念叫[二项分布](https://baike.baidu.com/item/%E4%BA%8C%E9%A1%B9%E5%88%86%E5%B8%83/1442377)，即下面分母中出现的形似分数的式子。这个概念就不细讲了。

首先，我们注意到每次远足选择一对朋友的概率是 $\frac{m}{\binom{n}{2}}$，因为一共有 $\binom{n}{2}$ 对不同的孩子组合，其中 $m$ 对是朋友。

接下来，考虑每一对朋友的贡献。在 $k$ 次远足中，选择某对朋友至少一次的期望贡献可以这样计算：每次远足选择这对朋友的概率是 $\frac{1}{\binom{n}{2}}$，而每次选择他们都会使他们的友谊值增加 $1$。因此，如果在 $k$ 次远足中选择他们 $i$ 次，他们的总贡献是 $f_i + i$。

因此，对于每一对朋友，问题就变成了需要计算在 $k$ 次远足中选择他们 $0,1,2,\cdots ,k$ 次的概率，并乘以相应的贡献。由于选择一对朋友的事件是独立的，所以这可以通过二项式概率来计算。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define lb(x) ((x) & (-x))
#define int long long
#define double long double
#define ff first
#define ss second
#define mr make_pair
#define l(p) t[p].l 
#define r(p) t[p].r
#define lz(p) t[p].lz
const int mod = 1e9+7 ;
const int dlt = 1e9 + 7 ;
void cmin(auto &x, auto y) {
    x = min(x, y) ;
}
void cmax(int &x, int y) {
    x = max(x, y) ;
}
int read() {
    char ch ;int s = 0 ;int w = 1;
    while((ch = getchar()) >'9' || ch < '0' )if(ch == '-')w = -1 ;
    while(ch >= '0' && ch <= '9')s = (s << 1) + (s << 3) + (ch ^ 48) , ch = getchar() ;
    return s * w ;
}
void print(int x) {
    if(x < 0) putchar('-'), x = -x ;                  
    if(x > 9)print(x / 10) ;
    putchar(x % 10 + '0') ;
}                                   
void prn(int x) {      
    print(x) ;                                          
    putchar('\n') ;            
} 
int pows(int x, int k) {
    int bace = x, ans = 1 ;
    while(k) {
        if(k & 1) ans *= bace, ans %= mod ;
        bace *= bace, bace %= mod ;
        k >>= 1 ;
    }
    return ans ;
}
int TT ;
int n, m ;
int k, q ;
string s ;
int f[1000005] ;
int fck[1000005], inv[1000005] ;
int C(int x, int y) {
    return fck[x] * inv[y] % mod * inv[x - y] % mod ;
}
int cal(int x) {
    return (x * (x - 1) / 2) % mod ;
}
signed main() {
    fck[0] = 1, inv[0] = 1 ;
	for(int i=1;i<=1000000;i++)fck[i]=fck[i-1]*i%mod,inv[i]=pows(fck[i],mod-2);
    TT = read() ;
    while(TT--) {
        n = read(), m = read(), k = read() ;
    	int p, gg ;
    	p = pows((n * (n - 1) / 2) % mod, mod - 2) ;
    	gg = ((1 - p) + mod) % mod  ;
    	int ans = 0 ;
    	for(int i = 1 ; i <= m ; i++) {
        	read(), read() ;
        	int w = read() ;
        	ans += w * p % mod ;ans %= mod ;
    	}
    	ans = ans * k % mod ;
    	for(int i = 2 ; i <= k ; i++) {
        	ans += m * cal(i) % mod * pows(p, i) % mod * pows(gg, k - i) % mod
        	* C(k, i) % mod ;
       	 	ans %= mod ;
    	}
    	prn(ans%mod) ;
    }
    return 0 ;
}
```

---

## 作者：Chazz (赞：0)

# CF1925D Good Trip

## 解题思路
首先，可以看出来 $a_i$ 和 $b_i$ 具体是几并不重要，因为题目只关系一对孩子而不是某一个孩子。因此，可以把题目理解为有 $r=\frac{n(n-1)}{2}$ 组孩子，其中 $m$ 组是朋友，这几组朋友的友谊值为 $f_i$。

先观察第一轮（初始情况），第一轮选择一对孩子时抽到的友谊值期望是 $\sum_{i=1}^{m}\frac{f_i}{r} +\sum_{i=m+1}^{n}0=\frac{\sum_{i=1}^{m}{f_i}}{r}$。为了方便，接下来设 $s=\sum_{i=1}^{m}{f_i}$，所以这轮的期望是 $\frac{s}{r}$，$s$ 是会随着抽取的进行动态变化的。

再考虑抽取后的结果，有 $\frac{m}{r}$ 的概率抽中是朋友的一对孩子，并是这对朋友的友谊值增加 $1$，所以一轮对 $s$ 的期望变化是增加 $\frac{m}{r}$。

最简单的计算方式是直接循环轮次 $1$ 到 $k$，但我们也知道 $1+2+3+...+x=\frac{x(x-1)}{2}$，所以最终答案的公式是 $\sum_{i=1}^k{\frac{s+i\cdot\frac{m}{r}}{r}}=\frac{ks+\frac{m}{r}\cdot\frac{k(k-1)}{2}}{r}=\frac{ksr+m\frac{k(k-1)}{2}}{r^2}$。

另外讲一下分数模的问题，可以自己去查一下小费马定理。下面附上代码，时间复杂度 $O(m+\log MOD)$。

## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef vector<int> vti;
typedef vector<vector<int>> mati;
typedef vector<ll> vtll;
typedef vector<vector<ll>> matll;
typedef pair<int, int> pii;

const int MAXINT = 2147483647;
const ll MAXLL = 9223372036854775807ll;
const ull MAXULL = 18446744073709551615ull, MOD = 1e9 + 7;

const int MAXN = 1e5 + 5;
ull n, m, k, a, b, f;

ull fast_mod_pow(ull a, ull b) {
    ull r = 1;
    a %= MOD;
    while (b) {
        if (b & 1) r = (r * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return r;
}

ull frac_mod(ull a, ull b) {
    return ((a % MOD) * fast_mod_pow(b % MOD, MOD - 2)) % MOD;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m >> k;
        int sf = 0;
        for (ull i = 0; i < m; i++) {
            cin >> a >> b >> f;
            sf = (sf + f) % MOD;
        }
        ull bo = ((n * (n - 1)) >> 1) % MOD;
        ull to = (sf * bo) % MOD;
        bo = (bo * bo) % MOD;
        ull s = ((k * to) % MOD + (m * (((k * (k - 1)) >> 1) % MOD) % MOD)) % MOD;
        cout << frac_mod(s, bo) << endl;
    }
    return 0;
}

```

---

## 作者：Zi_Gao (赞：0)

## 前言

估值要掉没了，快来写题解。

## 正文

### 0x00 分析题目

发现这题需要计算期望，不妨先把期望转化为求所有情况的贡献和，最后除一个情况数即可。首先可以发现贡献相对独立，不同的两对朋友之间的贡献互不影响，于是考虑拆分贡献，对于第 $i$ 对朋友，首先枚举其一起出游了几次，记为 $j$，总共有 $\frac{j\left(j+1\right)}{2}+\left(f_i-1\right)j$ 的贡献。其次考虑有多少中情况可以取到这样的贡献，分成两部分计算，第一部分是在哪几次出游自然有 $\tbinom{k}{j}$ 中选法，然后考虑剩下出游次数的贡献，除了这对朋友，其他可以任意选，所以是 $\left(\frac{n\left(n-1\right)}{2}-1\right)^{k-j}$ 种选法那么总的贡献是 $\left(\frac{j\left(j+1\right)}{2}+\left(f_i-1\right)j\right)\tbinom{k}{j}\left(\frac{n\left(n-1\right)}{2}-1\right)^{k-j}$，发现可以分离变量 $f_i$ 那么预处理两部分的贡献即可。

### 0x01 代码实现

AC CODE

```cpp
#include<bits/stdc++.h>
// #define ONLINE_JUDGE
#define INPUT_DATA_TYPE int
#define OUTPUT_DATA_TYPE int
INPUT_DATA_TYPE read(){register INPUT_DATA_TYPE x=0;register char f=0,c=getchar();while(c<'0'||'9'<c)f=(c=='-'),c=getchar();while('0'<=c&&c<='9')x=(x<<3)+(x<<1)+(c&15),c=getchar();return f?-x:x;}void print(OUTPUT_DATA_TYPE x){if(x<0)x=-x,putchar('-');if(x>9)print(x/10);putchar(x%10^48);return;}

#define MODINT_TYPE long long

namespace MODINT{
	unsigned long long d;
    __uint128_t m;
    const unsigned int barK=64;
    void init(long long mod){
        m=(((__uint128_t)1)<<barK)/(d=mod);
        return;
    }

    inline unsigned long long mod(register unsigned long long x){
        register unsigned long long w=(m*x)>>barK;
        w=x-w*d;
        return w>=d?w-d:w;
    }

    MODINT_TYPE exgcd(MODINT_TYPE a,MODINT_TYPE b,MODINT_TYPE &x,MODINT_TYPE &y){
        if(!b){
            x=1;
            y=0;
            return a;
        }
        MODINT_TYPE d=exgcd(b,a%b,y,x);
        y-=a/b*x;
        return d;
    }

    MODINT_TYPE inv(MODINT_TYPE n,MODINT_TYPE p){
        MODINT_TYPE x,y;
        exgcd(n,p,x,y);
        x%=p;
        return x>=0?x:x+p;
    }

    struct MODNUM{
        MODINT_TYPE val;
        MODNUM(MODINT_TYPE x){
            if(x<0){
                val=d-mod(-x);
                if(val>=d) val-=d;
            }else val=mod(x);
            return;
        }
        MODNUM(){val=0;}
        inline MODNUM operator + (const MODNUM& o) const{return (MODNUM){(val+o.val>=d)?(val+o.val-d):(val+o.val)};}
        inline MODNUM operator + (const MODINT_TYPE& o) const{return *this+MODNUM(o);}
        inline MODNUM operator - (const MODNUM& o) const{return (MODNUM){(val-o.val<0)?(val-o.val+d):(val-o.val)};}
        inline MODNUM operator - (const MODINT_TYPE& o) const{return *this-MODNUM(o);}
        inline MODNUM operator * (const MODNUM& o) const{return (MODNUM){mod(val*o.val)};}
        inline MODNUM operator * (const MODINT_TYPE& o) const{return *this*MODNUM(o);}
        inline MODNUM operator / (const MODNUM& o) const{return (MODNUM){mod(val*inv(o.val,d))};}
        inline MODNUM operator / (const MODINT_TYPE& o) const{return *this/MODNUM(o);}

        inline MODNUM operator ++(){
            ++val;
            if(val>=d) val-=d;
            return *this;
        }
        inline MODNUM operator ++(const int){
            MODNUM tmp=*this;
            ++val;
            if(val>=d) val-=d;
            return tmp;
        }
        inline MODNUM operator --(){
            --val;
            if(val<0) val+=d;
            return *this;
        }
        inline MODNUM operator --(const int){
            MODNUM tmp=*this;
            --val;
            if(val<0) val+=d;
            return tmp;
        }

        inline MODNUM& operator += (const MODNUM& o) {return *this=*this+o;}
        inline MODNUM& operator += (const MODINT_TYPE& o) {return *this=*this+o;}
        inline MODNUM& operator -= (const MODNUM& o) {return *this=*this-o;}
        inline MODNUM& operator -= (const MODINT_TYPE& o) {return *this=*this-o;}
        inline MODNUM& operator *= (const MODNUM& o) {return *this=*this*o;}
        inline MODNUM& operator *= (const MODINT_TYPE& o) {return *this=*this*o;}
        inline MODNUM& operator /= (const MODNUM& o) {return *this=*this/o;}
        inline MODNUM& operator /= (const MODINT_TYPE& o) {return *this=*this/o;}

        operator MODINT_TYPE(){
            return val;
        }
    };
};

#define PC_DATA_TYPE long long

const PC_DATA_TYPE PC_MOD=1000000007;
const PC_DATA_TYPE PC_DATA_SIZE=200010;

PC_DATA_TYPE inv[PC_DATA_SIZE],fact[PC_DATA_SIZE],invfact[PC_DATA_SIZE];

void init_pc(int n){
    register int i;
    for(inv[0]=0,inv[1]=fact[0]=fact[1]=invfact[0]=invfact[1]=1,i=2;i<=n;++i)
        invfact[i]=invfact[i-1]*(inv[i]=PC_MOD-PC_MOD/i*inv[PC_MOD%i]%PC_MOD)%PC_MOD,fact[i]=fact[i-1]*i%PC_MOD;
    return;
}

PC_DATA_TYPE A(int n,int m){
    if(n<0||m<0||n<m) return 0;
    return fact[n]*invfact[n-m]%PC_MOD;
}
PC_DATA_TYPE C(int n,int m){
    if(n<0||m<0||n<m) return 0;
    return fact[n]*invfact[n-m]%PC_MOD*invfact[m]%PC_MOD;
}

#define QPOW_DATA_TYPE MODINT::MODNUM
QPOW_DATA_TYPE qpow(register QPOW_DATA_TYPE base,register int e){
    register QPOW_DATA_TYPE res=1;
    while(e){
        if(e&1) res=(res*base);
        base=(base*base);
        e>>=1;
    }
    return res;
}

void solve(){
    register long long i;
    register MODINT::MODNUM baseVal=0,sum=0,res=0,tmp,sum2=0,now;
    long long n=read();
    long long m=read();
    long long k=read();
    if(m==0) return puts("0"),void();
    for(i=1;i<=k;++i){
        tmp=C(k,i)*qpow(n*(n-1)/2-1,k-i);
        baseVal+=tmp*(i*(i+1)/2);
        // sum2+=tmp;
        sum+=tmp*i;
    }
    for(i=0;i<m;++i){
        read();read();
        now=read();
        res+=sum*(now-1)+baseVal;
    }
    res/=qpow(n*(n-1)/2,k);
    print(res),putchar('\n');
}

int main(){
	#ifndef ONLINE_JUDGE
	freopen("name.in", "r", stdin);
	freopen("name.out", "w", stdout);
	#endif

    MODINT::init(1000000007);
    init_pc(PC_DATA_SIZE-1);

    int T=read();
    while(T--) solve();

	#ifndef ONLINE_JUDGE
	fclose(stdin);
	fclose(stdout);
	#endif
    return 0;
}
```


---

