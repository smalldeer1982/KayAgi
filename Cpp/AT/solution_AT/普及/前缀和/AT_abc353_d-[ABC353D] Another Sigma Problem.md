# [ABC353D] Another Sigma Problem

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc353/tasks/abc353_d

正整数 $ x,y $ に対して $ f(x,y) $ を以下で定義します。

- 十進表記の $ x,y $ をそれぞれ文字列として解釈しこの順に連結して得られる文字列を $ z $ とする。$ z $ を十進表記の整数として解釈したときの値を $ f(x,y) $ とする。
 
例えば $ f(3,14)=314,\ f(100,1)=1001 $ です。

長さ $ N $ の正整数列 $ A=(A_1,\ldots,A_N) $ が与えられます。次の式の値を $ 998244353 $ で割ったあまりを求めてください。

$ \displaystyle\ \sum_{i=1}^{N-1}\sum_{j=i+1}^N\ f(A_i,A_j) $

## 说明/提示

### 制約

- $ 2\leq\ N\leq\ 2\times\ 10^5 $
- $ 1\leq\ A_i\ \leq\ 10^9 $
- 入力される数値は全て整数
 
### Sample Explanation 1

\- $ f(A_1,A_2)=314 $ - $ f(A_1,A_3)=315 $ - $ f(A_2,A_3)=1415 $ なので、答えは $ f(A_1,A_2)+f(A_1,A_3)+f(A_2,A_3)\ =\ 2044 $ です。

### Sample Explanation 2

式の値を $ 998244353 $ で割ったあまりを求めることに注意してください。

## 样例 #1

### 输入

```
3
3 14 15```

### 输出

```
2044```

## 样例 #2

### 输入

```
5
1001 5 1000000 1000000000 100000```

### 输出

```
625549048```

# 题解

## 作者：旻偲 (赞：7)

## 题号：AT_abc353_d
### 做法：

题意很简单，就是让你按枚举顺序，将操作求和并取模得到最后的答案。$2 \leq n \leq 2 \times 10^5$，很显然这个数据范围不能暴力（~~我赛时甚至已经打完暴力放在提交页面准备交了，才发现数据范围~~），于是我们想到找一些性质来优化时间复杂度。

#### 分析操作 $f(a_i,a_j)$：  

$f(a_i,a_j) $ 表示为将 $a_j$ 拼接在 $a_i$ 之后，组成一个新的数字。   
形式化地表示就是：  
$f(a_i,a_j) = a_i \times 10^{|a_j|} + a_j$（其中 $|a_j|$ 表示 $a_j$ 的长度即 $a_j$ 有多少位数)。  
我们将结果分为两部分： 
1. $a_i$ 对答案的贡献，即 $a_i \times 10^{|a_j|}$。
2. $a_j$ 对答案的贡献，即 $ + a_j$。

那么就可以 $O(n)$ 地遍历数组，分别计算出 $a_i$ 为第一位操作数对答案的贡献（相同长度的 $a_j$ 对第一个情况的贡献是一样的），和 $a_i$ 为第二位操作数答案的贡献，累加到最后的答案即可。

#### 分析 $a_i$ 对答案的贡献次数：  

注意求和顺序： $\displaystyle \sum_{i=1}^{N-1}\sum_{j=i+1}^N f(a_i,a_j)$，即 $a_i$ 会作为 $a_j$ 的第一位的操作数，当且仅当 $i+1 \leq j \leq n$ 时，即第一种情况的贡献的次数为 $n-i+1$ 次，第二种情况的贡献次数为 $i-1$ 次。（$a_i$ 只会成为下标小于它的元素的第一个操作数，而下不会成为下标小于它的元素的第二个操作数，对着样例解释看看就知道了）  

#### 最后  

预处理出每一个数的长度（即有几位数），开一个桶记录下来各个长度的次数。然后遍历每一个数，按照上面的贡献次数和贡献方法计算即可所以枚举 $1$ 到 $9$ 位即可。最后 $a_i$ 对答案贡献的公式就是（$k$数组表示各个长度在下标为 $i+1$ 到 $n$ 的情况）：
$$  
\displaystyle a_i \times (i-1) +  \sum_{z = 1}^{9}a_i \times 10^z \times k[z] 
$$

最后记得在计算前把 $a_i$ 的长度删掉。

#### code  

```cpp
#include<bits/stdc++.h>
using namespace std;
const int mod = 998244353;
int a[200010],b[200010],c[10];
signed main()
{
    int n;
    cin>>n;
    for(int i = 1;i <= n;i++)
    {
        cin>>a[i];
        string s1 = to_string(a[i]);
        c[s1.size()]++;
        b[i] = a[i].size();//存下来 a[i] 的长度
    }
    long long ans = 0;
    for(int i = 1;i <= n;i++)
    {
        c[b[i]]--;//减去a[i]的长度，避免重复计算
        for(int z = 1;z <= 9;z++)//a[i] 作为第一个操作数的贡献
        {
            ans += (((a[i]*((long long)pow(10,z)%mod))%mod)*a[z])%mod;//注意步步取模，不然就挂了
            ans%=mod;
        }
        ans += (a[i]*(i-1))%mod;//第二种情况的贡献
        ans%=mod;
    }
    cout<<ans<<"\n";
    return 0;
}
```
~~7分钟出D，打满整场没出C，真难绷。~~

---

## 作者：xiaoshumiao (赞：3)

设 $g(a)$ 为 $a$ 的位数，例如 $g(114514)=6$。

则 $f(i,j)=i \times 10^{g(j)}+j$。

