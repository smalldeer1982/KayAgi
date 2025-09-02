# 题目信息

# Before an Exam

## 题目描述

Tomorrow Peter has a Biology exam. He does not like this subject much, but $ d $ days ago he learnt that he would have to take this exam. Peter's strict parents made him prepare for the exam immediately, for this purpose he has to study not less than $ minTime_{i} $ and not more than $ maxTime_{i} $ hours per each $ i $ -th day. Moreover, they warned Peter that a day before the exam they would check how he has followed their instructions.

So, today is the day when Peter's parents ask him to show the timetable of his preparatory studies. But the boy has counted only the sum of hours $ sumTime $ spent him on preparation, and now he wants to know if he can show his parents a timetable $ sсhedule $ with $ d $ numbers, where each number $ sсhedule_{i} $ stands for the time in hours spent by Peter each $ i $ -th day on biology studies, and satisfying the limitations imposed by his parents, and at the same time the sum total of all $ schedule_{i} $ should equal to $ sumTime $ .

## 样例 #1

### 输入

```
1 48
5 7
```

### 输出

```
NO
```

## 样例 #2

### 输入

```
2 5
0 1
3 5
```

### 输出

```
YES
1 4 ```

# AI分析结果



---

## 唯一算法分类：贪心

---

## 综合分析与结论

### 核心算法流程
1. **可行性判断**  
   Σmin ≤ sumTime ≤ Σmax  
   若不满足直接输出 NO

2. **贪心分配策略**  
   - **基础分配**：所有天先取最小值  
   - **增量填充**：从第1天开始，在不超过当天最大值的前提下，尽可能填满剩余时间  
   - **终止条件**：剩余时间归零时停止

### 解决难点
- **时间分配的顺序性**：需保证每个增量操作后仍满足总和约束  
- **剩余时间的动态调整**：需实时计算可分配的最大增量（max[i] - min[i]）

### 可视化设计要点
1. **动画方案**  
   - 网格表示天数，每格显示当前时间（初始为min值）  
   - 用红色高亮当前正在调整的天数  
   - 剩余时间以进度条形式展示

2. **复古像素风格**  
   - 使用 8-bit 色块（16色）表示时间区间：  
     🔵 最小值 | 🟢 当前值 | 🔴 最大值  
   - 时间填充时播放「像素点击」音效（Web Audio API）  
   - 成功时播放胜利音效（16-bit 上升音阶）

3. **交互设计**  
   - **暂停/继续**：观察中间状态  
   - **步进控制**：手动触发下一步填充  
   - **自动模式**：以固定速度播放填充过程

---

## 题解清单（≥4星）

### 1. Priori_Incantatem（⭐⭐⭐⭐⭐）
- **亮点**：极简实现 + 线性时间复杂度  
- **代码可读性**：变量命名清晰，无冗余操作  
- **核心代码**：
  ```cpp
  while(s) {
    if(s > b[i]-a[i]) { // 尽可能填满当天
      s -= b[i]-a[i];
      a[i] = b[i];
    } else { // 填充剩余量
      a[i] += s;
      s = 0;
    }
    i++;
  }
  ```

### 2. Loner_Knowledge（⭐⭐⭐⭐）
- **亮点**：结构体存储差值 + 增量预计算  
- **优化点**：避免重复计算(max[i]-min[i])

### 3. 离散小波变换°（⭐⭐⭐⭐）
- **亮点**：代码高度压缩 + 单次遍历  
- **关键逻辑**：
  ```cpp
  if(s >= T[i]) s -= T[i], printf("%d ",L[i]+T[i]);
  else printf("%d ",L[i]+s), s=0;
  ```

---

## 最优思路提炼

### 关键技巧
1. **两步式分配法**  
   先满足基础约束（min），再处理剩余时间  
   `总剩余时间 = sumTime - Σmin`

2. **贪心顺序选择**  
   按天序填充，保证尽早消耗剩余时间  
   *证明：任意顺序填充均可，但顺序处理实现最简单*

3. **差值预计算**  
   预处理 `max[i]-min[i]` 提升效率

---

## 同类型题推荐

1. **P1255 数楼梯**（贪心 + 高精度）  
2. **P1094 纪念品分组**（双指针贪心）  
3. **P1223 排队接水**（排序贪心）

---

## 代码核心实现

### 贪心算法片段
```cpp
int remaining = sumTime - total_min;
for(int day=0; day<d; ++day){
    int can_add = min(remaining, max[day]-min[day]);
    schedule[day] = min[day] + can_add;
    remaining -= can_add;
    if(remaining == 0) break;
}
```

---

## 可视化伪代码（Canvas实现）

```javascript
// 初始化画布
const canvas = document.getElementById('visual');
const ctx = canvas.getContext('2d');

// 绘制时间条
function drawBar(day, current, min, max) {
    const width = (current - min)/(max - min) * BAR_WIDTH;
    ctx.fillStyle = '#8BC34A'; // 绿色填充
    ctx.fillRect(X_START, Y_START + day*ROW_HEIGHT, width, BAR_HEIGHT);
    
    // 高亮当前操作
    if(day === currentDay) {
        ctx.strokeStyle = '#FF5722'; // 橙色边框
        ctx.strokeRect(X_START, Y_START + day*ROW_HEIGHT, BAR_WIDTH, BAR_HEIGHT);
    }
}

// 音效触发
function playSound(type) {
    const sfx = {
        fill: new Audio('data:audio/wav;base64,UklGRl9...'), // 填充音效
        done: new Audio('data:audio/wav;base64,UklGRk9...') // 完成音效
    };
    sfx[type].play();
}
```

---

## 个人心得摘录

> "在实现增量填充时，最初错误地从最后一天开始填充，导致剩余时间无法正确分配。后来改为顺序填充并单步调试，才理解贪心顺序不影响最终结果但影响中间状态。"  
> —— 某题解评论区调试经历

---

## 复古游戏化设计

### 实现要素
1. **像素风格**  
   - 使用 16x16 像素字体  
   - 时间条用 8x8 色块拼接

2. **音效设计**  
   - 填充音效：FC 风格「哔」声（Square wave, 440Hz, 50ms）  
   - 成功音效：上升琶音（C4-E4-G4-C5）  
   - 失败音效：低频噪音（100Hz, 200ms）

3. **自动演示AI**  
   ```javascript
   function autoPlay() {
       const interval = setInterval(() => {
           if(remaining === 0) {
               clearInterval(interval);
               playSound('done');
           } else {
               performNextFill();
               playSound('fill');
           }
       }, 1000); // 1秒/步
   }
   ```

---
处理用时：69.86秒