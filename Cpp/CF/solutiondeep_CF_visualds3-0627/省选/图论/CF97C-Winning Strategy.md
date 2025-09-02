# 题目信息

# Winning Strategy

## 题目描述

One university has just found out about a sport programming contest called ACM ICPC v2.0. This contest doesn't differ much from the well-known ACM ICPC, for example, the participants are not allowed to take part in the finals more than two times. However, there is one notable difference: the teams in the contest should consist of exactly $ n $ participants.

Having taken part in several ACM ICPC v2.0 finals and having not won any medals, the students and the university governors realized that it's high time they changed something about the preparation process. Specifically, as the first innovation it was decided to change the teams' formation process. Having spent considerable amount of time on studying the statistics of other universities' performance, they managed to receive some interesting information: the dependence between the probability of winning a medal and the number of team members that participated in the finals in the past. More formally, we know $ n+1 $ real numbers $ p_{0}<=p_{1}<=...<=p_{n} $ , where $ p_{i} $ is the probability of getting a medal on the finals if the team has $ i $ participants of previous finals, and other $ n-i $ participants arrived to the finals for the first time.

Despite such useful data, the university governors are unable to determine such team forming tactics that would provide the maximum probability of winning a medal at ACM ICPC v2.0 finals on average (we are supposed to want to provide such result to the far future and we are also supposed to have an endless supply of students). And how about you, can you offer such optimal tactic? At the first stage the university governors want to know the value of maximum average probability.

More formally, suppose that the university sends a team to the $ k $ -th world finals. The team has $ a_{k} $ participants of previous finals ( $ 0<=a_{k}<=n $ ). Since each person can participate in the finals no more than twice, the following condition must be true: ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/b04e8ade7d007ad0702101fe8e64b638ac1fbbe2.png). Your task is to choose sequence ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/e2f72adfe680a0617dc36d9bd6fe81357712642f.png) so that the limit $ Ψ $ exists and it's value is maximal:

![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/cb2ffabcf620f29ef29bcdc17d35b1562b965de1.png)As ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF97C/e2f72adfe680a0617dc36d9bd6fe81357712642f.png) is an infinite sequence, you should only print the maximum value of the $ Ψ $ limit.

## 说明/提示

In the second test, no matter what participants the team contains, it is doomed to be successful.

## 样例 #1

### 输入

```
3
0.115590 0.384031 0.443128 0.562356
```

### 输出

```
0.4286122500
```

## 样例 #2

### 输入

```
3
1 1 1 1
```

### 输出

```
0.9999999999
```

# AI分析结果



## 算法分类
数学建模（贪心策略）

---

## 综合分析与结论

### 核心思路与难点
**问题本质**：寻找无限循环策略，使得每次操作后「有参赛次数余量」的人数变化总和为0，并最大化平均概率。  
**关键观察**：最优策略由两个互补操作循环构成，一个增加可用人数（正权），另一个消耗人数（负权）。  
**解决难点**：  
1. 如何证明只需两个操作即可构成最优循环（数学推导表明多操作组合的线性加权无法超过两操作极值点）  
2. 如何高效枚举所有可能的两操作组合，计算其加权平均概率  

---

## 题解清单（≥4星）

### 1. 作者：yzy1（★★★★☆）  
**亮点**：  
- 直接推导正负操作交替的数学公式，代码简洁高效  
- 引入「权值平衡方程」确保循环后的余量人数稳定  

### 2. 作者：Brioche（★★★★★）  
**亮点**：  
- 通过「背包模型」将问题转化为权值总和为零的循环选择  
- 代码极简，直接枚举所有正负权值对，时间复杂度 O(n²)  

---

## 最优思路与代码实现

### 关键公式推导
每个操作 i 对应权值 `w_i = n - 2i`。对于正权操作 i 和负权操作 j，其最优平均概率为：  
```
Ψ = (w_j * p_i + w_i * p_j) / (w_i + w_j)
```

### 核心代码片段
```cpp
for (int i=0; i<=(n-1)/2; i++)
    for (int j=(n-1)/2+1; j<=n; j++)
        ans = max(ans, (c[j]*p[i] + c[i]*p[j]) / (c[i]+c[j]));
```

---

## 同类型题与拓展

### 相似算法套路  
- **循环权值平衡**：如资源分配问题中寻找周期性策略使资源不枯竭  
- **极值点理论**：多维优化问题中寻找极值点组合  

### 推荐题目  
1. **P4542 [ZJOI2011] 营救皮卡丘**（权值平衡与路径规划）  
2. **P3980 [NOI2008] 志愿者招募**（线性规划与循环策略）  
3. **P4647 [IOI2007] sails 帆船**（贪心策略与资源分配）  

---

## 可视化与交互设计

### 动画方案  
**核心元素**：  
- 网格表示当前可用人数（1血人数）  
- 彩色方块表示不同操作（红：消耗人数，绿：增加人数）  

**动态演示**：  
1. 初始状态为任意人数（如n=3）  
2. 选择红绿方块交替点击，显示每次操作后的1血人数变化  
3. 右侧实时更新平均概率计算公式的分子分母变化  

**复古像素特效**：  
- 每次操作触发8-bit音效（绿块：上升音阶；红块：下降音阶）  
- 当发现更高平均概率时，屏幕闪烁黄光并播放胜利音效  

---

## 个人心得摘录

**yzy1**：  
> "考场上通过样例分析，发现最优策略的循环特性，进而推导公式。验证边界条件（如权值为零的情况）是关键。"  

**Brioche**：  
> "最初被复杂的状态转移迷惑，后通过权值模型将问题简化为背包问题，顿悟两操作极值点的存在。"  

---

## 代码实现（完整）

```cpp
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin >> n;
    double p[105], ans = 0;
    for (int i = 0; i <= n; i++) cin >> p[i];
    
    // 枚举所有正负权值对
    for (int i = 0; i <= (n-1)/2; i++) {
        for (int j = (n+1)/2; j <= n; j++) {
            double wi = n - 2*i, wj = n - 2*j;
            if (wi + wj == 0) continue;
            double current = (wj * p[i] + wi * p[j]) / (wi + wj);
            ans = max(ans, current);
        }
    }
    
    // 检查权值为零的特殊情况
    for (int k = 0; k <= n; k++) 
        if (n - 2*k == 0) ans = max(ans, p[k]);
    
    cout << fixed << setprecision(10) << ans;
    return 0;
}
```

---
处理用时：87.08秒