我们枚举原题式子中的 $j$，对于每一个 $a_j$，他对答案的贡献为 $(a_1+a_2+\dots+a_{j-1}) \times 10^{g(a_j)}+(j-1) \times a_j$。

$a_1+a_2+\dots+a_{j-1}$ 可以用前缀和算，$g$ 可以直接数位分离或用 `log10` 函数。时间复杂度 $\mathcal O(N)$。
```cpp
#include<cstdio>
#define int long long
using namespace std;
const int N=2e5+10,MOD=998244353; int a[N],sum[N];
int calc(int x) {
  int cnt=0;
  while(x) cnt=(cnt+1)%MOD,x/=10;
  return cnt;
}
int pow10(int x) {
  int ans=1;
  while(x--) ans=ans*10%MOD;
  return ans;
}
signed main() {
  int n,ans=0; scanf("%lld",&n);
  for(int i=1;i<=n;i++) scanf("%lld",&a[i]),sum[i]=(sum[i-1]+a[i])%MOD;
  for(int i=2;i<=n;i++) ans=(ans+(sum[i-1]*pow10(calc(a[i]))%MOD+(i-1)*a[i]%MOD)%MOD)%MOD;
  printf("%lld",ans);
  return 0;
}
```

---

## 作者：liaoxingrui (赞：3)

## Content

定义 $f(x,y)$ 为 $x$ 后面拼接一个 $y$。

例如：

$$f(11,25) = 1125$$

$$f(3322,321) = 3322321$$

求:

$$\sum_{i = 1}^{N - 1} \sum_{j = i + 1}^N f(A_i,A_j)$$

注意：

**答案要模 $998244353$。**

## Solution

很明显暴力过不了，我们就可以来简化一下式子。

对于 $\sum_{i = 1}^N A_i$ 中的每一个 $A_i$，要么在最后，要么就在最前。

- $A_i$ 在最后时，可以发现它会有 $i - 1$ 次，因为它只会被前面的数字选中，被当作后面的数字，公式：

$$\sum_{i=1}^N A_i \times (i - 1)$$

- $A_i$ 在最前时，可以发现它所产生的答案（设后面那个数字的位数为 $x$）为 $10^x \times A_i$，我们可以在读入时就把每个数的位数统计（用 $sum_i$ 表示第 $i$ 个数的位数），然后我们可以设一个 $x$ 数组来统计 $sum_i$ 的值相同的个数，这样就可以把 $\sum_{j = i + 1}^N$ 省略，公式（$j$ 表示位数）：

$$\sum_{i=1}^N \sum_{j=1}^{10} 10^j \times x_j \times A_i$$

当然要注意每次开始第二个循环时都要把 $x_{sum_i}$ 减一，避免重复运算，造成 $f(A_i,A_i)$。

## Code

```cpp
#include<bits/stdc++.h>
#define int unsigned long long
#define mod 998244353
using namespace std;
const int N=3e5+5;
int n,y,ans;
int a[N],b[N],sum[N],x[15];
signed main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		y=a[i];
		while(y){
			sum[i]++;
			y/=10;
		}
		x[sum[i]]++;
	}
	for(int i=1;i<=n;i++){
		x[sum[i]]--;
		for(int j=1;j<=10;j++)
			ans=(ans+((x[j]*a[i])%mod*((int)pow(10,j)%mod))%mod)%mod;
		ans=(ans+(i-1)*a[i])%mod;
	}
	cout<<ans;
	return 0;
}
```

---

## 作者：ma_niu_bi (赞：2)

### D

### 问题陈述

对于正整数 $x$ 和 $y$，定义 $f(x, y)$ 如下：

- 将 $x$ 和 $y$ 的十进制表示解释为字符串，并按此顺序连接，得到字符串 $z$。将 $f(x, y)$ 解释为十进制整数时，其值就是 $z$ 的值。

例如， $f(3, 14) = 314$ 和 $f(100, 1) = 1001$。

给你一个长度为 $N$ 的正整数序列 $A = (A_1, \ldots, A_N)$。求下面表达式取模 $998244353$ 的值：

$\displaystyle \sum_{i=1}^{N-1}\sum_{j=i+1}^N f(A_i,A_j)$ 

### 思路

记 $c(A_i)$ 为 $A_i$ 位数，$w(A_i)$ 为 $A_i$ 的位权，$w(A_i)=10^{c(A_i)}$。

有 $f(A_i,A_j)=A_i \times w(A_j)+A_j$。

原式

$=\displaystyle \sum_{i=1}^{N-1}\sum_{j=i+1}^N f(A_i,A_j)$

$=\displaystyle\sum_{i=1}^{N-1}\sum_{j=i+1}^N A_i\times w(A_j)+A_j$

$=\displaystyle\sum_{i=1}^{N-1}A_i\times\sum_{j=i+1}^N w(A_j)+\sum_{j=i+1}^N A_j$

分别用两个前缀和维护位权以及和即可。

