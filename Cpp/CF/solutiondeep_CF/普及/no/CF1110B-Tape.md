# 题目信息

# Tape

## 题目描述

You have a long stick, consisting of $ m $ segments enumerated from $ 1 $ to $ m $ . Each segment is $ 1 $ centimeter long. Sadly, some segments are broken and need to be repaired.

You have an infinitely long repair tape. You want to cut some pieces from the tape and use them to cover all of the broken segments. To be precise, a piece of tape of integer length $ t $ placed at some position $ s $ will cover segments $ s, s+1, \ldots, s+t-1 $ .

You are allowed to cover non-broken segments; it is also possible that some pieces of tape will overlap.

Time is money, so you want to cut at most $ k $ continuous pieces of tape to cover all the broken segments. What is the minimum total length of these pieces?

## 说明/提示

In the first example, you can use a piece of length $ 11 $ to cover the broken segments $ 20 $ and $ 30 $ , and another piece of length $ 6 $ to cover $ 75 $ and $ 80 $ , for a total length of $ 17 $ .

In the second example, you can use a piece of length $ 4 $ to cover broken segments $ 1 $ , $ 2 $ and $ 4 $ , and two pieces of length $ 1 $ to cover broken segments $ 60 $ and $ 87 $ .

## 样例 #1

### 输入

```
4 100 2
20 30 75 80
```

### 输出

```
17
```

## 样例 #2

### 输入

```
5 100 3
1 2 4 60 87
```

### 输出

```
6
```

# AI分析结果

### 题目重写
# 胶带

## 题目描述

你有一根长棍，由 $m$ 个从 $1$ 到 $m$ 编号的段组成。每段长度为 $1$ 厘米。不幸的是，有些段损坏了，需要修复。

你有一卷无限长的修复胶带。你想从胶带上剪下一些片段，并用它们覆盖所有损坏的段。具体来说，长度为整数 $t$ 的胶带片段放置在位置 $s$ 时，将覆盖段 $s, s+1, \ldots, s+t-1$。

你可以覆盖未损坏的段；胶带片段之间也可以重叠。

时间就是金钱，因此你希望最多使用 $k$ 段连续的胶带来覆盖所有损坏的段。这些胶带片段的总长度最小是多少？

## 说明/提示

在第一个样例中，你可以使用一段长度为 $11$ 的胶带覆盖损坏的段 $20$ 和 $30$，并使用另一段长度为 $6$ 的胶带覆盖段 $75$ 和 $80$，总长度为 $17$。

在第二个样例中，你可以使用一段长度为 $4$ 的胶带覆盖损坏的段 $1$、$2$ 和 $4$，并使用两段长度为 $1$ 的胶带覆盖损坏的段 $60$ 和 $87$。

## 样例 #1

### 输入

```
4 100 2
20 30 75 80
```

### 输出

```
17
```

## 样例 #2

### 输入

```
5 100 3
1 2 4 60 87
```

### 输出

```
6
```

### 算法分类
贪心

### 题解分析与结论
本题的核心思路是通过贪心算法，选择相邻损坏段之间的最小间隔进行合并，从而减少胶带的使用数量，最终达到最小化总长度的目的。所有题解都采用了类似的思路，即计算相邻损坏段之间的间隔，排序后选择前 $n-k$ 个最小的间隔进行合并。

### 所选高分题解
1. **作者：chenlingxi (赞：3)**  
   - **星级：4**  
   - **关键亮点**：思路清晰，代码简洁，直接通过排序相邻间隔并选择前 $k-1$ 个最大的间隔进行合并，减少了总长度。  
   - **代码核心**：
     ```cpp
     int num = a[n] - a[1] + 1;
     for (int i = 2; i <= n; ++i) sum[i] = a[i] - 1 - a[i-1];
     sort(sum + 2, sum + n + 1, cmp);
     for (int i = 2; i <= s; ++i) num -= sum[i];
     cout << num;
     ```

2. **作者：installb (赞：2)**  
   - **星级：4**  
   - **关键亮点**：通过将问题转化为选择最小的 $n-k$ 个间隔进行合并，思路清晰，代码实现简洁。  
   - **代码核心**：
     ```cpp
     k = n - k;
     for (int i = 1; i <= n; ++i) dl[i - 1] = l[i] - l[i - 1] - 1;
     sort(dl + 1, dl + n);
     for (int i = 1; i <= k; ++i) sum += dl[i];
     cout << sum + n;
     ```

3. **作者：Zechariah (赞：1)**  
   - **星级：4**  
   - **关键亮点**：通过贪心策略，选择最小的 $n-k$ 个间隔进行合并，代码简洁且易于理解。  
   - **代码核心**：
     ```cpp
     for (int i = 1; i != n; ++i) t[i] = b[i + 1] - b[i] - 1;
     sort(t + 1, t + n);
     for (int i = 1; i <= n - k; ++i) ans += t[i];
     cout << ans + n;
     ```

### 最优关键思路
通过计算相邻损坏段之间的间隔，排序后选择前 $n-k$ 个最小的间隔进行合并，从而减少胶带的使用数量，最终达到最小化总长度的目的。

### 拓展思路
类似的问题可以出现在区间覆盖、线段合并等场景中，通常可以通过贪心算法进行优化。例如，在覆盖多个区间时，选择最小区间进行合并，以减少总长度或总数量。

### 推荐题目
1. [P1884 线段覆盖](https://www.luogu.com.cn/problem/P1884)
2. [P1803 线段覆盖](https://www.luogu.com.cn/problem/P1803)
3. [P1208 线段覆盖](https://www.luogu.com.cn/problem/P1208)

---
处理用时：29.23秒