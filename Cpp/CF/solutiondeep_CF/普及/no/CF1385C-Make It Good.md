# 题目信息

# Make It Good

## 题目描述

You are given an array $ a $ consisting of $ n $ integers. You have to find the length of the smallest (shortest) prefix of elements you need to erase from $ a $ to make it a good array. Recall that the prefix of the array $ a=[a_1, a_2, \dots, a_n] $ is a subarray consisting several first elements: the prefix of the array $ a $ of length $ k $ is the array $ [a_1, a_2, \dots, a_k] $ ( $ 0       \le k \le n $ ).

The array $ b $ of length $ m $ is called good, if you can obtain a non-decreasing array $ c $ ( $ c_1 \le c_2 \le \dots \le c_{m} $ ) from it, repeating the following operation $ m $ times (initially, $ c $ is empty):

- select either the first or the last element of $ b $ , remove it from $ b $ , and append it to the end of the array $ c $ .

For example, if we do $ 4 $ operations: take $ b_1 $ , then $ b_{m} $ , then $ b_{m-1} $ and at last $ b_2 $ , then $ b $ becomes $ [b_3, b_4, \dots, b_{m-3}] $ and $ c =[b_1,       b_{m}, b_{m-1}, b_2] $ .

Consider the following example: $ b = [1, 2, 3, 4, 4, 2, 1] $ . This array is good because we can obtain non-decreasing array $ c $ from it by the following sequence of operations:

1. take the first element of $ b $ , so $ b = [2, 3, 4, 4,         2, 1] $ , $ c = [1] $ ;
2. take the last element of $ b $ , so $ b = [2, 3, 4, 4,         2] $ , $ c = [1, 1] $ ;
3. take the last element of $ b $ , so $ b = [2, 3, 4, 4] $ , $ c = [1, 1, 2] $ ;
4. take the first element of $ b $ , so $ b = [3, 4, 4] $ , $ c = [1, 1, 2, 2] $ ;
5. take the first element of $ b $ , so $ b = [4, 4] $ , $ c         = [1, 1, 2, 2, 3] $ ;
6. take the last element of $ b $ , so $ b = [4] $ , $ c =         [1, 1, 2, 2, 3, 4] $ ;
7. take the only element of $ b $ , so $ b = [] $ , $ c = [1,         1, 2, 2, 3, 4, 4] $ — $ c $ is non-decreasing.

Note that the array consisting of one element is good.

Print the length of the shortest prefix of $ a $ to delete (erase), to make $ a $ to be a good array. Note that the required length can be $ 0 $ .

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, the array $ a $ is already good, so we don't need to erase any prefix.

In the second test case of the example, the initial array $ a $ is not good. Let's erase first $ 4 $ elements of $ a $ , the result is $ [4, 5, 2] $ . The resulting array is good. You can prove that if you erase fewer number of first elements, the result will not be good.

## 样例 #1

### 输入

```
5
4
1 2 3 4
7
4 3 3 8 4 5 2
3
1 1 1
7
1 3 1 4 5 3 2
5
5 4 3 2 3```

### 输出

```
0
4
0
2
3```

# AI分析结果

### 题目内容重写
# 使数组变好

## 题目描述

给定一个由 $n$ 个整数组成的数组 $a$。你需要找到需要删除的最短前缀的长度，使得删除后的数组成为一个“好”数组。数组的前缀是指数组的前 $k$ 个元素组成的子数组，$0 \le k \le n$。

一个长度为 $m$ 的数组 $b$ 被称为“好”数组，如果可以通过以下操作 $m$ 次（初始时 $c$ 为空），得到一个非递减的数组 $c$（$c_1 \le c_2 \le \dots \le c_{m}$）：

- 选择 $b$ 的第一个或最后一个元素，将其从 $b$ 中移除，并添加到 $c$ 的末尾。

例如，如果进行 $4$ 次操作：取 $b_1$，然后取 $b_{m}$，然后取 $b_{m-1}$，最后取 $b_2$，那么 $b$ 变为 $[b_3, b_4, \dots, b_{m-3}]$，而 $c = [b_1, b_{m}, b_{m-1}, b_2]$。

考虑以下例子：$b = [1, 2, 3, 4, 4, 2, 1]$。这个数组是“好”的，因为可以通过以下操作序列得到一个非递减的数组 $c$：

