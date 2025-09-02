# 题目信息

# [JRKSJ R2] Upper

## 题目描述

有 $n$ 张扑克，第 $i$ 张扑克上写有一个正整数 $a_i$。

现在要把扑克划分成若干个合法的连续子段，其中，一个连续子段 $[l,r]$ “合法”当且仅当这个子段同时满足两个条件： 

* $a_l< a_r$
* $\gcd(a_l,a_r)>1$ 

请问最多能划分多少段。如果没有合法的划分方案，输出 $-1$ 即可。

如果您不知道 $\gcd$ 是什么意思，请看“提示”部分。

## 说明/提示

### 数据范围
本题采用捆绑测试。

对于 $100\%$ 的数据，$2\le n\le 10^5$，$1\le a_i\le 10^9$。

| $\text{Subtask}$ | $n\le$ | $a_i\le$ | 特殊性质 | 分值 |
| :----------: | :----------: | :----------: | :----------: | :----------: |
| $1$ | $5$ | $10^9$ | 无 | $5$ |
| $2$ | $3\times10^3$ | $10^9$ | 无 | $15$ |
| $3$ | $2\times10^4$ | $10^6$ | 无 | $20$ |
| $4$ | $2\times 10^4$ | $10^9$ | 无 | $10$ |
| $5$ | $10^5$ | $10^9$ | 数据随机 | $10$ |
| $6$ | $10^5$ | $10^9$ | 无 | $40$ |

### 样例解释
对于样例 $1$，有且仅有一种划分方案 $\{2,1,8\},\{3,9\}$。\
对于样例 $2$，无合法的划分方案。

### 提示
对于两个正整数 $a,b$，$\gcd(a,b)$ 为它们的最大公因数，即满足既是 $a$ 的因数又是 $b$ 的因数的数中最大的数。

## 样例 #1

### 输入

```
5
2 1 8 3 9```

### 输出

```
2```

## 样例 #2

### 输入

```
5
5 4 3 2 1```

### 输出

```
-1```

## 样例 #3

### 输入

```
20
20 9 36 36 40 8 3 10 9 20 18 12 30 20 30 15 8 9 27 45```

### 输出

```
7```

# AI分析结果



## 唯一算法分类
动态规划 + 质因数分解 + 权值线段树

---

## 综合分析与结论
### 核心思路
通过动态规划（DP）求解最大划分段数，结合质因数分解将 GCD 条件转化为公共质因子问题，利用权值线段树维护每个质因子对应的最大 DP 值，实现高效转移。

### 算法流程
1. **离散化**：将 `a` 数组离散化为排名，缩小线段树规模。
2. **质因数分解**：预处理小质数，对每个 `a[i]` 分解出其所有质因数。
3. **动态规划**：定义 `f[i]` 表示前 `i` 个元素的最大段数，对每个 `a[i]`，查询其所有质因数对应的线段树中比当前值小的最大 `f[j-1]`，取最大值加 1。
4. **线段树更新**：将 `f[i-1]` 插入到当前质因数对应的线段树中，供后续元素查询。

### 解决难点
- **GCD 条件转化**：将 `gcd(a[j], a[i]) > 1` 转化为存在公共质因子，避免直接计算 GCD。
- **高效查询**：通过权值线段树对每个质因子维护前缀最大值，将查询复杂度降至 `O(log n)`。
- **空间优化**：动态开点线段树避免预分配内存，结合离散化压缩值域。

### 可视化设计
1. **动画演示**：展示以下步骤：
   - **质因数分解**：高亮当前处理的数 `a[i]`，分解出质因数并显示。
   - **线段树查询**：针对每个质因数，显示对应线段树结构和查询路径（如比 `a[i]` 小的最大值）。
   - **DP 更新**：在动画中标记 `f[i]` 的更新值，并插入到线段树中。
2. **复古像素风格**：
   - **数据结构可视化**：线段树节点以 8x8 像素块表示，不同质因数对应不同颜色。
   - **音效设计**：查询成功时播放上升音调，插入操作时播放确认音效，无解时播放低音。

---

## 题解清单 (4星及以上)
1. **KazamaRuri（5星）**  
   - **亮点**：代码简洁高效，最优解实现。利用质因数分解和动态开点线段树，离散化处理减少空间消耗。
   - **代码结构**：清晰的分步处理（分解、离散化、线段树更新）。

