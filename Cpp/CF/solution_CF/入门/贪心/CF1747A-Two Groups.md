# Two Groups

## 题目描述

给定一个包含 $n$ 个整数的数组 $a$。你需要将这 $n$ 个整数分成两个组 $s_1$ 和 $s_2$（组可以为空），使得满足以下条件：

- 对于每个 $i$ $(1 \leq i \leq n)$，$a_i$ 恰好属于一个组。
- $|sum(s_1)| - |sum(s_2)|$ 的值在所有分组方式中最大。这里 $sum(s_1)$ 表示组 $s_1$ 中所有数的和，$sum(s_2)$ 表示组 $s_2$ 中所有数的和。

请你求出 $|sum(s_1)| - |sum(s_2)|$ 的最大可能值。

## 说明/提示

在第一个测试用例中，可以分组为 $s_1 = \{10\}$，$s_2 = \{-10\}$。此时值为 $|10| - |-10| = 0$。

在第二个测试用例中，可以分组为 $s_1 = \{0, 11, -1\}$，$s_2 = \{-2\}$。此时值为 $|0 + 11 - 1| - |-2| = 10 - 2 = 8$。

在第三个测试用例中，可以分组为 $s_1 = \{2, 3, 2\}$，$s_2 = \{\}$。此时值为 $|2 + 3 + 2| - |0| = 7$。

在第四个测试用例中，可以分组为 $s_1 = \{-9, -4, 0\}$，$s_2 = \{2, 0\}$。此时值为 $|-9 - 4 + 0| - |2 + 0| = 13 - 2 = 11$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
4
2
10 -10
4
-2 -1 11 0
3
2 3 2
5
-9 2 0 0 -4```

### 输出

```
0
8
7
11```

# 题解

## 作者：sw2022 (赞：4)

## 题意简析

给定一个序列 $a\ (|a|=n,n>0)$，把这个序列分成两个序列 $X,Y$，求 $|\sum a_i\ (a_i\in X)|-|\sum a_i\ (a_i\in Y)|$ 的最大值。

对于序列中的所有元素 $a_i$，分两种情况讨论：

- $a_i>0$，则 $a_i$ 放在 $X$ 中的值比放在 $Y$ 中的值大 $2a_i$。
$$(X+|a_i|)-(Y-|a_i|)$$
- $a_i\le 0$，则当 $\forall a_j>0$，$a_j\in X$ 时，$a_i$ 放在 $X$ 和 $Y$ 中的值相等。
$$(X-|a_i|)-(Y-|a_i|)$$

所以答案的上界就是 $|\sum a_i\ (a_i>0)|-|\sum a_i\ (a_i\le 0)|=|\sum a_i\ (a_i>0)+\sum a_i\ (a_i\le 0)|=|\sum a_i|$。

## 代码/解释
```cpp
#include<bits/stdc++.h>
using namespace std;
int main()
{
    int t,n,a,i;
    long long s;
    cin>>t;
    while(t--)
    {
        cin>>n;s=0;
        for(i=1;i<=n;i++)
        cin>>a,s+=a;
        printf("%lld\n",llabs(s));
    }
    return 0;
}
```

---

## 作者：Lyccrius (赞：2)

> **提示**：将所有正数放在一组中，将所有负数放在第二组中怎么样

声明：答案是 $\lvert S \rvert$。

证明：设所有正元素之和为 $S_{pos}$，所有负元素之和为 $S_{neg}$。将所有正数放在第一组，将负数放在第二组。 我们得到 $\lvert S_{pos} \rvert - \lvert S_{neg} \rvert = \lvert S \rvert$。

让我们证明我们不能做得比这更好。令 $S_1$ 表示第一组元素的总和，$S_2$ 表示第二组元素的总和。 我们有 $\lvert S_1 \rvert - \lvert S_2 \rvert \le \lvert S_1 + S_2 \rvert = \lvert S \rvert$。 因此 $\lvert S \rvert$ 是答案的上限。

```
#include <cstdio>
#include <cmath>
 
int t;
int n;
int a;
long long s1, s2;
 
int main() {
    scanf("%d", &t);
    while (t--) {
        s1 = 0;
        s2 = 0;
        scanf("%d", &n);
        while (n--) {
            scanf("%d", &a);
            if (a > 0) s1 += a;
            else s2 -= a;
        }
        long long ans = std::abs(s1 - s2);
        printf("%lld\n", ans);
    }
    return 0;
}
```

---

## 作者：sunzz3183 (赞：0)

# CF1747A-Two Groups题解

## 题意

你现在有一个长度为 $n$ 的数组 $a$，现在你把这个数组恰好分为两组（可以为空），使得 $|sum_1|-|sum_2|$ 最大。

## 思路

看到这道题，我们可以先大猜结论

答案为 $|sum_a|$。

那么怎么正确性呢：

我们假设我们已经按照将正数分为一组，和记为 $sum_b$，将负数分为一组，和记为 $sum_c$ 的方法分好组了，则有：

情况一：$|sum_b|\geq|sum_c|$

则：$|sum_b|-|sum_c|$

$=|b_1+b_2+...+b_x|-|c_1+c_2+...+c_y|$ 

$=b_1+b_2+...+b_x+c_1+c_2+...+c_y$

你会发现就是所有数字的和

情况二：$|sum_b|\leq|sum_c|$

则：$|sum_c|-|sum_b|$

$=|c_1+c_2+...+c_y|-|b_1+b_2+...+b_x|$

$=-c_1-c_2-...-c_y-b_1-b_2-...-b_x$

$=-(b_1+b_2+...+b_x+c_1+c_2+...+c_y)$

你会发现就是所有数字的和的相反数

综上所述：答案为 $|sum_a|$。

那为什么这样分组就正确呢？

你仔细观察一下，会发现 **一个数在这两种情况下，在正数组和在负数组，价值是相同的** 自己可以出几组数据试试看。

所以，我们可以得到这道题的代码

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;char c=getchar();
	while(c<'0'||'9'<c){if(c=='-')f=-1;c=getchar();}
	while('0'<=c&&c<='9'){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
	return x*f;
}
int T,n;
signed main(){
	T=read();
	while(T--){
		n=read();
		int sum=0;
		for(int i=1;i<=n;i++)
			sum+=read();
		printf("%lld\n",abs(sum));
	}
	return 0;
}
```







