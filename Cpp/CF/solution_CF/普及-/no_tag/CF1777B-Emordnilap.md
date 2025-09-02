# Emordnilap

## 题目描述

A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array). There are $ n! = n \cdot (n-1) \cdot (n - 2) \cdot \ldots \cdot 1 $ different permutations of length $ n $ .

Given a permutation $ p $ of $ n $ numbers, we create an array $ a $ consisting of $ 2n $ numbers, which is equal to $ p $ concatenated with its reverse. We then define the beauty of $ p $ as the number of inversions in $ a $ .

The number of inversions in the array $ a $ is the number of pairs of indices $ i $ , $ j $ such that $ i < j $ and $ a_i > a_j $ .

For example, for permutation $ p = [1, 2] $ , $ a $ would be $ [1, 2, 2, 1] $ . The inversions in $ a $ are $ (2, 4) $ and $ (3, 4) $ (assuming 1-based indexing). Hence, the beauty of $ p $ is $ 2 $ .

Your task is to find the sum of beauties of all $ n! $ permutations of size $ n $ . Print the remainder we get when dividing this value by $ 1\,000\,000\,007 $ ( $ 10^9 + 7 $ ).

## 说明/提示

For the first test case of the example, $ p = [1] $ is the only permutation. $ a = [1, 1] $ has $ 0 $ inversions.

For the second test case of the example, the permutations are $ [1, 2] $ and $ [2, 1] $ . Their respective $ a $ arrays are $ [1, 2, 2, 1] $ and $ [2, 1, 1, 2] $ , both of which have $ 2 $ inversions.

## 样例 #1

### 输入

```
3
1
2
100```

### 输出

```
0
4
389456655```

# 题解

## 作者：arrow_king (赞：4)

## 题目大意

一个 $1,2,\dots,n-1,n$ 的排列 $p$，显然共有 $n!$ 种排法。现在要根据一个长度为 $n$ 的排列 $p$ 创造一个长度为 $2n$ 的序列 $a$，构造方法是将 $p$ 和它的反转拼在一起。现在要求所有 $n!$ 个排列经过这个构造生成的序列的逆序对数量的和模 $10^9+7$ 的值。

$\sum n\le10^5,t\le10^5$。

## 思路

一个一个枚举排列显然是不现实的。来找找规律。

从 $n=3$ 考虑，一共会有 $3!=3\times2\times1=6$ 种排列。

计算一下逆序对总和：

- `1,2,3`：反转得到 `1,2,3,3,2,1`，共有 $6$ 个逆序对。
- `1,3,2`：反转得到 `1,3,2,2,3,1`，共有 $6$ 个逆序对。
- `2,1,3`：反转得到 `2,1,3,3,1,2`，共有 $6$ 个逆序对。
- `2,3,1`：反转得到 `2,3,1,1,3,2`，共有 $6$ 个逆序对。
- `3,1,2`：反转得到 `3,1,2,2,1,3`，共有 $6$ 个逆序对。
- `3,2,1`：反转得到 `3,2,1,1,2,3`，共有 $6$ 个逆序对。

然后就会发现每种排列的逆序对数量都是一样的，所以答案就可以由某个序列的逆序对数量乘上 $n!$ 得到。

还没完，为啥是一样的呢？

首先，假设原排列的逆序对个数为 $m$ 个，那么新生成的反转序列的逆序对个数是多少个呢？因为没有相同的数，所以显然是 $\dfrac{n(n-1)}{2}-m$ 个。（因为长度为 $n$ 的排列一共只会有 $\dfrac{n(n-1)}{2}$ 个二元对。）

那么前半段和后半段的逆序对总和就是 $\dfrac{n(n-1)}{2}$ 个。

再考虑后面的半段和前面的半段之间生成的逆序对，显然对于后面的任意一个数 $x$，在前面都会有 $x-1$ 个数比它小。所以答案就会加上
$$\sum\limits^n_{i=1}(i-1)=\dfrac{n(n-1)}{2}$$

