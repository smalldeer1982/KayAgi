# 题目信息

# Inscribed Figures

## 题目描述

The math faculty of Berland State University has suffered the sudden drop in the math skills of enrolling students. This year the highest grade on the entrance math test was 8. Out of 100! Thus, the decision was made to make the test easier.

Future students will be asked just a single question. They are given a sequence of integer numbers $ a_1, a_2, \dots, a_n $ , each number is from $ 1 $ to $ 3 $ and $ a_i \ne a_{i + 1} $ for each valid $ i $ . The $ i $ -th number represents a type of the $ i $ -th figure:

1. circle;
2. isosceles triangle with the length of height equal to the length of base;
3. square.

The figures of the given sequence are placed somewhere on a Cartesian plane in such a way that:

- $ (i + 1) $ -th figure is inscribed into the $ i $ -th one;
- each triangle base is parallel to OX;
- the triangle is oriented in such a way that the vertex opposite to its base is at the top;
- each square sides are parallel to the axes;
- for each $ i $ from $ 2 $ to $ n $ figure $ i $ has the maximum possible length of side for triangle and square and maximum radius for circle.

Note that the construction is unique for some fixed position and size of just the first figure.

The task is to calculate the number of distinct points (not necessarily with integer coordinates) where figures touch. The trick is, however, that the number is sometimes infinite. But that won't make the task difficult for you, will it?

So can you pass the math test and enroll into Berland State University?

## 说明/提示

Here are the glorious pictures for the examples. Note that the triangle is not equilateral but just isosceles with the length of height equal to the length of base. Thus it fits into a square in a unique way.

The distinct points where figures touch are marked red.

In the second example the triangle and the square touch each other for the whole segment, it contains infinite number of points.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1156A/ecd8055b09d857a1401e35aa45bd638bb2a049f0.png)

## 样例 #1

### 输入

```
3
2 1 3
```

### 输出

```
Finite
7
```

## 样例 #2

### 输入

```
3
1 2 3
```

### 输出

```
Infinite
```

# AI分析结果



### 中文重述题目
# 内接图形

## 题目描述

给定由整数组成的序列 $a_1, a_2, \dots, a_n$（每个数取1到3且相邻不同），每个数代表图形的类型：
1. 圆形
2. 底边与高相等的等腰三角形
3. 正方形

图形按以下规则放置在笛卡尔平面：
- 第 $(i+1)$ 个图形内接于第 $i$ 个
- 三角形底边平行于OX轴，顶点朝上
- 正方形边平行于坐标轴
- 每个图形尽可能最大化尺寸

求所有图形接触点的数量（若出现无限个点则输出"Infinite"）。

## 样例
样例1：
输入：
3
2 1 3
输出：
Finite
7

样例2：
输入：
3
1 2 3
输出：
Infinite

### 算法分类
模拟

---

### 题解分析与结论

#### 核心思路
1. **相邻图形类型判断**：枚举每对相邻图形的6种组合，确定接触点数
2. **无限情况处理**：当出现三角形与正方形相邻时（2-3或3-2），立即返回无限
3. **重复点特判**：对序列中"3-1-2"的情况，需扣除重复计算的1个点

#### 最优题解

##### 题解作者：wxwoo（★★★★★）
**关键亮点**：
- 使用二维数组预存6种组合的接触点数
- 简洁的特判处理逻辑
- 完整处理所有边界情况

**核心代码**：
```cpp
const int res[4][4] = { /* 预存各组合结果 */
    0,0,0,0,
    0,0,3,4,  // 1后接2得3，后接3得4
    0,3,0,0x3f3f3f3f, // 2后接3得无限
    0,4,0x3f3f3f3f,0 
};

for(int i=2; i<=n; ++i) {
    ans += res[a[i-1]][a[i]];
    if(i>=3 && a[i-2]==3 && a[i-1]==1 && a[i]==2) ans--;
}
```

##### 题解作者：Doubeecat（修正版）（★★★★☆）
**关键亮点**：
- 直观的条件分支处理
- 详细注释说明每种图形组合情况
- 包含调试经历：原代码未处理特例的教训

**核心代码片段**：
```cpp
for(int i=2; i<=n; ++i){
    if(pre[i-2]==3 && pre[i-1]==1 && pre[i]==2) ans--;
    if(pre[i-1]==1) ans += (pre[i]==2) ? 3 : 4;
    else if(pre[i-1]==2) {
        if(pre[i]!=1) { puts("Infinite"); return; }
        ans +=3;
    } else { // pre[i-1]==3
        if(pre[i]!=1) { puts("Infinite"); return; }
        ans +=4;
    }
}
```

---

### 关键技巧总结
1. **预处理组合结果**：使用二维数组存储固定组合结果，简化条件判断
2. **滑动窗口特判**：遍历时检查连续三个元素的特定组合（3-1-2）
3. **即时终止判断**：遇到无限情况立即退出，避免无效计算

---

### 推荐类似题目
1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003) - 二维坐标覆盖判断
2. [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067) - 多条件格式化处理
3. [P1328 生活大爆炸版石头剪刀布](https://www.luogu.com.cn/problem/P1328) - 胜负规则矩阵判断

---
处理用时：41.74秒