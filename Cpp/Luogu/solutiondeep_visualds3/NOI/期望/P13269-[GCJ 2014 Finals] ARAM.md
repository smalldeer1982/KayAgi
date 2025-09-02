# 题目信息

# [GCJ 2014 Finals] ARAM

## 题目背景

League of Legends 是 Riot Games 的商标。Riot Games 并未参与也未支持 Google Code Jam。


## 题目描述

在游戏 *League of Legends*（英雄联盟）中，有一种叫做 “ARAM”（All Random, All Mid，全随机单中路） 的游戏模式。本题借鉴了这一设定，但无需了解英雄联盟也能理解题意。

每次开始 ARAM 游戏时，你会从 $\mathrm{N}$ 个“英雄”（champions）中**等概率**地随机获得一个。你使用某些英雄时更容易获胜，因此当运气不好时，你可能希望自己能抽到另一个英雄。幸运的是，游戏中提供了“重新抽取”（Reroll）的功能。

重新抽取的机制如下所述，但你不能随时使用它。重新抽取的能力可以看作是一种货币：在你开始第一个 ARAM 游戏之前，你拥有 $\mathrm{R}$ 个“重新抽取点数”（RD，Reroll Dollars）。你只有在手上至少有 $1$ RD 时，才可以使用重新抽取，每次消耗 $1$ RD。

每打完一局游戏，你会获得 $1 / \mathrm{G}$ 个 RD（其中 $\mathrm{G}$ 是一个整数），但你的 RD 总数永远不会超过 $\mathrm{R}$：即使你已经拥有 $\mathrm{R}$ 个 RD，打完一局之后你仍然只有 $\mathrm{R}$ 个。

如果你手上有至少 $1$ RD，并选择使用重新抽取，则你会消耗 $1$ RD，并重新从 $\mathrm{N}$ 个英雄中**等概率**地抽取一个（可能会重复拿到当前的英雄）。如果你不满意新的英雄，并且还有 $1$ RD 以上，你可以继续重新抽取。只要你还剩下 RD，就可以继续抽。

例如，如果 $\mathrm{R} = 2$ 且 $\mathrm{G} = 2$，你在第一局游戏使用了一次重新抽取，那么该局之后你将拥有 $1.5$ RD。下一局若未使用重新抽取，该局结束后你将拥有 $2.0$ RD。再下一局若也未使用，那么仍为 $2.0$（因为不能超过上限）。如果你在接下来的游戏中使用了两次重新抽取，那么该局结束后你将剩下 $0.5$ RD。

你将得到一份英雄列表，以及每个英雄的胜率。如果你要打 $10^{100}$ 局游戏，并始终采用最优策略（即期望胜率最大化），那么你预期能赢下多少比例的游戏？


## 说明/提示

## 限制条件

- $1 \leq \mathrm{T} \leq 100$
- $0.0 \leq \mathrm{P}_i \leq 1.0$，每个胜率值格式为 1 位整数 + 小数点 + 4 位数字

### Small 数据集（22 分）

- 时间限制：~~60~~ 3 秒
- $1 \leq \mathrm{N} \leq 1000$
- $1 \leq \mathrm{R} \leq 2$
- $1 \leq \mathrm{G} \leq 3$

### Large 数据集（42 分）

- 时间限制：~~120~~ 5 秒
- $1 \leq \mathrm{N} \leq 1000$
- $1 \leq \mathrm{R} \leq 20$
- $1 \leq \mathrm{G} \leq 20$

翻译由 ChatGPT-4o 完成

## 样例 #1

### 输入

```
3
2 1 1
1.0000 0.0000
3 1 1
1.0000 0.0000 0.5000
6 2 3
0.9000 0.6000 0.5000 0.1000 0.2000 0.8000```

### 输出

```
Case #1: 0.750000000000
Case #2: 0.666666666667
Case #3: 0.618728522337```

# AI分析结果

# 💡 Kay的C++算法解析：[GCJ 2014 Finals] ARAM 深入学习指南 💡

