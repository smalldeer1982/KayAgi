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



**算法分类**  
贪心算法

---

### **题解思路与核心难点分析**  
#### 核心思路  
所有题解均采用以下两步：  
1. **可行性判断**：检查总时间是否在 `ΣminTime` 和 `ΣmaxTime` 之间。  
2. **贪心分配**：先为每天分配 `minTime`，将剩余时间按顺序尽可能多地分配到每天，不超过当天的 `maxTime - minTime`。

#### 解决难点  
- **关键变量**：  
  - `剩余时间 = sumTime - ΣminTime`  
  - `每天的可调整空间 = maxTime - minTime`  
- **分配逻辑**：依次将剩余时间分配给每个天数，优先填满前面的天数（若剩余时间足够则填满当天，否则填入剩余部分）。

#### 算法对比  
- **Priori_Incantatem**：直接操作原始数组，逐个调整天数。  
- **Loner_Knowledge**：使用结构体存储区间差值，减少重复计算。  
- **离散小波变换°**：代码最简洁，用单循环完成分配，无需嵌套循环。

---

### **题解评分 (≥4星)**  
1. **Priori_Incantatem (4星)**  
   - 亮点：代码简洁，逻辑清晰，适合初学者。  
   - 缺点：变量名 `a[i]` 和 `b[i]` 可读性差。  

2. **Loner_Knowledge (4星)**  
   - 亮点：结构体封装数据，逻辑分离明确。  
   - 缺点：内层循环效率略低（但不影响正确性）。  

3. **离散小波变换° (5星)**  
   - 亮点：代码高效简洁，直接单循环完成分配。  
   - 代码片段：  
     ```cpp  
     if(s >= T[i]) s -= T[i], printf("%d ", L[i]+T[i]);  
     else printf("%d ", L[i]+s), s = 0;  
     ```

---

### **最优思路提炼**  
- **贪心分配策略**：按顺序优先填满前面的天数，确保剩余时间快速归零。  
- **代码优化**：无需嵌套循环，直接计算每天能分配的最大值。  

---

### **同类型题与算法套路**  
- **类似问题**：区间分配问题、资源调度问题。  
- **通用解法**：先确定可行范围，再按顺序贪心分配剩余资源。  

---

### **推荐相似题目**  
1. **P1803 线段覆盖**（贪心选择区间）  
2. **P1223 排队接水**（贪心排序策略）  
3. **P1094 纪念品分组**（双指针贪心）  

---

### **可视化与算法演示设计**  
#### 核心动画逻辑  
1. **初始状态**：显示每天的 `minTime` 和 `maxTime` 区间条（像素化进度条）。  
2. **分配过程**：  
   - 高亮当前处理的天数（红色边框）。  
   - 动态填充剩余时间（绿色像素块增长）。  
   - 播放“填充音效”（8-bit 短音）。  
3. **完成/失败**：  
   - 成功：所有天数填充完毕，播放胜利音效（上扬音调）。  
   - 失败：显示“NO”并播放低沉音效。  

#### 复古风格设计  
- **颜色方案**：16色调色板，绿色填充条，红色边框高亮。  
- **音效**：Web Audio API 生成 8-bit 音效，如：  
  ```javascript  
  function playBeep(freq) {  
    const osc = new OscillatorNode(context, { frequency: freq });  
    osc.connect(gain).connect(context.destination);  
    osc.start(); osc.stop(context.currentTime + 0.1);  
  }  
  ```  

---

### **代码实现（核心逻辑）**  
```cpp  
// 离散小波变换° 的代码核心逻辑  
int s = total_sum - sum_min;  
for (int i = 0; i < n; ++i) {  
    if (s >= delta[i]) {  
        cout << (min[i] + delta[i]) << " ";  
        s -= delta[i];  
    } else {  
        cout << (min[i] + s) << " ";  
        s = 0;  
    }  
}  
```  

---

### **总结**  
本题通过贪心策略快速验证可行性并构造解，代码实现简洁高效。可视化设计可通过复古像素风格增强理解，核心在于动态展示剩余时间的分配过程。

---
处理用时：58.98秒