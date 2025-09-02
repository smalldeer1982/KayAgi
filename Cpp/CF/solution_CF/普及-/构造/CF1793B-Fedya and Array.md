# Fedya and Array

## 题目描述

For his birthday recently Fedya was given an array $ a $ of $ n $ integers arranged in a circle, For each pair of neighboring numbers ( $ a_1 $ and $ a_2 $ , $ a_2 $ and $ a_3 $ , $ \ldots $ , $ a_{n - 1} $ and $ a_n $ , $ a_n $ and $ a_1 $ ) the absolute difference between them is equal to $ 1 $ .

Let's call a local maximum an element, which is greater than both of its neighboring elements. Also call a local minimum an element, which is less than both of its neighboring elements. Note, that elements $ a_1 $ and $ a_n $ are neighboring elements.

Unfortunately, Fedya lost an array, but he remembered in it the sum of local maximums $ x $ and the sum of local minimums $ y $ .

Given $ x $ and $ y $ , help Fedya find any matching array of minimum length.

## 说明/提示

In the first test case, the local maximums are the numbers at $ 3, 7 $ and $ 10 $ positions, and the local minimums are the numbers at $ 1, 6 $ and $ 8 $ positions. $ x = a_3 + a_7 + a_{10} = 2 + 0 + 1 = 3 $ , $ y = a_1 + a_6 + a_8 = 0 + (-1) + (-1) = -2 $ .

In the second test case, the local maximums are the numbers at $ 2 $ and $ 10 $ positions, and the local minimums are the numbers at $ 1 $ and $ 3 $ positions. $ x = a_2 + a_{10} = -1 + 5 = 4 $ , $ y = a_1 + a_3 = -2 + (-2) = -4 $ .

In the third test case, the local maximums are the numbers at $ 1 $ and $ 5 $ positions, and the local minimums are the numbers at $ 3 $ and $ 6 $ positions.

## 样例 #1

### 输入

```
4
3 -2
4 -4
2 -1
5 -3```

### 输出

```
10
0 1 2 1 0 -1 0 -1 0 1
16
-2 -1 -2 -1 0 1 2 3 4 5 4 3 2 1 0 -1 
6
1 0 -1 0 1 0
16
2 3 2 1 0 -1 0 -1 0 -1 0 1 2 1 0 1```

# 题解

## 作者：Nuyoah_awa (赞：7)

### 题目分析
本题是一个简单数学构造题。

首先题目让构造出一个环，使得所有相邻元素差为 $1$ 并且所有值比左右两个相邻值大的数之和为 $x$，所有值比左右两个相邻值小的数之和为 $y$。

