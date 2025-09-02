# Maximum Set

## 题目描述

A set of positive integers $ S $ is called beautiful if, for every two integers $ x $ and $ y $ from this set, either $ x $ divides $ y $ or $ y $ divides $ x $ (or both).

You are given two integers $ l $ and $ r $ . Consider all beautiful sets consisting of integers not less than $ l $ and not greater than $ r $ . You have to print two numbers:

- the maximum possible size of a beautiful set where all elements are from $ l $ to $ r $ ;
- the number of beautiful sets consisting of integers from $ l $ to $ r $ with the maximum possible size.

Since the second number can be very large, print it modulo $ 998244353 $ .

## 说明/提示

In the first test case, the maximum possible size of a beautiful set with integers from $ 3 $ to $ 11 $ is $ 2 $ . There are $ 4 $ such sets which have the maximum possible size:

- $ \{ 3, 6 \} $ ;
- $ \{ 3, 9 \} $ ;
- $ \{ 4, 8 \} $ ;
- $ \{ 5, 10 \} $ .

## 样例 #1

### 输入

```
4
3 11
13 37
1 22
4 100```

### 输出

```
2 4
2 6
5 1
5 7```

# 题解

## 作者：spider_oyster (赞：16)

要让这个集合最大，让任两个数能整除，假设集合内元素递增，则每次乘 $2$ 即可。

当然，也可以乘一个 $3$，但不能乘 $4$ 及以上的数，因为 $4=2\times2$，这时集合的大小显然会比之前的情况少 $1$。

所以集合内一共乘了 $n=log_{2}\frac{r}{l}$ 次 $2$，此时集合大小 $size=n+1$。

我们设集合内第一个能选的最大的数为 $x$，则 $x\times2^n\leq r$ ，此时全部乘 $2$ 一共有 $x-l+1$ 中方案。

现在考虑乘了一个 $3$ 的情况，此时 $x'\times 2^{n-1}\times3\leq r$，由于可以替换 $n$ 个 $2$ 中的任意一个为 $3$ ，所以现在又有 $(x'-l+1)\times n$ 种方案（由于~~懒~~ $int$ 是向下取整，所以我没打向下取整符号）。

```cpp
#include<bits/stdc++.h>
using namespace std;
 
int t,l,r;
 
int main()
{
	cin>>t;
	while(t--)
	{
		cin>>l>>r;
		int n=log2(r/l);
		int ans=r/(1<<n)-l+1;
		if(n>0)
		{
			int t=r/(1<<n-1)/3-l+1;
			if(t>0) ans=ans+t*n;
		}
		printf("%d %d\n",n+1,ans);
	}
}
```


---

## 作者：2huk (赞：4)

## 题目描述

定义一个集合 $S$ 是合法的，当前仅当任取集合中的两个元素 $x$ 和 $y$，则要么 $x\mid y$，要么 $y\mid x$。

给定区间 $[l, r]$，你需要输出两个数：

一个漂亮的集合的大小（元素个数），满足集合内元素都是 $[l, r]$ 的数。（包括端点）

上述最大大小的漂亮集合的方案数。

第二种情况数量可能很大，请输出答案对 $998244353$ 的结果。

## 样例输入输出

```
1
4 100
```

```
5 7
```

## 数据范围

$1 \le t \le 2 \times 10^4,\ 1 \le l \le r \le 10^6$

## 集合大小

第一问很简单。若要使集合的大小最大，那么一定要让第一个数最小，也就是 $l$。每一次将 $l$ 乘上一个最小的数，由于不能是 $1$，所以每次乘 $2$，只要在满足 $l \le r$ 的时候将答案自增 $1$ 即可。

```cpp
int q1(int l, int r)
{
	int res = 0;
	
	while (l <= r) res ++ , l *= 2;
	
	return res;
}
```

## 集合数量

从样例入手。

$l=4, r=100$

$4\xrightarrow{\times 2}8\xrightarrow{\times 2}16\xrightarrow{\times 2}32\xrightarrow{\times 2}64 $

$5\xrightarrow{\times 2}10\xrightarrow{\times 2}20\xrightarrow{\times 2}40\xrightarrow{\times 2}80$

$6\xrightarrow{\times 2}12\xrightarrow{\times 2}24\xrightarrow{\times 2}48\xrightarrow{\times 2}96$

