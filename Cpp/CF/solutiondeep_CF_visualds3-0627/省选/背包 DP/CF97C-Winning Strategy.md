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



---

## **算法分类**
数学结论/贪心策略

---

## **综合分析与结论**

### **题目核心逻辑**
在无限次组队中，找到交替使用两种策略（增加/减少可用有经验人数）的最优组合，使得长期平均胜率最大。关键在于发现最优策略由两种操作的无限循环构成，并通过数学推导求出加权平均概率的最大值。

### **题解思路对比**
1. **结论法（yzy1、Brioche）**  
   - **核心思想**：枚举所有正负权值组合（`b_i = n-2i`），计算对应的加权平均概率。  
   - **实现关键**：遍历所有满足 `b_i > 0` 和 `b_j < 0` 的 `i, j`，计算 `(-b_j*p_i + b_i*p_j)/(b_i - b_j)` 的最大值，并考虑 `b_k=0` 的特殊情况。  
   - **优势**：时间复杂度 `O(n²)`，简洁高效。

2. **分数规划（Brioche）**  
   - **核心思想**：二分答案，检查是否存在正环使得平均概率不低于当前猜测值。  
   - **实现关键**：建图后通过 SPFA 检查负环。  
   - **劣势**：代码复杂度高，适用性较低。

3. **倍增Floyd（Brioche）**  
   - **核心思想**：动态规划处理状态转移矩阵，模拟无限次操作后的稳定状态。  
   - **劣势**：实现复杂，状态转移矩阵的构造需要精细处理。

### **难点与解决**
- **难点**：如何证明最优策略仅需两种操作的交替循环。  
- **解决**：通过分析无限次操作后的极限行为，发现循环结构的必要性，并利用数学推导得出加权公式。

---

## **题解清单 (≥4星)**

1. **Brioche的结论法（5星）**  
   - **亮点**：代码极简，直接枚举所有正负组合，正确性明确。  
   - **代码片段**：  
     ```cpp
     for(int i=0;i<=(n-1)/2;i++)
         for(int j=(n-1)/2+1;j<=n;j++)
             ans=max(ans,(c[j]*p[i]+c[i]*p[j])/(c[j]+c[i]));
     ```

2. **yzy1的结论法（4星）**  
   - **亮点**：正确处理 `b=0` 的特殊情况，逻辑清晰。  
   - **代码片段**：  
     ```cpp
     each(z, zheng) {
         each(f, fu) {
             lf res = (f.gx * z.one + z.gx * (-f.one)) / (z.one - f.one);
             up(ans, res);
         }
     }
     ```

---

## **最优思路提炼**
1. **核心公式**：对每对 `(i, j)` 满足 `b_i > 0` 和 `b_j < 0`，计算：  
   \[
   \text{avg} = \frac{-b_j \cdot p_i + b_i \cdot p_j}{b_i - b_j}
   \]
2. **特判处理**：若存在 `b_k=0`，直接取 `max(ans, p_k)`。

---

## **同类型题推荐**
1. **CF939E Maximize!**（极值分析与数学推导）  
2. **CF147B Smile House**（正环检测与分数规划）  
3. **P4308 幸福路径**（倍增Floyd与动态规划）

---

## **可视化设计要点**
### **动画方案**
1. **像素风格状态图**：  
   - 用 8-bit 网格表示可用人数变化，红色方块标记当前选择的策略 `i` 和 `j`。  
   - 每次交替操作时，播放“选择”音效，绿色箭头表示人数增减方向。

2. **自动演示模式**：  
   - 初始展示所有 `b_i` 的正负分布，高亮最优的 `(i, j)` 组合。  
   - 循环播放交替操作，动态显示平均概率的收敛过程。

3. **音效设计**：  
   - **正确操作**：短促的“哔”声。  
   - **找到最优解**：8-bit 胜利音效。  
   - **错误操作**：低沉的“嘟”声。

---

## **核心代码实现**
```cpp
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    int n;
    cin >> n;
    double p[n+1], ans = 0;
    for (int i=0; i<=n; i++) {
        cin >> p[i];
        if (n-2*i == 0) ans = max(ans, p[i]); // 处理 b_k=0
    }
    for (int i=0; i<=(n-1)/2; i++) {        // 正权值区间
        for (int j=(n+1)/2; j<=n; j++) {    // 负权值区间
            double bi = n-2*i, bj = n-2*j;
            if (bi <=0 || bj >=0) continue; // 确保正负组合
            double avg = (-bj*p[i] + bi*p[j]) / (bi - bj);
            ans = max(ans, avg);
        }
    }
    printf("%.12lf\n", ans);
    return 0;
}
```

---
处理用时：172.79秒