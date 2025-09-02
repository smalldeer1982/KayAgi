# 题目信息

# [USACO08FEB] Hotel G

## 题目描述

The cows are journeying north to Thunder Bay in Canada to gain cultural enrichment and enjoy a vacation on the sunny shores of Lake Superior. Bessie, ever the competent travel agent, has named the Bullmoose Hotel on famed Cumberland Street as their vacation residence. This immense hotel has N (1 ≤ N ≤ 50,000) rooms all located on the same side of an extremely long hallway (all the better to see the lake, of course).

The cows and other visitors arrive in groups of size Di (1 ≤ Di ≤ N) and approach the front desk to check in. Each group i requests a set of Di contiguous rooms from Canmuu, the moose staffing the counter. He assigns them some set of consecutive room numbers r..r+Di-1 if they are available or, if no contiguous set of rooms is available, politely suggests alternate lodging. Canmuu always chooses the value of r to be the smallest possible.

Visitors also depart the hotel from groups of contiguous rooms. Checkout i has the parameters Xi and Di which specify the vacating of rooms Xi ..Xi +Di-1 (1 ≤ Xi ≤ N-Di+1). Some (or all) of those rooms might be empty before the checkout.

Your job is to assist Canmuu by processing M (1 ≤ M < 50,000) checkin/checkout requests. The hotel is initially unoccupied.

第一行输入 $n,m$，$n$ 代表有 $n$ 个房间 $(1\leq n \leq 50,000)$，编号为 $1 \sim n$，开始都为空房，$m$ 表示以下有 $m$ 行操作 $(1\leq m < 50,000)$，以下每行先输入一个数 $i$ ，表示一种操作：

若 $i$ 为 $1$，表示查询房间，再输入一个数 $x$，表示在 $1,2,...,n$ 房间中找到长度为 $x$ 的连续空房，输出连续 $x$ 个房间中左端的房间号，尽量让这个房间号最小，若找不到长度为 $x$ 的连续空房，输出 $0$。若找得到，在这 $x$ 个空房间中住上人。

若 $i$ 为 $2$，表示退房，再输入两个数 $x,y$ 代表房间号 $x \sim x+y-1$ 退房，即让房间为空。

你需要对每个输入 $1$ 输出对应的答案。

## 样例 #1

### 输入

```
10 6
1 3
1 3
1 3
1 3
2 5 5
1 6
```

### 输出

```
1
4
7
0
5
```

# AI分析结果



## 唯一算法分类
线段树

## 综合分析与结论
### 核心算法流程
1. **数据结构设计**：每个线段树节点维护四个关键属性：
   - `sum`：区间最大连续空房长度
   - `lmax`：左端点起始的最大连续空房长度
   - `rmax`：右端点起始的最大连续空房长度
   - `lazy`：懒标记（0-无标记，1-占用标记，2-清空标记）

2. **区间合并逻辑**：
   - 父节点的`lmax`取左子节点的`lmax`，若左子全空则加上右子`lmax`
   - 父节点的`rmax`取右子节点的`rmax`，若右子全空则加上左子`rmax`
   - 父节点的`sum`取三者最大值：左子`sum`、右子`sum`、左子`rmax`+右子`lmax`

3. **查询策略**：
   - 优先检查左子树能否容纳目标长度
   - 其次判断左右子交界处的合并长度是否满足
   - 最后检查右子树

### 可视化设计思路
**动画演示**：
1. **房间状态**：用颜色区分空房（绿色）和占用（红色），线段树节点以树状图展示，动态更新`sum/lmax/rmax`数值
2. **操作高亮**：
   - 查询时，按左→中→右顺序闪烁对应区间
   - 更新时，用流动光效标记被修改的连续房间区间
3. **数据流动**：线段树节点间的合并操作以箭头连线动态显示，重点展示`lmax/rmax`的拼接过程

**复古像素风格**：
- 采用8-bit风格调色板（翠绿#00FF00表空房，暗红#8B0000表占用）
- 线段树节点用16x16像素块表示，关键数值以迷你数字显示
- 音效设计：查询成功时播放FC游戏《超级马里奥》金币音效，更新操作时播放经典"blip"音效

## 题解清单（≥4星）
1. **Chemist（5星）**
   - 亮点：变量命名清晰，详细注释合并逻辑，代码可读性极佳
   - 关键代码片段：
     ```cpp
     void renew(int p) { // 区间合并核心逻辑
         if(t[p*2].sum == t[p*2].len) 
             t[p].lmax = t[p*2].len + t[p*2+1].lmax;
         else t[p].lmax = t[p*2].lmax;
         // 类似处理rmax...
         t[p].sum = max(max(t[p*2].sum, t[p*2+1].sum), 
                      t[p*2].rmax + t[p*2+1].lmax);
     }
     ```

2. **Owen_codeisking（4.5星）**
   - 亮点：代码高度简洁，利用三目运算符优化合并判断
   - 特色：通过宏定义简化节点属性访问，适合竞赛快速编码

3. **amstar（4星）**
   - 亮点：完整展示查询时的三种情况判断顺序，调试日志便于理解

## 核心代码实现
**线段树查询函数**：
```cpp
int query(int rt, int l, int r, int len) {
    if(segTree[rt].max < len) return 0;
    if(l == r) return l;
    pushDown(rt); // 下传懒标记
    int mid = (l + r) >> 1;
    if(segTree[rt<<1].max >= len) 
        return query(rt<<1, l, mid, len);
    if(segTree[rt<<1].rmax + segTree[rt<<1|1].lmax >= len)
        return mid - segTree[rt<<1].rmax + 1; // 跨左右子区间
    return query(rt<<1|1, mid+1, r, len);
}
```

## 相似题目推荐
1. **P2572 [SCOI2010] 序列操作**  
   （区间赋值/取反+连续1统计）
2. **P4145 上帝造题的七分钟2 / 花神游历各国**  
   （区间开平方+极值维护）
3. **P3373 【模板】线段树 2**  
   （双懒标记的区间修改）

## 可视化代码片段（Canvas演示）
```javascript
// 绘制线段树节点（像素风格）
function drawNode(x, y, node) {
  ctx.fillStyle = node.lazy ? "#8B0000" : "#00FF00"; // 红/绿色块
  ctx.fillRect(x, y, 16, 16); // 16x16像素块
  // 绘制sum/lmax/rmax数值
  drawText(x+2, y+12, node.sum.toString(), "white", 8); 
}
// 高亮查询路径
function highlightQuery(path) {
  path.forEach((pos, i) => {
    setTimeout(() => flashPixel(pos.x, pos.y), i*300); // 按步闪烁
  });
}
```

## 个人心得摘录
> **Chemist题解调试经验**：  
> "最初没处理左子全空的情况，导致合并时lmax计算错误。通过构造测试用例1-4-7序列发现bug，添加了左子sum等于len的判断条件。"  
> **启示**：边界条件测试至关重要，尤其是全空/全满的极端情况。

---
处理用时：75.76秒