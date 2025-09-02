# 题目信息

# Wooden Toy Festival

## 题目描述

In a small town, there is a workshop specializing in woodwork. Since the town is small, only three carvers work there.

Soon, a wooden toy festival is planned in the town. The workshop employees want to prepare for it.

They know that $ n $ people will come to the workshop with a request to make a wooden toy. People are different and may want different toys. For simplicity, let's denote the pattern of the toy that the $ i $ -th person wants as $ a_i $ ( $ 1 \le a_i \le 10^9 $ ).

Each of the carvers can choose an integer pattern $ x $ ( $ 1 \le x \le 10^9 $ ) in advance, different carvers can choose different patterns. $ x $ is the integer. During the preparation for the festival, the carvers will perfectly work out the technique of making the toy of the chosen pattern, which will allow them to cut it out of wood instantly. To make a toy of pattern $ y $ for a carver who has chosen pattern $ x $ , it will take $ |x - y| $ time, because the more the toy resembles the one he can make instantly, the faster the carver will cope with the work.

On the day of the festival, when the next person comes to the workshop with a request to make a wooden toy, the carvers can choose who will take on the job. At the same time, the carvers are very skilled people and can work on orders for different people simultaneously.

Since people don't like to wait, the carvers want to choose patterns for preparation in such a way that the maximum waiting time over all people is as small as possible.

Output the best maximum waiting time that the carvers can achieve.

## 说明/提示

In the first example, the carvers can choose patterns $ 1 $ , $ 7 $ , $ 9 $ for preparation.

In the second example, the carvers can choose patterns $ 3 $ , $ 30 $ , $ 60 $ for preparation.

In the third example, the carvers can choose patterns $ 14 $ , $ 50 $ , $ 85 $ for preparation.

## 样例 #1

### 输入

```
5
6
1 7 7 9 9 9
6
5 4 2 1 30 60
9
14 19 37 59 1 4 4 98 73
1
2
6
3 10 1 17 15 11```

### 输出

```
0
2
13
0
1```

# AI分析结果

### 题目内容重写（中文）

在一个小镇上，有一家专门从事木工的工作坊。由于小镇很小，只有三位雕刻师在那里工作。

不久，小镇计划举办一个木制玩具节。工作坊的员工们想为此做好准备。

他们知道，将有 $n$ 个人来到工作坊，要求制作木制玩具。人们各不相同，可能想要不同的玩具。为简单起见，我们用 $a_i$ 表示第 $i$ 个人想要的玩具的样式（$1 \le a_i \le 10^9$）。

每位雕刻师可以预先选择一个整数样式 $x$（$1 \le x \le 10^9$），不同的雕刻师可以选择不同的样式。$x$ 是整数。在节日准备期间，雕刻师们将熟练掌握所选样式的玩具制作技术，使他们能够立即从木材中切割出该样式的玩具。对于选择样式 $x$ 的雕刻师来说，制作样式为 $y$ 的玩具需要 $|x - y|$ 的时间，因为玩具越接近他能够立即制作的样式，雕刻师完成工作的速度就越快。

在节日当天，当下一个人来到工作坊要求制作木制玩具时，雕刻师们可以选择由谁来承担这项工作。同时，雕刻师们非常熟练，可以同时处理不同人的订单。

由于人们不喜欢等待，雕刻师们希望选择准备样式，使得所有人的最大等待时间尽可能小。

输出雕刻师们可以达到的最佳最大等待时间。

### 算法分类
二分

### 题解分析与结论

本题的核心是通过二分法来寻找最小的最大等待时间。多个题解都采用了二分答案的思路，通过检查某个等待时间是否可行来缩小搜索范围。以下是各题解的主要思路和难点对比：

1. **MornStar的题解**：
   - 思路：将数组排序后，枚举三个区间的分界点，计算每个区间的贡献，并使用二分优化。
   - 难点：如何高效地找到三个区间的分界点，使得最大等待时间最小。
   - 优化：通过二分法优化了分界点的查找，时间复杂度为 $O(n \log n)$。
   - 评分：4星
   - 关键亮点：通过二分法优化了分界点的查找，代码清晰，思路明确。

2. **xing_yue的题解**：
   - 思路：将问题转化为区间选点问题，使用二分法检查是否可以用不超过3个点覆盖所有区间。
   - 难点：如何将问题转化为区间选点问题，并设计高效的检查函数。
   - 优化：通过排序和贪心策略，快速检查某个等待时间是否可行。
   - 评分：4星
   - 关键亮点：将问题转化为区间选点问题，思路清晰，代码简洁。

3. **Jerry_heng的题解**：
   - 思路：从左到右搜索，看是否能在3次以内处理完所有订单，使用二分法优化。
   - 难点：如何设计高效的搜索策略，确保在3次内处理完所有订单。
   - 优化：通过二分法优化了搜索过程，时间复杂度为 $O(n \log n)$。
   - 评分：4星
   - 关键亮点：通过二分法优化了搜索过程，代码简洁，思路明确。

### 最优关键思路或技巧
- **二分答案**：通过二分法寻找最小的最大等待时间，结合排序和贪心策略，快速检查某个等待时间是否可行。
- **区间选点**：将问题转化为区间选点问题，通过贪心策略快速确定是否可以用不超过3个点覆盖所有区间。

### 可拓展之处
- 类似的问题可以通过二分答案和贪心策略来解决，例如在资源分配、任务调度等问题中，寻找最优的分配方案。

### 推荐题目
1. [P1020 导弹拦截](https://www.luogu.com.cn/problem/P1020)
2. [P1083 借教室](https://www.luogu.com.cn/problem/P1083)
3. [P1182 数列分段 Section II](https://www.luogu.com.cn/problem/P1182)

### 个人心得摘录
- **MornStar**：在第一个区间右端点确定的情况下，剩下的两个区间最大值要尽可能小，那么剩余两个区间产生的贡献就要尽可能相等。
- **Jerry_heng**：比赛结束前5分钟才调出来，调试过程中发现二分边界处理不当，导致WA，最终通过调整边界条件AC。

### 核心代码片段
```cpp
// MornStar的二分法优化代码
int l = 1, r = n;
while (l < r) {
    int mid = (l + r) >> 1;
    ans = min(ans, (max(max(a[i] - a[1], a[mid] - a[i + 1]), a[n] - a[mid + 1]) + 1) / 2);
    if ((a[mid] - a[i + 1] + 1) / 2 <= (a[n] - a[mid + 1] + 1) / 2) l = mid + 1;
    else r = mid;
}
```

```cpp
// xing_yue的区间选点代码
bool check(int x) {
    for (int i = 1; i <= n; i++) {
        t[i].l = a[i] - x;
        t[i].r = a[i] + x;
    }
    sort(t + 1, t + n + 1, cmp);
    int ans = 1, f = t[1].r;
    for (int i = 2; i <= n; i++) {
        if (t[i].l > f) {
            f = t[i].r;
            ans++;
        }
    }
    return ans <= 3;
}
```

```cpp
// Jerry_heng的二分法优化代码
bool check(int x) {
    int l = 1, r = 1;
    int cnt = 0;
    while (++cnt) {
        if (cnt == 4) return 0;
        while (r < n && a[r + 1] <= a[l] + 2 * x) r++;
        if (r == n) break;
        l = r + 1, r++;
    }
    return 1;
}
```

---
处理用时：40.47秒