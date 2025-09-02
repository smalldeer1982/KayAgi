# 题目信息

# [NOI Online #1 提高组] 冒泡排序

## 题目描述

给定一个 $1 ∼ n$ 的排列 $p_i$，接下来有 $m$ 次操作，操作共两种：
1. 交换操作：给定 $x$，将当前排列中的第 $x$ 个数与第 $x+1$ 个数交换位置。
2. 询问操作：给定 $k$，请你求出当前排列经过 $k$ 轮冒泡排序后的逆序对个数。
对一个长度为 $n$ 的排列 $p_i$ 进行一轮冒泡排序的伪代码如下：
```
for i = 1 to n-1:
  if p[i] > p[i + 1]:
    swap(p[i], p[i + 1])
```

## 说明/提示

#### 样例一解释
第一次操作：排列为 $\{1,2,3\}$，经过 0 轮冒泡排序后为 $\{1,2,3\}$，$0$ 个逆序对。

第二次操作：排列变为 $\{2,1,3\}$。

第三次操作：排列变为 $\{2,3,1\}$。

第四次操作：经过 $0$ 轮冒泡排序后排列变为 $\{2,3,1\}$，$2$ 个逆序对。

第五次操作：经过 $1$ 轮冒泡排序后排列变为 $\{2,1,3\}$，$1$ 个逆序对。

第六次操作：经过 $2$ 轮冒泡排序后排列变为 $\{1,2,3\}$，$0$ 个逆序对。

---

#### 数据范围与提示
对于测试点 1 ∼ 2：$n,m \leq 100$。

对于测试点 3 ∼ 4：$n,m \leq 2000$。

对于测试点 5 ∼ 6：交换操作个数不超过 $100$。

对于所有测试点：$2 \leq n,m \leq 2 \times 10^5$，$t_i \in \{1,2\}$，$1 \leq x < n$，$0 \leq k < 2^{31}$。

## 样例 #1

### 输入

```
3 6
1 2 3
2 0
1 1
1 2
2 0
2 1
2 2```

### 输出

```
0
2
1
0```

# AI分析结果


### 题目分析
本题考察冒泡排序中逆序对的变化规律。核心在于理解每轮冒泡排序对逆序对的影响：每轮排序会使每个非零逆序对计数减1，并分析交换操作对逆序对分布的动态影响。

### 算法思路
1. **初始逆序对计算**：
   - 使用树状数组计算每个位置前面比它大的数的个数（`b[i]`），并求总逆序对数 `total_cnt`。
   - 用两个树状数组 `tr_cnt` 和 `tr_sum` 分别维护 `b[i]` 值的分布（频率）和总和（`b[i]` 值 × 频率）。

2. **交换操作（类型1）**：
   - 若 `a[x] > a[x+1]`：
     - 原 `a[x+1]` 的逆序计数减1（因移除 `a[x]` 这个逆序对）。
     - 总逆序对数减1。
   - 若 `a[x] < a[x+1]`：
     - 原 `a[x]` 的逆序计数加1（因新增 `a[x+1]` 这个逆序对）。
     - 总逆序对数加1。
   - 交换 `a[x]` 和 `a[x+1]`，并交换对应的 `b` 值。
   - 更新树状数组：先删除旧 `b` 值的贡献，再添加新 `b` 值的贡献。

3. **查询操作（类型2）**：
   - 对 `k` 取最小值 `min(k, n-1)`（冒泡最多 `n-1` 轮）。
   - 计算 `b[i] ≤ k` 的个数 `c1` 和总和 `s1`。
   - 结果 = `(total_cnt - s1) - k × (n - c1)`。

### 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 200000 + 5;

class Fenwick {
private:
    int n;
    vector<ll> arr;
public:
    Fenwick(int size) : n(size), arr(size + 1, 0) {}
    void update(int i, ll delta) {
        while (i <= n) {
            arr[i] += delta;
            i += i & -i;
        }
    }
    ll query(int i) {
        ll s = 0;
        while (i) {
            s += arr[i];
            i -= i & -i;
        }
        return s;
    }
};