### 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
const int N = 3e5 + 5;
ll n, a[N], b[N], c[N], ans;
ll getw(ll x) {
    ll res = 1;
    while (x) res *= 10, res %= mod, x /= 10;
    return res;
}
int main() {
    cin >> n;
    for (int i = 1; i <= n; i ++) cin >> a[i];
    for (int i = n; i >= 1; i --) {
        b[i] = b[i + 1] + a[i], b[i] %= mod;
        c[i] = c[i + 1] + getw(a[i]), c[i] %= mod;
    } 
    for (int i = 1; i < n; i ++) 
        ans += b[i + 1] + a[i] * c[i + 1] % mod, ans %= mod;
    cout << ans << endl;
    return 0;
}
```

---

## 作者：ThisIsLu (赞：2)

不知道为什么要开个桶，直接算就行了呀。

设 $l_i$ 表示 $a_i$ 的位数，即可对式子变形：

$$
\begin{aligned}
&\sum_{i=1}^{n}\sum_{j=i+1}^{n}f(a_i,a_j)\\
=&\sum_{i=1}^{n}\sum_{j=i+1}^{n}a_i10^{l_j}+a_j\\
=&\sum_{i=1}^{n}\sum_{j=1}^{i-1}a_j10^{l_i}+a_i\\
=&\sum_{i=1}^{n}(i-1)a_i+10^{l_i}\sum_{j=1}^{i-1}a_j\\
\end{aligned}
$$

然后直接用前缀和处理 $\sum_{j=1}^{i-1}a_j$ 就行了。

代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=2e5,mod=998244353;
int n,a[N+5];
signed main(){
    cin>>n;
    int ans=0,sum=0;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        int tmp=a[i],l=1;
        while(tmp){
            l=(1ll*l*10)%mod;
            tmp/=10;
        }
        ans=(ans+1ll*l*sum+a[i]*(i-1))%mod;
        sum=(sum+a[i])%mod;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：ttq012 (赞：1)

考虑对于每一个 $i$ 计算对答案的贡献。

对于每一个 $i$，她都和之前的每一个 $j$ 产生了一次贡献。显然 $i$ 和 $j$ 拼接为 $\overline{ji}$，产生的贡献为 $10^{|i|}\times j+i$，其中 $|i|$ 表示的是 $i$ 的位数。

那么答案就是 $\sum\limits_{i=1}^n \sum\limits_{j=1}^{i-1} (10^{|i|}\times j+i)$，改一下变成 $\sum\limits_{i=1}^n \sum\limits_{j=1}^{i-1} i+\sum\limits_{i=1}^n\sum\limits_{j=1}^{i-1} (10^{|i|}\times j)$。发现前面可以直接 $O(n)$ 计算后面可以用一个前缀和优化。于是总的时间复杂度为 $O(n)$，可以通过。

```cpp
int n;cin>>n;F(i,1,n)cin>>a[i];
F(i,1,N-1)pw[i]=pw[i-1]*10%mod;
int s=0,st=0;
F(i,1,n){
        s+=a[i]*(i-1)+st*pw[to_string(a[i]).size()]%mod,s%=mod;
        st+=a[i],st%=mod;
}
cout<<s<<'\n';
```

---

## 作者：Luxingguang (赞：1)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc353_d)

## 一、思路分析
------------
我们可以先把每一个数的数位存储一下。

若 $y$ 有 $k$ 位，则 $f(x,y)=x\times 10^k+y$。

所以我们可以求数位的后缀和，再求出 $x$ 乘上当前后缀数组的值与 $x$ 作为末尾的和。

## 二、构造代码
------------
```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
const int N=2e5+5,MOD=998244353;
int n,a[N],c[N],d[N],sumh[N],ans;
signed main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++){
		scanf("%lld",&a[i]);
		int j=a[i];
		d[i]=1;
		while(j){
			c[i]++;
			d[i]*=10;
			j/=10;
		}a[i]%=MOD;
	}for(int i=n;i>=1;i--){
		sumh[i]=sumh[i+1]+d[i];
	}for(int i=1;i<=n;i++){
		ans+=(a[i]*((sumh[i+1]+i-1)%MOD))%MOD;
		ans%=MOD;
	}printf("%lld",ans);
	return 0;
}

```

---

## 作者：ANDER_ (赞：0)

~~万恶之西格玛~~

## 题目
给定你一个长度为 $n$ 的序列 $num$，定义 $f(a, b)$ 为 $\underline{ab}$。如 $f(114,514) = 114514$，让你求：

$\sum_{i = 1}^{n - 1}\sum_{j = i + 1}^{n} f(num_i, num_j)$

## 思路
暴力是不行了，见到这种数论相关题目，一定要做好推式子的准备。

对于 $f(a, b)$，它等于 $10^{lenth(b)}a + b$。借用上面的例子，$f(114, 514) = 10^3 \times 114 + 514 = 114514$。

对于 $f(x, num_i)$，$num_i$ 对整体贡献等于 $num_i(i - 1)$。而对于 $f(num_i, x)$，若序列中与 $x$ **长度相等**的个数为 $T_k$，其贡献为 $T_k·10^k·num_i$。

模拟以上过程，我们就可以用 $O(n)$ 的时间复杂度求解了。
## 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD = 998244353;
inline int Alexander(int a, int b) {
	while(b > 0) {
		a *= 10, b /= 10, a %= MOD;
	}
	return a;
}
int n, x, fir, ans;
signed main() {
	cin>>n>>fir;
	for(int i = 1 ; i < n ; i ++) {
		cin>>x;
		ans += Alexander(fir, x) + x * i % MOD;
		ans %= MOD, fir += x, fir %= MOD;
	}
	cout<<ans;
	return 0;
}
```
2024.05.24 管理员大大，本人过一审通过后发现代码写炸了，二审求过

---

## 作者：Ivan422 (赞：0)

题目大意：给出 $n$ 个数，求：

$$ \sum_{i=1}^{N-1}\sum_{j=i+1}^N\ f(A_i,A_j) $$

其中 $f(x,y)$ 表示将 $x$ 和 $y$ 直接拼起来。

思路：尝试固定 $j$，我们会发现这时的数一定在固定位置上有一个 $a_j$，可以尝试乘法分配律。得出结果为：

