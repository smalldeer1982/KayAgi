# 题目信息

# Game with modulo

## 题目描述

This is an interactive problem.

Vasya and Petya are going to play the following game: Petya has some positive integer number $ a $ . After that Vasya should guess this number using the following questions. He can say a pair of non-negative integer numbers $ (x, y) $ . Petya will answer him:

- "x", if $ (x \bmod a) \geq (y \bmod a) $ .
- "y", if $ (x \bmod a) < (y \bmod a) $ .

We define $ (x \bmod a) $ as a remainder of division $ x $ by $ a $ .

Vasya should guess the number $ a $ using no more, than 60 questions.

It's guaranteed that Petya has a number, that satisfies the inequality $ 1 \leq a \leq 10^9 $ .

Help Vasya playing this game and write a program, that will guess the number $ a $ .

## 说明/提示

In the first test, you should play $ 3 $ games with Petya's numbers $ 1 $ , $ 2 $ and $ 3 $ .

In the first game, Petya will answer "x" (without quotes) to any question, because $ (x \bmod 1) = 0 $ for any integer $ x $ .

In the second game, if you will ask pair $ (0, 0) $ , the answer will be "x" (without quotes), because $ (0 \bmod 2) \geq (0 \bmod 2) $ . But if you will ask pair $ (2, 5) $ , the answer will be "y" (without quotes), because $ (2 \bmod 2) < (5 \bmod 2) $ , because $ (2 \bmod 2) = 0 $ and $ (5 \bmod 2) = 1 $ .

## 样例 #1

### 输入

```
start
x
x
start
x
x
y
start
x
x
y
y
end
```

### 输出

```
? 0 0
? 10 1
! 1
? 0 0
? 3 4
? 2 5
! 2
? 2 4
? 2 5
? 3 10
? 9 1
! 3
```

# AI分析结果

### 题目翻译
这是一道交互式问题。

瓦西亚（Vasya）和彼佳（Petya）准备玩以下游戏：彼佳有一个正整数 $a$。之后，瓦西亚需要通过以下问题来猜出这个数字。他可以说出一对非负整数 $(x, y)$。彼佳会这样回答他：
- 如果 $(x \bmod a) \geq (y \bmod a)$，则回答 “x”。
- 如果 $(x \bmod a) < (y \bmod a)$，则回答 “y”。

我们将 $(x \bmod a)$ 定义为 $x$ 除以 $a$ 的余数。

瓦西亚需要在不超过 60 次提问的情况下猜出数字 $a$。

保证彼佳的数字满足不等式 $1 \leq a \leq 10^9$。

帮助瓦西亚玩这个游戏，并编写一个程序来猜出数字 $a$。

### 算法分类
二分

### 综合分析与结论
这些题解的核心思路都是利用二分法来猜出数字 $a$。首先通过某种方式找到一个范围 $[x, 2x]$，使得 $x \leq a \leq 2x$，然后在这个范围内进行二分查找。大部分题解采用倍增的方式来确定这个范围，即不断询问 $(x, 2x)$，直到满足条件。部分题解还考虑了特判情况，如 $a = 1$ 时的情况。而 acniu 的题解采用了随机化乱搞的做法，通过随机选取数对，利用数对的性质来定位 $a$ 的倍数，再对其质因子进行二分处理，不过这种方法存在一定的不确定性，询问次数可能会超过 60 次。

### 所选题解
- **作者：shucai (赞：7)  4星**
  - **关键亮点**：思路清晰，代码简洁，详细阐述了利用二分思想解决问题的过程，先通过倍增确定范围，再在范围内二分查找。
- **作者：PPL_ (赞：2)  4星**
  - **关键亮点**：对解题思路的分析较为全面，提到了倍增和二分的结合，并且对无解情况进行了一定的讨论，代码实现规范。
- **作者：miaokehao (赞：2)  4星**
  - **关键亮点**：思路简洁明了，代码实现直接，同样采用了先倍增后二分的方法，注释较少但逻辑清晰。

### 重点代码
以下是 shucai 题解的核心代码：
```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
string s;
int len;
inline void check(int &l, int &r) {
    do {
        printf("? %lld %lld\n", l, r);
        cin >> s;

        if (s[0] == 'y') {
            l = r;
            r <<= 1;
        }
    } while (s[0] == 'y');
}
signed main() {
    cin >> s;
    while (s.size() != 3 && s.size() != 7) {
        int l = 0, r = 1;
        check(l, r);
        while (l + 1 < r) {
            int mid = (l + r) >> 1;
            printf("? %lld %lld\n", mid, l);
            cin >> s;
            if (s[0] == 'x')
                l = mid;
            else
                r = mid;
        }
        printf("! %lld\n", l + 1);
        cin >> s;
    }
    return 0;
}
```
**核心实现思想**：`check` 函数通过不断询问 $(l, r)$，若回答为 “y” 则更新 $l$ 和 $r$，直到回答为 “x”，从而确定一个范围 $[l, r]$ 使得 $l \leq a \leq r$。在 `main` 函数中，先调用 `check` 函数确定范围，然后在这个范围内进行二分查找，最终猜出数字 $a$。

### 最优关键思路或技巧
- 利用倍增的思想快速确定 $a$ 的大致范围 $[x, 2x]$，将问题规模缩小。
- 在确定的范围内使用二分查找，每次询问可以将范围缩小一半，保证在不超过 60 次询问的情况下猜出 $a$。

### 可拓展之处
同类型题或类似算法套路：
- 其他交互式猜数字问题，可能规则不同，但都可以尝试利用二分、倍增等思想来缩小范围，减少询问次数。
- 一些需要通过不断询问获取信息来确定某个值的问题，也可以借鉴这种先确定范围再二分查找的思路。

### 推荐洛谷题目
- P2249 【深基13.例1】查找
- P1873 砍树
- P3853 [TJOI2007]路标设置

### 个人心得摘录与总结
- **PPL_**：提到这是人生第一道交互题，感觉很激动又有挑战，说明交互题对于新手来说有一定的新鲜感和难度。
- **acniu**：采用随机化乱搞做法，实测 $a$ 取 $10^9$ 时容易被卡，平均需要 40 次询问，10000 次测试中一般只有不到 30 次会询问过多，最大询问次数一般不超过 80，说明随机化算法存在一定的不确定性，在实际应用中需要考虑其稳定性。 

---
处理用时：38.46秒