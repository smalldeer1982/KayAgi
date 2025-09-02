# 题目信息

# New Year Present

## 题目描述

The New Year is coming! That's why many people today are busy preparing New Year presents. Vasily the Programmer is no exception.

Vasily knows that the best present is (no, it's not a contest) money. He's put $ n $ empty wallets from left to right in a row and decided how much money to put in what wallet. Vasily decided to put $ a_{i} $ coins to the $ i $ -th wallet from the left.

Vasily is a very busy man, so the money are sorted into the bags by his robot. Initially, the robot stands by the leftmost wallet in the row. The robot can follow instructions of three types: go to the wallet that is to the left of the current one (if such wallet exists), go to the wallet that is to the right of the current one (if such wallet exists), put a coin to the current wallet. Due to some technical malfunctions the robot cannot follow two "put a coin" instructions in a row.

Vasily doesn't want to wait for long, so he wants to write a program for the robot that contains at most $ 10^{6} $ operations (not necessarily minimum in length) the robot can use to put coins into the wallets. Help him.

## 样例 #1

### 输入

```
2
1 2
```

### 输出

```
PRPLRP```

## 样例 #2

### 输入

```
4
0 2 0 2
```

### 输出

```
RPRRPLLPLRRRP```

# AI分析结果

### 题目重写
# 新年礼物

## 题目描述
新年就要到了！这就是为什么现在很多人都在忙着准备新年礼物。程序员瓦西里也不例外。

瓦西里知道，最好的礼物（不，不是一场竞赛）是钱。他从左到右把 $n$ 个空钱包排成一排，并决定在每个钱包里放多少钱。瓦西里决定在从左数第 $i$ 个钱包里放 $a_{i}$ 枚硬币。

瓦西里是个大忙人，所以钱由他的机器人放进钱包里。最初，机器人站在这排钱包最左边的那个旁边。机器人可以遵循三种类型的指令：走到当前钱包左边的钱包（如果存在这样的钱包），走到当前钱包右边的钱包（如果存在这样的钱包），在当前钱包里放一枚硬币。由于一些技术故障，机器人不能连续执行两条“放一枚硬币”的指令。

瓦西里不想等太久，所以他想为机器人编写一个程序，该程序包含最多 $10^{6}$ 次操作（不一定是最短长度），机器人可以用这个程序将硬币放入钱包。帮帮他。

## 样例 #1
### 输入
```
2
1 2
```
### 输出
```
PRPLRP```
## 样例 #2
### 输入
```
4
0 2 0 2
```
### 输出
```
RPRRPLLPLRRRP```
### 算法分类
模拟
### 综合分析与结论
这些题解的核心思路都是围绕机器人放硬币的规则进行模拟。主要差异在于具体的模拟方式和处理细节。所有题解都利用题目不要求最短方案，操作数上限远大于实际可能的操作数这一条件，采用较为直接的模拟策略。部分题解通过来回移动来避免连续放硬币的问题，部分题解则是按顺序遍历钱包，在放硬币时根据位置进行特殊处理。整体来看，各题解思路清晰，但在代码实现的简洁性和可读性上有所差异。

### 所选的题解
无

### 通用建议与扩展思路
通用建议：在处理这类模拟题时，要清晰梳理题目规则，尤其是像不能连续放硬币、边界位置限制等关键条件。代码实现上，注意逻辑的清晰性和变量命名的规范性，以便于理解和调试。
扩展思路：类似题目可能会增加更多复杂条件，如机器人移动消耗能量、不同位置放硬币有不同要求等。可通过总结本题处理特殊条件的方式，举一反三，在遇到新条件时，合理设计模拟流程。

### 洛谷相似题目推荐
- [P1032 字串变换](https://www.luogu.com.cn/problem/P1032)
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
- [P1443 马的遍历](https://www.luogu.com.cn/problem/P1443)

### 个人心得摘录与总结
“封禁用户”提到因为不越界的条件导致花费2.5小时研究为何WA，说明在处理模拟题时，边界条件的处理至关重要，稍不注意就容易出错。在编写代码时，要对边界情况进行全面细致的检查和处理。 

---
处理用时：22.68秒