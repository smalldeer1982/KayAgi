# 题目信息

# Binary Search

## 题目描述

Anton got bored during the hike and wanted to solve something. He asked Kirill if he had any new problems, and of course, Kirill had one.

You are given a permutation $ p $ of size $ n $ , and a number $ x $ that needs to be found. A permutation of length $ n $ is an array consisting of $ n $ distinct integers from $ 1 $ to $ n $ in arbitrary order. For example, $ [2,3,1,5,4] $ is a permutation, but $ [1,2,2] $ is not a permutation ( $ 2 $ appears twice in the array), and $ [1,3,4] $ is also not a permutation ( $ n=3 $ but there is $ 4 $ in the array).

You decided that you are a cool programmer, so you will use an advanced algorithm for the search — binary search. However, you forgot that for binary search, the array must be sorted.

You did not give up and decided to apply this algorithm anyway, and in order to get the correct answer, you can perform the following operation no more than $ 2 $ times before running the algorithm: choose the indices $ i $ , $ j $ ( $ 1\le i, j \le n $ ) and swap the elements at positions $ i $ and $ j $ .

After that, the binary search is performed. At the beginning of the algorithm, two variables $ l = 1 $ and $ r = n + 1 $ are declared. Then the following loop is executed:

1. If $ r - l = 1 $ , end the loop
2. $ m = \lfloor \frac{r + l}{2} \rfloor $
3. If $ p_m \le x $ , assign $ l = m $ , otherwise $ r = m $ .

The goal is to rearrange the numbers in the permutation before the algorithm so that after the algorithm is executed, $ p_l $ is equal to $ x $ . It can be shown that $ 2 $ operations are always sufficient.

## 样例 #1

### 输入

```
5
6 3
1 2 3 4 5 6
6 5
3 1 6 5 2 4
5 1
3 5 4 2 1
6 3
4 3 1 5 2 6
3 2
3 2 1```

### 输出

```
0
1
3 4
2
2 4
1 5
2
4 5
2 4
1
1 3```

# AI分析结果



## 算法分类
**二分**

## 综合分析与结论
### 核心思路
题目要求在最多两次交换后，使得特定二分逻辑最终定位到目标值x。所有题解的核心思路均基于以下观察：

1. **直接模拟原二分过程**，找到算法终止时的位置l。
2. 若此时`a[l] == x`，无需任何操作。
3. 否则**交换x的原位置与位置l**，仅需一次操作即可保证后续二分正确。

### 解决难点与关键证明
- **交换的正确性**：无论原数组中x是否被二分过程访问，交换后均不影响二分路径。因为：
  - 若x被访问过，则其值<=x，交换后位置l的值仍满足条件。
  - 若x未被访问，则原二分路径未受x位置影响，交换后路径不变。

### 可视化设计要点
- **动画方案**：
  1. 初始展示数组，高亮x的位置。
  2. 逐步模拟二分过程，动态更新l、r、mid，用不同颜色标记当前mid和比较结果。
  3. 二分结束后，用闪烁效果突出l位置，并演示交换x与l的过程。
- **复古像素风格**：
  - 使用8-bit风格网格，每个元素显示为像素块，数值显示在中央。
  - 每次mid计算时播放“滴”声，交换时播放“咔嚓”音效，成功时播放胜利音效。
  - 自动模式下，二分过程以0.5秒/步自动执行，用户可暂停/单步调试。

## 题解评分 (≥4星)
1. **Sternenlicht (5星)**
   - **亮点**：通过分类讨论严格证明交换的正确性，代码简洁高效。
   - **代码**：直接模拟二分后交换，仅需20行核心逻辑。
2. **__Floze3__ (4.5星)**
   - **亮点**：用反证法证明l的性质，代码高度优化，无冗余判断。
3. **Sorato_ (4星)**
   - **亮点**：用极简代码实现，附详细注释，适合快速理解。

## 最优思路提炼
1. **模拟二分找l**：无需预排序，直接按题目给定逻辑计算最终l。
2. **交换即解**：无论原数组如何，交换x与l的位置可保证后续二分正确。
3. **无需二次操作**：题目允许两次交换，但实际最优解仅需一次。

## 类似题目推荐
1. **P1020 导弹拦截**（二分求最长不升子序列）
2. **P2678 跳石头**（二分答案+可行性验证）
3. **P2440 木材加工**（二分答案典型应用）

## 核心代码实现
```cpp
int main() {
    int T; cin >> T;
    while (T--) {
        int n, x, pos;
        cin >> n >> x;
        vector<int> a(n+1);
        for (int i=1; i<=n; i++) {
            cin >> a[i];
            if (a[i] == x) pos = i;
        }
        int l=1, r=n+1;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (a[mid] <= x) l = mid;
            else r = mid;
        }
        if (a[l] == x) cout << "0\n";
        else cout << "1\n" << l << ' ' << pos << '\n';
    }
}
```

## 可视化代码片段（Canvas动画）
```javascript
// 初始化8-bit风格网格
function drawArray(ctx, arr, l, r, mid, xPos) {
    ctx.clearRect(0, 0, 800, 100);
    for (let i=0; i<arr.length; i++) {
        ctx.fillStyle = i === mid ? '#FF0000' : (i >= l && i < r) ? '#00FF00' : '#999';
        ctx.fillRect(i*50, 0, 48, 48);
        ctx.fillText(arr[i], i*50+10, 30);
    }
    ctx.fillStyle = '#0000FF';
    ctx.fillRect(xPos*50, 50, 48, 48); // 高亮x位置
}
```

---
处理用时：70.04秒