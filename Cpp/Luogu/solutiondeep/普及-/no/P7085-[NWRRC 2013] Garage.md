# 题目信息

# [NWRRC 2013] Garage

## 题目描述



Wow! What a lucky day! Your company has just won a social contract for building a garage complex. Almost all formalities are done: contract payment is already transferred to your account.

So now it is the right time to read the contract. Okay, there is a sandlot in the form of $W \times H$ rectangle and you have to place some garages there. Garages are $w \times h$ rectangles and their edges must be parallel to the corresponding edges of the sandlot (you may not rotate garages, even by $90^{◦}).$ The coordinates of garages may be non-integer.

You know that the economy must be economical, so you decided to place as few garages as possible. Unfortunately, there is an opposite requirement in the contract: placing maximum possible number of garages.

Now let's see how these requirements are checked. . . The plan is accepted if it is impossible to add a new garage without moving the other garages (the new garage must also have edges parallel to corresponding sandlot edges).

![](https://www.acmicpc.net/upload/images2/garage.png)

Time is money, find the minimal number of garages that must be ordered, so that you can place them on the sandlot and there is no place for an extra garage.



## 说明/提示

Time limit: 2 s, Memory limit: 256 MB. 



## 样例 #1

### 输入

```
11 4 3 2
```

### 输出

```
2
```

## 样例 #2

### 输入

```
10 8 3 4
```

### 输出

```
2
```

## 样例 #3

### 输入

```
15 7 4 2
```

### 输出

```
4
```

# AI分析结果

### 算法分类
数学

### 综合分析与结论
题目要求在给定的矩形区域内放置尽可能少的车库，且无法再放置更多的车库。核心思路是通过数学计算确定水平和垂直方向上最多能放置的车库数量，并确保两个车库之间的距离小于车库的尺寸，从而无法再放置更多的车库。所有题解均基于这一思路，但在具体实现上有所不同。

### 所选题解
1. **作者：CGDGAD (5星)**
   - **关键亮点**：通过数学公式直接计算水平和垂直方向上的车库数量，代码简洁且高效。
   - **核心实现思想**：使用`ceil`函数计算水平和垂直方向上的车库数量，确保两个车库之间的距离小于车库的尺寸。
   - **代码片段**：
     ```cpp
     int a = (int)ceil( (double)(W - w + 0.000001) / (double)(2 * w - 0.000001) );
     int b = (int)ceil( (double)(H - h + 0.000001) / (double)(2 * h - 0.000001) );
     printf("%d\n", a * b);
     ```

2. **作者：朱屹涵2008 (4星)**
   - **关键亮点**：通过自定义函数`solve`计算水平和垂直方向上的车库数量，代码结构清晰。
   - **核心实现思想**：使用`ceil`函数计算水平和垂直方向上的车库数量，确保两个车库之间的距离小于车库的尺寸。
   - **代码片段**：
     ```cpp
     int solve(int X,int x){ 
         int num=ceil((double)(X-(x-MIN))/((double)(x*2)-MIN)); 
         return num;
     }
     cout<<solve(W,w)*solve(H,h);
     ```

3. **作者：E1_de5truct0r (4星)**
   - **关键亮点**：通过数学公式直接计算水平和垂直方向上的车库数量，代码简洁且高效。
   - **核心实现思想**：使用`ceil`函数计算水平和垂直方向上的车库数量，确保两个车库之间的距离小于车库的尺寸。
   - **代码片段**：
     ```cpp
     int K=ceil((A-a+0.001)/(2*a)),C=ceil((B-b+0.001)/(2*b)); 
     cout<<K*C;
     ```

### 最优关键思路或技巧
- **数学计算**：通过数学公式直接计算水平和垂直方向上的车库数量，确保两个车库之间的距离小于车库的尺寸。
- **代码简洁**：使用`ceil`函数和简单的数学公式，代码简洁且高效。

### 可拓展之处
- **类似问题**：可以扩展到其他几何图形的最优放置问题，如圆形、三角形等。
- **算法套路**：类似的最优化问题可以通过数学计算和贪心算法来解决。

### 推荐题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)
3. [P1064 金明的预算方案](https://www.luogu.com.cn/problem/P1064)

---
处理用时：23.12秒