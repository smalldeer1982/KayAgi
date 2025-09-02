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



### 算法分类
数学

### 综合分析与结论
题目要求找到满足长度区间且线段上无其他格点的点对。核心思路是通过枚举线段在x、y方向的差值i和j，并确保gcd(i,j)=1（保证无中间点），同时计算该线段在网格中的平移可能数和镜像翻转情况。水平和垂直线段需特殊处理（仅长度为1时合法）。

### 精选题解

#### 题解作者：do_while_false（⭐️⭐️⭐️⭐️⭐️）
- **关键亮点**：代码简洁高效，正确处理水平和垂直情况。枚举i,j从1开始避免冗余计算，利用gcd判断线段合法性，对符合条件的非水平/垂直线段乘2计数。
- **核心代码**：
```cpp
for(int i=1;i<=n;i++)
    for(int j=1;j<=m;j++)
        if(gcd(i,j)==1 && i*i+j*j>=l*l && i*i+j*j<=r*r)
            ans += 2*(n-i+1)*(m-j+1);
if(l==1) ans += n*(m+1) + (n+1)*m; // 处理水平和垂直
```

#### 题解作者：fyx_Catherine（⭐️⭐️⭐️⭐️）
- **关键亮点**：通过直角三角形的平移计数，对称性处理减少循环次数，单独处理l=1的特殊情况。
- **核心代码**：
```cpp
if(l==1) ans += (n+1)*m + (m+1)*n; // 水平/垂直线段
for(int i=1;i<=n;i++) {
    for(int j=1;j<=m;j++) {
        if(sqrt(i*i+j*j)在[l,r]内 && gcd(i,j)==1)
            ans += 2*(n-i+1)*(m-j+1);
    }
}
```

#### 题解作者：owlAlice（⭐️⭐️⭐️⭐️）
- **关键亮点**：详细推导gcd条件，正确处理线段翻转条件，代码可读性较强。
- **核心代码**：
```cpp
for(int i=0;i<=w;i++)
    for(int j=0;j<=h;j++) {
        if(gcd(i,j)==1 && 长度符合) {
            if(i+j != 1) ans += 平移数*2; // 非水平/垂直
            else ans += 平移数;
        }
    }
```

### 最优关键思路
1. **数学条件判断**：利用gcd(i,j)=1确保线段无中间点。
2. **平移计数公式**：对于边长为i,j的线段，平移次数为(n-i+1)*(m-j+1)。
3. **镜像翻转优化**：非水平/垂直线段乘2计数，避免重复枚举。
4. **特例处理**：水平/垂直线段仅在长度为1时合法，单独计算。

### 拓展与同类题
- **相似题目**：  
  1. [P2158 [SDOI2008] 仪仗队](https://www.luogu.com.cn/problem/P2158)（gcd判断可见性）  
  2. [P1447 [NOI2010] 能量采集](https://www.luogu.com.cn/problem/P1447)（二维gcd计数应用）  
  3. [P1516 青蛙的约会](https://www.luogu.com.cn/problem/P1516)（扩展欧几里得应用）

### 个人心得摘录
- **do_while_false**：  
  > “当线段为（1,0）或（0,1）时不需要翻折”——通过条件判断避免重复计数。  
- **CR_Raphael**：  
  > “枚举点（0,0）到其他点的可能性，再翻折统计”——对称性简化枚举范围。  
- **owlAlice**：  
  > “参考博客后理解到gcd条件是关键”——强调数学推导在解题中的重要性。

---
处理用时：177.27秒