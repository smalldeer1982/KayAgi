# [ARC004D] 表現の自由 ( Freedom of expression )

## 题目描述

[problemUrl]: https://atcoder.jp/contests/arc004/tasks/arc004_4

整数 $ N $ と $ M $ が与えられる時、整数 $ N $ を $ M $ 個の整数の積で表す方法は何通りあるでしょうか。  
 その答えを $ 1,000,000,007 $ で割った余りを答えてください。 入力は以下の形式で標準入力から与えられる。

> $ N $ $ M $

- 入力は $ 1 $ 行のみからなり、整数 $ N(1\ ≦\ |N|\ ≦\ 10^9) $ と整数 $ M(1\ ≦\ M\ ≦\ 10^5) $ が空白区切りで与えられる。
 
 整数 $ N $ を $ M $ 個の整数の積で表す方法の数を $ 1,000,000,007 $ で割った余りを標準出力に $ 1 $ 行で出力せよ 。  
 なお、最後には改行を出力せよ。 ```
<pre class="prettyprint linenums">
10 2
```

 ```
<pre class="prettyprint linenums">
8
```

- $ 10 $ を $ 2 $ つの整数の積で表す方法は以下の $ 8 $ 通りになります。
- $ 1\ \times\ 10 $
- $ 2\ \times\ 5 $
- $ 5\ \times\ 2 $
- $ 10\ \times\ 1 $
- $ (-1)\ \times\ (-10) $
- $ (-2)\ \times\ (-5) $
- $ (-5)\ \times\ (-2) $
- $ (-10)\ \times\ (-1) $
 

```
<pre class="prettyprint linenums">
1000000000 1
```

 ```
<pre class="prettyprint linenums">
1
```

- $ 1,000,000,000 $ を $ 1 $ つの積で書き表すには $ 1,000,000,000 $ と書くしか無いので、$ 1 $ 通りになります。

```
<pre class="prettyprint linenums">
-2 3
```

 ```
<pre class="prettyprint linenums">
12
```

- $ -2 $ を $ 3 $ つの整数の積で表す方法は以下の $ 12 $ 通りになります。
- $ 1\ \times\ 1\ \times\ (-2) $
- $ 1\ \times\ 2\ \times\ (-1) $
- $ 1\ \times\ (-1)\ \times\ 2 $
- $ 1\ \times\ (-2)\ \times\ 1 $
- $ 2\ \times\ 1\ \times\ (-1) $
- $ 2\ \times\ (-1)\ \times\ 1 $
- $ (-1)\ \times\ 1\ \times\ 2 $
- $ (-1)\ \times\ 2\ \times\ 1 $
- $ (-1)\ \times\ (-1)\ \times\ (-2) $
- $ (-1)\ \times\ (-2)\ \times\ (-1) $
- $ (-2)\ \times\ 1\ \times\ 1 $
- $ (-2)\ \times\ (-1)\ \times\ (-1) $
 

```
<pre class="prettyprint linenums">
50 1000
```

 ```
<pre class="prettyprint linenums">
96554651
```

# 题解

## 作者：灰鹤在此 (赞：2)

本题涉及的知识点：分解质因数、组合数（球盒问题）。

题意：把 $n$ 分解成 $m$ 个整数的方案数。

因为每一个整数都是由不同种类个数的质因数乘积而来，即质因数是组成整数的单位（乘积角度）。我们分解成的这 $m$ 个数也是由不同种类个数的质因数乘积而来，所以原问题就变成了先把 $n$ 分解质因数，我们设 $n=\prod\limits_{i=1}p_i^{k_i}$，于是我们就得到了每一个质因子的质数 $k_i$。然后我们要把这些 $k_i$ 分配到 $m$ 个组别里面。这个问题可以看成把 $n$ 个球（隶属不同的组的球不同）放入 $m$ 个不同盒子里面的方案数（盒子可空）。

这个用乘法原理和插板法可以解决，因为组别之间没有互相的限制，所以我们对于每一组的球用插板法求出他们的方案数。是 $\dbinom{k_i+m-1}{m-1}$，然后我们把所有的乘起来就是**不考虑符号**的方案数。

关于符号，我们让最后一位的符号为控制位，前面 $m-1$ 个符号随意安排，因为我们让最后一位符号控制了我们最终乘积的符号，于是我们的符号方案数就是 $2^{m-1}$。

