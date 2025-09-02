# 题目信息

# Exact Neighbours (Medium)

## 题目描述

The only difference between this and the hard version is that $ a_{1} = 0 $ .

After some recent attacks on Hogwarts Castle by the Death Eaters, the Order of the Phoenix has decided to station $ n $ members in Hogsmead Village. The houses will be situated on a picturesque $ n\times n $ square field. Each wizard will have their own house, and every house will belong to some wizard. Each house will take up the space of one square.

However, as you might know wizards are very superstitious. During the weekends, each wizard $ i $ will want to visit the house that is exactly $ a_{i} $ $ (0 \leq a_{i} \leq n) $ away from their own house. The roads in the village are built horizontally and vertically, so the distance between points $ (x_{i}, y_{i}) $ and $ (x_{j}, y_{j}) $ on the $ n\times n $ field is $  |x_{i} - x_{j}| + |y_{i} - y_{j}| $ . The wizards know and trust each other, so one wizard can visit another wizard's house when the second wizard is away. The houses to be built will be big enough for all $ n $ wizards to simultaneously visit any house.

Apart from that, each wizard is mandated to have a view of the Hogwarts Castle in the north and the Forbidden Forest in the south, so the house of no other wizard should block the view. In terms of the village, it means that in each column of the $ n\times n $ field, there can be at most one house, i.e. if the $ i $ -th house has coordinates $ (x_{i}, y_{i}) $ , then $ x_{i} \neq x_{j} $ for all $ i \neq j $ .

The Order of the Phoenix doesn't yet know if it is possible to place $ n $ houses in such a way that will satisfy the visit and view requirements of all $ n $ wizards, so they are asking for your help in designing such a plan.

If it is possible to have a correct placement, where for the $ i $ -th wizard there is a house that is $ a_{i} $ away from it and the house of the $ i $ -th wizard is the only house in their column, output YES, the position of houses for each wizard, and to the house of which wizard should each wizard go during the weekends.

If it is impossible to have a correct placement, output NO.

## 说明/提示

For the sample, the house of the 1st wizard is located at $ (4, 4) $ , of the 2nd at $ (1, 3) $ , of the 3rd at $ (2, 4) $ , of the 4th at $ (3, 1) $ .

The distance from the house of the 1st wizard to the house of the 1st wizard is $ |4 - 4| + |4 - 4| = 0 $ .

The distance from the house of the 2nd wizard to the house of the 1st wizard is $ |1 - 4| + |3 - 4| = 4 $ .

The distance from the house of the 3rd wizard to the house of the 1st wizard is $ |2 - 4| + |4 - 4| = 2 $ .

The distance from the house of the 4th wizard to the house of the 3rd wizard is $ |3 - 2| + |1 - 4| = 4 $ .

The view and the distance conditions are satisfied for all houses, so the placement is correct.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1970B2/9f9f415b711c20a1d43262d4b959c18fec467842.png)

## 样例 #1

### 输入

```
4
0 4 2 4```

### 输出

```
YES
4 4
1 3
2 4
3 1
1 1 1 3```

## 样例 #2

### 输入

```
4
0 1 3 1```

### 输出

```
YES
1 1
2 1
4 1
3 1
1 1 1 3```

# AI分析结果



**唯一算法分类**：构造

---

### **综合分析与结论**

1. **题目核心**  
   构造一个满足每列仅一个房子且每个巫师i的访问距离恰好为a_i的布局。中等难度中a₁=0，简化了构造起点。

2. **核心思路**  
   - **锚点构造**：将第一个房子放在（1,1），作为后续构造的锚点。  
   - **分情况讨论**：对每个i≥2的巫师，根据a_i的大小选择目标：  
     - **a_i较大**：以第一个房子为目标，通过调整行数满足距离。  
     - **a_i较小**：寻找前面的某个房子j，使得横向距离i-j恰好等于a_i，共享j的行数。  

3. **难点与解决**  
   - **列唯一性**：通过强制每列放置一个房子，保证约束。  
   - **距离验证**：分情况讨论，确保曼哈顿距离满足a_i。  
   - **坐标系转换**：部分题解需注意题目中坐标系的行列定义（如样例中的坐标可能是从下到上）。