$4\xrightarrow{\times 2}8\xrightarrow{\times 2}16\xrightarrow{\times 2}32\xrightarrow{\times 3}96$

$4\xrightarrow{\times 2}8\xrightarrow{\times 2}16\xrightarrow{\times 3}48\xrightarrow{\times 2}96$

$4\xrightarrow{\times 2}8\xrightarrow{\times 3}24\xrightarrow{\times 2}48\xrightarrow{\times 2}96$

$4\xrightarrow{\times 3}12\xrightarrow{\times 2}24\xrightarrow{\times 2}48\xrightarrow{\times 2}96$

只有以上 $7$ 种。

我们需要从中挖掘一些性质。

观察上面的数的变化，发现只有 $\times 2$ 和 $\times 3$ 两种操作，而且 $\times 3$ 在一种答案中只进行了一次。这里分别解释原因。

---

### 只有 $\times 2$ 和 $\times 3$ 两种操作

如果出现了 $\times 4$ 这样的操作，那么会发生怎样的事情呢？

假设 $l=2, r=16$，那么如果出现了 $\times 4$ 操作，就会有 $2 \xrightarrow{\times 2} 4 \xrightarrow{\times 4} 16$ 这一种情况。但是实际上可以在 $4$ 和 $16$ 之间再插入一个数 $8$，即 $2 \xrightarrow{\times 2} 4 \xrightarrow{\times 2} 8 \xrightarrow{\times 2}16$，这样的方法更优，因为它的集合大小为 $4$。所以不可能存在 $\times 4$ 操作。类似的，$\times 5, \times 6 \dots$ 等操作也不可能出现。

以下为严谨证明。

我们知道，第一项最优为 $l$，那么假设第一问的答案为 $x$，也就是集合最大是 $x$，那么显然集合中的最后一项为 $l \times 2^{x-1}$，且 $l \times 2^{x-1} \le r$。将 $2^{x-1}$ 记为 $p$，这个式子就变成了 $l \times p$。

反证法：如果存在 $\times 4$ 的情况，集合的最后一项就变为了 $l \times 4 \times p \times \dfrac 12$，化简得 $l \times p \times 2$，显然这个值是 $> r$ 的。所以不可能存在 $\times 4$ 的情况。

### $\times 3$ 操作最多只有一次

如果出现了 $\times 3 \times 3$ 这样的操作，那么会发生怎样的事情呢？

假设 $l=3, r=18$，那么最优解为 $3 \xrightarrow{\times 2} 6\xrightarrow{\times 2}12$，当然也可以出现 $1$ 个 $\times 3$，即 $3 \xrightarrow{\times 2} 6\xrightarrow{\times 3}18$。但是如果存在两个 $\times 3$，也就是 $3 \xrightarrow{\times 3} 9\xrightarrow{\times 3}27$，这样就不满足条件了。所以 $\times 3$ 操作最多只有一次。

以下为严谨证明：

同上面一样，第一项为 $l$，最后一项为 $l \times p$。

反证法：如果存在 $\times 3 \times 3$ 的情况，集合的最后一项就变为了 $l \times 3 \times 3 \times p \times \left(\dfrac 12\right)^2$，化简得 $l \times p \times 2.25$，显然这个值是 $> r$ 的，所以不可能存在 $\times 3 \times 3$ 的情况。

但是，如果只有一个 $\times 3$，集合的最后一项就变为了 $l \times 3 \times p \times \dfrac 12$，化简得 $l \times p \times 1.5$，显然这个值是有可能 $\le r$ 的，所以可能存在 $\times 3$ 的情况。

---

这是最大集合的性质，即最多出现一个 $\times 3$，其余全为 $\times 2$。这样就方便接下来的计算了。

继续分类讨论。以下分为没有 $\times 3$ 和最多 $1$ 次 $\times 3$ 的两种方法。

---

### 没有 $\times 3$ 操作

如果没有 $\times 3$ 操作，那么就说明全部是 $\times 2$ 操作。计算过程如下：

如果第一项为 $l$，且集合大小为 $x$，那么不难推出集合中的最后一项为 $l \times 2^{x-1}$，且 $l \times 2^{x-1} \le r$。

现在我们试着将 $l$ 调大，使得最后一项的值仍然是 $\le r$ 的，那么问题就相当于转化成了找有多少个 $>0$ 的 $p$，使得 $(l + p) \times 2^{x-1} \le r$。换言之，这个 $p$ 最大是几？

