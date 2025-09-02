# 题目信息

# Two Arrays and Sum of Functions

## 题目描述

You are given two arrays $ a $ and $ b $ , both of length $ n $ .

Let's define a function $ f(l, r) = \sum\limits_{l \le i \le r} a_i \cdot b_i $ .

Your task is to reorder the elements (choose an arbitrary order of elements) of the array $ b $ to minimize the value of $ \sum\limits_{1 \le l \le r \le n} f(l, r) $ . Since the answer can be very large, you have to print it modulo $ 998244353 $ . Note that you should minimize the answer but not its remainder.

## 样例 #1

### 输入

```
5
1 8 7 2 4
9 7 2 9 3
```

### 输出

```
646
```

## 样例 #2

### 输入

```
1
1000000
1000000
```

### 输出

```
757402647
```

## 样例 #3

### 输入

```
2
1 3
4 2
```

### 输出

```
20
```

# AI分析结果

【题目内容（中文重写）】
# 两个数组与函数之和

## 题目描述
给定两个长度均为 $n$ 的数组 $a$ 和 $b$。

定义函数 $f(l, r) = \sum\limits_{l \le i \le r} a_i \cdot b_i$。

你的任务是对数组 $b$ 的元素进行重新排序（选择元素的任意顺序），以最小化 $\sum\limits_{1 \le l \le r \le n} f(l, r)$ 的值。由于答案可能非常大，你需要将其对 $998244353$ 取模后输出。请注意，你应该最小化的是答案本身，而不是其取模后的余数。

## 样例 #1
### 输入
```
5
1 8 7 2 4
9 7 2 9 3
```
### 输出
```
646
```

## 样例 #2
### 输入
```
1
1000000
1000000
```
### 输出
```
757402647
```

## 样例 #3
### 输入
```
2
1 3
4 2
```
### 输出
```
20
```

【算法分类】
数学

【综合分析与结论】
这些题解的核心思路都是先推导得出每个 $a_i$ 的贡献为 $a_i\times(n - i + 1)\times i$，将其作为新的 $a_i$ 值，再利用排序不等式或差大积小的贪心策略，将新的 $a$ 数组从小到大排序，$b$ 数组从大到小排序，最后计算 $\sum\limits_{i = 1}^{n} a_i \cdot b_i$ 并对结果取模。

思路方面，各题解都围绕计算 $a_i$ 的贡献和排序展开，差异不大。算法要点在于准确计算 $a_i$ 的贡献次数以及合理排序。解决难点主要是推导 $a_i$ 的贡献次数和处理取模问题，部分题解强调在计算 $a_i\times(n - i + 1)\times i$ 时不能取模，否则可能导致排序错误。

【所选题解】
- Rex01（4星）
  - 关键亮点：思路清晰，代码简洁，对公式推导有一定展示。
- momo5440（4星）
  - 关键亮点：提到了排序不等式，给出了相关链接，适合进一步学习。
- OIerWu_829（4星）
  - 关键亮点：简洁明了地指出解题关键，提醒了取模问题。

【重点代码】
```cpp
// Rex01的核心代码
#include <iostream>
#include <algorithm>
#define ll long long
using namespace std;

const int N = 2e5 + 10;
const int mod = 998244353;
ll n, a[N], b[N], sum;

bool cmp(int a, int b)
{//从大到小排序函数
	return a > b; 
}

int main()
{
	cin >> n;
	for(int i = 1; i <= n; i++)
		cin >> a[i], a[i] *= (n - i + 1) * i;
	for(int i = 1; i <= n; i++)
		cin >> b[i];
	sort(a + 1, a + n + 1);//从小到大
	sort(b + 1, b + n + 1, cmp);//从大到小
	for(int i = 1;i <= n; i++)
	{
		sum %= mod;
		sum += a[i] % mod * b[i] % mod;
		sum %= mod;
	}
	cout << sum << endl;
	return 0;
}
```
核心实现思想：先读入数组 $a$ 和 $b$，将 $a$ 数组每个元素乘以 $(n - i + 1) \times i$，然后对 $a$ 数组从小到大排序，$b$ 数组从大到小排序，最后计算对应元素乘积之和并取模。

【可拓展之处】
同类型题可能会改变函数 $f(l, r)$ 的定义或约束条件，类似算法套路是先分析每个元素的贡献，再利用排序不等式或贪心策略求解。

【推荐题目】
1. P1009 [NOIP1998 普及组] 阶乘之和
2. P1018 [NOIP2000 提高组] 乘积最大
3. P1029 [NOIP2001 普及组] 最大公约数和最小公倍数问题

【个人心得】
- OIerWu_829：注意取模的问题，坑了我好久。
总结：在处理大数运算时，取模的时机和方式很关键，不当的取模可能导致结果错误。
- Frozencode：这题一眼**排序不等式**，第$i$个位置会贡献$i*(n - i + 1)$次(乘法原理),于是写了个排$a[i]$之后再逆序排$b[i]$，两个乘起来再乘以贡献的次数，结果$WA\ Test\ 4$。然后就发现哪里不对了，事实上$a[i]$位置是固定的，所以排序不等式中的$a[i]$应该是$a[i]*i*(n - i + 1)$，这里需要特别注意的是，因为排序不等式中是要**最大的**配上**最小的**，所以在算排序不等式中的$a[i]$是**不能取模的！！！**（取模后最大的就不一定是最大的了，会$WA\ Test\ 5$）。
总结：使用排序不等式时，要准确确定参与排序的元素，且在排序前不能随意取模，以免影响元素大小关系。 

---
处理用时：39.63秒