以样例一的第一组数据（$x = 3, y = -2$）为例，根据 $x$，环大致可以分成这两种情况（根据 $y$ 的分类同理）。
1. $x$ 是由一个局部最大值构成的，构造如图。![CF1793B1](https://cdn.luogu.com.cn/upload/image_hosting/zkx26n6i.png?x-oss-process=image/resize,m_lfit,h_170,w_225)
2. $x$ 是由多个局部最大值构成的，构造如图。![CF1793B2](https://cdn.luogu.com.cn/upload/image_hosting/tkluk3nr.png?x-oss-process=image/resize,m_lfit,h_170,w_225)

我们以上图为例，我们只看局部最大值，如果最大值是 $3$，可以看成 $x$ 从 $0$ 开始，最后回到 $0$。我们分成了两种情况，由一个局部最大值 $3$ 构成：从 $0 \sim 3$ 最少 $3$ 个数，从 $3 \sim 0$ 同理；第二种由一个局部最大值 $2$ 和一个局部最大值 $1$，我们不难发现，通过平移后，我们都可以看成是 $0 \sim 2 \sim 0$ 和 $0 \sim 1 \sim 0$ 两段拼接而成。

由此，我们可以推断出：对于任意 $x$ 可分解为： $x = x_1 + x_2 + …… + x_n$。若以第一种分类，$ans = x \times 2$；若以第二种分类，$ans = \sum ^{i\leq n}_{i=1}x_{i} \times 2$。很明显，前后两式的结果是一样的（对于 $y$ 的同理）。

综上，这两种方法所需要的元素个数是一样的（也最少的）。于是就可以输出最好输出的第一种，即输出从 $0 \sim x,x \sim y,y \sim 0$。

### code
```cpp
#include <iostream>
#include <cstdio>
using namespace std;
long long x, y, T;
int main()
{
	cin >> T;
	while(T--)
	{
		cin >> x >> y;
		cout << (x - y) * 2 << endl;
		for(int i = 0;i < x - y;i++)
			cout << x - i << " ";
		for(int i = 0;i < x - y;i++)
			cout << y + i << " ";
		cout << endl;
	}
	return 0;
}
```

---

## 作者：寻逍遥2006 (赞：3)

下文中我将称 local maximum 为邻域最大数， local minimum 为邻域最小数，很显然邻域最大数大于他两侧的数，邻域最小数小于他两侧的；称 $a_{i+1}=a_i+1$ 为一次上升， $a_{i+1}=a_i-1$ 为一次下降 。

我们来考虑这个数列的结构，不难发现：数列中邻域最大数和邻域最小数交替出现。

证明如下：对于一个邻域最大数 $a_i$ ，他右侧的数 $a_{i+1}$ 一定小于它，如果 $a_{i+2}>a_{i+1}$ 则 $a_{i+1}$ 为一个邻域最小数，否则 $a_i,a_{i+1},a_{i+2}$ 一直下降，重复此过程即可。由于相邻两数的差的绝对值等于 $1$ ，所以在重复考虑到 $a_i$ 之前，必然会出现一次 $a_{j+1}>a_j$ ，所以必然会出现一个邻域最小数。其他情况可以同理证明。

另一种理解方式是将数列图像化，它就是一条波动的折线，波峰和波谷是交替出现的。

根据我们上面的证明，发现，一个领域最大数和领域最小数之间的数是不断上升或者下降的，假设其中某两个相邻的邻域最大数和最小数分别为 $x_i$ 和 $y_i$ ，他们两个以及期间的数会出现形如 $x_i,x_i-1\dots y_i+1,y_i$ 或者 $x_i,x_i+1\dots y_i-1,y_i$ 的结构，在这种情况下，领域最大数和邻域最小数的差是等于这两个数下标的差的（出现关于 $n$ 和 $1$ 的衔接问题是可额外加或者减一个 $n$ ）。

由于数列中邻域最大数和邻域最小数交替出现，可以进行一一对应，如果，也就意味着，**所有领域最大数的和减去所有领域最小数的和，也就是 $x-y$ ，等于数列中上升或者下降的次数**。

由于序列是环状的，所以上升次数和下降次数应该是相等的才能符合要求。

于是假设序列长度为 $n$ ，我们就可以知道 $n=2(x-y)$ 。所以说只有这种情况下的 $n$ 可能合法，现在我们只需考虑构造。最简单的构造就是出现一个邻域最大数为 $x$ 和一个领域最小数为 $y$ ，中间一直上升或者下降即可。

```cpp
#include <bits/stdc++.h>
using namespace std;
int Qread()
{
	int x=0;bool f=false;char ch=getchar();
	while(ch<'0'||ch>'9') f|=('-'==ch),ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+(ch^48),ch=getchar();
	return f?-x:x; 
}
long long x,y;
long long dis;
long long ans;
void solve()
{
	x=Qread(),y=Qread();
	dis=x-y;
	printf("%lld\n",dis*2);
	for(int i=0;i<dis;i++) printf("%lld ",x-i);
	for(int i=0;i<dis;i++) printf("%lld ",y+i);
	printf("\n");
	return;
}
int T;
int main()
{
	T=Qread();
	while(T--) solve();
	return 0;
}
```

---

## 作者：_djc_ (赞：0)

## 思路

首先我们可以发现局部最小值和局部最大值会交替出现，并且数量相同，而在可能的构造中，数列从一个局部最小值变到局部最大值或是从局部最大值变到局部最小值，一定是直接降下去或升上去最短。也就是说设局部最大值构成 $a$，局部最小值构成 $b$，每一个 $a_i$ 到 $b_i$ 都需要 $a_i - b_i$ 项，而从最小值到最大值需要 $a_{i + 1} - b_i$ 项，那么总共就是需要 $(\sum a_i - \sum b_i) \times 2$ 项。

接下来考虑构造数组，我们可以假设数组中只有一个最大值、一个最小值，输出 $x, x-1, \cdots y, y + 1, y + 2, \cdots x - 1$ 即可。

## 代码

```cpp
#include <bits/stdc++.h>
#define maxn 1005
using namespace std;
inline int read() {
    int x = 0, f = 1; char c = getchar();
    while (c < '0' || c > '9') { if (c == '-') f = -1; c = getchar(); }
    while (c >= '0' && c <= '9') { x = x * 10 + c - '0'; c = getchar(); }
    return x * f;
}
int main() {
	int T = read();
	while (T--) {
		int a = read(), b = read();
		cout << (a - b) * 2 << endl;
		for (int i = a; i >= b; i--) cout << i << " ";
		for (int i = b + 1; i < a; i++) cout << i << " ";
		cout << endl;
	}
}
```


---

## 作者：loser_seele (赞：0)

赛时没做出来，寄。

实际上题目里没有写 $ x-y $ 的范围，只有当 $ x-y \leq 10^5 $ 的时候才满足条件限制，下面会讲到。

观察到局部极小值和局部极大值是互相生成的，于是他们的数量一样。然后考虑在同样位置上的两个数，我们设局部最大值在局部最小值前面，另一种情况类似，则距离为 $ a_i-b_i $，其中 $ a_i,b_i $ 分别表示局部极大值和局部极小值。反过来也可以类似计算。

于是得到总项数为 $ \sum (a_i-b_i)+(a_{i+1}-b_i) = 2(\sum a_i - \sum b_i) =2 \times (A-B)=n $。观察样例后不难得到这个结论。

构造是平凡的，类似 $ [y,y+1,y+1,...,x-1,x,x-1,...,y+1] $ 的形式即可满足条件。

时间复杂度为 $ \mathcal{O}(\sum n) $，因为答案保证输出总和不超过 $ 2 \times 10^5 $ 所以随便过。

[提交记录](https://codeforces.com/contest/1793/submission/193403393)

---

## 作者：yimuhua (赞：0)

### 题意

定义一个长为 $n$ 的序列 $a$ 中 $a_1$ 和 $a_2,a_3$ 和 $a_4,\dots,a_{n-1}$ 和 $a_n,a_n$ 和 $a_1$ 为相邻的。

定义局部最大值为与其相邻的元素都小于它的数，局部最小值为与其相邻的元素都大于它的数。

给出一个序列的局部最大值之和 $x$ 和局部最小值之和 $y$，求一个最短的序列满足 $x,y$。

### 思路

设第 $i$ 个局部最大值为 $a_i$，第 $i$ 个局部最小值为 $b_i$，序列长度为 $n$。

为了让 $b_i$ 接上 $a_i$，则需要 $a_i-b_i$ 个数字。

$\therefore n=(a_1-b_1)+(a_2-b_1)+(a_2-b_2)+\dots+(a_k-b_k)+(a_1-b_k)=2\times(a_1+a_2+\dots+a_k)-2\times(b_1+b_2+\dots+b_k)=2(x-y)$

此时有一种显然的构造方法：$x,x-1,x-2,\dots,y,y+1,y+2\dots,x-1$。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
long long t, x, y;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> t;
    while(t--) {
        cin >> x >> y;
        if(x > y)
            swap(x, y);
        cout << 2 * abs(x - y) << '\n' << x << ' ';
        for(long long i = x + 1; i < y; i++)
            cout << i << ' ';
        for(long long i = y; i > x; i--)
            cout << i << ' ';
        cout << '\n';
    }
    return 0;
}
```


---