1. 取 $b$ 的第一个元素，$b = [2, 3, 4, 4, 2, 1]$，$c = [1]$；
2. 取 $b$ 的最后一个元素，$b = [2, 3, 4, 4, 2]$，$c = [1, 1]$；
3. 取 $b$ 的最后一个元素，$b = [2, 3, 4, 4]$，$c = [1, 1, 2]$；
4. 取 $b$ 的第一个元素，$b = [3, 4, 4]$，$c = [1, 1, 2, 2]$；
5. 取 $b$ 的第一个元素，$b = [4, 4]$，$c = [1, 1, 2, 2, 3]$；
6. 取 $b$ 的最后一个元素，$b = [4]$，$c = [1, 1, 2, 2, 3, 4]$；
7. 取 $b$ 的唯一元素，$b = []$，$c = [1, 1, 2, 2, 3, 4, 4]$ —— $c$ 是非递减的。

注意，只包含一个元素的数组也是“好”的。

输出需要删除的最短前缀的长度，使得 $a$ 成为一个“好”数组。注意，这个长度可以是 $0$。

你需要回答 $t$ 个独立的测试用例。

## 说明/提示

在第一个测试用例中，数组 $a$ 已经是“好”的，因此不需要删除任何前缀。

在第二个测试用例中，初始数组 $a$ 不是“好”的。删除前 $4$ 个元素后，得到 $[4, 5, 2]$，这个数组是“好”的。你可以证明，如果删除更少的前缀元素，结果将不是“好”的。

## 样例 #1

### 输入

```
5
4
1 2 3 4
7
4 3 3 8 4 5 2
3
1 1 1
7
1 3 1 4 5 3 2
5
5 4 3 2 3```

### 输出

```
0
4
0
2
3```

### 算法分类
贪心

### 题解分析与结论
题目要求找到需要删除的最短前缀，使得剩下的数组成为一个“好”数组。通过分析可以发现，“好”数组实际上是一个单峰数组（先递增后递减）。因此，问题转化为找到数组的最长单峰后缀，然后计算需要删除的前缀长度。

大部分题解都采用了从右向左扫描数组的方法，先找到峰值，然后再从峰值向左找到左端点，最终计算需要删除的前缀长度。这种方法的时间复杂度为 $O(n)$，效率较高。

### 精选题解

#### 题解1：作者：JACK_POT (赞：15)
**星级：5星**
**关键亮点：**
- 通过从右向左扫描数组，先找到峰值，再找到左端点，思路清晰。
- 代码简洁，时间复杂度为 $O(n)$。

**核心代码：**
```cpp
int k = n;
while (a[k - 1] >= a[k] && k > 1) k--; // 上山，直到山顶
while (a[k - 1] <= a[k] && k > 1) k--; // 下山
printf("%d\n", k - 1);
```

#### 题解2：作者：iMya_nlgau (赞：2)
**星级：4星**
**关键亮点：**
- 同样采用从右向左扫描的方法，思路与题解1一致。
- 代码简洁，时间复杂度为 $O(n)$。

**核心代码：**
```cpp
int k = n;
while (a[k - 1] >= a[k] && k > 1) k--;
while (a[k - 1] <= a[k] && k > 1) k--;
printf("%d\n", k - 1);
```

#### 题解3：作者：chenxia25 (赞：0)
**星级：4星**
**关键亮点：**
- 通过从右向左扫描数组，先找到峰值，再找到左端点，思路清晰。
- 代码简洁，时间复杂度为 $O(n)$。

**核心代码：**
```cpp
int las;
for (int i = n; i; i--) { // 找最左峰值
    if (i < n && a[i] < a[i + 1]) break;
    las = i;
}
int las0;
for (int i = las; i; i--) { // 找最左左端点
    if (i < las && a[i] > a[i + 1]) break;
    las0 = i;
}
cout << las0 - 1 << "\n";
```

### 最优关键思路与技巧
- **从右向左扫描**：通过从右向左扫描数组，先找到峰值，再找到左端点，可以高效地找到最长单峰后缀。
- **时间复杂度优化**：通过一次或两次遍历数组，时间复杂度为 $O(n)$，适合处理大规模数据。

### 可拓展之处
- **类似问题**：可以扩展到其他需要找到特定子数组的问题，如最长递增子序列、最长递减子序列等。
- **算法优化**：可以进一步优化代码，减少不必要的判断，提高代码执行效率。

### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)
3. [P1106 删数问题](https://www.luogu.com.cn/problem/P1106)

---
处理用时：52.82秒