# Border

## 题目描述

Astronaut Natasha arrived on Mars. She knows that the Martians are very poor aliens. To ensure a better life for the Mars citizens, their emperor decided to take tax from every tourist who visited the planet. Natasha is the inhabitant of Earth, therefore she had to pay the tax to enter the territory of Mars.

There are $ n $ banknote denominations on Mars: the value of $ i $ -th banknote is $ a_i $ . Natasha has an infinite number of banknotes of each denomination.

Martians have $ k $ fingers on their hands, so they use a number system with base $ k $ . In addition, the Martians consider the digit $ d $ (in the number system with base $ k $ ) divine. Thus, if the last digit in Natasha's tax amount written in the number system with the base $ k $ is $ d $ , the Martians will be happy. Unfortunately, Natasha does not know the Martians' divine digit yet.

Determine for which values $ d $ Natasha can make the Martians happy.

Natasha can use only her banknotes. Martians don't give her change.

## 说明/提示

Consider the first test case. It uses the octal number system.

If you take one banknote with the value of $ 12 $ , you will get $ 14_8 $ in octal system. The last digit is $ 4_8 $ .

If you take one banknote with the value of $ 12 $ and one banknote with the value of $ 20 $ , the total value will be $ 32 $ . In the octal system, it is $ 40_8 $ . The last digit is $ 0_8 $ .

If you take two banknotes with the value of $ 20 $ , the total value will be $ 40 $ , this is $ 50_8 $ in the octal system. The last digit is $ 0_8 $ .

No other digits other than $ 0_8 $ and $ 4_8 $ can be obtained. Digits $ 0_8 $ and $ 4_8 $ could also be obtained in other ways.

The second test case uses the decimal number system. The nominals of all banknotes end with zero, so Natasha can give the Martians only the amount whose decimal notation also ends with zero.

## 样例 #1

### 输入

```
2 8
12 20
```

### 输出

```
2
0 4 ```

## 样例 #2

### 输入

```
3 10
10 20 30
```

### 输出

```
1
0 ```

# 题解

## 作者：Otue (赞：7)

## 题目大意
给定 $n$ 个数的序列 $a$ 和一个整数 $k$。$a$ 数组中选择一些数总和模 $k$ 为 $c$，输出所有可能的 $c$ 的情况。
## 思路
选择的数总和肯定为 $\gcd(a_1,a_2,...,a_n)$ 的倍数，记 $d=\gcd(a_1,a_2,...a_n)$。

则选择的数总和为 $d\times x$，$x$ 为整数。如果末尾数字为 $c$ 则有：

$$dx≡c\pmod k$$

即 $dx+ky=c$。由裴蜀定理，$c$ 一定为 $\gcd(d,k)$ 的倍数。即共有 $\dfrac{k}{\gcd(d,k)}$ 种 $c$，它们从 $0$ 开始，每一项都是 $\gcd(d,k)$ 的倍数。
## 代码
代码十分简短。

```c++
// 惊奇的发现裴蜀定理模板题竟是 CF1800
#include <bits/stdc++.h>
using namespace std;

#define int long long
const int N = 5e5 + 5;

int n, k, a[N], ans;

signed main() {
	cin >> n >> k;
	for (int i = 1; i <= n; i++) cin >> a[i];
	ans = k;
	for (int i = 1; i <= n; i++) ans = __gcd(ans, a[i]);
	cout << k / ans << endl;
	for (int i = 0; i < k / ans; i++) cout << i * ans << ' ';
}
```

---

## 作者：BLUESKY007 (赞：3)

