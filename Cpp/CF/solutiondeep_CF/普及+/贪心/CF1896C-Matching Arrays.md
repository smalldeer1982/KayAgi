# 题目信息

# Matching Arrays

## 题目描述

You are given two arrays $ a $ and $ b $ of size $ n $ . The beauty of the arrays $ a $ and $ b $ is the number of indices $ i $ such that $ a_i > b_i $ .

You are also given an integer $ x $ . Determine whether it is possible to rearrange the elements of $ b $ such that the beauty of the arrays becomes $ x $ . If it is possible, output one valid rearrangement of $ b $ .

## 说明/提示

In test cases 1 and 2, the beauty of the arrays has to be $ 0 $ since $ a_1 = 1 \le 2 = b_1 $ .

In test cases 3, 4, 5 and 6, the only possible beauty of the arrays is $ x = 1 $ and $ x = 2 $ . In particular, if $ b $ is rearranged to $ [2, 4, 1] $ , then $ a_3 = 3 > 1 = b_3 $ , so the beauty of the arrays is $ 1 $ . If $ b $ is kept in the same order as given the input, then $ a_2 = 4 > b_2 = 1 $ and $ a_3 = 3 > 2 = b_3 $ , so the beauty of the arrays is $ 2 $ .

## 样例 #1

### 输入

```
7
1 0
1
2
1 1
1
2
3 0
2 4 3
4 1 2
3 1
2 4 3
4 1 2
3 2
2 4 3
4 1 2
3 3
2 4 3
4 1 2
5 2
6 4 5 6 2
9 7 9 1 1```

### 输出

```
YES
2
NO
NO
YES
2 4 1
YES
4 1 2
NO
YES
1 9 9 7 1```

# AI分析结果



### 中文题目重写

# Matching Arrays

## 题目描述

给定两个长度为 $n$ 的数组 $a$ 和 $b$。定义数组 $a$ 和 $b$ 的“美感”为满足 $a_i > b_i$ 的下标 $i$ 的数量。给定整数 $x$，判断是否能通过重排 $b$ 的元素使得美感恰好为 $x$。若可行，输出一种可能的 $b$ 的排列方式。

## 输入格式

输入包含多组测试数据。每组数据第一行为 $n$ 和 $x$，接下来两行分别为 $a$ 和 $b$ 的元素。

## 输出格式

对于每组数据，若可行则输出 "YES" 和重排后的 $b$，否则输出 "NO"。

---

### 题解分析与关键思路

#### 最优解法思路
**贪心策略**：
1. **降序排序 $a$**，保留原始索引以便构造答案。
2. **升序排序 $b$**，确保最小的 $x$ 个元素在前。
3. **验证前 $x$ 对**：将 $a$ 的前 $x$ 大元素（降序后前 $x$ 个）升序排列，与 $b$ 的前 $x$ 小元素逐个配对，确保每个 $a_i > b_i$。
4. **验证剩余部分**：将 $a$ 剩余元素升序排列，与 $b$ 的剩余元素升序配对，确保每个 $a_i \le b_i$。

#### 解决难点
1. **配对顺序的确定**：通过双重排序（$a$ 降序后部分升序）确保贪心策略的最优性。
2. **索引管理**：在排序过程中保留原始索引，以便最终输出正确的排列顺序。
3. **边界检查**：验证所有配对条件是否严格满足，避免遗漏。

#### 题解评分与亮点
1. **wxzzzz（4.5星）**  
   **亮点**：清晰的排序逻辑与双重检查，代码结构简洁。  
   **关键代码**：
   ```cpp
   bool solve() {
       sort(a + 1, a + n + 1, cmp1); // a降序排序
       sort(b + 1, b + n + 1);       // b升序排序
       sort(a + 1, a + m + 1, cmp2); // 前x部分升序

       for (int i = 1; i <= m; i++) { // 检查前x对
           if (a[i].val <= b[i]) return 0;
           ans[a[i].id] = b[i];
       }

       sort(a + m + 1, a + n + 1, cmp2); // 剩余部分升序
       for (int i = m + 1; i <= n; i++) { // 检查剩余对
           if (a[i].val > b[i]) return 0;
           ans[a[i].id] = b[i];
       }
       return 1;
   }
   ```

2. **Register_int（4星）**  
   **亮点**：使用 Lambda 表达式简化排序，代码紧凑。  
   **关键代码**：
   ```cpp
   sort(a + 1, a + n + 1, [](const node &p, const node &q) { return p.x < q.x; });
   for (int i = 1; i <= m; i++) // 检查前x对
       if (b[i] >= a[n - m + i].x) f = 1;
   ```

3. **Eazin_star（4星）**  
   **亮点**：结构体管理索引，配对逻辑清晰。  
   **关键代码**：
   ```cpp
   sort(a + 1, a + n + 1, cmp); // a升序排序
   for (int i = 1; i <= x; i++) 
       ans[a[n - x + i].id] = b[i]; // 前x大配前x小
   ```

---

### 关键技巧总结
- **双重排序**：先整体降序/升序，再局部调整排序顺序以满足配对条件。
- **索引保留**：通过结构体或额外数组记录原始位置，确保输出正确。
- **贪心验证**：严格检查每个配对的边界条件，确保无遗漏。

---

### 拓展练习
1. **CF1038D**（贪心与极值配对）
2. **CF1353D**（结构体排序与构造）
3. **Luogu P1102**（双指针与条件计数）

---
处理用时：189.64秒