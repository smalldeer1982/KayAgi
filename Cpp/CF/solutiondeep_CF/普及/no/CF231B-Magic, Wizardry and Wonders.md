# 题目信息

# Magic, Wizardry and Wonders

## 题目描述

Vasya the Great Magician and Conjurer loves all kinds of miracles and wizardry. In one wave of a magic wand he can turn an object into something else. But, as you all know, there is no better magic in the Universe than the magic of numbers. That's why Vasya adores math and spends a lot of time turning some numbers into some other ones.

This morning he has $ n $ cards with integers lined up in front of him. Each integer is not less than 1, but not greater than $ l $ . When Vasya waves his magic wand, two rightmost cards vanish from the line and a new card magically appears in their place. It contains the difference between the left and the right numbers on the two vanished cards. Vasya was very interested to know what would happen next, and so he waved with his magic wand on and on, until the table had a single card left.

Suppose that Vasya originally had the following cards: 4, 1, 1, 3 (listed from left to right). Then after the first wave the line would be: 4, 1, -2, and after the second one: 4, 3, and after the third one the table would have a single card with number 1.

Please note that in spite of the fact that initially all the numbers on the cards were not less than 1 and not greater than $ l $ , the numbers on the appearing cards can be anything, no restrictions are imposed on them.

It is now evening. Vasya is very tired and wants to return everything back, but does not remember which cards he had in the morning. He only remembers that there were $ n $ cards, they contained integers from 1 to $ l $ , and after all magical actions he was left with a single card containing number $ d $ .

Help Vasya to recover the initial set of cards with numbers.

## 样例 #1

### 输入

```
3 3 2
```

### 输出

```
2 1 2 ```

## 样例 #2

### 输入

```
5 -4 3
```

### 输出

```
-1
```

## 样例 #3

### 输入

```
5 -4 4
```

### 输出

```
2 4 1 4 1 ```

# AI分析结果



# Magic, Wizardry and Wonders

## 题目描述

伟大魔术师Vasya面前排列着$n$张卡牌，每张卡牌上的数字都是1到$l$之间的整数。每次施法时，他将最右侧两张卡牌合并为它们的差值（左数减右数），直到只剩一张卡牌显示数字$d$。请根据$n$、$d$和$l$还原原始卡牌序列，或判断无解。

## 样例

### 样例1输入
```
3 3 2
```
### 样例1输出
```
2 1 2
```

### 样例2输入
```
5 -4 3
```
### 样例2输出
```
-1
```

### 样例3输入
```
5 -4 4
```
### 样例3输出
```
2 4 1 4 1
```

---

**算法分类**：构造

---

## 题解分析与结论

### 核心思路
通过数学分析发现，最终结果$d$等于奇数位之和减去偶数位之和。构造时采用贪心策略：
1. **极值判定**：计算奇数位全取$l$、偶数位全取1的最大$d_{max}$，以及奇数位全取1、偶数位全取$l$的最小$d_{min}$，若$d$超出此范围则无解
2. **贪心构造**：从首位开始，若当前剩余$d$为正则取最大$l$，否则取1，并动态调整剩余$d$
3. **末尾修正**：在最后一位通过调整消除剩余差值

### 精选题解

#### 题解作者：三点水一个各（评分：★★★★☆）
**关键亮点**：
- 通过奇偶位贡献拆分快速确定构造方向
- 贪心策略简洁高效，代码实现仅需O(n)时间
- 末尾修正技巧巧妙处理边界问题

**核心代码**：
```cpp
for(int i=1;i<=n;++i) {
    if(d>0) {
        a[i]=l; 
        d = l - d;  // 贪心取最大值并调整剩余差值
    } else {
        a[i]=1;
        d = 1 - d;  // 处理负差值情况
    }
}
a[n] -= d;  // 末尾修正
```

**个人心得**：
- 调试中发现必须将最终差值完全消除，否则会残留误差
- 通过极值计算提前排除无效情况，减少无效构造

---

## 拓展与练习建议

**类似构造技巧**：
- 交替符号序列构造（如CF1538D）
- 动态调整极值的贪心策略（如洛谷P1007 接水问题）

**推荐练习题**：
1. P1005 [矩阵取数游戏]：极值贪心+高精度处理
2. P1070 [道路游戏]：动态调整贡献的构造思想
3. P5662 [纪念品]：多维度的极值贪心策略

---
处理用时：135.64秒