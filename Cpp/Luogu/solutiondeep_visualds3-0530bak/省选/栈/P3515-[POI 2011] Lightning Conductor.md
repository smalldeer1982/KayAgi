# 题目信息

# [POI 2011] Lightning Conductor

## 题目描述

Progressive climate change has forced the Byteburg authorities to build a huge lightning conductor    that would protect all the buildings within the city.

These buildings form a row along a single street, and are numbered from ![](http://main.edu.pl/images/OI18/pio-en-tex.1.png) to ![](http://main.edu.pl/images/OI18/pio-en-tex.2.png).

The heights of the buildings and the lightning conductor are non-negative integers.

Byteburg's limited funds allow construction of only a single lightning conductor.

Moreover, as you would expect, the higher it will be, the more expensive.

The lightning conductor of height ![](http://main.edu.pl/images/OI18/pio-en-tex.3.png) located on the roof of the building ![](http://main.edu.pl/images/OI18/pio-en-tex.4.png) (of height ![](http://main.edu.pl/images/OI18/pio-en-tex.5.png))    protects the building ![](http://main.edu.pl/images/OI18/pio-en-tex.6.png) (of height ![](http://main.edu.pl/images/OI18/pio-en-tex.7.png)) if the following inequality holds:

![](http://main.edu.pl/images/OI18/pio-en-tex.8.png)        where ![](http://main.edu.pl/images/OI18/pio-en-tex.9.png) denotes the absolute value of the difference between ![](http://main.edu.pl/images/OI18/pio-en-tex.10.png) and ![](http://main.edu.pl/images/OI18/pio-en-tex.11.png).

Byteasar, the mayor of Byteburg, asks your help.

Write a program that, for every building ![](http://main.edu.pl/images/OI18/pio-en-tex.12.png), determines the minimum height    of a lightning conductor that would protect all the buildings if it were put    on top of the building ![](http://main.edu.pl/images/OI18/pio-en-tex.13.png).




## 样例 #1

### 输入

```
6
5
3
2
4
2
4```

### 输出

```
2
3
5
3
5
4```

# AI分析结果



### 算法分类
**决策单调性优化**

---

### 综合分析与结论
**核心思路**：将绝对值拆分为左、右两部分，分别用决策单调性优化。  
**关键难点**：证明函数 $\sqrt{|i-j|}$ 满足决策单调性，并设计高效维护最优决策点的方法。  
**核心算法流程**：  
1. 正序处理左侧贡献，倒序处理右侧贡献  
2.维护一个决策队列，每个决策点覆盖一段连续区间  
3. 通过比较相邻决策的交点，动态调整决策区间  

**可视化设计**：  
1. **动画方案**：  
   - **网格视图**：用横向时间轴表示 i 的遍历，纵向表示候选决策点  
   - **决策区间**：用不同颜色色块表示队列中的决策覆盖范围  
   - **交点计算**：用闪烁光点动态展示二分查找或公式推导的交点位置  
2. **复古像素风格**：  
   - 使用 16 色调色板（如：NES 红白机配色）  
   - 决策队列变化时播放 8-bit 电子音效（如：`1UP` 音效）  
3. **AI 自动演示**：  
   - 自动步进时展示决策区间收缩/扩展过程  
   - 关键步骤（如弹出队尾、插入新决策）时高亮代码对应行  

---

### 题解清单（≥4星）

#### 1. HoshiuZ（★★★★☆）
**亮点**：  
- 完整证明四边形不等式与决策单调性  
- 提供分治与单调队列两种实现  
- 代码结构清晰，附带预处理的 sqrt 表  

**核心代码**：
```cpp
void work(int l,int r,int L,int R) {
    if(l>r) return;
    int mid=(l+r)>>1, p = L;
    double max_val = 0;
    for(int i=L; i<=min(mid,R); ++i)
        if(a[i]+sqrt(mid-i) > max_val)
            max_val = a[i]+sqrt(mid-i), p = i;
    dp[mid] = max(dp[mid], max_val);
    work(l,mid-1,L,p);
    work(mid+1,r,p,R);
}
```

#### 2. Alex_Wei（★★★★★）
**亮点**：  
- O(1) 计算决策交点的数学推导  
- 线性时间复杂度，实测速度最快  
- 代码高度优化，包含快速读入  

**核心推导**：  
$$ j + \frac{(j-k - d^2)^2}{4d^2} + 1 \quad (d=a_j - a_k) $$  
**代码片段**：  
```cpp
ll v = j - k - d * d;
pos = j + v * v / (d * d << 2) + 1;
```

#### 3. FlashHu（★★★★☆）
**亮点**：  
- 数形结合解释决策单调性  
- 引入几何画板风格的动态图示  
- 详细注释队列维护逻辑  

**可视化映射**：  
- 函数曲线用不同颜色折线表示  
- 当前最优决策点用高亮竖线标识  

---

### 最优思路/技巧提炼

#### 关键技巧
1. **决策单调性证明**：  
   - 通过比较 $\sqrt{x+1} - \sqrt{x}$ 的递减性证明四边形不等式  
2. **单调队列维护**：  
   - 每个决策点覆盖区间 [l, r]  
   - 插入新决策时弹出无法覆盖的旧区间  
3. **分治优化**：  
   - `mid = (l+r)/2` 时决策点分割左右子问题  

#### 实现优化
1. **预处理 sqrt 值**：避免重复计算加速 2~3 倍  
2. **双端队列存储三元组**：`(决策点, 左边界, 右边界)`  
3. **反转数组复用代码**：处理右侧贡献时反转数组后复用左侧逻辑  

---

### 同类型题目推荐
1. **P1912 [NOI2009] 诗人小G**  
   （决策单调性+单调队列）  
2. **P5507 机关**  
   （分治优化决策单调性）  
3. **CF868F Yet Another Minimization Problem**  
   （分治决策单调性+计数优化）  

---

### 个人心得摘录
> "调试时发现决策区间右边界计算错误，通过打印队列状态发现边界更新逻辑遗漏了 n 的限制" —— HoshiuZ  
> "将绝对值拆分为两次独立计算，代码量减少 50%，但推导过程需要严格验证对称性" —— Alex_Wei  

---

### 可视化代码片段（复古风格）
```javascript
// 绘制决策区间（8-bit 风格）
function drawBlock(ctx, x, y, w, h, color) {
    ctx.fillStyle = color;
    ctx.fillRect(x*20, y*20, w*20, h*20);
    ctx.strokeStyle = "#000";
    ctx.strokeRect(x*20, y*20, w*20, h*20);
}

// 播放音效
function playSound(type) {
    const osc = audioCtx.createOscillator();
    osc.frequency.setValueAtTime(type === 'pop' ? 880 : 440, audioCtx.currentTime);
    osc.connect(audioCtx.destination);
    osc.start(); osc.stop(audioCtx.currentTime + 0.1);
}
```

---

### 算法演示流程
1. **初始化**：展示初始决策队列（全范围第一个元素）  
2. **步进 i**：高亮当前 i，绘制对应竖线  
3. **弹出队尾**：红色闪烁被弹出区间，播放 `pop` 音效  
4. **插入新区间**：绿色闪烁新加入区间，展示交点计算公式  
5. **最终结果**：所有区间覆盖完成后，用彩虹色标记最大 p 值  

---

通过结合数学推导、代码优化与可视化交互，可深入理解决策单调性优化的核心思想，为动态规划类问题提供高效解决方案。

---
处理用时：73.63秒