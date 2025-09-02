# 题目信息

# [ABC399B] Ranking with Ties

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc399/tasks/abc399_b

编号为 $1$ 至 $N$ 的 $N$ 人参加了一场竞赛，其中第 $i$ 人（$1 \leq i \leq N$）的 **得分** 为 $P_i$。

本竞赛的 **排名** 按照以下流程确定：

1. 准备变量 $r$ 并初始化为 $r = 1$。初始时所有 $N$ 人的排名均为未确定状态。
2. 重复以下操作直到所有 $N$ 人的排名确定：
   - 设当前未确定排名的人中最高得分为 $x$，且得分为 $x$ 的人数为 $k$。将所有得分为 $x$ 的 $k$ 人的排名确定为 $r$ 位，然后将 $r$ 增加 $k$。

请输出这 $N$ 人各自的排名。

## 说明/提示

### 约束条件

- $1 \leq N \leq 100$
- $1 \leq P_i \leq 100$
- 所有输入均为整数

### 样例解释 1

以下为 $N\ (=4)$ 人排名的确定流程：
1. 准备变量 $r$ 并初始化为 $r = 1$。初始时所有 4 人的排名均为未确定状态。
2. 当前未确定排名的是人 1、2、3、4，其中最高得分为 $P_2\ (=12)$。因此确定人 2 的排名为 $r\ (=1)$ 位，之后将 $r$ 增加 1 得 $r = 2$。
3. 当前未确定排名的是人 1、3、4，其中最高得分为 $P_3 = P_4\ (=9)$。因此确定人 3、4 的排名为 $r\ (=2)$ 位，之后将 $r$ 增加 2 得 $r = 4$。
4. 当前未确定排名的是人 1，其得分为 $P_1\ (=3)$。因此确定人 1 的排名为 $r\ (=4)$ 位，之后将 $r$ 增加 1 得 $r = 5$。
5. 所有 4 人的排名已确定，流程结束。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4

3 12 9 9```

### 输出

```
4

1

2

2```

## 样例 #2

### 输入

```
3

3 9 6```

### 输出

```
3

1

2```

## 样例 #3

### 输入

```
4

100 100 100 100```

### 输出

```
1

1

1

1```

## 样例 #4

### 输入

```
8

87 87 87 88 41 38 41 38```

### 输出

```
2

2

2

1

5

7

5

7```

# AI分析结果



# 算法分类  
**模拟**

## 综合分析与结论  
### 核心思路  
题目要求按特定规则对参赛者进行分组排名。核心思路是严格模拟题面描述的流程：  
1. 每次找出未确定排名的最高分群体  
2. 将该群体统一设置为当前排名值  
3. 更新排名值变量  

### 解决难点  
- **动态维护未处理群体**：通过布尔数组标记已处理人员  
- **批量处理相同得分者**：每次遍历两次数组（一次找最大值，一次收集所有等于最大值的人）  
- **排名值递推逻辑**：当前排名值`r`的增量等于当前处理批次的人数  

### 可视化设计要点  
1. **动画演示**：  
   - 用不同颜色区分已处理/未处理人员  
   - 高亮当前批次找到的最高分群体  
   - 显示浮动文字提示当前排名值变化（如 r=1 → r=1+k）  
2. **复古像素风格**：  
   - 用16色块表示参赛者，分数越高色块越大  
   - 处理批次时触发8-bit音效  
   - 背景音乐采用FC经典游戏循环旋律  

---

## 题解清单 (5星)  
### 题解：直接模拟流程  
**亮点**：  
- 严格按题意分步实现，代码可读性极强  
- 使用双重循环动态维护未处理群体，逻辑直观  
- 时间复杂度O(N²)完全满足题目约束  

**核心代码**：  
```cpp
vector<int> ans(N, 0);
int current_rank = 1, remaining = N;
while (remaining > 0) {
    int max_score = -1;
    for (int i = 0; i < N; ++i) 
        if (!ans[i]) max_score = max(max_score, P[i]);
    
    vector<int> targets;
    for (int i = 0; i < N; ++i)
        if (!ans[i] && P[i] == max_score) 
            targets.push_back(i);
    
    for (int idx : targets) ans[idx] = current_rank;
    current_rank += targets.size();
    remaining -= targets.size();
}
```

---

## 最优技巧提炼  
**批量处理思想**：  
- 将相同得分者视为一个整体处理，避免逐一个人更新  
- 通过`current_rank += k`实现排名值的跳跃式更新  

**状态标记技巧**：  
- 利用`ans[i] == 0`隐式维护未处理状态，无需额外空间  

---

## 相似题目推荐  
1. [P1093 奖学金](https://www.luogu.com.cn/problem/P1093) - 多条件排序  
2. [P1781 宇宙总统](https://www.luogu.com.cn/problem/P1781) - 特殊比较规则  
3. [P1177 排序模板](https://www.luogu.com.cn/problem/P1177) - 基础排序应用  

---

## 完整代码实现  
```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N;
    cin >> N;
    vector<int> P(N);
    for (int i = 0; i < N; ++i) cin >> P[i];
    
    vector<int> ans(N, 0);
    int current_rank = 1, remaining = N;
    
    while (remaining > 0) {
        int max_score = -1;
        for (int i = 0; i < N; ++i)
            if (!ans[i]) max_score = max(max_score, P[i]);
        
        vector<int> targets;
        for (int i = 0; i < N; ++i)
            if (!ans[i] && P[i] == max_score)
                targets.push_back(i);
        
        for (int idx : targets) ans[idx] = current_rank;
        current_rank += targets.size();
        remaining -= targets.size();
    }
    
    for (int rank : ans) cout << rank << '\n';
    return 0;
}
```

---
处理用时：121.13秒