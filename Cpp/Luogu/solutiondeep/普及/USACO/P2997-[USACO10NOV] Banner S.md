# 题目信息

# [USACO10NOV] Banner S

## 题目背景

题目大意(by:曹彦臣)：


平面上有(0,0)到(n,m)的(n+1)\*(m+1)个点。问有多少点对所连的线段不过其他点，且长度在[l,h]范围内。


## 题目描述

Bessie is returning from a long trip abroad, and Farmer John wants to erect a nice 'Welcome Home' banner in her pasture for her arrival. The banner will hang between two poles on a wire whose length is in the range L1..L2 (1 <= L1 <= L2; L1 <= L2 <= 1,500).

The pasture's size is W x H (1 <= W <= 1,000; 1 <= H <= 1,000), and Farmer John has installed a post at every point with integer

coordinates. Of these (W + 1) \* (H + 1) points, Farmer John must pick just two that will hold either end of the wire from which he will hang the banner.

FJ wants no interference with his banner as it hangs and requires that no post be directly under the tight wire he stretches between the two chosen posts.

Farmer John needs your help to figure out how many possible ways he can hang the banner. He knows the number is large and that a 32-bit integer might not be sufficient to compute the answer.

Consider the example pasture below, with W = 2 and H = 1: 

\* \* \*
\* \* \*
The banner size is in the range 2..3. This pasture contains (2+1) \* (1+1) = 6 points and has (6 take 2) = (6\*5)/(2\*1) = 15 different potential pairs of points between which the banner-holding wire might stretch:

```cpp
(0,0)-(0,1)   (0,0)-(2,1)   (0,1)-(2,1)   (1,1)-(2,0) 
(0,0)-(1,0)   (0,1)-(1,0)   (1,0)-(1,1)   (1,1)-(2,1) 
(0,0)-(1,1)   (0,1)-(1,1)   (1,0)-(2,0)   (2,0)-(2,1) 
(0,0)-(2,0)   (0,1)-(2,0)   (1,0)-(2,1) 
```
Of these pairs, only four have a length in the range 2..3:
Len                       Len

(0,0)-(2,0) 2.00          (0,1)-(2,0) 2.24 

(0,0)-(2,1) 2.24          (0,1)-(2,1) 2.00 

Of these four, the pairs (0,0)-(2,0) and (0,1)-(2,1) both have a post directly on the line between the endpoints, and thus are 

unsuitable.

So, just two pairs of points out of 15 are acceptable candidates for hanging the banner wire.


## 样例 #1

### 输入

```
2 1 2 3 
```

### 输出

```
2 
```

# AI分析结果



### 综合分析与结论
题目要求找出网格中满足长度区间且不经过其他点的线段对。核心条件是线段横纵坐标差互质（gcd=1）。各题解均采用枚举dx和dy，结合gcd判断和对称计数优化。关键难点在于处理水平和垂直线段的特殊情况（仅长度1且gcd=1时有效），以及避免重复计算。

### 精选题解
#### 1. do_while_false（4星）
**关键亮点**：  
- 代码简洁高效，直接枚举dx和dy的非零情况，通过对称性乘2处理斜线段。  
- 单独处理水平和垂直线段的特殊情况，逻辑清晰。  
**个人心得**：  
> "当线段为(1,0)或(0,1)时不需要翻折，因为此时线段方向唯一。"

**核心代码**：  
```cpp
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        if(gcd(i,j)==1 && i*i+j*j>=l*l && i*i+j*j<=r*r)
            ans += 2*(n-i+1)*(m-j+1);
if(l<=1 && 1<=r) 
    ans += n*(m+1) + m*(n+1);
```

#### 2. fyx_Catherine（4星）
**关键亮点**：  
- 通过直角边枚举减少冗余判断，数学转化直观。  
- 预处理gcd和距离，结合乘法原理快速统计数量。  
**核心代码**：  
```cpp
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        if(sqrt(i*i+j*j)在[l,r] && gcd(i,j)==1)
            ans += 2*(n-i+1)*(m-j+1);
if(l==1) ans += n*(m+1) + m*(n+1);
```

#### 3. Ryan_Adam（4星）
**关键亮点**：  
- 处理翻转时的重复计数问题，通过sum变量精确调整。  
- 枚举包含dx或dy为0的情况，确保完整性。  
**核心代码**：  
```cpp
for(int i=0;i<=w;i++)
    for(int j=0;j<=h;j++)
        if(gcd(i,j)==1 && l1<=sqrt(i*i+j*j)<=l2)
            ans += (w-i+1)*(h-j+1) * (非水平/垂直 ? 2 : 1);
```

### 最优关键思路
1. **数学转化**：线段无内部点 ⟺ gcd(dx, dy)=1。  
2. **对称优化**：非水平/垂直线段可镜像翻转，数量乘2。  
3. **特例处理**：dx或dy为0时，长度必须为1且满足区间。  
4. **枚举优化**：避免重复枚举，仅处理互质对和有效长度。

### 拓展与相关题目
1. **同型题目**：  
   - **P1516 青蛙的约会**（扩展欧几里得）  
   - **P1447 [NOI2010] 能量采集**（二维gcd计数）  
   - **P2508 [HAOI2008] 圆上的整点**（勾股数枚举）  

2. **调试经验**：  
   - **特判陷阱**：忘记处理dx=0或dy=0的情况导致漏解。  
   - **精度处理**：浮点比较改用整数运算避免误差（如比较距离平方）。  

### 推荐题目
1. **P1516 青蛙的约会**（扩展欧几里得应用）  
2. **P1447 [NOI2010] 能量采集**（二维gcd求和模型）  
3. **P2508 [HAOI2008] 圆上的整点**（勾股数性质与枚举）

---
处理用时：141.29秒