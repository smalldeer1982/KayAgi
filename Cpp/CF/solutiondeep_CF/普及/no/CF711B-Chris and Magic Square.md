# 题目信息

# Chris and Magic Square

## 题目描述

ZS the Coder and Chris the Baboon arrived at the entrance of Udayland. There is a $ n×n $ magic grid on the entrance which is filled with integers. Chris noticed that exactly one of the cells in the grid is empty, and to enter Udayland, they need to fill a positive integer into the empty cell.

Chris tried filling in random numbers but it didn't work. ZS the Coder realizes that they need to fill in a positive integer such that the numbers in the grid form a magic square. This means that he has to fill in a positive integer so that the sum of the numbers in each row of the grid (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711B/e9e8af3f495bde6f05bb15fe8a019d478bbc6918.png)), each column of the grid (![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711B/715dbd8d1021ddf349931cbf725fd485f986bf2d.png)), and the two long diagonals of the grid (the main diagonal — ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711B/141aae991a978e02f2d5b71795da24f641569581.png) and the secondary diagonal — ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF711B/0aa6adfaeb4cdadf568645c01154f2786989c40b.png)) are equal.

Chris doesn't know what number to fill in. Can you help Chris find the correct positive integer to fill in or determine that it is impossible?

## 说明/提示

In the first sample case, we can fill in $ 9 $ into the empty cell to make the resulting grid a magic square. Indeed,

The sum of numbers in each row is:

 $ 4+9+2=3+5+7=8+1+6=15 $ .

The sum of numbers in each column is:

 $ 4+3+8=9+5+1=2+7+6=15 $ .

The sum of numbers in the two diagonals is:

 $ 4+5+6=2+5+8=15 $ .

In the third sample case, it is impossible to fill a number in the empty square such that the resulting grid is a magic square.

## 样例 #1

### 输入

```
3
4 0 2
3 5 7
8 1 6
```

### 输出

```
9
```

## 样例 #2

### 输入

```
4
1 1 1 1
1 1 0 1
1 1 1 1
1 1 1 1
```

### 输出

```
1
```

## 样例 #3

### 输入

```
4
1 1 1 1
1 1 0 1
1 1 2 1
1 1 1 1
```

### 输出

```
-1
```

# AI分析结果



### 题目重写

# Chris和幻方

## 题目描述

ZS the Coder和Chris the Baboon来到Udayland的入口，这里有一个$n×n$的魔法网格，其中恰好有一个单元格是空的。他们需要在这个空单元格中填入一个正整数，使得网格中的数字构成一个幻方。

幻方的定义是：填入正整数后，网格每一行的数字之和、每一列的数字之和以及两条主对角线的数字之和都必须相等。

## 输入格式

第一行包含整数$n$，表示网格大小。  
接下来$n$行，每行$n$个整数，其中0表示空单元格。

## 输出格式

输出可填入的正整数，若无法构成幻方则输出-1。

## 样例

### 样例1输入
3  
4 0 2  
3 5 7  
8 1 6  
### 样例1输出
9

### 算法分类
构造

---

### 题解分析与结论

各题解核心思路一致：通过完整行确定幻和，计算填充值后验证全局。实现差异主要体现在验证逻辑的完整性：

1. **zhang_kevin（★★★★★）**
   - 亮点：双重验证机制（预检行/列差异 + 填充后全验证）
   - 代码结构清晰，处理了n=1特例，使用独立check函数验证
   - 关键代码：通过其他行确定幻和，计算填充值后重新计算行列和对角线和

2. **Nuclear_Fish_cyq（★★★★☆）**
   - 亮点：分离式验证逻辑，显式处理对角线包含0的情况
   - 缺点：缺少填充后的行和列二次验证
   - 关键代码：通过判断行列和对角线是否满足幻和进行验证

3. **___define___（★★★☆☆）**
   - 亮点：使用map统计合法和出现次数
   - 缺点：验证条件较为隐晦，可读性较差
   - 关键代码：通过统计合法和数量判断可行性

### 最优思路提炼

1. **确定幻和**：取任意完整行/列的和作为基准值
2. **计算填充值**：幻和 - 空行当前和
3. **全局验证**：
   - 填充后的所有行、列、对角线必须相等
   - 填充值必须为正整数
4. **特例处理**：n=1时直接返回1

### 核心代码实现

zhang_kevin的check函数核心逻辑：
```cpp
bool check(int ans) {
    Put_in(ans); // 填入计算结果
    // 验证对角线
    int d1 = 0, d2 = 0;
    for(int i=1; i<=n; i++) {
        d1 += a[i][i];
        d2 += a[i][n-i+1];
    }
    if(d1 != d2) return false;
    
    // 验证列和
    int col_sum[501] = {0};
    for(int j=1; j<=n; j++) 
        for(int i=1; i<=n; i++)
            col_sum[j] += a[i][j];
    for(int i=2; i<=n; i++)
        if(col_sum[i] != col_sum[i-1]) return false;
    
    // 验证行和
    int row_sum[501] = {0};
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
            row_sum[i] += a[i][j];
    for(int i=2; i<=n; i++)
        if(row_sum[i] != row_sum[i-1]) return false;
    
    return (d1 == row_sum[1] && row_sum[1] == col_sum[1]);
}
```

### 拓展建议

同类问题可考虑：
- 多空位填充问题（需要线性方程组求解）
- 非固定幻和问题（找规律构造）
- 三维幻方验证

### 推荐习题
1. P2615 幻方构造（NOIP2015 提高组）
2. P1476 魔板（USACO）
3. P2119 魔法阵（NOIP2016 普及组）

---
处理用时：62.19秒