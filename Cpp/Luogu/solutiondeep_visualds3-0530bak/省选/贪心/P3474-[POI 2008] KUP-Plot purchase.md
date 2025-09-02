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



### 综合分析与结论

**题目核心**：在二维矩阵中寻找满足和值区间约束的矩形区域，需处理大规模数据（n≤2000）。

**核心思路与难点**：
1. **预处理与单个元素处理**：排除>2k的无效点，直接命中[k,2k]的单个元素。
2. **极大子矩阵搜索**：用悬线法/单调栈找到由<k元素构成的最大子矩阵，其和≥k是解存在的充要条件。
3. **贪心切割策略**：若极大子矩阵和超过2k，逐行或逐列切割，利用元素<k的连续性确保总能找到合法区间。

**贪心策略与可视化设计**：
- **贪心切割**：每次选择行或列切割时，优先处理超限方向（例如和>2k时切割最后一行或列），通过步进式调整保证解的连续存在。
- **可视化关键点**：
  - **悬线法/单调栈过程**：高亮当前处理的矩阵高度与扩展区域。
  - **切割过程**：用颜色标记当前切割行/列，动态显示剩余矩阵的和值变化。
  - **复古像素风格**：矩阵元素以不同色块表示，切割时播放8-bit音效，成功时触发胜利音效。

---

### 题解清单（评分≥4星）

1. **kczno1（★★★★★）**
   - **亮点**：悬线法实现简洁，切割逻辑清晰，代码效率高。
   - **核心代码**：
     ```cpp
     while(S(li,lj,i,rj)>2*k) {
         if(S(li,lj,li+1,rj)>2*k) ++lj; // 列切割
         else ++li; // 行切割
     }
     ```

2. **i207M（★★★★☆）**
   - **亮点**：详细处理单调栈边界，切割时分层处理行和列。
   - **心得引用**：“即使坏点也要入栈充数”，强调边界处理的重要性。

3. **奇米（★★★★☆）**
   - **亮点**：注释清晰，切割逻辑分步实现，适合学习。
   - **关键片段**：
     ```cpp
     for(int j=by;j>=ay;--j) { // 列切割
         mx-=a[i][j];
         if(mx>=k) exit(0);
     }
     ```

---

### 最优思路与技巧提炼

**关键步骤**：
1. **极大子矩阵定位**：悬线法记录每列向上延伸高度，单调栈快速计算左右边界。
2. **贪心切割保证解存在性**：
   - 若子矩阵和>2k，必存在单行或单列可切割至合法区间。
   - 切割时优先处理最外侧行列，利用元素和<k的连续性避免解丢失。

**实现技巧**：
- **二维前缀和**：O(1)查询子矩阵和。
- **栈优化**：单调栈处理极大子矩阵时预存0和n+1避免边界判断。

---

### 同类型题与算法套路

**相似问题**：
1. **最大全0子矩阵**（如P4147玉蟾宫）——同用悬线法/单调栈。
2. **区间调整问题**：如从大区间切割满足条件的小区间，常用贪心逐步逼近。
3. **连续子数组和约束**：一维扩展到二维的思维迁移。

**通用套路**：
- **二维问题降维**：按行或列分解为多个一维问题。
- **贪心调整**：从极大解逐步缩小至合法范围，利用数据特性保证解存在。

---

### 推荐相似题目

1. **P4147 玉蟾宫**（悬线法模板题）
2. **P1719 寻找最大子矩阵**（二维最大和变形）
3. **P3400 仓鼠窝**（极大子矩阵计数）

---

### 个人心得摘录

- **i207M**：“单调栈出栈条件写成>=而非>，调试2小时”——边界条件需严谨验证。
- **hegm**：“笛卡尔树方法复杂度分析错误，重写后AC”——提醒算法选择需结合数据特性。
- **白简**：“逐行切割时忘记更新剩余和，导致死循环”——状态维护是关键。

---

### 可视化与算法演示设计

**复古像素风格设计**：
- **Canvas绘制**：矩阵以16x16像素块表示，色码区分元素值（绿: <k, 红: >2k, 黄: [k,2k]）。
- **动画流程**：
  1. **悬线法扩展**：高亮当前行与列扩展过程，播放“滴”声。
  2. **切割演示**：红色激光线划过被切割行列，触发“咔嚓”音效。
  3. **成功反馈**：找到解时矩阵闪烁，播放8-bit胜利音乐。

**交互功能**：
- **步进控制**：空格暂停/继续，方向键调整速度。
- **AI自动模式**：自动执行切割逻辑，用户可观察决策路径。

**代码片段（JS）**：
```javascript
// 绘制矩阵
ctx.fillStyle = colorMap[val];
ctx.fillRect(x*16, y*16, 16, 16);
// 切割动画
function animateCut(dir, pos) {
    playSound('laser');
    drawLine(dir, pos, 'red');
}
```

---

### 核心代码实现（kczno1悬线法）

```cpp
// 悬线法预处理
rep(i,1,n) rep(j,1,n) {
    if(a[i][j] <= 2*k) up[j]++;
    else up[j] = 0;
    while(top && up[st[top]] >= up[j]) {
        // 计算子矩阵和并切割
        ...
    }
    st[++top] = j;
}

// 贪心切割
while(S(li, lj, ri, rj) > 2*k) {
    if (当前行超限) li++;
    else lj++; // 列切割
}
printf("%d %d %d %d", lj+1, li+1, rj, ri);
```

---
处理用时：94.94秒