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



### 综合分析与结论

**题目核心思路**：通过贪心策略寻找最多的不重叠区间，每个区间的异或和为0，从而将初始代价（n）减去区间数得到最小总代价。

**解决难点**：如何高效检测这些区间。利用前缀异或和的性质：若两个位置的前缀异或和相等，则中间区间的异或和为0。使用哈希表（如`map`或`set`）记录前缀异或和的出现位置，每次发现重复值时，减少代价并重置状态。

**贪心选择策略**：每次尽可能找到最左边的有效区间，确保不重叠，最大化减少操作次数。关键验证点在于正确维护前缀异或和与哈希表。

**可视化设计思路**：
- **动画方案**：遍历数组时，实时显示当前前缀异或和与哈希表状态。发现重复值时，高亮对应区间，减少总代价，并清空哈希表。
- **颜色标记**：当前元素用红色标记，哈希表中存在的值用绿色高亮。成功匹配时，区间变为蓝色。
- **步进控制**：允许用户单步执行，观察每一步的前缀和变化和哈希表更新。
- **复古像素风格**：用8位像素网格展示数组元素，每次操作时播放经典音效，增强交互体验。

---

### 题解清单（≥4星）

1. **Zeardoe的题解（⭐⭐⭐⭐⭐）**
   - **关键亮点**：利用前缀异或和与哈希表，代码简洁高效，时间复杂度O(n)。
   - **代码可读性**：结构清晰，逻辑简明，适合快速理解核心贪心策略。

2. **FireRain的题解（⭐⭐⭐⭐）**
   - **关键亮点**：与Zeardoe思路一致，使用`set`优化查找效率，代码同样简洁。
   - **实践操作性**：直接通过遍历和集合操作实现，适合快速编写。

3. **happy_dengziyue的题解（⭐⭐⭐⭐）**
   - **关键亮点**：动态规划解法，适用于更复杂的情况（如hard版本），展示多角度思考。
   - **优化程度**：通过状态转移方程实现灵活更新，适合深入学习。

---

### 最优思路与代码实现

**核心贪心逻辑**：遍历数组，维护前缀异或和，用哈希表记录出现过的值。每次发现重复值时，减少代价，清空哈希表并重置前缀和。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main() {
    int t; cin >> t;
    while(t--) {
        int n, ans, tmp = 0; cin >> n;
        ans = n;
        map<int, int> mp{{0, 1}}; // 初始放入0
        for(int i = 0; i < n; ++i) {
            int a; cin >> a; tmp ^= a;
            if(mp.count(tmp)) {
                ans--;
                mp.clear();     // 清空哈希表
                tmp = 0;        // 重置前缀和
                mp[0] = 1;      // 重新初始化
            } else mp[tmp] = 1;
        }
        cout << ans << endl;
    }
    return 0;
}
```

---

### 同类型题目与套路

**常见套路**：利用前缀和/异或和的哈希表优化，寻找满足条件的子区间。常用于最小操作次数、最长子数组等问题。

**推荐题目**：
1. **洛谷P3131**：寻找和为7的倍数的子数组。
2. **洛谷P3406**：异或前缀和的应用。
3. **Codeforces 1547E**：贪心策略与区间覆盖结合。

---

### 个人心得摘录

- **调试经验**：初始时未将0加入哈希表，导致首个子区间无法检测。需注意前缀和的初始状态。
- **顿悟点**：每次重置哈希表是为了确保后续区间不重叠，最大化减少操作次数。

---

### 可视化与复古游戏化设计

**像素动画方案**：
1. **Canvas绘制**：数组元素显示为像素块，前缀和实时更新在顶部。
2. **音效设计**：
   - **匹配成功**：8-bit胜利音效。
   - **元素遍历**：按键声效。
3. **自动演示**：AI按步遍历，匹配时自动高亮区间并播放音效。
4. **关卡积分**：每匹配一个区间得10分，连击加分，增强游戏感。

**交互示例**：
```javascript
// 伪代码：演示贪心过程
function visualize(arr) {
    let xor = 0, map = new Set([0]), score = 0;
    for (let i = 0; i < arr.length; i++) {
        xor ^= arr[i];
        if (map.has(xor)) {
            score++;
            drawHighlight(i - map.get(xor), i); // 高亮区间
            playSound('success');
            map.clear();
            xor = 0;
        }
        map.add(xor);
    }
    return arr.length - score;
}
```

---

**总结**：本题通过巧妙的贪心策略与哈希表优化，将问题转化为寻找不重叠的异或零区间，极大降低了时间复杂度。掌握前缀和与哈希表的结合使用是解决此类问题的关键。

---
处理用时：89.78秒