---

### **题解清单 (≥4星)**

1. **0tAp (4星)**  
   - **亮点**：代码结构清晰，分情况处理三种情况（now=0、now>0、now<0），注释详细。  
   - **核心代码**：  
     ```cpp
     x[1] = 1, y[1] = 1;
     rep(i,2,n) {
         if (!a[i]) { x[i] = i, y[i] = 1; ans[i] = i; }
         int now = a[i] - i + 1;
         if (now == 0) { x[i] = i, y[i] = 1; ans[i] = 1; }
         else if (now > 0) { x[i] = i, y[i] = now + 1; ans[i] = 1; }
         else { x[i] = i, y[i] = y[-now + 1]; ans[i] = -now + 1; }
     }
     ```

2. **FFTotoro (4星)**  
   - **亮点**：代码简洁，索引处理灵活（从0开始），逻辑直击核心。  
   - **核心代码**：  
     ```cpp
     if (a[i] >= i) { row = a[i] - i + 1; target = 0; }
     else { j = i - a[i]; row = row_of_j; target = j; }
     ```

3. **I_am_Tangser (4星)**  
   - **亮点**：明确坐标系转换，处理行数调整。  
   - **注意**：需验证坐标系是否与样例一致。  
   - **核心代码**：  
     ```cpp
     if (a[i] >= i) { y[i] = a[i] - i + 2; }
     else { y[i] = y[i - a[i]]; }
     ```

---

### **最优思路提炼**

- **锚点法**：利用a₁=0的特性，固定第一个房子的位置，简化后续构造。  
- **贪心分治**：根据a_i的大小动态选择目标，大则锚定首房，小则横向匹配。  
- **行列分离**：通过列唯一性约束，独立处理行数，避免冲突。

---

### **同类型题与算法套路**

- **构造类**：需满足特定约束的排列或布局（如曼哈顿距离、唯一性）。  
- **贪心分治**：动态选择最优决策（如CF1328C、P1969）。  
- **曼哈顿距离拆分**：横向与纵向独立处理。

---

### **推荐题目**
1. **P1969**：积木大赛（构造递增序列）。  
2. **CF1328C**：Ternary XOR（构造满足条件的二进制数）。  
3. **P1056**：排座椅（贪心选择行列切割线）。

---

### **个人心得摘录**

- **坐标系陷阱**：注意题目中行列的定义方向（如样例可能从下到上）。  
- **索引处理**：从0或1开始需统一，避免越界（如FFTotoro题解中的灵活处理）。  
- **构造验证**：分情况讨论需覆盖所有可能性，确保数学推导正确。

---

### **可视化与算法演示**

1. **动画设计**：  
   - **网格绘制**：在Canvas中绘制n×n网格，每列用不同颜色标记已放置的房子。  
   - **动态构造**：高亮当前处理的列，显示行数选择逻辑（如向上延伸或匹配已有行）。  
   - **目标连线**：用箭头动态显示当前房子与目标房子的连接，标出曼哈顿距离。  

2. **复古像素风格**：  
   - **8位音效**：放置房子时播放“放置音效”，成功时播放胜利音效。  
   - **颜色标记**：锚点房子用红色，其他用绿色，目标连线用黄色。  
   - **自动演示**：按构造顺序自动播放，支持暂停/步进观察细节。  

**关键代码片段（伪代码）**：  
```javascript
// 绘制网格
ctx.fillStyle = "#8B8B8B";
for (let i = 0; i < n; i++) {
    ctx.fillRect(i * cellSize, 0, 1, canvasHeight); // 列线
    ctx.fillRect(0, i * cellSize, canvasWidth, 1); // 行线
}

// 放置房子动画
function placeHouse(col, row, targetCol, targetRow) {
    drawHouse(col, row, "#00FF00");
    drawArrow(col, row, targetCol, targetRow);
    playSound("place.wav");
}
```

---

**总结**：通过锚点构造与贪心分治，结合曼哈顿距离的横向/纵向拆分，可高效解决此类构造问题。

---
处理用时：378.94秒