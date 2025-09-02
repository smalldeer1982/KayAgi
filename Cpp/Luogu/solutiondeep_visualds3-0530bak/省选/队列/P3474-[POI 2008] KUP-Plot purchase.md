# 题目信息

# [POI 2008] KUP-Plot purchase

## 题目描述

Byteasar is going to buy an industrial plot.

His fortune is estimated at $k$ bythalers and this is exactly the amount    Byteasar would like to spend on the parcel.

Finding a parcel worth exactly $k$ bythalers, however, is not an easy task.

For this reason Byteasar is ready to buy a more expensive plot.

He considers taking out a loan. The Byteotian Credit Bank will grant him    a loan of up to $k$ bythalers. Thus, Byteasar can spend no more than $2k$    bythalers on the parcel and he would like to spend no less than $k$ bythalers.

The area in which Byteasar wants to buy his parcel is a square with side    length of $n$ metres. The current landlords have set up various prices per square metre. Byteasar has spoken to each one of them and has then prepared a price map    of the area. The map depicts the price of every metre by metre square. Clearly, there    are $n^2$ such squares. Now is the time to find the dream parcel. It has to be rectangular and consist of whole unit squares. Byteasar has already started looking for the plot on the map,    but after many hours he was still unable to find a suitable one. Be a chap and help him!

<Task> 

Write a programme that:

reads the numbers $k$ and $n$ from the standard input,  along with the price map of the area, determines a parcel with price in the interval $[k,2k]$ or states that no such parcel exists, writes out the result to the standard output.



## 说明/提示


给定 $k,n$ 和 $n\times n$ 的矩阵，求一个子矩形满足权值和在 $[k,2k]$ 之间。

$n<2000$，$1\le k\le10^9$，每个价格都是不大于$2 \times 10^9$ 的非负整数。

感谢@cn：苏卿念 提供的spj

## 样例 #1

### 输入

```
8 4
1 2 1 3
25 1 2 1
4 20 3 3
3 30 12 2```

### 输出

```
2 1 4 2```

# AI分析结果



**算法分类**  
悬线法/单调栈（极大子矩形问题）

---

### **题解思路与核心难点**

1. **核心思路**  
   - **预处理**：排除所有 >2k 的格子和 [k,2k] 的单个元素  
   - **极大子矩形**：用悬线法/单调栈找到由 <k 元素组成的最大子矩阵  
   - **切割调整**：若该矩阵和 ≥k，则通过逐行/列切割使其满足区间条件  

2. **关键证明**  
   - 若最大子矩阵和 >2k，通过逐行删除（每行和 <k）必然能找到满足条件的子矩阵（无法跳过 [k,2k] 区间）

3. **实现难点**  
   - 悬线法中 up/l/r 数组的动态维护  
   - 单调栈处理柱状图最大矩形时的边界条件  
   - 切割时的顺序选择（优先行或列）与二维前缀和的快速计算

---

### **题解评分（≥4星）**

1. **kczno1（★★★★★）**  
   - 亮点：最简洁的单调栈实现，直接集成切割逻辑  
   - 代码可读性：使用二维前缀和的紧凑计算，exit(0) 快速返回结果  

2. **i207M（★★★★☆）**  
   - 亮点：详细处理边界条件，提供调试经验（单调栈比较条件）  
   - 特色：显式维护极大矩形坐标，切割时优先处理行  

3. **奇米（★★★★☆）**  
   - 亮点：像素级注释预处理和单调栈操作  
   - 特色：切割时优先处理列，更易理解的变量命名  

---

### **最优思路提炼**

1. **极大子矩形快速定位**  
   ```cpp
   // 单调栈维护柱状图最大矩形（kczno1 实现）
   while(top && up[st[top]] >= up[j]) --top;
   L[j] = st[top] + 1; // 左边界
   st[++top] = j;
   ```

2. **动态切割策略**  
   ```cpp
   /* 切割逻辑（i207M）*/
   for(int i=aux; i>=alx; --i) {
       LL t = ask(i,aly,i,auy);
       if(t > 2*k) cutline(i,aly,auy); // 行内切割
       else mx -= t; // 整行丢弃
   }
   ```

3. **二维前缀和优化**  
   ```cpp
   // 预处理（白简）
   for(int i=1; i<=n; ++i)
       for(int j=1; j<=n; ++j)
           sum[i][j] = sum[i-1][j] + sum[i][j-1] 
                      - sum[i-1][j-1] + a[i][j];
   ```

---

### **同类题目推荐**

1. [P4147 玉蟾宫](https://www.luogu.com.cn/problem/P4147) - 极大子矩形模板题  
2. [P2733 家的范围](https://www.luogu.com.cn/problem/P2733) - 二维前缀和统计  
3. [P3400 仓鼠窝](https://www.luogu.com.cn/problem/P3400) - 带障碍的极大子矩阵计数  

---

### **算法可视化设计**

**动画方案**（基于 kczno1 代码）：  
1. **初始化阶段**  
   - 红色高亮 >2k 的障碍格子  
   - 绿色标记 [k,2k] 的合法单格（立即消失）  

2. **悬线法演示**  
   ```python
   # 伪代码流程
   for each row in matrix:
       update up[] array (蓝色渐变高度条)
       show monotonic stack operation with:
           - 当前柱子高亮黄色
           - 出栈柱子闪烁红色
           - 新左边界标记绿色
   ```

3. **切割过程**  
   - 最大矩形用橙色边框标记  
   - 逐行删除时，消失的行淡出+音效  
   - 找到解时全屏绿色闪烁+胜利音效  

**复古风格实现**：  
- 使用 `Canvas` 绘制 8-bit 像素网格  
- 音效：  
  - 障碍格子：低音 "boom"  
  - 行切割： "blip" 短音  
  - 找到解：经典 FC 过关音乐  

---

**核心代码片段（可视化逻辑）**  
```javascript
// 伪代码：切割动画
function animateCut(rect) {
    let rows = rect.height;
    for(let i=0; i<rows; i++) {
        // 高亮当前行
        ctx.fillStyle = 'rgba(255,255,0,0.3)';
        ctx.fillRect(rect.x, rect.y+i, rect.width, 1);
        
        // 播放切割音效
        playSound('blip', 0.2 + i*0.1);
        
        // 更新剩余矩形
        let remain = calculateRemaining(rect, i);
        if(remain.sum <= 2*k && remain.sum >=k) {
            flashGreen(remain); // 找到解
            return; 
        }
    }
}
```

---

**个人调试心得**  
> "单调栈的边界处理是最大难点——必须在栈底预置0，栈顶预置n+1，否则会漏掉边缘矩形" —— i207M  
> "切割时优先处理行更易实现，因为行的前缀和可以预处理" —— 奇米  

---

**总结**  
通过结合极大子矩阵定位与动态切割策略，该问题展现了二维问题的经典处理范式。可视化设计应重点呈现高度数组的维护过程与切割时的区间收缩逻辑，帮助理解连续性证明的核心思想。

---
处理用时：66.87秒