$\ \ \ \ \ \ $这道题大致题意是给定$n$个十进制整数和一个进制数$k$，可以用无数多个给定的十进制整数，问这些十进制整数的和在模k意义下有多少种不同的结果（$k$进制下整数的最后一位就是这个数模$k$的余数）。  
$\ \ \ \ \ \ $这明显是个数学题~~（但是不会做又有什么办法[逃]）~~，既然是求模k意义下的可能结果，我们可以让所有数对k取模，这样可以得到末位数字。但是对于蒟蒻来说这有什么用呢~~（反正本蒟蒻取模之后也还是看不出来）~~。其实这道题并不是要取模，也不是要用进制，而是在十进制下求最大公约数（下面详细解释）。  
$\ \ \ \ \ \ $众所周知有一道~~（毒瘤）~~题叫做[小凯的疑惑](https://www.luogu.org/problemnew/show/P3951)，这道题的结论是对于互质的两个数$a$和$b$，所有大于$a \times b-a-b$的数都可以用若干个$a,b$相加得到~~（别问我为什么看见这题想到了这个结论）~~$\color{#FFF}\text{因为它太毒瘤啦qwq}$。  
$\ \ \ \ \ \ $看到这里蒟蒻一定会问，为什么这道题会和最大公约数有关呢？因为exgcd告诉我们二元一次方程$ax+by=c$在$c \neq 0  ( mod \ \ gcd(x,y) ) $时无整数解，这个非常简单，因为$x = y= 0  ( mod \ \ gcd(x,y) ) $，所以$c=0 \times a+0 \times b=0 ( mod \ \ gcd(x,y) ) $，那么设给定的$n$个数的最大公约数$gcd({a_1},{a_2}, \cdots,{a_n} )=g$，则用给定的$n$个数的任意和都是$g$的倍数。既然所有$g$的倍数都可以构造，那么在模$k$意义下有多少个不同的数呢？此时就有一个二元一次方程$ag=bk+r(0 \leq r <k)$，答案个数也即$r$的可能取值个数，变形可得$ag-bk=r$，由exgcd得，当且仅当$r = 0(mod\ gcd(g,k))$时，方程有整数解。至此我们可以得到，对于任意的$ans \in [0,k)$满足$ans \equiv 0 (mod\ gcd({a_1},{a_2},\cdots ,{a_n},k))$都可以由若干个${a_1},{a_2},\cdots,{a_n}$相加得到（在模$k$意义下）。  
$\ \ \ \ \ \ $以上是本题的思路叙述，下面放上AC代码$\downarrow \downarrow \downarrow$
```cpp
#include<cstdio>//CF1010C 
#include<iostream>
#include<cstring>
#include<cstdlib>
#include<string>
#include<cmath>
#include<algorithm>
#define N 100010

using namespace std;

int n,k,a[N],gg,ans;

int gcd(int a,int b){
	if(b==0){
		return a;
	} 
	return gcd(b,a%b);
}

int main(){
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
    	scanf("%d",&a[i]);
	}
	gg=a[1];
	for(int i=2;i<=n;i++){
		if(gg==1){
			break;
		} 
		if(a[i]>gg){
			gg=gcd(a[i],gg);
		}
		else{
			gg=gcd(gg,a[i]);
		}
	}
	if(gg>k){
		gg=gcd(gg,k);
	}
	else{
		gg=gcd(k,gg);
	}
	ans=k/gg;
	printf("%d\n",ans);
	for(int i=0;i<ans;i++){
		printf("%d ",i*gg);
	}
    return 0;
}
```
$p.s.$有一点小的细节，就是在$gcd$已经等于$ 1 $的时候跳出循环，这样能跑的更快一点~~（其实也快不到哪里去...本来跑的就不慢[逃]）~~

---

## 作者：Infinity_Fantasy (赞：2)

## 题意分析
根据题目描述，最后我们凑出来的数字是 $x_1a_1+x_2a_2+\dots+x_na_n$，我们发现这个不就是多个整数的裴蜀定理吗，于是就有凑出来的数字都是 $\gcd(a_1,a_2,\dots,a_n)$ 的倍数。因为我们要求的是答案在 $k$ 进制下的最后一位，防止这个数大于 $k$，我们对二者再取最大公约数，我们记这个最大公约数为 $S$。

## 构造答案
根据如上推导，答案是 $S$ 的倍数，一开始我们什么都不选的答案为 0，每次加上这个 $S$，注意到答案不能超过 $k$，因此答案个数为 $\lfloor\frac{k}{S}\rfloor$。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,gd,a,ans;
int main(){
    cin>>n>>k;gd=k;
    for(int i=1;i<=n;i++) 
    	cin>>a,gd=__gcd(gd,a);
    cout<<k/gd<<"\n";
    for(int i=1;i<=k/gd;i++){
    	cout<<ans<<" ";
    	ans+=gd;
     }
    return 0;
}
```

---

## 作者：残阳如血 (赞：2)

### $\textbf{Description}$

给定一个序列 $\{a_n\}$，求这些数的线性组合在模 $k$ 的意义下有多少种不同的值。

$1\le n\le10^5$，$2\le k\le10^5$。

### $\textbf{Solution}$

题目要求的就是如下式子
$$
\sum\limits_{i=1}^{n}{t_i\times a_i}\equiv c\pmod k
$$
中 $c$ 的数量。

---

可以令 $a_{n+1}\gets k$，这样原式即可转化为
$$
\Big(\sum\limits_{i=1}^{n}{t_i\times a_i}\Big)+t_{n+1}\times a_{n+1}\equiv c\pmod k\\
\Big(\sum\limits_{i=1}^{n}{t_i\times a_i}\Big)+t_{n+1}\times a_{n+1}= c\\
\sum\limits_{i=1}^{n+1}{t_i\times a_i}=c\\
$$

---

> **裴蜀定理**
>
> 若 $a,b\in\mathbb{Z}$，则必然 $\exist\, x,y\in\mathbb{Z}$，使得 $ax+by=\gcd(a,b)$ 成立。

将其进行扩展，即可得

> 若 $\forall\, x\in\{a_n\}$，有 $x\in\mathbb{Z}$，则必然存在一组解 $\{t_n\}$​，使得
> $$
> \sum\limits_{i=1}^{n+1}{t_i\times a_i}=\gcd(a_1,a_2,\dots,a_n,a_n)
> $$
> 成立。

故由此可知，若 $c$ 是 $\gcd(a_1,a_2,\dots,a_n,k)$ 的倍数，那么就必然存在 $\{t_n\}$ 的一组解。

---

故求出 $d\gets \gcd(a_1,a_2,\dots,a_n,k)$，然后枚举 $d$ 的倍数，直到其 $\ge k$​。

> PS：这里倍数也包括 **$0$ 倍**！

### $\textbf{Code}$

```cpp
#include <bits/stdc++.h>
const int N = 1e5 + 10;

int n, k, d, a[N];

int main() {
  // 读入
  std::cin >> n >> k;
  for (int i = 1; i <= n; ++i)
    std::cin >> a[i];

  // 求出 gcd(a_1,a_2,...,a_n,k)
  d = std::__gcd(a[1], k);
  for (int i = 2; i <= n; ++i)
    d = std::__gcd(d, a[i]);
  
  // 找到 d 所有倍数中 < k 的个数，并将其依次输出
  std::cout << k / d << std::endl;
  for (int i = 0; i * d < k; ++i)
    std::cout << i * d << ' ';
  std::cout << std::endl;
  return 0;
}
```

---

## 作者：hzoi_Shadow (赞：2)

[题目传送门](https://www.luogu.com.cn/problem/CF1010C)

# 前置知识

[最大公约数](https://oi-wiki.org/math/number-theory/gcd/) | [裴蜀定理](https://oi-wiki.org/math/number-theory/bezouts/)

# 简化题意

给定一个长度为 $n$ 的序列 $a$，求 $(\sum\limits_{i=1}^{n}d_ia_i) \bmod k$ 一共会有多少种不同的取值及取值的所有情况，其中对于每一个 $i(1 \le i \le n)$ 均有 $d_i$ 为非负整数。

# 解法

依据裴蜀定理，不难得到存在一个长度为 $n$ 的序列 $x$ 满足 $a_1 x_1+a_2 x_2+a_3 x_3+ \dots = \gcd(a_1,a_2,a_3, \dots ,a_n)$，其中对于每一个 $i(1 \le i \le n)$ 均有 $x_i$ 为整数。所以一定有 $\gcd(a_1,a_2,a_3, \dots ,a_n)|\sum\limits_{i=1}^{n}d_ia_i$。

设 $d'=\gcd(a_1,a_2,a_3, \dots ,a_n),r=(\sum\limits_{i=1}^{n}d_ia_i) \bmod k,\sum\limits_{i=1}^{n}d_ia_i=d'l=kh+r$，不难得到当 $h$ 极大时有一组长度为 $n$ 的序列 $d$ 满足对于每一个 $i(1 \le i \le n)$ 均有 $d_i$ 为非负整数。
  - 这里可以感性理解一下。

于是可以建立一个不定方程 $d'l=kh+r$，用 $x'$ 代替 $l$，用 $y'$ 代替 $-h$，得 $d'x'+ky'=r$。依据裴蜀定理，该方程有解当且仅当 $\gcd(d',k)|r$。因为 $0 \le r<k$，所以共有 $\dfrac{k}{\gcd(d',k)}$ 个不同的取值，为保证递增有第 $i(1 \le i \le \dfrac{k}{\gcd(d',k)})$ 个取值为 $(i-1) \times \gcd(d',k)$。

# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long 
#define sort stable_sort 
#define endl '\n'
int a[500001];
int gcd(int a,int b)
{
	return b?gcd(b,a%b):a;
}
int main()
{
	int n,k,i,ans=0;
	cin>>n>>k;
	ans=k;
	for(i=1;i<=n;i++)
	{
		cin>>a[i];
		ans=gcd(ans,a[i]);
	}
	cout<<k/ans<<endl;
	for(i=0;i<=k/ans-1;i++)
	{
		cout<<i*ans<<" ";
	}
	return 0;
}
```

---

## 作者：Fa_Nanf1204 (赞：1)

### 分析：
首先题目中要求我们凑数，那我们先将这些数表示出来 $x_1a_1+x_2a_2+ \cdots + x_na_n$ 根据推广后的裴蜀定理，发现其一定是 $\gcd(a_1,a_2,\cdots,a_n)$ 的倍数，所以简化，令 $\gcd(a_1,a_2,\cdots,a_n)=d$ 则我们选的数就是 $dx$。转换为 $k$ 进制后所要求凑的末尾的数就可以表示为，$dx\equiv c\pmod k$，再次变形 $dx+ky=c$，很眼熟对吧，再用裴蜀定理得出 $c$ 是 $\gcd(d,k)$ 倍数，$c$ 的取值总共有 $\frac{k}{\gcd(d,k)}$ 个，从 $0$ 开始。
### Code:

```cpp
#include<bits/stdc++.h>
#define N 100005
using namespace std; 
int n,k,a[N],gcd,cnt,st,GCD;
int main(){
	cin>>n>>k;
	for(int i=1;i<=n;i++){
		cin>>a[i];
		gcd=__gcd(gcd,a[i]);
	}
	//gcd*x+k*y=__gcd(gcd,k)*z
	GCD=__gcd(gcd,k);
	cnt=k/GCD;
	cout<<cnt<<'\n';
	for(int i=1;i<=cnt;i++){
		cout<<st<<' ';
		st+=GCD;
	}
	return 0;
} 
```

---

## 作者：littleqwq (赞：1)

# CF1010C Border 题解

### 大致思路：

首先我们知道，我们选择的数，一定是 $\gcd(a_1, a_2,..., a_n)$ 的倍数，我们把 $\gcd(a_1, a_2,..., a_n)$ 看成一个变量 $x$，显然能得出 $x × y \equiv p (\bmod \ k)$，其中 $x × y$ 为选择的数的总和， $p$ 为可能的余数。那么由裴蜀定理可知，总共有 $\frac{k}{\gcd(k, x)}$ 种可能的余数，显然分别是 $0, k, 2k, 3k...$，我们依次输出即可，可能有人要问不是 $k$ 的倍数吗，但是我们可以用一个非常好的方法去思考，样例上第一个数都是 $0$，显然第一位必然是 $0$，接着就是可以用数学方法，必然能够算出一种方法，使得余数为 $0$，所以我们从 $0$ 到 $\frac{k}{\gcd(k, x)} - 1$ 依次枚举即可。

### 代码实现：

```
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n, k, res, x;
signed main()
{
	cin >> n >> k;
    res = k;
	for (int i = 1;i <= n; ++ i)
	{
        cin >> x;
		res = __gcd(res, x);
	}
    int P = k / res;
    cout << P << "\n";
	for (int i = 0;i < P; ++ i)
    {
        cout << i * res << " ";
    }
    cout << "\n";
	return 0;
}
```

这样这道题目就完成啦！！！

---

## 作者：hanmm81 (赞：1)

## 题目大意

给出 $n$ 个数的序列 $a$ 和一个整数 $k$，求 $(\sum\limits_{i=1}^{n}a_ix_i)\bmod k$（$x_i$ 为非负整数）的所有可能值

# 思路

根据裴蜀定理，我们可以知道 $\sum\limits_{i=1}^{n}a_ix_i$ 的值一定为 $\gcd(a_1,a_2,\dots,a_n)$ 的倍数，且由于要模 $k$ 且 $k \le 10000$，我们就可以开始枚举。

第一个答案就直接是 $\gcd(a_1,a_2,\dots,a_n) \bmod k$，而接下来的答案为上一个答案加 $\gcd(a_1,a_2,\dots,a_n)$ 然后模 $k$。而如果当前答案重复了就说明找完了输出答案。时间复杂度 $\mathcal{O}(n \log n + k)$

# 代码思路

这里用 `bool` 数组或 `bitset` 直接按思路干就行，只不过 `bitset` 的函数很方便所以我用的 `bitset`，代码如下：

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int n,k,a[100005],Gcd;
bitset<100005> bit;
/*
这里用到的一些 bitset 函数：
count()：返回有多少个 1。
_Find_first()：返回第一个 1 的下标。
_Find_next(int x)：返回 x 后面（不包括 x）的第一个 1 的下标。
_Find_first() 与 _Find_next()在没找到的情况下都返回 bitset 的大小 
*/
signed main(){
	cin >> n >> k;
	for (int i = 1;i <= n;i++) cin >> a[i],Gcd = __gcd(Gcd,a[i]);//找出第一个答案 
	for (int i = Gcd%k;!bit[i];i = (i+Gcd)%k) bit[i] = 1;//枚举答案 
	cout << bit.count() << "\n";
	for (int i = bit._Find_first();i != 100005;i = bit._Find_next(i)) cout << i << " ";//找被记录的答案
	return 0;
} 
```

---

## 作者：大菜鸡fks (赞：1)

这个加的过程和exgcd过程有点像。

不难yy出最小能构造的非0的就是gcd。

然后就是1*gcd,2*gcd,....

```cpp
#include<cstdio>
using namespace std;
int n,k,Gcd;
int gcd(int x,int y){(!y)?x:gcd(y,x%y);}
int main(){
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++){
		int x; scanf("%d",&x);
		Gcd=gcd(Gcd,x%k); 
	}
	printf("%d\n",k/Gcd);
	for (int i=0;i<k/Gcd;i++){
		printf("%d ",i*Gcd);
	}
	puts("");
	return 0;
} 
```

---

## 作者：Li_Yichen (赞：0)

首先声明一点，本题解在洛谷上因为评测问题没有评测记录，但是在官网已经通过。假设每一种货币 $a_i$ 的使用次数是 $x_i$，那么我们要求的是 $(a_1x_1 + a_2x_2 + ... + a_nx_n)$ 取模 $k$ 的可能出现数字的个数。那么我们定义现在的结果 $now = (a_1x_1 + a_2x_2 + ... + a_nx_n) \bmod k$，那么 $now = (a_1x_1 + a_2x_2 + ... + a_nx_n) - pk$，那么也就是说 $now$ 一定是 $\gcd(a_1,a_2,...,a_n,k)$ 的倍数，所有在范围内的倍数都是可能的答案。定义 $g = \gcd(a_1,a_2,...,a_n,k)$，方案数显然为 $\frac{k}{g}$。


```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n;
int k;
int a[500005];
int ans;
signed main() {
	cin >> n >> k;
	for(int i=1;i<=n;i++){
        cin >> a[i];
    }
	for(int i=1;i<=n;i++){
        ans = __gcd(ans,a[i]);
    }
    ans = __gcd(ans,k);
	cout << k / ans << endl;
    for(int i=0;i<k/ans;i++){
        cout << i * ans << " ";
    }
	return 0;
}
```

---

## 作者：chenhouyuan (赞：0)

## 题意
给你一个长度为 $n$ 的序列 $a$，同时令 $c\equiv\sum^n_{i=1}a_ib_i\pmod k$，求 $c$ 有多少种可能的值及其分别是多少。
## Solution
由裴蜀定理知 $c$ 一定是 $\gcd(a_1,a_2,\ldots,a_n)$ 的倍数，则原式可化为 $c\equiv\gcd(a_1,a_2,\ldots,a_n)x\pmod k$ 即 $\gcd(a_1,a_2,\ldots,a_n)x+ky\equiv c\pmod k$ 还是由裴蜀定理知 $c$ 是 $\gcd(a_1,a_2,\ldots,a_n,k)$ 的倍数，则 $c$ 有 $\lfloor\frac{k-1}{\gcd(a_1,a_2,\ldots,a_n,k)}\rfloor+1$ 种可能的值，然后输出 $0$ 以及 $\gcd(a_1,a_2,\ldots,a_n,k)$ 的倍数即可。
## AC Code
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll N=1e5+5;
ll n,k;
ll gcd(ll a,ll b){
	if(b==0)return a;
	return gcd(b,a%b);
}
int main(){
	ll a[N],x;
	cin>>n>>k;
	for(ll i=0;i<n;i++){
		cin>>a[i];
		if(i==0)x=a[i];
		else x=gcd(x,a[i]);
	}
	x=gcd(x,k);
	cout<<(k-1)/x+1<<endl;
	ll num=0;
	while(num<k){
		cout<<num<<' ';
		num+=x;
	}
	return 0;
}
```

