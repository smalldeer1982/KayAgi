# 题目信息

# Rings

## 题目描述

Frodo was caught by Saruman. He tore a pouch from Frodo's neck, shook out its contents —there was a pile of different rings: gold and silver..."How am I to tell which is the One?!" the mage howled.

"Throw them one by one into the Cracks of Doom and watch when Mordor falls!"





Somewhere in a parallel Middle-earth, when Saruman caught Frodo, he only found $ n $ rings. And the $ i $ -th ring was either gold or silver. For convenience Saruman wrote down a binary string $ s $ of $ n $ characters, where the $ i $ -th character was 0 if the $ i $ -th ring was gold, and 1 if it was silver.

Saruman has a magic function $ f $ , which takes a binary string and returns a number obtained by converting the string into a binary number and then converting the binary number into a decimal number. For example, $ f(001010) = 10, f(111) = 7, f(11011101) = 221 $ .

Saruman, however, thinks that the order of the rings plays some important role. He wants to find $ 2 $ pairs of integers $ (l_1, r_1), (l_2, r_2) $ , such that:

- $ 1 \le l_1 \le n $ , $ 1 \le r_1 \le n $ , $ r_1-l_1+1\ge \lfloor \frac{n}{2} \rfloor $
- $ 1 \le l_2 \le n $ , $ 1 \le r_2 \le n $ , $ r_2-l_2+1\ge \lfloor \frac{n}{2} \rfloor $
- Pairs $ (l_1, r_1) $ and $ (l_2, r_2) $ are distinct. That is, at least one of $ l_1 \neq l_2 $ and $ r_1 \neq r_2 $ must hold.
- Let $ t $ be the substring $ s[l_1:r_1] $ of $ s $ , and $ w $ be the substring $ s[l_2:r_2] $ of $ s $ . Then there exists non-negative integer $ k $ , such that $ f(t) = f(w) \cdot k $ .

Here substring $ s[l:r] $ denotes $ s_ls_{l+1}\ldots s_{r-1}s_r $ , and $ \lfloor x \rfloor $ denotes rounding the number down to the nearest integer.

Help Saruman solve this problem! It is guaranteed that under the constraints of the problem at least one solution exists.

## 说明/提示

In the first testcase $ f(t) = f(1111) = 15 $ , $ f(w) = f(101) = 5 $ .

In the second testcase $ f(t) = f(111000111) = 455 $ , $ f(w) = f(000111) = 7 $ .

In the third testcase $ f(t) = f(0000) = 0 $ , $ f(w) = f(1000) = 8 $ .

In the fourth testcase $ f(t) = f(11011) = 27 $ , $ f(w) = f(011) = 3 $ .

In the fifth testcase $ f(t) = f(001111) = 15 $ , $ f(w) = f(011) = 3 $ .

## 样例 #1

### 输入

```
7
6
101111
9
111000111
8
10000000
5
11011
6
001111
3
101
30
100000000000000100000000000000```

### 输出

```
3 6 1 3
1 9 4 9
5 8 1 4
1 5 3 5
1 6 2 4
1 2 2 3
1 15 16 30```

# AI分析结果

### 题目内容重写

**题目描述**

Frodo 被 Saruman 抓住了。Saruman 从 Frodo 的脖子上扯下了一个小袋子，倒出了里面的东西——一堆不同的戒指：金戒指和银戒指……“我怎么分辨哪个是魔戒？！”巫师咆哮道。

“把它们一个一个扔进末日裂缝，看着魔多何时陷落！”

在某个平行的中土世界，当 Saruman 抓住 Frodo 时，他只找到了 $n$ 个戒指。第 $i$ 个戒指要么是金的，要么是银的。为了方便，Saruman 写下一个长度为 $n$ 的二进制字符串 $s$，其中第 $i$ 个字符为 0 表示第 $i$ 个戒指是金的，为 1 表示是银的。

Saruman 有一个魔法函数 $f$，它接受一个二进制字符串并返回一个数字，该数字是通过将字符串转换为二进制数，然后再转换为十进制数得到的。例如，$f(001010) = 10, f(111) = 7, f(11011101) = 221$。

然而，Saruman 认为戒指的顺序起着重要的作用。他想要找到两对整数 $(l_1, r_1), (l_2, r_2)$，满足以下条件：

