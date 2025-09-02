# 题目信息

# Same Count One

## 题目描述

给定 $n$ 个长度为 $m$ 的，只包含 $0$ 和 $1$ 的数组，选择任意两个数组交换位置 $pos$ 上的数。在经过最少的操作后使得每个数组中的 $1$ 数量相等，并输出操作过程。

## 样例 #1

### 输入

```
3
3 4
1 1 1 0
0 0 1 0
1 0 0 1
4 3
1 0 0
0 1 1
0 0 1
0 0 0
2 2
0 0
0 1```

### 输出

```
1
2 1 1
1
4 2 2
-1```

# AI分析结果



### 综合分析与结论

**题目核心**：通过交换同一位置上的元素，使每个数组的1的数量相等。关键在于如何最小化交换次数，确保总1数可均分。

**贪心策略**：
1. **有效性条件**：总1数必须是n的倍数，否则无解。
2. **目标值计算**：每个数组的目标1数 `k = sum / n`。
3. **按列处理**：遍历每一列，收集需要减少（当前1数>k且该列为1）和需要增加（当前1数<k且该列为0）的数组，进行配对交换。
4. **更新状态**：每次交换后更新两个数组的1的数量，确保后续处理正确。

**难点与解决**：
- **正确维护状态**：需动态维护每个数组的当前1的数量，但无需维护其他列的值，因每列独立处理。
- **避免无效交换**：通过按列处理并实时更新，确保每次交换有效减少总差异。

**可视化设计思路**：
- **动态高亮**：当前处理列用高亮显示，需要交换的数组用不同颜色标识（红/蓝）。
- **音效与动画**：交换时播放提示音，像素块动态交换，进度条显示剩余差异。
- **复古风格**：采用8位像素风格，数组显示为网格，操作步骤如游戏关卡。

---

### 题解评分（≥4星）

1. **WaterSun的题解（5星）**
   - **亮点**：维护数组值的实时状态，避免Hack；双指针排序处理高效。
   - **代码可读性**：结构清晰，动态更新`vis`数组确保正确性。
   - **优化程度**：排序优化配对效率，减少冗余检查。

2. **Dream_weavers的题解（4星）**
   - **亮点**：简洁直观，按列处理快速配对。
   - **不足**：未维护数组值，但通过正确维护`cnt`数组保证正确性。

3. **VinstaG173的题解（4星）**
   - **亮点**：数学证明严谨，代码简洁，强调操作次数的最优性。
   - **实现**：按列处理，动态更新`cnt`数组。

---

### 最优思路与代码

**核心贪心逻辑**：
```cpp
for (int pos = 0; pos < m; pos++) {
    vector<int> need_add, need_remove;
    // 收集需要增加和减少的数组
    for (int i = 0; i < n; i++) {
        if (cnt[i] > k && a[i][pos] == 1) need_remove.push_back(i);
        if (cnt[i] < k && a[i][pos] == 0) need_add.push_back(i);
    }
    // 配对交换
    int pairs = min(need_add.size(), need_remove.size());
    for (int j = 0; j < pairs; j++) {
        swap(a[need_add[j]][pos], a[need_remove[j]][pos]);
        cnt[need_add[j]]++;
        cnt[need_remove[j]]--;
        record_swap(need_add[j], need_remove[j], pos);
    }
}
```

**完整代码（WaterSun）**：
```cpp
#include <bits/stdc++.h>
using namespace std;

struct Answer { int a, b, pos; };

void solve() {
    int n, m, sum = 0;
    cin >> n >> m;
    vector<vector<bool>> a(n, vector<bool>(m));
    vector<int> cnt(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int x; cin >> x;
            a[i][j] = x;
            cnt[i] += x;
            sum += x;
        }
    }
    if (sum % n != 0) { cout << "-1\n"; return; }
    int k = sum / n;
    vector<Answer> ans;
    for (int pos = 0; pos < m; pos++) {
        vector<int> add, rem;
        for (int i = 0; i < n; i++) {
            if (cnt[i] < k && !a[i][pos]) add.push_back(i);
            if (cnt[i] > k && a[i][pos]) rem.push_back(i);
        }
        for (int i = 0; i < min(add.size(), rem.size()); i++) {
            ans.push_back({rem[i]+1, add[i]+1, pos+1});
            cnt[rem[i]]--;
            cnt[add[i]]++;
        }
    }
    cout << ans.size() << '\n';
    for (auto &it : ans) 
        cout << it.a << ' ' << it.b << ' ' << it.pos << '\n';
}
```

---

### 类似题目推荐

1. **P1090 合并果子** - 贪心选择最小代价合并。
2. **P1223 排队接水** - 时间安排贪心。
3. **P4995 跳跳！** - 最大差值贪心选择。

---

### 可视化算法演示

**动画方案**：
1. **网格表示**：每个数组为一行，列用不同颜色区分0/1。
2. **高亮当前列**：处理列时闪烁，需交换的行高亮。
3. **交换效果**：交换时元素飞动，更新计数。
4. **进度条**：显示当前总差异，随交换减少。

**复古游戏化**：
- **像素风格**：数组显示为8-bit网格，音效提示交换。
- **自动演示**：AI逐步处理列，用户可暂停/调速。
- **得分系统**：每次有效交换得分，连击加成。

**交互示例**：
```javascript
// 伪代码示例
function animateSwap(a, b, pos) {
    highlightColumn(pos);
    playSound('swap');
    movePixels(a, pos, b, pos);
    updateCounters(a, b);
}
```

---

**总结**：通过按列贪心交换，动态维护计数，确保最小操作次数。正确性依赖于实时状态更新，可视化可增强理解。

---
处理用时：275.63秒