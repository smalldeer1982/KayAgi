# 题目信息

# STL

## 题目描述

Vasya used to be an accountant before the war began and he is one of the few who knows how to operate a computer, so he was assigned as the programmer.

We all know that programs often store sets of integers. For example, if we have a problem about a weighted directed graph, its edge can be represented by three integers: the number of the starting vertex, the number of the final vertex and the edge's weight. So, as Vasya was trying to represent characteristics of a recently invented robot in his program, he faced the following problem.

Vasya is not a programmer, so he asked his friend Gena, what the convenient way to store $ n $ integers is. Gena used to code in language X-- and so he can use only the types that occur in this language. Let's define, what a "type" is in language X--:

- First, a type is a string "int".
- Second, a type is a string that starts with "pair", then followed by angle brackets listing exactly two comma-separated other types of language X--. This record contains no spaces.
- No other strings can be regarded as types.

More formally: type := int | pair<type,type>. For example, Gena uses the following type for graph edges: pair<int,pair<int,int>>.

Gena was pleased to help Vasya, he dictated to Vasya a type of language X--, that stores $ n $ integers. Unfortunately, Gena was in a hurry, so he omitted the punctuation. Now Gena has already left and Vasya can't find the correct punctuation, resulting in a type of language X--, however hard he tries.

Help Vasya and add the punctuation marks so as to receive the valid type of language X--. Otherwise say that the task is impossible to perform.

## 样例 #1

### 输入

```
3
pair pair int int int
```

### 输出

```
pair<pair<int,int>,int>```

## 样例 #2

### 输入

```
1
pair int
```

### 输出

```
Error occurred```

# AI分析结果

### 题目内容中文重写
# STL

## 题目描述
Vasya 在战争爆发前是一名会计，他是少数知道如何操作电脑的人之一，因此他被任命为程序员。

我们都知道程序经常存储整数集合。例如，如果我们有一个关于带权有向图的问题，它的边可以用三个整数表示：起始顶点的编号、终止顶点的编号和边的权重。因此，当 Vasya 试图在他的程序中表示一个新发明的机器人的特征时，他遇到了以下问题。

Vasya 不是程序员，所以他问他的朋友 Gena，存储 $n$ 个整数的便捷方法是什么。Gena 过去用 X-- 语言编码，所以他只能使用该语言中出现的类型。让我们定义一下，X-- 语言中的 “类型” 是什么：
- 首先，类型是字符串 “int”。
- 其次，类型是一个以 “pair” 开头，然后跟尖括号，尖括号内正好列出两个用逗号分隔的 X-- 语言的其他类型的字符串。这个记录中没有空格。
- 没有其他字符串可以被视为类型。

更正式地说：type := int | pair<type,type>。例如，Gena 对图的边使用以下类型：pair<int,pair<int,int>>。

Gena 很高兴帮助 Vasya，他向 Vasya 口述了一个 X-- 语言的类型，该类型存储 $n$ 个整数。不幸的是，Gena 很匆忙，所以他省略了标点符号。现在 Gena 已经离开了，Vasya 无论怎么努力都找不到正确的标点，无法得到 X-- 语言的有效类型。

帮助 Vasya 添加标点符号，以得到 X-- 语言的有效类型。否则，说明该任务无法完成。

## 样例 #1
### 输入
```
3
pair pair int int int
```
### 输出
```
pair<pair<int,int>,int>
```

## 样例 #2
### 输入
```
1
pair int
```
### 输出
```
Error occurred
```

### 综合分析与结论
这些题解主要围绕如何给只包含 `pair` 和 `int` 的字符串添加标点，使其成为合法的 X-- 语言类型展开。大部分题解采用递归的方法，少部分使用栈来解决问题。

#### 思路对比
- **递归思路**：大多数题解采用递归，遇到 `pair` 就递归处理两个子类型，遇到 `int` 则直接添加到答案字符串中。在递归过程中判断输入是否足够，递归结束后判断是否有多余输入。
- **栈思路**：用栈记录每个 `pair` 的处理进度，遇到 `pair` 入栈，遇到 `int` 出栈并更新状态，最后判断栈是否为空来确定是否合法。

