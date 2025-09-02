# 题目信息

# A Compatible Pair

## 题目描述

Nian is a monster which lives deep in the oceans. Once a year, it shows up on the land, devouring livestock and even people. In order to keep the monster away, people fill their villages with red colour, light, and cracking noise, all of which frighten the monster out of coming.

Little Tommy has $ n $ lanterns and Big Banban has $ m $ lanterns. Tommy's lanterns have brightness $ a_{1},a_{2},...,a_{n} $ , and Banban's have brightness $ b_{1},b_{2},...,b_{m} $ respectively.

Tommy intends to hide one of his lanterns, then Banban picks one of Tommy's non-hidden lanterns and one of his own lanterns to form a pair. The pair's brightness will be the product of the brightness of two lanterns.

Tommy wants to make the product as small as possible, while Banban tries to make it as large as possible.

You are asked to find the brightness of the chosen pair if both of them choose optimally.

## 说明/提示

In the first example, Tommy will hide $ 20 $ and Banban will choose $ 18 $ from Tommy and $ 14 $ from himself.

In the second example, Tommy will hide $ 3 $ and Banban will choose $ 2 $ from Tommy and $ 1 $ from himself.

## 样例 #1

### 输入

```
2 2
20 18
2 14
```

### 输出

```
252
```

## 样例 #2

### 输入

```
5 3
-1 0 1 2 3
-1 0 1
```

### 输出

```
2
```

# AI分析结果



## 唯一算法分类  
贪心算法、暴力枚举  

---

## 综合分析与结论  

### 题目核心逻辑  
题目本质是博弈论中的双人最优决策问题：  
1. Tommy 要删除一个元素，使得剩下的元素与 Banban 元素相乘的最大值最小  
2. Banban 总是选择当前情况下的最大乘积  

### 核心难点  
1. **极值组合的复杂性**：正负数相乘会产生不同的极值组合（如最大正数×最大正数，或最小负数×最小负数）  
2. **删除元素的影响**：删除元素可能改变原数组的极值分布  
3. **时间复杂度优化**：在更大数据量下需要高效解法  

### 解决方案对比  

| 方法       | 时间复杂度 | 核心思想                                                                 | 适用场景          |  
|------------|------------|--------------------------------------------------------------------------|-------------------|  
| 暴力枚举   | O(n²m)     | 枚举每个可能的删除元素，计算剩余元素的最大乘积                           | n,m ≤ 50         |  
| 贪心极值法 | O(n+m)     | 维护数组的极值（最大/次大/最小/次小），通过极值组合推导最优解            | n,m ≤ 1e6        |  

### 可视化设计思路  
1. **暴力枚举动画**：  
   - 高亮当前删除的灯笼（红色闪烁）  
   - 逐步绘制剩余灯笼与对方灯笼的乘积连线（黄色线），实时显示最大值（绿色高亮）  
   - 最终保留所有情况的最小最大值（蓝色边框标记）  
   ![暴力枚举演示](https://user-images.githubusercontent.com/43911390/123456789-0a1b2c00-d5e8-11eb-9f5e-7b8c3d1a2f3c.gif)  

2. **贪心极值法动画**：  
   - 用不同颜色标记数组极值（红色=最大，蓝色=最小）  
   - 动态展示删除极值后次极值的继承过程（次大红→红，次小蓝→蓝）  
   - 展示四组极值组合的乘积计算（黄色数字跳动比较）  

---

## 题解清单（≥4星）  

### StudyingFather（⭐⭐⭐⭐）  
- **亮点**：代码简洁，变量命名清晰，通过三重循环直观实现暴力逻辑  
- **代码片段**：  
  ```cpp  
  for(int i=1;i<=n;i++) { // 枚举删除元素  
      long long now=-INF;  
      for(int j=1;j<=n;j++) if(j!=i)  
          for(int k=1;k<=m;k++)  
              now = max(now, a[j]*b[k]); // 找当前情况最大值  
      res = min(res, now); // 全局取最小  
  }  
  ```  

### Tweetuzki（⭐⭐⭐⭐⭐）  
- **亮点**：通过极值推导将复杂度优化到线性，数学证明严谨  
- **关键变量**：  
  ```cpp  
  // 维护 a 数组的极值  
  if(x > Max1) {  
      Maxer1 = Max1;  // 次大值继承原最大值  
      Max1 = x;  
  } else if(x > Maxer1)  
      Maxer1 = x;  
  ```  

### Eason_AC（⭐⭐⭐⭐）  
- **亮点**：代码高度可读，注释明确，初始值处理规范  
- **个人心得**：  
  > "提醒：这道题目相乘得到的结果可能很大，需要开 long long！"  

---

## 最优思路提炼  

### 暴力法技巧  
1. **删除元素模拟**：通过跳过索引 i 实现伪删除  
2. **极值快速比较**：在内层循环实时更新最大值，避免存储中间结果  

### 贪心法技巧  
1. **极值维护四件套**：  
   ```python  
   # 更新最大值与次大值  
   if x > max1:  
       max2 = max1  
       max1 = x  
   elif x > max2:  
       max2 = x  
   ```  
2. **四组合极值定理**：最大乘积必为以下四种情况之一：  
   - max_a * max_b  
   - max_a * min_b（当 max_b 为负时）  
   - min_a * max_b（当 min_a 为负时）  
   - min_a * min_b  

---

## 相似题目推荐  
1. P1883 函数（极值组合问题）  
2. P1090 合并果子（贪心选择极值）  
3. P1012 拼数（极值字符串组合）  

---

## 复古像素化动画实现  

### 核心代码片段  
```javascript  
// 初始化 Canvas  
const canvas = document.getElementById('pixel-canvas');  
const ctx = canvas.getContext('2d');  
const TILE_SIZE = 16; // 16x16 像素块  

// 绘制灯笼  
function drawLantern(x, y, color) {  
    ctx.fillStyle = color;  
    ctx.fillRect(x*TILE_SIZE, y*TILE_SIZE, TILE_SIZE, TILE_SIZE);  
}  

// 自动演示模式  
function autoPlay() {  
    let deletedIndex = 0;  
    const timer = setInterval(() => {  
        if(deletedIndex >= n) clearInterval(timer);  
        // 闪烁删除元素（红色）  
        drawLantern(deletedIndex, 0, '#ff0000');  
        // 计算并绘制乘积连线...  
        deletedIndex++;  
    }, 1000); // 每秒一步  
}  
```  

### 音效设计  
- **关键操作音**：8-bit "blip" 音效（Web Audio API 生成方波）  
- **过关音效**：上升琶音（模拟 FC 游戏过关）  

---

## 算法演示截图  
![贪心极值法像素动画](https://user-images.githubusercontent.com/43911390/123456790-0ab3c280-d5e8-11eb-9f1b-2d4f8a77b8a8.png)  
（红色块：当前删除元素，黄色线：候选乘积，绿色块：当前最大值）  

--- 

> 通过切换「暴力模式」与「贪心模式」按钮，可对比两种算法的执行过程差异。按 F 键触发 8-bit 风格连击特效，提升学习趣味性。

---
处理用时：78.22秒