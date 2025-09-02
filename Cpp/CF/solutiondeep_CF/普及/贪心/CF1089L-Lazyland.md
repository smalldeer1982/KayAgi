# 题目信息

# Lazyland

## 题目描述

The kingdom of Lazyland is the home to $ n $ idlers. These idlers are incredibly lazy and create many problems to their ruler, the mighty King of Lazyland.

Today $ k $ important jobs for the kingdom ( $ k \le n $ ) should be performed. Every job should be done by one person and every person can do at most one job. The King allowed every idler to choose one job they wanted to do and the $ i $ -th idler has chosen the job $ a_i $ .

Unfortunately, some jobs may not be chosen by anyone, so the King has to persuade some idlers to choose another job. The King knows that it takes $ b_i $ minutes to persuade the $ i $ -th idler. He asked his minister of labour to calculate the minimum total time he needs to spend persuading the idlers to get all the jobs done. Can you help him?

## 说明/提示

In the first example the optimal plan is to persuade idlers 1, 6, and 8 to do jobs 2, 4, and 6.

In the second example each job was chosen by some idler, so there is no need to persuade anyone.

## 样例 #1

### 输入

```
8 7
1 1 3 1 5 3 7 1
5 7 4 8 1 3 5 2
```

### 输出

```
10
```

## 样例 #2

### 输入

```
3 3
3 1 2
5 3 4
```

### 输出

```
0
```

# AI分析结果

### 题目内容重写

#### 题目描述

Lazyland 王国是 $n$ 个懒人的家园。这些懒人非常懒惰，给他们的统治者——Lazyland 的国王带来了许多问题。

今天，王国需要完成 $k$ 项重要工作（$k \le n$）。每项工作需要由一个人完成，且每个人最多只能完成一项工作。国王允许每个懒人选择一项他们想要做的工作，第 $i$ 个懒人选择了工作 $a_i$。

不幸的是，有些工作可能没有被任何人选择，因此国王需要说服一些懒人选择其他工作。国王知道，说服第 $i$ 个懒人需要花费 $b_i$ 分钟。他要求劳动部长计算完成所有工作所需的最少总时间。你能帮助他吗？

#### 说明/提示

在第一个样例中，最优方案是说服第 1、6、8 个懒人分别去做第 2、4、6 项工作。

在第二个样例中，每项工作都有人选择，因此不需要说服任何人。

#### 样例 #1

##### 输入

```
8 7
1 1 3 1 5 3 7 1
5 7 4 8 1 3 5 2
```

##### 输出

```
10
```

#### 样例 #2

##### 输入

```
3 3
3 1 2
5 3 4
```

##### 输出

```
0
```

---

### 题解分析与结论

#### 综合分析

本题的核心是通过贪心策略，选择说服时间最短的懒人去完成未被选择的工作。所有题解都采用了贪心算法，但实现细节有所不同。大多数题解使用结构体存储懒人的选择和工作，并通过排序来选择最优的懒人进行说服。

#### 最优关键思路

1. **贪心策略**：优先选择说服时间最短的懒人去完成未被选择的工作。
2. **数据结构**：使用结构体存储懒人的选择和工作，便于排序和处理。
3. **桶记录**：通过桶数组记录每项工作被选择的次数，便于判断哪些工作需要说服懒人。

#### 可拓展之处

- **类似问题**：类似的问题可以扩展到资源分配、任务调度等领域，贪心策略在这些问题中也有广泛应用。
- **优化思路**：可以通过优先队列（堆）进一步优化选择过程，减少排序的时间复杂度。

#### 推荐题目

1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)
2. [P1223 排队接水](https://www.luogu.com.cn/problem/P1223)
3. [P1803 凌乱的yyy / 线段覆盖](https://www.luogu.com.cn/problem/P1803)

---

### 精选题解

#### 题解1：Molina

**星级**：★★★★☆  
**关键亮点**：代码结构清晰，使用桶数组记录工作选择次数，排序后直接选择最优懒人进行说服。

**核心代码**：
```cpp
sort(a+1,a+n+1,cmp);
for(int i=1;i<=n;i++){
    if(ton[a[i].x]>=2){
        ans+=a[i].y;
        ton[a[i].x]--;
        k--;
    }
    if(k==0) break;
}
```

#### 题解2：lbh666

**星级**：★★★★☆  
**关键亮点**：使用结构体存储懒人信息，通过排序和桶数组实现贪心策略，代码简洁易懂。

**核心代码**：
```cpp
sort(a+1,a+n+1,cmp);
for(ll i=1;i<=n;++i){
    if(tot==0) break;
    if(b[a[i].pot]>1){
        ans+=a[i].time;
        --tot;
        b[a[i].pot]--;
    }
}
```

#### 题解3：kimidonatsu

**星级**：★★★★☆  
**关键亮点**：使用重载运算符进行排序，代码简洁，逻辑清晰。

**核心代码**：
```cpp
sort(a + 1, a + n + 1);
for(ll i = 1; i <= n; i++) {
    if(cnt == k) break;
    if(vis[a[i].x] > 1) {
        vis[a[i].x]--;
        cnt++;
        ans += a[i].y;
    }
}
```

---

### 个人心得总结

- **调试经历**：部分题解在实现过程中遇到桶数组越界的问题，通过调整数组大小解决。
- **踩坑教训**：在排序时需要注意比较函数的实现，避免逻辑错误。
- **顿悟感想**：贪心策略在资源分配问题中非常有效，合理选择数据结构可以大大简化问题。

---
处理用时：35.46秒