今天我们来一起分析Google Code Jam 2014 Finals的“ARAM”问题。这道题结合了概率、动态规划和马尔可夫链的知识，需要我们用数学思维建模游戏机制，找到长期最优策略下的期望胜率。本指南将帮助大家梳理思路，理解核心算法，并掌握解题技巧。


## 1. 题目解读与核心算法识别

✨ **本题主要考察**：数学（概率、动态规划、马尔可夫链稳态分析）

🗣️ **初步分析**：  
解决“ARAM”问题的关键在于**用数学模型翻译游戏规则**——就像用公式解物理题一样，我们把“reroll机会”“胜率期望”“状态转移”这些抽象概念转化为可计算的数学表达式。核心思路分三步：  
1. **动态规划算期望**：E_t表示有t次reroll机会时的最大期望胜率（抽到好英雄就停，不好就继续抽）；  
2. **概率算reroll次数**：prob(q,k)是状态q下用k次reroll的概率（前k次都抽差英雄，第k+1次抽好英雄）；  
3. **稳态求长期期望**：状态是当前的RD量（离散化为1/G的整数倍），长期玩游戏后状态分布会稳定，此时的期望就是各状态概率乘以该状态的E_t之和。


### 核心算法与可视化设计
我们用**8位像素风**让抽象的数学过程变直观：  
- **动态规划递推E_t**：用像素块代表E_t，从E_0开始，每步计算时用橙色块标“≥阈值的胜率”、蓝色块标“<阈值的胜率”，累加橙色块总和（sum_ge）、计数蓝色块数量（count_lt），最后生成E_t的绿色块。  
- **状态转移矩阵**：用像素网格表示状态（0到M），转移用带箭头的像素线表示（箭头越粗概率越大）。  
- **稳态分布**：用像素柱形图表示各状态概率，动画展示柱形从0逐步长高到稳定（最高柱形是最常出现的状态）。


## 2. 精选优质题解参考
由于待处理内容中无具体题解，我们总结**通用学习建议**：  
- 重点掌握**最优停止策略**：E_t = E[max(当前胜率, E_{t-1})]，用排序后的数组快速计算；  
- 练习**马尔可夫链稳态求解**：用高斯消元法解线性方程组；  
- 熟悉**概率乘法原理**：prob(q,k)是“拒绝k次、接受1次”的概率乘积。


## 3. 核心难点辨析与解题策略

<difficulty_intro>
解决本题的核心难点是“把游戏规则转数学模型”，以下是三个关键问题及解决方法：
</difficulty_intro>

### 难点1：理解最优停止策略，推导E_t递推公式
- **分析**：很多同学误以为“用k次reroll就是抽k+1次取最好”，但最优策略是“抽到好的就停，不好就继续”——阈值是剩下的机会的期望（E_{t-1}）。  
- **解决**：E_t = (≥阈值的胜率之和 + 阈值×<阈值的胜率数量) / N（用排序后的数组和lower_bound快速算这两个值）。  
- 💡 **学习笔记**：最优策略的核心是“比较当前收益和未来期望”，阈值就是未来期望。


### 难点2：计算prob(q,k)——用k次reroll的概率
- **分析**：prob(q,k)是“前k次都抽差英雄（必须继续），第k+1次抽好英雄（停止）”的概率。  
- **解决**：用排序后的数组算“≥阈值的胜率数量”，prob(q,k) = 前k次“<阈值”的概率乘积 × 第k+1次“≥阈值”的概率（k<q时）；k=q时最后乘1（必须接受第q+1次）。  
- 💡 **学习笔记**：prob(q,k)是“拒绝k次、接受1次”的概率，用乘法原理计算。


### 难点3：求解马尔可夫链的稳态分布
- **分析**：稳态分布是满足π = π×P的概率向量（P是转移矩阵），需要解线性方程组。  
- **解决**：用高斯消元法解“π[a] = sum(π[b]×P[b][a])”（每个状态a的方程）+“sum(π)=1”（总概率为1）。  
- 💡 **学习笔记**：稳态分布是“长期玩游戏后各状态的出现概率”，解线性方程组是关键。


