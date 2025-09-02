# 题目信息

# Cutlet

## 题目描述

Arkady wants to have a dinner. He has just returned from a shop where he has bought a semifinished cutlet. He only needs to fry it. The cutlet should be fried for $ 2n $ seconds, in particular, it should be fried for $ n $ seconds on one side and $ n $ seconds on the other side. Arkady has already got a frying pan and turn on fire, but understood that maybe he won't be able to flip the cutlet exactly after $ n $ seconds after the beginning of cooking.

Arkady is too busy with sorting sticker packs in his favorite messenger and can flip the cutlet only in some periods of time. Namely, there are $ k $ periods of time in which he can do it, the $ i $ -th of them is an interval of time from $ l_{i} $ seconds after he starts cooking till $ r_{i} $ seconds, inclusive. Arkady decided that it's not required to flip the cutlet exactly in the middle of cooking, instead, he will flip it several times in such a way that the cutlet will be fried exactly $ n $ seconds on one side and $ n $ seconds on the other side in total.

Help Arkady and find out if it's possible for him to cook the cutlet, if he is able to flip the cutlet only in given periods of time; and if yes, find the minimum number of flips he needs to cook the cutlet.

## 说明/提示

In the first example Arkady should flip the cutlet in time moment $ 3 $ seconds after he starts cooking and in time moment $ 13 $ seconds after he starts cooking.

In the second example, Arkady can flip the cutlet at $ 10 $ seconds after he starts cooking.

## 样例 #1

### 输入

```
10 2
3 5
11 13
```

### 输出

```
Full
2
```

## 样例 #2

### 输入

```
10 3
3 5
9 10
11 13
```

### 输出

```
Full
1
```

## 样例 #3

### 输入

```
20 1
3 19
```

### 输出

```
Hungry
```

# AI分析结果



### 唯一算法分类
动态规划（单调队列优化）

---

### 题解思路、算法要点与解决难点
**核心思路**：  
1. **状态设计**：`dp[i][j]` 表示处理前 `i` 个区间后，当前未被煎的那面（背面）累计煎了 `j` 秒的最小翻转次数。  
2. **状态转移**：每个区间内最多翻转两次，分三种情况：  
   - **不翻转**：直接继承前一个区间的状态。  
   - **翻转一次**：枚举翻转后的煎制时间，通过单调队列维护转移窗口的最小值。  
   - **翻转两次**：类似翻转一次，但需正序处理时间窗口。  
3. **单调队列优化**：对翻转一次和两次的转移分别维护单调队列，将时间复杂度从 `O(n^2)` 优化至 `O(nk)`。

**解决难点**：  
1. **转移方程推导**：正确分拆翻转次数对应的煎制时间关系，需数学推导确保无遗漏。  
2. **窗口维护**：翻转一次需倒序枚举 `j`，翻转两次需正序枚举 `j`，队列的维护范围需精确计算。  

---

### 题解评分 (≥4星)
1. **Kelin (5星)**  
   - 思路清晰，代码简洁，滚动数组优化空间，单调队列实现高效。  
   - 关键亮点：明确分拆翻转次数，双单调队列处理两种转移。  
   - 代码可读性强，变量命名合理。  

2. **yc20170111 (4星)**  
   - 状态定义与转移分析详细，注释明确。  
   - 代码实现稍冗长，但逻辑清晰，适合理解算法流程。  

3. **hstt (4星)**  
   - 代码注释详细，分步解析翻转逻辑。  
   - 使用双端队列优化，实现与理论结合紧密。  

---

### 最优思路或技巧提炼
1. **滚动数组优化**：仅保留当前和前一区间的状态，节省空间。  
2. **单调队列窗口维护**：  
   - 翻转一次：倒序枚举 `j`，维护 `r_i-j` 的递减窗口。  
   - 翻转两次：正序枚举 `j`，维护 `j` 的递增窗口。  
3. **数学简化**：通过时间差推导前驱状态，避免暴力枚举。  

