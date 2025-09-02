# LCM

## 题目描述

Ivan has number $ b $ . He is sorting through the numbers $ a $ from $ 1 $ to $ 10^{18} $ , and for every $ a $ writes $ \frac{[a, \,\, b]}{a} $ on blackboard. Here $ [a, \,\, b] $ stands for least common multiple of $ a $ and $ b $ . Ivan is very lazy, that's why this task bored him soon. But he is interested in how many different numbers he would write on the board if he would finish the task. Help him to find the quantity of different numbers he would write on the board.

## 说明/提示

In the first example $ [a, \,\, 1] = a $ , therefore $ \frac{[a, \,\, b]}{a} $ is always equal to $ 1 $ .

In the second example $ [a, \,\, 2] $ can be equal to $ a $ or $ 2 \cdot a $ depending on parity of $ a $ . $ \frac{[a, \,\, b]}{a} $ can be equal to $ 1 $ and $ 2 $ .

## 样例 #1

### 输入

```
1
```

### 输出

```
1```

## 样例 #2

### 输入

```
2
```

### 输出

```
2```

# 题解

## 作者：Dilute (赞：5)

## 在[本人blog](http://dilute.coding.me/2018/11/17/Solutions/Solution-CF1068B/)食用更佳

~~第一篇题解~~

我们都知道$lcm(a, b) = \frac{a * b}{\gcd(a, b)}$

∴ $\frac{lcm(a, b)}{a} = \frac{\frac{a * b}{\gcd(a, b)}}{a} = \frac{b}{\gcd(a, b)}$

题目的意思就被我们转化成了求$\frac{b}{\gcd(a, b)}$的种类数

又∵b是一个确定的数

∴$\frac{b}{\gcd(a, b)}$的种类数就等于$\gcd(a, b)$的种类数

由于$a$的范围在$[1, 10^{18}]$范围内，所以$\gcd(a, b)$的种类数就等于b的因数个数。

因数个数就可以$O(\sqrt n)$求辣QwQ

```cpp
// Sooke bless me.
// LJC00118 bless me.
#include<bits/stdc++.h>

#define INF 2147483647
#define ll long long

ll Inp(){
	char c = getchar();
	ll Neg = 1;
	while(c < '0' || c > '9'){
		if(c == '-')
			Neg = -1;
		c = getchar();
	}
	ll Sum = 0;
	while(c >= '0' && c <= '9'){
		Sum = ((Sum << 3) + (Sum << 1)) + c - '0';
		c = getchar();
	}
	return Neg * Sum;
}

int main(){
	ll n = Inp();
	ll qn = sqrt(n);
	ll Ans = 1;
	for(ll i = 2; i <= qn; i++){
		ll Cnt = 1;
		while(n % i == 0){
			n /= i;
			Cnt++;
		}
		Ans *= Cnt;
	}
	if(n > 1){
		Ans *= 2;
	}
	printf("%lld", Ans);
}
```

---

## 作者：lin000 (赞：4)

