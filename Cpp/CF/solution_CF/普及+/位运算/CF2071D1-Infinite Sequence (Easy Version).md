# Infinite Sequence (Easy Version)

## 题目描述

这是该问题的简单版本。不同版本的区别在于此版本中 $l = r$。仅当您解决了该问题的所有版本时才能进行 hack。

给定一个正整数 $n$ 和一个无限二进制序列 $a$ 的前 $n$ 项，该序列定义如下：

- 对于 $m > n$，$a_m = a_1 \oplus a_2 \oplus \ldots \oplus a_{\lfloor \frac{m}{2} \rfloor}$ $^{\text{∗}}$。

你的任务是计算给定区间 $[l, r]$ 内元素的和：$a_l + a_{l + 1} + \ldots + a_r$。

$^{\text{∗}}$ $\oplus$ 表示[按位异或操作](https://en.wikipedia.org/wiki/Bitwise_operation#XOR)。

## 说明/提示

第一个测试用例中，序列 $a$ 为：

$$[\underline{\color{red}{1}}, 1, 1, 0, 0, 1, 1, 1, 1, 1, \ldots]$$ 

其中 $l = 1$，$r = 1$。区间 $[1, 1]$ 的元素和为 $a_1 = 1$。

第二个测试用例中，序列 $a$ 为：

$$ [\text{\color{red}{1}}, \text{\color{red}{0}}, \underline{1}, 1, 1, 0, 0, 1, 1, 0, \ldots] $$

其中 $l = 3$，$r = 3$。区间 $[3, 3]$ 的元素和为 $a_3 = 1$。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
9
1 1 1
1
2 3 3
1 0
3 5 5
1 1 1
1 234 234
0
5 1111 1111
1 0 1 0 1
1 1000000000000000000 1000000000000000000
1
10 87 87
0 1 1 1 1 1 1 1 0 0
12 69 69
1 0 0 0 0 1 0 1 0 1 1 0
13 46 46
0 1 0 1 1 1 1 1 1 0 1 1 1```

### 输出

```
1
1
0
0
1
0
1
0
0```

# 题解

## 作者：masonxiong (赞：5)

# 题目简述

给定无限长数列 $a$ 的前 $n$ 项，对于 $m>n,a_m=\bigoplus_{i=1}^{\lfloor\frac m2\rfloor}a_i$。求 $a_l$。

# 题目分析

不妨假定 $n$ 是奇数。如果 $n$ 是偶数，你就手动计算 $a_{n+1}$ 然后 $n\larr n+1$ 就行。

我们注意到 $\lfloor\frac{2m}2\rfloor=\lfloor\frac{2m+1}2\rfloor=m$，那么就有 $a_{2m}=a_{2m+1}=\bigoplus_{i=1}^ma_i(2m>n)$。

$$
\begin{aligned}
a_{2m}=a_{2m+1}=\bigoplus_{i=1}^ma_i\\
=(\bigoplus_{i=1}^na_i)\oplus(a_{n+1}\oplus a_{n+2})\oplus(a_{n+3}\oplus a_{n+4})\oplus\dots\oplus a_m
\end{aligned}
$$

由于我们假定了 $n$ 是奇数，那括号里的两项相等。相等的两个数异或为 $0$，因此后面一大串全消掉了。如果 $m$ 是奇数的话就剩下了 $a_m$。那这样我们再递归计算 $a_m$ 就行。

# 题目做法

预处理 $s=\bigoplus_{i=1}^na_i$。然后：

$$
a_{2m}=a_{2m+1}=
\begin{cases}
s(m\equiv0\pmod2)\\
s\oplus a_m(m\equiv1\pmod2)
\end{cases}
$$

---

## 作者：program_xwl (赞：3)

# 思路
首先，我们要知道，相同的两个数异或值为 $0$，任何数异或 $0$ 还得原数。
若 $m>n$ 且为偶数，$\lfloor \frac{m}{2} \rfloor=\lfloor \frac{m+1}{2} \rfloor$，而对应的，$a_m\oplus a_{m+1}=0$，所以，题目求 $a_m$ 中是有很多重复操作的，对于它们，我们直接不计算。
# 代码
时间复杂度 $O(\sum (n+\log l))$
```cpp
#include <bits/stdc++.h>
using namespace std;

long long T,n,x,a[200005];

long long get_xor(int l,int r) {return a[r]^a[l-1];}//区间异或值

long long dfs(long long x)
{
	if(x <= n) return get_xor(x,x);//在a中直接返回
	if(x/2 <= n) return get_xor(1,x/2);//可以直接得出就直接得出
	long long the_ans = get_xor(1,n);//必定包含a所有数的异或和
	if(((x/2)&1) == 0) the_ans ^= dfs(x/2);//说明x/2号元素不能被抵消，递归下去计算
	if((n&1) == 0) the_ans ^= dfs(n+1);//说明n+1号元素不能被抵消，递归下去计算，注意这里dfs(n+1)是O(1)求解的
	return the_ans;
}

int main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> T;
	while(T--)
	{
		cin >> n >> x >> x;
		for(int i = 1;i <= n;i++) cin >> a[i];
		for(int i = 1;i <= n;i++) a[i] ^= a[i-1];//以便求区间异或
		cout << dfs(x) << '\n';
	}
	return 0;
}
```
感谢 @xyvsvg 指出错误

---