$$ f(\sum_{i=1}^{j-1}A_i,A_j) $$

前面的部分可以直接通过前缀和求解，而求 $f(x,y)$ 则可以通过数学方法求解，总时间复杂度 $O(n)$。

注意：取模！

```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
//#define double long double
//#define map unordered_map
//#pragma GCC optimize(2,3,"Ofast","inline")
const int N=3e5+10,M=1010,P=998244353,MOD=998244353;
const double PI=3.1415926,EPS=0.00001;
int n,a[N],s[N],ans,su;
signed main(){
    cin>>n;
    for(int i=1;i<=n;i++){cin>>a[i];}
    for(int i=1;i<=n;i++){
        int sz=pow(10,(int)to_string(a[i]).size());
        ans=(ans+(su%P)*(sz%P)+(a[i]*(i-1))%P)%P;
        su=(su+a[i])%P;
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：aeiouaoeiu (赞：0)

设 $b_i$ 为 $a_i$ 的位数，对于 $a_i$，我们试着拆一下贡献。

- 对于 $j<i$，我们要计算 $f(a_j,a_i)=\overline{a_ja_i}=a_j\times10^{b_i}+a_i$，此时对于一个 $j$，$a_i$ 贡献为 $a_i$。于是这一部分总贡献为 $(i-1)a_i$。
- 对于 $j>i$，我们要计算 $f(a_i,a_j)=\overline{a_ia_j}=a_i\times10^{b_j}+a_j$，此时对于一个 $j$，$a_i$ 贡献为 $a_i\times10^{b_j}$。我们对 $c_j=10^{b_j}$ 做一个前缀和记为 $s_j$，于是这一部分总贡献为 $(s_n-s_i)a_i$。

对于每个 $i$ 我们都能 $\mathcal{O}(1)$ 求出其贡献，加一起显然就是答案。

```cpp
#include<bits/stdc++.h>
#define pb emplace_back
#define pob pop_back
#define mp make_pair
using namespace std;
typedef long long ll;
typedef double db;
const ll maxn=200007,ee=1000000000000000007ll,p=998244353;
ll n,a[maxn],sum[maxn],ans;
ll gts(ll x){return (x?(gts(x/10)*10):1);}
int main(void){
	//freopen("data.in","r",stdin);
	//freopen("data.out","w",stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
	ll Tccs=1;
	//cin>>Tccs;
	for(int tcs=1;tcs<=Tccs;tcs++){
		cin>>n;
		for(int i=1;i<=n;i++) cin>>a[i],sum[i]=(sum[i-1]+gts(a[i]))%p;
		//for(int i=1;i<=n;i++) cout<<sum[i]<<" "; cout<<"\n";
		for(int i=1;i<=n;i++) ans=(ans+(i-1)*a[i]%p+((sum[n]-sum[i]+p)%p)*a[i]%p)%p;
		cout<<ans<<"\n";
	}
	return 0;
}
```

---

## 作者：Walrus (赞：0)

## ABC353_d
给定 $a,b$，定义 $f(a,b)$ 为 $a$ 与 $b$ 拼接后字符串对应的值。
比如 $f(123,456)=123456$。

求 
$$\sum\limits_{i=1}\limits^{N-1}\sum\limits_{j=i+1} \limits^{N}f(a_i,a_j)$$

暴力肯定是 $O(N^2)$ 的。

根据拼接后的字符串不难看出，$f(i,j)$ 其实等于 $i \times 10^x+j$，其中 $x$ 为 $j$ 的位数，对于每个 $j$，会被 $a_1 \sim a_{j-1}$ 影响到，所以考虑前缀和，将式子转化为求 

$$\sum\limits_{i=2}
\limits^{N}sum_{i-1}\times 10^x +a_i\times(i-1)$$

$x$ 还是 $a_i$ 的位数。

所以复杂度优化为 $O(N \log N)$。
## Code
```cpp
#include <bits/stdc++.h>
#define rep(i, j, k) for(int i = j; i <= k; ++i)
#define drep(i, j, k) for(int i = j; i >= k; --i)
#define int long long
using namespace std;
const int N = 3e5 + 5;
const int mod = 998244353;

int a[N], n, k, res, ans, sum[N];

int qkpow(int a, int b) {
	int res = 1;
	while(b) {
		if(b & 1) res = res * a % mod;
		a = a * a % mod;
		b >>= 1;
	}
	return res;
}

int get(int x) {
	int res = 0;
	while(x) ++res, x /= 10;
	return res;
}

signed main() {
	ios::sync_with_stdio(0);
	cin.tie(nullptr), cout.tie(nullptr);
	cin >> n;
	rep(i, 1, n) cin >> a[i], sum[i] = sum[i - 1] + a[i], sum[i] %= mod;
	drep(i, n, 2) {
		int len = get(a[i]);
		ans += qkpow(10, len) * sum[i - 1] % mod + a[i] * (i - 1);
		ans %= mod;
	}
	cout << (ans % mod + mod) % mod;
	return 0;
}
```

---

## 作者：2huk (赞：0)

> - 求 $\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^n f(a_i, a_j)$，其中 $f(i, j)$ 表示将 $i, j$ 顺次连接后得到的十进制数字。
> - $n \le 2 \times 10^8$，$1 \le a_i \le 10^9$。

显然我们可以通过 $\lfloor \lg n\rfloor + 1$ 来计算 $n$ 的位数，那么 $f(i, j)$ 就可以被表示为 $i \times 10^{\lfloor \lg n\rfloor + 1} + j$。那么所求即：
$$
\sum\limits_{i=1}^{n-1}\sum\limits_{j=i+1}^n (a_i \times 10^{\lfloor \lg a_j\rfloor + 1} + a_j)
$$
那么按照一般的处理方式，即改变求和顺序：
$$
\sum\limits_{j=2}^n\sum\limits_{i=1}^{j-1} (a_i \times 10^{\lfloor \lg a_j\rfloor + 1} + a_j)
$$
把第二个求和中与 $i$ 无关的提到外面：
$$
\sum_{j=2}^n \left(a_j \times (j-1) + 10^{\lfloor \lg a_j\rfloor + 1} \times \sum_{i=1}^{j-1}a_i\right)
$$
维护前缀和即可 $\Theta(n)$ 计算。

```cpp
int n, sum, res, a[N];

