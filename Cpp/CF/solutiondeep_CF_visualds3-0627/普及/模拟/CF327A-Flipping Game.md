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



---

## **唯一算法分类**  
**最大子段和**  

---

## **综合分析与结论**  

### 核心思路  
1. **问题转化**：将翻转区间问题转化为寻找最大贡献区间  
   - 每个元素翻转后的收益：0 → +1，1 → -1  
   - 构造贡献数组，求其最大子段和  
   - 最终答案 = 原数组1的总数 + 最大子段和  

2. **解决难点**  
   - **暴力枚举**的 O(n³) 解法直观但效率低  
   - **前缀和优化**将计算降至 O(n²)，但需额外空间  
   - **动态规划**的 O(n) 解法巧妙转化问题，无需预处理  

3. **可视化设计**  
   - **动画流程**：  
     - 初始数组 → 生成贡献数组 → 动态计算最大子段和  
     - 高亮当前子段和的起点与终点  
   - **像素风格**：  
     - 元素用 8-bit 方块表示（绿色=+1，红色=-1）  
     - 最大子段和区间闪烁显示  
   - **音效触发**：  
     - 当前子段和更新时播放“哔”声  
     - 发现更大子段时播放“叮”声  

---

## **题解清单 (≥4星)**  

| 作者          | 评分 | 关键亮点                         |  
|---------------|------|----------------------------------|  
| 若如初见      | ★★★★★| 创新性转化问题为最大子段和，O(n) 最优解 |  
| 小豆子范德萨  | ★★★★☆| 清晰 DP 推导，代码简洁易懂        |  
| 封禁用户      | ★★★★ | 前缀和优化思路清晰，代码简短       |  

---

## **最优思路与代码实现**  

### **核心代码片段**  
```cpp
// 若如初见题解的核心逻辑  
int cnt = 0, now = 0, ans = 0;  
for (int i = 1; i <= n; i++) {  
    int a;  
    scanf("%d", &a);  
    if (a) {  
        cnt++;  
        now = max(0, now - 1);  // 维护当前子段和  
    } else {  
        now++;  
        ans = max(ans, now);    // 更新最大值  
    }  
}  
printf("%d", cnt + ans);  
```

### **算法解析**  
- **now** 维护当前连续子段的和  
- **ans** 记录历史最大子段和  
- **cnt** 记录原数组1的总数  
- 每次遇到0时增加贡献，遇到1时减少贡献  

---

## **同类型题目与算法套路**  

1. **通用解法**  
   - 将操作转化为收益问题，求最大连续子序列  
   - 适用于需要选择最优区间操作的场景  

2. **相似题目**  
   - [53. 最大子数组和](https://leetcode.com/problems/maximum-subarray/)  
   - [152. 乘积最大子数组](https://leetcode.com/problems/maximum-product-subarray/)  
   - [洛谷 P1115 最大子段和](https://www.luogu.com.cn/problem/P1115)  

---

## **可视化算法演示**  

### **动画方案**  
1. **初始化阶段**：  
   - 展示原数组为 0/1 方块（灰色/黄色）  
   - 下方显示对应的贡献值（绿色/红色数字）  

2. **动态计算阶段**：  
   - 从左到右扫描贡献值  
   - 当前子段和区域用蓝色边框标记  
   - 当 `now` 值变为负时，重置子段起点  

3. **音效与提示**：  
   - 每次更新 `ans` 时播放“金币收集”音效  
   - 最终答案用金色数字弹出  

### **复古像素风格**  
- **Canvas 实现**：  
  ```javascript  
  // 绘制贡献数组方块  
  function drawBlock(x, value) {  
    ctx.fillStyle = value > 0 ? "#00FF00" : "#FF0000";  
    ctx.fillRect(x * 32, 100, 30, 30);  
    ctx.fillText(value, x * 32 + 10, 120);  
  }  
  ```  

---

## **个人心得摘录**  

> "将翻转操作转化为贡献值的变化，是本题最关键的思维跳跃。一旦想到这一点，后续的代码实现就变得异常简单。" —— 若如初见  

> "调试时发现，当所有元素都是1时，必须翻转一个区间才会减少1的总数。此时最优策略是翻转最小的区间（如单个元素），但题目要求必须翻转一次，因此答案应为 `cnt - 1`。" —— 小豆子范德萨  

---

## **推荐练习题**  
1. 洛谷 P1115 最大子段和  
2. 洛谷 P2642 双子序列最大和  
3. 洛谷 P3396 哈希冲突（区间操作思维）

---
处理用时：61.11秒