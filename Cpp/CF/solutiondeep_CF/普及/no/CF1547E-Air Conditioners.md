# 题目信息

# Air Conditioners

## 题目描述

On a strip of land of length $ n $ there are $ k $ air conditioners: the $ i $ -th air conditioner is placed in cell $ a_i $ ( $ 1 \le a_i \le n $ ). Two or more air conditioners cannot be placed in the same cell (i.e. all $ a_i $ are distinct).

Each air conditioner is characterized by one parameter: temperature. The $ i $ -th air conditioner is set to the temperature $ t_i $ .

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1547E/cf6634601d8b404820c7eae42e10e4cc87878a8e.png)Example of strip of length $ n=6 $ , where $ k=2 $ , $ a=[2,5] $ and $ t=[14,16] $ .For each cell $ i $ ( $ 1 \le i \le n $ ) find it's temperature, that can be calculated by the formula $ $$$\min_{1 \le j \le k}(t_j + |a_j - i|), $ $ </p><p>where  $ |a\_j - i| $  denotes absolute value of the difference  $ a\_j - i $ .</p><p>In other words, the temperature in cell  $ i $  is equal to the minimum among the temperatures of air conditioners, increased by the distance from it to the cell  $ i $ .</p><p>Let's look at an example. Consider that  $ n=6, k=2 $ , the first air conditioner is placed in cell  $ a\_1=2 $  and is set to the temperature  $ t\_1=14 $  and the second air conditioner is placed in cell  $ a\_2=5 $  and is set to the temperature  $ t\_2=16 $ . In that case temperatures in cells are:</p><ol> <li> temperature in cell  $ 1 $  is:  $ \\min(14 + |2 - 1|, 16 + |5 - 1|)=\\min(14 + 1, 16 + 4)=\\min(15, 20)=15 $ ; </li><li> temperature in cell  $ 2 $  is:  $ \\min(14 + |2 - 2|, 16 + |5 - 2|)=\\min(14 + 0, 16 + 3)=\\min(14, 19)=14 $ ; </li><li> temperature in cell  $ 3 $  is:  $ \\min(14 + |2 - 3|, 16 + |5 - 3|)=\\min(14 + 1, 16 + 2)=\\min(15, 18)=15 $ ; </li><li> temperature in cell  $ 4 $  is:  $ \\min(14 + |2 - 4|, 16 + |5 - 4|)=\\min(14 + 2, 16 + 1)=\\min(16, 17)=16 $ ; </li><li> temperature in cell  $ 5 $  is:  $ \\min(14 + |2 - 5|, 16 + |5 - 5|)=\\min(14 + 3, 16 + 0)=\\min(17, 16)=16 $ ; </li><li> temperature in cell  $ 6 $  is:  $ \\min(14 + |2 - 6|, 16 + |5 - 6|)=\\min(14 + 4, 16 + 1)=\\min(18, 17)=17 $ . </li></ol><p>For each cell from  $ 1 $  to  $ n$$$ find the temperature in it.

## 样例 #1

### 输入

```
5

6 2
2 5
14 16

10 1
7
30

5 5
3 1 4 2 5
3 1 4 2 5

7 1
1
1000000000

6 3
6 1 3
5 5 5```

### 输出

```
15 14 15 16 16 17 
36 35 34 33 32 31 30 31 32 33 
1 2 3 4 5 
1000000000 1000000001 1000000002 1000000003 1000000004 1000000005 1000000006 
5 6 5 6 6 5```

# AI分析结果

### 题目内容重写

**题目描述**

在一条长度为 $n$ 的土地上，有 $k$ 台空调：第 $i$ 台空调位于单元格 $a_i$（$1 \le a_i \le n$）。两台或更多空调不能放在同一个单元格中（即所有 $a_i$ 都是不同的）。

每台空调都有一个参数：温度。第 $i$ 台空调的温度设置为 $t_i$。

对于每个单元格 $i$（$1 \le i \le n$），其温度可以通过以下公式计算：

$$ \min_{1 \le j \le k}(t_j + |a_j - i|) $$

其中 $|a_j - i|$ 表示 $a_j - i$ 的绝对值。

换句话说，单元格 $i$ 的温度等于所有空调的温度加上其到该单元格的距离的最小值。

**样例**

输入：

```
5

6 2
2 5
14 16

10 1
7
30

5 5
3 1 4 2 5
3 1 4 2 5

7 1
1
1000000000

6 3
6 1 3
5 5 5
```

输出：

```
15 14 15 16 16 17 
36 35 34 33 32 31 30 31 32 33 
1 2 3 4 5 
1000000000 1000000001 1000000002 1000000003 1000000004 1000000005 1000000006 
5 6 5 6 6 5
```

### 算法分类

动态规划

### 题解分析与结论

本题的核心是通过动态规划（DP）来优化计算每个单元格的温度。大部分题解都采用了类似的思路：首先初始化所有单元格的温度为无穷大，然后根据空调的位置和温度进行初始化。接着，通过从左到右和从右到左两次遍历，更新每个单元格的温度，确保其温度是其左右相邻单元格温度的最小值加1。

### 所选高分题解

#### 题解1：Gokix (5星)

**关键亮点：**
- 简洁明了的DP思路，通过两次遍历（从左到右和从右到左）来更新温度。
- 代码简洁，易于理解和实现。

**核心代码：**
```cpp
for(i=2;i<=n;i++) f[i]=min(f[i],f[i-1]+1);
for(i=n-1;i>=1;i--) f[i]=min(f[i],f[i+1]+1);
```

#### 题解2：xuanyuan_Niubi (4星)

**关键亮点：**
- 详细解释了DP的转移过程，强调了从左到右和从右到左两次遍历的必要性。
- 代码清晰，注释详细。

**核心代码：**
```cpp
for(int i=2;i<=n;i++)c[i]=min(c[i],c[i-1]+1);
for(int i=n-1;i>=1;i--)c[i]=min(c[i],c[i+1]+1);
```

#### 题解3：_ajthreac_ (4星)

**关键亮点：**
- 通过分类讨论消除绝对值，简化了问题。
- 使用前后缀最小值来优化计算。

**核心代码：**
```cpp
for(rg int i=1;i<=n;i++)L[i]=min(L[i-1],L[i]);
for(rg int i=n;i>=1;i--)R[i]=min(R[i+1],R[i]);
```

### 最优关键思路

1. **初始化**：将所有单元格的温度初始化为无穷大，然后将空调所在单元格的温度设置为空调的温度。
2. **DP转移**：通过从左到右和从右到左两次遍历，更新每个单元格的温度，确保其温度是其左右相邻单元格温度的最小值加1。

### 可拓展之处

这种通过两次遍历来更新状态的DP思路可以应用于其他类似的问题，例如在网格中计算最短路径或最小成本等问题。

### 推荐题目

1. [P1091 合唱队形](https://www.luogu.com.cn/problem/P1091)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1216 [USACO1.5]数字三角形 Number Triangles](https://www.luogu.com.cn/problem/P1216)

---
处理用时：28.47秒