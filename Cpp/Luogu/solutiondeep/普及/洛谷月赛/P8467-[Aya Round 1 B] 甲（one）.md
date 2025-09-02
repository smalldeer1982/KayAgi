# 题目信息

# [Aya Round 1 B] 甲（one）

## 题目描述

定义长度为 $5$ 的序列 $S$ 为「好的」，当且仅当存在长度为 $5$ 的排列 $P$，满足 $S_{P_1}-1=S_{P_2}=S_{P_3}+1$ 且 $S_{P_4}=S_{P_5}$。现有一长度为 $5$ 的整数序列 $a$，满足 $0\le a_i \le 9(1\le i \le 5)$。其中 $a_1 \sim a_4$ 给定。试判断是否存在 $a_5$ 满足 $a$ 为「好的」。

其中，长度为 $5$ 的排列 $P$，指的是一个长度为 $5$ 的数列，其中 $1,2,3,4,5$ 在这个数列中出现且只出现一次。

## 说明/提示

### 附加样例

- 样例 $2$ 见下发文件中的 $\textbf{\textit{one2.in/one2.ans}}$。该样例满足测试点 $2$ 的限制。
- 样例 $3$ 见下发文件中的 $\textbf{\textit{one3.in/one3.ans}}$。该样例满足测试点 $5$ 的限制。

### 样例解释

#### 样例 \#1

- 对于第 $1$ 组数据，可以令 $a_5=8$。此时存在 $P=\{4,1,2,5,3\}$，满足 $a_{P_1}-1=a_{P_2}=a_{P_3}+1$ 且 $a_{P_4}=a_{P_5}$。故输出 $1$。
- 对于第 $2$ 组数据，可以令 $a_5=4$。此时存在 $P=\{3,2,1,4,5\}$，满足 $a_{P_1}-1=a_{P_2}=a_{P_3}+1$ 且 $a_{P_4}=a_{P_5}$。故输出 $1$。
- 对于第 $3$ 组数据，不存在可以使 $a$ 为「好的」的 $a_5$。

$$
\begin{aligned}
\fcolorbox{black}{#fbb}{3\ \ 2\ \ 8\ \ 4} + \fcolorbox{black}{yellow}{8} &\Rightarrow \fcolorbox{black}{#fbb}{2\ \ 3\ \ 4} + \fcolorbox{black}{yellow}{8\ \ 8}\ {\color{green}\sqrt{}}\\
\fcolorbox{black}{#fbb}{1\ \ 2\ \ 3\ \ 4} + \fcolorbox{black}{yellow}{4} &\Rightarrow \fcolorbox{black}{#fbb}{1\ \ 2\ \ 3} + \fcolorbox{black}{yellow}{4\ \ 4}\ {\color{green}\sqrt{}}\\
\fcolorbox{black}{#fbb}{1\ \ 9\ \ 4\ \ 9} +   \begin{cases}
\fcolorbox{black}{yellow}{0}\\
\fcolorbox{black}{yellow}{1}\\
\cdots\\
\fcolorbox{black}{yellow}{9}
\end{cases}&\Rightarrow
{\color{red}\xcancel{\color{black}
\begin{cases}
\fcolorbox{black}{#fbb}{1\ \ 9\ \ 4\ \ 9\ \ 0}\\
\fcolorbox{black}{#fbb}{1\ \ 9\ \ 4\ \ 9\ \ 1}\\
\cdots\\
\fcolorbox{black}{#fbb}{1\ \ 9\ \ 4\ \ 9\ \ 9}
\end{cases}}}
\end{aligned}
$$

### 数据范围

$$
\def\arraystretch{1.5}
\begin{array}{|c|c|c|} \hline
\textbf{\textsf{测试点}} & \bm{{T\le}} & \textbf{\textsf{特殊性质}} \cr\hline
1 & 100 & \textbf{A} \cr\hline
2 & 100 & \textbf{B} \cr\hline
3 & 100 & - \cr\hline
4 & 1000 & - \cr\hline
5 & 10^5 & - \cr\hline
\end{array}
$$

- 特殊性质 $\bf A$：$a_1=a_2=a_3=a_4$。
- 特殊性质 $\bf B$：$a_1,a_2,a_3,a_4$ 互不相等。

对于 $100\%$ 的数据，$1\le T\le 10^5$，$0\le a_i \le 9$。

## 样例 #1

### 输入

```
5
3 2 8 4
1 2 3 4
1 9 4 9
1 0 0 1
0 0 4 2```

### 输出

```
1
1
0
0
1```

# AI分析结果

### 综合分析与结论

本题的核心在于判断是否存在一个 $a_5$ 使得序列 $a$ 满足「好的」条件。题解主要分为两类：一类是通过枚举全排列和 $a_5$ 的值进行暴力判断；另一类是通过分类讨论，利用序列的特性进行优化。

- **暴力枚举法**：通过枚举所有可能的排列和 $a_5$ 的值，直接判断是否满足条件。虽然时间复杂度较高，但由于数据范围较小，仍然可行。
- **分类讨论法**：通过分析序列的特性，减少不必要的枚举，提高效率。这种方法需要对序列的排列和数值关系有较深的理解。

### 所选高星题解

#### 1. 作者：chen_zhe (★★★★☆)
**关键亮点**：
- 使用 `next_permutation` 枚举所有排列，思路清晰，代码简洁。
- 通过枚举 $a_5$ 的值，直接判断是否满足条件，逻辑简单易懂。

**核心代码**：
```cpp
do {
    for (int i = 0; i <= 9; i++) {
        a[5] = i;
        if (a[P[0]] - 1 == a[P[1]] && a[P[1]] == a[P[2]] + 1 && a[P[3]] == a[P[4]])
            flag = true;
    }
} while (next_permutation(P, P + 5));
```
**实现思想**：通过 `next_permutation` 枚举所有排列，再枚举 $a_5$ 的值，判断是否满足条件。

#### 2. 作者：落花月朦胧 (★★★★☆)
**关键亮点**：
- 通过排序和分类讨论，减少枚举次数，提高效率。
- 代码结构清晰，逻辑严谨。

**核心代码**：
```cpp
for (int i = 0; i <= 9; i++) {
    auto B = A;
    B.push_back(i);
    std::sort(B.begin(), B.end());
    if (B[0] + 1 == B[1] && B[1] + 1 == B[2] && B[3] == B[4] || 
        (B[0] == B[1] && B[2] + 1 == B[3] && B[3] + 1 == B[4])) {
        std::cout << "1\n";
        return;
    }
}
```
**实现思想**：枚举 $a_5$ 的值，排序后判断是否满足条件。

### 最优关键思路与技巧

- **暴力枚举**：适用于数据范围较小的情况，通过枚举所有可能性进行判断。
- **分类讨论**：通过分析序列的特性，减少不必要的枚举，提高效率。

### 可拓展之处

- **类似题目**：可以扩展到更大范围的序列或更复杂的条件，通过类似的枚举或分类讨论方法解决。
- **优化思路**：对于更大范围的数据，可以考虑更高效的算法或数据结构，如哈希表等。

### 推荐题目

1. [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
2. [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
3. [P1056 排座椅](https://www.luogu.com.cn/problem/P1056)

这些题目都涉及到序列的处理和条件判断，可以通过类似的思路进行解决。

---
处理用时：26.87秒