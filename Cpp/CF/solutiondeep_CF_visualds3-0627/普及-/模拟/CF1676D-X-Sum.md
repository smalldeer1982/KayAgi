# 题目信息

# X-Sum

## 题目描述

Timur's grandfather gifted him a chessboard to practice his chess skills. This chessboard is a grid $ a $ with $ n $ rows and $ m $ columns with each cell having a non-negative integer written on it.

Timur's challenge is to place a bishop on the board such that the sum of all cells attacked by the bishop is maximal. The bishop attacks in all directions diagonally, and there is no limit to the distance which the bishop can attack. Note that the cell on which the bishop is placed is also considered attacked. Help him find the maximal sum he can get.

## 说明/提示

For the first test case here the best sum is achieved by the bishop being in this position:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1676D/ef38eda1ec7208a8243b8f6ac83d0d9df8a29fbb.png)

## 样例 #1

### 输入

```
4
4 4
1 2 2 1
2 4 2 4
2 2 3 1
2 4 2 4
2 1
1
0
3 3
1 1 1
1 1 1
1 1 1
3 3
0 1 1
1 0 1
1 1 0```

### 输出

```
20
1
5
3```

# AI分析结果



# 算法分类
预处理与数学观察

---

## 题解思路与解决难点
### 核心思路
象的攻击范围由两条正交对角线构成。通过数学观察发现：
1. 左上-右下对角线上的点满足 `i+j` 相等
2. 右上-左下对角线上的点满足 `i-j` 相等（需加偏移量防负数）

### 解决难点
- **坐标映射**：将二维坐标转换为一维对角线的索引
- **重复计算**：象所在点会被两个对角线各计算一次，需减去一次自身值
- **时间复杂度**：暴力解法O(nm*(n+m))存在超时风险，预处理法O(nm)显著优化

### 最优解法步骤
1. 预处理两个数组`l[i+j]`和`r[i-j+m]`，记录每条对角线数值总和
2. 遍历每个点计算 `l[i+j] + r[i-j+m] - a[i][j]`
3. 取最大值即为答案

---

## 题解评分
### 5k_sync_closer（★★★★★）
- **亮点**：代码简洁高效，时间复杂度最优
- **关键代码**：预处理对角线和，双数组并行计算
```cpp
for(int i=1;i<=n;++i)
    for(int j=1;j<=m;++j)
        l[i+j] += a[i][j], r[i-j+m] += a[i][j];
```

### Rosemary_dream（★★★★☆）
- **亮点**：详细图示解释坐标规律，教学性强
- **代码特点**：变量命名直观，偏移处理清晰
```cpp
L[i+j] += p[i][j];  // 左上-右下对角线
R[i-j+m] += p[i][j];// 右上-左下对角线
```

### Mr__Cat（★★★★）
- **亮点**：使用map处理负数偏移，思维新颖
- **技巧**：通过映射避免数组越界，代码适应性高
```cpp
map<int,int> l,r;  // 处理i-j可能为负数的情况
```

---

## 最优思路提炼
**关键技巧**：  
- 将二维坐标转换为一维对角线和索引  
- **i+j** 标识左上-右下对角线  
- **i-j+m** 标识右上-左下对角线（m为列偏移）  
- 通过预处理将时间复杂度从O(n³)降至O(n²)

---

## 同类题目推荐
1. [洛谷P1219 八皇后](https://www.luogu.com.cn/problem/P1219)  
   （斜线攻击范围检测）
2. [CF1353E 交替路径](https://codeforces.com/problemset/problem/1353/E)  
   （对角线动态规划）
3. [洛谷P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)  
   （二维预处理+数学观察）

---

## 个人心得摘录
> "调试中发现对角线方向容易混淆，通过画图验证坐标规律是突破口" —— Rosemary_dream  
> "预处理数组大小需要仔细计算，否则会RE" —— 5k_sync_closer

---

## 可视化算法演示
### 核心流程动画
1. **棋盘绘制**：像素风格棋盘，每个格子显示数值
2. **对角线高亮**：点击任意格子时，用不同颜色标出两条对角线
3. **数值累加**：动态显示对角线上数值的累加过程
4. **最大值标记**：遍历过程中实时更新最大值，并用闪烁边框标记

### 复古风格设计
- **调色板**：8位红白机风格，使用#FF0000（红）、#00FF00（绿）、#0000FF（蓝）三基色
- **音效设计**：
  - 点击格子：8-bit "哔"声
  - 发现新最大值：上升音阶
  - 最终答案：经典FC通关音效
- **自动演示**：AI自动遍历所有格子，用贪吃蛇式移动展示计算过程

### 关键代码片段（Canvas动画）
```javascript
// 绘制对角线动画
function drawDiagonal(x, y) {
    ctx.strokeStyle = '#FF00FF'; // 紫色表示当前选中点
    // 左上-右下对角线（i+j=const）
    for(let i=0; i<n; i++) {
        let j = (x+y) - i;
        if(j >=0 && j <m) highlightCell(i,j);
    }
    // 右上-左下对角线（i-j=const）
    const offset = x - y + m;
    for(let i=0; i<n; i++) {
        let j = i - offset + m;
        if(j >=0 && j <m) highlightCell(i,j);
    }
}
```

---

## 总结
通过数学观察将二维问题转换为一维预处理，是解决网格类问题的经典思路。结合像素动画与音效反馈，可将抽象的坐标规律转化为直观的视觉体验，特别适合教学演示场景。

---
处理用时：85.25秒