---

### 同类型题或类似算法套路
- **单调队列优化DP**：适用于状态转移中存在滑动窗口最值问题的场景。  
- **时间区间分段处理**：将连续时间拆分为可操作区间，分段处理。  

---

### 推荐题目
1. **P1886 滑动窗口**：单调队列基础应用。  
2. **P1725 琪露诺**：单调队列优化时间窗口跳跃。  
3. **P3957 跳房子**：结合二分答案与单调队列优化。  

---

### 个人心得摘录
- **Kelin**：在实现中需注意数组越界，初始状态需置为无穷大。  
- **hstt**：调试时可通过输出中间状态验证队列维护的正确性。  

---

### 可视化与算法演示
**核心逻辑动画方案**：  
1. **网格绘制**：以时间轴为横坐标，背面煎制时间为纵坐标，动态显示 `dp` 值更新。  
2. **颜色标记**：  
   - **红色**：当前处理的区间和翻转操作。  
   - **绿色**：单调队列中的最小值位置。  
3. **步进控制**：允许单步执行翻转操作，观察队列元素变化。  

**复古像素风格设计**：  
- **8位色块**：用不同颜色块表示 `dp` 值高低，低值为亮色，高值为暗色。  
- **音效触发**：翻转时播放“哔”声，找到最优解时播放胜利音效。  

---

### 核心代码实现
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5, INF = 0x3f3f3f3f;
int n, k, dp[2][N]; // 滚动数组

int main() {
    scanf("%d%d", &n, &k);
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0; // 初始状态：0秒时背面煎0次
    int cur = 0;
    while (k--) {
        int l, r;
        scanf("%d%d", &l, &r);
        int nxt = cur ^ 1;
        memcpy(dp[nxt], dp[cur], sizeof(dp[nxt])); // 不翻转的情况
        
        deque<int> q;
        // 翻转两次，正序维护窗口
        for (int j = 0; j <= min(n, r); j++) {
            while (!q.empty() && dp[cur][j] <= dp[cur][q.back()]) 
                q.pop_back();
            q.push_back(j);
            while (q.front() < j - (r - l)) 
                q.pop_front();
            dp[nxt][j] = min(dp[nxt][j], dp[cur][q.front()] + 2);
        }
        
        q.clear();
        // 翻转一次，倒序维护窗口
        for (int j = r; j >= 0; j--) {
            int val = r - j;
            while (!q.empty() && dp[cur][val] <= dp[cur][q.back()]) 
                q.pop_back();
            q.push_back(val);
            while (q.front() < l - j) 
                q.pop_front();
            dp[nxt][j] = min(dp[nxt][j], dp[cur][q.front()] + 1);
        }
        cur = nxt;
    }
    if (dp[cur][n] < INF) 
        printf("Full\n%d\n", dp[cur][n]);
    else 
        puts("Hungry");
    return 0;
}
```

**代码说明**：  
- **滚动数组**：`cur` 和 `nxt` 交替表示当前和下一个区间。  
- **单调队列**：分别处理翻转两次（正序）和翻转一次（倒序）的窗口最值。  

---

### 可视化代码片段（Canvas动画）
```javascript
// 伪代码：绘制dp状态网格
function drawGrid() {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (let j = 0; j <= n; j++) {
        const color = dp[current][j] < INF ? 
            `hsl(${120 - dp[current][j] * 10}, 100%, 50%)` : '#333';
        ctx.fillStyle = color;
        ctx.fillRect(j * cellSize, current * cellSize, cellSize, cellSize);
    }
    // 高亮当前翻转操作
    ctx.strokeStyle = '#ff0';
    ctx.strokeRect(flipPos.x * cellSize, flipPos.y * cellSize, cellSize, cellSize);
}
```

---

**总结**：通过动态规划与单调队列优化的结合，高效解决了时间窗口内的最值问题，代码实现简洁且高效，适合作为同类问题的模板参考。

---
处理用时：99.70秒