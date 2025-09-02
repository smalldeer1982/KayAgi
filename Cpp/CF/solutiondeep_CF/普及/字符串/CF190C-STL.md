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
战争爆发前，Vasya 曾是一名会计，他是少数会操作计算机的人之一，因此被分配做程序员。

我们都知道，程序经常会存储整数集合。例如，如果我们有一个关于带权有向图的问题，它的边可以用三个整数表示：起始顶点的编号、终止顶点的编号和边的权重。所以，当 Vasya 试图在他的程序中表示一个新发明的机器人的特征时，他遇到了以下问题。

Vasya 不是程序员，所以他问他的朋友 Gena，存储 $n$ 个整数的便捷方法是什么。Gena 过去用 X-- 语言编程，所以他只能使用该语言中出现的类型。让我们来定义一下，在 X-- 语言中什么是“类型”：
- 首先，“int” 是一种类型。
- 其次，以 “pair” 开头，后面跟着尖括号，尖括号内恰好列出两个用逗号分隔的 X-- 语言的其他类型，这样的字符串也是一种类型。此记录中不包含空格。
- 其他字符串都不能被视为类型。

更正式地说：类型 := int | pair<类型,类型>。例如，Gena 对图的边使用以下类型：pair<int,pair<int,int>>。

Gena 很高兴帮助 Vasya，他向 Vasya 口述了一种 X-- 语言的类型，用于存储 $n$ 个整数。不幸的是，Gena 很匆忙，所以他省略了标点符号。现在 Gena 已经离开了，无论 Vasya 多么努力，他都无法找到正确的标点符号来形成 X-- 语言的有效类型。

请帮助 Vasya 添加标点符号，以得到 X-- 语言的有效类型。否则，说明该任务无法完成。

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
- **思路对比**：大部分题解采用递归思路，利用递归处理 `pair` 的嵌套结构，遇到 `pair` 就递归处理两个子类型，遇到 `int` 则直接处理。而 myee 的题解使用栈来模拟递归过程，通过栈中元素的状态判断输入的合法性。
- **算法要点**：递归解法的要点在于定义递归函数，根据输入是 `pair` 还是 `int` 进行不同处理，并处理好输入不足和多余的情况。栈解法的要点是用栈记录每个 `pair` 的处理进度，通过入栈和出栈操作判断合法性。
- **解决难点**：各题解主要解决了两个难点，一是处理 `pair` 的嵌套结构，递归解法通过递归调用自然地处理嵌套，栈解法通过栈的操作模拟嵌套；二是判断输入的合法性，通过标记变量记录输入不足的情况，在递归结束后检查是否有多余输入。

### 所选题解
- **Anguei（5星）**
    - **关键亮点**：思路清晰，代码简洁易懂，对递归的处理和输入合法性的判断逻辑明确。
    - **核心代码**：
```cpp
bool ok = true;
std::string s, ans;

void input() {
    if (std::cin >> s) {
        if (s == "pair") {
            ans += "pair<";
            input();
            ans += ",";
            input();
            ans += ">";
        } else if (s == "int")
            ans += "int";
    } else
        ok = false;
}

int main() {
    std::getline(std::cin, s);
    input();
    if (!ok)
        ans = "Error occurred";
    std::getline(std::cin, s);
    if (s.size())
        ans = "Error occurred";
    std::cout << ans << std::endl;
}
```
核心实现思想：定义 `input` 函数进行递归输入处理，遇到 `pair` 则添加相应符号并递归处理两个子类型，遇到 `int` 则直接添加。通过 `ok` 标记判断输入是否不足，在递归结束后检查是否有多余输入。

- **Jiyuu_no_Tsubasa（4星）**
    - **关键亮点**：详细分析了不合法的两种情况，并给出了清晰的处理逻辑，代码结构清晰。
    - **核心代码**：
```cpp
string ans="";
bool flag=1;
void work(){
    string s;
    cin>>s;
    if(s=="pair"){
        ans+="pair<";
        work();
        ans+=",";
        work();
        ans+=">";
    }
    else if(s=="int")
        ans+="int";
    else flag=0;
}
int main(){
    int n; cin>>n;
    work();
    string s; cin>>s;
    if(flag==0) cout<<"Error occurred";
    else if(s.size()!=0 ) cout<<"Error occurred";
    else cout<<ans;
    return 0;
}
```
核心实现思想：`work` 函数进行递归处理，遇到 `pair` 递归处理两个子类型，遇到 `int` 直接添加。用 `flag` 标记输入是否不足，递归结束后检查是否有多余输入。

- **玄学OIER荷蒻（4星）**
    - **关键亮点**：对递归过程中的输入判断详细，代码注释清晰，便于理解。
    - **核心代码**：
```cpp
string ans;
bool read() {
    string u;
    if (cin>>u) {
        if (u=="pair") {
            ans+="pair<";
            if (read()) {
                ans+=",";
                if (read()) {
                    ans+=">";
                    return 1;
                } else return 0;
            } else return 0;
        } else {
            ans+=u;
            return 1;
        }
    } else return 0;
}
int main() {
    int n;
    cin>>n;
    bool b=read();
    if (cin>>ans) {
        cout<<"Error occurred";
        return 0;
    }
    if (b) cout<<ans;
    else cout<<"Error occurred";
    return 0;
}
```
核心实现思想：`read` 函数递归处理输入，遇到 `pair` 递归处理两个子类型，每次递归返回是否有输入。在 `main` 函数中检查是否有多余输入。

### 最优关键思路或技巧
- 递归是处理嵌套结构的有效方法，通过递归调用可以自然地处理 `pair` 的嵌套。
- 使用标记变量记录输入不足的情况，在递归结束后检查是否有多余输入，以判断输入的合法性。
- 用字符串存储答案，避免在处理过程中直接输出，方便处理不合法的情况。

### 可拓展之处
同类型题可能会有更复杂的嵌套结构或更多的类型定义，类似的算法套路可以是使用递归或栈来处理嵌套结构，同时注意输入的合法性判断。

### 推荐题目
- [P1030 [NOIP2001 普及组] 求先序排列](https://www.luogu.com.cn/problem/P1030)：通过递归处理二叉树的遍历问题。
- [P1305 新二叉树](https://www.luogu.com.cn/problem/P1305)：涉及二叉树的构建和递归遍历。
- [P1229 遍历问题](https://www.luogu.com.cn/problem/P1229)：需要根据二叉树的遍历结果递归求解其他遍历结果。

### 个人心得摘录与总结
- 玄学OIER荷蒻：提到因为没有检查多余输入而 WA 了一次，总结出需要在最后检查是否有多余输入，提醒我们在处理输入时要全面考虑各种情况。 

---
处理用时：53.16秒