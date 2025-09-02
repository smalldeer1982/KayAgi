# 题目信息

# Black Square

## 题目描述

Polycarp has a checkered sheet of paper of size $ n×m $ . Polycarp painted some of cells with black, the others remained white. Inspired by Malevich's "Black Square", Polycarp wants to paint minimum possible number of white cells with black so that all black cells form a square.

You are to determine the minimum possible number of cells needed to be painted black so that the black cells form a black square with sides parallel to the painting's sides. All the cells that do not belong to the square should be white. The square's side should have positive length.

## 说明/提示

In the first example it is needed to paint $ 5 $ cells — $ (2,2) $ , $ (2,3) $ , $ (3,2) $ , $ (3,3) $ and $ (4,2) $ . Then there will be a square with side equal to three, and the upper left corner in $ (2,2) $ .

In the second example all the cells are painted black and form a rectangle, so it's impossible to get a square.

In the third example all cells are colored white, so it's sufficient to color any cell black.

## 样例 #1

### 输入

```
5 4
WWWW
WWWB
WWWB
WWBB
WWWW
```

### 输出

```
5
```

## 样例 #2

### 输入

```
1 2
BB
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
3 3
WWW
WWW
WWW
```

### 输出

```
1
```

# AI分析结果



### 中文题目重写
# 黑色正方形

## 题目描述

波利卡普有一张 $n×m$ 的方格纸，部分格子被涂成黑色，其余为白色。受马列维奇《黑色正方形》启发，他希望通过涂黑最少的白色格子，使得所有黑色格子构成一个边平行于纸张的正方形。

请计算最少需要涂黑的格子数。若无解输出 $-1$，注意正方形边长必须为正数。

## 样例 #1

### 输入
```
5 4
WWWW
WWWB
WWWB
WWBB
WWWW
```

### 输出
```
5
```

## 样例 #2

### 输入
```
1 2
BB
```

### 输出
```
-1
```

## 样例 #3

### 输入
```
3 3
WWW
WWW
WWW
```

### 输出
```
1
```

---

### 算法分类
模拟

---

### 题解对比与结论

#### 核心思路
所有题解均采用以下步骤：
1. **极值记录**：遍历记录所有黑格子的最小/最大行、列坐标
2. **边长计算**：正方形边长取行跨度与列跨度的最大值
3. **可行性验证**：若边长超过网格尺寸则无解
4. **特例处理**：无黑格时需涂1个格子

#### 最优题解亮点

1. **坐标极值法**（_Starlit__Sky_，5星）
   - 清晰分离行列极值计算
   - 完整处理边界条件和特例
   - 代码注释详细，逻辑可读性强

2. **极值压缩计算**（pyz51，4星）
   - 代码简洁，变量命名有优化空间
   - 通过单次遍历完成极值记录

3. **四角极值法**（rain_dew，4星）
   - 使用明确变量名 min_row/max_row
   - 流程图辅助说明增强理解

---

### 关键代码实现
```python
# 极值记录与计算（_Starlit__Sky_ 解法核心）
min_col = min_x = float('inf')
max_col = max_x = -1
min_row = min_y = float('inf')
max_row = max_y = -1
cnt = 0

for i in range(n):
    for j in range(m):
        if grid[i][j] == 'B':
            min_col = min(min_col, j)
            max_col = max(max_col, j)
            min_row = min(min_row, i)
            max_row = max(max_row, i)
            cnt += 1

side = max(max_col - min_col + 1, max_row - min_row + 1)
if cnt == 0:
    print(1)
elif side > max(n, m):
    print(-1)
else:
    print(side * side - cnt)
```

---

### 拓展思考
1. **极值计算模式**：类似问题常见于包围盒计算（如碰撞检测）
2. **动态规划变式**：若要求最大全黑正方形可参考洛谷 P1387
3. **多维扩展**：三维空间中的最小包围立方体问题

---

### 推荐练习
1. [P1387 最大正方形](https://www.luogu.com.cn/problem/P1387)  
   （动态规划求最大全1正方形）

2. [P2742 圈奶牛](https://www.luogu.com.cn/problem/P2742)  
   （计算包围所有点的最小周长）

3. [P2216 理想的正方形](https://www.luogu.com.cn/problem/P2216)  
   （二维滑动窗口极值处理）

---
处理用时：232.87秒