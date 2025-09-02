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
- **思路方面**：
    - **chen_zhe**：通过枚举5!种排列情况，再对a₅从0到9枚举，判断是否满足条件。
    - **落花月朦胧**：枚举0到9作为a₅，将其加入序列后排序，判断是否满足三种特定排序情况。
    - **云裳**：分类讨论，一种是序列中存在三个数满足a + 1 = b = c - 1 ，另一种是序列中有两个相等数，剩下两数相差1或2 。
    - **MujicaSaki**：枚举0到9加入序列，排序后判断是否满足s₁ + 1 = s₂ = s₃ - 1 && s₄ = s₅ ，因原40分代码判断第一种情况有局限，改进为三个数分别枚举且不相同。
- **算法要点**：主要是暴力枚举和条件判断，利用排序简化判断过程。
- **解决难点**：在于如何全面且高效地判断满足“好的”序列的条件。有的题解通过全排列枚举，有的通过分类讨论不同情况。

综合来看，chen_zhe的题解思路清晰，代码简洁直观，利用标准库函数实现全排列枚举；落花月朦胧的题解通过分析排序后的情况，简化了判断逻辑；云裳的题解通过细致分类讨论，减少了不必要的枚举，这三篇题解质量较高。MujicaSaki的题解虽思路正确，但代码相对复杂，可读性稍差。

### 所选的题解
- **作者：chen_zhe (5星)**
    - **关键亮点**：思路直接清晰，利用`next_permutation`函数枚举全排列，代码简洁明了，易于理解。
    ```cpp
    int T,a[6];
    int main()
    {
        cin >> T;
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
        return 0;
    }
    ```
    - **核心实现思想**：外层通过`next_permutation`枚举5个数的全排列，内层枚举a₅的取值，判断每种情况下是否满足“好的”序列条件。

- **作者：落花月朦胧 (4星)**
    - **关键亮点**：通过分析“好的”序列排序后的情况，总结出三种判断条件，减少了不必要的枚举，提高效率。
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
    - **核心实现思想**：枚举a₅取值加入原序列并排序，根据总结的三种排序后满足条件的情况进行判断。

- **作者：云裳 (4星)**
    - **关键亮点**：通过分类讨论，将原问题分为两种情况，分别判断，减少了枚举量，提高算法效率。
    ```cpp
    int main() {
        int t;
        cin >> t;
        while (t--) {
            int a[10];
            bool flag = 0;
            for (int i = 1; i <= 4; i++)
                cin >> a[i];
            sort(a + 1, a + 5);
            for (int i = 1; i <= 3; i++) {
                if (a[i] + 1 == a[i + 1] && a[i + 1] + 1 == a[i + 2]) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                cout << "1\n";
                continue;
            }
            for (int i = 1; i <= 4; i++) {
                for (int j = i + 1; j <= 4; j++) {
                    if (a[i] == a[j]) {
                        a[i] = INF, a[j] = INF;
                        flag = 1;
                        break;
                    }
                }
                if (flag)
                    break;
            }
            sort(a + 1, a + 5);
            if (!flag) {
                cout << "0\n";
                continue;
            }
            if (a[2] - a[1]!= 2 && a[2] - a[1]!= 1) {
                cout << "0\n";
                continue;
            }
            cout << "1\n";
        }
        return 0;
    }
    ```
    - **核心实现思想**：先排序，判断是否存在三个数满足a + 1 = b = c - 1 ，若不存在再找相等的两个数，处理后再次排序判断剩下两数差是否为1或2 。

### 最优关键思路或技巧
- **分类讨论**：如“云裳”题解，通过对原序列情况分类，减少不必要枚举，提高效率。
- **利用排序简化判断**：“落花月朦胧”和“MujicaSaki”题解，将序列排序后总结出满足条件的情况，使判断更简洁。

### 可拓展思路
同类型题可拓展到更大范围数据，此时暴力枚举可能失效，需进一步优化算法，如利用哈希表等数据结构快速查找满足条件的数。类似算法套路是对给定条件进行细致分析，通过分类讨论或排序等手段简化问题，降低时间复杂度。

### 相似知识点洛谷题目
- [P1157 组合的输出](https://www.luogu.com.cn/problem/P1157)：考察全排列枚举。
- [P1909 买铅笔](https://www.luogu.com.cn/problem/P1909)：通过分类讨论不同购买方案求解。
- [P1036 [NOIP2002 普及组] 选数](https://www.luogu.com.cn/problem/P1036)：需要枚举不同组合情况并判断。

### 个人心得摘录
- **MujicaSaki**：原代码只从第一个数字枚举判断第一种情况会有局限，比如对于某些数据不能全面判断，应三个数分别枚举且不能相同。总结为在枚举判断时要全面考虑各种可能情况，避免遗漏特殊数据导致错误。 

---
处理用时：38.37秒