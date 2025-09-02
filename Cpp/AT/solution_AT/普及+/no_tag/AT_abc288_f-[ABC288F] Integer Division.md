# [ABC288F] Integer Division

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc288/tasks/abc288_f

$ 10 $ 進表記で $ N $ 桁の正整数 $ X $ が与えられます。$ X $ の各桁は $ 0 $ ではありません。  
$ \lbrace\ 1,2,\ \ldots,\ N-1\ \rbrace $ の部分集合 $ S $ に対し、$ f(S) $ を以下のように定義します。

> $ X $ を $ 10 $ 進表記したものを長さ $ N $ の文字列とみなし、$ i\ \in\ S $ のとき、またそのときに限り文字列の $ i $ 文字目と $ i\ +\ 1 $ 文字目に区切りを入れることで $ |S|\ +\ 1 $ 個の文字列に分解する。  
> このようにして得られた $ |S|+1 $ 個の文字列を $ 10 $ 進表記された整数とみなし、$ f(S) $ をこれら $ |S|+1 $ 個の整数の積で定める。

$ S $ としてあり得るものは空集合を含めて $ 2^{N-1} $ 通りありますが、これら全てに対する $ f(S) $ の総和を $ 998244353 $ で割った余りを求めてください。

## 说明/提示

### 制約

- $ 2\ \leq\ N\ \leq\ 2\ \times\ 10^5 $
- $ X $ は $ 10 $ 進表記で $ N $ 桁で、各桁は $ 0 $ でない
- 入力はすべて整数

### Sample Explanation 1

$ S\ =\ \emptyset $ とすると、$ f(S)\ =\ 234 $ です。 $ S\ =\ \lbrace\ 1\ \rbrace $ とすると、$ f(S)\ =\ 2\ \times\ 34\ =\ 68 $ です。 $ S\ =\ \lbrace\ 2\ \rbrace $ とすると、$ f(S)\ =\ 23\ \times\ 4\ =\ 92 $ です。 $ S\ =\ \lbrace\ 1,\ 2\ \rbrace $ とすると、$ f(S)\ =\ 2\ \times\ 3\ \times\ 4\ =\ 24 $ です。 $ 234\ +\ 68\ +\ 92\ +\ 24\ =\ 418 $ であるため、$ 418 $ を出力します。

## 样例 #1

### 输入

```
3
234```

### 输出

```
418```

## 样例 #2

### 输入

```
4
5915```

### 输出

```
17800```

## 样例 #3

### 输入

```
9
998244353```

### 输出

```
258280134```

# 题解

## 作者：spider_oyster (赞：6)

考虑 DP，$f_{i}$ 表示考虑到 $X$ 的第 $i$ 位分法之和；

并设 $s(i,j)$ 表示 $X$ 的 $i$ 到 $j$ 位组成的数字。

则 $f_{i}=\sum_{j=0}^{i-1}f_{j} \times s(j+1,i)$。

但这样时间复杂度是 $n^2$ 的，所以得优化一下。

有求和，自然往前缀和上靠，又发现 $s(j+1,i)=s(j+1,i-1)\times10+X[i]$。

所以状态转移方程可以写成：
$f_{i}=\sum_{j=0}^{i-1}f_{j} \times s(j+1,i-1)\times 10+\sum_{j=0}^{i-1}f_{j}\times X_{i}$。

仔细观察前面那一项，当 $j=i-1$ 的时候，$s(j+1,i-1)=s(i,i-1)$，这种情况不存在，不用考虑，故：

$\sum_{j=0}^{i-1}f_{j} \times s(j+1,i-1)\times 10=\sum_{j=0}^{i-2}f_{j} \times s(j+1,i-1)\times 10=f_{i-1} \times 10$。

所以状态转移方程进一步写为：
$f_{i}=f_{i-1}\times 10+\sum_{j=0}^{i-1}f_{j}\times X_{i}$。

这道题就这么愉快的解决了！


```
#include<bits/stdc++.h>
#define F(i,s,t) for(register int i=(s);i<=(t);++i)
#define R(i,s,t) for(register int i=(s);i>=(t);--i)
#define ll long long
using namespace std;

const int N=2e5+15;
const int p=998244353;
int n;
ll f[N],sum;
char s[N]; 

int main()
{
	scanf("%d%s",&n,s+1);
	f[0]=1,f[1]=s[1]-'0';
	sum=f[0]+f[1];
	F(i,2,n)
	{
		f[i]=(f[i-1]*10%p+sum*(s[i]-'0')%p)%p;
		sum=(sum+f[i])%p;
	}
	cout<<f[n];
}
```


