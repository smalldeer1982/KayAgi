# 题目信息

# Almost Triple Deletions

## 题目描述

You are given an integer $ n $ and an array $ a_1,a_2,\ldots,a_n $ .

In one operation, you can choose an index $ i $ ( $ 1 \le i \lt n $ ) for which $ a_i \neq a_{i+1} $ and delete both $ a_i $ and $ a_{i+1} $ from the array. After deleting $ a_i $ and $ a_{i+1} $ , the remaining parts of the array are concatenated.

For example, if $ a=[1,4,3,3,6,2] $ , then after performing an operation with $ i=2 $ , the resulting array will be $ [1,3,6,2] $ .

What is the maximum possible length of an array of equal elements obtainable from $ a $ by performing several (perhaps none) of the aforementioned operations?

## 说明/提示

For the first testcase, an optimal sequence of operations would be: $ [1,2,3,2,1,3,3] \rightarrow [3,2,1,3,3] \rightarrow [3,3,3] $ .

For the second testcase, all elements in the array are already equal.

For the third testcase, the only possible sequence of operations is: $ [1,1,1,2,2,2] \rightarrow [1,1,2,2] \rightarrow [1,2] \rightarrow [] $ . Note that, according to the statement, the elements deleted at each step must be different.

For the fourth testcase, the optimal sequence of operations is: $ [1,1,2,2,3,3,1,1] \rightarrow [1,1,2,3,1,1] \rightarrow [1,1,1,1] $ .

For the fifth testcase, one possible reachable array of two equal elements is $ [4,4] $ .

## 样例 #1

### 输入

```
5
7
1 2 3 2 1 3 3
1
1
6
1 1 1 2 2 2
8
1 1 2 2 3 3 1 1
12
1 5 2 3 3 3 4 4 4 4 3 3```

### 输出

```
3
1
0
4
2```

# AI分析结果



### 综合分析与结论

**题目核心**：通过删除相邻不同元素，使最终数组全同且最长。关键在于判断哪些区间可完全删除，并利用动态规划（DP）寻找最优解。

**核心难点与解决**：
1. **区间可删条件**：长度为偶数且众数不超过半数。通过预处理或动态维护计数数组快速判断。
2. **DP状态设计**：`f[i]`表示以`a[i]`结尾的最长可能长度，转移时需满足中间区间可删且前后元素相同。

**题解对比与要点**：
- **I_am_Accepted**：动态维护计数与最大值，避免显式存储预处理数组，节省空间。
- **Sellaris**：预处理所有区间的可删性，再通过标准DP转移。
- **Miraik**：类似思路，强调区间可删条件与DP状态转移的关系。

### 最优思路提炼

1. **区间可删条件**：偶数长度且众数出现次数 ≤ 长度/2。
2. **动态规划**：
   - 状态定义：`f[i]`表示处理到位置`i`时，以`a[i]`结尾的最大长度。
   - 转移方程：`f[i] = max(f[j] + 1)`，其中`a[i] = a[j]`且区间`(j, i-1)`可删。
3. **实现优化**：遍历时动态维护计数数组和最大值，避免预处理所有区间。

### 可视化算法分析

**动画设计**：
- **步骤演示**：展示数组逐步删除相邻不同元素的过程，高亮当前操作元素。
- **颜色标记**：
  - 红色：当前可删除的相邻元素对。
  - 绿色：已形成的全同部分。
- **动态计数**：实时显示当前区间的众数及其出现次数，验证可删条件。

**复古像素风格**：
- 使用Canvas绘制数组元素为像素方块，删除时播放8-bit音效。
- 自动模式模拟贪心删除策略，手动模式允许单步调试。

### 题解清单（≥4星）

1. **I_am_Accepted（⭐️⭐️⭐️⭐️⭐️）**
   - **亮点**：动态维护计数，高效节省空间；代码简洁，时间复杂度O(n²)。
   - **代码片段**：
     ```cpp
     For(i,0,n) {
         if(i && !f[i]) continue;
         fill(cnt, 0); mx = 0;
         For(j,i+1,n+1) {
             if (((j-i-1)%2 == 0) && mx*2 <= (j-i-1) && equ(a[i], a[j])) 
                 ckmx(f[j], f[i]+1);
             ckmx(mx, ++cnt[a[j]]);
         }
     }
     ```

2. **Sellaris（⭐️⭐️⭐️⭐️）**
   - **亮点**：预处理所有区间可删性，思路清晰；提供多种解法对比。
   - **代码片段**：
     ```cpp
     for(int i=1; i<=n; i++) {
         fill(tong, 0); mx = 0;
         for(int j=i; j<=n; j++) {
             tong[a[j]]++;
             mx = max(mx, tong[a[j]]);
             if ((j-i+1)%2 == 0 && mx <= (j-i+1)/2) 
                 dp[i][j] = 1;
         }
     }
     ```

3. **Miraik（⭐️⭐️⭐️⭐️）**
   - **亮点**：明确状态转移方程，强调前后区间可删性检查。
   - **代码逻辑**：
     ```cpp
     for(int i=1; i<=n; i++) {
         for(int j=0; j<i; j++) {
             if (a[i] == a[j] && can_remove[j+1][i-1]) 
                 f[i] = max(f[i], f[j]+1);
         }
     }
     ```

### 同类型题目推荐

1. **洛谷 P1880 [NOI1995] 石子合并**  
   - 区间DP，处理环形数组合并最大/最小得分。

2. **洛谷 P1043 数字游戏**  
   - 区间划分与动态规划，求极值问题。

3. **洛谷 P1063 能量项链**  
   - 环形区间DP，处理能量合并的最大值。

### 核心代码实现（I_am_Accepted）

```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 5003;
int cnt[N], a[N], f[N], n;

inline bool equ(int x, int y) {
    return x == 0 || y == n+1 || a[x] == a[y];
}

void work() {
    cin >> n;
    for (int i=1; i<=n; ++i) cin >> a[i];
    memset(f, 0, sizeof(f));
    f[0] = 1; // 虚拟起点
    for (int i=0; i<=n; ++i) {
        if (i && !f[i]) continue;
        memset(cnt, 0, sizeof(cnt));
        int mx = 0;
        for (int j=i+1; j<=n+1; ++j) {
            int len = j - i - 1;
            if (j <= n) ++cnt[a[j]];
            mx = max(mx, cnt[a[j]]);
            if (len % 2 == 0 && mx * 2 <= len && equ(i, j)) {
                f[j] = max(f[j], f[i] + (j <= n));
            }
        }
    }
    cout << f[n+1] - 1 << endl;
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) work();
    return 0;
}
```

### 可视化设计要点

- **Canvas绘制**：数组元素显示为彩色像素块，删除操作时元素对闪烁并消失。
- **音效反馈**：删除时播放“哔”声，达成全同时播放胜利音效。
- **自动模式**：AI自动选择可删区间，按最优策略逐步执行。
- **交互控制**：支持暂停/继续、调整速度，高亮当前判断区间和众数统计。

通过动态演示，直观展示区间删除和DP状态转移过程，帮助理解贪心策略与动态规划的结合。

---
处理用时：110.00秒