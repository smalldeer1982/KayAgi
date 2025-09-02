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



### **唯一算法分类**
**单调栈**

### **综合分析与结论**
**核心思路**：枚举每个元素作为区间最小值，利用单调栈预处理其左右第一个更小值的位置，确定最大扩展区间。区间和通过前缀和快速计算，最终遍历所有元素取最大值。

**难点与解决**：
1. **高效确定左右边界**：通过两次单调栈遍历，分别处理每个元素左右第一个更小值的位置，时间复杂度 O(n)。
2. **处理多组数据与输出格式**：注意 UVA 的多组输入要求及输出间空行的处理。
3. **最优解选择逻辑**：在最大值相同时优先选择最短区间，再优先左端点最小。

**可视化设计要点**：
- **动画演示**：以数组元素为像素方块，当前处理元素高亮为红色，栈内元素为蓝色。弹出栈顶时标记其右边界，入栈时显示左边界扩展。前缀和计算部分以绿色动态显示区间和。
- **复古像素风格**：采用 8-bit 音效，元素边界确定时播放“哔”声，找到更大解时播放“叮”声。自动模式下步进速度可调，背景音乐为经典 FC 风格循环旋律。

---

### **题解清单 (≥4星)**
1. **Mr_think (5星)**
   - **亮点**：思路清晰，代码结构简洁，详细解释单调栈处理过程，处理多组数据严谨。
   - **关键代码**：
     ```cpp
     for(int i=1;i<=n;i++) {
         while(top && a[i]<a[st[top]]) you[st[top--]]=i-1;
         st[++top]=i;
     }
     ```

2. **Stinger (5星)**
   - **亮点**：深入分析单调栈的单调性原理，代码注释详细，输出格式处理周全。
   - **个人心得**：强调“栈内元素离栈顶越近越大”，帮助理解单调栈核心逻辑。

3. **让风忽悠你 (4星)**
   - **亮点**：悬线法实现，代码简洁，提供独特解题视角。
   - **关键优化**：通过左右扩展替代单调栈，适合理解扩展思想的初学者。

---

### **最优思路与代码实现**
**核心代码**（Mr_think 的关键逻辑）：
```cpp
// 预处理右边界
for(int i=1;i<=n;i++) {
    while(top && a[i]<a[st[top]]) 
        you[st[top--]]=i-1;
    st[++top]=i;
}
while(top) you[st[top--]]=n;

// 预处理左边界
for(int i=n;i>=1;i--) {
    while(top && a[i]<a[st[top]]) 
        zuo[st[top--]]=i+1;
    st[++top]=i;
}
while(top) zuo[st[top--]]=1;

// 计算结果
long long ans = 0;
for(int i=1;i<=n;i++) {
    long long now = a[i]*(sum[you[i]] - sum[zuo[i]-1]);
    if(now > ans || (now == ans && (you[i]-zuo[i] < dy-dz))) {
        ans = now;
        dz = zuo[i]; dy = you[i];
    }
}
```

---

### **相似题目推荐**
1. **POJ 2559** - 柱状图中的最大矩形（单调栈模板题）
2. **LeetCode 84** - 柱状图中最大的矩形（进阶变形）
3. **洛谷 P5788** - 单调栈模板题

---

### **可视化算法演示（伪代码）**
```javascript
// 初始化像素画布
const canvas = initCanvas(800, 600); 
const elements = data.map(val => new PixelBlock(val)); 

// 单调栈动画步骤
function animateStackProcess() {
    let stack = [];
    elements.forEach((elem, i) => {
        elem.highlight('red'); // 当前元素高亮
        while(stack.length > 0 && stack.top().val > elem.val) {
            let topElem = stack.pop();
            topElem.setRightBound(i-1); // 确定右边界
            playSound('beep'); // 音效反馈
        }
        elem.setLeftBound(stack.isEmpty() ? 0 : stack.top().index);
        stack.push(elem);
        elem.highlight('blue'); // 入栈元素标记
    });
}
```

---

### **总结**
通过单调栈预处理边界+前缀和计算区间和是该题的最优解，时间复杂度 O(n)。可视化设计应重点展示边界扩展过程与栈的动态变化，复古像素风格可增强学习趣味性。相似题目多围绕单调栈应用展开，需重点掌握该算法的核心思想。

---
处理用时：66.77秒