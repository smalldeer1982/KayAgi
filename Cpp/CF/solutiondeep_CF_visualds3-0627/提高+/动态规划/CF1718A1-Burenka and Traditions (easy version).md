# 题目信息

# Burenka and Traditions (easy version)

## 题目描述

This is the easy version of this problem. The difference between easy and hard versions is only the constraints on $ a_i $ and on $ n $ . You can make hacks only if both versions of the problem are solved.

Burenka is the crown princess of Buryatia, and soon she will become the $ n $ -th queen of the country. There is an ancient tradition in Buryatia — before the coronation, the ruler must show their strength to the inhabitants. To determine the strength of the $ n $ -th ruler, the inhabitants of the country give them an array of $ a $ of exactly $ n $ numbers, after which the ruler must turn all the elements of the array into zeros in the shortest time. The ruler can do the following two-step operation any number of times:

- select two indices $ l $ and $ r $ , so that $ 1 \le l \le r \le n $ and a non-negative integer $ x $ , then
- for all $ l \leq i \leq r $ assign $ a_i := a_i \oplus x $ , where $ \oplus $ denotes the [bitwise XOR operation](https://en.wikipedia.org/wiki/Bitwise_operation#XOR). It takes $ \left\lceil \frac{r-l+1}{2} \right\rceil $ seconds to do this operation, where $ \lceil y \rceil $ denotes $ y $ rounded up to the nearest integer.

Help Burenka calculate how much time she will need.

## 说明/提示

In the first test case, Burenka can choose segment $ l = 1 $ , $ r = 4 $ , and $ x=5 $ . so it will fill the array with zeros in $ 2 $ seconds.

In the second test case, Burenka first selects segment $ l = 1 $ , $ r = 2 $ , and $ x = 1 $ , after which $ a = [0, 2, 2] $ , and then the segment $ l = 2 $ , $ r = 3 $ , and $ x=2 $ , which fills the array with zeros. In total, Burenka will spend $ 2 $ seconds.

## 样例 #1

### 输入

```
7
4
5 5 5 5
3
1 3 2
2
0 0
3
2 5 7
6
1 2 3 3 2 1
10
27 27 34 32 2 31 23 56 52 4
5
1822 1799 57 23 55```

### 输出

```
2
2
0
2
4
7
4```

# AI分析结果



```markdown
# 题目翻译

## 题目描述

这是该问题的简单版本。与困难版本的区别仅在于对 $a_i$ 和 $n$ 的限制。只有两个版本的问题都被解决时，才能进行 hack。

Burenka 是 Buryatia 的王储，即将成为该国的第 $n$ 任女王。Buryatia 有一个古老的传统——在加冕前，统治者必须向居民展示自己的力量。为了确定第 $n$ 任统治者的力量，居民会给她一个长度为 $n$ 的数组 $a$，她必须在最短时间内将数组所有元素变为零。统治者可以进行以下两步操作任意次：

1. 选择两个索引 $l$ 和 $r$（$1 \le l \le r \le n$）和一个非负整数 $x$；
2. 对所有 $l \leq i \leq r$ 执行 $a_i := a_i \oplus x$（$\oplus$ 表示按位异或操作），操作耗时 $\left\lceil \frac{r-l+1}{2} \right\rceil$ 秒（$\lceil y \rceil$ 表示向上取整）。

请帮助 Burenka 计算所需的最短时间。

## 样例 #1

输入与输出见原题内容。

---

## 唯一算法分类
无算法分类

---

## 综合分析与结论

### 核心思路
所有题解均基于以下观察：
1. **操作时间特性**：长为 $k$ 的区间操作时间等效于 $\lceil k/2 \rceil$，等价于每次操作可处理 1 或 2 个元素，时间均为 1 秒。
2. **异或前缀和性质**：若区间 $[l+1, r]$ 的异或和为 0，则前缀异或和满足 $sum_r = sum_l$。此时该区间可用 $r-l-1$ 次操作处理，节省 1 秒。

### 算法要点
- **贪心策略**：初始答案为 $n$，每次发现极短的异或和为 0 的区间，答案减 1。
- **哈希表记录前缀和**：用 `map` 或 `set` 记录已出现的前缀异或和，若当前前缀和已存在，则触发区间划分，清空哈希表重新开始。

### 动态规划分析（次要思路）
- **状态定义**：$dp[i]$ 表示处理前 $i$ 个元素的最小时间。
- **转移方程**：
  - 单独处理 $a_i$：$dp[i] = dp[i-1] + 1$
  - 合并处理区间 $[l+1, i]$：$dp[i] = \min(dp[i], dp[l] + (i-l-1))$，其中 $sum_i = sum_l$
- **实现难点**：需用哈希表快速查找 $l$ 的位置，空间复杂度较高。

### 可视化设计思路
- **像素风格 DP 矩阵**：用 Canvas 绘制网格，每个格子表示 $dp[i]$，颜色深浅表示时间长短。
- **动画效果**：
  - 红色高亮当前处理的元素 $a_i$。
  - 当检测到 $sum_i$ 重复时，绿色闪烁区间 $[l+1, i]$，播放“成功”音效。
  - 左侧面板显示哈希表内容，实时更新前缀和状态。
- **音效设计**：
  - 默认操作：8-bit 点击声。
  - 区间合并：上扬音调。
  - 清空哈希表：短促提示音。

---

## 题解清单（≥4星）

### 1. Zeardoe（★★★★☆）
- **亮点**：代码简洁，贪心思路清晰，利用 `map` 记录前缀和。
- **代码片段**：
  ```cpp
  map<int, int> mp;
  mp[0] = 1;
  int tmp = 0;
  for (int i = 1; i <= n; i++) {
      int a; cin >> a; tmp ^= a;
      if (mp.count(tmp)) {
          ans--; mp.clear(); mp[0] = 1; tmp = 0;
      } else {
          mp[tmp] = 1;
      }
  }
  ```

### 2. happy_dengziyue（★★★★☆）
- **亮点**：动态规划实现完整，提供困难版解法。
- **状态转移**：结合前缀和与哈希表优化查找。

### 3. ricky_lin（★★★★☆）
- **亮点**：使用 `set` 替代 `map`，代码简洁高效。
- **代码片段**：
  ```cpp
  set<int> s;
  s.insert(0);
  for (int i = 1; i <= n; i++) {
      pre[i] = pre[i-1] ^ a[i];
      if (s.count(pre[i])) {
          ans--; s.clear(); pre[i] = 0;
      }
      s.insert(pre[i]);
  }
  ```

---

## 最优思路提炼
**关键技巧**：利用前缀异或和的重复出现划分极短异或零区间，每次减少操作次数。  
**实现要点**：
1. 初始化哈希表记录 `sum=0` 的位置。
2. 遍历时更新前缀和，若哈希表中存在当前值，则触发区间划分，清空哈希表。
3. 初始答案为 $n$，每划分一次减 1。

---

## 同类题目推荐
1. [CF665E] Beautiful Subarrays（前缀异或和+字典树）
2. [洛谷 P3131] 子串查找（前缀和哈希）
3. [洛谷 P3405] 平衡的队列（前缀和与模运算）

---

## 个人心得摘录
> “清空哈希表是关键，因为后续区间不能与已处理的区间重叠。”（Zeardoe）  
> “单独处理 $a_i=0$ 的情况可以避免无效操作。”（happy_dengziyue）

---

## 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while (t--) {
        int n, ans, sum = 0; 
        cin >> n; ans = n;
        unordered_map<int, bool> mp{{0, true}};
        for (int i = 0; i < n; i++) {
            int a; cin >> a; sum ^= a;
            if (mp.count(sum)) {
                ans--; mp.clear(); sum = 0;
                mp[0] = true;
            } else mp[sum] = true;
        }
        cout << ans << endl;
    }
}
```

---

## 可视化代码片段（JS+Canvas）
```javascript
// 绘制前缀和哈希表
function drawHashTable(ctx, map) {
    ctx.clearRect(0, 0, 300, 100);
    let idx = 0;
    map.forEach((val, key) => {
        ctx.fillText(`${key} → ${val}`, 10, 20 + idx * 20);
        idx++;
    });
}

// 动画主循环
function animate() {
    if (current >= n) return;
    sum ^= a[current];
    if (map.has(sum)) {
        playSound('success'); // 触发成功音效
        ctx.fillStyle = '#00ff00'; // 绿色高亮区间
        ctx.fillRect(l * 30, 50, (current - l) * 30, 30);
        ans--;
        map.clear();
        sum = 0;
    }
    map.set(sum, current);
    current++;
    requestAnimationFrame(animate);
}
```

---
处理用时：98.65秒