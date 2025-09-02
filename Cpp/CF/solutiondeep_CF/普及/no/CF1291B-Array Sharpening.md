# 题目信息

# Array Sharpening

## 题目描述

You're given an array $ a_1, \ldots, a_n $ of $ n $ non-negative integers.

Let's call it sharpened if and only if there exists an integer $ 1 \le k \le n $ such that $ a_1 < a_2 < \ldots < a_k $ and $ a_k > a_{k+1} > \ldots > a_n $ . In particular, any strictly increasing or strictly decreasing array is sharpened. For example:

- The arrays $ [4] $ , $ [0, 1] $ , $ [12, 10, 8] $ and $ [3, 11, 15, 9, 7, 4] $ are sharpened;
- The arrays $ [2, 8, 2, 8, 6, 5] $ , $ [0, 1, 1, 0] $ and $ [2, 5, 6, 9, 8, 8] $ are not sharpened.

You can do the following operation as many times as you want: choose any strictly positive element of the array, and decrease it by one. Formally, you can choose any $ i $ ( $ 1 \le i \le n $ ) such that $ a_i>0 $ and assign $ a_i := a_i - 1 $ .

Tell if it's possible to make the given array sharpened using some number (possibly zero) of these operations.

## 说明/提示

In the first and the second test case of the first test, the given array is already sharpened.

In the third test case of the first test, we can transform the array into $ [3, 11, 15, 9, 7, 4] $ (decrease the first element $ 97 $ times and decrease the last element $ 4 $ times). It is sharpened because $ 3 < 11 < 15 $ and $ 15 > 9 > 7 > 4 $ .

In the fourth test case of the first test, it's impossible to make the given array sharpened.

## 样例 #1

### 输入

```
10
1
248618
3
12 10 8
6
100 11 15 9 7 8
4
0 1 1 0
2
0 0
2
0 1
2
1 0
2
1 1
3
0 1 0
3
1 0 1```

### 输出

```
Yes
Yes
Yes
No
No
Yes
Yes
Yes
Yes
No```

# AI分析结果

### 题目内容重写
# 数组锐化

## 题目描述

给定一个包含 $n$ 个非负整数的数组 $a_1, \ldots, a_n$。

如果存在一个整数 $1 \le k \le n$，使得 $a_1 < a_2 < \ldots < a_k$ 且 $a_k > a_{k+1} > \ldots > a_n$，则称该数组为“锐化”数组。特别地，任何严格递增或严格递减的数组都是锐化的。例如：

- 数组 $[4]$、$[0, 1]$、$[12, 10, 8]$ 和 $[3, 11, 15, 9, 7, 4]$ 是锐化的；
- 数组 $[2, 8, 2, 8, 6, 5]$、$[0, 1, 1, 0]$ 和 $[2, 5, 6, 9, 8, 8]$ 不是锐化的。

你可以进行以下操作任意次：选择数组中的任意一个严格正的元素，并将其减一。形式上，你可以选择任意 $i$（$1 \le i \le n$）使得 $a_i>0$，并将 $a_i := a_i - 1$。

问是否可以通过若干次（可能为零次）操作使给定的数组变为锐化数组。

## 说明/提示

在第一个和第二个测试用例中，给定的数组已经是锐化的。

在第三个测试用例中，我们可以将数组转换为 $[3, 11, 15, 9, 7, 4]$（将第一个元素减 97 次，将最后一个元素减 4 次）。它是锐化的，因为 $3 < 11 < 15$ 且 $15 > 9 > 7 > 4$。

在第四个测试用例中，无法使给定的数组变为锐化数组。

## 样例 #1

### 输入

```
10
1
248618
3
12 10 8
6
100 11 15 9 7 8
4
0 1 1 0
2
0 0
2
0 1
2
1 0
2
1 1
3
0 1 0
3
1 0 1```

### 输出

```
Yes
Yes
Yes
No
No
Yes
Yes
Yes
Yes
No```

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是通过贪心算法，分别找到数组中可以形成严格递增前缀和严格递减后缀的最大范围，然后检查这两个范围是否有交集。如果有交集，则可以通过操作使数组变为锐化数组。

### 所选题解
#### 作者：liuyongle (赞：1)
- **星级**: 4
- **关键亮点**: 通过贪心算法分别计算严格递增前缀和严格递减后缀的最大范围，并检查它们的交集是否非空。思路清晰，代码简洁。
- **代码核心思想**: 分别从前往后和从后往前遍历数组，找到满足条件的前缀和后缀，最后检查它们的交集。

```cpp
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(false); cin.tie(0);

    int nbTests; cin >> nbTests;
    while (nbTests--) {
	    int nbElem; cin >> nbElem;
	    vector<int> tab(nbElem);

	    for (int i = 0; i < nbElem; ++i)
		    cin >> tab[i];

	    int prefixEnd = -1, suffixEnd = nbElem;

	    for (int i = 0; i < nbElem; ++i) {
		    if (tab[i] < i) break;
		    prefixEnd = i;
	    }
	    for (int i = nbElem-1; i >= 0; --i) {
		    if (tab[i] < (nbElem-1)-i) break;
		    suffixEnd = i;
	    }

	    if (suffixEnd <= prefixEnd) // Non-empty intersection
		    cout << "Yes\n";
	    else
		    cout << "No\n";
    }
}
```

#### 作者：邓布利多6 (赞：0)
- **星级**: 4
- **关键亮点**: 通过从前往后和从后往前扫描数组，找到满足条件的前缀和后缀，并检查它们的交集。思路清晰，代码简洁。
- **代码核心思想**: 分别从前往后和从后往前遍历数组，找到满足条件的前缀和后缀，最后检查它们的交集。

```cpp
#include <iostream>
using namespace std;
const int N = 1000001;
int t, n, a[N], high, high2;
int main()
{
	cin >> t;
	while(t--)
	{
		cin >> n; high = high2 = 0;
		for(int i = 1; i <= n; i++) cin >> a[i];
		for(int i = 1; i <= n; i++)
			if(a[i] < i - 1) { high = i - 1; break; }
		if(!high) high = n;
		for(int i = n; i; i--) 
			if(a[i] < (n - i)) { high2 = i + 1; break; }
		if(!high2) high2 = 1;
		cout << (high2 > high ? "No" : "Yes") << endl;
	}
	return 0;
}
```

### 最优关键思路或技巧
1. **贪心算法**: 通过贪心策略分别找到数组中可以形成严格递增前缀和严格递减后缀的最大范围。
2. **交集检查**: 通过检查前缀和后缀的交集是否非空，判断是否可以使数组变为锐化数组。

### 可拓展之处
类似的问题可以通过贪心算法解决，例如在数组中寻找满足特定条件的子序列或子数组。

### 推荐题目
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---
处理用时：39.61秒