1. $1 \le l_1 \le n$，$1 \le r_1 \le n$，$r_1-l_1+1\ge \lfloor \frac{n}{2} \rfloor$
2. $1 \le l_2 \le n$，$1 \le r_2 \le n$，$r_2-l_2+1\ge \lfloor \frac{n}{2} \rfloor$
3. 两对 $(l_1, r_1)$ 和 $(l_2, r_2)$ 必须不同，即至少有一个 $l_1 \neq l_2$ 或 $r_1 \neq r_2$。
4. 设 $t$ 为 $s[l_1:r_1]$ 的子串，$w$ 为 $s[l_2:r_2]$ 的子串。则存在一个非负整数 $k$，使得 $f(t) = f(w) \cdot k$。

帮助 Saruman 解决这个问题！题目保证在给定的约束下至少存在一个解。

### 算法分类
构造

### 题解分析与结论

该题的核心思路是通过构造满足条件的子串对来解决问题。大多数题解都利用了二进制数的特性，特别是通过添加或删除前导零或后缀零来构造倍数关系。具体来说，题解通常分为两种情况：

1. **字符串中存在0**：通过找到第一个0的位置，构造两个子串，使得其中一个子串是另一个子串的倍数。例如，如果0在前半部分，则构造 $[i, n]$ 和 $[i+1, n]$；如果0在后半部分，则构造 $[1, i]$ 和 $[1, i-1]$。
2. **字符串全为1**：构造两个长度不同的全1子串，使得其中一个子串是另一个子串的倍数。例如，构造 $[1, n/2]$ 和 $[1, 2*(n/2)]$。

### 评分较高的题解

#### 题解1：作者：Jairon314 (赞：5)
**星级：5星**
**关键亮点**：
- 思路清晰，直接利用了二进制数的特性，通过添加或删除前导零或后缀零来构造倍数关系。
- 代码简洁，逻辑明确，易于理解。
- 处理了全1字符串的特殊情况。

**核心代码**：
```cpp
for(int i=1;i<=n;i++){if(s[i]=='0'){pos_0=i;i=n+1;}}
if(pos_0==-1){
    out(1),out(2*(n/2)),out(1),outn(n/2);
} else if(pos_0<=(n/2)){
    out(pos_0),out(n),out(pos_0+1),outn(n);
} else{
    out(1),out(pos_0),out(1),outn(pos_0-1);
}
```

#### 题解2：作者：Chouquet (赞：5)
**星级：4星**
**关键亮点**：
- 通过分类讨论，详细分析了不同情况下的构造方法。
- 代码简洁，逻辑清晰，易于理解。
- 处理了全1字符串的特殊情况。

**核心代码**：
```cpp
for(int i=1;i<=n;i++)
    if(s[i]=='0'){
        ok = 1;
        if(i > (n >> 1))
            printf("1 %d 1 %d\n", i, i - 1);
        else
            printf("%d %d %d %d\n", i, n, i + 1, n);
        break;
    }
if(!ok)
    printf("1 %d 2 %d\n", n - 1, n);
```

#### 题解3：作者：FoXreign (赞：1)
**星级：4星**
**关键亮点**：
- 通过位移操作构造倍数关系，思路清晰。
- 代码简洁，逻辑明确，易于理解。
- 处理了全1字符串的特殊情况。

**核心代码**：
```cpp
if(!l0) {
    printf("1 %d 2 %d\n", n-1, n);
    continue;
}
if(r0>n/2) {
    printf("1 %d 1 %d\n", r0, r0-1);
    continue;
}
if(l0<n-n/2+1) {
    printf("%d %d %d %d\n", l0, n, l0+1, n);
    continue;
}
```

### 最优关键思路或技巧
- **二进制数的倍数关系**：通过添加或删除前导零或后缀零，可以轻松构造满足倍数关系的子串。
- **分类讨论**：根据字符串中0的位置，分别处理不同情况，确保构造的子串满足长度和倍数关系。

### 可拓展之处
- 类似的问题可以通过二进制数的特性来解决，例如通过位移操作构造倍数关系。
- 可以扩展到其他进制数的倍数关系问题。

### 推荐题目
1. [P1001 A+B Problem](https://www.luogu.com.cn/problem/P1001)
2. [P1002 过河卒](https://www.luogu.com.cn/problem/P1002)
3. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)

### 个人心得摘录
- **调试经历**：在处理全1字符串时，需要特别注意构造的子串长度是否满足条件。
- **顿悟感想**：通过添加或删除前导零或后缀零，可以轻松构造满足倍数关系的子串，这大大简化了问题的复杂度。

---
处理用时：44.18秒