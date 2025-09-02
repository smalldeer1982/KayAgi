# [ARC064F] Rotated Palindromes

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc064/tasks/arc064_d

高橋君と青木君が協力して数列を作ることになりました。

まず、高橋君が次の条件をすべて満たす数列 $ a $ を用意します。

- $ a $ は長さ $ N $ である。
- $ a $ の各要素は $ 1 $ 以上 $ K $ 以下の整数である。
- $ a $ は回文である。 すなわち、$ a $ を逆順にした数列は元の $ a $ と一致する。

次に、青木君が次の操作を好きな回数だけ繰り返します。

- $ a $ の先頭要素を末尾へ移動する。

以上の手続きにより、最終的な $ a $ が得られます。

最終的な $ a $ として考えられるものは何通りあるでしょうか？ $ 10^9+7 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 1\ <\ =N\ <\ =10^9 $
- $ 1\ <\ =K\ <\ =10^9 $

### Sample Explanation 1

次の $ 6 $ 通りです。 - $ (1,\ 1,\ 1,\ 1) $ - $ (1,\ 1,\ 2,\ 2) $ - $ (1,\ 2,\ 2,\ 1) $ - $ (2,\ 2,\ 1,\ 1) $ - $ (2,\ 1,\ 1,\ 2) $ - $ (2,\ 2,\ 2,\ 2) $

## 样例 #1

### 输入

```
4 2```

### 输出

```
6```

## 样例 #2

### 输入

```
1 10```

### 输出

```
10```

## 样例 #3

### 输入

```
6 3```

### 输出

```
75```

## 样例 #4

### 输入

```
1000000000 1000000000```

### 输出

```
875699961```

# 题解

## 作者：Scintilla (赞：10)

**Description**

任意选择一个长度为 $n$、其中元素为 $[1, k]$ 中整数的回文串，然后把它的一个前缀挪到最右侧，问一共能得到几种不同的串。答案对 $10^9 + 7$ 取模。

$n, k \le 10^9$。

**Solution**

我们来考虑如何去重。

显然只有循环同构的回文串才能转化。回文串的循环节肯定也是回文串，而最小循环节长度为偶数的回文串的循环同构只有把它最小循环节的前一半挪到后面所得的串，例如 $\texttt{abbaabba}$ 和 $\texttt{baabbaab}$；最下循环节长度为奇数的回文串没有循环同构，例如 $\texttt{abaaba}$ 就找不到循环同构。

所以对于一个回文串，若它的最小循环节长度为 $s$。若 $s$ 为偶数，则它挪 $\frac{s}{2}$ 个字符之后就又形成了一个回文串，这时再挪的话就会和这个回文串重复计数，所以它的贡献为 $\frac{s}{2}$。若 $s$ 为奇数，同理它的贡献为 $s$。

可以筛出 $n$ 的约数，枚举最小循环节的长度，计算它有多少种情况（除去有更小的循环节的情况）再累加贡献即可。我的实现比较劣，时间复杂度大概是 $\mathcal{O}(\sqrt{n} + d_n^2 \log n)$。

