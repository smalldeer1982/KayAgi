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
本题要求判断是否存在 $a_5$ 使长度为 5 的序列满足特定条件。各题解思路可归为两类：一是枚举全排列，逐一判断；二是分类讨论或枚举 $a_5$ 后排序判断。

- **chen_zhe**：枚举 5! 种排列和 $a_5$ 的 10 种可能，用 `next_permutation` 函数生成全排列，简单直接但枚举次数多。
- **落花月朦胧**：枚举 $a_5$ 后排序，判断三种可能情况，思路清晰，代码简洁。
- **云裳**：分类讨论，根据序列中是否有三个连续数或两个相等数判断，通过排序和标记处理，逻辑稍复杂。
- **MujicaSaki**：枚举 $a_5$ 后排序，用三重循环枚举三个数，避免重复，解决了之前代码的问题，但代码较复杂。

### 所选题解
- **chen_zhe（5星）**
    - **关键亮点**：思路直接，使用标准库函数 `next_permutation` 简化全排列生成，代码简洁易懂。
    - **核心代码**：
```cpp
while (T--)
{
    bool flag=false;
    for (int i=1;i<=4;i++)
        cin >> a[i];
    int P[]={1,2,3,4,5};
    do
    {
        for (int i=0;i<=9;i++)
        {
            a[5]=i;
            if (a[P[0]]-1==a[P[1]] && a[P[1]]==a[P[2]]+1 && a[P[3]]==a[P[4]])
                flag=true;
        }
    }while (next_permutation(P,P+5));
    puts(flag?"1":"0");
}
```
核心思想：枚举 5! 种排列和 $a_5$ 的 10 种可能，判断是否满足条件。

- **落花月朦胧（4星）**
    - **关键亮点**：思路清晰，对排序后的序列分三种情况判断，代码简洁高效。
    - **核心代码**：
```cpp
void solve() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;
    std::vector<int> A = {a, b, c, d};
    for (int i = 0; i <= 9; i++) {
        auto B = A;
        B.push_back(i);
        std::sort(B.begin(), B.end());
        if (B[0] + 1 == B[1] && B[1] + 1 == B[2] && B[3] == B[4] || (B[0] == B[1] && B[2] + 1 == B[3] && B[3] + 1 == B[4])) {
            std::cout << "1\n";
            return;
        }
        if (B[0] + 1 == B[1] && B[1] == B[2] && B[2] == B[3] && B[3] + 1 == B[4]) {
            std::cout << "1\n";
            return;
        }
    }
    std::cout << "0\n";
}
```
核心思想：枚举 $a_5$ 后排序，判断三种可能情况。

### 最优关键思路或技巧
- 使用 `next_permutation` 函数生成全排列，简化代码实现。
- 对排序后的序列进行分类讨论，减少枚举次数。

### 拓展思路
同类型题可考虑增加序列长度或改变判断条件，类似算法套路可用于处理排列组合相关的判断问题。

### 洛谷题目推荐
- [P1008 三连击](https://www.luogu.com.cn/problem/P1008)：涉及全排列的枚举和判断。
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)：需要枚举组合并判断条件。
- [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：考察组合的生成和输出。

### 个人心得摘录与总结
- **MujicaSaki**：原代码只考虑一种枚举方式得 40 分，通过分析特殊数据发现问题，采用三个数分别枚举且不重复的方法解决问题，提醒在调试时要注意特殊数据的分析。 

---
处理用时：22.44秒