好，合并一下就得到了答案是 $n!n(n-1)\bmod (10^9+7)$。

时间复杂度 $\mathcal O\left(t+\sum n\right)$。

## 代码

极度精简 $20$ 行代码

```cpp
#include<iostream>
#include<cstdio>
using namespace std;
#define mod 1000000007
#define il inline
#define ll long long
ll t,n;
il ll frac(ll n) {
	ll ans=1;
	for(int i=2;i<=n;i++) ans=(ans*i)%mod;
	return ans;
}
int main() {
	scanf("%lld",&t);
	while(t--) {
		scanf("%lld",&n);
		printf("%lld\n",((n*(n-1))%mod*frac(n))%mod);
	}
	return 0;
}
```

---

## 作者：rainygame (赞：1)

## 时间复杂度为 $O(n+t)$ 的解法

这道题本来是很简单的，但是考场上看漏了“所有 $n$ 之和不超过 $10^5$”这句话，于是想了半小时才想出如何把 $O(tn)$ 优化到 $O(t)$，进而导致我最后只做出来 $2$ 题……

闲话少说，让我们来看看这道题。非常容易想出一种暴力的做法，时间复杂度为 $O(t \times n! \times n^2)$，显然无法通过此题。

我们可以尝试找找规律：

当 $n=1$ 时，共有 $0$ 个。

当 $n=2$ 时，共有 $4$ 个。也可以枚举一下：

- `1,2`：反转得到 `1,2,2,1`，共有 $2$ 个逆序对。

- `2,1`：反转得到 `2,1,1,2`，共有 $2$ 个逆序对。

当 $n=3$ 时，我们可枚举一共 $3!=6$ 种可能：

- `1,2,3`：反转得到 `1,2,3,3,2,1`，共有 $6$ 个。

- `1,3,2`：反转得到 `1,3,2,2,3,1`，共有 $6$ 个。

- ……

**等一下，我们发现长度固定的 $a$ 的逆序对的个数是固定的！**

那么我们只需要找其中一个 $a$ 的逆序对个数，然后再乘上 $n!$ 就可以了。再通过一些优化，时间复杂度降为 $O(tn^2 \log n)$。（因为计算阶乘需要 $O(n)$ 的计算）。

但是显然，这个时间复杂度仍不让人满意。那有没有更快的方法呢？我们通过更多的枚举可以发现长度为 $2n$ 的 $a$ 的逆序对的数量为 $n(n-1)$，这个是考场找规律出来的。现在想到了证明：

因为 $a$ 的逆序对的个数是固定的，所以我们考虑更简单的第一种，也就是 $a = [1,2,\dots,n,n,n-1,\dots,2,1]$ 的时候。此时我们可以发现第一个数 $1$ 没有与它构成的逆序对，而第二个数有 $1$ 个，第三个数有 $2$ 个……到了第 $n$ 个数 $n$ 有 $n-1$ 个。前 $n$ 个数一共有 $1+2+\dots+(n-1)+n$ 个逆序对，用等差数列求和公式可化简为 $\frac{n(n-1)}{2}$。后面的 $n$ 个数也是一样，所以一个 $a$ 的逆序对个数就是 $\frac{n(n-1)}{2} \times 2 = n(n-1)$。那么答案即为 $n! \times n(n-1)$。时间复杂度降为 $O(tn)$，可以通过此题。

但是，但是，我不是说有 $O(n+t)$ 的解法吗？其实也很简单，我们可以 $O(n)$ 预处理 $1$ 到 $n$ 的阶乘（设 $i$ 的阶乘为 $f_i$），然后再在线计算 $f_n \times n(n-1)$ 即可。时间复杂度为 $O(n+t)$，空间复杂度为 $O(n)$，自认为这种解法比较优秀。

