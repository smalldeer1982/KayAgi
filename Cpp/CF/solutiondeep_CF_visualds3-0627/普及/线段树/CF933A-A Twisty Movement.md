# 题目信息

# A Twisty Movement

## 题目描述

A dragon symbolizes wisdom, power and wealth. On Lunar New Year's Day, people model a dragon with bamboo strips and clothes, raise them with rods, and hold the rods high and low to resemble a flying dragon.

A performer holding the rod low is represented by a $ 1 $ , while one holding it high is represented by a $ 2 $ . Thus, the line of performers can be represented by a sequence $ a_{1},a_{2},...,a_{n} $ .

Little Tommy is among them. He would like to choose an interval $ [l,r] $ ( $ 1<=l<=r<=n $ ), then reverse $ a_{l},a_{l+1},...,a_{r} $ so that the length of the longest non-decreasing subsequence of the new sequence is maximum.

A non-decreasing subsequence is a sequence of indices $ p_{1},p_{2},...,p_{k} $ , such that $ p_{1}<p_{2}<...<p_{k} $ and $ a_{p1}<=a_{p2}<=...<=a_{pk} $ . The length of the subsequence is $ k $ .

## 说明/提示

In the first example, after reversing $ [2,3] $ , the array will become $ [1,1,2,2] $ , where the length of the longest non-decreasing subsequence is $ 4 $ .

In the second example, after reversing $ [3,7] $ , the array will become $ [1,1,1,1,2,2,2,2,2,1] $ , where the length of the longest non-decreasing subsequence is $ 9 $ .

## 样例 #1

### 输入

```
4
1 2 1 2
```

### 输出

```
4
```

## 样例 #2

### 输入

```
10
1 1 2 2 2 1 1 2 2 1
```

### 输出

```
9
```

# AI分析结果



# 算法分类  
**动态规划**

---

## 综合分析与结论  
### 核心思路  
所有题解均围绕「允许一次翻转的最长非降子序列」展开，核心观察点在于：  
1. 最终最优序列形态为 `[1...][2...][1...][2...]` 四段结构  
2. 翻转操作可隐含在动态规划状态转移中，无需显式计算翻转区间  

### 解决难点  
- **状态设计**：将翻转后的最优形态拆解为四个阶段，通过状态转移隐含翻转可能性  
- **高效计算**：通过 O(n) 时间复杂度的动态规划，避免枚举所有可能的翻转区间  

### 算法流程可视化设计  
1. **动画方案**：  
   - 横向展示序列元素，用四种颜色块表示当前处理的四个状态（1段/2段/翻转后的1段/翻转后的2段）  
   - 步进式更新状态值，高亮当前处理的元素及其影响的四个状态值  
   - 右侧同步显示四个状态的当前最大值，用箭头标注状态转移路径  

2. **复古像素风格**：  
   - 使用 8-bit 像素字体，状态值用 16x16 像素块表示  
   - 元素处理时播放「哔」音效，状态更新时播放「叮」音效  
   - 自动演示模式可展示算法如何逐步推导最终解  

---

## 题解清单（评分 ≥4星）  
### 1. 浅色调（5星）  
**亮点**：  
- 提出两种解法，线段树解法展示思维深度，DP 解法代码极简  
- 状态转移方程设计精准，空间压缩至 O(1)  
**核心代码**：  
```cpp
f[1] += (x==1);
f[2] = max(f[1], f[2] + (x==2));
f[3] = max(f[2], f[3] + (x==1));
f[4] = max(f[3], f[4] + (x==2));
```

### 2. 蒟蒻丁（4星）  
**亮点**：  
- 手绘式解释四段结构如何对应翻转操作  
- 强调「无需实际翻转」的思维突破点  
**心得摘录**：  
> “发现它可以分为4组 [111][2222][111][2222]，这样交换23区间就得到了答案”

### 3. _sh1kong_（4星）  
**亮点**：  
- 提供完整的状态转移方程推导过程  
- 代码实现最简洁（仅 15 行）  
**核心代码**：  
```cpp
f[1] += (d[i] == 1);
f[2] = max(f[1], f[2] + (d[i] == 2));
f[3] = max(f[2], f[3] + (d[i] == 1));
f[4] = max(f[3], f[4] + (d[i] == 2));
```

---

## 最优思路提炼  
### 关键技巧  
1. **四阶段状态设计**：  
   - `f[1]`: 当前处理纯1段  
   - `f[2]`: 处理完1段后接2段  
   - `f[3]`: 翻转后重新接1段  
   - `f[4]`: 翻转后接最终2段  

2. **滚动更新**：  
   通过复用一维数组，将空间复杂度从 O(n) 优化至 O(1)  

### 思维突破点  
- 将翻转操作转化为允许一次「1→2→1→2」的结构变化  
- 利用序列元素仅为1/2的特性，避免复杂的最长子序列计算  

---

## 同类型题推荐  
1. **LeetCode 376. 摆动序列**  
   （状态设计处理序列波动）  

2. **洛谷 P1091 合唱队形**  
   （双向动态规划处理序列形态）  

3. **Codeforces 1353E. K-periodic Garland**  
   （状态转移处理特殊序列结构）  

---

## 可视化代码示例（关键逻辑）  
```javascript
// 像素动画核心逻辑
function updateAnimation(step) {
  ctx.fillStyle = '#8BDBFB'; // 背景色
  ctx.fillRect(0, 0, canvas.width, canvas.height);
  
  // 绘制当前处理的元素
  ctx.fillStyle = '#FF6B6B';
  drawPixelBlock(step*32, 100, a[step]); 
  
  // 更新四个状态值
  states.forEach((s, i) => {
    ctx.fillStyle = stateColors[i];
    drawPixelBlock(200 + i*64, 50, s.value);
  });
  
  // 触发音效
  if(step > 0) playSound('blip');
}
```

---

## 知识迁移建议  
1. **状态压缩**：当问题允许有限次操作时，可通过状态数表示操作阶段  
2. **序列分段处理**：将复杂操作转化为多段标准结构的组合  
3. **逆向思维**：通过分析最优解的形态反推状态转移方程

---
处理用时：76.35秒