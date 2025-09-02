# 题目信息

# Interesting Ratio

## 题目描述

最近，Misha 在 IT Campus "NEIMARK" 的夏令营中学习了新课题 —— 欧几里得算法。

当发现 $a \cdot b = \text{lcm}(a, b) \cdot \text{gcd}(a, b)$ 时，他有些惊讶。其中 $\text{gcd}(a, b)$ 是 $a$ 和 $b$ 的[最大公约数 (GCD)](https://en.wikipedia.org/wiki/Greatest_common_divisor)，而 $\text{lcm}(a, b)$ 是[最小公倍数 (LCM)](https://en.wikipedia.org/wiki/Least_common_multiple)。Misha 想到既然 LCM 和 GCD 的乘积存在，或许它们的商也值得研究：$F(a, b) = \frac{\text{lcm}(a, b)}{\text{gcd}(a, b)}$。

例如，他取 $a = 2$ 和 $b = 4$，计算得到 $F(2, 4) = \frac{4}{2} = 2$，结果是一个质数（一个数如果恰好有两个因数则为质数）！现在他认为当 $a < b$ 且 $F(a, b)$ 是质数时，这个比值 $F(a, b)$ 是"有趣的比值"。

由于 Misha 刚接触数论，他需要你帮忙计算 —— 满足 $F(a, b)$ 是"有趣的比值"且 $1 \leq a < b \leq n$ 的不同数对 $(a, b)$ 有多少个？

## 说明/提示

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
4
5
10
34
10007```

### 输出

```
4
11
49
24317```

# AI分析结果



## 算法分类
数论-质数筛法

## 综合分析与结论
题目要求找到满足条件的有序对 $(a, b)$，其中 $1 \leq a < b \leq n$，且 $\frac{\text{lcm}(a,b)}{\text{gcd}(a,b)}$ 是质数。通过数学推导，可将问题转化为统计每个质数 $p$ 的贡献，即计算满足 $b = a \cdot p$ 且 $a \cdot p \leq n$ 的 $a$ 的数量之和。

### 核心算法流程
1. **质数预处理**：使用欧拉筛或埃氏筛预处理所有质数，时间复杂度 $O(n)$。
2. **贡献计算**：对于每个质数 $p$，累加 $\left\lfloor \frac{n}{p} \right\rfloor$，时间复杂度 $O(\pi(n))$，其中 $\pi(n)$ 为 $n$ 以内的质数数量。

### 可视化设计思路
- **质数筛法动画**：展示筛法过程，用不同颜色标记质数和非质数，高亮当前处理的质数及其倍数。
- **贡献统计动画**：动态显示每个质数 $p$ 对应的 $\left\lfloor \frac{n}{p} \right\rfloor$，并累加到总答案中，用进度条表示计算进度。
- **复古像素风格**：采用 8-bit 像素风格，质数用绿色方块表示，非质数用红色，当前操作元素用黄色高亮。

## 题解清单（≥4星）
1. **Collapsarr（5星）**
   - 思路清晰，直接推导出核心公式，代码简洁高效。
   - 使用欧拉筛预处理质数，时间复杂度优秀。
2. **zhangli828（4星）**
   - 通过埃氏筛预处理质数，代码可读性高。
   - 明确分步解释数学推导，适合初学者理解。
3. **c_legg（4星）**
   - 实现思路与核心公式一致，代码结构清晰。
   - 使用埃氏筛，适合理解筛法的基础实现。

## 最优思路与代码实现
### 关键思路
- **数学推导**：$\frac{\text{lcm}(a,b)}{\text{gcd}(a,b)} = p$ 当且仅当 $b = a \cdot p$，其中 $p$ 是质数。
- **质数贡献**：每个质数 $p$ 的贡献为 $\left\lfloor \frac{n}{p} \right\rfloor$，统计所有质数的贡献之和。

### 代码片段
```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e7 + 10;
int prime[N], cnt;
bool vis[N];

void sieve() {
    for (int i = 2; i < N; ++i) {
        if (!vis[i]) prime[cnt++] = i;
        for (int j = 0; j < cnt && i * prime[j] < N; ++j) {
            vis[i * prime[j]] = true;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    sieve();
    int T, n;
    cin >> T;
    while (T--) {
        cin >> n;
        long long ans = 0;
        for (int i = 0; i < cnt && prime[i] <= n; ++i)
            ans += n / prime[i];
        cout << ans << '\n';
    }
    return 0;
}
```

## 相似题目
1. **洛谷 P3912** - 区间质数统计（需预处理质数）
2. **洛谷 P1217** - 回文质数（质数筛法与性质结合）
3. **洛谷 P3383** - 线性筛素数（筛法基础应用）

## 可视化与算法演示
- **筛法动态演示**：在 Canvas 网格中，初始全为灰色，质数标记为绿色，非质数标记为红色，当前处理数高亮为黄色。
- **贡献计算动画**：质数列表滚动显示，每个质数 $p$ 出现时，右侧显示 $\left\lfloor \frac{n}{p} \right\rfloor$ 并累加到总答案。
- **音效设计**：质数标记时播放“滴”声，贡献累加时播放“咔嚓”声，计算完成时播放胜利音效。

---
处理用时：212.02秒