考场代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
const int MOD = 1e9+7;
const int MAXN = 1e5+1;

long long t, n, x = 1;
long long f[MAXN];

int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	
	for (int i=1; i<MAXN; i++){
		x = (x*i)%MOD;
		f[i] = x;
	}
	
	cin >> t;
	while (t--){
		cin >> n;
		cout << (f[n]*(n-1)%MOD)*n%MOD << '\n';
	}

	return 0;
}

```

我自己也搞了[一道题](https://www.luogu.com.cn/problem/U276511)，和这道题数据范围的区别。各位可以尝试用上面的方法做一下。

---

## 作者：ExplodingKonjac (赞：1)

**[【原题链接】](https://www.luogu.com.cn/problem/CF1777B)**

第一眼看蒙了，卡了好几分钟。

## 题目分析

结论：所有排列的 beauty 是一样的。

把构造出的序列 $a$ 分成两半：$[1,2,\dots,n|n,n-1,\cdots,1]$。

左半边的贡献是 $p$ 中的逆序对数，右半边的贡献是 $p$ 中的顺序对数。因此这两部分合起来的贡献就是元素对数 $n(n-1)/2$。

至于跨过两边的贡献，也是 $n(n-1)/2$。因为对于左边的每一个数，所有比它小的正整数都在右边出现了。

所以答案是 $n!\cdot n(n-1)$。

## 代码实现

```cpp
#include <bits/stdc++.h>
using namespace std;

// 快读

using LL=long long;
using LD=long double;
using UI=unsigned int;
using ULL=unsigned long long;

template<int MOD>
class Modint
{
 private:
	int val;
	template<typename T> static T inverse(T a,T b)
		{ T x=0,y=1,t;for(;a;t=b/a,swap(a,b-=t*a),swap(y,x-=t*y));return x; }
	template<typename T> static T fix(T x)
		{ return (x%=MOD)<0?x+MOD:x; }
 public:
	Modint(): val(0){}
	template<typename T> Modint(const T &x): val(fix(x)){}
	inline int operator ()() { return val; }
	inline Modint &operator +=(const Modint &rhs)
		{ return (val+=rhs.val)>=MOD?val-=MOD:0,*this; }
	inline Modint &operator -=(const Modint &rhs)
		{ return (val-=rhs.val)<0?val+=MOD:0,*this; }
	inline Modint &operator *=(const Modint &rhs)
		{ return val=fix(1ll*val*rhs.val),*this; }
	inline Modint &operator /=(const Modint &rhs)
		{ return val=fix(1ll*val*inverse(rhs.val,MOD)),*this; }
	inline Modint &operator ++()
		{ return (++val)>=MOD?val-=MOD:0,*this; }
	inline Modint &operator --()
		{ return (--val)<0?val+=MOD:0,*this; }
	inline Modint operator ++(int)
		{ Modint res(*this);return ++*this,res; }
	inline Modint operator --(int)
		{ Modint res(*this);return --*this,res; }
	inline Modint operator +()
		{ return *this; }
	inline Modint operator -()
		{ return Modint(MOD-val); }
	inline Modint inv()const
		{ return Modint(inverse(val,MOD)); }
	friend inline Modint operator +(const Modint &lhs,const Modint &rhs)
		{ return Modint(lhs)+=rhs; }
	friend inline Modint operator -(const Modint &lhs,const Modint &rhs)
		{ return Modint(lhs)-=rhs; }
	friend inline Modint operator *(const Modint &lhs,const Modint &rhs)
		{ return Modint(lhs)*=rhs; }
	friend inline Modint operator /(const Modint &lhs,const Modint &rhs)
		{ return Modint(lhs)/=rhs; }
	friend inline bool operator ==(const Modint &lhs,const Modint &rhs)
		{ return lhs.val==rhs.val; }
	friend inline bool operator !=(const Modint &lhs,const Modint &rhs)
		{ return lhs.val!=rhs.val; }
	template<typename T> friend inline Modint qpow(Modint x,T y)
		{ Modint res(1);for(;y;x*=x,y>>=1)if(y&1)res*=x;return res; }
};
constexpr int MOD=1e9+7;
using Mint=Modint<MOD>;

