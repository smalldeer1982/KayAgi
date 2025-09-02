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



### 唯一算法分类  
贪心算法  

---

### 题解思路与核心难点分析  
**核心逻辑**：  
1. **可行性判断**：总时间需介于 ∑minTime 和 ∑maxTime 之间  
2. **贪心构造方案**：  
   - 初始分配每天最小时间  
   - 将剩余时间 `sumTime - ∑minTime` 按顺序尽可能分配到各天（不超过该天 maxTime）  

**解决难点对比**：  
- **数据结构**：多数题解使用数组存储每天区间，部分用结构体保存 min/max/delta  
- **分配策略**：所有题解均采用顺序填充，但实现方式不同（如单循环 vs 二重循环）  
- **输出处理**：部分题解在分配时直接修改原数组，部分新建结果数组  

---

### 题解评分（≥4星）  
1. **Priori_Incantatem（4星）**  
   - 亮点：最简代码框架，直接修改原数组节省空间  
   - 缺点：错误信息非标准输出（NO! YOU ARE...）  
2. **离散小波变换°（5星）**  
   - 亮点：代码极简（18行核心逻辑），变量命名清晰  
3. **Loner_Knowledge（4星）**  
   - 亮点：结构体封装数据，逻辑分层明确  

---

### 最优思路提炼  
**关键技巧**：  
1. **剩余时间动态分配**：`sumTime -= minSum` 后，按天顺序填充 `maxTime[i]-minTime[i]` 的差值  
2. **即时终止条件**：当剩余时间为0时立即停止分配  
3. **区间约束验证**：O(1) 时间完成可行性判断  

**代码片段示例**：  
```cpp
sum -= mins; // 计算可分配剩余时间
for(int i=1; i<=d; i++) {
    if(sum >= delta[i]) { // 尽可能填满当前天
        cout << maxTime[i] << " ";
        sum -= delta[i];
    } else { // 分配最后一部分
        cout << (minTime[i] + sum) << " ";
        sum = 0;
    }
}
```

---

### 相似题目推荐  
1. **P1255 数楼梯**（动态资源分配）  
2. **P1094 纪念品分组**（区间配对贪心）  
3. **P1803 凌乱的yyy / 线段覆盖**（区间调度贪心）  

---

### 算法可视化设计  
**动画方案**：  
1. **柱状图动态更新**：  
   - 初始显示所有天的 `minTime` 柱（蓝色）  
   - 红色进度条从下至上增长，表示当前分配的额外时间  
   - 当某天被填满至 `maxTime` 时，柱体变绿色  
2. **交互元素**：  
   - 速度滑块控制分配过程  
   - 暂停/继续按钮冻结当前状态  
   - 当前操作天用闪烁边框高亮  

**复古像素风实现**：  
```javascript
// 伪代码示例：Canvas绘制柱状图
function drawDay(day, height, isCurrent) {
  ctx.fillStyle = isCurrent ? "#FF5555" : "#5555FF";
  ctx.fillRect(day*30, 200-height, 25, height);
  if(height === maxHeight[day]) ctx.fillStyle = "#55FF55"; // 填满变绿
}
```

---

### 个人心得摘录  
- **Priori_Incantatem**：  
  > "先每天学习mintime小时然后多余的时间依次塞，像往桶里倒水一样简单"  
  → 形象比喻帮助理解贪心本质  

- **konglk**：  
  > "从后往前推当前能取得最大值，像倒可乐瓶底的糖"  
  → 逆向思维提供另一种分配视角  

---

### 核心算法演示（GIF静态示意）  
![贪心分配过程](https://via.placeholder.com/600x200/000/fff?text=动态展示柱状图+剩余时间)  
1. 初始状态：所有蓝柱为minTime  
2. 红色进度条逐天增长  
3. 填满的柱变绿，剩余时间数字递减  
4. 最终所有柱总和等于sumTime  

--- 

通过本案例可掌握贪心算法在区间分配问题中的典型应用模式，重点理解可行性判断与顺序填充的核心思想。

---
处理用时：73.90秒