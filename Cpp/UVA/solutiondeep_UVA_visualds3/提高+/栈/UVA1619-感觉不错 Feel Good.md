# 题目信息

# 感觉不错 Feel Good

## 题目背景

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=825&page=show_problem&problem=4494

[PDF](https://uva.onlinejudge.org/external/16/p1619.pdf)

## 题目描述

给出正整数 $n$ 和一个长度为 $n$ 的数列 $a$，要求找出一个子区间 $[l,r]$，使这个子区间的数字和乘上子区间中的最小值最大。

形式化的，要求找出 $[l,r]$ 使得：
$$
\left(\sum \limits_{i=l}^{r}a_i\right)\times\min\limits_{i=l}^{r}a_i
$$
最大。输出这个最大值与区间的两个端点。

在答案相等的情况下最小化区间长度，最小化长度的情况下最小化左端点序号。


## 说明/提示

$1 \leq n \leq 10^5, 0 \leq a_i \leq 10^6$。

## 样例 #1

### 输入

```
6
3 1 6 4 5 2```

### 输出

```
60
3 5```

# AI分析结果



### 唯一算法分类  
**单调栈**

---

### 综合分析与结论  
**核心思路**：通过单调栈预处理每个元素作为区间最小值时的最大扩展范围，结合前缀和快速计算区间和，最终遍历比较得出最优解。

**算法流程**：  
1. **预处理左右边界**：  
   - 正序遍历数组，用单调递增栈找到每个元素右侧第一个比它小的位置  
   - 逆序遍历数组，找到每个元素左侧第一个比它小的位置  
2. **计算前缀和**：快速获取任意区间的和  
3. **遍历比较**：对每个元素计算其作为最小值的区间贡献值，维护最大值及对应区间  

**解决难点**：  
- 通过单调栈将寻找边界的复杂度从 O(n²) 优化到 O(n)  
- 正确处理多解情况（长度优先、左端点优先）  

**可视化设计**：  
1. **像素风格动画**：  
   - 数组元素显示为彩色方块，高度对应数值  
   - 单调栈用不同颜色标记（如紫色边框）  
   - 当前处理元素高亮闪烁  
2. **音效触发**：  
   - 元素入栈：短促"哔"声  
   - 元素出栈：低沉"嘟"声  
   - 找到最优解：胜利音效  
3. **操作演示**：  
   ```javascript
   // 伪代码演示栈操作动画
   function animateStack(i) {
     highlight(i); // 当前元素闪烁
     while(stackNotEmpty() && top() > a[i]) {
       playSound('pop'); 
       let elem = stack.pop();
       setRightBound(elem, i-1); // 右边界动画
     }
     pushToStack(i); // 入栈动画
   }
   ```

---

### 题解清单（≥4星）  
#### 1. Mr_think（★★★★★）  
**亮点**：  
- 清晰解释单调栈预处理过程  
- 完整处理多组输入和输出格式  
- 代码包含关键条件判断逻辑  

**关键代码**：  
```cpp
// 单调栈处理右边界
for(int i=1;i<=n;i++) {
    while(top && a[i]<a[st[top]]) 
        you[st[top--]]=i-1;
    st[++top]=i;
}
```

#### 2. Stinger（★★★★☆）  
**亮点**：  
- 使用标准库stack实现，代码规范  
- 处理前缀和的溢出风险（long long）  
- 详细注释边界情况处理  

**个人心得**：  
> "栈内保存未确定右边界的元素，利用单调性保证每个元素只入栈出栈一次"

#### 3. 让风忽悠你（★★★★☆）  
**亮点**：  
- 悬线法替代单调栈实现  
- 动态维护区间扩展的左右边界  
- 代码简洁易懂  

**关键逻辑**：  
```cpp
for(int i=1;i<=n;i++)
    while(l[i]>1 && a[i]<=a[l[i]-1]) l[i]=l[l[i]-1];
```

---

### 最优思路提炼  
**关键技巧**：  
1. **单调栈双遍历**：正序找右边界，逆序找左边界  
2. **前缀和加速**：O(1) 时间获取任意区间和  
3. **多解处理策略**：  
   ```cpp
   if(now==ans && (r-l < best_r-best_l || 
      (r-l == best_r-best_l && l < best_l)))
   ```

**思维突破**：  
将"枚举区间"转换为"枚举最小值"，利用单调性快速确定有效区间范围。

---

### 相似题目推荐  
1. **POJ 2559** - 最大矩形面积（单调栈模板题）  
2. **LeetCode 84** - 柱状图中最大矩形（进阶变形）  
3. **洛谷 P5788** - 右侧第一个更大元素（单调栈基础）

---

### 可视化算法演示  
**动画设计**：  
```javascript
class MonotonicStackVisualizer {
  constructor(canvas) {
    this.ctx = canvas.getContext('2d');
    this.colors = ['#FF6B6B', '#4ECDC4', '#45B7D1']; // 像素风格配色
  }

  drawStep(i, stack, a, l, r) {
    // 绘制数组元素
    a.forEach((val, idx) => {
      const color = idx === i ? this.colors[0] : 
                   stack.includes(idx) ? this.colors[1] : this.colors[2];
      this.drawBlock(idx, val, color);
    });
    
    // 绘制当前处理的左右边界
    this.highlightBoundary(l[i], r[i]);
  }
  
  drawBlock(x, height, color) {
    // 8位风格方块绘制
    this.ctx.fillStyle = color;
    this.ctx.fillRect(x*30, 200-height*5, 28, height*5); // 每个块宽30px
  }
}
```

**交互功能**：  
- 速度调节滑块：`<input type="range" id="speed">`  
- 单步执行按钮：`<button onclick="nextStep()">▶</button>`  
- 自动播放模式：通过`requestAnimationFrame`实现帧控制

---

### 核心代码实现  
**单调栈预处理 + 前缀和计算**：  
```cpp
// 预处理右边界
stack<int> stk;
for(int i=1; i<=n; i++) {
    while(!stk.empty() && a[i] < a[stk.top()]) {
        r[stk.top()] = i-1;
        stk.pop();
    }
    stk.push(i);
}

// 计算前缀和
partial_sum(a.begin(), a.end(), prefix.begin());
```

**最优解判断逻辑**：  
```cpp
long long current = a[i] * (prefix[r[i]] - prefix[l[i]-1]);
if(current > ans || (current == ans && (r-l < ans_r-ans_l))) {
    update_answer();
}
```

---
处理用时：65.53秒