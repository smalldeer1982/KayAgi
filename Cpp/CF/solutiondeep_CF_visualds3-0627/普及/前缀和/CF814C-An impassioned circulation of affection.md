# 题目信息

# An impassioned circulation of affection

## 题目描述

Nadeko's birthday is approaching! As she decorated the room for the party, a long garland of Dianthus-shaped paper pieces was placed on a prominent part of the wall. Brother Koyomi will like it!

Still unsatisfied with the garland, Nadeko decided to polish it again. The garland has $ n $ pieces numbered from $ 1 $ to $ n $ from left to right, and the $ i $ -th piece has a colour $ s_{i} $ , denoted by a lowercase English letter. Nadeko will repaint at most $ m $ of the pieces to give each of them an arbitrary new colour (still denoted by a lowercase English letter). After this work, she finds out all subsegments of the garland containing pieces of only colour $ c $ — Brother Koyomi's favourite one, and takes the length of the longest among them to be the Koyomity of the garland.

For instance, let's say the garland is represented by "kooomo", and Brother Koyomi's favourite colour is "o". Among all subsegments containing pieces of "o" only, "ooo" is the longest, with a length of $ 3 $ . Thus the Koyomity of this garland equals $ 3 $ .

But problem arises as Nadeko is unsure about Brother Koyomi's favourite colour, and has swaying ideas on the amount of work to do. She has $ q $ plans on this, each of which can be expressed as a pair of an integer $ m_{i} $ and a lowercase letter $ c_{i} $ , meanings of which are explained above. You are to find out the maximum Koyomity achievable after repainting the garland according to each plan.

## 说明/提示

In the first sample, there are three plans:

- In the first plan, at most $ 1 $ piece can be repainted. Repainting the "y" piece to become "o" results in "kooomi", whose Koyomity of $ 3 $ is the best achievable;
- In the second plan, at most $ 4 $ pieces can be repainted, and "oooooo" results in a Koyomity of $ 6 $ ;
- In the third plan, at most $ 4 $ pieces can be repainted, and "mmmmmi" and "kmmmmm" both result in a Koyomity of $ 5 $ .

## 样例 #1

### 输入

```
6
koyomi
3
1 o
4 o
4 m
```

### 输出

```
3
6
5
```

## 样例 #2

### 输入

```
15
yamatonadeshiko
10
1 a
2 a
3 a
4 a
5 a
1 b
2 b
3 b
4 b
5 b
```

### 输出

```
3
4
5
7
8
1
2
3
4
5
```

## 样例 #3

### 输入

```
10
aaaaaaaaaa
2
10 b
10 z
```

### 输出

```
10
10
```

# AI分析结果



**算法分类**  
滑动窗口/双指针、预处理与记忆化  

---

**题解思路、算法要点与解决难点**  
- **核心问题**：每次询问允许修改最多 `m` 个字符，求最长连续 `c` 的子串。  
- **关键思路**：  
  1. **滑动窗口（双指针）**：对每个询问维护窗口，统计非 `c` 字符数量，调整窗口至符合条件。  
  2. **预处理与记忆化**：按需处理每个 `(m, c)` 组合，保存结果避免重复计算。  
  3. **前缀和优化**：预处理字符出现次数，快速计算区间内需修改的字符数。  

- **难点对比**：  
  - **双指针法**（时间复杂度 `O(nq)`）：直接处理每个询问，但无法应对大 `q`。  
  - **预处理法**（如Galex）：需处理所有可能的区间，但缺少前缀最大值步骤，可能导致错误。  
  - **动态预处理**（lnwhl）：按需处理 `(m, c)` 组合，时间复杂度 `O(26n² + q)`，高效且正确。  

---

**题解评分 (≥4星)**  
1. **Luo_gu_ykc（4星）**：思路清晰，代码直观，适用于小规模数据。  
2. **Ninelife_Cat（4星）**：结合前缀和优化双指针，代码易读。  
3. **lnwhl（5星）**：动态预处理与记忆化，高效处理大规模查询。  

---

**最优思路或技巧提炼**  
- **动态预处理+记忆化**：对首次遇到的 `(m, c)` 组合，用双指针计算并存储结果。后续查询直接返回，时间复杂度优化至 `O(26n² + q)`。  
- **滑动窗口核心逻辑**：  
  ```cpp
  int l = 1, r = 1, ans = 0;
  while (r <= n) {
    while (非c字符数超过m) l++;
    ans = max(ans, r - l + 1);
    r++;
  }
  ```

---

**同类型题或类似算法套路**  
- **滑动窗口**：适用于连续子串/子数组的最值问题（如允许修改k次的最长连续1）。  
- **预处理+记忆化**：适用于多组查询且存在重复参数的场景。  

**推荐题目**  
1. [LeetCode 1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/)  
2. [洛谷 P4551 最长异或路径](https://www.luogu.com.cn/problem/P4551)  
3. [CF 1328D Carousel](https://codeforces.com/problemset/problem/1328/D)  

---

**个人心得摘录**  
- **预处理陷阱**：Galex的解法因缺少前缀最大值步骤，导致某些情况结果错误。  
- **动态预处理优势**：按需处理避免无效计算，适合实际数据中的重复查询。  

---

**可视化与算法演示**  
- **动画方案**：  
  1. **滑动窗口演示**：  
     - **高亮**当前窗口范围，红色标记非 `c` 字符。  
     - **动态调整**：左指针右移时，红色标记减少，右指针扩展时新增标记。  
  2. **记忆化过程**：显示已处理的 `(m, c)` 组合，用不同颜色区分缓存命中。  

- **复古像素风格**：  
  - **Canvas网格**：字符用8位像素块表示，修改操作以闪光效果呈现。  
  - **音效**：滑动时播放“滴”声，命中缓存时播放胜利音效。  

---

**核心代码实现（lnwhl解法）**  
```cpp
#include <bits/stdc++.h>
using namespace std;
int n, q, sum[1505][30], f[1505][30];
string s;

int main() {
    cin >> n >> s >> q;
    s = ' ' + s;
    // 预处理前缀和
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 26; ++j) sum[i][j] = sum[i-1][j];
        sum[i][s[i]-'a']++;
    }
    // 处理查询
    while (q--) {
        int m; char c;
        cin >> m >> c;
        if (f[m][c-'a']) { // 记忆化直接返回
            cout << f[m][c-'a'] << endl;
            continue;
        }
        int l = 1, r = 1, ans = 0;
        while (r <= n) {
            // 计算当前窗口非c字符数
            int non_c = (r - l + 1) - (sum[r][c-'a'] - sum[l-1][c-'a']);
            if (non_c > m) l++;
            else {
                ans = max(ans, r - l + 1);
                r++;
            }
        }
        f[m][c-'a'] = ans; // 保存结果
        cout << ans << endl;
    }
    return 0;
}
```

---
处理用时：466.20秒