[CF1068B](https://www.luogu.com.cn/problem/CF1068B)

### 思路
题目要求给出数 $b$ 求有几个数 $a$ 满足 $\dfrac{lcm(a,b)}{a}$不相同。 我们可以

把 $b$ 设为 $B_1 \times B_2 \times ... \times B_n \times AB_1 \times AB_2 \times ... \times AB_n$，

把$a$ 设为 $A_1 \times A_2 \times ... \times A_n \times AB_1 \times AB_2 \times ... \times AB_n$

所以 $\dfrac{lcm(a,b)}{a} = \dfrac{b}{A_1 \times A_2 \times ... \times A_n}$
所以只需要找满足条件的 $A$ 的乘积的个数就可以，即，可以整除 $b$。所以本题就是找 $b$ 的因数个数。

### 代码
```cpp
#include <iostream>
#include <cmath>

using namespace std;

long long n , m , nq , ans;
int main(){
	cin >> n;
	for(long long i = 1 ; i <= sqrt(n); i++){
		if(n % i == 0)
			ans += 2;
		if(i * i == n)
			ans --;
	}
	cout << ans;
}
```


---

## 作者：XL4453 (赞：3)

### 题目分析：

首先有一个结论，$\dfrac{a\times b}{(a,b)}=[a,b]$，这个结论的证明很多，介绍一种比较简单的方法，用算术基本定理来证明。

首先可以知道：任意一个正整数 $a$ 都可以唯一分解为 $p_1^{r_1}\times p_2^{r_2}\times p_3^{r_3}...$ 其中 $p$ 表示质数。

那么，有：$[a,b]=p_1^{\max(r_{a1},r_{b1})}\times p_2^{\max(r_{a2},r_{b2})}\times p_3^{\max(r_{a3},r_{b3})}...$ 

且 $(a,b)=p_1^{\min(r_{a1},r_{b1})}\times p_2^{\min(r_{a2},r_{b2})}\times p_3^{\min(r_{a3},r_{b3})}...$ 

则 $\dfrac{a\times b}{(a,b)}=\dfrac{p_1^{r_{a1}+r_{b1}}\times p_1^{r_{a2}+r_{b2}}\times p_1^{r_{a3}+r_{b3}}...}{p_1^{\min(r_{a1},r_{b1})}\times p_2^{\min(r_{a2},r_{b2})}\times p_3^{\min(r_{a3},r_{b3})}...}$

$=p_1^{\max(r_{a1},r_{b1})}\times p_2^{\max(r_{a2},r_{b2})}\times p_3^{\max(r_{a3},r_{b3})}...=[a,b]$

-----------

那么对于这道题：

从原题中的式子推起：

$\dfrac{[a,b]}{a}=\dfrac{\dfrac{a\times b}{(a,b)}}{a}=\dfrac{b}{(a,b)}$

也就是求 $\dfrac{b}{(a,b)}$ 的取值。

由于 $a$ 的范远远大于 $b$，那么一定会将所有的 $b$ 的因数全都取到，而这样的一个式子也不可能出现除了 $b$ 的因数以外的取值，综上所述，得到答案就是 $b$ 的因数数。

------------------
### 代码：

```cpp
#include<cstdio>
using namespace std;
long long n,ans;
int main(){
	scanf("%lld",&n);
	for(long long i=1;i*i<=n;i++){
		if(i*i==n){ans++;continue;}
		if(n%i==0)ans+=2;
	}
	printf("%lld",ans);
	return 0;
}
```


---

## 作者：Z_M__ (赞：2)

类似这种给个式子的题，一般都先要将给的式子简化。

如这题给的式子是 $\dfrac{[a,b]}{a}$ ,上面的这个 $[a,b]=\dfrac{a*b}{\gcd(a,b)}$ , 所以原式就等于 $\dfrac{\tfrac{a*b}{\gcd(a,b)}}{a}=\dfrac{b}{\gcd(a,b)}$

简化完式子后， 现在的问题就是求不同的 $\dfrac{b}{\gcd(a,b)} , a\in[1,1^{10}]$ 的个数。

分几个情况：

1. $a\le b$ , 此时若$a$与$b$互质，那么上面的式子的值就都为$b$，若此时$a$为$b$的因数，则式子等于$b/a$。所以情况$1$中的个数为$b$的所有因数。

2. $a>b$, 若互质结果也为$b$，若$a$为$b$的倍数，则式子的值为$1$。所以情况$2$中的个数只有$1$或$b$两个值。

所以最终上面式子的值的个数为$b$的因数个数。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
int b, ans;
signed main ()
{
    cin >> b;
    for (int i = 1; i * i <= b; i++)
    	if (b % i == 0)
    	{
    		int c = b / i;
    		ans++;
    		if (c != i) ans++;
    	}
    cout << ans << endl;
    return 0;
}
```

---

## 作者：Arghariza (赞：2)

### 先推一下题目:

众所周知，$lcm(a,b)·gcd(a,b)=ab$

移项：$lcm(a,b)=\frac{ab}{gcd(a,b)}$

将$lcm(a,b)=\frac{ab}{gcd(a,b)}$代入原式，得：$\;\frac{lcm(a,b)}{a}=\frac{\frac{ab}{gcd(a,b)}}{a}=\frac{b}{gcd(a,b)}$

又 $ ∵b$是固定的$\;\&\;a\in[1,10^{18}]$

$∴$ 题目所求为$b$的**因数个数**

### 那么$b$的因数个数咋求呢？

- 因数个数定理：

对于任意正整数$x=\prod\limits_{i=1}^{n}p_i^{s_i}$（$p$表示$x$的所有质因子，$s_i$表示质因子$p_i$的个数），有$x$的因数个数$f_x=\prod\limits_{i=1}^{n}(s_i+1)$

~~此题做完~~

来看代码（附注释）：

```
#include <bits/stdc++.h>//万能头
#pragma GCC optimize(2)//开O2
#define ll long long//宏定义long long
using namespace std;//命名空间

ll n, ans = 1, x = 1;//x表示n的因数（递加）

inline ll read() {//快读
    ll w = 1, q = 0;
    char ch = ' ';
    while (ch != '-' && (ch < '0' || ch > '9')) ch = getchar();
    if (ch == '-') w = -1, ch = getchar();
    while (ch >= '0' && ch <= '9') q = q * 10 + ch - '0', ch = getchar();
    return w * q;
}

inline void write(ll x) {//快输
    if (x < 0) {
        x = ~(x - 1);
        putchar('-');
    }
    if (x > 9) write(x / 10);
    putchar(x % 10 + '0');
}

int main() {
	n = read();//读入
	ll k = sqrt(n);//求平方根（优化时间复杂度）
	while (n) {//只要n不为0
		if (x >= k) break;//若因子大于平方根则退出
		ll cnt = 1;//cnt为因子的个数
		x++;//因子递加
		while(n % x == 0) {//如果x是n的因子
			cnt++;//个数+1
			n /= x;//去掉1个x以免重复算
		}
		ans *= cnt;//递乘
	}
	ans = n > 1 ? ans * 2 : ans;//如果n没有除尽，则说明剩下因数1，乘上2(1+1)
	write(ans);//快输ans
	return 0;//结束
}
```

---

## 作者：两年打铁 (赞：1)

蒟蒻先一看题，本来是被题目描述劝退的，后来一想，还是颓一会数论吧。

~~众所周知~~ A和B的LCM是A*B/GCD(A,B).

多么优美的式子，一看题目给的描述，$\frac{LCM(A,B)}{B}$,嘿嘿嘿，~~小天才们~~应该已经想到什么了吧。

对！就是B/GCD(A,B);

那么这道题就是求B的约数了....

我们知道，要得到B的约数，我们只要枚举到$\sqrt{B}$,所以也只有$10^5$

温馨提醒您

# 做题千万个，范围第一个。


# 没有开long long ,爆T两行泪。

```
#include<bits/stdc++.h>
#define int long long 
using namespace std;
signed main()
{
	int b;
	cin>>b;
	int ans;
	if(b==1){puts("1");return 0;}
	if(b==2){puts("2");return 0;}
	for(register int i=1;i*i<=b;++i)
	{
		if(b%i==0)
		{
			if(i*i==b)
			{
				ans++;
				continue;
			}
			else 
			{
				ans+=2;
			}
		}
	}
	cout<<ans;
}
```


---

## 作者：sinsop90 (赞：1)

这道题我们可以冷静从$\frac{[a,b]}{a}$这个条件入手


由于我们知道$[a,b]$ $*$ $(a,b)$ $=$ $a b$


所以我们可以推出这个式子 $[a,b]$ $=$ $\frac{ab}{(a,b)}$


我们继续带入前面的式子,就可以得到$\frac{\frac{ab}{(a,b)}}{a}$


经过约分，我们就可以得到$\frac{b}{(a,b)}$,我们就可以发现


这道题的答案其实就是$b$的因数数量


上代码$:$

```
#include<bits/stdc++.h>
using namespace std;
int main(){
	long long n,ans=1;
	scanf("%lld",&n);
	for(long long i=2;i*i<=n;i++){
		long long num=1;
		while(n%i==0){
			num++;
			n/=i;
		}
		if (num != 0)ans*=num;
	}
	if (n > 1) {
		ans *= 2;
	}
	printf("%d", ans);
}
```


---