这样这个问题就很简单了，稍微移项即可。

$(l + p) \times 2^{x-1} \le r$

$2^{x-1}\times l + 2^{x-1}\times p \le r$

$p \le \left \lfloor \dfrac{r- 2^{x-1}\times l}{2^{x-1}} \right\rfloor$

右边可以直接求，所以没有 $\times 3$ 操作的集合数量为 $\left \lfloor\dfrac{r- 2^{x-1}\times l}{2^{x-1}} \right \rfloor+ 1$。（$+1$ 是因为包括 $l$ 不变大的情况）

### 最多 $1$ 次 $\times 3$ 操作

最多 $1$ 次 $\times 3$ 操作，是在 $\times 3$ 后的最后一项 $\le r$ 的时候才可能出现的。也就是 $l \times 2^{x-2} \times 3 \le r$ 的时候。

如果满足上面这个条件，就可以考虑 $1$ 次 $\times 3$ 操作的位置了。由于集合大小为 $x$，也就是有 $x-1$ 次的 $\times 2$ 操作，所以在这 $x-1$ 次的操作中需要找到一个位置把 $\times 2$ 替换为 $\times 3$，也就是 $C_{x-1}^1$，等于 $x-1$ 种。

---

至此，计算过程也推导完了，所以最终答案为

