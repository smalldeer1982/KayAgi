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



---

**算法分类**  
排序、滑动窗口、前缀和

---

**题解思路与算法要点**  
1. **核心思路**  
   Sasha需选择位置x，使得关闭最多k个酒吧后，剩余酒吧到x的距离和最小。最优策略是关闭离x最远的k个酒吧，保留最近的m = n -k个。通过滑动窗口遍历所有可能的连续m个酒吧，计算每个窗口的总距离和，并统计满足条件的x数目。

2. **关键步骤**  
   - **排序酒吧位置**：确保后续滑动窗口的有效性。  
   - **前缀和优化**：快速计算窗口内元素的总和。  
   - **滑动窗口遍历**：对每个窗口，计算其总距离和的最小值。  
   - **奇偶分情况处理**：根据m的奇偶性，确定x的候选区间。

3. **解决难点**  
   - **高效计算总距离和**：通过前缀和数组，将时间复杂度优化至O(n)。  
   - **候选区间合并**：处理m为偶数时的连续区间，避免重复计算。

---

**最优思路提炼**  
- **排序与滑动窗口**：通过排序和滑动窗口处理连续区间。  
- **前缀和优化**：快速计算窗口内元素的总和，避免重复遍历。  
- **奇偶分治**：根据窗口长度的奇偶性，统一处理总距离和的计算，简化代码逻辑。

---

**代码实现**  
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    
    int m = n - k;
    if (m <= 0) {
        cout << (int)1e9 << endl;
        return 0;
    }
    
    vector<long long> pre_sum(n + 1);
    for (int i = 0; i < n; ++i) {
        pre_sum[i + 1] = pre_sum[i] + a[i];
    }
    
    long long min_sum = LLONG_MAX;
    for (int i = 0; i <= n - m; ++i) {
        int left_size = m / 2;
        long long sum_left = pre_sum[i + left_size] - pre_sum[i];
        long long sum_right;
        if (m % 2 == 1) {
            sum_right = pre_sum[i + m] - pre_sum[i + left_size + 1];
        } else {
            sum_right = pre_sum[i + m] - pre_sum[i + left_size];
        }
        long long total = sum_right - sum_left;
        if (total < min_sum) {
            min_sum = total;
        }
    }
    
    long long ans = 0;
    for (int i = 0; i <= n - m; ++i) {
        int left_size = m / 2;
        long long sum_left = pre_sum[i + left_size] - pre_sum[i];
        long long sum_right;
        if (m % 2 == 1) {
            sum_right = pre_sum[i + m] - pre_sum[i + left_size + 1];
        } else {
            sum_right = pre_sum[i + m] - pre_sum[i + left_size];
        }
        long long total = sum_right - sum_left;
        if (total != min_sum) continue;
        
        if (m % 2 == 1) {
            ans += 1;
        } else {
            int mid_left = i + left_size - 1;
            int mid_right = mid_left + 1;
            ans += (a[mid_right] - a[mid_left] + 1);
        }
    }
    cout << ans << endl;
    return 0;
}
```

---

**可视化与算法演示**  
1. **动画设计**  
   - **排序步骤**：用像素块展示排序后的酒吧位置。  
   - **滑动窗口**：高亮当前窗口的起始和结束位置，动态计算总距离和。  
   - **奇偶分治**：用不同颜色区分奇偶窗口的中位数和区间范围。

2. **复古像素风格**  
   - **颜色方案**：用16色调色板区分酒吧、窗口、候选区间。  
   - **音效**：滑动窗口时触发“点击”音效，找到最小值时播放胜利音效。

---

**同类型题目推荐**  
1. [P1886 滑动窗口](https://www.luogu.com.cn/problem/P1886)  
2. [P1638 逛画展](https://www.luogu.com.cn/problem/P1638)  
3. [P1714 切蛋糕](https://www.luogu.com.cn/problem/P1714)

---
处理用时：332.75秒