# 题目信息

# [USACO09NOV] The Grand Farm-off S

## 题目描述

Farmer John owns 3\*N (1 <= N <= 500,000) cows surprisingly numbered 0..3\*N-1, each of which has some associated integer weight W\_i (1 <= W\_i <= d). He is entering the Grand Farm-off, a farming competition where he shows off his cows to the greater agricultural community.

This competition allows him to enter a group of N cows. He has given each of his cows a utility rating U\_i (1 <= U\_i <= h), which

represents the usefulness he thinks that a particular cow will have in the competition, and he wants his selection of cows to have the maximal sum of utility.

There might be multiple sets of N cows that attain the maximum utility sum. FJ is afraid the competition may impose a total weight limit on the cows in the competition, so a secondary priority is to bring lighter weight competition cows.

Help FJ find a set of N cows with minimum possible total weight among the sets of N cows that maximize the utility, and print the remainder when this total weight is divided by M (10,000,000 <= M <= 1,000,000,000).

Note: to make the input phase faster, FJ has derived polynomials which will generate the weights and utility values for each cow. For each cow 0 <= i < 3\*N,

 $$W_i=(a\times i^5+b\times i^2+c)\mod d$$
 
 $$U_i=(e\times i^5+f\times i^3+g)\mod h$$
 
 $$(0\le a,b,c,d,e,f,g,h\le 10^9)$$

The formulae do sometimes generate duplicate numbers; your algorithm should handle this properly. 

农夫约翰有3N(1 < N < 500000)头牛，编号依次为1..#N，每头牛都有一个整数值的体 重。约翰准备参加农场技艺大赛，向广大的农业社区展示他的奶牛.
大赛规则允许约翰带N头牛参赛.约翰给每头牛赋予了一个“有用度”Ui，它表 示了某头牛在比赛中的有用程度.约翰希望他选出的奶牛的有用度之和最大.

有可能选出很多组的N头牛都能达到有用度最大和.约翰害怕选出的N头牛的总重量会给大赛 带来震撼，所以，要考虑优先选择体重轻的奶牛.

帮助约翰选出N头总重量最轻，并且有用度之和最大的奶牛.输出体重模M后的余数.

注意：为了使输入更快，约翰使用了一个多项式来生成每头牛的体重和有用度.对每头牛/， 体重和有用度的计算公式为：



 $$W_i=(a\times i^5+b\times i^2+c)\mod d$$
 
 $$U_i=(e\times i^5+f\times i^3+g)\mod h$$
 
 $$(0\le a,b,c,d,e,f,g,h\le 10^9)$$

## 说明/提示

The functions generate weights of 5, 6, 9, 14, 21, and 30 along with utilities of 0, 1, 8, 27, 64, and 125.


The two cows with the highest utility are cow 5 and 6, and their combined weight is 21+30=51.


## 样例 #1

### 输入

```
2 0 1 5 55555555 0 1 0 55555555 55555555 
```

### 输出

```
51 
```

# AI分析结果



### 综合分析与结论
题目要求从3N头牛中选出U值最大的N头，若U相同则选W总和最小的。关键难点在于处理大数运算与多重排序条件。所有题解均采用结构体排序策略，核心差异在于对大数计算的优化处理方式。最优解法需满足：正确处理模运算、避免数值溢出、高效计算高次幂。

---

### 精选题解与评分

#### 1. 作者：FourteenObsidian（★★★★★）
**关键亮点**  
- 对参数预取模减少计算量  
- 分步计算i的幂次并逐次取模  
- 正确使用long long且代码可读性强  
**核心代码**  
```cpp
for(register long long i=0;i<3*n;++i){
    long long i1=i%d,i11=i%h;
    long long i2=(i1*i1)%d,i3=(i1*i2)%d,i5=(i2*i3)%d;
    long long i22=(i11*i11)%h,i33=(i11*i22)%h,i55=(i22*i33)%h;
    a1[i].w=((a*i5)%d + (b*i2)%d + c)%d; 
    a1[i].u=((e*i55)%h + (f*i33)%h + g)%h; 
}
```
**个人心得**  
"怕pow超时，结果与楼上dalao意外地写得差不多" —— 强调避免使用浮点函数，采用分步计算。

#### 2. 作者：Qing_s（★★★★）
**关键亮点**  
- 手动分解幂次计算过程清晰  
- 明确强调避免pow函数的重要性  
**核心代码**  
```cpp
for(int i=0;i<3*n;i++){
    long long i1=i%d, ii1=i%h;
    long long i2=i1*i%d, ii2=ii1*i%h;
    long long i3=i2*i%d, ii3=ii2*i%h;
    // ... 继续分解i^5的计算 ...
    cow[i].w = (a*i5 + b*i2 + c) % d;
}
```
**踩坑教训**  
"第一遍用pow只得了10分" —— 使用浮点函数导致精度错误，改为分步计算后解决。

#### 3. 作者：zy小可爱ღ（★★★★）  
**关键亮点**  
- 显式分离W和U的模运算  
- 代码简洁且变量命名清晰  
**核心代码**  
```cpp
l[i].w=((a%d)*((i%d*i%d*i%d*i%d*i%d) %d) + ... ) %d; 
l[i].u=((e%h)*((i%h*i%h*i%h*i%h*i%h) %h) + ... ) %h;
```

---

### 关键思路与技巧总结
1. **幂次分步计算**：将i^5分解为i²→i³→i⁵，每次乘i后立即取模，避免数值溢出。
2. **预取模优化**：对多项式系数a,b,c等先取模，减少中间计算值的大小。
3. **双重排序条件**：结构体排序时优先U降序，次优W升序，确保选择条件正确。
4. **变量类型管理**：全程使用long long防止溢出，数组大小设为3N+避免越界。

---

### 相似题目推荐
1. [P1093 奖学金](https://www.luogu.com.cn/problem/P1093) - 多重条件排序  
2. [P1104 生日](https://www.luogu.com.cn/problem/P1104) - 日期与字符串混合排序  
3. [P1009 阶乘之和](https://www.luogu.com.cn/problem/P1009) - 大数计算与高精度处理

---
处理用时：71.75秒