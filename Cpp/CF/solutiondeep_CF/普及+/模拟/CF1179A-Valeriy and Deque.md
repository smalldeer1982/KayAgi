# 题目信息

# Valeriy and Deque

## 题目描述

Recently, on the course of algorithms and data structures, Valeriy learned how to use a deque. He built a deque filled with $ n $ elements. The $ i $ -th element is $ a_i $ ( $ i $ = $ 1, 2, \ldots, n $ ). He gradually takes the first two leftmost elements from the deque (let's call them $ A $ and $ B $ , respectively), and then does the following: if $ A > B $ , he writes $ A $ to the beginning and writes $ B $ to the end of the deque, otherwise, he writes to the beginning $ B $ , and $ A $ writes to the end of the deque. We call this sequence of actions an operation.

For example, if deque was $ [2, 3, 4, 5, 1] $ , on the operation he will write $ B=3 $ to the beginning and $ A=2 $ to the end, so he will get $ [3, 4, 5, 1, 2] $ .

The teacher of the course, seeing Valeriy, who was passionate about his work, approached him and gave him $ q $ queries. Each query consists of the singular number $ m_j $ $ (j = 1, 2, \ldots, q) $ . It is required for each query to answer which two elements he will pull out on the $ m_j $ -th operation.

Note that the queries are independent and for each query the numbers $ A $ and $ B $ should be printed in the order in which they will be pulled out of the deque.

Deque is a data structure representing a list of elements where insertion of new elements or deletion of existing elements can be made from both sides.

## 说明/提示

 Consider all 10 steps for the first test in detail:2. $ [1, 2, 3, 4, 5] $ — on the first operation, $ A $ and $ B $ are $ 1 $ and $ 2 $ , respectively.So, $ 2 $ we write to the beginning of the deque, and $ 1 $ — to the end.
  
  We get the following status of the deque: $ [2, 3, 4, 5, 1] $ .
3. $ [2, 3, 4, 5, 1] \Rightarrow A = 2, B = 3 $ .
4. $ [3, 4, 5, 1, 2] $
5. $ [4, 5, 1, 2, 3] $
6. $ [5, 1, 2, 3, 4] $
7. $ [5, 2, 3, 4, 1] $
8. $ [5, 3, 4, 1, 2] $
9. $ [5, 4, 1, 2, 3] $
10. $ [5, 1, 2, 3, 4] $
11. $ [5, 2, 3, 4, 1] \Rightarrow A = 5, B = 2 $ .

## 样例 #1

### 输入

```
5 3
1 2 3 4 5
1
2
10
```

### 输出

```
1 2
2 3
5 2
```

## 样例 #2

### 输入

```
2 0
0 0
```

### 输出

```
```

# AI分析结果



### 题目重述
#### Valeriy and De端队列

**题目描述**  
Valeriy 在算法课上学习了双端队列（deque）的使用。他构建了一个包含 $n$ 个元素的 deque，第 $i$ 个元素为 $a_i$（$i=1,2,\ldots,n$）。每次操作时，他会取出 deque 最前面的两个元素 $A$ 和 $B$：  
- 若 $A > B$，将 $A$ 放回前端，$B$ 放到后端  
- 否则将 $B$ 放回前端，$A$ 放到后端  

给定 $q$ 个查询，每个查询要求输出第 $m_j$ 次操作时取出的两个元素 $A$ 和 $B$。

**输入输出样例**  
样例1输入：  
5 3  
1 2 3 4 5  
1 2 10  

输出：  
1 2  
2 3  
5 2  

**数据范围**  
$1 \leq n,q \leq 10^5$，$1 \leq m_j \leq 10^{18}$

---

### 题解综合分析

#### 关键思路总结
1. **阶段分离**：操作分为两个阶段  
   - **预处理阶段**：暴力模拟直到最大值到达队首（最多 $O(n)$ 次）  
   - **循环阶段**：最大值固定在前端，后续元素形成长度为 $n-1$ 的循环节  

2. **循环节优化**：  
   - 记录前 $k$ 次操作的原始结果  
   - 大查询通过取模运算定位循环节位置：`(m-k) % (n-1)`

3. **数据结构选择**：  
   - 使用 deque 或数组模拟操作  
   - 预存循环元素序列避免重复计算

#### 优质题解推荐
1. **lemon2021（★★★★☆）**  
   **亮点**：完整错误调试记录 + 循环节预处理  
   **心得**：  
   > "不开long long见祖宗" —— 多次因数据类型错误WA  
   > 暴力模拟发现规律：最大值到队首后出现固定循环模式

2. **do_while_true（★★★★★）**  
   **亮点**：高效数组模拟 + 数学化表达  
   ```cpp
   while(a[1] != mx) { // 预处理阶段
       if(a[1] > a[p]) a[++pn] = a[p];
       else swap(a[1],a[p]), a[++pn] = a[p];
       ans1[p] = a[1]; ans2[p] = a[p+1];
       ++p;
   }
   // 循环阶段计算
   printf("%d %d\n",mx,a[p+((m-p+1)%(n-1)==0?(n-1):(m-p+1)%(n-1))]);
   ```

3. **gaoshengxiang（★★★★☆）**  
   **亮点**：结构体记录操作 + 清晰阶段分离  
   ```cpp
   struct node{ int fir, sec; } s[100005]; // 预处理记录
   if(y <= ans) cout << s[y].fir << s[y].sec; 
   else cout << smax << k[(y-ans)%(n-1)]; // 循环节定位
   ```

---

### 同类题目推荐
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886) - 单调队列维护极值  
2. [P1996 约瑟夫问题](https://www.luogu.com.cn/problem/P1996) - 循环队列模拟  
3. [CF1110E Magic Stones](https://www.luogu.com.cn/problem/CF1110E) - 观察操作后的序列变化规律

---
处理用时：45.01秒