---

## 作者：joyslog (赞：0)

## Two Groups

[CF1747A](https://codeforces.com/problemset/problem/1747/A)

给定数列 $a_1 \dots a_n$，你要将他们分成两组，两组的和分别为 $sum_1$ 和 $sum_2$。求出 $\lvert sum_1 \rvert - \lvert sum_2 \rvert$ 的最大值。

多组数据，一个测试点内每组数据的 $n$ 之和满足 $\sum n\le 2\times 10^5$。

### 题解

考虑数据范围，我们可能需要一个 $O(\sum n)$ 的做法，于是试着找找规律。

容易发现，样例的答案都可以由 **把所有正数分到同一组** 且 **把所有负数分到另一组** 得到，于是敲上去直接通过 Pretests 了，最后也 AC 了。

这样为什么正确呢？

我们想要让 $\lvert sum_1 \rvert$ 尽量大，那么我们放同一种符号的数，绝对值自然就最大了。对于另一种符号的数，它分到哪一组其实无所谓：

假设第 $1$ 组的和为正数，对于一个负数 $x$，它分到第 $1$ 组，会使 $\lvert sum_1 \rvert$ 减少 $\lvert x\rvert$，即差值减少 $\lvert x\rvert$；分到第 $2$ 组，会使 $\lvert sum_2 \rvert$ 增加 $\lvert x\rvert$，差值也是减少 $\lvert x\rvert$。

若第 $1$ 组的和为负数也同理。所以我们把同一符号的数分到一起。

参考代码：

```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read() {...}
inline void write(ll x) {...}

int main() {
    int T = read();
    while(T--) {
        ll sum1 = 0, sum2 = 0;
        int n = read();
        for(int i = 1; i <= n; i++) {
            int x = read();
            if(x > 0)   sum1 += x;
            else    sum2 += -x;
        }
        write(max(sum1, sum2) - min(sum1, sum2));
        putchar('\n');
    }
    return 0;
}
```


---

## 作者：luo_shen (赞：0)

## 题意简述
给定一些数，将其划分到两个可重集 $s_1,s_2$ 中，$s_1,s_2$ 可以为空，问 $|\sum\limits_{x\in s_1}x|-|\sum\limits_{x\in s_2}x|$ 的最大值。
## 题目分析
可以想到将负数和正数分别分入 $s_1,s_2$，$0$ 随便放入哪个组。令 $a=\sum\limits_{x\in s_1}x,b=\sum\limits_{x\in s_2}x$，最后结果显然为 $||a|-|b||$，进行分类讨论可以知道，该值等于 $|a+b|$。
## Code
```cpp
void solve(){
    int n,ans=0;
    read(n);
    for(int i=1,x;i<=n;i++){
        read(x);
        ans+=x;
    }
    write_endl(abs(ans));
}
```

---

## 作者：CLCK (赞：0)

一道简单题。

将数列分为两组，其实只需要任意分配，最后大减小必为答案。

接着证明结论正确性。

对于数列 $a_1, a_2, a_3, 0, b_1, b_2, b_3(a1 \gt a_2 \gt a_3 \gt 0 \gt b_1 \gt b_2 \gt b_3)$，将其分组后，不妨设其结果为 $\lvert sum_1 \rvert - \lvert sum_2 \rvert (\lvert sum_1 \rvert > \lvert sum_2 \rvert)$ 时取到最大值，且 $sum_1 \gt 0, sum_2 \lt 0$，在 $sum_2$ 中取出一项 $b_1$，放入 $sum_1$ 中，$ans = \lvert sum_1 + b_1 \rvert - \lvert sum_2 - b_1 \rvert = \lvert sum_1 \rvert - \lvert b_1 \rvert - (\lvert sum_2 \rvert - \lvert b_1 \rvert) = \lvert sum1 \rvert - \lvert sum_2 \rvert$，与原答案相同，故得证。


```cpp
#include <iostream>
#include <cmath>
#define int long long //一定要开long long！
using namespace std;
int t;
signed main() {
	ios::sync_with_stdio(false); //输入输出优化
	cin.tie(0); cout.tie(0);
	cin >> t;
	while (t--) {
		int n;
		int sum1 = 0, sum2 = 0;
		cin >> n;
		for (int i = 0; i < n; i++) {
			int x = 0;
			cin >> x;
			if (x >= 0) sum1 += x; //为方便按照正负分组
			else sum2 += x;
		}
		cout << max(abs(sum1), abs(sum2)) - min(abs(sum1), abs(sum2)) << endl; //大减小必为正解
	}
	return 0;
}
```

完结撒花～

---

