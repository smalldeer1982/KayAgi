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



## 唯一算法分类
贪心算法

---

## 综合分析与结论

### 核心思路与难点
1. **可行性判定**：检查 `sumTime` 是否在总最小时间 `ΣminTime_i` 和总最大时间 `ΣmaxTime_i` 之间。
2. **贪心构造方案**：  
   - 初始分配所有天数为 `minTime_i`，计算剩余时间 `s = sumTime - ΣminTime_i`。  
   - 从第 1 天开始，依次将天数的时间增加到 `maxTime_i`（每次尽可能多分配），直到 `s` 用完。

### 可视化设计思路
- **动画效果**：  
  - **进度条展示**：每个天数显示为横向进度条，左侧为 `minTime_i`，右侧为 `maxTime_i`。当前分配值用绿色填充，剩余时间用红色显示。  
  - **高亮当前操作天**：处理某天时，其进度条边框变为黄色，分配时填充部分动态扩展。  
  - **步进控制**：用户可点击“下一步”或拖动进度条观察分配过程。  
- **复古像素风格**：  
  - **8位音效**：每次分配时播放“滴答”声，完成时播放胜利音效。  
  - **像素字体**：使用复古字体展示天数、剩余时间等关键数据。  
  - **自动演示模式**：算法自动运行，每步间隔 0.5 秒，模拟贪心分配过程。

---

## 题解清单 (≥4星)

### 1. Priori_Incantatem（5星）
- **亮点**：代码简洁，直接体现贪心核心逻辑；变量命名清晰，循环处理剩余时间高效。
- **核心代码**：
  ```cpp
  s -= mins;
  i = 1;
  while (s) {
    if (s > b[i] - a[i]) {
      s -= b[i] - a[i];
      a[i] = b[i];
    } else {
      a[i] += s;
      s = 0;
    }
    i++;
  }
  ```

### 2. Loner_Knowledge（4.5星）
- **亮点**：结构清晰，预处理 `delta` 减少重复计算；输出与计算分离，可读性高。
- **核心代码**：
  ```cpp
  t -= sum.min;
  for (int i = 0; i < d; ++i) {
    if (t >= D[i].delta) {
      printf("%d ", D[i].max);
      t -= D[i].delta;
    } else {
      printf("%d ", t + D[i].min);
      t = 0;
    }
  }
  ```

### 3. dfadfsafsdaf（4星）
- **亮点**：代码最短，利用结构体存储数据；贪心分配逻辑与输出合并，减少变量使用。
- **核心代码**：
  ```cpp
  t -= sum.min;
  for (int i = 0; i < d; ++i) 
    if (t >= e[i].delta) cout << e[i].max << " ", t -= e[i].delta;
    else cout << t + e[i].min << endl, t = 0;
  ```

---

## 最优思路提炼
1. **贪心验证与构造**：  
   - 总时间必须在 `[Σmin, Σmax]` 内才可能有解。  
   - 初始分配 `minTime_i`，剩余时间按天依次填满至 `maxTime_i`，直到 `s=0`。

2. **代码优化技巧**：  
   - **预处理差值**：提前计算 `maxTime_i - minTime_i` 减少循环内计算。  
   - **线性遍历**：只需一次遍历即可完成分配，时间复杂度 `O(d)`。

---

## 类似题目推荐
1. **P1803 凌乱的yyy / 线段覆盖**：贪心选择不重叠区间。  
2. **P2240 【深基12.例1】部分背包问题**：按性价比贪心分配重量。  
3. **P1223 排队接水**：贪心排序使平均等待时间最短。

---

## 可视化代码片段（JavaScript）
```javascript
// 初始化 Canvas
const canvas = document.getElementById('animation');
const ctx = canvas.getContext('2d');
const days = [...]; // 数据
let s = totalRemaining;

function draw() {
  ctx.clearRect(0, 0, canvas.width, canvas.height);
  days.forEach((day, i) => {
    // 绘制进度条背景（灰色）
    ctx.fillStyle = '#666';
    ctx.fillRect(50, 50 + i * 40, 200, 20);
    // 绘制当前分配（绿色）
    ctx.fillStyle = '#0f0';
    ctx.fillRect(50, 50 + i * 40, (day.current - day.min) / (day.max - day.min) * 200, 20);
  });
}

function step() {
  if (s <= 0) return;
  const day = days[currentDay];
  const alloc = Math.min(s, day.max - day.current);
  day.current += alloc;
  s -= alloc;
  currentDay++;
  draw();
}
```

---

## 个人心得摘录
- **Priori_Incantatem**：强调“先填满再处理下一天”的直觉，避免复杂数据结构。  
- **Michael_Kong**：提醒注意输出 `YES/NO` 的大小写，避免提交错误。  
- **konglk**：通过预处理 `maxbeleft` 数组优化判断，体现空间换时间思想。

---

## 复古游戏化设计
- **颜色方案**：16 色 EGA 调色板，绿色填充条、红色剩余条、黄色边框。  
- **音效设计**：  
  - **分配成功**：8-bit 上升音阶（`C4-E4-G4`）。  
  - **完成分配**：胜利音乐（连续三个高音 `G5-A5-B5`）。  
- **积分系统**：每正确分配一天得 10 分，剩余时间未用完扣分。

---
处理用时：70.07秒