int calc(int n) {
	// 计算 n 的位数
	return log10(n) + 1;
}

int fpm(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = (ll)res * a % P;
		b >>= 1, a = (ll)a * a % P;
	}
	return res;
}

void Luogu_UID_748509() {
	fin >> n;
	
	for (int i = 1; i <= n; ++ i ) {
		fin >> a[i];
		res = (res + a[i] * (i - 1) % P + sum * fpm(10, calc(a[i])) % P) % P;
		sum = (sum + a[i]) % P;
	}
	
	fout << res << '\n';
}
```

---

## 作者：T_TLucas_Yin (赞：0)

如果我们以每个 $f(i,j)$ 中的 $i$ 为第一关键字枚举，那么每一次计算时 $i$ 前移的位数是不一样的，所以无法实现预处理。所以我们要以 $j$ 为第一关键字枚举。即对于每个 $j$，计算对于所有 $1\le i< j$，$f(i,j)$ 的值。

注意到若当前的 $j$ 有 $K$ 位，所有的 $i$ 就都要前移 $K$ 位，即乘上 $10^{K}$。根据乘法分配律，设 $g_i=a_1+a_2+...+a_i$（即 $i$ 位前缀和），那么当前 $j$ 对应所有要求的 $f(i,j)$ 之和即为

$$g_{j-1}\times 10^K+a_j\times(j-1)$$

再加上取模。这样就可以 $O(n)$ 求出答案了。

```cpp
#include<bits/stdc++.h>
using namespace std;
const long long M=998244353;
long long n,a[1000005],f,sum;
int f1(long long x){
	int cnt=0;
	if(x==0) return 1;
	while(x!=0) cnt++,x/=10;
	return cnt;
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=n;i++){
		long long x=1,k=f1(a[i]);
		for(int j=1;j<=k;j++) x=x*10%M;
		sum=(sum+(f*x%M+a[i]*(i-1)%M)%M)%M;
		f=(f+a[i])%M;
	}
	cout<<sum;
	return 0;
}
```

---

## 作者：PineappleSummer (赞：0)

[Problem](https://atcoder.jp/contests/abc353/tasks/abc353_d)

Atcoder problems 评分：$\color{SeaGreen}{844}$。

比 C 简单的 D。

记 $cnt_i$ 为数字 $i$ 在十进制下的位数。

拆式子：$f(A_i,A_j)=A_i\times 10^{cnt_{A_j}}+A_j$。

考虑 $2\sim n$ 枚举 $i$，则答案为 $\displaystyle\sum_{i=2}^{N}\sum_{j=1}^{i-1}\ f(A_j,A_i) $。

对与每个 $i$，计算 $\displaystyle\sum_{j=1}^{i-1}\ f(A_j,A_i)$ 然后累加即可。继续拆式子：
$$\begin{aligned} \sum_{j=1}^{i-1}\ f(A_j,A_i)&=(\displaystyle\sum_{j=1}^{i-1}\ A_j\times 10^{cnt_{A_i}})+A_i\times (i-1)\\&=(\displaystyle\sum_{j=1}^{i-1}\ A_j)\times 10^{cnt_{A_i}}+A_i\times (i-1)\end{aligned}$$

$\displaystyle\sum_{j=1}^{i-1}\ A_j$ 用前缀和维护一下就行。

然后就做完了，记得对答案取模。
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
typedef long long LL;
const int N = 2e6 + 10, mod = 998244353;
int n, a[N], sum[N], ans, p[N];
int js (int k) { // 计算 k 的位数
	int cnt = 0;
	while (k) {
		cnt++;
		k /= 10;
	}
	return cnt;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	
	cin >> n;
	for (int i = 1; i <= 18; i++) p[i] = pow(10, i), p[i] %= mod;
	for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 1; i <= n; i++) {
		if (i > 1) ans = ((ans + sum[i - 1] * p[js(a[i])] % mod) % mod + a[i] * (i - 1) % mod) % mod;
		sum[i] = (sum[i - 1] + a[i]) % mod; // 前缀和
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Elairin176 (赞：0)

[传送门](https://www.luogu.com.cn/problem/AT_abc353_d)   
## 题意
设 $\operatorname{f}(a,b)$ 为 $a,b$ 拼接后的结果，如 $\operatorname{f}(114,514)=114514$.   
求 $(\sum\limits^{n-1}_{i=1}\sum\limits^n_{j=i+1}\operatorname{f}(a_i,a_j))\bmod998244353$.   
## 解法
看到拼接，这不直接秒了吗。   
我们设 $\operatorname{l}(x)$ 为 $x$ 的长度，那么不难发现 $\operatorname{f}(a,b)=10^{\operatorname{l}(b)}a+b$。    
那么，我们简单推一下式子：   
$\begin{aligned}\sum\limits^{n-1}_{i=1}\sum\limits^n_{j=i+1}\operatorname{f}(a_i,a_j)&=\sum\limits^{n-1}_{i=1}\sum\limits^n_{j=i+1}10^{\operatorname{l}(a_j)}a_i+a_j\\&=\sum\limits^{n-1}_{i=1}\big(\sum\limits^{10}_{k=1}10^{k}a_i\sum\limits^n_{j=i+1}[\operatorname{l}(a_j)=k]\big)+\sum\limits^n_{k=i+1}a_k\end{aligned}$     
那么我们作个前缀和即可。   
CODE:    
```cpp
//完整缺省源请见洛谷云剪贴板 jo5j6ogx
cst ll p=998244353;
cst int N=2e5;
int n;
ll a[N+10],w[15],q[11][N+10],ans,cnt[11][N+10];
il int len(ll x){
	int cnt=0;
	while(x){
		cnt++;
		x/=10;
	}	
	ret cnt;
}
il ll get1(int x,int l,int r){
	ret msub(q[x][r],q[x][l-1],p);
}
il ll get2(int x,int l,int r){
	ret cnt[x][r]-cnt[x][l-1];
}
int main(void){
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	w[0]=1;
	for(int i=1;i<=10;i++){
		w[i]=w[i-1]*10%p;
	}
	n=read<int>();
	for(int i=1;i<=n;i++){
		a[i]=read<ll>();
		int l=len(a[i]);
		for(int j=1;j<=10;j++){
			q[j][i]=(q[j][i-1]+(l==j)*a[i])%p;
			cnt[j][i]=(cnt[j][i-1]+(l==j));
		}
	}
	for(int i=1;i<n;i++){
		for(int j=1;j<=10;j++){
			ans=(ans+(w[j]*a[i]%p*get2(j,i+1,n)%p+get1(j,i+1,n)%p)%p)%p;
		}
	}
	write(ans);
	ret 0;
}
```

---

## 作者：MightZero (赞：0)

## 思路
首先考虑对每个数对 $(a_i,a_j)$ 的贡献分开处理：对于 $a_j$ 的部分，显然对答案的贡献就是自身；对于 $a_i$, 对答案的贡献是 $a_i\times 10^{\lfloor\lg a_j\rfloor+1}$，显然系数部分是可以预处理的。

因此对于每个 $a_i (1\le i \le n-1)$，其对答案的总贡献 $w_i$ 表达式如下：

$$w_i = (i-1)a_i+a_i \times \sum_{j=i+1}^{n}10^{\lfloor\lg a_j\rfloor+1}$$

## 具体实现
预处理出每个 $10^{\lfloor\lg a_j\rfloor+1}$，求和后直接计算即可。

需要注意按照以下代码的算法会爆 `long long`，需要使用 `__int128`。

## Code
```cpp
#include<bits/stdc++.h>
#define loop(x,l,r) for(ll (x) = (l);(x)<=(r);++(x))
#define elif else if
using namespace std;
using ll = __int128;
ll a[200005],pw[200005],sum,ans,n;
const ll mod=998244353;
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
signed main()
{
    n=read();
    loop(i,1,n)
    {
        a[i]=read();ans+=a[i]*(i-1);ans%=mod;
        ll x=a[i];pw[i]=1;while(x)pw[i]*=10,x/=10;
        pw[i]=max(pw[i],(ll)10);sum+=pw[i];
    }
    loop(i,1,n-1)
    {
        sum-=pw[i];
        ans+=a[i]*sum;
        ans%=mod;
    }
    write(ans);
    return 0;
}
```

[AC Record](https://atcoder.jp/contests/abc353/submissions/53365861)

---

## 作者：Special_Tony (赞：0)

# 思路
首先我们设 $s_i$ 是 $a_i$ 的位数，则 $f(a_i,a_j)=a_i\times10^{s_j}+a_j$。首先先看放在地位的情况，$a_i$ 会被放在低位 $i-1$ 次，所以低位之和就是 $\sum\limits_{i=1}^n(a_i\times(i-1))$。然后再看高位，$a_i$ 会被放在高位 $n-i$ 次，这 $n-i$ 次之和就是 $a_i\times(\sum\limits_{j=i+1}^n10^{s_j})$，其中后面部分可以倒着枚举时一边枚举一边处理。总答案就是 $\sum\limits_{i=1}^n(a_i\times(i-1))+\sum\limits_{i=1}^n(a_i\times(\sum\limits_{j=i+1}^n10^{s_j}))$。
# 代码
```cpp
# include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <int, int> pii;
const ll mod = 998244353;
int n, a[200005];
ll sum, ans, tmp;
int main () {
	ios::sync_with_stdio (0);
	cin.tie (0);
	cout.tie (0);
	cin >> n;
	for (int i = 1; i <= n; ++ i)
		cin >> a[i], ans += a[i] * (i - 1ll), ans %= mod;
	for (int i = n; i; -- i) {
		ans += sum * a[i], ans %= mod;
		tmp = 1;
		while (a[i])
			a[i] /= 10, tmp *= 10;
		sum += tmp, sum %= mod;
	}
	cout << ans;
	return 0;
}
```

---

## 作者：2011FYCCCTA (赞：0)

[原题](https://www.luogu.com.cn/problem/AT_abc353_d)

---
### 分析

以下用 $d(x)$ 表示 $x$ 的位数。

题目中的 $f(x ,y)$ 实际上求的就是 $x \times 10^{d(y)}+y$，所以，

$$\sum_{i=1}^{N-1}\sum_{j=i+1}^{N}f(A_i,A_j)$$ 

就可以写成：

$$\sum_{i=1}^{N-1}\sum_{j=i+1}^{N}A_i\times 10^{d(A_j)}+A_j$$

展开后即为：

$$\sum_{i=1}^{N-1}(A_i\times \sum_{j=i+1}^{N}10^{d(A_j)}+\sum_{j=i+1}^{N}A_j)$$

后两项用前缀和预处理一下即可。

---
### 代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int mod = 998244353;
int n , a[200005] , s1[200005],s2[200005],ans;
signed main()
{
    cin >> n;
    for (int i = 1 ; i <= n ; i++)
    {
		cin >>a[i]; 
		s1[i] = (s1[i - 1] + a[i]) % mod;
		int d = 1, x = a[i];
		while(x) {x /= 10; d *= 10;}
		s2[i] = (s2[i - 1] + d) % mod;
	}
    for (int i = 1 ; i <= n ; i++)
        ans = (ans + a[i] * (s2[n] - s2[i] + mod) % mod + (s1[n] - s1[i]+mod) % mod) % mod;
    cout<<ans%mod;
    return 0;
}
```