---

## 作者：FReQuenter (赞：4)

考虑 DP。

$f_i$ 表示当前看到第 $i$ 位的总和。

转移：

$$f_i=\sum^{i-1}_{j=1}f_j\times \overline{X_{j+1}X_{j+2}\dots X_{i}}$$

答案为 $f_N$，时间复杂度 $O(N^2)$。

考虑优化：

$$\begin{aligned}f_{i} & =\sum_{j=1}^{i-1}f_{j}\times\overline{X_{j+1}X_{j+2}\dots X_{i}} \\ &=\sum_{j=1}^{i-1} f_{j} \times(10\times \overline{X_{j+1}X_{j+2}\cdots X_{i-1}}+X_i) \\ &=10 \times f_{i-1}+X_i+X_i\times \sum_{j=1}^{i-1} f_{j} \end{aligned}$$

$\sum^{i-1}_{j=1}f_j$ 前缀和维护一下。

优化后时间复杂度 $O(N)$。

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 998244353
using namespace std;
signed main(){
  int n;
  string s;
  cin>>n>>s;
  int f=s[0]-48;int sum=f;
  for(int i=1;i<n;i++){
    f=f*10+s[i]-48+sum*(s[i]-48),f%=mod;
    sum+=f,sum%=mod;
  }
  cout<<f;
}
```

---

## 作者：CQ_Bab (赞：3)

# 前言
这道题因为取模问题，挂大分，请务必注意。
# 思路
~~看到取模一眼 Dp~~。我们定义 $f_i$ 为前 $i$ 个数能组成的所有得分。我们首先能想到一个 $n^2$ 的暴力，就是对于 $f_i=\sum\limits_{j=1}^{i-1}f_j\times \overline{c_{j+1}\cdots c_{i}}$ 然后我们就可以想一下如何优化，我们拿第一个样例打出来一个表可以发现一个规律。

- $f_1=2$。
- $f_2=f_1\times 3+23$。
- $f_3=f_1\times 34+f_2\times 4+234$

那么我们能发现一个规律，就是对于每一个 $f_i$ 都等于 $f_{i-1}$ 减去最后那个常数乘 $10$ 再加上自己的常数项和 $\sum\limits_{j=1}^{i-1}f_j\times c_i$ 这里一眼就可以用前缀和处理。最后答案即为 $f_n$。
# 代码
```cpp
#include <bits/stdc++.h>
#define IOS std::ios::sync_with_stdio(fasle);cin.tie(NULL);cout.tie(NULL)
#define int unsigned long long
#define ri register int
#define rep(i,x,y) for(ri i=x;i<=y;i++)
using namespace std ;
void print(int x) {
	if(x>=10) print(x/10);
	putchar(x%10+'0');
}
#define gcd(x,y) __gcd(x,y)
#define lcm(x,y) x*y/gcd(x,y)
int n;
char c[200100];
const int mod=998244353;
int f[200100];
int s[200100];
signed main() {
	cin>>n>>(c+1);
	f[1]=c[1]-'0';
	s[1]=f[1];
	int sum=(c[1]-'0');//初始化
	rep(i,2,n) {
		f[i]=((f[i-1]-sum+mod)%mod*10)%mod; //先将上一个减去常数项再乘上10
		sum=(sum*10+(c[i]-'0'))%mod;//更新当前组成的值
		f[i]=(f[i]+(s[i-1]*(c[i]-'0'))%mod+sum)%mod; //套公式
		s[i]=(s[i-1]+f[i])%mod; //更新前缀和
	}
	print(f[n]);
	return false;
}

