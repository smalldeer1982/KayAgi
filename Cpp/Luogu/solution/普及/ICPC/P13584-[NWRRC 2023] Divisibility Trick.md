# [NWRRC 2023] Divisibility Trick

## 题目描述

Dmitry 最近学会了一个简单的规则来判断一个整数是否能被 $3$ 整除。一个整数如果各位数字之和能被 $3$ 整除，那么它就能被 $3$ 整除。

后来他还了解到，同样的规则也可以用来判断一个整数是否能被 $9$ 整除。一个整数如果各位数字之和能被 $9$ 整除，那么它就能被 $9$ 整除。

Dmitry 的姐姐 Daria 想要捉弄他，想证明这个规则对任意除数 $d$ 都适用。为此，她想给 Dmitry 举一个正整数 $n$ 的例子，使得 $n$ 能被 $d$ 整除，并且 $n$ 的各位数字之和也能被 $d$ 整除。请你帮她找到这样一个数。

## 说明/提示

在第一个样例中，$3$ 能被 $3$ 整除，且其各位数字之和 $3$ 也能被 $3$ 整除。

在第二个样例中，$1898$ 能被 $13$ 整除，且其各位数字之和 $1 + 8 + 9 + 8 = 26$ 也能被 $13$ 整除。

在第三个样例中，任意正整数都满足条件。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3```

### 输出

```
3```

## 样例 #2

### 输入

```
13```

### 输出

```
1898```

## 样例 #3

### 输入

```
1```

### 输出

```
239```

# 题解

## 作者：Stars_visitor_tyw (赞：3)

## 题解：P13584 [NWRRC 2023] Divisibility Trick
### 分析
首先，题目中说 $n$ 的位数不超过 $10^6$，所以 $n$ 可能很大，排除枚举做法。

考虑构造。因为 $n$ 的各位数字之和 是 $d$ 的倍数，所以我们考虑构造 $d$ 个 $d$ 拼在一起，我们记 $d$ 的各位数字之和为 $k$，那么此时 $n$ 的各位数字之和即为 $d \times k$，满足条件。此时我们看第二个条件，列一下除法竖式即可发现，此时 $n$ 可以被 $d$ 整除并且 $\frac{n}{d}$ 是一个形如 $10101$ 的数。

因此，输出 $d$ 个 $d$ 拼在一起即为答案。

### 代码
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int d;
signed main()
{
    cin>>d;
    for(int i=1;i<=d;i++)cout<<d;
}
```

---

## 作者：InterN_NOT_FOUND (赞：2)

## 题意简述
给定一个正整数 $d$，构造一个正整数 $n$，要求 $n$ 和 $n$ 的数位之和均能被 $d$ 整除。$n$ 的位数不超过 $10^6$。

## 题目解法
由于 $n$ 可能很大，直接枚举 $d$ 的倍数不可取。

考虑其它的构造方法。不难想到这样一种构造方式：将若干个 $d$ 直接首尾相接拼起来。不难发现这样得出的正整数一定是 $d$ 的倍数。对于数位之和能被 $d$ 整除的要求，我们可以将 $d$ 个 $d$ 首尾相接拼起来，使得数位之和也是 $d$ 的倍数。

当 $d=1000$ 时，构造出的 $n$ 位数最大为 $1000 \times 4=4000$ 位，符合题目要求。

时间复杂度 $O(d)$。

代码：
```cpp
#include<bits/stdc++.h>

int d;

signed main()
{
	scanf("%d", &d);
	
	for (int i = 1; i <= d; ++i)
		printf("%d", d);
	
	return 0;
}


```

---

## 作者：CaYi (赞：1)

### 题目要求
构造一个数，使得各数位之和与这个数本身能被 $d$ 整除。

### 解析

神秘构造题。

设 $d$ 的数位长度为 $l$ ，比较显然的，$d \mid d \times 10^k$ ，所以可以构造由 $d$ 个 $d$ 拼起来的一个数 :

$$\overline{dd \dots dd}= d + d\times10^l + d\times10^{2l}+\dots+d\times10^{(d - 1)l}$$ 

这个数能被 $d$ 整除，并且此时无论 $d$ 的各数位之和为多少，假设为 $k$ ，我们构造出来的数个各数位和则为 $k \times d$，被 $d$ 整除，满足题目要求。所以直接输出 $d$ 个 $d$ 即可。

### Code Time

```cpp
/*
code by : CaYi
*/
#include <bits/stdc++.h>

using i64 = long long;
using u64 = unsigned long long;
//using i128 = __int128;

int main() {
	std::cin.tie(nullptr) -> sync_with_stdio(false);
	
	int d;
	std::cin >> d;
	for (int i = 1; i <= d; i++) {
		std::cout << d;
	}
	
	return 0;
}
```

