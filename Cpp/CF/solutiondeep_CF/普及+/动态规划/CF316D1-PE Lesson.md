# 题目信息

# PE Lesson

## 题目描述

Smart Beaver decided to be not only smart, but also a healthy beaver! And so he began to attend physical education classes at school X. In this school, physical education has a very creative teacher. One of his favorite warm-up exercises is throwing balls. Students line up. Each one gets a single ball in the beginning. The balls are numbered from $ 1 $ to $ n $ (by the demand of the inventory commission).

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316D1/dd5cf282ea1c98183da55e6989050cd8eabdb84c.png) Figure 1. The initial position for $ n=5 $ . After receiving the balls the students perform the warm-up exercise. The exercise takes place in a few throws. For each throw the teacher chooses any two arbitrary different students who will participate in it. The selected students throw their balls to each other. Thus, after each throw the students remain in their positions, and the two balls are swapped.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF316D1/6b5342e8a9f57fae45c7b1e47abe66718bc85450.png) Figure 2. The example of a throw. In this case there was a throw between the students, who were holding the $ 2 $ -nd and the $ 4 $ -th balls. Since the warm-up has many exercises, each of them can only continue for little time. Therefore, for each student we know the maximum number of throws he can participate in. For this lessons maximum number of throws will be $ 1 $ or $ 2 $ .

Note that after all phases of the considered exercise any ball can end up with any student. Smart Beaver decided to formalize it and introduced the concept of the "ball order". The ball order is a sequence of $ n $ numbers that correspond to the order of balls in the line. The first number will match the number of the ball of the first from the left student in the line, the second number will match the ball of the second student, and so on. For example, in figure $ 2 $ the order of the balls was ( $ 1 $ , $ 2 $ , $ 3 $ , $ 4 $ , $ 5 $ ), and after the throw it was ( $ 1 $ , $ 4 $ , $ 3 $ , $ 2 $ , $ 5 $ ). Smart beaver knows the number of students and for each student he knows the maximum number of throws in which he can participate. And now he is wondering: what is the number of distinct ways of ball orders by the end of the exercise.

## 样例 #1

### 输入

```
5
1 2 2 1 2
```

### 输出

```
120
```

## 样例 #2

### 输入

```
8
1 2 2 1 2 1 1 2
```

### 输出

```
16800
```

# AI分析结果

### 题目内容重写

#### PE课程

**题目描述**

聪明的海狸决定不仅要聪明，还要健康！于是它开始在学校X上体育课。在这所学校，体育老师非常有创意。他最喜欢的热身练习之一是抛球。学生们排成一排，每个人一开始都拿到一个球。球的编号从1到n（根据库存委员会的要求）。

图1展示了n=5时的初始位置。在拿到球后，学生们开始进行热身练习。练习由几次抛球组成。每次抛球时，老师任意选择两个不同的学生参与。被选中的学生互相抛球。因此，每次抛球后，学生们的位置保持不变，但两个球会交换位置。

图2展示了一次抛球的例子。在这种情况下，抛球发生在持有第2和第4个球的学生之间。由于热身练习有很多，每个练习只能持续很短的时间。因此，对于每个学生，我们知道他最多可以参与多少次抛球。在本节课中，最多抛球次数为1或2。

注意，在考虑的所有练习阶段结束后，任何球都可能落在任何学生手中。聪明的海狸决定将其形式化，并引入了“球序”的概念。球序是一个由n个数字组成的序列，对应于学生排成一排时球的顺序。第一个数字对应于最左边学生的球，第二个数字对应于第二个学生的球，依此类推。例如，在图2中，球的顺序是（1, 2, 3, 4, 5），抛球后变为（1, 4, 3, 2, 5）。聪明的海狸知道学生的数量以及每个学生最多可以参与多少次抛球。现在他想知道：练习结束时，有多少种不同的球序。

**样例 #1**

输入：
```
5
1 2 2 1 2
```
输出：
```
120
```

**样例 #2**

输入：
```
8
1 2 2 1 2 1 1 2
```
输出：
```
16800
```

### 题解分析与结论

#### 题解对比与评分

1. **yuzhechuan (5星)**
   - **关键亮点**：通过将问题分解为“1”和“2”的数量，分别处理。对于“1”的情况，使用动态规划计算排列数；对于“2”的情况，通过阶乘计算排列数。思路清晰，代码简洁。
   - **代码核心**：
     ```cpp
     for(int i=2;i<=cnt;i++) f[i]=(f[i-2]*(i-1)+f[i-1])%mod;
     for(int i=n;i>cnt;i--) ans=ans*i%mod;
     write(ans*f[cnt]%mod);
     ```
   - **个人心得**：通过将问题分解为“1”和“2”的情况，简化了问题复杂度。

2. **chufuzhe (4星)**
   - **关键亮点**：将问题分为交换一次和交换两次的人，分别计算方案数。使用动态规划计算交换一次的人的方案数，使用阶乘计算交换两次的人的方案数。
   - **代码核心**：
     ```cpp
     for(int i = 3; i <= cnt1; i++) {
         f[i] = (f[i - 1] + f[i-2] * 1ll * (i - 1) % 1000000007) % 1000000007;
     }
     for(int i = cnt1 + 1; i <= n; i++) {
         s = s * 1ll * i % 1000000007;
     }
     cout << s * f[cnt1] << endl;
     ```
   - **个人心得**：通过分开处理交换一次和交换两次的人，简化了问题。

3. **LCuter (3星)**
   - **关键亮点**：通过图论中的环排列来解决问题，思路较为复杂，代码实现较为繁琐。
   - **代码核心**：
     ```cpp
     for(REG int i=(t-1)/2+1;i<=t;++i) Ans=(Ans+1ll*Fac[t]*Iac[2*i-t]%Mod*_2Pow[t-i]%Mod*Iac[t-i]%Mod)%Mod;
     ```
   - **个人心得**：通过图论的方法解决问题，思路较为新颖，但实现复杂。

#### 最优关键思路

- **分解问题**：将问题分解为“1”和“2”的情况，分别处理。
- **动态规划**：对于“1”的情况，使用动态规划计算排列数。
- **阶乘计算**：对于“2”的情况，使用阶乘计算排列数。

#### 可拓展之处

- **类似问题**：可以扩展到更多种类的交换限制，如交换次数为3次或更多次。
- **算法套路**：动态规划与阶乘计算的结合，可以应用于其他排列组合问题。

#### 推荐题目

1. [P3383 【模板】线性筛素数](https://www.luogu.com.cn/problem/P3383)
2. [P1048 采药](https://www.luogu.com.cn/problem/P1048)
3. [P1060 开心的金明](https://www.luogu.com.cn/problem/P1060)

#### 个人心得总结

- **调试经历**：在处理动态规划时，注意边界条件的初始化。
- **踩坑教训**：在计算阶乘时，注意模运算的溢出问题。
- **顿悟感想**：通过将问题分解为更小的子问题，可以简化问题的复杂度。

---
处理用时：47.98秒