```

---

## 作者：Hell0_W0rld (赞：3)

# [ABC288F](https://atcoder.jp/contests/abc288/tasks/abc288_f) Solution
\*2024。

在 F 里面蒜很简单的了。

感谢 @lnwhl 和 @Lloyd_Gabriel_Lmd 指出文中的错误。
## 题目大意
给定一个 $n$ 位数 $X$，把 $X$ 分成若干段，得分为每一段的乘积（可以不分割，得分为 $X$）。求所有分法得分之和，取模 $998244353$。
## 普通 dp
设 $\operatorname{f}(l,r)$ 表示 $X$ 的第 $l\sim r$ 位组成的数。例如 $X=114514$，则 $\operatorname{f}(2,4)=145,~\operatorname{f}(1,3)=114$。

设 $\mathrm{dp}_i $ 表示 $X$ 的前 $i$ 位进行切割之后，所有方法得分和。容易得到转移方程：

$$\mathrm{dp}_i=\sum^{i-1}_{j=0} \mathrm{dp}_j \times \operatorname{f}(j+1,i)$$

原因也很简单。枚举切割点 $j$，用乘法分配律即可轻松得到答案：前面分数和为 $\mathrm{dp}_j$，再乘上这次的数即可。最后求和。

但是这样复杂度为 $O(N^2)$，无法通过本题。
## 优化
我们可以观察 $\mathrm{dp}_i$ 和 $\mathrm{dp}_{i-1}$：
+ $\mathrm{dp}_i=\sum^{i-1}_{j=0} \mathrm{dp}_j \times \operatorname{f}(j+1,i)$；
+ $\mathrm{dp}_{i-1}=\sum^{i-2}_{j=0} \mathrm{dp}_j \times \operatorname{f}(j+1,i-1)$。

我们可以兴奋地发现，几乎全部一样！除了一些细微的变化。具体见下图。

注：表格二行二列因为 `0*10+2=2`，作者~~粗心大意~~笔误打错了。

![](https://cdn.luogu.com.cn/upload/image_hosting/0hmo510d.png)

其实我们发现，系数就是上一次系数乘 $10$，再加当前位数字！

所以：$\mathrm{dp}_i=\mathrm{dp}_{i-1} \times 10 + x_i\times\sum^{i-1}_{j=0} \mathrm{dp}_j$，其中 $x_i$ 表示 $X$ 的第 $i$ 位是几，用前缀和维护即可。

## 实现细节
其实只依赖于上一个，说明可以用变量来维护。在原有基础上修改即可。前缀和也用变量维护即可，因为只是单纯求 $\sum^{i-1}_{j=0} \mathrm{dp}_j$，而不求区间和。所以，**连数组都不用开**！

注意初始化为 $\mathrm{dp}_0=1$，输出 $\mathrm{dp}_n$。

记得取模。
## Code
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll MOD=998244353;
int main(){
	ll n;string x;
	cin>>n>>x; x=" "+x;
	ll ans=0,sum=1;
	for(ll i=1;i<=n;++i){
		ans=(ans*10%MOD+sum*(x[i]-'0')%MOD)%MOD;
		sum=(sum+ans)%MOD;
	}
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：SlyCharlotte (赞：1)

[或许更好的阅读体验](https://zhuanlan.zhihu.com/p/611682026)

## 题意描述

给定一个 $n$ 位数 $X$，把 $X$ 分成若干段，得分为每一段的乘积（可以不分割，得分为 $X$）。求所有分法得分之和，取模 $998244353$。

## 简要分析

考虑 dp。

$f_i$ 指到 $i$ 结尾的字符串的所有分法之和。

则有一下转移：
$$
f_i = \sum_{j = 1} ^{i-1}{f_j\times\overline{X_jX_{j+1}\dots X_i}} 
$$
不难发现是 $O(n^2)$ 复杂度。

然后通过推式子 + 前缀和可以做到 $O(n)$ 复杂度。

这里说明一种不同意义的转移方式。

观察到第 $i$ 个数的加入只有两种方法，一是按上未尾，二是以乘号相隔。

则有：
$$
f_i = f_{i-1} \times a_i 
$$
$$
f_i =g_{i-1} \times a_i + f_{i-1} \times 10 
$$

其中 $g_i$ 是指形似 $A \times B \times C$ 接上 $C$ 后，$g_i = g_{i-1} + f_{i-1}$。

## 代码实现

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>

using namespace std;

typedef long long ll;
const ll maxn = 2e5 + 7;
const ll INF = 1e9 + 7, MOD = 998244353;

inline ll read() {
    char cCc;
    ll xXx = 0, wWw = 1;
    while (cCc < '0' || cCc > '9')
        (cCc == '-') && (wWw = -wWw), cCc = getchar();
    while (cCc >= '0' && cCc <= '9')
        xXx = (xXx << 1) + (xXx << 3) + (cCc ^ '0'), cCc = getchar();
    xXx *= wWw;
    return xXx;
}

ll f[maxn], g[maxn];

signed main() {
//    freopen("code.in","r",stdin);
//    freopen("code.out","w",stdout);
    ll n = read();
    string s;
    cin >> s;
    f[0] = s[0] - '0', g[0] = 1;
    for (ll i = 1; i < n; i++) {
        f[i] = (f[i - 1] * 10 + g[i - 1] * (s[i] - '0')) % MOD;
        g[i] = g[i - 1] + f[i - 1];
        f[i] = (f[i] + f[i - 1] * (s[i] - '0')) % MOD;
    }
    cout << f[n - 1] << '\n';
    return 0;
}
```



