# 题目信息

# Shifts and Sorting

## 题目描述

Let's define a cyclic shift of some string $ s $ as a transformation from $ s_1 s_2 \dots s_{n-1} s_{n} $ into $ s_{n} s_1 s_2 \dots s_{n-1} $ . In other words, you take one last character $ s_n $ and place it before the first character while moving all other characters to the right.

You are given a binary string $ s $ (a string consisting of only 0-s and/or 1-s).

In one operation, you can choose any substring $ s_l s_{l+1} \dots s_r $ ( $ 1 \le l < r \le |s| $ ) and cyclically shift it. The cost of such operation is equal to $ r - l + 1 $ (or the length of the chosen substring).

You can perform the given operation any number of times. What is the minimum total cost to make $ s $ sorted in non-descending order?

## 说明/提示

In the first test case, you can choose the whole string and perform a cyclic shift: 10 $ \rightarrow $ 01. The length of the substring is $ 2 $ , so the cost is $ 2 $ .

In the second test case, the string is already sorted, so you don't need to perform any operations.

In the third test case, one of the optimal strategies is the next:

1. choose substring $ [1, 3] $ : 11000 $ \rightarrow $ 01100;
2. choose substring $ [2, 4] $ : 01100 $ \rightarrow $ 00110;
3. choose substring $ [3, 5] $ : 00110 $ \rightarrow $ 00011.

 The total cost is $ 3 + 3 + 3 = 9 $ .

## 样例 #1

### 输入

```
5
10
0000
11000
101011
01101001```

### 输出

```
2
0
9
5
11```

# AI分析结果



---

## 唯一算法分类
**贪心**

---

## 综合分析与结论
### 核心思路与算法流程
**核心思路**：每次遇到 `0` 时，将其移动到所有已累积的 `1` 的前方，代价为当前 `1` 的数量 +1。  
**实现要点**：
1. 遍历字符串，维护 `cnt` 统计已遇到的 `1` 的数量。
2. 遇到 `0` 时，若 `cnt > 0`，累加代价 `ans += cnt + 1`。
3. 所有 `0` 处理完毕后，字符串变为 `000...111`。

**正确性证明**：  
每个 `0` 需要跨越所有前面的 `1` 才能到达正确位置。每次操作可将 `0` 移动一个位置，代价为子串长度（即 `1` 的数量 +1）。贪心策略保证每个 `0` 只处理一次，总代价最小。

---

## 题解清单 (≥4星)
1. **lihongqian__int128（★★★★★）**  
   - **亮点**：代码最简练，直接遍历统计 `1` 的数量，遇到 `0` 时累加代价。  
   - **关键变量**：`cnt` 统计 `1`，`ans` 累加代价。  
   - **代码可读性**：高，无冗余逻辑。

2. **cheng2010（★★★★）**  
   - **亮点**：逻辑与最优解一致，变量命名清晰。  
   - **附加处理**：用 `bz` 标记是否已遇到 `1`，优化边界判断。

3. **keep_shining（★★★★）**  
   - **亮点**：明确解释代价公式 `k+1` 的由来，代码注释清晰。  
   - **警示**：强调 `long long` 类型，避免溢出问题。

---

## 最优思路与代码实现
### 关键代码片段
```cpp
string s;
int cnt = 0, ans = 0;
for (char c : s) {
    if (c == '1') cnt++;
    else if (cnt > 0) ans += cnt + 1;
}
cout << ans << endl;
```

### 完整代码
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
signed main() {
    int t; cin >> t;
    while (t--) {
        string s; cin >> s;
        int cnt = 0, ans = 0;
        for (char c : s) {
            if (c == '1') cnt++;
            else if (cnt > 0) ans += cnt + 1;
        }
        cout << ans << '\n';
    }
    return 0;
}
```

---

## 同类型题与类似算法
### 相似题目
1. **P1106 删数问题**（贪心选择最小数字序列）  
2. **P2870 [USACO07DEC] Best Cow Line G**（贪心选择字典序最小）  
3. **P1563 [NOIP2016 提高组] 玩具谜题**（循环移位与状态管理）

---

## 可视化与算法演示设计
### 核心动画方案
1. **像素风格界面**：  
   - **颜色标记**：  
     - `0` 显示为蓝色方块，`1` 为红色方块。  
     - 当前遍历位置高亮为黄色边框。  
   - **动画流程**：  
     - 遍历字符串，遇到 `1` 时红色方块闪烁一次。  
     - 遇到 `0` 时，播放音效，蓝色方块向左移动至所有红色方块前方，显示代价公式 `cnt + 1`。  
   - **控制面板**：  
     - 步进控制：支持暂停、单步执行、调节速度。  
     - 显示实时代价累计值。

2. **音效设计**：  
   - **移动操作**：8-bit 短促“滴”声。  
   - **累加代价**：硬币收集音效。  
   - **完成排序**：经典 FC 过关音效。

3. **AI 自动演示**：  
   - 自动高亮当前字符，模拟人工决策过程。  
   - 单步间隔可调，适合教学演示。

---

## 个人心得摘录
- **调试关键**：需注意只有前面已有 `1` 时才累加代价，否则会错误计算前导 `0`。  
- **思维陷阱**：直观认为需要实际移动字符，但贪心策略只需统计 `1` 的数量。  
- **优化顿悟**：每个 `0` 的代价只与前面的 `1` 相关，与后续 `0` 无关。

---

## 复古游戏化演示（伪代码）
```javascript
// Canvas 初始化与像素绘制
const drawBlock = (char, x, isActive) => {
    ctx.fillStyle = char === '0' ? '#00F' : '#F00';
    ctx.fillRect(x * 20, 50, 18, 18);
    if (isActive) {
        ctx.strokeStyle = '#FF0';
        ctx.strokeRect(x * 20, 50, 18, 18);
    }
};

// 单步执行逻辑
function step() {
    if (currentChar === '0' && cnt > 0) {
        playSound('move'); // 触发音效
        ans += cnt + 1;
        updateScoreDisplay(ans);
    }
    drawAllBlocks();
}
```

---
处理用时：61.82秒