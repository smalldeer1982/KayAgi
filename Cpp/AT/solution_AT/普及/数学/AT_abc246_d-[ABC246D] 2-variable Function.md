# [ABC246D] 2-variable Function

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc246/tasks/abc246_d

整数 $ N $ が与えられるので、以下の条件を全て満たす最小の整数 $ X $ を求めてください。

- $ X $ は $ N $ 以上である。
- 非負整数 $ (a,b) $ の組であって、 $ X=a^3+a^2b+ab^2+b^3 $ を満たすようなものが存在する。

## 说明/提示

### 制約

- $ N $ は整数
- $ 0\ \le\ N\ \le\ 10^{18} $

### Sample Explanation 1

$ 9\ \le\ X\ \le\ 14 $ であるようなどの整数 $ X $ についても、問題文中の条件を満たすような $ (a,b) $ は存在しません。 $ X=15 $ は $ (a,b)=(2,1) $ とすると問題文中の条件を満たします。

### Sample Explanation 2

$ N $ 自身が条件を満たすこともあります。

### Sample Explanation 3

入出力が $ 32 $bit 整数型に収まらない場合があります。

## 样例 #1

### 输入

```
9```

### 输出

```
15```

## 样例 #2

### 输入

```
0```

### 输出

```
0```

## 样例 #3

### 输入

```
999999999989449206```

### 输出

```
1000000000000000000```

# 题解

## 作者：So_noSlack (赞：10)