int T,n;
int main()
{
	qin>>T;
	while(T--)
	{
		qin>>n;
		Mint ans=n;
		ans=ans*(ans-1)/2;
		for(int i=1;i<=n;i++) ans+=(n-i);
		for(int i=1;i<=n;i++) ans*=i;
		qout.writeln(ans());
	}
	return 0;
}
```


---

## 作者：12345678hzx (赞：1)

## 题目大意
多组数据，每组数据输入一个正整数 $n$，求出所有长度为 $n$ 的排列与这个排列相反的排列连接后的数组的逆序对和。
## 思路
由于每组输入只有一个数，考虑递推。

经过手玩 $n\le 4$ 可以看出，长度为 $1$ 的任意情况逆序对为 $0$，长度为 $2$ 的任意情况逆序对为 $2$，长度为 $3$ 的任意情况逆序对为 $6$，长度为 $4$ 的任意情况逆序对为 $12$，我们可以大胆猜测，这是一个二阶等差数列，再加上长度为 $n$ 的排列有 $n!$ 种，我们就可以相乘预处理出答案。
## 代码 
需要注意每步取模，像这种要取模的题，最好开 `long long`。
```cpp
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<algorithm>
#include<cmath>

using namespace std;

long long n,sum[100005],fac[100005];
int main() {
	int t;
	cin>>t;
	int tot=0;
	for(int i=1;i<=100000;i++) sum[i]=(sum[i-1]+tot)%1000000007,tot+=2;
	fac[1]=1;
	for(int i=2;i<=100000;i++) fac[i]=(fac[i-1]*i)%1000000007;
	while(t--) {
		cin>>n;
		cout<<sum[n]*fac[n]%1000000007<<"\n";
	}
	return 0;
}
```

---

## 作者：james1BadCreeper (赞：0)

序列可以分成前后两个部分。假设前半部分有 $m$ 个逆序对，那么就有 $\frac{n(n-1)}{2}-m$ 个正序对，也就是说后半部分有 $\frac{n(n-1)}{2}-m$ 个逆序对；后半部分的任意一个数 $i$ 在前半部分有 $i-1$ 个比它小，逆序对数为 $\frac{n(n-1)}{2}$。因此任意一个排列的逆序对数都是 $n(n-1)$，总答案就是 $n!n(n-1)$。

```cpp
#include <bits/stdc++.h>

using namespace std;
typedef long long i64;
const int P = 1000000007; 

int fac(int n) {
    int res = 1;
    for (int i = 1; i <= n; ++i) res = 1ll * res * i % P;
    return res; 
}

void solve(void) {
    int n; cin >> n;
    cout << 1ll * n * (n - 1) % P * fac(n) % P << "\n";
}

