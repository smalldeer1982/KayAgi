# 题目信息

# Sonya and Exhibition

## 题目描述

Sonya decided to organize an exhibition of flowers. Since the girl likes only roses and lilies, she decided that only these two kinds of flowers should be in this exhibition.

There are $ n $ flowers in a row in the exhibition. Sonya can put either a rose or a lily in the $ i $ -th position. Thus each of $ n $ positions should contain exactly one flower: a rose or a lily.

She knows that exactly $ m $ people will visit this exhibition. The $ i $ -th visitor will visit all flowers from $ l_i $ to $ r_i $ inclusive. The girl knows that each segment has its own beauty that is equal to the product of the number of roses and the number of lilies.

Sonya wants her exhibition to be liked by a lot of people. That is why she wants to put the flowers in such way that the sum of beauties of all segments would be maximum possible.

## 说明/提示

In the first example, Sonya can put roses in the first, fourth, and fifth positions, and lilies in the second and third positions;

- in the segment $ [1\ldots3] $ , there are one rose and two lilies, so the beauty is equal to $ 1\cdot 2=2 $ ;
- in the segment $ [2\ldots4] $ , there are one rose and two lilies, so the beauty is equal to $ 1\cdot 2=2 $ ;
- in the segment $ [2\ldots5] $ , there are two roses and two lilies, so the beauty is equal to $ 2\cdot 2=4 $ .

The total beauty is equal to $ 2+2+4=8 $ .

In the second example, Sonya can put roses in the third, fourth, and sixth positions, and lilies in the first, second, and fifth positions;

- in the segment $ [5\ldots6] $ , there are one rose and one lily, so the beauty is equal to $ 1\cdot 1=1 $ ;
- in the segment $ [1\ldots4] $ , there are two roses and two lilies, so the beauty is equal to $ 2\cdot 2=4 $ ;
- in the segment $ [4\ldots6] $ , there are two roses and one lily, so the beauty is equal to $ 2\cdot 1=2 $ .

The total beauty is equal to $ 1+4+2=7 $ .

## 样例 #1

### 输入

```
5 3
1 3
2 4
2 5
```

### 输出

```
01100```

## 样例 #2

### 输入

```
6 3
5 6
1 4
4 6
```

### 输出

```
110010```

# AI分析结果

### 题目内容重写（中文）

**Sonya 和展览**

#### 题目描述

Sonya 决定组织一个花卉展览。由于她只喜欢玫瑰和百合，因此她决定在展览中只展示这两种花。

展览中有 $n$ 朵花排成一排。Sonya 可以在第 $i$ 个位置放置一朵玫瑰或一朵百合。因此，每个位置必须恰好放置一朵花：玫瑰或百合。

她知道将有 $m$ 个人参观这个展览。第 $i$ 个参观者将参观从 $l_i$ 到 $r_i$ 的所有花朵。她知道每个区间的美丽程度等于该区间内玫瑰的数量与百合的数量的乘积。

Sonya 希望她的展览能被很多人喜欢。因此，她希望以某种方式放置花朵，使得所有区间的美丽程度之和最大。

#### 说明/提示

在第一个样例中，Sonya 可以在第1、4、5个位置放置玫瑰，在第2、3个位置放置百合；

- 在区间 $[1\ldots3]$ 中，有1朵玫瑰和2朵百合，因此美丽程度为 $1\cdot 2=2$；
- 在区间 $[2\ldots4]$ 中，有1朵玫瑰和2朵百合，因此美丽程度为 $1\cdot 2=2$；
- 在区间 $[2\ldots5]$ 中，有2朵玫瑰和2朵百合，因此美丽程度为 $2\cdot 2=4$。

总美丽程度为 $2+2+4=8$。

在第二个样例中，Sonya 可以在第3、4、6个位置放置玫瑰，在第1、2、5个位置放置百合；

- 在区间 $[5\ldots6]$ 中，有1朵玫瑰和1朵百合，因此美丽程度为 $1\cdot 1=1$；
- 在区间 $[1\ldots4]$ 中，有2朵玫瑰和2朵百合，因此美丽程度为 $2\cdot 2=4$；
- 在区间 $[4\ldots6]$ 中，有2朵玫瑰和1朵百合，因此美丽程度为 $2\cdot 1=2$。

总美丽程度为 $1+4+2=7$。

#### 样例 #1

##### 输入

```
5 3
1 3
2 4
2 5
```

##### 输出

```
01100```

#### 样例 #2

##### 输入

```
6 3
5 6
1 4
4 6
```

##### 输出

```
110010```

### 算法分类
**构造**

### 题解分析与结论

所有题解的核心思路都是通过交替放置玫瑰和百合，使得在每个区间内玫瑰和百合的数量尽可能接近，从而最大化每个区间的美丽程度之和。这种方法利用了“和一定，差小积大”的数学原理。

#### 题解评分与亮点

1. **作者：zplqwq (赞：6)**
   - **星级：5星**
   - **关键亮点**：简洁明了地解释了交替放置的原理，代码实现简单高效。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++) cout<<i%2;
     ```

2. **作者：__Hacheylight__ (赞：4)**
   - **星级：4星**
   - **关键亮点**：直接指出序列与m无关，简化了问题，代码简洁。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++) printf("%d",i&1);
     ```

3. **作者：锦瑟，华年 (赞：3)**
   - **星级：4星**
   - **关键亮点**：通过表格模拟解释了“和同近积大”的原理，思路清晰。
   - **代码核心**：
     ```cpp
     for(int i=1;i<=n;i++) printf("%d",i%2);
     ```

### 最优关键思路或技巧
交替放置玫瑰和百合，使得在每个区间内玫瑰和百合的数量尽可能接近，从而最大化每个区间的美丽程度之和。这种方法利用了“和一定，差小积大”的数学原理。

### 可拓展之处
类似的问题可以通过构造法解决，特别是在需要最大化或最小化某些乘积或和的情况下。例如，最大化某些区间内的元素和或最小化某些区间内的元素差。

### 推荐题目
1. [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)
2. [P1005 矩阵取数游戏](https://www.luogu.com.cn/problem/P1005)
3. [P1006 传纸条](https://www.luogu.com.cn/problem/P1006)

---
处理用时：32.48秒