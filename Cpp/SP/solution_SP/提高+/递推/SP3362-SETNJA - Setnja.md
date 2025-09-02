# SETNJA - Setnja

## 题目描述

在二叉树中：

每个节点都有两个孩子——一个左孩子和一个右孩子。
如果节点标记为整数 $x$ ，则其左子节点标记为 $2x$ ，右子节点标记为 $2x+1$ 。
树的根标为 $1$ 。
在二叉树上从根开始遍历。遍历中的每一步要么是跳到左孩子上，要么是跳到右孩子上，或暂停休息（停留在同一节点上）。

用由字符 $L，R$ 和 $P$ 组成的字符串描述遍历过程。

$L$ 表示跳到左孩子；
$R$ 表示跳到右孩子；
$P$ 表示暂停一轮操作。

$walk$ 的值是我们最终到达的节点的标签。例如，$LR$ 的 $walk$ 值为 5，而 $RPP$ 的 $walk$ 值为 3。

一次遍历由 $L，R，P$ 和 $* $ 描述。每个 $*$ 可以是三个动作中的任何一个。 例如， $L*R$ 可能代表 $LLR，LRR$ 和 $LPR$。集合 $ ** $ 可能代表$ LL，LR，LP，RL，RR，RP，PL，PR$ 和 $PP$。
最后，一次遍历后的 $walk$ 的总值是该次遍历中所有可能的遍历顺序的每一步所形成的 $walk$ 的值的总和。

计算给定遍历顺序后的 $walk$ 的总值。

## 样例 #1

### 输入

```
L*R```

### 输出

```
25```

# 题解

## 作者：TemplateClass (赞：0)

$\gdef \sum{\mathrm{sum}}$
$\gdef \count{\mathrm{count}}$

我们需要维护两个量：当前节点的可能值的总和，以及可能的路径数目。分别设它们为 $\sum$ 和 $\count$。初始时 $\sum = 1$，因为根节点的值为 $1$；$\count = 1$，因为目前只有一种路径，还未进行任何操作。

然后对于操作的每一步：

- 如果这一步是 $\tt L$，则 $\sum \gets \sum \times 2$。因为每个路径都会执行 $\tt L$ 操作，每个路径当前的节点值 $x$ 会变成 $2x$，所以新的 $\sum$ 是 $\sum \times 2$。而 $\count$ 保持不变。
- 如果这一步是 $\tt R$，则 $\sum \gets \sum \times 2 + \count$，因为每个 $x$ 变成 $2x + 1$，总和就是 $\sum \times 2 + \count$（每项增加 $1$，总共有 $\count$ 个项）。
- 如果这一步是 $\tt P$，毫无意义，跳过。
- 如果这一步是 $\texttt{*}$，则要考虑三种可能性。此时，每个当前可能的路径会分裂为三条路径，分别执行 $\tt L, R, P$。那么此时，$\sum$ 和 $\count$ 都会变化。
  - 执行 $\tt L$ 后的总和贡献是 $\sum \times 2 \times 1$（因为每个原来的路径变成 $\tt L$ 后的贡献是 $2x$，总和为 $2 \times \sum$，而每条路径现在有 $1$ 种可能）；
  - 执行 $\tt R$ 后的总和贡献是 $(\sum \times 2 + \count) \times 1$；
  - 执行 $\tt P$ 后的总和贡献是 $\sum \times 1$。
  - 所以此时总的贡献即为 $\sum \times 5 + \count$。同时，$\count \gets \count \times 3$，因为每个原来的路径分裂成三个路径。

因此直接计算即可，时间复杂度 $O(n)$，注意答案很可能很大，这里我采用 Python 3 中的 `decimal.Decimal` 类来统计答案。

```python
from decimal import *

s = input()
sum_val = Decimal(1)
count = Decimal(1)

getcontext().prec = 500000

for c in s:
    if c == 'L':
        sum_val = sum_val * Decimal(2)
    elif c == 'R':
        sum_val = sum_val * Decimal(2) + count
    elif c == '*':
        sum_val = Decimal(5) * sum_val + count
        count *= Decimal(3)

print(format(sum_val, 'f'))
```

---