---

## 作者：_Hzq_ (赞：1)

## 题解：P13584 \[NWRRC 2023] Divisibility Trick

### 题意分析

题目要求构造一个 $d$ 的倍数，要求该数的各位数字之和也为 $d$ 的倍数。

### 具体做法

刚开始，我们可能想到枚举 $d$ 的倍数，但这种做法显然会 TLE，因为 $n$ 的位数 $\leq10^6$，即 $n\leq10^{10^6}$。\
那我们如何去构造这个数呢？难点在于如何使各位数字之和为 $d$ 的倍数，可以把这个和表示为 $a \times d$，那 $a$ 即为 $d$ 的各位数字之和，$d$ 便要是 $d$ 出现的次数了。那这个数是否能被 $d$ 整除呢？可以发现 $d^x+d^{x-1}+···+d^1 \bmod d$ 是必然的为零的，所以，直接输出 $d$ 个 $d$ 便可。

### Code

```cpp line-numbers
#include<bits/stdc++.h>
using namespace std;
int d;
int main()
{
	cin >> d;
	for(int i=1;i<=d;i++) printf("%d",d);
	printf("\n");
	return 0;
}
```

---

## 作者：zhanlinchuan (赞：1)

# 题解
[P13584](https://www.luogu.com.cn/problem/P13584)
## 题意
输入一个正整数 $d$ 构造一个正整数 $n$ 使得 $n$ 是 $d$ 的倍数且 $n$ 的各数位之和也是 $d$ 的倍数。
## 思路
若干个 $d$ 首尾相连所得得数肯定是 $d$ 的倍数。如果要让各数位和也是 $d$ 的倍数，我们只需要让 $d$ 个 $d$ 首尾相连就可以。时间复杂度为 $O(d)$ 不会超时。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int d;
    cin>>d;
    for(int i=1;i<=d;i++) cout<<d;
    return 0;
}

```

---

## 作者：Forge_Unique (赞：1)

## 代码

答案就是 $d$ 个 $d$ 拼接起来。

## 证明

我们设一个整数 $x$ 表示 $d$ 的各个位数上的数字和，则答案的各个位数上的数字和就是 $x \times d$，而 $x \times d \bmod d = 0$。

我们令 $y$ 为 $d$ 的位数，则答案为 $d \times 10^0 + d \times 10^d + d \times 10^{2d} + \cdots + d \times 10^{(d - 1) \times d}$。所以它也是 $d$ 的倍数。

得证，答案就是 $d$ 个 $d$ 拼接起来。由于 $d \le 1000$ 所以答案也一定 $\le 10^6$。

---

## 作者：guoshengyu1231 (赞：1)

# 解题思路
题目要求给定一个正整数 $d$，要我们构造出一个**正**整数 $n$，使得 $d\mid n$，并且设 $sum$ 为 $n$ 的各个数位的数字之和，还得让 $d\mid sum$。既然我们的目标是构造出这个正整数 $n$。那我们不妨先考虑什么样的 $n$ **一定**可以满足条件。因为这一点还是比较难想的，所以这里我直接说结论了，对于任意一个正整数 $A$，将他重复若干遍得到的数 $\overline{AA\dots A}$，这个数一定能被 $A$ 整除。得到的商一定是由 $1$ 和若干个 $0$ 循环往复若干次得到的数。例如 $13$ 重复 $3$ 遍，得到的数为 $131313$，那他们的商就是 $10101$。所以这些思路就有了，我们将 $d$ 重复若干遍，直到他的各个数位的数字之和能被 $d$ 整除，最终的数就是答案。$\\$
虽然很难想，但是想到结论了那这题就基本做完了，代码也是出奇的短。
# 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int d,s,sum;
//s:d的数位之和，sum:记录新数的数位之和
int main()
{
    cin>>d;
    string t=to_string(d);//将d转成字符串
    for(char x:t) s+=x-'0';//计算s
    cout<<t;sum=s;//由于说是要正整数，所以最少要输出一个t
    while(sum%d)
     {
        cout<<t;
        sum+=s;//累加数位之和
     }
    return 0;
}
```

---

## 作者：lovely_firefly (赞：0)

~~这道题有黄吗~~

首先我们要使 $n$ 是 $d$ 的倍数，显然就可以让 $n$ 为若干个 $d$ 相连，显然此时 $n$ 可以表示为若干个 $d \times 10^k$ 之和，一定为 $d$ 的倍数。而对于 $n$ 各位数字之和要是 $d$ 的倍数，显然可以让 $d$ 个 $d$ 相连，可以证明一定满足条件。

