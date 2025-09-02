# MEX Table

## 题目描述

某天，顽皮的学生马克在课堂上捣乱，于是老师萨沙让他上黑板。萨沙给了马克一个 $n$ 行 $m$ 列的表格，要他在表格中填写数字 $0, 1, \ldots, n \cdot m - 1$。每个数字必须使用且仅使用一次，并要求这些数字的排列方式使得每行和每列的 MEX（最小未出现非负整数）之和最大化。具体来说，他需要使 $\sum\limits_{i = 1}^{n} \operatorname{mex}(\{a_{i,1}, a_{i,2}, \ldots, a_{i,m}\}) + \sum\limits_{j = 1}^{m} \operatorname{mex}(\{a_{1,j}, a_{2,j}, \ldots, a_{n,j}\})$ 最大，其中 $a_{i,j}$ 表示第 $i$ 行第 $j$ 列的数字。老师萨沙只关心最终的结果，因此他要求马克只需要告诉他在最佳填法下行和列 MEX 之和的最大值。

**注释**：MEX（最小未出现非负整数）定义为在给定的整数集合中未出现的最小非负整数。例如：
- 对于集合 $\{2,2,1\}$，$\operatorname{mex} = 0$，因为数字 $0$ 没有出现在集合中。
- 对于集合 $\{3,1,0,1\}$，$\operatorname{mex} = 2$，因为数字 $0$ 和 $1$ 出现在集合中，而 $2$ 没有。
- 对于集合 $\{0,3,1,2\}$，$\operatorname{mex} = 4$，因为数字 $0, 1, 2, 3$ 都出现在集合中，而 $4$ 没有。

## 说明/提示

- 在第一个测试用例中，由于表格中唯一的数字是 $0$，因此第一行和第一列的 MEX 之和为 $\operatorname{mex}(\{0\}) + \operatorname{mex}(\{0\}) = 1 + 1 = 2$。
  
- 在第二个测试用例中，可以将表格填充为如下：

$$
\begin{array}{cc}
3 & 0 \\
2 & 1 \\
\end{array}
$$

这样计算可得 $\sum\limits_{i = 1}^{n} \operatorname{mex}(\{a_{i,1}, a_{i,2}, \ldots, a_{i,m}\}) + \sum\limits_{j = 1}^{m} \operatorname{mex}(\{a_{1,j}, a_{2,j}, \ldots, a_{n,j}\}) = \operatorname{mex}(\{3, 0\}) + \operatorname{mex}(\{2, 1\}) + \operatorname{mex}(\{3, 2\}) + \operatorname{mex}(\{0, 1\}) = 1 + 0 + 0 + 2 = 3$。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
3
1 1
2 2
3 5```

### 输出

```
2
3
6```

