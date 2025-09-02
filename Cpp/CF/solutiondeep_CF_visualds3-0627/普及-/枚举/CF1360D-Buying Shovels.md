# 题目信息

# Buying Shovels

## 题目描述

Polycarp wants to buy exactly $ n $ shovels. The shop sells packages with shovels. The store has $ k $ types of packages: the package of the $ i $ -th type consists of exactly $ i $ shovels ( $ 1 \le i \le k $ ). The store has an infinite number of packages of each type.

Polycarp wants to choose one type of packages and then buy several (one or more) packages of this type. What is the smallest number of packages Polycarp will have to buy to get exactly $ n $ shovels?

For example, if $ n=8 $ and $ k=7 $ , then Polycarp will buy $ 2 $ packages of $ 4 $ shovels.

Help Polycarp find the minimum number of packages that he needs to buy, given that he:

- will buy exactly $ n $ shovels in total;
- the sizes of all packages he will buy are all the same and the number of shovels in each package is an integer from $ 1 $ to $ k $ , inclusive.

## 说明/提示

The answer to the first test case was explained in the statement.

In the second test case, there is only one way to buy $ 8 $ shovels — $ 8 $ packages of one shovel.

In the third test case, you need to buy a $ 1 $ package of $ 6 $ shovels.

## 样例 #1

### 输入

```
5
8 7
8 1
6 10
999999733 999999732
999999733 999999733```

### 输出

```
2
8
1
999999733
1```

# AI分析结果



## 算法分类
数学问题（因数分解）

---

## 题解思路与算法要点

### 核心思路
寻找 n 的最大因数且该因数 ≤k，所需最少包裹次数即为 n/该因数。所有题解均基于以下步骤：
1. **枚举因数对**：遍历 1 到 sqrt(n)，检查每个 i 是否为 n 的因数
2. **双因子处理**：若 i 是因数，则另一因数为 n/i，两者都要判断是否 ≤k
3. **维护最小值**：记录满足条件的因子对应的包裹次数（n/i 或 i）

### 解决难点
- **高效性**：O(√n) 时间遍历，避免 O(n) 超时
- **成对处理**：同时处理 i 和 n/i 两个因子，确保不漏解
- **边界处理**：正确处理 i*i == n 的特殊情况

---

## 题解评分（≥4星）

1. **丧黑福造（★★★★★）**
   - 亮点：代码最简，直接在枚举过程中维护最小值，无额外存储
   - 关键代码：双 if 判断因子对，实时更新 ans

2. **jasonshen_（★★★★☆）**
   - 亮点：详细推导数学原理，代码附注释说明边界条件
   - 关键代码：for 循环中同时处理 i 和 n/i 的合法性

3. **togeth1（★★★★☆）**
   - 亮点：使用 INT_MAX 初始化，突出算法实践性
   - 关键代码：minn = min(minn, ...) 的紧凑写法

---

## 最优思路提炼

**关键技巧**：
1. **因数对枚举**：只遍历到 sqrt(n)，处理 i 和 n/i 两个因子
2. **实时更新**：在枚举过程中直接维护最小值，避免存储所有因子
3. **双条件判断**：同时检查 i ≤k 和 n/i ≤k 的情况

**代码片段**：
```cpp
int ans = n; // 初始化为最大可能值
for(int i=1; i*i<=n; ++i) {
    if(n%i == 0) {
        if(i <= k) ans = min(ans, n/i);
        if(n/i <= k) ans = min(ans, i);
    }
}
```

---

## 同类题型推荐
1. **P1075 质因数分解**（基础因数分解）
2. **CF1475A Odd Divisor**（奇因数判断）
3. **AT_abc280_d Factorial Divisibility**（因数分解进阶）

---

## 可视化方案设计

### 核心动画逻辑
1. **像素网格展示**：
   - 用 16x16 像素块表示当前检查的因子 i 和对应的 n/i
   - 红色块表示超过 k 的非法因子，绿色表示合法

2. **动态标记**：
   - 当前检查的 i 用闪烁黄框标记
   - 合法因子对 (i, n/i) 用绿色连接线展示

3. **音效反馈**：
   - 发现新合法因子时播放 "coin" 音效
   - 更新最小值时播放 "power-up" 音效

### 复古风格实现
```javascript
// 伪代码示例
function drawStep(i) {
    ctx.fillStyle = '#8B8B83'; // 灰色背景
    ctx.fillRect(0, 0, 256, 256);
    
    // 绘制当前检查的i（黄色边框）
    drawBox(i*16, 120, 16, 16, '#FFFF00'); 
    
    // 绘制因子对
    if(n%i == 0) {
        drawBox(40, 80, 32, 32, i<=k ? '#00FF00' : '#FF0000'); // i
        drawBox(180, 80, 32, 32, (n/i)<=k ? '#00FF00' : '#FF0000'); // n/i
    }
    
    // 当前最优解显示在右下角
    drawText(`MIN: ${currentMin}`, 200, 200, '#FFFFFF');
}
```

---

## 个人心得摘录
- **《丧黑福造》**：强调"因数是成对出现的，必须同时处理两个因子"
- **《togeth1》**：调试中发现忘记处理 n/i 的情况导致 WA，提醒注意双因子检查
- **《Pink_Cut_Tree》**：初始 ans 应设为 n（对应买 1 个包裹的情况），避免特殊值遗漏

---

## 算法演示说明
**交互功能**：
- 速度调节滑块：控制枚举速度（50ms~2000ms/步）
- 单步执行按钮：手动控制遍历过程
- 音效开关：启用/禁用提示音

**动画效果**：
![因数分解动画示意图](https://via.placeholder.com/600x400/000000/FFFFFF?text=Factor+Enumeration+Visualization)
*示意图：左侧显示当前检查的i，右侧显示因子对和最小值变化*

---
处理用时：67.65秒