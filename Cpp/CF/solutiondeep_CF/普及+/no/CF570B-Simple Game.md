# 题目信息

# Simple Game

## 题目描述

One day Misha and Andrew were playing a very simple game. First, each player chooses an integer in the range from $ 1 $ to $ n $ . Let's assume that Misha chose number $ m $ , and Andrew chose number $ a $ .

Then, by using a random generator they choose a random integer $ c $ in the range between $ 1 $ and $ n $ (any integer from $ 1 $ to $ n $ is chosen with the same probability), after which the winner is the player, whose number was closer to $ c $ . The boys agreed that if $ m $ and $ a $ are located on the same distance from $ c $ , Misha wins.

Andrew wants to win very much, so he asks you to help him. You know the number selected by Misha, and number $ n $ . You need to determine which value of $ a $ Andrew must choose, so that the probability of his victory is the highest possible.

More formally, you need to find such integer $ a $ ( $ 1<=a<=n $ ), that the probability that ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF570B/fcf679a711cde29d2e9f9a082e28c313061224e7.png) is maximal, where $ c $ is the equiprobably chosen integer from $ 1 $ to $ n $ (inclusive).

## 说明/提示

In the first sample test: Andrew wins if $ c $ is equal to $ 2 $ or $ 3 $ . The probability that Andrew wins is $ 2/3 $ . If Andrew chooses $ a=3 $ , the probability of winning will be $ 1/3 $ . If $ a=1 $ , the probability of winning is $ 0 $ .

In the second sample test: Andrew wins if $ c $ is equal to $ 1 $ and $ 2 $ . The probability that Andrew wins is $ 1/2 $ . For other choices of $ a $ the probability of winning is less.

## 样例 #1

### 输入

```
3 1
```

### 输出

```
2```

## 样例 #2

### 输入

```
4 3
```

### 输出

```
2```

# AI分析结果

### 题目内容
# 简单游戏

## 题目描述
有一天，米沙和安德鲁在玩一个非常简单的游戏。首先，每个玩家从1到n的范围内选择一个整数。假设米沙选择了数字m，安德鲁选择了数字a。

然后，通过随机生成器，他们在1到n的范围内选择一个随机整数c（从1到n的任何整数被选中的概率相同），之后，数字离c更近的玩家获胜。男孩们约定，如果m和a与c的距离相同，米沙获胜。

安德鲁非常想赢，所以他请你帮助他。你知道米沙选择的数字和数字n。你需要确定安德鲁必须选择哪个值的a，以便他获胜的概率尽可能高。

更正式地说，你需要找到这样的整数a（1 <= a <= n），使得概率$P(|c - a| < |c - m|)$最大，其中c是从1到n（包括1和n）中等概率选择的整数。

## 说明/提示
在第一个示例测试中：如果c等于2或3，安德鲁获胜。安德鲁获胜的概率是2/3。如果安德鲁选择a = 3，获胜的概率将是1/3。如果a = 1，获胜的概率是0。

在第二个示例测试中：如果c等于1和2，安德鲁获胜。安德鲁获胜的概率是1/2。对于a的其他选择，获胜的概率更小。

## 样例 #1
### 输入
```
3 1
```
### 输出
```
2
```

## 样例 #2
### 输入
```
4 3
```
### 输出
```
2
```

### 算法分类
数学

### 题解综合分析与结论
所有题解核心思路均围绕寻找使安德鲁获胜概率最大的a值。大多题解通过分析绝对值不等式$|c - a| < |c - m|$，得出a应在m附近（m - 1或m + 1），再根据m与n的关系确定最终a值。部分题解利用数轴、数形结合等方式辅助理解。所有题解都注意到n = 1且m = 1时需特判输出1。各题解思路和实现较为相似，主要区别在于分析过程的详细程度与代码风格。

### 所选的题解
 - **作者：LKY928261 (5星)**
    - **关键亮点**：思路清晰简洁，先利用数学知识分析出$|c - a| < |c - m|$成立的三种情况，进而得出a取值规律，代码简洁明了。
    - **个人心得**：提到输入`1 1`时是个巨坑，需特判。
    - **重点代码**：
```cpp
if(n==1&&m==1)cout<<"1\n";//巨坑
else if(m<=n/2)cout<<m+1<<"\n";
else cout<<m-1<<"\n";
```
核心实现思想：先特判特殊情况n = 1且m = 1，然后根据m与n / 2的大小关系确定a取值。
 - **作者：珅肐 (4星)**
    - **关键亮点**：直接从使不等式成立角度出发，指出a应选在m附近，通过比较区间大小确定a选m - 1还是m + 1，思路直接。
    - **重点代码**：
```cpp
if(n==1 && m==1){puts("1");return 0;}
if(m-1>=n-m)printf("%d\n",m-1);
else printf("%d\n",m+1);
```
核心实现思想：先处理特殊情况，再通过比较m - 1与n - m的大小决定a值。
 - **作者：伟大的王夫子 (4星)**
    - **关键亮点**：通过画图辅助理解，分a < m和a > m两种情况讨论满足条件的c的取值数量，通过解不等式确定最终a的取值。
    - **重点代码**：
```cpp
if (m == 1) printf("%d\n", min(m + 1, n));
else if (n >= 2 * m) printf("%d", m + 1);
else printf("%d", m - 1);
```
核心实现思想：先处理m = 1的情况，再根据n与2m的大小关系确定a值。

### 最优关键思路或技巧
通过分析$|c - a| < |c - m|$这个绝对值不等式，结合数轴等工具，快速得出a应在m的相邻位置（m - 1或m + 1），再根据m与n的关系确定最终a值，这种利用数学关系简化问题的思维方式是关键。

### 拓展
此类题目属于基于概率和数学关系的逻辑推理题，类似套路是通过分析题目中的条件建立数学模型（如不等式、等式等），再结合边界条件和特殊情况求解。同类型题可考虑一些在特定规则下求最优策略或概率的问题。

### 相似知识点洛谷题目
 - [P1085 不高兴的津津](https://www.luogu.com.cn/problem/P1085)：通过分析条件得出最优选择，涉及简单数学推理。
 - [P1149 火柴棒等式](https://www.luogu.com.cn/problem/P1149)：需要通过枚举和数学运算找到满足等式的数量，与本题分析条件找最优解思路类似。
 - [P1247 取火柴游戏](https://www.luogu.com.cn/problem/P1247)：利用数学策略确定游戏中的最优取法，和本题寻找获胜最优策略类似。 

---
处理用时：43.47秒