---

## 作者：WaterSun (赞：0)

# 思路

定义 $dp_i$ 表示前 $i$ 位所能得到的答案。

那么，不难得出状态转移方程，其中 $X_{i,j}$ 表示 $X_{i,j}$ 转为的数字：

$$
dp_i = \sum_{j = 1}^{i - 1}(dp_j \times X_{j + 1 \sim i}) + X_{1,i}
$$

这样的时间复杂度为 $\Theta(n^2)$ 过不了，考虑用前缀和优化。

$$
\begin{aligned}
dp_i =& \sum_{j = 1}^{i - 1}(dp_j \times X_{j + 1,i}) + X_{1,i}\\
     =& \sum_{j = 1}^{i - 1}(dp_j \times (10 \times X_{j + 1,i - 1} + X_{i,i})) + X_{1,i}\\
     =& 10 \times dp_{i - 1} + X_{i,i} \times \sum_{j = 1}^{i - 1}(dp_j) + X_{1,i}
\end{aligned}
$$

然后用前缀和维护一下 $\sum_{j = 1}^{i - 1}(dp_j)$ 即可。

时间复杂度 $\Theta(n)$。

**注意：为了代码简介，我们规定 $dp_0 = sum_0 = 1$，这样就可以省去 $X_{1,i}$。因为每一次 $sum_i$ 都会多 $1$，加起来就正好为 $X_{1,n}$。**

# code

```cpp
#include <bits/stdc++.h>
#define int long long
#define re register

using namespace std;

const int N = 2e5 + 10,mod = 998244353;
int n;
int dp[N],sum[N];
string s;

signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> s;
	s = ' ' + s;
	dp[1] = s[1] - '0';
	sum[1] = dp[1] + 1;
	for (re int i = 2;i <= n;i++){
		dp[i] = (10 * dp[i - 1] + (s[i] - '0') * sum[i - 1]) % mod;
		sum[i] = (sum[i - 1] + dp[i]) % mod;
	}
	printf("%lld",dp[n]);
	return 0;
}
```

---

## 作者：CarroT5656 (赞：0)

**题目大意**

将一个长度为 $N$ 的正整数 $X$ 分割成若干块，得分为所有段的乘积。

求所有分割方法的得分的和，对 $998244353$ 取模。

**解题思路**

定义 $X[l..r]$ 表示 $X$ 第 $l$ 位到第 $r$ 位所表示的整数。

考虑 dp，列出转移方程。

* $dp_i$ 表示 $X$ 前 $i$ 位的得分的和。

* $dp_i=\sum\limits_{j=0}^{i-1}dp_j\times X[j+1..i]$

时间复杂度 $O(n^2)$，需要优化。

考虑拆开 dp 的转移方程。

$dp_i=\sum\limits_{j=0}^{i-1}dp_j\times X[j+1..i]$

$dp_i=\sum\limits_{j=0}^{i-1}dp_j\times (X[j+1..i-1]+X[i..i])$

$dp_i=10dp_{i-1}+(\sum\limits_{j=0}^{i-1}dp_j)\times X[i..i]$

用前缀和数组优化该 dp 即可。

时间复杂度 $O(n)$，可以通过。

**Code**

```cpp
#include<bits/stdc++.h>
#define ll long long
#define mod 998244353
#define N 200005 
using namespace std;
typedef pair<ll,ll> pll;
ll n,a[N],s[N]={1},dp[N]={1};
int main(){
    scanf("%lld",&n);
    for(ll i=1;i<=n;i++) scanf("%1lld",&a[i]);
    dp[1]=a[1],s[1]=a[1]+1;
    for(ll i=2;i<=n;i++){
        dp[i]=(10*dp[i-1]+a[i]*s[i-1])%mod;
        s[i]=(s[i-1]+dp[i])%mod;
    }
    printf("%lld\n",dp[n]%mod);
    return 0;
}
```

---

