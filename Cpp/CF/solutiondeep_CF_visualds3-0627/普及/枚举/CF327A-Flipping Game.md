# 题目信息

# Flipping Game

## 题目描述

Iahub got bored, so he invented a game to be played on paper.

He writes $ n $ integers $ a_{1},a_{2},...,a_{n} $ . Each of those integers can be either 0 or 1. He's allowed to do exactly one move: he chooses two indices $ i $ and $ j $ ( $ 1<=i<=j<=n $ ) and flips all values $ a_{k} $ for which their positions are in range $ [i,j] $ (that is $ i<=k<=j $ ). Flip the value of $ x $ means to apply operation $ x=1 $ - $ x $ .

The goal of the game is that after exactly one move to obtain the maximum number of ones. Write a program to solve the little game of Iahub.

## 说明/提示

In the first case, flip the segment from 2 to 5 $ (i=2,j=5) $ . That flip changes the sequence, it becomes: \[1 1 1 0 1\]. So, it contains four ones. There is no way to make the whole sequence equal to \[1 1 1 1 1\].

In the second case, flipping only the second and the third element $ (i=2,j=3) $ will turn all numbers into 1.

## 样例 #1

### 输入

```
5
1 0 0 1 0
```

### 输出

```
4
```

## 样例 #2

### 输入

```
4
1 0 0 1
```

### 输出

```
4
```

# AI分析结果



# 算法分类  
**最大子段和（贪心算法）**  

---

## 综合分析与结论  
### 核心算法流程  
1. **问题转换**：将原问题转化为寻找一个区间，使得翻转该区间后新增的1数量最大。  
   - **贡献值模型**：将每个元素转换为贡献值，`0 → +1`（翻转后增加1个1），`1 → -1`（翻转后减少1个1）。  
   - **最大子段和**：寻找贡献值最大的子区间，其和即为翻转该区间后1的净增加量。  
2. **关键变量**：  
   - `cnt`：原数组中1的总数。  
   - `current_sum`：当前子段的贡献和，动态维护最大值。  
3. **时间复杂度**：仅需一次遍历，时间复杂度为 `O(n)`。  

### 可视化设计要点  
1. **动画方案**：  
   - **像素网格**：用8位像素风格展示数组元素，0为蓝色方块（+1），1为红色方块（-1）。  
   - **动态扫描**：高亮当前扫描的元素，并实时显示当前子段和的累积值。  
   - **最大子段标记**：用金色边框标记历史最大子段。  
2. **音效与交互**：  
   - **步进音效**：每次移动指针播放短促的“哔”声。  
   - **更新最大值**：当发现新的最大子段时播放上扬音效。  
   - **交互控制**：支持暂停/继续、调整扫描速度。  

---

## 题解清单（≥4星）  
### 1. 作者：若如初见（★★★★★）  
**关键亮点**：  
- **思维突破**：将问题转化为最大子段和，时间复杂度优化到 `O(n)`。  
- **代码简洁**：仅需一次遍历，无需预处理，代码行数少且可读性强。  
- **扩展性强**：附带加强版题目链接，验证算法普适性。  

### 2. 作者：小豆子范德萨（★★★★☆）  
**关键亮点**：  
- **DP模型**：使用动态规划求最大子段和，与贡献值模型一致。  
- **状态转移清晰**：`dp[i] = max(b[i], dp[i-1] + b[i])` 直观易懂。  

### 3. 作者：Lips（★★★★☆）  
**关键亮点**：  
- **前缀和优化**：通过前缀和将暴力枚举优化到 `O(n²)`，适合理解基础优化思路。  
- **函数模块化**：将区间和、翻转后贡献等操作封装为函数，逻辑清晰。  

---

## 最优思路/技巧提炼  
### 关键思路  
**贡献值转换**：将原始数组中的元素转换为对最终结果的贡献值（0→+1，1→-1），问题等价于寻找贡献值最大的子区间。  

### 实现代码（核心逻辑）  
```cpp
#include <cstdio>
int main() {
    int n, a, now = 0, ans = 0, cnt = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a);
        if (a) cnt++, now = (now > 0) ? now - 1 : 0;
        else now++;
        ans = (now > ans) ? now : ans;
    }
    printf("%d", cnt + ans);
}
```

---

## 同类型题推荐  
1. **最大子数组和**（LeetCode 53）  
2. **乘积最大子数组**（LeetCode 152）  
3. **环形子数组的最大和**（LeetCode 918）  

---

## 个人心得摘录  
> **若如初见**提到：“贡献值模型的灵感来源于股票买卖中的最大利润问题，将翻转操作的影响量化为数值变化，是此类问题的通用技巧。”  
> **小豆子范德萨**反思：“最初尝试暴力枚举时忽略了贡献值的累积特性，动态规划模型让代码更高效。”  

---

## 可视化代码片段（JS Canvas）  
```javascript
// 绘制贡献值网格（8位像素风格）
function drawGrid(arr, maxStart, maxEnd) {
    ctx.clearRect(0, 0, canvas.width, canvas.height);
    for (let i = 0; i < arr.length; i++) {
        ctx.fillStyle = arr[i] === 0 ? "#3498db" : "#e74c3c"; // 0: 蓝色，1: 红色
        if (i >= maxStart && i <= maxEnd) {
            ctx.strokeStyle = "#f1c40f"; // 最大子段：金色边框
            ctx.strokeRect(i * 30, 50, 28, 28);
        }
        ctx.fillRect(i * 30, 50, 28, 28);
    }
}
```

---
处理用时：63.99秒