$$
res = \left\{\begin{matrix}
\left \lfloor \dfrac{r- 2^{x-1}\times l}{2^{x-1}}\right \rfloor + x & (l \times 2^{x-2} \times 3 \le r)\\ \left \lfloor \dfrac{r- 2^{x-1}\times l}{2^{x-1}}\right \rfloor  + 1 & (l \times 2^{x-2} \times 3 > r)
\end{matrix}\right.
$$

## 代码

给你一份不带取模的代码。

```cpp
int T, l, r, res, x, A, B, C;

int fpm(int a, int b)		// 求 2 的 x 次方 
{
	int res = 1;
	while (b)
	{
		if (b & 1) res *= a;
		b >>= 1, a *= a;
	}
	return res;
}

int set_size(int l, int r)		// 求最大集合大小 
{
	int res = 0;
	
	while (l <= r) res ++ , l *= 2;
	
	return res;
}

signed main()
{
	cin >> l >> r;
	x = set_size(l, r);		// x 为最大集合大小 

	A = r - fpm(2, x - 1) * l;
	B = fpm(2, x - 1);
	C = l * fpm(2, x - 2) * 3 <= r ? x : 1;

	res = A / B + C;
	cout << x << ' ' << res << '\n';
	
	return 0;
}
```

---

## 作者：forgotmyhandle (赞：4)

[你谷传送门](https://www.luogu.com.cn/problem/CF1796C)

[原题传送门](http://codeforces.com/problemset/problem/1796/C)

当天比赛打完之后看了看跟我排名差不多的人的这题代码，感觉莫名其妙，写了几十行。我看了看我只有十几行的 AC 代码，陷入了沉思。
## 分析
题目的要求其实可以转换为：在区间 $[l_0, r]$ 中选择一些数，使得这些数排序后每个数都是前一个数的倍数，要求选的尽可能多。那既然要选的尽可能多，左端点肯定要选上，并且应该让每个数都是前一个数的两倍。这样才能使得选出的最多。设最多选出 $k + 1$ 个数，那么有式子 $l_0 \times 2^k \le r$ 成立，即选出的最大数小于等于区间右端点。于是得出 $k \le \log_2(\frac{r}{l_0}) $。于是 $k$ 的最大值就是 $ \lfloor \log_2(\frac{r}{l_0}) \rfloor$。令 $k$ 取最大值，则输出的第一个答案就是 $k + 1$。

接下来题目让我们求这样的集合个数。显而易见的一个暴力就是从左端点开始枚举，一直枚举到不存在符合要求的集合。这样可能会炸，所以考虑优化。

~~考虑二分答案。~~

怎么可能二分答案（虽然也不是不行）！显然我们可以把刚才那个式子拿过来用：$l \times 2^k \le r$。移项得 $l_1 \le \frac{r}{2^k}$。令 $l_1$ 取最大值 $\lfloor \frac{r}{2^k} \rfloor$，则在每个数都是前一个数的两倍的情况下，左端点 $l \in [l_0, l_1]$。所以答案应该是 $l_1 - l_0 + 1$，因为从这个范围内的左端点开始往右都可以构造一个满足要求的集合。

你真以为就这么简单？

不可能的。

显然，在使选出的数最多的情况下，后一个数并不一定非要是前一个数的两倍。也可以是，比如说三倍，四倍什么的。在抱怨这题之前，让我们先仔细看看：后面一个数可以是前一个数的四倍吗？

显然不行。

若后面一个数是前一个数的四倍，那完全可以在中间再插一个数进去，使选出的数变多。顺着这个思路往下想，后面的数是前面数的五倍，六倍，甚至七倍，八倍，那显然也不行。所以在使得选出的数最多的情况下，后面的数最多是前面数的三倍。

~~猜你在想：排列组合。~~

你先别急。让我们接着想：若在选出的集合中有三个连续的数，分别叫 $x_1, 3x_1, 9x_1$。这个时候，我们发现，这三个数可以被四个数代替：$x_1, 2x_1, 4x_1, 8x_1$。这样，选出的数就又变多了。

发现什么问题？刚才的讨论说明了后面的数最多是前面数的三倍，而且最多只能有一个数是其前面数的三倍。于是我们可以再算出
一个临界点 $l_2$，使得从 $[l_0, l_2]$ 中任意一个左端点开始都可以构造 $k$ 个符合要求的集合（除此集合的左端点外，共有 $k$ 个数可以是其前面数的三倍），而从 $(l_2, l_1]$ 中任意一个左端点开始都只能构造一个符合要求的集合。那接下来的任务就是算出 $l_2$。

什么？你不会还想二分答案吧！别啊，我们有更加迅速的做法：先前那个式子 $l \times 2^k \le r$ 在这边改一改还能用：$l_2 \times 3 \times 2^{k-1} \le r$，也就是把其中一个 2 换成 3。移项得 $l_2 \le \frac{r}{3 \times 2^{k - 1}}$。令 $l_2$ 取最大值 $\lfloor \frac{r}{3 \times 2 {k - 1}} \rfloor$，则答案为 $(l_2 - l_0 + 1) \times k + (l_1 - l_0 + 1)$。

你真以为就这么简单？

是的，真就这么简单。写的时候注意一下精度问题就好了。

这里最终的 $l_2$ 算出来可能会小于 $l_0$，需要注意。

## 代码
```cpp
#include <iostream>
#include <math.h>
#define int long long
using namespace std;
const int p = 998244353;
signed main() {
    int tc;
    cin >> tc;
    while (tc--) {
        int a, b;
        cin >> a >> b;
        int x = log2((1.0 * b) / a);
        int l = a, m = (b / 3) / (1 << x - 1), r = b / (1 << x); // l 是 l0, r 是 l1，m 是 l2，x 是 k。
        cout << x + 1 << " " << (r - l + 1 + (((m - l + 1) % p) * (x % p) * (m >= l)) % p) % p << "\n";
    }
    return 0;
}
```

### 完结撒花~~~

---

## 作者：DerrickLo (赞：2)

首先第一个数很好算，只需要将 $l$ 不断乘 $2$ 然后判断是否大于 $r$ 即可，乘的数量加 $1$ 就是最大大小。

然后是第二个数，首先我们要知道不可能在 $S$ 中有两个数 $x$ 和 $y$ 使得 $x$ 是 $y$ 的 $4$ 倍及以上或 $y$ 是 $x$ 的 $4$ 倍及以上，因为$4 = 2^2$，所以如果出现以上情况这个集合一定不是最大的大小。

那么只能每一个数是前面一个数乘 $2$ 或乘 $3$。

我们讨论乘 $3$ 的个数，先计算出最多乘 $3$ 的个数，然后对于乘 $i$ 次 $3$，可以计算出最小的数的范围，然后对于在这个范围中的数，都有 $\dbinom{ans1-1}{i}$ 种放 $3$ 的情况，其中 $ans1$ 是第一个数。然后将所有情况累加即可。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,l,r,fac[2000005],CC[2000005];
int ksm(int a,int b){
	int res=1ll;
	while(b){
		if(b&1)res=res*a%998244353;
		a=a*a%998244353;
		b>>=1;
	}
	return res;
}
int C(int n,int m){//求组合数
	if(!m)return 1ll;
	return fac[n]%998244353*ksm(fac[m],998244351)%998244353*ksm(fac[n-m],998244351)%998244353;
} 
signed main(){
	cin>>n;
	fac[0]=1;
	for(int i=1;i<=2000000;i++)fac[i]=fac[i-1]*i%998244353;
	while(n--){
		cin>>l>>r;
		int ans1=1,ans2=0,ll=l,noww=1,limit=114514;
		while(ll*2<=r){
			ans1++;
			ll*=2;
			noww*=2;
		}
		if(ans1==1){//特判，我也不知道需不需要
			cout<<ans1<<" "<<r-l+1<<"\n";
			continue;
		}
		for(int i=0;i<ans1;i++)CC[i]=C(ans1-1,i);//预处理组合数
		for(int i=0;i<ans1;i++){//计算最多能取多少个3
			int p2=ksm(2,ans1-i-1),p3=ksm(3,i);
			if(p3*p2<=r/l)limit=i;
		}
		for(int i=0;i<=limit;i++){
			int p2=ksm(2,ans1-i-1),p3=ksm(3,i),nolim=r/p3/p2;//计算当取i个3时，最小的数最大是多少
			ans2+=(nolim-l+1)*CC[i];
			ans2%=998244353;
		}
		cout<<ans1<<" "<<ans2<<"\n";
	}
	return 0;
}
```

---

## 作者：cosf (赞：2)

# [Maximum Set](https://www.luogu.com.cn/problem/CF1796C)

思路
---

注意到，输出的第一个数是 $\lfloor\log_2(\lfloor\frac{r}{l}\rfloor)\rfloor + 1$。

这个结论比较显然，因为为了使个数最多，所以尽量相邻两项的比值最好为 $2$。

---

那么，第二个数怎么求呢？

令其中一个解为 $\{l, 2l, 4l, \dots, 2^{k}l\}$。

如果有 $2^{k-1}\times 3 \times l \le r$，那么可以构造 $\{l, 2l, \dots, 2^{k-1}l, 2^{k-1}\times 3 \times l\}$。如果有 $2^{k-1}\times 4 \times l \le r$，那么可以构造 $\{l, 2l, \dots, 2^{k+1}l\}$，元素个数比原来的解更大，那么矛盾了。

这么说，只需要考虑是不是存在某一位可以乘 $3$ 。

如果对于可以相邻两位比值为 $3$，那么一共有 $k$ 个解。

具体来说，就是如果存在一个解为 $\{m, 2m, 4m, \dots, 2^{k-1}m, 2^{k-1}3m\}$，那么 $\{m, 2m, 4m, \dots, 2^{k-2}3m, 2^{k-1}3m\}, \dots, \{m, 3m, 6m, \dots, 2^{k-1}3m\}$ 都是解，共计 $k$ 个。

那么有多少个 $m$ 满足可以有比值为 $3$ 呢？显然，有 $[l, \frac{r}{2^{k-1}3}]$ 是满足的，有 $\lfloor
\frac{r}{2^{k-1}3}\rfloor - k + 1$ 个。

而对于其他的情况，即只能比值为 $2$ 的，那么有 $\lfloor\frac{r}{2^k} - l + 1\rfloor$ 个。

我们就可以写出代码了。

一个提醒：$\lfloor
\frac{r}{2^{k-1}3}\rfloor - k + 1$ 对于 $l, r$ 很大的情况很基本上都小于 $0$，所以 `mod 998244353` 甚至可以当一个摆设。~~我这样过了~~

[AC Code](https://www.luogu.com.cn/record/112786078)
---
```cpp
// 这 csignal 不知道是哪来的，应该是 luogu rmj 加上去的
#include <csignal>
#include <iostream>
#include <cmath>
using namespace std;

int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		int l, r;
		cin >> l >> r;
        int i = int(log2(r / l)) + 1;// 这里的 i 是上面分析的 k + 1
        if (i == -2147483647) // 只有 1 个解的情况要特判（因为 log(0) = -2147483648）
        {
            cout << "1 " << r - l + 1 << endl; // m 取多少都一样
            continue;
        }
        cout << i << ' ';
        int lr = max((((r / 3) >> (i - 2)) - l + 1), 0); // 计算可以存在比值 3 的个数，这个要乘 k（即 i-1）
        int rr = max(((r >> (i - 1)) - l + 1), 0); // 比值为 2 的个数
        cout << lr * i + (rr - lr) << endl; // k*lr + rr = (i - 1) * lr + rr = i * lr + rr - lr
	}
}
```




---

## 作者：happybob (赞：1)

先考虑第一问。

显然构造应该为 $l, 2 \times l, 4 \times l, \cdots, 2^k \times l$，其中 $2^k \times l <= r$ 且 $2^{k+1} \times l > r$，这里可以暴力枚举，显然 $2^k$ 增长极快，所以暴力是一个 $\log$ 的。

另外就是第二问，考虑每一次，我们都是乘以 $2$，而导致不同方案但数量相同的就是不乘 $2$ 而乘其他数。

我们可以证明这个其他数只能是 $3$，如果我们乘以 $4$ 也可以达到最优数量，那么我们拆开乘以 $2$ 次 $2$ 则更优。大于 $4$ 同理。

所以我们只需要关心乘以 $3$。

除此之外，第一个数除了选 $l$，还可以选其他数，这也会导致更多的方案。

我们枚举**最多**乘以 $3$ 的数量，算出此时 $l$ 的范围，设**最多**乘以 $3$ 的数量为 $i$ 个，令 $a$ 为第一问的答案，那么这时总共需要乘 $3^i \times 2^{a-i-1}$，$-1$ 是因为一开始的 $l$ 不算在内，可以求出 $l$ 的范围。

对于这一范围，贡献为 $\dbinom{a}{i}$，逆元维护即可。

```cpp
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
using namespace std;

#define int long long

int t, l, r;
const int N = 2e6 + 5, MOD = 998244353LL;
int fac[N];

long long qpow(long long a, long long b)
{
	int res = 1, base = a;
	while (b)
	{
		if (b & 1LL) 
		{
			res = res * base % MOD;
		}
		base = base * base % MOD;
		b >>= 1LL;
	}
	return res;
}

long long nqpow(long long a, long long b)
{
	int res = 1, base = a;
	while (b)
	{
		if (b & 1LL)
		{
			res = res * base;
		}
		base = base * base;
		b >>= 1LL;
	}
	return res;
}

#define inv(x) (qpow(x, MOD - 2))

inline long long C(int n, int m)
{
	return fac[n] * inv(fac[m]) % MOD * inv(fac[n - m]) % MOD;
}

signed main()
{
	scanf("%lld", &t);
	fac[0] = 1;
	for (int i = 1; i < N; i++)
	{
		fac[i] = fac[i - 1] * i % MOD;
	}
	while (t--)
	{
		scanf("%lld%lld", &l, &r);
		long long ans1 = 0LL, ans2 = 0LL, p = l;
		while (p <= r)
		{
			ans1++;
			p *= 2LL;
		}
		int last = l;
		for (int i = ans1 - 1; i >= 0; i--)
		{
			long long g = nqpow(3LL, i) * nqpow(2LL, ans1 - i - 1);
			if (r / g < l)
			{
				continue;
			}
			long long cg = C(ans1, i);
			ans2 += cg * (r / g - last + 1LL) % MOD;
			ans2 %= MOD;
			last = r / g + 1LL;
		}
		printf("%lld %lld\n", ans1, ans2);
	}
	return 0;
}
```


---

## 作者：SlyCharlotte (赞：1)

[更好的阅读体验？](https://zhuanlan.zhihu.com/p/610522558)


## 题意描述

给你一个区间，求一个集合 $S,S\subseteq[l,r]$ 的最大长度与最长集合的个数。

需要满足 $\forall i,j \in S , \ \ i \mid j \ \lor \  j \mid i$，集合长度为 $1$ 默认合法。

## 简要分析

不难发现，最长长度的集合长这样 $l ,l\times 2,l\times 2^2 , \dots,l \times2^x$。

那么我们就可以处理出集合的最长长度。

接下来考虑仅 $\times 2$ 时的集合数量。

显然，我们只需将 $r$ 除以 $x - 1$ 次 $2$ 就可以知道集合的初值所属于的最大区间，即求出了集合数量。

我们考虑到，可以将集合中的某一个 $\times 2$ 替换成 $\times3$。

如果替换两个即等价于 $\times 9$，这时不妨使用 $3$ 个 $\times 2$ 即为 $\times 8$ 得到更优答案。 

对于计算存在一个 $\times 3$ 的集合个数，我们如法炮制。

将 $r$ 除以 $x-1$ 次 $2$ 随后再除以 $3$ 就可以知道集合的初值所属于的最大区间，即求出了集合数量。

时间复杂度 $O(T\log r)$。

## 代码实现

```cpp
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <string>
#include <cmath>
#include <vector>

using namespace std;

typedef long long ll;
const ll maxn = 1e5 + 7;
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

inline void write(ll xXx) {
    if (xXx < 0)
        putchar('-'), xXx = -xXx;
    if (xXx > 9)
        write(xXx / 10);
    putchar(xXx % 10 + '0');
}

void solve() {
    ll n = read(), m = read();
    ll tmp = m, ans = 0, cnt = 0, lim;
    if (n * 2 > m) {
        cout << 1 << " " << m - n + 1 << '\n';
        return;
    }
    while (tmp >= n) cnt++, tmp /= 2;
    lim = cnt - 1;
    tmp = m;

    while (lim--) tmp /= 2;

    ans = tmp - n + 1;
    lim = cnt - 2;
    tmp = m;
    while (lim--) tmp /= 2;
    ans += max(0ll, (tmp / 3 - n + 1) * (cnt - 1));
    cout << cnt << ' ' << ans << endl;
}

signed main() {
//    freopen("code.in","r",stdin);
//    freopen("code.out","w",stdout);
    ll T = read();
    while (T--)solve();
    return 0;
}
```


---

## 作者：Pwtking (赞：0)

思维题！

我们要找到一个集合内每两个数都能互相整除，显然大的那个数至少要是小的数的二倍，那么我们为了让这个集合内的数尽量多，肯定要让这个倍数最小，即为 $2$，同时将集合内的最小数设为 $l$。

由此我们得知最大的集合大小为 $\log_{2}{\frac{r}{l}}$。

求最大的集合个数，即时求出一个满足**乘上 $\log_{2}{\frac{r}{l}}$ 次 $2$ 小于等于 $r$ 的最大数减去 $l$** 加上一个满足**乘上 $\log_{2}{\frac{r}{l}}$ 次 $3$ 小于等于 $r$ 的最大数减去 $l$ 的和。**

为什么求最大集合数量的时候不需要求满足乘上 $\log_{2}{\frac{r}{l}}$ 次 $4$ 以上的数呢？

因为 $4=2^2$，即是若倍数大于四的话显然不可能构成最大集合。

---

## 作者：yuanruiqi (赞：0)

## 题意简述

漂亮集合指每两个数字都可以的整除的集合，求数字范围从 $l$ 到 $r$ 的漂亮集合最大的大小和最大大小的数量。

## 题目分析

对于一个集合，若将其元素排序数组 $a$，则由定义可得，这个集合是漂亮集合的充分且必要条件是 $a_{i-1}$ 整除 $a_{i}$，我们可以先求最大大小，即让这个漂亮集合的最小值为 $l$，$a_{i} = a_{i-1} \times 2$，统计乘的次数即可，记这个大小为 $ans1$。下面求这个大小的漂亮集合的数量 $ans2$，我们发现刚才所求得的最大漂亮集合的最大值是最小值的 $x=2^{ans1-1}$ 倍，先给 $ans2$ 加上公比为 $2$ 时的集合数量 $\lfloor \frac{r}{x} \rfloor - l + 1$。然后我们可以尝试将原本的等比数列 $a$ 中的一项与上一项之比改为 $3$，这时 $x=2^{ans1-2} \times 3$，若 $l \times x \leq r $，则让 $ans2$ 增加 $(\lfloor \frac{r}{x} \rfloor - l + 1)(ans1 - 1)$，因为除了首项不能选外（会与等比为 $2$ 的情况重复），有 $ans1-1$ 种方案。可以参考代码。

## 代码

```cpp
void solve()
{
    i64 l, r;
    cin >> l >> r;
    i64 tmp = l, ans1 = 0, ans2 = 0;
    while (tmp <= r) ++ans1, tmp <<= 1;
    cout << ans1 << ' ';
    i64 x = 1 << (ans1 - 1);
    if (ans1 == 1)
    {
        cout << r - l + 1 << '\n';
        return;
    }
    i64 k = r / x;
    ans2 = k - l + 1;
    x = x / 2 * 3;
    k = r / x;
    if (k >= l) ans2 += (k - l + 1) * (ans1 - 1) % mod;
    cout << ans2 % mod << '\n';
}
```

---