---

## 作者：small_john (赞：0)

## 思路

神仙题。

首先发现，设 $g=\displaystyle\gcd_{i=1}^n a_i$，那么最终的结果一定是 $xg\equiv m\pmod x$（$x$ 是非负整数），把这个式子用模的形式表示出来，即 $xg=yk+m$。然后将左边的项往右移，得到 $xg-yk=m$，这就是一个二元一次不定方程的形式。

根据裴蜀定理，这个方程有解当且仅当 $m$ 是 $\gcd(g,k)$ 的倍数。又由于 $0\le m<k$，所以答案就被确定了。输出这个范围内的 $\gcd(g,k)$ 的倍数即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

template<typename T> inline void read(T &x)
{
	x = 0;
	T f = 1;char ch = getchar();
	while(ch<'0'||ch>'9')
	{
		if(ch=='-')
		{
			f = -1,ch = getchar();
			break;
		}
		ch = getchar();
	}
	while(ch>='0'&&ch<='9')
		x = (x<<3)+(x<<1)+ch-48,ch = getchar();
	x*=f;
}
template<typename T = int> inline T read()
{
	T x;read(x);return x;
}
template<typename T> void write(T x)
{
    if(x<0) x = -x,putchar('-');
    if(x>9) write(x/10);
    putchar(x%10+48);
}
template<typename T> inline void writen(T x)
{
    write(x);
    putchar(10);
}
int n,k;
signed main()
{
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n),read(k);
	int g = k;
	for(int i = 1,x;i<=n;i++)
		read(x),g = __gcd(g,x);
	writen(k/g);
	for(int i = 0;i<k/g;i++)
		write(i*g),putchar(32);
	return 0;
}
```

---

## 作者：yyz_100110 (赞：0)

# [题目传送门](https://www.luogu.com.cn/problem/CF1010C)

### 题面分析：

给你一个序列 $a$ 个数为 $n$，和一个正整数 $k$，让你求出 $a$ 序列中的一些数加和模 $k$ 为 $m$，同时输出所有方案。

### 思路：

这个题好似是[裴蜀定理](https://baike.baidu.com/item/%E8%A3%B4%E8%9C%80%E5%AE%9A%E7%90%86/5186593)的板子题。

![](https://cdn.luogu.com.cn/upload/image_hosting/2stzfvph.png)

带入本题，那么可以得出，我们在序列 $a$ 中选择的数的总和一定为 $\gcd(a_1,a_2,a_3\cdots,a_n)$ 的倍数，我们可以记为 $d =\gcd(a_1,a_2,a_3\cdots,a_n)$。


`ax+by=m` 由此带入题目可化为 $dx+by=m$。那么一共有 $k$ 除以 $\gcd(d,k)$ 种方案。

### AcCode：

```cpp
#include<iostream>
#include<cstdio>
#define int long long
using namespace std;
const int N=10005;
int a[N];
int gcd(int a,int b){//手打 gcd。
    return !b?a:gcd(b,a%b);
}
signed main(){
	int n,k,m;
	    cin>>n>>k,m=k;
	for(int i=1;i<=n;i++) 
	    cin>>a[i],m=gcd(m,a[i]);//如上
	cout<<k/m<<'\n';
	for(int i=0;i<k/m;i++) cout<<i*m<<' ';
}
```

奉上 [AC记录](https://www.luogu.com.cn/record/138052977)。

谢谢观看！

---

## 作者：fedoralxy (赞：0)

## 题目翻译

给定长度为 $n$ 的序列 $a$ 和一个整数 $k$ 数组 $a$ 中一些数总和模 $k$ 为 $c$,输出所有可能的 $c$ 的情况。

## 解题思路

很显然，选择数的总和等于所有数取最大公因数,即  $(a_1,a_2,a_3,a_4,……,a_n)$ 的倍数。

设选择的数分别为 $d_1,d_2,d_3,……,d_n$。

令 $\sum_{i=1}^n d_i =x$，则易得：

$(a_1,a_2,a_3,a_4,……,a_n)\mid x$

令 $(a_1,a_2,a_3,a_4,……,a_n)=p$，易得：

 $x=pq(q\in N^+)$ 

设 $x$ 的末尾数字为 $w$，得到：

 $x\equiv w \pmod k$。

即，$x+kd=w$ 

有裴蜀定理:

设 $a,b\neq 0$ 且 $a,b \in N^+$，存在 $x,y \in N^+$ 使 $ax+by=(a,b)$

得：$(p,k)\mid  w$。
 
所以，共有 $\frac{k}{(p,k)}$ 种选择。

枚举即可。

注意的一点是每一项都是 
$(p,k)$ 的倍数。

### 代码

```cpp
#include<iostream>
#include<cstdio>
ll n,k;
ll a[N];
int main()
{
//	freopen("data.in","r",stdin);
//	freopen("data.out","w",stdout);
	std::cin>>n>>k;
	for(int i=1;i<=n;i++)cin>>a[i];
	ll d=k;
	for(int i=1;i<=n;i++)
		d=__gcd(d,a[i]);
	std::cout<<k/d<<endl;
	for(int i=0;i<k/d;i++)
		std::cout<<i*d<<" ";
	return 0;
}

