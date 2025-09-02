# 题目信息

# Minimize the error

## 题目描述

You are given two arrays $ A $ and $ B $ , each of size $ n $ . The error, $ E $ , between these two arrays is defined ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF960B/e950d33ee993b9f2e2ad61182c68b371192cc68e.png). You have to perform exactly $ k_{1} $ operations on array $ A $ and exactly $ k_{2} $ operations on array $ B $ . In one operation, you have to choose one element of the array and increase or decrease it by $ 1 $ .

Output the minimum possible value of error after $ k_{1} $ operations on array $ A $ and $ k_{2} $ operations on array $ B $ have been performed.

## 说明/提示

In the first sample case, we cannot perform any operations on $ A $ or $ B $ . Therefore the minimum possible error $ E=(1-2)^{2}+(2-3)^{2}=2 $ .

In the second sample case, we are required to perform exactly one operation on $ A $ . In order to minimize error, we increment the first element of $ A $ by $ 1 $ . Now, $ A=[2,2] $ . The error is now $ E=(2-2)^{2}+(2-2)^{2}=0 $ . This is the minimum possible error obtainable.

In the third sample case, we can increase the first element of $ A $ to $ 8 $ , using the all of the $ 5 $ moves available to us. Also, the first element of $ B $ can be reduced to $ 8 $ using the $ 6 $ of the $ 7 $ available moves. Now $ A=[8,4] $ and $ B=[8,4] $ . The error is now $ E=(8-8)^{2}+(4-4)^{2}=0 $ , but we are still left with $ 1 $ move for array $ B $ . Increasing the second element of $ B $ to $ 5 $ using the left move, we get $ B=[8,5] $ and $ E=(8-8)^{2}+(4-5)^{2}=1 $ .

## 样例 #1

### 输入

```
2 0 0
1 2
2 3
```

### 输出

```
2```

## 样例 #2

### 输入

```
2 1 0
1 2
2 2
```

### 输出

```
0```

## 样例 #3

### 输入

```
2 5 7
3 4
14 4
```

### 输出

```
1```

# AI分析结果

### 题目内容翻译

给定两个大小为 $n$ 的数组 $A$ 和 $B$，定义它们之间的误差 $E$ 为 $\sum_{i=1}^{n} (A_i - B_i)^2$。你需要对数组 $A$ 进行恰好 $k_1$ 次操作，对数组 $B$ 进行恰好 $k_2$ 次操作。每次操作可以选择数组中的一个元素，将其增加或减少 $1$。请输出在完成所有操作后，误差 $E$ 的最小可能值。

### 样例 #1

#### 输入
```
2 0 0
1 2
2 3
```

#### 输出
```
2
```

### 样例 #2

#### 输入
```
2 1 0
1 2
2 2
```

#### 输出
```
0
```

### 样例 #3

#### 输入
```
2 5 7
3 4
14 4
```

#### 输出
```
1
```

---

### 题解分析与结论

#### 思路总结
所有题解的核心思路都是将 $k_1$ 和 $k_2$ 合并为 $k = k_1 + k_2$，然后通过贪心策略，每次选择 $A$ 和 $B$ 中差值最大的元素进行操作，以减少误差。使用优先队列（堆）来维护这些差值，确保每次操作都能最大程度地减少误差。

#### 关键难点
1. **操作次数的合并**：由于对 $A$ 和 $B$ 的操作是等价的，可以将 $k_1$ 和 $k_2$ 合并为 $k$，简化问题。
2. **贪心策略的正确性**：每次选择差值最大的元素进行操作，确保每次操作都能最大程度地减少误差。
3. **优先队列的使用**：通过优先队列维护差值，确保每次都能快速找到最大值。

#### 最优思路
1. **合并操作次数**：将 $k_1$ 和 $k_2$ 合并为 $k$，简化问题。
2. **贪心策略**：每次选择差值最大的元素进行操作，确保每次操作都能最大程度地减少误差。
3. **优先队列**：使用优先队列维护差值，确保每次都能快速找到最大值。

#### 代码实现
```cpp
priority_queue<int> q;
for (int i = 1; i <= n; i++) q.push(abs(A[i] - B[i]));
for (int i = 1; i <= k; i++) {
    int t = q.top(); q.pop();
    if (t > 0) t--;
    else t++;
    q.push(t);
}
long long ans = 0;
while (!q.empty()) {
    ans += (long long)q.top() * q.top();
    q.pop();
}
cout << ans << endl;
```

#### 可拓展之处
1. **类似问题**：可以扩展到多个数组的操作，或者操作次数不固定的情况。
2. **其他优化**：可以考虑使用更高效的数据结构来维护差值，如斐波那契堆。

#### 推荐题目
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)
2. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
3. [P1168 中位数](https://www.luogu.com.cn/problem/P1168)

#### 个人心得摘录
- **调试经历**：在操作次数用完后，如果所有差值都为 $0$，仍然需要进行操作，否则会出错。
- **踩坑教训**：一定要开 `long long`，否则会溢出。
- **顿悟感想**：贪心策略的正确性可以通过数学证明，每次操作都能最大程度地减少误差。

---

### 精选题解

#### 题解1：DarkShadow (5星)
- **关键亮点**：思路清晰，代码简洁，使用优先队列维护差值，确保每次操作都能最大程度地减少误差。
- **代码实现**：
```cpp
priority_queue<int> q;
for (int i = 1; i <= n; i++) q.push(abs(A[i] - B[i]));
for (int i = 1; i <= k; i++) {
    int t = q.top(); q.pop();
    if (t > 0) t--;
    else t++;
    q.push(t);
}
long long ans = 0;
while (!q.empty()) {
    ans += (long long)q.top() * q.top();
    q.pop();
}
cout << ans << endl;
```

#### 题解2：w33z8kqrqk8zzzx33 (4星)
- **关键亮点**：详细解释了优先队列的使用方法，代码可读性强，适合初学者理解。
- **代码实现**：
```cpp
priority_queue<int> pq;
for (int i = 1; i <= n; i++) pq.push(abs(A[i] - B[i]));
while (k--) {
    int t = pq.top(); pq.pop();
    if (t == 0) pq.push(1);
    else pq.push(t - 1);
}
long long ans = 0;
while (!pq.empty()) {
    ans += 1ll * pq.top() * pq.top();
    pq.pop();
}
cout << ans << endl;
```

#### 题解3：ChenJr (4星)
- **关键亮点**：代码简洁，思路清晰，适合快速实现。
- **代码实现**：
```cpp
priority_queue<int> q;
for (int i = 1; i <= n; i++) q.push(abs(A[i] - B[i]));
while (k--) {
    int t = q.top(); q.pop();
    q.push(abs(t - 1));
}
long long ans = 0;
while (!q.empty()) {
    ans += 1ll * q.top() * q.top();
    q.pop();
}
cout << ans << endl;
```

---
处理用时：48.28秒