int main(void) {
    ios::sync_with_stdio(false);
    int T; cin >> T; 
    while (T--) solve();
    return 0;
}
```

---

## 作者：瀛洲仙子 (赞：0)

### 思路
此题求一个值。我们发现根据这个数据范围，不可能暴力。所以，我们显然需要用**数学公式**。

不妨先举例试试？
$n=4,a=[2,1,4,3,3,4,1,2]$ 则满足的数对有：$(a_1,a_2),(a_1,a_7),(a_3,a_4),(a_3,a_5),(a_3,a_7),(a_3,a_8),(a_4,a_7),(a_4,a_8),(a_5,a_7),(a_5,a_8),(a_6,a_7),(a_6,a_8)$，共 $12$ 对。    
$a=[3,1,4,2,2,4,1,3]$ 则满足的数对有：$(a_1,a_2),(a_1,a_4),(a_1,a_5),(a_1,a_7),(a_3,a_4),(a_3,a_5),(a_3,a_7),(a_3,a_8),(a_4,a_7),(a_5,a_7),(a_6,a_7),(a_6,a_8)$，共 $12$ 对。    
猜想：答案只与 $n$ 有关。     
$n=3,a=[1,3,2,2,3,1]$，共 $6$ 种。        
结论：答案为 $n!A^2_n=n(n-1)n!$
### 代码
根据以上结论，[无注释代码](https://codeforces.com/contest/1777/submission/190013049)如下。
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long lld;
lld pmt[100005];
const lld MOD=1e9+7;
void predo()
{
 pmt[1]=1;
 for(int i=2;i<=100000;++i)
  pmt[i]=pmt[i-1]*i%MOD;
}
int read()
{
 int x=0;char ch=0;
 while(!isdigit(ch))
  ch=getchar();
 while(isdigit(ch))
 {
  x=x*10+(ch-'0');
  ch=getchar();
 }
 return x;
}
void write(lld x)
{
 if(x>9)write(x/10);
 putchar(x%10+'0');
}
int main()
{
 predo();int t;
 t=read();while(t--)
 {
  lld n=read();
  if(n==1)printf("0\n");
  else{write((n*(n-1)%MOD)*pmt[n]%MOD);putchar('\n');}
 }
}
```

---

## 作者：zhicheng (赞：0)

### 题意简述

对长度为 $n$ 的每一个排列做以下操作：将它翻转过来接在原排列后，求所有新数串的逆序对数之和，对 $10^9+7$ 取模。

### 思路

我们先来看单个排列。对于一个排列的每一个数对，它一定是顺序对或逆序对（因为是排列，没有重复数字）。那么翻转后顺序对变为逆序，反之亦然，所以单独的原排列和翻转后的逆序对数之和为一个排列的数对数，即为 $\dfrac{n\times(n-1)}{2}$。而对于原序列中的逆序对 $(x_1,y_1)$，在接着的反排列中有一个与 $y_1$ 相等的 $y_{1}^{'}$ 与 $x$ 构成逆序对。相似地，对于翻转后的序列中的 $(x_2,y_2)$，在前面的正排列中有一个与 $y_2$ 相等的 $y_{2}^{'}$ 与 $x$ 也构成逆序对。所以接起来后的每一个序列的逆序对数都为 $n\times(n-1)$。共有（题目中有提示）$n!$ 个序列，所以最后答案就是 $n!\times n\times(n-1)$。

