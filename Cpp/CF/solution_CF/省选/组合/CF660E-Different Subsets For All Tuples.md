# Different Subsets For All Tuples

## 题目描述

For a sequence $ a $ of $ n $ integers between $ 1 $ and $ m $ , inclusive, denote $ f(a) $ as the number of distinct subsequences of $ a $ (including the empty subsequence).

You are given two positive integers $ n $ and $ m $ . Let $ S $ be the set of all sequences of length $ n $ consisting of numbers from $ 1 $ to $ m $ . Compute the sum $ f(a) $ over all $ a $ in $ S $ modulo $ 10^{9}+7 $ .

## 样例 #1

### 输入

```
1 3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
14
```

## 样例 #3

### 输入

```
3 3
```

### 输出

```
174
```

# 题解

## 作者：TheLostWeak (赞：25)

[在博客查看](https://www.cnblogs.com/chenxiaoran666/p/CF660E.html)

**大致题意：** 有一个长度为$n$的数列，每个位置上数字的值在$[1,m]$范围内，则共有$m^n$种可能的数列。分别求出每个数列中本质不同的子序列个数，然后求和。

### 一些分析

首先，我们单独考虑空序列的个数$m^n$，然后接下来就可以只考虑非空序列的个数了。

假设有一个长度为$i$的子序列（$1\le i\le n$），且其在序列中的位置分别为$pos_1,pos_2,...,pos_i$，值分别为$val_1,val_2,...,val_i$。

则我们强制在$1\sim pos_1-1$范围内不能出现$val_1$，$pos_1+1\sim pos_2-1$范围内不能出现$val_2$，以此类推。

所以，在前$pos_i$个位置中，除$pos_{1\sim i}$这$i$个位置填$val_{i\sim i}$外，如上所述，其余$pos_i-i$个位置各有$m-1$种填法。

而在第$pos_i$个位置之后就可以随便填了，每个位置都有$m$种填法。

###  推式子

通过之前的分析，于是得到式子如下：

$$\sum_{i=1}^nm^i\sum_{j=i}^nC_{j-1}^{i-1}(m-1)^{j-i}m^{n-j}$$

对于这个式子的解释：

首先，用$i$枚举子序列长度，而长度为$i$的子序列共有$m^i$种可能。

接下来$j$枚举$pos_i$，而$pos_{1\sim i-1}$依次选择$[1,pos_i-1]$（即这里的$[1,j-1]$）这个范围内的任意位置都是合法的，就相当于在$j-1$个位置中选择$i-1$个位置，方案数就是$C_{j-1}^{i-1}$。

从前文可得，$pos_i-i$（即这里的$j-i$）个位置有$m-1$种填法，$n-pos_i$（即这里的$n-j$）个位置有$m$种填法。

于是便得到上述式子。

然后就是化简：

先移项，把$m^i$移进去得到：

$$\sum_{i=1}^n\sum_{j=i}^nC_{j-1}^{i-1}(m-1)^{j-i}m^{n-j+i}$$

改变枚举顺序，得到：

$$\sum_{j=1}^n\sum_{i=1}^jC_{j-1}^{i-1}(m-1)^{j-i}m^{n-j+i}$$

观察到组合数中的$i-1$和$j-1$，不难想到直接将枚举的$i,j$减$1$，即：

$$\sum_{j=0}^{n-1}\sum_{i=0}^{j-1}C_j^i(m-1)^{(j+1)-(i+1)}m^{n-(j+1)+(i+1)}$$

然后我们可以化简一下系数，发现这些$1$和$-1$恰好抵消了，得到：

$$\sum_{j=0}^{n-1}\sum_{i=0}^{j-1}C_j^i(m-1)^{j-i}m^{n-j+i}$$

然后我们拎出$m^{n-j}$，就可以得到：

$$\sum_{j=0}^{n-1}m^{n-j}\sum_{i=0}^{j-1}C_j^i(m-1)^{j-i}m^i$$

那这样有什么好处呢？

回想一下**二项式定理**：$(x+y)^n=\sum_{i=0}^{n-1}x^iy^{n-i}$。

这似乎与上面式子的后半部分有几分相似。

于是就可以化简得到：

$$\sum_{j=0}^{n-1}m^{n-j}((m-1)+m)^j=\sum_{j=0}^{n-1}m^{n-j}(2m-1)^j$$

这个式子可以$O(nlogn)$快速幂计算，也可以直接$O(n)$计算。

总而言之，可以过了。

### 代码

```cpp
#include<bits/stdc++.h>
#define Tp template<typename Ty>
#define Ts template<typename Ty,typename... Ar>
#define Reg register
#define RI Reg int
#define Con const
#define CI Con int&
#define I inline
#define W while
#define N 1000000
#define X 1000000007
#define Qinv(x) Qpow(x,X-2)
#define Inc(x,y) ((x+=(y))>=X&&(x-=X))
using namespace std;
int n,m;
I int Qpow(RI x,RI y) {RI t=1;W(y) y&1&&(t=1LL*t*x%X),x=1LL*x*x%X,y>>=1;return t;}//快速幂
int main()
{
    RI i,ans,p1,p2,b1,b2;
    scanf("%d%d",&n,&m),ans=p1=Qpow(m,n),p2=1,b1=Qinv(m),b2=(1LL*2*m-1)%X;//初始化
    for(i=0;i^n;++i) Inc(ans,1LL*p1*p2%X),p1=1LL*p1*b1%X,p2=1LL*p2*b2%X;//O(n)计算答案
    return printf("%d",ans),0;//输出答案
}
```

---

## 作者：TLE_Automat (赞：9)

Problem E :

~~首行求赞qwq~~

**题意：**

对于一个序列 $a$ ，定义 $f(a)$ 为 $a$ 的不同子序列个数。

现在要求值域为 $[1,m]$ 的整数，长度为 $n$ 的所有序列 $a$ 的 $f(a)$ 之和 $\bmod 10^9+7$ 。

**数据范围：**

$1\le n,m\le 10^6$ 。

**做法：**

做这种题的经典套路是逆向思考，计算每种方案对答案的贡献。

所以我们考虑对于每个子序列对答案产生了产生了多大贡献，说人话就是计算每个子序列被多少不同的序列包含过，并且求和。

那我们如何考虑每个子序列呢？显然不能直接枚举子序列，所以我们需要继续从整体考虑。注意到 $n\le 10^6$ ，所以我们容易考虑到枚举子序列的长度 $k$ 然后进行计算。

假设当前子序列长度为 $k$ ，那么不加限制地填数总共有 $m^k$ 种填法。现在考虑在该子序列中插入一些数来还原整个序列，但为了不重复统计，我们要求该子序列在还原出的序列中出现位置最靠前，即出现位置下标的字典序最小。

假设我们的子序列为 $b_1,b_2,...,b_{k-1},b_k$ 。

容易发现，为了满足该子序列在还原出的序列中第一次出现，那么在 $b_1$ 前不能填与 $b_1$ 相等的数字，在 $b_1$ 到 $b_2$ 之间不能填与 $b_2$ 相等的数字，在 $b_{i-1}$ 到 $b_{i}$ 之间不能填与 $b_i$ 相等的数字。

但还要考虑 $b_k$ 之后可以填 $[1,m]$ 中任意的整数。假设 $b_k$ 后面还有 $j$ 个元素，那么对于子序列元素总共有 $m^k$ 种填法，$b_k$ 之前的非子序列元素有 $(m-1)^{n-k-j}$ 种填法，对于 $b_k$ 之后的元素有 $m^j$ 种填法。

最后一步，我们需要考虑子序列元素摆放的位置，因为 $b_k$ 后面有 $j$ 个元素，所以 $b_k$ 必须放在倒数第 $j+1$ 个位置，但是对于 $b_1$ 到 $b_{k-1}$ 的元素摆放位置并没有任何限制，所以总共有 $\binom {n-j-1} {k-1}$ 种选择位置的方法。

所以对于长度为 $k$ 所有子序列对答案的贡献为 $\sum\limits_{j=0}^{n-k} m^k\cdot m^j\cdot (m-1)^{n-k-j}\cdot\binom{n-j-1}{k-1}$ 。

所以最后的答案为：

$\large\sum\limits_{k=1}^n\sum\limits_{j=0}^{n-k} m^k\cdot m^j\cdot (m-1)^{n-k-j}\cdot\binom{n-j-1}{k-1}$ 。

但以上式子的时间复杂度为 $O(n^2)$ ，算上求逆元为 $O(n^2\log_2\text{Mod})$ ，显然直接爆炸，所以下面进入~~推柿子~~环节。

----

首先观察式子，我们注意到右边的组合数，不管 $k,j$ 如何变化，永远是不重复的，所以我们考虑每一个组合数 $\binom{n-j-1}{k-1}$ 被乘的系数 $m^k\cdot m^j\cdot (m-1)^{n-k-j}$ 。

式子变量太多看起来太冗杂怎么办，我们设 $s=k+j$ ，那么系数可化为 $m^s\cdot (m-1)^{n-s}$ ，组合数可被化为 $\binom{n-j-1}{s-j-1}$ 。

我们考虑枚举 $s$ ，那么就有了式子：

*原式* $\ =\large\sum\limits_{s=1}^{n} m^s\cdot(m-1)^{n-s}\sum\limits_{j=0}^{s-1}\binom{n-j-1}{s-j-1}$ 。

考虑这个式子为什么是对的，由于组合数已经是不重复的，所以对于每一个组合数 $\binom{n-j-1}{s-j-1}$ 的系数一定是 $m^s\cdot (m-1)^{n-s}$ ，所以该式子不重不漏地用另一种方式统计了原式子，所以是对的。

然后我们继续化简，发现右边的组合数求和实际上是在求杨辉三角一条斜边的和：

```ts
1
1 1
1 2 1
1 3 3 1
1 4 6 4 1
1 5 10 10 5 1
1 6 15 20 15 6 1
     ....
```

我们找规律发现一条斜边上的数字的和等于这条斜边最右下角的正下方的数字的值，比如 $1+3+6+10=20$ ，然后我们就可以发现 $\sum\limits_{j=0}^{s-1}\binom{n-j-1}{s-j-1}=\binom{n}{s-1}$ 。

所以：

*原式* $\ =\large\sum\limits_{s=1}^{n} m^s\cdot(m-1)^{n-s}\binom{n}{s-1}$ 。

然后我们就可以 $O(n)$ 计算了。

$Source:(by\_myself)$

```cpp
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int,int> pii;

const int MAXN=1e6+10;
const int Mod=1e9+7;

inline ll ksm(ll x,ll y)
{
    ll res=1;
    while(y)
    {
        if(y&1) res = res * x %Mod;
        x = x * x %Mod;
        y >>= 1;
    }
    return res;
}

int n,m;
ll fac[MAXN];

inline ll inv(ll x){ return ksm(x,Mod-2); }
inline ll C(ll x,ll y){ return fac[x] * inv(fac[y]) %Mod *inv(fac[x-y]) %Mod; } 

int main()
{
    scanf("%d%d",&n,&m);

    fac[0]=1;
    for(int i=1;i<=n;i++) fac[i] = fac[i-1] * i %Mod;

    ll ans=0;
    for(int s=1;s<=n;s++)
        ans = (ans + ksm(m,s) * ksm(m-1,n-s) %Mod * C(n,s-1) %Mod) %Mod;

    ans = (ans + ksm(m,n)) %Mod;
    
    printf("%lld\n",ans);

    return 0;
}
```


---

## 作者：fade_away (赞：7)

## Solution

蒟蒻表示不会推式子，那我们就 $dp$ ！

考虑如果知道序列 $a$ 长啥样怎么做，这显然是一个经典的子序列自动机上 $dp$ 。即 $f_i$ 表示以 $i$ 结尾的本质不同子序列个数，转移时枚举上一个数是 $x$ ，找到最大的 $j$ 满足 $j<i$ 且 $a_j=x$，然后令 $f_i= f_i+f_j$。

最终的本质不同子序列个数就是每个数最后一次出现的位置的 $f$ 的和。

然后考虑这道题怎么做，显然可以写出这样的式子：
$$
f_{i,j}=m^{i-1}+\sum_{k<i,t}f_{k,t}\times (m-1)^{i-k-1}
$$
其中 $f_{i,j}$ 表示前 $i$ 位，$a_i=j$ 的所有序列中以 $a_i$ 为结尾的本质不同子序列个数，$m^i$ 表示只取 $a_i$ 这一个数的方案，$f_{k,t}\times(m-1)^{i-k-1}$ 表示 $i$ 前面的最后一个值为 $t$ 的数下标是 $k$ 的方案中本质不同子序列的个数和。

这个东西是 $O(n^4)$ 的，但是我们发现所有数是等价的，这意味着我们可以对于每个 $i$ 把所有 $f_{i,j}$ 合并。

于是转移变成了：
$$
f_{i}=m^{i}+\sum_{k<i}f_{k}\times (m-1)^{i-k-1}\times m
$$

这个东西就可以用前缀和之类的东西直接 $O(n)$ 计算了。

最终的答案就是：
$$
m^n+\sum_{i=1}^nf_i\times (m-1)^{n-i}
$$

总时间复杂度 $O(n)$ 。

## Code
```cpp
int f[MAXN];
signed main() {
#ifndef ONLINE_JUDGE
	freopen("a.in", "r", stdin);
#endif
	int n, m, ans = 1;
	read(n), read(m), f[0] = 1, f[1] = m;
	for (int i = 1; i <= n ; ++ i) ans = 1ll * ans * m % mods;
	for (int i = 2, sum = 0, mul = m; i <= n ; ++ i) {
		sum = (1ll * sum * (m - 1) + f[i - 1]) % mods;
		mul = 1ll * mul * m % mods;
		f[i] = (1ll * sum * m + mul) % mods;
	}
	for (int i = n, mul = 1; i >= 1 ; -- i) {
		(ans += 1ll * f[i] * mul % mods) %= mods;
		mul = 1ll * mul * (m - 1) % mods;
	}
	print(ans);
	return 0;
}

```




---

## 作者：kouylan (赞：5)

首先空序列有 $m^n$ 个，接下来就算非空序列。

我们很容易想到按照子序列长度分开算。对于长度为 $i$ 的子序列，一共有 $m^i$ 个。设每一位的下标为 $x_1,x_2\dots x_i$。为了避免重复，对于一段相同的值，我们可以规定选择最后面的。因此我们要保证在 $(x_{k-1},x_k)$ 中，不能出现与 $x_{k}$ 相等的数，那这一段内每个位置有 $m-1$ 个选择。但是 $x_n$ 之后的位置就随便填了。

所以我们可以枚举 $x_i$，那么答案式子就是

$$\sum\limits_{i=1}^n m^i\sum\limits_{j=i}^n\dbinom{j-1}{i-1}(m-1)^{j-i}m^{n-j}$$

下面就开始推式子。

先置换一下

$$\sum\limits_{j=1}^n m^{n-j}\sum\limits_{i=1}^j\dbinom{j-1}{i-1}(m-1)^{j-i}m^i$$

$$\sum\limits_{j=0}^{n-1} m^{n-j-1}\sum\limits_{i=0}^j\dbinom{j}{i}(m-1)^{j-i}m^{i+1}$$

$$\sum\limits_{j=0}^{n-1} m^{n-j}\sum\limits_{i=0}^j\dbinom{j}{i}(m-1)^{j-i}m^i$$

我们发现里面这一个和式就是二项式定理，所以式子最终就变成

$$\sum\limits_{j=0}^{n-1} m^{n-j}(2m-1)^j$$

下面是 AC 代码
```cpp
#include <bits/stdc++.h>
using namespace std;

#define int long long

const int M = 1e9+7ll;

int n,m,ans;

int ksm(int x,int w)
{
	int s=1;
	while(w)
	{
		if(w&1)
			s = s*x%M;
		x = x*x%M;
		w >>= 1;
	}
	return s;
}

signed main()
{
	cin>>n>>m;
	ans = ksm(m,n);
	for(int j=0;j<n;j++)
		ans = (ans+ksm(m,n-j)*ksm(2*m-1,j))%M;
	cout<<ans<<endl;
	
	return 0;
}
```

祝大家 AC 愉快！

---

## 作者：wangxuye (赞：3)

### 题目链接
[CF660E Different Subsets For All Tuples](https://www.luogu.com.cn/problem/CF660E)
### 题目大意
有一个长度为 $n$ 的数列，每个位置上数字的值在 $[1,m]$ 范围内，则共有 $m^n$ 种可能的数列。分别求出每个数列中本质不同的子序列个数（包含空序列），然后求和，答案对 $10^9+7$ 取模。$(1\le n,m\le10^6,1\le n,m\le10^6)$
### 题目思路
这道一看就非常数学的题目当然要推式子辣。  
我们先枚举子序列长度（空序列是所有 $m^n$ 个序列的子序列），然后统计这样的子序列是多少个序列的子序列求和~~然后就做完了~~。  
我们会发现如果有一个子序列在一个序列中出现了多次就很难统计了，所以我们可以强制选字典序最小的。  
这样就可以得到一个式子辣
$$\begin{aligned}m^n+\sum_{i=1}^nm^i\sum_{j=0}^{n-i}(m-1)^j\times m^{n-i-j}\times C_{i+j-1}^{i-1} \end{aligned}$$
解释一下：  
$m^n$ 是空序列的答案  
$i$ 的 $\sum$ 是枚举长度， $j$ 的 $\sum$ 是枚举子序列在原序列中的最后一位的位置减去子序列长度（即选子序列的时候跳过了多少个位置）。  
由于我们上面强制选了字典序最小的子序列，所以任意两个相邻的被选进子序列中的数之间的所有位置都不能和后面被选的数相等，所以每个位置都有 $m-1$ 种选法，共有 $(m-1)^{j}$ 种方案。  
选完子序列后，还剩下 $n-i-j$ 个位置，每个位置随意填，共有 $m^{n-i-j}$ 种方案。  
跳过的位置要放在 $i$ 段中（子序列相邻两个数之间都有一个，第一个之前也有一段，共 $i$ 段），由隔板法可知有 $C_{i+j-1}^{i-1}$ 种方案。  
然后我们接着推：  
$$\begin{aligned}&m^n+\sum_{i=1}^nm^i\sum_{j=0}^{n-i}(m-1)^j\times m^{n-i-j}\times C_{i+j-1}^{i-1}\\=&m^n+\sum_{i=1}^n\sum_{j=0}^{n-i}(m-1)^j\times m^{n-j}\times C_{i+j-1}^{i-1}\\=&m^n+\sum_{j=0}^n(m-1)^j\times m^{n-j}\sum_{i=1}^{n-j}C_{i+j-1}^{j}\\=&m^n+\sum_{j=0}^n(m-1)^j\times m^{n-j}\times C_{n}^{j+1}\\=&m^n+\frac{m}{m-1}\sum_{j=0}^n(m-1)^{j+1}\times m^{n-(j+1)}C_{n}^{j+1}\\=&m^n+\frac{m}{m-1}\sum_{i=1}^n(m-1)^{i}\times m^{n-i}C_{n}^{i}\\=&m^n+\frac{m}{m-1}((\sum_{i=0}^n(m-1)^{i}\times m^{n-i}C_{n}^{i})-m^n)\\=&m^n+\frac{m}{m-1}\cdot((2m-1)^n-m^n) \end{aligned}$$
然后我们就可以愉快的用你喜欢的方式计算辣。  
上代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
const int P=1e9+7;
inline int ADD(int a,int b) { return a+b>=P?a+b-P:a+b; }
inline int MINUS(int a,int b) { return a-b<0?a-b+P:a-b; }

inline int quickmi(int x,int n)
{
	int res=1;
	for(;n;n>>=1)
	{
		if(n&1) res=1ll*res*x%P;
		x=1ll*x*x%P;
	}
	return res;
}
#define ni(x) quickmi(x,P-2)

inline int read()
{
	int s=0;
	bool flag=false;
	char ch=getchar();
	for(;ch<'0'||ch>'9';ch=getchar()) if(ch=='-') flag=true;
	for(;'0'<=ch&&ch<='9';ch=getchar()) s=(s<<3)+(s<<1)+(ch^'0');
	if(flag) return -s;
	return s;
}

int main()
{
	int n=read(),m=read();
	if(m==1) printf("%d\n",n+1);
	else printf("%d\n",ADD(quickmi(m,n),1ll*m*ni(m-1)%P*MINUS(quickmi(m+m-1,n),quickmi(m,n))%P));
	return 0;
}
```

---

## 作者：⑨_Cirno_ (赞：3)

我不会推什么式子，所以只好用这种菜鸡办法算>_<

假设我们已经得到了一个序列，我们来dp解决这个问题

设fi表示以i结尾的序列个数，s表示总序列个数

则每次往结尾加一个数a时，容易得到fa+=s，s=s*2-fa（这两步同时进行，即后一个式子加的fa是改变之前的

考虑使用矩阵

则对于每一个a，我们可以得到一个转移矩阵：

$$\begin{matrix}1 & 0 & 0 & ... & 0&0&...&0\\0 & 1 & 0 & ... & 0&0&...&0 \\0 & 0 & 1 & ... & 0&0&...&0 \\... & ... & ... & ...&...&...&...&...\\0&0&0&...&0&0&...&1\\0&0&0&...&0&1&...&0\\... & ... & ... & ...&...&...&...&...\\0&0&0&...&-1&0&...&2\end{matrix}$$

对于每个位置显然每个转移矩阵都是可能的，所以我们可以把可能的转移矩阵加起来，得到

$$\begin{matrix}m-1&0&...&1\\0&m-1&...&1\\...&...&...&...\\-1&-1&...&2m\end{matrix}$$

求该矩阵n次方然后乘初始矩阵就行

但我们发现这个矩阵很对称，这导致每次乘初始矩阵后前m行都是相同的

所以前m行用一个变量记就行了

这样矩阵是2*2的，可以暴力O(n)或快速幂O(logn)算

Code：
```
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long long LL;
const int M=1000000007;
#define ri register int 
#define rl register long long
int n,m;
ll ans=1,s=0;
ll qpow(ll a,ll b)
{
	ll s=a,ans=1;
	while(b)
	{
		if(b&1)
			ans=ans*s%M;
		s=s*s%M;
		b>>=1;
	}
	return ans;
}
int main()
{
	scanf("%d %d",&n,&m);
	for(ri i=1;i<=n;++i)
	{
		ll tmp=ans;
		ans=(ans*2*m%M-s*m)%M;
		s=(s*(m-1)+tmp)%M;
	}
	cout<<(ans%M+M)%M;
}

```


---

## 作者：MurataHimeko (赞：2)

考虑去计算每个子序列的贡献。

当两个子序列长度相同时，他们的贡献相同。只需要置换一下即可。

那么考虑去枚举对应长度去计算贡献。

发现贡献分为两段，第一段是子序列第一次出现前，第二段是子序列第一次出现后。

首先，根据贪心的思想，子序列的每个元素选的一定是选尽量靠前的位置。
那么对于第一段，如果不是钦定的子序列的位置，那么这个位置能选的方案是 $m-1$，因为不能提前选到下一个元素。对于第二段就无所谓了，方案是 $m$，因为已经选完了子序列。

考虑枚举最后一个元素出现的位置，也就是第一段和第二段的分界线。

长度为 $k$ 的子序列的第 $k$ 个元素在第 $j$ 个位置出现。


$$\sum_{k=1}^{n} m^k \sum_{j=k}^{n} m^{n-j} (m-1)^{j-k} \binom{j-1}{k-1} $$

先枚举 $j$。

$$\sum_{j=1}^{n} m^{n-j+1} \sum_{k=1}^{j} m^{k-1} (m-1)^{j-k} \binom{j-1}{k-1}$$

枚举 $j-1,k-1$。

$$\sum_{j=0}^{n-1} m^{n-j} \sum_{k=0}^{j} m^k (m-1)^{j-k} \binom{j}{k}$$

后面一项是二项式定理的形式。

$$\sum_{j=0}^{n-1} m^{n-j} (2m-1)^j$$

可以 $O(n)$ 计算。

---

## 作者：chenxia25 (赞：2)

我们考虑以子序列为贡献。为了去重，我们对每个子序列数以它为最前面的子序列的数列。

我们考虑对于一个长度为 $len$ 的子序列 $v_{1\sim len}$，将它放在位置 $pos_{1\sim len}$，有多少种数列。显然这 $len$ 个位置是固定的了，然后在 $p_{i-1}+1\sim p_i-1$ 的地方，不能有 $v_i$ 出现，其它值都能取（我当时课上没做出来就是因为这个地方想假了。我以为 $v_{i\sim len}$ 都不可以取的，实际上可以）。然后 $p_{len}+1\sim n$ 是都可以。那么方案数就是 $m^{n-p_{len}}(m-1)^{p_{len}-len}$。

然后因为对每个长度相同的、最后一个位置相同的子序列，贡献都是一样的，于是乘法原理可得答案式 $\sum\limits_{i=1}^n\sum\limits_{j=1}^n\dbinom{j-1}{i-1}m^{n-j+i}(m-1)^{j-i}$。直接算会炸，它一脸二项式定理的样子，考虑先交换 $i,j$，然后随便推得 $\sum\limits_{i=1}^nm^n\left(\dfrac{m-1}m+1\right)^{i-1}$。线对显然是会的，又显然可以做到线性。

---

## 作者：wsyhb (赞：0)

## 题解

考虑一个长度为 $k$ 的子序列 $(a_1,a_2,\cdots,a_k)$ 对答案的贡献，可以得到如下式子：

$$\sum_{i=k}^{n}\binom{i-1}{k-1}(m-1)^{i-k}m^{n-i}$$

**说明**：

枚举这个长度为 $k$ 的子序列的从左到右首次出现时 $a_k$ 的下标 $i$，则 $a_1,\cdots,a_{k-1}$ 的下标有 $\binom{i-1}{k-1}$ 种选法。

除去 $1$ 到 $i$ 位置中长度为 $k$ 子序列所占据的位置，剩余 $i-k$ 个，每个有 $m-1$ 种取值：设 $a_i$ 所在下标为 $b_i$，则对于 $0 \le t <k$，$b_t < x < b_{t+1}(b_0=0)$ 的位置 $x$，取值不能是 $a_{t+1}$。

$i+1$ 到 $n$ 号位置可以任取，均有 $m$ 种取值。

则题目所求答案为

$$m^n+\sum_{k=1}^{n}m^k\sum_{i=k}^{n}\binom{i-1}{k-1}(m-1)^{i-k}m^{n-i}$$

（$m^n$ 是空子序列的贡献，$m^k$ 是因为长度为 $k$ 的子序列有 $m^k$ 种，**下文省略 $m^n$ 这一部分**）

似乎不太好处理，考虑换一下 $\sum$ 的顺序：

$$\sum_{i=1}^{n}m^{n-i}\sum_{k=1}^{i}\binom{i-1}{k-1}(m-1)^{i-k}m^k$$

发现 $(m-1)^{i-k}$ 的系数是 $\binom{i-1}{k-1}=\binom{i-1}{i-k}$，于是从 $m^k$ 中提一个 $m$ 出来，以使用**二项式定理**：

$$
\begin{aligned}
&\sum_{i=1}^{n}m^{n-i+1}\sum_{k=1}^{i}\binom{i-1}{k-1}(m-1)^{i-k}m^{k-1}\\
=&\sum_{i=1}^{n}m^{n-i+1}[(m-1)+m]^{i-1}\\
=&\sum_{i=1}^{n}m^{n-i+1}(2m-1)^{i-1}
\end{aligned}
$$

预处理 $m$ 和 $2m-1$ 的幂即可。总**时间复杂度**为 $O(n)$。

## 代码

``` cpp
#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
const int max_n=1e6+5;
int pow_m[max_n],pow_2m_minus_1[max_n];
int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	pow_m[0]=pow_2m_minus_1[0]=1;
	for(int i=1;i<=n;++i)
	{
		pow_m[i]=1ll*pow_m[i-1]*m%mod;
		pow_2m_minus_1[i]=pow_2m_minus_1[i-1]*(2ll*m-1)%mod;
	}
	int ans=0;
	for(int i=1;i<=n;++i)
		ans=(ans+1ll*pow_m[n-i+1]*pow_2m_minus_1[i-1])%mod;
	ans+=pow_m[n];
	ans-=ans>=mod?mod:0;
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：tzc_wk (赞：0)

首先先给自己的博客打个广告：https://www.cnblogs.com/ET2006/

一道不那么一眼的 *2300

首先考虑怎样计算答案。空序列的贡献 $m^n$ 显然可以单独计算。然后对于每个序列，我们只用计算它第一次出现时候的贡献即可。

我们枚举这个子序列的长度 $len$，然后枚举它在原序列第一次出现的位置中，第一位的位置 $p_1$ 和它第一位的值 $v_1$——由于是第一次出现，所以原序列第 $1,2,3,\dots,p_1-1$ 位上的值都不应为 $v_1$，共有 $(m-1)^{p_1-1}$ 种选择，而 $v_1$ 共有 $m$ 种可能的值，所以贡献为 $m\times (m-1)^{p_1}$。同理再枚举 $p_2(p_1<p_2)$ 和 $v_2$，贡献为 $m\times (m-1)^{p_2-p_1}$，依次类推。假设最后一位在原序列中的位置为 $p_{len}$，那么原序列第 $len+1$ 位到第 $n$ 位显然想怎么填就怎么填，贡献为 $m^{n-p_{len}}$。最后根据乘法原理把所有贡献全乘在一起，可得一种 $p_1,p_2,\dots,p_{len}$ 对答案的贡献 $(m-1)^{p_{len}-len}\times m^{n-p_{len}+len}$

注意到这个贡献只与 $p_{len}$ 和 $len$ 有关，所以我们可以枚举 $p_{len}$ 和 $len$，那么合法的 $p_1,p_2,\dots,p_{len-1}$ 应当有 $\dbinom{p_{len}-1}{len-1}$ 种。故最终我们要求的答案即为（下文中用 $i$ 代替 $len$，$j$ 代替 $p_{len}$）

$$\sum\limits_{i=1}^n\sum\limits_{j=i}^n\dbinom{j-1}{i-1}\times (m-1)^{j-i}\times m^{n-j+i}$$

直接算显然会炸，考虑对原式进行一些变形：

转换枚举顺序：$\sum\limits_{j=1}^n\sum\limits_{i=1}^j\dbinom{j-1}{i-1}\times (m-1)^{j-i}\times m^{n-j+i}$

将 $m^{n-j}$ 提到外面，并将 $i$ 改为 $i+1$：$\sum\limits_{j=1}^nm^{m-j}\times\sum\limits_{i=0}^{j-1}\dbinom{j-1}{i}\times (m-1)^{j-i-1}\times m^{i+1}$

再把里面的 $m^{i+1}$ 拆成 $m^{i}\times m$：$\sum\limits_{j=1}^nm^{m-j+1}\times\sum\limits_{i=0}^{j-1}\dbinom{j-1}{i}\times (m-1)^{j-i-1}\times m^i$

发现里面那个 $\sum$ 中的东西长得一脸二项式定理的样子：$\sum\limits_{j=1}^nm^{m-j+1}\times(2m-1)^{j-1}$

大功告成。$\mathcal O(n\log n)$ 计算显然是没问题的，简单想想也能优化到 $\mathcal O(n)$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define fz(i,a,b) for(int i=a;i<=b;i++)
#define fd(i,a,b) for(int i=a;i>=b;i--)
#define ffe(it,v) for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define fill0(a) memset(a,0,sizeof(a))
#define fill1(a) memset(a,-1,sizeof(a))
#define fillbig(a) memset(a,63,sizeof(a))
#define pb push_back
#define ppb pop_back
#define mp make_pair
template<typename T1,typename T2> void chkmin(T1 &x,T2 y){if(x>y) x=y;}
template<typename T1,typename T2> void chkmax(T1 &x,T2 y){if(x<y) x=y;}
typedef pair<int,int> pii;
typedef long long ll;
template<typename T> void read(T &x){
	x=0;char c=getchar();T neg=1;
	while(!isdigit(c)){if(c=='-') neg=-1;c=getchar();}
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	x*=neg;
}
const int MOD=1e9+7;
int qpow(int x,int e){
	int ret=1;
	for(;e;e>>=1,x=1ll*x*x%MOD) if(e&1) ret=1ll*ret*x%MOD;
	return ret;
}
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	int ans=qpow(m,n),inv=qpow(m,MOD-2),iv=ans,pw=1;
	for(int i=1;i<=n;i++) ans=(ans+1ll*iv%MOD*pw%MOD)%MOD,iv=1ll*iv*inv%MOD,pw=1ll*pw*(2*m-1)%MOD;
	printf("%d\n",ans);
	return 0;
}
```

---

