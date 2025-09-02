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



### 中文重写题目
#### 题目名称：神奇随机和

**题目描述**  
瓦莱拉每天都要不断学习数学。今天，他遇到了一个难题：给定一个包含 $n$ 个数字的序列，允许依次进行两次操作：  
1. 选择任意前缀（可为空），将该前缀中所有数字乘以 $-1$  
2. 选择任意后缀（可为空），将该后缀中所有数字乘以 $-1$  

前缀和后缀允许重叠。求经过操作后能得到的序列最大总和。

**输入样例**  
样例1：  
3  
-1 -2 -3  
输出：6  

样例2：  
5  
-4 2 0 5 0  
输出：11  

样例3：  
5  
-1 10 -5 10 -2  
输出：18  

---

### 题解综合分析

#### 关键思路总结
通过数学分析发现，交叉部分符号变化相互抵消，问题等价于寻找一个中间子段保持原值，其余部分取反。最优解公式为 `2*最大子段和 - 总和`，时间复杂度 $O(n)$。

#### 高星题解推荐
1. **LuckyCloud（★★★★★）**
   - **核心亮点**：通过严谨数学推导将问题转化为最大子段和，代码简洁高效
   - **代码核心**：
     ```cpp
     // 求最大子段和
     for (int i=1;i<=n;i++) {
         if (S+a[i]<0) S=0;
         else {S+=a[i]; Max=max(Max,S);}
     }
     ans = Max*2 - sum;  // 套用公式
     ```

2. **Level_Down（★★★★★）**
   - **核心亮点**：逆向思维将问题转化为求原序列最大子段和，代码极简
   - **代码亮点**：
     ```cpp
     // 单次遍历同时计算总和与最大子段和
     for(int i=1;i<=n;i++) {
         sum += a[i];
         ans2 = max(ans2 + a[i], 0);
         ans = max(ans, ans2);
     }
     ```

3. **Z_M__（★★★★）**
   - **亮点补充**：通过数论视角解释公式合理性，提供完整数学证明
   - **公式推导**：
     ```cpp
     sum = l + mid + r       // 原序列总和
     ans = (-l) + mid + (-r) = 2*mid - sum
     ```

#### 关键实现技巧
- **滚动求子段和**：使用临时变量累计子段和，负数时重置
- **在线计算**：在读取输入时同步计算总和和子段和，节省内存
- **公式直接应用**：避免复杂预处理，直接套用推导公式

---

### 拓展训练
**相似题目推荐**  
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
2. [P1121 环状最大子段和](https://www.luogu.com.cn/problem/P1121)  
3. [P1982 反转前缀后缀](https://www.luogu.com.cn/problem/P1982)（改编自同类型题）

**思维拓展**  
当操作次数增加时，可考虑动态规划保存状态；若允许k次操作，可转化为分层最短路问题。

---
处理用时：38.20秒