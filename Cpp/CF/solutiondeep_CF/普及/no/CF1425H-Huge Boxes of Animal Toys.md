# 题目信息

# Huge Boxes of Animal Toys

## 题目描述

Chaneka has a hobby of playing with animal toys. Every toy has a different fun value, a real number. Chaneka has four boxes to store the toys with specification:

- The first box stores toys with fun values in range of $ (-\infty,-1] $ .
- The second box stores toys with fun values in range of $ (-1, 0) $ .
- The third box stores toys with fun values in range of $ (0, 1) $ .
- The fourth box stores toys with fun value in range of $ [1, \infty) $ .

Chaneka has $ A $ , $ B $ , $ C $ , $ D $ toys in the first, second, third, and fourth box, respectively. One day she decides that she only wants one toy, a super toy. So she begins to create this super toy by sewing all the toys she has.

While the number of toys Chaneka has is more than 1, she takes two different toys randomly and then sews them together, creating a new toy. The fun value of this new toy is equal to the multiplication of fun values of the sewn toys. She then puts this new toy in the appropriate box. She repeats this process until she only has one toy. This last toy is the super toy, and the box that stores this toy is the special box.

As an observer, you only know the number of toys in each box initially but do not know their fun values. You also don't see the sequence of Chaneka's sewing. Determine which boxes can be the special box after Chaneka found her super toy.

## 说明/提示

For the first case, here is a scenario where the first box is the special box:

- The first box had toys with fun values $ \{-3\} $ .
- The second box had toys with fun values $ \{ -0.5, -0.5 \} $
- The fourth box had toys with fun values $ \{ 3 \} $

The sewing sequence:

1. Chaneka sews the toy with fun $ -0.5 $ and $ -0.5 $ to a toy with fun $ 0.25 $ and then put it in the third box.
2. Chaneka sews the toy with fun $ -3 $ and $ 0.25 $ to a toy with fun $ -0.75 $ and then put it in the second box.
3. Chaneka sews the toy with fun $ -0.75 $ and $ 3 $ to a toy with fun $ -1.25 $ and then put it in the first box, which then became the special box.

Here is a scenario where the second box ends up being the special box:

- The first box had toys with fun values $ \{-3\} $
- The second box had toys with fun values $ \{ -0.33, -0.25 \} $ .
- The fourth box had toys with fun values $ \{ 3 \} $ .

The sewing sequence:

1. Chaneka sews the toy with fun $ -3 $ and $ -0.33 $ to a toy with fun $ 0.99 $ and then put it in the third box.
2. Chaneka sews the toy with fun $ 0.99 $ and $ 3 $ to a toy with fun $ 2.97 $ and then put in it the fourth box.
3. Chaneka sews the toy with fun $ 2.97 $ and $ -0.25 $ to a toy with fun $ -0.7425 $ and then put it in the second box, which then became the special box.

 There is only one toy for the second case, so Chaneka does not have to sew anything because that toy, by definition, is the super toy.

## 样例 #1

### 输入

```
2
1 2 0 1
0 1 0 0```

### 输出

```
Ya Ya Tidak Tidak
Tidak Ya Tidak Tidak```

# AI分析结果

### 题目内容重写（中文）

**题目描述**

Chaneka有一个喜欢玩动物玩具的爱好。每个玩具都有一个不同的乐趣值，一个实数。Chaneka有四个盒子来存放这些玩具，具体规格如下：

- 第一个盒子存放乐趣值在 $(-\infty, -1]$ 范围内的玩具。
- 第二个盒子存放乐趣值在 $(-1, 0)$ 范围内的玩具。
- 第三个盒子存放乐趣值在 $(0, 1)$ 范围内的玩具。
- 第四个盒子存放乐趣值在 $[1, \infty)$ 范围内的玩具。

Chaneka有 $A$、$B$、$C$、$D$ 个玩具分别存放在第一、第二、第三和第四个盒子中。有一天，她决定只想要一个玩具，一个超级玩具。于是她开始通过缝制她所有的玩具来创建这个超级玩具。

当Chaneka拥有的玩具数量多于1时，她随机取出两个不同的玩具并将它们缝制在一起，创建一个新的玩具。这个新玩具的乐趣值等于被缝制玩具的乐趣值的乘积。然后她将这个新玩具放入适当的盒子中。她重复这个过程，直到她只有一个玩具。这个最后的玩具就是超级玩具，存放这个玩具的盒子就是特殊盒子。

作为观察者，你只知道每个盒子中初始的玩具数量，但不知道它们的乐趣值。你也没有看到Chaneka的缝制顺序。请确定在Chaneka找到她的超级玩具后，哪些盒子可能成为特殊盒子。

### 算法分类

**数学**

### 题解分析与结论

这道题的核心在于通过数学分析确定最终超级玩具的乐趣值可能落在哪个区间。所有题解都基于以下两个关键点：

1. **符号问题**：最终乘积的符号取决于负数的个数。如果负数的个数为偶数，则乘积为正；否则为负。
2. **绝对值问题**：通过极端情况分析，确定乘积的绝对值是否可能趋近于0或无穷大。

### 所选高分题解

#### 题解1：UniGravity (5星)
**关键亮点**：
- 清晰地分析了符号和绝对值的问题。
- 通过极端情况分析，简洁地得出了结论。
- 代码实现简洁且易于理解。

**核心代码**：
```cpp
if ((a + b) % 2 == 1) {
    if ((a + d) > 0) a1 = 1; // 无穷趋近于负无穷
    if ((b + c) > 0) b1 = 1; // 无穷趋近于0
} else {
    if ((a + d) > 0) d1 = 1; // 无穷趋近于正无穷
    if ((b + c) > 0) c1 = 1; // 无穷趋近于0
}
```

#### 题解2：Qing_喵乖乖喵 (4星)
**关键亮点**：
- 通过简单的条件判断，快速得出结果。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
if((A+B)&1){
    if(D||A) A=1,D=0;
    if(B||C) B=1,C=0;
}else{
    if(D||A) A=0,D=1;
    if(B||C) B=0,C=1;
}
```

#### 题解3：WaterSky (4星)
**关键亮点**：
- 通过极端情况分析，快速得出结果。
- 代码实现简洁，逻辑清晰。

**核心代码**：
```cpp
if((A+B)%2==1){
    if(D || A) A=1,D=0;
    if(B || C) B=1,C=0;
}else{
    if(D || A) A=0,D=1;
    if(B || C) B=0,C=1;
}
```

### 最优关键思路与技巧

1. **符号分析**：通过负数的个数确定最终乘积的符号。
2. **极端情况分析**：通过将某些数取到极端值（如无穷大或无穷小），确定乘积的绝对值是否可能趋近于0或无穷大。

### 拓展思路

类似的问题可以通过分析符号和极端情况来解决，尤其是在涉及乘积或和的题目中。例如，在确定某些数的和或积的可能范围时，可以采用类似的思路。

### 推荐题目

1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)
2. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
3. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)

---
处理用时：35.27秒