[洛谷链接](https://www.luogu.com.cn/problem/AT_abc246_d)&[Atcoder 链接](https://atcoder.jp/contests/abc246/tasks/abc246_d)

本篇题解为此题较**简单做法**及**较少码量**，并且码风优良，请放心阅读。

## 题目简述

给定整数 $N$，请你找到最小的整数 $X$，满足：

- $X \ge N$。
- 存在一对非负整数 $(a,b)$，使得 $X = a^3 + a^2b + ab^2 + b^3$。

## 思路

首先可进行优化 $a^3 + a^2b + ab^2 + b^3$ 这一部分为 $(a^2 + b^2) \times (a + b)$。

证明如下：

$$a^3 + a^2b + ab^2 + b^3$$

提取公因数 $a^2$：

$$=a^2 \times (a + b) + ab^2 + b^3$$

提取公因数 $b^2$：

$$=a^2 \times (a + b) + b^2 \times (a + b)$$

提取公因式 $a + b$：

$$=(a^2 + b^2) \times (a + b)$$

接着因为 $a$，$b$ **并无实质性差异**，故可以假设 $a \le b$ 去用**双指针**确定 $X$ 的值。

可写一个 $\operatorname{check}(x,y)$ 函数返回传入的 $x$，$y$ 的值，判断 $\operatorname{check}(x,y)$ 是否 $ \ge N$，如 $\ge N$，**移动右区间并对答案取最小值**，否则**移动左区间**即可。

**注意**：$ans$ 初始化**需初始化为一个较大值**。

经过以上**分析及小优化**，很容易即可写出**代码**：

```cpp
#include<iostream>
#include<cmath>
using namespace std;

long long n, x, l = 0, r = 1e6 + 1, ans = 0x3f3f3f3f3f3f3f3f; // ans 初始化为 long long 最大值

long long check(long long x, long long y) {
    return (long long)(pow(x, 2) + pow(y, 2)) * (x + y); // 小优化
}

int main() {
    cin >> n; // 输入
    // 双指针枚举
    while(l <= r) {
        if(check(l, r) < n) l ++; // 移动左区间
        else {
            ans = min(ans, check(l, r)); // 更新答案
            r --; // 移动右区间
        }
    }
    cout << ans << endl; // 输出答案，换行好习惯
    return 0;
}
```

[提交记录](https://www.luogu.com.cn/record/117197589)

$$\text{The end!!}$$

---

## 作者：__HHX__ (赞：3)

# 思路（双指针）
我们先思考 $b$ 最大能取多少。

因为 $x = a^3 + a^2b + ab^2 + b^3$，故 $n \leq b^3$。

那 $b$ 取最大值便是 $x^{1 \over 3}$。

$a$ 取最小值，便是 $0$ 了。

当 $a$ 增大时数值变大，$b$ 缩小时数值缩小。

我们仅需在此情况时 $n \leq a^3 + a^2b + ab^2 + b^3$ 就取一遍最小。

最后输出最小值。

时间复杂度 $O(n)$。

弱弱的说一句 $(a^2 + b^2) \times (a + b) = a^3 + a^2b + ab^2 + b^3$，并且 $a \leq b$ 哦！
# 代码
```cpp
#include<iostream>
#include<algorithm>
 
using namespace std;
 
int main() {
	long long n, ans = 1e18 + 3;
	cin >> n;
	for(long long a = 0, b = 1e6; a <= b; a++) {
		for(; a <= b; b--) {
			if((a * a + b * b) * (a + b) < n) {
				break;
			}
			ans = min(ans, (a * a + b * b) * (a + b));
		}
	}
	cout << ans;
}
```

---

## 作者：Molina (赞：1)

# 本题大意
给你整数 $ N $，请你找到一个最小的整数 $ X $，满足：

- $ X \ge N $。
- 存在一对非负整数（$ a $，$ b $），使得 $ X=a^3+a^2b+ab^2+b^3 $。

题目链接：[luogu](https://www.luogu.com.cn/problem/AT_abc246_d) && [atcoder](https://atcoder.jp/contests/abc246/tasks/abc246_d)
# 本题思路：
先定义一个函数，返回 $ a^3+a^2b+ab^2+b^3 $ 的值。

然后从两边开始枚举，可以得到：答案的值一定小于 $ 10^6 $。

如果找到的答案小于 $ N $，则将 $ a $ 加一，找更大的值。如果符合条件，则先将较小的答案存进 $ ans $ 里面，再将 $ b $ 减一，找更小的值。最后输出答案即可。（详细讲解见代码）

注意：本题数据范围，$ N $ 小于十的十八次方。
# 代码来咯~

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,ans=1e18;//开long long
long long cz(long long a, long long b){
	return a*a*a+a*a*b+a*b*b+b*b*b;
}//函数返回值
int main(){
	cin>>n;
	long long a=0,b=1e6+1;
	while(a<=1e6+1  &&  b>=0)//从两边开始枚举
		if(cz(a,b)<n)  a++;//不符合则i++
		else{
			ans=min(ans,cz(a,b));
			b--;
		}//找最小值
	cout<<ans<<endl;
	return 0;
}
```

---

## 作者：zhanghaosong (赞：1)

# AT_abc246_d [ABC246D] 2-variable Function 题解

### 思路

1. 这道题数据范围非常大，$10^{18}$ 量级的，明显不能暴力枚举！

2. 这道题可以用**双指针**的方法去做。

### 解析

对于 $a^3 + a^2b + ab^2 + b^3$，可以对其进行如下变换：

$a^3 + a^2b + ab^2 + b^3$

$=(a^3 + a^2b) + (ab^2 + b^3)$

$=a^2(a+b)+b^2(a+b)$

$=(a^2+b^2)(a+b)$

然后我们设置两个指针 $l$ 和 $r$，分别代表 $a$ 和 $b$。由于原式中 $a$ 和 $b$ 对称，所以**不妨**设 $a\leq b$。易知 $a$ 可以取到 $0$（不保证 $b$ 取整数），$b$ 可以取到 $\sqrt[3]{N}+1 $，或 `ceil(cbrt(n))`。然后我们用类似二分的方法求出答案即可！

### 代码

不贴代码了（逃哇）

---

## 作者：minVan (赞：1)

**题目大意**

给定整数 $N$，请你找到最小的整数 $X$，满足：

- $X \ge N$
- 存在一对非负整数 $(a, b)$，使得 $X = a^3 + a^2b + ab^2 + b^3$。

**解题思路**

令 $f(a, b) = a^3 + a^2b + ab^2 + b^3$。

枚举 $a$ 和 $b$，$a$ 从 $0$ 到 $10^6$ 枚举，$b$ 从 $10^6$ 到 $0$ 枚举，如果 $f(a, b) < n$，那么 $a + 1$，否则取最小值并 $b - 1$。

**AC 代码，请勿抄袭**

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n, ans = LLONG_MAX;
long long F(long long a, long long b)
{
	return a * a * a + a * a * b + a * b * b + b * b * b;
}
int main()
{
	cin >> n;
	for(long long a = 0, b = 1000000; a <= 1000000 && b >= 0; )
	{
		if(F(a, b) < n)
			a++;
		else
		{
			ans = min(ans, F(a, b));
			b--;
		}
	}
	cout << ans;
	return 0;
}
```

---

## 作者：Kobe_BeanBryant (赞：1)

### 题目大意：
给定整数 $ N $，请你找到最小的整数 $ X $。
### 要求:
1. $ X $ 小于等于 $ N $。
2. 有一对非负整数 $ a $ 与 $ b $，让 $ X $ 等于 $ a^3+a^3b+ab^2+b^3 $。

### 思路：
1. 从两边枚举，得到的答案一定会小于 $ 10^6 $。
2. 若答案不符合要求一，则找更大的答案。
3. 若答案符合要求一，就先把较小的存起来，再找更小的值。
4. 输出最小值。

### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a=0,b=1e6,m=1e18,x=0;
int main(){
	cin>>n;
	while(a<=b){
		x=a*a*a+a*a*b+a*b*b+b*b*b;
		if(x>=n)b--;
		else a++;
		if(x>=n && x<m) m=min(x,m);
	}
	cout<<m;
	return 0;
}
```

---

## 作者：asas111 (赞：0)

## 思路

先对题目式子进行因式分解：

$a^3+a^2b+ab^2+b^3$

将它分成 $2$ 组。

$=(a^3+a^2b)+(ab^2+b^3)$

分别对每一组提取公因式。

$=a^2(a+b)+b^2(a+b)$

将两组合并同类项。

$=(a^2+b^2)(a+b)$

根据数据范围 $0\le N\le10^{18}$，所以 $a,b\le10^6$。

暴力枚举 $a$ 和 $b$ 的时间复杂度为 $O(n^2)$，显然会超时。

考虑只枚举 $a$，对 $b$ 进行二分。时间复杂度 $O(n\log n)$，可以通过此题。

## 代码
```cpp
#include<bits/stdc++.h>
#define ll long long
using namespace std;
int main(){
	ll n,a=1e18;
	cin>>n;
	for(ll i=0;i<=1000000;i++){
		ll l=0,r=1000000,ans=0;
		while(l<=r){
			ll mid=l+(r-l)/2,u=(i*i+mid*mid)*(i+mid);//对题目式子的因式分解
			if(u>=n)ans=u,r=mid-1;
			else l=mid+1;
		}
		a=min(a,ans);
	}
	cout<<a;
	return 0;
}

```


---

## 作者：zk_y (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc246_d)

我们先来看一下这道题目，这道题目需要我们判断两件事情：

> 首先，需要判断 $X$ 是否大于 $N$。
> 
> 然后，我们要判断 $X$ 能否写成例如 $a^3 + a^2b + ab^2 + b^3$ 的形式。

那么，我们来先对这个式子进行一下分析：

我们可以看出来这个式子是一个对称式，那我们不妨设 $a\le b$。

现在让我们来求 $b$ 的最大值，因为 $a\le b$，要使 $b$ 最大，我们必须要让 $a$ 最小，那么 $a$ 最小是几呢？肯定是 $0$。

那么对于 $b$ 就有 $b^3\le N$，所以 $b$ 就可以设置成 $\sqrt[3]{N}+1$。注意：这里必须加上 $1$。（精度误差害死人啊）

要计算 $\sqrt[3]{N}+1$ 方法还是比较多的，比如 ``cbrt`` 函数，``pow`` 函数等。这里我使用 ``pow`` 函数。（注意一下这里的指数写法）

# AC代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a=0,b,minn=1e25,ans;
int main(){
	scanf("%lld",&n);
	b=pow(n,1.0/3.0)+1;
	while(a<=b){
		ans= a*a*a + a*a*b + a*b*b + b*b*b;
		if(ans>=n){
			if(ans<minn)minn=ans;
			b--;
		}
		else a++;
	}
	printf("%lld\n",minn);
	return 0;
}
```


---

## 作者：Neilchenyinuo (赞：0)

## 题目大意
给定整数 $N$，请你找到最小的整数 $X$，满足：

- $X \ge N$。
- 存在一对非负整数 $(a, b)$，使得 $X = a^3 + a^2b + ab^2 + b^3$。

## Solution

1. 因为 $x=a^3 + a^2b + ab^2 + b^3$，所以 $n \leq b^3$。

2. 所以 $b$ 最大可取 $x^{\frac{1}{3}}$，也就是 $10^6$，$a$ 最小便是 $0$ 了。

3. 定义 $f(a,b)$ 这个函数，来计算 $a^3+a^2b+ab^2+b^3$ 的值。

4. 暴力枚举 $a$ 至 $b$ 的范围，即 $0$ 至 $10^6$，若 $f(a,b)<n$，那么 $a \gets a+1$。反之，取最小值并 $b \gets b-1$。

5. 浅浅提一句，时间复杂度 $O(n)$。

## 坑点

看这：$ 0\ \le\ N\ \le\ 10^{18} $。

## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long 
int n;
int f(int a,int b)
{
	return a*a*a+a*a*b+a*b*b+b*b*b;
}
signed main()
{
	cin>>n;
	int mini=1e18;
	for(int a=0,b=1e6;a<=1e6,b>=0;)
	{
		if(f(a,b)<n)
			a++;
		else
		{
			mini=min(mini,f(a,b));
			b--;
		}
	}
	cout<<mini;
	return 0;
}
```

---

## 作者：Tsawke (赞：0)

# [ABC246D 2-variable Function](https://www.luogu.com.cn/problem/AT_abc246_d) Solution

[TOC]

## [更好的阅读体验戳此进入](http://blog.monkey-hyx.tech?t=ABC246D)

## 题面

存在函数 $ f(a, b) = a^3 + a^2b + ab^2 + b^3 $，要求 $ a, b \ge 0 $，给定 $ n $，求最小的 $ f(a, b) $ 满足 $ f(a, b) \ge n $。$ n \le 10^{18} $。

## Solution

显然 $ a, b $ 的范围不超过 $ 10^6 $，则可以枚举 $ a $，二分 $ b $，取最小值即可。

对于二分 $ b $ 的单调性证明，可以考虑固定 $ a $ 为参数，则有函数 $ f(b) = b^3 + ab^2 + a^2b + a^3 $，三次函数不好操作，所以考虑求导，显然 $ f'(b) = 3b^2 + 2ab + a^2 $，因为 $ a, b $ 非负，所以显然导函数 $ f'(b) \ge 0 $，所以范围内函数取值单调递增，于是可以二分。

或者不进行二分，根据单调性，显然 $ a $ 减小时 $ b $ 不会比上次更大，所以写个双指针枚举，$ a $ 升序，$ b $ 降序，小于 $ n $ 时直接 `break` 即可。

## Code

```cpp
#define _USE_MATH_DEFINES
#include <bits/extc++.h>

#define PI M_PI
#define E M_E
#define npt nullptr
#define SON i->to
#define OPNEW void* operator new(size_t)
#define ROPNEW(arr) void* Edge::operator new(size_t){static Edge* P = arr; return P++;}

using namespace std;
using namespace __gnu_pbds;

mt19937 rnd(random_device{}());
int rndd(int l, int r){return rnd() % (r - l + 1) + l;}
bool rnddd(int x){return rndd(1, 100) <= x;}

typedef unsigned int uint;
typedef unsigned long long unll;
typedef long long ll;
typedef long double ld;

template<typename T = int>
inline T read(void);

ll Func(int a, int b){return (ll)a * a * a + (ll)a * a * b + (ll) a * b * b + (ll)b * b * b;}
int main(){
    ll N = read<ll>();
    ll mn(LLONG_MAX);
    for(int x = 0; x <= (int)1e6; ++x){
        int l = 0, r = (int)1e6;
        ll cur(-1);
        while(l <= r){
            int mid = (l + r) >> 1;
            ll tmp = Func(x, mid);
            if(tmp >= N)cur = tmp, r = mid - 1;
            else l = mid + 1;
        }
        mn = min(mn, cur);
    }printf("%lld\n", mn);
    fprintf(stderr, "Time: %.6lf\n", (double)clock() / CLOCKS_PER_SEC);
    return 0;
}

template<typename T>
inline T read(void){
    T ret(0);
    short flag(1);
    char c = getchar();
    while(c != '-' && !isdigit(c))c = getchar();
    if(c == '-')flag = -1, c = getchar();
    while(isdigit(c)){
        ret *= 10;
        ret += int(c - '0');
        c = getchar();
    }
    ret *= flag;
    return ret;
}
```

## UPD

update-2022_10_21 初稿

---

