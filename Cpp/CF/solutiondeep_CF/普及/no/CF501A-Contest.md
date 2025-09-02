# 题目信息

# Contest

## 题目描述

Misha and Vasya participated in a Codeforces contest. Unfortunately, each of them solved only one problem, though successfully submitted it at the first attempt. Misha solved the problem that costs $ a $ points and Vasya solved the problem that costs $ b $ points. Besides, Misha submitted the problem $ c $ minutes after the contest started and Vasya submitted the problem $ d $ minutes after the contest started. As you know, on Codeforces the cost of a problem reduces as a round continues. That is, if you submit a problem that costs $ p $ points $ t $ minutes after the contest started, you get ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF501A/0c1954e97a47d9a6cd1567e3d0ad4f4a76ada737.png) points.

Misha and Vasya are having an argument trying to find out who got more points. Help them to find out the truth.

## 样例 #1

### 输入

```
500 1000 20 30
```

### 输出

```
Vasya
```

## 样例 #2

### 输入

```
1000 1000 1 1
```

### 输出

```
Tie
```

## 样例 #3

### 输入

```
1500 1000 176 177
```

### 输出

```
Misha
```

# AI分析结果



【中文题目重写】
# 比赛

## 题目描述

Misha 和 Vasya 参加了一场 Codeforces 竞赛。他们各自只解决了一个问题，且都是一次提交通过。Misha 解决的问题价值 $a$ 分，Vasya 解决的问题价值 $b$ 分。Misha 在比赛开始后 $c$ 分钟提交，Vasya 在比赛开始后 $d$ 分钟提交。Codeforces 的题目分数会随着时间推移减少，具体规则为：若你在比赛开始 $t$ 分钟后提交价值 $p$ 分的题目，则最终得分为 $\max\left(\frac{3p}{10}, p - \frac{p \times t}{250}\right)$。

请判断 Misha 和 Vasya 谁的得分更高，或者是否平局。

## 输入样例 #1

500 1000 20 30

## 输出样例 #1

Vasya

---

【算法分类】
模拟

---

### 题解综合分析

本题考察对题意的直接模拟，核心在于正确实现分数计算公式，并注意浮点数精度处理。各题解主要差异体现在数值类型选择（整型/浮点型）和比较方式上。使用浮点型计算可确保精度正确，而比较时加入 epsilon 处理能避免浮点误差。

---

### 精选题解

#### 题解作者：_Clown_（★★★★★）
**关键亮点**：
1. 使用 double 类型确保计算精度
2. 浮点数比较时引入 1e-6 容差
3. 代码结构清晰，包含输入优化

**核心代码**：
```cpp
double X,Y;
X = max(0.3*A, A - A/250*C);
Y = max(0.3*B, B - B/250*D);
// 比较时使用 1e-6 容差
if(X-Y > 1e-6) cout<<"Misha";
else if(Y-X > 1e-6) cout<<"Vasya";
else cout<<"Tie";
```

**个人心得**：
> "浮点数比较大小时要写一个 EPS，不要直接比较" —— 强调浮点精度处理的重要性

---

#### 题解作者：666DHG（★★★★☆）
**核心思路**：
1. 采用浮点型计算保证准确性
2. 直接公式翻译，代码简洁
3. 变量命名清晰（ans1、ans2）

**关键实现**：
```cpp
ans1 = max(3*a/10.00, a - a*c/250.00);
ans2 = max(3*b/10.00, b - b*d/250.00);
// 直接比较（未显式处理精度，但题目数据范围下安全）
if (ans1 < ans2) printf("Vasya");
```

---

#### 题解作者：caibet（★★★★☆）
**实现要点**：
1. 使用 double 类型计算
2. 变量命名直观（x、y）
3. 逻辑结构简单明了

**代码片段**：
```cpp
double x = max(a*3/10, a - a/250*c);
double y = max(b*3/10, b - b/250*d);
// 标准比较（隐含数据范围安全假设）
if(x > y) cout<<"Misha";
```

---

### 关键思路总结
1. **浮点精度优先**：使用 double 类型进行中间计算，避免整型运算导致的精度丢失
2. **容差处理**：比较浮点数时采用 epsilon（如 1e-6）处理微小误差
3. **公式直译**：将题目给出的数学公式直接转换为代码表达式
4. **变量清晰**：通过合理命名区分不同选手的得分计算

---

### 拓展建议
同类问题可关注：
1. 涉及分数衰减机制的场景（如游戏得分计算）
2. 需要平衡整数与浮点运算的模拟题
3. 带有时序因素的比较问题

---

### 推荐习题
1. P1425 小鱼的游泳时间（模拟时间计算）
2. P5719 分类平均（浮点运算与条件判断）
3. P3954 成绩（多权重分数计算）

---
处理用时：175.12秒