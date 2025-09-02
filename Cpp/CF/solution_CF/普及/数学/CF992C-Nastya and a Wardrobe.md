# Nastya and a Wardrobe

## 题目描述

$Nastya$  收到了一个神奇的“双倍衣柜”，在每个月底，衣柜中的裙子数量都会双倍。

在第  $1$  年里，衣柜中有  $x$  条裙子。前  $k$  个月中，在双倍之后， $Nastya$  都有  $50\%$  的几率从衣柜中取出一条裙子（当然首先要保证衣柜内有裙子）。身为程序员，请你帮她求出第  $k + 1$  个月底，衣柜中的裙子双倍后，裙子数的期望值。这个值可能很大，你只要输出它对  $10^9+7$  取模的结果即可。

## 说明/提示

- 第  $1$  组样例的解释：

因为  $k = 0$ ，所以  $Nastya$  无法取走任何裙子。因此期望值就是  $x$  双倍的结果，也就是  $4$ 。

- 第  $2$  组样例的解释：

第一个月底双倍之后，衣柜中有  $4$  条裙子， $Nastya$  有  $50\%$  的几率取走  $1$  条，这意味着衣柜中的裙子有  $50\%$  的几率有  $3$  条， $50\%$  的几率有  $4$  条。第二个月底她不会取裙子，因此此时衣柜中的裙子有  $50\%$  的几率有  $6$  条， $50\%$  的几率有  $8$  条。综上所述，期望值为  $(6+8)/2 = 7$ 。

感谢@Sooke 提供翻译

## 样例 #1

### 输入

```
2 0
```

### 输出

```
4
```

## 样例 #2

### 输入

```
2 1
```

### 输出

```
7
```

## 样例 #3

### 输入

```
3 2
```

### 输出

```
21
```

# 题解

## 作者：CarrotMeow (赞：1)

## [CF992C Nastya and a Wardrobe](https://www.luogu.com.cn/problem/CF992C)

> 对 $x$ 进行 $k$ 次操作。对于每一次操作，有 $50 \%$ 的概率 $x \gets 2x$，否则 $x \gets 2x - 1$。求操作完后 $2x$ 的期望得数。

推公式找规律。

| 操作次数 | $x$ 取值区间 | 简化 |
| :-: | :-: | :-: |
| $1$ | $[2x - 1, 2x]$ | $[2x - 1, 2x]$ |
| $2$ | $[2 \times (2x - 1) - 1, 2 \times 2x]$ | $[2^2x - (2^2 - 1), 2^2x]$ |
| $3$ | $[2 \times (2(2x - 1) - 1) - 1, 2 \times 2 \times 2x]$ | $[2^3x - (2^3 - 1), 2^3x]$
| $\vdots$ | $\vdots$ | $\vdots$ |
| $k$ | | $[2^kx - (2^k - 1), 2^kx]$ |

（以上所有集合都只包括 **自然数**。）

可以发现，在第 $i$ 步，$x$ **平均** 分布于 $[2^ix - 2^i + 1, 2^ix]$，就相当于取平均数。在 $k$ 步内，$x$ 的期望就是

$$
\begin{aligned}
&\dfrac{(2^kx - 2^k + 1) + (2^kx)} 2 \\
=~ &\dfrac{2^{k + 1}x - 2^k + 1}2
\end{aligned}
$$

题目取的是 $2x$ 的期望，刚好把分母消掉。

