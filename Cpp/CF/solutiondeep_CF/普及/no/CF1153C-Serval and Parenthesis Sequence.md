# 题目信息

# Serval and Parenthesis Sequence

## 题目描述

Serval soon said goodbye to Japari kindergarten, and began his life in Japari Primary School.

In his favorite math class, the teacher taught him the following interesting definitions.

A parenthesis sequence is a string, containing only characters "(" and ")".

A correct parenthesis sequence is a parenthesis sequence that can be transformed into a correct arithmetic expression by inserting characters "1" and "+" between the original characters of the sequence. For example, parenthesis sequences "()()", "(())" are correct (the resulting expressions are: "(1+1)+(1+1)", "((1+1)+1)"), while ")(" and ")" are not. Note that the empty string is a correct parenthesis sequence by definition.

We define that $ |s| $ as the length of string $ s $ . A strict prefix $ s[1\dots l] $ $ (1\leq l< |s|) $ of a string $ s = s_1s_2\dots s_{|s|} $ is string $ s_1s_2\dots s_l $ . Note that the empty string and the whole string are not strict prefixes of any string by the definition.

Having learned these definitions, he comes up with a new problem. He writes down a string $ s $ containing only characters "(", ")" and "?". And what he is going to do, is to replace each of the "?" in $ s $ independently by one of "(" and ")" to make all strict prefixes of the new sequence not a correct parenthesis sequence, while the new sequence should be a correct parenthesis sequence.

After all, he is just a primary school student so this problem is too hard for him to solve. As his best friend, can you help him to replace the question marks? If there are many solutions, any of them is acceptable.

## 说明/提示

It can be proved that there is no solution for the second sample, so print ":(".

## 样例 #1

### 输入

```
6
(?????
```

### 输出

```
(()())```

## 样例 #2

### 输入

```
10
(???(???(?
```

### 输出

```
:(
```

# AI分析结果

### 题目翻译

#### Serval 和括号序列

#### 题目描述

Serval 很快告别了 Japari 幼儿园，开始了他在 Japari 小学的生活。

在他最喜欢的数学课上，老师教了他以下有趣的定义。

一个括号序列是一个仅包含字符 `(` 和 `)` 的字符串。

一个正确的括号序列是一个可以通过在序列的原始字符之间插入字符 `1` 和 `+` 来转换为正确算术表达式的括号序列。例如，括号序列 `()()` 和 `(())` 是正确的（转换后的表达式分别为 `(1+1)+(1+1)` 和 `((1+1)+1)`），而 `)(` 和 `)` 则不是。注意，空字符串根据定义也是一个正确的括号序列。

我们定义 $|s|$ 为字符串 $s$ 的长度。字符串 $s = s_1s_2\dots s_{|s|}$ 的严格前缀 $s[1\dots l]$ $(1\leq l< |s|)$ 是字符串 $s_1s_2\dots s_l$。注意，根据定义，空字符串和整个字符串都不是任何字符串的严格前缀。

学习了这些定义后，他提出了一个新的问题。他写下一个仅包含字符 `(`, `)` 和 `?` 的字符串 $s$。他打算将 $s$ 中的每个 `?` 独立地替换为 `(` 或 `)`，使得新序列的所有严格前缀都不是正确的括号序列，而新序列本身是一个正确的括号序列。

毕竟，他只是一个小学生，这个问题对他来说太难了。作为他最好的朋友，你能帮他替换这些问号吗？如果有多个解，任何一个都是可接受的。

#### 说明/提示

可以证明第二个样例无解，因此输出 `:(`。

#### 样例 #1

##### 输入

```
6
(?????
```

##### 输出

```
(()())
```

#### 样例 #2

##### 输入

```
10
(???(???(?
```

##### 输出

```
:(
```

### 算法分类
贪心、字符串

### 题解分析与结论

该题的核心在于通过贪心策略构造一个合法的括号序列，同时确保所有严格前缀都不是合法的括号序列。大多数题解都采用了类似的贪心思路：尽量将左括号放在前面，右括号放在后面，以确保前缀和始终大于0，直到最后一个字符时才满足和为0。

### 评分较高的题解

#### 题解1：作者：hsfzLZH1 (赞：7)
- **星级**：5星
- **关键亮点**：思路清晰，代码简洁，通过从后往前替换 `?` 为 `)`，确保左括号尽量靠前，最后检查合法性。
- **核心代码**：
```cpp
for(int i=n;i>=1;i--)
{
    if(nww==n/2)break;
    if(ss[i]=='?')ss[i]=')',nww++;
    if(nww==n/2)break;
}
for(int i=1;i<=n;i++)if(ss[i]=='?')ss[i]='(';
```
- **实现思想**：从后往前替换 `?` 为 `)`，确保左括号尽量靠前，最后检查合法性。

#### 题解2：作者：StudyingFather (赞：0)
- **星级**：4星
- **关键亮点**：思路清晰，代码简洁，通过贪心策略将左括号尽量靠前，最后检查合法性。
- **核心代码**：
```cpp
for(int i=0;i<n;i++)
  if(s[i]=='?')
  {
   if(cnt1<n/2)s[i]='(',cnt1++;
   else s[i]=')',cnt2++;
  }
```
- **实现思想**：将左括号尽量靠前，最后检查合法性。

#### 题解3：作者：Special_Tony (赞：0)
- **星级**：4星
- **关键亮点**：思路清晰，代码简洁，通过贪心策略将左括号尽量靠前，最后检查合法性。
- **核心代码**：
```cpp
for(int i=0;i<n;++i)
  if(a[i]=='?')
    if(x)
      --x, a[i]='(';
    else
      --y, a[i]=')';
```
- **实现思想**：将左括号尽量靠前，最后检查合法性。

### 最优关键思路或技巧
1. **贪心策略**：尽量将左括号放在前面，右括号放在后面，以确保前缀和始终大于0，直到最后一个字符时才满足和为0。
2. **合法性检查**：在构造完序列后，需要检查其是否满足所有严格前缀都不是合法的括号序列，且整个序列是合法的括号序列。

### 可拓展之处
类似的问题可以通过贪心策略解决，尤其是在需要构造满足特定条件的序列时。例如，构造一个合法的括号序列，或者构造一个满足特定条件的字符串。

### 推荐题目
1. [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
2. [P1044 栈](https://www.luogu.com.cn/problem/P1044)
3. [P1241 括号序列](https://www.luogu.com.cn/problem/P1241)

---
处理用时：30.13秒