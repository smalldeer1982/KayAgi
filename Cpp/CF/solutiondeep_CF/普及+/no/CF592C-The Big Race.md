# 题目信息

# The Big Race

## 题目描述

Vector Willman and Array Bolt are the two most famous athletes of Byteforces. They are going to compete in a race with a distance of $ L $ meters today.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF592C/9bfd48ba8eef8aa7a96654a450d8ae80783554b5.png)Willman and Bolt have exactly the same speed, so when they compete the result is always a tie. That is a problem for the organizers because they want a winner.

While watching previous races the organizers have noticed that Willman can perform only steps of length equal to $ w $ meters, and Bolt can perform only steps of length equal to $ b $ meters. Organizers decided to slightly change the rules of the race. Now, at the end of the racetrack there will be an abyss, and the winner will be declared the athlete, who manages to run farther from the starting point of the the racetrack (which is not the subject to change by any of the athletes).

Note that none of the athletes can run infinitely far, as they both will at some moment of time face the point, such that only one step further will cause them to fall in the abyss. In other words, the athlete will not fall into the abyss if the total length of all his steps will be less or equal to the chosen distance $ L $ .

Since the organizers are very fair, the are going to set the length of the racetrack as an integer chosen randomly and uniformly in range from 1 to $ t $ (both are included). What is the probability that Willman and Bolt tie again today?

## 说明/提示

In the first sample Willman and Bolt will tie in case $ 1 $ , $ 6 $ or $ 7 $ are chosen as the length of the racetrack.

## 样例 #1

### 输入

```
10 3 2
```

### 输出

```
3/10
```

## 样例 #2

### 输入

```
7 1 2
```

### 输出

```
3/7
```

# AI分析结果

### 题目内容
# 盛大的赛跑

## 题目描述
Vector Willman和Array Bolt是Byteforces最著名的两位运动员。今天他们将进行一场长度为 $L$ 米的赛跑。

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF592C/9bfd48ba8eef8aa7a96654a450d8ae80783554b5.png)Willman和Bolt的速度完全相同，所以他们比赛的结果总是平局。这对组织者来说是个问题，因为他们想要一个获胜者。

在观看之前的比赛时，组织者注意到Willman只能迈出长度为 $w$ 米的步伐，而Bolt只能迈出长度为 $b$ 米的步伐。组织者决定稍微改变一下比赛规则。现在，在赛道的尽头会有一个深渊，获胜者将被宣布为能够从赛道起点跑得更远的运动员（起点不会被任何运动员改变）。

请注意，两位运动员都不能无限远地跑，因为他们都会在某个时刻遇到这样一个点，再多走一步就会导致他们掉进深渊。换句话说，如果运动员所有步伐的总长度小于或等于选定的距离 $L$，那么他就不会掉进深渊。

由于组织者非常公平，他们将把赛道长度设置为从1到 $t$（两者都包括）之间随机且均匀选择的整数。那么今天Willman和Bolt再次平局的概率是多少？

## 说明/提示
在第一个样例中，如果选择1、6或7作为赛道长度，Willman和Bolt将打成平手。

## 样例 #1
### 输入
```
10 3 2
```
### 输出
```
3/10
```
## 样例 #2
### 输入
```
7 1 2
```
### 输出
```
3/7
```

### 算法分类
数学

### 综合分析与结论
该题解思路清晰，通过分析得出两种两人平局的情况：一是赛道长度小于两人步长的最小值，此时两人一步都不能走，距离相等；二是赛道长度是两人步长最小公倍数的倍数，且在此基础上可再延长小于两人步长最小值的长度，两人能走的距离也相等。最后通过统计这两种情况在总赛道长度范围[1, t]内的数量，并进行约分得到平局概率。时间复杂度为 $\mathcal{O}(1)$，代码简洁明了，通过模板实现输入输出，且考虑到数据范围使用了`__int128`类型。

### 所选的题解
 - **星级**：5星
 - **关键亮点**：思路清晰，准确分析出平局的两种情况，利用最小公倍数和步长最小值来统计平局数量，时间复杂度低，代码简洁且考虑到大数据范围。
 - **重点代码**：
```cpp
signed main() {
    t = read<ull>(), w = read<ull>(), b = read<ull>();
    ull lcm = w / __gcd(w, b) * b;
    ans = (t / lcm - 1) * min(w, b) // lcm(w, b)的倍数及延长
         + min({w, b, t % lcm + 1}); // 最后不能超过 t，特判
    ans += min(w, b) - 1; // 两人都走不了
    ull g = __gcd(t, ans); // 约分
    print(ans / g, '/'), print(t / g);
    return 0;
}
```
核心实现思想：先计算出两人步长的最小公倍数`lcm`，根据上述两种平局情况统计满足条件的赛道长度数量`ans`，最后对`ans`和总赛道长度范围`t`进行约分，输出平局概率。

### 最优关键思路或技巧
通过分析比赛规则，将问题转化为数学问题，利用最小公倍数和步长最小值的关系来统计满足平局条件的赛道长度数量，这种数学分析的思维方式是解题关键。同时，考虑到大数据范围使用`__int128`类型保证数据计算的准确性。

### 拓展
同类型题通常围绕数论相关知识，例如涉及最大公约数、最小公倍数、整除关系等概念，通过分析条件找到满足特定要求的数值数量或概率。类似算法套路是对题目条件进行深入分析，转化为数学模型，利用数论知识求解。

### 推荐题目
 - [P1029 最大公约数和最小公倍数问题](https://www.luogu.com.cn/problem/P1029)：通过已知的最大公约数和最小公倍数，求满足条件的数对数量，考察数论中最大公约数和最小公倍数的关系。
 - [P1403 [AHOI2005]约数研究](https://www.luogu.com.cn/problem/P1403)：计算1到n每个数的约数个数之和，考察约数相关的数学计算。
 - [P2613 【模板】有理数取余](https://www.luogu.com.cn/problem/P2613)：涉及有理数的取余运算，结合数论中的逆元等知识求解，与本题在数学运算和数论应用上有相似之处。 

---
处理用时：40.78秒