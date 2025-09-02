# 题目信息

# Limit

## 题目描述

You are given two polynomials:

- $ P(x)=a_{0}·x^{n}+a_{1}·x^{n-1}+...+a_{n-1}·x+a_{n} $ and
- $ Q(x)=b_{0}·x^{m}+b_{1}·x^{m-1}+...+b_{m-1}·x+b_{m} $ .

Calculate limit ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/c4175ff9e67dcea784338cdf48751a5246b376e3.png).

## 说明/提示

Let's consider all samples:

1. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/fa0398edff13cf2c92e5c43221f39e276c660081.png)
2. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/c67cf94a1cc8bcaea0f1fad4d1517e71a16c059c.png)
3. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/10f72864aeb3074d34f0800e3222dff4f843160b.png)
4. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/40209670dcba21fdfb878390c6903f068a0dc416.png)
5. ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF197B/9292f5d3f957b00c90b246f44689b5ebc7f89abc.png)

You can learn more about the definition and properties of limits if you follow the link: http://en.wikipedia.org/wiki/Limit\_of\_a\_function

## 样例 #1

### 输入

```
2 1
1 1 1
2 5
```

### 输出

```
Infinity
```

## 样例 #2

### 输入

```
1 0
-1 3
2
```

### 输出

```
-Infinity
```

## 样例 #3

### 输入

```
0 1
1
1 0
```

### 输出

```
0/1
```

## 样例 #4

### 输入

```
2 2
2 1 6
4 5 -7
```

### 输出

```
1/2
```

## 样例 #5

### 输入

```
1 1
9 0
-5 2
```

### 输出

```
-9/5
```

# AI分析结果



### 题目内容重写（原题已为中文，无需翻译）

### 算法分类
数学

### 题解综合分析
各题解均基于极限的核心性质：当x→+∞时，多项式的主导项为最高次项。处理逻辑分为三种情况：分子次数>分母次数（无穷大）、次数相等（系数比）、分母次数更大（0）。所有解法的关键点在于正确判断次数关系、处理系数符号、约分输出。

---

### 高分题解推荐
#### 1. 作者：Limit（★★★★★）
**关键亮点**  
- 逻辑清晰，分情况讨论完整  
- 正确处理符号问题（通过a0*b0的正负判断整体符号）  
- 使用辗转相除法约分  
- 代码结构规范，可读性强  

**核心代码**  
```cpp
if(N<M) printf("0/1");
else if(N>M) {
    if(a0*b0<0) printf("-");
    printf("Infinity");
}
else {
    int gcd=Gcd(a0,b0);
    a0/=gcd; b0/=gcd;
    printf("%d/%d",a0,b0);
}
```

#### 2. 作者：rui_er（★★★★☆）
**关键亮点**  
- 代码极度简洁，使用__gcd内置函数  
- 通过临时变量处理无用输入，节省内存  
- 符号判断直接通过乘积处理  

**个人心得**  
"养成了一个习惯，用 `veryImportantVariable` 存完全没用的输入" → 通过幽默命名暗示题目只需首项系数。

#### 3. 作者：xyf007（★★★★☆）
**关键亮点**  
- 独立编写gcd函数，避免依赖编译器特性  
- 单独处理分子分母的负号转正  
- 输出格式严格符合分母正数的要求  

---

### 最优解题思路总结
**核心技巧**：  
1. **主导项原理**：仅比较分子分母最高次数项的系数和次数  
2. **符号处理**：通过a0*b0的符号性判断无穷大的正负  
3. **约分技巧**：使用gcd化简分数形式  

**实现要点**：  
- 只需读取首项系数，后续输入可丢弃  
- 输出时确保分母为正（通过符号前置）  
- 特判次数相等时的分数化简  

---

### 拓展与相似题目
**类似套路题**：  
1. [P1022 计算器的改良](https://www.luogu.com.cn/problem/P1022)（多项式方程求解）  
2. [P1038 神经网络](https://www.luogu.com.cn/problem/P1038)（基于传递函数的极限分析）  
3. [P5143 攀爬者](https://www.luogu.com.cn/problem/P5143)（数学建模中的极值判断）

---
处理用时：41.65秒