#### 算法要点
- **递归**：利用递归函数模拟类型的嵌套结构，根据输入的 `pair` 或 `int` 进行不同处理。
- **栈**：通过栈的进出操作模拟类型的构建过程，判断输入是否合法。

#### 解决难点
- **判断合法性**：通过记录输入状态（如使用 `bool` 变量），在递归过程中判断输入是否足够，递归结束后判断是否有多余输入。
- **存储答案**：使用字符串存储最终结果，避免在处理过程中直接输出，因为可能存在不合法情况。

#### 评分
- **Anguei (赞：20)**：4星。思路清晰，代码简洁，递归实现逻辑明确，对输入不合法的情况处理得当。
- **Acerkaio (赞：8)**：3星。思路正确，代码结构清晰，但整体实现和细节处理稍逊一筹。
- **myee (赞：4)**：3星。采用栈的思路，有一定创新性，但代码中使用了较多自定义类型别名，影响可读性。
- **Jiyuu_no_Tsubasa (赞：3)**：3星。思路清晰，对不合法情况的分析详细，但代码中使用 `#include<bits/stdc++.h>` 可能存在兼容性问题。
- **玄学OIER荷蒻 (赞：2)**：3星。递归思路实现正确，但代码结构和注释可以进一步优化。
- **Xdl_rp (赞：0)**：3星。递归实现基本正确，但代码中 `read` 函数在本题中没有必要，增加了代码复杂度。
- **zbk233 (赞：0)**：3星。思路和实现与其他递归题解类似，没有明显亮点。
- **Toorean (赞：0)**：3星。递归思路清晰，但代码中部分逻辑可以简化。
- **shucai (赞：0)**：3星。思路和实现与其他递归题解相似，代码中使用 `#define int long long` 可能导致不必要的错误。
- **yimuhua (赞：0)**：3星。思路和实现与其他递归题解类似，没有突出特点。

#### 所选题解
- **Anguei (赞：20)**：4星。关键亮点是思路清晰，代码简洁，递归实现逻辑明确，对输入不合法的情况处理得当。
```cpp
bool ok = true;
std::string s, ans;

void input() // 简单的递归 
{
	if (std::cin >> s)
	{
		if (s == "pair")
		{
			ans += "pair<";
			input();
			ans += ",";
			input();
			ans += ">";
		}
		else if (s == "int")
			ans += "int";
	}
	else // 输入不全（意外终止） 
		ok = false;
}

int main()
{
	std::getline(std::cin, s); // 无用的一行输入，吃掉它 
    
	input();
    
	if (!ok)
		ans = "Error occurred";
        
	std::getline(std::cin, s);
	if (s.size()) // 输入有多余 
		ans = "Error occurred";
        
	std::cout << ans << std::endl;
}
```
核心实现思想：通过递归函数 `input` 处理输入，遇到 `pair` 递归处理两个子类型，遇到 `int` 直接添加到答案字符串中。在递归过程中判断输入是否足够，递归结束后判断是否有多余输入。

#### 最优关键思路或技巧
- **递归**：利用递归函数模拟类型的嵌套结构，根据输入的 `pair` 或 `int` 进行不同处理，简单高效地解决问题。
- **状态记录**：使用 `bool` 变量记录输入状态，方便判断输入是否合法。

#### 可拓展之处
同类型题或类似算法套路：
- 处理嵌套结构的表达式，如括号匹配、JSON 解析等。
- 树的遍历问题，递归可以很好地处理树的嵌套结构。

#### 推荐洛谷题目
- [P1739 表达式括号匹配](https://www.luogu.com.cn/problem/P1739)
- [P1030 求先序排列](https://www.luogu.com.cn/problem/P1030)
- [P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)

#### 个人心得摘录与总结
- **玄学OIER荷蒻**：提到最后需要检查多出来的输入，自己因为没检查导致 WA 了一次。总结是在处理输入时，要全面考虑输入可能出现的各种情况，包括输入不足和输入多余的情况。

---
处理用时：50.40秒