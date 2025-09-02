# Dreamoon and Sums

## 题目描述

Dreamoon loves summing up something for no reason. One day he obtains two integers $ a $ and $ b $ occasionally. He wants to calculate the sum of all nice integers. Positive integer $ x $ is called nice if ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF476C/4c08c1c4aa605a7661ec02846fcac8a50385ec4f.png) and ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF476C/199c47ec051f565599e933f0f95a0d9069b4a2ef.png), where $ k $ is some integer number in range $ \[1,a\] $ .

By ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF476C/f26b8897bea7b2ad070a91154fff6b5d3d6ecc9d.png) we denote the quotient of integer division of $ x $ and $ y $ . By ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF476C/e60b09b62a19a62f637ba6a66556f554bcb4dbf9.png) we denote the remainder of integer division of $ x $ and $ y $ . You can read more about these operations here: http://goo.gl/AcsXhT.

The answer may be large, so please print its remainder modulo $ 1000000007 $ ( $ 10^{9}+7 $ ). Can you compute it faster than Dreamoon?

## 说明/提示

For the first sample, there are no nice integers because ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF476C/05cf42fbd3551fd38e1ab2adca655a95016ccd28.png) is always zero.

For the second sample, the set of nice integers is $ {3,5} $ .

## 样例 #1

### 输入

```
1 1
```

### 输出

```
0
```

## 样例 #2

### 输入

```
2 2
```

### 输出

```
8
```

# 题解

## 作者：czh___ (赞：4)

题意：
给定两个数值 $a$，$b$。现在有一个 $x$ 满足 $x$ 与 $b$ 的商除以 $x$ 与 $b$ 的余数得到的数值记为 $k$，$k$ 要求在 $1$ 到 $a$ 之间（包括 $1$ 和 $a$）现在要求你求出所有的 $x$ 的和，并且结果和 $1000000007$ 取余。

题解：
这道题目，逆向思维思考一下，反着来求出所有的 $x$，即通过遍历所有的 $a$ 和 $b$ 求出所有的 $x$：


```cpp
for(int i=1;i<b;i++){
    for(int j=1;j<=a;j++){
        long long res=i*j*b+i;
        sum+=res;
        sum=sum%1000000007;
    }
}
```

但是光是这样，那肯定会超时的。所以我们可以通过提取公因式，这里可以提出 $i$，利用等差数列求和即可。
但是这里要注意数据范围，$a^3$ 的范围大约是 $10^{21}$，超过了 long long 的范围。

代码：

```cpp
#include<bits/stdc++.h>
#define int long long
#define mod 1000000007
using namespace std;
int ans,a,b;
signed main(){
   	ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
   	cin>>a>>b;
   	int m=b*(b-1)/2%mod;
   	for(int i=1;i<=a;i++){
		int temp=(i*b+1)%mod;
		ans=(ans+m*temp%mod)%mod;
	}
   	cout<<ans;
   	return 0;
}
```

拜拜！

---

## 作者：ZJle (赞：1)

令 $d=\lfloor x/b\rfloor,m=x\mod b$,



因为 $\frac{\lfloor x/b\rfloor}{x\mod b}=k$,所以 $d=mk$,

由带余除法，我们有 $x=db+m$

即 $x=mkb+ m=(kb+1) \times m$

我们知道余数的范围是 $[1, b-1]$,

那么我们要求的和式即为 $\sum^{a}_{k=1}((kb+1) \frac {b(b-1)}{2})$,我们可以 $O(a)$ 求出它，

当然也可以把它进一步化简为 $(\frac{a(a+1)}{2}b+a)\frac{b(b-1)}{2}$ 。

## 码

```cpp
#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
void file(){
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	#ifndef ONLINE_JUDGE
		freopen("1.in","r",stdin);
		freopen("1.out","w",stdout);
	#endif
}
auto main()->signed
{
	file();

	int a, b;
	while (cin>>a>>b)
	{
		int x = ((long long)b * (b - 1) / 2) % mod;
		int y = ((long long)a * (a + 1) / 2) % mod;
		y = ((long long)y * b + a) % mod;
		x = (long long)x * y % mod;
		cout<<x<<'\n';
	}
	return 0;
}
```


---

## 作者：_Kimi_ (赞：0)

# CF476C题解

### 前言

一开始我看洛谷翻译没看懂，自己扔到百度翻译才看懂。

### 题意

给定 $a,b$，求所有好数字的和。

对于好数字的定义：记 $\frac{x \div b}{x \bmod b}$ 为 $k$，如果 $k\ge1$ 且 $k\le a$，则 $x$ 为好数字。

答案对 $10^9+7$ 取模。

### 思路

简单数学题。
原式：

$$\frac{x\div b}{x \bmod b}=k$$

将分母移过去，得：

$$x=(x \bmod b)\times k\times b + (x \bmod b)$$

提取公因子，得：

$$x=(x \bmod b)\times(k\times b+1)$$

合法的 $x \bmod b$ 取值范围为 $\left[1,b-1\right]$，可以预处理成所有余数和，记余数和为 $sum$。

$$sum=\sum_{i=1}^{b-1}i$$

可以用等差数列来优化，首项为 $1$，末项为 $b-1$，项数为 $b-1$，即：

$$sum=(b-1+1)\times(b-1)\div2=b \times(b-1)\div2$$

式子中现在只有一个未知数 $k$ 了，枚举 $k$，再根据式子累加答案即可。

### 代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define WA AC
using namespace std;
const int mod = 1e9 + 7;
int a, b, sum, ans, x;
void input(){
    ios::sync_with_stdio(0);
	cin.tie(0);
	//freopen(".in", "r", stdin);
	//freopen(".out", "w", stdout);
	cin >> a >> b;
	sum = (b * (b - 1) / 2) % mod;
}
signed main(){
	input();
	for(int k = 1; k <= a; k++){
		x = (sum * ((k * b + 1) % mod)) % mod;
		ans += x;
		ans %= mod;
	}
	cout << ans << endl;
	return 0;
}
```

---

## 作者：冯老师 (赞：0)

**[洛谷](https://www.luogu.com.cn/problem/CF476C) [CF](https://codeforces.com/problemset/problem/476/C)**

> - 给出 $a,b$，求：
>
>     $$\left[\sum\limits_{x=1}^\infty \left(x\cdot \left[  1\le \dfrac{\lfloor\frac{x}{b}\rfloor}{x\bmod b}  \le a    \right]\right)\right]\bmod 10^9 + 7$$
>
> - $a,b\le 10^7$。

考虑枚举 $x\bmod b$，记为 $r$。则 $x = k\cdot b\cdot r+r$，其中 $1\le k\le a$，问题转化为求 $\sum\limits_{i=1}^a (i\cdot b\cdot r+r)$，运用等差数列求和可以得到这个式子就等于 $\dfrac{a\cdot (a+1)\cdot b\cdot r}{2}+ar$。

时间复杂度为 $\mathcal{O}(b)$，空间复杂度为 $\mathcal{O}(1)$。

**[提交记录（含代码）](https://codeforces.com/contest/476/submission/230922675)**

---

