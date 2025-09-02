# 题目信息

# Maximal Continuous Rest

## 题目描述

Each day in Berland consists of $ n $ hours. Polycarp likes time management. That's why he has a fixed schedule for each day — it is a sequence $ a_1, a_2, \dots, a_n $ (each $ a_i $ is either $ 0 $ or $ 1 $ ), where $ a_i=0 $ if Polycarp works during the $ i $ -th hour of the day and $ a_i=1 $ if Polycarp rests during the $ i $ -th hour of the day.

Days go one after another endlessly and Polycarp uses the same schedule for each day.

What is the maximal number of continuous hours during which Polycarp rests? It is guaranteed that there is at least one working hour in a day.

## 说明/提示

In the first example, the maximal rest starts in last hour and goes to the first hour of the next day.

In the second example, Polycarp has maximal rest from the $ 4 $ -th to the $ 5 $ -th hour.

In the third example, Polycarp has maximal rest from the $ 3 $ -rd to the $ 5 $ -th hour.

In the fourth example, Polycarp has no rest at all.

## 样例 #1

### 输入

```
5
1 0 1 0 1
```

### 输出

```
2
```

## 样例 #2

### 输入

```
6
0 1 0 1 1 0
```

### 输出

```
2
```

## 样例 #3

### 输入

```
7
1 0 1 1 1 0 1
```

### 输出

```
3
```

## 样例 #4

### 输入

```
3
0 0 0
```

### 输出

```
0
```

# AI分析结果



# Maximal Continuous Rest

## 题目描述

在 Berland 的每一天由 $n$ 小时组成。Polycarp 喜欢时间管理，因此他有一个固定的每日作息表，这是一个由 $0$ 和 $1$ 组成的序列 $a_1, a_2, \dots, a_n$，其中 $a_i=0$ 表示第 $i$ 小时工作，$a_i=1$ 表示休息。由于天数无限循环，需要找到 Polycarp 最长的连续休息小时数（允许跨天连接）。题目保证每天至少有一个工作小时。

## 算法分类
模拟

---

## 题解对比与结论

### 最优解法总结
环形数组问题可通过两种核心思路解决：
1. **破环成链**：将数组复制拼接成两倍长度，转化为普通线性数组的最长连续 1 问题。
2. **首尾两次遍历**：分别计算中间段最长 1、前缀 1 长度和后缀 1 长度，取首尾连接后的最大值。

### 高星题解推荐

#### 1. 作者：FP·荷兰猪（★★★★★）
**关键亮点**：  
- 空间复杂度 O(1)，仅需两次遍历  
- 分离处理中间段和环形首尾连接情况  
- 代码清晰，逻辑简洁  

**核心代码**：
```cpp
int maxv = 0, cnt = 0;
for (int i=1; i<=n; i++) {
    if (a[i]) cnt++;
    else cnt = 0;
    maxv = max(maxv, cnt);
}
int cnt2 = 0;
for (int i=1; i<=n && a[i]; i++) cnt2++; // 前缀连续1
for (int i=n; i>=1 && a[i]; i--) cnt2++; // 后缀连续1
cout << max(maxv, cnt2);
```

#### 2. 作者：zhy12138（★★★★☆）
**关键亮点**：  
- 显式处理首尾连接的特殊情况  
- 通过分段统计避免空间浪费  

**核心代码**：
```cpp
int ans = 0, num = 0;
for (int i=1; i<=n; i++) {
    if (a[i]) num++;
    else ans = max(ans, num), num = 0;
}
ans = max(ans, num); // 中间段最长
int pre = 0, suf = 0;
for (int i=1; i<=n && a[i]; i++) pre++; // 前缀
for (int i=n; i>=1 && a[i]; i--) suf++; // 后缀
cout << max(ans, pre + suf);
```

#### 3. 作者：happybob（★★★★☆）
**关键亮点**：  
- 破环成链模板化处理  
- 代码结构高度标准化，易于理解  

**核心代码**：
```cpp
int a[400005]; // 双倍空间
for (int i=1; i<=n; i++) a[i+n] = a[i]; // 复制数组
int max_len = 0, cur = 0;
for (int i=1; i<=2*n; i++) {
    if (a[i]) cur++;
    else max_len = max(max_len, cur), cur = 0;
}
cout << max(max_len, cur); // 处理全1特殊情况
```

---

## 关键思路与技巧
1. **环形数组处理**：当问题涉及环形结构时，优先考虑破环成链或首尾分段统计两种经典方法。
2. **空间优化**：若允许修改输入数组，可通过两次遍历实现 O(1) 空间复杂度。
3. **边界处理**：特别注意全 1 或全 0 的特殊情况（本题已保证至少一个 0）。

---

## 相似题目推荐
1. [P1888 滑动窗口](https://www.luogu.com.cn/problem/P1888) - 环形窗口处理  
2. [P1115 最大子段和（环形版）](https://www.luogu.com.cn/problem/P1115) - 环形数组最大子段和  
3. [CF1360E 射击游戏](https://codeforces.com/problemset/problem/1360/E) - 环形路径模拟

---
处理用时：143.93秒