所以代码就出来了：
```cpp
#include <iostream>
using namespace std;
int main()
{
    int n;cin>>n;
    for (int i=1;i<=n;++i)
        cout<<n;
    return 0;
}
```

---

## 作者：Genshin_ht (赞：0)

## 题意

给你一个 $n$，求一个数字 $x$，$x$ 的所有数位和是 $n$ 的倍数且 $x$ 是 $n$ 的倍数。

## Solution

诈骗。

很显然，$n$ 个 $n$ 组成的数字一定可以被 $n$ 整除，并且 $n$ 个 $n$ 组成的数字的数位和一定可以被 $n$ 整除。

$n\le 1000$，把 $n$ 个长度为 $\text{len}(n)$ 的数合起来，构造出来的数字长度是 $n\times \text{len}(n)$，可以过题目中答案不超过 $10^6$ 位的限制。

```
#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    for(int i = 1;i <= n;i++) cout << n;
    cout << endl;
}
```

---

## 作者：AnOIer (赞：0)

诈骗题。

看上去无从下手，实际上我们考虑一种构造方式使得 $n$ 始终能被 $d$ 整除，$n$ 各位数字之和也始终能被 $d$ 整除且具有一般性。

不难想到使 $\frac{n}{d}=101010\cdots$，令 $k$ 为商的 $10$ 循环次数，$s$ 为 $d$ 各位数字之和，这样 $n$ 各位数字之和即为 $k\times s$。

要使 $n$ 各位数字之和能被 $d$ 整除，最简单的方法就是使上文的 $k=d$，这样 $n$ 各位数字之和为 $d\times s$，一定能被 $d$ 整除。

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int d;
	cin>>d;
	for(int i=1;i<=d;i++) cout<<d;
	return 0;
}
```

---

## 作者：_aszxqw_ (赞：0)

~~这是我见过最水的黄题了~~    
直接输出 $d$ 个 $d$ 就可以了。    
举个例子：   
$d=5$ 时 输出的就是 $5\times 5$，$25$ 可以整除 $5$。  
那为什么 $d$ 个 $d$ 能整除 $d$ 呢，因为 $d$ 个 $d$ 就等于 $d\times$ $d$ 个 $1$ 组成的数字，而这个数字是可以被 $d$ 整除的，所以直接输出 $d$ 个 $d$ 就可以了。    
代码太简单了，就不放了。

---

## 作者：copper_ingot (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/P13584)

神秘构造题。

对于正整数 $d$，若干个 $d$ 拼起来的数 $\overline{ddd\dots}$ 是可以被 $d$ 整除的。

记 $d$ 的数位和为 $sum$，$d$ 个 $d$ 拼起来的数的数位和则为 $sum \times d$，可以被 $d$ 整除。

所以输出 $d$ 个 $d$ 即可。当 $d=1000$ 时输出的数仅有 $4000$ 位，符合限制。

---

## 作者：GuoMingXuants1 (赞：0)

### 思路

这题真有股诈骗人的感觉。

先放结论：直接输出 $d$ 个 $d$ 就行。

证明其实很简单：题目中说，如果有多个解，输出任意一个即可。对于 $d$ 个 $d$ 拼接的数，各位数字之和其实就是 $d$ 和单个 $d$ 本身的各位数字之和两者的乘积，那不就是能被 $d$ 整除吗？还有，$d$ 个 $d$ 拼接成的数能不能被 $d$ 整除？答案是肯定的，假定单个 $d$ 的数字位数是 $c$，我们把这个数还可以表示成这样：

$$
\sum_{i = 0}^{d - 1} 10^{i \times c} \times d
$$

发现没有？这个公式中，相加的每一项都含有 $d$，并且，还能保证 $10^{i \times c}$ 一定是正整数，将这个由 $d$ 个 $d$ 拼接的数提取因数，那么就一定含有因数 $d$，换而言之，就是能被 $d$ 整除。

### 代码
```cpp
#include<iostream>
using namespace std;
int main()
{
    int d;
    cin>>d;
    for(int i=1;i<=d;i++)
    {
        cout<<d;
    }
}
```

---

## 作者：Zayn_Pan (赞：0)

## 题目

输入一个正整数 $d$，$d$ 不超过 $1000$，找到一个位数少于 $10^6$，不含前导 $0$ 的正整数 $n$ 使得 $n$ 是 $d$ 的倍数，且 $n$ 的各位数字的和也是 $d$ 的倍数。

## 思路

~~这题似乎不需要什么思路~~

很容易想到，只需要输出 $d$ 个 $d$ 就行了。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int d;
    cin>>d;
    for(int i=1;i<=d;i++)cout<<d;
    return 0;
}
```

---

