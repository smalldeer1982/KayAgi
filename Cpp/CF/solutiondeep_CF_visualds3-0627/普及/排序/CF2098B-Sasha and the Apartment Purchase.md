# 题目信息

# Sasha and the Apartment Purchase

## 题目描述

Sasha 想在一条街道上购买一套公寓，这条街道上的房屋从左到右编号为 $1$ 到 $10^9$。

这条街道上有 $n$ 家酒吧，分别位于编号为 $a_1, a_2, \ldots, a_n$ 的房屋中。注意，可能有多个酒吧位于同一房屋中，这种情况下这些酒吧被视为不同的酒吧。

Sasha 担心在他购买公寓时，部分酒吧可能会关闭，但最多不超过 $k$ 家酒吧会关闭。

对于任意编号为 $x$ 的房屋，定义 $f(x)$ 为所有开放酒吧 $y$（即关闭部分酒吧后）的 $|x - y|$ 之和。

Sasha 可以购买编号为 $x$（$1 \le x \le 10^9$）的房屋中的公寓，当且仅当可以通过关闭最多 $k$ 家酒吧，使得 $f(x)$ 在所有房屋中达到最小值。

请确定 Sasha 可以购买公寓的不同房屋数量。

## 说明/提示

在第一个测试用例中，没有酒吧可以关闭，因此只有编号为 $2$ 和 $3$ 的房屋是合适的。对于编号为 $2$ 的房屋，距离之和为 $|2 - 1| + |2 - 2| + |2 - 3| + |2 - 4| = 4$；对于编号为 $3$ 的房屋，距离之和为 $|3 - 1| + |3 - 2| + |3 - 3| + |3 - 4| = 4$。然而，对于编号为 $1$ 的房屋，距离之和为 $|1 - 1| + |1 - 2| + |1 - 3| + |1 - 4| = 6$，因此编号为 $1$ 的房屋不合适。可以证明 Sasha 也无法在其他房屋购买公寓。

在第二个测试用例中，合适的房屋编号为 $6$ 和 $7$。如果 Sasha 选择编号为 $6$ 的房屋，只需不关闭任何酒吧。如果 Sasha 选择编号为 $7$ 的房屋，可以关闭编号为 $1$ 和 $6$ 的房屋中的酒吧。此时开放的酒吧将位于编号为 $6$、$7$ 和 $7$ 的房屋中。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
4 0
1 2 3 4
5 2
7 6 6 7 1
3 1
6 7 9
6 2
5 1 9 10 13 2```

### 输出

```
2
2
4
9```

# AI分析结果



## 算法分类
**滑动窗口与区间合并**

---

## 综合分析与结论

### 核心思路
1. **排序与滑动窗口**：将酒吧位置排序后，用滑动窗口遍历所有可能的连续 `m = n - k` 长度的子数组。
2. **中位数区间计算**：根据子数组长度的奇偶性，计算每个子数组对应的中位数区间：
   - **奇数**：区间为单个点 `[a[mid], a[mid]]`。
   - **偶数**：区间为两个中间点之间的所有整数 `[a[mid_low], a[mid_high]]`。
3. **区间合并**：所有子数组生成的区间按顺序合并，统计总覆盖的整数点数目。

### 解决难点
- **中位数性质**：利用排序后的数组，快速确定每个子数组的中位数区间。
- **高效合并**：由于子数组的中位数区间按顺序递增，合并只需线性时间。

### 可视化设计
1. **动画流程**：
   - **排序阶段**：展示原始酒吧位置排序过程。
   - **滑动窗口**：高亮当前子数组，标记中位数区间。
   - **区间合并**：动态合并区间，用颜色区分已合并区域。
2. **复古像素风格**：
   - 用网格表示排序后的数组，窗口滑动时用不同颜色块标记。
   - 音效：滑动时播放“移动”音效，合并成功时播放“成功”音效。
3. **交互控制**：
   - 步进控制：手动调整窗口滑动速度。
   - 自动演示：按预设速度自动完成整个过程。

---

## 题解清单
无其他题解，以下为最优解法：

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];
        sort(a.begin(), a.end());
        int m = n - k;
        if (m <= 0) {
            cout << 1000000000 << endl;
            continue;
        }
        vector<pair<int, int>> intervals;
        for (int left = 0; left + m <= n; ++left) {
            if (m % 2 == 1) {
                int mid = left + (m - 1) / 2;
                intervals.emplace_back(a[mid], a[mid]);
            } else {
                int mid_low = left + m / 2 - 1;
                int mid_high = left + m / 2;
                intervals.emplace_back(a[mid_low], a[mid_high]);
            }
        }
        // 合并区间
        if (intervals.empty()) {
            cout << 0 << endl;
            continue;
        }
        vector<pair<int, int>> merged;
        int current_start = intervals[0].first;
        int current_end = intervals[0].second;
        for (size_t i = 1; i < intervals.size(); ++i) {
            int s = intervals[i].first, e = intervals[i].second;
            if (s <= current_end + 1) {
                current_end = max(current_end, e);
            } else {
                merged.emplace_back(current_start, current_end);
                current_start = s;
                current_end = e;
            }
        }
        merged.emplace_back(current_start, current_end);
        // 计算总长度
        int ans = 0;
        for (auto &p : merged) {
            ans += p.second - p.first + 1;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

## 最优思路提炼
1. **排序预处理**：将酒吧位置排序以方便滑动窗口处理。
2. **滑动窗口遍历**：枚举每个可能的连续子数组，计算其对应的中位数区间。
3. **奇偶分治**：根据子数组长度的奇偶性，确定区间端点。
4. **合并区间**：按顺序合并所有区间，统计总覆盖点数目。

---

## 相似题目推荐
1. **洛谷 P1168**：滑动窗口中位数。
2. **洛谷 P1886**：滑动窗口最值。
3. **LeetCode 56**：合并区间（通用区间合并方法）。

---
处理用时：320.95秒