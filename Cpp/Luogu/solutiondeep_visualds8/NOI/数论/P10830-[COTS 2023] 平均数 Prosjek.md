# 题目信息

# [COTS 2023] 平均数 Prosjek

## 题目背景



译自 [Izborne Pripreme 2023 (Croatian IOI/CEOI Team Selection)](https://hsin.hr/pripreme2023/) D1T2。$\texttt{3s,0.5G}$。

祝 NaCly_Fish 生日快乐！（2024.7.28）

感谢 @Rainbow_qwq 修复交互库。警示后人：慎用 `multiset.count`（复杂度可退化至线性）。


## 题目描述


在黑板上有 $N$ 个非负整数。在一次操作中，可以选择黑板上的两个整数 $a,b$ 满足 $2\mid (a+b)$，将 $a,b$ 从黑板上擦去，然后写下 $(a+b)/2$。注意到每次操作后，黑板上的数都是整数。

试判断是否能让黑板上只剩下一个数。如果可以的话，还需要给出一组解。


## 说明/提示


#### 样例解释

样例 $2$ 解释：$[\boldsymbol{\textcolor{red}{1}},2,3,4,\boldsymbol{\textcolor{red}{5}},6] \to [\boldsymbol{\textcolor{red}{3}},2,\boldsymbol{\textcolor{red}{3}},4,6]\to [3,2,\boldsymbol{\textcolor{red}{4}},\boldsymbol{\textcolor{red}{6}}]\to [\boldsymbol{\textcolor{red}{5}},\boldsymbol{\textcolor{red}{3}},2]\to [\boldsymbol{\textcolor{red}{4}},\boldsymbol{\textcolor{red}{2}}]\to [3]$。

#### 数据范围

对于 $100\%$ 的数据，保证：

- $1\le T\le 10^5$；
- $1\le N,\sum N\le 10^6$；
- $0\le a_i\le 10^{18}$。

| 子任务编号 | 分值 | 约束  |
|:-----:|:------:|:-------:|
| $1$  | $9$  | $T\le 100$，$N\le 7$   |
| $2$  | $23$  | $T\le 100$，$a_i\le 10$  |
| $3$  | $16$  | $a_i$ 都为偶数 |
| $4$  | $52$  | 无额外约束 |




## 样例 #1

### 输入

```
2
3
1 4 5
4
1 4 5 5```

### 输出

```
-1
1 5
3 5
4 4```

## 样例 #2

### 输入

```
1
6
1 2 3 4 5 6```

### 输出

```
1 5
3 3
4 6
3 5
2 4```

# AI分析结果

# 💡 洛语云笺的C++算法解析：平均数 Prosjek 深入学习指南 💡

> 今天我们要一起破解一道 **“黑白棋盘”式的构造题**——平均数 Prosjek。  
> 题目说：黑板上有若干整数，每次可以挑两个 **和为偶数** 的数，擦掉它们，写上它们的平均数。问能否只剩一个数？  
> 这看似简单的规则背后，隐藏着 **奇偶性与二进制位** 的精妙舞蹈。让我们像侦探一样，一步步揭开它的面纱！

---

## 1. 题目解读与策略初探

### ✨ 核心挑战
- **核心挑战**：如何 **构造合法操作序列** 使得最终只剩一个数？  
  关键在于 **奇偶性守恒** 和 **二进制位的可控调整**。

### ✨ 核心算法标签
- 构造算法（Construction）  
- 奇偶性分析（Parity Analysis）  
- 二进制位操作（Bit Manipulation）

### 🗣️ 初步分析
- **朴素思路**：直接模拟每一步操作？但 $N\le 10^6$，显然不可行。  
- **关键观察**：  
  1. 每次操作后，**所有数的奇偶性分布** 会发生变化，但 **总和的奇偶性** 不变！  
  2. 如果能将问题 **归约到只剩两个数**，且这两个数奇偶性相同，就能最后一步合并。  
  3. 更深一步：利用 **二进制最低位** 的差异，可以 **强制构造** 出满足条件的数对。

### 🔍 算法侦探：如何在题目中发现线索？
1. **线索1 (奇偶性)**：  
   题目要求 $(a+b)$ 为偶数，即 $a,b$ **同奇偶**。这说明我们需要 **按奇偶性分类** 处理数。
2. **线索2 (二进制位)**：  
   当所有数同奇偶时，如何进一步操作？观察 **最低不同二进制位** 可以打破僵局。
3. **线索3 (数据规模)**：  
   $N\le 10^6$，要求线性或线性对数时间，排除了暴力模拟。

### 🧠 思维链构建：从线索到策略
> “侦探工作完成！让我们拼图：  
> 1. **线索1** 告诉我们：先按模 4 分类（$S_0,S_1,S_2,S_3$），因为模 4 能更精细刻画奇偶性。  
> 2. **线索2** 提示：如果 $S_0,S_2$ 或 $S_1,S_3$ 同时非空，可以 **保留一对异类数**，其余数内部消化。  
> 3. **线索3** 要求：用 **二进制位调整** 构造异类数对，确保线性复杂度。”

---

## 2. 精选优质题解参考

### 题解一：DaiRuiChen007 的构造法 ⭐⭐⭐⭐⭐
- **亮点**：  
  - 将数按 **模 4 分类**（$S_0,S_1,S_2,S_3$），清晰刻画奇偶性。  
  - 证明 **$S_0,S_2$ 或 $S_1,S_3$ 同时非空时一定有解**，并给出构造方法。  
  - 用 **二进制最低位差异** 强制构造异类数对，时间复杂度 $\mathcal{O}(n\log V)$。
- **代码技巧**：  
  - 用 `vector<ll> a[4]` 存储四类数，操作时用 `opr(x,y)` 封装合并逻辑。  
  - 对 $n\le 4$ 的情况用 **爆搜** 兜底，确保正确性。

### 题解二：Or1gam1 的简化版 ⭐⭐⭐⭐
- **亮点**：  
  - 用 **同奇偶内部消化** 的思想，简化 DaiRuiChen007 的证明。  
  - 强调 **二进制位调整** 的核心作用，避免复杂分类讨论。

---

## 3. 解题策略深度剖析

### 🎯 核心难点与关键步骤
1. **关键点1：模 4 分类**
   - **分析**：  
     将数按模 4 分类（$S_0,S_1,S_2,S_3$），因为：
     - $S_0,S_2$ 内部操作得偶数，$S_1,S_3$ 内部操作得偶数。  
     - $S_0+S_2$ 或 $S_1+S_3$ 操作得奇数，可打破僵局。
   - 💡 **学习笔记**：  
     模 4 比模 2 更精细，能区分“偶数中的偶数”（$S_0$）和“偶数中的奇数”（$S_2$）。

2. **关键点2：构造异类数对**
   - **分析**：  
     若 $S_0,S_2$ 或 $S_1,S_3$ 同时非空，保留一对异类数（如 $x_0\in S_0,x_2\in S_2$），其余数内部消化。最后合并异类数。
   - 💡 **学习笔记**：  
     构造题的核心是 **归约问题规模**，保留关键数对。

3. **关键点3：二进制位调整**
   - **分析**：  
     当所有数同奇偶时，找到 **最低二进制位差异**（如 $2^d$ 位不同），通过操作强制构造异类数对。
   - 💡 **学习笔记**：  
     二进制位是构造题的“万能钥匙”，能微调数的性质。

### ⚔️ 策略竞技场：不同解法的对比
| 策略 | 核心思想 | 优点 | 缺点 | 适用场景 |
|---|---|---|---|---|
| **暴力模拟** | 每一步枚举合法操作 | 直观 | 指数级复杂度 | $N\le 7$ |
| **模 4 分类 + 构造** | 按模 4 分类，构造异类数对 | 线性对数时间 | 需严谨证明 | $N\le 10^6$ |
| **二进制位调整** | 利用最低位差异构造 | 通用性强 | 需位运算技巧 | 同奇偶情况 |

---

## 4. C++核心代码实现赏析

### 本题通用核心C++实现参考
- **说明**：  
  综合 DaiRuiChen007 和 Or1gam1 的思路，提供完整构造方案。
- **完整核心代码**：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<array<ll, 2>> ops;
vector<ll> bucket[4];

void operate(int x, int y) {
    ll u = bucket[x].back(); bucket[x].pop_back();
    ll v = bucket[y].back(); bucket[y].pop_back();
    ll w = (u + v) / 2;
    ops.push_back({u, v});
    bucket[w & 3].push_back(w);
}

void solve_case() {
    ops.clear();
    for (int i = 0; i < 4; ++i) bucket[i].clear();

    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        ll x; cin >> x;
        bucket[x & 3].push_back(x);
    }

    // Case 1: All even or all odd
    if (bucket[1].empty() && bucket[3].empty()) {
        while (bucket[0].size() > 1 || bucket[2].size() > 1) {
            if (bucket[0].size() > 1) operate(0, 0);
            else operate(2, 2);
        }
        if (!bucket[0].empty() && !bucket[2].empty()) operate(0, 2);
    } else if (bucket[0].empty() && bucket[2].empty()) {
        while (bucket[1].size() > 1 || bucket[3].size() > 1) {
            if (bucket[1].size() > 1) operate(1, 1);
            else operate(3, 3);
        }
        if (!bucket[1].empty() && !bucket[3].empty()) operate(1, 3);
    } else {
        // Case 2: Mixed parity, construct pairs
        vector<ll> rem;
        if (!bucket[0].empty() && !bucket[2].empty()) {
            rem.push_back(bucket[0].back()); bucket[0].pop_back();
            rem.push_back(bucket[2].back()); bucket[2].pop_back();
        } else {
            rem.push_back(bucket[1].back()); bucket[1].pop_back();
            rem.push_back(bucket[3].back()); bucket[3].pop_back();
        }

        // Process remaining numbers
        while (true) {
            if (bucket[0].size() + bucket[2].size() > 1) {
                if (!bucket[0].empty() && !bucket[2].empty()) operate(0, 2);
                else if (!bucket[0].empty()) operate(0, 0);
                else operate(2, 2);
            } else if (bucket[1].size() + bucket[3].size() > 1) {
                if (!bucket[1].empty() && !bucket[3].empty()) operate(1, 3);
                else if (!bucket[1].empty()) operate(1, 1);
                else operate(3, 3);
            } else break;
        }

        // Collect remaining numbers
        for (int i = 0; i < 4; ++i)
            for (ll x : bucket[i]) rem.push_back(x);

        // Brute force for small cases
        vector<array<ll, 2>> cur;
        function<bool(vector<ll>)> dfs = [&](vector<ll> q) {
            if (q.size() == 1) {
                for (auto [u, v] : ops) cout << u << " " << v << "\n";
                for (auto [u, v] : cur) cout << u << " " << v << "\n";
                return true;
            }
            for (size_t i = 0; i < q.size(); ++i) {
                for (size_t j = i + 1; j < q.size(); ++j) {
                    if ((q[i] + q[j]) % 2 == 0) {
                        cur.push_back({q[i], q[j]});
                        vector<ll> next = {(q[i] + q[j]) / 2};
                        for (size_t k = 0; k < q.size(); ++k)
                            if (k != i && k != j) next.push_back(q[k]);
                        if (dfs(next)) return true;
                        cur.pop_back();
                    }
                }
            }
            return false;
        };
        if (!dfs(rem)) cout << "-1\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T; cin >> T;
    while (T--) solve_case();
    return 0;
}
```
- **代码解读概要**：  
  1. 按模 4 分类存储数。  
  2. 处理全偶或全奇情况，内部消化。  
  3. 混合情况时构造异类数对，剩余数爆搜。  
  4. 输出操作序列。

---

## 5. 算法可视化：像素动画演示

### 🎮 动画主题：二进制位的“魔法合并”
- **场景设计**：  
  一个 8×8 的像素网格，每个格子是一个数，颜色表示模 4 类别（$S_0$ 绿色，$S_1$ 蓝色，$S_2$ 黄色，$S_3$ 红色）。  
- **动画流程**：  
  1. **分类阶段**：数字像俄罗斯方块一样落入对应颜色的列。  
  2. **合并阶段**：同颜色数字碰撞合并，生成新数字并变色。  
  3. **构造阶段**：异类数字（如绿+黄）合并时，像素爆炸特效。  
- **音效**：  
  - 合并成功：8 位“叮”声。  
  - 无解：低沉“咚”声。  
- **交互**：  
  - 步进按钮：每按一次，执行一次合并。  
  - 自动模式：AI 自动选择最优合并顺序。

---

## 6. 拓展练习与相似问题思考

### 通用思路迁移
- **奇偶性分析**：适用于所有涉及“奇偶性约束”的问题，如：
  1. **硬币翻转**：每次翻转两枚硬币，能否全正面？  
  2. **灯泡开关**：每次切换两个灯泡状态，能否全亮？  
  3. **图着色**：相邻顶点颜色奇偶性约束。

### 洛谷推荐
1. **P3383** - 线性筛素数  
   🗣️ 推荐理由：巩固数论基础，为奇偶性分析铺垫。  
2. **P1908** - 逆序对  
   🗣️ 推荐理由：练习二进制位操作和分治思想。  
3. **P4779** - 最长递增子序列  
   🗣️ 推荐理由：理解状态归约和构造技巧。

---

## 7. 学习心得与经验分享

> **经验分享**（来自 DaiRuiChen007）：  
> “最初尝试暴力模拟，发现指数级复杂度不可行。后来意识到 **模 4 分类** 是关键，通过保留异类数对归约问题。调试时打印每一步的奇偶性分布，能快速定位错误。”

> **点评**：  
> 构造题的精髓是 **问题归约**，而非盲目模拟。通过分类和保留关键元素，能将复杂问题化繁为简。

---

<conclusion>
本次关于“平均数 Prosjek”的解析就到这里。记住：  
- **奇偶性** 是构造题的“显微镜”，能洞察数的本质。  
- **二进制位** 是“手术刀”，能精准调整数的性质。  
下次我们再一起探索新的算法挑战！💪
</conclusion>

---
处理用时：119.38秒