---

## 作者：ZettaByte (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc353_d)

### 题意

定义 $f(x, y)$ 为将 $x$ 和 $y$ 拼接在一起后的数。给出数列 $a$，求 $\displaystyle \sum_{i=1}^{N-1}\sum_{j=i+1}^N f(a_i,a_j)$。

### 解法

我们可以分开考虑每个数 $a_i$ 的贡献。

- 当 $j>i$ 时，设 $a_j$ 的位数为 $x$，则 $a_i$ 对答案的贡献为 $10^x\times a_i$；
- 当 $j<i$ 时，$a_i$ 对答案的贡献为 $a_i$。

具体实现时可以倒着枚举。

#### AC CODE：

```cpp
#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int mod = 998244353;
ll a[200010];
ll mpow(ll x, ll y) { ll ret = 1; for (int i = 1; i <= y; i++) ret *= x, ret %= mod; return ret; }

int main()
{
	int n; ll tmp = 0, ret = 0; scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", &a[i]);
	for (int i = n; i >= 1; i--)
	{
//		printf("%lld %lld\n", a[i], (tmp + i - 1));
		ret += a[i] * (tmp + i - 1), ret %= mod;
//		printf("%lld\n", mpow(10LL, to_string(i).size() + 1));
		tmp += mpow(10LL, to_string(a[i]).size()), tmp %= mod;
	} printf("%lld\n", ret);
	return 0;
}
```

