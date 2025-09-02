# Anton and School - 2

## 题目描述

As you probably know, Anton goes to school. One of the school subjects that Anton studies is Bracketology. On the Bracketology lessons students usually learn different sequences that consist of round brackets (characters "(" and ")" (without quotes)).

On the last lesson Anton learned about the regular simple bracket sequences (RSBS). A bracket sequence $ s $ of length $ n $ is an RSBS if the following conditions are met:

- It is not empty (that is $ n≠0 $ ).
- The length of the sequence is even.
- First ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to "(".
- Last ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF785D/666f6519688863e0a36337875170dd12050e1c31.png) charactes of the sequence are equal to ")".

For example, the sequence "((()))" is an RSBS but the sequences "((())" and "(()())" are not RSBS.

Elena Ivanovna, Anton's teacher, gave him the following task as a homework. Given a bracket sequence $ s $ . Find the number of its distinct subsequences such that they are RSBS. Note that a subsequence of $ s $ is a string that can be obtained from $ s $ by deleting some of its elements. Two subsequences are considered distinct if distinct sets of positions are deleted.

Because the answer can be very big and Anton's teacher doesn't like big numbers, she asks Anton to find the answer modulo $ 10^{9}+7 $ .

Anton thought of this task for a very long time, but he still doesn't know how to solve it. Help Anton to solve this task and write a program that finds the answer for it!

## 说明/提示

In the first sample the following subsequences are possible:

- If we delete characters at the positions $ 1 $ and $ 5 $ (numbering starts with one), we will get the subsequence "(())".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 3 $ and $ 4 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 2 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 4 $ and $ 5 $ , we will get the subsequence "()".
- If we delete characters at the positions $ 1 $ , $ 3 $ , $ 5 $ and $ 6 $ , we will get the subsequence "()".

The rest of the subsequnces are not RSBS. So we got $ 6 $ distinct subsequences that are RSBS, so the answer is $ 6 $ .

## 样例 #1

### 输入

```
)(()()
```

### 输出

```
6
```

## 样例 #2

### 输入

```
()()()
```

### 输出

```
7
```

## 样例 #3

### 输入

```
)))
```

### 输出

```
0
```

# 题解

## 作者：_Life_ (赞：15)

### 题意
给定由 `(` 与 `)` 组成的括号序列，求前半部分为 `(` 后半部分为 `)` 的子序列数量。$len \le 2\times10^5$

### 题解
因为要保证求出的子序列不重不漏，想到枚举最后一个 `(` 并强制选取。

假设这个 `(` 左边（包括自己）有 $a$ 个 `(`，右边有 $b$ 个 `)`，则对答案的贡献为 $\sum_{i=0}^{\min(a-1,b-1)}C_{a-1}^{i}\cdot C_b^{i+1}$

如果直接这样算，时间复杂度是 $O(n^2)$ 的，显然过不了。复杂度瓶颈在贡献的计算，所以我们祭出**范德蒙德卷积公式**进行优化。范德蒙德卷积公式本体：

$$\sum_{i=0}^kC_n^i\cdot C_m^{k-i}=C_{n+m}^k$$

感性证明一下：在大小为 $n$ 和 $m$ 的两堆东西里选 $k$ 个，得到左边的柿子和右边的柿子，所以等价。

发现范德蒙德卷积公式和计算贡献的那坨柿子很像，魔改一下：
$$\sum_{i=0}^{\min(a-1,b-1)}C_{a-1}^{i}\cdot C_b^{i+1}=\sum_{i=0}^{\min(a-1,b-1)}C_{a-1}^{a-1-i}\cdot C_b^{i+1}=C_{a+b-1}^{a}$$

然后这道题就做完了。

示例代码用了线性求阶乘逆元 时间复杂度 $O(n)$

### 代码
```cpp
#include<cstdio>
#include<cstring>
#define int long long
#define mod 1000000007
using namespace std;
int n,x[200005],y[200005],fac[200005],inv[200005],ans;
char str[200005];
int fastpow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1)
			ans=ans*a%mod;
		b>>=1;
		a=a*a%mod;
	}
	return ans;
}
int C(int n,int m){return fac[n]*inv[m]%mod*inv[n-m]%mod;}
signed main()
{
	scanf("%s",str+1);
	n=strlen(str+1);
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=fac[i-1]*i%mod;
	inv[n]=fastpow(fac[n],mod-2);
	for(int i=n-1;i>=0;i--)inv[i]=inv[i+1]*(i+1)%mod;
	for(int i=1;i<=n;i++)x[i]=x[i-1]+(str[i]=='(');
	for(int i=n;i>=1;i--)y[i]=y[i+1]+(str[i]==')');
	for(int i=1;i<=n;i++)
		if(str[i]=='(')
			ans=(ans+C(x[i]+y[i]-1,x[i]))%mod;
	printf("%lld",ans);
}
```

---

## 作者：YuntianZhao (赞：5)

# CF785D

$a$ 是从前往后数到 $i$ 时（的数量， $b$ 时从后往前数到 $i$ 时）的数量。

若答案中的最后一个（出现在第i位时，此时会有：

$ans = \sum _ { i = 1} ^ {str\_len} \sum _ {x = 0} ^ {\min(a _ i - 1, b _ i - 1)} C _ {a _ i - 1} ^ {x} \cdot C _ {b_i} ^ {x + 1}$

这玩意等价于：

$\sum _ {i = 1} ^ {str\_len} C _ {a _ i + b _ i - 1} ^ {a _ i}$

然后对于组合数取模有一个优化：

$C_{n}^{m} \% p = (m!(n-m)!)^ {p - 2} \% p$

之后就可以用快速幂来求解。

复杂度 $O(N \log P)$，其中$P = 1e9 + 7$