还有注意开 `long long`。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
long long mod=1e9+7; //模数
int main(){
    int t,n;
    long long ans;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        ans=(long long)n*(n-1);
        for(int i=2;i<=n;i++){
            ans*=(long long)i;
            ans%=mod;
        }
        printf("%lld\n",ans);  //注意 long long
    }
}
```

---

## 作者：eason1021 (赞：0)

# 题目简述
给定一个正整数 $n(1 \leq n \leq 10^5)$ 。设序列 $p$ 为 $1 \sim n$ 的一个排列，则 $S(p)$ 为序列 $p$ 与序列 $p$ 的反转首尾相接所得的序列的逆序对数。求所有 $1 \sim n$ 的排列 $p$ 的 $S(p)$ 之和。答案对 $10^9+7$ 取模

例如：$n = 2, p = [1, 2]$, 则 $S(p)$ 为 $[1, 2, 2, 1]$ 的逆序对数，为$2$。

数据保证所有 $n$ 的和不超过 $10^5$。

# 思路
## 1.暴力
直接枚举所有的排列求逆序对即可。

时间复杂度: $\Theta(n! \times n\log n)$

## 2.找规律
随机取一个 $1 \sim n$ 的排列 $p$。

设排列 $p$ 与其反转序列首尾相接的排列为 $a$ 。

则 $\forall i \in [1, n], a_i = a_{2n - i}$ 。

所以 $a_i$ 后大于 $a_i$ 的元素数量与 $a_{2n - i}$ 后大于 $a_{2n - i}$ 的元素数量之和就是 $a[i + 1, 2n]$ 和 $a[2n - i, 2n]$ 中大于 $a_i$ 的元素数量。设为 $sum$。

由于 $a[2n - i, 2n]$ 是 $a[1, i]$ 的反转。则 $sum$ 为序列 $a$ 中大于 $a_i$ 的元素数量。所以 $sum$ 为 $2(a_i - 1)$ 。
所以该排列 $p$ 的 $S(p)$ 为 

$\sum\limits_{i = 1} ^ {n} 2(p_i - 1)$

$=2\sum\limits_{i = 1} ^ {n} (i - 1)$

$=2\times\frac{n\times[(n-1)+0]}{2}$

$=n(n-1)$。

所以结果为 $n!\times n(n-1)$。

时间复杂度: $\Theta (1)$。

### 代码
```cpp
#include<bits/stdc++.h>
#include<cstdio>
using namespace std;
const int N = 1E5 + 5, MOD = 1E9 + 7;
int t;
long long n;
int main()
{
	cin >> t;
	while (t--) {
		cin >> n;
		long long ans = 0;
		long long tmp = 1;
		for (int i = 1; i <= n; i++) {
			tmp *= i;
			tmp %= MOD;
		}
		ans = n * (n - 1);
		ans %= MOD;
		ans *= tmp;
		ans %= MOD;
		cout << ans << '\n';
	}
}
```

---

## 作者：Nygglatho (赞：0)



设在 $a_1 \sim a_n$ 出现的数字为 $s$，则 $a_{n + 1} \sim a_{2n}$ 出现的数字为 $s'$，$s$ 在 $a$ 中出现的位置为 $f_s$。

由于 $1 \sim n$ 有 $n!$ 种排列，而对于每一个排列中数字的 $x, y(x > y)$，有：

- $f_x < f_y$，由于 $a_{n + 1} \sim a_{2n}$ 是 $p_1 \sim p_n$ 的翻转，所以显然 $f_{x'} > f_{y'}$。可以画下图理解一下：    
![](https://s1.ax1x.com/2023/01/23/pSJbs2R.png)     
此时，$x > y$ 且 $f_x < f_y$，$x > y'$ 且 $f_x < f_{y'}$，为最终答案贡献了 $2$。

- $f_x > f_y$，同理，$f_{x'} < f_{y'}$：               
![](https://s1.ax1x.com/2023/01/23/pSJbhIe.png)                    
此时，$x > y'$ 且 $f_x < f_{y'}$，$x' > y'$ 且 $f_{x'} < f_{y'}$，同样为最终答案贡献了 $2$。

那么显然排列中的每一个数字 $x$ 都为最终答案贡献了 $2(x - 1)$，总共贡献了：

$$
\sum\limits_{i=1}^{n-1}2i = \dfrac{2n(n-1)}{2} = n(n-1)
$$

而一共有 $n!$ 中排列方式，所以答案为：

$$
n!\cdot n(n-1)
$$

```c
#include "bits/stdc++.h"
using namespace std;

#define ll long long

ll f[1919810], g[1919810];
const ll mod = 1000000007ll;

int main() {
    int t, n;
    f[0] = 1ll;
    for (int i = 1; i <= 100000; ++i) {
        f[i] = ((f[i - 1] % mod) * ((1ll * i) % mod)) % mod;//计算 n!
        g[i] = ((i % mod) * ((1ll * i - 1ll) % mod)) % mod;//计算 n(n-1)
    }
    scanf ("%d", &t);
    while (t--) {
        scanf ("%d", &n);
        if (n == 1) puts("0");
        else printf ("%lld\n", (f[n] * g[n]) % mod);
    }
}
```

---

