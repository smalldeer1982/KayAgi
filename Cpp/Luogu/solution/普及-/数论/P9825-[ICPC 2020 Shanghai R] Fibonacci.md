# [ICPC 2020 Shanghai R] Fibonacci

## 题目描述

在数学中，斐波那契数列通常用 $f_n$ 表示，是一个序列，其中每个数字是前两个数字之和，起始为 $1$ 和 $1$。即 $f_1 = 1, f_2 = 1$，且 $f_n = f_{n-2} + f_{n-1}~(n \ge 3)$。

因此，该序列的开头是 $1, 1, 2, 3, 5, 8, 13, 21,\ldots$。

给定 $n$，请计算 $\sum_{i=1}^{n}{\sum_{j=i+1}^{n}{g(f_i,f_j)}}$，其中 $g(x,y) = 1$ 当 $x \cdot y$ 为偶数时，否则 $g(x,y) = 0$。

## 说明/提示

题面翻译由 ChatGPT-4o 提供。

## 样例 #1

### 输入

```
3```

### 输出

```
2```

## 样例 #2

### 输入

```
10```

### 输出

```
24```

## 样例 #3

### 输入

```
100```

### 输出

```
2739```

# 题解

## 作者：RP_I_AK_CSP (赞：9)

# P9825 [ICPC2020 Shanghai R] Fibonacci 题解

### 大致思路：

斐波那契数列有奇偶性的规律：奇、奇、偶、奇、奇、偶……

总共偶数个数为 $x = n ÷ 3$ 个，而想要使乘积是偶数，只有奇数乘偶数或偶数乘偶数两种可能：

- 第一种奇数乘偶数。贡献值为 $x (n - x)$。

- 第二种偶数乘偶数。贡献值为 $x (x - 1) ÷ 2$。

把它们相加就是总贡献值。

### 正确代码：

```
#include<bits/stdc++.h>
using namespace std;
long long n,x,a,b;
int main(){
	cin>>n;
	x=n/3;
	a=x*(n-x);
	b=x*(x-1)/2;
	cout<<(a+b)<<endl;
	return 0;
}
```

这道题就这样完成啦！！！

---

## 作者：chen_zhe (赞：6)

以下内容转载自官方题解：

考虑斐波那契数列模 $2$ 以后的值 $g$，$g_{3k} = 0$, $g_{3k+1}=g_{3k+2}=1$，我们只需要计算一下 $1\dots n$ 中有几个奇数，有几个偶数，就可以算出答案啦。

---

## 作者：littleqwq (赞：2)

# P9825 [ICPC2020 Shanghai R] Fibonacci 题解

### 大致思路：

- 纯暴力，用 $n ^ 2$ 的复杂度一个个列举出来，在列举途中把第 $i$ 项的斐波那契算出来，看看满足条件的数量，输出答案。

#### 实现代码：

