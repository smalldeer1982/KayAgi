# 题目信息

# Replacement

## 题目描述

Little Petya very much likes arrays consisting of $ n $ integers, where each of them is in the range from $ 1 $ to $ 10^{9} $ , inclusive. Recently he has received one such array as a gift from his mother. Petya didn't like it at once. He decided to choose exactly one element from the array and replace it with another integer that also lies in the range from $ 1 $ to $ 10^{9} $ , inclusive. It is not allowed to replace a number with itself or to change no number at all.

After the replacement Petya sorted the array by the numbers' non-decreasing. Now he wants to know for each position: what minimum number could occupy it after the replacement and the sorting.

## 样例 #1

### 输入

```
5
1 2 3 4 5
```

### 输出

```
1 1 2 3 4
```

## 样例 #2

### 输入

```
5
2 3 4 5 6
```

### 输出

```
1 2 3 4 5
```

## 样例 #3

### 输入

```
3
2 2 2
```

### 输出

```
1 2 2
```

# AI分析结果



# Replacement

## 题目描述

小 Petya 非常喜欢由 $n$ 个整数组成的数组，其中每个整数的范围在 $1$ 到 $10^9$ 之间（含边界）。最近他收到了母亲送的一个这样的数组作为礼物。但 Petya 并不满意，他决定选择数组中的一个元素，将其替换为另一个在 $1$ 到 $10^9$ 范围内的整数（不允许替换为自身或不进行任何替换）。

替换后，Petya 将数组按非递减顺序排序。现在他想知道：在替换并排序后，每个位置可能出现的最小数值是多少？

## 样例 #1

### 输入
```
5
1 2 3 4 5
```

### 输出
```
1 1 2 3 4
```

## 样例 #2

### 输入
```
5
2 3 4 5 6
```

### 输出
```
1 2 3 4 5
```

## 样例 #3

### 输入
```
3
2 2 2
```

### 输出
```
1 2 2
```

---

**算法分类**：贪心、排序

---

### 题解分析与结论

所有题解均采用以下核心思路：
1. **排序后替换最大元素**：通过两次排序操作，第一次确定最大元素的位置，将其替换为尽可能小的值（1，若原值为1则改为2），第二次排序得到最终数组。
2. **特判处理**：当最大元素为1时，必须替换为2以避免与原值相同。

#### 最优题解亮点

1. **封禁用户（5星）**
   - **关键思路**：通过总和最小推导出替换最大元素的贪心策略，详细解释两次排序的必要性。
   - **代码优化**：使用三目运算符简化条件判断，关流加速提升IO效率。
   ```cpp
   sort(a, a+n); 
   a[n-1] = (a[n-1] == 1 ? 2 : 1); 
   sort(a, a+n);
   ```

2. **wkjwkj（4星）**
   - **调试经验**：通过反例指出未特判全1数组的错误，强调边界条件的重要性。
   ```cpp
   if (a[n] == 1) a[n] = 2; 
   else a[n] = 1;
   ```

3. **Eason_AC（4星）**
   - **简洁实现**：直接对排序后的数组操作，逻辑清晰无冗余。
   ```cpp
   sort(a + 1, a + n + 1);
   a[n] = (a[n] == 1 ? 2 : 1);
   sort(a + 1, a + n + 1);
   ```

---

### 关键技巧总结

1. **两次排序法**：第一次排序定位最大元素，替换后再次排序保证结果有序。
2. **贪心替换策略**：替换最大元素为最小可能值（1或2），确保全局最优。
3. **边界处理**：特判全1数组，避免替换无效。

---

### 拓展练习

1. **[CF455A Boredom](https://www.luogu.com.cn/problem/CF455A)**  
   （贪心策略选择，需处理元素替换后的影响）
2. **[P1106 删数问题](https://www.luogu.com.cn/problem/P1106)**  
   （贪心删除策略，类似最小字典序问题）
3. **[CF1353C Board Moves](https://www.luogu.com.cn/problem/CF1353C)**  
   （通过排序与数学推导优化操作步骤）

---
处理用时：67.26秒