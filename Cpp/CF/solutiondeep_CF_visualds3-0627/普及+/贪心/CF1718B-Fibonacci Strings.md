# 题目信息

# Fibonacci Strings

## 题目描述

In all schools in Buryatia, in the $ 1 $ class, everyone is told the theory of Fibonacci strings.

"A block is a subsegment of a string where all the letters are the same and are bounded on the left and right by the ends of the string or by letters other than the letters in the block. A string is called a Fibonacci string if, when it is divided into blocks, their lengths in the order they appear in the string form the Fibonacci sequence ( $ f_0 = f_1 = 1 $ , $ f_i = f_{i-2} + f_{i-1} $ ), starting from the zeroth member of this sequence. A string is called semi-Fibonacci if it possible to reorder its letters to get a Fibonacci string."

Burenka decided to enter the Buryat State University, but at the entrance exam she was given a difficult task. She was given a string consisting of the letters of the Buryat alphabet (which contains exactly $ k $ letters), and was asked if the given string is semi-Fibonacci. The string can be very long, so instead of the string, she was given the number of appearances of each letter ( $ c_i $ for the $ i $ -th letter) in that string. Unfortunately, Burenka no longer remembers the theory of Fibonacci strings, so without your help she will not pass the exam.

## 说明/提示

In the first test case, a one-character string is semi-Fibonacci, being itself a Fibonacci string.

In the second test case, a string of two different characters is Fibonacci.

In the third test case, the string "abb" (let the first of the alphabet letter be a, the second letter b) is not a semi-Fibonacci string, since no permutation of its letters ("abb", "bab", and "bba") is a Fibonacci string.

In the fourth test case, two permutations of the letters of the string "abaccac" (the first letter is a, the second letter is b, the third letter is c) are Fibonacci strings — "abaaccc" and "cbccaaa".

## 样例 #1

### 输入

```
6
1
1
2
1 1
2
1 2
3
3 1 3
2
7 5
6
26 8 3 4 13 34```

### 输出

```
YES
YES
NO
YES
NO
YES```

# AI分析结果



### 题解思路、算法要点与解决难点

1. **核心贪心思路**：
   - **总和要求**：首先验证总字符数是否为斐波那契前缀和。若非，直接返回 `NO`。
   - **贪心分配**：从最大的斐波那契数开始，每次选择剩余最多的字符，且不能与上一次选中的字符重复。
   - **正确性保证**：若当前字符数扣除斐波那契数后剩余值超过次大字符数，则无法避免重复分配，返回 `NO`。

2. **数据结构与实现**：
   - **优先队列/堆**：动态维护当前各字符的剩余数量，快速获取最大值。
   - **排序策略**：每次处理后将字符数组重新排序，确保后续选择正确。

3. **难点解决**：
   - **总和匹配**：预处理斐波那契前缀和，快速判断合法性。
   - **避免连续选择**：记录上一次选中的字符类型，强制切换。
   - **剩余值验证**：扣除后若剩余值超过次大值，无法满足后续分配，直接失败。

---

### 题解评分（≥4星）

1. **happy_dengziyue（★★★★☆）**
   - **亮点**：清晰使用优先队列处理最大值，代码简洁，证明思路详细。
   - **改进点**：未显式处理连续选择的冲突，可能导致部分情况漏判。

2. **Alex_Wei（★★★★★）**
   - **亮点**：数学证明严谨，排序策略高效，处理剩余值的逻辑严密。
   - **代码**：通过排序和直接操作数组，避免堆的频繁调整，时间复杂度更优。

3. **YBaggio（★★★★☆）**
   - **亮点**：结合堆和延迟插入策略，有效处理重复选择问题。
   - **可视化友好**：通过队列操作模拟分配过程，适合动态演示。

---

### 最优思路提炼

1. **前缀和验证**：总字符数必须为斐波那契前缀和。
2. **倒序贪心分配**：从最大斐波那契数开始，优先分配剩余最多的字符。
3. **冲突避免**：
   - 记录上一次分配的字符类型，强制切换。
   - 若扣除后剩余值超过次大值，立即判定失败。

---

### 同类型题与算法套路

- **贪心分配问题**：如区间调度、任务分配、背包问题。
- **常见套路**：
  - 倒序处理（如“柠檬水找零”中的大额优先）。
  - 动态维护最大值（优先队列或排序）。

---

### 推荐题目

1. **P1090 合并果子**：优先队列实现最小代价合并。
2. **P1223 排队接水**：贪心排序策略求最小等待时间。
3. **P5019 铺设道路**：区间贪心覆盖问题。

---

### 可视化与算法演示

1. **动画设计**：
   - **倒序分配**：从右向左依次填充斐波那契数，高亮当前块。
   - **颜色标记**：当前选中字符用红色，上一次选中用灰色，冲突时闪烁警示。
   - **步进控制**：允许单步执行观察每一步的分配逻辑。

2. **复古游戏化**：
   - **像素风格**：字符块以8位像素显示，分配时播放“吃豆人”音效。
   - **连击积分**：每次成功分配增加积分，连续正确触发连击奖励。

---

### 核心代码片段

```cpp
// Alex_Wei 的排序策略核心代码
sort(c + 1, c + n + 1);
for (int i = p; i >= 0; --i) {
    c[n] -= f[i];
    if (c[n] < 0 || c[n] > c[n - 1]) return NO;
    // 重新排序确保下次选择正确
    for (int j = n; j > 1; --j)
        if (c[j] < c[j - 1]) swap(c[j], c[j - 1]);
}
```

---

### 总结

通过倒序贪心分配和动态维护最大值，结合数学证明确保正确性。优先队列或排序策略均可高效实现，关键在于正确处理剩余值和冲突避免。可视化设计通过步进和颜色标记强化理解，游戏化元素提升学习趣味性。

---
处理用时：110.49秒