int n, m;
int a[maxn];
ll b[maxn];
ll total_cnt;
Fenwick *tr_cnt, *tr_sum;

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

    // 计算初始b数组
    Fenwick temp(n);
    for (int i = 1; i <= n; i++) {
        b[i] = (i - 1) - temp.query(a[i]);
        total_cnt += b[i];
        temp.update(a[i], 1);
    }

    // 初始化树状数组
    tr_cnt = new Fenwick(n);
    tr_sum = new Fenwick(n);
    for (int i = 1; i <= n; i++) {
        int pos = b[i] + 1;
        tr_cnt->update(pos, 1);
        tr_sum->update(pos, b[i]);
    }

    while (m--) {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op == 1) {
            // 删除旧贡献
            int pos_x = b[x] + 1;
            int pos_x1 = b[x + 1] + 1;
            tr_cnt->update(pos_x, -1);
            tr_sum->update(pos_x, -b[x]);
            tr_cnt->update(pos_x1, -1);
            tr_sum->update(pos_x1, -b[x + 1]);

            if (a[x] > a[x + 1]) {
                b[x + 1]--;
                total_cnt--;
                swap(a[x], a[x + 1]);
                swap(b[x], b[x + 1]);
            } else if (a[x] < a[x + 1]) {
                b[x]++;
                total_cnt++;
                swap(a[x], a[x + 1]);
                swap(b[x], b[x + 1]);
            } else {
                swap(a[x], a[x + 1]);
                swap(b[x], b[x + 1]);
            }

            // 添加新贡献
            pos_x = b[x] + 1;
            pos_x1 = b[x + 1] + 1;
            tr_cnt->update(pos_x, 1);
            tr_sum->update(pos_x, b[x]);
            tr_cnt->update(pos_x1, 1);
            tr_sum->update(pos_x1, b[x + 1]);
        } else {
            x = min(x, n - 1);
            if (x >= n - 1) {
                printf("0\n");
            } else {
                ll c1 = tr_cnt->query(x + 1);
                ll s1 = tr_sum->query(x + 1);
                ll ans = (total_cnt - s1) - (ll)x * (n - c1);
                printf("%lld\n", ans);
            }
        }
    }
    delete tr_cnt;
    delete tr_sum;
    return 0;
}
```

### 算法分析
- **时间复杂度**：初始预处理 `O(n log n)`，每次操作 `O(log n)`，总复杂度 `O((n + m) log n)`。
- **空间复杂度**：`O(n)`，使用树状数组存储。
- **优势**：高效处理动态逆序对变化，树状数组操作常数小。

### 可视化算法设计
#### 冒泡排序逆序对变化动画（像素风格）
**场景设计**：
- 8-bit像素风格，网格展示数组元素（不同颜色方块）。
- 控制面板：步进/播放/速度调节。

**动画流程**：
1. **初始状态**：
   - 显示数组值及对应 `b[i]`（上方数字）。
   - 高亮当前逆序对（红色连线）。

2. **冒泡过程**：
   - 每轮：从左到右扫描，交换相邻逆序对。
   - 元素移动时添加像素轨迹，交换时播放 "blip" 音效。
   - `b[i]` 值实时更新（绿色减1动画）。

3. **交换操作**：
   - 交互式交换：点击相邻方块，显示比较过程。
   - 若逆序：红色闪烁 + "error" 音效；否则蓝色闪烁 + "click" 音效。

4. **查询展示**：
   - 输入 `k` 后，快速展示 `k` 轮冒泡结果。
   - 结果区显示公式：`(total - sum_b) - k×(n - count_b)`。

**技术实现**：
- Canvas绘制网格和动画。
- Web Audio API添加音效。
- 速度控制滑块调节帧率。

此设计帮助学习者直观理解冒泡排序中逆序对的动态变化规律。

---
处理用时：392.12秒