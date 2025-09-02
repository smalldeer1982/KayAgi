# 题目信息

# Wonderful Randomized Sum

## 题目描述

Learn, learn and learn again — Valera has to do this every day. He is studying at mathematical school, where math is the main discipline. The mathematics teacher loves her discipline very much and tries to cultivate this love in children. That's why she always gives her students large and difficult homework. Despite that Valera is one of the best students, he failed to manage with the new homework. That's why he asks for your help. He has the following task. A sequence of $ n $ numbers is given. A prefix of a sequence is the part of the sequence (possibly empty), taken from the start of the sequence. A suffix of a sequence is the part of the sequence (possibly empty), taken from the end of the sequence. It is allowed to sequentially make two operations with the sequence. The first operation is to take some prefix of the sequence and multiply all numbers in this prefix by $ -1 $ . The second operation is to take some suffix and multiply all numbers in it by $ -1 $ . The chosen prefix and suffix may intersect. What is the maximum total sum of the sequence that can be obtained by applying the described operations?

## 样例 #1

### 输入

```
3
-1 -2 -3
```

### 输出

```
6
```

## 样例 #2

### 输入

```
5
-4 2 0 5 0
```

### 输出

```
11
```

## 样例 #3

### 输入

```
5
-1 10 -5 10 -2
```

### 输出

```
18
```

# AI分析结果



### 题目翻译
# Wonderful Randomized Sum

## 题目描述

给定一个包含 $n$ 个数字的序列，允许依次进行两个操作：  
1. 选择任意前缀（可为空）并翻转所有数字符号  
2. 选择任意后缀（可为空）并翻转所有数字符号  

求最终能获得的最大序列和。前缀和后缀允许相交，此时相交部分符号被翻转两次（等价于未改变）。

## 样例 #1

### 输入
```
3
-1 -2 -3
```

### 输出
```
6
```

---

### 题解分析与结论

#### 关键思路总结
1. **数学转化**：交叉部分等效未翻转，最终和为 $2C - S$（$C$ 为中间段和，$S$ 为原总和）
2. **最大子段和**：问题转化为求原数组的最大子段和（使用 Kadane 算法）
3. **公式推导**：最优解为 $2 \times maxSubarray - sum$

#### 高分题解推荐

1. **LuckyCloud（5星）**  
   **核心亮点**：  
   - 通过数学推导将问题转化为最大子段和问题  
   - 代码简洁高效（时间复杂度 $O(n)$）  
   **代码核心**：  
   ```cpp
   long long sum = 0, maxSub = 0, current = 0;
   for (int i=0; i<n; i++) {
       sum += a[i];
       current = max(current + a[i], 0LL);
       maxSub = max(maxSub, current);
   }
   cout << 2*maxSub - sum;
   ```

2. **_lxy_（5星）**  
   **核心亮点**：  
   - 清晰说明保留最大子段和的原理  
   - 代码极简，直接应用公式  
   **代码核心**：  
   ```cpp
   int sum=0, maxSub=0, current=0;
   while (n--) {
       cin >> x;
       sum += x;
       current = max(current + x, 0);
       maxSub = max(maxSub, current);
   }
   cout << 2*maxSub - sum;
   ```

3. **Level_Down（4星）**  
   **核心亮点**：  
   - 逆向思维将问题转化为求相反数后的最小子段和  
   - 代码简洁但需理解逆向推导  
   **代码核心**：  
   ```cpp
   int sum=0, maxSub=0, current=0;
   while (n--) {
       sum += x;
       current = max(current + x, 0);
       maxSub = max(maxSub, current);
   }
   cout << 2*maxSub - sum;
   ```

---

#### 拓展技巧
- **类似题型套路**：当操作具有抵消性（如双符号翻转）时，常转化为子段最值问题  
- **举一反三**：类似题目可考虑区间反转、子段选择等变形  

#### 推荐练习题
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
2. [P2642 双子序列最大和](https://www.luogu.com.cn/problem/P2642)  
3. [P4513 小白逛公园](https://www.luogu.com.cn/problem/P4513)  

#### 调试心得摘录
- **注意空子段处理**：部分题解需考虑全负数时的边界条件（如 Kadane 算法初始值设 0）  
- **类型溢出**：使用 `long long` 防止大数溢出（如题解中变量声明为 `long long`）

---
处理用时：55.49秒