最终我们得到的答案就是不考虑符号的方案数乘以符号方案数。

Code:

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long mod=1e9+7;
const int MaxN=2e5+5;
long long n,m;
long long qpow(long long x,long long y){
	long long res=1;
	while(y){
		if(y&1){
			res=res*x%mod;
		}
		x=x*x%mod;
		y>>=1;
	}
	return res;
}
long long fac[MaxN],inv[MaxN];
void init(){
	fac[0]=fac[1]=inv[0]=inv[1]=1;
	for(long long i=2;i<=MaxN-5;i++){
		fac[i]=fac[i-1]*i%mod;
	}
	inv[MaxN-5]=qpow(fac[MaxN-5],mod-2);
	for(long long i=MaxN-5;i>=2;i--){
		inv[i-1]=inv[i]*i%mod;
	}
}
long long C(long long x,long long y){
	if(y>x){
		return 0;
	}
	return fac[x]*inv[y]%mod*inv[x-y]%mod;
}
long long memory[MaxN],cnt;
int main(){
	scanf("%lld%lld",&n,&m);
	init();
	if(n<0){
		n=-n;
	}
	long long sum=1,ans;
	for(long long i=2;i*i<=n;i++){
		if(n%i==0){
			cnt++;
			while(n%i==0){
				n/=i;
				memory[cnt]++;
			}
		}
	}
	if(n>1){
		memory[++cnt]=1;
	}
	for(long long i=1;i<=cnt;i++){
		sum=sum*C(memory[i]+m-1,m-1)%mod;
	}
	ans=sum*qpow(2,m-1)%mod;
	printf("%lld\n",ans);
	return 0;
}
```

---

## 作者：HohleFeuerwerke (赞：1)

### 前言

[题目link](https://www.luogu.com.cn/problem/AT187)。这个题被我用了远远高于蓝题的算法解决了。~~虽然我还没有写。~~

但是思维难度真的低。

### 正文

题目大概意思就是 $n$ 和 $m$ 给定，然后让你求出用 $m$ 个整数的乘积表示 $n$ 的方法数。

首先，不管这个 $m$ 是整是负，我们都能知道这 $m$ 个整数一定是 $n$ 的约数。

想到了约数，并且这个题又是一个数数题，那么~~不~~自然地就能够想到 pollard-rho。

首先跑一遍 pollard-rho 把 $n$ 唯一分解。这里讲一个小技巧：我们可以用 STL 的 map 来存储底数（素因数）和其指数的关系。这个也是易于实现的。略过了。

然后继续来看。

我们假设这个 $n$ 唯一分解以后长成这个样子：

$$n=\prod_{i=1}^{\text{unknown}}p_i^{k_i}$$

其中 $\text{unknown}$ 表示 $n$ 含有不同的素因子个数，$p_i$ 是素因子，$k_i$ 是指数。

然后进一步思考。我们要求得的答案是他分解为 $m$ 个数的方案种类。那么这个问题就变成了一个组合数学问题。

现在我有 $z$ 个因数，我需要知道从其中挑出 $m$ 个数，他们的积正好是 $n$ 的种数。

由于我已经将 $n$ 唯一分解了，那么我就知道了每一个素因数对应的指数。对于每一个素因数，$n$ 所对的 $p_i$ 的指数 $k_i$，一定是所有分解得来的数的 $p_i$ 的 $k'_i$ 之和。

进一步来说，我们可以写出这样一个式子：

$$\sum k'_i=k_i$$

其中 $k'_i$ 是分解的数的某一个质因数的指数，$k_i$ 是原数 $n$ 所含的这个质因数的指数。

感性的认识一下上面那个式子所对应的问题：一个有 $k_i$ 个小球的盒子，现在要把它分成 $m$ 堆，有几种方法。

对于每一个素因数我们都来求解这样一个问题，然后用乘法原理来算一下即可。

这是我们的第一个子问题。就是 $n$ 为正，且所有分解得到的数都为正数。

然后我们来思考接下来一个问题，如果 $n$ 为正，有可能分解得到的数为负数怎么办？

由于负数一定有偶数个，那么我们可以先行遍历一遍求出所有的符号可能性，然后和之前的结果乘一下就行了。

然后我们再讨论一下 $n$ 为负数时所得的结果。这个也是很简单的，跟 $n$ 为正数其实一样，只是后面讨论负数个数的时候稍微有些差别。

就是这样。这个题其实真的挺简单的。













---

## 作者：Conan15 (赞：0)

首先，容易想到先把正负问题分离出来，即只计算 $n$ 绝对值，拆分为若干**正整数乘积**的答案，最后乘上一些组合数就是有正有负的答案。


----------

似乎可以求出 $n$ 的所有因数。\
然后容易想到用 dfs 去模拟类似因数相乘的过程，记录当前是第几个因数、乘积是多少、用了几个因数……等等。\
显然每次添加一个因数，乘积至少 $\times 2$，所以最多选择 $\log n$ 个因数，复杂度一定是正确的。\
~~然后你就会像我一样调得很痛苦，可能是我实现方法的问题吧。~~

----------

既然因数不好做，那我们就从质因数入手！\
可以想象为现在有 $m$ 个 $1$，对于每一个质因数 $x$，你可以随机把它扔到 $m$ 个空位中的一个。\
这是什么模型？有若干个相同的球，放到若干个本质不同的箱子里，盒子允许为空的方案数！\
显然，当有 $n$ 个球，$k$ 个箱子的时候答案为 $C_{n+k-1,k-1}$。\
所以对于 $x$ 质因数，如果它存在 $k$ 个，那么对答案的贡献就是 $C_{m+k-1,k-1}$。

最后怎么处理正负问题？考虑枚举负数个数 $i$，则有 $C_{m,i}$ 种情况，枚举所有的 $i$ 计算组合数之和即可。\
但显然，这个组合数之和与 $2^{m-1}$ 是相等的。

代码中保留了我 dfs 写法中的红温部分，以及省略了 Modint 部分。

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 15, mod = 1e9 + 7;

template <class type,const type mod> struct Modint{ ...Write sth... };
typedef Modint<long long, mod> Mint;    //记得自定义 mod

int n, m, t;
int a[N], tot = 0;
Mint ans, res;

Mint fac[N], inv[N];
Mint qmi(Mint a, int k) {
    Mint res = 1;
    while (k) {
        if (k & 1) res *= a;
        a *= a;
        k >>= 1;
    }
    return res;
}
void init() {
    fac[0] = 1;
    for (int i = 1; i <= 200000; i++) fac[i] = fac[i - 1] * i;
    inv[200000] = qmi(fac[200000], mod - 2);
    for (int i = 199999; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1);
}
Mint C(int n, int m) { return fac[n] * inv[m] * inv[n - m]; }

// Mint val(int cnt) { return C(m, cnt); }  // m 个空位里面填 cnt 个

void get() {
    for (int i = 2; i <= n / i; i++) {
        int c = 0;
        while (n % i == 0) n /= i, c++;
        ans *= C(c + m - 1, m - 1);
    }
    if (n > 1) ans *= m;
}


// void dfs(int u, int now, int cnt) {  //当前到第几个数，还剩可分解的乘积为 now，选了总共 cnt 个数
//     if (now == 1) return;
//     //直接统计答案，考虑剩下的直接把 now 这个数填进去，剩下都是 1
//     if (cnt > 0) ans += val(cnt + 1), cout << u << ' ' << now << ' ' << cnt << endl;
//     if (cnt == m - 1 || u == tot) return;   //无法继续分解
//     //不选择这个数
//     dfs(u + 1, now, cnt);
//     //选择这个数
//     if (now % a[u] == 0) {
//         int nxt = now / a[u];
//         dfs(u + 1, nxt, cnt + 1);
//     }
// }

int main() {
    scanf("%d%d", &n, &m);
    ans = 1, res = 0;
    if (n < 0) n = -n, t = 1;
    init(), get();
    // a[++tot] = 0x3f3f3f3f;
    // dfs(1, n, 0);
    // if (n != 1) ans += m; //直接把 1 和 n 填进去, C(m, 1) = m
    // else ans++;
    
    for (int i = t; i <= m; i += 2) res += C(m, i);
    printf("%lld\n", ans * res);
    return 0;
}
```