### ✨ 解题技巧总结
- **排序胜率数组**：用lower_bound快速找阈值位置，优化计算；  
- **离散化状态**：把RD量转1/G的整数倍，状态数从无限变有限；  
- **预计算E_t**：递推计算，不用存储所有中间结果。


## 4. C++核心代码实现赏析

<code_intro_overall>
以下是解决本题的通用核心代码，涵盖动态规划、概率计算、稳态求解的完整逻辑。
</code_intro_overall>

### 本题通用核心C++实现参考
* **说明**：综合动态规划、概率计算和线性代数求解的核心逻辑，适用于所有测试用例。
* **完整核心代码**：
```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

using namespace std;
const double EPS = 1e-10;

// 计算E_t：有t次reroll机会的最大期望胜率
vector<double> compute_E(const vector<double>& sorted_P, int R) {
    int N = sorted_P.size();
    vector<double> E(R+1);
    E[0] = 0.0;
    for (double p : sorted_P) E[0] += p;
    E[0] /= N;

    for (int t = 1; t <= R; ++t) {
        double theta = E[t-1];
        int m = lower_bound(sorted_P.begin(), sorted_P.end(), theta) - sorted_P.begin();
        double sum_ge = 0.0;
        for (int i = m; i < N; ++i) sum_ge += sorted_P[i];
        int count_lt = m;
        E[t] = (sum_ge + theta * count_lt) / N;
    }
    return E;
}

// 计算prob(q,k)：状态q下用k次reroll的概率
vector<double> compute_prob(const vector<double>& sorted_P, const vector<double>& E, int q) {
    int N = sorted_P.size();
    vector<double> prob(q+1, 0.0);
    if (q == 0) { prob[0] = 1.0; return prob; }

    double theta_q = E[q-1];
    int m_q = lower_bound(sorted_P.begin(), sorted_P.end(), theta_q) - sorted_P.begin();
    double P_ge_q = (double)(N - m_q) / N;
    prob[0] = P_ge_q;

    double current_product = 1.0 - P_ge_q;
    for (int k = 1; k < q; ++k) {
        int t = q - k;
        double theta_t = E[t-1];
        int m_t = lower_bound(sorted_P.begin(), sorted_P.end(), theta_t) - sorted_P.begin();
        double P_ge_t = (double)(N - m_t) / N;
        prob[k] = current_product * P_ge_t;
        current_product *= (1.0 - P_ge_t);
    }
    prob[q] = current_product;
    return prob;
}

// 高斯消元法解线性方程组Ax = b
vector<double> gauss(vector<vector<double>> A, vector<double> b) {
    int n = A.size();
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (int j = i; j < n; ++j)
            if (fabs(A[j][i]) > fabs(A[pivot][i])) pivot = j;
        swap(A[i], A[pivot]); swap(b[i], b[pivot]);

        double div = A[i][i];
        for (int j = i; j < n; ++j) A[i][j] /= div;
        b[i] /= div;

        for (int j = 0; j < n; ++j) {
            if (j != i && fabs(A[j][i]) > EPS) {
                double factor = A[j][i];
                for (int k = i; k < n; ++k) A[j][k] -= factor * A[i][k];
                b[j] -= factor * b[i];
            }
        }
    }
    return b;
}

// 计算稳态分布
vector<double> compute_steady_state(const vector<vector<double>>& P) {
    int n = P.size();
    vector<vector<double>> A(n, vector<double>(n, 0.0));
    vector<double> b(n, 0.0);

    for (int i = 0; i < n-1; ++i) {
        A[i][i] = 1.0;
        for (int j = 0; j < n; ++j) A[i][j] -= P[j][i];
    }
    for (int j = 0; j < n; ++j) A[n-1][j] = 1.0;
    b[n-1] = 1.0;

    return gauss(A, b);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int T; cin >> T;
    for (int case_num = 1; case_num <= T; ++case_num) {
        int N, R, G; cin >> N >> R >> G;
        vector<double> P(N);
        for (int i = 0; i < N; ++i) cin >> P[i];
        sort(P.begin(), P.end());

        int M = R * G;
        vector<double> E = compute_E(P, R);

        vector<vector<double>> trans(M+1, vector<double>(M+1, 0.0));
        for (int a = 0; a <= M; ++a) {
            int q = a / G;
            vector<double> prob = compute_prob(P, E, q);
            for (int k = 0; k <= q; ++k) {
                int a_prime = min(M, a - k * G + 1);
                trans[a][a_prime] += prob[k];
            }
        }

        vector<double> pi = compute_steady_state(trans);
        double total = 0.0;
        for (int a = 0; a <= M; ++a) {
            int q = a / G;
            total += pi[a] * E[q];
        }

        cout << fixed << setprecision(12) << "Case #" << case_num << ": " << total << endl;
    }
    return 0;
}
```

