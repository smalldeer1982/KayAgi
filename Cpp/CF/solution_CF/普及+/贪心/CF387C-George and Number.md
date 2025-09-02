# George and Number

## 题目描述

George is a cat, so he really likes to play. Most of all he likes to play with his array of positive integers $ b $ . During the game, George modifies the array by using special changes. Let's mark George's current array as $ b_{1},b_{2},...,b_{|b|} $ (record $ |b| $ denotes the current length of the array). Then one change is a sequence of actions:

- Choose two distinct indexes $ i $ and $ j $ $ (1<=i,j<=|b|; i≠j) $ , such that $ b_{i}>=b_{j} $ .
- Get number $ v=concat(b_{i},b_{j}) $ , where $ concat(x,y) $ is a number obtained by adding number $ y $ to the end of the decimal record of number $ x $ . For example, $ concat(500,10)=50010 $ , $ concat(2,2)=22 $ .
- Add number $ v $ to the end of the array. The length of the array will increase by one.
- Remove from the array numbers with indexes $ i $ and $ j $ . The length of the array will decrease by two, and elements of the array will become re-numbered from $ 1 $ to current length of the array.

George played for a long time with his array $ b $ and received from array $ b $ an array consisting of exactly one number $ p $ . Now George wants to know: what is the maximum number of elements array $ b $ could contain originally? Help him find this number. Note that originally the array could contain only positive integers.

## 说明/提示

Let's consider the test examples:

- Originally array $ b $ can be equal to $ {5,9,5,5} $ . The sequence of George's changes could have been: $ {5,9,5,5}→{5,5,95}→{95,55}→{9555} $ .
- Originally array $ b $ could be equal to $ {1000000000,5} $ . Please note that the array $ b $ cannot contain zeros.
- Originally array $ b $ could be equal to $ {800,10,1} $ .
- Originally array $ b $ could be equal to $ {45} $ . It cannot be equal to $ {4,5} $ , because George can get only array $ {54} $ from this array in one operation.

Note that the numbers can be very large.

## 样例 #1

### 输入

```
9555
```

### 输出

```
4```

## 样例 #2

### 输入

```
10000000005
```

### 输出

```
2```

## 样例 #3

### 输入

```
800101
```

### 输出

```
3```

## 样例 #4

### 输入

```
45
```

### 输出

```
1```

## 样例 #5

### 输入

```
1000000000000001223300003342220044555
```

### 输出

```
17```

## 样例 #6

### 输入

```
19992000
```

### 输出

```
1```

## 样例 #7

### 输入

```
310200
```

### 输出

```
2```

# 题解

## 作者：5ab_juruo (赞：1)

本文同步发布于我的[博客园](https://www.cnblogs.com/5ab-juruo)。

题意：给定一个数 $p$，$p$ 由若干次拼接操作构成，每次拼接操作要求前面的数要大于等于后面的数，求原先最多有多少数，这些数都不允许存在前导零。

这个拼接时的大小要求十分让人讨厌，我们可以令拼接操作从左往右进行，这样左边的数尽可能大，而右边尽可能小。

同时，数是不允许存在前导零的，所以我们每次遍历，都往后一直到没有后继零为止，这个数与前面已经拼接完成的数进行大小比较。有两种情况：

1. 后面的数比前面小或相等，就拼接起来；
2. 后面的数比前面的数大：如 `23`，此时我们要将前面的数和后面的数合为一个整体，注意到这时这个数就不是拼接而来的。比如 `19992000` 就是一个数，不是由 `1999` 和 `2000` 构成的。

这种做法显然正确，证明如下：

设当前这一段为 $x$，前面已经完成的拼接段为 $p_1$，后面未合并的 $p_2$。

$p_1$ 已经无法与 $x$ 拼接，如果 $x$ 不和 $p_1$ 合成一个整体，则：

后面 $x$ 一定与 $p_2$ 拼接，否则一定没有合成整体优，但这样产生一个新数 $x^\prime>x$，更加无法和 $p_1$ 拼接。也没有直接合成优。

这样就可以了。

注意到有一个小 trick，在判整数大小时，不用傻乎乎地去写高精度，只需要判长度和首位即可，读者自证不难。

Code：

```cpp
#include <cstdio>
using namespace std;

const int max_n = 100000;
char a[max_n+1];

int main()
{
	int n, lp = 114514, ptr, cnt = 0; // 初始需要一个长度无限大的数

	scanf("%s", a);
	for (n = 0; a[n]; )
	{
		ptr = n + 1;
		while (a[ptr] && a[ptr] == '0') // 去除后继零
			ptr++;
		
		if (lp > ptr - lp || (lp == ptr - lp && a[0] >= a[lp]))
		{
			n = lp = ptr; // 可以拼接
			cnt++; // 记上数量
		}
		else // 否则直接合成
		{
			n = lp = ptr;
			cnt = 1; // 只能算一个
		}
	}

	printf("%d\n", cnt);

	return 0;
}
```

---

## 作者：Proxima_Centauri (赞：0)

[原题传送门](https://www.luogu.com.cn/problem/CF387C)

# ~~一本正经的~~分析
这个题，就是给你一个字符串，把它分割成几个部分，但注意从左到右依次变大。

下面我们分两个部分处理问题：

1. 分割成几个部分

我们用 $pos$ 来当遍历字符串的光标，用 $ans$ 来记录分割成的数量，用字符串 $t$ 来记录当前要分割的部分。
```
t += s[pos];
pos++;
```

但是，题目中有一个限定条件，那就是：不能有 $0$ ! 

于是我们把 $0$ 合并到 $t$ 上，采用如下的方式：
```
while (pos < s.size() && s[pos] == '0')//pos不能越界
{
	t += s[pos];
	pos++;
}
```
2. 依次变大

使用 $check$ 函数来判断大小：
```
bool check(string s1, string s2)
{
	if (s1.size() != s2.size()) return s1.size() > s2.size();
	return s1 >= s2;
}
```
用 $pre$ 来记录之前所有合并的字符串，把 $pre$ 和当前的 $t$ 作比较即可。
# AC code
```
#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
int f[100010];
bool check(string s1, string s2)
{
	if (s1.size() != s2.size()) return s1.size() > s2.size();
	return s1 >= s2;
}
int main()
{
	string s;
	cin >> s;
	string pre = "";
	int pos = 0, ans = 0;
	while (pos < s.size())
	{
		string t = "";
		t += s[pos];
		pos++;
		while (pos < s.size() && s[pos] == '0')
		{
			t += s[pos];
			pos++;
		}
		if (check(pre, t)) ans++;
		else ans = 1;
		pre += t;
	}
	cout << ans << endl;
	return 0;
}
```

---

