# 题目信息

# Name

## 题目描述

Everything got unclear to us in a far away constellation Tau Ceti. Specifically, the Taucetians choose names to their children in a very peculiar manner.

Two young parents abac and bbad think what name to give to their first-born child. They decided that the name will be the permutation of letters of string $ s $ . To keep up with the neighbours, they decided to call the baby so that the name was lexicographically strictly larger than the neighbour's son's name $ t $ .

On the other hand, they suspect that a name tax will be introduced shortly. According to it, the Taucetians with lexicographically larger names will pay larger taxes. That's the reason abac and bbad want to call the newborn so that the name was lexicographically strictly larger than name $ t $ and lexicographically minimum at that.

The lexicographical order of strings is the order we are all used to, the "dictionary" order. Such comparison is used in all modern programming languages to compare strings. Formally, a string $ p $ of length $ n $ is lexicographically less than string $ q $ of length $ m $ , if one of the two statements is correct:

- $ n&lt;m $ , and $ p $ is the beginning (prefix) of string $ q $ (for example, "aba" is less than string "abaa"),
- $ p_{1}=q_{1} $ , $ p_{2}=q_{2} $ , ..., $ p_{k-1}=q_{k-1} $ , $ p_{k}&lt;q_{k} $ for some $ k $ ( $ 1<=k<=min(n,m) $ ), here characters in strings are numbered starting from 1.

Write a program that, given string $ s $ and the heighbours' child's name $ t $ determines the string that is the result of permutation of letters in $ s $ . The string should be lexicographically strictly more than $ t $ and also, lexicographically minimum.

## 说明/提示

In the first sample the given string $ s $ is the sought one, consequently, we do not need to change the letter order there.

## 样例 #1

### 输入

```
aad
aac
```

### 输出

```
aad
```

## 样例 #2

### 输入

```
abad
bob
```

### 输出

```
daab
```

## 样例 #3

### 输入

```
abc
defg
```

### 输出

```
-1
```

## 样例 #4

### 输入

```
czaaab
abcdef
```

### 输出

```
abczaa
```

# AI分析结果

### 题目内容
# 名字

## 题目描述
在遥远的鲸鱼座τ星（Tau Ceti）星系，一切对我们来说都变得模糊不清。具体而言，鲸鱼座τ星人给孩子取名字的方式非常奇特。

年轻的父母阿巴克（abac）和巴德（bbad）正在思考给他们的第一个孩子取什么名字。他们决定名字将是字符串 $s$ 的字母排列。为了跟上邻居的步伐，他们决定给宝宝取的名字在字典序上要严格大于邻居儿子的名字 $t$。

另一方面，他们怀疑很快会引入名字税。根据该税，名字字典序越大的鲸鱼座τ星人将支付更高的税款。这就是为什么阿巴克和巴德想给新生儿取一个在字典序上严格大于名字 $t$ 且在此条件下字典序最小的名字。

字符串的字典序就是我们所熟悉的 “字典” 顺序。在所有现代编程语言中，这种比较方式用于比较字符串。形式上，长度为 $n$ 的字符串 $p$ 在字典序上小于长度为 $m$ 的字符串 $q$，如果以下两个陈述之一是正确的：
- $n < m$，并且 $p$ 是字符串 $q$ 的开头（前缀）（例如，“aba” 小于字符串 “abaa”）。
- 对于某个 $k$（$1 \leq k \leq \min(n, m)$），$p_1 = q_1$，$p_2 = q_2$，$\cdots$，$p_{k - 1} = q_{k - 1}$，$p_k < q_k$，这里字符串中的字符从 1 开始编号。

编写一个程序，给定字符串 $s$ 和邻居孩子的名字 $t$，确定由 $s$ 的字母排列得到的字符串。该字符串在字典序上应严格大于 $t$，并且在满足此条件下字典序最小。

## 说明/提示
在第一个样例中，给定的字符串 $s$ 就是所求的字符串，因此，我们无需在那里改变字母顺序。

## 样例 #1
### 输入
```
aad
aac
```
### 输出
```
aad
```

## 样例 #2
### 输入
```
abad
bob
```
### 输出
```
daab
```

## 样例 #3
### 输入
```
abc
defg
```
### 输出
```
-1
```

## 样例 #4
### 输入
```
czaaab
abcdef
```
### 输出
```
abczaa
```

### 算法分类
贪心

### 题解综合分析与结论
这两道题解都围绕如何找到满足字典序条件的字符串展开。No_commander 的题解采用贪心策略，通过逐步尝试抵着字典序相等重排 $s$，在遇到无法满足字典序大于等于 $t$ 某位字符时回退并调整，具有较强的逻辑性和优化意识；drah_yrev 的题解先判断一些特殊情况，再通过排序 $s$ 并遍历比较来确定结果，但整体思路相对不够清晰和完整，没有很好地处理所有情况。

### 所选的题解
- **No_commander（5星）**
    - **关键亮点**：采用贪心策略，逻辑清晰，复杂度分析合理，能高效解决问题。
    - **个人心得**：无

### 最优关键思路或技巧
采用贪心的思维方式，在尽量保证字典序相等的情况下构建目标字符串，遇到不满足条件时合理回退并调整后续字符顺序，以达到字典序严格大于 $t$ 且最小的目的。

### 可拓展之处
同类型题通常围绕字符串的字典序相关操作，类似算法套路可应用于在给定条件下寻找字符串排列的最优解问题。比如在一些字符串重排满足特定字典序关系的题目中，都可借鉴这种贪心构建的思路。

### 洛谷相似题目推荐
- P1059 [NOIP2006 普及组] 明明的随机数，涉及排序和去重，与本题对字符串排序处理有相似之处。
- P1181 数列分段 Section I，同样需要一定的贪心策略来解决问题，可锻炼贪心思维。
- P1909 买铅笔，通过比较不同购买方案的花费，选择最优方案，与本题贪心选择字典序最小的思路类似。 

---
处理用时：35.60秒