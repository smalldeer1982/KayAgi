# 题目信息

# Group Photo 2 (online mirror version)

## 题目描述

Many years have passed, and $ n $ friends met at a party again. Technologies have leaped forward since the last meeting, cameras with timer appeared and now it is not obligatory for one of the friends to stand with a camera, and, thus, being absent on the photo.

Simply speaking, the process of photographing can be described as follows. Each friend occupies a rectangle of pixels on the photo: the $ i $ -th of them in a standing state occupies a $ w_{i} $ pixels wide and a $ h_{i} $ pixels high rectangle. But also, each person can lie down for the photo, and then he will occupy a $ h_{i} $ pixels wide and a $ w_{i} $ pixels high rectangle.

The total photo will have size $ W×H $ , where $ W $ is the total width of all the people rectangles, and $ H $ is the maximum of the heights. The friends want to determine what minimum area the group photo can they obtain if no more than $ n/2 $ of them can lie on the ground (it would be strange if more than $ n/2 $ gentlemen lie on the ground together, isn't it?..)

Help them to achieve this goal.

## 样例 #1

### 输入

```
3
10 1
20 2
30 3
```

### 输出

```
180
```

## 样例 #2

### 输入

```
3
3 1
2 2
4 3
```

### 输出

```
21
```

## 样例 #3

### 输入

```
1
5 10
```

### 输出

```
50
```

# AI分析结果



**唯一算法分类**  
贪心算法

---

### **综合分析与结论**  
**题目核心**：在限制最多n/2人躺下的前提下，选择每个人的方向（站立/躺下），使得总宽度和最大高度的乘积最小。  
**解决思路**：  
1. **枚举最大高度maxh**：由于高度由最大值决定，枚举所有可能的maxh（范围1~最大w/h值）。  
2. **分类处理每个人**：  
   - 若两个方向均>maxh：无解。  
   - 若h>maxh且w≤maxh：必须躺下（计入躺下人数）。  
   - 若w>maxh且h≤maxh：必须站立。  
   - 其余可自由选择的人：按w_i-h_i排序，优先选差值大的躺下以最小化总宽度。  
3. **贪心优化**：在满足躺下人数限制的前提下，选择能最大减少宽度的候选人。  

**难点对比**：  
- **枚举范围**：需覆盖所有可能的maxh候选值（如所有出现过的w和h）。  
- **躺下人数限制**：需动态统计必须躺下人数，并高效处理可选躺下的最优选择。  
- **数据结构**：使用排序（如vector）或优先队列实现贪心策略。  

**可视化设计**：  
1. **动画流程**：  
   - 步进式展示每个maxh的枚举过程，高亮当前maxh值。  
   - 对每个人显示其w/h矩形，颜色标记状态（红：必须躺下，黄：必须站立，绿：可选）。  
   - 动态展示排序后的可选列表，逐项选择差值大的躺下。  
2. **复古像素效果**：  
   - 用8位风格绘制每个人的矩形块，maxh值以闪烁像素数字显示。  
   - 音效：选择躺下时播放“哔”声，无解时播放低音，找到更优解时播放上升音调。  
3. **交互面板**：  
   - 允许调节枚举速度，单步执行maxh或自动播放。  
   - 显示当前最优解的面积及对应的maxh和总宽度。  

---

### **题解清单 (4星及以上)**  
1. **communist（4星）**  
   - **亮点**：代码简洁，直接枚举maxh并分类处理，排序后贪心选择。  
   - **关键代码**：按w_i-h_i降序排序，动态调整躺下人数。  
   - **个人心得**：未明确提及，但代码逻辑清晰易于调试。  

2. **Bitter_Tea（4星）**  
   - **亮点**：结合前缀和剪枝，优先队列优化贪心选择。  
   - **关键代码**：处理不存在于h中的maxh时，选取最优w对应的h。  
   - **个人心得**：通过前缀和提前排除无效maxh，提升效率。  

3. **Happy_mouse（4星）**  
   - **亮点**：详细分类讨论五种情况，逻辑严谨。  
   - **关键代码**：分情况统计必躺人数，排序可选列表。  
   - **个人心得**：明确列出每种情况的处理策略，适合教学。  

---

### **最优思路与技巧提炼**  
1. **枚举maxh**：覆盖所有可能的候选值，避免遗漏最优解。  
2. **分类讨论**：明确每个人的状态（必躺/必站/可选），简化决策。  
3. **贪心排序**：按w_i-h_i降序选择可选躺下的人，最大化宽度减少。  
4. **数据结构优化**：使用排序或优先队列高效处理动态选择。  

---

### **同类型题与算法套路**  
- **类似问题**：资源分配问题（如背包变种）、双参数优化问题（如矩形覆盖）。  
- **通用解法**：固定一个参数（如最大值），贪心优化另一个参数的总和。  

---

### **推荐相似题目**  
1. **CF524B**（原题简单版，无躺下人数限制）  
2. **P2893 [USACO08FEB] Making the Grade G**（调整序列使非降，最小代价）  
3. **P2216 [HAOI2007] 理想的正方形**（二维滑动窗口最值）  

---

### **代码核心实现**  
```cpp
// 取自 communist 题解的核心逻辑
for(int maxh=1;maxh<=hh;maxh++) {
    int cnt=0, rs=sum_width;
    vector<int> candidates;
    for(int i=1;i<=n;i++) {
        if(w[i]>maxh && h[i]>maxh) { cnt=INF; break; } // 无解
        else if(h[i]>maxh) { cnt++; rs += h[i]-w[i]; } // 必须躺下
        else if(w[i]>maxh) continue;                   // 必须站立
        else if(w[i]>h[i]) candidates.push_back(i);    // 可选躺下
    }
    if(cnt > n/2) continue;
    sort(candidates.begin(), candidates.end(), [&](int a, int b) {
        return (w[a]-h[a]) > (w[b]-h[b]); // 按差值降序
    });
    // 贪心选择最多n/2 - cnt个
    for(int i=0; i < min((int)candidates.size(), n/2 - cnt); i++) {
        rs += h[candidates[i]] - w[candidates[i]];
    }
    ans = min(ans, rs * maxh);
}
```

---

### **复古游戏化动画代码片段**  
```javascript
// Canvas绘制示例（伪代码）
function drawStep(maxh, selected) {
    ctx.fillStyle = '#8B8B83'; // 复古灰背景
    ctx.fillRect(0, 0, canvas.width, canvas.height);
    // 绘制每个人矩形块
    people.forEach((p, i) => {
        let [w, h] = getOrientation(p, maxh);
        ctx.fillStyle = getColor(p, maxh, selected.includes(i));
        ctx.fillRect(x, y, w * scale, h * scale); // 缩放显示
    });
    // 显示当前maxh和面积
    drawPixelText(`MAXH: ${maxh}`, 10, 10);
    playSound('step'); // 步进音效
}
```

---
处理用时：112.61秒