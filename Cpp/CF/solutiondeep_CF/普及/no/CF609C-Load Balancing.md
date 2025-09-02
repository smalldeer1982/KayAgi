# 题目信息

# Load Balancing

## 题目描述

In the school computer room there are $ n $ servers which are responsible for processing several computing tasks. You know the number of scheduled tasks for each server: there are $ m_{i} $ tasks assigned to the $ i $ -th server.

In order to balance the load for each server, you want to reassign some tasks to make the difference between the most loaded server and the least loaded server as small as possible. In other words you want to minimize expression $ m_{a}-m_{b} $ , where $ a $ is the most loaded server and $ b $ is the least loaded one.

In one second you can reassign a single task. Thus in one second you can choose any pair of servers and move a single task from one server to another.

Write a program to find the minimum number of seconds needed to balance the load of servers.

## 说明/提示

In the first example two seconds are needed. In each second, a single task from server #2 should be moved to server #1. After two seconds there should be 3 tasks on server #1 and 4 tasks on server #2.

In the second example the load is already balanced.

A possible sequence of task movements for the third example is:

1. move a task from server #4 to server #1 (the sequence $ m $ becomes: 2 2 3 3 5);
2. then move task from server #5 to server #1 (the sequence $ m $ becomes: 3 2 3 3 4);
3. then move task from server #5 to server #2 (the sequence $ m $ becomes: 3 3 3 3 3).

The above sequence is one of several possible ways to balance the load of servers in three seconds.

## 样例 #1

### 输入

```
2
1 6
```

### 输出

```
2
```

## 样例 #2

### 输入

```
7
10 11 10 11 10 11 11
```

### 输出

```
0
```

## 样例 #3

### 输入

```
5
1 2 3 4 5
```

### 输出

```
3
```

# AI分析结果



# 负载均衡

## 题目描述

学校机房中有 $n$ 台服务器负责处理计算任务。已知每台服务器分配的任务量 $m_i$。现需通过任务转移使得各服务器负载尽可能均衡，即最小化最大负载与最小负载的差值。每次转移可在一秒内将任一任务从一个服务器移动到另一个服务器，求达成平衡所需的最短时间。

## 算法分类
贪心

---

## 题解综合分析

所有题解均采用贪心策略，核心思路为：将总任务数 $S$ 均分给 $n$ 台服务器，允许 $S \bmod n$ 台服务器多承载 1 个任务。通过计算各节点与目标值的差值绝对值之和，再除以 2 得到操作次数。各解法在实现细节略有差异，但核心思想一致。

---

## 精选题解

### 题解1（作者：Dry_ice） ⭐⭐⭐⭐
**亮点**：代码简洁，逻辑清晰，包含关键注释  
**关键思路**：
1. 总任务数 $S$ 均分得基础值 $avg = S/n$
2. 剩余 $rem = S \% n$ 个任务分配给 $rem$ 台服务器
3. 前 $n-rem$ 台调整到 $avg$，后 $rem$ 台调整到 $avg+1$
4. 差值绝对值总和除以 2 即为答案

```cpp
#include<stdio.h>
#include<algorithm>
int a[100005];
int main() {
    int n, sum = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        sum += a[i];
    }
    int avg = sum / n, rem = sum % n, ans = 0;
    std::sort(a, a + n);
    for(int i = 0; i < n - rem; ++i)
        ans += abs(a[i] - avg);
    for(int i = n - rem; i < n; ++i)
        ans += abs(a[i] - avg - 1);
    printf("%d\n", ans >> 1);
    return 0;
}
```

### 题解2（作者：yuheng_wang080904） ⭐⭐⭐⭐
**亮点**：数学推导完整，变量命名规范  
**技巧**：通过模运算处理余数分布，直接操作排序数组分段处理

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m[100005],sum,ans;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>m[i];
    for(int i=1;i<=n;i++) sum += m[i];
    sort(m+1,m+n+1);
    for(int i=1;i<=n-sum%n;i++) ans += abs(m[i]-sum/n);
    for(int i=n-sum%n+1;i<=n;i++) ans += abs(m[i]-(sum/n+1));
    cout<<ans/2<<endl;
    return 0;
}
```

---

## 关键思路总结
1. **目标值确定**：根据总任务数 $S$ 计算基础值 $avg = \lfloor S/n \rfloor$，余数 $rem = S \% n$ 决定 $rem$ 台服务器需多承担 1 个任务。
2. **排序优化**：通过排序后数组的前后分段处理，确保最小调整路径。
3. **差量统计**：计算各元素与目标值的绝对差之和，除以 2 抵消双向操作的影响。

---

## 类似题目推荐
1. [P3135 - 前缀和与平衡](https://www.luogu.com.cn/problem/P3135)  
2. [P1115 - 最大子段和](https://www.luogu.com.cn/problem/P1115)  
3. [P1031 - 均分纸牌](https://www.luogu.com.cn/problem/P1031)

---
处理用时：52.28秒