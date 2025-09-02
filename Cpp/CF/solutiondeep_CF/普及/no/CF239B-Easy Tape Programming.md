# 题目信息

# Easy Tape Programming

## 题目描述

There is a programming language in which every program is a non-empty sequence of "<" and ">" signs and digits. Let's explain how the interpreter of this programming language works. A program is interpreted using movement of instruction pointer (IP) which consists of two parts.

- Current character pointer (CP);
- Direction pointer (DP) which can point left or right;

Initially CP points to the leftmost character of the sequence and DP points to the right.

We repeat the following steps until the first moment that CP points to somewhere outside the sequence.

- If CP is pointing to a digit the interpreter prints that digit then CP moves one step according to the direction of DP. After that the value of the printed digit in the sequence decreases by one. If the printed digit was $ 0 $ then it cannot be decreased therefore it's erased from the sequence and the length of the sequence decreases by one.
- If CP is pointing to "<" or ">" then the direction of DP changes to "left" or "right" correspondingly. Then CP moves one step according to DP. If the new character that CP is pointing to is "<" or ">" then the previous character will be erased from the sequence.

If at any moment the CP goes outside of the sequence the execution is terminated.

It's obvious the every program in this language terminates after some steps.

We have a sequence $ s_{1},s_{2},...,s_{n} $ of "<", ">" and digits. You should answer $ q $ queries. Each query gives you $ l $ and $ r $ and asks how many of each digit will be printed if we run the sequence $ s_{l},s_{l+1},...,s_{r} $ as an independent program in this language.

## 样例 #1

### 输入

```
7 4
1>3>22<
1 3
4 7
7 7
1 7```

### 输出

```
0 1 0 1 0 0 0 0 0 0 
2 2 2 0 0 0 0 0 0 0 
0 0 0 0 0 0 0 0 0 0 
2 3 2 1 0 0 0 0 0 0 
```

# AI分析结果



# 题目内容重写

## 题目描述

有一种编程语言，其中每个程序都是由非空的“<”、“>”符号和数字组成的序列。解释器的工作原理如下：

指令指针（IP）由两部分组成：
- 当前字符指针（CP）
- 方向指针（DP，可指向左或右）

初始时，CP指向序列最左端字符，DP指向右。

重复以下步骤直到CP超出序列范围：
1. **数字处理**：若CP指向数字，打印该数字后，CP按DP方向移动一步。打印后的数字减1。若该数字原为0，则无法减，直接删除该字符。
2. **符号处理**：若CP指向“<”或“>”，则DP方向改为左或右。CP按新方向移动一步。若新指向的字符仍为符号，则删除原符号。

当CP超出序列时终止执行。

给定由“<”、“>”和数字组成的序列，回答q次查询。每次查询给出l和r，要求输出运行子序列s_l到s_r时各数字的打印次数。

# 算法分类
**模拟**

# 题解分析与总结

**关键思路对比**：
1. **删除处理**：
   - GUO120822：用'#'标记删除，通过`work`函数跳过标记。
   - RE_Prince：用布尔数组标记已删除位置。
   - do_while_true：直接修改字符为'*'并跳过。
2. **符号删除逻辑**：均在改变方向后检查下一字符是否为符号，若满足则删除当前符号。
3. **数据隔离**：每次查询复制原始数组，避免多测数据污染。

**最优思路提炼**：
- **符号处理**：方向改变后立即移动指针，若下一字符仍为符号则删除当前符号。
- **删除标记**：通过标记无效字符，在指针移动时循环跳过。
- **数组拷贝**：每次查询独立处理子序列，保证多测数据独立。

# 精选题解

## 1. RE_Prince（4星）
**亮点**：
- 使用布尔数组标记删除，逻辑清晰。
- 处理数字时区分0和其他情况，避免误操作。
- 代码结构规范，注释明确。

**核心代码**：
```cpp
int pl=l, dp=1;
while (pl>=l && pl<=r) {
    if (isdigit(f[pl])) {
        cnt[f[pl]-'0']++;
        if (f[pl] == '0') d[pl] = 1;
        else f[pl]--;
        // 移动并跳过已删除字符
        pl += dp;
        while (d[pl]) pl += dp;
    } else {
        // 处理方向并检查下一字符
        dp = (f[pl] == '<') ? -1 : 1;
        int now = pl;
        pl += dp;
        while (d[pl]) pl += dp;
        if (pl在范围内且f[pl]是符号) d[now] = 1;
    }
}
```

## 2. do_while_true（4星）
**亮点**：
- 通过`last`变量记录生效位置，避免误删。
- 使用`f`标记前一次是否为符号，逻辑严密。
- 代码注释详细，易于理解。

**调试心得**：
> “处理符号时要记录上一个有效的位置，否则可能删除错误字符。”

**核心代码**：
```cpp
if (ch[now] == '<' || ch[now] == '>') {
    // 更新方向并处理删除
    if (f) ch[last] = '*'; // 删除前一个符号
    f = 1;
    last = now;
}
```

# 拓展建议
- **同类题目**：
  1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003) - 模拟覆盖过程。
  2. [P1321 单词覆盖还原](https://www.luogu.com.cn/problem/P1321) - 字符串状态模拟。
  3. [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042) - 规则模拟与状态记录。

---
处理用时：64.51秒