---

## 作者：ZLCT (赞：0)

# [ARC004D] 表現の自由 ( Freedom of expression )
## 题目翻译
求 $m$ 个整数的排列使得乘积是 $n$ 的方案数。
## solution
该做法相比主流做法时间会差一些，但是思路较为自然。\
第一步是处理符号，$m$ 个数要使得答案为正/负数，那就取决于负号的奇偶性。上面题解写的用最后一个元素来调整是一种方法，但是不太容易想到。\
我们考虑直接根据奇偶性去枚举负号个数，假设现在枚举了 $i$ 个负号，分给 $m$ 个数的方案数就是 $\displaystyle\binom{m}{i}$，于是总的方案数就是
```math
\sum\limits_{i=[m\bmod{2}==1],i+=2}^{m}\binom{m}{i}
```
接下来我们考虑数字部分。\
观察到既然是乘积，那么其增长速度是很快的，若抛开非 $1$ 元素则至多由 $\log{n}$ 个元素组成。\
于是我们就可以根据使用元素个数进行 dp。\
我们设 $f_{i,j}$ 表示用 $i$ 个非 $1$ 元素构成 $j$ 的方案数，那么我们每次枚举它的非 $1$ 因数 $d$，转移就有 $f_{i,j}\leftarrow f_{i-1,\frac{j}{d}}$。\
最后我们去枚举有几个非 $1$ 元素，假设有 $x$ 个非 $1$ 元素，那么此时的方案数就是 $f_{x,n}$，而剩下的 $m-x$ 个 $1$ 我们可以看作是随便插入这 $x$ 数的中间。\
一共有 $x+1$ 个空，放入 $m-x$ 个 $1$，这是一个经典的插板法，方案数为 $\displaystyle\binom{m}{x}$。\
那这个题的复杂度不会爆炸吗？\
由于我们进行 dp 时用到的数都是 $n$ 的因数，所以我们至多进行 $d(n)$ 轮 dp。\
每轮 dp 我们都需要 $\sqrt{n}$ 的时间来枚举因数和 $d(n)\log{n}$ 的时间进行转移，当然也需要 $O(m)$ 的时间来预处理组合数，所以总时间复杂度为 $O(d(n)\times(\sqrt{n}+d(n)\log{n})+m)$。\
注意由于我们最后默认了插入的 $1$ 与前面构造 $n$ 的数不重复，所以当 $n=1$ 时会导致一开始的 $1$ 被认为是异类，这时候需要特判一下。
## code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+666;
const int mod=1e9+7;
const int maxn=1e5;
int ksm(int a,int b){
    int res=1;
    while(b){
        if(b&1){
            res=res*a%mod;
        }
        b>>=1;
        a=a*a%mod;
    }
    return res;
}
int n,m,A[N],invA[N],ans;
bool flag;
int C(int x,int y){
    if(x<y)return 0;
    return A[x]*invA[y]%mod*invA[x-y]%mod;
}
unordered_map<int,int>f[32];
unordered_map<int,bool>vis;
void dp(int x){
    if(vis[x])return;
    vis[x]=1;
    vector<int>vec;
    vec.push_back(1);
    for(int i=2;i*i<=x;++i){
        if(x%i)continue;
        dp(x/i);dp(i);
        vec.push_back(i);
        if(i!=x/i)vec.push_back(x/i);
    }
    for(int i=1;i<=30;++i){
        for(int j:vec){
            if(!f[i-1][j])continue;
            f[i][x]+=f[i-1][j];
            f[i][x]%=mod;
        }
    }
}
signed main(){
    cin>>n>>m;
    if(n<0){flag=1;n=-n;}
    A[0]=1;
    for(int i=1;i<=maxn;++i){
        A[i]=A[i-1]*i%mod;
    }
    invA[maxn]=ksm(A[maxn],mod-2);
    for(int i=maxn-1;i>=0;--i){
        invA[i]=invA[i+1]*(i+1)%mod;
    }
    ans=0;
    for(int i=flag;i<=m;i+=2){
        ans=(ans+C(m,i))%mod;
    }
    if(n==1){
        cout<<ans<<'\n';
        return 0;
    }
    f[0][1]=1;
    vis[1]=0;
    dp(n);
    int sum=0;
    for(int i=0;i<=30;++i){
        sum+=f[i][n]*C(m,i)%mod;
        sum%=mod;
    }
    cout<<ans*sum%mod<<'\n';
    return 0;
}
```

---