```

---

## 作者：Areka6219 (赞：0)

## 题意
给你 $n$ 个数和 $k$，让你求出这些数在 $\bmod \ k$ 的情况下能够凑出在区间 $[0, k - 1]$ 内的多少数并输出。
## 解法
- 这里提供的是 $O(nlogn + k)$ 的写法。
- 我们设 $x=\gcd(a_1,a_2,a_3,a_4,\cdots,a_n,k)$ 可以发现，我们凑出来的数均为 $x$ 的倍数。

- 证明：
设凑出来的数为 $p$，则：
$$
p = d_ia_i + d_ja_j + \cdots + d_na_n
$$
- 其中 $d_i$ 为系数。
- 因为 $x=\gcd(a_1,a_2,a_3,a_4,\cdots,a_n,k)$，所以 $x|p$，所以 $p$ 为 $x$ 的倍数。
- 于是我们想到求出 $x$ ，枚举 $x$ 的倍数即可。
- 枚举到哪里呢？我们知道 $(d_i *x) \bmod k$ 循环节为 $k$，所以枚举到 $k-1$ 就好啦！

## Code
```cpp
#include <bits/stdc++.h>

using namespace std;

#define int long long

inline int read() {
    register int x = 0, f = 1;
    register char ch;
    while(!isdigit(ch = getchar())) (ch == '-') && (f = -1);
    for(x = ch ^ 48; isdigit(ch = getchar()); x = (x << 3) + (x << 1) + (ch ^ 48));
    return x * f;
}

// ssds

int a, g, n, k;
vector <int> v;

bool vis[300001];

signed main() {
    n = read(), k = read();
    
    g = read();
    for(int i = 2; i <= n; ++i)
        g = __gcd(a = read(), g);
    g = __gcd(g, k);

    for(int i = 0; i < k; ++i) {
        int x = (g * i) % k;
        if(!vis[x])
            vis[x] = true, v.push_back(x);
    }
    
    cout << v.size() << endl;
    for(int i = 0; i < v.size(); ++i)
        cout << v[i] << " ";

    #ifndef ONLINE_JUDGE
        getchar();
    #endif
    return 0;
}

```

---