* **代码解读概要**：  
  1. `compute_E`：递推E_t，用lower_bound找阈值位置；  
  2. `compute_prob`：算用k次reroll的概率，用乘法原理；  
  3. `gauss`：高斯消元解线性方程组；  
  4. `main`：读输入、排序胜率、调用函数计算，最后输出总期望。


### 核心代码片段赏析
* **亮点**：用排序+lower_bound快速算“≥阈值的胜率数量”，优化效率。  
* **核心片段**（compute_E函数）：
  ```cpp
  for (int t = 1; t <= R; ++t) {
      double theta = E[t-1];
      int m = lower_bound(sorted_P.begin(), sorted_P.end(), theta) - sorted_P.begin();
      double sum_ge = 0.0;
      for (int i = m; i < N; ++i) sum_ge += sorted_P[i];
      int count_lt = m;
      E[t] = (sum_ge + theta * count_lt) / N;
  }
  ```
* **代码解读**：  
  这段计算E_t的核心逻辑——theta是阈值（E_{t-1}），m是第一个≥theta的胜率索引，sum_ge是≥theta的胜率总和，count_lt是<theta的胜率数量。E_t就是“≥theta的胜率直接取，<theta的胜率取theta”的平均值。  
* 💡 **学习笔记**：排序数组+lower_bound是处理“阈值问题”的神器，能把O(N)时间降到O(logN)。


## 5. 算法可视化：像素动画演示

### 动画方案：《像素ARAM实验室》
**主题**：玩家是“像素科学家”，用实验仪器分析ARAM最优策略，融合8位游戏元素。

### 核心演示步骤
1. **场景初始化**：屏幕分“胜率排序仪”“E_t计算仪”“转移矩阵”“稳态分布仪”，控制面板有“开始/暂停”“单步”按钮，播放8位背景音乐。  
2. **胜率排序**：乱序的胜率像素块按从小到大排序（像冒泡排序动画），完成后播放“叮”音效。  
3. **计算E_t**：E_0先出现，计算E_1时用红色框标阈值位置，橙色块累加、蓝色块计数，E_1的绿色块出现后播放“嗒”音效。  
4. **构建转移矩阵**：像素网格显示状态转移箭头（状态0→1是红色，状态1→1是绿色粗箭头）。  
5. **稳态求解**：柱形图从0逐步长高，稳定后播放“胜利”音效（像FC通关），显示总期望胜率。


## 6. 拓展练习与相似问题思考

### 相似问题思路迁移
- **最优停止问题**：比如“找房子”（看n套房子，选最好的），解法和E_t计算类似；  
- **马尔可夫链**：比如“排队问题”（顾客到达离开的状态转移）、“天气预测”（晴天→阴天→雨天的转移）。

### 洛谷推荐练习
1. **洛谷 P1295 糖果传递**（P1295）：考察数学建模和动态规划，锻炼将问题转化为前缀和的能力。  
2. **洛谷 P1827 美国血统**（P1827）：考察树的遍历和动态规划，锻炼递归和状态转移思维。  
3. **洛谷 P2579 棋子移动**（P2579）：考察状态转移和BFS，锻炼状态建模能力。


## 7. 学习心得与经验分享
本次分析的题解中未发现明确的作者个人心得分享部分。


## 总结
本次关于“ARAM”的分析就到这里。记住，**数学建模是解决复杂问题的钥匙**——把抽象规则转成公式，再用代码实现，就能解决看似难的问题。下次我们再一起探索新的编程挑战！💪

---
处理用时：406.08秒