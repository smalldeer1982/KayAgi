# 题目信息

# Text Document Analysis

## 题目描述

Modern text editors usually show some information regarding the document being edited. For example, the number of words, the number of pages, or the number of characters.

In this problem you should implement the similar functionality.

You are given a string which only consists of:

- uppercase and lowercase English letters,
- underscore symbols (they are used as separators),
- parentheses (both opening and closing).

It is guaranteed that each opening parenthesis has a succeeding closing parenthesis. Similarly, each closing parentheses has a preceding opening parentheses matching it. For each pair of matching parentheses there are no other parenthesis between them. In other words, each parenthesis in the string belongs to a matching "opening-closing" pair, and such pairs can't be nested.

For example, the following string is valid: "\_Hello\_Vasya(and\_Petya)\_\_bye\_(and\_OK)".

Word is a maximal sequence of consecutive letters, i.e. such sequence that the first character to the left and the first character to the right of it is an underscore, a parenthesis, or it just does not exist. For example, the string above consists of seven words: "Hello", "Vasya", "and", "Petya", "bye", "and" and "OK". Write a program that finds:

- the length of the longest word outside the parentheses (print 0, if there is no word outside the parentheses),
- the number of words inside the parentheses (print 0, if there is no word inside the parentheses).

## 说明/提示

In the first sample, the words "Hello", "Vasya" and "bye" are outside any of the parentheses, and the words "and", "Petya", "and" and "OK" are inside. Note, that the word "and" is given twice and you should count it twice in the answer.

## 样例 #1

### 输入

```
37
_Hello_Vasya(and_Petya)__bye_(and_OK)
```

### 输出

```
5 4```

## 样例 #2

### 输入

```
37
_a_(_b___c)__de_f(g_)__h__i(j_k_l)m__
```

### 输出

```
2 6```

## 样例 #3

### 输入

```
27
(LoooonG)__shOrt__(LoooonG)
```

### 输出

```
5 2```

## 样例 #4

### 输入

```
5
(___)
```

### 输出

```
0 0
```

# AI分析结果

### 题目翻译
# 文本文档分析

## 题目描述
现代文本编辑器通常会显示一些关于正在编辑文档的信息。例如，单词数量、页数或字符数量。

在这个问题中，你需要实现类似的功能。

给定一个仅由以下内容组成的字符串：
- 大写和小写英文字母；
- 下划线符号（用作分隔符）；
- 括号（包括左括号和右括号）。

保证每个左括号都有对应的右括号，同样，每个右括号都有对应的左括号与之匹配。换句话说，字符串中的每个括号都属于一个匹配的“左 - 右”对，并且这些对不会嵌套。

例如，以下字符串是有效的：“_Hello_Vasya(and_Petya)__bye_(and_OK)”。

单词是连续字母的最大序列，即该序列的左侧第一个字符和右侧第一个字符是下划线、括号，或者根本不存在。例如，上述字符串由七个单词组成：“Hello”、“Vasya”、“and”、“Petya”、“bye”、“and”和“OK”。编写一个程序，找出：
- 括号外最长单词的长度（如果括号外没有单词，则输出 0）；
- 括号内单词的数量（如果括号内没有单词，则输出 0）。

## 说明/提示
在第一个样例中，单词“Hello”、“Vasya”和“bye”在任何括号之外，而单词“and”、“Petya”、“and”和“OK”在括号内。注意，单词“and”出现了两次，在答案中应计数两次。

## 样例 #1
### 输入
```
37
_Hello_Vasya(and_Petya)__bye_(and_OK)
```
### 输出
```
5 4
```

## 样例 #2
### 输入
```
37
_a_(_b___c)__de_f(g_)__h__i(j_k_l)m__
```
### 输出
```
2 6
```

## 样例 #3
### 输入
```
27
(LoooonG)__shOrt__(LoooonG)
```
### 输出
```
5 2
```

## 样例 #4
### 输入
```
5
(___)
```
### 输出
```
0 0
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是模拟遍历字符串的过程，通过标记当前是否在括号内，分别统计括号外最长单词长度和括号内单词数量。各题解的主要区别在于实现细节和代码风格。
- **思路**：大多题解通过一个标记变量（如 `flag`、`a`、`tmp` 等）来区分当前字符是在括号内还是括号外，然后根据字符类型（字母、下划线、括号）进行不同的处理。
- **算法要点**：在遍历字符串时，遇到字母则累加单词长度，遇到分隔符（下划线或括号）则判断是否需要更新最长单词长度或增加括号内单词数量。
- **解决难点**：主要难点在于正确处理括号的嵌套（本题保证括号不嵌套）和单词的分隔，确保统计结果准确。

### 通用建议与扩展思路
在处理字符串模拟问题时，要注意边界条件和特殊情况，如字符串开头或结尾是单词的情况。可以使用标记变量来区分不同的状态，使逻辑更加清晰。对于类似的字符串处理问题，如统计特定字符组合的数量、提取特定格式的信息等，都可以采用类似的模拟思路。

### 重点代码及核心实现思想
以下是作者为“TLMPEX”的题解的核心代码：
```c
#include<bits/stdc++.h>
using namespace std;
string k;
int main(){
    int n,i,a=0,s=0,x=0,y=0;
    cin>>n;
    getchar();
    getline(cin,k);
    for(i=0;i<n;i++){
        if(a<1&&k[i]!='_'&&k[i]!='(')s++;
        else if(a<1&&(k[i]=='_'||k[i]=='(')){
            x=max(x,s);
            s=0;
        }
        if(a&&k[i]!=')'){
            if(k[i]=='_'&&k[i-1]!='_'&&k[i-1]!='(')
                y++;
            if(k[i]!='_'&&k[i+1]==')')y++;
        }
        if(k[i]=='(')a=1;
        if(k[i]==')')a=0;
    }
    if(s)x=max(x,s);
    cout<<x<<" "<<y;
}
```
核心实现思想：使用变量 `a` 标记是否在括号内，`s` 记录当前单词长度，`x` 记录括号外最长单词长度，`y` 记录括号内单词数量。遍历字符串，根据字符类型和 `a` 的值进行相应的处理，最后输出结果。

### 推荐洛谷题目
1. [P1055 ISBN 号码](https://www.luogu.com.cn/problem/P1055)：字符串处理，需要根据规则判断 ISBN 号码的正确性。
2. [P1200 [USACO1.1] 你的飞碟在这儿 Your Ride Is Here](https://www.luogu.com.cn/problem/P1200)：字符串处理，通过计算字符串的乘积来判断是否匹配。
3. [P1308 统计单词数](https://www.luogu.com.cn/problem/P1308)：字符串处理，统计一个单词在给定文本中出现的次数。

### 个人心得摘录与总结
- **过氧化氢_syq0057**：第一次提交 #6WA 了，第二次交 #11WA 了，然后第三次过了。总结：在做字符串模拟题时，要注意边界条件和特殊情况，多进行测试，确保代码的正确性。 

---
处理用时：37.69秒