```cpp
#include <bits/stdc++.h>

using namespace std;

#define il inline
#define re register
#define rep(i, s, e) for (re int i = s; i <= e; ++i)
#define drep(i, s, e) for (re int i = s; i >= e; --i)
#define file(a) freopen(#a".in", "r", stdin), freopen(#a".out", "w", stdout)

const int mod = 1e9 + 7;

const int N = 1000010;

il int read() {
    int x = 0; bool f = true; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = false; c = getchar();}
    while (isdigit(c)) x = (x << 1) + (x << 3) + (c ^ 48), c = getchar();
    return f ? x : -x;
}

il int inc(int a, int b) { return (a += b) >= mod ? a - mod : a; }
il int dec(int a, int b) { return (a -= b) < 0 ? a + mod : a; }
il int mul(int a, int b) { return 1ll * a * b % mod; }
il int qpow(int a, int b) { int res = 1; for (; b; b >>= 1, a = mul(a, a)) if (b & 1) res = mul(res, a); return res; }

int n, k, tot, d[N], cnt[N], ans;

int main() {
    n = read(), k = read();
    for (int i = 1; i * i <= n; ++i) {
        if (n % i) continue;
        d[++tot] = i;
        if (i * i != n) d[++tot] = n / i;
    }
    sort(d + 1, d + tot + 1);
    rep(i, 1, tot) {
        cnt[i] = qpow(k, (d[i] + 1) >> 1);
        rep(j, 1, i - 1) if (!(d[i] % d[j])) cnt[i] = dec(cnt[i], cnt[j]);
        ans = inc(ans, mul(cnt[i], (d[i] & 1) ? d[i] : d[i] >> 1));
    }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：zhylj (赞：6)

## 分析

考虑求出所有最小整周期为 $x$（即最短的循环节长度为 $x$）的循环同构意义下本质不同的回文串的方案数 $f(x)$，那么答案就为：

$$
\sum_{x\mid n} xf(x)
$$

先考虑最小整周期为 $n$，即形如 $AA^r$（$A^r$ 表示 $A$ 的翻转）或 $AcA^r$（$c$ 表示一个字符），循环同构意义下本质不同回文串的方案数。

手模了几组这样的串后，可以发现与 $AA^r$ 循环同构的回文串有且仅有一个：$A^rA$，例如 $\mathtt {1221}$ 和 $\mathtt {2112}$.

我们同样可以发现，对于形如 $AcA^r$ 的回文串，不存在任何回文串与其循环同构。

再发现，我们对一个存在循环节的串循环位移，相当于对其每个循环节进行循环位移，所以上述的规则可以直接适用于任何存在循环节的情况：形如 $AA^rA\cdots AA^r$ 的串存在唯一与其不相同且循环同构的串为 $A^rA\cdots A^rA$，于是设 $f_0(x)$ 表示最小整周期为 $x$ 的回文串个数，则我们有：

$$
f(x) = \left\{\begin{aligned}
\frac {f_0(x)}2 & \quad,2\mid x \\
f_0(x) & \quad,2\nmid x
\end{aligned}\right.
$$

然后考虑最小整周期恰为 $x$ 的方案数不好求，于是考虑设 $F(x)$ 表示最小整周期 $d$ 是 $x$ 的约数的方案数，而我们显然有 $F(x) = k^{\lceil x/2\rceil}$.

莫比乌斯反演可得：

$$
F(x) = \sum_{d\mid x} f_0(d) \iff f_0(x) = \sum_{d\mid x} \mu\left(\frac xd\right)F(x)
$$

暴力计算就可以做到 $\mathcal O(\sqrt nd(n))$ 的复杂度，其中 $d$ 为约数个数函数，但应该可以通过一些其他技巧优化计算做到更优。

## 代码

[提交记录](https://atcoder.jp/contests/arc064/submissions/21397115).

---

## 作者：Graphcity (赞：4)

光看题面并不能很容易地计数合法字符串个数，考虑发掘性质：

1. 对于任意回文串，它的最小循环节一定是回文串。  
  **证明**：根据 border 理论，比较最长的 border 即可得出结论。

2. 我们设最小循环节为它本身的回文串为「本原回文串」。观察发现，对于任意本原回文串，如果长度为奇数，那么它的任意循环位移均不是回文串；如果长度为偶数，恰有一个循环位移同样为回文串。

设 $f_i$ 为长度为 $i$ 的本原回文串个数。显然本题只用考虑 $i$ 为 $n$ 约数的情况，个数在 $\sqrt[3]{n}$ 级别。

对于一个 $i$，考虑容斥。长度为 $i$ 的回文串共有 $k^{\lceil\frac{i}{2}\rceil}$ 种，同时还要减去存在更小的循环节的情况。也就是说，

$$
f_i=k^{\lceil\frac{i}{2}\rceil}-\sum_{j\mid i} f_j
$$

暴力枚举的时间复杂度是 $O(n^{\frac{2}{3}})$。

接下来就是统计答案。如果 $i$ 为奇数，则每一个本原回文串可以产生 $i$ 个不同的合法串。如果 $i$ 为偶数，可以产生 $\dfrac{i}{2}$ 个不同的合法串。将 $f_i$ 与这些系数相乘之后求和即可。

```cpp
#include<bits/stdc++.h>
#define For(i,a,b) for(int i=(a);i<=(b);++i)
#define Rof(i,a,b) for(int i=(a);i>=(b);--i)
using namespace std;
const int Maxn=2e5,Mod=1e9+7;

