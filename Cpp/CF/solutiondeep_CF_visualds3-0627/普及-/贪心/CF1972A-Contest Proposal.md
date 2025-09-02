# 题目信息

# Contest Proposal

## 题目描述

A contest contains $ n $ problems and the difficulty of the $ i $ -th problem is expected to be at most $ b_i $ . There are already $ n $ problem proposals and the difficulty of the $ i $ -th problem is $ a_i $ . Initially, both $ a_1, a_2, \ldots, a_n $ and $ b_1, b_2, \ldots, b_n $ are sorted in non-decreasing order.

Some of the problems may be more difficult than expected, so the writers must propose more problems. When a new problem with difficulty $ w $ is proposed, the most difficult problem will be deleted from the contest, and the problems will be sorted in a way that the difficulties are non-decreasing.

In other words, in each operation, you choose an integer $ w $ , insert it into the array $ a $ , sort array $ a $ in non-decreasing order, and remove the last element from it.

Find the minimum number of new problems to make $ a_i\le b_i $ for all $ i $ .

## 说明/提示

In the first test case:

- Propose a problem with difficulty $ w=800 $ and $ a $ becomes $ [800,1000,1400,2000,2000,2200] $ .
- Propose a problem with difficulty $ w=1800 $ and $ a $ becomes $ [800,1000,1400,1800,2000,2000] $ .

It can be proved that it's impossible to reach the goal by proposing fewer new problems.

In the second test case:

- Propose a problem with difficulty $ w=1 $ and $ a $ becomes $ [1,4,5,6,7,8] $ .
- Propose a problem with difficulty $ w=2 $ and $ a $ becomes $ [1,2,4,5,6,7] $ .
- Propose a problem with difficulty $ w=3 $ and $ a $ becomes $ [1,2,3,4,5,6] $ .

It can be proved that it's impossible to reach the goal by proposing fewer new problems.

## 样例 #1

### 输入

```
2
6
1000 1400 2000 2000 2200 2700
800 1200 1500 1800 2200 3000
6
4 5 6 7 8 9
1 2 3 4 5 6```

### 输出

```
2
3```

# AI分析结果



## 算法分类
**贪心算法**

## 综合分析与结论
题目要求通过插入新问题，使得调整后的难度数组每个元素不超过预期数组对应位置的值，且插入次数最少。核心思路是利用贪心策略，从后向前匹配两数组元素，尽可能保留较大的a元素匹配较大的b元素，无法匹配时插入新元素。

**核心难点**在于如何高效确定必须替换的a元素数量，并保证每次插入操作最优。通过从后向前的双指针遍历，每次比较当前最大元素，若a[i]超过b[j]则必须插入，否则保留。该策略确保每次插入操作替换掉最大的无效元素，从而最小化插入次数。

**可视化设计**可展示双指针移动过程，高亮当前比较的a[i]与b[j]，插入时显示替换最大元素。复古像素风格中，用不同颜色标记匹配成功/失败，音效提示插入操作。自动演示模式可逐步展示指针移动与插入计数变化。

## 题解评分（5星）
### 题解1：贪心双指针法（5星）
- **思路清晰**：从后往前匹配，直观反映替换逻辑。
- **代码简洁**：仅需一次遍历，时间复杂度O(n)。
- **最优性证明**：贪心策略确保每次操作局部最优，整体最优。
- **可读性高**：代码逻辑与问题描述直接对应。

## 最优思路提炼
**关键技巧**：逆序双指针贪心匹配。维护两个指针从末尾开始，若当前a元素可保留则同步前移，否则计数插入并仅前移a指针。此方法最大化保留可用元素，保证最小插入次数。

## 同类型题推荐
1. **CF977D**：贪心逆序构造序列。
2. **LeetCode 870. Advantage Shuffle**：贪心匹配最大可能元素。
3. **洛谷P1090**：贪心合并有序序列。

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < n; i++) cin >> b[i];
        sort(a.begin(), a.end());
        sort(b.begin(), b.end());
        
        int i = n - 1, j = n - 1, ans = 0;
        while (i >= 0 && j >= 0) {
            if (a[i] <= b[j]) {
                i--;
                j--;
            } else {
                ans++;
                i--;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
```

## 可视化算法演示
**动画设计**：
1. **初始状态**：显示排序后的a、b数组，指针i、j位于末尾。
2. **比较步骤**：高亮a[i]和b[j]，红色表示a[i] > b[j]（需插入），绿色表示可保留。
3. **插入操作**：插入新元素后，最大a元素被删除，指针i左移，计数器增加。
4. **结束条件**：当任意指针越界时停止，显示最终插入次数。

**复古风格**：
- 像素方块表示数组元素，移动指针时有8-bit音效。
- 插入时播放“哔”声，成功匹配播放“叮”声。
- Canvas动态绘制指针移动与元素替换，背景循环芯片音乐。

**交互功能**：
- 步进控制：空格键单步执行。
- 速度调节：滑块调整动画速度。
- 自动模式：AI自动运行，展示完整流程。

---
处理用时：159.88秒