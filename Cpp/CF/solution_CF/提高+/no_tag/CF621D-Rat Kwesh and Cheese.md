# Rat Kwesh and Cheese

## 题目描述

Wet Shark asked Rat Kwesh to generate three positive real numbers $ x $ , $ y $ and $ z $ , from $ 0.1 $ to $ 200.0 $ , inclusive. Wet Krash wants to impress Wet Shark, so all generated numbers will have exactly one digit after the decimal point.

Wet Shark knows Rat Kwesh will want a lot of cheese. So he will give the Rat an opportunity to earn a lot of cheese. He will hand the three numbers $ x $ , $ y $ and $ z $ to Rat Kwesh, and Rat Kwesh will pick one of the these twelve options:

1. $a_1=x^{y^z}$；
2. $a_2=x^{z^y}$；
3. $a_3=(x^y)^z$；
4. $a_4=(x^z)^y$；
5. $a_5=y^{x^z}$；
6. $a_6=y^{z^x}$；
7. $a_7=(y^x)^z$；
8. $a_8=(y^z)^x$；
9. $a_9=z^{x^y}$；
10. $a_{10}=z^{y^x}$；
11. $a_{11}=(z^x)^y$；
12. $a_{12}=(z^y)^x$。

Let $ m $ be the maximum of all the $ a_{i} $ , and $ c $ be the smallest index (from $ 1 $ to $ 12 $ ) such that $ a_{c}=m $ . Rat's goal is to find that $ c $ , and he asks you to help him. Rat Kwesh wants to see how much cheese he gets, so he you will have to print the expression corresponding to that $ a_{c} $ .

## 样例 #1

### 输入

```
1.1 3.4 2.5
```

### 输出

```
z^y^x
```

## 样例 #2

### 输入

```
2.0 2.0 2.0
```

### 输出

```
x^y^z
```

## 样例 #3

### 输入

```
1.9 1.8 1.7
```

### 输出

```
(x^y)^z
```

# 题解

## 作者：xukehg (赞：0)

还算简单。

首先如此大数肯定无法直接计算，考虑对每种情况套一个 $\log$ 函数，比对 $\log$ 过的值。

由高中函数知识得：$\log(x^y) = y\log(x)$，于是 $12$ 种情况分别为：

1，形如 $x^{y^z}$ 及其轮换，则答案为 $\log(x ^ {y ^ z}) = y ^ z\log(x)$，虽然 $y ^ z$ 仍然很大，但可以使用双精度浮点数存储。

2，形如 $(x ^ y) ^ z$ 及其轮换，则答案为 $\log((x ^ y) ^ z) = z\log(x ^ y) = zy\log(x)$。

综上，我就可以进行比对了。

[记录](https://codeforces.com/contest/621/submission/288883635)：

```cpp
#include <bits/stdc++.h>
#define ld long double
using namespace std;

ld x,y,z;
signed main(){
//  freopen(".in","r",stdin);
//  freopen(".out","w",stdout);
	ios::sync_with_stdio(false);
	cin.tie(0),cout.tie(0);
	cin >> x >> y >> z;
	ld ans1 = powl(y,z) * logl(x),ans2 = powl(z,y) * logl(x),ans3 = powl(x,z) * logl(y),ans4 = powl(z,x) * logl(y),ans5 = powl(x,y) * logl(z),ans6 = powl(y,x) * logl(z);
	ld ans7 = y * z * logl(x),ans8 = x * y * logl(z),ans9 = x * z * logl(y),anss = max({ans1,ans2,ans3,ans4,ans5,ans6,ans7,ans8,ans9});
	if (anss == ans1){cout << "x^y^z";return 0;}
	if (anss == ans2){cout << "x^z^y";return 0;}
	if (anss == ans3){cout << "y^x^z";return 0;}
	if (anss == ans4){cout << "y^z^x";return 0;}
	if (anss == ans5){cout << "z^x^y";return 0;}
	if (anss == ans6){cout << "z^y^x";return 0;}
	if (anss == ans7){cout << "(x^y)^z";return 0;}
	if (anss == ans9){cout << "(y^x)^z";return 0;}
	if (anss == ans8){cout << "(z^x)^y";return 0;}
}
```

---

## 作者：1234567890sjx (赞：0)

$2400$？哈哈哈，虚高。

指数直接计算值过大。因为只需要知道相对的大小关系因此考虑经典套路将指数映射为另一个单调递增且值互不相同的函数。这里选取 $\log$ 函数是因为其有一些优美的性质。

根据高中数学必修一可知，$\log(x^{y^z})=y^z\log(x)$，$\log((x^y)^z)=z\log(x^y)=yz\log(x)$。此时数据最大为 $200^{200}\log(200)$。本来考虑做二次 $\log$ 但是此时值可能小于等于 $0$ 使得 $\log$ 无意义。因此使用 `long double`，可以存储下这么大的数。此时直接比较所有数的大小即可。然后就是我的写法可能需要注意一下精度的问题。

下面给出指数求 $\log$ 部分的核心代码：

```cpp
//x^y^z
long double calc(long double x,long double y,long double z){
    return powl(y,z)*logl(x);
}
//(x^y)^z
long double lc(long double x,long double y,long double z){
    return logl(x)*y*z;
}

---

