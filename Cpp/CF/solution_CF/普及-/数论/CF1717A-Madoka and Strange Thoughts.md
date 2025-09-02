# Madoka and Strange Thoughts

## 题目描述

给定一个整数 $n$，求出有多少组满足条件的 $\left ( a, b\right) (1 \le a, b \le n)$，使得 $\frac{\operatorname{lcm}(a, b) }{\gcd(a, b) } \le 3$。

在该题目中，$\gcd(a, b)$ 指的是 $a$ 和 $b$ 的最大公约数，而 $lcm(a, b)$ 指的是 $a$ 和 $b$ 的最小公倍数。

## 样例 #1

### 输入

```
6
1
2
3
4
5
100000000```

### 输出

```
1
4
7
10
11
266666666```

# 题解

## 作者：Andy_L (赞：12)

$\color{#E74C3C}\text{温馨提示:}$

$\color{#E74C3C}\text{遇见题解勿抄袭，棕名封号两行泪。}$

[洛谷题目传送门](https://www.luogu.com.cn/problem/CF1717A)

[CF题目传送门](https://codeforces.com/contest/1717/problem/A)

---

### 题目大意：

给定一个 $n$ ，让你求出有多少个 $a,b$ 满足 $1 \le a,b \le n $ 且 $\frac{\operatorname{lcm}(a,b)}{\gcd(a,b)} \le 3 $ 。

---

### 思路：

一眼看过去就不是暴力的题目。我们可以先找规律，既然提到了 $\gcd$ 和 $\operatorname{lcm}$ ，那么肯定和短除法有关系了。

可以从倍数关系入手，最直接得体现在底部数字（红圈的地方）的位置。

![](https://s1.ax1x.com/2022/09/03/vop0Mj.png)

我们可以发现短除法之后底部数字只可能是以下几种情况：

1. 为 `1  1` 时有 $n$ 种情况。

1. 为 `1  2` 时有 $\lfloor \frac{n}{2} \rfloor$ 种情况。

1. 为 `2  1` 有 $\lfloor \frac{n}{2} \rfloor$ 种情况。

1. 为 `1  3` 有 $\lfloor \frac{n}{3} \rfloor$ 种情况。

1. 为 `3  1` 有 $\lfloor \frac{n}{3} \rfloor$ 种情况。

为什么呢？

因为我们要求的是 $\frac{\operatorname{lcm}(a,b)}{\gcd(a,b)} \le 3 $ ，所以你最多只能是$3$ 倍关系，理由是 $\frac{\operatorname{lcm}(a,b)}{\gcd(a,b)} = $ 底部数字相乘，可以再看看上面的图片。

这样我们就知道底部数字只能是上面的 $5$ 种情况了。

当底部数字为 `1  2` 或 `2   1` 都是 $a=2b$ 或 $b=2a$ 的情况，所以有 $\lfloor \frac{n}{2} \rfloor$ 种情况。

当底部数字为 `1  3` 或 `3   1` 时同理，那么最后加起来就可以了。



---

$$\text{Coding Time}$$

```cpp
#include <bits/stdc++.h>
using namespace std;
int main()
{
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	int t;cin>>t;
	while (t--)
	{
		int n;cin>>n;
		cout<<n+(n/2)+(n/2)+(n/3)+(n/3)<<endl;//答案
	}
	return 0;
}
```

---

[AC 记录](https://www.luogu.com.cn/record/85819366)

---

## 作者：ScottSuperb (赞：10)

## 题意简述
找出有多少对**有序**数对 $(a, b)$ 存在，使 $1 \leq a, b \leq n$ 且他们的最小公倍数不大于最小公因数的 $3$ 倍，即 $\frac{\operatorname{lcm}(a, b)}{\operatorname{gcd}(a, b)} \leq 3$。
## 解法分析
签到题。让我们先回顾一下小学学的用短除法求最小公倍数和最大公因数的方法。  
![](https://cdn.luogu.com.cn/upload/image_hosting/m0h28ktt.png)  
我们知道，将左边所有数相乘就是最大公因数，再依次与下面两个数相乘就是最小公倍数。于是我们发现，最小公倍数除以最大公因数的商正是下面的两个数之积。那么就可以得出结论，满足 $\frac{\operatorname{lcm}(a, b)}{\operatorname{gcd}(a, b)} \leq 3$ 的数对 $(a, b)$ 一定是由数对 $(1, 1),(1, 2),(2, 1),(1, 3),(3, 1)$ 其中一个同乘某个数得到的，那么我们只需保证乘后得到的数对满足 $1 \leq a, b \leq n$ 即可。如何统计这样的方案数呢？显然，由 $(1, 1)$ 得到的有 $n$ 种，由 $(1, 2),(2, 1)$ 得到的有 $\left \lfloor \frac{n}{2} \right \rfloor \times 2$ 种，由 $(1, 3),(3, 1)$ 得到的有 $\left \lfloor \frac{n}{3} \right \rfloor \times 2$ 种。输出它们们的和即可。
## 代码
读写函数定义已省略
```cpp
#include <bits/stdc++.h>

using namespace std;

int main() {
	int t = read(), n;
	while (t--) {
		n = read();
		write(n + n / 2 * 2 + n / 3 * 2);
	}
	return 0;
}
```

---

## 作者：wzmzmhk (赞：4)

这里给出一种比较无脑的新做法。

前置知识：小学找规律。

-----------------

题目大意：求出有多少对 $(a, b)$ 满足 $1\le a,b\le n$ 且 $\dfrac{ \operatorname{lcm}(a, b) }{ \gcd(a, b) } \le 3$。

根据题意，不难写出 bf 做法：
```cpp
for (int i = 1;i <= n; i++)
	for (int j = 1; j <= n; j++)
		if (3 * gcd(i, j) >= i * j / gcd(i, j)) cnt++;
```        
然后拿这个打一下 $1 \sim 25$ 的表：
```
1 4 7 10 11 16 17 20 23 26 27 32 33 36 39 42 43 48 49 52 55 58 59 64 65 
```

通过找规律，我们发现这个数列是六个数一组。

设这是第 $t$ 组，那么该组的第一个数就是 $t \times 16 - 16$。对于剩下的数，有：
- 第 $2$ 个数比第 $1$ 个数大 $3$。
- 第 $3$ 个数比第 $2$ 个数大 $3$。
- 第 $4$ 个数比第 $3$ 个数大 $3$。
- 第 $5$ 个数比第 $4$ 个数大 $1$。
- 第 $6$ 个数比第 $5$ 个数大 $5$。

据此即可写出代码：
```cpp
int n; cin >> n;
int a = n / 6;
if (n % 6) a++;
int val = (a - 1) * 16 + 1;
if (n % 6 == 1) cout << val << endl;
else if (n % 6 == 2) cout << val + 3 << endl;
else if (n % 6 == 3) cout << val + 6 << endl;
else if (n % 6 == 4) cout << val + 9 << endl;
else if (n % 6 == 5) cout << val + 10 << endl;
else cout << val + 15 << endl;

```

---

## 作者：__Allen_123__ (赞：2)

## 题意简述

- 给定一个整数 $n$。
- 求出有多少组满足条件的 $\left ( a, b\right) (1 \le a, b \le n)$，使得 $\frac{\operatorname{lcm}(a, b) }{\gcd(a, b) } \le 3$。
- 输入共 $t$ 组数据。
- $1 \le t \le 10^4$，$1 \le n \le 10^8$。

## 题目分析

我们先观察一下数据范围：$1 \le n \le 10^8$，如果暴力枚举 $a$ 和 $b$，时间复杂度 $O(n^2)$，会被 TLE 到飞起。

那么，有没有一种更好的方法，能够降低复杂度甚至直接算出答案呢？

题目条件中已经给出：$\frac{\operatorname{lcm}(a, b) }{\gcd(a, b) } \le 3$，我们应该可以很快想到，如果这个式子的结果这么小，那么 $a$ 和 $b$ 就很可能是倍数关系，因为在一般情况下两数的最小公倍数会很大，最大公约数会很小，导致式子的值变得很大。那么从倍数关系出发，考虑如下的五个数对：

$(a, a)$ $(a, 2a)$ $(2a, a)$ $ (3a, a)$ $(a, 3a)$

计算可得，这五个数对，它们都满足条件$(\frac{\operatorname{lcm}(a, b) }{\gcd(a, b) } \le 3)$。

而其他的例如 $(a, 4a)$ 这种的数对，虽然它们也是倍数关系，但是$\frac{\operatorname{lcm}(a, b) }{\gcd(a, b) }$的值超过了 $3$，不满足条件。

所以推论结束，最终得到：只有如上的五种式子满足条件。

找到满足条件的思路以后，我们可以开始计算了：

首先是 $(a, a)$ 这个式子，也就是当 $a = b$ 时，它满足条件的范围是 $1 - n$ 之间的所有整数，共 $n$ 种可能性；

其次是 $(a, 2a)$ 和 $(2a, a)$，也就是当 $a = 2b$ 或 $b = 2a$ 时，它们满足条件的范围是 $1 - {[n\div2]}$ 之间的所有整数（因为如果 $a$ 或 $b$ 超过了 $n$ ，它们就不满足 $1 \le a, b \le n$ 的条件了），共 $\left [ n \div 2 \right ] \times 2$ 种可能性。

最后一种可能是 $(a, 3a)$ 和 $(3a, a)$，它们满足条件的范围为 $1 - {[n\div3]}$，共 $[n\div 3] \times 2$种可能性，原因同上，不再赘述。

综上所述，总共的可能性就为 $n + \left [ n \div 2 \right ] \times 2 + [n\div 3] \times 2$，大功告成！

那么既然我们找到了答案的推导式，我们就可以很容易地写代码了：

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;
int res, t, n;
int main(){
	scanf("%d", &t);
	while(t--){ 
		scanf("%d", &n);
		int a = n / 3, b = n / 2;
		res = a * 2 + b * 2 + n; // 计算最终结果，式子如上所述
		printf("%d\n", res);
	}
	return 0;
}
```

---

## 作者：DaiRuiChen007 (赞：1)

# CF1717A 题解



## 思路分析

设 $\gcd(a,b)=d, \begin{cases}a=d\times x\\b=d\times y\end{cases}$，则 $\operatorname{lcm}(a,b)=dxy$，$\dfrac{\operatorname{lcm}(a,b)}{\gcd(a,b)}=xy$。

因此 $xy\le 3, (x,y)=(1,1)/(1,2)/(1,3)/(2,1)/(3,1)$，所以答案为： $n+2\times \left(\left\lfloor\dfrac n2\right\rfloor+\left\lfloor\dfrac n3\right\rfloor\right)$。

时间复杂度 $\Theta(1)$。

## 代码呈现

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline void solve() {
	int n;
	scanf("%lld",&n);
	printf("%lld\n",n+(n/2+n/3)*2);
	return ;
}
signed main() {
	int T;
	scanf("%lld",&T);
	while(T--) solve();
	return 0;
} 
```



---

## 作者：xiaomuyun (赞：1)

- [洛谷传送门](https://www.luogu.com.cn/problem/CF1717A)
- [CodeForces 传送门](https://codeforces.com/contest/1717/problem/A)

Update (2022/9/28)：修改了勘误，主要是打错了，代码表述没有问题。

## 思路分析

一道挺好的结论题。

首先我们知道，因为 $\gcd(a,b)$ 是 $a$ 和 $b$ 的因数，而且 $\operatorname{lcm}(a,b)$ 是 $a$ 和 $b$ 的倍数，所以 $\operatorname{lcm}(a,b)$ 一定是 $\gcd(a,b)$ 的倍数，因此 $\dfrac{\operatorname{lcm}(a,b)}{\gcd(a,b)}$ 一定是个正整数。

然后因为题目中说到了 $\dfrac{\operatorname{lcm}(a,b)}{\gcd(a,b)}\le3$，所以 $\dfrac{\operatorname{lcm}(a,b)}{\gcd(a,b)}$ 只可能是 $1$、$2$ 或 $3$。然后我们按照这个式子的值分类讨论一下：

- $\dfrac{\operatorname{lcm}(a,b)}{\gcd(a,b)}=1$：这时 $a$ 一定等于 $b$，所以一共有 $n$ 种方案，其中第 $i$ 种是 $a=i,b=i$（$1\le i\le n$）。
- $\dfrac{\operatorname{lcm}(a,b)}{\gcd(a,b)}=2$：这时有 $2$ 种情况，一种是 $a=2b$，另一种是 $b=2a$。所以为了让那个更大的数不超过 $n$，所以一共有 $\lfloor\dfrac{n}{2}\rfloor\times2$ 种方案（其中 $\lfloor\dfrac{n}{2}\rfloor$ 表示其中一种情况，然后两种情况的方案数是一样的）。
- $\dfrac{\operatorname{lcm}(a,b)}{\gcd(a,b)}=3$：这时也有 $2$ 种情况，一种是 $a=3b$，另一种是 $b=3a$。所以也是为了让更大的数不超过 $n$，所以一共有 $\lfloor\dfrac{n}{3}\rfloor\times2$ 种方案。

所以最后把答案加起来，就是 $n+\lfloor\dfrac{n}{2}\rfloor\times2+\lfloor\dfrac{n}{3}\rfloor\times2$。

## 代码实现

```cpp
#include<cstdio>
using namespace std;
int t,n;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		printf("%d\n",n+n/2*2+n/3*2);
	}
	return 0;
}
```

---

## 作者：Jasper08 (赞：0)

设 $\gcd(a,b)=d,a=da',b=db'$，又因为 $\text{lcm}(a,b)=da'b'$，所以 $\frac{\text{lcm}(a,b)}{\gcd(a,b)}=\frac{da'b'}{d}=a'b'\le 3$。而 $a',b'$ 均为正整数，所以 $(a',b')=(1,1)$ 或 $(1,2)$ 或 $(1,3)$ 或 $(2,1)$ 或 $(3,1)$。

而 $1\sim n$ 中，满足 $(a',b')=(1,1)$ 的数对有 $n$ 个，$(a',b')=(1,2)$ 和 $(2,1)$ 的数对均有 $\left\lfloor\frac{n}{2}\right\rfloor$ 个，$(a',b')=(1,3)$ 和 $(3,1)$ 的数对有 $\left\lfloor\frac{n}{3}\right\rfloor$ 个。所以总答案即为 $n+2\left\lfloor\frac{n}{2}\right\rfloor+2\left\lfloor\frac{n}{3}\right\rfloor$。

代码如下：

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

int t, n;

int main() {
	scanf("%d", &t);
	while (t -- ) {
		scanf("%d", &n);
		int ans = n + n / 2 * 2 + n / 3 * 2;
		printf("%d\n", ans);
	}
	return 0;
}
```

---

## 作者：封禁用户 (赞：0)

## 题意简述

有 $t$ 组测试数据（$1 \leq t \leq 10^4$）。对于每一组测试数据给你一个数 $n$（$1 \leq n \leq 10^8$），要求你输出存在多少对整数 $(a,b)$，满足：

1. $1 \leq a, b \leq n$。

2. $\frac{\operatorname{lcm}(a, b)}{\operatorname{gcd}(a,b)} \leq 3$，其中 $\operatorname{lcm}$ 指 [最小公倍数](https://baike.baidu.com/item/%E6%9C%80%E5%B0%8F%E5%85%AC%E5%80%8D%E6%95%B0/6192375)，$\operatorname{gcd}$ 指 [最大公因数](https://baike.baidu.com/item/%E6%9C%80%E5%A4%A7%E5%85%AC%E7%BA%A6%E6%95%B0/869308)。

## 题目分析

考虑打表 $[1,31]$ 内每个数的答案，你可以自行运行以下程序观察结果。

```cpp
#include <bits/stdc++.h>
using namespace std;

int gcd(int x, int y) {
	if (y == 0) return x;
	return gcd(y, x % y);
}

int lcm(int x, int y) {
	return x * y / gcd(x, y);
}

int solve(int n) {
	int ans = 0;
	for (int a = 1; a <= n; a++)
		for (int b = 1; b <= n; b++)
			if (lcm(a, b) / gcd(a, b) <= 3)
				ans++;
	return ans;
}

int main() {
	for (int i = 1; i <= 30; i++)
		cout << "answer " << i << " is " << solve(i) << endl;
	for (int i = 2; i <= 31; i++)
		cout << "answer " << i << " minus answer " << i - 1 << " is " << solve(i) - solve(i - 1) << endl;
	return 0;
}
```

我们发现答案的差值是按 $3, 3, 3, 1, 5, 1$ 的顺序循环的。于是我们就可以枚举有多少轮过去了，在最后一轮里加上剩下的数字就是答案，很显然这个过程是 $O(1)$ 的。

例如 $n$ 为 8 的时候，我们发现已经进行过一轮了，总和是 $16$（$3 + 3 + 3 + 1 + 5 + 1$），接着第二轮剩下一个 $3$，加上原来的 $1$，所以答案就是 $1 + 16 + 3 = 20$。

有了明了的思路，代码就是水到渠成的事情了。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

int a[] = {3, 6, 9, 10, 15, 16};

int main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		if (n == 1) cout << 1 << endl;
		else cout << 1 + (n - 2) / 6 * 16 + a[(n - 2) % 6] << endl;
	}
	return 0;
}
```

---

## 作者：zhicheng (赞：0)

### 思路

$\dfrac{\operatorname{lcm}(a,b)}{\gcd(a,b)} \leq 3$，就表明我们要最大化 $\gcd(a,b)$，最小化 $\operatorname{lcm}(a,b)$。我们先设 $a \leq b$，那么当 $b$ 是 $a$ 的倍数时，$\gcd(a,b)$ 最大为 $a$，$\operatorname{lcm}(a,b)$ 最小为 $b$，所以 $\dfrac{b}{a} \leq 3$，也就是 $a=b$ 或 $b=2a$ 或 $b=3a$。第一种情况有 $n$ 个，第二种情况有 $\left\lfloor\dfrac{n}{2}\right\rfloor \times 2$ 个，第三种有 $\left\lfloor\dfrac{n}{3}\right\rfloor \times 2$ 个（后两种 $\times 2$ 是因为可以交换，$a>b$ 时还有）。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
	int n,a;
	scanf("%d",&n);
	while(n--){
		scanf("%d",&a);
		printf("%d\n",a/3*2+a/2*2+a);  //直接整除输出即可
	}
}
```

---

## 作者：cyhtxdy (赞：0)

## 题意：
求 $a\le n, b\le n$ 且满足 $\frac{{\operatorname{lcm}(a,b)}}{\gcd(a,b)}\le3$ 的二元组个数。

注意：$(a,b)$ 若满足条件，则 $(b,a)$ 也满足条件。

## 思路：
容易发现，只有以下三种二元组是合法的：$(x,x),(x,2\times x),(x,3\times x)$。

接下来证明一下：令 $d=\gcd (a,b)$，那么可以得到 $a=k\times d$。

当 $k>4$ 时一定是非法的，因为 $\operatorname{lcm}(a,b)\ge \gcd(a,b)$，则$\frac{{\operatorname{lcm}(a,b)}}{\gcd(a,b)}>4$。

那么得到 $k\le 3$。发现二元组 $(2\times x,3\times x)$ 非法，那么只有 $3$ 种合法可能：$(x,x),(x,2 \times x),(x,3 \times x)$。

计算答案：

$(x,x)$ 的个数是 $n$，$(x,2 \times x)$ 的个数是 $2 \times \lfloor \frac{n}{2} \rfloor$， $(x,3\times x)$ 的个数是 $2 \times \lfloor \frac{n}{3} \rfloor$。加起来即可。

## 代码：
```
#include <bits/stdc++.h>

using namespace std;

int T;

int main () {
	cin >> T;
	while (T --) {
		int n;
		cin >> n;
		cout << n + (n / 2) * 2 + (n / 3) * 2 << endl;
	}
	
	return 0;
}
```


---

