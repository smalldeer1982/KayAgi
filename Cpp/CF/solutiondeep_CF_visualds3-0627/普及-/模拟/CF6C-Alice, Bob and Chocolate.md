# 题目信息

# Alice, Bob and Chocolate

## 题目描述

Alice and Bob like games. And now they are ready to start a new game. They have placed $ n $ chocolate bars in a line. Alice starts to eat chocolate bars one by one from left to right, and Bob — from right to left. For each chocololate bar the time, needed for the player to consume it, is known (Alice and Bob eat them with equal speed). When the player consumes a chocolate bar, he immediately starts with another. It is not allowed to eat two chocolate bars at the same time, to leave the bar unfinished and to make pauses. If both players start to eat the same bar simultaneously, Bob leaves it to Alice as a true gentleman.

How many bars each of the players will consume?

## 样例 #1

### 输入

```
5
2 9 8 2 7
```

### 输出

```
2 3
```

# AI分析结果



## 算法分类
**双指针模拟**

---

## 题解思路与核心难点
### 核心思路
通过双指针模拟两人吃巧克力的过程：  
1. **双指针初始化**：`p1`从左开始，`p2`从右开始  
2. **时间累加比较**：每次选择累加时间较小的一方推进指针  
3. **相遇终止条件**：当 `p1 > p2` 时终止  
4. **关键难点**：正确处理两人同时选择同一块巧克力的逻辑（时间相等时，Bob让给Alice）

### 解决难点
- **指针推进规则**：当 `sumA <= sumB` 时，Alice推进（包含两人时间相等的情况）  
- **终止条件**：循环条件 `p1 <= p2` 确保所有巧克力被处理  
- **结果计算**：最终 `p1-1` 表示Alice吃的块数，`n-p2` 表示Bob吃的块数  

---

## 题解评分（≥4星）

### 1. Loner_Knowledge（5星）
- **亮点**：代码最简洁，逻辑直击核心，时间复杂度 O(n)  
- **关键代码**：
```cpp
for(int sum1=0,sum2=0; p1<=p2; ) {
    if(sum1 <= sum2) sum1 += num[p1++];
    else sum2 += num[p2--];
}
```

### 2. 封禁用户（4星）
- **亮点**：加入输入优化，变量命名更清晰  
- **关键代码**：
```cpp
while(q <= h) {
    if(a <= b) a += c[q++];
    else b += c[h--];
}
```

### 3. 胡金梁（4星）
- **亮点**：代码与最优解完全一致，变量命名更直观  
- **关键代码**：
```cpp
for(int sA=0, sB=0; pA <= pB; ) {
    if(sA <= sB) sA += num[pA++];
    else sB += num[pB--];
}
```

---

## 最优思路提炼
### 核心技巧
- **双指针贪心推进**：通过比较累计时间决定推进方向  
- **O(1)空间复杂度**：仅用两个变量存储累计时间  
- **边界处理艺术**：`p1-1` 和 `n-p2` 的精妙计算结果  

### 同类型题套路
- **双指针模拟**：如 [11. 盛最多水的容器](https://leetcode.cn/problems/container-with-most-water/)  
- **时间/资源分配问题**：如 [CF4C. Registration System](https://codeforces.com/problemset/problem/4/C)  

---

## 推荐相似题目
1. [CF4C. Registration System](https://codeforces.com/problemset/problem/4/C)（哈希表模拟）  
2. [洛谷P1106 删数问题](https://www.luogu.com.cn/problem/P1106)（贪心+栈）  
3. [LeetCode 42. 接雨水](https://leetcode.cn/problems/trapping-rain-water/)（双指针进阶）  

---

## 可视化算法设计
### 动画方案
1. **像素风格界面**：  
   - 使用 16 色调色板，巧克力块用不同颜色表示时间  
   - Alice和Bob用不同颜色箭头（红/蓝）标记当前位置  

2. **关键动画步骤**：  
   - **步骤1**：高亮当前处理的巧克力块  
   - **步骤2**：显示 `sumA` 和 `sumB` 的数值变化（顶部状态栏）  
   - **步骤3**：指针移动时有 "像素抖动" 效果  

3. **交互功能**：  
   - **速度调节**：滑块控制动画速度（1x~10x）  
   - **单步执行**：空格键触发下一步操作  
   - **音效设计**：  
     - 指针移动时播放 8-bit "哔" 声  
     - 结果确定时播放经典 FC 过关音效  

### 核心逻辑演示代码（伪代码）
```javascript
// 初始化 Canvas
const ctx = initCanvas(); 
let p1 = 0, p2 = n-1, sumA = 0, sumB = 0;

function animateStep() {
    // 绘制当前状态
    drawChocolates();
    drawPointers();
    
    // 决策逻辑
    if (sumA <= sumB) {
        sumA += time[p1];
        p1++;
    } else {
        sumB += time[p2];
        p2--;
    }
    
    // 触发音效
    playSound('move');
}
```

---

## 个人心得摘录
> "当两人同时开始吃同一块巧克力时，Alice会让给Bob，这个条件可以通过 `sum1 <= sum2` 巧妙处理，不需要额外判断" —— Loner_Knowledge  
> "`p1-1` 的计算方式最初让我调试了很久，后来才明白循环终止时p1的位置是第一个未被吃的巧克力" —— 胡金梁  

---

## 最终代码实现
```cpp
#include <cstdio>

int num[100002];
int main() {
    int n, p1 = 1, p2;
    scanf("%d", &n);
    p2 = n;
    for(int i=1; i<=n; ++i) scanf("%d", num+i);
    
    for(int sum1=0, sum2=0; p1 <= p2; ) {
        if(sum1 <= sum2) sum1 += num[p1++];
        else sum2 += num[p2--];
    }
    
    printf("%d %d", p1-1, n - p2);
    return 0;
}
```

---
处理用时：86.91秒