保险起见，开 `int128`。[GNU C++17 代码](https://codeforces.com/contest/992/submission/238358495)。

---

最后我们请出万能 Python——

```python
x, k = map(int, input().split()); print((0, (x * pow(2, k + 1, 10 ** 9 + 7) - pow(2, k, 10 ** 9 + 7) + 1) % (10 ** 9 + 7))[x != 0])
```

[一行 AC](https://codeforces.com/contest/992/submission/238363446)。

---

## 作者：Composite_Function (赞：1)

$$\text{前文}$$

这道题总体不难，但各种卡精度的地方前前后后卡了我很多次，蓝题配得上。

------------

观察题面，发现必然不是线性及更高的时间复杂度。然而，这道题目确实递推的。所以，可以得出结论：时间复杂度必然是 $\log$ 级别的。

既然考虑到了 $\log$ 那么自然而然地就想到了快速幂。而且，题目也提到了翻倍。唯一需要处理的就是期望通项方程的问题了。通项方程也就意味着需要递推方程。

在期望的问题上有个陷阱，开始我认为必须按照每个分支去考虑。但思考后发现只需要对每次期望往后推即可。

若当前已有的裙子数量期望为 $a$，翻倍后期望为 $2a$。又因有 $50\%$ 拿走一条，期望便是 $2(a-\dfrac{1}{2})=2a-1$。

接下来，用数学归纳法和递推转通项均可证出答案为 $n \times 2^{k + 1} - 2^k + 1$，以下两种方法均给出：

1. 数学归纳法（关于 $k$）：当 $k=0$ 时显然成立；当 $k = x$ 时成立，则当 $k=x+1$ 时，答案 $=2(n \times 2^{x + 1} - 2^x + 1) - 1=n \times 2^{x + 2} - 2^{x+1} + 1$。
2. 递推转通项（关于 $k$）：设答案为 $a_k$，初始值 $a_0=2n$，递推方程 $a_{k+1}=2a_k-1$。所以 $a_{k+1}-1=2(a_k-1)$，由得到 $a_k-1=n \times 2^{k + 1} - 2^k$，$a_k=n \times 2^{k + 1} - 2^k + 1$。

然后，想到没有裙子则不能拿，所以 $n=0$ 要特判。

------------

做了那么多，得到了答案。然而真正难的在开始。

首先根据题目意思写出这样的代码：

```cpp
# include <bits/stdc++.h>
using namespace std;
# define int long long
const int mod = 1e9 + 7;
int n, k;
int qpow(int base, int index, int mod)
{
	int ans = 1;
	while (index > 0) {
		if (index & 1) ans = ans * base % mod;
		base = base * base % mod, index >>= 1;
	}
	return ans;
}
signed main()
{
	cin >> n >> k;
	if (n == 0) cout << 0 << endl;
	else cout << n * qpow(2, k + 1, mod) - qpow(2, k, mod) + 1 << endl;
	return 0;
} 
```

然而，WA on #5，发现有可能乘后大于模数，于是加上在模一次，修改这行代码：

```cpp
	else cout << (n * qpow(2, k + 1, mod) - qpow(2, k, mod) + 1) % mod << endl;
```

可是还是错了，想到可能会有负数，于是再改：

```cpp
	else cout << (n * qpow(2, k + 1, mod) - qpow(2, k, mod) + 1 + mod) % mod << endl;
```

照一个正常的出题人思路，这里已经够了。但是 $n \le 10^{18}$，还需要改乘法。

你可以选择用高精板子，但这里有取模，代码很长。我使用的是二进制累加：

```cpp

int _time(int base, int index, int mod)
{
	int ans = 0;
	while (index > 0) {
		if (index & 1) ans = (ans + base) % mod;
		base = (base + base) % mod, index >>= 1;
	}
	return ans;
}
```

------------

终于，在各种烦人的问题下，这份代码终于 AC 了此题。篇幅原因，代码就不放了。祝大家很快 AC 此题！

~~看在蒟蒻作者码了那么久的份上要个赞不过分吧（逃~~

---

## 作者：子谦。 (赞：1)


题意很清晰，这种题，我们当然还是有两种方法来做啦

### 方法一：找规律

读完题我们来看样例，通过样例一已我们大概可以看出，答案或许是$n*2^{k+1}$

肯定不能这么简单对吧，那就来看样例二，难道答案是$n*2^{k+1}-k$或者是$n*2^{k+1}-2^{k-1}$也有可能是$n*2^{k+1}-2^k+1$

通过样例三可得，答案是$n*2^{k+1}-2^k+1$

### 方法二：数学证明

每个月都是乘2，所以第i个月取走一个对第j个月的影响就是$2^{j-i}(i<j)$

那么每个月都会对最后一个月产生影响，影响总和是$ \sum _ {i=0} ^ {k-1} 2^i $，也就是$2^k-1$

这是负的影响，正的影响很容易算，就是$n*2^{k+1}$

说白了，每个月要么直接乘二，要么-1再乘二，我们把这个-1提出来，就分成了上面所说的正贡献和负贡献

千万别忘了特判等于零，还有直接乘会爆long long

下面放代码

```cpp
#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cctype>
#define ll long long
#define gc getchar
#define mo 1000000007
using namespace std;

inline ll read(){
	ll a=0;int f=0;char p=gc();
	while(!isdigit(p)){f|=p=='-';p=gc();}
	while(isdigit(p)){a=(a<<3)+(a<<1)+(p^48);p=gc();}
	return f?-a:a;
}

ll n,k,k1,e=2,sum=1;
inline ll cheng(ll a,ll b){
	ll sum=0;
	while(b){
		if(b&1)sum=(sum+a)%mo;
		a=(a<<1)%mo;b>>=1;
	}
	return sum;
}

int main(){
	n=read();k1=k=read();++k;
	if(n==0){
		puts("0");
		return 0;
	}k%=mo-1;
	while(k){
		if(k&1)n=cheng(n,e)%mo;
		e=cheng(e,e)%mo;k>>=1;
	}e=2;k1%=mo-1;
	while(k1){
		if(k1&1)sum=cheng(sum,e)%mo;
		e=cheng(e,e)%mo;k1>>=1;
	}
	--sum;if(sum<0)sum+=mo;
	printf("%lld\n",((n-sum)%mo+mo)%mo);
	return 0;
}
```

不要抄代码哦

---

## 作者：_czy (赞：0)

## 分析
我们可以分析裙子数的区间来找规律。

第一个月，$[2x-1,2x]$。

第二个月，$[4x-3,4x]$。

第三个月，$[8x-7,8x]$。

同理，第 $k$ 个月，$[2^kx-2^k+1,2^kx]$。

答案显然是 $2^{k+1}x-2^k+1$ (注意是第 $k+1$ 月底翻倍后的)。

不过指数 $k$ 有点大，需要快速幂。而且要特判 $x=0$ 的情况。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define P 1000000007
ll x,k;
int qpow(ll a,ll b){
	int s=1;
	while(b){
		if(b%2)s=s*a%P;
		a=a*a%P,b/=2;
	}
	return s;
}
int main(){
	cin>>x>>k;
	if(!x){
		cout<<0;
		return 0;
	}
	cout<<(qpow(2,k+1)*(x%P)%P-qpow(2,k)+1+P)%P;
}
```

---

## 作者：Toothless03 (赞：0)

一看就是数（猜）学（的）题

### 推公式！！！
对于第一个月来说，裙子的数量取值为 $[x\times2-1,x\times2]\cap \mathbb Z$ ，而每种取值的概率都是 $50\%$ 。

对于第二个月来说，裙子的数量取值范围是 $[(x\times2-1)\times2-1,x\times2\times2]\cap \mathbb Z\equiv [x\times2^2-2^2+1,x\times2^2]\cap \mathbb Z$ ，而每种取值的概率都是 $25 \%$ 。

对于第三个月来说，裙子的数量取值范围是 $[((x\times2-1)\times2-1)\times2-1,x\times2\times2\times2]\cap \mathbb Z\equiv [x\times2^3-2^3+1,x\times2^3]\cap \mathbb Z$ ，而每种取值的概率都是 $12.5\%$ 。

更一般的对于前 $k$ 个月中某月 $n$ ，我们可以发现它裙子数量可以达到的值是 $[x\times 2 ^k -2^k+1,x\times 2^k]\cap \mathbb Z$ 。
而对于每种情况，其概率都为 $\frac{100\%}{2^k}$ ，所以在前 $k$ 个月，数量的期望是 $\frac{x\times 2^{k+1}-2^k+1}{2}$ ，由于最后一个月数量乘二，所以最终结果为 $x\times2^{k+1}-2^k+1$ 。

所以快速幂一下就行了。

ps：不开 long long 见祖宗，还需判断一下当 $x=0$ 的情况。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
#define max(x, y) (x > y ? x : y)
#define min(x, y) (x < y ? x : y)
const int mod = 1e9 + 7;
int fpow(int x, int p) {
    if (p == 0)
        return 1;
    if (p == 1)
        return x;
    int t = fpow(x, p / 2);
    if (p & 1)
        return (t * t % mod) * x % mod;
    return (t * t) % mod;
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int x, k;
    cin >> x >> k;
    if (x == 0) {
        cout << "0" << endl;
        return 0;
    }
    cout <<  ((((2 * x - 1 + mod) % mod) * fpow(2, k) + mod) % mod + 1) % mod << endl;
}
```

---