```c++
#include <bits/stdc++.h>
using namespace std;

const int maxn = 200005;

const int mod = 1e9 + 7;

long long a[maxn], b[maxn], fact[maxn];
string s;

long long power(long long x, int n){
  long long ans = 1;
  while (n) {
    if (n & 1) ans = ans * x % mod;
    x = x * x % mod;
    n >>= 1;
  }
  return ans;
}

int main() {
  long long ans = 0;
  cin >> s;
  if (s[0] == '(') a[0] = 1;
  int str_len = s.size();
  for (int i = 1; i < str_len; i++) {
    if (s[i] == '(') a[i] = a[i - 1] + 1;
    else a[i] = a[i - 1];
  }
  for (int i = str_len - 1; i >= 0; i--) {
    if (s[i] == ')') b[i] = b[i + 1] + 1;
    else b[i] = b[i + 1];
  }
  fact[0] = 1;
  for (int i = 1; i < maxn; i++) {
    fact[i] = fact[i - 1] * i % mod;
  }
  for (int i = 0; i < str_len; i++) {
    if (s[i] == ')') continue;
    long long cnt1 = a[i], cnt2 = a[i] + b[i] - 1;
    ans = (ans + (fact[cnt2] * power(fact[cnt1] * fact[cnt2 - cnt1] % mod, mod - 2)) % mod) % mod;
//    cout << ans << " ";
  }
  cout << ans << endl;
  return 0;
}

```

---

## 作者：是个汉子 (赞：3)

### Solution

这个题经过一番思考，发现前面一位和后面一位之间是不会相互影响的，也就是各自的**贡献**是独立算的。

那我们就直接通过一些排列组合的方式来求出答案即可。

刚刚我提到了贡献，所以我们可以对这个括号序列的每一位进行计算，最后相加。然后发现因为他们是成对匹配的，当你算左括号的时候，右括号已经被算了一遍，算右括号的时候，左括号被算了一次，会重复计算。那么就只考虑左括号就行了。

记录当前位左边有多少左括号（包括自己），右边有多少右括号，设有 $a$ 个左括号， $b$ 个右括号，那么满足条件的子串会多 $C_{a-1}^0C_b^1+C_{a-1}^1C_b^2+\cdots+C_{a-1}^xC_{b}^{x+1}+\cdots=\sum\limits_{i=0}^{\min(a-1,b-1)}C_{a-1}^xC_b^{x+1}$ 。

然后有个神奇的东西叫**范德蒙德卷积**，它是长这个样子的： $\sum\limits_{i=0}^kC_n^iC_m^{k-i}=C_{n+m}^k$ 。

原题中的式子我们也可以类似的转化： $\sum\limits_{i=0}^{\min(a-1,b-1)}C_{a-1}^xC_b^{x+1}=\sum\limits_{i=0}^{\min(a-1,b-1)}C_{a-1}^{a-x-1}C_b^{x+1}=C_{a+b-1}^a$ 。

呜呼，那么我们只要预处理出每一位的左括号，右括号和组合数就好了。

时间复杂度： $O(len_s)$ 

### 代码

```c++
#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#define ll long long

using namespace std;
const int N=200010,mod=1e9+7;
char s[N];
int l[N],r[N];
ll ans,fac[N],inv[N];

ll fpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1) res=res*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return res;
}

inline void init(){
    fac[0]=1;
    for(int i=1;i<=200000;i++) fac[i]=fac[i-1]*i%mod;
    inv[200000]=fpow(fac[200000],mod-2);
    for(int i=200000;i>=1;i--) inv[i-1]=inv[i]*i%mod;
}

inline ll C(ll n,ll m){
    if(n<m) return 0;
    return fac[n]*inv[n-m]%mod*inv[m]%mod;
}

int main(){
    init();
    scanf("%s",s+1);
    int len=strlen(s+1);
    for(int i=1;i<=len;i++)
        l[i]=(s[i]=='('?l[i-1]+1:l[i-1]);
    for(int i=len;i>=1;i--)
        r[i]=(s[i]==')'?r[i+1]+1:r[i+1]);
    for(int i=1;i<=len;i++)
        if(s[i]=='(') ans=(ans+C(l[i]+r[i]-1,l[i]))%mod;
    printf("%lld\n",ans);
    return 0;
}
```



---

## 作者：TTpandaS (赞：2)

对于每个左括号，我们都把它作为子序列中最后一个左括号，这样可以保证子序列一定不会被重复计算。

枚举其左侧选出 $j$ 个左括号，那么右侧就需要 $j+1$ 个右括号，所以能组成的子序列数量为

$$ \sum_{i=1}^{n}\sum_{j=0}^{\min(L_i,R_i-1)} C_{L_i}^{j} C_{R_i}^{j+1} $$

其中 $L_i$ 表示第 $i$ 个位置前左括号的数量，$R_i$ 表示第 $i$ 个位置后右括号的数量。

这样的表达式时间复杂度为 $n^2$，不可过此题。

我们将表达式转换为

$$ \sum_{i=1}^{n}\sum_{j=0}^{\min(L_i,R_i-1)} C_{L_i}^{L_i-j} C_{R_i}^{j+1} $$

那么我们可以将 $C_{L_i}^{L_i-j}$ 视作在 $L_i$ 个女孩中选择 $L_i-j$ 个作为女朋友的方案数，将 $C_{R_i}^{j+1}$ 视作在 $R_i$ 个女孩中选择 $j+1$ 个作为女朋友的方案数。

可以发现最终选择的女朋友数始终为定值 $L_i+1$，而总的女孩数为 $L_i+R_i$ 个，所以我们可以把 

$$\sum_{j=0}^{\min(L_i,R_i-1)} C_{L_i}^{L_i-j} C_{R_i}^{j+1} $$

视作在 $L_i+R_i$ 个女孩中选择 $L_i+1$ 个作为女朋友的方案数，也就等于

$$ C_{L_i+R_i}^{L_i+1}$$

所以表达式可以转换为

$$ \sum_{i=1}^{n} C_{L_i+R_i}^{L_i+1} $$

可以 $O(n)$ 解决。

以上所写的恒等式可以写成一般化形式

$$ \sum_{i=0}^{n} C_{n}^{i} C_{m}^{k-i} = C_{n+m}^{k} $$

这也称为 范德蒙德恒等式。

---