2. **ZillionX（5星）**  
   - **亮点**：引入 Exact Division 优化质因数分解速度，代码性能最优。详细注释和模块化设计。
   - **优化点**：预处理质数的逆元加速分解。

3. **Spasmodic（4星）**  
   - **亮点**：使用 `unordered_map` 维护线段树根节点，代码可读性强。动态开点实现节省内存。
   - **改进点**：未处理大质数的优化，分解效率略低。

---

## 最优思路代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
int n, a[N], f[N], rt[N*20], lc[N*40], rc[N*40], mx[N*40], tot;
vector<int> primes[N];
unordered_map<int, int> pid; // 质数到线段树根节点的映射

void factorize(int x, int idx) {
    primes[idx].clear();
    for (int d = 2; d*d <= x; ++d) {
        if (x % d == 0) {
            primes[idx].push_back(d);
            while (x % d == 0) x /= d;
        }
    }
    if (x > 1) primes[idx].push_back(x);
}

void update(int &o, int l, int r, int pos, int val) {
    if (!o) o = ++tot;
    mx[o] = max(mx[o], val);
    if (l == r) return;
    int m = (l + r) >> 1;
    if (pos <= m) update(lc[o], l, m, pos, val);
    else update(rc[o], m+1, r, pos, val);
}

int query(int o, int l, int r, int R) {
    if (!o || R < l) return -1;
    if (r <= R) return mx[o];
    int m = (l + r) >> 1;
    return max(query(lc[o], l, m, R), query(rc[o], m+1, r, R));
}

int main() {
    scanf("%d", &n);
    vector<int> disc(a, a+n);
    sort(disc.begin(), disc.end());
    disc.erase(unique(disc.begin(), disc.end()), disc.end());
    
    for (int i = 0; i < n; ++i) {
        scanf("%d", &a[i]);
        a[i] = lower_bound(disc.begin(), disc.end(), a[i]) - disc.begin() + 1;
        factorize(disc[a[i]-1], i);
    }

    memset(f, -1, sizeof f);
    f[0] = 0;
    int max_a = disc.size();
    
    for (int i = 1; i <= n; ++i) {
        int cur = -1;
        for (int p : primes[i-1]) {
            if (!pid.count(p)) pid[p] = 0;
            cur = max(cur, query(pid[p], 1, max_a, a[i-1]-1));
        }
        f[i] = (cur == -1) ? -1 : cur + 1;
        
        if (f[i-1] != -1) {
            for (int p : primes[i-1]) {
                update(pid[p], 1, max_a, a[i-1], f[i-1]);
            }
        }
    }
    printf("%d\n", f[n] > 0 ? f[n] : -1);
    return 0;
}
```

---

## 相似题目推荐
1. **P1972 [SDOI2009] HH的项链** - 区间查询与元素唯一性，线段树应用。
2. **P3383 【模板】线性筛素数** - 质数筛法练习，分解质因数基础。
3. **P5490 【模板】扫描线** - 线段树动态开点与离散化技巧。

---

## 可视化算法演示
**动画步骤**（伪代码）：
```javascript
class Visualization {
  constructor() {
    this.canvas = document.getElementById("canvas");
    this.ctx = this.canvas.getContext("2d");
    this.speed = 500; // 动画速度（ms/步）
    this.currentStep = 0;
  }

  // 绘制线段树结构
  drawSegmentTree(root, x, y, level) {
    // 以像素方块表示节点，颜色区分不同质因数
  }

  // 执行单步动画
  async step() {
    switch(this.currentStep) {
      case 0: // 分解质因数
        highlightNumber(a[i]);
        showFactors(primes[i]);
        break;
      case 1: // 线段树查询
        highlightPrimeNodes();
        showQueryPath();
        break;
      case 2: // DP 更新
        updateDPValue();
        playSuccessSound();
        break;
    }
    this.currentStep = (this.currentStep + 1) % 3;
  }
}
```

**复古效果**：
- **调色板**：16色，线段树节点用绿色（查询）、红色（更新）。
- **音效**：ChipTone 库生成 8-bit 音效，关键操作触发短音。
- **AI 模式**：自动逐步执行，按最优路径展示查询和更新过程。

---
处理用时：104.57秒