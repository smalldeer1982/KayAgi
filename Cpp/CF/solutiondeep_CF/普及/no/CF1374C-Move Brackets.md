# 题目信息

# Move Brackets

## 题目描述

You are given a bracket sequence $ s $ of length $ n $ , where $ n $ is even (divisible by two). The string $ s $ consists of $ \frac{n}{2} $ opening brackets '(' and $ \frac{n}{2} $ closing brackets ')'.

In one move, you can choose exactly one bracket and move it to the beginning of the string or to the end of the string (i.e. you choose some index $ i $ , remove the $ i $ -th character of $ s $ and insert it before or after all remaining characters of $ s $ ).

Your task is to find the minimum number of moves required to obtain regular bracket sequence from $ s $ . It can be proved that the answer always exists under the given constraints.

Recall what the regular bracket sequence is:

- "()" is regular bracket sequence;
- if $ s $ is regular bracket sequence then "(" + $ s $ + ")" is regular bracket sequence;
- if $ s $ and $ t $ are regular bracket sequences then $ s $ + $ t $ is regular bracket sequence.

For example, "()()", "(())()", "(())" and "()" are regular bracket sequences, but ")(", "()(" and ")))" are not.

You have to answer $ t $ independent test cases.

## 说明/提示

In the first test case of the example, it is sufficient to move the first bracket to the end of the string.

In the third test case of the example, it is sufficient to move the last bracket to the beginning of the string.

In the fourth test case of the example, we can choose last three openning brackets, move them to the beginning of the string and obtain "((()))(())".

## 样例 #1

### 输入

```
4
2
)(
4
()()
8
())()()(
10
)))((((())```

### 输出

```
1
0
1
3```

# AI分析结果

【题目内容中文重写】
# 移动括号

## 题目描述

给定一个长度为 $n$ 的括号序列 $s$，其中 $n$ 是偶数（能被2整除）。字符串 $s$ 由 $\frac{n}{2}$ 个左括号 '(' 和 $\frac{n}{2}$ 个右括号 ')' 组成。

在一次操作中，你可以选择恰好一个括号并将其移动到字符串的开头或结尾（即选择某个索引 $i$，删除 $s$ 的第 $i$ 个字符，并将其插入到所有剩余字符之前或之后）。

你的任务是找到使 $s$ 变为合法括号序列所需的最少操作次数。可以证明在给定的约束条件下，答案总是存在的。

合法括号序列的定义如下：

- "()" 是合法括号序列；
- 如果 $s$ 是合法括号序列，那么 "(" + $s$ + ")" 也是合法括号序列；
- 如果 $s$ 和 $t$ 都是合法括号序列，那么 $s$ + $t$ 也是合法括号序列。

例如，"()()", "(())()", "(())" 和 "()" 是合法括号序列，但 ")(", "()(" 和 ")))" 不是。

你需要回答 $t$ 组独立的测试用例。

## 说明/提示

在第一个样例中，只需将第一个括号移动到字符串的末尾。

在第三个样例中，只需将最后一个括号移动到字符串的开头。

在第四个样例中，可以选择最后三个左括号，将它们移动到字符串的开头，得到 "((()))(())"。

## 样例 #1

### 输入

```
4
2
)(
4
()()
8
())()()(
10
)))((((())```

### 输出

```
1
0
1
3```

【算法分类】
贪心

【题解分析与结论】
本题的核心思路是通过贪心算法来统计需要移动的括号数量。所有题解都采用了类似的方法：遍历字符串，统计左括号和右括号的匹配情况，当遇到不匹配的右括号时，记录需要移动的次数。这种方法的时间复杂度为 $O(n)$，空间复杂度为 $O(1)$，非常高效。

【评分较高的题解】

1. **作者：Acestar (赞：4)**
   - **星级：4**
   - **关键亮点：** 思路清晰，代码简洁，直接通过统计不匹配的右括号数量来得到答案。
   - **核心代码：**
     ```cpp
     int sum = 0, ans = 0;
     for(int i = 0; i < len; i++) {
         if(s[i] == '(') sum++;
         else sum--;
         if(sum < 0) ans++, sum = 0;
     }
     printf("%d\n", ans);
     ```

2. **作者：Clouder (赞：1)**
   - **星级：4**
   - **关键亮点：** 通过将左括号和右括号分别视为 $1$ 和 $-1$，利用前缀和的概念来统计不匹配的括号数量。
   - **核心代码：**
     ```cpp
     int ans = 0, sum = 0;
     for(int i = 1; i <= n; ++i) {
         sum += (s[i] == '(' ? 1 : -1);
         if(sum < 0) ++ans, sum = 0;
     }
     printf("%d\n", ans);
     ```

3. **作者：PragmaGCC (赞：0)**
   - **星级：4**
   - **关键亮点：** 通过模拟括号匹配过程，统计未匹配的右括号数量，思路清晰且代码简洁。
   - **核心代码：**
     ```cpp
     int ans = 0, sta = 0;
     for(int i = 0; i < n; i++) {
         if(s[i] == '(') sta++;
         else {
             if(sta == 0) ans++;
             else sta--;
         }
     }
     cout << ans << endl;
     ```

【最优关键思路或技巧】
- **贪心思想：** 通过遍历字符串，实时统计左括号和右括号的匹配情况，当遇到不匹配的右括号时，记录需要移动的次数。
- **前缀和：** 将左括号和右括号分别视为 $1$ 和 $-1$，利用前缀和的概念来统计不匹配的括号数量。

【可拓展之处】
- **类似题目：** 可以扩展到其他类型的括号匹配问题，如多种括号的匹配（如 `{}`, `[]`, `()` 等）。
- **算法套路：** 贪心算法在处理括号匹配问题时非常有效，类似的思路可以应用于其他需要实时统计和匹配的场景。

【推荐题目】
1. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1449 后缀表达式](https://www.luogu.com.cn/problem/P1449)

---
处理用时：30.78秒