inline int Pow(int x,int y)
{
    int res=1;
    while(y)
    {
        if(y&1) res=1ll*res*x%Mod;
        x=1ll*x*x%Mod,y>>=1;
    }
    return res;
}

int n,m,ans,h[Maxn+5],f[Maxn+5],s;

int main()
{
    cin>>n>>m; h[1]=1,h[2]=n,s=2;
    int now=n; for(int i=2;i*i<=n;++i) if(n%i==0)
    {
        h[++s]=i,h[++s]=n/i;
        while(now%i==0) now/=i;
    } if(now>1) h[++s]=now;
    sort(h+1,h+s+1),s=unique(h+1,h+s+1)-h-1;
    For(i,1,s)
    {
        f[i]=Pow(m,(h[i]+1)/2);
        For(j,1,i-1) if(h[i]%h[j]==0) f[i]=(f[i]-f[j]+Mod)%Mod;
    }
    For(i,1,s) ans=(ans+1ll*f[i]*(h[i]/(1+(h[i]%2==0))))%Mod;
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：Honor誉 (赞：4)

Description
然而，由于小C沉迷于制作游戏，他完全忘记了自己作为国家集训队的一员，还有156道作业题等他完成。还有一天作业就要截止了，而他一题还没有做。于是他赶紧挑了一道看起来最简单的题：

“给定一个整数N，请你求出有多少字符集为1到K之间整数的字符串，使得该字符串可以由一个长度为N的回文串循环移位后得到。所谓循环移位，就是把字符串的某个前缀（可以为空）移到字符串末尾，如"1221"循环移位可以得到"1221"、"2211"、"2112"、"1122"四个字符串。结果对109+7取模。”

为了不让小C的集训队资格被CCF取消，请你帮助他完成这道题吧。

Input

第一行包含两个整数N,K。

Output

输出满足条件的字符串数对109+7取模的结果。

Sample Input
## Sample Input 1
4 2

## Sample Input 2
1 10

## Sample Input 3
6 3

## Sample Input 4
1000000000 1000000000

Sample Output
## Sample Output 1
6

## Sample Output 2
10

## Sample Output 3
75

## Sample Output 4
875699961

HINT

在第一个样例中，有"1111"、"1122"、"1221"、"2211"、"2112"、"2222"，共6个字符串符合条件。

我们先考虑枚举回文串，因为回文串是回文的，所以我们只用枚举回文串的一半，回文串的个数就是$m^{(n+1)/2}$。

每一个回文串应该有$n$种循环移位后的到的字符串，但是这样计算后我们会发现这比答案大很多，因为有重复。

我们考虑如何计算不重复的字符串的个数，我们可以枚举回文串的循环节。

分两种情况讨论。

### 1.循环节为奇数
因为一个回文串的循环节必定为回文串，所以我们循环移位1个循环节的长度为$len$就会有重复，所以会产生$len$个新字符串。

### 2.循环节为偶数
因为上述的原因，循环节必定回文，我们只要有$len/2$的长度就会重复。

比如说，串$122111221$,我们移了两位之后，串变成$21122112$,虽然看起来与原串并不相同，但是我们在枚举回文串的时候，也会枚举到$21122112$,所以也算重复。

### 接下来DP。

我们先预处理出$n$的所有因数，$a[]$

我们设$dp[i]$表示最小循环节为$a[i]$时，有多少个符合条件的回文串。

我们在$dp[i]$中减去$dp[a[i]的因子]$，为了保证$a[i]$时最小的循环节。

ans就直接加上回文串所贡献的字符串个数即可。

时间复杂度大约$O（因子个数^2*log(n/2)）$

```cpp

#include<bits/stdc++.h>
#define mod 1000000007
#define int long long
using namespace std;
int dp[2010],cnt,n,k,a[2010],ans;
int fastpow(int x,int y)
{
    int sum=1;
    while(y)
    {
        if(y&1)
        {
            sum=(1ll*sum*x)%mod;
        }
        x=(1ll*x*x)%mod;
        y>>=1;
    }
    return sum;
}
signed main()
{
    scanf("%lld%lld",&n,&k);
    for(int i=1;i*i<=n;i++)//枚举因子
    {
        if(n%i==0)
        {
            a[++cnt]=i;
            if(i*i!=n)
            {
                a[++cnt]=n/i;
            }
        }
    }
    sort(a+1,a+cnt+1);
    for(int i=1;i<=cnt;i++)
    {
        dp[i]=fastpow(k,(a[i]+1)/2);//有多少个回文串
        for(int j=1;j<i;j++)
        {
            if(a[i]%a[j]==0)//去重
            {
                dp[i]=(dp[i]-dp[j]+mod)%mod;
            }
        }
        if(a[i]&1)//统计答案
        {
            ans=(ans+dp[i]*a[i])%mod;
        }else{
            ans=(ans+dp[i]*(a[i]/2))%mod;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
```

---

## 作者：qinhuanmma (赞：2)

一个比较直观的想法是用回文串个数乘上 $n$ 得到答案，但显然这样会算重。

考虑如何去重。由于和循环移位有关，考虑标志物思想，即每个计入答案的串只在一个回文串处计算贡献。

那么我们对每个回文串考虑贡献。设回文串 $A$ 一直循环移位，直到再次回文，变成了回文串 $B$，移位了 $t(\ge 1)$ 次。那么在 $A$ 处只需计入 $t$ 的贡献。

考虑 $t$ 和 $A$ 的关系。设 $A$ 的最小循环节长度为 $s$，那么显然 $t\le s$。考虑 $A$ 作为回文串的性质：$A$ 循环移位 $t$ 位得到的串与 $A$ 循环移位 $s-t$ 为得到的串相同。

那很奇怪了，由于 $s$ 是最小循环节，所以 $A$ 循环移位 1 位，2 位……$s$ 位得到的串应该互不相同（否则会有更小的循环节），这就说明要么 $t=s-t$，要么 $t=s$。

所以 $s$ 为奇数时 $t=s$，$s$ 为偶数时 $t=\frac{s}{2}$。

接下来就很套路了，对于每个 $x\mid n$，统计有多少个长为 $n$ 回文串满足最小循环节长度为 $x$，即有多少长度为 $x$ 的最小循环节为本身的回文串。

设方案数为 $f_x$，正难则反，用总减不合法即可。
$$
f_x=k^{\lceil \frac{x}{2} \rceil}-\sum_{i|x,i\not=x}{f_i}
$$
时间复杂度 $O(d(n)^2)$，$d(n)$ 表示 n 的因子个数。
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N = 200010, mod = 1e9 + 7;
namespace cza{
	int n, k;
	int kpow(int a, int b){
		int c = 1;
		while(b){
			if(b & 1) c = a * c % mod;
			a = a * a % mod, b >>= 1;
		}
		return c;
	}
	int tmp[N], tcnt;
	int tmp2[N], t2;
	int cnt[N];
	int main(){
		cin >> n >> k;
		for(int i = 1; i * i <= n; i++){
			if(n % i == 0){
				tmp[++tcnt] = i;
				if(i * i != n) tmp2[++t2] = n / i;
			}
		}
		while(t2) tmp[++tcnt] = tmp2[t2--];
		int ans = 0;
		for(int i = 1; i <= tcnt; i++){
			cnt[i] = kpow(k, tmp[i] + 1 >> 1);
			for(int j = 1; j < i; j++){
				if(tmp[i] % tmp[j] == 0) cnt[i] -= cnt[j];
			}
			cnt[i] = (cnt[i] % mod + mod) % mod;
			ans += cnt[i] * (tmp[i] & 1 ? tmp[i] : tmp[i] >> 1) % mod;
			ans %= mod;
		}
		cout << ans;
		return 0;
	}
}
signed main(){
	return cza::main();
}
```

---

## 作者：lgswdn_SA (赞：2)

这题可以直接考虑变化带来的贡献，因为对于每一个可以得到的非循环数列都可以唯一确定其初始的循环数列，重复发生当且仅当一个回文串经过移动后变成了另一个回文串，即一个回文串是另一个的循环位移。先将这个回文串拆成自己的一个循环节（也是一个回文串），我们发现当且仅当这个循环节是偶回文串才会出现回文循环位移（把循环节长度的一半的前缀扔到后面去）。一个最小循环节可以一一对应一个长 $n$ 的串，于是设最小循环节长度为 $m$。若 $m$ 为奇则其对答案的贡献为 $s(m)=m$；若 $m$ 为偶则其对答案的贡献为 $s(m)=\frac{m}{2}$。

然后就是数长度为 $m$ 的最小回文循环节的个数。设 $f(m)$ 表示这个个数，我们可以容斥一下，于是有
$$
f(m)=K^{\lceil\frac{m}{2}\rceil}-\sum_{d|m} f(d)
$$
$$
ans=\sum_{d|n} f(d)s(d)
$$
时间复杂度 $O(d^2(n)\log K+\sqrt n)$。

https://atcoder.jp/contests/arc064/submissions/28627100

---

## 作者：james1BadCreeper (赞：0)

考虑如何不重不漏地统计。如果一个回文串是由多个相同的回文串组成的，那么设它的最小循环节长度为 $t$，那么将其移动 $t$ 次后就会变成原来的回文串。

设 $f_i$ 表示长度为 $i$ 的回文串个数，我们只需要考虑 $i$ 为 $n$ 的约数的情况。

长度为 $i$ 的回文串有 $k^{\lceil i/2 \rceil}$ 种，根据上面所说的不重不漏，容斥得到 $f_i=k^{\lceil i/2 \rceil}-\sum_{j\mid i} f_j$。

如何统计答案？如果 $i$ 是奇数，那么操作 $i$ 次之后所构成的串均不相同，系数为 $i$；如果 $i$ 是偶数，那么操作 $i/2$ 次之后会变成一个新的回文串，为了防止算重，其系数为 $i/2$。

```cpp
#include <bits/stdc++.h>
using namespace std; 
const int P = 1000000007; 

inline int poww(int a, int b) {
    int r = 1; 
    for (; b; b >>= 1, a = 1ll * a * a % P) if (b & 1) r = 1ll * r * a % P; 
    return r; 
}

int n, k, f[100005]; 
vector<int> d; 

int main(void) {
    cin >> n >> k; 
    for (int i = 1; i * i <= n; ++i) if (n % i == 0) {
        d.emplace_back(i); 
        if (i * i != n) d.emplace_back(n / i); 
    }
    sort(d.begin(), d.end()); 
    int ans = 0; 
    for (int i = 0; i < d.size(); ++i) {
        f[i] = poww(k, d[i] + 1 >> 1); 
        for (int j = 0; j < i; ++j) if (d[i] % d[j] == 0) f[i] = (f[i] - f[j]) % P; 
        ans = (ans + 1ll * f[i] * (d[i] % 2 ? d[i] : d[i] / 2)) % P; 
    }
    cout << (ans + P) % P << "\n"; 
    return 0; 
}
```

---