## 作者：OIerBoy (赞：2)

# 前置知识
范德蒙德卷积公式：$\sum\limits_{i=0}^kC_{n}^{i}\times C_{m}^{k-i}=C_{n+m}^k$。

至于证明请看此篇[文章](https://www.luogu.com.cn/blog/foreverlasting/yi-lei-heng-deng-shi-di-ying-yong-zha-shi-liao-zha-shi-liao-post)。

# Sol
我们这道题很明显就要从 $\begin{matrix}\underbrace{(((\cdots (((}\\k\end{matrix} \begin{matrix}\underbrace{)))\cdots )))}\\k\end{matrix}$ 这里入手，不然的话题目完全可以叫你保证括号合法就行了。

这样我们就可以发现序列的前后是不会互相影响的，即可以独立的计算贡献，而为了保证不去重复计算答案，我们只需要去考虑计算左括号的贡献就行了。

当前位置为 ```(``` 时，定它作为最右边的左括号，记左边有 $a$ 个左括号，右边有 $b$ 个右括号，则当前对答案的贡献为：$\sum\limits_{i=0}^{\min(a-1,b-1)}C_{a-1}^i\times C_{b}^{i+1}$。但只是这个式子不足以让我们通过这道题，时间复杂度是 $O(n^2)$ 的。

这时，我们就需要用到上面的范德蒙德卷积公式了。

$$\sum\limits_{i=0}^kC_{n}^{i}\times C_{m}^{k-i}=C_{n+m}^k$$

可以发现我们推出来的式子很像范德蒙德卷积公式，这样我们就可以对式子进行化简了。

$$\begin{aligned}& \sum\limits_{i=0}^{\min(a-1,b-1)}C_{a-1}^i\times C_{b}^{i+1}\\ =& \sum\limits_{i=0}^{\min(a-1,b-1)}C_{a-1}^{a-1-i}\times C_{b}^{i+1}\\ = & C_{a+b-1}^a\end{aligned}$$

这样我们只需要预处理一下 $1\sim i$ 出现过的左括号记为 $l_i$，$i\sim n$ 出现过的右括号记为 $r_i$ 就可以了。

# Code
```cpp
#include<bits/stdc++.h>
#define db doub
#define int long long
#define inf LONG_LONG_MAX
#define fir first
#define sec second
#define ls (x<<1)
#define rs (x<<1|1)
#define mid ((l+r)>>1)
#define Pr(i,j) pair<i,j>
#define PB(i) push_back(i)
#define MP(i,j) make_pair(i,j)
#define Fo(i,j) for(auto i:j)
#define mem(i,j) memset(i,j,sizeof(i))
#define FO(i,j,k) for(int i=j;i;i=k)
#define FFF(i,j,k) for(auto i=j;i!=k;++i)
#define For(i,j,k) for(int i=j;i<=k;++i)
#define FoR(i,j,k) for(int i=j;i^k;++i)
#define FOR(i,j,k) for(int i=j;i>=k;--i)
using namespace std;
template <typename _Tp>void read(_Tp& first) {
    _Tp x = 0, f = 1; char c = getchar();
    while (!isdigit(c)) {if (c == '-') f = -1; c = getchar();}
    while (isdigit(c)) x = (x << 3) + (x << 1) + (c ^ '0'), c = getchar();
    first = x * f;
}
#define N 200005
#define Mod 1000000007
int n,ans,l[N],r[N];
int fac[N],inv[N];
char a[N];
int ksm(int a,int b){
    int res=1;
    while(b){
        if(b&1)res=res*a%Mod;
        a=a*a%Mod;
        b>>=1;
    }return res;
}
int C(int n,int m){
    return fac[n]*inv[n-m]%Mod*inv[m]%Mod;
}
void into(){
    fac[0]=1;
    For(i,1,n)fac[i]=fac[i-1]*i%Mod;
    inv[n]=ksm(fac[n],Mod-2);
    FOR(i,n-1,0)inv[i]=inv[i+1]*(i+1)%Mod;
}
signed main(){
    cin>>a+1;n=strlen(a+1);into();
    For(i,1,n)l[i]=l[i-1]+(a[i]=='(');
    FOR(i,n,1)r[i]=r[i+1]+(a[i]==')');
    For(i,1,n)if(a[i]=='(')
        ans=(ans+C(l[i]+r[i]-1,l[i]))%Mod;
    cout<<ans;
    return 0;
}
```

---

## 作者：1沃尔克 (赞：2)

首先想到爆搜。
简单好打分又少。

因为要求选成对括号，考虑组合数。

从左向右枚举，当我们枚举到一个左括号时，在他左边（包括自身）选出n个左括号，在他右边选出m个右括号此时答案为

for(int i=1;i<=min(n,m);i++)
c(i-1,n-1)*C(i,m)

假设你n<=m

可以写成
for(int i=1;i<=n;i++)C(i-1,n-i)*C(i,m)
<=>C(n-i,n-1)*C(i,m)

因为C(n,n-1)=0;
又<=>for(int i=0;i<=n;i++)C(n-i,n-1)*C(i,m)

相当于从n+m+1个中选n个即：C(n,n+m-1)

局势就明了啦。
```cpp
#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#define Mod 1000000007
using namespace std;
int fpow(int a,int b)
{
	int ans=1,t=a;
	while(b)
	{
		if(b&1)ans=(long long)ans*t%Mod;
		t=(long long)t*t%Mod;
		b>>=1;
	}
	return ans;
}
int fac[200010],inv[200010];
int n;
char st[200010];
int suf[200010];
int main()
{
	scanf("%s",st+1);
	n=strlen(st+1);
	fac[0]=1;
	for(int i=1;i<=n;i++)fac[i]=(long long)fac[i-1]*i%Mod;
	inv[n]=fpow(fac[n],Mod-2);
	for(int i=n;i>=1;i--)inv[i-1]=(long long)inv[i]*i%Mod;
	for(int i=n;i>=1;i--)
		if(st[i]==')')suf[i]=suf[i+1]+1;
		else suf[i]=suf[i+1];
	int pre=0,ans=0;
	for(int i=1;i<=n;i++)
		if(st[i]=='(')
		{
			pre++;
			ans=(ans+(long long)fac[pre-1+suf[i]]*inv[pre]%Mod*inv[suf[i]-1]%Mod)%Mod;
		}
	printf("%d\n",ans);
	fclose(stdin);fclose(stdout);
	return 0;
}
```


---

## 作者：Last_Reincarnation (赞：2)

[题面传送门](https://www.luogu.org/problem/CF785D)

~~本题是我们$hdyz$模拟的一道题~~

### 一.部分分数思路

首先说一下部分得分,我的考场~~骗分~~思路:

**1.对于20%的数据，满足$len ≤ 20$；**


**2.对于另外20%的数据，保证存在一个x，使得前x个括号都是左括号，后$len - x$个括号都是右括号，括号序列长这个样子$(((...((())...)))$**

这四十分只要稍加思考就可以拿到。

题意是让删除若干个，使其左面全是$‘（’$， 右面全是$‘）’$，我们可以考虑有多少个可以匹配

首先考虑 $2.$另外的$20%$的数据，因为是特殊情况，我们可以考虑不删除，考虑匹配，有多少个可以匹配。

l为‘(’个数， r 为‘)’ 个数

则答案为 $\sum\limits_{i=1}^{min(l,r)}C_l^i*C_r^i$

这个应该很好理解，就是在分界线左面选i个，右边也选i个，将答案相乘，就是有i个成功匹配的答案。

然后 1. $len ≤ 20$ 就是大法师爆搜呗，然后这道题就可以成功$40$分啦。

$40pt$  $code$(养成先看主函数的情况)

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define int long long
#define Re register
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 2 * 1e5 + 10;

int l, r, len, qwq, qaq, hehe, rht;
char z[maxn];
long long res, ans;
long long jc[maxn], inv[maxn];

int f_;
char ch_;
template <class T>
	T read(T &x_){
		x_ = 0, f_ = 1, ch_ = getchar();
		while (ch_ < '0' || ch_ > '9'){if (ch_ == '-') f_ = -1; ch_ = getchar();}
		while (ch_ >= '0' && ch_ <= '9') x_ = (x_ << 3) + (x_ << 1) + ch_ - 48, ch_ = getchar();
		return x_ *= f_;
	}

inline int Max (int x, int y){return (x > y) ? x : y;}

inline int Min (int x, int y){return (x < y) ? x : y;}

long long Power (long long a, int b){
	res = 1;
	for (; b;b >>= 1){
		if (b & 1) res = (res * a) % mod;
		a = (a * a) % mod;
	}
	return res % mod;
}//快速幂不用说吧？ 

void pre_work(){
	qwq = Max(l, r);
	jc[1] = 1;
	jc[0] = 1; 
	for (Re int i = 2;i <= qwq; ++i) jc[i] = jc[i-1]*i % mod;// 处理阶乘 
	inv[1] = 1;
	inv[0] = 1;//一定记得处理0的逆元 ,和0的阶乘 
	for (Re int i = 2;i <= qwq; ++i) inv[i] = Power (jc[i], mod-2) % mod;//处理阶乘的逆元 
}

namespace subtask1{
	int prel[maxn];
	int prer[maxn];
	void Pre_work(){ // 处理前缀和 
		for (Re int i = 1;i <= len; ++i){
			if (z[i] == '('){
				prel[i] = prel[i-1] + 1;
				prer[i] = prer[i-1];
			}
			else {
				prer[i] = prer[i-1] + 1;
				prel[i] = prel[i-1];
			}
		}
		for (Re int i = 1;i <= len; ++i){
			if (z[i] == '(')
				ans += prer[len]-prer[i];
		}
		if (ans == 0){
			printf ("0\n");
			exit(0);
		}
	}
	void Dfs (int x, int sum){//大爆搜。。。。 
		if (prer[len]-prer[x] < sum) return;
		if (sum == rht){
			if (prer[len]-prer[x] >= sum) {
				hehe = prer[len]-prer[x];
				ans = (ans + (((jc[hehe]  * inv[sum]) % mod) * inv[hehe-sum]) % mod) % mod;
			}
			return;
		}
		for (Re int i = x + 1;i <= len; ++i){
			if (z[i] == ')') continue;
			Dfs(i, sum+1);
		}
	}
}

signed main(){
//	freopen ("beauty.in", "r", stdin);
//	freopen ("beauty.out", "w", stdout);
	cin >> (z + 1);
	len = strlen(z + 1);
	for (Re int i = 1;i <= len; ++i){
		if (z[i] == '(') ++l;
		else break;
	}//处理2.的分，左边括号数量 
	for (Re int i = len;i >= 1; --i){
		if (z[i] == ')') ++r;
		else break;
	}//右面括号数量 
	if (l+r == len){//如果左边 + 右边 == len ， 就可以骗分了！！！ 
		pre_work();
		qwq = Min (l, r);//要到min(l, r); 
		for (Re int i = 1;i <= qwq; ++i){//下面是上面我说的公式 
			qaq = ((((jc[l]*inv[i]) % mod)*inv[l-i])%mod) * ((((jc[r]*inv[i])%mod)*inv[r-i])%mod);
			ans = (ans + qaq) % mod;
		}
		ans %= mod;
		printf ("%lld\n", ans);
	}
	else {// len <= 20;
		l = r = 0;
		for (Re int i = 1;i <= len; ++i){
			if (z[i] == '(') ++l;
			else ++r;
		}//处理总的l 和 r的数量 
		pre_work(); //处理阶乘 和 阶乘的逆元 
		using namespace subtask1;
		Pre_work(); // 处理suml[] 和sumr[],在我这里数组名字叫prel[] prer[] 
		rht = 2;  // 然后下面就开始大爆搜了 (应该不会有人抄吧，我就不解释了，应该都能写出来爆搜)
		qwq = Min (l, r);
		while (rht <= qwq){
			for (Re int i = 1;i <= len; ++i){
				if (prer[len] - prer[i] < rht) break;
				if (z[i] == ')') continue;
				Dfs (i, 1);
			}
			++rht;
			ans %= mod;
		}
		printf ("%lld\n", ans);
	}
	return 0;
}
```

### 2.正解具体思路

然后开始正解部分

我们可以枚举左右括号的长度i进行计算。假设左半部分长度为
$n$，右半部分长度为$m$， 先假设$n <= m$, 最终答案为
 $ \sum\limits_{i=1}^{n}C_n^i*C_m^i$ 
 然后枚举每一个空隙，但是这样答案会错，因为会被重复计算(应该可以想到吧)然后我考试想到这里就没招了（只能乖乖骗分和暴力），但是 其实已经距离正解不远了。
 
 正解就是变一下枚举空隙为枚举左扩号
 
 我们枚举左括号时，设当前左边左括号数为$n$（包括它自己）， 右边右号数为m，此时答案为
 
 $ \sum\limits_{i=1}^{min(n,m)}C_{n-1}^{i-1}*C_m^i$ 
 （这样不会重复，因为每到一个左括号，这个左括号必选，然后再前面选$i-1$个,不懂的思考一下一定可以明白）
 
 依旧，设$n <= m$，则式子可以写成 $ \sum\limits_{i=1}^{n}C_{n-1}^{n-i}*C_m^i$ 
 
若i = 0，$C_{n-1}^{n} = 0$ ,所以式子可以变为 $ \sum\limits_{i=0}^{n}C_{n-1}^{n-i}*C_m^i$ 
 
 这个式子等价于在左右$n-m+1$个东西中，一共选出$n$个，也就是说，这个式子整体就等于$ C_{n+m-1}^{n}$，然后枚举每一个左括号的位置时，答案就可以O（1）计算了
 
 这里的复杂度O(n),加上预处理的时间大概是$n logn$
 
 上面懂啦，代码就很简单了，相信大家不成问题
 
 $code$
 
 ```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define int long long
#define Re register
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 2*1e5+ 10;

int l, r;
int res, ans, len;
int QwQ, QaQ;
int suml[maxn], sumr[maxn];
int jc[maxn], inv[maxn];
char z[maxn];

inline int Max (int x, int y){return (x > y) ? x : y;}

inline int Min (int x, int y){return (x < y) ? x : y;}

int Power (int a, int b){
	res = 1;
	for (; b; b>>= 1){
		if (b & 1) res = (res * a) % mod;
		a = (a * a) % mod;
	}
	return res % mod;
}//快速幂，求逆元用的

void Pre_work (){
	jc[1] = 1; jc[0] = 1;
	for (Re int i = 2;i <= len; ++i) jc[i] = jc[i-1] * i % mod;
	inv[1] = 1; inv[0] = 1;
	for (Re int i = 2;i <= len; ++i) inv[i] = Power (jc[i], mod-2) % mod;
}//处理阶乘 和 阶乘的逆元

signed main(){
	cin >> (z + 1);
	len = strlen(z + 1);
	for (Re int i = 1;i <= len; ++i){
		if (z[i] == '('){
			suml[i] = suml[i-1] + 1;
			sumr[i] = sumr[i-1];
			++l;
		}
		else {
			suml[i] = suml[i-1];
			sumr[i] = sumr[i-1] + 1;
			++r;
		}
	}//处理前缀和
	Pre_work();
	for (Re int i = 1;i <= len; ++i){
		if (z[i] == ')') continue;//枚举每个左括号
		QwQ = suml[i];
		QaQ = sumr[len] - sumr[i];
		ans = (ans + (((jc[QwQ+QaQ-1]  % mod) * inv[QwQ]) % mod) * inv[QaQ-1] % mod) % mod;//公式
	}
	cout << ans ;
	return 0;
}
```
祝大家$cps2019$,  $Rp++$;









---

## 作者：loceaner (赞：1)

$20$分：

暴搜，只能从左往右搜，所以记录一下上次用的是哪一个，这次枚举直接从上次用的下一个开始枚举，保证从左往右

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

const int A = 1e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;

inline int read() {
	char c = getchar();
	int x = 0, f = 1;
	for( ; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for( ; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}

int n, m, ans, vis[A], a[A];
char s[A];
int c[4000][4000];

void dfs(int cnt, int last) {
	if(cnt > n + 1) return;
	if((cnt - 1) % 2 == 0 && cnt - 1 != 0) {
		int now = cnt - 1;
		int zuo = 0, you = 0, cao = 0;
		for(int i = 1; i <= now / 2; i++) {
			if(a[i] == 2) {
				cao = 1;
				break;
			}
			if(a[i] == 1) zuo++;
		}
		for(int i = now / 2 + 1; i <= now; i++) {
			if(a[i] == 1) {
				cao = 1;
				break;
			}
			if(a[i] == 2) you++;
		}
		if(!cao && zuo == you && zuo + you == now) ans++;
	}
	for(int i = last + 1; i <= n; i++) {
		if(!vis[i]) {
			vis[i] = 1;
			a[cnt] = (s[i] == '(' ? 1: 2);
			dfs(cnt + 1, i);
			vis[i] = 0;
		}
	}
}

signed main() {
	freopen("beauty.in", "r", stdin);
	freopen("beauty.out", "w", stdout);
	scanf("%s", s + 1);
	n = strlen(s + 1);
	if(n <= 20) {
		dfs(1, 0);
		cout << ans % mod << '\n';
		return 0;
	}
	return 0;
}
```

$50$分：

考虑每个左括号，不包括他的，左边有多少个左括号，右边有多少个右括号，就可以得出，对于每一个左括号的位置，都有：（$x$是指左边不包括这个左括号有多少个左括号，$y$是右边有多少个右括号）

$$\sum_{i = 0}^{x} C(x, i) * C(y, i + 1)$$

然后就有$50$了

$100$分：

考虑直接换一种想法，我们枚举包括这个位置的左括号的，左边有多少个左括号，右边有多少个右括号，这个位置必须选，那么就能得出

$$\sum_{i = 1}^{x} C(x, i) * C(y, i)$$

但是这样就会把不选这个位置的情况算上，所以还要减去

$$\sum_{i = 1}^{x} C(x - 1, i) * C(y, i)$$

就得出了
$$\sum_{i = 1}^{x} C(x, i) * C(y, i) - \sum_{i = 1}^{x} C(x - 1, i) * C(y, i) $$

有一个辅助式子

$$\sum_{i = 0}^{x} C(x, i) * C(y, i) = C(x + y, x)$$

所以上面的式子就能写成

$$(C(x + y, x) - 1 )- ( C(x + y - 1, x - 1) - 1)$$

就等于

$$C(x + y, x) -  C(x + y - 1, x - 1) $$

对于每个左括号的位置，我们都这样计算一遍，然后就做完了

时间复杂度$O(n)$

```cpp
#include <cmath>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define int long long
using namespace std;

const int A = 5e5 + 11;
const int B = 1e6 + 11;
const int mod = 1e9 + 7;

inline int read() {
	char c = getchar(); int x = 0, f = 1;
	for( ; !isdigit(c); c = getchar()) if(c == '-') f = -1;
	for( ; isdigit(c); c = getchar()) x = (x << 3) + (x << 1) + (c ^ 48);
	return x * f;
}

int n, m, a[A], b[A], fac[A], inv[A], ans; //a[i]左边的左括号个数，b[i]右边的右括号个数 
char s[A];

int power(int a, int b, int res = 1) {
	while(b) {
		if(b & 1) res = res * a % mod;
		a = a * a % mod; b >>= 1;
	} return res;
} 

void prepare(int n) {
	fac[0] = 1;
	for(int i = 1; i <= n; i++) fac[i] = fac[i - 1] * i % mod;
	inv[n] = power(fac[n], mod - 2);
	for(int i = n - 1; i >= 0; i--) inv[i] = inv[i + 1] * (i + 1) % mod; 
	return;
}

int C(int n, int m) {
	if(n < m) return 0;
	return fac[n] % mod * inv[n - m] % mod * inv[m] % mod;
}

signed main() {
	scanf("%s", s + 1);
	n = strlen(s + 1);
	prepare(n * 2);
	for(int i = n; i >= 1; i--)
		if(s[i] == ')') b[i] = b[i + 1] + 1;
		else b[i] = b[i + 1];
	for(int i = 1; i <= n; i++) {
		if(s[i] == '(') a[i] = a[i - 1] + 1;
		else a[i] = a[i - 1]; 
	}
	for(int i = 1; i <= n; i++) {
		if(s[i] == ')') continue;
		int x = a[i], y = b[i];
		ans += C(x + y, x) - C(x + y - 1, x - 1) , ans %= mod;
	}
	ans = (ans % mod + mod) % mod;
	cout << ans << '\n';
	return 0;
}
```

---

## 作者：_sunkuangzheng_ (赞：0)

$\textbf{1.1 Solution}$

设位置 $i$ 前面（包括 $i$）有 $a_i$ 个左括号，位置 $i$ 后面有 $b_i$ 个右括号，我们对于每个**是左括号**的位置 $i$，求出**强制选择**这个位置的方案数量。这个括号必须选，而剩余的括号可以随意选择，我们很容易写出这个式子：（以下推导假设 $a_i > b_{i+1}$，另一种情况同理）

$$\begin{aligned}ans &= \sum\limits_{j=1}^{\min(a_i,b_i)} \dbinom{a_i-1}{j-1} \dbinom{b_{i+1}}{j} \\ &= \sum\limits_{j=1}^{\min(a_i,b_i)} \dbinom{a_i-1}{j-1} \dbinom{b_{i+1}}{b_{i+1}-j} \\ &= \dbinom{a_i+b_{i+1}-1}{b_{i+1}-1}\end{aligned}$$

其中第二步到第三步用的是**范德蒙德卷积**，证明可以简单的考虑组合意义。

当 $a_i \le b_{i+1}$ 时，求得的答案是

$$\dbinom{a_i+b_{i+1}-1}{a_i}$$

与上面的式子相等。

因此我们预处理阶乘和阶乘的逆元，累加每一个 $i$ 的答案。时间复杂度 $\mathcal O(n)$。

$\textbf{1.2 Code}$

```cpp
/**
 *    author: sunkuangzheng
 *    created: 04.10.2023 14:08:32
**/
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5+5,mod = 1e9+7;
int t,n,a[maxn],b[maxn],f[maxn],g[maxn],ans;string s;
int qp(int a,int b){
    int r = 1;
    for(;b;b >>= 1,a = a * a % mod) if(b & 1) r = r * a % mod;
    return r; 
}int c(int n,int m){return (n<0||m<0||n<m) ? 0 : f[n] * g[m] % mod * g[n-m] % mod;}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0);
    cin >> s;n = s.size(),s = " " + s,f[0] = g[0] = 1;
    for(int i = 1;i <= n;i ++) f[i] = f[i-1] * i % mod,a[i] = a[i-1] + (s[i] == '(');
    g[n] = qp(f[n],mod-2),b[n] = s[n] == ')';
    for(int i = n - 1;i >= 1;i --) g[i] = g[i+1] * (i+1) % mod,b[i] = b[i+1] + (s[i] == ')');
    for(int i = 1;i < n;i ++) if(s[i] == '(')ans = (ans + c(a[i]+b[i+1]-1,a[i])) % mod;
    cout << ans;
}
```

---

## 作者：wcyQwQ (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF785D)

[可能更好的阅读体验](https://chenyu-w.github.io./2023/02/09/CF785D%20Anton%20and%20School%20-%202/)

## 前言

范德蒙德卷积入门题。

## 分析

遇到这种分成前后两段的问题，一般都是枚举每个点作为分界点的答案，这题也是一样，我们记 $[1, i]$ 的 `(` 数量为 $l_i$，$[i, n]$ 的 `)` 数量为 $r_i$，然后我们枚举每个点作为最后一个 `(` 时的答案，考虑当前点为 $i$，选取的子序列长度为 $2k$，那么就相当于从 $[1, i - 1]$ 中选 $k - 1$ 个 `(`，再从 $[i, n]$ 中选取 $k$ 个 `)`，用组合数可表示为
$$
\sum_k \binom{l_i - 1}{k - 1}\binom{r_i}{k}
$$
这很像范德蒙德卷积的形式，于是我们稍作变化，得到
$$
\begin{aligned}
&\sum_k \binom{l_i - 1}{k - 1}\binom{r_i}{k}\\
&=\sum_k \binom{l_i - 1}{l_i - k}\binom{r_i}{k}\\
&=\binom{l_i + r_i - 1}{l_i}
\end{aligned}
$$
这样就可以 $O(1)$ 计算每个位置的答案了，总的时间复杂度为 $O(n)$。

## 代码

```c++
#include <bits/stdc++.h>
#define L(i, j, k) for (int i = (j); i <= (k); i++)
#define R(i, j, k) for (int i = (j); i >= (k); i--)
#define G(i, u) for (int i = h[(u)]; ~i; i = ne[i])
#define ll long long
#define ld long double
#define ull unsigned long long

using namespace std;
const int N = 2e5 + 10, mod = 1e9 + 7;
char s[N];
int l[N], r[N], fac[N], ifac[N];

inline int read() {
    int x = 0, y = 1; char c = getchar();
    while (c < '0' || c > '9') {if (c == '-') y = -1; c = getchar();}
    while (c >= '0' && c <= '9') x = x * 10 + c - '0', c = getchar();
    return x * y;
}

inline int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % mod;
		a = 1ll * a * a % mod;
		b >>= 1;
	}
	return res;
}

inline void init(int n) {
	fac[0] = ifac[0] = 1;
	L(i, 1, n) fac[i] = 1ll * fac[i - 1] * i % mod;
	ifac[n] = qpow(fac[n], mod - 2);
	R(i, n - 1, 1) ifac[i] = 1ll * ifac[i + 1] * (i + 1) % mod; 
}

inline int C(int x, int y) {
	if (x < y || y < 0) return 0;
	return 1ll * fac[x] * (1ll * ifac[y] * ifac[x - y] % mod) % mod;
}

int main() {
	scanf("%s", s + 1);
	int n = strlen(s + 1);
	init(n);
	L(i, 1, n) l[i] += s[i] == '(', r[i] += s[i] == ')';
	L(i, 1, n) l[i] += l[i - 1];
	R(i, n, 1) r[i] += r[i + 1];
	int res = 0;
	L(i, 1, n) {
		if (s[i] == ')') continue;
		res = (res + C(l[i] + r[i] - 1, l[i])) % mod;
	}
	printf("%d\n", res);
    return 0;
}
```



---

## 作者：daniEl_lElE (赞：0)

## Solution

**前情需要：当 $n<0$ 或 $m<0$ 或 $n<m$ 时本文定义 $\binom{n}{m}=0$。**

考虑以某个位置 $i$ 为**最后一个** `(` 有多少种不同的方案数。记录 $i$ 位置及以前的 `(` 数量为 $a_i$，$i$ 及以后的 `)` 数量为 $b_i$。

考虑长度为 $2\times x$ 的子串的方案数为 $\binom{a_i-1}{x-1}\times\binom{b_i}{x}$，意思是除了最后一个必须要选以外其他随便选。

那么总方案数就是 $\sum_{x=1}^{b_i}\binom{a_i-1}{x-1}\times\binom{b_i}{x}=\sum_{x=1}^{b_i}\binom{a_i-1}{x-1}\times\binom{b_i}{b_i-x}$。

考虑组合数组合意义递推理论，我们发现下面选的总数一直都是 $(x-1)+(b_i-x)=b_i-1$，那么其实意义就是从 $a_i-1+b_i$ 段落中选出 $b_i-1$ 的方案，只是分成两段考虑（这段是比较重要的组合意义递推方式，下面选的数量一定，上面覆盖**全部方案**，总和就是 $\binom{up_1+up_2+\dots+up_{k}}{down_1+down_{2}+\dots+down_{k}}$）。

复杂度 $\Theta(n)$。

## Code

```cpp
#include <bits/stdc++.h>
#define int long long
#define double long double
#define mid ((l+r)>>1)
using namespace std;
const int mod=1e9+7;
int qp(int a,int b){
	int ans=1;
	while(b){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans;
}
int fac[10000005],inv[10000005];
void init(){
	fac[0]=1;
	for(int i=1;i<=10000000;i++) fac[i]=fac[i-1]*i%mod;
	inv[10000000]=qp(fac[10000000],mod-2);
	for(int i=9999999;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
}
int C(int i,int j){
	if(i<0||j<0||i<j) return 0;
	return fac[i]*inv[i-j]%mod*inv[j]%mod;
}
int a1[200005],a2[200005];
signed main(){
	//freopen("","r",stdin);
	//freopen("","w",stdout);
	init();
	string s;
	cin>>s;
	int n=s.size();
	s=" "+s;
	for(int i=1;i<=n;i++){
		a1[i]=a1[i-1]+(s[i]=='(');
	}
	for(int i=n;i>=1;i--){
		a2[i]=a2[i+1]+(s[i]==')');
	}
	int sum=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='(') sum=(sum+C(a1[i]+a2[i]-1,a2[i]-1))%mod;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：_Fontainebleau_ (赞：0)

## 题意

- 给定一个长度为 $n$ 的字符串，由 `(` 和 `)` 组成。
- 求有多少个字符串，前半部分由 `(` 组成，后半部分由 `)` 组成。答案对 $10^9+7$ 取模。
- $1\le{n}\le{2\times10^5}$。

## 做法

### 前置知识

Vandermonde 卷积公式：

$$\color{darkgreen}\sum_{k}\binom{r}{k}\binom{s}{n-k}=\binom{r+s}{n}$$

证明：

$$\begin{aligned}\sum_{n=0}^{r+s}\binom{r+s}{n}x^n&=\left(1+x\right)^{r+s}\\&=\left(1+x\right)^r\left(1+x\right)^s\\&=\left(\sum_{n=0}^r\binom{r}{n}x^n\right)\left(\sum_{n=0}^r\binom{s}{n}x^n\right)\\&=\sum_{n=0}^{r+s}\left(\sum_{k}\binom{r}{k}\binom{s}{n-k}\right)x^n\end{aligned}$$

对比系数，可得。

### 在此之后

硬取当前这一位 `(`。

如果当前这一位之前（包括自己）有 $x$ 个 `(`，之后有 $y$ 个 `)`。那么当前这一位的贡献是 $\displaystyle\sum_{i=0}^{\min\left(x-1,y-1\right)}\binom{x-1}{i}\binom{y}{i+1}$。考虑这个跟前置知识的关系。我们把这个式子改一下就是 $\displaystyle\sum_{i=0}^{\min\left(x-1,y-1\right)}\binom{x-1}{i}\binom{y}{y-i-1}=\binom{x+y-1}{y-1}$。

然后，预处理一下阶乘和逆元就可以 $O(n)$ 做了。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 200000
#define mod 1000000007
using namespace std;
string s;
int n,cnt,ans,fac[200005],I[200005],inv[200005],r[200005];
inline int read()
{
	int x=0,f=1;char c=getchar();
	while(c<'0'||c>'9'){if(c=='-')f=-f;c=getchar();}
	while(c>='0'&&c<='9'){x=x*10+c-'0';c=getchar();}
	return x*f;
}
inline int f(int base,int y)
{
	int res=1,p=base;
	while(y)
	{
		if(y&1)	res=1ll*(res*p)%mod;
		p=1ll*(p*p)%mod;y>>=1;
	}
	return res;
}
inline int getc(int n,int m)
{
	if(n<m||n<0||m<0)	return 0;
	return 1ll*fac[n]*inv[m]%mod*inv[n-m]%mod;
}
signed main()
{
	std::cin.tie (0);
	std::ios::sync_with_stdio (false);
	cin>>s;n=s.size();
	fac[0]=1;
	for(int i=1;i<=maxn;i++) fac[i]=fac[i-1]*i%mod;
	inv[maxn]=f(fac[maxn],mod-2);
	for(int i=maxn-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
//	fac[1]=inv[1]=I[1]=1;
//	for(int i=2;i<=n;i++)	fac[i]=1ll*fac[i-1]*i%mod,I[i]=1ll*(mod-mod/i)*I[mod%i]%mod;
//	for(int i=2;i<=n;i++)	inv[i]=I[fac[i]];
	for(int i=n-1;i>=0;i--)	r[i]=r[i+1]+(s[i]==')');
	for(int i=0;i<n;i++)
	{
		if(s[i]=='(')	
		{
			cnt++;
			ans=ans+getc(cnt+r[i]-1,r[i]-1);ans%=mod;			
		}
	
	}
	printf("%d\n",ans);
	return 0;
}
```


---

## 作者：Grisses (赞：0)

[题面](https://www.luogu.com.cn/problem/CF785D)

首先，我们可以预处理出每一位前面的左括号个数以及后面的右括号个数，记为 $l_i$ 和 $r_i$。

那么，我们枚举选的第一个右括号的位置 $i$，即枚举所有 $s_i=')'$ 的 $i$，然后再枚举左右括号的个数 $k$，此时的方案数为 $\sum\limits_{k=1}^{r_i}C_{l_i}^k\times C_{r_i-1}^{k-1}$（实际上上界应该是 $\min(l_i,r_i)$，但是当 $m>n$ 时，$C_n^m=0$，所以补上几项也无所谓）。

看着上面的式子，我们进行一些改造：
$$
\begin{array}{c}
&\sum\limits_{k=1}^{r_i}C_{l_i}^k\times C_{r_i-1}^{k-1}\\
=&\sum\limits_{k=1}^{r_i}C_{l_i}^k\times C_{r_i-1}^{r_i-k}\\
=&C_{l_i+r_i-1}^{r_i}
\end{array}
$$

其中最后一步由**范德蒙德恒等式**得出。

### 范德蒙德恒等式
$$\sum\limits_{i=0}^{n}C_n^i\times C_{m}^{r-i}=C_{n+m}^r$$

证明，假设我们要在 $n+m$ 个球中选出 $r$ 个，那么我们可以前 $n$ 个球选 $i$ 个，后 $m$ 个球选 $r-i$ 个，然后根据加乘原理将方案数算出，即是上式。

代码：
```cpp
  #include<bits/stdc++.h>
  #define int long long
  using namespace std;
  const int mod=1e9+7;
  int m,n,x,y,ans,num[40],c[5000005],inc[5000005],l[2000005],r[2000005];
  char s[2000005];
  int fpow(int a,int b){
      if(b<0)return 1;
      int res=1;
      while(b){
          if(b&1)res=res*a%mod;
          a=a*a%mod;
          b>>=1;
      }
      return res;
  }
  inline int C(int n,int m){
      if(m>n)return 0;
      return c[n]*inc[m]%mod*inc[n-m]%mod;
  }
  signed main()
  {
      c[0]=c[1]=1;
      for(int i=2;i<=5000000;i++)c[i]=c[i-1]*i%mod;
      inc[5000000]=fpow(c[5000000],mod-2);
      for(int i=5000000-1;i>=0;i--)inc[i]=inc[i+1]*(i+1)%mod;//初始化阶乘以及逆元
      scanf("%s",s+1);
      n=strlen(s+1);
      for(int i=1;i<=n;i++){
          if(s[i]=='(')l[i]=1;
          else r[i]=1;
      }
      for(int i=1;i<=n;i++)l[i]+=l[i-1];
      for(int i=n;i>=1;i--)r[i]+=r[i+1];//分别计算前后缀和
      for(int i=1;i<=n;i++){
          if(s[i]==')'){
              ans=(ans+C(l[i]+r[i]-1,r[i]))%mod;//累加，原因见上
          }
      }
      printf("%lld",ans);
      return 0;
  }
```

---