```
#include<bits/stdc++.h>
using namespace std;
long long n,ans;
int f(int k){
	if(k==1)return 1;
	if(k==2)return 1;
	return f(k-1)+f(k-2);
}
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if((f(i)*f(j))%2==0){
				ans++;
			} 
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

成功收获大量超时。

- 在上面的方法中稍做优化，先算出斐波那契前 $n$ 项，在一个个暴力计算，输出答案。

#### 实现代码：

```
#include<bits/stdc++.h>
using namespace std;
long long n,a[1000001],ans;
int main(){
	cin>>n;
	a[1]=1;
	a[2]=1;
	a[3]=2;
	for(int i=3;i<=n;i++){
		a[i]=a[i-1]+a[i-2];
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if((a[i]*a[j])%2==0){
				ans++;
			} 
		}
	}
	cout<<ans<<endl;
	return 0;
}
```

本次不是超时，由于数据在 $10^9$ 以内，所以收获了越界。

- 找规律，我们会发现，斐波那契数列有奇偶性规律，都是以：奇、奇、偶、奇、奇、偶……这样的顺序出现，而想要使乘积为偶数，只有偶数乘偶数，或者偶数乘奇数两种可能，而这两种可能必须包含偶数，而结合上面数列的奇偶性，那么数列的前 $n$ 位包含 $n ÷ 3$ 个偶数，我们把它看为 $k$，接着分类讨论：

1. 奇数乘偶数，我们要从 $k$ 个数中选一个，从 $n - k$ 个剩下的数中选一个，一共有 $k × (n - k)$ 种可能。

2. 偶数乘偶数，我们要从 $k$ 个数中选两个，一共有 $k × (k - 1) ÷ 2$ 种可能。

总共有 $k × (n - k) + k × (k - 1) ÷ 2$ 种可能。

### 代码实现：

```
#include<bits/stdc++.h>
using namespace std;
long long n,k;
int main(){
	cin>>n;
	k=n/3;
	cout<<((k*(k-1)/2)+(k*(n-k)))<<endl;
	return 0;
}
```

这样这道题就顺利完成啦！！！

---

## 作者：Big_Dinosaur (赞：2)

数学题。

$f_i$ 为偶数，当 $i \bmod 3=0$ 时成立。前 $n$ 个数，共有 $\lfloor\dfrac{n}{3}\rfloor$ 个偶数。偶数与任意数（共 $n-1$ 个）相乘，为偶数；但是，这样算有重复，两个偶数相乘，记了 $2$ 次，应该减掉，减 $\dfrac{\lfloor\dfrac{n}{3}\rfloor\times(\lfloor\dfrac{n}{3}\rfloor-1)}{2}$。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace ZYT{
inline void _(){
int n;cin>>n;cout<<n/3*(n-1)-(n/3)*(n/3-1)/2;
}
}
signed main(){ZYT::_();}
```

---

## 作者：YMnRb (赞：2)

