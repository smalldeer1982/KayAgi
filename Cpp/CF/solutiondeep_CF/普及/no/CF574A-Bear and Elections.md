# 题目信息

# Bear and Elections

## 题目描述

`Limak`前来参加选举。

在选举中，候选人总共有$n$位，第$i$位候选人当前的选票是$a_{i}$。

`Limak`十分渴望权力，于是他决定使用下作的手段赢得选举——贿赂市民。对于每一个市民，`Limak`只需要一颗糖果就可以贿赂他。

请问，`Limak`至少需要几颗糖果才能赢得选举？

## 说明/提示

$2 \leq n \leq 100$；

$1 \leq a_{i} \leq 1000$；

## 样例 #1

### 输入

```
5
5 1 11 2 8
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
1 8 8 8
```

### 输出

```
6
```

## 样例 #3

### 输入

```
2
7 6
```

### 输出

```
0
```

# AI分析结果



# Bear and Elections 的题解分析

**标签：贪心**

## 题目重述
`Limak`参加选举，共有$n$位候选人，其初始票数为$a_1$（第一位候选人）。他需要通过贿赂选民来确保自己的票数严格超过其他所有候选人。每贿赂一位选民需要1颗糖果。求最少需要多少糖果？

## 题解综合分析

### 核心思路对比
各题解均采用贪心策略：每次减少当前最高票数对手的票。差异主要在数据结构选择：
1. **优先队列**（O(m log n)）：高效维护最大值
2. **数组排序**（O(n log n)每次操作）：简单但效率较低

### 最优思路提炼
使用大根堆（优先队列）维护其他候选人的票数，每次操作只需处理堆顶元素，时间复杂度最优。

---

## 精选高分题解

### 题解1：lichenzhen（★★★★★）
**亮点**：  
• 使用优先队列高效维护最大值  
• 代码结构清晰，变量命名合理  
• 时间复杂度最优（O(m log n)）

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    priority_queue<int> p;
    int n, z, ans = 0; 
    cin >> n >> z;
    for(int i=2; i<=n; i++) {
        int a; cin >> a;
        p.push(a);
    }
    while(z <= p.top()) {
        int maxn = p.top();
        p.pop();
        p.push(maxn - 1);
        ans++;
        z++;
    }
    cout << ans;
}
```

---

### 题解2：Fcersoka（★★★★）
**亮点**：  
• 直观的数组排序实现  
• 代码极简，适合小数据量  
• 通过限定排序范围优化效率

```cpp
#include<bits/stdc++.h>
using namespace std;
int main() {
    int n, a[101], ans=0;
    cin >> n;
    for(int i=1; i<=n; i++) cin >> a[i];
    sort(a+2, a+n+1);
    while(a[n] >= a[1]) {
        a[1]++; a[n]--; ans++;
        sort(a+2, a+n+1);
    }
    cout << ans;
}
```

---

### 题解3：agicy（★★★★）
**亮点**：  
• 对排序范围进行明确注释  
• 添加边界条件预判优化  
• 变量命名具有自解释性

```cpp
#include <algorithm>
#include <cstdio>
int main() {
    int n, vote, a[101], ans=0;
    scanf("%d%d", &n, &vote);
    for(int i=1; i<n; i++) scanf("%d", &a[i]);
    std::sort(a+1, a+n);
    while(a[n-1] >= vote) {
        a[n-1]--; vote++; ans++;
        std::sort(a+1, a+n);
    }
    printf("%d", ans);
}
```

---

## 关键技巧总结
1. **数据结构选择**：优先队列适合动态维护最大值，避免重复全排序
2. **边界处理**：单独处理Limak的票数变量，简化逻辑
3. **循环条件**：`while(z <= p.top())` 严格保证最终状态

## 同类题目推荐
1. [P1090 合并果子](https://www.luogu.com.cn/problem/P1090)  
   （贪心+优先队列经典问题）
2. [P1208 混合牛奶](https://www.luogu.com.cn/problem/P1208)  
   （贪心策略选择最优单价）
3. [P2240 部分背包问题](https://www.luogu.com.cn/problem/P2240)  
   （价值密度贪心思想）

## 题解心得摘录
> "根据正常人的想法和思维，选票最多的人是Limak最大的敌人，我们应该多贿赂他的支持者。"  
> —— 来自agicy的题解，强调贪心策略的直觉来源。调试时需注意每次操作后必须重新维护最大值结构。

---
处理用时：97.93秒