# 题目信息

# Petr and Permutations

## 题目描述

Petr likes to come up with problems about randomly generated data. This time problem is about random permutation. He decided to generate a random permutation this way: he takes identity permutation of numbers from $ 1 $ to $ n $ and then $ 3n $ times takes a random pair of different elements and swaps them. Alex envies Petr and tries to imitate him in all kind of things. Alex has also come up with a problem about random permutation. He generates a random permutation just like Petr but swaps elements $ 7n+1 $ times instead of $ 3n $ times. Because it is more random, OK?!

You somehow get a test from one of these problems and now you want to know from which one.

## 说明/提示

Please note that the sample is not a valid test (because of limitations for $ n $ ) and is given only to illustrate input/output format. Your program still has to print correct answer to this test to get AC.

Due to randomness of input hacks in this problem are forbidden.

## 样例 #1

### 输入

```
5
2 4 5 1 3
```

### 输出

```
Petr
```

# AI分析结果

### 题目内容重写

#### Petr and Permutations

**题目描述**

Petr 喜欢提出关于随机生成数据的问题。这次的问题是关于随机排列的。他决定以这种方式生成一个随机排列：他取从 $1$ 到 $n$ 的恒等排列，然后随机选择一对不同的元素并交换它们，共进行 $3n$ 次交换。Alex 羡慕 Petr 并试图模仿他。Alex 也提出了一个关于随机排列的问题。他像 Petr 一样生成一个随机排列，但交换元素 $7n+1$ 次而不是 $3n$ 次。因为它更随机，对吧？

你得到了其中一个问题的测试数据，现在你想知道它是来自哪个问题的。

**说明/提示**

请注意，样例不是一个有效的测试（由于 $n$ 的限制），仅用于说明输入/输出格式。你的程序仍然需要正确回答此样例才能通过。

由于输入的随机性，本题禁止 hack。

**样例 #1**

**输入**

```
5
2 4 5 1 3
```

**输出**

```
Petr
```

---

### 题解综合分析与结论

本题的核心在于判断给定的排列是通过 $3n$ 次交换还是 $7n+1$ 次交换生成的。由于 $3n$ 和 $7n+1$ 的奇偶性不同，因此可以通过计算排列的逆序数的奇偶性或还原排列所需的交换次数的奇偶性来判断。

### 精选题解

#### 题解1：pufanyi (赞：14)

**星级：5星**

**关键亮点：**
- 使用贪心策略还原排列，计算交换次数的奇偶性。
- 时间复杂度为 $O(n)$，效率高。
- 代码简洁，思路清晰。

**核心代码：**
```cpp
int ans = 0;
for(int i = 1; i <= n; ++i)
{
    while(aa[i] != i)
    {
        swap(aa[aa[i]], aa[i]);
        ans++;
    }
}
if((n & 1) == (ans & 1)) // 判断奇偶性相同
    puts("Petr");
else
    puts("Um_nik");
```

**个人心得：**
通过贪心策略还原排列，计算交换次数的奇偶性，思路清晰且高效。

---

#### 题解2：Mr_Wu (赞：7)

**星级：4星**

**关键亮点：**
- 利用逆序数的奇偶性进行判断。
- 使用树状数组计算逆序数，时间复杂度为 $O(n \log n)$。
- 代码结构清晰，注释详细。

**核心代码：**
```cpp
for (int i = 1; i <= n; i++)
{
    ans = (ans + query(n) - query(a[i] - 1)) % 2; 
    insert(a[i], 1);
}
if ((ans - 3 * n) % 2 == 0) printf("Petr");
else printf("Um_nik");
```

**个人心得：**
通过树状数组计算逆序数，思路清晰，代码实现较为复杂但效率较高。

---

#### 题解3：duyi (赞：5)

**星级：4星**

**关键亮点：**
- 通过计算排列中元素与位置相同的个数来判断。
- 时间复杂度为 $O(n)$，代码简洁。
- 思路新颖，适合快速判断。

**核心代码：**
```cpp
int ans = 0;
for (int i = 1; i <= n; ++i) {
    ans += (p[i] == i);
}
if (n == 5 || ans > 2) {
    cout << "Petr" << endl;
} else {
    cout << "Um_nik" << endl;
}
```

**个人心得：**
通过计算排列中元素与位置相同的个数来判断，思路简单且高效。

---

### 最优关键思路或技巧

1. **奇偶性判断**：通过计算排列的逆序数或还原排列所需的交换次数的奇偶性，可以快速判断排列是通过 $3n$ 次还是 $7n+1$ 次交换生成的。
2. **贪心策略**：使用贪心策略还原排列，计算交换次数的奇偶性，时间复杂度为 $O(n)$。
3. **树状数组**：利用树状数组计算逆序数，时间复杂度为 $O(n \log n)$，适合大规模数据处理。

### 可拓展之处

- **逆序数计算**：逆序数的计算在排序、排列等问题中广泛应用，掌握其计算方法有助于解决类似问题。
- **贪心策略**：贪心策略在排列还原、交换次数计算等问题中具有高效性，适合快速求解。

### 推荐题目

1. [P1908 逆序对](https://www.luogu.com.cn/problem/P1908)
2. [P1966 火柴排队](https://www.luogu.com.cn/problem/P1966)
3. [P1774 最接近神的人](https://www.luogu.com.cn/problem/P1774)

这些题目都涉及到逆序数的计算或排列的交换操作，有助于巩固相关知识。

---
处理用时：40.97秒