[返回题目](https://www.luogu.com.cn/problem/P9825 "P9825 [ICPC2020 Shanghai R] Fibonacci")

根据题意，当 $x$ 和 $y$ 有至少一个是偶数时，$g(x,y) = 1$，否则 $g(x,y) = 0$。我们需要求出 $\sum_{i=1}^{n}{\sum_{j=i+1}^{n}{g(f_i,f_j)}}$ 的值。

由于 $n<10^9$，这道题显然不可以用暴力解决。

我们可以发现，斐波那契数列满足以下规律：奇数，奇数，偶数，奇数，奇数，偶数…… 也就是说斐波那契数列的第 $n$ 项 $f_i$ 满足：
$$
\begin{cases}
i\,\text{不能被}\,3\,\text{整除时} & f_i\,\text{为奇数} \\ 
i\,\text{能被}\,3\,\text{整除时} & f_i\,\text{为偶数}
\end{cases}
$$

（对于以上性质，由于证明很简单，在此不做论证，读者可以自行证明。）

当 $i$ 可以被 $3$ 整除时，$f_i$ 是偶数，所以$g(f_i,x) = 1$，$x$ 可以为任何整数。所以 $\sum_{j=i+1}^{n}{g(f_i,f_j)} = n-i$ 。 

由于在 $f_{1,2,3...i-1,i}$ 中，偶数有 $i/3$（向下取整）个，所以在 $f_{i+1,i+2...n-1,n}$ 中，偶数就有 $n/3 - i/3$（向下取整）个。于是当 $i$ 不能被 3 整除时，$\sum_{j=i+1}^{n}{g(f_i,f_j)}=f_{i+1,i+2...n-1,n}$ 中偶数的个数 $=n/3-i/3$（向下取整）。

于是可以得到以下时间复杂度为 $O(n)$ 的代码：

```cpp
// Lang: C/C++

#include <stdio.h>
using ullint = unsigned long long;
// 相当于 typedef unsigned long long ullint;

int main()
{
	int i, n;
	ullint ans = 0; // 由于结果可能很大，所以需要用 unsigned long long
	scanf("%d", &n);
	for (i = 1; i <= n; ++i)
		if (i % 3) ans += n / 3 - i / 3;
		else ans += n - i;
	printf("%llu", ans);
	return O;
}
```

根据以上的思路，我们可以进一步直接列出公式，这样就可以将时间复杂度降到 $O(1)$ 得到答案。推导较为复杂，有能力可以自行推导。

---

还有一种更加简洁的思路如下：

因为当 $x$ 和 $y$ 有至少一个是偶数时，$g(x,y) = 1$，否则 $g(x,y) = 0$。也就是当 $x$ 和 $y$ 都是奇数时，$g(x,y) = 0$，否则 $g(x,y) = 1$ 。

这样，就可以将题目所求的 $\sum_{i=1}^{n}{\sum_{j=i+1}^{n}{g(f_i,f_j)}}$ 转化为 所有满足 $i<j≤n$ 的有序数对 $(i,j)$ 数量 减去 所有满足 $i<j≤n$ 且 $i, j$ 都不能被 $3$ 整除的有序数对 $(i,j)$ 数量。

于是得到以下时间复杂度为 $O(1)$ 的代码：

```cpp
// Lang: C/C++

#include <stdio.h>
using ullint = unsigned long long;

int main()
{
	ullint n; 
	scanf("%llu", &n);
	printf("%llu", n*(n-1)/2 - (n-n/3)*(n-n/3-1)/2);
	return O;
}
```

$\scriptsize\color{#999}\textsf{update: 2023/11/12}$

---

## 作者：2021zjhs005 (赞：1)

~~纯属的签到题。~~

---------------------------------------------------------分割线---------------------------------------------------------


---------------------------------------------------------分割线---------------------------------------------------------

题目大意
-------------

求出：

$$\sum_{i=1}^n\sum_{j=i+1}^{n}g(f_i,f_j)$$

其中，$g(x,y)$ 返回 $1 - x\times y \bmod 2$。

题目分析
------------

首先，我们知道：乘积是偶数，**至少有一个因数是偶数**。

我们仔细观察**斐波那契数列**的**奇偶性**，发现呈如下排列：

奇 奇 偶 奇 奇 偶 奇 奇 偶 奇 奇 偶 ……

**以“奇奇偶”为一个周期**（毕竟**奇数+奇数=偶数，奇数+偶数=奇数**）。

令偶数个数为 $k$（或者说**按照“奇奇偶”的顺序排有 $k$ 组**），则：

$$k=n\div 3$$

继续观察（由于是“奇奇偶”为一个排列，可以每三个分开）：

$1$，$1$，$2$，$3$，$5$，$8$，$13$，$21$，$34$

和右边的斐波那契数相乘之后，有几个偶数：

$3$，$3$，$6$，$2$，$2$，$3$，$1$，$1$，$0$

发现：除了偶数以外的斐波那契数，其余的**和右边数的相乘的结果是偶数的数量**呈**等差数列**，就是 $k \times (k+1) \div 2 $。

由于一组有两个奇数，除了偶数，剩下奇数的匹配方式方案数是：

$$k\times (k+1) \div 2\times 2 = k\times (k+1)$$

加上可能会多余的 $n\bmod 3$ 个奇数（定为 $ji$），也就是有：

$$k\times (k+1) + ji\times k = k\times (k+1+ji)$$

加上偶数可以和任意的数乘（除了最后一个偶数，所以减 $1$），也就是有：

$$k\times (k+1+ji) + (k-1)\times k\times 3\div 2$$

AC 代码
------------

```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
ll n;
int main(){
cin>>n;
ll ou=n/3,ji=n%3; 
cout<<ou*(ou+1+ji)+(ou-1)*ou*3/2;//公式。
return 0;
}
```


---

## 作者：wangjue233 (赞：1)

# Solution
[题目传送门](https://www.luogu.com.cn/problem/P9825)

## 题目描述

给定 $n$，请计算 $\sum_{i=1}^{n}{\sum_{j=i+1}^{n}{g(f_i,f_j)}}$，当 $x \cdot y$ 为偶数时 $g(x,y) = 1$，否则 $g(x,y) = 0$。

## 题目思路

在斐波那契数列中，每个奇数后面有一个奇数，然后是一个偶数。所以，斐波那契数列的周期是：奇数、奇数、偶数、奇数、奇数、偶数……。

因为偶数乘任何数都是偶数，所以每个偶数 $f_i$ 和它后面的所有 $f_j$ ($i < j$) 都会产生一个满足条件的数对。

## 解题步骤

1. 确定数列中位置为偶数的斐波那契数的个数 $k = n / 3$。
2. 对所有的偶数位置的 $f_i$ 进行求和，得到满足条件的数对的个数。

## AC Code

```cpp
#include <iostream>
#define ll long long
using namespace std;
int main(){
    ll n; cin >> n;
    ll k = n / 3; //计算位置为偶数的斐波那契数的个数
    ll k1 = n - k; //计算剩余个数
    ll ans = k * k1 + k * (k - 1) / 2; //用等差数列求和公式计算结果
    cout << ans << "\n"; 
    return 0;
}

---

## 作者：Xdwjs (赞：1)

题目要求我们输出积为偶数时 $i$ 和 $j$ 的组合方式数量。

观察斐波那契数列。前两个数都是奇数，所以第三个数就是偶数；前两个数一个奇数一个偶数，所以第四个数就是奇数；前两个数一个奇数一个偶数，所以第五个数也是奇数。

以此类推。我们很容易发现，如果将斐波那契数列三个分为一组，则每组的前两个数是奇数，最后一个数是偶数。

下一步需要另一个规律：一个偶数乘上另一个数，结果还是偶数，只有相乘的两个数都为奇数时，结果才是奇数。

于是思路就有了，先算出数列中奇数的个数，求出这么多数的组合方式数量，这就是积为奇数时 $i$ 和 $j$ 的组合方式数量，再用所有 $i$ 和 $j$ 的组合数量减去积为奇数时的组合方式数量，就是积为偶数时的组合方式数量。

Code：

```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin>>n;
    int o=(n/3*2)+(n%3);//表示奇数的个数
    cout<<n*(n-1)/2-o*(o-1)/2;
    return 0;
}
```

---

## 作者：ACtheQ (赞：1)

 # [ICPC2020 Shanghai R] Fibonacci 题解
 
 本体考验数学能力。
 
 首先知道 $g(x,y)$ 的目的为判断偶数，若 $x$ 或 $y$ 为偶数，则 $g(x,y)=1$ 否则 $g(x,y)=0$。

找规律可以得知，斐波那契数列的规律是奇、奇、偶，因为 $f_{3\times x+3}=f_{3\times x+2}+f_{3\times x+1}$ 则 $f_{3\times x+3}$ 为偶，因为奇加奇等于偶数。

$f_{3\times y+2}=f_{3\times y+1}+f_{3\times y}$ 则 $f_{3\times y+2}$ 为奇，因为奇加偶等于奇数。

$f_{3\times z+1}=f_{3\times z}+f_{3\times z-1}$ 则 $f_{3\times z+1}$ 为奇，因为偶加奇等于奇数。

那么答案就等于 $\lfloor\frac{n}{3}\rfloor\times(\lfloor\frac{n}{3}\rfloor+1)+\lfloor\frac{n}{3}\rfloor\times n-\lfloor\frac{3+\lfloor\frac{n}{3}\rfloor\times 3}{2}\rfloor)$。

```c++
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main()
{
	int n;
	cin>>n;
	cout<<(int)(n/3)*((int)(n/3)+1)+(int)(n/3)*n-(int)(n/3)*(3+(int)(n/3)*3)/2;
	return 0;
}
```

---

## 作者：tder (赞：1)

[$\Large\color{black}\textbf{P9825 [ICPC2020 Shanghai R] Fibonacci}$](https://www.luogu.com.cn/problem/P9825) $\Large\textbf{题解}$

[$\textbf{题目传送门}$](https://www.luogu.com.cn/problem/P9825)

[$\textbf{更好的阅读体验}$](https://www.luogu.com.cn/blog/tder/solution-P9825)

~~斐波那契...？~~

---

$$\large\textbf{题意}$$


定义斐波那契数列 $f_i$：

$$
f_1=1,f_2=1,f_i=f_{i-1}+f_{i-2}(i>2).
$$

给定整数 $n$，计算所有满足 $1 \le i < j \le n$ 且 $f_i \cdot f_j$ 为偶数的 $(i,j)$ 对数。

---

$$\large\textbf{思路}$$

考虑将斐波那契数列简化，$1$ 表示偶数，$0$ 表示奇数，则为：$001~001~001~001\dotsm$。可以发现每 $3$ 项中有 $1$ 个偶数，即前 $n$ 项中有 $k_1=\lfloor\frac n3\rfloor$ 个偶数、$k_2=n-\lfloor\frac n3\rfloor$ 个奇数。

如果 $x,y$ 中有偶数，那可能有 $1$ 个或 $2$ 个偶数。有 $1$ 个偶数时，由于是组合不考虑顺序，设 $x$ 偶 $y$ 奇，则有 $k_1\times k_2$ 中情况；有 $2$ 个偶数时，则有 $\frac{k_1\times(k_1-1)}2$ 种。答案共有 $k_1k_2+\frac{k_1(k_1-1)}2$ 种。

---

$$\large\textbf{代码}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int N = 1e5 + 5;
signed main() {
	ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
	int n, k1, k2;
	cin>>n; 
	k1 = n / 3, k2 = n - f1;
	cout<<k1 * k2 + k1 * (k1 - 1) / 2;
	return 0;
}
```

---

## 作者：Vct14 (赞：0)

我们已知同号两数之和为偶数，异号两数之和为奇数。

因为斐波那契数列前两项均为奇数，所以第三项为偶数；第四项为第二项（奇数）与第三项（偶数）之和，为奇数；第五项为偶数与奇数之和，为奇数；第六项为两奇数之和，又为偶数。

因此它的规律为奇、奇、偶、奇、奇、偶、奇、奇、偶······

那么其中共有 $m=\left\lfloor\dfrac{n}{3}\right\rfloor$ 个偶数。

因为两数之积为偶数，所以两数中至少有一个偶数。我们分情况考虑。

- 偶数乘偶数。则题目可化为从 $m$ 个数中选择不相同的两个，问方法数。则答案为 $C_m^2=\dfrac{m(m-1)}2$。
- 奇数乘偶数。题目可化为先从 $m$ 个数中选择一个，再从剩下的 $n-m$ 个数中选择一个，问方法数。答案为 $C_m^1\times C_{n-m}^1=m(n-m)$。

最终答案为 $\dfrac{m(m-1)}2+m(n-m)$。

```c++
#include<bits/stdc++.h>
using namespace std;

int main(){
	long long n;
	cin>>n;
	long long m=n/3;
	cout<<m*(m-1)/2+m*(n-m); 
	return 0;
}
```

---

## 作者：FreedomKing (赞：0)

### 思路

首先需要知道只有奇数与奇数相乘才能得出奇数，所以考虑设出每两项之**积都为偶**的贡献减去每**两项都是奇数**的贡献。

通过打表可得斐波那契数列的奇偶规律为“奇奇偶”，每三个为一循环。然后我们便可根据规律求出第 $n$ 项内有多少个奇数，直接组合数两两组合即可。

### AC Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+5;
int a[N],n,m,t,k;
signed main(){
	cin>>n;
	m=n/3;
	t=m*2+n%3;
	cout<<n*(n-1)/2-t*(t-1)/2;
	return 0;
}
```

---

