# 题目信息

# Beautiful Triple Pairs

## 题目描述

Polycarp was given an array $ a $ of $ n $ integers. He really likes triples of numbers, so for each $ j $ ( $ 1 \le j \le n - 2 $ ) he wrote down a triple of elements $ [a_j, a_{j + 1}, a_{j + 2}] $ .

Polycarp considers a pair of triples $ b $ and $ c $ beautiful if they differ in exactly one position, that is, one of the following conditions is satisfied:

- $ b_1 \ne c_1 $ and $ b_2 = c_2 $ and $ b_3 = c_3 $ ;
- $ b_1 = c_1 $ and $ b_2 \ne c_2 $ and $ b_3 = c_3 $ ;
- $ b_1 = c_1 $ and $ b_2 = c_2 $ and $ b_3 \ne c_3 $ .

Find the number of beautiful pairs of triples among the written triples $ [a_j, a_{j + 1}, a_{j + 2}] $ .

## 说明/提示

In the first example, $ a = [3, 2, 2, 2, 3] $ , Polycarp will write the following triples:

1. $ [3, 2, 2] $ ;
2. $ [2, 2, 2] $ ;
3. $ [2, 2, 3] $ .

 The beautiful pairs are triple $ 1 $ with triple $ 2 $ and triple $ 2 $ with triple $ 3 $ .In the third example, $ a = [1, 2, 3, 2, 2, 3, 4, 2] $ , Polycarp will write the following triples:

1. $ [1, 2, 3] $ ;
2. $ [2, 3, 2] $ ;
3. $ [3, 2, 2] $ ;
4. $ [2, 2, 3] $ ;
5. $ [2, 3, 4] $ ;
6. $ [3, 4, 2] $ ;

 The beautiful pairs are triple $ 1 $ with triple $ 4 $ , triple $ 2 $ with triple $ 5 $ , and triple $ 3 $ with triple $ 6 $ .

## 样例 #1

### 输入

```
8
5
3 2 2 2 3
5
1 2 1 2 1
8
1 2 3 2 2 3 4 2
4
2 1 1 1
8
2 1 1 2 1 1 1 1
7
2 1 1 1 1 1 1
6
2 1 1 1 1 1
5
2 1 1 1 1```

### 输出

```
2
0
3
1
8
4
3
2```

# AI分析结果



# Beautiful Triple Pairs 题解分析

## 算法分类
**哈希表与容斥原理**

---

## 题解思路与解决难点
### 核心逻辑
- **问题建模**：每个三元组需要统计与之前三元组恰好有一个位置不同的对数。
- **哈希表统计**：用多个哈希表分别记录前两位相同、第一位和第三位相同、后两位相同的三元组数量。
- **容斥原理**：减去三个位置全相同的情况（每个全相同三元组会被三个部分统计重复计算三次）。

### 关键难点
- **重叠计数处理**：全相同的三元组会同时满足三个部分统计条件，需用容斥原理减去3倍的全相同计数。
- **高效哈希设计**：通过将三元组的不同位置组合编码为整数或pair，提高哈希表查询效率。

---

## 题解评分（≥4星）
1. **Eddie08012025（5星）**
   - **亮点**：代码结构清晰，使用tuple处理全相同情况，注释明确。
   - **代码片段**：
     ```cpp
     ans += a[make_pair(z[i-2], z[i-1])];
     ans += b[make_pair(z[i-2], z[i])];
     ans += c[make_pair(z[i-1], z[i])];
     ans -= d[make_tuple(z[i-2], z[i-1], z[i])]*3;
     ```

2. **DrAlfred（4星）**
   - **亮点**：通过枚举位置组合简化逻辑，代码简洁。
   - **关键代码**：
     ```cpp
     for (int i = 0; i < 3; i++) {
         for (int j = i + 1; j < 3; j++) {
             map<pair<int, int>, int> cnt;
             for (int k = 1; k <= n - 2; k++) {
                 ans += cnt[{a[k + i], a[k + j]}]++;
             }
         }
     }
     ```

3. **Weekoder（4星）**
   - **亮点**：使用大进制哈希压缩维度，优化查询速度。
   - **哈希技巧**：
     ```cpp
     a[i] * 133331 + a[i + 1]  // 前两位哈希
     a[i] * 133331 * 133331 + a[i + 1] * 133331 + a[i + 2]  // 全三位哈希
     ```

---

## 最优思路提炼
1. **哈希表分治**：用三个哈希表分别统计两位置相同的情况，一个哈希表统计全相同。
2. **容斥减法**：最终答案 = 部分相同统计值 - 3×全相同统计值。
3. **高效编码**：将三元组的部分或全部位置编码为整数或pair，避免嵌套数据结构。

---

## 类似题目
1. **CF1000D Yet Another Problem On a Subsequence**（三元组模式统计）
2. **LeetCode 2001. Number of Pairs of Interchangeable Rectangles**（哈希表统计比例）
3. **洛谷 P1102 A-B 数对**（哈希表统计差值）

---

## 可视化算法演示
### 动画设计
1. **数据结构展示**：
   - 用三个颜色区域分别表示前两位、第一位和第三位、后两位的哈希表。
   - 全相同哈希表用红色高亮。
2. **操作步骤**：
   - **步骤1**：处理新三元组`[3,2,2]`，更新前两位哈希表（键`(3,2)`，值+1）。
   - **步骤2**：查询前两位哈希表，累加当前键的已有值到答案。
   - **步骤3**：更新全相同哈希表，若已有相同键，答案减去3倍该值。
3. **动态效果**：
   - 三元组进入时，显示其在各哈希表的更新过程。
   - 减法操作时用红色闪烁提示容斥。

### 复古像素风格
- **颜色方案**：8-bit调色板（绿、蓝、黄分别表示三个部分哈希表，红色表示全相同）。
- **音效**：
  - 更新哈希表时播放短促“滴”声。
  - 容斥减法时播放“咔嚓”声。

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
#define int long long

signed main() {
    int t, n;
    cin >> t;
    while (t--) {
        cin >> n;
        vector<int> a(n);
        for (auto &x : a) cin >> x;

        map<pair<int, int>, int> cnt12, cnt13, cnt23;
        map<tuple<int, int, int>, int> cnt_all;
        int ans = 0;

        for (int i = 0; i <= n - 3; i++) {
            int x = a[i], y = a[i + 1], z = a[i + 2];
            
            ans += cnt12[{x, y}];
            ans += cnt13[{x, z}];
            ans += cnt23[{y, z}];
            ans -= 3 * cnt_all[{x, y, z}];

            cnt12[{x, y}]++;
            cnt13[{x, z}]++;
            cnt23[{y, z}]++;
            cnt_all[{x, y, z}]++;
        }
        cout << ans << "\n";
    }
    return 0;
}
```

---
处理用时：60.67秒