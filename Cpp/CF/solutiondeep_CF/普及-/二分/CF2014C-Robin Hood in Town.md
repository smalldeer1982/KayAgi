# 题目信息

# Robin Hood in Town

## 题目描述

In Sherwood, we judge a man not by his wealth, but by his merit.



Look around, the rich are getting richer, and the poor are getting poorer. We need to take from the rich and give to the poor. We need Robin Hood!

There are $ n $ people living in the town. Just now, the wealth of the $ i $ -th person was $ a_i $ gold. But guess what? The richest person has found an extra pot of gold!

More formally, find an $ a_j=max(a_1, a_2, \dots, a_n) $ , change $ a_j $ to $ a_j+x $ , where $ x $ is a non-negative integer number of gold found in the pot. If there are multiple maxima, it can be any one of them.

A person is unhappy if their wealth is strictly less than half of the average wealth $ ^{\text{∗}} $ .

If strictly more than half of the total population $ n $ are unhappy, Robin Hood will appear by popular demand.

Determine the minimum value of $ x $ for Robin Hood to appear, or output $ -1 $ if it is impossible.

 $ ^{\text{∗}} $ The average wealth is defined as the total wealth divided by the total population $ n $ , that is, $ \frac{\sum a_i}{n} $ , the result is a real number.

## 说明/提示

In the first test case, it is impossible for a single person to be unhappy.

In the second test case, there is always $ 1 $ happy person (the richest).

In the third test case, no additional gold are required, so the answer is $ 0 $ .

In the fourth test case, after adding $ 15 $ gold, the average wealth becomes $ \frac{25}{4} $ , and half of this average is $ \frac{25}{8} $ , resulting in $ 3 $ people being unhappy.

In the fifth test case, after adding $ 16 $ gold, the average wealth becomes $ \frac{31}{5} $ , resulting in $ 3 $ people being unhappy.

## 样例 #1

### 输入

```
6
1
2
2
2 19
3
1 3 20
4
1 2 3 4
5
1 2 3 4 5
6
1 2 1 1 1 25```

### 输出

```
-1
-1
0
15
16
0```

# AI分析结果

### 题目内容重写（中文）

在舍伍德，我们不以财富评判一个人，而是以他的功绩。

看看周围，富人越来越富，穷人越来越穷。我们需要劫富济贫。我们需要罗宾汉！

镇上有 $n$ 个人。现在，第 $i$ 个人的财富是 $a_i$ 金币。但你知道吗？最富有的人找到了一个额外的金罐！

更正式地说，找到 $a_j=\max(a_1, a_2, \dots, a_n)$，将 $a_j$ 改为 $a_j+x$，其中 $x$ 是从金罐中找到的非负整数金币。如果有多个最大值，可以任选其中一个。

如果一个人的财富严格低于平均财富的一半，他就会感到不幸福。

如果超过一半的人口感到不幸福，罗宾汉就会应大家的要求出现。

确定让罗宾汉出现的最小 $x$ 值，或者输出 $-1$ 如果这不可能。

$^{\text{∗}}$ 平均财富定义为总财富除以总人口 $n$，即 $\frac{\sum a_i}{n}$，结果是一个实数。

### 题解分析与结论

这些题解大多采用了相似的思路，即通过排序和二分查找来确定最小的 $x$ 值。以下是各题解的主要思路和优化点：

1. **二分查找**：大多数题解都使用了二分查找来优化搜索过程，时间复杂度为 $O(n \log n)$。
2. **排序**：几乎所有题解都先对数组进行排序，以便快速找到中位数或进行其他计算。
3. **特判**：对于 $n \leq 2$ 的情况，所有题解都直接输出 $-1$，因为在这种情况下无法满足条件。
4. **数学推导**：部分题解通过数学推导直接计算出 $x$ 的值，避免了二分查找的复杂度。

### 评分较高的题解

#### 题解1：Temp113 (4星)
- **关键亮点**：使用二分查找，代码结构清晰，时间复杂度优化较好。
- **代码核心**：
  ```cpp
  bool check(int aa){
      tmp = a[n];
      a[n] += aa;
      s = 0;
      tot = 0;
      for(int i = 1; i <= n; i++) s += a[i];
      d = ((double) s) / n / 2;
      for(int i = 1; i <= n; i++) if(a[i] < d) tot++;
      a[n] = tmp;
      if(tot > ((double) n) / 2) return 1;
      else return 0;    
  }
  ```

#### 题解2：alan1118 (4星)
- **关键亮点**：通过数学推导直接计算 $x$，代码简洁，时间复杂度为 $O(n \log n)$。
- **代码核心**：
  ```cpp
  sort(a+1, a+n+1);
  LL p = a[n/2+1];
  LL m = p * 2 * n + 1;
  cout << max(0LL, m-sum) << endl;
  ```

#### 题解3：Karieciation (4星)
- **关键亮点**：通过数学公式直接计算 $x$，代码简洁，时间复杂度为 $O(n \log n)$。
- **代码核心**：
  ```cpp
  sort(a+1, a+1+n);
  ll v=(ll)a[n+2>>1]*n<<1;
  if(sum>v)
      puts("0");
  else
      printf("%lld\n",v-sum+1);
  ```

### 最优关键思路与技巧

1. **二分查找**：在需要确定最小 $x$ 值的情况下，二分查找是一种高效的搜索方法，尤其适用于大范围搜索。
2. **排序与中位数**：通过排序可以快速找到中位数，进而简化计算过程。
3. **数学推导**：通过数学公式直接计算 $x$ 的值，可以避免不必要的循环和判断，提高代码效率。

### 可拓展之处

1. **类似问题**：可以扩展到其他需要确定最小或最大值的场景，如资源分配、负载均衡等。
2. **算法优化**：可以进一步优化二分查找的边界条件，减少不必要的计算。

### 推荐题目

1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)

### 个人心得摘录

- **调试经历**：部分题解提到在调试过程中发现边界条件处理不当，导致结果错误，提醒我们在编写代码时要特别注意边界条件的处理。
- **踩坑教训**：有题解提到在计算过程中忘记开 `long long`，导致溢出错误，提醒我们在处理大数时要注意数据类型的选择。
- **顿悟感想**：通过数学推导直接计算 $x$ 的值，可以大大简化代码逻辑，提高代码的可读性和效率。

---
处理用时：33.73秒