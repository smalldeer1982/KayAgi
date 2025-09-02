# 题目信息

# A Compatible Pair

## 题目描述

Nian is a monster which lives deep in the oceans. Once a year, it shows up on the land, devouring livestock and even people. In order to keep the monster away, people fill their villages with red colour, light, and cracking noise, all of which frighten the monster out of coming.

Little Tommy has $ n $ lanterns and Big Banban has $ m $ lanterns. Tommy's lanterns have brightness $ a_{1},a_{2},...,a_{n} $ , and Banban's have brightness $ b_{1},b_{2},...,b_{m} $ respectively.

Tommy intends to hide one of his lanterns, then Banban picks one of Tommy's non-hidden lanterns and one of his own lanterns to form a pair. The pair's brightness will be the product of the brightness of two lanterns.

Tommy wants to make the product as small as possible, while Banban tries to make it as large as possible.

You are asked to find the brightness of the chosen pair if both of them choose optimally.

## 说明/提示

In the first example, Tommy will hide $ 20 $ and Banban will choose $ 18 $ from Tommy and $ 14 $ from himself.

In the second example, Tommy will hide $ 3 $ and Banban will choose $ 2 $ from Tommy and $ 1 $ from himself.

## 样例 #1

### 输入

```
2 2
20 18
2 14
```

### 输出

```
252
```

## 样例 #2

### 输入

```
5 3
-1 0 1 2 3
-1 0 1
```

### 输出

```
2
```

# AI分析结果



### 算法分类
无算法分类（问题核心为数学分析与枚举优化）

---

### 题解思路、算法要点与解决难点
#### **核心思路对比**
1. **暴力枚举法**  
   - **要点**：枚举每个可能被隐藏的灯笼，计算剩余灯笼与对方灯笼所有可能的乘积，取最大值的全局最小。  
   - **实现**：三重循环（隐藏元素、剩余元素、对方元素），时间复杂度为 O(n²m)。  
   - **难点**：需正确处理乘积的极值初始化和多轮循环边界条件。

2. **贪心优化法**  
   - **要点**：通过数学分析，发现最大乘积仅由极值组合（最大/次大、最小/次小）决定。  
   - **实现**：预处理极值，仅需计算隐藏最大或最小值后的四种可能组合，时间复杂度为 O(n+m)。  
   - **难点**：需严格证明隐藏极值即可覆盖所有最优情况，并正确处理次极值更新逻辑。

---

### 题解评分（≥4星）
1. **Tweetuzki 的贪心解法** ⭐⭐⭐⭐⭐  
   - **亮点**：高效处理大数据，数学分析深刻，代码预处理极值逻辑清晰。  
   - **适用性**：适用于所有数据范围，时间复杂度最优。  
   - **代码片段**：  
     ```cpp
     // 预处理 a 的极值
     if (x > Max1) { Maxer1 = Max1; Max1 = x; }
     if (x < Min1) { Miner1 = Min1; Min1 = x; }
     // 计算两种隐藏情况的最大值
     llt ans1 = max( max(Maxer1*Max2, ... ), ... );
     ```

2. **StudyingFather 的暴力解法** ⭐⭐⭐⭐  
   - **亮点**：代码简洁易懂，三重循环直接覆盖所有情况。  
   - **适用性**：小数据范围（n, m ≤ 50）下高效。  
   - **代码片段**：  
     ```cpp
     for (int i=1;i<=n;i++) {
         long long now = -INF;
         // 计算隐藏 i 后的最大乘积
         for (int j=1;j<=n;j++) if (j!=i) ...
     }
     ```

3. **Eason_AC 的暴力解法** ⭐⭐⭐⭐  
   - **亮点**：变量命名清晰，初始化处理规范。  
   - **适用性**：代码可读性强，适合初学者理解暴力思路。  
   - **代码片段**：  
     ```cpp
     for (int k=1;k<=n;k++) {
         ll maxi = -INF;
         for (int i=1;i<=n;i++) if (i != k) ...
     }
     ```

---

### 最优思路提炼
**贪心策略的关键步骤**：
1. **极值预处理**：记录数组的极值（最大、次大、最小、次小）。  
2. **组合分析**：最大乘积仅由四种组合产生：`MaxA*MaxB`, `MaxA*MinB`, `MinA*MaxB`, `MinA*MinB`。  
3. **隐藏策略**：Tommy 需隐藏对当前最大贡献最大的极值（MaxA 或 MinA），取两种情况下的最优解。  

---

### 同类型题与算法套路
- **极值组合问题**：如「最大子数组乘积」、「数组中两数最大乘积」。  
- **贪心策略应用**：通过数学性质减少计算量，如「加油站问题」、「任务调度」。  

---

### 推荐相似题目
1. [P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  
2. [P1249 最大乘积](https://www.luogu.com.cn/problem/P1249)  
3. [P1887 乘积最大](https://www.luogu.com.cn/problem/P1887)  

---

### 可视化算法演示
#### **核心动画设计**
- **暴力枚举**：  
  - **动态网格**：用网格表示 `a` 和 `b` 的灯笼，隐藏某行后高亮剩余行列的乘积计算。  
  - **颜色标记**：红色标记当前隐藏元素，绿色标记正在计算的乘积对，黄色显示当前最大值。  
  - **步进控制**：可暂停观察每轮隐藏后的最大乘积变化。  

- **贪心策略**：  
  - **极值追踪**：用不同颜色标注数组中的极值（最大/最小），动态更新隐藏后的次极值。  
  - **组合对比**：并列显示四种极值组合的乘积，突出最终选择的组合。  

#### **复古像素风格**  
- **8位画风**：灯笼用 16x16 像素块表示，极值闪烁提示。  
- **音效交互**：计算极值时触发“点击”音效，隐藏元素时播放“消失”音效。  

---

### 代码实现（贪心法）
```cpp
#include <iostream>
#include <climits>
using namespace std;
typedef long long llt;

int main() {
    int n, m;
    llt MaxA = LLONG_MIN, MaxerA = LLONG_MIN;
    llt MinA = LLONG_MAX, MinerA = LLONG_MAX;
    llt MaxB = LLONG_MIN, MinB = LLONG_MAX;
    
    cin >> n >> m;
    for (int i=0; i<n; ++i) {
        llt x; cin >> x;
        if (x > MaxA) { MaxerA = MaxA; MaxA = x; }
        else if (x > MaxerA) MaxerA = x;
        if (x < MinA) { MinerA = MinA; MinA = x; }
        else if (x < MinerA) MinerA = x;
    }
    for (int i=0; i<m; ++i) {
        llt x; cin >> x;
        MaxB = max(MaxB, x);
        MinB = min(MinB, x);
    }
    
    llt ans1 = max({MaxerA*MaxB, MaxerA*MinB, MinA*MaxB, MinA*MinB});
    llt ans2 = max({MaxA*MaxB, MaxA*MinB, MinerA*MaxB, MinerA*MinB});
    cout << min(ans1, ans2) << endl;
    return 0;
}
```

---
处理用时：181.66秒