---

## 作者：_zqh_ (赞：0)

赛后 5 min 就 AC 了，我太菜了。
# 思路简述
我们把 $f$ 函数拆一下：

$$
f(A_i,A_j)=A_i \times 10^{g(A_j)} + A_j
$$

其中 $g$ 表示数的位数；

考虑每个数作为后面的数的情况，那么第 $i$ 个数对答案的总贡献就是：

$$
A_i \times (i - 1)
$$

则每个数作为前面的数的贡献：

$$
A_i \times(\sum^{n}_{j=i+1}10^{g(A_j)})
$$

那么答案为：

$$
\sum^{n}_{i=1}A_i \times (i - 1 + \sum^{n}_{j=i+1}10^{g(A_j)})
$$

用前缀和维护 $j$ 这一维即可。

这里笔者的代码是将两种贡献分开算的。

[code](https://atcoder.jp/contests/abc353/submissions/53386669)。

---

## 作者：qw1234321 (赞：0)

考虑到题目中的柿子中的 $A_j$ 对和的贡献仅为 $A_j$，$A_i$ 的贡献为 $A_i \times (10 ^ {g(A_j)})$。

其中 $g(A_j)$ 为 $A_j$ 的位数。

那么就很简单了，枚举每一个数 $a_i$，则 $a_i$ 当柿子中的 $A_j$ 时，会产生 $a_i \times (i - 1)$ 的贡献，$a_i$ 当柿子中的 $A_i$ 时，会产生 $a_i \times b_{i,j} \times 10 ^ {j}$ 的贡献。

其中 $b_{i,j}$ 为 $a_i$ 后面位数为 $j$ 的数有多少个，这个可以预处理。

在 $[1,10]$ 范围内枚举 $j$ 即可，还要时刻注意取模问题（本人因这个而吃了两发罚时）。

时间复杂度约 $\mathcal O(10 \times n)$。

[code.](https://atcoder.jp/contests/abc353/submissions/53353690)

---

## 作者：int_stl (赞：0)

一道前缀和好题。

话不多说，先推式子：

$$
\sum_{i=1}^{N-1}\sum_{j=i+1}^{N}f(A_i,A_j) \\
=\sum_{i=1}^{N-1}(\sum_{j=i+1}^{N}A_i \times 10^{\lfloor\log_{10}A_j\rfloor+1}+A_j) \\
=\sum_{i=1}^{N-1}(\sum_{j=i+1}^{N} A_i \times 10^{\lfloor\log_{10}A_j\rfloor+1}+\sum_{j=i+1}^{N}A_j) \\
=\sum_{i=1}^{N-1}(A_i \times \sum_{j=i+1}^{N}10^{\lfloor\log_{10}A_j\rfloor+1}+\sum_{j=i+1}^{N}A_j)
$$

可以发现，里面两个求和的部分都可以用前缀和维护，这样时间复杂度为 $O(n)$，能轻松通过此题。

代码如下：
```cpp
#include <iostream>
#include <cmath>
using namespace std;
typedef long long ll;
const ll mod = 998244353;
int n;
ll a[200006];
ll pre[200006];
ll pre1[200006];
int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pre[i] = (pre[i - 1] + a[i]) % mod;
        pre1[i] = (pre1[i - 1] + (ll)pow(10, (ll)(log10(a[i])) + 1)) % mod;
    }
    ll ans = 0;
    for (int i = 1; i < n; i++) {
        ll t = (pre[n] - pre[i] + mod) % mod;
        t = (t + a[i] % mod * ((pre1[n] - pre1[i] + mod) % mod) % mod) % mod;
        ans = (ans + t) % mod;
    }
    cout << ans;
}
```

---

## 作者：Pentiment (赞：0)

## ABC353D 题解

最 Sigma Problem 的一集。

### 题目大意

定义 $f(x,y)$ 是将 $x,y$ 拼接起来（像字符串那样）后的值。给你一个长度为 $n$ 的序列 $a_i$，求：
$$
\sum_{i=1}^{n-1}\sum_{j=i+1}^nf(a_i,a_j)
$$

### Solution

发现 $f(x,y)$ 其实就是将 $x$ 的十进制右移 $\lfloor\lg y\rfloor+1$ 位后与 $y$ 相加的值，即：
$$
f(x,y)=x\cdot10^{\lfloor\lg y\rfloor+1}+y
$$
原式化为：
$$
\sum_{i=1}^{n-1}\sum_{j=i+1}^nf(a_i,a_j)=\sum_{i=1}^{n-1}\sum_{j=i+1}^n(a_i\cdot10^{\lfloor\lg a_j\rfloor+1}+a_j)=\sum_{i=1}^{n-1}a_i\sum_{j=i+1}^n10^{\lfloor\lg a_j\rfloor+1}+\sum_{i=2}^n(i-1)a_i
$$
发现前半部分可以做后缀和，后半部分可以直接求，两者相加即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
void read(int &a) { a = 0; char c = getchar(); while (c < '0' || c > '9') c = getchar(); while (c >= '0' && c <= '9') a = a * 10 - '0' + c, c = getchar(); }
typedef long long ll;
const int N = 200005, mod = 998244353;
int n, a[N], sum[N], Pow[11] = {1}, ans;
int Log(int x) { int y = 0; while (x) x /= 10, y++; return y; }
int main() {
	for (int i = 1; i <= 10; i++) Pow[i] = Pow[i - 1] * 10 % mod;
	read(n);
	for (int i = 1; i <= n; i++) read(a[i]);
	for (int i = n; i >= 1; i--) sum[i] = (sum[i + 1] + Pow[Log(a[i])]) % mod;
	for (int i = 1; i < n; i++) ans = (ans + (ll)a[i] * sum[i + 1]) % mod;
	for (int i = 2; i <= n; i++) ans = (ans + (ll)a[i] * (i - 1)) % mod;
	printf("%d", ans);
}
```

---

## 作者：SkyLines (赞：0)

## Translate

定义 $f(x,y)$ 如下：

将 $x,y$ 的十进制表示为字符串，按顺序连接得到 $z$，$f(x,y)$ 的十进制数就为 $z$。

例如，$f(4,14)=414$，$f(1,14)=114$，$f(11,45)=1145$。

有一个数组 $A=(A_1,\dots,A_N)$，求：

$$\displaystyle \sum_{i=1}^{N-1}\sum_{j=i+1}^N f(A_i,A_j)$$

## Solution

设 $g(k)$ 为 $k$ 在十进制下的位数。

首先观察样例：$A=(3,14,15)$。

可以得到：

* $f(A_1,A_2)=314=3 \times 10^2 + 14$

* $f(A_1,A_3)=315=3 \times 10^2 + 15$

* $f(A_2,A_3)=1415=14 \times 10^2 + 15$

很明显 $f(x,y)=x \times 10^{g(y)}+y$。

总和为：$3 \times (10^2+10^2)+14 \times 10^2+14+15 \times 2=2044$。

可以发现：

当 $A_i$ 为 $f(x,y)$ 中的 $y$ 时，对答案的贡献为 $(i-1) \times A_i$。

当 $A_i$ 为 $f(x,y)$ 中的 $x$ 时，对答案的贡献为 $\sum_{j=i+1}^N 10^{g(A_j)} \times A_i$，这一部分可以用后缀和。

## Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int max_(int aa, int bb){
	return aa > bb ? aa : bb;
}
int min_(int aa, int bb){
	return aa < bb ? aa : bb;
}
int abs_(int aa){
	return aa > 0 ? aa : -aa;
}
int pow_(int aa, int bb, int cc){
	int ans = 1;
	while(bb){
		if(bb & 1) ans = ans * aa % cc;
		aa = aa * aa % cc;
		bb >>= 1;
	}
	return ans;
}
const int N = 2e5 + 5, mod = 998244353;
int n, a[N];
long long summ[N], ans, anss;
long long mult(int aa, int bb){
	ans = 1;
	for(int i = 1; i <= bb; i++){
		ans *= aa;
	}
	return ans;
}
int get_(int aa){
	ans = 1;
	for(int i = 0; i <= aa; i++){
		if(ans * 10 > aa){
			return i;
		}else ans *= 10;
	}
	return -1;
}
int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		scanf("%d", &a[i]);
	}
	for(int i = n; i >= 1; i--) summ[i] = (summ[i + 1] + (mult(10, get_(a[i]) + 1))) % mod;
	for(int i = 1; i <= n; i++){
		anss = (anss + ((long long) i - 1) * a[i]) % mod;
		anss = (anss + summ[i + 1] * a[i]) % mod;
	}
	printf("%lld", anss);
	return 0;
}
```

---

