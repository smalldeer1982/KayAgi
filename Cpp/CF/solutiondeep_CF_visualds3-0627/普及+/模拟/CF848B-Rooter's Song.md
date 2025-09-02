# 题目信息

# Rooter's Song

## 题目描述

Wherever the destination is, whoever we meet, let's render this song together.

On a Cartesian coordinate plane lies a rectangular stage of size $ w×h $ , represented by a rectangle with corners $ (0,0) $ , $ (w,0) $ , $ (w,h) $ and $ (0,h) $ . It can be seen that no collisions will happen before one enters the stage.

On the sides of the stage stand $ n $ dancers. The $ i $ -th of them falls into one of the following groups:

- Vertical: stands at $ (x_{i},0) $ , moves in positive $ y $ direction (upwards);
- Horizontal: stands at $ (0,y_{i}) $ , moves in positive $ x $ direction (rightwards).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/78a4617a270ecba0555a87f4deb825cf1f501330.png)According to choreography, the $ i $ -th dancer should stand still for the first $ t_{i} $ milliseconds, and then start moving in the specified direction at $ 1 $ unit per millisecond, until another border is reached. It is guaranteed that no two dancers have the same group, position and waiting time at the same time.

When two dancers collide (i.e. are on the same point at some time when both of them are moving), they immediately exchange their moving directions and go on.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/14a342567b0e0e96e2854bafb4e39a8b293ebae4.png)Dancers stop when a border of the stage is reached. Find out every dancer's stopping position.

## 说明/提示

The first example corresponds to the initial setup in the legend, and the tracks of dancers are marked with different colours in the following figure.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF848B/d441e2a826ff927d107333215574de12d2f00a07.png)In the second example, no dancers collide.

## 样例 #1

### 输入

```
8 10 8
1 1 10
1 4 13
1 7 1
1 8 2
2 2 0
2 5 14
2 6 0
2 6 1
```

### 输出

```
4 8
10 5
8 8
10 6
10 2
1 8
7 8
10 6
```

## 样例 #2

### 输入

```
3 2 3
1 1 2
2 1 1
1 1 5
```

### 输出

```
1 3
2 1
1 3
```

# AI分析结果



---

## 唯一算法分类  
**数学建模 + 排序分组**

---

## 综合分析与结论  
### 核心思路与难点  
1. **碰撞条件推导**：通过分析发现，相撞的必要条件是 \( p_i - t_i = p_j - t_j \)，其中 \( p_i \) 为垂直舞者的 \( x \) 或水平舞者的 \( y \)。  
2. **分组处理**：将满足 \( p_i - t_i = \text{const} \) 的舞者划为同一组，不同组之间无碰撞可能。  
3. **排序对应**：同一组内，垂直和水平舞者的路径交点顺序固定，通过排序起点和终点实现一一映射，避免模拟碰撞。  

### 算法流程  
1. **分组**：以 \( p_i - t_i \) 为键将舞者分组。  
2. **终点计算**：垂直舞者终点为 \( (x, h) \)，水平舞者终点为 \( (w, y) \)。  
3. **排序对应**：  
   - 垂直舞者按 \( x \) 从小到大排序，对应终点按 \( (x, h) \)。  
   - 水平舞者按 \( y \) 从小到大排序，对应终点按 \( (w, y) \)。  
   - 合并所有终点并按 \( y \) 降序、\( x \) 升序排序，与起点排序后的舞者一一对应。  

### 可视化设计  
- **动画方案**：  
  1. **分组染色**：不同组用不同颜色区分，同一组内垂直/水平路径用箭头表示。  
  2. **排序过程**：动态展示起点和终点的排序，用连线表示对应关系。  
  3. **碰撞模拟**：高亮碰撞点，播放“交换”音效，显示最终位置。  
- **复古风格**：  
  - **像素舞台**：用 8-bit 色块表示舞台边界，舞者为移动像素点。  
  - **音效设计**：碰撞时播放短促电子音，终点到达时播放上扬音效。  
  - **控制面板**：支持暂停/步进，调整分组显示和排序动画速度。  

---

## 题解清单（≥4星）  
1. **zyctc（5星）**  
   - **亮点**：代码简洁，统一排序所有终点实现对应，逻辑清晰。  
   - **关键代码**：  
     ```cpp  
     sort(d[k].begin(), d[k].end());  
     sort(p.begin(), p.end());  
     for(int i=0;i<d[k].size();i++) ans[d[k][i].id]=p[i];  
     ```  
2. **moye到碗里来（4星）**  
   - **亮点**：通过数量关系直接判断终点类型，数学推导深入。  
   - **关键代码**：  
     ```cpp  
     if(sz1 - j -1 >= sz2) ans[...] = vertical_end;  
     else ans[...] = horizontal_end;  
     ```  

---

## 最优思路提炼  
1. **分组条件**：利用 \( p_i - t_i \) 分组，避免无效碰撞计算。  
2. **排序对应**：同一组内起点和终点按固定规则排序后直接映射，复杂度 \( O(n \log n) \)。  
3. **几何观察**：路径交点顺序不变性，确保排序后终点正确对应。  

---

## 同类题目推荐  
1. **P1007 独木桥**（蚂蚁相撞问题）  
2. **CF650C Table Compression**（坐标离散化与排序）  
3. **P1365 均分纸牌**（数学建模与分组策略）  

---

## 个人心得摘录  
> “在碰撞处理中卡了很久，画图后发现同一组的路径交点顺序固定，才想到排序对应法。” —— moye到碗里来  

---

## 代码核心实现  
```cpp  
// zyctc 题解核心片段  
for(auto k:dif) {  
    p.clear();  
    for(auto i:d[k]) {  
        if(!i.y) p.pb((node){i.x, Y, 0});  
        else p.pb((node){X, i.y, 0});  
    }  
    sort(d[k].begin(), d[k].end());  
    sort(p.begin(), p.end());  
    for(int i=0;i<d[k].size();i++) ans[d[k][i].id]=p[i];  
}  
```  

---

## 可视化关键逻辑  
```javascript  
// 伪代码：Canvas绘制舞者路径  
function drawGroup(group) {  
    group.dancers.forEach(dancer => {  
        ctx.fillStyle = dancer.type === 'vertical' ? '#FF0000' : '#00FF00';  
        ctx.fillRect(dancer.startX, dancer.startY, 5, 5);  
        drawArrow(dancer.start, dancer.end);  
    });  
    group.endPoints.sort().forEach((end, i) => {  
        drawLine(group.dancers[i].start, end);  
    });  
}  
```  

--- 

**总结**：通过数学推导将碰撞问题转化为排序分组，避免暴力模拟，是本题最优解法。

---
处理用时：136.59秒