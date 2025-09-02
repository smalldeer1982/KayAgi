# 题目信息

# Sale

## 题目描述

Once Bob got to a sale of old TV sets. There were $ n $ TV sets at that sale. TV set with index $ i $ costs $ a_{i} $ bellars. Some TV sets have a negative price — their owners are ready to pay Bob if he buys their useless apparatus. Bob can «buy» any TV sets he wants. Though he's very strong, Bob can carry at most $ m $ TV sets, and he has no desire to go to the sale for the second time. Please, help Bob find out the maximum sum of money that he can earn.

## 样例 #1

### 输入

```
5 3
-6 0 35 -2 4
```

### 输出

```
8
```

## 样例 #2

### 输入

```
4 2
7 0 0 -7
```

### 输出

```
7
```

# AI分析结果



## 唯一算法分类
贪心算法

---

## 综合分析与结论
本题要求选取最多 m 个价格最低的负值元素，求和的绝对值即为最大收益。所有题解均采用贪心策略，核心步骤为：
1. **排序**：将数组升序排列
2. **选择**：从前向后遍历，取前 m 个负数
3. **边界处理**：遇到非负数或选满 m 个时停止

**难点对比**：  
- 取反法（empty）需处理符号转换，可能存在理解门槛  
- 零值处理（Cinderella）错误地将零计入，但实际不影响结果  
- 堆实现（fls233666）展示不同数据结构的选择  

**可视化设计**：  
- **动画方案**：展示数组排序后逐步选取元素的过程，已选元素标绿色，非负数标红色  
- **交互设计**：允许调整 m 的值，动态显示选取过程和总和  
- **复古风格**：用 8-bit 像素风格显示数组，选中元素时播放 "coin" 音效，结束播放胜利音效  

---

## 题解清单（≥4星）
1. **骗分过样例（5星）**  
   - 亮点：代码极简，条件判断精准，直接体现贪心核心  
   - 关键代码：  
     ```cpp
     sort(a,a+n);
     for(int i=0;i<m;i++) if(a[i]<0) total += -a[i];
     ```

2. **xuezhe（5星）**  
   - 亮点：Python实现简洁，逻辑清晰，边界处理明确  
   - 关键代码：  
     ```python
     a.sort()
     while i<m and a[i]<0: s -= a[i]; i +=1
     ```

3. **fls233666（4星）**  
   - 亮点：堆结构实现，展示不同数据结构的应用  
   - 关键代码：  
     ```cpp
     priority_queue<int, vector<int>, greater<int>> q;
     if(a<0) q.push(a);
     while(!q.empty() && m--) ans -= q.top();
     ```

---

## 最优思路提炼
- **核心贪心**：排序后取前 m 个最小负数  
- **实现技巧**：  
  - 直接排序原数组，避免符号转换的潜在错误  
  - 循环中严格判断 `<0`，确保零值不参与计算  
  - 提前终止循环优化性能  

---

## 同类题目推荐
1. **P1090 合并果子** - 贪心+优先队列  
2. **P1208 混合牛奶** - 单价排序贪心  
3. **P4995 跳跳！** - 交替极值选择  

---

## 个人心得摘录
> "注意是赚的钱，要用零减" —— 芝麻大饼  
> **启示**：符号转换需谨慎，建议保持原数组处理  

---

## 可视化代码片段（复古风格）
```javascript
// 伪代码：Canvas绘制排序数组
const drawArray = (arr, selected) => {
  ctx.fillStyle = "#2D2D2D"; // 背景色
  ctx.fillRect(0, 0, width, height);
  arr.forEach((val, i) => {
    ctx.fillStyle = selected.includes(i) ? "#00FF00" : val < 0 ? "#FF0000" : "#FFFFFF";
    drawPixelBlock(i * 10, 50, val); // 绘制像素块
  });
};
// 音效触发
function playSound(effect) {
  if(effect === 'pick') beep(440, 50); // 选中音
  else if(effect === 'end') beep(880, 200); // 结束音
}
```

---
处理用时：261.70秒