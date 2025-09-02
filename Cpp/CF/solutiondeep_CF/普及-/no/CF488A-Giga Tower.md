# 题目信息

# Giga Tower

## 题目描述

Giga Tower is the tallest and deepest building in Cyberland. There are $ 17777777777 $ floors, numbered from $ -8888888888 $ to $ 8888888888 $ . In particular, there is floor $ 0 $ between floor $ -1 $ and floor $ 1 $ . Every day, thousands of tourists come to this place to enjoy the wonderful view.

In Cyberland, it is believed that the number "8" is a lucky number (that's why Giga Tower has $ 8888888888 $ floors above the ground), and, an integer is lucky, if and only if its decimal notation contains at least one digit "8". For example, $ 8,-180,808 $ are all lucky while $ 42,-10 $ are not. In the Giga Tower, if you write code at a floor with lucky floor number, good luck will always be with you (Well, this round is #278, also lucky, huh?).

Tourist Henry goes to the tower to seek good luck. Now he is at the floor numbered $ a $ . He wants to find the minimum positive integer $ b $ , such that, if he walks $ b $ floors higher, he will arrive at a floor with a lucky number.

## 说明/提示

For the first sample, he has to arrive at the floor numbered $ 180 $ .

For the second sample, he will arrive at $ 8 $ .

Note that $ b $ should be positive, so the answer for the third sample is $ 10 $ , not $ 0 $ .

## 样例 #1

### 输入

```
179
```

### 输出

```
1
```

## 样例 #2

### 输入

```
-1
```

### 输出

```
9
```

## 样例 #3

### 输入

```
18
```

### 输出

```
10
```

# AI分析结果

【题目内容（中文重写）】
# Giga Tower

## 题目描述
Giga Tower 是赛博世界中最高且最深的建筑。它共有 17777777777 层，楼层编号从 -8888888888 到 8888888888。特别地，在 -1 层和 1 层之间有 0 层。每天，成千上万的游客来到这里欣赏美妙的景色。

在赛博世界中，人们认为数字“8”是幸运数字（这就是为什么 Giga Tower 有 8888888888 层在地面以上）。一个整数是幸运数字，当且仅当它的十进制表示中至少包含一个数字“8”。例如，8、-180、808 都是幸运数字，而 42、-10 不是。在 Giga Tower 中，如果你在楼层编号为幸运数字的楼层编写代码，好运将一直伴随着你（嗯，这一轮是第 278 轮，也是幸运数字，对吧？）。

游客 Henry 前往塔楼寻求好运。现在他在编号为 a 的楼层。他想找到最小的正整数 b，使得如果他向上走 b 层，就会到达一个楼层编号为幸运数字的楼层。

## 说明/提示
对于第一个样例，他必须到达编号为 180 的楼层。
对于第二个样例，他将到达 8 层。
请注意，b 必须是正整数，所以第三个样例的答案是 10，而不是 0。

## 样例 #1
### 输入
```
179
```
### 输出
```
1
```

## 样例 #2
### 输入
```
-1
```
### 输出
```
9
```

## 样例 #3
### 输入
```
18
```
### 输出
```
10
```

【算法分类】
枚举

【综合分析与结论】
这些题解的核心思路都是通过枚举正整数 b，判断 a + b 是否为幸运数字（即十进制表示中至少包含一个数字 8），直到找到满足条件的最小正整数 b。

### 思路对比
- 大部分题解采用直接枚举 b 从 1 开始递增，不断判断 a + b 是否为幸运数字。
- Cult_style 的题解将正整数和负数分开讨论，正整数从 1 到 10 枚举，负数部分先转化为正整数再进行分析。

### 算法要点
- 都需要实现一个判断函数，用于判断一个数是否为幸运数字，一般通过取模和除法运算逐位判断。
- 枚举时要注意 b 是正整数，从 1 开始。

### 解决难点
- 处理负数时，要先取绝对值再进行判断，避免取模得到负数。
- 原数本身是幸运数字时，要保证 b 为正整数，所以答案不是 0。

### 评分
- damage：4 星，思路清晰，代码简洁，对关键步骤有详细注释。
- 伟大的王夫子：4 星，思路和代码都很清晰，对取绝对值的原因有解释。
- lxgw：4 星，思路明确，代码规范，对需要注意的点有说明。

【所选题解】
- damage（4 星）：关键亮点是思路清晰，代码简洁，对负数取绝对值和 b 初始值的设置有详细说明。
- 伟大的王夫子（4 星）：关键亮点是对取绝对值的原因进行了解释，代码可读性高。
- lxgw（4 星）：关键亮点是思路明确，对需要注意的点有详细说明，代码规范。

【重点代码】
```cpp
// damage 的判断函数
bool check(int x) {
    if(x < 0) x = -x;
    while(x) {
        if(x % 10 == 8) return true;
        x /= 10;
    }
    return false;
}
```
核心实现思想：通过取模运算获取数的每一位，判断是否为 8，若有则返回 true，否则返回 false。

【可拓展之处】
同类型题可能会改变幸运数字的定义，如包含特定数字组合或满足特定数学条件的数字为幸运数字，解题思路仍可采用枚举法，关键在于修改判断函数。

【推荐题目】
- P1036 选数
- P1047 校门外的树
- P1059 明明的随机数

【个人心得】
Cult_style：“是负数的话，一开始我一点头绪也没有，后面想了想，唉，不管了，先把负数变成正整数再说”，总结：遇到复杂情况时，可以先尝试将问题简化，转化为熟悉的情况再进行分析。 

---
处理用时：26.90秒