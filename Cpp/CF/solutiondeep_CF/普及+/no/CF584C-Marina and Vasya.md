# 题目信息

# Marina and Vasya

## 题目描述

Marina loves strings of the same length and Vasya loves when there is a third string, different from them in exactly $ t $ characters. Help Vasya find at least one such string.

More formally, you are given two strings $ s_{1} $ , $ s_{2} $ of length $ n $ and number $ t $ . Let's denote as $ f(a,b) $ the number of characters in which strings $ a $ and $ b $ are different. Then your task will be to find any string $ s_{3} $ of length $ n $ , such that $ f(s_{1},s_{3})=f(s_{2},s_{3})=t $ . If there is no such string, print $ -1 $ .

## 样例 #1

### 输入

```
3 2
abc
xyc
```

### 输出

```
ayd```

## 样例 #2

### 输入

```
1 0
c
b
```

### 输出

```
-1
```

# AI分析结果

### 题目内容
# Marina和Vasya
## 题目描述
Marina喜欢长度相同的字符串，而Vasya喜欢存在一个与它们恰好在 $t$ 个字符上不同的第三个字符串。帮助Vasya找到至少一个这样的字符串。
更正式地说，给定两个长度为 $n$ 的字符串 $s_{1}$ 、 $s_{2}$ 以及数字 $t$ 。用 $f(a,b)$ 表示字符串 $a$ 和 $b$ 不同字符的数量。那么你的任务是找到任意一个长度为 $n$ 的字符串 $s_{3}$ ，使得 $f(s_{1},s_{3}) = f(s_{2},s_{3}) = t$ 。如果不存在这样的字符串，则输出 $-1$ 。
## 样例 #1
### 输入
```
3 2
abc
xyc
```
### 输出
```
ayd
```
## 样例 #2
### 输入
```
1 0
c
b
```
### 输出
```
-1
```
### 算法分类
构造
### 题解综合分析与结论
三道题解均围绕如何构造出满足条件的字符串展开。xzy090626提供了两种构造方案，第一种先将答案串设为 $a$ 再修改，对 $a_i\neq b_i$ 的位置先改成既不是 $a_i$ 也不是 $b_i$ 的字符，之后根据当前不同位置个数 $d$ 与 $t$ 的大小关系进行调整；第二种预处理时让答案串每个位置都与两个串不同，操作时只减少不同位置个数，且注意修改顺序。luo_shen先判断无解情况，即当 $t\times 2 \lt$ 两串不同字符位置总数 $tot$ 时无解，有解时先平均分配两串不同位置，再进行调整。三道题解思路各有特点，xzy090626的两种方法思路较为清晰，代码实现相对简洁；luo_shen的方法结合了对无解情况的判断，但代码相对复杂一些。
### 所选的题解
无（所有题解均未达到4星）
### 通用建议与扩展思路
对于此类构造题，关键在于找到合理的构造策略。可以先从简单情况入手分析，如本题中先考虑无解的条件，再思考有解时如何逐步构造出满足条件的字符串。在实现过程中，要注意对边界条件的处理以及操作顺序对结果的影响。同类型题通常围绕字符串的特定性质构造新字符串，可以多练习此类题目，加深对字符串操作和逻辑构造的理解。
### 推荐题目
- [P1004 方格取数](https://www.luogu.com.cn/problem/P1004)：涉及对二维方格数据的处理与构造路径获取最大价值，与本题类似在于需要按一定规则构造方案。
- [P1242 新汉诺塔](https://www.luogu.com.cn/problem/P1242)：汉诺塔问题变种，需构造合理的移动方案，锻炼构造思路。
- [P1433 吃奶酪](https://www.luogu.com.cn/problem/P1433)：在给定条件下构造遍历路径，与本题构造满足条件字符串思路类似。 

---
处理用时：39.63秒