## 作者：qzhwlzy (赞：0)

### 题目大意

给定 $n$ 位数 $X$，求把 $X$ 分成若干段的所有方案中，所有段的乘积之和。

~~赛时感觉这题比 E 简单~~

### 思路

考虑按照数位从前往后 DP。记 $f_i$ 表示 $X$ 的前 $i$ 位的答案。考虑如何从 $f_{i-1}$ 转移到 $f_i$（假设 $X$ 的前 $i$ 位为 $a_1,a_2,\ldots,a_{i-1},a_i$），包含 $a_i$ 的划分为：$a_1\ a_2\ \ldots\ a_{j-1}\ /\ a_j\ a_{j+1}\ \ldots\ a_i$（$a_1\sim a_{j-1}$ 也有划分，这里没有体现），那么，答案应为：

$$
f_{j-1}\times (\overline{a_j\,a_{j+1}\,\ldots\,a_{i-1}}\times 10 + a_i) = f_{j-1}\times \overline{a_j\,a_{j+1}\,\ldots\,a_{i-1}}\times 10 + f_{j-1}\times a_i
$$

那么，枚举所有的 $j$，最终的答案为：

$$
f_i = f_{i-1}\times 10 + \sum\limits_{j=1}^{i-1} f_j\times a_i
$$

其中 $\sum\limits_{j=1}^{i-1} f_j$ 可以用前缀和维护掉，最终复杂度 $\mathcal{O}(n)$。

```cpp
#include<iostream>
#include<cstdio>
#define maxn 200005
#define mod 998244353
#define ll long long
using namespace std;
int n; char a[maxn]; ll f[maxn],pre[maxn];
int main(){
      cin>>n>>a+1; f[1]=1LL*(a[1]-'0'); pre[1]=1LL;
      for(int i=2;i<=n;i++){
            pre[i]=(pre[i-1]+f[i-1])%mod;
            f[i]=(f[i-1]*10LL%mod+pre[i]*(a[i]-'0')%mod)%mod;
      }
      printf("%lld",f[n]%mod);
      return 0;
}
```

---

## 作者：AlicX (赞：0)

### 前言 

十分经典的一道题，原型是将一个数分成 $k$ 组，求乘积，其中 $k$ 是一个定值，是一道非常简单的题。此题与它的区别就是并未给定一个  $k$，解决方案同样简单，只需要进行分类讨论即可。

## Solution

可以十分轻松地看出此题是一道 DP，定义 $f_i$ 表示前 $i$ 个元素分段后所得的总的乘积和。接下来考虑转移，暴力转移非常显然，枚举上一个分界点 $j$，$f_i=f_i+f_j \times get(j+1,i)$，$get(x,y)$ 表示第 $x$ 位到第 $y$ 位的数字，时间复杂度为 $O(n^2)$。

考虑优化这个式子，展开式子可以发现：每一项都含有 $f_j \times a_i$，把它用前缀和优化掉，接下来就只剩 $f_j \times get(j+1,i-1)$，每次更新 $f_i$ 时，都让这个东西乘上 $10$，再加上第 $i$ 的贡献 $a_i$，就可以将它也用前缀和优化掉。

注意，本文的代码用了两个前缀和，读者可以继续退式子，是可以推到一个前缀和的做法的。细节见代码。

```cpp
#include<bits/stdc++.h> 
#define int long long 
#define x first 
#define y second
#define il inline
#define debug() puts("-------") 
using namespace std; 
typedef pair<int,int> pii; 
const int N=2e5+10,Mod=998244353,INF=1e9+7; 
int n; 
int a[N];
int f[N],g[N]; 
int s1[N],s2[N]; 
signed main(){ 
	cin>>n; 
	for(int i=1;i<=n;i++){ 
		char c; cin>>c; 
		a[i]=c-'0'; 
	} f[1]=a[1]; s1[1]=a[1]; int lst=a[1]; 
	for(int i=2;i<=n;i++){ 
		lst=(lst*10+a[i])%Mod; 
		f[i]=(lst+a[i]*s1[i-1])%Mod; 
		f[i]=(f[i]+s2[i-1]*10)%Mod; 
		s1[i]=(s1[i-1]+f[i])%Mod; 
		s2[i]=(s2[i-1]*10+s1[i-1]*a[i])%Mod; 
	} cout<<f[n]%Mod<<endl; 
	return 0; 
} /*
3
234

4
5915

*/
```


---

