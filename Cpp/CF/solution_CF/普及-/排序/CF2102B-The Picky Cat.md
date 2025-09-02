# The Picky Cat

## 题目描述

给定一个整数数组 $a_1, a_2, \ldots, a_n$。你可以执行以下操作任意次数（包括零次）：

- 选择一个下标 $i$（$1 \le i \le n$）。将 $a_i$ 乘以 $-1$（即更新 $a_i := -a_i$）。

你的任务是判断是否可以通过上述操作使得下标为 $1$ 的元素成为数组的中位数。注意操作也可以应用于下标 $1$，这意味着中位数可以是 $a_1$ 的原值或其相反数。

数组 $b_1, b_2, \ldots, b_m$ 的中位数定义为数组中第 $\left\lceil \frac{m}{2} \right\rceil$ 小的元素 $^{\text{∗}}$。例如，数组 $[3, 1, 2]$ 的中位数是 $2$，而数组 $[10, 1, 8, 3]$ 的中位数是 $3$。

保证数组 $a$ 中元素的绝对值互不相同。形式化地说，不存在下标对 $1 \le i < j \le n$ 满足 $|a_i| = |a_j|$。

$^{\text{∗}}$ $\lceil x \rceil$ 是向上取整函数，返回大于等于 $x$ 的最小整数。

## 说明/提示

在第一个测试用例中，$a_1 = 2$ 已经是数组 $a = [2, 3, 1]$ 的中位数，因此不需要任何操作。

在第二个测试用例中，我们可以执行两次操作：一次在下标 $2$，一次在下标 $5$。数组变为 $[1, -2, 3, 4, -5]$，其中中位数为 $1$。

在第三个测试用例中，如果对下标 $1$ 执行操作，数组将变为 $[-4, 2, 0, -5]$，其中中位数为 $-4$。

在第四个测试用例中，可以证明不存在任何操作序列能使数组的中位数变为 $5$ 或 $-5$。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
7
3
2 3 1
5
1 2 3 4 5
4
4 2 0 -5
4
-5 0 4 3
4
-10 8 3 2
1
1
10
9 1000 -999 -13 456 -223 23 24 10 0```

### 输出

```
YES
YES
YES
NO
NO
YES
YES```

# 题解

## 作者：cflsfzh (赞：1)

我们发现，这道题只跟绝对值有关。设 $a_1$ 为 $b$，假设此时有个值为 $c$，若 $\operatorname{abs}(c) < \operatorname{abs}(b)$，显然这种数字的对于 $a$ 来说是大还是小都是同步的。若 $\operatorname{abs}(c) > \operatorname{abs}(b)$，显然这种数字对于 $a$ 来说是大是小是任意的。于是我们只需要判断大小同步的数量是否小于等于 $n\div2$ 即可，若满足即为``Yes``，反之即为``No``。代码不挂了。

---

## 作者：szh_AK_all (赞：1)

感觉和省选 D1T1 有点像。

考虑 $a_1$ 是否要乘上 $-1$ 两种情况。

对于每种情况，找出一定比 $a_1$ 大的数的个数 $da$，一定比 $a_1$ 小的数的个数 $xi$，如果满足条件当且仅当 $xi+1\le k$ 并且 $n-da\ge k$。

```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long
int a[1000005];
 
signed main() {
	int t;
	cin >> t;
	while (t--) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; i++)
			cin >> a[i];
		int k = (n + 1) / 2;
		int da = 0, xi = 0, de = 0;
		for (int i = 2; i <= n; i++) {
			if (abs(a[i]) == abs(a[1]))
				de++;
			else if (-1 * abs(a[i]) > a[1])
				da++;
			else if (abs(a[i]) < a[1])
				xi++;
		}
		if (xi + 1 <= k && xi + de + n - xi - de - da >= k)
			cout << "yes";
		else {
			a[1] *= -1;
			da = 0, xi = 0, de = 0;
			for (int i = 2; i <= n; i++) {
				if (abs(a[i]) == abs(a[1]))
					de++;
				else if (-1 * abs(a[i]) > a[1])
					da++;
				else if (abs(a[i]) < a[1])
					xi++;
			}
			if (xi + 1 <= k && xi + de + n - xi - de - da >= k)
				cout << "yes";
			else
				cout << "no";
		}
		cout << endl;
	}
}
```

---

