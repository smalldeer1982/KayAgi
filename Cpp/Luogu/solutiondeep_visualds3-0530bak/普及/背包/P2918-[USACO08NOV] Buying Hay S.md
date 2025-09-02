# 题目信息

# [USACO08NOV] Buying Hay S

## 题目描述

Farmer John is running out of supplies and needs to purchase H (1 <= H <= 50,000) pounds of hay for his cows.

He knows N (1 <= N <= 100) hay suppliers conveniently numbered 1..N. Supplier i sells packages that contain P\_i (1 <= P\_i <= 5,000) pounds of hay at a cost of C\_i (1 <= C\_i <= 5,000) dollars. Each supplier has an unlimited number of packages available, and the packages must be bought whole.

Help FJ by finding the minimum cost necessary to purchase at least H pounds of hay.

约翰的干草库存已经告罄，他打算为奶牛们采购 $H(1 \leq H \leq 50000)$ 磅干草。

他知道 $N(1 \leq N\leq 100)$ 个干草公司，现在用 $1$ 到 $N$ 给它们编号。第 $i$ 公司卖的干草包重量为 $P_i (1 \leq P_i \leq 5,000)$ 磅，需要的开销为 $C_i (1 \leq C_i \leq 5,000)$ 美元。每个干草公司的货源都十分充足， 可以卖出无限多的干草包。

帮助约翰找到最小的开销来满足需要，即采购到至少 $H$ 磅干草。

## 说明/提示

FJ can buy three packages from the second supplier for a total cost of 9.


## 样例 #1

### 输入

```
2 15 
3 2 
5 3 
```

### 输出

```
9 
```

# AI分析结果



### 唯一算法分类
完全背包

---

### 综合分析与结论
**核心思路**：将问题转化为完全背包模型，处理“至少H磅”的特殊条件。状态定义为`dp[j]`表示购买至少j磅干草的最小成本，通过扩展容量至`H+5000`（最大单包重量）确保最优解不被遗漏。

**解决难点**：
1. 需要处理“至少”而非“恰好”的条件，通过最终在`[H, H+MaxP]`区间取最小值解决
2. 状态转移时需覆盖所有可能的重量组合，采用完全背包正向更新的方式

**可视化设计**：
- **动画方案**：绘制动态表格展示`dp[j]`更新过程，用绿色高亮当前处理的物品和更新的单元格
- **颜色标记**：红色标记最终解的候选区间`H~H+5000`，蓝色表示当前最小值的传播路径
- **音效设计**：更新`dp[j]`时播放电子音效，找到最终解时播放8-bit胜利音效
- **复古风格**：采用16色NES调色板，表格用像素边框，数字使用复古点阵字体

---

### 题解评分（≥4星）
1. **CCF_zkskyer（★★★★★）**
   - 亮点：清晰解释容量扩展原理，代码可读性极强，包含关键注释
   - 代码：通过`h+Max`扩展容量，最终遍历候选区间取最小值

2. **EarthGiao（★★★★☆）**
   - 亮点：详细分析错误原因，给出数学证明`H+5000`的合理性
   - 代码：预处理`dp[0]=0`，使用`h+5000`作为上限

3. **Sunbread（★★★★☆）**
   - 亮点：代码最简练，包含详细问题转化思路说明
   - 代码：在线读取数据，直接操作`dp[j]`的更新逻辑

---

### 最优思路提炼
**关键技巧**：
1. **容量扩展**：背包上限设为`H+5000`，覆盖可能更优的超量购买方案
2. **逆向状态定义**：`dp[j]`表示获得至少j磅的最小成本，允许状态转移覆盖更大重量
3. **初始化优化**：仅需`dp[0]=0`，其他位置初始化为极大值，确保正确性

**代码核心逻辑**：
```cpp
memset(dp, 0x3f, sizeof(dp)); // 初始化为极大值
dp[0] = 0; // 关键初始化

for (int i = 1; i <= n; i++) {
    for (int j = p[i]; j <= h + 5000; j++) { // 完全背包正向更新
        dp[j] = min(dp[j], dp[j - p[i]] + c[i]);
    }
}

int ans = *min_element(dp + h, dp + h + 5001); // 候选区间取最小
```

---

### 同类题目推荐
1. [P1616 疯狂的采药](https://www.luogu.com.cn/problem/P1616)  
   （完全背包模板题，求最大价值）
2. [P1510 精卫填海](https://www.luogu.com.cn/problem/P1510)  
   （类似“至少”条件处理，需转换背包定义）
3. [P1853 投资的最大效益](https://www.luogu.com.cn/problem/P1853)  
   （多重背包变种，需处理利息再投资）

---

### 个人心得摘录
> "本蒟蒻被坑了！！！其实要扩展到h+5000，否则会WA" —— CCF_zskyer  
> **总结**：忽视超量购买的优化空间是常见错误点，需通过数学分析确定扩展范围

> "把重量当价值，花费当限制条件，结果最后一个循环直接找第一个满足条件的" —— Egg_eating_master  
> **启示**：逆向定义状态可能简化问题，但需注意时间复杂度

---

### 可视化算法演示（伪代码）
```javascript
// 初始化画布与音效
const canvas = initCanvas();
const beepSound = loadSound('8bit-beep.wav');
const successSound = loadSound('8bit-success.wav');

// 动态绘制背包表格
function animateDP() {
  for (let i = 0; i < items.length; i++) {
    for (let j = items[i].p; j <= H + 5000; j++) {
      highlightCell(j, 'blue'); // 高亮当前更新位置
      updateDP(j, Math.min(dp[j], dp[j - items[i].p] + items[i].c));
      playSound(beepSound);
      wait(100); // 控制动画速度
    }
  }
  
  // 高亮候选区间并找到最小值
  highlightRange(H, H + 5000, 'red');
  const ans = findMinInRange(H, H + 5000);
  playSound(successSound);
}
```

**复古效果实现**：
- 使用`16x16`像素格子绘制DP表格
- 数值显示采用`NES`风格的黄色字体
- 背景音乐循环播放《超级玛丽》地下关BGM的8-bit改编版

---
处理用时：62.36秒